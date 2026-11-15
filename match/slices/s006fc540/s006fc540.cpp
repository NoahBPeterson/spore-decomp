// SP fragment-shader module (part 5): cFragmentDecl binary Write/Read, vector set_capacity,
// ClearPSFragment, and cFragmentShader::Write.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <string.h>

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

// ==========================================================================================
// Binary (de)serialization of the 0x19-byte fragment-decl record.
// IO::Put/Get are inline forwarding overloads: they build a by-value temporary and pass its
// address to the underlying cdecl stream call, which is what the original compiler emitted.
struct IO;
extern "C" IO* IOPut(IO* io, const void* p, int n);          // operator<<
extern "C" IO* IOGetB(IO* io, const void* p, int n);         // byte read
extern "C" IO* IOWriteU16(IO* io, const uint16_t* p, int n, int f);
extern "C" IO* IOWriteU32(IO* io, const uint32_t* p, int n, int f);
extern "C" IO* IOGet16(IO* io, const void* p, int n, int f);
extern "C" IO* IOGet32(IO* io, const void* p, int n, int f);

struct IO {
  IO* Put(uint8_t v)  { return IOPut(this, &v, 1); }
  IO* Put(uint16_t v) { return IOWriteU16(this, &v, 1, 0); }
  IO* Put(uint32_t v) { return IOWriteU32(this, &v, 1, 0); }
  IO* Get(uint8_t& v)  { return IOGetB(this, &v, 1); }
  IO* Get(uint16_t& v) { return IOGet16(this, &v, 1, 0); }
  IO* Get(uint32_t& v) { return IOGet32(this, &v, 1, 0); }
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
  bool Write(IO* io);                     // 0x006fceb0
  bool Read(IO* io, uint32_t version);    // 0x006fcdc0
};

// @ 0x006fceb0
bool FragRec::Write(IO* io) {
  io->Put(m1);
  io->Put(m2);
  io->Put(m4);
  io->Put(m6);
  io->Put(m8);
  io->Put(mc);
  io->Put(m10);
  io->Put(m14);
  io->Put(m18);
  return true;
}

// @ 0x006fcdc0
bool FragRec::Read(IO* io, uint32_t version) {
  io->Get(m1);
  if (version <= 6) {
    uint8_t tmp;
    io->Get(tmp);
  }
  io->Get(m2);
  io->Get(m4);
  io->Get(m6);
  if (version <= 6) {
    uint16_t tmp;
    io->Get(tmp);
    io->Get(tmp);
    io->Get(tmp);
  }
  io->Get(m8);
  io->Get(mc);
  io->Get(m10);
  io->Get(m14);
  io->Get(m18);
  return true;
}

// ==========================================================================================
// Support declarations for the fragment-table / fragment-shader members below.
extern "C" void  FUN_00f47380(void* p);                                  // 0x00f47380 operator delete
extern "C" void* FUN_00f473a0(unsigned int n, const char* name, int flags, unsigned debugFlags,
                              const char* file, int line);               // 0x00f473a0 eastl allocator
extern "C" void __stdcall FUN_011e0b22(void* p, int count, int size, void (*dtor)(void*));
extern "C" void __stdcall FUN_011e0b85(void* p, int count, int size, void (*ctor)(void*),
                                       void (*dtor)(void*));
extern "C" void  FUN_007a41a0();                                         // 0x007a41a0 slot dtor
extern "C" void  FUN_006e5790();                                         // 0x006e5790 slot ctor
extern "C" void  FUN_011f4200();                                         // 0x011f4200 Shader::Release
extern "C" void* FUN_0067dd60();                                         // 0x0067dd60 shader-data manager
extern "C" int   FUN_00777a10();                                         // 0x00777a10 shader count
extern "C" int   FUN_00777760();                                         // 0x00777760 cShaderBase::Write
extern "C" void  FUN_0047d240();                                         // 0x0047d240 (thiscall, 1 arg)
extern "C" void  FUN_006fbed0();                                         // 0x006fbed0 PixelFragInfo operator=
extern "C" void  FUN_006fb040();                                         // 0x006fb040 PixelFragInfo dtor (ret)
extern "C" void  FUN_006fa730();                                         // 0x006fa730 vector allocate (ret 4)
extern "C" void  FUN_006fa950(void*, void*, void*);                      // 0x006fa950 element transfer
extern "C" void  FUN_006fa9e0(void*, void*, void*);                      // 0x006fa9e0 element transfer
extern "C" void  FUN_006fc480();                                         // 0x006fc480 vector resize (ret 4)
extern "C" void  FUN_006fad40();                                         // 0x006fad40 vector ctor (ret 4)
extern "C" void  FUN_006fbb30();                                         // 0x006fbb30 vector swap (ret 4)
extern "C" void  FUN_006fab90();                                         // 0x006fab90 element dtor (ret 8)
extern "C" void* FUN_00847ff0(void*, void*, void*);                      // 0x00847ff0 range move
extern "C" void  FUN_006fd220(void*, unsigned, const void*);             // 0x006fd220 construct range
extern "C" void  FUN_006fd170(void*, void*, void*, void*, void*);        // 0x006fd170
extern "C" void  FUN_006fd250(void*, void*, void*);                      // 0x006fd250
extern "C" void  FUN_006fd140(void*, void*, void*);                      // 0x006fd140
extern "C" int __cdecl FUN_0093a6c0(void* io, void* p, int n);           // 0x0093a6c0 read block
extern "C" int __cdecl FUN_0093a700(void* io, void* p, int n, int f);    // 0x0093a700 read uint16
extern "C" int __cdecl FUN_0093a780(void* io, void* p, int n, int f);    // 0x0093a780 read uint32
extern "C" int __cdecl FUN_0093a9a0(void* io, const void* p, int n);     // 0x0093a9a0 write block
extern "C" int __cdecl FUN_0093aa70(void* io, const void* p, int n, int f); // 0x0093aa70 write uint32

