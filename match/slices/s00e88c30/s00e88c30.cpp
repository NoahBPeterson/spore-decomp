// Slice s00e88c30 -- Simulator city-view helpers around 0x00e88c30..0x00e899a7:
// the cCityFeedbackView loyalty-bar meter helpers, the cBuildingView configure/space-capture
// update, the damage-effect spawner, the cCityTerritory/cCitySoundLoopView deleting
// destructors and cCityTerritoryView::HandleSimulationUpdate.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell/Simulator TU; same as s00e86d40).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Raw virtual-call / field helpers.
// ---------------------------------------------------------------------------
#define VS(o, off)             (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)         ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1) ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define FI32(p, off)  (*(int*)((char*)(p) + (off)))
#define FU8(p, off)   (*(u8*)((char*)(p) + (off)))
#define FU32(p, off)  (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))

// ---------------------------------------------------------------------------
// Callees.
// ---------------------------------------------------------------------------
extern "C" void operator_delete_array(void*);   // 0x00f47380

// ---------------------------------------------------------------------------
// cSpatialObjectView (retail size 0x34) -- layout from slice s00e86d40.
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

struct cSpatialObjectView {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void v28(void*);
    virtual void* v2c();
    virtual void* v30();

    void Dtor();                        // 0x00e92660  ??1cSpatialObjectView@@QAE@XZ

    u32   mField04;                     // +0x04
    u32   mField08;                     // +0x08
    void* mpObject;                     // +0x0c
    void* mpObjectCombatant;            // +0x10
    u8    mField14;                     // +0x14
    char  pad_15[3];
    Vec3  mColor;                       // +0x18
    u32   mField24;                     // +0x24
    u32   mField28;                     // +0x28
    u32   mField2c;                     // +0x2c
    u8    mbField30;                    // +0x30
    u8    mbDamageState;                // +0x31
    u8    mbField32;                    // +0x32
    char  pad_33[1];
};

// cSpatialObject: the world object referenced by a view through mpObject.
struct cSpatialObject {
    void DestroyAllEffects(int flag);   // 0x00c8b0a0
};

// Reference-counted effect objects reached through a view's mpEffect members.
struct cRefObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
};

// ---------------------------------------------------------------------------
// Vtables (address-only references).
// ---------------------------------------------------------------------------
extern void* vtbl_cCityTerritory;       // 0x01486208
extern void* vtbl_cCitySoundLoopView;   // 0x0148625c

// ---------------------------------------------------------------------------
// cCityTerritory: cSpatialObjectView subclass (no extra members accessed here).
// ---------------------------------------------------------------------------
struct cCityTerritory : cSpatialObjectView {
    void* deleting_dtor(char flag);
};

