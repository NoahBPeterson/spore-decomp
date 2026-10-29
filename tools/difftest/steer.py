"""Cheap input steering for equiv.py (no solver): drive the generated inputs toward uncovered branch edges.

- Comparison constants: the immediates and memory constants each compare-before-jcc uses (both builds)
  join the generator's dictionary, with +-1 (float constants with +-1 ulp).
- Input-to-state steering ("Redqueen"): for an uncovered edge whose branch already ran, replay an input
  that reached it with the compare instrumented; the compared operand's value is traced back to the input
  location it was read from (argument slot, entry register, pool object field, image .data global, or a
  malloc result), and copies of the input with that location set to the other operand's value (+-1 /
  +-1 ulp, bit masks for `test`) are queued for the normal test loop.
- Coverage-guided parent choice: mutation prefers corpus inputs that reach branches with an uncovered edge.
Every candidate is an ordinary Input: both builds run it, and it is compared like any other.
"""
import collections, math, os, struct

import capstone
from capstone import x86_const as X
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_READ
import unicorn.x86_const as U

import machine as M

MAX_TRIES = 6            # instrumented replays per (side, branch) before it is left to random mutation
BOUNDARY_TRIES = 2       # boundary replays per covered branch
MAX_OCC = 8              # compare executions recorded per replay
RECENT = 96              # reads remembered before each compare
_MASK = {1: 0xFF, 2: 0xFFFF, 4: 0xFFFFFFFF, 8: 0xFFFFFFFFFFFFFFFF}


def _ucreg(r):
    n = _md_reg_name(r)
    return getattr(U, "UC_X86_REG_" + n.upper(), None) if n else None


_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def _md_reg_name(r):
    try:
        return _md.reg_name(r)
    except Exception:
        return None


def f32(u):
    return struct.unpack("<f", struct.pack("<I", u & 0xFFFFFFFF))[0]


def u32f(x):
    try:
        return struct.unpack("<I", struct.pack("<f", x))[0]
    except OverflowError:
        return 0x7F7FFFFF if x > 0 else 0xFF7FFFFF


def next32(x, up):
    """Adjacent float32 (by one ulp)."""
    u = u32f(x)
    if x == 0.0:
        return f32(1) if up else f32(0x80000001)
    if (x > 0) == up:
        return f32(u + 1)
    return f32(u - 1)


def x87_val(v):
    mant, exp = v
    sign = -1.0 if exp & 0x8000 else 1.0
    e = exp & 0x7FFF
    if e == 0x7FFF:
        return float("nan")
    if e == 0 and mant == 0:
        return sign * 0.0
    try:
        return sign * math.ldexp(mant, e - 16383 - 63)
    except OverflowError:
        return sign * float("inf")


def fcmp_before(cfg, src):
    """The fcom/fucom/ftst feeding the x87 status-word branch at src (None if not that pattern)."""
    p = cfg.prev.get(src)
    for _ in range(12):
        if p is None:
            return None
        ins = cfg.insns[p]
        if ins.mnemonic in ("fnstsw", "fstsw"):
            q = cfg.prev.get(p)
            for _ in range(6):
                if q is None:
                    return None
                qi = cfg.insns[q]
                if qi.mnemonic.startswith("f"):
                    return qi if qi.mnemonic.startswith(("fcom", "fucom", "ftst", "ficom")) else None
                q = cfg.prev.get(q)
            return None
        p = cfg.prev.get(p)
    return None


def harvest_constants(cfgs, img):
    """Integer and float constants compared before branches in either build."""
    ints, floats = set(), set()
    for cfg in cfgs:
        for src in cfg.branch_end.values():
            a = src[0]
            for ins in (cfg.cmp_before.get(a), fcmp_before(cfg, a)):
                if ins is None:
                    continue
                for op in ins.operands:
                    if op.type == X.X86_OP_IMM:
                        ints.add(op.imm & 0xFFFFFFFF)
                    elif op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index:
                        addr = op.mem.disp & 0xFFFFFFFF
                        if not img.in_image(addr):
                            continue
                        try:
                            if op.size == 4:
                                v = struct.unpack("<I", img.read(addr, 4))[0]
                                (floats if ins.mnemonic.startswith("f") else ints).add(f32(v) if ins.mnemonic.startswith("f") else v)
                            elif op.size == 8:
                                floats.add(struct.unpack("<d", img.read(addr, 8))[0])
                        except Exception:
                            pass
    out = set()
    for c in ints:
        out |= {c, (c + 1) & 0xFFFFFFFF, (c - 1) & 0xFFFFFFFF}
    for x in floats:
        if math.isfinite(x):
            out |= {u32f(x), u32f(next32(x, True)), u32f(next32(x, False))}
    return out


