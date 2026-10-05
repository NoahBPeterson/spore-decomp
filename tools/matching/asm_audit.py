#!/usr/bin/env python3
"""List byte-exact claims whose source is assembly transcription rather than C++.

usage: asm_audit.py [slice-id ...]      (default: every slice under match/slices)
A manifest entry is flagged when its function body (text from its `// @ 0x<VA>` marker to the next one) uses
`_emit`, is `__declspec(naked)`, or contains more than 3 `__asm` blocks. A few `__asm` statements inside C++
(fnstcw/fldcw, cvtss2si helpers) are not flagged. Output: "<slice> <va> emit=N naked=B asm=N"; exit 1 if any.
Flagged entries need a human look: tiny hand-written thunks may be legitimate, transcribed bodies are not.
"""
import glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ids = sys.argv[1:] or sorted(os.path.basename(d) for d in glob.glob(os.path.join(ROOT, "match/slices/*")))
hits = 0
for sid in ids:
    d = os.path.join(ROOT, "match/slices", sid)
    man = os.path.join(d, "manifest.txt")
    if not os.path.exists(man):
        continue
    claimed = {l.split()[2].lower().zfill(8) for l in open(man)
               if l.strip() and not l.lstrip().startswith("#") and len(l.split()) >= 3}
    for cpp in glob.glob(os.path.join(d, "*.cpp")):
        parts = re.split(r"//\s*@\s*(?:0x)?([0-9a-fA-F]{6,8})", open(cpp, errors="ignore").read())
        for i in range(1, len(parts), 2):
            va, body = parts[i].lower().zfill(8), parts[i + 1]
            emit, naked, asm = body.count("_emit"), "naked" in body, len(re.findall(r"__asm\b", body))
            if va in claimed and (emit or naked or asm > 3):
                print("%s %s emit=%d naked=%s asm=%d" % (sid, va, emit, naked, asm))
                hits += 1
sys.exit(1 if hits else 0)
