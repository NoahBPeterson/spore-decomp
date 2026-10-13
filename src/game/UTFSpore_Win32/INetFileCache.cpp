// src/game/UTFSpore_Win32/INetFileCache.cpp -- migrated from slice(s) s00949cc0, s00948de0, s00947d50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/INetFileCache.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/INetFileCache.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/MemoryStream.h"

// unnamed retail callees and globals (address in the comment)
extern const float kMemStreamOpt2;        // 0x01470F1C
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "EA/Internet/URL.h"

// ---- items of slice s00947d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl memcpy(void*, const void*, unsigned int);
inline void* operator new(unsigned int, void* p) { return p; }
#define kEastlFile "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void __cdecl operator_delete__(void*) throw();   // 0x00f47380
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);   // EASTL form
int __cdecl GetTime64();   // 0x00941bb0
int __cdecl Sprintf16(wchar_t* buf, const wchar_t* fmt, ...);   // 0x009399c0
struct str8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;
    str8() {}
    str8(const str8& o);
    str8(const char* s);
    ~str8() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    void AllocateSelf(unsigned n);       // 0x00475ab0
    void RangeInitialize(const char* pBegin, const char* pEnd);
};
struct wstr16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAlloc;
    wstr16() {}
    wstr16(const wstr16& o);
    ~wstr16() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    void AllocateSelf(unsigned n);       // 0x00429760
    void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd);
    void Assign(const wchar_t* b, const wchar_t* e);   // 0x00423650 (WString_Assign)
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
__forceinline str8::str8(const str8& o) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    RangeInitialize(o.mpBegin, o.mpEnd);
}
__forceinline void str8::RangeInitialize(const char* pBegin, const char* pEnd) {
    AllocateSelf((unsigned)(pEnd - pBegin) + 1);
    char* dst = mpBegin;
    memcpy(dst, pBegin, (unsigned)(pEnd - pBegin));
    mpEnd = dst + (pEnd - pBegin);
    *mpEnd = 0;
}
__forceinline void wstr16::RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
    AllocateSelf((unsigned)(pEnd - pBegin) + 1);
    wchar_t* dst = mpBegin;
    memcpy(dst, pBegin, (unsigned)(pEnd - pBegin) * 2);
    mpEnd = dst + (pEnd - pBegin);
    *mpEnd = 0;
}
__forceinline str8::str8(const char* s) {
    const char* e = s;
    while (*e++)
        ;
    const char* end = s + (e - (s + 1));
    unsigned n = end - s;
    unsigned cap = n + 1;
    char* b;
    char* c;
    if (cap > 1) {
        b = (char*)operator new(cap, "EASTL", 0, 0, kEastlFile, 0xd1);
        c = b + cap;
    } else {
        b = (char*)0x1667bac;
        c = (char*)0x1667bad;
    }
    mpBegin = b;
    mpEnd = b;
    mpCapacity = c;
    memcpy(b, s, n);
    mpEnd = b + (end - s);
    *mpEnd = 0;
}
__forceinline wstr16::wstr16(const wstr16& o) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    const wchar_t* pBegin = o.mpBegin;
    const wchar_t* pEnd = o.mpEnd;
    RangeInitialize(pBegin, pEnd);
}
bool __cdecl StrEqual(const str8* a, const str8* b);   // eastl::operator==<char>
bool __cdecl StrEqualC(const str8* a, const char* b);  // 0x555020 eastl::operator==<char>(const basic_string&, const char*)
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
namespace EA {
namespace IO {
bool __cdecl FileExists(const wchar_t* path);       // 0x931fa0
}
}
namespace EA {
namespace IO {
bool __cdecl DirExists(const wchar_t* path);        // 0x9322b0
}
}
namespace EA {
namespace IO {
bool __cdecl CreateTempFile(wchar_t* out, const wchar_t* dir, const wchar_t* prefix, const wchar_t* ext);  // 0x932580
}
}
namespace EA {
namespace IO {
struct IStreamV {
    virtual void s0();
    virtual int  AddRef();
    virtual int  Release();
};
}
}
namespace EA {
namespace IO {
struct FileStreamObj : IStreamV {
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18();
    virtual bool Open(int, int, int, int);        // slot 19 (+0x4c)
};
}
}
namespace EA {
namespace IO {
struct FileStream_s0094_7d50 : FileStreamObj {
    uint32_t pad[(0x22c - 4) / 4];
    FileStream_s0094_7d50(const wchar_t* path);   // 0x931e10
    ~FileStream_s0094_7d50();                     // 0x931e70
    int  AddRef();                     // 0x9317b0 (non-virtual entry used for stack streams)
    bool Open(int access, int create, int share, int hint);   // 0x9318f0
    bool Write(const void* p, unsigned n);                    // 0x931d30
    unsigned Read(void* p, unsigned n);                       // 0x931ce0
    void Close();                                             // 0x931a70
};
}
}
namespace EA {
namespace IO {
struct IniFile {
    uint32_t pad[0x47c / 4];
    IniFile(const wchar_t* path, int flag);    // 0x935450
    ~IniFile();                                // 0x935040
    void WriteEntry(const wchar_t* section, const wchar_t* key, const wchar_t* value);  // 0x9344b0
};
}
}
struct MemoryStream {
    virtual void s0();
    virtual int  AddRef();           // 1
    virtual int  Release();          // 2
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void SetSize(unsigned);  // 8 (+0x20)
    virtual void s9();
    virtual bool Open(int, int);     // 10 (+0x28)
    uint32_t pad[8];
    MemoryStream(const char* name);  // 0x93bd50
    void SetOption(int opt, float v);     // 0x93bb40
    void* GetData();                      // 0x93ba70
};
extern const float kMemStreamOpt2;        // 0x01470F1C
namespace EA {
namespace Internet {
struct Info_s0094_7d50 {
    str8   msMIMEContentType;       // +0
    wstr16 msCachedFileName;        // +0x10
    MemoryStream* mpMemoryStream;   // +0x20
    unsigned mnDataSize;            // +0x24
    unsigned mnLocation;            // +0x28
    unsigned mnTimeoutSeconds;      // +0x2c
    unsigned mnTimeCreated;         // +0x30
    unsigned mnTimeLastUsed;        // +0x34
    unsigned mnTimeTimeout;         // +0x38

