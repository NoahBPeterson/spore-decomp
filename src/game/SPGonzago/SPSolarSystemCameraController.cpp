// src/game/SPGonzago/SPSolarSystemCameraController.cpp -- migrated from slice(s) s0101ec40, s0101c780, s0101bd10, s0101aea0, s01019f50, s010180e0, s01399700, s01020e80, s0101fb40, s01019090, s01018810, s010175b0, s01016540 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSolarSystemCameraController.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "sse_helpers.h"
#include "SP/cSPTimer.h"
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>
#include "cSPMatrix4.h"
#include "EA/Stopwatch.h"
#include "SP/cViewer.h"
#include <intrin.h>
#include "SP/cPlanetModel.h"
#include <stddef.h>

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
// Clamp: the vetted SseClamp in sse_helpers.h

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
extern f32 g16dd434;
extern u8  g16dd3fc;
extern u8  g16dd441;
extern u32 g16dd444;
extern u32 g16dd448;
extern u32 g16dd44c;
extern u32 g16dda78;
extern f32 g16dda74;
extern f32 g16dda70;
extern Table g16dda14;
extern Table g16dda28;
extern f32 g15b6d88;
extern f32 g15b6d8c;
extern u32 g15b6ddc;
extern u32 g15b6de0;
extern u32 g15b6de4;
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
extern u32   DAT_01495910;
void* __cdecl FUN_0067dcc0();                        // SP::MessageServer
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

// ---- items of slice s010180e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
namespace SP {
struct Vector3_s0101_80e0 { float x, y, z; };
}
namespace SP {
class cInventoryCamera {
 public:
virtual void pv00();
virtual void pv01();
virtual void pv02();
virtual void pv03();
virtual void pv04();
virtual void pv05();
virtual void pv06();
virtual void pv07();
virtual void pv08();
virtual void pv09();
virtual void pv10();
  virtual Vector3_s0101_80e0* GetPosition();   // +0x2c
};
}
namespace SP {
class cPlayerInventory_s0101_80e0 {
 public:
  char pad00[0x34];
  cInventoryCamera mCamera;         // +0x34
  char pad38[0x74c - 0x38];
  bool mbCameraOverride;            // +0x74c
  char pad74d[0x750 - 0x74d];
  Vector3_s0101_80e0 mCameraOverridePos;       // +0x750
};
}
namespace SP {
class cSPSimulatorSpaceGame_s0101_80e0 {
 public:
  cPlayerInventory_s0101_80e0* GetPlayerInventory();   // 0x00a1ad60
};
}
namespace SP {
cSPSimulatorSpaceGame_s0101_80e0* GetUFOSimulator_s0101_80e0();   // 0x00ffbe50
}
namespace SP {
class cGameTimeManager_s0101_80e0 {
 public:
  char pad00[0x48];
  uint32_t mnFlags;                 // +0x48
};
}
namespace SP {
cGameTimeManager_s0101_80e0* GameTimeManager_s0101_80e0();   // 0x00b3d380
}
namespace SP {
class cSPSpacePlanetCameraController_s0101_80e0 {
 public:
  float GetCurrentZoom();           // 0x010187c0
};
}
// ---- items of slice s010180e0 end

