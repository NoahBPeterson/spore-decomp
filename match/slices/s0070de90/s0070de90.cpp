// Slice s0070de90: SP::cMaterialManager / SP::cLightingManager helpers + EA refcount algorithms.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <new>
#include <intrin.h>

// ---- stub types --------------------------------------------------------------
struct Mat { char _p[0x18]; unsigned mID; };   // cMaterialInternal: mID at +0x18

struct cMaterialManager {
    int  GetIDFromMaterial(Mat* m);
    void GetIDsFromMaterials(int n, Mat** mats, unsigned* ids);
};

// A refcounted object whose count sits at +0x3c.
struct RC3c  { void AddRef(); void Release(); };
// A refcounted object whose count sits at +0x3c (second family).
struct RC3b  { void AddRef(); void Release(); };
// Plain refcount at +0x14.
struct RC14  { int _pad[5]; int mCount; };
struct AutoRef14 { RC14* mpObject; void WeakRelease(); };
struct AutoRefA  { RC3c* mpObject; void Release(); };
struct AutoRefB  { RC3b* mpObject; void Release(); };
struct VObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual int  v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
};
struct Holder    { char _p[0xc]; VObj* mpObject; int Get(); };

// @ 0x0070e2c0
int cMaterialManager::GetIDFromMaterial(Mat* m)
{
    return m->mID;
}

// @ 0x0070e2d0
void cMaterialManager::GetIDsFromMaterials(int n, Mat** mats, unsigned* ids)
{
    for (int i = 0; i < n; i++)
        ids[i] = mats[i]->mID;
}

// @ 0x0070e300
void AutoRef14::WeakRelease()
{
    if (mpObject != 0)
    {
        int c = mpObject->mCount;
        if (c > 1)
            mpObject->mCount = c - 1;
    }
}

// @ 0x0070e320
void AutoRefA::Release()
{
    if (mpObject != 0)
        mpObject->Release();
}

// @ 0x0070e330
void AutoRefB::Release()
{
    if (mpObject != 0)
        mpObject->Release();
}

