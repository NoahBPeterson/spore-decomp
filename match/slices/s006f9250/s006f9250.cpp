// SP::cFilterChain fragment/pixel-shader definition module (part 2).
// Contains EASTL 0x78-byte element assignment/copy/erase helpers, the shader-struct text
// generators, the filter-chain event handler, and larger vector/descriptor members.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <string.h>

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
// Larger members.  This region is dominated by compiler-generated EASTL container
// copy/assign helpers over the 0x78-byte filter descriptor (six nested vectors at
// +0x00/+0x14/+0x28/+0x3c/+0x50/+0x64) and over the chain's own filter list at +0x120.
//
// 0x6f8710 uninitialized_copy<FilterElem28> (CopyFilterRange, slice s006f8380)
// 0x6f9430 / 0x6f5170 / 0x6f9880 / 0x6f8100 / 0x6f8140 / 0x6f9c70 / 0x6f8190 / 0x6f51b0
//          EASTL vector<...> reallocate / destroy / offset / fill helpers
// 0x6f50f0 vector<12-byte>::reserve      0x799d00 vector<8-byte>::reserve
// 0x4aa350 vector<4-byte>::reserve       0x76ffd0 / 0x714bc0 element range copy
// 0x11e0744 memmove
extern "C" void  __cdecl EASTL_deallocate_(void* p);            // 0x00f47380 (allocator free)
void* EASTL_allocate_(unsigned n, const char* name, int flags, int dbg, const char* file, int line); // 0x00f473a0
extern "C" int   __cdecl ReportCleanup();                       // 0x0067dcc0

// --- filter element / descriptor (see slice s006f8380 for the full model) ------------------
struct FilterElem28 {                                  // 0x28 bytes
  FilterElem28& operator=(const FilterElem28&);
};
struct Vec28 {
  FilterElem28* begin;   // +0
  FilterElem28* end;     // +4
  FilterElem28* cap;     // +8
  Vec28& operator=(const Vec28&);                      // 0x006f9730
};
void __cdecl Vec28ForceEmit(Vec28* d, const Vec28* s) { *d = *s; }

// EASTL vector<FilterElem28> internals referenced by operator=.
extern "C" void* __cdecl CopyFilterRange(void** dst, const void* first, const void* last, void* result); // 0x6f8710
FilterElem28* __cdecl Vec28Realloc(Vec28* self, int count, const FilterElem28* first,
                                   const FilterElem28* last);   // 0x006f9430
void __cdecl DestroyFilterRange(FilterElem28* first, FilterElem28* last);         // 0x006f5170
FilterElem28* __cdecl AssignFilterRange(FilterElem28* dst, const FilterElem28* first,
                                        const FilterElem28* last);                // 0x006f8140

// @ 0x006f9730  (the classic EASTL vector<FilterElem28>::operator=; three paths)
Vec28& Vec28::operator=(const Vec28& src) {
  if (this == &src)
    return *this;
  int srcCount = (int)(src.end - src.begin) / 0x28;
  FilterElem28* curBegin = begin;
  FilterElem28* curEnd = end;

  if (srcCount > (int)(cap - begin) / 0x28) {
    // grow: build a fresh buffer, tear down the old storage, install it
    FilterElem28* buf = Vec28Realloc(this, srcCount, src.begin, src.end);
    DestroyFilterRange(curBegin, curEnd);
    if (curBegin != 0 && *((int*)curBegin - 1) != 0)
      EASTL_deallocate_(curBegin);
    begin = buf;
    end = (FilterElem28*)((char*)buf + srcCount * 0x28);
    cap = end;
    return *this;
  }

  int curCount = (int)(curEnd - curBegin) / 0x28;
  if (srcCount > curCount) {
    // copy over the live elements, then uninitialized_copy the remainder
    const FilterElem28* mid = (const FilterElem28*)((const char*)src.begin + curCount * 0x28);
    FilterElem28* dst = AssignFilterRange(curBegin, src.begin, mid);
    void* endSlot = curEnd;
    CopyFilterRange(&endSlot, mid, src.end, dst);
    end = (FilterElem28*)((char*)begin + srcCount * 0x28);
    return *this;
  }

  FilterElem28* newEnd = AssignFilterRange(begin, src.begin, src.end);
  DestroyFilterRange(newEnd, curEnd);
  end = (FilterElem28*)((char*)begin + srcCount * 0x28);
  return *this;
}
struct Vec8 {                                          // generic 8-byte-element vector
  void* begin; void* end; void* cap;
  void assign(const Vec8& src);                        // reserve + memmove
};
struct Vec12 {                                          // 12-byte-element vector
  void* begin; void* end; void* cap;
};
struct Vec4 {                                           // 4-byte-element vector
  void* begin; void* end; void* cap;
};

