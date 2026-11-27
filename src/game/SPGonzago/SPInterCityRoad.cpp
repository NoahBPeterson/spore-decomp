// src/game/SPGonzago/SPInterCityRoad.cpp -- migrated from slice(s) s00c41360, s00c404c0 by tools/migrate/rewrite.py
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
#include <math.h>

// ---- items of slice s00c404c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int     u32;
typedef signed   int     i32;
typedef unsigned char    u8;
typedef float            f32;
extern "C" f32 g_1485720;            // 0x01485720  (_HK_REAL_ONE)
extern "C" u8  g_15740d8;            // 0x015740d8
extern "C" wchar_t g_146cd68[];      // 0x0146cd68  L"IntercityRoadMesh"
extern "C" u8  g_1667bac;            // 0x01667bac  eastl gEmptyString16
// 0x00b18460: the base object's Cast (thiscall, ret 4).
struct cObjectCastBase { void* FUN_00b18460(i32 typeID); };
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

// ---- items of slice s00c41360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_RoadDefaultScale;             // 0x0169cb58
void __cdecl operator_delete__(void* p);   // 0xf47380 (operator delete[])
struct Vector3_s00c4_1360 {
    float x, y, z;
    Vector3_s00c4_1360() {}
    Vector3_s00c4_1360(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00c4_1360(const Vector3_s00c4_1360& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3_s00c4_1360 operator-(const Vector3_s00c4_1360& a, const Vector3_s00c4_1360& b) { return Vector3_s00c4_1360(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3_s00c4_1360 operator+(const Vector3_s00c4_1360& a, const Vector3_s00c4_1360& b) { return Vector3_s00c4_1360(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3_s00c4_1360 operator*(const Vector3_s00c4_1360& a, float s) { return Vector3_s00c4_1360(a.x * s, a.y * s, a.z * s); }
struct PodVec3 {    // trivially copyable (integer-register copies)
    float x, y, z;
};
bool __cdecl Vector3Equal(const PodVec3* a, const PodVec3* b);   // 0x004232c0
extern PodVec3 g_DefaultPosition;                                 // 0x0168e690 (also the "no position" marker)
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p) {
        if (((uint32_t*)p)[-1])
            operator_delete__(p);
    }
};
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin) mAllocator.deallocate(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValue(T* pos, const T& v);
    void push_back_default();
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct cCurvePoint {          // 0x3c bytes
    Vector3_s00c4_1360 mPos;             // +0x00
    float mF0c;               // +0x0c
    int mF10;                 // +0x10
    uint32_t pad14[(0x38 - 0x14) / 4];
    bool mF38;                // +0x38
    cCurvePoint(const Vector3_s00c4_1360& p) : mPos(p), mF0c(1.0f), mF10(0), mF38(false) {}
};
typedef SpVector<Vector3_s00c4_1360> Vec3Vector;
typedef SpVector<cCurvePoint> CurveVector;
template <> cCurvePoint* CurveVector::erase(cCurvePoint* first, cCurvePoint* last);          // 0xac4570
template <> cCurvePoint* CurveVector::insert(cCurvePoint* pos, const cCurvePoint& v);        // 0xc41190
template <> void CurveVector::push_back_default();                                           // 0xc410e0
template <> Vector3_s00c4_1360* Vec3Vector::erase(Vector3_s00c4_1360* first, Vector3_s00c4_1360* last);                       // 0x50f740
template <> void Vec3Vector::DoInsertValue(Vector3_s00c4_1360* pos, const Vector3_s00c4_1360& v);                  // 0x4b5ad0
struct cCurveParams {         // 20 bytes
    const char* mpName;
    void* mpA;
    void* mpFunc;
    void* mpB;
    void* mpC;
};
extern cCurveParams g_LandAvoidCitiesParams;          // 0x1565b54 ("landAvoidCities")
struct cCurveBuilder {
    void Build(const cCurveParams& params, const PodVec3& a, const PodVec3& b,
               CurveVector& out, float t0, float t1);  // 0xac6960
};
cCurveBuilder* __cdecl GetCurveBuilder();             // 0xb3d290
struct cCityWalls {
    char pad[0x25c];
    float mOuterRadius;                               // +0x25c
    const PodVec3& GetWallPosition(Vector3_s00c4_1360& out, const Vector3_s00c4_1360& towards, int flag);   // 0xbec660 (sret)
    const PodVec3& RequestPosition(Vector3_s00c4_1360& out, int mode);                           // 0xbec2d0 (sret)
};
struct cSpatialObject_s00c4_1360 {
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
    virtual const Vector3_s00c4_1360& GetPosition();             // +0x2c
};
struct cCity {
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
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
    virtual cCityWalls* GetCityWalls();               // +0x6c
    char pad04[0x120 - 4 - 4 * 0];
    cSpatialObject_s00c4_1360 mSpatial;                          // +0x120 (secondary base)
};
class cInterCityRoad_s00c4_1360 {
public:
    char pad[0x118];
    bool mbFlag118;               // +0x118
    cCity* mpCity1;               // +0x11c
    cCity* mpCity2;               // +0x120
    int mRoadType;                // +0x124
    Vec3Vector mPathData;         // +0x128
    float mWidth;                 // +0x13c
    void BuildPath();             // 0x00c41360
    void RegisterCity(void* city);                             // 0x00b18550
    void SetupCities(void* city1, void* city2, int roadType);  // 0x00c41c60
};
struct RefCounted
{
    virtual void AddRef();                             // +0x00
    virtual void Release();                            // +0x04
};
// ---- items of slice s00c41360 end

// @ 0x00c40cd0
void* cInteractiveOrnament::Cast_00c40cd0(i32 typeID)
{
    void* self = this;
    if (typeID == 0x2bca14b)
        return self;
    void* obj = ((cObjectCastBase*)self)->FUN_00b18460(typeID);
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

// Typed views of the archive's stream-holder interfaces.
struct RoadStreamHolder {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void* GetIO(); // slot 6
};
struct RoadArchive {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual RoadStreamHolder* GetStreamHolder(); // slot 8
};

// @ 0x00c40d40
bool cInterCityRoad::WriteRoad(void* stream)
{
    RoadStreamHolder* __restrict sub = ((RoadArchive*)stream)->GetStreamHolder();
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
    RoadStreamHolder* __restrict sub = ((RoadArchive*)stream)->GetStreamHolder();
    u32 tag;
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
{    i32 n = (i32)(vec->mEnd - vec->mBegin);
    RoadStreamHolder* __restrict sub = ((RoadArchive*)stream)->GetStreamHolder();
    i32 count = n;
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
    ((StreamObj*)stream)->Slot1c();}

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

// @ 0x00c41360
void cInterCityRoad_s00c4_1360::BuildPath()
{
    mPathData.erase(mPathData.begin(), mPathData.end());

    if (mpCity1 && mpCity1->GetCityWalls() && mpCity2 && mpCity2->GetCityWalls()) {
        CurveVector curve;

        Vector3_s00c4_1360 tmp;
        PodVec3 posA = mpCity1->GetCityWalls()->GetWallPosition(tmp, mpCity2->mSpatial.GetPosition(), 0);
        PodVec3 posB = mpCity2->GetCityWalls()->GetWallPosition(tmp, mpCity1->mSpatial.GetPosition(), 0);
        if (Vector3Equal(&posA, &g_DefaultPosition))
            posA = mpCity1->GetCityWalls()->RequestPosition(tmp, 5);
        if (Vector3Equal(&posB, &g_DefaultPosition))
            posB = mpCity2->GetCityWalls()->RequestPosition(tmp, 5);

        GetCurveBuilder()->Build(g_LandAvoidCitiesParams, posA, posB, curve, 0.0f, 1.0f);

        // drop the tail of the curve starting at the first point inside city 2's wall radius
        for (unsigned i = 0; i < (unsigned)curve.size(); ++i) {
            Vector3_s00c4_1360 d = curve[i].mPos - mpCity2->mSpatial.GetPosition();
            cCityWalls* w = mpCity2->GetCityWalls();
            float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
            if (len < w->mOuterRadius + 1.0f) {
                curve.erase(&curve[i], curve.end());
                break;
            }
        }
        // drop the head of the curve up to the last point inside city 1's wall radius
        for (int i = curve.size(); i != 0; --i) {
            Vector3_s00c4_1360 d = curve[i - 1].mPos - mpCity1->mSpatial.GetPosition();
            cCityWalls* w = mpCity1->GetCityWalls();
            float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
            if (len < w->mOuterRadius + 1.0f) {
                curve.erase(curve.begin(), &curve[i]);
                break;
            }
        }

        if (curve.begin() != curve.end()) {
            // first point too far from city 1: add a start point on the wall circle
            {
                const Vector3_s00c4_1360* p = &curve.begin()->mPos;
                Vector3_s00c4_1360 d = *p - mpCity1->mSpatial.GetPosition();
                cCityWalls* w = mpCity1->GetCityWalls();
                float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
                if (len > w->mOuterRadius + 3.0f) {
                    float r = mpCity1->GetCityWalls()->mOuterRadius + 1.0f;
                    cCurvePoint* first = curve.begin();
                    Vector3_s00c4_1360 d2 = first->mPos - mpCity1->mSpatial.GetPosition();
                    float inv = 1.0f / sqrtf(d2.x * d2.x + d2.z * d2.z + d2.y * d2.y);
                    Vector3_s00c4_1360 off = d2 * inv * r;
                    Vector3_s00c4_1360 np = mpCity1->mSpatial.GetPosition() + off;
                    curve.insert(curve.begin(), cCurvePoint(Vector3_s00c4_1360(g_DefaultPosition.x, g_DefaultPosition.y, g_DefaultPosition.z)));
                    curve.begin()->mPos = np;
                }
            }
            // last point too far from city 2: add an end point on the wall circle
            {
                cCurvePoint* last = curve.end() - 1;
                Vector3_s00c4_1360 d = last->mPos - mpCity2->mSpatial.GetPosition();
                cCityWalls* w = mpCity2->GetCityWalls();
                float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
                if (len > w->mOuterRadius + 3.0f) {
                    float r = mpCity2->GetCityWalls()->mOuterRadius + 1.0f;
                    cCurvePoint* last2 = curve.end() - 1;
                    Vector3_s00c4_1360 d2 = last2->mPos - mpCity2->mSpatial.GetPosition();
                    float inv = 1.0f / sqrtf(d2.x * d2.x + d2.z * d2.z + d2.y * d2.y);
                    Vector3_s00c4_1360 off = d2 * inv * r;
                    Vector3_s00c4_1360 np = off + mpCity2->mSpatial.GetPosition();
                    curve.push_back_default();
                    (curve.end() - 1)->mPos = np;
                }
            }
        }

        int n = curve.size();
        for (int i = 0; i < n; ++i)
            mPathData.push_back(curve[i].mPos);
    }
}

// @ 0x00c41c60
void cInterCityRoad_s00c4_1360::SetupCities(void* city1, void* city2, int roadType)
{
    RegisterCity(city1);

    cCity* old1 = mpCity1;
    if ((cCity*)city1 != old1)
    {
        if (city1 != 0)
            ((RefCounted*)city1)->AddRef();
        mpCity1 = (cCity*)city1;
        if (old1 != 0)
            ((RefCounted*)old1)->Release();
    }

    cCity* old2 = mpCity2;
    if ((cCity*)city2 != old2)
    {
        if (city2 != 0)
            ((RefCounted*)city2)->AddRef();
        mpCity2 = (cCity*)city2;
        if (old2 != 0)
            ((RefCounted*)old2)->Release();
    }

    mRoadType = roadType;
    const float scale = g_RoadDefaultScale;
    mbFlag118 = true;
    mWidth = scale;
    BuildPath();
}
