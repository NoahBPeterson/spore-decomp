// slice s0059c4c0 — SP::cSPEditorAnimatedCreatureManager (retail layout): creature map helpers,
// creation/removal and per-creature forwarding setters.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
#include "types.h"

typedef unsigned int size_t;

// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
};

extern const cSPVector3 kZeroVector;      // 0x015E5B8C
extern const float      kIdentityQuat[4]; // 0x0150E1C8

namespace EA {

template <typename T>
class RefCountTemplate {
public:
    RefCountTemplate() : mnRefCount(0) {}
    virtual ~RefCountTemplate() {}
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        // volatile read-modify-write gives the load / add -1 / store shape
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x4
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p);   // out of line (0x00572680 for cSPEditorAnimatedCreatureData)
    void Reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

}  // namespace EA

namespace eastl {

struct allocator {};
struct sp_vector_allocator { uint32_t pad[2]; sp_vector_allocator() {} };
struct true_type {};

template <typename T>
struct less { bool operator()(const T& a, const T& b) const { return a < b; } };

template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;    // +0x0
    rbtree_node_base* mpNodeLeft;     // +0x4
    rbtree_node_base* mpNodeParent;   // +0x8
    char              mColor;         // +0xc
};

rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);   // 0x00921580

template <typename T>
struct rbtree_node : public rbtree_node_base {
    T mValue;   // +0x10
};

template <typename T>
struct rbtree_iterator {
    typedef rbtree_node<T> node_type;
    node_type* mpNode;
    rbtree_iterator() : mpNode(0) {}
    explicit rbtree_iterator(const node_type* pNode) : mpNode((node_type*)pNode) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    T* operator->() const { return &mpNode->mValue; }
    rbtree_iterator& operator++() { mpNode = (node_type*)RBTreeIncrement(mpNode); return *this; }
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
};

// eastl::map<Key, T> (rbtree<..., unique keys>), 2008 layout, 0x1C bytes
template <typename Key, typename T>
class map {
public:
    typedef pair<const Key, T>           value_type;
    typedef rbtree_node<value_type>      node_type;
    typedef rbtree_iterator<value_type>  iterator;

    less<Key>        mCompare;   // +0x0
    rbtree_node_base mAnchor;    // +0x4
    uint32_t         mnSize;     // +0x14
    allocator        mAllocator; // +0x18

    map() : mAnchor(), mnSize(0) { reset(); }
    ~map() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }

    iterator begin() { return iterator((node_type*)mAnchor.mpNodeLeft); }
    iterator end() { return iterator((node_type*)&mAnchor); }

    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear()
    {
        DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
        reset();
    }

    iterator find(const Key& key);                                                    // 0x00E5C780 (folded)
    iterator erase(iterator position);                                                // 0x0059C460
    iterator DoInsertValue(iterator position, const value_type& value, true_type);   // 0x0059C520
    iterator insert(iterator position, const value_type& value)
    {
        return DoInsertValue(position, value, true_type());
    }
    iterator lower_bound(const Key& key)
    {
        node_type*        pCurrent  = (node_type*)mAnchor.mpNodeParent;
        rbtree_node_base* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!mCompare(pCurrent->mValue.first, key)) {
                pRangeEnd = pCurrent;
                pCurrent  = (node_type*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (node_type*)pCurrent->mpNodeRight;
        }
        return iterator((node_type*)pRangeEnd);
    }
    T& operator[](const Key& key);
    void DoFreeNode(node_type* pNode)
    {
        pNode->~node_type();
        operator delete[](pNode);
    }
    void DoNukeSubtree(node_type* pNode);
};

template <typename T, typename Allocator>
class vector {
public:
    T*        mpBegin;
    T*        mpEnd;
    T*        mpCapacity;
    Allocator mAllocator;
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector();                                                  // out of line (0x005C7F10, folded)
    T* DoInsertValue(T* position, const T& value);              // 0x005C8480
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

}  // namespace eastl

