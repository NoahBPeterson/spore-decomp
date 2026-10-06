// Slice s009a2c90: creature-animation helper functions.
// Reconstructed from the annotated disassembly.
#include "types.h"
#pragma inline_depth(0)

// ---------------------------------------------------------------------------
// stubs
// ---------------------------------------------------------------------------
struct S99d060 { void f(); };
extern void FUN_009a1d90(int, float, int, int);
extern int  FUN_009a1c20(int, int, int);
extern int  FUN_0067cb20();
extern int  FUN_921580(int);
extern int* g_166c058;
extern int* g_166c05c;
extern void FUN_f47380(void*);

struct S9a1b00 { int f(int, int); };
struct S9a2f80 { int f(int, int); };
struct S9a3760 { void f(int*, unsigned*); };
struct S9a3820 { void f(int*, unsigned*); };
struct S9a3c40 { void f(void*); };
struct Rbtree99 { int find(int*, int*); };
struct S9a1770 { void f(int); };
struct S9a2d50 { void f(int, int, int); };
struct S9a3080 { void f(int); };
struct S99f0b0 { void f(); };
struct S9c4cc0 { void f(); };
struct S9a35b0 { void f(); };
struct S9a3630 { int f(); };
struct S9a2cc0 { bool f(int); };
struct S9a2fd0 { void f(unsigned); };
extern void FUN_009a80e0(void*);
extern int  FUN_009a1530();
extern void FUN_009a0df0();
extern int g_15504e0;
extern int g_166b260;
extern void* __cdecl operator_new(int, const char*, int, int, const char*, int);
extern void __cdecl FUN_9216a0(void*, void*, void*, int);
struct S9b3450 { void f(); };
struct S99c980 { void f(); };
struct S99c660 { void f(); };
struct S9c26a0 { void f(); };
struct S9a3890 { void* f(int*); };
struct S9a3980 { void f(int*, char*, unsigned*, char); };
struct S9a3a10 { void f(int*, int, unsigned*, char); };
struct S9a38f0 { bool f(int, int, int*); };
struct S9a34a0 { S9a34a0* f(); };

