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

extern void* __stdcall StringRangeInit(unsigned n);   // 0x475ab0
extern "C" void* __cdecl memset(void*, int, unsigned);

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
  FragDecl(const FragDecl& src);   // 0x006fa850 (string-range copy ctor)
};

// @ 0x006fa850  cFragmentDecl string-range constructor.
FragDecl::FragDecl(const FragDecl& src) {
  mDecl.mpBegin = 0;
  mDecl.mpEnd   = 0;
  mDecl.mpCap   = 0;

  const char* s = src.mDecl.mpBegin;
  const char* e = src.mDecl.mpEnd;
  const unsigned size = (unsigned)(e - s);

  mDecl.mpBegin = (char*)StringRangeInit(size + 1);
  char* dst = mDecl.mpBegin;
  memcpy(dst, s, size);
  mDecl.mpEnd = dst + size;
  *mDecl.mpEnd = 0;

  mDataID   = src.mDataID;
  mSourceID = src.mSourceID;
  mNumConst = src.mNumConst;
  mOffset   = src.mOffset;
  mFlags    = src.mFlags;
}

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
// ==========================================================================================
// cPixelFragmentInfo: pixel-fragment declaration container (0x64 bytes).
// ==========================================================================================
extern char g_emptyStr[];     // 0x01667bac  empty-string sentinel buffer
extern char g_emptyStrCap[];  // 0x01667bad  (sentinel begin + 1)

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);  // msvcr90 interlocked
extern "C" void  __cdecl deleteBlock(void*);      // 0xf47380 (operator delete thunk)
extern "C" void* __cdecl newBlock(unsigned n, const char* name, int flags, int dbg,
                                  const char* file, int line);  // 0xf473a0
extern "C" int   __cdecl sprintf(char* dst, const char* fmt, ...);
// The stream interface used by the serializers.
struct IStream;
namespace EA { namespace IO {
bool WriteUint32(IStream* s, const uint32_t* v, uint32_t count, int endian);  // 0x93aa70
bool WriteUint16(IStream* s, const uint16_t* v, uint32_t count, int endian);  // 0x93a9d0
bool WriteBool8(IStream* s, const bool* v, uint32_t count);                   // 0x93a9a0
bool WriteCString(IStream* s, const char* p, int count, int endian);          // 0x93adb0
}}
inline bool WriteU32(IStream* s, uint32_t v) { return EA::IO::WriteUint32(s, &v, 1, 0); }
inline bool WriteU16(IStream* s, uint16_t v) { return EA::IO::WriteUint16(s, &v, 1, 0); }
inline bool WriteB8(IStream* s, uint8_t v) { return EA::IO::WriteBool8(s, (const bool*)&v, 1); }
inline bool WriteStr(IStream* s, const char* p, int n) { return EA::IO::WriteCString(s, p, n, 0); }

extern "C" void  __cdecl FragDeclDestroyRange(void* first, void* last); // 0x6fab90

// ==========================================================================================
// The 0x64-byte pixel-fragment declaration record (also the head of the 0x130-byte
// vector element used by the shader-source builder).
// ==========================================================================================
struct PixelFrag {
  uint32_t mf00;     // +0x00
  uint32_t mf04;     // +0x04  (str1 begin)
  uint32_t mf08;     // +0x08  (str1 end)
  uint32_t mf0c;     // +0x0c  (str1 cap)
  uint32_t mf10;     // +0x10
  uint32_t mf14;     // +0x14  (str2 begin)
  uint32_t mf18;     // +0x18  (str2 end)
  uint32_t mf1c;     // +0x1c  (str2 cap)
  uint32_t mf20;     // +0x20
  uint32_t mf24;     // +0x24  (decl vector begin)
  uint32_t mf28;     // +0x28  (decl vector end)
  uint32_t mf2c;     // +0x2c  (decl vector cap)
  uint32_t mf30;     // +0x30
  uint32_t mf34;     // +0x34
  uint32_t mf38;     // +0x38
  uint32_t mf3c;     // +0x3c
  uint8_t  mf40;     // +0x40
  uint8_t  mf41;     // +0x41
  uint16_t mf42;     // +0x42
  uint32_t mf44;     // +0x44
  uint32_t mf48;     // +0x48
  uint32_t mf4c;     // +0x4c
  uint32_t mf50;     // +0x50
  uint32_t mf54;     // +0x54
  uint32_t mf58;     // +0x58
  uint32_t mf5c;     // +0x5c
  uint32_t mf60;     // +0x60

