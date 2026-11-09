// src/game/SPTerrain/SPTerrainResourceManager.cpp -- migrated from slice(s) s00f94660, s00f93790, s00f927c0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainResourceManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainMapBase.h"
#include "SP/cTerrainMapSet.h"
#include "SP/cTerrainStateMgr.h"
#include <new>
#include <math.h>

// ---- items of slice s00f927c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAAllocate(unsigned int size, const char* name, int, int, int, int);  // 0x00f473a0
void __cdecl op_delete(void*);                                                       // 0x00f47380
struct GmeRefCount {
    GmeRefCount() : mRefCount(0) {}
    virtual ~GmeRefCount() {}
    void AddRef() { ++mRefCount; }
    void Release() {
        int m = mRefCount;
        mRefCount = m - 1;
        if (m - 1 == 0) {
            mRefCount = 1;
            delete this;
        }
    }
    int mRefCount;                                          // +0x04
};
struct cSPVector3_s00f9_27c0 { float x, y, z; };
struct CObj {
    void  v0();                                             // generic vtbl slot 0
    void  v1();                                             // generic vtbl slot 1
    bool  IsA();                                            // 0x00f699a0
    void  DoB();                                            // 0x00f6bc10
    void  DoC();                                            // 0x00f678a0
    void  DoD(int);                                         // 0x00fc04b0
    void  DoE(int, int, int, int, int);                     // 0x00f9b8c0
    void  DoF();                                            // 0x004535d0
};
struct cTerrainStateMgr {
    cTerrainStateMgr(void*);                                // 0x00fbe130
};
void* __cdecl FUN_00fa23a0();                               // 0x00fa23a0
void* __cdecl FUN_00f48a70();                               // 0x00f48a70
void* __cdecl SP_PropertyManager();                         // 0x0067de30
bool  __cdecl SP_GetPropertyAsVector3(const void*, unsigned int, cSPVector3_s00f9_27c0*);  // 0x006a1110
void  __cdecl TerraBlend(float*, float, float);             // 0x00fc20e0
void  __cdecl SetEffectSeed(unsigned int);                  // 0x007dade0
struct cTerrainResourceManagerBase {
    virtual ~cTerrainResourceManagerBase() {}
    virtual void v1() {}
};
struct TerrainVec {
    void* mpBegin;                                          // +0x00
    void* mpEnd;                                            // +0x04
    void* mpCapacity;                                       // +0x08
    unsigned int mAlloc[2];                                 // +0x0c
};
struct cTerrainResourceManager : cTerrainResourceManagerBase, GmeRefCount {
    ~cTerrainResourceManager();                             // 0x00f93420
    void  GetVector(float*);                                // 0x00f931f0
    void* Create(void*, int, int, float);                   // 0x00f932f0
    int   GetCount(int);                                    // 0x00f933f0
    bool  GetPlanet(void*, int, int, int, float);           // 0x00f93490
    void* Get(int*);                                        // 0x00f93560

    unsigned int mPad0C;                                    // +0x0c
    TerrainVec   mVec0;                                     // +0x10
    TerrainVec   mVec1;                                     // +0x24
    TerrainVec   mVec2;                                     // +0x38
    TerrainVec   mVec3;                                     // +0x4c
    void*        m60;                                       // +0x60
    void*        m64;                                       // +0x64
};
// ---- items of slice s00f927c0 end