// @ 0x00e89770
void* cCityTerritory::deleting_dtor(char flag)
{
    *(void**)this = &vtbl_cCityTerritory;
    ((cSpatialObject*)mpObject)->DestroyAllEffects(1);
    ((cSpatialObjectView*)this)->Dtor();
    if (flag & 1)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------------------
// cCitySoundLoopView: cSpatialObjectView subclass with a refcounted effect at +0x34.
// ---------------------------------------------------------------------------
struct cCitySoundLoopView : cSpatialObjectView {
    void* mpEffect_34;                  // +0x34
    void* deleting_dtor(char flag);
};

// @ 0x00e89950
void* cCitySoundLoopView::deleting_dtor(char flag)
{
    void* p = mpEffect_34;
    *(void**)this = &vtbl_cCitySoundLoopView;
    if (p != 0) {
        VC1(void, p, 0xc, int, 1);
        p = mpEffect_34;
        if (p != 0) {
            mpEffect_34 = 0;
            VC0(void, p, 4);
        }
    }
    if (mpEffect_34 != 0)
        VC0(void, mpEffect_34, 4);
    ((cSpatialObjectView*)this)->Dtor();
    if (flag & 1)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------------------
// cSPUIMeter: the refcounted UI meter.  Shutdown 0x00e06940, Init 0x00e06a10,
// the two setters 0x00e06c50 / 0x00e06cf0.  Virtual slots +0 add-ref, +4 release.
// ---------------------------------------------------------------------------
struct cSPUIMeter {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    virtual void v08();                       // +0x08
    virtual void v0c();                       // +0x0c

    cSPUIMeter* Init(u32 hdr, u32 a, u32 b, const wchar_t* name, u32 d);  // 0x00e06a10
    void Shutdown(int flag);                  // 0x00e06940
    void Func_e06c50(void* obj);              // 0x00e06c50
    void Func_e06cf0(u32 v);                  // 0x00e06cf0
};

// AutoRefCount<T>: assignment adopts p (add-ref), releasing the old object.
template <class T>
struct AutoRef {
    T* mpObj;
    T* operator=(T* p) {
        T* old = mpObj;
        if (p != old) {
            if (p)   p->AddRef();
            mpObj = p;
            if (old) old->Release();
        }
        return p;
    }
};

void* operator_new(u32 size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
extern char g_allocTag_013f6b3c;               // 0x013f6b3c (allocation tag)

// ---------------------------------------------------------------------------
// cCity: the world city referenced by a feedback view through its +0x0c pointer.
// Only the fields touched by the loyalty-bar updater are named.
// ---------------------------------------------------------------------------
struct cCitySub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool Func58();                    // +0x58
};

struct cCityHall {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual u32  Func0c(u32 arg);             // +0x0c
};

struct cCity {
    u8       mPre_120[0x120];
    cCitySub mSub;                            // +0x120
    u8       mPad_124[0x748 - 0x124];
    float    mField748;                       // +0x748  progress 0..100
    int      mField74c;                       // +0x74c  state id
    int      mField750;                       // +0x750
    int      mField754;                       // +0x754  state id
    int      mField758;                       // +0x758
    int      mField75c;                       // +0x75c  state id

    cCityHall* GetCityHall();                 // 0x00bd9b40
};

// ---------------------------------------------------------------------------
// cCityFeedbackView: three loyalty meters at +0x10/+0x14/+0x18.
// ---------------------------------------------------------------------------
struct cCityFeedbackView {
    void*    mField00;
    void*    mField04;
    void*    mField08;
    cCity*   mpObject;                        // +0x0c
    AutoRef<cSPUIMeter> mMeter1;              // +0x10
    AutoRef<cSPUIMeter> mMeter2;              // +0x14
    AutoRef<cSPUIMeter> mMeter3;              // +0x18

    cSPUIMeter* UpdateLoyaltyBar(cSPUIMeter* p, char bShow, u32 hdr);
    void        HandleSimulationUpdate(int, int);
};

// @ 0x00e88c30
cSPUIMeter* cCityFeedbackView::UpdateLoyaltyBar(cSPUIMeter* p, char bShow, u32 hdr)
{
    if (bShow != 0) {
        if (p != 0)
            return p;

        void* mem = operator_new(0x50, &g_allocTag_013f6b3c, 0, 0, 0, 0);
        cSPUIMeter* np;
        if (mem != 0)
            np = ((cSPUIMeter*)mem)->Init(hdr, 0x3ffb28c, 0x4d428c1, L"CivConversionBar", 0xe9f70df9);
        else
            np = 0;

        np->Func_e06c50(mpObject);
        cCityHall* hall = mpObject->GetCityHall();
        np->Func_e06cf0(hall != 0 ? hall->Func0c(0x1186577) : 0);
        return np;
    }

    if (p != 0) {
        p->Shutdown(1);
        p = 0;
    }
    return p;
}

// @ 0x00e88ce0
void cCityFeedbackView::HandleSimulationUpdate(int, int)
{
    if (mpObject == 0)
        return;

    int state1 = mpObject->mField754;
    mMeter1 = UpdateLoyaltyBar(mMeter1.mpObj, (state1 != -1), 1);
    mMeter2 = UpdateLoyaltyBar(mMeter2.mpObj,
                               (mpObject->mField74c != -1) && (100.0f > mpObject->mField748), 0);
    mMeter3 = UpdateLoyaltyBar(mMeter3.mpObj,
                               (mpObject->mField75c != -1) && !mpObject->mSub.Func58(), 2);
}

// ---------------------------------------------------------------------------
// cBuildingView (retail size 0x88) -- same layout as slice s00e86d40.
// ---------------------------------------------------------------------------
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))

struct cSPTimer {                        // 0x00bc3130 Restart
    u32 mData[8];                        // +0x00..+0x1f
    void Restart();                      // 0x00bc3130
};

struct cBuildingSub {                    // embedded sub-object at cBuildingData +0x34
    virtual void s00();
};

struct cBuildingData {                   // argument of ConfigureBuildingView
    u8          mPad_34[0x34];
    cBuildingSub mSub;                   // +0x34
};

struct cXform {                          // object returned by cBuildingView vtable[0x2c]
    u8    mPad_4c[0x4c];
    float mField4c;                      // +0x4c
    float mField50;                      // +0x50
    float mField54;                      // +0x54
};

