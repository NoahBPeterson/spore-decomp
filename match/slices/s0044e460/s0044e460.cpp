// Slice s0044e460 - SP::cSPEditorBlock helpers and small math routines.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

// ---------------------------------------------------------------------------
// Small vector/plane math helpers (free functions).  The vector types expose
// named components and an in-class operator[] (the original inlines it, which
// materialises index*4 for constant subscripts).
// ---------------------------------------------------------------------------
struct Vec3 {
    float x, y, z;
    const float& operator[](int i) const { return ((const float*)this)[i]; }
};
struct Vec4 {
    float x, y, z, w;
    const float& operator[](int i) const { return ((const float*)this)[i]; }
};

// @ 0x0044e460 -- out = a x b (evaluation-order near miss)
Vec3* Cross(Vec3* out, const Vec3* a, const Vec3* b)
{
    Vec3 t;
    t.x = a->y * b->z - a->z * b->y;
    t.y = a->z * b->x - a->x * b->z;
    t.z = a->x * b->y - a->y * b->x;
    *out = t;
    return out;
}

// @ 0x0044e510 -- plane through point `a` with normal `b` (byte-exact)
Vec4* PlaneFromPointNormal(Vec4* out, const Vec3* a, const Vec3* b)
{
    float cap = a->x * b->x + a->y * b->y + a->z * b->z;
    float t40 = (*b)[0];
    float v9 = (*b)[1];
    float t10 = (*b)[2];
    out->x = t40; out->y = v9; out->z = t10; out->w = -cap;
    return out;
}

// @ 0x0044e5d0 -- signed plane evaluation at a point (byte-exact)
float PlaneEval(const Vec4* plane, const Vec3* point)
{
    return (*point)[0] * (*plane)[0] + (*point)[1] * (*plane)[1] + (*point)[2] * (*plane)[2] + (*plane)[3];
}

// @ 0x0044e640 -- ray/plane intersection; false when parallel (byte-exact)
bool IntersectRayPlane(const Vec3* origin, const Vec3* dir, const Vec4* plane, float* tOut)
{
    float denom = (*dir)[0] * (*plane)[0] + (*dir)[1] * (*plane)[1] + (*dir)[2] * (*plane)[2];
    if (denom == 0.0f)
        return false;
    float t = -PlaneEval(plane, origin) / denom;
    if (tOut)
        *tOut = t;
    return t >= 0.0f;
}

// ---------------------------------------------------------------------------
// cSPEditorBlock (retail offsets; only members touched by this slice are named)
// ---------------------------------------------------------------------------
struct cSPEditorBlock;
struct Bounds;

struct cPropertyList;
extern void SP_GetPropertyAsKey(cPropertyList* list, unsigned int id, unsigned int* keyOut); // 0x006a1250
extern bool PropertyGetBool(void* prop);            // 0x0041e920
extern int  FUN_0044a7e60(cSPEditorBlock* self);    // 0x004a7e60

struct cPropertyList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual bool HasProperty(unsigned int id);                       // slot 7  (+0x1c)
    virtual void s8();
    virtual bool GetProperty(unsigned int id, void** out);           // slot 9  (+0x24)
};

struct Bounds {
    unsigned int mData[8];
    Bounds();
    ~Bounds(); // 0x004ae250
    void Set(const void* src);      // 0x0044d960: this = dst, arg = src
};

struct cSPEditorBlock;

// Virtual Release through the object's second vtable slot (vtable+8).
static void ReleaseBlock(void* p)
{
    if (p) {
        void** vtbl = *(void***)p;
        ((void(__thiscall*)(void*))vtbl[2])(p);
    }
}

// Virtual AddRef through the object's first vtable slot (vtable+4).
static void AddRefBlock(void* p)
{
    if (p) {
        void** vtbl = *(void***)p;
        ((void(__thiscall*)(void*))vtbl[1])(p);
    }
}

// AutoRefCount<T>::operator=(T*): addref the new value, store, release the old.
static void AssignRef(cSPEditorBlock** slot, cSPEditorBlock* nv)
{
    if (nv != *slot) {
        cSPEditorBlock* old = *slot;
        AddRefBlock(nv);
        *slot = nv;
        ReleaseBlock(old);
    }
}

