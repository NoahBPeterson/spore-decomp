// src/game/SPEngine/SPAppCloudDescription.cpp -- migrated from slice(s) s00f57590, s00f56950, s00f53b60, s00f52df0, s00f523a0, s00a6dfc0, s007ec220, s00f54af0, s007ed1b0, s004553b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppCloudDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cError.h"
#include <xmmintrin.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/IO/IStream.h"

// ---- items of slice s004553b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
// ---- items of slice s004553b0 end

// ---- items of slice s007ed1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* d, const void* s, unsigned int n);
extern "C" __declspec(dllimport) char* __cdecl StrStr(const char* s, const char* sub); // IAT strstr
extern const float kInv255;   // 0x13eecd4  0.003921569f
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line); // 0x00f473a0
void operator delete(void* p, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // matching placement delete
void operator delete(void* p); // 0x00f47380
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
namespace EA {
namespace IO {
void ReadInt32(void* r, void* d, int n, int f);
}
}
namespace EA {
namespace IO {
void ReadTriple(void* r, void* d, int n, int f);
}
}
namespace EA {
namespace ArgScript {
class cArguments_s007e_d1b0 {
 public:
  char** MainArguments(int* count, int minCount, int maxCount);  // 0x00838020
  char* operator[](int index);                                  // 0x00837f20
  bool HasFlag(const char* name);                               // 0x008380b0
};  // namespace ArgScript
}
}
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
static float ArgToFloat(void* iface, void* arg) {
  typedef float(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0x98))(iface, arg);
}
static void* ArgToVec3_s007e_d1b0(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*, void*);
  return ((F0)VSLOT(iface, 0xb0))(iface, dst, arg);
}
struct Vec3Vec {
  Vec3* mpBegin;     // +0x0
  Vec3* mpEnd;       // +0x4
  Vec3* mpCapacity;  // +0x8
  void PushBack(Vec3* value);
  void ScaleCurve(Vec3* pos, Vec3* value);
  void erase(Vec3* first, Vec3* last);   // 0x009E0480
};
struct FloatVec {
  float* mpBegin;      // +0x00
  float* mpEnd;        // +0x04
  float* mpCapacity;   // +0x08
  void erase(float* first, float* last);
  void push_back(const float& value);
  void push_back_slow(float* end, const float& value);   // 0x00455660
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  float& operator[](uint32_t i) { return mpBegin[i]; }
};
void __cdecl ScaleVec3Vec(float scale, Vec3Vec* vec);            // 0x007ECC30
struct EffectDesc {
  void*    vt;           // +0x00
  uint32_t f04;          // +0x04
  uint32_t f08;          // +0x08
  uint32_t f0c;          // +0x0c
  uint32_t mFlags;       // +0x10
  uint32_t f14;          // +0x14
  uint32_t f18;          // +0x18
  uint32_t f1c;          // +0x1c
  uint32_t f20;          // +0x20
  uint32_t f24;          // +0x24
  uint32_t f28;          // +0x28
  uint32_t f2c;          // +0x2c
  uint32_t f30;          // +0x30
  uint32_t f34;          // +0x34
  uint32_t f38;          // +0x38
  uint32_t f3c;          // +0x3c
  uint32_t f40;          // +0x40
  uint32_t f44;          // +0x44
  uint32_t f48;          // +0x48
  Vec3Vec  mColorVec;    // +0x4c
  uint32_t f58;          // +0x58
  uint32_t f5c;          // +0x5c
  FloatVec mScaleVec;    // +0x60
  uint32_t f6c;          // +0x6c
  uint32_t f70;          // +0x70
  FloatVec mParentVec;   // +0x74
  EffectDesc();                           // 0x007EC5E0
  ~EffectDesc();                          // 0x007EC660
  EffectDesc(const EffectDesc& x);        // 0x007ED7C0
  int CopyFrom(const EffectDesc& other);  // 0x007ED740
};
inline void FloatVec::erase(float* first, float* last) {
  memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
  mpEnd = mpEnd - (last - first);
}
inline void FloatVec::push_back(const float& value) {
  if (mpEnd < mpCapacity) {
    float* p = mpEnd;
    mpEnd = p + 1;
    if (p != 0) *p = value;
  } else {
    push_back_slow(mpEnd, value);
  }
}
struct BattleCommand {
  void* vt;               // +0x00
  void* mIface;           // +0x04
  void* mField8;          // +0x08
  EffectDesc* mDesc;      // +0x0c
  void ColorCommand(EA::ArgScript::cArguments_s007e_d1b0* args);           // 0x007ED490
  void FloatListCommand(EA::ArgScript::cArguments_s007e_d1b0* args);       // 0x007ED560
  void FloatListParentCommand(EA::ArgScript::cArguments_s007e_d1b0* args); // 0x007ED670
};
inline void PushBackInline(Vec3Vec* v, Vec3* value) {
  Vec3* p = v->mpEnd;
  if (p < v->mpCapacity) {
    v->mpEnd = p + 1;
    if (p != 0) {
      p->x = value->x;
      p->y = value->y;
      p->z = value->z;
      return;
    }
  } else {
    v->ScaleCurve(p, value);
  }
}
    void operator delete(void*); // 0x00f47380
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007ed1b0 end

// ---- items of slice s007ec220 begin (TODO(rewrite): local stubs, replace by canonical classes)
#undef REGISTER_TEXT_CMD
namespace EA {
namespace ArgScript {
class cArguments_s007e_c220;
}
}
namespace EA {
namespace ArgScript {
void** MainArguments(cArguments_s007e_c220* self, int n);
}
}
namespace EA {
namespace ArgScript {
void** OptionArguments(cArguments_s007e_c220* self, const char* name, int n);
}
}

static void ArgToVec3(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*);
  ((F0)VSLOT(iface, 0xa4))(dst, arg);
}
struct Vec3Vec_s007e_c220 {
  Vec3* mpBegin;  // +0x0
  Vec3* mpEnd;    // +0x4
};
struct ScreenEffect {
  char pad[0x50];
};
struct SphereSurface {
  char pad[0x50];
};
// ---- items of slice s007ec220 end

// ---- items of slice s00a6dfc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  MakeCaseInsensitive(void* s);                              // 0x8409b0
extern "C" void* v007e2ea0(void* out, void* ht);                            // 0x7e2ea0 hashtable find
extern "C" void  v00a6e9e0(void** out, void* map);                          // 0xa6e9e0 map find
extern "C" void  v00a6ea80(void** out, void* map);                          // 0xa6ea80 map insert
extern "C" void  v00b20930(void** out, void* key);                          // 0xb20930 MapStrFind::Find
extern const char  kTerrain[];      // 0x1455e4c "terrain"
extern const char  kWater[];        // 0x1455e44 "water"
namespace EA {
namespace Swarm {
struct EString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpAlloc;      // +0x0c
    void assign(const char* first, const char* last);   // 0x00454cb0
};
}
}
namespace EA {
namespace Swarm {
struct DrawInfoTarget;
}
}
namespace EA {
namespace Swarm {
class cEffectsParser { public:
    char      _pad00[0x10];
    unsigned  mFlags;               // +0x10
    char      _pad14[0x0c];
    void*     mpColl;               // +0x20
    char      _pad24[0x20];
    int       m44;                  // +0x44
    char      _pad48[0x30];
    int       m78;                  // +0x78
    char      _pad7c[0x10];
    void*     mpSaveColl;           // +0x8c
    char      _pad90[0x28];
    char      mEditors[0x13 * 0x20]; // +0xb8
    char      mName[0x10];          // +0x3c4

    long long EffectsMapID(const char* s);                          // 00a6e600
    long long MapFindA(const char* s);                              // 00a6eaf0
    long long MapFindB(const char* s, int idx);                     // 00a6eb60
    long long MapFindC(const char* s, int idx);                     // 00a6ebd0
    long long LookupRes(int idx, const char* s);                    // 00a6ec40
    void      ParseDrawInfoOptions(void* args, void* obj, DrawInfoTarget* t); // 00a6ed80
    int       GetInheritedA(int a, int depth, void* c);             // 00a6f090
    int       GetInheritedB(int a, int depth, void* c);             // 00a6f0d0
};
}
}
namespace EA {
namespace Swarm {
struct DrawInfoTarget {
    int      m00;               // +0x00
    int      m04;               // +0x04
    char     m08;               // +0x08
    char     mType;             // +0x09 (0xf = text; else decal)
    char     mFlags;            // +0x0a
    char     mBuffer;           // +0x0b
    short    mLayer;            // +0x0c
    char     _pad0e[2];
    float    mSortOffset;       // +0x10
    char     _pad14[4];
    unsigned mResA;             // +0x18
    unsigned mResB;             // +0x1c
};
}
}
// ---- items of slice s00a6dfc0 end

// ---- items of slice s00f523a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ArgScript {
struct cArguments_s00f5_23a0 {
    const char** OptionArguments(const char* name, int* count, int min, int max);  // 0x00838130 (EA::ArgScript::cArguments::OptionArguments)
    const char** OptionArguments(const char* name, int min);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
    bool HasFlag(const char* name);  // 0x008380b0 (EA::ArgScript::cArguments::HasFlag)
};
}
}
struct cIArgEvaluator {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
    virtual float EvalFloat(const char* s);             // vtable 0x98
    virtual void v39();
    virtual unsigned short EvalUShort(const char* s);   // vtable 0xa0
};
float* ParseVector2(float* out, cIArgEvaluator* eval, const char*** p, int count);
struct EffectParams {
    char  pad00[8];
    unsigned m_flags;       // +0x08
    char  pad0c[0x18 - 0x0c];
    float m_delayX;         // +0x18
    float m_delayY;         // +0x1c
    float m_triggerX;       // +0x20
    float m_triggerY;       // +0x24
    char  pad28[0x78 - 0x28];
    float m_value;          // +0x78
    unsigned short m_7c;    // +0x7c
    char  pad7e[2];
    float m_speedScale;     // +0x80
};
// ---- items of slice s00f523a0 end

