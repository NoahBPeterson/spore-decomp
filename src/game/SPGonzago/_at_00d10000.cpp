// src/game/SPGonzago/_at_00d10000.cpp -- migrated from slice(s) s00d1f650, s00d1e930, s00d1df40, s00d1cdf0, s00d14460 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d10000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include <stddef.h>
#include "SP/cRotationRing.h"
#include "SP/cGameData.h"
#include "cSPUILayout.h"
#include "SP/cSpatialObject.h"
#include "SP/cCommunity.h"
#include "SP/cCity.h"
#include "SP/cSPCreatureBase.h"
#include <math.h>
#include <wchar.h>
#include "EA/Variant.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cLocalInputState.h"
#include "SP/cTribe.h"

// ---- items of slice s00d14460 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSpatial {
    virtual void  p000();                                   // +0x00
    virtual void  p004();                                   // +0x04
    virtual void  p008();                                   // +0x08
    virtual void  p00c();                                   // +0x0c
    virtual void  p010();                                   // +0x10
    virtual void  p014();                                   // +0x14
    virtual void  p018();                                   // +0x18
    virtual void  p01c();                                   // +0x1c
    virtual void  p020();                                   // +0x20
    virtual void  p024();                                   // +0x24
    virtual void  p028();                                   // +0x28
    virtual void* GetPosition();                            // +0x2c
    virtual void  p030();                                   // +0x30
    virtual void  p034();                                   // +0x34
    virtual void  SetPosition(const void* pPosition);       // +0x38
    virtual void  SetOrientation(const void* pMatrix);      // +0x3c
};
struct cNoun {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04 (release)
    virtual void* v008();                                   // +0x08
    virtual void* v00c(uint32_t nType);                     // +0x0c (cast)
    virtual void  v010();                                   // +0x10
    virtual void  v014();                                   // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void  v038();                                   // +0x38
    virtual void  v03c();                                   // +0x3c
    virtual void  v040();                                   // +0x40
    virtual void  v044();                                   // +0x44
    virtual void  v048();                                   // +0x48
    virtual void  v04c();                                   // +0x4c
    virtual void  v050();                                   // +0x50
    virtual void  v054();                                   // +0x54
    virtual void  v058();                                   // +0x58
    virtual void  v05c();                                   // +0x5c
    virtual void  v060();                                   // +0x60
    virtual void  v064();                                   // +0x64
    virtual void  v068();                                   // +0x68
    virtual void  v06c();                                   // +0x6c
    virtual void  v070();                                   // +0x70
    virtual void  v074();                                   // +0x74
    virtual void  v078();                                   // +0x78
    uint8_t       mPad004[0x30];                            // +0x04 .. +0x33
    cSpatial      mSpatial;                                 // +0x34
    uint8_t       mPad038[0xd0];                            // +0x38 .. +0x107
    int32_t       mDefA;                                    // +0x108
    int32_t       mDefB;                                    // +0x10c
    int32_t       mDefC;                                    // +0x110
    int32_t       mDefD;                                    // +0x114
    int32_t       mValueCount;                              // +0x118
    int32_t       mValues[64];                              // +0x11c
};
struct cGameNounManager {
    void* mpVTable;                                         // +0x00
    uint8_t mPad004[0x34];                                  // +0x04 .. +0x37
    void* GetGameDataVector(void* pA, void* pB, void* pC, void* pD, void* pE);   // 0x00b21340
    void  RemoveNoun();                                     // 0x00b225d0
    void* CreateNoun(uint32_t nType);                       // 0x00b22640
};
struct cNounList {
    uint8_t mPad00[0x04];                                   // +0x00 .. +0x03
    cNoun** mpBegin;                                        // +0x04
    cNoun** mpEnd;                                          // +0x08
};
cGameNounManager* __cdecl SP_GetNounManager();              // 0x00b3d300 (global form)
void   __stdcall FUN_010829f0(void* pArg);                  // 0x010829f0
// ---- items of slice s00d14460 end

