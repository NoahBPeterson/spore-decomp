// Slice s00df10d0 -- SP::tNewGameFlow::ReadPropList (0x00df10d0, 2755 bytes).
//
// Reads the "new game flow" property list: clears the three state/button/summary hash_maps and the
// panel-order vector, then for every enabled "ChooseXxx" bool adds a panel (state -> button ID,
// button ID -> state, state -> summary-field ID, from two static per-panel-index tables), reads a set
// of uint32 string/layout IDs and one bool into members, and finally fills two uint32 vectors (one
// straight from a uint32 array property, one with FNV hashes of a string16 array property).
//
// Module flags (same module as s00df47b0): /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc.
// The retail class is larger than the 2008 PDB layout (hash_maps instead of maps, extra fields), so
// the fields past the maps are named by role at their retail offsets.
#include "types.h"
#include <new>
#include <string.h>

namespace eastl {

struct allocator {
    allocator() {}
};

template <typename T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;
    const T* c_str() const { return mpBegin; }
};
typedef basic_string<wchar_t> string16;

template <typename T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    void DoInsertValue(T* position, const T& value);   // 0x004558a0 (vector<uint32_t>)
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct hash_node_u32;

// hash_map<uint32_t, uint32_t>
struct hash_map_u32_u32 {
    uint32_t mEmptyBases;   // the empty hash/equal functor bases occupy 4 bytes under MSVC
    hash_node_u32** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    allocator mAllocator;

    void DoFreeNodes(hash_node_u32** pBucketArray, uint32_t n);   // 0x005687d0 (folded instance)
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    uint32_t& operator[](const uint32_t& key);   // 0x00ad3da0
};

}  // namespace eastl

using eastl::string16;

// ---- properties ----
struct Property {
    uint32_t mData[4];
    uint16_t mFlags;   // +0x10
    uint16_t mType;    // +0x12 (1 bool, 10 uint32)
    bool* GetValueBool();       // 0x0041e920
    uint32_t* GetValueUInt32(); // 0x0041ea00
};

struct cPropList {
    virtual int AddRef();
    virtual int Release();
    virtual void pv2(); virtual void pv3(); virtual void pv4(); virtual void pv5(); virtual void pv6();
    virtual void pv7(); virtual void pv8();
    virtual bool GetProperty(uint32_t id, Property*& result);   // +0x24
};

template <typename T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    intrusive_ptr& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    void reset_null()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* get() const { return mpObject; }
};
typedef intrusive_ptr<cPropList> PropListPtr;

struct cPropManager {
    virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
    virtual void pv4(); virtual void pv5(); virtual void pv6(); virtual void pv7();
    virtual void pv8(); virtual void pv9(); virtual void pv10();
    virtual bool GetPropertyListImpl(uint32_t instanceID, uint32_t groupID, PropListPtr& dst);   // +0x2c
    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropListPtr& dst)
    {
        dst.reset_null();
        return GetPropertyListImpl(instanceID, groupID, dst);
    }
};
cPropManager* PropertyManager();   // 0x0067de30

static inline bool GetBool(const cPropList* list, uint32_t id, bool& value)
{
    Property* prop;
    if (list && ((cPropList*)list)->GetProperty(id, prop) && prop->mType == 1) {
        value = *prop->GetValueBool();
        return true;
    }
    return false;
}
static inline bool GetUInt32(const cPropList* list, uint32_t id, uint32_t& value)
{
    Property* prop;
    if (list && ((cPropList*)list)->GetProperty(id, prop) && prop->mType == 10) {
        value = *prop->GetValueUInt32();
        return true;
    }
    return false;
}

bool GetPropertyAsUint32Array(const cPropList* list, uint32_t id, int& count, uint32_t*& dst);   // 0x006a0840
bool GetPropertyAsString16Array(const cPropList* list, uint32_t id, int& count, string16*& dst);  // 0x006a0bc0

namespace EA { namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, bool lowercase);       // 0x00932e80
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, bool lowercase);   // 0x00932f30
} }
static inline uint32_t id(const char* s) { return EA::Hash::FNV1_String8(s, 0x811c9dc5, true); }
static inline uint32_t id(const wchar_t* s) { return EA::Hash::FNV1_String16(s, 0x811c9dc5, true); }

bool IsWorldLayoutFlagSet(int index);   // 0x00685520 (byte flag of a 0x28-byte world layout entry)

extern const uint32_t kGUI_PanelButtonIDs[];    // 0x0147e4d8
extern const uint32_t kGUI_PanelSummaryIDs[];   // 0x0147e51c

namespace SP {

enum GameState { kStateNone = 0 };

class tNewGameFlow {
public:
    void ReadPropList(uint32_t instanceID);