struct cSPEditorBlock {
    char                pad_00[0xc];
    cPropertyList*      mpPropList;        // +0x0c
    char                pad_10[0x1c0 - 0x10];
    float               mBaseJointScale;   // +0x1c0
    float               mUniformScale;     // +0x1c4
    char                pad_1c8[0x1cc - 0x1c8];
    int                 mScaleType;        // +0x1cc
    char                pad_1d0[0x234 - 0x1d0];
    void*               mpSnapAxesBase;    // +0x234 (eastl::vector mpBegin)
    char                pad_238[0x33c - 0x238];
    cSPEditorBlock*     mpSocketConnector; // +0x33c (AutoRefCount<cMWModel>)
    cSPEditorBlock**    mpChildBegin;      // +0x340
    cSPEditorBlock**    mpChildEnd;        // +0x344
    cSPEditorBlock**    mpChildCap;        // +0x348
    char                pad_34c[0x3e0 - 0x34c];
    cSPEditorBlock*     mpLinked;          // +0x3e0
    cSPEditorBlock*     mpLinkedAlt;       // +0x3e4
    char                pad_3e8[0xdc8 - 0x3e8];
    unsigned int        mFlags[2];         // +0xdc8 (60-bit flag array)

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }

    bool FUN_00435c80() const;                 // 0x00435c80 (out-of-line GetFlag(0x39))

    void  SetFlag(int id, int value);          // 0x00435a10
    int   FUN_0044f220();                      // 0x0044f220 (receiver = socket connector)
    int   CalculateSymmetrySign();             // 0x0044f240
    int   FindSnapAxis(Vec3 v, float w);       // 0x0044d9e0
    int   FUN_0044c050();                      // 0x0044c050
    int   FUN_0044c450();                      // 0x0044c450
    Bounds* GetBounds(Bounds* out, float x, float y, float z, float w); // 0x0044e720
    int   GetBlockType(unsigned int key);      // 0x0044e830
    void  SetBaseJointScale(float scale);      // 0x0044e980
    void  RefreshLinkedFlag();                 // 0x0044ea80
    void  RecursiveFlagA();                    // 0x0044ede0
    void  RecursiveFlagB();                    // 0x0044eea0
    void  RecursiveFlagC();                    // 0x0044efb0
    void  SetScaleType(int type);              // 0x0044f130
};

// @ 0x0044e720
Bounds* cSPEditorBlock::GetBounds(Bounds* out, float x, float y, float z, float w)
{
    Vec3 v;
    v.x = x; v.y = y; v.z = z;
    int idx = FindSnapAxis(v, w);
    int i = idx;
    if (i >= 0) {
        void* p = (void*)((char*)mpSnapAxesBase + (i << 5));
        out->Set(p);
        return out;
    }
    Bounds b;
    out->Set(&b);
    b.~Bounds();
    return out;
}

// @ 0x0044e830
int cSPEditorBlock::GetBlockType(unsigned int key)
{
    cPropertyList* p = mpPropList;
    if (p->HasProperty(0x3a3b9d21)) {
        unsigned int k[3] = {0, 0, 0};
        SP_GetPropertyAsKey(p, 0x3a3b9d21, k);
        if (key == k[0])
            return 0;
    }
    if (p->HasProperty(0xf48eb09)) {
        unsigned int k[3] = {0, 0, 0};
        SP_GetPropertyAsKey(p, 0xf48eb09, k);
        if (key == k[0])
            return 1;
    }
    if (p->HasProperty(0x18c1dbe0)) {
        unsigned int k[3] = {0, 0, 0};
        SP_GetPropertyAsKey(p, 0x18c1dbe0, k);
        if (key == k[0])
            return -1;
    }
    return -1;
}

// @ 0x0044e980
void cSPEditorBlock::SetBaseJointScale(float scale)
{
    if (*(int*)&scale == -2) {
        *(int*)&mBaseJointScale = CalculateSymmetrySign();
        if (mpSocketConnector != 0) {
            int s2 = mpSocketConnector->FUN_0044f220();
            if (s2 != 0 && s2 != -2 && s2 != *(int*)&mBaseJointScale) {
                *(int*)&mUniformScale = -1;
                *(int*)&mBaseJointScale = s2;
            }
        }
    } else {
        *(int*)&mBaseJointScale = *(int*)&scale;
    }
    if (mpLinked != 0) {
        if (*(int*)&mBaseJointScale == 0)
            *(int*)&mpLinked->mBaseJointScale = 0;
        else
            *(int*)&mpLinked->mBaseJointScale = -*(int*)&mBaseJointScale;
    }
}

