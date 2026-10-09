// Slice s006f0890 -- SP::cEffectsRenderer helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"
#include <intrin.h>

inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}

// EA allocator entry points (operator_new 0xf473a0 / operator_delete__ 0xf47380)
void* __cdecl EaNew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void __cdecl EaDelete(void* p);  // 0x00f47380

// ---- refcounted image resource (refcount at +8) -----------------------------
struct RcObj {
    void* vt;
    int pad;
    long rc;
    void Release()
    {
        long* p = &rc;
        _InterlockedExchangeAdd(p, -1);
        long n = _InterlockedExchangeAdd(p, 0);
        if (n < 1)
            _InterlockedExchangeAdd(p, 1);
        else
            _InterlockedExchangeAdd(p, 0);
    }
};

struct ImageRef {
    RcObj* p;
    ImageRef() : p(0) {}
    ~ImageRef() { if (p) p->Release(); }
    void Assign(RcObj* o);  // 0x00576650
};

// ---- stub interfaces ---------------------------------------------------------
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void RemoveListener(void* handler, unsigned msgId, int mask);  // +0x2c
};

struct IFlagSink {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void SetFlag(int f);  // +0x50
};

struct IObj1 { virtual void v0(); virtual void Release1(); };                       // slot 1
struct IObj3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void Release3(); };
struct IObj5 {
    virtual void v0(); virtual void v1(); virtual void Release2();
    virtual void v3(); virtual void v4(); virtual void Flush();
};  // Release2 +8, Flush +0x14

struct Viewer24 {
    char pad[8];
    IObj3 sub;
    void Teardown();  // 0x0076b000
};

struct SubObj {  // 0x24c/0x250/0x254 members
    void Cleanup();  // 0x007c3ba0
    void Dtor();     // 0x007c4000
};

extern IMessageServer* __cdecl MessageServer();      // 0x0067dcc0
extern IFlagSink* __cdecl GetFlagSink();             // 0x0067dd50
extern void __cdecl ShutdownTextRenderer();

extern "C" void* __cdecl MoveShorts(void* dst, const void* src, unsigned n);  // 0x011e0744

struct P8 { int a, b; };
struct V8 {
    P8* mpBegin;
    P8* mpEnd;
    int pad[3];
    __forceinline void Erase(P8* first, P8* last)
    {
        P8* d = first;
        P8* e0 = mpEnd;
        for (P8* s = last; s != e0; ++s, ++d) {
            d->a = s->a;
            d->b = s->b;
        }
        mpEnd += -(last - first);
    }
};

struct E70 {
    char d[0x70];
    E70();                       // 0x006e9b00
    ~E70();                      // 0x006ea920
    void Assign(const E70* o);   // 0x006ebb80
    void Copy(const E70* o);     // 0x006eabc0
};

struct TextRenderer {
    void Release();  // 0x007a8530
};

struct VE70 {  // vector of 0x70-byte elements, erase with assignment + dtor
    E70* mpBegin;
    E70* mpEnd;
    __forceinline void Erase(E70* first, E70* last)
    {
        E70* d = first;
        E70* e0 = mpEnd;
        for (E70* s = last; s != e0; ++s, ++d)
            d->Assign(s);
        E70* e = mpEnd;
        for (; d < e; ++d)
            d->~E70();
        mpEnd += (last - first);
    }
};

struct V70Owner {  // object at +0x174 (this for 0x6eb990)
    E70* mpBegin;
    E70* mpEnd;
    void DestroyRange(E70* first, E70* last);  // 0x006eb990
    __forceinline void Erase(E70* first, E70* last)
    {
        E70* d = first;
        E70* e0 = mpEnd;
        for (E70* s = last; s != e0; ++s, ++d)
            d->Copy(s);
        DestroyRange(d, mpEnd);
        mpEnd += (last - first);
    }
};