namespace SP {

class cAnimatingCreatureController;
class cIAnimWorldCreatureHelper {
public:
    void OnAnimationStarted(int anim);                   // 0x00A006F0
};

class cAnimatingCreature {
public:
    virtual void Unk0();
    virtual int  PlayAnimation(uint32_t animID, int flags);   // slot 1
    virtual void Unk2(); virtual void Unk3(); virtual void Unk4(); virtual void Unk5();
    virtual void Unk6(); virtual void Unk7(); virtual void Unk8(); virtual void Unk9();
    virtual void Unk10(); virtual void Unk11(); virtual void Unk12(); virtual void Unk13();
    virtual void Unk14(); virtual void Unk15(); virtual void Unk16(); virtual void Unk17();
    virtual void Unk18(); virtual void Unk19(); virtual void Unk20(); virtual void Unk21();
    virtual void GetCurrentAnimation(uint32_t* pAnimID, int a, int* pCount, int b);   // slot 22
    void AddRef();
    void Release();

    void SetIdle(int);                                 // 0x00A02AB0
    bool IsAnimationDone(int);                         // 0x00A02B20
    bool IsAnimationQueued(uint32_t animID);           // 0x00A02B40
    bool IsAnimationLooping(int);                      // 0x00A04940
    void SetTurnRate(int);                             // 0x00A04C80
    void SetMoving(bool);                              // 0x00A04CA0

    cSPVector3 mPosition;                              // +0x4
    char pad_10[0x54 - 0x10];
    int mState;                                        // +0x54
    char pad_58[0x88 - 0x58];
    uint32_t mFlags;                                   // +0x88
    char pad_8c[0x184 - 0x8c];
    cIAnimWorldCreatureHelper* mpHelper;               // +0x184
};

class cIModelWorld {
public:
    virtual void AddRef();
    virtual void Release();
};

class cSPEditorAnimationManager {
public:
    virtual void Unk0();
    virtual void AddRef();
    virtual void Release();
    void Shutdown();                                   // 0x00C2E4E0
};

class cSPEditorAnimatedEventInfo {
public:
    virtual void Unk0();
    virtual void AddRef();
    virtual void Release();
};

struct cCreatureBlock;
class cISPCreatureAnimWorld {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void Unk2(); virtual void Unk3(); virtual void Unk4(); virtual void Unk5();
    virtual void Unk6(); virtual void Unk7();
    virtual void Update();                                                                      // slot 8
    virtual void Unk9(); virtual void Unk10(); virtual void Unk11();
    virtual cAnimatingCreature* CreateCreature(cCreatureBlock* block, int lod, const cSPVector3* pos,
                                               const float* orient, bool visible);            // slot 13 (MSVC lists overloads in reverse)
    virtual cAnimatingCreature* CreateCreature(const void* key, int lod, const cSPVector3* pos,
                                               const float* orient, bool visible);            // slot 12
    virtual void Unk14();
    virtual void RemoveCreature(cAnimatingCreature* creature);                                  // slot 15
};

class cSPEditorAnimatedCreatureData : public EA::RefCountTemplate<int> {
public:
    cSPEditorAnimatedCreatureData();                                         // 0x0059ACE0
    void Init(cAnimatingCreature* creature, cIModelWorld* modelWorld);       // 0x0059AE20
    void Shutdown();                                                         // 0x0059AE60
    bool IsAnimInterruptible();                                              // 0x0059AE80
    void SetPreserveHeight(bool preserve);                                   // 0x0059AC50
    void SetLookAtTarget(const cSPVector3& target, bool immediate);          // 0x0059AC60
    void SetTargetPosition(const cSPVector3& pos, bool immediate, bool raw); // 0x0059B0F0
    void SetTargetAngle(float angle, bool immediate);                        // 0x0059B2F0
    void SetLookAtEnabled(int enabled);                                      // 0x0059B420
    void SetLastAnimationPlayed(uint32_t animID);                            // 0x007CD950 (folded)

