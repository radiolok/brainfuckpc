#!/usr/bin/env python3
"""Turn YouTube auto-generated .vtt subtitles into readable Markdown.

YouTube's automatic captions repeat every line two or three times while the
"karaoke" highlight moves along. This script drops the inline timing tags,
removes the repeats and groups the text into ~60-second paragraphs, each
starting with a link that opens the video at that moment.

    python3 vtt2md.py SUBS_DIR OUT_DIR [--videos videos.json] [--para 60]
                      [--fixes fixes.tsv]

SUBS_DIR holds files named <index>_<videoid>.<lang>.vtt as written by
fetch_subs.sh. One OUT_DIR/<index>-<videoid>.md is written per video, plus
OUT_DIR/README.md with the index.

fixes.tsv (next to this script by default) lists recurring recognition errors
as <regex> TAB <replacement>; they are applied to every caption line.
"""
import argparse
import json
import os
import re
import sys

TS = re.compile(r"(\d+):(\d\d):(\d\d)\.(\d+)\s+-->\s+(\d+):(\d\d):(\d\d)\.(\d+)")
TAG = re.compile(r"<[^>]+>")
NAME = re.compile(r"^(\d+)_([A-Za-z0-9_-]{11})\.([\w-]+)\.vtt$")
LANG_PREF = ["ru", "ru-orig", "en", "en-orig"]


def parse_vtt(path):
    """Yield (start_seconds, text_line) for every distinct caption line."""
    cues = []
    with open(path, encoding="utf-8") as f:
        block = []
        for raw in f:
            line = raw.rstrip("\n")
            if line == "":  # cues are separated by truly empty lines;
                # auto-captions put a single space inside a cue
                if block:
                    cues.append(block)
                block = []
            else:
                block.append(line)
        if block:
            cues.append(block)

    out = []
    last = ""
    for block in cues:
        start = None
        texts = []
        for line in block:
            m = TS.search(line)
            if m:
                h, mi, s = int(m.group(1)), int(m.group(2)), int(m.group(3))
                start = h * 3600 + mi * 60 + s
                continue
            if start is None:
                continue  # WEBVTT header, Kind:, Language: ...
            t = TAG.sub("", line).replace("&nbsp;", " ").replace("&amp;", "&").strip()
            if t:
                texts.append(t)
        for t in texts:
            # rolling captions: the same line appears again in the next cue
            if t == last or (last and last.endswith(t)):
                continue
            if last and t.startswith(last):
                t = t[len(last):].strip()
                if not t:
                    continue
            out.append((start, t))
            last = t
    return out


def load_fixes(path):
    """Read <regex> TAB <replacement> rules; '#' starts a comment line."""
    rules = []
    if not path or not os.path.exists(path):
        return rules
    with open(path, encoding="utf-8") as f:
        for n, raw in enumerate(f, 1):
            line = raw.rstrip("\n")
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            if "\t" not in line:
                sys.exit(f"{path}:{n}: expected <regex> TAB <replacement>")
            pat, rep = line.split("\t", 1)
            rules.append((re.compile(pat, re.IGNORECASE), rep))
    return rules


def apply_fixes(text, rules):
    for pat, rep in rules:
        text = pat.sub(rep, text)
    return text


def fmt(sec):
    h, rem = divmod(int(sec), 3600)
    m, s = divmod(rem, 60)
    return f"{h}:{m:02d}:{s:02d}" if h else f"{m}:{s:02d}"


def to_markdown(vid, lines, meta, para, rules=()):
    title = meta.get("ru") or vid
    head = [f"# {title}", ""]
    if meta.get("en") and meta["en"] != title:
        head += [f"*{meta['en']}*", ""]
    head += [f"▶ [youtu.be/{vid}](https://youtu.be/{vid})"
             + (f" · {meta['dur']}" if meta.get("dur") else ""), "",
             "> Automatic transcript generated from YouTube's auto-captions. "
             "The author's name and a few recurring terms are corrected "
             "([`fixes.tsv`](../../tools/youtube/fixes.tsv)); everything else is "
             "as recognised — expect misheard words, missing punctuation and "
             "wrong technical terms.", ""]
    body = []
    cur, cur_start = [], None
    for start, t in lines:
        if cur_start is None:
            cur_start = start
        if start - cur_start >= para and cur:
            body.append((cur_start, apply_fixes(" ".join(cur), rules)))
            cur, cur_start = [], start
        cur.append(t)
    if cur:
        body.append((cur_start, apply_fixes(" ".join(cur), rules)))
    for start, text in body:
        head.append(f"[`{fmt(start)}`](https://youtu.be/{vid}?t={int(start)}) {text}")
        head.append("")
    return "\n".join(head)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("subs")
    ap.add_argument("out")
    ap.add_argument("--videos", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "videos.json"))
    ap.add_argument("--para", type=int, default=60, help="paragraph length in seconds")
    ap.add_argument("--fixes", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "fixes.tsv"),
                    help="recognition fixes, <regex> TAB <replacement> per line ('' to disable)")
    a = ap.parse_args()
    rules = load_fixes(a.fixes)

    meta = {}
    if os.path.exists(a.videos):
        meta = {v["id"]: v for v in json.load(open(a.videos, encoding="utf-8"))}
    order = {vid: i for i, vid in enumerate(meta)}

    # pick the best language per video
    best = {}
    for fn in os.listdir(a.subs):
        m = NAME.match(fn)
        if not m:
            continue
        _, vid, lang = m.groups()
        rank = LANG_PREF.index(lang) if lang in LANG_PREF else len(LANG_PREF)
        if vid not in best or rank < best[vid][0]:
            best[vid] = (rank, fn, lang)
    if not best:
        sys.exit(f"no <index>_<id>.<lang>.vtt files in {a.subs}")

    os.makedirs(a.out, exist_ok=True)
    rows = []
    for vid, (_, fn, lang) in sorted(best.items(), key=lambda kv: order.get(kv[0], 999)):
        lines = parse_vtt(os.path.join(a.subs, fn))
        n = order.get(vid, len(order)) + 1
        name = f"{n:02d}-{vid}.md"
        with open(os.path.join(a.out, name), "w", encoding="utf-8") as f:
            f.write(to_markdown(vid, lines, meta.get(vid, {}), a.para, rules))
        words = sum(len(t.split()) for _, t in lines)
        rows.append((n, name, meta.get(vid, {}).get("ru", vid), lang, words))
        print(f"{name}: {lang}, {words} words")

    idx = ["# Video transcripts", "",
           "Automatic transcripts of the [BrainfuckPC playlist](../videos.md), "
           "generated by [`tools/youtube`](../../tools/youtube).", "",
           "| # | Video | Lang | Words |", "|---:|---|---|---:|"]
    idx += [f"| {n} | [{t}]({name}) | {lang} | {w} |" for n, name, t, lang, w in rows]
    with open(os.path.join(a.out, "README.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(idx) + "\n")


if __name__ == "__main__":
    main()
