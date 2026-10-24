// slice s005ccc90 -- shopping-token translator / editor-spine helpers. Flags:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Bodies reconstructed from work/match/scratch_s005ccc90_cards.txt.  The retail
// cSPEditorShoppingTokenTranslator is larger than the dev PDB layout (the disasm
// touches +0x50..+0x68, past the PDB's size 0x50), so the extra members are
// declared explicitly at their retail offsets.
#include <new>
#include <math.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

// 0x016e4178 hkMemory singleton (allocate is vtable slot 4 / +0x10).
class hkMemory {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void* allocate(int size, int memClass);  // vtable +0x10
};
extern hkMemory* g_hkMemory;

#define PV(n) virtual void pv##n();

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar16, ...> -- represented by its three pointers (the trailing
// fixed-vector-allocator storage is not modelled; only pointer members are used).
namespace eastl {
class string16 {
 public:
  wchar_t* mpBegin;     // +0x00
  wchar_t* mpEnd;       // +0x04
  wchar_t* mpCapacity;  // +0x08
  char mAllocator[12];  // +0x0c (fixed_vector_allocator storage; unused here)

  string16();
  string16& append(const wchar_t* s);                          // 0x005c3d90
  string16& operator=(const string16& x);                      // 0x0057cb60
  string16& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  string16& assign(const wchar_t* s);
  void sprintf(const wchar_t* fmt, ...);                       // 0x0041e050
  void DeallocateSelf();                                       // 0x00933960
};

// 0x01667bac eastl::gEmptyString16 -- the shared 2-wchar empty buffer a freshly
// constructed fixed-buffer string points its three pointers at.
extern wchar_t gEmptyString16[2];

inline string16::string16()
    : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {
  mAllocator[0] = 0;
}
inline string16& string16::assign(const wchar_t* s) {
  const wchar_t* end = s;
  while (*end)
    ++end;
  return assign(s, end);
}
}  // namespace eastl

namespace EA {
namespace Hash {
unsigned int FNV1_String16(const wchar_t* s, unsigned int seed, int caseMode);  // 0x00932f30
}
namespace Locale {
int SetNumberString(double value, wchar_t* buffer, int bufferSize, int flags);  // 0x00881ea0
int SetNumberString(__int64 value, wchar_t* buffer, int bufferSize);             // 0x00881ae0
int GetLocaleInfoString(int locale, int index, wchar_t* buffer, int size, void* out);  // 0x00880910
}
}

// shared numeric prefix appended before every formatted number token value.
extern "C" const wchar_t DAT_013ec468[];
// locale value passed by address to GetLocaleInfoString.
extern "C" char DAT_01517d44[];
// global "current token value" object; its +0x40..+0x4c fields feed the format strings.
extern "C" char* DAT_015ee298;
// locale date-format entry point (int dayField, int ... , wchar_t* buffer, int size, int flags).
extern "C" int FUN_00881720(int a, int b, int c, wchar_t* buffer, int size, int flags);
extern "C" const wchar_t DAT_013f5c04[];  // date format string

// ---------------------------------------------------------------------------------------------
class cRefCounted {
 public:
  int mPad0;
  int mRef;  // +4
  void IncRef(int unused);
  void DecRef(int unused);

  char pad0[4];
};

// @ 0x005CDBB0
void cRefCounted::IncRef(int unused) {
  (void)unused;
  mRef++;
}

// @ 0x005CDBC0
void cRefCounted::DecRef(int unused) {
  (void)unused;
  mRef--;
}

// ---------------------------------------------------------------------------------------------
class cTimeObj {
 public:
  PV(0) PV(1)
  virtual int GetType();  // +0x8
  int mPad4, mPad8;
  float mFloat0c;         // +0xc
  cTimeObj* mChild;       // +0x10
};

// @ 0x005CD910
float TimeObjValue(cTimeObj* obj) {
  if (obj->GetType() != 0xe)
    return 0.0f;
  cTimeObj* child = obj->mChild;
  if (child->GetType() != 8)
    return 0.0f;
  return child->mFloat0c;
}

// ---------------------------------------------------------------------------------------------
inline float FMax(float a, float b) { return a > b ? a : b; }
inline float FMin(float a, float b) { return a < b ? a : b; }

class cInterp {
 public:
  char pad0[0x88];
  float mFloat88;  // +0x88
  float mFloat8c;  // +0x8c
  float mFloat90;  // +0x90
  float mFloat94;  // +0x94
  float mFloat98;  // +0x98
  void Interp(float a, float b, float* out1, float* out2);
};

// @ 0x005CD870
void cInterp::Interp(float a, float b, float* out1, float* out2) {
  float t = ((a + b) * 0.5f) / mFloat98;
  t = FMax(t, 0.0f);
  t = FMin(t, 1.0f);
  t = (mFloat94 - mFloat90) * (1.0f - t) + mFloat90;
  *out1 = mFloat88 * t;
  *out2 = mFloat8c * t;
}

// ---------------------------------------------------------------------------------------------
class cSpine {
 public:
  char pad0[0x34];
  int mInt34;       // +0x34
  char pad38[0x74 - 0x38];
  int mInt74;       // +0x74
  char pad78[0x11c - 0x78];
  float mFloat11c;  // +0x11c
  unsigned int GetKey(int index);        // 0x005efd70
  unsigned int MakeVertKey(float a, int b);  // 0x005cdb30
};
float GetExactSkinRadiusFromVertebra(float a);  // 0x004a5b70

// @ 0x005CDB30
unsigned int cSpine::MakeVertKey(float a, int b) {
  unsigned int key = GetKey(b);
  float radius = GetExactSkinRadiusFromVertebra(a);
  int scaled = (int)((radius * -0.5f) / ((mFloat11c * 2.0f) * 0.25f + mFloat11c));
  return (mInt74 - scaled) * 0x400 | ((mInt34 << 0xb) | key) << 5 | 2;
}

// ---------------------------------------------------------------------------------------------
// SP::cString -- opaque 0x14-byte localized-string wrapper; only the methods used are declared.
namespace SP {
class cString {
 public:
  cString();                                                    // 0x006b5060
  ~cString();                                                   // 0x006b5240
  bool Load(unsigned int table, unsigned int id, const wchar_t* name);  // 0x006b54b0
  const wchar_t* GetText();                                     // 0x006b55c0
  char mData[0x14];
};
}  // namespace SP

// ---------------------------------------------------------------------------------------------
// SP::cSPEditorShoppingTokenTranslator -- derived from cStringTokenTranslator (vtable+refcount,
// 0x8 bytes).  The retail object extends past the dev PDB's 0x50; the extra members are laid out
// by offset from the disassembly (wide-string fields appended directly, the rest formatted).
namespace SP {
class cSPEditorShoppingTokenTranslator {
 public:
  char mBase[0x8];                       // +0x00 cStringTokenTranslator (vtable + refcount)
  eastl::string16 mModelName;            // +0x08
  eastl::string16 mUserName;             // +0x18
  unsigned int numItems;                 // +0x28
  unsigned int numFilteredItems;         // +0x2c
  unsigned int numInvalidItems;          // +0x30
  unsigned int mField34;                 // +0x34
  unsigned int mField38;                 // +0x38
  unsigned int mField3c;                 // +0x3c
  const wchar_t* mStr40;                 // +0x40 (appended verbatim)
  unsigned int mField44;                 // +0x44
  unsigned int mField48;                 // +0x48
  unsigned int mField4c;                 // +0x4c
  unsigned int mField50;                 // +0x50
  unsigned int mField54;                 // +0x54
  unsigned int mField58;                 // +0x58
  const wchar_t* mStr5c;                 // +0x5c (appended verbatim)
  unsigned int mField60;                 // +0x60
  unsigned int mField64;                 // +0x64
  eastl::string16 mField68;              // +0x68

  bool TranslateToken(const wchar_t* token, eastl::string16& out);       // 0x005ccc90
  static bool GetTimeString(__int64 time, eastl::string16& out);         // 0x005cd340
};
}  // namespace SP

using SP::cSPEditorShoppingTokenTranslator;

// append the shared prefix, then the member formatted as an unsigned number.
static void AppendUnsignedToken(eastl::string16& out, unsigned int value, wchar_t* buf) {
  out.append(DAT_013ec468);
  double d = (double)(int)value;
  if ((int)value < 0)
    d += 4294967296.0;
  EA::Locale::SetNumberString(d, buf, 0x40, 0);
  buf[0x3f] = 0;
  out.append(buf);
}

// @ 0x005CCC90
bool cSPEditorShoppingTokenTranslator::TranslateToken(const wchar_t* token, eastl::string16& out) {
  unsigned int h = EA::Hash::FNV1_String16(token, 0x811c9dc5, 1);
  wchar_t buf[0x40];
  switch (h) {
    case 0x05528f5a: AppendUnsignedToken(out, numInvalidItems, buf); break;   // +0x30
    case 0x0378e33c: AppendUnsignedToken(out, mField34, buf); break;
    case 0x123e4a36: AppendUnsignedToken(out, numItems, buf); break;         // +0x28
    case 0x12952639: AppendUnsignedToken(out, mField54, buf); break;
    case 0x2c681634: AppendUnsignedToken(out, mField44, buf); break;
    case 0x3e3b70e9: AppendUnsignedToken(out, mField50, buf); break;
    case 0x3ec5c09c: AppendUnsignedToken(out, mField48, buf); break;
    case 0x78c71409: AppendUnsignedToken(out, mField3c, buf); break;
    case 0xdd2e337d: AppendUnsignedToken(out, mField58, buf); break;
    case 0xe0ebb94b: AppendUnsignedToken(out, mField38, buf); break;
    case 0xea2eddc2: AppendUnsignedToken(out, numFilteredItems, buf); break;  // +0x2c
    case 0xdec2041a: AppendUnsignedToken(out, mField4c, buf); break;

    // signed 32-bit member widened to 64 bits.
    case 0x2eb181ff: {
      out.append(DAT_013ec468);
      EA::Locale::SetNumberString((__int64)(int)mField64, buf, 0x40);
      buf[0x3f] = 0;
      out.append(buf);
      break;
    }
    // unsigned 32-bit member (high half zeroed).
    case 0xb90a7c17: {
      out.append(DAT_013ec468);
      EA::Locale::SetNumberString((__int64)mField60, buf, 0x40);
      buf[0x3f] = 0;
      out.append(buf);
      break;
    }

    // wide-string members appended verbatim.
    case 0x2f199e6e: out.append(mStr40); break;
    case 0x9b8bc62e: out.append(mStr5c); break;

    // string members copied into the output.
    case 0x8074d8d6:
      out = mField68;
      break;
    case 0xd7f0f12d:
      if (&mModelName != &out)
        out.assign(mModelName.mpBegin, mModelName.mpEnd);
      break;
    case 0x4c770a96:
      if (&mUserName != &out)
        out.assign(mUserName.mpBegin, mUserName.mpEnd);
      break;

    default:
      return false;
  }
  return true;
}

// ---------------------------------------------------------------------------------------------
namespace SP {
// 0x0092e5a0 -- seconds between local time and UTC.
__int64 GetLocalTimeBias();
// 0x0092df80 EA::DateTime::DateTime::GetParameter, 0x0092e3d0 Set (thiscall).
class DateTime {
 public:
  __int64 mnSeconds;                                    // +0x00
  unsigned int GetParameter(int parameter) const;       // 0x0092df80
  void Set(int timeFrame);                              // 0x0092e3d0
};
}  // namespace SP

extern "C" __int64 __stdcall _alldiv(int lo, int hi, int divLo, int divHi);  // 0x011e09e0

// @ 0x005CD190
void GetDayOfWeekString(int day, eastl::string16& out, char useResource) {
  if (!useResource) {
    // rotate the 1..7 day index into the locale's weekday slot (Monday==1 .. Sunday==7).
    int idx = 1;
    switch (day) {
      case 1: idx = 7; break;
      case 3: idx = 2; break;
      case 4: idx = 3; break;
      case 5: idx = 4; break;
      case 6: idx = 5; break;
      case 7: idx = 6; break;
      default: idx = 1;
    }
    wchar_t buf[0x40];
    if (EA::Locale::GetLocaleInfoString(0xb, idx, buf, 0x80, DAT_01517d44) != -1) {
      const wchar_t* end = buf;
      while (*end)
        ++end;
      out.assign(buf, end);
    }
    return;
  }
  SP::cString cs;
  unsigned int id = 0;
  const wchar_t* name = 0;
  bool load = true;
  switch (day) {
    case 1: name = L"*Sunday*"; id = 0x5b175e8; break;
    case 2: name = L"*Monday*"; id = 0x5b175e9; break;
    case 3: name = L"*Tuesday*"; id = 0x5b175ea; break;
    case 4: name = L"*Wednesday*"; id = 0x5b175eb; break;
    case 5: name = L"*Thursday*"; id = 0x5b175ec; break;
    case 6: name = L"*Friday*"; id = 0x5b175ed; break;
    case 7: name = L"*Saturday*"; id = 0x5b175ee; break;
    default: load = false;
  }
  if (load)
    cs.Load(0x7c6511a1, id, name);
  const wchar_t* txt = cs.GetText();
  const wchar_t* end = txt;
  while (*end)
    ++end;
  out.assign(txt, end);
}

// @ 0x005CD340
bool cSPEditorShoppingTokenTranslator::GetTimeString(__int64 time, eastl::string16& out) {
  if (time <= 0)
    return false;

  SP::DateTime dt;
  dt.Set(2);                                    // current local time
  __int64 elapsed = dt.mnSeconds - (SP::GetLocalTimeBias() + time);
  __int64 nowWeeks = _alldiv((int)dt.mnSeconds, (int)(dt.mnSeconds >> 32), 0x93a80, 0) & 0xffffffff;
  __int64 tWeeks = _alldiv((int)(SP::GetLocalTimeBias() + time),
                           (int)((SP::GetLocalTimeBias() + time) >> 32), 0x93a80, 0);
  (void)nowWeeks;

  // clear the output only if it is currently non-empty.
  if (out.mpBegin != out.mpEnd) {
    out.mpBegin[0] = 0;
    out.mpEnd = out.mpBegin;
  }

  int ehi = (int)(elapsed >> 32);
  unsigned int elo = (unsigned int)elapsed;

  if (ehi == 0) {
    if (elo < 0x3c) {
      *(unsigned int*)(DAT_015ee298 + 0x44) = elo;
      SP::cString cs;
      cs.Load(0x7c6511a1, 0x5b175f0, L"*Seconds Ago*");
      out.append(cs.GetText());
      return true;
    }
    if (elo < 0xe10) {
      *(unsigned int*)(DAT_015ee298 + 0x48) = (unsigned int)_alldiv(elo, ehi, 0x3c, 0);
      SP::cString cs;
      cs.Load(0x7c6511a1, 0x5b175f1, L"*Minutes Ago*");
      out.append(cs.GetText());
      return true;
    }
    if (elo < 0x15180) {
      *(unsigned int*)(DAT_015ee298 + 0x4c) = (unsigned int)_alldiv(elo, ehi, 0xe10, 0);
      SP::cString cs;
      cs.Load(0x7c6511a1, 0x5b175f2, L"*Hours Ago*");
      out.append(cs.GetText());
      return true;
    }
  } else if (ehi < 0) {
    return true;
  }

  // week-number comparison: same week -> "DayOfWeek", previous week -> "*Last DayOfWeek*".
  __int64 nowWeek = _alldiv((int)DAT_01517d44[0], 0, 1, 0);  // placeholder, replaced below
  (void)nowWeek;
  __int64 nowW = _alldiv((int)(dt.mnSeconds), (int)(dt.mnSeconds >> 32), 0x93a80, 0);
  (void)nowW;

  if (tWeeks == _alldiv((int)dt.mnSeconds, (int)(dt.mnSeconds >> 32), 0x93a80, 0)) {
    eastl::string16 day;
    GetDayOfWeekString(dt.GetParameter(7), day, 0);
    out.sprintf(DAT_013f5c04, day.mpBegin);
    day.DeallocateSelf();
    return true;
  }
  __int64 prevWeek = _alldiv((int)dt.mnSeconds, (int)(dt.mnSeconds >> 32), 0x93a80, 0) - 1;
  if (tWeeks == prevWeek) {
    eastl::string16 day;
    GetDayOfWeekString(dt.GetParameter(7), day, 1);
    *(const wchar_t**)(DAT_015ee298 + 0x40) = day.mpBegin;
    SP::cString cs;
    cs.Load(0x7c6511a1, 0x5b175ef, L"*Last DayOfWeek*");
    out.append(cs.GetText());
    day.DeallocateSelf();
    return true;
  }

  // different week -> full date string.
  int a = dt.GetParameter(6);
  int b = dt.GetParameter(2);
  int c = dt.GetParameter(1);
  wchar_t buf[0x80];
  if (FUN_00881720(a, b, c, buf, 0x80, 0) != -1) {
    out.append(buf);
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------------------------
// Havok type stubs (only the members/offsets used here).
struct __declspec(align(16)) hkVector4 {
  float x, y, z, w;
  hkVector4() {}
  hkVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

class hkReferencedObject {  // vtable[0] deleting dtor, +0x4 memSize, +0x6 refCount
 public:
  virtual void* Delete(int flags);
  unsigned short memSize;   // +0x04
  unsigned short refCount;  // +0x06
  void removeReference();   // 0x0109ae60 hkWorldObject::removeReference
  void release() {
    if (memSize != 0 && --refCount == 0)
      Delete(1);
  }
};

class hkShape : public hkReferencedObject {
 public:
  int m_userData;  // +0x0c
};
class hkConvexShape : public hkShape {
 public:
  float m_radius;  // +0x10
};
class hkCapsuleShape : public hkConvexShape {
 public:
  hkCapsuleShape(const hkVector4& vertexA, const hkVector4& vertexB, float radius);  // 0x010c2730
};
class hkConvexTranslateShape : public hkConvexShape {
 public:
  hkConvexTranslateShape(const hkConvexShape* shape, const hkVector4& offset);  // 0x010bfeb0
};
class hkBoxShape : public hkConvexShape {
 public:
  hkBoxShape(const hkVector4& halfExtents, float radius);  // 0x010c05d0
};

class hkRigidBodyCinfo {  // opaque 0xd0-byte cinfo, filled by offsets
 public:
  hkRigidBodyCinfo();  // 0x01087ed0
  char mData[0xd0];
};

class hkEntity : public hkReferencedObject {
 public:
  void removeReference();  // 0x0109ae60
};
class hkRigidBody : public hkEntity {
 public:
  hkRigidBody(const hkRigidBodyCinfo& cinfo);  // 0x010878b0
};

class hkWorld {
 public:
  hkRigidBody* addEntity(hkRigidBody* body, int activation);   // 0x01082ee0
  void removeConstraint(char* tmp, void* constraint);          // 0x01086e90
  void removeEntity(char* tmp, void* body);                    // 0x01083110
};

struct hkTransform {
  float rot[3][4];
  float pos[4];
};

// @ 0x005CD670  (cdecl) build an orthonormal 3x4 basis around row `axis`.
void FUN_005cd670(hkTransform* xf, int axis) {
  float* m = &xf->rot[0][0];
  hkVector4 local(0.0f, 0.0f, 0.0f, 0.0f);
  float* lp = &local.x;
  lp[axis] = 1.0f;
  float a0 = m[axis * 4 + 0];
  float a1 = m[axis * 4 + 1];
  float a2 = m[axis * 4 + 2];
  if (a2 * lp[2] + a1 * lp[1] + a0 * lp[0] < 1e-6f) {
    for (int i = 0; i < 12; ++i)
      m[i] = 0.0f;
    m[0] = 1.0f;
    m[5] = 1.0f;
    m[10] = 1.0f;
    return;
  }
  int next = (axis + 1) % 3;
  m[axis * 4 + 0] = lp[0];
  m[axis * 4 + 1] = lp[1];
  m[axis * 4 + 2] = lp[2];
  m[axis * 4 + 3] = lp[3];

  float* rn = m + next * 4;
  rn[axis] = 0.0f;
  float len2 = rn[0] * rn[0] + rn[1] * rn[1] + rn[2] * rn[2];
  float s = (len2 == 0.0f) ? 0.0f : 1.0f / sqrtf(len2);
  rn[0] *= s;
  rn[1] *= s;
  rn[2] *= s;
  rn[3] *= s;

  float* rp = m + ((axis + 2) % 3) * 4;
  rp[0] = m[axis * 4 + 1] * rn[2] - rn[1] * m[axis * 4 + 2];
  rp[1] = rn[0] * m[axis * 4 + 2] - m[axis * 4 + 0] * rn[2];
  rp[2] = rn[1] * m[axis * 4 + 0] - m[axis * 4 + 1] * rn[0];
  rp[3] = 0.0f;
}

// ---------------------------------------------------------------------------------------------
namespace SP {
namespace EditorUtils {
float GetExactSkinRadiusFromVertebra(float scale);  // 0x004a5b70
}

// cSPEditorSpine -- only the members touched by this slice are declared, at their retail offsets.
class cSPEditorSpine {
 public:
  char pad00[0x14];
  hkWorld* mpHavokWorld;                          // +0x14
  char pad18[0x60 - 0x18];
  float mSpineHavokWorldSolverTau;                // +0x60
  char pad64[0x70 - 0x64];
  float mSpineVertebraMaxMassProportion;          // +0x70
  char pad74[0x11c - 0x74];
  float mVertebraHalfWidth;                       // +0x11c

  hkConvexShape* CreateVertebraShape(float scale);                              // 0x005cd9a0
  void RemoveVertebraFromWorld(int* info);                                      // 0x005cdae0
  void CreateWallBoxAndAddToWorld(const hkVector4& halfExt, const hkVector4& pos, hkWorld* world);  // 0x005cdbf0
};

// @ 0x005CD9A0  build the vertebra's capsule + translate shape.
hkConvexShape* cSPEditorSpine::CreateVertebraShape(float scale) {
  float skinRadius = SP::EditorUtils::GetExactSkinRadiusFromVertebra(scale);
  float radius = mVertebraHalfWidth * 2.0f * mSpineVertebraMaxMassProportion * 0.25f + skinRadius;
  float d = scale * -0.15993178f;

  hkVector4 vA(-d, 0.0f, 0.0f, 0.0f);
  hkVector4 vB(d, 0.0f, 0.0f, 0.0f);
  hkVector4 offset(0.0f, 0.0f, d, 0.0f);

  void* capMem = g_hkMemory->allocate(0x30, 0x24);
  *(unsigned short*)((char*)capMem + 4) = 0x30;
  hkCapsuleShape* capsule = new (capMem) hkCapsuleShape(vA, vB, radius);

  void* xMem = g_hkMemory->allocate(0x30, 0x24);
  *(unsigned short*)((char*)xMem + 4) = 0x30;
  hkConvexTranslateShape* xlat = new (xMem) hkConvexTranslateShape(capsule, offset);

  capsule->release();
  return xlat;
}

// @ 0x005CDAE0  drop a vertebra's Havok constraint and body from the world.
void cSPEditorSpine::RemoveVertebraFromWorld(int* info) {
  char tmp;
  if (info[2] != 0) {
    mpHavokWorld->removeConstraint(&tmp, (void*)info[2]);
    info[2] = 0;
  }
  if (info[0] != 0)
    mpHavokWorld->removeEntity(&tmp, (void*)info[0]);
  info[0] = 0;
  info[3] = 0;
}

// @ 0x005CDBF0  build a Havok box for a spine wall and add its rigid body to the world.
void cSPEditorSpine::CreateWallBoxAndAddToWorld(const hkVector4& halfExt, const hkVector4& pos,
                                                hkWorld* world) {
  hkRigidBodyCinfo cinfo;
  *(float*)((char*)&cinfo + 0xb0) = 0.0f;
  *(unsigned char*)((char*)&cinfo + 0xc0) = 7;

  void* boxMem = g_hkMemory->allocate(0x20, 0x24);
  *(unsigned short*)((char*)boxMem + 4) = 0x20;
  hkBoxShape* box = new (boxMem) hkBoxShape(halfExt, 0.04f);
  *(void**)((char*)&cinfo + 4) = box;
  *(hkVector4*)((char*)&cinfo + 0x10) = pos;

  void* rbMem = g_hkMemory->allocate(0xd0, 0x2a);
  *(unsigned short*)((char*)rbMem + 4) = 0xd0;
  hkRigidBody* body = new (rbMem) hkRigidBody(cinfo);
  box->release();

  *(float*)((char*)body + 0x64) = mSpineHavokWorldSolverTau;
  *(unsigned int*)((char*)body + 0x38) = 1;
  world->addEntity(body, 1);
  body->removeReference();
}
}  // namespace SP