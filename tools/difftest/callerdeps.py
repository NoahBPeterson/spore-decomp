#!/usr/bin/env python3
"""Does any caller in the original image depend on a register surviving (or carrying a value out of) a call?

usage: callerdeps.py <va> <reg>[,<reg>...] [--result] [--depth N=2] [-v]
       callerdeps.py --results DIR [--out FILE]     classify every FAIL in DIR (rebaseline/equiv JSONs) whose
                                                  reason names a register ("first: xmm4 (untouched ...)", "first: eax")

The equivalence harness and tools/hybrid/build.py refuse a replacement that writes a register the original
never writes (an LTCG caller may keep a live value there across the call: InterpRamp 0x114e780 / xmm3,
crackling audio) or that drops an eax result the original leaves before `ret` (uninitialized_copy 0x99efa0,
rbtree::find 0xe5c780). Both are defects only if some caller actually reads that register after the call.
This tool answers that statically, from the original image:

  * call sites: every E8/E9 byte in .text whose rel32 lands on <va>. Hits that are not an instruction boundary
    in a linear decode of the containing function are walked anyway (a decode can desync on inline data, and
    a false byte match can only add DEPENDS/UNKNOWN, never hide a reader); the count is printed as unverified;
  * from each return address, every path is walked (both branch arms, direct jmps followed, loops cut by a
    visited set) until each register in the set is overwritten in full on that path (SAFE on the path) or
    read (DEPENDS, with the reading instruction as evidence);
  * a path that reaches `ret` with the register still pending escapes to the caller's own callers, which are
    checked the same way up to --depth levels (an eax value returned onward, or a register kept for an LTCG
    grandparent); beyond the depth, or at an indirect jmp, the path is UNKNOWN;
  * a direct call on the path: the callee is checked for reading the register before writing it (DEPENDS:
    register argument); otherwise the register stays pending through it (conservative: we do not assume the
    callee kills it). An indirect call reads ecx/edx (this / fastcall argument) and kills eax, ecx, edx,
    xmm0-7 (no custom convention is possible through a pointer);
  * callee-saved registers (ebx, esi, edi, ebp) are DEPENDS by the ABI without a search.
Verdict per (va, register set): DEPENDS if any path reads it, else UNKNOWN if any path is unknown, else SAFE.
Two questions, by mode: "preserve" (default; the original leaves the register untouched, does a caller keep a
live value in it across the call?) and --result (the original hands back a value in eax, does a caller read
it?). With no direct call site the function is reached only through pointers, where the standard ABI applies:
in preserve mode a scratch register is then SAFE; in result mode it is UNKNOWN, since a pointer caller may well
read the result (Pool_AllocGlobal 0x928ad0, an allocation callback, is exactly that case).

Written 2026-10-16 to tell which of the re-check's register FAILs are consequential.
"""
import argparse, bisect, glob, json, os, re, struct, sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import capstone                                    # noqa: E402
from capstone import x86                           # noqa: E402
from resolve import Image                          # noqa: E402
from regfacts import FULL                          # noqa: E402

CALLEE_SAVED = {"ebx", "esi", "edi", "ebp"}
SCRATCH = {"eax", "ecx", "edx"} | {"xmm%d" % k for k in range(8)}
# instructions that write a whole xmm register (anything else may merge into the old value)
XMM_FULL = {"movaps", "movups", "movapd", "movupd", "movdqa", "movdqu", "xorps", "xorpd", "pxor", "movd", "movq",
            "cvtdq2ps", "cvtps2dq", "cvttps2dq", "shufps", "unpcklps", "unpckhps", "andps", "orps", "andnps",
            "mulps", "addps", "subps", "divps", "minps", "maxps", "sqrtps", "rsqrtps", "rcpps", "pshufd", "pand",
            "por", "pandn", "paddd", "psubd", "cmpps", "movlhps", "movhlps"}
MAX_STEPS = 4000

_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_md.detail = True


