// src/game/SPEngine/SPGraphicsFragmentPS.cpp -- migrated from slice(s) s006fc540, s006fd520, s006fb5c0, s006fa2c0, s006f9250 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFragmentPS.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl sprintf(char* dst, const char* fmt, ...);

// ---- items of slice s006f9250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int g_shaderDataDirty[];   // 0x016f89f8 (rw::graphics::ActiveState::m_shaderDataDirty)
extern void* g_shaderFns[];                // 0x016fa604
namespace SP {
 char* TextCopy(char* dst, const char* src); 
}
struct ShaderRec {
  char pad00[0x10];
  unsigned short field10;   // +0x10
  unsigned short field12;   // +0x12
  unsigned short field14;   // +0x14
  char pad16[2];
  unsigned int   field18;   // +0x18
};
struct ShaderMgr {
  char pad00[0x28];
  int          count;       // +0x28
  ShaderRec**  recs;        // +0x2c
  char pad30[0xac - 0x30];
  void**       objects;     // +0xac
  char padb0[0x12c - 0xb0];
  unsigned int field12c;    // +0x12c
};
extern ShaderMgr* g_shaderMgr;             // 0x01619760
struct ShaderDef { char* mName; };
extern ShaderDef** g_shaderDefsBegin;   // 0x01619878
extern ShaderDef** g_shaderDefsEnd;     // 0x0161987c
// ---- items of slice s006f9250 end

// ---- items of slice s006fa2c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern void* __stdcall StringRangeInit(unsigned n);   // 0x475ab0
extern "C" void* __cdecl memset(void*, int, unsigned);
extern char g_emptyStr[];     // 0x01667bac  empty-string sentinel buffer
extern char g_emptyStrCap[];  // 0x01667bad  (sentinel begin + 1)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);  // msvcr90 interlocked
extern "C" void  __cdecl deleteBlock(void*);      // 0xf47380 (operator delete thunk)
extern "C" void* __cdecl newBlock(unsigned n, const char* name, int flags, int dbg,
                                  const char* file, int line);  // 0xf473a0
extern "C" void  __cdecl FragDeclDestroyRange(void* first, void* last); // 0x6fab90
extern "C" int  __cdecl BuildSamplerString(int n, int decls, char* out); // 0x6fcb90
extern "C" void __cdecl SetTexture(int reg, uint32_t tex);               // 0x11f1280
extern "C" void* __cdecl RangeCopyCtor(void* dst, const void* first, void* out);  // 0x6fe2d0
extern "C" void  __cdecl RangeCopyBack(void* first, const void* last, void* dst); // 0x6fe310
extern "C" void* __cdecl DoAllocateImpl(void* self, unsigned n, const void* alloc); // 0x6fa770
extern "C" void* __cdecl Vec28CtorImpl(void* out, const void* first, const void* last,
                                       void* dst, const void* alloc); // 0x6fa8d0
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void* operator new[](unsigned int size, int flags, const void* p);
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
struct Vec28 {
  void* begin;
  void* end;
  void* cap;
  Vec28* init(size_t n, const void* alloc);
  Vec28(const void* other);              // 0x006fad40
  void CopyTail(const void*, const void*);   // 0x006fae30
  void InsertGrow(const void*, const void*);  // 0x006faea0
};
struct IStream_s006f_a2c0;
namespace EA {
namespace IO {
bool WriteUint32(IStream_s006f_a2c0* s, const uint32_t* v, uint32_t count, int endian);  // 0x93aa70
}
}
namespace EA {
namespace IO {
bool WriteUint16(IStream_s006f_a2c0* s, const uint16_t* v, uint32_t count, int endian);  // 0x93a9d0
}
}
namespace EA {
namespace IO {
bool WriteBool8(IStream_s006f_a2c0* s, const bool* v, uint32_t count);                   // 0x93a9a0
}
}
namespace EA {
namespace IO {
bool WriteCString(IStream_s006f_a2c0* s, const char* p, int count, int endian);          // 0x93adb0
}
}
inline bool WriteU32(IStream_s006f_a2c0* s, uint32_t v) { return EA::IO::WriteUint32(s, &v, 1, 0); }
inline bool WriteU16(IStream_s006f_a2c0* s, uint16_t v) { return EA::IO::WriteUint16(s, &v, 1, 0); }
inline bool WriteB8(IStream_s006f_a2c0* s, uint8_t v) { return EA::IO::WriteBool8(s, (const bool*)&v, 1); }
inline bool WriteStr(IStream_s006f_a2c0* s, const char* p, int n) { return EA::IO::WriteCString(s, p, n, 0); }
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
  void Serialize(IStream_s006f_a2c0* s);    // 0x006fa480
};
// ---- items of slice s006fa2c0 end

// ---- items of slice s006fb5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_emptyStr[2];   // 0x01667bac: shared empty-string storage
extern int g_psMax;              // 0x015345b0
extern bool g_psFlag;            // 0x015345ac
extern uint32_t g_tick;          // 0x016f8cf8
extern "C" void opAssign2c0(void* self, void* src);                  // 0x006fa2c0
extern "C" bool LoadAndSelectPS(void* self, const char* name);       // 0x006fb860
void operator delete[](void* p) throw();   // 0x00f47380

