#include "types.h"
#include <string.h>

// Slice s00669f50 - cSPUIFeedListItem helpers and comparators.

struct VObj { void** vt; };
struct CItem { char pad[0xc]; int* p; };
typedef int  (__thiscall *FnRetInt)(void*);
typedef long long (__thiscall *FnRetLL)(void*);
typedef bool (__thiscall *FnRetBool)(void*);
typedef void* (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef int  (__thiscall *FnV2iR)(void*, int, int);
unsigned __cdecl FUN_006b8ea0(int, int, int);

// ------------------------------------------------------------------
// @ 0x0066a5c0
extern int g_ids24[24];
int FindIndex0066a5c0(int x) {
  int i = 0;
  do {
    if (x == g_ids24[i]) return i;
    ++i;
  } while (i < 0x18);
  return 0x18;
}

// ------------------------------------------------------------------
// @ 0x0066a5e0
struct FillBuf {
  int a0, a1, a2, a3, a4, a5, m18;
  bool m1c;
  void Set(unsigned char b, int p);
};
void FillBuf::Set(unsigned char b, int p) {
  memset(this, b, 0x18);
  m18 = p;
  m1c = false;
}

// ------------------------------------------------------------------
// @ 0x0066a610
struct Neger {
  int Neg(int a, int b);
};
int Neger::Neg(int a, int b) {
  return -((FnV2iR)((VObj*)this)->vt[5])(this, a, b);
}

// ------------------------------------------------------------------
// @ 0x0066a630
struct Switcher {
  int pad0; int pad1; int m8;
  unsigned Get();
};
unsigned Switcher::Get() {
  switch (m8) {
  case 0: return 0x2dfb4f9f;
  case 1: return 0xa28a67e8;
  case 2: return 0x5cd23f68;
  case 3: return 0x93b9d42e;
  case 4: return 0x38f64117;
  default: return 0;
  }
}

// ------------------------------------------------------------------
// @ 0x0066ad70
struct Switcher2 {
  int pad0; int pad1; int m8;
  unsigned Get();
};
unsigned Switcher2::Get() {
  switch (m8) {
  case 0: return 0x7ca87ec2;
  case 1: return 0x3019275;
  case 2: return 0x1d7707e0;
  default: return 0;
  }
}

// ------------------------------------------------------------------
// @ 0x0066a800
extern int* g_vecBegin15fb19c;
extern int* g_vecEnd15fb1a0;
int GetElem0066a800(int i) {
  if (i >= 0 && i < (int)(g_vecEnd15fb1a0 - g_vecBegin15fb19c))
    return g_vecBegin15fb19c[i];
  return 0;
}

// ------------------------------------------------------------------
// Lookup used by the comparators: object at arg+0xc has a subobject at
// +0x10 whose slot 3 returns a pointer for the given id.
__forceinline int* Lookup0066(void* a) {
  int* p = *(int**)((char*)a + 0xc);
  return p ? (int*)((FnV0i)((VObj*)((char*)p + 0x10))->vt[3])(
                 (VObj*)((char*)p + 0x10), 0x13d55dc8)
           : 0;
}

// ------------------------------------------------------------------
// @ 0x0066ab90
struct Cmp0c {
  unsigned operator()(int a, int b);
};
unsigned Cmp0c::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      int x = ((FnRetInt)((VObj*)p)->vt[3])(p);
      int y = ((FnRetInt)((VObj*)*(int**)(b + 0xc))->vt[3])(*(int**)(b + 0xc));
      if (x != 0) {
        if (y != 0) return FUN_006b8ea0(x, y, 0);
        return 1;
      }
      return (y != 0) ? -1 : 0;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066ac10
struct Cmp10 {
  unsigned operator()(int a, int b);
};
unsigned Cmp10::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      int x = ((FnRetInt)((VObj*)p)->vt[4])(p);
      int y = ((FnRetInt)((VObj*)*(int**)(b + 0xc))->vt[4])(*(int**)(b + 0xc));
      if (x != 0) {
        if (y != 0) return FUN_006b8ea0(x, y, 0);
        return 1;
      }
      return (y != 0) ? -1 : 0;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066aca0
struct Cmp70 {
  unsigned operator()(int a, int b);
};
unsigned Cmp70::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      unsigned char x = ((FnRetBool)((VObj*)p)->vt[28])(p);
      unsigned char y = ((FnRetBool)((VObj*)*(int**)(b + 0xc))->vt[28])(*(int**)(b + 0xc));
      if (y == x) return 0;
      return (y < x) ? 0xffffffffu : 1u;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066ad10
struct Cmp38 {
  unsigned operator()(CItem& a, CItem& b);
};
unsigned Cmp38::operator()(CItem& a, CItem& b) {
  int* p = a.p;
  if (p) {
    if (b.p) {
      int x = ((FnRetInt)((VObj*)p)->vt[14])(p);
      int y = ((FnRetInt)((VObj*)b.p)->vt[14])(b.p);
      if (x == y) return 0;
      return (x <= y) ? 1u : 0xffffffffu;
    }
    if (a.p) return 0xffffffff;
  }
  return b.p != 0;
}

// ------------------------------------------------------------------
// @ 0x0066aa40
struct Cmp28 {
  unsigned operator()(int a, int b);
};
unsigned Cmp28::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      long long x = ((FnRetLL)((VObj*)p)->vt[10])(p);
      long long y = ((FnRetLL)((VObj*)*(int**)(b + 0xc))->vt[10])(*(int**)(b + 0xc));
      if (x == y) return 0;
      if (x > y) return 0xffffffff;
      return 1;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066aad0
struct Cmp94 {
  unsigned operator()(int a, int b);
};
unsigned Cmp94::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  if (p) {
    if (q) {
      long long x = ((FnRetLL)((VObj*)p)->vt[37])(p);
      long long y = ((FnRetLL)((VObj*)q)->vt[37])(q);
      if (x == y) return 0;
      if (x > y) return 0xffffffff;
      return 1;
    }
    return 0xffffffff;
  }
  return q != 0;
}

