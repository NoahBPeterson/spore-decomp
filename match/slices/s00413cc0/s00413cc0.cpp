// Slice s00413cc0: vector helpers and a clip-playback object ("blend tree" builder).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
extern "C" long _InterlockedIncrement(long volatile* addend);
#pragma intrinsic(_InterlockedIncrement)

// ---------------------------------------------------------------------------
// Math
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};

Vector3* CrossLike(Vector3* out, const void* a, const void* b);   // 0x0041db10
void    ScaleInPlace(Vector3* v, const Vector3* s);         // 0x0041dba0
Vector3* Combine(Vector3* out, const void* a, const Vector3* v);  // 0x0041dc10

template <typename T>
inline const T& min_ref(const T& a, const T& b) { return (a > b) ? b : a; }

// ---------------------------------------------------------------------------
// Smart pointers
// ---------------------------------------------------------------------------
namespace Resource {
struct ThreadedObject {
    void* vtable;
    long mnRefCount;
    int AddRef() { uint32_t unused0, unused1, unused2; return _InterlockedIncrement(&mnRefCount); }
    int Release();                                  // 0x00404f90
};
}

struct LoadHandle {
    int AddRef();                                   // 0x0068f950
    int Release();                                  // 0x00690120
    void Cancel();                                  // 0x006926b0
    void Attach(void* owner);                       // 0x004227d0
    uint32_t pad[6];
    uint32_t mFlags;                                // +0x18
    void SetFlags(uint32_t f) { mFlags = f; }
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T* detach() { T* p = mpObject; mpObject = 0; return p; }
    intrusive_ptr& operator=(const intrusive_ptr& ip) { return operator=(ip.mpObject); }
    T** operator&() {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    intrusive_ptr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------------------
// Clip data
// ---------------------------------------------------------------------------
struct PointArray {
    Vector3 v[3];
    Vector3& operator[](int i) { return v[i]; }
};

struct ClipEntry {                                  // 0x8c
    int16_t mId;                                    // +0x00
    int16_t mParent;                                // +0x02
    int16_t mLink;                                  // +0x04
    uint16_t pad06;
    uint16_t mFlags;                                // +0x08
    uint8_t padA;
    uint8_t mType;                                  // +0x0b
    uint32_t pad0C[(0x2c - 0x0c) / 4];
    float mTime;                                    // +0x2c
    PointArray mPos;                                // +0x30
    Vector3 mDir;                                   // +0x54
    uint32_t pad60[(0x8c - 0x60) / 4];
};

struct ClipEntryList {                              // begin/end of 0x8c-byte entries
    ClipEntry* mpBegin;
    ClipEntry* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct ClipModel {
    uint32_t pad[0x98 / 4];
    ClipEntryList mEntries;                         // +0x98
};

struct ClipNode {
    bool Test(float t);                             // 0x004f96a0
    void Finish(int flag);                          // 0x004fc320
};

struct ClipSkin {
    void Reset();                                   // 0x00508400
};

// Playable clip: a refcounted object holding the model, the blend node and the playback time.
struct Clip : Resource::ThreadedObject {
    intrusive_ptr<ClipModel> mpModel;               // +0x08
    uint32_t pad0C[(0x34 - 0x0c) / 4];
    intrusive_ptr<ClipSkin> mpSkin;                 // +0x34
    intrusive_ptr<ClipNode> mpNode;                 // +0x38
    float mTime;                                    // +0x3c
};

Vector3 SamplePosition(const Vector3* a, const Vector3* b, float t);   // 0x004a5c70
float   SampleScale(float t);                                          // 0x004a5c00

struct IFactory {
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vc();
    virtual void Create(LoadHandle** out);
    static IFactory* Get();                         // 0x0068f4d0
};

struct IntVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    IntVector(int n, int value);                    // 0x00422740
    ~IntVector() { for (int* p = mpBegin; p < mpEnd; ++p) {} Free(); }
    void Free();                                    // 0x004c0b80
    int& operator[](int i) { return mpBegin[i]; }
};

struct Mixer {
    void Reset();                                   // 0x004fd520
    int AddKey(Vector3* pos, float a, float b, int id);                  // 0x004fcc20
    void Link(int from, int to, float w, uint32_t flags);                // 0x004fcca0
    void SetRoot(ClipNode* node);                   // 0x004fd380
};

struct Solver {
    uint32_t pad[0x1c / 4];
    uint32_t mField1C;                              // +0x1c
    bool Run(ClipNode* a, ClipSkin* b, float t);          // 0x005400a0
    bool Apply(bool flag);                          // 0x0053eda0
    void Finish();                                  // 0x00540210
};

class ClipPlayer {
public:
    bool BuildBlend(Clip* src);               // 0x00413de0
    bool Advance(Clip* t, float time, bool flag);   // 0x004142e0
    void Rewind(int unused);                        // 0x004143e0
    bool Step(Clip* t, float time);           // 0x00414420
    bool Start(Clip* clip, float time, LoadHandle** out);   // 0x00414470
    int  BuildChain(ClipEntry* e, int count, int i, int prev, int id, int link, int h);   // 0x00412900

    uint32_t pad00[0x80 / 4];
    intrusive_ptr<LoadHandle> mpHandle;             // +0x80
    intrusive_ptr<Clip> mpCurrent; // +0x84
    intrusive_ptr<Mixer> mpMixer;                   // +0x88
    intrusive_ptr<Solver> mpSolver;                 // +0x8c
};

// @ 0x00413cc0
Vector3* ComputeVector(Vector3* ret, const void* a, const void* b, Vector3 c) {
    Vector3 tmp;
    Vector3 v = *CrossLike(&tmp, b, a);
    ScaleInPlace(&v, &c);
    Vector3 tmp2;
    *ret = *Combine(&tmp2, a, &v);
    return ret;
}

// @ 0x00413d60
float MinComponent(Vector3* v) {
    return min_ref(min_ref((*v)[0], (*v)[1]), (*v)[2]);
}

// @ 0x00413de0
bool ClipPlayer::BuildBlend(Clip* src) {
    if (mpHandle) {
        mpHandle->Cancel();
        mpHandle = 0;
        mpCurrent = 0;
    }
    int count;
    int i;
    float one;
    int prevB;
    int prevH;
    ClipEntry* e;
    float linkWeight;
    linkWeight = 0.3f;
    one = 1.0f;
    e = src->mpModel->mEntries.mpBegin;
    count = src->mpModel->mEntries.size();
    i = 0;
    while (i < count && !(e[i].mFlags & 1))
        i++;
    if (i == count)
        return false;
    mpMixer->Reset();
    prevB = -1;
    prevH = -1;
    for (i = 0; i < count && e[i].mType == 5; i++) {
        ClipEntry* p = &e[i];
        Vector3 pos = SamplePosition(&p->mDir, &p->mPos[2], p->mTime);
        float scale = SampleScale(p->mTime);
        int h = mpMixer->AddKey(&pos, one, scale, p->mId);
        if (i > 0)
            mpMixer->Link(prevH, h, linkWeight, prevB | 0x80000000);
        prevH = h;
        prevB = p->mParent;
    }
    IntVector handles(count, -1);
    for (; i < count && e[i].mType == 3; i++) {
        ClipEntry* p = &e[i];
        if (p->mFlags & 1) {
            if (p->mLink == -1 || e[p->mLink].mType != 3) {
                prevB = p->mParent - 1;
                prevH = -1;
            } else {
                prevB = e[p->mLink].mParent;
                prevH = handles.mpBegin[p->mLink];
            }
            handles[i] = BuildChain(e, count, i, prevB, p->mParent, p->mId, prevH);
        }
    }
    src->mpNode->Finish(1);
    mpMixer->SetRoot(src->mpNode);
    mpMixer->Reset();
    bool result = true;
    return result;
}

// @ 0x004142e0
bool ClipPlayer::Advance(Clip* t, float time, bool flag) {
    bool result = false;
    for (;;) {
        if (!(t->mpNode->Test(time) && mpSolver->Run(t->mpNode, t->mpSkin, time)))
            break;
        if (mpSolver->Apply(flag)) {
            result = true;
            break;
        }
        if (!(mpSolver->mField1C && time < 0.5f))
            break;
        time *= 1.2f;
    }
    t->mTime = time;
    mpSolver->Finish();
    return result;
}

// @ 0x004143e0
void ClipPlayer::Rewind(int unused) {
    Advance(mpCurrent, mpCurrent->mTime, true);
}

// @ 0x00414420
bool ClipPlayer::Step(Clip* t, float time) {
    bool ok = BuildBlend(t);
    if (!ok) {
        t->mpSkin->Reset();
        return true;
    }
    return Advance(t, time, false);
}

// @ 0x00414470
bool ClipPlayer::Start(Clip* clip, float time, LoadHandle** out) {
    BuildBlend(clip);
    intrusive_ptr<LoadHandle> handle;
    IFactory::Get()->Create(&handle);
    mpHandle = handle;
    mpCurrent = clip;
    mpCurrent->mTime = time;
    handle.get()->Attach(this);
    handle.get()->SetFlags(0x80000000);
    *out = handle.detach();
    return true;
}
