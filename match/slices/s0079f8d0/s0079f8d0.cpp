// slice s0079f8d0 -- the eastl::vector<SP::cSplitModelElement> instance ops and the
// SP::cSplitManager::cSplitInstanceList element-vector ops (cl 15.00 /O2 /MD /Gy /EHsc /TP).
//
// Decompiled from the original PE (work/SporeApp.analysis.bin) and the Ghidra C
// (work/decomp_all/c/00790000.c, 007a0000.c).  Callees are masked relocations, so the
// declarations only need the right calling convention and argument sizes.  The original
// cSplitInstance / cSplitModelElement / cSplitInstanceList helpers clean their stack
// (ret N) and take their first argument in ecx; MSVC only allows __thiscall on members,
// so they are declared as members of a stub class `Tc` and reached through
// `((Tc*)recv)->m_00xxxxxx(...)`, where the member name carries the original VA.
#include "types.h"

typedef unsigned int uint;
typedef unsigned char uchar;

// 0x11e0744 is the CRT byte-range copy thunk the 0x14-byte element vectors use for
// their prefix/suffix moves in the grow path.
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, uint32_t);

// ---------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------

// 0x38-byte transform member of a cSplitInstance element.
struct cSPTransform {
  unsigned short mFlags;              // +0x00
  unsigned short mModificationCount;  // +0x02
  unsigned char  pad04[0x0c];         // +0x04 mTranslation (cSPVector3)
  unsigned char  pad10[0x04];         // +0x10 mScale
  unsigned char  pad14[0x24];         // +0x14 mRotation (cSPMatrix3)
  cSPTransform& operator=(cSPTransform const&);  // 0x537dc0 (thiscall, ret4)
};

// 0x74-byte instance payload used by cSplitInstanceList.
struct cSplitInstance {
  unsigned char mFlags;               // +0x00
  cSPTransform  mInstanceTransform;   // +0x04
  cSPTransform  mFinalTransform;      // +0x3c
  cSplitInstance();                         // 0x7993a0 (thiscall, plain ret)
  cSplitInstance(cSplitInstance const&);    // 0x799450 (thiscall, ret4)
};

// 0x20-byte element of eastl::vector<SP::cString,...> used by FUN_0079fe20: a 0xe-length
// empty string header plus a refcounted tail pointer whose release runs at scope exit.
struct Elem20 {
  uint32_t m00, m04, m08, m0c, m10, m14;   // +0x00
  uint16_t m18, m1a;                        // +0x18
  void*    m1c;                             // +0x1c
  Elem20() {
    m00 = 0; m04 = 0; m08 = 0; m0c = 0xe; m10 = 0; m14 = 0; m18 = 0; m1a = 0; m1c = 0;
  }
  ~Elem20() {
    if (m1c != 0) (*(void(__thiscall*)(void*, int))*(void**)m1c)(m1c, 1);
  }
};

// 0x78-byte freelist element of a cSplitInstanceList.
struct cElement {
  int            mNextFree;           // +0x00
  cSplitInstance mData;               // +0x04
};

// POD mirror of a 0x78-byte element whose mBody is only ever constructed by the
// out-of-line cSplitInstance ctor; avoids the /GS cookie a char[] local would add.
struct Elem78 {
  int      mKey;                      // +0x00
  uint32_t mBody[0x1d];               // +0x04 .. +0x77
};

// A 0x14-byte editable split model element (the target vectors' value_type).
// Kept as typed words (no byte array) so locals do not attract a /GS cookie.
struct Elem14 {
  uint32_t m00, m04, m08, m0c, m10;   // +0x00 .. +0x13
};

// Generic 0x10-byte eastl vector header (retail layout).
struct VecBase {
  void* mpBegin;                      // +0x00
  void* mpEnd;                        // +0x04
  void* mpCapacity;                   // +0x08
  void* mAllocator;                   // +0x0c
};

// The 8-byte {refcounted*, index} pair pushed by FUN_0079fd20.
struct RefIndexPair {
  void* mPtr;                         // +0x00
  int   mIndex;                       // +0x04
};

