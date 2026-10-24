// Slice s00bd2840: the single function here is 0x00BD2AF0 (1845 bytes, __thiscall, no args), an
// object whose embedded cLocomotiveObject (at +0x34) supplies position, orientation and scale.
// It rebuilds the object's world-space geometry:
//   - every local hull point (+0x2a0) is scaled, rotated by the orientation quaternion, offset by
//     the position and snapped to the planet surface (DirectionToSurfacePosition) -> +0x2c8;
//   - every local normal (+0x2b4) is rotated by the same quaternion -> +0x2dc;
//   - the dirty flag (+0x2f0) is set;
//   - every local part transform (+0x2f4) is composed with (position, scale, rotation) -> +0x308;
//   - the attached helper object (+0x1f0), if any, is told to update.
// The class name is Claude-coined (the PDB candidate "SP::AddTribeRoads" is a caller-scored guess).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE; no EH frame).
#include "types.h"

// ---- math ---------------------------------------------------------------------------------
struct Vector3 { float x, y, z; };                       // plain copies go through integer registers

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

struct Matrix3 { float m[9]; };

// cSPTransform / cTransform (0x38 bytes)
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mOffset;
    float mScale;
    Matrix3 mRotation;

    cSPTransform() : mFlags(0), mModificationCount(0) {}
    cSPTransform& operator=(const cSPTransform& o);      // 0x00537dc0
    void Accumulate(const cSPTransform* other);          // 0x0040ccb0
    void SetOffset(const Vector3& v) { mOffset = v; mFlags |= 4; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetRotation(const Matrix3& r) { mRotation = r; mFlags |= 2; mModificationCount++; }
};

namespace SP { Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion& q); }   // 0x0059c190 (cdecl)

// ---- containers -----------------------------------------------------------------------------
template <class T> struct SpVector {                     // eastl::vector with sp_vector_allocator (0x14 bytes)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void resize(int n);
};
template <> void SpVector<Vector3>::resize(int n);       // 0x00473810
template <> void SpVector<cSPTransform>::resize(int n);  // 0x0041e3b0

// ---- game objects ---------------------------------------------------------------------------
class cLocomotiveObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    /* 2ch */ virtual const Vector3& GetPosition();
    /* 30h */ virtual const Quaternion& GetOrientation();
    /* 34h */ virtual float GetScale();
};

struct cPlanetModel {
    Vector3* DirectionToSurfacePosition(Vector3* out, Vector3* dir);   // 0x00b815a0
};
namespace SP { cPlanetModel* __cdecl PlanetModel(); }                  // 0x00b3d350

struct cHelperObject { void Update(); };                               // 0x00be0020 (thiscall)

class cPlacedModelBase {
public:
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0c();
    virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28(); virtual void b2c();
    virtual void* GetWorld();                       // +0x30
    virtual void b34(); virtual void b38(); virtual void b3c(); virtual void b40();
    virtual void b44(); virtual void b48(); virtual void b4c(); virtual void b50();
    virtual void b54(); virtual void b58(); virtual void b5c(); virtual void b60();
    virtual void b64(); virtual void b68(); virtual void b6c(); virtual void b70();
    virtual void b74(); virtual void b78(); virtual void b7c(); virtual void b80();
    virtual void* Slot84();                         // +0x84
};

class cPlacedModel : public cPlacedModelBase {
public:
    char _pad00[0x30];
    cLocomotiveObject mLocomotive;           // +0x34
    char _pad38[0x1f0 - 0x38];
    cHelperObject* mpHelper;                 // +0x1f0
    char _pad1f4[0x2a0 - 0x1f4];
    SpVector<Vector3> mLocalPoints;          // +0x2a0
    SpVector<Vector3> mLocalNormals;         // +0x2b4
    SpVector<Vector3> mWorldPoints;          // +0x2c8
    SpVector<Vector3> mWorldNormals;         // +0x2dc
    uint8_t mWorldDirty;                     // +0x2f0
    char _pad2f1[3];
    SpVector<cSPTransform> mLocalTransforms; // +0x2f4
    SpVector<cSPTransform> mWorldTransforms; // +0x308

