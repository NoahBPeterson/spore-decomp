// Slice s00a3af80: 00a3b640.
// eastl::hash_map<unsigned, String8>::operator[](const uint32& key), the same shape as the
// hash_map::operator[] instantiations already matched at 0x5526a0:
//     iterator it = find(key);
//     if (it != end()) return it.mpNode->mValue.second;
//     return insert(value_type(key, T())).first.mpNode->mValue.second;
// The stored value is the 16-byte char eastl string (begin/end/capacity/allocator): its destructor
// compares mpCapacity - mpBegin byte-wise against 1, and its default ctor points at the shared empty
// string gStrEmpty (0x1667bac), which is what the insert path materialises at 0xa3b694.

typedef unsigned int uint32;

extern char gStrEmpty[];   // 0x1667bac (shared empty eastl string)

void* operator new(unsigned int, const char*, int, int, const char*, int);
void operator delete[](void*);   // 0x00f47380

struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int mAlloc;
    String8() {
        mpBegin = gStrEmpty;
        mpEnd = gStrEmpty;
        mpCapacity = gStrEmpty + 1;
    }
    ~String8() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete[](mpBegin); }
    void assign(char* pBegin, char* pEnd);   // 0x00454cb0 (eastl::basic_string::assign)
};

struct StrPair {
    const uint32 first;
    String8 second;
    StrPair(const uint32& key, const String8& value);   // 0x00b209f0
};

// eastl::hashtable node: the value_type pair first, the chain link after it.
struct StrNode {
    StrPair mValue;      // +0x00
    StrNode* mpNext;     // +0x14
};

