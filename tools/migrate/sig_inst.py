#!/usr/bin/env python3
"""inst signal for modmap.py (design signal 6): template instantiations and compiler-generated
members that anchored as COMDAT or sandwiched follow the class they were instantiated for.

Rule.  For each function assigned below confidence 0.7 by `anchor-comdat` / `anchor-sandwiched`
whose name contains a template argument list or is a `scalar/vector deleting destructor'
($E static initialisers are skipped): collect the game classes it mentions (the enclosing class
of a deleting destructor, then every qualified identifier inside the template arguments, first
argument first), look each up in the class -> owner map of sig_vtable.class_owners (>= 2 unique
anchored methods, >= 90% in one module), and if they all agree take that module.  With no owner,
use the module of the function's direct callers (retail_feat calls, reversed) when every caller
is placed at conf >= 0.9 and they agree.  The module replaces the current one at confidence 0.7
(how = "inst") only if it differs AND it is a module that holds a dev copy of the same function
(ctx.dev_name_mods) -- the retail linker can only have kept a copy that existed.

Measured (all three hold-out seeds, identical to the full run): of ~590 low-confidence named
functions 441 are $E initialisers, ~80 are not instantiations, ~40 have no owner, 10 already
agree, 3-6 are blocked by the dev-copy check, and NONE are moved: inst adds 0 assignments and
leaves hold-out precision unchanged.  The population is too small (comdat anchors are 563 in
total) for the rule to matter; it is kept as a guard that fires when other signals change the
owner map.  Hidden anchors are never comdat, so hold-out cannot score it beyond 'no change'.
"""
import collections, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import sig_vtable as V

INST_CONF = 0.7
LOW = 0.7                  # only functions assigned below this confidence are re-examined
IDENT = re.compile(r"[A-Za-z_`][A-Za-z0-9_:`' ]*[A-Za-z0-9_']")


def template_args(part):
    """Text inside the outermost <...> of a name component, or ''."""
    i = part.find("<")
    if i < 0 or not part.endswith(">"):
        return ""
    return part[i + 1:-1]


def class_tokens(text):
    """Qualified identifiers (A::B::C) occurring in a template argument list, in order."""
    out, depth, cur, i = [], 0, "", 0
    # a token is a maximal run of identifier characters and '::' at any nesting depth
    for m in re.finditer(r"`?[A-Za-z_][A-Za-z0-9_]*(?:'?(?:::`?[A-Za-z_][A-Za-z0-9_]*'?)*)", text):
        out.append(m.group(0))
    return out


def game_class_candidates(name):
    """Class names a template instantiation / compiler-generated member may belong to:
    enclosing class of a `scalar deleting destructor', then every identifier inside template
    arguments of the enclosing class (first argument first)."""
    parts = V.split_top(name)
    if len(parts) < 2:
        return []
    enclosing = parts[:-1]
    cands = []
    method = parts[-1]
    if method.startswith("`scalar deleting") or method.startswith("`vector deleting"):
        cands.append("::".join(enclosing))
    for comp in enclosing:
        args = template_args(comp)
        if args:
            cands.extend(class_tokens(args))
    # the method itself may be a template (eastl::make_heap<T *,...> free functions)
    margs = template_args(method)
    if margs:
        cands.extend(class_tokens(margs))
    return cands


def owner_of_name(owners, name):
    """Module owning the game class named in `name`, or None when absent / ambiguous."""
    mods = []
    for c in game_class_candidates(name):
        o = owners.get(c)
        if o:
            mods.append(o["module"])
    if mods and len(set(mods)) == 1:
        return mods[0]
    return None


def apply(ctx):
    owners = getattr(ctx, "_vt_owners", None) or V.class_owners(ctx)
    callers = getattr(ctx, "_inst_callers", None)
    if callers is None:
        callers = collections.defaultdict(set)
        for k, f in ctx.retail_feat.items():
            for c in f["calls"]:
                callers[int(c, 16) if isinstance(c, str) else c].add(int(k, 16))
        ctx._inst_callers = callers
    stats = collections.Counter()
    moved = []
    for va in sorted(ctx.assign):
        e = ctx.assign[va]
        if e["confidence"] >= LOW or not e.get("name") or not e["how"].startswith("anchor"):
            continue
        name = e["name"]
        if name.startswith("$"):
            stats["static-init"] += 1
            continue
        generated = "<" in name or "`scalar deleting" in name or "`vector deleting" in name
        if not generated:
            stats["not-instantiation"] += 1
            continue
        dev_mods = ctx.dev_name_mods.get(ctx.dev[e["dev"]][1], set()) if e.get("dev") in ctx.dev else set()
        m = owner_of_name(owners, name)
        src = "class"
        if m is None:
            # fall back to the callers' module when they all agree
            cm = {ctx.assign[c]["module"] for c in callers.get(va, ()) if c in ctx.assign
                  and ctx.assign[c]["confidence"] >= 0.9}
            if len(cm) == 1:
                m = next(iter(cm))
                src = "callers"
        if m is None:
            stats["no-owner"] += 1
            continue
        if m == e["module"]:
            stats["agrees-" + src] += 1
            continue
        if dev_mods and m not in dev_mods:
            stats["owner-not-a-dev-copy-" + src] += 1
            continue
        old = e["module"]
        if ctx.set(va, m, "inst", INST_CONF):
            stats["moved-" + src] += 1
            moved.append((va, old, m, src))
    ctx.inst_stats = dict(stats)
    ctx.inst_moved = moved
    if os.environ.get("VT_EVAL"):
        print("  [inst]", dict(stats))