  PixelFrag();                   // 0x006fafe0
  ~PixelFrag();                  // 0x006fb040
  void PushBack();               // 0x006fb0e0
  void Serialize(IStream* s);    // 0x006fa480
};

// @ 0x006fafe0
PixelFrag::PixelFrag() : mf00(0) {
  mf0c = (uint32_t)g_emptyStrCap;
  char* e = g_emptyStr;
  mf08 = mf04 = (uint32_t)e;
  mf18 = mf14 = (uint32_t)e;
  mf1c = (uint32_t)g_emptyStrCap;
  mf24 = 0; mf28 = 0; mf2c = 0;
  mf38 = 0; mf3c = 0;
  mf40 = 0; mf41 = 0;
  mf44 = 0; mf48 = 0; mf4c = 0; mf50 = 0;
  mf54 = 0; mf58 = 0; mf5c = 0; mf60 = 0;
}

// @ 0x006fb040
PixelFrag::~PixelFrag() {
  if (mf44 != 0) {
    volatile long* pRef = (volatile long*)(mf44 + 8);
    _InterlockedExchangeAdd(pRef, -1);
    const long after = *pRef;
    if (after < 1) {
      _InterlockedExchangeAdd(pRef, 1);
    } else {
      _InterlockedExchangeAdd(pRef, 0);
    }
  }

  FragDeclDestroyRange((void*)mf24, (void*)mf28);
  if (mf24 != 0 && *(int*)(mf24 - 4) != 0) {
    deleteBlock((void*)mf24);
  }

  if ((int)(mf1c - mf14) > 1 && mf14 != 0) {
    deleteBlock((void*)mf14);
  }
  if ((int)(mf0c - mf04) > 1 && mf04 != 0) {
    deleteBlock((void*)mf04);
  }
}

// @ 0x006fa480  cFragmentDecl bulk serialization of the global pixel-fragment table.
void PixelFrag::Serialize(IStream* s) {
  PixelFrag* p = (PixelFrag*)0x16198e8;
  do {
    WriteU32(s, *(uint32_t*)((char*)p + 0x10));
    WriteU32(s, *(uint32_t*)((char*)p + 0x14));
    WriteB8(s, *(uint8_t*)((char*)p + 0x18));
    WriteB8(s, *(uint8_t*)((char*)p + 0x19));

    WriteU32(s, *(uint32_t*)((char*)p - 0x28));
    WriteStr(s, *(const char**)((char*)p - 0x24),
             *(int*)((char*)p - 0x20) - *(int*)((char*)p - 0x24));
    WriteStr(s, *(const char**)((char*)p - 0x14),
             *(int*)((char*)p - 0x10) - *(int*)((char*)p - 0x14));

    const FragDecl* d = *(const FragDecl**)((char*)p - 4);
    const int n = (int)((*(const char**)p - (const char*)d) / 0x1c);
    WriteU32(s, (uint32_t)n);
    for (int i = 0; i < n; ++i, d = (const FragDecl*)((const char*)d + 0x1c)) {
      WriteStr(s, d->mDecl.mpBegin, (int)(d->mDecl.mpEnd - d->mDecl.mpBegin));
      WriteU16(s, d->mDataID);
      WriteU16(s, d->mSourceID);
      WriteU16(s, d->mNumConst);
      WriteU16(s, d->mOffset);
      WriteU32(s, d->mFlags);
    }

    uint32_t handle;
    if (*(uint32_t*)((char*)p + 0x1c) == 0) {
      handle = 0xffffffffu; WriteU32(s, handle);
      handle = 0xffffffffu; WriteU32(s, handle);
    } else {
      handle = 0; WriteU32(s, handle);   // resolved via shared-buffer vtable slot +0x2c
      handle = 0; WriteU32(s, handle);
    }

    WriteU32(s, *(uint32_t*)((char*)p + 0x20));
    WriteU32(s, *(uint32_t*)((char*)p + 0x24));
    WriteU32(s, *(uint32_t*)((char*)p + 0x28));
    WriteU32(s, *(uint32_t*)((char*)p + 0x2c));
    WriteU32(s, *(uint32_t*)((char*)p + 0x30));
    WriteU32(s, *(uint32_t*)((char*)p + 0x34));
    WriteU32(s, *(uint32_t*)((char*)p + 0x38));

    p = (PixelFrag*)((char*)p + 0x64);
  } while ((int)p < 0x161fce8);
}

