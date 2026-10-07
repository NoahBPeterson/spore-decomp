// slice s00582250 -- SP::cAppModeEditorBase editor helpers.
// 0x00582250: mouse-wheel handler for a selected editor block (or an editor handle): scales the
// block (and up to 5 ancestors with falloff), or adjusts its twist/size/handle value, rebuilds limbs
// and symmetric partners, then plays the "block changed" editor sounds.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the local string/intrusive_ptr have
// no EH frame).  Offsets are from the retail disassembly.
#include "types.h"
#include <math.h>

extern "C" void* memcpy(void* dst, const void* src, size_t n);
extern "C" size_t strlen(const char* s);
#pragma intrinsic(strlen)
inline void* operator new(size_t, void* p) throw() { return p; }
void* operator new[](size_t n, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);

namespace SP {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// ---------------------------------------------------------------- minimal EASTL pieces
extern char gEmptyString[1];                          // 0x01667bac

template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);  // 0x004558a0
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    char* DoAllocate(size_t n) { return new("Editor", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) char[n]; }
    void DoFree(char* p) { if (p) operator delete[](p); }
    void AllocateSelf(size_t n)
    {
        if (n > 1) {
            mpBegin = DoAllocate(n);
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = gEmptyString;
            mpCapacity = gEmptyString + 1;
        }
    }
    void RangeInitialize(const char* pBegin, const char* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n);
        mpEnd = mpBegin + (pEnd - pBegin);
        *mpEnd = 0;
    }
    string(const char* p) { RangeInitialize(p, p + strlen(p)); }
    ~string()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    const char* c_str() const { return mpBegin; }
};
bool operator==(const string& a, const char* b);      // 0x00555020

// ---------------------------------------------------------------- editor types
struct cSPEditorBlock;

struct cBlockState {                                  // returned by 0x0043c240
    uint32_t pad0[0x180 / 4];
    float mValue;                                     // +0x180
};

struct cBlockModelLink {                              // block +0x28
    bool Get4adc40();                                 // 0x004adc40
    void Set4adc20(bool b);                           // 0x004adc20
};

struct cSPEditorBlock {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[(0x28 - 0x04) / 4];
    cBlockModelLink* mpLink;                          // +0x28
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    Vector3 mPosition;                                // +0x48
    uint32_t pad54[(0x1d0 - 0x54) / 4];
    float mTwist;                                     // +0x1d0
    float pad1d4;
    float mScale;                                     // +0x1d8
    float mScaleTarget;                               // +0x1dc
    float mMinScale;                                  // +0x1e0
    float mMaxScale;                                  // +0x1e4
    uint32_t pad1e8[(0x218 - 0x1e8) / 4];
    float mHandleMin;                                 // +0x218
    float mHandleMax;                                 // +0x21c
    uint32_t pad220[(0x33c - 0x220) / 4];
    cSPEditorBlock* mpParent;                         // +0x33c
    vector<cSPEditorBlock*> mChildren;                // +0x340
    uint32_t pad350[(0x460 - 0x350) / 4];
    const char* mpName;                               // +0x460
    uint32_t pad464[(0xdc8 - 0x464) / 4];
    uint32_t mFlags;                                  // +0xdc8

    bool IsLocked() const      { return (mFlags >> 3) & 1; }
    bool IsScalable() const    { return (mFlags >> 7) & 1; }
    bool HasTwist() const      { return (mFlags >> 10) & 1; }
    bool HasState() const      { return (mFlags >> 11) & 1; }

    void SetTwist(float v);                           // 0x0043eae0
    cBlockState* GetState();                          // 0x0043c240
    void SetState(cBlockState* s, float v, int a, int b);  // 0x0043c450
    void StateChanged();                              // 0x00449ce0
    void SetScaleTarget(float v, int b);              // 0x00440020
    float GetHandleValue();                           // 0x0043eed0
};

template<class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    intrusive_ptr& operator=(T* pObject);             // out of line: 0x004b09b0
    __forceinline void reset(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};

struct cSPEditorHandle {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int GetType();                            // +0x10
    cSPEditorBlock* GetRigblock();                    // 0x0047e6c0
};

struct cSPEditorModel {
    uint32_t pad0[0x58 / 4];
    uint32_t mModelType;                              // +0x58
};

struct cSPEditorSkeleton {                            // editor +0x14c
    uint32_t pad0[0xe8 / 4];
    cSPEditorBlock* mpSymmetryRoot;                   // +0xe8
    cSPEditorBlock* mpFirstBlock;                     // +0xec
    void Update5d2790();                              // 0x005d2790
};

struct TorsoFlags {
    bool a;
    bool b;
};

struct cSPEditorSkinManager {
    void UpdateTorso(TorsoFlags flags, int x);        // 0x004c3230
};