// ---- items of slice s00d1cdf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char* s);
extern char  gEmptyStr16[];      // 0x01667bac  shared eastl empty string
extern char  gEmptyStr16b[];     // 0x01667bad  &gEmptyStr16 + 1
extern void* gCurrentRot_169dda4; // 0x0169dda4
extern float gDefVec_169dd88;    // 0x0169dd88  default (1,0,0)-ish vector
extern float gDefVec_169dd8c;    // 0x0169dd8c
extern float gDefVec_169dd90;    // 0x0169dd90
extern float gDefUp_169dd94;     // 0x0169dd94
extern float g_c5_1486110;       // 0x01486110  5.0f
extern float g_c1_1485720;       // 0x01485720  1.0f
extern float g_c10_1473c70;      // 0x01473c70  10.0f
typedef unsigned int   uint;
typedef unsigned char  u8;
void  operator_delete_array(void* p);                     // 0x00f47380
void __fastcall cGameData_ctor(void* self);         // 0x00b18660
void __fastcall cSpatialObject_ctor(void* self);    // 0x00c89630
void __fastcall cSpatialObject_dtor(void* self);    // 0x00c8a420
void __fastcall cGameData_dtor(void* self);         // 0x00b184c0
struct cGameData {
    void* mpVtbl_00;
    void* mpVtbl_04;
    void Write(void* stream);      // 0x00b18590  (external)
    void Read(void* stream);       // 0x00b18600  (external)
};
void* __stdcall FUN_00b18460(int tag);              // 0x00b18460  tag cast helper
void* __cdecl FUN_0059aed0(float* out, const float* def, void* m); // 0x0059aed0
int   __cdecl WriteUint32(void* s, const void* p, int n, int f);   // 0x0093aa70
int   __cdecl ReadInt32(void* s, void* p, int n, int f);           // 0x0093a780
typedef void   (__thiscall *VFn0) (void*);
typedef void*  (__thiscall *VFnR) (void*);
typedef void   (__thiscall *VFn1) (void*, void*);
typedef void*  (__thiscall *VFnR1)(void*, void*);
typedef void   (__thiscall *VFn2) (void*, void*, void*);
typedef void   (__thiscall *VFn2F)(void*, void*, float);
typedef double (__thiscall *VFnD) (void*);
#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))
struct cSpatialObject {
    void* mpVtbl_00;             // +0x00  (0x1479fd0 / 0x147a128)
};
struct cGameModel {              // the object behind mpModel_108
    void* mpVtbl_00;             // +0x00
    u8    mPad_04[0x6b];         // +0x04
    u8    mbFlag_6f;             // +0x6f
    u8    mPad_70[0x14];         // +0x70
    float mf_84;                 // +0x84
};
struct EaString {                // eastl::basic_string<char>
    char* mpBegin_00;
    char* mpEnd_04;
    char* mpCap_08;
    void SetEmpty() { mpBegin_00 = gEmptyStr16; mpEnd_04 = gEmptyStr16; mpCap_08 = gEmptyStr16b; }
    void FreeIfOwned() {
        if (mpCap_08 - mpBegin_00 > 1 && mpBegin_00 != 0)
            operator_delete_array(mpBegin_00);
    }
    void assign(const char* first, const char* last);   // 0x00454cb0  (external)
};
struct cRotationRing;
struct cRotationObj {
    void*     mpVtbl_00;          // +0x000
    void*     mpVtbl_04;          // +0x004
    u8        mPad_08[0x2c];      // +0x008
    cSpatialObject mSpatial_34;   // +0x034
    u8        mPad_38[0x9c];      // +0x038
    void*     mpRuntime_0d4;      // +0x0d4  runtime/frame object
    u8        mPad_d8[0x4];       // +0x0d8
    char*     mpStr2Begin_dc;     // +0x0dc
    char*     mpStr2End_e0;       // +0x0e0
    u8        mPad_e4[0x24];      // +0x0e4
    cGameModel* mpModel_108;      // +0x108  current model (refcounted)
    u8        mPad_10c[0x4];      // +0x10c
    EaString  mName_110;          // +0x110
    u8        mPad_11c[0x4];      // +0x11c
    uint      mn_120;             // +0x120
    uint      mn_124;             // +0x124
    uint      mn_128;             // +0x128
    float     mf_12c;             // +0x12c
    void*     mp_130;             // +0x130
};
struct cRotationBall : cRotationObj {
    void* Cast(int tag);
    char  Write(void* stream);
    char  Read(void* stream);
    void* GetDefaultVec();
    void* SetThing5c(void* v);
    int   IsFlagSet();
    void  SetFlag(u8 v);
    void  SetThing64(void* v, float f);
    bool  IsCurrent();
    double GetRadius();
    void  SetModel(cGameModel* m, void* p);
    cRotationBall* InitBall();
    void  FiniBall();
    void  GetWorldPos(float* out);
};
struct cRotationRing : cRotationObj {
    void* Cast(int tag);
    char  Write(void* stream);
    void* GetDefaultVec2();
    void* SetThing6c(void* v);
    char  GetFlagR();
    void  CopyTo(EaString* dst);
    void  SetNameFromCStr(const char* s);
    cRotationRing* InitRing();
    void  FiniRing();
};
struct cRefObj {
    void* mpVtbl_00;              // +0x00
    void* mp_04;                  // +0x04
    void* mp_08;                  // +0x08
    cRefObj* Init(void* o);
    void Destroy();
};
struct cSPUILayoutObj {
    void Shutdown(unsigned flags);       // 0x00811ad0
};
extern void* gCurrentRot_169dda0; // 0x0169dda0
// ---- items of slice s00d1cdf0 end