struct FragDecl_s006f_b5c0 {
  BasicString mDecl;
  uint16_t mDataID, mSourceID, mNumConst, mOffset;
  uint32_t mFlags;
  FragDecl_s006f_b5c0() { mDecl.mpBegin = g_emptyStr; mDecl.mpEnd = g_emptyStr; mDecl.mpCap = g_emptyStr + 1; }
  FragDecl_s006f_b5c0(const FragDecl_s006f_b5c0&);                       // 0x006fa850
  ~FragDecl_s006f_b5c0() {
    if (mDecl.mpCap - mDecl.mpBegin > 1 && mDecl.mpBegin) operator delete[](mDecl.mpBegin);
  }
  FragDecl_s006f_b5c0& operator=(const FragDecl_s006f_b5c0&);
};
FragDecl_s006f_b5c0* __cdecl do_fill28(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last, const FragDecl_s006f_b5c0& v);      // 0x006fabd0
FragDecl_s006f_b5c0* __cdecl do_copy28(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last, FragDecl_s006f_b5c0* result);       // 0x006fac30
FragDecl_s006f_b5c0* __cdecl do_copy_backward28(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last, FragDecl_s006f_b5c0* res); // 0x006faca0
FragDecl_s006f_b5c0** __cdecl UninitCopyOut(FragDecl_s006f_b5c0** out, FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last,
                                 FragDecl_s006f_b5c0* dest, const void* tag);                     // 0x006fa8d0
FragDecl_s006f_b5c0* __cdecl UninitCopy(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last, FragDecl_s006f_b5c0* dest);         // 0x006fa950
FragDecl_s006f_b5c0* __cdecl DestroyN(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last, FragDecl_s006f_b5c0* dest);           // 0x006fa9e0
FragDecl_s006f_b5c0* __cdecl UninitFillN(FragDecl_s006f_b5c0* dest, unsigned n, const FragDecl_s006f_b5c0& v, FragDecl_s006f_b5c0* tag); // 0x006faa60
static inline void FreeBlock(void* p) {
  if (p && ((int*)p)[-1] != 0) operator delete[](p);
}
template<class T> static inline void swapPtr(T& a, T& b) { T t = a; a = b; b = t; }
struct Vec28_s006f_b5c0 {
  FragDecl_s006f_b5c0* mpBegin;
  FragDecl_s006f_b5c0* mpEnd;
  FragDecl_s006f_b5c0* mpCap;
  Vec28_s006f_b5c0() {}
  Vec28_s006f_b5c0(const Vec28_s006f_b5c0&);                                       // 0x006fad40
  ~Vec28_s006f_b5c0() { DoDestroy(mpBegin, mpEnd); FreeBlock(mpBegin); }
  unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
  unsigned capacity() const { return (unsigned)(mpCap - mpBegin); }

  FragDecl_s006f_b5c0* DoAllocateAndCopy(unsigned n, FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last);  // 0x006fadd0
  void DoDestroy(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last) throw();                         // 0x006fab90
  FragDecl_s006f_b5c0* erase(FragDecl_s006f_b5c0* first, FragDecl_s006f_b5c0* last);                          // 0x006fbc00

  // operator= at 0x006fb9e0; the body is named Assign so the equivalence checker can find it.
  __declspec(noinline) Vec28_s006f_b5c0& Assign(const Vec28_s006f_b5c0& x);      // 0x006fb9e0
  __forceinline Vec28_s006f_b5c0& operator=(const Vec28_s006f_b5c0& x) { return Assign(x); }
  void swap(Vec28_s006f_b5c0& o);                                     // 0x006fbb30
  void DoInsertValues(FragDecl_s006f_b5c0* pos, unsigned n, const FragDecl_s006f_b5c0& v);  // 0x006fbc60
  void resize(unsigned n);                                 // 0x006fc480
};
struct VecTemp : Vec28_s006f_b5c0 {
  int mPad0, mPad1;
  VecTemp(const Vec28_s006f_b5c0& v) : Vec28_s006f_b5c0(v) {}
};
struct ImgRef {
  void* p;
  void Assign(void* v);
};
struct PixelFrag_s006f_b5c0 {
  uint32_t f0;          // +0x00
  BasicString s4;       // +0x04
  BasicString s14;      // +0x14
  Vec28_s006f_b5c0 v24;            // +0x24
  uint32_t f30, f34;
  uint32_t f38, f3c;
  uint8_t b40, b41;
  uint8_t pad42[2];
  ImgRef r44;           // +0x44
  uint32_t f48, f4c, f50, f54, f58, f5c, f60;
  PixelFrag_s006f_b5c0& operator=(const PixelFrag_s006f_b5c0& o);  // 0x006fbed0
};
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
  FragDecl_s006f_b5c0* mpFrag[32];   // +0x2c
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
namespace IO {
 struct IStream; 
}
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
    void operator delete[](void*); // 0x00f47380
// ---- items of slice s006fb5c0 end

// ---- items of slice s006fd520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_shader;            // 0x16f6568
extern unsigned int g_softStateUpdated;  // 0x16f9110
extern unsigned int g_softStateDelta;    // 0x16f8af8
extern unsigned int g_rasterDelta;       // 0x16f8b00
extern unsigned char g_uvMapping[];      // 0x16f85b4
extern unsigned char g_texTable_16f6ddc[]; // 0x16f6ddc (pointer stored as bytes)
void  __cdecl FUN_006fefe0();
void  __cdecl FUN_006fb960();
void  __cdecl FUN_006fefa0();
void  __cdecl FUN_006fb920();
bool  __cdecl FUN_006fef70(void* shader);
bool  __cdecl FUN_006fb8f0(void* shader);
void  __cdecl FUN_011f1280(int index, void* texture);
void  __cdecl FUN_011f1210();
void  __cdecl FUN_011f7850();
void  __cdecl FUN_011f6920();
void  __cdecl FUN_006fa1b0(unsigned state, bool flag);
struct TexEntry {
    int           index;   // +0x00
    void**        texture; // +0x04
    unsigned char flags;   // +0x08
    unsigned char s0;      // +0x09
    unsigned char s1;      // +0x0a
    unsigned char s2;      // +0x0b
    unsigned char s3;      // +0x0c
    char          pad0d[3];
};
struct TexTable {
    int      count;   // +0x00
    TexEntry entries[1];
};
struct ShaderBlob {
    char name[0x130];
};
// ---- items of slice s006fd520 end

