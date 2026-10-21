// Slice s00b41900: Simulator geometry/physics helpers (MSVC 2008 SP1, /O2).
//
//  0x00b41900  reflect contact points of a triangle raycast onto the triangle plane
//  0x00b41a40  filtered near-list iterator constructor
//  0x00b41c80  hash table copy constructor (bucket array + node chains)
//  0x00b41dc0  pool: allocate a node for an object pointer
//  0x00b41e20  pool: release/free a bucket array of node chains
//  0x00b41ea0  lower_bound over 8-byte {key,value} pairs
//  0x00b41ee0  property lookup by message id            (separate section below)
//  0x00b421b0  creature state update                    (separate section below)
//  0x00b42370  collision shape: transform its two local points to world space
//  0x00b425b0  collision shape: project a direction (center dot dir, support extent)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 for sqrt/fabs chains).
#include "types.h"
#include <math.h>
#include <float.h>

// ----------------------------------------------------------------------------
// vector / matrix / transform
// ----------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    __declspec(noinline) Matrix3(const Matrix3& o);   // 0x0041cb40
    __declspec(noinline) Matrix3& operator=(const Matrix3& o);
    Matrix3& SetIdentity();
};

// 0x0167ec08: identity matrix referenced as an external constant.
extern Matrix3 g_identity;

#define MAT3_ASSIGN_DEF(CLS)                                                             \
    __declspec(noinline) CLS::CLS(const CLS& o)                                          \
    {                                                                                    \
        for (int i = 0; i < 9; i++)                                                      \
            ((float*)this)[i] = ((const float*)&o)[i];                                   \
    }                                                                                    \
    __declspec(noinline) CLS& CLS::operator=(const CLS& o)                               \
    {                                                                                    \
        for (int i = 0; i < 9; i++)                                                      \
            ((float*)this)[i] = ((const float*)&o)[i];                                   \
        return *this;                                                                    \
    }

MAT3_ASSIGN_DEF(Matrix3)

Matrix3& Matrix3::SetIdentity()
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
    return *this;
}

// v * m  (row-major storage, row-vector convention)
__forceinline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    return Vector3(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
                   v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
                   v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]);
}
__forceinline Vector3 operator*(float s, const Vector3& v)
{
    return Vector3(s * v.x, s * v.y, s * v.z);
}
__forceinline Vector3 operator*(const Vector3& v, float s)
{
    return s * v;
}
__forceinline Vector3 operator+(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}
__forceinline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}
__forceinline float Dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

extern const Vector3 kZero;        // 0x0167eb8c
extern float h;                    // 0x01471064 (0.5f)

// Dynamic initializer of the identity constant (has its own fixed source order, so it
// has to be emitted before the transform local below is constructed in place).
Matrix3 g_identity = Matrix3().SetIdentity();

struct cSPTransform {
    enum { kFlagScale = 1, kFlagRotation = 2, kFlagOffset = 4 };
    uint16_t mFlags;               // +0x00
    uint16_t mModificationCount;   // +0x02
    Vector3 mTranslation;          // +0x04
    float mScale;                  // +0x10
    Matrix3 mRotation;             // +0x14

    cSPTransform();
};

// Local transform objects are zero-filled and then carry the identity rotation.
__declspec(noinline) cSPTransform::cSPTransform()
{
    mFlags = 0;
    mModificationCount = 0;
    mTranslation = kZero;
    mScale = 1.0f;
    mRotation = g_identity;
}

struct BoundingBox {
    Vector3 lower, upper;
};

// ----------------------------------------------------------------------------
// collision shape (slices s00b3fe40 / s00b42760 carry the same class)
// ----------------------------------------------------------------------------
class CollisionShape {
public:
    uint32_t pad00[3];
    int mShapeType;                // +0x0c: 0/1 sphere-like, 2 box, other
    uint32_t pad10[(0xf8 - 0x10) / 4];
    Vector3 mAxes[3];              // +0x0f8: box axes (rows)
    Vector3 mLocalPointA;          // +0x11c
    Vector3 mLocalPointB;          // +0x128

    void GetCenter(Vector3* out);                 // 0x00b3d9c0
    float GetRadius();                            // 0x00b3d630
    void AddToBoundingBox(BoundingBox* box);      // 0x00b3f420
    void GetTransform(cSPTransform* out);         // 0x00b3f6c0