    Info_s0094_7d50(const Info_s0094_7d50& o);            // 0x00948230 (out of line)
    ~Info_s0094_7d50() {}
};
}
}
namespace EA {
namespace Internet {
struct Pair {                       // pair<const string, Info>, 0x4c bytes
    str8 first;
    Info_s0094_7d50 second;
    Pair(const str8& k, const Info_s0094_7d50& v);   // 0x009483a0
    Pair(const Pair& o);                  // 0x00948800
    ~Pair();                              // 0x00948020
};
}
}
namespace EA {
namespace Internet {
struct Node : Pair {                // + next at +0x4c
    Node* mpNext;
    Node(const Pair& p) : Pair(p) {}
};
}
}
namespace EA {
namespace Internet {
struct Iter {
    Node*  mpNode;
    Node** mpBucket;
    Iter() {}
    Iter(Node* n, Node** b) : mpNode(n), mpBucket(b) {}
    Iter(const Iter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
    void IncrementBucket() {
        do {
            ++mpBucket;
        } while (*mpBucket == 0);
        mpNode = *mpBucket;
    }
    void Increment() {
        mpNode = mpNode->mpNext;
        if (mpNode == 0)
            IncrementBucket();
    }
};
}
}
namespace EA {
namespace Internet {
struct InsertResult : Iter {
    bool bInserted;
};
}
}
namespace EA {
namespace Internet {
struct RehashResult {               // pair<bool, unsigned>
    bool bNeedRehash;
    unsigned nNewBuckets;
};
}
}
namespace EA {
namespace Internet {
struct HashTable {                  // object at INetFileCache+0x34
    int     mUnused;
    Node**  mpBucketArray;          // +4
    unsigned mnBucketCount;         // +8
    unsigned mnElementCount;        // +0xc
    struct RehashPolicy {
        char pad[0xc];
        void GetRehash(RehashResult* out, unsigned buckets, unsigned elems, unsigned ins);   // 0x921440
    } mRehashPolicy;                // +0x10
    void DoRehash(unsigned n);                      // 0x947f50
    Iter* Find(Iter* out, const str8* key);         // 0x9486e0
    struct Tag1 { Tag1() {} };
    struct Tag2 { Tag2() {} };
    Iter FindAs(const char* const& key, Tag1, Tag2);   // 0x948300 (find_as<const char*>)
    InsertResult* DoInsert(InsertResult* out, const Pair* v);   // 0x948cb0
};
}
}
namespace EA {
namespace Internet {
struct StreamListNode {
    StreamListNode* next;
    StreamListNode* prev;
    EA::IO::IStreamV* stream;
};
}
}
namespace EA {
namespace Internet {
class INetFileCache_s0094_7d50 {
public:
    bool    mbInitialized;              // +0
    int     mRefCount;                  // +4
    wstr16  msCacheDirectory;           // +8
    wstr16  msIniFileName;              // +0x18
    StreamListNode* mpOpenStreams;      // +0x28
    int     pad2c[2];                   // +0x2c
    HashTable mDataMap;                 // +0x34
    char    pad48[0x58 - 0x34 - sizeof(HashTable)];
    unsigned mnEnabledLocations;        // +0x58

