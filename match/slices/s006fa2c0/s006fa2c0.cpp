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
extern char g_emptyStr[];     // 0x01667bac  empty-string sentinel buffer
extern char g_emptyStrCap[];  // 0x01667bad  (sentinel begin + 1)

struct Str3 { char* mpBegin; char* mpEnd; char* mpCap; };

struct PixelFrag {
  uint32_t mf00;   // +0x00
  Str3     mStr1;  // +0x04
  uint32_t mf10;   // +0x10
  Str3     mStr2;  // +0x14
  uint32_t mf20;   // +0x20
  uint32_t mf24;   // +0x24
  uint32_t mf28;   // +0x28
  uint32_t mf2c;   // +0x2c
  uint32_t mf30;   // +0x30
  uint32_t mf34;   // +0x34
  uint32_t mf38;   // +0x38
  uint32_t mf3c;   // +0x3c
  uint8_t  mf40;   // +0x40
  uint8_t  mf41;   // +0x41
  uint16_t mf42;   // +0x42
  uint32_t mf44;   // +0x44
  uint32_t mf48;   // +0x48
  uint32_t mf4c;   // +0x4c
  uint32_t mf50;   // +0x50
  uint32_t mf54;   // +0x54
  uint32_t mf58;   // +0x58
  uint32_t mf5c;   // +0x5c
  uint32_t mf60;   // +0x60
  PixelFrag();                   // 0x006fafe0
  ~PixelFrag();                  // 0x006fb040
  void AssignA();                // 0x006fa2c0
  void AssignB();                // 0x006fa480
  void PushBack();               // 0x006fb0e0
};

// @ 0x006fafe0
PixelFrag::PixelFrag() : mf00(0) {
  mStr1.mpCap = g_emptyStrCap;
  char* e = g_emptyStr;
  mStr1.mpEnd = mStr1.mpBegin = e;
  mStr2.mpEnd = mStr2.mpBegin = e;
  mStr2.mpCap = g_emptyStrCap;
  mf24 = 0; mf28 = 0; mf2c = 0;
  mf38 = 0; mf3c = 0;
  mf40 = 0; mf41 = 0;
  mf44 = 0; mf48 = 0; mf4c = 0; mf50 = 0;
  mf54 = 0; mf58 = 0; mf5c = 0; mf60 = 0;
}

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