    EA::AutoRefCount<cAnimatingCreature> mAnimatingCreature;   // +0x8
    cIModelWorld* mModelWorld;                                 // +0xc
    char pad_10[0x4c - 0x10];
    float mMovementSpeed;                                      // +0x4c
    float mRotationSpeed;                                      // +0x50
    char pad_54[0x84 - 0x54];
    bool mIsTurning;                                           // +0x84
};

// Creature description block filled from an editor model (ctor 0x004BACC0, dtor 0x004BAD50)
struct cCreatureBlockData { char pad_0[0x38]; cSPVector3 mBounds[3]; };
struct cCreatureRigData { void Assign(const void* src); };            // 0x006DF280
struct RefVector { RefVector& operator=(const void* src); };          // 0x0041EBE0
struct cCreatureBlock {
    cCreatureBlockData* mpData;   // +0x0
    uint32_t pad_4;
    cCreatureRigData mRig;        // +0x8
    uint32_t pad_c[5];
    RefVector mRefs;              // +0x20
    uint32_t pad_24[5];
    cCreatureBlock();
    ~cCreatureBlock();
};
struct cEditorModel { char pad_0[0xb8]; char mRig[0xe4 - 0xb8]; char mRefs[0xfc - 0xe4]; int mFC; int m100; };
struct cEditorSkin {
    char pad_0[0x10]; int m10;
    cSPVector3* GetBound(cSPVector3* out, int index);                   // 0x004ADCA0
};
void BuildCreatureBlock(cEditorModel* model, cCreatureBlock* block, bool skinned, int flags);   // 0x0046AAC0
void BuildCreatureRig(cEditorModel* model, int skin, int a, int b);                            // 0x0046DAD0
void FinalizeCreatureBlock(cCreatureBlock* block);                                             // 0x0046B460

class cSPEditorAnimatedCreatureManager : public EA::RefCountTemplate<int> {
public:
    cSPEditorAnimatedCreatureManager();
    virtual ~cSPEditorAnimatedCreatureManager();

    void Shutdown();
    void RemoveCreature(uint32_t id);
    uint32_t AddCreature(cEditorSkin* skin, cEditorModel* model, bool fromModel, bool skinned);
    uint32_t AddCreature(const void* key);
    cAnimatingCreature* GetCreature(uint32_t id);
    cSPEditorAnimatedCreatureData* GetCreatureStructure(uint32_t id);
    void PlayAnimation(uint32_t id, uint32_t animID);
    void AddDelayedEvent(EA::AutoRefCount<cSPEditorAnimatedEventInfo> event);
    void SetCreatureIdle(uint32_t id);
    bool IsAnimationPlaying(uint32_t id, uint32_t animID);
    bool IsPlayingAnimation(uint32_t id);
    bool IsAnimationDone(uint32_t id);
    void SetCreatureVisible(uint32_t id, bool visible);
    void SetCreatureTargetAngle(uint32_t id, float angle, bool immediate);
    void SetCreatureTargetPosition(uint32_t id, cSPVector3 pos, bool immediate, bool raw);
    void SetCreaturePreserveHeight(uint32_t id, bool preserve);
    void SetCreatureLookAtTarget(uint32_t id, const cSPVector3 pos, bool immediate);
    void SetCreatureIsTurning(uint32_t id, bool turning);
    void SetCreatureLookAtEnabled(uint32_t id, int enabled);
    void SetCreatureSpeeds(uint32_t id, float movementSpeed, float rotationSpeed);
    bool GetCreaturePosition(uint32_t id, cSPVector3& pos);
    void SetCreatureTurnRate(uint32_t id, int rate);
    void SetCreatureMoving(uint32_t id, bool moving);
    void ResetCreature(uint32_t id);

    typedef eastl::map<uint32_t, EA::AutoRefCount<cSPEditorAnimatedCreatureData> > CreatureMap;
    CreatureMap mAnimatedCreatures;                                                                  // +0x8
    eastl::vector<EA::AutoRefCount<cSPEditorAnimatedEventInfo>, eastl::sp_vector_allocator> mDelayedAnimatedEvents;  // +0x24
    EA::AutoRefCount<cISPCreatureAnimWorld>     mAnimWorld;     // +0x38
    EA::AutoRefCount<cSPEditorAnimationManager> mAnimManager;   // +0x3c
    EA::AutoRefCount<cIModelWorld>              mModelWorld;    // +0x40
    uint32_t                                    mCurrentID;     // +0x44
};

}  // namespace SP

using namespace SP;

