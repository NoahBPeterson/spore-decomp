// Slice s00abb100: a point-cloud / path analysis object message handler, EASTL vector
// insert-n instantiations for 8-byte pairs and 0x28-byte FilterElem records, and helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <string.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void operator_delete__(void* p);

#define EASTL_ALLOC_H \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

#define EALLOC(n) ((n) ? operator new((n), "EASTL", 0, 0, EASTL_ALLOC_H, 0xd1) : 0)
#define EFREE(p) \
  do { if ((p) && ((int*)(p))[-1] != 0) operator_delete__(p); } while (0)

struct Vec3 { float x, y, z; };
struct P8 { float a, b; };

// eastl::vector<bool, fixed_vector_allocator<1,16,1,0,1>> storage view (begin/end/cap)
struct VBool {
  void* begin; void* end; void* cap;
  void CopyFrom(const VBool& o);
};
extern void* __cdecl vb_memmove(void* dst, const void* src, unsigned int n);  // eastl vector<bool>::DoInsertValue
inline void VBool::CopyFrom(const VBool& o) {
  int size = (char*)o.end - (char*)o.begin;
  void* mem = EALLOC(size);
  begin = mem;
  end = mem;
  cap = (char*)mem + size;
  unsigned int sz = (char*)o.end - (char*)o.begin;
  void* r = vb_memmove(mem, o.begin, sz);
  end = (char*)r + sz;
}

// A 0x28-byte record: two flag bytes, two words, then a vector<bool> at +0x10.
struct FilterElem {
  uint8_t a;
  uint8_t b;
  uint32_t pad04;
  uint32_t c;   // +8
  uint32_t d;   // +0xc
  VBool v;      // +0x10
  uint32_t pad[3];
};

// ---------------------------------------------------------------------------
// FUN_00abb100 object. 'this' is the sub-object at base+4.
struct V3Vec {
  Vec3* mBegin; Vec3* mEnd; Vec3* mCap;
  void __thiscall Erase(void* b, void* e);              // FUN_009e0480
  void __thiscall Reset(int n);                         // FUN_00ab9f70
  void __thiscall PushBack(void* where, const void* v); // FUN_00ab9e40
};
struct InfoVec {
  void* mBegin; void* mEnd; void* mCap;
  void __thiscall Erase(void* b, void* e);              // FUN_009e0480
  void __thiscall Finish(int n, void* p);               // FUN_00ab9fe0
};
struct BoundsBox {
  float mn[3], mx[3];
  void __thiscall Reset();                              // FUN_006e6d90
};
struct BoolVec {
  uint32_t* mBegin; uint32_t* mEnd; uint32_t* mCap;
  void __thiscall Clear();                              // FUN_005810a0
  void __thiscall Resize(int n, const float* v);        // FUN_00aba390
};
struct Analyzer {
  void __thiscall Rebuild(float v);                     // FUN_00aba3f0 on (this-4)
  bool __thiscall Handle(int id, const float* data, int count);
};
void* __cdecl VBMove(void* dst, const void* src, unsigned int n);  // eastl vector<bool> DoInsertValue

#define F(T, off) (*(T*)((char*)this + (off)))

