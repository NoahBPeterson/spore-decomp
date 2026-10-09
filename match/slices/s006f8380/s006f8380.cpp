// SP::cFilterChain (retail layout, ~0x228 bytes): screen-filter application / creation.
// Member offsets are taken from the constructor at 0x006f8d40.  The class has three vtables
// (multiple inheritance), modelled here as three explicit pointer fields so the compiler does
// not emit its own vtable stores.  Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);

class cViewer;
class cIGraphicsSystem;

// +0x10 : 0x100-byte custom shader-data block.
class cShaderDataCustom {
public:
  char pad[0x100];
  void Init();  // 0x0077d170
};

// 0x28-byte filter element (the range-copy helper at 0x006f8710 clones it).
struct FilterElem28 {
  uint8_t  mFlags;      // +0x00
  uint8_t  mDest;       // +0x01
  uint8_t  pad02[6];    // +0x02
  uint32_t mSourceLo;   // +0x08
  uint32_t mSourceHi;   // +0x0c
  uint8_t* mBufBegin;   // +0x10
  uint8_t* mBufEnd;     // +0x14
  uint8_t* mBufCap;     // +0x18
  uint32_t mTail[4];    // +0x1c
};

struct FilterVec28 {
  FilterElem28* begin;
  FilterElem28* end;
  FilterElem28* cap;
};

// 0x78-byte filter descriptor (destroyed element-wise by ~cFilterChain).
struct FilterDesc78 {
  char pad[0x78];
  void Destroy();  // 0x006f66d0
};

class cFilterChain {
public:
  void*  vtbl0;                 // +0x000
  void*  vtbl1;                 // +0x004
  void*  vtbl2;                 // +0x008
  int32_t m00c;                 // +0x00c
  cShaderDataCustom mCustomSD;  // +0x010
  float  m110, m114, m118;      // +0x110
  float  m11c;                  // +0x11c
  uint8_t* mDescBegin;          // +0x120
  uint8_t* mDescEnd;            // +0x124
  uint8_t* mDescCap;            // +0x128
  uint8_t pad12c[8];            // +0x12c
  uint8_t m134;                 // +0x134
  uint8_t pad135[3];            // +0x135
  void**  mTexBegin;            // +0x138
  void**  mTexEnd;              // +0x13c
  void**  mTexCap;              // +0x140
  uint8_t pad144[8];            // +0x144
  float  m14c, m150, m154, m158, m15c, m160;
  uint8_t pad164[0xc];          // +0x164
  float  m170;                  // +0x170
  uint8_t pad174[8];            // +0x174
  cViewer* mViewer;             // +0x17c
  uint8_t pad180[4];            // +0x180
  uint8_t m184;                 // +0x184
  uint8_t pad185[3];            // +0x185
  float  m188, m18c, m190, m194, m198, m19c, m1a0;
  uint8_t m1a4;                 // +0x1a4
  uint8_t pad1a5[3];            // +0x1a5
  float  m1a8, m1ac, m1b0;
  int32_t mIndex[17];           // +0x1b4
  uint8_t m1f8;                 // +0x1f8
  uint8_t pad1f9[3];            // +0x1f9
  uint8_t* mBitsBegin;          // +0x1fc
  uint8_t* mBitsEnd;            // +0x200
  uint8_t* mBitsCap;            // +0x204
  uint8_t pad208[8];            // +0x208
  uint16_t* mArrBegin;          // +0x210
  uint16_t* mArrEnd;            // +0x214
  uint16_t* mArrCap;            // +0x218
  uint8_t pad21c[8];            // +0x21c
  int32_t m224;                 // +0x224

  cFilterChain();
  ~cFilterChain();

