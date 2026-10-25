// Slice s004c4650: SP::cSPEditorSkinManager helpers and related editor tasks (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"
#include <intrin.h>

#pragma pack(push, 4)

namespace SP {

// ---------------------------------------------------------------------------
// math / small shared types
// ---------------------------------------------------------------------------
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

class cSPEditorBlock;

// ---------------------------------------------------------------------------
// EA::AutoRefCount<T> (retail: single pointer, AddRef/Release on the pointee)
// ---------------------------------------------------------------------------
template <class T> class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& o) { return operator=(o.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T* mpObject;
};

// ---------------------------------------------------------------------------
// EA::vector<RefCounted*> -- three pointers, plus the ThreadedObject variants.
// ---------------------------------------------------------------------------
struct RefVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void ctorRef(void* p);                              // 0x429360
    void eraseRange(void* first, void* last);           // 0x426280
    void resize(int n);                                 // 0x41ee90
    void dtorRef();                                     // 0x41eb80
    bool emptyRef() const;                              // 0x526430
};

// ---------------------------------------------------------------------------
// TickState singleton (0x401080 returns it)
// ---------------------------------------------------------------------------
class TickState {
public:
    static TickState* Get();                            // 0x401080
    void ClearPtr(void* p);                             // 0x522a40
    void ClearPtr100();                                 // 0x5227a0
};

// intrusive refcounted resource object: only Release is invoked here
class ThreadedObject {
public:
    void Release();                                     // 0x404f90
};

// ---------------------------------------------------------------------------
// cRuntimeCreatureResource -- only the deform table is inspected here.
// +0x98: vector<DeformRecord> (0x8c-byte stride), each record has a uint16
// flag word at +8, bit 0 == "detached/unused".
// ---------------------------------------------------------------------------
struct DeformRecord {
    char pad[0x8c];
};

class cRuntimeCreatureResource {
public:
    char pad0[0x98];
    DeformRecord* mDeformBegin;     // +0x98
    DeformRecord* mDeformEnd;       // +0x9c
};

class cSkinObject {
public:
    char pad0[8];
    AutoRefCount<cRuntimeCreatureResource> mResource;   // +0x8
};

// ---------------------------------------------------------------------------
// cSPEditorSkinPart (retail layout: resource @0x8, mOrderedBlocks @0xa4,
// mBlockMatInfos @0xc0/0xc4, material @0xd0, instance id @0xd4,
// textures @0xfc/0x100, skin resolutions @0x120/0x124/0x128).
// ---------------------------------------------------------------------------
class cSPEditorSkinPart : public cSkinObject {
public:
    char pad9c[0xa4 - 0xc];
    RefVec mOrderedBlocks;        // +0xa4 (erase/resize through RefVec)
    char padac[0xc0 - 0xb0];
    void** mBlockMatInfosBegin;   // +0xc0
    void** mBlockMatInfosEnd;     // +0xc4
    char padc8[0xd0 - 0xc8];
    uint32_t mDrawMaterial;       // +0xd0
    uint32_t mInstance;           // +0xd4
    char padd8[0xfc - 0xd8];
    void* mDiffuseTex;            // +0xfc
    void* mNormalTex;             // +0x100
    char pad104[0x120 - 0x104];
    float mSkinResolutionRealtime;    // +0x120
    float mSkinResolutionHighQuality; // +0x124
    float mSkinResolution;            // +0x128

    void AddRef() { _InterlockedIncrement((long*)((char*)this + 4)); }
    void Release() { if (_InterlockedDecrement((long*)((char*)this + 4)) == 0) Destroy(); }
    void Destroy();