    bool CreateMemoryStream(MemoryStream** out);  // 0x00947d50 (EA::Internet::INetFileCache::CreateMemoryStream)
    bool RemoveCachedFile(const wstr16* name);  // 0x00947de0 (EA::Internet::INetFileCache::RemoveCachedFile)
    bool WriteDataToFile(const wchar_t* name, const void* data, unsigned size);  // 0x00947e30 (EA::Internet::INetFileCache::WriteDataToFile)
    bool ReadDataFromFile(const wchar_t* name, void* buf, unsigned size);  // 0x00947ec0 (EA::Internet::INetFileCache::ReadDataFromFile)
    bool UpdateCacheIniFile();  // 0x00948080 (EA::Internet::INetFileCache::UpdateCacheIniFile)
    Iter* FindOldest(Iter* out, unsigned mask);
    bool SetCacheDirectory(const wchar_t* dir);
    bool SetIniFileName(const wchar_t* name);
    bool CreateNewCachedDataStream(EA::IO::IStreamV** out);  // 0x009484e0 (EA::Internet::INetFileCache::CreateNewCachedDataStream)
    bool GetNewCacheFileName(int a, int b, wstr16* out);  // 0x009485f0 (EA::Internet::INetFileCache::GetNewCacheFileName)
    bool IsEntryValid(const char* key);
    bool MoveEntryToLocation(Info_s0094_7d50* info, unsigned want);
    bool ForceAllDataToLocation(unsigned loc);  // 0x00948aa0 (EA::Internet::INetFileCache::ForceAllDataToLocation)
    bool RemoveUnusedCachedFiles();  // 0x00948b30 (EA::Internet::INetFileCache::RemoveUnusedCachedFiles)
};
}
}
namespace EA {
namespace Internet {
extern const wchar_t kCacheExt[];   // L".cache" @ 0x0143F638
}
}
namespace EA {
namespace Internet {
bool __cdecl MIMEStringToMIMETypes(const char* b, int* a, int* c, unsigned len);   // 0x94a3f0
}
}
namespace EA {
namespace Internet {
bool __cdecl MIMETypesToFileExtension(int a, int b, wchar_t* out, unsigned cap);   // 0x94a1b0
}
}
namespace EA {
namespace Internet {
void __cdecl NormalizeDirectory(wstr16* s);        // 0x931770
}
}
namespace EA {
namespace Internet {
bool __cdecl CreateDirectoryPath(const wchar_t* p);  // 0x932960
}
}
// ---- items of slice s00947d50 end

// ---- items of slice s00948de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString[];   // 0x1667bac (shared empty-string sentinel)
typedef unsigned int uint;
void* __cdecl operator_new(unsigned int, const char*, int, int, const char*, int);   // 0xf473a0 (EASTL allocator)
void* __cdecl operator_new(unsigned int, const char*, int, int, int, int);           // same, 5th arg int
void* __cdecl memcpy_thunk(void* dst, const void* src, unsigned int n);              // 0x11e0744
namespace EA {
namespace IO {
namespace File {
        bool __cdecl Exists(const wchar_t*);                          // 0x931fa0
}
}
}
namespace EA {
namespace IO {
namespace File {
        bool __cdecl Remove(const wchar_t*);                          // 0x931fd0
}
}
}
namespace EA {
namespace IO {
namespace File {
        bool __cdecl Move(const wchar_t*, const wchar_t*, bool);      // 0x931ff0
}
}
}
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
struct Pair_s0094_8de0 {                      // eastl::pair<const string, Info>
    String first;
    Info   second;
    Pair_s0094_8de0(const String& k, const Info& i);   // 0x9483a0 (not defined here)
    Pair_s0094_8de0(const Pair_s0094_8de0& o);                    // 0x948800 (not defined here)
    ~Pair_s0094_8de0();                                // 0x948020 (not defined here)
};
struct Node_s0094_8de0 {                      // hashtable node
    Pair_s0094_8de0  mValue;
    Node_s0094_8de0* mpNext;                  // +0x4c
};
struct Iter_s0094_8de0 {
    Node_s0094_8de0*  mpNode;
    Node_s0094_8de0** mpBucket;
    Iter_s0094_8de0() {}
    Iter_s0094_8de0(Node_s0094_8de0** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    Iter_s0094_8de0(Node_s0094_8de0* pNode, Node_s0094_8de0** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
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
    Node_s0094_8de0*  mpNode;
    Node_s0094_8de0** mpBucket;
    ConstIter(const Iter_s0094_8de0& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
struct IterBool { Iter_s0094_8de0 first; bool second; };
extern Node_s0094_8de0* gEmptyBucketArray_s0094_8de0[];        // 0x154df28
struct RehashPolicy {
    float mfMaxLoadFactor; float mfGrowthFactor; uint mnNextResize;
};
struct Tag {};
struct HT {
    int    mPad;                   // +0 (this+0x34 in INetFileCache)
    Node_s0094_8de0** mpBucketArray;          // +4
    uint   mnBucketCount;          // +8
    uint   mnElementCount;         // +0xc
    RehashPolicy mRehashPolicy;    // +0x10 (max load, growth, next resize)
    int    mAllocator;             // +0x1c
    HT() { mRehashPolicy.mfMaxLoadFactor = 1.0f; mRehashPolicy.mfGrowthFactor = 2.0f; reset(); }
    void reset() { mnBucketCount = 1; mpBucketArray = gEmptyBucketArray_s0094_8de0; mnElementCount = 0; mRehashPolicy.mnNextResize = 0; }

    void  DoFreeNodes(Node_s0094_8de0** pNodeArray, uint nBucketCount);   // 0x948de0
    Iter_s0094_8de0  erase(ConstIter i);                                       // 0x948e80
    Iter_s0094_8de0  find_as(const char* const& key, Tag tagHash, Tag tagEq);   // 0x948300
    Iter_s0094_8de0  find(const String& key);                             // 0x9486e0
    IterBool insert(const Pair_s0094_8de0& value, Tag tag);               // 0x948cb0
    Iter_s0094_8de0 begin() { Iter_s0094_8de0 i(mpBucketArray); if (!i.mpNode) i.increment_bucket(); return i; }
    Iter_s0094_8de0 end()   { return Iter_s0094_8de0(mpBucketArray + mnBucketCount); }
    void clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnElementCount = 0; }
    ~HT() { clear(); if (mnBucketCount > 1) operator_delete__(mpBucketArray); }
};
struct MemBuf {                    // object held in Info::mpMemoryStream when cached in RAM
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual int  Slot7(const char* pName);   // +0x1c
    void* mpData;                            // +4 (after vptr)
};
Pair_s0094_8de0 MakePair(String key, Info info);                              // 0x948780 (by-value args, returns by sret)
String* __cdecl ConvertToString8(String* out, WString* in);   // 0x93c570
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
struct IniFile_s0094_8de0 {
    uint32_t mData[0x11f];
    IniFile_s0094_8de0(const wchar_t* path, int flags);        // 0x935450
    ~IniFile_s0094_8de0();                                     // 0x935040
    void EnumEntries(const wchar_t* section, bool (__cdecl* cb)(const wchar_t*, const wchar_t*, void*), void* user);   // 0x935560
};
namespace EA {
namespace Internet {
class INetFileCache_s0094_8de0 {
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

    INetFileCache_s0094_8de0();
    ~INetFileCache_s0094_8de0();
    void ClearCacheMap();  // 0x00948f00 (EA::Internet::INetFileCache::ClearCacheMap)
    void DoPeriodicCacheMaintenance();  // 0x009492e0 (EA::Internet::INetFileCache::DoPeriodicCacheMaintenance)
    bool RemoveCachedData(const char* pURL);  // 0x00949530 (EA::Internet::INetFileCache::RemoveCachedData)
    bool CommitNewCachedDataStream(IStream* pStream, const char* pURL, uint nLocations, bool bClose,
                                   const char* pMIMEType, uint nTimeoutSeconds);
    bool GetCachedDataStream(const char* pURL, IStream** ppStream, const char** ppMIMEType);  // 0x009498c0 (EA::Internet::INetFileCache::GetCachedDataStream)
    bool ReadCacheIniFile();  // 0x00949b00 (EA::Internet::INetFileCache::ReadCacheIniFile)

    // other-slice members
    void UpdateCacheIniFile();                                  // 0x948080
    void RemoveCachedFile(WString* pFileName);                  // 0x947de0
    void ForceAllDataToLocation(uint nLocation);                // 0x948aa0
    void GetNewCacheFileName(uint a, uint b, WString* pOut);    // 0x9485f0
    void FindOldest(Iter_s0094_8de0* pOut, uint nLocation);                // 0x9481b0
    bool ForceCachedDataToLocation(Info* pInfo, uint nLocations);   // 0x948940
};
}
}
using EA::Internet::INetFileCache_s0094_8de0;
bool __cdecl IniFileCallbackFunction(const wchar_t* pKey, const wchar_t* pValue, void* pCache);
bool __cdecl MIMEStringToMIMETypes(const char* s, uint* pA, uint* pB, int len);   // 0x94a3f0
struct RawMem {                                                      // raw storage, constructed via thiscall ctors
    IStream* MemoryStream_Ctor(void* pData, int size);              // 0x93c270
    IStream* FileStream_Ctor(const wchar_t* path);                  // 0x931e10
};
inline ListNode* FindReverse(ListNode* first, ListNode* last, IStream* value) {
    for (; first != last; first = first->mpPrev)
        if (first->mpPrev->mValue == value)
            break;
    return first;
}
// ---- items of slice s00948de0 end

// ---- items of slice s00949cc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool  __cdecl CreateDirectoryPath(const wchar_t*);
bool  __cdecl Directory_Exists(const wchar_t*);
void  __cdecl GetDriveFreeSpace(wchar_t*);
// ---- items of slice s00949cc0 end

// @ 0x00947d50
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::CreateMemoryStream(MemoryStream** out)
{
    MemoryStream* p = new("UTFInternet/INetFileCache/MemoryStream", 0, 0, 0, 0) MemoryStream("UTFInternet/INetFileCache/MemoryStream");
    if (p) {
        p->AddRef();
        p->SetOption(1, 1.0f);
        p->SetOption(2, kMemStreamOpt2);
        p->Open(0, 0);
        *out = p;
        p->AddRef();
        p->Release();
        return true;
    }
    return false;
}
}}  // namespace EA::Internet



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



// @ 0x00948020
namespace EA { namespace Internet {
Pair::~Pair()
{}
}}  // namespace EA::Internet



// @ 0x00948080
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::UpdateCacheIniFile()
{
    wchar_t iniPath[260];
    wchar_t section[64];
    wchar_t value[2048];
    if (mnEnabledLocations & 2) {
        EA::IO::ConcatenatePathComponents(iniPath, msCacheDirectory.mpBegin, msIniFileName.mpBegin);
        EA::IO::FileRemove(iniPath);
        EA::IO::IniFile ini(iniPath, 1);
        int idx = 0;
        Node** p = mDataMap.mpBucketArray;
        Node* n = *p;
        if (!n) {
            ++p;
            if (*p == 0) {
                do {
                    ++p;
                } while (*p == 0);
            }
            n = *p;
        }
        while (n != mDataMap.mpBucketArray[mDataMap.mnBucketCount]) {
            if (n->second.mnLocation & 2) {
                Sprintf16(section, L"CacheEntry%05d", idx);
                Sprintf16(value, L"%hs,%ls,%hs,%u,%u,%u,%u,%u",
                          n->first.mpBegin, n->second.msCachedFileName.mpBegin,
                          n->second.msMIMEContentType.mpBegin,
                          n->second.mnDataSize, n->second.mnTimeoutSeconds,
                          n->second.mnTimeCreated, n->second.mnTimeLastUsed,
                          n->second.mnTimeTimeout);
                ini.WriteEntry(L"Cache Entries", section, value);
                ++idx;
            }
            n = n->mpNext;
            if (!n) {
                do {
                    n = p[1];
                    ++p;
                } while (!n);
            }
        }
    }
    return true;
}
}}  // namespace EA::Internet



