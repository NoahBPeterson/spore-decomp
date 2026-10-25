// s00467a20 -- 0x00467a20 BuildModel, 0x00467ef0 MeshUploadJob::Prep
// Editor model-mesh upload job setup. Unoptimized editor module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

// Reserved frame of an inline callee that cl /Ob1 declined (not identified): an N-dword hole.
template <int N>
inline void ScratchSlots()
{
    uint32_t s[N];
}

struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

template <class T>
struct ptr {
    T* p;
    ptr() : p(0) {}
};

template <class T>
struct AutoRef {
    T* p;
    AutoRef() : p(0) {}
    AutoRef(T* o) : p(o)
    {
        if (p)
            p->AddRef();
    }
    ~AutoRef();                            // 0x004a9b10 (virtual Release)
    AutoRef& operator=(T* o)
    {
        if (o != p) {
            T* old = p;
            if (o)
                o->AddRef();
            p = o;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};

struct Vector3 {
    float x, y, z;
};

struct ThreadedObject {
    uint32_t pad0;
    volatile long mnRefCount;              // +0x04
    void AddRef() { _InterlockedExchangeAdd(&mnRefCount, 1); }
    void Release();                        // 0x00404f90
};

// 0x8c-byte creature part; byte +0xb is the "already handled" flag.
struct Part {
    uint8_t pad0[0xb];
    uint8_t mFlag;                         // +0x0b
    uint8_t padC[0x8c - 0xc];
};

struct VecPart {
    Part* mpBegin;
    Part* mpEnd;
    Part* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct Creature : IObject {
    uint32_t pad04[(0x98 - 4) / 4];
    VecPart mParts;                        // +0x98
};

struct VecU32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    void resize(unsigned int n, const uint32_t& value);   // 0x004746c0
    void push_back(const uint32_t& value);                // 0x00454860
};

struct BuildObj : IObject {
    uint32_t pad04[(0x98 - 4) / 4];
    VecU32 mVec98;                         // +0x98
};

// A 0x14-byte eastl vector header (begin/end/capacity + sp_vector_allocator).
struct Vec14 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    void erase(void* first, void* last);   // 0x00426280
    void resize(int n);                    // 0x0041ee90
};

// Seven such vectors (0x8c bytes) live at MeshUploadJob+0x14 and at BuildSource+0.
struct SevenVec {
    Vec14 v[7];                            // v[4] at +0x50, v[5] at +0x64
    SevenVec& operator=(const SevenVec& o);    // 0x004696d0
};

struct BuildSource {
    SevenVec mSeven;                       // +0x00
};

struct XformTmp {                          // 0x38 bytes (BBoxTransform builder)
    uint16_t flags;
    uint16_t count;
    float x, y, z;                         // +0x04
    float scale;                           // +0x10
    float rot[9];                          // +0x14
    XformTmp();                            // 0x00409930
};

struct XformVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    void assign(XformTmp* first, XformTmp* last, char tag);   // 0x0047b480
};

struct __declspec(align(4)) Elem7c {       // transform pair + count + two cleared pointers
    XformTmp m0;                           // +0x00
    XformTmp m1;                           // +0x38
    int mCount;                            // +0x70
    ptr<IObject> mpObj;                    // +0x74
    ptr<void> mpAlloc;                     // +0x78
    Elem7c(int n) : mCount(n) {}
    ~Elem7c();                             // 0x0041f2d0
};

struct ElemVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const Elem7c& value);   // 0x0041f650
};

struct CJob;
class MeshUploadJob;

struct CJob {
    int AddRef();                          // 0x0068f950
    int Release();                         // 0x00690120
    void AddDependency(CJob* other);       // 0x00691380
    void SetOwner(MeshUploadJob* job);     // 0x0068f9b0
    void SetCallback(MeshUploadJob* job);  // 0x00475650
    bool SetTask(MeshUploadJob* job);      // 0x00475580
};

struct JobRef {
    CJob* p;
    JobRef() : p(0) {}
    ~JobRef()
    {
        if (p)
            p->Release();
    }
    CJob** Reset();                        // 0x0041d940
    JobRef& operator=(CJob* o)
    {
        if (o != p) {
            CJob* old = p;
            if (o)
                o->AddRef();
            p = o;
            if (old)
                old->Release();
        }
        return *this;
    }
    CJob* operator->() const { return p; }
    operator CJob*() const { return p; }
};

class MeshUploadJob : public IObject {
public:
    MeshUploadJob();                       // 0x00469590
    int AddRef();                          // 0x0068f950
    int Release();                         // 0x00690120
    bool Prep(CJob* pJob);                 // 0x00467ef0
    bool Run(CJob* pDependency);           // 0x004680c0

