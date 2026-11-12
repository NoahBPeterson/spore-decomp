// src/game/SPGonzago/SPLocomotiveObject.cpp -- migrated from slice(s) s00c41360, s00c432e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPLocomotiveObject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocomotiveObject.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s00c432e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSpatialVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
    void erase(void* first, void* last);                     // 0x00b48e40
};
}
namespace SP {
struct cUIntVector {
    uint32_t* mpBegin;                                       // +0x00
    uint32_t* mpEnd;                                         // +0x04
    uint32_t* mpCapacity;                                    // +0x08
    void DoInsertKey4(uint32_t* pos, const uint32_t* value); // 0x00b96600
};
}
namespace SP {
struct cSubD4 {
    void Reset();                                            // 0x00ac5330
};
}
namespace SP {
struct cLocomotiveObject_s00c4_32e0 {
    uint32_t       mPad00[0xd4 / 4];                         // +0x00 .. +0xd3
    cSubD4         mSubD4;                                   // +0xd4
    uint32_t       mPadD8[0x1a0 / 4];                        // +0xd8 .. +0x277
    cSpatialVector mNeighbors;                               // +0x278
    uint32_t       mPad284[0x20c / 4];                       // +0x284 .. +0x48f
    cUIntVector    mVectors;                                 // +0x490
    uint32_t       mPad49c[0x30 / 4];                        // +0x49c .. +0x4cb
    void*          mpField4cc;                               // +0x4cc

    void Shutdown();  // 0x00c43f90 (SP::cLocomotiveObject::Shutdown)
    void InsertUnique(uint32_t value);
};
}
extern "C" void __fastcall FUN_00c8b2e0(void*);                             // 0x00c8b2e0
// ---- items of slice s00c432e0 end

// ---- items of slice s00c41360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_OneThird;                     // 0x013f26dc (0.33333334f)
extern float g_HkRealZero;                   // 0x01485378 (0.0f)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct PodVec3 {    // trivially copyable (integer-register copies)
    float x, y, z;
};
struct cCityWalls {
    char pad[0x25c];
    float mOuterRadius;                               // +0x25c
    const PodVec3& GetWallPosition(Vector3& out, const Vector3& towards, int flag);   // 0xbec660 (sret)
    const PodVec3& RequestPosition(Vector3& out, int mode);                           // 0xbec2d0 (sret)
};
struct cSpatialObject {
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
    virtual const Vector3& GetPosition();             // +0x2c
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
    cSpatialObject mSpatial;                          // +0x120 (secondary base)
};
struct cRandomGlobal { float RandomDouble(); };        // 0x009360d0 (thiscall)
struct cRoad
{
    void RemoveInt(int value);
    char    pad04[0x118 - 0x04];    // +0x04 (after vptr)
    bool    mbFlag118;              // +0x118
    cCity*  mpCity1;                // +0x11c
    cCity*  mpCity2;                // +0x120
    int     mRoadType;              // +0x124
    char    pad128[0x13c - 0x128];
    float   mF13c;                  // +0x13c
    char    pad140[0x1a8 - 0x140];
    Vector3 mV1a8;                  // +0x1a8
    Vector3 mV1b4;                  // +0x1b4
    float   mF1c0;                  // +0x1c0
    float   mF1c4;                  // +0x1c4
    char    pad1c8[0x1f4 - 0x1c8];
    void*   mBegin1f4;              // +0x1f4
    void*   mEnd1f8;                // +0x1f8
    char    pad1fc[0x208 - 0x1fc];
    Vector3 mV208;                  // +0x208
    char    pad214[0x250 - 0x214];
    int     mF250;                  // +0x250
    float   mF254;                  // +0x254
    char    pad258[0x260 - 0x258];
    float   mF260;                  // +0x260
    char    pad264[0x26c - 0x264];
    float   mF26c;                  // +0x26c
    int     mF270;                  // +0x270
    char    pad274[0x278 - 0x274];
    Vector3 mV278;                  // +0x278
    char    pad284[0x490 - 0x284];
    int*    mpIntBegin490;          // +0x490
    int*    mpIntEnd494;            // +0x494
    char    pad498[0x4b8 - 0x498];
    Vector3 mV4b8;                  // +0x4b8

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
    virtual const Vector3& GetPosition();              // +0x2c
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
    virtual char Action58();                           // +0x58
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
virtual void v63();
virtual void v64();
virtual void v65();
virtual void v66();
virtual void v67();
virtual void v68();
virtual void v69();
virtual void v70();
virtual void v71();
virtual void v72();
virtual void v73();
virtual void v74();
virtual void v75();
virtual void v76();
virtual void v77();
virtual void v78();
virtual void v79();
virtual void v80();
virtual void v81();
virtual void v82();
virtual void v83();
virtual void v84();
virtual void v85();
    virtual void* LookupById(uint32_t id);             // +0xb8
    virtual void v87();
    virtual void Chain(uint32_t a, uint32_t b);        // +0xc4

