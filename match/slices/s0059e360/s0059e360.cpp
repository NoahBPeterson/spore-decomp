// slice s0059e360 — SP::cSPEditorAppEconomy (retail layout: wealth balances/caps, block affordability)
// and SP::cSPEditorVehicleAbilities construction.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
// cSPEditorVerbIconData / vector helpers (an x87 module) live in s0059e360_b.cpp.
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int size_t;

// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

struct ResourceKey {
    uint32_t instanceID;   // +0x0
    uint32_t typeID;       // +0x4
    uint32_t groupID;      // +0x8
};

namespace EA {

template <typename T>
class RefCountTemplate {
public:
    RefCountTemplate() : mnRefCount(0) {}
    virtual ~RefCountTemplate() {}
protected:
    T mnRefCount;   // +0x4
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

}  // namespace EA

namespace eastl {

struct sp_vector_allocator {
    uint32_t mData[2];
    sp_vector_allocator() {}
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};

template <typename T>
class vector {
public:
    T*                  mpBegin;      // +0x0
    T*                  mpEnd;        // +0x4
    T*                  mpCapacity;   // +0x8
    sp_vector_allocator mAllocator;   // +0xc
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
    }
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    T& operator[](size_t n) { return mpBegin[n]; }
    void resize(size_t n, const T& value);              // 0x004746C0 (int instance)
    T* DoInsertValue(T* position, const T& value);      // 0x00454EE0 (AutoRefCount<cSPEditorBlock> instance)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};

// eastl::map<uint32_t, uint32_t> (2008 layout, 0x1C bytes)
struct uint_map {
    uint32_t         mCompare;    // +0x0 (empty less<>)
    rbtree_node_base mAnchor;     // +0x4
    uint32_t         mnSize;      // +0x14
    uint32_t         mAllocator;  // +0x18 (empty allocator)
    uint_map() : mAnchor(), mnSize(0) { reset(); }
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
};

}  // namespace eastl

namespace App {
struct Property {
    char     pad_0[0x12];
    uint16_t mnType;           // +0x12
    int* GetValueInt32();      // 0x0041E990
};
}

namespace SP {

class cString {
public:
    void Load(uint32_t tableID, uint32_t instanceID, int flags);   // 0x006B54B0
    uint32_t pad[5];
};

class cPropertyList {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void Unk2(); virtual void Unk3(); virtual void Unk4(); virtual void Unk5();
    virtual void Unk6(); virtual void Unk7(); virtual void Unk8();
    virtual bool GetProperty(uint32_t propID, App::Property*& prop);   // slot 9
};

class cDirectPropertyList {
public:
    bool GetBool(uint32_t propID);   // 0x006A25A0
};
extern cDirectPropertyList* sAppProperties;   // 0x015FD918

class cPropertyManager {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5(); virtual void Unk6(); virtual void Unk7();
    virtual void Unk8(); virtual void Unk9(); virtual void Unk10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppList);   // slot 11
};
cPropertyManager* PropertyManager();   // 0x0067DE30

class cComplexityManager {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5(); virtual void Unk6(); virtual void Unk7();
    virtual void Unk8(); virtual void Unk9(); virtual void Unk10(); virtual void Unk11();
    virtual void Unk12(); virtual void Unk13(); virtual void Unk14(); virtual void Unk15();
    virtual void Unk16(); virtual void Unk17(); virtual void Unk18(); virtual void Unk19();
    virtual void Unk20(); virtual void Unk21(); virtual void Unk22(); virtual void Unk23();
    virtual void Unk24(); virtual void Unk25(); virtual void Unk26();
    virtual float GetComplexity(cPropertyList* propList);   // slot 27
};
cComplexityManager* ComplexityManager();   // 0x00401010

bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t propID, uint32_t* pValue);   // 0x006A12A0
bool TryGetUIntProperty(cPropertyList* list, uint32_t propID, uint32_t* pValue);         // 0x00410370

