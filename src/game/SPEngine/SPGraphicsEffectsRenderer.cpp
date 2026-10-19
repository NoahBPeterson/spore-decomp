// src/game/SPEngine/SPGraphicsEffectsRenderer.cpp -- migrated from slice(s) s006f1770, s006f0890, s006ef990, s006ee1f0, s006ed2c0, s006ea030, s006e80d0, s006e7110, s006e6100 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsEffectsRenderer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_0067dd50();
#include <math.h>
#include <algorithm>
#include <string.h>
#include <intrin.h>
#include "SP/cEffectsRenderer.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cViewer.h"
#include "rw/graphics/GlobalState.h"
#include <new>

// ---- items of slice s006e6100 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Inner {
    void F2(int, float);            // 0x006f40b0
    void F1(float);                 // 0x006f3f00
    void F3(int, float, int);       // 0x006f4a10
};
class ShaderHost {
public:
    uint32_t pad[0x100];            // 0x400-byte object

    char HandleMessage2(int msg, int extra);                  // 0x006e6810
    void CallF2(int a, float b);                              // 0x006e69a0
    void CallF1(float b);                                     // 0x006e6930
    void CallF3(int a, float b, int c);                       // 0x006e6970
    void SetMode(int mode);                                   // 0x006e69e0
    int  ComputeSize(int a, int b, int c);                    // 0x006e6a20
    int  ResetCounter();                                      // 0x006e6b40
    void SetParams(int a, int b, char c1, char c2, char c3);  // 0x006e6b70
    void CallIface(int v);                                    // 0x006e6c20
    bool IsDone();                                            // 0x006e6c60
    void TailVirtual();                                       // 0x006e6c80
    char Write(void* stream);                                 // 0x006e6100
};
struct Manager {
    void* vtbl;
};
typedef int(__thiscall* VirtualFn1)(void*, int);
typedef void(__thiscall* VirtualFn3)(void*, int, int, int);
// ---- items of slice s006e6100 end

// ---- items of slice s006e7110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_matName7cc0[];
struct Inner7c {
    char F7(int, int, int, int, int, int, int);       // 0x0076bc50
    void F12(int, int, int, int, int, int, int, int, // 0x0076ba30
             int, int, int, int);
    void FF(float);                                   // 0x00776450
    void FI(int);                                     // 0x006f4280 / 0x0076cd30
    int  Fp(int, int);                                // 0x... vtable +0x10
    void Fq(int, int, float);                         // vtable +0x18/+0x1c
};
class Host3 {
public:
    uint32_t pad[0x120];

    void Method7110(int);                                    // 0x006e7110
    __declspec(noinline) void Method7270(void*, void*);      // 0x006e7270
    void DispatchList(unsigned char* list, int arg);         // 0x006e73d0
    char Method7450(unsigned char flags);                    // 0x006e7450
    void Method7880(int arg);                                // 0x006e7880
    void Method78b0(void* a, void* b, int c);                // 0x006e78b0
    void Method79b0(int, int, int, int, int, int, int, int,
                    int, int, float, float);                 // 0x006e79b0
    void SetFlag(int index, unsigned char v);                // 0x006e7aa0
    void Method7ac0(void* arg);                              // 0x006e7ac0
    void Method7b50(void* arg);                              // 0x006e7b50
    char Method7c60();                                       // 0x006e7c60
    char Method7c80(int, int, int, int, int, int);           // 0x006e7c80
    void Method7cc0(int, int, int, int);                     // 0x006e7cc0
    void Method7d00(float);                                  // 0x006e7d00
    void Method7d40(int, uint32_t*, float);                 // 0x006e7d40
    void Method7da0();                                       // 0x006e7da0
    void Method7dd0(int, float*, float);                     // 0x006e7dd0
    void Method7ed0(int, uint32_t*, float);                 // 0x006e7ed0
    void Method7f30();                                       // 0x006e7f30
    int  Method7fa0(int index, int value);                   // 0x006e7fa0
    void Method8000(int index, float* v, float w);           // 0x006e8000
    void Method8090(int index, int a, float b);              // 0x006e8090
};
typedef int(__thiscall* VGet)(void*, int, int);
typedef void(__thiscall* VSet)(void*, int, float*, float);
typedef void(__thiscall* VSet2)(void*, int, int, float);
// ---- items of slice s006e7110 end

