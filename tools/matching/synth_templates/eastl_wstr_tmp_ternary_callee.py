# Pattern 633 (5 instances): bool F(A1* a, const wchar16* p, void* x): if x, s = p ? Mk(p,-1) : WString();
# return Callee(a, s.empty()?0:s.begin, x, L"name"). NOT byte-exact: structure identical, but orig keeps
# the default temp's begin/cap in edi/esi and x in ebp; ours reloads from the stack and uses esi for x.
PATTERN = 'sub esp, N ; push ebp ; mov ebp, dword ptr [esp + N] ; mov dword ptr [esp + N], N ; test ebp, ebp ; je +N ; mov eax, dword ptr [esp + N] ; push ebx ; push esi ; push edi ; test eax, eax ; je +N ; push -N ; push eax ; lea eax, [esp + N] ; push eax ; mov ebx, N ; call EXT ; mov esi, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; add esp, N ; jmp +N ; mov edi, A ; mov esi, A ; mov ebx, N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], esi ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test bl, N ; je +N ; sub esi, edi ; and esi, A ; and ebx, A ; cmp esi, N ; jle +N ; test edi, edi ; je +N ; push edi ; call EXT ; add esp, N ; test bl, N ; je +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; mov esi, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov eax, esi ; sub eax, dword ptr [esp + N] ; push A ; neg eax ; sbb eax, eax ; and eax, esi ; push ebp ; push eax ; push edx ; call EXT ; mov bl, al ; mov eax, dword ptr [esp + N] ; sub eax, esi ; and eax, A ; add esp, N ; cmp eax, N ; jle +N ; test esi, esi ; je +N ; push esi ; call EXT ; add esp, N ; pop edi ; pop esi ; mov al, bl ; pop ebx ; pop ebp ; add esp, N ; ret  ; mov al, N ; pop ebp ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = """typedef unsigned short wchar16;
void EASTL_allocator_deallocate(void* p);
extern char sEmpty8[];
struct Alloc2 { const char* mpName; };
struct WString {
    wchar16* mpBegin; wchar16* mpEnd; wchar16* mpCap; Alloc2 a;
    WString(): mpBegin((wchar16*)sEmpty8), mpEnd((wchar16*)sEmpty8), mpCap((wchar16*)(sEmpty8+2)) {}
    WString(const WString&);
    ~WString() { if ((mpCap - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin); }
};
WString Mk(const wchar16*, int);
struct A1;
"""
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
    cal = "Callee_%08x" % c[4]
    nm = "g_%08x" % A[2]
    src = ("extern const wchar_t %s[];\nbool %s(A1*, const wchar16*, void*, const wchar_t*);\n"
           "bool FUN_%08x(A1* a, const wchar16* p, void* x) {\n"
           "    if (!x) return true;\n"
           "    WString s(p ? Mk(p, -1) : WString());\n"
           "    return %s(a, s.mpBegin != s.mpEnd ? s.mpBegin : 0, x, %s);\n}\n") % (nm, cal, va, cal, nm)
    return src, "?FUN_%08x@@YA_NPAUA1@@PBGPAX@Z" % va