// ---- items of slice s00d1df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*        gVtableE207;       // 0x0147a2b0
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
struct IRefS {
    PV                                           // 0x00
    virtual void Slot4();                        // 0x04
    virtual void Slot8();                        // 0x08
};
struct E207Obj {
    void* mpVtbl;                                      // +0x00
    void* mpA;                                         // +0x04
    void* mpB;                                         // +0x08
};
void  __cdecl OpDelete(void* p);                    // 0x00f47380
// ---- items of slice s00d1df40 end

// ---- items of slice s00d1e930 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* SP_NounManager();                                      // 0x00b3d300 cdecl
void* SP_PropertyManager();                                  // 0x0067de30 cdecl
void* SP_GetCurrentGameMode();                               // 0x00b5b800 cdecl
void* FUN_00f473a0(size_t, const char*, int, int, int, int); // 0x00f473a0 cdecl operator new
void  FUN_004d3760(void*);                                   // 0x004d3760 thiscall ctor
void  FUN_00f47380(void*);                                   // 0x00f47380 cdecl operator delete
char  FUN_004d92b0(void*, void*);                            // 0x004d92b0 cdecl ReadAbilityData
char  FUN_00685520(int);                                     // 0x00685520 cdecl
void  FUN_00555e80(void*, void*);                            // 0x00555e80 cdecl
void  FUN_00d1f160(uint32_t, uint32_t*, int, void**);        // 0x00d1f160 cdecl
__declspec(noinline) void __cdecl FUN_00d1f250(void**, uint32_t); // 0x00d1f250 cdecl
void* g_169de30[3];   // 0x0169de30
void* g_169de3c[2];   // 0x0169de3c
void* g_169de44[2];   // 0x0169de44
void* g_169de4c[6];   // 0x0169de4c
void* g_169de64[6];   // 0x0169de64
struct RCObj {
    virtual void vf0(int arg);      // vtable[0]  (destroy/release with a flag)
    int mRef;                       // +0x04
};
static inline void rc_release(RCObj* p)
{
    int n = p->mRef;
    p->mRef = --n;
    if (n == 0) {
        p->mRef = 1;
        p->vf0(1);
    }
}
struct PropList {
    virtual void vf0(int arg);      // vtable[0]
    virtual void vf1();             // vtable[1]  (release)
};
struct AbilitySet {
    RCObj* mArr00[3];   // +0x00
    RCObj* mArr0c[2];   // +0x0c
    RCObj* mArr14[2];   // +0x14
    RCObj* mArr1c[6];   // +0x1c
    RCObj* mArr34[6];   // +0x34
    void destroy();
};
struct cTerrainEditor {
    char  _p000[0x10fc];
    void* mpListA;                        // +0x10fc
    void* mpListB;                        // +0x1100
    bool  GetFlagValue(uint32_t id, int* outValue);      // 0x00c77380
    void  SetFlagValue(uint32_t id, uint32_t value);     // 0x00c79f00
    bool  HasFlagOrInsert(uint32_t id);                  // 0x00c77bf0
};
struct IdVec {                            // grow-able uint32 vector
    uint32_t* mpBegin;                    // +0x00
    uint32_t* mpEnd;                      // +0x04
    uint32_t* mpCap;                      // +0x08
};
char g_1654c01;                           // 0x01654c01  game-mode tag
char g_1654c02;                           // 0x01654c02
void* FUN_00f67d90();                     // 0x00f67d90 thiscall GetCurrentTerrainSphere
// ---- items of slice s00d1e930 end

