// Slice s00743b20 -- SP::cModelWorld model/instance accessors + eastl sort/heap helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- masked externs
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);
void  __cdecl EA_Free(void*);   // 0x00f47380

// ---------------------------------------------------------------- class stubs
struct intrusive_node { intrusive_node* mpNext; intrusive_node* mpPrev; };

struct Model {
    void*    mpWorld;                 // +0x00
    uint32_t mFlags;                  // +0x04
    char     pad08[0x38];             // +0x08
    int      mnRefCount;              // +0x40
    char     pad44[0x28];             // +0x44
    float    mDefaultBoundingRadius;  // +0x6c
    char     pad70[0x20];             // +0x70
    void*    mpField90;               // +0x90  (abs 0x98 in cMWModelInternal)
};

struct cModelInstance {
    int  GetAnimationIDs();                              // 0x0073aba0
    int  GetAnimIDs(uint32_t* dst, int g, int h);        // 0x0073abb0
    int  GetAnimMoveToTimes(int a, int b, int c);        // 0x0073abb0
    int  GetNumBones();                                  // 0x0073b7e0
    int  GetPoseTransforms(void* dst, int original);     // 0x0073d6b0
    int  GetBoneTransforms(void* dst);                   // 0x00740550
    int  GetBoneIDs(void* dst);                          // 0x00740740
    int  GetBoneParents(void* dst);                      // 0x00743030
    bool GetAnimationRange(int a, float& d, int b, float& c);  // 0x0073b6d0
    void SetActive(int a, int b, int c, float d, int e);
    void MoveToTime(int a, int b, float c);
    void SetWeight(int a, int b, float c);
};

void __cdecl AddRefThunk(void*);            // 0x00bddd00
void __cdecl LineClip(const void*, const void*, int, int);  // 0x006989d0

struct cSPVector3 { float x, y, z; };
struct cSPMatrix3 { float m[9]; };
struct cSPTransform {
    uint16_t   mFlags;         // +0x00
    uint16_t   mModCount;      // +0x02
    cSPVector3 mTranslation;   // +0x04
    float      mScale;         // +0x10
    cSPMatrix3 mRotation;      // +0x14
};

// cMWModelInternal: intrusive_list_node base at +0, Model base at +8.
struct cMWModelInternal : intrusive_node, Model {
    void* mpField9c;                  // abs +0x9c
    void* mpFieldA0;                  // +0xa0
    void* mpFieldA4;                  // +0xa4
    void* mpFieldA8;                  // +0xa8
    void* mpFieldAC;                  // +0xac
    void* mpFieldB0;                  // +0xb0
    cModelInstance* mAnim[6];         // +0xb4
    char    pad_cc[0x138 - 0xcc];
    uint32_t mFlags138;               // +0x138
};

struct cLoadQueue { void StallUntilLoaded(uint32_t); };

// ---------------------------------------------------------------- forward decls
struct cModelWorld;

// IModelWorld virtual table stub -- slot at +0x58 (index 22) = StallUntilLoaded.
struct IModelWorld {
    virtual int   AddRef();                              // +0x00
    virtual int   Release();                             // +0x04
    virtual void  dtor();                                // +0x08
    virtual void* CreateModel(uint32_t, uint32_t, int);  // +0x0c
    virtual int   GetNumModelsLoading();                 // +0x10
    virtual bool  CallOnLoad(Model*, void*, void*);      // +0x14
    virtual void  PreloadModels(void*, int);             // +0x18
    virtual bool  ModelsHavePreloaded(int);              // +0x1c
    virtual void* CreateGroup(int, void*&);              // +0x20
    virtual void* m24();                                 // +0x24
    virtual void* m28();                                 // +0x28
    virtual bool  m2c(void*);                            // +0x2c
    virtual bool  m30(void*);                            // +0x30
    virtual bool  m34(void*);                            // +0x34
    virtual bool  m38(void*);                            // +0x38
    virtual bool  m3c(void*);                            // +0x3c
    virtual bool  m40(void*);                            // +0x40
    virtual bool  m44(void*);                            // +0x44
    virtual bool  m48(void*);                            // +0x48
    virtual bool  m4c(void*);                            // +0x4c
    virtual void  GetModelResourceIDs(Model*, void*, void*); // +0x50
    virtual void  GetRegionList(Model*, void*);          // +0x54
    virtual void  StallUntilLoaded(Model*);              // +0x58
};

