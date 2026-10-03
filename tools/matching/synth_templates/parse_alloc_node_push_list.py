# bool __thiscall f(Node** list): if (Parse(&str, &ctx)) { n = Alloc(this->f4c, Desc{fn,0,0,0}, ctx); n->next=*list; *list=n; return true; }
# Callees decoded from the two calls (+0x10 and +0x3d).
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va, off):
    rel = struct.unpack("<i", _pe.get_data(va + off + 1 - _base, 4))[0]
    return va + off + 5 + rel

PATTERN = 'push ecx ; push ebx ; push esi ; push edi ; lea eax, [esp + N] ; push eax ; push A ; mov ebx, ecx ; call EXT ; test al, al ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; sub esp, N ; mov eax, esp ; mov ecx, A ; mov dword ptr [eax], ecx ; mov ecx, dword ptr [ebx + N] ; xor edx, edx ; mov dword ptr [eax + N], edx ; xor esi, esi ; xor edi, edi ; mov dword ptr [eax + N], esi ; push ecx ; mov dword ptr [eax + N], edi ; call EXT ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax + N], edx ; mov dword ptr [ecx], eax ; add esp, N ; mov al, N ; pop edi ; pop esi ; pop ebx ; pop ecx ; ret N ; pop edi ; pop esi ; xor al, al ; pop ebx ; pop ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Desc { void* fn; int a, b, c; };
struct Node { void* x; Node* next; };
struct Ctx;
"""

def emit(va, A, N):
    p = _callee(va, 0x10); q = _callee(va, 0x3d)
    src = ("bool __fastcall FUN_%08x_P(struct Obj*, int, const void*, Ctx**);\n"  # placeholder, replaced below
           % va)
    src = ("""struct Obj%(v)08x { char pad[0x4c]; int f4c; bool __thiscall run(Node** list); bool __thiscall FUN_%(p)08x(const void*, Ctx**); };
Node* __cdecl FUN_%(q)08x(int, Desc, Ctx*);
extern char g_%(s)08x[];
bool Obj%(v)08x::run(Node** list) {
  Ctx* c;
  if (this->FUN_%(p)08x(g_%(s)08x, &c)) {
    Desc d = { (void*)0x%(f)08xu, 0, 0, 0 };
    Node* n = FUN_%(q)08x(f4c, d, c);
    n->next = *list; *list = n; return true;
  }
  return false;
}""" % dict(v=va, p=p, q=q, s=A[0], f=A[1]))
    return src, "?run@Obj%08x@@QAE_NPAPAUNode@@@Z" % va
