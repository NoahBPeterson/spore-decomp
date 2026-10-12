"""callgraph: place unnamed functions by the modules of their already-assigned call neighbours.

Rule (design signal 4 of docs/migration.md).  Static helpers and private methods are compiled into
the object file that uses them, so an unassigned function whose assigned direct callers and callees
all sit in one module M lives in M -- provided M is also physically adjacent.  Evidence is the
retail direct-call graph (work/xmatch/retail.json "calls", reverse map built here); neighbours with
confidence >= 0.6 count (comdat anchors and weak tiers do not).  Each round looks only at still
unassigned functions; main-tier assignments of earlier rounds count as evidence in later ones
(up to 4 rounds, the loop stops when a round adds nothing).

A function stays unassigned when:
  excl-lib       its VA is in symbols/lib_names.txt (CRT/library, 1,947 functions);
  excl-shared    its direct callers span >= 3 distinct assigned modules (shared helper);
  excl-disagree  its assigned callers+callees name more than one module;
  excl-noflank   the voted module is neither the module of the nearest assigned function before it
                 nor of the nearest one after it in address order (the gap's flanking runs).
                 Retail .text is module-major, so a function cannot sit in an object whose code is
                 elsewhere; this is the decisive filter: without it hold-out precision is 63-76%,
                 and a vote that matches no flank is right 9% of the time;
  excl-far       M has no assigned function within 10 functions (address-order index distance).

Tiers (evidence-order index distance d = to the nearest assigned function of M; n = agreeing
neighbours; a "-rN" suffix marks round N >= 2, i.e. derivative on callgraph's own output):
  callgraph        0.8 (0.7 in rounds >= 2)   flank match, d <= 5, n >= 2
  callgraph-weak   0.5                        flank match, round 1 only, d <= 5 with n = 1, or
                                              d 6..10 with n >= 2
Dropped as imprecise: "far" (no run of M within 64 fns): 0 of 13 right; n = 1 with d > 5: ~74%;
d > 10: 55-67%; weak in rounds >= 2: ~84%.  The number of agreeing neighbours barely matters once
the flank/near test holds (n = 1: 94%, n >= 2: 95%), so n only separates the tiers.

Data: work/xmatch/retail.json (calls), symbols/lib_names.txt.  Runtime ~2 s, no cache needed.

Measured (anchor,interp,callgraph; hold-out hides unique anchors; only hidden anchors that fall to
this signal count, which is a small sample: 5-25 per seed at 0.2).  Pooled with 6 seeds at 0.5 /
0.3 for statistics (both keep the same rule):
  tier             full-run fn   KB      hold-out 0.2 seeds 1/2/3 (right/wrong)    pooled 0.5 x3
  callgraph          110       20.8      8/1  5/0  8/1  (88.9, 100, 88.9%)        85/4 = 95.5%
  callgraph-r2         2        0.3      (inside the above when hit)               9/0
  callgraph-weak     404       97.7      16/1  21/1  25/3 (94.1, 95.5, 89.3%)     186/12 = 93.9%
Full run: 28,781 assigned = 31.8% by count, 48.2% by size (was 28,265 = 31.2% / 47.4%): +516
functions, +118.7 KB.  Exclusions (round 1): lib 1,947, shared 965, disagree 6,895, noflank 9,233,
far 553.  Fan-in (distinct direct callers) of the 62,202 unassigned functions at the start:
0: 44,062; 1: 10,501; 2: 3,235; 3: 1,450; 4: 760; 5: 496; 6: 309; 7: 237; 8: 190; 9: 120; >=10: 842.
Most unassigned functions have NO direct caller (virtual methods reached through vtables), which is
why the call graph can only move 0.6% of them; the vtable signal is the way into that population.
"""
import bisect, collections, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

SHARED_MODS = int(os.environ.get("CG_SHARED", 3))  # callers from this many distinct modules = shared helper
MIN_CONF = 0.6       # neighbours below this (comdat 0.5, weak tiers) are not evidence
MIN_VOTES = int(os.environ.get("CG_VOTES", 2))
MAIN_D = int(os.environ.get("CG_MAIND", 5))       # main tier: voted module has an assigned fn this close
WEAK_D = int(os.environ.get("CG_WEAKD", 10))
WEAK = bool(int(os.environ.get("CG_WEAK", "1")))
MAX_ROUNDS = int(os.environ.get("CG_ROUNDS", 4))
LATE_CONF = float(os.environ.get("CG_LATE", 0.7))  # confidence of round >= 2 main-tier assignments
CG_TRACE = bool(int(os.environ.get("CG_TRACE", "0")))


