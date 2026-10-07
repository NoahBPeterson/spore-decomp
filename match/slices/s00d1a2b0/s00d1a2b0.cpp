// Slice s00d1a2b0: SP::cGameEditInputStrategy::ShowGameplayMarkerProperties (level editor UI).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: string locals get no EH frame; no cookie despite the wchar_t buffer).
// Retail layout of cGameEditInputStrategy is the 2008 PDB's shifted by +4 from 0xa4 on
// (mGameplayMarkerRoot 0xa4, mGameplayMarkerArea 0xa8, mGameplayMarkerScrollbar 0xac, mLayout 0xe0).
#include "types.h"
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

// float->int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);

// ------------------------------------------------------------------ EASTL strings
namespace eastl {
extern char gEmptyString[];   // 0x01667bac

struct allocator {
    void* allocate(unsigned int n) {
        return operator new[](n, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    void deallocate(void* p, unsigned int) { operator delete[](p); }
};

template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    basic_string() { AllocateSelf(); }
    __forceinline basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + CharStrlen(p)); }
    ~basic_string() { DeallocateSelf(); }

    static unsigned int CharStrlen(const T* p) {
        const T* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (unsigned int)(pCurrent - p);
    }
    void AllocateSelf() {
        mpBegin = (T*)gEmptyString;
        mpEnd = (T*)gEmptyString;
        mpCapacity = (T*)gEmptyString + 1;
    }
    void AllocateSelf(unsigned int n) {
        if (n > 1) {
            mpBegin = DoAllocate(n);
            mpEnd = mpBegin;
            mpCapacity = mpBegin + n;
        } else
            AllocateSelf();
    }
    T* DoAllocate(unsigned int n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void RangeInitialize(const T* pBegin, const T* pEnd) {
        const unsigned int n = (unsigned int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n * sizeof(T));
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    const T* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    basic_string& assign(const T* pBegin, const T* pEnd);   // 0x00423650 (wchar_t)
    basic_string& operator=(const basic_string& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string& sprintf(const T* pFormat, ...);           // 0x0041e050 (wchar_t)
};
typedef basic_string<char> string8;
typedef basic_string<wchar_t> string16;

template <class It, class Compare> void sort(It first, It last, Compare compare);
}  // namespace eastl

// A vector<uint32_t> whose storage is freed only when the allocation header says so.
struct IdVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    IdVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~IdVector() {
        if (mpBegin && mpBegin[-1] != 0)
            operator delete[](mpBegin);
    }
};

namespace EA {
eastl::string16 ConvertToString16(const eastl::string8& s);   // 0x0093c6d0
eastl::string8 ConvertToString8(const eastl::string16& s);    // 0x0093c570
namespace Hash { uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, int caseMode); } // 0x00932f30
namespace IO {
int SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
              wchar_t* pExtension, int flags);                                           // 0x00930180
}
namespace ResourceMan {
struct Key {
    uint32_t instanceID, typeID, groupID;
    Key(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual bool GetFileName(const Key& key, eastl::string16& dst);   // +0x7c
};
IResourceManager* GetManager();   // 0x0067dcd0
}
}  // namespace EA

inline uint32_t id(const wchar_t* p) { return EA::Hash::FNV1_String16(p, 0x811c9dc5, 1); }

// ------------------------------------------------------------------ properties
struct Property {
    union {
        struct { void* mpData; uint32_t mnItemSize; uint32_t mnItemCount; };
        uint32_t mValue[4];
    };
    short mnFlags;     // +0x10
    unsigned short mnType;   // +0x12
    uint32_t GetItemCount() const { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    void* GetValue() { return (mnFlags & 0x30) ? mpData : (mnType ? (void*)this : 0); }
};

struct PropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t propID);          // +0x1c
    virtual void v20(); virtual void v24();
    virtual Property* GetProperty(uint32_t propID);     // +0x28
};

struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual bool GetPropertyList(uint32_t instanceID, PropertyList** ppList);   // +0x30
    virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void GetPropertyListIDs(uint32_t groupID, IdVector& dst);           // +0x48
};

