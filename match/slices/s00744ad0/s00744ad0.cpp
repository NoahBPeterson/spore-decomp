// Slice s00744ad0 -- SP::cModelWorld continuation + eastl container helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- masked externs
struct Model;
struct cModelInstance;
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);
void  __cdecl EA_Free(void*);       // 0x00f47380
void* __cdecl EA_New2(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
void  __cdecl MemMove(void*, const void*, unsigned); // 0x13cc480 msvcr90!memmove
int   __cdecl VecDoInsertValue();   // 0x011e0744
void  __cdecl PropertyGetFloatArray(void*, const char*, void*, void*); // 0x006a08b0
bool  __stdcall Check434b0(void*);   // 0x007434b0
bool  __cdecl RuntimeModelBuilder_GetRuntimeMeshes(cModelInstance*, int, int, int, int); // 0x007763b0

// ---------------------------------------------------------------- class stubs
struct intrusive_node { intrusive_node* mpNext; intrusive_node* mpPrev; };

struct Model {
    void*    mpWorld;                 // +0x00
    uint32_t mFlags;                  // +0x04
    char     pad08[0x38];             // +0x08
    int      mnRefCount;              // +0x40
    char     pad44[0x94 - 0x44];      // +0x44
};

struct cModelInstance {
    void SetBoneTable(int a, int b);
    void SetBoneCallback(int a, int b, int c, int d);
    void SetAnimationGroupTransform(int a, int b);
    int  GetRegionMaterialInfo(int region);
    void SetDynamicDraw(int a, int b);
    int  GetDeformationHandles(void* a, void* b);
    int  GetArenaResource();
    bool SelectMesh(int a, int b);
    cModelInstance* Init();
    void SetFlags(int a, int b);
    void Method742cf0(void* a);
    void ConstructFromGameModelResource(void* a);
    int  GetAnimationIDs();
    void SetActive(int a, int b, int c, float d, int e);
    void MoveToTime(int a, int b, float c);
    void SetWeight(int a, int b, float c);
};

struct cMWModelInternal : intrusive_node, Model {
    void*    mpField9c;               // abs +0x9c
    void*    mpFieldA0;
    void*    mpFieldA4;
    void*    mpFieldA8;
    void*    mpFieldAC;
    void*    mpFieldB0;
    cModelInstance* mAnim[6];         // +0xb4
    char     pad_cc[0xd4 - 0xcc];
    int      mFieldD4;                // +0xd4
    int      mFieldD8;                // +0xd8
    void*    mpFieldDC;               // +0xdc
    char     pad_e0[0x124 - 0xe0];
    float    mField124;               // +0x124
    uint8_t  mField128;               // +0x128
    uint8_t  mField129;               // +0x129
    char     pad_12a[0x138 - 0x12a];
    uint32_t mFlags138;               // +0x138
};

struct cLoadQueue { void StallUntilLoaded(uint32_t); };

// IModelWorld vtable stub -- slot 0x58 (index 22) = StallUntilLoaded.
struct IModelWorld {
    virtual int   AddRef();
    virtual int   Release();
    virtual void  dtor();
    virtual void* CreateModel(uint32_t, uint32_t, int);
    virtual int   GetNumModelsLoading();
    virtual bool  CallOnLoad(Model*, void*, void*);
    virtual void  PreloadModels(void*, int);
    virtual bool  ModelsHavePreloaded(int);
    virtual void* CreateGroup(int, void*&);
    virtual void* m24();
    virtual void* m28();
    virtual bool  m2c(void*);
    virtual bool  m30(void*);
    virtual bool  m34(void*);
    virtual bool  m38(void*);
    virtual bool  m3c(void*);
    virtual bool  m40(void*);
    virtual bool  m44(void*);
    virtual bool  m48(void*);
    virtual bool  m4c(void*);
    virtual void  GetModelResourceIDs(Model*, void*, void*);
    virtual void  GetRegionList(Model*, void*);
    virtual void  StallUntilLoaded(Model*);
};

struct EffectInner;
struct EffectEntry {
    uint32_t     mID;         // +0x00
    uint32_t     mPad4;       // +0x04
    EffectInner* mpInner;     // +0x08
    char         pad0C[0x44 - 0x0C];
    uint8_t      mEnabled;    // +0x44
    char         pad45[3];
};  // 0x48

struct EffectInner {
    virtual void v00(); virtual void v04(); virtual void v08(int); virtual void v0C(int);
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual bool v44(int, int, int); virtual bool v48(int, int, int);
    virtual bool v4C(int, int);
};

struct cModelWorld : IModelWorld {
    int   Getb20(Model*);
    int   GetNumAnimations(Model*);
    int   GetAnimationIDs(Model*, uint32_t*);
    int   GetAnimationMoveToTimes(Model*, int, int);
    int   GetDeformationAnimationIDs(Model*, int, int);
    float StallGetBoundingBox(Model*);
    void* GetNumAnimationGroups(Model*);
    void  GetModelResourceIDs(Model*, uint32_t*, uint32_t*);
    void  StallUntilLoaded2(Model*, uint32_t);
    void  AnimAction(Model*, int, int, float, int);
    void  MoveToTime(Model*, int, float, int);
    void  SetWeight(Model*, int, float, int);
    bool  GetAnimationRange(Model*, int, int, float&, float&);
    int   GetNumBones(Model*);
    int   GetPoseTransforms(Model*, void*, int);
    int   GetBoneTransforms(Model*, void*);
    int   GetBoneIDs(Model*, void*);
    int   GetBoneParents(Model*, void*);
    bool  IsVecEmpty(int);
    void* VecClear();
    bool  CallOnLoad(Model*, void*, void*);

    void  SetBoneTable(Model*, int, int);
    void  SetBoneCallback(Model*, int, int, int, int);
    void  SetAnimationGroupTransform(Model*, int, int);
    int   GetMaterialInfo(Model*, int);
    void  SetDynamicDraw(Model*, int, int);
    int   GetNumLODs(Model*);
    void  SetLOD(Model*, int);
    void  SetSomeFloat(Model*, float);
    void  SetEffectEnabled(Model*, char, char, int);
    char  ForEachEffectA(Model*, int, int, int, int);
    char  ForEachEffectB(Model*, int, int, int, int);
    char  ForEachEffectC(Model*, int, int, int);
    int   GetDeformationHandles(Model*, void*, void*);
    bool  GetRuntimeMeshes(Model*, int, int, int, int);
    bool  CheckFlag(Model*, int);
    bool  SelectMesh(Model*, int, int, char);
    uint32_t GetSlot(int);
    int   HACK_GetArenaResource(Model*);
    void  FillColor(int*);
    void* ReleaseRef();
    void  ReleaseRefs();
    void* DequeInsert(int, int);
};

// ---------------------------------------------------------------- helpers
void* cModelWorld::VecClear() { *(uint32_t*)this = 0; return this; }

// 0x00744ad0
void cModelWorld::SetBoneTable(Model* model, int a, int b) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->SetBoneTable(a, b);
        ++i;
        ++p;
    } while (i < 4);
}

