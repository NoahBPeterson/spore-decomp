// Slice s00948de0 - EA::Internet::INetFileCache (hashtable of cached entries, ini reader, cache maintenance).
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------
void  __cdecl operator_delete__(void*) throw();
void* __cdecl operator_new(unsigned int, const char*, int, int, const char*, int);   // 0xf473a0 (EASTL allocator)
void* __cdecl operator_new(unsigned int, const char*, int, int, int, int);           // same, 5th arg int
void* __cdecl memcpy_thunk(void* dst, const void* src, unsigned int n);              // 0x11e0744
uint  __cdecl GetTime64();                                                           // 0x941bb0

namespace EA { namespace IO {
    wchar_t* __cdecl ConcatenatePathComponents(wchar_t* out, const wchar_t* dir, const wchar_t* file);  // 0x92fe60
    namespace File {
        bool __cdecl Exists(const wchar_t*);                          // 0x931fa0
        bool __cdecl Remove(const wchar_t*);                          // 0x931fd0
        bool __cdecl Move(const wchar_t*, const wchar_t*, bool);      // 0x931ff0
    }
} }

// ---------------------------------------------------------------------------
// minimal EASTL strings (16 bytes each, empty-string sentinel pointers)
// ---------------------------------------------------------------------------
extern char gEmptyString[];   // 0x1667bac (shared empty-string sentinel)
struct String  { char*    mpBegin; char*    mpEnd; char*    mpCapacity; int mAlloc;
    String(const char* p) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; RangeInitialize(p); }
    void RangeInitialize(const char* p);   // 0x57cc10
    struct NoInit {};
    String(NoInit) {}
    String(const String& o); // (string copy ctor, not defined here)
    void assign(const char* b, const char* e);   // 0x454cb0
    String() { mpBegin = gEmptyString; mpEnd = gEmptyString; mpCapacity = gEmptyString + 1; }
    ~String() { if (mpCapacity - mpBegin > 1 && mpBegin) operator_delete__(mpBegin); }
};
struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAlloc;
    WString(const wchar_t* pSrc) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; RangeInitialize(pSrc); }
    WString() { mpBegin = (wchar_t*)gEmptyString; mpEnd = (wchar_t*)gEmptyString; mpCapacity = (wchar_t*)gEmptyString + 1; }
    ~WString() { if (mpCapacity - mpBegin > 1 && mpBegin) operator_delete__(mpBegin); }
    void RangeInitialize(const wchar_t* pBegin);       // 0x579a90 (thiscall, null-terminated source)
    void Assign(const wchar_t* b, const wchar_t* e);   // 0x423650
    void Erase(uint pos, uint n);                      // 0x4228e0
};

void String_sprintf(String* s, const char* fmt, ...);                              // 0x472fe0

inline void FreeStr(String& s)   { if (s.mpCapacity - s.mpBegin > 1 && s.mpBegin) operator_delete__(s.mpBegin); }
inline void FreeWStr(WString& s) { if (s.mpCapacity - s.mpBegin > 1 && s.mpBegin) operator_delete__(s.mpBegin); }

// ---------------------------------------------------------------------------
// Stream interface (EA::IO::IStream-like); slot index = vtable offset / 4
// ---------------------------------------------------------------------------
struct IStream {
    virtual void v0();
    virtual int  AddRef();                      // +4
    virtual int  Release();                     // +8
    virtual int  GetType();                     // +0xc
    virtual void v4();
    virtual void v5();
    virtual int  v6();                          // +0x18
    virtual int  GetSize();                     // +0x1c
    virtual void v8();
    virtual void v9();
    virtual bool Close(int, int);               // +0x28
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void SetPath(const wchar_t*);       // +0x3c
    virtual void v16();
    virtual int  GetPath(wchar_t*, int);        // +0x44
    virtual void v18();
    virtual bool Open(int, int, int, int);      // +0x4c
};

