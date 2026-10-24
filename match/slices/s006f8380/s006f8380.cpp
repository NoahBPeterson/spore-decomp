// SP::cFilterChain (retail layout, ~0x228 bytes): screen-filter application / creation.
// Member offsets are taken from the constructor at 0x006f8d40.  The class has three vtables
// (multiple inheritance), modelled here as three explicit pointer fields so the compiler does
// not emit its own vtable stores.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
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

// +0x10 : 0x100-byte custom shader-data block.
class cShaderDataCustom {
public:
  char pad[0x100];
  void Init();  // 0x0077d170
};

// 0x28-byte filter operation element (the range-copy helper at 0x006f8710 clones it).
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

// The bytes a FilterElem28::mBufBegin points at; the filter switch reads texture ids here.
struct cTexIndexBlock {
  uint8_t mIdx0;   // +0x00
  uint8_t mIdx1;   // +0x01
  uint8_t mIdx2;   // +0x02
  uint8_t mIdx3;   // +0x03
  uint8_t mIdx4;   // +0x04
  uint8_t pad05;   // +0x05
  uint8_t mIdx6;   // +0x06
};

// 0x78-byte filter descriptor (rebuilt by CreateScreenFilterInternal, destroyed by ~cFilterChain).
struct FilterDesc78 {
  FilterElem28* mBegin;     // +0x00
  FilterElem28* mEnd;       // +0x04
  uint8_t  pad08[0xc];      // +0x08
  int32_t* mScaleTable;     // +0x14  (8-byte entries, biased backward by 0x100)
  uint8_t  pad18[0x10];     // +0x18
  float*   mStrengthTable;  // +0x28
  uint8_t  pad2c[0x38];     // +0x2c
  int32_t* mTextureTable;   // +0x64  (8-byte entries)
  uint8_t  pad68[0x10];     // +0x68
  void Destroy();           // va 006f66d0
};

// A screen filter held in cFilterChain::mTexBegin.
struct cSlotNode {          // one slot->texture hash node
  uint16_t  mKey;           // +0x00
  uint8_t   pad02[6];       // +0x02
  cSlotNode* mNext;         // +0x08
};

// The 16-bit-keyed hash table embedded in a screen filter at +0x0c.
struct cSlotHash {
  uint8_t   pad00[4];       // +0x0c
  cSlotNode** mArray;       // +0x10
  int32_t   mCount;         // +0x14
  int32_t   mField18;       // +0x18
  int32_t*  FindOrInsert(uint16_t* key);           // va 006f65d0
  void      ReleaseBuckets(void* array, int n);    // va 00693230
};

class cScreenFilter {
public:
  float      mStrength;     // +0x00
  int32_t    mField04;      // +0x04
  uint16_t   mSlot;         // +0x08
  uint16_t   pad0a;         // +0x0a
  cSlotHash  mHash;         // +0x0c
  uint8_t    pad1c[0x58];   // +0x1c
  int32_t    mField74;      // +0x74

  void RemoveCameraTextures();                        // va 006f6910
  bool AddCameraTexture(unsigned a, unsigned b, int* out); // va 006f6830
  void Apply(int a, int b, int c, void* d);           // va 006f5260
  void Resolve(uint32_t a, int b);                    // va 006f8260
  bool CreateScreenFilterInternal(FilterDesc78* d);   // va 006f87f0
};

class cViewer;

// Singleton returned by 0x0067dd50; only the two vtable slots used below are named.
class cRenderSystem {
public:
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void v0c();
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual uint16_t* GetViewportInfo();       // +0x1c
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
  virtual void v30();
  virtual void v34();
  virtual void v38();
  virtual void v3c();
  virtual void v40();
  virtual void v44();
  virtual void v48();
  virtual void AttachRenderTarget(void* obj, int a, int b);   // +0x4c
};
extern "C" cRenderSystem* GetRenderSystem(); // va 0067dd50

