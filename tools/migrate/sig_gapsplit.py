"""gapsplit: place the unnamed functions at the edges of a gap from the flanking runs and the
dev build's function sequence (design signal 5 of docs/migration.md, in its simplest robust form).

Rule.  Every gap (ctx.gaps()) lies between the last function of run A (module MA) and the first of
run B (module MB).  Raw dev function COUNTS are a poor bound: between consecutive same-module
anchors retail holds only ~15% of the dev functions (median 21%; the dev build emits every inline
accessor and template instance, retail inlines or folds them), and a count test alone (the
"n <= tA + slack" rule) hit only 55-75% on hold-out.  So the dev side is filtered to the
functions retail plausibly keeps (size >= 32 bytes, no '<' in the name, name unique to the
module, dev VA not already claimed by a retail anchor) and the evidence is the ORDERED SIZE
SEQUENCE: retail/dev sizes agree within 0.6..1.7 for 92% of anchors.

  same        MA == MB, both runs hold a unique anchor (this is a pair interp refused to span
              because it runs against its chain's dev direction): the whole gap is MA when
              n <= span + 2, where span = unclaimed dev functions of MA between the two
              counterparts (any direction).                          gapsplit-same        0.8
              n <= 2*span + 4 (interp's own WIDE bound).             gapsplit-same-wide   0.5
  tail/head   otherwise take A's last unique anchor, list the filtered dev functions beyond it in
              the run's direction (direction = majority of the run's anchor dev VAs; with one
              anchor try both and accept only if exactly one direction aligns), and find the
              longest k such that the first k gap sizes align with the first k dev sizes (>= 85%
              of positions within the ratio window, the k-th matching).  The first k gap
              functions go to MA.  Symmetrically the last k go to MB from B's first anchor.
              k >= 5                                                  gapsplit-tail / -head 0.8
              k = 3..4                                                gapsplit-short        0.5
              If the two claims overlap, the overlap is dropped (MA != MB) or only A is taken.
  The middle of a gap larger than the two aligned ends is left unassigned (it holds anchorless
  modules or library code); that is why most of the 62k remaining functions stay in gaps.

Data: ctx.anchors (dev VAs), ctx.dev_by_module / ctx.dev (sizes, names), retail sizes.  No cache
needed; a full modmap run takes ~2 s.

Measured (hold-out 0.2, seeds 1-6 pooled; 0.5 for the thin tiers; hidden anchors in the stretch):
  gapsplit-same        446 right /  18 wrong  96.1%   (every seed 95.7-98.6%)
  gapsplit-same-wide    61 /  3 95.3%  (0.5: 50 / 0)
  gapsplit-tail         46 /  1 97.9%  (0.5: 127 / 1  99.2%)
  gapsplit-head         28 /  1 96.6%  (0.5:  85 / 5  94.4%)
  gapsplit-short       133 / 11 92.4%  (0.5: 254 / 12 95.5%)
  The 3% xmatch name error caps what hold-out can show at ~97%; most 'wrong' cases are
  callee-single anchors whose own module is doubtful.  CAVEAT: hold-out gaps are artificial (cut
  by a hidden anchor, so the truth is usually MA or MB); real gaps more often hold anchorless
  modules, so head/tail/short precision on the real gaps is probably a few points lower.
Full run (anchor,interp,gapsplit): +2,851 functions: same 1813 fn 508 KB, same-wide 222 / 56 KB,
tail 191 / 46 KB, head 283 / 48 KB, short 342 / 91 KB.  Gaps in the anchor+interp state: 1933 ->
380 closed, 122 partly closed, 1431 untouched.
"""
import bisect

LO, HI = 0.6, 1.7            # retail/dev size ratio accepted as "same function"
MIN_SIZE = 32                # dev functions below this are mostly inline accessors retail dropped
MIN_K = 3                    # shortest aligned prefix/suffix that is assigned at all
STRONG_K = 5                 # aligned length for the main tier
THR = 0.85                   # fraction of the aligned window whose sizes must agree
SAME_SLACK, SAME_FACTOR = 2, 1.0
WIDE_SLACK, WIDE_FACTOR = 4, 2.0


def _is_candidate(ctx, v):
    m, name, size, _loc = ctx.dev[v]
    return size >= MIN_SIZE and "<" not in name and len(ctx.dev_name_mods[name]) == 1


def _run_info(ctx, runs):
    uniq = sorted(va for va, a in ctx.anchors.items() if not a["comdat"] and not a.get("sandwiched"))
    for r in runs:
        i = bisect.bisect_left(uniq, r["lo"])
        j = bisect.bisect_right(uniq, r["hi"])
        mine = [v for v in uniq[i:j] if ctx.anchors[v]["module"] == r["module"]]
        r["uanch"] = mine
        up = dn = 0
        for a, b in zip(mine, mine[1:]):
            da, db = ctx.anchors[a]["dev"], ctx.anchors[b]["dev"]
            up += db > da
            dn += db < da
        r["dir"] = 1 if up > dn else -1 if dn > up else 0
    return runs


