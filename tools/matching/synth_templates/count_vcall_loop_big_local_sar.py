# Serialize-style (pow2 stride): n=(end-begin)>>k; ext(self->v8()->v6(), &n,1,0); per elem: Obj o(elem,g,k); o.f(self); self->v7() tailcall.
PATTERN = 'sub esp, N ; push ebx ; mov ebx, dword ptr [esp + N] ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, dword ptr [edi + N] ; sub esi, dword ptr [edi] ; mov ecx, ebx ; sar esi, N ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], esi ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; mov esi, dword ptr [edi] ; mov edi, dword ptr [edi + N] ; add esp, N ; cmp esi, edi ; je +N ; push A ; push A ; push esi ; lea ecx, [esp + N] ; call EXT ; push ebx ; lea ecx, [esp + N] ; call EXT ; add esi, N ; cmp esi, edi ; jne +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx + N] ; pop edi ; pop esi ; mov ecx, ebx ; pop ebx ; add esp, N ; jmp eax'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    stride = N[-3]
    pad = (N[0] - 4) // 4
    t = "%08x" % va
    src = f"""
struct Mid_{t} {{ virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5(); virtual void* m6(); }};
struct Self_{t} {{
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void v7(); virtual Mid_{t}* v8();
}};
struct Elem_{t} {{ char d[{stride}]; }};
struct Vec_{t} {{ Elem_{t}* b; Elem_{t}* e; }};
struct Obj_{t} {{ Obj_{t}(const void*, const void*, const void*); void f(Self_{t}*); unsigned int pad[{pad}]; }};
extern "C" __declspec(noalias) void ext_{t}(void*, void*, int, int);
extern char g_{A[-1]:08x};
extern char g_{A[-2]:08x};
void FUN_{t}(Self_{t}* self, Vec_{t}* v) {{
  int n = v->e - v->b;
  Mid_{t}* m = self->v8();
  int k = n;
  void* r = m->m6();
  ext_{t}(r, &k, 1, 0);
  for (Elem_{t}* p = v->b, *e = v->e; p != e; ++p) {{
    Obj_{t} o(p, &g_{A[-1]:08x}, &g_{A[-2]:08x});
    o.f(self);
  }}
  self->v7();
}}
"""
    return src, "?FUN_%08x@@YAXPAUSelf_%08x@@PAUVec_%08x@@@Z" % (va, va, va)