// ---- items of slice s006e80d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  f67dd50();
extern void*  f67dd70();   // SP::MaterialManager
extern void   f76d5c0();
extern void   f76d6e0();
extern void*  g15d0838;    // default camera raster
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned long long u64;
struct Ext {
    void* r6f2050(int, int);
    char  r6f4170();
    void* r6f41e0(int);
    void* r6f3fe0();
    void  r6f3ee0(int);
    void* r6f3f20(int);
    float r6f3ff0(int);
    float r6f4010(int);
    float r6f4000(int);
    void  r6f4190(void*);
    void  r6f3fb0(int);
    void  r7c4010(void*);
    void  r7c4ad0(float, float);
    void  r7c4ba0(float);
    void  r7c4bc0(float);
    void  r7c4be0(void*, int);
    void  r7c3c50(int);
    void  r7c3cb0(void*);
    void  r7a4420(int, int, int, int);
    int   r7a47c0(int, int, int);
    char  r7a4910(int, int, int, int, int);
    void  r7a4650();
    void* r776420(float, float);
    void  r776440();
    void  r7764a0();
    void  r7764c0(int, int, float, float);
    void  r776520(int, int, float, float);
    void  r776a60(int, void*, void*);
    char  r7773c0(unsigned char, int, int, int);
    char  r7775a0(unsigned char, int, int, int);
};
#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]
struct CCreature {
    char m_unk[0x9c0];
    // 0x006e80d0
    void m80d0(int idx, int a, int b);
    // 0x006e8160
    void m8160(float a, float b);
    // 0x006e8200
    char m8200(char* p, int a);
    // 0x006e82b0
    void m82b0(int a, int b, float c, float d);
    // 0x006e8360
    void m8360(int a);
    // 0x006e83e0
    void m83e0(int a, int* out1, int* out2);
    // 0x006e8420
    void m8420(int a, void* b);
    // 0x006e8480
    void m8480(void* b);
    // 0x006e8810
    void m8810(uint* flags, void** p3, uint* p4);
    // 0x006e8d70 / 0x006e8dd0 forwarders
    void m8d70(int, int, void*, int, int, int, int, int, int, int);
    void m8dd0(int, int, int, int, void*, int, int, int, int, int, int, int, int);
    // 0x006e8e40
    void m8e40(int a, int b);
    // 0x006e8ee0
    int  m8ee0(int a, int b, int c);
    // 0x006e8f20
    char m8f20(int a, int b, int c, int d, int e);
    // 0x006e8f60
    u64  m8f60(int a);
};
// ---- items of slice s006e80d0 end

// ---- items of slice s006ea030 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g1533c74;
typedef unsigned char  uchar;
struct E6 {
    void  r537dc0(void*);     // cSPTransform::operator=
    void  r6e6ee0(void*, int, float, int);
    void  r7c4fd0_dummy();
};
struct R70 {
    char m[0x70];
    R70* mabc0(const R70& src);   // 0x6eabc0 copy ctor
    R70* mac80(const R70& src);   // 0x6eac80 assign
};
struct S6 {
    char m_unk[0x380];

    // 0x6ea030 render pass A
    void m030(int a, int b, int c);
    // 0x6ea470 render pass B
    void m470(int a, uint flags, int c);
    // 0x6ea920 EH dtor
    void m920();
    // 0x6ea9e0 setter
    void m9e0(int idx, float* box, float pad);
    // 0x6ead40 transform setter
    void mad40(int idx, void* xf);
};
// ---- items of slice s006ea030 end

// ---- items of slice s006ed2c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted {
    virtual void AddRef() = 0;   // vtable +0
    virtual void Release() = 0;  // vtable +4
};
template<class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Release() { T* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
    AutoRefCount& operator=(T* p) { if (mpObject) { T* old = mpObject; mpObject = p; old->Release(); } else mpObject = p; return *this; }
};
template<class T>
struct evec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    char mAllocator[4];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned n) { return *(mpBegin + n); }
    void push_back(const T& v);
    void erase(T* first, T* last);
};
struct cTextureParticleSet {
    char pad0[0x48];
    bool mActive;        // +0x48
    bool mInActiveList;  // +0x49
    char pad1[0x70 - 0x4a];
};
struct cModelParticleSet {
    char pad0[0x50];
    bool mActive;            // +0x50
    char pad1[0x5c - 0x51];
    void* mpField5c;         // +0x5c
    IRefCounted* mpField60;  // +0x60
    int mField64;            // +0x64
    char pad2[0x68 - 0x68];
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
};
struct DispatchData { void* p0; void* p1; void* p2; };
class cEffectsModel {
public:
    void* mpVtable;                          // +0x00
    char padV[4];                            // +0x04
    evec<DispatchData> mDispatchData;        // +0x08
    char pad0[0x50 - 0x18];
    Vector3 mBoxMin;                         // +0x50
    Vector3 mBoxMax;                         // +0x5c
    float   mBoundingRadius;                 // +0x68
    AutoRefCount<IRefCounted> mAsyncRequest; // +0x6c
    evec<AutoRefCount<IRefCounted> > mResourceRefs;  // +0x70

    cEffectsModel(unsigned, unsigned, unsigned, const float*);   // 6ed8d0
    void AddResourceRef(IRefCounted* p);                         // 6edaa0
    void Reset();                                                // 6edb10
    void UpdateFromResource(int* res);                           // 6edbc0
    char Update();                                               // 6ee140
};
class cEffectsRenderer {
public:
    char pad0[0x174];
    evec<cTextureParticleSet> mTextureParticleSets;    // +0x174
    char pad1[4];                                       // +0x184
    evec<unsigned short> mActiveTextureParticleSets;   // +0x188
    char pad2[0x1b8 - 0x198];
    cModelParticleSet* mModelBegin;      // +0x1b8
    cModelParticleSet* mModelEnd;        // +0x1bc
    evec<int> mFreeIDs;                  // +0x1cc
    IRefCounted* mSys1e0;                // +0x1e0

