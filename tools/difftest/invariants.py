#!/usr/bin/env python3
"""Input-object invariants: stop mis-counting "the random input built an impossible object" as a code FAIL.

A differential run feeds the function pointer soup. For most functions that is fine: any dword is a value
the function may legitimately see. Some functions, though, read a *length field* out of that object and use
it to index an array whose extent is fixed by the FUNCTION's own code or by the object's declared type:

  * `face::count` (+0xb0) indexes the local `vector4 v[4]` of polygon_sphere_contact 0x40a000 /
    polygon_capsule_contact 0x40b0f0. `corpus > 4` walks off a 4-entry local array into other frame
    slots, whose contents are a function of the frame layout (orig 0xd8 vs ours 0xc4) - not of the code.
  * `GFace::n` (+0) indexes `GFace::idx[4]` and drives the `vtx[3][4]` local of
    StratEnt::create_shadow_mesh 0x42b080. `n == 0` leaves `vtx` uninitialised (0xCCCCCCCC ids reach
    Psys::add_rec2 0x411920, whose heap result is a stale-stack block).
  * `Terrain::w` / `h` (+0x278 / +0x27c) are the last cell indices of the declared `cell[251][251]`
    (+0x288) that Terrain::sample 0x465af0 indexes; soup dims put the corner pointers far outside the
    grid, into whatever the pool/frame happens to hold.

Neither the compiler nor the source is at fault in these cases: NO valid object of that type can carry
such a length. Comparing two builds on one is comparing their frame layouts, so the harness must not count
it. This module declares, per row, the length field and the *declared capacity* it may not exceed, derived
from the type's own header (parsed below, so the bound is auditable rather than magic).

Two uses, both visible:
  * `enforce` (generation): a generated/mutated input that carries such an object has the length field
    moved into range, so most inputs remain useful instead of being thrown away;
  * `check` (discard): any input that still violates an invariant - whatever path produced it, including
    fault repair and steering - is discarded under the `invalid-object` key before it is compared, with
    the count and the offending field in the JSON. A discarded input is never compared, so this can never
    hide a difference in a comparison that does happen, and a violation of a field the invariant does not
    name is still a mismatch.

Disabled by `--no-invariants` (or `DIFFTEST_NO_INVARIANTS=1`): back to the raw soup exactly as before.
"""
import os
import re
import struct

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))

try:                                    # machine.py has no dependency on this module, so this is safe
    import machine as _M
    SLOT, POOL_BASE, POOL_SIZE = _M.SLOT, _M.POOL_BASE, _M.POOL_SIZE
except Exception:                       # noqa: BLE001 - keep the module importable on its own (tests)
    SLOT = 0x10000
    POOL_BASE = 0x40000000
    POOL_SIZE = 0x10000000
NSLOTS = POOL_SIZE // SLOT


# ====================================================================== declared capacities
# The bound of every invariant below is the *declared* array of the type the function walks, read from the
# header so that a reviewer can check it against the source. A missing/changed declaration falls back to the
# explicit constant and, failing that, disables that invariant (a wrong bound must never excuse a mismatch).

_HEADERS = ("src/include/shape.h", "src/game/strat/strat_entity.h", "src/game/terrain_a/terrain.h",
            "src/include/dialog_rec.h")
_decl_cache = {}


def _header_texts():
    if "txt" not in _decl_cache:
        parts = []
        for rel in _HEADERS:
            try:
                with open(os.path.join(ROOT, rel), encoding="utf-8", errors="replace") as f:
                    parts.append(f.read())
            except OSError:
                pass
        _decl_cache["txt"] = "\n".join(parts)
    return _decl_cache["txt"]