class Deps:
    def __init__(self, img=None):
        self.img = img or Image()
        t0, tn = self.img.section(".text")
        self.t0, self.text = t0, self.img.read(t0, tn)
        self._sites = None
        self._ins = {}
        self._entry = {}

    # ------------------------------------------------------------- call sites

    def sites(self, va):
        """[(site va, 'call'|'jmp', containing function start, on a decoded boundary)] of direct calls/jmps to va."""
        if self._sites is None:
            self._sites = {}
            t = self.text
            for op in (b"\xe8", b"\xe9"):
                i = t.find(op)
                while 0 <= i <= len(t) - 5:
                    tgt = (self.t0 + i + 5 + struct.unpack_from("<i", t, i + 1)[0]) & 0xFFFFFFFF
                    if self.t0 <= tgt < self.t0 + len(t):
                        self._sites.setdefault(tgt, []).append((self.t0 + i, "call" if op == b"\xe8" else "jmp"))
                    i = t.find(op, i + 1)
        out = []
        for s, kind in self._sites.get(va, []):
            k = bisect.bisect_right(self.img.starts, s) - 1
            if k < 0:
                continue
            f = self.img.starts[k]
            out.append((s, kind, f, s in self.boundaries(f)))
        return out

    def boundaries(self, f):
        if f not in self._ins:
            lo, hi = self.img.func_extent(f)
            self._ins[f] = {i.address for i in _md.disasm(self.img.read(lo, hi - lo), lo)}
        return self._ins[f]

    def insn(self, a):
        try:
            return next(_md.disasm(self.img.read(a, 16), a), None)
        except Exception:
            return None

    # ------------------------------------------------------------- dataflow

    @staticmethod
    def rw(i):
        try:
            r, w = i.regs_access()
        except capstone.CsError:
            return set(), set(), set()
        reads = {FULL.get(i.reg_name(x), i.reg_name(x)) for x in r}
        writes_any = {FULL.get(i.reg_name(x), i.reg_name(x)) for x in w}
        full = set()
        for x in w:
            n = i.reg_name(x)
            if n in ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp"):
                full.add(n)
            elif n.startswith("xmm") and (i.mnemonic in XMM_FULL or (i.mnemonic in ("movss", "movsd") and "[" in i.op_str)):
                full.add(n)
        # xor r, r / sub r, r / pxor x, x: capstone lists the register as read, but no value is consumed
        if i.mnemonic in ("xor", "sub", "pxor", "xorps", "xorpd") and len(i.operands) == 2 and \
                i.operands[0].type == x86.X86_OP_REG and i.operands[1].type == x86.X86_OP_REG and \
                i.operands[0].reg == i.operands[1].reg:
            reads.discard(FULL.get(i.reg_name(i.operands[0].reg), i.reg_name(i.operands[0].reg)))
        return reads, writes_any, full

    def entry_reads(self, f, regs, depth):
        """Registers of `regs` that function f may read before writing (register arguments)."""
        key = (f, frozenset(regs))
        if key not in self._entry:
            self._entry[key] = set()          # recursion guard
            res = self.walk(f, set(regs), depth, entry=True)
            self._entry[key] = {r for r, _ in res["reads"]}
        return self._entry[key]

    def walk(self, start, regs, depth, entry=False):
        """Walk every path from `start` with `regs` pending. Returns {'reads': [(reg, insn va)],
        'escapes': bool, 'unknown': [why]}."""
        out = {"reads": [], "escapes": False, "unknown": []}
        seen = set()
        work = [(start, frozenset(regs))]
        steps = 0
        while work:
            a, pend = work.pop()
            while pend:
                if (a, pend) in seen:
                    break
                seen.add((a, pend))
                steps += 1
                if steps > MAX_STEPS:
                    out["unknown"].append("step budget at %08x" % a)
                    return out
                i = self.insn(a)
                if i is None or i.mnemonic in ("int3", "hlt", "ud2"):
                    break
                m = i.mnemonic
                reads, _w, full = self.rw(i)
                if m == "call":
                    op = i.operands[0]
                    if op.type == x86.X86_OP_IMM:
                        tgt = op.imm & 0xFFFFFFFF
                        if depth > 0 and tgt in self.img.start_set:
                            got = self.entry_reads(tgt, pend, depth - 1) if not entry else set()
                            for r in got:
                                out["reads"].append((r, i.address))
                            pend = pend - got
                        # conservative: whatever the callee does not read stays pending
                    else:
                        for r in pend & {"ecx", "edx"}:
                            out["reads"].append((r, i.address))
                        pend = pend - SCRATCH
                    a = i.address + i.size
                    continue
                hit = pend & reads
                for r in hit:
                    out["reads"].append((r, i.address))
                pend = pend - hit - full
                if m == "ret":
                    if pend:
                        out["escapes"] = True
                    break
                if m == "jmp":
                    op = i.operands[0]
                    if op.type == x86.X86_OP_IMM:
                        tgt = op.imm & 0xFFFFFFFF
                        if tgt in self.img.start_set and tgt != start:   # tail call: like call + ret
                            if not entry and depth > 0:
                                got = self.entry_reads(tgt, pend, depth - 1)
                                for r in got:
                                    out["reads"].append((r, i.address))
                            out["escapes"] = True
                            break
                        a = tgt
                        continue
                    out["unknown"].append("indirect jmp at %08x" % i.address)
                    break
                if m.startswith("j") or m in ("loop", "loope", "loopne", "jecxz"):
                    op = i.operands[0]
                    if op.type == x86.X86_OP_IMM:
                        work.append((op.imm & 0xFFFFFFFF, pend))
                a = i.address + i.size
        return out

    # ------------------------------------------------------------- verdict

    def check(self, va, regs, depth=2, _seen=None, result=False):
        """{'verdict': SAFE|DEPENDS|UNKNOWN, 'evidence': [...], 'sites': n}"""
        regs = set(regs)
        ev, unknown = [], []
        if regs & CALLEE_SAVED:
            return {"verdict": "DEPENDS", "evidence": ["callee-saved %s (ABI)" % ",".join(sorted(regs & CALLEE_SAVED))],
                    "sites": None}
        if regs - SCRATCH - CALLEE_SAVED:   # 'st' (x87 stack), segment registers, ...: not tracked by the walk
            return {"verdict": "UNKNOWN", "evidence": ["untracked register(s) %s" % ",".join(sorted(regs - SCRATCH - CALLEE_SAVED))],
                    "sites": None}
        _seen = _seen if _seen is not None else set()
        _seen.add(va)
        sites = self.sites(va)
        if not sites:
            if not result and regs <= SCRATCH:
                return {"verdict": "SAFE", "evidence": ["no direct call site: pointer callers follow the standard ABI, "
                                                        "which never keeps a scratch register across a call"], "sites": 0}
            return {"verdict": "UNKNOWN", "evidence": ["no direct call site: pointer callers cannot be seen"], "sites": 0}
        for s, kind, f, _ok in sites:
            if kind == "call":
                i = self.insn(s)
                res = self.walk(s + i.size, regs, depth)
            else:   # tail jmp from f: f's callers see our registers when f returns
                res = {"reads": [], "escapes": True, "unknown": []}
            for r, at in res["reads"]:
                ev.append("%s read at %08x after the %s at %08x (in %08x)" % (r, at, kind, s, f))
            unknown += res["unknown"]
            if res["escapes"] and not res["reads"]:
                if depth <= 0:
                    unknown.append("escapes from %08x past depth" % f)
                elif f not in _seen:
                    sub = self.check(f, regs, depth - 1, _seen, result)
                    if sub["verdict"] == "DEPENDS":
                        ev += ["via %08x: %s" % (f, e) for e in sub["evidence"]]
                    elif sub["verdict"] == "UNKNOWN":
                        unknown += ["via %08x: %s" % (f, e) for e in sub["evidence"]]
        unverified = sum(1 for x in sites if not x[3])
        if ev:
            return {"verdict": "DEPENDS", "evidence": ev, "sites": len(sites), "unverified": unverified}
        if unknown:
            return {"verdict": "UNKNOWN", "evidence": unknown, "sites": len(sites), "unverified": unverified}
        return {"verdict": "SAFE", "evidence": [], "sites": len(sites), "unverified": unverified}


