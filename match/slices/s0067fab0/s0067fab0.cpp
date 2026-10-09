// Slice s0067fab0: App::CheatManager construction, command-registration hashing
// (FUN_0067fb80/FUN_0067fc50), HSL<->RGB colour helpers (FUN_0067fe30/FUN_0067ff30),
// EASTL 0x48/0x60-byte record copy/destroy helpers, bitset serializers and the
// cCheatManager record destructors (0x6804a0..0x680b70).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- externals
void* EAAlloc(unsigned size, const char* area, int a, int b, const char* file, int line);
void  EAFree(void* p); // 0x00f47380
extern "C" void  StreamOpShift(void* stream, const void* data, int count);   // 0x0093a9a0
extern "C" void  WriteUint32(void* pStream, const void* pData, int n, int);  // 0x0093aa70
extern "C" double ValidateDouble(double v);                                  // 0x011e0906

// ---------------------------------------------------------------- shared types
// eastl-style string (0x14 bytes here), lives at +0x28 in the 0x48-byte records.
struct cString14 {
  void* p0; void* p1; void* p2; void* p3; void* p4;
  const char* c_str();                       // 0x006b5240
  void CopyCtor(const cString14& src);       // 0x006b56f0
  void CopyAssign(const cString14& src);     // 0x006b5430
};

// 0x48-byte record: 10 dwords, cString at +0x28, 3 trailing dwords.
struct Rec48 {
  unsigned a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;  // +0x00..+0x24
  cString14 str;                                    // +0x28
  unsigned x, y, z;                                 // +0x3c,0x40,0x44

  Rec48(const Rec48& src);              // @ 0x006800c0
  Rec48* AssignFrom(const Rec48* src);  // @ 0x00680130
};

struct Vec48 {
  Rec48* mpBegin;   // +0
  Rec48* mpEnd;     // +4
  Rec48* mpCap;     // +8
};

struct Vec60 {
  char* mpBegin;    // +0
  char* mpEnd;      // +4
  char* mpCap;      // +8
};

// vtable-only stream stub (writers read through +0x30 / +0x38).
struct IOStream {
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
  virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
  virtual void Read(void* dst, int n);      // +0x30
  virtual void s34();
  virtual void Write(const void* src, int n);  // +0x38
};

// ---------------------------------------------------------------- allocator helper
static inline void FreeOwned(void* p) {
  if (p != 0 && *(int*)((char*)p - 4) != 0) EAFree(p);
}

static inline void Copy48(Rec48* dst, const Rec48* src) {
  dst->a0 = src->a0; dst->a1 = src->a1; dst->a2 = src->a2; dst->a3 = src->a3;
  dst->a4 = src->a4; dst->a5 = src->a5; dst->a6 = src->a6; dst->a7 = src->a7;
  dst->a8 = src->a8; dst->a9 = src->a9;
  dst->str.CopyAssign(src->str);
  dst->x = src->x; dst->y = src->y; dst->z = src->z;
}

// ================================================================ App::CheatManager::CheatManager
// @ 0x0067fab0
struct CheatManager {
  void* vt0;        // +0x00
  void* vt4;        // +0x04
  unsigned f8;      // +0x08
  unsigned char fc; // +0x0c
  void* f10;        // +0x10
  void* f14;        // +0x14
  unsigned f18;     // +0x18
  unsigned char f1c; // +0x1c
  unsigned f20;     // +0x20
  unsigned char f28; // +0x28
  void* f2c;        // +0x2c
  void* f30;        // +0x30
  unsigned f34;     // +0x34
  unsigned f38;     // +0x38
  unsigned f3c;     // +0x3c
  unsigned f44;     // +0x44
  void* f4c;        // +0x4c
  void* f50;        // +0x50
  unsigned f54;     // +0x54
  unsigned char f58; // +0x58
  unsigned f5c;     // +0x5c
  unsigned char f64; // +0x64
};