namespace SP {
IPropertyManager* PropertyManager();   // 0x0067de30
bool GetPropertyAsString8(PropertyList* pList, uint32_t propID, eastl::string8& dst);   // 0x006a13b0
bool GetPropertyAsUint32Array(PropertyList* pList, uint32_t propID, uint32_t& count, uint32_t*& pArray);   // 0x006a0840

namespace {
struct cPropertyListNameSort {
    cPropertyListNameSort(uint32_t groupID);   // 0x00d196f0
    uint32_t mData[10];
};
uint32_t GetGameplayMarkerClassId(uint32_t typeHash);   // 0x00d15b30
}
}

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* p) {
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
    T** AsPointer() {
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

// ------------------------------------------------------------------ UTFWin
struct Rectangle { float x1, y1, x2, y2; };

struct IWindow {
    virtual int AddRef();                                         // +0x00
    virtual int Release();                                        // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                          // +0x0c
    virtual IWindow* GetParent();                                 // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual const Rectangle& GetArea();                           // +0x34
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void SetArea(const Rectangle& area);                  // +0x60
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                   // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8();
    virtual void** GetChildrenBegin(void*** pResult);             // +0xcc (sret)
    virtual void** GetChildrenEnd(void*** pResult);               // +0xd0 (sret)
    virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void DisposeWindowFamily(IWindow* pChild);            // +0xe0
};

// Offset from an intrusive-list node to its IWindow (a variable in the original).
extern int g_1440aec;

struct IWinComboBox {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c();
    virtual IWindow* ToWindow();                                  // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void AddItem(const wchar_t* text);                    // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void SetSelection(int index, bool notify);           // +0x44
};

struct IWinScrollbar {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void SetValue(int value, bool notify);               // +0x24
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void SetMaxValue(int value, bool notify);            // +0x34
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    uint32_t mData[3];
};

// ------------------------------------------------------------------ nouns
struct NounEntry {
    uint32_t mUnk0, mUnk4;
    uint32_t mClassID;          // +0x08
    uint32_t mInstanceID;       // +0x0c
    uint32_t mUnk10;
    PropertyList* mpPropList;   // +0x14
    NounEntry* mpNext;          // +0x18
};

struct NounEntryIterator {
    NounEntry* mpNode;
    NounEntry** mpBucket;
    NounEntryIterator(NounEntry** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    NounEntryIterator(NounEntry* pNode, NounEntry** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    NounEntryIterator& operator++() { increment(); return *this; }
    NounEntry* operator->() const { return mpNode; }
    bool operator!=(const NounEntryIterator& x) const { return mpNode != x.mpNode; }
};

struct NounEntryTable {
    uint32_t mUnk0;
    NounEntry** mpBucketArray;   // +0x04
    uint32_t mnBucketCount;      // +0x08
    NounEntryIterator begin() {
        NounEntryIterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    NounEntryIterator end() { return NounEntryIterator(mpBucketArray + mnBucketCount); }
};

struct Noun {
    uint32_t mUnk[3];
    PropertyList* mpPropList;   // +0x0c
};

struct cNounManager {
    uint32_t pad[8];
    NounEntryTable mEntries;   // +0x20
    Noun* GetNoun(uint32_t classID, uint32_t instanceID);   // 0x00b21000
};
namespace SP { cNounManager* NounManager(); }   // 0x00b3d300
const char* GetNounClassName(uint32_t classID);  // 0x00b21490

// ------------------------------------------------------------------ the marker
struct cCommandGameplayMarker {
    uint32_t pad[0x108 / 4];
    uint32_t mType;             // +0x108 (hash of the type name)
    uint32_t mDefClassID;       // +0x10c
    uint32_t mDefInstanceID;    // +0x110
    uint32_t mGroup;            // +0x114
    uint32_t mValueCount;       // +0x118
    uint32_t mValues[32];       // +0x11c
    static int ParseTypeEnum(const char* p);   // 0x00d14600
};

// 0x00d15350
void SetGameplayMarkerDefaultValue(cCommandGameplayMarker* pMarker, uint32_t index, int type, const wchar_t* pDefault);

namespace SP {
class cGameEditInputStrategy {
public:
    void ShowGameplayMarkerProperties(cCommandGameplayMarker* pMarker, bool bReadOnly, bool bSetDefaults);
    void AddLabel(const wchar_t* text, float& x, float& y);                                      // 0x00d15630
    void AddComboBox(uint32_t controlID, float& x, float& y);                                    // 0x00d15780
    void AddTextEdit(uint32_t controlID, int type, uint32_t* pValue, float& x, float& y);       // 0x00d17550

    IWinComboBox* FindComboBox(uint32_t controlID) {
        IWindow* pWindow = mLayout.FindWindowByID(controlID, true);
        return pWindow ? (IWinComboBox*)pWindow->Cast(0x2f5528d9) : 0;
    }

    uint32_t pad[0xa4 / 4];
    IWindow* mGameplayMarkerRoot;              // +0xa4
    IWindow* mGameplayMarkerArea;              // +0xa8
    IWinScrollbar* mGameplayMarkerScrollbar;   // +0xac
    uint32_t pad2[(0xe0 - 0xb0) / 4];
    cSPUILayout mLayout;                       // +0xe0
};

// @ 0x00d1a2b0
void cGameEditInputStrategy::ShowGameplayMarkerProperties(cCommandGameplayMarker* pMarker, bool bReadOnly, bool bSetDefaults)
{
    AutoRefCount<PropertyList> pPropList;
    if (!PropertyManager()->GetPropertyList(id(L"LevelEditor"), pPropList.AsPointer()))
        return;

    // Clear out the previous controls.
    void** it;
    void** itEnd;
    mGameplayMarkerArea->GetChildrenBegin(&it);
    mGameplayMarkerArea->GetChildrenEnd(&itEnd);
    while (it != itEnd) {
        void** pNode = it;
        it = (void**)*pNode;
        mGameplayMarkerArea->DisposeWindowFamily((IWindow*)((char*)pNode + g_1440aec));
    }
    mGameplayMarkerRoot->SetFlag(1, true);

    float x, y;
    y = x = 5.0f;
    {
        AddLabel(L"Type", x, y);
        AutoRefCount<IWinComboBox> pCombo(FindComboBox(0xabc0fff8));
        if (!pCombo) {
            AddComboBox(0xabc0fff8, x, y);
            pCombo = FindComboBox(0xabc0fff8);
            Property* pTypes = pPropList->GetProperty(0x185a7a14);
            uint32_t count = pTypes->GetItemCount();
            int selection = 0;
            eastl::string16* pType = (eastl::string16*)pTypes->GetValue();
            for (uint32_t i = 0; i < count; i++, pType++) {
                pCombo->AddItem(pType->c_str());
                uint32_t hash = id(pType->c_str());
                if (pMarker->mType == 0)
                    pMarker->mType = hash;
                if (hash == pMarker->mType)
                    selection = i;
            }
            pCombo->SetSelection(selection, false);
        }
        pCombo->ToWindow()->SetFlag(2, bReadOnly);
        pCombo->ToWindow()->SetFlag(0x10, !bReadOnly);
        pCombo->ToWindow()->SetFlag(0x1000, !bReadOnly);

        // Definition: every noun of the marker's class.
        x = 5.0f;
        y = 35.0f;
        AddLabel(L"Definition", x, y);
        AddComboBox(0xabc0fff9, x, y);
        uint32_t classID = GetGameplayMarkerClassId(pMarker->mType);
        pCombo = FindComboBox(0xabc0fff9);
        int selection = 0;
        int index = 0;
        NounEntryTable& entries = NounManager()->mEntries;
        for (NounEntryIterator itNoun = entries.begin(); itNoun != entries.end(); ++itNoun) {
            if (itNoun->mClassID == classID) {
                uint32_t instanceID = itNoun->mInstanceID;
                eastl::string16 name;
                if (itNoun->mpPropList && itNoun->mpPropList->HasProperty(0x2e9c159)) {
                    eastl::string8 name8;
                    GetPropertyAsString8(itNoun->mpPropList, 0x2e9c159, name8);
                    name = EA::ConvertToString16(name8);
                }
                if (name.empty()) {
                    eastl::string8 className(GetNounClassName(itNoun->mClassID));
                    name.sprintf(L"%ls 0x%08x", EA::ConvertToString16(className).c_str(), instanceID);
                }
                pCombo->AddItem(name.c_str());
                if (pMarker->mDefClassID == classID && pMarker->mDefInstanceID == instanceID)
                    selection = index;
                index++;
            }
        }
        pCombo->SetSelection(selection, false);

        // Triggers.
        x = 5.0f;
        y = 65.0f;
        Noun* pNoun = NounManager()->GetNoun(pMarker->mDefClassID, pMarker->mDefInstanceID);
        if (pNoun && pNoun->mpPropList) {
            uint32_t triggerCount = 0;
            uint32_t* pTriggers = 0;
            if (GetPropertyAsUint32Array(pNoun->mpPropList, 0x3d03b03, triggerCount, pTriggers)) {
                IdVector ids;
                PropertyManager()->GetPropertyListIDs(0x3cddc79, ids);
                eastl::sort(ids.mpBegin, ids.mpEnd, cPropertyListNameSort(0x3cddc79));
                eastl::string16 label;
                eastl::string16 fileName;
                for (int i = 0; i < (int)triggerCount; i++) {
                    label.sprintf(L"Trigger %d", i);
                    AddLabel(label.c_str(), x, y);
                    uint32_t controlID = i + 0xabc0fff0;
                    AddComboBox(controlID, x, y);
                    pCombo = FindComboBox(controlID);
                    uint32_t current = pTriggers[i];
                    int triggerSel = 0;
                    pCombo->AddItem(L"None");
                    int item = 1;
                    for (uint32_t* pID = ids.mpBegin; pID != ids.mpEnd; pID++) {
                        uint32_t listID = *pID;
                        if (listID != 0x2ea8fb98) {
                            fileName.clear();
                            EA::ResourceMan::GetManager()->GetFileName(
                                EA::ResourceMan::Key(listID, 0xb1b104, 0x3cddc79), fileName);
                            wchar_t buffer[256];
                            EA::IO::SplitPath(fileName.c_str(), 0, 0, buffer, 0, 4);
                            pCombo->AddItem(buffer);
                            if (listID == current)
                                triggerSel = item;
                            item++;
                        }
                    }
                    pCombo->SetSelection(triggerSel, false);
                    x = 5.0f;
                    y += 30.0f;
                    pCombo->ToWindow()->SetFlag(2, false);
                    pCombo->ToWindow()->SetFlag(0x10, true);
                    pCombo->ToWindow()->SetFlag(0x1000, true);
                }
            }
        }

        AddLabel(L"Group", x, y);
        AddTextEdit(0xabc0fffa, 10, &pMarker->mGroup, x, y);
        x = 5.0f;
        y += 30.0f;
    }

    // Per-type parameters: triples of (label, type, default) strings.
    if (pPropList->HasProperty(pMarker->mType)) {
        Property* pParams = pPropList->GetProperty(pMarker->mType);
        uint32_t count = pParams->GetItemCount();
        if (count <= 0x60) {
            pMarker->mValueCount = count / 3;
            eastl::string16* pParam = (eastl::string16*)pParams->GetValue();
            for (uint32_t i = 0; i < count; i += 3, pParam += 3) {
                uint32_t index = i / 3;
                int type = cCommandGameplayMarker::ParseTypeEnum(EA::ConvertToString8(pParam[1]).c_str());
                AddLabel(pParam[0].c_str(), x, y);
                if (bSetDefaults)
                    SetGameplayMarkerDefaultValue(pMarker, index, type, pParam[2].c_str());
                if (type == 1 || type == 9 || type == 10 || type == 13 || !pPropList->HasProperty(type)) {
                    AddTextEdit(index | 0xabc00000, type, &pMarker->mValues[index], x, y);
                } else {
                    AddComboBox(index | 0xabc00000, x, y);
                    AutoRefCount<IWinComboBox> pCombo(FindComboBox(index | 0xabc00000));
                    Property* pChoices = pPropList->GetProperty(type);
                    uint32_t n = pChoices->GetItemCount();
                    eastl::string16* pChoice = (eastl::string16*)pChoices->GetValue();
                    for (; n; n--, pChoice++)
                        pCombo->AddItem(pChoice->c_str());
                    pCombo->SetSelection(pMarker->mValues[index], false);
                }
                x = 5.0f;
                y += 30.0f;
            }
        }
    }

    Rectangle area = mGameplayMarkerArea->GetArea();
    area.y1 = 0.0f;
    area.y2 = y;
    mGameplayMarkerArea->SetArea(area);
    if (mGameplayMarkerScrollbar) {
        RoundToInt(area.y2);
        mGameplayMarkerScrollbar->SetMaxValue(RoundToInt(y), true);
        mGameplayMarkerScrollbar->SetValue(0, true);
    }
}
}  // namespace SP