struct FilterDesc {                                     // the 0x78-byte descriptor
  Vec28  v00;   // +0x00  (vector<FilterElem28>)
  Vec8   v14;   // +0x14  (8-byte elements)
  Vec4   v28;   // +0x28  (4-byte elements)
  Vec12  v3c;   // +0x3c  (12-byte elements)
  Vec8   v50;   // +0x50  (8-byte elements)
  Vec8   v64;   // +0x64  (8-byte elements)

  void AssignDescA(const FilterDesc* src);             // 0x006f9520
  void AssignDescB(const FilterDesc* src);             // 0x006f95e0
};

// range-copy / vector helpers referenced by the assign helpers
extern "C" void* __cdecl CopyFilterRange(void** dst, const void* first, const void* last, void* result); // 0x6f8710
void* __cdecl VecReserve8(void* self, int n);          // 0x00799d00
void* __cdecl VecReserve4(void* self, int n);          // 0x004aa350
void* __cdecl VecReserve12(void* self, const void* src); // 0x006f50f0
void* __cdecl CopyElems8(void** outEnd, const void* first, const void* last, void* dst); // 0x0076ffd0
void* __cdecl CopyElems8f(void** outEnd, const void* first, const void* last, void* dst); // 0x00714bc0

// @ 0x006f9520  (vector<FilterElem28> range-assign: allocate + uninitialized_copy)
void FilterDesc::AssignDescA(const FilterDesc* src) {
  int n = (int)((src->v00.end - src->v00.begin) / 0x28);
  FilterElem28* newBuf = 0;
  if (n != 0) {
    newBuf = (FilterElem28*)EASTL_allocate_((unsigned)(n * 0x28), "Graphics", 0, 0,
                                            (const char*)0x013ebb38, 0xd1);
  }
  v00.begin = newBuf;
  v00.end = newBuf;
  v00.cap = (FilterElem28*)((char*)newBuf + n * 0x28);
  void* endSlot = v00.end;
  CopyFilterRange(&endSlot, src->v00.begin, src->v00.end, newBuf);
  v00.end = (FilterElem28*)endSlot;
}

// @ 0x006f95e0  (copy every nested vector of a descriptor)
void FilterDesc::AssignDescB(const FilterDesc* src) {
  AssignDescA(src);                                     // +0x00 vector<FilterElem28>

  {                                                     // +0x14 vector<8-byte>
    int n = (int)((char*)src->v14.end - (char*)src->v14.begin) >> 3;
    VecReserve8(&v14, n);
    void* endSlot = 0;
    CopyElems8(&endSlot, src->v14.begin, src->v14.end, v14.begin);
    v14.end = endSlot;
  }
  {                                                     // +0x28 vector<4-byte>
    int n = (int)((char*)src->v28.end - (char*)src->v28.begin) >> 2;
    VecReserve4(&v28, n);
    int bytes = (int)((char*)src->v28.end - (char*)src->v28.begin);
    memmove(v28.begin, src->v28.begin, bytes);
    v28.end = (char*)v28.begin + bytes;
  }
  {                                                     // +0x3c vector<12-byte>
    VecReserve12(&v3c, &src->v3c);
  }
  {                                                     // +0x50 vector<8-byte>
    int n = (int)((char*)src->v50.end - (char*)src->v50.begin) >> 3;
    VecReserve8(&v50, n);
    void* endSlot = 0;
    CopyElems8f(&endSlot, src->v50.begin, src->v50.end, v50.begin);
    v50.end = endSlot;
  }
  {                                                     // +0x64 vector<8-byte>
    int n = (int)((char*)src->v64.end - (char*)src->v64.begin) >> 3;
    VecReserve8(&v64, n);
    int bytes = (int)((char*)src->v64.end - (char*)src->v64.begin);
    memmove(v64.begin, src->v64.begin, bytes);
    v64.end = (char*)v64.begin + bytes;
  }
}

// ==========================================================================================
struct CFilterChain {
  char pad0[0x120];
  Vec78* m120;             // +0x120  vector<0x78-byte filter records> begin
  Vec78* m124;             // +0x124  end
  char pad128[0x8];
  void* m130;              // +0x130
  char pad134[4];
  void** m138;             // +0x138  texture-object table (2 entries)
  char pad13c[0x38];
  int m174;                // +0x174
  int m178;                // +0x178
  int m17c;                // +0x17c
  int m180;                // +0x180
  char pad184[0x74];
  uint8_t m1f8;            // +0x1f8
  char pad1f9[3];
  uint8_t* m1fc;           // +0x1fc  vector<bool> begin
  uint8_t* m200;           // +0x200  end
  uint8_t* m204;           // +0x204  cap
  char pad208[8];
  uint16_t* m210;          // +0x210  vector<u16> begin
  uint16_t* m214;          // +0x214  end
  uint16_t* m218;          // +0x218  cap
  int mIndex[17];          // +0x1b4  (overlaps the block above; per-filter state)
  int m224;                // +0x224