// 0x00744b10
void cModelWorld::SetBoneCallback(Model* model, int a, int b, int c, int d) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->SetBoneCallback(c, d, a, b);
        ++i;
        ++p;
    } while (i < 4);
}

// 0x00744b60
void cModelWorld::SetAnimationGroupTransform(Model* model, int a, int b) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->SetAnimationGroupTransform(a, b);
        ++i;
        ++p;
    } while (i < 4);
}

// 0x00744ba0
int cModelWorld::GetMaterialInfo(Model* model, int region) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    if (region < 0)
        return *(int*)((char*)m + 0xd8);
    cModelInstance* inst = *(cModelInstance**)((char*)m + 0x9c);
    return inst->GetRegionMaterialInfo(region);
}

// 0x00744be0
void cModelWorld::SetDynamicDraw(Model* model, int a, int b) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance** p = (cModelInstance**)((char*)m + 0x9c);
    int n = 4;
    do {
        if (*p)
            (*p)->SetDynamicDraw(a, b);
        ++p;
    } while (--n);
}

// 0x00744c30
int cModelWorld::GetNumLODs(Model* model) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int count = 0, i = 0;
    int* p = (int*)((char*)m + 0x9c);
    do {
        if (*p == 0)
            return count;
        ++i;
        ++count;
        ++p;
    } while (i < 4);
    return count;
}

