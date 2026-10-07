// SP pixel-fragment-shader module (part 4): vector<cFragmentDecl> assignment/swap/insert,
// pixel-shader selection, cPixelFragmentInfo assignment, and the generate-PS entry point.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

#include <string.h>
void operator delete[](void* p) throw();   // 0x00f47380
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);

// ==========================================================================================
// Shared element models (cFragmentDecl and its vector).
struct BasicString {
  char* mpBegin;
  char* mpEnd;
  char* mpCap;
  int   mAlloc;
  BasicString& assign(const char* first, const char* last);
  BasicString& operator=(const BasicString& o) {
    if (&o != this) assign(o.mpBegin, o.mpEnd);
    return *this;
  }
};

extern char g_emptyStr[2];   // 0x01667bac: shared empty-string storage

struct FragDecl {
  BasicString mDecl;
  uint16_t mDataID, mSourceID, mNumConst, mOffset;
  uint32_t mFlags;
  FragDecl() { mDecl.mpBegin = g_emptyStr; mDecl.mpEnd = g_emptyStr; mDecl.mpCap = g_emptyStr + 1; }
  FragDecl(const FragDecl&);                       // 0x006fa850
  ~FragDecl() {
    if (mDecl.mpCap - mDecl.mpBegin > 1 && mDecl.mpBegin) operator delete[](mDecl.mpBegin);
  }
  FragDecl& operator=(const FragDecl&);
};

// Helpers defined in slice s006fa2c0 (cdecl).
FragDecl* __cdecl do_fill28(FragDecl* first, FragDecl* last, const FragDecl& v);      // 0x006fabd0
FragDecl* __cdecl do_copy28(FragDecl* first, FragDecl* last, FragDecl* result);       // 0x006fac30
FragDecl* __cdecl do_copy_backward28(FragDecl* first, FragDecl* last, FragDecl* res); // 0x006faca0
FragDecl** __cdecl UninitCopyOut(FragDecl** out, FragDecl* first, FragDecl* last,
                                 FragDecl* dest, const void* tag);                     // 0x006fa8d0
FragDecl* __cdecl UninitCopy(FragDecl* first, FragDecl* last, FragDecl* dest);         // 0x006fa950
FragDecl* __cdecl DestroyN(FragDecl* first, FragDecl* last, FragDecl* dest);           // 0x006fa9e0
FragDecl* __cdecl UninitFillN(FragDecl* dest, unsigned n, const FragDecl& v, FragDecl* tag); // 0x006faa60

// Vector storage header test used by the vector allocator: a block whose word at [-4] is zero is
// not owned and is never freed.
static inline void FreeBlock(void* p) {
  if (p && ((int*)p)[-1] != 0) operator delete[](p);
}

template<class T> static inline void swapPtr(T& a, T& b) { T t = a; a = b; b = t; }

struct Vec28 {
  FragDecl* mpBegin;
  FragDecl* mpEnd;
  FragDecl* mpCap;
  Vec28() {}
  Vec28(const Vec28&);                                       // 0x006fad40
  ~Vec28() { DoDestroy(mpBegin, mpEnd); FreeBlock(mpBegin); }
  unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
  unsigned capacity() const { return (unsigned)(mpCap - mpBegin); }

  FragDecl* DoAllocateAndCopy(unsigned n, FragDecl* first, FragDecl* last);  // 0x006fadd0
  void DoDestroy(FragDecl* first, FragDecl* last) throw();                         // 0x006fab90
  FragDecl* erase(FragDecl* first, FragDecl* last);                          // 0x006fbc00

  // operator= at 0x006fb9e0; the body is named Assign so the equivalence checker can find it.
  __declspec(noinline) Vec28& Assign(const Vec28& x);      // 0x006fb9e0
  __forceinline Vec28& operator=(const Vec28& x) { return Assign(x); }
  void swap(Vec28& o);                                     // 0x006fbb30
  void DoInsertValues(FragDecl* pos, unsigned n, const FragDecl& v);  // 0x006fbc60
  void resize(unsigned n);                                 // 0x006fc480
};

struct VecTemp : Vec28 {
  int mPad0, mPad1;
  VecTemp(const Vec28& v) : Vec28(v) {}
};

struct ImgRef {
  void* p;
  void Assign(void* v);
};

