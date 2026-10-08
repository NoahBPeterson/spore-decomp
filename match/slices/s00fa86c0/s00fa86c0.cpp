// Slice s00fa86c0 -- 0x00fa8850 SP::cTerrainSphere::GenerateImpostorUpdate (retail layout, 2022 bytes).
// Re-renders one cube-face mip of the planet impostor textures (a = face 0..5, b = pass 0..2):
//   1. clears the cached impostor state (this+0x8a0), and for passes 0..2 sets the level byte of the pass's
//      texture, locks it, notifies the resource manager and unlocks it;
//   2. chains itself: next face (a+1, b), next pass (0, b+1), or (6,3) after the last face of pass 2;
//   3. otherwise (a >= 5, b >= 2) builds the "planetImpostor" and "planetAtmoImpostor" mesh jobs: property
//      lists (created on demand with a parent list), a cMITextureSet / cMaterialInfo pair each, a mesh builder,
//      and GetModelAsGameMeshes jobs queued after the sphere's own job (this+0x894).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH)
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void  __cdecl operator_delete__(void* p);                      // 0x00f47380

extern unsigned g_impostorParentGroup;                          // 0x015b11fc

// Intrusive refcounted object whose deleting dtor is vtable slot 0 (inline AddRef / Release).
struct RefObj
{
    virtual void Destroy(int del);
    volatile long mnRefCount;      // +4
};
inline void RefAddRef(RefObj* o) { _InterlockedIncrement(&o->mnRefCount); }
inline void RefRelease(RefObj* o)
{
    if (_InterlockedDecrement(&o->mnRefCount) == 0)
    {
        _InterlockedExchange(&o->mnRefCount, 1);
        o->Destroy(1);
    }
}

// Smart pointer for RefObj-derived objects with inline refcounting.
template <class T>
struct RCPtr
{
    T* p;
    RCPtr(T* x) : p(x)
    {
        if (p)
            RefAddRef(p);
    }
    ~RCPtr()
    {
        if (p)
            RefRelease(p);
    }
};

struct cJob
{
    void* fn;                      // +0x00 job callback
    unsigned arg;                  // +0x04
    char pad[0x10];
    int flag;                      // +0x18
    int Release();                 // 0x00690120
    void Queue();                  // 0x006909b0
};
struct JobRef
{
    cJob* p;
    JobRef() : p(0) {}
    ~JobRef()
    {
        if (p)
            p->Release();
    }
    void Reset()
    {
        cJob* t = p;
        if (t)
        {
            p = 0;
            t->Release();
        }
    }
};

// Virtual (slot 0 AddRef / slot 1 Release) refcounted interface.
struct IRef
{
    virtual void AddRef();
    virtual void Release();
};
struct IPropList : IRef
{
    void SetParent(IPropList* parent);                 // 0x006a1710
};
struct cPropertyList : IPropList
{
    char pad[0x38 - 4];
    cPropertyList(const char* name);                   // 0x006a1b90
};
// Out-of-line AutoRefCount<T>::operator= (0x004535d0 / 0x00b5f950).
struct PLRef
{
    IPropList* p;
    PLRef() : p(0) {}
    ~PLRef()
    {
        if (p)
            p->Release();
    }
    PLRef& operator=(IPropList* x);                    // 0x004535d0
    void Reset()
    {
        IPropList* t = p;
        if (t)
        {
            p = 0;
            t->Release();
        }
    }
};

struct MeshRef : IRef {};   // placeholder; element type of the mesh vector

struct IMeshBuilder : IRef
{
    virtual void s2(), s3(), s4(), s5(), s6(), s7(), s8(), s9(), s10(), s11();
    virtual void s12(), s13(), s14(), s15(), s16(), s17(), s18(), s19(), s20(), s21();
    virtual void s22(), s23(), s24(), s25(), s26(), s27(), s28(), s29(), s30(), s31();
    virtual void s32(), s33(), s34(), s35(), s36(), s37(), s38(), s39(), s40(), s41();
    virtual void s42();
    virtual RefObj* GetMesh();                         // +0xac
};
struct BuilderRef
{
    IMeshBuilder* p;
    BuilderRef(IMeshBuilder* x) : p(x)
    {
        if (p)
            p->AddRef();
    }
    ~BuilderRef()
    {
        if (p)
            p->Release();
    }
    BuilderRef& operator=(IMeshBuilder* x);            // 0x00b5f950
};
IMeshBuilder* __cdecl NewMeshBuilder();                // 0x00715de0 (new cMeshBuilder, 0x228 "Graphics")