// @ 0x009481b0
namespace EA { namespace Internet {
Iter* INetFileCache_s0094_7d50::FindOldest(Iter* out, unsigned mask)
{
    Node** p = mDataMap.mpBucketArray;
    Node* n = *p;
    if (n == 0) {
        ++p;
        if (*p == 0) {
            do {
                ++p;
            } while (*p == 0);
        }
        n = *p;
    }
    Node* endNode = mDataMap.mpBucketArray[mDataMap.mnBucketCount];
    Node** endBucket = &mDataMap.mpBucketArray[mDataMap.mnBucketCount];
    unsigned oldest = (unsigned)-1;
    out->mpNode = endNode;
    out->mpBucket = endBucket;
    while (n != endNode) {
        if (n->second.mnLocation & mask) {
            unsigned t = n->second.mnTimeLastUsed;
            if (t < oldest) {
                out->mpNode = n;
                out->mpBucket = p;
                oldest = t;
            }
        }
        n = n->mpNext;
        if (!n) {
            do {
                n = p[1];
                ++p;
            } while (!n);
        }
    }
    return out;
}
}}  // namespace EA::Internet



// @ 0x00948230
namespace EA { namespace Internet {
Info_s0094_7d50::Info_s0094_7d50(const Info_s0094_7d50& o)
: msMIMEContentType(o.msMIMEContentType), msCachedFileName(o.msCachedFileName) {
    mpMemoryStream = o.mpMemoryStream;
    mnDataSize = o.mnDataSize;
    mnLocation = o.mnLocation;
    mnTimeoutSeconds = o.mnTimeoutSeconds;
    mnTimeCreated = o.mnTimeCreated;
    mnTimeLastUsed = o.mnTimeLastUsed;
    mnTimeTimeout = o.mnTimeTimeout;
}
}}  // namespace EA::Internet