    void GetWorldPoints(Vector3* a, Vector3* b);
    void ProjectDirection(const Vector3& dir, float* centerDot, float* extent);
};

// @ 0x00b42370
void CollisionShape::GetWorldPoints(Vector3* a, Vector3* b)
{
    cSPTransform xform;
    GetTransform(&xform);
    *a = mLocalPointA;
    *b = mLocalPointB;
    if (xform.mFlags & cSPTransform::kFlagRotation) {
        *a = *a * xform.mRotation;
    }
    *a = *a * xform.mScale + xform.mTranslation;
    if (xform.mFlags & cSPTransform::kFlagRotation)
        *b = *b * xform.mRotation;
    *b = *b * xform.mScale + xform.mTranslation;
}


// @ 0x00b425b0
void CollisionShape::ProjectDirection(const Vector3& dir, float* centerDot, float* extent)
{
    Vector3 center;
    GetCenter(&center);

    BoundingBox box;
    box.lower.x = FLT_MAX;
    box.lower.y = FLT_MAX;
    box.lower.z = FLT_MAX;
    box.upper.x = -FLT_MAX;
    box.upper.y = -FLT_MAX;
    box.upper.z = -FLT_MAX;
    AddToBoundingBox(&box);

    float fx = (box.upper.x - box.lower.x) * h * 0.5f;
    float fy = (box.upper.y - box.lower.y) * h * 0.5f;
    float fz = (box.upper.z - box.lower.z) * h * 0.5f;
    if (mShapeType != 2) {
        float r = GetRadius();
        fx = r;
        fy = r;
        fz = r;
    }
    Vector3 ext(fx, fy, fz);

    *centerDot = Dot(dir, center);
    float ex = fabs(Dot(mAxes[2], dir)) * ext.x;
    float ey = fabs(Dot(mAxes[0], dir)) * ext.y;
    float ez = fabs(Dot(mAxes[1], dir)) * ext.z;
    *extent = (float)((ex + ey) + ez);
}

// ----------------------------------------------------------------------------
// external helpers
// ----------------------------------------------------------------------------
void* __cdecl EAAllocate(uint32_t size, const char* pName, int a, int b, const char* file,
                         int line);                       // 0x00f473a0
extern "C" void* __cdecl memset(void*, int, unsigned);    // 0x011e073e
void __cdecl operator_delete(void* p);                    // 0x00f47380

// raycast against the triangle fan in `verts`, appends contacts and their count.
bool __cdecl CastFan(const void* self, void* a2, void* a3, void* a4, const void* contacts,
                     int* pCount);                         // 0x00b3ef30

// normalized normal of triangle (a, b, c)
void __cdecl TriangleNormal(Vector3* out, const Vector3* a, const Vector3* b, float cx, float cy,
                            float cz);                     // 0x00b3d8d0

// @ 0x00b41900
int CastFanTriangle(const float* fan, void* a2, void* a3, void* a4, Vector3* out,
                    const Vector3* contacts)
{
    int nContacts = 0;
    if (!CastFan(fan, a2, a3, a4, contacts, &nContacts))
        return 0;

    Vector3 normal;
    TriangleNormal(&normal, (const Vector3*)fan, (const Vector3*)(fan + 3), fan[6], fan[7], fan[8]);

    float d0 = fan[1] * normal.y + fan[2] * normal.z;
    d0 += fan[0] * normal.x;

    const Vector3* in = contacts;
    for (int i = nContacts; i > 0; i--) {
        Vector3 p = *in;
        float d = (p.z * normal.z + p.y * normal.y) + p.x * normal.x - d0;
        out->x = p.x - d * normal.x;
        out->y = p.y - d * normal.y;
        out->z = p.z - d * normal.z;
        out++;
        in++;
    }
    return nContacts;
}

// ----------------------------------------------------------------------------
// near-list filtering
// ----------------------------------------------------------------------------
struct NearFilter {
    bool __thiscall IsValid(void* p);     // 0x00c02600
};

struct NearRange {
    void** mpBegin;                       // +0
    void** mpEnd;                         // +4
};

struct NearIter {
    void** mpCurrent;                     // +0
    void** mpEnd;                         // +4
    NearFilter mFilter;                   // +8

