# cdecl bool f(O* o, void* a, int x, void* b): optional a/b locked via vfunc[0], ext(o,a,x,b), then unlocked via vfunc[1] (b, then a)
import os, struct
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov al, N ; test ebx, ebx ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; push ebx ; mov ecx, esi ; call edx ; test al, al ; setne al ; push edi ; mov edi, dword ptr [esp + N] ; test edi, edi ; je +N ; test al, al ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; push edi ; mov ecx, esi ; call edx ; test al, al ; jne +N ; xor al, al ; test edi, edi ; je +N ; test al, al ; je +N ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edx + N] ; push edi ; mov ecx, esi ; call eax ; test al, al ; je +N ; mov al, N ; jmp +N ; test al, al ; je +N ; mov eax, dword ptr [esp + N] ; push edi ; push eax ; push ebx ; push esi ; call EXT ; add esp, N ; test al, al ; je +N ; mov al, N ; jmp +N ; xor al, al ; pop edi ; test ebx, ebx ; je +N ; test al, al ; je +N ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edx + N] ; push ebx ; mov ecx, esi ; call eax ; test al, al ; je +N ; pop esi ; mov al, N ; pop ebx ; ret  ; xor al, al ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
_IMG = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../work/SporeApp.analysis.bin")
def _ext(va):
    import pefile
    pe = pefile.PE(_IMG, fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    code = pe.get_data(va - base, 147)
    i = code.index(b"\xe8", 0x58)
    return (va + i + 5 + struct.unpack("<i", code[i+1:i+5])[0]) & 0xffffffff
def emit(va, A, N):
    t = _ext(va)
    name = "FUN_%08x" % va
    src = ("struct O_%08x { virtual bool v0(void*); virtual bool v1(void*); };\n"
           "bool FUN_%08x(O_%08x*, void*, int, void*);\n"
           "bool %s(O_%08x* o, void* a, int x, void* b) {\n"
           "  bool r = true;\n  if (a) r = o->v0(a) != 0;\n  if (b) r = r && o->v0(b);\n"
           "  bool s = r && FUN_%08x(o, a, x, b);\n  if (b) s = s && o->v1(b);\n  if (a) s = s && o->v1(a);\n  return s;\n}"
           % (va, t, va, name, va, t))
    return src, "?%s@@YA_NPAUO_%08x@@PAXH1@Z" % (name, va)
