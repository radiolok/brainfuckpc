# YouTube tools

Helpers for the [video list](../../doc/videos.md).

| File | |
|---|---|
| `videos.json` | the playlist in publishing order: id, original title, English title, length |
| `fetch_subs.sh` | downloads YouTube auto-captions (Russian) for every video and runs `vtt2md.py` |
| `vtt2md.py` | cleans auto-caption `.vtt` (removes the rolling repeats and timing tags) into Markdown with clickable timestamps, one file per video, into `doc/videos/` |

```sh
pip install -U yt-dlp
./tools/youtube/fetch_subs.sh                      # all videos
ONLY=5hhbGBlP3_4 ./tools/youtube/fetch_subs.sh     # one video
COOKIES_FROM=firefox ./tools/youtube/fetch_subs.sh # if YouTube asks to sign in
```

It has to run from a home connection — YouTube answers datacenter IPs
(GitHub Actions, cloud VMs) with *"Sign in to confirm you're not a bot"*.
Raw `.vtt` files are kept in `tools/youtube/.subs/` (git-ignored), so a second
run only fetches what is missing.
