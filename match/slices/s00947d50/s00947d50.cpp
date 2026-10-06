// Slice s00947d50 -- EA::Internet::INetFileCache (UTFInternet): cache file I/O, entry migration,
// hashtable<string, pair<const string, Info>> instances.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc)
#include "types.h"
#include <wchar.h>
#include <string.h>

extern "C" {
__declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
}
void* __cdecl memcpy(void*, const void*, unsigned int);
inline void* operator new(unsigned int, void* p) { return p; }
static const char kEastlFile[] = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\allocator.h";
void* __cdecl memset(void*, int, unsigned int);
void __cdecl operator_delete__(void*) throw();
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);   // EASTL form
int __cdecl GetTime64();
int __cdecl Sprintf16(wchar_t* buf, const wchar_t* fmt, ...);

// ---------------------------------------------------------------------------
// Minimal EASTL-shaped strings (16 bytes incl. allocator)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// IO stubs
// ---------------------------------------------------------------------------
namespace EA { namespace IO {
bool __cdecl ConcatenatePathComponents(wchar_t* out, const wchar_t* dir, const wchar_t* name);  // 0x92fe60
bool __cdecl FileRemove(const wchar_t* path);       // 0x931fd0
bool __cdecl FileExists(const wchar_t* path);       // 0x931fa0
bool __cdecl DirExists(const wchar_t* path);        // 0x9322b0
bool __cdecl CreateTempFile(wchar_t* out, const wchar_t* dir, const wchar_t* prefix, const wchar_t* ext);  // 0x932580

struct IStreamV {
    virtual void s0();
    virtual int  AddRef();
    virtual int  Release();
};
struct FileStreamObj : IStreamV {
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18();
    virtual bool Open(int, int, int, int);        // slot 19 (+0x4c)
};

struct FileStream : FileStreamObj {
    uint32_t pad[(0x22c - 4) / 4];
    FileStream(const wchar_t* path);   // 0x931e10
    ~FileStream();                     // 0x931e70
    int  AddRef();                     // 0x9317b0 (non-virtual entry used for stack streams)
    bool Open(int access, int create, int share, int hint);   // 0x9318f0
    bool Write(const void* p, unsigned n);                    // 0x931d30
    unsigned Read(void* p, unsigned n);                       // 0x931ce0
    void Close();                                             // 0x931a70
};

struct IniFile {
    uint32_t pad[0x47c / 4];
    IniFile(const wchar_t* path, int flag);    // 0x935450
    ~IniFile();                                // 0x935040
    void WriteEntry(const wchar_t* section, const wchar_t* key, const wchar_t* value);  // 0x9344b0
};

}} // namespace EA::IO

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

// ---------------------------------------------------------------------------
// INetFileCache data
// ---------------------------------------------------------------------------
namespace EA { namespace Internet {

struct Info {
    str8   msMIMEContentType;       // +0
    wstr16 msCachedFileName;        // +0x10
    MemoryStream* mpMemoryStream;   // +0x20
    unsigned mnDataSize;            // +0x24
    unsigned mnLocation;            // +0x28
    unsigned mnTimeoutSeconds;      // +0x2c
    unsigned mnTimeCreated;         // +0x30
    unsigned mnTimeLastUsed;        // +0x34
    unsigned mnTimeTimeout;         // +0x38

    Info(const Info& o);            // 0x00948230 (out of line)
    ~Info() {}
};

struct Pair {                       // pair<const string, Info>, 0x4c bytes
    str8 first;
    Info second;
    Pair(const str8& k, const Info& v);   // 0x009483a0
    Pair(const Pair& o);                  // 0x00948800
    ~Pair();                              // 0x00948020
};

struct Node : Pair {                // + next at +0x4c
    Node* mpNext;
    Node(const Pair& p) : Pair(p) {}
};

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
struct InsertResult : Iter {
    bool bInserted;
};

struct RehashResult {               // pair<bool, unsigned>
    bool bNeedRehash;
    unsigned nNewBuckets;
};

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
    Iter FindAs(const str8& key, Tag1, Tag2);   // 0x948300 (find_as<const char*>)
    InsertResult* DoInsert(InsertResult* out, const Pair* v);   // 0x948cb0
};

struct StreamListNode {
    StreamListNode* next;
    StreamListNode* prev;
    EA::IO::IStreamV* stream;
};

class INetFileCache {
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