// @ 0x006fa2c0  cFragmentDecl assignment/merge into the active-state sampler table.
extern "C" int  __cdecl BuildSamplerString(int n, int decls, char* out); // 0x6fcb90
extern "C" void __cdecl SetTexture(int reg, uint32_t tex);               // 0x11f1280

void FragmentDeclAssign(int activeState, const char* in) {
  int idx = 0;
  if (*(int*)0x16f6dac != 0) {
    idx = *(int*)(*(int*)0x16f6dac + 4);
    if (*(int*)(activeState + 0x188 + idx * 0x14) ==
        *(int*)(activeState + 0x18c + idx * 0x14)) {
      idx = 0;
    }
  }

  const FragDecl* decls = *(const FragDecl**)(activeState + 0x188 + idx * 0x14);
  const int built = BuildSamplerString(
      (int)((*(int*)(activeState + 0x18c + idx * 0x14) - (int)decls) / 0x1c),
      (int)decls, (char*)in);
  ((char*)in)[built] = 0;

  for (int i = 0; i < built; ++i) {
    const uint32_t ch = (uint8_t)in[i];
    const uint32_t entry = 0x1619904 + ch * 0x64;
    if (*(uint32_t*)entry == 0) {
      continue;
    }

    int reg = 0;
    const char* q = in;
    uint32_t c = (uint8_t)*q;
    if (c != ch) {
      do {
        reg += *(uint8_t*)(0x1619900 + c * 0x64);
        c = (uint8_t)q[1];
        ++q;
      } while (c != ch);
      if (reg >= 0x11) {
        continue;
      }
    }

    SetTexture(reg, *(uint32_t*)entry);
    *(uint32_t*)0x16f8b00 |= (1u << (reg & 0x1f));

    const int nState = *(int*)(0x1619914 + ch * 0x64);
    if (nState > 0) {
      uint32_t dirty = *(uint32_t*)(0x16f9530 + reg * 4);
      const uint32_t* src = (const uint32_t*)(0x1619918 + ch * 0x64);
      uint32_t* dst = (uint32_t*)(0x16f9fcc + reg * 0x38);
      uint32_t bits = 1;
      for (int k = nState; k != 0; --k) {
        *dst++ = *src++;
        dirty |= bits;
        bits = (bits >> 31) | (bits << 1);
      }
      *(uint32_t*)(0x16f9530 + reg * 4) = dirty;
    }

    uint32_t w;
    if ((w = *(uint32_t*)(0x1619908 + ch * 0x64)) != 0) {
      *(uint32_t*)(0x16f9530 + reg * 4) |= 0x20;
      *(uint32_t*)(0x16f9fe0 + reg * 0x38) = w;
    }
    if ((w = *(uint32_t*)(0x161990c + ch * 0x64)) != 0) {
      *(uint32_t*)(0x16f9530 + reg * 4) |= 0x10;
      *(uint32_t*)(0x16f9fdc + reg * 0x38) = w;
    }
    if ((w = *(uint32_t*)(0x1619910 + ch * 0x64)) != 0) {
      *(uint32_t*)(0x16f9530 + reg * 4) |= 0x40;
      *(uint32_t*)(0x16f9fe4 + reg * 0x38) = w;
    }
  }
}