// cPixelFragmentInfo: a pixel-fragment declaration bundle.
struct PixelFrag {
  uint32_t f0;          // +0x00
  BasicString s4;       // +0x04
  BasicString s14;      // +0x14
  Vec28 v24;            // +0x24
  uint32_t f30, f34;
  uint32_t f38, f3c;
  uint8_t b40, b41;
  uint8_t pad42[2];
  ImgRef r44;           // +0x44
  uint32_t f48, f4c, f50, f54, f58, f5c, f60;
  PixelFrag& operator=(const PixelFrag& o);  // 0x006fbed0
};

// @ 0x006fbed0
PixelFrag& PixelFrag::operator=(const PixelFrag& o) {
  f0 = o.f0;
  s4 = o.s4;
  s14 = o.s14;
  v24 = o.v24;
  f38 = o.f38;
  f3c = o.f3c;
  b40 = o.b40;
  b41 = o.b41;
  r44.Assign(o.r44.p);
  f48 = o.f48;
  f4c = o.f4c;
  f50 = o.f50;
  f54 = o.f54;
  f58 = o.f58;
  f5c = o.f5c;
  f60 = o.f60;
  return *this;
}

// ==========================================================================================
// Pixel-shader cache table (entries of 0x130 bytes, sorted by name, 0x016198a0).
struct IPixelShader {
  virtual long __stdcall QueryInterface();
  virtual long __stdcall AddRef();
  virtual long __stdcall Release();
};

struct PSEntry {
  char mName[0x20];       // +0x00 shader name key
  IPixelShader* mpPS;     // +0x20
  uint32_t mTick;         // +0x24
  int mCount;             // +0x28
  FragDecl* mpFrag[32];   // +0x2c
  uint32_t mFlags0[32];   // +0xac
  uint32_t mFlags;        // +0x12c
};

struct PSTable {
  PSEntry* mpBegin;
  PSEntry* mpEnd;
  void Grow();                                  // 0x006fb0e0
  void erase(PSEntry* first, PSEntry* last);    // 0x006fae30
  void reserve(unsigned n);                     // 0x006faae0
  void resize(unsigned n);                      // 0x006ff060
};

struct StackAlloc {                              // EA::Allocator::StackAllocator, 0x0161fda4
  int pad[2];
  char* mpEnd;                                   // +0x08
  char* mpCur;                                   // +0x0c
  char* mpLast;                                  // +0x10
  bool AllocateNewBlock(unsigned size);          // 0x00928ba0
  void Reset();                                  // 0x00928dc0
  void* Alloc(unsigned size) {
    size = (size + 7) & ~7u;
    if ((int)((mpEnd - mpCur) - size) < 0 && !AllocateNewBlock(size)) return 0;
    char* p = mpCur;
    mpCur = p + size;
    mpLast = mpCur;
    return p;
  }
};

typedef long (__stdcall* SetPSFn)(void*, void*);
typedef long (__stdcall* CreatePSFn)(void*, const void*, void*);
struct D3DDevice { void** vtbl; };

extern PSTable g_psTable;        // 0x016198a0
extern PSEntry* g_curPS;         // 0x01619760
extern int g_psMax;              // 0x015345b0
extern bool g_psFlag;            // 0x015345ac
extern uint32_t g_tick;          // 0x016f8cf8
extern StackAlloc g_stackAlloc;  // 0x0161fda4
extern D3DDevice* g_device;      // 0x016f89d0
extern IPixelShader* g_activePS; // 0x016f89cc
struct IntVec { uint32_t* mpBegin; uint32_t* mpEnd; };
extern IntVec g_vecA;            // 0x01619878
extern IntVec g_vecB;            // 0x0161988c

int __cdecl BinaryFindPixelShader(const char* key, PSEntry* base, int n);   // 0x006fdab0
void __cdecl FillPixelShader(void* a, const char* key, PSEntry* e);          // 0x006fb310
void* __cdecl MemSet(void* p, int v, unsigned n);                            // 0x011e073e
void* __cdecl MemCopy(void* dst, const void* src, unsigned n);               // 0x011e0744

