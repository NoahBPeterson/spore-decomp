#!/usr/bin/env python3
"""snapreplay.py: replay captured entry states through the original function and ours, and compare.

usage: snapreplay.py [--dir work/capture] [--va VA[,VA...]] [--limit N] [--budget N] [-v] [--json OUT]

tools/hybrid/capture.py records, on the first calls of each target function in a real run of the original game,
the thread's registers and the writable memory (as deltas: snapshot k holds the pages that changed since k-1).
For each snapshot this rebuilds the memory of that moment, maps it into the equivalence harness's machine
(tools/difftest/machine.py: the original image, our compiled function resolved against it as equiv.py does),
sets the registers, makes the return address the harness's sentinel, and runs the original function, then (from
the same state) ours. It compares what each left behind: every byte written outside the function's own stack
frame, eax / edx, the x87 top, esp. Real inputs, so a difference is a real behaviour difference (or a harness
limit: a call into another module's code, which the snapshot does not hold, stops a run; both sides stopping at
the same external call compares what was written up to it).

Verdicts per snapshot: SAME, DIFF (first differing address, both values, the global or object it falls in),
STOP (a side stopped: external call / fault / budget, with where), SKIP (no source, our function did not compile).
"""
import argparse, bisect, collections, glob, json, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))

CTX = {"edi": 0x9c, "esi": 0xa0, "ebx": 0xa4, "edx": 0xa8, "ecx": 0xac, "eax": 0xb0, "ebp": 0xb4, "eip": 0xb8,
       "eflags": 0xc0, "esp": 0xc4}
CTX_FPCW = 0x1c


def read_snapshots(d):
    """[(seq, va, path)] sorted by seq."""
    out = []
    for f in glob.glob(os.path.join(d, "cap_*.bin")):
        m = re.match(r"cap_([0-9a-f]{8})_([0-9a-f]{8})\.bin$", os.path.basename(f))
        if m:
            out.append((int(m[1], 16), int(m[2], 16), f))
    return sorted(out)


def parse(path):
    """-> (va, ctx bytes, [(page, bytes or None for zero)])"""
    b = open(path, "rb").read()
    magic, seq, va, n = struct.unpack_from("<4I", b, 0)
    assert magic == 0x50434d4d, path
    ctx = b[16:16 + n]
    p = 16 + n
    pages = []
    while True:
        rec = struct.unpack_from("<I", b, p)[0]
        p += 4
        if rec == 0xffffffff:
            break
        if rec & 1:
            pages.append((rec & ~0xfff, None))
        else:
            pages.append((rec, b[p:p + 0x1000]))
            p += 0x1000
    return va, ctx, pages


def module_of(va):
    """(module stem, source path) whose bookkeeping lists va."""
    for f in glob.glob(os.path.join(ROOT, "src", "**", "*.nonmatching.txt"), recursive=True) + \
            glob.glob(os.path.join(ROOT, "src", "**", "*.manifest.txt"), recursive=True):
        for line in open(f, errors="replace"):
            p = line.split()
            if p and ("%08x" % va) in p[:3]:
                src = re.sub(r"\.(nonmatching|manifest)\.txt$", ".cpp", f)
                return os.path.basename(src)[:-4], src
    return None, None