    float DistSqToPos();                               // 0x00c422c0
    bool  WithinRadius(float r);                       // 0x00c42210
};
struct cRoadTail
{
    uint8_t* mpBegin;               // +0x00
    uint8_t* mpEnd;                 // +0x04
    uint8_t  pad08[0x14 - 0x08];
    uint8_t  mDefault[0x3c];        // +0x14
};
int __cdecl FUN_00c42310(int* param_1)
{
    if (param_1 == 0)
        return 0;
    int* p = (int*)(*(int(__thiscall**)(int*, uint32_t))(*param_1 + 0xb8))(param_1, 0x17f243b);
    if (p == 0)
        return 0;
    char c = (*(char(__thiscall**)(int*))(*p + 0x2c))(p);
    if (c == 0)
        return 0;
    return 1;
}
struct IdLookupTarget
{
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
    virtual char  Test();                              // +0x2c
};
struct IdLookupSource
{
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
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
    virtual IdLookupTarget* Lookup(uint32_t id);       // +0xb8
    IdLookupTarget* Find(uint32_t id) { return Lookup(id); }
};
struct EntityRef
{
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
    virtual void* BuildEffect(float scale, const Vector3* pos, int a, void* fn, void* id);  // +0x2c
};
struct AvatarHolder2
{
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
    virtual void AddEffect(void* effect);              // +0x48
};
AvatarHolder2* __cdecl GetAvatarHolder2b();            // 0x00b3d240
void __cdecl EffectCallback0(void* a);                 // 0x00d9a9c0
// ---- items of slice s00c41360 end

// @ 0x00c41ed0
int __fastcall FUN_00c41ed0(cRoad* this_, float a, float b)
{
    if (!(b * b >= a)) {
        if (this_->mF260 > g_HkRealZero) {
            if (this_->mF254 * this_->mF254 >= a)
                return 1;
        }
        return 0;
    }
    return 1;
}

// @ 0x00c420f0
float __cdecl FUN_00c420f0(cRandomGlobal* r, float a, float b)
{
    float r1 = r->RandomDouble();
    float r2 = r->RandomDouble();
    float r3 = r->RandomDouble();
    return (r3 + r2 + r1) * (b - a) * g_OneThird + a;
}

// @ 0x00c42140
void cRoad::RemoveInt(int value)
{
    unsigned i = 0;
    unsigned n = (unsigned)(mpIntEnd494 - mpIntBegin490);
    if (n <= 0) return;
    int* p = *(int* volatile*)&mpIntBegin490;
    do {
        if (value == *p) goto found;
        _ReadWriteBarrier();
        ++i;
        ++p;
    } while (i < (unsigned)(mpIntEnd494 - mpIntBegin490));
    return;
found:
    _ReadWriteBarrier();
    mpIntBegin490[i] = mpIntBegin490[mpIntEnd494 - mpIntBegin490 - 1];
    mpIntEnd494 -= 1;
}

