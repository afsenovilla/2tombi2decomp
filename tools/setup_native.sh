#!/bin/bash
# Installs the fast native toolchain (no Wine/DOSBox) for tools/ncheck.py:
#  - old-gcc gcc-2.7.2-psx (cc1 + cpp) from decompals/old-gcc -> /opt/oldgcc/gcc-2.7.2-psx
#    and gcc-2.8.1-psx (files with a `// CC gcc-2.8.1` header)  -> /opt/oldgcc/gcc-2.8.1-psx
#  - maspsx (ASPSX emulator)                                   -> /opt/maspsx
#  - binutils-mipsel-linux-gnu (as/objcopy/objdump)
set -e
for v in gcc-2.7.2-psx gcc-2.8.1-psx; do
  mkdir -p /opt/oldgcc/$v
  curl -fsSL https://github.com/decompals/old-gcc/releases/download/0.17/$v.tar.gz | tar xz -C /opt/oldgcc/$v
done
# gcc-2.8.1-nocse: gcc-2.8.1-psx without the post-reload CSE pass (reload_cse_regs returns at once), which Sony's
# library compiler did not run (`// CC gcc-2.8.1-nocse`, docs/STATUS.md); one byte of cc1 patched, checked by sha1
if [ ! -x /opt/oldgcc/gcc-2.8.1-nocse/cc1 ]; then
  echo "1e6d934a67650c9f9d9b8e9792df19e3252ce36d  /opt/oldgcc/gcc-2.8.1-psx/cc1" | sha1sum -c --quiet
  cp -r /opt/oldgcc/gcc-2.8.1-psx /opt/oldgcc/gcc-2.8.1-nocse.tmp
  printf '\xc3' | dd of=/opt/oldgcc/gcc-2.8.1-nocse.tmp/cc1 bs=1 seek=$((0x13F026)) conv=notrunc status=none
  echo "2e7a0f71ade51e18a1d05322d55b0986540b76f4  /opt/oldgcc/gcc-2.8.1-nocse.tmp/cc1" | sha1sum -c --quiet
  mv /opt/oldgcc/gcc-2.8.1-nocse.tmp /opt/oldgcc/gcc-2.8.1-nocse
fi
# Loop-hoisting variants (docs/STATUS.md 2026-11-23): Sony's library compiler hoisted more loop invariants out of
# loops with calls than the stock cc1. In scan_loop the threshold is `(loop_has_call ? 1 : 2) * (3 + n_non_fixed_regs)`;
# patching the immediates of `mov $1,%edx` / `mov $2,%edx` raises it. gcc-2.7.2-loop4: both set to 4 (file offsets
# 0xC6C66 / 0xC6C6D); gcc-2.8.1-loop2: the call case set to 2 (0xDC87D); gcc-2.8.1-nocse-loop2: the same on the
# nocse cc1. Per-file set-ups (`// CC gcc-2.7.2-loop4`...): CD_cachefile does not match with loop4.
patch_cc1() {  # patch_cc1 SRC DST SHA1_SRC SHA1_DST OFFSET:BYTE...
  local src=$1 dst=$2 s0=$3 s1=$4; shift 4
  [ -x /opt/oldgcc/$dst/cc1 ] && return 0
  echo "$s0  /opt/oldgcc/$src/cc1" | sha1sum -c --quiet
  rm -rf /opt/oldgcc/$dst.tmp && cp -r /opt/oldgcc/$src /opt/oldgcc/$dst.tmp
  for ob in "$@"; do
    printf "\\x${ob#*:}" | dd of=/opt/oldgcc/$dst.tmp/cc1 bs=1 seek=$((${ob%%:*})) conv=notrunc status=none
  done
  echo "$s1  /opt/oldgcc/$dst.tmp/cc1" | sha1sum -c --quiet
  mv /opt/oldgcc/$dst.tmp /opt/oldgcc/$dst
}
patch_cc1 gcc-2.7.2-psx gcc-2.7.2-loop4 2eb81ff2bb8a3a3515f7a6ec4676a48f7cca45bf \
  3384800e862f52e87cd3cbfb6ea5897496f2395b 0xC6C66:04 0xC6C6D:04
