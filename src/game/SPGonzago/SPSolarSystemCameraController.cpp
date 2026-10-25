// src/game/SPGonzago/SPSolarSystemCameraController.cpp -- migrated from slice(s) s01399700, s01020e80, s0101fb40, s01019090, s01018810, s010175b0, s01016540 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSolarSystemCameraController.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPTimer.h"
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern float g_1485720;    // 1.0f
extern float g_13ec4d0;
extern float g_13ebca0;

// ---- items of slice s01016540 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
void* __cdecl   FUN_00b3d470();                         // 0x00b3d470
void* __cdecl   SP_GetUFOSimulator();                   // 0x00ffbe50
float  __cdecl  FUN_01041cd0(float a, float b, float c);  // 0x01041cd0 (ret 0xc)
extern float g_1485720;    // 1.0f
extern float g_13ec4d0;
extern float g_13ebca0;
struct Vec3 { float x, y, z; };
struct Property {
    u8  pad_00[0x12];
    u16 mType_12;                       // +0x12
    float* GetFloat();                  // 0x0041ea70 ret 4
};
static inline char* vpt(void* o) { return *(char**)o; }
static __forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
struct Blk64 { u32 w[16]; };
struct cVarListSerializer {
    u32  mData[0xa14 / 4];
    void Ctor(void* a, void* b, u32 c);      // 0x00692f90 ret 0xc
    void Serialize(void* o);                 // 0x00692900 ret 4
    u8   Read(void* o);                      // 0x00693e10 ret 4
};
void __cdecl EA_IO_WriteUint32(void* stream, void* val, int n, int b); // 0x0093aa70 ret 0x10
void __cdecl EA_IO_ReadInt32(void* stream, void* out, int n, int b);   // 0x0093a780 ret 0x10
struct cSPSimulatorSpaceGame {
    void* GetPlayerInventory();              // 0x00a1ad60 ret 4
};
struct UFOInv {
    void FUN_00c3daa0(float f);              // 0x00c3daa0 ret 4
    void PopToDestination();                 // 0x00c37e60
    void FUN_00c37120();                     // 0x00c37120
    void StartPlayerDeathSequence();         // 0x00c3c520
    void SetPlanetDestination(void* dest);   // 0x00ffc350 ret 0x14
    float mCollisionTimer_540;               // +0x540
    u8    mFlag_74c;                         // +0x74c
};
struct cSPCameraControllerSolarSystem {
    // vtable-using base (cDefaultCameraController) occupies 0x00..0x67
    u8  pad_00[0x68];
    Vec3 mVec_68;                                      // +0x68 (saved/desired)
    Vec3 mVec_74;                                      // +0x74 (current)
    u8   pad_80[4];                                    // 0x80..0x83
    void* mpProperty_84;                               // +0x84 (property manager)
    u8   pad_88[8];                                    // 0x88..0x8f
    float mFloat_90;                                   // +0x90
    u8  pad_94[0x64];                                  // 0x94..0xf7
    Blk64 mBlk_f8;                                     // +0xf8 (0x40 bytes)
    u8   pad_138[4];                                   // 0x138..0x13b
    u8   mFlag_13c;                                    // +0x13c
    u8   mFlag_13d;                                    // +0x13d
    u8   pad_13e[2];                                   // 0x13e..0x13f
    u8   mFlag_140;                                    // +0x140
    u8   pad_141[0x53];                                // 0x141..0x193
    u8   mFlag_194;                                    // +0x194
    u8   pad_195[3];                                   // 0x195..0x197
    u32  mFlags_198;                                   // +0x198

    // members
    void FUN_010170e0();                               // 010170e0
    void FUN_01017170(float f);                        // 01017170 ret 4
    void FUN_010171b0(float f);                        // 010171b0 ret 4
    void FUN_01017200(void* out);                      // 01017200 ret 4
    u32  FUN_01017260();                               // 01017260
    void FUN_01017270(char b);                         // 01017270 ret 4
    void Write(void* stream);                          // 01017290 ret 4
    u8   Read(void* stream);                           // 01017300 ret 4
    float FUN_01017410(int a);                         // 01017410 ret 4
};
// ---- items of slice s01016540 end

// ---- items of slice s010175b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl FUN_01021230();
extern void* __cdecl FUN_00ffbe50();
extern void* __cdecl FUN_00b3d350();
extern void* __cdecl FUN_00c37360();
extern void* __cdecl FUN_00b3d380();
extern void* __cdecl FUN_0067ddd0();
extern void __cdecl FUN_00f47380(void* p);
typedef float f32;
#define VT(p) (*(void***)(p))
struct cSPVector3_s0101_75b0 {
    union { f32 x; u32 ux; };
    union { f32 y; u32 uy; };
    union { f32 z; u32 uz; };
};
struct TableEntry { f32 key; f32 value; };
struct Table { TableEntry* begin; TableEntry* end; };
extern f32 g16dd3d0;
extern f32 g16dd3b4;
extern f32 g16dd360;
extern f32 g16dd35c;
extern f32 g16dd368;
extern f32 g16dd364;
extern f32 g16dd374;
extern f32 g16dd384;
extern f32 g16dd394;
extern f32 g16dd398;
extern f32 g16dd39c;
extern f32 g16dd3a0;
extern f32 g16dd3a4;
extern f32 g16dd3a8;
extern f32 g16dd3e8;
extern f32 g16dd3ec;
extern f32 g16dd3f8;
extern f32 g16dd414;
extern f32 g16dd418;
extern u8  g16dd3fc;
extern u8  g16dd441;
extern u32 g16dda78;
extern f32 g16dda74;
extern f32 g16dda70;
extern Table g16dda14;
extern Table g16dda28;
extern f32 g15b6d88;
extern f32 g15b6d8c;
class COps {
public:
    bool FUN_00c8b800();
    f32 FUN_00b7e4d0();
    f32 FUN_00a0ab60();
    f32 FUN_00c37120();
    void FUN_00b815a0(void* out, void* dir);
    void* FUN_00a1ad60();
    u32 FUN_01021080();
    bool FUN_01044920();
};
#define MOPS(p) ((COps*)(p))
extern void __cdecl FUN_00571db0(void* h, u32 a, u32 b, u32 c, u32 d);
extern f32 __cdecl FUN_010433e0(void* a, u32 b, f32 c, u32 d);
extern f32 __cdecl FUN_01043310(void* a, u32 b, f32 c, u32 d);
extern "C" f32 __cdecl sqrtf(f32 x);
struct cGameTimeManager {
    u8 pad00[0x48];
    u8 m48;                          // +0x48
};
class cPlayerInventory {
public:
    u8 pad00[0x34];
    void* m34;                       // +0x34  embedded object (vtable first)
    u8 pad38[0x74c - 0x38];
    u8 m74C;                         // +0x74c
    u8 pad74D[0x750 - 0x74D];
    f32 m750[3];                     // +0x750
};
class cSPSpacePlanetCameraController {
public:
    u8 pad00[0x14];
    void* mPathSource;               // +0x14
    u8 pad18[0x60 - 0x18];
    f32 m60;                         // +0x60
    u8 pad64[0x68 - 0x64];
    union { f32 f; u8 b; } m68;      // +0x68
    f32 kPlanetFarZoomHeight;        // +0x6c
    f32 m70;                         // +0x70
    f32 m74;                         // +0x74  planet radius
    f32 m78;                         // +0x78
    f32 m7C;                         // +0x7c
    f32 m80;                         // +0x80
    f32 m84;                         // +0x84
    u8 pad88[0x8c - 0x88];
    f32 m8C;                         // +0x8c
    f32 m90;                         // +0x90
    u32 m94;                         // +0x94
    u32 m98;                         // +0x98
    u32 m9C;                         // +0x9c
    u32 mA0;                         // +0xa0
    u32 mA4;                         // +0xa4
    u32 mA8;                         // +0xa8
    f32 mAC;                         // +0xac
    f32 mB0;                         // +0xb0
    u32 mB4;                         // +0xb4
    u32 mB8;                         // +0xb8
    u32 mBC;                         // +0xbc
    u32 mC0;                         // +0xc0
    u32 mC4;                         // +0xc4
    u32 mC8;                         // +0xc8
    u8 padCC[0xd0 - 0xcc];
    f32 mD0;                         // +0xd0
    u32 mD4;                         // +0xd4
    u32 mD8;                         // +0xd8
    u32 mDC;                         // +0xdc
    u32 mE0;                         // +0xe0
    u32 mE4;                         // +0xe4
    u32 mE8;                         // +0xe8
    f32 mEC;                         // +0xec
    f32 mF0;                         // +0xf0
    f32 mF4;                         // +0xf4
    u8 padF8[0x138 - 0xf8];
    u32 m138;                        // +0x138
    u8 m13C;                         // +0x13c
    u8 m13D;                         // +0x13d
    u8 m13E;                         // +0x13e
    u8 m13F;                         // +0x13f
    u8 m140;                         // +0x140
    u8 pad141[0x144 - 0x141];
    u32 m144;                        // +0x144
    u32 m148;                        // +0x148
    u32 m14C;                        // +0x14c
    u8 pad150[0x15c - 0x150];
    u32 m15C;                        // +0x15c
    u32 m160;                        // +0x160
    u32 m164;                        // +0x164
    u8 pad168[0x194 - 0x168];
    u8 m194;                         // +0x194
    u8 pad195[0x198 - 0x195];
    u32 m198;                        // +0x198
    u8 pad19C[0x228 - 0x1A0];

