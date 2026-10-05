// Slice s0070de90: SP::cMaterialManager / SP::cLightingManager helpers + EA refcount algorithms.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

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

// A config record lives out of line (0x144 bytes).
struct LConfig { unsigned char _d[0x144]; LConfig(); LConfig(const LConfig&); LConfig& operator=(const LConfig&); ~LConfig(); };
struct LConfigVec {
    LConfig* mpBegin; LConfig* mpEnd; LConfig* mpCap;
    void DoInsertValues(LConfig* pos, unsigned n, const LConfig& v); // 0x70d080
    LConfig* Erase(LConfig* first, LConfig* last);                   // 0x70ce80
};
LConfig* __cdecl LConfig_Default(LConfig* out);                      // 0x70dd50

void ReloadLightingStates(void* self);  // 0x70e160
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

// @ 0x0070e280
char cMaterialMsgRegister(void* self)
{
    ReloadLightingStates(self);
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
void** MakeHashNode(void** src)
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
void UninitCopyAtomic8(void** out, void** first, void** last, void** dst)
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
void CopyBackwardWeak14(void** first, void** last, void** dstEnd)
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
int  __cdecl CreateVertexBuffer(unsigned flags, int b);      // 0x007616f0
void* __cdecl CreateCompiledState(void* vb);                 // 0x007617a0
void __cdecl RegisterInvalidShader();                        // 0x00713f20
void* __cdecl PropGetBoolStub();                             // 0x0041e920
void* __cdecl PropGetIntStub();                              // 0x0041e990
void* __cdecl SpriteMgrA();                                  // 0x00761b40
void* __cdecl SpriteMgrB();                                  // 0x0067dd60
void __cdecl DoNothing1();                                   // 0x00761150
void __cdecl GetImageResourceStub();                         // 0x00576650
void __cdecl DoNothing2();                                   // 0x0077e6d0
void __cdecl DoNothing3();                                   // 0x0067d0c0
int  __cdecl WriteUint32Stub(void* s, void* d, int n, int f); // 0x0093aa70
void __cdecl FreeStreamStub(void* s);                        // 0x006fe430
void __cdecl FragDeclStub(void* s);                          // 0x006fa480
void __cdecl _eh_vector_constructor_iterator_(void* ptr, unsigned size, unsigned count, void* ctor, void* dtor);
extern void* g_device;
char __cdecl props_get(void* propList, unsigned id, void* out);
extern unsigned char g_dbg[8];
extern unsigned g_dbg2;
void __cdecl make_the_buffer(void* self, unsigned flags);
void __cdecl FillLightingStateFromConfig(void* a, void* b);   // 0x0070aed0
void __cdecl RBTreeInc(void* n);                              // 0x00921580

// @ 0x0070e480  (fixed-array wrapper constructor)
void* MakeFixedArray(void* ret, const void* src)
{
    const void* first = *(const void**)ret;
    _eh_vector_constructor_iterator_(ret, 8, 4, 0, 0);
    *(const void**)ret = first;
    ((unsigned*)ret)[1] = 0x10;
    return ret;
}

// @ 0x0070e4e0  (rebuild per-instance graphics resources)
void RebuildResources1(int self)
{
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
char cMaterialManager_Init(void* self)
{
    ActiveStateFlushX();
    unsigned* props = (unsigned*)PropertyManager();
    if (props != 0)
    {
        char* out;
        if (props_get(props, 0x5fb85a3, &out) && *(short*)(out + 0x12) == 1)
            g_dbg[0] = *(char*)PropGetBoolStub();
        if (props_get(props, 0x5fb85a4, &out) && *(short*)(out + 0x12) == 9)
            g_dbg2 = *(int*)PropGetIntStub();
        if (props_get(props, 0x179ada3, &out) && *(short*)(out + 0x12) == 1)
        {
            if (*(char*)PropGetBoolStub() != 0)
            {
                RegisterInvalidShader();
                make_the_buffer(self, 0x7ffffffe);
                return 1;
            }
        }
    }
    make_the_buffer(self, 0x80000002);
    return 1;
}

void make_the_buffer(void* self, unsigned flags)
{
    {
        unsigned* vb = (unsigned*)CreateVertexBuffer(flags, 0);
        vb[0x10d] |= 1;
        vb[0x10e] |= 1;
        vb[0] |= 0x10;
        vb[1] |= 0x10;
        vb[0x19] = 0x3f800000;
        vb[0x1a] = 0x3f800000;
        vb[0x1b] = 0x3f800000;
        vb[0x1c] = 0x3f800000;
        vb[0x10f] = 0;
        vb[0x10d] |= 2; vb[0x10e] |= 2; vb[0x110] = 0;
        vb[0x10d] |= 4; vb[0x10e] |= 4; vb[0x111] = 0;
        vb[0x10d] |= 8; vb[0x10e] |= 8; vb[0x112] = 0;
        void* cs = CreateCompiledState(vb);
        *(void**)((char*)self + 0x1b4) = cs;
        *(char*)((char*)self + 0x1b8) = 1;
        *(void**)((char*)self + 0x1bc) = cs;
        *(int*)((char*)self + 0x1d0) = -1;
        DoNothing1();
        void* m = SpriteMgrA();
        void* mm = SpriteMgrB();
        GetImageResourceStub();
        DoNothing2();
        DoNothing3();
        if (*(int*)((char*)self + 0x208) == 0 && *(int*)((char*)self + 0x20c) == 0)
        {
            if (*(int*)((char*)self + 0x218) == 1)
            {
                *(int*)((char*)self + 0x20c) = 0;
            }
            else
            {
                *(int*)((char*)self + 0x20c) = 0;
            }
            *(int*)((char*)self + 0x208) = 0;
        }
        *(int*)((char*)self + 0x220) = 0;
    }
}

// @ 0x0070eea0  (SP::cMaterialManager::WriteMaterials)
char cMaterialManager_WriteMaterials(int self, void* stream)
{
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

// @ 0x0070de90  (cLightingManager lighting-state message handler)
int cLightingManager_HandleMessage(void* self, int msg, void* data)
{
    if (msg != 0xf62def)
        return 0;
    int id = *(int*)((char*)data + 0x10);
    if (id == *(int*)0x01535b38)
    {
        int state = *(int*)((char*)data + 0x18);
        int count = (*(int*)((char*)self + 0x18) - *(int*)((char*)self + 0x14)) / 0x144;
        void* found = 0;
        int i = 0;
        for (; i < count; i++)
        {
            void* cfg = (void*)(*(int*)((char*)self + 0x14) + i * 0x144);
            if (*(void**)cfg != 0 && *(int*)(*(int*)cfg + 8) == state)
                break;
        }
        if (i < count)
        {
            void* cfg = (void*)(*(int*)((char*)self + 0x14) + i * 0x144);
            FillLightingStateFromConfig(cfg, cfg);
            found = cfg;
        }
        else
        {
            void* pm = PropertyManager();
            void** vt = *(void***)pm;
            void* prop = 0;
            if (((char(__thiscall*)(void*, int, int, void**))vt[0x2c / 4])(pm, state, id, &prop))
            {
                LConfig tmp;
                LConfig_Default(&tmp);
                LConfigVec_Resize((LConfigVec*)((char*)self + 0x14), count + 1);
                LConfig* last = *(LConfig**)((char*)self + 0x18) - 1;
                FillLightingStateFromConfig((void*)prop, last);
                tmp.~LConfig();
                found = last;
            }
        }
        if (found != 0)
        {
            void* node = (void*)*(int*)((char*)self + 0x30);
            void* head = (char*)self + 0x2c;
            while (node != head)
            {
                void* w = *(void**)((char*)node + 0x14);
                if (*(void**)((char*)w + 0x10) == found)
                    RBTreeInc(node);
                node = (void*)*(int*)node; // advance placeholder
                break;
            }
        }
    }
    return 1;
}

// @ 0x0070e160  (reload lighting states from the property manager)
void ReloadLightingStates(void* self)
{
    unsigned local[3];
    local[0] = 0; local[1] = 0; local[2] = 0;
    void* pm = PropertyManager();
    void** vt = *(void***)pm;
    ((void(__thiscall*)(void*, unsigned, void*))vt[0x48 / 4])(pm, *(unsigned*)0x01535b38, local);
    unsigned n = (local[1] - local[0]) >> 2;
    LConfigVec_Resize((LConfigVec*)((char*)self + 0x18), n);
    for (unsigned i = 0; i < n; i++)
    {
        void* prop = 0;
        unsigned key = *(unsigned*)(local[0] + i * 4);
        if (((char(__thiscall*)(void*, unsigned, unsigned, void**))vt[0x2c / 4])(pm, key, *(unsigned*)0x01535b38, &prop))
        {
            LConfig* dst = *(LConfig**)((char*)self + 0x18) + i;
            FillLightingStateFromConfig(prop, dst);
        }
    }
    if (local[0] != 0)
        EFree2((void*)local[0]);
}