// @ 0x0059c4c0
template <typename Key, typename T>
void eastl::map<Key, T>::DoNukeSubtree(node_type* pNode)
{
    while (pNode) {
        DoNukeSubtree((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

// @ 0x0059c740
template <typename Key, typename T>
T& eastl::map<Key, T>::operator[](const Key& key)
{
    iterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, itLower->first))
        itLower = insert(itLower, value_type(key, T()));
    return itLower->second;
}

template class eastl::map<uint32_t, EA::AutoRefCount<cSPEditorAnimatedCreatureData> >;

// @ 0x0059c5f0
cSPEditorAnimatedCreatureManager::~cSPEditorAnimatedCreatureManager()
{
}

// @ 0x0059c640
void cSPEditorAnimatedCreatureManager::Shutdown()
{
    if (mAnimWorld) {
        for (CreatureMap::iterator it = mAnimatedCreatures.begin(); it != mAnimatedCreatures.end(); ++it) {
            mAnimWorld->RemoveCreature(it->second->mAnimatingCreature);
            it->second->Shutdown();
        }
        mAnimatedCreatures.clear();
        mAnimWorld->Update();
        mAnimWorld.Reset();
    }
    if (mAnimManager) {
        mAnimManager->Shutdown();
        mAnimManager.Reset();
    }
}

// @ 0x0059c6e0
void cSPEditorAnimatedCreatureManager::RemoveCreature(uint32_t id)
{
    CreatureMap::iterator it;
    it = mAnimatedCreatures.find(id);
    if (mAnimWorld && it != mAnimatedCreatures.end()) {
        mAnimWorld->RemoveCreature(it->second->mAnimatingCreature);
        it->second->Shutdown();
        mAnimatedCreatures.erase(it);
    }
}

// @ 0x0059c7c0
cSPEditorAnimatedCreatureManager::cSPEditorAnimatedCreatureManager()
    : mCurrentID(1)
{
}

// @ 0x0059c830
uint32_t cSPEditorAnimatedCreatureManager::AddCreature(cEditorSkin* skin, cEditorModel* model, bool fromModel, bool skinned)
{
    uint32_t id = 0;
    if (mAnimWorld && skin && model) {
        id = mCurrentID;
        cCreatureBlock block;
        if (fromModel) {
            BuildCreatureBlock(model, &block, skinned, 0);
            BuildCreatureRig(model, skin->m10, model->mFC, model->m100);
            block.mRig.Assign(model->mRig);
            block.mRefs = model->mRefs;
        } else
            BuildCreatureBlock(model, &block, skinned, 0);
        if (skinned)
            FinalizeCreatureBlock(&block);
        if (block.mpData) {
            for (int i = 0; i < 3; i++)
                block.mpData->mBounds[i] = *skin->GetBound(&cSPVector3(), i);
        }
        cAnimatingCreature* creature = mAnimWorld->CreateCreature(&block, 2, &kZeroVector, kIdentityQuat, true);
        if (creature) {
            cSPEditorAnimatedCreatureData* data = new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedCreatureData();
            mAnimatedCreatures[id] = data;
            data->Init(creature, mModelWorld);
            creature->mFlags |= 1;
            creature->mState = 2;
            mCurrentID++;
        }
    }
    return id;
}

// @ 0x0059c9c0
uint32_t cSPEditorAnimatedCreatureManager::AddCreature(const void* key)
{
    uint32_t id = 0;
    if (mAnimWorld && key) {
        id = mCurrentID;
        cAnimatingCreature* creature = mAnimWorld->CreateCreature(key, 2, &kZeroVector, kIdentityQuat, true);
        if (creature) {
            cSPEditorAnimatedCreatureData* data = new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedCreatureData();
            mAnimatedCreatures[id] = data;
            data->Init(creature, mModelWorld);
            creature->mFlags |= 1;
            creature->mState = 2;
            mCurrentID++;
        }
    }
    return id;
}

// @ 0x0059ca70
cAnimatingCreature* cSPEditorAnimatedCreatureManager::GetCreature(uint32_t id)
{
    if (mAnimWorld && mAnimatedCreatures.find(id) != mAnimatedCreatures.end())
        return mAnimatedCreatures[id]->mAnimatingCreature;
    return 0;
}

// @ 0x0059cac0
cSPEditorAnimatedCreatureData* cSPEditorAnimatedCreatureManager::GetCreatureStructure(uint32_t id)
{
    if (mAnimWorld && mAnimatedCreatures.find(id) != mAnimatedCreatures.end())
        return mAnimatedCreatures[id];
    return 0;
}

// @ 0x0059cb10
void cSPEditorAnimatedCreatureManager::PlayAnimation(uint32_t id, uint32_t animID)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (mAnimManager && data && data->mAnimatingCreature) {
        data->mAnimatingCreature->PlayAnimation(animID, 0);
        data->SetLastAnimationPlayed(animID);
    }
}

// @ 0x0059cb80
void cSPEditorAnimatedCreatureManager::AddDelayedEvent(EA::AutoRefCount<cSPEditorAnimatedEventInfo> event)
{
    if (mAnimManager)
        mDelayedAnimatedEvents.push_back(event);
}

// @ 0x0059cbd0
void cSPEditorAnimatedCreatureManager::SetCreatureIdle(uint32_t id)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (mAnimManager && creature)
        creature->SetIdle(0);
}