// SP::cSplitManager::cSplitInstanceList (retail 0x18 + trailing insert counter at +0x18).
struct cSplitInstanceList {
  int      mNextFree;                 // +0x00
  VecBase  mDataArray;                // +0x04 .. +0x13
  unsigned int mSize;                 // +0x14
  unsigned int mInsertCount;          // +0x18
};

// ---------------------------------------------------------------------------
// callee declarations
//
// Members of `Tc` reproduce the original __thiscall (first argument in ecx, callee-
// cleaned stack); the enclosing unnamed-namespace wrappers call them the way the
// original call sites did.  The m_00xxxxxx names carry the original VA for the
// callee resolver.
// ---------------------------------------------------------------------------
struct Tc {
  // --- 0x14-byte-element vector helpers: original __thiscall (receiver in ecx) ---
  void  m_0079a4a0(int a);                       // move-construct into this (1 stack arg)
  void  m_0079a6c0(int a);                       // shallow-copy-construct into this (1 stack arg)
  void  m_0079f640(int a);                       // copy-assign into this (1 stack arg)
  void  m_0079f4e0(int a, int b);                // push_back (2 stack args)
  int   m_0079ae00(int n, int a, int b);         // allocate n (3 stack args, ret 0xc)
  void  m_0079b0d0(int a, int b);                // destroy range (2 stack args)
  // --- free cdecl helpers: all arguments on the stack, no ecx ---
  void  m_0079a710(int a, int b, int c, int d, int e);
  void  m_0079a800(int a, int b, int c, int d);
  void  m_0079a8f0(int a, int b, int c);
  void  m_0079aaa0(int a, int b, int c);
  int   m_0079ab00(int a, int b, int c);
  void  m_0079ab40(int a, int b, int c);
  void  m_0079b150(int a);
  void  m_0079b190(int a, int b, int c);
  void  m_0079b1c0(int a, int b, int c, int d);
  void  m_0079b2a0(int a, int b, int c, int d);
  void  m_0079b470(int a, int b, int c);
  void  m_0079b6b0(int a, int b);
  int   m_0079f730(int a, int b, int c);         // returns dst
  void  m_0079f770(int a, int b, int c);
  void  m_01023030(int a, int b);                // destroy [a,b) 0x14-elements (thiscall)
  void  m_0079f7b0(int a);
  void  m_0079fcc0(int a, int b, int c);
  void  m_0799dc0(int a, int b, int c);
  void  m_0799d60(int a, int b, int c);
  int   m_00424cf0(int src, int nbytes);   // thiscall DoInsertValue: move nbytes to `this`
  // --- direct thiscall helpers on the target objects ---
  void  m_0537dc0(void* a);                 // cSPTransform::operator= (1 stack arg)
  void  m_07993a0();                        // cSplitInstance() (0 stack args)
  void  m_0799450(void* a);                 // cSplitInstance(copy) (1 stack arg)
  // --- sibling target functions (called as thiscall members / defined below) ---
  void  m_0079f8d0(int first, int last);         // ret 8
  void  m_0079fa20(int first, int last);
  void  m_0079fa70(int pos, int n, int value);
  __declspec(noinline) void m_007a0010(int n);
  void  m_007a0110(void* pos, int n, void* value);
  void  m_007a0460(void* other);
  void  m_007a0600(void* pos, void* value);
  int   m_0079ff40(void* src);
};

// cdecl callees
extern "C" void* operator_new(unsigned int size, const char* area, int a, int b,
                              const char* allocatorPath, int line);   // 0x00f473a0
extern "C" void  operator_delete(void* p);                            // 0x00f47380
extern "C" void* memmove_(void* dst, const void* src, unsigned int n); // 0x011e0744
extern "C" const char g_allocatorPath[];                              // 0x013eb8a4
extern "C" const char g_allocatorFile[];                              // 0x013ebb38