struct VShort {
    short* mpBegin;
    short* mpEnd;
    __forceinline void Erase(short* first, short* last)
    {
        MoveShorts(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd += -(last - first);
    }
};

struct Effects890 {
    char pad0[0x14];
    char handler[4];
    int m18, m1c;
    int m20;
    Viewer24* mViewer;           // +0x24
    IObj3* m28;                  // +0x28
    char pad2c[0x40 - 0x2c];
    IObj1* m40;                  // +0x40
    char pad44[4];
    VE70 mSets;                  // +0x48
    char pad50[0x5c - 0x50];
    VShort mAct;                 // +0x5c
    char pad64[0x104 - 0x64];
    V8 mDrawLists[4];            // +0x104 (stride 0x14)
    char pad154[0x174 - 0x154];
    V70Owner mV174;              // +0x174
    char pad17c[0x188 - 0x17c];
    VShort mFree;                // +0x188
    char pad190[0x1b0 - 0x190];
    int m1b0, m1b4;
    char pad1b8[0x204 - 0x1b8];
    TextRenderer mText;          // +0x204
    char pad208[0x24c - 0x208];
    SubObj* m24c;
    SubObj* m250;
    SubObj* m254;
    char pad258[0x360 - 0x258];
    IObj5* m360;
    IObj5* m364;
    char pad368[1];
    bool m369;

    bool Shutdown();
};

// @ 0x006f0890
bool Effects890::Shutdown()
{
    IMessageServer* ms = MessageServer();
    ms->RemoveListener(this ? (void*)handler : 0, 0x6694879, (int)0xffffd8f1);
    m1b0 = 0;
    m1b4 = 0;
    if (m369) {
        IFlagSink* s = GetFlagSink();
        s->SetFlag(0x12);
        s->SetFlag(3);
        s->SetFlag(0x20);
        s->SetFlag(0x16);
    }
    m20 = 0;
    if (m28) {
        IObj3* t = m28;
        m28 = 0;
        t->Release3();
    }
    mText.Release();

    // clear four 8-byte-element vectors
    V8* v = mDrawLists;
    for (int i = 4; i != 0; --i, ++v)
        v->Erase(v->mpBegin, v->mpEnd);

    mSets.Erase(mSets.mpBegin, mSets.mpEnd);
    mAct.Erase(mAct.mpBegin, mAct.mpEnd);
    mV174.Erase(mV174.mpBegin, mV174.mpEnd);
    mFree.Erase(mFree.mpBegin, mFree.mpEnd);

    if (mViewer) {
        mViewer->Teardown();
        if (mViewer) {
            Viewer24* t = mViewer;
            mViewer = 0;
            t->sub.Release3();
        }
    }
    if (m360) {
        m360->Flush();
        if (m360) {
            IObj5* t = m360;
            m360 = 0;
            t->Release2();
        }
    }
    if (m364) {
        m364->Flush();
        if (m364) {
            IObj5* t = m364;
            m364 = 0;
            t->Release2();
        }
    }
    if (m24c) {
        m24c->Cleanup();
        SubObj* t = m24c;
        if (t) {
            t->Dtor();
            EaDelete(t);
        }
    }
    if (m250) {
        m250->Cleanup();
        SubObj* t = m250;
        if (t) {
            t->Dtor();
            EaDelete(t);
        }
    }
    if (m254) {
        m254->Cleanup();
        SubObj* t = m254;
        if (t) {
            t->Dtor();
            EaDelete(t);
        }
    }
    if (m40) {
        IObj1* t = m40;
        m40 = 0;
        t->Release1();
    }
    return true;
}

// ---- 0x006f0b90: SP::cEffectsRenderer::Render (layer pass) -------------------
extern unsigned g_softStateDirty;     // 0x016f9528
extern unsigned g_samplerA;           // 0x016f9530
extern unsigned g_samplerB;           // 0x016f9534
extern unsigned g_renderDirty;        // 0x016fa38c
extern unsigned g_renderDirty2;       // 0x016fa39c
extern int g_s0;  // 0x016f9fe0
extern int g_s1;  // 0x016f9fdc
extern int g_s2;  // 0x016f9fe4
extern int g_s3;  // 0x016fa018
extern int g_s4;  // 0x016fa014
extern int g_s5;  // 0x016fa01c
extern int g_s6;  // 0x016f9238
extern int g_fogType;                 // 0x016f9f7c
extern int g_r250, g_r410;            // 0x016f9250, 0x016f9410
extern int g_b218;  // 0x016f9218
extern int g_b23c;  // 0x016f923c
extern int g_b21c;  // 0x016f921c
extern int g_b244;  // 0x016f9244
extern int g_b240;  // 0x016f9240
void __cdecl SetBlendMode(int mode);  // 0x011f1340

struct D3DCaps { char pad[0xc4]; unsigned c4; char pad2[4]; unsigned cc; };
D3DCaps* __cdecl GetD3DCAPS9();       // 0x011f8af0

struct ViewIface {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual void SetView(int v);  // +0x24
};
struct IStateSink {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void SetTarget(void* t);  // +0x50
};
extern IStateSink* __cdecl GetStateSink();  // 0x0067ddc0

struct Prop {
    char pad[0x10];
    unsigned char flags;
    char pad2;
    unsigned short type;
};
struct IProps {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool Get(unsigned key, Prop** out);  // +0x24
};
extern struct PropList* g_pProps;  // 0x015fd918
struct PropList : IProps {
    float GetFloatProperty(unsigned key);  // 0x006a2710
};

struct Viewer250 {
    void Copy(int src, int a, int b);  // 0x007c50b0 (static-like: this = viewer)
    float GetA();                      // 0x007c3c90
    float GetB();                      // 0x007c3ca0
    void SetA(float f);                // 0x007c4ba0
    void SetB(float f);                // 0x007c4bc0
};

struct Region {
    int a, b, c, d;
};

struct CamBlock {
    void SetA(float f);  // 0x006ffa80 (this = renderer+0x260)
    void Set(const void* p);  // 0x006ffe00
};

struct Effects0B90 {
    char pad0[0x44];
    struct Inner { char pad[0x110]; bool m110; }* m44;
    char pad48[0x5c - 0x48];
    short* m5c;
    short* m60;
    char pad64[0x188 - 0x64];
    int m188, m18c;
    char pad190[0x1e0 - 0x190];
    ViewIface* m1e0;
    char pad1e4[0x250 - 0x1e4];
    Viewer250* m250;
    char pad254[0x260 - 0x254];
    CamBlock m260;

