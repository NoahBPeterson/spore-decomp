#!/bin/sh
# Install wine, msitools and xvfb from the cached .deb files when no Ubuntu mirror is reachable.
#
#   sh tools/ci/install_cached_debs.sh [DIR]      (default ~/apt-archives, the apt-noble-winehq-v1 cache)
#
# The cache holds every package the last networked install downloaded (warm-caches.yml).  Packages the runner image
# already has at the same or a newer version are skipped, so nothing is downgraded; the rest go to one dpkg -i call,
# which orders them by their dependencies.  Fails unless wine runs afterwards.
set -u
dir=${1:-$HOME/apt-archives}
ls "$dir"/*.deb >/dev/null 2>&1 || { echo "no cached .deb files in $dir" >&2; exit 1; }

list=$(mktemp)
skipped=0
for deb in "$dir"/*.deb; do
    pkg=$(dpkg-deb -f "$deb" Package)
    arch=$(dpkg-deb -f "$deb" Architecture)
    ver=$(dpkg-deb -f "$deb" Version)
    [ "$arch" = all ] && name=$pkg || name=$pkg:$arch
    have=$(dpkg-query -W -f='${db:Status-Abbrev} ${Version}' "$name" 2>/dev/null || true)
    case "$have" in
        "ii "*)
            if dpkg --compare-versions "${have##* }" ge "$ver"; then
                skipped=$((skipped + 1))
                continue
            fi ;;
    esac
    echo "$deb" >>"$list"
done
echo "installing $(wc -l <"$list" | tr -d ' ') cached packages ($skipped already installed at the same or a newer version)"
# shellcheck disable=SC2046
sudo DEBIAN_FRONTEND=noninteractive dpkg -i --force-confdef --force-confold $(cat "$list") >/dev/null || true
wine --version || { echo "wine is not usable after installing from the cache" >&2; exit 1; }
command -v msiextract >/dev/null || { echo "msiextract missing after installing from the cache" >&2; exit 1; }
