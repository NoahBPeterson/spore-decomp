#!/usr/bin/env python3
"""Equivalence layer: symbolic execution of both functions with angr, compared with Z3 (tools/equiv/LAYERS.md).

Install (once): angr lives in its own venv, so the project venv keeps its own capstone/pefile versions:

    python3 -m venv work/angr-venv && work/angr-venv/bin/pip install angr==10.0.6 pefile capstone
    (Windows: py -3 -m venv work\\angr-venv && work\\angr-venv\\Scripts\\pip install angr==10.0.6 pefile capstone)

`prove()` runs in any interpreter (it needs only capstone and, for retail callee facts, the analysis image); the
solving runs in a child process of the angr interpreter: $EQUIV_ANGR_PYTHON, else work/angr-venv, else the current
interpreter when it can import angr. The child is killed at `timeout` (its whole process group), and it never
starts processes of its own.

Model (one machine state, shared by both versions):
- Inputs: every GPR and the flags are symbols; esp is symbolic with the ABI preconditions 0x10000 <= esp <= 0x7fff0000
  and esp % 4 == 0; DF = 0; x87 stack empty (ftop 0, tags 0), rounding modes round-to-nearest.
- Memory is an uninterpreted array M0 (byte-addressed, Z3 array theory), written through a per-path write log;
  pointers may alias anything, including the live stack. One assumption (the compiler makes it too, whenever it
  moves a push across a load): an address computed from the entry state alone never points into the unallocated
  stack within 1 MB below the entry esp. Memory below esp is dead at calls and returns and is not compared.
- Relocated fields: ours is placed at the retail VA, and each of its relocated fields is rewritten to the retail
  address it is paired with by one consistent bijection (proposed by aligning the relocation-bearing instructions,
  or taken from hints; the same trust the byte-match check places in relocations).
- Calls are events. A callee is unknown code, identical in both versions: its outputs are fresh symbols named by
  the call's index on the path (shared by the two versions), which is sound because the call's inputs are proved
  equal first. L1 inputs: esp, the argument registers its decorated name implies (eax/ecx/edx when unknown), DF,
  the x87 stack, and memory at and above esp except the caller's private frame (saved registers; locals beyond the
  argument window when the window is known and no frame address escaped). L2 inputs: every register and all
  memory at and above esp. Outputs: eax/ecx/edx/flags/xmm/x87 registers (L2: every GPR but esp) and memory outside
  the caller's private frame. esp after the call = esp + 4 + ret N (from the retail callee's `ret N`, else a shared
  symbol in {0, 4, .., 64}); a callee without any reachable `ret` is noreturn and ends the path.
- Counterexamples are reported as "refuted" only when they do not rest on a guess: a heuristic relocation
  pairing, a register read only because an unknown callee's convention might read it, a difference inside the
  caller's own frame at an L1 call, x87 precision, or given hints all make the result "unknown" instead.
- Paths: each version is explored separately (angr, VEX semantics). Paths are paired by their branch-decision bit
  strings, a pairing is used only after its path conditions are proved equal; unpaired paths are compared with
  every path of the other version whose condition overlaps. A pair is equivalent when no input in the overlap
  makes any observable differ: event sequence, call targets and inputs, return target, registers of the level,
  esp, DF, memory.
- Loops (back edges of the static CFG, and rep-prefixed instructions): explored up to N visits of the head. A state
  that arrives once more is accepted only if it provably never leaves the loop: one generic iteration's exit
  conditions depend only on a register set U that the iteration maps to itself, the state's U values are a fixed
  point, no exit is feasible from it and the body writes no memory (then it diverges, and is compared as a path
  ending in `diverge`). N doubles from 2 to 64 until every such state diverges; otherwise the result is unknown.
- x87 arithmetic is modelled with 64-bit doubles (VEX); a proof or refutation is kept only when both versions run
  the same sequence of x87 instructions (mnemonic and memory size), else the result is unknown.

Hints (small, no instructions or values): {"v": 1, "bij": [[retail field offset, ours field offset], ...],
"loops": {"retail"|"ours": {"<head offset hex>": [N, reason]}}, "pairs": [[retail bits, ours bits], ...] for paths
not paired with the same bit string, "fallback": [retail bits, ...]}. Given hints are only checked; a wrong one
gives "unknown" (never trusted).

    angr_layer.py VA [--level L1|L2] [--timeout S] [--hints FILE] [--save-hints FILE]
"""
import json, os, re, struct, subprocess, sys, time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
ANGR_VERSION = "10.0.6"
MAX_BOUND = 64
GPR = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]
CALLEE_SAVED = ["ebx", "esi", "edi", "ebp"]
XMM = ["xmm%d" % k for k in range(8)]


# ====================================================================== shared helpers (no angr)
def _md(detail=False):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = detail
    return md


def decode(code, base):
    """[(capstone insn)] for linear disassembly (MSVC code has no embedded data before the end)."""
    return list(_md(True).disasm(code, base))


def _imm_target(i):
    try:
        return int(i.op_str, 16) if re.fullmatch(r"0x[0-9a-f]+", i.op_str) else None
    except ValueError:
        return None


def classify(code, base):
    """Static facts of one function: {addr: kind} for call/ret/tail/ijmp/trap, branch targets, loop heads."""
    ins = decode(code, base)
    end = base + len(code)
    by = {i.address: i for i in ins}
    kinds, succ = {}, {}
    for i in ins:
        m, a = i.mnemonic, i.address
        fall = a + i.size
        t = _imm_target(i)
        if m == "call":
            kinds[a] = "call"
            succ[a] = [fall]
        elif m in ("ret", "retn"):
            kinds[a] = "ret"
            succ[a] = []
        elif m == "jmp":
            if t is None:
                kinds[a] = "ijmp"
                succ[a] = []
            elif base <= t < end:
                succ[a] = [t]
            else:
                kinds[a] = "tail"
                succ[a] = []
        elif m.startswith("j") or m.startswith("loop"):
            if t is not None and not (base <= t < end):
                kinds[a] = "tailcc"
            succ[a] = [fall] + ([t] if t is not None and base <= t < end else [])
        elif m in ("int3", "ud2", "hlt", "int"):
            kinds[a] = "trap"
            succ[a] = []
        else:
            succ[a] = [fall]
        if m.startswith(("rep ", "repe ", "repne ", "repz ", "repnz ")):
            kinds.setdefault(a, "rep")
    # loop heads: targets of back edges in a DFS from the entry
    heads, color = set(), {}
    stack = [(base, iter(succ.get(base, [])))]
    color[base] = 1
    while stack:
        a, it = stack[-1]
        nxt = next(it, None)
        if nxt is None:
            color[a] = 2
            stack.pop()
            continue
        if nxt not in by:
            continue
        c = color.get(nxt, 0)
        if c == 1:
            heads.add(nxt)
        elif c == 0:
            color[nxt] = 1
            stack.append((nxt, iter(succ.get(nxt, []))))
    reach = {a for a, c in color.items() if c}
    for a, k in kinds.items():
        if k == "rep" and a in reach:
            heads.add(a)
    return {"ins": ins, "kinds": kinds, "succ": succ, "heads": heads, "reach": reach}


def loop_body(info, head):
    """instructions of the natural loop of head: reachable from head (not through head) and reaching head"""
    succ = info["succ"]
    fwd, todo = set(), [head]
    while todo:
        a = todo.pop()
        for b in succ.get(a, []):
            if b != head and b not in fwd and b in succ:
                fwd.add(b)
                todo.append(b)
    pred = {}
    for a, bs in succ.items():
        for b in bs:
            pred.setdefault(b, []).append(a)
    back, todo = set(), [head]
    while todo:
        a = todo.pop()
        for b in pred.get(a, []):
            if b != head and b not in back:
                back.add(b)
                todo.append(b)
    return {head} | (fwd & back)


def x87_signature(code, base):
    """Ordered x87 operations (mnemonic + memory operand size): rounding points of the 80-bit unit."""
    out = []
    for i in decode(code, base):
        if i.mnemonic.startswith("f") and i.mnemonic not in ("fwait",):
            sz = re.search(r"(byte|word|dword|qword|tbyte|xword) ptr", i.op_str)
            out.append(i.mnemonic + (":" + sz.group(1) if sz else ""))
    return out


# ---------------------------------------------------------------------- decorated names (MSVC)
_SIMPLE = {c: 4 for c in "CDEFGHIJK"}
_SIMPLE.update({"M": 4, "N": 8, "O": 8})
_UNDER = {"N": 4, "J": 8, "K": 8, "W": 4, "D": 4, "E": 4, "F": 4, "G": 4, "H": 4, "I": 4}


