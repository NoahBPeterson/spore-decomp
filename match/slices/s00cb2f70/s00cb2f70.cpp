// Slice s00cb2f70 - simulator serializable Write/Read, Object::Cast helpers,
// PathPrefsForTool and two navigation helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- vtable calls
struct VObj { void** vt; };

typedef void* (__thiscall *FnVp0)(void*);

// ---------------------------------------------------------------- externals
bool __cdecl EA_IO_WriteUint32(void* s, const void* p, uint32_t n, int endian); // 0x0093aa70
bool __cdecl EA_IO_ReadInt32(void* s, void* p, uint32_t n, int endian);         // 0x0093a780

extern char g_157d398;   // [0x0157d398]
extern char g_157d7d8;   // [0x0157d7d8]
extern char g_157dd7c;   // [0x0157dd7c]
extern char g_157ddb8;   // [0x0157ddb8]
extern char g_157e358;   // [0x0157e358]
extern char g_157e578;   // [0x0157e578]
extern char g_157e758;   // [0x0157e758]

// ---------------------------------------------------------------- object models
struct IStream;

// cGameData subobject: sits at offset 0 of every serializable object.
struct cGameData {
    void* mpVtbl;        // +0x00
    char  pad04[0x30];   // +0x04
    void __thiscall Write(IStream* s);   // 0x00b18590
    void __thiscall Read(IStream* s);    // 0x00b18600
};

// cLocomotiveObject subobject: at +0x34 of every projectile.
struct cLocomotiveObject {
    char  pad00[0x1000];
    void __thiscall Write(IStream* s);   // 0x00c448a0
    void __thiscall Read(IStream* s);    // 0x00c43c10
};

// cSpatialObject subobject.
struct cSpatialObject {
    char  pad00[0x1000];
    void __thiscall Write(IStream* s);   // 0x00c88a90
};

// ---------------------------------------------------------------- serializer
struct cDataSerializationInfo { char d[0x14]; };

class cVarListSerializer {
public:
    cDataSerializationInfo mInfos[128]; // +0x0000
    int      mSerializableVarCount;     // +0x0a00
    int      mSerializedVarCount;       // +0x0a04
    uint32_t mSignature;                // +0x0a08
    void*    mpObject;                  // +0x0a0c
    void*    mpSerializerList;          // +0x0a10

    cVarListSerializer(void* obj, void* list, uint32_t sig); // 0x00692f90
    bool __thiscall Serialize(IStream* s);                   // 0x00692900
    bool __thiscall SerializeRead(IStream* s);               // 0x00693e10
};

// Common prologue shared by all Write() bodies: writer lookup + type tag.
static inline void* StreamWriter(IStream* s) {
    return ((FnVp0)((VObj*)s)->vt[0x20 / 4])(s);
}
static inline void* WriterValue(void* w) {
    return ((FnVp0)((VObj*)w)->vt[0x18 / 4])(w);
}

// ---------------------------------------------------------------- 0x00cb36e0
struct cSPSpaceToolData {
    char pad00[0x150];
    char mb150;                                     // +0x150
    int __thiscall GetProjectileMotion();           // 0x0104bd90
};

// @ 0x00cb36e0
int __cdecl SP_PathPrefsForTool(cSPSpaceToolData* tool) {
    int result = 2;
    if (tool->mb150 != 0) {
        switch (tool->GetProjectileMotion()) {
        case 0x3307b570:              result = 5; break;
        case (int)0x82ce6992:         result = 2; break;
        case (int)0xa7172377:         result = 4; break;
        case 0x0ba57653:              result = 1; break;
        case (int)0x63aa81ae:         result = 3; break;
        case (int)0x6a93cd4e:         result = 1; break;
        }
    }
    return result;
}

// ---------------------------------------------------------------- 0x00cb3760
struct CSubCast {
    void* __thiscall Cast_00c41d00(int type);   // 0x00c41d00
    void* __thiscall Cast_00b18460(int type);   // 0x00b18460
    void* __thiscall Cast_00c884f0(int type);   // 0x00c884f0
    void* __thiscall Cast_00bfc380(int type);   // 0x00bfc380
    void* __thiscall Cast_00ac0320(int type);   // 0x00ac0320
};

struct CObj3760 {
    void* __thiscall Cast(int type);
};

// @ 0x00cb3760
void* CObj3760::Cast(int type) {
    if (type != 0x1428a48) {
        if (type != 0x142db2a) {
            void* r = ((CSubCast*)((char*)this + 0x34))->Cast_00c41d00(type);
            if (r == 0) {
                r = ((CSubCast*)this)->Cast_00b18460(type);
                if (r == 0)
                    r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
            }
            return r;
        }
        return this ? (char*)this + 0x504 : 0;
    }
    return this;
}

