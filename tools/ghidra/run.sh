#!/bin/sh
# Usage: tools/ghidra/run.sh <script.py> [args...]   (runs against the analyzed project, no re-analysis)
here=$(cd "$(dirname "$0")/../.." && pwd)
script=$1; shift
GHIDRA_INSTALL_DIR=$(ls -d /opt/homebrew/Cellar/ghidra/*/libexec | tail -1) \
GHIDRA_MAXMEM=10G \
exec pyghidra --project-path "$here/work/ghidra" --project-name spore --skip-analysis \
  "$here/work/SporeApp.analysis.bin" "$here/tools/ghidra/$script" "$@"