// ------------------------------------------------------------------
// @ 0x0066a950
struct Cmp950 {
  unsigned operator()(int a, int b);
};
unsigned Cmp950::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  if (p) {
    if (q) {
      if (((FnRetBool)((VObj*)p)->vt[30])(p)) {
        if (((FnRetBool)((VObj*)q)->vt[30])(q)) {
          int x = ((FnRetInt)((VObj*)p)->vt[34])(p);
          int y = ((FnRetInt)((VObj*)q)->vt[34])(q);
          if (x == y) return 0;
          return (x <= y) ? 1u : 0xffffffffu;
        }
      }
      if (((FnRetBool)((VObj*)p)->vt[30])(p)) return 0xffffffff;
      return ((FnRetBool)((VObj*)q)->vt[30])(q) != 0;
    }
    return 0xffffffff;
  }
  return q != 0;
}

// ------------------------------------------------------------------
// @ 0x0066ada0
struct CmpAd {
  int pad0; int pad1; int m8;
  unsigned operator()(int a, int b);
};
unsigned CmpAd::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  float* fa = 0;
  float* fb = 0;
  if (p) {
    int* r = (int*)((FnV0)((VObj*)p)->vt[38])(p);
    if (*r == 1) fa = (float*)((FnV0)((VObj*)p)->vt[38])(p) + 1;
  }
  if (q) {
    int* r = (int*)((FnV0)((VObj*)q)->vt[38])(q);
    if (*r == 1) fb = (float*)((FnV0)((VObj*)q)->vt[38])(q) + 1;
  }
  if (!fa) return fb != 0;
  if (fb) {
    float x, y;
    switch (m8) {
    case 0: x = fa[0]; y = fb[0]; break;
    case 1: x = fa[1]; y = fb[1]; break;
    case 2: x = fa[2]; y = fb[2]; break;
    default: return 0;
    }
    if (x == y) return 0;
    if (x <= y) return 1;
  }
  return 0xffffffff;
}

typedef int (__thiscall *FnCmp2)(void*, void*, void*);

// @ 0x00669f50
// PARTIAL: SP::cSPUIFeedListItem::Init (1640 bytes). Skeleton only - the real
// body does a long chain of property/key lookups plus eastl string setup.
struct FeedItemInit {
  int Init(int* a, int* b, unsigned c, void* d);
};
int FeedItemInit::Init(int* a, int* b, unsigned c, void* d) {
  (void)a; (void)b; (void)c; (void)d;
  return 1;
}

