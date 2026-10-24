// slice s00d557f0 — SetStarPattern (PDB name), space-turret fire pattern.
// Fills `out` with `count` points on a five-pointed star around `pos`: an inner ring and
// an outer ring of five points (rotating `dir` about the normalized `pos` axis), then
// fills the edges with evenly spaced interpolation points.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(cos, sin, sqrt)

inline void* operator new(unsigned int, void* p) throw() { return p; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    T* erase(T* first, T* last);
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    void clear() { erase(mpBegin, mpEnd); }
};

typedef SpVector<Vector3> Vec3Vector;
template <> Vector3* Vec3Vector::erase(Vector3* first, Vector3* last);          // 0x50f740
template <> void Vec3Vector::DoInsertValue(Vector3* pos, const Vector3& v);     // 0x4b5ad0

extern float g_169ebf0;     // base angular step (radians)

// Adds five points of one star ring: the direction `d` rotated about the unit axis of `p`
// by successive angles, scaled by `scale` and offset by `p`.
static __forceinline void AddStarRing(Vec3Vector& out, const Vector3& p, const Vector3& d,
                               float scale, float angle, const float& step)
{
    for (int i = 5; i != 0; --i) {
        float inv = 1.0f / (float)sqrt(p.x * p.x + (p.z * p.z + p.y * p.y));
        float s = (float)sin(angle * 0.5f);
        float c = (float)cos(angle * 0.5f);
        float qy = (p.y * inv) * s;
        float qz = (p.z * inv) * s;
        float qx = s * (inv * p.x);
        float rx = (((c * qy + qz * qx) * d.z + (qy * qx - c * qz) * d.y) * 2.0f +
                     (1.0f - (qz * qz + qy * qy) * 2.0f) * d.x) * scale + p.x;
        float ry = (((qz * qy - c * qx) * d.z + (c * qz + qy * qx) * d.x) * 2.0f +
                     (1.0f - (qz * qz + qx * qx) * 2.0f) * d.y) * scale + p.y;
        float rz = (((c * qx + qz * qy) * d.y + (qz * qx - c * qy) * d.x) * 2.0f +
                     (1.0f - (qx * qx + qy * qy) * 2.0f) * d.z) * scale + p.z;
        Vector3 r(rx, ry, rz);
        out.push_back(r);
        angle = step + angle;
    }
}