    bool CreateMemoryStream(MemoryStream** out);
    bool RemoveCachedFile(const wstr16* name);
    bool WriteDataToFile(const wchar_t* name, const void* data, unsigned size);
    bool ReadDataFromFile(const wchar_t* name, void* buf, unsigned size);
    bool UpdateCacheIniFile();
    Iter* FindOldest(Iter* out, unsigned mask);
    bool SetCacheDirectory(const wchar_t* dir);
    bool SetIniFileName(const wchar_t* name);
    bool CreateNewCachedDataStream(EA::IO::IStreamV** out);
    bool GetNewCacheFileName(int a, int b, wstr16* out);
    bool IsEntryValid(const char* key);
    bool MoveEntryToLocation(Info* info, unsigned want);
    bool ForceAllDataToLocation(unsigned loc);
    bool RemoveUnusedCachedFiles();
};

extern const wchar_t kCacheExt[];   // L".cache" @ 0x0143F638
bool __cdecl MIMEStringToMIMETypes(const char* b, int* a, int* c, unsigned len);   // 0x94a3f0
bool __cdecl MIMETypesToFileExtension(int a, int b, wchar_t* out, unsigned cap);   // 0x94a1b0
void __cdecl NormalizeDirectory(wstr16* s);        // 0x931770
bool __cdecl CreateDirectoryPath(const wchar_t* p);  // 0x932960

// @ 0x00947d50
bool INetFileCache::CreateMemoryStream(MemoryStream** out) {
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

// @ 0x00947de0
bool INetFileCache::RemoveCachedFile(const wstr16* name) {
    wchar_t buf[260];
    if (name->mpEnd - name->mpBegin != 0) {
        EA::IO::ConcatenatePathComponents(buf, msCacheDirectory.mpBegin, name->mpBegin);
        return EA::IO::FileRemove(buf);
    }
    return false;
}

// @ 0x00947e30
bool INetFileCache::WriteDataToFile(const wchar_t* name, const void* data, unsigned size) {
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
bool INetFileCache::ReadDataFromFile(const wchar_t* name, void* buf, unsigned size) {
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
Pair::~Pair() {}

// @ 0x00948230
Info::Info(const Info& o) : msMIMEContentType(o.msMIMEContentType), msCachedFileName(o.msCachedFileName) {
    mpMemoryStream = o.mpMemoryStream;
    mnDataSize = o.mnDataSize;
    mnLocation = o.mnLocation;
    mnTimeoutSeconds = o.mnTimeoutSeconds;
    mnTimeCreated = o.mnTimeCreated;
    mnTimeLastUsed = o.mnTimeLastUsed;
    mnTimeTimeout = o.mnTimeTimeout;
}

// @ 0x009483a0
Pair::Pair(const str8& k, const Info& v) : first(k), second(v) {}

// @ 0x00948800
Pair::Pair(const Pair& o) : first(o.first), second(o.second) {}

// @ 0x00948780
Pair __cdecl PairConstructByValue(str8 key, Info info) {
    return Pair(key, info);
}

// @ 0x009481b0
Iter* INetFileCache::FindOldest(Iter* out, unsigned mask) {
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

// @ 0x00948300
Iter HashTable::FindAs(const str8& key, Tag1, Tag2) {
    unsigned h = 0x811c9dc5;
    const char* cp = key.mpBegin;
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
        if (StrEqual((const str8*)e, &key))
            break;
    }
    Iter result(mpBucketArray[mnBucketCount], &mpBucketArray[mnBucketCount]);
    if (e) {
        result.mpNode = e;
        result.mpBucket = bucket;
    }
    return result;
}

// @ 0x00948400
bool INetFileCache::SetCacheDirectory(const wchar_t* dir) {
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

// @ 0x00948460
bool INetFileCache::SetIniFileName(const wchar_t* name) {
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

// @ 0x009484e0
bool INetFileCache::CreateNewCachedDataStream(EA::IO::IStreamV** out) {
    bool ok = false;
    unsigned flags = mnEnabledLocations;
    wchar_t path[260];
    if (flags & 1) {
        ok = CreateMemoryStream((MemoryStream**)out);
    } else if (flags & 2) {
        if (EA::IO::CreateTempFile(path, msCacheDirectory.mpBegin, 0, L".ctmp")) {
            EA::IO::FileStreamObj* fs = new("UTFInternet/INetFileCache/FileStream", 0, 0, 0, 0) EA::IO::FileStream(path);
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

// @ 0x009485f0
bool INetFileCache::GetNewCacheFileName(int a, int b, wstr16* out) {
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

// @ 0x00948860
bool INetFileCache::IsEntryValid(const char* key) {
    str8 tmp(key);
    Iter it;
    mDataMap.Find(&it, &tmp);
    if (it.mpNode == mDataMap.mpBucketArray[mDataMap.mnBucketCount])
        return false;
    return (unsigned)GetTime64() < it.mpNode->second.mnTimeTimeout;
}

// @ 0x00948940
bool INetFileCache::MoveEntryToLocation(Info* info, unsigned want) {
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

// @ 0x00948aa0
bool INetFileCache::ForceAllDataToLocation(unsigned loc) {
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

// @ 0x00948cb0
InsertResult* HashTable::DoInsert(InsertResult* out, const Pair* v) {
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

// @ 0x00948080
bool INetFileCache::UpdateCacheIniFile() {
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

// ---------------------------------------------------------------------------
// RemoveUnusedCachedFiles: delete "*.cache" files in the cache directory that no entry refers to
// ---------------------------------------------------------------------------
struct DirEntry {
    int      pad0;
    wchar_t* nameBegin;     // +4
    wchar_t* nameEnd;       // +8
    char     pad[0x30 - 0xc];
};

struct DequeIt {
    DirEntry*  mpCurrent;       // +0
    DirEntry*  mpBegin;         // +4
    DirEntry*  mpEnd;           // +8
    DirEntry** mpCurrentArrayPtr;   // +0xc
};

struct DirEntryDeque {          // 0x30 bytes
    DirEntry** mpPtrArray;      // +0
    unsigned   mnPtrArraySize;  // +4
    DequeIt    mItBegin;        // +8
    DequeIt    mItEnd;          // +0x18
    void*      mpAllocator;     // +0x28
    int        pad2c;
    void DoInit(unsigned n);    // eastl::DequeBase::DoInit
    ~DirEntryDeque();           // 0x5f96c0
};

struct DirFinder {
    int a, b, c, d;
    int Find(const wchar_t* dir, DirEntryDeque* out, const wchar_t* pattern, int flags, int maxSize, int zero);   // 0x92ef40
};

void* __cdecl GetDefaultAllocator();   // EA::Allocator::ICoreAllocator::GetDefaultAllocator

// @ 0x00948b30
bool INetFileCache::RemoveUnusedCachedFiles() {
    wchar_t path[260];
    DirFinder finder;
    finder.a = finder.b = finder.c = finder.d = 0;
    DirEntryDeque files;
    files.mpPtrArray = 0;
    files.mnPtrArraySize = 0;
    files.mItBegin.mpCurrent = 0; files.mItBegin.mpBegin = 0; files.mItBegin.mpEnd = 0; files.mItBegin.mpCurrentArrayPtr = 0;
    files.mItEnd.mpCurrent = 0; files.mItEnd.mpBegin = 0; files.mItEnd.mpEnd = 0; files.mItEnd.mpCurrentArrayPtr = 0;
    files.mpAllocator = GetDefaultAllocator();
    files.pad2c = 0;
    files.DoInit(0);
    if (finder.Find(msCacheDirectory.mpBegin, &files, L"*.cache", 2, 0x100000, 0)) {
        DirEntry* cur = files.mItBegin.mpCurrent;
        DirEntry* chunkEnd = files.mItBegin.mpEnd;
        DirEntry** arr = files.mItBegin.mpCurrentArrayPtr;
        while (cur != files.mItEnd.mpCurrent) {
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
            while (n != mDataMap.mpBucketArray[mDataMap.mnBucketCount]) {
                if (_wcsicmp(n->second.msCachedFileName.mpBegin, cur->nameBegin) == 0)
                    break;
                n = n->mpNext;
                if (!n) {
                    do {
                        n = p[1];
                        ++p;
                    } while (!n);
                }
            }
            if (n == mDataMap.mpBucketArray[mDataMap.mnBucketCount]) {
                if ((cur->nameEnd - cur->nameBegin) != 0) {
                    EA::IO::ConcatenatePathComponents(path, msCacheDirectory.mpBegin, cur->nameBegin);
                    EA::IO::FileRemove(path);
                }
            }
            ++cur;
            if (cur == chunkEnd) {
                ++arr;
                cur = *arr;
                chunkEnd = cur + 4;
            }
        }
    }
    files.~DirEntryDeque();
    return true;
}

}} // namespace EA::Internet
