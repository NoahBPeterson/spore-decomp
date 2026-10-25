// src/game/SPGonzago/SPRotationRingView.cpp -- migrated from slice(s) s00e91ce0, s00e90e00 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPRotationRingView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "EA/ResourceMan/Key.h"
#include "SP/cRotationRing.h"
#include "SP/cSpatialObject.h"
#include <float.h>
#include <string.h>

// ---- items of slice s00e90e00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
void* __cdecl FUN_0067de30();                                       // 0x0067de30
void  __cdecl FUN_006bb5e0();                                       // 0x006bb5e0
void  __cdecl FUN_006bb600();                                       // 0x006bb600
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
struct cModel {
    void*    mpObj;        // +0x00
    union {
        uint32_t mFlags;       // +0x04 (dword view)
        uint8_t  mFlagBytes[4];// +0x04 (byte view)
        struct { uint32_t mPadBit : 15; uint32_t mwFlagF : 1; };  // bit 15
        struct { uint32_t mPadBit2 : 14; uint32_t mwFieldE : 1; }; // bit 14
        struct { unsigned char mbFlag0 : 1; };                    // bit 0 (byte unit)
    };
    uint16_t mField08;     // +0x08
    uint16_t mField0a;     // +0x0a
    uint8_t  pad_0c[0x0c];
    float    mField18;     // +0x18
    uint8_t  pad_1c[0x24];
    uint32_t mRefCount;    // +0x40
    uint8_t  pad_44[0x08];
    V3       mColor;       // +0x4c
    float    mField58;     // +0x58
    uint8_t  pad_5c[0x30];
    float    mField8c;     // +0x8c
    uint8_t  pad_90[0x63c - 0x90];
    uint32_t mField63c;    // +0x63c
    uint32_t mField640;    // +0x640
    float    mField644;    // +0x644
    float    mField648;    // +0x648
    uint8_t  pad_64c[0x0c];
    uint32_t mField658;    // +0x658
    uint8_t  mbField65c;   // +0x65c
    uint8_t  mbField65d;   // +0x65d
    uint8_t  pad_65e[0x02];
    float    mField660;    // +0x660
};
struct cSpatialObject;
class cViewA {
public:
    virtual void v00();

    cViewA();                                   // 0x00e915d0
    ~cViewA();                                  // 0x00e915f0

    bool  GetFlag0();                           // 0x00e91400
    void  Update_916a0(int a, int b);           // 0x00e916a0
    void  SetModelFlag(bool b);                 // 0x00e91ba0
    void  SetFlag0(bool b);                     // 0x00e91bd0
    bool  GetFlagF();                           // 0x00e91bf0

    uint32_t mField04;                          // +0x04
    uint32_t mField08;                          // +0x08
    cSpatialObject* mpObject;                   // +0x0c
    void*    mpField10;                         // +0x10
    cModel*  mModel;                            // +0x14
    uint32_t mField18;                          // +0x18
};
class cRotationRingView {
public:
    virtual void v00(void*);

    cRotationRingView();                        // 0x00e91c10
    ~cRotationRingView();                       // 0x00e91c30

    uint32_t mField04;                          // +0x04
    uint32_t mField08;                          // +0x08
    cSpatialObject* mpObject;                   // +0x0c
    void*    mpGameDataView;                    // +0x10
    cModel*  mModel;                            // +0x14
    uint32_t mAnimID;                           // +0x18
    int      mLifeTimer;                        // +0x1c
};
// ---- items of slice s00e90e00 end

// ---- items of slice s00e91ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix33 { float m[9]; };
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
uint32_t __cdecl SPIDFromName(const char* name);                        // 0x00571cf0
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
float __cdecl GetPropertyF(uint32_t group, int a, uint32_t prop, float def);  // 0x00bcea30
V3* __cdecl GetPropertyV3a(V3* out, uint32_t group, int a, uint32_t prop, V3 def); // 0x00e91410
V3* __cdecl GetPropertyV3b(V3* out, uint32_t group, int a, uint32_t prop, V3 def); // 0x00e914f0
int __cdecl GetPropertyI(uint32_t group, int a, uint32_t prop, int def);      // 0x00bda3b0
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);               // 0x00f473a0
void* __cdecl GonzagoModelWorld();                                       // 0x00b3d520
void* __cdecl GetCurrentGameMode();                                      // 0x00b5b800
void  Matrix3Assign(void* dst, const void* src);                         // 0x0041cb40
void* Matrix3FromFacingAndUp(void* out, const void* facing, const void* up); // 0x0069b440
void* Mat3MulV3(void* out, const void* m, const void* v);                // 0x0059aed0
void* cSPTransformAssign(void* self, const void* src);                   // 0x00537dc0
float __cdecl pow_f(double x, double y);                                 // 0x011e08f0
const float  f_13ec4b8 = 1e-08f;
const float  f_147b9f0 = 30.0f;
const float  f_13ebc68 = 1.0f;
class cRotationRing {
public:
virtual void v00();
virtual void v04();
virtual void* v08();
virtual void* v0c();
virtual void  v10();
virtual void  v14();
virtual void v18();
virtual void  v1c();
virtual void  v20();
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void* v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
virtual void  v58();
virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void* v70();
};
class cRotationRingView_s00e9_1ce0 {
public:
virtual void v00(void*);
virtual void v04(int);
    virtual cRotationRingView_s00e9_1ce0* MakeView(void* gamedata);   // +0x08
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();

