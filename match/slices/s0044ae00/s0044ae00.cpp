// Slice s0044ae00: cSPEditorBlock accessors / bounding-box /Od /Ob1 helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"
#include <math.h>
#include <float.h>

struct V3 {
    float x, y, z;
    V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
struct M3 {
    float m[9];
    M3& operator=(const M3& o);
};
struct V3Q {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct F3 {
    float v[3];
    float operator[](int i) const { return v[i]; }
};
struct V3P { float x, y, z; V3P() {} V3P(const V3P& o) : x(o.x), y(o.y), z(o.z) {} };
struct Mat9 { float m[9]; };

// Smart pointer shape used by the editor (AutoRefCount): inline conversion + operator->.
template <class T>
struct Sp {
    T* p;
    operator T*() const { return p; }
    T* operator->() const { return p; }
};

struct Prop { char pad[0x12]; unsigned short type; float* GetFloat(); };
struct PropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProp(unsigned id, Prop** out);   // slot 9 (+0x24)
};

// cSPBoundingBox: min then max.
extern const float kFltMax;                         // 0x013ec2a0
struct Xf {
    unsigned short flags;
    unsigned short count;
    V3 pos;
    float scale;
    Mat9 mat;
    Xf();                                           // 0x00409930
    void SetPosition(const V3& p) { pos = p; flags |= 4; ++count; }
    void SetOrientation(const Mat9& m) { mat = m; flags |= 2; ++count; }
    void SetScale(float s) { scale = s; ++count; }
};
struct BBox {
    V3Q mn, mx;
    BBox();                                         // 0x00409c00
    BBox(const BBox& o);                            // 0x00511140
    void SetCenterRadius(const V3Q* c, float r);     // 0x00409ce0
    void Transform(Xf* x);                          // 0x00409dd0
    void Scale(float s);                            // 0x0044ad00
    void Merge(const BBox& o);                      // 0x0043f050
    bool IsInverted() { return mn[0] > mx[0]; }
    bool IsInfinite() { return mn[0] == -kFltMax || mx[0] == kFltMax; }
};
extern V3Q g_defaultCenter;                          // 0x015d255c

struct Handle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Vfn14();
    void SetBoundingBox(BBox* b);                   // 0x00485200
    void F5650();                                   // 0x00485650
    bool IsFlagSet();                               // 0x0047f290
    void F5550();                                   // 0x00485550
};

struct Fade {
    bool IsPlaying();                               // 0x00434100
    void Update(float dt);                          // 0x00433b30
};

struct Bits32 {
    unsigned int w;
    void SetBit(unsigned i) { w |= (1u << (i % 32)); }
    void ClearBit(unsigned i) { w &= ~(1u << (i % 32)); }
    void set(unsigned i, bool v) {
        if (i < 32) {
            if (v)
                SetBit(i);
            else
                ClearBit(i);
        }
    }
};
struct Obj { unsigned int pad0; Bits32 flags; };

struct Link {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11();
    virtual void Vfn30(int a, int b);               // +0x30
};

// +0x10 model / +0x18 model world; slots are 0x54 / 0x60 / 0xd4 / 0xe4.
struct ModelWorld {
    virtual void w00();
    virtual void w01();
    virtual void w02();
    virtual void w03();
    virtual void w04();
    virtual void w05();
    virtual void w06();
    virtual void w07();
    virtual void w08();
    virtual void w09();
    virtual void w0a();
    virtual void w0b();
    virtual void w0c();
    virtual void w0d();
    virtual void w0e();
    virtual void w0f();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual BBox* GetBounds(Obj* model);            // +0x60 (6 floats: min, max)
    virtual void w19();
    virtual void w1a();
    virtual void w1b();
    virtual void w1c();
    virtual void w1d();
    virtual void w1e();
    virtual void w1f();
    virtual void w20();
    virtual void w21();
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w2a();
    virtual void w2b();
    virtual void w2c();
    virtual void w2d();
    virtual void w2e();
    virtual void w2f();
    virtual void w30();
    virtual void w31();
    virtual void w32();
    virtual void w33();
    virtual void w34();
    virtual void Vfnd4(Obj* a, void* b, int c);       // +0xd4
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void Vfne4(Obj* model, BBox* out);        // +0xe4
};
struct Sizer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d(); virtual void v0e();
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual void Vfn54(unsigned inst, unsigned group, float* begin, int count, V3Q* mn, V3Q* mx);   // +0x54
};
Sizer* GetSizer();                                  // 0x00401010