// ---------------------------------------------------------------- 0x00cb37d0
struct CArtilleryProjectile {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    bool __thiscall Write(IStream* s);
};

// @ 0x00cb37d0
bool CArtilleryProjectile::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x1428a48;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157d398, 0x1a80d26);
    ser.Serialize(s);
    return true;
}

// ---------------------------------------------------------------- 0x00cb3850
struct CArtilleryProjectileR {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    bool __thiscall Read(IStream* s);
};

// @ 0x00cb3850
bool CArtilleryProjectileR::Read(IStream* s) {
    uint32_t id;
    void* w = StreamWriter(s);
    void* v = WriterValue(w);
    EA_IO_ReadInt32(v, &id, 1, 0);
    mGameData.Read(s);
    mLoco.Read(s);
    cVarListSerializer ser(this, &g_157d398, 0x1a80d26);
    ser.SerializeRead(s);
    return true;
}

// ---------------------------------------------------------------- 0x00cb3940
struct CFlakProjectile {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};

// @ 0x00cb3940
void CFlakProjectile::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x240e3b7;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157d7d8, 0x1a80d26);
    ser.Serialize(s);
}

// ---------------------------------------------------------------- 0x00cb3ad0
struct CObj3ad0 {
    void* __thiscall Cast(int type);
};

// @ 0x00cb3ad0
void* CObj3ad0::Cast(int type) {
    if (type != 0x142db2a) {
        if (type != 0x244d3c0) {
            void* r = ((CSubCast*)((char*)this + 0x34))->Cast_00c41d00(type);
            if (r == 0) {
                r = ((CSubCast*)this)->Cast_00b18460(type);
                if (r == 0) {
                    r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
                    if (r == 0)
                        r = ((CSubCast*)((char*)this + 0x518))->Cast_00bfc380(type);
                }
            }
            return r;
        }
        return this;
    }
    return this ? (char*)this + 0x504 : 0;
}

// ---------------------------------------------------------------- 0x00cb3b70
struct CCulturalProjectile {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};

// @ 0x00cb3b70
void CCulturalProjectile::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x244d3c0;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157dd7c, 0x1a80d26);
    ser.Serialize(s);
}

// ---------------------------------------------------------------- 0x00cb3c80
struct CObj3c80 {
    void* __thiscall Cast(int type);
};

// @ 0x00cb3c80
void* CObj3c80::Cast(int type) {
    if (type != 0x142db2a) {
        if (type != 0x24630ce) {
            void* r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
            if (r == 0) {
                r = ((CSubCast*)this)->Cast_00b18460(type);
                if (r == 0)
                    r = ((CSubCast*)((char*)this + 0x11c))->Cast_00ac0320(type);
            }
            return r;
        }
        return this;
    }
    return this ? (char*)this + 0x108 : 0;
}

// ---------------------------------------------------------------- 0x00cb3d20
struct CResourceProjectile {
    cGameData      mGameData;    // +0x00
    cSpatialObject mSpatial;     // +0x34
    void __thiscall Write(IStream* s);
};

// @ 0x00cb3d20
void CResourceProjectile::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x24630ce;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mSpatial.Write(s);
    cVarListSerializer ser(this, &g_157ddb8, 0x1a80d26);
    ser.Serialize(s);
}

// ---------------------------------------------------------------- 0x00cb3e20
struct CObj3e20 {
    void* __thiscall Cast(int type);
};

// @ 0x00cb3e20
void* CObj3e20::Cast(int type) {
    if (type != 0x142db2a) {
        if (type != 0x4167194) {
            void* r = ((CSubCast*)this)->Cast_00b18460(type);
            if (r == 0)
                r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
            return r;
        }
        return this;
    }
    return this ? (char*)this + 0x108 : 0;
}

// ---------------------------------------------------------------- 0x00cb3e90
struct CDefaultAoEArea {
    cGameData      mGameData;    // +0x00
    cSpatialObject mSpatial;     // +0x34
    void __thiscall Write(IStream* s);
};

// @ 0x00cb3e90
void CDefaultAoEArea::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x4167194;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mSpatial.Write(s);
    cVarListSerializer ser(this, &g_157e358, 0x1a80d26);
    ser.Serialize(s);
}