CheatManager* __fastcall CheatManager_ctor(CheatManager* p) {
  p->vt4 = (void*)0x13ef094;
  p->f8 = 0;
  p->vt0 = (void*)0x1401b78;
  p->vt4 = (void*)0x1401b74;
  p->fc = 0;
  p->f14 = 0; p->f18 = 0; p->f1c = 0; p->f18 = 0;
  p->f1c = 0;
  p->f20 = 0;
  p->f10 = (char*)p + 0x10;
  p->f14 = (char*)p + 0x10;
  p->f28 = 0;
  p->f30 = 0; p->f34 = 0; p->f38 = 0;
  p->f2c = (char*)p + 0x2c;
  p->f30 = (char*)p + 0x2c;
  p->f34 = 0;
  p->f38 = 0;
  p->f3c = 0;
  p->f44 = 0;
  p->f50 = 0;
  p->f4c = (char*)p + 0x4c;
  *(unsigned*)((char*)p + 0x54) = 0;
  *(unsigned*)((char*)p + 0x58) = 0;
  p->f4c = (char*)p + 0x4c;
  p->f50 = (char*)p + 0x4c;
  p->f54 = 0;
  p->f58 = 0;
  p->f5c = 0;
  p->f64 = 1;
  return p;
}

// ================================================================ 0x48 record helpers
// @ 0x006800c0
Rec48::Rec48(const Rec48& src) {
  a0 = src.a0; a1 = src.a1; a2 = src.a2; a3 = src.a3; a4 = src.a4;
  a5 = src.a5; a6 = src.a6; a7 = src.a7; a8 = src.a8; a9 = src.a9;
  str.CopyCtor(src.str);
  x = src.x; y = src.y; z = src.z;
}

// @ 0x00680130
Rec48* Rec48::AssignFrom(const Rec48* src) {
  a0 = src->a0; a1 = src->a1; a2 = src->a2; a3 = src->a3; a4 = src->a4;
  a5 = src->a5; a6 = src->a6; a7 = src->a7; a8 = src->a8; a9 = src->a9;
  str.CopyAssign(src->str);
  x = src->x; y = src->y; z = src->z;
  return this;
}

// @ 0x00680230
char* FUN_00680230(char* first, char* last, char* out) {
  while (first != last) {
    ((cString14*)(first + 0x28))->c_str();
    first += 0x48;
    out += 0x48;
  }
  return out;
}

// @ 0x00680270
Rec48* FUN_00680270(Rec48* first, Rec48* last, Rec48* out) {
  while (first != last) {
    Copy48(out, first);
    ++first;
    ++out;
  }
  return out;
}

// @ 0x00680300
Rec48* FUN_00680300(Rec48* first, Rec48* last, Rec48* out) {
  while (last != first) {
    --last;
    --out;
    Copy48(out, last);
  }
  return out;
}

// @ 0x006803f0
void __stdcall FUN_006803f0(char* first, char* last) {
  for (; first < last; first += 0x48) ((cString14*)(first + 0x28))->c_str();
}

// @ 0x006804a0
void __fastcall FUN_006804a0(char* p) {
  FreeOwned(*(void**)(p + 0x4c));
  FreeOwned(*(void**)(p + 0x38));
  FreeOwned(*(void**)(p + 0x24));
  FreeOwned(*(void**)(p + 0x10));
}

// @ 0x00680730
void __fastcall FUN_00680730(Vec48* v) {
  char* p = (char*)v->mpBegin;
  char* end = (char*)v->mpEnd;
  for (; p < end; p += 0x48) ((cString14*)(p + 0x28))->c_str();
  FreeOwned(v->mpBegin);
}

// @ 0x00680800
char* FUN_00680800(char* first, char* last, char* out) {
  while (first != last) {
    FreeOwned(*(void**)(first + 0x4c));
    FreeOwned(*(void**)(first + 0x38));
    FreeOwned(*(void**)(first + 0x24));
    FreeOwned(*(void**)(first + 0x10));
    first += 0x60;
    out += 0x60;
  }
  return out;
}

// @ 0x00680b70
void __stdcall FUN_00680b70(char* first, char* last) {
  for (; first < last; first += 0x60) {
    FreeOwned(*(void**)(first + 0x4c));
    FreeOwned(*(void**)(first + 0x38));
    FreeOwned(*(void**)(first + 0x24));
    FreeOwned(*(void**)(first + 0x10));
  }
}