// @ 0x0070e340
void** AssignCopyA(void** first, void** last, void** dst)
{
    while (first != last)
    {
        void* src = *first;
        void* old = *dst;
        if (src != old)
        {
            if (src != 0)
                ((RC3c*)src)->AddRef();
            *dst = src;
            if (old != 0)
                ((RC3c*)old)->Release();
        }
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x0070e390
void** AssignCopyB(void** first, void** last, void** dst)
{
    while (first != last)
    {
        void* src = *first;
        void* old = *dst;
        if (src != old)
        {
            if (src != 0)
                ((RC3b*)src)->AddRef();
            *dst = src;
            if (old != 0)
                ((RC3b*)old)->Release();
        }
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x0070e890
void __stdcall RangeWeakRelease(RC14** first, RC14** last)
{
    while (first < last)
    {
        RC14* p = *first;
        if ((p != 0) && (p->mCount > 1))
            --p->mCount;
        ++first;
    }
}

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EAlloc(size_t n, const char* name, int a, unsigned b, const char* file, int line); // 0x00f473a0

void* __cdecl MessageServer(void);          // 0x0067dcc0
void* __cdecl PropertyManager(void);        // 0x0067de30

// A config record lives out of line (0x144 bytes). The payload is spelled as scalars (no array) so the
// compiler does not treat a local LConfig temporary as a /GS buffer.
struct LConfig {
    void* mpProperty;               // +0x000
    int mPad04, mPad08, mPad0c, mPad10, mPad14, mPad18, mPad1c, mPad20;
    int mPad24, mPad28, mPad2c, mPad30, mPad34, mPad38, mPad3c, mPad40;
    int mPad44, mPad48, mPad4c, mPad50, mPad54, mPad58, mPad5c, mPad60;
    int mPad64, mPad68, mPad6c, mPad70, mPad74, mPad78, mPad7c, mPad80;
    int mPad84, mPad88, mPad8c, mPad90, mPad94, mPad98, mPad9c, mPadA0;
    int mPadA4, mPadA8, mPadAc, mPadB0, mPadB4, mPadB8, mPadBc, mPadC0;
    int mPadC4, mPadC8, mPadCc, mPadD0, mPadD4, mPadD8, mPadDc, mPadE0;
    int mPadE4, mPadE8, mPadEc, mPadF0, mPadF4, mPadF8, mPadFc, mPad100;
    int mPad104, mPad108, mPad10c, mPad110, mPad114, mPad118, mPad11c, mPad120;
    int mPad124, mPad128, mPad12c, mPad130, mPad134, mPad138, mPad13c, mPad140;
    LConfig();                      // 0x00706dd0
    LConfig(const LConfig&);
    LConfig& operator=(const LConfig&);
    ~LConfig();                     // 0x007067f0
};
struct LConfigVec {
    LConfig* mpBegin; LConfig* mpEnd; LConfig* mpCap;
    void DoInsertValues(LConfig* pos, unsigned n, const LConfig& v); // 0x70d080
    LConfig* Erase(LConfig* first, LConfig* last);                   // 0x70ce80
    void push_back(const LConfig& v);                                // 0x70dd50
    void Resize(unsigned n);                                         // 0x70e060
};
LConfig* __cdecl LConfig_Default(LConfig* out);                      // 0x70dd50

// Refcounted property handle: the property's vtable slot 1 releases it.
struct PropRef {
    void* mpProp;
    PropRef() : mpProp(0) {}
    ~PropRef()
    {
        void* p = mpProp;
        if (p != 0)
        {
            mpProp = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
    }
    PropRef& operator=(void* p)
    {
        if (mpProp != 0)
        {
            void* old = mpProp;
            mpProp = 0;
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
        }
        mpProp = p;
        return *this;
    }
};

// A lighting world hangs off a node of the manager's world tree.
struct WorldNode {
    WorldNode* mpNext;      // +0x00  tree linkage
    void* mpParent;         // +0x04
    void* mpRight;          // +0x08
    char _pad0c[8];         // +0x0c
    void* mpWorld;          // +0x14
};
struct WorldObj {
    char _pad[0x10];
    void* mpConfig;         // +0x10  selected cLightingConfig
    void ApplyConfig();     // 0x007094c0
};
struct WorldTree {
    WorldNode* mpRoot;      // +0x00  anchor node; its address is the end sentinel
};
WorldNode* __cdecl RBTreeIncrement(WorldNode* node);   // 0x00921580

// A property record: type tag at +0x12, typed accessors.
struct PropValue {
    char _pad[0x12];
    short mType;            // +0x12
    char* GetBool();        // 0x0041e920
    int*  GetInt();         // 0x0041e990
};
// The app property list's vtable: +0x24 looks up an id, +0x2c by key, +0x48 enumerates keys.
struct PropertyList {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();                                                         // +0x20
    virtual char GetProperty(unsigned id, PropValue** out);                     // +0x24
    virtual void v0a();                                                         // +0x28
    virtual char GetPropertyByKey(unsigned key, unsigned id, PropValue** out);  // +0x2c
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11();
    virtual void EnumKeys(unsigned id, void* span);                             // +0x48
};

// A begin/end/cap vector of property keys handed back by PropertyList, released on scope exit.
void __cdecl EFree2(void* p);   // 0x00f47380
struct PropSpan {
    void* mpBegin; void* mpEnd; void* mpCap;
    ~PropSpan()
    {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            EFree2(mpBegin);
    }
};

// The manager itself (Reload's `this`): config vector at +0x18, world tree at +0x30.
struct LightingMgr {
    char mPad00[0x18];              // +0x00
    LConfigVec mConfigs;            // +0x18
    char mPad2c[4];                 // +0x2c
    WorldTree mWorlds;              // +0x30
    void FillLightingStateFromConfig(void* prop, LConfig* cfg);   // 0x0070aed0
    void Reload();                  // 0x0070e160
};

// Message-target subobject at manager+4: the same config vector seen at +0x14.
struct LightingMsgTarget {
    char mPad00[0x14];              // +0x00
    LConfigVec mConfigs;            // +0x14
    char mPad28[4];                 // +0x28
    WorldTree mWorlds;              // +0x2c
};
struct MsgReg { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
                virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
                virtual void a8(void*, int); virtual void a9(); virtual void a10(); virtual void a11(); };

// @ 0x0070e060
void LConfigVec_Resize(LConfigVec* self, unsigned n)
{
    unsigned sz = (unsigned)((self->mpEnd - self->mpBegin) / 0x144);
    if (n > sz)
    {
        LConfig tmp;
        LConfig_Default(&tmp);
        self->DoInsertValues(self->mpEnd, n - sz, tmp);
        tmp.~LConfig();
    }
    else
    {
        self->Erase(self->mpBegin + n, self->mpEnd);
    }
}

struct MsgRegOwner { char MsgRegister(); };
struct RebuildOwner { void Rebuild(); };
struct MatMgrW { char WriteMaterials(void* stream); };

// @ 0x0070e280
char MsgRegOwner::MsgRegister()
{
    void* self = this;
    ((LightingMgr*)self)->Reload();
    void* ms = MessageServer();
    if (ms != 0)
    {
        if (self != 0)
            ((MsgReg*)ms)->a8((char*)self + 4, 0xf62def);
        else
            ((MsgReg*)ms)->a8(0, 0xf62def);
    }
    return 1;
}

// @ 0x0070e6b0
void** __stdcall MakeHashNode(void** src)
{
    void** p = (void**)EAlloc(0xc, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
    if (p != 0)
    {
        p[0] = src[0];
        void* v = src[1];
        p[1] = v;
        if (v != 0)
            ((RC3c*)v)->AddRef();
    }
    p[2] = 0;
    return p;
}

// @ 0x0070ea70
void** UninitCopyAtomic8(void** out, void** first, void** last, void** dst)
{
    *out = dst;
    for (; first != last; ++first)
    {
        void** cur = (void**)*out;
        if (cur != 0)
        {
            void* p = *first;
            *cur = p;
            if (p != 0)
                ++*(volatile long*)((char*)p + 8);
        }
        *out = (void**)((char*)*out + 4);
    }
    return out;
}

// @ 0x0070eb30
void FillNAtomic8(void** dst, unsigned n, void** value)
{
    for (; n != 0; --n)
    {
        if (dst != 0)
        {
            void* p = *value;
            *dst = p;
            if (p != 0)
                ++*(volatile long*)((char*)p + 8);
        }
        ++dst;
    }
}

// @ 0x0070e3e0
void** CopyBackwardA(void** first, void** last, void** dstEnd)
{
    while (last != first)
    {
        void* s = last[-1];
        void* old = dstEnd[-1];
        --last;
        --dstEnd;
        if (s != old)
        {
            if (s != 0)
                ((RC3c*)s)->AddRef();
            *dstEnd = s;
            if (old != 0)
                ((RC3c*)old)->Release();
        }
    }
    return dstEnd;
}

// @ 0x0070e430
void** CopyBackwardB(void** first, void** last, void** dstEnd)
{
    while (last != first)
    {
        void* s = last[-1];
        void* old = dstEnd[-1];
        --last;
        --dstEnd;
        if (s != old)
        {
            if (s != 0)
                ((RC3b*)s)->AddRef();
            *dstEnd = s;
            if (old != 0)
                ((RC3b*)old)->Release();
        }
    }
    return dstEnd;
}

// @ 0x0070ebb0
void FillWeak14(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ++*(int*)((char*)s + 0x14);
            *first = s;
            if (old != 0)
            {
                int c = *(int*)((char*)old + 0x14);
                if (c > 1)
                    *(int*)((char*)old + 0x14) = c - 1;
            }
        }
        ++first;
    }
}

// @ 0x0070ebf0
void AssignWeak14(void** first, void** last, void** dst)
{
    while (first != last)
    {
        void* s = *first;
        void* old = *dst;
        if (s != old)
        {
            if (s != 0)
                ++*(int*)((char*)s + 0x14);
            *dst = s;
            if (old != 0)
            {
                int c = *(int*)((char*)old + 0x14);
                if (c > 1)
                    *(int*)((char*)old + 0x14) = c - 1;
            }
        }
        ++first;
        ++dst;
    }
}

// @ 0x0070ec30
void** CopyBackwardWeak14(void** first, void** last, void** dstEnd)
{
    while (last != first)
    {
        void* s = last[-1];
        void* old = dstEnd[-1];
        --last;
        --dstEnd;
        if (s != old)
        {
            if (s != 0)
                ++*(int*)((char*)s + 0x14);
            *dstEnd = s;
            if (old != 0)
            {
                int c = *(int*)((char*)old + 0x14);
                if (c > 1)
                    *(int*)((char*)old + 0x14) = c - 1;
            }
        }
    }
    return dstEnd;
}

// @ 0x0070eb70
void UninitCopyWeak14(void** out, void** first, void** last, void** dst)
{
    *out = dst;
    if (first != last)
    {
        do
        {
            if (dst != 0)
            {
                void* p = *first;
                *dst = p;
                if (p != 0)
                    ++*(int*)((char*)p + 0x14);
            }
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
}

// @ 0x0070e950
void FillA(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ((RC3c*)s)->AddRef();
            *first = s;
            if (old != 0)
                ((RC3c*)old)->Release();
        }
        ++first;
    }
}

// @ 0x0070ea20
void FillB(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ((RC3b*)s)->AddRef();
            *first = s;
            if (old != 0)
                ((RC3b*)old)->Release();
        }
        ++first;
    }
}

// @ 0x0070e4c0
int Holder::Get()
{
    VObj* p = mpObject;
    if (p != 0)
        return p->v5();
    return 0;
}

// ---- remaining functions (behavioral reconstructions) ------------------------
void __cdecl D3D_FlushSomeStates(void);                      // 0x006fd7b0
int  __cdecl ResSize(void* p);                               // 0x00777740
void __cdecl ResCopy(void* dst, int n, void* out);           // 0x00777720
void* __cdecl EAlloc8(size_t n, unsigned a, int b, int c, const char* d, int e, int f, int g); // 0x00f473d0
void __cdecl EFree2(void* p);                                // 0x00f47380
void* __cdecl MessageServerRaw(void);                        // 0x0067dcc0
void __cdecl ActiveStateFlushX(void);                        // 0x006fd790
void* __cdecl CreateVertexBuffer(int flags, int b);           // 0x007616f0
void* __cdecl CreateCompiledState(void* vb);                 // 0x007617a0
void __cdecl RegisterInvalidShader();                        // 0x00713f20
void* __cdecl PropGetBoolStub();                             // 0x0041e920
void* __cdecl PropGetIntStub();                              // 0x0041e990
void* __cdecl SpriteMgrA();                                  // 0x00761b40
void* __cdecl SpriteMgrB();                                  // 0x0067dd60
void __cdecl DoNothing1(void* p);                             // 0x00761150
void __cdecl GetImageResourceStub();                         // 0x00576650
void __cdecl DoNothing2();                                   // 0x0077e6d0
void __cdecl DoNothing3();                                   // 0x0067d0c0
int  __cdecl WriteUint32Stub(void* s, void* d, int n, int f); // 0x0093aa70
void __cdecl FreeStreamStub(void* s);                        // 0x006fe430
void __cdecl FragDeclStub(void* s);                          // 0x006fa480
extern void* g_device; // 0x016f89d0
char __cdecl props_get(void* propList, unsigned id, void* out);
extern unsigned char g_dbg[8];      // 0x015345ac
extern unsigned g_dbg2;             // 0x015345b0
extern void* g_propList;            // 0x015fd918
extern const float kOne;            // 0x01485720
int __stdcall QueryPerformanceCounter(long long* counter);   // kernel32

// ---- SP::cMaterialManager ---------------------------------------------------
struct VBDesc {
    unsigned mFlags00;              // +0x000
    unsigned mFlags04;              // +0x004
    char mPad08[0x5c];              // +0x008
    float mOne64;                   // +0x064
    float mOne68;                   // +0x068
    float mOne6c;                   // +0x06c
    float mOne70;                   // +0x070
    char mPad74[0x434 - 0x74];      // +0x074
    unsigned mFlags434;             // +0x434
    unsigned mFlags438;             // +0x438
    int mState43c;                  // +0x43c
    int mState440;                  // +0x440
    int mState444;                  // +0x444
    int mState448;                  // +0x448
};
struct VBInitOwner { void Init(int a, int b); };   // 0x011f9c10 (thiscall on the VB)
struct ImageOwner { void GetImageResource(void* res); };   // 0x00576650

struct MaterialMgr {
    char mPad000[0x1b4];            // +0x000
    void* mpState1b4;               // +0x1b4
    unsigned char mb1b8;            // +0x1b8
    char mPad1b9[3];                // +0x1b9
    void* mpState1bc;               // +0x1bc
    char mPad1c0[0x10];             // +0x1c0
    int mState1d0;                  // +0x1d0
    char mPad1d4[0x34];             // +0x1d4
    unsigned mTickLow;              // +0x208
    unsigned mTickHigh;             // +0x20c
    char mPad210[8];                // +0x210
    int mClockSource;               // +0x218
    char mPad21c[4];                // +0x21c
    int mState220;                  // +0x220
    char Init();                    // 0x0070ec80
};

void __stdcall FixedElem_ctor(void* p);   // 0x006c0fa0  rw::BaseResourceDescriptor::BaseResourceDescriptor
void __stdcall FixedElem_dtor(void* p);   // 0x00c2e4e0
void __stdcall _eh_vector_constructor_iterator_(void* ptr, unsigned size, unsigned count,
                                                void (__stdcall* ctor)(void*),
                                                void (__stdcall* dtor)(void*));

struct FixedArrayBuilder {
    void* mpFirst;              // +0x00
    void* MakeFixedArray(void* dest);
};

// @ 0x0070e480  (fixed-array wrapper constructor)
void* FixedArrayBuilder::MakeFixedArray(void* dest)
{
    volatile int state = 0;
    const void* first = mpFirst;
    _eh_vector_constructor_iterator_(dest, 8, 4, FixedElem_ctor, FixedElem_dtor);
    void** out = (void**)dest;
    out[0] = (void*)first;
    out[1] = (void*)0x10;
    return out;
}

// @ 0x0070e4e0  (rebuild per-instance graphics resources)
void RebuildOwner::Rebuild()
{
    int self = (int)this;
    D3D_FlushSomeStates();
    int n = (*(int*)(self + 0x9c) - *(int*)(self + 0x98)) >> 2;
    for (int i = 0; i < n; i++)
    {
        char* p = (char*)(*(int*)(*(int*)(self + 0x98) + i * 4) + 0x88);
        for (int j = 0; j < 0x10; j++)
        {
            if (*(void**)(p - 0x40) != 0)
            {
                int sz = ResSize(*(void**)(p - 0x40));
                void* nb = EAlloc8(sz, 0x10, 0, 0, "Graphics", 0, 0, 0);
                ResCopy(*(void**)(p - 0x40), sz, nb);
                void* obj = *(void**)(p - 0x40);
                void** vt = *(void***)obj;
                ((void(__thiscall*)(void*))vt[2])(obj);
                *(void**)(p - 0x40) = nb;
            }
            if (*(void**)p != 0)
            {
                int sz = ResSize(*(void**)p);
                void* nb = EAlloc8(sz, 0x10, 0, 0, "Graphics", 0, 0, 0);
                ResCopy(*(void**)p, sz, nb);
                void* obj2 = *(void**)p;
                void** vt2 = *(void***)obj2;
                ((void(__thiscall*)(void*))vt2[2])(obj2);
                *(void**)p = nb;
            }
            p += 4;
        }
    }
}

// @ 0x0070e5e0  (release per-instance graphics resources)
void RebuildResources2(int self)
{
    int n = (*(int*)(self + 0x9c) - *(int*)(self + 0x98)) >> 2;
    for (int i = 0; i < n; i++)
    {
        char* p = (char*)(*(int*)(*(int*)(self + 0x98) + i * 4) + 0x88);
        for (int j = 0; j < 0x10; j++)
        {
            void* a = *(void**)(p - 0x40);
            if (a != 0)
            {
                void** vt = *(void***)g_device;
                ((void(__thiscall*)(void*, void*, void*))vt[0x16c / 4])(g_device, a, p - 0x40);
                EFree2(a);
            }
            void* b = *(void**)p;
            if (b != 0)
            {
                void** vt = *(void***)g_device;
                ((void(__thiscall*)(void*, void*, void*))vt[0x1a8 / 4])(g_device, b, p);
                EFree2(b);
            }
            p += 4;
        }
    }
}

// @ 0x0070e8c0  (uninitialized copy with AddRef)
void UninitCopyA2(void** out, void** first, void** last, void** dst)
{
    *out = dst;
    void** result = dst;
    try
    {
        for (; first != last; ++first, ++result)
        {
            void* s = *first;
            *result = s;
            if (s != 0)
                ((RC3c*)s)->AddRef();
        }
    }
    catch (...)
    {
        for (void** q = dst; q != result; ++q)
            ((RC3c*)*q)->Release();
        throw;
    }
    *out = result;
}

// @ 0x0070e9a0  (uninitialized fill_n with AddRef)
void UninitFillNA2(void** first, unsigned n, void** value)
{
    void** result = first;
    try
    {
        for (; n != 0; --n, ++result)
        {
            void* s = *value;
            *result = s;
            if (s != 0)
                ((RC3c*)s)->AddRef();
        }
    }
    catch (...)
    {
        for (void** q = first; q != result; ++q)
            ((RC3c*)*q)->Release();
        throw;
    }
}

// @ 0x0070eac0  (fill with atomic refcount at +8)
void FillAtomic8(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ++*(volatile long*)((char*)s + 8);
            *first = s;
            if (old != 0)
            {
                volatile long* rc = (volatile long*)((char*)old + 8);
                --*rc;
            }
        }
        ++first;
    }
}