    void SetTextureParticleActive(int index, bool active);   // 6ed2c0
    void RemoveParticleSet(int index);                       // 6ed340
    int  ActivateByKey(unsigned int a, unsigned int b);      // 6ed440
};
// ---- items of slice s006ed2c0 end

// ---- items of slice s006ef990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00762a60(void* p);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* CreateTestModel();
extern "C" void* FUN_007c3af0(const char* s);
extern "C" void* FUN_00762b70(void* p, int a, int b, int c);
struct Dispatch3 { void* p0; void* p1; void* p2; };   // 0xc
struct cEffectsModelR {
    void** mpVtable;      // +0x00
    int    mnRefCount;    // +0x04
    Dispatch3* mpBegin;   // +0x08
    Dispatch3* mpEnd;     // +0x0c

    void Reset();         // 6edb10
};
struct cEffectsModel2;
class cEffectsRendererSystem {
public:
    char pad0[4];
    cEffectsModel2* mpModel;        // +0x04
    char pad1[0x30d50 - 0x08];
    void* mAt30d50;                 // +0x30d50
    void* mAt30d54;                 // +0x30d54  (vector begin)
    void* mAt30d58;                 // +0x30d58  (vector end)
    char pad2[0x30d68 - 0x30d5c];
    void* mAt30d68;                 // +0x30d68
    void* mAt30d6c;                 // +0x30d6c
    char pad3[0x30d7c - 0x30d70];
    void* mAt30d7c;                 // +0x30d7c
    void* mAt30d80;                 // +0x30d80
    int   mAt30d84;                 // +0x30d84

    bool Init();                    // 6ef9e0
    char Shutdown();                // 6efa90
private:
    void* SetDeviceState();
    void* GetImageResource(void*);
    void  FUNecf10(int);
};
struct cERSDtor;
extern cERSDtor* g_pEffectsRendererSystem;   // DAT_01618d10
void* CreateMesh(int n);           // SP::CreateMesh
struct MeshStub {
    void FUN96e0(int);
    void FUN9670(int, void*);
};
struct cEffectsModel2 {
    void** mpVtable;    // +0
    int    mnRefCount;  // +4
};
struct cERSDtor { void Shutdown(); ~cERSDtor(); };
// ---- items of slice s006ef990 end

// ---- items of slice s006f0890 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl MoveShorts(void* dst, const void* src, unsigned n);  // 0x011e0744
extern unsigned g_softStateDirty;     // 0x016f9528
extern unsigned g_samplerA;           // 0x016f9530
extern unsigned g_samplerB;           // 0x016f9534
extern unsigned g_renderDirty;        // 0x016fa38c
extern unsigned g_renderDirty2;       // 0x016fa39c
extern int g_s0;  // 0x016f9fe0
    extern int g_s1; // 0x016f9fdc
    extern int g_s2; // 0x016f9fe4
    extern int g_s3; // 0x016fa018
    extern int g_s4; // 0x016fa014
    extern int g_s5; // 0x016fa01c
extern int g_s6;  // 0x016f9238
extern int g_fogType;                 // 0x016f9f7c
extern int g_r250, g_r410;            // 0x016f9250, 0x016f9410
extern int g_b218;  // 0x016f9218
extern int g_b23c;  // 0x016f923c
extern int g_b21c;  // 0x016f921c
extern int g_b244;  // 0x016f9244
extern int g_b240;  // 0x016f9240
void __cdecl EaDelete(void* p);  // 0x00f47380
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
    void EaDelete(...); // 0x00f47380
// ---- items of slice s006f0890 end

// @ 0x006e6840
void __stdcall GetLayout(int type, unsigned char* out)
{
    switch (type) {
    case 0:
    case 6:
    case 7:
    case 8:
        out[1] = 0x0c; out[2] = 0x10; out[0] = 0; break;
    case 2:
    case 3:
        out[1] = 0x10; out[2] = 0x20; out[3] = 0x24; out[0] = 0; break;
    case 4:
        out[1] = 0x10; out[2] = 0x20; out[3] = 0x2c; out[4] = 0x30; out[0] = 0; break;
    case 5:
        out[1] = 0x0c; out[0] = 0; break;
    case 9:
        out[1] = 0x40; out[0] = 0; break;
    default:
        break;
    }
}









// @ 0x006e68e0
int __stdcall FindKnownValue(int* p)
{
    for (;;) {
        switch (*p) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0x20:
            return *p;
        default:
            ++p;
            break;
        }
    }
}









// @ 0x006e6930
void ShaderHost::CallF1(float b)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F1(b);
    }
}









// @ 0x006e6970
void ShaderHost::CallF3(int a, float b, int c)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F3(a, b, c);
    }
}









// @ 0x006e69a0
void ShaderHost::CallF2(int a, float b)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F2(a, b);
    }
}