// ---- items of slice s00f93790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_vtblGmeRefCount;
extern int g_rdata149015c;
extern int g_rdata1490158;
extern "C" void _ReadWriteBarrier(void);
extern "C" void* FUN_0067dcd0();                        // 0x0067dcd0 ResourceMan::GetManager
extern "C" void* FUN_0067de30();                        // 0x0067de30 SP::PropertyManager
extern "C" void  FUN_00f47380(void*);                   // 0x00f47380 operator delete
extern "C" void* FUN_00926020(int, int, int, int, int, int); // 0x00926020 ZoneObject_new
extern "C" void* FUN_008d9f80(void*, int, int);         // 0x008d9f80 DatabasePackedFile ctor
extern "C" int   FUN_006a0ae0(void*, int, void*, void*); // 0x006a0ae0 eastl vector reserve
extern "C" int   FUN_006a0990(void*, int, void*, void*); // 0x006a0990 eastl vector probe
extern "C" void  FUN_00bed3e0(void*, void*);             // 0x00bed3e0 property refresh
extern "C" void* FUN_00425d30(void*, void*);             // 0x00425d30 Vec12_DoInsertValue
extern "C" void* FUN_004548d0(void*, int);               // 0x004548d0 vector set-size
extern "C" int   FUN_006a1110(void*, int, void*);        // 0x006a1110 GetPropertyAsVector3
extern "C" int   FUN_00fc2080(float, float);             // 0x00fc2080 TerraDistClass
extern "C" void* FUN_004e3e10(void*, void*);             // 0x004e3e10 SpVector<Key>::DoInsertKey
extern "C" void  FUN_0093a780(void*, void*, int, int);   // 0x0093a780 EA::IO::ReadInt32
extern "C" void  FUN_0093aa70(void*, const void*, int, int); // 0x0093aa70 EA::IO::WriteUint32
extern "C" int   FUN_006b4b60(void*, void*);             // 0x006b4b60 async-save
extern "C" void* FUN_006a1b90(void*, const char*);       // 0x006a1b90 cPropertyList ctor
extern "C" void  FUN_006a1710(void*, void*);             // 0x006a1710 cPropertyList::SetParent
extern "C" void  FUN_00512050(void*, void*, void*, void*); // 0x00512050 range construct
extern "C" void* FUN_00a11310(void*, void*, void*);      // 0x00a11310 copy to new storage
extern "C" void* FUN_00abced0(void*, void*, void*);      // 0x00abced0 copy_backward
extern "C" void* FUN_00b84c80(void*, void*, void*);      // 0x00b84c80 copy
extern "C" void* FUN_0041ea00(void*);                    // 0x0041ea00 Property::GetUInt
extern void* g_015fd918;   // 0x015fd918 SP app-properties cDirectPropertyList*
extern void* gEmptyString16; // 0x01667bac eastl::gEmptyString16
#pragma intrinsic(_ReadWriteBarrier)
struct Vector3 {
    float x, y, z;
};
template <class T>
class SpVector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    T* mpPool;
    T* mpStorage;
    T* erase(T* first, T* last);
};
class Self {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();

private:
    char pad4[8];

public:
    char mFlag;
    SpVector<Vector3> mVec[4];
};
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned short wchar16;
struct EVariant { u32 w0, w1, w2, w3; u16 flags; u16 typeId; };
struct Key { u32 mInstance, mType, mGroup; };
typedef int   (__thiscall *FM0)(void*);
typedef int   (__thiscall *FM1)(void*, int);
typedef int   (__thiscall *FM2)(void*, int, int);
typedef int   (__thiscall *FM3)(void*, int, int, int);
typedef int   (__thiscall *FM4)(void*, int, int, int, int);
typedef int   (__thiscall *FM5)(void*, int, int, int, int, int);
typedef void* (__thiscall *FP0)(void*);
typedef void* (__thiscall *FP1)(void*, int);
extern "C" void* FUN_006b1f90(u32);                     // 0x006b1f90 SP_GetSaveArea
extern "C" void  FUN_00427fd0(EVariant*, void*);        // 0x00427fd0 Variant_SetInt
extern "C" void  FUN_00422f40(EVariant*, void*);        // 0x00422f40 Variant_SetVec12
extern "C" void  FUN_0093db80(EVariant*, int);          // 0x0093db80 Variant::Destruct
extern "C" int   FUN_0093dd80(EVariant*, u16, u16, const void*, u32, u32); // 0x0093dd80 Variant::Construct
extern "C" void* FUN_00f473a0(u32, const char*, int, int, int, int); // 0x00f473a0 EAAllocate
extern "C" int   FUN_00931fa0(const wchar16*);          // 0x00931fa0 EA::IO::File::Exists
extern "C" void* FUN_0041e050(void*, const wchar16*, ...); // 0x0041e050 WStr_Format
extern "C" u32 __fastcall FUN_00a68fb0(void*, int, u32);// 0x00a68fb0 RandomUint32Uniform
extern "C" int   FUN_006a25a0(void*, u32);               // 0x006a25a0 cDirectPropertyList::GetDescription
extern "C" void  FUN_007dade0(u32);                      // 0x007dade0 SP::SetEffectSeed
// ---- items of slice s00f93790 end

// ---- items of slice s00f94660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_006b4840();                       // 0x006b4840  async-save preamble
extern "C" void* FUN_004c0410(void*, int);             // 0x004c0410  eastl string resize
typedef unsigned int   uintptr_t;
typedef void  (__thiscall *FnV)(void*);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void  (__thiscall *FnVI)(void*, int);
typedef void  (__thiscall *FnVIII)(void*, int, int, int);
typedef int   (__thiscall *FnIV)(void*, int, int, int, int);
typedef int   (__thiscall *FnIV5)(void*, int, int, int, int, int);
typedef int   (__thiscall *FnIIII)(void*, int, int, int);
typedef void* (__thiscall *FnPV)(void*, void*);
typedef void  (__thiscall *FnVV)(void*, void*);
extern "C" void  FUN_00931fd0(const wchar16*);         // 0x00931fd0  EA::IO::File::Remove
extern "C" int   FUN_00931ff0(const wchar16*, const wchar16*, int); // 0x00931ff0  EA::IO::File::Move
extern "C" int   FUN_0013cc50c(const wchar16*, const wchar16*); // 0x13cc50c  msvcr90!_wcsicmp
extern wchar16* gEmptyString16_s00f9_4660;                 // 0x01667bac  eastl::gEmptyString16
// ---- items of slice s00f94660 end

// @ 0x00f931f0
void cTerrainResourceManager::GetVector(float* out)
{
    void** vt = *(void***)this;
    void* obj = ((void*(__thiscall*)(void*, float*))vt[1])(this, out);
    if (obj != 0)
        ((CObj*)obj)->v0();

    cSPVector3_s00f9_27c0 a;
    a.x = 0.5f;
    a.y = 0.5f;
    a.z = 0.5f;
    SP_GetPropertyAsVector3(obj, 0x3a23f98, &a);

    float b[4];
    b[0] = a.x;
    b[1] = a.y;
    b[2] = a.z;
    TerraBlend(b, a.z, a.y);

    out[0] = (b[0] + a.x) * 0.5f;
    out[1] = a.x;
    out[2] = a.y;
    out[3] = a.z;

    cSPVector3_s00f9_27c0 c;
    c.x = 32.0f;
    c.y = 32.0f;
    c.z = 500.0f;
    SP_GetPropertyAsVector3(obj, 0x3a23f99, &c);
    out[4] = c.z;

    if (obj != 0)
        ((CObj*)obj)->v1();
}