    __thiscall NearIter(const NearRange& range, bool bAuto);
    void Advance();            // 0x00b3d850
};

// @ 0x00b41a40
NearIter::NearIter(const NearRange& range, bool)
{
    mpCurrent = range.mpBegin;
    mpEnd = range.mpEnd;
    if (mpCurrent != mpEnd && !mFilter.IsValid(*mpCurrent))
        Advance();
}

// ----------------------------------------------------------------------------
// pool / hash table node storage
// ----------------------------------------------------------------------------
struct PoolNode {
    void* mpObject;       // +0
    PoolNode* mpNext;     // +4
};

// vtable-slot stubs: `G(n-1) virtual R m();` places m at byte offset 4*n.
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();

struct V46 { G46 virtual uint32_t AddRef(); };   // AddRef at +0xbc
struct V47 { G47 virtual void Release(); };      // Release at +0xc0

struct Obj {
    virtual uint32_t AddRef();      // vtable +0xbc
    virtual void Release();         // vtable +0xc0
};
struct Pool {
    uint32_t pad00[(0x1c - 0x00) / 4];
    PoolNode* mpFreeList;         // +0x1c
    uint32_t pad20[(0x24 - 0x20) / 4];
    PoolNode* mpBegin;            // +0x24
    PoolNode* mpEnd;              // +0x28
    uint32_t mNodeSize;           // +0x2c
    PoolNode* mpSentinel;         // +0x30

    PoolNode* NewNode(Obj** ppObj);
    void FreeBuckets(PoolNode** buckets, uint32_t count);
};

struct HNode {
    uint32_t mKey;         // +0
    Obj* mpValue;          // +4
    HNode* mpNext;         // +8
};

// The copied value's refcount entry point is plain vtable slot 0.
struct RefObj {
    virtual void AddRef();
};

struct HashTable {
    uint32_t m0;                 // +0x00
    HNode** mpBucketArray;       // +0x04
    uint32_t mnBucketCount;      // +0x08
    uint32_t mnElementCount;     // +0x0c
    uint32_t m10;                // +0x10
    uint32_t m14;                // +0x14
    uint32_t m18;                // +0x18
    Pool mPool;                  // +0x1c

    __thiscall HashTable(const HashTable& other);
};

extern HNode* g_emptyBucketArray;   // 0x0154df28

