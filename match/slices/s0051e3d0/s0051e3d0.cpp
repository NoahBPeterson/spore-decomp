// Slice 6: nSPSkinner PaintSystem destructor plus DeviceRestore and cPaintSystem::Shutdown.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void DefaultRefCounted_Release(void* p);   // 0x0040????  (DefaultRefCounted::Release)
void FUN_00402420(void* p);                // 0x00402420
void SP_cJob_GetStatus(void* job);         // 0x00690120
void FUN_00526a40();                       // 0x00526a40
void FUN_004e1bf0();                       // 0x004e1bf0
void FUN_00525e10(void* p);                // 0x00525e10
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0

extern void* g_vtblF1c74;                // 0x013f1c74
extern void* g_vtblF1c70;                // 0x013f1c70
extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblSkinnerPaintSystem;   // 0x013eb394

inline void VCall1(void* p)
{
    (*(void(__thiscall**)(void*))(((void**)*(void**)p)[1]))(p);
}

struct PaintSystem2 {
    void dtor();
};

// @ 0x0051e3d0 PaintSystem dtor (full member teardown)
void PaintSystem2::dtor()
{
    *(void**)this = &g_vtblF1c74;
    *(void**)((char*)this + 4) = &g_vtblF1c70;
    if (*(void**)((char*)this + 0x104) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x104));
    if (*(void**)((char*)this + 0x100) != 0)
        FUN_00402420(*(void**)((char*)this + 0x100));
    if (*(void**)((char*)this + 0xfc) != 0)
        SP_cJob_GetStatus(*(void**)((char*)this + 0xfc));
    if (*(void**)((char*)this + 0xf8) != 0)
        SP_cJob_GetStatus(*(void**)((char*)this + 0xf8));
    if (*(void**)((char*)this + 0xf4) != 0)
        VCall1(*(void**)((char*)this + 0xf4));
    if (*(void**)((char*)this + 0xf0) != 0)
        VCall1(*(void**)((char*)this + 0xf0));
    for (uint32_t i = *(uint32_t*)((char*)this + 0x94); i < *(uint32_t*)((char*)this + 0x98); i += 8) {
    }
    FUN_00526a40();
    FUN_004e1bf0();
    FUN_00525e10(this);
    if (*(void**)((char*)this + 0x1c) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x1c));
    if (*(void**)((char*)this + 0x18) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x18));
    if (*(void**)((char*)this + 0x14) != 0)
        VCall1(*(void**)((char*)this + 0x14));
    if (*(void**)((char*)this + 0x10) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x10));
    if (*(void**)((char*)this + 0x0c) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x0c));
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    *(void**)this = &g_vtblSkinnerPaintSystem;
}

// ---- DeviceRestore support types (retail layout; the 2008 PDB differs) ----
struct RCObj {                      // refcount at +4, Release = 0x00453540 (thiscall)
    void* vt; int mRef;
    int AddRef() { return mRef++ + 1; }
    void __thiscall Release();  // 0x00453540
};
struct VObj {                       // slot0 AddRef, slot1 Release
    virtual void AddRef();
    virtual void Rel();
    virtual void S2();
    virtual void S3(int);
};
struct Job {
    void __thiscall Done();  // 0x00690120
};
struct AllocT {
    void __thiscall Init(unsigned, unsigned, unsigned, unsigned, unsigned, void*, void*, unsigned);  // 0x009266b0
};
struct MsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Subscribe(void* who, unsigned id);   // +0x20
};
struct FxMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual VObj* CreateEffect(unsigned id, int flag);  // +0x4c
};
struct JobMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Schedule(void* handle);                // +0x10
};
struct Vec8 {
    uint32_t first, last;
    void __thiscall erase(uint32_t f, uint32_t l);  // 0x00530c80
};
struct Rc1 {
    Rc1* __thiscall Ctor();  // 0x005062f0  (0x414 bytes)
};
struct Rc2 {
    Rc2* __thiscall Ctor();  // 0x0051a8a0  (0x350 bytes)
};
struct Rc3 {
    Rc3* __thiscall Ctor();  // 0x00507380  (0x1d0 bytes)
};
struct AOR : VObj {
    AOR* __thiscall Ctor();  // 0x00516ba0
    void __thiscall Setup(unsigned a, unsigned b);  // 0x00516ca0
};
struct JobSlot { void* fn; void* owner; uint32_t pad[4]; uint32_t flag; };
struct JobHandle {
    JobSlot* p;
    JobHandle* __thiscall Reset();  // 0x0041d940 (returns this)
};