// @ 0x00f932f0
void* cTerrainResourceManager::Create(void* obj, int a3, int a4, float a5)
{
    int v1 = *(int*)((char*)obj + 0x10);
    int v2 = *(int*)((char*)obj + 8);
    void** ovt = *(void***)obj;
    int local = 0;
    bool ok = ((bool(__thiscall*)(void*, unsigned int, int*))ovt[0x24 / 4])(obj, 0x2a907b7, &local);
    if (ok && *(short*)(*(int*)&local + 0x12) == 10) {
        int* r = (int*)FUN_00fa23a0();
        v2 = *r;
    }
    void* mgr = FUN_00fa23a0();
    if (mgr != 0)
        ((CObj*)mgr)->v0();
    void* state = EAAllocate(0xc40, "Terrain/ResourceManager/cTerrainStateMgr", 0, 0, 0, 0);
    if (state != 0)
        state = new (state) cTerrainStateMgr(mgr);
    else
        state = 0;
    *(void**)((char*)mgr + 0x20c) = state;
    ((CObj*)state)->DoD(0);
    *(int*)((char*)mgr + 0x1cc) = v2;
    void** mvt = *(void***)mgr;
    ((void(__thiscall*)(void*, void*))mvt[0x114 / 4])(mgr, this);
    ((void(__thiscall*)(void*))mvt[0x128 / 4])(mgr);
    ((void(__thiscall*)(void*))mvt[0xa0 / 4])(mgr);
    SetEffectSeed((unsigned int)v2);
    int cond = (local == 0) ? 1 : 0;
    ((CObj*)mgr)->DoE(0, 0, cond, a3, a4);
    ((void(__thiscall*)(void*))mvt[1])(mgr);
    (void)v1; (void)a5;
    return mgr;
}

// @ 0x00f933f0
int cTerrainResourceManager::GetCount(int idx)
{
    int* p = (int*)((char*)this + 0x10 + idx * 0x14);
    return (p[1] - p[0]) / 12;
}

// @ 0x00f93420
cTerrainResourceManager::~cTerrainResourceManager()
{
    _ReadWriteBarrier();
    void* p = m64;
    if (p != 0) {
        void* sub = (char*)p + 4;
        void** vt = *(void***)sub;
        ((void(__thiscall*)(void*))vt[1])(sub);
    }

    TerrainVec* vec = (TerrainVec*)((char*)this + 0x10);
    TerrainVec* q = vec + 4;
    int i = 3;
    for (;;) {
        void* d = (--q)->mpBegin;
        if (d != 0 && *(int*)((char*)d - 4) != 0)
            op_delete(d);
        if (--i < 0)
            break;
    }
}

// @ 0x00f93490
bool cTerrainResourceManager::GetPlanet(void* out, int a3, int a4, int a5, float a6)
{
    void* e = FUN_00f48a70();
    if (!((CObj*)e)->IsA()) {
        e = FUN_00f48a70();
        ((CObj*)e)->DoB();
    }
    e = FUN_00f48a70();
    ((CObj*)e)->DoC();

    cSPVector3_s00f9_27c0 local;
    local.x = *(float*)((char*)out + 0);
    local.y = *(float*)((char*)out + 4);
    local.z = *(float*)((char*)out + 8);

    void** vt = *(void***)this;
    void* obj = ((void*(__thiscall*)(void*, cSPVector3_s00f9_27c0*))vt[1])(this, &local);
    if (obj != 0) {
        void** ovt = *(void***)obj;
        ((void(__thiscall*)(void*))ovt[0])(obj);
        ((void(__thiscall*)(void*, unsigned int, int*))ovt[0x24 / 4])(obj, 0x3ad556a, &a5);
    }
    void* res = Create(obj, a3, a4, a6);
    if (res != 0) {
        *(void**)out = res;
        ((CObj*)res)->v0();
        if (obj != 0)
            ((CObj*)obj)->v1();
        return true;
    }
    if (obj != 0)
        ((CObj*)obj)->v1();
    return false;
}

// @ 0x00f93560
void* cTerrainResourceManager::Get(int* p)
{
    void* pm = SP_PropertyManager();
    int local = 0;
    void** pvt = *(void***)pm;
    bool ok = ((bool(__thiscall*)(void*, int, int, int*))pvt[0x2c / 4])(pm, p[0], p[2], &local);
    if (!ok) {
        unsigned int key = (unsigned int)p[2];
        if ((key & 0xff0000) != 0x840000) {
            if (local != 0)
                ((CObj*)local)->v1();
            return 0;
        }
        unsigned int idx = (key >> 8) & 0xff;
        if (idx >= 0xb0 && idx <= 0xb3) {
            TerrainVec* v = (TerrainVec*)((char*)this + 0x10 + (idx - 0xb0) * 0x14);
            if (v->mpBegin == v->mpEnd) {
                if (local != 0)
                    ((CObj*)local)->v1();
                return 0;
            }
        }
    }
    if (local != 0)
        ((CObj*)local)->v1();
    return 0;
}