struct cModelWorld : IModelWorld {
    // slice methods
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
};

// ---------------------------------------------------------------- helpers
// 0x00743b20
uint32_t Getb20(Model* model) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    return ~(m->mFlags138 >> 4) & 1;
}

// 0x00743b50
void* cModelWorld::VecClear() {
    *(uint32_t*)this = 0;
    return this;
}

// 0x00743bb0 -- destruct range of pointers
void __stdcall DestroyPtrRange(void** first, void** last) {
    for (; first < last; ++first) {
        if (*first)
            EA_Free(*first);
    }
}

// ---------------------------------------------------------------- cModelWorld
// 0x00744760
void cModelWorld::StallUntilLoaded2(Model* model, uint32_t a) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cLoadQueue* q = (cLoadQueue*)m->mpField9c;
    if (q)
        q->StallUntilLoaded(a);
}

// 0x00744790
int cModelWorld::GetNumAnimations(Model* model) {
    if (model) {
        cMWModelInternal* m = static_cast<cMWModelInternal*>(model);
        if (m) {
            cModelInstance* inst = m->mAnim[0];
            if (inst)
                return inst->GetAnimationIDs();
        }
    }
    return 0;
}

// 0x00744aa0
int cModelWorld::GetBoneParents(Model* model, void* dst) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetBoneParents(dst) : 0;
}

// 0x007447c0
int cModelWorld::GetAnimationIDs(Model* model, uint32_t* dst) {
    if (model) {
        cMWModelInternal* m = static_cast<cMWModelInternal*>(model);
        if (m) {
            cModelInstance* inst = m->mAnim[0];
            if (inst)
                return inst->GetAnimIDs(dst, 0, 0);
        }
    }
    return 0;
}

// 0x007447f0
int cModelWorld::GetAnimationMoveToTimes(Model* model, int a, int b) {
    if (model) {
        cMWModelInternal* m = static_cast<cMWModelInternal*>(model);
        if (m) {
            cModelInstance* inst = m->mAnim[0];
            if (inst)
                return inst->GetAnimMoveToTimes(b, a, 0);
        }
    }
    return 0;
}

// 0x00744830
int cModelWorld::GetDeformationAnimationIDs(Model* model, int a, int b) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetAnimMoveToTimes(b, a, 0) : 0;
}

// 0x007449e0
int cModelWorld::GetNumBones(Model* model) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetNumBones() : 0;
}

// 0x00744a10
int cModelWorld::GetPoseTransforms(Model* model, void* dst, int original) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetPoseTransforms(dst, original) : 0;
}

// 0x00744a40
int cModelWorld::GetBoneTransforms(Model* model, void* dst) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetBoneTransforms(dst) : 0;
}

// 0x00744a70
int cModelWorld::GetBoneIDs(Model* model, void* dst) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetBoneIDs(dst) : 0;
}

// 0x007446a0
float cModelWorld::StallGetBoundingBox(Model* model) {
    bool b = (model->mFlags >> 17) & 1;
    if (!b)
        this->StallUntilLoaded(model);
    return model->mDefaultBoundingRadius;
}

// 0x007446c0
void* cModelWorld::GetNumAnimationGroups(Model* model) {
    if (((model->mFlags >> 16) & 1) == 0)
        this->StallUntilLoaded(model);
    return (char*)model + 0x70;
}