    void Render(unsigned flags, Region** pr, int arg);
    void DispatchWithAdditionalMaterial(unsigned flags, Region** pr, int arg);  // 0x006ee6f0
    void Pass2(unsigned flags, Region** pr, int arg);                           // 0x006efc70
    void RenderTextureParticles(unsigned flags, Region* pr, int arg);           // 0x006efe90
    void Pass40(unsigned flags, Region** pr, int arg);                          // 0x006e78b0
    void Pass80(unsigned flags, Region** pr, int arg);                          // 0x006ea030
};

// @ 0x006f0b90
void Effects0B90::Render(unsigned flags, Region** pr, int arg)
{
    if (m1e0)
        m1e0->SetView(*(int*)pr);
    GetStateSink()->SetTarget(m1e0);
    unsigned skip = flags & 0x10000;
    if (skip == 0) {
        g_samplerA |= 0x20;
        g_renderDirty |= 0x8000;
        g_samplerA |= 0x10;
        g_samplerA |= 0x40;
        g_samplerB |= 0x20;
        g_samplerB |= 0x10;
        g_samplerB |= 0x40;
        g_softStateDirty = (g_softStateDirty & 0xfff1ffff) | 0x10000;
        g_s0 = 2;
        g_s1 = 2;
        g_s2 = 2;
        g_s3 = 2;
        g_s4 = 2;
        g_s5 = 2;
        g_s6 = 2;
        g_fogType = 0;
        D3DCaps* caps = GetD3DCAPS9();
        if (caps->c4 <= 0xfffe0000 || caps->cc <= 0xffff0000) {
            g_renderDirty |= 0x200000;
            g_r250 = 0;
        }
        if (caps->c4 <= 0xfffe0000) {
            g_renderDirty2 |= 0x20;
            g_r410 = 0;
        }
        g_renderDirty |= 0x10080;
        g_b23c = 4;
        g_b218 = 1;
        SetBlendMode(0x60005);
        g_renderDirty |= 0x60100;
        g_b21c = 1;
        g_b244 = 5;
        g_b240 = 0;
    }
    m260.Set((char*)*(int*)pr + 0xc0);
    if (g_pProps) {
        Prop* p;
        if (g_pProps->Get(0x13d7382, &p) && p->type == 0xd) {
            float* f = (float*)p;
            if (p->flags & 0x30)
                f = *(float**)p;
            m260.SetA(*f);
        }
    }
    if (g_pProps) {
        Prop* p;
        if (g_pProps->Get(0x63b0756, &p) && p->type == 0xd) {
            float* f = (float*)p;
            if (p->flags & 0x30)
                f = *(float**)p;
            m260.SetA(*f);
        }
    }
    if (flags & 4)
        DispatchWithAdditionalMaterial(flags, pr, arg);
    if ((flags & 2) && m188 != m18c)
        Pass2(flags, pr, arg);
    if ((flags & 1) && m5c != m60) {
        if (skip == 0) {
            g_renderDirty |= 0x10080;
            g_b218 = 0;
            g_b23c = 2;
            SetBlendMode(0x60005);
            g_renderDirty |= 0x60100;
            g_b21c = 1;
            g_b244 = 5;
            g_b240 = 0;
        }
        unsigned hi = flags & 0x4000000;
        Region* use;
        Region tmp;
        if (hi || (flags & 0x2000000)) {
            float f = g_pProps->GetFloatProperty(0x637fee8);
            m250->Copy(*(int*)pr, 0, 0);
            if (hi)
                m250->SetA(m250->GetA() + f);
            else if (flags & 0x2000000)
                m250->SetB(m250->GetB() - f);
            Region* src = *pr;
            tmp.a = (int)m250;
            tmp.b = src->b;
            tmp.c = src->c;
            tmp.d = src->d;
            use = &tmp;
        } else
            use = (Region*)pr;
        RenderTextureParticles(flags, use, arg);
    }
    if (flags & 0x40)
        Pass40(flags, pr, arg);
    if (skip == 0) {
        g_renderDirty |= 0x10080;
        g_b218 = 1;
        g_b23c = 2;
        SetBlendMode(0x10002);
        g_renderDirty |= 0x40100;
        g_b21c = 0;
        g_b244 = 8;
    }
    if ((char)flags < 0 && m44->m110)
        Pass80(flags, pr, arg);
    if (skip == 0) {
        g_renderDirty |= 0x8000;
        g_s6 = 2;
    }
}

// ---- 0x006f0fb0: add a texture particle set --------------------------------
struct KeyPair { int lo, hi; };
struct MatPair { int a, b; };

struct IMatMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual int Find(int lo);  // +0x28
};
struct IResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual RcObj* Get(int lo, int hi, int flag);  // +0x20
};
extern IMatMgr* __cdecl MaterialManager();    // 0x0067dd70
extern IResMgr* __cdecl ResourceManager();    // 0x0067dd60
extern RcObj** g_defaultImage;                // 0x01618d10