// @ 0x00f93790
extern "C" void __stdcall FUN_00f93790(void* ctx)
{
    u32* p = (u32*)ctx;
    void* local = 0;
    void* pm = FUN_0067de30();
    if (local) { void* t = local; local = 0; ((FM0)(*(void***)t)[1])(t); }
    u8 ok = (u8)((FM3)(*(void***)pm)[0x2c / 4])(pm, p[0], p[2], (int)&local);
    if (ok) {
        void* obj = local;
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x3ad5568);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x3ad5569);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x43b29e1);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x43b29e2);
        EVariant v; v.w0 = v.w1 = v.w2 = v.w3 = 0; v.flags = 0; v.typeId = 0;
        int zero = 0;
        FUN_00427fd0(&v, &zero);
        ((FM2)(*(void***)obj)[0x14 / 4])(obj, 0x3ad556a, (int)&v);
        if (v.flags & 4) FUN_0093db80(&v, 0);
        void* mgr = FUN_0067dcd0();
        void* sa = FUN_006b1f90(0x31389b5);
        ((FM3)(*(void***)mgr)[0x20 / 4])(mgr, (int)obj, 0, (int)sa);
    }
    if (local) { void* t = local; local = 0; ((FM0)(*(void***)t)[1])(t); }
}

// @ 0x00f938b0
extern "C" void FUN_00f938b0(void* vec)
{
    void* mgr = FUN_0067dcd0();
    u32 block[4];
    block[0] = 0x1490124; block[1] = 0; block[2] = 0; block[3] = 0;
    ((FM2)(*(void***)mgr)[0x34 / 4])(mgr, (int)&block[1], (int)&block[0]);
    void* pm = FUN_0067de30();
    int count = (int)((u32)(block[0] - (u32)vec) / 0xc);
    ((FM2)(*(void***)pm)[0x3c / 4])(pm, (int)vec, count);
    void* sa = FUN_006b1f90(0x31389b5);
    int n = ((FM2)(*(void***)sa)[0x30 / 4])(sa, (int)&block[0], (int)&block[1]);
    if (n > 0) {
        int base = (int)block[1];
        for (int i = 0; i < n; ++i)
            ((FM1)(*(void***)sa)[0x40 / 4])(sa, base + i);
    }
    if (block[0] && *(u32*)(block[0] - 4)) FUN_00f47380((void*)block[0]);
}

// @ 0x00f939b0
void* __fastcall FUN_00f939b0()
{
    int zero = 0;
    int* p = (int*)EAAllocate(0x68, "Terrain/ResourceManager/cTerrainResourceManager", zero, zero, zero, zero);
    if (p != 0) {
        p[2] = zero;
        p[1] = (int)&g_vtblGmeRefCount;
        _ReadWriteBarrier();
        *((char*)p + 0xc) = (char)zero;
        p[0] = (int)&g_rdata149015c;
        p[1] = (int)&g_rdata1490158;
        _ReadWriteBarrier();
        p[4] = zero;
        p[5] = zero;
        p[6] = zero;
        p[9] = zero;
        p[10] = zero;
        p[0xb] = zero;
        p[0xe] = zero;
        p[0xf] = zero;
        p[0x10] = zero;
        p[0x13] = zero;
        p[0x14] = zero;
        p[0x15] = zero;
        *((char*)p + 0x60) = (char)zero;
        p[0x19] = zero;
        return p;
    }
    return 0;
}