// @ 0x0044ea80
void cSPEditorBlock::RefreshLinkedFlag()
{
    bool b = false;
    if (mpSocketConnector != 0) {
        if (mpSocketConnector->GetFlag(0x39) || mpSocketConnector->GetFlag(0x3a))
            b = true;
    }
    if (b) {
        SetFlag(0x3a, 1);
        cSPEditorBlock* saved = mpLinked;
        AssignRef(&mpLinked, (cSPEditorBlock*)0);
        if (saved != 0)
            AssignRef(&saved->mpLinked, (cSPEditorBlock*)0);
    } else {
        SetFlag(0x3a, 0);
        if (!GetFlag(0x39)) {
            AssignRef(&mpLinked, mpLinkedAlt);
            if (mpLinked != 0) {
                cSPEditorBlock* r = mpLinked;
                AssignRef(&r->mpLinked, r->mpLinkedAlt);
            }
        }
    }
    int n = (int)(((char*)mpChildEnd - (char*)mpChildBegin) >> 2);
    for (int i = 0; i < n; ++i)
        mpChildBegin[i]->RefreshLinkedFlag();
}

// @ 0x0044ede0
void cSPEditorBlock::RecursiveFlagA()
{
    bool b = false;
    if (mpSocketConnector != 0 && mpLinked != 0) {
        if (mpSocketConnector->FUN_00435c80())
            b = true;
    }
    SetFlag(0x3a, b ? 1 : 0);
    int n = (int)(((char*)mpChildEnd - (char*)mpChildBegin) >> 2);
    for (int i = 0; i < n; ++i)
        mpChildBegin[i]->RecursiveFlagA();
}

// @ 0x0044eea0
void cSPEditorBlock::RecursiveFlagB()
{
    if (GetFlag(0x39)) {
        int n = (int)(((char*)mpChildEnd - (char*)mpChildBegin) >> 2);
        for (int i = 0; i < n; ++i) {
            cSPEditorBlock* c = mpChildBegin[i];
            if (c->mpLinked == 0)
                c->RecursiveFlagB();
            else
                c->RefreshLinkedFlag();
        }
    }
}

// @ 0x0044efb0
void cSPEditorBlock::RecursiveFlagC()
{
    if (GetFlag(0x3a)) {
        SetFlag(0x39, 1);
        SetFlag(0x3a, 0);
        cSPEditorBlock* p = mpLinked;
        mpLinked = 0;
        ReleaseBlock(p);
        if (p != 0) {
            cSPEditorBlock* q = p->mpLinked;
            p->mpLinked = 0;
            ReleaseBlock(q);
        }
    }
    int n = (int)(((char*)mpChildEnd - (char*)mpChildBegin) >> 2);
    for (int i = 0; i < n; ++i)
        mpChildBegin[i]->RecursiveFlagC();
}

// @ 0x0044f130
void cSPEditorBlock::SetScaleType(int type)
{
    if (GetFlag(0xb)) {
        if (GetFlag(0xa)) {
            mScaleType = type;
            SetFlag(9, 1);
        } else {
            mScaleType = 2;
        }
    } else {
        mScaleType = 3;
    }
}

// @ 0x0044f240
int cSPEditorBlock::CalculateSymmetrySign()
{
    FUN_0044a7e60(this);
    if (GetFlag(7))
        return 0;
    char flag = 0;
    if (mpSocketConnector != 0) {
        flag = mpSocketConnector->GetFlag(7) ? 1 : 0;
        if (!flag) {
            flag = mpSocketConnector->GetFlag(0) ? 0 : 1;
        }
    }
    int a = FUN_0044c050();
    int b = FUN_0044c450();
    int result = a;
    if (result == 0) {
        result = b;
        if (result == 0) {
            char pb = 0;
            cPropertyList* p = mpPropList;
            if (p != 0) {
                void* prop = 0;
                if (p->GetProperty(0x7bd0ca3e, &prop)) {
                    if (*(unsigned short*)((char*)prop + 0x12) == 1)
                        pb = *(char*)PropertyGetBool(prop);
                }
            }
            if (pb)
                result = -1;
        }
    }
    (void)flag;
    (void)*(void**)((char*)this + 0x33c);
    return result;
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380
    void SP_GetPropertyAsKey(...); // 0x006a1250

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Bounds {
    ~Bounds(); // 0x004ae250
};
}
