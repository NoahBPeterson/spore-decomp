// Slice s006ef990 — SP::cEffectsRendererSystem / SP::cEffectsModel helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"
#include <intrin.h>

extern "C" void FUN_00762a60(void* p);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void FUN_00f47410_free(void* p);          // 0x00f47410
extern "C" void FUN_00762a00_free(void* p);          // 0x00762a00

struct Dispatch3 { void* p0; void* p1; void* p2; };   // 0xc

// cEffectsModel layout (retail): vptr +0, refcount +4, dispatch vector +8.
struct cEffectsModelR {
    void** mpVtable;      // +0x00
    int    mnRefCount;    // +0x04
    Dispatch3* mpBegin;   // +0x08
    Dispatch3* mpEnd;     // +0x0c

    void Reset();         // 6edb10
};

// ---- 0x006ef990 (free function, cdecl: takes the model pointer) -------------
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

// ---- cEffectsRendererSystem -------------------------------------------------
struct cEffectsModel2;
extern "C" void* __cdecl GAlloc(unsigned n, unsigned align, int a, const void* tag,
                                int b, int c, int d, int e);   // 0x00f473d0
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
inline void* operator new(unsigned, void* p) { return p; }

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

// Thread-safe reference count at +8.
struct AtomicRefCounted {
    void* vftable;          // +0
    uint32_t mField4;       // +4
    volatile long mnRefCount; // +8

    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    int Release()
    {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};

class __declspec(align(16)) cEffectsRendererSystem {
public:
    cEffectsRendererSystem();
    AtomicRefCounted* mAt0;         // +0x00  (atomic ref-counted)
    cEffectsModel2* mpModel;        // +0x04  (model, refcount at +4)
    char pad1[0x30d50 - 0x08];
    void* mAt30d50;                 // +0x30d50
    void* mAt30d54;                 // +0x30d54  (vector begin)
    void* mAt30d58;                 // +0x30d58  (vector end)
    void* mAt30d5c;                 // +0x30d5c
    char pad2[0x30d68 - 0x30d60];
    void* mAt30d68;                 // +0x30d68
    void* mAt30d6c;                 // +0x30d6c
    void* mAt30d70;                 // +0x30d70
    char pad3[0x30d7c - 0x30d74];
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

inline cEffectsRendererSystem::cEffectsRendererSystem()
    : mAt0(0), mpModel(0), mAt30d50(0), mAt30d54(0), mAt30d58(0), mAt30d5c(0),
      mAt30d68(0), mAt30d6c(0), mAt30d70(0), mAt30d7c(0), mAt30d80(0), mAt30d84(0)
{
}

struct cERSDtor;
extern cERSDtor* g_pEffectsRendererSystem;   // DAT_01618d10

extern "C" void* CreateTestModel();
extern "C" void* FUN_007c3af0(const char* s);
extern "C" void* FUN_00762b70(void* p, int a, int b, int c);
void* CreateMesh(int n);           // SP::CreateMesh

struct MeshStub {
    void FUN96e0(int);
    void FUN9670(int, void*);
};
struct cEffectsModel2 {
    void** mpVtable;    // +0
    int    mnRefCount;  // +4
};

// ---- 0x006ef9e0 -------------------------------------------------------------
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

// erase(begin(), end()) of a dword vector (eastl-style copy-then-shrink tail).
struct DwordVector {
    void** mpBegin;
    void** mpEnd;