inline bool GetPropertyInt(cPropertyList* list, uint32_t propID, int& value)
{
    App::Property* prop;
    if (list && list->GetProperty(propID, prop) && prop->mnType == 9) {
        value = *prop->GetValueInt32();
        return true;
    }
    return false;
}

extern const float kComplexityCostScale;   // 0x01470F1C

inline int CeilToInt(float f)
{
    int i = _mm_cvt_ss2si(_mm_load_ss(&f));
    if ((float)i < f)
        i = i + 1;
    return i;
}


class cSPEditorBlock {
public:
    virtual void Unk0();
    virtual void AddRef();
    virtual void Release();
    char pad_4[0x3e0 - 0x4];
    cSPEditorBlock* mpSymmetricBlock;   // +0x3e0
    char pad_3e4[0x5e4 - 0x3e4];
    int   mCost;                        // +0x5e4
    int   mCost1;                       // +0x5e8
    int   mCost2;                       // +0x5ec
    int   mCost3Type;                   // +0x5f0
    float mComplexity;                  // +0x5f4
    char pad_5f8[0xdc8 - 0x5f8];
    uint32_t mFlags;                    // +0xdc8
};

typedef eastl::vector<EA::AutoRefCount<cSPEditorBlock> > BlockVector;
int  GetBlockPileValue(cSPEditorBlock* block, int mode);                 // 0x00491350
void GetBlockPile(cSPEditorBlock* block, BlockVector* blocks, int flags);  // 0x0048C790

struct cCantAffordReason {
    cString  mTitle;      // +0x0
    cString  mText;       // +0x14
    uint32_t mImageID;    // +0x2c
    bool     mbBlocking;  // +0x30
};

class cSPEditorEconomy : public EA::RefCountTemplate<int> {
public:
    void SendChangedMessage();   // 0x005A7840
};

class cSPEditorAppEconomy : public cSPEditorEconomy {
public:
    virtual void Init(int numTypes);                                              // slot 1
    virtual void SetBalanceCap(int type, int cap);                                // slot 2
    virtual bool CanAfford(int type, int amount);                                 // slot 3
    virtual int  CanAffordWithReason(const ResourceKey& key, cCantAffordReason* pReason);   // slot 4
    virtual bool CanAffordBlock(cSPEditorBlock* block);                           // slot 5
    virtual bool CanAffordBlockPile(cSPEditorBlock* block);                       // slot 6
    virtual void EnforceBalanceCap(int type);                                     // slot 7
    virtual void AdjustWealth(int type, int delta);                               // slot 8
    virtual void SetWealth(int type, int value);                                  // slot 9
    virtual int  GetWealth(int type);                                             // slot 10
    virtual void AddBlockValue(cSPEditorBlock* block);                            // slot 11
    virtual void DeductBlockValue(cSPEditorBlock* block);                         // slot 12
    virtual void DeductBlockPileValue(cSPEditorBlock* block, int mode);           // slot 13
    bool CanAfford(const ResourceKey& key);

    eastl::vector<int> mBalances;      // +0x8
    eastl::vector<int> mBalanceCaps;   // +0x1c
};

}  // namespace SP

using namespace SP;

// @ 0x0059e360
bool cSPEditorAppEconomy::CanAfford(const ResourceKey& key)
{
    return CanAffordWithReason(key, 0) == 1;
}

// @ 0x0059e380
void cSPEditorAppEconomy::AddBlockValue(cSPEditorBlock* block)
{
    AdjustWealth(0, block->mCost);
}

// @ 0x0059e3a0
void cSPEditorAppEconomy::DeductBlockValue(cSPEditorBlock* block)
{
    AdjustWealth(0, -block->mCost);
}

// @ 0x0059e3c0
void cSPEditorAppEconomy::SetBalanceCap(int type, int cap)
{
    mBalanceCaps[type] = cap;
}

// @ 0x0059e3e0
void cSPEditorAppEconomy::EnforceBalanceCap(int type)
{
    int cap = mBalanceCaps[type];
    if (cap && mBalances[type] > cap)
        mBalances[type] = cap;
}

