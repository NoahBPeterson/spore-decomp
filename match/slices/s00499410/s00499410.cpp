// Slice s00499410 (batch w1g0, slice 97), 0x00499410..0x0049a0be.
// /Od editor-region code (flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-).
// 00499410 is the editor "pick block" routine (ray vs. block / skin / ground plane),
// 00499b40 computes barycentric weights of a point in a triangle, 00499f10 builds a
// triangle-frame basis, 0049a0c0 picks a normalized direction for a block.

#include "types.h"

// Vector3 with an out-of-line 3-arg ctor (0x00436CA0); copies are implicit.
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az);          // 0x00436CA0
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct V3Agg { float x, y, z; };
// Copy ctor assigning in its body (x87 fld/fstp), expanded inline.
struct Vec3I {
    float x, y, z;
    Vec3I() {}
    Vec3I(const Vec3I& o) { x = o.x; y = o.y; z = o.z; }
};
// Same layout with an out-of-line copy ctor (0x004098A0).
struct Vec3C {
    float x, y, z;
    Vec3C() {}
    Vec3C(const Vec3C& o);                          // 0x004098A0
};

struct Plane {
    float a, b, c, d;
    Plane() {}
    Plane(float ax, float bx, float cx, float dx);   // 0x0044E410
};

extern Vector3 g_15d64d8;
extern Vector3 g_15d6324;
extern Vec3C   g_15d64d8_v3c;                    // 0x015d64d8 (g_15d64d8 seen as Vec3C)

Vector3* VectorSub(Vector3* out, const Vector3* a, const Vector3* b);            // 0x41db10
Vector3* VectorAdd(Vector3* out, const Vector3* a, const Vector3* b);            // 0x41dc10
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v);          // 0x41de40
Vector3* Vector3_Negate(Vector3* out, const Vector3* v);                         // 0x422020
bool     Vector3Equal(const Vector3* a, const Vector3* b);                       // 0x4232c0
Vector3* Vector3_Normalize(Vector3* out, const Vector3* v);                      // 0x436ce0
Vector3* Cross(Vector3* out, const Vector3* a, const Vector3* b);                // 0x44e460
float    VectorLength(const Vector3* v);                                         // 0x40ae50
float    Dot3(const float* a, const float* b);                                   // 0x455cc0
void PlaneFromPointNormal(Plane* out, const Vector3* p, const Vector3* n);       // 0x44e510
bool IntersectRayPlane(const Vector3* o, const Vector3* d, const Plane* p, float* t); // 0x44e640

// @ 0x0049a030
bool FUN_0049a030(Vector3 origin, Vector3 dir, Vector3* out) {
    Plane p;
    PlaneFromPointNormal((Plane*)&p, &g_15d64d8, &g_15d6324);
    float t;
    if (!IntersectRayPlane(&origin, &dir, &p, &t))
        return false;
    Vector3 sv;
    Vector3_Scale(&sv, &t, &dir);
    Vector3 r;
    VectorAdd(&r, &origin, &sv);
    *out = r;
    return true;
}

// ---------------------------------------------------------------------------
// Reference-counted objects: the counted interface sits at +4 (second base).
// ---------------------------------------------------------------------------
struct IBase0 { virtual void b0(); };
struct IRefCount {
    virtual void r0();
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
};
struct RefObj : IBase0, IRefCount { };