// 0x00744f80
int cModelWorld::GetDeformationHandles(Model* model, void* a, void* b) {
    this->StallUntilLoaded(model);
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = *(cModelInstance**)((char*)m + 0x9c);
    if (inst)
        return inst->GetDeformationHandles(a, b);
    return 0;
}

// 0x00744fc0
bool cModelWorld::GetRuntimeMeshes(Model* model, int a, int b, int c, int d) {
    this->StallUntilLoaded(model);
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = *(cModelInstance**)((char*)m + 0x9c);
    if (inst)
        return RuntimeModelBuilder_GetRuntimeMeshes(inst, a, b, c, d);
    return false;
}

// 0x00745010
bool cModelWorld::CheckFlag(Model* model, int a) {
    this->StallUntilLoaded(model);
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* p = *(cModelInstance**)((char*)m + 0xac);
    if (p) {
        if (Check434b0((void*)a))
            return true;
    }
    return false;
}

// 0x00745050
bool cModelWorld::SelectMesh(Model* model, int a, int b, char c) {
    this->StallUntilLoaded(model);
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = c ? *(cModelInstance**)((char*)m + 0xac)
                             : *(cModelInstance**)((char*)m + 0x9c);
    if (inst)
        return inst->SelectMesh(a, b);
    return false;
}

// 0x007450a0
uint32_t cModelWorld::GetSlot(int i) {
    return *(uint32_t*)((char*)this + 0x1cc + i * 0x20);
}

// 0x00745110
int cModelWorld::HACK_GetArenaResource(Model* model) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = *(cModelInstance**)((char*)m + 0x9c);
    if (inst)
        return inst->GetArenaResource();
    return 0;
}

// 0x00744c70
void cModelWorld::SetLOD(Model* model, int lod) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    if (lod < 0) {
        m->mFlags138 &= 0xefffffff;
        if (m->mFieldD4 == 0) {
            uint32_t tmp = 0;
            PropertyGetFloatArray(*(void**)((char*)m + 0x98), (const char*)0x2e33a81,
                                  &tmp, &m->mFieldD4);
            m->mField129 = (uint8_t)tmp;
            return;
        }
    } else {
        m->mFlags138 |= 0x10000000;
        m->mField128 = (uint8_t)lod;
        m->mFieldD4 = 0;
        m->mField129 = 0;
    }
}

// 0x00744cf0
struct Prop {
    char pad[0x12];
    uint16_t mType;                 // +0x12
    float* GetFloat();
};
struct PropHolder {
    virtual bool Find(int id, void** out);   // slot 9 (0x24)
};
void cModelWorld::SetSomeFloat(Model* model, float v) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    if (0.0f <= v) {
        m->mFlags138 |= 0x20000000;
        m->mField124 = v;
    } else {
        m->mFlags138 &= 0xdfffffff;
        m->mField124 = 0.0f;
        PropHolder* h = *(PropHolder**)((char*)m + 0x98);
        if (h) {
            void* tmp = 0;
            if (h->Find(0x2a907b8, &tmp) && ((Prop*)tmp)->mType == 0xd) {
                m->mField124 = *((Prop*)tmp)->GetFloat();
            }
        }
    }
}

// 0x00745520
struct SlotVec { int* mp; int next(int idx); };
int SlotVec::next(int idx) {
    uint32_t* p = (uint32_t*)(mp + idx * 5);
    uint32_t v = *p;
    do {
        if ((v >> 0x1e) & 1)
            return 0x3fffffff;
        v = p[5];
        p += 5;
        ++idx;
    } while ((int)v < 0);
    return idx;
}