class Steer:
    def __init__(self, runner, gen, opts):
        self.r, self.gen, self.opts = runner, gen, opts
        self.queue = collections.deque()
        self.tries = {}
        self.btries = {}
        self.reach = {"orig": {}, "ours": {}}       # branch src -> latest valid input that executed it
        self.hits = {}                              # id(input) -> {(side, src)}
        self.frontier_cache = None
        self.made = 0
        self.stats = collections.Counter()
        consts = harvest_constants([runner.orig.cfg, runner.ours.cfg], runner.img)
        extra = [gen.fin(c) for c in sorted(consts) if c not in set(gen.dic)]
        gen.dic.extend(extra[:4096])
        self.n_consts = len(consts)
        self.concolic = None
        self.cc_time = 0.0                          # seconds spent tracing/solving (capped at 40% of --time-limit)
        if os.environ.get("DIFFTEST_CONCOLIC"):        # opt-in while it is evaluated
            try:
                import concolic
                if concolic.z3 is not None:
                    self.concolic = concolic.Concolic(runner, self)
            except Exception:           # noqa: BLE001 - z3 missing: input-to-state only, as before
                self.concolic = None

    # ------------------------------------------------------------------ bookkeeping
    def note_valid(self, inp, edges_by_side):
        hs = set()
        for side, edges in edges_by_side.items():
            for s, _d in edges:
                self.reach[side][s] = inp
                hs.add((side, s))
        self.hits[id(inp)] = hs
        self.frontier_cache = None

    def frontier(self):
        """{(side name, branch src)} for branches that ran in a valid input but miss an edge."""
        if self.frontier_cache is None:
            fr = set()
            scope = getattr(self.r, "edge_scope", None)     # --edge-scope: the original's edges that matter
            for side in ((self.r.orig,) if scope is not None else (self.r.orig, self.r.ours)):
                cov = side.edges
                skip = side.cfg_static_unreachable
                for e in (scope if scope is not None else side.cfg.edges):
                    if e not in cov and e not in skip and e[0] in self.reach[side.name]:
                        fr.add((side.name, e[0]))
            self.frontier_cache = fr
        return self.frontier_cache

    def pick_parent(self, corpus, rng):
        fr = self.frontier()
        if not fr or not corpus:
            return corpus[-1 - min(int(rng.expovariate(0.15)), len(corpus) - 1)]
        w = [1 + 4 * len(self.hits.get(id(c), ()) & fr) for c in corpus]
        return rng.choices(corpus, w)[0]

    def has_work(self):
        """Uncovered branches still worth a replay (boundary probing never extends the run)."""
        return any(self.tries.get(k, 0) < MAX_TRIES for k in self.frontier())

    def next(self, rng, corpus):
        if not self.queue:
            self.refill(rng, corpus)
        return self.queue.popleft() if self.queue else None

    def refill(self, rng, corpus):
        fr = [k for k in self.frontier() if self.tries.get(k, 0) < MAX_TRIES]
        boundary = False
        if not fr:
            # every reachable edge is covered (or given up on): probe the boundary of covered compares
            # (operand == constant, +-1, +-1 ulp), where `>` vs `>=` and near-miss constants differ
            fr = [(sn, src) for sn in ("orig", "ours") for src in self.reach[sn]
                  if self.btries.get((sn, src), 0) < BOUNDARY_TRIES]
            boundary = True
            if not fr:
                return
        rng.shuffle(fr)
        tries = self.btries if boundary else self.tries
        key = min(fr, key=lambda k: tries.get(k, 0))
        tries[key] = tries.get(key, 0) + 1
        self.stats["boundary" if boundary else "frontier"] += 1
        sname, src = key
        side = self.r.orig if sname == "orig" else self.r.ours
        inp0 = self.reach[sname][src]
        self._boundary = boundary
        cands = self.redqueen(side, src, inp0, rng)
        self.stats["replays"] += 1
        if cands:
            self.stats["redqueen"] += len(cands)
        else:
            cands = [self.gen.mutate(inp0, rng, corpus) for _ in range(3)]
            self.stats["havoc"] += len(cands)
        for c in cands[:24]:
            c.origin = "steer"
        cands = cands[:24]
        self.queue.extend(cands)
        self.made += len(cands)

    # ------------------------------------------------------------------ instrumented replay
    def redqueen(self, side, src, inp0, rng):
        cfg = side.cfg
        jins = cfg.insns[src]
        cins = fcmp_before(cfg, src) if jins.id != X.X86_INS_JMP else None
        kind = "float" if cins is not None else "int"
        if cins is None:
            cins = cfg.cmp_before.get(src) if jins.id != X.X86_INS_JMP else jins
        self.byte_table = None
        if jins.id == X.X86_INS_JMP:
            # two-level switch: movzx idx, byte [sel + bytetable]; jmp [idx*4 + table]: steer the selector
            p = cfg.insns.get(cfg.prev.get(src))
            if p is not None and p.id == X.X86_INS_MOVZX and p.operands[1].type == X.X86_OP_MEM and \
                    p.operands[1].size == 1 and p.operands[1].mem.index == 0 and p.operands[1].mem.base:
                cins = p
                self.byte_table = p.operands[1].mem.disp & 0xFFFFFFFF
        if cins is None:
            return []
        r, m = self.r, self.r.m
        uc = m.uc
        # a branch on a callee's result (`call f; test al, al; je`): the compare that decides it is inside f, so
        # every cmp/test of f is instrumented too and each one it executed becomes an input-to-state target
        self._last_ranges = []
        inner = self._callee_compares(cfg, cins) if kind == "int" else []
        windows = list(self._last_ranges)
        def replay(inp):
            """Run inp with the compare (and the callee's compares) instrumented -> (occ, iocc, allocs)."""
            recent = collections.deque(maxlen=RECENT)
            occ, iocc, allocs = [], [], []

            def on_read(uc_, access, address, size, value, _):
                try:
                    v = int.from_bytes(m.read(address, size), "little") if size in (1, 2, 4, 8) else None
                except Exception:
                    return
                if v is not None:
                    recent.append((address, size, v, uc_.reg_read(U.UC_X86_REG_EIP)))

            def on_cmp(uc_, address, size, _):
                if r.cur is not side or len(occ) >= MAX_OCC:
                    return
                try:
                    occ.append((self._operands(cins, kind), list(recent)))
                except Exception:
                    pass

            def on_icmp(uc_, address, size, ins):
                if r.cur is not side or len(iocc) >= 4 * MAX_OCC:
                    return
                try:
                    iocc.append((ins, self._operands(ins, "int"), list(recent)))
                except Exception as e:
                    if os.environ.get("DIFFTEST_STEER_DEBUG"):
                        print("  callee cmp %08x: operands failed: %r" % (ins.address, e), flush=True)
            ranges = [(M.POOL_BASE, M.POOL_BASE + M.POOL_SIZE), (r.esp_entry, r.args_hi)]
            ranges += [(lo, hi) for _nm, lo, hi in m.writable]
            hooks = [uc.hook_add(UC_HOOK_MEM_READ, on_read, begin=lo, end=hi - 1) for lo, hi in ranges]
            hooks.append(uc.hook_add(UC_HOOK_CODE, on_cmp, begin=cins.address, end=cins.address))
            for ins in inner:
                hooks.append(uc.hook_add(UC_HOOK_CODE, on_icmp, user_data=ins, begin=ins.address, end=ins.address))
            m.alloc_log = allocs
            try:
                r.run_side(side, inp)
            except Exception:
                pass
            finally:
                for h in hooks:
                    uc.hook_del(h)
                m.alloc_log = None
            return occ, iocc, allocs

        occ, iocc, allocs = replay(inp0)
        if inner and iocc and os.environ.get("DIFFTEST_STEER_CHAIN"):
            # (opt-in: on the interpreter's sample it cost more time than it found, see docs/matching.md)
            # Chained conditions (check_party: the id below the table count, PartyMgr::index_of finds it, the
            # record it finds has type 1): a candidate that reaches a compare its parent never reached is
            # replayed at once and steered from, up to 3 levels, instead of waiting for a later round to pick
            # it as a parent. A candidate whose result test flips (`test al, al` sees nonzero) is returned first.
            reached = {i.address for i, _o, _r in iocc}
            level, deeper, winners = [(inp0, iocc, allocs)], [], []
            for _depth in range(3):
                nxt = []
                for base, bio, bal in level:
                    tried = 0
                    for ins, ops, rec in reversed(bio):
                        for c in self._candidates(ins, "int", ops, rec, base, bal, jins, rng)[:4]:
                            if tried >= 12:
                                break
                            tried += 1
                            o2, io2, al2 = replay(c)
                            self.stats["chain-replay"] += 1
                            if any(op[0][0] for op, _rc in o2 if op and op[0][0] is not None):
                                winners.append(c)
                            new = {i.address for i, _o, _r in io2} - reached
                            if new:
                                reached |= new
                                nxt.append((c, io2, al2))
                                deeper.append(c)
                if winners or not nxt:
                    break
                level = nxt[:3]
            if winners or deeper:
                self.stats["chain-win" if winners else "chain-deeper"] += 1
                for c in (winners + deeper)[:24]:
                    c.origin = "steer"
                return (winners + deeper)[:24]
        out = []
        budget = 0.4 * getattr(self.opts, "time_limit", 180)
        if self.concolic is not None and not getattr(self, "_boundary", False) and kind == "int" \
                and self.cc_time < budget:
            # z3 over the traced path, for every uncovered branch while its share of the run's time lasts: the
            # callee's chained decisions (windows) when the branch tests a callee's result, else its own
            import time as _t
            t0 = _t.time()
            try:
                cc = self.concolic.steer(side, inp0, src, window=windows or None)
                if cc and os.environ.get("DIFFTEST_STEER_DEBUG"):
                    print("  concolic %08x: %d candidate(s)" % (src, len(cc)), flush=True)
            except Exception as e:      # noqa: BLE001 - steering must never stop a run
                cc = []
                if os.environ.get("DIFFTEST_STEER_DEBUG"):
                    print("  concolic failed: %r" % e, flush=True)
            self.cc_time += _t.time() - t0
            self.stats["concolic"] += len(cc)
            out.extend(cc)
        if os.environ.get("DIFFTEST_STEER_DEBUG"):
            print("  replay %s %08x: %d callee compares hooked (%s), fired: %s" % (side.name, src, len(inner),
                  " ".join("%x" % i.address for i in inner[:12]), sorted({"%x" % i.address for i, _o, _r in iocc})),
                  flush=True)
        # the callee's compares first (each deciding compare, latest occurrence), then the tested function's own
        # compare: for `call f; test al, al` the latter only says "al was 0", which no input location holds
        seen = set()
        for ins, ops, rec in reversed(iocc):
            if ins.address in seen:
                continue
            seen.add(ins.address)
            self.stats["callee-cmp"] += 1
            if os.environ.get("DIFFTEST_STEER_DEBUG"):
                locs = [self._locations(o[0], o[1], o[2], rec, inp0, "int") if o[0] is not None and not o[3] else None
                        for o in ops]
                print("  callee cmp %08x %s %s | ops %s | locs %s" % (ins.address, ins.mnemonic, ins.op_str,
                      [(("%x" % o[0]) if o[0] is not None else None, o[3]) for o in ops], locs), flush=True)
            for c in self._candidates(ins, "int", ops, rec, inp0, allocs, jins, rng)[:8]:
                out.append(c)
        for ops, rec in occ:
            self.fpcs = {a for a, i in cfg.insns.items() if i.mnemonic.startswith("f")}
            for c in self._candidates(cins, kind, ops, rec, inp0, allocs, jins, rng):
                out.append(c)
                if len(out) >= 24 + 8 * len(seen):
                    return out
        return out

    def _callee_compares(self, cfg, cins):
        """The cmp/test instructions of the function whose result `cins` tests (`call f` within the three
        instructions before `test al, al` / `test eax, eax`), or []. Image functions only, cached."""
        if cins.mnemonic != "test" or len(cins.operands) != 2 or cins.operands[0].type != X.X86_OP_REG or \
                cins.operands[0].reg != cins.operands[1].reg or _md_reg_name(cins.operands[0].reg) not in ("al", "eax"):
            return []
        a, tgt = cins.address, None
        for _ in range(3):
            a = cfg.prev.get(a)
            ins = cfg.insns.get(a) if a is not None else None
            if ins is None:
                break
            if ins.id == X.X86_INS_CALL:
                if ins.operands[0].type == X.X86_OP_IMM:
                    tgt = ins.operands[0].imm & 0xFFFFFFFF
                break
        if tgt is None:
            return []
        cache = self.__dict__.setdefault("_ccache", {})
        if tgt not in cache:
            # the callee and the image functions it calls directly (check_party 0x49d160 decides through
            # PartyMgr::index_of 0x48ad00's compares too)
            out, todo, done, ranges = [], [(tgt, 0)], set(), []
            while todo and len(out) < 128:
                f, depth = todo.pop(0)
                if f in done:
                    continue
                done.add(f)
                try:
                    img = self.r.img
                    lo, hi = img.func_extent(f)
                    code = img.read(lo, hi - lo)
                    import resolve as R
                    insns, _ = R.recursive_descent(lambda x, k, lo=lo, code=code: code[x - lo:x - lo + k], lo, hi, f,
                                                   lambda x: None)
                except Exception:
                    continue
                ranges.append((lo, hi))
                for _a, i in sorted(insns.items()):
                    if i.mnemonic in ("cmp", "test"):
                        out.append(i)
                    elif i.id == X.X86_INS_CALL and depth < 1 and i.operands[0].type == X.X86_OP_IMM:
                        todo.append((i.operands[0].imm & 0xFFFFFFFF, depth + 1))
            cache[tgt] = out[:128]
            self.__dict__.setdefault("_cranges", {})[tgt] = ranges
            self._last_ranges = ranges
        else:
            self._last_ranges = self.__dict__.get("_cranges", {}).get(tgt, [])
        return cache[tgt]

    def _operands(self, ins, kind):
        """[(value, size, mem address or None, is_imm)] of the compare's operands (x87: floats)."""
        uc = self.r.m.uc
        res = []
        if kind == "float":
            fpsw = uc.reg_read(U.UC_X86_REG_FPSW)
            top = (fpsw >> 11) & 7

            def st(i):
                return x87_val(uc.reg_read(U.UC_X86_REG_FP0 + ((top + i) & 7)))
            res.append((st(0), 10, None, False))
            if ins.mnemonic.startswith("ftst"):
                res.append((0.0, 10, None, True))
                return res
            ops = [o for o in ins.operands]
            if not ops:
                res.append((st(1), 10, None, False))
            for o in ops:
                if o.type == X.X86_OP_MEM:
                    a = self._ea(o)
                    raw = self.r.m.read(a, o.size)
                    if ins.mnemonic.startswith("fi"):
                        v = float(int.from_bytes(raw, "little", signed=True))
                    else:
                        v = struct.unpack("<f" if o.size == 4 else "<d", raw)[0] if o.size in (4, 8) else None
                    res.append((v, o.size, a, False))
                elif o.type == X.X86_OP_REG and X.X86_REG_ST0 <= o.reg <= X.X86_REG_ST7:
                    i = o.reg - X.X86_REG_ST0
                    if i:
                        res.append((st(i), 10, None, False))
            if len(res) == 1:
                res.append((st(1), 10, None, False))
            return res
        if ins.id == X.X86_INS_JMP:                 # jump table: the index register
            o = ins.operands[0]
            res.append((uc.reg_read(_ucreg(o.mem.index)), 4, None, False))
            return res
        if ins.id == X.X86_INS_MOVZX and self.byte_table is not None:   # byte-indexed switch: the selector
            res.append((uc.reg_read(_ucreg(ins.operands[1].mem.base)), 4, None, False))
            return res
        for o in ins.operands:
            if o.type == X.X86_OP_REG:
                ur = _ucreg(o.reg)
                res.append((uc.reg_read(ur) & _MASK.get(o.size, 0xFFFFFFFF), o.size, None, False))
            elif o.type == X.X86_OP_MEM:
                a = self._ea(o)
                res.append((int.from_bytes(self._peek(a, o.size), "little"), o.size, a, False))
            elif o.type == X.X86_OP_IMM:
                res.append((o.imm & _MASK.get(o.size, 0xFFFFFFFF), o.size, None, True))
        return res

    def _peek(self, a, n):
        """Read n bytes at a; a pool page the run has not touched yet (a compare hook fires before the access
        that would map it) is read from the pool generator, without mapping it."""
        m = self.r.m
        try:
            return m.read(a, n)
        except Exception:
            if not (M.POOL_BASE <= a and a + n <= M.POOL_BASE + M.POOL_SIZE) or getattr(m, "lazy", None) is None:
                raise
            out = bytearray()
            for k in range(n):
                p = (a + k) & ~0xFFF
                out.append(m.lazy(p)[(a + k) & 0xFFF])
            return bytes(out)

    def _ea(self, o):
        uc = self.r.m.uc
        a = o.mem.disp
        if o.mem.base:
            a += uc.reg_read(_ucreg(o.mem.base))
        if o.mem.index:
            a += uc.reg_read(_ucreg(o.mem.index)) * o.mem.scale
        return a & 0xFFFFFFFF

    # ------------------------------------------------------------------ candidate inputs
    def _locations(self, val, size, addr, rec, inp, kind):
        """Input locations holding a compared operand: [(region, key, size)]."""
        locs = []
        if addr is not None and self.region(addr):
            locs.append((addr, size if size in (1, 2, 4, 8) else 4))
        if kind == "float":
            for a, s, v, _pc in reversed(rec):
                if (s == 4 and f32(v) == val) or (s == 8 and struct.unpack("<d", struct.pack("<Q", v))[0] == val):
                    if (a, s) not in locs:
                        locs.append((a, s))
                    if len(locs) >= 3:
                        break
            return locs
        size = size if size in (1, 2, 4) else 4
        msk = _MASK[size]
        for a, s, v, _pc in reversed(rec):
            if s > 4:
                continue
            if s >= size:                   # e.g. a dword read compared as a byte: its low part
                ok, loc = (v & msk) == val, (a, size)
            else:                           # movzx / movsx of a narrower field
                ok = val == v or ((v >> (8 * s - 1)) & 1 and val == (v | (~_MASK[s] & msk)))
                loc = (a, s)
            if ok and loc not in locs:
                locs.append(loc)
                if len(locs) >= 3:
                    break
        for k, w in enumerate(inp.args):
            if w == val and ("arg", k) not in locs:
                locs.append(("arg", k))
                break
        for rn, w in inp.regs.items():
            if w == val:
                locs.append(("reg", rn))
                break
        return locs

    def _near_locations(self, val, size, rec):
        """[(location, delta)] for fields read shortly before the compare whose value differs from the
        operand by a small constant (`movsx ecx, byte [x]; dec ecx; cmp ecx, 12h`)."""
        size = size if size in (1, 2, 4) else 4
        msk = _MASK[size]
        out = []
        for a, s, v, _pc in reversed(rec):
            if s > 4:
                continue
            exts = {v & msk}
            if s < size and (v >> (8 * s - 1)) & 1:
                exts.add((v | (~_MASK[s] & msk)) & msk)
            for e in exts:
                d = (e - val) & msk
                d = d - (msk + 1) if d > msk // 2 else d
                if d and -4 <= d <= 4:
                    out.append(((a, min(s, size)), d))
                    break
            if len(out) >= 2:
                break
        return out

    def region(self, a):
        r = self.r
        if M.POOL_BASE <= a < M.POOL_BASE + M.POOL_SIZE:
            return "pool"
        if r.esp_entry + 4 <= a < r.args_hi:
            return "arg"
        if r.m.in_image_writable(a):
            return "data"
        return None

    def set_loc(self, inp, loc, val, kind):
        """Copy of inp with the location set to val; None if the location cannot be set."""
        out = inp.copy()
        if loc[0] == "arg":
            out.args[loc[1]] = val & 0xFFFFFFFF
            return out
        if loc[0] == "reg":
            out.regs[loc[1]] = val & 0xFFFFFFFF
            return out
        a, s = loc
        if kind == "float":
            try:
                raw = struct.pack("<f", val) if s == 4 else struct.pack("<d", val)
            except (OverflowError, struct.error):
                return None                 # a double boundary outside float range
        else:
            raw = (val & _MASK[s]).to_bytes(s, "little")
        reg = self.region(a)
        if reg is None:
            return None
        if reg == "arg":
            for j, byte in enumerate(raw):
                k, off = divmod(a + j - (self.r.esp_entry + 4), 4)
                words = out.args if k < len(out.args) else out.pad
                kk = k if k < len(out.args) else k - len(out.args)
                if kk >= len(words):
                    return None
                w = bytearray(struct.pack("<I", words[kk]))
                w[off] = byte
                words[kk] = struct.unpack("<I", bytes(w))[0]
            return out
        for j in range(0, len(raw)):
            a4 = (a + j) & ~3
            cur = self.dword(out, a4, reg)
            if cur is None:
                return None
            w = bytearray(struct.pack("<I", cur))
            w[(a + j) & 3] = raw[j]
            nv = struct.unpack("<I", bytes(w))[0]
            if reg == "pool":
                out.pool_over[a4] = nv
            else:
                out.overrides[a4] = nv
        return out

    def dword(self, inp, a4, reg):
        if reg == "pool":
            if a4 in inp.pool_over:
                return inp.pool_over[a4]
            slot = a4 & ~(M.SLOT - 1)
            pages = self.gen.slot_pages(inp, slot)
            pg = pages[a4 & ~0xFFF]
            return struct.unpack_from("<I", pg, a4 & 0xFFF)[0]
        if a4 in inp.overrides:
            return inp.overrides[a4]
        m = self.r.m
        for nm, lo, hi in m.writable:
            if lo <= a4 < hi:
                return struct.unpack_from("<I", m.image_base_page(nm, a4 & ~0xFFF), a4 & 0xFFF)[0]
        return None

    def _targets(self, ins, kind, ops, jins):
        """[(operand index, [values])]: values that move the compare across its boundary."""
        if kind == "float":
            x, y = ops[0][0], ops[1][0]
            if x is None or y is None or not (math.isfinite(x) and math.isfinite(y)):
                return []
            ys = [y, next32(y, True), next32(y, False)]
            xs = [x, next32(x, True), next32(x, False)]
            return [(0, ys), (1, xs)]
        if ins.id == X.X86_INS_JMP or self.byte_table is not None:
            v = ops[0][0]
            tbl = jins.operands[0].mem.disp & 0xFFFFFFFF
            ks = []
            cfg_targets = [d for (s, d) in self.r_cfg_edges(jins)]
            for k in range(256):
                try:
                    tg = self.r.m.u32(tbl + 4 * k)
                except Exception:
                    break
                if tg in cfg_targets and tg not in self.covered_targets(jins):
                    ks.append(k)
            if self.byte_table is not None:         # selectors whose byte entry is a missing case
                try:
                    bt = self.r.m.read(self.byte_table, 256)
                except Exception:
                    bt = b""
                ks = [x for k in ks for x in [i for i, b in enumerate(bt) if b == k][:2]]
            return [(0, ks[:8])] if ks else []
        mn = ins.mnemonic
        if len(ops) == 1:                            # inc/dec/neg/shift...: hit zero and the sign boundary
            v = ops[0][0]
            return [(0, [0, 1, 0xFFFFFFFF, 2, (v + 1), (v - 1)])]
        (x, sx, _ax, ix), (y, sy, _ay, iy) = ops[0], ops[1]
        msk = _MASK.get(sx, 0xFFFFFFFF)
        if mn == "test":
            if not iy and x == y:
                return [(0, [0, 1, msk, (msk >> 1) + 1])]
            return [(0, [x & ~y & msk, x | y, y, 0]), (1, [x & ~y & msk, x | y])]
        out = [(0, [y, (y + 1) & msk, (y - 1) & msk])]
        if not iy:
            out.append((1, [x, (x + 1) & msk, (x - 1) & msk]))
        return out

    def r_cfg_edges(self, jins):
        for side in (self.r.orig, self.r.ours):
            if jins.address in side.cfg.insns and side.cfg.insns[jins.address] is jins:
                return [e for e in side.cfg.edges if e[0] == jins.address]
        return []

    def covered_targets(self, jins):
        for side in (self.r.orig, self.r.ours):
            if side.cfg.insns.get(jins.address) is jins:
                return {d for (s, d) in side.edges if s == jins.address}
        return set()

    def _candidates(self, ins, kind, ops, rec, inp0, allocs, jins, rng):
        out = []
        for idx, vals in self._targets(ins, kind, ops, jins):
            if idx >= len(ops):
                continue
            val, size, addr, is_imm = ops[idx]
            if is_imm or val is None:
                continue
            if ins.id == X.X86_INS_JMP or self.byte_table is not None:
                # the index is the input, maybe off by a small constant (`dec ecx`): set it to each missing case
                locs = [(l, 0) for l in self._locations(val, 4, None, rec, inp0, "int")[:2]]
                locs += self._near_locations(val, 4, rec)
                for loc, d in locs:
                    for k in vals:
                        c = self.set_loc(inp0, loc, k + d, "int")
                        if c is not None:
                            out.append(c)
                continue
            ords = [k for k, p in allocs if p == val]
            if kind == "int" and M.DYN_BASE <= val < M.DYN_BASE + M.DYN_SIZE and 0 in vals and ords:
                c = inp0.copy()                     # a malloc result compared with 0: let that allocation fail
                c.alloc_fail = tuple(sorted(set(getattr(inp0, "alloc_fail", ())) | {ords[0]}))
                out.append(c)
                continue
            locs = self._locations(val, size, addr, rec, inp0, kind)
            for loc in locs:
                for v in vals:
                    c = self.set_loc(inp0, loc, v, kind)
                    if c is not None:
                        out.append(c)
            if kind == "int" and addr is None and not any(isinstance(l[0], int) for l in locs):
                for loc, d in self._near_locations(val, size, rec):
                    for v in vals:
                        c = self.set_loc(inp0, loc, v + d, kind)
                        if c is not None:
                            out.append(c)
            if kind == "int" and addr is None and (not locs or val == 0 or val < 0x100):
                out.extend(self._pair_candidates(rec, inp0, rng)[:8])
            if kind == "float" and not locs:
                out.extend(self._float_candidates(rec, inp0, vals)[:12])
        return out

    def _float_candidates(self, rec, inp0, vals):
        """The compared float is computed (|a - b|, a * k, ...): set one recent float field to the
        boundary value and the other recent float fields to 0."""
        fl = []
        for a, s, v, pc in reversed(rec):
            if s == 4 and pc in self.fpcs and self.region(a) in ("pool", "data", "arg") and (a, 4) not in fl:
                fl.append((a, 4))
            if len(fl) >= 4:
                break
        out = []
        for loc in fl:
            base = inp0
            for other in fl:
                if other != loc and base is not None:
                    base = self.set_loc(base, other, 0.0, "float")
            if base is None:
                continue
            for v in vals:
                c = self.set_loc(base, loc, v, "float")
                if c is not None:
                    out.append(c)
        return out

    def _pair_candidates(self, rec, inp0, rng):
        """The compared value is computed, not loaded: when it comes from two adjacent pointer fields
        (std::vector-style begin/end, a count from end - begin), make end = begin + a small size."""
        out = []
        seen = set()
        reads = {a: v for a, s, v, _pc in rec if s == 4 and self.region(a) in ("pool", "data")}
        for a, s, v, _pc in reversed(rec):
            if s != 4 or a in seen or (a - 4) not in reads:
                continue
            seen.add(a)
            u = reads[a - 4]
            base = inp0
            if not (M.POOL_BASE <= u < M.POOL_BASE + M.POOL_SIZE):
                u = self.gen.slot_ptr(rng)          # begin is not a pointer yet: make it one
                base = self.set_loc(inp0, (a - 4, 4), u, "int")
                if base is None:
                    continue
            for d in (0, 4, 8, 16, 32, 64, 0x60, 0xb4):
                c = self.set_loc(base, (a, 4), u + d * rng.choice((1, 2)), "int")
                if c is not None:
                    out.append(c)
            if len(out) >= 12:
                break
        return out

    def _loc_value(self, inp, loc):
        if loc[0] == "arg":
            return inp.args[loc[1]]
        if loc[0] == "reg":
            return inp.regs[loc[1]]
        a, s = loc
        reg = self.region(a)
        if reg is None or reg == "arg":
            return None
        cur = self.dword(inp, a & ~3, reg)
        return None if cur is None else (cur >> (8 * (a & 3))) & _MASK.get(s, 0xFFFFFFFF)