// AutoRefCount<T>: the out-of-line destructors of the two instantiations used here are
// written as two classes so each carries its original address.
struct RefObj;
struct SkinMgr;
struct AutoRefCountRefObj {
    RefObj* mpObject;
    AutoRefCountRefObj(RefObj* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountRefObj();                                 // 0x004A9AE0
};
struct AutoRefCountSkinMgr {
    SkinMgr* mpObject;
    ~AutoRefCountSkinMgr();                                // 0x004A9B10
    SkinMgr* operator->() const { return mpObject; }
    operator SkinMgr*() const { return mpObject; }
};

struct Block;
struct Entity;
struct SkinMgr {
    bool   PickSkin(int pickId, Vector3 org, Vector3 dir, Vector3* a, Vector3* b, float* t, int c);  // 0x004C4A30
    // same function, origin given as a Vec3C (copied with the out-of-line copy ctor)
    bool   PickSkin(int pickId, Vec3C org, Vector3 dir, Vector3* a, Vector3* b, float* t, int c);    // 0x004C4A30
    Block* GetBlockAtSkinPoint(Vec3C pt, int id);  // 0x004C4D30
};
struct Entity {
    char     pad0[0x28];
    RefObj*  mp28;
    char     pad2c[0xdc8 - 0x2c];
    unsigned mFlagBits[2];
    RefObj*  GetRefObj() { return mp28; }
    int      GetSkinIdentifierForPicking();                // 0x0043A870
    bool     HasAnyBlockFlag();                            // 0x00435D40
    unsigned GetWord(unsigned i) const { return mFlagBits[i]; }
    bool     TestFlag(unsigned pos) const {
        if (pos < 60)
            return (GetWord(pos >> 5) & (1u << (pos % 32))) != 0;
        return false;
    }
};
Block* PickBlockForPinning(Entity* e, unsigned arg, Vector3 org, Vector3 dir,
                           Vector3* outPt, Vector3* outN, bool* flag, int z);   // 0x004A4D60
void   FUN_0049c630(Vector3* out, Vec3C pt, SkinMgr* skin);                   // 0x0049C630 cdecl

// @ 0x00499410
Block* FUN_00499410(Entity* e, Vector3 org, Vector3 dir, AutoRefCountSkinMgr skin,
                    Vector3* outPt, Vector3* outN, unsigned arg30)
{
    AutoRefCountRefObj u(e->GetRefObj());
    Block* p30 = 0;
    int n37 = e->GetSkinIdentifierForPicking();
    Block* obj = 0;
    bool v28 = false;
    Vector3 t24;
    Vector3 v33;
    if (!e->TestFlag(11))
        obj = PickBlockForPinning(e, arg30, org, dir, &t24, &v33, &v28, 0);
    p30 = obj;
    *outPt = t24;
    *outN = v33;
    if (skin) {
        bool v14 = false;
        Vector3 t25, m;
        float n1;
        bool t14 = skin->PickSkin(n37, org, dir, &t25, &m, &n1, 1);
        if (n37 == 1) {
            Vector3 pos2, nrm2;
            float t2;
            if (skin->PickSkin(2, org, dir, &pos2, &nrm2, &t2, 1)) {
                if (!t14 || n1 > t2) {
                    t25 = pos2;
                    m = nrm2;
                    v14 = true;
                }
                t14 = true;
            }
        }
        if (!t14) {
            float nrm[3] = { 1.0f, 0.0f, 0.0f };
            float pt[3] = { 0.0f, 0.0f, 0.0f };
            Plane pl(nrm[0], nrm[1], nrm[2], -Dot3(pt, nrm));
            Vec3C hit;
            hit = g_15d64d8_v3c;
            float t;
            if (IntersectRayPlane(&org, &dir, &pl, &t)) {
                Vector3 sv, sum;
                Vector3_Scale(&sv, &t, &dir);
                Vector3 r = *VectorAdd(&sum, &org, &sv);
                hit.x = r.x; hit.y = r.y; hit.z = r.z;
            }
            Vector3 onPlane;
            FUN_0049c630(&onPlane, hit, skin.mpObject);
            Vector3 tmp;
            Vector3 d = *VectorSub(&tmp, &onPlane, (Vector3*)&hit);
            Vector3 nd;
            Vector3_Normalize(&nd, &d);
            if (skin->PickSkin(n37, hit, nd, &t25, &m, &n1, 1)) {
                if (n1 < 1.0f && e->HasAnyBlockFlag())
                    t14 = true;
            }
        }
        if (t14) {
            bool take = true;
            if (obj) {
                Vector3 tmp;
                Vector3 diff = *VectorSub(&tmp, &org, &t24);
                if (!(VectorLength(&diff) > n1))
                    take = false;
            }
            if (take) {
                *outPt = t25;
                *outN = m;
                if (v14)
                    p30 = skin->GetBlockAtSkinPoint(*(Vec3C*)&t24, 2);
                else
                    p30 = skin->GetBlockAtSkinPoint(*(Vec3C*)&t24, n37);
            }
        }
    }
    return p30;
}

// @ 0x00499b40
// Barycentric weights of point p in triangle (a, b, c).
Vector3 FUN_00499b40(Vector3 a, Vector3 b, Vector3 c, Vector3 p)
{
    Vector3 n5, t15, t24;
    Vector3 u = *VectorSub(&n5, &b, &c);
    float w = VectorLength(&u);
    Vector3 p39 = *VectorSub(&t15, &a, &c);
    float p30 = VectorLength(&p39);
    Vector3 key = *VectorSub(&t24, &b, &a);
    float bucket = VectorLength(&key);
    if (w > 0.0f && p30 > 0.0f && bucket > 0.0f) {
        Vector3 p11, size, n37;
        Vector3 chunk = *VectorSub(&p11, &c, &p);
        Vector3 t6 = *VectorSub(&size, &b, &c);
        float v23 = VectorLength(Cross(&n37, &t6, &chunk)) / w;
        Vector3 n18, p10, v28, t12, t26, obj;
        Vec3C v9(*(Vec3C*)VectorSub(&n18, &c, &p));
        Vec3C ret(*(Vec3C*)VectorSub(&p10, &a, &c));
        float t18 = VectorLength(Cross(&v28, (Vector3*)&ret, (Vector3*)&v9)) / p30;
        Vec3C k(*(Vec3C*)VectorSub(&t12, &a, &p));
        Vec3C hi(*(Vec3C*)VectorSub(&t26, &b, &a));
        float last = VectorLength(Cross(&obj, (Vector3*)&hi, (Vector3*)&k)) / bucket;
        float count = p30 * t18 * 0.5f;
        float i = w * v23 * 0.5f;
        float n28 = bucket * last * 0.5f;
        float v33 = count + i + n28;
        if (v33 > 0.0f)
            return Vector3(i / v33, count / v33, n28 / v33);
    }
    return Vector3(0.33f, 0.33f, 0.33f);
}

Vector3* FUN_004a89e0(Vector3* out, const Vector3* a, const Vector3* b);          // 0x004A89E0 cdecl

template <int N> inline void ScratchSlots() { unsigned s[N]; }

// @ 0x00499f10
Vector3* FUN_00499f10(Vector3* ret, Vector3 a, Vector3 b, Vector3 c)
{
    Vector3 t13, n29, v11, alloc, cur, cap;
    Vector3 n38 = *VectorSub(&t13, &b, &a);
    Vector3 offset = *VectorSub(&v11, &c, &a);
    Vector3_Normalize(&cur, Cross(&n29, &offset, &n38));
    ScratchSlots<9>();
    Vector3 n6 = *VectorSub(&alloc, &b, &a);
    Vector3_Normalize(&cap, &n6);
    FUN_004a89e0(ret, &cur, &cap);
    ScratchSlots<6>();
    return ret;
}

struct DirSrc;
struct DirOwner {
    char pad0[0x28];
    DirSrc* mp28;
    char pad2c[0x48 - 0x2c];
    Vec3I mDir;                                          // +0x48
    DirSrc* GetSrc() { return mp28; }
    const Vec3I& GetDir() { return mDir; }
};
struct DirSrc {
    Vector3 GetDir(Vec3I a, DirOwner* o, int z0, int z1, Vector3 b);  // 0x004ABBC0 (hidden return slot first)
};
// @ 0x0049a0c0
Vector3* FUN_0049a0c0(Vector3* ret, DirOwner* o)
{
    DirSrc* m;
    if (o && (m = o->mp28) != 0) {
        Vector3 d = o->GetSrc()->GetDir(o->GetDir(), o, 0, 0, g_15d6324);
        V3Agg neg1 = { -1.0f, -1.0f, -1.0f };
        if (Vector3Equal(&d, (Vector3*)&neg1)) {
            Vector3 t;
            Vector3 n = *Vector3_Negate(&t, (Vector3*)&o->mDir);
            Vector3_Normalize(ret, &n);
            return ret;
        }
        Vector3 t;
        Vector3 s = *VectorSub(&t, &d, (Vector3*)&o->mDir);
        Vector3_Normalize(ret, &s);
        return ret;
    }
    ret->x = g_15d64d8.x;
    ret->y = g_15d64d8.y;
    ret->z = g_15d64d8.z;
    return ret;
}