// @ 0x006e69e0
void ShaderHost::SetMode(int mode)
{
    Manager* m = (Manager*)FUN_0067dd50();
    if (mode != 6 && mode != 5) {
        VirtualFn1 fn = (VirtualFn1)((void**)m->vtbl)[0x58 / 4];
        if (fn(m, 0x16) != 0) {
            *(char*)((char*)this + 0x368) = (char)mode;
        }
    }
}









// @ 0x006e6b70
void ShaderHost::SetParams(int a, int b, char c1, char c2, char c3)
{
    *(int*)((char*)this + 0x1f8) = a;
    *(char*)((char*)this + 0x1f4) = 1;
    *(int*)((char*)this + 0x1fc) = b;
    *(int*)((char*)this + 0x200) = 0;
    if (c1 != 0) {
        *(int*)((char*)this + 0x200) = 1;
    }
    if (c2 != 0) {
        *(int*)((char*)this + 0x200) = *(int*)((char*)this + 0x200) | 2;
    }
    if (c3 != 0) {
        *(int*)((char*)this + 0x200) = *(int*)((char*)this + 0x200) | 4;
    }
}









// @ 0x006e6c20
void ShaderHost::CallIface(int v)
{
    Manager* o = *(Manager**)((char*)this + 0x25c);
    VirtualFn3 fn = (VirtualFn3)((void**)o->vtbl)[0xa8 / 4];
    fn(o, 0, v, 0);
}









// @ 0x006e6ca0
void SortPairsA(uint32_t* begin, uint32_t* end)
{
    uint32_t* p = begin;
    if (p != end) {
        while ((p = p + 2) != end) {
            uint32_t v1 = *p;
            uint32_t v2 = p[1];
            uint32_t* q = p;
            while (q != begin && q[-2] < v1) {
                *q = q[-2];
                q[1] = q[-1];
                q -= 2;
            }
            *q = v1;
            q[1] = v2;
        }
    }
}









// @ 0x006e6cf0
void SortPairsB(uint32_t* begin, uint32_t* end)
{
    for (uint32_t* p = begin; p != end; p += 2) {
        uint32_t v1 = *p;
        uint32_t v2 = p[1];
        uint32_t* q = p;
        uint32_t prev = q[-2];
        while (prev < v1) {
            *q = q[-2];
            q[1] = q[-1];
            q -= 2;
            prev = *q;
        }
        *q = v1;
        q[1] = v2;
    }
}









// @ 0x006e7450
char Host3::Method7450(unsigned char)
{
    return 0;
}








// @ 0x006e7880
void Host3::Method7880(int arg)
{
    Inner7c* a = *(Inner7c**)((char*)this + 0x35c);
    if (a != 0) {
        a->FI(arg);
    }
    Inner7c* b = *(Inner7c**)((char*)this + 0x24);
    if (b != 0) {
        b->FI(arg);
    }
}








// @ 0x006e7b50
void Host3::Method7b50(void*)
{
}








// @ 0x006e7c60
char Host3::Method7c60()
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        return p->F7(0, 0, 0, 0, 0, 0, 1);
    }
    return 0;
}








// @ 0x006e7c80
char Host3::Method7c80(int a, int b, int c, int d, int e, int f)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        return p->F7(a, b, c, d, e, f, 1);
    }
    return 0;
}








// @ 0x006e7cc0
void Host3::Method7cc0(int a, int b, int c, int d)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        p->F12(a, b, c, d, 0, 0, 0, (int)g_matName7cc0, 0, 0, 0, 0);
    }
}








// @ 0x006e7d00
void Host3::Method7d00(float v)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x360);
    if (p != 0) {
        p->FF(v);
    }
}








// @ 0x006e7d40
void Host3::Method7d40(int index, uint32_t* v, float w)
{
    if (index >= 0) {
        if (index < (*(int*)((char*)this + 0x4c) - *(int*)((char*)this + 0x48)) / 0x70) {
            char* e = (char*)(*(int*)((char*)this + 0x48) + index * 0x70);
            *(uint32_t*)(e + 0x4c) = v[0];
            *(uint32_t*)(e + 0x50) = v[1];
            *(uint32_t*)(e + 0x54) = v[2];
            *(float*)(e + 0x58) = w;
        }
    }
}








// @ 0x006e7dd0
void Host3::Method7dd0(int, float*, float)
{
}








// @ 0x006e7ed0
void Host3::Method7ed0(int index, uint32_t* v, float w)
{
    if (index >= 0) {
        if (index < (*(int*)((char*)this + 0x178) - *(int*)((char*)this + 0x174)) / 0x70) {
            char* e = (char*)(*(int*)((char*)this + 0x174) + index * 0x70);
            *(uint32_t*)(e + 0x4c) = v[0];
            *(uint32_t*)(e + 0x50) = v[1];
            *(uint32_t*)(e + 0x54) = v[2];
            *(float*)(e + 0x58) = w;
        }
    }
}








// @ 0x006e7f30
void Host3::Method7f30()
{
}








