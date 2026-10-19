#!/usr/bin/env python3
"""rewrite: turn a slice TU into the module TU of the canonical source tree.

Phase B step 3 of docs/migration.md; the procedure and the worked example are in
docs/migration-runbook.md section 3.

usage: rewrite.py <slice-id> [--apply] [--module SUBSTR] [--scratch DIR]

  without --apply   print the plan (class map, member/method renames, converted thunks, unmapped
                    items) and write work/migrate/renames_<slice>.json
  with --apply      also write src/game/<dir>/<object>.cpp (appending to an existing module TU in VA
                    order), src/game/<dir>/<object>/{manifest,nonmatching,partial}.txt,
                    symbols/slices/<slice>.txt (retail VA -> canonical name for the difftest
                    resolver) and work/migrate/rewrite_<slice>.json (what was done)

The renames file work/migrate/renames_<slice>.json has two halves.  "auto" is recomputed on every
run (the evidence-based class map, member map, method map).  "manual" is read back and wins over
"auto": class_map / methods / members entries that evidence could not settle, "externs" for
callees and globals, "edits" (per function VA: exact find -> replace on the rewritten body) for the
few constructs no rule covers, each with a "why".  Whatever had to be decided by hand lives there.

Rules (all of them are applied to the function bodies, nothing else is touched):
  1. class map     slice struct -> canonical class: by function names (modmap), by methods with
                   retail address comments (pdb_names), by the canonical member at the same
                   offset in an already mapped owner (by-value, pointer and nested), by virtual
                   slot signatures of mapped interfaces, then by same short name in the namespace.
  2. member map    every node of the slice struct (members, nested by-value structs, small arrays)
                   paired with a node of the canonical class at the same (offset, size).  Offsets of
                   the canonical class come from compiling a probe under VC9 (the generated header's
                   comments are the generator's own estimate and can be a word off).  Chains are
                   rewritten by longest dotted-path match.
  3. method map    slice method -> canonical method: virtual slots by slot index, else by the retail
                   VA of the declaration, else by parameter shape + name similarity (unique winner
                   only); the definition line takes the canonical signature with the slice's
                   parameter names.
  4. thunks        ((TFx)(*(void***)EXPR)[0xNN / 4])(EXPR, args) -> EXPR->Method(args), Method from
                   the canonical vtable slot NN/4 of EXPR's class.
  5. allocation    T* p = (T*)ICoreAllocator_Alloc_Named(size, A, "name"); if (p) return p->Init(..);
                   return 0;   ->   return new (A, "name") T(..);
  6. externs       callees and globals with a retail address comment: named from pdb_names / names.txt /
                   KNOWN_EXTERNS; the rest stay as extern declarations with their address.
"""
import argparse, collections, copy, difflib, hashlib, json, os, re, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import headers as H  # noqa: E402
import rewrite_stubs as RS  # noqa: E402
sys.path.insert(0, os.path.join(os.path.dirname(HERE), "matching"))
import asm_audit  # noqa: E402

W = lambda *p: os.path.join(ROOT, *p)


def row_va(tok):
    """The VA of a bookkeeping row's VA column, or None when the token is not one (a wrapped reason line)."""
    m = re.fullmatch(r"(?:0x)?([0-9a-fA-F]{6,8})", tok or "")
    return int(m.group(1), 16) if m else None


def read_rows(path):
    """Rows of a nonmatching.txt/partial.txt/manifest.txt: comment and blank lines skipped; a physical line whose first
    token is not a VA continues the reason of the row above (slice s0091e650's partial.txt wraps one) and is joined to it."""
    rows = []
    for line in open(path):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        t = line.split()
        if row_va(t[0]) is None and not (len(t) >= 3 and row_va(t[2]) is not None):
            if rows:
                rows[-1] += " " + " ".join(t)
            continue
        rows.append(line.rstrip("\n"))
    return rows
INC = W("src", "game", "include")
SLICES = W("match", "slices")
SCALARS = {"int", "unsigned", "unsigned int", "short", "unsigned short", "char", "unsigned char", "signed char", "long",
           "unsigned long", "float", "double", "bool", "wchar_t", "uint8_t", "uint16_t", "uint32_t", "int8_t", "int16_t",
           "int32_t", "int64_t", "uint64_t", "__int64", "void", "size_t"}
FN_PTR = re.compile(r"\(\s*\*")
RUN_ALL_DEFAULT_FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]        # tools/matching/run_all.py DEFAULT_FLAGS

# Callees/globals whose canonical spelling is established by evidence outside pdb_names (each entry says why).
# name in the slice -> dict(decl = replacement declaration (None: declare nothing), call = name used in bodies,
#                           why = evidence)
KNOWN_EXTERNS = {
    "kTimeoutNone": dict(
        decl="namespace EA { namespace Thread { extern const unsigned int kTimeoutNone; } }  // 0x1436788",
        call="EA::Thread::kTimeoutNone",
        why="runbook s3 worked example: 0x1436788 is EA::Thread::kTimeoutNone (ThreadTime, passed by const reference to "
            "Mutex::Lock(unsigned int const &)); unnamed in pdb_globals.json"),
    "FindEmbeddedPackageHeader": dict(
        call="FindEmbeddedPackageHeader",
        why="symbols/names.txt names 0x8dd510 Resource::FindEmbeddedPackageHeader; no PDB type, extern \"C\" cdecl kept"),
}


# ---------------------------------------------------------------------------------------------
# text utilities
# ---------------------------------------------------------------------------------------------
def mask(text):
    """Same length as text, with comment bodies and string/char literal contents replaced by spaces
    (newlines kept) so that structure can be found with regexes."""
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


def match_close(m, i):
    """Index of the bracket closing the one at m[i] (masked text)."""
    pairs = {"(": ")", "[": "]", "{": "}", "<": ">"}
    o = m[i]
    c = pairs[o]
    d = 0
    for j in range(i, len(m)):
        if m[j] == o:
            d += 1
        elif m[j] == c:
            d -= 1
            if d == 0:
                return j
    return -1


def split_top(text, mtext=None, sep=","):
    """Split at top-level `sep` (outside (), [], {}, <> in templates only when `mtext` has no operators)."""
    mtext = mtext if mtext is not None else mask(text)
    out, d, last = [], 0, 0
    for i, ch in enumerate(mtext):
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        elif ch == sep and d == 0:
            out.append(text[last:i])
            last = i + 1
    tail = text[last:]
    if tail.strip() or out:
        out.append(tail)
    return [x.strip() for x in out]


def split_params(text):
    """Split a C++ parameter list at top-level commas, counting (), [], {} and template <> depth."""
    out, d, last = [], 0, 0
    m = mask(text)
    for i, ch in enumerate(m):
        if ch in "([{<":
            d += 1
        elif ch in ")]}>":
            if ch == ">" and i > 0 and m[i - 1] == "-":
                continue
            d -= 1
        elif ch == "," and d == 0:
            out.append(text[last:i].strip())
            last = i + 1
    tail = text[last:].strip()
    if tail or out:
        out.append(tail)
    return out


def norm_type(t):
    t = re.sub(r"\b(const|volatile|struct|class|enum|union)\b", " ", t)
    t = re.sub(r"\s+", " ", t).strip()
    t = re.sub(r"\s*([*&])", r" \1", t)          # `int*` and `int *` are one type
    t = re.sub(r"([*&])\s+(?=[*&])", r"\1", t)    # `int * *` -> `int **`
    return t


SLICE_STRUCTS = set()      # struct names the slice being rewritten defines (set by Rewrite): base_type() drops a namespace qualifier from them


def base_type(t):
    """('IStream', 1) for 'const IStream *'; ('uint32_t', 0)."""
    t = norm_type(t)
    ptr = t.count("*") + t.count("&")
    t = t.replace("*", " ").replace("&", " ")
    t = re.sub(r"\s+", " ", t).strip()
    if SLICE_STRUCTS and t not in SLICE_STRUCTS and "<" not in t and "::" in t and t.rsplit("::", 1)[1] in SLICE_STRUCTS:
        t = t.rsplit("::", 1)[1]          # `const SP::cPropertyList *` in a slice that declares its own `class cPropertyList` inside namespace SP
    return t, ptr


def words(name):
    ws = re.findall(r"[A-Z]+(?![a-z])|[A-Z]?[a-z]+|\d+", name)
    def stem(w):
        w = w.lower()
        if w.endswith("ing") and len(w) > 5:
            return w[:-3]
        if w.endswith("ed") and len(w) > 4:
            return w[:-2]
        if w.endswith("s") and not w.endswith("ss") and len(w) > 3:
            return w[:-1]
        return w
    return {stem(w) for w in ws if w.lower() not in ("internal", "do")}


def word_sim(a, b):
    r = difflib.SequenceMatcher(None, a.lower(), b.lower()).ratio()
    wa, wb = words(a), words(b)
    if wa and wb:
        r = max(r, 0.9 * len(wa & wb) / min(len(wa), len(wb)) if len(wa & wb) >= 1 and (len(wa & wb) >= 2 or len(wa) == 1 or len(wb) == 1) else 0)
    return r


def name_key(n):
    """method-name anchor (fix pass 6 B): equal up to case and underscores (FindPhotoByGuid / FindPhotoByGUID,
    GetClassID / GetClassId).  word_sim alone paired opposites (SetUIDisabled -> SetUIEnabled 1.00, SetTabIndentOff -> On,
    getIdentity -> setIdentity, PreloadResources -> UnloadResources) and unrelated slots (Init -> AsInterface 0.80)"""
    return re.sub(r"_", "", n).lower()


def class_key(n):
    """short class name without namespace, leading c/I prefix, trailing digits and case: cSPUISettings13 -> spuisettings"""
    n = re.sub(r"<.*", "", n).split("::")[-1]
    n = re.sub(r"^[cI](?=[A-Z])", "", n)
    return re.sub(r"\d+$", "", n).lower()


def class_anchor(sname, canon):
    """the slice struct's name names the canonical class: equal keys, or one contains the other (at least 4 letters:
    IButton / IWinButton, PropertyList / cDirectPropertyList, Job / cJob)"""
    a, b = class_key(sname), class_key(canon)
    if not a or not b:
        return False
    return a == b or (min(len(a), len(b)) >= 3 and (a in b or b in a))


# slot/method names that are placeholders (v10, pv08, slot_10, m24, _cb0, d0, FUN_00a2e1b0, Fn0095f620, sub_..)
PLACEHOLDER = re.compile(r"^(?:v|pv|vf|vfn|slot_?|m|_cb|cb|d|f|s|fn|Fn|FUN_|sub_|W|unk_?)?[0-9a-fA-F]{1,8}$|^(?:FUN|Fn|sub)_?[0-9a-fA-F]{6,8}$")


# names whose bodies the linker folds across classes (one `Release` body serves cRefObject and cAnimatingCreature): an
# address named like this says nothing about the class
FOLDED_NAMES = {"addref", "release", "getrefcount", "refcount", "operator=", "operatornew", "operatordelete", "new",
                "delete", "asinterface", "cast", "dispose", "destroy", "destruct"}


# ---------------------------------------------------------------------------------------------
# the slice
# ---------------------------------------------------------------------------------------------
class SliceStruct:
    def __init__(self, name, kind, bases, body_lines, first_line, text):
        self.name, self.kind, self.bases, self.line, self.text = name, kind, bases, first_line, text
        self.members = []      # dict(name, type, array, cmt)
        self.methods = []      # dict(name, ret, params, virtual, slot, va, inline, cmt)
        nslot = 0
        depth = 0
        for ln in body_lines:
            raw = ln.split("//")[0].rstrip()
            ms = mask(raw)
            d0 = depth
            depth += ms.count("{") - ms.count("}")
            if d0 > 0:                  # inside the body of an inline method of the slice struct
                continue
            cmt = ln.split("//", 1)[1].strip() if "//" in ln else ""
            s = raw.strip()
            if not s or s in ("public:", "private:", "protected:"):
                continue
            va = None
            off = None
            m = re.match(r"^\+0x([0-9a-fA-F]+)", cmt)
            if m:
                off = int(m.group(1), 16)
            m = re.match(r"^(\d+)\s*\(0x([0-9a-fA-F]+)\)", cmt)       # `// 12 (0x30)`: vtable slot index and byte offset
            if m and int(m.group(1)) * 4 == int(m.group(2), 16):
                off = int(m.group(2), 16)
            m = re.search(r"(?<![+\w])0x([0-9a-fA-F]{6,8})\b", cmt)
            if m and not re.match(r"^\+0x", cmt):
                va = int(m.group(1), 16)
            if "(" in s:
                inline = "{" in s
                head = s.split("{")[0].strip().rstrip(";")
                head = re.sub(r"^virtual\s+", "", head) if head.startswith("virtual") else head
                virt = s.startswith("virtual")
                mm = re.match(r"^(?P<ret>.*?)(?P<name>~?\w+)\s*\((?P<params>.*)\)\s*(?P<const>const)?$", head)
                if not mm:
                    continue
                ret = mm.group("ret").strip()
                name = mm.group("name")
                params = split_top(mm.group("params")) if mm.group("params").strip() else []
                slot = None
                if virt:
                    slot = off // 4 if off is not None else nslot
                    nslot = slot + 1
                self.methods.append(dict(name=name, ret=ret, params=params, virtual=virt, slot=slot, va=va,
                                         inline=inline, cmt=cmt, ctor=(name == self.name or name == "~" + self.name)))
            elif s.endswith(";") and not s.startswith(("typedef", "friend", "using")):
                mm = re.match(r"^(?P<type>.+?[\s\*&])(?P<name>\w+)\s*(?P<arr>\[[^\]]*\])?\s*;$", s)
                if mm:
                    self.members.append(dict(name=mm.group("name"), type=mm.group("type").strip(),
                                             array=mm.group("arr"), cmt=cmt))


class Chunk:
    def __init__(self, va, text):
        self.va, self.text = va, text
        m = mask(text)
        b = m.index("{")
        # a constructor's member-initialiser list (`) : mBase(a), mField(0) {`) belongs to the body, not to the signature:
        # cut at the first ':' (not '::') that follows a ')' at parenthesis depth 0
        cut, depth = b, 0
        for i in range(b):
            ch = m[i]
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
            elif ch == ":" and depth == 0 and m[i - 1] != ":" and m[i + 1] != ":" and ")" in m[:i]:
                cut = i
                break
        self.sig_text = text[:cut]
        # preprocessor lines in front of the signature (`#pragma auto_inline(off)`, s007ada40 0x7ae980) are emitted with the
        # function, in front of its definition line, not parsed as part of the signature
        self.lead = [l for l in self.sig_text.split("\n") if l.lstrip().startswith("#")]
        if self.lead:
            self.sig_text = "\n".join(l for l in self.sig_text.split("\n") if not l.lstrip().startswith("#"))
        sig = re.sub(r"^\s*//.*$", "", self.sig_text, flags=re.M)
        sig = re.sub(r"\s+", " ", sig).strip()
        e = match_close(m, b)
        self.body = text[cut:e + 1]
        self.after = text[e + 1:]
        # `Job& Job::operator=(const Job& s)` (s00942ff0 0x9436b0) is a method named operator= (it had no name, so no row)
        mm = re.match(r"^(?P<ret>.*?)\s*(?P<cls>\w+)::(?P<name>operator\s*(?:\(\s*\)|\[\s*\]|[^\s\w(]+)|~?\w+)\s*\((?P<params>.*)\)\s*(?P<const>const)?\s*$", sig)
        self.ok = bool(mm)
        self.cls = self.name = self.ret = None
        self.params, self.const = [], False
        if mm:
            self.ret, self.cls, self.name = mm.group("ret").strip(), mm.group("cls"), mm.group("name")
            # a definition spelled with its namespace (`EA::Variant* SP::cPropertyList::Foo(..)`): the namespace qualifier of
            # the class is not part of the return type
            self.ret = re.sub(r"\s*(?:\w+\s*::\s*)+$", "", self.ret).strip()
            # template-argument commas are not parameter separators (fix pass 5, s005580e0 0x558ae0 `Constraint(AnyConstraint,
            # eastl::vector<Constraint, eastl::sp_vector_allocator>)` counted 3 parameters and its row found no symbol)
            self.params = split_params(mm.group("params")) if mm.group("params").strip() and mm.group("params").strip() != "void" else []
            self.const = bool(mm.group("const"))
        self.canon = None      # canonical decl chosen for it
        self.module = None
        # a function without `Class::` in its definition (`extern "C" int FUN_008dd250(...)`): its canonical name is a
        # namespace function of the dev build.  A forward declaration of the same function may precede the definition
        # (`int CopyDatabaseRecord(...);`): only the last statement is the definition.
        self.free = False
        self.cc = None
        if not mm:
            fs = sig.rsplit(";", 1)[-1].strip()
            fs = re.sub(r'^extern\s+"C"\s*', "", fs)
            fm = re.match(r"^(?P<ret>.*?)\s*(?:(?P<cc>__cdecl|__stdcall|__fastcall)\s+)?(?P<name>[A-Za-z_]\w*)\s*\((?P<params>.*)\)\s*$", fs)
            if fm:
                self.free = True
                self.ret, self.name, self.cc = fm.group("ret").strip(), fm.group("name"), fm.group("cc")
                p = fm.group("params").strip()
                self.params = split_params(p) if p and p != "void" else []


class InstChunk(Chunk):
    """An explicit instantiation statement that is a function's whole definition (`template R C::f(params);`): kept verbatim,
    rendered as the statement; its row binds by the member name (the stub class may be renamed)."""
    def __init__(self, va, text):
        self.va, self.text = va, text
        st = " ".join(re.sub(r"//[^\n]*", "", text).split()).rstrip(";").strip()
        self.sig_text = st
        self.lead = []
        self.body = ";"
        self.after = ""
        self.inst = True
        self.ok = False
        self.free = False
        self.cc = None
        self.canon = None
        self.module = None
        self.cls = None
        self.const = st.endswith(" const")
        # (a member/function template instantiated with explicit template arguments, `template PropMap*
        # eastl::copy_backward_impl<..>::do_copy<PropMap*, PropMap*>(..);`, is deliberately no chunk: tried in fix pass 5 on
        # s007ca950 0x7caac0/0x7cab00/0x7cb450, the slice's copy_backward_impl template then vanished from the TU and the
        # neighbouring s007cc5f0 block failed C2065; the statement stays a preamble item)
        mm = re.match(r"^template\s+.*?::\s*(?P<name>operator\s*(?:\(\s*\)|\[\s*\]|[^\s\w(]+)|~?\w+)\s*(?:<(?:[^<>()]|<(?:[^<>()]|<[^<>()]*>)*>)*>)?\s*\((?P<params>.*)\)\s*(?:const)?$", st)
        self.name = mm.group("name") if mm else None
        # the class/namespace right before `::name` (`copy_backward_impl` in `eastl::copy_backward_impl<0, ..>::do_copy<..>(..)`):
        # two instantiations of one member name are told apart by it (fix pass 5, s007ca950 0x7caac0 / 0x7cab00)
        self.owner = None
        if mm:
            head = st[:mm.start("name")]
            mo = re.search(r"(\w+)\s*(?:<(?:[^<>]|<(?:[^<>]|<[^<>]*>)*>)*>)?\s*::\s*$", head)
            self.owner = mo.group(1) if mo else None
        self.ret = None
        p = mm.group("params").strip() if mm else ""
        self.params = split_params(p) if p and p != "void" else []


VA_GUARD = "#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)"


MARKER = re.compile(r"^//\s*@\s*0x([0-9a-fA-F]+)\b(.*)$")


def hoist_decls(text):
    """A chunk may open with the declarations its function needs (`struct HasStg { ... };`, typedefs, externs, prototypes,
    `static const` tables, macros) between the marker and the function: those belong to the preamble.  Every leading
    statement that ends with `;` at depth 0 (several lines too: s007aea30's two-line `extern "C" uint32_t trymapblock(..,\n
    ..);`), every class/union/template-class definition `...};` and every `#define` (with `\\` continuations) is hoisted, up to
    the first function definition (`... }` at depth 0).  A `#pragma` stays with the function (s007ada40: `#pragma
    auto_inline(off)` before DestroyDxtSurface decides that the implicit ~DxtSurface 0x7ae980 is emitted out of line).
    Before fix pass 2 only single-line typedef/extern lines and plain struct definitions were hoisted, so s007ada40's
    `static const unsigned __int64 kMaskRGB = ..;` became part of FUN_007adcf0's signature (and was dropped by make_verbatim:
    C2065), and s007aea30's chunk was cut at `union DxtColor {` (C2447).  -> (declaration lines, rest of the chunk)."""
    lines = text.split("\n")
    hoisted = []
    i, n = 0, len(lines)
    while i < n:
        s = lines[i].strip()
        if not s or s.startswith("//"):
            hoisted.append(lines[i]) if hoisted else None
            i += 1
            continue
        if s.startswith("#"):
            if re.match(r"#\s*pragma\b", s):
                break
            j = i
            while lines[j].rstrip().endswith("\\") and j + 1 < n:
                j += 1
            hoisted += lines[i:j + 1]
            i = j + 1
            continue
        ms = mask(lines[i]).strip()
        if re.match(r"^\}[\s}]*;?$", ms):
            # the closer of a namespace the slice opened before the marker (s00538e90: `namespace EA { namespace Swarm {` +
            # `// @ 0x840bb0` + prototype + `// @ 0x840d50` + prototype + `} }`): it goes to the preamble with its opener,
            # which parse_slice left there; counted into a statement it drove the depth to -2 and hoisted 59 bogus lines
            hoisted.append(lines[i])
            i += 1
            continue
        j, depth, seen, end = i, 0, False, None
        is_ns = bool(re.match(r"^(?:inline\s+)?namespace\b[^;(]*\{", ms)) or ms in ("namespace", "namespace {") or \
            bool(re.match(r"^namespace\s*(\w+\s*)?$", ms))
        while j < n:
            mj = mask(lines[j])
            depth += mj.count("{") - mj.count("}") + mj.count("(") - mj.count(")")
            seen = seen or "{" in mj
            if depth == 0 and mj.rstrip().endswith(";"):
                end = j
                break
            if depth == 0 and seen and mj.rstrip().endswith("}"):
                if is_ns:
                    # a namespace block of declarations (s00538e90's `namespace { struct cXxxCommand {..}; ... }`) is hoisted
                    # when a function follows it, or when it defines no function itself (a namespace that wraps the marker's
                    # own function, s00947d50, stays)
                    blk = mask("\n".join(lines[i:j + 1]))
                    rest = mask("\n".join(lines[j + 1:]))
                    # (fix pass 4: a namespace that wraps a top-level function definition is the marker's function, whatever
                    # follows it: s0046e450 0x46e450 / s004629e0 0x4629e0 were hoisted because structs follow the block, and
                    # the next marker's chunk began with the preamble text)
                    if not namespace_defines_function("\n".join(lines[i:j + 1])) and \
                            ("{" in rest or not re.search(r"\)\s*(?:const\s*)?(?:throw\s*\([^)]*\)\s*)?\{", blk)):
                        end = j
                elif re.match(r'^extern\s*"C(?:\+\+)?"\s*\{', lines[i].strip()) and \
                        not namespace_defines_function("\n".join(lines[i:j + 1])):
                    # a linkage block of declarations after the marker (s00764df0 0x765980: `extern "C" { void* EA_New(..); .. }`
                    # then HVec and HVec::grow): preamble, not the function (fix pass 4: a declarations-only chunk took the VA)
                    end = j
                elif j == i and "::" not in ms and re.match(r"^[\w\s\*&<>,]*?\b\w+\s*\([^()]*\)\s*\{\s*\}$", ms) and \
                        re.search(r"\)\s*(?:const\s*)?\{", mask("\n".join(lines[j + 1:]))):
                    # an empty one-line placeholder in front of the marker's function (s00705660 0x705b50: `void fn705030() {}`,
                    # the address of a function passed as an argument elsewhere, then struct Big5b50 and Big5b50::copy, the
                    # function of the row): preamble (fix pass 5: the chunk was bound to the placeholder, DIFF 1 byte)
                    end = j
                elif re.match(r"^template\s*<", ms) and next_is_plain_function(lines, j + 1):
                    # a helper function template in front of the marker's function (s00624fb0 0x625560: `template <class T>
                    # const T& max_(..) {..}` + SetCurrentCamera): the helper goes to the preamble (fix pass 4: the chunk was
                    # bound to max_, SetCurrentCamera became a stub and 13 functions were dropped, C3861)
                    end = j
                break                         # a function definition (or a linkage block): not hoisted
            j += 1
        if end is None:
            break
        hoisted += lines[i:end + 1]
        i = end + 1
    return hoisted, "\n".join(lines[i:])


def next_is_plain_function(lines, k):
    """The next statement from line k (blank and comment lines skipped) is a non-template function definition."""
    n = len(lines)
    while k < n and (not lines[k].strip() or lines[k].lstrip().startswith("//")):
        k += 1
    if k >= n:
        return False
    head = mask(lines[k]).strip()
    if head.startswith(("template", "}", "struct", "class", "union", "enum", "namespace", "typedef", "#", "extern", "using")):
        return False
    rest = mask("\n".join(lines[k:]))
    a, b = rest.find("{"), rest.find(";")
    return a >= 0 and (b < 0 or a < b) and bool(re.search(r"\)\s*(?:const\s*)?$", rest[:a].rstrip()))


def namespace_defines_function(text):
    """Does a `namespace X { ... }` block hold a function definition at its own top level (not an inline method of a class)?"""
    m = mask(text)
    a = m.find("{")
    if a < 0:
        return False
    depth, start = 0, a + 1
    k = a + 1
    while k < len(m):
        ch = m[k]
        if ch == "{":
            head = m[start:k].strip()
            if depth == 0:
                if re.match(r"^(?:inline\s+)?namespace\b", head):
                    return namespace_defines_function(m[start:])
                if re.search(r"\)\s*(?:const\s*)?(?:throw\s*\([^)]*\)\s*)?$", head) and \
                        not re.match(r"^(?:template\s*<(?:[^<>]|<[^<>]*>)*>\s*)?(?:struct|class|union|enum)\b", head):
                    return True
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth < 0:
                return False
            if depth == 0:
                start = k + 1
        elif ch == ";" and depth == 0:
            start = k + 1
        k += 1
    return False


PARAM_KW = set("const volatile unsigned signed int char short long float double void bool wchar_t __int64 struct class enum union".split())


def proto_key(text):
    """A function prototype item (no body) -> (name, extern_c, [parameter types without names], return type), else None.
    `extern "C" __declspec(dllimport) int __cdecl _stricmp(const char* a, const char* b);  // 0x..` ->
    ('_stricmp', True, ['const char*', 'const char*'], 'int')."""
    ns, inner = RS.unwrap_namespaces(text)
    m = mask(inner).strip()
    if "{" in m or not m.endswith(";") or "(" not in m or "=" in m.split("(")[0] or \
            m.startswith(("typedef", "template", "struct", "class", "union", "enum", "using")):
        return None
    ext_c = bool(re.match(r'^extern\s+"', inner.strip()))
    throws = bool(re.search(r"\bthrow\s*\(\s*\)", mask(inner)))
    code = inner.split("//")[0] if "//" in mask(inner) else inner
    code = re.sub(r'^\s*extern\s*("C")?', " ", code)
    code = re.sub(r"__declspec\s*\([^()]*\)|\bthrow\s*\([^()]*\)|\b__(?:cdecl|stdcall|fastcall|thiscall)\b|\binline\b|\bstatic\b", " ", code)
    mc = mask(code)
    p = mc.find("(")
    if p < 0:           # `__declspec(thread) int g_tls_dummy;`: the only parenthesis was the __declspec's (mig8 s004bd850)
        return None
    mm = re.search(r"(operator\s*\S+?|~?[A-Za-z_]\w*)\s*$", code[:p])
    if not mm or "(*" in mc[:p + 2].replace(" ", "") or mm.group(1) in RS.KEYWORDS:
        return None
    e = match_close(mc, p)
    if e < 0 or mc[e + 1:].strip().rstrip(";").strip() not in ("", "const"):
        return None
    params = []
    for prm in split_params(code[p + 1:e]):
        prm = re.sub(r"\s*=.*$", "", prm).strip()
        toks = re.findall(r"[A-Za-z_]\w*|::|\*|&|\.\.\.|\[[^\]]*\]|<[^>]*>", prm)
        # drop the parameter name: a trailing identifier after another type token (not a keyword like `int`)
        if len(toks) >= 2 and re.match(r"^[A-Za-z_]\w*$", toks[-1]) and toks[-1] not in PARAM_KW and toks[-2] != "::":
            toks = toks[:-1]
        params.append(" ".join(toks))
    if params == ["void"]:
        params = []
    return ("::".join(ns + [mm.group(1).replace(" ", "")]), ext_c, params, " ".join(code[:mm.start()].split()), throws)


def same_function(a, b):
    """Two prototype keys declare one function (so the second must not be emitted again): same name and parameter count,
    and either one has C linkage (C functions do not overload) or the parameter types agree (only linkage, dllimport,
    throw(), parameter names or the return type differ)."""
    if a[0] != b[0] or len(a[2]) != len(b[2]):
        return False
    if a[4] != b[4] and a[1] == b[1]:
        # `throw()` changes the callers' code (no EH state around the call: s007e20a0's byte-exact 0x7e20a0 needs its
        # `EASTL_allocator_deallocate(void*) throw()`, s006a7e40 declared it without): VC9 accepts both declarations, keep both
        return False
    norm = lambda ps: [re.sub(r"\s+", "", x) for x in ps]
    return a[1] or b[1] or norm(a[2]) == norm(b[2])


def relocate_named_markers(lines):
    """`// @ 0x006404F0  SP::cSPPlayModeSubModePhoto::HandleButton` over ~140 lines of stubs, an inline helper
    `GetRecorderState() {..}` and then `bool cSPPlayModeSubModePhoto::HandleButton(int id) {`: the helper was the chunk's
    function and took the VA (mig9 s006404f0, SPSubModePhoto: HandleButton held, equiv "our symbol not found").  A marker that
    names a function whose first definition after it is another function moves to the named function's definition, when that
    is defined before the next marker; otherwise nothing changes."""
    marks = [i for i, l in enumerate(lines) if MARKER.match(l)]
    moves = []
    for k, i in enumerate(marks):
        mn = re.match(r"^\s*(?:[A-Za-z_]\w*::)*(~?[A-Za-z_]\w*)\s*$", MARKER.match(lines[i]).group(2))
        if not mn:
            continue
        name = mn.group(1)
        nxt = marks[k + 1] if k + 1 < len(marks) else len(lines)
        defre = re.compile(r"^[A-Za-z_][^;{}()]*?(?<![\w~])%s\s*\(" % re.escape(name))
        first, target = None, None
        for j in range(i + 1, nxt):
            l = lines[j]
            if not l[:1].strip() or l.lstrip().startswith(("//", "#")):
                continue
            mt = re.match(r"^[A-Za-z_][^;{}()=]*?(~?[A-Za-z_]\w*)\s*\(", l)
            if not mt:
                continue
            rest = mask("\n".join(lines[j:min(nxt, j + 12)]))
            kb, ks = rest.find("{"), rest.find(";")
            if kb < 0 or (0 <= ks < kb):
                continue            # a declaration
            if first is None:
                first = mt.group(1)
                if first == name:
                    break
            if defre.match(l):
                target = j
                break
        if first is not None and first != name and target is not None:
            moves.append((i, target))
    if not moves:
        return lines
    out = list(lines)
    for i, t in sorted(moves, reverse=True):
        m = out[i]
        out.insert(t, m)
        del out[i]
    return out


def mod_match(flt, module):
    """--module FILTER selects a module by its object name (`SPEditorHandle` -> SPBake/SPEditorHandle.obj) or its path.  It
    was a substring test: `SPEditorHandle` also took SPEditorHandleRotationRing/SPEditorHandleDeform, `SPUIFeedList` took
    SPUIFeedListCategory and `SPString` SPStringManager, and their TUs were rewritten by other objects' runs (mig10/mig11)."""
    f = flt.lower().replace("\\", "/")
    m = module.lower().replace("\\", "/")
    stem = m.rsplit("/", 1)[-1]
    return f in (m, stem, stem[:-4] if stem.endswith(".obj") else stem, m[:-4] if m.endswith(".obj") else m)


def parse_slice(sid, variant=""):
    path = os.path.join(SLICES, sid, sid + variant + ".cpp")
    if not os.path.exists(path) and os.path.exists(path[:-4] + ".c"):
        path = path[:-4] + ".c"         # a C slice (mig12 s008be260.c): its functions land in the object's C++ TU like any other
    if not variant and not os.path.exists(path):
        # a slice whose only TU is a flag variant (`s007f9550_od.cpp`, fix pass 5: round 5 landed it from a temporary copy):
        # the file its manifest rows name, else the single <sid>_*.cpp
        names = set()
        for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
            p = os.path.join(SLICES, sid, f)
            if f == "manifest.txt" and os.path.exists(p):
                for l in open(p):
                    t = l.split("#", 1)[0].split()
                    if t and t[0].endswith(".cpp"):
                        names.add(os.path.basename(t[0]))
        cands = sorted(names) if len(names) == 1 else sorted(f for f in os.listdir(os.path.join(SLICES, sid))
                                                             if f.startswith(sid + "_") and f.endswith(".cpp"))
        if len(cands) == 1:
            path = os.path.join(SLICES, sid, cands[0])
    text = open(path, encoding="utf-8", errors="replace").read()
    # rewrite_stubs: the slice's own header expanded in place, local types.h includes dropped, and a `// @ 0xVA` marker
    # inserted before every function definition the slice left unmarked whose VA the manifest/FUN_ name/banner gives
    lines, _marked = RS.insert_missing_markers(RS.slice_lines(sid, text), sid)
    lines = relocate_named_markers(lines)
    marks = [i for i, l in enumerate(lines) if MARKER.match(l)]
    # a legend of consecutive marker lines over one block (s00688dd0: `// @ 0x00689BE0 ..operator[]` .. `// @ 0x00689D00
    # ..GetFirstParameterID` above operator[]) is one boundary at its first line, whose VA is the function that follows; the
    # others name functions defined later (each under its own marker or found by insert_missing_markers).  Every line made
    # a boundary paired the last legend VA with operator[]'s body and gave two chunks one VA (KeyError in make_verbatim)
    marks = [i for k, i in enumerate(marks) if k == 0 or marks[k - 1] != i - 1]
    # banners (fix pass 4, s0073f320): a VA marked twice (`// @ 0x0073fe80 / 0x0073ffb0  bone-binding validators` over helpers,
    # then `// @ 0x0073fe80` over ValidateA) whose later marker is followed by a function definition was announced by the
    # earlier line (`// @ 0x0073f4b0  SP::cModelInstance::SetAnimationGroupTransform` .. declarations .. `// @ 0x0073f4b0`):
    # neither is a boundary.  Before, the helper under the banner took the VA (KeyError in build, 13 functions held)
    def _va(i):
        return int(MARKER.match(lines[i]).group(1), 16)
    def _defines(i, nxt):
        _h, b = hoist_decls("\n".join(lines[i + 1:nxt]))
        return "{" in mask(b)
    def _fname(i, nxt):
        _h, b = hoist_decls("\n".join(lines[i + 1:nxt]))
        mb = mask(b)
        k0 = mb.find("(")
        mm = re.search(r"(~?\w+)\s*$", mb[:k0]) if k0 > 0 else None
        return mm.group(1) if mm else None
    syms = RS.slice_rows(sid)[1]
    banner = set()
    for k, i in enumerate(marks):
        later = [i2 for i2 in marks[k + 1:] if _va(i2) == _va(i)]
        if later and i not in banner:
            k2 = marks.index(later[0])
            nxt = marks[k2 + 1] if k2 + 1 < len(marks) else len(lines)
            nxt1 = marks[k + 1] if k + 1 < len(marks) else len(lines)
            sm = re.match(r"^\?(\w+)@", syms.get(_va(i), "") or "")
            if sm and _fname(i, nxt1) == sm.group(1) and _fname(later[0], nxt) != sm.group(1):
                # the earlier marker's function is the manifest's (s00741210 0x741aa0 `?insert@Vec8@@`; the later marker is a
                # placeholder `cMI_Geo::Sub1aa0() {}`): the later line is the banner
                banner.add(later[0])
            elif _defines(later[0], nxt):
                banner.add(i)
    marks = [i for i in marks if i not in banner]
    if not marks:
        # mig7 report 24 (s0081e070, s0081f0e0, s00820cc0, s008219a0, s008268b0, s006eed00): a slice without a single
        # `// @ 0x` function marker has nothing to migrate; this was an IndexError
        raise NoFunctions("%s: no reconstructed functions (no `// @ 0x` markers)" % sid)
    pre = lines[:marks[0]]
    chunks = []
    carry_lead = []         # `#pragma optimize(..)` in front of the NEXT marker (see below)
    ns_at = enclosing_namespaces(lines)
    for k, i in enumerate(marks):
        j = marks[k + 1] if k + 1 < len(marks) else len(lines)
        va = int(MARKER.match(lines[i]).group(1), 16)
        hoisted, body = hoist_decls("\n".join(lines[i + 1:j]))
        # an explicit instantiation under its own marker (s004e01d0: `// @ 0x004E0880 ?reserve@..` +
        # `template void eastl::vector<EA::AutoRefCount<SP::cTextureInstance> >::reserve(uint32_t);`) is what makes the compiler
        # emit the function: it goes with the template definition of the same VA (after its body), not to the preamble
        inst = [l for l in hoisted if re.match(r"^\s*template\s+(?!<)[^;]*;\s*(//.*)?$", l)]
        tgt = next((c for c in chunks if c.va == va), None)
        if inst and tgt is not None:
            hoisted = [l for l in hoisted if l not in inst]
            tgt.body = tgt.body.rstrip() + "\n" + "\n".join(l.strip() for l in inst) + "\n"
        if tgt is None and "{" not in mask(body):
            # an explicit instantiation under its own marker whose template members are defined in the preamble's stub class
            # (fix pass 4, s0059b4b0 0x59c2f0 `template CreatureMap::iterator CreatureMap::DoInsertValueImpl(..);` over two
            # lines, 0x59c460 `template CreatureMap::iterator CreatureMap::erase(..);`, both byte-exact): the statement is the
            # function's whole definition; it was hoisted to the preamble and the VA silently never landed
            stmt = [];
            k0 = None
            for k1, l in enumerate(hoisted):
                if k0 is None and re.match(r"^\s*template\s+(?!<)", mask(l)):
                    k0 = k1
                if k0 is not None and mask(l).rstrip().endswith(";"):
                    stmt = hoisted[k0:k1 + 1]
                    break
            if stmt:
                hoisted = [l for l in hoisted if l not in stmt]
                ic = InstChunk(va, "\n".join(l.strip() for l in stmt))
                if ic.name:
                    ic.enc_ns = ns_at[i]
                    pre += hoisted
                    chunks.append(ic)
                    continue
                hoisted += stmt
        pre += hoisted
        if "{" not in mask(body):          # a marker over declarations only (the function follows under a second marker)
            continue
        # a namespace opened right after the marker around the function (s0046e450 `// @ 0x0046e450` + `namespace SP { namespace
        # EditorUtils {` + the definition + `} }`): the function is defined inside it (fix pass 4)
        own_ns = []
        while True:
            mo = re.match(r"^(\s*(?://[^\n]*\n\s*)*)namespace\s+(\w+)\s*\{", body)
            if not mo or not namespace_defines_function(body[len(mo.group(1)):]):
                break
            # ... and only when the function is the namespace's FIRST item (mig8 s004b8af0: the implicit 0x4b8ef0's chunk went on
            # into `namespace eastl { struct sp_vector_allocator ..; template .. copy_impl(..) {..} .. }`, which was taken as the
            # function's own namespace: its opener was dropped and its closer emitted, C2059 in the preamble, 4 functions held)
            rest = mask(body[mo.end():]).lstrip()
            k1 = rest.find("{")
            head1 = rest[:k1] if k1 >= 0 else rest
            if re.match(r"^(?:template\b|struct\b|class\b|union\b|enum\b|typedef\b)", head1):
                break
            own_ns.append(mo.group(2))
            body = body[mo.end():]
        ch = Chunk(va, body.rstrip() + "\n")
        if carry_lead:
            ch.lead = carry_lead + list(ch.lead)
            carry_lead = []
        if own_ns:
            aft = ch.after
            for _n in own_ns:
                aft = re.sub(r"^\s*\}[ \t]*(?://[^\n]*)?", "", aft, count=1)
            ch.after = aft
        ch.enc_ns = ns_at[i] + own_ns
        # what follows a function's closing brace (structs, typedefs, statics, helper functions the next function needs)
        # belongs to the preamble: the module TU is written in VA order, the slice in its own order
        # ... except the `#pragma` lines right after the closing brace: they restore what a pragma before the function set
        # (`#pragma inline_depth(0)` .. function .. `#pragma inline_depth()`).  In the preamble the restore came first and every
        # later function of the TU was compiled without inlining (mig8/mig7r: 30+ functions byte-exact in their slices were
        # dropped as DIFF in the module TU, e.g. s005d61b0's hkDefaultError::sectionBegin calling hkArray::pushBack)
        aft = ch.after.split("\n")
        keep = []
        while aft and (not aft[0].strip() or re.match(r"^\s*#\s*pragma\b", aft[0])):
            l0 = aft.pop(0)
            if l0.strip():
                keep.append(l0)
        # ... and `#pragma optimize("gt", off)` in front of the NEXT function's marker (only comments after it) sets up that
        # function: it is the next chunk's lead, not a preamble line (mig11 s009feb30 UpdateGoalWeight: hoisted without its
        # restore, it compiled the whole queued_blender TU unoptimized and all 6 functions were dropped as DIFF)
        k = len(aft)
        while k > 0 and (not aft[k - 1].strip() or aft[k - 1].lstrip().startswith("//") or re.match(r"^\s*#\s*pragma\b", aft[k - 1])):
            k -= 1
        tail_prag = [l for l in aft[k:] if re.match(r"^\s*#\s*pragma\b", l)]
        if tail_prag:
            carry_lead = tail_prag
            aft = [l for l in aft[:k]] + [l for l in aft[k:] if not re.match(r"^\s*#\s*pragma\b", l)]
        pre += aft
        ch.after = "\n".join(keep)
        chunks.append(ch)
    # two definitions under one VA (mig7 s0061c350 0x61d0d0: cGetAssetFeedTransaction::HandleResult and
    # cEditFeedTransaction::HandleResult, one folded retail body): the first one is the function, a later one keeps its text in
    # the preamble as a definition of its own class's member (KeyError in qual_of / compile_symbols before)
    seen_va, kept = set(), []
    for ch in chunks:
        if ch.va in seen_va and not getattr(ch, "inst", False):
            pre += ["// (second definition under 0x%08x; the retail body is folded)" % ch.va] + ch.body.split("\n")
            continue
        seen_va.add(ch.va)
        kept.append(ch)
    chunks = kept
    # an explicit instantiation the slice wrote inside `namespace X {` that reached the preamble outside that block (mig7r
    # s004e01d0 0x4e0600: its marker's chunk became a template definition, the statement landed after the block's `}`:
    # `template class hash_map<..>;` at global scope, C2059; the slice's three functions were held) gets its namespaces back
    pre_ns = enclosing_namespaces(pre)
    pos = {}
    for k, l in enumerate(lines):
        pos.setdefault(l, k)
    for k, l in enumerate(pre):
        if not re.match(r"^\s*template\s+(?!<)[^;{]*;\s*(//.*)?$", l) or pre_ns[k]:
            continue
        want = ns_at[pos[l]] if l in pos else []
        if want:
            pre[k] = " ".join("namespace %s {" % n for n in want) + " " + l.strip() + " " + "}" * len(want)
    return text, pre, chunks