// @ 0x00abb100
bool __thiscall Analyzer::Handle(int id, const float* data, int count) {
  Vec3 v;
#define pts ((V3Vec*)((char*)this + 0x130))
#define info ((InfoVec*)((char*)this + 0x538))
#define bv ((BoolVec*)((char*)this + 0x56c))
  switch (id) {
    case 4:
      F(float, 0x110) = data[0];
      return true;
    case 1:
      F(float, 0x114) = data[0];
      return true;
    case 5: {
      v.x = data[0];
      v.y = data[1];
      v.z = data[2];
      *(Vec3*)((char*)this + 0x118) = v;
      return true;
    }
    case 0x101:
      F(float, 0x108) = data[1];
      F(float, 0x100) = data[2];
      F(float, 0x10c) = data[4];
      F(float, 0x104) = data[5];
      return true;
    case 0xd: {
      int n = count / 3;
      if (*(uint32_t*)(F(char*, 0x10) + 8) & 1) {
        if (n > 0)
          F(int, 0x34) = n - 1;
        else
          F(int, 0x34) = 0;
        if (*(uint32_t*)(F(char*, 0x10) + 8) & 1) goto L26c;
      }
      if (n <= 0) {
        pts->Erase(pts->mBegin, pts->mEnd);
        info->Erase(info->mBegin, info->mEnd);
        bv->Clear();
        ((Analyzer*)((char*)this - 4))->Rebuild(0.0f);
        return true;
      }
    L26c:
      pts->Reset(n);
      ((BoundsBox*)((char*)this + 0x48))->Reset();
      {
        const float* p = data + 2;
        for (int i = n; i > 0; --i, p += 3) {
          v.y = p[-1] - F(float, 0xb8);
          v.x = p[-2] - F(float, 0xb4);
          v.z = p[0] - F(float, 0xbc);
          if (F(float, 0xc0) != 1.0f) {
            float s = 1.0f / F(float, 0xc0);
            v.x = s * v.x;
            v.y = v.y * s;
            v.z = v.z * s;
          }
          if (F(uint8_t, 0xb0) & 2) {
            Vec3 r;
            r.x = (F(float, 0xcc) * v.z + F(float, 0xc8) * v.y) + F(float, 0xc4) * v.x;
            r.y = (F(float, 0xd8) * v.z + F(float, 0xd4) * v.y) + F(float, 0xd0) * v.x;
            r.z = (F(float, 0xe4) * v.z + F(float, 0xe0) * v.y) + F(float, 0xdc) * v.x;
            v = r;
          }
          *(Vec3*)((char*)pts->mBegin + ((char*)p - (char*)data) - 8) = v;
          BoundsBox* bb = (BoundsBox*)((char*)this + 0x48);
          if (v.x < bb->mn[0]) bb->mn[0] = v.x;
          if (v.x > bb->mx[0]) bb->mx[0] = v.x;
          if (v.y < bb->mn[1]) bb->mn[1] = v.y;
          if (v.y > bb->mx[1]) bb->mx[1] = v.y;
          if (v.z < bb->mn[2]) bb->mn[2] = v.z;
          if (v.z > bb->mx[2]) bb->mx[2] = v.z;
        }
      }
      F(bool, 0xe) = n > F(int, 0x34);
      if (!F(bool, 0xe)) {
        Vec3* last = pts->mEnd - 1;
        if (pts->mEnd < pts->mCap) {
          Vec3* d = pts->mEnd++;
          if (d) *d = *last;
        } else {
          pts->PushBack(pts->mEnd, last);
        }
      }
      {
        uint32_t* b = bv->mBegin;
        uint32_t* e = bv->mEnd;
        VBMove(b, e, 0);
        bv->mEnd = bv->mEnd - (e - b);
        float one = 1.0f;
        bv->Resize(pts->mEnd - pts->mBegin, &one);
      }
      if ((*(uint32_t*)(F(char*, 0x10) + 8) >> 6) & 1)
        info->Finish(pts->mEnd - pts->mBegin, (char*)this + 0x6c);
      else
        info->Finish(2, (char*)this + 0x6c);
      return true;
    }
  }
  return false;
#undef pts
#undef info
#undef bv
}

// @ 0x00abb5b0
extern void* g_1676070;
extern void* g_1676078;
extern void* g_167607c;
extern void* g_1676084;
extern int g_1676088;
extern int g_167608c;
extern void FUN_00ab9220();
extern void FUN_00ab9e00();
extern void FUN_00abb560();
extern void FUN_00ab3250();
void FUN_00abb5b0() {
  g_1676070 = (void*)FUN_00ab9220;
  g_1676078 = (void*)FUN_00ab9e00;
  g_167607c = (void*)FUN_00abb560;
  g_1676084 = (void*)FUN_00ab3250;
  g_1676088 = 1;
  g_167608c = 1;
}

