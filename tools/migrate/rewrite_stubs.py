"""rewrite_stubs: slice text that the class-oriented rules of rewrite.py do not cover.

Written for the SPEngine/SPPropertyManager.obj pilot (slices s006a32a0..s006aa3f0), whose slices hold
free functions, library template instantiations, functions of module-local classes and stubs next to the
real methods.  Everything here is generic text handling, used by rewrite.py at four points:

  slice_lines()           the slice as a list of lines with `#include "sNNNN.h"` expanded and the
                          slice-local `types.h` includes dropped (the TU includes game/types.h itself);
  insert_missing_markers  functions the slice never marked with `// @ 0xVA` get a marker, the VA coming
                          from (1) `FUN_<8 hex>` in the name, (2) the slice manifest's decorated symbol
                          (class, name), (3) a `// 006a3400 ...` banner above the definition;
  needed_items()          which of the slice's non-function items (local struct stubs, typedefs, statics,
                          helper declarations) the emitted functions actually use, transitively, in
                          slice order;
  merge_items()           item-wise merge of a slice's local items into the module TU that already holds
                          other slices' items: identical text is shared, a same-name item with different
                          text (every slice invents its own `struct String`) is renamed `Name_<slice>` in
                          the new slice only.
"""
import os, re

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
SLICES = os.path.join(ROOT, "match", "slices")

KEYWORDS = set("""if else for while do switch case default return break continue goto sizeof new delete this
true false const volatile static extern inline struct class union enum typedef namespace unsigned signed int char
short long float double void bool operator template typename virtual public private protected using register
__stdcall __cdecl __thiscall __fastcall __declspec __asm __int64 wchar_t size_t uint8_t uint16_t uint32_t uint64_t
int8_t int16_t int32_t int64_t NULL""".split())