// @ 0x006e7fa0
int Host3::Method7fa0(int index, int value)
{
    char* e = (char*)(*(int*)((char*)this + 0x1b8) + index * 0x68);
    void* p = *(void**)(e + 0x60);
    if (p != 0) {
        VGet fn = (VGet)((void**)(*(void**)p))[0x10 / 4];
        return fn(p, index, value);
    }
    if (index >= 0) {
        int count = (*(int*)((char*)this + 0x1bc) - *(int*)((char*)this + 0x1b8)) / 0x68;
        if (index < count) {
            *(char*)(e + 0x50) = (char)value;
        }
    }
    return (int)this;
}








// @ 0x006e8000
void Host3::Method8000(int index, float* v, float w)
{
    char* e = (char*)(*(int*)((char*)this + 0x1b8) + index * 0x68);
    void* p = *(void**)(e + 0x60);
    if (p != 0) {
        VSet fn = (VSet)((void**)(*(void**)p))[0x18 / 4];
        fn(p, index, v, w);
        return;
    }
    if (index >= 0) {
        int count = (*(int*)((char*)this + 0x1bc) - *(int*)((char*)this + 0x1b8)) / 0x68;
        if (index < count) {
            *(float*)(e + 4) = v[0];
            *(float*)(e + 8) = v[1];
            *(float*)(e + 0xc) = v[2];
            *(float*)((char*)(*(int*)((char*)this + 0x1b8) + index * 0x68) + 0x10) = w;
        }
    }
}








// @ 0x006e8090
void Host3::Method8090(int index, int a, float b)
{
    void* p = *(void**)(*(int*)((char*)this + 0x1b8) + index * 0x68 + 0x60);
    if (p != 0) {
        VSet2 fn = (VSet2)((void**)(*(void**)p))[0x1c / 4];
        fn(p, index, a, b);
    }
}








// @ 0x006e80d0
void CCreature::m80d0(int idx, int a, int b)
{
    char* self = (char*)this;
    int off = idx * 0x68;
    void* e = *(void**)(self + 0x1b8);
    void* p = *(void**)((char*)e + off + 0x60);
    if (p) {
        ((void(__thiscall*)(void*, int, int, int))VFN(p, 0x20))(p, idx, a, b);
        return;
    }
    void* r = ((Ext*)(*(void**)(self + 0x40)))->r6f2050(a, b);
    if (r) {
        *(uint*)((char*)*(void**)(self + 0x1b8) + off + 0x54) = *(uint*)r;
        *(uint*)((char*)*(void**)(self + 0x1b8) + off + 0x58) = *(uint*)((char*)r + 4);
        return;
    }
    void* mm = f67dd70();
    void* base = (char*)*(void**)(self + 0x1b8) + off;
    int v = ((int(__thiscall*)(void*, int))VFN(mm, 0x28))(mm, a);
    *(uint*)((char*)base + 0x54) = (uint)v;
}







// @ 0x006e8160
void CCreature::m8160(float a, float b)
{
    if (*(void**)((char*)this + 0x20) == 0)
        return;
    int rect[4];
    ((Ext*)(*(void**)((char*)this + 0x20)))->r7c4010(rect);
    float x = a / (float)(rect[2] - rect[0]);
    float y = b / (float)(rect[3] - rect[1]);
    ((Ext*)(*(void**)((char*)this + 0x20)))->r7c4ad0(x, y);
    if (*(void**)((char*)this + 0x360))
        ((Ext*)(*(void**)((char*)this + 0x360)))->r776420(-x, -y);
}







// @ 0x006e8200
char CCreature::m8200(char* p, int a)
{
    char* self = (char*)this;
    if (*(char*)(self + 0x368)) {
        void* m = f67dd50();
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x60))(m, 0x16, 2);
        *(char*)(self + 0x368) = 0;
    }
    if (*p == '\n') {
        void* q = *(void**)(self + 0x35c);
        if (q)
            return (char)((int(__thiscall*)(void*, void*, int, ushort))VFN(q, 0x18))(
                q, *(void**)(p + 0x10), a, *(ushort*)(p + 2));
        return 0;
    }
    void* h = *(void**)(self + 0x360);
    if (h && ((Ext*)h)->r7773c0((unsigned char)*p, *(int*)(p + 8), *(int*)(p + 0xc), a))
        return 1;
    void* h2 = *(void**)(self + 0x364);
    if (h2 && ((Ext*)h2)->r7775a0((unsigned char)*p, *(int*)(p + 8), *(int*)(p + 0xc), a))
        return 1;
    return 0;
}







// @ 0x006e82b0
void CCreature::m82b0(int a, int b, float c, float d)
{
    if (a >= 0xc) {
        if (*(void**)((char*)this + 0x35c) == 0)
            return;
        ((void(__thiscall*)(void*, int, int, float, float))VFN(
            *(void**)((char*)this + 0x35c), 0x1c))(
            *(void**)((char*)this + 0x35c), a, b, c, d);
        return;
    }
    if (a < 1)
        return;
    {
        void* h = *(void**)((char*)this + 0x360);
        int t = a - 1;
        if (h && (t == 5 || t == 4)) {
            ((Ext*)h)->r7764c0(a, b, c, d);
            return;
        }
    }
    {
        void* h2 = *(void**)((char*)this + 0x364);
        if (h2)
            ((Ext*)h2)->r776520(a, b, c, d);
    }
}







