// Slice s009a2c90: creature-animation helper functions.
// Reconstructed from the annotated disassembly.
#include "types.h"
#pragma inline_depth(0)

// ---------------------------------------------------------------------------
// stubs
// ---------------------------------------------------------------------------
struct S99d060 {
  void f();                                                      // 0x99d060
};
extern float FUN_009a1d90(int, float, int, int);
extern int  FUN_009a1c20(int, int, int);
extern int  FUN_0067cb20();
extern int  FUN_921580(int);
extern int* g_166c058;
extern int* g_166c05c;
extern void FUN_f47380(void*);                                   // 0xf47380

struct S9a1b00 {
  int f(int, int);                                               // 0x9a1b00
};
struct S9a2f80 {
  int f(int, int);                                               // 0x9a2f80
};
struct S9a3760 { int* f(int*, unsigned*); };
struct S9a3820 { int* f(int*, unsigned*); };
struct S9a3c40 { void f(void*); };
struct Rbtree99 { int find(int*, int*); };
struct S9a1770 { void f(int); };
// Not defined in this TU: the call is left to the original 009a3080 image.
// (009a3080 is still a partial skeleton here, so its caller cannot be
// validated against our approximation.)
struct S9a3080Call { void f(int); };
struct S9a2d50 { void f(int, int, int); };                       // 0x9a2d50
struct S9a3080 { void f(char); };
struct S99f0b0 {
  void f();                                                      // 0x99f0b0
};
struct S9c4cc0 {
  void f();                                                      // 0x9c4cc0
};
struct S9a35b0 { void f(); };
struct S9a3630 { int f(); };
extern bool FUN_009a2cc0(void*, int);
struct S9a2fd0 { void f(unsigned); };                            // 0x9a2fd0
extern void FUN_009a80e0(void*);
extern int  FUN_009a1530();
extern void FUN_009a0df0();
extern int g_15504e0;
extern int g_166b260;
extern void* __cdecl operator_new(int, const char*, int, int, const char*, int);  // 0xf473a0
extern void __cdecl FUN_9216a0(void*, void*, void*, int);                        // 0x9216a0
struct S9b3450 { void f(); };
struct S99c980 { void f(); };
struct S99c660 { void f(); };
struct S9c26a0 {
  void f();                                                      // 0x9c26a0
};
struct S9a3890 { void* f(int*); };                               // 0x9a3890
struct S9a3980 { void f(int*, char*, unsigned*, char); };
struct S9a3a10 { void f(int*, int, unsigned*, char); };
struct S9a38f0 { bool f(int, int, int*); };
struct S9a34a0 { S9a34a0* f(); };
struct S9a3b10 { int* f(int*, unsigned*, int); };
struct S9a3220 { bool f(void*, void*, int); };