    f32 FUN_01017790(bool a, bool b);
    void FUN_01017910();
    void* FUN_01017b70();
    f32 FUN_01017bb0();
    f32 FUN_01017d30();
    f32 FUN_01017e80();
    bool FUN_01017f20();
};
class cEditorTraceObject {
public:
    u32 mVtbl0;                      // +0x00
    u32 mVtbl4;                      // +0x04
    u32 mVtbl8;                      // +0x08
    u8 pad0C[0x10 - 0x0c];
    void* m10;                       // +0x10
    void* m14;                       // +0x14
    u32 m18;                         // +0x18
    u32 m1C;                         // +0x1c
    u32 m20;                         // +0x20
    u32 m24;                         // +0x24
    u32 m28;                         // +0x28
    u8 pad2C[0x48 - 0x2c];
    void* m48;                       // +0x48

    void FUN_01018060();
};
struct ArrayHeader { u32 count; };
// ---- items of slice s010175b0 end

// ---- items of slice s01018810 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
};
struct Quaternion {
    float x, y, z, w;
};
Vector3* QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0 (cdecl)
// ---- items of slice s01018810 end

// ---- items of slice s01019090 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gPlanetCamSnapDistance;       // 0x016dd410 (added to the planet radius)
inline Vector3 operator-(const Vector3& a, const Vector3& b) { Vector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }
inline float MaxSS(float a, float b) { return (a > b) ? a : b; }
inline float MinSS(float a, float b) { return (a < b) ? a : b; }
Vector3*    RotateTowards(Vector3* out, const Vector3* from, const Vector3* to, float t); // 0x00b0fd00
float       PlanetRadiusAt(const Vector3* p);                                         // 0x00c375d0
extern const Vector3    kUFOForward;       // 0x015b6de8
namespace SP {
class cGameTimeManager_s0101_9090 { public:
    uint32_t pad0[0x48 / 4];
    uint8_t  mFlags;   // +0x48, bit 0 = paused
};
}
namespace SP {
cGameTimeManager_s0101_9090* GameTimeManager();       // 0x00b3d380
}
namespace SP {
struct IGameInputManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool IsRotateInputActive(int arg);   // +0x18
};
}
namespace SP {
IGameInputManager* GameInputManager();     // 0x00b3d250
}
namespace SP {
class cSpatialObject_s0101_9090 { public:   // the UFO's spatial base (cSPGameDataUFO + 0x34)
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3*    GetPosition();      // +0x2c
    virtual const Quaternion* GetOrientation();   // +0x30
};
}
namespace SP {
class cSPGameDataUFO_s0101_9090 { public:
    uint32_t pad0[0x34 / 4];
    cSpatialObject_s0101_9090 mSpatialStorage;                 // +0x34 (used through Spatial())
    float GetMaxGroundSpeed();                      // 0x00c38840
    cSpatialObject_s0101_9090* Spatial() { return reinterpret_cast<cSpatialObject_s0101_9090*>(reinterpret_cast<char*>(this) + 0x34); }
    template <typename T> T& At(int off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off); }
};
}
namespace SP {
class cSPSimulatorSpaceGame_s0101_9090 { public:
    cSPGameDataUFO_s0101_9090* GetPlayerInventory();           // 0x00a1ad60
};
}
namespace SP {
cSPSimulatorSpaceGame_s0101_9090* GetUFOSimulator();           // 0x00ffbe50
}
namespace SP {
class cSPSpacePlanetCameraController_s0101_9090 {
public:
    void UpdateYaw(float seconds);                                                       // 0x01019090
    void UpdateCameraPitchRotation(float seconds, float pitch, Vector3* lookAt, Vector3* eye);  // 0x01019950

    // ---- retail layout (offsets verified against 0x0101d130 / 0x01019090 / 0x01019950) ----
    uint32_t pad00[0x78 / 4];
    float    mPitch;                   // +0x78 (camera pitch angle)
    uint32_t pad7c[(0x90 - 0x7c) / 4];
    float    mYawInput;                // +0x90 (yaw rotation input, radians)
    Vector3  mEyeDirection;            // +0x94
    uint32_t padA0[(0xcc - 0xa0) / 4];
    bool     mZooming;                 // +0xcc
    uint8_t  padCD[(0x13c - 0xcd)];
    bool     mApproachFollow;          // +0x13c
    uint8_t  pad13d[(0x198 - 0x13d)];
    uint32_t mFlags;                   // +0x198 (bit 0 = pitch tracking, bit 1 = yaw follow)
};
}
static __forceinline void RotateEyeAroundLookAt(float angle, const Vector3* lookAt, Vector3* eye)
{
    Vector3 ax;
    ax.x = lookAt->y * eye->z - lookAt->z * eye->y;
    ax.y = lookAt->z * eye->x - lookAt->x * eye->z;
    ax.z = eye->y * lookAt->x - lookAt->y * eye->x;
    float axInv = 1.0f / sqrtf(ax.y * ax.y + (ax.z * ax.z + ax.x * ax.x));
    float half = angle * 0.5f;
    Vector3 an;
    an.x = axInv * ax.x;
    an.y = axInv * ax.y;
    an.z = axInv * ax.z;
    float s = sinf(half);
    Quaternion q;
    q.x = s * an.x;
    q.y = s * an.y;
    q.z = s * an.z;
    float c = cosf(half);
    volatile float cMem = c;    // the original rounds cos() to float before the final multiply
    Vector3 toEye;
    toEye.x = eye->x - lookAt->x;
    toEye.y = eye->y - lookAt->y;
    toEye.z = eye->z - lookAt->z;
    volatile float qInvMem = 1.0f / sqrtf(q.y * q.y + (q.z * q.z + (q.x * q.x + c * c)));
    float qInv = qInvMem;
    Quaternion qn;
    qn.x = qInv * q.x;
    qn.y = qInv * q.y;
    qn.z = qInv * q.z;
    qn.w = qInv * cMem;
    Vector3 rotated;
    const Vector3* r = QuaternionRotate(&rotated, &toEye, &qn);
    Vector3 origin = *lookAt;
    eye->x = r->x + origin.x;
    eye->y = r->y + origin.y;
    eye->z = r->z + origin.z;
}
// ---- items of slice s01019090 end