// ---- items of slice s00f52df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_16c9234;   // 0x016c9234
extern const float g_16c9238;   // 0x016c9238
extern const float g_16c923c;   // 0x016c923c
struct Vec3_s00f5_2df0 {
    float x, y, z;
    Vec3_s00f5_2df0() {}
    Vec3_s00f5_2df0(float a, float b, float c) : x(a), y(b), z(c) {}
};
namespace SP {
template <class T> struct SimpleVector {                        // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;                                            // +0x00
    T*       mpEnd;                                              // +0x04
    T*       mpCapacity;                                         // +0x08
    uint32_t mAllocator[2];                                      // +0x0c

    void DoInsertValue(T* pos, const T& value);                  // 0x00455660
    void AllocateCopy(int count, const void* allocator);          // 0x004aa350
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void FreeRange(T* first, T* last);                           // 0x00a87300
};
}
namespace SP {
template <class T> struct Vector {                               // out-of-line DoInsertValue
    T*       mpBegin;                                            // +0x00
    T*       mpEnd;                                              // +0x04
    T*       mpCapacity;                                         // +0x08
    uint32_t mAllocator[2];                                      // +0x0c

    void DoInsertValue(T* pos, const T& value);                  // 0x007ed1b0
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
struct cCloudDescription {
    void*    mVtbl;                 // +0x000
    void*    mParser;               // +0x004
    uint32_t m08;                   // +0x008
    float    f0c, f10, f14, f18, f1c, f20, f24;                       // +0x00c .. +0x027
    float    f28, f2c, f30, f34, f38, f3c;                            // +0x028 .. +0x03f
    float    f40, f44, f48, f4c, f50, f54, f58, f5c, f60;             // +0x040 .. +0x063
    SP::SimpleVector<float> v64;    // +0x064
    float    f78;                   // +0x078
    uint16_t w7c;                   // +0x07c
    uint8_t  pad7e[2];              // +0x07e (uninitialised)
    float    f80;                   // +0x080
    SP::SimpleVector<float> v84;    // +0x084
    float    f98;                   // +0x098
    SP::SimpleVector<float> v9c;    // +0x09c
    float    fb0;                   // +0x0b0
    SP::SimpleVector<float> vb4;    // +0x0b4
    float    fc8;                   // +0x0c8
    float    fcc;                   // +0x0cc
    SP::Vector<Vec3_s00f5_2df0> d0;            // +0x0d0
    float    fe4, fe8, fec;         // +0x0e4 .. +0x0ec
    SP::SimpleVector<float> vf0;    // +0x0f0
    float    f104;                  // +0x104
    int32_t  a108;                  // +0x108
    int32_t  a10c;                  // +0x10c
    uint8_t  b110;                  // +0x110
    uint8_t  b111;                  // +0x111
    uint8_t  b112;                  // +0x112
    uint8_t  b113;                  // +0x113
    uint16_t w114;                  // +0x114
    uint8_t  pad116[2];             // +0x116 (uninitialised)
    float    f118;                  // +0x118
    uint8_t  pad11c[4];             // +0x11c (uninitialised)
    int32_t  a120;                  // +0x120
    int32_t  a124;                  // +0x124
    uint8_t  b128;                  // +0x128
    uint8_t  b129;                  // +0x129
    uint8_t  b12a;                  // +0x12a
    uint8_t  b12b;                  // +0x12b
    uint8_t  b12c;                  // +0x12c
    uint8_t  b12d;                  // +0x12d
    uint8_t  b12e;                  // +0x12e
    uint8_t  b12f;                  // +0x12f
    float    f130[13];              // +0x130 .. +0x163
    SP::SimpleVector<float> s164;   // +0x164
    uint8_t  b178;                  // +0x178
    uint8_t  b179;                  // +0x179
    uint8_t  b17a;                  // +0x17a
    uint8_t  b17b;                  // +0x17b
    uint8_t  pad17c[4];             // +0x17c (uninitialised)
    SP::SimpleVector<float> s180;   // +0x180
    SP::SimpleVector<float> v194;   // +0x194
    SP::SimpleVector<float> s1a8;   // +0x1a8
    float    f1bc[9];               // +0x1bc .. +0x1df
    int32_t  a1e0[6];               // +0x1e0 .. +0x1f7
    float    a1f8[7];               // +0x1f8 .. +0x213
    SP::SimpleVector<float> v214;   // +0x214
    uint8_t  b228;                  // +0x228
    uint8_t  pad229[3];             // +0x229 (uninitialised)
    float    f22c;                  // +0x22c
    float    f230;                  // +0x230
    float    f234;                  // +0x234
    SP::SimpleVector<float> v238;   // +0x238
    float    f24c;                  // +0x24c
    float    f250;                  // +0x250
    SP::SimpleVector<float> s254;   // +0x254

    cCloudDescription();
    ~cCloudDescription();
};
static inline void FreeCounted(void* p) {
    if (p) {
        if (((int*)p)[-1] != 0)
            operator delete(p);
    }
}
// ---- items of slice s00f52df0 end

// ---- items of slice s00f53b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fUnset;              // 0x015b0be8 (sentinel compared against +-x)
extern float g_fEpsilon;            // 0x013ec4b8 (added before sqrt, ~1e-8)
typedef unsigned int  u32;
typedef unsigned char u8;
typedef float (__thiscall *FN_FLOAT)(void* self, const char* s);
typedef char  (__thiscall *FN_BOOL) (void* self, const char* s);
typedef void  (__thiscall *FN_VEC2) (void* self, void* out, const char* s);
typedef void* (__thiscall *FN_VEC3) (void* self, void* out, const char* s);
static __forceinline FN_FLOAT SlotFloat(void* p) { return *(FN_FLOAT*)((char*)(*(void**)p) + 0x98); }
static __forceinline FN_BOOL  SlotBool (void* p) { return *(FN_BOOL *)((char*)(*(void**)p) + 0xa0); }
static __forceinline FN_VEC2  SlotVec2 (void* p) { return *(FN_VEC2 *)((char*)(*(void**)p) + 0xa4); }
static __forceinline FN_VEC3  SlotVec3 (void* p) { return *(FN_VEC3 *)((char*)(*(void**)p) + 0xa8); }
static __forceinline float ParseFloat(void* p, const char* s)             { return SlotFloat(p)(p, s); }
static __forceinline void  ParseVec2 (void* p, void* out, const char* s)  { SlotVec2(p)(p, out, s); }
static __forceinline void* ParseVec3 (void* p, void* out, const char* s)  { return SlotVec3(p)(p, out, s); }
namespace EA {
namespace ArgScript {
class cArguments_s00f5_3b60 { public:
    const char** MainArguments(int n);                                      // 0x838320
    const char** MainArguments(int* pCount, int lo, int hi);                // 0x838020
    bool         HasFlag(const char* name);                                 // 0x8380b0
    const char** OptionArguments(const char* name, int n);                  // 0x838330
    const char** OptionArguments(const char* name, int* pCount, int lo, int hi); // 0x838130
};
}
}
namespace EA {
namespace ArgScript {
float ParseRangedFloat(void* parser, const char* s, float lo, float hi);    // 0x840d50
}
}
namespace EA {
namespace Swarm {
class cEffectsParser_s00f5_3b60 { public:
    // 0xa6ed80
    void ParseDrawInfoOptions(EA::ArgScript::cArguments_s00f5_3b60* args, void* parser, void* out);  // 0x00a6ed80 (EA::Swarm::cEffectsParser::ParseDrawInfoOptions)
};  // namespace EA::Swarm
}
}
struct DrawInfoVector {
    long long resize(int n, const char* value);                             // 0xa6ec40
    long long FUN_00a6e600(const char* name);                               // 0xa6e600
};
void  __cdecl FUN_006e9910(float radius);                                   // 0x6e9910
void  __cdecl FUN_00a93c60(void* v);                                        // 0xa93c60
struct Vec3Helper { void FUN_00a9a1c0(float a, float b, float c); };        // 0xa9a1c0
struct CVec3 { float x, y, z; };
extern CVec3 g_cloudDir;            // 0x016c9234 (unit x/y/z triple)
struct cCloudSourceCommand {
    void* mVtbl;      // +0x00
    void* mParser;    // +0x04
    void* m08;        // +0x08
    void* mParams;    // +0x0c

    void Execute(EA::ArgScript::cArguments_s00f5_3b60* args);            // 0x00f53b60
    void Speed(EA::ArgScript::cArguments_s00f5_3b60* args);              // 0x00f54040
    void Delay(EA::ArgScript::cArguments_s00f5_3b60* args);              // 0x00f54290
    void Duration(EA::ArgScript::cArguments_s00f5_3b60* args);           // 0x00f544d0
    void SetCount(EA::ArgScript::cArguments_s00f5_3b60* args);           // 0x00f545c0
    void Tile(EA::ArgScript::cArguments_s00f5_3b60* args);               // 0x00f54670
    void Material(EA::ArgScript::cArguments_s00f5_3b60* args);           // 0x00f547a0
    void Count(EA::ArgScript::cArguments_s00f5_3b60* args);              // 0x00f54880
    void HeightRange(EA::ArgScript::cArguments_s00f5_3b60* args);        // 0x00f54980
    void SetHeightRange(EA::ArgScript::cArguments_s00f5_3b60* args);     // 0x00f54ab0
};
// ---- items of slice s00f53b60 end

// ---- items of slice s00f54af0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char* __cdecl strstr_s00f5_4af0(const char* haystack, const char* needle);
namespace EA {
namespace ArgScript {
struct cArguments_s00f5_4af0;
}
}
namespace EA {
namespace ArgScript {
struct Vector3 {
    float x, y, z;
};
}
}
namespace EA {
namespace ArgScript {
struct cParser {
    virtual void v00() {} virtual void v01() {} virtual void v02() {} virtual void v03() {}
    virtual void v04() {} virtual void v05() {} virtual void v06() {} virtual void v07() {}
    virtual void v08() {} virtual void v09() {} virtual void v10() {} virtual void v11() {}
    virtual void v12() {} virtual void v13() {} virtual void v14() {} virtual void v15() {}
    virtual void v16() {} virtual void v17() {} virtual void v18() {} virtual void v19() {}
    virtual void v20() {} virtual void v21() {} virtual void v22() {} virtual void v23() {}
    virtual void v24() {} virtual void v25() {} virtual void v26() {} virtual void v27() {}
    virtual void v28() {} virtual void v29() {} virtual void v30() {} virtual void v31() {}
    virtual void v32() {} virtual void v33() {} virtual void v34() {} virtual void v35() {}
    virtual void v36() {} virtual void v37() {}
    virtual float Evaluate(const char* text);          // +0x98
    virtual void v39() {} virtual void v40() {} virtual void v41() {} virtual void v42() {}
    virtual void v43() {}
    virtual Vector3 EvaluateVector(const char* text);  // +0xb0
};
}
}
namespace EA {
namespace ArgScript {
struct cEffectsParser_s00f5_4af0 {
    int64_t EffectsMapID(const char* name);            // 0x00a6e600
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s00f5_4af0 {
    const char** MainArguments(int* count, int minArgs, int maxArgs) const;   // 0x00838020
    bool HasFlag(const char* name) const;                                     // 0x008380b0
    const char** OptionArguments(const char* name, int minArgs) const;        // 0x00838330
    const char* operator[](int index) const;                                  // 0x00837f20
};
}
}
namespace EA {
namespace ArgScript {
struct Vec0C {
    Vector3* mpBegin;       // +0
    Vector3* mpEnd;         // +4
    Vector3* mpCapacity;    // +8
    Vector3* erase(Vector3* first, Vector3* last);           // 0x009e0480
    void ScaleCurve(Vector3* end, const Vector3* value);     // 0x007ed1b0
    void push_back(const Vector3& value) {
        if (mpEnd < mpCapacity) {
            Vector3* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot) {
                slot->x = value.x;
                slot->y = value.y;
                slot->z = value.z;
            }
        } else {
            ScaleCurve(mpEnd, &value);
        }
    }
};
}
}
namespace EA {
namespace ArgScript {
extern float g_cloudAlphaValue;    // 0x013eecd4
}
}
namespace EA {
namespace ArgScript {
struct cEffect {
    uint32_t pad00[4];          // +0x00
    uint32_t mFlags;            // +0x10
    uint32_t pad14[0x31];       // +0x14 .. +0xd7
    Vec0C    mCurve;            // +0xd8
    uint32_t padE4[2];          // +0xe4
    Vector3  mVary;             // +0xec
    uint32_t padF8[0x33];       // +0xf8 .. +0x1c3
    float    mPinDistance;      // +0x1c4
    float    mValue1;           // +0x1c8
    float    mStrength;         // +0x1cc
    float    mScout;            // +0x1d0
    float    mVertical;         // +0x1d4
    float    mKillHeight;       // +0x1d8
    float    mDeathTime;        // +0x1dc
    uint32_t pad1E0[2];         // +0x1e0
    int64_t  mId;               // +0x1e8
    uint32_t pad1F0[0x20];      // +0x1f0 .. +0x26f
    cEffectsParser_s00f5_4af0* mpEffectsParser;   // +0x270
};
}
}
namespace EA {
namespace ArgScript {
struct cEffectCommandBase {
    void*    mpVtable;      // +0
    cParser* mParser;       // +4
    uint32_t mPad08;        // +8
    cEffect* mEffect;       // +0xc
};
}
}
namespace EA {
namespace ArgScript {
float ParseRangedFloat(cParser* parser, const char* text, float minValue, float maxValue);                 // 0x00840d50
}
}
namespace EA {
namespace ArgScript {
Vector3* ParseRangedVector3(Vector3* out, cParser* parser, const char* text, float minValue, float maxValue); // 0x00840e10
}
}
namespace EA {
namespace ArgScript {
void ApplyCurveAlpha(float value, Vec0C* curve);                                                          // 0x007ecc30
}
}
namespace EA {
namespace ArgScript {
struct cPinCommand : cEffectCommandBase {
    void ParseLine(const cArguments_s00f5_4af0& args);        // 0x00f54af0
};
}
}
namespace EA {
namespace ArgScript {
struct cScoutCommand : cEffectCommandBase {
    void ParseLine(const cArguments_s00f5_4af0& args);        // 0x00f54c00
};
}
}
namespace EA {
namespace ArgScript {
struct cStrengthCommand : cEffectCommandBase {
    void ParseLine(const cArguments_s00f5_4af0& args);        // 0x00f54d60
};
}
}
namespace EA {
namespace ArgScript {
struct cStrengthExCommand : cEffectCommandBase {
    void ParseLine(const cArguments_s00f5_4af0& args);        // 0x00f54e10
};
}
}
namespace EA {
namespace ArgScript {
struct cCloudAlphaCommand : cEffectCommandBase {
    void Execute(const cArguments_s00f5_4af0& args);          // 0x00f558b0
};
}
}
// ---- items of slice s00f54af0 end

// ---- items of slice s00f56950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char* PTR_s_cloud;         // 0x015b0af4  ("cloud")
extern uint16_t    gEmptyString16[];    // 0x01667bac
struct Vec3_s00f5_6950 { float x, y, z; Vec3_s00f5_6950() {} Vec3_s00f5_6950(const Vec3_s00f5_6950& o) : x(o.x), y(o.y), z(o.z) {} };
namespace EA {
namespace ArgScript {
#define PV(n) virtual void pv##n();
}
}
namespace EA {
namespace ArgScript {
class cIParser_s00f5_6950 { public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float GetFloat(const char* text);              // +0x98
    PV(39) PV(40) PV(41) PV(42) PV(43)
    virtual Vec3_s00f5_6950 GetVector2(const char* text);             // +0xb0
};
}
}
namespace EA {
namespace ArgScript {
class cICommand_s00f5_6950 {
    public: virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s00f5_6950 : public cICommand_s00f5_6950 { public:
    cIParser_s00f5_6950* mParser;      // +0x4
    int       mRefCount;    // +0x8
    cCommandBase_s00f5_6950();         // 0x0083c800
};
}
}
void*  __cdecl EAAllocate(uint32_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
namespace SP {
template <class T> struct SimpleVector_s00f5_6950 {                        // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void DoInsertValue(T* pos, const T& value);                  // 0x00455660
    void AllocateCopy(int count, const void* allocator);          // 0x004aa350
    void resize(int count);                                      // 0x004afc80
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last) {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd = mpEnd - (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
}
struct SubD0
{
    uint32_t w[5];
    void AssignFrom(const SubD0& src);      // 0x006f50f0
};
struct Sub164
{
    uint32_t w[5];
    void AssignFrom(const Sub164& src);     // 0x00a9a310
};
struct Sub180
{
    uint32_t w[5];
    void AssignFrom(const Sub180& src);     // 0x006f50f0
};
struct Sub1a8
{
    uint32_t w[5];
    void AssignFrom(const Sub1a8& src);     // 0x00a87920
};
struct Sub1f8
{
    uint32_t w[13];
    void AssignFrom(const Sub1f8& src);     // 0x00a9a7f0
};
struct Sub254
{
    uint32_t w[5];
    void AssignFrom(const Sub254& src);     // 0x00a9a370
};
struct Blob20 { uint32_t w[8]; };
struct cCloudEffectCommand {
    void*    mVtbl;                // +0x00
    void*    mParser;              // +0x04
    int      mFlags08;             // +0x08
    float    mFloats[22];          // +0x0c .. +0x60
    SP::SimpleVector_s00f5_6950<float> v64;   // +0x64
    float    f78;                  // +0x78
    uint16_t w7c;                  // +0x7c
    float    f80;                  // +0x80
    SP::SimpleVector_s00f5_6950<float> v84;   // +0x84
    float    f98;                  // +0x98
    SP::SimpleVector_s00f5_6950<float> v9c;   // +0x9c
    float    fb0;                  // +0xb0
    SP::SimpleVector_s00f5_6950<float> vb4;   // +0xb4
    float    fc8;                  // +0xc8
    float    fcc;                  // +0xcc
    SubD0    d0;                   // +0xd0
    float    fe4;                  // +0xe4
    float    fe8;                  // +0xe8
    float    fec;                  // +0xec
    SP::SimpleVector_s00f5_6950<float> vf0;   // +0xf0
    float    f104;                 // +0x104
    Blob20   blob108;              // +0x108
    uint8_t  b128[8];              // +0x128
    float    f130[13];             // +0x130 .. +0x160
    Sub164   s164;                 // +0x164
    uint8_t  b178[5];              // +0x178
    Sub180   s180;                 // +0x180
    SP::SimpleVector_s00f5_6950<float> v194;  // +0x194
    Sub1a8   s1a8;                 // +0x1a8
    float    f1bc[9];              // +0x1bc .. +0x1dc
    uint32_t a1e0[6];              // +0x1e0
    Sub1f8   s1f8;                 // +0x1f8
    float    f22c;                 // +0x22c
    float    f230;                 // +0x230
    float    f234;                 // +0x234
    SP::SimpleVector_s00f5_6950<float> v238;  // +0x238
    float    f24c;                 // +0x24c
    float    f250;                 // +0x250
    Sub254   s254;                 // +0x254

    cCloudEffectCommand();                                     // 0x00f53590
    cCloudEffectCommand(const cCloudEffectCommand& src);       // 0x00f56cc0
};
struct AppPropsFields {
    virtual void vf0();
    AppPropsFields();              // 0x0083cdd0
    char mPad[0x2c];               // vptr + 0x2c = 0x30
};
struct cOwner { void Set(const char* name, int a, void* obj); }; // 0x00a6f9c0
struct cCloudEffect : AppPropsFields {
    cOwner*  mOwner;               // +0x30
    int      mPad34;               // +0x34
    int      mField38;             // +0x38
    int      mPad3c;               // +0x3c
    cCloudEffectCommand mCmd;      // +0x40
    char     pad2a8[8];            // +0x2a8
    const char* mStrBegin;         // +0x2b0
    const char* mStrEnd;           // +0x2b4
    void*    mStrCap;              // +0x2b8
    int      mPad2bc;              // +0x2bc
    uint8_t  mFlag2c0;             // +0x2c0

    cCloudEffect() : mField38(0xeba93c76), mStrBegin((const char*)gEmptyString16),
                     mStrEnd((const char*)gEmptyString16), mStrCap((void*)0x1667bad) {}
    virtual void Update(char flag);                            // 0x00f57410 = vtable +0x14
};
struct Registrar {
virtual void rv0();
virtual void rv1();
virtual void rv2();
virtual void rv3();
virtual void rv4();
    virtual void AddCommand(const char* name, void* obj);      // +0x14
    virtual void AddGroup(const char* name, void* obj);        // +0x18
};
struct cCloudGroup : EA::ArgScript::cCommandBase_s00f5_6950 {
    int mPad;                      // +0xc
    cCloudGroup() {}
};
// ---- items of slice s00f56950 end

// ---- items of slice s00f57590 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
template <class T> struct SimpleVector_s00f5_7590 {                       // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void operator=(const SimpleVector_s00f5_7590& src);                    // 0x0050d4e0
    void DoInsertValue(T* pos, const T& value);                 // 0x00a87d20
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            *mpEnd++ = value;
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { mpEnd = mpBegin; }
};  // namespace SP
}
namespace EA {
namespace ArgScript {
class cIParser_s00f5_7590 { public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void pv35(void* obj);
    PV(36) PV(37)
    virtual float GetFloat(const char* text);                   // +0x98
    PV(39) PV(40) PV(41) PV(42) PV(43)
    virtual Vec3 GetVector2(const char* text);                  // +0xb0
};
}
}
namespace EA {
namespace ArgScript {
class cArguments_s00f5_7590 { public:
    const char** MainArguments(int* count, int minCount, int maxCount);                     // 0x00838020
    const char** MainArguments(int count);                                                  // 0x00838320
    const char** OptionArguments(const char* name, int count);                              // 0x00838330
    const char** OptionArguments(const char* name, int* count, int minCount, int maxCount); // 0x00838130
    bool         HasFlag(const char* flag);                                                 // 0x008380b0
    const char*  operator[](int index);                                                     // 0x00837f20
};
}
}
struct SubD0_s00f5_7590  {  // 0x006f50f0
    uint32_t w[5];
    void AssignFrom(const SubD0_s00f5_7590& s);
};
struct Sub164_s00f5_7590 {  // 0x00a9a310
    uint32_t w[5];
    void AssignFrom(const Sub164_s00f5_7590& s);
};
struct Sub180_s00f5_7590 {  // 0x006f50f0
    uint32_t w[5];
    void AssignFrom(const Sub180_s00f5_7590& s);
};
struct Sub1a8_s00f5_7590 {  // 0x00a87920
    uint32_t w[5];
    void AssignFrom(const Sub1a8_s00f5_7590& s);
};
struct Sub254_s00f5_7590 {  // 0x00a9a500
    uint32_t w[5];
    void AssignFrom(const Sub254_s00f5_7590& s);
};
struct cCloudDescription_s00f5_7590 {
    void*    mVtbl;                 // +0x000
    void*    mParser;               // +0x004
    uint32_t m08;                   // +0x008
    float    f0c, f10, f14, f18, f1c, f20, f24;      // +0x00c .. +0x027
    float    f28, f2c, f30, f34, f38, f3c;           // +0x028 .. +0x03f
    float    f40, f44, f48, f4c, f50, f54, f58, f5c, f60;  // +0x040 .. +0x063
    SP::SimpleVector_s00f5_7590<float> v64;    // +0x064
    float    f78;                   // +0x078
    uint16_t w7c;                   // +0x07c
    float    f80;                   // +0x080
    SP::SimpleVector_s00f5_7590<float> v84;    // +0x084
    float    f98;                   // +0x098
    SP::SimpleVector_s00f5_7590<float> v9c;    // +0x09c
    float    fb0;                   // +0x0b0
    SP::SimpleVector_s00f5_7590<float> vb4;    // +0x0b4
    float    fc8;                   // +0x0c8
    float    fcc;                   // +0x0cc
    SubD0_s00f5_7590    d0;                    // +0x0d0
    float    fe4, fe8, fec;         // +0x0e4 .. +0x0ec
    SP::SimpleVector_s00f5_7590<float> vf0;    // +0x0f0
    float    f104;                  // +0x104
    uint32_t blob108[8];            // +0x108
    uint8_t  b128[8];               // +0x128
    float    f130[13];              // +0x130 .. +0x15f
    Sub164_s00f5_7590   s164;                  // +0x164
    uint8_t  b178[5];               // +0x178
    Sub180_s00f5_7590   s180;                  // +0x180
    SP::SimpleVector_s00f5_7590<float> v194;   // +0x194
    Sub1a8_s00f5_7590   s1a8;                  // +0x1a8
    float    f1bc[9];               // +0x1bc .. +0x1df
    uint32_t a1e0[6];               // +0x1e0 .. +0x1f7
    uint32_t a1f8[7];               // +0x1f8 .. +0x213
    SP::SimpleVector_s00f5_7590<float> v214;   // +0x214
    uint8_t  b228;                  // +0x228
    float    f22c;                  // +0x22c
    float    f230;                  // +0x230
    float    f234;                  // +0x234
    SP::SimpleVector_s00f5_7590<float> v238;   // +0x238
    float    f24c;                  // +0x24c
    float    f250;                  // +0x250
    Sub254_s00f5_7590   s254;                  // +0x254

    cCloudDescription_s00f5_7590();                                    // 0x00f53590
    ~cCloudDescription_s00f5_7590();                                   // 0x00f53420
    cCloudDescription_s00f5_7590& operator=(const cCloudDescription_s00f5_7590& src);
};
struct Archive {
virtual void r0();
virtual void r1();
virtual void r2();
virtual void r3();
virtual void r4();
virtual void r5();
virtual void r6();
virtual void r7();
virtual void r8();
virtual void r9();
virtual void r10();
virtual void r11();
    virtual void Read(void* dst, int size);                     // vtable +0x30
};
void __cdecl ReadInt32 (Archive* ar, void* out, int count, int flags);  // 0x0093a780
void __cdecl ReadByte  (Archive* ar, void* out, int count);             // 0x0093a6c0
void __cdecl ReadU32a  (Archive* ar, void* out, int count, int flags);  // 0x0093a700
void __cdecl ReadU32b  (Archive* ar, void* out, int count, int flags);  // 0x0093a800
void __cdecl ReadVecF  (Archive* ar, void* v);                          // 0x007d27d0
void __cdecl ReadSubA  (Archive* ar, void* v);                          // 0x007ed920
void __cdecl ReadSubB  (Archive* ar, void* v);                          // 0x00a9a870
void __cdecl ReadSubC  (Archive* ar, void* v);                          // 0x00a87f50
void __cdecl ReadBlob  (Archive* ar, void* v);                          // 0x00a85b00
void __cdecl ReadSubD  (Archive* ar, void* v);                          // 0x00a7b9a0
void __cdecl ReadSubE  (Archive* ar, void* v);                          // 0x00a7ba10
void __cdecl ReadSubF  (Archive* ar, void* v);                          // 0x00a9a8d0
struct cEffectsParser_s00f5_7590 {
    const char** GetInheritedDescription(const char** argv, int count, int type);  // 0x00a6f090
};
struct EaString {
    const char* mpBegin;            // +0x00
    const char* mpEnd;              // +0x04
    void*       mpCapacity;         // +0x08
    uint32_t    mPad;               // +0x0c
    void assign(const char* first, const char* last);       // 0x00454cb0
};
struct cCloudEffect_s00f5_7590 {
    char     pad00[0x04];
    EA::ArgScript::cIParser_s00f5_7590* mParser;   // +0x04
    char     pad08[0x30 - 0x08];
    cEffectsParser_s00f5_7590* mOwner;             // +0x30
    char     pad34[0x40 - 0x34];
    cCloudDescription_s00f5_7590 mCmd;             // +0x40
    char     pad2a8[0x2b0 - 0x2a8];
    EaString mStr;                      // +0x2b0
    uint8_t  b2c0;                      // +0x2c0
    uint8_t  b2c1;                      // +0x2c1

    void Execute(EA::ArgScript::cArguments_s00f5_7590& args);   // 0x00f57ba0
};
struct SurfaceInfo {
    uint32_t m00;                                       // +0x00
    uint32_t m04, m08, m0c, m10, m14, m18, m1c;         // +0x04 .. +0x1f
    uint32_t m20, m24, m28, m2c, m30, m34, m38, m3c;    // +0x20 .. +0x3f
    uint32_t m40, m44, m48, m4c, m50, m54;              // +0x40 .. +0x57
};
struct CloudBigState {
    char     pad00[0x10];
    uint32_t mFlags;                                    // +0x10
    char     pad14[0x1b0 - 0x14];
    SP::SimpleVector_s00f5_7590<SurfaceInfo> mSurfaces;            // +0x1b0
    char     pad1c4[0x270 - 0x1c4];
    void*    mParser270;                                // +0x270
};
void __cdecl ParseSurfaceOptions(const char* name, EA::ArgScript::cArguments_s00f5_7590* args,
                                 void* out, void* parser);           // 0x00a7d280
struct cCloudSurfaceCommand {
    char     pad00[0x0c];
    CloudBigState* mState;                              // +0x0c
    void Execute(EA::ArgScript::cArguments_s00f5_7590& args);      // 0x00f57a30
};
// ---- items of slice s00f57590 end

// @ 0x00455660
void* VectorPushBack3(int* self, Vec3* value)
{
    if (self[1] == self[2]) {
        // grow and append; outlined
    }
    return 0;
}

// @ 0x007ecb50
extern "C" void ScreenFilterTextureExecute(int* self, EA::ArgScript::cArguments_s007e_c220* args)
{
  void** p = EA::ArgScript::MainArguments(args, 1);
  uint32_t count = *(uint32_t*)p;
  ScreenEffect* fx = *(ScreenEffect**)((char*)self + 0xc);
  extern void Vec3Resize(ScreenEffect*, uint32_t);
  Vec3Resize(fx, count);
  void** o = EA::ArgScript::OptionArguments(args, "factor", 1);
  if (o) *(float*)((char*)fx + 0x30) = ArgToFloat(*(void**)((char*)self + 4), *o);
}

// @ 0x007ecc30
void ScaleVec3Vec(float s, Vec3Vec_s007e_c220* v)
{
  int32_t count = (int32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  if (count != 0) {
    uint32_t i = 0;
    uint32_t off = 0;
    __m128 sv = _mm_load_ss(&s);
    do {
      Vec3* e = (Vec3*)((char*)v->mpBegin + off);
      _mm_store_ss(&e->x, _mm_mul_ss(_mm_load_ss(&e->x), sv));
      _mm_store_ss(&e->y, _mm_mul_ss(_mm_load_ss(&e->y), sv));
      _mm_store_ss(&e->z, _mm_mul_ss(_mm_load_ss(&e->z), sv));
      ++i;
      off += 0xc;
    } while (i < (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc);
  }
}

// @ 0x007ed090
extern "C" void SphereSurfaceParseExtraOptions(SphereSurface* self, EA::ArgScript::cArguments_s007e_c220* args)
{
  void** p = EA::ArgScript::MainArguments(args, 1);
  if (p) {
    extern void WStringAssign(void* dst, void* arg);   // 0x0041e050 (equiv t3)
    WStringAssign((char*)self + 0x14, *p);
  }
  p = EA::ArgScript::OptionArguments(args, "radius", 1);
  if (p) {
    extern void Vec3Resize(SphereSurface*, uint32_t);
    Vec3Resize(self, *(uint32_t*)p);
  }
  p = EA::ArgScript::OptionArguments(args, "factor", 1);
  if (p) {
    void* iface = *(void**)((char*)self + 0x4);
    *(float*)((char*)self + 0x30) = ArgToFloat(iface, *p);
  }
  p = EA::ArgScript::OptionArguments(args, "offset", 1);
  if (p) {
    void* iface = *(void**)((char*)self + 0x4);
    Vec3 tmp;
    ArgToVec3(iface, &tmp, *p);
    *(float*)((char*)self + 0x40) = tmp.x;
    *(float*)((char*)self + 0x44) = tmp.y;
  }
}

// @ 0x007ed1b0
void Vec3Vec::ScaleCurve(Vec3* pos, Vec3* value)
{
  Vec3Vec* v = this;
  if (v->mpEnd != v->mpCapacity) {
    if (pos <= value && value < v->mpEnd) value = (Vec3*)((char*)value + 0xc);
    if (v->mpEnd) *v->mpEnd = v->mpEnd[-1];
    Vec3* dst = v->mpEnd;
    Vec3* src = v->mpEnd;
    while ((Vec3*)((char*)src - 0xc) != pos) {
      dst[-1] = src[-2];
      dst = (Vec3*)((char*)dst - 0xc);
      src = (Vec3*)((char*)src - 0xc);
    }
    *pos = *value;
    v->mpEnd = (Vec3*)((char*)v->mpEnd + 0xc);
    return;
  }
  uint32_t cap = (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  if (cap == 0) cap = 1;
  else cap = cap * 2;
  Vec3* data = cap ? (Vec3*)operator new[](cap * 0xc, "App", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  Vec3* d = data;
  for (Vec3* p = v->mpBegin; p != pos; ++p, ++d) *d = *p;
  if (d) *d = *value;
  ++d;
  for (Vec3* p = pos; p != v->mpEnd; ++p, ++d) *d = *p;
  if (v->mpBegin) operator delete(v->mpBegin);
  v->mpBegin = data;
  v->mpEnd = d;
  v->mpCapacity = data + cap;
}

// @ 0x007ed3e0
void Vec3Vec::PushBack(Vec3* value)
{
  Vec3Vec* v = this;
  Vec3* p = v->mpEnd;
  if (p < v->mpCapacity) {
    v->mpEnd = p + 1;
    if (p != 0) {
      p->x = value->x;
      p->y = value->y;
      p->z = value->z;
      return;
    }
  } else {
    ScaleCurve(p, value);
  }
}

// @ 0x007ed490
void BattleCommand::ColorCommand(EA::ArgScript::cArguments_s007e_d1b0* args)
{
  int count;
  char** list = args->MainArguments(&count, 1, 0x7fffffff);
  Vec3Vec& colors = mDesc->mColorVec;
  colors.erase(colors.mpBegin, colors.mpEnd);
  Vec3 tmp;
  for (int i = 0; i < count; ++i) {
    Vec3* value = (Vec3*)ArgToVec3_s007e_d1b0(mIface, &tmp, list[i]);
    PushBackInline(&mDesc->mColorVec, value);
  }
  char* text = (*args)[0];
  if (StrStr(text, "255") != 0)
    ScaleVec3Vec(kInv255, &mDesc->mColorVec);
}

// @ 0x007ed560
void BattleCommand::FloatListCommand(EA::ArgScript::cArguments_s007e_d1b0* args)
{
  int count;
  char** list = args->MainArguments(&count, 1, 0x7fffffff);
  FloatVec& sv = mDesc->mScaleVec;
  sv.erase(sv.mpBegin, sv.mpEnd);
  for (int i = 0; i < count; ++i)
    mDesc->mScaleVec.push_back(ArgToFloat(mIface, list[i]));
  char* text = (*args)[0];
  if (StrStr(text, "255") != 0) {
    const float k = kInv255;
    FloatVec& v = mDesc->mScaleVec;
    for (uint32_t i = 0; i < v.size(); ++i) v[i] *= k;
  }
}

// @ 0x007ed670
void BattleCommand::FloatListParentCommand(EA::ArgScript::cArguments_s007e_d1b0* args)
{
  int count;
  char** list = args->MainArguments(&count, 0, 0x7fffffff);
  FloatVec& pv = mDesc->mParentVec;
  pv.erase(pv.mpBegin, pv.mpEnd);
  for (int i = 0; i < count; ++i) {
    float value = ArgToFloat(mIface, list[i]);
    mDesc->mParentVec.push_back(value);
  }
  if (args->HasFlag("parentScale"))
    mDesc->mFlags |= 1;
}

// @ 0x007ed920
extern "C" void* ReadVec3Vec(void* reader, Vec3Vec* v)
{
  uint32_t n = 0;
  EA::IO::ReadInt32(reader, &n, 1, 0);
  extern void Vec3Resize(Vec3Vec*, uint32_t);
  Vec3Resize(v, n);
  uint32_t i = 0;
  while (i < n) {
    typedef void(__thiscall * F0)(void*, void*, int);
    ((F0)VSLOT(reader, 0x30))(reader, (char*)v->mpBegin + i * 0xc, 0xc);
    ++i;
  }
  return reader;
}

// @ 0x007edaf0
extern "C" void ReadEffect(void* reader, void* unused, char* dst)
{
  uint32_t flags = 0;
  EA::IO::ReadInt32(reader, &flags, 1, 0);
  *(uint32_t*)(dst + 8) = flags & 0xf;
  uint32_t n = 0;
  EA::IO::ReadInt32(reader, &n, 1, 0);
  extern void WStringResize(void*, uint32_t);
  WStringResize(dst, n);
  extern void ReadRaw(void*, void*, uint32_t, int);   // 0x0093a700 (equiv t3)
  ReadRaw(reader, *(void**)(dst + 0xc), n, 0);
  EA::IO::ReadTriple(reader, dst + 0x20, 1, 0);
  EA::IO::ReadInt32(reader, dst + 0x28, 1, 0);
  EA::IO::ReadTriple(reader, dst + 0x30, 1, 0);
  typedef void(__thiscall * F0)(void*, void*, int);
  ((F0)VSLOT(reader, 0x30))(reader, dst + 0x38, 8);
  EA::IO::ReadInt32(reader, dst + 0x40, 1, 0);
  ReadVec3Vec(reader, (Vec3Vec*)(dst + 0x44));
  extern void ReadPlaneVec(void*, void*);   // 0x007d27d0 (equiv t3)
  ReadPlaneVec(reader, dst + 0x58);
  ReadPlaneVec(reader, dst + 0x6c);
}

// @ 0x00a6e600
namespace EA { namespace Swarm {
long long cEffectsParser::EffectsMapID(const char* s)
{
    const char* p = s;
    const char* q = p + 1;
    do { } while (*p++ != 0);
    char* esi = (char*)this + 0x3c4;
    ((EString*)esi)->assign(s, s + (int)(p - q));
    MakeCaseInsensitive(esi);
    if (strcmp(kTerrain, s) == 0)
        return 0;
    if (strcmp(kWater, s) == 0)
        return 1;
    void* coll = *(void**)((char*)this + 0x8c);
    if (coll != 0) {
        long long v = (*(long long(__thiscall**)(void*, const char*))(*((char**)coll) + 0x1c))(coll, s);
        if (v != -1)
            return v;
    }
    return -1;
}
}}  // namespace EA::Swarm

// @ 0x00a6ebd0
namespace EA { namespace Swarm {
long long cEffectsParser::MapFindC(const char* s, int idx)
{
    void* self = this;
    char* edi = (char*)self;
    char* esi = edi + 0x3c4;
    const char* p = s;
    do { } while (*p++ != 0);
    ((EString*)esi)->assign(s, p - 1);
    MakeCaseInsensitive(esi);
    char* tbl = *(char**)(edi + 0x78) + idx * 0x20;
    void* local_8[2];
    v007e2ea0(local_8, tbl);
    int ecx = *(int*)(tbl + 8);
    int edx = *(int*)(tbl + 4);
    if ((int)local_8[0] == *(int*)(edx + ecx * 4))
        return -1;
    return *(int*)((char*)local_8[0] + 0x10);
}
}}  // namespace EA::Swarm

// @ 0x00a6ec40
namespace EA { namespace Swarm {
long long cEffectsParser::LookupRes(int idx, const char* s)
{
    void* self = this;
    char* esi = (char*)self;
    char* edi = esi + 0x3c4;
    const char* p = s;
    do { } while (*p++ != 0);
    ((EString*)edi)->assign(s, p - 1);
    MakeCaseInsensitive(edi);
    if (idx < 0x13) {
        char* ep = (char*)(idx * 0x20 + esi + 0xb8);
        void* local_10[3];
        v00a6e9e0(local_10, ep);
        if ((int)local_10[0] != *(int*)(*(int*)(ep + 4) + *(int*)(ep + 8) * 4))
            return ((long long*)local_10[0])[2];
    }
    if (idx == 1) {
        int a = ((cEffectsParser*)esi)->MapFindC((char*)*(void**)edi, 1);
        if (a >= 0) {
            char* coll = *(char**)(esi + 0x20);
            char* r = (char*)(*(void*(__thiscall**)(char*, int, int))(*((char**)coll) + 0x28))(coll, a, 1);
            return *(long long*)(r + 8);
        }
    }
    void* save = *(void**)(esi + 0x8c);
    if (save != 0) {
        void* local_10[3];
        char c = (*(char(__thiscall**)(void*, int, const char*, void*))(*((char**)save) + 8))(save, idx, s, local_10);
        if (c)
            return *(long long*)local_10;
        if (((*(unsigned*)(esi + 0x10) >> 1) & 1) == 0) {
            void* it[2];
            v00b20930(it, edi);
            if ((int)it[0] == (int)(esi + 0x3d8 + idx * 0x1c))
                v00a6ea80(it, edi);
        }
    }
    return -1;
}
}}  // namespace EA::Swarm

// @ 0x00f52b80
void FUN_00f52b80(EA::ArgScript::cArguments_s00f5_23a0* args, EffectParams& out, cIArgEvaluator& eval)
{
    int count;
    const char** p;
    unsigned short u16;

    p = args->OptionArguments("loop", &count, 1, 2);
    if (p != 0) {
        out.m_value = eval.EvalFloat(p[0]);
        if (count > 1) u16 = eval.EvalUShort(p[1]);
        else u16 = 0;
    }
    else {
        p = args->OptionArguments("single", &count, 0, 1);
        if (p != 0) {
            if (count > 0) out.m_value = eval.EvalFloat(p[0]);
            else out.m_value = 0.01f;
            u16 = 1;
        }
        else {
            p = args->OptionArguments("sustain", &count, 1, 2);
            if (p == 0) {
                p = args->OptionArguments("hold", &count, 1, 2);
                if (p == 0) {
                    p = args->OptionArguments("kill", &count, 1, 2);
                    if (p == 0) goto after_mode;
                    out.m_flags |= 0x8000000;
                }
                else {
                    out.m_flags |= 0x10000000;
                }
            }
            else {
                out.m_flags |= 4;
            }
            out.m_value = eval.EvalFloat(p[0]);
            if (count > 1) u16 = eval.EvalUShort(p[1]);
            else u16 = 1;
        }
    }
    out.m_7c = u16;

after_mode:
    if (args->HasFlag("sizeScale"))   out.m_flags |= 0x100;
    if (args->HasFlag("areaScale"))   out.m_flags |= 0x200;
    if (args->HasFlag("volumeScale")) out.m_flags |= 0x400;

    p = args->OptionArguments("speedScale", 1);
    if (p != 0) out.m_speedScale = eval.EvalFloat(p[0]);

    const char** q;
    q = args->OptionArguments("delay", &count, 1, 0x7fffffff);
    if (q != 0) {
        float vec[2];
        float* v = ParseVector2(vec, &eval, &q, count);
        out.m_delayX = v[0];
        out.m_delayY = v[1];
    }
    q = args->OptionArguments("trigger", &count, 1, 0x7fffffff);
    if (q != 0) {
        float vec[2];
        float* v = ParseVector2(vec, &eval, &q, count);
        out.m_triggerX = v[0];
        out.m_triggerY = v[1];
    }
}

// @ 0x00f53420
cCloudDescription::~cCloudDescription()
{
    FreeCounted(s254.mpBegin);
    FreeCounted(v238.mpBegin);
    FreeCounted(v214.mpBegin);
    s1a8.FreeRange(s1a8.mpBegin, s1a8.mpEnd);
    FreeCounted(s1a8.mpBegin);
    FreeCounted(v194.mpBegin);
    FreeCounted(s180.mpBegin);
    FreeCounted(s164.mpBegin);
    FreeCounted(vf0.mpBegin);
    FreeCounted(d0.mpBegin);
    FreeCounted(vb4.mpBegin);
    FreeCounted(v9c.mpBegin);
    FreeCounted(v84.mpBegin);
    FreeCounted(v64.mpBegin);
    mVtbl = (void*)0x13ef094;
}

// @ 0x00f53590
cCloudDescription::cCloudDescription()
{
    mParser = 0;
    mVtbl = (void*)0x148e910;
    m08 = 0;

    f0c = 2.0f;
    f10 = 2.0f;
    f14 = 0.0f;
    f18 = -1.0f;
    f1c = -1.0f;
    f20 = -1.0f;
    f24 = -1.0f;
    f28 = 0.0f;
    f2c = 0.0f;
    f30 = 1.0f;
    f34 = 0.0f;
    f38 = 0.0f;
    f3c = 1.0f;
    f40 = 0.0f; f44 = 0.0f; f48 = 0.0f; f4c = 0.0f;
    f50 = 0.0f; f54 = 0.0f; f58 = 0.0f; f5c = 0.0f;
    f60 = -1.0f;

    v64.mpBegin = 0; v64.mpEnd = 0; v64.mpCapacity = 0;
    f78 = 1.0f;
    w7c = 0;
    f80 = 0.0f;
    v84.mpBegin = 0; v84.mpEnd = 0; v84.mpCapacity = 0;
    f98 = 0.0f;
    v9c.mpBegin = 0; v9c.mpEnd = 0; v9c.mpCapacity = 0;
    fb0 = 0.0f;
    vb4.mpBegin = 0; vb4.mpEnd = 0; vb4.mpCapacity = 0;
    fc8 = 0.0f;
    fcc = 0.0f;
    d0.mpBegin = 0; d0.mpEnd = 0; d0.mpCapacity = 0;

    fe4 = g_16c9234;
    fe8 = g_16c9238;
    fec = g_16c923c;

    vf0.mpBegin = 0; vf0.mpEnd = 0; vf0.mpCapacity = 0;
    f104 = 0.0f;

    a108 = -1;
    a10c = -1;
    b110 = 0; b111 = 0; b112 = 0; b113 = 0;
    w114 = 0;
    f118 = 0.0f;
    a120 = -1;
    a124 = -1;
    b128 = 0; b129 = 0;
    b12c = 0; b12d = 0; b12e = 0; b12f = 0;
    f130[0] = 0.0f;
    b12a = 1; b12b = 1;

    f130[1] = g_16c9234;
    f130[2] = g_16c9238;
    f130[3] = g_16c923c;
    f130[4] = 0.0f; f130[5] = 0.0f; f130[6] = 0.0f;
    f130[7] = g_16c9234;
    f130[8] = g_16c9238;
    f130[9] = g_16c923c;
    f130[10] = 0.0f; f130[11] = 0.0f; f130[12] = 0.0f;

    s164.mpBegin = 0; s164.mpEnd = 0; s164.mpCapacity = 0;
    b178 = 0; b17a = 0;
    b179 = 0xff; b17b = 0xff;
    s180.mpBegin = 0; s180.mpEnd = 0; s180.mpCapacity = 0;
    v194.mpBegin = 0; v194.mpEnd = 0; v194.mpCapacity = 0;
    s1a8.mpBegin = 0; s1a8.mpEnd = 0; s1a8.mpCapacity = 0;

    f1bc[5] = -1.0e9f;
    f1bc[0] = 1.0f;
    f1bc[1] = 0.0f; f1bc[2] = 0.0f; f1bc[3] = 0.0f; f1bc[4] = 0.0f;
    f1bc[6] = 0.0f;
    f1bc[7] = -10000.0f;
    f1bc[8] = 10000.0f;

    a1e0[0] = -1; a1e0[1] = -1; a1e0[2] = -1;
    a1e0[3] = -1; a1e0[4] = -1; a1e0[5] = -1;

    a1f8[0] = 5.0f; a1f8[1] = 5.0f;
    a1f8[2] = 0.0f; a1f8[3] = 0.0f;
    a1f8[4] = 0.25f;
    a1f8[5] = 0.0f; a1f8[6] = 0.0f;

    v214.mpBegin = 0; v214.mpEnd = 0; v214.mpCapacity = 0;
    b228 = 2;
    f22c = g_16c9234;
    f230 = g_16c9238;
    f234 = g_16c923c;
    v238.mpBegin = 0; v238.mpEnd = 0; v238.mpCapacity = 0;
    f24c = 1.0f;
    f250 = 0.0f;
    s254.mpBegin = 0; s254.mpEnd = 0; s254.mpCapacity = 0;

    v64.push_back(30.0f);
    d0.push_back(Vec3_s00f5_2df0(1.0f, 1.0f, 1.0f));
    vf0.push_back(1.0f);
    v84.push_back(1.0f);
    v9c.push_back(1.0f);
    vb4.push_back(0.0f);
}

// @ 0x00f53b60
void cCloudSourceCommand::Execute(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    float vout[3];          // shared Vec2/Vec3 parse buffer
    float lo0, lo1, lo2;    // inclusive bounds
    float hi0, hi1, hi2;    // exclusive bounds
    const char** a;

    args->MainArguments(0);
    lo0 = g_cloudDir.x;
    lo1 = g_cloudDir.y;
    lo2 = g_cloudDir.z;
    hi0 = lo0;
    hi1 = lo1;
    hi2 = lo2;
    *(u32*)((char*)mParams + 0x10) &= ~0x10u;

    if (args->HasFlag("point")) goto done;

    a = args->OptionArguments("square", 1);
    if (a) {
        float d = ParseFloat(mParser, a[0]);
        if (lo0 != g_fUnset && lo0 != -g_fUnset) {
            lo0 -= d; lo1 -= d; lo2 = lo2; hi0 += d; hi1 += d; hi2 = hi2;
        }
        goto done;
    }
    a = args->OptionArguments("quad", 1);
    if (a) {
        ParseVec2(mParser, vout, a[0]);
        if (lo0 != g_fUnset && lo0 != -g_fUnset) {
            lo0 -= vout[0]; lo1 -= vout[1]; lo2 = lo2; hi0 += vout[0]; hi1 += vout[1]; hi2 = hi2;
        }
        goto done;
    }
    a = args->OptionArguments("cube", 1);
    if (a) { FUN_006e9910(ParseFloat(mParser, a[0])); goto done; }

    a = args->OptionArguments("box", 1);
    if (a == 0) {
        a = args->OptionArguments("circle", 1);
        if (a) {
            *(u32*)((char*)mParams + 0x10) |= 0x10u;
            float r = ParseFloat(mParser, a[0]);
            ((Vec3Helper*)vout)->FUN_00a9a1c0(r, r, 0.0f);
            goto done;
        }
        a = args->OptionArguments("sphere", 1);
        if (a) {
            *(u32*)((char*)mParams + 0x10) |= 0x10u;
            FUN_006e9910(ParseFloat(mParser, a[0]));
            goto done;
        }
        a = args->OptionArguments("ellipse", 1);
        if (a) { ellipseBox: *(u32*)((char*)mParams + 0x10) |= 0x10u; goto parseBox; }
        a = args->OptionArguments("ellipsoid", 1);
        if (a) goto ellipseBox;

        a = args->OptionArguments("ring", 2);
        if (a) {
            float r = ParseFloat(mParser, a[0]);
            *(float*)((char*)mParams + 0x68) = EA::ArgScript::ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
            ((Vec3Helper*)vout)->FUN_00a9a1c0(r, r, 0.0f);
            goto done;
        }
        a = args->OptionArguments("torus", 2);
        if (a) {
            ParseVec3(mParser, vout, a[0]);
            *(float*)((char*)mParams + 0x68) = EA::ArgScript::ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
            goto offset;
        }
        goto done;
    }
parseBox:
    ParseVec3(mParser, vout, a[0]);
offset:
    FUN_00a93c60(vout);

done:
    a = args->OptionArguments("offset", 1);
    if (a) {
        float* p = (float*)ParseVec3(mParser, vout, a[0]);
        if (lo0 != g_fUnset && lo0 != -g_fUnset) {
            hi0 = p[0] + hi0;
            lo0 = p[0] + lo0;
            lo1 = p[1] + lo1;
            hi1 = p[1] + hi1;
            lo2 = p[2] + lo2;
            hi2 = p[2] + hi2;
        }
    }
    *(float*)((char*)mParams + 0x5c) = hi0;
    *(float*)((char*)mParams + 0x60) = hi1;
    *(float*)((char*)mParams + 0x64) = hi2;
    *(float*)((char*)mParams + 0x50) = lo0;
    *(float*)((char*)mParams + 0x54) = lo1;
    *(float*)((char*)mParams + 0x58) = lo2;
    if (args->HasFlag("scaleCloud"))    *(u32*)((char*)mParams + 0x10) |= 0x800u;
    if (args->HasFlag("resetIncoming")) *(u32*)((char*)mParams + 0x10) |= 0x4000000u;
}

// @ 0x00f54040
void cCloudSourceCommand::Speed(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    float fdir[3];
    float tmp[3];
    int   n;
    args->MainArguments(0);
    const char** a = args->OptionArguments("speed", &n, 1, 0x7fffffff);
    if (a) {
        float v = ParseFloat(mParser, a[0]);
        float b = 0.0f;
        if (n > 1) b = ParseFloat(mParser, a[1]);
        *(float*)((char*)mParams + 0x48) = v - b;
        *(float*)((char*)mParams + 0x4c) = b + v;
    }
    a = args->OptionArguments("dir", &n, 1, 2);
    if (a) {
        ParseVec3(mParser, fdir, a[0]);
        float bx = g_cloudDir.x, by = g_cloudDir.y, bz = g_cloudDir.z;
        if (n > 1) {
            float* p = (float*)ParseVec3(mParser, tmp, a[1]);
            bx = p[0]; by = p[1]; bz = p[2];
        }
        float inv = 1.0f / sqrtf((float)(fdir[0] * fdir[0] + fdir[1] * fdir[1]
                                  + fdir[2] * fdir[2] + g_fEpsilon));
        float ux = fdir[0] * inv;
        float uy = fdir[1] * inv;
        float uz = fdir[2] * inv;
        *(float*)((char*)mParams + 0x30) = ux;
        *(float*)((char*)mParams + 0x3c) = ux;
        *(float*)((char*)mParams + 0x34) = uy;
        *(float*)((char*)mParams + 0x40) = uy;
        *(float*)((char*)mParams + 0x38) = uz;
        *(float*)((char*)mParams + 0x44) = uz;
        if (ux != g_fUnset && ux != -g_fUnset) {
            *(float*)((char*)mParams + 0x30) = ux - bx;
            *(float*)((char*)mParams + 0x34) = uy - by;
            *(float*)((char*)mParams + 0x38) = uz - bz;
            *(float*)((char*)mParams + 0x3c) = ux + bx;
            *(float*)((char*)mParams + 0x40) = uy + by;
            *(float*)((char*)mParams + 0x44) = uz + bz;
        }
    }
    if (args->HasFlag("base"))          *(u32*)((char*)mParams + 0x10) |= 0x8u;
    if (args->HasFlag("scaleExisting")) *(u32*)((char*)mParams + 0x10) |= 0x2000000u;
}

// @ 0x00f54290
void cCloudSourceCommand::Delay(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    int n;
    args->MainArguments(0);
    *(u32*)((char*)mParams + 0x10) |= 0x80000u;

    const char** a = args->OptionArguments("delay", &n, 1, 2);
    if (a) {
        float v = ParseFloat(mParser, a[0]);
        float b = 0.0f;
        if (n > 1) b = ParseFloat(mParser, a[1]);
        *(float*)((char*)mParams + 0x200) = v - b;
        *(float*)((char*)mParams + 0x204) = v + b;
    }
    a = args->OptionArguments("strength", &n, 1, 2);
    if (a) {
        float v = ParseFloat(mParser, a[0]);
        float b = 0.0f;
        if (n > 1) b = ParseFloat(mParser, a[1]);
        *(float*)((char*)mParams + 0x208) = v - b;
        *(float*)((char*)mParams + 0x20c) = v + b;
    }
    a = args->OptionArguments("turn", &n, 1, 0x7fffffff);
    if (a) {
        *(float*)((char*)mParams + 0x210) = EA::ArgScript::ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);
        if (n < 2) *(u32*)((char*)mParams + 0x214) = 0;
        else       *(float*)((char*)mParams + 0x214) = EA::ArgScript::ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
    }
    a = args->OptionArguments("mix", 1);
    if (a) *(float*)((char*)mParams + 0x218) = EA::ArgScript::ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);

    if (args->HasFlag("wait")) *(u32*)((char*)mParams + 0x10) |= 0x100000u;
}

// @ 0x00f544d0
void cCloudSourceCommand::Duration(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    float b = 0.0f;
    float v = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, a[0]);
    if (n > 1) b = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, a[1]);
    *(float*)((char*)mParams + 0x14) = v - b;
    *(float*)((char*)mParams + 0x18) = v + b;

    const char** p = args->OptionArguments("preroll", 1);
    if (p) {
        *(float*)((char*)mParams + 0x1c) =
            (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
        return;
    }
    *(float*)((char*)mParams + 0x1c) = v > 0.5f ? v : 0.5f;
}

// @ 0x00f545c0
void cCloudSourceCommand::SetCount(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 1);
    if (n > 0) {
        *(long long*)((char*)mParams + 0x110) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(1, a[0]);
    }
    *(u8*)((char*)mParams + 0x119) = 0x0f;
    const char** p = args->OptionArguments("overrideSet", 1);
    if (p) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x131) = fn(mParser, p[0]);
    }
    else *(u8*)((char*)mParams + 0x131) = 0;
    ((EA::Swarm::cEffectsParser_s00f5_3b60*)*(void**)((char*)mParams + 0x270))
        ->ParseDrawInfoOptions(args, mParser, (char*)mParams + 0x110);
}

// @ 0x00f54670
void cCloudSourceCommand::Tile(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 1);
    if (n > 0) {
        *(long long*)((char*)mParams + 0x110) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(0, a[0]);
    }
    const char** t = args->OptionArguments("tile", &n, 1, 2);
    if (t) {
        *(u8*)((char*)mParams + 0x132) =
            (*(FN_BOOL*)((char*)(*(void**)mParser) + 0xa0))(mParser, t[0]);
        if (n > 1)
            *(u8*)((char*)mParams + 0x133) =
                (*(FN_BOOL*)((char*)(*(void**)mParser) + 0xa0))(mParser, t[1]);
        else *(u8*)((char*)mParams + 0x133) = 1;
    }
    ((EA::Swarm::cEffectsParser_s00f5_3b60*)*(void**)((char*)mParams + 0x270))
        ->ParseDrawInfoOptions(args, mParser, (char*)mParams + 0x110);
    const char** p = args->OptionArguments("overrideSet", 1);
    if (p) {
        *(u8*)((char*)mParams + 0x131) =
            (*(FN_BOOL*)((char*)(*(void**)mParser) + 0xa0))(mParser, p[0]);
    }
    else   *(u8*)((char*)mParams + 0x131) = 0;
    if (args->HasFlag("acceptComposite")) *(u32*)((char*)mParams + 0x10) |= 0x400000u;
    else                                  *(u32*)((char*)mParams + 0x10) &= 0xffbfffffu;
}

// @ 0x00f547a0
void cCloudSourceCommand::Material(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 1);
    if (n > 0) {
        *(long long*)((char*)mParams + 0x110) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(2, a[0]);
    }
    *(u32*)((char*)mParams + 0x10) |= 0x200000u;
    const char** m = args->OptionArguments("material", 1);
    if (m) {
        *(long long*)((char*)mParams + 0x128) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(1, m[0]);
        *(u8*)((char*)mParams + 0x119) = 0x0f;
    }
    const char** p = args->OptionArguments("overrideSet", 1);
    if (p) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x131) = fn(mParser, p[0]);
    }
    else *(u8*)((char*)mParams + 0x131) = 0;
    ((EA::Swarm::cEffectsParser_s00f5_3b60*)*(void**)((char*)mParams + 0x270))
        ->ParseDrawInfoOptions(args, mParser, (char*)mParams + 0x110);
}