// @ 0x00948300
namespace EA { namespace Internet {
Iter HashTable::FindAs(const char* const& key, Tag1, Tag2)
{
    const char* k = key;
    unsigned h = 0x811c9dc5;
    const char* cp = k;
    unsigned c = (unsigned char)*cp;
    while (c) {
        h = h * 0x1000193;
        ++cp;
        h ^= c;
        c = (unsigned char)*cp;
    }
    unsigned nb = mnBucketCount;
    Node** buckets = mpBucketArray;
    unsigned n = h % nb;
    Node** bucket = &buckets[n];
    Node* e;
    for (e = *bucket; e; e = e->mpNext) {
        if (StrEqualC((const str8*)e, k))
            break;
    }
    Iter it;
    if (e)
        it = Iter(e, bucket);
    else
        it = Iter(buckets[nb], &buckets[nb]);
    return Iter(it);
}
}}  // namespace EA::Internet



// @ 0x009483a0
namespace EA { namespace Internet {
Pair::Pair(const str8& k, const Info_s0094_7d50& v)
: first(k), second(v) {}
}}  // namespace EA::Internet



// @ 0x00948400
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::SetCacheDirectory(const wchar_t* dir)
{
    bool r = false;
    if (*dir != 0) {
        const wchar_t* e = dir;
        while (*e)
            ++e;
        msCacheDirectory.Assign(dir, dir + (e - dir));
        NormalizeDirectory(&msCacheDirectory);
        if (EA::IO::DirExists(msCacheDirectory.mpBegin))
            return true;
        const wchar_t* cp = msCacheDirectory.mpBegin;
        r = CreateDirectoryPath(cp);
    }
    return r;
}
}}  // namespace EA::Internet