extern AllocT g_FixedAlloc;                 // 0x015de2a0
extern unsigned g_015de57c;                 // 0x015de57c
void* operator_new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
MsgServer* GetMessageServer();              // 0x0067dcc0
FxMgr* GetEffectsManager();                 // 0x0067ddd0
JobMgr* GetJobMgr();                        // 0x0068f4d0
void __cdecl FUN_00541600(void*);   // 0x00541600
void __cdecl FUN_00541660(void*);   // 0x00541660
extern char ParticleTickJobCallback[];      // 0x005248a0
extern char BuildMeshJobCallback[];         // 0x00524a50

inline void SetRC(RCObj** slot, RCObj* p)
{
    if (p != *slot) {
        RCObj* old = *slot;
        if (p) p->AddRef();
        *slot = p;
        if (old) old->Release();
    }
}
template<class T> struct Ref { T* mp; T* operator->() const { return mp; } };
inline void SetV(Ref<VObj>* slotr, VObj* p)
{
    VObj** slot = &slotr->mp;
    if (p != *slot) {
        VObj* old = *slot;
        if (p) p->AddRef();
        *slot = p;
        if (old) old->Rel();
    }
}

struct PS {
    void* vt0; void* vt1; uint32_t p8;
    RCObj* m0c; RCObj* m10; Ref<VObj> m14; RCObj* m18;
    uint32_t p1c, m20, p24[10], m4c;
    uint32_t m50, m54, m58, m5c;
    uint8_t m60, m61, m62, m63;
    uint32_t m64, m68, m6c, m70, m74;
    uint8_t m78, m79, m7a, m7b, m7c, m7d, m7e, m7f;
    uint32_t p80[5];
    Vec8 m94;
    uint32_t p9c[0x14];
    uint32_t mec;
    Ref<VObj> mf0; Ref<VObj> mf4;
    JobHandle mf8; JobHandle mfc;
    uint32_t m100;
    RCObj* m104;
    void DeviceRestore();
};

// @ 0x0051e5b0 `anonymous namespace'::DeviceRestore
void PS::DeviceRestore()
{
    void* mem1; void* mem2; void* mem3; void* mem4;
    g_FixedAlloc.Init(0x50, 0, 200, 0, 0, (void*)FUN_00541600, (void*)FUN_00541660, 0);
    SetRC(&m10, 0);
    m20 = 0;
    {
        mem1 = operator_new(0x414, "Skinner", 0, 0, 0, 0);
        SetRC(&m0c, mem1 ? (RCObj*)((Rc1*)mem1)->Ctor() : 0);
    }
    {
        mem2 = operator_new(0x350, "Skinner", 0, 0, 0, 0);
        SetRC(&m18, mem2 ? (RCObj*)((Rc2*)mem2)->Ctor() : 0);
    }
    m60 = 0; m61 = 0; m62 = 0; m7b = 0;
    SetV(&mf0, 0);
    m50 = 0; m5c = 0; m54 = 0x4d2; m58 = 0x4d2;
    m68 = 0; m6c = 0; m70 = 0; m74 = 0xffffffff;
    m78 = 0; m79 = 0; m7a = 0; m63 = 1; m64 = 0;
    m7c = 0; m7d = 0; m7e = 0;
    Vec8* v = &m94;
    v->erase(v->first, v->last);
    mec = 0;
    GetMessageServer()->Subscribe(this, 0x44edd9c);
    GetMessageServer()->Subscribe(this, 0x247ca7b);
    SetV(&mf4, GetEffectsManager()->CreateEffect(0x37f23d0, 0));
    mf4->S3(4);
    {
        mem3 = operator_new(0x14, "Skinner/MeshAORender", 0, 0, 0, 0);
        SetV(&m14, mem3 ? ((AOR*)mem3)->Ctor() : 0);
    }
    m14->AddRef();
    ((AOR*)m14.mp)->Setup(0x46e92e0, g_015de57c);
    GetJobMgr()->Schedule(mf8.Reset());
    JobSlot* a1 = mf8.p;
    JobSlot* a2 = mf8.p;
    a2->fn = ParticleTickJobCallback;
    a2->owner = this;
    JobSlot* a3 = mf8.p;
    a3->flag = 1;
    JobMgr* jm2 = GetJobMgr();
    JobHandle* h = &mfc;
    if (h->p) { JobSlot* t = h->p; h->p = 0; ((Job*)t)->Done(); }
    jm2->Schedule(h);
    JobSlot* b1 = mfc.p;
    JobSlot* b2 = mfc.p;
    b2->fn = BuildMeshJobCallback;
    b2->owner = this;
    JobSlot* b3 = mfc.p;
    b3->flag = 1;
    {
        mem4 = operator_new(0x1d0, "Skinner", 0, 0, 0, 0);
        SetRC(&m104, mem4 ? (RCObj*)((Rc3*)mem4)->Ctor() : 0);
    }
}

// @ 0x0051ec70 nSPSkinner::cPaintSystem::Shutdown -- PARTIAL skeleton (1083-byte /Od body)
void FUN_0051ec70(void* self) { (void)self; }
