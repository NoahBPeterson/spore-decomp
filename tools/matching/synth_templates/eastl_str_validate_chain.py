# Pattern 83 (15 instances): 460-byte EASTL string helper, template instantiations.
# Shape: char string s = Assign(spec); if non-empty { K(p ? Mk(p,-1) : WString()); Pair pr = Split(s);
#   virtual-call validation chain on obj (slots 0,2,3,1) with a global debug flag }.
# NOT byte-exact: frame layout (0x54) and prologue/early part match, but register allocation
# (orig: edi=sEmpty, esi pushed late) and jump threading of second.empty() do not.
PATTERN = 'sub esp, N ; mov eax, dword ptr [esp + N] ; push ebx ; push edi ; push eax ; lea ecx, [esp + N] ; mov edi, A ; push ecx ; mov dword ptr [esp + N], N ; mov bl, N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], A ; call EXT ; mov eax, dword ptr [esp + N] ; add esp, N ; cmp eax, dword ptr [esp + N] ; je +N ; mov eax, dword ptr [esp + N] ; push esi ; test eax, eax ; je +N ; push -N ; push eax ; lea edx, [esp + N] ; push edx ; mov ebx, N ; call EXT ; mov esi, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; add esp, N ; jmp +N ; mov esi, A ; mov ebx, N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], esi ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test bl, N ; je +N ; sub esi, edi ; and esi, A ; and ebx, A ; cmp esi, N ; jle +N ; test edi, edi ; je +N ; push edi ; call EXT ; add esp, N ; test bl, N ; je +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; push ebp ; lea edx, [esp + N] ; push edx ; lea eax, [esp + N] ; push eax ; call EXT ; mov esi, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; mov edx, dword ptr [esi] ; mov ebx, dword ptr [esp + N] ; mov eax, dword ptr [edx] ; add esp, N ; mov ecx, esi ; cmp edi, ebp ; jne +N ; push ebx ; call eax ; test al, al ; jne +N ; xor al, al ; cmp edi, ebp ; pop ebp ; jne +N ; test al, al ; je +N ; push ebx ; jmp +N ; push edi ; call eax ; test al, al ; setne al ; cmp byte ptr [A], N ; je +N ; test al, al ; je +N ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edx + N] ; push ebx ; push A ; mov ecx, esi ; call eax ; jmp +N ; test al, al ; je +N ; mov edx, dword ptr [esi] ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [edx + N] ; push eax ; mov ecx, esi ; call edx ; test al, al ; je +N ; mov al, N ; jmp +N ; test al, al ; je +N ; push edi ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; mov ecx, esi ; call edx ; test al, al ; je +N ; mov bl, N ; jmp +N ; xor bl, bl ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; cmp ecx, N ; pop esi ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; mov edx, dword ptr [esp + N] ; sub edx, edi ; and edx, A ; cmp edx, N ; jle +N ; test edi, edi ; je +N ; push edi ; call EXT ; add esp, N ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; sub ecx, eax ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; pop edi ; mov al, bl ; pop ebx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = 'typedef unsigned short wchar16;\nvoid EASTL_allocator_deallocate(void* p);\nextern char sEmpty8[];\nstruct Alloc2 { const char* mpName; };\nstruct String8 {\n    char* mpBegin; char* mpEnd; char* mpCap; Alloc2 a;\n    String8(): mpBegin(sEmpty8), mpEnd(sEmpty8), mpCap(sEmpty8+1) {}\n    ~String8() { if ((mpCap - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin); }\n    bool empty() const { return mpBegin==mpEnd; }\n};\nstruct WString {\n    wchar16* mpBegin; wchar16* mpEnd; wchar16* mpCap; Alloc2 a;\n    WString(): mpBegin((wchar16*)sEmpty8), mpEnd((wchar16*)sEmpty8), mpCap((wchar16*)(sEmpty8+2)) {}\n    ~WString() { if ((mpCap - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin); }\n    bool empty() const { return mpBegin==mpEnd; }\n};\nstruct Pair { WString first, second; };\nstruct Obj {\n    virtual bool v0(const wchar16*);\n    virtual bool v1(const wchar16*);\n    virtual bool v2(const wchar16*, const wchar16*);\n    virtual bool v3(const wchar16*);\n};\nstruct Body8 { char* b; char* e; char* c; };\nWString Mk(const char*, int);\nPair Split(const Body8&);\nextern const wchar16 kType[];\nstruct K { int pad[4]; K(const WString&); };\n'
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import synth as _s
from card import load_funcs, bounds
_starts = None
def _calls(va):
    global _starts
    if _starts is None:
        _starts, _ = load_funcs()
    code = bounds(va, _starts)
    return [int(i.op_str, 16) for i in _s.md.disasm(code, va) if i.mnemonic == "call" and i.op_str.startswith("0x")]
def emit(va, A, N):
    c = _calls(va)
    flag = "g_%08x" % A[6]
    asg = "Assign_%08x" % c[0]
    src = ("extern char %s;\nvoid %s(Body8*, const char*);\n"
           "bool FUN_%08x(Obj* o, const char* p, const char* spec, const wchar16* a4) {\n"
           "    bool r = true;\n    String8 s;\n    %s((Body8*)&s.mpBegin, spec);\n"
           "    if (!s.empty()) {\n        { K k(p ? Mk(p, -1) : WString()); }\n        {\n"
           "        Pair pr = Split(*(Body8*)&s.mpBegin);\n"
           "        const wchar16* key = pr.second.empty() ? a4 : pr.second.mpBegin;\n"
           "        bool ok = o->v0(key);\n"
           "        if (!pr.second.empty() && %s && ok) ok = o->v2(kType, a4);\n"
           "        ok = ok && o->v3(pr.first.mpBegin);\n"
           "        r = ok && o->v1(key);\n        }\n    }\n    return r;\n}\n") % (flag, asg, va, asg, flag)
    return src, "?FUN_%08x@@YA_NPAUObj@@PBD1PBG@Z" % va