def declared_array_len(type_name, member, required=None, default=None):
    """Capacity of `type_name`'s array member `member` (`vector4 w[4]` -> 4), or `default`.

    required: a regex fragment the declaration line must contain (disambiguates the several `Terrain`
    structs and the two `cell` unions); the whole declaration must be an array of a fixed size, so a
    pointer member (`GVert* verts`) can never be mistaken for a capacity."""
    key = (type_name, member, required)
    if key in _decl_cache:
        return _decl_cache[key]
    got = default
    m = re.search(r"struct\s+%s\b\s*(?::[^{]+)?\{" % re.escape(type_name), _header_texts())
    if m:
        body = _header_texts()[m.end():]
        depth = 1
        for i, ch in enumerate(body):       # the struct body up to its matching brace
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    body = body[:i]
                    break
        for line in body.split("\n"):
            code = line.split("//")[0]
            # Declarations can share a line (`int n; int idx[4]; char pad14[..];`), so look at the single
            # declarator that names the member: from the last ';'/'{' before it up to its own ';'.
            for m2 in re.finditer(r"(?<![\w>.\]])(?:\w[\w:<>*&\s]*?\s)?(\w+)\s*((?:\[[^\]]*\])+)\s*;", code):
                if m2.group(1) != member:
                    continue
                dims = [int(d) for d in re.findall(r"\[\s*(\d+)\s*\]", m2.group(2))]
                if len(dims) != len(re.findall(r"\[[^\]]*\]", m2.group(2))):
                    continue            # a non-constant extent ([0x54 - 0x14], a pointer target, ...)
                if required and not re.search(required, m2.group(0)):
                    continue
                got = 1
                for d in dims:          # cell[251][251] -> 251 * 251
                    got *= d
                break
            else:
                continue
            break
    _decl_cache[key] = got
    return got


# ====================================================================== the invariants

class Invariant:
    """One length field (or a family of them) that a row's inputs must keep within a declared capacity.

    name/why are for the reason string. fields(gen, inp) yields ("<label>", value, lo, hi) for every dword
    the invariant governs - a missing/unreachable one yields nothing, which is never a violation. Each field
    carries its OWN bounds, because the object's array capacities differ (a face's count is 1..4, the entity's
    id-array length is 0..64)."""

    def __init__(self, name, why, fields, bounds, fix=None):
        self.name, self.why = name, why
        self.fields, self.fix = fields, fix
        self.bounds = list(bounds)          # [(lo, hi)] the fields of this invariant enforce, for reporting

    def violations(self, gen, inp):
        """[(label, value, lo, hi)] of every governed dword outside its own bounds (empty = well formed)."""
        out = []
        for label, v, lo, hi in self.fields(gen, inp):
            if v is not None and not (lo <= v <= hi):
                out.append((label, v, lo, hi))
        return out


def _dword(gen, inp, addr):
    """The dword an input holds at an absolute address of the lazily materialised pool, or None when the
    address is not in the pool (the object the pointer names was never mapped) - exactly the bytes
    `run_side` would see, since both go through InputGen.slot_pages."""
    if not (POOL_BASE <= addr < POOL_BASE + NSLOTS * SLOT):
        return None
    slot = (addr - POOL_BASE) & ~(SLOT - 1)
    page = addr & ~0xFFF
    buf = gen.slot_pages(inp, POOL_BASE + slot).get(page)
    if buf is None or addr & 0xFFF > len(buf) - 4:
        return None
    return struct.unpack_from("<I", buf, addr & 0xFFF)[0]


def _signed(v):
    return v - (1 << 32) if v is not None and v >= (1 << 31) else v


# -- face::count: the local `vector4 v[4]` of the two polygon contacts (0x40a000 / 0x40b0f0). The loop
#    bound is `a->count`, the array it walks is fixed at 4 (`shape.h`: `vector4 w[4]`), and count == 0 makes
#    `i % count` divide by zero, so a well-formed face is 1..4 (a real one is 3 or 4).

FACE_CAP = declared_array_len("face", "w", required=r"vector4\s+w\s*\[", default=4)


def _face_count(gen, inp):
    a = inp.args[0] if inp.args else 0
    if not (POOL_BASE <= a < POOL_BASE + NSLOTS * SLOT):
        return
    yield "face::count", _dword(gen, inp, a + 0xB0), 1, FACE_CAP


FACE_INV = Invariant("face::count", "the local v[4] walk of a face (shape.h: vector4 w[4], count +0xb0)",
                     _face_count, [(1, FACE_CAP)]) if FACE_CAP and 1 <= FACE_CAP else None