  bool AddFilterChain(int a, int b);            // 0x006f9250
  void Notify2(int a, int b);                   // 0x006f9ac0
  void Shutdown();                              // 0x006f9cf0
  void Notify3(int a, int* out, unsigned short c); // 0x006f9e20
  void ApplyFilters(FilterDesc* d, uint16_t count, int* p4, int p5); // 0x006f8380
  void SubSF(int a, int b);                     // 0x006f9c70
};

// @ 0x006f9250
bool CFilterChain::AddFilterChain(int a, int b) {
  m1f8 = 0;
  int count = (int)((char*)m124 - (char*)m120) / 0x78;
  int n = count - 1;
  bool flagA = false;       // [esp+0x13]
  bool flagB = false;       // bl
  int idxA = -1;            // ebp
  int idxB = -1;            // edi
  for (int i = n; i >= 0; --i) {
    if (m210[i] == 1 && m1fc[i] == 1) {
      flagA = true;
      idxA = i;
    } else if (m210[i] == 0 && m1fc[i] == 1) {
      flagB = true;
      idxB = i;
    }
  }
  char* base = (char*)m120;
  if (flagA && flagB) {
    FilterDesc* eA = (FilterDesc*)(base + idxB * 0x78);
    FilterDesc* eB = (FilterDesc*)(base + idxA * 0x78);
    int cB = (int)((char*)eB->v00.end - (char*)eB->v00.begin) / 0x28;
    ((char*)eB->v00.begin)[cB * 0x28 - 0x27] = 0x41;
    ApplyFilters(eA, (uint16_t)((int)((char*)eA->v00.end - (char*)eA->v00.begin) / 0x28), &b, 0);
    ApplyFilters(eB, (uint16_t)cB, &b, 1);
  } else if (flagA) {
    FilterDesc* eB = (FilterDesc*)(base + idxA * 0x78);
    int cB = (int)((char*)eB->v00.end - (char*)eB->v00.begin) / 0x28;
    ApplyFilters(eB, (uint16_t)cB, &a, 1);
  } else if (flagB) {
    FilterDesc* eA = (FilterDesc*)(base + idxB * 0x78);
    int cA = (int)((char*)eA->v00.end - (char*)eA->v00.begin) / 0x28;
    ((char*)eA->v00.begin)[cA * 0x28 - 0x27] = 1;
    ApplyFilters(eA, (uint16_t)cA, &b, 0);
  }
  return false;
}

// vector<FilterDesc>::insert(pos, elem) as inlined by the original.  Helpers:
//   0x6f9880 uninitialized_copy(srcFirst, srcLast, dst) -> dstEnd     (3 args)
//   0x6f8100 copy(srcFirst, srcLast, dst) -> dstEnd                   (3 args)
//   0x6f99e0 _copy_backward(srcFirst, srcLast, dstEnd)                (3 args)
//   0x6f9430 reallocate(self, count, first, last) -> 0
//   0xf473a0 allocator
struct Vec78Ins { Elem78* begin; Elem78* end; Elem78* cap; };

Elem78* __cdecl CopyRange78(Elem78* dst, const Elem78* first, const Elem78* last);   // 0x006f9880
Elem78* __cdecl AssignRange78(Elem78* dst, const Elem78* first, const Elem78* last); // 0x006f8100
Elem78* __cdecl CopyBackward78(Elem78* dstEnd, const Elem78* first, const Elem78* last); // 0x006f99e0
void* __cdecl Realloc78(Vec78Ins* self, int n, Elem78* first, Elem78* last);         // 0x006f9430
void  __cdecl Destroy78(Elem78* first, Elem78* last);                                // 0x006f5170

// 0x006f9910  Elem78::operator=(const Elem78&)  (in slice, defines the copy)