// Engine shader-state tables consumed by the region filter (0x6fcb90).
extern void*    _mShaderData[];      // 0x016f65a8
extern void*    _mVertexDescriptor;  // 0x016f65a0
extern void*    _mRasterShadow[];    // 0x016f5c58
extern uint8_t  _mUVMapping[];       // 0x016f85b4
extern uint8_t* DAT_016f6e84;        // 0x016f6e84
extern uint32_t* DAT_016f6db0;       // 0x016f6db0
extern uint32_t DAT_016f65b4;        // 0x016f65b4
extern uint32_t* DAT_016f6ee0;       // 0x016f6ee0
extern uint8_t  DAT_016198c0[];      // 0x016198c0  flat 0x100 x 0x64 pixel-fragment-info table
extern uint16_t DAT_01667bac;        // 0x01667bac  eastl::gEmptyString16

static void* AllocGraphics(unsigned int n) {
  return FUN_00f473a0(n, "Graphics", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
}

// ------------------------------------------------------------------------------------------
struct ShaderSlot {          // 0x14 bytes
  FragRec* mpBegin;          // +0x00
  FragRec* mpEnd;            // +0x04
  FragRec* mpCap;            // +0x08
  uint32_t mField0C;         // +0x0c
  uint32_t mField10;         // +0x10
};

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

struct cFragmentShader {
  uint8_t    mPad00[0x38];     // +0x00..+0x37
  uint32_t   mField38;         // +0x38
  uint32_t   mRefCount;        // +0x3c
  uint32_t   mField40;         // +0x40
  uint32_t   mField44;         // +0x44
  ShaderSlot mSlotsA[0x10];    // +0x48
  ShaderSlot mSlotsB[0x10];    // +0x188
  bool Write(IO* io);          // 0x006fcf90
  __declspec(noinline) void DestroyArrays();        // 0x006fd1b0
  void* ConstructArrays();     // 0x006fd280
  int  Release();              // 0x006fd300
};

// Resize an eastl string so that it can hold exactly n bytes, then stream n bytes into it.
// Mirrors the shrink-in-place / grow-with-realloc dance of the original reader.
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

// ------------------------------------------------------------------------------------------
// eastl::vector<SP::cFragmentDecl, sp_vector_allocator>::set_capacity(unsigned)
// @ 0x006fc540
void Vec25::set_capacity(unsigned n) {
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

// ------------------------------------------------------------------------------------------
// @ 0x006fc6a0
void ClearPSFragment(int index) {
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

// ------------------------------------------------------------------------------------------
// Streams the whole 0x100-entry pixel-fragment-info table in from the given IO stream.
// @ 0x006fc780
void ReadFragmentTable(void* io) {
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

// ------------------------------------------------------------------------------------------
// Filters "default-state" fragment records out of a flat 0x1c-strided array, appending the
// surviving opcodes (biased by the matched state value) into out. Returns the number written.
// @ 0x006fcb90
int FilterFragmentRegions(int count, void* records, char* out) {
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

// ------------------------------------------------------------------------------------------
// SP::cFragmentShader::Write(EA::IO&)
// @ 0x006fcf90
bool cFragmentShader::Write(IO* io) {
  if (((int(__thiscall*)(void*, void*))FUN_00777760)(this, io) == 0)
    return false;

  for (int i = 0; i < 0x10; ++i) {
    FragRec* aB = mSlotsA[i].mpBegin;
    FragRec* aE = mSlotsA[i].mpEnd;
    FragRec* bB = mSlotsB[i].mpBegin;
    FragRec* bE = mSlotsB[i].mpEnd;
    if (aB == aE && bB == bE)
      continue;

    char idx = (char)i;
    FUN_0093a9a0(io, &idx, 1);

    uint32_t n1 = (uint32_t)(uintptr_t)((char*)aE - (char*)aB) / 0x1c;
    FUN_0093aa70(io, &n1, 1, 0);
    for (uint32_t k = 0; k < n1; ++k) {
      aB[k].Write(io);
      char b = *(char*)&aB[k];
      FUN_0093a9a0(io, &b, 1);
    }

    uint32_t n2 = (uint32_t)(uintptr_t)((char*)bE - (char*)bB) / 0x1c;
    FUN_0093aa70(io, &n2, 1, 0);
    for (uint32_t k = 0; k < n2; ++k) {
      bB[k].Write(io);
      char b = *(char*)&bB[k];
      FUN_0093a9a0(io, &b, 1);
    }
  }

  char term = (char)0xff;
  FUN_0093a9a0(io, &term, 1);
  return true;
}

// ------------------------------------------------------------------------------------------
// @ 0x006fd1b0
void cFragmentShader::DestroyArrays() {
  FUN_011e0b22((char*)this + 0x188, 0x14, 0x10, (void(*)(void*))FUN_007a41a0);
  FUN_011e0b22((char*)this + 0x48, 0x14, 0x10, (void(*)(void*))FUN_007a41a0);
}

// @ 0x006fd280
void* cFragmentShader::ConstructArrays() {
  mField38 = 0;
  mRefCount = 0;
  mField40 = 0;
  mField44 = 0;
  FUN_011e0b85((char*)this + 0x48, 0x14, 0x10, (void(*)(void*))FUN_006e5790,
               (void(*)(void*))FUN_007a41a0);
  FUN_011e0b85((char*)this + 0x188, 0x14, 0x10, (void(*)(void*))FUN_006e5790,
               (void(*)(void*))FUN_007a41a0);
  return this;
}

// @ 0x006fd300
int cFragmentShader::Release() {
  int ref = (int)mRefCount - 1;
  ((void(__thiscall*)(void*))FUN_011f4200)(this);
  if (ref == 0) {
    DestroyArrays();
    FUN_00f47380(this);
  }
  return ref;
}

// ------------------------------------------------------------------------------------------
// Insert n moved-in elements (copied from src) at pos, growing the capacity if required.
// @ 0x006fd330
void Vec25::insert_moved(void* pos, unsigned n, const void* src) {
  uint32_t cap = (uint32_t)(uintptr_t)((char*)mpCap - (char*)mpBegin) / 0x1c;
  if (n > cap) {
    uint32_t size = (uint32_t)(uintptr_t)((char*)mpEnd - (char*)mpBegin) / 0x1c;
    uint32_t newCap = size * 2;
    if (size == 0)
      newCap = 1;
    uint32_t want = size + n;
    if (want < newCap)
      want = newCap;
    char* buf = want ? (char*)AllocGraphics(want * 0x1c) : 0;
    char* e1 = (char*)FUN_00847ff0(mpBegin, pos, buf);
    FUN_006fd220(e1, n, src);
    char* e2 = (char*)FUN_00847ff0(pos, mpEnd, e1 + n * 0x1c);
    if (mpBegin != 0 && ((int*)((char*)mpBegin - 4))[0] != 0)
      FUN_00f47380(mpBegin);
    mpBegin = (FragRec*)buf;
    mpEnd = (FragRec*)e2;
    mpCap = (FragRec*)(buf + want * 0x1c);
    return;
  }

  if (n == 0)
    return;

  uint32_t seven[7];
  {
    volatile uint32_t* d7 = seven;
    const volatile uint32_t* s7 = (const volatile uint32_t*)src;
    for (int i = 0; i < 7; ++i)
      d7[i] = s7[i];
  }

  char* p = (char*)pos;
  char* end = (char*)mpEnd;
  uint32_t after = (uint32_t)(uintptr_t)(end - p) / 0x1c;

  if (n < after) {
    uint32_t nb = n * 0x1c;
    char* mid = end - nb;
    FUN_006fd170(seven, mid, end, end, p);
    FUN_006fd250(p, mid, end);
    mpEnd = (FragRec*)(end + nb);
    FUN_006fd140(p, p + nb, seven);
  } else {
    uint32_t extra = n - after;
    FUN_006fd220(end, extra, seven);
    mpEnd = (FragRec*)(end + extra * 0x1c);
    FUN_006fd170(seven, p, end, mpEnd, p);
    mpEnd = (FragRec*)((char*)mpEnd + after * 0x1c);
    FUN_006fd140(p, end, seven);
  }
}