// @ 0x00948460
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::SetIniFileName(const wchar_t* name)
{
    wchar_t buf[260];
    EA::IO::ConcatenatePathComponents(buf, msCacheDirectory.mpBegin, msIniFileName.mpBegin);
    if (EA::IO::FileExists(buf))
        EA::IO::FileRemove(buf);
    const wchar_t* e = name;
    while (*e)
        ++e;
    msIniFileName.Assign(name, name + (e - name));
    return true;
}
}}  // namespace EA::Internet



// @ 0x009484e0
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::CreateNewCachedDataStream(EA::IO::IStreamV** out)
{
    bool ok = false;
    unsigned flags = mnEnabledLocations;
    wchar_t path[260];
    if (flags & 1) {
        ok = CreateMemoryStream((MemoryStream**)out);
    } else if (flags & 2) {
        if (EA::IO::CreateTempFile(path, msCacheDirectory.mpBegin, 0, L".ctmp")) {
            EA::IO::FileStreamObj* fs = new("UTFInternet/INetFileCache/FileStream", 0, 0, 0, 0) EA::IO::FileStream_s0094_7d50(path);
            if (fs) {
                fs->AddRef();
                if (fs->Open(2, 2, 1, 0)) {
                    *out = fs;
                    ok = true;
                }
                fs->Release();
            }
        }
    }
    if (ok) {
        (*out)->AddRef();
        StreamListNode* anchor = (StreamListNode*)mpOpenStreams;
        StreamListNode* node = (StreamListNode*)operator new(0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
        if (&node->stream)
            node->stream = *out;
        node->next = anchor;
        node->prev = anchor->prev;
        anchor->prev->next = node;
        anchor->prev = node;
    }
    return ok;
}
}}  // namespace EA::Internet



// @ 0x009485f0
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::GetNewCacheFileName(int a, int b, wstr16* out)
{
    wchar_t ext[260] = {0};
    wchar_t outPath[260];
    MIMETypesToFileExtension(a, b, ext, 0x104);
    wcscat(ext, kCacheExt);
    bool ok = EA::IO::CreateTempFile(outPath, msCacheDirectory.mpBegin, 0, ext);
    if (ok) {
        unsigned dl = msCacheDirectory.mpEnd - msCacheDirectory.mpBegin;
        const wchar_t* p = outPath + dl;
        const wchar_t* e = p;
        if (*p)
            while (*e)
                ++e;
        out->Assign(p, p + (e - p));
    }
    return ok;
}
}}  // namespace EA::Internet



// @ 0x00948780
namespace EA { namespace Internet {
Pair __cdecl PairConstructByValue(str8 key, Info_s0094_7d50 info)
{
    return Pair(key, info);
}
}}  // namespace EA::Internet



// @ 0x00948800
namespace EA { namespace Internet {
Pair::Pair(const Pair& o)
: first(o.first), second(o.second) {}
}}  // namespace EA::Internet



// @ 0x00948860
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::IsEntryValid(const char* key)
{
    str8 tmp(key);
    Iter it;
    mDataMap.Find(&it, &tmp);
    if (it.mpNode == mDataMap.mpBucketArray[mDataMap.mnBucketCount])
        return false;
    return (unsigned)GetTime64() < it.mpNode->second.mnTimeTimeout;
}
}}  // namespace EA::Internet



// @ 0x00948940
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::MoveEntryToLocation(Info_s0094_7d50* info, unsigned want)
{
    bool ok = false;
    unsigned cur = info->mnLocation;
    if (cur & 3) {
        unsigned add = ~cur & want & 3;
        ok = add == 0;
        if (add & 1) {
            if (info->mpMemoryStream == 0) {
                ok = CreateMemoryStream(&info->mpMemoryStream);
                if (!ok)
                    return ok;
            }
            info->mpMemoryStream->SetSize(info->mnDataSize);
            if (ok) {
                unsigned size = info->mnDataSize;
                const wchar_t* nm = info->msCachedFileName.mpBegin;
                void* buf = info->mpMemoryStream->GetData();
                if (ReadDataFromFile(nm, buf, size))
                    ok = true;
                else
                    ok = false;
            }
        }
        if (add & 2) {
            wstr16* cn = &info->msCachedFileName;
            if (cn->mpBegin == cn->mpEnd) {
                const char* mb = info->msMIMEContentType.mpBegin;
                const char* me = info->msMIMEContentType.mpEnd;
                if (mb != me) {
                    int ta, tb;
                    if (MIMEStringToMIMETypes(mb, &ta, &tb, me - mb))
                        GetNewCacheFileName(ta, tb, cn);
                }
            }
            if (cn->mpBegin == cn->mpEnd)
                GetNewCacheFileName(0, 0, cn);
            unsigned size = info->mnDataSize;
            void* buf = info->mpMemoryStream->GetData();
            ok = WriteDataToFile(cn->mpBegin, buf, size);
        }
        if (ok) {
            unsigned rem = ~want & info->mnLocation & 3;
            if (rem & 1) {
                info->mpMemoryStream->Release();
                info->mpMemoryStream = 0;
            }
            if (rem & 2)
                info->msCachedFileName.clear();
            info->mnLocation = want;
        }
    }
    return ok;
}
}}  // namespace EA::Internet