// ==========================================================================================
// @ 0x006fb5c0  find or build the pixel shader for `key` (LRU-evicting sorted cache)
extern "C" IPixelShader* __cdecl GetGeneratedPixelShader(void* a, const char* key) {
  PSEntry* base = g_psTable.mpBegin;
  PSEntry* end = g_psTable.mpEnd;
  int n = (int)(end - base);
  int idx = BinaryFindPixelShader(key, base, n);
  if (idx < 0) {
    if (g_psMax != 0 && g_psMax <= n) {
      int oldest = 0, oi = 0;
      for (int i = 1; i < n; i++) {
        if (base[i].mTick < base[oi].mTick) { oldest = i; oi = i; }
      }
      PSEntry* e = &base[oldest];
      if (e->mpPS) {
        e->mpPS->Release();
        e->mpPS = 0;
        base = g_psTable.mpBegin;
        end = g_psTable.mpEnd;
      }
      memmove(&base[oldest], &base[oldest + 1], ((end - base) - oldest - 1) * sizeof(PSEntry));
      g_psTable.mpEnd--;
      n = (int)(g_psTable.mpEnd - g_psTable.mpBegin);
      idx = BinaryFindPixelShader(key, g_psTable.mpBegin, n);
    }
    idx = -1 - idx;
    g_psTable.Grow();
    if (idx < n)
      memmove(&g_psTable.mpBegin[idx + 1], &g_psTable.mpBegin[idx], (n - idx) * sizeof(PSEntry));
    g_curPS = &g_psTable.mpBegin[idx];
    MemSet(g_curPS, 0, sizeof(PSEntry));
    if (g_psFlag) FillPixelShader(a, key, g_curPS);
    g_curPS->mTick = g_tick;
    memcpy(g_curPS, key, 0x20);
    g_curPS->mCount = (int)(g_vecA.mpEnd - g_vecA.mpBegin);
    MemCopy(g_curPS->mpFrag, g_vecA.mpBegin, (g_vecA.mpEnd - g_vecA.mpBegin) * 4);
    MemCopy(g_curPS->mFlags0, g_vecB.mpBegin, (g_vecB.mpEnd - g_vecB.mpBegin) * 4);
    for (int i = 0; i < g_curPS->mCount; i++)
      g_curPS->mFlags |= g_curPS->mpFrag[i]->mFlags;
    return g_curPS->mpPS;
  }
  g_curPS = &g_psTable.mpBegin[idx];
  g_curPS->mTick = g_tick;
  return g_curPS->mpPS;
}

// ==========================================================================================
// DispatchCB: assign a temp cFragmentDecl and select the corresponding pixel shader.
// (extern "C" so the calls are plain cdecl; 006fa2c0 writes the temp, 006fb860 uses it.)
extern "C" void opAssign2c0(void* self, void* src);                  // 0x006fa2c0
extern "C" bool LoadAndSelectPS(void* self, const char* name);       // 0x006fb860

// @ 0x006fb8f0
extern "C" void __cdecl DispatchCB(void* self) {
  uint32_t local[8];
  opAssign2c0(self, local);
  LoadAndSelectPS(self, (const char*)local);
}

// @ 0x006fb860  select the pixel shader named `name` on the device; true if it changed
extern "C" __declspec(noinline) bool LoadAndSelectPS(void* self, const char* name) {
  IPixelShader* ps;
  if (g_curPS && strcmp(g_curPS->mName, name) == 0) {
    g_curPS->mTick = g_tick;
    ps = g_curPS->mpPS;
  } else {
    ps = GetGeneratedPixelShader(self, name);
  }
  bool changed = g_activePS != ps;
  if (g_activePS != ps) {
    ((SetPSFn)g_device->vtbl[0x1ac / 4])(g_device, ps);     // SetPixelShader
    g_activePS = ps;
  }
  return changed;
}

// @ 0x006fb920  drop every cached shader entry and reset the cache capacity
extern "C" void UnregisterShaders() {
  g_psTable.erase(g_psTable.mpBegin, g_psTable.mpEnd);
  g_psTable.reserve(g_psMax ? g_psMax : 0x200);
  g_curPS = 0;
}

// @ 0x006fb960  release every shader, empty the table and reset the fragment allocator
extern "C" void ClearFragments() {
  int n = (int)(g_psTable.mpEnd - g_psTable.mpBegin);
  for (int i = 0; i < n; i++) {
    PSEntry* e = &g_psTable.mpBegin[i];
    if (e->mpPS) {
      e->mpPS->Release();
      e->mpPS = 0;
    }
  }
  g_psTable.erase(g_psTable.mpBegin, g_psTable.mpEnd);
  g_stackAlloc.Reset();
}

// ==========================================================================================
// eastl::vector<cFragmentDecl> members.