    uint32_t pad04[2];                     // +0x04
    AutoRef<BuildObj> mpMesh;              // +0x0c
    AutoRef<Creature> mpHolder;            // +0x10
    SevenVec mSeven;                       // +0x14
    XformVec mXforms;                      // +0xa0
    uint32_t padB4[5];                     // +0xb4
    AutoRef<ThreadedObject> mThread;       // +0xc8
    Vector3 mOffset;                       // +0xcc
    uint32_t mInstanceID;                  // +0xd8
    uint32_t mTypeID;                      // +0xdc
    JobRef mJob;                           // +0xe0
    int mE4;                               // +0xe4
    int mE8;                               // +0xe8
    VecU32 mEC;                            // +0xec
    uint32_t pad100[9];                    // +0x100
    VecU32 m124;                           // +0x124
    uint32_t pad138[9];                    // +0x138
    Vec14 m15c;                            // +0x15c
    uint32_t pad170[17];                   // +0x170
    ElemVec m1b4;                          // +0x1b4
    uint32_t pad1c8[(0x20cc - 0x1c8) / 4];
};

struct IJobManager {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual bool AddJob(CJob** job);       // slot 4 (+0x10)
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void Lock();                   // +0x20
    virtual void Unlock();                 // +0x24
};
IJobManager* GetJobManager();              // 0x0068f4d0

int Vec20_find(void* vec, int key);        // 0x0071dd80

// @ 0x00467a20
bool BuildModel(uint32_t instance, uint32_t type, Creature* pHolder, BuildObj* pMesh, BuildSource* pSource,
                ThreadedObject* pThread, const Vector3* pOffset, bool flag, XformTmp* pXforms,
                CJob** ppOutJob, CJob* pInJob)
{
    Part* pParts = pHolder->mParts.mpBegin;
    int nParts = pHolder->mParts.size();
    int n = nParts;
    for (int i = nParts - 1; i >= 0; i--) {
        if (pParts[i].mFlag != 1)
            break;
        n--;
    }
    int total = n;
    if (pSource != 0 && !flag) {
        for (int i = 0; i < nParts; i++) {
            void* pEntry = ((void**)pSource->mSeven.v[4].mpBegin)[i];
            if (pEntry != 0)
                total += Vec20_find(pEntry, 5);
        }
    }
    if (total > 0x100)
        return false;
    uint32_t zero = 0;
    pMesh->mVec98.resize(total, zero);
    AutoRef<MeshUploadJob> pJob(new ("Editor", 0, 0, 0, 0) MeshUploadJob());
    pJob->mpMesh = pMesh;
    pJob->mpHolder = pHolder;
    pJob->mThread = pThread;
    pJob->mOffset = *pOffset;
    pJob->mInstanceID = instance;
    pJob->mTypeID = type;
    pJob->mJob = pInJob;
    if (pXforms != 0) {
        char tag;
        pJob->mXforms.assign(pXforms, (XformTmp*)((char*)pXforms + nParts * 0x38), tag);
    }
    if (ppOutJob == 0) {
        bool ok = pJob->Prep(0) && pJob->Run(0);
        return ok;
    }
    pJob->mSeven = pSource->mSeven;
    if (flag) {
        pJob->mSeven.v[5].erase(pJob->mSeven.v[5].mpBegin, pJob->mSeven.v[5].mpEnd);
        pJob->mSeven.v[5].resize(nParts);
    }
    JobRef pNewJob;
    if (!GetJobManager()->AddJob(pNewJob.Reset()))
        return false;
    pNewJob->SetOwner(pJob);
    pNewJob->SetCallback(pJob);
    if (pInJob != 0)
        pInJob->AddDependency(pNewJob);
    *ppOutJob = pNewJob.p;
    pNewJob.p = 0;
    return true;
}

// @ 0x00467ef0
bool MeshUploadJob::Prep(CJob* pJob)
{
    Part* pParts = mpHolder->mParts.mpBegin;
    int nParts = mpHolder->mParts.size();
    mE4 = nParts;
    for (int i = nParts - 1; i >= 0; i--) {
        if (pParts[i].mFlag != 1)
            break;
        mE4--;
    }
    mE8 = mE4;
    ScratchSlots<8>();
    {
        Elem7c elem(mE4);
        m1b4.push_back(elem);
    }
    m124.push_back(0);
    mEC.push_back(0);
    if (pJob == 0)
        return true;
    *(int*)((char*)pJob + 0x1c) = 0;
    return pJob->SetTask(this);
}