// Vector of refcounted mesh pointers (EASTL vector, inline dtor).
struct MeshHolder
{
    RefObj* p;
    MeshHolder(RefObj* x) : p(x)
    {
        if (p)
            RefAddRef(p);
    }
    ~MeshHolder()
    {
        if (p)
            RefRelease(p);
    }
};
struct RefVec
{
    MeshHolder* mpBegin;
    MeshHolder* mpEnd;
    MeshHolder* mpCapacity;
    unsigned    mAllocator;
    RefVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void PushBack(const MeshHolder& h);                          // 0x0041ef20
    void DestroyRange(MeshHolder* first, MeshHolder* last);      // 0x004243e0
    ~RefVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

struct cMITextureSet
{
    char pad[0x70];
    cMITextureSet();                                             // 0x0040d010
    void InsertResource(int slot, void* res);                    // 0x0077cb10
    void setSlotU0(int slot, int v);                             // 0x00777a60
    void setSlotU1(int slot, int v);                             // 0x00777a80
    void setSlotV0(int slot, int v);                             // 0x00777aa0
};
struct cMaterialInfo : RefObj
{
    char pad[0x1c - 8];
    cMaterialInfo();                                             // 0x0077d1d0
    void PushBack(cMITextureSet* ts);                            // 0x0077d970
};

struct PropMgr
{
    virtual void v0(), v1(), v2(), v3(), v4(), v5(), v6(), v7(), v8(), v9(), v10();
    virtual char GetPropertyList(unsigned id, unsigned group, IPropList** out);        // +0x2c
    virtual void v12();
    virtual void SetPropertyList(IPropList* pl, unsigned id, unsigned group);          // +0x34
};
PropMgr* __cdecl GetPropertyManager();                           // 0x0067de30

struct LockInfo { void* data; int a, b, c, d, e, f; };
struct Tex
{
    char pad[0x12];
    unsigned char level;                                         // +0x12
    int  Lock(int mode, int zero, LockInfo* out);                // 0x011ef750
    void Unlock(LockInfo* info);                                 // 0x011ef880
};
struct TexObj { Tex* tex; unsigned flags; };
struct ResMgrA
{
    virtual void v0(), v1(), v2(), v3(), v4(), v5(), v6(), v7(), v8(), v9(), v10(), v11(), v12();
    virtual void Load(TexObj* t);                                // +0x34
};
struct ResMgrB
{
    virtual void v0(), v1(), v2(), v3(), v4(), v5(), v6(), v7(), v8(), v9(), v10(), v11();
    virtual void Update(unsigned a, unsigned b, void* data);     // +0x30
};
ResMgrA* __cdecl GetResMgrA();                                   // 0x0067dd60
ResMgrB* __cdecl GetResMgrB();                                   // 0x0067dda0

struct IScheduler
{
    virtual void v0(), v1(), v2(), v3();
    virtual void AddJob(cJob** out);                             // +0x10
};
IScheduler* __cdecl GetScheduler();                              // 0x0068f4d0
void* __cdecl GetSaveArea(unsigned id);                          // 0x006b1f90
extern char FUN_00f96d20;                                        // job callback

bool __cdecl GetModelAsGameMeshes(cJob** pJob, RefVec* vec, unsigned id3, unsigned id4, cMaterialInfo* rc5,
                                  void* vec6, IPropList* list, void* a8, void* a9, void* saveArea, void* key,
                                  cJob* chain);                  // 0x007573a0

struct ImpostorState
{
    void Reset();                                                // 0x00f99ff0
};

namespace SP
{
struct cTerrainSphere
{
    char           pad0[0x18];
    unsigned       keyInstance;       // +0x18
    unsigned       keyType;           // +0x1c
    unsigned       keyGroup;          // +0x20
    char           pad1[0x884 - 0x24];
    TexObj*        faceTex[3];        // +0x884 .. +0x88c
    void*          res3;              // +0x890
    cJob*          mJob;              // +0x894
    unsigned       f898;
    unsigned       f89c;
    ImpostorState* mImpostorState;    // +0x8a0
    unsigned       f8a4;
    unsigned       f8a8;

