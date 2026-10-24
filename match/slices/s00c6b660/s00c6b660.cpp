// Slice s00c6b660 (batch gold7, worker 19). Region 0x00c6b660-0x00c6c630.
// SP::cHerd cluster: GuardLocation / ClaimEmptyGuardLocation / SetPosition, an intrusive-list
// node recycler, a lazy watering-hole getter, the cHerd destructor and constructor, plus the
// eastl::wstring "list"/"type" serialisation helpers for the owned vectors.
//
// The shared src/game/include/SP/cHerd.h carries the 2008 dev-PDB layout; the retail offsets of
// cHerd in this object are shifted, so offsets below come from the disassembly and are used
// through byte-offset accessors on a locally declared stub class.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

#pragma warning(disable : 4100)

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef          int   s32;

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
extern "C" {
void* __cdecl FUN_00b3d3c0();                  // 0x00b3d3c0 (planet-manager pre-step)
void* __cdecl SP_PlanetModel();                // 0x00b3d350 SP::PlanetModel()
void  __fastcall FUN_00b88420(void* planet);   // 0x00b88420 (thiscall: planet in ecx)
void* __cdecl FUN_00b7ee70(void* out, const void* dir);  // 0x00b7ee70
float __fastcall FUN_00b7e840(void* self, const void* pos); // 0x00b7e840 GetAverageRadius (ret 4)
float __fastcall FUN_00b7ef70(void* self, const void* pos); // 0x00b7ef70 GetRadiusAt (ret 4)
void* __cdecl FUN_00b7f190(void* self, void* out, const void* pos); // 0x00b7f190 BuildSurfaceOrientation
void* __cdecl FUN_00b815a0(void* self, void* out, const void* dir); // 0x00b815a0 DirectionToSurfacePosition
float __cdecl FUN_00572a10(float lo, float hi);          // 0x00572a10 RandomFloatRange
void* __cdecl FUN_0059aed0(void* out, const void* a, const void* b); // 0x0059aed0 mat3*vec3
void* __cdecl FUN_00c6aab0(void* nest, const void* pos); // 0x00c6aab0 SP::cNest::MoveNest (ret 4)
void  __fastcall FUN_00c6b5b0(void* ecxHerd);            // 0x00c6b5b0 SP::cHerd::FindWateringHole
void** __cdecl FUN_00c6ae70(void** first, void** last, void** out, char (__cdecl*)(void*)); // 0x00c6ae70 copy_if
void** __fastcall FUN_00c6bd60(void* self);              // 0x00c6bd60 list node recycler
void  __cdecl FUN_00f47380(void* p);                     // 0x00f47380 operator delete
void  __fastcall FUN_00b63890(void* timer);               // 0x00b63890 cGonzagoTimer ctor
void  __fastcall FUN_00b638b0(void* timer);               // 0x00b638b0 cGonzagoTimer dtor
void  __fastcall FUN_00b18660(void* gameData);            // 0x00b18660 cGameData ctor
void  __fastcall FUN_00b184c0(void* gameData);            // 0x00b184c0 cGameData dtor
void* __cdecl FUN_00926720(void* self, u32 objectSize, u32 alignment, u32 maxObjects,
                          u32 objectSize2, int flag, void* alloc, void* free,
                          const char* name);             // 0x00926720 FixedAllocatorBase ctor
void  __fastcall FUN_00926640(void* self);                // 0x00926640 FixedAllocatorBase dtor
void  __fastcall FUN_00ae6970(void* vec);                 // 0x00ae6970 eastl/sp_vector dtor
float __cdecl FUN_00694fe0(void* out, const void* vec2); // 0x00694fe0 cTypedValueToStringT<Vector2>::Write
void* __cdecl FUN_0093c5a0(void* out, int name, int n);  // 0x0093c5a0 EA::ConvertToString16
void* __cdecl FUN_0093c6d0(void* out, const void* in);   // 0x0093c6d0 EA::ConvertToString16
void  __cdecl FUN_0056e2d0(void* dst, const void* src);  // 0x0056e2d0 eastl::wstring copy ctor
void  __cdecl FUN_00579a90(void* self, int n);           // 0x00579a90 eastl::wstring::range_initialize
char  __cdecl FUN_00ac8050(void* ser, int nameChar, void* elem);   // 0x00ac8050 write list<ref>
char  __cdecl FUN_00ae5530(void* ser, int nameChar, void* elem, const wchar_t* cls); // 0x00ae5530 write list<Key>
}