// rbtree node (EASTL rbtree_node layout)
struct RbNode {
  RbNode*  left;    // +0x00
  RbNode*  right;   // +0x04
  RbNode*  parent;  // +0x08
  int      color;   // +0x0c
  unsigned key0;    // +0x10
  unsigned key1;    // +0x14
};
// rbtree container header; anchor occupies +0x04 (anchor.parent == root)
struct RbTree {
  int      field0;  // +0x00
  RbNode   anchor;  // +0x04
};
// animation object as seen by FUN_009a2c90
struct S9a2c90Obj {
  unsigned char unknown[0xb0];
  double        fieldB0;  // +0xb0
};

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
// @ 0x009a34a0  S9a34a0::f: animation-object init
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
  ((S9a3080Call*)self)->f(1);
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x009a2cc0  FUN_009a2cc0: animation object init
// ---------------------------------------------------------------------------
// animation object; only the fields touched here are named.
struct S9a2cc0Obj {
  void*    field00;      // +0x00  (pointer checked for null)
  int      pad04[2];     // +0x04
  int      field0c;      // +0x0c
  int      field10;      // +0x10
  int      field14;      // +0x14
  int      pad18[0x25];  // +0x18
  unsigned char fieldAc; // +0xac
  unsigned char fieldAd; // +0xad
  unsigned char padAe[2];// +0xae
  double   fieldB0;      // +0xb0
  double   fieldB8;      // +0xb8
  int      fieldC0;      // +0xc0
  int      fieldC4;      // +0xc4
  S9a1770  fieldC8;      // +0xc8
};
extern int g_15504e0;
extern int g_166b260;
__declspec(noinline) bool FUN_009a2cc0(void* self_, int p2) {
  S9a2cc0Obj* self = (S9a2cc0Obj*)self_;
  self->fieldAc = 0;
  self->fieldC8.f(0);
  FUN_009a80e0(self);
  if (self->field00 == 0) return false;
  self->field0c = p2;
  self->field10 = g_15504e0;
  g_15504e0 += 1;
  *(int*)((char*)self->field00 + 0x12c) = g_166b260;
  g_166b260 += 1;
  self->fieldB0 = 0.0;
  self->fieldC0 += 1;
  self->fieldAc = 1;
  self->fieldC4 = 0;
  (void)FUN_009a1d90((int)(size_t)self, 0.0f, 1, 1);
  return true;
}

// ---------------------------------------------------------------------------
// 0x1f0-byte animation channel element; only the trailing vector is used by
// the reserve helper.
struct SAnimElem {
  unsigned char pad00[0x1dc];
  int*          mpBegin;   // +0x1dc
  int*          mpEnd;     // +0x1e0
  int*          mpCap;     // +0x1e4
  unsigned char pad1[8];
};
struct S9a1530 {
  SAnimElem* f();                                                // 0x9a1530
};
struct S9a0df0 {
  void f();                                                      // 0x9a0df0
};