// ---------------------------------------------------------------- 0x00cb3f80
// @ 0x00cb3f80
void __cdecl FUN_00cb3f80(float* a, float* b, float* c,
                          float* out1, float* out2, float* out3) {
    float f1  = c[0];
    float f2  = a[0];
    float f3  = b[0];
    float f4  = a[1];
    float f9  = f2 * f2;
    float f7  = f1 * f1;
    float f5  = b[1];
    float f6  = c[1];
    float f10 = f3 * f3;
    float f8  = ((((f7 * f3 - f7 * f2) + f10 * f2) - f10 * f1) + f9 * f1) - f9 * f3;

    *out1 = (((((f6 * f3 - f5 * f1) - f6 * f2) - f4 * f3) + f4 * f1) + f5 * f2) / f8;
    *out2 = -((((((f5 - f6) * f9 + f7 * f4) - f10 * f4) + f10 * f6) - f7 * f5) / f8);
    *out3 = (((((f9 * f1 - f7 * f2) * f5 + (f10 * f6) * f2) - (f10 * f4) * f1)
              - (f9 * f6) * f3) + (f7 * f4) * f3) / f8;
}

// ---------------------------------------------------------------- 0x00cb41c0
struct CCulturalProjectileW {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};

// @ 0x00cb41c0
void CCulturalProjectileW::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x4f76f08;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157e578, 0x1a80d26);
    ser.Serialize(s);
}

// ---------------------------------------------------------------- 0x00cb4350
struct CResourceProjectileW2 {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};

// @ 0x00cb4350
void CResourceProjectileW2::Write(IStream* s) {
    void* w = StreamWriter(s);
    uint32_t id = 0x5776a28;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157e758, 0x1a80d26);
    ser.Serialize(s);
}

// ---------------------------------------------------------------- 0x00cb2f70
// Navigation helper shared by the projectile steering path.  `raw` is the
// locomotive object at obj+0x14; `world` is raw's +0xb8 view (the spatial /
// simulator object); the per-object path data comes from FUN_00c41ec0.

typedef void*  (__thiscall *FnVp1i)(void*, int);
typedef float* (__thiscall *FnVp0p)(void*);
typedef void   (__thiscall *FnVp1v)(void*, void*);

struct PathSlot;

struct LocoSub34 {
    void** vt;                              // +0x00
    PathSlot* __thiscall FUN_00c41ec0();    // 0x00c41ec0
};

struct RawLoco {
    void** vt;                              // +0x00
    char   pad04[0x1a0 - 0x04];
    float  mf1a0;                           // +0x1a0
    PathSlot* __thiscall FUN_00c41ec0();    // 0x00c41ec0
    bool   __thiscall IsNearGoal();         // 0x00c42e20
};

struct SimWorld {
    char       pad00[0x34];
    LocoSub34  mSub;                        // +0x34
    char       pad38[0x21c - 0x38];
    float      mf21c;                       // +0x21c
    char       pad220[0x2a4 - 0x220];
    uint32_t   mFlags2a4;                   // +0x2a4
    char       pad2a8[0xb1c - 0x2a8];
    int        mB1c;                        // +0xb1c
    char       padB20[0xbcd - 0xb20];
    char       mbcd;                        // +0xbcd
    float __thiscall FUN_00c9ffd0(float* p); // 0x00c9ffd0
};

// Path data block returned by FUN_00c41ec0; the first dword pair is a byte
// range into the per-object route buffer (element stride 0x3c).
struct PathSlot {
    int   mBegin;                       // +0x00
    int   mEnd;                         // +0x04
    float mf08;                         // +0x08
    char  pad0c[0x14 - 0x0c];
    float mPos[3];                      // +0x14
    float mf20;                         // +0x20
    char  pad24[0x4c - 0x24];
    unsigned char mFlag4c;              // +0x4c
    char  pad4d[0x5c - 0x4d];
    int   mCount5c;                     // +0x5c
    char  pad60[0x68 - 0x60];
    int   mf68;                         // +0x68
    float mf6c;                         // +0x6c
};

struct NavObj { char pad00[0x14]; RawLoco* mp14; };

// Locomotion request builder (first block only uses its ctor + first dword).
struct LocoRequestLocal {
    void* mData;                            // +0x00
    void* __thiscall ctor();                // 0x00ac9850
};

// Locomotion request filled in and handed to LocoSub34::vt[0xdc].
struct LocoRequest {
    int   m00;                          // +0x00
    int   m04;                          // +0x04
    int   m08;                          // +0x08
    char  pad0c[0x14 - 0x0c];
    float mPos[3];                      // +0x14
    float mf20;                         // +0x20
    char  pad24[0x28 - 0x24];
    int   m28;                          // +0x28
    char  pad2c[0x50 - 0x2c];
    unsigned char m50;                  // +0x50
    char  pad51[0x54 - 0x51];
    float mf54;                         // +0x54
    float mf58;                         // +0x58
    float mf5c;                         // +0x5c
    int   m60;                          // +0x60
    float mf64;                         // +0x64
    char  pad68[0x6c - 0x68];
    float mf6c;                         // +0x6c
    float mf70;                         // +0x70
    int   m74;                          // +0x74
};

