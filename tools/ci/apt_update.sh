#!/bin/sh
# apt-get update that survives an unreachable runner mirror.
#
# GitHub's Ubuntu runners fetch from azure.archive.ubuntu.com through mirror+file:/etc/apt/apt-mirrors.txt. When that
# name does not resolve, apt-get update only warns ("Failed to fetch ... Temporary failure resolving") and exits 0,
# and the install then fails with "held broken packages" because the i386 indexes are missing (2026-11-11, PR #170).
# This retries once, then points apt at archive.ubuntu.com and tries again.
set -u
log=$(mktemp)

update() {
    sudo apt-get update -qq >"$log" 2>&1
    status=$?
    cat "$log"
    [ $status -eq 0 ] && ! grep -q 'Failed to fetch' "$log"
}

update && exit 0
echo "apt-get update could not reach a mirror; retrying in 20 s"
sleep 20
update && exit 0

echo "switching the Ubuntu mirror to archive.ubuntu.com"
if [ -f /etc/apt/apt-mirrors.txt ]; then
    printf 'http://archive.ubuntu.com/ubuntu/\n' | sudo tee /etc/apt/apt-mirrors.txt >/dev/null
fi
for f in /etc/apt/sources.list /etc/apt/sources.list.d/*.sources /etc/apt/sources.list.d/*.list; do
    [ -f "$f" ] && sudo sed -i 's#http://azure\.archive\.ubuntu\.com/ubuntu#http://archive.ubuntu.com/ubuntu#g' "$f"
done
update && exit 0
echo "apt-get update still failing after switching mirrors" >&2
exit 1