// @ 0x00680930
void __fastcall FUN_00680930(char* p) {
  FreeOwned(*(void**)(p + 0xb0));
  FreeOwned(*(void**)(p + 0x9c));
  FreeOwned(*(void**)(p + 0x88));
  FreeOwned(*(void**)(p + 0x74));
  FUN_00680730((Vec48*)(p + 0x60));
}

// @ 0x006809a0
void __fastcall FUN_006809a0(char* p) {
  FreeOwned(*(void**)(p + 0x24));
  FreeOwned(*(void**)(p + 0x10));
  void* q = *(void**)p;
  if ((int)(*(int*)(p + 8) - (int)q) > 1 && q != 0) EAFree(q);
}

// @ 0x006809f0
void __fastcall FUN_006809f0(char* p) {
  FUN_00680730((Vec48*)(p + 0x10));
  void* q = *(void**)p;
  if ((int)(*(int*)(p + 8) - (int)q) > 1 && q != 0) EAFree(q);
}

// @ 0x00680b10
void __fastcall FUN_00680b10(char* p) {
  FreeOwned(*(void**)(p + 0x28));
  FreeOwned(*(void**)(p + 0x14));
  void* q = *(void**)(p + 4);
  if ((int)(*(int*)(p + 0xc) - (int)q) > 1 && q != 0) EAFree(q);
}

// @ 0x00680890  (zero-initialise a large aggregate)
void __fastcall FUN_00680890(char* p) {
#define Z4(o) (*(unsigned*)(p + (o)) = 0)
  Z4(0x00); Z4(0x04); Z4(0x08); Z4(0x0c); Z4(0x10); Z4(0x14); Z4(0x18);
  Z4(0x1c); Z4(0x20); Z4(0x24); Z4(0x28); Z4(0x2c); Z4(0x30); Z4(0x34);
  Z4(0x38); Z4(0x3c); Z4(0x40); Z4(0x44); Z4(0x48); Z4(0x4c);
  Z4(0x54); Z4(0x58); Z4(0x5c); Z4(0x60); Z4(0x64); Z4(0x68);
  Z4(0x74); Z4(0x78); Z4(0x7c);
  Z4(0x88); Z4(0x8c); Z4(0x90);
  Z4(0x9c); Z4(0xa0); Z4(0xa4);
  Z4(0xb0); Z4(0xb4); Z4(0xb8);
#undef Z4
}

// ================================================================ bitset serializers
// @ 0x00680500
void __stdcall FUN_00680500(unsigned* pBits, IOStream* pStream) {
  unsigned i = 0;
  unsigned bit = 1;
  do {
    bool b = false;
    if (i < 0x9a) b = (pBits[i >> 5] & bit) != 0;
    StreamOpShift(pStream, &b, 1);
    ++i;
    bit = (bit << 1) | (bit >> 31);
  } while ((int)i < 0x9a);
}

// @ 0x00680560
void __stdcall FUN_00680560(unsigned* pBits, IOStream* pStream) {
  unsigned i = 0;
  unsigned bit = 1;
  do {
    unsigned char b = 0;
    pStream->Read(&b, 1);
    if (i < 0x9a) {
      if (b == 0)
        pBits[i >> 5] &= ~bit;
      else
        pBits[i >> 5] |= bit;
    }
    ++i;
    bit = (bit << 1) | (bit >> 31);
  } while ((int)i < 0x9a);
}

// ================================================================ vector serializers
// @ 0x00680390
void __stdcall FUN_00680390(unsigned** pVec, IOStream* pStream) {
  int count = (int)((char*)pVec[1] - (char*)pVec[0]) >> 2;
  pStream->Write(&count, 4);
  unsigned* p = pVec[0];
  for (; p != pVec[1]; ++p) {
    unsigned tmp = *p;
    WriteUint32(pStream, &tmp, 1, 0);
  }
}

