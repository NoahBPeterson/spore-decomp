// Slice s004a4d60: SP::EditorUtils::PickBlockForPinning (0x4a4d60, 3076 bytes, byte-exact).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Raycasts for a block to pin `block` onto: marks every block that must be ignored with the pin
// type bit on its model, picks along the ray, and (for pinnable blocks) averages the hit position
// with four probe rays offset around it. The signature comes from the dev-build mangled name.
// Frame-layout notes (/Od): local names were picked so that cl's name-hash slot order matches
// (one hash bucket order per scope; ties go to the later-declared name); the bitset's word()
// returns a reference so its address temps land at the bottom of the frame; push_back has its
// real inline body because cl declines it and keeps its reserved frame as a hole; ScratchSlots
// stand in for the other declined inlines' holes.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

// Reserves N dwords of /Od frame at the point of the call: stands in for the reserved frame of an
// inline helper the original compiler declined to inline (docs/matching.md, /Od frame layout).
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------
// Math. Vector3 is the math-library type returned by the out-of-line operators;
// cSPVector3 is the editor's vector (trivial copy-assignment, converting
// assignment/ctor from Vector3 copy per float).
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cSPVector3 : Vector3 {
    cSPVector3() {}
    cSPVector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

Vector3 operator+(const Vector3& a, const Vector3& b);              // @ 0x41dc10
Vector3 operator-(const Vector3& a, const Vector3& b);              // @ 0x41db10
// The two operator* overloads live in separate namespaces only so that the difftest resolver
// (which cannot tell them apart by parameter list) maps each to its own address.
namespace VecScaleR {
Vector3 operator*(const Vector3& v, const float& s);                // @ 0x41dca0
}
namespace VecScaleL {
Vector3 operator*(const float& s, const Vector3& v);                // @ 0x41de40
}
using namespace VecScaleR;
using namespace VecScaleL;
Vector3& operator+=(Vector3& a, const Vector3& b);                  // @ 0x41ddb0
Vector3& operator/=(Vector3& a, const float& s);                    // @ 0x4a9d20
Vector3 Cross(const Vector3& a, const Vector3& b);                  // @ 0x44e460
extern const Vector3 kPinAxis;                                      // @ 0x15d6324
extern const Vector3 kZeroVector;                                   // @ 0x15d64d8

// ---------------------------------------------------------------------------
// Bit sets (two dwords). test() covers 0x3c bits, set() 0x40.
// ---------------------------------------------------------------------------
struct Bits64 {
    uint32_t w[2];
    uint32_t& word(uint32_t pos) { return w[pos >> 5]; }
    __forceinline void set(uint32_t pos, bool v)
    {
        if (pos < 0x40) {
            if (v) word(pos) |= (1u << (pos % 32));
            else   word(pos) &= ~(1u << (pos % 32));
        }
    }
};
struct Bits60 {
    uint32_t w[2];
    __forceinline bool test(uint32_t pos) const
    {
        if (pos < 0x3c) { uint32_t word = w[pos >> 5]; return (word & (1u << (pos % 32))) != 0; }
        return false;
    }
};

// cMWPickInfo filter (ctor @ 0x4a4c70).
struct cSPEditorPickInfo {
    Bits64 m0;
    Bits64 m8;
    int m10;
    bool m14;
    bool m15;
    cSPEditorPickInfo();
};

// ---------------------------------------------------------------------------
// Ref counting
// ---------------------------------------------------------------------------
struct RefCountTemplate {
    void* vptr;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                                                  // @ 0x453540
};

struct cMWModel {
    uint32_t pad0[0x10];
    int mRefCount;                                                  // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
};
void __fastcall CountedRelease(cMWModel* p);                        // @ 0x40f360
struct ModelRef {
    cMWModel* p;
    ModelRef(cMWModel* q) : p(q) { if (p) p->AddRef(); }
    ~ModelRef() { if (p) CountedRelease(p); }
};

// Pick hit returned by the world raycast.
struct cMWHit {
    uint32_t pad0[0x10];
    int mRefCount;                                                  // +0x40
    uint32_t pad44[(0x5c - 0x44) / 4];
    unsigned char m5c;
    unsigned char mKind;                                            // +0x5d
    unsigned char pad5e[2];
    uint32_t pad60;
    void* mpObject;                                                 // +0x64 (IUnknown32 AutoRefCount)
    void AddRef() { mRefCount = mRefCount + 1; }
    void* GetObject() { return mpObject; }
};
void __fastcall HitRelease(cMWHit* p);                              // @ 0x40f360
struct HitRef {
    cMWHit* p;
    HitRef(cMWHit* q) : p(q) { if (p) p->AddRef(); }
    ~HitRef() { if (p) HitRelease(p); }
    cMWHit* operator->() const { return p; }
};

struct cSPEditorBlock;
void* __cdecl InterfaceCast(void* const* p);                        // @ 0x4aa2a0

// ---------------------------------------------------------------------------
// Containers
// ---------------------------------------------------------------------------
struct BlockRef {
    cSPEditorBlock* mpObject;
    cSPEditorBlock* operator->() const { return mpObject; }
};
struct BlockVector {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef& operator[](int i) { BlockRef* p = mpBegin + i; return *p; }
};

struct sp_vector_allocator { sp_vector_allocator() {} };
// eastl::fixed_vector<AutoRefCount<cSPEditorBlock>, 8>
struct FixedBlockVector {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    uint32_t mAllocator;                                            // +0x0c
    uint32_t mUnknown10;                                            // +0x10
    uint32_t mPoolCount;                                            // +0x14 (zeroed by InitFixed)
    BlockRef mBuffer[8];                                            // +0x18
    void Construct(const sp_vector_allocator& a);                   // @ 0x540470 (vector ctor)
    void InitFixed();                                               // @ 0x453770
    void Destroy();                                                 // @ 0x453eb0 (~vector)
    FixedBlockVector() { Construct(sp_vector_allocator()); InitFixed(); }
    ~FixedBlockVector() { Destroy(); }
    BlockRef& operator[](int i) { BlockRef* p = mpBegin + i; return *p; }
    cSPEditorBlock* get(int i) { return mpBegin[i].mpObject; }
};

// eastl::sp_vector_allocator (empty); its copy ctor stayed out of line (0x429360).
struct vec3_allocator {
    vec3_allocator() {}
    vec3_allocator(const vec3_allocator& a);                        // @ 0x429360
};
struct Vec3Vector {
    cSPVector3* mpBegin;
    cSPVector3* mpEnd;
    cSPVector3* mpCapacity;
    vec3_allocator mAllocator;
    uint32_t mUnknown10;                                            // +0x10 (vector is 0x14 bytes here)
    Vec3Vector(const vec3_allocator& allocator = vec3_allocator())
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
    ~Vec3Vector() { Destroy(); }
    void Destroy();                                                 // @ 0x540520 (the out-of-line ~vector)
    int size() const { return (int)(mpEnd - mpBegin); }
    void DoInsertValue(cSPVector3* position, const cSPVector3& value); // @ 0x4b5ad0
    // @ 0x4739d0 (declined inline)
    void push_back(const cSPVector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) cSPVector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// ---------------------------------------------------------------------------
// Editor objects
// ---------------------------------------------------------------------------
struct cSPEditorModel {
    void* vptr;
    RefCountTemplate mRef;                                          // +0x4
    cSPEditorBlock* GetBlock(int i);                                // @ 0x4accb0
    int GetBlockCount();                                            // @ 0x4accf0
    float GetScale();                                               // @ 0x4adaa0
    bool IsSymmetric();                                             // @ 0x4adc40
    void SetAllNodeStates(int state);                               // @ 0x4ae090
    void ClearAllNodeStates();                                      // @ 0x4ae040
};
struct EditorModelRef {
    cSPEditorModel* p;
    EditorModelRef(cSPEditorModel* q) : p(q) { if (p) p->mRef.AddRef(); }
    ~EditorModelRef() { if (p) p->mRef.Release(); }
    cSPEditorModel* operator->() const { return p; }
};

struct cMWPickInfo;
struct IModelWorld {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual cMWHit* Raycast(const cSPVector3& o, const cSPVector3& e, int zero, cSPVector3& normal,
                            cSPVector3& pos, cSPEditorPickInfo& filter, int* extra, int* level); // slot 0x24
};
struct IModelManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual uint32_t GetTypeBit(uint32_t key, int zero);            // slot 0x28
};
IModelManager* __cdecl ModelManager();                              // @ 0x67dd80

struct cSPEditorBlock {
    void* vptr;
    uint32_t pad04[(0x18 - 4) / 4];
    IModelWorld* mWorld;                                            // +0x18
    uint32_t pad1c[(0x28 - 0x1c) / 4];
    cSPEditorModel* mEditorModel;                                   // +0x28
    uint32_t pad2c[(0x3c0 - 0x2c) / 4];
    uint32_t mBlockType;                                            // +0x3c0
    uint32_t pad3c4;
    bool mbPinnable;                                                // +0x3c8
    unsigned char pad3c9[3];
    uint32_t pad3cc[(0x3e0 - 0x3cc) / 4];
    cSPEditorBlock* mParent;                                        // +0x3e0
    uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
    Bits60 mFlags;                                                  // +0xdc8

    IModelWorld* GetWorldPtr() { return mWorld; }
    IModelWorld* GetWorld() { return GetWorldPtr(); }
    uint32_t GetBlockType() { return mBlockType; }
    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock* GetParent() { return mParent; }
    bool IsPinnable() { return mbPinnable; }
    bool HasRelevantPoints(cSPEditorBlock* other);                  // @ 0x4382a0
    void SetModelBit(uint32_t bit, bool v);                         // @ 0x43bf90
};
bool __cdecl GetSymmetricPile(cSPEditorBlock* block, FixedBlockVector& list, bool b); // @ 0x49dd20

namespace SP { namespace EditorUtils {
cSPEditorBlock* PickBlockForPinning(cSPEditorBlock* block, BlockVector& blocks, cSPVector3 origin,
                                    cSPVector3 dir, cSPVector3& outNormal, cSPVector3& outPos,
                                    bool& outIsPin, int* level);
} }

// @ 0x4a4d60
// Local names were chosen so that cl's /Od name-hash slot order reproduces the original frame.
cSPEditorBlock* SP::EditorUtils::PickBlockForPinning(cSPEditorBlock* block, BlockVector& blocks,
    cSPVector3 origin, cSPVector3 dir, cSPVector3& outNormal, cSPVector3& outPos, bool& outIsPin, int* level)
{
    EditorModelRef theModel(block->GetEditorModel());
    if (block->GetBlockType() == 0x9183dc9b)
        theModel.p->SetAllNodeStates(2);
    else
        theModel.p->SetAllNodeStates(4);
    bool bSym = theModel->IsSymmetric();
    IModelWorld* modelWorld = block->GetWorld();
    IModelManager* modelManager = ModelManager();
    if (modelManager) {
        // Mark every block that must not be picked (by the pin type bit of its model).
        uint32_t pinTypeBit = modelManager->GetTypeBit(0x900c6add, 0);
        int blockCount = theModel->GetBlockCount();
        for (int i = 0; i < blockCount; i++) {
            cSPEditorBlock* other = theModel->GetBlock(i);
            if (other->mFlags.test(7) || other->mFlags.test(10) || !block->HasRelevantPoints(other))
                other->SetModelBit(pinTypeBit, true);
            else
                other->SetModelBit(pinTypeBit, false);
        }
        blockCount = (int)(blocks.mpEnd - blocks.mpBegin);
        for (int j = 0; j < blockCount; j++) {
            cSPEditorBlock* sel = blocks[j].mpObject;
            sel->SetModelBit(pinTypeBit, true);
            if (bSym && sel->GetParent())
                sel->GetParent()->SetModelBit(pinTypeBit, true);
        }
        block->SetModelBit(pinTypeBit, true);
        if (bSym && block->GetParent()) {
            block->GetParent()->SetModelBit(pinTypeBit, true);
            FixedBlockVector parentPile;
            GetSymmetricPile(block->GetParent(), parentPile, true);
            for (int k = 0, pileCount = (int)(parentPile.mpEnd - parentPile.mpBegin); k < pileCount; k++) {
                cSPEditorBlock* c = parentPile[k].mpObject;
                c->SetModelBit(pinTypeBit, true);
            }
        }
        FixedBlockVector ownPile;
        GetSymmetricPile(block, ownPile, true);
        for (int m = 0, pileSize = (int)(ownPile.mpEnd - ownPile.mpBegin); m < pileSize; m++)
            ownPile[m]->SetModelBit(pinTypeBit, true);

        cSPEditorPickInfo pickFilter;
        pickFilter.m0.set(modelManager->GetTypeBit(0x9138fd8d, 0), true);
        pickFilter.m8.set(pinTypeBit, true);
        pickFilter.m15 |= 1;
        int extraInfo;
        HitRef hit(modelWorld->Raycast(origin, origin + 1000.0f * dir, 0, outNormal, outPos, pickFilter,
                                       &extraInfo, level));

        if (block->IsPinnable()) {
            // Average the hit position with four probes offset around the ray.
            cSPVector3 hitNormal, hitPos;
            int probeExtra, probeLevel;
            Vector3 rightVec = Cross(dir, kPinAxis);
            Vector3 binormal = Cross(rightVec, dir);
            Vec3Vector points;
            points.push_back(outPos);
            float probeRadius = theModel->GetScale() * 0.02f;
            for (int n = 0; n < 4; n++) {
                cSPVector3 start;
                switch (n) {
                case 0: start = origin + binormal * probeRadius; break;
                case 1: start = origin - binormal * probeRadius; break;
                case 2: start = origin + rightVec * probeRadius; break;
                case 3: start = origin - rightVec * probeRadius; break;
                }
                cMWHit* probeHit = modelWorld->Raycast(start, start + 1000.0f * dir, 0, hitNormal, hitPos,
                                                       pickFilter, &probeExtra, &probeLevel);
                if (probeHit)
                    points.push_back(hitPos);
            }
            cSPVector3 sum = kZeroVector;
            int numHits = points.size();
            numHits = numHits;   // (sic) the original reloads and re-stores the count here
            for (int q = 0; q < numHits; q++)
                sum += points.mpBegin[q];
            if (numHits > 0)
                sum /= (float)numHits;
            outPos = sum;
            ScratchSlots<1>();   // ~vector's reserved frame (declined inline 0x540520)
        }

        cSPEditorBlock* resultBlock = 0;
        if (hit.p && hit->GetObject() && (resultBlock = (cSPEditorBlock*)InterfaceCast(&hit->mpObject)) != 0
            && hit.p->mKind == 2)
            outIsPin = true;
        // Reserved frames of declined inlines in this tail (interface_cast, the AutoRefCount
        // releases run by the destructors below): 13 dwords in the original frame.
        ScratchSlots<13>();
        theModel.p->ClearAllNodeStates();
        return resultBlock;
    }
    return 0;
}
