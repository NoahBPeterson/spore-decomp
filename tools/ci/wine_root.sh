#!/bin/sh
# The installed wine, msitools and xvfb as one archive of the packages' files, so the byte-match check unpacks them
# (seconds) instead of running apt-get update and installing about 150 packages (about 50 seconds).
#
#   sh tools/ci/wine_root.sh mark               before the install: remembers which packages the runner already has
#   sh tools/ci/wine_root.sh save DIR           after it: the files of every package the install added -> DIR/root.tar.zst
#   sh tools/ci/wine_root.sh restore DIR        unpacks DIR/root.tar.zst over /, keeping every file that already exists;
#                                               exits 1 unless wine, msiextract and Xvfb then run (the caller installs
#                                               with apt instead)
#
# Only packages the runner image did not have go in, never its upgraded ones or the dpkg database, and restore never
# replaces an existing file: GitHub serves several image versions at once (two jobs of one run got 20261116 and
# 20261122), so the archive only adds files and does not depend on which image it was made on.
set -eu
tmp=${RUNNER_TEMP:-/tmp}

pkgs() { dpkg-query -W -f '${db:Status-Abbrev}${binary:Package}\n' | sed -n 's/^ii *//p' | sort; }

case "${1:-}" in
mark)
    pkgs >"$tmp/wine_root.before" ;;
save)
    out=$2
    mkdir -p "$out"
    pkgs | comm -13 "$tmp/wine_root.before" - >"$tmp/wine_root.new"
    echo "$(wc -l <"$tmp/wine_root.new" | tr -d ' ') packages added by the install"
    # shellcheck disable=SC2046
    dpkg -L $(cat "$tmp/wine_root.new") | sort -u \
        | grep -Ev '^/usr/share/(doc|man|locale|lintian|bash-completion|zsh|bug|info)(/|$)' \
        | while IFS= read -r f; do if [ -e "$f" ] || [ -L "$f" ]; then printf '%s\n' "$f"; fi; done \
        >"$tmp/wine_root.files"
    sudo tar --no-recursion -T "$tmp/wine_root.files" -cpf - 2>/dev/null | zstd -q -T0 -6 >"$out/root.tar.zst"
    ls -l "$out/root.tar.zst"
    cut -d/ -f2-4 "$tmp/wine_root.files" | sort | uniq -c | sort -rn | head -12 ;;
restore)
    [ -f "$2/root.tar.zst" ] || { echo "no archive in $2"; exit 1; }
    zstd -dcq "$2/root.tar.zst" | sudo tar -xpf - -C / --skip-old-files
    sudo ldconfig
    wine --version && command -v msiextract >/dev/null && command -v Xvfb >/dev/null \
        || { echo "the unpacked wine does not run; installing with apt instead"; exit 1; } ;;
*)
    echo "usage: wine_root.sh mark | save DIR | restore DIR" >&2
    exit 2 ;;
esac