// @ 0x00d557f0
void SetStarPattern(int count, Vec3Vector& out, Vector3 p, Vector3 d, float radius)
{
    out.clear();
    static float sStep = g_169ebf0 * 0.2f;

    int n = count;
    if (n >= 5) {
        AddStarRing(out, p, d, radius * 0.5f, 0.0f, sStep);
        n -= 5;
        if (n >= 5) {
            AddStarRing(out, p, d, radius, sStep * 0.5f, sStep);
            n -= 5;
        }
    }

    int m = n / 10;
    if (m != 0) {
        const Vector3* v = out.mpBegin;
        float dx = v[0].x - v[5].x;
        float dy = v[0].y - v[5].y;
        float dz = v[0].z - v[5].z;
        float stepT = (float)sqrt(dx * dx + (dy * dy + dz * dz)) / (float)(m + 1);
        for (int j = 0; j < 5; ++j) {
            const Vector3* base = out.mpBegin;
            Vector3 a = base[j];
            Vector3 b = base[j + 5];
            Vector3 c = base[(j < 4) ? j + 1 : 0];
            if (m > 0) {
                Vector3 d1(b.x - a.x, b.y - a.y, b.z - a.z);
                Vector3 d2(b.x - c.x, b.y - c.y, b.z - c.z);
                float inv1 = 1.0f / (float)sqrt(d1.y * d1.y + (d1.z * d1.z + d1.x * d1.x));
                Vector3 u1(inv1 * d1.x, d1.y * inv1, d1.z * inv1);
                float inv2 = 1.0f / (float)sqrt(d2.y * d2.y + (d2.z * d2.z + d2.x * d2.x));
                Vector3 u2(inv2 * d2.x, d2.y * inv2, d2.z * inv2);
                float t = stepT;
                for (int k = m; k != 0; --k) {
                    Vector3 q1(u1.x * t + a.x, u1.y * t + a.y, u1.z * t + a.z);
                    out.push_back(q1);
                    Vector3 q2(u2.x * t + c.x, u2.y * t + c.y, u2.z * t + c.z);
                    out.push_back(q2);
                    t = t + stepT;
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// Space-turret fire-pattern selection and agent bookkeeping (0x00d56070..0x00d56630)

struct Target {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Release();          // vtable +0x14
};

struct cSpaceTurretStateInfo {
    int32_t  mState;                 // +0x00
    Target*  mpTarget;               // +0x04
    uint64_t mNextMissileTime;       // +0x08
    uint64_t mNextBeamTime;          // +0x10
    uint64_t mBeamCutoffTime;        // +0x18
    int32_t  mBehaviorIndex;         // +0x20
};

// eastl::rbtree node base: Right(+0), Left(+4), Parent(+8), Color(+0xc)
struct RBNodeBase {
    RBNodeBase* mpNodeRight;         // +0x00
    RBNodeBase* mpNodeLeft;          // +0x04
    RBNodeBase* mpNodeParent;        // +0x08
    uint32_t    mColor;              // +0x0c
};

struct StateNode : RBNodeBase {
    int32_t mKey;                    // +0x10
    int32_t mPad14;                  // +0x14
    cSpaceTurretStateInfo mValue;    // +0x18
};

struct StatePair {
    int32_t mKey;                    // +0x00
    int32_t mPad04;                  // +0x04
    cSpaceTurretStateInfo mValue;    // +0x08
    StatePair* Construct(const int* key, const cSpaceTurretStateInfo* src);   // 0x00d548e0
};

// One-byte tag matching eastl's empty integral_constant argument slot.
struct InsertTag { unsigned char mValue; InsertTag() : mValue(0) {} };

struct StateMap {
    uint32_t   mUnused;              // +0x00
    RBNodeBase mAnchor;              // +0x04
    uint32_t   mSize;                // +0x14

    void Insert(StateNode** out, StateNode* position, const StatePair* value,
                InsertTag unique);   // 0x00d54ed0
    cSpaceTurretStateInfo& GetOrInsert(const int& key);
};

struct cLocomotiveObject {
    Vector3* GetVelocity();          // 0x00d20610
};

// cBehaviorSpaceTurret derives from cInteraction (0x74 bytes); only the base's
// AddAgent entry point and the derived layout are needed here.
struct cInteractionAgent;
struct cInteraction {
    char mBase[0x74];
    bool AddAgent(cInteractionAgent* pAgent);   // 0x00abf640
};

extern Vector3 g_169ebe4;           // 0x0169ebe4 reference direction constant

// The fire-pattern code asks the owning object for a direction through vtable slot 0x2c.
static __forceinline Vector3* GetObjectDirection(void* obj)
{
    void** vtbl = *(void***)obj;
    return ((Vector3* (__thiscall*)(void*))vtbl[0x2c / 4])(obj);
}

struct cPlanetModel {
    char pad[0x100];
    Vector3* DirectionToSurfacePosition(Vector3* out, const Vector3* dir);        // 0x00b815a0
    Vector3* MakeRandomWorldPosition(Vector3* out, const Vector3* dir, float a, float b); // 0x00b81780
};
cPlanetModel* PlanetModel();        // 0x00b3d350

struct Matrix3 { float m[9]; };
void __cdecl MatrixFromTwoVectors(Matrix3* out, const Vector3* a, const Vector3* b);  // 0x0069b1c0

struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t range);   // 0x00a68fb0
};

void FUN_00d55060(int count, Vec3Vector& out, Vector3 p, Vector3 d1, Vector3 d2, float r);
void FUN_00d552c0(int count, Vec3Vector& out, Vector3 p, Vector3 d1, Vector3 d2, float r);
void FUN_00d554f0(int count, Vec3Vector& out, Vector3 p, Vector3 d1, Vector3 d2, float r);

struct cBehaviorSpaceTurret : cInteraction {
    StateMap mMap;                   // +0x74
    char mPad8c[0xb8 - (0x74 + sizeof(StateMap))];
    int32_t mF0b8;                   // +0xb8
    char mPadBc[0x74c - 0xb8 - 4];
    char mF74c;                      // +0x74c

    bool AddAgent(cInteractionAgent* pAgent);
};

// @ 0x00d56070
void UpdateFirePattern(Vec3Vector& out, int count, cBehaviorSpaceTurret* turret)
{
    out.clear();

    Vector3 dir;
    if (turret->mF74c == 0) {
        cLocomotiveObject* loco = (cLocomotiveObject*)((char*)turret + 0x34);
        Vector3* vel = loco->GetVelocity();
        float sq = vel->x * vel->x + vel->y * vel->y + vel->z * vel->z;
        if ((float)sqrt(sq) > 0.0f) {
            Vector3 pos;
            Vector3* dirRaw = GetObjectDirection(loco);
            Vector3* surf = PlanetModel()->DirectionToSurfacePosition(&pos, dirRaw);
            Vector3 v = *surf;
            Vector3 rnd = *PlanetModel()->MakeRandomWorldPosition(&pos, &v, 0.0f, 20.0f);
            Vector3* pdir = GetObjectDirection(loco);
            float sqSpeed = pdir->x * pdir->x + pdir->y * pdir->y + pdir->z * pdir->z;
            float speed = (float)sqrt(sqSpeed);
            float inv = 1.0f / (float)sqrt(rnd.x * rnd.x + rnd.z * rnd.z + rnd.y * rnd.y);
            dir.x = (inv * rnd.x) * speed;
            dir.y = (rnd.y * inv) * speed;
            dir.z = (rnd.z * inv) * speed;
        } else {
            dir = *GetObjectDirection(loco);
        }
    } else {
        dir = *GetObjectDirection((cLocomotiveObject*)((char*)turret + 0x34));
    }

    float inv = 1.0f / (float)sqrt(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y);
    Vector3 d;
    d.x = inv * dir.x;
    d.y = dir.y * inv;
    d.z = dir.z * inv;

    Matrix3 m;
    MatrixFromTwoVectors(&m, &g_169ebe4, &d);
    Vector3 row0(m.m[0], m.m[1], m.m[2]);
    Vector3 row1(m.m[3], m.m[4], m.m[5]);
    Vector3 row2(m.m[6], m.m[7], m.m[8]);

    if (count == 0)
        return;

    RandomLinearCongruential* rng = (RandomLinearCongruential*)0x1601760;
    int half = count / 2;
    int n = rng->RandomUint32Uniform(half) + half;
    int kind = rng->RandomUint32Uniform(4);
    switch (kind) {
    case 0: FUN_00d552c0(n, out, dir, row1, row0, 40.0f); break;
    case 1: FUN_00d554f0(n, out, dir, row1, row0, 40.0f); break;
    case 2: SetStarPattern(n, out, dir, row1, 40.0f); break;
    default: FUN_00d55060(n, out, dir, row2, row1, 40.0f); break;
    }
}

// @ 0x00d56510
cSpaceTurretStateInfo& StateMap::GetOrInsert(const int& key)
{
    RBNodeBase* anchor = &mAnchor;
    RBNodeBase* pos = anchor;
    RBNodeBase* cur = mAnchor.mpNodeParent;
    while (cur) {
        if ((uint32_t)((StateNode*)cur)->mKey < (uint32_t)key) {
            cur = cur->mpNodeRight;
        } else {
            pos = cur;
            cur = cur->mpNodeLeft;
        }
    }

    if (pos == anchor || (uint32_t)key < (uint32_t)((StateNode*)pos)->mKey) {
        cSpaceTurretStateInfo src;
        src.mpTarget = 0;
        src.mNextMissileTime = 0;
        src.mNextBeamTime = 0;
        src.mBeamCutoffTime = 0;
        src.mBehaviorIndex = 0;

        StatePair pair;
        pair.Construct(&key, &src);
        StateNode* result = 0;
        Insert(&result, (StateNode*)pos, &pair, InsertTag());
        if (pair.mValue.mpTarget)
            pair.mValue.mpTarget->Release();
        pos = result;
    }
    return ((StateNode*)pos)->mValue;
}

// @ 0x00d565c0
bool cBehaviorSpaceTurret::AddAgent(cInteractionAgent* pAgent)
{
    if (pAgent != 0) {
        mF0b8 = (mF0b8 == 0);
        cSpaceTurretStateInfo* info = &mMap.GetOrInsert(*(const int*)&pAgent);
        info->mState = 0;
        Target* t = info->mpTarget;
        if (t) {
            info->mpTarget = 0;
            t->Release();
        }
        info->mNextMissileTime = 0;
        info->mBehaviorIndex = mF0b8;
    }
    return cInteraction::AddAgent(pAgent);
}