// @ 0x0059cc40
bool cSPEditorAnimatedCreatureManager::IsAnimationPlaying(uint32_t id, uint32_t animID)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature) {
        int count = 0;
        creature->GetCurrentAnimation(0, 0, &count, 0);
        if (count < 1 && !creature->IsAnimationDone(0)) {
            uint32_t currentID = 0;
            creature->GetCurrentAnimation(&currentID, 0, 0, 0);
            if (currentID == animID)
                return !creature->IsAnimationLooping(0);
            return creature->IsAnimationQueued(animID) != 0;
        }
    }
    return false;
}

// @ 0x0059cd20
bool cSPEditorAnimatedCreatureManager::IsPlayingAnimation(uint32_t id)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature) {
        int count = 0;
        creature->GetCurrentAnimation(0, 0, &count, 0);
        if (count < 1 && !creature->IsAnimationDone(0))
            return true;
    }
    return false;
}

// @ 0x0059cdb0
bool cSPEditorAnimatedCreatureManager::IsAnimationDone(uint32_t id)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature && !creature->IsAnimationDone(0)) {
        cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
        if (data)
            return data->IsAnimInterruptible();
    }
    return true;
}

// @ 0x0059ce30
void cSPEditorAnimatedCreatureManager::SetCreatureVisible(uint32_t id, bool visible)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature) {
        if (visible)
            creature->mFlags |= 1;
        else
            creature->mFlags &= ~1;
    }
}

// @ 0x0059cea0
void cSPEditorAnimatedCreatureManager::SetCreatureTargetAngle(uint32_t id, float angle, bool immediate)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data)
        data->SetTargetAngle(angle, immediate);
}

// @ 0x0059cf00
void cSPEditorAnimatedCreatureManager::SetCreatureTargetPosition(uint32_t id, cSPVector3 pos, bool immediate, bool raw)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data)
        data->SetTargetPosition(pos, immediate, raw);
}

// @ 0x0059cf60
void cSPEditorAnimatedCreatureManager::SetCreaturePreserveHeight(uint32_t id, bool preserve)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data)
        data->SetPreserveHeight(preserve);
}

// @ 0x0059cfb0
void cSPEditorAnimatedCreatureManager::SetCreatureLookAtTarget(uint32_t id, const cSPVector3 pos, bool immediate)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data)
        data->SetLookAtTarget(pos, immediate);
}

// @ 0x0059d010
void cSPEditorAnimatedCreatureManager::SetCreatureIsTurning(uint32_t id, bool turning)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data)
        data->mIsTurning = turning;
}

// @ 0x0059d060
void cSPEditorAnimatedCreatureManager::SetCreatureLookAtEnabled(uint32_t id, int enabled)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data)
        data->SetLookAtEnabled(enabled);
}

// @ 0x0059d0b0
void cSPEditorAnimatedCreatureManager::SetCreatureSpeeds(uint32_t id, float movementSpeed, float rotationSpeed)
{
    cSPEditorAnimatedCreatureData* data = GetCreatureStructure(id);
    if (data) {
        data->mMovementSpeed = movementSpeed;
        data->mRotationSpeed = rotationSpeed;
    }
}

// @ 0x0059d110
bool cSPEditorAnimatedCreatureManager::GetCreaturePosition(uint32_t id, cSPVector3& pos)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature) {
        pos = creature->mPosition;
        return true;
    }
    return false;
}

// @ 0x0059d180
void cSPEditorAnimatedCreatureManager::SetCreatureTurnRate(uint32_t id, int rate)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature)
        creature->SetTurnRate(rate);
}

// @ 0x0059d1e0
void cSPEditorAnimatedCreatureManager::SetCreatureMoving(uint32_t id, bool moving)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (creature)
        creature->SetMoving(moving);
}

// @ 0x0059d240
void cSPEditorAnimatedCreatureManager::ResetCreature(uint32_t id)
{
    cAnimatingCreature* creature = GetCreature(id);
    if (mAnimManager && creature) {
        SetCreatureTargetPosition(id, kZeroVector, true, true);
        int anim = creature->PlayAnimation(0x4330667, 0);
        if (creature->mpHelper)
            creature->mpHelper->OnAnimationStarted(anim);
    }
}