// ==========================================================================================
// Vec28 (0x130-byte element vector) helpers.
// ==========================================================================================
extern "C" void* __cdecl RangeCopyCtor(void* dst, const void* first, void* out);  // 0x6fe2d0
extern "C" void  __cdecl RangeCopyBack(void* first, const void* last, void* dst); // 0x6fe310
extern "C" void* __cdecl DoAllocateImpl(void* self, unsigned n, const void* alloc); // 0x6fa770
extern "C" void* __cdecl Vec28CtorImpl(void* out, const void* first, const void* last,
                                       void* dst, const void* alloc); // 0x6fa8d0

// @ 0x006fad40
Vec28::Vec28(const void* other) {
  const char* o = (const char*)other;
  DoAllocateImpl(this, 0, o + 0x0c);
  Vec28CtorImpl(this, 0, 0, begin, o + 0x0c);
}

// @ 0x006fae30
void Vec28::CopyTail(const void* first, const void* last) {
  char* dst = (char*)end;
  const char* src = (const char*)first;
  const char* stop = (const char*)last;
  while (src != stop) {
    for (unsigned i = 0; i < 0x130 / 4; ++i) {
      ((uint32_t*)dst)[i] = ((const uint32_t*)src)[i];
    }
    dst += 0x130;
    src += 0x130;
  }
  const unsigned added = (unsigned)((const char*)last - (const char*)first) / 0x130;
  end = (char*)end + added * 0x130;
}

// @ 0x006faea0
void Vec28::InsertGrow(const void* first, const void* last) {
  char* e = (char*)end;
  if (e != (char*)cap) {
    const char* ins = (const char*)first;
    if (ins >= (const char*)last && (const char*)last < e) {
      ins += 0x130;
    }
    if (e != 0) {
      memcpy(e, e - 0x130, 0x130);
    }
    RangeCopyBack((char*)end - 0x130, end, (void*)last);
    memcpy((void*)last, ins, 0x130);
    end = (char*)end + 0x130;
    return;
  }

  unsigned n = (unsigned)((e - (char*)begin) / 0x130);
  if (n == 0) {
    n = 1;
  } else {
    n *= 2;
  }
  void* newBase = (void*)0;
  if (n != 0) {
    newBase = newBlock(n * 0x130, "Graphics", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                       0xd1);
  }
  char* mid = (char*)RangeCopyCtor(begin, first, newBase);
  if (mid != 0) {
    memcpy(mid, last, 0x130);
  }
  char* newEnd = (char*)RangeCopyCtor((void*)last, end, mid + 0x130);
  if (begin != 0 && *(int*)((char*)begin - 4) != 0) {
    deleteBlock(begin);
  }
  end   = newEnd;
  begin = newBase;
  cap   = (char*)newBase + n * 0x130;
}

// @ 0x006fb0e0
void PixelFrag::PushBack() {
  Vec28* v = (Vec28*)((char*)this + 0x04);   // element vector lives at PixelFrag+0x04
  char* e = (char*)v->end;
  if (e < (char*)v->cap) {
    v->end = e + 0x130;
    if (e != 0) {
      memset(e, 0, 0x130);
    }
    return;
  }
  char tmp[0x130];
  memset(tmp, 0, 0x130);
  v->InsertGrow(tmp, tmp);
}