struct cSPEditorLimbStructure {
    uint32_t data[0x44 / 4];
    cSPEditorLimbStructure();                         // 0x00488850
    ~cSPEditorLimbStructure();                        // 0x00488900
    void Build(cSPEditorBlock* limb, int a, int b);   // 0x004891a0
    void FixAllJoints();                              // 0x00489ae0
    void Apply();                                     // 0x00488980
};

// cdecl editor utilities
void ScaleBlock(cSPEditorBlock* block, float amount);                 // 0x004a5b30
Vector3 GetBlockCenter(cSPEditorBlock* block);                        // 0x004a5d10
float GetBlockRadius(cSPEditorBlock* block);                          // 0x004a5c40
cSPEditorBlock* GetScaleParent(cSPEditorBlock* block);                // 0x004a5970
void MoveHandle(cSPEditorHandle* handle, float amount);               // 0x00496b60
void ApplyBlockScale(cSPEditorBlock* block, float scale, int a, int b); // 0x0049e6a0
void SnapBlock(cSPEditorBlock* b, int, int, int, int, int, int, int); // 0x004a6d20
cSPEditorBlock* FindClosestSymmetry(Vector3 point, cSPEditorBlock* block);  // 0x0049c570
void PlaceSymmetric(cSPEditorBlock* block, Vector3 pos, Vector3 dir,
                    cSPEditorSkinManager* skin, bool keepZ, float eps);  // 0x0049d6b0
void GetAllLimbs(cSPEditorBlock* block, vector<cSPEditorBlock*>* out, bool unique);  // 0x004a0020
void SetSoundSymbol(uint32_t a, uint32_t b, const char* name);       // 0x00572070
void PlayEditorSound(uint32_t a, uint32_t b, float v, int c);         // 0x00435f40
float CalculateModelSize(cSPEditorModel* model);                      // 0x0048ca10

class cAppModeEditorBase {
public:
    uint32_t pad0[0x98 / 4];
    cSPEditorModel* mpEditorModel;                    // +0x98
    uint32_t pad9c[(0x14c - 0x9c) / 4];
    cSPEditorSkeleton* mpSkeleton;                    // +0x14c
    cSPEditorSkinManager* mpSkinManager;              // +0x150
    uint32_t pad154[(0x20c - 0x154) / 4];
    uint8_t pad20c[2];
    bool mbPlayModelSizeSound;                        // +0x20e

    bool IsManipulatorEnabled(uint32_t id);           // 0x005740e0
    bool OnBlockWheel(cSPEditorBlock* block, cSPEditorHandle* handle, int wheelDelta);
};