// @ 0x00f93a20
extern "C" void __fastcall FUN_00f93a20(void* self, int, int position, int first, int last, int arg4)
{
    (void)arg4;
    if (first == last) return;
    u32* v = (u32*)self;
    u32 n = (u32)(last - first) / 0xc;
    if (n <= ((v[2] - v[1]) / 0xc)) {
        int mpEnd = (int)v[1];
        u32 nMove = (u32)(mpEnd - position) / 0xc;
        if (n < nMove) {
            int tail = mpEnd - (int)n * 0xc;
            u32 local = 0;
            FUN_00512050(&local, (void*)tail, (void*)mpEnd, (void*)mpEnd);
            v[1] = (u32)mpEnd + n * 0xc;
            FUN_00abced0((void*)position, (void*)tail, (void*)mpEnd);
            FUN_00b84c80((void*)first, (void*)last, (void*)position);
            return;
        }
        // Construct the input tail past the end, slide the old tail right, then
        // drop the input head into the gap.
        int fplus = first + (int)nMove * 0xc;
        u32 outA = 0;
        FUN_00512050(&outA, (void*)fplus, (void*)last, (void*)mpEnd);
        v[1] = (u32)mpEnd + (n - nMove) * 0xc;
        int mpEnd2 = (int)v[1];
        u32 outB = 0;
        FUN_00512050(&outB, (void*)position, (void*)mpEnd, (void*)mpEnd2);
        v[1] = (u32)mpEnd2 + nMove * 0xc;
        FUN_00abced0((void*)first, (void*)fplus, (void*)(position + (int)nMove * 0xc));
        return;
    }
    // Grow: copy [begin,position) to fresh storage, construct the input there,
    // copy [position,end) after it, then swap in the new storage.
    u32 size = (v[1] - v[0]) / 0xc;
    u32 newCap = size * 2;
    if (size == 0) newCap = 1;
    if (newCap <= n + size) newCap = n + size;
    void* buf = 0;
    if (newCap != 0)
        buf = FUN_00f473a0(newCap * 0xc, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    FUN_00a11310((void*)v[0], (void*)position, buf);
    void* mid = (char*)buf + ((u32)(position - v[0]));
    u32 outC = 0;
    FUN_00512050(&outC, (void*)first, (void*)last, mid);
    void* newEnd = (void*)outC;
    FUN_00a11310((void*)position, (void*)v[1], newEnd);
    void* final = (char*)newEnd + ((u32)(v[1] - position));
    u32 oldb = v[0];
    if (oldb && oldb != v[4]) FUN_00f47380((void*)oldb);
    v[0] = (u32)buf;
    v[1] = (u32)final;
    v[2] = (u32)buf + newCap * 0xc;
}

// @ 0x00f93c00
bool __fastcall FUN_00f93c00(Self* self)
{
    if (self->mFlag != 0) {
        self->mFlag = 0;
        SpVector<Vector3>* p = &self->mVec[0];
        int n = 4;
        do {
            p->erase(p->mpBegin, p->mpEnd);
            p = (SpVector<Vector3>*)((char*)p + 0x14);
            --n;
        } while (n != 0);
        self->v9();
    }
    return true;
}

// @ 0x00f93c40
extern "C" u8 __fastcall FUN_00f93c40(void* self, int, int param)
{
    void* mgr = FUN_0067dcd0();
    void* db = *(void**)((char*)self + 0x64);
    if (db) {
        ((FM3)(*(void***)mgr)[0x50 / 4])(mgr, 0, (int)db, 0);
        ((FM0)(*(void***)db)[0x1c / 4])(db);
        ((FM0)(*(void***)db)[8 / 4])(db);
        db = *(void**)((char*)self + 0x64);
        if (db) {
            *(void**)((char*)self + 0x64) = 0;
            ((FM0)(*(void***)((char*)db + 4))[4 / 4])((char*)db + 4);
        }
    }
    ((FM0)(*(void***)self)[0x24 / 4])(self);
    if (param == 0) return 1;

    void* str[3];
    str[0] = gEmptyString16; str[1] = gEmptyString16; str[2] = (void*)0x1667bae;
    void* sa = FUN_006b1f90(0x4729a47);
    void* name = (void*)((FP1)(*(void***)sa)[0x28 / 4])(sa, param);
    FUN_0041e050(str, (const wchar16*)0x14901e4, name);   // L"%ls%ls.pld"

    u8 result = 0;
    if (FUN_00931fa0((const wchar16*)str[0])) {
        void* raw = FUN_00926020(0x388, (int)"Terrain/ResourceManager/DatabasePackedFile", 0, 0, 0, 0);
        void* newdb = 0;
        if (raw) newdb = FUN_008d9f80(raw, 0, 0);
        void* old = *(void**)((char*)self + 0x64);
        if (newdb != old) {
            if (newdb) ((FM0)(*(void***)((char*)newdb + 4))[0 / 4])((char*)newdb + 4);
            *(void**)((char*)self + 0x64) = newdb;
            if (old) ((FM0)(*(void***)((char*)old + 4))[4 / 4])((char*)old + 4);
        }
        void* cur = *(void**)((char*)self + 0x64);
        ((FM0)(*(void***)cur)[4 / 4])(cur);
        ((FM1)(*(void***)cur)[0x2c / 4])(cur, (int)str[0]);
        if ((u8)((FM3)(*(void***)cur)[0x18 / 4])(cur, 1, 3, 0)) {
            ((FM3)(*(void***)mgr)[0x50 / 4])(mgr, 1, (int)cur, 0xfffffc18);
            result = 1;
        }
    }
    if ((((u32)((char*)str[2] - (char*)str[0]) & ~1u) > 2) && str[0])
        FUN_00f47380(str[0]);
    return result;
}

// @ 0x00f93dd0
extern "C" void __fastcall FUN_00f93dd0(void* self, int, u32 seed, void* obj)
{
    FUN_007dade0(seed);

    Key vecBuf[24];
    Key* vbeg = vecBuf;
    Key* vend = vecBuf;
    Key* vcap = vecBuf + 24;
    Key* vpool = vecBuf;
    u32 i;
    for (i = 0x40cf84e; i < 0x40cf858; ++i) {
        u32 a = 0, b = 0;
        if ((u8)FUN_006a0ae0(obj, (int)i, &a, &b)) {
            u32 r = FUN_00a68fb0((void*)0x016778dc, 0, a);
            Key* src = (Key*)b + r;
            if (vend < vcap) {
                if (vend) *vend = *src;
                ++vend;
            } else {
                FUN_00425d30(vend, src);
                ++vend;
            }
            ((FM1)(*(void***)obj)[0x18 / 4])(obj, (int)i);
        }
    }

    if (vbeg != vend) {
        Key extra[24];
        Key* ebeg = extra;
        Key* eend = extra;
        u32 a = 0, b = 0;
        if ((u8)FUN_006a0ae0(obj, 0x3abb0af, &a, &b)) {
            FUN_00bed3e0(&a, &b);
            u32 cnt = a;
            Key* src = (Key*)b;
            for (u32 k = 0; k < cnt; ++k) { *eend++ = *src++; }
        }
        void* selfv = (char*)self + 0x10;
        FUN_00f93a20(selfv, 0, (int)ebeg, (int)eend, 0, 0);
        EVariant v; v.w0 = v.w1 = v.w2 = v.w3 = 0; v.flags = 0; v.typeId = 0;
        FUN_0093dd80(&v, 0x20, 0x98, ebeg, 0xc, (u32)((char*)eend - (char*)ebeg) / 0xc);
        ((FM2)(*(void***)obj)[0x14 / 4])(obj, 0x3abb0af, (int)&v);
        if (v.flags & 4) FUN_0093db80(&v, 0);
        if (ebeg && ebeg != extra + 24) FUN_00f47380(ebeg);
    }

    u32 a = 0, b = 0;
    if ((u8)FUN_006a0990(obj, 0x40d6a39, &a, &b)) {
        u32 r = FUN_00a68fb0((void*)0x016778dc, 0, a);
        Key* src = (Key*)b + r;
        EVariant v;
        v.w0 = src->mInstance; v.w1 = src->mType; v.w2 = src->mGroup; v.w3 = 0;
        v.typeId = 0x31; v.flags = 2;
        ((FM2)(*(void***)obj)[0x14 / 4])(obj, 0x3a23f99, (int)&v);
        if (v.flags & 4) FUN_0093db80(&v, 0);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x40d6a39);
    }

    if (vbeg && vbeg != vecBuf) FUN_00f47380(vbeg);
}