REG_RE = re.compile(r"first: (eax|ecx|edx|ebx|esi|edi|ebp|xmm[0-7])\b( \(untouched)?")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("va", nargs="?")
    ap.add_argument("regs", nargs="?")
    ap.add_argument("--depth", type=int, default=2)
    ap.add_argument("--result", action="store_true", help="the register carries the original's result (eax)")
    ap.add_argument("--results")
    ap.add_argument("--out")
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    d = Deps()
    if a.results:
        rows = []
        for f in sorted(glob.glob(os.path.join(a.results, "*.json"))):
            try:
                r = json.load(open(f))[0]
            except Exception:
                continue
            m = REG_RE.search(r.get("reason") or "")
            if r.get("verdict") != "FAIL" or not m:
                continue
            va = int(r["va"], 16)
            # "first: eax" alone is a result the original returns; "(untouched by the original)" is preserve mode
            result = not m.group(2)
            res = d.check(va, {m.group(1)}, a.depth, result=result)
            rows.append({"slice": r["slice"], "va": r["va"], "reg": m.group(1),
                         "mode": "result" if result else "preserve", **res})
            print("%s %s %-5s %-8s %-8s %s" % (r["slice"], r["va"], m.group(1), rows[-1]["mode"], res["verdict"],
                                          (res["evidence"] or [""])[0]), flush=True)
        if a.out:
            json.dump(rows, open(a.out, "w"), indent=1)
        from collections import Counter
        print(Counter(x["verdict"] for x in rows))
        return
    res = d.check(int(a.va, 16), set(a.regs.split(",")), a.depth, result=a.result)
    print("%s %s: %s (%s direct sites)" % (a.va, a.regs, res["verdict"], res["sites"]))
    for e in res["evidence"][: None if a.v else 8]:
        print("  " + e)


if __name__ == "__main__":
    main()