// ---------------------------------------------------------------------------
// @ 0x009a3890
// ---------------------------------------------------------------------------
__declspec(noinline) void* S9a3890::f(int* param_1) {
  char* n = (char*)operator_new(
      0x1c, "EASTL", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (n + 0x10) {
    int v = *param_1;
    *(int*)(n + 0x10) = v;
    if (v) ((S9b3450*)(size_t)v)->f();
    *(int*)(n + 0x14) = param_1[1];
    int w = param_1[2];
    *(int*)(n + 0x18) = w;
    if (w) ((S99c980*)(size_t)w)->f();
  }
  return n;
}

// ---------------------------------------------------------------------------
// @ 0x009a38f0
// ---------------------------------------------------------------------------
__declspec(noinline) bool S9a38f0::f(int a, int b, int* out) {
  int key[2];
  key[0] = a; key[1] = b;
  if (a) ((S9b3450*)(size_t)a)->f();
  int found;
  ((S9a3820*)g_166c05c)->f(&found, (unsigned*)key);
  if (a) ((S9c26a0*)(size_t)a)->f();
  if ((char*)found != (char*)g_166c05c + 4) {
    if (out) {
      if (*(int*)(found + 0x18)) ((S99c980*)*(int*)(found + 0x18))->f();
      *out = *(int*)(found + 0x18);
    }
    return true;
  }
  if (out) *out = 0;
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x009a3980
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a3980::f(int* out, char* node, unsigned* key, char param5) {
  int b = 0;
  if (param5 == 0 && node != (char*)this + 4 && *(unsigned*)(node + 0x10) <= *key) b = 1;
  char* n = (char*)operator_new(
      0x18, "EASTL", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (n + 0x10) {
    *(unsigned*)(n + 0x10) = *key;
    unsigned v = key[1];
    *(unsigned*)(n + 0x14) = v;
    if (v) ((S99c660*)(size_t)v)->f();
  }
  FUN_9216a0(n, node, (char*)this + 4, b);
  *(int*)((char*)this + 0x14) += 1;
  *out = (int)(size_t)n;
}

// ---------------------------------------------------------------------------
// @ 0x009a3a10
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a3a10::f(int* out, int node, unsigned* key, char param5) {
  int b = 0;
  if (param5 == 0 && node != (int)((char*)this + 4) && *(unsigned*)(node + 0x10) <= *key &&
      (*(unsigned*)(node + 0x10) < *key || *(unsigned*)(node + 0x14) <= key[1])) b = 1;
  int n = (int)(size_t)((S9a3890*)this)->f((int*)key);
  FUN_9216a0((void*)(size_t)n, (void*)(size_t)node, (char*)this + 4, b);
  *(int*)((char*)this + 0x14) += 1;
  *out = n;
}

// ---------------------------------------------------------------------------
// @ 0x009a34a0  animation-object init
// ---------------------------------------------------------------------------
__declspec(noinline) S9a34a0* S9a34a0::f() {
  char* self = (char*)this;
  *(int*)(self + 0) = 0;
  for (int off = 0x2c; off <= 0x70; off += 4) *(float*)(self + off) = 0.0f;
  *(float*)(self + 0x7c) = 0.0f; *(float*)(self + 0x78) = 0.0f; *(float*)(self + 0x74) = 0.0f;
  *(int*)(self + 4) = 0;
  *(float*)(self + 0x88) = 0.0f; *(float*)(self + 0x84) = 0.0f; *(float*)(self + 0x80) = 0.0f;
  *(float*)(self + 0x8c) = 1.0f;
  *(int*)(self + 8) = 0;
  *(float*)(self + 0x98) = 0.0f; *(float*)(self + 0x94) = 0.0f; *(float*)(self + 0x90) = 0.0f;
  *(int*)(self + 0x18) = 0; *(int*)(self + 0x1c) = 0; *(int*)(self + 0x20) = 0;
  *(float*)(self + 0xa4) = 0.0f; *(float*)(self + 0xa0) = 0.0f; *(float*)(self + 0x9c) = 0.0f;
  *(float*)(self + 0xa8) = 1.0f;
  *(int*)(self + 0xc8) = 0; *(int*)(self + 0xcc) = 0; *(int*)(self + 0xd0) = 0;
  *(int*)(self + 0xdc) = 0;
  ((S9a3080*)self)->f(1);
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x009a2cc0
// ---------------------------------------------------------------------------
__declspec(noinline) bool S9a2cc0::f(int p2) {
  char* self = (char*)this;
  *(unsigned char*)(self + 0xac) = 0;
  ((S9a1770*)(self + 0xc8))->f(0);
  FUN_009a80e0(self);
  if (*(int*)self == 0) return false;
  *(int*)(self + 0xc) = p2;
  *(int*)(self + 0x10) = g_15504e0;
  g_15504e0 += 1;
  *(int*)(*(int*)self + 0x12c) = g_166b260;
  g_166b260 += 1;
  *(double*)(self + 0xb0) = 0.0;
  *(int*)(self + 0xc0) += 1;
  *(unsigned char*)(self + 0xac) = 1;
  *(int*)(self + 0xc4) = 0;
  FUN_009a1d90((int)(size_t)self, 0.0f, 1, 1);
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x009a2fd0
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a2fd0::f(unsigned p2) {
  char* self = (char*)this;
  int count = (*(int*)(self + 4) - *(int*)self) / 0x1f0;
  if ((unsigned)count < p2) {
    int tmp = FUN_009a1530();
    ((S9a2d50*)self)->f(*(int*)(self + 4), (int)(p2 - count), tmp);
    FUN_009a0df0();
  } else {
    ((S9a2f80*)self)->f((int)(p2 * 0x1f0 + *(int*)self), *(int*)(self + 4));
  }
}

// ---------------------------------------------------------------------------
// @ 0x009a35b0
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a35b0::f() {
  char* self = (char*)this;
  ((S9a3080*)self)->f(1);
  int v = *(int*)(self + 0xc8);
  if (v && *(int*)(v - 4)) FUN_f47380((void*)v);
  char* sub = self + 0x18;
  ((S9a1b00*)sub)->f(*(int*)sub, *(int*)(sub + 4));
  int v2 = *(int*)sub;
  if (v2 && *(int*)(v2 - 4)) FUN_f47380((void*)v2);
  if (*(int*)(self + 8)) ((S99f0b0*)*(int*)(self + 8))->f();
  if (*(int*)(self + 4)) ((S9c4cc0*)*(int*)(self + 4))->f();
  if (*(int*)self) ((S99d060*)*(int*)self)->f();
}

// ---------------------------------------------------------------------------
// @ 0x009a3630
// ---------------------------------------------------------------------------
__declspec(noinline) int S9a3630::f() {
  char* self = (char*)this;
  int local[2];
  local[0] = *(int*)(self + 0xdc) - 1;
  local[1] = 0;
  int* p = (local[0] < 1) ? &local[1] : &local[0];
  int v = *p;
  *(int*)(self + 0xdc) = v;
  if (v < 1) {
    *(int*)(self + 0xdc) = 1;
    ((S9a35b0*)self)->f();
    FUN_f47380(self);
    v = 0;
  }
  return v;
}

// ---------------------------------------------------------------------------
// @ 0x009a36a0  binary-heap sift up
// ---------------------------------------------------------------------------
__declspec(noinline) void FUN_009a36a0(int* arr, int start, int pos, int item, int extra) {
  (void)extra;
  int parent = (pos - 1) >> 1;
  if (pos <= start) { arr[pos] = item; return; }
  do {
    int v = arr[parent];
    if (*(unsigned*)(v + 0x12c) <= *(unsigned*)(item + 0x12c)) break;
    arr[pos] = v;
    pos = parent;
    parent = (parent - 1) >> 1;
  } while (pos > start);
  arr[pos] = item;
}

// ---------------------------------------------------------------------------
// @ 0x009a36f0  binary-heap sift down
// ---------------------------------------------------------------------------
__declspec(noinline) void FUN_009a36f0(int* arr, int start, int end, int pos, int a5, int a6) {
  int p = pos;
  int child = p * 2 + 2;
  if (child < end) {
    do {
      int* base = (int*)((char*)arr - 4);
      int left = base[child];
      int right = arr[child];
      if (*(unsigned*)(right + 0x12c) > *(unsigned*)(left + 0x12c)) child--;
      arr[p] = arr[child];
      p = child;
      child = p * 2 + 2;
    } while (child < end);
  }
  if (child == end) { arr[p] = arr[child - 1]; p = child - 1; }
  FUN_009a36a0(arr, start, p, a5, a6);
}

// ---------------------------------------------------------------------------
// @ 0x009a2c90  add a double field and forward to FUN_009a1d90
// ---------------------------------------------------------------------------
__declspec(noinline) void FUN_009a2c90(int a, float b, int c, int d) {
  FUN_009a1d90(a, b + (float)*(double*)(a + 0xb0), c, d);
}

// ---------------------------------------------------------------------------
// @ 0x009a2f80
// ---------------------------------------------------------------------------
__declspec(noinline) int S9a2f80::f(int p2, int p3) {
  char* self = (char*)this;
  int r = FUN_009a1c20(p3, *(int*)(self + 4), p2);
  ((S9a1b00*)self)->f(r, *(int*)(self + 4));
  int diff = p3 - p2;
  int v = (int)(((long long)diff * 0x7bdef7bdLL) >> 32) - diff;
  v >>= 8;
  v = (int)((unsigned)v >> 31) + v;
  *(int*)(self + 4) += v * 0x1f0;
  return p2;
}

// ---------------------------------------------------------------------------
// @ 0x009a3680
// ---------------------------------------------------------------------------
__declspec(noinline) bool FUN_009a3680(int a, int b) {
  (void)a;
  if (FUN_0067cb20()) {
    void* p = (void*)(size_t)FUN_0067cb20();
    ((void(__thiscall*)(void*, int))((void**)(*(void***)p))[0xc])(p, b);
  }
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x009a3760
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a3760::f(int* out, unsigned* key) {
  unsigned k0 = key[0], k1 = key[1];
  char* head = (char*)this + 4;
  char* parent = head;
  char* node = *(char**)((char*)this + 0xc);
  while (node) {
    unsigned n0 = *(unsigned*)(node + 0x10);
    unsigned n1 = *(unsigned*)(node + 0x14);
    if (k0 > n0 || (k0 == n0 && k1 < n1)) node = *(char**)node;
    else { parent = node; node = *(char**)(node + 4); }
  }
  *out = (int)(size_t)parent;
}

// ---------------------------------------------------------------------------
// @ 0x009a37a0
// ---------------------------------------------------------------------------
__declspec(noinline) int FUN_009a37a0(int key) {
  int local;
  int* tree = g_166c058;
  ((Rbtree99*)tree)->find(&local, &key);
  if ((char*)local != (char*)tree + 4) return *(int*)((char*)(size_t)local + 0x14);
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x009a37e0
// ---------------------------------------------------------------------------
__declspec(noinline) int FUN_009a37e0(int key) {
  if (!key) return 0;
  int count = 0;
  int* tree = g_166c05c;
  char* end = (char*)tree + 4;
  for (char* node = *(char**)((char*)tree + 8); node != end; node = (char*)(size_t)FUN_921580((int)(size_t)node))
    if (*(int*)(node + 0x10) == key) count++;
  return count;
}

// ---------------------------------------------------------------------------
// @ 0x009a3820
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a3820::f(int* out, unsigned* key) {
  unsigned k0 = key[0], k1 = key[1];
  char* head = (char*)this + 4;
  char* parent = head;
  char* node = *(char**)((char*)this + 0xc);
  while (node) {
    unsigned n0 = *(unsigned*)(node + 0x10);
    unsigned n1 = *(unsigned*)(node + 0x14);
    if (k0 > n0 || (k0 == n0 && k1 < n1)) node = *(char**)node;
    else { parent = node; node = *(char**)(node + 4); }
  }
  if (parent != head && *(unsigned*)(parent + 0x10) <= k0 &&
      (*(unsigned*)(parent + 0x10) < k0 || *(unsigned*)(parent + 0x14) <= k1))
    *out = (int)(size_t)parent;
  else
    *out = (int)(size_t)head;
}

// ---------------------------------------------------------------------------
// @ 0x009a2d50  vector grow/copy (554 bytes; skeleton)
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a2d50::f(int a, int b, int c) { (void)a; (void)b; (void)c; }

// ---------------------------------------------------------------------------
// @ 0x009a3080  (413 bytes; skeleton)
// ---------------------------------------------------------------------------
volatile int g_op_9a3080;
__declspec(noinline) void S9a3080::f(int a) { g_op_9a3080 = a; }

// ---------------------------------------------------------------------------
// @ 0x009a3220  (631 bytes; skeleton)
// ---------------------------------------------------------------------------
struct S9a3220 { void f(); };
__declspec(noinline) void S9a3220::f() {}

// ---------------------------------------------------------------------------
// @ 0x009a3b10  (302 bytes; skeleton)
// ---------------------------------------------------------------------------
struct S9a3b10 { void f(); };
__declspec(noinline) void S9a3b10::f() {}

// ---------------------------------------------------------------------------
// @ 0x009a3c40  recursive tree delete
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a3c40::f(void* node_) {
  char* node = (char*)node_;
  while (node) {
    ((S9a3c40*)this)->f(*(void**)node);
    char* next = *(char**)(node + 4);
    int ref = *(int*)(node + 0x14);
    if (ref) ((S99d060*)(size_t)ref)->f();
    FUN_f47380(node);
    node = next;
  }
}