// @ 0x00abb5f0   uninitialized_fill_n of an 8-byte element
P8* FUN_00abb5f0(P8* dst, unsigned int n, const P8* val) {
  for (; n > 0; --n, ++dst)
    if (dst) {
      dst->a = val->a;
      dst->b = val->b;
    }
  return dst;
}

// vector<P8>: fill-insert helpers (instantiated twice with different element copy routines)
struct VecP8 {
  P8* mBegin;
  P8* mEnd;
  P8* mCap;
  void __thiscall InsertN_A(P8* pos, unsigned int n, const P8* val);  // 0x00abb660
  void __thiscall InsertN_B(P8* pos, unsigned int n, const P8* val);  // 0x00abb820
  void __thiscall Resize_A(unsigned int n);                           // 0x00abba40
  void __thiscall Erase(P8* first, P8* last);                         // FUN_00d018d0
};
extern P8* __cdecl CopyA(P8* first, P8* last, P8* dest);   // FUN_0099efa0
extern P8* __cdecl CopyB(P8* first, P8* last, P8* dest);   // FUN_00838b90
extern void __cdecl CopyFwdA(void* src, P8* first, P8* last, P8* dest, unsigned int n);  // FUN_0076ffd0
extern void __cdecl CopyFwdB(void* src, P8* first, P8* last, P8* dest, unsigned int n);  // FUN_00714bc0
extern void __cdecl CopyBackward(P8* first, P8* last, P8* destEnd);  // FUN_0073fe50
extern void __cdecl FillRange(P8* first, P8* last, const P8* val);   // FUN_00a52da0
extern void __cdecl FillN(P8* first, unsigned int n, const P8* val); // FUN_006ac440
extern P8* FUN_00abb5f0(P8* dst, unsigned int n, const P8* val);

// @ 0x00abb660
void __thiscall VecP8::InsertN_A(P8* pos, unsigned int n, const P8* val) {
  if (n <= (unsigned int)(mCap - mEnd)) {
    if (n != 0) {
      P8 tmp = *val;
      P8* oldEnd = mEnd;
      unsigned int after = mEnd - pos;
      if (n < after) {
        P8* mid = oldEnd - n;
        CopyFwdA(&pos, mid, oldEnd, oldEnd, (unsigned int)mid);
        mEnd += n;
        CopyBackward(pos, mid, oldEnd);
        FillRange(pos, pos + n, &tmp);
        return;
      }
      unsigned int extra = n - after;
      FillN(oldEnd, extra, &tmp);
      mEnd += extra;
      CopyFwdA(&pos, pos, oldEnd, mEnd, after);
      mEnd += after;
      FillRange(pos, oldEnd, &tmp);
    }
  } else {
    int size = mEnd - mBegin;
    unsigned int grow = size * 2;
    if (size == 0) grow = 1;
    unsigned int newCap = size + n;
    if (newCap < grow) newCap = grow;
    P8* mem = (P8*)EALLOC(newCap * 8);
    P8* p = CopyA(mBegin, pos, mem);
    P8* q = p;
    for (unsigned int i = n; i != 0; --i, ++q)
      if (q) {
        q->a = val->a;
        q->b = val->b;
      }
    P8* nend = CopyA(pos, mEnd, p + n);
    EFREE(mBegin);
    mBegin = mem;
    mEnd = nend;
    mCap = mem + newCap;
  }
}