// @ 0x00f54880
void cCloudSourceCommand::Count(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    args->MainArguments(0);
    if (const char** a = args->OptionArguments("speed", 1))
        *(float*)((char*)mParams + 0x138) =
            (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, a[0]);
    if (const char** a = args->OptionArguments("count", 1)) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x136) = fn(mParser, a[0]);
    }
    if (const char** a = args->OptionArguments("start", 1)) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x135) = fn(mParser, a[0]);
    }
    if (const char** a = args->OptionArguments("random", 1)) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x137) = fn(mParser, a[0]);
    }
}

// @ 0x00f54980
void cCloudSourceCommand::HeightRange(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    const char** a = args->MainArguments(1);
    *(long long*)((char*)mParams + 0x1f0) =
        ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->FUN_00a6e600(a[0]);

    if (args->HasFlag("pinToSurface")) *(u32*)((char*)mParams + 0x10) |= 0x20u;

    const char** p = args->OptionArguments("belowHeight", 1);
    if (p) {
        *(u32*)((char*)mParams + 0x10) |= 0x40u;
        float* d = (float*)((char*)mParams + 0x1e4);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
    }
    p = args->OptionArguments("aboveHeight", 1);
    if (p) {
        *(u32*)((char*)mParams + 0x10) |= 0x40u;
        float* d = (float*)((char*)mParams + 0x1e0);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
    }
    p = args->OptionArguments("heightRange", 2);
    if (p) {
        *(u32*)((char*)mParams + 0x10) |= 0x40u;
        float* d = (float*)((char*)mParams + 0x1e0);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
        d = (float*)((char*)mParams + 0x1e4);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[1]);
    }
    if (args->HasFlag("density")) *(u32*)((char*)mParams + 0x10) |= 0x80u;
}