    bool BuildSkeleton();                              // 0x4ca6e0
    void RebuildSkinA();                               // 0x4cb340
    void RebuildSkinB();                               // 0x4cb820
    void Shutdown();                                   // 0x4cced0
    cSPEditorBlock* GetBlockOnSkin(cSPVector3 pos);    // 0x4ccb70
    void SetDefaultMaterial(uint32_t id);              // 0x4cd020
    void SetSkinResolutions(float realtime, float highQuality);  // 0x4cd060
    bool PickSkinPart(cSPVector3 lod, cSPVector3 dir, cSPVector3* outPos,
                      cSPVector3* outNormal, float* outDist, char flag);  // 0x4ccae0
};

// ---------------------------------------------------------------------------
// cSPEditorSkinManager
// ---------------------------------------------------------------------------
class cSPEditorSkinManager {
public:
    char pad0[0x10];
    void* mModel;                        // +0x10
    void* mSceneObjectModelWorld;        // +0x14
    AutoRefCount<cSPEditorSkinPart> mTorsoSkin;    // +0x18
    AutoRefCount<cSPEditorSkinPart> mCompleteSkin; // +0x1c
    char pad20[0x48 - 0x20];
    struct BlockPart { void* block; AutoRefCount<cSPEditorSkinPart> part; };
    struct BlockVec {
        BlockPart* mpBegin;              // +0x48
        BlockPart* mpEnd;                // +0x4c
        int Size() { return (int)(mpEnd - mpBegin); }
        bool Empty() { return mpEnd == mpBegin; }
        BlockPart& Back() { return mpEnd[-1]; }
        void PopBack();                  // 0x4c6070
    };
    BlockVec mBlockTransforms;           // +0x48
    char pad50[0x5c - 0x50];
    AutoRefCount<struct cPaintRequest> mPaintRequest;   // +0x5c
    uint32_t mDefaultMaterial;           // +0x60
    char pad64[0x78 - 0x64];
    float mPaintResolution;              // +0x78
    float mRealtimeResolution;           // +0x7c
    float mHighQualityResolution;        // +0x80
    uint8_t mPaintEnabled;               // +0x84

    bool CheckPaint() const;             // 0x4c58b0
    void* GetSkin(uint32_t which);
    void Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5);   // 0x4c38e0
    void EnablePaint(char enable);                                 // 0x4c4650
    bool PickSkin(uint32_t which, cSPVector3 lod, cSPVector3 dir,
                  cSPVector3* outPos, cSPVector3* outNormal, float* outDist, char flag);
    cSPEditorBlock* GetBlockOnSkin(uint32_t which, cSPVector3 pos);
    void DetachSkinParts();                                        // 0x4c4eb0
    void SetDefaultMaterial(uint32_t id);
    void SetDefaultMaterialToDetachedLimb(uint32_t id, const void* block);
    void SetSkinResolutions(float realtime, float highQuality);
};

// opaque refcounted paint-request object; only its release is invoked
class cPaintRequest {
public:
    void AddRef() {}
    void Release();                      // 0x453540
};

// ---------------------------------------------------------------------------
// opaque callees bound by address comment
// ---------------------------------------------------------------------------
cSPVector3 normalized_safe(const cSPVector3& v);              // 0x449c20
float VectorLength(const cSPVector3& v);                      // 0x40ae50
cSPVector3 GetSkinTip(cSPEditorBlock* block);                 // 0x4a5d10
float GetSkinRadius(cSPEditorBlock* block);                   // 0x4a5c40
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b); // 0x41db10

// ---------------------------------------------------------------------------
// in-slice definitions
// ---------------------------------------------------------------------------

// @ 0x004c49e0 (pre-existing in this slice)
void* cSPEditorSkinManager::GetSkin(uint32_t which)
{
    switch (which) {
    case 0: {
        cSPEditorSkinPart* p = mTorsoSkin;
        return p;
    }
    case 1: {
        cSPEditorSkinPart* p = mCompleteSkin;
        return p;
    }
    }
    return 0;
}