// ---- items of slice s00d1f650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_gameModeTribe2;    // 0x01654c02
struct cGameNounManager_s00d1_f650 {
    void* GetPlayerTribe();                    // 0x00bfc5f0
};
struct cTribe {
    int   GetToolOfType(int type);             // 0x00c8f6e0
};
void*  GetCurrentGameMode();                 // 0x00b5b800
void*  NounManager();                        // 0x00b3d300
unsigned char FUN_00d1f400(void* p);         // 0x00d1f400 cdecl
// ---- items of slice s00d1f650 end

// @ 0x00d15090
void __stdcall FUN_00d15090(void* pArg)
{
    FUN_010829f0(pArg);
    if (*(void**)0x0168d248) {
        cGameNounManager* pManager = SP_GetNounManager();
        cNounList* pList = (cNounList*)pManager->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                                   (void*)0x00acdff0, (void*)0x00b1e500,
                                                                   (void*)0x018c43e8);
        int32_t nCount = (int32_t)(pList->mpEnd - pList->mpBegin);
        cNoun*** pppBegin = &pList->mpBegin;
        for (int32_t i = 0; i < nCount; ++i)
            (*pppBegin)[i]->v078();
    }
}

// @ 0x00d1d4d0
void* cRotationBall::Cast(int tag)
{
    if (tag == 0x7292112)
        return this;
    if (tag == 0x1186577)
        return this ? (void*)((char*)this + 0x34) : 0;
    return FUN_00b18460(tag);
}

// @ 0x00d1d540
char cRotationBall::Write(void* stream)
{
    void* impl = (*(VFnR)VSLOT(stream, 0x20))(stream);
    uint tag = 0x7292112;
    void* iface = (*(VFnR)VSLOT(impl, 0x18))(impl);
    WriteUint32(iface, &tag, 1, 0);
    ((cGameData*)this)->Write(stream);
    cGameModel* m = mpModel_108;
    if (m) {
        void* r = (*(VFnR1)VSLOT(m, 0xb8))(m, (void*)0x179c807);
        (*(VFn1)VSLOT(stream, 0x2c))(stream, r);
    } else {
        (*(VFn1)VSLOT(stream, 0x2c))(stream, 0);
    }
    return 1;
}

// @ 0x00d1d5c0
void cRotationBall::GetWorldPos(float* out)
{
    if (!mpModel_108) {
        out[0] = gDefVec_169dd88;
        out[1] = gDefVec_169dd8c;
        out[2] = gDefVec_169dd90;
        return;
    }
    float* a = (float*)(*(VFnR)VSLOT(mpModel_108, 0x2c))(mpModel_108);
    float ax = a[0], ay = a[1], az = a[2];
    void* mtx = (*(VFnR)VSLOT(mpModel_108, 0x30))(mpModel_108);
    float local[3];
    float* b = (float*)FUN_0059aed0(local, &gDefUp_169dd94, mtx);
    float bx = b[0], by = b[1], bz = b[2];
    void* r = (*(VFnR)VSLOT(mpModel_108, 0xac))(mpModel_108);
    if (r) {
        double s = (*(VFnD)VSLOT(mpModel_108, 0x34))(mpModel_108) * *(float*)((char*)r + 0x84);
        float fs = (float)s;
        ax = bx * fs + ax;
        ay = by * fs + ay;
        az = bz * fs + az;
    }
    out[0] = bx * g_c10_1473c70 + ax;
    out[1] = by * g_c10_1473c70 + ay;
    out[2] = bz * g_c10_1473c70 + az;
}