    void BuildImpostorMesh(IMeshBuilder* b, const wchar_t* name, float scale, int flag);   // 0x00f9a040
    void PostImpostorStep(int a, int b);                                                   // 0x00fa0560
    void GenerateImpostorUpdate(int a, int b);                                             // 0x00fa8850
};

struct ResKey { unsigned instance, type, group; };

// @ 0x00fa8850
void cTerrainSphere::GenerateImpostorUpdate(int a, int b)
{
    mImpostorState->Reset();
    if (b < 3)
    {
        int levels[6] = {3, 2, 0, 1, 4, 5};
        Tex* tex = 0;
        if (b == 0 || b == 1 || b == 2)
        {
            TexObj* h = faceTex[b];
            if (!(h->flags & 1))
                GetResMgrA()->Load(h);
            tex = h->tex;
        }
        tex->level = (unsigned char)levels[a];
        LockInfo info;
        if (!tex->Lock(2, 0, &info))
            return;
        GetResMgrB()->Update(f898, f89c, info.data);
        tex->Unlock(&info);
    }
    if (a < 5)
    {
        PostImpostorStep(a + 1, b);
        return;
    }
    if (b < 2)
    {
        PostImpostorStep(0, b + 1);
        return;
    }
    if (a == 5 && b == 2)
    {
        PostImpostorStep(6, 3);
        return;
    }

    PropMgr* pm = GetPropertyManager();
    BuilderRef builder(NewMeshBuilder());
    BuildImpostorMesh(builder.p, L"planetImpostor", 1.0f, 1);

    ResKey keyA;
    keyA.instance = keyInstance;
    keyA.type = keyType;
    keyA.group = keyGroup;
    ResKey keyB = keyA;
    keyA.type = 0xe6bce5;
    keyB.type = 0xe6bce5;
    unsigned groupB = (keyGroup & 0xe0ff28ff) | 0x2800;
    keyA.group = (keyA.group & 0xe7ff28ff) | 0x7002800;

    cMITextureSet* ts = new ("Terrain/Sphere/cMITextureSet", 0, 0, 0, 0) cMITextureSet();
    ts->InsertResource(0, faceTex[0]);
    ts->setSlotU0(0, 3);
    ts->setSlotU1(0, 2);
    ts->setSlotV0(0, 2);
    ts->InsertResource(1, faceTex[1]);
    ts->setSlotU0(1, 3);
    ts->setSlotU1(1, 2);
    ts->setSlotV0(1, 2);
    ts->InsertResource(2, faceTex[2]);
    ts->setSlotU0(2, 3);
    ts->setSlotU1(2, 2);
    ts->setSlotV0(2, 2);
    ts->InsertResource(3, res3);
    ts->setSlotU0(3, 3);
    ts->setSlotU1(3, 2);
    ts->setSlotV0(3, 2);

    RCPtr<cMaterialInfo> mi(new ("Terrain/Sphere/cMaterialInfo", 0, 0, 0, 0) cMaterialInfo());
    mi.p->PushBack(ts);

    IScheduler* sched = GetScheduler();
    cJob** pMyJob = &mJob;
    if (mJob)
    {
        cJob* old = mJob;
        *pMyJob = 0;
        old->Release();
    }
    sched->AddJob(pMyJob);
    (*pMyJob)->arg = f8a8;
    (*pMyJob)->fn = &FUN_00f96d20;
    (*pMyJob)->flag = 1;

    PLRef pl2;
    PLRef pl1;
    if (!pm->GetPropertyList(keyB.instance, groupB, &pl1.p))
    {
        pl1 = new ("Terrain/PlanetImpostor/ImpostorPropertyList", 0, 0, 0, 0) cPropertyList("PlanetImpostor");
        pl2.Reset();
        if (pm->GetPropertyList(0x752f1cd8, g_impostorParentGroup, &pl2.p))
            pl1.p->SetParent(pl2.p);
        pm->SetPropertyList(pl1.p, keyB.instance, groupB);
    }

    JobRef job;
    RefVec v;
    {
        MeshHolder tmp(builder.p->GetMesh());
        v.PushBack(tmp);
    }
    cJob* chain = *pMyJob;
    IPropList* listArg = pl1.p;
    job.Reset();
    GetModelAsGameMeshes(&job.p, &v, keyB.instance, groupB, mi.p, 0, listArg, 0, 0, GetSaveArea(0x11ac1ac), 0, chain);

    builder = NewMeshBuilder();
    BuildImpostorMesh(builder.p, L"planetAtmoImpostor", 1.2f, 0);

    PLRef pl3;
    if (!pm->GetPropertyList(keyA.instance, keyA.group, &pl3.p))
    {
        pl3 = new ("Terrain/PlanetImpostor/ImpostorPropertyList", 0, 0, 0, 0) cPropertyList("PlanetImpostorAtmosphere");
        pl3.p->SetParent(pl2.p);
        pm->SetPropertyList(pl3.p, keyA.instance, keyA.group);
    }

    cMITextureSet* ts2 = new ("Terrain/Sphere/cMITextureSet", 0, 0, 0, 0) cMITextureSet();
    ts2->InsertResource(0, res3);
    ts2->setSlotU0(0, 3);
    ts2->setSlotU1(0, 2);
    ts2->setSlotV0(0, 2);

    RCPtr<cMaterialInfo> mi2(new ("Terrain/Sphere/cMaterialInfo", 0, 0, 0, 0) cMaterialInfo());
    mi2.p->PushBack(ts2);

    JobRef job2;
    RefVec v2;
    {
        MeshHolder tmp(builder.p->GetMesh());
        v2.PushBack(tmp);
    }
    cJob* chain2 = *pMyJob;
    IPropList* listArg2 = pl3.p;
    job2.Reset();
    GetModelAsGameMeshes(&job2.p, &v2, keyA.instance, keyA.group, mi2.p, 0, listArg2, 0, 0, GetSaveArea(0x11ac1ac), 0, chain2);

    if (job.p && job2.p)
    {
        job.p->Queue();
        job2.p->Queue();
        (*pMyJob)->Queue();
    }
}
}  // namespace SP