// @ 0x00f54ab0
void cCloudSourceCommand::SetHeightRange(EA::ArgScript::cArguments_s00f5_3b60* args)
{
    const char** a = args->MainArguments(1);
    *(long long*)((char*)mParams + 0x1f8) =
        ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->FUN_00a6e600(a[0]);
}

// @ 0x00f54af0
namespace EA { namespace ArgScript {
void cPinCommand::ParseLine(const cArguments_s00f5_4af0& args)
{
    int count;
    const char** main = args.MainArguments(&count, 0, 1);
    if (count > 0) {
        mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
    } else {
        mEffect->mId = 0;
    }
    mEffect->mFlags |= 0x2000;
    if (args.HasFlag("pinToMap")) {
        mEffect->mFlags |= 0x40000;
        mEffect->mPinDistance = 0.0f;
    } else {
        const char** option = args.OptionArguments("bounce", 1);
        if (option)
            mEffect->mPinDistance = mParser->Evaluate(option[0]);
    }
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
    const char** death = args.OptionArguments("death", 1);
    if (death)
        mEffect->mDeathTime = ParseRangedFloat(mParser, death[0], 0.0f, 1.0f);
}
}}  // namespace EA::ArgScript

// @ 0x00f54c00
namespace EA { namespace ArgScript {
void cScoutCommand::ParseLine(const cArguments_s00f5_4af0& args)
{
    int count;
    const char** main = args.MainArguments(&count, 2, 3);
    const char* third;
    if (count > 2) {
        mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
        mEffect->mValue1 = mParser->Evaluate(main[1]);
        third = main[2];
    } else {
        mEffect->mId = 0;
        mEffect->mValue1 = mParser->Evaluate(main[0]);
        third = main[1];
    }
    mEffect->mStrength = mParser->Evaluate(third);
    mEffect->mFlags |= 0x2000;
    mEffect->mFlags |= 0x4000;
    const char** option = args.OptionArguments("scout", 1);
    if (option)
        mEffect->mScout = mParser->Evaluate(option[0]);
    const char** vertical = args.OptionArguments("vertical", 1);
    if (vertical)
        mEffect->mVertical = mParser->Evaluate(vertical[0]);
    const char** killHeight = args.OptionArguments("killHeight", 1);
    if (killHeight)
        mEffect->mKillHeight = mParser->Evaluate(killHeight[0]);
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
}
}}  // namespace EA::ArgScript