# -- GFace::n of the ground faces the entity's id list names: StratEnt::create_shadow_mesh 0x42b080 walks
#    `ctx->ground->faces[ids[i]]` for `i < nids` and indexes `GFace::idx[4]` + the local vtx[3][4] by
#    `face->n`. n outside 3..4 leaves vtx uninitialised (and n == 0 divides by zero); nids itself is an
#    index into the declared `ids[64]` (+0x174), so a well-formed entity has 0 <= nids <= 64.

GFACE_CAP = declared_array_len("GFace", "idx", default=4)
IDS_CAP = declared_array_len("StratEnt", "ids", default=64)


def _ground_face(gen, inp):
    """(face-object address, nids) of the entity's ground-face walk, or (None, None) when the entity or its
    grid is not a pool object at all (then the invariant governs nothing)."""
    th = inp.regs.get("ecx", 0)              # thiscall: this in ecx
    if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
        return None, None
    nids = _dword(gen, inp, th + 0x274)
    if nids is None or not (0 <= nids <= IDS_CAP):
        return None, nids
    ctx = _dword(gen, inp, th + 0x04)
    ground = _dword(gen, inp, ctx + 0xB0) if ctx is not None else None
    faces = _dword(gen, inp, ground + 0x14) if ground is not None else None
    if faces is None or not (POOL_BASE <= faces < POOL_BASE + NSLOTS * SLOT):
        return None, nids
    return (th, faces, nids), nids


def _ground_face_counts(gen, inp):
    if not GFACE_CAP:
        return
    walk, _nids = _ground_face(gen, inp)
    if walk is None:
        return
    th, faces, nids = walk
    for k in range(min(nids, IDS_CAP)):
        fid = _signed(_dword(gen, inp, th + 0x174 + 4 * k))
        if fid is None or fid < 0:
            continue
        n = _dword(gen, inp, faces + 0x88 * fid)
        if n is not None:
            yield "GFace::n(ids[%d])" % k, n, 3, GFACE_CAP


GFACE_INV = Invariant("GFace::n",
                      "the GFace::idx[4] / vtx[3][4] walk of the ground faces named by StratEnt::ids[64] "
                      "(strat_entity.h: GFace{int n; int idx[4]}, ids +0x174, nids +0x274)",
                      _ground_face_counts, [(3, GFACE_CAP)]) if GFACE_CAP and 3 <= GFACE_CAP else None


# -- GFace::n == 0 / nids: the SAME row also reads `nids` as the length of the declared `ids[64]` (+0x174)
#    walk, and `n == 0` divides by zero in the uv/alpha loop. Both are stated separately so the reason names
#    the field that was out of range.

def _strat_nids(gen, inp):
    th = inp.regs.get("ecx", 0)
    if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
        return
    nids = _dword(gen, inp, th + 0x274)
    if nids is not None:
        yield "StratEnt::nids", nids, 0, IDS_CAP


NIDS_INV = Invariant("StratEnt::nids", "the declared ids[64] (+0x174) the id list indexes",
                     _strat_nids, [(0, IDS_CAP)])


# -- Terrain::w / h: Terrain::sample 0x465af0 indexes the declared cell[251][251] (+0x288) through
#    cell_of 0x464b40, which clamps to [0, w-1]/[0, h-1]. w / h are the LAST cell index, so a well-formed
#    terrain has 0 <= w, h <= 250, and scale (+0xc3b0e0) must be non-zero. Soup dims (0xCCCCCCCC and
#    friends) put the four corner pointers arbitrarily far outside the grid.

CELL_TOTAL = declared_array_len("Terrain", "cell", required=r"terrain_cell", default=251 * 251)
CELL_DIM = int(round(CELL_TOTAL ** 0.5)) if CELL_TOTAL else 251


def _terrain_dims(gen, inp):
    th = inp.regs.get("ecx", 0)
    if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
        return
    yield "Terrain::w", _signed(_dword(gen, inp, th + 0x278)), 0, CELL_DIM - 1
    yield "Terrain::h", _signed(_dword(gen, inp, th + 0x27C)), 0, CELL_DIM - 1