// @ 0x0070ec80  (SP::cMaterialManager::Init)
char MaterialMgr::Init()
{
    ActiveStateFlushX();
    PropValue* prop;
    if (g_propList != 0 &&
        ((PropertyList*)g_propList)->GetProperty(0x5fb85a3, &prop) &&
        prop->mType == 1)
        g_dbg[0] = *prop->GetBool();
    if (g_propList != 0 &&
        ((PropertyList*)g_propList)->GetProperty(0x5fb85a4, &prop) &&
        prop->mType == 9)
        g_dbg2 = *prop->GetInt();

    void* vb;
    if (g_propList != 0 &&
        ((PropertyList*)g_propList)->GetProperty(0x179ada3, &prop) &&
        prop->mType == 1 &&
        *prop->GetBool() != 0)
    {
        RegisterInvalidShader();
        vb = CreateVertexBuffer(0x7ffffffe, 0);
    }
    else
    {
        vb = CreateVertexBuffer((int)0x80000002, 0);
    }

    VBDesc* desc = (VBDesc*)vb;
    desc->mFlags434 |= 1;
    desc->mFlags438 |= 1;
    desc->mFlags00 |= 0x10;
    desc->mFlags04 |= 0x10;
    const float one = kOne;
    desc->mOne64 = one;
    desc->mOne68 = one;
    desc->mOne6c = one;
    desc->mOne70 = one;
    desc->mState43c = 0;
    desc->mFlags434 |= 2; desc->mFlags438 |= 2; desc->mState440 = 0;
    desc->mFlags434 |= 4; desc->mFlags438 |= 4; desc->mState444 = 0;
    desc->mFlags434 |= 8; desc->mFlags438 |= 8; desc->mState448 = 0;

    ((VBInitOwner*)vb)->Init(4, 0);
    void* cs = CreateCompiledState(vb);
    mpState1b4 = cs;
    mb1b8 = 1;
    mpState1bc = cs;
    mState1d0 = -1;
    DoNothing1(vb);

    void* image = SpriteMgrA();
    void* mgr = SpriteMgrB();
    void** vt = *(void***)mgr;
    void* res = ((void*(__thiscall*)(void*, void*, int))vt[0x48 / 4])(mgr, image, 0);
    ((ImageOwner*)((char*)this + 0x14))->GetImageResource(res);
    DoNothing2();
    DoNothing3();

    if ((mTickLow | mTickHigh) == 0)
    {
        if (mClockSource == 1)
        {
            unsigned long long stamp = __rdtsc();
            mTickLow = (unsigned)stamp;
            mTickHigh = (unsigned)(stamp >> 32);
        }
        else
        {
            long long counter = 0;
            QueryPerformanceCounter(&counter);
            mTickLow = (unsigned)counter;
            mTickHigh = (unsigned)(counter >> 32);
        }
    }
    mState220 = 0;
    return 1;
}