struct MatCache {
    MatPair* Find(int lo, int hi);   // 0x006f2050
    RcObj* GetImg(int lo, int hi);   // 0x006e65e0
};

struct SetDesc {
    int lo, hi;
    char pad8;
    unsigned char kind;   // +9
    unsigned char fl;     // +0xa
    char padb[0x18 - 0xb];
    int lo2, hi2;
    char rest[0x20 - 0x20];
};

struct Set70 {
    int id;                 // +0
    char desc[0x20];        // +8
    char pad[0x28 - 0x28];
};

struct Effects0FB0 {
    char pad0[0x40];
    MatCache* m40;
    char pad44[4];
    E70* mSetsBegin;        // +0x48
    E70* mSetsEnd;          // +0x4c
    char pad50[0x70 - 0x50];
    int* mFreeBegin;        // +0x70
    int* mFreeEnd;          // +0x74
    char pad78[0x84 - 0x78];
    int mMat84[0x10];       // +0x84
    int mMatC4[0x10];       // +0xc4
    char pad104[0x1e4 - 0x104];
    bool m1e4;

    bool AddParticleSet(int id, const SetDesc* d, int* outIndex);
};

void PushSet(E70** vec, const E70* v);  // 0x006f0810

extern int g_default_dummy;

// @ 0x006f0fb0
bool Effects0FB0::AddParticleSet(int id, const SetDesc* d, int* outIndex)
{
    ImageRef img1;
    int mat1 = 0;
    ImageRef img2;
    int mat2 = 0;
    // inline: resource lookup
    if (d->kind == 0xf) {
        MatPair* p = m40->Find(d->lo, d->hi);
        if (p) {
            mat1 = p->a;
            mat2 = p->b;
        } else
            mat1 = MaterialManager()->Find(d->lo);
        if (mat1 == 0)
            return false;
        if ((d->lo2 & d->hi2) != -1) {
            if (d->lo2 == 0x7f000000 && d->hi2 == 0) {
                img1.Assign(*g_defaultImage);
            } else {
                img1.Assign(m40->GetImg(d->lo2, d->hi2));
                if (img1.p) {
                    unsigned hi = (unsigned)d->hi2;
                    if ((hi & 0xc0000000) == 0x40000000 && (hi & 0xff00) == 0x2800) {
                        hi = (hi & 0xffff2cff) | 0x2c00;
                        img1.Assign(ResourceManager()->Get(d->lo2, hi, 0));
                    }
                }
            }
        }
    } else {
        if (d->fl & 3)
            mat1 = mMat84[d->kind];
        else
            mat1 = mMatC4[d->kind];
        if ((d->lo & d->hi) != -1) {
            if (d->lo == 0x7f000000 && d->hi == 0)
                img1.Assign(*g_defaultImage);
            else
                img1.Assign(ResourceManager()->Get(d->lo, d->hi, 0));
        }
        if ((d->lo2 & d->hi2) != -1) {
            if (d->lo2 == 0x7f000000 && d->hi2 == 0)
                img2.Assign(*g_defaultImage);
            else
                img2.Assign(ResourceManager()->Get(d->lo2, d->hi2, 0));
        }
        if (mat1 == 0)
            return false;
        if (!m1e4 && img1.p == 0)
            return false;
    }

    if (mFreeBegin == mFreeEnd) {
        *outIndex = (int)(mSetsEnd - mSetsBegin);
        E70 tmp;
        PushSet(&mSetsBegin, &tmp);
    } else {
        *outIndex = mFreeEnd[-1];
        mFreeEnd -= 1;
    }
    E70* s = mSetsBegin + *outIndex;
    unsigned char keep = ((unsigned char*)s)[0x49];
    {
        E70 tmp;
        s->Assign(&tmp);
    }
    *(int*)s = id;
    for (int i = 0; i < 8; ++i)
        ((int*)s)[2 + i] = ((const int*)d)[i];
    ((ImageRef*)((char*)s + 0x28))->Assign(img1.p);
    ((ImageRef*)((char*)s + 0x2c))->Assign(img2.p);
    *(int*)((char*)s + 0x5c) = mat1;
    *(int*)((char*)s + 0x60) = mat2;
    ((unsigned char*)s)[0x49] = keep;
    return true;
}