// @ 0x006f9ac0  (vector<Elem78>::insert of one 0x78-byte record into m120)
void CFilterChain::Notify2(int a, int b) {
  Vec78Ins* self = (Vec78Ins*)&m120;     // begin @+0x120, end @+0x124, cap @+0x128
  Elem78* where = (Elem78*)(void*)a;     // insertion position
  Elem78* src   = (Elem78*)(void*)b;     // element to copy
  if (self->end == self->cap) {
    // no spare capacity: reallocate
    int n = (int)((char*)self->end - (char*)self->begin) / 0x78;
    if (n == 0) {
      n = 1;
    } else {
      n += n;
    }
    Elem78* nb = (Elem78*)EASTL_allocate_((unsigned)(n * 0x78), (const char*)0x013ebb38,
                                          0, 0, (const char*)0x013eb8a4, 0xd1);
    Elem78* pos = CopyRange78(nb, self->begin, where);      // copy [begin, where)
    AssignRange78(pos, where, self->end);                    // copy [where, end)
    // destroy the old records and free the old buffer
    Destroy78(self->begin, self->end);
    if (self->begin != 0 && *((int*)self->begin - 1) != 0)
      EASTL_deallocate_(self->begin);
    self->end = (Elem78*)((char*)nb + ((char*)self->end - (char*)self->begin));
    self->begin = nb;
    self->cap = (Elem78*)((char*)nb + n * 0x78);
  } else {
    // spare capacity: shift the tail by one and copy the element in
    Elem78* newLast = (Elem78*)((char*)self->end + 0x78);
    CopyBackward78(newLast, where, self->end);
    AssignRange78(where, src, (const Elem78*)((const char*)src + 0x78));
    self->end = (Elem78*)((char*)self->end + 0x78);
  }
  m224 = 0;
}

// @ 0x006f9cf0  (release every GPU-side resource held by the chain)
void CFilterChain::Shutdown() {
  void* rs = (void*)ReportCleanup();
  void* ctx = (this != 0) ? (void*)((char*)this + 4) : 0;
  ((void(__thiscall*)(void*, void*, int, int))(*(void***)rs)[0x2c / 4])(rs, ctx, 0x44edd9c, -0x270f);
  for (int i = 0; i < 2; ++i) {
    void* obj = *(void**)((char*)m138 + i * 4);
    ((void(__thiscall*)(void*))0x006f8190)(obj);
    if (obj != 0) {
      ((void(__thiscall*)(void*))0x006f51b0)(obj);
      EASTL_deallocate_(obj);
    }
  }
  {  // clear the +0x120 vector
    void* end = m124;
    ((void(__cdecl*)(void*, void*))0x006f9a50)(m120, end);
  }
  void* p;
  p = (void*)m174; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
  p = (void*)m178; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
  p = (void*)m17c; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
  p = (void*)m180; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
}

// @ 0x006f9e20
void CFilterChain::Notify3(int a, int* out, unsigned short c) {
  ((void(__thiscall*)(void*, int))0x006f9c70)((char*)this + 0x120, a);   // append filter record
  // append a 'true' to the +0x1fc vector<bool>
  if (m200 < m204) {
    *m200++ = 1;
  } else {
    uint8_t tmp = 1;
    ((void(__cdecl*)(void*, void*))0x00426730)(m200, &tmp);
  }
  // append c to the +0x210 vector<u16>
  if (m214 < m218) {
    *m214++ = c;
  } else {
    ((void(__cdecl*)(void*, void*))0x006f5bc0)(m214, &c);
  }
  int cnt = (int)((char*)m124 - (char*)m120) / 0x78;
  *out = cnt + 0xc;
  int idx = (int)(short)c;
  *(int*)((char*)this + 0x1b4 + idx * 4) = cnt - 1;
  void* filter = *(void**)((char*)m138 + idx * 4);
  ((void(__thiscall*)(void*, int))0x006f87f0)(filter, a);
}

// ==========================================================================================
// Global shader-dirty propagation.  Walks the active shader table and marks each affected
// shader state; identical shape to FUN_006fe230 (0x006fe230) in slice s006fd520 but with
// `add` semantics for the dirty mask and a 0 argument to the per-shader callback.
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
extern unsigned int g_shaderDataDirty[];   // 0x016f89f8 (rw::graphics::ActiveState::m_shaderDataDirty)
extern void* g_shaderFns[];                // 0x016fa604

// @ 0x006fa1b0
void SetShaderDirty(unsigned int mask, char add) {
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

// ==========================================================================================
// Shader-name table lookup (global vector<ShaderDef*>).  Each entry's first field is the
// NUL-terminated shader name; the comparison is an inlined strcmp.
struct ShaderDef { char* mName; };

extern ShaderDef** g_shaderDefsBegin;   // 0x01619878
extern ShaderDef** g_shaderDefsEnd;     // 0x0161987c

// @ 0x006fa250
bool ShaderNameMatches(const char** name) {
  int count = (int)(g_shaderDefsEnd - g_shaderDefsBegin);
  for (int i = 0; i < count; ++i) {
    if (strcmp(g_shaderDefsBegin[i]->mName, *name) == 0)
      return true;
  }
  return false;
}