// @ 0x00f940a0
extern "C" u8 __fastcall FUN_00f940a0(void* self, int)
{
    char* s = (char*)self;
    if (s[0xc]) return 1;
    s[0xc] = 1;
    s[0x60] = 1;

    void* sa = FUN_006b1f90(0x11ac19c);
    u8 fromSave = 1;
    u32 keyBlk[3];
    keyBlk[0] = 0x5528db9; keyBlk[1] = 0x5528d58; keyBlk[2] = 0x40a00200;
    u32 local5c = 0;
    if ((u8)((FM4)(*(void***)sa)[0x34 / 4])(sa, (int)keyBlk, (int)&local5c, 1, 6)) {
        void* stream = (void*)((FP0)(*(void***)self)[0x18 / 4])(self);
        u32 v = 0;
        FUN_0093a780(stream, &v, 1, 0);
        if (((int)v < 0) && ((v & 0x7fffffff) == 2)) {
            fromSave = 0;
            char* p = s + 0x10;
            int n4 = 4;
            do {
                u32 cnt = 0;
                FUN_0093a780(stream, &cnt, 1, 0);
                FUN_004548d0(p, (int)cnt);
                FUN_0093a780(stream, *(void**)p, (int)((cnt * 0xc) >> 2), 0);
                p += 0x14;
            } while (--n4);
        }
        ((FM0)(*(void***)self)[0x24 / 4])(self);
    }

    if (fromSave) {
        void* pm = FUN_0067de30();
        u32 slot = 0;
        u32 v2[3];
        v2[0] = v2[1] = v2[2] = 0;
        u32 k;
        for (k = 0xa3; (int)k <= 0xab; ++k) {
            int key = (int)(((k & 0xff) | 0x418400) << 8);
            ((FM2)(*(void***)pm)[0x48 / 4])(pm, key, (int)v2);
            int count = (int)(v2[1] - v2[0]) >> 2;
            for (int idx = 0; idx < count; ++idx) {
                if (slot) { void* t = (void*)slot; slot = 0; ((FM0)(*(void***)t)[1])(t); }
                u8 ok = (u8)((FM3)(*(void***)pm)[0x2c / 4])(pm, *(int*)(v2[0] + idx * 4), key, (int)&slot);
                if (ok && !((FM1)(*(void***)(void*)slot)[0x1c / 4])((void*)slot, 0x6369b24)) {
                    int pv = 0;
                    if (slot && ((FM2)(*(void***)(void*)slot)[0x24 / 4])((void*)slot, 0xd2f669ec, (int)&pv) &&
                        *(u16*)(pv + 0x12) == 0xa) {
                        void* q = (*(u8*)(pv + 0x10) & 0x30) ? *(void**)pv : (void*)pv;
                        if (*(u32*)q == 0) continue;
                    }
                    u32 v3[3];
                    if (FUN_006a1110((void*)slot, 0x3a23f98, v3)) {
                        int dist = FUN_00fc2080(*(float*)&v3[1], *(float*)&v3[2]);
                        Key nk;
                        nk.mInstance = *(u32*)(v2[0] + idx * 4);
                        nk.mType = 0;
                        nk.mGroup = (u32)key;
                        char* bucket = s + 0x10 + dist * 0x14;
                        Key* end = *(Key**)(bucket + 4);
                        if (end < *(Key**)(bucket + 8)) {
                            *end = nk;
                            *(Key**)(bucket + 4) = end + 1;
                        } else {
                            FUN_004e3e10(bucket, &nk);
                        }
                    }
                }
            }
        }
        if (slot) { void* t = (void*)slot; ((FM0)(*(void***)t)[4 / 4])(t); }
    }

    {
        void* wsa = FUN_006b1f90(0x31389b5);
        int wv[3];
        wv[0] = wv[1] = wv[2] = 0;
        int res = (int)((FM5)(*(void***)self)[0x34 / 4])(self, (int)wv, (int)&wv[1], 2, 6, 1);
        if ((u8)res) {
            void* stream = (void*)((FP0)(*(void***)(void*)wv[1])[0x18 / 4])((void*)wv[1]);
            u32 marker = 0x80000002;
            FUN_0093aa70(stream, &marker, 1, 0);
            char* p = s + 0x10;
            int n4 = 4;
            do {
                u32 cnt = (u32)(*(u32*)(p + 4) - *(u32*)p) / 0xc;
                FUN_0093aa70(stream, &cnt, 1, 0);
                FUN_0093aa70(stream, *(void**)p, (int)(((cnt * 0xc) >> 2)), 0);
                p += 0x14;
            } while (--n4);
            ((FM0)(*(void***)(int)wv[1])[0x24 / 4])((void*)wv[1]);
        }
        if (wv[0] && *(u32*)(wv[0] - 4)) FUN_00f47380((void*)wv[0]);
    }

    ((FM0)(*(void***)self)[0x24 / 4])(self);
    return 1;
}

