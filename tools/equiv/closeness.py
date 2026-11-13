"""How close is our build of a function to retail, when it is neither byte-exact nor decided by a proof?

Static and fast (milliseconds), so it can rank every undecided function. Four measures:
  similarity  the instruction sequences compared with registers abstracted (any general register is `r`, any xmm
              `x`) and addresses normalized (a relocated field is `ADDR`, a call target `CALL`, a jump inside the
              function `L`), so register allocation and moved globals do not count as distance
  calls       the calls in order: direct, or indirect with the vtable slot (`call [r+0x14]` -> v14)
  stores      the memory offsets written through a register (member fields; the stack frame is left out) and to
              fixed addresses (globals)
  shape       conditional branches, loops (backward jumps) and returns
and a label: SAME SHAPE (same calls, stores and conditional branches), NEAR, or DIFFERENT SHAPE.

It measures structure, NOT correctness. Validated against proofs (2026-11-13, 300 random functions of each tier):
72% of proven-equivalent functions are SAME SHAPE, but so are 64% of proven-different ones, because most real bugs
(a wrong value, argument or condition) keep the calls, stores and branches. So it is a distance for orientation, never
a verdict: the verdict comes from tools/contrib/prove.py or the quick check's angr and emulator steps.
"""
import collections, difflib, re

import capstone
from capstone import x86_const as X

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MD.detail = True
GPR = re.compile(r"\b(e?[abcd]x|[abcd][lh]|e?[sd]i|e?[sb]p)\b")
XMM = re.compile(r"\bxmm\d\b")
HEX = re.compile(r"0x[0-9a-f]+")


def _reloc_bytes(f):
    return {o + k for o in f.relocs for k in range(4)}


def features(f):
    """(tokens, calls, stores, shape) of a Func (tools/equiv/func.py)"""
    rb = _reloc_bytes(f)
    toks, calls, stores = [], [], collections.Counter()
    cond = loops = rets = 0
    for i in MD.disasm(f.code, f.va):
        off = i.address - f.va
        relocated = any(o in rb for o in range(off, off + i.size))
        m = i.mnemonic
        ops = i.op_str
        if m == "call" or m.startswith("j"):
            if i.operands and i.operands[0].type == X.X86_OP_IMM:
                t = i.operands[0].imm & 0xffffffff
                inside = f.va <= t < f.va + len(f.code)
                ops = "L" if inside else "CALL"
                if m.startswith("j") and inside and t <= i.address:
                    loops += 1
                if m == "call":
                    calls.append("direct")
            elif m == "call":
                mm = re.search(r"\[[^\]]*?(0x[0-9a-f]+)\]", i.op_str)
                calls.append("v%x" % int(mm.group(1), 16) if mm and not relocated else "indirect")
            if m.startswith("j") and m != "jmp":
                cond += 1
        elif m.startswith("ret"):
            rets += 1
        if relocated:
            ops = HEX.sub("ADDR", ops)
        ops = XMM.sub("x", GPR.sub("r", ops))
        toks.append(m + " " + ops)
        # stores: memory operand written, not on the stack
        if i.operands and i.operands[0].type == X.X86_OP_MEM and (i.operands[0].access & capstone.CS_AC_WRITE):
            mem = i.operands[0].mem
            base = i.reg_name(mem.base) if mem.base else ""
            if base in ("esp", "ebp"):
                pass
            elif not base and not mem.index:
                stores["global"] += 1
            else:
                stores["+%x" % (mem.disp & 0xffffffff)] += 1
    return toks, calls, stores, (cond, loops, rets)


def compare(retail, ours):
    a, b = features(retail), features(ours)
    sim = difflib.SequenceMatcher(None, a[0], b[0], autojunk=False).ratio()
    calls_same = a[1] == b[1]
    sa, sb = a[2], b[2]
    st_common = sum((sa & sb).values())
    st_total = max(sum(sa.values()), sum(sb.values()))
    stores_same = sa == sb
    shape_same = a[3][0] == b[3][0]     # conditional branches; loop and return counts follow block layout
    diffs = []
    if not calls_same:
        if len(a[1]) != len(b[1]):
            diffs.append("calls: retail %d, ours %d" % (len(a[1]), len(b[1])))
        else:
            k = next(n for n, (x, y) in enumerate(zip(a[1], b[1])) if x != y)
            diffs.append("call #%d: retail %s, ours %s" % (k, a[1][k], b[1][k]))
    if not stores_same:
        fmt = lambda c: " ".join(k if n == 1 else "%s\u00d7%d" % (k, n) for k, n in sorted(c.items())[:4])
        only_r, only_o = fmt(sa - sb), fmt(sb - sa)
        diffs.append("stores: %d of %d alike%s%s" % (st_common, st_total,
                     "; only retail writes " + only_r if only_r else "",
                     "; only ours writes " + only_o if only_o else ""))
    if not shape_same:
        diffs.append("conditional branches: retail %d, ours %d" % (a[3][0], b[3][0]))
    big = (len(a[1]) != len(b[1])) or (st_total and st_common / st_total < 0.8) or abs(a[3][0] - b[3][0]) > 1
    if calls_same and stores_same and shape_same and sim >= 0.5:
        label = "SAME SHAPE"
    elif big or sim < 0.6:
        label = "DIFFERENT SHAPE"
    else:
        label = "NEAR"
    return {"label": label, "similarity": round(sim, 3), "calls_same": calls_same, "stores_same": stores_same,
            "shape_same": shape_same, "diffs": diffs, "n": (len(a[0]), len(b[0]))}


def describe(c):
    head = {"SAME SHAPE": "SAME SHAPE: the same calls, stores and branches (values can still differ: see the verdict)",
            "NEAR": "NEAR: mostly the same shape; one part differs a little",
            "DIFFERENT SHAPE": "DIFFERENT SHAPE: calls, stores or branches differ"}[c["label"]]
    return "%s; instructions %d%% alike ignoring registers (%d vs %d)%s" % (
        head, round(100 * c["similarity"]), c["n"][0], c["n"][1], "".join("\n  - " + d for d in c["diffs"]))