// @ 0x00d1d740
char cRotationBall::Read(void* stream)
{
    void* impl = (*(VFnR)VSLOT(stream, 0x20))(stream);
    int tag = 0;
    void* iface = (*(VFnR)VSLOT(impl, 0x18))(impl);
    ReadInt32(iface, &tag, 1, 0);
    ((cGameData*)this)->Read(stream);
    void* obj = 0;
    (*(VFn2)VSLOT(stream, 0x28))(stream, (void*)0x179c807, &obj);
    if (obj) {
        cGameModel* casted = (cGameModel*)(*(VFnR1)VSLOT(obj, 0xc))(obj, (void*)0x1186577);
        cGameModel* old = mpModel_108;
        if (casted != old) {
            if (casted) (*(VFn0)VSLOT(casted, 0xbc))(casted);
            mpModel_108 = casted;
            if (old) (*(VFn0)VSLOT(old, 0xc0))(old);
        }
    } else {
        cGameModel* old = mpModel_108;
        if (old) {
            mpModel_108 = 0;
            (*(VFn0)VSLOT(old, 0xc0))(old);
        }
    }
    if (obj) (*(VFn0)VSLOT(obj, 4))(obj);
    return 1;
}

// @ 0x00d1d810
cRotationBall* cRotationBall::InitBall()
{
    cGameData_ctor(this);
    cSpatialObject* sp = &mSpatial_34;
    cSpatialObject_ctor(sp);
    mpVtbl_00 = (void*)0x147a0a8;
    mpVtbl_04 = (void*)0x147a094;
    sp->mpVtbl_00 = (void*)0x1479fd0;
    mpModel_108 = 0;
    mName_110.SetEmpty();
    mn_124 = 0x2f4e681b;
    mn_128 = 0x40606000;
    mn_120 = 0x0ca40c72;
    return this;
}

// @ 0x00d1d930
void* cRotationBall::GetDefaultVec()
{
    void* rt = mpRuntime_0d4;
    if (rt)
        return (*(VFnR)VSLOT(rt, 0x2c))(rt);
    return (void*)&gDefVec_169dd88;
}

// @ 0x00d1d950
void* cRotationBall::SetThing5c(void* v)
{
    void* rt = mpRuntime_0d4;
    (*(VFn1)VSLOT(rt, 0x5c))(rt, v);
    return v;
}

// @ 0x00d1d990
int cRotationBall::IsFlagSet()
{
    cGameModel* m = mpModel_108;
    if (m && m->mbFlag_6f != 0)
        return 1;
    return 0;
}

// @ 0x00d1d9b0
void cRotationBall::SetFlag(u8 v)
{
    mpModel_108->mbFlag_6f = v;
}

// @ 0x00d1d9e0
void cRotationBall::SetThing64(void* v, float f)
{
    void* rt = mpRuntime_0d4;
    (*(VFn2F)VSLOT(rt, 0x64))(rt, v, f);
}

// @ 0x00d1da10
void* cRotationRing::SetThing6c(void* v)
{
    void* rt = mpRuntime_0d4;
    (*(VFn1)VSLOT(rt, 0x6c))(rt, v);
    return v;
}

// @ 0x00d1da60
void cRotationBall::FiniBall()
{
    cSpatialObject* sp = &mSpatial_34;
    mpVtbl_00 = (void*)0x147a0a8;
    mpVtbl_04 = (void*)0x147a094;
    sp->mpVtbl_00 = (void*)0x1479fd0;
    mName_110.FreeIfOwned();
    if (mpModel_108)
        (*(VFn0)VSLOT(mpModel_108, 0xc0))(mpModel_108);
    cSpatialObject_dtor(sp);
    cGameData_dtor(this);
}

// @ 0x00d1dac0
void cRotationRing::SetNameFromCStr(const char* s)
{
    mName_110.assign(s, s + strlen(s));
}

// @ 0x00d1db10
void* cRotationRing::Cast(int tag)
{
    if (tag == 0x2ee8eeb)
        return this;
    if (tag == 0x1186577)
        return this ? (void*)((char*)this + 0x34) : 0;
    return FUN_00b18460(tag);
}