// The camera view used by the chain (methods live elsewhere in the binary).
class cViewer {
public:
  bool Copy(cViewer* src, bool a, bool b);  // va 007c50b0
  void ApplyFrustum(float a, float b);      // va 007c4ad0
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
  void Op0(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6c30
  void Op1(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f5f80
  void Op2(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6f40
  void Op3(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f71f0
  void Op4(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6060
  void Op5(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f60f0
  void Op6(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6180
  void Op7(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6270
  void Op8(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f7430
  void Op12(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f6430
  void Op13(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f7680
  void Op15(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f6500
  void Op16(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f79a0
  void Op17(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f7f70
  void OpBig(int a0, int a1, int a, int b, int c, int a5, int a6, int viewer, int p5); // va 006f54a0
  void RemoveAt(int idx);
  void ApplyFilters(FilterDesc78* d, uint16_t count, int* p4, int p5);
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
  m154 = 0.5f;      // orig reads [0x1471064] (0.5f)
  m158 = 2.0f;      // orig reads [0x1470f1c] (2.0f), not 1.0f
  m15c = 0.5f;      // orig reads [0x1471064] (0.5f)
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
  m1a8 = 0.5f;      // orig keeps xmm1 = [0x1471064] (0.5f) alive and stores it here
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
    int slot = (int)*(int16_t*)(mArrEnd - 1);
    cScreenFilter* f = (cScreenFilter*)mTexBegin[slot];
    mIndex[slot] = -1;
    f->RemoveCameraTextures();
    f->mHash.ReleaseBuckets(f->mHash.mArray, f->mHash.mCount);
    f->mHash.mField18 = 0;
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
      ((int*)p)[2] = 0;
      ((int*)p)[1] = 0x13ef094;
      ((int*)p)[0] = 0x140b778;
      ((int*)p)[1] = 0x14188c0;
      obj = p;
    }
    GetRenderSystem()->AttachRenderTarget(obj, 0, 0);
    cScreenFilter* f2 = (cScreenFilter*)mTexBegin[slot];
    if (0.0f < f2->mStrength) f2->mStrength = 0.0f;
    while (mBitsBegin != mBitsEnd && mBitsEnd[-1] == 0) {
      mDescEnd -= 0x78;
      ((FilterDesc78*)mDescEnd)->Destroy();
      mBitsEnd -= 1;
      mArrEnd -= 1;
    }
    if (mDescBegin != mDescEnd) {
      int i = (int)((mDescEnd - mDescBegin) / 0x78) - 1;
      for (; i >= 0; --i) {
        if (mArrBegin[i] == (uint16_t)slot) {
          ((cScreenFilter*)mTexBegin[slot])
              ->CreateScreenFilterInternal((FilterDesc78*)(mDescBegin + i * 0x78));
          mIndex[slot] = i;
        }
      }
    }
  } else {
    uint32_t s = (uint32_t)(idx - 0xd);
    if (s < (uint32_t)((mDescEnd - mDescBegin) / 0x78) && s < (uint32_t)(mBitsEnd - mBitsBegin)) {
      mBitsBegin[s] = 0;
    }
  }
}

// ==========================================================================================
// @ 0x006f8380  (apply the filters of a descriptor to this chain; ret 0x10)
void cFilterChain::ApplyFilters(FilterDesc78* d, uint16_t count, int* p4, int p5) {
  if (count == 0) return;
  int last = (int)count - 1;
  for (int i = 0; i < (int)count; ++i) {
    FilterElem28* e = (FilterElem28*)((char*)d->mBegin + i * 0x28);
    uint8_t dest = e->mDest;
    int srcLo = (int)e->mSourceLo;
    int srcHi = (int)e->mSourceHi;
    if (m134) {
      ((cScreenFilter*)mTexBegin[(int)(int16_t)p5])->Apply(srcLo, srcHi, dest, p4);
    }
    mViewer->Copy((cViewer*)*p4, false, false);
    mViewer->ApplyFrustum(0.0f, 0.0f);
    if (i < last) {
      FilterElem28* nxt = (FilterElem28*)((char*)d->mBegin + i * 0x28 + 0x28);
      if (nxt->mFlags == 0x11) {
        cScreenFilter* f = (cScreenFilter*)mTexBegin[(int)(int16_t)p5];
        if (!(0.0f < f->mStrength) && f->mField04 == 0) {
          dest = nxt->mDest;
        }
      }
    }
    switch (e->mFlags) {
      case 0:  Op0(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 1:  Op1(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 2:  Op2(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 3:  Op3(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 4:  Op4(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 5:  Op5(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 6:  Op6(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 7:  Op7(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 8:  OpBig(0x78, 0, srcLo, srcHi, dest, 0, 0, (int)mViewer, p5); break;
      case 9:  OpBig(0x82, 0, srcLo, srcHi, dest, 0, 0, (int)mViewer, p5); break;
      case 10: Op8(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 12: Op12(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 13: Op13(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 14: OpBig(0xd2, 0, srcLo, srcHi, dest, 0, 0, (int)mViewer, p5); break;
      case 15: Op15(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 16: Op16(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 17: {
        cScreenFilter* f = (cScreenFilter*)mTexBegin[(int)(int16_t)p5];
        if (0.0f < f->mStrength)
          Op17(d, e, srcLo, srcHi, dest, (int)mViewer, p5);
        break;
      }
      default: break;
    }
  }
}

// ==========================================================================================
// @ 0x006f87f0  (create/refresh the screen filters described by a descriptor; ret 4)
bool cScreenFilter::CreateScreenFilterInternal(FilterDesc78* d) {
  RemoveCameraTextures();
  mHash.ReleaseBuckets(mHash.mArray, mHash.mCount);
  mHash.mField18 = 0;
  mField74 = 0;

  uint16_t* info = GetRenderSystem()->GetViewportInfo();
  uint16_t uVar2 = info[0];
  uint16_t uVar3 = info[2];

  int out = 0;
  if (!AddCameraTexture(uVar2, uVar3, &out)) {
    mSlot = 0xffff;
  } else {
    mSlot = (uint16_t)out;
  }

  char* base = (char*)d->mBegin;
  if (d->mBegin == d->mEnd)
    return true;
  uint16_t counter = (uint16_t)(uint32_t)(((char*)d->mEnd - (char*)d->mBegin) / 0x28);
  if (counter == 0)
    return true;

  int off = 0;
  do {
    FilterElem28* e = (FilterElem28*)(base + off);
    uint8_t dest = e->mDest;
    uint32_t srcLo = e->mSourceLo;
    int srcHi = (int)e->mSourceHi;
    cTexIndexBlock* tb = (cTexIndexBlock*)e->mBufBegin;

    // ---- look the source slot up in this filter's hash table.
    cSlotNode* node = mHash.mArray[(srcLo & 0xffff) % (uint32_t)mHash.mCount];
    cSlotNode* endNode = mHash.mArray[mHash.mCount];
    while (node != 0) {
      if ((uint16_t)srcLo == node->mKey) break;
      node = node->mNext;
    }
    bool sourceKnown = ((node ? node : endNode) != endNode);

    // ---- and the destination slot too.
    cSlotNode* dnode = mHash.mArray[((uint32_t)dest) % (uint32_t)mHash.mCount];
    while (dnode != 0) {
      if ((uint16_t)dest == dnode->mKey) break;
      dnode = dnode->mNext;
    }
    bool destKnown = ((dnode ? dnode : endNode) != endNode);

    if (!sourceKnown) {
      uint64_t v = ((uint64_t)(uint32_t)srcHi << 32) | (uint32_t)srcLo;
      if ((v - 0x20) < 0x20) {
        int* entry = (int*)((char*)d->mScaleTable + (srcLo & 0xffff) * 8 - 0x100);
        int scale = entry[0];
        int tex = entry[1];
        int created = 0;
        if (scale != 0) {
          if (AddCameraTexture((int)(uVar2 / scale), (int)(uVar3 / scale), &created)) {
            uint16_t key = (uint16_t)srcLo;
            *mHash.FindOrInsert(&key) = created;
          }
        } else {
          if (AddCameraTexture((unsigned)tex, (unsigned)tex, &created)) {
            uint16_t key = (uint16_t)srcLo;
            *mHash.FindOrInsert(&key) = created;
          }
        }
      } else {
        if (srcHi > 0 || srcLo >= 0x40) {
          Resolve(srcLo, srcHi);
        }
      }
    }

    if (!destKnown && (uint8_t)(dest - 0x20) < 0x20) {
      int* entry = (int*)((char*)d->mScaleTable + (uint32_t)dest * 8 - 0x100);
      int scale = entry[0];
      int tex = entry[1];
      int created = 0;
      if (scale != 0) {
        if (AddCameraTexture((int)(uVar2 / scale), (int)(uVar3 / scale), &created)) {
          uint16_t key = dest;
          *mHash.FindOrInsert(&key) = created;
        }
      } else {
        if (AddCameraTexture((unsigned)tex, (unsigned)tex, &created)) {
          uint16_t key = dest;
          *mHash.FindOrInsert(&key) = created;
        }
      }
    }

    // ---- per-filter-type fixups.
    int32_t* texTable = d->mTextureTable;
    switch (e->mFlags) {
      case 0: {
        int idx = tb->mIdx6;
        if (idx != 0xff) {
          int a = texTable[idx * 2];
          int b = texTable[idx * 2 + 1];
          if (!(b == 0 && a <= 5)) Resolve((uint32_t)a, b);
        }
        break;
      }
      case 2: {
        int idx = tb->mIdx0;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx6;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 3: {
        int idx = tb->mIdx2;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 10:
      case 13: {
        int idx = tb->mIdx0;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 16: {
        int idx = tb->mIdx1;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx2;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx3;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx4;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 17: {
        int idx = tb->mIdx0;
        if (idx != 0xff) mStrength = d->mStrengthTable[idx];
        if (tb->mIdx1 != 0) {
          mField04 = 0;
        } else if (tb->mIdx2 != 0) {
          mField04 = 1;
        }
        idx = tb->mIdx3;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      default: break;
    }

    off += 0x28;
  } while (--counter != 0);

  return true;
}