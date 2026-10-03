# Read bool bits through chained vcalls into a bit mask, limit N bits.
PATTERN = 'push ecx ; push ebp ; mov ebp, dword ptr [esp + N] ; mov eax, dword ptr [ebp] ; mov edx, dword ptr [eax + N] ; push esi ; mov ecx, ebp ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; xor esi, esi ; add esp, N ; cmp dword ptr [esp + N], esi ; jle +N ; push edi ; mov edi, dword ptr [esp + N] ; lea esp, [esp] ; mov edx, dword ptr [ebp] ; mov eax, dword ptr [edx + N] ; mov ecx, ebp ; mov byte ptr [esp + N], N ; call eax ; mov edx, dword ptr [eax] ; lea ecx, [esp + N] ; push ecx ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push eax ; call EXT ; add esp, N ; cmp esi, N ; jae +N ; mov ecx, esi ; and ecx, N ; cmp byte ptr [esp + N], N ; je +N ; mov edx, N ; shl edx, cl ; or dword ptr [edi], edx ; jmp +N ; mov eax, N ; shl eax, cl ; not eax ; and dword ptr [edi], eax ; inc esi ; cmp esi, dword ptr [esp + N] ; jl +N ; pop edi ; pop esi ; mov eax, ebp ; pop ebp ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
struct Inner { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5();
  virtual void* get(bool* b); };
struct Mid2x { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5();
  virtual void* get(); };
struct Mid { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5();
  virtual void* get(); };
struct Stream { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual Mid* sub(); };
"""
def emit(va, A, N):
    lim = N[15]
    src = """extern "C" void __cdecl ext_count(void*, int*, int, int);
extern "C" void __cdecl ext_bool(void*, bool*);
Stream* __cdecl FUN_%08x(Stream* s, u32* out) {
    int n;
    void* h = s->sub()->get();
    ext_count(h, &n, 1, 0);
    for (int i = 0; i < n; i++) {
        bool b = false;
        ext_bool(((Mid2x*)s->sub())->get(), &b);
        if ((u32)i < %du) {
            if (b) *out |= 1u << (i & 31);
            else *out &= ~(1u << (i & 31));
        }
    }
    return s;
}""" % (va, lim)
    return src, "?FUN_%08x@@YAPAUStream@@PAU1@PAI@Z" % va
