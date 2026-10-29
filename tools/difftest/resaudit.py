#!/usr/bin/env python3
"""Resolution audit: check every address the resolver gave our function's references against the address the
ORIGINAL uses at the same spot.

The equivalence harness runs our compiled function inside the original image, so each relocation in our object
(a callee, a global, a vtable) must be mapped to an original address. resolve.py does that from names,
annotations and heuristics; a wrong mapping is silent: our build then calls/reads the wrong thing, and the
harness reports a false FAIL, or (worse) both builds agree on wrong behaviour and it reports a false PASS.
Three wave-1 FAILs were such mappings (another slice's `g_item_count`, ICF'd vector helpers run as our own
copies).

Method: disassemble both functions, align the two instruction streams (difflib over mnemonic + operand shapes),
and for every relocated 4-byte field of OUR instruction inside an aligned run, read the original's 4 bytes at
the same offset of the paired instruction. Expected original value = resolved address + the addend stored in
our object (rel32: the call/jmp target). Pairs come only from aligned runs of at least MIN_RUN instructions
(a short run can pair unrelated code). Per symbol:
  agree      every strong pair agrees
  disagree   some strong pair has a different original value; a different but byte-identical function
             (an un-folded copy of the same template) counts as `same-code`, not a disagreement
  unverified no strong pair (very different code around every use, or our own local data)
Symbols our object defines itself (loaded from our object, not mapped) are not audited.

usage: resaudit.py <slice-id> <va> [...] [--flags "..."]    (prints the audit of each function)
"""
import difflib, os, struct, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import capstone                                    # noqa: E402
from capstone import x86 as X                      # noqa: E402
from coff import REL_DIR32, REL_REL32              # noqa: E402
import resolve as R                                # noqa: E402

MIN_RUN = 3


def _shape(ins):
    ops = []
    for op in ins.operands:
        if op.type == X.X86_OP_REG:
            ops.append("r")
        elif op.type == X.X86_OP_IMM:
            ops.append("i")
        elif op.type == X.X86_OP_MEM:
            # an absolute operand ([g_x], [g_x+4]) must not pair with a register-based one ([ecx+0x88]): that
            # pairing compared a global's address with a field offset
            ops.append("m%d%s" % (op.size, "a" if op.mem.base == 0 and op.mem.index == 0 else
                                  "t" if op.mem.base == 0 else "b"))
        else:
            ops.append("?")
    return (ins.mnemonic,) + tuple(ops)


def our_insns(coff, fsym):
    sec = coff.sections[fsym.secno - 1]
    data = sec.data
    rel = {off: (si, typ) for (off, si, typ) in sec.relocs}

    # a switch's `jmp [eax*4 + table]` holds only the addend until relocated: apply our own section's DIR32
    # relocations for decoding, or recursive descent never reaches the case bodies and the audit pairs the
    # default case with the original's first case (0x4055e0)
    code = bytearray(data)
    for off, (si, typ) in rel.items():
        s = coff.syms[si]
        if typ == REL_DIR32 and s.defined and s.secno == fsym.secno and off + 4 <= len(code):
            struct.pack_into("<I", code, off, (s.value + struct.unpack_from("<I", data, off)[0]) & 0xFFFFFFFF)
    code = bytes(code)

    def rd(a, n):
        return code[a:a + n]

    def tt(a):
        x = rel.get(a)
        if x is None:
            return None
        s = coff.syms[x[0]]
        if s.defined and s.secno == fsym.secno:
            return (s.value + struct.unpack_from("<I", data, a)[0]) & 0xFFFFFFFF
        return None
    insns, _t = R.recursive_descent(rd, 0, len(data), fsym.value, tt)
    return insns, rel, data


def same_code(img, a, b):
    """True when original functions a and b are byte-identical (an un-folded template copy)."""
    try:
        la, ha = img.func_extent(a)
        lb, hb = img.func_extent(b)
    except Exception:
        return False
    return la == a and lb == b and ha - la == hb - lb and img.read(la, ha - la) == img.read(lb, hb - lb)


def same_data(img, coff, s, got, want, addend):
    """True when the original operand points at read-only bytes identical to what our operand points at: a
    string literal / constant the linker kept twice. Compared over our defined object's size when we have it."""
    ro = img.section(".rdata")
    if not ro or not all(ro[0] <= x < ro[0] + ro[1] for x in (got, want)):
        return False                                # only read-only data can be a harmless duplicate
    n = 0
    if s.defined:
        sec = coff.sections[s.secno - 1]
        n = len(sec.data) - s.value - addend
    n = max(4, min(n or 16, 256))
    try:
        return img.read(got, n) == img.read(want, n)
    except Exception:
        return False


