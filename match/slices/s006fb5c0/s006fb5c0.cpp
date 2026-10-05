// SP pixel-fragment-shader module (part 4): vector<cFragmentDecl> assignment/swap/insert,
// pixel-shader selection, cPixelFragmentInfo assignment, and the generate-PS entry point.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" __declspec(dllimport) int __cdecl sprintf(char* dst, const char* fmt, ...);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void* operator new[](unsigned int size, int flags, const void* p);

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

struct FragDecl {
  BasicString mDecl;
  uint16_t mDataID, mSourceID, mNumConst, mOffset;
  uint32_t mFlags;
  FragDecl& operator=(const FragDecl&);
};

struct Vec28 {
  FragDecl* mpBegin;
  FragDecl* mpEnd;
  FragDecl* mpCap;
  bool empty() const { return mpBegin == mpEnd; }
  unsigned size() const { return (unsigned)((mpEnd - mpBegin) / 0x1c); }
  unsigned capacity() const { return (unsigned)((mpCap - mpBegin) / 0x1c); }
  FragDecl* begin() const { return mpBegin; }
  FragDecl* end() const { return mpEnd; }

  __declspec(noinline) Vec28& operator=(const Vec28& x);   // 0x006fb9e0
  void Swap(Vec28& o);                                     // 0x006fbb30
  void DoInsertValue(FragDecl* pos, const FragDecl& v);    // 0x006fbf70
  void DoInsertValues(FragDecl* pos, unsigned n, const FragDecl& v);  // 0x006fc1f0
  void resize(unsigned n);                                 // 0x006fc480
  void AppendN(FragDecl* pos, unsigned n, const FragDecl& v);  // 0x006fbc60
  void SwapRaw(Vec28& o);                                  // 0x006fbb30 pointer path
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
// DispatchCB: assign a temp cFragmentDecl and select the corresponding pixel shader.
// (extern "C" so the calls are plain cdecl; 006fa2c0 writes the temp, 006fb860 uses it.)
extern "C" void opAssign2c0(void* self, void* src);          // 0x006fa2c0
extern "C" bool LoadAndSelectPS(void* self, void* src);      // 0x006fb860

// @ 0x006fb8f0
extern "C" void __cdecl DispatchCB(void* self) {
  uint32_t local[8];
  opAssign2c0(self, local);
  LoadAndSelectPS(self, local);
}

// ==========================================================================================
// Stubs / approximations for the larger members (see partial.txt).

// @ 0x006fb5c0
extern "C" void* GetGeneratedPixelShader(void* a, int b) { (void)a; (void)b; return 0; }

// @ 0x006fb860
extern "C" __declspec(noinline) bool LoadAndSelectPS(void* self, void* name) {
  (void)self;
  return *(volatile int*)name != 0;  // opaque read so callers keep their temp
}

// @ 0x006fb920
extern "C" void UnregisterShaders() {}

// @ 0x006fb960
extern "C" void ClearFragments() {}

// @ 0x006fb9e0
__declspec(noinline) Vec28& Vec28::operator=(const Vec28& x) {
  if (this != &x) {
    mpBegin = x.mpBegin;
    mpEnd = x.mpEnd;
    mpCap = x.mpCap;
  }
  return *this;
}

// @ 0x006fbb30
void Vec28::Swap(Vec28& o) {
  FragDecl* a = mpBegin; mpBegin = o.mpBegin; o.mpBegin = a;
  a = mpEnd; mpEnd = o.mpEnd; o.mpEnd = a;
  a = mpCap; mpCap = o.mpCap; o.mpCap = a;
}

// @ 0x006fbc60
void Vec28::AppendN(FragDecl* pos, unsigned n, const FragDecl& v) {
  (void)pos; (void)n; (void)v;
}

// @ 0x006fbf70
void Vec28::DoInsertValue(FragDecl* pos, const FragDecl& v) { (void)pos; (void)v; }

// @ 0x006fc1f0
void Vec28::DoInsertValues(FragDecl* pos, unsigned n, const FragDecl& v) {
  (void)pos; (void)n; (void)v;
}

// @ 0x006fc480
void Vec28::resize(unsigned n) { (void)n; }

// ==========================================================================================
// @ 0x006fb310 (defined in slice s006fa2c0 as GeneratePixelShader) is referenced here only
// through the global shader system; nothing further required for this slice.