// @ 0x00abb820
void __thiscall VecP8::InsertN_B(P8* pos, unsigned int n, const P8* val) {
  if (n <= (unsigned int)(mCap - mEnd)) {
    if (n != 0) {
      P8 tmp = *val;
      P8* oldEnd = mEnd;
      unsigned int after = mEnd - pos;
      if (n < after) {
        P8* mid = oldEnd - n;
        CopyFwdB(&val, mid, oldEnd, oldEnd, (unsigned int)mid);
        mEnd += n;
        CopyBackward(pos, mid, oldEnd);
        FillRange(pos, pos + n, &tmp);
        return;
      }
      FUN_00abb5f0(oldEnd, n - after, &tmp);
      mEnd += n - after;
      CopyFwdB(&pos, pos, oldEnd, mEnd, after);
      mEnd += after;
      FillRange(pos, oldEnd, &tmp);
    }
  } else {
    int size = mEnd - mBegin;
    unsigned int grow = size * 2;
    if (size == 0) grow = 1;
    unsigned int newCap = size + n;
    if (newCap < grow) newCap = grow;
    P8* mem = (P8*)EALLOC(newCap * 8);
    P8* p = CopyB(mBegin, pos, mem);
    P8* q = p;
    for (unsigned int i = n; i != 0; --i, ++q)
      if (q) {
        q->a = val->a;
        q->b = val->b;
      }
    P8* nend = CopyB(pos, mEnd, p + n);
    EFREE(mBegin);
    mBegin = mem;
    mEnd = nend;
    mCap = mem + newCap;
  }
}

// @ 0x00abb9e0   destructor (derived dtor body: frees three arrays, resets vtable)
struct StateVec { void __thiscall Destroy(); };  // FilterChain_StateVector_Destroy
struct FilterChainObj {
  void* vtbl;
  uint32_t pad04[3];
  void* arr10;
  uint32_t pad14[4];
  void* arr24;
  uint32_t pad28[4];
  void* arr38;
  uint32_t pad3c[12];
  StateVec state6c;
  void __fastcall Dtor();
};
extern void* vtbl_cCreatureAbility_00abb9e0[];
void __fastcall FilterChainObj::Dtor() {
  state6c.Destroy();
  EFREE(arr38);
  EFREE(arr24);
  EFREE(arr10);
  vtbl = vtbl_cCreatureAbility_00abb9e0;
}

// @ 0x00abba40
void __thiscall VecP8::Resize_A(unsigned int n) {
  if (n > (unsigned int)(mEnd - mBegin)) {
    uint32_t v[2];
    v[0] = 0;
    v[1] = 0x100;
    InsertN_A(mEnd, n - (mEnd - mBegin), (P8*)v);
    return;
  }
  Erase(mBegin + n, mEnd);
}

// @ 0x00abbaa0
struct Triple { uint32_t a, b, c; };
struct ConfigObj {
  void* vtbl;
  uint32_t f04;
  uint8_t f08;
  uint32_t f0c;
  Triple t10;
  uint32_t pad1c[2];
  Triple t24;
  uint32_t pad30[2];
  Triple t38;
  uint32_t pad44[2];
  float f4c, f50, f54, f58;
  uint32_t pad5c;
  uint32_t f60, f64;
  uint16_t f68;
  Triple t6c;
  uint32_t pad78[2];
  Triple t80;
  uint32_t pad8c[2];
  Triple t94;
  uint32_t pada0[2];
  Triple ta8;
  uint32_t padb4[2];
  Triple tbc;
  uint32_t padc8[2];
  Triple td0;
  void __fastcall Ctor();
};
extern void* vtbl_014597f8[];
void __fastcall ConfigObj::Ctor() {
  f04 = 0;
  vtbl = vtbl_014597f8;
  f08 = 0;
  f0c = 0;
  t10.a = 0; t10.b = 0; t10.c = 0;
  t24.a = 0; t24.b = 0; t24.c = 0;
  t38.a = 0; t38.b = 0; t38.c = 0;
  f4c = 2.0f;
  f50 = 0.0f; f54 = 0.0f; f58 = 0.0f;
  f60 = 0xffffffff;
  f64 = 0xffffffff;
  f68 = 0;
  t6c.a = 0; t6c.b = 0; t6c.c = 0;
  t80.a = 0; t80.b = 0; t80.c = 0;
  t94.a = 0; t94.b = 0; t94.c = 0;
  ta8.a = 0; ta8.b = 0; ta8.c = 0;
  tbc.a = 0; tbc.b = 0; tbc.c = 0;
  td0.a = 0; td0.b = 0; td0.c = 0;
}