// @ 0x006fb9e0
Vec28& Vec28::Assign(const Vec28& x) {
  if (&x != this) {
    FragDecl* xb = x.mpBegin;
    FragDecl* xe = x.mpEnd;
    unsigned n = (unsigned)(xe - xb);
    FragDecl* mb = mpBegin;
    if (n > (unsigned)(mpCap - mb)) {
      FragDecl* pNew = DoAllocateAndCopy(n, xb, xe);
      DoDestroy(mpBegin, mpEnd);
      FreeBlock(mpBegin);
      mpBegin = pNew;
      mpCap = pNew + n;
    } else if (n > (unsigned)(mpEnd - mb)) {
      do_copy28(xb, xb + (mpEnd - mb), mb);
      FragDecl* out;
      UninitCopyOut(&out, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
    } else {
      FragDecl* p = do_copy28(xb, xe, mb);
      DoDestroy(p, mpEnd);
    }
    mpEnd = mpBegin + n;
  }
  return *this;
}

// @ 0x006fbb30
void Vec28::swap(Vec28& o) {
  if ((mpBegin == 0 || ((int*)mpBegin)[-1] != 0) && (o.mpBegin == 0 || ((int*)o.mpBegin)[-1] != 0)) {
    swapPtr(mpBegin, o.mpBegin);
    swapPtr(mpEnd, o.mpEnd);
    swapPtr(mpCap, o.mpCap);
    return;
  }
  VecTemp temp(*this);
  *this = o;
  o = temp;
}

// @ 0x006fbc60
void Vec28::DoInsertValues(FragDecl* pos, unsigned n, const FragDecl& value) {
  if ((unsigned)(mpCap - mpEnd) >= n) {
    if (n > 0) {
      const FragDecl temp(value);
      unsigned nExtra = (unsigned)(mpEnd - pos);
      FragDecl* oldEnd = mpEnd;
      if (n < nExtra) {
        FragDecl* out;
        UninitCopyOut(&out, oldEnd - n, oldEnd, oldEnd, pos);
        mpEnd += n;
        do_copy_backward28(pos, oldEnd - n, oldEnd);
        do_fill28(pos, pos + n, temp);
      } else {
        UninitFillN(oldEnd, n - nExtra, temp, oldEnd);
        mpEnd += n - nExtra;
        FragDecl* out;
        UninitCopyOut(&out, pos, oldEnd, mpEnd, oldEnd);
        mpEnd += nExtra;
        do_fill28(pos, oldEnd, temp);
      }
    }
  } else {
    unsigned nPrev = size();
    unsigned nGrow = nPrev ? nPrev * 2 : 1;
    if (nGrow < nPrev + n) nGrow = nPrev + n;
    FragDecl* pNew = nGrow ? (FragDecl*)operator new(nGrow * sizeof(FragDecl), "Graphics", 0, 0, "", 0xd1) : 0;
    FragDecl* pNewEnd = UninitCopy(mpBegin, pos, pNew);
    DestroyN(mpBegin, pos, pNew);
    UninitFillN(pNewEnd, n, value, pNewEnd);
    pNewEnd += n;
    FragDecl* oldEnd = mpEnd;
    pNewEnd = UninitCopy(pos, oldEnd, pNewEnd);
    DestroyN(pos, oldEnd, pNewEnd);
    FreeBlock(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCap = pNew + nGrow;
  }
}

// @ 0x006fc480
void Vec28::resize(unsigned n) {
  FragDecl* b = mpBegin;
  FragDecl* e = mpEnd;
  if (n > (unsigned)(e - b)) {
    const FragDecl def;
    DoInsertValues(e, n - (unsigned)(e - b), def);
  } else {
    erase(b + n, e);
  }
}

// ==========================================================================================
// Pixel-shader cache serialization.
namespace IO { struct IStream; }
bool __cdecl WriteUint32(IO::IStream* s, const void* p, int n, int endian);   // 0x0093aa70
bool __cdecl WriteUint16(IO::IStream* s, const void* p, int n, int endian);   // 0x0093a9d0
bool __cdecl WriteBytes(IO::IStream* s, const void* p, unsigned n);           // 0x0093a9a0
bool __cdecl ReadInt32(IO::IStream* s, void* p, int n, int endian);           // 0x0093a780
bool __cdecl ReadUInt16(IO::IStream* s, void* p, int n, int endian);          // 0x0093a700
bool __cdecl ReadBytes(IO::IStream* s, void* p, unsigned n);                  // 0x0093a6c0
unsigned __cdecl GetShaderByteSize(IPixelShader* ps);                          // 0x00777740
void __cdecl GetShaderBytes(IPixelShader* ps, unsigned size, void* dst);       // 0x00777720

struct ByteVec {
  char* mpBegin;
  char* mpEnd;
  char* mpCap;
  ByteVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
  ~ByteVec() { FreeBlock(mpBegin); }
  void DoInsertValues(char* pos, unsigned n, const char& v);                  // 0x004c10e0
  // Make the buffer exactly `sz` bytes long.
  void Fit(unsigned sz) {
    if ((unsigned)(mpEnd - mpBegin) < sz) {
      char zero = 0;
      DoInsertValues(mpEnd, sz - (unsigned)(mpEnd - mpBegin), zero);
    } else {
      MemCopy(mpBegin + sz, mpEnd, 0);
      mpEnd = mpBegin + sz;
    }
  }
};

// @ 0x006fbf70  write the shader cache to a stream
void WriteShaderCache(IO::IStream* s) {
  uint32_t v = 0;
  WriteUint32(s, &v, 1, 0);
  v = (uint32_t)(g_psTable.mpEnd - g_psTable.mpBegin);
  WriteUint32(s, &v, 1, 0);
  ByteVec buf;
  int n = (int)(g_psTable.mpEnd - g_psTable.mpBegin);
  for (int i = 0; i < n; i++) {
    PSEntry* e = &g_psTable.mpBegin[i];
    uint32_t w;
    WriteBytes(s, e, 0x20);
    if (e->mpPS != 0) {
      unsigned sz = GetShaderByteSize(e->mpPS);
      buf.Fit(sz);
      GetShaderBytes(e->mpPS, sz, buf.mpBegin);
      w = sz;
      WriteUint32(s, &w, 1, 0);
      WriteBytes(s, buf.mpBegin, sz);
    } else {
      w = 0;
      WriteUint32(s, &w, 1, 0);
    }
    w = (uint32_t)e->mCount;
    WriteUint32(s, &w, 1, 0);
    for (int j = 0; j < e->mCount; j++) {
      uint32_t t0 = e->mpFrag[j]->mDataID;
      WriteUint16(s, &t0, 1, 0);
      uint32_t t1 = e->mpFrag[j]->mSourceID;
      WriteUint16(s, &t1, 1, 0);
      uint32_t t2 = e->mpFrag[j]->mNumConst;
      WriteUint16(s, &t2, 1, 0);
      uint32_t t3 = e->mpFrag[j]->mOffset;
      WriteUint16(s, &t3, 1, 0);
      uint32_t t4 = e->mpFrag[j]->mFlags;
      WriteUint32(s, &t4, 1, 0);
    }
    WriteUint32(s, e->mFlags0, e->mCount, 0);
    w = e->mFlags;
    WriteUint32(s, &w, 1, 0);
  }
}

// @ 0x006fc1f0  read the shader cache from a stream and create the D3D shaders
void ReadShaderCache(IO::IStream* s) {
  int version, count;
  ReadInt32(s, &version, 1, 0);
  ReadInt32(s, &count, 1, 0);
  g_psTable.resize(count);
  if (g_psMax < count + 0x10) g_psMax = count + 0x10;
  ByteVec buf;
  int n = (int)(g_psTable.mpEnd - g_psTable.mpBegin);
  for (int i = 0; i < n; i++) {
    PSEntry* e = &g_psTable.mpBegin[i];
    unsigned sz;
    ReadBytes(s, e, 0x20);
    ReadInt32(s, &sz, 1, 0);
    e->mpPS = 0;
    if (sz) {
      buf.Fit(sz);
      ReadBytes(s, buf.mpBegin, sz);
      ((CreatePSFn)g_device->vtbl[0x1a8 / 4])(g_device, buf.mpBegin, &e->mpPS);   // CreatePixelShader
    }
    ReadInt32(s, &e->mCount, 1, 0);
    char* p = (char*)g_stackAlloc.Alloc((unsigned)e->mCount * sizeof(FragDecl));
    for (int j = 0; j < e->mCount; j++) {
      ReadUInt16(s, p + 0x10, 1, 0);
      ReadUInt16(s, p + 0x12, 1, 0);
      ReadUInt16(s, p + 0x14, 1, 0);
      ReadUInt16(s, p + 0x16, 1, 0);
      ReadInt32(s, p + 0x18, 1, 0);
      e->mpFrag[j] = (FragDecl*)p;
      p += sizeof(FragDecl);
    }
    ReadInt32(s, e->mFlags0, e->mCount, 0);
    ReadInt32(s, &e->mFlags, 1, 0);
  }
}