TERRAIN_INV = Invariant("Terrain::w/h",
                        "the cell[%d][%d] walk of Terrain::sample (terrain.h: int w +0x278, int h +0x27c, "
                        "cell[251][251] +0x288)" % (CELL_DIM, CELL_DIM),
                        _terrain_dims, [(0, CELL_DIM - 1)])


# -- Elem::n: the Module System interpreter Operation::execute 0x49fa10 reads `n` (+8) operands of the
#    declared `__int64 vals[16]` (+0x10) into its local params[16] / types[16]. n > 16 writes past both
#    arrays into whatever frame slots follow them, which the two builds lay out differently (the original's
#    types[19] is its saved `neg` flag), so the result is a property of the frame, not of the code.

ELEM_CAP = declared_array_len("Elem", "vals", default=16)


def _elem_n(gen, inp):
    th = inp.regs.get("ecx", 0)
    if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
        return
    yield "Elem::n", _signed(_dword(gen, inp, th + 0x08)), 0, ELEM_CAP


ELEM_N_INV = Invariant("Elem::n", "the operand count of an operation (dialog_rec.h: int n +8, __int64 vals[%d] +0x10)"
                       % ELEM_CAP, _elem_n, [(0, ELEM_CAP)]) if ELEM_CAP else None


# ====================================================================== registry

# (module, va) -> the invariants its inputs must satisfy. Keyed by the row's own module+VA, not by symbol:
# a module rename or a second instantiation of the same source cannot silently pick up someone else's bound.
# The Mount & Blade rows (shapes 0x40a000, strat_entity 0x42b080, terrain_a 0x465af0, script_interpreter 0x49fa10)
# are not Spore functions; the invariant kinds above stay as templates for Spore's own (2026-10-29 port).
SPECS = {}


# -- --pin: a field the run is held to (a switch's selector, so each case of a dispatch can be driven on its own).
#    Not a capacity: the row's code accepts any value there, the pin only says which part of the function this
#    run is about. Spec "this+OFF&MASK=V1,V2,..." (hex): the bits MASK of the dword at this+OFF are one of V1..
#    (the bits outside MASK stay soup). An input whose `this` is not a pool object cannot carry the pin and is
#    discarded under the same invalid-object key, so no unpinned input is ever compared under a pinned row.

def pin_invariant(spec):
    m = re.fullmatch(r"this\+(?:0x)?([0-9a-fA-F]+)(?:&(?:0x)?([0-9a-fA-F]+))?=([0-9a-fA-Fx,]+)", spec.strip())
    if not m:
        raise ValueError("--pin: expected this+OFF[&MASK]=V1,V2,... (hex), got %r" % spec)
    off, mask = int(m.group(1), 16), int(m.group(2) or "ffffffff", 16)
    vals = sorted({int(v, 16) & mask for v in m.group(3).split(",") if v})
    lo, hi = vals[0], vals[-1]

    def fields(gen, inp):
        th = inp.regs.get("ecx", 0)
        if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
            yield "pin(this not a pool object)", -1, lo, hi
            return
        v = _dword(gen, inp, th + off)
        # out-of-set values report as just outside [lo..hi] so violations() flags them
        yield "pin(this+%#x)" % off, (v & mask if v is not None and v & mask in vals else
                                      (hi + 1 if v is not None else -1)), lo, hi

    def fix(bad, gen, inp, rng):
        th = inp.regs.get("ecx", 0)
        if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
            return []
        v = _dword(gen, inp, th + off) or 0
        return [(th + off, (v & ~mask) | rng.choice(vals))]

    return Invariant("pin(this+%#x&%#x)" % (off, mask), "the field --pin holds to %s" % ",".join("%#x" % v for v in vals),
                     fields, [(lo, hi)], fix)


def hint(spec):
    """--hint "this+OFF[&MASK]=V1,V2,...@P": a soft pin. In a share P of freshly generated inputs the masked dword at
    this+OFF is set to one of the values; nothing is ever discarded and mutation/steering may move it again. For a
    field whose realistic values soup rarely produces (a Module System operand's tag dword: 0 / -1 = a constant)."""
    body, _, prob = spec.partition("@")
    inv = pin_invariant(body)
    p = float(prob) if prob else 0.5
    off = int(re.match(r"this\+(?:0x)?([0-9a-fA-F]+)", body).group(1), 16)

    def apply(gen, inp, rng):
        if rng.random() >= p:
            return
        for addr, val in inv.fix([], gen, inp, rng):
            inp.pool_over[addr] = val & 0xFFFFFFFF
    apply.spec, apply.off = spec, off
    return apply