// @ 0x00948aa0
namespace EA { namespace Internet {
bool INetFileCache_s0094_7d50::ForceAllDataToLocation(unsigned loc)
{
    bool ok = true;
    Node** bk = mDataMap.mpBucketArray;
    Node** p = bk;
    Node* n = *p;
    if (!n) {
        do {
            ++p;
        } while (*p == 0);
        n = *p;
    }
    Node* endNode = bk[mDataMap.mnBucketCount];
    while (n != endNode) {
        bool r = MoveEntryToLocation(&n->second, loc);
        ok = r && ok;
        n = n->mpNext;
        if (!n) {
            do {
                n = p[1];
                ++p;
            } while (!n);
        }
    }
    return ok;
}
}}  // namespace EA::Internet



// @ 0x00948cb0
namespace EA { namespace Internet {
InsertResult* HashTable::DoInsert(InsertResult* out, const Pair* v)
{
    unsigned h = 0x811c9dc5;
    const char* cp = v->first.mpBegin;
    unsigned c = (unsigned char)*cp;
    while (c) {
        h = h * 0x1000193;
        ++cp;
        h ^= c;
        c = (unsigned char)*cp;
    }
    unsigned n = h % mnBucketCount;
    Node** bucket = &mpBucketArray[n];
    Node* e = *bucket;
    for (; e; e = e->mpNext) {
        if (StrEqual((const str8*)v, (const str8*)e))
            break;
    }
    if (e) {
        out->mpNode = e;
        out->mpBucket = bucket;
        out->bInserted = false;
        return out;
    }
    RehashResult rr;
    mRehashPolicy.GetRehash(&rr, mnBucketCount, mnElementCount, 1);
    Node* nn = (Node*)operator new(sizeof(Node), "EASTL", 0, 0, kEastlFile, 0xd1);
    if (nn)
        new (nn) Pair(*v);
    nn->mpNext = 0;
    if (rr.bNeedRehash) {
        n = h % rr.nNewBuckets;
        DoRehash(rr.nNewBuckets);
    }
    nn->mpNext = mpBucketArray[n];
    mpBucketArray[n] = nn;
    ++mnElementCount;
    out->mpNode = nn;
    out->mpBucket = &mpBucketArray[n];
    out->bInserted = true;
    return out;
}
}}  // namespace EA::Internet