// @ 0x00d1db40
void cRotationBall::SetModel(cGameModel* m, void* p)
{
    cGameModel* old = mpModel_108;
    if (m != old) {
        if (m) (*(VFn0)VSLOT(m, 0xbc))(m);
        mpModel_108 = m;
        if (old) (*(VFn0)VSLOT(old, 0xc0))(old);
    }
    if (!m)
        (*(VFn1)VSLOT(this, 0x6c))(this, 0);
    else
        (*(VFn1)VSLOT(this, 0x6c))(this, p);
}

// @ 0x00d1dba0
char cRotationRing::Write(void* stream)
{
    void* impl = (*(VFnR)VSLOT(stream, 0x20))(stream);
    uint tag = 0x2ee8eeb;
    void* iface = (*(VFnR)VSLOT(impl, 0x18))(impl);
    WriteUint32(iface, &tag, 1, 0);
    ((cGameData*)this)->Write(stream);
    cGameModel* m = mpModel_108;
    if (m) {
        void* r = (*(VFnR1)VSLOT(m, 0xb8))(m, (void*)0x179c807);
        (*(VFn1)VSLOT(stream, 0x2c))(stream, r);
    } else {
        (*(VFn1)VSLOT(stream, 0x2c))(stream, 0);
    }
    return 1;
}

// @ 0x00d1dc20
cRotationRing* cRotationRing::InitRing()
{
    cGameData_ctor(this);
    cSpatialObject* sp = &mSpatial_34;
    cSpatialObject_ctor(sp);
    mpVtbl_00 = (void*)0x147a200;
    mpVtbl_04 = (void*)0x147a1ec;
    sp->mpVtbl_00 = (void*)0x147a128;
    mpModel_108 = 0;
    mName_110.SetEmpty();
    mp_130 = 0;
    mf_12c = 0.0f;
    mn_124 = 0x2f4e681b;
    mn_128 = 0x40606000;
    mn_120 = 0x0c1ef506;
    return this;
}

// @ 0x00d1dd30
bool SP::cRotationRing::GetIsHighlightedManipulator() const
{
    return gCurrentRot_169dda0 == (void*)this;
}

// @ 0x00d1dd70
double cRotationBall::GetRadius()
{
    cGameModel* m = mpModel_108;
    if (m)
        return (*(VFnD)VSLOT(m, 0x74))(m) + g_c5_1486110;
    float one = g_c1_1485720;
    return one;
}

// @ 0x00d1ddb0
void* cRotationRing::GetDefaultVec2()
{
    void* rt = mpRuntime_0d4;
    if (rt)
        return (*(VFnR)VSLOT(rt, 0x2c))(rt);
    return (void*)&gCurrentRot_169dda4;
}

// @ 0x00d1dde0
char cRotationRing::GetFlagR()
{
    return (char)mpModel_108->mbFlag_6f;
}

// @ 0x00d1de10
void cRotationRing::FiniRing()
{
    cSpatialObject* sp = &mSpatial_34;
    mpVtbl_00 = (void*)0x147a200;
    mpVtbl_04 = (void*)0x147a1ec;
    sp->mpVtbl_00 = (void*)0x147a128;
    mName_110.FreeIfOwned();
    if (mpModel_108)
        (*(VFn0)VSLOT(mpModel_108, 0xc0))(mpModel_108);
    cSpatialObject_dtor(sp);
    cGameData_dtor(this);
}

// @ 0x00d1de70
void cRotationRing::CopyTo(EaString* dst)
{
    dst->assign(mpStr2Begin_dc, mpStr2End_e0);
}

// @ 0x00d1deb0
cRefObj* cRefObj::Init(void* o)
{
    mpVtbl_00 = (void*)0x147a2b0;
    mp_04 = 0;
    mp_08 = 0;
    void* old = mp_08;
    if (o != old) {
        if (o) (*(VFn0)VSLOT(o, 0))(o);
        mp_08 = o;
        if (old) (*(VFn0)VSLOT(old, 4))(old);
    }
    return this;
}

// @ 0x00d1df00
void cRefObj::Destroy()
{
    if (mp_04) {
        ((cSPUILayoutObj*)mp_04)->Shutdown(1);
        void* c = mp_04;
        if (c) {
            mp_04 = 0;
            (*(VFn0)VSLOT(c, 8))(c);
        }
    }
    if (mp_08) {
        void* c = mp_08;
        mp_08 = 0;
        (*(VFn0)VSLOT(c, 4))(c);
    }
}