// ---- items of slice s0101fb40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_016dd34c;
extern float g_016dd350;
extern float g_016dd354;
extern float g_016dd358;
extern float g_016dd35c;
extern float g_016dd360;
extern float g_016dd364;
extern float g_016dd368;
extern float* g_016dd36c;
extern int g_016dd370;
extern float g_016dd374;
extern float g_016dd378;
extern float g_016dd37c;
extern float g_016dd380;
extern float g_016dd384;
extern bool g_016dd388;
extern bool g_016dd389;
extern bool g_016dd38a;
extern bool g_016dd38b;
extern float g_016dd38c;
extern float g_016dd390;
extern float g_016dd394;
extern float g_016dd398;
extern float g_016dd39c;
extern float g_016dd3a0;
extern float g_016dd3a4;
extern float g_016dd3a8;
extern float* g_016dd3ac;
extern int g_016dd3b0;
extern float g_016dd3b4;
extern float g_016dd3b8;
extern float g_016dd3bc;
extern float g_016dd3c0;
extern float g_016dd3c4;
extern float g_016dd3c8;
extern float g_016dd3cc;
extern float g_016dd3d0;
extern float g_016dd3d4;
extern float g_016dd3d8;
extern float g_016dd3dc;
extern float g_016dd3e0;
extern float g_016dd3e4;
extern float g_016dd3e8;
extern float g_016dd3ec;
extern float g_016dd3f0;
extern float g_016dd3f4;
extern float g_016dd3f8;
extern bool g_016dd3fc;
extern bool g_016dd3fe;
extern bool g_016dd3ff;
extern float g_016dd400;
extern float g_016dd404;
extern float g_016dd408;
extern float g_016dd40c;
extern float g_016dd410;
extern float g_016dd414;
extern float g_016dd418;
extern float g_016dd41c;
extern float g_016dd420;
extern float g_016dd424;
extern float g_016dd428;
extern float g_016dd42c;
extern float g_016dd430;
extern float g_016dd434;
extern float g_016dd438;
extern float g_016dd43c;
extern bool g_016dd440;
extern bool g_016dd441;
struct Property_s0101_fb40 {
    char pad0[0x10];
    unsigned char flags;   // +0x10: bits 0x30 = value stored indirectly
    char pad1;
    short type;            // +0x12: 1 = bool, 0xd = float
    float* __thiscall GetFloat();   // 0x41ea70
    bool*  __thiscall GetBool();    // 0x41e920
};
struct IPropertyList {
    virtual void v0();
    virtual void Release();                                  // +0x04
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s0101_fb40** out);   // +0x24
};
struct IPropertyManager {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void GetPropertyList(uint32_t a, uint32_t b, IPropertyList** out);  // +0x2c
};
struct PairIF { float key; float value; };
struct VecPairIF {
    PairIF* begin; PairIF* end; PairIF* cap;
    void __thiscall insertN(PairIF* pos, unsigned n, const PairIF& v);   // 0x479830
    void __thiscall erase(PairIF* first, PairIF* last);                  // 0x530c80
    void eraseInline(PairIF* first, PairIF* last) { end += -(last - first); }
};
namespace SP {
IPropertyManager* __cdecl PropertyManager();                                       // 0x67de30
}
namespace SP {
void __cdecl GetPropertyAsFloatArray(IPropertyList*, uint32_t, float**, int*);     // 0x6a08b0
}
namespace SP {
void __cdecl GetPropertyAsPairArray(IPropertyList*, uint32_t, int*, PairIF**);     // 0x6a0920
}
extern VecPairIF g_016dda14, g_016dda28;
#define READ_BOOL(g, def, id) \
    { Property_s0101_fb40* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 1) g = *prop->GetBool(); }
#define READ_F(g, def, id) \
    { Property_s0101_fb40* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 0xd) g = *prop->GetFloat(); }
#define READ_FI(g, def, id) \
    { Property_s0101_fb40* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 0xd) { \
        float* pf = (float*)prop; \
        if (prop->flags & 0x30) pf = *(float**)prop; \
        g = *pf; } }
#define READ_DEG(g, def, id) \
    { Property_s0101_fb40* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 0xd) g = *prop->GetFloat(); \
    g = g * 0.017453292f; }
namespace SP {
class cDefaultCameraController {
public:
    uint32_t pad[5];
    IPropertyList* mConfig;   // +0x14
    // @ 0x0101FB40
    void ReadProperties();
};
}
// ---- items of slice s0101fb40 end

// ---- items of slice s01020e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_0067de30();                        // SP::PropertyManager
struct Ext {
    void* FUN_0101fb40();
    void* FUN_00c70f90(int);                 // float
    void  FUN_01017bb0();
    void* FUN_00c70c00();
    void  FUN_00c82f00();
    void* FUN_00c71e70();
    void* FUN_00c8b360();
    void  FUN_00c8b800();
    void* FUN_00c31730();
    void* FUN_00ba9370();
    void  FUN_00bb3750();
    void  FUN_00bb59b0();
    void* FUN_00b8de30();
void  FUN_00b3d2a0i(int);
void  FUN_00ad92d0();
    void* FUN_00ff3f00();
    void  FUN_0140efa0();
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }
struct Cam { char f20e80(int msg, int* p); void f20fc0(); void f21020(); };
// ---- items of slice s01020e80 end

// ---- items of slice s01399700 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct PropDesc {
    const char* name;    // +0x00
    uint        hash;    // +0x04
    uint        offset;  // +0x08
    uint        f0c;     // +0x0c  (uninitialised in the original)
    uint        f10;     // +0x10  (uninitialised in the original)
    uint        f14;     // +0x14  (uninitialised in the original)
    void*       f18;     // +0x18
    void*       f1c;     // +0x1c
    void*       f20;     // +0x20
    void*       f24;     // +0x24
    void*       f28;     // +0x28
    void*       f2c;     // +0x2c
    void*       f30;     // +0x30
    void*       f34;     // +0x34
    void*       f38;     // +0x38
};
extern PropDesc g_props_0c40[11];   // 0x15b6e28  (stride 0x3c)
void FUN_00692ca0();
void FUN_006930b0();
void FUN_006930f0();
void FUN_00572810();
void FUN_00694fc0();
void FUN_00695010();
void FUN_00ac88c0();
void FUN_00ac88f0();
void FUN_00acbb80();
void FUN_00acbba0();
void FUN_00b1fbf0();
void FUN_00b6e3a0();
// ---- items of slice s01399700 end

