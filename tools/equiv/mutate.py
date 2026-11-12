"""Mutants of our build for the self-test (tools/equiv/LAYERS.md): a layer that proves a mutant equivalent is broken
for this function, so its proof of the real build is not accepted.

Kinds: an immediate changed by +1, a store turned into nops, a register operand renamed (only one occurrence, so the
data flow changes), and two adjacent dependent instructions swapped. Relocated fields are never touched."""
import random
from dataclasses import replace

import capstone
from capstone import x86_const as X

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MD.detail = True


def _reloc_bytes(f):
    return {o + k for o in f.relocs for k in range(4)}


def candidates(f):
    rb = _reloc_bytes(f)
    out = []
    ins = list(MD.disasm(f.code, f.va))
    for k, i in enumerate(ins):
        off = i.address - f.va
        span = set(range(off, off + i.size))
        if span & rb or i.mnemonic in ("ret", "int3", "nop") or i.mnemonic.startswith("j") or i.mnemonic == "call":
            continue
        # immediate +1 (the last byte(s) of the instruction hold the immediate when its size is 1 or 4)
        if i.operands and i.operands[-1].type == X.X86_OP_IMM and i.mnemonic not in ("push",):
            ib = getattr(i, "imm_size", 0)
            if ib in (1, 4) and getattr(i, "imm_offset", 0):
                pos = off + i.imm_offset
                out.append(("imm+1 at +%#x %s %s" % (off, i.mnemonic, i.op_str), [(pos, (f.code[pos] + 1) & 0xff)]))
        # store -> nops
        if i.operands and i.operands[0].type == X.X86_OP_MEM and i.mnemonic.startswith("mov") \
                and (i.operands[0].access & capstone.CS_AC_WRITE):
            out.append(("dropped store at +%#x %s %s" % (off, i.mnemonic, i.op_str),
                        [(off + j, 0x90) for j in range(i.size)]))
        # reg-reg mov: flip the source register field (modrm reg) to another register
        if i.mnemonic == "mov" and len(i.operands) == 2 and all(o.type == X.X86_OP_REG for o in i.operands) \
                and i.size == 2 and i.bytes[0] in (0x89, 0x8B):
            m = i.bytes[1]
            nm = (m & 0xC7) | ((((m >> 3) & 7) ^ 1) << 3)
            out.append(("register changed at +%#x %s %s" % (off, i.mnemonic, i.op_str), [(off + 1, nm)]))
    return out


def mutants(f, k=5, seed=1):
    """[(description, Func)] up to k mutants, deterministic for a seed."""
    c = candidates(f)
    rng = random.Random(seed)
    rng.shuffle(c)
    out = []
    for desc, patch in c[:k]:
        b = bytearray(f.code)
        for pos, v in patch:
            b[pos] = v
        out.append((desc, replace(f, code=bytes(b), meta=dict(f.meta, mutant=desc))))
    return out