struct cCombatant {                      // 0x008e7f80 GetDamageState
    int GetDamageState();                // 0x008e7f80
};

struct PropRef {                         // 0x0041ea70 GetFloat
    u8    mPad_12[0x12];
    u16   mKind;                         // +0x12
    float* GetFloat();                   // 0x0041ea70
};

class cBuildingView : public cSpatialObjectView {
public:
    void*    mpEffect_34;                // +0x34
    int      mState_38;                  // +0x38
    float    mScale_3c;                  // +0x3c
    float    mScale_40;                  // +0x40
    float    mScale_44;                  // +0x44
    int      mXformIndices[4];           // +0x48
    u8       mbFlag_58;                  // +0x58
    u8       mPad_59[7];
    cSPTimer mTimer;                     // +0x60
    void*    mpEffect_80;                // +0x80
    void*    mpEffect_84;                // +0x84

    void ConfigureBuildingView(cBuildingData* p2);        // 0x00e88e10
    void UpdateSpaceCaptureEffects();                     // 0x00e89060
    void SpawnAndPlaceDamageEffects();                    // 0x00e89530
};

// Callees used by ConfigureBuildingView.
extern "C" void* GetCurrentGameMode();                    // 0x00b5b800
extern "C" void* FUN_00bd99e0(void* v);                   // 0x00bd99e0
extern "C" void* GonzagoModelWorld();                      // 0x00b3d520
extern "C" void  SetKeyKind(void* v, u32 kind, int flag);  // 0x0068c6d0
extern "C" void* PropertyManager();                       // 0x0067de30
extern "C" void  GetPropertyT_int(void* obj, u32 tag, int* out);  // 0x0040cf10
extern Vec3  g_cityColor_15a87b4;                         // 0x015a87b4 (RGB vec)
extern char  g_gameModeCity_1654c10;                      // 0x01654c10

// @ 0x00e88e10
void cBuildingView::ConfigureBuildingView(cBuildingData* p2)
{
    cBuildingData* p = 0;
    if (p2 != 0)
        p = (cBuildingData*)VC1(void*, p2, 0xc, u32, 0xe9cb8ba);

    if (GetCurrentGameMode() == &g_gameModeCity_1654c10) {
        mColor = g_cityColor_15a87b4;
    } else {
        Vec3* w = (Vec3*)VC0(void*, p, 0x84);
        Vec3* q = (Vec3*)FUN_00bd99e0(w);
        mColor = *q;
    }

    Vec3  local;
    Vec3* ref;
    if (VC0(char, &p->mSub, 0x90) == 0) {
        ref = (Vec3*)&mField24;
    } else {
        Vec3* w = (Vec3*)VC0(void*, &p->mSub, 0x98);
        local = *w;
        ref = &local;
    }
    VC4(void, this, 0x28, void*, p2, void*, GonzagoModelWorld(), void*, ref, void*, &mColor);

    u32 kind = VC0(u32, p2, 0x38);
    if (mpObject != 0) {
        cCombatant* c = (cCombatant*)VC1(void*, mpObject, 0xb8, u32, 0x13f94d4);
        if (c != 0 && c->GetDamageState() == 2) {
            Vec3* w = (Vec3*)VC0(void*, mpObject, 0x98);
            Vec3  key = *w;
            SetKeyKind(&key, 0x7e, 0);
            VC1(void, mpObject, 0x94, void*, &key);
            cXform* x = (cXform*)VC0(void*, this, 0x2c);
            x->mField4c = 0.4f;
            x->mField50 = 0.4f;
            x->mField54 = 0.4f;
        }
    }

    void* prop = 0;
    void* pm = PropertyManager();
    if (VC2(char, pm, 0x30, u32, 0xb6a5c63d, void**, &prop) != 0) {
        if (kind == 0xecade42 || kind == 0xff10521) {
            if (prop != 0) {
                void* out = 0;
                if (VC2(char, prop, 0x24, u32, 0x1ca5e86, void**, &out) != 0
                    && ((PropRef*)out)->mKind == 0xd)
                    mScale_44 = *((PropRef*)out)->GetFloat();
            }
        } else if (kind == 0x1007ae63) {
            GetPropertyT_int(prop, 0x1c38187, (int*)&mScale_44);
        } else {
            GetPropertyT_int(prop, 0x1ca5e8e, (int*)&mScale_44);
        }
    }
    mScale_40 = 1.0f;
    mScale_3c = 1.0f;
    mTimer.Restart();
    if (prop != 0)
        VC0(void, prop, 4);
}