extern float gZeroF;        // 0x01485378  0.0f
extern float gHalfF;        // 0x01471064  0.5f
extern float gOneF;         // 0x01485720  1.0f
extern float gSixtyFourF;   // 0x0140f334  64.0f
extern float gInv64F;       // 0x0140e968  0.015625 = 1/64
extern float gTenF;         // 0x01473c70  10.0f
extern float gFifteenF;     // 0x014007f4  15.0f
extern float gFLTMax;       // 0x014718e8  FLT_MAX
extern float g065F;         // 0x014718d8  0.65f
extern float gAngleStep;    // 0x01693eac  2*pi / segment (runtime-init)
extern float gWateringHoleSeed[3];   // 0x01693e50.. (runtime-init)
extern float gSurfaceUpSeed[3];      // 0x01693ea0.. (runtime-init)
extern float gSignFlip;     // 0x013eb8b0  0x80000000 sign-mask word
extern u8    gAxisPerm[4];  // 0x014718b8  axis-permutation byte table
extern u8    gUnknownFlag;  // 0x015d8b55

namespace SP {

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

// A reference-counted object (intrusive list node payload).
class RefObj
{
  public:
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual bool IsValid();             // +0x2c
};

// vtable-bearing interface used for the +0x34 sub-object of a herd animal / nest.
class ISpatial
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vec3* GetPosition();          // +0x2c
};

}  // namespace SP

// cHerd with the retail byte offsets (PDB layout in the headers is shifted).
namespace SP {

class cHerd
{
  public:
    cHerd();                             // 0x00c6c110
    ~cHerd();                            // 0x00c6bde0
    // 0x00c6b660
    float* GuardLocation(Vec3* out, int index);
    // 0x00c6b8e0
    int ClaimEmptyGuardLocation(float unused, Vec3* out);
    // 0x00c6ba20
    void SetPosition(const Vec3* pos);
    // 0x00c6bdc0
    Vec3* GetWateringHolePosition();

    ISpatial* NestSpatial() { return reinterpret_cast<ISpatial*>(mpNest); }
    const Vec3* OwnPosition() { return reinterpret_cast<const Vec3*>(this); }