def specs_for(sid, va, enabled=True):
    """Invariants for one row; empty when disabled, when the row declares none, or when the module's
    declaration the capacity came from is missing."""
    if not enabled or os.environ.get("DIFFTEST_NO_INVARIANTS"):
        return []
    return [i for i in SPECS.get((sid, va), ()) if i is not None]


def describe(invs):
    """The bounds a row enforces ('face::count in [1..4]'), or "" when the row declares none. Each field
    carries its own declared capacity, so a row with several names each one."""
    return ", ".join("%s in %s" % (i.name, "/".join("[%d..%d]" % b for b in i.bounds))
                     for i in invs)


def check(invs, gen, inp):
    """-> (label, value, lo, hi, inv) of the first violated field, else None. Never raises: an input whose
    object cannot be reached is simply not judged."""
    for inv in invs:
        try:
            bad = inv.violations(gen, inp)
        except Exception:       # noqa: BLE001 - an unreadable input is not a violation
            bad = []
        if bad:
            label, value, lo, hi = bad[0]
            return label, value, lo, hi, inv
    return None


def enforce(invs, gen, inp, rng):
    """Generation side: move every governed length field that is out of range into range, so the input keeps
    an object the function can walk. Returns the number of fields repaired. Only the pool dwords an
    invariant governs are ever rewritten, so an input that already satisfies the invariants is
    byte-identical to the un-enforced one."""
    fixed = 0
    for inv in invs:
        try:
            bad = inv.violations(gen, inp)
        except Exception:       # noqa: BLE001
            continue
        if not bad:
            continue
        for addr, val in _repairs(inv, bad, gen, inp, rng):
            inp.pool_over[addr] = val & 0xFFFFFFFF
            fixed += 1
        if fixed:               # one field per pass is enough: re-check on the next input, keep this cheap
            pass
    return fixed


def _repairs(inv, bad, gen, inp, rng):
    """[(pool address, new dword)] that brings the violated fields of one invariant back in range."""
    out = []
    if inv.fix is not None:
        return inv.fix(bad, gen, inp, rng)
    if inv is FACE_INV:
        a = inp.args[0] if inp.args else 0
        if POOL_BASE <= a < POOL_BASE + NSLOTS * SLOT:
            out.append((a + 0xB0, rng.randint(1, FACE_CAP)))
    elif inv is NIDS_INV:
        th = inp.regs.get("ecx", 0)
        if POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT:
            out.append((th + 0x274, rng.randint(0, 4)))
    elif inv is GFACE_INV:
        walk, _nids = _ground_face(gen, inp)
        if walk is None:
            return out
        th, faces, nids = walk
        for label, _v, _lo, _hi in bad:
            # The label is "GFace::n(ids[3])": take the FIRST bracketed integer, not everything between
            # the first "[" and the last character (that gave int("3)") and crashed the run - the same
            # slice also parsed the report's "e.g. ... outside [0..64]" text as int("3]")).
            m = re.search(r"\[(\d+)\]", label)
            if not m:
                continue                    # no array index in this label: nothing addressable to repair
            k = int(m.group(1))
            fid = _signed(_dword(gen, inp, th + 0x174 + 4 * k))
            if fid is not None and fid >= 0:
                out.append((faces + 0x88 * fid, rng.randint(3, GFACE_CAP)))
    elif inv is ELEM_N_INV:
        th = inp.regs.get("ecx", 0)
        if POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT:
            out.append((th + 0x08, rng.randint(0, ELEM_CAP)))
    elif inv is TERRAIN_INV:
        th = inp.regs.get("ecx", 0)
        if not (POOL_BASE <= th < POOL_BASE + NSLOTS * SLOT):
            return out
        for label, _v, _lo, _hi in bad:
            off = 0x278 if label.endswith("::w") else 0x27C
            out.append((th + off, rng.randint(4, min(60, CELL_DIM - 1))))
    return out