// @ 0x0066a830
struct Sorter830 {
  int pad0, pad1, pad2;   // +0x0..+0xc
  int* mC;                // +0xc
  int* m10;               // +0x10
  char pad14[0xc];
  bool m20;               // +0x20
  bool operator()(void* pa, void* pb);
};
bool Sorter830::operator()(void* pa, void* pb) {
  unsigned char* a = (unsigned char*)pa;
  unsigned char* b = (unsigned char*)pb;
  bool r = b[0x1c] < a[0x1c];
  if (b[0x1c] != a[0x1c]) return r;
  unsigned char a1 = a[0x1d];
  unsigned char av = 0, bv = 0;
  if (a1 == 0 && *(void**)(a + 4) != 0 && *(char*)((char*)*(void**)(a + 4) + 0xf4) != 0) av = 1;
  if (b[0x1d] == 0 && *(void**)(b + 4) != 0 && *(char*)((char*)*(void**)(b + 4) + 0xf4) != 0) bv = 1;
  r = bv < av;
  if (bv != av) return r;
  r = b[0x1d] < a1;
  if (b[0x1d] != a1) return r;
  int n = (int)(m10 - mC);
  for (int i = 0; i < n; ++i) {
    int* obj;
    int slot;
    if (i == 0 && m20) { obj = (int*)*mC; slot = 6; }
    else { obj = (int*)mC[i]; slot = 5; }
    int res = ((FnCmp2)((VObj*)obj)->vt[slot])(obj, pa, pb);
    if (res != 0) return res < 0;
  }
  unsigned x = *(unsigned*)a, y = *(unsigned*)b;
  r = x < y;
  if (x == y) {
    if (a[4] == b[4] && a[8] == b[8]) return false;
    if (a[8] != b[8]) return a[8] < b[8];
    return a[4] < b[4];
  }
  return r;
}
// @ 0x0066af20
struct Vec3 { int* begin; int* end; int* cap; };
void vec_cctor(void*, int, void*);
void FUN_01022c60(void*, void*, void*, void*, void*);
struct CtorAf {
  void* vt;              // +0
  int m4;                // +4
  int m8;                // +8
  Vec3 mC;               // +0xc
  char pad18[8];
  bool m20;              // +0x20
  bool m21;              // +0x21
  int m24, m28, m2c, m30;
  CtorAf(int p2, Vec3* p3);
};
CtorAf::CtorAf(int p2, Vec3* p3) {
  m4 = 0;
  vt = (void*)0x1400620;
  m8 = p2;
  vec_cctor(&mC, (int)(p3->end - p3->begin), (void*)((char*)p3 + 0xc));
  int v = p2;
  void* out;
  FUN_01022c60(&v, p3->begin, p3->end, mC.begin, &out);
  mC.end = (int*)v;
  m20 = false;
  m24 = 0;
  m21 = true;
  m28 = 0;
  m2c = 0;
  m30 = 0;
}

// @ 0x0066a680
struct CmpA680 {
  int pad0; int pad1; int m8;
  unsigned operator()(int a, int b);
};
unsigned CmpA680::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  float* fa = 0;
  float* fb = 0;
  if (p) {
    int* r = (int*)((FnV0)((VObj*)p)->vt[38])(p);
    if (*r == 0) fa = (float*)((FnV0)((VObj*)p)->vt[38])(p) + 1;
  }
  if (q) {
    int* r = (int*)((FnV0)((VObj*)q)->vt[38])(q);
    if (*r == 0) fb = (float*)((FnV0)((VObj*)q)->vt[38])(q) + 1;
  }
  if (!fa) return fb != 0;
  if (fb) {
    float x, y;
    switch (m8) {
    case 0: x = (*(int*)fa == 1) ? 1.0f : 0.0f; y = (*(int*)fb == 1) ? 1.0f : 0.0f; break;
    case 1: x = (*(int*)fa == 2) ? 1.0f : 0.0f; y = (*(int*)fb == 2) ? 1.0f : 0.0f; break;
    case 2: x = (*(int*)fa == 3) ? 1.0f : 0.0f; y = (*(int*)fb == 3) ? 1.0f : 0.0f; break;
    case 3: x = fa[1]; y = fb[1]; break;
    case 4: x = fa[2]; y = fb[2]; break;
    default: return 0;
    }
    if (x == y) return 0;
    if (x <= y) return 1;
  }
  return 0xffffffff;
}