class _Mangled:
    def __init__(self, s, i):
        self.s, self.i, self.back = s, i, []

    def peek(self, n=1):
        return self.s[self.i:self.i + n]

    def take(self, n=1):
        r = self.s[self.i:self.i + n]
        self.i += n
        return r

    def name_frags(self):
        """skip a qualified name 'a@b@@' (no templates)"""
        while True:
            c = self.peek()
            if c == "":
                raise ValueError
            if c == "@":
                self.take()
                return
            if c.isdigit():
                self.take()
                continue
            if c == "?":
                raise ValueError("template or special name")
            j = self.s.index("@", self.i)
            self.i = j + 1

    def type(self):
        """size in bytes of one type (pass-by-value), None when unknown; advances past it"""
        start = self.i
        c = self.take()
        if c == "":
            raise ValueError
        if c in _SIMPLE:
            return _SIMPLE[c]
        if c == "X":
            return 0
        if c == "_":
            d = self.take()
            if d not in _UNDER:
                raise ValueError
            sz = _UNDER[d]
        elif c in "PQRSAB":
            q = self.take()
            if q == "E":
                q = self.take()
            if q == "6":                                  # function pointer
                self.take()                               # calling convention
                self.type()
                self.params()
                self.take() if self.peek() == "Z" else None
            else:
                self.type()
            sz = 4
        elif c in "VUT":
            self.name_frags()
            sz = None
        elif c == "W":
            self.take()
            self.name_frags()
            sz = 4
        elif c.isdigit():
            return self.back[int(c)] if int(c) < len(self.back) else None
        else:
            raise ValueError("type %r" % c)
        if self.i - start > 1 and len(self.back) < 10:
            self.back.append(sz)
        return sz

    def params(self):
        """[sizes] of the parameter list, or 'varargs'"""
        if self.peek() == "X":
            self.take()
            return []
        out = []
        while True:
            c = self.peek()
            if c == "@":
                self.take()
                return out
            if c == "Z":
                self.take()
                return "varargs"
            if c == "":
                raise ValueError
            out.append(self.type())


def name_facts(nm):
    """Facts a decorated name gives: reads (argument registers), W (stack argument bytes), ret64, fret (float
    return), conv. Missing keys are unknown."""
    if not nm:
        return {}
    if nm.startswith("__imp_"):
        nm = nm[6:]
    f = {}
    if nm.startswith(("__chkstk", "__alloca_probe")):
        return {"chkstk": True, "reads": ["eax"]}
    if nm.startswith(("__ftol2", "__ftol")):
        return {"reads": [], "W": 0, "fdelta": 1, "ret64": True}
    m = re.fullmatch(r"_([A-Za-z0-9_$]+)@(\d+)", nm)
    if m:
        return {"reads": [], "W": int(m.group(2)), "conv": "stdcall"}
    m = re.fullmatch(r"@([A-Za-z0-9_$]+)@(\d+)", nm)
    if m:
        return {"reads": ["ecx", "edx"], "conv": "fastcall"}
    if nm.startswith("_") and "@" not in nm:
        return {"reads": [], "conv": "cdecl"}
    if not nm.startswith("?"):
        return {}
    m = re.search(r"@@(?:[QRUVABEFIJMN]([A-D])|([CDKLSTYZ]))([AEGI])", nm)
    if not m:
        return {}
    conv = {"A": "cdecl", "E": "thiscall", "G": "stdcall", "I": "fastcall"}[m.group(3)]
    f["conv"] = conv
    f["reads"] = {"cdecl": [], "thiscall": ["ecx"], "stdcall": [], "fastcall": ["ecx", "edx"]}[conv]
    p = _Mangled(nm, m.end())
    try:
        if p.peek() == "?":                               # return type cv-qualifier for class returns
            p.take(2)
        rt = p.peek(2)
        f["ret64"] = rt in ("_J", "_K")
        f["fret"] = rt[:1] in ("M", "N", "O")
        if p.peek() == "@":                               # constructors/destructors have no return type
            p.take()
        else:
            p.type()
        ps = p.params()
        if ps != "varargs" and all(x is not None for x in ps):
            if conv == "fastcall":
                regs, W = 0, 0
                for x in ps:
                    if x <= 4 and regs < 2:
                        regs += 1
                    else:
                        W += (x + 3) & ~3
                f["W"] = W
            else:
                f["W"] = sum((x + 3) & ~3 for x in ps)
    except (ValueError, IndexError):
        pass
    return f


# ====================================================================== parent side
def _angr_python():
    env = os.environ.get("EQUIV_ANGR_PYTHON")
    if env:
        return env
    for p in (os.path.join(ROOT, "work", "angr-venv", "bin", "python"),
              os.path.join(ROOT, "work", "angr-venv", "Scripts", "python.exe")):
        if os.path.exists(p):
            return p
    try:
        import importlib.util
        if importlib.util.find_spec("angr"):
            return sys.executable
    except Exception:
        pass
    return None


def _tok_key(tok):
    """A token as a hashable key and (name, addend) when it has a symbol name."""
    if tok[0] == "abs":
        return ("abs", tok[1]), None
    _, nm, typ, addend = tok
    addend = addend if addend < 0x80000000 else addend - (1 << 32)
    return ("sym", nm, addend), (nm, addend)


def _reloc_shapes(code, base, relocs):
    """[(field offset, shape)] in code order; shape abstracts registers, keeps mnemonic and operand role."""
    out = []
    for i in decode(code, base):
        o0, o1 = i.address - base, i.address - base + i.size
        for o in sorted(relocs):
            if o0 <= o < o1:
                ops = re.sub(r"\b(e?[abcd]x|[abcd][lh]|e?[sd]i|e?bp|e?sp|xmm\d)\b", "R", i.op_str)
                ops = re.sub(r"0x[0-9a-f]+", "K", ops)
                out.append((o, "%s %s @%d" % (i.mnemonic, ops, o - o0)))
    return out


def propose_bijection(retail, ours):
    """[(retail field offset, ours field offset)], clean: an alignment of the relocation-bearing instructions."""
    import difflib
    ra = _reloc_shapes(retail.code, retail.va, retail.relocs)
    ob = _reloc_shapes(ours.code, ours.va, ours.relocs)
    sm = difflib.SequenceMatcher(None, [s for _, s in ra], [s for _, s in ob], autojunk=False)
    pairs, clean = [], True
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            pairs += [(ra[i1 + k][0], ob[j1 + k][0], True) for k in range(i2 - i1)]
        else:
            clean = False
            if tag == "replace":
                for k in range(min(i2 - i1, j2 - j1)):
                    if ra[i1 + k][1].split()[0] == ob[j1 + k][1].split()[0]:
                        pairs.append((ra[i1 + k][0], ob[j1 + k][0], False))
    return [(a, b) for a, b, _ in pairs], clean


def build_mapping(retail, ours, pairs):
    """ours key -> retail address, checked: one-to-one, and one base per symbol name. -> (map, problems)"""
    m, inv, base, problems = {}, {}, {}, []
    for ro, oo in pairs:
        if ro not in retail.relocs or oo not in ours.relocs:
            problems.append("pair (%x, %x) is not a relocated field" % (ro, oo))
            continue
        x = retail.relocs[ro][1]
        k, nmad = _tok_key(ours.relocs[oo])
        if k in m and m[k] != x or x in inv and inv[x] != k:
            problems.append("inconsistent pairing at retail +%x / ours +%x" % (ro, oo))
            continue
        if nmad:
            b = (x - nmad[1]) & 0xffffffff
            if base.setdefault(nmad[0], b) != b:
                problems.append("symbol %s paired with two bases" % nmad[0])
                continue
        m[k], inv[x] = x, k
    for oo, tok in ours.relocs.items():               # same symbol, other addend: its base is known
        k, nmad = _tok_key(tok)
        if k not in m and nmad and nmad[0] in base:
            x = (base[nmad[0]] + nmad[1]) & 0xffffffff
            if x not in inv:
                m[k], inv[x] = x, k
    return m, problems


def _rel32_fields(code, base):
    out = {}
    for i in decode(code, base):
        b = i.bytes
        if (b[0] in (0xE8, 0xE9) and i.size == 5) or (b[0] == 0x0F and 0x80 <= b[1] <= 0x8F and i.size == 6):
            out[i.address - base + i.size - 4] = i.address + i.size
    return out


def patch_ours(retail, ours, mapping):
    """ours' bytes placed at the retail VA, with every relocated field rewritten to its paired retail address
    (an unpaired one gets a fresh address that nothing in retail uses). -> (code, unpaired count, names by addr)"""
    code = bytearray(ours.code)
    rel32 = _rel32_fields(ours.code, ours.va)
    fresh, unpaired, names = 0x7ff00000, 0, {}
    used = {t[1] for t in retail.relocs.values()}
    for o, tok in sorted(ours.relocs.items()):
        k, nmad = _tok_key(tok)
        if k in mapping:
            x = mapping[k]
        else:
            while fresh in used:
                fresh += 0x1000
            x, unpaired = fresh, unpaired + 1
            mapping[k] = x
            used.add(x)
        if nmad:
            names[x] = nmad[0]
        if o in rel32:
            struct.pack_into("<i", code, o, ((x - (retail.va + o + 4) + 0x80000000) & 0xffffffff) - 0x80000000)
        else:
            struct.pack_into("<I", code, o, x)
    return bytes(code), unpaired, names