// @ 0x0070eea0  (SP::cMaterialManager::WriteMaterials)
char MatMgrW::WriteMaterials(void* stream)
{
    int self = (int)this;
    int local[3];
    local[0] = *(int*)(self + 0x200);
    local[1] = 0x469a3f7;
    local[2] = *(int*)0x01535f68;
    int saved = 0;
    void** vt = *(void***)stream;
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int, int, int))vt[0x34 / 4])
              (stream, local, &saved, 2, 6, 1, 0);
    if (ok == 0)
        return 0;
    int s = ((int(__thiscall*)(void*))vt[0x18 / 4])(stream);
    int one = 1;
    WriteUint32Stub((void*)s, &one, 1, 0);
    FreeStreamStub((void*)s);
    FragDeclStub((void*)s);
    ((void(__thiscall*)(void*))vt[0x24 / 4])(stream);
    return 1;
}

// @ 0x0070de90 cLightingManager_HandleMessage
char __fastcall cLightingManager_HandleMessage(LightingMsgTarget* self, int, int msg, void* data)
{
    if (msg != 0xf62def)
        return 0;
    int key = *(int*)((char*)data + 0x10);
    if (key == *(int*)0x01535b38)
    {
        int state = *(int*)((char*)data + 0x18);
        LightingMgr* mgr = (LightingMgr*)((char*)self - 4);
        LConfig* found = 0;
        int count = (int)(self->mConfigs.mpEnd - self->mConfigs.mpBegin);
        for (int i = 0; i < count; i++)
        {
            LConfig* cfg = self->mConfigs.mpBegin + i;
            if (cfg->mpProperty != 0 && *(int*)(*(int*)cfg->mpProperty + 8) == state)
            {
                mgr->FillLightingStateFromConfig(cfg->mpProperty, cfg);
                found = cfg;
                break;
            }
        }
        if (found == 0)
        {
            void* pm = PropertyManager();
            PropRef prop;
            prop = 0;
            if (((PropertyList*)pm)->GetPropertyByKey(key, state, (PropValue**)&prop.mpProp))
            {
                {
                    LConfig tmp;
                    self->mConfigs.push_back(tmp);
                }
                found = self->mConfigs.mpEnd - 1;
                mgr->FillLightingStateFromConfig(prop.mpProp, found);
            }
        }
        if (found != 0)
        {
            WorldNode* head = (WorldNode*)&self->mWorlds;
            for (WorldNode* node = self->mWorlds.mpRoot; node != head; node = RBTreeIncrement(node))
            {
                WorldObj* world = (WorldObj*)node->mpWorld;
                if (world->mpConfig != 0 && world->mpConfig == (void*)found)
                    world->ApplyConfig();
            }
        }
    }
    return 1;
}