    __forceinline void AddPanel(GameState state)
    {
        uint32_t buttonID = kGUI_PanelButtonIDs[mNumPanels];
        mStateToButtonMap[state] = buttonID;
        mButtonToStateMap[kGUI_PanelButtonIDs[mNumPanels]] = state;
        uint32_t summaryID = kGUI_PanelSummaryIDs[mNumPanels];
        mStateToSummaryFieldMap[state] = summaryID;
        mNumPanels++;
    }

    eastl::hash_map_u32_u32 mButtonToStateMap;        // +0x00
    eastl::hash_map_u32_u32 mStateToButtonMap;        // +0x20
    eastl::hash_map_u32_u32 mStateToSummaryFieldMap;  // +0x40
    eastl::vector<uint32_t> mPanelOrder;              // +0x60
    uint32_t m70;
    eastl::vector<uint32_t> mFlowIDs;                 // +0x74
    uint32_t m84;
    uint32_t mNumPanels;                              // +0x88
    uint32_t mChooseYourPanelStringID;                // +0x8c
    uint32_t mIdentitySummaryStringID;                // +0x90
    uint32_t m94;
    uint32_t m98;
    uint32_t m9c;
    uint32_t mA0;
    uint32_t mA4;
    uint32_t mA8;
    uint32_t mAC;
    uint32_t mB0;
    uint32_t mB4;
    uint32_t mB8;
    bool mBC;
};

void tNewGameFlow::ReadPropList(uint32_t instanceID)
{
    mStateToButtonMap.clear();
    mButtonToStateMap.clear();
    mPanelOrder.clear();
    PropListPtr propList;
    mNumPanels = 0;
    mChooseYourPanelStringID = 0;

    if (PropertyManager()->GetPropertyList(instanceID, 0, propList)) {

        bool bValue;
        GetBool(propList.get(), id("ChooseName"), bValue);
        if (bValue)
            AddPanel((GameState)4);
        GetBool(propList.get(), id("ChooseDifficulty"), bValue);
        if (bValue)
            AddPanel((GameState)5);
        GetBool(propList.get(), id("ChooseTheme"), bValue);
        if (bValue)
            AddPanel((GameState)6);
        GetBool(propList.get(), id("ChooseSpecialty"), bValue);
        if (bValue)
            AddPanel((GameState)7);
        GetBool(propList.get(), id("ChooseAssets"), bValue);
        if (bValue)
            AddPanel((GameState)8);
        GetBool(propList.get(), id("ChooseCreature"), bValue);
        if (bValue)
            AddPanel((GameState)3);
        GetBool(propList.get(), id("ChooseDiet"), bValue);
        if (bValue)
            AddPanel((GameState)2);
        GetBool(propList.get(), id("ChooseCreatureAndAssetsTogether"), bValue);
        if (bValue)
            AddPanel((GameState)9);
        if (IsWorldLayoutFlagSet(2)) {
            GetBool(propList.get(), id("ChooseCaptainName"), bValue);
            if (bValue)
                AddPanel((GameState)10);
        }

        mStateToSummaryFieldMap[1] = 0x05a72f75;

        GetUInt32(propList.get(), 0x7075c07e, mChooseYourPanelStringID);
        GetUInt32(propList.get(), 0xf2f72138, mIdentitySummaryStringID);
        GetBool(propList.get(), 0x25844b66, mBC);
        GetUInt32(propList.get(), 0x10b6634e, mAC);
        GetUInt32(propList.get(), 0xb3ae8587, mB0);
        GetUInt32(propList.get(), 0x525760b1, mB4);
        GetUInt32(propList.get(), 0x182d5e45, m94);
        GetUInt32(propList.get(), 0x0aa450b4, m98);
        GetUInt32(propList.get(), 0xd07e6aee, m9c);
        GetUInt32(propList.get(), 0x2a29cc75, mA0);
        GetUInt32(propList.get(), 0x296042c0, mA4);
        GetUInt32(propList.get(), 0xe10ae352, mA8);
        GetUInt32(propList.get(), 0xd047a893, mB8);

        int count;
        uint32_t* values;
        if (GetPropertyAsUint32Array(propList.get(), 0xc06f6c08, count, values)) {
            for (int i = 0; i < count; i++)
                mPanelOrder.push_back(values[i]);
        }

        mFlowIDs.clear();
        string16* names;
        if (GetPropertyAsString16Array(propList.get(), 0x578f6aed, count, names)) {
            for (int i = 0; i < count; i++)
                mFlowIDs.push_back(id(names[i].c_str()));
        }
    }
}

}  // namespace SP
