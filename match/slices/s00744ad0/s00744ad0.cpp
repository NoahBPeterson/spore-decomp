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
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
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
    void  FillColor(int, float*);
    void* ReleaseRef();
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
int SlotNext(int* self, int idx) {
    uint32_t* p = (uint32_t*)(*self + idx * 0x14);
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
int SlotCount(int* first, int* last) {
    int n = 0;
    for (;;) {
        uint32_t* p = (uint32_t*)first;
        if (last == first)
            return n;
        do {
            first = (int*)(p + 5);
            if ((*p >> 0x1e) & 1)
                break;
            p = (uint32_t*)first;
        } while ((int)*first < 0);
        ++n;
    }
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
        int n = p->mRef - 1;
        p->mRef = n;
        if (n == 0) {
            p->mRef = 1;
            p->v0(1);
        }
    }
    return this;
}
