// Slice s00b4fd80: attribute-property reader into globals, a camera/constraint-ish ctor and
// per-frame helpers (Havok hkVector4 transformed positions, terrain height sampling, cube-face
// selection). Mixed SSE/x87 float code.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char uchar;

// ------------------------------------------------------------------ variant property host
struct Variant {
    int            mData;    // +0x00 (pointer when flags & 0x30)
    char           pad04[0xc];
    unsigned char  mFlags;   // +0x10
    char           pad11;
    short          mType;    // +0x12
};
struct IVarHost {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool GetProp(unsigned id, Variant** out);   // +0x24
};

static __forceinline int ReadIntProp(IVarHost* obj, unsigned id, int def)
{
    if (obj) {
        Variant* v;
        if (obj->GetProp(id, &v)) {
            short t = v->mType;
            if (t == 10 || t == 0x10) {
                if (v->mFlags & 0x30) return *(int*)v->mData;
                return *(int*)(v ? v : 0);
            }
        }
    }
    return def;
}

static __forceinline float ReadFloatProp(IVarHost* obj, unsigned id, float def)
{
    if (obj) {
        Variant* v;
        if (obj->GetProp(id, &v)) {
            short t = v->mType;
            if (t == 0xd || t == 0x10) {
                if (v->mFlags & 0x30) return *(float*)v->mData;
                return *(float*)(v ? v : 0);
            }
        }
    }
    return def;
}

extern unsigned g_167ece4;   // 0x0167ece4
extern float    g_1569ae8;   // 0x01569ae8
extern float    g_1569aec;   // 0x01569aec
extern float    g_1569af0;   // 0x01569af0
extern float    g_1569af4;   // 0x01569af4

// @ 0x00b4fd80
void __cdecl FUN_00b4fd80(IVarHost* obj)
{
    g_167ece4 = (unsigned)ReadIntProp(obj, 0x7a2456e2, 0x3759d899);
    g_1569ae8 = ReadFloatProp(obj, 0x19b1e0f2, 1.0f);
    float f = ReadFloatProp(obj, 0x9c9f1c1b, 20.0f);
    g_1569aec = f * f;
    f = ReadFloatProp(obj, 0x421ce80f, 100.0f);
    g_1569af0 = f * f;
    g_1569af4 = ReadFloatProp(obj, 0x8ca0ae12, 100.0f);
}

// ------------------------------------------------------------------ ref-counted object (plain ref at +4)
struct RC {
    virtual void Release(int);   // +0x00
    int   mRef;                  // +0x04
};
struct IChildSrc {
    virtual void c0(); virtual void c1(); virtual void c2();
    virtual void* GetChild();    // +0x0c
};
struct RCNode {
    char  pad24[0x24];
    IChildSrc* m24;              // +0x24
};
struct RC2 : RC {
    char  pad08[0x1c];
    RCNode* m24;                 // +0x24
};

static __forceinline void AssignRC(RC** slot, RC* np)
{
    RC* old = *slot;
    if (np != old) {
        if (np) np->mRef++;
        *slot = np;
        if (old) {
            if (--old->mRef == 0) {
                old->mRef = 1;
                old->Release(1);
            }
        }
    }
}

struct ChildObj {
    virtual void v0();
    char  pad04[4];
    RC*   m08;                  // +0x08
    RC*   m0c;                  // +0x0c
    int   m10;
    char  pad14[0x20];
    float f34;                  // +0x34
    float f38;                  // +0x38
};

extern void* g_vtblFB0;         // 0x01461390
extern const float kNeg200;     // 0x0146138c = -200.0f
extern const float kPos200;     // 0x01477fbc = 200.0f

struct ObjFFB0 : RC2 {
    void* ctor(RC* param);      // 0x00b4ffb0
};

// @ 0x00b4ffb0
void* __thiscall ObjFFB0::ctor(RC* param)
{
    *(RC**)((char*)this + 0x34) = param;
    *(int*)((char*)this + 8) = 0;
    *(void**)this = &g_vtblFB0;
    *(short*)((char*)this + 6) = 1;
    *(RC**)((char*)this + 0x38) = 0;
    *(RC**)((char*)this + 0x3c) = 0;

    ChildObj* child = (ChildObj*)this->m24->m24->GetChild();

    AssignRC((RC**)((char*)this + 0x38), child->m0c);
    AssignRC((RC**)((char*)this + 0x3c), child->m08);

    RC* m3c = *(RC**)((char*)this + 0x3c);
    *(int*)((char*)this + 0x40) = *(int*)((char*)m3c + 0x10);
    int n = *(int*)((char*)m3c + 8);
    *(int*)((char*)this + 0x44) = n;
    *(int*)((char*)this + 0x48) = n * n;
    *(float*)((char*)this + 0x4c) = child->f34;
    *(float*)((char*)this + 0x50) = child->f38;

    float neg = kNeg200;
    *(float*)((char*)this + 0x10) = neg;
    *(float*)((char*)this + 0x14) = neg;
    *(float*)((char*)this + 0x18) = neg;
    *(float*)((char*)this + 0x1c) = neg;
    float pos = kPos200;
    *(float*)((char*)this + 0x20) = pos;
    *(float*)((char*)this + 0x24) = pos;
    *(float*)((char*)this + 0x28) = pos;
    *(float*)((char*)this + 0x2c) = pos;
    return this;
}