def enclosing_namespaces(lines):
    """For every line: the namespaces open at its start (`namespace EA { namespace Internet {` ... `}}`).  s00947d50 defines its
    INetFileCache methods inside `namespace EA { namespace Internet {`: a verbatim copy emitted at global scope could not name
    the slice's (renamed) stub class (C2653 'INetFileCache_s0094_7d50' : is not a class or namespace name)."""
    out, stack, depth = [], [], 0
    for l in lines:
        out.append([n for n, _d in stack])
        m = mask(l)
        pos = 0
        for mm in re.finditer(r"\bnamespace\s+(\w+)\s*\{|\{|\}", m):
            t = mm.group(0)
            if t.startswith("namespace"):
                depth += 1
                stack.append((mm.group(1), depth))
            elif t == "{":
                depth += 1
            else:
                if stack and stack[-1][1] == depth:
                    stack.pop()
                depth -= 1
    return out


def named_param(ptype, name):
    """Parameter declaration of type text `ptype` named `name`; a function-pointer type takes the name inside its declarator:
    `bool (__cdecl *)(SP::cJob &, void *)` -> `bool (__cdecl *a2)(SP::cJob &, void *)` (s0068f670 ContinueJob 0x68f970 and
    s009413d0 SetNotificationTarget 0x942150 were demoted on `C2146`/`C2143` for `bool (__cdecl *)(..) a2`)."""
    m = re.search(r"\((\s*(?:__\w+\s*)?)\*\s*\)\s*\(", ptype)
    if m:
        return ptype[:m.start()] + "(%s*%s)" % (m.group(1), name) + ptype[m.end() - 1:]
    return "%s %s" % (ptype, name)


def base_list(text):
    """`public A, private B::C` -> ['A', 'B::C'] (the first one is the primary base)."""
    if not text:
        return []
    return [re.sub(r"\b(?:public|private|protected|virtual)\b", " ", b).strip() for b in split_params(text) if b.strip()]


def parse_preamble(pre):
    """-> (structs: {name: SliceStruct}, items: [(kind, text)]) ; kind in include/struct/typedef/extern/other/comment."""
    structs, items = {}, []
    # a C header guard around a linkage block (`#ifdef __cplusplus` / `extern "C" {` / `#endif` ... `#ifdef __cplusplus` /
    # `}` / `#endif`): the module TU is always C++, so the guards go and the block is an ordinary linkage block (mig12
    # s008bb550: the `#endif` after `extern "C" {` became part of the block's first item, `extern "C" #endif`, C2014)
    pre = list(pre)
    k = 0
    while k + 2 < len(pre):
        a, b, c = (x.strip() for x in pre[k:k + 3])
        if re.match(r"#\s*if(?:def\s+__cplusplus|\s+defined\s*\(?\s*__cplusplus\s*\)?)\s*$", a) and re.match(r"#\s*endif\b", c) \
                and (re.match(r'^extern\s+"C"\s*\{\s*(//.*)?$', b) or re.match(r"^\}\s*(//.*)?$", b)):
            pre[k:k + 3] = [pre[k + 1]]
        k += 1
    # several typedefs on one line (`typedef uint8_t uint8; typedef int16_t int16;`, mig12 s008b71c0) are one item each, so
    # each is kept when its own name is used (the line was one item keyed by one name, and `uint32` was dropped: C2061)
    k = 0
    while k < len(pre):
        ms = mask(pre[k]).split("//")[0]
        if ms.strip().startswith("typedef") and ms.count(";") > 1 and not re.search(r"[{}()]", ms):
            parts = [x.strip() + ";" for x in pre[k].split("//")[0].split(";") if x.strip()]
            pre[k:k + 1] = parts
            k += len(parts)
            continue
        # several prototypes on one line (`void __cdecl FUN_00f63170(); void __cdecl FUN_00fc5480();`, mig12 s00fc10d0) are
        # one item each too: the line was keyed by its first name and dropped, and the caller of the second hit C2065
        code = ms.strip()
        if code.count(";") > 1 and not re.search(r"[{}]", code) and code.count("(") == code.count(")") and code.endswith(";") \
                and not code.startswith(("#", "extern", "typedef", "return", "using")) \
                and all(re.search(r"\w\s*\([^;]*\)\s*$", x) for x in code.split(";") if x.strip()):
            cut = [i for i, ch in enumerate(ms) if ch == ";"]
            parts, st = [], 0
            for i in cut:
                parts.append(pre[k][st:i + 1].strip())
                st = i + 1
            pre[k:k + 1] = [x for x in parts if x != ";"]
            k += len(parts)
            continue
        k += 1
    i, n = 0, len(pre)
    while i < n:
        l = pre[i]
        s = l.strip()
        if not s:
            i += 1
            continue
        if s.startswith("//"):
            items.append(("comment", l))
            i += 1
            continue
        if s.startswith("#"):
            j = i
            while pre[j].rstrip().endswith("\\") and j + 1 < n:          # a macro continued over several lines
                j += 1
            kind = "include" if s.startswith("#include") else ("define" if re.match(r"#\s*define\s+\w", s) else "pragma")
            items.append((kind, "\n".join(pre[i:j + 1])))
            i = j + 1
            continue
        # several bases (`class DxtSurface : public DxtBase1, public DxtBase2, public DxtRefCount {`, s007ada40) are a struct
        # too: before fix pass 2 the line fell through to the statement path and the item was named after its last base
        m = re.match(r"^(struct|class|union)\s+(\w+)\s*(?::\s*((?:(?:public|private|protected|virtual)\s+)*[\w:<>, ]+?))?\s*\{?\s*(//.*)?$", s)
        one = re.match(r"^(struct|class|union)\s+(\w+)\s*(?::\s*((?:(?:public|private|protected|virtual)\s+)*[\w:<>, ]+?))?\s*\{(.*)\}\s*;\s*(//.*)?$", s)
        if one:             # struct Key { uint32_t inst, type, group; };
            body = []
            for decl in one.group(4).split(";"):
                decl = decl.strip()
                if not decl:
                    continue
                if "(" not in decl and "," in decl:
                    tm = re.match(r"^(.*?[\s\*&])(\w+(?:\s*,\s*\w+)+)$", decl)
                    if tm:
                        body += ["%s%s;" % (tm.group(1), n.strip()) for n in tm.group(2).split(",")]
                        continue
                body.append(decl + ";")
            st = SliceStruct(one.group(2), one.group(1), base_list(one.group(3)), body, i + 1, l)
            structs[st.name] = st
            items.append(("struct", l))
            i += 1
            continue
        if m and not s.endswith(";"):
            j = i
            depth = 0
            seen = False
            while j < n:
                ms = mask(pre[j])
                depth += ms.count("{") - ms.count("}")
                if "{" in ms:
                    seen = True
                if seen and depth == 0:
                    break
                j += 1
            body = pre[i + 1:j]
            body = [b for b in body]
            text = "\n".join(pre[i:j + 1])
            st = SliceStruct(m.group(2), m.group(1), base_list(m.group(3)), body, i + 1, text)
            structs[st.name] = st
            items.append(("struct", text))
            i = j + 1
            continue
        nm = re.match(r"^namespace\s+(\w+)\s*\{", s)
        if nm and nm.group(1) == "__equiv_ann":      # the slice's equivalence-checker annotation block, not code
            j = i
            depth = 0
            while j < n:
                depth += mask(pre[j]).count("{") - mask(pre[j]).count("}")
                if depth <= 0:
                    break
                j += 1
            i = j + 1
            continue
        if nm:
            # a namespace block: parse its content as a preamble of its own and wrap every inner item in the namespace again, so
            # that classes inside namespaces are slice structs (with `.ns`) and each declaration can be kept or dropped on its own
            j = i
            depth = 0
            while j < n:
                depth += mask(pre[j]).count("{") - mask(pre[j]).count("}")
                if depth <= 0:
                    break
                j += 1
            block = "\n".join(pre[i:j + 1])
            mb = mask(block)
            ob = mb.index("{")
            cb = match_close(mb, ob)
            inner = block[ob + 1:cb].split("\n")
            istructs, iitems = parse_preamble(inner)
            for st in istructs.values():
                st.ns = [nm.group(1)] + getattr(st, "ns", [])
                structs.setdefault(st.name, st)
            # a retail address comment after the closing brace (`namespace EA { string16 Foo(); }  // 0x0093c5a0`) is an
            # annotation of the declaration (the difftest resolver binds callees by it): keep it on the declaration's line
            tail = block[cb + 1:].strip()
            tail_cmt = tail if tail.startswith("//") else ""
            real = [it for it in iitems if it[0] not in ("comment", "include", "pragma")]
            for kind, text in iitems:
                if kind in ("comment", "include", "pragma"):
                    continue
                if tail_cmt and len(real) == 1 and "//" not in text.split("\n")[-1]:
                    text = text + "  " + tail_cmt
                items.append(("other", "namespace %s {\n%s\n}" % (nm.group(1), text)))
            i = j + 1
            continue
        # a statement: up to the terminating ';' at depth 0
        j = i
        buf = []
        depth = 0
        seen_brace = False
        while j < n:
            buf.append(pre[j])
            ms = mask(pre[j])
            depth += ms.count("(") - ms.count(")") + ms.count("{") - ms.count("}")
            seen_brace = seen_brace or "{" in ms
            if ms.rstrip().endswith(";") and depth == 0:
                break
            if seen_brace and depth == 0 and ms.rstrip().endswith("}"):       # a function definition or a namespace block
                break
            j += 1
        text = "\n".join(buf)
        kind = "typedef" if s.startswith("typedef") else ("extern" if s.startswith("extern") else "other")
        if re.match(r'^extern\s+"C"\s*\{', s) and kind == "extern":
            # a linkage block `extern "C" { decl; decl; ... }` is one declaration per item (`extern "C" decl;`), so each
            # callee is keyed, kept or dropped on its own (s0091f520: the block was keyed by its first name and emitted whole,
            # and its `GetSystemInfo(void*)` clashed with s0091e650's `GetSystemInfo(SYSTEM_INFO*)` in the module TU)
            mt = mask(text)
            ob = mt.index("{")
            cb = match_close(mt, ob)
            acc = []
            for ln in text[ob + 1:cb].split("\n"):
                code = mask(ln).split("//")[0].strip()
                if not acc and not code:
                    continue
                acc.append(ln.strip())
                joined = mask("\n".join(acc))
                if code.endswith(";") and joined.count("(") == joined.count(")") and joined.count("{") == joined.count("}"):
                    # a type defined in the block (`struct ChartSet { .. };`, mig10 s006e0030: the members were split into
                    # `extern "C"` items, C2059) is one item without the linkage prefix, which means nothing for a type
                    if re.match(r"^\s*(?:struct|class|union|enum)\b[^;]*\{", joined):
                        items.append(("other", "\n".join(acc)))
                    else:
                        items.append(("extern", 'extern "C" ' + "\n".join(acc)))
                    acc = []
            if acc:
                items.append(("extern", 'extern "C" ' + "\n".join(acc)))
            i = j + 1
            continue
        items.append((kind, text))
        i = j + 1
    return structs, items


# ---------------------------------------------------------------------------------------------
# canonical headers
# ---------------------------------------------------------------------------------------------
class CanonDecl:
    def __init__(self, **kw):
        self.__dict__.update(kw)

    def sig(self):
        return "%s %s(%s)%s" % (self.ret, self.name, ", ".join(self.params), " const" if self.const else "")


def parse_cdecl(line):
    """One declaration line of a generated header (class level) -> CanonDecl or None."""
    code, _, cmt = line.partition("//")
    code = code.strip()
    if not code.endswith(";") and "{" not in code:
        return None
    code = code.split("{")[0].strip().rstrip(";").strip()
    virt = static = False
    if code.startswith("virtual "):
        virt, code = True, code[8:]
    if code.startswith("static "):
        static, code = True, code[7:]
    # first '(' outside <>
    d = 0
    p = -1
    for i, ch in enumerate(code):
        if ch == "<":
            d += 1
        elif ch == ">":
            d -= 1
        elif ch == "(" and d == 0:
            p = i
            break
    if p < 0:
        return None
    head = code[:p].rstrip()
    mm = re.match(r"^(?P<ret>.*?)(?P<name>operator\s*[^\s(]+|~?\w+)$", head)
    if not mm:
        return None
    ret, name = mm.group("ret").strip(), mm.group("name").strip()
    e = match_close(code, p)
    params = split_params(code[p + 1:e]) if code[p + 1:e].strip() else []
    after = code[e + 1:]
    slot = va = None
    m = re.search(r"slot (\d+)", cmt)
    if m:
        slot = int(m.group(1))
    m = re.search(r"0x([0-9a-fA-F]{6,8})", cmt)
    if m:
        va = int(m.group(1), 16)
    return CanonDecl(virtual=virt, static=static, ret=ret, name=name, params=params, const="const" in after,
                     slot=slot, va=va, access=("protected" if "protected" in cmt else ("private" if "private" in cmt else "public")),
                     cmt=cmt.strip(), ctor=(not ret and not name.startswith("~")), dtor=name.startswith("~"))


class Canon:
    """A generated canonical class header, parsed back: declarations (with slots/VAs), data members, bases."""
    _cache = {}

    @classmethod
    def get(cls, name):
        if name not in cls._cache:
            cls._cache[name] = cls(name)
        return cls._cache[name]

    def __init__(self, name):
        self.name = name
        self.short = name.split("::")[-1]
        self.path = os.path.join(INC, H.include_path(name))
        self.exists = os.path.exists(self.path)
        self.decls, self.members, self.slots, self.bases = [], [], {}, []
        self.base_off = {}        # direct base -> offset (from the `public X /* +0xN */` comments of the class line)
        self.block_class = {}     # vtable block index -> class the vtable is "for" ({for `X'} in the header comment)
        if not self.exists:
            return
        lines = open(self.path, encoding="utf-8").read().split("\n")
        start = next((i for i, l in enumerate(lines) if re.match(r"^(class|struct)\s+%s\b" % self.short, l)), None)
        if start is None:
            return
        for b, off in re.findall(r"public ([\w:]+)(?:\s*/\*\s*\+0x([0-9a-fA-F]+)\s*\*/)?", lines[start].split("{")[0]):
            self.bases.append(b)
            self.base_off[b] = int(off, 16) if off else 0
        block = -1
        indata = False
        for l in lines[start + 1:]:
            if l.startswith("};"):
                break
            if re.match(r"^\s{2}// vtable ", l):
                block += 1
                bm = re.search(r"\{for `([^']+)'\}", l)
                if bm:
                    self.block_class[block] = bm.group(1)
                continue
            if l.startswith(" public:") and "data (retail offsets)" in l:
                indata = True
                continue
            if not re.match(r"^\s{2}\S" if not indata else r"^\s{2,4}\S", l):    # members of an anonymous union sit one level deeper
                continue
            if indata:
                mm = re.match(r"^\s{2,4}(?P<decl>.+?);\s*//\s*(?P<c>.*)$", l)
                if mm and not mm.group("decl").startswith(("union", "//")):
                    d = mm.group("decl")
                    am = re.match(r"^(?P<type>.+?)\s+(?P<name>\w+)(?P<arr>\[[^\]]*\])?$", re.sub(r"^mutable\s+", "", d))
                    if am:
                        off = re.search(r"0x([0-9a-fA-F]+)", mm.group("c"))
                        self.members.append(dict(type=am.group("type").strip(), name=am.group("name"), array=am.group("arr"),
                                                 off=int(off.group(1), 16) if off else None))
                continue
            if l.lstrip().startswith("//"):
                continue
            d = parse_cdecl(l)
            if d:
                d.block = block if d.virtual else None
                self.decls.append(d)
                if d.virtual and block == 0 and d.slot is not None:
                    self.slots[d.slot] = d

    def member(self, name):
        return next((m for m in self.members if m["name"] == name), None)


def base_offset(cls, target, seen=None):
    """Offset of the base-class subobject `target` inside `cls` (sum of the `+0xN` base comments), or None."""
    if cls == target:
        return 0
    c = Canon.get(cls)
    for b in c.bases:
        o = base_offset(b, target)
        if o is not None:
            return c.base_off.get(b, 0) + o
    return None


def parse_cdecl_demangled(dm):
    d = H.parse_decl(dm)
    if not d:
        return None
    return dict(name=d["name"], params=split_params(d["params"]) if d["params"] else [], ret=d["ret"])


def canon_methods(cls, seen=None):
    """Declarations of a class and its bases (derived first)."""
    seen = seen or set()
    if cls in seen:
        return []
    seen.add(cls)
    c = Canon.get(cls)
    out = list(c.decls)
    for b in c.bases:
        for d in canon_methods(b, seen):
            if not any(x.name == d.name and x.params == d.params and x.const == d.const for x in out):
                out.append(d)
    return out


