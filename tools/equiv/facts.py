"""Register facts a caller can depend on (tools/equiv/LAYERS.md, acceptance step 2).

kill set:    the volatile registers (eax, ecx, edx, xmm0-7) a function's code can write, through its own calls.
             A caller compiled with knowledge of the callee (same source file, or /LTCG) keeps a value in a register
             the callee does not write.
entry regs:  the registers read before being written on some path from entry (push of a callee-saved register
             and zero idioms like xor r, r are not reads). A function that reads one has a register argument.

Callee kill sets come from the retail image, transitively (memoized). An indirect call, an import, a function
without a fingerprint, or a recursion cycle counts as killing every volatile register.
"""
import capstone
from capstone import x86_const as X

from func import MD as _MD0, image  # noqa: F401

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MD.detail = True

VOLATILE = ["eax", "ecx", "edx"] + ["xmm%d" % k for k in range(8)]
ALL_VOL = frozenset(VOLATILE)
SAVED = {"ebx", "esi", "edi", "ebp"}
FAM = {}
for f, parts in (("eax", "al ah ax"), ("ecx", "cl ch cx"), ("edx", "dl dh dx"), ("ebx", "bl bh bx"),
                 ("esi", "si"), ("edi", "di"), ("ebp", "bp"), ("esp", "sp")):
    FAM[f] = f
    for p in parts.split():
        FAM[p] = f
for k in range(8):
    FAM["xmm%d" % k] = "xmm%d" % k
ZERO_IDIOM = ("xor", "sub", "pxor", "xorps", "xorpd")


def _regs(i):
    try:
        rd, wr = i.regs_access()
    except capstone.CsError:
        return set(), set()
    r = {FAM.get(i.reg_name(x)) for x in rd} - {None}
    w = {FAM.get(i.reg_name(x)) for x in wr} - {None}
    if i.mnemonic in ZERO_IDIOM and len(i.operands) == 2 and all(o.type == X.X86_OP_REG for o in i.operands) \
            and i.operands[0].reg == i.operands[1].reg:
        r -= {FAM.get(i.reg_name(i.operands[0].reg))}
    if i.mnemonic == "push" and i.operands and i.operands[0].type == X.X86_OP_REG \
            and FAM.get(i.reg_name(i.operands[0].reg)) in SAVED:
        r -= {FAM.get(i.reg_name(i.operands[0].reg))}      # saving a callee-saved register is not a use
    return r, w


def _call_target(i):
    """('direct', va) | ('indirect', None) | None"""
    if i.mnemonic == "call" or (i.mnemonic == "jmp" and i.operands and i.operands[0].type == X.X86_OP_IMM):
        op = i.operands[0]
        if op.type == X.X86_OP_IMM:
            return ("direct", op.imm & 0xffffffff)
        if i.mnemonic == "call":
            return ("indirect", None)
    return None


_kill_memo = {}


def retail_kill(va, _stack=None):
    """Kill set of the retail function at va (frozenset of volatile registers)."""
    if va in _kill_memo:
        return _kill_memo[va]
    _stack = _stack or set()
    if va in _stack:
        return ALL_VOL
    import task
    fp = task.fingerprint(va)
    if not fp:
        return ALL_VOL
    pe = image()
    code = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, fp["size"])
    out = set()
    _stack = _stack | {va}
    for i in MD.disasm(code, va):
        _, w = _regs(i)
        out |= w & ALL_VOL
        t = _call_target(i)
        if t:
            if t[0] == "indirect":
                out = set(ALL_VOL)
                break
            if not va <= t[1] < va + fp["size"]:
                out |= retail_kill(t[1], _stack)
        if len(out) == len(ALL_VOL):
            break
    res = frozenset(out)
    _kill_memo[va] = res
    return res