# ---------------------------------------------------------------------------------------------
# masking (same contract as rewrite.mask; duplicated so that this module is importable alone)
# ---------------------------------------------------------------------------------------------
def mask(text):
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                out[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(out)


# ---------------------------------------------------------------------------------------------
# slice rows
# ---------------------------------------------------------------------------------------------
def slice_rows(sid):
    """-> (vas: set of ints, symbols: {va: decorated symbol}) from the slice's manifest/nonmatching/partial files."""
    vas, syms = set(), {}
    d = os.path.join(SLICES, sid)
    p = os.path.join(d, "manifest.txt")
    if os.path.exists(p):
        for line in open(p):
            parts = line.split("#", 1)[0].split()
            if len(parts) >= 3:
                try:
                    va = int(parts[2], 16)
                except ValueError:
                    continue
                vas.add(va)
                syms[va] = parts[1]
    for f in ("nonmatching.txt", "partial.txt"):
        p = os.path.join(d, f)
        if os.path.exists(p):
            for line in open(p):
                if line.strip() and not line.lstrip().startswith("#"):
                    try:
                        vas.add(int(line.split()[0], 16))
                    except ValueError:
                        pass
    return vas, syms


def mangled_path(sym):
    """'?Init@Vec38@@QAEPAU1@HPBX@Z' -> ['Vec38', 'Init'] (innermost last); None when not a decorated C++ name."""
    if not sym.startswith("?") or "@@" not in sym:
        return None
    return list(reversed(sym[1:sym.index("@@")].split("@")))


# ---------------------------------------------------------------------------------------------
# the slice as lines
# ---------------------------------------------------------------------------------------------
LOCAL_TYPES = re.compile(r'^\s*#\s*include\s+"(?:\.\./)*(?:include/|game/)?types\.h"\s*$')


def slice_lines(sid, text):
    """The slice text with its own header expanded in place and the slice-local types.h includes removed."""
    out = []
    for l in text.split("\n"):
        if LOCAL_TYPES.match(l):
            continue
        # `#include "s006bd150.h"` (the slice's own header) or `#include "../s006bc1b0/s006bc1b0.h"` (a sibling slice's
        # header shared by a run of slices)
        m = re.match(r'^\s*#\s*include\s+"(?:\.\./(s[0-9a-f]{8})/)?(s[0-9a-f]{8}\.h)"\s*$', l)
        if m:
            hp = os.path.join(SLICES, m.group(1) or sid, m.group(2))
            if os.path.exists(hp):
                for hl in open(hp, encoding="utf-8", errors="replace").read().split("\n"):
                    if LOCAL_TYPES.match(hl) or re.match(r"^\s*#\s*pragma\s+once", hl):
                        continue
                    out.append(hl)
                continue
        out.append(l)
    return out


# ---------------------------------------------------------------------------------------------
# top-level scan
# ---------------------------------------------------------------------------------------------
NONFUNC_HEAD = re.compile(r'^(?:template\s*<[^>]*>\s*)?(?:struct|class|union|enum|namespace)\b|^extern\s*"C"\s*$|^typedef\b|=')


def toplevel_defs(text):
    """Function definitions at brace depth 0 -> [(start, end, head)] offsets into `text` (end exclusive), `start`
    at the first character of the signature.  Struct/class/enum/namespace bodies and initialisers are skipped."""
    m = mask(text)
    n = len(m)
    out = []
    i = 0
    stmt = 0
    while i < n:
        c = m[i]
        if c == "#" and (i == 0 or m[i - 1] == "\n" or not m[text.rfind("\n", 0, i) + 1:i].strip()):
            j = text.find("\n", i)
            while j > 0 and text[j - 1] == "\\":
                j = text.find("\n", j + 1)
            i = n if j < 0 else j + 1
            stmt = i
            continue
        if c == ";":
            stmt = i + 1
        elif c == "{":
            head = re.sub(r"\s+", " ", m[stmt:i]).strip()
            j = i
            d = 0
            while j < n:
                if m[j] == "{":
                    d += 1
                elif m[j] == "}":
                    d -= 1
                    if d == 0:
                        break
                j += 1
            isfn = bool(head) and not NONFUNC_HEAD.search(head) and re.search(r"\)\s*(?:const)?$", head) is not None
            if isfn:
                s = stmt
                while s < n and m[s] in " \t\r\n":
                    s += 1
                out.append((s, j + 1, head))
            i = j + 1
            stmt = i
            continue
        i += 1
    return out


def _qualified_name(head):
    """Qualified name of a function head: 'bool EA::ArgScript::cExprFunction::EvalBool(int a)' -> EA::ArgScript::cExprFunction::EvalBool."""
    p = head.find("(")
    if p < 0:
        return None
    m = re.search(r"(~?[A-Za-z_]\w*(?:::~?[A-Za-z_]\w*)*)\s*$", head[:p])
    return m.group(1) if m else None


BANNER_VA = re.compile(r"^\s*//\s*(?:0x)?([0-9a-fA-F]{6,8})\b")


def insert_missing_markers(lines, sid, known_vas=()):
    """Give every function definition that has no `// @ 0xVA` marker one, when its VA can be established.
    -> (lines, [(va, name, how)]) ."""
    rows, syms = slice_rows(sid)
    rows = set(rows) | set(known_vas)
    by_path = {}
    for va, sym in syms.items():
        p = mangled_path(sym)
        if p:
            by_path.setdefault(tuple(p[-2:]), []).append(va)
            by_path.setdefault((p[-1],), []).append(va)
    text = "\n".join(lines)
    defs = toplevel_defs(text)
    starts = [0]
    for k, l in enumerate(lines):
        starts.append(starts[-1] + len(l) + 1)
    import bisect
    marker = re.compile(r"^//\s*@\s*0x[0-9a-fA-F]+\b")
    inserts = []
    prev_end_line = -1
    for (s, e, head) in defs:
        ln = bisect.bisect_right(starts, s) - 1          # line index of the signature start
        # preceding non-blank line a marker?
        k = ln - 1
        marked = False
        # the marker may sit above banner/comment lines (`// @ 0x006bb890  thunk` + `// -----`) that precede the definition
        while k >= 0 and (not lines[k].strip() or lines[k].lstrip().startswith("//")):
            marked = marked or bool(marker.match(lines[k]))
            k -= 1
        if marked:
            prev_end_line = bisect.bisect_right(starts, e - 1) - 1
            continue
        name = _qualified_name(head)
        va, how = None, None
        m = re.search(r"\bFUN_([0-9a-fA-F]{8})\b", head)
        if m:
            va, how = int(m.group(1), 16), "FUN_ name"
        if va is None and name:
            comps = name.split("::")
            for key in (tuple(comps[-2:]), (comps[-1],)):
                cands = by_path.get(key, [])
                if len(set(cands)) == 1:
                    va, how = cands[0], "manifest symbol %s" % "::".join(key)
                    break
        if va is None:
            # the comment block between the previous definition and this one
            for q in range(ln - 1, max(prev_end_line, ln - 40), -1):
                bm = BANNER_VA.match(lines[q])
                if bm and int(bm.group(1), 16) in rows:
                    va, how = int(bm.group(1), 16), "banner comment line %d" % (q + 1)
                    break
        if va is not None and va in rows:
            inserts.append((ln, va, name or head[:30], how))
        prev_end_line = bisect.bisect_right(starts, e - 1) - 1
    out = list(lines)
    for ln, va, name, how in sorted(inserts, reverse=True):
        out.insert(ln, "// @ 0x%08x" % va)
    return out, [(va, name, how) for _ln, va, name, how in sorted(inserts)]


# ---------------------------------------------------------------------------------------------
# items: declared names and uses
# ---------------------------------------------------------------------------------------------
IDENT = re.compile(r"[A-Za-z_]\w*")


def unwrap_namespaces(text):
    """`namespace A {\nnamespace B {\ndecl\n}\n}` -> (["A", "B"], "decl") (rewrite.parse_preamble wraps every item of a
    namespace block in its namespaces); text that is not wrapped -> ([], text)."""
    ns = []
    while True:
        mm = re.match(r"^\s*namespace\s+(\w+)\s*\{(.*)\}\s*(?://[^\n]*)?\s*$", text, re.S)
        if not mm or "}" not in mask(text):
            break
        # only unwrap when the closing brace is the one matching the opening one
        mt = mask(text)
        o = mt.index("{")
        d = 0
        for k in range(o, len(mt)):
            d += (mt[k] == "{") - (mt[k] == "}")
            if d == 0:
                break
        if mt[k + 1:].strip() and not mt[k + 1:].strip().startswith("//"):
            break
        ns.append(mm.group(1))
        text = mm.group(2).strip("\n")
    return ns, text


def item_names(kind, text):
    """Names an item (parse_preamble kind, text) declares."""
    m = mask(text)
    if m.lstrip().startswith("namespace"):        # `namespace EA { namespace ArgScript { class cIMetaCommand {..}; }}`
        _ns, inner = unwrap_namespaces(text)
        if inner != text:                       # one wrapped declaration: classes, templates, function declarations
            mi = mask(inner).lstrip()
            # a function template (`template <class T> inline T* uninitialized_copy_ptr(..) {..}`, s004e01d0) is not a class
            is_cls = mi.startswith(("struct", "class", "union", "enum")) or \
                bool(re.match(r"template\s*<[^>]*>\s*(?:struct|class|union)\b", mi))
            return item_names("struct" if is_cls else "other", inner)
        return re.findall(r"\b(?:struct|class|union|enum)\s+(\w+)\s*(?::[^{;]*)?\{", m)
    if kind == "define":
        mm = re.match(r"\s*#\s*define\s+(\w+)", m)
        return [mm.group(1)] if mm else []
    if kind == "struct":
        mm = re.match(r"\s*(?:template\s*<[^>]*>\s*)?(?:struct|class|union)\s+(\w+)", m)
        return [mm.group(1)] if mm else []
    if kind == "typedef":
        # function-pointer typedef: `(*Name)(` or `(__thiscall *Name)(` (the calling convention comes first)
        mm = re.search(r"\(\s*(?:__\w+\s*)?\*?\s*(?:__\w+\s+)?(\w+)\s*\)\s*\(", m)
        if mm:
            return [mm.group(1)]
        mm = re.search(r"(\w+)\s*(?:\[[^\]]*\])?\s*;\s*$", m.strip())
        return [mm.group(1)] if mm else []
    if kind in ("extern", "other"):
        mc = re.match(r"\s*(?:template\s*<[^>]*>\s*)?(?:struct|class|union)\s+(\w+)[^;{()]*\{", m)
        if mc:                                  # a class definition the struct parser did not take (several bases, template)
            return [mc.group(1)]
        mo = re.search(r"\boperator\s*(new|delete)\b(\s*\[\s*\])?\s*\(", m.split("{")[0])
        if mo:                                  # `void* operator new[](size_t, const char*, ...)`: used by every new-expression
            return ["operator " + mo.group(1)]
        mo = re.search(r"\boperator\s*(==|!=|<=|>=|<|>|\+=|-=|\+|-|\*|/|%|\[\s*\]|\(\s*\)|!|&&|\|\||=)\s*\(", m.split("{")[0])
        if mo and not re.match(r"\s*(?:struct|class|union)\b", m):
            # a free operator (`namespace eastl { bool operator==(const string8&, const char*); }`): used through operator syntax
            return ["operator" + re.sub(r"\s+", "", mo.group(1))]
        mp = re.match(r"\s*(?:static\s+|extern\s+|const\s+)*[\w:<>\s\*&]+?\(\s*\*\s*(?:__\w+\s+)?(\w+)\s*\)\s*\(", m)
        if mp:                                  # a function-pointer variable: `bool (*g_pParse)(int) = &Parse;`
            return [mp.group(1)]
        head = m.split("{")[0]
        head = re.sub(r"\([^()]*\)\s*$", "", head.strip().rstrip(";"))      # trailing parameter list
        head = re.split(r"=", head)[0]
        head = re.sub(r"\[[^\]]*\]", " ", head)
        ids = [x for x in IDENT.findall(head) if x not in KEYWORDS]
        mm = re.search(r"(\w+)\s*\(", m.split("{")[0].split("=")[0])
        if mm and mm.group(1) not in KEYWORDS:
            return [mm.group(1)]
        return ids[-1:] if ids else []
    return []


def item_uses(kind, text):
    """Identifiers an item mentions (its own name included)."""
    m = mask(text)
    # a name after `::`, `.` or `->` is qualified or a member access: it cannot name a global-scope local stub
    # (`EA::ResourceMan::PFIndexModifiable::Foo` does not use the slice's own `struct PFIndexModifiable`)
    # (a leading `::` is the global scope, a use: s00948de0's `::MIMEStringToMIMETypes(...)`)
    return {mm.group(0) for mm in IDENT.finditer(m)
            if mm.group(0) not in KEYWORDS and not re.search(r"([\w>)]\s*::|\.|->)\s*~?\s*$", m[max(0, mm.start() - 8):mm.start()])}


def needed_items(items, fn_texts, skip=()):
    """items: [(kind, text)] in slice order.  fn_texts: the emitted functions' text (signature + body).
    -> the items to emit (struct/typedef/extern/other whose declared name is used, transitively), in slice order.
    A forward declaration (`struct X;`) is kept when X is used and no definition of X is kept."""
    used = set()
    for t in fn_texts:
        used |= item_uses("other", t)
        mt = mask(t)
        if re.search(r"\bnew\b", mt):
            used.add("operator new")
        if re.search(r"\bdelete\b", mt):
            used.add("operator delete")
    decl = []
    for k, (kind, text) in enumerate(items):
        if kind in ("struct", "typedef", "extern", "other", "define") and k not in skip:
            decl.append((k, kind, text, item_names(kind, text)))
    # an item wrapped in namespaces (parse_preamble wraps every item of a namespace block) is used by the qualified spelling
    # `EA::IO::WriteUint32(...)` too: `item_uses` ignores names after `::`, so the qualified chains of the function texts are
    # matched against the item's qualified name
    chains = set()
    for t in fn_texts:
        for mm in re.finditer(r"[A-Za-z_]\w*(?:\s*::\s*~?[A-Za-z_]\w*)+", mask(t)):
            chains.add(re.sub(r"\s+", "", mm.group(0)))
    qual = {}
    for k, kind, text, names in decl:
        ns, _inner = unwrap_namespaces(text)
        if ns:
            qual[k] = ["::".join(ns + [n]) for n in names]

    def qused(k):
        return any(ch == q or ch.startswith(q + "::") for q in qual.get(k, []) for ch in chains)
    # operator symbols the function texts use (`name == "pi"`): a free operator item is used when its symbol appears and one of
    # the types it takes is used (s0083d3d0/s0083e1c0/s0083f140: the verbatim bodies compare the slice's eastl::string8 with a
    # literal through the slice's `bool operator==(const string8&, const char*)`, which was never emitted: C2678)
    optexts = [mask(t) for t in fn_texts]

    def op_used(k, text, names):
        for n in names:
            if not n.startswith("operator") or n in ("operator new", "operator delete"):
                continue
            sym = n[len("operator"):]
            if not any(sym in t.replace(" ", "") for t in optexts):
                continue
            mt = mask(text)
            params = mt[mt.find("(", mt.find("operator")) + 1:]
            if any(i in used for i in IDENT.findall(params) if i not in KEYWORDS):
                return True
        return False
    keep = set()
    changed = True
    while changed:
        changed = False
        for k, kind, text, names in decl:
            if k in keep or not names:
                continue
            if any(n in used for n in names) or qused(k) or op_used(k, text, names):
                keep.add(k)
                used |= item_uses(kind, text)
                # a kept item's own new/delete-expressions need the slice's operator new/delete declarations (s007e4260: the
                # inline helper NewBehaviorMessage uses the 6-argument placement new; only function texts were scanned: C2660)
                mk = mask(text)
                if re.search(r"\bnew\b", mk) and not re.search(r"\boperator\s*new\b", mk):
                    used.add("operator new")
                if re.search(r"\bdelete\b", mk) and not re.search(r"\boperator\s*delete\b", mk):
                    used.add("operator delete")
                optexts.append(mk)
                for mm in re.finditer(r"[A-Za-z_]\w*(?:\s*::\s*~?[A-Za-z_]\w*)+", mask(text)):
                    chains.add(re.sub(r"\s+", "", mm.group(0)))
                changed = True
    return [items[k] for k, _kind, _text, _names in decl if k in keep]


def norm(text):
    return re.sub(r"\s+", " ", mask(text)).strip()


def rename_word(text, old, new, ns=()):
    """Replace identifier `old` by `new` outside strings/comments, not after '.', '->' or '::'.  With `ns` (the namespaces
    the renamed item lives in) the qualified spelling `ns::old` is renamed too."""
    m = mask(text)
    q = "".join(re.escape(n) + r"\s*::\s*" for n in ns)
    pat = re.compile(r"(?<![\w.>:])(?:%s)?%s\b" % (q, re.escape(old))) if q else re.compile(r"(?<![\w.>:])%s\b" % re.escape(old))
    out, last = [], 0
    for mm in pat.finditer(m):
        # `->old` / `.old`: member access keeps its name
        # a namespace of the same name is not the class (s00691680 renames the stub class EA::Thread::Thread: `namespace Thread {`
        # and the qualifier in `Thread::Mutex` are the namespace EA::Thread, renaming them hid the slice's Mutex stub)
        if re.search(r"\bnamespace\s+$", m[max(0, mm.start() - 20):mm.start()]):
            continue
        if old in ns and re.match(r"\s*::", m[mm.end():mm.end() + 4]) and mm.group(0) == old:
            continue
        out.append(text[last:mm.start()])
        out.append(mm.group(0)[:len(mm.group(0)) - len(old)] + new)
        last = mm.end()
    out.append(text[last:])
    return "".join(out)
