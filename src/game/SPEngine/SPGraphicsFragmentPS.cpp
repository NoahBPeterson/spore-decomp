// src/game/SPEngine/SPGraphicsFragmentPS.cpp -- migrated from slice(s) s006fd520, s006fb5c0, s006fa2c0, s006f9250 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFragmentPS.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl sprintf(char* dst, const char* fmt, ...);

// ---- items of slice s006f9250 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
 char* TextCopy(char* dst, const char* src); 
}
extern "C" __declspec(dllimport) int __cdecl sprintf(char* dst, const char* fmt, ...);
// ---- items of slice s006f9250 end

// ---- items of slice s006fa2c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct Vec28 {
  void* begin;
  void* end;
  void* cap;
  Vec28* init(size_t n, const void* alloc);
  Vec28(const void* other);              // 0x006fad40
  void CopyTail(const void*, const void*);   // 0x006fae30
  void InsertGrow(const void*, const void*);  // 0x006faea0
};
struct PixelFrag {
  char pad[0x64];
  PixelFrag();                   // 0x006fafe0
  ~PixelFrag();                  // 0x006fb040
  void AssignA();                // 0x006fa2c0
  void AssignB();                // 0x006fa480
  void PushBack();               // 0x006fb0e0
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
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
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
struct ShaderBlob {
    char name[0x130];
};
// ---- items of slice s006fd520 end

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




// @ 0x006fa250
bool ShaderNameMatches(const void* name)
{
  (void)name;
  return false;
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
  (void)other;
  begin = 0; end = 0; cap = 0;
}



// @ 0x006fae30
void Vec28::CopyTail(const void* a, const void* b)
{ (void)a; (void)b; }



// @ 0x006faea0
void Vec28::InsertGrow(const void* a, const void* b)
{ (void)a; (void)b; }



// @ 0x006fafe0
PixelFrag::PixelFrag()
{ pad[0] = 0; }



// @ 0x006fb040
PixelFrag::~PixelFrag()
{}



// @ 0x006fb0e0
void PixelFrag::PushBack()
{}



// @ 0x006fb150
void RegisterShaderTable()
{}



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