// ---- 0x006f13a0: SP::cEffectsRenderer layer render dispatch ----------------
struct IEffectsMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual int GetDefault();  // +0xa0
};
extern IEffectsMgr* __cdecl EffectsManager();  // 0x0067ddd0

struct IPassA {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Render(unsigned flags, unsigned type, int a, int b);  // +0xc
};

struct App3c { char pad[0xc]; int m0c; };
struct AppProps { char pad[0x3c]; App3c* m3c; };
extern AppProps* g_app;  // 0x015fd918

struct PassB {
    bool Ready();  // 0x007764b0
    void Render(unsigned flags, unsigned type, int a, int b);  // 0x00776e60
};

struct cEffectsRendererLayer {
    char pad0[0x2c];
    int mAt2c;
    char pad1[0x344 - 0x30];
    IPassA* mAt344;
    char pad2[0x34c - 0x348];
    PassB* mAt34c;
    char pad3[0x354 - 0x350];
    int mAt354;

    void RenderMainEffectsLayer(unsigned flags, unsigned type, int a, int b);
};

struct EffectsOuter {
    void RenderTex(unsigned flags, int a, int b);  // 0x006e8810
    void RenderMain(unsigned flags, int a, int b); // 0x006f0b90
};

// @ 0x006f13a0
void cEffectsRendererLayer::RenderMainEffectsLayer(unsigned flags, unsigned type, int a, int b)
{
    if (g_app->m3c->m0c == 0)
        return;
    if (mAt2c == 0)
        mAt2c = EffectsManager()->GetDefault();
    if (flags == 0 || (flags & 0x6000000) != 0)
        flags |= 0xff;
    unsigned t = type;
    mAt354 = b;
    switch (t) {
    case 3:
        if (flags & 0x28) {
            ((EffectsOuter*)((char*)this - 0x18))->RenderTex(flags, a, b);
            mAt354 = 0;
            return;
        }
        break;
    case 6:
    case 18:
    case 19:
    case 24:
    case 28:
        if (flags & 0x47) {
            ((EffectsOuter*)((char*)this - 0x18))->RenderMain(flags, a, b);
            mAt354 = 0;
            return;
        }
        break;
    case 22:
        if (mAt344 && (flags & 0x20))
            mAt344->Render(flags, type, a, b);
        if (mAt34c && (flags & 0x10) && !mAt34c->Ready())
            mAt34c->Render(flags, type, a, b);
        break;
    case 32:
        if (mAt34c && (flags & 0x10) && mAt34c->Ready())
            mAt34c->Render(flags, type, a, b);
        break;
    default:
        break;
    }
    mAt354 = 0;
}