union FloatBytes4 { float f; unsigned char bytes[4]; };

extern float g_157d340;
extern float g_169a37c;
extern float g_169a380;
extern float g_169a384;
extern float g_147510c;

PathSlot*  __cdecl FUN_00cb1210(SimWorld* world);                                  // 0x00cb1210
void       __cdecl FUN_00cadb50(void* u);                                          // 0x00cadb50
bool       __cdecl FUN_00cadc20(NavObj* obj, SimWorld* w, float* pos, PathSlot* p); // 0x00cadc20
float      __cdecl FUN_00c9f380(SimWorld* world);                                  // 0x00c9f380
unsigned char __cdecl FUN_00c41ed0(float a, float b);                              // 0x00c41ed0
void       __cdecl FUN_00cadd50(NavObj* obj, SimWorld* w, PathSlot* p, float f, float d); // 0x00cadd50
bool       __cdecl FUN_00cb2480(SimWorld* w, PathSlot* p, float* a, float* b, void** c);  // 0x00cb2480
uint32_t   __cdecl FUN_00cb2770(SimWorld* w, float* a, PathSlot* p, float* b, float* c,
                                float* d, void** e);                               // 0x00cb2770
void       __cdecl FUN_00b47520(void* p);                                          // 0x00b47520
void       __cdecl operator_delete_array(void* p);                                 // 0x00f47380

// @ 0x00cb2f70
void __cdecl FUN_00cb2f70(NavObj* obj) {
    RawLoco* raw = obj->mp14;
    SimWorld* world;
    if (raw == 0)
        world = 0;
    else
        world = (SimWorld*)((FnVp1i)((VObj*)raw)->vt[0xb8 / 4])(raw, 0x137e8e0);

    float* pos = ((FnVp0p)((VObj*)raw)->vt[0x2c / 4])(raw);
    float mtx[12];
    ((FnVp1v)((VObj*)&world->mSub)->vt[0x5c / 4])(&world->mSub, mtx);

    PathSlot* p = raw->FUN_00c41ec0();
    int hasRoute = p->mCount5c;
    bool nearGoal = raw->IsNearGoal();

    float dz = p->mPos[2] - pos[2];
    float dy = p->mPos[1] - pos[1];
    float dx = p->mPos[0] - pos[0];
    float dist2 = (dz * dz + dy * dy) + dx * dx;
    float dist = sqrtf(dist2);

    bool noPath = (raw->mf1a0 == 0.0f);
    bool flag = (raw->mf1a0 > g_157d340) || noPath;
    if (world->mbcd != 0
        || ((pos[0] == g_169a37c && pos[1] == g_169a380 && pos[2] == g_169a384)
            || (hasRoute == 0 || nearGoal))) {
        flag = false;
    }

    FloatBytes4 arg;
    arg.f = 1.0f;

    if (hasRoute != 0) {
        if (noPath) {
            void* u = FUN_00cb1210(world);
            FUN_00cadb50(u);
            world->mFlags2a4 &= 0xfffffff4u;
            if (!FUN_00cadc20(obj, world, pos, p))
                return;
        }

        float ratio = FUN_00c9f380(world) / world->mf21c;
        float sel = (ratio > 1.0f) ? ratio : 1.0f;
        float scale = (p->mBegin == p->mEnd) ? p->mf20 : (sel * 2.0f);

        arg.f = scale;
        arg.bytes[0] = FUN_00c41ed0(dist * dist, scale);
        FUN_00cadd50(obj, world, p, arg.f, dist);

        float inv;
        if ((dz > dist
             && (inv = 1.0f / sqrtf(dist2 + 1e-08f),
                 0.9f > (mtx[1] * (dz * inv) + mtx[2] * (dy * inv)
                         + (inv * dx) * mtx[0])))
            || arg.bytes[0] != 0) {
            float* e = (float*)p->mBegin;
            if (e == (float*)p->mEnd) {
                LocoSub34* sub = &world->mSub;
                LocoRequestLocal req;
                void* r = req.ctor();
                ((FnVp1v)((VObj*)sub)->vt[0xdc / 4])(sub, r);
                int* rp = (int*)req.mData;
                if (rp != 0 && rp[-1] != 0)
                    operator_delete_array(rp);
                flag = false;
            }
            else {
                if (p->mFlag4c & 1)
                    flag = true;
                float* dst = p->mPos;
                for (int i = 0; i < 0xf; ++i)
                    dst[i] = e[i];
                FUN_00b47520(e);
                float ndx = p->mPos[0] - pos[0];
                dist = sqrtf((p->mPos[1] - pos[1]) * (p->mPos[1] - pos[1])
                             + ((p->mPos[2] - pos[2]) * (p->mPos[2] - pos[2])
                                + ndx * ndx));
            }
        }
    }

    float f1c = 1.0f;
    if (!flag || noPath || !(p->mFlag4c & 1)) {
        PathSlot* q = FUN_00cb1210(world);
        if (q->mEnd != 0 && q->mf08 < 1.0f)
            f1c = q->mf08;
    }
    else {
        flag = FUN_00cb2480(world, p, &dz, &f1c, (void**)&pos);
    }

    if (flag
        && FUN_00cb2770(world, &dz, p, &arg.f, &dist, &f1c, (void**)&pos) > 2) {
        raw->mf1a0 = 0.0f;
    }

    uint32_t flags = world->mFlags2a4;
    if (flags & 0xb) {
        LocoSub34* sub = &world->mSub;
        PathSlot* st = sub->FUN_00c41ec0();
        if (((flags & 2) == 0) || st->mf6c <= 2.0f) {
            if (st->mf6c <= 30.0f) {
                float* pp = ((FnVp0p)((VObj*)sub)->vt[0x2c / 4])(sub);
                LocoRequest req;
                req.m00 = 0;
                req.m04 = 0;
                req.m08 = 0;
                req.mPos[0] = pp[0];
                req.mPos[1] = pp[1];
                req.mPos[2] = pp[2];
                req.mf20 = 1.0f;
                req.m28 = 0;
                req.m50 = 0;
                req.mf54 = 0.0f;
                req.mf58 = 0.0f;
                req.mf5c = 0.0f;
                req.m60 = 1;
                req.mf64 = 2.0f;
                req.mf6c = g_147510c;
                req.mf70 = 0.0f;
                req.m74 = 0;
                ((FnVp1v)((VObj*)sub)->vt[0xdc / 4])(sub, &req);
                int* data = *(int**)&req;
                if (data != 0 && data[-1] != 0)
                    operator_delete_array(data);
            }
        }
        else {
            world->mFlags2a4 = flags & 0xfffffffdu;
        }
    }

    p->mf68 = (int)dist;
}

