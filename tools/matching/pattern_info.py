#!/usr/bin/env python3
"""pattern_info.py <queue-index> [--samples N] — show a queued pattern, its size and sample cards."""
import json, os, subprocess, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
i = int(sys.argv[1]); n = int(sys.argv[sys.argv.index("--samples") + 1]) if "--samples" in sys.argv else 3
todo = json.load(open(os.path.join(ROOT, "work/pattern_todo.json")))
if i >= len(todo):
    print("NO PATTERN"); sys.exit(1)
p = json.load(open(os.path.join(ROOT, "work/patterns.json")))[todo[i]]
print("PATTERN:", repr(p["pattern"]))
print("instances:", len(p["vas"]))
print("sample VAs:", " ".join(p["vas"][:12]))
sys.stdout.flush()
step = max(1, len(p["vas"]) // n)
subprocess.run([sys.executable, os.path.join(ROOT, "tools/matching/card.py")] + p["vas"][::step][:n])