// @ 0x006e8360
void CCreature::m8360(int a)
{
    char* self = (char*)this;
    void* r = *(void**)(self + 0x35c);
    if (r && a >= 0xc) {
        ((void(__thiscall*)(void*, int))VFN(r, 0x20))(r, a);
        ((Ext*)(*(void**)(self + 0x20)))->r7c3cb0(g15d0838);
        goto done;
    }
    if (a < 1)
        goto done;
    {
        void* h = *(void**)(self + 0x360);
        int t = a - 1;
        if (h && (t == 5 || t == 4)) {
            ((Ext*)h)->r776440();
        } else {
            void* h2 = *(void**)(self + 0x364);
            if (h2)
                ((Ext*)h2)->r7764a0();
        }
    }
done:
    {
        void* m = f67dd50();
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x60))(m, 0x16, 2);
        *(char*)(self + 0x368) = 0;
    }
}







// @ 0x006e8420
void CCreature::m8420(int a, void* b)
{
    char* self = (char*)this;
    void* old = *(void**)(self + 0x28);
    if (b != old) {
        if (b)
            ((void(__thiscall*)(void*))VFN(b, 0x8))(b);
        *(void**)(self + 0x28) = b;
        if (old)
            ((void(__thiscall*)(void*))VFN(old, 0xc))(old);
    }
    if (a != 0) {
        *(void**)(self + 0x20) = (void*)a;
    } else {
        void* q = *(void**)(self + 0x28);
        *(void**)(self + 0x20) = (void*)((int(__thiscall*)(void*))VFN(q, 0x1c))(q);
    }
    if (*(void**)(self + 0x35c))
        ((Ext*)(*(void**)(self + 0x35c)))->r6f3ee0(a);
}







