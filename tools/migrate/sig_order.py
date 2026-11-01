"""order: fill the gaps between runs from the order in which retail links its object files.

Within one directory (one library project), retail links its objects in alphabetical order of their
file name, like a project file list: 622 of 706 consecutive pairs of runs with at least two anchors
each are alphabetical (2026-11-01); most of the rest are restarts at a filter-folder boundary
(`XHTMLFrameSet.obj` -> `HitMaskFactory.obj`).  Dev link order is no help (53% ascending, and the
dev build does not keep half of its own objects contiguous), so this signal uses names only.

Rules, applied after every other signal, to still-unassigned functions only:

  order-enclosed (0.7)  a gap whose flanking runs are the same module M: an object is contiguous,
                        so the gap is M's (the anchors' dev order or a wide count kept interp out).
  order-split (0.5)     a gap between modules A and B with no candidate in between (no unplaced
                        module of A's or B's directory whose name sorts between them): A's tail then
                        B's head.  The split point maximises call-graph agreement: each function
                        votes with the modules of its assigned direct callers and callees (A or B
                        only).
  A gap without votes stays unassigned: splitting it in proportion to the dev functions left on each
  side was right only 55-60% of the time.  Data-reference votes (functions sharing .data/.rdata
  addresses) lowered the split precision from 73% to 69% and are not used.

Hold-out (5 seeds x 20% of the unique anchors, 2026-11-01): order-enclosed 88.9% (91.3% outside
template instantiations, whose dev object is wherever the dev linker kept the COMDAT), order-split
72.7% (75.1% outside templates).

Gaps with an unplaced candidate module in between are left alone (they need size alignment
against that module's dev functions, which is sig_gapsplit's domain).
"""
import collections


def _key(module):
    return module.split("/")[-1].lower()


def _dir(module):
    return module.split("/")[0]


def apply(ctx):
    callers = collections.defaultdict(set)
    callees = {}
    for k, v in ctx.retail_feat.items():
        va = int(k, 16)
        cs = {int(c, 16) for c in v.get("calls", [])}
        callees[va] = cs
        for c in cs:
            callers[c].add(va)

    placed = {e["module"] for e in ctx.assign.values()}
    absent = collections.defaultdict(list)
    for m in ctx.dev_by_module:
        if m not in placed:
            absent[_dir(m)].append(m)

    stats = collections.Counter()

    # 1. enclosed gaps
    for g in ctx.gaps():
        if g["before"] and g["before"] == g["after"]:
            for va in g["vas"]:
                ctx.set(va, g["before"], "order-enclosed", 0.7)
            stats["enclosed-gaps"] += 1

    # 2. two-way splits, votes from the assignment after step 1
    for g in ctx.gaps():
        A, B = g["before"], g["after"]
        if not A or not B or A == B:
            continue
        ka, kb = _key(A), _key(B)
        if ka < kb:
            between = lambda k: ka < k < kb
        else:   # a folder restart: A's folder tail or B's folder head
            between = lambda k: k > ka or k < kb
        cands = [m for d in {_dir(A), _dir(B)} for m in absent.get(d, []) if between(_key(m))]
        if cands:
            stats["skip-candidates"] += 1
            continue
        vas = g["vas"]
        votes = []
        for va in vas:
            a = b = 0
            for n in callees.get(va, set()) | callers.get(va, set()):
                m = ctx.module_of(n)
                a += m == A
                b += m == B
            votes.append((a, b))
        if any(a or b for a, b in votes):
            # score(k) = sum_{i<k} a_i - b_i  (B's votes on A's side count against it) + sum_{i>=k} b_i - a_i
            n = len(vas)
            pre = [0]
            for a, b in votes:
                pre.append(pre[-1] + a - b)
            tot_b = sum(b - a for a, b in votes)
            best, bk = None, 0
            for k in range(n + 1):
                # sum_{i>=k} (b_i - a_i) = tot_b - sum_{i<k} (b_i - a_i) = tot_b + pre[k]
                s = pre[k] + tot_b + pre[k]
                if best is None or s > best:
                    best, bk = s, k
            how, conf = "order-split", 0.5
            stats["split-voted"] += 1
        else:
            # no votes: a split in proportion to the dev functions left on each side was right only
            # 55-60% of the time in hold-out (five seeds, 2026-11-01), so the gap stays unassigned
            stats["split-novotes"] += 1
            continue
        for i, va in enumerate(vas):
            ctx.set(va, A if i < bk else B, how, conf)
    ctx.order_stats = dict(stats)