def audit(coff, fsym, res, orig_insns, img):
    """-> dict: per-symbol verdicts plus summary lists (see module doc)."""
    ours, rel, data = our_insns(coff, fsym)
    oa, ua = sorted(orig_insns), sorted(ours)
    so = [_shape(orig_insns[a]) for a in oa]
    su = [_shape(ours[a]) for a in ua]
    sm = difflib.SequenceMatcher(None, so, su, autojunk=False)
    pair = {}                                       # our insn addr -> orig insn addr (strong pairs only)
    for bo, bu, n in sm.get_matching_blocks():
        if n >= MIN_RUN:
            for k in range(n):
                pair[ua[bu + k]] = oa[bo + k]
    per = {}                                        # symbol name -> {"agree": n, "disagree": [...], "same": [...], "unpaired": n}
    local = {}                                      # our locally loaded callee -> original call targets at its uses
    for a in ua:
        ins = ours[a]
        for p in range(a, a + ins.size):
            if p not in rel:
                continue
            si, typ = rel[p]
            s = coff.syms[si]
            if s.defined and s.secno == fsym.secno:
                continue                            # our own function's labels / jump tables
            if typ not in (REL_DIR32, REL_REL32):
                continue
            if si not in res.addr:
                # loaded from our object, not mapped. Harmless for data we define, but a CALL where the original
                # calls a real function means the harness runs our own copy of it (an ICF'd template helper):
                # behaviour may match while the call trace does not (the 0x41b960 / 0x41ca60 false FAILs)
                o = pair.get(a)
                oi = orig_insns.get(o) if o is not None else None
                if typ == REL_REL32 and oi is not None and oi.size == ins.size:
                    field = struct.unpack_from("<I", bytes(oi.bytes), p - a)[0]
                    got = (o + (p - a) + 4 + field) & 0xFFFFFFFF
                    if got in img.start_set:
                        local.setdefault(s.name, set()).add(got)
                continue
            rec = per.setdefault(s.name, {"agree": 0, "disagree": [], "same": [], "unpaired": 0,
                                          "resolved": res.addr[si]})
            o = pair.get(a)
            oi = orig_insns.get(o) if o is not None else None
            if oi is None or oi.size != ins.size:   # same shape but another encoding length: field offsets differ
                rec["unpaired"] += 1
                continue
            addend = struct.unpack_from("<I", data, p)[0]          # wraps: a negative addend is fine mod 2^32
            field = struct.unpack_from("<I", bytes(oi.bytes), p - a)[0]
            want = (res.addr[si] + addend) & 0xFFFFFFFF
            if typ == REL_REL32:
                got = (o + (p - a) + 4 + field) & 0xFFFFFFFF          # the original's call/jmp target
            else:
                got = field
            if got != want and not img.in_image(got):
                # the paired original operand is not an address at all (a float constant 0x3f333333 pushed where we
                # push a string): the alignment paired different instructions; not evidence either way
                rec["unpaired"] += 1
                continue
            if got == want:
                rec["agree"] += 1
            elif typ == REL_REL32 and same_code(img, got, want):
                rec["same"].append((o, got))
            elif typ == REL_DIR32 and same_data(img, coff, s, got, want, addend):
                rec["same"].append((o, got))        # a duplicate copy of identical read-only data (a string literal)
            else:
                rec["disagree"].append((o, got, want))
    out = {"symbols": {}, "disagree": [], "unverified": [], "agree": [], "same_code": [],
           "local_copy": [{"symbol": nm, "original": ["%08x" % v for v in sorted(vs)]} for nm, vs in sorted(local.items())]}
    for nm, rec in sorted(per.items()):
        if rec["disagree"]:
            v = "disagree"
            o, got, want = rec["disagree"][0]
            out["disagree"].append({"symbol": nm, "resolved": "%08x" % rec["resolved"], "expected": "%08x" % want,
                                    "original": "%08x" % got, "at": "%08x" % o, "pairs": rec["agree"] + len(rec["disagree"]),
                                    "disagreeing": len(rec["disagree"])})
        elif rec["agree"] or rec["same"]:
            v = "agree" if not rec["same"] else "same-code"
            (out["agree"] if v == "agree" else out["same_code"]).append(nm)
        else:
            v = "unverified"
            out["unverified"].append(nm)
        out["symbols"][nm] = {"verdict": v, "agree": rec["agree"], "disagree": len(rec["disagree"]),
                              "same_code": len(rec["same"]), "unpaired": rec["unpaired"]}
    out["pairs"] = len(pair)
    out["insns"] = [len(oa), len(ua)]
    return out


def _is_code(sec):
    c = sec.is_code
    return c() if callable(c) else c