    void erase_all()
    {
        unsigned n = (unsigned)(mpEnd - mpBegin);
        memcpy(mpBegin, mpEnd, (unsigned)(mpEnd - mpEnd));
        mpEnd -= n;
    }
};

// ---- 0x006efa90 -------------------------------------------------------------
// @ 0x006efa90
char cEffectsRendererSystem::Shutdown()
{
    if (mAt30d7c)
        FUN_00f47410_free(mAt30d7c);
    if (mAt30d80)
        FUN_00762a00_free(mAt30d80);
    ((DwordVector*)&mAt30d54)->erase_all();
    ((DwordVector*)&mAt30d68)->erase_all();

    if (mAt0) {
        AtomicRefCounted* old = mAt0;
        mAt0 = 0;
        old->Release();
    }
    if (mpModel) {
        Release((cEffectsModelR*)mpModel);
        if (mpModel) {
            cEffectsModel2* p = mpModel;
            mpModel = 0;
            int n = p->mnRefCount - 1;
            p->mnRefCount = p->mnRefCount - 1;
            if (n == 0) {
                p->mnRefCount = 1;
                _ReadWriteBarrier();
                ((void (__thiscall*)(void*, int))p->mpVtable[0])(p, 1);
            }
        }
    }
    return 1;
}

// ---- 0x006efb90 (static singleton factory) ----------------------------------
// @ 0x006efb90
void CreateEffectsRendererSystem()
{
    cEffectsRendererSystem* p = (cEffectsRendererSystem*)GAlloc(
        sizeof(cEffectsRendererSystem), 0x10, 0, (const void*)0x140b2e4, 0, 0, 0, 0);
    new (p) cEffectsRendererSystem;
    g_pEffectsRendererSystem = (cERSDtor*)p;
    p->Init();
}

// ---- 0x006efc10 -------------------------------------------------------------
// @ 0x006efc10
struct cERSDtor { void Shutdown(); ~cERSDtor(); };

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

// ===========================================================================
// cEffectsRenderer (0x70-byte particle records, 0x68-byte entities)
// ===========================================================================
typedef unsigned int   uint32_t_;
typedef unsigned short uint16_t_;
typedef unsigned char  uint8_t_;
typedef short          int16_t_;

extern "C" float g1471064;      // 0x01471064 distance scale
extern "C" float g1470f1c;      // 0x01470f1c falloff coefficient
extern "C" float g1485720;      // 0x01485720 one
extern "C" float g1533c74;      // 0x01533c74 far bound
extern "C" unsigned g16f9528;   // 0x016f9528 render flags
extern "C" unsigned g16fa38c;   // 0x016fa38c raster flags
extern "C" unsigned g16f9238;   // 0x016f9238
extern "C" unsigned g16f96a8;   // 0x016f96a8 material colour
extern "C" unsigned g16f96ac;
extern "C" unsigned g16f96b0;
extern "C" unsigned g16f96b4;
extern "C" unsigned g16f96a0;
extern "C" void*    g16fa380;   // 0x016fa380 current matrix pointer
extern "C" float    g16fa4f0[16]; // 0x016fa4f0 default matrix
extern "C" unsigned g140afc4, g140afc8, g140afcc, g140afd0;
extern "C" unsigned* g_pRendererSystem4;   // 0x1618d10 + 4 modeled below

extern cERSDtor* g_pEffectsRendererSystem;
static void* g_pERS4() { return *(void**)((char*)g_pEffectsRendererSystem + 4); }

// __thiscall callees, declared __fastcall with a dummy 2nd argument.
extern "C" char __fastcall f7c4fd0(void*, int);                     // 0x007c4fd0 viewer begin
extern "C" void __fastcall f7c3c10(void*, int);                     // 0x007c3c10 viewer end
extern "C" char __fastcall f6ee140(void*, int);                     // 0x006ee140 ready?
extern "C" void __fastcall f6e7ac0(void*, int, void*);              // 0x006e7ac0 bind
extern "C" void __fastcall f6e7b50(void*, int, void*);              // 0x006e7b50 draw
extern "C" char __fastcall f700120(void*, int, float*, float*, int); // 0x00700120 frustum test
extern "C" void __fastcall f7c3d30(void*, int, int, int, int, float*); // 0x007c3d30 camera
extern "C" void __cdecl f6ec7c0(void*, void*, void*);               // 0x006ec7c0 sort bucket
extern "C" void __fastcall f6ec390(void*, int, void*, void*);       // 0x006ec390 push bucket rec
extern "C" void* __fastcall f6ecb40(void*, int, void*, int, void*); // 0x006ecb40 insert-fill
extern "C" void __fastcall f6ea470(void*, int, int, int, int, void*); // 0x006ea470 render pass
extern "C" void __fastcall f7c50b0(void*, int, int, int, int);      // 0x007c50b0
extern "C" void __fastcall f7c4be0(void*, int, void*, int);         // 0x007c4be0
extern "C" void __fastcall f7c3c20(void*, int, float*);             // 0x007c3c20 colour
extern "C" void __fastcall f7c3c50(void*, int, int);                // 0x007c3c50
extern "C" void __fastcall f6e9bf0(void*, int);                     // 0x006e9bf0 particle ctor
extern "C" void __fastcall f6e9330(void*, int, const void*);        // 0x006e9330 particle copy-ctor
extern "C" void __fastcall f6eabc0(void*, int, const void*);        // 0x006eabc0 particle assign
extern "C" void* __fastcall f6ed5b0(void*, int, void*, void*);      // 0x006ed5b0 particle grow-insert
extern "C" char __fastcall f6f1c40(void*, int, uint32_t_, uint32_t_, void**); // 0x006f1c40 lookup
extern "C" void* __fastcall f6f2050(void*, int, int, int);          // 0x006f2050 lookup pair
extern "C" void* __fastcall f67dd70(void*, int);                    // 0x0067dd70 singleton
extern "C" void __fastcall f6e9cc0(void*, int);                     // 0x006e9cc0 entity ctor
extern "C" void __fastcall f6eac80(void*, int, const void*);        // 0x006eac80 entity assign
extern "C" void __fastcall f6e7f30(void*, int);                     // 0x006e7f30 entity dtor
extern "C" void __fastcall f6eeae0(void*, int, const void*);        // 0x006eeae0 entity push-back
extern "C" void __fastcall fA7bf40(void*, int, void*, void*);       // 0x00a7bf40 entity map find

// refcounted pointer whose counter lives at +4 (plain, non-atomic)
static inline void AddRef4(void* p) { if (p) ++((int*)p)[1]; }
static inline void Release4(void* p)
{
    if (p) {
        int n = ((int*)p)[1] - 1;
        ((int*)p)[1] = n;
        if (n == 0) {
            ((int*)p)[1] = 1;
            _ReadWriteBarrier();
            ((void (__thiscall*)(void*, int))((void**)*(void**)p)[0])(p, 1);
        }
    }
}
static inline void VtCall0(void* p, int slot)
{
    ((void (__thiscall*)(void*))((void**)*(void**)p)[slot])(p);
}

struct Vec3p { char* mpBegin; char* mpEnd; char* mpCap; };
struct BucketVec { char* mpBegin; char* mpEnd; char* mpCap; char pad[8]; }; // 0x14

class cEffectsRenderer {
public:
    char m[0x3a0];