// ---------------------------------------------------------------------------
// INetFileCache data types
// ---------------------------------------------------------------------------
struct Info {
    String   msMIMEContentType;    // +0x00
    WString  msCachedFileName;     // +0x10
    IStream* mpMemoryStream;       // +0x20
    uint     mnDataSize;           // +0x24
    uint     mnLocation;           // +0x28
    uint     mnTimeoutSeconds;     // +0x2c
    uint     mnTimeCreated;        // +0x30
    uint     mnTimeLastUsed;       // +0x34
    uint     mnTimeTimeout;        // +0x38
    Info() {}
    Info(const Info& o);          // 0x948230 (not defined here)
};

struct Pair {                      // eastl::pair<const string, Info>
    String first;
    Info   second;
    Pair(const String& k, const Info& i);   // 0x9483a0 (not defined here)
    Pair(const Pair& o);                    // 0x948800 (not defined here)
    ~Pair();                                // 0x948020 (not defined here)
};

struct Node {                      // hashtable node
    Pair  mValue;
    Node* mpNext;                  // +0x4c
};

struct Iter {
    Node*  mpNode;
    Node** mpBucket;
    Iter() {}
    Iter(Node** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    Iter(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (!mpNode)
            mpNode = *++mpBucket;
    }
    void increment_bucket() {
        ++mpBucket;
        while (!*mpBucket)
            ++mpBucket;
        mpNode = *mpBucket;
    }
};
struct ConstIter {
    Node*  mpNode;
    Node** mpBucket;
    ConstIter(const Iter& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
struct IterBool { Iter first; bool second; };

extern Node* gEmptyBucketArray[];        // 0x154df28

struct RehashPolicy {
    float mfMaxLoadFactor; float mfGrowthFactor; uint mnNextResize;
};

struct Tag {};

struct HT {
    int    mPad;                   // +0 (this+0x34 in INetFileCache)
    Node** mpBucketArray;          // +4
    uint   mnBucketCount;          // +8
    uint   mnElementCount;         // +0xc
    RehashPolicy mRehashPolicy;    // +0x10 (max load, growth, next resize)
    int    mAllocator;             // +0x1c
    HT() { mRehashPolicy.mfMaxLoadFactor = 1.0f; mRehashPolicy.mfGrowthFactor = 2.0f; reset(); }
    void reset() { mnBucketCount = 1; mpBucketArray = gEmptyBucketArray; mnElementCount = 0; mRehashPolicy.mnNextResize = 0; }

    void  DoFreeNodes(Node** pNodeArray, uint nBucketCount);   // 0x948de0
    Iter  erase(ConstIter i);                                       // 0x948e80
    Iter  find_as(const char* const& key, Tag tagHash, Tag tagEq);   // 0x948300
    Iter  find(const String& key);                             // 0x9486e0
    IterBool insert(const Pair& value, Tag tag);               // 0x948cb0
    Iter begin() { Iter i(mpBucketArray); if (!i.mpNode) i.increment_bucket(); return i; }
    Iter end()   { return Iter(mpBucketArray + mnBucketCount); }
    void clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnElementCount = 0; }
    ~HT() { clear(); if (mnBucketCount > 1) operator_delete__(mpBucketArray); }
};

struct MemBuf {                    // object held in Info::mpMemoryStream when cached in RAM
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual int  Slot7(const char* pName);   // +0x1c
    void* mpData;                            // +4 (after vptr)
};
Pair MakePair(String key, Info info);                              // 0x948780 (by-value args, returns by sret)
String* __cdecl ConvertToString8(String* out, WString* in);   // 0x93c570

// ---------------------------------------------------------------------------
// hashtable members
// ---------------------------------------------------------------------------

// @ 0x00948de0  hashtable::DoFreeNodes
void HT::DoFreeNodes(Node** pNodeArray, uint nBucketCount) {
    for (uint i = 0; i < nBucketCount; ++i) {
        Node* pNode = pNodeArray[i];
        while (pNode) {
            Node* const pTempNode = pNode;
            pNode = pNode->mpNext;
            FreeWStr(pTempNode->mValue.second.msCachedFileName);
            FreeStr(pTempNode->mValue.second.msMIMEContentType);
            FreeStr(pTempNode->mValue.first);
            operator_delete__(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}

// @ 0x00948e80  hashtable::erase(const_iterator)
Iter HT::erase(ConstIter i) {
    Iter iNext(i.mpNode, i.mpBucket);
    iNext.increment();
    Node* pNode = i.mpNode;
    Node** pBucket = i.mpBucket;
    Node* pCurrent = *pBucket;
    if (pCurrent == pNode)
        *pBucket = pCurrent->mpNext;
    else {
        Node* pNext2 = pCurrent->mpNext;
        while (pNext2 != pNode) {
            pCurrent = pNext2;
            pNext2 = pNext2->mpNext;
        }
        pCurrent->mpNext = pNext2->mpNext;
    }
    pNode->mValue.~Pair();
    operator_delete__(pNode);
    --mnElementCount;
    return iNext;
}

// ---------------------------------------------------------------------------
// INetFileCache (retail layout: stream list at +0x28, hash table at +0x34)
// ---------------------------------------------------------------------------
struct ListNode { ListNode* mpNext; ListNode* mpPrev; IStream* mValue; };
struct ListAnchor {
    ListNode* mpNext; ListNode* mpPrev;
    ListAnchor() { mpNext = (ListNode*)this; mpPrev = (ListNode*)this; }
    ~ListAnchor() {
        ListNode* pNode = mpNext;
        while (pNode != (ListNode*)this) {
            ListNode* pCurrent = pNode;
            pNode = pNode->mpNext;
            operator_delete__(pCurrent);
        }
    }
};

struct IniFile {
    uint32_t mData[0x11f];
    IniFile(const wchar_t* path, int flags);        // 0x935450
    ~IniFile();                                     // 0x935040
    void EnumEntries(const wchar_t* section, bool (__cdecl* cb)(const wchar_t*, const wchar_t*, void*), void* user);   // 0x935560
};

namespace EA { namespace Internet {

class INetFileCache {
public:
    bool     mbInitialized;                 // +0x00
    int      mRefCount;                     // +0x04
    WString  msCacheDirectory;              // +0x08
    WString  msIniFileName;                 // +0x18
    ListAnchor mStreamList;                 // +0x28 (anchor: next, prev)
    uint32_t mPad30;                        // +0x30
    HT       mDataMap;                      // +0x34
    bool     mbKeepExpired;                 // +0x54
    uint     mnEnabledLocations;            // +0x58
    uint     mnMaxRAMCacheSize;             // +0x5c
    uint     mnMaxFileCacheSize;            // +0x60
    uint     mnDefaultExpirationTimeSeconds;// +0x64
    uint     mnCacheAccessCount;            // +0x68
    uint     mnCacheAccessCountSinceLastMaintenance;   // +0x6c

    INetFileCache();
    ~INetFileCache();
    void ClearCacheMap();
    void DoPeriodicCacheMaintenance();
    bool RemoveCachedData(const char* pURL);
    bool CommitNewCachedDataStream(IStream* pStream, const char* pURL, uint nLocations, bool bClose,
                                   const char* pMIMEType, uint nTimeoutSeconds);
    bool GetCachedDataStream(const char* pURL, IStream** ppStream, const char** ppMIMEType);
    bool ReadCacheIniFile();

    // other-slice members
    void UpdateCacheIniFile();                                  // 0x948080
    void RemoveCachedFile(WString* pFileName);                  // 0x947de0
    void ForceAllDataToLocation(uint nLocation);                // 0x948aa0
    void GetNewCacheFileName(uint a, uint b, WString* pOut);    // 0x9485f0
    void FindOldest(Iter* pOut, uint nLocation);                // 0x9481b0
    bool ForceCachedDataToLocation(Info* pInfo, uint nLocations);   // 0x948940
};

} }

using EA::Internet::INetFileCache;

bool __cdecl IniFileCallbackFunction(const wchar_t* pKey, const wchar_t* pValue, void* pCache);

bool __cdecl MIMEStringToMIMETypes(const char* s, uint* pA, uint* pB, int len);   // 0x94a3f0
struct MemoryStream;
struct RawMem {                                                      // raw storage, constructed via thiscall ctors
    IStream* MemoryStream_Ctor(void* pData, int size);              // 0x93c270
    IStream* FileStream_Ctor(const wchar_t* path);                  // 0x931e10
};

// @ 0x00948f00  INetFileCache::ClearCacheMap
void INetFileCache::ClearCacheMap() {
    for (Iter it = mDataMap.begin(); it.mpNode != mDataMap.end().mpNode; it.increment()) {
        if (it.mpNode->mValue.second.mpMemoryStream)
            it.mpNode->mValue.second.mpMemoryStream->Release();
    }
    mDataMap.clear();
}

// @ 0x00948f80  IniFile "Cache Entries" enumeration callback (INetFileCache::IniFileCallbackFunction)
// value = "url,filename,mime,size,timeout,created,lastUsed,timeTimeout"
bool __cdecl IniFileCallbackFunction(const wchar_t* pKey, const wchar_t* pValue, void* pCacheVoid) {
    INetFileCache* pCache = (INetFileCache*)pCacheVoid;
    if (*pValue) {
        WString sLine(pValue);
        uint32_t fRaw[32];
        WString* f = (WString*)fRaw;
        for (int k = 7; k >= 0; --k) {
            f[k].mpBegin = (wchar_t*)gEmptyString;
            f[k].mpEnd = (wchar_t*)gEmptyString;
            f[k].mpCapacity = (wchar_t*)gEmptyString + 1;
        }
        uint nField = 7;
        for (int i = (int)(sLine.mpEnd - sLine.mpBegin) - 1; i >= 0; --i) {
            if (nField == 0)
                break;
            if (sLine.mpBegin[i] == L',') {
                uint n = (uint)(sLine.mpEnd - sLine.mpBegin) - i;
                f[nField].Assign(&sLine.mpBegin[i + 1], &sLine.mpBegin[i + 1] + n - 1);
                sLine.Erase(i, n);
                --nField;
            }
        }
        if (nField == 0) {
            Info info;
            f[0].Assign(sLine.mpBegin, sLine.mpEnd);
            String_sprintf(&info.msMIMEContentType, "%ls", f[2].mpBegin);
            info.msCachedFileName.Assign(f[1].mpBegin, f[1].mpEnd);
            info.mpMemoryStream = 0;
            info.mnDataSize = wcstoul(f[3].mpBegin, 0, 10);
            info.mnLocation = 2;
            info.mnTimeoutSeconds = wcstoul(f[4].mpBegin, 0, 10);
            info.mnTimeCreated = wcstoul(f[5].mpBegin, 0, 10);
            info.mnTimeLastUsed = wcstoul(f[6].mpBegin, 0, 10);
            info.mnTimeTimeout = wcstoul(f[7].mpBegin, 0, 10);
            if (info.mnDataSize <= 0x3d0900) {
                uint now = GetTime64();
                if (info.mnTimeCreated > now) info.mnTimeCreated = now;
                if (info.mnTimeLastUsed > now) info.mnTimeLastUsed = now;
                if (info.mnTimeTimeout > now) {
                    wchar_t path[260];
                    EA::IO::ConcatenatePathComponents(path, pCache->msCacheDirectory.mpBegin, info.msCachedFileName.mpBegin);
                    if (EA::IO::File::Exists(path)) {
                        String key;
                        ConvertToString8(&key, &f[0]);
                        Pair pr(key, info);
                        pCache->mDataMap.insert(pr, Tag());
                    }
                } else
                    pCache->RemoveCachedFile(&info.msCachedFileName);
            } else {
                if (info.msCachedFileName.mpEnd - info.msCachedFileName.mpBegin) {
                    wchar_t path[260];
                    EA::IO::ConcatenatePathComponents(path, pCache->msCacheDirectory.mpBegin, info.msCachedFileName.mpBegin);
                    EA::IO::File::Remove(path);
                }
            }
        }
        for (int k = 7; k >= 0; --k)
            FreeWStr(f[k]);
    }
    return true;
}

// @ 0x009492e0  INetFileCache::DoPeriodicCacheMaintenance
void INetFileCache::DoPeriodicCacheMaintenance() {
    uint nFileUsed = 0;
    uint nRAMUsed = 0;
    bool bChanged = false;
    mnCacheAccessCountSinceLastMaintenance = 0;
    if (!mbKeepExpired) {
        uint now = GetTime64();
        Iter it = mDataMap.begin();
        while (it.mpNode != mDataMap.end().mpNode) {
            Info& info = it.mpNode->mValue.second;
            if (now >= info.mnTimeTimeout) {
                if ((info.mnLocation & 1) && info.mpMemoryStream)
                    info.mpMemoryStream->Release();
                if (info.mnLocation & 2) {
                    if (info.msCachedFileName.mpEnd - info.msCachedFileName.mpBegin) {
                        wchar_t path[260];
                        EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, info.msCachedFileName.mpBegin);
                        EA::IO::File::Remove(path);
                    }
                    bChanged = true;
                }
                it = mDataMap.erase(it);
            } else {
                if (info.mnLocation & 1) nRAMUsed += info.mnDataSize;
                if (info.mnLocation & 2) nFileUsed += info.mnDataSize;
                it.increment();
            }
        }
    }
    if ((mnEnabledLocations & 1) && nRAMUsed > mnMaxRAMCacheSize) {
        do {
            Iter it;
            FindOldest(&it, 1);
            if (it.mpNode == mDataMap.end().mpNode)
                break;
            Info& info = it.mpNode->mValue.second;
            ForceCachedDataToLocation(&info, mnEnabledLocations & 2);
            bChanged = true;
            if (info.mnLocation & 2)
                nFileUsed += info.mnDataSize;
            else
                mDataMap.erase(it);
            nRAMUsed -= info.mnDataSize;
        } while (nRAMUsed > mnMaxRAMCacheSize);
    }
    if ((mnEnabledLocations & 2) && nFileUsed > mnMaxFileCacheSize) {
        do {
            Iter it;
            FindOldest(&it, 2);
            if (it.mpNode == mDataMap.end().mpNode)
                break;
            Node* pNode = it.mpNode;
            if (pNode->mValue.second.msCachedFileName.mpEnd - pNode->mValue.second.msCachedFileName.mpBegin) {
                wchar_t path[260];
                EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, pNode->mValue.second.msCachedFileName.mpBegin);
                EA::IO::File::Remove(path);
            }
            nFileUsed -= pNode->mValue.second.mnDataSize;
            bChanged = true;
            mDataMap.erase(it);
        } while (nFileUsed > mnMaxFileCacheSize);
    }
    if (bChanged)
        UpdateCacheIniFile();
}

// @ 0x00949530  INetFileCache::RemoveCachedData
bool INetFileCache::RemoveCachedData(const char* pURL) {
    ++mnCacheAccessCount;
    if (++mnCacheAccessCountSinceLastMaintenance > 0x28)
        DoPeriodicCacheMaintenance();
    const char* pKey = pURL;
    Tag tag = Tag();
    Iter it = mDataMap.find_as(pKey, Tag(), Tag());
    if (it.mpNode != mDataMap.end().mpNode) {
        Node* pNode = it.mpNode;
        if (pNode->mValue.second.mpMemoryStream) {
            pNode->mValue.second.mpMemoryStream->Release();
            pNode->mValue.second.mpMemoryStream = 0;
        }
        {
            WString sName(pNode->mValue.second.msCachedFileName.mpBegin);
            RemoveCachedFile(&sName);
        }
        mDataMap.erase(it);
        return true;
    }
    return false;
}

inline ListNode* FindReverse(ListNode* first, ListNode* last, IStream* value) {
    for (; first != last; first = first->mpPrev)
        if (first->mpPrev->mValue == value)
            break;
    return first;
}

// @ 0x00949620  INetFileCache::CommitNewCachedDataStream
bool INetFileCache::CommitNewCachedDataStream(IStream* pStream, const char* pURL, uint nLocations, bool bClose,
                                              const char* pMIMEType, uint nTimeoutSeconds) {
    bool bResult = false;
    ListNode* pFirst = (ListNode*)&mStreamList;
    ListNode* pLast = mStreamList.mpNext;
    pFirst = FindReverse(pFirst, pLast, pStream);
    if (pFirst != pLast) {
        ListNode* pNode = pFirst->mpPrev->mpNext->mpPrev;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        operator_delete__(pNode);
    }
    RemoveCachedData(pURL);
    if (nLocations) {
        Info* pInfo;
        {
            Pair tmp1 = MakePair(String(pURL), Info());
            Pair tmp2(tmp1);
            IterBool ib = mDataMap.insert(tmp2, Tag());
            pInfo = &ib.first.mpNode->mValue.second;
        }
        pInfo->mnTimeoutSeconds = (nTimeoutSeconds == 0xffffffffu) ? mnDefaultExpirationTimeSeconds : nTimeoutSeconds;
        uint now = GetTime64();
        pInfo->mnTimeTimeout = pInfo->mnTimeoutSeconds + now;
        pInfo->mnTimeCreated = now;
        pInfo->mnTimeLastUsed = now;
        pInfo->msMIMEContentType.assign(pMIMEType, pMIMEType + strlen(pMIMEType));
        pInfo->mnDataSize = pStream->GetSize();
        pInfo->mnLocation = (pStream->GetType() == 0x34722300) ? 2 : 1;
        pInfo->mpMemoryStream = 0;
        if (pInfo->mnLocation & 2) {
            pStream->v6();
            wchar_t path[260];
            uint n = pStream->GetPath(path, 260);
            path[n] = 0;
            if (n > 0) {
                uint a, b;
                if (!MIMEStringToMIMETypes(pInfo->msMIMEContentType.mpBegin, &a, &b,
                                           pInfo->msMIMEContentType.mpEnd - pInfo->msMIMEContentType.mpBegin)) {
                    a = 0;
                    b = 0;
                }
                GetNewCacheFileName(a, b, &pInfo->msCachedFileName);
                if (pInfo->msCachedFileName.mpEnd - pInfo->msCachedFileName.mpBegin) {
                    if (EA::IO::File::Move(path, pInfo->msCachedFileName.mpBegin, true)) {
                        pStream->SetPath(pInfo->msCachedFileName.mpBegin);
                        bResult = true;
                        if (bClose)
                            bResult = pStream->Open(1, 6, 1, 0);
                    }
                }
            }
        } else {
            pInfo->mpMemoryStream = pStream;
            bResult = true;
        }
        if (ForceCachedDataToLocation(pInfo, nLocations) && bResult)
            bResult = true;
        else
            bResult = false;
    } else
        bResult = true;
    if (bClose)
        pStream->Close(0, 0);
    if (++mnCacheAccessCountSinceLastMaintenance > 0x28)
        DoPeriodicCacheMaintenance();
    return bResult;
}

// @ 0x009498c0  INetFileCache::GetCachedDataStream
bool INetFileCache::GetCachedDataStream(const char* pURL, IStream** ppStream, const char** ppMIMEType) {
    bool bResult = false;
    String sKey((String::NoInit()));
    {
        uint n = (uint)strlen(pURL);
        const char* pEnd = pURL + n;
        uint nCap = n + 1;
        char* p;
        char* pCapEnd;
        if (nCap > 1) {
            p = (char*)operator_new(nCap, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            pCapEnd = p + nCap;
        } else {
            p = gEmptyString;
            pCapEnd = gEmptyString + 1;
        }
        sKey.mpBegin = p;
        sKey.mpCapacity = pCapEnd;
        memcpy_thunk(p, pURL, n);
        sKey.mpEnd = p + (pEnd - pURL);
        *sKey.mpEnd = 0;
    }
    Iter it = mDataMap.find(sKey);
    sKey.~String();
    Node* pNode = it.mpNode;
    if (pNode != mDataMap.end().mpNode) {
        pNode->mValue.second.mnTimeLastUsed = GetTime64();
        if ((pNode->mValue.second.mnLocation & 1) && pNode->mValue.second.mpMemoryStream) {
            void* pMem = operator_new(0x24, "UTFInternet/INetFileCache/MemoryStream", 0, 0, 0, 0);
            if (pMem) {
                MemBuf* pSrc = (MemBuf*)pNode->mValue.second.mpMemoryStream;
                void* pData = pSrc->mpData;
                IStream* pNew = ((RawMem*)pMem)->MemoryStream_Ctor(pData, pSrc->Slot7("UTFInternet/INetFileCache/MemoryStream"));
                if (pNew) {
                    pNew->AddRef();
                    pNew->AddRef();
                    pNew->Close(0, 0);
                    *ppStream = pNew;
                    pNew->Release();
                    bResult = true;
                }
            }
        } else if (pNode->mValue.second.mnLocation & 2) {
            if (pNode->mValue.second.msCachedFileName.mpBegin != pNode->mValue.second.msCachedFileName.mpEnd) {
                wchar_t path[260];
                EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, pNode->mValue.second.msCachedFileName.mpBegin);
                void* pMem = operator_new(0x22c, "UTFInternet/INetFileCache/FileStream", 0, 0, 0, 0);
                if (pMem) {
                    IStream* pFile = ((RawMem*)pMem)->FileStream_Ctor(path);
                    if (pFile) {
                        pFile->AddRef();
                        if (pFile->Open(1, 6, 1, 0)) {
                            pFile->AddRef();
                            *ppStream = pFile;
                            bResult = true;
                        }
                        pFile->Release();
                    }
                }
            }
        }
        if (bResult && ppMIMEType)
            *ppMIMEType = pNode->mValue.second.msMIMEContentType.mpBegin;
    }
    if (++mnCacheAccessCountSinceLastMaintenance > 0x28)
        DoPeriodicCacheMaintenance();
    return bResult;
}

// @ 0x00949b00  INetFileCache::ReadCacheIniFile
bool INetFileCache::ReadCacheIniFile() {
    if (mnEnabledLocations & 2) {
        wchar_t path[260];
        EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, msIniFileName.mpBegin);
        if (EA::IO::File::Exists(path)) {
            IniFile ini(path, 1);
            ini.EnumEntries(L"Cache Entries", IniFileCallbackFunction, this);
        }
    }
    return true;
}


// @ 0x00949b80  INetFileCache::INetFileCache
INetFileCache::INetFileCache() : mbInitialized(false), mRefCount(0) {
    mbKeepExpired = false;
    mnEnabledLocations = 3;
    mnMaxRAMCacheSize = 1000000;
    mnMaxFileCacheSize = 3000000;
    mnDefaultExpirationTimeSeconds = 18000;
    mnCacheAccessCount = 0;
    mnCacheAccessCountSinceLastMaintenance = 0;
}

// @ 0x00949c10  INetFileCache::~INetFileCache
INetFileCache::~INetFileCache() {
    if (mbInitialized) {
        if (mnEnabledLocations & 2) {
            ForceAllDataToLocation(2);
            UpdateCacheIniFile();
        }
        ClearCacheMap();
        mbInitialized = false;
    }
}
