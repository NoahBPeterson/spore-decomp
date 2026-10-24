// match/slices/s00c404c0/s00c404c0.cpp
// Slice s00c404c0 -- Simulator::cInteractiveOrnament ctor/dtor/Update/SetLifetime/
// InitFromDefinition, SP::cInterCityRoad ctor/dtor/Write/Read/RemoveOwner and the
// SpVector<cCurvePoint> / vector<cSPVector3> serialization helpers.
// Reconstructed from work/match/scratch_s00c404c0_card.txt.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast

#include <new>

typedef unsigned int     u32;
typedef signed   int     i32;
typedef unsigned char    u8;
typedef unsigned short   u16;
typedef unsigned __int64 u64;
typedef float            f32;
typedef double           f64;

// ---------------------------------------------------------------------------
// Globals referenced directly by absolute address in the original.
// ---------------------------------------------------------------------------
extern "C" f32 g_168e690;            // 0x0168e690
extern "C" f32 g_168e694;            // 0x0168e694
extern "C" f32 g_168e698;            // 0x0168e698
extern "C" f32 g_13eb960;            // 0x013eb960
extern "C" f32 g_13ec5b4;            // 0x013ec5b4  (1000.0f)
extern "C" f32 g_146cb48;            // 0x0146cb48  (FLT_MAX)
extern "C" f32 g_13f9428;            // 0x013f9428
extern "C" f32 g_13f4fd0;            // 0x013f4fd0
extern "C" f32 g_1485720;            // 0x01485720  (_HK_REAL_ONE)
extern "C" f64 g_1447a10;            // 0x01447a10
extern "C" u8  g_15740d8;            // 0x015740d8
extern "C" wchar_t g_146cd68[];      // 0x0146cd68  L"IntercityRoadMesh"
extern "C" u8  g_168e65c;            // 0x0168e65c
extern "C" u8  g_1667bac;            // 0x01667bac  eastl gEmptyString16

// ---------------------------------------------------------------------------
// External free callees.
// ---------------------------------------------------------------------------
void* __cdecl   FUN_00f21760(void* obj, void* arg);                       // 0x00f21760
void* __stdcall FUN_00b18460(i32 typeID);                                 // 0x00b18460 (ret 4)
void* __cdecl   SP_PlanetModel();                                         // 0x00b3d350
void* __stdcall SP_NounManager(void* arg);                                // 0x00b3d300 (ret 4)
void  __cdecl   FUN_00f47380(void* p);                                    // 0x00f47380 operator delete[]
void  __cdecl   FUN_00571d90(void* self);                                 // 0x00571d90
bool  __cdecl   EA_IO_WriteUint32(void* io, const void* p, u32 count, i32 flags);  // 0x0093aa70
bool  __cdecl   EA_IO_ReadInt32(void* io, void* p, u32 count, i32 flags);          // 0x0093a780
i32   __cdecl   EA_Hash_FNV1_String8(u64 name);                           // 0x006a0ae0-ish

extern "C" f64 pow(f64 base, f64 exp);

// ---------------------------------------------------------------------------
// Role-based models of the engine classes involved (offsets are exact).
// ---------------------------------------------------------------------------
struct RelObj;      // reference counted object: vtable slot 1 == Release
struct Key { u32 w[3]; };                                     // 0x0c bytes
struct Vector3 {                                              // 0x0c bytes
    f32 x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct RelObj {
    void Release() { (**(void (__thiscall**)(void*))(*(void***)this + 1))(this); }
};

// SpVector<Vector3> (stride 0x0c) -- used by the road's point list and the
// <Vector3> serialization helpers.
struct SpVec3 {
    Vector3* mBegin;                                          // +0x00
    Vector3* mEnd;                                            // +0x04
    Vector3* mCap;                                            // +0x08
    Vector3* Erase(Vector3* first, Vector3* last);            // 0x0050f740
    void Reserve(i32 count);                                  // 0x00473890
    void DoInsertValue(Vector3* pos, const Vector3* v);       // 0x004b5ad0
};

// cSpatialObject subobject (lives at +0x34 of the interactable/intercity objects).
struct cSpatialObject {
    void* mVtbl_00;                                           // +0x34
    u8    pad_04[0x50 - 0x04];
    void  Ctor_00c89630();                                    // 0x00c89630
    void  Dtor_00c8a420();                                    // 0x00c8a420
    void  Dtor_00c8b2e0();                                    // 0x00c8b2e0
    bool  Write(void* stream);                                // 0x00c88a90
    bool  Read(void* stream);                                 // 0x00c88b00
    void* Cast_00c884f0(i32 typeID);                          // 0x00c884f0
};

// Base of both the ornament and the intercity road.
struct cInteractableObject {
    cInteractableObject();                                    // 0x00c3f9b0
    void* mVtbl_00;                                           // +0x00
    void* mVtbl_04;                                           // +0x04
    u8    pad_08[0x2c - 0x08];
    void* mpOwner_2c;                                         // +0x2c
    u8    pad_30[4];
    cSpatialObject mSpatial;                                  // +0x34