// the sibling target functions, declared as plain (this==nullptr) calls so the current
// definition stays out of line instead of being inlined/folded
void __fastcall FUN_0079fef0(void* self);
// free cdecl helpers (arguments on the stack, no ecx receiver)
void FUN_0079f7b0(void* elem);
void FUN_0079b6b0(int elem, int sub);

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------
static inline int count14(void* beg, void* end) {
  return (int)((char*)end - (char*)beg) / 0x14;   // signed /20, matches 0x66666667 reciprocal
}
static inline int count8(void* beg, void* end) {
  return (int)((char*)end - (char*)beg) >> 3;
}
static inline bool spNeedsDelete(void* p) {
  return p != 0 && *((int*)p - 1) != 0;
}

// ---------------------------------------------------------------------------
// @ 0x0079f8d0  vector<0x78-byte element>::append_range(first, last)
//   `self` is the vector, `first`/`last` are iterators (raw element pointers).
// ---------------------------------------------------------------------------
// @ 0x0079f8d0
void Tc::m_0079f8d0(int firstArg, int lastArg) {
  VecBase* v = (VecBase*)this;
  char* first = (char*)firstArg;
  char* last  = (char*)lastArg;
  char* end   = (char*)v->mpEnd;
  if (end == v->mpCapacity) {
    int units = (int)(end - (char*)v->mpBegin) / 0x78;
    int cap;
    if (units == 0) { cap = 1; }
    else { cap = units * 2; if (cap == 0) cap = 0; }
    char* nb;
    if (cap == 0) nb = 0;
    else nb = (char*)operator_new(cap * 0x78, "Graphics", 0, 0, g_allocatorPath, 0xd1);
    ((Tc*)0)->m_0799dc0((int)v->mpBegin, (int)first, (int)nb);   // uninitialized_move [begin,first)
    char* p = first;
    if (p != nb) { /* (only used for its side effect) */ }
    // the destination of the moved prefix is nb; the new element goes after it
    char* dst = nb + ((char*)first - (char*)v->mpBegin);
    if (dst != 0) {
      *(int*)dst = *(int*)last;
      ((Tc*)(dst + 4))->m_0799450(last + 4);                     // cSplitInstance copy ctor
    }
    char* moved = dst + 0x78;
    ((Tc*)0)->m_0799dc0((int)first, (int)v->mpEnd, (int)moved);  // uninitialized_move [first,end)
    if (spNeedsDelete(v->mpBegin)) operator_delete(v->mpBegin);
    v->mpEnd = moved + ((char*)v->mpEnd - first);
    v->mpBegin = nb;
    v->mpCapacity = nb + cap * 0x78;
    return;
  }
  if (last >= first && last < end) last += 0x78;
  if (end != 0) {
    *(int*)end = *(int*)(end - 0x78);
    ((Tc*)(end + 4))->m_0799450(end - 0x74);
  }
  ((Tc*)0)->m_0079aaa0((int)first, (int)v->mpEnd + -0x78, (int)v->mpEnd);
  *(int*)first = *(int*)last;
  first[4] = last[4];
  ((Tc*)(first + 8))->m_0537dc0(last + 8);
  ((Tc*)(first + 0x40))->m_0537dc0(last + 0x40);
  v->mpEnd = (char*)v->mpEnd + 0x78;
}