// @ 0x0070e160 Reload
void LightingMgr::Reload()
{
    PropSpan span;
    span.mpBegin = 0; span.mpEnd = 0; span.mpCap = 0;
    void* pm = PropertyManager();
    ((PropertyList*)pm)->EnumKeys(*(unsigned*)0x01535b38, (void*)&span);
    unsigned n = (unsigned)(((char*)span.mpEnd - (char*)span.mpBegin) >> 2);
    mConfigs.Resize(n);
    PropRef prop;
    prop = 0;
    LConfig* dst = mConfigs.mpBegin;
    for (unsigned i = 0; i < n; i++)
    {
        prop = 0;
        unsigned key = ((unsigned*)span.mpBegin)[i];
        if (((PropertyList*)pm)->GetPropertyByKey(key, *(unsigned*)0x01535b38, (PropValue**)&prop.mpProp))
            FillLightingStateFromConfig(prop.mpProp, dst);
        ++dst;
    }
    prop = 0;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct LConfig {
    ~LConfig();   // 0x00f47380 (equiv t3)
};
struct RC3b {
    void AddRef();   // 0x006e54c0 (equiv t3)
    void Release();   // 0x006fd300 (equiv t2)
};
struct RC3c {
    void AddRef();   // 0x006e54c0 (equiv t3)
    void Release();   // 0x006e57a0 (equiv t3)
};
}
