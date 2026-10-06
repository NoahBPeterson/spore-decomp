// Slice s009a9600: cSPUILayoutManager / rbtree helpers.
// Reconstructed from the annotated disassembly; real name for the EASTL DoNukeSubtree.
#include "types.h"

// ---------------------------------------------------------------------------
// stubs
// ---------------------------------------------------------------------------
extern void FUN_f47380(void*);              // operator delete(void*) cdecl
struct S9a3630b { int f(); };               // refcount-descend (slice 33)
struct S9ac2a0 { void f(); };
struct S9ae1c0 { void f(); };
struct S99c970 { void f(); };
struct S9ac2b0 { float f(); };
struct S9ae350 { void f(); };
extern void FUN_009a9c00(int, int, int);
extern void __stdcall FUN_009ae350(int, int, int, int);

extern "C" __declspec(dllimport) unsigned long __stdcall
GetFullPathNameA(const char*, unsigned long, char*, char**);

struct S9a9600 { void f(void*); };
struct S9a9640 { void f(); };
struct S9a9b90 { S9a9b90* f(int); };
struct S9aa4c0 { S9aa4c0* f(int*); };
struct S9aa500 { void f(int*, unsigned*); };

// ---------------------------------------------------------------------------
// @ 0x009a9600  eastl::rbtree<...>::DoNukeSubtree
// ---------------------------------------------------------------------------
void S9a9600::f(void* node_) {
  char* node = (char*)node_;
  while (node) {
    ((S9a9600*)this)->f(*(void**)node);
    char* next = *(char**)(node + 4);
    FUN_f47380(node);
    node = next;
  }
}

// ---------------------------------------------------------------------------
// @ 0x009a9640
// ---------------------------------------------------------------------------
void S9a9640::f() {
  char* self = (char*)this;
  int* end = *(int**)(self + 4);
  for (int* p = *(int**)self; p < end; p++) {
    if (*p) ((S9a3630b*)(size_t)*p)->f();
  }
  int v = *(int*)self;
  if (v && *(int*)(v - 4)) FUN_f47380((void*)v);
}

// ---------------------------------------------------------------------------
// @ 0x009a9680  (668 bytes; skeleton)
// ---------------------------------------------------------------------------
struct S9a9680 { void f(); };
void S9a9680::f() {}

// ---------------------------------------------------------------------------
// @ 0x009a9920  (591 bytes; skeleton)
// ---------------------------------------------------------------------------
struct S9a9920 { void f(); };
void S9a9920::f() {}

// ---------------------------------------------------------------------------
// @ 0x009a9b70  GetFullPathNameA wrapper
// ---------------------------------------------------------------------------
unsigned long __cdecl FUN_009a9b70(const char* a, unsigned long b, char* c, char** d) {
  return GetFullPathNameA(a, b, c, d);
}

// ---------------------------------------------------------------------------
// @ 0x009a9b90
// ---------------------------------------------------------------------------
S9a9b90* S9a9b90::f(int p2) {
  int old = *(int*)this;
  if (p2 != old) {
    if (p2) ((S9ac2a0*)(size_t)p2)->f();
    *(int*)this = p2;
    if (old) ((S9ae1c0*)(size_t)old)->f();
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x009a9bc0  three-field strict-less comparator
// ---------------------------------------------------------------------------
bool __stdcall FUN_009a9bc0(unsigned* a, unsigned* b) {
  if (a[0] < b[0]) return true;
  if (a[0] == b[0]) {
    if (a[1] < b[1]) return true;
    if (a[1] == b[1]) return a[3] < b[3];
  }
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x009a9c00  (1949 bytes; skeleton)
// ---------------------------------------------------------------------------
struct S9a9c00 { void f(); };
void S9a9c00::f() {}

// ---------------------------------------------------------------------------
// @ 0x009aa3a0  scale/seek helper (x87; approximate)
// ---------------------------------------------------------------------------
struct S9aa3a0 { void f(int, int, int*, int); };
void S9aa3a0::f(int a, int b, int* p3, int p4) {
  unsigned n = (*p3 == 0) ? 0 : *(unsigned*)(*p3 + 0x10);
  float sc = ((S9ac2b0*)(size_t)p3)->f();
  float frac;
  if (n < 2) frac = 0.0f;
  else frac = ((float)p4 * sc) / (float)(n - 1);
  int fi = (int)frac;
  FUN_009a9c00(a, b, fi);
  FUN_009ae350(p4, fi, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x009aa440
// ---------------------------------------------------------------------------
int FUN_009aa440(int param_1, int* param_2) {
  bool bVar3;
  if (((*(unsigned char*)((char*)param_2 + 0x1ac) & 7) == 4) && param_2[0x8e] == 0)
    bVar3 = false;
  else
    bVar3 = true;
  int iVar1 = *param_2;
  int iVar5 = *(int*)(param_1 + 0x2e8) - *(int*)(param_1 + 0x2e4);
  unsigned uVar2 = *(unsigned*)(iVar1 + 0x440);
  bool al = uVar2 < (unsigned)(iVar5 / 700);
  if (bVar3 && !al) return 1;
  if (!bVar3 && !al) {
    if (*(int*)(iVar1 + 0x1f8) == 0) return 1;
    return 0;
  }
  if (*(unsigned*)(iVar1 + 0x1f8) == uVar2) return 1;
  if (*(int*)(iVar1 + 0x1f8) == 0) return 1;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x009aa4c0
// ---------------------------------------------------------------------------
S9aa4c0* S9aa4c0::f(int* p) {
  int n = *p;
  int old = *(int*)this;
  if (n != old) {
    if (n) ((S99c970*)(size_t)n)->f();
    *(int*)this = n;
    if (old) ((S9a3630b*)(size_t)old)->f();
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x009aa500  rbtree three-field lower_bound
// ---------------------------------------------------------------------------
void S9aa500::f(int* out, unsigned* key) {
  char* head = (char*)this + 4;
  char* parent = head;
  char* node = *(char**)((char*)this + 0xc);
  while (node) {
    unsigned n0 = *(unsigned*)(node + 0x10);
    unsigned n1 = *(unsigned*)(node + 0x14);
    unsigned n3 = *(unsigned*)(node + 0x1c);
    if (n0 < key[0] || (n0 == key[0] && (n1 < key[1] || (n1 == key[1] && n3 < key[3]))))
      node = *(char**)node;
    else { parent = node; node = *(char**)(node + 4); }
  }
  if (parent != head && *(unsigned*)(parent + 0x10) <= key[0] &&
      (key[0] != *(unsigned*)(parent + 0x10) ||
       (*(unsigned*)(parent + 0x14) <= key[1] &&
        (key[1] != *(unsigned*)(parent + 0x14) || *(unsigned*)(parent + 0x1c) <= key[3]))))
    *out = (int)(size_t)parent;
  else
    *out = (int)(size_t)head;
}
