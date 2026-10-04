// Slice s004cc190: SP::cSPEditorSkinPart (the creature-editor skin mesh part) and a
// cSkinObject helper. Retail layout = 2008 PDB layout + 0x24/0x28 (bigger base, 0x14-byte vectors).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc: member dtors have no EH frame).
#include "types.h"

union LARGE_INTEGER {
    struct { uint32_t LowPart; int32_t HighPart; } u;
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);
extern "C" long _InterlockedIncrement(long volatile* addend);
#pragma intrinsic(_InterlockedIncrement)

#pragma pack(push, 4)

// Reproduces dead /Od stack slots left by inlined helpers whose locals the original never used.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

inline float Lerp(float a, float b, float t) { float d = b - a; d *= t; return a + d; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};

// ---------------------------------------------------------------------------
// EA::Stopwatch
// ---------------------------------------------------------------------------
#define EA_READ_CPU_CYCLE(t) __asm { rdtsc } __asm { mov dword ptr [t + 4], edx } __asm { mov dword ptr [t], eax }
inline uint64_t GetStopwatchCycle() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return li.QuadPart;
}

namespace EA {
class Stopwatch {
public:
    enum Units { kUnitsCycles = 0, kUnitsCPUCycles = 1, kUnitsNanoseconds = 2, kUnitsMicroseconds = 3,
                 kUnitsMilliseconds = 4, kUnitsSeconds = 5 };
    Stopwatch(int units, bool bStartImmediately);   // 0x0093A560
    uint64_t GetElapsedTime() const;                 // 0x0093A3A0
    uint32_t GetElapsedTimeMs() const;               // 0x0093A5E0
    float GetElapsedTimeFloat() const { return (float)(int64_t)GetElapsedTime() * mfStopwatchCyclesToUnitsCoefficient; }
    void Restart() {
        if (mnUnits == kUnitsCPUCycles) {
            uint64_t nCycle;
            EA_READ_CPU_CYCLE(nCycle);
            mnStartTime = nCycle;
        } else
            mnStartTime = GetStopwatchCycle();
        mnTotalElapsedTime = 0;
    }

    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
};

template <class T> class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            ScratchSlots<2>();
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T* mpObject;
};
} // namespace EA

namespace eastl {
template <class T> class intrusive_ptr {
public:
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
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
    T* mpObject;
};
} // namespace eastl

// ---------------------------------------------------------------------------
// EASTL bits (retail vectors are 0x14 bytes: 3 pointers + an 8-byte allocator)
// ---------------------------------------------------------------------------

namespace eastl {
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};

template <class T> inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}

template <class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase();                                   // 0x00425990
};

template <class T> struct vector : public VectorBase<T> {
    vector() {}
    ~vector() { destruct(this->mpBegin, this->mpEnd); ScratchSlots<3>(); }
    T* begin() { return this->mpBegin; }
    T* end() { return this->mpEnd; }
    int size() const { return (int)(this->mpEnd - this->mpBegin); }
    bool empty() const;                              // out of line (0x00526430)
    T& operator[](uint32_t i) { return this->mpBegin[i]; }
};

template <int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline bitset& set(uint32_t i, bool value) {  // /Ob1 refuses this size otherwise
        if (i < N) {
            if (value)
                DoGetWord(i) |= (1 << (i % 32));
            else
                DoGetWord(i) &= ~(1 << (i % 32));
        }
        return *this;
    }
    uint32_t DoGetWordValue(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWordValue(i) & (1 << (i % 32))) != 0;
        return false;
    }
};
template <> inline uint32_t& bitset<32>::DoGetWord(uint32_t) { return mWord[0]; }
} // namespace eastl

#pragma pack(pop)

#pragma pack(push, 4)

namespace SP {

class cMWModel;
class cIModelWorldImpl {
public:
    void* vtbl_placeholder_never_used();
};
struct cModelWorldVtbl;
class cModelWorldBase {
public:
#define V(n) virtual void Unk##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37)
    V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
    V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73)
    V(74) V(75) V(76) V(77) V(78) V(79) V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89) V(90)
#undef V
    virtual void RemoveModel(cMWModel* model, int flags);   // vtable +0x16C
};

class cMWModel {
public:
    void AddRef() { mnRefCount++; }
    void Release();                                  // 0x0040F360
    void RemoveFromWorld() { mpWorld->RemoveModel(this, 0); }
    cModelWorldBase* mpWorld;                        // 0x00
    eastl::bitset<32> mFlags;                        // 0x04
    uint32_t pad8[14];
    int mnRefCount;                                  // 0x40
    eastl::bitset<64> mGroupFlags;                   // 0x44
};

