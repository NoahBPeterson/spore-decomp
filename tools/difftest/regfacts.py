"""Static register facts about a function's machine code, shared by the equivalence harness
(equiv.py) and the hybrid builder (tools/hybrid/build.py).

returns_eax(insns): the function hands a value back in eax although it may be declared void.
regs_written(insns): every register the function writes (full GPR names, xmmN, 'st'), minus the
    ones it restores with pop. A replacement must not write a register outside this set: an LTCG
    caller may keep a live value in a register its callee provably never touches (InterpRamp,
    0x114e780, wrote xmm3 where the original used xmm0-2/xmm7: crackling audio, 2026-10-12).

`insns` is a list of capstone instructions (detail on) in address order.
"""
import capstone
from capstone import x86

EAX = {x86.X86_REG_EAX, x86.X86_REG_AX, x86.X86_REG_AL, x86.X86_REG_AH}
FULL = {}
for _grp, _names in {"eax": ("al", "ah", "ax", "eax"), "ebx": ("bl", "bh", "bx", "ebx"),
                     "ecx": ("cl", "ch", "cx", "ecx"), "edx": ("dl", "dh", "dx", "edx"),
                     "esi": ("sil", "si", "esi"), "edi": ("dil", "di", "edi"), "ebp": ("bp", "ebp")}.items():
    for _n in _names:
        FULL[_n] = _grp
IGNORE = {"esp", "eflags", "eip", "fpsw", "fs", "gs", "ds", "es", "ss", "cs"}
GPR_SCRATCH = ("eax", "ecx", "edx")
XMM = tuple("xmm%d" % k for k in range(8))


def disasm(code, va):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return list(md.disasm(code, va))


def _writes_eax(i):
    try:
        _r, w = i.regs_access()
    except capstone.CsError:
        return False
    return any(r in EAX for r in w) and i.mnemonic not in ("push", "pop")


def returns_eax(ins):
    """True if the function returns a value in eax: every `ret` is preceded (ignoring pops / esp
    adds) by an eax write other than a call, in one of the shapes seen to matter, or the function
    is call-free and its first eax value is an argument/load it keeps (pop-front, lower_bound,
    copy -> end, init -> this)."""
    rets = [k for k, i in enumerate(ins) if i.mnemonic == "ret"]
    if not rets:
        return False
    if not any(i.mnemonic == "call" for i in ins):
        writers = [k for k, i in enumerate(ins) if _writes_eax(i)]
        if writers:
            first = ins[writers[0]]
            loads = first.mnemonic == "mov" and first.op_str.startswith("eax, dword ptr [")
            if (loads or first.op_str == "eax, ecx") and len(writers) == 1:
                return True
            if first.mnemonic == "mov" and (first.op_str.startswith(("eax, dword ptr [esp", "eax, dword ptr [ebp"))
                                            or first.op_str == "eax, ecx"):
                return True
    for k in rets:
        j = k - 1
        writer = None
        while j >= 0:
            i = ins[j]
            if i.mnemonic == "call":
                break
            if _writes_eax(i):
                writer = j
                break
            j -= 1
        if writer is None:
            return False
        between = ins[writer + 1:k]
        trailing = all(x.mnemonic in ("pop", "leave") or (x.mnemonic == "add" and x.op_str.startswith("esp"))
                       for x in between)
        w = ins[writer]
        retptr = w.mnemonic == "mov" and w.op_str.startswith("eax, dword ptr [esp") and \
            any(x.op_str.startswith("dword ptr [eax") for x in between if x.mnemonic == "mov")
        this_ret = w.mnemonic == "mov" and w.op_str == "eax, ecx"
        if not (trailing or retptr or this_ret):
            return False
    return True


def regs_written(ins):
    w, saved = set(), set()
    for i in ins:
        try:
            _r, ws = i.regs_access()
        except capstone.CsError:
            continue
        if i.mnemonic == "pop" and i.operands and i.operands[0].type == x86.X86_OP_REG:
            n = i.reg_name(i.operands[0].reg)
            saved.add(FULL.get(n, n))
        for r in ws:
            n = i.reg_name(r)
            if n not in IGNORE:
                w.add(FULL.get(n, n))
    return {("st" if r.startswith("st") else r) for r in w} - saved