// 0x00745660
int SlotCount(uint32_t* first, uint32_t* last) {
    int n = 0;
    do {
        uint32_t* p = first;
        if (last == first)
            return n;
        do {
            first = p + 5;
            bool b = (*p >> 0x1e) & 1;
            if (b)
                break;
            p = first;
            bool b2 = (*first >> 0x1f) & 1;
            if (!b2)
                break;
        } while (true);
        ++n;
    } while (true);
}

// ---------------------------------------------------------------- effect iteration
// 0x00744d80
void cModelWorld::SetEffectEnabled(Model* model, char a, char b, int id) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (!e || !e->mpInner)
        return;
    do {
        if (id == 0 || (id == (int)e->mID && e->mPad4 == 0)) {
            if ((*(uint32_t*)((char*)m + 0xc) >> 0x13) & 1) {
                int arg = (b == 0);
                if (a)
                    e->mpInner->v08(arg);
                else
                    e->mpInner->v0C(arg);
            }
            e->mEnabled = a;
        }
        e = (EffectEntry*)((char*)e + 0x48);
    } while (e->mpInner);
}

// 0x00744e10
char cModelWorld::ForEachEffectA(Model* model, int a, int b, int c, int id) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (!e)
        return 0;
    EffectInner* inner = e->mpInner;
    char result = 0;
    while (inner) {
        if (id == 0 || (id == (int)e->mID && e->mPad4 == 0)) {
            if (inner->v44(a, b, c))
                result = 1;
        }
        inner = *(EffectInner**)((char*)e + 0x50);
        e = (EffectEntry*)((char*)e + 0x48);
    }
    return result;
}

// 0x00744e90
char cModelWorld::ForEachEffectB(Model* model, int a, int b, int c, int id) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (!e)
        return 0;
    EffectInner* inner = e->mpInner;
    char result = 0;
    while (inner) {
        if (id == 0 || (id == (int)e->mID && e->mPad4 == 0)) {
            if (inner->v48(a, b, c))
                result = 1;
        }
        inner = *(EffectInner**)((char*)e + 0x50);
        e = (EffectEntry*)((char*)e + 0x48);
    }
    return result;
}

// 0x00744f10
char cModelWorld::ForEachEffectC(Model* model, int a, int b, int id) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (!e)
        return 0;
    EffectInner* inner = e->mpInner;
    char result = 0;
    while (inner) {
        if (id == 0 || (id == (int)e->mID && e->mPad4 == 0)) {
            if (inner->v4C(a, b))
                result = 1;
        }
        inner = *(EffectInner**)((char*)e + 0x50);
        e = (EffectEntry*)((char*)e + 0x48);
    }
    return result;
}

// 0x007456a0
void SlotAssign(int* dst, int* src) {
    if (((-1 < *src) || (*dst < 0)) && (-1 < *src)) {
        if (*dst < 0) {
            if (dst + 1 != 0) {
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                dst[4] = src[4];
                *dst = *src;
                return;
            }
        } else {
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
        }
    }
    *dst = *src;
}

// 0x00743bb0 (shared with slice s00743b20)
void __stdcall DestroyRange(void** first, void** last) {
    for (; first < last; ++first)
        if (*first)
            EA_Free(*first);
}

// 0x00745630
struct RangeDtor { void Destroy(void**, void**); };
void __fastcall DequeDoPopFront(int* self) {
    if (*self) {
        ((RangeDtor*)self)->Destroy((void**)self[5], (void**)(self[9] + 4));
        if (*self)
            EA_Free((void*)*self);
    }
}

// 0x007455e0
struct ChunkObj { virtual int AddRef(); virtual int Release(); };
void __fastcall DestroyChunk(int param_1) {
    ChunkObj* p = *(ChunkObj**)(*(int*)(param_1 + 8) + 4);
    if (p)
        p->Release();
    if (*(int*)(param_1 + 0xc))
        EA_Free(*(void**)(param_1 + 0xc));
    int* q = (int*)(*(int*)(param_1 + 0x14) + 4);
    *(int**)(param_1 + 0x14) = q;
    int v = *q;
    *(int*)(param_1 + 0xc) = v;
    *(int*)(param_1 + 0x10) = v + 0xe0;
    *(int*)(param_1 + 8) = *(int*)(param_1 + 0xc);
}