// ------------------------------------------------------------------ Havok vector helper
struct HkVec { char d[0x10]; };
struct HkObj { void setTransformedPos(const void* a, HkVec* out); };  // 0x01081360

struct Obj500E0 {
    void F(const void* a, HkObj* b);   // 0x00b500e0
};

// @ 0x00b500e0
void __thiscall Obj500E0::F(const void* a, HkObj* b)
{
    float s = *(float*)((char*)this + 0x50) + *(float*)((char*)this + 0x4c);
    if (s != *(float*)((char*)this + 0x30)) {
        *(float*)((char*)this + 0x20) = s;
        *(float*)((char*)this + 0x24) = s;
        *(float*)((char*)this + 0x28) = s;
        *(float*)((char*)this + 0x2c) = 0.0f;
        float n = s * -1.0f;
        *(float*)((char*)this + 0x10) = n;
        *(float*)((char*)this + 0x14) = n;
        *(float*)((char*)this + 0x18) = n;
        *(float*)((char*)this + 0x1c) = 0.0f;
        *(float*)((char*)this + 0x30) = s;
    }
    HkObj* va = (HkObj*)a;
    va->setTransformedPos(a, (HkVec*)((char*)this + 0x10));
    b->setTransformedPos(a, (HkVec*)((char*)this + 0x20));
}

// @ 0x00b50170
struct Variant8 { uchar flag; float v; };
struct IVarInvoke {
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
    virtual void i4(); virtual void i5(); virtual void i6(); virtual void i7();
    virtual void i8();
    virtual void Invoke(unsigned a, unsigned b, Variant8 t, unsigned c);  // +0x24
};
struct Obj50170 {
    void F(unsigned a, unsigned b, unsigned c);   // 0x00b50170
};
// @ 0x00b50170
void __thiscall Obj50170::F(unsigned a, unsigned b, unsigned c)
{
    Variant8 t;
    t.flag = 0;
    t.v = 0.0f;
    ((IVarInvoke*)this)->Invoke(a, b, t, c);
}

// @ 0x00b501a0
struct S24 { float a, b, c, d; int e; float f; };
struct Obj501A0 { float a, b, c, d; int e; float f; S24& operator=(const S24& src); };
// @ 0x00b501a0
S24& __thiscall Obj501A0::operator=(const S24& src)
{
    a = src.a;
    b = src.b;
    c = src.c;
    d = src.d;
    e = src.e;
    f = src.f;
    return *(S24*)this;
}

// @ 0x00b501d0  (partial: terrain height/face sampling)
struct Obj501D0 { void F(float* p, unsigned a, char b, float e, void* f); };
// @ 0x00b501d0
void __thiscall Obj501D0::F(float* p, unsigned a, char b, float e, void* f)
{
    (void)this; (void)p; (void)a; (void)b; (void)e; (void)f;
}

// @ 0x00b50780
struct SVec { float a, b, c, d; int e; float f; };
struct Obj50780 {
    char pad0[4];
    float mDist;      // +0x04
    uchar mFlag;      // +0x08
    char pad9[3];
    SVec* mDst;       // +0x0c
    void F(unsigned param2, SVec* src);   // 0x00b50780
};
// @ 0x00b50780
void __thiscall Obj50780::F(unsigned param2, SVec* src)
{
    (void)param2;
    if (mDist > src->f) {
        float nf = src->f;
        SVec* dst = mDst;
        mDist = nf;
        dst->a = src->a;
        dst->b = src->b;
        dst->c = src->c;
        dst->d = src->d;
        dst->e = src->e;
        dst->f = src->f;
        mFlag = 1;
    }
}

// @ 0x00b507d0
struct Obj507D0 { void F(unsigned param2, unsigned param3, uchar* out); };  // 0x00b507d0
// @ 0x00b507d0
void __thiscall Obj507D0::F(unsigned param2, unsigned param3, uchar* out)
{
    (void)param2;
    struct Tmp { void* vt; uchar flag; float v; };
    Tmp t;
    t.vt = &g_vtblFB0;
    t.flag = 0;
    t.v = *(float*)((char*)this + 0x14);
    ((IVarInvoke*)this)->Invoke(param3, 0, *(Variant8*)((char*)&t + 4), 0);
    *out = t.flag;
}

// @ 0x00b50820
struct Obj50820 { void F(float* p, unsigned a, unsigned b); };   // 0x00b50820
// @ 0x00b50820
void __thiscall Obj50820::F(float* p, unsigned a, unsigned b)
{
    (void)this; (void)p; (void)a; (void)b;
}
