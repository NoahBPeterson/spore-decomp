// src/game/UTFSpore_Win32/INetFileCache.cpp -- migrated from slice(s) s00948de0, s00947d50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/INetFileCache.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/INetFileCache.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/MemoryStream.h"
#include <stdlib.h>
#include <string.h>

// ---- items of slice s00947d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace IO {
bool __cdecl ConcatenatePathComponents(wchar_t* out, const wchar_t* dir, const wchar_t* name);  // 0x92fe60
}
}
namespace EA {
namespace IO {
bool __cdecl FileRemove(const wchar_t* path);       // 0x931fd0
}
}
// ---- items of slice s00947d50 end

// ---- items of slice s00948de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString[];   // 0x1667bac (shared empty-string sentinel)
typedef unsigned int uint;
void  __cdecl operator_delete__(void*) throw();
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
inline void FreeStr(String& s)   { if (s.mpCapacity - s.mpBegin > 1 && s.mpBegin) operator_delete__(s.mpBegin); }
inline void FreeWStr(WString& s) { if (s.mpCapacity - s.mpBegin > 1 && s.mpBegin) operator_delete__(s.mpBegin); }
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
// ---- items of slice s00948de0 end

// @ 0x00947de0
bool EA::Internet::INetFileCache::RemoveCachedFile(eastl::basic_string<wchar_t, eastl::allocator> const & name)
{
    wchar_t buf[260];
    if (name.mpEnd - name.mpBegin != 0) {
        EA::IO::ConcatenatePathComponents(buf, msCacheDirectory.mpBegin, name.mpBegin);
        return EA::IO::FileRemove(buf);
    }
    return false;
}



// @ 0x00947e30
bool EA::Internet::INetFileCache::WriteDataToFile(wchar_t const * name, unsigned char * data, unsigned int size)
{
    wchar_t path[260];
    bool ok = false;
    EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, name);
    EA::IO::FileStream fs(path);
    fs.AddRef();
    if (fs.Open(2, 4, 1, 0)) {
        ok = fs.Write(data, size);
        fs.Close();
    }
    return ok;
}



// @ 0x00947ec0
bool EA::Internet::INetFileCache::ReadDataFromFile(wchar_t const * name, unsigned char * buf, unsigned int size)
{
    wchar_t path[260];
    bool ok = false;
    EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, name);
    EA::IO::FileStream fs(path);
    fs.AddRef();
    if (fs.Open(1, 6, 1, 0)) {
        ok = fs.Read(buf, size) == size;
        fs.Close();
    }
    return ok;
}


// @ 0x00948de0
void HT::DoFreeNodes(Node** pNodeArray, uint nBucketCount)
{
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

// @ 0x00948e80
Iter HT::erase(ConstIter i)
{
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
