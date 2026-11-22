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