// @ 0x004c4650  cSPEditorSkinManager::EnablePaint (thiscall, ret 4: char enable)
void cSPEditorSkinManager::EnablePaint(char enable)
{
    if (enable == 0 || mPaintEnabled != 0) {
        if (enable == 0 && mPaintEnabled != 0) {
            if (CheckPaint()) {
                void* req = mPaintRequest;
                TickState::Get()->ClearPtr(req);
            }
            TickState::Get()->ClearPtr100();
            mPaintRequest = 0;
            mPaintEnabled = 0;
        }
    } else {
        Update(0, 1, 0, 0);

        cSPEditorSkinPart* part = mCompleteSkin;
        part->BuildSkeleton();
        part->RebuildSkinA();
        part->RebuildSkinB();

        cRuntimeCreatureResource* res = part->mResource;
        DeformRecord* deformBegin = res->mDeformBegin;
        void** blockMatInfos = part->mBlockMatInfosBegin;
        int count = (int)((char*)res->mDeformEnd - (char*)res->mDeformBegin) / 0x8c;

        RefVec vec;
        vec.mpBegin = 0;
        vec.mpEnd = 0;
        vec.mpCapacity = 0;
        unsigned char pad = 0;
        vec.ctorRef(&pad);

        part->mOrderedBlocks.eraseRange(part->mOrderedBlocks.mpBegin, part->mOrderedBlocks.mpEnd);
        part->mOrderedBlocks.resize(count);

        for (int i = 0; i < count; ++i) {
            if ((*(uint16_t*)((char*)deformBegin + i * 0x8c + 8) & 1) == 0) {
                void* matInfo = blockMatInfos[i];
                char* sub = *(char**)((char*)matInfo + 0x10);
                vec.eraseRange(vec.mpBegin, vec.mpEnd);
                (*(void(__thiscall**)(void*, void*))(*(char**)sub + 0xf4))(sub, &vec);
                if (!vec.emptyRef()) {
                    void* newVal = *(void**)vec.mpBegin;
                    void** slot = (void**)((char*)part->mOrderedBlocks.mpBegin + i * 4);
                    if (newVal != *slot) {
                        void* oldVal = *slot;
                        if (newVal != 0) {
                            long* rc = (long*)((char*)newVal + 4);
                            _InterlockedIncrement(rc);
                        }
                        *slot = newVal;
                        if (oldVal != 0) {
                            ((ThreadedObject*)oldVal)->Release();
                        }
                    }
                }
            }
        }
        TickState::Get()->ClearPtr100();
        mPaintEnabled = 1;
        vec.dtorRef();
    }
}

// @ 0x004c4a30  cSPEditorSkinManager::PickSkin (thiscall, ret 0x2c)
bool cSPEditorSkinManager::PickSkin(uint32_t which, cSPVector3 lod, cSPVector3 dir,
                                    cSPVector3* outPos, cSPVector3* outNormal, float* outDist,
                                    char flag)
{
    if (which == 0) {
        return mTorsoSkin->PickSkinPart(lod, dir, outPos, outNormal, outDist, flag);
    }
    if (which == 1) {
        return mCompleteSkin->PickSkinPart(lod, dir, outPos, outNormal, outDist, flag);
    }
    if (which == 2) {
        char found = 0;
        float bestDist = 0.0f;
        cSPVector3 bestPos;
        cSPVector3 bestNormal;
        BlockVec* vec = &mBlockTransforms;
        int n = vec->Size();
        for (int i = 0; i < n; ++i) {
            if (vec->mpBegin[i].block != 0) {
                cSPVector3 pos;
                cSPVector3 normal;
                float dist;
                if (vec->mpBegin[i].part->PickSkinPart(lod, dir, &pos, &normal, &dist, flag)) {
                    if (found && bestDist <= dist) {
                        continue;
                    }
                    bestDist = dist;
                    bestPos = pos;
                    bestNormal = normal;
                    found = 1;
                }
            }
        }
        if (found) {
            *outPos = bestPos;
            *outNormal = bestNormal;
            *outDist = bestDist;
            return true;
        }
    }
    return false;
}

