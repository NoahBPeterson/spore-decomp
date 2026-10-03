# Serialize-a-vector helper (16 instances, element stride varies): bool f(Ar* ar, const char* name, Vec* v)
# If the vector is non-empty: build a wide-string name (cond ? Convert(name,-1) : S16(0), copy-constructed into w;
# branch temps destroyed via the ?: flag bits), ar->Begin(name or L"list"), loop `ok = ok && Item(ar,0,p)`, ar->End(...).
# Strings are 16 bytes (3 pointers + allocator). Needs no /EHsc (no EH frame in original).
# Status: NOT byte-exact. Closest spelling leaves ~52 diff bytes: the original lowers the two `?:` name selects as
# late branch-pushes (vtable load first, then cmp/je push ebp / push L"list") while cl folds them through eax.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov ecx, dword ptr [esi] ; push edi ; xor edi, edi ; mov al, N ; mov dword ptr [esp + N], edi ; mov byte ptr [esp + N], al ; cmp ecx, dword ptr [esi + N] ; je +N ; mov eax, dword ptr [esp + N] ; push ebx ; push ebp ; cmp eax, edi ; je +N ; push -N ; push eax ; lea edx, [esp + N] ; push edx ; lea ebx, [edi + N] ; call EXT ; add esp, N ; jmp +N ; push edi ; lea ecx, [esp + N] ; mov ebx, N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; call EXT ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test bl, N ; je +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; and ebx, A ; cmp ecx, N ; jle +N ; cmp eax, edi ; je +N ; push eax ; call EXT ; add esp, N ; test bl, N ; je +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub edx, eax ; and edx, A ; cmp edx, N ; jle +N ; cmp eax, edi ; je +N ; push eax ; call EXT ; add esp, N ; mov edi, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax] ; mov ecx, edi ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebp ; jmp +N ; push A ; call edx ; mov eax, dword ptr [esp + N] ; mov esi, dword ptr [esi] ; mov ebx, dword ptr [eax + N] ; cmp esi, ebx ; je +N ; mov edi, edi ; cmp byte ptr [esp + N], N ; je +N ; push esi ; push N ; push edi ; call EXT ; add esp, N ; mov byte ptr [esp + N], N ; test al, al ; jne +N ; mov byte ptr [esp + N], N ; add esi, N ; cmp esi, ebx ; jne +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebp ; jmp +N ; push A ; call eax ; mov ecx, dword ptr [esp + N] ; sub ecx, ebp ; and ecx, A ; cmp ecx, N ; jle +N ; test ebp, ebp ; je +N ; push ebp ; call EXT ; add esp, N ; mov al, byte ptr [esp + N] ; pop ebp ; pop ebx ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
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
bool __cdecl I_@V(Ar* ar, int z, E_@V* e);
bool F_@V(Ar* ar, const char* name, V_@V* v) {
  bool ok = true;
  if (v->b != v->e) {
    S16n w(name ? Convert(name, -1) : S16((const wchar_t*)0));
    wchar_t* nm = w.b;
    ar->Begin(nm != w.e ? nm : L"list");
    E_@V* q = v->e; for (E_@V* p = v->b; p != q; ++p) ok = ok && I_@V(ar, 0, p);
    ar->End(nm != w.e ? nm : L"list");
    if ((w.c - nm) > 1 && nm) S16::dealloc(nm);
  }
  return ok;
}"""

def emit(va, A, N):
    v = "%08x" % va
    src = TPL.replace("@V", v).replace("@S", str(N[-8]))
    return src, "?F_%s@@YA_NPAUAr@@PBDPAUV_%s@@@Z" % (v, v)