// 0x00744680
bool cModelWorld::IsVecEmpty(int i) {
    struct Entry { void* p0; void* p1; void* p2; uint32_t a; uint32_t b; };
    Entry* v = (Entry*)((char*)this + 0x5d0 + i * 0x14);
    return v->p0 == v->p1;
}

// ---------------------------------------------------------------- 0x00743b60
struct RefCounted { virtual void AddRef(); virtual void Release(); };
struct Elem28 {
    uint32_t    m0;
    RefCounted* mRef;
    uint32_t    m8, mC, m10, m14, m18;
    Elem28(const Elem28& o);
};
Elem28::Elem28(const Elem28& o) {
    m0 = o.m0;
    mRef = o.mRef;
    if (mRef)
        mRef->AddRef();
    m8 = o.m8;
    mC = o.mC;
    m10 = o.m10;
    m14 = o.m14;
    m18 = o.m18;
}

// ---------------------------------------------------------------- 0x00743fb0
uint32_t BoxDistSq(const float* p, float radius, const float* box) {
    float d2 = 0.0f;
    for (int i = 0; i < 3; ++i) {
        float v = p[i];
        if (v < box[i]) {
            float d = v - box[i];
            d2 += d * d;
        } else if (v > box[i + 3]) {
            float d = v - box[i + 3];
            d2 += d * d;
        }
    }
    return d2 <= radius * radius;
}

// 0x00744900
void cModelWorld::MoveToTime(Model* model, int a, float b, int c) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->MoveToTime(a, c, b);
        ++i;
        ++p;
    } while (i < 6);
}

// 0x00744950
void cModelWorld::SetWeight(Model* model, int a, float b, int c) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->SetWeight(a, c, b);
        ++i;
        ++p;
    } while (i < 4);
}

// 0x007449a0
bool cModelWorld::GetAnimationRange(Model* model, int a, int b, float& c, float& d) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    if (inst)
        return inst->GetAnimationRange(a, d, b, c);
    return false;
}

// ---------------------------------------------------------------- eastl sort/heap helpers
struct Pair8 { uint32_t val; float key; };

// 0x00743be0 -- insertion_sort (guarded, descending key)
void SortDescGuarded(Pair8* first, Pair8* last) {
    if (first == last)
        return;
    Pair8* iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        Pair8 temp = *iSorted;
        Pair8* iNext = iSorted;
        if (iSorted != first) {
            do {
                if (!(temp.key > (iNext - 1)->key))
                    break;
                *iNext = *(iNext - 1);
                --iNext;
            } while (iNext != first);
        }
        *iNext = temp;
        ++iSorted;
    } while (iSorted != last);
}

// 0x00743c50 -- eastl::Internal::insertion_sort_simple (descending key)
void SortDescUnguarded(Pair8* first, Pair8* last) {
    for (Pair8* current = first; current != last; ++current) {
        Pair8* end = current;
        Pair8* prev = current - 1;
        Pair8 value = *current;
        while (value.key > prev->key) {
            *end = *prev;
            --end;
            --prev;
        }
        *end = value;
    }
}

// 0x00743cb0 -- insertion_sort (guarded, ascending key)
void SortAscGuarded(Pair8* first, Pair8* last) {
    if (first == last)
        return;
    Pair8* iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        Pair8 temp = *iSorted;
        Pair8* iNext = iSorted;
        if (iSorted != first) {
            do {
                if (!(temp.key < (iNext - 1)->key))
                    break;
                *iNext = *(iNext - 1);
                --iNext;
            } while (iNext != first);
        }
        *iNext = temp;
        ++iSorted;
    } while (iSorted != last);
}

// 0x00743d20 -- eastl::Internal::insertion_sort_simple (ascending key)
void SortAscUnguarded(Pair8* first, Pair8* last) {
    for (Pair8* current = first; current != last; ++current) {
        Pair8* end = current;
        Pair8* prev = current - 1;
        Pair8 value = *current;
        while (value.key < prev->key) {
            *end = *prev;
            --end;
            --prev;
        }
        *end = value;
    }
}