// ---- 0x006f1510 / 0x006f16c0: eastl::vector<T0xC0> insert / push_back --------
struct Elt {
    int f0;
    char* m4;
    int f8;
    char* mC;
    int f10;
    char* m14;
    char rest[0xc0 - 0x18];
    Elt();                               // 0x006ec730
    Elt(const Elt& o);                   // 0x006ecaa0
    Elt& operator=(const Elt& o);        // 0x006ecfc0
    ~Elt()
    {
        if (((int)(mC - m4) & ~1) > 2 && m4 && m4 != m14)
            EaDelete(m4);
    }
};
Elt* __cdecl EltCopyBackward(Elt* first, Elt* last, Elt* dstEnd);  // 0x006ed890
Elt* __cdecl EltUninitCopy(Elt* first, Elt* last, Elt* dst);       // 0x006ecd40
void __cdecl EltDestroyRange(Elt* first, Elt* last, Elt* dst);     // 0x006ec6d0

struct EltVector {
    Elt* mpBegin;
    Elt* mpEnd;
    Elt* mpCapacity;
    void Insert(Elt* pos, const Elt* val);
    void PushBack();
};

// @ 0x006f1510
void EltVector::Insert(Elt* pos, const Elt* val)
{
    if (mpEnd != mpCapacity) {
        const Elt* v = val;
        if (v >= pos && v < mpEnd)
            ++v;
        Elt* e = mpEnd;
        if (e)
            new (e) Elt(e[-1]);
        EltCopyBackward(pos, mpEnd - 1, mpEnd);
        *pos = *v;
        ++mpEnd;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    int newCap = n ? n * 2 : 1;
    Elt* newMem = newCap ? (Elt*)EaNew(newCap * sizeof(Elt), "Graphics", 0, 0,
                                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                           : 0;
    Elt* newEnd = EltUninitCopy(mpBegin, pos, newMem);
    EltDestroyRange(mpBegin, pos, newMem);
    if (newEnd)
        new (newEnd) Elt(*val);
    Elt* e = mpEnd;
    Elt* tail = EltUninitCopy(pos, e, newEnd + 1);
    EltDestroyRange(pos, e, newEnd + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        EaDelete(mpBegin);
    mpCapacity = newMem + newCap;
    mpBegin = newMem;
    mpEnd = tail;
}

// @ 0x006f16c0
void EltVector::PushBack()
{
    if (mpEnd < mpCapacity) {
        Elt* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            new (p) Elt();
        return;
    }
    Elt tmp;
    Insert(mpEnd, &tmp);
}
// --- equivalence checker address annotations
    void EaDelete(...); // 0x00f47380
    extern int g_s1; // 0x016f9fdc
    extern int g_s2; // 0x016f9fe4
    extern int g_s3; // 0x016fa018
    extern int g_s4; // 0x016fa014
    extern int g_s5; // 0x016fa01c

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