// @ 0x006e8480
void CCreature::m8480(void* b)
{
    char* self = (char*)this;
    if (*(void**)(self + 0x1e0) == b)
        return;
    if (*(void**)(self + 0x1e0) != 0) {
        int n = (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70;
        if (n > 0) {
            char* p = *(char**)(self + 0x48);
            for (int i = 0; i < n; i++, p += 0x70) {
                void* v = *(void**)(p + 0x68);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    *(void**)(p + 0x68) = 0;
                }
            }
        }
        n = (*(int*)(self + 0x178) - *(int*)(self + 0x174)) / 0x70;
        if (n > 0) {
            char* p = *(char**)(self + 0x174);
            for (int i = 0; i < n; i++, p += 0x70) {
                void* v = *(void**)(p + 0x64);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    *(void**)(p + 0x64) = 0;
                }
            }
        }
        n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                char* base = *(char**)(self + 0x1b8);
                void* v = *(void**)(base + i * 0x68 + 0x5c);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    base = *(char**)(self + 0x1b8);
                    *(void**)(base + i * 0x68 + 0x5c) = 0;
                }
            }
        }
    }
    {
        void* old = *(void**)(self + 0x1e0);
        if (b != old) {
            if (b)
                ((void(__thiscall*)(void*))VFN(b, 0x0))(b);
            *(void**)(self + 0x1e0) = b;
            if (old)
                ((void(__thiscall*)(void*))VFN(old, 0x4))(old);
        }
    }
    if (*(void**)(self + 0x1e0) != 0) {
        int n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
        for (int i = 0; i < n; i++) {
            int idx = *(ushort*)(*(int*)(self + 0x5c) + i * 2);
            char* e = *(char**)(self + 0x48) + idx * 0x70;
            if (*(char*)(e + 0x48)) {
                float c[3];
                c[0] = (*(float*)(e + 0x30) + *(float*)(e + 0x3c)) * 0.5f;
                c[1] = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * 0.5f;
                c[2] = (*(float*)(e + 0x44) + *(float*)(e + 0x38)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x68) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
        n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
        for (int i = 0; i < n; i++) {
            int idx = *(ushort*)(*(int*)(self + 0x188) + i * 2);
            char* e = *(char**)(self + 0x174) + idx * 0x70;
            if (*(char*)(e + 0x48)) {
                float c[3];
                c[0] = (*(float*)(e + 0x2c) + *(float*)(e + 0x38)) * 0.5f;
                c[1] = (*(float*)(e + 0x3c) + *(float*)(e + 0x30)) * 0.5f;
                c[2] = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x64) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
        n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
        for (int i = 0; i < n; i++) {
            char* base = *(char**)(self + 0x1b8);
            char* e = base + i * 0x68;
            if (*(char*)(e + 0x50) && *(void**)e != 0) {
                void* v = *(void**)e;
                float c[3];
                c[0] = (*(float*)((char*)v + 0x5c) + *(float*)((char*)v + 0x50)) * 0.5f;
                c[1] = (*(float*)((char*)v + 0x60) + *(float*)((char*)v + 0x54)) * 0.5f;
                c[2] = (*(float*)((char*)v + 0x64) + *(float*)((char*)v + 0x58)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x5c) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
    }
}







// @ 0x006e8d70
void CCreature::m8d70(int a2, int a3, void* a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7; (void)a8; (void)a9; (void)a10; (void)a11;
    void* o = *(void**)((char*)this + 0x24);
    if (o)
        f76d5c0();
}







// @ 0x006e8dd0
void CCreature::m8dd0(int, int, int, int, void*, int, int, int, int, int, int, int, int)
{
    void* o = *(void**)((char*)this + 0x24);
    if (o)
        f76d6e0();
}







// @ 0x006ea920
void S6::m920()
{
    char* self = (char*)this;
    void* p = *(void**)(self + 0x6c);
    if (p)
        ((void(__thiscall*)(void*))VFN(p, 8))(p);
    void* q = *(void**)(self + 0x2c);
    if (q) {
        int* rc = (int*)((char*)q + 8);
        if (--(*rc) < 1)
            (*rc)++;
    }
    void* r = *(void**)(self + 0x28);
    if (r) {
        int* rc = (int*)((char*)r + 8);
        if (--(*rc) < 1)
            (*rc)++;
    }
}






// @ 0x006ea9e0
void S6::m9e0(int idx, float* box, float pad)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70)
        return;
    int e = idx * 0x70 + *(int*)(self + 0x48);
    *(float*)(e + 0x3c) = box[3];
    *(float*)(e + 0x40) = box[4];
    *(float*)(e + 0x44) = box[5];
    *(float*)(e + 0x30) = box[0];
    *(float*)(e + 0x34) = box[1];
    *(float*)(e + 0x38) = box[2];
    float f = *(float*)(e + 0x30);
    pad = pad * 0.5f;
    if (f != g1533c74 && f != -g1533c74) {
        *(float*)(e + 0x30) = f - pad;
        *(float*)(e + 0x34) = *(float*)(e + 0x34) - pad;
        *(float*)(e + 0x38) = *(float*)(e + 0x38) - pad;
        *(float*)(e + 0x3c) = pad + *(float*)(e + 0x3c);
        *(float*)(e + 0x40) = pad + *(float*)(e + 0x40);
        *(float*)(e + 0x44) = pad + *(float*)(e + 0x44);
    }
    void* h = *(void**)(self + 0x1e0);
    if (h) {
        float c[3];
        if (*box == g1533c74) {
            c[0] = *(float*)0x1618de0;
            c[1] = *(float*)0x1618de4;
            c[2] = *(float*)0x1618de8;
        } else {
            c[0] = (*box + box[3]) * 0.5f;
            c[1] = (box[4] + box[1]) * 0.5f;
            c[2] = (box[5] + box[2]) * 0.5f;
        }
        if (*(int*)(e + 0x68) == 0)
            *(int*)(e + 0x68) =
                ((int(__thiscall*)(void*, float, float*))VFN(h, 0x18))(h, 1.0f, c);
        else
            ((void(__thiscall*)(void*, float, float*, int))VFN(h, 0x1c))(
                h, 1.0f, c, *(int*)(e + 0x68));
    }
    void* vl = *(void**)(e + 0x6c);
    if (vl) {
        *(void**)(e + 0x6c) = 0;
        ((void(__thiscall*)(void*))VFN(vl, 8))(vl);
    }
}






// @ 0x006eabc0
R70* R70::mabc0(const R70& src)
{
    char* d = (char*)this;
    char* s = (char*)&src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    void* n = *(void**)(s + 0x28);
    void* o = *(void**)(d + 0x28);
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 4))++;
        *(void**)(d + 0x28) = n;
        if (o) {
            int v = (*(volatile int*)((char*)o + 4) += -1);
            if (v == 0) {
                *(int*)((char*)o + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(o, 0))(o, 1);
            }
        }
    }
    *(uint*)(d + 0x38) = *(uint*)(s + 0x38);
    *(uint*)(d + 0x3c) = *(uint*)(s + 0x3c);
    *(uint*)(d + 0x40) = *(uint*)(s + 0x40);
    *(uint*)(d + 0x2c) = *(uint*)(s + 0x2c);
    *(uint*)(d + 0x30) = *(uint*)(s + 0x30);
    *(uint*)(d + 0x34) = *(uint*)(s + 0x34);
    *(float*)(d + 0x44) = *(float*)(s + 0x44);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
    return this;
}






// @ 0x006ead40
void S6::mad40(int idx, void* xf)
{
    char* self = (char*)this;
    int e = idx * 0x68 + *(int*)(self + 0x1b8);
    void* o = *(void**)(e + 0x60);
    if (o) {
        ((void(__thiscall*)(void*, int, void*))VFN(o, 0x14))(o, idx, xf);
        return;
    }
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68)
        return;
    ((E6*)(e + 0x18))->r537dc0(xf);
    float a = *(float*)(e + 0x14);
    float b = *(float*)(e + 0x28);
    *(ushort*)(e + 0x18) |= 1;
    *(ushort*)(e + 0x1a) = *(ushort*)(e + 0x1a) + 1;
    *(float*)(e + 0x28) = a * b;
    void* h = *(void**)(self + 0x1e0);
    if (h) {
        float c[3];
        c[0] = *(float*)((char*)xf + 4);
        c[1] = *(float*)((char*)xf + 8);
        c[2] = *(float*)((char*)xf + 0xc);
        if (*(int*)(e + 0x5c) == 0)
            *(int*)(e + 0x5c) =
                ((int(__thiscall*)(void*, float, float*))VFN(h, 0x18))(h, 1.0f, c);
        else
            ((void(__thiscall*)(void*, float, float*, int))VFN(h, 0x1c))(
                h, 1.0f, c, *(int*)(e + 0x5c));
    }
}