// @ 0x006fb150
void RegisterShaderTable() {
  uint32_t* aBegin = *(uint32_t**)0x1619878;
  uint32_t* aEnd   = *(uint32_t**)0x161987c;
  memcpy(aBegin, aEnd, 0);
  const int removedA = (int)(aEnd - aBegin);
  *(uint32_t**)0x161987c = aEnd - removedA;

  uint32_t* bBegin = *(uint32_t**)0x161988c;
  uint32_t* bEnd   = *(uint32_t**)0x1619890;
  memcpy(bBegin, bEnd, 0);
  const int removedB = (int)(bEnd - bBegin);
  *(uint32_t**)0x1619890 = bEnd - removedB;
}

// ==========================================================================================
// Anonymous-namespace shader-source builders.
// ==========================================================================================
extern "C" int  __cdecl ShaderNameMatches(const void* decl);        // 0x6fa250
extern "C" void __cdecl Vec28_PushPair(void* vec, const void* v);  // 0x6ec4a0
extern "C" void __cdecl SPVectorI_DoInsertValue(void* vec, uint32_t* v); // 0x4558a0

// Shader-source assembly externs (callees, not slice targets).
extern "C" char* __cdecl GenerateInputStruct(char* out, uint32_t a, uint32_t b, uint32_t c); // 0x6f9f00
extern "C" char* __cdecl GenerateCurrentStruct(char* out, uint32_t a);   // 0x6fa010
extern "C" char* __cdecl GenerateOutputStruct(char* out, uint32_t a);    // 0x6fa0a0
extern "C" char* __cdecl GenerateFillOutputStruct(char* out, uint32_t a); // 0x6fa130
extern "C" char* __cdecl TextCopy(char* out, const char* src);           // 0x6fd9a0
extern "C" char* __cdecl SP_TextCopySubstitute(char* out, const char* tpl, int a, int b, int c, int d); // 0x6fd9c0
extern "C" char* __cdecl PSProfileFromVersion(int v);                    // 0x7776f0
extern "C" int   __cdecl D3DXCompileShader(const void* src, int len, const void* a,
                                           const void* b, const void* entry, const char* profile,
                                           const void* flags, void** blob, void** errors); // 0x11e1fd4
#define VT(p) (*(void***)(p))


