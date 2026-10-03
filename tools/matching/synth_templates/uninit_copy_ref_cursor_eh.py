# Uninit-copy loop with destination cursor in a struct, new-expression EH state (placement delete declared).
# r->p = init; for (; first != last; ++first, ++r->p) new(r->p) T(*first); return r;
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov dword ptr [esi], eax ; mov eax, dword ptr [esp + N] ; cmp eax, dword ptr [esp + N] ; je +N ; jmp +N ; lea ecx, [ecx] ; mov ecx, dword ptr [esi] ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], N ; test ecx, ecx ; je +N ; push eax ; call EXT ; mov eax, dword ptr [esp + N] ; add dword ptr [esi], N ; add eax, N ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; cmp eax, dword ptr [esp + N] ; jne +N ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\ninline void operator delete(void*, void*) {}\n"
PRELUDE += "template<class T> inline void construct_at_(T* p, const T& v) { void* vp = p; ::new (vp) T(v); }\n"
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase
def _size(va):
    code = _pe.get_data(va - _base, 128)
    i = code.index(b"\x8b\x0e")  # mov ecx,[esi]
    j = code.index(b"\x06", i)  # add dword ptr [esi], imm
    return code[j+1] if code[j-1] == 0x83 else struct.unpack("<i", code[j+1:j+5])[0]
def emit(va, A, N):
    size = _size(va)
    s = "S%08x" % va
    r = "R%08x" % va
    i = "I%08x" % va
    src = ("struct %(s)s { char d[0x%(sz)x]; %(s)s(const %(s)s&); };\n"
           "struct %(r)s { %(s)s* p; };\n"
           "struct %(i)s { %(s)s* p; %(s)s& operator*() const { return *p; } %(i)s& operator++() { ++p; return *this; }\n"
           "  bool operator!=(const %(i)s& o) const { return p != o.p; } };\n"
           "%(r)s* FUN_%(va)08x(%(r)s* r, %(i)s first, %(i)s last, %(i)s init) {\n"
           "    r->p = init.p;\n"
           "    for (; first != last; ++first, ++r->p) construct_at_(r->p, *first);\n"
           "    return r;\n}\n") % dict(s=s, r=r, i=i, sz=size, va=va)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@U%s@@11@Z" % (va, r, i)
