# Function-local static fixed-buffer vector (inline ctor + atexit dtor, MSVC guard bit) used as a
# key when a global key is null; then a stdcall virtual call on a global service (slot 94 / 109).
import re
PATTERN = 'mov eax, dword ptr [A] ; push esi ; test eax, eax ; je +N ; cmp dword ptr [esp + N], N ; mov esi, dword ptr [esp + N] ; mov ecx, dword ptr [A] ; mov edx, dword ptr [ecx] ; push esi ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; push ecx ; je +N ; mov ecx, dword ptr [edx + N] ; call ecx ; pop esi ; ret  ; mov ecx, dword ptr [edx + N] ; call ecx ; pop esi ; ret  ; mov eax, N ; test byte ptr [A], al ; jne +N ; or dword ptr [A], eax ; mov eax, A ; push A ; mov dword ptr [A], eax ; mov dword ptr [A], eax ; mov dword ptr [A], eax ; mov dword ptr [A], A ; call EXT ; add esp, N ; mov esi, dword ptr [esp + N] ; push A ; push esi ; mov ecx, A ; call EXT ; cmp dword ptr [esp + N], N ; mov eax, dword ptr [A] ; push esi ; je +N ; mov ecx, dword ptr [A] ; mov edx, dword ptr [eax] ; mov edx, dword ptr [edx + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; push ecx ; push eax ; call edx ; pop esi ; ret  ; mov edx, dword ptr [A] ; mov ecx, dword ptr [eax] ; push edx ; mov edx, dword ptr [esp + N] ; push edx ; push eax ; mov eax, dword ptr [ecx + N] ; call eax ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Vec {
  void *b, *e, *cap; int al; void *p; int pad; char buf[0x100];
  Vec() { p = buf; e = buf; b = buf; cap = buf + 0x100; }
  ~Vec();
  void init(int a, const void *k);
};
typedef void (__stdcall *F)(void*, int, int, int);
struct Sv { F *vt; };
extern Sv *g_svc;
"""
def emit(va, A, N):
    key, svc, d = A[0], A[1], A[11]
    s1, s2 = N[4] // 4, N[5] // 4
    src = """extern int g_%08x; extern char g_%08x[];
void FUN_%08x(int a, int b, int c) {
  if (g_%08x) {
    if (c) g_svc->vt[%d](g_svc, a, g_%08x, b);
    else g_svc->vt[%d](g_svc, a, g_%08x, b);
    return;
  }
  static Vec v;
  v.init(b, g_%08x);
  if (c) g_svc->vt[%d](g_svc, a, (int)v.b, b);
  else g_svc->vt[%d](g_svc, a, (int)v.b, b);
}""" % (key, d, va, key, s1, key, s2, key, d, s1, s2)
    return src, "?FUN_%08x@@YAXHHH@Z" % va