    void CullActive(int flags, void* viewer, int batch);      // 0x6efc70
    void BuildBatches(int a1, void* a2, int a3);              // 0x6efe90
    bool AddParticle(uint32_t_ id, const void* block, int* outIndex); // 0x6f0320
    char AddEntity(uint32_t_ a1, uint32_t_ a2, int a3, float a4);     // 0x6f05a0
};

static inline void ClearBucket(BucketVec* v)
{
    unsigned n = (unsigned)((v->mpEnd - v->mpBegin) >> 3);
    memcpy(v->mpBegin, v->mpEnd, (unsigned)(v->mpEnd - v->mpEnd));
    v->mpEnd = v->mpEnd - n * 8;
}

static inline void ClearU16Vec(Vec3p* v)
{
    unsigned n = (unsigned)((v->mpEnd - v->mpBegin) >> 1);
    memcpy(v->mpBegin, v->mpEnd, (unsigned)(v->mpEnd - v->mpEnd));
    v->mpEnd = v->mpEnd - n * 2;
}

// ---- 0x006efc70 ------------------------------------------------------------
// @ 0x006efc70
void cEffectsRenderer::CullActive(int flags, void* viewer, int batch)
{
    *(int*)(m + 0x1b0) = 0;
    *(int*)(m + 0x1b4) = 0;
    *(int*)(m + 0x37c) = 0;
    *(int*)(m + 0x380) = 0;
    *(int*)(m + 0x384) = 0;

    unsigned mask = 0;
    if (flags & 0x20000) mask = 8;
    if (flags & 0x40000) mask |= 0x40;

    if (!f7c4fd0(*(void**)viewer, 0))
        return;

    uint16_t_* vb = *(uint16_t_**)(m + 0x188);
    int n = (*(int*)(m + 0x18c) - (int)vb) >> 1;
    int kept = 0;
    for (int i = 0; i < n; i++) {
        char* e = *(char**)(m + 0x174) + vb[i] * 0x70;
        if (*(uint8_t_*)(e + 0x48) == 0) {
            *(uint8_t_*)(e + 0x49) = 0;
            continue;
        }
        if (f6ee140(*(void**)(e + 0x28), 0))
            f6e7ac0(this, 0, e);

        uint8_t_ fl = *(uint8_t_*)(e + 0x12);
        bool inMask = (fl & mask) == mask;
        if (fl & 0x10) {
            if (inMask)
                f6e7b50(this, 0, e);
        } else {
            float box[6];
            box[0] = *(float*)(e + 0x2c);
            box[1] = *(float*)(e + 0x30);
            box[2] = *(float*)(e + 0x34);
            box[3] = *(float*)(e + 0x38);
            box[4] = *(float*)(e + 0x3c);
            box[5] = *(float*)(e + 0x40);
            float d = *(float*)(*(char**)(e + 0x28) + 0x68) * *(float*)(e + 0x44);
            if (box[0] != g1533c74 && box[0] != -g1533c74) {
                box[0] -= d;
                box[1] -= d;
                box[2] -= d;
                box[3] += d;
                box[4] += d;
                box[5] += d;
            }
            if (inMask) {
                if (!(f700120(m + 0x260, 0, box, box + 3, 0x200) & 0x40))
                    f6e7b50(this, 0, e);
            }
        }
        vb[kept++] = vb[i];
    }

    Vec3p* v = (Vec3p*)(m + 0x188);
    int size = (int)((v->mpEnd - v->mpBegin) >> 1);
    if ((unsigned)kept <= (unsigned)size) {
        memcpy(v->mpBegin + kept * 2, v->mpEnd, (unsigned)(v->mpEnd - v->mpEnd));
        v->mpEnd = v->mpEnd - (((v->mpEnd - (v->mpBegin + kept * 2)) >> 1) * 2);
    } else {
        unsigned char zero = 0;
        f6ecb40(v, 0, v->mpEnd, kept - size, &zero);
    }
    f7c3c10(*(void**)viewer, 0);
}

// ---- 0x006efe90 ------------------------------------------------------------
// @ 0x006efe90
void cEffectsRenderer::BuildBatches(int a1, void* a2, int a3)
{
    *(int*)(m + 0x370) = 0;
    *(int*)(m + 0x374) = 0;
    *(int*)(m + 0x378) = 0;

    unsigned f = g16f9528;
    g16fa38c |= 0x8000;
    f |= 1;
    f |= 0x10;
    g16f9528 = f;
    g16f96a8 = g140afc4;
    g16f96ac = g140afc8;
    g16f96b0 = g140afcc;
    g16f96b4 = g140afd0;
    g16f96a0 = 4;
    float identity[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 0.0f };
    memcpy(g16fa4f0, identity, 0x40);
    g16fa380 = g16fa4f0;
    g16f9238 = 1;

    for (int b = 0; b < 4; b++)
        ClearBucket((BucketVec*)(m + 0x104 + b * 0x14));

    float cam[4];
    f7c3d30(*(void**)a2, 0, 0, 0, 0, cam);

    uint16_t_* vb = *(uint16_t_**)(m + 0x5c);
    char* base = *(char**)(m + 0x48);
    int n = (*(int*)(m + 0x60) - (int)vb) >> 1;
    int kept = 0;
    for (int i = 0; i < n; i++) {
        char* e = base + vb[i] * 0x70;
        if (*(uint8_t_*)(e + 0x48) == 0) {
            *(uint8_t_*)(e + 0x49) = 0;
            continue;
        }
        float dz = (*(float*)(e + 0x30) + *(float*)(e + 0x3c)) * g1471064 - cam[2];
        float dx = (*(float*)(e + 0x44) + *(float*)(e + 0x38)) * g1471064 - cam[0];
        float dy = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * g1471064 - cam[1];
        uint8_t_ bucket = *(uint8_t_*)(e + 0x13);
        float d2 = dx * dx + dy * dy + dz * dz;
        float r = *(float*)(e + 0x18);
        float keyf = d2 + (r + d2 * g1470f1c) * r;
        if (bucket < 4) {
            uint32_t_ bits = *(uint32_t_*)&keyf;
            uint32_t_ v0 = (bits | 0x8000000f) ^ (uint32_t_)((int)bits >> 31);
            uint32_t_ key = (v0 >> 4) +
                ((((uint32_t_)(int)*(int16_t_*)(e + 0x14) - 8) & 0xf) << 28);
            BucketVec* bv = (BucketVec*)(m + 0x104 + (bucket + 0xd) * 5 * 4);
            char* dst = bv->mpEnd;
            uint32_t_ rec[2];
            rec[0] = key;
            rec[1] = (uint32_t_)(size_t)e;
            if (dst < bv->mpCap) {
                bv->mpEnd = dst + 8;
                if (dst) {
                    *(uint32_t_*)dst = key;
                    *((void**)dst + 1) = e;
                }
            } else {
                f6ec390(bv, 0, dst, rec);
            }
        }
        if ((*(uint8_t_*)(e + 0x12) & 0x20) && *(uint8_t_*)(e + 0x13) > 0)
            *(uint8_t_*)(m + 0x357 + *(uint8_t_*)(e + 0x13)) = 1;
        else if (*(uint8_t_*)(e + 0x13) > 0)
            *(uint8_t_*)(m + 0x357 + *(uint8_t_*)(e + 0x13)) = 0;
        vb[kept++] = vb[i];
    }

    ClearU16Vec((Vec3p*)(m + 0x5c));

    for (int b = 0; b < 4; b++) {
        BucketVec* bv = (BucketVec*)(m + 0x104 + b * 0x14);
        unsigned char zero = 0;
        f6ec7c0(bv->mpBegin, bv->mpEnd, &zero);
    }

    f6ea470(this, 0, 0, a1, a3, *(void**)a2);

    for (int b = 1; b < 4; b++) {
        BucketVec* bv = (BucketVec*)(m + 0x104 + b * 0x14);
        bool draw = true;
        if (bv->mpBegin == bv->mpEnd) {
            void* obj = *(void**)(m + 0x25c);
            if (!((char (__thiscall*)(void*, int))((void**)*(void**)obj)[0x23])(obj, b - 1))
                draw = false;
        }
        if (draw) {
            void* viewer = *(void**)(m + 0x25c);
            int pair[2];
            pair[0] = -1;
            pair[1] = -1;
            ((void (__thiscall*)(void*, int, int*, int))((void**)*(void**)viewer)[0x2a])(viewer, b - 1, pair, 1);
            f7c50b0(*(void**)(m + 0x24c), 0, (int)*(void**)a2, 1, 1);
            f7c4be0(*(void**)(m + 0x24c), 0, pair, 1);
            if (*(uint8_t_*)(m + 0x357 + b)) {
                float col[4];
                col[0] = g1471064;
                col[1] = g1471064;
                col[2] = g1485720;
                col[3] = 0.0f;
                f7c3c20(*(void**)(m + 0x24c), 0, col);
            } else {
                float col[4];
                col[0] = 0.0f;
                col[1] = 0.0f;
                col[2] = 0.0f;
                col[3] = 0.0f;
                f7c3c20(*(void**)(m + 0x24c), 0, col);
            }
            f7c3c50(*(void**)(m + 0x24c), 0, 1);
        }
        if (bv->mpBegin != bv->mpEnd)
            f6ea470(this, 0, b, a1, a3, *(void**)(m + 0x24c));
    }
}

// ---- 0x006f0320 ------------------------------------------------------------
// @ 0x006f0320
bool cEffectsRenderer::AddParticle(uint32_t_ id, const void* block, int* outIndex)
{
    const uint32_t_* blk = (const uint32_t_*)block;
    uint32_t_ k0 = blk[0];
    uint32_t_ k1 = blk[1];
    void* ref = 0;
    uint32_t_ v18 = 0;
    uint32_t_ v1c = 0;

    if ((k0 & k1) != 0xffffffff) {
        if (k0 == 0x7f000000 && k1 == 0) {
            ref = g_pERS4();
        } else {
            f6f1c40(*(void**)(m + 0x40), 0, k0, k1, &ref);
        }
    }
    if (ref == 0) {
        if (*(uint8_t_*)(m + 0x1e4) == 0)
            return false;
        ref = g_pERS4();
    }

    if (((const uint8_t_*)block)[9] == 0xf) {
        uint32_t_* found = (uint32_t_*)f6f2050(*(void**)(m + 0x40), 0, (int)blk[6], (int)blk[7]);
        if (found) {
            v18 = found[0];
            v1c = found[1];
        } else {
            void* obj = f67dd70(0, 0);
            v18 = ((uint32_t_ (__thiscall*)(void*, int))((void**)*(void**)obj)[0xa])(
                obj, (int)blk[6]);
        }
    }

    int index;
    if (*(int*)(m + 0x19c) != *(int*)(m + 0x1a0)) {
        int* tail = *(int**)(m + 0x1a0);
        index = *(tail - 1);
        *(int**)(m + 0x1a0) = (int*)((char*)tail - 4);
        *outIndex = index;
    } else {
        Vec3p* v = (Vec3p*)(m + 0x174);
        char tmp[0x70];
        f6e9bf0(tmp, 0);
        index = (int)((v->mpEnd - v->mpBegin) / 0x70);
        *outIndex = index;
        if (v->mpEnd < v->mpCap) {
            char* slot = v->mpEnd;
            v->mpEnd = slot + 0x70;
            if (slot)
                f6e9330(slot, 0, tmp);
        } else {
            f6ed5b0(v, 0, v->mpEnd, tmp);
        }
        Release4(*(void**)(tmp + 0x28));
    }

    char* e = *(char**)(m + 0x174) + (*outIndex) * 0x70;
    uint8_t_ saved49 = *(uint8_t_*)(e + 0x49);

    char tmp2[0x70];
    f6e9bf0(tmp2, 0);
    f6eabc0(e, 0, tmp2);
    Release4(*(void**)(tmp2 + 0x28));

    *(uint32_t_*)e = id;
    memcpy(e + 8, block, 0x20);

    void** rslot = (void**)(e + 0x28);
    if (ref != *rslot) {
        AddRef4(ref);
        void* old = *rslot;
        *rslot = ref;
        Release4(old);
    }

    *(uint32_t_*)(e + 0x5c) = v18;
    *(uint32_t_*)(e + 0x60) = v1c;
    *(uint8_t_*)(e + 0x49) = saved49;
    f6e7ac0(this, 0, e);
    return true;
}

// ---- 0x006f05a0 ------------------------------------------------------------
// @ 0x006f05a0
char cEffectsRenderer::AddEntity(uint32_t_ a1, uint32_t_ a2, int a3, float a4)
{
    uint8_t_* b = *(uint8_t_**)(m + 0x40);
    uint32_t_ key[3];
    key[0] = 0;
    key[1] = a1;
    key[2] = a2;
    void* res = 0;
    fA7bf40(b + 0xa8, 0, &res, key);

    int* slots = *(int**)(b + 0xa8 + 4);
    int mask = *(int*)(b + 0xa8 + 8);
    int sentinel = slots[mask];

    void* found = 0;
    if ((int)a2 != sentinel)
        found = *(void**)((char*)(size_t)a2 + 8);

    if (found) {
        char ok = ((char (__thiscall*)(void*, uint32_t_, uint32_t_, void**, float))
                   ((void**)*(void**)found)[2])(found, a1, a2, &res, a4);
        if (!ok)
            return 0;
    } else {
        void* ref = 0;
        if ((a1 & a2) != 0xffffffff) {
            if (a1 == 0x7f000000 && a2 == 0) {
                ref = g_pERS4();
            } else {
                f6f1c40(b, 0, a1, a2, &ref);
            }
        }
        if (ref == 0) {
            if (*(uint8_t_*)(m + 0x1e4) == 0)
                return 0;
            ref = g_pERS4();
        }
        res = ref;
    }

    int* out = (int*)(size_t)a3;
    int index;
    Vec3p* v = (Vec3p*)(m + 0x1b8);
    if (*(int*)(m + 0x1cc) != *(int*)(m + 0x1d0)) {   // free-list non-empty
        int* tail = *(int**)(m + 0x1d0);
        index = *(tail - 1);
        *(int**)(m + 0x1d0) = (int*)((char*)tail - 4);
        char tmp[0x68];
        f6e9cc0(tmp, 0);
        f6eac80(v->mpBegin + index * 0x68, 0, tmp);
        f6e7f30(tmp, 0);
        *out = index;
    } else {
        char tmp[0x68];
        f6e9cc0(tmp, 0);
        f6eeae0(v, 0, tmp);
        f6e7f30(tmp, 0);
        index = (int)((v->mpEnd - v->mpBegin) / 0x68) - 1;
        *out = index;
    }

    char* e = v->mpBegin + (*out) * 0x68;
    void** slot0 = (void**)e;
    if (res != *slot0) {
        AddRef4(res);
        void* old = *slot0;
        *slot0 = res;
        Release4(old);
    }
    *(float*)(e + 0x14) = a4;
    *(uint32_t_*)(e + 0x54) = 0;
    *(uint32_t_*)(e + 0x58) = 0;
    *(uint32_t_*)(e + 0x5c) = 0;
    void** p60 = (void**)(e + 0x60);
    if (found != *p60) {
        if (found)
            VtCall0(found, 0);
        void* old = *p60;
        *p60 = found;
        if (old)
            VtCall0(old, 1);
    }
    *(uint32_t_*)(e + 0x64) = 0;
    return 1;
}