// @ 0x00582250
bool cAppModeEditorBase::OnBlockWheel(cSPEditorBlock* block, cSPEditorHandle* handle, int wheelDelta)
{
    float delta = (float)wheelDelta * (1.0f / 120.0f);
    bool handled = false;
    float soundValue = 0.0f;

    if (block && !block->IsLocked()) {
        float amount = delta * 0.1f;
        handled = true;
        if (block->IsScalable()) {
            if (!IsManipulatorEnabled(0x7ad67439))
                return false;
            amount *= 0.5f;
            ScaleBlock(block, amount);
            Vector3 center = GetBlockCenter(block);
            float radius = GetBlockRadius(block);

            intrusive_ptr<cSPEditorBlock> p = GetScaleParent(block);
            float falloff = 1.0f;
            for (int i = 0; p && i < 5; ++i) {
                float dx = p->mPosition.x - center.x;
                float dy = p->mPosition.y - center.y;
                float dz = p->mPosition.z - center.z;
                float distSq = dy * dy + dz * dz + dx * dx;
                float dist = sqrtf(distSq);
                float f;
                if (radius > dist)
                    f = dist / radius * (0.3f - 1.0f) + 1.0f;
                else
                    f = radius / dist * 0.3f;
                if ((amount > 0.0f) != (block->mScale > p->mScale))
                    f *= 0.4f;
                falloff *= 0.7f;
                if (f > falloff)
                    f = falloff;
                if (f < 0.1f)
                    break;
                ScaleBlock(p.get(), f * amount);
                falloff = f;
                p.reset(GetScaleParent(p.get()));
            }

            p = block->mpParent;
            falloff = 1.0f;
            for (int i = 0; p && i < 5; ++i) {
                float dx = p->mPosition.x - center.x;
                float dy = p->mPosition.y - center.y;
                float dz = p->mPosition.z - center.z;
                float distSq = dx * dx + dy * dy + dz * dz;
                float dist = sqrtf(distSq);
                float f;
                if (radius > dist)
                    f = dist / radius * (0.3f - 1.0f) + 1.0f;
                else
                    f = radius / dist * 0.3f;
                if ((amount > 0.0f) != (block->mScale > p->mScale))
                    f *= 0.4f;
                falloff *= 0.7f;
                if (f > falloff)
                    f = falloff;
                if (f < 0.1f)
                    break;
                ScaleBlock(p.get(), f * amount);
                falloff = f;
                p.reset(p->mpParent);
            }

            TorsoFlags torso;
            torso.a = false;
            torso.b = false;
            mpSkinManager->UpdateTorso(torso, 0);

            vector<cSPEditorBlock*> blocks;
            for (cSPEditorBlock* b = mpSkeleton->mpFirstBlock; b; b = b->mpParent) {
                int n = b->mChildren.size();
                for (int j = 0; j < n; ++j) {
                    cSPEditorBlock* child = b->mChildren[j];
                    if (!child->IsScalable())
                        blocks.push_back(child);
                }
            }

            bool keepZ = mpEditorModel->mModelType != 0xdfad9f51;
            bool flat = mpEditorModel->mModelType == 0xdfad9f51;
            int count = blocks.size();
            for (int i = 0; i < count; ++i) {
                cSPEditorBlock* sym = FindClosestSymmetry(blocks[i]->mPosition, mpSkeleton->mpSymmetryRoot);
                Vector3 symPos = GetBlockCenter(sym);
                cSPEditorBlock* cur = blocks[i];
                float dx = cur->mPosition.x - symPos.x;
                float dy = cur->mPosition.y - symPos.y;
                float dz = cur->mPosition.z - symPos.z;
                if (flat)
                    dz = 0.0f;
                float len = sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);
                float invLen = 1.0f / len;
                PlaceSymmetric(cur, symPos, Vector3(invLen * dx, invLen * dy, dz * invLen),
                               mpSkinManager, keepZ, 0.1f);
            }

            bool linked = block->mpLink->Get4adc40();
            block->mpLink->Set4adc20(false);
            vector<cSPEditorBlock*> limbs;
            GetAllLimbs(block, &limbs, linked);
            {
                cSPEditorLimbStructure limb;
                int nLimbs = limbs.size();
                for (int i = 0; i < nLimbs; ++i) {
                    limb.Build(limbs[i], 0, 0);
                    limb.FixAllJoints();
                    limb.Apply();
                }
                block->mpLink->Set4adc20(linked);
                if (mpSkeleton)
                    mpSkeleton->Update5d2790();
                soundValue = (block->mScale - block->mMinScale) / (block->mMaxScale - block->mMinScale);
            }
        } else if (block->HasState()) {
            if (block->HasTwist()) {
                if (!IsManipulatorEnabled(0x8665f54d) && !IsManipulatorEnabled(0xe931544d))
                    return false;
                block->SetTwist(amount * 0.25f + block->mTwist);
                soundValue = block->mTwist;
            } else if (block->GetState()) {
                cBlockState* state = block->GetState();
                float v = amount * 0.25f + state->mValue;
                if (v > 1.0f)
                    v = 1.0f;
                else if (0.0f > v)
                    v = 0.0f;
                if (state->mValue != v) {
                    block->SetState(state, v, 0, 1);
                    block->StateChanged();
                }
                soundValue = state->mValue;
            }
        } else {
            block->SetScaleTarget(expf(amount * 0.75f) * block->mScaleTarget, 1);
            ApplyBlockScale(block, block->mScaleTarget, 1, 1);
            soundValue = (block->mScale - block->mMinScale) / (block->mMaxScale - block->mMinScale);
        }
    } else {
        if (!handle || handle->GetType() != 0x50e8e23)
            return handled;
        handled = true;
        MoveHandle(handle, delta * 0.05f);
        block = handle->GetRigblock();
        if (!block)
            return handled;
        block->GetHandleValue();
        float lo = block->mHandleMin;
        float hi = block->mHandleMax;
        soundValue = (block->GetHandleValue() - lo) / (hi - lo);
    }

    if (block) {
        SnapBlock(block, 0, 0, 0, 0, 0, 1, 1);
        string name(block->mpName);
        if (!(name == "")) {
            SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, name.c_str());
            PlayEditorSound(0xb07c3bbf, 0xfdedb725, soundValue, 0);
        }
        if (mbPlayModelSizeSound)
            PlayEditorSound(0x1d6253c0, 0xdef22b96, CalculateModelSize(mpEditorModel), 0);
    }
    return handled;
}

}  // namespace SP

// @ 0x00582d00  (106 bytes) -- not reconstructed (partial.txt)
void FUN_00582d00() {}
// @ 0x00582d70  (622 bytes) -- not reconstructed (partial.txt)
void FUN_00582d70() {}