// ---------------------------------------------------------------------------
// @ 0x009a2fd0 S9a2fd0::f
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a2fd0::f(unsigned p2) {
  char* self = (char*)this;
  int count = (*(int*)(self + 4) - *(int*)self) / 0x1f0;
  if (p2 > (unsigned)count) {
    SAnimElem tmp;
    SAnimElem* t = ((S9a1530*)&tmp)->f();
    int c2 = (*(int*)(self + 4) - *(int*)self) / 0x1f0;
    ((S9a2d50*)self)->f(*(int*)(self + 4), (int)(p2 - c2), (int)(size_t)t);
    ((S9a0df0*)&tmp)->f();
    if (tmp.mpBegin && *(int*)((char*)tmp.mpBegin - 4))
      FUN_f47380(tmp.mpBegin);
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
// @ 0x009a2c90  FUN_009a2c90: add a double field and forward to FUN_009a1d90
// ---------------------------------------------------------------------------
__declspec(noinline) float FUN_009a2c90(int a, float b, int c, int d) {
  S9a2c90Obj* obj = (S9a2c90Obj*)a;
  return FUN_009a1d90(a, (float)((double)b + obj->fieldB0), c, d);
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
// @ 0x009a3760  S9a3760::f: rbtree lower_bound
// ---------------------------------------------------------------------------
__declspec(noinline) int* S9a3760::f(int* out, unsigned* key) {
  RbTree* t = (RbTree*)this;
  RbNode* head = &t->anchor;
  RbNode* parent = head;
  RbNode* node = head->parent;
  if (node) {
    unsigned k0 = key[0], k1 = key[1];
    do {
      if (k0 > node->key0 || (k0 == node->key0 && k1 > node->key1)) node = node->left;
      else { parent = node; node = node->right; }
    } while (node);
  }
  *out = (int)(size_t)parent;
  return out;
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
// @ 0x009a3820  S9a3820::f: rbtree lower_bound (<=)
// ---------------------------------------------------------------------------
__declspec(noinline) int* S9a3820::f(int* out, unsigned* key) {
  RbTree* t = (RbTree*)this;
  RbNode* head = &t->anchor;
  RbNode* parent = head;
  RbNode* node = head->parent;
  if (node) {
    unsigned k0 = key[0], k1 = key[1];
    do {
      if (k0 > node->key0 || (k0 == node->key0 && k1 > node->key1)) node = node->left;
      else { parent = node; node = node->right; }
    } while (node);
    if (parent != head && parent->key0 <= k0 && (parent->key0 < k0 || parent->key1 <= k1)) {
      *out = (int)(size_t)parent;
      return out;
    }
  }
  *out = (int)(size_t)head;
  return out;
}

// ---------------------------------------------------------------------------
// element-range helpers used by the vector insert
// ---------------------------------------------------------------------------
struct S9a17d0 {
  void f(int);                                                   // 0x9a17d0
};                                  // copy-construct element
extern int  FUN_009a1920(int, int, int);   // 0x9a1920 copy-construct [first,last) at dest
extern void FUN_009a1960(int, int);        // 0x9a1960 destroy [first,last)
extern int  FUN_009a1bf0(int, unsigned, int);  // 0x9a1bf0 fill count elements
extern int  FUN_009a1bb0(int*, int, int, int); // 0x9a1bb0 copy-construct range, out cursor
extern int  FUN_009a1a20(int, int, int);   // 0x9a1a20 copy-backward range
extern void FUN_009a1eb0(int, int, int);   // 0x9a1eb0 copy-assign fill range

// ---------------------------------------------------------------------------
// @ 0x009a2d50 S9a2d50::f  vector insert(position, n, value)
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a2d50::f(int position, int n_, int value) {
  int* base = (int*)this;
  unsigned n = (unsigned)n_;
  int size = (base[1] - base[0]) / 0x1f0;
  if ((unsigned)size < n) {
    unsigned cap = (unsigned)(size * 2);
    if (size == 0) cap = 1;
    unsigned want = (unsigned)size + n;
    if (want < cap) want = cap;
    char* buf;
    if (want == 0) buf = 0;
    else
      buf = (char*)operator_new(
          (int)(want * 0x1f0), "EASTL", 0, 0,
          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
          0xd1);
    char* first = (char*)FUN_009a1920(base[0], position, (int)buf);
    FUN_009a1960(base[0], position);
    FUN_009a1bf0((int)first, n, value);
    char* mid = first + n * 0x1f0;
    char* oldEnd = (char*)base[1];
    char* newEnd = (char*)FUN_009a1920(position, (int)oldEnd, (int)mid);
    FUN_009a1960(position, (int)oldEnd);
    if (base[0] && *(int*)(base[0] - 4)) FUN_f47380((void*)base[0]);
    base[0] = (int)buf;
    base[1] = (int)newEnd;
    base[2] = (int)(buf + want * 0x1f0);
  } else if (n != 0) {
    SAnimElem tmp;
    ((S9a17d0*)&tmp)->f(value);
    char* oldEnd = (char*)base[1];
    int have = (base[1] - position) / 0x1f0;
    char* dst;
    if ((int)n < have) {
      char* src = oldEnd - n * 0x1f0;
      int out = (int)oldEnd;
      FUN_009a1bb0(&out, (int)src, (int)oldEnd, (int)oldEnd);
      base[1] += (int)(n * 0x1f0);
      FUN_009a1a20(position, (int)src, (int)oldEnd);
      dst = src;
    } else {
      FUN_009a1bf0((int)oldEnd, n - (unsigned)have, (int)&tmp);
      base[1] += (int)((n - (unsigned)have) * 0x1f0);
      int out = base[1];
      FUN_009a1bb0(&out, position, (int)oldEnd, base[1]);
      base[1] += (int)((unsigned)have * 0x1f0);
      dst = oldEnd;
    }
    FUN_009a1eb0(position, (int)dst, (int)&tmp);
    ((S9a0df0*)&tmp)->f();
  }
}


// ---------------------------------------------------------------------------
// animation-channel object shared by reset (009a3080) and bind (009a3220)
// ---------------------------------------------------------------------------
struct SAnim {
  void*         p00;        // +0x00
  void*         p04;        // +0x04
  void*         p08;        // +0x08
  int           f0c;        // +0x0c
  int           f10;        // +0x10
  int           f14;        // +0x14
  int           vBegin;     // +0x18
  int           vEnd;       // +0x1c
  int           vCap;       // +0x20
  int           pad24[2];   // +0x24
  float         fv[32];     // +0x2c..+0xab
  unsigned char bAc;        // +0xac
  unsigned char bAd;        // +0xad
  unsigned char padAe[2];   // +0xae
  double        dB0;        // +0xb0
  double        dB8;        // +0xb8
  int           c0;         // +0xc0
  int           c4;         // +0xc4
  unsigned char helper[0x14]; // +0xc8
  int           fDc;        // +0xdc
};

// ---------------------------------------------------------------------------
// @ 0x009a3080 S9a3080::f
// ---------------------------------------------------------------------------
__declspec(noinline) void S9a3080::f(char p2) {
  SAnim* self = (SAnim*)this;
  if (self->p00) {
    void* p = self->p00;
    self->p00 = 0;
    ((S99d060*)p)->f();
  }
  if (self->p04) {
    void* p = self->p04;
    self->p04 = 0;
    ((S9c4cc0*)p)->f();
  }
  if (self->p08) {
    void* p = self->p08;
    self->p08 = 0;
    ((S99f0b0*)p)->f();
  }
  self->fv[0] = 0.0f;  self->fv[1] = 0.0f;  self->fv[2] = 0.0f;  self->fv[3] = 0.0f;
  self->fv[4] = 0.0f;  self->fv[5] = 0.0f;  self->fv[6] = 0.0f;  self->fv[7] = 0.0f;
  const float one = 1.0f;
  self->fv[8] = 0.0f;  self->fv[9] = 0.0f;  self->fv[10] = 0.0f; self->fv[11] = 0.0f;
  self->fv[12] = 0.0f; self->fv[13] = 0.0f; self->fv[14] = 0.0f; self->fv[15] = 0.0f;
  self->fv[16] = 0.0f; self->fv[17] = 0.0f; self->fv[18] = 0.0f; self->fv[19] = 0.0f;
  self->fv[20] = 0.0f; self->fv[21] = 0.0f; self->fv[22] = 0.0f; self->fv[23] = 0.0f;
  self->fv[24] = one;
  self->fv[25] = 0.0f; self->fv[26] = 0.0f; self->fv[27] = 0.0f;
  self->fv[28] = 0.0f; self->fv[29] = 0.0f; self->fv[30] = 0.0f;
  self->fv[31] = one;
  self->f0c = -1;
  self->f10 = g_15504e0;
  g_15504e0 += 1;
  self->f14 = 0;
  if (p2) {
    int* vec = &self->vBegin;
    int b = vec[0];
    int e = vec[1];
    int r = FUN_009a1c20(e, e, b);
    ((S9a1b00*)vec)->f(r, vec[1]);
    vec[1] += ((e - b) / -0x1f0) * 0x1f0;
  }
  double z = 0.0;
  self->dB0 = z;
  self->dB8 = z;
  self->bAc = 0;
  self->bAd = 0;
  self->c0 = 1;
  self->c4 = 0;
  ((S9a1770*)self->helper)->f(0);
}

// ---------------------------------------------------------------------------
// @ 0x009a3220 S9a3220::f  animation channel bind
// ---------------------------------------------------------------------------
struct SAnimSrcEntry {
  unsigned char pad00[0xd4];
  unsigned      count;      // +0xd4
};
struct SAnimSrc {
  unsigned char pad00[0x114];
  int           refs;       // +0x114
  unsigned      flags;      // +0x118
  float         f11c;       // +0x11c
  float         f120;       // +0x120
  unsigned char pad124[0x144 - 0x124];
  unsigned      count;      // +0x144
  int*          items;      // +0x148
};
struct SAnimElem2 {
  int           f00;        // +0x00
  int           f04;        // +0x04
  int           f08;        // +0x08
  int           f0c;        // +0x0c
  int           f10;        // +0x10
  int           pad14[0x6a];// +0x14..+0x1bb
  int           f1bc;       // +0x1bc
  int           pad1c0[7];  // +0x1c0..+0x1db
  int*          vBegin;     // +0x1dc
  int*          vEnd;       // +0x1e0
  int*          vCap;       // +0x1e4
  int           pad1e8[2];  // +0x1e8..+0x1ef
};
struct SBindRec {
  int f00, f04, f08, f0c, f10, f14, f18, f1c;
  int f20, f24, f28, f2c, f30, f34;
};
struct SBindObj {
  SAnimSrc* src;              // +0x00
  void*     data;             // +0x04
  SBindRec* rec;              // +0x08
  int       pad0c;            // +0x0c
  int       pad10;            // +0x10
  int       f14;              // +0x14
  int*      vBegin;           // +0x18
  int*      vEnd;             // +0x1c
  int*      vCap;             // +0x20
  unsigned char pad24[0xad - 0x24];
  unsigned char bAd;          // +0xad
  unsigned char padAe[0xb8 - 0xae];
  double    dB8;              // +0xb8
};
struct S999dd0 {
  void resize(int*, int, int*);                                  // 0x999dd0
};
struct SAddRef {
  void f();                                                      // 0xa17060
};
extern void FUN_009a1ee0(void*, int, void*);              // 0x9a1ee0

__declspec(noinline) bool S9a3220::f(void* p1, void* p2, int p3) {
  SBindObj* self = (SBindObj*)this;
  SAnimSrc* old = self->src;
  if ((SAnimSrc*)p1 != old) {
    if (p1) ((SAnimSrc*)p1)->refs += 1;
    self->src = (SAnimSrc*)p1;
    if (old) ((S99d060*)old)->f();
  }
  void* oldData = self->data;
  if (p2 != oldData) {
    if (p2) ((SAddRef*)p2)->f();
    self->data = p2;
    if (oldData) ((S9c4cc0*)oldData)->f();
  }
  SAnimSrc* src = self->src;
  float f = 0.0f;
  if (src) f = (src->f120 - 1.0f) * src->f11c;
  self->dB8 = (double)f;
  if ((unsigned)((self->vEnd - self->vBegin) / 0x1f0) < src->count) {
    int** vec = &self->vBegin;
    ((S9a2fd0*)vec)->f(src->count);
  }
  self->f14 = (int)(size_t)self->vBegin;
  unsigned n = src->count;
  if (n != 0) {
    unsigned i = 0;
    int off = 0;
    do {
      SAnimElem2* elem = (SAnimElem2*)((char*)(size_t)self->f14 + off);
      int item = src->items[i];
      elem->f00 = item;
      unsigned cnt = ((SAnimSrcEntry*)(size_t)item)->count;
      int* vEnd = elem->vEnd;
      int* vBegin = elem->vBegin;
      unsigned have = (unsigned)((vEnd - vBegin) >> 2);
      if (cnt > have) {
        int zero = 0;
        ((S999dd0*)&elem->vBegin)->resize(vEnd, (int)(cnt - have), &zero);
      } else {
        int* dest = vBegin + cnt;
        elem->vEnd = dest;
      }
      int* p = elem->vBegin;
      int* e = elem->vEnd;
      while (p != e) { *p = 0; p++; }
      off += 0x1f0;
      elem->f1bc = elem->f10;
      i++;
    } while (i < n);
  }
  self->bAd = (unsigned char)((src->flags >> 3) & 1);
  if (p3 == 0) {
    if (self->rec == 0) {
      SBindRec* nrec = (SBindRec*)operator_new(
          0x38, "Anim/abd/struct", 0, 0, 0, 0);
      if (nrec) {
        nrec->f00 = 0; nrec->f04 = 0; nrec->f08 = 0; nrec->f0c = 0;
        nrec->f14 = 0; nrec->f1c = 0; nrec->f20 = 0; nrec->f24 = 0;
        nrec->f30 = 0;
      } else {
        nrec = 0;
      }
      SBindRec* oldRec = self->rec;
      if (nrec != oldRec) {
        if (nrec) nrec->f30 += 1;
        self->rec = nrec;
        if (oldRec) ((S99f0b0*)oldRec)->f();
      }
    }
    int* p = (int*)self->data;
    int zero = 0;
    bool temp = false;
    if (p == 0) { temp = true; p = &zero; }
    FUN_009a1ee0(self->src, *p, self->rec);
    if (temp && *p) ((S9c26a0*)(size_t)*p)->f();
  } else {
    SBindRec* oldRec = self->rec;
    if ((SBindRec*)p3 != oldRec) {
      ((SBindRec*)p3)->f30 += 1;
      self->rec = (SBindRec*)p3;
      if (oldRec) ((S99f0b0*)oldRec)->f();
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// EASTL rbtree node/container (node keys follow the 16-byte node base)
// ---------------------------------------------------------------------------
struct RbBase { RbBase* mpRight; RbBase* mpLeft; RbBase* mpParent; int mColor; };
struct RbKeyed : RbBase { unsigned k0; unsigned k1; };
struct RbTree2 { int field0; RbBase anchor; int mSize; };

extern int* FUN_9215c0(int);  // 0x9215c0 RBTreeDecrement

// ---------------------------------------------------------------------------
// @ 0x009a3b10 S9a3b10::f
// ---------------------------------------------------------------------------
__declspec(noinline) int* S9a3b10::f(int* out, unsigned* key, int unused) {
  (void)unused;
  RbTree2* t = (RbTree2*)this;
  RbBase* head = &t->anchor;
  RbBase* node = t->anchor.mpParent;
  RbBase* comp = head;
  bool less = true;
  if (node) {
    do {
      comp = node;
      RbKeyed* cn = (RbKeyed*)node;
      if (cn->k0 > key[0] || (cn->k0 == key[0] && key[1] < cn->k1)) {
        less = true;
        node = node->mpLeft;
      } else {
        less = false;
        node = node->mpRight;
      }
    } while (node);
  }
  RbBase* hint = comp;
  RbBase* pos = comp;
  if (less) {
    if (comp != t->anchor.mpLeft) {
      pos = (RbBase*)FUN_9215c0((int)comp);
    } else {
      int side = 0;
      if (comp != head) {
        RbKeyed* cn = (RbKeyed*)comp;
        if (cn->k0 < key[0] || (cn->k0 == key[0] && key[1] >= cn->k1)) side = 1;
      }
      RbKeyed* n = (RbKeyed*)((S9a3890*)this)->f((int*)key);
      FUN_9216a0(n, comp, head, side);
      t->mSize += 1;
      *out = (int)(size_t)n;
      ((char*)out)[4] = 1;
      return out;
    }
  }
  RbKeyed* pn = (RbKeyed*)pos;
  if (!(key[0] > pn->k0 || (key[0] == pn->k0 && key[1] > pn->k1))) {
    *out = (int)(size_t)pos;
    ((char*)out)[4] = 0;
    return out;
  }
  int side = 0;
  if (hint != head) {
    RbKeyed* hn = (RbKeyed*)hint;
    if (hn->k0 < key[0] || (hn->k0 == key[0] && key[1] >= hn->k1)) side = 1;
  }
  RbKeyed* n = (RbKeyed*)((S9a3890*)this)->f((int*)key);
  FUN_9216a0(n, hint, head, side);
  t->mSize += 1;
  *out = (int)(size_t)n;
  ((char*)out)[4] = 1;
  return out;
}

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