namespace {
// @ 0x006fb1b0
char* AddPixelFragmentDeclarations(char* out, int tableIndex, int* regBase, int samplerBase) {
  const char* base = (const char*)0x16198c0 + tableIndex * 0x64;

  const uint8_t nSampler = *(const uint8_t*)(base + 0x40);
  for (int i = 0; i < (int)nSampler; ++i) {
    out += sprintf(out, "extern uniform sampler Sampler%d : register(s%d);\n",
                   samplerBase, samplerBase);
    ++samplerBase;
  }

  const FragDecl* d = *(const FragDecl**)(base + 0x24);
  const FragDecl* dEnd = *(const FragDecl**)(base + 0x28);
  const int count = (int)(dEnd - d);
  for (int i = 0; i < count; ++i, d = (const FragDecl*)((const char*)d + 0x1c)) {
    if (ShaderNameMatches(d)) {
      continue;
    }
    Vec28_PushPair((void*)0x1619878, &d);
    SPVectorI_DoInsertValue((void*)0x161988c, (uint32_t*)regBase);
    out += sprintf(out, "extern uniform %s : register(c%d);\n", d->mDecl.mpBegin, *regBase);
    *regBase += d->mNumConst;
  }

  const char* prologue = *(const char**)(base + 0x14);
  if (prologue != *(const char**)(base + 0x18)) {
    out += sprintf(out, "\n%s\n\n", prologue);
  }
  return out;
}

// @ 0x006fb310
void GeneratePixelShader(void* a, void* b) {
  // a = the shader-material record, b = the 32-entry permutation key string.
  const char* perm = (const char*)b;

  char buffer[0x1300];
  uint32_t usedFlagsA = 0;    // local_4c / uVar9-style OR accumulator
  uint32_t usedFlagsB = 0;    // local_48
  uint32_t myb = 0;           // ebx accumulator
  int idx = 0;                // edi (input-register index)
  uint8_t regBase = 0;        // local_4d (next available register)
  char* out = buffer;
  *out = 0;

  RegisterShaderTable();

  // 1. Scan the 32 permuted table entries, accumulating register usage.
  for (int k = 0; k < 0x20 && perm[k] != 0; ++k) {
    const uint8_t ch = (uint8_t)perm[k];
    const char* base = (const char*)0x16198c0 + ch * 0x64;
    const uint32_t f38 = *(uint32_t*)(base + 0x38);
    const uint32_t f3c = *(uint32_t*)(base + 0x3c);
    usedFlagsB |= f38;
    myb        |= f3c;

    if ((f38 & 0xffff0000) != 0) {
      uint8_t n = *(uint8_t*)(base + 0x3a);
      if ((int)n + regBase > 8) {
        n = 8 - regBase;
      }
      const uint8_t cnt = n;
      for (int r = 0; r < cnt; ++r) {
        usedFlagsA |= (1u << ((regBase + 6 + r) & 0x1f));
      }
      regBase += n;
    }

    // Emit declarations when the entry has samplers, uniforms, or a name.
    if (*(uint8_t*)(base + 0x41) > 0 || *(uint8_t*)(base + 0x40) > 0 ||
        *(uint32_t*)(base + 0x14) != *(uint32_t*)(base + 0x18)) {
      out = AddPixelFragmentDeclarations(out, ch, &idx, regBase);
    }
    regBase += *(uint8_t*)(base + 0x40);
  }

  // 2. Append the generated input/current/output struct declarations.
  out = GenerateInputStruct(out, usedFlagsB, regBase, usedFlagsA);
  out = GenerateCurrentStruct(out, usedFlagsA);
  out = GenerateOutputStruct(out, usedFlagsA);
  out = TextCopy(out, *(const char**)0x15345a4);
  out = TextCopy(out, (const char*)0x1401b70);
  if ((myb & 2) != 0 && (usedFlagsB & 0x20) != 0) {
    out = TextCopy(out, (const char*)0x140b9cc);
  }

  // 3. Substitute each permutation entry's body template.
  int argOff = 0;
  for (int k = 0; k < 0x20 && perm[k] != 0; ++k) {
    const uint8_t ch = (uint8_t)perm[k];
    const char* tpl = *(const char**)(0x16198c4 + ch * 0x64);
    const uint8_t sub = *(const uint8_t*)((const char*)b + 0x40 + k);
    out = SP_TextCopySubstitute(out, tpl, sub, 0, argOff, 0);
    argOff += *(uint8_t*)(0x1619900 + ch * 0x64);
  }

  out = GenerateFillOutputStruct(out, usedFlagsA);
  char* end = TextCopy(out, *(const char**)0x15345a0);
  *end = 0;

  // 4. Compile the assembled source (profile/generation packed into two args).
  uint32_t version = *(uint16_t*)((const char*)a + 0x12);
  if (version != 0) {
    version |= 0xffff0000u;
  }
  char* profile = PSProfileFromVersion(version);
  int flags = 0x12;
  if ((*(uint8_t*)((const char*)a + 0x44) & 2) != 0) {
    flags = 0x32;
  }

  void* blob = 0;
  void* errors = 0;
  const int ok = D3DXCompileShader(buffer, 0, 0, 0, (const void*)0x140bb6c, profile,
                                   (const void*)flags, &blob, &errors);
  if (ok >= 0) {
    if (errors != 0) {
      ((void (__thiscall*)(void*))VT(errors)[2])(errors);
    }
    void* device = *(void**)0x16f89d0;
    void* text = ((void* (__thiscall*)(void*, void*))VT(blob)[3])(blob, errors);
    ((void (__thiscall*)(void*, void*))VT((char*)device + 0x1a8)[0])((char*)device + 0x1a8, text);
    ((void (__thiscall*)(void*))VT(blob)[2])(blob);
  }
}
}  // namespace