// @ 0x01017150
void FUN_01017150()
{
    cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)SP_GetUFOSimulator();
    UFOInv* inv = (UFOInv*)sim->GetPlayerInventory();
    inv->FUN_00c37120();
}

// @ 0x01017290
void cSPCameraControllerSolarSystem::Write(void* stream)
{
    void* p = (void*)(**(int(__thiscall**)(void*))(vpt(stream) + 0x20))(stream);
    u32 tag = 0x303154cc;
    void* io = (void*)(**(int(__thiscall**)(void*))(vpt(p) + 0x18))(p);
    EA_IO_WriteUint32(io, &tag, 1, 0);
    cVarListSerializer buf;
    buf.Ctor(this, (void*)0x15b6e28, 0x1a80d26);
    buf.Serialize(stream);
}

// @ 0x01017300
u8 cSPCameraControllerSolarSystem::Read(void* stream)
{
    cVarListSerializer buf;
    u32 tmp;
    void* p = (void*)(**(int(__thiscall**)(void*))(vpt(stream) + 0x20))(stream);
    void* io = (void*)(**(int(__thiscall**)(void*))(vpt(p) + 0x18))(p);
    EA_IO_ReadInt32(io, &tmp, 1, 0);
    buf.Ctor(this, (void*)0x15b6e28, 0x1a80d26);
    u8 ok = buf.Read(stream);
    if ((**(u32(__thiscall**)(void*))(vpt(stream) + 0x3c))(stream) < 0x220001) {
        mVec_74 = mVec_68;
    }
    return ok;
}

// @ 0x01017390
void FUN_01017390()
{
    u8* p = (u8*)FUN_00b3d470() + 0xc4;
    if (*(int*)p == 0)
        return;
    u8* p2 = (u8*)FUN_00b3d470() + 0xc4;
    void* q = *(void**)p2;
    (**(void(__thiscall**)(void*, int))(vpt(q) + 0xc))(q, 1);
    u8* base = (u8*)FUN_00b3d470();
    void*& slot = *(void**)(base + 0xc4);
    void* r = slot;
    if (r == 0)
        return;
    slot = 0;
    (**(void(__thiscall**)(void*))(vpt(r) + 4))(r);
}

// @ 0x01017410
float cSPCameraControllerSolarSystem::FUN_01017410(int a)
{
    float f0 = g_1485720;      // property 0x195e020
    void* prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e020, &out) &&
            out->mType_12 == 0xd)
            f0 = *out->GetFloat();
    }
    float f1 = g_13ec4d0;      // property 0x195e021
    prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e021, &out) &&
            out->mType_12 == 0xd)
            f1 = *out->GetFloat();
    }
    float f2 = g_1485720;      // property 0x195e022
    prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e022, &out) &&
            out->mType_12 == 0xd)
            f2 = *out->GetFloat();
    }
    float f3 = g_1485720;      // property 0x195e023
    prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e023, &out) &&
            out->mType_12 == 0xd)
            f3 = *out->GetFloat();
    }
    float r = FUN_01041cd0(f0, f1, *(float*)&a);
    r = Clamp(r, 0.0f, 1.0f);
    return ((f3 - f2) * r + f2) * g_13ebca0;
}

// @ 0x010175b0
f32 __stdcall FUN_010175b0(int mode, f32 value)
{
    f32 lo = g16dd3d0;
    f32 hi = g16dd3b4;
    Table* table;
    if (mode == 1) {
        if (!MOPS(FUN_01021230())->FUN_00c8b800()) {
            f32 t = (value - lo) / (hi - lo);
            if (t < 0.0f)
                t = 0.0f;
            if (t > 1.0f)
                t = 1.0f;
            if ((g16dda78 & 1) == 0) {
                g16dda78 = g16dda78 | 1;
                g16dda74 = 0.08726646f;
            }
            if ((g16dda78 & 2) == 0) {
                g16dda78 = g16dda78 | 2;
                g16dda70 = 0.87266463f;
            }
            return (g16dda70 - g16dda74) * t + g16dda74;
        }
        table = &g16dda14;
    } else {
        table = &g16dda28;
    }

    TableEntry* b = table->begin;
    int n = (int)(table->end - b);
    if (n <= 0)
        return 0.0f;

    f32 v = value;
    if (v < b[0].key)
        v = b[0].key;
    if (v > b[n - 1].key)
        v = b[n - 1].key;

    TableEntry* lower = 0;
    TableEntry* upper = 0;
    for (int i = 0; i < n; i++) {
        TableEntry* e = &b[i];
        if (v <= e->key) {
            if (e->key <= v)
                return e->value;
            if (upper == 0 || e->key < upper->key)
                upper = e;
        } else {
            if (lower == 0 || e->key > lower->key)
                lower = e;
        }
    }
    if (lower != 0 && upper != 0)
        return lower->value + (upper->value - lower->value) *
               ((v - lower->key) / (upper->key - lower->key));
    return 0.0f;
}

// @ 0x01017790
f32 cSPSpacePlanetCameraController::FUN_01017790(bool a, bool b)
{
    u32 ctx = MOPS(this)->FUN_01021080();
    f32 high;
    f32 low;
    if (ctx == 1) {
        if (!a) {
            high = g16dd3a8;
            low = g16dd3a4;
        } else if (!b) {
            high = g16dd398;
            low = g16dd394;
        } else {
            high = g16dd3a0;
            low = g16dd39c;
        }
    } else {
        if (!a) {
            high = g16dd368;
            low = g16dd364;
        } else {
            high = g16dd360;
            low = g16dd35c;
        }
    }

    f32 lo = 0.0f;
    if (ctx == 1)
        lo = g16dd3d0;
    else if (ctx == 2)
        lo = g16dd384;
    f32 hi = 0.0f;
    if (ctx == 1)
        hi = g16dd3b4;
    else if (ctx == 2)
        hi = g16dd374;

    f32 t = (this->m68.f - lo) / (hi - lo);
    t = t < lo ? lo : t;
    t = t > hi ? hi : t;
    return high + (low - high) * t;
}