// @ 0x00f94480
extern "C" void* __fastcall FUN_00f94480(void* self, int, int orig1, int orig2, int orig3)
{
    (void)orig1;
    void* pm = FUN_0067de30();
    void* local = 0;
    if (!(u8)((FM3)(*(void***)pm)[0x2c / 4])(pm, orig2, orig3, (int)&local)) {
        if (local) { void* t = local; ((FM0)(*(void***)t)[1])(t); }
        return 0;
    }
    if (!local) return 0;
    if (((FM1)(*(void***)local)[0x1c / 4])(local, 0x6369b24)) {
        void* t = local; ((FM0)(*(void***)t)[1])(t);
        return 0;
    }
    {
        int pv = 0;
        if (((FM2)(*(void***)local)[0x24 / 4])(local, 0xd2f669ec, (int)&pv) &&
            *(u16*)(pv + 0x12) == 0xa) {
            void* q = FUN_0041ea00((void*)pv);
            if (*(u32*)q < 1) {
                void* t = local; ((FM0)(*(void***)t)[1])(t);
                return 0;
            }
        }
    }

    void* list = FUN_00f473a0(0x38, "Terrain/ResourceManager/cPropertyList", 0, 0, 0, 0);
    void* cls = 0;
    if (list) cls = FUN_006a1b90(list, "PlanetDefinition");

    void* appProps = g_015fd918;
    if (FUN_006a25a0(appProps, 0x636d04e)) {
        ((FM1)(*(void***)cls)[0x34 / 4])(cls, (int)self);
    } else if ((orig3 & 0xff00) == 0xa100 && FUN_006a25a0(appProps, 0x636d04d)) {
        ((FM1)(*(void***)cls)[0x34 / 4])(cls, (int)self);
    } else {
        FUN_006a1710(cls, self);
    }

    FUN_00f93dd0(self, 0, *(u32*)orig2, cls);
    ((FM3)(*(void***)pm)[0x34 / 4])(pm, (int)cls, *(int*)orig2, *(int*)(orig2 + 8));

    EVariant v; v.w0 = v.w1 = v.w2 = v.w3 = 0; v.flags = 0; v.typeId = 0;
    v.typeId = 0x20; v.flags = 2;
    u32 vec[3];
    vec[0] = (u32)orig3; vec[1] = 0xb1b104; vec[2] = (u32)orig3;
    FUN_00422f40(&v, vec);
    ((FM2)(*(void***)cls)[0x14 / 4])(cls, 0x3d03f84, (int)&v);
    if (v.flags & 4) FUN_0093db80(&v, 0);

    void* sa = FUN_006b1f90(0x31389b5);
    FUN_006b4b60(cls, sa);

    if (local) { void* t = local; ((FM0)(*(void***)t)[1])(t); }
    return cls;
}

// @ 0x00f94660
extern "C" int FUN_00f94660(int self, void* db, int asset, int mode, int listArg)
{
    uint8_t local6 = 0;
    int local8 = 0;
    int localc = 0;
    if (!((FnIV5)(*(void***)db)[0x34 / 4])(db, asset, (int)&localc, 6, 1, mode))
        return 0;
    void* r = (void*)((FnP)(*(void***)localc)[0x18 / 4])((void*)localc);
    int ok = 0;
    if (r) {
        void* io = (void*)((FnP)(*(void***)r)[0x1c / 4])(r);
        FUN_004c0410(io, 0x20);
        if (io) {
            void* w = (void*)((FnP)(*(void***)localc)[0x18 / 4])((void*)localc);
            int wr = 0;
            if (w != 0)
                wr = ((FnIIII)(*(void***)w)[0x30 / 4])(w, 0, (int)(*(uint32_t*)io), 0);
            if (w == 0 || !wr)
                goto fail;
        }
        if (listArg) {
            ((FnV)(*(void***)listArg)[4 / 4])((void*)listArg);
        }
        // common finish: write the stream then read it back
        ((FnV)(*(void***)localc)[0x24 / 4])((void*)localc);
        if (localc) {
            void* t = (void*)localc;
            localc = 0;
            ((FnV)(*(void***)t)[8 / 4])(t);
        }
        if (!((FnIV5)(*(void***)db)[0x34 / 4])(db, asset, (int)&localc, 2, 1, 1))
            goto fail;
        void* r2 = (void*)((FnP)(*(void***)localc)[0x18 / 4])((void*)localc);
        ok = 0;
        if (!r2)
            goto fail;
        ((FnVV)(*(void***)r2)[0x38 / 4])(r2, (void*)(*(uint32_t*)io));
        ((FnV)(*(void***)localc)[0x24 / 4])((void*)localc);
        ok = 1;
    }
fail:
    if (localc)
        ((FnV)(*(void***)localc)[8 / 4])((void*)localc);
    return ok;
}