// @ 0x00948de0
void HT::DoFreeNodes(Node_s0094_8de0** pNodeArray, uint nBucketCount)
{
    for (uint i = 0; i < nBucketCount; ++i) {
        Node_s0094_8de0* pNode = pNodeArray[i];
        while (pNode) {
            Node_s0094_8de0* const pTempNode = pNode;
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
Iter_s0094_8de0 HT::erase(ConstIter i)
{
    Iter_s0094_8de0 iNext(i.mpNode, i.mpBucket);
    iNext.increment();
    Node_s0094_8de0* pNode = i.mpNode;
    Node_s0094_8de0** pBucket = i.mpBucket;
    Node_s0094_8de0* pCurrent = *pBucket;
    if (pCurrent == pNode)
        *pBucket = pCurrent->mpNext;
    else {
        Node_s0094_8de0* pNext2 = pCurrent->mpNext;
        while (pNext2 != pNode) {
            pCurrent = pNext2;
            pNext2 = pNext2->mpNext;
        }
        pCurrent->mpNext = pNext2->mpNext;
    }
    pNode->mValue.~Pair_s0094_8de0();
    operator_delete__(pNode);
    --mnElementCount;
    return iNext;
}


// @ 0x00948f00
void EA::Internet::INetFileCache_s0094_8de0::ClearCacheMap()
{
    for (Iter_s0094_8de0 it = mDataMap.begin(); it.mpNode != mDataMap.end().mpNode; it.increment()) {
        if (it.mpNode->mValue.second.mpMemoryStream)
            it.mpNode->mValue.second.mpMemoryStream->Release();
    }
    mDataMap.clear();
}


// @ 0x00948f80
bool __cdecl IniFileCallbackFunction(const wchar_t* pKey, const wchar_t* pValue, void* pCacheVoid)
{
    INetFileCache_s0094_8de0* pCache = (INetFileCache_s0094_8de0*)pCacheVoid;
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
                        Pair_s0094_8de0 pr(key, info);
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


// @ 0x009492e0
void EA::Internet::INetFileCache_s0094_8de0::DoPeriodicCacheMaintenance()
{
    uint nFileUsed = 0;
    uint nRAMUsed = 0;
    bool bChanged = false;
    mnCacheAccessCountSinceLastMaintenance = 0;
    if (!mbKeepExpired) {
        uint now = GetTime64();
        Iter_s0094_8de0 it = mDataMap.begin();
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
            Iter_s0094_8de0 it;
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
            Iter_s0094_8de0 it;
            FindOldest(&it, 2);
            if (it.mpNode == mDataMap.end().mpNode)
                break;
            Node_s0094_8de0* pNode = it.mpNode;
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


// @ 0x00949530
bool EA::Internet::INetFileCache_s0094_8de0::RemoveCachedData(const char* pURL)
{
    ++mnCacheAccessCount;
    if (++mnCacheAccessCountSinceLastMaintenance > 0x28)
        DoPeriodicCacheMaintenance();
    const char* pKey = pURL;
    Tag tag = Tag();
    Iter_s0094_8de0 it = mDataMap.find_as(pKey, Tag(), Tag());
    if (it.mpNode != mDataMap.end().mpNode) {
        Node_s0094_8de0* pNode = it.mpNode;
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


// @ 0x00949620
bool EA::Internet::INetFileCache_s0094_8de0::CommitNewCachedDataStream(IStream* pStream, const char* pURL, uint nLocations, bool bClose, const char* pMIMEType, uint nTimeoutSeconds)
{
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
            Pair_s0094_8de0 tmp1 = MakePair(String(pURL), Info());
            Pair_s0094_8de0 tmp2(tmp1);
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
                if (!::MIMEStringToMIMETypes(pInfo->msMIMEContentType.mpBegin, &a, &b,
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


// @ 0x009498c0
bool EA::Internet::INetFileCache_s0094_8de0::GetCachedDataStream(const char* pURL, IStream** ppStream, const char** ppMIMEType)
{
    bool bResult = false;
    Node_s0094_8de0* pNode;
    {
        // the key string is built in place and freed by hand right after the find (the original
        // has no EH frame, so no String object with a destructor is live across the calls)
        struct { char* mpBegin; char* mpEnd; char* mpCapacity; int mAlloc; } sKey;
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
        pNode = mDataMap.find(*(const String*)&sKey).mpNode;
        if (sKey.mpCapacity - sKey.mpBegin > 1 && sKey.mpBegin)
            operator_delete__(sKey.mpBegin);
    }
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


// @ 0x00949b00
bool EA::Internet::INetFileCache::ReadCacheIniFile()
{
    if (mnEnabledLocations & 2) {
        wchar_t path[260];
        EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, msIniFileName.mpBegin);
        if (EA::IO::File::Exists(path)) {
            IniFile_s0094_8de0 ini(path, 1);
            ini.EnumEntries(L"Cache Entries", IniFileCallbackFunction, this);
        }
    }
    return true;
}


// @ 0x00949b80
EA::Internet::INetFileCache_s0094_8de0::INetFileCache_s0094_8de0()
: mbInitialized(false), mRefCount(0) {
    mbKeepExpired = false;
    mnEnabledLocations = 3;
    mnMaxRAMCacheSize = 1000000;
    mnMaxFileCacheSize = 3000000;
    mnDefaultExpirationTimeSeconds = 18000;
    mnCacheAccessCount = 0;
    mnCacheAccessCountSinceLastMaintenance = 0;
}


// @ 0x00949c10
EA::Internet::INetFileCache_s0094_8de0::~INetFileCache_s0094_8de0()
{
    if (mbInitialized) {
        if (mnEnabledLocations & 2) {
            ForceAllDataToLocation(2);
            UpdateCacheIniFile();
        }
        ClearCacheMap();
        mbInitialized = false;
    }
}

// @ 0x00949cc0
bool EA::Internet::INetFileCache::Init()
{
    bool bOk = true;
    if (!mbInitialized) {
        if (msCacheDirectory.length() == 0) {
            wchar_t buf[260];
            GetDriveFreeSpace(buf);
            const wchar_t* e = buf;
            while (*e) ++e;
            unsigned int n = (unsigned int)(e - buf);
            msCacheDirectory.assign(buf, buf + n);
            const wchar_t* lit = L"EA Network Cache\\";
            const wchar_t* le = lit;
            while (*le) ++le;
            unsigned int n2 = (unsigned int)(le - lit);
            msCacheDirectory.append(lit, lit + n2);
        }
        if (!Directory_Exists(msCacheDirectory.c_str()))
            bOk = CreateDirectoryPath(msCacheDirectory.c_str());
        ReadCacheIniFile();
        RemoveUnusedCachedFiles();
        mbInitialized = true;
    }
    return bOk;
}