// @ 0x00f54d60
namespace EA { namespace ArgScript {
void cStrengthCommand::ParseLine(const cArguments_s00f5_4af0& args)
{
    int count;
    const char** main = args.MainArguments(&count, 1, 0x7fffffff);
    mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
    mEffect->mFlags |= 0x2000;
    mEffect->mFlags |= 0x8000;
    const char** option = args.OptionArguments("strength", 1);
    if (option) {
        mEffect->mStrength = mParser->Evaluate(option[0]);
    } else {
        mEffect->mStrength = 1.0f;
    }
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
}
}}  // namespace EA::ArgScript

// @ 0x00f54e10
namespace EA { namespace ArgScript {
void cStrengthExCommand::ParseLine(const cArguments_s00f5_4af0& args)
{
    int count;
    const char** main = args.MainArguments(&count, 1, 0x7fffffff);
    mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
    mEffect->mFlags |= 0x2000;
    mEffect->mFlags |= 0x10000;
    const char** option = args.OptionArguments("strength", 1);
    if (option) {
        mEffect->mStrength = mParser->Evaluate(option[0]);
    } else {
        mEffect->mStrength = 1.0f;
    }
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
}
}}  // namespace EA::ArgScript

// @ 0x00f54ef0
namespace
{
class cCloudEffectCommand {
 public:
  void OnRegister();
};
void cCloudEffectCommand::OnRegister() {}
}