// ---------------------------------------------------------------- 0x00cb34d0
char* __cdecl PlanetModel();                              // 0x00b3d350
void  __cdecl FUN_00cae280(NavObj* obj);                  // 0x00cae280

struct Sim34d0 {
    char pad00[4];
    char mb4;                                             // +0x04
    void __thiscall FUN_00cb34d0(NavObj* obj);
};

// @ 0x00cb34d0
void Sim34d0::FUN_00cb34d0(NavObj* obj) {
    SimWorld* world;
    if (obj->mp14 == 0)
        world = 0;
    else
        world = (SimWorld*)((FnVp1i)((VObj*)obj->mp14)->vt[0xb8 / 4])(obj->mp14, 0x137e8e0);

    char* pm;
    if (world->mB1c != 1 || (pm = PlanetModel(), pm[0xf0] == 0)) {
        if (mb4 != 0) {
            PathSlot* p = obj->mp14->FUN_00c41ec0();
            if (p->mCount5c != 0) {
                int count = (int)(p->mEnd - p->mBegin) / 0x3c;
                if (count > 0) {
                    int off = 0;
                    do {
                        float* e = (float*)(p->mBegin + off);
                        float len = world->FUN_00c9ffd0(e);
                        float x = e[0], y = e[1], z = e[2];
                        float inv = 1.0f / sqrtf(((x * x + y * y) + z * z) + 1e-08f);
                        e[0] = (x * inv) * len;
                        e[1] = len * (y * inv);
                        e[2] = len * (z * inv);
                        off += 0x3c;
                    } while (--count != 0);
                }
                float* q = p->mPos;
                float len = world->FUN_00c9ffd0(q);
                float x = q[0], y = q[1], z = q[2];
                float inv = 1.0f / sqrtf(((x * x + y * y) + z * z) + 1e-08f);
                q[0] = (x * inv) * len;
                q[1] = (y * inv) * len;
                q[2] = (z * inv) * len;
            }
            mb4 = 0;
        }
        FUN_00cb2f70(obj);
        FUN_00cae280(obj);
    }
}