patch_cc1 gcc-2.8.1-psx gcc-2.8.1-loop2 1e6d934a67650c9f9d9b8e9792df19e3252ce36d \
  1f4a6ea4628c05cdd1dd16f155f4e6405367e345 0xDC87D:02
patch_cc1 gcc-2.8.1-nocse gcc-2.8.1-nocse-loop2 2e7a0f71ade51e18a1d05322d55b0986540b76f4 \
  0204821eb2eeadab4fa91b7a1517617d3feb3bb0 0xDC87D:02
[ -d /opt/maspsx ] || git clone -q https://github.com/mkst/maspsx.git /opt/maspsx
command -v mipsel-linux-gnu-as >/dev/null || apt-get install -y binutils-mipsel-linux-gnu
# PSY-Q headers used by the functions ported from psx_tomba (Sony copyright: not stored in this repo)
cd "$(dirname "$0")/.."
if [ ! -d include/psyq ]; then
  [ -d /tmp/psx_tomba ] || git clone -q --depth 1 https://github.com/hansbonini/psx_tomba /tmp/psx_tomba
  cp -r /tmp/psx_tomba/include/psyq include/psyq
fi
# psx_tomba's own base headers (MIT, per its README), used by the library C taken from it (src/*/psyq, `#include "pt/common.h"`)
if [ ! -f include/pt/common.h ]; then
  [ -d /tmp/psx_tomba ] || git clone -q --depth 1 https://github.com/hansbonini/psx_tomba /tmp/psx_tomba
  mkdir -p include/pt && cp /tmp/psx_tomba/include/{common.h,types.h,include_asm.h,version.h} include/pt/
  (cd /tmp/psx_tomba/src/psyq && find . -name '*.h') | while read -r h; do
    mkdir -p "include/pt/$(dirname "$h")"; sed 's|#include "common.h"|#include "pt/common.h"|' "/tmp/psx_tomba/src/psyq/$h" > "include/pt/$h"
  done
fi
# MIT decompilations of the Psy-Q libraries, read by hand-matching of the library (AGENTS.md "Compilers")
[ -d /opt/psyz ] || git clone -q --depth 1 https://github.com/Xeeynamo/psyz /opt/psyz || true
[ -d /opt/psy-q-decomp ] || git clone -q --depth 1 https://github.com/sozud/psy-q-decomp /opt/psy-q-decomp || true
# psyz's sources include the Psy-Q 4.0 SDK headers as include/og/ (its Makefile makes them from psyq400.tar.gz):
# the same headers, lower-case names, in /opt/psyz_inc/og for tools/pzsweep.py (never copied into the repo)
if [ -d /opt/psyz ] && [ ! -f /opt/psyz_inc/og/libgpu.h ]; then
  t=$(mktemp -d)
  if curl -fsSL --retry 3 -o $t/psyq400.tar.gz https://github.com/psyqz/psyz/releases/download/requirements/psyq400.tar.gz \
      && (cd $t && cp /opt/psyz/decomp/sdk/psyq400.tar.gz.sha256 . && sha256sum -c --quiet psyq400.tar.gz.sha256); then
    tar xzf $t/psyq400.tar.gz -C $t INCLUDE
    mkdir -p /opt/psyz_inc/og/sys
    for f in $t/INCLUDE/*.H; do tr -d '\r' < "$f" > "/opt/psyz_inc/og/$(basename "$f" | tr A-Z a-z)"; done
    for f in $t/INCLUDE/SYS/*.H; do tr -d '\r' < "$f" > "/opt/psyz_inc/og/sys/$(basename "$f" | tr A-Z a-z)"; done
  fi
  rm -rf $t
fi
echo "toolchain ready"