class cTextureInstance {
public:
    void AddRef() { _InterlockedIncrement((long*)&mnRefCount); }
    void Release();                                  // 0x00402420
    uint32_t pad0[2];
    int mnRefCount;                                  // 0x08
};

class cSPEditorBlock {
public:
    uint32_t pad0[0xDC8 / 4];
    eastl::bitset<60> mFlags;                        // 0xDC8
};

class cMaterialInfo;
class cShaderDataMaterialParams;
class cMaterial;

class cIModelWorld {
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual void Unk2();
    virtual cMWModel* CreateModel(uint32_t instance, uint32_t group, int flags);
};

class cIModelManager {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3(); virtual void Unk4();
    virtual void Unk5(); virtual void Unk6(); virtual void Unk7(); virtual void Unk8(); virtual void Unk9();
    virtual uint32_t GetGroupIndex(uint32_t group, int flags);
};
cIModelManager* ModelManager();                      // 0x0067DD80

class cIMaterialManager {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3(); virtual void Unk4();
    virtual void Unk5(); virtual void Unk6(); virtual void Unk7(); virtual void Unk8(); virtual void Unk9();
    virtual cMaterial* GetMaterial(uint32_t id);
};
cIMaterialManager* MaterialManager();                // 0x0067DD70

class cMesh {
public:
    void AddRef();
    void Release();
    bool Raycast(const Vector3& origin, const Vector3& dir, bool b, int, int c, int, int a, int a2); // 0x0050BD90
    uint32_t pad0[2];
    eastl::vector<uint32_t> mVerts;                  // 0x08
};

class cImplicitSurface {
public:
    void AddRef();
    void Release();
    void GetNodeWeights(const Vector3& pos, eastl::vector<struct NodeWeight>* out); // 0x004F9570
};

struct NodeWeight {
    uint32_t mNode;
    float mWeight;
};

struct AllocTag { AllocTag() {} };
struct NodeWeightAllocator {
    NodeWeightAllocator(const AllocTag& tag);        // 0x00429360
    uint32_t pad[2];
};
struct NodeWeightVector {
    NodeWeight* mpBegin;
    NodeWeight* mpEnd;
    NodeWeight* mpCapacity;
    NodeWeightAllocator mAllocator;
    NodeWeightVector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(AllocTag()) {}
    ~NodeWeightVector();                             // 0x004CDDD0
    bool empty() const;                              // 0x00526430
    int size() const { return (int)(mpEnd - mpBegin); }
};

class cIDynamicDraw {
public:
    cIDynamicDraw() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
class cDynamicDrawBase : public cIDynamicDraw {
public:
    cDynamicDrawBase() { ScratchSlots<1>(); }
};

class RefVector {   // eastl::vector<EA::AutoRefCount<cMaterialInfo>, sp_vector_allocator>
public:
    RefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~RefVector() { ScratchSlots<7>(); DoDestroy(); }
    void DoDestroy();                                // 0x0041EB80
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    eastl::sp_vector_allocator mAllocator;
};

namespace Resource {
class ThreadedObject {
public:
    virtual ~ThreadedObject();
    int Release();                                   // 0x00404F90
    long mnRefCount;                                 // 0x04
};
}

class cSkinObject : public Resource::ThreadedObject {
public:
    cSkinObject();                                   // 0x004C6BA0
    ~cSkinObject();                                  // 0x004C72F0
    void BuildBlocks(cSPEditorBlock** blocks, int count, eastl::vector<cSPEditorBlock*>* ordered); // 0x004C73F0
    void Tessellate(float resolution);               // 0x004CA430
    bool Raycast(Vector3 origin, Vector3 dir, int a, int a2, int c, bool b);

    uint32_t pad8;
    uint32_t padC[5];                                // 0x0C mBlockProps
    eastl::vector<uint8_t> mNodeBlockMap;            // 0x20
    EA::AutoRefCount<cMesh> mMesh;                   // 0x34
    EA::AutoRefCount<cImplicitSurface> mSurface;     // 0x38
    uint32_t pad3C[32];                              // 0x3C
};

Vector3 normalized_safe(const Vector3& v);           // 0x00449C20
Vector3 GetBlockCenter(cSPEditorBlock* block);       // 0x004A5D10
float GetBlockRadius(cSPEditorBlock* block);         // 0x004A5C40
Vector3 operator-(const Vector3& a, const Vector3& b); // 0x0041DB10
float VectorLength(const Vector3& v);                // 0x0040AE50
void RegisterDynamicDraw(cDynamicDrawBase* draw, uint32_t instance, uint32_t group);   // 0x007544E0
void UnregisterDynamicDraw(uint32_t instance, uint32_t group);                         // 0x00754620

class cSPEditorSkinPart : public cSkinObject, public cDynamicDrawBase {
public:
    cSPEditorSkinPart();
    ~cSPEditorSkinPart();
    virtual int AddRef();
    virtual int Release();
    void SetModel(uint32_t instance, uint32_t group, bool allowHighQuality);
    void Update(eastl::vector<cSPEditorBlock*>& blocks, bool forceHighQuality);
    void RestartQualityTimer();
    bool IsHighQualityPending();
    void UpdateSceneObject(cIModelWorld* world);
    void SetVisible(bool visible);
    cSPEditorBlock* GetBlockAt(Vector3 pos);
    void ReleaseModel();
    void SetDrawMaterial(uint32_t id);
    void SetSkinResolution(float realtime, float highQuality);