struct Blk;
struct BlkVec {
    Sp<Blk>* mpBegin;
    Sp<Blk>* mpEnd;
    Sp<Blk>* mpCap;
    int size() const { return (int)(mpEnd - mpBegin); }
    Sp<Blk>& operator[](int i) { return mpBegin[i]; }
};
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct Blk {
    char pad00[0xc];
    Sp<PropList> mPropList;     // +0xc
    Sp<Obj> mModel;             // +0x10
    char pad14[4];
    Sp<ModelWorld> mWorld;      // +0x18
    unsigned mInstance;         // +0x1c
    unsigned mGroup;            // +0x20
    char pad24[0x2c - 0x24];
    bool m2c;
    char pad2d[0x34 - 0x2d];
    bool m34;                   // +0x34
    char pad35[0x48 - 0x35];
    V3 mPosition;               // +0x48
    char pad54[0x60 - 0x54];
    Mat9 mOrient;               // +0x60
    char pad84[0x14c - 0x84];
    Sp<Handle> mRing[5];        // +0x14c
    char pad160[0x188 - 0x160];
    int m188;                   // +0x188
    char pad18c[0x1a8 - 0x18c];
    bool m1a8;
    bool m1a9;
    char pad1aa[2];
    int m1ac;
    char pad1b0[0x1d8 - 0x1b0];
    float mScaleY;              // +0x1d8
    char pad1dc[0x1e8 - 0x1dc];
    V3 mVec;                    // +0x1e8
    M3 mMat;                    // +0x1f4
    char pad218[0x230 - 0x218];
    bool m230;
    char pad231[0x284 - 0x231];
    char m284[0x38];            // +0x284
    char pad2bc[0x33c - 0x2bc];
    Sp<Blk> mSocket;            // +0x33c
    BlkVec mChildren;           // +0x340
    char pad34c[0x3a0 - 0x34c];
    V3P m3a0;                   // +0x3a0
    char pad3ac[0x3e0 - 0x3ac];
    Sp<Blk> m3e0;               // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    Sp<Link> m3ec;              // +0x3ec
    Sp<Obj> m3f0;               // +0x3f0
    char pad3f4[0x40c - 0x3f4];
    F3 m40c;              // +0x40c
    char pad418[0x434 - 0x418];
    int m434;                   // +0x434
    char pad438[0x604 - 0x438];
    int m604;                   // +0x604
    char pad608[0x704 - 0x608];
    FloatVec m704;              // +0x704
    char pad710[0xdc8 - 0x710];
    unsigned int mFlags[2];     // +0xdc8 (bitset<60>)
    Fade mFade;                 // +0xdd0

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

    BBox GetBBox(int type, bool a, bool b);         // 0x0044ae00
    float GetDefaultScale();
    V3* B550(V3* out);
    M3* B590(M3* out);
    void B640(int a);
    void B6b0();
    bool B780();
    void B7b0(unsigned ms);
    void Ba20(bool a, bool b);

    float FUN_0043eed0();
    float FUN_0043f3f0();
    bool FUN_0044c030();
    void RebuildPhysics();                          // 0x00452040
    void SetBooleanAttribute(int id, bool v);       // 0x00435a10
    bool IsSymmetryLocked();                        // 0x00435c80
    V3P GetOffsetA(int i);                           // 0x00438120
    V3P GetOffsetB(int i);                           // 0x004381e0
    bool Place(V3P a, V3P b);                         // 0x00437b00
    V3P FUN_004364a0();                              // 0x004364a0
};
bool FUN_004a7e60(Blk* b);