// @ 0x0059e400
void cSPEditorAppEconomy::AdjustWealth(int type, int delta)
{
    if (delta) {
        mBalances[type] += delta;
        EnforceBalanceCap(type);
        SendChangedMessage();
    }
}

// @ 0x0059e430
void cSPEditorAppEconomy::SetWealth(int type, int value)
{
    if (mBalances[type] != value) {
        mBalances[type] = value;
        EnforceBalanceCap(type);
        SendChangedMessage();
    }
}

// @ 0x0059e470
bool cSPEditorAppEconomy::CanAfford(int type, int amount)
{
    return mBalances[type] >= amount;
}

// @ 0x0059e490
bool cSPEditorAppEconomy::CanAffordBlock(cSPEditorBlock* block)
{
    int multiplier = 2;
    if ((block->mFlags >> 7) & 1)
        multiplier = 1;
    if (CanAfford(0, block->mCost) &&
        CanAfford(1, block->mCost1 * multiplier) &&
        CanAfford(2, block->mCost2 * multiplier) &&
        CanAfford(4, CeilToInt((float)multiplier * block->mComplexity))) {
        if (block->mCost3Type == 2 || CanAfford(3, multiplier))
            return CanAfford(5, multiplier);
    }
    return false;
}

// @ 0x0059e580
int cSPEditorAppEconomy::CanAffordWithReason(const ResourceKey& key, cCantAffordReason* pReason)
{
    bool limited = !sAppProperties->GetBool(0x677d3ea);
    EA::AutoRefCount<cPropertyList> propList;
    PropertyManager()->GetPropertyList(key.instanceID, key.groupID, propList.AsPPTypeParam());

    int value = 0;
    GetPropertyInt(propList, 0x3c652302, value);
    if (!limited || CanAfford(1, value * 2)) {
        value = 0;
        GetPropertyInt(propList, 0x51fa9dfa, value);
        if (!limited || CanAfford(2, value * 2)) {
            int count = 1;
            uint32_t type = 0;
            GetPropertyAsKeyInstance(propList, 0x2196ad5, &type);
            if (type == 0xc9db779b)
                GetPropertyInt(propList, 0x4dbcdd2, count);
            else {
                int n;
                if (GetPropertyInt(propList, 0x4460b63, n) && n >= 2)
                    count = 0;
            }
            if (CanAfford(3, count * 2) && CanAfford(5, 2)) {
                float complexity = ComplexityManager()->GetComplexity(propList);
                if (limited && !CanAfford(4, CeilToInt(complexity * kComplexityCostScale))) {
                    if (pReason) {
                        pReason->mTitle.Load(0x496bfb26, 0x102, 0);
                        pReason->mText.Load(0x496bfb26, 0x202, 0);
                        pReason->mImageID = 0x22c4855f;
                    }
                    return 3;
                }
                uint32_t cost = 0;
                TryGetUIntProperty(propList, 0x2166464, &cost);
                if (!CanAfford(0, cost)) {
                    if (pReason) {
                        pReason->mTitle.Load(0x496bfb26, 0x101, 0);
                        pReason->mText.Load(0x496bfb26, 0x201, 0);
                        pReason->mImageID = 0;
                        pReason->mbBlocking = true;
                    }
                    return 2;
                }
                return 1;
            }
        }
    }
    if (pReason) {
        pReason->mTitle.Load(0x496bfb26, 0x102, 0);
        pReason->mText.Load(0x496bfb26, 0x202, 0);
        pReason->mImageID = 0x22c4855f;
    }
    return 3;
}