    eastl::vector<cSPEditorBlock*> mOrderedBlocks;   // 0xC0
    cMaterial* mDrawMaterial;                        // 0xD4
    uint32_t mInstance;                              // 0xD8
    uint32_t mGroup;                                 // 0xDC
    EA::AutoRefCount<cMWModel> mModel;               // 0xE0
    RefVector mBlockMatInfos;                        // 0xE4
    cShaderDataMaterialParams* mSpecParams;          // 0xF8
    eastl::intrusive_ptr<cTextureInstance> mDiffuseTex;  // 0xFC
    eastl::intrusive_ptr<cTextureInstance> mNormalTex;   // 0x100
    bool mAllowHighQualityPass;                      // 0x104
    bool mLastPassHighQuality;                       // 0x105
    EA::Stopwatch mQualityTimer;                     // 0x108
    float mSkinResolutionRealtime;                   // 0x120
    float mSkinResolutionHighQuality;                // 0x124
    float mSkinResolution;                           // 0x128
    bool mExpand;                                    // 0x12C
};

// @ 0x004CC190
cSPEditorSkinPart::cSPEditorSkinPart()
    : mDrawMaterial(0), mInstance(0), mModel(0), mSpecParams(0),
      mAllowHighQualityPass(false), mLastPassHighQuality(false),
      mQualityTimer(EA::Stopwatch::kUnitsSeconds, false),
      mSkinResolutionRealtime(0.05f), mSkinResolutionHighQuality(0.028f), mSkinResolution(0.028f),
      mExpand(false)
{
}

// @ 0x004CC330
// cIDynamicDraw::AddRef override: `this` is the cDynamicDrawBase subobject (+0xBC).
int cSPEditorSkinPart::AddRef()
{
    return _InterlockedIncrement(&mnRefCount);
}

// @ 0x004CC350
int cSPEditorSkinPart::Release()
{
    ScratchSlots<3>();
    return ThreadedObject::Release();
}

// @ 0x004CC3A0
cSPEditorSkinPart::~cSPEditorSkinPart()
{
}

// @ 0x004CC470
void cSPEditorSkinPart::SetModel(uint32_t instance, uint32_t group, bool allowHighQuality)
{
    mInstance = instance;
    mGroup = group;
    mAllowHighQualityPass = allowHighQuality;
    mLastPassHighQuality = false;
    mQualityTimer.Restart();
    if (instance)
        RegisterDynamicDraw(this, instance, group);
}

// @ 0x004CC540
void cSPEditorSkinPart::Update(eastl::vector<cSPEditorBlock*>& blocks, bool forceHighQuality)
{
    bool useRealtime = true;
    float resolution = mSkinResolutionRealtime;
    if (forceHighQuality || (mAllowHighQualityPass && mQualityTimer.GetElapsedTimeFloat() >= 0.2f))
        useRealtime = false;
    BuildBlocks(blocks.begin(), blocks.size(), &mOrderedBlocks);
    if (useRealtime) {
        EA::Stopwatch timer(EA::Stopwatch::kUnitsMilliseconds, true);
        Tessellate(mSkinResolution);
        uint32_t elapsedMs = timer.GetElapsedTimeMs();
        if (elapsedMs > 20)
            mSkinResolution = Lerp(mSkinResolution, mSkinResolutionRealtime, 0.1f);
        else if (elapsedMs < 15)
            mSkinResolution = Lerp(mSkinResolution, mSkinResolutionHighQuality, 0.4f);
        mLastPassHighQuality = false;
    } else {
        Tessellate(mSkinResolutionHighQuality);
        mLastPassHighQuality = true;
    }
}

// @ 0x004CC6F0
void cSPEditorSkinPart::RestartQualityTimer()
{
    mQualityTimer.Restart();
}

// @ 0x004CC760
bool cSPEditorSkinPart::IsHighQualityPending()
{
    return mAllowHighQualityPass && !mLastPassHighQuality && mQualityTimer.GetElapsedTimeFloat() >= 0.2f;
}

// @ 0x004CC7D0
void cSPEditorSkinPart::UpdateSceneObject(cIModelWorld* world)
{
    if (!mModel && mInstance) {
        mModel = world->CreateModel(mInstance, mGroup, 0);
        mModel->mFlags.set(12, true);
        cIModelManager* manager = ModelManager();
        if (manager) {
            mModel->mGroupFlags.set(manager->GetGroupIndex(mGroup, 0), true);
            mModel->mGroupFlags.set(manager->GetGroupIndex(0x0FEB8DF2, 0), true);
        }
    }
}

// @ 0x004CCA40
void cSPEditorSkinPart::SetVisible(bool visible)
{
    if (mModel)
        mModel->mFlags.set(0, visible);
}

// @ 0x004CCAE0
bool cSkinObject::Raycast(Vector3 origin, Vector3 dir, int a, int a2, int c, bool b)
{
    dir = normalized_safe(dir);
    ScratchSlots<6>();
    if (mMesh && !mMesh->mVerts.empty())
        return mMesh->Raycast(origin, dir, b, 0, c, 0, a, a2);
    return false;
}

// @ 0x004CCB70
cSPEditorBlock* cSPEditorSkinPart::GetBlockAt(Vector3 pos)
{
    int nodeIndex = -1;
    bool indirect = false;
    if (mSurface && !mNodeBlockMap.empty() && !mOrderedBlocks.empty()) {
        NodeWeightVector weights;
        mSurface->GetNodeWeights(pos, (eastl::vector<NodeWeight>*)&weights);
        if (!weights.empty()) {
            float bestWeight = 0.0f;
            int idx = 0;
            int num = weights.size();
            for (; idx < num; idx++) {
                uint32_t id = weights.mpBegin[idx].mNode;
                float weight = weights.mpBegin[idx].mWeight;
                if (weight > bestWeight) {
                    nodeIndex = id & 0x7FFFFFFF;
                    indirect = (id & 0x80000000) != 0;
                    bestWeight = weight;
                }
            }
        }
    }
    if (nodeIndex == -1) {
        float minDistance = 3.402823466e+38F;
        cSPEditorBlock* pBest = 0;
        cSPEditorBlock** it = mOrderedBlocks.begin();
        cSPEditorBlock** last = mOrderedBlocks.end();
        for (; it != last; ++it) {
            cSPEditorBlock* block = *it;
            if (block->mFlags.test(10) && block->mFlags.test(7)) {
                Vector3 center = GetBlockCenter(block);
                float radius = GetBlockRadius(block);
                Vector3 diff = Vector3(center - pos);
                float distance = VectorLength(diff) - radius;
                if (distance < minDistance) {
                    pBest = block;
                    minDistance = distance;
                }
            }
        }
        return pBest;
    }
    return indirect ? mOrderedBlocks[mNodeBlockMap[nodeIndex]] : mOrderedBlocks[nodeIndex];
}

// @ 0x004CCED0
void cSPEditorSkinPart::ReleaseModel()
{
    if (mModel) {
        mModel->RemoveFromWorld();
        mModel = 0;
    }
    if (mInstance) {
        UnregisterDynamicDraw(mInstance, mGroup);
        mInstance = 0;
    }
    mDiffuseTex = 0;
    mNormalTex = 0;
}

// @ 0x004CD020
void cSPEditorSkinPart::SetDrawMaterial(uint32_t id)
{
    mDrawMaterial = MaterialManager()->GetMaterial(id);
}

// @ 0x004CD060
void cSPEditorSkinPart::SetSkinResolution(float realtime, float highQuality)
{
    if (realtime > 0.0f)
        mSkinResolutionRealtime = realtime;
    if (highQuality > 0.0f) {
        mSkinResolutionHighQuality = highQuality;
        mSkinResolution = highQuality;
    }
}

} // namespace SP

#pragma pack(pop)

// ---------------------------------------------------------------------------
// eastl::fixed_vector<uint32_t, 64> (0x100-byte inline buffer at +0x18)
// ---------------------------------------------------------------------------
namespace eastl {
struct fixed_vector_allocator64 {
    fixed_vector_allocator64(void* pBuffer) : mpPoolBegin(pBuffer) {}
    uint32_t mOverflow;
    void* mpPoolBegin;
    uint32_t mPad;
};

struct fixed_vector_u32_64 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    fixed_vector_allocator64 mAllocator;
    uint32_t mBuffer[64];

    fixed_vector_u32_64(uint32_t n);
    void resize(uint32_t n);                         // 0x004CD790
};

// @ 0x004CD0C0
fixed_vector_u32_64::fixed_vector_u32_64(uint32_t n)
    : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(mBuffer)
{
    mpEnd = mBuffer;
    mpBegin = mpEnd;
    mpCapacity = mpBegin + 64;
    resize(n);
}
} // namespace eastl