// eastl::hashtable_iterator_base / hashtable_iterator
struct StrIterBase {
    StrNode* mpNode;
    StrNode** mpBucket;
    StrIterBase(StrNode* pNode, StrNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
struct StrIter : StrIterBase {
    StrIter(StrNode* pNode = 0, StrNode** pBucket = 0) : StrIterBase(pNode, pBucket) {}
    StrIter(StrNode** pBucket) : StrIterBase(*pBucket, pBucket) {}
    StrIter(const StrIter& x) : StrIterBase(x.mpNode, x.mpBucket) {}
};
inline bool operator!=(const StrIterBase& a, const StrIterBase& b) { return a.mpNode != b.mpNode; }
inline bool operator==(const StrIterBase& a, const StrIterBase& b) { return a.mpNode == b.mpNode; }

namespace eastl {
struct true_type {};
template <typename T1, typename T2> struct pair { T1 first; T2 second; };
}

// eastl::prime_rehash_policy
struct RehashPolicy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    unsigned mnNextResize;
};

struct StrHashTable {
    int mFunctors;                // +0x00
    StrNode** mpBucketArray;      // +0x04
    unsigned mnBucketCount;       // +0x08
    unsigned mnElementCount;      // +0x0c
    RehashPolicy mRehashPolicy;   // +0x10
    StrIter find(const uint32& key);                                   // 0x00a3b2c0
    StrIter end() { return StrIter(mpBucketArray + mnBucketCount); }
    eastl::pair<StrIter, bool> DoInsertValue(const StrPair& value,
                                             eastl::true_type);        // 0x00a3b580
    eastl::pair<StrIter, bool> insert(const StrPair& value) {
        return DoInsertValue(value, eastl::true_type());
    }
    // eastl::hash_map<unsigned, String8>::operator[]; named OperatorIndex (not operator[]) so the
    // checker can bind the symbol (MSVC mangles operator[] as ??A, which the marker match rejects).
    String8& OperatorIndex(const uint32& key);
};

// @ 0x00a3b640
String8& StrHashTable::OperatorIndex(const uint32& key) {
    StrIter it = find(key);
    if (it != end())
        return it.mpNode->mValue.second;
    return insert(StrPair(key, String8())).first.mpNode->mValue.second;
}

// ===========================================================================
// s00a3af80 (continued): 0x00a3af80, 0x00a3b3a0, 0x00a3b720, 0x00a3b890,
// 0x00a3b970, 0x00a3b9a0, 0x00a3bb60.
//
// SP::Audio event-modifier primitives (the cEventModifierPrimitive base plus the
// eastl hash_map<unsigned, String8> at +0x18) and the cListener shutdown helper.
// Callees outside the slice are declared with their calling convention only; the
// checker masks the call relocations and matches the call shapes.
// ===========================================================================

void operator delete(void*);       // 0x00f47380

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V  virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
#define V16 V4 V4 V4 V4

extern uint32 g_layoutManager;           // 0x01553a24 (cSPUILayoutManager*)
extern "C" const float _HK_REAL_ONE;     // 0x01485720
extern char gMouthNameA[];               // 0x014537e8
extern char gMouthNameB[];               // 0x014537ec

namespace EA { namespace Audio {

struct ResourceKey;
struct IConfiguration;

struct ResponseCurve {
    unsigned char mData[0x364];           // inline fixed_vector<ResponseCurveData,42>
    bool InitFromConfiguration(IConfiguration* pConfiguration, uint32 nId);  // 0x00a1a9d0
    void SetResponseCurveData(float* pData, int nCount);                      // 0x00a1a590
};

struct Command {
    bool GetUint32(uint32 nKey, uint32* pValue);                             // 0x00a0fab0
};

struct IConfiguration {
    V
    virtual void Release();                                        // slot 1  +0x04
    V
    virtual void GetKeys(void* pKeys, int nFlags);                 // slot 3  +0x0c
    V4 V4 V4
    virtual char* GetDisplayName(uint32 nKey);                     // slot 16 +0x40
};

struct AudioSystem {
    V16 V16 V16 V4 V4 V V V       // slots 0..58
    virtual char* GetNameById(uint32 nId);        // slot 59 +0xec
    V
    V
    V16
    virtual bool GetConfiguration(uint32 nInstance, IConfiguration** ppConfiguration,
                                  uint32 nGroup);                  // slot 78 +0x138
};

AudioSystem* GetSystemAT();                                    // 0x00a206f0

namespace Eapd { namespace Debug {
struct ObjectError {
    V4 V4 V4 V V
    virtual void GetList(void* pOut, void* pParam, int nFlags); // slot 14 +0x38
};
ObjectError* ObjectErrorFunc();                                // 0x008de1a0
}}

}}

namespace SP {
struct IMessageServer {
    V4 V4 V V V
    virtual void Post(void* pPayload, uint32 nKey, int nParam); // slot 11 +0x2c
};
IMessageServer* MessageServer();                                // 0x0067dcc0
}

// eastl red-black-tree node (the key lives at +0x10).
struct RBKeyNode {
    void*  mpLeft;    // +0x00
    void*  mpParent;  // +0x04
    void*  mpRight;   // +0x08
    int    mColor;    // +0x0c
    uint32 mKey;      // +0x10
};
extern RBKeyNode* RBTreeIncrement(RBKeyNode* pNode);   // 0x00921580
extern void DoNukeSubtree(RBKeyNode* pNode);           // 0x009a9600

namespace SP { namespace Audio {

struct cEventModifierPrimitive {
    void*  mpVtable;                             // +0x00
    int    mnRefCount;                           // +0x04
    uint32 mKeyInstance;                         // +0x08
    uint32 mKeyType;                             // +0x0c
    uint32 mKeyGroup;                            // +0x10
    EA::Audio::IConfiguration* mConfiguration;   // +0x14
    bool ReadTuningValues(const EA::Audio::ResourceKey* pKey);    // 0x00a3a610
    void Append(char* pDst, int nCapacity, char* pStr, bool bSep); // 0x00a3a4c0
};

struct cEventModifierPrimitiveFootTypeBase : cEventModifierPrimitive {
    EA::Audio::ResponseCurve mCurves[10];        // +0x18, stride 0x364
    bool ReadTuningValues(const EA::Audio::ResourceKey* pKey);    // 0x00a3af80
};

struct cEventModifierPrimitiveMouthType : cEventModifierPrimitive {
    StrHashTable mTable;                         // +0x18
    void ModifyEvent(EA::Audio::Command* pCmd, uint32 a2, char* pDst, int nCapacity); // 0x00a3b3a0
    void Rebuild(uint32 nInstance, int nMode);   // 0x00a3b720
    bool RebuildAll();                           // 0x00a3b890
    bool RebuildIfCurrent(void* pEntry);         // 0x00a3b970
};

struct cEventModifierPrimitiveSurfaceType : cEventModifierPrimitive {
    void ModifyEvent(EA::Audio::Command* pCmd, uint32 a2, char* pDst, int nCapacity); // 0x00a3b9a0
};

}}

struct cListener {
    uint32 mPad0[2];    // +0x00 (EA::RefCountTemplate<int> then EA::Messaging::IHandler)
    bool Shutdown();    // 0x00a3bb60
};

// @ 0x00a3af80
bool SP::Audio::cEventModifierPrimitiveFootTypeBase::ReadTuningValues(const EA::Audio::ResourceKey* pKey) {
    bool bResult = false;
    if (cEventModifierPrimitive::ReadTuningValues(pKey)) {
        float v[2];
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[0].InitFromConfiguration(mConfiguration, 0x39b853a3u)) mCurves[0].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[1].InitFromConfiguration(mConfiguration, 0x7f30f249u)) mCurves[1].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[2].InitFromConfiguration(mConfiguration, 0x61e3ee74u)) mCurves[2].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[3].InitFromConfiguration(mConfiguration, 0xa1d9e5f7u)) mCurves[3].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[4].InitFromConfiguration(mConfiguration, 0x04db21b5u)) mCurves[4].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[5].InitFromConfiguration(mConfiguration, 0x0a15b885u)) mCurves[5].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = _HK_REAL_ONE;
        if (!mCurves[6].InitFromConfiguration(mConfiguration, 0xd9534bb0u)) mCurves[6].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = 0.0f;
        if (!mCurves[7].InitFromConfiguration(mConfiguration, 0xd7e85196u)) mCurves[7].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = 0.0f;
        if (!mCurves[8].InitFromConfiguration(mConfiguration, 0x917ee1dbu)) mCurves[8].SetResponseCurveData(v, 1);
        v[0] = 0.0f; v[1] = 0.0f;
        if (!mCurves[9].InitFromConfiguration(mConfiguration, 0x6f5b6da8u)) mCurves[9].SetResponseCurveData(v, 1);
        bResult = true;
    }
    return bResult;
}

