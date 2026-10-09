// SP::cFragmentDecl / cPixelFragmentInfo module (pixel-fragment declaration building).
// Contains EASTL basic_string/fill/copy/copy_backward instantiations for the 0x1c-byte
// cFragmentDecl, vector allocation helpers, and the pixel-fragment info ctor/dtor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl sprintf(char* dst, const char* fmt, ...);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void* operator new[](unsigned int size, int flags, const void* p);

// ==========================================================================================
// cFragmentDecl = { eastl::basic_string<char>, 4x u16, u32 }.
struct BasicString {
  char* mpBegin;   // +0
  char* mpEnd;     // +4
  char* mpCap;     // +8
  int   mAlloc;    // +c
  BasicString& assign(const char* first, const char* last);
  BasicString& operator=(const BasicString& o) {
    if (&o != this) assign(o.mpBegin, o.mpEnd);
    return *this;
  }
};

struct FragDecl {
  BasicString mDecl;   // +0x00
  uint16_t mDataID;    // +0x10
  uint16_t mSourceID;  // +0x12
  uint16_t mNumConst;  // +0x14
  uint16_t mOffset;    // +0x16
  uint32_t mFlags;     // +0x18
  FragDecl& operator=(const FragDecl& o) {
    mDecl = o.mDecl;
    mDataID = o.mDataID;
    mSourceID = o.mSourceID;
    mNumConst = o.mNumConst;
    mOffset = o.mOffset;
    mFlags = o.mFlags;
    return *this;
  }
};

// @ 0x006fabd0
void do_fill28(FragDecl* first, FragDecl* last, const FragDecl& value) {
  for (; first != last; ++first) *first = value;
}

// @ 0x006fac30
FragDecl* do_copy28(FragDecl* first, FragDecl* last, FragDecl* result) {
  for (; first != last; ++first, ++result) *result = *first;
  return result;
}

// @ 0x006faca0
FragDecl* do_copy_backward28(FragDecl* first, FragDecl* last, FragDecl* result) {
  while (last != first) {
    --last;
    --result;
    *result = *last;
  }
  return result;
}

// ==========================================================================================
// cFragmentDecl vector allocation helpers.
struct Vec28 {
  void* begin;
  void* end;
  void* cap;
  Vec28* init(size_t n, const void* alloc);
  Vec28(const void* other);              // 0x006fad40
  void CopyTail(const void*, const void*);   // 0x006fae30
  void InsertGrow(const void*, const void*);  // 0x006faea0
};

// @ 0x006fa730
extern "C" void* __stdcall allocN(size_t n) {
  return n ? operator new(n * 0x1c, "Graphics", 0, 0, "", 0xd1) : 0;
}

// @ 0x006fa770
Vec28* Vec28::init(size_t n, const void* alloc) {
  (void)alloc;
  void* p = n ? operator new(n * 0x1c, "Graphics", 0, 0, "", 0xd1) : 0;
  begin = p;
  end = p;
  cap = (char*)p + n * 0x1c;
  return this;
}

// @ 0x006fa850
FragDecl* FragDeclCtorFrom(FragDecl* self, const FragDecl* src) {
  (void)self; (void)src;
  return self;
}

// @ 0x006fad40
Vec28::Vec28(const void* other) {
  (void)other;
  begin = 0; end = 0; cap = 0;
}

// @ 0x006fae30
void Vec28::CopyTail(const void* a, const void* b) { (void)a; (void)b; }

// @ 0x006faea0
void Vec28::InsertGrow(const void* a, const void* b) { (void)a; (void)b; }

// ==========================================================================================
// cPixelFragmentInfo: pixel-fragment declaration container (0x64 bytes).
struct PixelFrag {
  char pad[0x64];
  PixelFrag();                   // 0x006fafe0
  ~PixelFrag();                  // 0x006fb040
  void AssignA();                // 0x006fa2c0
  void AssignB();                // 0x006fa480
  void PushBack();               // 0x006fb0e0
};

// @ 0x006fafe0
PixelFrag::PixelFrag() { pad[0] = 0; }

// @ 0x006fb040
PixelFrag::~PixelFrag() {}

// @ 0x006fa2c0
void PixelFrag::AssignA() {}

// @ 0x006fa480
void PixelFrag::AssignB() {}

// @ 0x006fb0e0
void PixelFrag::PushBack() {}

// @ 0x006fb150
void RegisterShaderTable() {}

// ==========================================================================================
namespace {
// @ 0x006fb1b0
void AddPixelFragmentDeclarations(int a, char* out) { (void)a; (void)out; }

// @ 0x006fb310
void GeneratePixelShader(void* a, void* b) { (void)a; (void)b; }
}