def _libset():
    s = set()
    p = os.path.join(ROOT, "symbols", "lib_names.txt")
    for line in open(p):
        if line.startswith("#"):
            continue
        t = line.split()
        if len(t) >= 2:
            try:
                s.add(int(t[0], 16))
            except ValueError:
                pass
    return s


def graph(ctx):
    g = getattr(ctx, "_cg_graph", None)
    if g is None:
        callees = {}
        callers = collections.defaultdict(set)
        for k, v in ctx.retail_feat.items():
            va = int(k, 16)
            cs = {int(c, 16) for c in v.get("calls", ())}
            cs.discard(va)
            cs = {c for c in cs if c in ctx.retail}
            callees[va] = cs
            for c in cs:
                callers[c].add(va)
        g = ctx._cg_graph = (callees, callers)
    return g


def apply(ctx):
    callees, callers = graph(ctx)
    lib = _libset()
    order = ctx.order
    idx = {va: i for i, va in enumerate(order)}
    st = collections.Counter()
    ctx.cg_stats = st
    ctx.cg_trace = []
    fan = collections.Counter()      # fan-in (distinct direct callers) of the unassigned, first round

    for rnd in range(1, MAX_ROUNDS + 1):
        mod_idx = collections.defaultdict(list)     # module -> sorted order-indices of assigned fns
        for va, e in ctx.assign.items():
            mod_idx[e["module"]].append(idx[va])
        for l in mod_idx.values():
            l.sort()
        # nearest assigned function before / after each index, found by one sweep
        prev_mod = [None] * len(order)
        last = None
        for i, va in enumerate(order):
            prev_mod[i] = last
            if va in ctx.assign:
                last = ctx.assign[va]["module"]
        next_mod = [None] * len(order)
        last = None
        for i in range(len(order) - 1, -1, -1):
            next_mod[i] = last
            if order[i] in ctx.assign:
                last = ctx.assign[order[i]]["module"]

        def near(mod, i):
            l = mod_idx.get(mod)
            if not l:
                return 10 ** 9
            j = bisect.bisect_left(l, i)
            d = 10 ** 9
            if j < len(l):
                d = min(d, l[j] - i)
            if j > 0:
                d = min(d, i - l[j - 1])
            return d

        new = []
        for i, va in enumerate(order):
            if va in ctx.assign:
                continue
            if rnd == 1:
                fan[min(len(callers.get(va, ())), 10)] += 1
            if va in lib:
                if rnd == 1:
                    st["excl-lib"] += 1
                continue
            cm = collections.Counter()   # modules of the assigned direct callers
            for c in callers.get(va, ()):
                e = ctx.assign.get(c)
                if e and e["confidence"] >= MIN_CONF:
                    cm[e["module"]] += 1
            if len(cm) >= SHARED_MODS:
                st["excl-shared-r%d" % rnd] += 1
                continue
            votes = collections.Counter(cm)
            for c in callees.get(va, ()):
                e = ctx.assign.get(c)
                if e and e["confidence"] >= MIN_CONF:
                    votes[e["module"]] += 1
            if not votes:
                continue
            if len(votes) > 1:
                st["excl-disagree-r%d" % rnd] += 1
                continue
            mod, n = next(iter(votes.items()))
            if mod != prev_mod[i] and mod != next_mod[i]:
                st["excl-noflank-r%d" % rnd] += 1
                continue
            d = near(mod, i)
            if CG_TRACE:
                ctx.cg_trace.append(dict(va=va, rnd=rnd, mod=mod, n=n, d=d, ncaller=sum(cm.values()),
                                         flank=(mod == prev_mod[i]) + (mod == next_mod[i]), size=ctx.retail[va]))
            new.append((va, mod, n, d))
        added = 0
        for va, mod, n, d in new:
            sfx = "" if rnd == 1 else "-r%d" % rnd
            if d <= MAIN_D and n >= MIN_VOTES:
                ctx.set(va, mod, "callgraph" + sfx, 0.8 if rnd == 1 else LATE_CONF)
            elif WEAK and rnd == 1 and (d <= MAIN_D or (d <= WEAK_D and n >= MIN_VOTES)):
                ctx.set(va, mod, "callgraph-weak" + sfx, 0.5)
            else:
                st["excl-far-r%d" % rnd] += 1
                continue
            added += 1
        st["round%d" % rnd] = added
        if not added:
            break
    ctx.cg_fanin = dict(sorted(fan.items()))
