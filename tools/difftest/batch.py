#!/usr/bin/env python3
"""Run equiv.py over every nonmatching VA of the slices in a batch file and summarise.

usage: batch.py <work/batches/X.json | slice-id ...> [--out work/difftest/X_equiv.json] [equiv options]
Writes the per-function JSON (list of equiv results) and prints a summary table
(counts and KB of original code per verdict, most common UNSUPPORTED reasons).
Functions run sequentially in one process; a crash in one is recorded and the batch continues.
"""
import collections, json, os, re, sys, time, traceback

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import equiv  # noqa: E402
import slice as S  # noqa: E402


def targets(spec):
    out = []
    for s in spec:
        if s.endswith(".json"):
            # an entry's optional "test_vas" restricts it to those VAs (e.g. to finish an interrupted run)
            ids = [(x["id"], x.get("test_vas")) for x in json.load(open(s))]
        else:
            ids = [(s, None)]
        for sid, only in ids:
            for va, _d, _r in S.read_rows(os.path.join(S.slice_dir(sid), "nonmatching.txt")):
                if only is None or "%08x" % va in only:
                    out.append((sid, va))
    return out


def reason_class(r):
    why = r.get("reason", "")
    if why.startswith("our symbol not found"):
        return "symbol not found"
    if "unresolved reference" in why:
        return "unresolved references"
    if why.startswith("only "):
        m = re.search(r"discards: ([\w:()\-]+)", why)
        return "inputs discarded (%s)" % (m.group(1).split("=")[0] if m else "?")
    if "unresolved symbol(s)" in why:
        return "ours reached a trapped (EH/vtable-only) symbol"
    if why.startswith("compile failed"):
        return "compile failed"
    if why.startswith("harness error"):
        return "harness error"
    return why[:60]


def summary(results):
    lines = []
    by = collections.defaultdict(list)
    for r in results:
        by[r["verdict"]].append(r)
    lines.append("| verdict | functions | KB of original code |")
    lines.append("|---|---:|---:|")
    for v in ("PASS", "WEAK", "FAIL", "UNSUPPORTED"):
        kb = sum(r.get("orig_size", 0) for r in by[v]) / 1024.0
        lines.append("| %s | %d | %.1f |" % (v, len(by[v]), kb))
    lines.append("")
    lines.append("| slice | va | verdict | valid/inputs | coverage | KB | reason |")
    lines.append("|---|---|---|---:|---:|---:|---|")
    for r in sorted(results, key=lambda r: ("PASS WEAK FAIL UNSUPPORTED".split().index(r["verdict"]), r["slice"])):
        cov = r.get("coverage", {}).get("pct")
        lines.append("| %s | %s | %s | %s | %s | %.1f | %s |" % (
            r["slice"], r["va"], r["verdict"],
            "%d/%d" % (r["valid"], r["inputs"]) if "valid" in r else "-",
            "%.1f%%" % cov if cov is not None else "-", r.get("orig_size", 0) / 1024.0,
            (r.get("reason", "") + (" [%s]" % r["first_mismatch"].get("kind") if r.get("first_mismatch") else ""))
            .replace("|", "/")[:170]))
    uns = collections.Counter(reason_class(r) for r in by["UNSUPPORTED"])
    lines.append("")
    lines.append("UNSUPPORTED reasons: " + ", ".join("%s: %d" % kv for kv in uns.most_common()))
    return "\n".join(lines)


def main():
    argv = sys.argv[1:]
    out = None
    if "--out" in argv:
        i = argv.index("--out")
        out = argv[i + 1]
        del argv[i:i + 2]
    spec = [a for a in argv if not a.startswith("-") and (a.endswith(".json") or re.match(r"s[0-9a-f]{8}$", a))]
    rest = [a for a in argv if a not in spec]
    opts = equiv.parse_args(["x"] + rest)
    results = []
    done = set()
    if out and os.path.exists(out):      # resume: skip functions already in the output file
        try:
            for r in json.load(open(out)):
                if isinstance(r, dict) and "slice" in r and "va" in r:
                    results.append(r)
                    done.add((r["slice"], r["va"]))
        except Exception:
            pass
    tl = [t for t in targets(spec) if (t[0], "%08x" % t[1]) not in done]
    if done:
        print("resuming: %d already done, %d to go" % (len(done), len(tl)), flush=True)
    for k, (sid, va) in enumerate(tl):
        print("[%d/%d] %s %08x" % (k + 1, len(tl), sid, va), flush=True)
        t0 = time.time()
        try:
            r = equiv.test_function(sid, va, opts, log=lambda *a: None)
        except Exception as e:  # keep the batch going
            r = {"slice": sid, "va": "%08x" % va, "verdict": "UNSUPPORTED",
                 "reason": "harness error: %s" % e, "traceback": traceback.format_exc()[-2000:],
                 "seconds": round(time.time() - t0, 1)}
        if "orig_size" not in r:
            try:
                lo, hi = equiv.context()["img"].func_extent(va)
                r["orig_size"] = hi - lo
            except Exception:
                r["orig_size"] = 0
        results.append(r)
        equiv.print_result(r)
        if out:
            os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)
            tmp = out + ".tmp"          # atomic: a kill never leaves a truncated results file
            with open(tmp, "w") as fh:
                json.dump(results, fh, indent=1)
                fh.flush()
                os.fsync(fh.fileno())
            os.replace(tmp, out)
    text = summary(results)
    print(text)
    if out:
        open(os.path.splitext(out)[0] + "_summary.md", "w").write(text + "\n")


if __name__ == "__main__":
    main()
