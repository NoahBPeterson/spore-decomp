"""library: place what no signal could put in an object into its library (top directory).

Retail .text is library-major: walking the placements of confidence >= 0.7 in address order, each top
directory of the dev build (SPBake, SPEditors, SPEngine, Spui, UTFSpore_Win32, SPCreatureAnim, SPAudio,
Swarm, SPGonzago, SPTerrain, SPMovie, Native Release, ...) is one or two long blocks with few small
interruptions (2026-11-01).  Which object of the library a function is in can stay unknown while the
library is not.

  component (0.3)  inside a range of symbols/components.json without a dev-build directory (Havok 3.1.0,
                   linked from prebuilt hk*.lib): that component.  Its few placed functions there are
                   misnamed anchors: the component replaces them (listed under
                   "conflicts") and they do not act as flanks.
  library (0.3)    the two nearest placements of confidence >= FLANK_CONF on each side are all in one
                   directory: that directory.

The module key is `<dir>/_at_<va & ~0xffff>.obj`: one TU per 64 KB of retail address space inside the
library (src/game/<dir>/_at_<...>.cpp), a name that does not move when better signals take functions
out of it.

Hold-out (3 seeds x 20% of the unique anchors): see docs/migration.md, "library".
"""
import bisect, json, os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FLANK_CONF = 0.7
FLANKS = 2
COMPONENT_DIRS = {"Havok 3.1.0": "Havok"}


def _key(d, va):
    return "%s/_at_%08x.obj" % (d, va & ~0xffff)


def apply(ctx):
    comp = json.load(open(os.path.join(ROOT, "symbols", "components.json")))
    ranges = [(int(lo, 16), int(hi, 16), COMPONENT_DIRS[n]) for n, rs in comp.items()
              if n in COMPONENT_DIRS for lo, hi in rs]
    in_comp = lambda va: next((d for lo, hi, d in ranges if lo <= va < hi), None)
    for va in ctx.order:
        d = in_comp(va)
        if not d:
            continue
        prev = ctx.assign.get(va)
        if prev:
            # the range is instruction-identical to the dev build's prebuilt hk*.lib; the game anchors inside it
            # are xmatch misnames (0x010840e0 "SP::cSPEditorVerbIcon::InitializeSize" references
            # .\world\hkWorld.cpp, 0x01083570 "cTribePlannerWindow::UpdateList" Havok's broadphase timers)
            ctx.conflicts.append(dict(va="%08x" % va, name=prev.get("name"), kept=_key(d, va), kept_how="component",
                                      other=prev["module"], other_how=prev["how"]))
        ctx.assign[va] = dict(module=_key(d, va), how="component", confidence=0.3, name=None, dev=None)
    strong = [va for va in ctx.order if va in ctx.assign and ctx.assign[va]["confidence"] >= FLANK_CONF
              and not in_comp(va)]
    lib = lambda va: ctx.assign[va]["module"].split("/")[0]
    for va in ctx.order:
        if va in ctx.assign:
            continue
        i = bisect.bisect_left(strong, va)
        if i < FLANKS or i + FLANKS > len(strong):
            continue
        ds = {lib(x) for x in strong[i - FLANKS:i + FLANKS]}
        if len(ds) == 1:
            d = ds.pop()
            ctx.set(va, _key(d, va), "library", 0.3)