// ---- items of slice s01019f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern const float kFloatOne;           // 0x01485720 (_HK_REAL_ONE)
extern const float kFacingDefaultX;     // 0x016dd444
extern const float kFacingDefaultY;     // 0x016dd448
extern const float kFacingDefaultZ;     // 0x016dd44c
extern const float kCamDistance;        // 0x01465544 (1000.0f)
extern const float kCamFOV;             // 0x013f1cac (50.0f)
extern const float kCamMaxZoom;         // 0x01488874 (0.1f)
extern char vtbl_BehaviorMessage[];     // 0x013eb90c (UI::BehaviorMessage base vtable)
extern char vtbl_SlotMessage[];         // 0x013eb844 (SlotMessage derived vtable)
extern const float kEffectMaxDistance;  // 0x013fec70 (1500.0f)
struct Vec4 { float x, y, z, w; };
struct Matrix34 {
    Vec4 xAxis;    // +0x00
    Vec4 yAxis;    // +0x10
    Vec4 zAxis;    // +0x20
};
struct Vec3Row {
    float x, y, z;
    Vec3Row() {}
    Vec3Row(const Vec4& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33 {
    Vec3Row xAxis, yAxis, zAxis;
    Matrix33() {}
    Matrix33(const Matrix34& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};
struct Vector3_s0101_9f50 {
    float x, y, z;
    Vector3_s0101_9f50() {}
    Vector3_s0101_9f50(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s0101_9f50& operator=(const Vector3_s0101_9f50& o) {
        *(int*)&x = *(const int*)&o.x;
        *(int*)&y = *(const int*)&o.y;
        *(int*)&z = *(const int*)&o.z;
        return *this;
    }
};
struct Quaternion_s0101_9f50 {
    float x, y, z, w;
    Quaternion_s0101_9f50() {}
    Quaternion_s0101_9f50(const Quaternion_s0101_9f50& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};
Quaternion_s0101_9f50& QuaternionFromMatrix33(Quaternion_s0101_9f50& out, const Matrix33& m, float tolerance);   // 0x00472b80
struct cViewer {
    Matrix34 mCameraToWorldTransform;              // +0x00
    Vector3_s0101_9f50  mEye;                                 // +0x30
};
namespace EA {
class Stopwatch_s0101_9f50 {
public:
    enum Units { kUnitsCycles = 0, kUnitsSeconds = 5 };
    Stopwatch_s0101_9f50() {}
    Stopwatch_s0101_9f50(int units, bool bStartImmediately);       // 0x0093a560
    uint64_t mnStartTime;                               // +0x00
    uint64_t mnTotalElapsedTime;                        // +0x08
    int      mnUnits;                                   // +0x10
    float    mfStopwatchCyclesToUnitsCoefficient;       // +0x14
};
}
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
struct cCameraControllerPrimary {
    virtual void p0();
};
struct cListenerBase {
    virtual void l0();
    virtual void l1();
    virtual void l2();
    virtual void l3();
};
struct cContentValidationSummarizer {
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    void* mpOwner;                                      // +0x04 within this subobject
    cContentValidationSummarizer() : mpOwner(0) {}
};
struct CCameraTargetRef {
    IRefCounted* mpTarget;
    CCameraTargetRef(IRefCounted* p) : mpTarget(p) {
        if (p != 0)
            p->AddRef();
    }
};
struct CField14Seed {
    void* mValue;
    CField14Seed() : mValue(0) {
    }
};
struct cCameraControllerBase : cCameraControllerPrimary, cListenerBase, cContentValidationSummarizer {
    CCameraTargetRef mTarget;                           // +0x10
    CField14Seed mField14;                              // +0x14
    void*        m18;                                   // +0x18
    void*        m1c;                                   // +0x1c
    void*        m20;                                   // +0x20
    void*        m24;                                   // +0x24
    void*        m28;                                   // +0x28
    uint32_t     m2c;                                   // +0x2c
    EA::Stopwatch_s0101_9f50 mStopwatch;                           // +0x30
    void*        m48;                                   // +0x48
    void*        m4c;                                   // +0x4c
    void*        m50;                                   // +0x50
    uint32_t     m54;                                   // +0x54
    uint32_t     m58;                                   // +0x58
    void*        m5c;                                   // +0x5c
    float        m60;                                   // +0x60
    float        m64;                                   // +0x64

    cCameraControllerBase(IRefCounted* target);

    virtual void l0();                                  // override cListenerBase
    virtual void c0();                                  // override cContentValidationSummarizer
};
extern const Vector3_s0101_9f50 kUFOForward_s0101_9f50;       // 0x015b6de8
extern const Vector3_s0101_9f50 kWorldUp;          // 0x015b6df4
extern const Quaternion_s0101_9f50 kIdentityOrient;// 0x015b6e00
struct Matrix44Raw { float m[16]; };    // +0xf8 .. +0x137 (not initialized by the constructor)
struct cSPSpacePlanetCameraController_s0101_9f50 : cCameraControllerBase {
    bool     mSnapTuning;          // +0x68
    uint8_t  pad069[3];
    float    mDistance;            // +0x6c
    float    mFOV;                 // +0x70
    float    mSurfaceDistance;     // +0x74
    float    mZoom;                // +0x78
    float    mMaxZoom;             // +0x7c
    float    mLookAtHeight;        // +0x80
    float    mPitch;               // +0x84
    float    mPullOut;             // +0x88
    float    mPullOutRight;        // +0x8c
    float    mPullOutUp;           // +0x90
    Vector3_s0101_9f50  mEyeDirection;        // +0x94
    Vector3_s0101_9f50  mAnchorDir;           // +0xa0
    float    mAC;                  // +0xac
    float    mB0;                  // +0xb0
    Vector3_s0101_9f50  mEye;                 // +0xb4
    Vector3_s0101_9f50  mLookAt;              // +0xc0
    bool     mZooming;             // +0xcc
    uint8_t  pad0cd[3];
    float    mTuningBlend;         // +0xd0
    Vector3_s0101_9f50  mPrevEye;             // +0xd4
    Quaternion_s0101_9f50 mPrevOrientation;   // +0xe0
    float    mBlendIn;             // +0xf0
    float    mBlendInTime;         // +0xf4
    Matrix44Raw mCameraToWorld;    // +0xf8
    int      mMode;                // +0x138
    bool     mFlag13c;             // +0x13c
    bool     mRotateLeft;          // +0x13d
    bool     mRotateRight;         // +0x13e
    bool     mApproachStart;       // +0x13f
    bool     mApproaching;         // +0x140
    uint8_t  pad141[3];
    Vector3_s0101_9f50  mApproachFrom;        // +0x144
    Vector3_s0101_9f50  mApproachTo;          // +0x150
    Vector3_s0101_9f50  mApproachBase;        // +0x15c
    Vector3_s0101_9f50  mApproachUp;          // +0x168
    Quaternion_s0101_9f50 mApproachOrientation;// +0x174
    float    mApproachTwist;       // +0x184
    Vector3_s0101_9f50  mApproachAnchor;      // +0x188
    bool     mApproachDone;        // +0x194
    uint8_t  pad195[3];
    int      m198;                 // +0x198

    cSPSpacePlanetCameraController_s0101_9f50(IRefCounted* target);

    void SetSourceInterpolation(cViewer* viewer, float weight);  // 0x01019f50 (cSPSpacePlanetCameraController::SetSourceInterpolation)
    void UpdateEffects();
};
struct cSPSpaceCameraController : cCameraControllerBase {
    Vector3_s0101_9f50  m68;                                  // +0x68
    Vector3_s0101_9f50  m74;                                  // +0x74 (not initialized by the constructor)
    float    m80;                                  // +0x80
    volatile uint32_t m84;                         // +0x84
    volatile uint32_t m88;                         // +0x88
    Vector3_s0101_9f50  m8c;                                  // +0x8c
    Vector3_s0101_9f50  m98;                                  // +0x98
    Vector3_s0101_9f50  ma4;                                  // +0xa4
    float    mb0;                                  // +0xb0
    float    mb4;                                  // +0xb4
    float    mb8;                                  // +0xb8
    float    mbc;                                  // +0xbc
    float    mc0;                                  // +0xc0
    float    mc4;                                  // +0xc4
    float    mc8;                                  // +0xc8
    float    mcc;                                  // +0xcc
    float    md0;                                  // +0xd0
    uint8_t  md4[7];                               // +0xd4

    cSPSpaceCameraController(IRefCounted* target);
};
struct SlotMessage {
    void*         mVtable;        // +0x00
    volatile long mRefCount;      // +0x04
    float         mPayloadA;      // +0x08 distance to the surface
    uint32_t      mPayloadGap;    // +0x0c
    float         mPayloadB;      // +0x10 maximum distance
    uint32_t      mBody[7];       // +0x14 .. +0x2f listener slots
    uint32_t      mArg;           // +0x30
    uint32_t      mPad34;         // +0x34
    uint32_t      mListenerMask;  // +0x38

    void Destruct();              // 0x00421cf0
};
struct MessageServerT {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void v4();
    virtual void Post(uint32_t id, SlotMessage* msg, uint32_t extra);   // +0x14
};
MessageServerT* MessageServer();          // 0x0067dcc0
struct CameraAltitude {
    uint8_t pad[0x34];
    float   mAltitude;                    // +0x34
};
struct PlanetModelUFO {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual CameraAltitude* v3();         // +0x0c
};
struct PlanetModelRoot {
    uint8_t        pad[0x24];
    PlanetModelUFO* mUFO;                 // +0x24
};
PlanetModelRoot* PlanetModel();          // 0x00b3d350
struct InventoryBase {
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
    virtual Vector3_s0101_9f50* GetPosition();       // +0x2c
};
struct PlayerInventory {
    uint8_t       pad00[0x34];
    InventoryBase mBase;                  // +0x34
    uint8_t       pad38[0x74c - 0x38];
    uint8_t       mShipLocked;            // +0x74c
    uint8_t       pad74d[3];
    Vector3_s0101_9f50       mShipPosition;          // +0x750
};
struct cSPSimulatorSpaceGame_s0101_9f50 {
    PlayerInventory* GetPlayerInventory();// 0x00a1ad60
};
cSPSimulatorSpaceGame_s0101_9f50* GetUFOSimulator_s0101_9f50(); // 0x00ffbe50
struct EffectGameTimeManager {
    uint8_t pad[0x48];
    uint8_t mFlags;                       // +0x48 bit 0 = paused
};
EffectGameTimeManager* EffectGameTimeManagerFn();   // 0x00b3d380
// ---- items of slice s01019f50 end

// ---- items of slice s0101aea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_015b6da4, DAT_015b6da0, DAT_015b6d9c, DAT_015b6d94;
extern float DAT_015b6da8, DAT_01495390, DAT_01495394, DAT_01485720, DAT_01495934;
extern float DAT_013f4fd0, DAT_013fdf1c, DAT_013f89b8, DAT_013f9428, DAT_01470f1c;
extern float DAT_013eb1bc, DAT_013f0e84;
extern float DAT_016dd3d0, DAT_016dd384, DAT_016dd3b4, DAT_016dd374, DAT_016dd3cc;
extern float DAT_016dd3b8, DAT_016dd380, DAT_016dd3e8, DAT_016dd3ec, DAT_016dd3e0;
extern float DAT_016dd3e4, DAT_016dd414, DAT_016dd418, DAT_016dd3c8, DAT_016dd3c4;
extern int   DAT_016dd36c, DAT_016dd370, DAT_016dd3ac, DAT_016dd3b0;
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);
extern u8    DAT_015b6d98;
extern u32   DAT_016dd444, DAT_016dd448, DAT_016dd44c;
int   __cdecl FUN_01021080();                        // GetUniverseContext
void* __cdecl FUN_01021260();                        // GetActivePlanet
void* __cdecl FUN_00a206f0();                        // EA::Audio::GetSystemAT
void  __cdecl FUN_00435ed0(u32, int);                // KillSetiEffects
void  __cdecl FUN_01017fe0();                        // 0x01017fe0
void* __cdecl FUN_010666a0();                        // 0x010666a0
void* __cdecl FUN_0067cac0();                        // 0x0067cac0
void* __cdecl FUN_00b3d4d0();                        // GetTriggerMgr
unsigned char __cdecl FUN_01044920();                // 0x01044920
unsigned char __cdecl FUN_010422e0();                // TransitionFromSolarToGalaxy
unsigned char __cdecl FUN_01042450();                // 0x01042450
unsigned char __cdecl FUN_010423d0();                // 0x010423d0
void  __cdecl FUN_01042480(float*, float*);          // 0x01042480
float __cdecl FUN_00c375d0(float*);                  // 0x00c375d0
float* __cdecl FUN_0105c3d0(void*, void*, float);    // 0x0105c3d0
float* __cdecl FUN_0059aed0(void*, void*, void*);    // 0x0059aed0
float __cdecl FUN_00b0f060(float, float, float);     // KeyboardRamp
struct Ext_s0101_aea0 {
    long long FUN_0093a3a0();                // EA::Stopwatch::GetElapsedTimeFloat
    void FUN_0093a1a0(int);                  // EA::Stopwatch::SetUnits
    char FUN_00c8b800();                     // 0x00c8b800
    void* FUN_00a1ad60();                    // GetPlayerInventory
    void FUN_00c3daa0(float);                // 0x00c3daa0
    void FUN_01017fe0();                     // 0x01017fe0
    float FUN_01017790(int, int);            // 0x01017790
    float FUN_01017d30();                    // 0x01017d30
    float FUN_00c37120();                    // 0x00c37120
    char FUN_00c37170();                     // 0x00c37170
    float FUN_00c3ae70();                    // 0x00c3ae70
    void FUN_00ffe3d0(float, int);           // 0x00ffe3d0
    float FUN_00fb7ba0();                    // 0x00fb7ba0
    float FUN_00b7e4d0();                    // 0x00b7e4d0
    float FUN_00b7ef70(void*);               // GetRadiusAt
    void* FUN_0107b70_getUFO();              // GetUFOPosition (placeholder naming)
    void FUN_0067c8c0(u32, int);             // 0x0067c8c0
    void FUN_01065d20();                     // 0x01065d20
};
static inline Ext_s0101_aea0* E_s0101_aea0(void* p) { return (Ext_s0101_aea0*)p; }
struct UFO_Sample {
    union {
        long long raw;      // the stopwatch's 64-bit value is spilled into the sample's own storage
        struct {
            float t;
            char  keep;
        };
    };
};
struct UFO_SampleVec {
    UFO_Sample* begin;
    UFO_Sample* end;
    UFO_Sample* cap;
    void FUN_00B534C0(UFO_Sample* e, UFO_Sample* s);   // 0x00b534c0
    void FUN_Erase(UFO_Sample* first, UFO_Sample* last); // 0x00d018d0 eastl::vector::erase
};
struct UFO {
    u8 raw[0x300];
    void  aea0(float delta);   // UpdateMouseWheel
    void  b0f0();
    void  b160(float, float);
    void  b4c0(float);
    void  b530(char);
    void  b670(float);
    void  b9e0();
    void  ba10(char);
    void  bad0(int, int);
    char  bb10(int, int, int, int);
    void  bb90(int, char);
};
// ---- items of slice s0101aea0 end

// ---- items of slice s0101bd10 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cViewer_s0101_bd10 { public:
    void SetNear(float v);                       // 0x007c4ba0 (thiscall, ret 4)
    void SetFar(float v);                        // 0x007c4bc0 (thiscall, ret 4)
    void SetViewAngle(float v);                  // 0x007c5350 (thiscall, ret 4)
    void SetCameraToWorld(const float* m);       // 0x007c4c40 (thiscall, ret 4)
};
}
namespace SP {
class cSpatialObject_s0101_bd10 { public:
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
    virtual const Vector3* GetPosition();        // +0x2c
};
}
namespace SP {
class cSPGameDataUFO_s0101_bd10 { public:
    uint32_t pad0[0x34 / 4];
    cSpatialObject_s0101_bd10 mSpatial;                     // +0x34
    uint32_t pad38[(0x718 - 0x38) / 4];
    Vector3 mSavedPos;                           // +0x718
    uint32_t pad724[(0x74c - 0x724) / 4];
    bool mHasPos;                                // +0x74c
    float GetScale();                            // 0x00c3ae70
};
}
namespace SP {
class cSPSimulatorSpaceGame_s0101_bd10 { public:
    cSPGameDataUFO_s0101_bd10* GetPlayerInventory();        // 0x00a1ad60
};
}
namespace SP {
struct IStageAttachment {                                      // object held in IStage+0xc4
    virtual void v00();                                        // +0x00
    virtual int  Release();                                    // +0x04
    virtual void v08();                                        // +0x08
    virtual void v0c(int);                                     // +0x0c
};
}
namespace SP {
struct StageRef {                                              // ref-counted pointer member
    IStageAttachment* mPtr;                                    // +0x00
    __forceinline operator bool() const { return mPtr != 0; }
    __forceinline IStageAttachment* operator->() const { return mPtr; }
    __forceinline void reset() {
        IStageAttachment* old = mPtr;
        if (old != 0) {
            mPtr = 0;
            old->Release();
        }
    }
};
}
namespace SP {
struct IStage {                                                // b3d4d0 -> +0x2c
    uint32_t pad[0x2c / 4];                                    // +0x00
    int mMode;                                                 // +0x2c
    uint32_t pad30[(0xc4 - 0x30) / 4];                         // +0x30
    StageRef mC4;                                              // +0xc4
};
}
namespace SP {
struct cSpaceLocation {                                       // 0x01021230 result
    const Vector3* GetPosition();                            // 0x00c8b360 (thunk)
    bool IsKnown();                                          // 0x00c8b800 (thunk)
};
}
namespace SP {
struct cCivData_s0101_bd10 {                                             // 0x01021240 result
    int GetContext();                                        // 0x00801920 (returns field +0x48)
};
}
namespace SP {
struct ISpaceGame { bool IsFrozen(); };                      // 0x00b18e40
}
namespace SP {
int GetUniverseContext();                        // 0x01021080
}
namespace SP {
cSPSimulatorSpaceGame_s0101_bd10* GetUFOSimulator_s0101_bd10();        // 0x00ffbe50
}
namespace SP {
IStage* GetStage();                              // 0x00b3d4d0
}
namespace SP {
ISpaceGame* SpaceGameGet();                      // 0x01002bd0
}
namespace SP {
cSpatialObject_s0101_bd10* GetActivePlanet();               // 0x01021260
}
namespace SP {
cSpaceLocation* GetHomeLocation();               // 0x01021230
}
namespace SP {
cCivData_s0101_bd10* GetPlayerCiv();                        // 0x01021240
}
namespace SP {
bool  IsCivOutsideRange(int civ);                // 0x00c8b520 (true when the civ id is 0 or > 3)
}
namespace SP {
Vector3* ComputeUFOOffsetPos(Vector3* out, int unused, float scale);  // 0x0105c5d0
}
namespace SP {
void ResetEffectStates();                        // 0x006f3290
}
namespace SP {
void UpdateFocus(Vector3* cur, Vector3* vel, const Vector3* target, float c1, float c1k, float dtms);  // 0x010426a0
}
namespace SP {
void UpdateZoom(float* zoom, float* vel, float target, float v, float v2, float dtms);                   // 0x01042570
}
namespace SP {
void OffsetFromZoom(Vector3* out, const Vector3* in);                                                    // 0x010424c0
}
namespace SP {
void BuildCameraMatrix(const Vector3* target, const Vector3* eye, const Vector3* up, float* out16);      // 0x01043580
}
namespace SP {
extern float gCamK3d0;   // 0x016dd3d0
}
namespace SP {
extern float gCamK3b4;   // 0x016dd3b4
}
namespace SP {
extern float gCamK384;   // 0x016dd384
}
namespace SP {
extern float gCamK374;   // 0x016dd374
}
namespace SP {
extern float gCamK43c;   // 0x016dd43c
}
namespace SP {
extern float gCamK438;   // 0x016dd438
}
namespace SP {
extern float gCamK434;   // 0x016dd434
}
namespace SP {
extern float gCamK354;   // 0x016dd354
}
namespace SP {
extern float gCamK358;   // 0x016dd358
}
namespace SP {
extern float gCamK350;   // 0x016dd350
}
namespace SP {
extern float gCamK34c;   // 0x016dd34c
}
namespace SP {
extern float gCamK3b8;   // 0x016dd3b8
}
namespace SP {
extern float gCamK3bc;   // 0x016dd3bc
}
namespace SP {
extern float gCamK3c0;   // 0x016dd3c0
}
namespace SP {
extern float gCamK378;   // 0x016dd378
}
namespace SP {
extern float gCamK37c;   // 0x016dd37c
}
namespace SP {
extern float gCamK3cc;   // 0x016dd3cc
}
namespace SP {
extern float gCamQuarterPi; // 0x015b6dd0 (pi/4, default vertical camera angle)
}
namespace SP {
extern float gCamK380;   // 0x016dd380
}
namespace SP {
extern float gCamK444;   // 0x016dd444
}
namespace SP {
extern float gCamK448;   // 0x016dd448
}
namespace SP {
extern float gCamK44c;   // 0x016dd44c
}
namespace SP {
extern float gCamK430;   // 0x016dd430
}
namespace SP {
extern float gCamK424;   // 0x016dd424
}
namespace SP {
extern float gCamK42c;   // 0x016dd42c
}
namespace SP {
extern float gCamK420;   // 0x016dd420
}
namespace SP {
extern float gCamK428;   // 0x016dd428
}
namespace SP {
extern float gCamK41c;   // 0x016dd41c
}
namespace SP {
extern float gCamPhase;  // 0x016dda7c
}
namespace SP {
extern float gCamC1;     // 0x015b6db8
}
namespace SP {
extern float gCamC2;     // 0x015b6db4
}
namespace SP {
extern float gCamMinZoom; // 0x015b6db0
}
namespace SP {
extern bool gCamShake;   // 0x015b6dac
}
namespace SP {
extern const Vector3 kCamUp;  // 0x015b6df4
}
namespace SP {
extern Vector3 kCamOrigin;    // 0x016dd444 (default focus/velocity, .bss at runtime)
}
namespace SP {
class cSPCameraControllerSolarSystem_s0101_bd10 {
public:
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual float GetZoom();                    // +0x5c
    virtual void v60();                          // +0x60
    virtual void v64(int);                       // +0x64

    void Update(int ms, cViewer_s0101_bd10* viewer);       // 0x0101c080
    void snapToHome();                           // 0x0101bd10
    void snapToSystem();                         // 0x0101be60
    void restoreSavedView();                     // 0x0101bf40
    void SetCameraDistance(float v);             // 0x0101b4c0

    void FUN_0101aea0(float dt);                // ret 4
    void FUN_0101b160(float a, float b);        // ret 8
    void FUN_01017390();
    void FUN_0101a330(int ms, int zero);        // ret 8
    float FUN_01017790(bool a, bool b);         // ret 8
    void FUN_010180e0(Vector3* out, Vector3 pos, Vector3 dir, int zero);   // ret 0x20

    uint32_t pad04[(0x60 - 4) / 4];
    float mF60;                                  // 0x60
    uint32_t pad64;
    float mZoom;                                 // 0x68
    float mF6c;                                  // 0x6c
    float mF70;                                  // 0x70
    Vector3 mSavedZoom;                          // 0x74
    uint32_t pad80[(0x88 - 0x80) / 4];           // 0x80
    int mState;                                  // 0x88
    uint32_t pad8c[(0x98 - 0x8c) / 4];
    Vector3 mFocus;                              // 0x98
    Vector3 mFocusVel;                           // 0xa4
    uint32_t padB0;
    float mTargetZoom;                           // 0xb4
    float mZoomVel[2];                           // 0xb8
    uint8_t padC0[0xd7 - 0xc0];
    bool mSnapped;                               // 0xd7
    bool mResetPending;                          // 0xd8
};
}
inline int Min_s0101_bd10(const int& a, const int& b) { return (a < b) ? a : b; }
// ---- items of slice s0101bd10 end

// ---- items of slice s0101c780 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
namespace SP {
struct Vec3_s0101_c780 { float x, y, z; Vec3_s0101_c780() {} Vec3_s0101_c780(float a, float b, float c) : x(a), y(b), z(c) {} };
}
namespace SP {
struct Vec4_s0101_c780 { float x, y, z, w; Vec4_s0101_c780() {} Vec4_s0101_c780(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
}
namespace SP {
static inline float Dot3(const Vec3_s0101_c780& a, const Vec3_s0101_c780& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
}
namespace SP {
static inline float Len3(const Vec3_s0101_c780& a) { return (float)sqrt((double)Dot3(a, a)); }
}
namespace SP {
static inline Vec3_s0101_c780 Sub3(const Vec3_s0101_c780& a, const Vec3_s0101_c780& b) { return Vec3_s0101_c780(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
static inline Vec3_s0101_c780 Cross3(const Vec3_s0101_c780& a, const Vec3_s0101_c780& b) {
    return Vec3_s0101_c780(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
}
namespace SP {
extern float g_1477fbc;  // 0x1477fbc (200.0f)
}
namespace SP {
extern float g_13eb1bc;  // 0x13eb1bc (-1.0f, the card's "g_zero" label is wrong)
}
namespace SP {
extern float g_15b6dbc;  // 0x15b6dbc (solar min-zoom rate)
}
namespace SP {
struct cPlanetModel_s0101_c780 {
    float GetRadius();  // 0xb7e4d0
};
}
namespace SP {
cPlanetModel_s0101_c780* __cdecl PlanetModel_s0101_c780();  // 0xb3d350
}
namespace SP {
struct cCameraFrame {
    char data[0x40];
    cCameraFrame* Initialize(void* viewer);  // 0xb16dc0  ?Initialize@cCameraFrame@@QAEPAU1@PAVcViewer@SP@@@Z
};
}
namespace SP {
struct cSPSimulatorSpaceGame_s0101_c780 {
    void* GetPlayerInventory();  // 0xa1ad60
};
}
namespace SP {
void* __cdecl App();            // 0x67dd10
}
namespace SP {
void* __cdecl GetUFOSimulator_s0101_c780();  // 0xffbe50
}
extern "C" char __cdecl FUN_00b182f0(void*, int);                     // 0xb182f0
extern "C" char __cdecl FUN_00b17c10(void*, void*);                   // 0xb17c10
extern "C" char __cdecl FUN_00b17810(void*, void*);                   // 0xb17810
extern "C" char __cdecl FUN_00b181d0(void*, float*);                  // 0xb181d0
extern "C" void __cdecl FUN_00b16490(void*, float);                   // 0xb16490
extern "C" void __cdecl FUN_00b16450(void*, void*);                   // 0xb16450
extern "C" void __cdecl FUN_00b16e50(void*, void*);                   // 0xb16e50
extern "C" void __cdecl FUN_00799320(float* out, const float* in);       // 0x799320
namespace SP {
struct cShapeQuery {
    Vec3_s0101_c780 origin;        // +0x00
    char rest[0x1fc];
    void FUN_00b17790(int enable);  // 0xb17790
};
}
namespace SP {
class cSPSpacePlanetCameraController_s0101_c780 {
public:
    char pad00[0x6c];
    float mPlanetFarZoomHeight;    // +0x6c
    char pad70[0x78 - 0x70];
    float mSolarMinZoom;           // +0x78
    char pad7c[0x84 - 0x7c];
    float mSolarZoomRateMax;       // +0x84
    char pad88[0x90 - 0x88];
    float mWantDebugSolarPullOut;  // +0x90
    Vec3_s0101_c780  mGalaxyZoom;             // +0x94: x = min zoom, y = max zoom, z = rate min
    char padA0[0x198 - 0xa0];
    union { float f; uint32_t u; } mCurrentMatrixYAxisX;  // +0x198 (bit 0 is OR-ed in)
    char pad19c[0x200 - 0x19c];

    void FUN_0101c780(float a1, float* a2, float* a3, float* a4,
                      float a5, int a6, float a7, float a8);
    float* GetUFOPosition();  // 0x1017b70
    void UpdateCameraPitchRotation(float a1, float a8, Vec3_s0101_c780* a3, Vec3_s0101_c780* a2);  // 0x1019950
};
}
namespace SP {
static void* VCall0(void* obj, int byte_offset)
{
    void** vt = *(void***)obj;
    typedef void* (__fastcall* Fn)(void*);
    return ((Fn)vt[byte_offset / 4])(obj);
}
}
// ---- items of slice s0101c780 end

// ---- items of slice s0101ec40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00a1ad60();                     // 0xa1ad60  cSPSimulatorSpaceGame::GetPlayerInventory (thiscall)
extern "C" void  FUN_0101d130();                     // 0x101d130 (thiscall, 2 args, ret 8)
extern "C" void  FUN_01043580(void*, void*, void*, void*); // 0x1043580 (cdecl, 4 args)
extern "C" void  FUN_007c4ba0();                     // 0x7c4ba0  cViewer::FUN_007c4ba0 (thiscall, 1 arg, ret 4)
extern "C" void  FUN_007c4bc0();                     // 0x7c4bc0  cViewer::FUN_007c4bc0 (thiscall, 1 arg, ret 4)
extern "C" void  FUN_007c5350();                     // 0x7c5350  cViewer::SetViewAngle (thiscall, 1 arg, ret 4)
extern "C" void  FUN_007c4c40();                     // 0x7c4c40  cViewer::SetCameraToWorld (thiscall, 1 arg, ret 4)
extern "C" void  FUN_0101ad50();                     // 0x101ad50 (thiscall, 0 args)
extern "C" void* FUN_00b3d280();                     // 0xb3d280  GetCameraCtl
extern "C" void  FUN_00b10540();                     // 0xb10540  cTerrainCameraController::FUN_00b10540 (thiscall, 3 args, ret 0xc)
extern "C" float DAT_016dd444_s0101_ec40;   // 0x16dd444  invalid-position sentinel x
extern "C" float DAT_016dd448_s0101_ec40;   // 0x16dd448  invalid-position sentinel y
extern "C" float DAT_016dd44c_s0101_ec40;   // 0x16dd44c  invalid-position sentinel z
struct S {
  void FUN_0101ec40(void* param_2, void* param_3);   // 0x101ec40
};
// ---- items of slice s0101ec40 end

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
    r = SseClamp(r, 0.0f, 1.0f);
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

// @ 0x01017910
void cSPSpacePlanetCameraController::FUN_01017910()
{
    this->mD4 = 0;
    this->mD8 = 0;
    this->mE0 = 0;
    this->mDC = 0;
    this->mE4 = 0;
    this->mF0 = 1.0f;
    this->mF4 = 1.0f;
    this->mE8 = 0;
    this->mEC = 1.0f;

    this->m68.b = 1;
    this->kPlanetFarZoomHeight = 50.0f;
    this->m70 = g16dd434;
    this->m74 = MOPS(FUN_00b3d350())->FUN_00b7e4d0();
    this->m7C = 0.2617994f;
    this->m78 = 0.0f;
    this->m90 = 0.0f;
    this->m94 = g15b6ddc;
    this->m98 = g15b6de0;
    this->m9C = g15b6de4;
    this->mA0 = g16dd444;
    this->mA4 = g16dd448;
    this->mA8 = g16dd44c;
    this->mAC = 0.0f;
    this->mB0 = 0.0f;
    this->m198 = 0;
    this->m138 = 0;
    this->mB4 = g16dd444;
    this->mB8 = g16dd448;
    this->mBC = g16dd44c;
    this->mC0 = g16dd444;
    this->mC4 = g16dd448;
    this->mC8 = g16dd44c;
    this->mD0 = 0.0f;
    this->m13F = 1;
    this->m140 = 0;
    this->m144 = g16dd444;
    this->m148 = g16dd448;
    this->m14C = g16dd44c;
    this->m15C = g16dd444;
    this->m160 = g16dd448;
    this->m164 = g16dd44c;
    this->m13C = 1;
    this->m8C = 0.0f;
    this->m80 = 0.0f;
    this->m84 = 0.2617994f;
    this->m13E = 0;

    void** slot = (void**)((u8*)FUN_00b3d470() + 0xc4);
    if (*slot != 0) {
        void* obj = *(void**)((u8*)FUN_00b3d470() + 0xc4);
        ((void (__thiscall*)(void*, u32))VT(obj)[0xc / 4])(obj, 1);

        void** slot2 = (void**)((u8*)FUN_00b3d470() + 0xc4);
        void* q = *slot2;
        if (q != 0) {
            *slot2 = 0;
            ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
            return;
        }
    }
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

// @ 0x010187c0
namespace SP {
float cSPSpacePlanetCameraController_s0101_80e0::GetCurrentZoom()
{
  cPlayerInventory_s0101_80e0* pInventory = GetUFOSimulator_s0101_80e0()->GetPlayerInventory();
  const Vector3_s0101_80e0* pPos;
  if (pInventory->mbCameraOverride && (GameTimeManager_s0101_80e0()->mnFlags & 1) == 0) {
    pPos = &pInventory->mCameraOverridePos;
  } else {
    pPos = pInventory->mCamera.GetPosition();
  }
  return sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z);
}
}  // namespace SP

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

// @ 0x01019f50
void cSPSpacePlanetCameraController_s0101_9f50::SetSourceInterpolation(cViewer* viewer, float weight)
{
    mPrevEye = viewer->mEye;
    Matrix33 m(viewer->mCameraToWorldTransform);
    Quaternion_s0101_9f50 tmp;
    Quaternion_s0101_9f50 q = QuaternionFromMatrix33(tmp, m, 0.0f);
    mPrevOrientation = q;
    mBlendInTime = weight;
    mBlendIn = 0.0f;
}

// @ 0x0101a070
cCameraControllerBase::cCameraControllerBase(IRefCounted* target)
: mTarget(target),
      mField14(), m18(0), m1c(0), m20(0), m24(0), m28(0),
      mStopwatch(EA::Stopwatch_s0101_9f50::kUnitsCycles, false),
      m48(0), m4c(0), m50(0), m5c(0), m60(0.0f), m64(0.0f) {
}

// @ 0x0101a130
cSPSpaceCameraController::cSPSpaceCameraController(IRefCounted* target)
: cCameraControllerBase(target) {
    m68.x = kFacingDefaultX;
    m68.y = kFacingDefaultY;
    m68.z = kFacingDefaultZ;
    m80 = 0.0f;
    m84 = 0;
    m88 = 0;
    m8c.x = kFacingDefaultX;
    m8c.y = kFacingDefaultY;
    m8c.z = kFacingDefaultZ;
    m98.x = kFacingDefaultX;
    m98.y = kFacingDefaultY;
    m98.z = kFacingDefaultZ;
    ma4.x = kFacingDefaultX;
    ma4.y = kFacingDefaultY;
    ma4.z = kFacingDefaultZ;
    mb0 = 0.0f;
    mb4 = 0.0f;
    mb8 = 0.0f;
    mbc = 0.0f;
    mc0 = 0.0f;
    mc4 = 0.0f;
    mc8 = 0.0f;
    mcc = 0.0f;
    md0 = kFloatOne;
    md4[0] = 0; md4[1] = 0; md4[2] = 0; md4[3] = 0; md4[4] = 0; md4[5] = 0; md4[6] = 0;
}

// @ 0x0101a9d0
cSPSpacePlanetCameraController_s0101_9f50::cSPSpacePlanetCameraController_s0101_9f50(IRefCounted* target)
: cCameraControllerBase(target) {
    float dist = kCamDistance;
    mFOV = kCamFOV;
    mDistance = dist;
    mSurfaceDistance = dist;
    mPullOut = dist;
    mZoom = 0.0f;
    mLookAtHeight = 0.0f;
    mPullOutRight = 0.0f;
    mPullOutUp = 0.0f;
    float maxZoom = kCamMaxZoom;
    mMaxZoom = maxZoom;
    mPitch = maxZoom;
    mSnapTuning = false;
    mEyeDirection.x = kUFOForward_s0101_9f50.x;
    mEyeDirection.y = kUFOForward_s0101_9f50.y;
    mEyeDirection.z = kUFOForward_s0101_9f50.z;
    mAnchorDir.x = kFacingDefaultX;
    mAnchorDir.y = kFacingDefaultY;
    mAnchorDir.z = kFacingDefaultZ;
    mAC = 0.0f;
    mB0 = 0.0f;
    mEye.x = kFacingDefaultX;
    mEye.y = kFacingDefaultY;
    mEye.z = kFacingDefaultZ;
    mLookAt.x = kFacingDefaultX;
    mLookAt.y = kFacingDefaultY;
    mLookAt.z = kFacingDefaultZ;
    mZooming = false;
    mTuningBlend = 0.0f;
    mPrevEye.x = kFacingDefaultX;
    mPrevEye.y = kFacingDefaultY;
    mPrevEye.z = kFacingDefaultZ;
    mPrevOrientation.x = kIdentityOrient.x;
    mPrevOrientation.y = kIdentityOrient.y;
    mPrevOrientation.z = kIdentityOrient.z;
    mPrevOrientation.w = kIdentityOrient.w;
    mBlendIn = 0.0f;
    mBlendInTime = 0.0f;
    mMode = 0;
    mRotateLeft = false;
    mRotateRight = false;
    mApproachStart = false;
    mApproaching = false;
    mFlag13c = true;
    mApproachFrom.x = kFacingDefaultX;
    mApproachFrom.y = kFacingDefaultY;
    mApproachFrom.z = kFacingDefaultZ;
    mApproachTo.x = kFacingDefaultX;
    mApproachTo.y = kFacingDefaultY;
    mApproachTo.z = kFacingDefaultZ;
    mApproachBase.x = kWorldUp.x;
    mApproachBase.y = kWorldUp.y;
    mApproachBase.z = kWorldUp.z;
    mApproachUp.x = kWorldUp.x;
    mApproachUp.y = kWorldUp.y;
    mApproachUp.z = kWorldUp.z;
    mApproachOrientation.x = kIdentityOrient.x;
    mApproachOrientation.y = kIdentityOrient.y;
    mApproachOrientation.z = kIdentityOrient.z;
    mApproachOrientation.w = kIdentityOrient.w;
    mApproachTwist = 0.0f;
    mApproachAnchor.x = kFacingDefaultX;
    mApproachAnchor.y = kFacingDefaultY;
    mApproachAnchor.z = kFacingDefaultZ;
    m198 = 0;
    mApproachDone = true;
}

// @ 0x0101ad50
void cSPSpacePlanetCameraController_s0101_9f50::UpdateEffects()
{
    MessageServerT* server = MessageServer();
    if (server == 0)
        return;

    float altitude = 0.0f;
    PlanetModelUFO* ufo = PlanetModel()->mUFO;
    if (ufo != 0)
        altitude = ufo->v3()->mAltitude;

    GetUFOSimulator_s0101_9f50()->GetPlayerInventory();
    PlayerInventory* inv = GetUFOSimulator_s0101_9f50()->GetPlayerInventory();

    Vector3_s0101_9f50* position;
    if (inv->mShipLocked != 0 && (EffectGameTimeManagerFn()->mFlags & 1) == 0)
        position = &inv->mShipPosition;
    else
        position = inv->mBase.GetPosition();

    double sum = (double)position->x * (double)position->x
               + (double)position->y * (double)position->y
               + (double)position->z * (double)position->z;
    float maxDistance = kEffectMaxDistance;
    float distance = (float)sqrt(sum) - altitude;
    if (distance > kEffectMaxDistance)
        distance = kEffectMaxDistance;

    SlotMessage msg;
    msg.mArg = 0;
    msg.mVtable = vtbl_BehaviorMessage;
    _InterlockedExchange(&msg.mRefCount, 0);
    msg.mVtable = vtbl_SlotMessage;
    msg.mListenerMask = 0;
    msg.mPayloadA = distance;
    msg.mPayloadB = maxDistance;
    server->Post(0x60e4e46e, &msg, 0);
    msg.Destruct();
}

// @ 0x0101aea0
void UFO::aea0(float delta)
{
    char* s = (char*)raw;
    long long lVar = E_s0101_aea0(s + 0x30)->FUN_0093a3a0();
    float fVar12 = (float)lVar * *(float*)(s + 0x44);
    *(float*)(s + 0x64) = *(float*)(s + 0x60);

    // drop the stale prefix of the sample vector (8-byte {float t; char keep;} elements)
    UFO_Sample* begin = *(UFO_Sample**)(s + 0x48);
    UFO_Sample* end = *(UFO_Sample**)(s + 0x4c);
    if (begin != end) {
        char dl = ((char*)end)[-4];
        UFO_Sample* mark = begin;
        bool found = false;
        for (UFO_Sample* it = begin; it != end; ++it) {
            if (it->keep != dl || (fVar12 - it->t) > DAT_015b6da4) {
                mark = it + 1;
                found = true;
            }
        }
        if (found) {
            UFO_Sample* dst = begin;
            for (UFO_Sample* src = mark; src != end; ++src) *dst++ = *src;
            *(UFO_Sample**)(s + 0x4c) = end - (mark - begin);
        }
    }

    int mode = *(int*)(s + 0x5c);
    if (mode != 0) {
        float k = (mode == 1) ? DAT_01485720 : DAT_013eb1bc;
        int n = *(int*)(s + 0x4c) - *(int*)(s + 0x48);
        n >>= 3;
        float q = (float)(unsigned)n / DAT_015b6da0;
        q = q * delta;
        q = q * DAT_013fdf1c;
        float z = *(float*)(s + 0x60);
        *(float*)(s + 0x60) = z + (1.0f - expf(q)) * (k - z);
    } else {
        bool run = true;
        if (*(int*)(s + 0x48) != *(int*)(s + 0x4c)) {
            float d = fVar12 - (*(UFO_Sample**)(s + 0x4c))[-1].t;
            if (!(d > DAT_015b6d9c)) run = false;
        }
        if (run) {
            if (DAT_015b6d98 != 0) {
                float z = *(float*)(s + 0x60);
                float q = delta / DAT_015b6d94;
                q = q * DAT_013fdf1c;
                *(float*)(s + 0x60) = z - (1.0f - expf(q)) * z;
            } else {
                *(float*)(s + 0x60) = 0.0f;
            }
        }
    }

    float z = *(float*)(s + 0x60);
    if (z > DAT_01495934 && DAT_01495934 > *(float*)(s + 0x64)) {
        void* a = FUN_00a206f0();
        int r = a ? ((int(__thiscall*)(void*))VTP(a)[0x20 / 4])(a) : 0;
        void* b = FUN_00a206f0();
        if (b) {
            ((void(__thiscall*)(void*, int))VTP(b)[0x38 / 4])(b, 0x3475365);
            ((void(__thiscall*)(void*, int, int))VTP(b)[0x40 / 4])(b, 0x3475381, 0xfeb2337b);
            ((void(__thiscall*)(void*, int, int))VTP(b)[0x40 / 4])(b, 0x3475385, r);
            ((void(__thiscall*)(void*))VTP(b)[0x58 / 4])(b);
        }
        *(int*)(s + 0x5c) = 0;
        return;
    }
    if (DAT_013f89b8 > z && *(float*)(s + 0x64) >= DAT_013f89b8) {
        void* a = FUN_00a206f0();
        int r = a ? ((int(__thiscall*)(void*))VTP(a)[0x20 / 4])(a) : 0;
        FUN_00435ed0(0x5677db96, r);
    }
    *(int*)(s + 0x5c) = 0;
}

// @ 0x0101b0f0
void UFO::b0f0()
{
    char* s = (char*)raw;
    char* sw = s + 0x30;
    E_s0101_aea0(sw)->FUN_0093a1a0(5);
    u32 hi;
    if (*(int*)(sw + 0x10) == 1) {
        unsigned long long t = __rdtsc();
        *(u32*)sw = (u32)t;
        hi = (u32)(t >> 32);
    } else {
        unsigned long long t;
        QueryPerformanceCounter((long long*)&t);
        *(u32*)sw = (u32)t;
        hi = (u32)(t >> 32);
    }
    *(u32*)(sw + 4) = hi;
    *(u32*)(sw + 8) = 0;
    *(u32*)(sw + 0xc) = 0;
    UFO_SampleVec* vec = (UFO_SampleVec*)(s + 0x48);
    vec->FUN_Erase(vec->begin, vec->end);   // 0x00d018d0 eastl::vector::erase
    *(u32*)(s + 0x5c) = 0;
    *(float*)(s + 0x60) = 0.0f;
}

// @ 0x0101b160
void UFO::b160(float p2, float p3)
{
    char* s = (char*)raw;
    int ctx = FUN_01021080();
    float f = *(float*)(s + 0x68);
    float speed = -(p2 * p3);
    float lo = 0.0f;
    if (ctx == 1) lo = DAT_016dd3d0;
    else if (ctx == 2) lo = DAT_016dd384;
    float clampLo = lo;
    float hi = 0.0f;
    if (ctx == 1) hi = DAT_016dd3b4;
    else if (ctx == 2) hi = DAT_016dd374;
    float clampHi = hi;
    float nearT, farT;
    if (ctx == 1) {
        nearT = E_s0101_aea0(FUN_01021230())->FUN_00c8b800() ? DAT_016dd3cc : 400.0f;
        farT = DAT_016dd3b8;
    } else {
        nearT = DAT_016dd380;
        farT = DAT_016dd374;
    }

    void* inv = E_s0101_aea0(FUN_00ffbe50())->FUN_00a1ad60();
    float cur = *(float*)(s + 0xb4);
    char cKeep = *(char*)((char*)inv + 0x74c);
    bool near = DAT_01495934 > fabs(f - cur);
    bool outside = (cur <= lo) || (hi <= cur);
    *(char*)(s + 0xd5) = cKeep && near && outside;

    if (*(char*)(s + 0xd7) != 0) {
        if (f >= nearT && farT >= f && fabs(speed) > DAT_01495934 && (cur - f) * speed < 0.0f)
            *(char*)(s + 0xd7) = 0;
    }

    if (*(char*)(s + 0xd7) == 0) {
        E_s0101_aea0(FUN_00ffbe50())->FUN_00a1ad60();
        char trans;
        if (ctx == 1) trans = FUN_010422e0();
        else trans = FUN_01042450();
        if (!trans || f > nearT) {
            clampLo = nearT;
            *(char*)(s + 0xd9) = 0;
        } else if (f == nearT) {
            if (!*(char*)(s + 0xd9)) {
                *(char*)(s + 0xd9) = 1;
                b0f0();
                speed = 0.0f;
            }
        } else {
            *(char*)(s + 0xd7) = 1;
            *(float*)(s + 0xb4) = lo;
            FUN_01017fe0();
        }
        if (ctx != 1 || !FUN_010423d0() || f < farT) {
            clampHi = farT;
            *(char*)(s + 0xda) = 0;
        } else if (f == farT) {
            if (!*(char*)(s + 0xda)) {
                *(char*)(s + 0xda) = 1;
                b0f0();
                speed = 0.0f;
            }
        } else {
            *(char*)(s + 0xd7) = 1;
            *(float*)(s + 0xb4) = hi;
            FUN_01017fe0();
        }
    }

    *(char*)(s + 0xd6) = cKeep && near && *(float*)(s + 0xb4) == nearT && 0.0f > speed;

    if (*(char*)(s + 0xd7) == 0) {
        bool up = f > *(float*)(s + 0xb4);
        float v = E_s0101_aea0(s)->FUN_01017790(0, up) * speed + f;
        if (v < clampLo) v = clampLo;
        if (v > clampHi) v = clampHi;
        *(float*)(s + 0xb4) = v;
    }
}

// @ 0x0101b4c0
void UFO::b4c0(float f)
{
    char* s = (char*)raw;
    if (f > 0.0f) {
        *(float*)(s + 0xb4) = f;
        *(float*)(s + 0x68) = f;
    } else {
        *(float*)(s + 0x68) = *(float*)(s + 0xb4);
    }
    *(float*)(s + 0xb8) = 0.0f;
    *(u32*)(s + 0xa4) = DAT_016dd444;
    *(u32*)(s + 0xa8) = DAT_016dd448;
    *(u32*)(s + 0xac) = DAT_016dd44c;
    b0f0();
    *(u8*)(s + 0xd5) = 0;
}

// @ 0x0101b530
void UFO::b530(char param)
{
    char* s = (char*)raw;
    int ctx = FUN_01021080();
    float local_c = 0.0f, local_8 = 0.0f;
    if (ctx == 1) local_c = DAT_016dd3b4;
    else if (ctx == 2) local_c = DAT_016dd374;
    if (ctx == 1) local_8 = DAT_016dd3d0;
    else if (ctx == 2) local_8 = DAT_016dd384;
    float fv = ((float(__thiscall*)(void*))VTP(this)[0x5c / 4])(this);
    *(u8*)(s + 0xd7) = 1;
    *(u8*)(s + 0xd8) = 1;
    b0f0();
    int iVar2 = DAT_016dd36c;
    int iVar3 = DAT_016dd370;
    if (ctx == 1) { iVar2 = DAT_016dd3ac; iVar3 = DAT_016dd3b0; }
    if (param == 0) {
        *(float*)(s + 0xb4) = local_8;
        if (!iVar3 || iVar2 < 1) return;
        int i = iVar2 - 1;
        if (i < 0) return;
        while (!(fv > *(float*)(iVar3 + i * 4))) {
            if (--i < 0) return;
        }
        *(float*)(s + 0xb4) = *(float*)(iVar3 + i * 4);
    } else {
        *(float*)(s + 0xb4) = local_c;
        if (!iVar3 || iVar2 < 1) return;
        int i = 0;
        while (!(*(float*)(iVar3 + i * 4) > fv)) {
            if (++i >= iVar2) return;
        }
        *(float*)(s + 0xb4) = *(float*)(iVar3 + i * 4);
    }
}

// @ 0x0101b670
void UFO::b670(float param)
{
    char* s = (char*)raw;
    void* inv = E_s0101_aea0(FUN_00ffbe50())->FUN_00a1ad60();
    if (!inv) return;
    if (!E_s0101_aea0(inv)->FUN_00c37170()) return;
    void* tm = FUN_00b3d4d0();
    if (*(int*)((char*)tm + 0x2c) == 1 || *(int*)((char*)tm + 0x2c) == 2) return;

    float camDist = E_s0101_aea0(FUN_00c37360())->FUN_00fb7ba0();
    float radius = E_s0101_aea0(FUN_00b3d350())->FUN_00b7e4d0();
    float farDist = radius + DAT_016dd3ec;
    float nearDist = DAT_016dd3e8 + radius;

    float x = *(float*)((char*)inv + 0x718);
    float y = *(float*)((char*)inv + 0x71c);
    float z = *(float*)((char*)inv + 0x720);
    float dist = sqrtf(x * x + y * y + z * z);
    float minDist = FUN_00c375d0((float*)E_s0101_aea0(s)->FUN_0107b70_getUFO()) + camDist;

    float ratio = (dist - minDist) / (nearDist - minDist);
    float clamped = ratio;
    if (clamped < 0.0f) clamped = 0.0f;
    if (clamped > 1.0f) clamped = 1.0f;
    float rampT = (DAT_016dd414 - DAT_016dd418) * clamped + DAT_016dd418;

    float alt = *(float*)(s + 0x8c);
    if (alt == 0.0f) alt = E_s0101_aea0(s)->FUN_01017d30();
    float height = E_s0101_aea0(inv)->FUN_00c37120();
    float absAlt = fabs(alt);

    if (absAlt > 0.1f) {
        void* q = FUN_0067cac0();
        int* o = *(int**)((char*)q + 0x4c);
        if (o && o[2] == 0x1930f01e) {
            E_s0101_aea0(q)->FUN_0067c8c0(0x1930f01e, 1);
            E_s0101_aea0(FUN_010666a0())->FUN_01065d20();
        }
    }
    if (*(char*)(s + 0x13d) != 0) {
        if (fabs(dist - height) < 1.0f) *(char*)(s + 0x13d) = 0;
    }

    char canRamp = FUN_01044920();
    if (*(char*)(s + 0x13d) == 0) {
        if (!canRamp || nearDist > dist) {
            *(char*)(s + 0x13e) = 0;
        } else if (dist == nearDist) {
            if (!*(char*)(s + 0x13e)) {
                *(char*)(s + 0x13e) = 1;
                b0f0();
                E_s0101_aea0(inv)->FUN_00c3daa0(nearDist);
                return;
            }
        } else {
            *(char*)(s + 0x13d) = 1;
            *(char*)(s + 0x13e) = 0;
            *(u8*)(s + 0x194) = 1;
            E_s0101_aea0(inv)->FUN_00c3daa0(height * 2.0f);
            return;
        }
        if (absAlt > DAT_01495934) {
            param = (height - dist) * DAT_015b6da8 + dist - alt * clamped * param;
            float* pMax = &param;
            if (minDist > param) pMax = &minDist;
            E_s0101_aea0(inv)->FUN_00c3daa0(*pMax);
        }
        if (*(float*)(s + 0x60) > 0.0f || *(float*)(s + 0x8c) > 0.0f) *(u8*)(s + 0x194) = 0;
        else if (*(float*)(s + 0x60) < 0.0f || *(float*)(s + 0x8c) < 0.0f) *(u8*)(s + 0x194) = 1;
    }
    if (canRamp) param = FUN_00b0f060(DAT_016dd3e4, DAT_016dd3e0, dist - radius);
    else param = 0.0f;
    E_s0101_aea0(FUN_00ffbe50())->FUN_00ffe3d0(param, *(u8*)(s + 0x194));
}

// @ 0x0101b9e0
void UFO::b9e0()
{
    char* s = (char*)raw;
    char b = 0;
    *(u8*)(s + 0x194) = b;
    if (*(u8*)(s + 0x140) != b) b0f0();
    *(u8*)(s + 0xcc) = b;
    *(u8*)(s + 0x13e) = b;
}

// @ 0x0101ba10
void UFO::ba10(char param)
{
    char* s = (char*)raw;
    void* inv = E_s0101_aea0(FUN_00ffbe50())->FUN_00a1ad60();
    b0f0();
    *(u8*)(s + 0x13d) = 1;
    if (param != 0) {
        void* model = FUN_00b3d350();
        float f = E_s0101_aea0(model)->FUN_00b7e4d0();
        E_s0101_aea0(inv)->FUN_00c3daa0((f + DAT_016dd3e8) * 2.0f);
        *(u8*)(s + 0x194) = 1;
        return;
    }
    char* p = (char*)inv + 0x750;
    void* model = FUN_00b3d350();
    float f = E_s0101_aea0(model)->FUN_00b7ef70(p);
    void* pm = FUN_00c37360();
    float f2 = E_s0101_aea0(pm)->FUN_00fb7ba0();
    float v = f2 + f2 + f;
    float h = E_s0101_aea0(inv)->FUN_00c37120();
    if (v < h) {
        E_s0101_aea0(inv)->FUN_00c3daa0(v);
        *(u8*)(s + 0x194) = 0;
        return;
    }
    *(u8*)(s + 0x194) = 0;
}

// @ 0x0101bad0
void UFO::bad0(int a, int b)
{
    (void)b;
    int v = a;
    int local = 100;
    int* p = &v;
    if (v >= 100) p = &local;
    aea0((float)*p * 0.001f);
}

// @ 0x0101bb10
char UFO::bb10(int a, int b, int c, int d)
{
    (void)b; (void)c; (void)d;
    char* s = (char*)raw;
    if (a == 0) return 0;
    UFO_Sample smp;
    smp.raw = E_s0101_aea0(s + 0x30)->FUN_0093a3a0();
    smp.t = (float)smp.raw * *(float*)(s + 0x44);
    smp.keep = (a > 0);
    UFO_Sample* end = *(UFO_Sample**)(s + 0x4c);
    if (end < *(UFO_Sample**)(s + 0x50)) {
        *(UFO_Sample**)(s + 0x4c) = end + 1;
        if (end) *end = smp;
    } else {
        ((UFO_SampleVec*)(s + 0x48))->FUN_00B534C0(end, &smp);
    }
    *(int*)(s + 0x5c) = (a < 1) + 1;
    return 0;
}

// @ 0x0101bb90
void UFO::bb90(int param2, char param3)
{
    char* s = (char*)raw;
    void* planet = FUN_01021260();
    void* inv = E_s0101_aea0(FUN_00ffbe50())->FUN_00a1ad60();
    E_s0101_aea0(FUN_00ffbe50())->FUN_00ffe3d0(0.0f, 1);

    float buf[3];
    float* a = FUN_0059aed0(buf, (void*)param2,
                            ((void*(__thiscall*)(void*))VTP(planet)[0x30 / 4])(planet));
    float v[3];
    v[0] = a[0];
    v[1] = a[1];
    v[2] = a[2];
    FUN_01042480((float*)(s + 0x68), v);

    b0f0();
    b4c0(DAT_016dd3c8);

    float* p = FUN_0105c3d0(buf, planet, E_s0101_aea0(inv)->FUN_00c3ae70());
    *(float*)(s + 0x98) = *(float*)((char*)inv + 0x718) + p[0];
    *(float*)(s + 0x9c) = *(float*)((char*)inv + 0x71c) + p[1];
    *(float*)(s + 0xa0) = *(float*)((char*)inv + 0x720) + p[2];

    *(int*)(s + 0x88) = 1;
    *(float*)(s + 0xb4) = DAT_016dd3c4;
    *(u8*)(s + 0xd7) = 1;
    if (param3 != 0) {
        ((void(__thiscall*)(void*, int))VTP(this)[0x64 / 4])(this, 1);
        *(u8*)(s + 0xd8) = 0;
    }

    void* mgr = FUN_00b3d470();
    void** slot = (void**)((char*)mgr + 0xc4);
    if (*slot) {
        mgr = FUN_00b3d470();
        slot = (void**)((char*)mgr + 0xc4);
        void* obj = *slot;
        ((void(__thiscall*)(void*, int))VTP(obj)[0xc / 4])(obj, 1);
        mgr = FUN_00b3d470();
        slot = (void**)((char*)mgr + 0xc4);
        void* old = *slot;
        if (old) {
            *slot = 0;
            ((void(__thiscall*)(void*))VTP(old)[4 / 4])(old);
        }
    }
}

// @ 0x0101bd10
void SP::cSPCameraControllerSolarSystem_s0101_bd10::snapToHome()
{
    if (mZoom == 0.0f) {
        mZoom = 100.0f;
        mF70 = SP::gCamQuarterPi;
    }
    // The view offset is one Vector3 in the original (mZoom/mF6c/mF70 are its lanes).
    mSavedZoom = *(const Vector3*)&mZoom;

    mFocus = SP::kCamOrigin;
    mFocusVel = SP::kCamOrigin;

    if (SP::IsCivOutsideRange(SP::GetPlayerCiv()->GetContext())) {
        mState = 4;
        SetCameraDistance(SP::gCamK3bc);
        mTargetZoom = SP::gCamK3c0;
        mSnapped = true;
        if (mResetPending) {
            v64(0);
            mResetPending = false;
        }
    } else {
        SetCameraDistance(SP::gCamK3b8);
    }

    if (SP::GetStage()->mC4) {
        SP::GetStage()->mC4->v0c(1);
        SP::GetStage()->mC4.reset();
    }
}

// @ 0x0101be60
void SP::cSPCameraControllerSolarSystem_s0101_bd10::snapToSystem()
{
    mFocus = SP::kCamOrigin;
    mFocusVel = SP::kCamOrigin;

    int ctx = SP::GetPlayerCiv()->GetContext();
    if (ctx == 2)
        SetCameraDistance(SP::gCamK3d0);
    else
        SetCameraDistance(SP::gCamK3cc);
    mTargetZoom = SP::gCamK3b8;
    mSnapped = true;

    if (SP::GetStage()->mC4) {
        SP::GetStage()->mC4->v0c(1);
        SP::GetStage()->mC4.reset();
    }
}

// @ 0x0101bf40
void SP::cSPCameraControllerSolarSystem_s0101_bd10::restoreSavedView()
{
    SP::cSPGameDataUFO_s0101_bd10* ufo = SP::GetUFOSimulator_s0101_bd10()->GetPlayerInventory();
    Vector3 offset;
    Vector3* pos = SP::ComputeUFOOffsetPos(&offset, (int)SP::GetPlayerCiv(), ufo->GetScale());

    mFocus.x = ufo->mSavedPos.x + pos->x;
    mFocus.y = ufo->mSavedPos.y + pos->y;
    mFocus.z = ufo->mSavedPos.z + pos->z;
    mFocusVel = SP::kCamOrigin;

    // The view offset is one Vector3 in the original (mZoom/mF6c/mF70 are its lanes).
    *(Vector3*)&mZoom = mSavedZoom;

    SetCameraDistance(SP::gCamK37c);
    mTargetZoom = SP::gCamK378;
    mSnapped = true;
    if (mResetPending) {
        v64(1);
        mResetPending = false;
    }

    if (SP::GetStage()->mC4) {
        SP::GetStage()->mC4->v0c(1);
        SP::GetStage()->mC4.reset();
    }
}

// @ 0x0101c080
void SP::cSPCameraControllerSolarSystem_s0101_bd10::Update(int ms, SP::cViewer_s0101_bd10* viewer)
{
    int ctx = SP::GetUniverseContext();
    FUN_0101aea0((float)Min_s0101_bd10(ms, 100) * 0.001f);

    uint32_t clamped = Min_s0101_bd10(ms, 100);
    float dtms = (float)clamped;
    ms = (int)clamped;
    float dt = dtms * 0.001f;

    SP::cSPGameDataUFO_s0101_bd10* ufo = SP::GetUFOSimulator_s0101_bd10()->GetPlayerInventory();
    int mode = SP::GetStage()->mMode;
    if (mode != 1 && mode != 2 && !SP::SpaceGameGet()->IsFrozen())
        FUN_0101b160(mF60, dt);

    float zoom = GetZoom();
    float lo = 0.0f;
    if (ctx == 1)
        lo = SP::gCamK3d0;
    else if (ctx == 2)
        lo = SP::gCamK384;
    float hi = 0.0f;
    if (ctx == 1)
        hi = SP::gCamK3b4;
    else if (ctx == 2)
        hi = SP::gCamK374;
    float range[2];
    range[1] = lo;
    range[0] = hi;
    float frac = (zoom - lo) / (hi - lo);

    float nearV = SP::gCamK43c;
    float farV = SP::gCamK438;
    float angle = SP::gCamK434;
    float p, q;
    if (ctx == 2) {
        p = SP::gCamK354;
        q = SP::gCamK358;
        angle = (p - q) * frac + q;
    } else if (ctx == 1) {
        nearV = 1.0f;
        q = SP::gCamK350;
        p = SP::gCamK34c;
        angle = (p - q) * frac + q;
    }
    viewer->SetNear(nearV);
    viewer->SetFar(farV);
    viewer->SetViewAngle(angle);

    float* pZoom = &mZoom;
    if (fabsf(mZoom - mTargetZoom) < 1.5258789e-05f)
        mSnapped = false;
    if (!mSnapped) {
        if (*pZoom > lo && hi > *pZoom)
            FUN_01017390();
    }
    bool follow;
    if (mSnapped) {
        if (ctx == 1) {
            if (zoom > SP::gCamK3b8)
                mState = 3;
            else if (SP::gCamK3cc > zoom)
                mState = 2;
        } else {
            if (SP::gCamK380 > zoom)
                mState = 4;
        }
    } else {
        if (ctx == 2 && mState == 3)
            mState = 0;
    }
    follow = (ctx == 1) && (mState == 4 || mState == 1);

    Vector3 P;
    P.x = SP::gCamK444;
    P.y = SP::gCamK448;
    P.z = SP::gCamK44c;
    if (follow) {
        SP::cSpatialObject_s0101_bd10* planet = SP::GetActivePlanet();
        if (planet) {
            const Vector3* pos = planet->GetPosition();
            P.x = pos->x; P.y = pos->y; P.z = pos->z;
        }
        if (!mSnapped && ufo->mHasPos) {
            float dx = mFocus.x - P.x, dy = mFocus.y - P.y, dz = mFocus.z - P.z;
            if (0.04f > dx * dx + dy * dy + dz * dz)
                mState = 0;
        }
    } else if (mState == 2) {
        const Vector3* pos = ufo->mSpatial.GetPosition();
        P.x = pos->x; P.y = pos->y; P.z = pos->z;
    } else if (!ufo->mHasPos) {
        P.x = ufo->mSavedPos.x; P.y = ufo->mSavedPos.y; P.z = ufo->mSavedPos.z;
    } else if (ctx == 2) {
        SP::cSpaceLocation* loc = SP::GetHomeLocation();
        if (loc) {
            const Vector3* pos = loc->GetPosition();
            P.x = pos->x; P.y = pos->y; P.z = pos->z;
        }
    } else if (ctx == 1) {
        SP::cSpatialObject_s0101_bd10* planet = SP::GetActivePlanet();
        if (planet) {
            const Vector3* pos = planet->GetPosition();
            P.x = pos->x; P.y = pos->y; P.z = pos->z;
        }
    }

    SP::UpdateFocus(&mFocus, &mFocusVel, &P, SP::gCamC1, SP::gCamC1 * 0.001f, dtms);
    float v = FUN_01017790(mSnapped, *pZoom > mTargetZoom) * 0.001f;
    SP::UpdateZoom(pZoom, mZoomVel, mTargetZoom, v, SP::gCamC2 * v, dtms);

    if (!mSnapped) {
        float z = *pZoom;
        z = MaxSS(z, range[1]);
        z = MinSS(z, range[0]);
        *pZoom = z;
    }

    Vector3 t3;
    t3.x = *pZoom;
    t3.y = pZoom[1];
    t3.z = pZoom[2];
    if (ctx == 1) {
        if (!SP::GetHomeLocation()->IsKnown() && SP::gCamMinZoom > t3.x)
            t3.x = SP::gCamMinZoom;
    }
    if (SP::gCamShake) {
        SP::gCamPhase = dt + SP::gCamPhase;
        float w = SP::gCamK430 * SP::gCamPhase;
        float half = *pZoom * 0.5f;
        float s = (float)sin(w);
        t3.x = s * SP::gCamK424 + t3.x;
        if (half > t3.x)
            t3.x = half;
        t3.y = (float)sin(SP::gCamK42c * SP::gCamPhase) * SP::gCamK420 + t3.y;
        t3.z = (float)sin(SP::gCamPhase * SP::gCamK428) * SP::gCamK41c + t3.z;
        if (0.01f > t3.z)
            t3.z = 0.01f;
    }

    Vector3 dir;
    SP::OffsetFromZoom(&dir, &t3);
    FUN_0101a330(ms, 0);
    Vector3 out;
    FUN_010180e0(&out, mFocus, dir, 0);
    Vector3 target;
    target.x = out.x + dir.x;
    target.y = out.y + dir.y;
    target.z = out.z + dir.z;
    float matrix[16];
    SP::BuildCameraMatrix(&target, &out, &SP::kCamUp, matrix);
    viewer->SetCameraToWorld(matrix);
    SP::ResetEffectStates();
}

// @ 0x0101c780
namespace SP {
void cSPSpacePlanetCameraController_s0101_c780::FUN_0101c780(float a1, float* a2, float* a3, float* a4, float a5, int a6, float a7, float a8)
{
    (void)a5; (void)a6;

    Vec3_s0101_c780 P(a2[0], a2[1], a2[2]);
    if (Len3(P) >= PlanetModel_s0101_c780()->GetRadius() + g_1477fbc)
        return;

    // Bring up a camera frame for the current viewer.
    void* app = App();
    if (app != 0) {
        void* viewer = VCall0(app, 0x50);
        if (viewer != 0) {
            void* viewer2 = VCall0(viewer, 0x1c);
            cCameraFrame frame;
            frame.Initialize(viewer2);
        }
    }

    Vec3_s0101_c780 A(a3[0], a3[1], a3[2]);
    Vec3_s0101_c780 B(a4[0], a4[1], a4[2]);

    cShapeQuery query;
    query.origin = P;
    Vec3_s0101_c780 savedA = A;

    bool want_debug = (mWantDebugSolarPullOut != 0.0f) || (a7 != 0.0f);
    bool flag = false;
    bool moved = false;

    char hit = FUN_00b182f0(&query, 0x18);
    if (hit == 0) {
        hit = FUN_00b17c10(&query, 0);
        if (hit == 0)
            hit = FUN_00b17810(&query, 0);
    }
    if (hit != 0) {
        flag = true;
        moved = true;
    }

    if (want_debug && flag) {
        cSPSimulatorSpaceGame_s0101_c780* sim = (cSPSimulatorSpaceGame_s0101_c780*)GetUFOSimulator_s0101_c780();
        if (sim != 0)
            sim->GetPlayerInventory();

        float* ufo = GetUFOPosition();
        if (ufo != 0) {
            Vec3_s0101_c780 U(ufo[0], ufo[1], ufo[2]);
            float inv = 1.0f / Len3(U);
            float half = -(mWantDebugSolarPullOut * 0.5f);
            float s = (float)sin((double)half);
            float c = (float)cos((double)half);
            Vec4_s0101_c780 rotq(s * inv * U.x, s * inv * U.y, s * inv * U.z, c);

            float rotq_n[4];
            FUN_00799320(rotq_n, &rotq.x);

            Vec4_s0101_c780 galres;
            FUN_0059aed0(&galres.x, &mGalaxyZoom.x, rotq_n);
            mGalaxyZoom = Vec3_s0101_c780(galres.x, galres.y, galres.z);

            float neg = mPlanetFarZoomHeight * g_13eb1bc;
            Vec3_s0101_c780 target(A.x + galres.x * neg, A.y + galres.y * neg, A.z + galres.z * neg);

            Vec3_s0101_c780 axis = Cross3(target, A);
            float inv2 = 1.0f / Len3(axis);
            float half2 = -(mSolarZoomRateMax * 0.5f);
            float s2 = (float)sin((double)half2);
            float c2 = (float)cos((double)half2);
            Vec4_s0101_c780 rot2(s2 * inv2 * axis.x, s2 * inv2 * axis.y, s2 * inv2 * axis.z, c2);

            float rot2_n[4];
            FUN_00799320(rot2_n, &rot2.x);

            Vec3_s0101_c780 delta = Sub3(target, A);
            Vec4_s0101_c780 deltaq(delta.x, delta.y, delta.z, 0.0f);
            float out2[4];
            FUN_0059aed0(out2, &deltaq.x, rot2_n);
            Vec3_s0101_c780 p3(A.x + out2[0], A.y + out2[1], A.z + out2[2]);

            float solar_min = mSolarMinZoom;
            mCurrentMatrixYAxisX.u |= 1u;
            mSolarMinZoom = solar_min - a7;

            UpdateCameraPitchRotation(a1, a8, &A, &p3);
            savedA = A;
            query.FUN_00b17790(1);
        }
    }

    float clearance = 0.0f;
    if (FUN_00b181d0(&query, &clearance) != 0) {
        FUN_00b16490(&query, clearance);
        query.FUN_00b17790(1);
    }

    char bufA[0x100];
    char bufB[0x40];
    struct PathOut { void* p1; void* p2; void* p3; int pad; } po;
    po.p1 = bufA;
    po.p2 = bufA;
    po.p3 = bufB;
    po.pad = 0;
    if (FUN_00b17c10(&query, &po) != 0) {
        moved = true;
        FUN_00b16450(&query, &po);
        query.FUN_00b17790(1);
    }

    struct AuxOut { int pad; char data[0x80]; } aux;
    aux.pad = 0;
    if (FUN_00b17810(&query, &aux) != 0) {
        moved = true;
        FUN_00b16e50(&query, &aux);
        query.FUN_00b17790(1);
    }

    a2[0] = query.origin.x;
    a2[1] = query.origin.y;
    a2[2] = query.origin.z;
    a3[0] = savedA.x;
    a3[1] = savedA.y;
    a3[2] = savedA.z;

    if (moved)
        mSolarMinZoom = mSolarMinZoom - g_15b6dbc * a1;
}
}  // namespace SP

// @ 0x0101ec40
void S::FUN_0101ec40(void* param_2, void* param_3)
{
  char* self = (char*)this;

  void* ufo = FUN_00ffbe50();
  void* inv = ((void* (__thiscall*)(void*))FUN_00a1ad60)(ufo);

  int iVar2;
  if (*(char*)((char*)inv + 0x74c) != 0) {
    void* gt = FUN_00b3d380();
    if ((*(unsigned char*)((char*)gt + 0x48) & 1) == 0) {
      iVar2 = (int)inv + 0x750;
      goto L_ec80;
    }
  }
  {
    char* o = (char*)inv + 0x34;
    iVar2 = (*(int (__thiscall**)(void*))((char*)*(void**)o + 0x2c))(o);
  }

L_ec80:
  float* pf = (float*)(self + 0xb4);
  if (pf[0] == DAT_016dd444_s0101_ec40 && pf[1] == DAT_016dd448_s0101_ec40 && pf[2] == DAT_016dd44c_s0101_ec40) {
    self[0x68] = 1;
    ((void (__thiscall*)(void*, void*, void*))FUN_0101d130)(this, param_2, param_3);
  }

  float local_40[16];
  FUN_01043580(pf, (void*)iVar2, pf, local_40);

  ((void (__thiscall*)(void*, float))FUN_007c4ba0)(param_3, 2.0f);
  ((void (__thiscall*)(void*, float))FUN_007c4bc0)(param_3, 3000.0f);
  ((void (__thiscall*)(void*, float))FUN_007c5350)(param_3, *(float*)(self + 0x70));
  ((void (__thiscall*)(void*, float*))FUN_007c4c40)(param_3, local_40);

  ((void (__thiscall*)(void*))FUN_0101ad50)(this);

  float local_4c[3];
  FUN_01042480(local_4c, pf);

  if (FUN_00b3d280() != 0) {
    ((void (__thiscall*)(void*, float, float, float))FUN_00b10540)(FUN_00b3d280(), local_4c[1], local_4c[2], local_4c[0] * 0.5f);
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

// @ 0x01020eb0
void FUN_01020eb0(void* self, int param_2, int param_3)
{
    char* s = (char*)self;
    int local = 100;
    int* p = &param_2;
    if (param_2 >= 100) p = &local;
    FUN_00b3d380();
    (void)param_3;
}

// @ 0x01020fc0
void Cam::f20fc0()
{
    char* s = (char*)this;
    E(s)->FUN_0101fb40();
    void* edi = (s == 0) ? 0 : (s + 4);
    void* ms = FUN_0067dcc0();
    *(void**)(s + 0x18) = ms;
    *(void**)(s + 0x1c) = edi;
    *(void**)(s + 0x20) = &DAT_01495910;
    *(u32*)(s + 0x24) = 1;
    *(u32*)(s + 0x28) = 0;
    if (ms && edi)
        ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, edi, 0xf62def);
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