// @ 0x004c4d30  cSPEditorSkinManager::GetBlockOnSkin (thiscall, ret 0x10)
cSPEditorBlock* cSPEditorSkinManager::GetBlockOnSkin(uint32_t which, cSPVector3 pos)
{
    if (which == 0) {
        return mTorsoSkin->GetBlockOnSkin(pos);
    }
    if (which == 1) {
        return mCompleteSkin->GetBlockOnSkin(pos);
    }
    if (which == 2) {
        cSPEditorBlock* result = 0;
        BlockVec* vec = &mBlockTransforms;
        int n = vec->Size();
        for (int i = 0; result == 0 && i < n; ++i) {
            if (vec->mpBegin[i].block != 0) {
                result = vec->mpBegin[i].part->GetBlockOnSkin(pos);
            }
        }
        return result;
    }
    return 0;
}

// @ 0x004c4eb0  cSPEditorSkinManager::DetachSkinParts (this, no args)
void cSPEditorSkinManager::DetachSkinParts()
{
    EnablePaint(0);
    mModel = 0;
    mSceneObjectModelWorld = 0;
    if (mTorsoSkin != 0) {
        mTorsoSkin->Shutdown();
    }
    if (mCompleteSkin != 0) {
        mCompleteSkin->Shutdown();
    }
    while (!mBlockTransforms.Empty()) {
        cSPEditorSkinPart* last = mBlockTransforms.Back().part;
        last->Shutdown();
        mBlockTransforms.PopBack();
    }
}

// @ 0x004c4f60  cSPEditorSkinManager::SetDefaultMaterial (this, ret 4: id)
void cSPEditorSkinManager::SetDefaultMaterial(uint32_t id)
{
    mDefaultMaterial = id;
    if (mTorsoSkin != 0) {
        mTorsoSkin->SetDefaultMaterial(mDefaultMaterial);
    }
    if (mCompleteSkin != 0) {
        mCompleteSkin->SetDefaultMaterial(mDefaultMaterial);
    }
    int n = mBlockTransforms.Size();
    for (int i = 0; i < n; ++i) {
        mBlockTransforms.mpBegin[i].part->SetDefaultMaterial(mDefaultMaterial);
    }
}

// @ 0x004c5030  cSPEditorSkinManager::SetDefaultMaterialToDetachedLimb (this, ret 8: id, block)
void cSPEditorSkinManager::SetDefaultMaterialToDetachedLimb(uint32_t id, const void* block)
{
    BlockVec* vec = &mBlockTransforms;
    int n = vec->Size();
    for (int i = 0; i < n; ++i) {
        if (vec->mpBegin[i].block != 0) {
            cSPEditorSkinPart* part = vec->mpBegin[i].part;
            void** begin = part->mBlockMatInfosBegin;
            void** end = part->mBlockMatInfosEnd;
            void** it = begin;
            while (it != end && *it != block) {
                ++it;
            }
            if (it != end) {
                part->SetDefaultMaterial(id);
                return;
            }
        }
    }
}

// @ 0x004c5100  cSPEditorSkinManager::SetSkinResolutions (this, ret 8: realtime, highQuality)
void cSPEditorSkinManager::SetSkinResolutions(float realtime, float highQuality)
{
    mPaintResolution = highQuality;
    mRealtimeResolution = realtime;
    mHighQualityResolution = highQuality;
    if (mTorsoSkin != 0) {
        mTorsoSkin->SetSkinResolutions(highQuality, highQuality);
    }
    if (mCompleteSkin != 0) {
        mCompleteSkin->SetSkinResolutions(realtime, highQuality);
    }
    BlockVec* vec = &mBlockTransforms;
    int n = vec->Size();
    for (int i = 0; i < n; ++i) {
        vec->mpBegin[i].part->SetSkinResolutions(realtime, highQuality);
    }
}
} // namespace SP

#pragma pack(pop)
