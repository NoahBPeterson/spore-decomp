// src/game/SPGonzago/SPInterCityRoad.cpp -- migrated from slice(s) s00c404c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPInterCityRoad.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInterCityRoad.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cInteractableObject.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" wchar_t g_146cd68[];      // 0x0146cd68  L"IntercityRoadMesh"
extern "C" unsigned int wcslen(const wchar_t* p);
#include <new>

// ---- items of slice s00c404c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int     u32;
typedef signed   int     i32;
typedef unsigned char    u8;
typedef float            f32;
extern "C" f32 g_1485720;            // 0x01485720  (_HK_REAL_ONE)
extern "C" u8  g_15740d8;            // 0x015740d8
extern "C" wchar_t g_146cd68[];      // 0x0146cd68  L"IntercityRoadMesh"
extern "C" u8  g_1667bac;            // 0x01667bac  eastl gEmptyString16
void* __stdcall FUN_00b18460(i32 typeID);                                 // 0x00b18460 (ret 4)
void* __cdecl   SP_PlanetModel();                                         // 0x00b3d350
bool  __cdecl   EA_IO_WriteUint32(void* io, const void* p, u32 count, i32 flags);  // 0x0093aa70
bool  __cdecl   EA_IO_ReadInt32(void* io, void* p, u32 count, i32 flags);          // 0x0093a780
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
struct SpVec3 {
    Vector3* mBegin;                                          // +0x00
    Vector3* mEnd;                                            // +0x04
    Vector3* mCap;                                            // +0x08
    Vector3* Erase(Vector3* first, Vector3* last);            // 0x0050f740
    void Reserve(i32 count);                                  // 0x00473890
    void DoInsertValue(Vector3* pos, const Vector3* v);       // 0x004b5ad0
};
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
struct cCombatant {
    u8   mBytes_00[0xc8];
    void Ctor_00bfd4e0();                                     // 0x00bfd4e0
    void Dtor_00bfcd00();                                     // 0x00bfcd00
};
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
struct eastlWString {
    wchar_t* mpBegin;                                         // +0x00
    wchar_t* mpEnd;                                           // +0x04
    wchar_t* mpCap;                                           // +0x08
    void Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
extern "C" unsigned int wcslen(const wchar_t* p);
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
struct cCityDisplayStrategy {
    void AddResourceNodes();                                  // 0x00b8bba0
};
struct cVarListSerializer {
    u32  mData[0xa14 / 4];
    void Ctor(void* owner, void* a, u32 b);                   // 0x00692f90
    bool Serialize(void* stream);                             // 0x00692900
    bool Read(void* stream);                                  // 0x00693e10
};
struct StreamSub {
    void* GetIO() { return (**(void* (__thiscall**)(void*))(*(void***)this + 6))(this); }
};
struct StreamObj {
    StreamSub* GetSub() { return (**(StreamSub* (__thiscall**)(void*))(*(void***)this + 8))(this); }
    void Slot1c() { (**(void (__thiscall**)(void*))(*(void***)this + 7))(this); }
};
struct SpVecSP3 {
    Vector3* mBegin;                                          // +0x00
    Vector3* mEnd;                                            // +0x04
    Vector3* mCap;                                            // +0x08
};
// ---- items of slice s00c404c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" f32 g_1485720;            // 0x01485720  (_HK_REAL_ONE)
extern "C" u8  g_15740d8;            // 0x015740d8
extern "C" u8  g_1667bac;            // 0x01667bac  eastl gEmptyString16

// @ 0x00c40cd0
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

// @ 0x00c40d20
bool __stdcall FUN_00c40d20(void* unused)
{
    if (SP_PlanetModel() != 0)
        ((cCityDisplayStrategy*)SP_PlanetModel())->AddResourceNodes();
    return true;
}

// @ 0x00c40d40
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

// @ 0x00c40de0
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

// @ 0x00c40e80
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

// @ 0x00c40f10
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

// @ 0x00c412f0
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