// @ 0x00a3b3a0
namespace SP { namespace Audio {
void cEventModifierPrimitiveMouthType::ModifyEvent(
        EA::Audio::Command* pCmd, uint32 a2, char* pDst, int nCapacity) {
    EA::Audio::AudioSystem* pSystem = EA::Audio::GetSystemAT();
    uint32 v0;
    if (pCmd->GetUint32(0x39fb001u, &v0) && v0 != 0) {
        StrIter it = mTable.find(v0);
        if (it != mTable.end())
            Append(pDst, nCapacity, it.mpNode->mValue.second.mpBegin, true);
        return;
    }
    uint32 u;
    pCmd->GetUint32(0x39f9e01u, &u);
    if (u == 0) return;
    uint32 w = 0;
    pCmd->GetUint32(0x39f9e08u, &w);
    char* pName;
    uint32 sel;
    if (u == 1) {
        sel = 0x156573c3u;
        if (w >= 5) sel = 0x0b65639du;
    } else if (w < 5) {
        pName = pSystem->GetNameById(u);
        goto have_name;
    } else if (w == 5) {
        {
            StrIter it = mTable.find(u);
            if (it == mTable.end()) return;
            pName = it.mpNode->mValue.second.mpBegin;
        }
        goto have_name;
    } else {
        sel = 0x0b65639du;
    }
    {
        StrIter it = mTable.find(sel);
        if (it == mTable.end()) return;
        pName = it.mpNode->mValue.second.mpBegin;
    }
have_name:
    if (pName == 0) return;
    Append(pDst, nCapacity, pName, false);
    Append(pDst, nCapacity, (w < 5) ? gMouthNameA : gMouthNameB, false);
    uint32 b = 1;
    if (pCmd->GetUint32(0x44d63a2u, &b) && b == 0) pDst[0] = 'b';
    uint32 e = 0;
    if (pCmd->GetUint32(0x48def6du, &e) && e != 0) pDst[0] = 'e';
}
}}