def _dll_names(ours):
    """{address in the DLL: decorated name} from the /LTCG link map next to the DLL"""
    dll = ours.meta.get("dll") if ours.meta else None
    if not dll:
        return {}
    mp = os.path.join(os.path.dirname(dll), "ltcg.map")
    if not os.path.exists(mp):
        return {}
    out = {}
    for line in open(mp, encoding="latin-1"):
        mm = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+f\s", line)
        if mm:
            out.setdefault(int(mm.group(2), 16), mm.group(1))
    return out


def scan_callee(va, budget=4000):
    """Retail callee facts from the analysis image: {'retn': N} when every reachable ret pops N, 'noreturn' when
    the reachable code (direct jumps followed, calls not entered) has no ret and no indirect jump."""
    try:
        sys.path.insert(0, HERE)
        import func as FN
        pe = FN.image()
    except BaseException:
        return {}
    ib = pe.OPTIONAL_HEADER.ImageBase
    md = _md()
    seen, todo, rets, opaque = set(), [va], set(), False
    while todo and len(seen) < budget:
        a = todo.pop()
        while a not in seen and len(seen) < budget:
            seen.add(a)
            try:
                b = pe.get_data(a - ib, 16)
            except Exception:
                opaque = True
                break
            i = next(md.disasm(b, a), None)
            if i is None:
                opaque = True
                break
            m = i.mnemonic
            if m in ("ret", "retn"):
                rets.add(int(i.op_str, 16) if i.op_str else 0)
                break
            if m in ("int3", "ud2", "hlt"):
                break
            t = _imm_target(i)
            if m == "jmp":
                if t is None:
                    opaque = True
                else:
                    todo.append(t)
                break
            if m.startswith("j") and m != "jmp":
                if t is not None:
                    todo.append(t)
            a = i.address + i.size
    if todo:
        opaque = True
    out = {}
    if len(rets) == 1:
        out["retn"] = rets.pop()
    elif not rets and not opaque:
        out["noreturn"] = True
    return out


def _call_sites(code, base):
    """{call instruction offset: ('direct', target) | ('mem', disp32) | ('other', None)}"""
    out = {}
    for i in decode(code, base):
        if i.mnemonic in ("call", "jmp") or (i.mnemonic.startswith("j") and _imm_target(i) is not None):
            t = _imm_target(i)
            if t is not None:
                out[i.address - base] = ("direct", t)
            else:
                mm = re.fullmatch(r"dword ptr \[(0x[0-9a-f]+)\]", i.op_str)
                out[i.address - base] = ("mem", int(mm.group(1), 16)) if mm else ("other", None)
    return out


def prepare(retail, ours, level, hints):
    """Everything the worker needs, as JSON-able data, plus notes for the detail line."""
    notes = []
    if hints and "bij" in hints:
        pairs, clean = [tuple(p) for p in hints["bij"]], True
    else:
        pairs, clean = propose_bijection(retail, ours)
    mapping, problems = build_mapping(retail, ours, pairs)
    if problems:
        if hints and "bij" in hints:
            raise HintError("hint bijection rejected: " + "; ".join(problems[:3]))
        clean = False
        notes += problems[:3]
    pcode, unpaired, oname = patch_ours(retail, ours, mapping)
    if unpaired:
        clean = False
        notes.append("%d relocated field(s) of ours unpaired" % unpaired)
    dll = _dll_names(ours)
    inv = {}
    for k, x in mapping.items():
        if k[0] == "sym":
            inv.setdefault(x, k[1])
        elif k[1] in dll:
            inv.setdefault(x, dll[k[1]])
    # callee facts, keyed by retail target address (direct) or "m<addr>" (call [addr])
    facts = {}
    for side_code in (retail.code, pcode):
        for o, (kind, t) in _call_sites(side_code, retail.va).items():
            if kind == "other" or (kind == "direct" and retail.va <= t < retail.va + len(retail.code)):
                continue
            key = ("%x" % t) if kind == "direct" else ("m%x" % t)
            if key in facts:
                continue
            f = {}
            nm = inv.get(t) or oname.get(t)
            f.update(name_facts(nm))
            if kind == "direct":
                sc = scan_callee(t)
                if "retn" in sc:
                    f["retn"] = sc["retn"]
                    if f.get("conv") in ("stdcall", "thiscall") or (f.get("conv") is None and sc["retn"]):
                        f["W"] = sc["retn"] if f.get("conv") != "fastcall" else f.get("W")
                if sc.get("noreturn"):
                    f["noreturn"] = True
            elif nm:
                m = re.search(r"@(\d+)$", nm)
                if m and f.get("conv") == "stdcall":
                    f["retn"] = int(m.group(1))
            if f.get("conv") == "cdecl" and "retn" not in f:
                f["retn"] = 0
            f["name"] = nm or ""
            facts[key] = f
    own = name_facts(ours.meta.get("symbol") if ours.meta else ours.name) or name_facts(ours.name)
    ret64 = own.get("ret64", True) if own else True
    sa, sb = x87_signature(retail.code, retail.va), x87_signature(pcode, retail.va)
    job = {
        "level": level, "facts": facts, "ret64": ret64, "clean": clean,
        "x87": bool(sa or sb), "x87_same": sa == sb,
        "sides": {"retail": {"code": retail.code.hex(), "base": retail.va},
                  "ours": {"code": pcode.hex(), "base": retail.va}},
        "hints": hints or {}, "bij": [list(p) for p in pairs], "notes": notes,
    }
    return job


class HintError(Exception):
    pass


def prove(retail, ours, level, hints, timeout):
    """LAYERS.md API. Runs the solver in a child process (killed at `timeout`)."""
    t0 = time.time()
    res = lambda st, d, h=None: {"status": st, "seconds": round(time.time() - t0, 2), "detail": d,
                                 "hints": h or {}}
    if level not in ("L1", "L2"):
        return res("unknown", "level must be L1 or L2")
    py = _angr_python()
    if not py:
        return res("unknown", "angr is not installed (see tools/equiv/angr_layer.py docstring)")
    try:
        job = prepare(retail, ours, level, hints)
    except HintError as e:
        return res("unknown", str(e))
    except Exception as e:
        return res("unknown", "prepare failed: %s: %s" % (type(e).__name__, e))
    job["timeout"] = max(1.0, timeout - (time.time() - t0) - 1.0)
    kw = {}
    if os.name == "nt":
        kw["creationflags"] = subprocess.CREATE_NEW_PROCESS_GROUP
    else:
        kw["start_new_session"] = True
    env = dict(os.environ, PYTHONHASHSEED="0")
    p = subprocess.Popen([py, "-I", os.path.abspath(__file__), "--worker"], stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env, **kw)
    try:
        out, err = p.communicate(json.dumps(job).encode(), timeout=max(1.0, timeout - (time.time() - t0)))
    except subprocess.TimeoutExpired:
        _kill(p)
        return res("unknown", "timeout after %.0fs" % timeout)
    except BaseException:
        _kill(p)
        raise
    try:
        r = json.loads(out.decode().strip().splitlines()[-1])
    except Exception:
        return res("unknown", "worker failed: %s" % err.decode(errors="replace")[-600:])
    r["seconds"] = round(time.time() - t0, 2)
    if job["notes"]:
        r["detail"] = r.get("detail", "") + " [bijection: %s]" % "; ".join(job["notes"])
    return r


def _kill(p):
    try:
        if os.name == "nt":
            p.kill()
        else:
            import signal
            os.killpg(p.pid, signal.SIGKILL)
    except Exception:
        try:
            p.kill()
        except Exception:
            pass
    try:
        p.wait(5)
    except Exception:
        pass


# ====================================================================== worker side (angr + z3)
class Unsupported(Exception):
    pass


class GiveUp(Exception):
    pass


def worker_main():
    import logging
    logging.disable(logging.CRITICAL)
    job = json.loads(sys.stdin.read())
    t0 = time.time()
    try:
        r = Worker(job).run()
    except (Unsupported, GiveUp) as e:
        r = {"status": "unknown", "detail": str(e), "hints": {}}
    except Exception as e:
        import traceback
        r = {"status": "unknown", "detail": "error: %s: %s | %s" % (
            type(e).__name__, e, traceback.format_exc().strip().splitlines()[-3][:200]), "hints": {}}
    r["seconds"] = round(time.time() - t0, 2)
    sys.stdout.write(json.dumps(r) + "\n")
    sys.stdout.flush()


def _lin(x):
    """x as ({hash: (coef, term)}, const) over +, - and constants."""
    if x.concrete:
        return {}, x.concrete_value
    if x.op == "__add__":
        terms, k = {}, 0
        for a in x.args:
            t, c = _lin(a)
            k += c
            for h, (co, term) in t.items():
                terms[h] = (terms.get(h, (0, term))[0] + co, term)
        return terms, k
    if x.op == "__sub__" and len(x.args) == 2:
        t1, c1 = _lin(x.args[0])
        t2, c2 = _lin(x.args[1])
        for h, (co, term) in t2.items():
            t1[h] = (t1.get(h, (0, term))[0] - co, term)
        return t1, c1 - c2
    return {x.hash(): (1, x)}, 0


