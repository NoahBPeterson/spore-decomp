#!/bin/sh
# Keep a permission broker alive. If the broker process dies, restart it detached.
# The broker is the single point of failure for a wave: if it is down, unanswered
# permission requests time out and abort every tool, silently stalling all sessions.
#
# usage: opencode_broker_watch.sh <group> <sessions-file>
group="${1:-gold1}"
sessions="${2:-work/opencode/sessions_${group}.txt}"
cd "$(dirname "$0")/.." || exit 1
watchlog="work/opencode/broker_watch_${group}.log"
while :; do
    if ! pgrep -f "opencode_broker.py ${group}" >/dev/null 2>&1; then
        echo "$(date '+%H:%M:%S') broker ${group} down; restarting" >> "$watchlog"
        .venv/bin/python tools/opencode_broker.py "${group}" --sessions "$PWD/${sessions}" \
            >> "work/opencode/broker_${group}.log" 2>&1 &
    fi
    sleep 30
done