// 0x00745560
void ChunkFind(uint32_t* out, int* cur, int* start, int* end, int** seg, int key) {
    while (cur != end && *cur != key) {
        cur += 7;
        if (cur == end) {
            seg += 1;
            cur = *seg;
            end = cur + 0x38;
            start = cur;
        }
    }
    out[2] = (uint32_t)end;
    out[3] = (uint32_t)seg;
    out[0] = (uint32_t)cur;
    out[1] = (uint32_t)start;
}

// 0x00745710
int* DequeAdvance(int* self, int n) {
    int d = (self[0] - self[1]) / 0x1c + n;
    if (d < 8) {
        self[0] = self[0] + n * 0x1c;
        return self;
    }
    int i = ((d + 0x1000000 + ((d + 0x1000000) >> 31 & 7)) >> 3) - 0x200000;
    int* p = (int*)(self[3] + i * 4);
    self[3] = (int)p;
    int v = *p;
    self[1] = v;
    self[2] = v + 0xe0;
    self[0] = self[1] + (d - i * 8) * 0x1c;
    return self;
}

// 0x007458d0
int g_allocLine = 0xd1;
void DequeInit(int* self, unsigned count) {
    int i6 = (count >> 3) + 1;
    unsigned a = (count >> 3) + 3;
    unsigned b = 8;
    unsigned cap = (a < 9) ? a : b;
    self[1] = cap;
    int* p = (int*)EA_New(cap * 4, "Graphics", 0, 0, (const char*)0x13ebb38, 0xd1);
    int* first = (int*)((char*)p + ((cap - i6) >> 1) * 4);
    int* last = first + i6;
    self[0] = (int)p;
    for (int* q = first; q < last; ++q)
        *q = (int)EA_New(0xe0, "Graphics", 0, 0, (const char*)0x13ebb38, 0xd1);
    self[5] = (int)first;
    int v = *first;
    self[3] = v;
    self[4] = v + 0xe0;
    self[2] = self[3];
    self[9] = (int)(last - 1);
    v = last[-1];
    self[7] = v;
    self[8] = v + 0xe0;
    self[6] = self[7] + (count & 7) * 0x1c;
}

