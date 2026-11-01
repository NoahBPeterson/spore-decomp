"""order: fill the gaps between runs from the order in which retail links its object files.

Within one directory (one library project), retail links its objects in alphabetical order of their
file name, like a project file list: 622 of 706 consecutive pairs of runs with at least two anchors
each are alphabetical (2026-11-01); most of the rest are restarts at a filter-folder boundary
(`XHTMLFrameSet.obj` -> `HitMaskFactory.obj`).  Dev link order is no help (53% ascending, and the
dev build does not keep half of its own objects contiguous), so this signal uses names only.

Rules, applied after every other signal, to still-unassigned functions only, repeated until nothing
changes (splits re-vote with the functions placed in the previous round):

  order-enclosed (0.7)  a gap whose flanking runs are the same module M: an object is contiguous,
                        so the gap is M's (the anchors' dev order or a wide count kept interp out).
                        Not when a flank is itself an order-split placement (44-54% in hold-out).
  order-split (0.8)     a gap between modules A and B with no unplaced module of A's or B's
                        directory whose name sorts between them: A's tail then B's head.  The split
                        point maximises agreement with per-function votes, and only functions whose
                        own votes agree with their side are assigned.
  order-split-ev (0.5)  the same where an unplaced module does sort in between but leaves no trace
                        in the gap (no gap function uses a feature unique to that module in the dev
                        build): most of the 768 dev objects without a placed function are not in
                        retail at all (247 of the 282 with unique features show none of them).

Votes of a gap function for A or B: its assigned direct callers and callees, and its features
(string literals, constants >= 0x10000, imports) that only A's or only B's functions use in the
dev build (work/xmatch/dev.json).

Hold-out (5 seeds x 20% of the unique anchors, single pass, 2026-11-01): order-enclosed 88.9%
(91.3% outside template instantiations, whose dev object is wherever the dev linker kept the COMDAT),
order-split 92.2%, order-split-ev 79.3%.  Rejected: assigning the functions between the split point
and the votes by position (60.0% with the name gate, 37.9% without); a split in proportion to the
dev functions left on each side (55-60%); votes from shared .data/.rdata addresses (lowered the
splits); gating only on traces (60.8% before votes were per function).
"""
import collections, json, os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ROUNDS = 5


def _key(module):
    return module.split("/")[-1].lower()


def _dir(module):
    return module.split("/")[0]


def _feats(v):
    """Features of one function row (retail.json / dev.json) that can name its object: string
    literals of 4+ characters, constants >= 0x10000, imports."""
    f = {("s", x) for x in v.get("strs", []) if isinstance(x, str) and len(x) >= 4}
    f |= {("c", x) for x in v.get("consts", []) if isinstance(x, int) and abs(x) >= 0x10000}
    f |= {("i", x) for x in v.get("imps", [])}
    return f


def unique_features(ctx):
    """{retail va: set of dev modules} for retail functions that use a feature which, in the dev
    build, only one module's functions use."""
    owners = collections.defaultdict(set)
    for k, v in json.load(open(os.path.join(ROOT, "work", "xmatch", "dev.json"))).items():
        d = ctx.dev.get(int(k, 16))
        if d:
            for f in _feats(v):
                owners[f].add(d[0])
    uniq = {f: next(iter(ms)) for f, ms in owners.items() if len(ms) == 1}
    out = collections.defaultdict(set)
    for k, v in ctx.retail_feat.items():
        for f in _feats(v):
            if f in uniq:
                out[int(k, 16)].add(uniq[f])
    return out


def apply(ctx):
    callers = collections.defaultdict(set)
    callees = {}
    for k, v in ctx.retail_feat.items():
        va = int(k, 16)
        cs = {int(c, 16) for c in v.get("calls", [])}
        callees[va] = cs
        for c in cs:
            callers[c].add(va)
    ufeat = unique_features(ctx)
    stats = collections.Counter()
    for _ in range(ROUNDS):
        n = _round(ctx, callers, callees, ufeat, stats)
        stats["rounds"] += 1
        if not n:
            break
    ctx.order_stats = dict(stats)


def _flank_how(ctx, g):
    """The weaker `how` of the two assigned functions flanking gap g."""
    i = ctx.order.index(g["lo"])
    j = ctx.order.index(g["hi"])
    a = ctx.assign.get(ctx.order[i - 1]) if i else None
    b = ctx.assign.get(ctx.order[j + 1]) if j + 1 < len(ctx.order) else None
    return min((e for e in (a, b) if e), key=lambda e: e["confidence"])["how"]


def _round(ctx, callers, callees, ufeat, stats):
    placed = {e["module"] for e in ctx.assign.values()}
    absent = collections.defaultdict(list)
    for m in ctx.dev_by_module:
        if m not in placed:
            absent[_dir(m)].append(m)
    before = len(ctx.assign)

    for g in ctx.gaps():
        if g["before"] and g["before"] == g["after"]:
            if _flank_how(ctx, g).startswith("order-split"):
                continue   # between two split placements: 44-54% in hold-out
            for va in g["vas"]:
                ctx.set(va, g["before"], "order-enclosed", 0.7)

    for g in ctx.gaps():
        A, B = g["before"], g["after"]
        if not A or not B or A == B:
            continue
        ka, kb = _key(A), _key(B)
        if ka < kb:
            between = lambda k: ka < k < kb
        else:   # a folder restart: A's folder tail or B's folder head
            between = lambda k: k > ka or k < kb
        if not [m for d in {_dir(A), _dir(B)} for m in absent.get(d, []) if between(_key(m))]:
            how, conf = "order-split", 0.8
        elif not {m for va in g["vas"] for m in ufeat.get(va, ()) if m not in placed}:
            how, conf = "order-split-ev", 0.5
        else:
            stats["skip-traces"] += 1
            continue
        vas = g["vas"]
        votes = []
        for va in vas:
            a = b = 0
            for nb in callees.get(va, set()) | callers.get(va, set()):
                m = ctx.module_of(nb)
                a += m == A
                b += m == B
            fm = ufeat.get(va, ())
            a += A in fm
            b += B in fm
            votes.append((a, b))
        if not any(a != b for a, b in votes):
            stats["skip-novotes"] += 1
            continue
        # split k maximises sum_{i<k} (a_i - b_i) + sum_{i>=k} (b_i - a_i) = 2 pre[k] - pre[n]
        pre = [0]
        for a, b in votes:
            pre.append(pre[-1] + a - b)
        bk = max(range(len(vas) + 1), key=lambda k: (pre[k], -k))
        for i, va in enumerate(vas):
            a, b = votes[i]
            if (i < bk and a > b) or (i >= bk and b > a):
                ctx.set(va, A if i < bk else B, how, conf)
    return len(ctx.assign) - before
