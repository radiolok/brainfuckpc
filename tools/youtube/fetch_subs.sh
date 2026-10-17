#!/usr/bin/env bash
# Download auto-generated subtitles for the BrainfuckPC playlist and turn them
# into Markdown transcripts in doc/videos/.
#
# Run it from a home connection: YouTube answers cloud / CI machines with
# "Sign in to confirm you're not a bot". If it does that to you too, add
#   COOKIES_FROM=firefox ./tools/youtube/fetch_subs.sh     (or chrome, edge, ...)
#
# Requirements: python3, yt-dlp  (pip install -U yt-dlp)
#
#   ./tools/youtube/fetch_subs.sh          # all 34 videos
#   ONLY=5hhbGBlP3_4 ./tools/youtube/fetch_subs.sh

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
PLAYLIST="https://www.youtube.com/playlist?list=PLHI3L7Als_GPlqEA98NgcnIerBVcbE5Fn"
SUBS="${SUBS_DIR:-$HERE/.subs}"
OUT="${OUT_DIR:-$ROOT/doc/videos}"

command -v yt-dlp >/dev/null || { echo "yt-dlp not found: pip install -U yt-dlp" >&2; exit 1; }
mkdir -p "$SUBS"

args=(--skip-download --write-auto-subs --write-subs
      --sub-langs "ru,ru-orig" --sub-format vtt
      --extractor-args "youtube:lang=ru"
      --no-overwrites --ignore-errors --sleep-requests 1
      -o "$SUBS/%(playlist_index)03d_%(id)s.%(ext)s")
[[ -n "${COOKIES_FROM:-}" ]] && args+=(--cookies-from-browser "$COOKIES_FROM")

if [[ -n "${ONLY:-}" ]]; then
    # keep the playlist numbering for a single video
    idx=$(python3 -c "import json,sys;v=json.load(open('$HERE/videos.json'));print([x['id'] for x in v].index('$ONLY')+1)")
    args=("${args[@]/\%(playlist_index)03d/$(printf %03d "$idx")}")
    yt-dlp "${args[@]}" "https://youtu.be/$ONLY"
else
    yt-dlp "${args[@]}" "$PLAYLIST"
fi

# yt-dlp numbers the playlist newest-first; videos.json is oldest-first.
# vtt2md.py ignores the prefix and orders by videos.json, so both work.
python3 "$HERE/vtt2md.py" "$SUBS" "$OUT"
echo
echo "Transcripts written to ${OUT#$ROOT/}/ — review, then commit:"
echo "  git add doc/videos && git commit -m 'doc: video transcripts'"