    float GetRingAnimationPercentage(float param);   // 0x00e91ce0
    void  HandleSimulationUpdate(int a, int b);      // 0x00e91e40

    uint32_t mField04;                       // +0x04
    uint32_t mField08;                       // +0x08
    cRotationRing* mpObject;                 // +0x0c
    void*    mpGameDataView;                 // +0x10
    void*    mModel;                         // +0x14
    uint32_t mAnimID;                        // +0x18
    int      mLifeTimer;                     // +0x1c
};
#define VC0(R, o, off)               ((R (__thiscall*)(void*))VF(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)       ((R (__thiscall*)(void*, T1))VF(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VF(o, off))((void*)(o), (a1), (a2))
// ---- items of slice s00e91ce0 end

// @ 0x00e91400
bool cViewA::GetFlag0()
{
    return mModel->mbFlag0;
}

// @ 0x00e91410
V3* __cdecl GetPropertyV3a(V3* out, uint32_t group, int a, uint32_t prop, V3 def)
{
    void* guard = 0;
    void* obj = FUN_0067de30();
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);

    bool ok = ((bool(__thiscall*)(void*, uint32_t, int, void**))VF(obj, 0x2c))
                  (obj, group, a, &guard);
    if (ok) {
        void* val = 0;
        if (((bool(__thiscall*)(void*, uint32_t, void**))VF(guard, 0x24))(guard, prop, &val)) {
            void* src;
            uint16_t ty = *(uint16_t*)((char*)val + 0x12);
            if (ty == 0x31 || ty == 0x10) {
                if (*(uint8_t*)((char*)val + 0x10) & 0x30)
                    src = *(void**)val;
                else
                    src = (ty != 0) ? val : 0;
            } else {
                FUN_006bb5e0();
                src = 0;
            }
            float* f = (float*)src;
            out->x = f[0];
            out->y = f[1];
            out->z = f[2];
        } else {
            *out = def;
        }
    } else {
        *out = def;
    }
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);
    return out;
}

// @ 0x00e914f0
V3* __cdecl GetPropertyV3b(V3* out, uint32_t group, int a, uint32_t prop, V3 def)
{
    void* guard = 0;
    void* obj = FUN_0067de30();
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);

    bool ok = ((bool(__thiscall*)(void*, uint32_t, int, void**))VF(obj, 0x2c))
                  (obj, group, a, &guard);
    if (ok) {
        void* val = 0;
        if (((bool(__thiscall*)(void*, uint32_t, void**))VF(guard, 0x24))(guard, prop, &val)) {
            void* src;
            uint16_t ty = *(uint16_t*)((char*)val + 0x12);
            if (ty == 0x32 || ty == 0x10) {
                if (*(uint8_t*)((char*)val + 0x10) & 0x30)
                    src = *(void**)val;
                else
                    src = (ty != 0) ? val : 0;
            } else {
                FUN_006bb600();
                src = 0;
            }
            float* f = (float*)src;
            out->x = f[0];
            out->y = f[1];
            out->z = f[2];
        } else {
            *out = def;
        }
    } else {
        *out = def;
    }
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);
    return out;
}

// @ 0x00e915d0
cViewA::cViewA()
{
    mField08 = 0;
    mField04 = 0;
    *(void**)this = (void*)0x1486a80;
    mpObject = 0;
    mpField10 = 0;
    mModel = 0;
    mField18 = 0;
}