// ---------------------------------------------------------------------------
// @ 0x0079fa70  grow-and-insert: append `n` default 0x14-byte elements at `pos`.
// ---------------------------------------------------------------------------
// @ 0x0079fa70
void Tc::m_0079fa70(int pos, int n, int value) {
  VecBase* v = (VecBase*)this;
  char* p = (char*)pos;
  if ((uint)count14(v->mpEnd, v->mpCapacity) < (uint)n) {
    int size = count14(v->mpBegin, v->mpEnd);
    uint cap = (uint)size * 2;
    if (size == 0) cap = 1;
    uint grow = (uint)size + (uint)n;
    uint newCap = grow > cap ? grow : cap;
    if (newCap == 0) newCap = (grow != 0) ? grow : 1;
    if (newCap == 0) newCap = 1;
    char* nb = 0;
    if (newCap != 0)
      nb = (char*)operator_new(newCap * 0x14, "Graphics", 0, 0, g_allocatorPath, 0xd1);
    char* begin = (char*)v->mpBegin;
    int   pre   = count14(begin, p);
    ((Tc*)0)->m_0799dc0((int)begin, (int)p, (int)nb);
    char* dst = nb + pre * 0x14;
    ((Tc*)0)->m_0079a8f0(n, value, (int)p);                      // fill n value-ish elements
    ((Tc*)0)->m_0799dc0((int)p, (int)v->mpEnd, (int)(dst + n * 0x14));
    if (spNeedsDelete(begin)) operator_delete(begin);
    v->mpBegin = nb;
    v->mpEnd = dst + n * 0x14 + count14(p, v->mpEnd) * 0x14;
    v->mpCapacity = nb + newCap * 0x14;
  } else if (n != 0) {
    ((Tc*)0)->m_0079a6c0(value);
    char* end = (char*)v->mpEnd;
    uint tail = (uint)count14(p, end);
    uint num = (uint)n;
    if (num < tail) {
      char* hole = end - num * 0x14;
      ((Tc*)0)->m_0079a800(value, (int)hole, (int)end, (int)end);
      v->mpEnd = (char*)v->mpEnd + num * 0x14;
      ((Tc*)0)->m_0079ab40((int)p, (int)hole, (int)end);
      ((Tc*)0)->m_0079b190((int)p, (int)(p + num * 0x14), 0);
    } else {
      ((Tc*)0)->m_0079a8f0((int)(num - tail), 0, (int)p);
      v->mpEnd = (char*)v->mpEnd + (num - tail) * 0x14;
      ((Tc*)0)->m_0079a800((int)p, (int)p, (int)end, (int)v->mpEnd);
      v->mpEnd = (char*)v->mpEnd + tail * 0x14;
      ((Tc*)0)->m_0079b190((int)p, (int)end, 0);
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x0079fa20  destroy [first,last) and shrink the vector to end at `first`.
// ---------------------------------------------------------------------------
// @ 0x0079fa20
void Tc::m_0079fa20(int first, int last) {
  VecBase* v = (VecBase*)this;
  char* res = (char*)((Tc*)0)->m_0079ab00(last, (int)v->mpEnd, first);  // relink tail
  ((Tc*)this)->m_01023030((int)res, (int)v->mpEnd);                     // destroy range
  v->mpEnd = (char*)v->mpEnd + ((last - first) / 0x14) * 0x14;
}

// ---------------------------------------------------------------------------
// @ 0x0079fd20  build a vector of {refcounted*, index} pairs from a vector<ptr*>.
// ---------------------------------------------------------------------------
// @ 0x0079fd20
void FUN_0079fd20(void* out, void* pvec) {
  VecBase* v = (VecBase*)out;
  VecBase* src = (VecBase*)pvec;
  v->mpBegin = 0; v->mpEnd = 0; v->mpCapacity = 0;
  uint n = (uint)((char*)src->mpEnd - (char*)src->mpBegin) >> 2;
  for (uint i = 0; i < n; i++) {
    void* p = ((void**)src->mpBegin)[i];
    if (p != 0) ((volatile int*)p)[1] = ((volatile int*)p)[1] + 1;
    RefIndexPair* end = (RefIndexPair*)v->mpEnd;
    if (end < (RefIndexPair*)v->mpCapacity) {
      v->mpEnd = end + 1;
      if (end != 0) {
        end->mPtr = p;
        if (p != 0) ((volatile int*)p)[1] = ((volatile int*)p)[1] + 1;
        end->mIndex = (int)i;
      }
    } else {
      ((Tc*)0)->m_0079f4e0((int)v->mpEnd, (int)&p);
    }
    if (p != 0) {
      volatile int* rc = (volatile int*)p + 1;
      int old = *rc;
      *rc = old - 1;
      if (old == 1) {
        *rc = 1;
        (*(void(__thiscall*)(void*, int))*(void**)p)(p, 1);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x0079fe20  push_back an empty 0x20-byte element (0xe = empty string length).
// ---------------------------------------------------------------------------
// @ 0x0079fe20
void __fastcall FUN_0079fe20(void* self) {
  VecBase* v = (VecBase*)self;
  char* end = (char*)v->mpEnd;
  if (end < (char*)v->mpCapacity) {
    v->mpEnd = end + 0x20;
    if (end != 0) {
      *(int*)(end + 0x00) = 0;
      *(int*)(end + 0x04) = 0;
      *(int*)(end + 0x08) = 0;
      *(int*)(end + 0x0c) = 0xe;
      *(int*)(end + 0x10) = 0;
      *(int*)(end + 0x14) = 0;
      *(unsigned short*)(end + 0x18) = 0;
      *(unsigned short*)(end + 0x1a) = 0;
      *(int*)(end + 0x1c) = 0;
      return;
    }
  } else {
    Elem20 tmp;
    ((Tc*)self)->m_00424cf0((int)v->mpEnd, (int)&tmp);   // append empty string element
  }
}

// ---------------------------------------------------------------------------
// @ 0x0079fef0  eastl::vector<cElement>::push_back() -- one default 0x78-byte element.
// ---------------------------------------------------------------------------
// @ 0x0079fef0
void __fastcall FUN_0079fef0(void* self) {
  VecBase* v = (VecBase*)self;
  char* end = (char*)v->mpEnd;
  if (end < (char*)v->mpCapacity) {
    v->mpEnd = end + 0x78;
    if (end != 0) {
      ((Elem78*)end)->mKey = -2;                // kKeyDataValid
      ((Tc*)(end + 4))->m_07993a0();     // cSplitInstance() -- tail call
    }
    return;
  }
  Elem78 tmp;
  tmp.mKey = -2;
  ((Tc*)(&tmp.mBody))->m_07993a0();
  ((Tc*)v)->m_0079f8d0((int)v->mpEnd, (int)&tmp);
}

// ---------------------------------------------------------------------------
// @ 0x0079ff40  cSplitInstanceList::insert(cSplitInstance const& src) -> int index
// ---------------------------------------------------------------------------
// @ 0x0079ff40
int Tc::m_0079ff40(void* src) {
  cSplitInstanceList* list = (cSplitInstanceList*)this;
  int idx = list->mNextFree;
  if (idx < 1) {
    char* beg = (char*)list->mDataArray.mpBegin;
    char* end = (char*)list->mDataArray.mpEnd;
    idx = (int)(end - beg) / 0x78;
    FUN_0079fef0(&list->mDataArray);
  } else {
    char* slot = (char*)list->mDataArray.mpBegin + idx * 0x78;
    list->mNextFree = *(int*)slot;
    *(int*)slot = -2;
  }
  // Two out-of-line cSplitInstance copies (locals kept POD to avoid a /GS cookie).
  Elem78 a;
  ((Tc*)(&a.mBody))->m_0799450(src);         // cSplitInstance(copy) from src
  Elem78 b;
  b.mKey = -2;
  ((Tc*)(&b.mBody))->m_0799450(&a.mBody);    // cSplitInstance(copy) from a
  char* slot = (char*)list->mDataArray.mpBegin + idx * 0x78;
  *(int*)slot = b.mKey;                      // 0xfffffffe
  slot[4] = ((unsigned char*)&b.mBody)[0];   // b.mFlags
  ((Tc*)(slot + 8))->m_0537dc0((char*)&b.mBody + 4);
  ((Tc*)(slot + 0x40))->m_0537dc0((char*)&b.mBody + 0x3c);
  list->mInsertCount++;
  return idx;
}

// ---------------------------------------------------------------------------
// @ 0x007a0010  Elem14-vector::resize(n)
// ---------------------------------------------------------------------------
// @ 0x007a0010
void Tc::m_007a0010(int n) {
  VecBase* v = (VecBase*)this;
  int size = count14(v->mpBegin, v->mpEnd);
  if ((uint)size < (uint)n) {
    Elem14 tmp;
    tmp.m00 = 0; tmp.m04 = 0; tmp.m08 = 0;   // only the first 3 words are cleared
    ((Tc*)this)->m_0079fa70((int)v->mpEnd, n - size, (int)&tmp);
  } else {
    ((Tc*)this)->m_0079fa20((int)v->mpBegin + n * 0x14, (int)v->mpEnd);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a0110  grow-and-insert `n` copies of a 0x14-byte element at `pos`.
// ---------------------------------------------------------------------------
// @ 0x007a0110
void Tc::m_007a0110(void* pos, int n, void* value) {
  VecBase* v = (VecBase*)this;
  char* p = (char*)pos;
  if ((uint)count14(v->mpEnd, v->mpCapacity) < (uint)n) {
    int size = count14(v->mpBegin, v->mpEnd);
    uint cap = (uint)size * 2;
    if (size == 0) cap = 1;
    uint grow = (uint)size + (uint)n;
    uint newCap = grow < cap ? cap : grow;
    char* nb = 0;
    if (newCap != 0)
      nb = (char*)operator_new(newCap * 0x14, "Graphics", 0, 0, g_allocatorPath, 0xd1);
    char* begin = (char*)v->mpBegin;
    uint preBytes = (uint)(p - begin);
    char* dst = (char*)memmove(nb, begin, preBytes);                     // move prefix
    dst = dst + (preBytes / 0x14) * 0x14;
    ((Tc*)0)->m_0079b2a0((int)dst, (int)n, (int)value, (int)p);
    uint tailBytes = (uint)((char*)v->mpEnd - p);
    char* moved = (char*)memmove(dst + n * 0x14, p, tailBytes);          // move suffix
    if (spNeedsDelete(begin)) operator_delete(begin);
    v->mpBegin = nb;
    v->mpEnd = moved + (tailBytes / 0x14) * 0x14;
    v->mpCapacity = nb + newCap * 0x14;
  } else if (n != 0) {
    ((Tc*)0)->m_0079b150((int)value);
    char* end = (char*)v->mpEnd;
    uint tail = (uint)count14(p, end);
    uint num = (uint)n;
    if (num < tail) {
      char* hole = end - num * 0x14;
      ((Tc*)0)->m_0079b1c0((int)value, (int)hole, (int)end, (int)end);
      v->mpEnd = (char*)v->mpEnd + num * 0x14;
      ((Tc*)0)->m_0079b470((int)p, (int)hole, (int)end);
      ((Tc*)0)->m_0079fcc0((int)p, (int)(p + num * 0x14), 0);
    } else {
      ((Tc*)0)->m_0079b2a0((int)end, (int)(num - tail), 0, (int)p);
      v->mpEnd = (char*)v->mpEnd + (num - tail) * 0x14;
      ((Tc*)0)->m_0079b1c0((int)p, (int)p, (int)end, (int)v->mpEnd);
      v->mpEnd = (char*)v->mpEnd + tail * 0x14;
      ((Tc*)0)->m_0079fcc0((int)p, (int)end, 0);
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a0360  SP::`anonymous namespace'::CompileSplitModels(modelVec, transforms)
// ---------------------------------------------------------------------------
// @ 0x007a0360
void FUN_007a0360(void* p1, void* p2) {
  VecBase* v1 = (VecBase*)p1;
  VecBase* v2 = (VecBase*)p2;
  int local_4 = count14(v1->mpBegin, v1->mpEnd);
  ((Tc*)v2)->m_007a0010(local_4);
  local_4 = count14(v1->mpBegin, v1->mpEnd);
  if (local_4 > 0) {
    int local_8 = 0;
    do {
      char* trans = (char*)v2->mpBegin + local_8;
      char* elem  = (char*)v1->mpBegin + local_8;
      FUN_0079f7b0(trans);
      int c = count8(*(void**)(elem + 0), *(void**)(elem + 4));
      for (int j = 0; j < c; j++)
        FUN_0079b6b0((int)trans, (int)(*(char**)(elem + 0) + j * 8));
      local_8 += 0x14;
      local_4--;
    } while (local_4 != 0);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a0410  destroy each 0x14-byte element, then shrink to 0
// ---------------------------------------------------------------------------
// @ 0x007a0410
void FUN_007a0410(void* self) {
  VecBase* v = (VecBase*)self;
  int n = count14(v->mpBegin, v->mpEnd);
  for (int i = 0; i < n; i++)
    FUN_0079f7b0((void*)((char*)v->mpBegin + i * 0x14));
  ((Tc*)self)->m_007a0010(0);
}

// ---------------------------------------------------------------------------
// @ 0x007a0460  Elem14-vector::operator=(Elem14-vector const&)
// ---------------------------------------------------------------------------
// @ 0x007a0460
void Tc::m_007a0460(void* other_) {
  VecBase* self = (VecBase*)this;
  VecBase* other = (VecBase*)other_;
  if (other == self) return;
  char* oBegin = (char*)other->mpBegin;
  char* oEnd   = (char*)other->mpEnd;
  uint uVar2 = (uint)count14(oBegin, oEnd);
  if ((uint)count14(self->mpBegin, self->mpCapacity) < uVar2) {
    char* nb = (char*)((Tc*)self)->m_0079ae00((int)uVar2, (int)oBegin, (int)oEnd);
    ((Tc*)self)->m_0079b0d0((int)self->mpBegin, (int)self->mpEnd);
    if (spNeedsDelete(self->mpBegin)) operator_delete(self->mpBegin);
    self->mpCapacity = nb + uVar2 * 0x14;
    self->mpBegin = nb;
    self->mpEnd = nb + uVar2 * 0x14;
    return;
  }
  uint uVar3 = (uint)count14(self->mpBegin, self->mpEnd);
  if (uVar3 < uVar2) {
    ((Tc*)0)->m_0079f730((int)oBegin, (int)(oBegin + uVar3 * 0x14), (int)self->mpBegin);
    char* p = (char*)other->mpEnd;
    ((Tc*)0)->m_0079a710((int)&p,
                         (int)(oBegin + count14(self->mpBegin, self->mpEnd) * 0x14),
                         (int)p, (int)self->mpEnd, (int)p);
    self->mpEnd = (char*)self->mpBegin + uVar2 * 0x14;
    return;
  }
  char* dst = (char*)((Tc*)0)->m_0079f730((int)oBegin, (int)oEnd, (int)self->mpBegin);
  ((Tc*)self)->m_0079b0d0((int)dst, (int)self->mpEnd);
  self->mpEnd = (char*)self->mpBegin + uVar2 * 0x14;
}

// ---------------------------------------------------------------------------
// @ 0x007a0600  grow-and-insert one 0x14-byte element at `pos` from `value`.
// ---------------------------------------------------------------------------
// @ 0x007a0600
void Tc::m_007a0600(void* pos, void* value) {
  VecBase* v = (VecBase*)this;
  char* p = (char*)pos;
  char* end = (char*)v->mpEnd;
  if (end != (char*)v->mpCapacity) {
    if (p <= (char*)value && (char*)value < end) value = (char*)value + 0x14;
    if (end != 0) ((Tc*)end)->m_0079a4a0((int)end - 0x14);
    ((Tc*)0)->m_0079f770((int)p, (int)v->mpEnd + -0x14, (int)v->mpEnd);
    ((Tc*)p)->m_0079f640((int)value);
    v->mpEnd = (char*)v->mpEnd + 0x14;
    return;
  }
  int units = (int)(end - (char*)v->mpBegin) / 0x14;
  int cap;
  if (units == 0) cap = 1;
  else { cap = units * 2; if (cap == 0) cap = 0; }
  char* nb = 0;
  if (cap != 0) nb = (char*)operator_new(cap * 0x14, "Graphics", 0, 0, g_allocatorPath, 0xd1);
  char* begin = (char*)v->mpBegin;
  uint preBytes = (uint)(p - begin);
  char* dst = (char*)memmove(nb, begin, preBytes);                       // move prefix
  dst = dst + (preBytes / 0x14) * 0x14;
  if (dst != 0) ((Tc*)dst)->m_0079a4a0((int)value);
  uint tailBytes = (uint)((char*)v->mpEnd - p);
  char* moved = (char*)memmove(dst + 0x14, p, tailBytes);                // move suffix
  if (spNeedsDelete(begin)) operator_delete(begin);
  v->mpEnd = moved + (tailBytes / 0x14) * 0x14;
  v->mpBegin = nb;
  v->mpCapacity = nb + cap * 0x14;
}