class Replayer:
    def __init__(self, opts):
        self.opts = opts
        self.runners = {}
        self.mem = {}           # page -> bytes: the memory as of the snapshot being replayed

    def runner(self, va):
        import equiv as E
        import machine as M
        if va in self.runners:
            return self.runners[va]
        # every Runner loads its object at the same address of the one shared machine and adds code hooks there:
        # a cached runner for another function would run whatever was loaded last, so each function gets a fresh
        # machine and only the current runner is kept
        self.runners.clear()
        ctx = E.context()
        ctx["m"] = E.machine_hooks(M.Machine(ctx["img"]))
        sid, src = module_of(va)
        r = None
        why = None
        if src is None:
            why = "no row lists it"
        else:
            o = E.parse_args([sid, "%x" % va, "--src", src])
            t = E.prepare(sid, va, None, lambda *a, **k: None, src)
            if t.verdict:
                why = "%s: %s" % (t.verdict, (getattr(t, "reason", "") or "")[:120])
            else:
                r = E.Runner(t, o)
        self.runners[va] = (r, why)
        return r, why

    def apply(self, pages):
        for p, data in pages:
            self.mem[p] = data

    def run_side(self, r, side, ctx):
        import machine as M
        from unicorn import UC_HOOK_MEM_WRITE, UC_PROT_READ, UC_PROT_WRITE
        from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                                       UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP,
                                       UC_X86_REG_EFLAGS, UC_X86_REG_FPCW, UC_X86_REG_FPSW, UC_X86_REG_FP0)
        m, uc = r.m, r.m.uc
        img_lo, img_hi = m.img.base, m.img.base + m.img.size
        harness = [(M.OBJ_BASE, M.OBJ_BASE + 0x10000000), (M.POOL_BASE, M.POOL_BASE + M.POOL_SIZE),
                   (M.DYN_BASE, M.DYN_BASE + M.DYN_SIZE), (M.TRAP_BASE, 0x100000000)]
        mapped = []
        restore = {}
        fresh = []
        for p in sorted(self.mem):
            if any(lo <= p < hi for lo, hi in harness):
                continue                                 # collides with the harness's own map: left out
            if img_lo <= p < img_hi:
                if not m.in_image_writable(p):
                    continue
                restore[p] = bytes(uc.mem_read(p, 0x1000))
                data = self.mem[p]
                uc.mem_write(p, data if data is not None else b"\0" * 0x1000)
            else:
                fresh.append(p)
        # contiguous pages in one mem_map each: unicorn's per-region cost makes 100k single-page maps quadratic
        i = 0
        while i < len(fresh):
            j = i + 1
            while j < len(fresh) and fresh[j] == fresh[j - 1] + 0x1000:
                j += 1
            lo, n = fresh[i], j - i
            try:
                uc.mem_map(lo, n * 0x1000, UC_PROT_READ | UC_PROT_WRITE)
                mapped.append((lo, n * 0x1000))
                uc.mem_write(lo, b"".join(self.mem[q] if self.mem[q] is not None else b"\0" * 0x1000
                                          for q in fresh[i:j]))
            except Exception:
                for q in fresh[i:j]:                     # overlaps an existing map: page by page
                    try:
                        uc.mem_map(q, 0x1000, UC_PROT_READ | UC_PROT_WRITE)
                        mapped.append((q, 0x1000))
                        uc.mem_write(q, self.mem[q] if self.mem[q] is not None else b"\0" * 0x1000)
                    except Exception:
                        pass
            i = j
        regs = {k: struct.unpack_from("<I", ctx, o)[0] for k, o in CTX.items()}
        m.take_dirty()
        m.dyn_next = M.DYN_BASE                         # the harness heap restarts per run: equal allocation
        m.dyn_sizes = {}                                # sequences give equal pointers on both sides
        m.rand_state = 1
        m.alloc_fail, m.alloc_count = (), 0
        m.lazy = None
        m.trace_imports = []
        m.fake_handler = None
        m.reset_cpu({}, [])
        for nm, rid in (("eax", UC_X86_REG_EAX), ("ebx", UC_X86_REG_EBX), ("ecx", UC_X86_REG_ECX),
                        ("edx", UC_X86_REG_EDX), ("esi", UC_X86_REG_ESI), ("edi", UC_X86_REG_EDI),
                        ("ebp", UC_X86_REG_EBP), ("esp", UC_X86_REG_ESP)):
            uc.reg_write(rid, regs[nm])
        uc.reg_write(UC_X86_REG_EFLAGS, regs["eflags"] & ~0x100)
        uc.reg_write(UC_X86_REG_FPCW, struct.unpack_from("<I", ctx, CTX_FPCW)[0] & 0xffff)
        esp0 = regs["esp"]
        ret_addr = struct.unpack("<I", uc.mem_read(esp0, 4))[0]
        uc.mem_write(esp0, struct.pack("<I", M.SENTINEL))
        written = {}

        def on_write(uc_, access, address, size, value, _):
            for pg in {address & ~0xfff, (address + size - 1) & ~0xfff}:
                if pg not in written:
                    try:
                        written[pg] = bytes(uc_.mem_read(pg, 0x1000))
                    except Exception:
                        written[pg] = None
        h = uc.hook_add(UC_HOOK_MEM_WRITE, on_write)

        def on_unmapped(uc_, access, address, size, value, _):
            # a page the capture never saw non-zero: the process had it as zero memory (data only, never code;
            # below the harness's own ranges)
            from unicorn import UC_MEM_READ_UNMAPPED, UC_MEM_WRITE_UNMAPPED
            if access not in (UC_MEM_READ_UNMAPPED, UC_MEM_WRITE_UNMAPPED) or not 0x10000 <= address < M.OBJ_BASE:
                return False
            for pg in {address & ~0xfff, (address + size - 1) & ~0xfff}:
                try:
                    uc_.mem_map(pg, 0x1000, UC_PROT_READ | UC_PROT_WRITE)
                    mapped.append((pg, 0x1000))
                except Exception:
                    pass
            return True
        from unicorn import UC_HOOK_MEM_READ_UNMAPPED, UC_HOOK_MEM_WRITE_UNMAPPED
        h2 = uc.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED, on_unmapped)
        r.cur = side
        r.calls = []
        r.fakes = []
        status = m.run(side.entry, None, self.opts.budget)
        r.cur = None
        uc.hook_del(h)
        uc.hook_del(h2)
        fpsw = uc.reg_read(UC_X86_REG_FPSW)
        top = (fpsw >> 11) & 7
        out = {"status": status, "fault": m.last_fault, "eip": uc.reg_read(0x1a) if False else None,
               "eax": uc.reg_read(UC_X86_REG_EAX), "edx": uc.reg_read(UC_X86_REG_EDX),
               "esp": (uc.reg_read(UC_X86_REG_ESP) - esp0) & 0xffffffff,
               "st0": uc.reg_read(UC_X86_REG_FP0 + top) if (8 - top) % 8 else None,
               "imports": list(m.trace_imports), "calls": list(r.calls)}
        # what changed: every written byte outside the function's own frame (below its entry esp + 4)
        after = {}
        for pg, before in written.items():
            if before is None:
                continue
            cur = bytes(uc.mem_read(pg, 0x1000))
            if cur != before:
                after[pg] = (before, cur)
            uc.mem_write(pg, before)                     # back to the snapshot for the other side
        frame_lo = esp0 - 0x100000
        changes = {}
        for pg, (before, cur) in after.items():
            for k in range(0x1000):
                a = pg + k
                if frame_lo <= a < esp0 + 4:
                    continue                             # the frame and the return slot
                if M.MISC_BASE <= a < M.MISC_BASE + M.MISC_SIZE or M.DYN_BASE <= a < M.DYN_BASE + M.DYN_SIZE:
                    continue                             # harness scratch / its heap (malloc results differ)
                if before[k] != cur[k]:
                    changes[a] = cur[k]
        out["changes"] = changes
        out["esp0"] = esp0
        m.take_dirty()
        m.take_image_dirty()
        uc.mem_write(esp0, struct.pack("<I", ret_addr))
        for p, n in mapped:
            uc.mem_unmap(p, n)
        for p, data in restore.items():
            uc.mem_write(p, data)
        return out

    def compare(self, a, b):
        if a["status"][0] != "ok" or b["status"][0] != "ok":
            return "STOP", "orig %s / ours %s" % (a["status"], b["status"])
        for k in ("eax", "esp"):
            if a[k] != b[k]:
                return "DIFF", "%s orig %08x ours %08x" % (k, a[k], b[k])
        ka, kb = set(a["changes"]), set(b["changes"])
        diff = sorted(x for x in ka | kb if a["changes"].get(x) != b["changes"].get(x))
        # a dword both sides set to an address in the stack below the entry esp (a pointer to a local: each
        # compiler lays its frame out differently) is the same value
        lo, hi = a["esp0"] - 0x100000, a["esp0"]

        def dword(ch, d):
            if all(d + i in ch for i in range(4)):
                return sum(ch[d + i] << (8 * i) for i in range(4))
            return None
        frame_ptr = set()
        for d in {x & ~3 for x in diff}:
            va_, vb_ = dword(a["changes"], d), dword(b["changes"], d)
            if va_ is not None and vb_ is not None and lo <= va_ < hi and lo <= vb_ < hi:
                frame_ptr.update(range(d, d + 4))
        diff = [x for x in diff if x not in frame_ptr]
        if diff:
            x = diff[0]
            return "DIFF", "%d bytes differ, first %08x%s: orig %s ours %s" % (
                len(diff), x, where(x), fmt(a["changes"].get(x)), fmt(b["changes"].get(x)))
        return "SAME", "%d bytes written" % len(ka)