    void UpdateWorldGeometry();
};

// Rotate a vector by a unit quaternion (standard quaternion-to-matrix terms).
static __forceinline Vector3 Rotate(const Quaternion& q, const Vector3& v)
{
    float yy = q.y * q.y;
    float xy = q.y * q.x;
    float zz = q.z * q.z;
    float zx = q.z * q.x;
    float zy = q.z * q.y;
    float zw = q.z * q.w;
    float xx = q.x * q.x;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    Vector3 r;
    r.x = ((xy - zw) * v.y + (wy + zx) * v.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * v.x;
    r.y = ((zw + xy) * v.x + (zy - wx) * v.z) * 2.0f + (1.0f - (zz + xx) * 2.0f) * v.y;
    r.z = ((zx - wy) * v.x + (wx + zy) * v.y) * 2.0f + (1.0f - (yy + xx) * 2.0f) * v.z;
    return r;
}

// @ 0x00BD2AF0
void cPlacedModel::UpdateWorldGeometry()
{
    int count = mLocalPoints.size();
    mWorldPoints.resize(count);
    mWorldNormals.resize(count);

    float scale = mLocomotive.GetScale();
    Quaternion q = mLocomotive.GetOrientation();
    const Vector3* pPosition = &mLocomotive.GetPosition();

    if (count > 0) {
        float yy = q.y * q.y;
        float xy = q.y * q.x;
        float zz = q.z * q.z;
        float zx = q.z * q.x;
        float zy = q.z * q.y;
        float zw = q.z * q.w;
        float xx = q.x * q.x;
        float wx = q.w * q.x;
        float wy = q.w * q.y;
        float a01 = xy - zw;
        float a02 = wy + zx;
        float m00 = 1.0f - (zz + yy) * 2.0f;
        float a12 = zy - wx;
        float a10 = zw + xy;
        float m11 = 1.0f - (zz + xx) * 2.0f;
        float a21 = wx + zy;
        float a20 = zx - wy;
        float m22 = 1.0f - (yy + xx) * 2.0f;

        for (int i = 0; i < count; ++i) {
            Vector3 p = mLocalPoints[i];
            Vector3 v;
            v.x = p.x * scale;
            v.y = p.y * scale;
            v.z = p.z * scale;
            Vector3 r = Rotate(q, v);
            Vector3 dir;
            dir.x = pPosition->x + r.x;
            dir.y = pPosition->y + r.y;
            dir.z = pPosition->z + r.z;
            Vector3 tmp;
            dir = *SP::PlanetModel()->DirectionToSurfacePosition(&tmp, &dir);
            mWorldPoints[i] = dir;

            float nx = mLocalNormals[i].x;
            float ny = mLocalNormals[i].y;
            float nz = mLocalNormals[i].z;
            Vector3& out = mWorldNormals[i];
            out.x = (a02 * nz + a01 * ny) * 2.0f + m00 * nx;
            out.y = (a10 * nx + a12 * nz) * 2.0f + m11 * ny;
            out.z = (a20 * nx + a21 * ny) * 2.0f + m22 * nz;
        }
    }

    mWorldDirty = 1;

    Matrix3 rotation;
    cSPTransform xf;
    xf.SetOffset(*pPosition);
    xf.SetRotation(*SP::Matrix3FromQuaternion(&rotation, q));

    int numParts = mLocalTransforms.size();
    mWorldTransforms.resize(numParts);
    for (int i = 0; i < numParts; ++i) {
        cSPTransform t;
        t.SetOffset(xf.mOffset);
        t.SetScale(scale);
        t.SetRotation(xf.mRotation);
        t.Accumulate(&mLocalTransforms[i]);
        mWorldTransforms[i] = t;
    }

    if (mpHelper)
        mpHelper->Update();
}

// =============================================================================================
// Sibling functions in the same 0x00bd2xxx family (all __thiscall unless noted).
//   0x00bd2840  property-list enumerator
//   0x00bd2a10  forward bulk copy of 0xc64-byte records
//   0x00bd2a80  backward bulk copy of the same records
//   0x00bd3230  cCommunity::func58h passthrough + world-geometry refresh
//   0x00bd3280  "is there another community of my kind near me" finder
//   0x00bd3380  set the approach direction and refresh
//   0x00bd3500  cCommunity::func54h passthrough + world-geometry refresh
//   0x00bd3550  like 0x00bd3280 but the identity test is FUN_00c9fee0
//   0x00bd3640  set position (3 floats), refresh if changed
//   0x00bd36c0  set orientation (4 floats), refresh if changed
// =============================================================================================

#include <math.h>

// ---- additional globals ----------------------------------------------------------------------
extern const float g_f1486110;  // 0x01486110  5.0f
extern const float g_f13ec4b8;  // 0x013ec4b8  +1e-08f

extern const wchar_t kWList[];      // 0x013f58ac  L"list"
extern const wchar_t kWUint32[];    // 0x01401158  L"uint32_t"

// ---- record copied by 0x00bd2a10 / 0x00bd2a80 ------------------------------------------------
struct Vec20B {
    uint8_t mData[0x20];
    Vec20B& operator=(const Vec20B& o);           // 0x00473500
};

struct Record {                                   // 0x0c64 bytes
    cSPTransform mTransform;                      // +0x00
    float        mField38;                        // +0x38
    float        mField3c;                        // +0x3c
    uint32_t     mField40;                        // +0x40
    uint32_t     mField44;                        // +0x44
    uint32_t     mField48;                        // +0x48
    Vec20B       mVec4c;                          // +0x4c
    uint8_t      mRest[0x0c64 - 0x6c];
};

// ?Assign@cSPTransformOps@@QAEPAU1@PBX@Z
struct cSPTransformOps {
    void* mRaw;
    cSPTransformOps* Assign(const void* src);     // 0x00537dc0
};

// ---- the object these methods belong to (its vptr sits at +0x34 of cPlacedModel) -------------
class cCommunity {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void* GetWorld();                     // +0x30  (owner world / geometry object)
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual void* Slot84();                       // +0x84

    Vector3    mPosition;                         // +0x04
    Quaternion mOrientation;                      // +0x10
    char       _pad20[0x30c - 0x20];
    uint8_t    mDirty30c;                         // +0x30c
    char       _pad30d[3];
    void*      mpChild310;                        // +0x310
    Vector3    mDir314;                           // +0x314
    char       _pad320[4];
    void*      mpField324;                        // +0x324

    void func54h(float* dir);                     // 0x00c88670 (ret 4)
    void func58h(void* arg);                      // 0x00c886d0 (ret 4)

    void    CallFunc58(void* arg);                // 0x00bd3230
    void    CallFunc54(float* dir);               // 0x00bd3500
    uint8_t FindPeerA(cCommunity* other);         // 0x00bd3280
    uint8_t FindPeerB(cCommunity* other);         // 0x00bd3550
    void    SetDirection(float* dir);             // 0x00bd3380
    void    SetPosition(float* v);                // 0x00bd3640
    void    SetOrientation(float* v);             // 0x00bd36c0

    cPlacedModel* Owner() { return (cPlacedModel*)((char*)this - 0x34); }
};

// ---- object returned by GetWorld() and by the noun vector -----------------------------------
class cObject {
public:
    virtual void o00(); virtual void o04(); virtual void o08(); virtual void o0c();
    virtual void o10(); virtual void o14(); virtual void o18(); virtual void o1c();
    virtual void* TypeId();                       // +0x20
    virtual void o24(); virtual void o28(); virtual void o2c();
    virtual void o30(); virtual void o34(); virtual void o38(); virtual void o3c();
    virtual void o40(); virtual void o44(); virtual void o48();
    virtual int  Slot4c();                        // +0x4c
    virtual void o50();
    virtual void* Slot54();                       // +0x54

    void SetOwner(void* owner);                   // 0x00bd7f20 (ret 4): byte [this+0x6c] = 1
};

// cObject embedded at +0x508 with its own vtable (the +0x54 test in 0x00bd3280).
class cObjectHeader {
public:
    virtual void h00(); virtual void h04(); virtual void h08(); virtual void h0c();
    virtual void h10(); virtual void h14(); virtual void h18(); virtual void h1c();
    virtual void h20(); virtual void h24(); virtual void h28(); virtual void h2c();
    virtual void h30(); virtual void h34(); virtual void h38(); virtual void h3c();
    virtual void h40(); virtual void h44(); virtual void h48(); virtual void h4c();
    virtual void h50();
    virtual void* Slot54();                       // +0x54
};

// ---- external helpers ------------------------------------------------------------------------
extern "C" float __fastcall SampleChildField260(void* child);       // 0x00bebe40
extern "C" void* __fastcall CommunityKey(void* self);              // 0x00c9fee0
extern "C" void* __cdecl FUN_00cd7d10();                           // 0x00cd7d10
extern "C" void* __cdecl FUN_00d3d420();                           // 0x00d3d420
extern "C" void* __cdecl FUN_00ae72d0();                           // 0x00ae72d0
extern "C" void* __cdecl FUN_00b1e500();                           // 0x00b1e500
namespace SP { void* GetCurrentGameMode(); }                       // 0x00b5b800

// The noun manager and its game-data vector lookup (0x00b3d300 / 0x00b21340).
class cGameNounManager {
public:
    void* GetGameDataVector(void* f0, void* f1, void* f2, void* f3, void* type);  // 0x00b21340 (ret 0x14)
};
extern "C" void* __cdecl SP_NounManager();                         // 0x00b3d300

// ---- console / string helpers for 0x00bd2840 -------------------------------------------------
extern "C" void* __cdecl EA_ConvertToString16(void* out, const char* src, int len);  // 0x0093c5a0
extern "C" void  __fastcall WStringRangeInitialize(void* self, void* a, void* b);    // 0x00579a90
extern "C" void  __fastcall WStringConstruct(void* self, const void* src);           // 0x0056e2d0
extern "C" void* __cdecl operator_delete(void* p);                                   // 0x00f47380
extern "C" char  __fastcall TypedValueToStringShort(void* self, int a, int b, const wchar_t* t);  // 0x00675990

// The property-list chunked vector walked by 0x00bd2840.
struct PropBlock {
    int* mpFirst;               // +0x00
    int* mpLast;                // +0x04
    int* mpCur;                 // +0x08
    int* mpNextArray;           // +0x0c
    int* mpIter;                // +0x10
    int* mpChunkBase;           // +0x14
    int* mpEnd;                 // +0x18
};

class PropVisitor {
public:
    virtual void SetName(const wchar_t* name);   // +0x00
    virtual void SetValue(const wchar_t* name);  // +0x04
};

// The refresh tail shared by 0x00bd3230/0x00bd3380/0x00bd3500/0x00bd3640/0x00bd36c0:
//   owner->UpdateWorldGeometry(); obj = self->GetWorld(); if (obj && obj->TypeId()==0x18c43e8) flag(obj);
static __forceinline void RefreshTail(cCommunity* self)
{
    cPlacedModel* owner = (cPlacedModel*)((char*)self - 0x34);
    owner->UpdateWorldGeometry();
    cObject* obj = (cObject*)owner->GetWorld();
    if (obj != 0 && obj->TypeId() == (void*)0x018c43e8)
        obj->SetOwner(owner);
}

// @ 0x00bd2840
uint8_t FUN_00bd2840(int* visitor, const char* name, PropBlock* block)
{
    uint8_t result = 1;
    if (block->mpCur == block->mpEnd)
        return result;

    bool noName = (name == 0);
    wchar_t* pName;
    wchar_t  bufA[6];
    wchar_t  bufB[6];

    if (noName) {
        int zeroed[3];
        zeroed[0] = 0; zeroed[1] = 0; zeroed[2] = 0;
        WStringRangeInitialize(zeroed, 0, 0);
        WStringConstruct((void*)zeroed, 0);
        pName = (wchar_t*)zeroed[1];
        if (2 < (int)((char*)zeroed[2] - (char*)zeroed[1] & 0xfffffffe) && zeroed[1] != 0)
            operator_delete((void*)zeroed[1]);
    }
    else {
        void* s = EA_ConvertToString16(bufA, name, -1);
        WStringConstruct(bufB, s);
        if (2 < (int)((char*)bufA[2] - (char*)bufA[0] & 0xfffffffe) && bufA[0] != 0)
            operator_delete((void*)bufA[0]);
        pName = bufB;
    }

    const wchar_t* label = pName;
    ((PropVisitor*)visitor)->SetName(label);

    int* i = block->mpIter;                 // +0x10
    int* chunkEnd = block->mpNextArray;     // +0x0c
    int* chunkBase = block->mpChunkBase;    // +0x14
    int* end = block->mpEnd;                // +0x18

    while (i != end) {
        if (result) {
            if (!TypedValueToStringShort(visitor, 0, *i, kWUint32))
                result = 0;
        }
        ++i;
        if (i == chunkEnd) {
            i = (int*)chunkBase[1];
            chunkBase += 1;
            chunkEnd = (int*)((char*)i + 0x100);
        }
    }

    const wchar_t* lbl = pName;
    ((PropVisitor*)visitor)->SetValue(lbl);
    if (2 < (int)((char*)block->mpCur - (char*)pName & 0xfffffffe) && pName != 0)
        operator_delete(pName);

    return result;
}

// @ 0x00bd2a10
Record* FUN_00bd2a10(Record* begin, Record* end, Record* dst)
{
    if (begin != end) {
        do {
            ((cSPTransformOps*)dst)->Assign(begin);
            dst->mField38 = begin->mField38;
            dst->mField3c = begin->mField3c;
            dst->mField40 = begin->mField40;
            dst->mField44 = begin->mField44;
            dst->mField48 = begin->mField48;
            dst->mVec4c = begin->mVec4c;
            begin = (Record*)((char*)begin + 0x0c64);
            dst   = (Record*)((char*)dst   + 0x0c64);
        } while (begin != end);
    }
    return dst;
}

// @ 0x00bd2a80
Record* FUN_00bd2a80(Record* begin, Record* end, Record* dst)
{
    if (end != begin) {
        do {
            end = (Record*)((char*)end - 0x0c64);
            dst = (Record*)((char*)dst - 0x0c64);
            ((cSPTransformOps*)dst)->Assign(end);
            dst->mField38 = end->mField38;
            dst->mField3c = end->mField3c;
            dst->mField40 = end->mField40;
            dst->mField44 = end->mField44;
            dst->mField48 = end->mField48;
            dst->mVec4c = end->mVec4c;
        } while (end != begin);
    }
    return dst;
}

// @ 0x00bd3230
void cCommunity::CallFunc58(void* arg)
{
    cCommunity* self = this;
    self->func58h(arg);
    RefreshTail(self);
}

// @ 0x00bd3500
void cCommunity::CallFunc54(float* dir)
{
    cCommunity* self = this;
    self->func54h(dir);
    RefreshTail(self);
}

// @ 0x00bd3280
uint8_t cCommunity::FindPeerA(cCommunity* other)
{
    cCommunity* self = this;
    int* o = (int*)other;
    if (o[0x0b20 / 4] == 1) {
        void* key = (self != 0) ? (void*)((char*)self + 0x34) : 0;
        if (CommunityKey(other) == key)
            return 0;
    }

    int* vec = (int*)((cGameNounManager*)SP_NounManager())->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ae72d0, (void*)FUN_00b1e500,
        (void*)0x018c6de8);
    int count = (int)(vec[2] - vec[1]) >> 2;
    for (int i = 0; i < count; ++i) {
        cObject* n = *(cObject**)(vec[1] + i * 4);
        if (n == (cObject*)other)
            continue;
        int a = n->Slot4c();
        int b = ((cObject*)other)->Slot4c();
        if (a != b)
            continue;
        if (*(int*)((char*)n + 0x0b20) != 1)
            continue;
        void* key = (self != 0) ? (void*)((char*)self + 0x120) : 0;
        void* got = ((cObjectHeader*)((char*)n + 0x508))->Slot54();
        if (got == key)
            return 1;
    }
    return 0;
}