// @ 0x00e915f0
cViewA::~cViewA()
{
    cModel* m = mModel;
    *(void**)this = (void*)0x1486a80;
    ((void(__thiscall*)(void*, void*, int))VF(m->mpObj, 0x16c))(m->mpObj, m, 0);

    m = mModel;
    if (m != 0) {
        mModel = 0;
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    m = mModel;
    if (m != 0) {
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    void* p = mpField10;
    if (p != 0)
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    cSpatialObject* o = mpObject;
    if (o != 0)
        ((void(__thiscall*)(void*))VF(o, 4))(o);
    *(void**)this = (void*)0x1455648;
}

// @ 0x00e91ba0
void cViewA::SetModelFlag(bool b)
{
    cModel* m = mModel;
    if (m == 0)
        return;
    void* o = m->mpObj;
    typedef void (__thiscall* Fn)(void*, void*, int);
    if (b)
        ((Fn)VF(o, 0x16c))(o, m, 1);
    else
        ((Fn)VF(o, 0x16c))(o, m, 0);
}

// @ 0x00e91bd0
void cViewA::SetFlag0(bool b)
{
    uint32_t* f = &mModel->mFlags;
    if (b)
        *f |= 1u;
    else
        *f &= 0xfffffffeu;
}

// @ 0x00e91bf0
bool cViewA::GetFlagF()
{
    bool b;
    if (mModel != 0) {
        b = (mModel->mFlags >> 0xf) & 1;
    } else {
        b = true;
    }
    return b;
}

// @ 0x00e91c10
cRotationRingView::cRotationRingView()
{
    mField08 = 0;
    mField04 = 0;
    *(void**)this = (void*)0x1486b1c;
    mpObject = 0;
    mpGameDataView = 0;
    mModel = 0;
    mAnimID = 0;
    mLifeTimer = 0;
}

// @ 0x00e91c30
cRotationRingView::~cRotationRingView()
{
    cModel* m = mModel;
    *(void**)this = (void*)0x1486b1c;
    ((void(__thiscall*)(void*, void*, int))VF(m->mpObj, 0x16c))(m->mpObj, m, 0);

    m = mModel;
    if (m != 0) {
        mModel = 0;
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    m = mModel;
    if (m != 0) {
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    void* p = mpGameDataView;
    if (p != 0)
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    cSpatialObject* o = mpObject;
    if (o != 0)
        ((void(__thiscall*)(void*))VF(o, 4))(o);
    *(void**)this = (void*)0x1455648;
}

// @ 0x00e91ce0
float cRotationRingView_s00e9_1ce0::GetRingAnimationPercentage(float param)
{
    if (GetCurrentGameMode() == (void*)0x01654c10) {
        cRotationRing* obj = mpObject;
        if (obj != 0)
            return VC0(float, obj, 0x68) * 0.01f;
    }
    else {
        cRotationRing* obj = mpObject;
        if (param != 0.0f) {
            cRotationRing* other = *(cRotationRing**)((char*)(uintptr_t)param + 0xc);
            if (other != 0)
                obj = other;
        }
        if (obj != 0) {
            float scale = GetPropertyF(id("CommunityEditor"), 0,
                                       id("CityRotationHandleRadiusScaleFactor"),
                                       *(float*)0x1486b88);
            void* pi = (void*)VC0(void*, obj, 0x70);
            if (pi != 0) {
                if (VC1(int, pi, 0xc, uint32_t, 0x4f396a66) != 0)
                    scale = GetPropertyF(id("CommunityEditor"), 0,
                                         id("TribeRotationHandleRadiusScaleFactor"),
                                         *(float*)0x1486b5c);
            }
            return VC0(float, obj, 0x68) * scale;
        }
    }
    return GetPropertyF(id("CommunityEditor"), 0,
                        id("RotationHandleRadiusDefault"), *(float*)0x13fe160);
}

// @ 0x00e91e40
void cRotationRingView_s00e9_1ce0::HandleSimulationUpdate(int a, int b)
{
    (void)a; (void)b;
    cRotationRing* obj = mpObject;
    if (obj == 0)
        return;

    if (VC0(int, obj, 0x58) == 0) {
        *(uint32_t*)((char*)mModel + 4) &= 0xfffffffeu;
        mLifeTimer = 0;
        return;
    }
    *(uint32_t*)((char*)mModel + 4) |= 1u;

    float ringScale = GetPropertyF(id("CommunityEditor"), 0,
                                   id("CityRotationRingScaleFactor"), f_13ebc68);
    V3 ringOffset;
    GetPropertyV3a(&ringOffset, id("CommunityEditor"), 0,
                   id("CityRotationRingOffset"), *(V3*)0x016c5ac0);

    if (GetCurrentGameMode() != (void*)0x01654c10) {
        void* pi = (void*)VC0(void*, mpObject, 0x70);
        if (pi != 0 && VC1(int, pi, 0xc, uint32_t, 0x4f396a66) != 0) {
            ringScale = GetPropertyF(SPIDFromName("CommunityEditor"), 0,
                                     SPIDFromName("TribeRotationRingScaleFactor"),
                                     f_147b9f0);
            GetPropertyV3a(&ringOffset, SPIDFromName("CommunityEditor"), 0,
                           SPIDFromName("TribeRotationRingOffset"), *(V3*)0x016c5ac0);
        }
    }

    VC0(void, (char*)mpObject + 0x34, 0x30);

    void* mw = (void*)VC0(void*, mpObject, 0x58);
    V3 off2;
    Mat3MulV3(&off2, &ringOffset, (void*)VC0(void*, mw, 0x30));

    void* mw2 = (void*)VC0(void*, mpObject, 0x58);
    V3 base;
    memcpy(&base, (void*)VC1(void*, mw2, 0x2c, void*, 0), sizeof(V3));

    void* mw3 = (void*)VC0(void*, mpObject, 0x58);
    V3 dir;
    VC1(void, mw3, 0x60, void*, &dir);
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + f_13ec4b8);
    V3 ndir;
    ndir.x = dir.x * inv;
    ndir.y = inv * dir.y;
    ndir.z = inv * dir.z;

    Matrix33 mat;
    Matrix3Assign(&mat, (void*)0x016c5afc);

    V3 sum;
    sum.x = base.x + off2.x;
    sum.y = base.y + off2.y;
    sum.z = base.z + off2.z;

    V3 upv;
    VC1(void, (void*)VC0(void*, mpObject, 0x58), 0x5c, void*, &upv);
    V3 faceOut;
    Matrix3FromFacingAndUp(&faceOut, &ndir, &upv);

    // transform message (0x38 bytes): flags/modcount/translation/scale/rotation
    struct Xform {
        uint16_t flags;      // +0x00
        uint16_t modcount;   // +0x02
        V3       trans;      // +0x04
        float    scale;      // +0x10
        Matrix33 rot;        // +0x14
    } xf;
    xf.flags = 6;
    xf.modcount = 2;
    xf.trans = sum;
    xf.scale = 1.0f;
    memcpy(&xf.rot, &faceOut, sizeof(Matrix33));
    cSPTransformAssign((char*)mModel + 8, &xf);

    uint32_t* modc = (uint32_t*)((char*)mModel + 0xc);
    (void)modc;
    *(uint16_t*)((char*)mModel + 0xa) += 1;
    *(float*)((char*)mModel + 8 + 0x10) = base.x;

    bool rollover = false;
    if (!VC0(bool, mpObject, 0x80) && !VC0(bool, mpObject, 0x24))
        rollover = false;
    else
        rollover = true;

    V3 color;
    if (!rollover)
        GetPropertyV3b(&color, id("CommunityEditor"), 0, id("HandleColorDefault"),
                       *(V3*)0x1486aa4);
    else
        GetPropertyV3b(&color, id("CommunityEditor"), 0, id("HandleColorRollover"),
                       *(V3*)0x1486ab8);
    void* model = mModel;
    *(V3*)((char*)model + 0x4c) = color;

    float f0 = 0.0f;
    float f1 = 0.0f;
    void* gw = GonzagoModelWorld();
    VC2(void, gw, 0x80, void*, mModel, void*, 0);   // (model, animID, &f0, &f1, 0)
    (void)f0; (void)f1;

    float pct = GetRingAnimationPercentage(0.0f);
    int popMs = GetPropertyI(id("CommunityEditor"), 0, id("RotationHandlePopTimeMS"), 200);
    double dd = pow_f((double)mLifeTimer, (double)popMs);
    float v = (float)(dd * (1.0 - 0.0) * pct + 0.0);
    void* gw2 = GonzagoModelWorld();
    VC2(void, gw2, 0x74, void*, mModel, void*, 0);  // (model, animID, v, 0)
    (void)v;
    void* gw3 = GonzagoModelWorld();
    VC1(void, gw3, 0x10c, void*, mModel);
    mLifeTimer++;
    if ((uint32_t)popMs < (uint32_t)mLifeTimer)
        mLifeTimer = popMs;
}

// @ 0x00e923b0
cRotationRingView_s00e9_1ce0* cRotationRingView_s00e9_1ce0::MakeView(void* gamedata)
{
    cRotationRingView_s00e9_1ce0* view = (cRotationRingView_s00e9_1ce0*)operator_new_sp(
        0x20, "Simulator/cRotationRingView", 0, 0, 0, 0);
    if (view != 0) {
        view->mField04 = 0;
        view->mField08 = 0;
        *(void**)view = (void*)0x1486b1c;
        view->mField08 = 0;
        view->mField04 = 0;
        view->mpObject = 0;
        view->mpGameDataView = 0;
        view->mModel = 0;
        view->mAnimID = 0;
        view->mLifeTimer = 0;
    }
    else {
        view = 0;
    }
    // assign gamedata view with refcount
    void* old = view->mpGameDataView;
    if (gamedata != old) {
        if (gamedata != 0)
            (*(void(__thiscall**)(void*))gamedata)(gamedata);       // AddRef
        view->mpGameDataView = gamedata;
        if (old != 0)
            (*(void(__thiscall**)(void*, int))(*(void**)old))(old, 0);  // Release+? via slot 1
    }
    (void)view;
    return view;
}