def audit_bindings(coff, fsym, res, orig_insns, img):
    """{symbol index: (original address, evidence)} for references the resolver could not tie to the image but the
    original's own instructions do: our TU's own definition of a global the original keeps in its .data (Spore
    s01353d90 defines `Attribute gSpatialObjectAttributes[25]` and initialises it: ours wrote its private copy and
    every input FAILed), and a function or data symbol the resolver fell back to modelling (Spore 0x00afbde0's
    Elem24Vec::DtorElems ran as a zero stub where the original calls 0x00afb090). A binding needs at least one strong
    pair (same-size instructions in an aligned run, as audit() uses), every pair giving the same address, an address
    inside the image, and for a call a known function start. Symbols already mapped by name or position are never
    rebound: this only replaces "ours" and "model" with evidence."""
    ours, rel, data = our_insns(coff, fsym)
    oa, ua = sorted(orig_insns), sorted(ours)
    sm = difflib.SequenceMatcher(None, [_shape(orig_insns[a]) for a in oa], [_shape(ours[a]) for a in ua],
                                 autojunk=False)
    pair = {}
    for bo, bu, n in sm.get_matching_blocks():
        if n >= MIN_RUN:
            for k in range(n):
                pair[ua[bu + k]] = oa[bo + k]
    models = {m.get("symbol") for m in getattr(res, "models", ()) if str(m.get("kind") or "").startswith("model")}
    seen = {}                                       # si -> set of base addresses the pairs imply
    for a in ua:
        ins = ours[a]
        for p in range(a, a + ins.size):
            if p not in rel:
                continue
            si, typ = rel[p]
            sy = coff.syms[si]
            if typ not in (REL_DIR32, REL_REL32):
                continue
            # a named data object our TU defines (a section symbol such as `.bss` may hold several objects whose
            # image addresses need not be contiguous, so only named ones are bound)
            # Writable sections only: a read-only definition (a float constant `__real@...`, a string, a vtable) is
            # part of what our code computes, and binding it to the original's would hide a changed constant (the
            # test_changed_constant_fails mutant PASSed until this was restricted). Mutable globals are game state
            # whose storage is the image's.
            own_data = (si not in res.addr and sy.defined and sy.secno > 0 and sy.secno != fsym.secno and
                        not sy.name.startswith(".") and not _is_code(coff.sections[sy.secno - 1]) and
                        coff.sections[sy.secno - 1].writable)
            if not (own_data or (si in res.addr and sy.name in models)):
                continue
            o = pair.get(a)
            oi = orig_insns.get(o) if o is not None else None
            if oi is None or oi.size != ins.size:
                continue
            addend = struct.unpack_from("<I", data, p)[0]
            field = struct.unpack_from("<I", bytes(oi.bytes), p - a)[0]
            got = ((o + (p - a) + 4 + field) if typ == REL_REL32 else field) & 0xFFFFFFFF
            base = (got - addend) & 0xFFFFFFFF
            seen.setdefault(si, set()).add((base, typ))
    out = {}
    for si, bases in seen.items():
        if len({b for b, _t in bases}) != 1:
            continue
        base, typ = next(iter(bases))
        if not img.in_image(base):
            continue
        if typ == REL_REL32 and base not in img.start_set:
            continue
        out[si] = (base, "our own definition" if si not in res.addr else "was modelled")
    return out


def summary(a):
    """One line for the verdict reason / report."""
    s = "resolution audit: %d agree, %d same-code, %d unverified, %d disagree, %d local copies" % (
        len(a["agree"]), len(a["same_code"]), len(a["unverified"]), len(a["disagree"]), len(a["local_copy"]))
    if a["disagree"]:
        s += " (" + "; ".join("%s resolved %s (operand %s), original operand %s at %s" % (
            d["symbol"], d["resolved"], d["expected"], d["original"], d["at"])
                              for d in a["disagree"][:3]) + ")"
    if a["local_copy"]:
        s += " [our own copy runs where the original calls: " + "; ".join(
            "%s -> %s" % (d["symbol"], ",".join(d["original"])) for d in a["local_copy"][:3]) + "]"
    return s


if __name__ == "__main__":
    import equiv as E
    args = [x for x in sys.argv[1:]]
    flags = None
    if "--flags" in args:
        i = args.index("--flags")
        flags = args[i + 1]
        del args[i:i + 2]
    sid, vas = args[0], [int(v, 16) for v in args[1:]]
    for va in vas:
        t = E.prepare(sid, va, flags.split() if flags else None, lambda *x: None)
        if getattr(t, "audit", None) is None:
            if not hasattr(t, "orig_insns"):
                print("%08x  %s %s" % (va, t.verdict or "-", getattr(t, "reason", "")))
                continue
            t.audit = audit(t.coff, t.fsym, t.res, t.orig_insns, E.context()["img"])
        print("%08x  %s" % (va, summary(t.audit)))
        for nm, r in t.audit["symbols"].items():
            if r["verdict"] != "agree":
                print("    %-10s %s  %s" % (r["verdict"], nm, {k: v for k, v in r.items() if k != "verdict"}))