  // thiscall callees (bodies live elsewhere in the binary).
  bool AddCameraTexture(int a, int b, int* out);          // 0x006f6830
  void* FindSlot(uint16_t id);                            // 0x006f65d0
  void Sub0(FilterElem28*, int, int, int, int, int, int); // 0x006f6c30
  void Sub1(FilterElem28*, int, int, int, int, int, int); // 0x006f5f80
  void Sub2(FilterElem28*, int, int, int, int, int, int); // 0x006f6f40
  void Sub3(FilterElem28*, int, int, int, int, int, int); // 0x006f71f0
  void Sub4(FilterElem28*, int, int, int, int, int, int); // 0x006f6060
  void Sub5(FilterElem28*, int, int, int, int, int, int); // 0x006f60f0
  void Sub6(FilterElem28*, int, int, int, int, int, int); // 0x006f6180
  void Sub7(FilterElem28*, int, int, int, int, int, int); // 0x006f6270
  void Sub8(FilterElem28*, int, int, int, int, int, int); // 0x006f6430
  void Sub9(FilterElem28*, int, int, int, int, int, int); // 0x006f6500
  void Sub10(FilterElem28*, int, int, int, int, int, int);// 0x006f7680
  void Sub11(FilterElem28*, int, int, int, int, int, int);// 0x006f79a0
  void Sub12(FilterElem28*, int, int, int, int, int, int);// 0x006f7430
  void Sub13(FilterElem28*, int, int, int, int, int, int);// 0x006f7f70 ApplyStrengthFilter
  void Sub14(FilterElem28*, int, int, int, int, int, int);// 0x006f71f0 slot used twice
  void BigCreate(int, int, int, int, int, int, int, int);// 0x006f54a0
  void AddRect(int a, int b);                             // 0x006f8260
  void ResetHashed();                                     // 0x006f6910
  void InitBuckets(int, int);                             // hashtable DoAllocateBuckets
  bool CreateScreenFilterInternal(FilterVec28* v);        // 0x006f87f0
  void RemoveAt(int idx);                                 // 0x006f9020
  void ApplyFilters(FilterVec28* v, uint16_t count, void* p4, int p5);  // 0x006f8380
  int p5_unused();
};

// ---- external globals referenced by the constructor --------------------------------------
extern float g1619524, g1619528, g161952c;
extern float g13f1160, g1477fbc, g1485720, g1485544;
extern float g1534250, g1534254, g1534258;
extern float g16194f8, g16194fc, g1619500;

static inline void FreeGuarded(void* p) {
  if (p != 0 && *((int*)p - 1) != 0) EASTL_allocator_deallocate(p);
}

// ==========================================================================================
// @ 0x006f8d40  (constructor)
cFilterChain::cFilterChain() {
  vtbl1 = (void*)0x13eb384;
  vtbl2 = (void*)0x13ec458;
  m00c = 0;
  mCustomSD.Init();
  vtbl0 = (void*)0x140b7b8;
  vtbl1 = (void*)0x140b7a8;
  vtbl2 = (void*)0x140b798;

  m110 = g1619524;
  m114 = g1619528;
  m118 = g161952c;
  m11c = 0.0f;
  mDescBegin = 0;
  mDescEnd = 0;
  mDescCap = 0;
  m134 = 0;
  mTexBegin = 0;
  mTexEnd = 0;
  mTexCap = 0;
  m14c = g1477fbc;
  m150 = g13f1160;
  m154 = 0.5f;
  m158 = 1.0f;
  m15c = 0.5f;
  m160 = g1477fbc;
  m170 = g1485720;
  mViewer = 0;
  m184 = 0;
  m188 = g1534250;
  m18c = g1534254;
  m190 = g1534258;
  m194 = g16194f8;
  m198 = g16194fc;
  m19c = g1619500;
  m1a0 = 0.0f;
  m1a4 = 0;
  m1a8 = g13f1160;
  m1ac = 0.0f;
  m1b0 = g1485544;
  m1f8 = 0;
  mBitsBegin = 0;
  mBitsEnd = 0;
  mBitsCap = 0;
  mArrBegin = 0;
  mArrEnd = 0;
  mArrCap = 0;
  m224 = 0;
}