// 0x007457a0
void DequeInsert(int* self, unsigned count, int flag) {
    int* begin = (int*)self[5];
    int n = (self[9] - (int)begin) >> 2;
    int i6 = n + 1;
    unsigned total = i6 + count;
    unsigned cap = self[1];
    if (total * 2 < cap) {
        int* dst = (int*)(self[0] + ((cap - total >> 1) + (flag ? count : 0)) * 4);
        if (dst < begin)
            VecDoInsertValue();
        else
            MemMove(dst + (i6 - (((int)(n * 4 + 4)) >> 2)), begin, n * 4 + 4);
    } else {
        int newcap = i6 + 2 + cap;
        int* p = (int*)EA_New(newcap * 4, "Graphics", 0, 0,
                              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        int* dst = (int*)((char*)p + (((int)begin - self[0]) / 4 + (flag ? count : 0)) * 4);
        if (self[0])
            VecDoInsertValue();
        if (self[0])
            EA_Free((void*)self[0]);
        self[0] = (int)p;
        self[1] = newcap;
        self[5] = (int)dst;
        int v = *dst;
        self[3] = v;
        self[4] = v + 0xe0;
        self[9] = (int)(dst + n);
        v = dst[n];
        self[7] = v;
        self[8] = v + 0xe0;
    }
}

// 0x00745340
struct RCObj { virtual int AddRef(); virtual int Release(); };
void cModelWorld::ReleaseRefs() {
    RCObj* a = *(RCObj**)((char*)this + 0x90);
    if (a)
        a->Release();
    RCObj* b = *(RCObj**)((char*)this + 0x64);
    if (b)
        b->Release();
}

// 0x007453d0
void* __fastcall GetThing(void*);   // 0x00bddd00
bool __cdecl FactoryNew(void** out, void* arg2, unsigned flags) {
    cModelInstance* inst = (cModelInstance*)EA_New(0xa0, "Graphics/ModelManager/Animations", 0, 0, 0, 0);
    if (inst)
        inst = inst->Init();
    if (inst)
        *(int*)((char*)inst + 4) += 1;
    inst->SetFlags(flags & 1, (flags >> 1) & 1);
    void* r1 = 0;
    void* h = GetThing(arg2);
    if (h) r1 = (void*)((int (__thiscall*)(void*, int))((*(void***)h)[3]))(h, 0x2f4e681b);
    void* r2 = 0;
    void* h2 = GetThing(arg2);
    if (h2) r2 = (void*)((int (__thiscall*)(void*, int))((*(void***)h2)[3]))(h2, 0xe6bce5);
    if (r1)
        inst->Method742cf0(r1);
    else if (r2)
        inst->ConstructFromGameModelResource(r2);
    *out = inst;
    return true;
}

// 0x007459c0
void Sort18(uint32_t* first, uint32_t* last, bool (*compare)(const void*, const void*)) {
    if (first == last)
        return;
    uint32_t* cur = first;
    while ((cur += 6) != last) {
        uint32_t tmp[6];
        tmp[0] = cur[0]; tmp[1] = cur[1]; tmp[2] = cur[2];
        tmp[3] = cur[3]; tmp[4] = cur[4]; tmp[5] = cur[5];
        uint32_t* p = cur;
        while (p != first) {
            uint32_t* prev = p - 6;
            if (!compare(tmp, prev))
                break;
            p[0] = prev[0]; p[1] = prev[1]; p[2] = prev[2];
            p[3] = prev[3]; p[4] = prev[4]; p[5] = prev[5];
            p = prev;
        }
        p[0] = tmp[0]; p[1] = tmp[1]; p[2] = tmp[2];
        p[3] = tmp[3]; p[4] = tmp[4]; p[5] = tmp[5];
    }
}

// 0x007459c0
// 0x00745140
void cModelWorld::FillColor(int* out) {
    float x, y, z, w;
    switch (*out) {
    case 0:
        out[1] = 0x3f800000; out[2] = 0x3f800000;
        out[3] = 0x3f800000; out[4] = 0x3f800000; return;
    case 1:
    case 0xc:
        x = 1.0f; y = 0.0f; z = 0.0f; w = 1.0f; break;
    case 2:
    case 3:
        out[1] = *(int*)((char*)this + 0x850);
        out[2] = *(int*)((char*)this + 0x854);
        out[3] = *(int*)((char*)this + 0x858);
        out[4] = *(int*)((char*)this + 0x85c); return;
    case 4:
        x = 0.0f; y = 0.5f; z = 1.0f; w = 1.0f; break;
    case 5:
    case 8:
        x = 0.8f; y = 0.8f; z = 1.1f; w = 1.0f; break;
    case 9:
        x = 0.9f; y = 0.9f; z = 1.0f; w = 1.0f; break;
    case 0xb:
        x = 1.0f; y = 0.5f; z = 0.0f; w = 0.75f; break;
    default:
        x = 1.0f; y = 1.0f; z = 1.0f; w = 1.0f; break;
    }
    out[1] = *(int*)&x;
    out[2] = *(int*)&y;
    out[3] = *(int*)&z;
    out[4] = *(int*)&w;
}

// 0x007453a0
struct Small7 { uint32_t d[7]; uint8_t b; void* Init(); };
void* Small7::Init() {
    d[0] = 0xffffffff;
    d[1] = 0; d[2] = 0; d[3] = 0; d[4] = 0; d[5] = 0; d[6] = 0;
    b = 1;
    return this;
}

// 0x007454f0
struct RefObj { virtual void v0(int); int mRef; };
struct AutoRef { RefObj* mp; AutoRef* Release(); };
AutoRef* AutoRef::Release() {
    RefObj* p = mp;
    if (p) {
        mp = 0;
        int n = (*(volatile int*)&p->mRef += -1);
        if (n == 0) {
            *(volatile int*)&p->mRef = 1;
            p->v0(1);
        }
    }
    return this;
}