def fmt(v):
    return "-" if v is None else "%02x" % v


_names = None


def where(a):
    """ (the named global the address falls in, from resolve_map.json)"""
    global _names
    if _names is None:
        _names = []
        p = os.path.join(ROOT, "work", "relink", "standalone", "resolve_map.json")
        if os.path.exists(p):
            rm = json.load(open(p))
            _names = sorted({(int(va, 16), n) for n, d in rm["names"].items() for va in d})
    i = bisect.bisect_right(_names, (a, "￿")) - 1
    if i >= 0 and 0x5a8000 <= a < 0x8ee5b94 and a - _names[i][0] < 0x100000:
        return " (%s+%#x)" % (_names[i][1][:50], a - _names[i][0])
    return ""


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dir", default=os.path.join(ROOT, "work", "capture"))
    ap.add_argument("--va")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--budget", type=int, default=20000000)
    ap.add_argument("--json")
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    os.chdir(ROOT)
    snaps = read_snapshots(a.dir)
    want = {int(v, 16) for v in a.va.split(",")} if a.va else None
    rp = Replayer(a)
    results = []
    tally = collections.Counter()
    done = 0
    for seq, va, path in snaps:
        _va, ctx, pages = parse(path)
        rp.apply(pages)
        if want and va not in want:
            continue
        if a.limit and done >= a.limit:
            break
        done += 1
        r, why = rp.runner(va)
        if r is None:
            verdict, detail = "SKIP", why
        else:
            try:
                o = rp.run_side(r, r.orig, ctx)
                u = rp.run_side(r, r.ours, ctx)
                verdict, detail = rp.compare(o, u)
            except Exception as e:
                verdict, detail = "ERROR", "%s: %s" % (type(e).__name__, e)
        tally[verdict] += 1
        results.append({"seq": seq, "va": "%08x" % va, "verdict": verdict, "detail": detail})
        print("%5d %08x %-5s %s" % (seq, va, verdict, detail), flush=True)
    print("; ".join("%s %d" % kv for kv in tally.most_common()))
    if a.json:
        json.dump(results, open(a.json, "w"), indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
