// Slice s005ea3d0: cSPUILayoutManager::cWorld-style container helpers (EASTL-heavy).
// Module flags: /O2 /MD /Gy /TP (the original was not built with /EHsc).
#include "types.h"

extern "C" void FreeMem(void* p);                                          // 0x00f47380
extern "C" void* __cdecl MemCpy(void* dst, const void* src, uint32_t n);    // 0x011e0744
extern "C" int __cdecl WStringCompare(const wchar_t* b1, const wchar_t* e1,
                                      const wchar_t* b2, const wchar_t* e2);  // 0x005e9260

// ---------------------------------------------------------------- EASTL pieces
struct WString {                                     // eastl::basic_string<wchar_t>, 0x10 bytes
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mFlags;
    WString() {}
    ~WString() {
        if ((int32_t)(((uint32_t)mpCapacity - (uint32_t)mpBegin) & 0xfffffffeu) > 2 && mpBegin)
            FreeMem(mpBegin);
    }
};

template <class T>
struct Vector {                                      // eastl::vector<T, sp_vector_allocator>, 0x14 bytes
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[2];
    Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
    ~Vector() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            FreeMem(mpBegin);
    }
};

struct WStringPair {                                 // eastl::pair<const basic_string<wchar_t>, int>
    WString first;                                   // +0x00
    int32_t second;                                  // +0x10
    WStringPair* Construct(const WString& key, const uint32_t& id);   // 0x008d6580
};
struct TrueType { };                                 // eastl::true_type, empty
struct LessWString { bool operator()(const WString& a, const WString& b) const; };
struct NodeBase {
    NodeBase* mpNodeRight;                           // +0x00
    NodeBase* mpNodeLeft;                            // +0x04
    NodeBase* mpNodeParent;                          // +0x08
    uint8_t  mColor;                                 // +0x0c
};
struct WStringMapNode : NodeBase {
    WStringPair mValue;                              // +0x10
};
struct WStringMapIterator {
    WStringMapNode* mpNode;
    WStringMapIterator() {}
    WStringMapIterator(WStringMapNode* p) : mpNode(p) {}
    WStringMapIterator(const WStringMapIterator& x) : mpNode(x.mpNode) {}
    WStringPair* operator->() const { return &mpNode->mValue; }
    bool operator!=(const WStringMapIterator& x) const { return mpNode != x.mpNode; }
    bool operator==(const WStringMapIterator& x) const { return mpNode == x.mpNode; }
};
class WStringMap {                                   // eastl::map<basic_string<wchar_t>, int>, 0x1c bytes
public:
    LessWString mCompare;                            // +0x00
    NodeBase mAnchor;                                // +0x04
    uint32_t mnSize;                                 // +0x14
    WStringMapIterator end() { return WStringMapIterator((WStringMapNode*)&mAnchor); }
    WStringMapIterator lower_bound(const WString& key);                                      // 0x005e97e0
    WStringMapIterator DoInsertValue(WStringMapIterator position, const WStringPair& value,
                                     TrueType inserted);                                     // 0x005ea0d0
    WStringMapIterator insert(WStringMapIterator position, const WStringPair& value) {
        return DoInsertValue(position, value, TrueType());
    }
    int32_t* FindOrInsert(const WString& key);
};

// ---------------------------------------------------------------- 005ea8f0
struct Vec8470W {                                    // eastl::vector<uint16_t>
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    uint32_t mAlloc[2];
    Vec8470W() {}
    void Construct(uint32_t count, const uint32_t* alloc);   // 0x005e92c0
};
struct Vec8470I {                                    // eastl::vector<uint32_t>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[2];
    Vec8470I() {}
    void Construct(uint32_t count, const uint32_t* alloc);   // 0x004aa350
};
struct Pair8470 {
    Vec8470W mWords;                                 // +0x00
    Vec8470I mIds;                                   // +0x14
    Pair8470(const Pair8470& src);
};