// ==========================================================================================
// @ 0x006f8f60  (destructor)
cFilterChain::~cFilterChain() {
  vtbl0 = (void*)0x140b7b8;
  vtbl1 = (void*)0x140b7a8;
  vtbl2 = (void*)0x140b798;
  _ReadWriteBarrier();

  FreeGuarded(mArrBegin);
  FreeGuarded(mBitsBegin);
  FreeGuarded(mTexBegin);

  uint8_t* p = mDescBegin;
  uint8_t* e = mDescEnd;
  while (p < e) {
    ((FilterDesc78*)p)->Destroy();
    p += 0x78;
  }
  FreeGuarded(mDescBegin);

  vtbl2 = (void*)0x13ec458;
  vtbl1 = (void*)0x13eb394;
  vtbl0 = (void*)0x13eb938;
}

// ==========================================================================================
// @ 0x006f8710  (uninitialized range copy of 0x28-byte elements; __cdecl)
extern "C" FilterElem28** __cdecl CopyFilterRange(FilterElem28** dst, const FilterElem28* first,
                                                  const FilterElem28* last, FilterElem28* result) {
  *dst = result;
  if (first != last) {
    for (; first != last; first = (const FilterElem28*)((const char*)first + 0x28)) {
      FilterElem28* p = *dst;
      if (p != 0) {
        p->mFlags = first->mFlags;
        p->mDest = first->mDest;
        p->mSourceLo = first->mSourceLo;
        p->mSourceHi = first->mSourceHi;
        uint32_t n = (uint32_t)((const char*)first->mBufEnd - (const char*)first->mBufBegin);
        uint8_t* buf = 0;
        if (n != 0) {
          buf = (uint8_t*)EASTL_allocator_allocate(
              n, "Graphics", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1);
        }
        p->mBufBegin = buf;
        p->mBufEnd = buf;
        p->mBufCap = buf + n;
        memcpy(buf, first->mBufBegin, n);
        p->mBufEnd = buf + n;
      }
      *dst = (FilterElem28*)((char*)*dst + 0x28);
    }
  }
  return dst;
}

// ==========================================================================================
// @ 0x006f9020  (remove a screen filter slot by index; ret 4)
void cFilterChain::RemoveAt(int idx) {
  int n = (int)((mDescEnd - mDescBegin) / 0x78) + 0xc;
  if (idx == n) {
    uint16_t slot = ((uint16_t*)mArrEnd)[-1];
    FilterElem28* d = (FilterElem28*)mTexBegin[slot];
    mIndex[slot] = -1;
    ResetHashed();
    InitBuckets(0, 0);
    *(int*)((char*)d + 0x18) = 0;
    if (mDescBegin != mDescEnd) {
      mDescEnd -= 0x78;
      ((FilterDesc78*)mDescEnd)->Destroy();
      mBitsEnd -= 1;
      mArrEnd -= 1;
    }
    m184 = 0;
    void* p = operator new(0xc, "Graphics", 0, 0, 0, 0);
    void* obj = 0;
    if (p != 0) {
      ((void**)p)[2] = 0;
      ((void**)p)[1] = (void*)0x13ef094;
      ((void**)p)[0] = (void*)0x140b778;
      ((void**)p)[1] = (void*)0x14188c0;
      obj = p;
    }
    ((void(__thiscall*)(void*, void*, int, int))(*(void***)obj)[0x13])(obj, 0, 0, 0);
    FilterElem28* f = (FilterElem28*)mTexBegin[slot];
    if (0.0f < *(float*)f) *(float*)f = 0.0f;
    while (mBitsBegin != mBitsEnd && mBitsEnd[-1] == 0) {
      mDescEnd -= 0x78;
      ((FilterDesc78*)mDescEnd)->Destroy();
      mBitsEnd -= 1;
      mArrEnd -= 1;
    }
    if (mDescBegin != mDescEnd) {
      int i = (int)((mDescEnd - mDescBegin) / 0x78) - 1;
      int off = i * 0x78;
      for (; i >= 0; i--, off -= 0x78) {
        if (mArrBegin[i] == slot) {
          CreateScreenFilterInternal((FilterVec28*)(mDescBegin + off));
          mIndex[slot] = i;
        }
      }
    }
  } else {
    uint32_t s = idx - 0xd;
    if (s < (uint32_t)((mDescEnd - mDescBegin) / 0x78) && s < (uint32_t)(mBitsEnd - mBitsBegin)) {
      mBitsBegin[s] = 0;
    }
  }
}