def calls(f):
    """[(offset, ('direct', target) | ('indirect', None) | ('sym', name))] in address order. A direct call of an
    object file's function has a relocation token naming the callee."""
    out = []
    for i in MD.disasm(f.code, f.va):
        t = _call_target(i)
        if not t:
            continue
        off = i.address - f.va
        tok = f.relocs.get(off + i.size - 4)
        if t[0] == "direct" and tok is not None:
            if tok[0] == "sym":
                t = ("sym", tok[1])
            elif f.va <= t[1] < f.va + len(f.code):
                continue
            else:
                t = ("direct", tok[1])
        elif t[0] == "direct" and f.va <= t[1] < f.va + len(f.code):
            continue                                   # a jump inside the function
        out.append((off, t))
    return out


def own_writes(f):
    out = set()
    for i in MD.disasm(f.code, f.va):
        out |= _regs(i)[1] & ALL_VOL
    return out


def entry_regs(f):
    """Registers read before written on some path from entry (must-defined analysis over the CFG)."""
    ins = list(MD.disasm(f.code, f.va))
    if not ins:
        return set()
    idx = {i.address: k for k, i in enumerate(ins)}
    succ = {}
    for k, i in enumerate(ins):
        s = []
        m = i.mnemonic
        nxt = ins[k + 1].address if k + 1 < len(ins) else None
        tgt = None
        if m.startswith("j") and i.operands and i.operands[0].type == X.X86_OP_IMM:
            tgt = i.operands[0].imm & 0xffffffff
        if m == "jmp":
            s = [tgt] if tgt in idx else []
        elif m.startswith("j"):
            s = ([tgt] if tgt in idx else []) + ([nxt] if nxt is not None else [])
        elif m.startswith("ret") or m == "int3":
            s = []
        else:
            s = [nxt] if nxt is not None else []
        succ[k] = [idx[a] for a in s if a in idx]
    allregs = {"eax", "ecx", "edx", "ebx", "esi", "edi", "ebp"} | {"xmm%d" % k for k in range(8)}
    defined = {0: frozenset()}
    work = [0]
    reads = set()
    while work:
        k = work.pop()
        d = defined[k]
        i = ins[k]
        r, w = _regs(i)
        reads |= (r & allregs) - d
        if i.mnemonic == "call":
            w = w | ALL_VOL                          # the callee's results are defined after the call
        nd = d | (w & allregs)
        for s in succ[k]:
            old = defined.get(s)
            new = nd if old is None else (old & nd)
            if old is None or new != old:
                defined[s] = frozenset(new)
                work.append(s)
    return reads


def facts(f, retail_side=None):
    """{'kill': sorted, 'entry': sorted, 'calls': n}. For our side, pass the retail Func: our k-th call is the
    retail k-th call (same order), so the callee kill sets come from the retail targets."""
    cs = calls(f)
    kill = set(own_writes(f))
    ref = calls(retail_side) if retail_side is not None else cs
    if len(ref) != len(cs):
        kill = set(ALL_VOL)
    else:
        for _off, t in ref:
            kill |= retail_kill(t[1]) if t[0] == "direct" else ALL_VOL
    return {"kill": sorted(kill), "entry": sorted(entry_regs(f)), "calls": len(cs)}


def same(retail, ours):
    """(True, facts) when ours can stand in for retail in every caller that knows its register use."""
    a = facts(retail)
    b = facts(ours, retail)
    if a["calls"] != b["calls"]:
        return False, "retail makes %d calls, ours %d" % (a["calls"], b["calls"]), a
    if a["kill"] != b["kill"]:
        return False, "kill set differs: retail %s, ours %s" % (a["kill"], b["kill"]), a
    if a["entry"] != b["entry"]:
        return False, "entry registers differ: retail %s, ours %s" % (a["entry"], b["entry"]), a
    return True, "", a


def std_call_safe(target_va):
    """A call may be modelled with the standard convention (callee reads its arguments, writes eax/ecx/edx) only
    when the callee really kills eax, ecx and edx; otherwise a caller may keep a value in one of them across it."""
    return {"eax", "ecx", "edx"} <= retail_kill(target_va)