// @ 0x0059e8d0
bool cSPEditorAppEconomy::CanAffordBlockPile(cSPEditorBlock* block)
{
    if (!CanAfford(0, GetBlockPileValue(block, 2)))
        return false;

    BlockVector blocks;
    GetBlockPile(block, &blocks, 0);
    blocks.push_back(block);
    if (block->mpSymmetricBlock) {
        GetBlockPile(block->mpSymmetricBlock, &blocks, 0);
        blocks.push_back(block->mpSymmetricBlock);
    }

    bool limited = !sAppProperties->GetBool(0x677d3ea);
    size_t numBlocks = blocks.size();
    int cost1 = 0;
    int cost2 = 0;
    int cost3 = 0;
    float complexity = 0.0f;
    for (size_t i = 0; i < blocks.size(); i++) {
        EA::AutoRefCount<cSPEditorBlock> b = blocks[i];
        cost1 += b->mCost1;
        cost2 += b->mCost2;
        complexity += b->mComplexity;
        if (b->mCost3Type != 2)
            cost3++;
    }
    if (limited && (!CanAfford(1, cost1) || !CanAfford(2, cost2)))
        return false;
    if (!CanAfford(3, cost3))
        return false;
    if (limited && !CanAfford(4, CeilToInt(complexity)))
        return false;
    return CanAfford(5, numBlocks);
}

// @ 0x0059eb40
void cSPEditorAppEconomy::DeductBlockPileValue(cSPEditorBlock* block, int mode)
{
    if (mode == 2)
        AdjustWealth(0, -GetBlockPileValue(block, mode));
    else if (mode == 0) {
        BlockVector blocks;
        GetBlockPile(block, &blocks, 0);
        blocks.push_back(block);
        for (size_t i = 0; i < blocks.size(); i++)
            DeductBlockValue(blocks[i]);
    }
}

// @ 0x0059ec80
void cSPEditorAppEconomy::Init(int numTypes)
{
    mBalances.resize(numTypes, 0);
    mBalanceCaps.resize(numTypes, 0);
}

namespace SP {

bool ReadAbilityList(eastl::uint_map* abilities, uint32_t propID);   // 0x004E5180

class cISPEditorAbilityProvider {
public:
    virtual ~cISPEditorAbilityProvider() {}
};

class cRefCounted {
public:
    cRefCounted() : mnRefCount(0) {}
    virtual ~cRefCounted() {}
    int mnRefCount;
};

class cSPEditorVehicleAbilities : public cISPEditorAbilityProvider, public cRefCounted {
public:
    cSPEditorVehicleAbilities(ResourceKey vehicleKey, uint32_t abilityListPropID, uint32_t typeInstance,
                              uint32_t modelType, bool showStats);
    virtual ~cSPEditorVehicleAbilities();
    void SetVehicle(ResourceKey vehicleKey, uint32_t modelType);

    ResourceKey       mVehicleKey;          // +0xc
    ResourceKey       mTypeKey;             // +0x18
    eastl::vector<int> mAbilityLines;       // +0x24
    eastl::uint_map   mAbilities;           // +0x38
    uint32_t          mAbilityListPropId;   // +0x54
    bool              mbHasAbilities;       // +0x58
    uint32_t          mModelType;           // +0x5c
    bool              mbShowStats;          // +0x60
    bool              mb61;                 // +0x61
    bool              mb62;                 // +0x62
    bool              mb63;                 // +0x63
};

}  // namespace SP

// @ 0x0059f030
cSPEditorVehicleAbilities::cSPEditorVehicleAbilities(ResourceKey vehicleKey, uint32_t abilityListPropID,
                                                     uint32_t typeInstance, uint32_t modelType, bool showStats)
{
    mVehicleKey         = vehicleKey;
    mModelType          = 0;
    mb61                = false;
    mb62                = true;
    mb63                = false;
    mAbilityListPropId  = abilityListPropID;
    mTypeKey.instanceID = typeInstance;
    mTypeKey.typeID     = 0x510a95b;
    mTypeKey.groupID    = 0x40464100;
    mbHasAbilities      = false;
    if (abilityListPropID != (uint32_t)-1 && mAbilities.mnSize == 0)
        mbHasAbilities = ReadAbilityList(&mAbilities, abilityListPropID);
    mbShowStats = showStats;
    mModelType  = modelType;
}

// @ 0x0059ece0
void cSPEditorVehicleAbilities::SetVehicle(ResourceKey vehicleKey, uint32_t modelType)
{
    mVehicleKey = vehicleKey;
    mModelType  = modelType;
}