def same(a, b):
    """structurally equal ASTs (angr 10's AST.identical() ignores variable names: never use it)"""
    return a is b or a.hash() == b.hash()


def const_diff(x, a):
    t1, c1 = _lin(x)
    t2, c2 = _lin(a)
    for h, (co, term) in t2.items():
        t1[h] = (t1.get(h, (0, term))[0] - co, term)
    if any(co % (1 << 32) for co, _ in t1.values()):
        return None
    return (c1 - c2) % (1 << 32)


class Worker:
    def __init__(self, job):
        import angr
        from angr import claripy as C
        import z3
        self.angr, self.C, self.z3 = angr, C, z3
        self.job = job
        self.level = job["level"]
        self.deadline = time.time() + job["timeout"]
        self.facts = job["facts"]
        self.hints = job.get("hints") or {}
        self.base_syms = {}          # name -> (epoch, addr AST)
        self.base_by_key = {}
        self.assume = []             # claripy constraints that hold for every input (ABI, call facts)
        self.IN = {r: C.BVS("in_" + r, 32, explicit_name=True) for r in GPR}
        self.IN["flags"] = C.BVS("in_flags", 32, explicit_name=True)
        self.IN["fpreg"] = C.BVS("in_fpreg", 512, explicit_name=True)
        for x in XMM:
            self.IN[x] = C.BVS("in_" + x, 128, explicit_name=True)
        esp = self.IN["esp"]
        self.assume += [C.UGE(esp, 0x10000), C.ULE(esp, 0x7fff0000), (esp & 3) == 0]
        self.PROBE = C.BVS("x_probe", 32, explicit_name=True)
        self.zmemo = {}
        self.zarr = {}
        self.stats = {}
        self._proj = {}
        self.guessed = set()        # observables that exist only because a callee's convention is unknown

    # ------------------------------------------------------------------ memory
    def base_byte(self, epoch, addr):
        k = (epoch, addr.hash())
        s = self.base_by_key.get(k)
        if s is None:
            nm = "m%s_%d" % (epoch, len(self.base_syms))
            s = self.C.BVS(nm, 8, explicit_name=True)
            self.base_syms[nm] = (epoch, addr)
            self.base_by_key[k] = s
        return s

    def make_mem_plugin(self):
        W = self
        angr, C = self.angr, self.C

        class LogMem(angr.SimStatePlugin):
            SUPPORTS_CONCRETE_LOAD = True

            def __init__(self, log=(), epoch="0"):
                super().__init__()
                self.log = log
                self.epoch = epoch

            def concrete_load(self, addr, size, **kw):
                mem = self.state.project.loader.memory
                lo, hi = self.state.project.loader.min_addr, self.state.project.loader.max_addr + 1
                return mem.load(addr, min(size, hi - addr)) if lo <= addr < hi else b""

            @angr.SimStatePlugin.memo
            def copy(self, memo):
                return LogMem(self.log, self.epoch)

            def merge(self, *a, **k):
                return False

            def widen(self, *a, **k):
                return False

            @staticmethod
            def _bv(v, n=None):
                if isinstance(v, int):
                    return C.BVV(v, (n or 4) * 8)
                if isinstance(v, bytes):
                    return C.BVV(int.from_bytes(v, "big"), len(v) * 8)
                return v

            def store(self, addr, data, size=None, endness=None, condition=None, **kw):
                addr = self._bv(addr)
                W.note_addr(self.state, addr)
                if isinstance(size, int) and isinstance(data, int):
                    data = C.BVV(data, size * 8)
                data = self._bv(data)
                if type(data).__name__.startswith("FP"):
                    data = C.fpToIEEEBV(data)
                n = data.size() // 8
                if isinstance(size, int) and size < n:
                    data = data[size * 8 - 1:0] if endness != "Iend_BE" else data[n * 8 - 1:(n - size) * 8]
                    n = size
                if condition is not None and not (condition.concrete and condition.is_true()):
                    data = C.If(condition, data, self.load(addr, n, endness=endness))
                bs = [data.get_byte(n - 1 - k) for k in range(n)]
                if endness == "Iend_BE":
                    bs = bs[::-1]
                self.log = self.log + (("w", addr, tuple(bs)),)

            def load(self, addr, size=None, endness=None, condition=None, fallback=None, **kw):
                addr = self._bv(addr)
                W.note_addr(self.state, addr)
                n = size if isinstance(size, int) else size.concrete_value
                bs = [W.read_byte(addr + k, self.log, self.epoch) for k in range(n)]
                v = C.Concat(*(bs[::-1] if endness != "Iend_BE" else bs)) if n > 1 else bs[0]
                if condition is not None and fallback is not None:
                    v = C.If(condition, v, fallback)
                return v

        return LogMem

    def note_addr(self, st, addr):
        """dead-stack assumption: an address computed from the entry state alone (inputs other than esp, memory
        at entry, constants) never points into the unallocated stack below the entry esp (the compiler assumes the
        same when it moves pushes across loads). Kept per path, as part of its condition."""
        if st is None:
            return
        vs = addr.variables
        if "in_esp" in vs or not all(v.startswith(("in_", "m0_")) for v in vs):
            return
        C, e = self.C, self.IN["esp"]
        c = C.UGE(e - addr - 1, 0x100000)            # not in [esp - 1 MB, esp), modulo 2^32
        st.globals["dz"] = st.globals.get("dz", ()) + (c,)

    def read_byte(self, x, log, epoch="0"):
        C = self.C
        cur = self.base_byte(epoch, x)
        for ent in log:
            if ent[0] == "w":
                _, a, bs = ent
                d = const_diff(x, a)
                if d is not None:
                    if d < len(bs):
                        cur = bs[d]
                    continue
                off = x - a
                sel = cur
                for k in reversed(range(len(bs))):
                    sel = C.If(off == k, bs[k], sel)
                cur = sel if len(bs) == 1 else C.If(C.ULT(off, len(bs)), sel, cur)
            else:                               # ("havoc", epoch, protected ranges)
                _, ep, prot = ent
                inside = []
                decided_in = False
                for lo, hi in prot:
                    d, w = const_diff(x, lo), const_diff(hi, lo)
                    if d is not None and w is not None:
                        if d < w:
                            decided_in = True
                            break
                        continue
                    inside.append(C.ULT(x - lo, hi - lo))
                if decided_in:
                    continue
                fresh = self.base_byte(ep, x)
                cur = C.If(C.Or(*inside), cur, fresh) if inside else fresh
        return cur

    def read_word(self, x, log, n=4):
        bs = [self.read_byte(x + k, log) for k in range(n)]
        return self.C.Concat(*bs[::-1])

    # ------------------------------------------------------------------ z3
    def z(self, e, subst=None):
        """claripy AST -> z3 (base memory bytes become Select on per-epoch arrays)."""
        z3 = self.z3
        memo = self.zmemo if subst is None else {}
        stack = [e]
        while stack:
            x = stack[-1]
            h = x.hash()
            if h in memo:
                stack.pop()
                continue
            kids = [a for a in x.args if hasattr(a, "op") and hasattr(a, "hash")]
            if x.op == "BVS" and x.args[0] in self.base_syms:
                kids = [self.base_syms[x.args[0]][1]]
            elif x.op == "BVS" and subst and x.args[0] in subst:
                kids = [subst[x.args[0]]]
            pend = [k for k in kids if k.hash() not in memo]
            if pend:
                stack.extend(pend)
                continue
            stack.pop()
            memo[h] = self._z1(x, memo, subst)
        return memo[e.hash()]

    def _arr(self, epoch):
        z3 = self.z3
        if epoch not in self.zarr:
            self.zarr[epoch] = z3.Array("M" + str(epoch), z3.BitVecSort(32), z3.BitVecSort(8))
        return self.zarr[epoch]

    def _z1(self, x, memo, subst):
        z3 = self.z3
        op, args = x.op, x.args
        A = lambda k: memo[args[k].hash()]
        if op == "BVS":
            nm = args[0]
            if nm in self.base_syms:
                ep, addr = self.base_syms[nm]
                return z3.Select(self._arr(ep), memo[addr.hash()])
            if subst and nm in subst:
                return memo[subst[nm].hash()]
            return z3.BitVec(nm, x.size())
        if op == "BVV":
            return z3.BitVecVal(args[0], args[1])
        if op == "BoolV":
            return z3.BoolVal(args[0])
        if op == "BoolS":
            return z3.Bool(args[0])
        n = [memo[a.hash()] if hasattr(a, "hash") and a.hash() in memo else a for a in args]
        if op == "__add__":
            r = n[0]
            for v in n[1:]:
                r = r + v
            return r
        if op == "__sub__":
            return n[0] - n[1]
        if op == "__mul__":
            r = n[0]
            for v in n[1:]:
                r = r * v
            return r
        if op in ("__and__", "__or__", "__xor__"):
            f = {"__and__": lambda a, b: a & b, "__or__": lambda a, b: a | b, "__xor__": lambda a, b: a ^ b}[op]
            r = n[0]
            for v in n[1:]:
                r = f(r, v)
            return r
        simple = {
            "__invert__": lambda a: ~a, "__neg__": lambda a: -a,
            "__lshift__": lambda a, b: a << b, "__rshift__": lambda a, b: a >> b, "LShR": z3.LShR,
            "__floordiv__": z3.UDiv, "__mod__": z3.URem, "SDiv": lambda a, b: a / b, "SMod": z3.SRem,
            "__eq__": lambda a, b: a == b, "__ne__": lambda a, b: a != b,
            "ULT": z3.ULT, "ULE": z3.ULE, "UGT": z3.UGT, "UGE": z3.UGE,
            "__lt__": z3.ULT, "__le__": z3.ULE, "__gt__": z3.UGT, "__ge__": z3.UGE,
            "SLT": lambda a, b: a < b, "SLE": lambda a, b: a <= b, "SGT": lambda a, b: a > b,
            "SGE": lambda a, b: a >= b, "RotateLeft": z3.RotateLeft, "RotateRight": z3.RotateRight,
            "Not": z3.Not, "If": z3.If,
        }
        if op in simple:
            return simple[op](*n)
        if op == "And":
            return z3.And(*n)
        if op == "Or":
            return z3.Or(*n)
        if op == "Xor":
            return z3.Xor(*n)
        if op == "Concat":
            return z3.Concat(*n) if len(n) > 1 else n[0]
        if op == "Extract":
            return z3.Extract(n[0], n[1], n[2])
        if op == "ZeroExt":
            return z3.ZeroExt(n[0], n[1])
        if op == "SignExt":
            return z3.SignExt(n[0], n[1])
        if op == "Reverse":
            v = n[0]
            sz = v.size()
            return z3.Concat(*[z3.Extract(8 * k + 7, 8 * k, v) for k in range(sz // 8)]) if sz > 8 else v
        return self._zfp(x, op, n)

    def _zsort(self, s):
        z3 = self.z3
        nm = str(s)
        if "32" in nm or "FLOAT" in nm.upper() and "DOUBLE" not in nm.upper():
            return z3.Float32()
        return z3.Float64()

    def _zrm(self, rm):
        z3 = self.z3
        s = str(rm)
        for k, v in (("NearestTiesEven", z3.RNE()), ("NearestTiesAway", z3.RNA()), ("TowardsZero", z3.RTZ()),
                     ("TowardsPositive", z3.RTP()), ("TowardsNegative", z3.RTN())):
            if k in s:
                return v
        raise Unsupported("rounding mode %s" % s)

    def _hidden_rm(self, x):
        """the rounding mode of a conversion (angr 10 keeps it out of .args; smtlib() shows it)"""
        C = self.C
        k = x.args[0]
        leaf = C.FPS("_d", C.FSORT_FLOAT if k.size() == 32 else C.FSORT_DOUBLE) if type(k).__name__ == "FP" \
            else C.BVS("_d", k.size())
        txt = x.replace(k, leaf).smtlib()
        m = re.search(r"\b(RNE|RNA|RTZ|RTP|RTN)\b", txt)
        if not m:
            raise Unsupported("rounding mode of %s" % x.op)
        return {"RNE": self.z3.RNE, "RNA": self.z3.RNA, "RTZ": self.z3.RTZ, "RTP": self.z3.RTP,
                "RTN": self.z3.RTN}[m.group(1)]()

    def _zfp(self, x, op, n):
        z3 = self.z3
        isrm = lambda v: "RM" in type(v).__name__ or "RM_" in str(v)
        if op == "FPS":
            return z3.FP(n[0], self._zsort(n[1]))
        if op == "FPV":
            return z3.FPVal(n[0], self._zsort(n[1]))
        if op in ("fpAdd", "fpSub", "fpMul", "fpDiv"):
            a, b, rm = (n[0], n[1], n[2]) if isrm(n[2]) else (n[1], n[2], n[0])
            return {"fpAdd": z3.fpAdd, "fpSub": z3.fpSub, "fpMul": z3.fpMul, "fpDiv": z3.fpDiv}[op](
                self._zrm(rm), a, b)
        if op == "fpSqrt":
            a, rm = (n[0], n[1]) if isrm(n[1]) else (n[1], n[0])
            return z3.fpSqrt(self._zrm(rm), a)
        if op in ("fpNeg", "fpAbs"):
            return {"fpNeg": z3.fpNeg, "fpAbs": z3.fpAbs}[op](n[0])
        if op in ("fpEQ", "fpLT", "fpLEQ", "fpGT", "fpGEQ", "fpNE"):
            return {"fpEQ": z3.fpEQ, "fpLT": z3.fpLT, "fpLEQ": z3.fpLEQ, "fpGT": z3.fpGT, "fpGEQ": z3.fpGEQ,
                    "fpNE": z3.fpNEQ}[op](n[0], n[1])
        if op in ("fpIsNaN", "fpIsInf"):
            return {"fpIsNaN": z3.fpIsNaN, "fpIsInf": z3.fpIsInf}[op](n[0])
        if op in ("fpMin", "fpMax"):
            return {"fpMin": z3.fpMin, "fpMax": z3.fpMax}[op](n[0], n[1])
        if op == "fpToIEEEBV":
            return z3.fpToIEEEBV(n[0])
        if op == "bvToFP":
            return z3.fpBVToFP(n[0], z3.Float32() if x.size() == 32 else z3.Float64())
        if op in ("fpToFp", "fpToFP", "fpToFPSigned", "fpToFPUnsigned", "fpToSBV", "fpToUBV"):
            rm = self._hidden_rm(x)
            v = n[0]
            if op in ("fpToSBV", "fpToUBV"):
                return (z3.fpToSBV if op == "fpToSBV" else z3.fpToUBV)(rm, v, z3.BitVecSort(x.size()))
            srt = z3.Float32() if x.size() == 32 else z3.Float64()
            if op == "fpToFPSigned":
                return z3.fpSignedToFP(rm, v, srt)
            if op == "fpToFPUnsigned":
                return z3.fpUnsignedToFP(rm, v, srt)
            return z3.fpFPToFP(rm, v, srt)
        if op == "fpFP":
            return z3.fpFP(n[0], n[1], n[2])
        raise Unsupported("claripy op %s" % op)

    def solver(self):
        s = self.z3.Solver()
        for a in self.assume:
            s.add(self.z(a))
        return s

    def check(self, s, *extra):
        rem = self.deadline - time.time()
        if rem < 0.5:
            raise GiveUp("timeout (solver)")
        s.set("timeout", int(min(rem, 600) * 1000))
        r = s.check(*extra)
        self.stats["queries"] = self.stats.get("queries", 0) + 1
        if r == self.z3.unknown:
            raise GiveUp("solver returned unknown (%s)" % s.reason_unknown())
        return r == self.z3.sat

    def pc(self, st):
        cs = list(st.solver.constraints) + list(st.globals.get("dz", ()))
        return self.C.And(*cs) if cs else self.C.true()

    # ------------------------------------------------------------------ exploration
    def project(self, side):
        if side in self._proj:
            return self._proj[side]
        sd = self.job["sides"][side]
        code = bytes.fromhex(sd["code"])
        base = sd["base"]
        proj = self.angr.load_shellcode(code, arch="x86", start_offset=0, load_address=base)
        info = classify(code, base)
        info["code"], info["base"], info["end"] = code, base, base + len(code)
        info["by"] = {i.address: i for i in info["ins"]}
        self._proj[side] = (proj, info)
        return proj, info

    def entry_state(self, proj, info):
        angr, C = self.angr, self.C
        st = proj.factory.blank_state(addr=info["base"], remove_options={angr.options.UNICORN} |
                                      angr.options.simplification)
        st.register_plugin("memory", self.make_mem_plugin()())
        for r in GPR:
            setattr(st.regs, r, self.IN[r])
        st.regs.cc_op, st.regs.cc_dep1, st.regs.cc_dep2, st.regs.cc_ndep = 0, self.IN["flags"], 0, 0
        st.regs.d = 1
        st.regs.ftop = 0
        st.regs.fptag = 0
        st.regs.fpreg = self.IN["fpreg"]
        st.regs.fpround = 0
        st.regs.sseround = 0
        for x in XMM:
            setattr(st.regs, x, self.IN[x])
        st.globals["events"] = ()
        st.globals["br"] = ""
        st.globals["visits"] = ()
        st.globals["escaped"] = False
        return st

    def snapshot(self, s):
        g = {r: getattr(s.regs, r) for r in GPR}
        g["eflags"] = s.regs.eflags
        g["d"] = s.regs.d
        g["ftop"] = s.regs.ftop
        g["fptag"] = s.regs.fptag
        g["fpreg"] = s.regs.fpreg
        for x in XMM:
            g[x] = getattr(s.regs, x)
        return g

    def stop_len(self, info, a):
        """instructions to execute from a before reaching a special instruction or a loop head"""
        n, x = 0, a
        while True:
            i = info["by"].get(x)
            if i is None:
                return max(n, 1)
            if n and (x in info["kinds"] or x in info["heads"]):
                return n
            n += 1
            if x in info["kinds"]:
                return n
            m = i.mnemonic
            if m.startswith("j") or m.startswith("loop") or m in ("ret", "call"):
                return n
            x = i.address + i.size

    def last_ins(self, info, a, k):
        x, i = a, None
        for _ in range(k):
            i = info["by"].get(x)
            if i is None:
                return None
            m = i.mnemonic
            if m.startswith("j") or m.startswith("loop"):
                return i
            x = i.address + i.size
        return i

    def callee(self, info, i):
        """(target AST, facts) of a call/jmp instruction"""
        C = self.C
        t = _imm_target(i)
        if t is not None:
            return C.BVV(t, 32), dict(self.facts.get("%x" % t, {})), "%x" % t
        return None, None, None

    def operand_target(self, s, i):
        """evaluate the register/memory operand of an indirect call/jmp"""
        from capstone import x86_const as X
        op = i.operands[0]
        if op.type == X.X86_OP_REG:
            return getattr(s.regs, i.reg_name(op.reg))
        if op.type == X.X86_OP_MEM:
            m = op.mem
            if m.segment != 0:
                raise Unsupported("segment-relative call at %x" % i.address)
            a = self.C.BVV(m.disp & 0xffffffff, 32)
            if m.base:
                a = a + getattr(s.regs, i.reg_name(m.base))
            if m.index:
                a = a + getattr(s.regs, i.reg_name(m.index)) * m.scale
            return s.memory.load(a, 4, endness="Iend_LE")
        raise Unsupported("call operand at %x" % i.address)

    def private_ranges(self, s, esp_ev, W):
        """the caller's frame a callee may not touch: [esp+4+W, in_esp+4) when W is known and nothing escaped;
        else the saved-register slots and the return address."""
        C, inesp = self.C, self.IN["esp"]
        saved = []
        for ent in s.memory.log:
            if ent[0] != "w":
                continue
            d = const_diff(ent[1], inesp)
            if d is None or not (0xffff0000 <= d):
                continue
            a = ent[1]
            if any(const_diff(a, lo) == 0 for lo, _ in saved):
                continue
            bs = [self.read_byte(a + k, s.memory.log) for k in range(4)]
            for r in CALLEE_SAVED:
                want = [self.IN[r][8 * k + 7:8 * k] for k in range(4)]
                if all(same(b, w) for b, w in zip(bs, want)):
                    saved.append((a, a + 4))
                    break
        saved.append((inesp, inesp + 4))
        if W is not None and not s.globals["escaped"]:
            return [(esp_ev + 4 + W, inesp + 4)] + saved, saved
        return saved, saved

    def escapes(self, s, regs_visible, esp_ev, W):
        """does a frame address become visible to a callee (argument registers, memory outside the frame)?"""
        if s.globals["escaped"]:
            return True
        name = "in_esp"
        for r in regs_visible:
            if name in getattr(s.regs, r).variables:
                return True
        inesp = self.IN["esp"]
        for ent in s.memory.log:
            if ent[0] != "w":
                continue
            if not any(name in b.variables for b in ent[2]):
                continue
            d = const_diff(ent[1], inesp)
            if d is None:
                return True
            if W is None:
                return True
            de = const_diff(ent[1], esp_ev + 4 + W)
            if de is None or de >= 0x80000000:          # below the private frame: an argument or callee area
                return True
        return False

    def do_call(self, s, i, info, tail=False):
        """the call event and the callee's effect; returns the successor state or None (path ends)"""
        C = self.C
        L2 = self.level == "L2"
        k = len(s.globals["events"])
        tgt, f, key = self.callee(info, i)
        if tgt is None:
            tgt = self.operand_target(s, i)
            mm = re.fullmatch(r"dword ptr \[(0x[0-9a-f]+)\]", i.op_str)
            key = ("m%x" % int(mm.group(1), 16)) if mm else None
            f = dict(self.facts.get(key, {})) if key else {}
            if not mm and "reads" not in f:
                f["reads"], f["guess"] = ["ecx", "edx"], True    # thiscall or fastcall at most
        esp0 = s.regs.esp
        if tail:
            esp_ev = esp0
        else:
            esp_ev = esp0 - 4
            s.memory.store(esp_ev, C.BVS("ra%d" % k, 32, explicit_name=True), endness="Iend_LE")
            s.regs.esp = esp_ev
        retn = f.get("retn")
        if retn is None:
            rn = C.BVS("rn%d" % k, 32, explicit_name=True)
            self.assume += [C.ULE(rn, 64), (rn & 3) == 0]
            retn = rn
        W = f.get("W")
        reads = f.get("reads")
        if reads is None:
            reads, f["guess"] = ["eax", "ecx", "edx"], True
        visible = [r for r in GPR if r != "esp"] if L2 else list(reads)
        esc = self.escapes(s, visible, esp_ev, W)
        if esc:
            s.globals["escaped"] = True
        prot, saved = self.private_ranges(s, esp_ev, W)
        ev = dict(kind="call", target=tgt, key=key or "", regs=self.snapshot(s), esp=esp_ev, log=s.memory.log,
                  reads=reads, W=W, prot=prot, escaped=esc, name=f.get("name", ""),
                  guess=reads if f.get("guess") else [])
        s.globals["events"] = s.globals["events"] + (ev,)
        if f.get("noreturn"):
            ev2 = dict(kind="noreturn")
            s.globals["events"] = s.globals["events"] + (ev2,)
            return None
        # effects
        fresh = lambda nm, bits: C.BVS("c%d_%s" % (k, nm), bits, explicit_name=True)
        kills = [r for r in GPR if r != "esp"] if L2 else ["eax", "ecx", "edx"]
        if f.get("chkstk"):
            kills = ["eax"]
        for r in kills:
            setattr(s.regs, r, fresh(r, 32))
        s.regs.cc_op, s.regs.cc_dep1, s.regs.cc_dep2, s.regs.cc_ndep = 0, fresh("flags", 32), 0, 0
        for x in XMM:
            setattr(s.regs, x, fresh(x, 128))
        fd = f.get("fdelta", -1 if f.get("fret") else 0)
        if fd:
            s.regs.ftop = s.regs.ftop + fd
            if fd < 0:
                s.regs.fptag = s.regs.fptag | (C.BVV(1, 64) << ((s.regs.ftop & 7).zero_extend(32) * 8))
            else:
                s.regs.fptag = s.regs.fptag & ~(C.BVV(0xff, 64) << (((s.regs.ftop - 1) & 7).zero_extend(32) * 8))
        s.regs.fpreg = fresh("fpreg", 512)
        s.memory.log = s.memory.log + (("havoc", str(k + 1), tuple(prot)),)
        if f.get("chkstk"):
            s.regs.esp = esp0 - ev["regs"]["eax"]
        else:
            s.regs.esp = esp_ev + 4 + retn
        if tail:
            return self.do_ret(s, None, after_tail=True)
        s.regs.ip = i.address + i.size
        return s

    def do_ret(self, s, i, after_tail=False):
        n = 0 if i is None else (int(i.op_str, 16) if i.op_str else 0)
        esp = s.regs.esp
        if after_tail:
            # the callee returned to our caller: its esp already includes the return
            ev = dict(kind="ret", regs=self.snapshot(s), esp_after=esp, target=None, log=s.memory.log)
        else:
            ev = dict(kind="ret", regs=self.snapshot(s), esp_after=esp + 4 + n,
                      target=s.memory.load(esp, 4, endness="Iend_LE"), log=s.memory.log)
        s.globals["events"] = s.globals["events"] + (ev,)
        return None

    def explore(self, side, bound, gen=None):
        """-> (finished states, dropped states at loop heads)"""
        proj, info = self.project(side)
        self.info = getattr(self, "info", {})
        self.info[side] = info
        st = self.entry_state(proj, info)
        done, dropped, todo, steps = [], [], [st], 0
        maxpaths = 3000
        while todo:
            if time.time() > self.deadline:
                raise GiveUp("timeout (exploring %s)" % side)
            s = todo.pop()
            a = s.addr if not s.regs.ip.symbolic else None
            if a is None:
                raise Unsupported("symbolic jump target in %s" % side)
            if not (info["base"] <= a < info["end"]) or a not in info["by"]:
                raise Unsupported("%s jumps to %x (outside the decoded function)" % (side, a))
            kind = info["kinds"].get(a)
            if a in info["heads"]:
                vis = s.globals["visits"]
                n = sum(1 for x in vis if x == a) + 1
                s.globals["visits"] = vis + (a,)
                b = bound.get(a, MAX_BOUND) if isinstance(bound, dict) else bound
                if n > b:
                    dropped.append(s)
                    continue
            i = info["by"][a]
            if kind == "call":
                t = _imm_target(i)
                if t is not None and info["base"] <= t < info["end"]:
                    raise Unsupported("call into the function itself at %x" % a)
                r = self.do_call(s, i, info)
                if r is None:
                    done.append(s)
                else:
                    todo.append(r)
                continue
            if kind == "ret":
                self.do_ret(s, i)
                done.append(s)
                continue
            if kind == "tail":
                self.do_call(s, i, info, tail=True)
                done.append(s)
                continue
            if kind == "ijmp":
                raise Unsupported("indirect jump at +%x in %s (switch table?)" % (a - info["base"], side))
            if kind == "tailcc":
                raise Unsupported("conditional tail jump at +%x in %s" % (a - info["base"], side))
            if kind == "trap":
                s.globals["events"] = s.globals["events"] + (dict(kind="trap"),)
                done.append(s)
                continue
            k = self.stop_len(info, a)
            try:
                succ = proj.factory.successors(s, num_inst=k)
            except Exception as e:
                raise Unsupported("angr cannot step +%x in %s: %s" % (a - info["base"], side, type(e).__name__))
            steps += 1
            if succ.unconstrained_successors:
                raise Unsupported("unconstrained successor at +%x in %s" % (a - info["base"], side))
            fl = succ.flat_successors
            last = self.last_ins(info, a, k)
            fall = last.address + last.size if last is not None else None
            for t in fl:
                jk = t.history.jumpkind
                if jk not in ("Ijk_Boring",):
                    raise Unsupported("jumpkind %s at +%x in %s" % (jk, a - info["base"], side))
                if len(fl) > 1:
                    t.globals["br"] = t.globals["br"] + ("0" if t.addr == fall else "1")
                todo.append(t)
            if len(done) + len(todo) + len(dropped) > maxpaths:
                raise GiveUp("more than %d paths in %s" % (maxpaths, side))
        self.stats["steps_" + side] = self.stats.get("steps_" + side, 0) + steps
        return done, dropped

    # ------------------------------------------------------------------ loops
    def iteration(self, side, head):
        """one generic iteration of the loop at head: [(constraints, out regs, exits?, wrote memory?)]"""
        C = self.C
        proj, info = self.project(side)
        st = self.entry_state(proj, info)
        st.regs.ip = head
        g = {r: C.BVS("g_" + r, 32, explicit_name=True) for r in GPR + ["flags"]}
        for r in GPR:
            setattr(st.regs, r, g[r])
        st.regs.cc_op, st.regs.cc_dep1, st.regs.cc_dep2, st.regs.cc_ndep = 0, g["flags"], 0, 0
        st.memory.epoch = "g"
        body = loop_body(info, head)
        out, todo, steps = [], [st], 0
        while todo:
            if time.time() > self.deadline:
                raise GiveUp("timeout (loop analysis)")
            s = todo.pop()
            a = s.addr
            if s is not st and a == head:
                out.append((list(s.solver.constraints), s, False))
                continue
            if a not in body:
                out.append((list(s.solver.constraints), s, True))
                continue
            if a in info["kinds"] and info["kinds"][a] != "rep":
                return None                                  # a call or return inside the loop
            if a != head and a in info["heads"]:
                return None                                  # a nested loop
            k = 1 if a == head else self.stop_len(info, a)
            succ = proj.factory.successors(s, num_inst=k)
            steps += 1
            if steps > 400 or succ.unconstrained_successors:
                return None
            for t in succ.flat_successors:
                if t.history.jumpkind != "Ijk_Boring":
                    return None
                todo.append(t)
        return g, out

    def diverges(self, side, s):
        """True when the dropped state s provably never leaves its loop (see module docstring)"""
        C, z3 = self.C, self.z3
        head = s.addr
        r = self.iteration(side, head)
        if r is None:
            return False, "loop body has calls, nested loops or too many paths"
        g, paths = r
        for cons, t, ex in paths:
            if t.memory.log:
                return False, "loop body writes memory"
        outv = lambda t, u: t.regs.eflags if u == "flags" else getattr(t.regs, u)
        # U: the registers the exit decisions depend on, closed under "the next value of u depends on"
        need = set()
        for cons, t, ex in paths:
            for c in cons:
                need |= set(c.variables)
        U, todo = set(), list(need)
        while todo:
            v = todo.pop()
            if not v.startswith("g_"):
                return False, "loop exit depends on memory or on %s" % v
            u = v[2:]
            if u in U:
                continue
            U.add(u)
            for cons, t, ex in paths:
                if not ex:
                    todo += [w for w in outv(t, u).variables if w[2:] not in U]
        sval = {u: (s.regs.eflags if u == "flags" else getattr(s.regs, u)) for u in U}
        subst = {"g_" + u: sval[u] for u in U}
        q = self.solver()
        q.add(self.z(self.pc(s)))
        bad = []
        for cons, t, ex in paths:
            c = self.z(C.And(*cons), subst) if cons else z3.BoolVal(True)
            if ex:
                bad.append(c)
            else:
                ne = [self.z(outv(t, u), subst) != self.z(sval[u]) for u in sorted(U)]
                bad.append(z3.And(c, z3.Or(*ne)) if ne else z3.BoolVal(False))
        if self.check(q, z3.Or(*bad)):
            return False, "a state at the bound can still leave the loop"
        return True, "diverge:%s" % ",".join(sorted(U))

    def explore_bounded(self, side):
        """explore with a loop bound that has a checked reason. -> (done, diverging, loop hints)"""
        hl = (self.hints.get("loops") or {}).get(side)
        info = self.project(side)[1]
        heads = sorted(info["heads"])
        if not heads:
            done, dropped = self.explore(side, MAX_BOUND)
            return done, [], {}
        if hl is not None:
            bound = {info["base"] + int(k, 16): v[0] for k, v in hl.items()}
            if set(bound) != set(heads):
                raise GiveUp("hint loops do not name the loop heads of %s" % side)
            seq = [bound]
        else:
            seq = [{h: n for h in heads} for n in (2, 4, 8, 16, 32, MAX_BOUND)]
        last = "no bound"
        for bound in seq:
            done, dropped = self.explore(side, bound)
            reasons, ok = {}, True
            for s in dropped:
                d, why = self.diverges(side, s)
                if not d:
                    ok, last = False, why
                    break
                reasons[s.addr] = why
            if ok:
                for s in dropped:
                    s.globals["events"] = s.globals["events"] + (dict(kind="diverge", esp=s.regs.esp,
                                                                      log=s.memory.log),)
                hints = {"%x" % (h - info["base"]): [bound[h], reasons.get(h, "exits within bound")]
                         for h in heads}
                return done, dropped, hints
            if hl is not None:
                raise GiveUp("hint loop bound for %s rejected: %s" % (side, last))
        raise GiveUp("loop in %s not bounded up to %d iterations: %s" % (side, MAX_BOUND, last))

    # ------------------------------------------------------------------ comparison
    def observables(self, ea, eb):
        """[(name, a, b)] or a string naming a structural difference"""
        C = self.C
        L2 = self.level == "L2"
        ka = [(e["kind"], e.get("key", "")) for e in ea]
        kb = [(e["kind"], e.get("key", "")) for e in eb]
        if [k for k, _ in ka] != [k for k, _ in kb]:
            return "event sequence %s vs %s" % ([k for k, _ in ka], [k for k, _ in kb])
        obs, regions = [], []
        inesp = self.IN["esp"]
        for n, (x, y) in enumerate(zip(ea, eb)):
            tag = "%s#%d" % (x["kind"], n)
            if x["kind"] in ("noreturn", "trap"):
                continue
            if x["kind"] == "call":
                obs.append((tag + " target", x["target"], y["target"]))
                if L2:
                    regs = GPR + ["eflags", "d", "ftop", "fptag", "fpreg"] + XMM
                else:
                    reads = sorted(set(x["reads"]) | set(y["reads"]))
                    regs = ["esp", "d", "ftop", "fptag"] + reads
                    self.guessed |= {"%s %s" % (tag, r) for r in set(x["guess"]) | set(y["guess"])}
                obs += [("%s %s" % (tag, r), x["regs"][r], y["regs"][r]) for r in regs]
                if not L2:
                    obs += self.x87_valid(tag, x["regs"], y["regs"])
                lo = x["esp"]
                excl = [] if (L2 or x["escaped"] or y["escaped"]) else list(x["prot"]) + list(y["prot"])
                regions.append((tag + " memory", lo, excl, x["log"], y["log"],
                                x["W"] if x["W"] == y["W"] else None))
            elif x["kind"] == "ret":
                if x["target"] is not None or y["target"] is not None:
                    if x["target"] is None or y["target"] is None:
                        return "tail call vs return at %s" % tag
                    obs.append((tag + " return target", x["target"], y["target"]))
                obs.append((tag + " esp", x["esp_after"], y["esp_after"]))
                if L2:
                    regs = [r for r in GPR if r != "esp"] + ["eflags", "d", "ftop", "fptag", "fpreg"] + XMM
                else:
                    regs = ["eax", "ebx", "esi", "edi", "ebp", "d", "ftop", "fptag"] + (
                        ["edx"] if self.job["ret64"] else [])
                obs += [("%s %s" % (tag, r), x["regs"][r], y["regs"][r]) for r in regs]
                if not L2:
                    obs += self.x87_valid(tag, x["regs"], y["regs"])
                regions.append((tag + " memory", x["esp_after"], [], x["log"], y["log"], None))
            elif x["kind"] == "diverge":
                excl = [] if L2 else [(x["esp"], inesp + 4)]
                regions.append((tag + " memory", x["esp"], excl, x["log"], y["log"], None))
        return obs, regions

    def x87_valid(self, tag, ra, rb):
        out = []
        for k in range(8):
            ta, tb = ra["fptag"][8 * k + 7:8 * k], rb["fptag"][8 * k + 7:8 * k]
            va, vb = ra["fpreg"][64 * k + 63:64 * k], rb["fpreg"][64 * k + 63:64 * k]
            if ta.concrete and ta.concrete_value == 0 and tb.concrete and tb.concrete_value == 0:
                continue
            out.append(("%s st-slot%d" % (tag, k), self.C.If(ta != 0, va, 0), self.C.If(tb != 0, vb, 0)))
        return out

    def compare_pair(self, sa, sb, pcs, known_equal_pc):
        """None when equivalent on the overlap, else a counterexample dict"""
        C, z3 = self.C, self.z3
        ea, eb = sa.globals["events"], sb.globals["events"]
        q = self.solver()
        q.add(pcs[0])
        if not known_equal_pc:
            q.add(pcs[1])
        r = self.observables(ea, eb)
        if isinstance(r, str):
            if not self.check(q):
                return None
            return self.cex(q, r, [], None)
        obs, regions = r
        diffs = []
        guessed = self.guessed
        for name, a, b in obs:
            if a.size() != b.size():
                return {"what": name + " (size)"}
            if same(a, b):
                continue
            diffs.append((name, self.z(a) != self.z(b)))
        x = self.PROBE
        zx = self.z(x)
        for name, lo, excl, la, lb, _ in regions:
            if la is lb:
                continue
            ma, mb = self.read_byte(x, la), self.read_byte(x, lb)
            if same(ma, mb):
                continue
            cond = [z3.UGE(zx, self.z(lo))]
            for elo, ehi in excl:
                cond.append(z3.Not(z3.ULT(zx - self.z(elo), self.z(ehi) - self.z(elo))))
            diffs.append((name, z3.And(*cond + [self.z(ma) != self.z(mb)])))
        if not diffs:
            return None
        strict = [d for n, d in diffs if n not in guessed]
        if strict and self.check(q, z3.Or(*strict)):
            return self.cex(q, None, [(n, d) for n, d in diffs if n not in guessed], regions)
        weak = [d for n, d in diffs if n in guessed]
        if not weak or not self.check(q, z3.Or(*weak)):
            return None
        c = self.cex(q, None, [(n, d) for n, d in diffs if n in guessed], regions)
        c["assumed_reads"] = True
        return c

    def cex(self, q, what, diffs, regions):
        z3 = self.z3
        m = q.model()
        out = {}
        if what:
            out["what"] = what
        else:
            bad = [n for n, d in diffs if z3.is_true(m.eval(d, model_completion=True))]
            out["what"] = ", ".join(bad[:4]) or diffs[0][0]
            mem = [n for n in bad if n.endswith("memory")]
            if mem:
                ev = lambda e: m.eval(self.z(e), model_completion=True).as_long()
                addr = ev(self.PROBE)
                out["addr"] = hex(addr)
                reg = [r for r in regions if r[0] == mem[0]][0]
                lo, top = ev(reg[1]), ev(self.IN["esp"]) + 4
                argtop = lo + 4 + reg[5] if isinstance(reg[5], int) else lo
                out["frame"] = lo <= addr < top and addr >= argtop
        for r in GPR:
            out["in_" + r] = hex(m.eval(self.z(self.IN[r]), model_completion=True).as_long())
        return out

    def run(self):
        t0 = time.time()
        level = self.level
        A, Ad, la = self.explore_bounded("retail")
        B, Bd, lb = self.explore_bounded("ours")
        A, B = A + Ad, B + Bd
        texp = time.time() - t0
        hints_out = {"v": 1, "bij": self.job["bij"], "loops": {}}
        if la:
            hints_out["loops"]["retail"] = la
        if lb:
            hints_out["loops"]["ours"] = lb
        if not hints_out["loops"]:
            del hints_out["loops"]
        zpc = {}
        feasible = {}
        for side, S in (("a", A), ("b", B)):
            for s in S:
                zpc[id(s)] = self.z(self.pc(s))
        # pairing
        hp = {a: b for a, b in self.hints.get("pairs", [])}
        hfall = set(self.hints.get("fallback", []))
        given = "pairs" in self.hints or "fallback" in self.hints
        bysig = {}
        for sb in B:
            bysig.setdefault(sb.globals["br"], []).append(sb)
        siga = {sa.globals["br"] for sa in A}
        for x, y in hp.items():
            if x not in siga or y not in bysig:
                raise GiveUp("hint pairs name a path that does not exist (%s -> %s)" % (x, y))
        if not hfall <= siga:
            raise GiveUp("hint fallback names a path that does not exist")
        pairs_out, fallback_out = [], []
        unA, usedB = [], set()
        cexs = []
        matched = 0
        for sa in A:
            sig = sa.globals["br"]
            if given and sig in hfall:
                unA.append(sa)
                fallback_out.append(sig)
                continue
            want = hp.get(sig, sig)
            cands = [sb for sb in bysig.get(want, []) if id(sb) not in usedB]
            ok = None
            for sb in cands:
                q = self.solver()
                if not self.check(q, z3_xor(self.z3, zpc[id(sa)], zpc[id(sb)])):
                    ok = sb
                    break
            if ok is None:
                if given:
                    raise GiveUp("hint pairing rejected for path %s" % (sig or "(entry)"))
                unA.append(sa)
                fallback_out.append(sig)
                continue
            usedB.add(id(ok))
            matched += 1
            if want != sig:
                pairs_out.append([sig, want])
            c = self.compare_pair(sa, ok, (zpc[id(sa)], zpc[id(ok)]), True)
            if c:
                cexs.append(c)
                break
        if not cexs and unA:
            unB = [sb for sb in B if id(sb) not in usedB]
            for sa in unA:
                q = self.solver()
                q.add(zpc[id(sa)])
                if not self.check(q):
                    continue                     # infeasible under the full memory model
                for sb in unB:
                    q2 = self.solver()
                    q2.add(zpc[id(sa)], zpc[id(sb)])
                    if not self.check(q2):
                        continue
                    c = self.compare_pair(sa, sb, (zpc[id(sa)], zpc[id(sb)]), False)
                    if c:
                        cexs.append(c)
                        break
                if cexs:
                    break
        if pairs_out:
            hints_out["pairs"] = pairs_out
        if fallback_out:
            hints_out["fallback"] = fallback_out
        nloops = sum(len(v) for v in hints_out.get("loops", {}).values())
        summary = ("%s: retail %d paths (%d diverging), ours %d (%d); %d paired by equal path condition, %d by "
                   "overlap; explore %.1fs, %d queries" % (level, len(A), len(Ad), len(B), len(Bd), matched,
                                                          len(unA), texp, self.stats.get("queries", 0)))
        if nloops:
            summary += "; loops " + json.dumps(hints_out["loops"], separators=(",", ":"))
        if cexs:
            c = cexs[0]
            st = "refuted"
            why = []
            if not self.job["clean"]:
                st, why = "unknown", why + ["relocation pairing is heuristic"]
            if self.job["x87"] and not self.job["x87_same"]:
                st, why = "unknown", why + ["x87 sequences differ (64-bit model)"]
            if st == "refuted" and c.get("assumed_reads"):
                st, why = "unknown", why + ["the differing register is read only if the unknown callee's "
                                            "convention reads it"]
            if self.hints:
                st, why = "unknown", why + ["checked against given hints"]
            if st == "refuted" and c.get("frame") and level == "L1":
                st, why = "unknown", why + ["the memory difference is in the caller's own frame"]
            d = "difference: %s" % json.dumps(c, separators=(",", ":"))
            if why:
                d = "counterexample in the model, not trusted (%s): %s" % ("; ".join(why), d)
            return {"status": st, "detail": d + " | " + summary, "hints": {}}
        if self.job["x87"] and not self.job["x87_same"]:
            return {"status": "unknown", "detail": "equal in the 64-bit x87 model, but the x87 instruction "
                    "sequences differ | " + summary, "hints": hints_out}
        return {"status": "proved", "detail": summary, "hints": hints_out}


def z3_xor(z3, a, b):
    return z3.Xor(a, b)


# ====================================================================== command line
def main():
    if "--worker" in sys.argv:
        return worker_main()
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("va")
    ap.add_argument("--level", default="L1")
    ap.add_argument("--timeout", type=float, default=600)
    ap.add_argument("--hints")
    ap.add_argument("--save-hints")
    a = ap.parse_args()
    sys.path.insert(0, HERE)
    import func as FN
    va = int(a.va, 16)
    r = prove(FN.retail_func(va), FN.our_func(va), a.level,
              json.load(open(a.hints)) if a.hints else None, a.timeout)
    if a.save_hints:
        json.dump(r["hints"], open(a.save_hints, "w"))
    print(json.dumps({k: v for k, v in r.items() if k != "hints"}, indent=1))
    print("hints: %d bytes" % len(json.dumps(r["hints"], separators=(",", ":"))))


if __name__ == "__main__":
    main()