// @ 0x0044ae00
BBox Blk::GetBBox(int type, bool a, bool b)
{
    BBox box;
    if (a && GetFlag(10) && (GetFlag(11) || GetFlag(7))) {
        if (GetFlag(11)) {
            float h0 = FUN_0043eed0();
            float h1 = FUN_0043f3f0();
            float avg = (h0 + h1) * 0.5f;
            float depth = (float)fabs(m40c[1]);
            float e = avg * 0.06f;
            box.mn.x = -e;
            box.mn.y = -depth;
            box.mn.z = -e;
            box.mx.x = e;
            box.mx.y = 0.0f;
            box.mx.z = e;
        } else {
            box.mn.x = -0.19f;
            box.mn.y = -0.07f;
            box.mn.z = -0.35f;
            box.mx.x = 0.19f;
            box.mx.y = 0.07f;
            box.mx.z = 0.03f;
        }
    } else if (mModel && mWorld) {
        if (GetFlag(21)) {
            mWorld->Vfne4(mModel, &box);
        } else {
            BBox* r = mWorld->GetBounds(mModel);
            box.mx = r->mx;
            box.mn = r->mn;
        }
    } else {
        Sizer* s = GetSizer();
        int cnt = m704.size();
        float* beg = m704.mpBegin;
        s->Vfn54(mInstance, mGroup, beg, cnt, &box.mn, &box.mx);
    }
    if (box.IsInverted() || box.IsInfinite())
        box.SetCenterRadius(&g_defaultCenter, 0.01f);
    switch (type) {
    case 0: {
        Xf xf;
        xf.SetPosition(mPosition);
        xf.SetOrientation(mOrient);
        xf.SetScale(mScaleY);
        box.Transform(&xf);
        break;
    }
    case 1:
        box.Scale(mScaleY);
        break;
    }
    float scale = (type == 2) ? 1.0f : mScaleY;
    if (b) {
        int n = mChildren.size();
        int i;
        for (i = 0; i < n; i++)
            box.Merge(mChildren[i]->GetBBox(type, a, b));
    }
    return box;
}

// @ 0x0044b550  (byte-exact)
V3* Blk::B550(V3* out)
{
    *out = mVec;
    return out;
}

// @ 0x0044b590  (near miss: frame 0x30)
M3* Blk::B590(M3* out)
{
    *out = mMat;
    return out;
}

// @ 0x0044b5c0
float Blk::GetDefaultScale()
{
    if (mPropList) {
        float r = 1.0f;
        PropList* pl = mPropList.p;
        if (pl) {
            Prop* p;
            if (pl->GetProp(0x536c50c, &p) && p->type == 0xd)
                r = *p->GetFloat();
        }
        return r;
    }
    return 1.0f;
}

// @ 0x0044b640
void Blk::B640(int)
{
    BBox box = GetBBox(2, false, false);
    for (int i = 0; i < 3; i++) {
        if (mRing[2 + i]) {
            mRing[2 + i]->SetBoundingBox(&box);
        }
    }
}

// @ 0x0044b6b0
void Blk::B6b0()
{
    if (m2c) {
        for (int i = 0; i < 3; i++) {
            if (mRing[2 + i]) {
                mRing[2 + i]->F5650();
                mRing[2 + i]->Vfn14();
                if (mRing[2 + i]->IsFlagSet()) {
                    mRing[2 + i]->F5550();
                }
            }
        }
    }
}

// @ 0x0044b780  (byte-exact)
bool Blk::B780()
{
    if (m604 != 0)
        return true;
    if (m434 != 0)
        return true;
    return false;
}

// @ 0x0044b7b0
void Blk::B7b0(unsigned ms)
{
    if (mFade.IsPlaying()) {
        float dt = (float)ms * 0.001f;
        mFade.Update(dt);
    }
    if (FUN_0044c030() || m230) {
        m230 = false;
        if (m1a8 && m188 != 0)
            RebuildPhysics();
        if (m1a9) {
            if (m1ac > 5) {
                m1a9 = false;
            } else if (mSocket) {
                if (!mSocket->GetFlag(10)) {
                    if (Place(GetOffsetA(1), GetOffsetB(1))) {
                        m1a9 = false;
                    } else {
                        m1ac = m1ac + 1;
                        if (m1ac == 5)
                            m3a0 = FUN_004364a0();
                    }
                } else {
                    m1a9 = false;
                }
            }
        }
        if (GetFlag(39) && mModel) {
            mWorld->Vfnd4(mModel, &m284, 0);
        }
    }
}

// @ 0x0044ba20
void Blk::Ba20(bool a, bool b)
{
    int n;
    int i;
    if (mModel) {
        if (FUN_0044c030()) {
            SetBooleanAttribute(9, true);
            Obj* o = mModel.p;
            o->flags.set(0, false);
            if (m3ec)
                m3ec->Vfn30(1, 0);
            if (m3f0 && !GetFlag(5)) {
                Obj* o2 = m3f0.p;
                o2->flags.set(0, false);
            }
            m34 = false;
        }
        n = mChildren.size();
        for (i = 0; i < n; i++) {
            if (!FUN_004a7e60(this) && mChildren[i]->IsSymmetryLocked()) {
                mChildren[i]->Ba20(a, true);
            } else if (b) {
                mChildren[i]->Ba20(a, b);
            }
        }
        if (a && m3e0)
            m3e0->Ba20(false, false);
    }
}