// ==========================================================================================
// @ 0x006f8380  (apply the filters of a cFilterChainDesc to this chain; ret 0x10)
void cFilterChain::ApplyFilters(FilterVec28* v, uint16_t count, void* p4, int p5) {
  if (count == 0) return;
  int last = (int)count - 1;
  int off = 0;
  for (uint32_t i = 0; i < count; ++i, off += 0x28) {
    FilterElem28* e = (FilterElem28*)((char*)v->begin + off);
    uint8_t dest = e->mDest;
    uint32_t src = e->mSourceLo;
    uint32_t srcHi = e->mSourceHi;
    if (m134) {
      Sub0(e, (int)src, (int)srcHi, dest, 0, 0, 0);
    }
    AddCameraTexture(0, 0, 0);
    AddRect(0, 0);
    if (off < last * 0x28) {
      FilterElem28* nxt = (FilterElem28*)((char*)v->begin + off + 0x28);
      if (nxt->mFlags == 0x11) {
        FilterElem28* tex = (FilterElem28*)mTexBegin[(int)(short)src];
        if (!(0.0f < *(float*)tex) && *(int*)((char*)tex + 4) == 0) {
          dest = nxt->mDest;
        }
      }
    }
    switch (e->mFlags) {
      case 0:  Sub0(e, 0, 0, 0, 0, 0, 0); break;
      case 1:  Sub1(e, 0, 0, 0, 0, 0, 0); break;
      case 2:  Sub2(e, 0, 0, 0, 0, 0, 0); break;
      case 3:  Sub3(e, 0, 0, 0, 0, 0, 0); break;
      case 4:  Sub4(e, 0, 0, 0, 0, 0, 0); break;
      case 5:  Sub5(e, 0, 0, 0, 0, 0, 0); break;
      case 6:  Sub6(e, 0, 0, 0, 0, 0, 0); break;
      case 7:  Sub7(e, 0, 0, 0, 0, 0, 0); break;
      case 8:  BigCreate(0, 0, 0, 0, 0, 0, 0, 0); break;
      case 9:  BigCreate(0, 0, 0, 0, 0, 0, 0, 0); break;
      case 10: Sub12(e, 0, 0, 0, 0, 0, 0); break;
      case 11: Sub8(e, 0, 0, 0, 0, 0, 0); break;
      case 12: Sub10(e, 0, 0, 0, 0, 0, 0); break;
      case 13: BigCreate(0, 0, 0, 0, 0, 0, 0, 0); break;
      case 14: Sub9(e, 0, 0, 0, 0, 0, 0); break;
      case 15: Sub11(e, 0, 0, 0, 0, 0, 0); break;
      case 16: Sub2(e, 0, 0, 0, 0, 0, 0); break;
      case 17: {
        float f = *(float*)mTexBegin[(int)(short)src];
        if (f > 0.0f) Sub13(e, 0, 0, 0, 0, 0, 0);
        break;
      }
      default: break;
    }
  }
}

// ==========================================================================================
// @ 0x006f87f0  (create screen filters from a descriptor; ret 4)
bool cFilterChain::CreateScreenFilterInternal(FilterVec28* v) {
  ResetHashed();
  InitBuckets(0, 0);
  *(float*)((char*)&mCustomSD + 0x0c) = 0.0f;
  *(float*)((char*)&mCustomSD + 0x6c) = 0.0f;

  void* mgr = 0;  // FUN_0067dd50()
  void* info = 0;
  int t0 = 0, t1 = 0;
  int rectid = 0;
  if (!AddCameraTexture(t0, t1, &rectid)) {
    mIndex[0] = 0xffff;
  } else {
    *(int*)((char*)this + 0x1f8) = rectid;
  }
  (void)info;
  (void)mgr;
  (void)p5_unused();
  return true;
}

int cFilterChain::p5_unused() { return 0; }