    unsigned char pad000[0x34];
    Vec3 mInitialPosition;               // 0x34
    unsigned char pad040[0x54 - 0x40];
    void** mpEggsBegin;                  // 0x54
    void** mpEggsEnd;                    // 0x58
    unsigned char pad05c[0x80 - 0x5c];
    int   mCurrentFeedingGrounds;        // 0x80  (= -1)
    u8    mb084;                         // 0x84
    u8    mbShouldEvolve;                // 0x85  (= 1)
    unsigned char pad086[0x94 - 0x86];
    float mDNAEvolutionThreshold;        // 0x94
    unsigned char pad098[0xa4 - 0x98];
    void* mpSpeciesProfile;              // 0xa4
    unsigned char pad0a8[0x108 - 0xa8];
    float mTerritoryRadius;              // 0x108
    int   mNumGuardsPerLocation;         // 0x10c
    int   mNumGuards;                    // 0x110  (= 1)
    float mGuardMinRadius;               // 0x114  (= 10.0f)
    float mGuardMaxRadius;               // 0x118  (= 15.0f)
    unsigned char pad11c[0x120 - 0x11c];
    int   mNumGuardLocations;            // 0x120
    int   mActivateBrainLevel;           // 0x124
    unsigned char pad128[0x130 - 0x128];
    unsigned char mGonzagoTimer130[0x20];// 0x130
    float mScaleMultiplier;              // 0x150
    float mHitpointOverride;             // 0x154
    float mDamageMultiplier;             // 0x158
    unsigned char pad15c[0x160 - 0x15c];
    void* mpNest;                        // 0x160
    RefObj* mpHerdMom;                   // 0x164
    unsigned char pad168[0x190 - 0x168];
    u8    mbExtinction;                  // 0x190
    u8    mbBestFriends;                 // 0x191
    u8    mbTransientHerd;               // 0x192
    void* mpEggLayer;                    // 0x194
    u8    mbEggsInNest;                  // 0x198
    unsigned char pad199[0x1a0 - 0x199];
    unsigned char mGonzagoTimer1a0[0x20];// 0x1a0
    unsigned char mChangeFeedingGrounds[0x20]; // 0x1c0
    int*  mValidLocationsBegin;          // 0x1e0
    int*  mValidLocationsEnd;            // 0x1e4
    int*  mValidLocationsCap;            // 0x1e8
    unsigned char pad1ec[0x1f4 - 0x1ec];
    u8*   mLocationStatusBegin;          // 0x1f4
    u8*   mLocationStatusEnd;            // 0x1f8
    u8*   mLocationStatusCap;            // 0x1fc
    unsigned char pad200[0x208 - 0x200];
    u8    mbCheckedForWateringHole;      // 0x208
    unsigned char pad209[0x20c - 0x209];
    Vec3  mWateringHolePosition;         // 0x20c
};

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// 0x00c6b660 -- SP::cHerd::GuardLocation (ret 8): write the guard-post position for `index`
// (0 = the herd's own origin) into `out`.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b660
float* SP::cHerd::GuardLocation(SP::Vec3* out, int index)
{
    if (index == 0) {
        const Vec3* src;
        if (mpNest)
            src = NestSpatial()->GetPosition();
        else
            src = OwnPosition();
        out->x = src->x;
        out->y = src->y;
        out->z = src->z;
        return (float*)out;
    }

    float radius = FUN_00572a10(mGuardMinRadius, mGuardMaxRadius);
    float span = (float)(index - 1) * gAngleStep;

    const Vec3* base;
    if (mpNest)
        base = NestSpatial()->GetPosition();
    else
        base = OwnPosition();

    float bx = base->x, by = base->y, bz = base->z;
    float inv = 1.0f / (float)sqrt(bx * bx + by * by + bz * bz);
    float ang = (span / (float)(mNumGuardsPerLocation - 1)) * gHalfF;
    float s = (float)sin(ang);
    float c = (float)cos(ang);

    Vec3 ring;
    ring.x = bx * inv * s;
    ring.y = by * inv * s;
    ring.z = bz * inv * s;

    Vec3 dir;
    if (mpNest) {
        void* q = (*(void*(__thiscall**)(ISpatial*, void*, const void*))
                   (*(void***)NestSpatial() + 0x5c / 4))(NestSpatial(), &dir, &ring);
        (void)q;
        FUN_0059aed0(&dir, &dir, &dir);   // placeholder: see note below
    } else {
        char orient[0x30];
        void* pm = SP_PlanetModel();
        FUN_00b7f190(pm, orient, base);
        FUN_0059aed0(&ring, gSurfaceUpSeed, orient);
        Vec3 scratch;
        scratch.x = ring.x; scratch.y = ring.y; scratch.z = ring.z;
        Vec3 unit;
        unit.x = bx * inv * c;
        unit.y = by * inv * c;
        unit.z = bz * inv * c;
        FUN_0059aed0(&dir, &scratch, &unit);
    }
    (void)ang; (void)s; (void)c;

    const Vec3* anchor;
    if (mpNest)
        anchor = NestSpatial()->GetPosition();
    else
        anchor = OwnPosition();

    Vec3 world;
    world.x = anchor->x + dir.x * radius;
    world.y = anchor->y + dir.y * radius;
    world.z = anchor->z + dir.z * radius;

    Vec3 result;
    void* pm2 = SP_PlanetModel();
    FUN_00b815a0(pm2, &result, &world);
    out->x = result.x;
    out->y = result.y;
    out->z = result.z;
    return (float*)out;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b8e0 -- SP::cHerd::ClaimEmptyGuardLocation (ret 8): pick the first valid guard post
// whose position passes the radius/height screen; returns its index or -1.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b8e0
int SP::cHerd::ClaimEmptyGuardLocation(float unused, SP::Vec3* out)
{
    (void)unused;
    FUN_00b3d3c0();
    void* planet = SP_PlanetModel();
    FUN_00b88420(planet);

    int count = (int)(mLocationStatusEnd - mLocationStatusBegin);
    for (int i = 0; i < count; ++i) {
        if (mLocationStatusBegin[i] != 0)
            continue;

        Vec3 loc;
        GuardLocation(&loc, i);

        int* slot = &mValidLocationsBegin[i];
        if (*slot == 1) {
            *slot = 0;
            Vec3 d;
            FUN_00b7ee70(&d, &loc);
            if (sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) < g065F) {
                float rad = FUN_00b7e840(planet, &loc);
                u32 r = *(u32*)&rad;
                if ((r & 0x98000000) == 0) {
                    *slot = 2;
                    goto claim;
                }
            }
        }
        if (*slot == 2) {
        claim:
            mLocationStatusBegin[i] = 1;
            out->x = loc.x;
            out->y = loc.y;
            out->z = loc.z;
            return i;
        }
        if (i == 0) {
            *slot = 2;
            mLocationStatusBegin[0] = 1;
            out->x = loc.x;
            out->y = loc.y;
            out->z = loc.z;
            return 0;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6ba20 -- SP::cHerd::SetPosition (ret 4): snap a normalised position to the host planet
// surface, move the nest, and record the herd origin.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ba20
void SP::cHerd::SetPosition(const SP::Vec3* pos)
{
    float px = pos->x, py = pos->y, pz = pos->z;
    float ax = (px < 0.0f) ? -px : px;
    float ay = (py < 0.0f) ? -py : py;
    float az = (pz < 0.0f) ? -pz : pz;

    int q0, q1;
    u32 axis;
    if (az >= ax && az >= ay) {
        q0 = (int)((px / pz + gOneF) * gSixtyFourF);
        q1 = (int)((py / az + gOneF) * gSixtyFourF);
        axis = (pz < 0.0f) ? 1u : 0u;
    } else if (ax >= ay) {
        q0 = (int)((pz / py + gOneF) * gSixtyFourF);
        q1 = (int)((px / ay + gOneF) * gSixtyFourF);
        axis = (py < 0.0f) ? 5u : 4u;
    } else {
        q0 = (int)((py / px + gOneF) * gSixtyFourF);
        q1 = (int)((pz / ax + gOneF) * gSixtyFourF);
        axis = (px < 0.0f) ? 3u : 2u;
    }
    if (q0 == 0x80) q0 = 0x7f;
    if (q1 == 0x80) q1 = 0x7f;

    float v = ((float)q0 + gHalfF) * gInv64F - gOneF;
    float w = ((float)q1 + gHalfF) * gInv64F - gOneF;
    float inv = 1.0f / (float)sqrt(v * v + w * w + gOneF);
    float sgn = (axis & 1) ? -inv : inv;

    const u8* perm = gAxisPerm + (axis >> 1) * 4;
    Vec3 dir;
    ((float*)&dir)[perm[0]] = sgn * v;
    ((float*)&dir)[perm[1]] = inv * w;
    ((float*)&dir)[perm[2]] = sgn;

    void* pm = SP_PlanetModel();
    float radius = FUN_00b7ef70(pm, &dir);
    dir.x *= radius;
    dir.y *= radius;
    dir.z *= radius;

    if (mpNest)
        FUN_00c6aab0(mpNest, &dir);
    mInitialPosition.x = dir.x;
    mInitialPosition.y = dir.y;
    mInitialPosition.z = dir.z;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6bd10 -- eastl::remove_if(first,last,pred): stable compaction of the elements the
// predicate accepts, returning one past the last kept slot.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6bd10
void** __cdecl FUN_00c6bd10(void** first, void** last, char (__cdecl* pred)(void*))
{
    for (; first != last; ++first) {
        if (pred(*first))
            break;
    }
    if (first != last)
        return FUN_00c6ae70(first + 1, last, first, pred);
    return first;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6bd60 -- intrusive-list node recycler: for each node release its payload ref and push the
// node onto the free list headed by *(self + 0x18).
// ---------------------------------------------------------------------------------------------
// @ 0x00c6bd60
void** __fastcall FUN_00c6bd60(void* self)
{
    char* node = *(char**)self;
    while (node != (char*)self) {
        char* cur = node;
        void* ref = *(void**)(cur + 8);
        node = *(char**)node;
        if (ref)
            (*(void(__thiscall**)(void*))(*(char**)ref + 4))(ref);
        *(char**)cur = *(char**)((char*)self + 0x18);
        *(char**)((char*)self + 0x18) = cur;
    }
    return (void**)self;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6bdc0 -- SP::cHerd::GetWateringHolePosition: lazily resolve the watering-hole position.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6bdc0
SP::Vec3* SP::cHerd::GetWateringHolePosition()
{
    if (!mbCheckedForWateringHole) {
        mbCheckedForWateringHole = 1;
        FUN_00c6b5b0(this);
    }
    return &mWateringHolePosition;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6bde0 -- SP::cHerd::~cHerd
// ---------------------------------------------------------------------------------------------
// @ 0x00c6bde0
SP::cHerd::~cHerd()
{
    void* vt0 = (void*)0x1471c10;
    void* vt1 = (void*)0x1471c00;
    void* a = mLocationStatusBegin;
    *(void**)this = vt0;
    *(void**)((char*)this + 4) = vt1;
    if (a && *(int*)((char*)a - 4) != 0)
        FUN_00f47380(a);
    void* b = *(void**)((char*)this + 0x1e0);
    if (b && *(int*)((char*)b - 4) != 0)
        FUN_00f47380(b);
    FUN_00b638b0((char*)this + 0x1c0);
    FUN_00b638b0((char*)this + 0x1a0);
    if (mpEggLayer) {
        void* m = mpEggLayer;
        (*(void(__thiscall**)(void*))(*(char**)m + 4))(m);
    }
    {
        char* listBase = (char*)this + 0x168;
        FUN_00c6bd60(listBase);
        FUN_00926640(listBase + 8);
    }
    if (mpHerdMom) {
        void* m = mpHerdMom;
        (*(void(__thiscall**)(void*))(*(char**)m + 4))(m);
    }
    if (mpNest) {
        void* m = mpNest;
        (*(void(__thiscall**)(void*))(*(char**)m + 4))(m);
    }
    FUN_00b638b0((char*)this + 0x130);
    void* c = *(void**)((char*)this + 0xa8);
    if (c && *(int*)((char*)c - 4) != 0)
        FUN_00f47380(c);
    void* d = *(void**)((char*)this + 0x68);
    if (d && *(int*)((char*)d - 4) != 0)
        FUN_00f47380(d);
    FUN_00ae6970((char*)this + 0x54);
    FUN_00ae6970((char*)this + 0x40);
    FUN_00b184c0(this);
}

// ---------------------------------------------------------------------------------------------
// 0x00c6bf20 -- serialise a Vector2 field as its wstring "list"/"type" entry.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6bf20
u8 __cdecl FUN_00c6bf20(void** serializer, int name, const void* vec2, int elem)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    WStr A;
    A.begin = (wchar_t*)0x1667bac;
    A.end   = (wchar_t*)0x1667bac;
    A.cap   = (wchar_t*)0x1667bad;
    FUN_00694fe0(&A, vec2);
    if (A.begin == A.end)
        goto done;
    {
        WStr B;
        bool noName = (name == 0);
        if (noName) {
            B.begin = (wchar_t*)0x1667bac;
            B.end   = (wchar_t*)0x1667bac;
            B.cap   = (wchar_t*)0x1667bae;
        } else {
            FUN_0093c5a0(&B, name, -1);
        }
        WStr C;
        FUN_0056e2d0(&C, &B);
        if (noName && ((char*)B.cap - (char*)B.begin & ~1) > 2 && B.begin)
            FUN_00f47380(B.begin);
        if (!noName && ((char*)B.cap - (char*)B.begin & ~1) > 2 && B.begin)
            FUN_00f47380(B.begin);

        WStr D;
        FUN_0093c6d0(&D, &A);
        bool ok;
        if (D.begin == D.end) {
            ok = (*(char(__thiscall**)(void**, int))(*(char**)serializer))(serializer, elem) != 0;
        } else {
            ok = (*(char(__thiscall**)(void**, wchar_t*))(*(char**)serializer))(serializer, D.begin) != 0;
            if (ok && gUnknownFlag != 0)
                ok = (*(char(__thiscall**)(void**, const wchar_t*, int))
                       (*(char**)serializer + 8))(serializer, L"type", elem) != 0;
        }
        if (ok) {
            if (D.begin == D.end)
                ok = (*(char(__thiscall**)(void**, int))(*(char**)serializer + 0xc))(serializer, elem) != 0;
            if (ok) {
                if (D.begin == D.end)
                    ok = (*(char(__thiscall**)(void**, int))(*(char**)serializer + 4))(serializer, elem) != 0;
                else
                    ok = (*(char(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
                         (serializer, D.begin) != 0;
            }
        }
        if (((char*)D.cap - (char*)D.begin & ~1) > 2 && D.begin)
            FUN_00f47380(D.begin);
        if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
            FUN_00f47380(C.begin);
        u8 r = ok ? 1 : 0;
        if (((char*)A.cap - (char*)A.begin) > 1 && A.begin)
            FUN_00f47380(A.begin);
        return r;
    }
done:
    if (((char*)A.cap - (char*)A.begin) > 1 && A.begin)
        FUN_00f47380(A.begin);
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6c110 -- SP::cHerd::cHerd
// ---------------------------------------------------------------------------------------------
// @ 0x00c6c110
SP::cHerd::cHerd()
{
    FUN_00b18660(this);
    *(void**)this = (void*)0x1471c10;
    *(void**)((char*)this + 4) = (void*)0x1471c00;

    char* p = (char*)this;
    *(void**)(p + 0x40) = 0;
    *(void**)(p + 0x44) = 0;
    *(void**)(p + 0x48) = 0;
    mInitialPosition.x = 0.0f;
    mInitialPosition.y = 0.0f;
    mInitialPosition.z = 0.0f;
    *(void**)(p + 0x54) = 0;
    *(void**)(p + 0x58) = 0;
    *(void**)(p + 0x5c) = 0;
    *(void**)(p + 0x68) = 0;
    *(void**)(p + 0x6c) = 0;
    *(void**)(p + 0x70) = 0;
    *(u8*)(p + 0x7c) = 0;
    mCurrentFeedingGrounds = -1;
    mb084 = 0;
    *(void**)(p + 0x88) = 0;
    *(void**)(p + 0x8c) = 0;
    *(void**)(p + 0x90) = 0;
    mbShouldEvolve = 1;
    mDNAEvolutionThreshold = gFLTMax;
    *(void**)(p + 0x98) = 0;
    *(void**)(p + 0x9c) = 0;
    *(void**)(p + 0xa0) = 0;
    mpSpeciesProfile = 0;
    *(void**)(p + 0xbc) = 0;
    *(void**)(p + 0xa8) = p + 0xc0;
    *(void**)(p + 0xac) = p + 0xc0;
    *(void**)(p + 0xb0) = p + 0xf0;
    *(float*)(p + 0x108) = 0.0f;
    *(void**)(p + 0x110) = (void*)1;
    *(void**)(p + 0xf0) = 0;
    *(void**)(p + 0xf4) = 0;
    *(void**)(p + 0xf8) = 0;
    *(u8*)(p + 0xfc) = 0;
    *(void**)(p + 0x100) = 0;
    *(void**)(p + 0x104) = 0;
    *(void**)(p + 0x10c) = 0;
    mGuardMinRadius = gTenF;
    mGuardMaxRadius = gFifteenF;
    *(u8*)(p + 0x128) = 1;
    *(void**)(p + 0x11c) = 0;
    *(void**)(p + 0x120) = 0;
    *(void**)(p + 0x124) = (void*)5;
    *(void**)(p + 0x12c) = 0;
    FUN_00b63890(p + 0x130);

    *(float*)(p + 0x150) = 0.0f;
    *(float*)(p + 0x154) = 0.0f;
    *(float*)(p + 0x158) = 0.0f;
    *(void**)(p + 0x15c) = 0;
    *(void**)(p + 0x160) = 0;
    *(void**)(p + 0x164) = 0;

    char localAlloc[0x20];
    FUN_00926720(localAlloc, 0xc, 4, 8, 0, -1, (void*)0x6abeb0, (void*)0xf47410, "Simulator/list");
    char* head = p + 0x168;
    for (int i = 0; i < 8; ++i)
        *(u32*)(head + 8 + i * 4) = *(u32*)(localAlloc + i * 4);
    *(void**)head = head;
    *(void**)(head + 4) = head;
    FUN_00926640(localAlloc);

    *(u8*)(p + 0x190) = 0;
    *(u8*)(p + 0x191) = 0;
    *(u8*)(p + 0x192) = 0;
    *(void**)(p + 0x194) = 0;
    *(u8*)(p + 0x198) = 0;
    FUN_00b63890(p + 0x1a0);
    FUN_00b63890(p + 0x1c0);

    *(void**)(p + 0x1e0) = 0;
    *(void**)(p + 0x1e4) = 0;
    *(void**)(p + 0x1e8) = 0;
    *(void**)(p + 0x1f4) = 0;
    *(void**)(p + 0x1f8) = 0;
    *(void**)(p + 0x1fc) = 0;
    mbCheckedForWateringHole = 0;
    mWateringHolePosition.x = gWateringHoleSeed[0];
    mWateringHolePosition.y = gWateringHoleSeed[1];
    mWateringHolePosition.z = gWateringHoleSeed[2];
}

// ---------------------------------------------------------------------------------------------
// 0x00c6c390 -- write a list of reference-counted objects as "list" entries.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6c390
u8 __cdecl FUN_00c6c390(void** serializer, int name, void** list)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    if (list[0] == list[1])
        return 1;

    bool noName = (name == 0);
    WStr N;
    if (noName) {
        N.begin = 0; N.end = 0; N.cap = 0;
        FUN_00579a90(&N, 0);
    } else {
        FUN_0093c5a0(&N, name, -1);
    }
    WStr C;
    FUN_0056e2d0(&C, &N);
    if (noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);
    if (!noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);

    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);

    u8 ok = 1;
    char* end = (char*)list[1];
    for (char* it = (char*)list[0]; it != end; it += 4) {
        if (ok)
            ok = FUN_00ac8050(serializer, 0, it) != 0;
    }
    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);
    if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
        FUN_00f47380(C.begin);
    return ok;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6c4e0 -- write a list of EA::ResourceMan::Key entries.
// ---------------------------------------------------------------------------------------------
// @ 0x00c6c4e0
u8 __cdecl FUN_00c6c4e0(void** serializer, int name, void** list)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    if (list[0] == list[1])
        return 1;

    bool noName = (name == 0);
    WStr N;
    if (noName) {
        N.begin = 0; N.end = 0; N.cap = 0;
        FUN_00579a90(&N, 0);
    } else {
        FUN_0093c5a0(&N, name, -1);
    }
    WStr C;
    FUN_0056e2d0(&C, &N);
    if (noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);
    if (!noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);

    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);

    u8 ok = 1;
    char* end = (char*)list[1];
    for (char* it = (char*)list[0]; it != end; it += 0xc) {
        if (ok)
            ok = FUN_00ae5530(serializer, 0, it, L"EA::ResourceMan::Key") != 0;
    }
    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);
    if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
        FUN_00f47380(C.begin);
    return ok;
}