// ---------------------------------------------------------------------------
// Stream (de)serialization helpers.
struct IStream {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
  virtual int Read(void* dst, unsigned int n);  // vtable +0x30
};
extern int __cdecl io_ReadInt32(IStream* s, void* dst, int count, int flags);   // 0x93a780
extern int __cdecl io_ReadBytes(IStream* s, void* dst, int count);              // 0x93a6c0
extern int __cdecl io_ReadUInt64(IStream* s, void* dst, int count, int flags);  // 0x93a800

// @ 0x00abbb80   read a vector<pair<float,float>>-sized array: count, then 8 bytes per element
IStream* __cdecl FUN_00abbb80(IStream* s, VecP8* v) {
  unsigned int n;
  io_ReadInt32(s, &n, 1, 0);
  v->Resize_A(n);
  for (unsigned int i = 0; i < n; ++i) {
    P8* e = v->mBegin + i;
    io_ReadInt32(s, &e->a, 1, 0);
    io_ReadInt32(s, &e->b, 1, 0);
  }
  return s;
}

// @ 0x00abbbf0
IStream* __cdecl FUN_00abbbf0(IStream* s, VecP8* v) {
  unsigned int n;
  io_ReadInt32(s, &n, 1, 0);
  unsigned int size = v->mEnd - v->mBegin;
  if (n > size) {
    P8 tmp;
    v->InsertN_B(v->mEnd, n - (v->mEnd - v->mBegin), &tmp);
  } else {
    v->Erase(v->mBegin + n, v->mEnd);
  }
  for (unsigned int i = 0; i < n; ++i) s->Read(v->mBegin + i, 8);
  return s;
}

// @ 0x00abbc80   uninitialized_copy of FilterElem[first,last) -> dest
FilterElem* __cdecl FUN_00abbc80(FilterElem* first, FilterElem* last, FilterElem* dest) {
  for (; first != last; ++first, ++dest) {
    if (dest) {
      dest->a = first->a;
      dest->b = first->b;
      dest->c = first->c;
      dest->d = first->d;
      dest->v.CopyFrom(first->v);
    }
  }
  return dest;
}

// @ 0x00abbd30   copy-assign FilterElem range from a single source
struct VBoolRef { void __thiscall Assign(const VBool* src); };  // FUN_006f6770
void __cdecl FUN_00abbd30(FilterElem* first, FilterElem* last, FilterElem* src) {
  if (first != last) {
    do {
      first->a = src->a;
      first->b = src->b;
      first->c = src->c;
      first->d = src->d;
      ((VBoolRef*)&first->v)->Assign(&src->v);
      ++first;
    } while (first != last);
  }
}

// @ 0x00abbd80   uninitialized_fill_n of FilterElem
FilterElem* __cdecl FUN_00abbd80(FilterElem* dest, unsigned int n, FilterElem* src) {
  for (; n > 0; --n, ++dest) {
    if (dest) {
      dest->a = src->a;
      dest->b = src->b;
      dest->c = src->c;
      dest->d = src->d;
      dest->v.CopyFrom(src->v);
    }
  }
  return dest;
}

// @ 0x00abbe20   copy_backward of FilterElem range
FilterElem* __cdecl FUN_00abbe20(FilterElem* first, FilterElem* last, FilterElem* dest) {
  if (last != first) {
    FilterElem* d = dest;
    do {
      --last;
      --d;
      d->a = last->a;
      d->b = last->b;
      d->c = last->c;
      d->d = last->d;
      ((VBoolRef*)&d->v)->Assign(&last->v);
    } while (last != first);
    return d;
  }
  return dest;
}