// @ 0x00b41c80
HashTable::HashTable(const HashTable& other)
{
    m0 = other.m0;
    mnBucketCount = other.mnBucketCount;
    mnElementCount = other.mnElementCount;
    m10 = other.m10;
    m14 = other.m14;
    m18 = other.m18;
    if (mnElementCount != 0) {
        unsigned size = mnBucketCount * 4;
        HNode* buckets =
            (HNode*)EAAllocate(
                size + 4, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        memset(buckets, 0, size);
        ((uint32_t*)buckets)[size / 4] = 0xffffffff;
        mpBucketArray = (HNode**)buckets;
        for (uint32_t i = 0; i < other.mnBucketCount; i++) {
            HNode** link = &mpBucketArray[i];
            for (HNode* src = other.mpBucketArray[i]; src; src = src->mpNext) {
                HNode* node =
                    (HNode*)EAAllocate(
                        0xc, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                        0xd1);
                if (node) {
                    node->mKey = src->mKey;
                    node->mpValue = src->mpValue;
                    if (node->mpValue)
                        ((RefObj*)node->mpValue)->AddRef();
                    node->mpNext = 0;
                }
                *link = node;
                link = &node->mpNext;
            }
        }
    } else {
        mnBucketCount = 1;
        mpBucketArray = (HNode**)&g_emptyBucketArray;
        mnElementCount = 0;
        m18 = 0;
    }
}

// ----------------------------------------------------------------------------
// pool
// ----------------------------------------------------------------------------
// @ 0x00b41dc0
PoolNode* Pool::NewNode(Obj** ppObj)
{
    PoolNode* node = mpFreeList;
    if (node)
        mpFreeList = (PoolNode*)node->mpObject;
    else
        node = (PoolNode*)EAAllocate(
            mNodeSize, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    if (node) {
        Obj* pObj = *ppObj;
        node->mpObject = pObj;
        if (pObj)
            ((V46*)pObj)->AddRef();
    }
    node->mpNext = 0;
    return node;
}

// @ 0x00b41e20
void Pool::FreeBuckets(PoolNode** buckets, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++) {
        PoolNode* node = buckets[i];
        while (node) {
            PoolNode* next = node->mpNext;
            if (node->mpObject)
                ((V47*)node->mpObject)->Release();
            if (node != mpSentinel) {
                if (node >= mpBegin && node < mpEnd) {
                    node->mpObject = mpFreeList;
                    mpFreeList = node;
                } else {
                    operator_delete(node);
                }
            }
            node = next;
        }
        buckets[i] = 0;
    }
}

// ----------------------------------------------------------------------------
// lower_bound over 8-byte pairs
// ----------------------------------------------------------------------------
struct KeyPair {
    int mKey;       // +0
    int mValue;     // +4
};

// @ 0x00b41ea0
KeyPair* LowerBoundPair(KeyPair* begin, KeyPair* end, const int* pKey)
{
    int count = (int)(end - begin);
    if (count > 0) {
        do {
            int half = count >> 1;
            if (begin[half].mKey < *pKey) {
                begin += half + 1;
                count += -1 - half;
            } else {
                count = half;
            }
        } while (count > 0);
    }
    return begin;
}

// ----------------------------------------------------------------------------
// creature message/value plumbing
// ----------------------------------------------------------------------------
struct MsgTableNode {
    uint32_t mKey;          // +0x0
    uint32_t mValue;        // +0x4
    MsgTableNode* mpNext;   // +0x8
};

// eastl::hashtable<unsigned, eastl::pair<const unsigned, int>>
struct MsgTable {
    uint32_t mRehashPolicy;      // +0x0
    MsgTableNode** mpBuckets;    // +0x4
    uint32_t mnBucketCount;      // +0x8

    MsgTableNode* Find(const uint32_t* pKey) const;   // 0x00645ed0
    MsgTableNode* End() const { return mpBuckets[mnBucketCount]; }
};

// object that carries a table of per-message values (params: default + table)
struct cMessageContext {
    uint32_t mDefaultValue;      // +0x00
    MsgTable mTable;             // +0x04
};

// object returned by the property lookup (creature / game data object)
struct cSPProperty {
    uint32_t pad00[(0x34 - 0x00) / 4];
    uint32_t mName34;            // +0x34: name blob, hashed by 0x00f21a90
    uint32_t mFlags38;           // +0x38
    uint32_t pad3c[(0x10c - 0x3c) / 4];
    void* mpObject10c;           // +0x10c
    uint32_t pad110[(0x228 - 0x110) / 4];
    uint32_t m228;               // +0x228
    uint32_t pad22c[(0xb1c - 0x22c) / 4];
    int mValueB1c;               // +0xb1c
    uint32_t padB20[(0xb58 - 0xb20) / 4];
    uint32_t mFlagsB58;          // +0xb58

    virtual bool GetFlag58();    // vtable +0x58
};

class cCreatureBase {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual uint32_t GetMessageId();                    // +0x20
    virtual void v024(); virtual void v028(); virtual void v02c(); virtual void v030();
    virtual void v034(); virtual void v038(); virtual void v03c(); virtual void v040();
    virtual void v044();
    virtual bool GetFlag48();                           // +0x48
    virtual void v04c(); virtual void v050(); virtual void v054(); virtual void v058();
    virtual void v05c(); virtual void v060(); virtual void v064(); virtual void v068();
    virtual void v06c(); virtual void v070();
    virtual float GetScale();                           // +0x74
    virtual void v078(); virtual void v07c(); virtual void v080(); virtual void v084();
    virtual void v088(); virtual void v08c(); virtual void v090(); virtual void v094();
    virtual void v098(); virtual void v09c(); virtual void v0a0(); virtual void v0a4();
    virtual void v0a8(); virtual void v0ac(); virtual void v0b0(); virtual void v0b4();
    virtual void* GetSubObject(uint32_t id);            // +0xb8

    uint32_t pad00[(0x50 - 0x04) / 4];
    uint32_t mFlags50;           // +0x50
    uint32_t pad54[(0x110 - 0x54) / 4];
    int mType110;                // +0x110
    uint32_t mValue114;          // +0x114
    uint32_t pad118[(0x130 - 0x118) / 4];
    uint32_t mName130;           // +0x130
    uint32_t mPtr134;            // +0x134
};

// object that owns a message table (property source)
struct cPropertySource {
    uint32_t pad00[(0x04 - 0x00) / 4];
    MsgTable mTable;             // +0x04
};

class cPropertyRegistry {
public:
    cPropertySource* GetMessageSource();    // 0x00b532f0
};

extern cPropertyRegistry* g_pPropertyRegistry;   // 0x0167eae8

cSPProperty* __cdecl FindProperty(void* self, uint32_t id);     // 0x00ac80d0
uint32_t __cdecl HashName(const void* pName);                   // 0x00f21a90
int __cdecl GetCurrentGameMode();                               // 0x00b5b800
void* __cdecl CastObject(void* p);                              // 0x00c90460
cSPProperty* __cdecl GetPropertySet(uint32_t id);               // 0x00b3d310

// @ 0x00b41ee0
uint32_t GetMessageValue(cCreatureBase* self, cMessageContext* pContext)
{
    if (!pContext)
        return 0;

    uint32_t defaultValue = pContext->mDefaultValue;
    const MsgTable* pTable = &pContext->mTable;
    uint32_t key = 0;

    switch (self->GetMessageId()) {
    case 0x2a8fb3f:
        key = self->mValue114;
        break;

    case 0x18c8f0c:
        if (!FindProperty(self, 0x18c8f0c)->GetFlag58())
            return 0;
        break;

    case 0x18c6de8:
        switch (FindProperty(self, 0x18c6de8)->mValueB1c) {
        case 0:
            key = 0x28346586;
            break;
        case 1:
            key = 0x9e3c3dfa;
            break;
        case 2:
            key = 0x3e9c273b;
            break;
        }
        break;

    case 0x18c88e4: {
        cSPProperty* pProp = FindProperty(self, 0x18c88e4);
        if (pProp->mFlags38)
            key = HashName(&pProp->mName34);
        else if (pProp->m228 == 0x5d97f762)
            key = 0x5d97f762;
        else
            return 0;
        break;
    }

    case 0x18eb45e:
        if ((FindProperty(self, 0x18eb45e)->mFlagsB58 >> 9) & 1)
            if (GetCurrentGameMode() == 0x1654c05)
                key = 0xd8c67022;
        break;

    case 0x3a2511e:
        if (self->mPtr134) {
            cSPProperty* pSet = GetPropertySet(0x18c88e4);
            cPropertyRegistry* pReg = (cPropertyRegistry*)pSet->mpObject10c;
            pTable = &pReg->GetMessageSource()->mTable;
            key = HashName(&self->mName130);
        } else {
            key = self->mValue114;
            if (key == 0) {
                switch (self->mType110) {
                case 1:
                    key = 0xe1c134a8;
                    break;
                case 2:
                    key = 0x67fe5dc7;
                    break;
                case 3:
                    key = 0x6b7a9a63;
                    break;
                case 6:
                    key = 0x713c33f8;
                    break;
                case 7:
                    key = 0x2081b4f5;
                    break;
                }
            }
        }
        break;

    case 0x629bafe:
        if (!CastObject(FindProperty(self, 0x629bafe)->mpObject10c))
            return 0;
        break;

    case 0x52aa6122: {
        uint32_t* pSet = (uint32_t*)GetPropertySet(0);
        if (pSet[0x20 / 4])
            return 0;
        break;
    }
    }

    MsgTableNode* pNode = pTable->Find(&key);
    if (pNode != pTable->End())
        return pNode->mValue;
    return defaultValue;
}

// ----------------------------------------------------------------------------
// creature ranged attack update
// ----------------------------------------------------------------------------
// Object returned by 0x00b3d310.
struct GameData {
    uint32_t pad00[(0x20 - 0x00) / 4];
    uint32_t m20;                          // +0x20
};

// One of the per-instance objects returned by the virtual at vtable offset 0xb8.
struct AttackObject {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual bool Use(uint32_t id, uint32_t a, uint32_t* ppArg);   // +0x0c
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
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
    virtual void Release();                // +0x60

    uint32_t pad04[(0xf90 - 0x04) / 4];
    uint8_t mFlagF90;                      // +0xf90
};

struct XformMsgHeader {
    uint16_t mFlags;                       // +0x00
    uint16_t mModCount;                    // +0x02
};

struct XformMsg {
    XformMsgHeader mHeader;                // +0x00
    Vector3 mTranslation;                  // +0x04
    float mScale;                          // +0x10
    Matrix3 mRotation;                     // +0x14
};

class cAttackCreature {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044();
    virtual bool HasAttack();              // +0x48
    virtual void v04c(); virtual void v050(); virtual void v054(); virtual void v058();
    virtual void v05c(); virtual void v060(); virtual void v064(); virtual void v068();
    virtual void v06c(); virtual void v070();
    virtual float GetScale();              // +0x74
    virtual void v078(); virtual void v07c(); virtual void v080(); virtual void v084();
    virtual void v088(); virtual void v08c(); virtual void v090(); virtual void v094();
    virtual void v098(); virtual void v09c(); virtual void v0a0(); virtual void v0a4();
    virtual void v0a8(); virtual void v0ac(); virtual void v0b0(); virtual void v0b4();
    virtual AttackObject* GetAttack();      // +0xb8

    uint32_t pad00[(0x50 - 0x04) / 4];
    uint32_t mFlags50;                     // +0x50
};

// A target that receives the attack effect message.
class cEffectHost {
public:
    virtual void v00(); virtual void v04();
    virtual void ReceiveMessage(void* msg);   // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void Apply(void* msg);            // +0x18
};

void* __cdecl GetActivePlanet();                        // 0x01021260
float __cdecl GetPlanetLavaSomething();                 // 0x00c70a20
void* __cdecl GetTerraformTuning();                     // 0x01049a10
float __cdecl GetLavaThreshold(void* pTuning);          // 0x01049bf0
float __cdecl GetTerraformHeight(float a, uint32_t b);  // 0x00b7e430
AttackObject* __cdecl GetEffectsManager();              // 0x0067ddd0
uint32_t* __cdecl AsPPTypeParam(void* pOut);            // 0x00a16f40
void* __cdecl XformMsgCtor(void* self);                 // 0x00434040
void __cdecl SetTarget(void* self, void* pTarget);      // 0x00571d40
void __cdecl Matrix3FromQuaternion(Matrix3* out, const void* pQuat);   // 0x0059c190

extern float g_lavaScale;   // 0x0167eb78
extern float h;             // 0x01471064 (0.5f)

// @ 0x00b421b0
void UpdateRangedAttacks(cAttackCreature* self, bool bActive, const void* pQuat,
                         cEffectHost* pTarget)
{
    uint32_t flags = self->mFlags50;
    bool bWasActive = (flags & 0x1000) == 0x1000;
    if (!bActive) {
        self->mFlags50 = flags & ~0x1000u;
        return;
    }
    self->mFlags50 = flags | 0x1000;
    if (bWasActive)
        return;

    GetActivePlanet();
    float height = GetPlanetLavaSomething();
    float threshold = GetLavaThreshold(GetTerraformTuning());
    if (height > threshold)
        return;

    AttackObject* pAttack = self->GetAttack();
    if (!self->HasAttack() || height == 0.0f || !pQuat ||
        (pAttack && !pAttack->mFlagF90))
        goto done;

    if (GetTerraformHeight(height, 1) <= g_lavaScale)
        goto done;

    {
        AttackObject* pManager = GetEffectsManager();
        uint32_t* pArg = 0;
        AsPPTypeParam(&pArg);
        if (!pManager->Use(0x7484a8e4, 0, pArg))
            goto done;

        XformMsg msg;
        XformMsgCtor(&msg);
        SetTarget(&msg, 0);   // unused placeholder for the shared base ctor
        Matrix3FromQuaternion(&msg.mRotation, pQuat);
        msg.mTranslation.x = 0.0f;   // placeholders replaced below
        msg.mHeader.mFlags |= 2;
        msg.mHeader.mModCount++;
        msg.mScale = self->GetScale();
        msg.mHeader.mModCount++;
        pTarget->ReceiveMessage(&msg);
        pTarget->Apply(0);
    }

done:
    if (pAttack)
        pAttack->Release();
}