// @ 0x005ea8f0
Pair8470::Pair8470(const Pair8470& src) {
    Vec8470I* ids = &mIds;
    int32_t byteDiff;
    mWords.Construct((uint32_t)(src.mWords.mpEnd - src.mWords.mpBegin), src.mWords.mAlloc);
    byteDiff = (int32_t)((const uint8_t*)src.mWords.mpEnd -
                         (const uint8_t*)src.mWords.mpBegin);
    mWords.mpEnd = (uint16_t*)MemCpy(mWords.mpBegin, src.mWords.mpBegin, (uint32_t)byteDiff)
                   + (byteDiff >> 1);
    ids->Construct((uint32_t)(src.mIds.mpEnd - src.mIds.mpBegin), src.mIds.mAlloc);
    byteDiff = (int32_t)((const uint8_t*)src.mIds.mpEnd -
                         (const uint8_t*)src.mIds.mpBegin);
    ids->mpEnd = (uint32_t*)MemCpy(ids->mpBegin, src.mIds.mpBegin, (uint32_t)byteDiff)
                 + (byteDiff >> 2);
}

// ---------------------------------------------------------------- 005eae50
// @ 0x005eae50
int32_t* WStringMap::FindOrInsert(const WString& key) {
    WStringMapIterator it = lower_bound(key);
    if (it == end() ||
        WStringCompare(key.mpBegin, key.mpEnd, it->first.mpBegin, it->first.mpEnd) < 0)
        it = insert(it, *WStringPair().Construct(key, 0));
    return &it->second;
}

// ---------------------------------------------------------------- big object
// 0x40c-byte container: 8 wstring vectors, 7 arrays of 3 wstring vectors,
// 8 {field,5,10,map} groups, scalars/bools and four more maps/vectors.
extern "C" void* __cdecl CopyWStrings(const WString* first, const WString* last,
                                      WString* dst);                        // 0x0084ab40

struct EmptyAllocator {};
struct UILayoutNode : NodeBase {
    WString mKey;                                    // +0x10
    uint32_t mValue;                                 // +0x20
};

class UILayoutMap {                                  // eastl::map, 0x1c bytes
public:
    LessWString mCompare;                            // +0x00
    NodeBase mAnchor;                                // +0x04
    uint32_t mnSize;                                 // +0x14
    EmptyAllocator mAllocator;                       // +0x18
    UILayoutMap() : mAnchor(), mnSize(0) { reset(); }
    ~UILayoutMap() { DoNuke((UILayoutNode*)mAnchor.mpNodeParent); }
    void reset() {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear() {
        DoNuke((UILayoutNode*)mAnchor.mpNodeParent);
        reset();
    }
    void DoNuke(UILayoutNode* pNode);                // 0x005e9fb0
};

class WStringVector {                                // eastl::vector<wstring>, 0x14 bytes
public:
    WString* mpBegin;                                // +0x00
    WString* mpEnd;                                  // +0x04
    WString* mpCapacity;                             // +0x08
    uint32_t mAlloc[2];                              // +0x0c
    WStringVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~WStringVector() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            FreeMem(mpBegin);
    }
    void DoDestroyValues(WString* first, WString* last);   // 0x0084aad0
    WString* erase(WString* first, WString* last) {
        if (first != last) {
            WString* p = (WString*)CopyWStrings(last, last, first);
            DoDestroyValues(p, last);
            mpEnd -= last - first;
        }
        return first;
    }
    void clear() {
        WString* first = mpBegin;
        WString* last = mpEnd;
        WString* p = (WString*)CopyWStrings(last, last, first);
        DoDestroyValues(p, mpEnd);
        mpEnd -= last - first;
    }
};