// 0x00743f00 -- promote_heap (greater)
void PromoteF00(Pair8* first, int top, int pos, Pair8 value) {
    for (int parent = (pos - 1) >> 1;
         (pos > top) && (first[parent].key > value.key);
         parent = (pos - 1) >> 1) {
        first[pos] = first[parent];
        pos = parent;
    }
    first[pos] = value;
}

// 0x00743f60 -- promote_heap (less)
void PromoteF60(Pair8* first, int top, int pos, Pair8 value) {
    for (int parent = (pos - 1) >> 1;
         (pos > top) && (value.key > first[parent].key);
         parent = (pos - 1) >> 1) {
        first[pos] = first[parent];
        pos = parent;
    }
    first[pos] = value;
}

// 0x00743e50 -- promote_heap<cOccluder*,int,cOccluder,bool(*)(...)>
struct cOccluder6 { uint32_t d[6]; };
void PromoteCocc(cOccluder6* first, int top, int pos, cOccluder6 value,
                 bool (*compare)(const cOccluder6&, const cOccluder6&)) {
    int parent = (pos - 1) >> 1;
    while (pos > top && compare(first[parent], value)) {
        first[pos] = first[parent];
        pos = parent;
        parent = (pos - 1) >> 1;
    }
    first[pos] = value;
}

// 0x00743d90 -- eastl uninitialized_copy of Elem28 (placement new)
inline void* operator new(unsigned int, void* p) { return p; }
Elem28* UninitCopy(const Elem28* first, const Elem28* last, Elem28* dst) {
    for (; first != last; ++first, ++dst)
        new (dst) Elem28(*first);
    return dst;
}

// 0x00744870
void cModelWorld::AnimAction(Model* model, int arga, int argb, float argc, int argd) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance** p = m->mAnim;
    if (*p) {
        bool b = (argb == 2);
        if (argb == 2 || argb == 0)
            argb = 1;
        else
            argb = 0;
        int i = 0;
        do {
            cModelInstance* inst = *p;
            if (!inst)
                break;
            inst->SetActive(arga, argd, argb, argc, b);
            ++i;
            ++p;
        } while (i < 6);
        m->mFlags138 |= 0x40000000u;
    }
}

// ---------------------------------------------------------------- transforms
// 0x00744050
void TransformTwo(const cSPVector3* p1, const cSPVector3* p2, const cSPTransform* t, int a, int b) {
    cSPVector3 r1, r2;
    {
        const cSPVector3* p = p1;
        cSPVector3 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        float s = t->mScale;
        if (s != 1.0f) {
            float inv = 1.0f / s;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r1.x = t->mRotation.m[0]*v.x + t->mRotation.m[1]*v.y + t->mRotation.m[2]*v.z;
            r1.y = t->mRotation.m[3]*v.x + t->mRotation.m[4]*v.y + t->mRotation.m[5]*v.z;
            r1.z = t->mRotation.m[6]*v.x + t->mRotation.m[7]*v.y + t->mRotation.m[8]*v.z;
        } else {
            r1 = v;
        }
    }
    {
        const cSPVector3* p = p2;
        cSPVector3 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        float s = t->mScale;
        if (s != 1.0f) {
            float inv = 1.0f / s;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r2.x = t->mRotation.m[0]*v.x + t->mRotation.m[1]*v.y + t->mRotation.m[2]*v.z;
            r2.y = t->mRotation.m[3]*v.x + t->mRotation.m[4]*v.y + t->mRotation.m[5]*v.z;
            r2.z = t->mRotation.m[6]*v.x + t->mRotation.m[7]*v.y + t->mRotation.m[8]*v.z;
        } else {
            r2 = v;
        }
    }
    LineClip(&r1, &r2, a, b);
}