// @ 0x00d1e140
void* __fastcall FUN_00d1e140(E207Obj* self, void* edx, unsigned int flags)
{
    (void)edx;
    self->mpVtbl = (void*)&gVtableE207;
    _ReadWriteBarrier();
    void* p2 = self->mpB;
    if (p2) ((IRefS*)p2)->Slot4();
    void* p1 = self->mpA;
    if (p1) ((IRefS*)p1)->Slot8();
    if (flags & 1)
        OpDelete(self);
    return self;
}

// @ 0x00d1f070
void AbilitySet::destroy()
{
    for (int i = 5; i >= 0; i--) rc_release(mArr34[i]);
    for (int i = 5; i >= 0; i--) rc_release(mArr1c[i]);
    for (int i = 1; i >= 0; i--) rc_release(mArr14[i]);
    for (int i = 1; i >= 0; i--) rc_release(mArr0c[i]);
    for (int i = 2; i >= 0; i--) rc_release(mArr00[i]);
}

// @ 0x00d1f160
void __cdecl FUN_00d1f160(uint32_t id, uint32_t* data, int count, void** arr)
{
    void* local4 = 0;
    void* pm = SP_PropertyManager();

    for (int n = count; n != 0; n--) {
        if (local4 != 0) {
            PropList* t = (PropList*)local4;
            local4 = 0;
            t->vf1();
        }

        ((void(__thiscall*)(void*, uint32_t, uint32_t, void**))
             (*(void***)pm)[0x2c / 4])(pm, *data, id, &local4);

        if (local4 != 0) {
            RCObj* nc = (RCObj*)FUN_00f473a0(0x13c, "Simulator/cCreatureAbility", 0, 0, 0, 0);
            if (nc != 0)
                FUN_004d3760(nc);

            RCObj* old = (RCObj*)arr[0];
            if (nc != old) {
                if (nc != 0)
                    nc->mRef++;
                arr[0] = nc;
                if (old != 0)
                    rc_release(old);
            }

            FUN_004d92b0(arr[0], local4);
        }

        data++;
        arr++;
    }

    if (local4 != 0) {
        PropList* t = (PropList*)local4;
        t->vf1();
    }
}

// @ 0x00d1f250
void __cdecl FUN_00d1f250(void** arr, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++) {
        RCObj* p = (RCObj*)arr[i];
        if (p != 0) {
            arr[i] = 0;
            int n = p->mRef;
            p->mRef = --n;
            if (n == 0) {
                p->mRef = 1;
                p->vf0(1);
            }
        }
    }
}

// @ 0x00d1f2a0
void __cdecl FUN_00d1f2a0(void)
{
    uint32_t a[6];

    a[0] = 0x6282938f; a[1] = 0xe10f1680; a[2] = 0x042592a5;
    FUN_00d1f160(0xdd91ac58, a, 3, g_169de30);

    a[0] = 0x93f63c50; a[1] = 0x854f28cd;
    FUN_00d1f160(0xdd91ac58, a, 2, g_169de3c);

    if (FUN_00685520(2)) {
        a[0] = 0x672b9a9f; a[1] = 0x0f27ecc2;
        FUN_00d1f160(0xdd91ac58, a, 2, g_169de44);
    }

    a[0] = 0x6282938f; a[1] = 0xe10f1680; a[2] = 0x042592a5;
    a[3] = 0x5a93b784; a[4] = 0xe5aa4c4d; a[5] = 0xdf4f5863;
    FUN_00d1f160(0xc85c1f8b, a, 6, g_169de4c);

    a[0] = 0xb522e3ee; a[1] = 0x515b7e25; a[2] = 0x166a2770;
    a[3] = 0xc60fc2ec; a[4] = 0xec13fdbe; a[5] = 0x2b2f0629;
    FUN_00d1f160(0xc85c1f8b, a, 6, g_169de64);
}

// @ 0x00d1f3c0
void __cdecl FUN_00d1f3c0(void)
{
    FUN_00d1f250(g_169de30, 3);
    FUN_00d1f250(g_169de3c, 2);
    FUN_00d1f250(g_169de44, 2);
    FUN_00d1f250(g_169de4c, 6);
    FUN_00d1f250(g_169de64, 6);
}

