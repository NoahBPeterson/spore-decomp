#!/usr/bin/env python3
"""Register footprint of a hook versus its original: which registers each version writes.

usage: regfootprint.py <hybrid.exe> [--all] [va ...]

An LTCG-built caller may keep live values in registers its callee is known not to touch (a custom
convention the compiler proves per call site). A replacement that writes such a register corrupts
the caller silently; the equivalence harness compares outputs, not what stayed untouched. Rule:
the set of registers our function writes must be a subset of the original's (callee-saved registers
restored by pop are not counted; esp/eflags ignored; GPRs are reduced to their full register).
Prints one line per hook that violates it, with the extra registers; --all prints every hook.
"""
import json, os, struct, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import pefile                        # noqa: E402
import capstone                      # noqa: E402
from capstone import x86             # noqa: E402

BASE = 0x400000
IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

FULL = {}
for grp, names in {
    "eax": ("al", "ah", "ax", "eax"), "ebx": ("bl", "bh", "bx", "ebx"), "ecx": ("cl", "ch", "cx", "ecx"),
    "edx": ("dl", "dh", "dx", "edx"), "esi": ("sil", "si", "esi"), "edi": ("dil", "di", "edi"),
    "ebp": ("bp", "ebp"),
}.items():
    for n in names:
        FULL[n] = grp
IGNORE = {"esp", "eflags", "eip", "fpsw", "fs", "gs", "ds", "es", "ss", "cs"}


def file_off(pe, va):
    for s in pe.sections:
        lo = BASE + s.VirtualAddress
        hi = lo + max(s.Misc_VirtualSize, s.SizeOfRawData)
        if lo <= va < hi:
            return s.PointerToRawData + va - lo
    raise KeyError(hex(va))


def written(pe, va, size):
    """Registers written by the straight-line disassembly of [va, va+size) (all paths together);
    registers restored by `pop` before a ret are callee-saved and removed."""
    code = bytes(pe.__data__[file_off(pe, va): file_off(pe, va) + size])
    w, saved = set(), set()
    for i in md.disasm(code, va):
        _r, ws = i.regs_access()
        if i.mnemonic == "pop" and i.operands and i.operands[0].type == x86.X86_OP_REG:
            saved.add(FULL.get(i.reg_name(i.operands[0].reg), i.reg_name(i.operands[0].reg)))
        for r in ws:
            n = i.reg_name(r)
            if n in IGNORE:
                continue
            w.add(FULL.get(n, n))
    # x87 stack registers are reported as st(0)...; keep them as one class
    w = {("st" if r.startswith("st") else r) for r in w}
    return w - saved


def main():
    args = sys.argv[1:]
    show_all = "--all" in args
    args = [a for a in args if a != "--all"]
    exe = args[0]
    only = {int(a, 16) for a in args[1:]}
    pe = pefile.PE(exe)
    pe.__data__ = bytearray(pe.__data__)
    img = pefile.PE(IMAGE)
    img.__data__ = bytearray(img.__data__)
    hooks = json.load(open(exe + ".hooks.json"))["hooks"]
    # our function's size: up to the next hook entry in .hybx (entries are laid out in order)
    entries = sorted(int(h["entry"], 16) for h in hooks)
    nxt = {e: (entries[i + 1] if i + 1 < len(entries) else e + 0x2000) for i, e in enumerate(entries)}
    bad = 0
    for h in hooks:
        va, entry = int(h["va"], 16), int(h["entry"], 16)
        if only and va not in only:
            continue
        try:
            wo = written(img, va, h["orig_size"])
            wu = written(pe, entry, h.get("our_size") or min(nxt[entry] - entry, 0x4000))
        except Exception as e:  # noqa: BLE001
            print("%08x %s: %s" % (va, h["slice"], e))
            continue
        extra = sorted(wu - wo)
        if extra or show_all:
            bad += bool(extra)
            print("%08x %-10s extra=%-28s orig=%s ours=%s" % (va, h["slice"], ",".join(extra) or "-",
                                                             ",".join(sorted(wo)), ",".join(sorted(wu))))
    print("%d of %d hooks write registers the original does not" % (bad, len(hooks) if not only else len(only)))


if __name__ == "__main__":
    main()