// @ 0x00f94820
extern "C" uint8_t __fastcall FUN_00f94820(void* self, int, void* pathArg)
{
    struct Ctx {
        void*  mVecA[3];   //  0..0xb   (eastl vector<pair>?)
        void*  mVecB[3];   // 0xc..0x17
        void*  mVtbl;      // 0x18  = 0x1490124
        void*  mVtbl2;     // 0x1c
        void*  mWStrA[3];  // 0x20  (basic_string<wchar16>)
        void*  mWStrB[3];  // 0x2c
        void*  mWStrC[3];  // 0x38
        void*  pDb;        // 0x44  DatabasePackedFile*
    };
    Ctx* c = (Ctx*)((char*)self - 0x3c);   // real object base
    (void)c;

    FUN_006b4840();
    void* mgr = FUN_0067dcd0();
    void* saveArea = FUN_006b1f90(0x4729a47);
    void* stream = (void*)((FnP)(*(void***)saveArea)[0x28 / 4])(saveArea);

    void* mVecA[3] = { 0, 0, 0 };
    void* mVecB[3] = { 0, 0, 0 };
    void* mVtbl = (void*)0x1490124;
    void* handle = (void*)((FnPV)(*(void***)mgr)[0x38 / 4])(mgr, mVecB);
    (void)mVtbl;

    void* strA[3];
    strA[0] = gEmptyString16_s00f9_4660; strA[1] = gEmptyString16_s00f9_4660; strA[2] = (void*)0x1667bae;
    FUN_0041e050(strA, (const wchar16*)0x1490258, stream);  // L"%lstemp.pld"

    void* dbf = (void*)FUN_00926020(0x388, (int)"Terrain/ResourceManager/DatabasePackedFile", 0, 0, 0, 0);
    void* db;
    if (!dbf) {
        db = 0;
    } else {
        db = FUN_008d9f80(dbf, 0, 0);
        if (db)
            ((FnV)(*(void***)*(void**)((char*)db + 4))[0 / 4])((void*)db);
    }
    (void)handle;

    ((FnV)(*(void***)db)[4 / 4])(db);
    ((FnVV)(*(void***)db)[0x2c / 4])(db, strA[0]);
    ((FnVIII)(*(void***)db)[0x18 / 4])(db, 2, 2, 0);

    int n = (int)((FnIV)(*(void***)mgr)[0x48 / 4])(mgr, 0xb1b104, -1, 0, 0);
    int good = 0;
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            void* res = (void*)((FnPI)(*(void***)db)[0xc / 4])(db, *(uint32_t*)((char*)mVecB[0] + i * 4));
            void* cmp = (void*)((FnPI)(*(void***)db)[0xc / 4])(db, i);
            int mode = 0;
            if ((int)((FnP)(*(void***)db)[0xc / 4]) == (int)cmp || 1) {
                // best-effort: pick the smaller key
                mode = 0;
            }
            if (!FUN_00f94660((int)res, db, (int)cmp, mode, (int)mVecA))
                ++good;
        }
    }
    ((FnV)(*(void***)db)[0x1c / 4])(db);
    ((FnV)(*(void***)db)[8 / 4])(db);

    if (good != 0) {
        if (mVecA[0] && *(uint32_t*)((char*)mVecA[0] - 4))
            FUN_00f47380(mVecA[0]);
        ((FnV)(*(void***)*(void**)((char*)db + 4))[4 / 4])((void*)db);
        if (mVecB[0])
            FUN_00f47380(mVecB[0]);
        if (strA[0])
            FUN_00f47380(strA[0]);
        return 0;
    }

    void* strB[3];
    strB[0] = gEmptyString16_s00f9_4660; strB[1] = gEmptyString16_s00f9_4660; strB[2] = (void*)0x1667bae;
    FUN_0041e050(strB, (const wchar16*)0x1490238, (void*)(uintptr_t)0); // L"%lslastSave.pld"
    void* strC[3];
    strC[0] = gEmptyString16_s00f9_4660; strC[1] = gEmptyString16_s00f9_4660; strC[2] = (void*)0x1667bae;
    FUN_0041e050(strC, (const wchar16*)0x14901e4, strB[0], mVecA[2]);   // L"%ls%ls.pld"

    void* mine = (void*)((char*)self + 0x64 - 0x3c);
    (void)mine;
    void* seed = *(void**)((char*)self + 0x64);
    if (seed) {
        const wchar16* s1 = (const wchar16*)((FnP)(*(void***)seed)[0x28 / 4])(seed);
        if (FUN_0013cc50c(s1, gEmptyString16_s00f9_4660) == 0) {
            ((FnVIII)(*(void***)db)[0x50 / 4])(db, 0, (int)seed, 0);
            ((FnV)(*(void***)seed)[0x1c / 4])(seed);
            ((FnV)(*(void***)seed)[8 / 4])(seed);
            if (seed) {
                *(void**)((char*)self + 0x64) = 0;
                ((FnV)(*(void***)((char*)seed + 4))[4 / 4])((char*)seed + 4);
            }
        }
    }
    FUN_00931fd0((const wchar16*)strB[0]);
    int mv1 = FUN_00931ff0((const wchar16*)strB[0], (const wchar16*)mVecA[2], 1);
    uint8_t mv2 = (uint8_t)FUN_00931ff0((const wchar16*)strB[0], (const wchar16*)mVecA[2], 1);
    (void)mv1;
    if (!*(void**)((char*)self + 0x64))
        ((FnVI)(*(void***)self)[0x1c / 4])(self, (int)mVecA[2]);

    if (strA[0] && strA[0] != (void*)0x1667bac)
        FUN_00f47380(strA[0]);
    if (strB[0] && strB[0] != (void*)0x1667bac)
        FUN_00f47380(strB[0]);
    if (strC[0])
        FUN_00f47380(strC[0]);
    if (mVecA[0] && *(uint32_t*)((char*)mVecA[0] - 4))
        FUN_00f47380(mVecA[0]);
    ((FnV)(*(void***)*(void**)((char*)db + 4))[4 / 4])((void*)db);
    if (mVecB[0])
        FUN_00f47380(mVecB[0]);
    return mv2;
}