// @ 0x00c421f0
int* __fastcall FUN_00c421f0(cRoad* this_)
{
    void* b = this_->mBegin1f4;
    if (b == this_->mEnd1f8)
        return (int*)&this_->mV208;
    _ReadWriteBarrier();
    return (int*)((uint32_t)this_->mEnd1f8 - 0x3c);
}

// @ 0x00c42210
bool __fastcall FUN_00c42210(cRoad* this_, float r)
{
    if (this_->mF250 == 0)
        return true;
    Vector3 p;
    if (this_->mBegin1f4 == this_->mEnd1f8)
    {
        p.x = this_->mV208.x;
        p.y = this_->mV208.y;
        p.z = this_->mV208.z;
    }
    else
    {
        float* q = (float*)((uint8_t*)this_->mEnd1f8 - 0x3c);
        p.x = q[0];
        p.y = q[1];
        p.z = q[2];
    }
    const Vector3& c = this_->GetPosition();
    float dx = p.x - c.x;
    float dy = p.y - c.y;
    float dz = p.z - c.z;
    return sqrtf(dz * dz + dx * dx + dy * dy) < r;
}

// @ 0x00c422c0
float __fastcall FUN_00c422c0(cRoad* this_)
{
    if (this_->mF250 == 0)
        return 0.0f;
    const Vector3& pos = this_->GetPosition();
    float dx = this_->mV208.x - pos.x;
    float dy = this_->mV208.y - pos.y;
    float dz = this_->mV208.z - pos.z;
    return dz * dz + dx * dx + dy * dy;
}

// @ 0x00c42310
int __cdecl FUN_00c42310(IdLookupSource* param_1)
{
    if (param_1 != 0)
    {
        IdLookupTarget* t = param_1->Find(0x17f243b);
        if (t != 0)
        {
            if (t->Test() != 0)
                return 1;
        }
    }
    return 0;
}

// @ 0x00c42350
void __fastcall FUN_00c42350(cRoad* this_)
{
    if (this_->mF26c == g_HkRealZero)
        return;
    AvatarHolder2* holder = GetAvatarHolder2b();
    void* id = 0;
    (void)id;
    void* effectId = ((IdLookupSource*)this_)->Find(0x17f243b);
    void* effect = ((EntityRef*)this_)->BuildEffect(this_->mF26c, &this_->mV278,
                                                    0, (void*)EffectCallback0, effectId);
    holder->AddEffect(effect);
}

// @ 0x00c423c0
int* __fastcall FUN_00c423c0(cRoadTail* t)
{
    uint8_t* e = t->mpEnd;
    if (t->mpBegin == e)
        return (int*)t->mDefault;
    return (int*)(e - 0x3c);
}

// @ 0x00c43f90
namespace SP {
void cLocomotiveObject_s00c4_32e0::Shutdown()
{
    void* previous = mpField4cc;
    if (previous) {
        mpField4cc = 0;
        ((void (__thiscall*)(void*))((void**)*(void**)previous)[0x04 / 4])(previous);
    }
    mNeighbors.erase(mNeighbors.mpBegin, mNeighbors.mpEnd);
    mSubD4.Reset();
    FUN_00c8b2e0(this);
}
}  // namespace SP

// @ 0x00c43fe0
namespace SP {
void cLocomotiveObject_s00c4_32e0::InsertUnique(uint32_t value)
{
    uint32_t* it = mVectors.mpBegin;
    uint32_t* last = mVectors.mpEnd;
    while (it != last && *it != value)
        ++it;
    if (it == last) {
        if (last != mVectors.mpCapacity) {
            mVectors.mpEnd = last + 1;
            if (last)
                *last = value;
        } else {
            mVectors.DoInsertKey4(last, &value);
        }
    }
}
}  // namespace SP
