# Serialize-a-vector-of-u32-sized-items helper with a type-name arg (9 instances): bool f(Ar* ar, const char* name, Vec* v)
# Status: NOT byte-exact; closest spelling leaves ~25 diff bytes (orig loads nm before the vtable and reloads arg3 for v->e).
# Same shape as serialize_vec_wstr_name but the per-item call takes a 4th arg: the wide type name (e.g. L"uint32_t").
import os, pefile
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov ecx, dword ptr [esi] ; push edi ; xor edi, edi ; mov al, N ; mov dword ptr [esp + N], edi ; mov byte ptr [esp + N], al ; cmp ecx, dword ptr [esi + N] ; je +N ; mov eax, dword ptr [esp + N] ; push ebx ; push ebp ; cmp eax, edi ; je +N ; push -N ; push eax ; lea edx, [esp + N] ; push edx ; lea ebx, [edi + N] ; call EXT ; add esp, N ; jmp +N ; push edi ; lea ecx, [esp + N] ; mov ebx, N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; call EXT ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test bl, N ; je +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; and ebx, A ; cmp ecx, N ; jle +N ; cmp eax, edi ; je +N ; push eax ; call EXT ; add esp, N ; test bl, N ; je +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub edx, eax ; and edx, A ; cmp edx, N ; jle +N ; cmp eax, edi ; je +N ; push eax ; call EXT ; add esp, N ; mov edi, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax] ; mov ecx, edi ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebp ; jmp +N ; push A ; call edx ; mov eax, dword ptr [esp + N] ; mov esi, dword ptr [esi] ; mov ebx, dword ptr [eax + N] ; cmp esi, ebx ; je +N ; mov edi, edi ; cmp byte ptr [esp + N], N ; je +N ; push A ; push esi ; push N ; push edi ; call EXT ; add esp, N ; mov byte ptr [esp + N], N ; test al, al ; jne +N ; mov byte ptr [esp + N], N ; add esi, N ; cmp esi, ebx ; jne +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebp ; jmp +N ; push A ; call eax ; mov ecx, dword ptr [esp + N] ; sub ecx, ebp ; and ecx, A ; cmp ecx, N ; jle +N ; test ebp, ebp ; je +N ; push ebp ; call EXT ; add esp, N ; mov al, byte ptr [esp + N] ; pop ebp ; pop ebx ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
_pe = pefile.PE(os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../work/SporeApp.analysis.bin"), fast_load=True)
def _wstr(a):
    d = _pe.get_data(a - _pe.OPTIONAL_HEADER.ImageBase, 128)
    s = d.decode("utf-16-le", "ignore").split("\0")[0]
    return "".join(c if c.isalnum() or c in "_:" else "_" for c in s)
PRELUDE = """struct S16 {
  wchar_t* b; wchar_t* e; wchar_t* c; int al;
  void init(const wchar_t* s);
  S16() : b(0), e(0), c(0) {}
  S16(const wchar_t* s) : b(0), e(0), c(0) { init(s); }
  ~S16() { if ((c - b) > 1 && b) dealloc(b); }
  static void __cdecl dealloc(void*);
};
struct S16n { wchar_t* b; wchar_t* e; wchar_t* c; int al; S16n(const S16& o); };
S16 __cdecl Convert(const char* s, int n);
struct Ar { virtual void Begin(wchar_t*); virtual void End(wchar_t*); };
"""
TPL = """struct E_@V { char d[@S]; };
struct V_@V { E_@V* b; E_@V* e; };
bool __cdecl I_@V(Ar* ar, int z, E_@V* e, const wchar_t* tn);
bool F_@V(Ar* ar, const char* name, V_@V* v) {
  bool ok = true;
  if (v->b != v->e) {
    S16n w(name ? Convert(name, -1) : S16((const wchar_t*)0));
    wchar_t* nm = w.b;
    if (nm != w.e) ar->Begin(nm); else ar->Begin(L"list");
    E_@V* q = v->e; for (E_@V* p = v->b; p != q; ++p) ok = ok && I_@V(ar, 0, p, L"@T");
    if (nm != w.e) ar->End(nm); else ar->End(L"list");
    if ((w.c - nm) > 1 && nm) S16::dealloc(nm);
  }
  return ok;
}"""
def emit(va, A, N):
    v = "%08x" % va
    src = TPL.replace("@V", v).replace("@S", str(N[-8])).replace("@T", _wstr(A[4]))
    return src, "?F_%s@@YA_NPAUAr@@PBDPAUV_%s@@@Z" % (v, v)