// ---- items of slice s006fc540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00f47380(void* p);                                  // 0x00f47380 operator delete
extern "C" void* FUN_00f473a0(unsigned int n, const char* name, int flags, unsigned debugFlags,
                              const char* file, int line);               // 0x00f473a0 eastl allocator
extern "C" void* FUN_0067dd60();                                         // 0x0067dd60 shader-data manager
extern "C" int   FUN_00777a10();                                         // 0x00777a10 shader count
extern "C" void  FUN_006fa730();                                         // 0x006fa730 vector allocate (ret 4)
extern "C" void  FUN_006fa950(void*, void*, void*);                      // 0x006fa950 element transfer
extern "C" void  FUN_006fa9e0(void*, void*, void*);                      // 0x006fa9e0 element transfer
extern "C" void  FUN_006fc480();                                         // 0x006fc480 vector resize (ret 4)
extern "C" void  FUN_006fad40();                                         // 0x006fad40 vector ctor (ret 4)
extern "C" void  FUN_006fbb30();                                         // 0x006fbb30 vector swap (ret 4)
extern "C" void  FUN_006fab90();                                         // 0x006fab90 element dtor (ret 8)
extern "C" int __cdecl FUN_0093a6c0(void* io, void* p, int n);           // 0x0093a6c0 read block
extern "C" int __cdecl FUN_0093a700(void* io, void* p, int n, int f);    // 0x0093a700 read uint16
extern "C" int __cdecl FUN_0093a780(void* io, void* p, int n, int f);    // 0x0093a780 read uint32
extern void*    _mShaderData[];      // 0x016f65a8
extern void*    _mVertexDescriptor;  // 0x016f65a0
extern void*    _mRasterShadow[];    // 0x016f5c58
extern uint8_t  _mUVMapping[];       // 0x016f85b4
extern uint8_t* DAT_016f6e84;        // 0x016f6e84
extern uint32_t* DAT_016f6db0;       // 0x016f6db0
extern uint32_t DAT_016f65b4;        // 0x016f65b4
extern uint32_t* DAT_016f6ee0;       // 0x016f6ee0
extern uint8_t  DAT_016198c0[];      // 0x016198c0  flat 0x100 x 0x64 pixel-fragment-info table
struct IO_s006f_c540;
extern "C" IO_s006f_c540* IOPut(IO_s006f_c540* io, const void* p, int n);          // operator<<
extern "C" IO_s006f_c540* IOGetB(IO_s006f_c540* io, const void* p, int n);         // byte read
extern "C" IO_s006f_c540* IOWriteU16(IO_s006f_c540* io, const uint16_t* p, int n, int f);
extern "C" IO_s006f_c540* IOWriteU32(IO_s006f_c540* io, const uint32_t* p, int n, int f);
extern "C" IO_s006f_c540* IOGet16(IO_s006f_c540* io, const void* p, int n, int f);
extern "C" IO_s006f_c540* IOGet32(IO_s006f_c540* io, const void* p, int n, int f);
struct IO_s006f_c540 {
  IO_s006f_c540* Put(uint8_t v)  { return IOPut(this, &v, 1); }
  IO_s006f_c540* Put(uint16_t v) { return IOWriteU16(this, &v, 1, 0); }
  IO_s006f_c540* Put(uint32_t v) { return IOWriteU32(this, &v, 1, 0); }
  IO_s006f_c540* Get(uint8_t& v)  { return IOGetB(this, &v, 1); }
  IO_s006f_c540* Get(uint16_t& v) { return IOGet16(this, &v, 1, 0); }
  IO_s006f_c540* Get(uint32_t& v) { return IOGet32(this, &v, 1, 0); }
};
struct FragRec {
  uint8_t  pad0;
  uint8_t  m1;    // +1
  uint16_t m2;    // +2
  uint16_t m4;    // +4
  uint16_t m6;    // +6
  uint32_t m8;    // +8
  uint32_t mc;    // +0xc
  uint32_t m10;   // +0x10
  uint32_t m14;   // +0x14
  uint8_t  m18;   // +0x18
  bool Write(IO_s006f_c540* io);                     // 0x006fceb0
  bool Read(IO_s006f_c540* io, uint32_t version);    // 0x006fcdc0
};
static void* AllocGraphics(unsigned int n) {
  return FUN_00f473a0(n, "Graphics", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
}
struct Vec25 {
  FragRec* mpBegin;                                        // +0x00
  FragRec* mpEnd;                                          // +0x04
  FragRec* mpCap;                                          // +0x08
  void set_capacity(unsigned n);                           // 0x006fc540
  void insert_moved(void* pos, unsigned n, const void* src); // 0x006fd330
};
struct cPixelFragmentInfo {  // 0x64 bytes
  uint32_t mFlags;           // +0x00
  uint32_t mStr1Begin;       // +0x04
  uint32_t mStr1End;         // +0x08
  uint32_t mStr1Cap;         // +0x0c
  uint32_t mField10;         // +0x10
  uint32_t mStr2Begin;       // +0x14
  uint32_t mStr2End;         // +0x18
  uint32_t mStr2Cap;         // +0x1c
  uint32_t mField20;         // +0x20
  Vec25    mRegions;         // +0x24
  uint32_t mField30;         // +0x30
  uint32_t mField34;         // +0x34
  uint32_t mField38;         // +0x38
  uint32_t mField3C;         // +0x3c
  uint8_t  mField40;         // +0x40
  uint8_t  mField41;         // +0x41
  uint32_t mField44;         // +0x44
  uint32_t mField48;         // +0x48
  uint32_t mField4C;         // +0x4c
  uint32_t mField50;         // +0x50
  uint32_t mField54;         // +0x54
  uint32_t mField58;         // +0x58
  uint32_t mField5C;         // +0x5c
  uint32_t mField60;         // +0x60
};
struct CFragDecl {           // 0x1c bytes (elements of the +0x24 region vector)
  char*    mpBegin;          // +0x00
  char*    mpEnd;            // +0x04
  char*    mpCap;            // +0x08
  uint32_t mField0C;         // +0x0c
  uint16_t mField10;         // +0x10
  uint16_t mField12;         // +0x12
  uint16_t mField14;         // +0x14
  uint16_t mField16;         // +0x16
  uint32_t mField18;         // +0x18
};
static void ReadIntoStringField(void* io, uint32_t& begin, uint32_t& end, uint32_t& cap, uint32_t n) {
  char* pb = (char*)(uintptr_t)begin;
  char* pe = (char*)(uintptr_t)end;
  char* pc = (char*)(uintptr_t)cap;
  uint32_t len = (uint32_t)(uintptr_t)(pe - pb);
  if (n < len) {
    char* ne = pb + n;
    if (ne != pe) {
      memmove(ne, pe, 1);
      pe = ne;
    }
  } else if (len < n) {
    uint32_t newCap = len + len / 2;
    if (newCap < n) newCap = n;
    if (newCap < 0x1f) newCap = 0x1f;
    char* nb = (char*)AllocGraphics(newCap + 1);
    memcpy(nb, pb, len);
    memset(nb + len, 0, newCap + 1 - len);
    pb = nb;
    pe = nb + n;
    pc = nb + newCap;
  }
  FUN_0093a6c0(io, pb, (int)n);
  begin = (uint32_t)(uintptr_t)pb;
  end = (uint32_t)(uintptr_t)pe;
  cap = (uint32_t)(uintptr_t)pc;
}
extern "C" void  FUN_0047d240();                                         // 0x0047d240 (thiscall, 1 arg)
extern "C" void  FUN_006fbed0();                                         // 0x006fbed0 PixelFragInfo operator=
extern "C" void  FUN_006fb040();                                         // 0x006fb040 PixelFragInfo dtor (ret)
// ---- items of slice s006fc540 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_006fd730(int stage, int type, int value);  // 0x006fd730 (stays in the slice: not this object's)

// @ 0x006f9f00
char* GenerateInputStruct(char* p, uint32_t flags, uint32_t numTex, uint32_t texMask)
{
  char* r = SP::TextCopy(p, "\nstruct cFragIn\n{\n");
  if (flags & 2) r = SP::TextCopy(r, "float4 position : POSITION0;\n");
  if (flags & 4) r = SP::TextCopy(r, "float3 normal : NORMAL0;\n");
  if (flags & 8) r = SP::TextCopy(r, "float3 tangent : TANGENT0;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "float3 binormal : BINORMAL0;\n");
  if (flags & 0x20) r = SP::TextCopy(r, "float4 color : COLOR0;\n");
  if (flags & 0x140) r = SP::TextCopy(r, "float4 color1 : COLOR1;\n");
  uint8_t i = 0;
  while (i < numTex) {
    if (texMask & (1 << (i + 6))) {
      r += sprintf(r, "float4 texcoord%d : TEXCOORD%d;\n", i, i);
    }
    ++i;
  }
  if (flags & 0x80) r = SP::TextCopy(r, "int4 indices :BLENDINDICES0;\n");
  return SP::TextCopy(r, "};\n\n");
}

// @ 0x006fa010
char* GenerateCurrentStruct(char* p, uint32_t flags)
{
  char* r = SP::TextCopy(p, "struct cFragCurrent\n{\n");
  if (flags & 2) r = SP::TextCopy(r, "float4 color;\n");
  if (flags & 4) r = SP::TextCopy(r, "float4 color1;\n");
  if (flags & 8) r = SP::TextCopy(r, "float4 color2;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "float4 color3;\n");
  if (flags & 0x20) r = SP::TextCopy(r, "float depth;\n");
  return SP::TextCopy(r, "};\n\n");
}

// @ 0x006fa0a0
char* GenerateOutputStruct(char* p, uint32_t flags)
{
  char* r = SP::TextCopy(p, "struct cFragOut\n{\n");
  if (flags & 2) r = SP::TextCopy(r, "float4 color :COLOR0;\n");
  if (flags & 4) r = SP::TextCopy(r, "float4 color1 :COLOR1;\n");
  if (flags & 8) r = SP::TextCopy(r, "float4 color2 :COLOR2;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "float4 color3 :COLOR3;\n");
  if (flags & 0x20) r = SP::TextCopy(r, "float depth :DEPTH;\n");
  return SP::TextCopy(r, "};\n\n");
}

// @ 0x006fa130
char* GenerateFillOutputStruct(char* p, uint32_t flags)
{
  char* r = SP::TextCopy(p, "\n");
  if (flags & 2) r = SP::TextCopy(r, "Out.color = Current.color;\n");
  if (flags & 4) r = SP::TextCopy(r, "Out.color1 = Current.color1;\n");
  if (flags & 8) r = SP::TextCopy(r, "Out.color2 = Current.color2;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "Out.color3 = Current.color3;\n");
  if (flags & 0x20) return SP::TextCopy(r, "Out.depth = Current.depth;\n");
  return r;
}

// @ 0x006fa1b0
void SetShaderDirty(unsigned int mask, char add)
{
  ShaderMgr* m = g_shaderMgr;
  if (add != 0)
    mask |= m->field12c;
  if ((m->field12c & mask) == 0)
    return;
  if (m->count <= 0)
    return;
  for (int i = 0; i < m->count; ++i) {
    ShaderRec* s = m->recs[i];
    unsigned int x = s->field18 & mask;
    if (x == 0)
      continue;
    if (x == 8 && add == 0 &&
        (g_shaderDataDirty[s->field12 >> 5] & (1u << (s->field12 & 0x1f))) == 0)
      continue;
    void* fn = g_shaderFns[(unsigned)s->field10 * 8];
    ((void(__cdecl*)(void*, unsigned short, int))fn)(m->objects[i], s->field14, 0);
  }
}

// @ 0x006fa250
bool ShaderNameMatches(const char** name)
{
  int count = (int)(g_shaderDefsEnd - g_shaderDefsBegin);
  for (int i = 0; i < count; ++i) {
    if (strcmp(g_shaderDefsBegin[i]->mName, *name) == 0)
      return true;
  }
  return false;
}

// @ 0x006fa2c0
void FragmentDeclAssign(int activeState, const char* in)
{
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

// @ 0x006fa480
void PixelFrag::Serialize(IStream_s006f_a2c0* s)
{
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

// @ 0x006fa730
extern "C" void* __stdcall allocN(size_t n)
{
  return n ? operator new(n * 0x1c, "Graphics", 0, 0, "", 0xd1) : 0;
}

// @ 0x006fa770
Vec28* Vec28::init(size_t n, const void* alloc)
{
  (void)alloc;
  void* p = n ? operator new(n * 0x1c, "Graphics", 0, 0, "", 0xd1) : 0;
  begin = p;
  end = p;
  cap = (char*)p + n * 0x1c;
  return this;
}

// @ 0x006fa850
FragDecl::FragDecl(const FragDecl& src)
{
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
void do_fill28(FragDecl* first, FragDecl* last, const FragDecl& value)
{
  for (; first != last; ++first) *first = value;
}

// @ 0x006fac30
FragDecl* do_copy28(FragDecl* first, FragDecl* last, FragDecl* result)
{
  for (; first != last; ++first, ++result) *result = *first;
  return result;
}

// @ 0x006faca0
FragDecl* do_copy_backward28(FragDecl* first, FragDecl* last, FragDecl* result)
{
  while (last != first) {
    --last;
    --result;
    *result = *last;
  }
  return result;
}

// @ 0x006fad40
Vec28::Vec28(const void* other)
{
  const char* o = (const char*)other;
  DoAllocateImpl(this, 0, o + 0x0c);
  Vec28CtorImpl(this, 0, 0, begin, o + 0x0c);
}

// @ 0x006fae30
void Vec28::CopyTail(const void* first, const void* last)
{
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
void Vec28::InsertGrow(const void* first, const void* last)
{
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

// @ 0x006fafe0
PixelFrag::PixelFrag()
: mf00(0) {
  mf0c = (uint32_t)g_emptyStrCap;
  _ReadWriteBarrier();
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
PixelFrag::~PixelFrag()
{
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

// @ 0x006fb0e0
void PixelFrag::PushBack()
{
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
void RegisterShaderTable()
{
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

// @ 0x006fb1b0
void AddPixelFragmentDeclarations(int a, char* out)
{ (void)a; (void)out; }

// @ 0x006fb310
void GeneratePixelShader(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x006fb5c0
extern "C" IPixelShader* __cdecl GetGeneratedPixelShader(void* a, const char* key)
{
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

// @ 0x006fb860
extern "C" __declspec(noinline) bool LoadAndSelectPS(void* self, const char* name)
{
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

// @ 0x006fb8f0
extern "C" void __cdecl DispatchCB(void* self)
{
  uint32_t local[8];
  opAssign2c0(self, local);
  LoadAndSelectPS(self, (const char*)local);
}

// @ 0x006fb920
extern "C" void UnregisterShaders()
{
  g_psTable.erase(g_psTable.mpBegin, g_psTable.mpEnd);
  g_psTable.reserve(g_psMax ? g_psMax : 0x200);
  g_curPS = 0;
}

// @ 0x006fb960
extern "C" void ClearFragments()
{
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

// @ 0x006fb9e0
Vec28_s006f_b5c0& Vec28_s006f_b5c0::Assign(const Vec28_s006f_b5c0& x)
{
  if (&x != this) {
    FragDecl_s006f_b5c0* xb = x.mpBegin;
    FragDecl_s006f_b5c0* xe = x.mpEnd;
    unsigned n = (unsigned)(xe - xb);
    FragDecl_s006f_b5c0* mb = mpBegin;
    if (n > (unsigned)(mpCap - mb)) {
      FragDecl_s006f_b5c0* pNew = DoAllocateAndCopy(n, xb, xe);
      DoDestroy(mpBegin, mpEnd);
      FreeBlock(mpBegin);
      mpBegin = pNew;
      mpCap = pNew + n;
    } else if (n > (unsigned)(mpEnd - mb)) {
      do_copy28(xb, xb + (mpEnd - mb), mb);
      FragDecl_s006f_b5c0* out;
      UninitCopyOut(&out, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
    } else {
      FragDecl_s006f_b5c0* p = do_copy28(xb, xe, mb);
      DoDestroy(p, mpEnd);
    }
    mpEnd = mpBegin + n;
  }
  return *this;
}

// @ 0x006fbb30
void Vec28_s006f_b5c0::swap(Vec28_s006f_b5c0& o)
{
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
void Vec28_s006f_b5c0::DoInsertValues(FragDecl_s006f_b5c0* pos, unsigned n, const FragDecl_s006f_b5c0& value)
{
  if ((unsigned)(mpCap - mpEnd) >= n) {
    if (n > 0) {
      const FragDecl_s006f_b5c0 temp(value);
      unsigned nExtra = (unsigned)(mpEnd - pos);
      FragDecl_s006f_b5c0* oldEnd = mpEnd;
      if (n < nExtra) {
        FragDecl_s006f_b5c0* out;
        UninitCopyOut(&out, oldEnd - n, oldEnd, oldEnd, pos);
        mpEnd += n;
        do_copy_backward28(pos, oldEnd - n, oldEnd);
        do_fill28(pos, pos + n, temp);
      } else {
        UninitFillN(oldEnd, n - nExtra, temp, oldEnd);
        mpEnd += n - nExtra;
        FragDecl_s006f_b5c0* out;
        UninitCopyOut(&out, pos, oldEnd, mpEnd, oldEnd);
        mpEnd += nExtra;
        do_fill28(pos, oldEnd, temp);
      }
    }
  } else {
    unsigned nPrev = size();
    unsigned nGrow = nPrev ? nPrev * 2 : 1;
    if (nGrow < nPrev + n) nGrow = nPrev + n;
    FragDecl_s006f_b5c0* pNew = nGrow ? (FragDecl_s006f_b5c0*)operator new(nGrow * sizeof(FragDecl_s006f_b5c0), "Graphics", 0, 0, "", 0xd1) : 0;
    FragDecl_s006f_b5c0* pNewEnd = UninitCopy(mpBegin, pos, pNew);
    DestroyN(mpBegin, pos, pNew);
    UninitFillN(pNewEnd, n, value, pNewEnd);
    pNewEnd += n;
    FragDecl_s006f_b5c0* oldEnd = mpEnd;
    pNewEnd = UninitCopy(pos, oldEnd, pNewEnd);
    DestroyN(pos, oldEnd, pNewEnd);
    FreeBlock(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCap = pNew + nGrow;
  }
}

// @ 0x006fbed0
PixelFrag_s006f_b5c0& PixelFrag_s006f_b5c0::operator=(const PixelFrag_s006f_b5c0& o)
{
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

// @ 0x006fbf70
void WriteShaderCache(IO::IStream* s)
{
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

// @ 0x006fc1f0
void ReadShaderCache(IO::IStream* s)
{
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
    char* p = (char*)g_stackAlloc.Alloc((unsigned)e->mCount * sizeof(FragDecl_s006f_b5c0));
    for (int j = 0; j < e->mCount; j++) {
      ReadUInt16(s, p + 0x10, 1, 0);
      ReadUInt16(s, p + 0x12, 1, 0);
      ReadUInt16(s, p + 0x14, 1, 0);
      ReadUInt16(s, p + 0x16, 1, 0);
      ReadInt32(s, p + 0x18, 1, 0);
      e->mpFrag[j] = (FragDecl_s006f_b5c0*)p;
      p += sizeof(FragDecl_s006f_b5c0);
    }
    ReadInt32(s, e->mFlags0, e->mCount, 0);
    ReadInt32(s, &e->mFlags, 1, 0);
  }
}

// @ 0x006fc480
void Vec28_s006f_b5c0::resize(unsigned n)
{
  FragDecl_s006f_b5c0* b = mpBegin;
  FragDecl_s006f_b5c0* e = mpEnd;
  if (n > (unsigned)(e - b)) {
    const FragDecl_s006f_b5c0 def;
    DoInsertValues(e, n - (unsigned)(e - b), def);
  } else {
    erase(b + n, e);
  }
}

// @ 0x006fc540
void Vec25::set_capacity(unsigned n)
{
  uint32_t count = (uint32_t)(uintptr_t)((char*)mpEnd - (char*)mpBegin) / 0x1c;
  if (n != 0xffffffffu && count < n) {
    FragRec* fresh = (FragRec*)((void*(__thiscall*)(void*, unsigned))FUN_006fa730)(this, n);
    FragRec* oldBegin = mpBegin;
    FragRec* oldEnd = mpEnd;
    FUN_006fa950(oldBegin, oldEnd, fresh);
    FUN_006fa9e0(oldBegin, oldEnd, fresh);
    if (oldBegin != 0 && ((int*)((char*)oldBegin - 4))[0] != 0)
      FUN_00f47380(oldBegin);
    uint32_t moved = (uint32_t)(uintptr_t)((char*)oldEnd - (char*)oldBegin) / 0x1c;
    mpBegin = fresh;
    mpEnd = (FragRec*)((char*)fresh + moved * 0x1c);
    mpCap = (FragRec*)((char*)fresh + n * 0x1c);
    return;
  }
  if (n < count)
    ((void(__thiscall*)(void*, unsigned))FUN_006fc480)(this, n);

  Vec25 tmp;
  ((void(__thiscall*)(void*, void*))FUN_006fad40)(&tmp, this);
  ((void(__thiscall*)(void*, void*))FUN_006fbb30)(this, &tmp);
  ((void(__thiscall*)(void*, void*, void*))FUN_006fab90)(&tmp, tmp.mpEnd, tmp.mpBegin);
  if (tmp.mpBegin != 0 && ((int*)((char*)tmp.mpBegin - 4))[0] != 0)
    FUN_00f47380(tmp.mpBegin);
}

// @ 0x006fc6a0
namespace SP {
void ClearPSFragment(int index)
{
  cPixelFragmentInfo tmp;
  cPixelFragmentInfo* dst = (cPixelFragmentInfo*)(DAT_016198c0 + (unsigned)index * 0x64);
  tmp.mFlags = 0;
  tmp.mStr1Begin = 0x01667bac;
  tmp.mStr1End = 0x01667bac;
  tmp.mStr1Cap = 0x01667bad;
  tmp.mField10 = 0;
  tmp.mStr2Begin = 0x01667bac;
  tmp.mStr2End = 0x01667bac;
  tmp.mStr2Cap = 0x01667bad;
  tmp.mField20 = 0;
  tmp.mRegions.mpBegin = 0;
  tmp.mRegions.mpEnd = 0;
  tmp.mRegions.mpCap = 0;
  tmp.mField30 = 0;
  tmp.mField34 = 0;
  tmp.mField38 = 0;
  tmp.mField3C = 0;
  tmp.mField40 = 0;
  tmp.mField41 = 0;
  tmp.mField44 = 0;
  tmp.mField48 = 0;
  tmp.mField4C = 0;
  tmp.mField50 = 0;
  tmp.mField54 = 0;
  tmp.mField58 = 0;
  tmp.mField5C = 0;
  tmp.mField60 = 0;
  ((void(__thiscall*)(void*, const void*))FUN_006fbed0)(dst, &tmp);
  ((void(__thiscall*)(void*))FUN_006fb040)(&tmp);
  ((void(__thiscall*)(void*, int))FUN_0047d240)((char*)dst + 4, 0);
  ((void(__thiscall*)(void*, int))FUN_0047d240)((char*)dst + 0x14, 0);
  ((Vec25*)((char*)dst + 0x24))->set_capacity(0);
}
}  // namespace SP

// @ 0x006fc780
void ReadFragmentTable(void* io)
{
  void* mgr = FUN_0067dd60();
  cPixelFragmentInfo* rec = (cPixelFragmentInfo*)(DAT_016198c0);
  for (int i = 0; i < 0x100; ++i, ++rec) {
    FUN_0093a780(io, &rec->mField38, 1, 0);
    FUN_0093a780(io, &rec->mField3C, 1, 0);
    FUN_0093a6c0(io, &rec->mField40, 1);
    FUN_0093a6c0(io, &rec->mField41, 1);
    FUN_0093a780(io, &rec->mFlags, 1, 0);

    uint32_t n1 = 0;
    if (FUN_0093a780(io, &n1, 1, 0) != 0)
      ReadIntoStringField(io, rec->mStr1Begin, rec->mStr1End, rec->mStr1Cap, n1);

    uint32_t n2 = 0;
    if (FUN_0093a780(io, &n2, 1, 0) != 0)
      ReadIntoStringField(io, rec->mStr2Begin, rec->mStr2End, rec->mStr2Cap, n2);

    uint32_t cnt = 0;
    FUN_0093a780(io, &cnt, 1, 0);
    ((void(__thiscall*)(void*, unsigned))FUN_006fc480)(&rec->mRegions, cnt);
    if (cnt != 0) {
      CFragDecl* elem = (CFragDecl*)rec->mRegions.mpBegin;
      for (uint32_t k = 0; k < cnt; ++k, ++elem) {
        uint32_t ln = 0;
        if (FUN_0093a780(io, &ln, 1, 0) != 0)
          ReadIntoStringField(io, *(uint32_t*)&elem->mpBegin, *(uint32_t*)&elem->mpEnd,
                              *(uint32_t*)&elem->mpCap, ln);
        FUN_0093a700(io, &elem->mField10, 1, 0);
        FUN_0093a700(io, (char*)elem + 0x12, 1, 0);
        FUN_0093a700(io, (char*)elem + 0x14, 1, 0);
        FUN_0093a700(io, (char*)elem + 0x16, 1, 0);
        FUN_0093a780(io, &elem->mField18, 1, 0);
      }
    }

    int32_t slotId = 0;
    int32_t slotArg = 0;
    FUN_0093a780(io, &slotId, 1, 0);
    FUN_0093a780(io, &slotArg, 1, 0);
    if (slotId != -1) {
      uint32_t fresh = ((uint32_t(__thiscall*)(void*, int, int, int))
                        (*(void***)mgr)[0x20 / 4])(mgr, slotId, slotArg, 0);
      uint32_t old = rec->mField44;
      if (fresh != old) {
        if (fresh != 0)
          ++*(uint32_t*)(uintptr_t)(fresh + 8);
        rec->mField44 = fresh;
        if (old != 0) {
          int* rc = (int*)(uintptr_t)(old + 8);
          --*rc;
        }
      }
    }

    FUN_0093a780(io, &rec->mField48, 1, 0);
    FUN_0093a780(io, &rec->mField4C, 1, 0);
    FUN_0093a780(io, &rec->mField50, 1, 0);
    FUN_0093a780(io, &rec->mField54, 1, 0);
    FUN_0093a780(io, &rec->mField58, 1, 0);
    FUN_0093a780(io, &rec->mField5C, 1, 0);
    FUN_0093a780(io, &rec->mField60, 1, 0);

    if ((rec->mFlags & 2) != 0) {
      uint32_t hl = 0;
      FUN_0093a780(io, &hl, 1, 0);
      char* dst;
      uint32_t dstEnd;
      if (hl + 1 < 2) {
        dst = (char*)(uintptr_t)0x01667bac;
        dstEnd = 0x01667bad;
      } else {
        dst = (char*)AllocGraphics(hl + 1);
        dstEnd = (uint32_t)(uintptr_t)dst + hl + 1;
      }
      memset(dst, 0x20, hl);
      dst[hl] = 0;
      FUN_0093a6c0(io, dst, (int)hl);
      if ((int)(dstEnd - (uint32_t)(uintptr_t)dst) > 1 && dst != 0)
        FUN_00f47380(dst);
    }
  }
}

// @ 0x006fcb90
int FilterFragmentRegions(int count, void* records, char* out)
{
  int written = 0;
  uint32_t mask = 0;
  uint8_t* base = (uint8_t*)records;
  while (count > 0) {
    --count;

    uint32_t f0c = *(uint32_t*)(base + 0x0c);
    uint32_t f10 = *(uint32_t*)(base + 0x10);
    uint32_t f08 = *(uint32_t*)(base + 0x08);
    if (((f0c & mask) != f0c) || ((f10 & mask) != 0) ||
        (f08 != (*(uint32_t*)((char*)_mVertexDescriptor + 0x10) & f08))) {
      base += 0x1c;
      continue;
    }

    int8_t c = *(int8_t*)(base + 0x18);
    bool reach;
    if (c < 0)
      reach = true;
    else if (DAT_016f6e84 == 0)
      reach = (c == 0);
    else
      reach = (*DAT_016f6e84 <= (uint8_t)c);
    if (!reach) {
      base += 0x1c;
      continue;
    }

    uint16_t u0 = *(uint16_t*)(base + 2);
    uint16_t u1 = *(uint16_t*)(base + 4);
    uint16_t u2 = *(uint16_t*)(base + 6);
    uint8_t  op = *(uint8_t*)(base + 1);

    bool matched = false;
    char add = 0;
    switch (op) {
    case 0:
      matched = true;
      break;
    case 1:
      matched = (_mShaderData[u0] != 0);
      break;
    case 2:
      matched = (DAT_016f6db0 != 0 && *DAT_016f6db0 == (uint32_t)u0);
      break;
    case 4:
      if (_mShaderData[u0] != 0) {
        matched = true;
        add = *(char*)_mShaderData[u0];
      }
      break;
    case 5:
      matched = (_mShaderData[u0] != 0 && _mShaderData[u1] != 0);
      break;
    case 6:
      matched = (_mShaderData[u0] != 0 && _mShaderData[u1] != 0 && _mShaderData[u2] != 0);
      break;
    case 7:
      matched = (_mShaderData[u0] != 0 && (uint16_t)*(uint8_t*)_mShaderData[u0] == u1);
      break;
    case 9:
      if (_mShaderData[u0] != 0 && _mShaderData[u1] != 0) {
        add = *(char*)_mShaderData[u0];
        matched = true;
      }
      break;
    case 10:
      matched = (_mRasterShadow[u0] != 0 && _mUVMapping[u0] != 0);
      break;
    case 0xb: {
      if (DAT_016f65b4 != 0) {
        int sc = FUN_00777a10();
        if (sc > 0) {
          matched = true;
          add = (char)(sc - 1);
        }
      }
      break;
    }
    case 0xc:
      matched = ((u0 & *(uint16_t*)DAT_016f6ee0) == u1);
      break;
    default:
      break;
    }

    if (matched) {
      mask |= *(uint32_t*)(base + 0x14);
      uint8_t b0 = *base;
      if (b0 != 0) {
        out[written] = (char)(b0 + add);
        ++written;
      }
    }
    base += 0x1c;
  }
  return written;
}

// @ 0x006fd7b0
void __cdecl FUN_006fd7b0()
{
    FUN_006fefe0();
    FUN_006fb960();
    FUN_006fefa0();
    FUN_006fb920();
}

// @ 0x006fd7d0
int __cdecl FUN_006fd7d0()
{
    TexTable* tbl = (TexTable*)g_texTable_16f6ddc;
    if (tbl != 0) {
        bool changed = false;
        int n = tbl->count;
        if (n > 0) {
            TexEntry* e = &tbl->entries[0];
            for (int i = 0; i < n; i++, e++) {
                if (e->texture == 0) {
                    FUN_011f1280(e->index, 0);
                } else {
                    FUN_011f1280(e->index, *e->texture);
                }
                g_rasterDelta |= ((unsigned)1 << (e->index & 0x1f));
                if (e->flags != 0) {
                    if (e->flags & 1) {
                        FUN_006fd730(e->index, 1, e->s0);
                        FUN_006fd730(e->index, 2, e->s0);
                        FUN_006fd730(e->index, 3, e->s0);
                    }
                    if (e->flags & 2) {
                        FUN_006fd730(e->index, 6, e->s1);
                        FUN_006fd730(e->index, 5, e->s1);
                    }
                    if (e->flags & 4) {
                        FUN_006fd730(e->index, 7, e->s2);
                    }
                    if ((e->flags & 8) && g_uvMapping[e->index] != e->s3) {
                        g_uvMapping[e->index] = e->s3;
                        changed = true;
                    }
                }
            }
            if (changed) {
                g_softStateUpdated |= 0x8000;
                g_softStateDelta |= 0x8000;
                FUN_011f1210();
            }
        }
    }
    unsigned int state = g_softStateUpdated;
    void* shader = g_shader;
    bool b0 = false;
    bool b1 = false;
    if ((state & 0x113fcc) != 0) {
        b0 = FUN_006fef70(shader);
        state = g_softStateUpdated;
    }
    if ((state & 0x51800c) != 0) {
        b1 = FUN_006fb8f0(shader);
        state = g_softStateUpdated;
    }
    if (state != 0) {
        FUN_006fa1b0(state, b0);
        state = g_softStateUpdated;
        if (state != 0) {
            FUN_006fa1b0(state, b1);
        }
    }
    unsigned int* d = g_shaderDataDirty;
    for (int k = 0x40; k != 0; k--) {
        *d++ = 0;
    }
    FUN_011f7850();
    FUN_011f6920();
    return 1;
}

// @ 0x006fdab0
int __cdecl BinaryFindPixelShader(const char* key, const ShaderBlob* base, unsigned count)
{
    int first = 0;
    if (count > 0) {
        unsigned n = count;
        int last = (int)count - 1;
        do {
            if (n <= 1) {
                int c = strcmp(key, base[first].name);
                if (c == 0)
                    return first;
                return (c < 0) ? (-1 - first) : (-2 - first);
            }
            int mid = ((int)(n & 1) - 1) + (int)(n >> 1) + first;
            int c = strcmp(key, base[mid].name);
            if (c == 0)
                return mid;
            if (c < 0)
                last = mid - 1;
            else
                first = mid + 1;
            n = (unsigned)(last - first) + 1;
        } while (n != 0);
    }
    return -1 - first;
}
