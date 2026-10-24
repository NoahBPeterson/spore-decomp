// src/game/SPEditors/SPEditorAppEconomy.cpp -- migrated from slice(s) s0059e360 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorAppEconomy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorAppEconomy.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cISPEditorAbilityProvider.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorEconomy.h"
#include "SP/cString.h"
#include <xmmintrin.h>
#include "EA/AutoRefCount.h"

// ---- items of slice s0059e360 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
class RefCountTemplate_s0059_e360 {
public:
    RefCountTemplate_s0059_e360() : mnRefCount(0) {}
    virtual ~RefCountTemplate_s0059_e360() {}
protected:
    T mnRefCount;   // +0x4
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0059_e360 {
public:
    T* mpObject;
    AutoRefCount_s0059_e360() : mpObject(0) {}
    AutoRefCount_s0059_e360(T* p) : mpObject(p) { if (p) p->AddRef(); }
    AutoRefCount_s0059_e360(const AutoRefCount_s0059_e360& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0059_e360() { if (mpObject) mpObject->Release(); }
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
}
namespace eastl {
struct sp_vector_allocator_s0059_e360 {
    uint32_t mData[2];
    sp_vector_allocator_s0059_e360() {}
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};
}
namespace eastl {
template <typename T>
class vector_s0059_e360 {
public:
    T*                  mpBegin;      // +0x0
    T*                  mpEnd;        // +0x4
    T*                  mpCapacity;   // +0x8
    sp_vector_allocator_s0059_e360 mAllocator;   // +0xc
    vector_s0059_e360() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector_s0059_e360()
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
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
namespace App {
struct Property {
    char     pad_0[0x12];
    uint16_t mnType;           // +0x12
    int* GetValueInt32();      // 0x0041E990
};
}
namespace SP {
class cString_s0059_e360 {
public:
    void Load(uint32_t tableID, uint32_t instanceID, int flags);   // 0x006B54B0
    uint32_t pad[5];
};
}
namespace SP {
class cPropertyList_s0059_e360 {
public:
    virtual void AddRef();
    virtual void Release();
virtual void Unk2();
virtual void Unk3();
virtual void Unk4();
virtual void Unk5();
virtual void Unk6();
virtual void Unk7();
virtual void Unk8();
    virtual bool GetProperty(uint32_t propID, App::Property*& prop);   // slot 9
};
}
namespace SP {
class cDirectPropertyList_s0059_e360 {
public:
    bool GetBool(uint32_t propID);   // 0x006A25A0
};
}
namespace SP {
extern cDirectPropertyList_s0059_e360* sAppProperties;   // 0x015FD918
}
namespace SP {
class cPropertyManager_s0059_e360 {
public:
virtual void Unk0();
virtual void Unk1();
virtual void Unk2();
virtual void Unk3();
virtual void Unk4();
virtual void Unk5();
virtual void Unk6();
virtual void Unk7();
virtual void Unk8();
virtual void Unk9();
virtual void Unk10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s0059_e360** ppList);   // slot 11
};
}
namespace SP {
cPropertyManager_s0059_e360* PropertyManager();   // 0x0067DE30
}
namespace SP {
class cComplexityManager {
public:
virtual void Unk0();
virtual void Unk1();
virtual void Unk2();
virtual void Unk3();
virtual void Unk4();
virtual void Unk5();
virtual void Unk6();
virtual void Unk7();
virtual void Unk8();
virtual void Unk9();
virtual void Unk10();
virtual void Unk11();
virtual void Unk12();
virtual void Unk13();
virtual void Unk14();
virtual void Unk15();
virtual void Unk16();
virtual void Unk17();
virtual void Unk18();
virtual void Unk19();
virtual void Unk20();
virtual void Unk21();
virtual void Unk22();
virtual void Unk23();
virtual void Unk24();
virtual void Unk25();
virtual void Unk26();
    virtual float GetComplexity(cPropertyList_s0059_e360* propList);   // slot 27
};
}
namespace SP {
cComplexityManager* ComplexityManager();   // 0x00401010
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s0059_e360* list, uint32_t propID, uint32_t* pValue);   // 0x006A12A0
}
namespace SP {
bool TryGetUIntProperty(cPropertyList_s0059_e360* list, uint32_t propID, uint32_t* pValue);         // 0x00410370
}
namespace SP {
inline bool GetPropertyInt(cPropertyList_s0059_e360* list, uint32_t propID, int& value)
{
    App::Property* prop;
    if (list && list->GetProperty(propID, prop) && prop->mnType == 9) {
        value = *prop->GetValueInt32();
        return true;
    }
    return false;
}
}
namespace SP {
extern const float kComplexityCostScale;   // 0x01470F1C
}
namespace SP {
inline int CeilToInt(float f)
{
    int i = _mm_cvt_ss2si(_mm_load_ss(&f));
    if ((float)i < f)
        i = i + 1;
    return i;
}
}
namespace SP {
class cSPEditorBlock_s0059_e360 {
public:
    virtual void Unk0();
    virtual void AddRef();
    virtual void Release();
    char pad_4[0x3e0 - 0x4];
    cSPEditorBlock_s0059_e360* mpSymmetricBlock;   // +0x3e0
    char pad_3e4[0x5e4 - 0x3e4];
    int   mCost;                        // +0x5e4
    int   mCost1;                       // +0x5e8
    int   mCost2;                       // +0x5ec
    int   mCost3Type;                   // +0x5f0
    float mComplexity;                  // +0x5f4
    char pad_5f8[0xdc8 - 0x5f8];
    uint32_t mFlags;                    // +0xdc8
};
}
namespace SP {
struct cCantAffordReason {
    cString_s0059_e360  mTitle;      // +0x0
    cString_s0059_e360  mText;       // +0x14
    uint32_t mUnk28;      // +0x28
    uint32_t mImageID;    // +0x2c
    bool     mbBlocking;  // +0x30
};
}
namespace SP {
class cSPEditorEconomy_s0059_e360 : public EA::RefCountTemplate_s0059_e360<int> {
public:
    void SendChangedMessage();   // 0x005A7840
};
}
namespace SP {
class cSPEditorAppEconomy_s0059_e360 : public cSPEditorEconomy_s0059_e360 {
public:
    virtual void Init(int numTypes);                                              // slot 1
    virtual void SetBalanceCap(int type, int cap);                                // slot 2
    virtual bool CanAfford(int type, int amount);                                 // slot 3
    virtual int  CanAffordWithReason(const ResourceKey& key, cCantAffordReason* pReason);   // slot 4 0x0059e580
    virtual bool CanAffordBlock(cSPEditorBlock_s0059_e360* block);                           // slot 5
    virtual bool CanAffordBlockPile(cSPEditorBlock_s0059_e360* block);                       // slot 6
    virtual void EnforceBalanceCap(int type);                                     // slot 7
    virtual void AdjustWealth(int type, int delta);                               // slot 8
    virtual void SetWealth(int type, int value);                                  // slot 9
    virtual int  GetWealth(int type);                                             // slot 10
    virtual void AddBlockValue(cSPEditorBlock_s0059_e360* block);                            // slot 11
    virtual void DeductBlockValue(cSPEditorBlock_s0059_e360* block);                         // slot 12
    virtual void DeductBlockPileValue(cSPEditorBlock_s0059_e360* block, int mode);           // slot 13
    bool CanAfford(const ResourceKey& key);

    eastl::vector_s0059_e360<int> mBalances;      // +0x8
    eastl::vector_s0059_e360<int> mBalanceCaps;   // +0x1c
};
}
// ---- items of slice s0059e360 end

// @ 0x0059e580
int SP::cSPEditorAppEconomy_s0059_e360::CanAffordWithReason(const ResourceKey& key, SP::cCantAffordReason* pReason)
{
    bool limited = !SP::sAppProperties->GetBool(0x677d3ea);
    EA::AutoRefCount_s0059_e360<SP::cPropertyList_s0059_e360> propList;
    SP::PropertyManager()->GetPropertyList(key.instanceID, key.groupID, propList.AsPPTypeParam());

    int value = 0;
    SP::GetPropertyInt(propList, 0x3c652302, value);
    if (!limited || CanAfford(1, value * 2)) {
        value = 0;
        SP::GetPropertyInt(propList, 0x51fa9dfa, value);
        if (!limited || CanAfford(2, value * 2)) {
            int count = 1;
            uint32_t type = 0;
            SP::GetPropertyAsKeyInstance(propList, 0x2196ad5, &type);
            if (type == 0xc9db779b)
                SP::GetPropertyInt(propList, 0x4dbcdd2, count);
            else {
                int n;
                if (SP::GetPropertyInt(propList, 0x4460b63, n) && n >= 2)
                    count = 0;
            }
            if (CanAfford(3, count * 2) && CanAfford(5, 2)) {
                float complexity = SP::ComplexityManager()->GetComplexity(propList);
                if (limited && !CanAfford(4, SP::CeilToInt(complexity * SP::kComplexityCostScale))) {
                    if (pReason) {
                        pReason->mTitle.Load(0x496bfb26, 0x102, 0);
                        pReason->mText.Load(0x496bfb26, 0x202, 0);
                        pReason->mImageID = 0x22c4855f;
                    }
                    return 3;
                }
                uint32_t cost = 0;
                SP::TryGetUIntProperty(propList, 0x2166464, &cost);
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