// @ 0x006805c0
extern "C" void FUN_006b56f0(cString14*, const cString14*);
void FUN_006805c0(char* pBegin, char* pEnd, IOStream* pStream) {
  int count = (int)(pEnd - pBegin) / 0x48;
  pStream->Write(&count, 4);
  for (char* it = pBegin; it != pEnd; it += 0x48) {
    unsigned bits0[5];
    unsigned bits1[5];
    for (int i = 0; i < 5; ++i) bits0[i] = *(unsigned*)(it + 4 * i);
    for (int i = 0; i < 5; ++i) bits1[i] = *(unsigned*)(it + 0x14 + 4 * i);
    cString14 tmp;
    tmp.CopyCtor(*(cString14*)(it + 0x28));
    unsigned x = *(unsigned*)(it + 0x3c);
    unsigned y = *(unsigned*)(it + 0x40);
    unsigned z = *(unsigned*)(it + 0x44);
    FUN_00680500(bits0, pStream);
    FUN_00680500(bits1, pStream);
    WriteUint32(pStream, &x, 1, 0);
    WriteUint32(pStream, &y, 1, 0);
    WriteUint32(pStream, &z, 1, 0);
    tmp.c_str();
  }
}

// ================================================================ vector copy ctor
extern "C" void FUN_00680420(void**, char*, char*, char*, void**);
// @ 0x00680a50
struct VecOps { char** FUN_00680a50(char** src); };
char** VecOps::FUN_00680a50(char** src) {
  char** dst = (char**)this;
  int n = (int)(src[1] - src[0]) / 0x48;
  char* p;
  if (n == 0)
    p = 0;
  else
    p = (char*)EAAlloc(
        n * 0x48, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
  dst[0] = p;
  dst[1] = p;
  dst[2] = p + n * 0x48;
  FUN_00680420((void**)&src, src[0], src[1], p, (void**)src);
  dst[1] = (char*)src;
  return dst;
}

// ================================================================ cheat name map (partial)
extern unsigned short gEmptyString;                                        // 0x01667bac
extern "C" void  FUN_0067e5c0(void* pThis, void** ppOut, void** pKey);     // lower_bound
extern "C" void* FUN_0067ee60(void** pKey, void** ppNode);                 // node alloc/ctor
extern "C" void  FUN_0067f790(void* pTree, void* pNode, void* pValue, void* tag);
extern "C" void  FUN_0067e830(void* pValue);                               // PairB dtor
extern "C" void  FUN_0067f0c0(void* pTree, void** pKeyOut, void* pNode);
extern "C" int   _stricmp(const char*, const char*);

// @ 0x0067fb80
void** __fastcall FUN_0067fb80(char* pThis, void** pKey) {
  void* pNode = 0;
  FUN_0067e5c0(pThis, &pNode, pKey);
  if (pNode != (void*)(pThis + 4)) {
    if (_stricmp((const char*)*pKey, *(const char**)((char*)pNode + 0x10)) >= 0)
      return (void**)((char*)pNode + 0x20);
  }
  void* pNew = 0;
  void* pValue = FUN_0067ee60(pKey, &pNew);
  void* pTree = 0;
  FUN_0067f790(&pTree, pNode, pValue, 0);
  FUN_0067e830(pValue);
  return (void**)((char*)pValue + 0x20);
}

// @ 0x0067fc50
char* __fastcall FUN_0067fc50(char* pThis, char* pName, void* pCmd, char pFlag) {
  void* pParser = *(void**)(pThis + 0x44);
  if (pParser) {
    typedef void (__thiscall *RegFn)(void*, char*, void*);
    (*(RegFn*)((char*)*(void**)pParser + 0x14))(pParser, pName, pCmd);
  }
  char* pBegin;
  char* pCap;
  int nLen = 0;
  while (pName[nLen] != 0) ++nLen;
  if (nLen + 1 < 2) {
    pBegin = (char*)&gEmptyString;
    pCap = pBegin + 1;
  } else {
    pBegin = (char*)EAAlloc(
        nLen + 1, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    pCap = pBegin + nLen + 1;
  }
  for (int i = 0; i < nLen; ++i) pBegin[i] = pName[i];
  pBegin[nLen] = 0;
  void* key[3] = {pBegin, pBegin + nLen, pCap};
  void** pValue = FUN_0067fb80(pThis, key);
  void* pOld = *pValue;
  if (pCmd != pOld) {
    if (pCmd) {
      typedef void (__thiscall *AddRefFn)(void*);
      (*(AddRefFn*)((char*)*(void**)pCmd + 0xc))(pCmd);
    }
    *pValue = pCmd;
    if (pOld) {
      typedef void (__thiscall *RelFn)(void*);
      (*(RelFn*)((char*)*(void**)pOld + 0x10))(pOld);
    }
  }
  if ((pCap - pBegin) > 1 && pBegin) EAFree(pBegin);
  if (pFlag) {
    char* qBegin;
    char* qCap;
    int n = 0;
    while (pName[n] != 0) ++n;
    if (n + 1 < 2) {
      qBegin = (char*)&gEmptyString;
      qCap = qBegin + 1;
    } else {
      qBegin = (char*)EAAlloc(
          n + 1, "App", 0, 0,
          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
          0xd1);
      qCap = qBegin + n + 1;
    }
    for (int i = 0; i < n; ++i) qBegin[i] = pName[i];
    qBegin[n] = 0;
    void* key2[3] = {qBegin, qBegin + n, qCap};
    void* pNode = 0;
    FUN_0067f0c0((void*)(pThis + 0x28), key2, pNode);
    if ((qCap - qBegin) > 1 && qBegin) EAFree(qBegin);
  }
  return pBegin;
}

// ================================================================ colour conversion
static inline float RoundHalf(float x) {
  int n;
  __asm {
    movss xmm0, x
    cvtss2si eax, xmm0
    cvtsi2ss xmm1, eax
    mov ecx, eax
    sub ecx, 1
    ucomiss xmm0, xmm1
    cmovb eax, ecx
    mov n, eax
  }
  return (float)n;
}

// @ 0x0067fe30  HSL -> RGB
int FUN_0067fe30(float* out, float h, float s, float l) {
  float hp = h + 60.0f;
  double d = ValidateDouble((double)(hp * 0.0027777778f));
  float f = hp - (float)d * 360.0f;
  float ff = f * 0.008333334f;
  int n = (int)RoundHalf(ff);
  if (ff < (float)n) n = n - 1;
  f = (f - (float)(n * 0x78)) * 0.016666668f;
  if (n == 3) n = 2;
  out[n] = l;
  float p;
  if (f <= 1.0f) {
    p = f * s;
  } else {
    p = s;
    s = (2.0f - f) * s;
  }
  out[(n + 1) % 3] = (1.0f - s) * l;
  out[(n + 2) % 3] = (1.0f - p) * l;
  return (int)out;
}

// @ 0x0067ff30  RGB -> HSL
void FUN_0067ff30(float r, float g, float b, float* ph, float* ps, float* pl) {
  if (ph == 0 || ps == 0 || pl == 0) return;
  float c[3];
  c[0] = r; c[1] = g; c[2] = b;
  float* pMin = &c[0];
  if (c[1] < *pMin) pMin = &c[1];
  if (c[2] < *pMin) pMin = &c[2];
  float* pMax = &c[0];
  if (c[1] > *pMax) pMax = &c[1];
  if (c[2] > *pMax) pMax = &c[2];
  float maxv = *pMax;
  float delta = maxv - *pMin;
  if (delta == 0.0f) {
    *ph = 0.0f; *ps = 0.0f; *pl = maxv;
    return;
  }
  float hue = 0.0f;
  if (r == maxv)
    hue = ((g - b) / delta) * 60.0f;
  else if (g == maxv)
    hue = ((b - r) / delta) * 60.0f + 120.0f;
  else if (b == maxv)
    hue = ((r - g) / delta) * 60.0f + 240.0f;
  if (hue < 0.0f) hue += 360.0f;
  *ph = hue;
  *ps = delta / maxv;
  *pl = maxv;
}
// --- equivalence checker address annotations
    void EAFree(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