// @ 0x00f558b0
namespace EA { namespace ArgScript {
void cCloudAlphaCommand::Execute(const cArguments_s00f5_4af0& args)
{
    int count;
    const char** main = args.MainArguments(&count, 1, 0x7fffffff);
    mEffect->mCurve.erase(mEffect->mCurve.mpBegin, mEffect->mCurve.mpEnd);
    for (int i = 0; i < count; ++i) {
        Vector3 value = mParser->EvaluateVector(main[i]);
        mEffect->mCurve.push_back(value);
    }
    const char** option = args.OptionArguments("vary", 1);
    if (option) {
        Vector3 temp;
        mEffect->mVary = *ParseRangedVector3(&temp, mParser, option[0], 0.0f, 1.0f);
    }
    if (strstr_s00f5_4af0(args[0], "255"))
        ApplyCurveAlpha(g_cloudAlphaValue, &mEffect->mCurve);
}
}}  // namespace EA::ArgScript

// @ 0x00f574c0
void SWARM_CloudAddCommands(Registrar* p1, Registrar* p2)
{
    cCloudEffect* obj = (cCloudEffect*)EAAllocate(0x2c8, "ArgScript/CloudEffect", 0, 0, 0, 0);
    obj = new (obj) cCloudEffect();
    p2->AddCommand(PTR_s_cloud, obj);

    cCloudGroup* grp = (cCloudGroup*)EAAllocate(0x10, "ArgScript/GroupCloud", 0, 0, 0, 0);
    if (grp) {
        new (grp) cCloudGroup();
        p1->AddGroup(PTR_s_cloud, grp);
    } else {
        p1->AddGroup(PTR_s_cloud, grp);
    }
}