// Same storage, but the element-destruction loop is inlined (member arrays).
__forceinline void DestroyWStrings(WString* first, WString* last) {
    for (; first < last; ++first)
        first->~WString();
}
class WStringVectorInline {
public:
    WString* mpBegin;
    WString* mpEnd;
    WString* mpCapacity;
    uint32_t mAlloc[2];
    WStringVectorInline() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~WStringVectorInline() {
        DestroyWStrings(mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            FreeMem(mpBegin);
    }
};

struct UILayoutGroup {                               // 0x28 bytes, unused base
    uint32_t mField;                                 // +0x00
    int32_t  mFive;                                  // +0x04
    int32_t  mTen;                                   // +0x08
    UILayoutMap mMap;                                // +0x0c
};
struct UILayoutGroupFirst {                          // +0x00 left uninitialised
    uint32_t mField;
    int32_t  mFive;
    int32_t  mTen;
    UILayoutMap mMap;
    UILayoutGroupFirst() : mFive(5), mTen(10) {}
};
struct UILayoutGroupZeroed {                         // +0x00 zeroed
    uint32_t mField;
    int32_t  mFive;
    int32_t  mTen;
    UILayoutMap mMap;
    UILayoutGroupZeroed() : mField(0), mFive(5), mTen(10) {}
};
struct ZeroedWord {
    uint32_t mValue;
    ZeroedWord() : mValue(0) {}
};
struct GroupFieldBase {
    uint32_t mField;
    GroupFieldBase() : mField(0) {}
};
struct UILayoutGroupZeroedLate {                     // same layout
    volatile uint32_t mField;
    volatile int32_t  mFive;
    volatile int32_t  mTen;
    UILayoutMap mMap;
    UILayoutGroupZeroedLate() : mField(0), mFive(5), mTen(10) {}
};

class UILayoutData {
public:
    WStringVector mV0;                               // +0x000
    WStringVector mV1;                               // +0x014
    WStringVector mV2;                               // +0x028
    WStringVector mV3;                               // +0x03c
    WStringVector mV4;                               // +0x050
    WStringVector mV5;                               // +0x064
    WStringVector mV6;                               // +0x078
    WStringVector mV7;                               // +0x08c
    WStringVectorInline mArr0[3];                    // +0x0a0
    WStringVectorInline mArr1[3];                    // +0x0dc
    WStringVectorInline mArr2[3];                    // +0x118
    WStringVectorInline mArr3[3];                    // +0x154
    WStringVectorInline mArr4[3];                    // +0x190
    WStringVectorInline mArr5[3];                    // +0x1cc
    WStringVectorInline mArr6[3];                    // +0x208
    UILayoutGroupFirst  mGroup0;                     // +0x244
    UILayoutGroupZeroed mGroup1;                     // +0x26c
    UILayoutGroupZeroed mGroup2;                     // +0x294
    UILayoutGroupZeroed mGroup3;                     // +0x2bc
    UILayoutGroupZeroed mGroup4;                     // +0x2e4
    UILayoutGroupZeroed mGroup5;                     // +0x30c
    UILayoutGroupZeroedLate mGroup6;                 // +0x334
    UILayoutGroupZeroedLate mGroup7;                 // +0x35c
    uint32_t mScalar;                                // +0x384
    UILayoutMap mMap388;                             // +0x388
    WStringVector mV3a4;                             // +0x3a4
    bool mFlag0;                                     // +0x3b8
    bool mFlag1;                                     // +0x3b9
    bool mFlag2;                                     // +0x3ba
    bool mFlag3;                                     // +0x3bb
    bool mFlag4;                                     // +0x3bc
    bool mFlag5;                                     // +0x3bd
    bool mFlag6;                                     // +0x3be
    bool mFlag7;                                     // +0x3bf
    UILayoutMap mMap3c0;                             // +0x3c0
    UILayoutMap mMap3dc;                             // +0x3dc
    WStringVector mV3f8;                             // +0x3f8
    UILayoutData();
    ~UILayoutData();
    void Clear();
};

// @ 0x005ea3d0
UILayoutData::~UILayoutData() {}

// @ 0x005ea970
UILayoutData::UILayoutData()
    : mFlag0(false), mFlag1(false), mFlag2(false), mFlag3(false),
      mFlag4(false), mFlag5(false), mFlag6(false), mFlag7(false), mScalar(0) {}

// @ 0x005eaef0
void UILayoutData::Clear() {
    mV0.clear();
    mV1.clear();
    mV2.clear();
    mV3.clear();
    mV4.clear();
    mV5.clear();
    mMap388.clear();
    mV3a4.clear();
    mMap3c0.clear();
    mGroup0.mMap.clear();
    mGroup1.mMap.clear();
    mGroup2.mMap.clear();
    mGroup3.mMap.clear();
    mGroup4.mMap.clear();
    mGroup5.mMap.clear();
}