// @ 0x006ed2c0
void cEffectsRenderer::SetTextureParticleActive(int index, bool active)
{
    if (index < 0 || index >= (int)mTextureParticleSets.size())
        return;
    cTextureParticleSet& p = mTextureParticleSets[index];
    if (p.mActive == active)
        return;
    p.mActive = active;
    if (!active)
        return;
    if (p.mInActiveList)
        return;
    mActiveTextureParticleSets.push_back((unsigned short)index);
    p.mInActiveList = 1;
}





// @ 0x006ed340
void cEffectsRenderer::RemoveParticleSet(int index)
{
    if (index < 0)
        return;
    if (index >= (mModelEnd - mModelBegin) / 0x68)
        return;
    cModelParticleSet* p = mModelBegin + index;
    if (p->mpField60 == 0) {
        if (*(unsigned int*)p->pad0 != 0) {
            *(unsigned int*)p->pad0 = 0;
            p->mActive = false;
            if (p->mpField5c != 0) {
                if (mSys1e0 != 0)
                    mSys1e0->AddRef();
                p->mpField5c = 0;
            }
            mFreeIDs.push_back(index);
        }
        return;
    }
    p->mpField60->Release();
    p->mpField60 = 0;
    p->mField64 = -1;
    mFreeIDs.push_back(index);
}





// @ 0x006ed8d0
cEffectsModel::cEffectsModel(unsigned, unsigned, unsigned, const float* box)
{
    mpVtable = 0;
    mAsyncRequest = (IRefCounted*)0;
    mBoundingRadius = 0.0f;
    if (box) {
        mBoxMin = Vector3(box[0], box[1], box[2]);
        mBoxMax = Vector3(box[3], box[4], box[5]);
    }
}





// @ 0x006eeb60
void vector_insert_stub(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
}




// @ 0x006ef990
void Release(cEffectsModelR* self)
{
    Dispatch3* it = self->mpBegin;
    Dispatch3* end = self->mpEnd;
    for (; it != end; ++it)
        FUN_00762a60(it->p0);
    self->Reset();
    int n = self->mnRefCount - 1;
    self->mnRefCount = self->mnRefCount - 1;
    if (n == 0) {
        self->mnRefCount = 1;
        _ReadWriteBarrier();
        ((void (__thiscall*)(void*, int))self->mpVtable[0])(self, 1);
    }
}



// @ 0x006ef9e0
bool cEffectsRendererSystem::Init()
{    GetImageResource(SetDeviceState());
    cEffectsModel2* m = (cEffectsModel2*)CreateTestModel();
    cEffectsModel2* old = mpModel;
    if (m != old) {
        if (m)
            m->mnRefCount++;
        mpModel = m;
        if (old) {
            int n = old->mnRefCount - 1;
            old->mnRefCount = old->mnRefCount - 1;
            if (n == 0) {
                old->mnRefCount = 1;
                _ReadWriteBarrier();
                ((void (__thiscall*)(void*, int))old->mpVtable[0])(old, 1);
            }
        }
    }
    mAt30d50 = FUN_007c3af0("T0FT4FT4FT4FT4B");
    mAt30d80 = FUN_00762b70(mAt30d50, 0x9c4, 9, 0);
    mAt30d7c = CreateMesh(3);
    ((MeshStub*)mAt30d7c)->FUN96e0(0);
    ((MeshStub*)mAt30d7c)->FUN9670(1, mAt30d80);
    FUNecf10(1);
    mAt30d84 = 0;
    return true;
}



// @ 0x006efa90
char cEffectsRendererSystem::Shutdown()
{
    return 1;
}



// @ 0x006efb90
void CreateEffectsRendererSystem()
{
}



// @ 0x006efc10
void DestroyEffectsRendererSystem()
{
    g_pEffectsRendererSystem->Shutdown();
    cERSDtor* p = g_pEffectsRendererSystem;
    if (p) {
        p->~cERSDtor();
        EASTL_allocator_deallocate(p);
    }
    g_pEffectsRendererSystem = 0;
}



// @ 0x006efc70
void RenderSomething(int)
{
}



// @ 0x006efe90
void RenderTextureParticlesStub()
{
}



// @ 0x006f0320
void EffectsHelper320(int)
{
}



// @ 0x006f05a0
void EffectsHelper5a0(int)
{
}



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


// @ 0x006f1770
bool AddParticleSet(int a, int b, int c, int d)
{ (void)a; (void)b; (void)c; (void)d; return true; }