// @ 0x00f57590
cCloudDescription_s00f5_7590& cCloudDescription_s00f5_7590::operator=(const cCloudDescription_s00f5_7590& src)
{
    m08 = src.m08;
    f0c = src.f0c;
    f10 = src.f10;
    f14 = src.f14;
    f18 = src.f18;
    f1c = src.f1c;
    f20 = src.f20;
    f24 = src.f24;
    f34 = src.f34;
    f38 = src.f38;
    f3c = src.f3c;
    f28 = src.f28;
    f2c = src.f2c;
    f30 = src.f30;
    f40 = src.f40;
    f44 = src.f44;
    f54 = src.f54;
    f58 = src.f58;
    f5c = src.f5c;
    f48 = src.f48;
    f4c = src.f4c;
    f50 = src.f50;
    f60 = src.f60;
    v64 = src.v64;
    f78 = src.f78;
    w7c = src.w7c;
    f80 = src.f80;
    v84 = src.v84;
    f98 = src.f98;
    v9c = src.v9c;
    fb0 = src.fb0;
    vb4 = src.vb4;
    fc8 = src.fc8;
    fcc = src.fcc;
    d0.AssignFrom(src.d0);
    fe4 = src.fe4;
    fe8 = src.fe8;
    fec = src.fec;
    vf0 = src.vf0;
    f104 = src.f104;
    for (int i = 0; i < 8; ++i)  blob108[i] = src.blob108[i];
    for (int i = 0; i < 8; ++i)  b128[i] = src.b128[i];
    for (int i = 0; i < 13; ++i) f130[i] = src.f130[i];
    s164.AssignFrom(src.s164);
    for (int i = 0; i < 5; ++i)  b178[i] = src.b178[i];
    s180.AssignFrom(src.s180);
    v194 = src.v194;
    s1a8.AssignFrom(src.s1a8);
    for (int i = 0; i < 9; ++i)  f1bc[i] = src.f1bc[i];
    for (int i = 0; i < 6; ++i)  a1e0[i] = src.a1e0[i];
    for (int i = 0; i < 7; ++i)  a1f8[i] = src.a1f8[i];
    v214 = src.v214;
    b228 = src.b228;
    f22c = src.f22c;
    f230 = src.f230;
    f234 = src.f234;
    v238 = src.v238;
    f24c = src.f24c;
    f250 = src.f250;
    s254.AssignFrom(src.s254);
    return *this;
}

