#!/usr/bin/env bash
# Build all BrainfuckPC AVR firmwares (Linux/macOS, also used by CI).
#
# Requirements: cmake, make, avr-gcc, avr-libc, avr-binutils.
#   Debian/Ubuntu: sudo apt install cmake gcc-avr avr-libc binutils-avr
#
# Usage:  ./fw/build.sh            -> results in fw/bin/
#         BUILD_DIR=/tmp/x ./fw/build.sh
#
# On Windows the legacy fw/build.py (Atmel Studio + MinGW) still works.

set -euo pipefail

FW_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${BUILD_DIR:-${FW_DIR}/build}"
BIN_DIR="${BIN_DIR:-${FW_DIR}/bin}"
TOOLCHAIN="${FW_DIR}/generic-gcc-avr.cmake"

if [[ -z "${AVR_FIND_ROOT_PATH:-}" ]]; then
    for p in /usr/lib/avr /usr/avr /opt/local/avr /usr/local/avr; do
        if [[ -d "$p" ]]; then export AVR_FIND_ROOT_PATH="$p"; break; fi
    done
    if [[ -z "${AVR_FIND_ROOT_PATH:-}" ]]; then
        gcc_dir="$(dirname "$(command -v avr-gcc)")/../avr"
        [[ -d "$gcc_dir" ]] && export AVR_FIND_ROOT_PATH="$(cd "$gcc_dir" && pwd)"
    fi
fi

rm -rf "$BIN_DIR"
mkdir -p "$BIN_DIR" "$BUILD_DIR"

# name | source dir | extra cmake args
TARGETS=(
    "memorybrd|memorybrd|-DAVR_MCU=atmega2560"
    "iv6brd_ip_show|iv6brd|-DAVR_MCU=atmega168 -DSHOWER=IP_SHOW -DBINARY_NAME=iv6brd_ip_show"
    "iv6brd_ap_show|iv6brd|-DAVR_MCU=atmega168 -DSHOWER=AP_SHOW -DBINARY_NAME=iv6brd_ap_show"
    "iv6brd_cmd_show|iv6brd|-DAVR_MCU=atmega168 -DSHOWER=CMD_SHOW -DBINARY_NAME=iv6brd_cmd_show"
    "iv6brd_counter|iv6brd|-DAVR_MCU=atmega168 -DCOUNTER=ON -DBINARY_NAME=iv6brd_counter"
    "iv6brd_terminal|iv6brd|-DAVR_MCU=atmega168 -DTERMINAL=ON -DBINARY_NAME=terminal"
)

# Allow building a single target: ./build.sh iv6brd_counter
ONLY="${1:-}"
failed=()

for entry in "${TARGETS[@]}"; do
    IFS='|' read -r name src args <<< "$entry"
    [[ -n "$ONLY" && "$ONLY" != "$name" ]] && continue
    echo "=== ${name} ==="
    bdir="${BUILD_DIR}/${name}"
    rm -rf "$bdir"
    # shellcheck disable=SC2086
    if cmake -S "${FW_DIR}/${src}" -B "$bdir" \
            -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN" $args >"$bdir.log" 2>&1 \
       && make -C "$bdir" >>"$bdir.log" 2>&1; then
        find "$bdir" -maxdepth 1 \( -name '*.elf' -o -name '*.hex' -o -name '*.lst' -o -name '*.map' \) \
            -exec cp {} "$BIN_DIR/" \;
        grep -E "^(Program|Data|  *text)" -A1 "$bdir.log" | head -4 || true
    else
        echo "!!! ${name} FAILED, log: $bdir.log"
        tail -30 "$bdir.log" || true
        failed+=("$name")
    fi
done

echo
ls -la "$BIN_DIR"
if (( ${#failed[@]} )); then
    echo "Failed: ${failed[*]}"
    exit 1
fi