def _dev_lists(ctx, r, side, claimed):
    """Candidate dev-size sequences beyond the run's last unique anchor ('tail', toward higher
    retail VAs) or before its first ('head'), nearest-to-anchor first, one per possible direction.
    Returns a list of (direction, sizes)."""
    if not r["uanch"]:
        return []
    va = r["uanch"][-1] if side == "tail" else r["uanch"][0]
    d = ctx.anchors[va]["dev"]
    vs = ctx.dev_by_module[r["module"]]
    k = bisect.bisect_left(vs, d)
    above = [ctx.dev[v][2] for v in vs[k + 1:] if v not in claimed and _is_candidate(ctx, v)]
    below = [ctx.dev[v][2] for v in vs[:k][::-1] if v not in claimed and _is_candidate(ctx, v)]
    out = {}
    if r["dir"] in (1, 0):
        out[1] = above if side == "tail" else below
    if r["dir"] in (-1, 0):
        out[-1] = below if side == "tail" else above
    return list(out.items())


def _ok(a, b):
    return b > 0 and LO <= a / b <= HI


def _prefix(gs, s):
    """Longest k <= min(len(gs), len(s)) whose first k sizes align >= THR with the k-th matching."""
    best = 0
    hits = 0
    for k in range(1, min(len(gs), len(s)) + 1):
        hits += _ok(gs[k - 1], s[k - 1])
        if _ok(gs[k - 1], s[k - 1]) and hits >= THR * k:
            best = k
    return best


def apply(ctx):
    claimed = {a["dev"] for a in ctx.anchors.values()}
    runs = _run_info(ctx, ctx.runs())
    by_hi = {r["hi"]: r for r in runs}
    by_lo = {r["lo"]: r for r in runs}
    pos = {v: i for i, v in enumerate(ctx.order)}
    for g in ctx.gaps():
        vas, n = g["vas"], g["n"]
        sizes = [ctx.retail[v] for v in vas]
        i0, i1 = pos[g["lo"]], pos[g["hi"]]
        ra = by_hi.get(ctx.order[i0 - 1]) if i0 > 0 and g["before"] else None
        rb = by_lo.get(ctx.order[i1 + 1]) if i1 + 1 < len(ctx.order) and g["after"] else None
        ka = kb = 0
        if ra and rb and g["before"] == g["after"]:
            hc = _same(ctx, ra, rb, n, claimed)
            if hc:
                for v in vas:
                    ctx.set(v, g["before"], hc[0], hc[1])
                continue
        if ra:
            ks = {d: _prefix(sizes, s) for d, s in _dev_lists(ctx, ra, "tail", claimed)}
            ka = _decide(ks)
        if rb:
            ks = {d: _prefix(sizes[::-1], s) for d, s in _dev_lists(ctx, rb, "head", claimed)}
            kb = _decide(ks)
        if ka < MIN_K: ka = 0
        if kb < MIN_K: kb = 0
        if ka + kb > n:                       # claims overlap: give up the overlap
            if ka and kb and g["before"] != g["after"]:
                ov = ka + kb - n
                ka -= (ov + 1) // 2
                kb -= ov // 2
                ka, kb = (ka if ka >= MIN_K else 0), (kb if kb >= MIN_K else 0)
            else:
                ka = min(ka, n); kb = 0 if g["before"] == g["after"] else min(kb, n - ka)
        for v in vas[:ka]:
            ctx.set(v, g["before"], *(("gapsplit-tail", 0.8) if ka >= STRONG_K else ("gapsplit-short", 0.5)))
        for v in vas[n - kb:] if kb else []:
            ctx.set(v, g["after"], *(("gapsplit-head", 0.8) if kb >= STRONG_K else ("gapsplit-short", 0.5)))


def _same(ctx, ra, rb, n, claimed):
    """Both flanking runs are the same module and each has a unique anchor: the gap sits between
    two consecutive unique anchors of one module that interp refused to span (pair against its
    chain's direction).  Returns (how, confidence) when n fits the number of unclaimed dev
    functions between the two counterparts, else None."""
    if not ra["uanch"] or not rb["uanch"]:
        return None
    da, db = ctx.anchors[ra["uanch"][-1]]["dev"], ctx.anchors[rb["uanch"][0]]["dev"]
    lo, hi = min(da, db), max(da, db)
    vs = ctx.dev_by_module[ra["module"]]
    span = sum(1 for v in vs[bisect.bisect_right(vs, lo):bisect.bisect_left(vs, hi)] if v not in claimed)
    if n <= SAME_FACTOR * span + SAME_SLACK:
        return "gapsplit-same", 0.8
    if n <= WIDE_FACTOR * span + WIDE_SLACK:
        return "gapsplit-same-wide", 0.5
    return None


def _decide(ks):
    if not ks:
        return 0
    if len(ks) == 1:
        return next(iter(ks.values()))
    a, b = sorted(ks.values())
    return b if a == 0 else 0                 # two directions possible: accept only if one fails