// @ 0x00f57a30
void cCloudSurfaceCommand::Execute(EA::ArgScript::cArguments_s00f5_7590& args)
{
    const char** argv = args.MainArguments(1);

    SurfaceInfo info;
    info.m00 = 0;
    info.m04 = 0;
    info.m08 = 0;
    info.m0c = 0xffffffff;
    info.m10 = 0xffffffff;
    info.m14 = 0x3f800000;
    info.m18 = 0x3f800000;
    info.m1c = 0;
    info.m20 = 0;
    info.m24 = 0;
    info.m28 = 0x3f800000;
    info.m2c = 0;
    info.m30 = 0;
    info.m34 = 0;
    info.m38 = 0xce6e6b28;
    info.m3c = 0xffffffff;
    info.m40 = 0xffffffff;
    info.m44 = 0;
    info.m48 = 0;
    info.m4c = 0;

    if (args.HasFlag("reset"))
        mState->mSurfaces.clear();

    ParseSurfaceOptions(argv[0], &args, (char*)&info + 4, mState->mParser270);
    mState->mSurfaces.push_back(info);
    mState->mFlags |= 0x1000;
}

// @ 0x00f57ba0
void cCloudEffect_s00f5_7590::Execute(EA::ArgScript::cArguments_s00f5_7590& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 3);

    const char* p = argv[0];
    while (*p) ++p;
    mStr.assign(argv[0], p);

    cCloudDescription_s00f5_7590 tmp;
    mCmd = tmp;
    tmp.~cCloudDescription_s00f5_7590();

    b2c0 = 0;
    b2c1 = 0;
    if (count > 1) {
        const char* inh = (const char*)mOwner->GetInheritedDescription(argv, count, 0x2b);
        if (inh)
            mCmd = *(const cCloudDescription_s00f5_7590*)inh;
    }
    mParser->pv35(this);
}

// @ 0x00f57c50
void ReadDescription(Archive* ar, int /*version*/, cCloudDescription_s00f5_7590* desc)
{
    int tmp;
    ReadInt32(ar, &tmp, 1, 0);
    desc->m08 = (uint32_t)tmp;

    ar->Read(&desc->f0c, 8);
    ReadInt32(ar, &desc->f14, 1, 0);
    ar->Read(&desc->f18, 8);
    ar->Read(&desc->f20, 8);
    ar->Read(&desc->f28, 0xc);
    ar->Read(&desc->f34, 0xc);
    ar->Read(&desc->f40, 8);
    ar->Read(&desc->f48, 0xc);
    ar->Read(&desc->f54, 0xc);
    ReadInt32(ar, &desc->f60, 1, 0);
    ReadVecF(ar, &desc->v64);
    ReadInt32(ar, &desc->f78, 1, 0);
    ReadU32a(ar, &desc->w7c, 1, 0);
    ReadInt32(ar, &desc->f80, 1, 0);
    ReadVecF(ar, &desc->v84);
    ReadInt32(ar, &desc->f98, 1, 0);
    ReadVecF(ar, &desc->v9c);
    ReadInt32(ar, &desc->fb0, 1, 0);
    ReadInt32(ar, &desc->fc8, 1, 0);
    ReadInt32(ar, &desc->fcc, 1, 0);
    ReadVecF(ar, &desc->vb4);
    ReadVecF(ar, &desc->vf0);
    ReadInt32(ar, &desc->f104, 1, 0);
    ReadSubA(ar, &desc->d0);
    ar->Read(&desc->fe4, 0xc);
    ReadBlob(ar, desc->blob108);
    ReadByte(ar, &desc->b128[0], 1);
    ReadByte(ar, &desc->b128[1], 1);
    ReadByte(ar, &desc->b128[2], 1);
    ReadByte(ar, &desc->b128[3], 1);
    ReadByte(ar, &desc->b128[4], 1);
    ReadByte(ar, &desc->b128[5], 1);
    ReadByte(ar, &desc->b128[6], 1);
    ReadByte(ar, &desc->b128[7], 1);
    ReadInt32(ar, &desc->f130[0], 1, 0);
    ar->Read(&desc->f130[1], 0xc);
    ReadInt32(ar, &desc->f130[4], 1, 0);
    ReadInt32(ar, &desc->f130[5], 1, 0);
    ReadInt32(ar, &desc->f130[6], 1, 0);
    ar->Read(&desc->f130[7], 0xc);
    ReadInt32(ar, &desc->f130[10], 1, 0);
    ReadInt32(ar, &desc->f130[11], 1, 0);
    ReadInt32(ar, &desc->f130[12], 1, 0);
    ReadSubB(ar, &desc->s164);
    ReadByte(ar, &desc->b178[0], 1);
    ReadByte(ar, &desc->b178[1], 1);
    ReadByte(ar, &desc->b178[2], 1);
    ReadByte(ar, &desc->b178[3], 1);
    ReadSubA(ar, &desc->s180);
    ReadVecF(ar, &desc->v194);
    ReadSubC(ar, &desc->s1a8);
    ReadInt32(ar, &desc->f1bc[0], 1, 0);
    ReadInt32(ar, &desc->f1bc[1], 1, 0);
    ReadInt32(ar, &desc->f1bc[2], 1, 0);
    ReadInt32(ar, &desc->f1bc[3], 1, 0);
    ReadInt32(ar, &desc->f1bc[4], 1, 0);
    ReadInt32(ar, &desc->f1bc[5], 1, 0);
    ReadInt32(ar, &desc->f1bc[6], 1, 0);
    ar->Read(&desc->f1bc[7], 8);
    ReadU32b(ar, &desc->a1e0[0], 1, 0);
    ReadU32b(ar, &desc->a1e0[2], 1, 0);
    ReadU32b(ar, &desc->a1e0[4], 1, 0);
    ReadSubD(ar, &desc->a1f8[0]);
    ar->Read(&desc->a1f8[4], 0xc);
    ReadSubE(ar, &desc->v238);
    ReadSubF(ar, &desc->s254);
}