// @ 0x00d1f400
bool __cdecl FUN_00d1f400(uint32_t param_1)
{
    uint32_t tag = *(uint32_t*)(param_1 + 8);

    void* terr = SP_NounManager();
    cTerrainEditor* sphere = (cTerrainEditor*)
        ((void*(__thiscall*)(void*)) FUN_00f67d90)(terr);

    uint32_t foundA = 0;
    uint32_t foundB = 0;
    IdVec vec;
    vec.mpBegin = 0; vec.mpEnd = 0; vec.mpCap = 0;

    uint32_t nameA;
    uint32_t nameB;

    void* mode = SP_GetCurrentGameMode();
    if (mode == (void*)&g_1654c01) {
        nameA = 0x5ff7927;
        nameB = 0x5ff7928;
        FUN_00555e80(sphere->mpListA, &vec);
    } else if (mode == (void*)&g_1654c02) {
        nameA = 0x5ff7baf;
        nameB = 0x5ff7bb6;
        FUN_00555e80(sphere->mpListA, &vec);
        FUN_00555e80(sphere->mpListB, &vec);
    } else {
        if (vec.mpBegin != 0 && *((int*)vec.mpBegin - 1) != 0)
            FUN_00f47380(vec.mpBegin);
        return false;
    }

    bool okA = sphere->GetFlagValue(nameA, (int*)&foundA);
    if (okA == 0 || sphere->GetFlagValue(nameB, (int*)&foundB) == 0) {
        void* mode2 = SP_GetCurrentGameMode();
        uint32_t n = (uint32_t)(vec.mpEnd - vec.mpBegin);
        uint32_t flags = 0;
        if (mode2 == (void*)&g_1654c01) {
            for (uint32_t i = 0; i < n; i++) {
                uint32_t id = vec.mpBegin[i];
                if (id == 0xe4237bd6)          flags |= 0x20000;
                else if (id == 0x03419db6)     flags |= 0x40000;
                else if (id == 0x630ad0eb)     flags |= 0x80000;
            }
        } else if (mode2 == (void*)&g_1654c02) {
            for (uint32_t i = 0; i < n; i++) {
                int id = (int)vec.mpBegin[i];
                if (id < -0x11f3edc6) {
                    if (id == -0x11f3edc7)         flags |= 0x200000;
                    else if (id == -0x49d6a8dc)    flags |= 0x800000;
                    else if (id == -0x3867e9cf)    flags |= 0x1000000;
                    else if (id == -0x1a0caa4d)    flags |= 0x100000;
                } else if (id == 0x27cb4512)       flags |= 0x2000000;
                else if (id == 0x5961d110)         flags |= 0x400000;
            }
        }
        foundA = flags;
        foundB = 0;
        sphere->SetFlagValue(nameA, flags);
        sphere->SetFlagValue(nameB, foundB);
    }

    // Pack the pair as (high=foundA, low=foundB) and test bit `tag`.
    unsigned long long bits = (unsigned long long)foundB
                            | ((unsigned long long)foundA << 32);
    unsigned long long mask = 1ULL << tag;
    bool result = (bits & mask) != 0;

    if (vec.mpBegin != 0 && *((int*)vec.mpBegin - 1) != 0)
        FUN_00f47380(vec.mpBegin);
    return result;
}

// @ 0x00d1fa20
unsigned char F_d1fa20(int* p)
{
    if (p[3] == 4)
        return FUN_00d1f400(p);
    if (GetCurrentGameMode() == (void*)&g_gameModeTribe2) {
        cTribe* tribe = (cTribe*)((cGameNounManager_s00d1_f650*)NounManager())->GetPlayerTribe();
        switch (p[2]) {
        case 5:  return tribe->GetToolOfType(4) != 0;
        case 6:  return tribe->GetToolOfType(5) != 0;
        case 7:  return tribe->GetToolOfType(6) != 0;
        case 0x2b: return tribe->GetToolOfType(3) != 0;
        case 0x3a: return tribe->GetToolOfType(1) != 0;
        case 0x3b: return tribe->GetToolOfType(2) != 0;
        default: return 0;
        }
    }
    return 1;
}