// @ 0x00a3b720
namespace SP { namespace Audio {
void cEventModifierPrimitiveMouthType::Rebuild(uint32 nInstance, int nMode) {
    EA::Audio::IConfiguration* pConfiguration = 0;
    EA::Audio::AudioSystem* pSystem = EA::Audio::GetSystemAT();
    pSystem->GetConfiguration(nInstance, &pConfiguration, g_layoutManager);
    if (pConfiguration) {
        RBKeyNode* pNode = 0;
        RBKeyNode* pNodeEnd = 0;
        pConfiguration->GetKeys(&pNode, 1);
        while (pNode != pNodeEnd) {
            uint32 nKey = pNode->mKey;
            char* pName = pConfiguration->GetDisplayName(nKey);
            if (pName) {
                char* pEnd = pName;
                while (*pEnd) ++pEnd;
                mTable.OperatorIndex(nKey).assign(pName, pEnd);
            }
            pNode = RBTreeIncrement(pNode);
        }
        if (pNodeEnd) {
            DoNukeSubtree(pNodeEnd);
            operator delete[](pNodeEnd);
        }
    }
    if (pConfiguration) pConfiguration->Release();
}
}}

// @ 0x00a3b890
namespace SP { namespace Audio {
bool cEventModifierPrimitiveMouthType::RebuildAll() {
    struct Entry { uint32 mId; uint32 mPad[2]; };          // stride 0xc
    struct Vec { Entry* mpBegin; Entry* mpEnd; Entry* mpCapacity; };
    struct Param { void* mpUnknown; uint32 mGroup; };
    Vec vec = { 0, 0, 0 };
    Param param = { (void*)0x01402ee0, g_layoutManager };
    EA::Audio::Eapd::Debug::ObjectError* pError = EA::Audio::Eapd::Debug::ObjectErrorFunc();
    pError->GetList(&vec, &param, 0);
    for (Entry* p = vec.mpBegin; p != vec.mpEnd; ++p)
        Rebuild(p->mId, 1);
    if (vec.mpBegin && *((int*)vec.mpBegin - 1) != 0)
        operator delete[](vec.mpBegin);
    return true;
}
}}

// @ 0x00a3b970
namespace SP { namespace Audio {
bool cEventModifierPrimitiveMouthType::RebuildIfCurrent(void* pEntry) {
    uint32* p = (uint32*)pEntry;
    if (p[2] == g_layoutManager) {
        Rebuild(p[0], 0);
        return true;
    }
    return false;
}
}}

// @ 0x00a3b9a0
namespace SP { namespace Audio {
void cEventModifierPrimitiveSurfaceType::ModifyEvent(
        EA::Audio::Command* pCmd, uint32 a2, char* pDst, int nCapacity) {
    uint32 v = 0;
    if (!pCmd->GetUint32(0x39fa376u, &v)) return;
    switch (v) {
    case 1u:           Append(pDst, nCapacity, (char*)"_wade", false);   return;
    case 2u:           Append(pDst, nCapacity, (char*)"_splash", false); return;
    case 3u:           Append(pDst, nCapacity, (char*)"_grass", false);  return;
    case 4u:           Append(pDst, nCapacity, (char*)"_ice", false);    return;
    case 5u:           Append(pDst, nCapacity, (char*)"_lava", false);   return;
    case 0x2fe99727u:  Append(pDst, nCapacity, (char*)"_sand", false);   return;
    case 0x7aab588au:  Append(pDst, nCapacity, (char*)"_wood", false);   return;
    case 0x7fd0653au:  Append(pDst, nCapacity, (char*)"_rock", false);   return;
    case 0x920790dfu:  Append(pDst, nCapacity, (char*)"_glass", false);  return;
    case 0x9375c65eu:  Append(pDst, nCapacity, (char*)"_metal", false);  return;
    default:           Append(pDst, nCapacity, (char*)"_dirt", false);   return;
    }
}
}}

// @ 0x00a3bb60
bool cListener::Shutdown() {
    SP::IMessageServer* pServer = SP::MessageServer();
    if (pServer) {
        pServer->Post(this ? (char*)this + 8 : 0, 0x2b0c259u, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x22d1adcu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x248975fu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x2489766u, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x248976au, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x52d9babu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x539a4ceu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x539a4cfu, -9999);
    }
    return true;
}