// SP::cFilterChain fragment/pixel-shader definition module (part 2).
// Contains EASTL 0x78-byte element assignment/copy/erase helpers, the shader-struct text
// generators, the filter-chain event handler, and larger vector/descriptor members.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

namespace SP { char* TextCopy(char* dst, const char* src); }
extern "C" __declspec(dllimport) int __cdecl sprintf(char* dst, const char* fmt, ...);
extern "C" void* SP_MessageServer();

// ==========================================================================================
// EASTL element model: the 0x78-byte descriptor is six 0x14-byte sub-objects, each with its
// own out-of-line operator= (and destructor).  006f9910 is the compiler-generated
// Elem78::operator=, 006f9970/006f99e0 are eastl::copy/copy_backward, 006f9a50 is erase.
struct Elem14 { char pad[0x14]; Elem14& operator=(const Elem14&); ~Elem14(); };
struct Elem78 {
  Elem14 m0, m1, m2, m3, m4, m5;
  Elem78& operator=(const Elem78&);
};

// @ 0x006f9910
Elem78& Elem78::operator=(const Elem78& o) {
  m0 = o.m0;
  m1 = o.m1;
  m2 = o.m2;
  m3 = o.m3;
  m4 = o.m4;
  m5 = o.m5;
  return *this;
}

// @ 0x006f9970
extern "C" Elem78* __cdecl copy79(Elem78* first, Elem78* last, Elem78* result) {
  for (; first != last; ++first, ++result) *result = *first;
  return result;
}

// @ 0x006f99e0
extern "C" Elem78* __cdecl copy_backward79(Elem78* first, Elem78* last, Elem78* result) {
  while (last != first) {
    --last;
    --result;
    *result = *last;
  }
  return result;
}

struct Vec78 {
  Elem78* begin;
  Elem78* end;
  Elem78* cap;
  Elem78* erase(Elem78* first, Elem78* last);  // 0x006f9a50
};

// @ 0x006f9a50
Elem78* Vec78::erase(Elem78* first, Elem78* last) {
  Elem78* newEnd = copy79(last, this->end, first);
  Elem78* e = this->end;
  while (newEnd < e) {
    newEnd->~Elem78();
    newEnd = (Elem78*)((char*)newEnd + 0x78);
  }
  this->end -= last - first;
  return first;
}

// ==========================================================================================
// Shader-struct text generators.
namespace {

// @ 0x006f9f00
char* GenerateInputStruct(char* p, uint32_t flags, uint32_t numTex, uint32_t texMask) {
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
char* GenerateCurrentStruct(char* p, uint32_t flags) {
  char* r = SP::TextCopy(p, "struct cFragCurrent\n{\n");
  if (flags & 2) r = SP::TextCopy(r, "float4 color;\n");
  if (flags & 4) r = SP::TextCopy(r, "float4 color1;\n");
  if (flags & 8) r = SP::TextCopy(r, "float4 color2;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "float4 color3;\n");
  if (flags & 0x20) r = SP::TextCopy(r, "float depth;\n");
  return SP::TextCopy(r, "};\n\n");
}

// @ 0x006fa0a0
char* GenerateOutputStruct(char* p, uint32_t flags) {
  char* r = SP::TextCopy(p, "struct cFragOut\n{\n");
  if (flags & 2) r = SP::TextCopy(r, "float4 color :COLOR0;\n");
  if (flags & 4) r = SP::TextCopy(r, "float4 color1 :COLOR1;\n");
  if (flags & 8) r = SP::TextCopy(r, "float4 color2 :COLOR2;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "float4 color3 :COLOR3;\n");
  if (flags & 0x20) r = SP::TextCopy(r, "float depth :DEPTH;\n");
  return SP::TextCopy(r, "};\n\n");
}

// @ 0x006fa130
char* GenerateFillOutputStruct(char* p, uint32_t flags) {
  char* r = SP::TextCopy(p, "\n");
  if (flags & 2) r = SP::TextCopy(r, "Out.color = Current.color;\n");
  if (flags & 4) r = SP::TextCopy(r, "Out.color1 = Current.color1;\n");
  if (flags & 8) r = SP::TextCopy(r, "Out.color2 = Current.color2;\n");
  if (flags & 0x10) r = SP::TextCopy(r, "Out.color3 = Current.color3;\n");
  if (flags & 0x20) return SP::TextCopy(r, "Out.depth = Current.depth;\n");
  return r;
}

}  // namespace

// ==========================================================================================
// Filter-chain event handler.
struct EvChain {
  char pad0[0x120];
  void* m120;         // +0x120
  void* m124;         // +0x124
  char pad128[0xc];
  uint8_t m134;       // +0x134
  char pad135[0xEF];
  int m224;           // +0x224
  void SubSF(int, int);                       // 0x006f9250
  void Notify(int a0, int a1, int a2, int a3);  // 0x006f94b0
};

// @ 0x006f94b0
void EvChain::Notify(int a0, int a1, int a2, int a3) {
  m224 = a3;
  if (a1 == 0x16 && m120 != m124) {
    SubSF(a0, a2);
    if (m134) {
      m134 = 0;
      void* srv = SP_MessageServer();
      ((void(__thiscall*)(void*, int, int, int))(*(void***)srv)[5])(srv, 0x6694879, 0, 0);
    }
  }
  m224 = 0;
}

// ==========================================================================================
// Larger members.  Bodies below are behaviourally approximate (marked partial in
// partial.txt); they exist so the slice source compiles and documents the call shape.
struct CFilterChain {
  char pad0[0x120];
  void* m120;
  void* m124;
  char pad128[0x10c];
  void* m234;
  int m224;

  bool AddFilterChain(int a, int b);            // 0x006f9250
  void AssignDescA(void* src);                  // 0x006f9520
  void AssignDescB(void* src);                  // 0x006f95e0
  void AssignVec28(void* src);                  // 0x006f9730
  void Notify2(int a, int b);                   // 0x006f9ac0
  void Shutdown();                              // 0x006f9cf0
  void Notify3(int a, int b, int c);            // 0x006f9e20
};

// @ 0x006f9250
bool CFilterChain::AddFilterChain(int a, int b) {
  (void)a; (void)b;
  return m120 != m124;
}

// @ 0x006f9520
void CFilterChain::AssignDescA(void* src) {
  (void)src;
}

// @ 0x006f95e0
void CFilterChain::AssignDescB(void* src) {
  (void)src;
}

// @ 0x006f9730
void CFilterChain::AssignVec28(void* src) {
  (void)src;
}

// @ 0x006f9ac0
void CFilterChain::Notify2(int a, int b) {
  (void)a; (void)b;
  m234 = 0;
}

// @ 0x006f9cf0
void CFilterChain::Shutdown() {
}

// @ 0x006f9e20
void CFilterChain::Notify3(int a, int b, int c) {
  (void)a; (void)b; (void)c;
}

// ==========================================================================================
// @ 0x006fa1b0
void SetShaderDirty(uint32_t mask, char add) {
  if (add == 0) {
    if ((mask & 0u) == 0) return;
  } else {
    mask = mask | 0u;
  }
}

// @ 0x006fa250
bool ShaderNameMatches(const void* name) {
  (void)name;
  return false;
}