# ---------------------------------------------------------------------------------------------
# the tool
# ---------------------------------------------------------------------------------------------
class Rewrite:
    def __init__(self, sid, scratch, variant=""):
        self.sid = sid
        # `--variant _od`: the slice's flag-variant TU (s007f8540_od.cpp next to s007f8540.cpp, fix pass 5): its own items
        # block (`items of slice s007f8540_od`) and its own stub-rename suffix, so the plain and the variant run do not
        # replace each other's blocks or collide on renamed stub names
        self.variant = variant or ""
        self.bid = sid + self.variant
        tag = re.sub(r"\W", "", self.variant)
        self.rsfx = "_s" + sid[1:5] + "_" + sid[5:] + (("_" + tag) if tag else "")
        self.scratch = scratch
        os.makedirs(scratch, exist_ok=True)
        self.src_text, self.pre, self.chunks = parse_slice(sid, self.variant)
        self.structs, self.items = parse_preamble(self.pre)
        # an `extern "C"` function prototype inside a namespace names the global C function (C linkage ignores namespaces):
        # it is emitted at global scope, so another slice's global declaration of it is the same text, not a second
        # candidate (fix pass 5, s0058be50 `namespace SP { extern "C" void EASTL_allocator_deallocate(void*); }` next to
        # s005b94b0's global one: C2668 ambiguous call through ADL in s005b94b0's eastl stub)
        def _cglobal(kind, text):
            ns, inner = RS.unwrap_namespaces(text)
            mi = RS.mask(inner).strip()
            # (only a retail function with an address comment: a Win32 API spelled with the slice's own types in a namespace,
            # s004057b0's QueryPerformanceCounter(int64_t*), would clash with <windows.h>'s at global scope, C2664)
            if ns and kind in ("extern", "other") and re.match(r'^extern\s+"C"\s+[^{]*\)\s*;', inner.split("//")[0].strip()) and \
                    "{" not in mi and re.search(r"//\s*@?\s*0x[0-9a-fA-F]{6,8}", inner):
                return inner.strip()
            return text
        self.items = [(k, _cglobal(k, t)) for k, t in self.items]
        SLICE_STRUCTS.clear()
        SLICE_STRUCTS.update(self.structs)
        self.data = H.Data()
        # `bool SP::GetPropertyAsKey(...)`: a definition qualified by a NAMESPACE (no struct of that name in the slice or in
        # the dev types) is a namespace function like the unqualified ones; its canonical declaration is the dev public
        for c in self.chunks:
            if c.ok and c.cls not in self.structs and c.cls not in self.data.types.structs:
                c.free, c.ok, c.slice_ns, c.cls = True, False, c.cls, None
        self.views = {}
        for d in self.data.views["defs"]:
            if d["slice"] == sid:
                self.views[d["name"]] = d
        # structs the slice takes from a sibling slice's header (`#include "../s006bc1b0/s006bc1b0.h"`; the text is expanded
        # in place by slice_lines) have their view under that slice: member renames need it, the slice's own view wins
        for sid2 in re.findall(r'#\s*include\s+"\.\./(s[0-9a-f]{8})/', self.src_text):
            for d in self.data.views["defs"]:
                if d["slice"] == sid2 and d["name"] not in self.views:
                    self.views[d["name"]] = d
        self.renames_path = W("work", "migrate", "renames_%s.json" % sid)
        self.manual = {}
        if os.path.exists(self.renames_path):
            self.manual = json.load(open(self.renames_path)).get("manual", {})
        # VA keys are 8 lowercase hex digits; `"0x00931e10"` / `"00931E10"` were silently ignored (mig10 EAFileStream's hold)
        for sec, v in list(self.manual.items()):
            if isinstance(v, dict):
                self.manual[sec] = {(k.lower()[2:] if k.lower().startswith("0x") else k.lower()).zfill(8)
                                    if re.fullmatch(r"(?:0[xX])?[0-9a-fA-F]{5,8}", k) else k: w for k, w in v.items()}
        self.notes = []          # (kind, text) for the report
        self.explicit_this_methods()
        self.class_map = {}      # slice struct -> canonical class
        self.why = {}            # slice struct -> evidence string
        self.method_map = collections.defaultdict(dict)   # slice struct -> {slice method: (canon decl or None)}
        self.members_map = {}    # slice struct -> {slice dotted path: (canonical dotted path, slice type of node)}
        self.fn_class = {}       # va -> canonical class of the function
        self.pdb_names = self.data.pdb_names
        self.symbols = {}
        self.call_decls = []   # declarations of renamed calls, referenced by \x04index\x04 markers until arguments are fixed
        self.retype = {}       # per function: local name -> (slice type text, canonical type text)
        self.stats = collections.Counter()
        self.used = set()      # canonical classes whose complete type a body needs (receivers of virtual calls, new-expressions)

    # ---- 1. split by module/class ------------------------------------------------------------
    def explicit_this_methods(self):
        """A free `__cdecl` function whose first parameter is `Cls* pThis` and whose dev function is a non-static
        `__cdecl` method of Cls (a variadic member: VC9 passes `this` as the first stack argument) is that method: the
        definition is rewritten to `Ret Cls::Name(rest...)` with `pThis` -> `this`, and the method map names it.
        Slice s009013e0: `bool __cdecl FUN_009017d0(XmlTextWriter* pThis, const wchar_t* name, const wchar_t* fmt, ...)` is
        `virtual bool __cdecl EA::XML::XmlTextWriter::AppendAttributeF(wchar_t const *, wchar_t const *, ...)` (dev UAA)."""
        mm = self.data.modmap["functions"]
        for i, c in enumerate(self.chunks):
            if not c.free or not c.params:
                continue
            e = mm.get("%08x" % c.va)
            dev = e.get("dev") if e else None
            mangled = self.data.pub.get(int(dev, 16)) if dev else None
            if not mangled:
                continue
            d = H.parse_decl(self.data.und.many([mangled]).get(mangled))
            if not d or d["static"] or d["cc"] != "__cdecl" or d["cls"] not in self.data.types.structs:
                continue
            p0 = re.match(r"^\s*([\w:]+)\s*\*\s*(\w+)\s*$", c.params[0])
            short = d["cls"].split("::")[-1]
            if not p0 or p0.group(1).split("::")[-1] != short:
                continue
            pname = p0.group(2)
            ms = re.search(r"(?:__cdecl\s+)?\b%s\s*\(\s*%s\s*\*\s*%s\s*,?\s*" % (re.escape(c.name), re.escape(p0.group(1)), re.escape(pname)),
                           c.sig_text)
            if not ms:
                continue
            sig = c.sig_text[:ms.start()] + "%s::%s(" % (short, c.name) + c.sig_text[ms.end():]
            body = re.sub(r"(?<![\w.>])%s\b" % re.escape(pname), "this", c.body)
            nc = Chunk(c.va, sig + body + "\n")
            if not nc.ok:
                continue
            self.chunks[i] = nc
            self.notes.append(("explicit-this", "0x%08x %s: free __cdecl function with explicit %s* %s is the __cdecl method %s::%s" % (
                c.va, c.name, p0.group(1), pname, d["cls"], d["name"])))

    def assign_chunks(self, module_filter=None):
        self.module_filter = module_filter
        mm = self.data.modmap["functions"]
        for c in self.chunks:
            e = mm.get("%08x" % c.va)
            c.module = e["module"] if e else None
            c.dev_name = e.get("name") if e else None
            if c.dev_name and c.cls:
                # only chunks of the module being migrated name classes (a slice mixes neighbours: SPPropertyHelpers' SP::GetPropertyAsText is
                # a namespace function, not a method of a class "SP"), and only a class the dev types know
                if module_filter and not (c.module and mod_match(module_filter, c.module)):
                    continue
                cls, _m = H.split_qual(c.dev_name)
                if cls not in self.data.types.structs:
                    continue
                self.fn_class[c.va] = cls
                self.class_map.setdefault(c.cls, cls)
                self.why.setdefault(c.cls, "function names: 0x%08x is %s (modmap, %s)" % (c.va, c.dev_name, e["how"]))
        # chunks the module map names no dev function for (interpolated: 0x8d81a0) whose VA is the retail address of a method
        # declared by exactly one generated header (not inherited): that class owns the function, whatever class the slice
        # (which only knows the neighbours it sat between) calls it a method of
        for c in self.chunks:
            if c.va in self.fn_class or c.dev_name or not c.cls or \
                    (module_filter and not (c.module and mod_match(module_filter, c.module))):
                continue
            owner = self.header_owners().get(c.va, set())
            if len(owner) == 1:
                self.fn_class[c.va] = next(iter(owner))
                self.notes.append(("class-by-address", "0x%08x %s::%s is %s (retail address in its generated header)" % (
                    c.va, c.cls, c.name, next(iter(owner)))))
        # namespace functions (no `Class::` in the slice): the canonical declaration is the dev public of the function
        for c in self.chunks:
            c.free_decl, c.free_why = None, None
            if not c.free or (module_filter and not (c.module and mod_match(module_filter, c.module))):
                continue
            c.free_decl, c.free_why = self.free_function_decl(c, mm.get("%08x" % c.va))
        for k, v in self.manual.get("class_map", {}).items():
            self.class_map[k] = v
            self.why[k] = "manual: " + self.manual.get("why", {}).get(k, "renames file")
        # chunks of a slice class with a mapped canonical class that have no name inherit it
        for c in self.chunks:
            if c.va not in self.fn_class and c.cls in self.class_map:
                self.fn_class[c.va] = self.class_map[c.cls]

    def tu_methods(self):
        """{retail va: (canonical class, method name)} of the functions already defined in the src/game module TUs
        (`// @ 0xVA` marker, then the qualified definition)."""
        if not hasattr(self, "_tu_methods"):
            out = {}
            for root, _d, files in os.walk(W("src", "game")):
                if os.sep + "include" in root + os.sep:
                    continue
                for f in files:
                    if not f.endswith(".cpp"):
                        continue
                    txt = open(os.path.join(root, f), encoding="utf-8", errors="replace").read()
                    for mm in re.finditer(r"(?m)^// @ 0x([0-9a-fA-F]+)\n[^\n(]*?([A-Za-z_][\w:]*)::(~?\w+)\s*\(", txt):
                        out[int(mm.group(1), 16)] = (mm.group(2), mm.group(3))
            self._tu_methods = out
        return self._tu_methods

    def header_owners(self):
        """{retail va: {canonical classes whose generated header declares a method at it (not inherited)}}"""
        if not hasattr(self, "_header_owners"):
            idx = collections.defaultdict(set)
            for name in self._all_headers():
                c = Canon.get(name)
                for d in c.decls:
                    if d.va and "inherited from" not in d.cmt and not d.ctor:
                        idx[d.va].add(name)
            self._header_owners = idx
        return self._header_owners

    def free_function_decl(self, c, e):
        """Canonical declaration of a namespace function: the dev public of the modmap's dev function, demangled
        (`bool __cdecl EA::ResourceMan::CopyDatabaseRecord(Database *, Database *, Key const &, bool)`).
        -> (CanonDecl, evidence) or (None, why not)."""
        dev = e.get("dev") if e else None
        D = self.data
        mangled, via = None, None
        if not dev and e:
            # no dev counterpart in the module map (interpolated functions carry none): a manual `methods` entry
            # {va: "SP::Name"}, else the one namespace function of the same dev object file with the slice's own name
            frees = D.free_decls_of(e["module"])
            want = self.manual.get("methods", {}).get("%08x" % c.va)
            if want:
                hit = [d for d in frees if (d["cls"] + "::" + d["name"]) == want or d["name"] == want]
                via = "manual: %s" % self.manual.get("why", {}).get("%08x" % c.va, "renames file")
            else:
                hit = [d for d in frees if d["name"] == c.name]
                via = "the only function named %s in the dev object %s" % (c.name, e["module"])
            if len(hit) == 1:
                mangled = hit[0]["mangled"]
            elif len(hit) > 1:
                return None, "%d dev functions named %s in %s" % (len(hit), want or c.name, e["module"])
        if not dev and not mangled:
            return None, "modmap has no dev function for 0x%08x (how: %s)" % (c.va, e.get("how") if e else None)
        if dev:
            mangled = D.pub.get(int(dev, 16))
        if not mangled:
            return None, "dev function %s has no public symbol" % dev
        dm = D.und.many([mangled]).get(mangled)
        d = H.parse_decl(dm) if dm else None
        if not d or d["virtual"] or d["static"] or d["cls"] in D.types.structs or "operator" in d["name"]:
            return None, "dev public %s is not a namespace function (%s)" % (mangled, dm)
        if "anonymous namespace" in (d["cls"] or ""):
            # file-local function (internal linkage, decorated with the dev build's unnamed-namespace hash): it keeps the slice's spelling
            return None, "dev function %s is in an anonymous namespace (file-local)" % (d["name"])
        if "<" in d["name"]:
            # eastl:: algorithm instantiations (lower_bound, uninitialized_copy): the template belongs in a shared header and the
            # instance is whatever the compiler emits for it; runbook s7 keeps library instantiations in the slice
            return None, "library template instantiation (%s): stays in the slice" % d["name"][:60]
        params = split_params(d["params"]) if d["params"] and d["params"].strip() != "void" else []
        cc = d["cc"] if d["cc"] and d["cc"] != "__cdecl" else None
        decl = CanonDecl(ret=d["ret"], name=d["name"], params=params, const=False, virtual=False, static=False, slot=None,
                         va=c.va, access="public", cmt="", ctor=False, dtor=False, free=True, ns=d["cls"], cc=cc)
        return decl, "dev public %s (%s)%s" % (mangled, dm, (" [" + via + "]") if via else "")

    # ---- 2. map the other structs ------------------------------------------------------------
    def map_structs(self):
        T = self.data.types
        known_canon = set(T.structs)
        changed = True
        # (a) the main class first (done by assign_chunks); (b) by-value/pointer members of mapped owners
        # needs canonical offsets, which the probe provides; run it for the classes mapped so far.
        for rounds in range(4):
            before = len(self.class_map)
            self.probe_classes(sorted(set(self.class_map.values())))
            self.refuse_foreign_layouts()
            for sname, canon in list(self.class_map.items()):
                if sname not in self.structs:
                    continue
                self.map_from_members(sname, canon)
            self.map_from_methods_va()
            self.map_from_signatures()
            self.map_from_function_signatures()
            self.map_from_slots()
            self.map_from_short_names()
            if len(self.class_map) == before:
                break
        # a canonical class without a generated header cannot replace the slice's stub: converted bodies would name an
        # undefined type and the stub item was respelled with the canonical name inside its own namespace (s00947d50 `IniFile`
        # -> EA::IO::IniFile: `struct EA::IO::IniFile {` in `namespace EA { namespace IO {`, C2039 for every function of the TU)
        for sname, canon in list(self.class_map.items()):
            if sname in self.manual.get("class_map", {}) or Canon.get(canon).exists or "<" in canon:
                continue
            if any(self.fn_class.get(c.va) == canon for c in self.chunks):
                continue
            del self.class_map[sname]
            self.notes.append(("class-map", "%s -> %s dropped: no generated header for %s (the slice's stub stays)" % (sname, canon, canon)))

    SHIFT_LIMIT = 0x10      # the byte-exact main-class views are at most a word or two off (names one slot off); a class of
                            # another layout shifts its members by hundreds of bytes

    def refuse_foreign_layouts(self):
        """A function-name mapping (modmap: the retail function is named like a method of class X) only says the code is
        *like* X's.  When the slice's own view of the class puts the members it shares by name with X at offsets that are
        far from the canonical ones, the slice is a different class of the same name family (retail s006bc1b0: the 64-bit
        DatabasePackedFile with the FileStream at +0x30 of size 0x434 and the mutexes at 0x478 vs the 0x388 class whose
        mutexes are at 0x270, vtable 0x140a154 with 28 slots vs 0x14367b0 with 37): mapping it would rename members that
        are not the canonical ones.  The class is unmapped and its functions stay in the slice.  Manual class_map wins."""
        if not hasattr(self, "refused"):
            self.refused = {}
            # structs a slice takes from another slice's header (`#include "../s006bc1b0/s006bc1b0.h"`) have their
            # view under that slice
            self.included_views = {}
            for sid2 in re.findall(r'#\s*include\s+"\.\./(s[0-9a-f]{8})/', self.src_text):
                for d in self.data.views["defs"]:
                    if d["slice"] == sid2 and d["name"] not in self.views:
                        self.included_views.setdefault(d["name"], d)
        for sname, canon in list(self.class_map.items()):
            view = self.views.get(sname) or self.included_views.get(sname)
            if sname in self.manual.get("class_map", {}) or sname in self.refused or not view:
                continue
            if not any(c.cls == sname for c in self.chunks):
                continue
            shifts = []
            for m in view["members"]:
                if m.get("pad") or m.get("offset") is None:
                    continue
                o = self.probe.get((canon, m["name"]))
                if o and o[0] is not None:
                    shifts.append((abs(m["offset"] - o[0]), m["name"], m["offset"], o[0]))
            bad = [x for x in shifts if x[0] > self.SHIFT_LIMIT]
            if len(shifts) >= 2 and bad:
                bad.sort(reverse=True)
                why = "the slice's view of %s disagrees with %s: %d of %d members shared by name sit at other offsets (%s)" % (
                    sname, canon, len(bad), len(shifts), ", ".join("%s slice 0x%x canonical 0x%x" % (n, so, co) for _d, n, so, co in bad[:3]))
                self.refused[sname] = why
                del self.class_map[sname]
                self.why.pop(sname, None)
                for c in self.chunks:
                    if c.cls == sname:
                        self.fn_class.pop(c.va, None)
                self.notes.append(("layout-mismatch", why))

    def map_from_methods_va(self):
        # fix pass 6 B: a vote needs an anchor.  The retail method must be named like the slice's (no placeholder FUN_/Fn
        # names, no unnamed generated-header owners), and not a name whose bodies the linker folds across classes; the
        # class name may also anchor it.  mig7: cRefObject -> cAnimatingCreature (Release), cStarManager -> cAppModeEditorBase
        # (SaveState -> Redo), cJob -> cJobManager while SP::cJob exists, cInputManager -> EA::Audio::Sound (header owner)
        for s in self.structs.values():
            if s.name in self.class_map:
                continue
            votes = collections.Counter()
            anchored = collections.Counter()
            for m in s.methods:
                if m["va"] is None:
                    continue
                e = self.pdb_names.get("%08x" % m["va"]) or {}
                nm = e.get("name") or (self.data.modmap["functions"].get("%08x" % m["va"]) or {}).get("name")
                if not nm:
                    # unnamed in pdb_names (Refpack::CompressData 0x92c9f0): the address a generated header gives to a
                    # method of exactly one class (not inherited) is the same evidence
                    own = self.header_owners().get(m["va"], set())
                    if len(own) == 1 and not m["ctor"]:
                        votes[next(iter(own))] += 1
                        self.hdr_votes = getattr(self, "hdr_votes", {})
                        self.hdr_votes.setdefault(s.name, []).append("%s -> %s (0x%08x, generated header)" % (m["name"], next(iter(own)), m["va"]))
                    continue
                cls, mshort = H.split_qual(nm)
                if name_key(mshort) == name_key(m["name"]) and name_key(mshort).replace("operator", "") not in FOLDED_NAMES \
                        and name_key(mshort) not in FOLDED_NAMES or (m["ctor"] and cls.split("::")[-1] == mshort):
                    anchored[cls] += 1
                # a retail address that pdb_names gives to a constructor/destructor is not evidence for a slice method that
                # is neither (the linker folded identical bodies: 0x9276c0 `MemAlloc::Free(void*)` is named
                # SP::cLocalLightInfo::~cLocalLightInfo, a one-line free)
                if (mshort.startswith("~") or mshort == cls.split("::")[-1]) and not (m["ctor"] or m["name"].startswith("~")):
                    self.notes.append(("class-map", "%s::%s: address 0x%08x is named %s (a constructor/destructor body, probably folded): not used as class evidence" % (
                        s.name, m["name"], m["va"], nm)))
                    continue
                votes[cls] += 1
            if votes:
                exact = [c for c in votes if class_key(c) == class_key(s.name)]
                named = [c for c in votes if class_anchor(s.name, c)]
                if exact or named or len(anchored) == 1:
                    cls = max(exact, key=lambda c: (votes[c], anchored[c])) if exact else \
                        max(named, key=lambda c: (votes[c], anchored[c])) if named else next(iter(anchored))
                    # the slice names its struct like another canonical class (cJob while the votes say cJobManager)
                    other = self.namesake(s.name, cls)
                    if other:
                        self.notes.append(("class-map", "%s not mapped to %s by retail address: the slice's name is that of %s" % (
                            s.name, cls, other)))
                        continue
                else:
                    self.notes.append(("class-map", "%s not mapped by retail address: no anchored vote (%s)" % (
                        s.name, ", ".join("%s %d" % (c, n) for c, n in votes.most_common(3)) if not anchored else
                        "anchored votes split: " + ", ".join("%s %d" % (c, n) for c, n in anchored.most_common(3)))))
                    continue
                if cls in self.data.types.structs and not cls.startswith("eastl::"):
                    self.class_map[s.name] = cls
                    self.why[s.name] = "retail address comments: %s" % ", ".join(
                        ["%s -> %s" % (m["name"], (self.pdb_names.get("%08x" % m["va"]) or {}).get("name"))
                         for m in s.methods if m["va"] and (self.pdb_names.get("%08x" % m["va"]) or {}).get("name")] +
                        getattr(self, "hdr_votes", {}).get(s.name, []))
                else:
                    self.notes.append(("template-owner", "%s: methods name %s (a library template; mapped through its owner member)" % (s.name, cls)))

    def slot_clash(self, st, canon):
        """(slots whose real names disagree, slots whose names agree) between a slice struct's virtuals and the header's"""
        c = Canon.get(canon)
        agree = clash = 0
        for m in st.methods:
            if not m["virtual"] or m["slot"] is None:
                continue
            d = c.slots.get(m["slot"])
            if not d or PLACEHOLDER.match(m["name"]) or PLACEHOLDER.match(d.name) or m["name"].startswith("~") and d.dtor:
                continue
            if name_key(d.name) == name_key(m["name"]):
                agree += 1
            elif d.dtor or m["name"].startswith("~") or name_key(m["name"]) in FOLDED_NAMES or name_key(d.name) in FOLDED_NAMES \
                    or word_sim(m["name"], d.name) < 0.5:
                clash += 1
        return clash, agree

    def stub_has_library_members(self, sname, depth=0):
        """Does the slice's stub `sname` (or a slice struct it holds by value) hold a canonical class by value (FileStream,
        Mutex, eastl containers)?  Those members take the canonical size in the module TU and move every later offset."""
        view = self.views.get(sname) or getattr(self, "included_views", {}).get(sname)
        if not view or depth > 4:
            return True                       # unknown layout: treat as hazardous
        for b in view.get("base_layout", []):
            if b["name"] not in self.structs or self.stub_has_library_members(b["name"], depth + 1):
                return True
        for m in view["members"]:
            if m.get("pad"):
                continue
            bt, ptr = base_type(m["type"])
            bt = re.sub(r"\[.*$", "", bt).strip()
            if ptr or bt in SCALARS or bt in ("uint32_t", "int32_t", "uint16_t", "int16_t", "uint8_t", "int8_t", "uint64_t",
                                               "int64_t", "size_t", "wchar_t", "bool", "float", "double", "char"):
                continue
            if bt in self.structs:
                if self.stub_has_library_members(bt, depth + 1):
                    return True
                continue
            return True                       # a canonical / library type held by value
        return False

    def namesake(self, sname, cls):
        """another canonical class whose name is exactly the slice struct's (class_key), when `cls` is not"""
        if class_key(cls) == class_key(sname):
            return None
        if not hasattr(self, "_by_key"):
            self._by_key = collections.defaultdict(list)
            for t in self.data.types.structs:
                if "<" not in t:
                    self._by_key[class_key(t)].append(t)
        hit = self._by_key.get(class_key(sname))
        return hit[0] if hit else None

    def map_from_signatures(self):
        """Slice virtuals vs the canonical slot of the same index: parameter and return types pair by position
        (IdxEntry* <-> PFRecordInfo &), so the structs the slice invented for them get their class."""
        T = self.data.types
        for sname, canon in list(self.class_map.items()):
            st = self.structs.get(sname)
            if not st:
                continue
            cc = Canon.get(canon)
            for m in st.methods:
                if not m["virtual"] or m["slot"] not in cc.slots:
                    continue
                d = cc.slots[m["slot"]]
                if len(d.params) != len(m["params"]):
                    continue
                pairs = [(self.ptype(sp), cp) for sp, cp in zip(m["params"], d.params)] + [(m["ret"], d.ret)]
                for sp, cp in pairs:
                    sb = base_type(sp)[0]
                    if sb not in self.structs and sb.split("::")[-1] in self.structs:
                        sb = sb.split("::")[-1]          # the slice spells EA::Variant for its own `struct Variant` in namespace EA
                    cb = self.cls_of(cp)
                    if sb in self.structs and sb not in self.class_map and cb:
                        vs = self.views.get(sb, {}).get("size")
                        cl = T.layout(cb, "retail")
                        if vs and cl and cl["size"] != vs:
                            continue
                        self.class_map[sb] = cb
                        self.why[sb] = "parameter/return type of %s::%s (slot %d) vs %s" % (sname, m["name"], m["slot"], d.sig())

    def map_from_function_signatures(self):
        """Namespace functions: the dev public's parameter and return types pair by position with the slice's own
        (`cSPColorRGB* out` <-> `cSPColorRGB *`, `EA::ResourceMan::Key* out` <-> `Key *`): the structs the slice declared for
        them get their class, when the sizes agree."""
        T = self.data.types
        for c in self.chunks:
            d = getattr(c, "free_decl", None)
            if not c.free or d is None or len(c.params) > len(d.params):
                continue
            pairs = [(self.ptype(sp), cp) for sp, cp in zip(c.params, d.params)] + [(c.ret, d.ret)]
            for sp, cp in pairs:
                sb = base_type(sp)[0]
                if sb not in self.structs and sb.split("::")[-1] in self.structs:
                    sb = sb.split("::")[-1]
                cb = self.cls_of(cp)
                if sb in self.structs and sb not in self.class_map and cb:
                    vs = self.views.get(sb, {}).get("size")
                    cl = T.layout(cb, "retail")
                    if vs and cl and cl["size"] != vs:
                        self.notes.append(("class-map", "%s not mapped to %s through the signature of 0x%08x: sizes 0x%x vs 0x%x" % (
                            sb, cb, c.va, vs, cl["size"])))
                        continue
                    self.class_map[sb] = cb
                    self.why[sb] = "parameter/return type of %s (0x%08x) vs the dev public %s" % (c.name, c.va, d.sig())

    def map_from_slots(self):
        """Interfaces: slice virtual slot names/arity vs the canonical classes already pulled in by owners
        (pointer/by-value members) - only candidates are classes whose header exists."""
        for s in self.structs.values():
            if s.name in self.class_map:
                continue
            vm = [m for m in s.methods if m["virtual"]]
            if len(vm) < 3:
                continue
            best = None
            for path in sorted(self._all_headers()):
                cname = path
                c = Canon.get(cname)
                if len(c.slots) < len(vm):
                    continue
                score = 0
                for m in vm:
                    d = c.slots.get(m["slot"])
                    if d and len(d.params) == len(m["params"]):
                        score += 1
                        if d.name == m["name"]:
                            score += 2
                if best is None or score > best[0]:
                    best = (score, cname)
            if best and best[0] >= len(vm) + 2 and class_anchor(s.name, best[1]) and not self.namesake(s.name, best[1]):
                # real slot names that disagree with the canonical ones (the slice's CustomWinProc has AddRef/Release at
                # slots 1/2, EA::UTFWin::CustomWinProc Release/destructor): another vtable
                clash, agree = self.slot_clash(s, best[1])
                if clash > agree:
                    self.notes.append(("class-map", "%s not mapped to %s: %d of its named vtable slots disagree with the header, %d agree" % (
                        s.name, best[1], clash, agree)))
                    best = None
            if best and best[0] >= len(vm) + 2 and (not class_anchor(s.name, best[1]) or self.namesake(s.name, best[1])):
                # fix pass 6 B: slot arity alone is no evidence (every 3-slot refcounted interface scored 7 against
                # EA::Audio::FactoryBinarySampleData; IHook -> EA::Audio::Group, IObj -> EA::Swarm::cIMap in manager2)
                self.notes.append(("class-map", "%s not mapped to %s: vtable slot shape (%d slots, score %d) without a name anchor" % (
                    s.name, best[1], len(vm), best[0])))
            elif best and best[0] >= len(vm) + 2:
                self.class_map[s.name] = best[1]
                self.why[s.name] = "vtable slot shape (%d slots, score %d)" % (len(vm), best[0])

    def _all_headers(self):
        if not hasattr(self, "_hdrs"):
            self._hdrs = []
            for root, _d, files in os.walk(INC):
                for f in files:
                    p = os.path.relpath(os.path.join(root, f), INC)[:-2]
                    if p.startswith(("eastl", "game", "EAMutex")):
                        continue
                    self._hdrs.append(p.replace(os.sep, "::").replace("/", "::"))
        return self._hdrs

    def map_from_short_names(self):
        for s in self.structs.values():
            if s.name in self.class_map or not s.members and not s.methods:
                continue
            for owner in set(self.class_map.values()):
                ns = "::".join(owner.split("::")[:-1])
                cand = (ns + "::" if ns else "") + s.name
                if cand in self.data.types.structs:
                    self.class_map[s.name] = cand
                    self.why[s.name] = "same short name in the owner's namespace (%s)" % ns
                    break

    # ---- node trees (slice side and canonical side) ------------------------------------------
    def slice_nodes(self, sname, base=0, prefix="", depth=0):
        """[(path, abs offset, size, kind, type text)] for a slice struct; paths are dotted from the owner."""
        d = self.views.get(sname)
        out = []
        if not d:
            return out
        for b in d.get("base_layout", []):
            out += self.slice_nodes(b["name"], base + (b["offset"] or 0), prefix, depth + 1)
        # sliceviews.py leaves offset/size null when it cannot lay the struct out (a template member such as
        # AtomicInt<int> or Vec<T>, an unknown base): the slice's own `// +0xNN` comments then give the offsets, and a
        # member's size is the distance to the next member
        ms = [m for m in d["members"] if not m.get("pad")]
        offs = [m["offset"] if m.get("offset") is not None else m.get("comment_offset") for m in ms]
        for i, m in enumerate(ms):
            off = offs[i]
            if off is None:
                continue
            size = m.get("size")
            if size is None:
                nxt = next((o for o in offs[i + 1:] if o is not None and o > off), None)
                if nxt is None:
                    continue
                size = nxt - off
            m = dict(m, offset=off, size=size)
            path = prefix + m["name"]
            t = m["type"]
            bt, ptr = base_type(t)
            arr = re.match(r"^(.*)\[(0x[0-9a-fA-F]+|\d+)\]$", t)
            if arr and ptr == 0 and arr.group(1).strip() in SCALARS | {"uint32_t", "uint32_t "} and int(arr.group(2), 0) <= 16:
                n = int(arr.group(2), 0)
                es = m["size"] // n
                out.append((path, base + m["offset"], m["size"], "comp", t))
                for i in range(n):
                    out.append(("%s[%d]" % (path, i), base + m["offset"] + i * es, es, "leaf", arr.group(1).strip()))
            elif ptr == 0 and bt in self.views and depth < 4:
                out.append((path, base + m["offset"], m["size"], "comp", t))
                out += self.slice_nodes(bt, base + m["offset"], path + ".", depth + 1)
            else:
                out.append((path, base + m["offset"], m["size"], "leaf", t))
        return out

    def canon_nodes(self, cls, base_path="", depth=0):
        """[(path, type text)] of the canonical class (members of bases included) and nested by-value members."""
        T = self.data.types
        c = Canon.get(cls)
        out = []
        for b in c.bases:
            out += self.canon_nodes(b, base_path, depth + 1)
        for m in c.members:
            path = base_path + m["name"]
            t = m["type"]
            out.append((path, t + (m["array"] or "")))
            if depth < 3 and not m["array"] and not t.rstrip().endswith("*") and t in T.structs:
                out += self.canon_nodes_pdb(t, path + ".", depth + 1)
        return out

    def canon_nodes_pdb(self, tname, prefix, depth):
        T = self.data.types
        L = T.layout(tname, "retail")
        out = []
        if not L:
            return out
        for b in L["bases"]:
            out += self.canon_nodes_pdb(b["name"], prefix, depth + 1)
        for m in L["members"]:
            if not m["name"] or m["name"].startswith("<"):
                continue
            t = H.cpp_type(m["type"] or "int") if m["type"] else "unsigned char"
            out.append((prefix + m["name"], t))
            if depth < 4 and m["type"] and m["type"].startswith("struct:") and m["type"][7:] in T.structs:
                out += self.canon_nodes_pdb(m["type"][7:], prefix + m["name"] + ".", depth + 1)
        return out

    # ---- VC9 probe -----------------------------------------------------------------------------
    def probe_classes(self, classes):
        """offsets/sizes of canonical nodes under VC9 -> self.probe[(cls, path)] = (offset, size).
        One compile error per node (cl stops at 100 errors, so nodes go in chunks of 90): the array
        dimension of `char (*p)[offset * 65536 + size + 1] = 1` is printed in the diagnostic."""
        if not hasattr(self, "probe"):
            self.probe = {}
            self._probed = set()
            self._nprobe = 0
        todo = [c for c in classes if c not in self._probed and Canon.get(c).exists]
        # per-class cache (work/migrate/probe_cache, keyed by class + include-tree stamp): every slice of a module probes the
        # same canonical classes, each chunk is a 1.5 s VC9 compile under wine (2026-10-18 profile: 7.4 of 11.4 s of a dry
        # run).  RW_NO_PROBE_CACHE=1 bypasses it
        for c in list(todo):
            hit = self.probe_cache_get(c)
            if hit is not None:
                for path, v in hit["got"]:
                    self.probe[(c, path)] = tuple(v)
                for path in hit["missing"]:
                    self.notes.append(("probe", "no VC9 offset for %s::%s (path does not compile)" % (c, path)))
                todo.remove(c)
                self._probed.add(c)
        if not todo:
            return
        incs = ["#include <stddef.h>"] + ['#include "%s"' % H.include_path(c) for c in todo]
        nodes = []
        for c in todo:
            seen = set()
            for path, _t in self.canon_nodes(c):
                if path not in seen:
                    seen.add(path)
                    nodes.append((c, path))
            nodes.append((c, ""))
        # cl stops at 100 errors (C1003).  A path that does not compile adds errors of its own (up to 25 extra in one chunk of
        # s00627d50), so a chunk can stop before its last lines: the nodes it never reached go back into the queue, and a
        # chunk that reached nothing is retried in halves.  Before (2026-10-18), those nodes were reported as "does not
        # compile", and which ones depended on how the classes happened to share chunks
        pending, size, incomplete = list(nodes), 90, set()
        while pending:
            chunk, pending = pending[:size], pending[size:]
            lines = []
            for i, (c, path) in enumerate(chunk):
                if path:
                    lines.append("char (*p%d)[offsetof(%s, %s) * 65536 + sizeof(((%s*)0)->%s) + 1] = 1;" % (i, c, path, c, path))
                else:
                    lines.append("char (*p%d)[sizeof(%s) + 1] = 1;" % (i, c))
            self._nprobe += 1
            p = os.path.join(self.scratch, "probe%d.cpp" % self._nprobe)
            open(p, "w").write("\n".join(incs + lines) + "\n")
            out = self.cl(p, extra=[])
            got = set()
            for m in re.finditer(r"\.cpp\((\d+)\) : error C2440: 'initializing' : cannot convert from 'int' to 'char \(\*\)\[(\d+)\]'", out):
                ln = int(m.group(1)) - len(incs) - 1
                if 0 <= ln < len(chunk):
                    c, path = chunk[ln]
                    v = int(m.group(2)) - 1
                    self.probe[(c, path)] = (v >> 16, v & 0xffff) if path else (0, v)
                    got.add(ln)
            reached = len(chunk) - 1
            if "C1003" in out:
                reached = max(got) if got else -1
                if reached < 0:
                    if size > 1:
                        size = max(1, size // 2)
                        pending = chunk + pending
                        continue
                    incomplete.add(chunk[0][0])     # one node alone exceeds 100 errors: its header does not compile
                    reached = 0
                else:
                    pending = chunk[reached + 1:] + pending
            for i, (c, path) in enumerate(chunk[:reached + 1]):
                if i not in got:
                    self.notes.append(("probe", "no VC9 offset for %s::%s (path does not compile)" % (c, path)))
        for c in todo:
            mine = [(path, self.probe[(c, path)]) for cc, path in nodes if cc == c and (c, path) in self.probe]
            if c not in incomplete and any(path == "" for path, _v in mine):   # its sizeof compiled: cacheable
                self.probe_cache_put(c, mine, [path for cc, path in nodes if cc == c and (c, path) not in self.probe])
        self._probed.update(todo)

    _inc_stamp = None

    @classmethod
    def include_stamp(cls):
        """Fingerprint of src/game/include (path, size, mtime of every file; ~10 ms): a probe's result is reused only while
        no header changed."""
        if cls._inc_stamp is None:
            h = hashlib.sha1()
            for d, _dirs, fs in sorted(os.walk(INC)):
                for f in sorted(fs):
                    st = os.stat(os.path.join(d, f))
                    h.update(("%s %d %d\n" % (os.path.join(d, f), st.st_size, st.st_mtime_ns)).encode())
            cls._inc_stamp = h.hexdigest()
        return cls._inc_stamp

    def _probe_cache_path(self, c):
        return W("work", "migrate", "probe_cache", hashlib.sha1((self.include_stamp() + "\n" + c).encode()).hexdigest() + ".json")

    def probe_cache_get(self, c):
        if os.environ.get("RW_NO_PROBE_CACHE"):
            return None
        try:
            return json.load(open(self._probe_cache_path(c)))
        except (OSError, ValueError):
            return None

    def probe_cache_put(self, c, got, missing):
        if os.environ.get("RW_NO_PROBE_CACHE"):
            return
        cp = self._probe_cache_path(c)
        os.makedirs(os.path.dirname(cp), exist_ok=True)
        fd, tmp = tempfile.mkstemp(dir=os.path.dirname(cp), prefix=".tmp")
        with os.fdopen(fd, "w") as f:
            json.dump({"class": c, "got": [[p, list(v)] for p, v in got], "missing": missing}, f)
        os.replace(tmp, cp)

    def cl(self, path, extra):
        w = lambda p: "Z:" + p.replace("/", "\\")
        cmd = [W("tools", "matching", "cl.sh"), "/nologo", "/c", "/O2", "/MD", "/Gy", "/TP", "/GS-", "/arch:SSE",
               "/I" + w(INC), "/Fo" + w(path[:-4] + ".obj")] + extra + [w(path)]
        r = subprocess.run(cmd, capture_output=True, text=True)
        return r.stdout + r.stderr

    # ---- 3. member maps ------------------------------------------------------------------------
    def map_from_members(self, sname, canon):
        """Pair the nodes of a slice struct with canonical nodes at the same (offset, size); structs that are
        member types of the pair get their canonical class from it."""
        if sname in self.members_map:
            return
        snodes = self.slice_nodes(sname)
        cnodes = {}
        for path, t in self.canon_nodes(canon):
            o = self.probe.get((canon, path))
            if o and o[0] is not None and o[1] is not None:
                cnodes[path] = (o[0], o[1], t)
        by_os = collections.defaultdict(list)
        for path, (o, s, t) in cnodes.items():
            by_os[(o, s)].append((path, t))
        mp = {}
        used = set()
        # fraction of the slice's own (non-array) leaf nodes that a canonical parent struct has a direct node for
        sleaf = {(off, size) for path, off, size, kind, t in snodes if kind == "leaf" and "[" not in path}
        parent_os = collections.defaultdict(set)
        for path, (o, sz, t) in cnodes.items():
            parent_os[path.rpartition(".")[0]].add((o, sz))

        def coverage(cpath):
            return len(sleaf & parent_os[cpath.rpartition(".")[0]]) / float(len(sleaf) or 1)
        for path, off, size, kind, t in snodes:
            cands = by_os.get((off, size), [])
            # prefer a candidate of the same kind (a composite pairs with a struct-typed node), then the shallowest
            def is_comp(ct):
                return ct in self.data.types.structs and not ct.rstrip().endswith(("*", "&"))
            is_arr = bool(re.match(r"^.*\[(?:0x[0-9a-fA-F]+|\d+)\]$", t))
            pick = [c for c in cands if (is_comp(c[1]) == (kind == "comp")) and (c[0] not in used or is_arr)]
            if not pick:
                pick = [c for c in cands if c[0] not in used and kind != "comp"]
            if pick:
                # several canonical nodes at one (offset, size) are the members of a union (EA::Variant: mInt32, mFloat,
                # mPointer.mpData ...).  Pick the one whose name is closest to the slice member's, plus the one whose
                # parent struct can hold the slice's other members too (all of mpData/mnItemSize/mnItemCount fit
                # mPointer), before the shallowest.
                pick.sort(key=lambda c: (-(self.leaf_name_sim(path, c[0]) + coverage(c[0])), c[0].count("."), len(c[0])))
                mp[path] = (pick[0][0], t, pick[0][1])
                am = re.match(r"^(.*?)\s*\[(?:0x[0-9a-fA-F]+|\d+)\]$", t)
                if am and "[" not in pick[0][1]:
                    # an array of words over a canonical struct (PFHeader.f[10] over PFDatabaseHeader): indexed accesses
                    # go through a word pointer
                    mp[path] = ("\x05%s\x05%s" % (pick[0][0], am.group(1).strip()), t, pick[0][1])
                # a scalar the slice reads where the canonical member is a struct of the same size (the slice's `unsigned char
                # mCompare` is the 1-byte comparator `less<unsigned int>`): reads go through a typed view of the same byte
                elif kind == "leaf" and t.strip() in SCALARS and is_comp(pick[0][1]) and size == cnodes[pick[0][0]][1]:
                    mp[path] = ("\x07%s\x07%s" % (pick[0][0], t.strip()), t, pick[0][1])
                # a word pointer over a canonical pointer of another type (the slice's `uint32 *mapBucketArray` is
                # `hash_node<..> **mpBucketArray`; the slice walks the nodes as words): reads go through a cast, which
                # compiles to the same load
                elif kind == "leaf" and t.strip().endswith("*") and pick[0][1].strip().endswith("*") and \
                        norm_type(t) != norm_type(pick[0][1]) and base_type(t)[1] == 1 and \
                        base_type(t)[0] in ("uint32", "uint16", "uint8", "uint32_t", "uint16_t", "uint8_t", "int", "unsigned", "unsigned int", "char"):
                    mp[path] = ("\x06%s\x06%s" % (pick[0][0], t.strip()), t, pick[0][1])
                used.add(pick[0][0])
            elif path in cnodes and cnodes[path][0] == off and path not in used:
                # same name at the same offset, size differs (the slice's FileStream is a word short of retail's)
                mp[path] = (path, t, cnodes[path][2])
                used.add(path)
        # a slice word that is half of a canonical 8-byte member (the slice splits an int64 into two words)
        for path, off, size, kind, t in snodes:
            if path in mp or kind != "leaf" or size not in (1, 2, 4):
                continue
            for cpath, (co, cs, ct) in cnodes.items():
                if co <= off < co + cs and cs > size and cs in (8,) and ct.strip() in ("__int64", "unsigned __int64", "long long"):
                    mp[path] = ("\x03%s\x03%d\x03%s" % (cpath, (off - co) // size, {1: "unsigned char", 2: "unsigned short", 4: "unsigned int"}[size]), t, None)
                    break
        # manual member renames win
        for k, v in self.manual.get("members", {}).get(sname, {}).items():
            mp[k] = (v, None, None)
        self.members_map[sname] = mp
        # propagate class mapping to member types
        T = self.data.types
        for path, (cpath, stype, ctype) in mp.items():
            if not stype or not ctype:
                continue
            sb, sptr = base_type(stype)
            ct = ctype.strip()
            cb = ct.rstrip("*& ").strip()
            cptr = ct[len(cb):].count("*") + ct[len(cb):].count("&")
            if sb not in self.structs or sb in self.class_map or sptr != cptr:
                continue
            if cb not in T.structs and not cb.startswith("eastl::"):
                continue
            if sptr:        # through a pointer the pointee may be a base or a derived class: sizes must agree
                vs = self.views.get(sb, {}).get("size")
                cl = T.layout(cb, "retail")
                if vs and cl and cl["size"] != vs:
                    self.notes.append(("class-map", "%s not mapped to %s through the pointer member %s: sizes 0x%x vs 0x%x" % (
                        sb, cb, path, vs, cl["size"])))
                    continue
            self.class_map[sb] = cb
            self.why[sb] = "type of the member at the same offset in %s: %s %s" % (canon, ctype, cpath)
        self.unpaired = getattr(self, "unpaired", {})
        self.unpaired[sname] = [p for (p, off, size, kind, t) in snodes if p not in mp and kind == "leaf" and p not in ("d",)]

    @staticmethod
    def leaf_name_sim(spath, cpath):
        """similarity of the last components of a slice member path and a canonical member path, Hungarian prefix (m, mn,
        mp, mb, mf) dropped: mpData ~ mPointer.mpData, mnItemCount ~ mElementCount (shares 'Count')."""
        strip = lambda n: re.sub(r"\[\d+\]$", "", n.rpartition(".")[2]).lstrip("m").lstrip("npbf") if n else n
        sn, cn = strip(spath), strip(cpath)
        return word_sim(sn, cn) if sn and cn else 0.0

    # ---- 4. methods ------------------------------------------------------------------------------
    @staticmethod
    def kind_of(t):
        t = t.strip()
        if t.endswith("&") or t.endswith("& const"):
            return "ref"
        if t.endswith("*") or "[" in t or t.endswith("* const"):
            return "ptr"
        if re.search(r"\bbool\b", t):
            return "bool"
        if re.search(r"\b(float|double)\b", t):
            return "float"
        return "int"

    @staticmethod
    def ptype(p):
        """type part of a parameter declaration 'const Key* key' -> 'const Key*'."""
        p = p.strip()
        m = re.match(r"^(.*?)(\w+)(\s*\[[^\]]*\])?$", p)
        if m and m.group(1).strip() and not m.group(1).strip().endswith(("::", "<", ",")):
            t = m.group(1).strip()
            return t + (m.group(3) or "")
        return p

    @staticmethod
    def pname(p, i):
        m = re.match(r"^(.*?)(\w+)(\s*\[[^\]]*\])?$", p.strip())
        if m and m.group(1).strip() and not m.group(1).strip().endswith(("::", "<", ",")):
            return m.group(2)
        return "a%d" % i

    def shape(self, sparams, cparams):
        if len(sparams) != len(cparams):
            return None
        if not sparams:
            return 1.0
        sc = 0.0
        for sp, cp in zip(sparams, cparams):
            a, b = self.kind_of(self.ptype(sp)), self.kind_of(cp)
            if a == b:
                sc += 1
            elif {a, b} == {"ptr", "ref"}:
                sc += 0.8
            elif {a, b} <= {"int", "bool"}:
                sc += 0.6
        return sc / len(sparams)

    def choose_decl(self, name, sparams, va, cls, claimed, sret=None):
        """canonical declaration for a slice method of a mapped class; -> (decl, how) or (None, why)."""
        short = cls.split("::")[-1]
        if va:
            # the header's destructor line `virtual ~X(); // slot 0, 0x<A>, dtor body 0x<B>`: A is the scalar deleting
            # destructor (??_G, compiler-generated: no source spelling, so the slice body stays verbatim), B the destructor
            # itself whatever the slice calls it (s0094fb80 0x94fe70 was shape-guessed as SetMode, s00936090 0x936920 as
            # IsValidLibrary, s008117f0 0x811f80 as Shutdown; fix pass 3)
            for d in canon_methods(cls):
                if not d.dtor:
                    continue
                mb = re.search(r"dtor body 0x([0-9a-fA-F]{6,8})", d.cmt or "")
                if mb and int(mb.group(1), 16) == va:
                    return d, "destructor by retail address (the header's dtor body 0x%08x)" % va
                if d.va == va and not (d.virtual and d.slot is not None):
                    return d, "destructor by retail address 0x%08x (non-virtual)" % va
                if d.va == va:
                    return None, "scalar deleting destructor of %s (the header's slot-0 address 0x%08x): compiler-generated, " \
                        "kept verbatim" % (cls, va)
        if name == short or name == "~" + short:        # constructor / destructor of the class
            ctors = [d for d in canon_methods(cls) if (d.ctor if name == short else d.dtor) and d.name == name]
            if name != short:
                return (ctors[0], "destructor") if ctors else (None, "no destructor declared")
            byva = [d for d in ctors if va and d.va == va]
            hit = byva or [d for d in ctors if len(d.params) == len(sparams)]
            return (hit[0], "constructor by %s" % ("address" if byva else "arity")) if len(hit) == 1 else \
                (None, "%d constructors match (%d parameters)" % (len(hit), len(sparams)))
        if va:
            # the slice models a constructor as a method returning `this` (`void* PFIndexModifiable_(void* allocator)`): when
            # the retail address is the one the generated header gives the class's constructor, it is that constructor
            cb = [d for d in canon_methods(cls) if d.ctor and d.name == short and d.va == va]
            if len(cb) == 1 and len(cb[0].params) >= len(sparams):
                return cb[0], "constructor by retail address 0x%08x (the slice models it as a method returning this)" % va
        decls = [d for d in canon_methods(cls) if not d.ctor and not d.dtor]
        man = self.manual.get("methods", {})
        key = "%08x" % va if va else None
        for k in (key, "%s::%s" % (self.cur_slice_cls, name)):
            if k and k in man:
                want = man[k]
                hit = [d for d in decls if d.name == want and len(d.params) == len(sparams)]
                if not hit:
                    # the slice stub left out trailing parameters the canonical method has (s0091e650 EndSection 0x91ea80:
                    # slice `void EndSection()`, retail `ret 4`, canonical `bool EndSection(char const *)`): the manual name
                    # wins when exactly one overload has more parameters; they are named a<n>..
                    more = [d for d in decls if d.name == want and len(d.params) > len(sparams)]
                    hit = more if len(more) == 1 else []
                if hit:
                    return hit[0], "manual: %s" % self.manual.get("why", {}).get(k, "renames file")
        if va:
            hit = [d for d in decls if d.va == va]
            if len(hit) == 1:
                if len(hit[0].params) == len(sparams):
                    return hit[0], "retail address 0x%08x" % va
                if len(hit[0].params) > len(sparams):
                    # an incomplete slice stub (`bool Write() { return false; }` for WriteToMemory(void*&, uint&, uint, bool)):
                    # the address names the method, the slice just did not declare all its parameters (never more than
                    # the canonical method has: that is how 0x8d88d0 InternalSetPosition was told from InternalRead)
                    self.notes.append(("method", "0x%08x %s: slice declares %d parameters, %s takes %d: trailing parameters named a%d.." % (
                        va, name, len(sparams), hit[0].name, len(hit[0].params), len(sparams) + 1)))
                    return hit[0], "retail address 0x%08x (incomplete slice stub: %d of %d parameters)" % (va, len(sparams), len(hit[0].params))
                self.notes.append(("method", "0x%08x %s: address names %s (%d params) but the slice has %d: address evidence rejected" % (
                    va, name, hit[0].name, len(hit[0].params), len(sparams))))
        if va:
            # the slice function has the name of a method of the class, but the class's header puts that method at another
            # retail address: this is another function of the same name (0x6bbe20 AsInterface of a sibling class with its
            # own interface id; the class's is 0x8d81a0, slot 3 of the secondary vtable 0x143679c)
            other = [d for d in decls if d.name == name and d.va and d.va != va and len(d.params) == len(sparams)]
            if other and not [d for d in decls if d.va == va]:
                return None, "address contradiction: %s is at 0x%08x in the header of %s, this function is at 0x%08x" % (
                    name, other[0].va, cls, va)
        same = [d for d in decls if d.name == name and len(d.params) == len(sparams) and d not in claimed]
        if len(same) == 1:
            return same[0], "same name and arity"
        cand = []
        for d in decls:
            if d in claimed:
                continue
            # fix pass 6 B: a method the header puts at another retail address is another function (AudioSystem 0xa2f1a0 ->
            # Init 0xa252b0, EditorUI 0x5de690 -> EnableUIButton 0x5dc610), and the names must agree up to case and
            # underscores (dev-only Login for PostGetAssetFeed, AsInterface for Init, AddRef for a destructor)
            if va and d.va and d.va != va:
                continue
            if name_key(name) != name_key(d.name):
                continue
            sh = self.shape(sparams, d.params)
            if sh is None:
                continue
            cn = re.sub(r"^Internal", "", d.name)
            sim = max(word_sim(name, d.name), word_sim(name, cn))
            if name.lower() in d.name.lower() or cn.lower() in name.lower():
                sim = min(0.95, sim + 0.3)
            if name == d.name:
                sim = 1.0
            # overloads that differ only in constness (GetProperty(key, Variant**) / GetProperty(key, Variant const**) const):
            # the slice definition's own constness breaks the tie
            cc = getattr(self, "cur_const", None)
            bonus = 0.1 if cc is not None and d.const == cc else 0.0
            cand.append((0.5 * sh + 0.5 * sim + bonus, sh, sim, d))
        cand.sort(key=lambda x: -x[0])
        if cand and cand[0][0] >= 0.62 and (len(cand) == 1 or cand[0][0] - cand[1][0] >= 0.08):
            return cand[0][3], "shape+name (score %.2f, runner-up %.2f)" % (cand[0][0], cand[1][0] if len(cand) > 1 else 0)
        return None, "no unique canonical method (best: %s)" % ", ".join("%s %.2f" % (x[3].name, x[0]) for x in cand[:3])

    def map_methods(self):
        self.chunk_vas = {c.va for c in self.chunks}
        claimed = set()
        order = sorted(self.chunks, key=lambda c: c.va)
        # pass 1: address evidence first, so that later shape guesses do not steal those declarations
        for c in order:
            self.cur_slice_cls = c.cls
            self.cur_const = c.const
            cls = self.fn_class.get(c.va)
            c.decl, c.how = None, None
            if c.free:
                # namespace function: the dev public's declaration, with the slice's parameter names; the slice may
                # declare fewer parameters than the function takes (an incomplete stub), never more
                d = c.free_decl
                if d is None:
                    c.how = c.free_why or "no canonical declaration"
                elif len(c.params) > len(d.params):
                    c.how = "slice has %d parameters, the dev function %d: declaration rejected" % (len(c.params), len(d.params))
                else:
                    c.decl, c.how = d, c.free_why
                    if len(c.params) < len(d.params):
                        self.notes.append(("method", "0x%08x %s: slice declares %d parameters, the dev function takes %d: trailing parameters named a%d.. " % (
                            c.va, d.name, len(c.params), len(d.params), len(c.params) + 1)))
                continue
            if not c.ok or not cls or Canon.get(cls).exists is False:
                c.how = "no canonical class" + (" (%s)" % self.refused[c.cls] if c.cls in getattr(self, "refused", {}) else "")
                continue
            d, how = self.choose_decl(c.name, c.params, c.va, cls, claimed, c.ret)
            if d is not None and how.startswith(("retail", "manual")):
                c.decl, c.how = d, how
                claimed.add(d)
        for c in order:
            if c.decl is not None or not c.ok:
                continue
            self.cur_slice_cls = c.cls
            self.cur_const = c.const
            cls = self.fn_class.get(c.va)
            if not cls:
                continue
            d, how = self.choose_decl(c.name, c.params, c.va, cls, claimed, c.ret)
            c.decl, c.how = d, how
            if d is not None:
                claimed.add(d)
        for c in order:
            if c.decl is not None and not c.free:
                d = copy.copy(c.decl)            # the slice definition's own return type travels with the declaration
                d.slice_ret = c.ret
                self.method_map[c.cls][c.name] = d
        # methods of the other mapped structs (calls in bodies): virtual slots by index, else address, else shape+name
        self.mm_how = {}
        for sname, canon in self.class_map.items():
            st = self.structs.get(sname)
            if not st:
                continue
            cc = Canon.get(canon)
            for m in st.methods:
                if m["ctor"]:
                    continue
                if m["name"] in self.method_map.get(sname, {}):     # a class the slice also defines methods of: the declared-only ones
                    continue
                d = None
                if m["virtual"] and m["slot"] in cc.slots and len(cc.slots[m["slot"]].params) == len(m["params"]):
                    d = cc.slots[m["slot"]]
                    how = "vtable slot %d" % m["slot"]
                elif m["va"]:
                    hit = [x for x in canon_methods(canon) if x.va == m["va"] and not x.ctor]
                    if len(hit) == 1 and len(hit[0].params) == len(m["params"]):
                        d, how = hit[0], "retail address 0x%08x" % m["va"]
                    elif not hit:
                        # a method no header binds to an address ("dev only") that an earlier slice already migrated: the
                        # module TU holds `// @ 0xVA` + `bool EA::ResourceMan::DatabasePackedFile::CloseOpenRecords()`
                        tu = self.tu_methods().get(m["va"])
                        hit = [x for x in canon_methods(canon) if tu and tu[0] == canon and x.name == tu[1] and not x.ctor
                               and len(x.params) == len(m["params"])]
                        if len(hit) == 1:
                            d, how = hit[0], "retail address 0x%08x is %s in the module TU" % (m["va"], tu[1])
                if d is None:
                    self.cur_slice_cls = sname
                    self.cur_const = None
                    mkey = "%s::%s" % (sname, m["name"])
                    dd, how = self.choose_decl(m["name"], m["params"], None, canon, set(), None)
                    d = dd
                if d is not None:
                    d = copy.copy(d)                  # the slice's own return type travels with the declaration (convert_chains)
                    d.slice_ret = m["ret"]
                    self.method_map[sname][m["name"]] = d
                    self.mm_how["%s::%s" % (sname, m["name"])] = how
                else:
                    self.notes.append(("method", "%s::%s: %s" % (sname, m["name"], how)))
            for m in st.methods:
                if m["ctor"] or m["name"] in self.method_map[sname] or not m["va"]:
                    continue
        # the manual entries for structs whose methods evidence cannot name
        for k, v in self.manual.get("method_names", {}).items():
            sname, mname = k.split("::")
            self.method_map[sname][mname] = CanonDecl(name=v, ret="", params=[], const=False, virtual=False, static=False,
                                                       slot=None, va=None, access="public", cmt="manual", ctor=False,
                                                       dtor=False, manual=True)

    # ---- 5. function bodies --------------------------------------------------------------------
    def env_for(self, c):
        env = {}
        for i, p in enumerate(c.params):
            env[self.pname(p, i)] = self.ptype(p)
        return env

    def collect_locals(self, body, env):
        m = mask(body)
        known = set(self.structs) | SCALARS | {"bool", "char", "int", "float", "unsigned", "double", "long", "short"}
        for mm in re.finditer(r"(?:^|[;{}(])\s*((?:const\s+)?[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*(?:\s*\*+)?)\s+(\w+)\s*(\[[^\]]*\])?\s*(?==|;|,|\))", m):
            t, n, arr = mm.group(1).strip(), mm.group(2), mm.group(3)
            bt = base_type(t)[0]
            if bt in ("return", "else", "goto", "delete", "new", "case", "typedef", "sizeof", "throw"):
                continue
            if bt in known or bt.split()[-1] in known:
                env[n] = t + (arr or "")
        return env

    def this_member_path(self, sname, elems):
        """Longest prefix of elems (list of ('name'|'idx', text)) that is a node path of slice struct sname:
        -> (consumed, canonical path, slice type of the node) or None."""
        mp = self.members_map.get(sname)
        if mp is None:
            return None
        best = None
        for n in range(1, len(elems) + 1):
            path = ""
            for k, (kind, text) in enumerate(elems[:n]):
                path += ("." + text if path else text) if kind == "name" else "[%s]" % text
            if path in mp:
                best = (n, mp[path][0], mp[path][1], mp[path][2])
        return best

    def type_of_chain_member(self, sname, name):
        """slice type text of a direct member `name` of slice struct sname (bases included)."""
        d = self.views.get(sname)
        if not d:
            return None
        for b in d.get("base_layout", []):
            t = self.type_of_chain_member(b["name"], name)
            if t:
                return t
        for m in d["members"]:
            if m["name"] == name:
                return m["type"]
        return None

    def resolve_chain(self, start_type, elems, this_struct=None):
        """Rewrite the member accesses of a chain.  start_type: slice struct name of the object the chain starts at
        (the implicit this for bare members).  elems: [('name'|'idx', text, op)] after the start.  Returns
        (new elems text list, slice struct name of the end, unresolved bool)."""
        out = []
        cur = start_type
        i = 0
        n = len(elems)
        while i < n:
            if cur is None or cur not in self.members_map:
                # unmapped owner: copy the rest through
                out += [(e[2], e[1], e[0]) for e in elems[i:]]
                return out, None
            hit = self.this_member_path(cur, [(e[0], e[1]) for e in elems[i:]])
            if hit:
                used, cpath, stype, _ct = hit
                out.append((elems[i][2], cpath, "path"))
                i += used
                cur = base_type(stype)[0] if stype else None
                continue
            out.append((elems[i][2], elems[i][1], elems[i][0]))
            t = self.type_of_chain_member(cur, elems[i][1]) if elems[i][0] == "name" else None
            cur = base_type(t)[0] if t else None
            i += 1
        return out, cur

    def rewrite_body(self, c):
        body = c.body
        S = c.cls
        self.retype = {}
        env = self.collect_locals(body, self.env_for(c))
        self.pointer_locals(c, body, env)
        c.env = env
        notes = []
        ref_params = {}
        if c.decl is not None:
            for i, (sp, cp) in enumerate(zip(c.params, c.decl.params)):
                if self.kind_of(self.ptype(sp)) == "ptr" and self.kind_of(cp) == "ref":
                    ref_params[self.pname(sp, i)] = base_type(self.ptype(sp))[0]
        # 0a. one-line accessors the slice struct defines inline (`HoleSet& HoleA() { return mActive.mHoles; }`)
        body = self.inline_accessors(c, body, notes)
        # 0. a virtual of a secondary base: the slice's `this` is the subobject pointer
        body = self.secondary_this(c, body, notes)
        # 1. virtual-call thunks
        body = self.convert_thunks(c, body, env, notes)
        # 2. allocation idiom
        body = self.convert_alloc(c, body, env, notes)
        # 3. drop vptr stores into stub objects
        body = self.drop_vptr_stores(c, body, env, notes)
        # 3b. constructors/destructors of a canonical class: the compiler stores the class's own vptrs (`vt0 = vtbl_DPF0;
        # vt4 = vtbl_DPF4;` of the slice's stub base classes), and a destructor stores them first
        if c.decl is not None and (c.decl.dtor or c.decl.ctor):
            body, nv = re.subn(r"^[ \t]*(?:this\s*->\s*)?vt\d*\s*=\s*vtbl_\w+\s*;[ \t]*\n", "", body, flags=re.M)
            if nv:
                self.stats["vptr_stores_dropped"] += nv
                notes.append("%d vptr store(s) of the class's own vtables dropped (the compiler stores them)" % nv)
        # 4. chains
        body = self.convert_chains(c, body, env, ref_params, notes)
        body = re.sub(r"\(\((?:unsigned int|uint32_t) \*\)&([\w.]+)\)\[0\] = ([^;\n]+);(\s*)\n(\s*)\(\((?:unsigned int|uint32_t) \*\)&\1\)\[1\] = 0;",
                      lambda mm: "%s = %s;" % (mm.group(1), mm.group(2)), body)
        # 5. types
        body = self.convert_types(c, body)
        # 5b. a constructor's member-initialiser list
        body = self.convert_init_list(c, body, notes)
        # 6. externs
        body = self.convert_externs(c, body)
        body = body.replace("\x01", "")
        for v, (old, new) in self.retype.items():
            body, n = re.subn(r"(?<![\w:])%s(\s+)%s\b" % (re.escape(old), re.escape(v)), lambda mm: new + mm.group(1) + v, body, count=1)
            notes.append("local %s: %s -> %s%s" % (v, old, new, "" if n else " (declaration not found)"))
        # an incomplete slice stub (`// TODO(partial)`) that returns a placeholder value from a method the canonical class declares
        # void (`void* PutFileInfo(..) { return 0; }` for AddRecord): the placeholder goes
        if c.decl is not None and c.decl.ret.strip() == "void" and "TODO(partial" in body:
            body, nret = re.subn(r"\breturn\s+[^;]+;", "return;", body)
            if nret:
                notes.append("stub placeholder `return <value>;` -> `return;` (canonical return type is void) (%d)" % nret)
        # a constructor modelled as a method returning this: the value is gone
        if c.decl is not None and getattr(c.decl, "ctor", False):
            body, nret = re.subn(r"\breturn\s+this\s*;", "return;", body)
            if nret:
                notes.append("constructor: `return this;` -> `return;` (%d)" % nret)
        # 6b. a slice method that returns a pointer where the canonical one returns a reference (`Variant* GetPropertyValue(key)`
        # is `Variant const & GetProperty(key) const`): `return &x;` -> `return x;`, `return p;` -> `return *p;`
        if c.decl is not None and c.ret and c.ret.rstrip().endswith("*") and c.decl.ret.rstrip().endswith("&"):
            def _ret(mm):
                e = mm.group(1).strip()
                inner = re.match(r"^\(\(([\w: ]+?)\s*\*\)\s*&\s*(.*)\)$", e, re.S)        # ((T *)&Call(..)) made by the call rule
                if inner:
                    return "return %s;" % inner.group(2)
                if re.match(r"^&\s*\w+(?:(?:\.|->)\w+|\[[^\]]*\])*$", e):
                    return "return %s;" % e[1:].strip()
                return "return *(%s);" % e
            mb = mask(body)
            out, last = [], 0
            for mm in re.finditer(r"\breturn\s+([^;]+);", mb):
                out.append(body[last:mm.start()])
                out.append(_ret(re.match(r"return\s+([^;]+);", body[mm.start():mm.end()], re.S)))
                last = mm.end()
            out.append(body[last:])
            body = "".join(out)
            self.stats["pointer_returns_to_reference"] += 1
        # 6c. the slice declared a variadic method with an explicit `va_list ap` last parameter where the canonical method takes
        # `...` (s0091e650 0x91ead0: retail is `lea eax,[esp+0x14] / push eax`, i.e. va_start on the stack arguments, not a
        # va_list argument): the definition gets the ellipsis and the body starts with `va_list ap; va_start(ap, <last>);`
        if c.decl is not None and len(c.params) >= 2 and len(c.params) == len(c.decl.params) and \
                c.decl.params[-1].strip() == "..." and re.match(r"^\s*va_list\s+\w+\s*$", c.params[-1]):
            ap = c.params[-1].split()[-1]
            last = self.pname(c.params[-2], len(c.params) - 2)
            k = body.find("{")
            if k >= 0 and not re.search(r"\bva_start\s*\(", body):
                body = body[:k + 1] + "\n    va_list %s;\n    va_start(%s, %s);" % (ap, ap, last) + body[k + 1:]
                notes.append("va_list parameter %s -> ellipsis + va_start(%s, %s)" % (ap, ap, last))
                self.stats["va_list_to_ellipsis"] += 1
        # 6d. a parameter the slice typed `void *` (or a typedef of it) that the canonical declaration types `T *`: assignments
        # to it from the slice's untyped callees get the cast (s0091e650 GetTimeString/GetDateString: `tm = _localtime64(&t);`
        # where the slice's _localtime64 returns void* and the parameter is `tm const *`)
        if c.decl is not None:
            for i, (sp, cp) in enumerate(zip(c.params, c.decl.params)):
                st = self.ptype(sp).replace(" ", "")
                if st not in ("void*", "constvoid*") and not self.is_void_ptr_typedef(st):
                    continue
                ct = cp.strip()
                if not ct.endswith("*") or re.match(r"^(const\s+)?void\s*\*$|^void\s+const\s*\*$", ct):
                    continue
                nm = self.pname(sp, i)
                # a parameter named like its own type (`tm const * tm`) hides the type name: elaborate it
                cast = ct
                b0 = re.match(r"^(?:const\s+)?(\w+)", ct)
                if b0 and b0.group(1) == nm:
                    cast = "struct " + ct
                body, na = re.subn(r"(?<![\w.>])(%s\s*=\s*)(?!=)([^;]+);" % re.escape(nm), lambda mm: "%s(%s)%s;" % (mm.group(1), cast, mm.group(2).strip()), body)
                if na:
                    notes.append("parameter %s: void* slice type, canonical %s: %d assignment(s) cast" % (nm, ct, na))
                    self.stats["void_ptr_param_casts"] += na
        # 6d'. a parameter the slice typed as an integer that the canonical declaration types `T *` (s0091f520
        # WriteStackMemoryView(unsigned lo, int len) is `(unsigned char const *, unsigned int)`): the body keeps its integer
        # arithmetic on a local copy `unsigned lo_v = (unsigned)lo;`
        if c.decl is not None:
            for i, (sp, cp) in enumerate(zip(c.params, c.decl.params)):
                st = re.sub(r"\s+", " ", self.ptype(sp)).strip()
                if st not in ("unsigned", "unsigned int", "int", "uint32_t", "int32_t", "long", "unsigned long", "DWORD", "uint32") or \
                        not cp.strip().endswith("*"):
                    continue
                nm = self.pname(sp, i)
                k = body.find("{")
                if k < 0 or not re.search(r"(?<![\w.>])%s\b" % re.escape(nm), body[k:]):
                    continue
                inner = re.sub(r"(?<![\w.>:])%s\b" % re.escape(nm), nm + "_v", body[k + 1:])
                body = body[:k + 1] + "\n    %s %s_v = (%s)%s;" % (st, nm, st, nm) + inner
                notes.append("parameter %s: integer %s in the slice, canonical %s: the body uses a local copy %s_v" % (nm, st, cp.strip(), nm))
                self.stats["int_param_local_copies"] += 1
        # 6e. the same for a data member of the function's class: the slice typed it `void *` (`void* mpFile;`), the canonical
        # member is `T *` (`_iobuf* mpFile;`): `mpFile = fopen(..)` (the slice's fopen returns its FILEP = void*) gets the cast
        # (s0091e650 OpenReport 0x91e9c0)
        st_ = self.structs.get(S) if S else None
        if c.decl is not None and st_ is not None and not c.free and c.va in self.fn_class:
            canon_c = Canon.get(self.fn_class[c.va])
            for m in st_.members:
                mt = m["type"].replace(" ", "")
                if m.get("array") or (mt not in ("void*",) and not self.is_void_ptr_typedef(mt)):
                    continue
                cm = canon_c.member(m["name"]) if canon_c.exists else None
                ct = (cm or {}).get("type", "").strip()
                if not ct.endswith("*") or ct.replace(" ", "") in ("void*", "constvoid*") or (cm or {}).get("array"):
                    continue
                body, na = re.subn(r"(?<![\w.>])((?:this\s*->\s*)?%s\s*=\s*)(?!=)(?!0\s*;)([^;]+);" % re.escape(m["name"]),
                                   lambda mm: "%s(%s)%s;" % (mm.group(1), ct, mm.group(2).strip()), body)
                if na:
                    notes.append("member %s: void* in the slice, canonical %s: %d assignment(s) cast" % (m["name"], ct, na))
                    self.stats["void_ptr_member_casts"] += na
        # 7. manual edits
        for e in self.manual.get("edits", []):
            if int(e["va"], 16) == c.va:
                if e["find"] not in body:
                    notes.append("manual edit not applicable (text not found): %r" % e["find"][:60])
                else:
                    body = body.replace(e["find"], e["replace"], 1)
                    self.stats["manual_edits_applied"] += 1
        c.out_body = body
        c.notes = notes

    def is_void_ptr_typedef(self, t):
        """True when t is a slice typedef of void* (`typedef void* FILEP;`)."""
        for kind, text in self.items:
            if kind == "typedef" and re.match(r"^\s*typedef\s+void\s*\*\s*%s\s*;" % re.escape(t), text):
                return True
        return False

    def convert_init_list(self, c, body, notes):
        """`: SP::cResourceBase(name), mParent.mpObject(0), mCount(0) {` of a constructor, after member and type conversion.
        Two entries do not survive the conversion and are rewritten by rule:
          - a base initialiser whose arguments the canonical base constructors do not take (the slice's base stub took an
            unused name): the base's default constructor is called, when it has one;
          - `a.b(0)` where `a` is a by-value wrapper whose only member `b` the slice saw as a raw pointer (AutoRefCount):
            `a()` (value-initialisation of the wrapper stores the same zero)."""
        if c.decl is None or not c.decl.ctor or not body.lstrip().startswith(":"):
            return body
        mb = mask(body)
        d0 = 0
        ob = None
        for i, ch in enumerate(mb):
            if ch == "(":
                d0 += 1
            elif ch == ")":
                d0 -= 1
            elif ch == "{" and d0 == 0:
                ob = i
                break
        if ob is None:
            return body
        head = body[:ob]
        entries = split_top(head.lstrip()[1:], mask(head.lstrip()[1:]))
        cls = self.fn_class.get(c.va)
        bases = Canon.get(cls).bases if cls else []
        out = []
        for e in entries:
            e = e.strip()
            mm = re.match(r"^(?P<n>[\w:]+(?:\.\w+)*)\s*\((?P<a>.*)\)$", e, re.S)
            if not mm:
                out.append(e)
                continue
            n, a = mm.group("n"), mm.group("a").strip()
            q = n if n in bases else next((b for b in bases if b.split("::")[-1] == n.split("::")[-1]), None)
            if q and a:
                short = q.split("::")[-1]
                ctors = [d for d in canon_methods(q) if d.ctor and d.name == short and
                         not (len(d.params) == 1 and "&" in d.params[0] and short in d.params[0])]      # not the copy constructor
                nargs = len(split_top(a, mask(a)))
                if ctors and not any(len(d.params) == nargs for d in ctors) and any(not d.params for d in ctors):
                    notes.append("base %s initialised with its default constructor (the canonical constructors take no %d argument(s))" % (q, nargs))
                    e = "%s()" % n
            elif "." in n and a == "0":
                e = "%s()" % n.rsplit(".", 1)[0]
                notes.append("by-value wrapper member %s zero-initialised" % n.rsplit(".", 1)[0])
            out.append(e)
        return "\n: " + ", ".join(out) + " " + body[ob:]

    ACCESSOR = re.compile(r"[\w:<>\*&\s]*?\b(\w+)\s*\(\s*\)\s*(?:const\s*)?\{\s*return\s+([^;{}]+?)\s*;\s*\}")

    def inline_accessors(self, c, body, notes):
        """Calls of the one-line accessors of the function's own slice struct become the member expression they return, which
        the member-chain rules then map to the canonical path (HoleA().Reset(0) -> mActiveHoleTable.Reset(0))."""
        st = self.structs.get(c.cls)
        if not st:
            return body
        for line in st.text.split("\n"):
            mm = self.ACCESSOR.match(line.strip())
            if not mm or "(" in mm.group(2):
                continue
            name, expr = mm.group(1), mm.group(2).strip()
            body, n = re.subn(r"(?<![\w.:>])%s\s*\(\s*\)" % re.escape(name), expr, body)
            if n:
                self.stats["accessors_inlined"] += n
                notes.append("inline accessor %s() -> %s x%d" % (name, expr, n))
        return body

    def secondary_this(self, c, body, notes):
        """A virtual method that the canonical class declares in the vtable of a secondary base (AsInterface, slot 3 of
        the IUnknown32 vtable at +4) is compiled by VC9 with `this` = the subobject pointer and the adjustment inline;
        the slice, which has no base classes, spells the full object as `(char *)this - K` and the subobject as `this`
        (behind a null test, the pointer-upcast idiom `(uint32_t)(-(int)(P != 0)) & (uint32_t)this`, or bare).  In the
        canonical class `this` is the full object: `(char *)this - K` -> `this`, the subobject -> `static_cast<Base *>(this)`
        (measured on AsInterface 0x8d81a0 and the sibling class's 0x6bbe20: instruction-identical)."""
        d = c.decl
        cls = self.fn_class.get(c.va)
        if d is None or not d.virtual or not d.block or not cls:
            return body
        base = Canon.get(cls).block_class.get(d.block)
        K = base_offset(cls, base) if base else None
        if not K:
            return body
        cast = r"(?:\(\s*(?:char|uint8_t|unsigned\s+char)\s*\*\s*\)\s*this|reinterpret_cast\s*<\s*(?:char|uint8_t|unsigned\s+char)\s*\*\s*>\s*\(\s*this\s*\))"
        idiom = re.compile(r"\(\s*void\s*\*\s*\)\s*\(\s*\(\s*uint32_t\s*\)\s*\(\s*-\s*\(\s*\(\s*int\s*\)\s*\(\s*%s\s*-\s*%d\s*!=\s*0\s*\)\s*\)\s*\)\s*&\s*\(\s*uint32_t\s*\)\s*this\s*\)" % (cast, K))
        body, n1 = idiom.subn("\x06BASE\x06", body)
        body, n2 = re.subn(r"%s\s*-\s*%d\b" % (cast, K), "\x06THIS\x06", body)
        # what is left of `this` as a value (not `this->member`) is the subobject pointer
        body, n3 = re.subn(r"(?<![\w.>\x06])this\b(?!\s*(?:->|\.))", "\x06BASE\x06", body)
        body = body.replace("\x06THIS\x06", "this").replace("\x06BASE\x06", "static_cast<%s *>(this)" % base)
        if n1 or n2 or n3:
            self.used.add(base)
            self.stats["secondary_this_rewritten"] += n1 + n2 + n3
            notes.append("virtual of the secondary base %s (+0x%x): `(char*)this - %d` x%d -> this, subobject `this` x%d -> static_cast" % (
                base, K, K, n2, n1 + n3))
        return body

    def pointer_locals(self, c, body, env):
        """`uint32_t old = mpManager;` where the canonical member is a pointer: the local is that pointer type."""
        m = mask(body)
        for mm in re.finditer(r"(?:^|[;{}])\s*(uint32_t|int|unsigned)\s+(\w+)\s*=\s*(\w+)\s*;", m):
            t, v, rhs = mm.groups()
            hit = self.this_member_path(c.cls, [("name", rhs)])
            if hit and hit[3] and hit[3].rstrip().endswith("*") and self.cls_of(hit[3]):
                self.retype[v] = (t, hit[3].strip())
                env[v] = hit[3].strip()

    # -- thunks
    THUNK = re.compile(r"\(\(\s*(\w+)\s*\)\s*\(\s*\*\s*\(\s*void\s*\*\s*\*\s*\*\s*\)\s*([^()]+?)\s*\)\s*\[\s*(0x[0-9a-fA-F]+|\d+)\s*/\s*4\s*\]\s*\)\s*\(")

    def cls_of(self, text):
        t = norm_type(text or "")
        t = t.rstrip("*& ").strip()
        if t not in self.data.types.structs:
            t = re.sub(r",\s+", ",", t)             # the demangler prints `basic_string<char, eastl::allocator>`, the PDB `<char,eastl::allocator>`
        return t if t in self.data.types.structs else None

    def expr_canon(self, expr, c, env):
        """canonical class of a simple expression ('this', 'idx', '&mFile', 'mpMemoryLocation.p', 'mgr')."""
        e = expr.strip()
        if e.startswith("&"):
            e = e[1:].strip()
        if e == "this":
            return self.fn_class.get(c.va)
        toks = re.findall(r"[A-Za-z_]\w*", e)
        if not toks:
            return None
        cur_s = cur_c = None
        rest = toks
        if toks[0] in env:
            cur_s = base_type(env[toks[0]])[0]
            cur_c = self.class_map.get(cur_s)
            if cur_c is None and c.decl is not None:        # a parameter the slice typed as an integer
                for i, p in enumerate(c.params):
                    if self.pname(p, i) == toks[0] and i < len(c.decl.params):
                        cur_c = self.cls_of(c.decl.params[i])
            rest = toks[1:]
        else:
            cur_s, cur_c = c.cls, self.fn_class.get(c.va)
        i = 0
        while i < len(rest):
            hit = self.this_member_path(cur_s, [("name", t) for t in rest[i:]]) if cur_s else None
            if hit:
                used, _cp, stype, ctype = hit
                i += used
                cur_s = base_type(stype)[0] if stype else None
                cur_c = self.cls_of(ctype)
            else:
                m = Canon.get(cur_c).member(rest[i]) if cur_c else None
                cur_s = None
                cur_c = self.cls_of(m["type"]) if m else None
                i += 1
        return cur_c

    def canon_of_expr_type(self, sname):
        if sname in self.class_map:
            return self.class_map[sname]
        return None

    DELETE = re.compile(r"\(\(\s*TF1\s*\)\s*\(\s*\*\s*\(\s*void\s*\*\s*\*\s*\*\s*\)\s*(\w+)\s*\)\s*\[\s*0\s*\]\s*\)\s*\(\s*\1\s*,\s*1\s*\)")

    LOCAL_TF = re.compile(r"[ \t]*typedef\s+([\w\s\*]+?)\s*\(\s*__thiscall\s*\*\s*(\w+)\s*\)\s*\([^;]*\)\s*;[ \t]*\n?")

    def convert_thunks(self, c, body, env, notes):
        # slot 0 called with flag 1 is the scalar deleting destructor: delete p
        body = self.DELETE.sub(lambda mm: "delete %s" % mm.group(1), body)
        # the slice spells the function-pointer type either with a preamble typedef (TFb1, TFc2, ...) or with a typedef
        # inside the function (`typedef void (__thiscall *Fn)(DatabasePackedFile*);`): name -> return type
        local_tf = {mm.group(2): mm.group(1).strip() for mm in self.LOCAL_TF.finditer(mask(body))}
        skip_from = 0
        while True:
            m = mask(body)
            mm = self.THUNK.search(m, skip_from)
            if mm and not (mm.group(1).startswith("TF") or mm.group(1) in local_tf):
                skip_from = mm.end()          # some other cast of a vtable slot
                continue
            if not mm:
                # the local typedefs nothing uses any more go
                for nm in local_tf:
                    ndef = len([t for t in self.LOCAL_TF.finditer(mask(body)) if t.group(2) == nm])
                    if len(re.findall(r"(?<![\w.])%s\b" % re.escape(nm), mask(body))) == ndef:
                        body = self.LOCAL_TF.sub(lambda t: "" if t.group(2) == nm else t.group(0), body)
                return body
            ob = mm.end() - 1
            cb = match_close(m, ob)
            args = split_top(body[ob + 1:cb], m[ob + 1:cb])
            recv = mm.group(2).strip()
            slot = int(mm.group(3), 0) // 4
            canon = self.expr_canon(recv, c, env)
            decl = Canon.get(canon).slots.get(slot) if canon else None
            if canon:
                self.used.add(canon)
            if decl is None:
                self.stats["thunks_left"] += 1
                notes.append("thunk slot %d on %s (%s) left: no canonical slot" % (slot, recv, canon))
                body = body[:mm.start()] + "\x02THUNK" + body[mm.start() + 1:]
                continue
            # first argument is the receiver (maybe cast)
            a0 = re.sub(r"^\(\s*(void\s*\*|int|uint32_t)\s*\)\s*", "", args[0]).strip() if args else ""
            if args and a0.replace(" ", "") != recv.replace(" ", ""):
                notes.append("thunk receiver %r differs from the first argument %r (adjusted this?); left" % (recv, args[0]))
                body = body[:mm.start()] + "\x02THUNK" + body[mm.start() + 1:]
                continue
            rest = args[1:]
            if len(rest) != len(decl.params):
                notes.append("thunk slot %d (%s): %d args but %s takes %d; left" % (slot, decl.name, len(rest), decl.sig(), len(decl.params)))
                body = body[:mm.start()] + "\x02THUNK" + body[mm.start() + 1:]
                continue
            conv = []
            for a, pt in zip(rest, decl.params):
                conv.append(self.fix_arg(a, pt, c, env))
            if recv == "this":
                call = "\x01%s(%s)" % (decl.name, ", ".join(conv))
            else:
                r = recv
                if r.startswith("&"):
                    r = "(%s)" % r
                call = "%s->\x01%s(%s)" % (r, decl.name, ", ".join(conv))
            # the slice's typedef returns char, which converts to bool with `test al,al / setne al`; a plain
            # `return Call();` of a bool would be a tail call, `Call() ? true : false` compiles to the slice's code
            # (measured on ReadHeaders 0x8d8320: also tried (char), != 0, !!, != false: all different)
            if (mm.group(1).startswith("TFc") or local_tf.get(mm.group(1)) == "char") and decl.ret.strip() == "bool" and \
                    re.search(r"\breturn\s*$", body[:mm.start()]) and re.match(r"\s*;", body[cb + 1:]):
                call = call + " ? true : false"
            pre = body[:mm.start()]
            cm = re.search(r"\(\s*(\w+)\s*\*\s*\)\s*$", pre)
            if cm and self.class_map.get(cm.group(1)) and self.class_map[cm.group(1)] == self.cls_of(decl.ret) and \
                    decl.ret.rstrip().endswith("*"):
                pre = pre[:cm.start()]            # (Index*)CreateIndex(3): the call already returns a PFIndex *
            body = pre + call + body[cb + 1:]
            self.stats["thunks_converted"] += 1
            # the call was wrapped in parens ((TF)(...)[..])(args): consumed up to cb; the outer paren pair of
            # the slice's spelling is the cast expression itself, nothing else to strip
        return body.replace("\x02THUNK", "((")

    def var_ctype(self, name, c, env):
        """type text of a variable as the canonical code sees it: a parameter takes the canonical declaration's type."""
        if c.decl is not None:
            for i, p in enumerate(c.params):
                if self.pname(p, i) == name and i < len(c.decl.params):
                    return c.decl.params[i]
        return env.get(name)

    def fix_arg(self, a, ptype, c, env, ctor=False):
        """Argument of a converted call: the slice passes pointers as (int) and out-parameters as &x; the canonical
        parameters have real types (pointer, reference, enum)."""
        a = a.strip()
        k = self.kind_of(ptype)
        pt_base = ptype.replace("const", "").replace("&", "").replace("*", "").strip()
        m = re.match(r"^\(\s*(int|uint32_t|unsigned|void\s*\*)\s*\)\s*(.+)$", a)
        inner = m.group(2).strip() if m else a
        om = re.match(r"^&\s*(\w+)$", inner)
        if k == "ptr" and om and ptype.rstrip().endswith("**") and "const" in ptype:
            # out-parameter of pointer type whose canonical pointee is const (`Variant const **` of the const GetProperty):
            # the slice's non-const `Property* p;` local takes the canonical pointee type
            v = om.group(1)
            lt = env.get(v)
            want = ptype.rstrip()[:-1].rstrip()
            if lt and lt.rstrip().endswith("*") and "const" not in lt:
                lb = norm_type(lt).rstrip("* ").strip()      # as spelled (convert_types renames only unqualified slice names)
                old = lt.replace(lb, self.qualify(self.class_map[lb], "EA::ResourceMan"), 1) if lb in self.class_map else lt
                self.retype[v] = (old.replace(" *", "*"), want)
            return "&" + v
        if k == "ref" and re.match(r"^&\s*\w+(?:(?:\.|->)\w+|\[[^\]]*\])+$", inner):     # &it->second -> it->second (lvalue chain)
            return inner[1:].strip()
        if k == "ref" and re.match(r"^&\s*\w+$", inner):          # out-parameter: &len -> len
            v = inner[1:].strip()
            lt = env.get(v)
            want = ptype.rstrip("& ").strip()
            if lt and norm_type(lt) != norm_type(want):
                self.retype[v] = (lt, want)
            return v
        if re.fullmatch(r"-?\d+|0x[0-9a-fA-F]+", inner) and pt_base not in SCALARS and \
                (pt_base in self.data.types.enums or "PositionType" in pt_base):
            return "(%s)%s" % (ptype, inner)
        if not m:
            if k == "ptr" and re.match(r"^\w+$", inner):
                vt = self.var_ctype(inner, c, env)
                # (a void * argument needs the cast whatever is called: void * does not convert to a typed pointer)
                if vt and self.kind_of(vt) == "ptr" and norm_type(vt) != norm_type(ptype) and \
                        (ctor or (base_type(vt)[0] == "void" and base_type(ptype)[0] != "void")):
                    return "(%s)%s" % (ptype, inner)
            return a
        if k in ("ptr", "ref"):
            if re.match(r"^[A-Za-z_]\w*$", inner):
                vt = self.var_ctype(inner, c, env)
                if vt and (("[" in vt) or norm_type(vt) in ("char", "char *", "void *", "unsigned char *", "uint8_t *")) and \
                        norm_type(vt) != norm_type(ptype):
                    return "(%s)%s" % (ptype.replace("&", "*") if k == "ref" else ptype, inner)
            return inner
        return inner

    # -- allocation idiom
    ALLOC = re.compile(r"(?P<ind>[ \t]*)(?P<T>\w+)\s*\*\s*(?P<v>\w+)\s*=\s*\(\s*(?P=T)\s*\*\s*\)\s*ICoreAllocator_Alloc_Named\s*\(\s*"
                       r"(?P<size>0x[0-9a-fA-F]+|\d+)\s*,\s*(?P<alloc>[^,]+?)\s*,\s*(?P<name>\"[^\"]*\")\s*\)\s*;\s*\n"
                       r"\s*if\s*\(\s*(?P=v)\s*\)\s*\n?\s*return\s+(?P=v)\s*->\s*(?P<init>\w+)\s*\((?P<args>[^;]*)\)\s*;")

    def convert_alloc(self, c, body, env, notes):
        pos = 0
        while True:
            mm = self.ALLOC.search(body, pos)
            if not mm:
                return body
            T = mm.group("T")
            canon = self.class_map.get(T)
            if not canon:
                notes.append("allocation of %s: class not mapped; left" % T)
                pos = mm.end()
                continue
            args = split_top(mm.group("args"))
            ctors = [d for d in canon_methods(canon) if d.ctor and len(d.params) == len(args)
                     and d.name == canon.split("::")[-1]]
            conv = []
            for k, a in enumerate(args):
                a = a.strip()
                ptypes = {d.params[k] for d in ctors}
                if len(ptypes) == 1:
                    pt = next(iter(ptypes))
                    a = self.fix_arg(a, pt, c, env, ctor=True)
                conv.append(a)
            if not ctors:
                notes.append("no %d-argument constructor in %s" % (len(args), canon))
            self.used.add(canon)
            end = mm.end()
            m2 = re.match(r"\s*\n([ \t]*)return\s+0\s*;", body[end:])
            if m2 and m2.group(1) == mm.group("ind"):
                end += m2.end()
            new = "%sreturn new (%s, %s) %s(%s);" % (mm.group("ind"), mm.group("alloc").strip(), mm.group("name"), T, ", ".join(conv))
            body = body[:mm.start()] + new + body[end:]
            self.stats["allocations_converted"] += 1
            pos = mm.start() + len(new)

    def drop_vptr_stores(self, c, body, env, notes):
        """`Refpack rp; ... rp.vt = vtbl_Refpack;`: the canonical class sets its own vptr in the (inline) constructor,
        which runs where the slice stored the vptr, so the declaration moves to the store."""
        out = body
        for mm in list(re.finditer(r"[ \t]*\b(\w+)\.vt\s*=\s*\w+\s*;[ \t]*\n", body)):
            v = mm.group(1)
            t = base_type(env.get(v, ""))[0]
            st = self.structs.get(t)
            if not (st and t in self.class_map and any(m["name"] == "vt" for m in st.members)):
                continue
            dm = re.search(r"([ \t]*)%s\s+%s\s*;[ \t]*\n" % (re.escape(t), re.escape(v)), out)
            ind = re.match(r"[ \t]*", mm.group(0)).group(0)
            out = out.replace(mm.group(0), "%s%s %s;\n" % (ind, t, v), 1)
            if dm:
                out = out.replace(dm.group(0), "", 1)
            notes.append("%s %s: declaration moved to the vptr store (the canonical constructor sets the vptr)" % (t, v))
        return out

    # -- chains
    def convert_chains(self, c, body, env, ref_params, notes):
        m = mask(body)
        edits = []
        i = 0
        n = len(m)
        kw = {"if", "while", "for", "return", "switch", "sizeof", "else", "goto", "case", "new", "delete", "true", "false",
              "bool", "int", "char", "void", "unsigned", "short", "long", "float", "double", "const", "this"}
        main_cls = self.fn_class.get(c.va)
        while i < n:
            mm = re.compile(r"[A-Za-z_]\w*").search(m, i)
            if not mm:
                break
            s0 = mm.start()
            prev = m[max(0, s0 - 2):s0]
            if prev.endswith(".") or prev.endswith("->") or prev.endswith("::") or (s0 > 0 and m[s0 - 1] == "\x01"):
                i = mm.end()
                continue
            name = mm.group(0)
            if name in kw and name != "this":
                i = mm.end()
                continue
            # elements
            j = mm.end()
            elems = []
            call_open = None
            while True:
                k = j
                while k < n and m[k] in " \t":
                    k += 1
                if m.startswith("->", k) or m[k:k + 1] == ".":
                    op = "->" if m.startswith("->", k) else "."
                    k += len(op)
                    while k < n and m[k] in " \t":
                        k += 1
                    mi = re.compile(r"\x01?[A-Za-z_]\w*").match(m, k)
                    if not mi:
                        break
                    elems.append(("name", body[mi.start():mi.end()], op))
                    j = mi.end()
                elif m[k:k + 1] == "[":
                    e = match_close(m, k)
                    # the index expression can name members too (`mapBucketArray[mapBucketCount]`): rewrite it by the same rules
                    elems.append(("idx", self.convert_chains(c, body[k + 1:e], env, ref_params, notes).strip(), ""))
                    j = e + 1
                elif m[k:k + 1] == "(":
                    call_open = k
                    break
                else:
                    break
            end = j
            # decide the start object
            start_struct = None
            first_is_member = False
            repl_first = None
            if name == "this":
                start_struct = main_cls and c.cls
                cmain = c.cls
                if elems and elems[0][0] == "name":
                    start_struct = c.cls
                    first_is_member = False
                    # this->member...: treat as implicit-this chain without the 'this->' prefix
                    new, endstruct = self.resolve_chain(c.cls, elems)
                    repl = "this" + self.chain_text(new)
                    edits.append((s0, end, repl, endstruct, call_open, elems))
                i = end
                continue
            if name in env:
                start_struct = base_type(env[name])[0]
                if name in ref_params and elems and elems[0][2] == "->":
                    elems[0] = (elems[0][0], elems[0][1], ".")
                new, endstruct = self.resolve_chain(start_struct, elems) if start_struct in self.members_map or elems else ([], None)
                if start_struct not in self.members_map:
                    new, endstruct = [(e[2], e[1], e[0]) for e in elems], None
                    endstruct = None
                edits.append((s0, end, name + self.chain_text(new), endstruct, call_open, [("name", name, "")] + elems))
                i = end
                continue
            # implicit this: a member of the slice class
            t0 = self.type_of_chain_member(c.cls, name) if c.cls in self.views else None
            if t0 is not None:
                allel = [("name", name, "")] + elems
                new, endstruct = self.resolve_chain(c.cls, allel)
                txt = self.chain_text(new)
                if txt.startswith("."):
                    txt = txt[1:]
                if txt.startswith("->"):
                    txt = txt[2:]
                edits.append((s0, end, txt, endstruct, call_open, allel))
                i = end
                continue
            # bare call of a method of this class (not a member): Foo(...)
            if call_open is not None and not elems and self.slice_method(c.cls, name) is not None:
                d = self.slice_method(c.cls, name)
                self.call_decls.append(d)
                edits.append((s0, end, "\x04%d\x04%s" % (len(self.call_decls) - 1, d.name), None, call_open, []))
            i = max(end, mm.end())
        # method renames at the end of chains
        out = body
        for (s0, end, txt, endstruct, call_open, elems) in sorted(edits, key=lambda x: -x[0]):
            if txt != out[s0:end]:
                self.stats["member_chains_rewritten"] += 1
            # a call at the end of the chain: rename the last element if it is a method of the end object
            new_txt = txt
            if call_open is not None and elems and elems[-1][0] == "name":
                last = elems[-1][1]
                recv_struct = self.chain_receiver_struct(c, elems, env)
                if last.startswith("\x01"):
                    pass
                elif recv_struct and self.slice_method(recv_struct, last) is not None:
                    d = self.slice_method(recv_struct, last)
                    self.call_decls.append(d)
                    if d.name != last:
                        self.stats["method_renames"] += 1
                    new_txt = re.sub(r"%s$" % re.escape(last), "\x04%d\x04%s" % (len(self.call_decls) - 1, d.name), txt)
                elif recv_struct and recv_struct in self.class_map and last in [x.name for x in canon_methods(self.class_map[recv_struct])]:
                    pass
                elif recv_struct and recv_struct in self.structs:
                    notes.append("method %s::%s has no canonical name; left" % (recv_struct, last))
            out = out[:s0] + new_txt + out[end:]
        # bare dereferences of reference parameters: *key -> key
        for pn in ref_params:
            out = re.sub(r"\*\s*%s\b" % re.escape(pn), pn, out)
        # qualified calls of a base class method (`cPropertyList::GetPropertyA(key, out)` from the derived slice class)
        mo = mask(out)
        for mm in reversed(list(re.finditer(r"(?<![\w:.>])([A-Za-z_]\w*)\s*::\s*([A-Za-z_]\w*)\s*\(", mo))):
            sname, meth = mm.group(1), mm.group(2)
            if sname in self.structs and sname in self.class_map:
                d = self.slice_method(sname, meth)
                if d is not None:
                    self.call_decls.append(d)
                    if d.name != meth:
                        self.stats["method_renames"] += 1
                    out = out[:mm.start(2)] + "\x04%d\x04%s" % (len(self.call_decls) - 1, d.name) + out[mm.end(2):]
        # arguments of the calls renamed above: canonical parameter types (references, enums)
        while True:
            m = mask(out)
            hits = list(re.finditer(r"\x04(\d+)\x04(\w+)\s*\(", m))
            if not hits:
                break
            mm = hits[-1]
            d = self.call_decls[int(mm.group(1))]
            ob = mm.end() - 1
            cb = match_close(m, ob)
            args = split_top(out[ob + 1:cb], m[ob + 1:cb]) if out[ob + 1:cb].strip() else []
            if len(args) == len(d.params):
                args = [self.fix_arg(a, pt, c, env) for a, pt in zip(args, d.params)]
            call = mm.group(2) + "(" + ", ".join(args) + ")"
            # the slice's method returns a pointer where the canonical one returns a reference (`Variant* GetPropertyValue(key)` is
            # slot 10 `Variant const & GetProperty(key) const`): the address of the result, cast to the slice's pointer type
            sr = getattr(d, "slice_ret", None)
            if sr and sr.rstrip().endswith("*") and d.ret.rstrip().endswith("&") and mm.start() > 0:
                pointee = d.ret.rstrip()[:-1].replace("const", " ").strip()
                self.stats["ref_returns_to_pointer"] += 1
                # the receiver chain in front of the method name (`mParent.mpObject->`, `Base::`) belongs to the call
                st = mm.start()
                while st > 0:
                    mt = re.search(r"(?:[\w]+(?:\s*\[[^\]]*\])*\s*(?:\.|->|::)\s*)$", out[:st])
                    if not mt:
                        break
                    st = mt.start()
                out = out[:st] + "((%s *)&%s%s)" % (pointee, out[st:mm.start()], call) + out[cb + 1:]
                continue
            out = out[:mm.start()] + call + out[cb + 1:]
        return out

    def slice_method(self, sname, name, depth=0):
        """canonical declaration the slice method `sname::name` maps to, looked up in the slice struct and then in its bases
        (the slice's cDirectPropertyList calls SetProperty/GetPropertyValue, which its base cPropertyList declares)."""
        d = self.method_map.get(sname, {}).get(name)
        if d is not None or depth > 6:
            return d
        st = self.structs.get(sname)
        for b in (st.bases if st else []):
            d = self.slice_method(b.split("::")[-1], name, depth + 1)
            if d is not None:
                return d
        return None

    def chain_receiver_struct(self, c, elems, env):
        """slice struct name of the object a method call at the end of the chain is made on."""
        # re-walk: start object is elems[0] (for env/implicit chains already folded in `elems`)
        names = [e for e in elems]
        if not names:
            return None
        first = names[0]
        if first[0] != "name":
            return None
        if first[1] in env:
            cur = base_type(env[first[1]])[0]
            rest = names[1:-1]
        else:
            cur = c.cls
            rest = names[:-1]
        # walk through the members using the slice paths
        i = 0
        while i < len(rest):
            hit = self.this_member_path(cur, [(e[0], e[1]) for e in rest[i:]])
            if hit:
                used, _cp, stype, _ct = hit
                i += used
                cur = base_type(stype)[0] if stype else None
            else:
                t = self.type_of_chain_member(cur, rest[i][1]) if rest[i][0] == "name" else None
                cur = base_type(t)[0] if t else None
                i += 1
            if cur is None:
                return None
        return cur

    @staticmethod
    def chain_text(new):
        out = ""
        for op, text, kind in new:
            if kind == "idx":
                out += "[%s]" % text
            elif kind == "path" and text.startswith("\x05"):
                _e, q, ty = text.split("\x05")
                out = "((%s *)&%s%s)" % (ty, (out + (op or ".")) if out else "", q)
            elif kind == "path" and text.startswith("\x07"):
                _e, q, ty = text.split("\x07")
                out = "(*(%s *)&%s%s)" % (ty, (out + (op or ".")) if out else "", q)
            elif kind == "path" and text.startswith("\x06"):
                _e, q, ty = text.split("\x06")
                out = "((%s)%s%s)" % (ty, (out + (op or ".")) if out else "", q)
            elif kind == "path" and text.startswith("\x03"):
                _e, q, idx, ty = text.split("\x03")
                out = "((%s *)&%s%s)[%s]" % (ty, (out + (op or ".")) if out else "", q, idx)
            elif kind == "path":
                out += (op or "") + text
            else:
                out += (op or ".") + text
        return out

    # -- types
    def qualify(self, canon, ns):
        """canonical class name as spelled inside namespace ns ('EA::ResourceMan')."""
        if ns and canon.startswith(ns + "::"):
            return canon[len(ns) + 2:]
        return canon

    def item_view(self, kind, text, fns):
        """A kept function declaration that only converted (non-verbatim) functions call is spelled with the canonical class
        names (`VariantPair*` -> `eastl::pair<unsigned int, EA::Variant>*`): the slice stub type it mentions is not what the
        converted bodies pass.  Declarations that verbatim functions use keep the slice's spelling and stub types."""
        conv_uses, verb_uses = set(), set()
        for c in fns:
            tgt = verb_uses if getattr(c, "verbatim", False) else conv_uses
            ctext = c.defline + "\n" + c.out_body
            tgt.update(RS.item_uses("other", ctext))
            for mm in re.finditer(r"[A-Za-z_]\w*(?:\s*::\s*~?[A-Za-z_]\w*)+", RS.mask(ctext)):     # qualified spellings too
                tgt.add(re.sub(r"\s+", "", mm.group(0)).split("::")[-1])
        nm = RS.item_names(kind, text)
        if kind in ("other", "extern") and nm and any(n in conv_uses for n in nm) and not any(n in verb_uses for n in nm) \
                and not RS.mask(RS.unwrap_namespaces(text)[1]).lstrip().startswith(("struct", "class", "union", "template")):
            return self.map_class_names(text)
        return text

    def map_class_names(self, text):
        names = {s: self.qualify(v, "EA::ResourceMan") for s, v in self.class_map.items() if s in self.structs}
        if not names:
            return text
        m = mask(text)
        pat = re.compile(r"(?<![\w.>:\x01])(%s)\b(?!\s*::)" % "|".join(re.escape(k) for k in sorted(names, key=len, reverse=True)))
        out, last = [], 0
        for mm in pat.finditer(m):
            # a namespace of the same name (`namespace Thread {` inside EA::Thread next to class Thread, mig12 s00922500)
            # is not the class: respelled, it became `namespace EA::Thread::Thread {` (C2061)
            if re.search(r"\bnamespace\s+$", m[:mm.start()]):
                continue
            out.append(text[last:mm.start()])
            out.append(names[mm.group(1)])
            last = mm.end()
        out.append(text[last:])
        return "".join(out)

    def convert_types(self, c, body):
        ns = "EA::ResourceMan"
        names = {s: self.qualify(v, ns) for s, v in self.class_map.items() if s != c.cls}
        if not names:
            return body
        m = mask(body)
        # a slice struct may be spelled with the namespace the slice declared it in (`eastl::basic_string8`, `EA::Variant`):
        # the whole qualified name is replaced, unless the qualifier is itself a class (a nested type)
        pat = re.compile(r"(?<![\w.>:\x01])((?:[A-Za-z_]\w*\s*::\s*)*)(%s)\b(?!\s*::)" % "|".join(re.escape(k) for k in sorted(names, key=len, reverse=True)))
        out, last = [], 0
        for mm in pat.finditer(m):
            q = re.sub(r"\s+", "", mm.group(1)).rstrip(":")
            if q and q in self.data.types.structs:
                continue
            out.append(body[last:mm.start()])
            out.append(names[mm.group(2)])
            last = mm.end()
        out.append(body[last:])
        return "".join(out)

    def convert_externs(self, c, body):
        for nm, e in self.externs.items():
            if e.get("call") and e["call"] != nm:
                body = re.sub(r"(?<![\w.:>])%s\b" % re.escape(nm), e["call"], body)
        return body


    # ---- 6. externs -------------------------------------------------------------------------------
    def collect_externs(self):
        self.externs = {}
        names_txt = {}
        for line in open(W("symbols", "names.txt"), encoding="utf-8", errors="replace"):
            parts = line.split("#", 1)[0].split()
            if len(parts) >= 2:
                try:
                    names_txt[int(parts[0], 16)] = parts[1]
                except ValueError:
                    pass
        for kind, text in self.items:
            if kind not in ("extern", "other"):
                continue
            code = text.split("//")[0]
            # the declared name: the first identifier followed by ( [ ; that is not a keyword or attribute
            # (`extern "C" __declspec(dllimport) BOOL __stdcall VerQueryValueA(...)` is VerQueryValueA, not __declspec:
            # report_s0091e650.md, every dllimport of the slice collapsed onto one key "__declspec")
            code = re.sub(r"__declspec\s*\([^()]*\)", " ", code)
            mm = next((x for x in re.finditer(r"(\w+)\s*(\(|\[|;)", code) if x.group(1) not in RS.KEYWORDS), None)
            if not mm:
                continue
            name = mm.group(1)
            va = None
            vm = re.search(r"//.*?0x([0-9a-fA-F]{6,8})", text)
            if vm:
                va = int(vm.group(1), 16)
            canon_call = None
            if kind == "other":
                # a prototype without `extern` (`IAlloc* GetDefaultAllocator();  // 0x925cb0`) is a callee when its retail
                # address is a static/free method of a canonical class: the header declares it, the call is qualified
                if va is None or not re.match(r"^[\w\s\*&:<>]+\b%s\s*\([^)]*\)\s*;\s*(//.*)?$" % re.escape(name), text.strip()):
                    continue
                nm = (self.pdb_names.get("%08x" % va) or {}).get("name")
                if not nm:
                    continue
                cls, meth = H.split_qual(nm)
                if meth != name or not Canon.get(cls).exists or not any(d.name == meth and d.static for d in Canon.get(cls).decls):
                    continue
                canon_call = nm
                self.used.add(cls)
            e = dict(text=text, va=va, call=name, decl=text)
            if canon_call:
                e.update(call=canon_call, decl=None, why="retail 0x%08x is %s (pdb_names), a static method of the canonical class" % (va, canon_call))
            if name in KNOWN_EXTERNS:
                e.update(KNOWN_EXTERNS[name])
                e["decl"] = KNOWN_EXTERNS[name].get("decl", text)
            if name in self.manual.get("externs", {}):
                e.update(self.manual["externs"][name])
            e["name_from"] = names_txt.get(va) if va else None
            self.externs[name] = e

    # ---- 7. definitions -----------------------------------------------------------------------------
    def qual_of(self, c):
        """qualifier of the function's canonical name: the class for a method, the namespace for a namespace function."""
        return c.decl.ns if c.free else self.fn_class[c.va]

    def free_definition_line(self, c):
        """`bool CopyDatabaseRecord(Database * src, ...)` inside `namespace EA { namespace ResourceMan {`: canonical
        parameter types with the slice's names (a1.. for parameters the slice did not declare)."""
        d = c.decl
        short = lambda t: t.replace(d.ns + "::", "")
        parts = []
        for i, cp in enumerate(d.params):
            nm = self.pname(c.params[i], i) if i < len(c.params) else "a%d" % (i + 1)
            m = re.match(r"^(.*?)(\s*\[[^\]]*\])$", cp)
            parts.append(named_param(short(cp), nm) if not m else "%s %s%s" % (short(m.group(1)), nm, m.group(2)))
        return "%s %s%s(%s)" % (short(d.ret), d.cc + " " if d.cc else "", d.name, ", ".join(parts))

    def definition_line(self, c):
        d = c.decl
        if c.free:
            return self.free_definition_line(c)
        cls = self.fn_class[c.va]
        ret = d.ret
        parts = []
        for i, cp in enumerate(d.params):
            if cp.strip() == "...":
                parts.append("...")             # the ellipsis of a variadic method takes no name
                continue
            nm = self.pname(c.params[i], i) if i < len(c.params) else "a%d" % (i + 1)     # a1.. for parameters an incomplete slice stub did not declare
            m = re.match(r"^(.*?)(\s*\[[^\]]*\])$", cp)
            parts.append(named_param(cp, nm) if not m else "%s %s%s" % (m.group(1), nm, m.group(2)))
        return "%s%s::%s(%s)%s" % (ret + " " if ret else "", cls, d.name, ", ".join(parts), " const" if d.const else "")

    def collect_includes(self):
        incs = ["game/types.h"]
        seen = set()
        for c in self.chunks:
            cls = self.fn_class.get(c.va)
            if cls and cls not in seen and Canon.get(cls).exists:
                seen.add(cls)
                incs.append(H.include_path(cls))
            if c.free and c.decl is not None and c in getattr(self, "fns", []):
                # classes named by a namespace function's signature: complete types when a header exists
                for t in [c.decl.ret] + c.decl.params:
                    for q in re.findall(r"[A-Za-z_]\w*(?:::\w+)+", t):
                        if q not in seen and Canon.get(q).exists:
                            seen.add(q)
                            incs.append(H.include_path(q))
        for sname, canon in sorted(self.class_map.items()):
            if canon in seen or not Canon.get(canon).exists:
                continue
            seen.add(canon)
            incs.append(H.include_path(canon))
        for canon in sorted(self.used):
            if canon not in seen and Canon.get(canon).exists:
                seen.add(canon)
                incs.append(H.include_path(canon))
        # canonical classes a converted body names (a local `cSPUILayout* lay = ...; lay->Shutdown(1);` in
        # SP::cSPUIFeedEdit::Shutdown, s0065bf20): complete types.  The headers forward-declare the pointees of smart-pointer
        # members since fix pass 3 (include cycles), so the TU can no longer count on getting them transitively.
        for c in getattr(self, "fns", []):
            if getattr(c, "verbatim", False) or not getattr(c, "out_body", None):
                continue
            for q in sorted(set(re.findall(r"(?<![\w:])([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)", RS.mask(c.out_body)))):
                if q in seen or ("::" not in q and q not in H.KNOWN_STRUCTS) or q.split("::")[0] in ("eastl", "std"):
                    continue
                if Canon.get(q).exists:
                    seen.add(q)
                    incs.append(H.include_path(q))
        return incs

    def build(self, module_filter):
        self.canon_hdrs = []
        self.ctor_calls = []
        self.collect_externs()
        self.map_methods()
        self.implicit_member_chunks()
        self.fns = []
        for c in sorted(self.chunks, key=lambda x: x.va):
            if module_filter and (not c.module or not mod_match(module_filter, c.module)):
                self.notes.append(("skipped", "0x%08x %s::%s belongs to %s" % (c.va, c.cls, c.name, c.module)))
                continue
            if "%08x" % c.va in self.manual.get("exclude", {}):
                # manual `exclude` {va: why}: modmap puts the function in this module on evidence the slice contradicts
                # (a wrong xmatch anchor name); it stays in the slice
                self.notes.append(("skipped", "0x%08x %s::%s stays in the slice: manual exclude: %s" % (
                    c.va, c.cls, c.name, self.manual["exclude"]["%08x" % c.va])))
                continue
            asm = asm_audit.why(c.text)
            if asm:
                # docs/matching.md "No assembly transcription" (2026-10-18: round 7 landed 37 naked functions of
                # s007a41c0/s007a51d0 into SPGraphicsSystem.cpp): a transcribed body is not decompiled C++ and stays
                # in the slice as a partial row
                self.notes.append(("skipped", "0x%08x %s stays in the slice: asm transcription (%s)" % (c.va, c.name, asm)))
                continue
            if str(c.how).startswith("address contradiction"):
                self.notes.append(("skipped", "0x%08x %s::%s stays in the slice: %s" % (c.va, c.cls, c.name, c.how)))
                continue
            if c.cls in getattr(self, "refused", {}) and "%08x" % c.va in self.slice_exact_vas() and \
                    "%08x" % c.va not in self.manual.get("leave_in_slice", {}) and \
                    (not getattr(self, "batch_vas", None) or "%08x" % c.va in self.batch_vas[1]):
                # fix pass 5 (s0057ae10 0x57ae10, s00585330, s00585d40: the slices' cAppModeEditorBase views put same-named
                # members 0x14..0x5a from SP::cAppModeEditorBase): a function that is BYTE-EXACT in the slice lands verbatim
                # with the slice's own (renamed) stub; the checked apply verifies the bytes and drops it on a DIFF, so the
                # s006bc1b0 hazard below (a verbatim copy whose library members change size) cannot pass unseen
                self.make_verbatim(c)
                self.notes.append(("verbatim", "0x%08x %s::%s: slice layout refused for mapping, byte-exact in the slice: %s" % (
                    c.va, c.cls, c.name, self.refused[c.cls])))
                self.fns.append(c)
                continue
            if c.cls in getattr(self, "refused", {}) and not self.stub_has_library_members(c.cls) and \
                    "%08x" % c.va not in self.manual.get("leave_in_slice", {}) and \
                    (not getattr(self, "batch_vas", None) or "%08x" % c.va in self.batch_vas[1]):
                # fix pass 6 D (2026-10-19): the s006bc1b0 hazard below needs by-value members of canonical library classes in
                # the slice's stub; a stub of scalars, pointers and slice-local types keeps its own layout in the module TU, so the
                # non-exact function lands verbatim like the byte-exact ones (the landing agent's equiv check is the gate).
                # mig8/mig9: DatabasePackedFile_v2 22, SPEditorPaintTheme 14, SPPlayMode 9 functions were held by the guard
                self.make_verbatim(c)
                self.notes.append(("verbatim", "0x%08x %s::%s: slice layout refused for mapping, stub has no library members: %s" % (
                    c.va, c.cls, c.name, self.refused[c.cls])))
                self.fns.append(c)
                continue
            if c.cls in getattr(self, "refused", {}):
                # a class whose slice layout is not the canonical class's: a verbatim copy would need the slice's stub
                # of that class, whose library members (FileStream 0x434, Mutex) the canonical headers replace by their
                # own sizes, so every offset behind them moves (measured on s006bc1b0: 0x6bc310 PASS -> FAIL, 0x6bcea0
                # WEAK -> FAIL, the exact ones DIFF); the function stays in the slice
                self.notes.append(("skipped", "0x%08x %s::%s stays in the slice: %s" % (c.va, c.cls, c.name, self.refused[c.cls])))
                continue
            bv = getattr(self, "batch_vas", None)
            if bv and "%08x" % c.va not in bv[1] and "%08x" % c.va not in self.manual.get("leave_in_slice", {}):
                self.notes.append(("skipped", "0x%08x %s: not in batch %s's list for this slice and module: stays in the slice" % (
                    c.va, c.name, bv[0])))
                continue
            keep = self.manual.get("leave_in_slice", {})
            if "%08x" % c.va in keep:
                # manual "leave_in_slice" {"006a30c0": why}: the function stays in the slice (a verdict the migrated spelling
                # worsens, or a function that cannot be written with the canonical classes yet)
                self.notes.append(("skipped", "0x%08x %s: left in the slice by the renames file: %s" % (c.va, c.name, keep["%08x" % c.va])))
                continue
            if c.decl is None:
                # no canonical declaration: the function keeps the slice's text and its local stub types (rule
                # "verbatim": never lose a function because the canonical class cannot be found)
                self.make_verbatim(c)
                self.notes.append(("verbatim", "0x%08x %s: %s" % (c.va, (c.cls + "::" if c.cls else "") + str(c.name), c.how)))
                self.fns.append(c)
                continue
            self.rewrite_body(c)
            c.defline = self.definition_line(c)
            lost = self.conversion_loses_behaviour(c)
            if lost:
                self.make_verbatim(c)
                self.notes.append(("verbatim", "0x%08x %s: conversion refused: %s" % (c.va, c.name, lost)))
            self.fns.append(c)

    @staticmethod
    def _special_kind(text):
        """'dtor' / 'ctor' when a definition line defines a destructor / constructor (`X::~X(`, `X::X(`), else None."""
        m = re.search(r"(?<!\w)(\w+)\s*::\s*(~?)\s*(\w+)\s*\(", mask(re.sub(r"(?m)//.*$", "", text or "")))
        if not m or m.group(1) != m.group(3):
            return None
        return "dtor" if m.group(2) else "ctor"

    @staticmethod
    def _statements(body):
        """The body without comments, braces and whitespace ('' for `{}`)."""
        s = re.sub(r"(?s)/\*.*?\*/", "", body or "")
        s = re.sub(r"(?m)//.*$", "", s)
        return re.sub(r"[\s{};]", "", s)

    def conversion_loses_behaviour(self, c):
        """Why a converted function must stay verbatim, or None (fix pass 6, mig7 report 23: s006068c0 0x606f30, the
        slice's `cAuthMessage::~cAuthMessage() {}`, whose meaning is the compiler-generated scalar deleting destructor
        (`delete this`), became the empty `cSPPaletteItemUIOneClickPaint::slot_22() {}`; equiv said FAIL before and after,
        so only a structural check catches it)."""
        if getattr(c, "implicit", None):
            return None
        sig = re.sub(r"(?m)^\s*//.*$", "", c.sig_text or "")
        sig = sig.rsplit(";", 1)[-1] if ";" in mask(sig) else sig      # the definition, not the stub struct in front of it
        was, now = self._special_kind(sig), self._special_kind(c.defline)
        # a plain function becoming a ctor/dtor (report 05: cSPPlayMode_ctor -> the dev ctor) is a mapping equiv judges;
        # losing a ctor/dtor, or swapping one for the other, changes what the compiler generates around the body
        if was and was != now:
            return "the slice defines a %s, the canonical declaration a %s" % (was or "plain function", now or "plain function")
        if self._statements(c.body) and not self._statements(c.out_body):
            return "the converted body is empty but the slice's is not"
        return None

    def slice_exact_vas(self):
        """VAs of the slice's manifest.txt rows (byte-exact in the slice)."""
        if not hasattr(self, "_slice_exact"):
            self._slice_exact = set()
            mp = os.path.join(SLICES, self.sid, "manifest.txt")
            if os.path.exists(mp):
                for line in open(mp):
                    p = line.split("#", 1)[0].split()
                    if len(p) >= 3 and re.fullmatch(r"(?:0x)?[0-9a-fA-F]{6,8}", p[2]):
                        self._slice_exact.add("%08x" % int(p[2], 16))
        return self._slice_exact

    IMPLICIT = {"copy constructor": "copy", "copy assignment": "assign", "destructor": "dtor", "scalar deleting destructor": "sdtor"}

    def implicit_member_chunks(self):
        """Compiler-generated special members the slice lists with a marker but cannot define (s00942290: `// @ 0x00942CE0
        Cookie40 copy constructor (implicit)`, copy assignment 0x942d70, destructor 0x942630; manifest symbols
        ??0Cookie40@@QAE@ABU0@@Z / ??4Cookie40@@QAEAAU0@ABU0@@Z): the slice's other functions made the compiler emit them.  In the
        module TU a forcing function does the same whatever else the TU holds (round 2 landed them by hand inside an items
        block, which a re-run regenerates): `#pragma auto_inline(off)` + a function that copies / assigns / destroys an S (the
        s007ada40 DestroyDxtSurface idiom that keeps ??1DxtSurface out of line, byte-exact).  The row binds to the member's
        own decorated name (cls/name/params of the chunk), not to the forcing function."""
        syms = RS.slice_rows(self.sid)[1]
        mm = self.data.modmap["functions"]
        lines = self.src_text.split("\n")
        # an empty placeholder under the marker (`void F_0046a7c0() {}`) whose manifest row is a special member of a slice struct
        # (`??0M18real@@`, s00469bb0: the slice made the compiler emit it with its own forcing helper) is that member too
        # (fix pass 4: the placeholder was landed, DIFF 2 bytes, and the byte-exact row stayed behind)
        kinds = {"??0": "copy constructor", "??4": "copy assignment", "??1": "destructor"}
        for c in list(self.chunks):
            sym = syms.get(c.va, "")
            mk = re.match(r"^(\?\?[014])(\w+)@@", sym)
            if mk and mk.group(2) in self.structs and re.match(r"^F_[0-9a-fA-F]{6,8}$", str(c.name)) and \
                    re.sub(r"\s+", "", mask(c.body)) == "{}":
                self.chunks.remove(c)
                lines.append("// @ 0x%08x %s %s (implicit)" % (c.va, mk.group(2), kinds[mk.group(1)]))
        have = {c.va for c in self.chunks}
        # a bare marker whose NEXT line names the member in a comment (s004186c0: `// @ 0x00418960` + `// EditorResource scalar
        # deleting destructor (compiler-generated from the virtual dtor).`, `// @ 0x00418990` + `// EditorResource::~EditorResource
        # is implicit (...)`; round 5 hand-added their manifest rows, which the next apply prunes): read as the one-line form
        extra = []
        for i, line in enumerate(lines[:-1]):
            mb = re.match(r"^//\s*@\s*0x([0-9a-fA-F]+)\s*$", line.strip())
            nxt = lines[i + 1].strip()
            if not mb or not nxt.startswith("//"):
                continue
            ms = re.match(r"^//\s*(\w+)\s+scalar deleting destructor\b.*(?:compiler-generated|implicit)", nxt)
            md = re.match(r"^//\s*(\w+)::~(\w+)\s+is implicit\b", nxt)
            if ms:
                extra.append("// @ 0x%s %s scalar deleting destructor (implicit)" % (mb.group(1), ms.group(1)))
            elif md and md.group(1) == md.group(2):
                extra.append("// @ 0x%s %s destructor (implicit)" % (mb.group(1), md.group(1)))
        lines = lines + extra
        for line in lines:
            m = re.match(r"^//\s*@\s*0x([0-9a-fA-F]+)\s+(\w+)\s+(copy constructor|copy assignment|scalar deleting destructor|destructor)\s*\(implicit", line.strip())
            if not m:
                continue
            va, S, what = int(m.group(1), 16), m.group(2), self.IMPLICIT[m.group(3)]
            sym = syms.get(va, "")
            if va in have or S not in self.structs:
                continue
            if sym and not sym.startswith({"copy": "??0%s@@" % S, "assign": "??4%s@@" % S, "dtor": "??1%s@@" % S,
                                           "sdtor": "??_G%s@@" % S}[what]):
                continue
            body = {"copy": "void rwForceEmit_%s_copy(const %s& s)\n{\n    %s c(s);\n}\n" % (S, S, S),
                    "assign": "void rwForceEmit_%s_assign(%s& d, const %s& s)\n{\n    d = s;\n}\n" % (S, S, S),
                    "dtor": "void rwForceEmit_%s_dtor(%s* p)\n{\n    p->~%s();\n}\n" % (S, S, S),
                    # the scalar deleting destructor is emitted with the class's vtable; `delete p` references it
                    "sdtor": "void rwForceEmit_%s_sdtor(%s* p)\n{\n    delete p;\n}\n" % (S, S)}[what]
            c = Chunk(va, body)
            c.lead = ["// %s %s (implicit): the forcing function below makes the compiler emit it out of line" % (S, m.group(3)),
                      "#pragma auto_inline(off)"]
            c.after = "#pragma auto_inline(on)"
            e = mm.get("%08x" % va) or {}
            c.module, c.dev_name, c.free_decl, c.free_why = e.get("module"), None, None, None
            c.decl, c.how = None, "implicit %s of the slice's %s (marker without a definition)" % (m.group(3), S)
            c.implicit = (S, {"copy": S, "assign": "operator=", "dtor": "~" + S, "sdtor": "~" + S}[what],
                          {"copy": 1, "assign": 1, "dtor": 0, "sdtor": 0}[what])
            self.chunks.append(c)
            self.notes.append(("implicit", "0x%08x %s %s: forcing function emitted" % (va, S, m.group(3))))

    def make_verbatim(self, c):
        """Chunk without a canonical declaration: signature and body exactly as in the slice."""
        c.verbatim = True
        c.free = False
        c.decl = None
        self.fn_class.pop(c.va, None)
        sig = re.sub(r"^\s*//.*$", "", c.sig_text, flags=re.M)
        sig = sig.rsplit(";", 1)[-1] if ";" in mask(sig) else sig
        c.defline = " ".join(sig.split())
        c.out_body = c.body
        c.notes = []
        # manual edits marked "verbatim": true apply to the slice text kept for a verbatim function (s00948de0 0x949620: the
        # global MIMEStringToMIMETypes(.., uint*, ..) is hidden by s00947d50's EA::Internet:: overload once the method is
        # defined with its namespace-qualified class; the call is spelled `::MIMEStringToMIMETypes`)
        for e in self.manual.get("edits", []):
            if e.get("verbatim") and int(e["va"], 16) == c.va and e["find"] in c.out_body:
                c.out_body = c.out_body.replace(e["find"], e["replace"], 1)
                self.stats["manual_edits_applied"] += 1
        if getattr(c, "implicit", None):
            c.cls, c.name, n = c.implicit           # the row binds to the special member, not to the forcing function
            c.params = ["x"] * n
        base = re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", c.cls or "")
        c.cls_ns = list(getattr(self.structs.get(base), "ns", []) or [])

    def qualify_function_after_using(self, c):
        """A verbatim function the slice defines after its global `using namespace N;` names N's stubs unqualified (s009b5ce0
        RayCastParts uses RC::Owner as `Owner`, fix pass 4): the directive is not emitted, so they get `N::`."""
        if getattr(c, "_qualified_using", False) or not getattr(c, "verbatim", False):
            return
        c._qualified_using = True
        for kind, text in self.items:
            mm = re.match(r"^\s*using\s+namespace\s+([\w:\s]+?)\s*;", RS.mask(text))
            if not mm or RS.unwrap_namespaces(text)[0]:
                continue
            n = re.sub(r"\s+", "", mm.group(1))
            ens = list(getattr(c, "enc_ns", []) or [])
            if ens and ens[0] == n.split("::")[0]:
                continue
            c.out_body = self.qualify_names(c.out_body, n)
            # the definition line: only the part before the qualified name (the return type); the class qualifier is
            # render_function's (a `SP::` here made `SP::X::X()` collide with it: C2084 / C2523 on s0059c4c0's ctor/dtor)
            dl = c.defline
            mq = re.search(r"(?<![\w:])([A-Za-z_]\w*)\s*::\s*~?\s*\w+\s*\(", dl)
            if mq:
                # ... and the parameter list after it (mig8 s007e6210 0x7e67a0 `bool cAppSystemEx::Init(CommandLine* cmd)`
                # after `using namespace AppInit;`: C2065 'CommandLine')
                c.defline = self.qualify_names(dl[:mq.start()], n) + dl[mq.start():mq.end()] + self.qualify_names(dl[mq.end():], n)
            else:
                c.defline = self.qualify_names(dl, n)

    def render_function(self, c):
        # manual "pragmas" {va: {"lead": [lines], "after": [lines], "why"}}: preprocessor lines around one function (s0083e1c0
        # 0x83e9d0: in the module TU the earlier-defined DiscardWhiteSpace 0x83ce90 is inlined into EvalSignedIntNumber, retail
        # and the slice (which only declared it) call it: `#pragma inline_depth(0)` for this function only)
        pm = self.manual.get("pragmas", {}).get("%08x" % c.va)
        if pm and not getattr(c, "_pragmas_done", False):
            c._pragmas_done = True
            c.lead = list(getattr(c, "lead", [])) + list(pm.get("lead", []))
            c.after = (c.after + "\n" if c.after else "") + "\n".join(pm.get("after", []))
        self.qualify_function_after_using(c)
        defline = c.defline
        wrap = []
        if getattr(c, "verbatim", False):
            # a verbatim function keeps the scope the slice defined it in: inside the slice's `namespace X {` (its stub classes
            # and its decorated name live there); a method of a namespaced stub defined at global scope (s00942290: `int
            # HTTPClient::ReadRawBody` after `using namespace EA::Internet;`, which the TU does not emit) gets the qualifier
            wrap = list(getattr(c, "enc_ns", []) or [])
            cns = getattr(c, "cls_ns", [])
            if cns and not wrap and c.cls:
                base = re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", c.cls)
                defline = re.sub(r"(?<![\w:])(%s(?:_s[0-9a-f]{4}_[0-9a-f]{4})?)\s*::" % re.escape(base),
                                 lambda mm: "::".join(cns + [mm.group(1)]) + "::", defline, count=1)
                # the return type in front of the qualified name is looked up at global scope: the namespace's stubs it names
                # get the qualifier too (fix pass 4, s0059c4c0 `cAnimatingCreature* cSPEditorAnimatedCreatureManager::GetCreature`
                # after `using namespace SP;`: C2143, and the 14 verbatim callers of GetCreature/GetCreatureStructure dropped)
                q = "::".join(cns) + "::"
                k = defline.find(q)
                if k > 0:
                    defline = self.qualify_names(defline[:k], "::".join(cns)) + defline[k:]
        out = ["// @ 0x%08x" % c.va] + list(getattr(c, "lead", [])) + [defline, c.out_body.rstrip()]
        if wrap:
            out.insert(1 + len(getattr(c, "lead", [])), " ".join("namespace %s {" % n for n in wrap))
        if c.free:
            parts = c.decl.ns.split("::")
            out.insert(1 + len(getattr(c, "lead", [])), "\n".join("namespace %s {" % n for n in parts))
        # text after the closing brace: the slice's next banner comment and, in slices that end with a block of
        # unmarked skeleton stubs ("remaining functions"), those stubs; neither belongs to this function
        after = []
        for l in c.after.split("\n"):
            if re.match(r"^\s*//\s*(-{5,}|={5,}|remaining functions)", l) or re.match(r"^\}", l):
                break                    # a banner, or the `}  // namespace SP` that closes the slice's own wrapper
            after.append(l)
        after = "\n".join(after).strip()
        if after and not all(l.strip().startswith("//") or not l.strip() for l in after.split("\n")):
            out.append(after)
        if c.free:
            out.append("\n".join("}" for _n in c.decl.ns.split("::")) + "  // namespace " + c.decl.ns)
        if wrap:
            out.append("".join("}" for _n in wrap) + "  // namespace " + "::".join(wrap))
        return "\n".join(out) + "\n"

    def render_preamble(self, fns):
        text = "\n".join(c.out_body for c in fns)
        lines = ["// %s -- migrated from slice(s) %s by tools/migrate/rewrite.py" % (self.tu_rel, self.sid),
                 "// Object file: %s.  Function bodies keep the slice's code; types, members and virtual calls use the" % self.module,
                 "// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.", ""]
        if any(re.match(r"^\s*typedef\s+[\w\s\*]+\bva_list\s*;", RS.mask(t)) for _k, t in self.items):
            # the slice's own `typedef char va_list;` (s00b1fd50 FormatAppend / VA_START) must win over <vadefs.h>, which any
            # system include (<new>) pulls in (C2040); round 4 hand-wrote this guard into SPGameNounManager.cpp (fix pass 4)
            lines.append(VA_GUARD)
        for inc in self.collect_includes():
            lines.append('#include "%s"' % inc)
        if re.search(r"\bNULL\b", text):
            # the slice's NULL came from its own includes (mig11 tgaread TGA_about/TGA_info: C2065 'NULL')
            lines += ["#ifndef NULL", "#define NULL 0", "#endif"]
        # classes a namespace function's signature names that have no generated header (only pointers/references to
        # them are needed): forward declarations
        fwd = set()
        for c in fns:
            if c.free:
                for t in [c.decl.ret] + c.decl.params:
                    # (?![\w<:]): `EA::COM::AutoRefCount<..>` backtracked to `EA::COM` and forward-declared the namespace as a
                    # class (C2365, then the stub rename broke every COM:: use; mig10 SPCookie s00609790, 7 functions)
                    for q in re.findall(r"[A-Za-z_]\w*(?:::\w+)+(?![\w<:])", t):
                        if not Canon.get(q).exists and q not in self.data.types.enums:
                            fwd.add(q)
        if fwd:
            lines.append("")
            for q in sorted(fwd):
                ns, _sep, nm = q.rpartition("::")
                lines.append("%s class %s; %s" % (" ".join("namespace %s {" % n for n in ns.split("::")), nm, " ".join("}" for _n in ns.split("::"))))
        ext = []
        ext_name = {}
        # the local stub types' own inline bodies use globals too (DBase's constructor stores `vtbl_AppDPF0`): an extern is
        # declared when the functions or the stubs the functions need mention it
        stub_text = "\n".join(self.render_local_items(fns, []))
        for nm, e in self.externs.items():
            if not re.search(r"(?<![\w.])%s\b" % re.escape(e["call"].split("::")[-1]), text + "\n" + stub_text):
                continue
            if e.get("decl"):
                if re.match(r"^(_Interlocked\w+|_ReadWriteBarrier|_BitScan\w+|__debugbreak|__cpuid|_mm_\w+)$", nm) and (
                        any(k2 == "include" and "intrin.h" in t2 for k2, t2 in self.items) or
                        (os.path.exists(W(*self.tu_rel.split("/"))) and "<intrin.h>" in open(W(*self.tu_rel.split("/"))).read())):
                    continue          # an intrinsic <intrin.h> declares (render_local_items)
                dtext = e["decl"]
                for ns_r, old_n, new_n in getattr(self, "renamed", []):
                    # the stub renames of this run reach the extern too (fix pass 4, s0063ba50: `extern
                    # AutoRef<cConnectingDialog> gConnectingDialog;` kept the old stub name next to the renamed item)
                    dtext = RS.rename_word(dtext, old_n, new_n, ns_r)
                ext.append(dtext)
                ext_name[dtext] = e["call"].split("::")[-1]
        # local stub types first: the extern declarations may name them (`extern const Vector3 kDefaultVector3;`, or a
        # slice typedef: `BOOL __stdcall VerQueryValueA(const void*, LPCSTR, ...)` before `typedef int BOOL;` failed in
        # s0091e650); only an extern that the stubs' inline bodies use and that names no local struct, typedef or macro
        # goes before them.  Everything else (also `va_list` users, whose <stdarg.h> include is a slice item) goes after.
        local_names = set()
        for kind, t in self.items:
            if kind in ("struct", "typedef", "define"):
                local_names |= set(RS.item_names(kind, t))
            elif kind == "other" and re.match(r"^\s*(?:template\s*<(?:[^<>]|<[^<>]*>)*>\s*)?(?:struct|class|union)\s+\w+(?:[^;]*\{|\s*;)", RS.mask(RS.unwrap_namespaces(t)[1])):
                # a class template the parser files as "other" (s0063ba50 `template <class T> struct AutoRef {..}`), or a forward
                # declaration (s0063d9e0 `struct IPropList;` before `extern IPropList* gAppProperties;`): an extern
                # that names it goes after the stubs (C2143 before '<', 14 functions dropped, fix pass 4)
                local_names |= set(RS.item_names(kind, t))
        local_names.add("va_list")
        stub_ids = set(RS.IDENT.findall(RS.mask(stub_text)))
        ext_early = [d for d in ext if not (set(RS.IDENT.findall(RS.mask(d))) & local_names)
                     and ext_name.get(d) in stub_ids]
        ext_late = [d for d in ext if d not in ext_early]
        if ext_early:
            lines += ["", "// unnamed retail callees and globals (address in the comment)"] + ext_early
        lines += self.render_local_items(fns, ext)
        if ext_late:
            lines += ["", "// unnamed retail callees and globals that name local stubs (address in the comment)"] + ext_late
        # one #include per header (the canonical includes and the local items' header for a replaced stub repeated
        # "EA/XML/XmlTextWriter.h" in s009013e0)
        out, seen_inc = [], set()
        for l in "\n".join(lines).split("\n"):
            if re.match(r"^\s*#\s*include\b", l):
                if l.strip() in seen_inc:
                    continue
                seen_inc.add(l.strip())
            out.append(l)
        return "\n".join(out) + "\n"

    canon_hdrs = []

    def canonical_item_header(self, text):
        """Header (relative to src/game/include) of the canonical class a local-stub item defines, else None.  The item is a
        class/struct/template definition, possibly wrapped in `namespace X {` blocks (parse_preamble wraps every item of a
        namespace block individually); the qualified name decides: EA::Variant -> EA/Variant.h, SP::cPropertyList ->
        SP/cPropertyList.h, template EA::Thread::AtomicInt -> EA/Thread/AtomicInt.h (headers.py FAMILY_HEADERS)."""
        ns, inner = RS.unwrap_namespaces(text)
        names = RS.item_names("struct", inner) if RS.mask(inner).lstrip().startswith(("struct", "class", "union", "template")) else []
        me = re.match(r"\s*enum\s+([A-Za-z_]\w*)\s*\{", RS.mask(inner))
        if me:
            names = [me.group(1)]       # a named enum with a canonical header (fix pass 5, s005580e0 SP::FunctionalMatch::Sentinel)
        if len(names) != 1:
            return None
        q = "::".join(ns + [names[0]])
        path = H.include_path(q)
        if os.path.exists(os.path.join(INC, path)):
            # the file must declare the class (eastl/string.h exists but declares basic_string/string8/string16, not `string`)
            htext = open(os.path.join(INC, path), encoding="utf-8", errors="replace").read()
            if re.search(r"\b(?:struct|class|union|enum)\s+%s\b|\btypedef\b[^;]*\b%s\s*;" % (re.escape(names[0]), re.escape(names[0])), htext):
                return path
            return None
        fam = H.family_header(q + "<") or H.family_header(q)
        if fam and os.path.exists(os.path.join(INC, fam)):
            return fam
        # a typedef or class another header of the namespace's directory defines (`eastl::string8` is a typedef in
        # eastl/string.h: the s0083c900 stub `namespace eastl { struct string8 {..} }` was not recognised, so it was not
        # renamed and redefined the typedef once a later slice included the header: C2371)
        if ns:
            dpath = os.path.join(INC, *ns)
            if os.path.isdir(dpath):
                for f in sorted(os.listdir(dpath)):
                    if not f.endswith(".h"):
                        continue
                    htext = open(os.path.join(dpath, f), encoding="utf-8", errors="replace").read()
                    if re.search(r"\btypedef\b[^;{]*\b%s\s*;|\b(?:class|struct|union)\s+%s\s*(?::[^;{]*)?\{" % (
                            re.escape(names[0]), re.escape(names[0])), htext):
                        return os.path.join(*ns, f).replace(os.sep, "/")
        return None

    def render_local_items(self, fns, ext=()):
        """The slice's own system includes and the local stub types/typedefs/statics/helpers the emitted functions use."""
        out = []
        verb = [c for c in fns if getattr(c, "verbatim", False)]
        texts = [c.defline + "\n" + c.out_body for c in fns] + list(ext)
        # a converted variadic body (va_list / va_start) needs the slice's <stdarg.h> too (s009013e0 AppendAttributeF 0x9017d0)
        varargs = any(re.search(r"\bva_(?:list|start|arg|end)\b", t) for t in texts)
        if verb or varargs:
            seen = set()
            for kind, text in self.items:
                if kind in ("include", "pragma") and text.strip() not in seen and not re.search(r'#\s*include\s+"', text) and \
                        (verb or "stdarg" in text):
                    seen.add(text.strip())
                    out.append(text)
        skip = {k for k, (kind, text) in enumerate(self.items) if kind == "extern" and any(
            n in self.externs for n in RS.item_names(kind, text))}
        # the slice's prototype of a namespace function this TU defines (`namespace SP { bool GetPropertyAsKey(const
        # cPropertyList*, ...); }`) is dropped: the definition with the canonical signature declares it, and the slice's
        # parameter types (its local stubs) would clash with the canonical ones
        defined = {c.name for c in fns if c.free and not getattr(c, "verbatim", False) and c.decl is not None}
        for k, (kind, text) in enumerate(self.items):
            if kind in ("extern", "other"):
                _ns, inner = RS.unwrap_namespaces(text)
                mi = RS.mask(inner)
                names = RS.item_names(kind, text)
                if names and set(names) <= defined and mi.strip().endswith(";") and "{" not in mi:
                    skip.add(k)
        # a local stub of a class/template that has a canonical header is not emitted: the header replaces it (the include
        # goes in when a function uses the name)
        used = set()
        for t in texts:
            used |= RS.item_uses("other", t)
        chains = {re.sub(r"\s+", "", mm.group(0)) for t in texts
                  for mm in re.finditer(r"[A-Za-z_]\w*(?:\s*::\s*~?[A-Za-z_]\w*)+", RS.mask(t))}
        vused = set()
        vtexts = [c.defline + "\n" + c.out_body for c in fns if getattr(c, "verbatim", False)]
        for t in vtexts:
            vused |= RS.item_uses("other", t)
        for kind, text in RS.needed_items(self.items, vtexts):        # and what the stubs they use refer to
            vused |= set(RS.item_names(kind, text))
        # headers the TU includes anyway (the converted functions' classes) and everything they include: a stub of a class
        # those headers define would be a redefinition, so the canonical class wins there even for a verbatim function
        inc_closure = set()
        todo = [h for h in self.collect_includes()]
        while todo:
            h = todo.pop()
            if h in inc_closure:
                continue
            inc_closure.add(h)
            try:
                for mm in re.finditer(r'^#include "([^"]+)"', open(os.path.join(INC, h), encoding="utf-8").read(), re.M):
                    todo.append(mm.group(1))
            except OSError:
                pass
        for k, (kind, text) in enumerate(self.items):
            hdr = self.canonical_item_header(text)
            # a verbatim function keeps the slice's own stub (its members/signatures are the slice's, e.g.
            # `const char** MainArguments(..)` where the canonical class returns `const char * const *`) unless a header
            # the TU includes already defines the class
            if hdr and (hdr in inc_closure or not (set(RS.item_names(kind, text)) & vused)):
                skip.add(k)
                ns, _inner = RS.unwrap_namespaces(text)
                qn = ["::".join(ns + [n]) for n in RS.item_names(kind, text)]
                if (any(n in used for n in RS.item_names(kind, text)) or any(ch == q or ch.startswith(q + "::") for q in qn for ch in chains)) \
                        and hdr not in self.canon_hdrs:
                    self.canon_hdrs.append(hdr)
        # a verbatim function (and the stubs it needs) is the slice's text: the extern declarations it uses stay as the slice
        # spelled them (`extern const int kTimeoutNone[];`), whatever the converted functions call them
        for k in [k for k in skip if self.items[k][0] == "extern" and set(RS.item_names(*self.items[k])) & vused]:
            skip.discard(k)
        # a using-directive is not emitted: in a module TU it reaches every later slice's functions (s00942290's `using namespace
        # EA::Internet;` made s009413d0's global stub `HTTPClient` ambiguous with the canonical class: C2872); verbatim methods
        # of namespaced stubs are qualified instead (render_function)
        skip |= {k for k, (kind, text) in enumerate(self.items) if re.match(r"^\s*using\s+namespace\b", RS.mask(text))}
        # a slice's own declaration of a compiler intrinsic (`extern "C" long __stdcall _InterlockedExchange(volatile long*, long);`,
        # s007af8b0) clashes with <intrin.h> once any slice of the module TU includes it (C2373): the header's declaration is used
        tu_path = W(*getattr(self, "tu_rel", "x/y").split("/"))
        tu_text = open(tu_path).read() if os.path.exists(tu_path) else ""
        if re.search(r"#\s*include\s*<intrin\.h>", tu_text) or any(k2 == "include" and "intrin.h" in t2 for k2, t2 in self.items):
            skip |= {k for k, (kind, text) in enumerate(self.items) if kind in ("extern", "other") and
                     any(re.match(r"^(_Interlocked\w+|_ReadWriteBarrier|_BitScan\w+|__debugbreak|__cpuid|_mm_\w+)$", n) for n in RS.item_names(kind, text))
                     and "{" not in RS.mask(text)}
            if not any(k2 == "include" and "intrin.h" in t2 for k2, t2 in self.items) and \
                    any(re.search(r"\b_Interlocked\w+\s*\(", c.out_body) for c in fns):
                out.append("#include <intrin.h>")
        items = RS.needed_items(self.items, texts, skip)
        items = self.qualify_after_using(items)
        # a kept function declaration that only converted (non-verbatim) functions call is spelled with the canonical class
        # names (`VariantPair*` -> `eastl::pair<unsigned int, EA::Variant>*`): the slice stub type it mentions is not what the
        # converted bodies pass.  Declarations that verbatim functions use keep the slice's spelling and stub types.
        items = [(kind, self.item_view(kind, text, fns)) for kind, text in items]
        items = [(kind, self.annotate_renamed(kind, text)) for kind, text in items]
        for hdr in self.canon_hdrs:
            out.append('#include "%s"' % hdr)
        # a stub's inline body that calls a free function of this slice (s00942ff0: JobVecBlob::destroyRange() calls
        # JobDestroyRange 0x943420, which the slice defines further down; in the TU every function follows the items: C3861) gets
        # the function's prototype (with its retail address, so the resolver binds it when the function is not emitted) in front
        # of the first item that uses it
        free_fns = {}
        for c in self.chunks:
            if c.name and (not c.cls or getattr(c, "free", False)) and not getattr(c, "implicit", None):
                sig = re.sub(r"^\s*//.*$", "", c.sig_text, flags=re.M)
                sig = sig.rsplit(";", 1)[-1] if ";" in mask(sig) else sig
                sig = " ".join(sig.split())
                for ns_r, old_n, new_n in getattr(self, "renamed", []):       # the stub renames of this run
                    sig = RS.rename_word(sig, old_n, new_n, ns_r)
                head = sig.split("(")[0]
                if sig and "(" in sig and not re.match(r"^template\b", sig) and "::" not in head and "<" not in head:
                    free_fns.setdefault(c.name, (sig, c.va, list(getattr(c, "enc_ns", []) or [])))
        declared = set()
        if items:
            out += ["", "// ---- items of slice %s begin (TODO(rewrite): local stubs, replace by canonical classes)" % self.bid]
            for kind, text in items:
                if kind in ("struct", "other") and "{" in RS.mask(text):
                    for nm in sorted(RS.item_uses(kind, text) & set(free_fns)):
                        if nm in declared or nm in RS.item_names(kind, text):
                            continue
                        declared.add(nm)
                        sig, va, ens = free_fns[nm]
                        if va not in {f.va for f in fns}:
                            # not landed here: a `static` prototype without its body is C2129 (mig10 SPCookie, TrimWhitespace
                            # 0x609cc0 stays in the slice)
                            sig = re.sub(r"^(?:\s*(?:static|inline|__inline|__forceinline)\b)+\s*", "", sig)
                        cmt = "  // 0x%08x (defined below; used by a stub's inline body)" % va
                        out.append((" ".join("namespace %s {" % n for n in ens) + " %s; " % sig + "}" * len(ens) + cmt) if ens else sig + ";" + cmt)
                out.append(text)
            out.append("// ---- items of slice %s end" % self.bid)
        return out

    def qualify_after_using(self, items):
        """A global-scope item that follows the slice's `using namespace N;` (the directive is not emitted, see render) names
        N's stubs without the qualifier: they get `N::` (fix pass 4, s0059c4c0: `template class eastl::map<uint32_t,
        EA::AutoRefCount<cSPEditorAnimatedCreatureData> >;` after `using namespace SP;` was emitted at global scope, C2065 on
        the renamed SP stub, and the whole slice (22 byte-exact functions) stayed behind)."""
        usings = []
        for k, (kind, text) in enumerate(self.items):
            mm = re.match(r"^\s*using\s+namespace\s+([\w:\s]+?)\s*;", RS.mask(text))
            if mm and not RS.unwrap_namespaces(text)[0]:
                usings.append((k, re.sub(r"\s+", "", mm.group(1))))
        if not usings:
            return items
        idx = {id(t): k for k, (_kd, t) in enumerate(self.items)}
        out = []
        for kind, text in items:
            k = idx.get(id(text))
            ins = RS.unwrap_namespaces(text)[0]
            if k is None:
                out.append((kind, text))
                continue
            own = set() if re.match(r"^\s*template\s+(?:class|struct)\b", RS.mask(text)) else set(RS.item_names(kind, text))
            for uk, n in usings:
                # (an item of ANOTHER namespace after the directive too: s009ba4c0's `namespace nSPCreatureAnim { struct
                # goal_pos_rot { vector_3 pos; ..} }` after `using namespace checkerlib;`, C2146, fix pass 4)
                if uk <= k and (not ins or ins[0] != n.split("::")[0]):
                    text = self.qualify_names(text, n, own)
            out.append((kind, text))
        return out

    def qualify_names(self, text, n, own=()):
        """Prefix `n::` to the bare uses in `text` of the stubs the slice defines in namespace n (and not at global scope)."""
        defined, glob = collections.defaultdict(set), set()
        for kind, t in self.items:
            ns, _inner = RS.unwrap_namespaces(t)
            # an explicit instantiation / using-directive declares nothing, also inside a namespace block (s0056df80:
            # `namespace SP { namespace Traits { using namespace eastl; } }` made every `eastl::` SP::Traits::eastl::, C3083)
            if re.match(r"^\s*(?:template\s+(?:class|struct)\b|using\b)", RS.mask(_inner)):
                continue
            (defined["::".join(ns)] if ns else glob).update(RS.item_names(kind, t))
        for v in sorted(defined.get(n, ()), key=len, reverse=True):
            if v in glob or v in own:
                continue
            m = RS.mask(text)
            pat = re.compile(r"(?<![\w.>:~])%s\b" % re.escape(v))
            pieces, last = [], 0
            for mm in pat.finditer(m):
                if re.search(r"\b(?:namespace|struct|class|union|enum)\s+$", m[max(0, mm.start() - 12):mm.start()]):
                    continue
                pieces.append(text[last:mm.start()] + n + "::" + v)
                last = mm.end()
            if pieces:
                text = "".join(pieces) + text[last:]
                self.stats["qualified_after_using"] += 1
        return text

    def annotate_renamed(self, kind, text):
        """A stub renamed `Name_sNNNN_NNNN` declares methods whose decorated names no longer say which retail function they
        are (round 2 left 0x68f970/0x68f9f0/0x690120 in s0068f670 for this: `?Lock@Mutex_s0068_f670@Thread@EA@@` unresolved,
        PASS -> UNSUPPORTED): each declaration without an address gets the `// 0xVA` of the original class's method of that
        name and arity (generated header, else a unique pdb_names entry), which the difftest resolver binds by annotation."""
        ren = {new_n: (ns, old_n) for ns, old_n, new_n in getattr(self, "renamed", [])}
        ns_i, inner = RS.unwrap_namespaces(text)
        names = RS.item_names("struct", inner) if RS.mask(inner).lstrip().startswith(("struct", "class", "union", "template")) else []
        if len(names) != 1 or names[0] not in ren:
            return text
        ns, old_n = ren[names[0]]
        q = "::".join(list(ns) + [old_n])
        if not hasattr(self, "_pdb_rev"):
            self._pdb_rev = collections.defaultdict(list)
            for va_s, e in self.pdb_names.items():
                if e.get("name"):
                    self._pdb_rev[e["name"]].append(int(va_s, 16))
        canon = Canon.get(q)
        # a one-line stub `struct Mutex { void Lock(const void*); void Unlock(); char pad[0x28]; };` is laid out one member per
        # line first, so its methods get annotated too (fix pass 5, s0075de80: ?Lock@Mutex_s0075_de80@Thread@EA@@ stayed
        # unresolved, 0x75e090..0x75e3b0 PASS -> UNSUPPORTED)
        def _expand(t):
            out2 = []
            for l in t.split("\n"):
                ml = re.match(r"^(\s*)((?:struct|class|union)\s+\w+[^{;]*)\{([^{}]*)\}\s*;\s*(//.*)?$", l)
                if ml and "(" in ml.group(3) and ml.group(3).count(";") >= 2:
                    out2.append("%s%s{%s" % (ml.group(1), ml.group(2), ("  " + ml.group(4)) if ml.group(4) else ""))
                    out2 += ["%s    %s;" % (ml.group(1), d.strip()) for d in ml.group(3).split(";") if d.strip()]
                    out2.append("%s};" % ml.group(1))
                else:
                    out2.append(l)
            return "\n".join(out2)
        text = _expand(text)
        out = []
        for line in text.split("\n"):
            mm = re.match(r"^(\s+)(?:__declspec\([^)]*\)\s*)?(?:virtual\s+)?[\w:<>\*&\s~]*?\b(~?\w+)\s*\(([^;{}]*)\)\s*(?:const\s*)?;\s*(//.*)?$", line)
            if mm and not re.search(r"0x[0-9a-fA-F]{6,8}", mm.group(4) or ""):
                nm, ar = mm.group(2), len(split_params(mm.group(3))) if mm.group(3).strip() not in ("", "void") else 0
                vas = sorted({d.va for d in canon.decls if d.va and d.name == nm and len(d.params) == ar and not d.virtual}) if canon.exists else []
                if not vas:
                    vas = sorted(set(self._pdb_rev.get(q + "::" + nm, [])))
                if not vas:
                    # a global stub of a namespaced class (s006907e0 `cJobManager` = SP::cJobManager: FailJob, GetFreeLink)
                    suf = "::%s::%s" % (old_n, nm)
                    if not hasattr(self, "_pdb_suffix"):
                        self._pdb_suffix = collections.defaultdict(set)
                        for n2, v2 in self._pdb_rev.items():
                            parts = n2.split("::")
                            if len(parts) >= 2:
                                self._pdb_suffix["::%s::%s" % (parts[-2], parts[-1])].update(v2)
                    vas = sorted(self._pdb_suffix.get(suf, set()))
                if not vas:
                    # a method another slice landed in a module TU under the same class name (s0068f670's
                    # cJobManager::GetFreeLink 0x690050, unnamed in pdb_names)
                    vas = sorted({va2 for va2, (c2, n2) in self.tu_methods().items()
                                  if n2 == nm and re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", c2.split("::")[-1]) == old_n})
                if len(vas) == 1:
                    line = "%s  // 0x%08x (%s::%s)" % (line.rstrip(), vas[0], q, nm) if not mm.group(4) else "%s 0x%08x" % (line.rstrip(), vas[0])
                    self.stats["renamed_stub_methods_annotated"] += 1
            out.append(line)
        return "\n".join(out)

    def annotate_stub_methods(self, kind, text):
        """A local stub struct of a class whose methods this slice defines declares them without an address (they were
        defined in the same TU); once a definition is converted (or moved to another module TU) the call from a verbatim
        function is an external reference, which the difftest resolver binds by the `// 0xVA` comment of the declaration:
        add it.  (`bool SetLocation(const wchar_t* path);`  ->  `...  // 0x008d99c0`)"""
        if kind != "struct":
            return text
        names = RS.item_names(kind, text)
        if len(names) != 1:
            return text
        defs = collections.defaultdict(list)
        for c in self.chunks:
            if c.cls == names[0] and c.name:
                defs[c.name].append(c.va)
        if not defs:
            return text
        out = []
        for line in text.split("\n"):
            mm = re.match(r"^(\s+)(?:__declspec\([^)]*\)\s*)?(?:virtual\s+)?[\w:<>\*&\s~]*?\b(~?\w+)\s*\([^;{}]*\)\s*(?:const\s*)?;\s*(//.*)?$", line)
            if mm and len(defs.get(mm.group(2), [])) == 1 and not re.search(r"0x[0-9a-fA-F]{6,8}", mm.group(3) or ""):
                line = "%s  // 0x%08x" % (line.rstrip(), defs[mm.group(2)][0]) if not mm.group(3) else \
                    "%s 0x%08x" % (line.rstrip(), defs[mm.group(2)][0])
            out.append(line)
        return "\n".join(out)

    # ---- 8. apply ---------------------------------------------------------------------------------
    def apply(self):
        mods = collections.defaultdict(list)
        for c in self.fns:
            mods[c.module].append(c)
        results = {}
        for module, fns in mods.items():
            self.module = module
            d, obj = os.path.split(module)
            stem = obj[:-4]
            self.tu_rel = "src/game/%s/%s.cpp" % (d, stem)
            tu = W(*self.tu_rel.split("/"))
            os.makedirs(os.path.dirname(tu), exist_ok=True)
            self.drop_annotation_dummies(tu)
            self.drop_orphan_instantiations(fns, tu)
            self.rename_shadowed_stubs(fns)
            self.resolve_conflicts(fns, tu)
            pre = self.render_preamble(fns)
            blocks = {c.va: self.render_function(c) for c in fns}
            old_pre = None
            if os.path.exists(tu):
                old = open(tu).read()
                parts = re.split(r"(?m)^(?=// @ 0x[0-9a-fA-F]+$)", old)
                old_vas = {int(re.match(r"// @ 0x([0-9a-fA-F]+)", b).group(1), 16) for b in parts[1:]}
                if old_vas and not old_vas <= {c.va for c in self.chunks}:
                    # functions of other slices live in this TU: keep them, merge preamble and blocks
                    old_pre = parts[0]
                    mine = {c.va for c in self.chunks}
                    bv = getattr(self, "batch_vas", None)
                    if bv:
                        # a VA the batch gives to another slice is that slice's block (fix pass 5: s007ca950 marks 0x7ca060, which
                        # mig5 lands from s007c9910; re-applying s007ca950 pruned s007c9910's function)
                        mine = {va for va in mine if "%08x" % va in bv[1]}
                    emitted = {c.va for c in fns}
                    for b in parts[1:]:
                        va = int(re.match(r"// @ 0x([0-9a-fA-F]+)", b).group(1), 16)
                        if va in mine and va not in emitted and va not in getattr(self, "failed_vas", ()):
                            # an earlier run of this slice emitted it, this one does not (a rule or a header changed its class):
                            # the TU must not keep a function the slice now holds back.  A function that only failed to
                            # compile in this run keeps its old block (fix pass 6)
                            self.notes.append(("pruned", "0x%08x removed from the module TU: not emitted by this run" % va))
                            continue
                        blocks.setdefault(va, b if b.endswith("\n") else b + "\n")
                    pre = self.merge_preamble(old_pre, pre, "\n".join(blocks[v] for v in blocks if v not in emitted))
            body = "\n".join(blocks[v] for v in sorted(blocks))
            pre = self.forward_protos(pre, blocks)
            pre = self.held_callee_protos(pre, body, fns)
            pre = self.placement_new_guard(pre)
            # fix pass 6 C19: every re-apply added blank lines (s00575270: +153); runs of blank lines collapse to one
            open(tu, "w").write(re.sub(r"\n{3,}", "\n\n", pre + "\n" + body))
            results[module] = (tu, sorted(c.va for c in fns))
        return results

    PNEW_GUARD = "#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)"
    PNEW_RE = r"(?m)^\s*inline\s+void\s*\*\s*operator\s+new\s*\(\s*(?:unsigned\s+int|size_t\w*|unsigned)\s*\w*\s*,\s*void\s*\*\s*\w*\s*\)\s*(?:throw\s*\(\s*\)\s*)?\{"
    PDEL_RE = r"(?m)^\s*inline\s+void\s+operator\s+delete\s*\(\s*void\s*\*\s*\w*\s*,\s*void\s*\*\s*\w*\s*\)\s*(?:throw\s*\(\s*\)\s*)?\{"

    def placement_new_guard(self, pre):
        """A TU that includes <new> and holds a slice's own inline placement `operator new(size_t, void*)` (without <new>'s
        throw(): no null check before the constructor, which the byte-exact slices need) redefines it (C2084).  As round 5
        did by hand in SPGraphicsModelManager.cpp: `#define __PLACEMENT_NEW_INLINE` before the first `#include <new>` makes
        <new> skip its pair, and a placement delete is provided when no slice item defines one (fix pass 5, re-landing
        SPGraphicsModelManager from scratch: s00745ac0..s0074b170 failed C2084 against s00743b20's placement new)."""
        if not re.search(r"(?m)^#include\s*<new>", pre) or not re.search(self.PNEW_RE, mask(pre)):
            return pre
        lines = pre.split("\n")
        if self.PNEW_GUARD not in lines:
            k = next(i for i, l in enumerate(lines) if re.match(r"#include\s*<new>", l))
            lines.insert(k, self.PNEW_GUARD)
        if not re.search(self.PDEL_RE, mask("\n".join(lines))):
            last_inc = max(i for i, l in enumerate(lines) if l.startswith("#include"))
            lines.insert(last_inc + 1, "inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)")
        return "\n".join(lines)

    def forward_protos(self, pre, blocks):
        """Prototypes for free functions of the TU that a function earlier in VA order calls: the slice defined its helper
        first (s00538e90 `cSPVector3* normalized(..)` at the top, 0x539440), the module TU puts it in VA order after its
        callers (0x5391c0 Execute: C3861, fix pass 3).  Only plain global free functions (no class/namespace qualifier, not
        inside a namespace block, not a template) are declared."""
        defs = {}
        for va in sorted(blocks):
            b = blocks[va]
            # a function the slice defined inside `namespace X {` (one wrapper per level, nothing else in it) is declared
            # inside the same namespaces (fix pass 5, s0057bfb0: `namespace SP { __forceinline void SendEditorStateChanged() }`
            # at 0x57c440, called by SetLocalState 0x57c2f0: C3861)
            wrap = []
            mw = re.match(r"^((?:\s*//[^\n]*\n)*)((?:\s*namespace\s+\w+\s*\{\s*\n)+)", b)
            if mw:
                wrap = re.findall(r"namespace\s+(\w+)", mw.group(2))
                b = b[mw.end():]
            if re.search(r"(?m)^\s*(namespace\b|template\s*<)", b):
                continue
            mb = mask(b)
            k = mb.find("{")
            if k < 0:
                continue
            head_lines = [l for l in b[:k].split("\n") if l.strip() and not l.lstrip().startswith(("//", "#"))]
            head = " ".join(l.strip() for l in head_lines)
            m = re.match(r"^((?:static\s+|inline\s+)?[\w\s\*&<>,]*?[\w\*&>]\s*\**)\s*\b([A-Za-z_]\w*)\s*\(([^{}]*)\)\s*$", head)
            if not m or "::" in head.split("(")[0] or m.group(2) in ("if", "while", "for", "switch", "return"):
                continue
            defs.setdefault(m.group(2), (va, head, wrap))
        if not defs:
            return pre
        protos = []
        mp = mask(pre)
        for name, (va, head, wrap) in sorted(defs.items(), key=lambda x: x[1][0]):
            if re.search(r"\b%s\s*\(" % re.escape(name), mp):
                continue                  # the preamble declares (or defines) it already
            if any(v < va and re.search(r"(?<![\w:.>])%s\s*\(" % re.escape(name), mask(blocks[v])) for v in blocks):
                protos.append("".join("namespace %s { " % w for w in wrap) + head + ";" + " }" * len(wrap) +
                              "   // defined at 0x%08x, called earlier in the TU" % va)
        if not protos:
            return pre
        self.notes.append(("forward-proto", ", ".join(p.split("(")[0].split()[-1] for p in protos)))
        return pre.rstrip("\n") + "\n\n// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)\n" + \
            "\n".join(protos) + "\n"

    def held_callee_protos(self, pre, body, fns):
        """A free function this slice defines but does not emit (another object's, or held back) that an emitted function of the
        slice calls gets a prototype with its retail address (fix pass 4, s00766fa0: PaintHolder::FUN_00767170 calls
        ReadPaintStuff 0x766fa0, module None: C3861 and the byte-exact caller was dropped)."""
        emitted = {c.va for c in fns}
        texts = mask("\n".join(c.defline + "\n" + c.out_body for c in fns))
        mp, mb = mask(pre), mask(body)
        protos = []
        for c in self.chunks:
            if c.va in emitted or c.cls or not c.name or getattr(c, "inst", False) or getattr(c, "implicit", None):
                continue
            name = str(c.name)
            # a call, or the function's address (`VisitTree(a, (void*)FUN_0080d6b0, local)`, mig13 s0080d670: C2065)
            if not re.search(r"(?<![\w:.>])%s\b(?!\s*::)" % re.escape(name), texts):
                continue
            if re.search(r"\b%s\s*\(" % re.escape(name), mp) or re.search(r"(?m)^(?![\s{}])(?!if\b|while\b|for\b|return\b)[^\n;]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), mb):
                continue            # declared or defined in the TU already
            sig = re.sub(r"^\s*//.*$", "", c.sig_text, flags=re.M)
            sig = sig.rsplit(";", 1)[-1] if ";" in mask(sig) else sig
            sig = " ".join(sig.split())
            if not sig or "::" in sig.split("(")[0] or re.match(r"^template\b", sig):
                continue
            for ns_r, old_n, new_n in getattr(self, "renamed", []):
                sig = RS.rename_word(sig, old_n, new_n, ns_r)
            ens = list(getattr(c, "enc_ns", []) or [])
            # a static/inline helper of the slice declared here without its body is C2129 (mig10 SPCookie TrimWhitespace)
            sig = re.sub(r"^(?:\s*(?:static|inline|__inline|__forceinline)\b)+\s*", "", sig)
            cmt = "  // 0x%08x (stays in the slice: not this object's)" % c.va
            # the closing braces go before the comment (they were after it and commented out: C1075, mig10 eapdeditor 0xa4c470)
            protos.append((" ".join("namespace %s {" % n for n in ens) + " " + sig + "; " + "}" * len(ens) + cmt) if ens else sig + ";" + cmt)
        if not protos:
            return pre
        self.notes.append(("held-callee-proto", ", ".join(p.split("(")[0].split()[-1] for p in protos)))
        return pre.rstrip("\n") + "\n\n// callees this slice defines outside this object (rewrite.py held_callee_protos)\n" + "\n".join(protos) + "\n"

    def _tu_defines_cpp(self, name):
        """The module TU (as it is on disk) defines a free function `name` (after the first marker) without C linkage."""
        tu = W(*getattr(self, "tu_rel", "x/y").split("/"))
        if not os.path.exists(tu):
            return False
        t = open(tu).read()
        k = t.find("\n// @ 0x")
        if k < 0:
            return False
        body = mask(t[k:])
        for mm in re.finditer(r"(?m)^([^\n;{}]*?)\b%s\s*\([^;{}]*\)\s*\{" % re.escape(name), body):
            if "::" in mm.group(1).split("(")[0][-2:] or re.search(r"extern\s*\"C\"", t[k + mm.start():k + mm.end()]):
                continue
            if not re.search(r"(\w+)::\s*$", mm.group(1)):
                return True
        return False

    def merge_preamble(self, old, new, others=""):
        """Preamble of the module TU as it is (`old`) plus what this slice adds (`new`): new includes after the last old
        include; every other new item (extern, local stub struct, typedef, static, helper) appended unless the TU already
        holds the same item (same text modulo whitespace and comments).  Same-name items with different text were
        renamed before rendering (resolve_conflicts)."""
        # a re-run of a slice that is not the last one merged keeps its items section where it was: later slices' sections
        # share its typedefs and stubs (identical text is emitted once), so the section must stay in front of theirs
        m0 = re.search(r"\n?// ---- items of slice %s begin" % self.bid, old)
        ins_at = len(old[:m0.start()].rstrip("\n").split("\n")) if m0 else None
        mown = re.search(r"(?s)// ---- items of slice %s begin[^\n]*\n(.*?)// ---- items of slice %s end" % (self.bid, self.bid), old)
        own_old = parse_preamble(mown.group(1).rstrip("\n").split("\n"))[1] if mown else []
        old = re.sub(r"(?s)\n?// ---- items of slice %s begin.*?// ---- items of slice %s end\n?" % (self.bid, self.bid), "\n", old)
        lines = old.rstrip("\n").split("\n")
        _s, old_items = parse_preamble(lines)
        # includes compare by their text: RS.norm masks string literals, which blanks the file name of every #include
        have = {(t.strip() if k == "include" else RS.norm(t)) for k, t in old_items if k not in ("comment",)}
        _s2, new_items = parse_preamble(new.rstrip("\n").split("\n"))
        old_protos = {}
        for kind, text in old_items:
            pk = proto_key(text) if kind in ("extern", "other") else None
            if pk:
                old_protos.setdefault(pk[0], []).append(pk + (text,))
        def _only_later(text):
            # every identical copy of this item sits behind this slice's section (a later slice's block deduplicated against
            # this slice's copy when it was applied): dropping it here leaves the section without it (fix pass 5, s007ca950:
            # `aligned_buffer` only in s007cc5f0's block below, C2143 in fixed_vector)
            first = next((l.strip() for l in text.split("\n") if l.strip()), "")
            pos = [i for i, l in enumerate(lines) if first and l.strip() == first]
            return bool(pos) and min(pos) >= ins_at
        incs, rest, seen_local = [], [], False
        for kind, text in new_items:
            if kind == "comment":
                if "local stubs" in text:
                    seen_local = True
                    pending = text
                continue
            n = text.strip() if kind == "include" else RS.norm(text)
            if n in have and not (kind != "include" and ins_at is not None and _only_later(text)):
                continue
            pk = proto_key(text) if kind in ("extern", "other") else None
            dll = lambda t: bool(re.search(r"__declspec\s*\(\s*dllimport\s*\)", RS.mask(t)))
            if pk and dll(text):
                # the TU declares it without dllimport: the CRT is imported in retail (/MD: `call dword ptr [__imp_isspace]`, which
                # s0083e1c0's byte-exact EvalRealExpression/EvalIntTerm/EvalIntExpression need; s0083c900 declared a plain
                # `isspace` first): the dllimport spelling replaces the TU's declarations of the same function
                for o in old_protos.get(pk[0], []):
                    if same_function(pk, o) and not dll(o[5]) and o[5] in "\n".join(lines):
                        lines = "\n".join(lines).replace(o[5], text).split("\n")
                        self.notes.append(("dedup-proto", "%s: the TU's declaration respelled with this slice's dllimport" % pk[0]))
            if pk and pk[1] and self._tu_defines_cpp(pk[0].split("::")[-1]):
                # an `extern "C"` prototype of a function another slice DEFINES in this TU with C++ linkage (s00767ee0's
                # `extern "C" void __cdecl UnionDestroy(void*, int)` vs s00765f80's definition, 0x7668c0): emitted first, it gave
                # the definition C linkage and the byte-exact row lost its symbol (fix pass 4)
                self.notes.append(("dedup-proto", "%s: defined in the module TU with C++ linkage; this slice's extern \"C\" dropped" % pk[0]))
                continue
            def _later(o):
                # the TU's declaration sits in a later slice's block, behind where this slice's section goes back in: this
                # slice's items cannot see it (fix pass 5, s0057bfb0's `operator new[]` vs s005802f0's: C2661 in its inline
                # operator new and allocator stub).  A redeclaration with the same linkage and return type is legal: keep it
                if ins_at is None or o[1] != pk[1] or re.sub(r"\s+", "", o[3]) != re.sub(r"\s+", "", pk[3]):
                    return False
                first = o[5].strip().split("\n")[0]
                pos = next((i for i, l in enumerate(lines) if first and first in l), None)
                return pos is not None and pos >= ins_at
            if pk and any(same_function(pk, o) and not _later(o) for o in old_protos.get(pk[0], [])):
                # the TU already declares this function with another spelling: linkage (`extern "C"` vs C++: C2732,
                # s00689ee0 RBTreeIncrement vs s00688dd0's), `__declspec(dllimport)` (s0083a9f0 _stricmp, s0083b810 isalpha),
                # `throw()` (s00942ff0 operator_delete__) or only the return type (C2556, s00948de0 vs s00947d50
                # ConcatenatePathComponents).  The TU's declaration is used; the call site codegen is the same
                self.notes.append(("dedup-proto", "%s: the module TU already declares it (%s); this slice's spelling dropped" % (
                    pk[0], " ".join(text.split())[:120])))
                continue
            have.add(n)
            if kind == "include":
                incs.append(text)
            else:
                rest.append(text)
        if own_old:
            # an item this slice's previous block had and this run no longer emits, which later blocks or other slices'
            # functions use: they deduplicated against this block's copy (identical text is emitted once), so it stays
            # (fix pass 5, s007ca950 re-applied after s007cb590/s007cc5f0: `aligned_buffer` vanished, C2143 in their blocks)
            ctx_used = RS.item_uses("other", "\n".join(lines) + "\n" + others)
            newn = {RS.norm(t) for k, t in new_items if k not in ("comment", "include")}
            keep_old = [t for k, t in own_old if k not in ("comment", "include") and RS.norm(t) not in newn and
                        RS.norm(t) not in have and any(n in ctx_used for n in RS.item_names(k, t)) and
                        self.rsfx not in t]      # (an item spelled with this slice's previous renames is stale)
            if keep_old:
                rest = keep_old + rest
                self.notes.append(("kept-items", "%d item(s) of this slice's previous block that the TU still uses" % len(keep_old)))
        if VA_GUARD in new and VA_GUARD not in lines:
            first_inc = next((i for i, l in enumerate(lines) if l.startswith("#include")), len(lines))
            lines = lines[:first_inc] + [VA_GUARD] + lines[first_inc:]
        last_inc = max([i for i, l in enumerate(lines) if l.startswith("#include")] or [len(lines) - 1])
        out = lines[:last_inc + 1] + incs + lines[last_inc + 1:]
        if rest:
            block = ["", "// ---- items of slice %s begin%s" % (self.bid, " (TODO(rewrite): local stubs, replace by canonical classes)" if seen_local else "")] + \
                rest + ["// ---- items of slice %s end" % self.bid]
            if ins_at is not None and ins_at < len(lines):
                at = ins_at + (len(incs) if ins_at > last_inc else 0)
                out = out[:at] + block + out[at:]
            else:
                out += block
        if self.sid not in lines[0]:
            out[0] = out[0].replace("migrated from slice(s) ", "migrated from slice(s) %s, " % self.sid)
        return "\n".join(out) + "\n"

    def resolve_conflicts(self, fns, tu):
        """Local items of this slice whose name the module TU already uses for a different definition are renamed
        `Name_<slice>` in this slice's items and function texts (every slice invents its own `struct String`)."""
        if not os.path.exists(tu):
            return
        old = open(tu).read()
        parts = re.split(r"(?m)^(?=// @ 0x[0-9a-fA-F]+$)", old)
        old_vas = {int(re.match(r"// @ 0x([0-9a-fA-F]+)", b).group(1), 16) for b in parts[1:]}
        if not old_vas or old_vas <= {c.va for c in self.chunks}:
            return                      # the TU is rebuilt from this slice alone
        old = re.sub(r"(?s)\n?// ---- items of slice %s begin.*?// ---- items of slice %s end\n?" % (self.bid, self.bid), "\n", parts[0])
        _s, old_items = parse_preamble(old.split("\n"))
        have = {}
        old_protos = {}
        for kind, text in old_items:
            for n in RS.item_names(kind, text):
                have[n] = RS.norm(text)
            pk = proto_key(text) if kind in ("extern", "other") else None
            if pk:
                old_protos.setdefault(pk[0], []).append(pk)
        # free functions other slices' blocks define in the TU: a local struct of the same name clashes (mig8 IMESupport:
        # s007f3380 landed `IMECandidateListCtor(..)` as a function, s007f42e0's `struct IMECandidateListCtor` then failed
        # C2059 in `((IMECandidateListCtor*)mem)->Ctor()`)
        mine_vas = {c.va for c in self.chunks}
        for b in parts[1:]:
            va_b = int(re.match(r"// @ 0x([0-9a-fA-F]+)", b).group(1), 16)
            if va_b in mine_vas:
                continue
            mb = RS.mask(b)
            k = mb.find("{")
            head = " ".join(l.strip() for l in b[:k].split("\n")[1:] if l.strip() and not l.strip().startswith(("//", "#"))) if k > 0 else ""
            mf = re.search(r"(?<![\w:~])([A-Za-z_]\w*)\s*\([^()]*(?:\([^()]*\)[^()]*)*\)\s*(?:const\s*)?$", head)
            if mf and not head[:mf.start()].rstrip().endswith("::"):
                have.setdefault(mf.group(1), "<free function of another slice>")
        # a prototype the module TU declares with the same parameters but another return type that names a different local stub
        # (s0063aa90 `cConfigMgr* GetConfigManager();` vs s0063ba50 `IConfigManager* GetConfigManager();`, both 0x67dd30):
        # merge_preamble kept the TU's spelling and this slice's verbatim calls of IConfigManager::GetBool did not compile
        # (C2039, fix pass 4): this slice's function is renamed; calls bind by the address comment.  When the TU's spelling
        # returns a canonical (qualified) class, that declaration keeps serving (s005c53c0's manual edits rely on it)
        local_types = set()
        for kind, text in self.items:
            if kind in ("struct", "typedef") or (kind == "other" and re.match(
                    r"^\s*(?:template\s*<(?:[^<>]|<[^<>]*>)*>\s*)?(?:struct|class|union)\s+\w+[^;]*\{", RS.mask(RS.unwrap_namespaces(text)[1]))):
                local_types |= set(RS.item_names(kind, text))
        ret_clash = set()
        # this slice's local types that the TU defines differently (they are renamed below): a prototype returning one of them
        # with the TU's identical SPELLING still clashes (fix pass 5, s005598b0 0x5598b0 Init / s005634e0 0x563ac0: `ICheatManager*
        # CheatManager();` in both slices, this slice's ICheatManager becomes ICheatManager_s0055_98b0, the TU's prototype was
        # kept and the verbatim `ICheatManager_s0055_98b0* p = CheatManager();` failed C2440)
        diff_local = set()
        for kind, text in self.items:
            for n in RS.item_names(kind, text):
                if n in local_types and n in have and have[n] != RS.norm(self.item_view(kind, text, fns)):
                    diff_local.add(n)
        for kind, text in self.items:
            pk0 = proto_key(text) if kind in ("extern", "other") else None
            if not pk0:
                continue
            # a prototype this slice declares inside a namespace hides the TU's GLOBAL one for every function in that
            # namespace (fix pass 5, s0049a2a0 `namespace SP { cMessageManager* MessageManager(); }` vs the global one of
            # s004a6f10, whose SP-scoped body then called this slice's: C2039 'RemoveListener'): compared by its short name
            short = pk0[0].split("::")[-1]
            pairs = [(pk0, o) for o in old_protos.get(pk0[0], [])]
            if short != pk0[0]:
                pairs += [((short,) + tuple(pk0[1:]), o) for o in old_protos.get(short, [])]
            else:
                # ... and the mirror case: this slice's GLOBAL prototype vs the TU's namespaced one, which hides it inside that
                # namespace (s00579e20 `MsgServer* MessageServer();` vs `namespace SP { IMessageServer* MessageServer(); }`:
                # the verbatim SP:: methods called the TU's, C2039 'Post')
                for k2, os_ in old_protos.items():
                    if "::" in k2 and k2.split("::")[-1] == short:
                        pairs += [(pk0, (short,) + tuple(o[1:])) for o in os_]
            for pk, o in pairs:
                if same_function(pk, o) and re.sub(r"\s+", "", pk[3]) == re.sub(r"\s+", "", o[3]) and \
                        not pk[0].split("::")[-1].startswith("operator") and "::" not in o[3] and \
                        set(RS.IDENT.findall(pk[3])) & diff_local:
                    ns, _i = RS.unwrap_namespaces(text)
                    ret_clash.add((tuple(ns), pk[0].split("::")[-1]))
                # (a qualified return type keeps the TU's declaration only when it is a canonical class: fix pass 5, s00591fa0
                # `ISaveArea* GetSaveArea(uint32_t)` vs s0058e6d0's `Resource::Database* GetSaveArea(uint32_t)`, a stub of a
                # slice-local namespace: C2039 'GetPath' in the verbatim HandleMessage 0x591fa0)
                canon_ret = any(Canon.get(q).exists for q in re.findall(r"[A-Za-z_]\w*(?:::[A-Za-z_]\w*)+", re.sub(r"\s+", "", o[3])))
                # (a canonical return type keeps serving unless this slice's own spelling returns one of its local stubs: the
                # verbatim bodies call the stub's members, fix pass 5, s00579e20 0x57a610 `ModelMgr* ModelManager()` vs the TU's
                # `IModelManager*`, 0x57a710 `MessageServer()->Post`: C2440 / C2039)
                mine_stub = bool(set(RS.IDENT.findall(pk[3])) & local_types)
                if same_function(pk, o) and re.sub(r"\s+", "", pk[3]) != re.sub(r"\s+", "", o[3]) and \
                        not pk[0].split("::")[-1].startswith("operator") and (not canon_ret or mine_stub) and \
                        (mine_stub or re.sub(r"\s+", "", pk[3]) in ("int", "void*", "unsigned", "unsignedint", "bool", "char*", "constchar*")):
                    # (also a scalar/void* return: s0051a350 `int GetPaintSystem();` vs another slice's `void* GetPaintSystem();`,
                    # 0x401080: the verbatim `int ps = GetPaintSystem();` failed C2440)
                    ns, _i = RS.unwrap_namespaces(text)
                    ret_clash.add((tuple(ns), short))
        for ns, n in sorted(ret_clash):
            if any(not getattr(c, "verbatim", False) and re.search(r"(?<![\w:.>])%s\s*\(" % re.escape(n), mask(c.out_body)) for c in fns):
                # a converted function of this slice calls it: the prototype it relies on stays (fix pass 5, s00584300 Init
                # 0x584300 lost `MessageServer()`, C3861, when the prototype was renamed for the verbatim functions)
                continue
            self.rename_stub(fns, ns, n, "the module TU declares %s with another return type" % n, verbatim_only=True)
        # a name that is a namespace on one side and a class on the other (fix pass 5): (a) this slice's class X where the TU
        # has `namespace X` (s00591fa0's `SP::Resource` class hid the `Resource::CreateNameFromKey` namespace of s0058e6d0's
        # verbatim body: C2039 in ANOTHER slice's function, the whole slice failed); (b) this slice's `namespace X` where the TU
        # has a global class X (s004035d0/s00404660/s004057b0/s00413cc0: `namespace Resource { struct ThreadedObject }` vs
        # s004024??'s `struct Resource`: C2757) -> this slice's namespace is renamed in its items and verbatim functions
        tu_ns = set(re.findall(r"\bnamespace\s+(\w+)\s*\{", mask(old)))
        cls_clash = set()
        for kind, text in self.items:
            ns, inner = RS.unwrap_namespaces(text)
            mi = RS.mask(inner).lstrip()
            if mi.startswith(("struct", "class", "union")) or re.match(r"template\s*<", mi):
                for n in RS.item_names("struct", inner):
                    if n in tu_ns:
                        cls_clash.add((tuple(ns), n))
        for ns, n in sorted(cls_clash):
            self.rename_stub(fns, ns, n, "the module TU has a namespace %s" % n,
                             verbatim_only=(n in self.class_map or "::".join(list(ns) + [n]) in self.class_map))
        my_ns = set()
        for kind, text in self.items:
            ns, _inner = RS.unwrap_namespaces(text)
            if ns:
                my_ns.add(ns[0])
        for c in fns:
            if getattr(c, "verbatim", False):
                my_ns |= set((getattr(c, "cls_ns", []) or [])[:1]) | set((getattr(c, "enc_ns", []) or [])[:1])
        for x in sorted(my_ns):
            if re.match(r"^(?:struct|class|union)\s+%s\b" % re.escape(x), have.get(x, "")) and x not in ("SP", "EA", "eastl", "std", "rw"):
                self.rename_namespace(fns, x)
        skip = {k for k, (kind, text) in enumerate(self.items) if kind == "extern" and any(
            n in self.externs for n in RS.item_names(kind, text))}
        # operator overloads are not renamed (below); one this TU already has with the same parameter types (another slice's
        # identical placement new, or <new>'s `operator new(size_t, void*)` once any slice includes <new>) is not emitted again
        # (C2084, s005c4500, fix pass 4)
        def _op_params(t):
            mt = RS.mask(RS.unwrap_namespaces(t)[1])
            # only an item that IS an operator new/delete (a call `operator delete(p)` inside a stub's body is not:
            # s0063d9e0's allocator stub was dropped as a duplicate)
            mo = re.match(r"^\s*(?:inline\s+|static\s+|extern\s+)*void\s*\*?\s*(?:__\w+\s+)?operator\s*(new|delete)\s*(\[\s*\])?\s*\(([^()]*)\)", mt)
            if not mo:
                return None
            ps = []
            for x in mo.group(3).split(","):
                toks = re.findall(r"[A-Za-z_]\w*|\*|&", x.replace("size_t", "unsigned int"))
                if len(toks) >= 2 and re.match(r"^[A-Za-z_]\w*$", toks[-1]) and toks[-1] not in PARAM_KW:
                    toks = toks[:-1]
                if toks:
                    # (`unsigned` alone is `unsigned int`: s0074c260's `operator new(unsigned, void* p)` was not seen as the TU's
                    # placement new, C2084, fix pass 5)
                    ps.append(re.sub(r"^unsigned$", "U", "".join(toks).replace("unsignedint", "U")))
            return (mo.group(1), bool(mo.group(2)), tuple(ps), "{" in mt)
        have_ops = {_op_params(t) for _k, t in old_items if _op_params(t)}
        tu_inc_new = any(k == "include" and re.search(r"<new>", t) for k, t in old_items) or \
            any(k == "include" and re.search(r"<new>", t) for k, t in self.items)
        drop = []
        for k, (kind, text) in enumerate(self.items):
            op = _op_params(text)
            if not op:
                continue
            # only a definition is a duplicate (C2084); a repeated prototype is legal and the TU's own may sit in a LATER
            # slice's block (fix pass 5, s0057bfb0: its `operator new[]` prototype was dropped because s005802f0's block,
            # 800 lines further down, declares it; the inline operator new and allocator above failed C2661)
            if (op in have_ops and op[3]) or (tu_inc_new and op[3] and op[0] == "new" and not op[1] and op[2] == ("U", "void*")):
                drop.append(k)
        if drop:
            self.items = [it for k, it in enumerate(self.items) if k not in drop]
            self.notes.append(("dedup-operator", "%d operator new/delete item(s) the TU already has" % len(drop)))
        done = set()
        for _round in range(8):
            texts = [c.defline + "\n" + c.out_body for c in fns]
            clash = []
            for kind, text in RS.needed_items(self.items, texts, skip):
                ns, inner0 = RS.unwrap_namespaces(text)
                mi0 = RS.mask(inner0).strip()
                if kind in ("other", "extern") and mi0.endswith(")") is False and mi0.endswith(";") and "(" in mi0 and "{" not in mi0 \
                        and not mi0.startswith(("typedef", "extern \"C\" long")) and "=" not in mi0:
                    continue      # a function prototype that differs from the TU's is an overload (or a redeclaration), not a stub clash
                if RS.is_template_member_def(text) or self.is_stub_member_def(text):
                    # an out-of-class member definition of a class template is not a stub of that member's name: renaming the
                    # member renamed the in-class declaration but not `this->DoAssignFromIterator(..)` calls (fix pass 5,
                    # s007cb590 vs s007ca950's identical-named definitions: C2039, five functions dropped); when its class
                    # stub is renamed, the qualifier follows
                    continue
                for n in RS.item_names(kind, text):
                    if n.startswith("operator"):
                        # operators overload (s004680c0's inline placement `operator new(unsigned, void*)` next to s00466320's
                        # 6-argument one): a different parameter list is not a clash, and an operator cannot be renamed
                        # (fix pass 4: the placement new was dropped, C2661 in Vec::push_back)
                        continue
                    if re.match(r"^(?:struct|class|union)\s+%s\s*;$" % re.escape(n), mi0) and \
                            re.match(r"^(?:struct|class|union)\s+%s\b" % re.escape(n), have.get(n, "")):
                        # a forward declaration is compatible with the TU's class of that name (fix pass 5, s005598b0
                        # `struct ICheatManager;` was renamed against s005580e0's definition, which made the TU's
                        # `ICheatManager* CheatManager();` return another type: C2440 in the verbatim Init 0x5598b0)
                        continue
                    if n in have and have[n] != RS.norm(self.item_view(kind, text, fns)) and (tuple(ns), n) not in done:
                        clash.append((tuple(ns), n))
            if not clash:
                break
            for ns, n in clash:
                done.add((ns, n))
                # a stub the slice maps to a canonical class: the converted functions spell the canonical class and keep it
                # (fix pass 5, s007ca950 0x7cb390 SP::cOption::~cOption was renamed to the stub, the row found no symbol)
                mapped = n in self.class_map or "::".join(list(ns) + [n]) in self.class_map
                self.rename_stub(fns, ns, n, "the module TU already defines %s differently" % n, verbatim_only=mapped)

    def include_closure(self):
        """Headers (relative to src/game/include) the TU includes for its converted functions, and everything they include."""
        inc_closure = set()
        todo = [h for h in self.collect_includes()]
        while todo:
            h = todo.pop()
            if h in inc_closure:
                continue
            inc_closure.add(h)
            try:
                for mm in re.finditer(r'^#include "([^"]+)"', open(os.path.join(INC, h), encoding="utf-8").read(), re.M):
                    todo.append(mm.group(1))
            except OSError:
                pass
        return inc_closure

    def rename_shadowed_stubs(self, fns):
        """A verbatim function that uses the slice's own stub of a class which a header the TU includes anyway defines (with
        other members: the stub has the slice's `GetText()`, `const char** MainArguments(..)`) keeps its stub: the stub is
        renamed `Name_sNNNN_NNNN` for the verbatim functions, the canonical class stays what the converted ones use."""
        vtexts = [c.defline + "\n" + c.out_body for c in fns if getattr(c, "verbatim", False)]
        if not vtexts:
            return
        inc = self.include_closure()
        done = set()
        # namespaces the verbatim functions are defined in (their class's or an enclosing `namespace X {`): a GLOBAL stub
        # `struct cSPPaletteUI` is hidden there by a canonical `SP::cSPPaletteUI` (unqualified lookup inside a method of
        # SP::X finds SP:: first).  Fix pass 5, s00575270 0x575810 TestCondition: C2039 'IsPaintByNumber' is not a member of
        # 'SP::cSPPaletteUI' in the demoted verbatim body; the slice's stub is renamed for the verbatim functions instead.
        scopes = set()
        for c in fns:
            if getattr(c, "verbatim", False):
                for nsl in (list(getattr(c, "cls_ns", []) or []), list(getattr(c, "enc_ns", []) or [])):
                    for k in range(1, len(nsl) + 1):
                        scopes.add("::".join(nsl[:k]))
        needed = RS.needed_items(self.items, vtexts)
        # ... and the namespaces of the kept namespace-wrapped items (s00587a20 0x587a20 Deactivate: the slice's
        # `namespace EA { namespace Messaging { void RemoveHandler(IMessageServer*, IHandler*, ..); } }` names its global stub
        # IHandler, which there means the canonical EA::Messaging::IHandler: C2665 in the stub's inline Unregister)
        for _kind, text in needed:
            nsl = RS.unwrap_namespaces(text)[0]
            for k in range(1, len(nsl) + 1):
                scopes.add("::".join(nsl[:k]))
        for kind, text in needed:
            hdr = self.canonical_item_header(text)
            if not hdr and scopes:
                ns0, inner0 = RS.unwrap_namespaces(text)
                if not ns0 and RS.mask(inner0).lstrip().startswith(("struct", "class", "union")):
                    nm0 = RS.item_names("struct", inner0)
                    if len(nm0) == 1:
                        for sc in sorted(scopes):
                            p0 = H.include_path(sc + "::" + nm0[0])
                            if os.path.exists(os.path.join(INC, p0)) and re.search(
                                    r"\b(?:struct|class|union)\s+%s\b" % re.escape(nm0[0]),
                                    open(os.path.join(INC, p0), encoding="utf-8", errors="replace").read()):
                                hdr = p0
                                break
            if not hdr:
                # a namespaced stub the slice hoists to global scope (`namespace SP { struct cSPColorRGB {..}; }` +
                # `using SP::cSPColorRGB;`) collides with a canonical GLOBAL class of that name (cSPColorRGB.h): C2874,
                # mig9 s005a4250/s005a51c0 (SPEditorColorPicker, 21 functions).  The stub is renamed; so is the using.
                ns1, inner1 = RS.unwrap_namespaces(text)
                if ns1 and RS.mask(inner1).lstrip().startswith(("struct", "class", "union")):
                    nm1 = RS.item_names("struct", inner1)
                    if len(nm1) == 1 and re.search(r"(?m)^\s*using\s+(?:::)?%s\s*;" % re.escape("::".join(ns1 + [nm1[0]])),
                                                   "\n".join(t for _k, t in self.items)):
                        p1 = H.include_path(nm1[0])
                        if os.path.exists(os.path.join(INC, p1)) and re.search(
                                r"\b(?:struct|class|union)\s+%s\b" % re.escape(nm1[0]),
                                open(os.path.join(INC, p1), encoding="utf-8", errors="replace").read()):
                            hdr = p1
            # renamed whenever the class HAS a canonical header, not only when this run includes it: a later slice of the module
            # that converts a function includes the header, and the earlier slice's kept block then redefines the class
            # (s0083c900's eastl::allocator / string8 stubs vs s0083d3d0's eastl/string.h: C2011 in another slice's block, which
            # no rename of the later slice can fix; round 2 hand-edited Expression.cpp)
            if hdr:
                ns, _inner = RS.unwrap_namespaces(text)
                for n in RS.item_names(kind, text):
                    if (tuple(ns), n) not in done:
                        done.add((tuple(ns), n))
                        self.rename_stub(fns, ns, n, "a header the TU includes defines %s; the verbatim functions keep the slice's stub" % "::".join(list(ns) + [n]),
                                         verbatim_only=True)

    def is_stub_member_def(self, text):
        """`bool F_ec20::f(int* io, unsigned index) { .. }`: an out-of-class definition of a member of one of the slice's
        stub classes names no stub of its own (fix pass 6 C13: item_names gave `f`, which clashed with another slice's `f`;
        the in-class declarations were renamed to f_s0069_e3a0 and the definitions not: C2039, s0069e3a0 0x69ec20/0x69f940;
        SwatchStrategies' clash loop).  When the class stub itself is renamed, the qualifier follows."""
        _ns, inner = RS.unwrap_namespaces(text)
        mi = RS.mask(inner)
        k = mi.find("{")
        if k < 0:
            return False
        mm = re.search(r"(?<![\w:])([A-Za-z_]\w*)\s*::\s*~?\s*(?:operator\s*\S+?|[A-Za-z_]\w*)\s*\(", mi[:k])
        if not mm:
            return False
        if not hasattr(self, "_stub_struct_names"):
            self._stub_struct_names = {n for kind, t in self.items if kind == "struct" for n in RS.item_names(kind, t)} | \
                {n for kind, t in self.items if kind == "other" and RS.mask(RS.unwrap_namespaces(t)[1]).lstrip().startswith(("struct", "class", "union"))
                 for n in RS.item_names(kind, t)}
        return mm.group(1) in self._stub_struct_names

    DUMMY_RE = re.compile(r"^\s*(?:extern\s+)?void\s+(?:__\w+\s+)?([A-Za-z_]\w*)\s*\(\s*\.\.\.\s*\)\s*;\s*//\s*(?:@\s*)?0x[0-9a-fA-F]+")

    def drop_annotation_dummies(self, tu):
        """`void GetMaterialManager(...); // 0x0067dd70`: an equivalence-checker address annotation, not a declaration of the
        function.  Where the slice or the TU declares the function for real it overloads that one, and the verbatim calls
        are ambiguous (mig9 s00a0f350 0xa0f350 C2668; also GetSystemAT, GetStyleManager, SetCreatureAnimManager drops).
        The real declaration carries the address comment the resolver needs, so the dummy is dropped."""
        old = mask(open(tu).read()) if os.path.exists(tu) else ""
        texts = [RS.mask(RS.unwrap_namespaces(t)[1]) for _k, t in self.items]
        keep = []
        for (kind, text), mt in zip(self.items, texts):
            md = self.DUMMY_RE.match(RS.unwrap_namespaces(text)[1])
            if md:
                n = md.group(1)
                real = re.compile(r"(?<![\w:.>])%s\s*\((?!\s*\.\.\.\s*\))" % re.escape(n))
                if any(real.search(t2) for t2 in texts if t2 is not mt) or real.search(old):
                    self.notes.append(("annotation-dummy", "%s(...) dropped: the slice or the TU declares %s" % (n, n)))
                    continue
            keep.append((kind, text))
        self.items = keep

    INST_RE = re.compile(r"^\s*template\s+(?!<)[^;{}]*?\b([A-Za-z_]\w*)\s*<[^;{}]*>\s*\([^;{}]*\)\s*;")

    def drop_orphan_instantiations(self, fns, tu):
        """`template cSPPaletteItem** find<..>(..);` after the slice's own `template <..> It find(..) {..}`: the statement goes to
        the preamble (trailing lines of a chunk), but when the template's chunk is not landed here (another object, or none)
        nothing defines `find` in the TU: C2143 (mig9 s005c0c00 0x5c1cc0, SPEditorPaintLikeThis, 20 functions held).  An
        explicit function-template instantiation whose template the SLICE defines is dropped unless a landed function or the
        TU defines that template; instantiations of header templates are kept."""
        old = mask(open(tu).read()) if os.path.exists(tu) else ""
        src = mask(self.src_text)
        landed = "\n".join(mask(c.defline) for c in fns)
        keep = []
        for kind, text in self.items:
            mi = self.INST_RE.match(mask(RS.unwrap_namespaces(text)[1]))
            if mi:
                n = mi.group(1)
                tdef = re.compile(r"template\s*<[^;{}]*>\s*[^;{}()]*?\b%s\s*\([^;{}]*\)\s*(?:const\s*)?\{" % re.escape(n))
                if tdef.search(src) and not tdef.search(old) and not re.search(r"\b%s\s*\(" % re.escape(n), landed):
                    self.notes.append(("orphan-instantiation", "explicit instantiation of %s dropped: its template is not landed here" % n))
                    continue
            keep.append((kind, text))
        self.items = keep

    def rename_namespace(self, fns, old_n):
        """This slice's top-level `namespace X` -> `X_sNNNN_NNNN` in its items and verbatim functions (the module TU has a
        global class X).  Converted functions spell canonical names and are left alone."""
        new_n = old_n + self.rsfx
        pat_ns = re.compile(r"\bnamespace(\s+)%s\b" % re.escape(old_n))
        pat_q = re.compile(r"(?<![\w.>:])%s(\s*::)" % re.escape(old_n))
        def ren(t):
            m = mask(t)
            out, last = [], 0
            for mm in sorted(list(pat_ns.finditer(m)) + list(pat_q.finditer(m)), key=lambda x: x.start()):
                k = mm.group(0).rfind(old_n)
                out.append(t[last:mm.start() + k]); out.append(new_n)
                last = mm.start() + k + len(old_n)
            out.append(t[last:])
            return "".join(out)
        self.items = [(k, ren(t)) for k, t in self.items]
        for c in fns:
            if not getattr(c, "verbatim", False):
                continue
            c.defline, c.out_body = ren(c.defline), ren(c.out_body)
            for attr in ("cls_ns", "enc_ns"):
                v = getattr(c, attr, None)
                if v and v[0] == old_n:
                    setattr(c, attr, [new_n] + list(v[1:]))
        self.notes.append(("renamed-namespace", "%s -> %s (the module TU has a class %s)" % (old_n, new_n, old_n)))

    def rename_stub(self, fns, ns, old_n, why, verbatim_only=False):
        """Rename a local stub item (and every use of it in this slice's items and function texts) to `Name_<slice>`.
        verbatim_only: the converted functions spell the canonical class (`EA::ArgScript::cArguments`), the rename is
        for the slice's own stub that only the verbatim functions use."""
        # the slice's 8 hex digits are split: difftest/resolve.py reads any 6-8 hex digit run in a symbol name as the
        # address of the function ("hex-name": `Mutex_008d91e0` made every Mutex_008d91e0 method call 0x8d91e0)
        new_n = old_n + self.rsfx
        if not hasattr(self, "renamed"):
            self.renamed = []
        self.renamed.append((tuple(ns), old_n, new_n))
        # a constructor/destructor definition `Old::Old(...)` / `Old::~Old()`: rename_word leaves the name after `::` alone
        # (also `New<K, T>::Old(` of a class template: fix pass 5, s005634e0 hash_map_s0056_34e0<K, T>::hash_map, C2063)
        ctor = lambda t: re.sub(r"\b%s(\s*<(?:[^<>]|<[^<>]*>)*>)?\s*::\s*(~?)\s*%s\b" % (re.escape(new_n), re.escape(old_n)),
                                lambda mm: "%s%s::%s%s" % (new_n, mm.group(1) or "", mm.group(2), new_n), t)
        def _ren_item(t):
            ins = RS.unwrap_namespaces(t)[0]
            if ns and ins and list(ins) != list(ns) and old_n in RS.item_names("struct", RS.unwrap_namespaces(t)[1]):
                return RS.rename_word(t, old_n, new_n, ns, qualified_only=True)
            return ctor(RS.rename_word(t, old_n, new_n, ns))
        self.items = [(k, _ren_item(t)) for k, t in self.items]
        for c in fns:
            if verbatim_only and not getattr(c, "verbatim", False):
                continue
            c.defline = ctor(RS.rename_word(c.defline, old_n, new_n, ns))
            c.out_body = ctor(RS.rename_word(c.out_body, old_n, new_n, ns))
            if getattr(c, "cls", None) == old_n:
                c.cls = new_n
        self.notes.append(("renamed-stub", "%s%s -> %s (%s)" % ("::".join(ns) + "::" if ns else "", old_n, new_n, why)))

    @staticmethod
    def module_flags(module, flags):
        """tools/migrate/module_flags.json {"dir/Obj.obj": {"drop": [flag..], "add": [flag..], "evidence"}}: the object's own
        compile flags where its slices disagree with retail (fix pass 4: EASharedLibrary.obj has no EH frames, so /EHsc from
        the slice rows is dropped)."""
        try:
            o = json.load(open(W("tools", "migrate", "module_flags.json"))).get(module)
        except (OSError, ValueError):
            o = None
        if not o:
            return list(flags)
        out = [f for f in flags if f not in o.get("drop", [])]
        for f in o.get("add", []):
            if f not in out:
                out.append(f)
        return out

    def write_bookkeeping(self, module, d, stem, fns):
        sdir = os.path.join(SLICES, self.sid)
        outdir = W("src", "game", d, stem)
        os.makedirs(outdir, exist_ok=True)
        vas = {c.va for c in fns}
        src_col = "../src/game/%s/%s.cpp" % (d, stem)
        # manifest rows come from the slice manifest; the symbol becomes the decorated name of the new object
        rows = []
        # a slice may have no manifest.txt at all (s00ed74f0 ships only nonmatching.txt: the apply crashed with
        # FileNotFoundError, round 3): no byte-exact rows, flags from nonmatching measurement
        mlines = open(os.path.join(sdir, "manifest.txt")).read().split("\n") if os.path.exists(os.path.join(sdir, "manifest.txt")) else []
        for line in mlines:
            p = line.split("#", 1)[0].split()
            if len(p) >= 3 and row_va(p[2]) in vas:
                rows.append((row_va(p[2]), p[3:]))
        mf = []
        # the flags the slice's functions were verified with (rows of one slice share them); nonmatching rows have no
        # flags column of their own, so they are measured and promoted with these
        allrows = [p[3:] for p in (l.split("#", 1)[0].split() for l in mlines) if len(p) >= 4]
        for fl0 in allrows:
            if fl0:
                self.slice_flags = self.module_flags(module, [f for f in fl0 if not f.startswith("/I")])
                break
        # a function this run moves that the slice's own bookkeeping has no row for (s006907e0 lands cJob::AddRef 0x68f950,
        # whose byte-exact row is in s0068f670's manifest: the batch gave the VA to the later slice): the row of the slice
        # that has one (verify_exact then checks the claim)
        norow = vas - {r[0] for r in rows}
        for fname in ("nonmatching.txt", "partial.txt"):
            p2 = os.path.join(sdir, fname)
            if os.path.exists(p2):
                norow -= {row_va(l.split()[0]) for l in read_rows(p2)}
        if norow:
            import glob as _glob
            for mp2 in sorted(_glob.glob(os.path.join(SLICES, "*", "manifest.txt"))):
                if os.path.dirname(mp2) == sdir:
                    continue
                for line in open(mp2):
                    p = line.split("#", 1)[0].split()
                    if len(p) >= 3 and row_va(p[2]) in norow:
                        rows.append((row_va(p[2]), p[3:]))
                        norow.discard(row_va(p[2]))
                        self.notes.append(("manifest", "0x%08x: row taken from %s (this slice has none)" % (
                            row_va(p[2]), os.path.basename(os.path.dirname(mp2)))))
                if not norow:
                    break
        for va, flags in sorted(rows):
            sym = self.symbols.get(va)
            if not sym:
                self.notes.append(("manifest", "no decorated symbol for 0x%08x" % va))
                continue
            # a manifest row without flags is compiled by run_all with ITS defaults: say so explicitly in the new row
            fl = self.module_flags(module, [f for f in (flags or RUN_ALL_DEFAULT_FLAGS) if not f.startswith("/I")]) + ["/Isrc/game/include"]
            mf.append("%s  %s  %08x  %s" % (src_col, sym, va, " ".join(fl)))
        self.merge_rows(os.path.join(outdir, "manifest.txt"), "# source  symbol  va  flags", mf, key=lambda l: int(l.split()[2], 16))
        for fname in ("nonmatching.txt", "partial.txt"):
            p = os.path.join(sdir, fname)
            if not os.path.exists(p):
                continue
            rows2 = [l for l in read_rows(p) if row_va(l.split()[0]) in vas]
            head = next((l.rstrip("\n") for l in open(p) if l.startswith("#")), "# va  diff-bytes  reason")
            self.merge_rows(os.path.join(outdir, fname), head, rows2, key=lambda l: int(l.split()[0], 16))
        self.prune_rows(d, stem)

    def prune_rows(self, d, stem):
        """Drop every row of the module's manifest/nonmatching/partial whose function has no '// @ 0xVA' marker in the
        module TU: rows of this slice's functions that an earlier run moved and this one holds back, and functions a
        session left in the slice (manual leave_in_slice / exclude, a header request).  The slice keeps those rows; the
        module files describe only what the TU defines (report_s009013e0.md: three hand-added partial rows for functions
        held back with a header request)."""
        tu = W("src", "game", d, stem + ".cpp")
        if not os.path.exists(tu):
            return
        marks = {int(m, 16) for m in re.findall(r"^// @ 0x([0-9a-fA-F]+)", open(tu).read(), re.M)}
        outdir = W("src", "game", d, stem)
        # a function has one row: byte-exact (manifest) wins over equivalent (nonmatching) over partial
        exact = set()
        mp = os.path.join(outdir, "manifest.txt")
        if os.path.exists(mp):
            exact = {row_va(l.split()[2]) for l in read_rows(mp) if len(l.split()) > 2}
        equiv = set()
        np_ = os.path.join(outdir, "nonmatching.txt")
        if os.path.exists(np_):
            equiv = {row_va(l.split()[0]) for l in read_rows(np_)}
        for fname, col, better in (("manifest.txt", 2, set()), ("nonmatching.txt", 0, exact), ("partial.txt", 0, exact | equiv)):
            p = os.path.join(outdir, fname)
            if not os.path.exists(p):
                continue
            kept, dropped = [], 0
            for l in open(p).read().split("\n"):
                f = l.split("#", 1)[0].split()
                if f and len(f) > col and not l.lstrip().startswith("#") and (row_va(f[col]) not in marks or row_va(f[col]) in better):
                    dropped += 1
                    continue
                kept.append(l)
            if dropped:
                open(p, "w").write("\n".join(kept))
                self.notes.append(("pruned", "%d row(s) without a function in %s.cpp (or with a better row) removed from %s/%s" % (dropped, stem, stem, fname)))

    def row_flags(self, va):
        """Flags of a nonmatching/partial row of this slice as the difftest harness picks them (explicit note in the
        reason, manifest flags, source comment, defaults), plus the include root of the new tree."""
        try:
            sys.path.insert(0, W("tools", "difftest"))
            import slice as S
            fl, _how = S.choose_flags(self.sid, va)
        except Exception as e:              # noqa: BLE001
            self.notes.append(("flags", "choose_flags failed for 0x%08x: %s" % (va, e)))
            return None
        return " ".join([f for f in fl if not f.startswith("/I")] + ["/Isrc/game/include"])

    def measure_rows(self):
        """Byte-diff counts of the nonmatching/partial rows against the new object (run_all on a scratch manifest), so
        the module's nonmatching.txt/partial.txt carry current numbers; a row that now matches is reported."""
        py = W(".venv", "bin", "python")
        py = py if os.path.exists(py) else sys.executable
        res = {}
        for module in {c.module for c in self.fns}:
            d, obj = os.path.split(module)
            stem = obj[:-4]
            outdir = W("src", "game", d, stem)
            rows = []
            for fname in ("nonmatching.txt",):       # partial.txt rows are carried over unchanged
                p = os.path.join(outdir, fname)
                if os.path.exists(p):
                    for line in open(p):
                        if line.strip() and not line.startswith("#"):
                            va = int(line.split()[0], 16)
                            if va in self.symbols:
                                rows.append((va, self.symbols[va]))
            if not rows:
                continue
            flags = " ".join(getattr(self, "slice_flags", None) or ["/O2", "/MD", "/Gy", "/TP", "/GS-", "/arch:SSE"]) + " /Isrc/game/include"
            mp = os.path.join(self.scratch, "measure_%s.txt" % stem)
            # each row with the flags the difftest harness would use for it (tools/difftest/slice.choose_flags)
            open(mp, "w").write("".join("../src/game/%s/%s.cpp  %s  %08x  %s\n" % (d, stem, sym, va, self.row_flags(va) or flags)
                                        for va, sym in rows))
            rout = self.run_all_locked(mp)
            if "COMPILE FAIL" in rout:
                self.notes.append(("measure", "run_all did not run: " + rout[-200:].strip()))
                continue
            for line in rout.splitlines():
                mm = re.match(r"^(MATCH|DIFF|FAIL)\s+\S+\s+([0-9a-f]{8})\s*(?:DIFF (\d+) bytes)?", line)
                if mm:
                    res[int(mm.group(2), 16)] = "MATCH" if mm.group(1) == "MATCH" else (mm.group(3) or "?")
            for fname in ("nonmatching.txt",):
                p = os.path.join(outdir, fname)
                if not os.path.exists(p):
                    continue
                out = []
                for line in open(p).read().split("\n"):
                    parts = line.split(None, 2)
                    if line.strip() and not line.startswith("#") and len(parts) >= 2 and int(parts[0], 16) in res:
                        v = res[int(parts[0], 16)]
                        if v == "MATCH":
                            # byte-exact in the module TU now (the slice's row was an equivalent one): promote it
                            va = int(parts[0], 16)
                            self.merge_rows(os.path.join(outdir, "manifest.txt"), "# source  symbol  va  flags",
                                            ["../src/game/%s/%s.cpp  %s  %08x  %s" % (d, stem, self.symbols[va], va, self.row_flags(va) or flags)],
                                            key=lambda l: int(l.split()[2], 16))
                            self.notes.append(("now-exact", "0x%s now matches byte for byte: row moved from nonmatching.txt to manifest.txt (%s)" % (
                                parts[0], parts[2][:60] if len(parts) > 2 else "")))
                            self.stats["promoted_to_exact"] += 1
                            continue
                        line = "%s %s %s" % (parts[0], v, parts[2] if len(parts) > 2 else "")
                    out.append(line)
                open(p, "w").write("\n".join(out))
        return res

    @staticmethod
    def merge_rows(path, head, rows, key):
        have = {}
        if os.path.exists(path):
            for l in read_rows(path):
                have[key(l)] = l
        for r in rows:
            have[key(r)] = r
        open(path, "w").write(head + "\n" + "\n".join(have[k] for k in sorted(have)) + ("\n" if have else ""))

    def compile_symbols(self):
        """Compile the written TU into the scratch dir and read the decorated name of each function."""
        sys.path.insert(0, W("tools", "difftest"))
        from coff import Coff
        self.symbols = {}
        for module in {c.module for c in self.fns}:
            d, obj = os.path.split(module)
            tu = W("src", "game", d, obj[:-4] + ".cpp")
            ofile = os.path.join(self.scratch, "tu_%s.obj" % obj[:-4])
            w = lambda p: "Z:" + p.replace("/", "\\")
            if os.path.exists(ofile):
                os.remove(ofile)
            r = subprocess.run([W("tools", "matching", "cl.sh"), "/nologo", "/c", "/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-", "/arch:SSE",
                                "/I" + w(INC), "/Fo" + w(ofile), w(tu)], capture_output=True, text=True)
            log = r.stdout + r.stderr
            self.compile_log = log
            if not os.path.exists(ofile) or re.search(r"\berror C\d+", log):
                return log or "no object file produced"
            allf = Coff(ofile).functions()
            self.obj_names = set(allf)
            funcs = sorted((sym.secno, sym.value, n) for n, sym in allf.items() if n.startswith("?"))
            mine = [c for c in self.fns if c.module == module]
            und = self.data.und.many([n for _a, _b, n in funcs])
            used = set()
            slice_syms = RS.slice_rows(self.sid)[1]
            for c in sorted(mine, key=lambda x: x.va):
                if getattr(c, "verbatim", False):
                    # the slice's own spelling; its decorated manifest symbol when the object defines it (a renamed stub
                    # type changes the decorated name, then the demangled name decides)
                    want = ((c.cls + "::") if c.cls else "") + str(c.name)
                    # the slice's manifest symbol, also a C-linkage one (`_FUN_0068a2e0`, s00689ee0: the `?`-only list gave the
                    # byte-exact 0x68a2e0 no row)
                    # (not when the function's class was renamed for this TU and the slice symbol names the old class: that
                    # symbol is another slice's class of the same name, fix pass 5, s00576140 0x576b40 `??0BoundingBox@@QAE@XZ`
                    # bound s00573520's implicit BoundingBox constructor, DIFF 3 bytes)
                    ren = re.search(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", c.cls or "")
                    if slice_syms.get(c.va) in self.obj_names and slice_syms[c.va] not in used and \
                            (not ren or c.cls in slice_syms[c.va]):
                        self.symbols[c.va] = slice_syms[c.va]
                        used.add(slice_syms[c.va])
                        continue
                    # the class may have been renamed for this TU (`INetFileCache_s0094_7d50`) and the function may sit in the
                    # slice's namespace (`EA::Internet::`): match the class with an optional rename suffix
                    tm = re.search(r">\s*::\s*(operator\s*(?:\[\s*\]|\(\s*\)|[^\s\w(]+)|~?\w+)\s*\(", mask(c.sig_text or ""))
                    if getattr(c, "inst", False):
                        # an explicit instantiation: the member of a template class (`eastl::rbtree_s0059_b4b0<..>::erase(`)
                        # (a template renamed for this TU keeps its `_sNNNN_NNNN` suffix; template arguments may hold
                        # function-pointer types with parentheses: s0074c260 quick_sort_impl<cOccluder*, int, OccCmp>)
                        pat = re.compile(r"::%s(?:_s[0-9a-f]{4}_[0-9a-f]{4})?(?:<.*>)?\(" % re.escape(str(c.name)))
                    elif not c.cls and tm:
                        # a template member defined out of class (s0059c4c0 0x59c740 `T& eastl::map<Key, T>::operator[](..)`):
                        # the instantiation's demangled name (fix pass 4: the row had no symbol, equiv bound another function)
                        pat = re.compile(r">::%s\(" % re.escape(re.sub(r"\s+", "", tm.group(1))))
                        ms = mask(c.sig_text)
                        b0 = ms.find("(", tm.end() - 1)
                        e0 = match_close(ms, b0)
                        inner = c.sig_text[b0 + 1:e0].strip()
                        c.params = split_params(inner) if inner and inner != "void" else []
                    elif c.cls:
                        base = re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", c.cls)
                        nbase = re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", str(c.name))
                        npat = re.escape(nbase) + ("(?:_s[0-9a-f]{4}_[0-9a-f]{4})?" if nbase.lstrip("~") == base else "")
                        pat = re.compile(r"(?:^|[\s:*&])%s(?:_s[0-9a-f]{4}_[0-9a-f]{4})?::%s\(" % (re.escape(base), npat))
                    else:
                        pat = re.compile(r"(?:^|[\s:*&])%s\(" % re.escape(want))
                        # an out-of-class member definition with no c.cls (`void cEditorCheat::Execute(..)`): the qualifier
                        # of the definition is required, else the bare name binds another class's method (fix pass 5:
                        # s0058d430 0x58d430 bound cEditorAddDNACheat::Execute, s007ca950 0x7cae30..0x7cb270 bound the
                        # Execute of the neighbouring command class; /O2 had dropped the unreferenced anonymous-namespace
                        # definition from the binding object)
                        qm = re.search(r"(\w+)\s*(?:<[^()]*>)?\s*::\s*%s\s*\(" % re.escape(want), mask(c.sig_text or ""))
                        # (only a qualifier that is a slice struct: a typedef qualifier, `PropFixV::resize`, demangles to
                        # the template it names and keeps the bare-name match)
                        q = re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", qm.group(1)) if qm else None
                        if q and (q in self.structs or qm.group(1) in self.structs):
                            pat = re.compile(r"(?:^|[\s:*&])%s(?:_s[0-9a-f]{4}_[0-9a-f]{4})?::%s\(" % (re.escape(q), re.escape(want)))
                    cands = [(si, off, n) for si, off, n in funcs
                             if n not in used and pat.search((und.get(n) or "").replace("class ", "").replace("struct ", ""))
                             and (getattr(c, "inst", False) or self.demangled_arity(und.get(n)) in (None, len(c.params)))]
                    own = getattr(c, "owner", None) if getattr(c, "inst", False) else None
                    if own and len(cands) > 1:
                        # an instantiation's owner (`copy_backward_impl` vs `copy_impl` for two `do_copy`s) is preferred, not
                        # required: a typedef owner (`PropVec::insert`) demangles to the class it names
                        po = re.compile(r"\b%s(?:_s[0-9a-f]{4}_[0-9a-f]{4})?(?:<.*?>)?::%s" % (re.escape(own), re.escape(str(c.name))))
                        cands = [x for x in cands if po.search(und.get(x[2]) or "")] or cands
                    if ren and len(cands) > 1:
                        # the renamed class first (s00576140 0x576b40: `BoundingBox::BoundingBox` of s00573520 came first)
                        own = [x for x in cands if re.search(r"(?:^|[\s:*&])%s::" % re.escape(c.cls),
                                                             (und.get(x[2]) or "").replace("class ", "").replace("struct ", ""))]
                        cands = own or cands
                else:
                    want = "%s::%s" % (self.qual_of(c), c.decl.name)
                    cands = [(si, off, n) for si, off, n in funcs
                             if n not in used and (" " + (und.get(n) or "").replace("class ", "").replace("struct ", "")).find(" " + want + "(") >= 0]
                    # overloads (GetProperty(key) const / GetProperty(key, Variant**) / ... ): the parameter list and constness of
                    # the canonical declaration pick the object symbol, not only the name
                    exact = [x for x in cands if self.sig_matches(und.get(x[2]), c.decl)]
                    if exact:
                        cands = exact
                    else:
                        # no spelling agrees (the demangler prints `unsigned char *` for `uchar const *`...): the parameter
                        # count still tells overloads apart (ShouldRecordBeCompressed(Key const &, uint) vs the 5-parameter one)
                        byarity = [x for x in cands if self.demangled_arity(und.get(x[2])) == len(c.decl.params)]
                        if byarity:
                            cands = byarity
                if cands:
                    self.symbols[c.va] = cands[0][2]
                    used.add(cands[0][2])
                else:
                    self.notes.append(("symbols", "no object symbol for 0x%08x %s" % (c.va, want)))
        return ""

    @staticmethod
    def sig_matches(dm, decl):
        """Does the demangled signature `dm` have the parameter list and constness of the canonical declaration?"""
        if not dm or "(" not in dm or decl is None:
            return False
        m = mask(dm)
        b = m.index("(")
        e = match_close(m, b)
        def norm(t):
            t = re.sub(r"\b(struct|class|enum|union)\b", "", t)
            return re.sub(r"\s+", "", t)
        got = [norm(x) for x in (split_params(dm[b + 1:e].strip()) if dm[b + 1:e].strip() not in ("", "void") else [])]
        want = [norm(x) for x in decl.params]
        return got == want and (dm[e + 1:].strip().startswith("const")) == bool(getattr(decl, "const", False))

    @staticmethod
    def demangled_arity(dm):
        """Number of parameters in a demangled signature (None when it cannot be told)."""
        if not dm or "(" not in dm:
            return None
        # `anonymous namespace'::X: the backtick-quote pair is not a character literal (mask blanked the rest of the
        # signature: ValueError on s00538e90's file-local command classes, fix pass 3)
        m = mask(re.sub(r"`[^`']*'", lambda mm: "_" * len(mm.group(0)), dm))
        # the call operator's own `()` is part of the name (`Manager::ChangeNotificationInfoCompare::operator()(..)`, s008de020
        # 0x8de1e0: arity 0, the row lost its symbol)
        oc = m.find("operator()")
        b = m.index("(", oc + len("operator()")) if oc >= 0 and "(" in m[oc + len("operator()"):] else m.index("(")
        e = match_close(m, b)
        inner = dm[b + 1:e].strip()
        if inner in ("", "void"):
            return 0
        return len(split_params(inner))

    def callee_names(self):
        """Callees the slice declares with a retail address comment but pdb_names.json does not name (PFHoleTable::Free
        0x8dc000, the record constructors): the dev public of the mapped canonical method gives the decorated name the
        new object references, so the difftest resolver can bind it.  -> [(va, mangled, qualified name)]"""
        D = self.data
        if not hasattr(D, "_methods_by_class"):
            D._methods_by_class = collections.defaultdict(list)
            for dva, mangled in D.pub.items():
                f = D.dev_fn.get(dva)
                if f:
                    cname, _m = H.split_qual(f["name"])
                    D._methods_by_class[cname].append((dva, mangled, f))
        out = []
        chunk_vas = {c.va for c in self.chunks}
        for sname, canon in sorted(self.class_map.items()):
            st = self.structs.get(sname)
            if not st or sname in {c.cls for c in self.chunks}:
                continue
            ms = D._methods_by_class.get(canon, [])
            dm = D.und.many([m for _d, m, _f in ms])
            for m in st.methods:
                va = m["va"]
                if not va or va in chunk_vas:
                    continue
                if (self.pdb_names.get("%08x" % va) or {}).get("name") and not m["name"].startswith("Init"):
                    continue          # constructors are named in pdb_names by class only: the overload needs the decorated name
                if m["ctor"] is False and m["name"] in self.method_map.get(sname, {}):
                    want_name = self.method_map[sname][m["name"]].name
                    is_ctor = False
                elif m["name"].startswith("Init"):
                    want_name, is_ctor = canon.split("::")[-1], True
                else:
                    continue
                pn = self.pdb_names.get("%08x" % va) or {}
                if pn.get("dev") and int(pn["dev"], 16) in D.pub and H.split_qual(pn.get("name") or "")[0] == canon:
                    out.append((va, D.pub[int(pn["dev"], 16)], pn["name"]))      # pdb_names pairs the retail VA with its dev function
                    continue
                cands = []
                for dva, mangled, f in ms:
                    dd = parse_cdecl_demangled(dm.get(mangled))
                    if dd and dd["name"] == want_name and len(dd["params"]) == len(m["params"]):
                        cands.append((mangled, dd))
                if len(cands) == 1:
                    out.append((va, cands[0][0], "%s::%s" % (canon, want_name)))
                else:
                    self.notes.append(("callee-name", "0x%08x %s::%s: %d dev publics match %s" % (va, sname, m["name"], len(cands), want_name)))
        return out

    def write_names(self):
        p = W("symbols", "slices", self.sid + ".txt")
        lines = []
        for va, mangled, q in self.callee_names():
            lines.append("%08x %s  # %s (callee of %s, named from the dev publics; slice address comment)" % (va, mangled, q, self.sid))
        for c in sorted(self.fns, key=lambda x: x.va):
            sym = self.symbols.get(c.va)
            if sym:
                nm = ((c.cls + "::") if c.cls else "") + str(c.name) if getattr(c, "verbatim", False) else \
                    "%s::%s" % (self.qual_of(c), c.decl.name)
                lines.append("%08x %s  # %s migrated from %s%s" % (c.va, sym, nm, self.sid, " (verbatim, slice spelling)" if getattr(c, "verbatim", False) else ""))
        if lines:
            # several modules migrate out of one slice, each run writes only its own functions: keep the other lines
            # (keyed by VA, this run's lines win)
            have = {}
            if os.path.exists(p):
                for l in open(p).read().split("\n"):
                    if l.strip() and not l.startswith("#"):
                        have[l.split()[0]] = l
            for l in lines:
                have[l.split()[0]] = l
            # a line an earlier run wrote for a function this slice no longer migrates (it names a symbol the module TU
            # does not have any more) goes; the slice's own spelling of that address is restored from git when it had one
            now = {c.va for c in self.fns}
            mine = {"%08x" % c.va for c in self.chunks if c.va not in now}
            for k in [k for k, l in have.items() if k in mine and "migrated from %s" % self.sid in l]:
                del have[k]
                orig = subprocess.run(["git", "show", "HEAD:symbols/slices/%s.txt" % self.sid], capture_output=True, text=True, cwd=ROOT)
                for ol in orig.stdout.split("\n"):
                    if ol.split()[:1] == [k]:
                        have[k] = ol
                self.notes.append(("pruned", "names line of 0x%s removed (no longer migrated from %s)" % (k, self.sid)))
            open(p, "w").write("\n".join(have[k] for k in sorted(have)) + "\n")

    def write_report(self):
        rep = dict(
            slice=self.sid,
            functions_moved=["%08x" % c.va for c in self.fns],
            functions_left_in_slice=[n[1] for n in self.notes if n[0] in ("skipped", "unmapped-function", "dropped")],
            functions_verbatim=["%08x" % c.va for c in self.fns if getattr(c, "verbatim", False)],
            structs_replaced={k: v for k, v in sorted(self.class_map.items()) if k in self.structs},
            structs_kept_as_local_stubs=[s for s in self.structs if s not in self.class_map and
                                         any(re.search(r"(?<![\w.])%s\b" % re.escape(s), c.out_body) for c in self.fns)],
            structs_dropped_unused=[s for s in self.structs if s not in self.class_map and
                                    not any(re.search(r"(?<![\w.])%s\b" % re.escape(s), c.out_body) for c in self.fns)],
            member_paths_mapped=sum(len(m) for m in self.members_map.values()),
            counters=dict(self.stats),
            method_renames={"%s::%s" % (s, k): d.name for s, m in self.method_map.items() for k, d in m.items() if d.name != k},
            manual_entries={k: (len(v) if hasattr(v, "__len__") else v) for k, v in self.manual.items() if k != "why"},
            notes=[list(n) for n in self.notes if n[0] != "probe"],
        )
        # one report per module when the slice is migrated module by module (--module): runs must not overwrite each other
        suffix = "_" + re.sub(r"\W", "", self.module_filter) if getattr(self, "module_filter", None) else ""
        suffix += re.sub(r"\W", "", self.variant)
        json.dump(rep, open(W("work", "migrate", "rewrite_%s%s.json" % (self.sid, suffix)), "w"), indent=1)
        return rep

    def write_renames(self):
        auto = dict(
            class_map={k: dict(canonical=v, why=self.why.get(k, "")) for k, v in sorted(self.class_map.items())},
            members={s: {k: v[0] for k, v in mp.items()} for s, mp in self.members_map.items()},
            unpaired_members={s: u for s, u in getattr(self, "unpaired", {}).items() if u},
            methods={s: {k: d.sig() + (" // 0x%08x" % d.va if d.va else "") for k, d in m.items()} for s, m in self.method_map.items() if m},
            functions={"%08x" % c.va: dict(slice="%s::%s" % (c.cls, c.name), canonical=(c.defline if getattr(c, "defline", None) else None),
                                           how=c.how, notes=getattr(c, "notes", [])) for c in self.chunks},
            unmapped_structs=[s for s in self.structs if s not in self.class_map],
            notes=[list(n) for n in self.notes])
        os.makedirs(os.path.dirname(self.renames_path), exist_ok=True)
        json.dump(dict(auto=auto, manual=self.manual), open(self.renames_path, "w"), indent=1)

    # ---- 9. checked apply: never leave the module TU uncompilable or a byte-exact function inexact ---------------------
    def module_paths(self):
        out = []
        for module in sorted({c.module for c in self.fns}):
            d, obj = os.path.split(module)
            stem = obj[:-4]
            out.append(W("src", "game", d, stem + ".cpp"))
            for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
                out.append(W("src", "game", d, stem, f))
        out.append(W("symbols", "slices", self.sid + ".txt"))
        return out

    def snapshot(self):
        return {p: (open(p).read() if os.path.exists(p) else None) for p in self.module_paths()}

    @staticmethod
    def restore(snap):
        for p, text in snap.items():
            if text is None:
                if os.path.exists(p):
                    os.remove(p)
            else:
                os.makedirs(os.path.dirname(p), exist_ok=True)
                open(p, "w").write(text)

    def prune_unemitted(self):
        """A run that emits no function (everything left in the slice / excluded) still removes what an earlier run of this
        slice put in the module TU: its function blocks, its items section and their rows (s004e01d0: the stale verbatim
        `reserve` of round 0 stayed in SPGraphicsTextureUtilities.cpp, and the next slice's merge would have kept it)."""
        mods = {c.module for c in self.chunks if c.module and (not getattr(self, "module_filter", None) or
                                                               mod_match(self.module_filter, c.module))}
        mine = {c.va for c in self.chunks}
        bv = getattr(self, "batch_vas", None)
        if bv:
            # fix pass 6 (mig7, reports 01/21/22): only what the batch lists for this slice; the rest of the slice's landed
            # blocks belong to earlier batches.  The unfiltered set emptied EditorManipulationUtilities to 0/24
            mine = {va for va in mine if "%08x" % va in bv[1]}
        mine -= getattr(self, "failed_vas", set())      # failed to compile this run: the earlier block stays
        allmine = {c.va for c in self.chunks}
        for module in sorted(mods):
            d, obj = os.path.split(module)
            tu = W("src", "game", d, obj[:-4] + ".cpp")
            if not os.path.exists(tu):
                continue
            old = open(tu).read()
            parts = re.split(r"(?m)^(?=// @ 0x[0-9a-fA-F]+$)", old)
            keep = [b for b in parts[1:] if int(re.match(r"// @ 0x([0-9a-fA-F]+)", b).group(1), 16) not in mine]
            left = [b for b in keep if int(re.match(r"// @ 0x([0-9a-fA-F]+)", b).group(1), 16) in allmine]
            pre = parts[0] if left else re.sub(
                r"(?s)\n?// ---- items of slice %s begin.*?// ---- items of slice %s end\n?" % (self.bid, self.bid), "\n", parts[0])
            new = pre + "".join(keep)
            if new != old:
                open(tu, "w").write(new)
                self.notes.append(("pruned", "%d block(s) of %s removed from %s.cpp: this run emits none" % (
                    len(parts) - 1 - len(keep), self.sid, obj[:-4])))
            self.prune_rows(d, obj[:-4])

    def demote(self, c, why):
        """A converted function that does not compile or lost byte-exactness keeps the slice's text (verbatim); a verbatim
        one that still fails stays in the slice (dropped from this run)."""
        if getattr(c, "verbatim", False):
            if c in self.fns:
                self.fns.remove(c)
            # fix pass 6: an earlier run's block of this function stays in the TU (prune skips it); only a deliberate hold
            # (leave_in_slice, exclude, asm, layout guard) removes a landed function
            self.failed_vas = getattr(self, "failed_vas", set()) | {c.va}
            self.notes.append(("dropped", "0x%08x %s stays in the slice: %s" % (c.va, c.name, why)))
            self.stats["dropped_to_slice"] += 1
            return
        self.make_verbatim(c)
        for ns, old_n, new_n in getattr(self, "renamed", []):
            c.defline = RS.rename_word(c.defline, old_n, new_n, ns)
            c.out_body = RS.rename_word(c.out_body, old_n, new_n, ns)
            # a constructor/destructor `New::Old(...)` (s00948de0 0x949b80: C2039 'INetFileCache' is not a member of
            # 'INetFileCache_s0094_8de0'), as rename_stub does for the functions it renames
            c.defline = re.sub(r"\b%s\s*::\s*(~?)\s*%s\b" % (re.escape(new_n), re.escape(old_n)),
                               lambda mm: "%s::%s%s" % (new_n, mm.group(1), new_n), c.defline)
            if c.cls == old_n:
                c.cls = new_n
        self.notes.append(("demoted", "0x%08x %s converted body rejected, slice text kept: %s" % (c.va, c.name, why)))
        self.stats["demoted_to_verbatim"] += 1

    def repair_failed(self, log):
        """Compiler errors in CONVERTED bodies that one mechanical edit fixes, applied before demoting: an int where the canonical
        type is an enum (`return 0;` in a function returning EA::ArgScript::tArgError, s0083a9f0 ParseVectorArgument/ParseArgument
        /ParseArgumentEx; `job->mResult = 6;` into EA::Internet::HTTPClient::JobResult, s00942290) -> `return (E)(0);` / `x = (E)(6);`.
        An enum cast of an int is the same machine code.  -> number of edits."""
        n = 0
        done = getattr(self, "_repairs", set())
        self._repairs = done
        for module in sorted({c.module for c in self.fns}):
            d, obj = os.path.split(module)
            lines = open(W("src", "game", d, obj[:-4] + ".cpp")).read().split("\n")
            block_of, cur = [], None
            for l in lines:
                mm = re.match(r"^// @ 0x([0-9a-fA-F]+)$", l)
                if mm:
                    cur = int(mm.group(1), 16)
                block_of.append(cur)
            mine = {c.va: c for c in self.fns if c.module == module and not getattr(c, "verbatim", False)}
            for m in re.finditer(r"(\S[^\n(]*)\((\d+)\) : error C2440: '(return|=|initializing)' : cannot convert from 'int' to '([\w:]+)'", log):
                if not m.group(1).replace("\\", "/").lower().endswith("/" + obj[:-4].lower() + ".cpp"):
                    continue
                ln, what, enum = int(m.group(2)), m.group(3), m.group(4)
                if not (0 < ln <= len(lines)) or block_of[ln - 1] not in mine or enum not in self.data.types.enums:
                    continue
                c = mine[block_of[ln - 1]]
                src = lines[ln - 1]
                if what == "return":
                    fixed = re.sub(r"\breturn\s+(.+?)\s*;", lambda mm: "return (%s)(%s);" % (enum, mm.group(1)), src, count=1)
                else:
                    fixed = re.sub(r"(?<![=!<>])=\s*(?!=)([^;]+);", lambda mm: "= (%s)(%s);" % (enum, mm.group(1).strip()), src, count=1)
                if fixed == src or (c.va, src.strip()) in done:
                    continue
                done.add((c.va, src.strip()))
                if src.strip() in c.out_body:
                    c.out_body = c.out_body.replace(src.strip(), fixed.strip())
                    n += 1
                    self.stats["enum_casts"] += 1
                    self.notes.append(("repaired", "0x%08x %s: `%s` -> `%s` (C2440 int -> %s)" % (c.va, c.name, src.strip()[:60], fixed.strip()[:80], enum)))
            # a slice pointer parameter that the canonical declaration takes by reference (`const char** p` vs `char const *& p`,
            # s0083e1c0 EvalSignedIntNumber / EvalIntFactor, s0083d3d0 EvalIntParentheses): the body's `*p` became `p`, so a
            # call of a slice helper that still takes the pointer (`DiscardWhiteSpace(p)`, `const char **`) gets `&p`, and the
            # reverse mismatch `*p`
            for m in re.finditer(r"(\S[^\n(]*)\((\d+)\) : error C2664: '([^']+)' : cannot convert parameter (\d+) from '([^']+)' to '([^']+)'", log):
                if not m.group(1).replace("\\", "/").lower().endswith("/" + obj[:-4].lower() + ".cpp"):
                    continue
                ln, fname, k, frm, to = int(m.group(2)), m.group(3).split("::")[-1], int(m.group(4)), m.group(5), m.group(6)
                if not (0 < ln <= len(lines)) or block_of[ln - 1] not in mine:
                    continue
                nf, nt = frm.replace(" ", ""), to.replace(" ", "")
                if nt == nf + "*":
                    wrap = "&%s"
                elif nf == nt.rstrip("&") + "*" and nt.endswith("&"):
                    wrap = "*%s"
                else:
                    continue
                c = mine[block_of[ln - 1]]
                src = lines[ln - 1]
                mc = re.search(r"\b%s\s*\(" % re.escape(fname), src)
                if not mc:
                    continue
                o = mc.end() - 1
                e = match_close(mask(src), o)
                if e < 0:
                    continue
                args = split_top(src[o + 1:e])
                if k > len(args) or not re.match(r"^[A-Za-z_]\w*$", args[k - 1]):
                    continue
                args[k - 1] = wrap % args[k - 1]
                fixed = src[:o + 1] + ", ".join(args) + src[e:]
                if (c.va, src.strip()) in done or src.strip() not in c.out_body:
                    continue
                done.add((c.va, src.strip()))
                c.out_body = c.out_body.replace(src.strip(), fixed.strip())
                n += 1
                self.stats["ref_ptr_args"] += 1
                self.notes.append(("repaired", "0x%08x %s: `%s` -> `%s` (C2664 %s -> %s)" % (c.va, c.name, src.strip()[:60], fixed.strip()[:80], frm, to)))
        return n

    def demote_failed(self, log):
        """Attribute compiler errors to this slice's functions by line number and demote them.  -> number demoted/dropped."""
        allerrs = [(m.group(1), int(m.group(2)), m.group(3).strip()) for m in re.finditer(r"(\S[^\n(]*)\((\d+)\) : (?:fatal )?error (C\d+[^\n]*)", log)]
        if not allerrs:
            return 0
        n = 0
        for module in sorted({c.module for c in self.fns}):
            d, obj = os.path.split(module)
            # not the headers' lines; VC9 prints the path in either case (lowercased in some runs: report_s009013e0.md), so compare
            # case-insensitively
            errs = [(ln, msg) for f, ln, msg in allerrs if f.replace("\\", "/").lower().endswith("/" + obj[:-4].lower() + ".cpp")]
            lines = open(W("src", "game", d, obj[:-4] + ".cpp")).read().split("\n")
            block_of = []              # line index -> va of the enclosing function block, None in the preamble
            cur = None
            for l in lines:
                mm = re.match(r"^// @ 0x([0-9a-fA-F]+)$", l)
                if mm:
                    cur = int(mm.group(1), 16)
                block_of.append(cur)
            mine = {c.va: c for c in self.fns if c.module == module}
            hit = {}
            renamed_now = set()
            for ln, msg in errs:
                va = block_of[ln - 1] if 0 < ln <= len(block_of) else None
                if va in mine:
                    hit.setdefault(va, msg)
                elif (va is None and re.match(r"C(2371|2373|2011|2084|2086|2365|2374|2953|2040)\b", msg)) or \
                        (re.match(r"C2733\b", msg) and va not in mine and any(
                            re.search(r"\b%s\s*\(" % re.escape(x), mask(t)) for x in re.findall(r"'([\w:]+)'", msg)[:1] for _k, t in self.items)):
                    # (C2733 `second C linkage of overloaded function`: this slice's `extern "C" bool FUN_00693c70(VStream*, void*)`
                    # prototype vs another slice's extern "C" DEFINITION with other parameters, reported at that definition;
                    # fix pass 5, s00694210)
                    # (C2040: two slices' `extern T g_x;` of one retail global with different types, fix pass 5 s0074c260
                    # `extern PropListW* g_appProps;` vs `extern int g_appProps;`: this slice's is renamed, the address comment
                    # still binds it)
                    # a local stub of this slice redefines a name an included canonical header (or another slice) declares:
                    # rename the stub in this slice, keep the functions
                    qn = re.search(r"'([\w:]+)'", msg)
                    if qn:
                        parts = qn.group(1).split("::")
                        key = (tuple(parts[:-1]), parts[-1])
                        if key not in renamed_now and not any(r[0] == key[0] and r[1] == key[1] for r in getattr(self, "renamed", [])):
                            renamed_now.add(key)
                            self.rename_stub([c for c in self.fns], key[0], key[1], "redefinition: %s" % msg[:80], verbatim_only=bool(key[0]))
                            n += 1
                elif va is None and re.match(r"C2664\b", msg) and (self.rsfx) in \
                        (re.search(r" to '([^']*)'", msg) or re.search(r"()", "")).group(1) and \
                        re.search(r"from '[^']*_s[0-9a-f]{4}_[0-9a-f]{4}", msg):
                    # an earlier slice's item calls its own function F (global), and this slice declares F in a namespace with
                    # its own stub types: inside that namespace this F hides the global one (fix pass 4: s0059b4b0's iterator
                    # calls ::RBTreeIncrement(rbtree_node_base_s0059_b4b0*), s0059c4c0 declares eastl::RBTreeIncrement(
                    # rbtree_node_base_s0059_c4c0*), C2664 and the whole slice stayed behind): rename this slice's F
                    qn = re.search(r"'([\w:]+)'", msg)
                    if qn:
                        parts = qn.group(1).split("::")
                        key = (tuple(parts[:-1]), parts[-1])
                        if key not in renamed_now and not any(r[0] == key[0] and r[1] == key[1] for r in getattr(self, "renamed", [])):
                            renamed_now.add(key)
                            self.rename_stub([c for c in self.fns], key[0], key[1], "hides another slice's overload: %s" % msg[:80])
                            n += 1
                elif va is None:
                    # preamble: a local stub of this slice (or an include) is wrong; the functions using the offending
                    # item's names cannot compile: attribute by the identifiers on the error line
                    ids = set(RS.IDENT.findall(lines[ln - 1])) if 0 < ln <= len(lines) else set()
                    for c in mine.values():
                        if ids & RS.item_uses("other", c.defline + "\n" + c.out_body):
                            hit.setdefault(c.va, "preamble line %d: %s" % (ln, msg))
            # a syntax error in one function (or an unclosed namespace) makes the compiler report errors in the functions
            # after it: converted bodies are suspected first; verbatim functions are dropped only when no converted one failed
            if renamed_now:
                continue                # the redefinition explains the other errors: retry before blaming a function
            conv = {va: m for va, m in hit.items() if not getattr(mine[va], "verbatim", False)}
            for va, msg in (conv or hit).items():
                self.demote(mine[va], msg)
                n += 1
        return n

    def run_all_locked(self, manifest, tries=120, wait=10):
        """run_all.py on a manifest; waits (never kills) while another run holds work/run_all.lock.  -> stdout+stderr."""
        import time
        py = W(".venv", "bin", "python")
        py = py if os.path.exists(py) else sys.executable
        out = ""
        for _i in range(tries):
            r = subprocess.run([py, W("tools", "matching", "run_all.py"), "--manifest", manifest, "-v"], capture_output=True, text=True, cwd=ROOT)
            out = r.stdout + r.stderr
            if "another run_all" not in out or "functions byte-exact" in out:
                return out
            time.sleep(wait)
        raise RuntimeError("run_all.lock held for %d s" % (tries * wait))

    def verify_exact(self):
        """run_all on the module manifest rows of this slice's functions -> {va: status}."""
        py = W(".venv", "bin", "python")
        py = py if os.path.exists(py) else sys.executable
        res = {}
        for module in sorted({c.module for c in self.fns}):
            d, obj = os.path.split(module)
            stem = obj[:-4]
            mp = W("src", "game", d, stem, "manifest.txt")
            vas = {c.va for c in self.fns if c.module == module}
            rows = []
            if os.path.exists(mp):
                for line in open(mp):
                    p = line.split("#", 1)[0].split()
                    if len(p) >= 3 and int(p[2], 16) in vas:
                        rows.append(line)
            if not rows:
                continue
            scratch = os.path.join(self.scratch, "verify_%s.txt" % stem)
            open(scratch, "w").write("".join(rows))
            out = self.run_all_locked(scratch)
            for line in out.splitlines():
                mm = re.match(r"^(MATCH|DIFF|FAIL)\s+\S+\s+([0-9a-f]{8})\s*(.*)$", line)
                if mm:
                    res[int(mm.group(2), 16)] = "MATCH" if mm.group(1) == "MATCH" else (mm.group(3) or mm.group(1)).strip()
            if "COMPILE FAIL" in out:
                for va in vas:
                    res.setdefault(va, "COMPILE FAIL")
        return res

    def apply_checked(self, rounds=10):
        """apply() + compile + bookkeeping + byte-exact check, retried after demoting what fails.  -> (ok, log)."""
        snap = self.snapshot()
        log = ""
        for rnd in range(rounds):
            self.restore(snap)
            if not self.fns:
                self.prune_unemitted()
                return True, "nothing to write"
            self.apply()
            log = self.compile_symbols()
            if log:
                # keep the failing TU and the compiler log in the scratch directory (the TU is restored below)
                for module in {c.module for c in self.fns}:
                    tu = W("src", "game", os.path.dirname(module), os.path.basename(module)[:-4] + ".cpp")
                    if os.path.exists(tu):
                        open(os.path.join(self.scratch, "failed_%s_round%d.cpp" % (self.sid, rnd)), "w").write(open(tu).read())
                open(os.path.join(self.scratch, "failed_%s_round%d.log" % (self.sid, rnd)), "w").write(log)
                if self.repair_failed(log):
                    continue
                if self.demote_failed(log):
                    continue
                self.restore(snap)
                return False, log
            self.write_names()
            for module, fns in {c.module: [x for x in self.fns if x.module == c.module] for c in self.fns}.items():
                d, obj = os.path.split(module)
                self.module = module
                self.write_bookkeeping(module, d, obj[:-4], fns)
            try:
                bad = {va: st for va, st in self.verify_exact().items() if st != "MATCH"}
            except RuntimeError as e:
                self.restore(snap)
                return False, "verification impossible: %s" % e
            if bad:
                byva = {c.va: c for c in self.fns}
                keep = {int(x, 16) for x in os.environ.get("RW_KEEP_DIFF", "").split(",") if x}      # debugging: keep these VAs in the TU
                bad = {va: st for va, st in bad.items() if va not in keep}
                for va, st in sorted(bad.items()):
                    if va in byva:
                        self.demote(byva[va], "byte-exact in the slice, %s in the module TU" % st)
                if not bad:
                    return True, ""
                continue
            return True, ""
        self.restore(snap)
        return False, log or "still failing after %d rounds" % rounds


class NoFunctions(Exception):
    pass


def var_sources(sid):
    """{va: variant suffix} for the functions of a slice that live in a second source `<sid><suffix>.cpp`"""
    d = os.path.join(SLICES, sid)
    var_of = {}
    if not os.path.exists(os.path.join(d, sid + ".cpp")):
        return var_of
    mp_ = os.path.join(d, "manifest.txt")
    if os.path.exists(mp_):
        for l in open(mp_):
            t = l.split("#", 1)[0].split()
            if len(t) >= 3 and t[0].endswith(".cpp"):
                base = os.path.basename(t[0])[:-4]
                if base.startswith(sid) and base != sid:
                    var_of[t[2].lower().zfill(8)] = base[len(sid):]
    marks = lambda f: {m.lower().zfill(8) for m in re.findall(r"(?m)^\s*//\s*@\s*0x([0-9a-fA-F]+)", open(f, errors="replace").read())}
    main_vas = marks(os.path.join(d, sid + ".cpp"))
    for f in sorted(os.listdir(d)):
        if f.endswith(".cpp") and f.startswith(sid) and f != sid + ".cpp":
            for va in marks(os.path.join(d, f)) - main_vas:
                var_of.setdefault(va, f[len(sid):-4])
    return var_of


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("slice")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--module")
    ap.add_argument("--scratch", default=None,
                    help="scratch directory (probe sources, objects); default work/migrate/scratch_<slice>, one per slice so "
                         "concurrent runs of different slices do not overwrite each other's probe files")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--variant", default="", help="a flag-variant TU of the slice (`_od` reads <slice>_od.cpp): only the VAs whose "
                    "manifest rows name that file are landed from it; a plain run skips them (fix pass 5, SPUIBehavior)")
    ap.add_argument("--batch", help="work/batches/<name>.json: functions of this slice that the batch does not list for the "
                                    "module stay in the slice (fix pass 2; round 2 needed hand-written leave_in_slice rows)")
    a = ap.parse_args()
    if not a.scratch:
        a.scratch = W("work", "migrate", "scratch_%s" % a.slice)
    try:
        rw = Rewrite(a.slice, a.scratch, a.variant)
    except NoFunctions as e:
        print(e)
        return
    if a.batch:
        ents = json.load(open(W("work", "batches", a.batch + ".json")))
        listed = {va.lower() for e in ents if e["id"] == a.slice and (not a.module or mod_match(a.module, e["module"]))
                  for va in e["vas"]}
        # a VA the batch lists for this module under another slice that does not define it (mig3: 0x4f6510 under s005ec030 but
        # defined in s004f56f0, 0x4f6720 under s004ef880 but defined in s004f6630; round 3 landed them by hand) is this
        # slice's when this slice defines it
        def _defines(sid, va):          # the slice's bookkeeping has a row for it (a declaration-only marker does not count)
            vas, _syms = RS.slice_rows(sid)
            return int(va, 16) in vas
        for e in ents:
            if e["id"] == a.slice or (a.module and not mod_match(a.module, e["module"])):
                continue
            for va in e["vas"]:
                if va.lower() not in listed and not _defines(e["id"], va.lower()) and _defines(a.slice, va.lower()):
                    listed.add(va.lower())
        # variants: a VA whose manifest row names `<slice><variant>.cpp` lands from that variant's run only.  fix pass 6 C7: any
        # second source `<slice>*.cpp` is a variant (s0062da00_ui.cpp, s00634490b.cpp), and a VA without a manifest row
        # (a nonmatching row: 0x62e2e0) belongs to the source whose marker defines it when the main source does not
        var_of = var_sources(a.slice)
        listed_all = set(listed)
        listed = {va for va in listed if var_of.get(va, "") == a.variant}
        rw.batch_vas = (a.batch, listed)
    rw.assign_chunks(a.module)
    if a.batch:
        # fix pass 6 auto-union (mig7 reports 01, 02, 21, 22): this slice's functions that an earlier batch already put in the
        # module TU belong to this run too, so a re-apply that lists only new VAs neither prunes them nor leaves their items out
        # of the merged preamble.  A VA the batch gives to another slice stays that slice's (fix pass 5, s007ca950)
        other = {va.lower() for e in ents if e["id"] != a.slice for va in e["vas"]}
        added = []
        for module in sorted({c.module for c in rw.chunks if c.module and (not a.module or mod_match(a.module, c.module))}):
            d, obj = os.path.split(module)
            tu = W("src", "game", d, obj[:-4] + ".cpp")
            if not os.path.exists(tu):
                continue
            have = {m.lower().zfill(8) for m in re.findall(r"(?m)^// @ 0x([0-9a-fA-F]+)$", open(tu).read())}
            for c in rw.chunks:
                v = "%08x" % c.va
                if c.module == module and v in have and v not in listed and v not in other and var_of.get(v, "") == a.variant:
                    listed.add(v)
                    added.append(v)
        if added:
            rw.notes.append(("union", "%d function(s) already in the module TU added to the batch: %s" % (len(added), " ".join(sorted(added)))))
    rw.map_structs()
    rw.build(a.module)
    if not a.quiet:
        print("class map:")
        for k, v in sorted(rw.class_map.items()):
            print("  %-20s -> %-50s %s" % (k, v[:50], rw.why.get(k, "")[:100]))
        print("unmapped structs:", [s for s in rw.structs if s not in rw.class_map])
        print("methods of other mapped structs:")
        for k, how in sorted(getattr(rw, "mm_how", {}).items()):
            s_, m_ = k.split("::", 1)
            print("  %-40s -> %-50s [%s]" % (k, rw.method_map[s_][m_].sig()[:50], how))
        print("functions:")
        for c in rw.chunks:
            print("  0x%08x %-22s -> %s   [%s]" % (c.va, (c.cls + "::" + c.name) if c.ok else "(free function)", (c.decl.sig() if c.decl else "-"), c.how))
            for n in getattr(c, "notes", []):
                print("      note:", n)
    for n in rw.notes:
        if n[0] != "probe":
            print("note", n[0], n[1][:200])
    if a.batch and not a.variant:             # a variant run never points back (an agent would loop)
        other_vars = sorted({var_of.get(va, "") for va in listed_all if var_of.get(va, "") != a.variant})
        for v in other_vars:
            vv = sorted(va for va in listed_all if var_of.get(va, "") == v)
            print("VARIANT SOURCE: %d batch function(s) of this slice live in %s%s.cpp (%s): after this entry, run the same "
                  "commands with --variant %s" % (len(vv), a.slice, v or "", " ".join(vv[:8]), v or '""'))
    log = ""
    if a.apply:
        if not os.environ.get("RW_NO_WRITE"):
            rw.write_renames()
        ok, log = rw.apply_checked()
        if not ok:
            print("COMPILE FAILED (module TU and bookkeeping restored)\n" + log[-6000:])
        else:
            rw.measure_rows()
            rep = rw.write_report()
            print("wrote", ", ".join(sorted({"src/game/" + c.module[:-4] + ".cpp" for c in rw.fns})))
            print("report:", json.dumps(rep["counters"]), "left in slice:", rep["functions_left_in_slice"],
                  "local stubs:", rep["structs_kept_as_local_stubs"])
            for n in rw.notes:
                if n[0] in ("demoted", "dropped", "renamed-stub"):
                    print("note", n[0], n[1][:300])
    if not os.environ.get("RW_NO_WRITE"):       # dry sweeps while landing agents edit the renames files' manual sections
        rw.write_renames()


if __name__ == "__main__":
    main()