// @ 0x00bd3550
uint8_t cCommunity::FindPeerB(cCommunity* other)
{
    cCommunity* self = this;
    int* o = (int*)other;
    if (o[0x0b20 / 4] == 1) {
        void* key = (self != 0) ? (void*)((char*)self + 0x34) : 0;
        if (CommunityKey(other) == key)
            return 0;
    }

    int* vec = (int*)((cGameNounManager*)SP_NounManager())->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ae72d0, (void*)FUN_00b1e500,
        (void*)0x018c6de8);
    int count = (int)(vec[2] - vec[1]) >> 2;
    for (int i = 0; i < count; ++i) {
        cObject* n = *(cObject**)(vec[1] + i * 4);
        if (n == (cObject*)other)
            continue;
        int a = n->Slot4c();
        int b = ((cObject*)other)->Slot4c();
        if (a != b)
            continue;
        if (*(int*)((char*)n + 0x0b20) != 1)
            continue;
        void* key = (self != 0) ? (void*)((char*)self + 0x34) : 0;
        if (CommunityKey(n) == key)
            return 1;
    }
    return 0;
}

// @ 0x00bd3380
void cCommunity::SetDirection(float* dir)
{
    cCommunity* self = this;
    cPlacedModel* owner = (cPlacedModel*)((char*)self - 0x34);
    float offset = g_f1486110;
    if (SP::GetCurrentGameMode() == (void*)0x01654c10)
        offset = 0.0f;

    if (owner->Slot84() != 0) {
        void* s2 = owner->Slot84();
        if (*(void**)((char*)s2 + 0x324) != 0) {
            void* s3 = owner->Slot84();
            offset = SampleChildField260(*(void**)((char*)s3 + 0x324));
        }
    }

    self->mDir314 = *(Vector3*)dir;

    Vector3 d = *(Vector3*)dir;
    float inv = 1.0f / sqrtf((d.x * d.x + d.y * d.y) + d.z * d.z + g_f13ec4b8);
    float t[3];
    t[0] = d.x + (d.x * inv) * offset;
    t[1] = d.y + (d.y * inv) * offset;
    t[2] = d.z + (d.z * inv) * offset;

    self->func54h(t);
    RefreshTail(self);

    void* child = self->mpChild310;
    if (child != 0) {
        void* slot = *(void**)((char*)child + 0x70);
        void (*fn)(void*, float*) = *(void (**)(void*, float*))((char*)slot + 0x38);
        fn((char*)child + 0x70, t);
    }
}

// @ 0x00bd3640
void cCommunity::SetPosition(float* v)
{
    cCommunity* self = this;
    if (v[0] != self->mPosition.x || v[1] != self->mPosition.y || v[2] != self->mPosition.z) {
        self->func54h(v);
        RefreshTail(self);
        self->mDirty30c = 1;
    }
}

// @ 0x00bd36c0
void cCommunity::SetOrientation(float* v)
{
    cCommunity* self = this;
    if (v[0] != self->mOrientation.x || v[1] != self->mOrientation.y ||
        v[2] != self->mOrientation.z || v[3] != self->mOrientation.w) {
        self->func58h(v);
        RefreshTail(self);
        self->mDirty30c = 1;
    }
}