// @ 0x010178e0
cSPVector3_s0101_75b0* __stdcall FUN_010178e0(cSPVector3_s0101_75b0* out)
{
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    cSPVector3_s0101_75b0* pos = (cSPVector3_s0101_75b0*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
    out->x = pos->x;
    out->y = pos->y;
    out->z = pos->z;
    return out;
}

// @ 0x01017b70
void* cSPSpacePlanetCameraController::FUN_01017b70()
{
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    if (inv->m74C != 0) {
        cGameTimeManager* tm = (cGameTimeManager*)FUN_00b3d380();
        if ((tm->m48 & 1) == 0)
            return inv->m750;
    }
    return ((void* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
}

// @ 0x01017bb0
f32 cSPSpacePlanetCameraController::FUN_01017bb0()
{
    f32 l18 = MOPS(FUN_00c37360())->FUN_00a0ab60();
    f32 l1c = this->m74;

    cPlayerInventory* invA = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    cPlayerInventory* invB = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();

    f32* pos;
    if (invB->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
        pos = invB->m750;
    else
        pos = (f32*)((f32* (__thiscall*)(void*))VT(&invB->m34)[0x2c / 4])(&invB->m34);

    f32 dist = sqrtf(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]) - l1c;
    f32 gap = MOPS(invA)->FUN_00c37120() - l1c;

    f32* minPtr = &gap;
    if (dist <= gap)
        minPtr = &dist;
    f32* maxPtr = &gap;
    if (gap <= dist)
        maxPtr = &dist;

    f32 base = g15b6d88 * l18;
    f32 v = *minPtr;
    if (v < base)
        v = base;
    if (v > l18)
        v = l18;
    f32 t = (v - base) / (l18 - base);
    return (*maxPtr - dist) * (((2.7f - (t + t)) * t) * t) + dist;
}

// @ 0x01017ce0
void __stdcall FUN_01017ce0(u32 unused, cSPVector3_s0101_75b0* out)
{
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    cSPVector3_s0101_75b0* pos;
    if (inv->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
        pos = (cSPVector3_s0101_75b0*)inv->m750;
    else
        pos = (cSPVector3_s0101_75b0*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);

    out->ux = pos->ux;
    out->uy = pos->uy;
    out->uz = pos->uz;
}

// @ 0x01017d30
f32 cSPSpacePlanetCameraController::FUN_01017d30()
{
    f32 res = this->m60;
    if (this->m140 != 0 && g16dd3fc == 0) {
        f32 a = MOPS(FUN_00b3d350())->FUN_00b7e4d0() + g16dd3e8;
        f32 b = MOPS(FUN_00c37360())->FUN_00a0ab60();
        f32 c = MOPS(FUN_00b3d350())->FUN_00b7e4d0();
        f32 d = (a - (c + b)) / (((g16dd414 + g16dd418) * 0.5f) * g16dd3f8);
        if (this->m194 != 0)
            d = -d;
        res = d;
    }
    return res;
}

// @ 0x01017dd0
cSPVector3_s0101_75b0* __stdcall FUN_01017dd0(cSPVector3_s0101_75b0* out)
{
    void* planet = FUN_00b3d350();
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();

    if (planet != 0) {
        cSPVector3_s0101_75b0* pos;
        if (inv->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
            pos = (cSPVector3_s0101_75b0*)inv->m750;
        else
            pos = (cSPVector3_s0101_75b0*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
        MOPS(planet)->FUN_00b815a0(out, pos);
        return out;
    }

    cSPVector3_s0101_75b0* pos;
    if (inv->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
        pos = (cSPVector3_s0101_75b0*)inv->m750;
    else
        pos = (cSPVector3_s0101_75b0*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
    out->x = pos->x;
    out->y = pos->y;
    out->z = pos->z;
    return out;
}

// @ 0x01017e80
f32 cSPSpacePlanetCameraController::FUN_01017e80()
{
    bool flag = MOPS(this)->FUN_01044920();
    f32 a = MOPS(FUN_00b3d350())->FUN_00b7e4d0();
    f32 c = g16dd3ec + a;
    f32 b = a + g16dd3e8;
    if (flag) {
        if (this->m13D != 0)
            return b + 1.0f;
        if (this->m13E != 0) {
            if (this->FUN_01017d30() < 0.0f)
                return b;
        }
    }
    return c;
}

// @ 0x01017f20
bool cSPSpacePlanetCameraController::FUN_01017f20()
{
    if (g16dd441 != 0)
        return true;

    if (this->m13D != 0) {
        f32 h = MOPS(FUN_00b3d350())->FUN_00b7e4d0() + g16dd3e8;
        f32 v = ((f32 (__thiscall*)(void*))VT(this)[0x60 / 4])(this);
        if (h > v)
            return false;
    }

    f32 ref = this->FUN_01017bb0();
    u32 arg;
    switch (this->m138) {
    case 3:
        arg = 0x6046db4;
        break;
    case 4:
        arg = 0x6046db5;
        break;
    default:
        arg = 0x195a060;
        break;
    }

    f32 v1 = FUN_010433e0(this->mPathSource, arg, ref, 0);
    void* src = this->mPathSource;
    f32 v2 = FUN_01043310(src, arg, v1, 1);
    return v2 - this->kPlanetFarZoomHeight < g15b6d8c;
}

// @ 0x01017fe0
void __cdecl FUN_01017fe0()
{
    void** slot = (void**)((u8*)FUN_00b3d470() + 0xc4);
    if (*slot == 0) {
        void* effects = FUN_0067ddd0();
        void** slot2 = (void**)((u8*)FUN_00b3d470() + 0xc4);
        void* old = *slot2;
        if (old != 0) {
            *slot2 = 0;
            ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
        }
        ((void (__thiscall*)(void*, u32, u32, void**))VT(effects)[0x2c / 4])(effects, 0x44059911, 0, slot2);
    }

    void** slot3 = (void**)((u8*)FUN_00b3d470() + 0xc4);
    if (*slot3 != 0) {
        void** slot4 = (void**)((u8*)FUN_00b3d470() + 0xc4);
        void* obj = *slot4;
        ((void (__thiscall*)(void*, u32))VT(obj)[8 / 4])(obj, 0);
    }
}

// @ 0x01018060
void cEditorTraceObject::FUN_01018060()
{
    void* arr = this->m48;
    if (arr != 0) {
        ArrayHeader* hdr = ((ArrayHeader*)arr) - 1;
        if (hdr->count != 0)
            FUN_00f47380(arr);
    }

    u32 h = this->m18;
    if (h != 0) {
        this->m18 = 0;
        FUN_00571db0((void*)h, this->m1C, this->m20, this->m24, this->m28);
    }

    void* p14 = this->m14;
    if (p14 != 0)
        ((void (__thiscall*)(void*))VT(p14)[4 / 4])(p14);
    void* p10 = this->m10;
    if (p10 != 0)
        ((void (__thiscall*)(void*))VT(p10)[4 / 4])(p10);

    this->mVtbl8 = 0x13ec458;
    this->mVtbl4 = 0x13eb394;
    this->mVtbl0 = 0x13eb938;
}

// @ 0x01018810
void __stdcall ConeTangentSolve(const float* dir, const float* axis, float R, float k, float ang, float off, float* outA, float* outB, float* outC) // 0x01018810
{
    float dl = 1.0f / sqrtf(dir[2] * dir[2] + (dir[1] * dir[1] + dir[0] * dir[0]));
    float nz = dir[2] * dl;
    float ny = dir[1] * dl;
    float nx = dir[0] * dl;

    const float bx = axis[0], by = axis[1], bz = axis[2];   // the original loads the axis once, up front
    float half = ang * 0.5f - off;
    float rx = ny * R;
    float rz = nz * R;
    float rxx = nx * R;
    float cosv = cosf(half);
    float d = R - sinf(half) * k;

    float t = R * R - d * d;
    float r = (t > 0.0f) ? t : 0.0f;
    float sq = sqrtf(r);

    float invR = 1.0f / R;
    float tx = (nx * d + bx * sq) * invR;
    float tz = invR * (nz * d + bz * sq);
    float ty = invR * (ny * d + by * sq);

    float cx = bz * ny - by * nz;
    float cy = bx * nz - bz * nx;
    float cz = by * nx - ny * bx;

    float ux = cz * ty - cy * tz;
    float uy = cx * tz - tx * cz;
    float uz = tx * cy - cx * ty;

    float m = ((ux * rxx + uz * rz) + uy * rx) + cosv * k;
    double cmp = cos(1.6231561917811632);

    float px = tx * R + ux * m;
    outA[0] = px;
    float lx = px - rxx;
    float py = ty * R + uy * m;
    outA[1] = py;
    float ly = py - rx;
    float pz = tz * R + uz * m;
    outA[2] = pz;
    float lz = pz - rz;

    outB[0] = rxx;
    outB[1] = rx;
    outB[2] = rz;
    float c = ((lx * bx + bz * lz) + by * ly) / k;
    outC[0] = rxx;
    outC[1] = rx;
    outC[2] = rz;

    if (!((double)c > cmp)) {
        float ax = outA[0], ay = outA[1], az = outA[2];
        float d1x = outB[0] - ax, d1z = outB[2] - az, d1y = outB[1] - ay;
        float d2x = dir[0] - ax, d2y = dir[1] - ay, d2z = dir[2] - az;
        float i1 = 1.0f / sqrtf(d1y * d1y + (d1z * d1z + d1x * d1x));
        float i2 = 1.0f / sqrtf(d2y * d2y + (d2z * d2z + d2x * d2x));
        if (((i2 * d2z) * (i1 * d1z) + (i2 * d2y) * (i1 * d1y)) + (i1 * d1x) * (i2 * d2x) < cosv) {
            double px2 = dir[0], py2 = dir[1], pz2 = dir[2];
            float f = (float)(sqrt(pz2 * pz2 + (py2 * py2 + px2 * px2)) -
                              (double)R / ((double)ny * (double)ty + ((double)tz * (double)nz + (double)tx * (double)nx)));
            outA[0] = ax + nx * f;
            outA[1] = ay + ny * f;
            outA[2] = az + f * nz;
            outB[0] = outB[0] + nx * f;
            outB[1] = ny * f + outB[1];
            outB[2] = f * nz + outB[2];
            return;
        }
    } else {
        if (c <= -1.0f) c = -1.0f;
        if (1.0f <= c) c = 1.0f;
        float qi = 1.0f / sqrtf(cy * cy + (cz * cz + cx * cx));
        Vector3 axn;
        axn.x = qi * cx;
        axn.y = qi * cy;
        axn.z = qi * cz;
        double hang = ((double)(float)acos(c) - 1.6231562f) * 0.5;
        float sh = (float)sin(hang);
        float ch = (float)cos(hang);
        Quaternion q;
        q.x = sh * axn.x;
        q.y = sh * axn.y;
        q.z = sh * axn.z;
        q.w = ch;
        Vector3 lv;
        lv.x = lx;
        lv.y = ly;
        lv.z = lz;
        Vector3 res;
        Vector3* rr = QuaternionRotate(&res, &lv, &q);
        float qx = rr->x + rxx;
        float qy = rr->y + rx;
        float qz = rr->z + rz;
        outA[0] = qx;
        outA[1] = qy;
        outA[2] = qz;
        float e1y = dir[1] - qy, e1x = dir[0] - qx, e1z = dir[2] - qz;
        float e2x = outB[0] - qx, e2z = outB[2] - qz, e2y = outB[1] - qy;
        float i2 = 1.0f / sqrtf(e2y * e2y + (e2z * e2z + e2x * e2x));
        float len = sqrtf(e1y * e1y + (e1z * e1z + e1x * e1x));
        float i1 = 1.0f / len;
        float dot = ((i1 * e1z) * (i2 * e2z) + (i1 * e1y) * (i2 * e2y)) + (i1 * e1x) * (i2 * e2x);
        if (dot < cosv) {
            float pl = sqrtf(qy * qy + (qz * qz + qx * qx));
            float pi = 1.0f / pl;
            float s = (len * cosv - dot * len) + pl;
            outA[0] = (pi * qx) * s;
            outA[1] = (pi * qy) * s;
            outA[2] = (pi * qz) * s;
            return;
        }
    }
}

// @ 0x01019090
void SP::cSPSpacePlanetCameraController_s0101_9090::UpdateYaw(float seconds)
{
    SP::cSPGameDataUFO_s0101_9090* ufo = SP::GetUFOSimulator()->GetPlayerInventory();
    SP::cSPGameDataUFO_s0101_9090* posUfo = SP::GetUFOSimulator()->GetPlayerInventory();

    const Vector3* pPos;
    if (posUfo->At<bool>(0x74c) && !(SP::GameTimeManager()->mFlags & 1))
        pPos = &posUfo->At<Vector3>(0x750);
    else
        pPos = posUfo->Spatial()->GetPosition();

    // Planet normal at the camera anchor.
    Vector3 p;
    p.x = pPos->x;
    p.y = pPos->y;
    p.z = pPos->z;
    float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
    Vector3 n;
    n.x = p.x * inv;
    n.y = p.y * inv;
    n.z = p.z * inv;

    // Keep the eye direction tangent: dir = normalize(p x (eyeDir x n)).
    Vector3& dir = mEyeDirection;
    Vector3 side;
    side.x = n.z * dir.y - n.y * dir.z;
    side.y = dir.z * n.x - n.z * dir.x;
    side.z = n.y * dir.x - dir.y * n.x;
    Vector3 t;
    t.x = side.z * p.y - side.y * p.z;
    t.y = p.z * side.x - side.z * p.x;
    t.z = side.y * p.x - p.y * side.x;
    float tInv = 1.0f / sqrtf(t.x * t.x + t.z * t.z + t.y * t.y);
    t.x = tInv * t.x;
    t.y = t.y * tInv;
    t.z = t.z * tInv;
    dir = t;

    if (!(SP::GameTimeManager()->mFlags & 1) && !(mFlags & 2))
    {
        // Follow the UFO's heading projected onto the tangent plane.
        Vector3 fwd;
        const Vector3* f = QuaternionRotate(&fwd, &kUFOForward, ufo->Spatial()->GetOrientation());
        float d = (f->z * n.z + f->y * n.y) + f->x * n.x;
        Vector3 h;
        h.x = f->x - d * n.x;
        h.y = f->y - n.y * d;
        h.z = f->z - n.z * d;
        float hInv = 1.0f / sqrtf(h.x * h.x + h.z * h.z + h.y * h.y + 1e-08f);
        h.x = hInv * h.x;
        h.y = hInv * h.y;
        h.z = hInv * h.z;
        dir = h;
    }
    else if (!(SP::GameTimeManager()->mFlags & 1) && (mFlags & 2) && (mApproachFollow || ufo->At<bool>(0x74c)))
    {
        mApproachFollow = true;
        Vector3 fwd;
        const Vector3* f = QuaternionRotate(&fwd, &kUFOForward, ufo->Spatial()->GetOrientation());
        float d = (n.z * f->z + n.y * f->y) + f->x * n.x;
        Vector3 h;
        h.x = f->x - d * n.x;
        h.y = f->y - n.y * d;
        h.z = f->z - n.z * d;
        float hInv = 1.0f / sqrtf(h.x * h.x + h.z * h.z + h.y * h.y + 1e-08f);

        float e = (dir.x * n.x + n.y * dir.y) + n.z * dir.z;
        Vector3 w;
        w.x = dir.x - e * n.x;
        w.y = dir.y - n.y * e;
        w.z = dir.z - n.z * e;
        float wInv = 1.0f / sqrtf(w.x * w.x + w.z * w.z + w.y * w.y + 1e-08f);

        float c = (((wInv * w.x) * (hInv * h.x) + (wInv * w.z) * (hInv * h.z)) + (wInv * w.y) * (hInv * h.y));
        float lo = -1.0f;
        float hi = 1.0f;
        c = MinSS(MaxSS(c, lo), hi);
        float angle = (float)acos(c);
        float threshold = (ufo->At<float>(0x604) == 0.0f) ? 0.02f : 0.1f;
        if (fabsf(angle) < threshold)
            mFlags &= ~2u;
    }

    if (mYawInput != 0.0f)
    {
        float half = mYawInput * 0.5f;
        float s = sinf(half);
        Quaternion q;
        q.x = n.x * s;
        q.y = n.y * s;
        q.z = n.z * s;
        float c = cosf(half);
        volatile float cMem = c;
        float qInv = 1.0f / sqrtf(c * c + q.z * q.z + q.x * q.x + q.y * q.y);
        Quaternion qn;
        qn.x = qInv * q.x;
        qn.y = qInv * q.y;
        qn.z = qInv * q.z;
        qn.w = qInv * cMem;
        Vector3 rotated;
        const Vector3* r = QuaternionRotate(&rotated, &dir, &qn);
        dir.x = r->x;
        dir.y = r->y;
        dir.z = r->z;
    }

    // Steer the eye direction towards the UFO when it is moving away from the anchor.
    Vector3 anchorToUfo;
    anchorToUfo.x = pPos->x - ufo->At<float>(0x750);
    anchorToUfo.y = pPos->y - ufo->At<float>(0x754);
    anchorToUfo.z = pPos->z - ufo->At<float>(0x758);
    float dist = sqrtf(anchorToUfo.x * anchorToUfo.x + anchorToUfo.z * anchorToUfo.z + anchorToUfo.y * anchorToUfo.y);
    if (dist > 1.5258789e-05f)
    {
        float invDist = 1.0f / dist;
        Vector3 u;
        u.x = invDist * (ufo->At<float>(0x750) - pPos->x);
        u.y = invDist * (ufo->At<float>(0x754) - pPos->y);
        u.z = invDist * (ufo->At<float>(0x758) - pPos->z);
        float dp = (n.z * u.z + n.y * u.y) + u.x * n.x;
        if (fabsf(dp) < (float)cos(0.8726646192371845))
        {
            Vector3 v;
            v.x = u.x - n.x * dp;
            v.y = u.y - n.y * dp;
            v.z = u.z - n.z * dp;
            float vInv = 1.0f / sqrtf(v.x * v.x + v.z * v.z + v.y * v.y);
            Vector3 target;
            target.x = vInv * v.x;
            target.y = vInv * v.y;
            target.z = vInv * v.z;

            const Vector3& vel = ufo->At<Vector3>(0x724);
            float speed = sqrtf((vel.x * vel.x + vel.y * vel.y) + vel.z * vel.z);
            float one = 1.0f;
            float ratio = speed / ufo->GetMaxGroundSpeed();
            const float& step = Min(ratio, one);
            if (!(0.0f > (dir.z * target.z + dir.y * target.y) + target.x * dir.x) && !ufo->At<bool>(0x608) &&
                sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z) < PlanetRadiusAt(pPos) + gPlanetCamSnapDistance)
            {
                Vector3 toward;
                const Vector3* r = RotateTowards(&toward, &dir, &target, step * seconds);
                dir = *r;
            }
        }
    }
}

// @ 0x01019950
void SP::cSPSpacePlanetCameraController_s0101_9090::UpdateCameraPitchRotation(float seconds, float pitch, Vector3* lookAt, Vector3* eye)
{
    SP::cSPGameDataUFO_s0101_9090* ufo = SP::GetUFOSimulator()->GetPlayerInventory();

    if (mFlags & 1)
    {
        // Pitch tracks the angle between the eye and the horizon; clamp the stored pitch to it.
        Vector3 d = *eye - *lookAt;
        float dInv = 1.0f / sqrtf(d.x * d.x + (d.z * d.z + d.y * d.y));
        Vector3 dn;
        dn.x = dInv * d.x;
        dn.y = d.y * dInv;
        dn.z = d.z * dInv;
        float lInv = 1.0f / sqrtf(lookAt->x * lookAt->x + (lookAt->y * lookAt->y + lookAt->z * lookAt->z));
        Vector3 ln;
        ln.x = lookAt->x * lInv;
        ln.y = lookAt->y * lInv;
        ln.z = lookAt->z * lInv;
        float dot = (ln.x * dn.x + ln.z * dn.z) + ln.y * dn.y;
        float c = ((((dn.x - ln.x * dot) * -1.0f) * dn.x + ((dn.z - ln.z * dot) * -1.0f) * dn.z) +
                   ((dn.y - ln.y * dot) * -1.0f) * dn.y);
        float lo = -1.0f;
        float hi = 1.0f;
        c = MinSS(MaxSS(c, lo), hi);
        double angle = acos(c);
        float cur = mPitch;
        float minPitch = (float)(1.5882496f - angle);
        float maxPitch = (float)(3.1241393f - angle);
        mPitch = MinSS(MaxSS(cur, minPitch), maxPitch);

        RotateEyeAroundLookAt(mPitch, lookAt, eye);

        if (!ufo->At<bool>(0x74c) && mZooming && !SP::GameInputManager()->IsRotateInputActive(0xcdcdcdcd))
            mFlags &= ~1u;
    }
    else
    {
        float one = 1.0f;
        float t = seconds * 2.0f;
        const float& ratio = (1.0f > t) ? t : one;
        float cur = mPitch;
        mPitch = (pitch - cur) * ratio + cur;

        RotateEyeAroundLookAt(mPitch, lookAt, eye);
    }
}

// @ 0x0101fb40
void SP::cDefaultCameraController::ReadProperties()
{
    int count1, count2; PairIF* pData1; PairIF* pData2;
    if (!mConfig) {
        IPropertyManager* pm = SP::PropertyManager();
        if (mConfig) { IPropertyList* old = mConfig; mConfig = 0; old->Release(); }
        pm->GetPropertyList(0x521d0174, 0x2ae0c7e, &mConfig);
    }
    READ_BOOL(g_016dd3fe, 0, 0x469153d);
    READ_F(g_016dd43c, 0.0f, 0x195a051);
    READ_F(g_016dd438, 0.0f, 0x195a052);
    READ_F(g_016dd434, 50.0f, 0x195a050);
    READ_F(g_016dd430, 1.0f, 0xe0e60974);
    READ_F(g_016dd42c, 0.699999988f, 0xe0e60975);
    READ_F(g_016dd428, 0.400000006f, 0xe0e60976);
    READ_F(g_016dd424, 0.25f, 0x4e53ffab);
    READ_F(g_016dd420, 0.0299999993f, 0x4e53ffaa);
    READ_F(g_016dd41c, 0.0299999993f, 0x4e53ffa9);
    READ_F(g_016dd418, 50.0f, 0x4658312);
    READ_F(g_016dd414, 2000.0f, 0x46c082b);
    READ_F(g_016dd410, 200.0f, 0x46d60ad);
    READ_DEG(g_016dd40c, 60.0f, 0x195a064);
    READ_F(g_016dd408, 1.0f, 0x48775d9);
    READ_F(g_016dd404, 1.0f, 0x48775e6);
    READ_F(g_016dd400, 1.0f, 0x48775e8);
    READ_F(g_016dd3d8, 0.0500000007f, 0x5baf74f);
    READ_F(g_016dd3d4, 0.00100000005f, 0x5baf750);
    READ_BOOL(g_016dd441, 1, 0x4a0b118);
    READ_BOOL(g_016dd440, 0, 0x4a4bb05);
    READ_BOOL(g_016dd3ff, 0, 0x4a4bb09);
    READ_BOOL(g_016dd3fc, 0, 0x4a4bb1c);
    READ_BOOL(g_016dd38b, 0, 0x4a4bb23);
    READ_BOOL(g_016dd38a, 0, 0x4a4bb27);
    READ_F(g_016dd3f8, 5.0f, 0x49a1d5e);
    READ_DEG(g_016dd3dc, 15.0f, 0x195a061);
    READ_F(g_016dd3f4, 900.0f, 0x63c0263);
    READ_F(g_016dd3f0, 1500.0f, 0x63c0261);
    READ_F(g_016dd3ec, 1000.0f, 0x6295b9e);
    READ_F(g_016dd3e8, 1500.0f, 0x37e593a);
    READ_F(g_016dd3e4, 500.0f, 0x6491aed);
    READ_F(g_016dd3e0, 800.0f, 0x6491aef);
    READ_BOOL(g_016dd389, 0, 0x6046db3);
    READ_F(g_016dd3d0, 20.0f, 0x195a021);
    READ_F(g_016dd3cc, 21.0f, 0x62fd07e);
    READ_F(g_016dd3c8, 25.0f, 0x62eb1ab);
    READ_F(g_016dd3c4, 50.0f, 0x62eb1ad);
    READ_F(g_016dd3c0, 500.0f, 0x62eb1b7);
    READ_F(g_016dd3bc, 800.0f, 0x5e3dcee);
    READ_F(g_016dd3b8, 2300.0f, 0x62ff0ce);
    READ_F(g_016dd3b4, 2400.0f, 0x195a020);
    g_016dd3b0 = 0; g_016dd3ac = 0;
    SP::GetPropertyAsFloatArray(mConfig, 0x632c41b, &g_016dd3ac, &g_016dd3b0);
    READ_F(g_016dd3a8, 2000.0f, 0x4657fb9);
    READ_F(g_016dd3a4, 200000.0f, 0x46ab5aa);
    READ_F(g_016dd3a0, 2000.0f, 0x632a46e);
    READ_F(g_016dd39c, 200000.0f, 0x632a472);
    READ_F(g_016dd398, 2000.0f, 0x665ed99);
    READ_F(g_016dd394, 200000.0f, 0x665ed9c);
    READ_F(g_016dd390, 0.0f, 0x3277323);
    READ_F(g_016dd38c, 0.0f, 0x3277324);
    READ_BOOL(g_016dd388, 0, 0x4691389);
    READ_F(g_016dd350, g_016dd434, 0x61ca5a3);
    READ_F(g_016dd34c, g_016dd434, 0x61ca5b2);
    {
        PairIF fill; pData1 = 0;
        count1 = 0;
        SP::GetPropertyAsPairArray(mConfig, 0x632a03b, &count1, &pData1);
        unsigned n = (unsigned)(g_016dda14.end - g_016dda14.begin);
        if ((unsigned)count1 > n) g_016dda14.insertN(g_016dda14.end, count1 - n, fill);
        else g_016dda14.erase(g_016dda14.begin + count1, g_016dda14.end);
        for (int i = 0; i < count1; ++i) {
            g_016dda14.begin[i].key = pData1[i].key;
            g_016dda14.begin[i].value = pData1[i].value * 0.017453292f;
        }
    }
    READ_FI(g_016dd384, 0.100000001f, 0x195a001);
    READ_FI(g_016dd380, 0.200000003f, 0x62ff100);
    READ_FI(g_016dd37c, 1.0f, 0x5e3e315);
    READ_FI(g_016dd378, 10.0f, 0x62eb105);
    READ_FI(g_016dd374, 1500.0f, 0x195a000);
    g_016dd370 = 0; g_016dd36c = 0;
    SP::GetPropertyAsFloatArray(mConfig, 0x632a816, &g_016dd36c, &g_016dd370);
    READ_FI(g_016dd368, 20000.0f, 0x46bb221);
    READ_FI(g_016dd364, 2000000.0f, 0x46bb224);
    READ_FI(g_016dd360, 20000.0f, 0x632a54d);
    READ_FI(g_016dd35c, 2000000.0f, 0x632a54f);
    {
        PairIF fill; pData2 = 0;
        count2 = 0;
        SP::GetPropertyAsPairArray(mConfig, 0x3a8dee8, &count2, &pData2);
        unsigned n = (unsigned)(g_016dda28.end - g_016dda28.begin);
        if ((unsigned)count2 > n) g_016dda28.insertN(g_016dda28.end, count2 - n, fill);
        else g_016dda28.eraseInline(g_016dda28.begin + count2, g_016dda28.end);
        for (int i = 0; i < count2; ++i) {
            g_016dda28.begin[i].key = pData2[i].key;
            g_016dda28.begin[i].value = pData2[i].value * 0.017453292f;
        }
    }
    READ_FI(g_016dd358, g_016dd434, 0x61ca5b9);
    READ_FI(g_016dd354, g_016dd434, 0x61ca5d4);
}

// @ 0x01020e80
char Cam::f20e80(int msg, int* p)
{
    if (msg == 0xf62def && *(int*)((char*)p + 0x18) == 0x521d0174) {
        E((char*)this - 4)->FUN_0101fb40();
    }
    return 0;
}

// @ 0x01021020
void Cam::f21020()
{
    char* s = (char*)this;
    f20fc0();
    int* p = (int*)(s + 0x84);
    if (*p == 0) {
        void* pman = FUN_0067de30();
        int old = *p;
        if (old) {
            *p = 0;
            ((void(__thiscall*)(void*))VTP((void*)old)[1])((void*)old);
        }
        ((void(__thiscall*)(void*, u32, u32, void*))VTP(pman)[0x2c / 4])(
            pman, 0x1106d054, 0x2ae0c7e, p);
    }
}

// @ 0x013a0c40
void PropTableInit_0c40()
{
    PropDesc d;
    d.name = "mScaleFactor"; d.hash = 0x3a212e6u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0xbcu;
    g_props_0c40[0] = d;

    d.name = "mLookAtCenter"; d.hash = 0x3a212f4u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x8cu;
    g_props_0c40[1] = d;

    d.name = "mLookAtCurrent"; d.hash = 0x3a21303u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x98u;
    g_props_0c40[2] = d;

    d.name = "mLookAtVelocity"; d.hash = 0x3a21318u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0xa4u;
    g_props_0c40[3] = d;

    d.name = "mOffsetCurrent"; d.hash = 0x3a21342u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x68u;
    g_props_0c40[4] = d;

    d.name = "mLastGalacticOffset"; d.hash = 0x684df08u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x74u;
    g_props_0c40[5] = d;

    d.name = "mZoomTarget"; d.hash = 0x3a21345u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0xb4u;
    g_props_0c40[6] = d;

    d.name = "mZoomVelocity"; d.hash = 0x3a2135bu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0xb8u;
    g_props_0c40[7] = d;

    d.name = "mLastDeltaPhi"; d.hash = 0x22556efu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0x80u;
    g_props_0c40[8] = d;
}