    bool LoadModelChecked(void* model);                       // 0x00c3f890
    bool InitFromDefinition(void* p, i32 a, u32 b);           // 0x00c3fc80 (ret 0xc)
    void FUN_00c3f9a0(void* arg);                             // 0x00c3f9a0
    void Destroy(i32 arg);                                    // 0x00c3fa70
};

// The combatant subobject inside cInteractiveOrnament (+0x170).
struct cCombatant {
    u8   mBytes_00[0xc8];
    void Ctor_00bfd4e0();                                     // 0x00bfd4e0
    void Dtor_00bfcd00();                                     // 0x00bfcd00
};

// The instanced-model object hung off cInteractiveOrnament::mpModel_d0.
struct OrnModelImpl;
typedef void (__thiscall *OrnModelFn)(OrnModelImpl* self, void* model, i32 flag);
struct OrnModelImpl { void** mVtbl_00; };                     // +0x00 = vtable
struct OrnModel {
    OrnModelImpl* mpImpl_00;                                  // +0x00
    u32           mFlags_04;                                  // +0x04
    u8            pad_08[0x58 - 0x08];
    f32           mAlpha_58;                                  // +0x58
    void Notify_16c(void* owner, i32 flag) {
        OrnModelImpl* impl = mpImpl_00;
        OrnModelFn fn = (OrnModelFn)(*(void**)((u8*)impl->mVtbl_00 + 0x16c));
        fn(impl, owner, flag);
    }
};

// ---------------------------------------------------------------------------
// SSE clamp helper (explicitly permitted <=8-instruction inline asm at
// docs/matching.md:196); cl emits the maxss/minss sequence for this shape.
// ---------------------------------------------------------------------------
static __forceinline f32 Clamp(f32 value, f32 lo, f32 hi)
{
    __asm {
        movss xmm0, value
        maxss xmm0, lo
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}

// cInteractiveOrnament -- 0x258 bytes.
struct cInteractiveOrnament : cInteractableObject {
    u32   mFlags_84;                                          // +0x84
    i32   mState_88;                                          // +0x88
    u8    pad_8c[0x9c - 0x8c];
    void* mpSub_9c;                                           // +0x9c (has a u32 flag at +4)
    u8    pad_a0[0xa3 - 0xa0];
    u8    mByte_a3;                                           // +0xa3
    u8    pad_a4[1];
    u8    mByte_a5;                                           // +0xa5
    u8    pad_a6[3];
    u8    mByte_a9;                                           // +0xa9
    u8    pad_aa[0xd0 - 0xaa];
    OrnModel* mpModel_d0;                                     // +0xd0
    u8    pad_d4[0x110 - 0xd4];
    i32   mType_110;                                          // +0x110
    u8    pad_114[0x130 - 0x114];
    void* mVtbl_130;                                          // +0x130
    RelObj* mpRef_134;                                        // +0x134
    RelObj* mpRef_138;                                        // +0x138
    RelObj* mpRef_13c;                                        // +0x13c
    RelObj* mpRef_140;                                        // +0x140
    u8    mByte_144;                                          // +0x144
    u8    pad_145[3];
    RelObj* mpRef_148;                                        // +0x148
    RelObj* mpRef_14c;                                        // +0x14c
    RelObj* mpRef_150;                                        // +0x150
    u8    pad_154[0xc];
    u8    mByte_160;                                          // +0x160
    u8    pad_161[3];
    f32   mField_164;                                         // +0x164
    RelObj* mpRef_168;                                        // +0x168
    u8    pad_16c[4];
    cCombatant mCombatant_170;                                // +0x170
    u32   mFlags_238;                                         // +0x238
    u8    mByte_23c;                                          // +0x23c
    u8    pad_23d[3];
    i32   mLifetime_240;                                      // +0x240
    i32   mTimer_244;                                         // +0x244
    i32   mField_248;                                         // +0x248
    Key*  mKeys_24c;                                          // +0x24c
    Key*  mKeysEnd_250;                                       // +0x250
    Key*  mKeysCap_254;                                       // +0x254

    cInteractiveOrnament();                                   // 0x00c404c0
    void  Dtor_00c40720(i32 arg);
    bool  LoadModel_00c407d0(void* model);
    void  Attach_00c40800(void* effect);
    void  SetLifetime_00c40830(f32 seconds, u8 keepModel);
    void  Update_00c408f0(i32 dt);
    u32   InitFromDefinition_00c40ab0(void* def, i32 a, u32 b);
    void* Cast_00c40cd0(i32 typeID);
    void  AttachEffect(void* effect);                         // 0x00c3ff10
};

// eastl wide string (3 pointers).
struct eastlWString {
    wchar_t* mpBegin;                                         // +0x00
    wchar_t* mpEnd;                                           // +0x04
    wchar_t* mpCap;                                           // +0x08
    void Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

extern "C" unsigned int wcslen(const wchar_t* p);

// ---------------------------------------------------------------------------
// cGameData / cInterCityRoad -- the serializable road object.
// ---------------------------------------------------------------------------
struct cGameData {
    cGameData();                                              // 0x00b18660
    void* mVtbl_00;                                           // +0x00
    void* mVtbl_04;                                           // +0x04
    u8    pad_08[0x2c - 0x08];
    RelObj* mpOwner_2c;                                       // +0x2c
    u8    pad_30[4];
    cSpatialObject mSpatial;                                  // +0x34
    u8    pad_84[0x108 - 0x84];

    bool Write(void* stream);                                 // 0x00b18590
    bool Read(void* stream);                                  // 0x00b18600
    void Dtor_00b184c0();                                     // 0x00b184c0
};

struct cInterCityRoad : cGameData {
    eastlWString mStr_108;                                    // +0x108 (0x108..0x113)
    u8       pad_114[4];                                      // +0x114
    u8       mByte_118;                                       // +0x118
    u8       pad_119[3];
    RelObj*  mpRef_11c;                                       // +0x11c
    RelObj*  mpRef_120;                                       // +0x120
    u8       pad_124[4];
    SpVec3   mVec_128;                                        // +0x128
    u8       pad_134[8];                                      // +0x134
    f32      mFloat_13c;                                      // +0x13c

    cInterCityRoad();                                         // 0x00c40f10
    void  Dtor_00c41040();
    bool  WriteRoad(void* stream);                            // 0x00c40d40
    bool  ReadRoad(void* stream);                             // 0x00c40de0
    void  RemoveOwner_00c412f0();                             // 0x00c412f0
};

// cCityDisplayStrategy (only the entry point used here).
struct cCityDisplayStrategy {
    void AddResourceNodes();                                  // 0x00b8bba0
};

// cVarListSerializer (0xa14 bytes of state).
struct cVarListSerializer {
    u32  mData[0xa14 / 4];
    void Ctor(void* owner, void* a, u32 b);                   // 0x00692f90
    bool Serialize(void* stream);                             // 0x00692900
    bool Read(void* stream);                                  // 0x00693e10
};

// Stream helpers: the caller receives an object whose vtable slot 0x20 returns
// a second object whose slot 0x18 yields the actual IO stream; slot 0x1c is the
// completion call.
struct StreamSub {
    void* GetIO() { return (**(void* (__thiscall**)(void*))(*(void***)this + 6))(this); }
};
struct StreamObj {
    StreamSub* GetSub() { return (**(StreamSub* (__thiscall**)(void*))(*(void***)this + 8))(this); }
    void Slot1c() { (**(void (__thiscall**)(void*))(*(void***)this + 7))(this); }
};

// SpVector<cCurvePoint> (stride 0x3c).
struct cCurvePoint {
    f32 m0;                                                   // +0x00
    f32 m4;                                                   // +0x04
    f32 m8;                                                   // +0x08
    f32 m12;                                                  // +0x0c
    i32 m10;                                                  // +0x10
    u8  pad_14[0x38 - 0x14];
    u8  m38;                                                  // +0x38
    cCurvePoint()
        : m0(g_168e690), m4(g_168e694), m8(g_168e698), m12(g_1485720), m10(0), m38(0) {}
    void CopyFrom(const cCurvePoint* src);                    // 0x00ac1ff0
};
struct SpVecCurve {
    cCurvePoint* mBegin;                                      // +0x00
    cCurvePoint* mEnd;                                        // +0x04
    cCurvePoint* mCap;                                        // +0x08
    void push_back_default();                                 // 0x00c410e0
    cCurvePoint* insert_00c41190(cCurvePoint* pos, const cCurvePoint& v);
    void DoInsertValue(cCurvePoint* pos, const cCurvePoint& v);  // 0x00ac45e0
};

// eastl::vector<cSPVector3> (12-byte elements) -- the STL sequence writer's argument.
struct SpVecSP3 {
    Vector3* mBegin;                                          // +0x00
    Vector3* mEnd;                                            // +0x04
    Vector3* mCap;                                            // +0x08
};

// SpVector<Key> append used by InitFromDefinition.
struct SpVecKey {
    Key* mBegin;                                              // +0x00
    Key* mEnd;                                                // +0x04
    Key* mCap;                                                // +0x08
    void DoInsertKey(Key* pos, const Key* v);                 // 0x004e3e10
};

// Property-list helpers used by InitFromDefinition.
struct PropList {
    bool  Has(i32 hash);
    void* Find(i32 hash);
    void  Reserve(i32 hash, i32* count, void** data);
};
struct Prop {
    i32  GetInt();
    u8   GetBool();
};

// ===========================================================================
// @ 0x00c404c0
// ===========================================================================
cInteractiveOrnament::cInteractiveOrnament()
{
    mVtbl_130 = (void*)0x146c56c;
    mpRef_134 = 0;
    mpRef_138 = 0;
    mpRef_13c = 0;
    mpRef_140 = 0;
    mByte_144 = 0;
    mpRef_148 = 0;
    mpRef_14c = 0;
    mpRef_150 = 0;
    mByte_160 = 0;
    mField_164 = 0.0f;
    mpRef_168 = 0;
    mCombatant_170.Ctor_00bfd4e0();
    mVtbl_00 = (void*)0x146cca0;
    mVtbl_04 = (void*)0x146cc8c;
    mSpatial.mVtbl_00 = (void*)0x146cbc8;
    mVtbl_130 = (void*)0x146cbb8;
    *(void**)mCombatant_170.mBytes_00 = (void*)0x146cb50;
    mFlags_238 = 0;
    mTimer_244 = 0;
    mByte_23c = 1;
    mLifetime_240 = -1;
    mField_248 = -1;
    mKeys_24c = 0;
    mKeysEnd_250 = 0;
    mKeysCap_254 = 0;
    mFlags_84 |= 0x200;
    mByte_a5 = 0;
}

// ===========================================================================
// @ 0x00c40720
// ===========================================================================
void cInteractiveOrnament::Dtor_00c40720(i32 arg)
{
    cCombatant* pCombat = &mCombatant_170;
    mVtbl_00 = (void*)0x146cca0;
    mVtbl_04 = (void*)0x146cc8c;
    mSpatial.mVtbl_00 = (void*)0x146cbc8;
    mVtbl_130 = (void*)0x146cbb8;
    *(void**)pCombat->mBytes_00 = (void*)0x146cb50;
    if (mKeys_24c != 0 && ((u32*)mKeys_24c)[-1] != 0)
        FUN_00f47380(mKeys_24c);
    pCombat->Dtor_00bfcd00();
    mVtbl_130 = (void*)0x146c56c;
    if (mpRef_168 != 0)
        mpRef_168->Release();
    if (mpRef_150 != 0)
        mpRef_150->Release();
    if (mpRef_14c != 0)
        mpRef_14c->Release();
    if (mpRef_148 != 0)
        mpRef_148->Release();
    cInteractableObject::Destroy(arg);
}

// ===========================================================================
// @ 0x00c407d0
// ===========================================================================
bool cInteractiveOrnament::LoadModel_00c407d0(void* model)
{
    if (LoadModelChecked(model)) {
        u32* pFlags = (u32*)((u8*)mpSub_9c + 4);
        *pFlags &= 0xfffffffd;
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00c40800
// ===========================================================================
void cInteractiveOrnament::Attach_00c40800(void* effect)
{
    FUN_00f21760(this, effect);
    mFlags_238 |= 1;
    AttachEffect(effect);
}

// ===========================================================================
// @ 0x00c40830
// ===========================================================================
void cInteractiveOrnament::SetLifetime_00c40830(f32 seconds, u8 keepModel)
{
    f32 t = Clamp(seconds, 0.0f, g_146cb48);
    mLifetime_240 = (i32)(t * g_13ec5b4);
    if (mLifetime_240 <= 0) {
        mFlags_238 &= 0xfffffffd;
    } else {
        mFlags_238 |= 2;
    }
    if (keepModel == 0) {
        mFlags_238 |= 4;
        OrnModel* model = mpModel_d0;
        if (model != 0)
            model->Notify_16c(model, 1);
    } else {
        mFlags_238 &= 0xfffffffb;
    }
    OrnModel* model2 = mpModel_d0;
    if (model2 != 0)
        model2->mAlpha_58 = g_1485720;
}

// ===========================================================================
// @ 0x00c408f0
// ===========================================================================
void cInteractiveOrnament::Update_00c408f0(i32 dt)
{
    if (mByte_a9 == 0) {
        OrnModel* model = mpModel_d0;
        if (model == 0)
            return;
        if (((model->mFlags_04 >> 15) & 1) == 0)
            return;
        model->Notify_16c(model, 0);
        return;
    }
    if (mFlags_238 & 1)
        return;
    if ((mFlags_238 & 2) == 0)
        return;
    i32 life = mLifetime_240;
    if (life > 0) {
        life -= dt;
        mLifetime_240 = life;
        if (life <= 0) {
            mLifetime_240 = 0;
            mTimer_244 = 0xbb8;
        }
    }
    if (mTimer_244 <= 0)
        return;
    OrnModel* model = mpModel_d0;
    if (model != 0) {
        mTimer_244 -= dt;
        if (mTimer_244 > 0) {
            f32 secs = (f32)dt * g_13f9428;
            f64 f = pow(g_1447a10, (f64)secs);
            model->mAlpha_58 = (f32)(f * (f64)model->mAlpha_58)
                             + (f32)((1.0 - f) * (f64)g_13eb960);
            mpModel_d0->mFlags_04 |= 2;
            return;
        }
        if (mFlags_238 & 4)
            model->mAlpha_58 = 0.0f;
    }
    if (mFlags_238 & 4) {
        (**(void (__thiscall**)(void*, i32))(*(void***)this + 0xd))(this, 0);
        (**(void (__thiscall**)(void*, void*))(*(void***)&mSpatial + 0xe))(&mSpatial, &g_168e65c);
        mByte_a9 = 0;
        OrnModel* m = mpModel_d0;
        if (m != 0)
            FUN_00571d90(m);
    } else {
        void* nm = SP_NounManager(this);
        (**(void (__thiscall**)(void*, void*))(*(void***)nm + 0xd))(nm, this);
        mTimer_244 = 0;
    }
}

// ===========================================================================
// @ 0x00c40ab0
// ===========================================================================
u32 cInteractiveOrnament::InitFromDefinition_00c40ab0(void* def, i32 a, u32 b)
{
    if (!cInteractableObject::InitFromDefinition(def, a, b))
        return 0;
    PropList* props = *(PropList**)((u8*)def + 0xc);
    if (!props->Has(0x3a39c47))
        return 0;
    void* propObj = props->Find(0x3a39c47);
    u16 kind = *(u16*)((u8*)propObj + 0x12);
    void* keyObj;
    if (kind == 9 || kind == 0x10) {
        if ((*(u8*)((u8*)propObj + 0x10) & 0x30) != 0)
            keyObj = *(void**)propObj;
        else
            keyObj = (kind != 0) ? propObj : 0;
    } else {
        keyObj = (void*)0x15d1160;
    }
    FUN_00c3f9a0(*(void**)keyObj);

    switch (mType_110) {
    case 1:
    case 3:
        mState_88 = 2;
        break;
    case 2:
        mState_88 = 1;
        break;
    case 6:
        mState_88 = 4;
        break;
    }

    if (props->Has(0x3cc94df)) {
        i32 v = ((Prop*)props->Find(0x3cc94df))->GetInt();
        mLifetime_240 = v * 1000;
        if (mLifetime_240 <= 0)
            mFlags_238 &= 0xfffffffd;
        else
            mFlags_238 |= 2;
    }
    if (props->Has(0x3cc9447)) {
        u8 v = ((Prop*)props->Find(0x3cc9447))->GetBool();
        if (v == 0)
            mFlags_84 |= 0x200;
        else
            mFlags_84 &= 0xfffffdff;
    }
    if (props->Has(0x553ecca)) {
        mByte_a3 = ((Prop*)props->Find(0x553ecca))->GetBool();
    }
    if (props->Has((i32)0xe0361a31)) {
        i32 count = 0;
        void* data = 0;
        props->Reserve((i32)0xe0361a31, &count, &data);
        SpVecKey* vec = (SpVecKey*)&mKeys_24c;
        i32 i = 0;
        i32 off = 0;
        while (i < count) {
            Key* src = (Key*)(off + (u8*)data);
            Key* end = vec->mEnd;
            if (end < vec->mCap) {
                vec->mEnd = (Key*)((u8*)end + 0xc);
                if (end != 0) {
                    end->w[0] = src->w[0];
                    end->w[1] = src->w[1];
                    end->w[2] = src->w[2];
                }
            } else {
                vec->DoInsertKey(end, src);
            }
            i++;
            off += 0xc;
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00c40cd0
// ===========================================================================
void* cInteractiveOrnament::Cast_00c40cd0(i32 typeID)
{
    void* self = this;
    if (typeID == 0x2bca14b)
        return self;
    void* obj = FUN_00b18460(typeID);
    if (obj == 0)
        obj = ((cSpatialObject*)((u8*)self + 0x34))->Cast_00c884f0(typeID);
    return obj;
}

// ===========================================================================
// @ 0x00c40d20
// ===========================================================================
bool __stdcall FUN_00c40d20(void* unused)
{
    if (SP_PlanetModel() != 0)
        ((cCityDisplayStrategy*)SP_PlanetModel())->AddResourceNodes();
    return true;
}

// ===========================================================================
// @ 0x00c40d40
// ===========================================================================
bool cInterCityRoad::WriteRoad(void* stream)
{
    StreamSub* sub = ((StreamObj*)stream)->GetSub();
    u32 tag = 0x2bca14b;
    void* io = sub->GetIO();
    EA_IO_WriteUint32(io, &tag, 1, 0);
    bool ok;
    if (cGameData::Write(stream) && mSpatial.Write(stream))
        ok = true;
    else
        ok = false;
    cVarListSerializer ser;
    ser.Ctor(this, &g_15740d8, 0x1a80d26);
    if (ser.Serialize(stream) && ok)
        return true;
    return false;
}

// ===========================================================================
// @ 0x00c40de0
// ===========================================================================
bool cInterCityRoad::ReadRoad(void* stream)
{
    StreamSub* sub = ((StreamObj*)stream)->GetSub();
    u32 tag = 0;
    void* io = sub->GetIO();
    EA_IO_ReadInt32(io, &tag, 1, 0);
    bool ok;
    if (cGameData::Read(stream) && mSpatial.Read(stream))
        ok = true;
    else
        ok = false;
    cVarListSerializer ser;
    ser.Ctor(this, &g_15740d8, 0x1a80d26);
    if (ok) {
        if (ser.Read(stream))
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00c40e80
// ===========================================================================
void __cdecl FUN_00c40e80(void* stream, SpVecSP3* vec)
{
    i32 count = (i32)((u8*)vec->mEnd - (u8*)vec->mBegin) / 12;
    StreamSub* sub = ((StreamObj*)stream)->GetSub();
    void* io = sub->GetIO();
    EA_IO_WriteUint32(io, &count, 1, 0);
    Vector3* it = vec->mBegin;
    Vector3* end = vec->mEnd;
    while (it != end) {
        StreamSub* s2 = ((StreamObj*)stream)->GetSub();
        void* io2 = s2->GetIO();
        EA_IO_WriteUint32(io2, it, 3, 0);
        it++;
    }
    ((StreamObj*)stream)->Slot1c();
}

// ===========================================================================
// @ 0x00c40f10
// ===========================================================================
cInterCityRoad::cInterCityRoad()
{
    cSpatialObject* sp = &mSpatial;
    sp->Ctor_00c89630();
    f32 one = g_1485720;
    mVtbl_00 = (void*)0x146ce68;
    mVtbl_04 = (void*)0x146ce54;
    sp->mVtbl_00 = (void*)0x146cd90;
    mStr_108.mpBegin = (wchar_t*)&g_1667bac;
    mStr_108.mpEnd = (wchar_t*)&g_1667bac;
    mStr_108.mpCap = (wchar_t*)((u8*)&g_1667bac + 2);
    mByte_118 = 0;
    mpRef_11c = 0;
    mpRef_120 = 0;
    mVec_128.mBegin = 0;
    mVec_128.mEnd = 0;
    mVec_128.mCap = 0;
    mFloat_13c = one;
    const wchar_t* p = g_146cd68;
    mStr_108.Assign(p, p + wcslen(p));
}

// ===========================================================================
// @ 0x00c41040
// ===========================================================================
void cInterCityRoad::Dtor_00c41040()
{
    if (mVec_128.mBegin != 0 && ((u32*)mVec_128.mBegin)[-1] != 0)
        FUN_00f47380(mVec_128.mBegin);
    if (mpRef_120 != 0)
        mpRef_120->Release();
    if (mpRef_11c != 0)
        mpRef_11c->Release();
    if ((((i32)mStr_108.mpCap - (i32)mStr_108.mpBegin) & -2) > 2 && mStr_108.mpBegin != 0)
        FUN_00f47380(mStr_108.mpBegin);
    mSpatial.Dtor_00c8a420();
    cGameData::Dtor_00b184c0();
}

// ===========================================================================
// @ 0x00c410e0
// ===========================================================================
void SpVecCurve::push_back_default()
{
    cCurvePoint* e = mEnd;
    if (e < mCap) {
        mEnd = e + 1;
        if (e != 0)
            ::new((void*)e) cCurvePoint();
    } else {
        DoInsertValue(e, cCurvePoint());
    }
}

// ===========================================================================
// @ 0x00c41190
// ===========================================================================
cCurvePoint* SpVecCurve::insert_00c41190(cCurvePoint* pos, const cCurvePoint& v)
{
    i32 index = (i32)((u8*)pos - (u8*)mBegin) / 0x3c;
    cCurvePoint* end = mEnd;
    if (pos == end && end != mCap) {
        mEnd = (cCurvePoint*)((u8*)end + 0x3c);
        if (end != 0)
            end->CopyFrom(&v);
    } else {
        DoInsertValue(pos, v);
    }
    return (cCurvePoint*)((u8*)mBegin + index * 0x3c);
}

// ===========================================================================
// @ 0x00c41210
// ===========================================================================
void __cdecl FUN_00c41210(void* stream, SpVec3* vec)
{
    vec->Erase(vec->mBegin, vec->mEnd);
    i32 count = 0;
    StreamSub* sub = ((StreamObj*)stream)->GetSub();
    void* io = sub->GetIO();
    EA_IO_ReadInt32(io, &count, 1, 0);
    vec->Reserve(count);
    for (u32 i = 0; i < (u32)count; i++) {
        Vector3 v;
        StreamSub* s2 = ((StreamObj*)stream)->GetSub();
        void* io2 = s2->GetIO();
        EA_IO_ReadInt32(io2, &v, 3, 0);
        Vector3* end = vec->mEnd;
        if (end < vec->mCap) {
            vec->mEnd = end + 1;
            if (end != 0)
                *end = v;
        } else {
            vec->DoInsertValue(end, &v);
        }
    }
    ((StreamObj*)stream)->Slot1c();
}

// ===========================================================================
// @ 0x00c412f0
// ===========================================================================
void cInterCityRoad::RemoveOwner_00c412f0()
{
    RelObj* r1 = mpRef_11c;
    if (r1 != 0) {
        mpRef_11c = 0;
        r1->Release();
    }
    RelObj* r2 = mpRef_120;
    if (r2 != 0) {
        mpRef_120 = 0;
        r2->Release();
    }
    mVec_128.Erase(mVec_128.mBegin, mVec_128.mEnd);
    RelObj* r3 = mpOwner_2c;
    if (r3 != 0) {
        mpOwner_2c = 0;
        r3->Release();
    }
    mSpatial.Dtor_00c8b2e0();
}