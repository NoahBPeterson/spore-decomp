# Quick-sort partition (eastl-style) over Obj** with a by-value ref-counted pivot whose destructor
# calls a virtual (Release) at vtable offset N[-1], plus an empty thiscall comparator by value.
# Forced evaluation order via temps (b then a) and goto loops reproduces the register schedule.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; lea ebx, [ebx] ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [edi] ; push ecx ; push eax ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; add edi, N ; jmp +N ; mov eax, dword ptr [esi - N] ; mov edx, dword ptr [esp + N] ; sub esi, N ; push eax ; push edx ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; mov eax, dword ptr [esi - N] ; sub esi, N ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test al, al ; jne +N ; cmp edi, esi ; jae +N ; push esi ; push edi ; call EXT ; add esp, N ; add edi, N ; jmp +N ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; mov eax, edi ; pop edi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
_v = "".join("virtual void v%d(); " % i for i in range(64))
PRELUDE = ("struct Obj { %s};\nstruct Cmp { bool operator()(Obj* a, Obj* b) const throw(); };\n"
           "void swp(Obj**, Obj**) throw();\n") % _v
def emit(va, A, N):
    idx = N[-1] // 4
    p = "P_%08x" % va
    src = ("struct %s { Obj* p; ~%s() { if (p) p->v%d(); } operator Obj*() { return p; } };\n"
           "Obj** FUN_%08x(Obj** first, Obj** last, %s pivot, Cmp comp) throw() {\n"
           "top:\n"
           "  { Obj* b = pivot; Obj* a = *first; if (comp(a, b)) { ++first; goto top; } }\n"
           "  --last;\n"
           "l2:\n"
           "  { Obj* b = *last; Obj* a = pivot; if (comp(a, b)) { --last; goto l2; } }\n"
           "  if (first < last) { swp(first, last); ++first; goto top; }\n"
           "  return first;\n}\n") % (p, p, idx, va, p)
    return src, "?FUN_%08x@@YAPAPAUObj@@PAPAU1@0U%s@@UCmp@@@Z" % (va, p)