// 0x007442c0
void TransformTwoOffset(const cSPVector3* p1, const cSPVector3* p2, const cSPTransform* t,
                        cSPVector3 a, float pad, cSPVector3 b) {
    cSPVector3 r1, r2;
    {
        const cSPVector3* p = p1;
        cSPVector3 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        float s = t->mScale;
        if (s != 1.0f) {
            float inv = 1.0f / s;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r1.x = t->mRotation.m[0]*v.x + t->mRotation.m[1]*v.y + t->mRotation.m[2]*v.z;
            r1.y = t->mRotation.m[3]*v.x + t->mRotation.m[4]*v.y + t->mRotation.m[5]*v.z;
            r1.z = t->mRotation.m[6]*v.x + t->mRotation.m[7]*v.y + t->mRotation.m[8]*v.z;
        } else {
            r1 = v;
        }
    }
    {
        const cSPVector3* p = p2;
        cSPVector3 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        float s = t->mScale;
        if (s != 1.0f) {
            float inv = 1.0f / s;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r2.x = t->mRotation.m[0]*v.x + t->mRotation.m[1]*v.y + t->mRotation.m[2]*v.z;
            r2.y = t->mRotation.m[3]*v.x + t->mRotation.m[4]*v.y + t->mRotation.m[5]*v.z;
            r2.z = t->mRotation.m[6]*v.x + t->mRotation.m[7]*v.y + t->mRotation.m[8]*v.z;
        } else {
            r2 = v;
        }
    }
    if (pad != 0.0f) {
        float off = pad / t->mScale;
        a.x -= off; a.y -= off; a.z -= off;
        b.x += off; b.y += off; b.z += off;
    }
    LineClip(&r1, &r2, *(int*)&a, 0);
}

// ---------------------------------------------------------------- resource ids
struct ResInfo { char pad[8]; uint32_t field8; uint32_t fieldC; uint32_t field10; };
struct ResHolder { ResInfo* Get(); };

// 0x007446e0
void cModelWorld::GetModelResourceIDs(Model* model, uint32_t* pInstance, uint32_t* pGroup) {
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    uint32_t inst = 0, group = 0;
    ResInfo* p = (ResInfo*)m->mpField90;
    volatile uint32_t tmp;
    if (p) {
        tmp = p->fieldC;
    } else {
        ResHolder* y = (ResHolder*)m->mpField9c;
        if (y) {
            p = y->Get();
            if (p) {
                y = (ResHolder*)m->mpField9c;
                p = y->Get();
                tmp = p->fieldC;
            }
        }
    }
    if (p) {
        group = p->field10;
        inst = p->field8;
    }
    if (pInstance)
        *pInstance = inst;
    if (pGroup)
        *pGroup = group;
}

// 0x007445b0
bool cModelWorld::CallOnLoad(Model* model, void* cb, void* data) {
    if (((model->mFlags >> 14) & 1) != 0) {
        ((void (__cdecl*)(Model*, void*))cb)(model, data);
        return true;
    }
    for (int i = 0; i < 8; ++i) {
        char* e = (char*)this + 0x318 + i * 0x50;
        if (*(Model**)e == model) {
            for (int j = 0; j < 8; ++j) {
                char* f = (char*)this + 0x318 + j * 0x50;
                if (*(Model**)f == model) {
                    *(void**)(f + 0x14) = cb;
                    *(void**)(f + 0x18) = data;
                    return true;
                }
            }
            return false;
        }
    }
    char* begin = *(char**)((char*)this + 0x5a0);
    char* segEnd = *(char**)((char*)this + 0x5a8);
    char** segTable = *(char***)((char*)this + 0x5ac);
    char* end = *(char**)((char*)this + 0x5b0);
    while (begin != end) {
        if (*(Model**)begin == model) {
            *(void**)(begin + 0x14) = cb;
            *(void**)(begin + 0x18) = data;
            return true;
        }
        begin += 0x1c;
        if (begin == segEnd) {
            begin = *(char**)((char*)segTable + 4);
            segTable = (char**)((char*)segTable + 4);
            segEnd = *(char**)(begin + 0xe0);
        }
    }
    return false;
}