// @ 0x00abbe70   read vector<uint8_t>
struct ByteVec { uint8_t* mBegin; uint8_t* mEnd; uint8_t* mCap; void __thiscall Resize(unsigned int n); };  // 0x4c0410
IStream* __cdecl FUN_00abbe70(IStream* s, ByteVec* v) {
  unsigned int n;
  io_ReadInt32(s, &n, 1, 0);
  v->Resize(n);
  for (unsigned int i = 0; i < n; ++i) io_ReadBytes(s, v->mBegin + i, 1);
  return s;
}

// @ 0x00abbec0   read vector<uint64_t>
struct U64Vec { uint64_t* mBegin; uint64_t* mEnd; uint64_t* mCap; void __thiscall Resize(unsigned int n); };  // 0xa6b080
IStream* __cdecl FUN_00abbec0(IStream* s, U64Vec* v) {
  unsigned int n;
  io_ReadInt32(s, &n, 1, 0);
  v->Resize(n);
  for (unsigned int i = 0; i < n; ++i) io_ReadUInt64(s, v->mBegin + i, 1, 0);
  return s;
}

// @ 0x00abbf70   vector<FilterElem>::insert(pos, n, value)
struct VBoolCopy { void __thiscall CopyCtor(const VBool* src); };  // FUN_00473140
struct VecFE {
  FilterElem* mBegin;
  FilterElem* mEnd;
  FilterElem* mCap;
  void __thiscall InsertN(FilterElem* pos, unsigned int n, const FilterElem* val);
};
extern FilterElem* __cdecl FEUninitCopy(void* dummy, FilterElem* first, FilterElem* last, FilterElem* dest);  // FUN_006f8710
extern void __cdecl FEDestroyRange(FilterElem* first, FilterElem* last, FilterElem* dummy);                    // FUN_00abb620
void __thiscall VecFE::InsertN(FilterElem* pos, unsigned int n, const FilterElem* val) {
  if (n <= (unsigned int)(mCap - mEnd)) {
    if (n != 0) {
      FilterElem tmp;
      tmp.a = val->a;
      tmp.b = val->b;
      tmp.c = val->c;
      tmp.d = val->d;
      ((VBoolCopy*)&tmp.v)->CopyCtor(&val->v);
      FilterElem* oldEnd = mEnd;
      unsigned int after = mEnd - pos;
      if (n < after) {
        FilterElem* mid = oldEnd - n;
        FEUninitCopy(&val, mid, oldEnd, oldEnd);
        mEnd += n;
        FUN_00abbe20(pos, mid, oldEnd);
        FUN_00abbd30(pos, pos + n, &tmp);
      } else {
        FUN_00abbd80(oldEnd, n - after, &tmp);
        mEnd += n - after;
        FEUninitCopy(&pos, pos, oldEnd, mEnd);
        mEnd += after;
        FUN_00abbd30(pos, oldEnd, &tmp);
      }
      EFREE(tmp.v.begin);
    }
  } else {
    int size = mEnd - mBegin;
    unsigned int grow = size * 2;
    if (size == 0) grow = 1;
    unsigned int newCap = size + n;
    if (newCap < grow) newCap = grow;
    FilterElem* mem = (FilterElem*)EALLOC(newCap * 0x28);
    FilterElem* old = mBegin;
    FUN_00abbc80(old, pos, mem);
    FilterElem* p = mem + (pos - old);
    FEDestroyRange(old, pos, mem);
    FUN_00abbd80(p, n, (FilterElem*)val);
    FilterElem* p2 = p + n;
    FilterElem* end = mEnd;
    FUN_00abbc80(pos, end, p2);
    FilterElem* nend = p2 + (end - pos);
    FEDestroyRange(pos, end, p2);
    EFREE(mBegin);
    mBegin = mem;
    mEnd = nend;
    mCap = mem + newCap;
  }
}
