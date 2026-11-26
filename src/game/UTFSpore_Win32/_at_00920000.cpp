// src/game/UTFSpore_Win32/_at_00920000.cpp -- migrated from slice(s) s009205e0, s0091f520 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00920000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Debug/ReportWriter.h"

// unnamed retail callees and globals (address in the comment)
extern "C" char g_143d824[];
extern "C" __declspec(dllimport) int __cdecl strcmp(const char*, const char*);
#include <string.h>
#include <intrin.h>
#pragma intrinsic(__readfsdword)

// ---- items of slice s0091f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_143d824[];
void* __cdecl op_delete(void*);                       // 0x00f47380
void* __cdecl op_new(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
struct Mgr {
    virtual void m00();                    // 0x00
    virtual void m04();                    // 0x04
    virtual int  m08(int, int);            // 0x08
    virtual int  m0c(int);                 // 0x0c
    virtual int  m10();                    // 0x10
    virtual int  m14(int);                 // 0x14
    virtual int  m18();                    // 0x18
    virtual int  m1c(int, int, int);       // 0x1c
    virtual int  m20();                    // 0x20
    virtual int  m24(int, int, int);       // 0x24

    int Create(int a1, int a2, Mgr* a3);            // 0x009200d0
    int Factory24(int a1, int a2, int a3, int a4);  // 0x00920110
    int Factory1c(int a1, int a2, int a3, int a4);  // 0x00920240
};
struct HTNode {
    uint32_t k0, k1, k2;
    HTNode*  next;   // +0xc
};
struct HTable {
    uint32_t pad0;          // +0
    HTNode** buckets;       // +4
    uint32_t bucketCount;   // +8
    uint32_t count;         // +0xc
    uint32_t pad10;         // +0x10
    void EraseKey(HTNode*);   // 0x00920290
    HTNode* Insert(HTNode** out, uint32_t* key, int unused);
};
struct HTPre { void PreRehash(void*, uint32_t, uint32_t, int); }; // 0x00921440 (ecx = table+0x10)
struct HTMap {                 // 0x14 bytes of interest
    uint32_t pad0;             // +0x00
    HTNode** buckets;          // +0x04
    uint32_t bucketCount;      // +0x08
    uint32_t count;            // +0x0c
    void DoFreeNodes(HTNode** bucketArray, uint32_t bucketCount); // 0x007611f0
};
struct HTMap2 {                // table at +0x108
    uint32_t pad0;             // +0x00
    void**   buckets;          // +0x04
    uint32_t bucketCount;      // +0x08
    uint32_t count;            // +0x0c
    void DoFreeNodes(void** bucketArray, uint32_t bucketCount);   // 0x0093dc70
};
struct EARWMutexData { char pad[0x100]; };
class RWMutex {
public:
    EARWMutexData mRWMutexData;
    ~RWMutex();                                    // 0x00922310
};
struct HTStrNode {
    void*          key;    // +0
    uint32_t       a, b, c;
    HTStrNode*     next;   // +0x10
};
struct HTStrIter;
struct HTStr {
    uint32_t    pad0;
    HTStrNode** buckets;   // +4
    uint32_t    bucketCount; // +8

    HTStrIter* Find(HTStrIter* out, void** pkey); // @ 0x00920560
};
struct HTStrIter { HTStrNode* node; HTStrNode** slot; };
extern "C" __declspec(dllimport) int __cdecl strcmp(const char*, const char*);
struct NTbl {
    virtual void  n00();                        // 0x00
    virtual int   n04(void*, int);              // 0x04
    virtual int   n08(int, int);                // 0x08
    virtual void* n0c(int);                     // 0x0c
    virtual NTbl* n10(const char*, void*);      // 0x10

    int FindByName(const char* name, int extra, NTbl* tbl); // @ 0x00920160
};
// ---- items of slice s0091f520 end

// ---- items of slice s009205e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_154df28[];
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
extern wchar_t* g_pNullStr;             // 0x1667b88
extern unsigned g_boundLo[];   // 0x143d850
extern unsigned g_boundHi[];   // 0x143dc50
#pragma warning(disable:4035)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);
void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
struct EapdLock {
    int  mLockWord;                      // +0
    void Init(int count, int intra);     // 0x922500
    int  Lock(int reason, void* name);   // 0x9223a0
    void Unlock();                       // 0x922480
};
struct RangeMapper {   // receiver arrives in ECX
    float scale;        // +0
    float growth;       // +4
    int   limit;        // +8
    int   Round1(unsigned key);                                    // 0x921360
    int   Round2(int key);                                         // 0x9213c0
    void  Map(unsigned char* out, int a, int b, int c);            // 0x921440
};
void  sys_gui();                        // 0xc2e4e0
struct Range {
    wchar_t* begin;
    wchar_t* end;
    void append(const wchar_t* first, const wchar_t* last);   // 0x672750
    void appendChar(wchar_t c);                               // 0x8e3f10
};
Range* FUN_00920f30(Range* r, char flag);
wchar_t* FindExtension(wchar_t* first, wchar_t* last);
__declspec(noinline) unsigned* UpperBound(unsigned* first, unsigned* last, const unsigned* key);
__declspec(noinline) unsigned* LowerBound(unsigned* first, unsigned* last, const unsigned* key);
struct HashNode;
struct SymbolNode;
struct HashIter {
    HashNode*  mpNode;      // +0
    HashNode** mpSlot;      // +4
    HashIter() {}
    HashIter(const HashIter& o) : mpNode(o.mpNode), mpSlot(o.mpSlot) {}
};
struct SymbolIter {
    SymbolNode*  mpNode;    // +0
    SymbolNode** mpSlot;    // +4
    SymbolIter() {}
    SymbolIter(const SymbolIter& o) : mpNode(o.mpNode), mpSlot(o.mpSlot) {}
};
struct HashValue {
    const char* mpName;     // +0
    void*       mpStream;   // +4
    void*       mpOwner;    // +8
    unsigned    mKey;       // +0xc
};
struct HashNode {
    const char* mpName;     // +0
    void*       mpStream;   // +4
    void*       mpOwner;     // +8
    unsigned    mKey;       // +0xc
    HashNode*   mpNext;     // +0x10
};
struct SymbolValue {
    unsigned    mKey;       // +0
    void*       mpStream;   // +4
    void*       mpOwner;    // +8
};
struct SymbolNode {
    unsigned    mKey;       // +0
    void*       mpStream;   // +4
    void*       mpOwner;    // +8
    SymbolNode* mpNext;     // +0xc
};
struct HashTable {
    void*        mpUnknown0;    // +0
    HashNode**   mpBuckets;     // +4
    unsigned     mnBucketCount; // +8
    unsigned     mnSize;        // +0xc
    RangeMapper  mRangeMap;     // +0x10
    HashIter     insert(const HashValue& value, bool bFlag);  // @ 009205e0
    void         rehash(unsigned newSize);                    // 0x920340
    void         find(HashIter* out, const char* const* key); // 0x920560
    HashIter     erase(HashIter pos);                         // 0xb4f930
    unsigned     lookup(unsigned key);                        // @ 009209c0
    unsigned     find2(unsigned key, unsigned* out);          // @ 00920a70
};
struct SymbolHashTable {
    char         pad0[4];       // +0
    SymbolNode** mpBuckets;     // +4
    unsigned     mnBucketCount; // +8
    unsigned     mnSize;        // +0xc
    RangeMapper  mRangeMap;     // +0x10
    SymbolIter   insert(const SymbolValue& value, bool bFlag); // 0x920490
    SymbolIter   erase(SymbolIter pos);                        // 0x6859b0
};
struct EapdStream {
    virtual void        Unused0();                          // +0
    virtual unsigned    Read(void* buffer, unsigned size);  // +4
    virtual void        Unused1();                          // +8
    virtual const char* GetName(unsigned key);              // +0xc
};
struct EapdSymbolTable {
    char            pad00[8];    // +0
    EapdLock        mLock;       // +8
    char            pad0c[0xfc]; // +0xc
    SymbolHashTable symbols;     // +0x108
    char            pad124[4];   // +0x124
    HashTable       groups;      // +0x128
    EapdSymbolTable* ctor();                           // @ 009206d0
    bool LoadSymbols(EapdStream* stream);              // @ 00920780
    bool LoadGroups(EapdStream* stream, void* owner);  // @ 00920b30
};
struct EapdNode {
    unsigned mKey;      // +0
    unsigned mValue;    // +4
    unsigned mExtra;    // +8
    EapdNode* mpNext;   // +0xc
};
struct EapdFind {
    EapdNode*  node;
    EapdNode** slot;
};
struct EapdEastlTable {
    unsigned    pad0;         // +0
    EapdNode**  mpBuckets;    // +4
    unsigned    mnBucketCount;// +8
    unsigned    mnSize;       // +0xc
    void find(EapdFind* out, const unsigned* key);   // 0x685f30
};
struct EapdGroupNode {
    unsigned mKey;      // +0
    unsigned mValue;    // +4
    unsigned mExtra;    // +8
    unsigned mData;     // +0xc
    EapdGroupNode* mpNext;  // +0x10
};
struct EapdGroupFind {
    EapdGroupNode*  node;
    EapdGroupNode** slot;
};
struct EapdGroupTable {
    unsigned        pad0;          // +0
    EapdGroupNode** mpBuckets;     // +4
    unsigned        mnBucketCount; // +8
    unsigned        mnSize;        // +0xc
    void Find(EapdGroupFind* out, const unsigned* key);   // 0x920560
};
struct MapOut {
    bool mValid;   // +0
    int  mKey;     // +4
};
// ---- items of slice s009205e0 end

// @ 0x009200b0
int __stdcall CallRefCtor(Mgr* p)
{
    if (p != 0) {
        int r = p->m0c(1);
        if (r != 0) return r;
    }
    return 0;
}

// @ 0x009200d0
int Mgr::Create(int a1, int a2, Mgr* a3)
{
    if (a3 == 0)
        a3 = (Mgr*)m14(a1);
    if (a3 != 0)
        return a3->m08(a1, a2);
    return 0;
}

// @ 0x00920110
int Mgr::Factory24(int a1, int a2, int a3, int a4)
{
    Mgr* p = (Mgr*)m24(a1, a3, a4);
    if (p != 0) {
        int r = p->m0c(a2);
        if (r != 0) return r;
        p->m00();
        p->m04();
    }
    return 0;
}

// @ 0x00920160
int NTbl::FindByName(const char* name, int extra, NTbl* tbl)
{
    unsigned found = 0;
    unsigned handles[0x80];
    if (tbl == 0) {
        tbl = n10(name, &found);
    } else {
        unsigned n = (unsigned)tbl->n04(handles, 0x80);
        unsigned i = 0;
        while (i < n) {
            const char* nm = (const char*)tbl->n0c((int)handles[i]);
            if (strcmp(name, nm) == 0) { found = handles[i]; break; }
            ++i;
        }
        if (i == n) return 0;
    }
    if (tbl == 0) return 0;
    return tbl->n08((int)found, extra);
}

// @ 0x00920240
int Mgr::Factory1c(int a1, int a2, int a3, int a4)
{
    Mgr* p = (Mgr*)m1c(a1, a3, a4);
    if (p != 0) {
        int r = p->m0c(a2);
        if (r != 0) return r;
        p->m00();
        p->m04();
    }
    return 0;
}

// @ 0x00920410
void __fastcall HT_Destroy(HTNode** self)
{
    self[0] = (HTNode*)g_143d824;
    HTMap* a = (HTMap*)((char*)self + 0x128);
    a->DoFreeNodes(a->buckets, a->bucketCount);
    a->count = 0;
    if (a->bucketCount > 1)
        op_delete(a->buckets);
    HTMap2* b = (HTMap2*)((char*)self + 0x108);
    b->DoFreeNodes(b->buckets, b->bucketCount);
    b->count = 0;
    if (b->bucketCount > 1)
        op_delete(b->buckets);
    ((RWMutex*)((char*)self + 8))->~RWMutex();
}

// @ 0x00920490
HTNode* HTable::Insert(HTNode** out, uint32_t* key, int unused)
{
    HTable* self = this;
    uint8_t rehash[8];
    ((HTPre*)&self->pad10)->PreRehash(rehash, self->bucketCount, self->count, 1);
    if (rehash[0] != 0)
        self->EraseKey((HTNode*)*(uint32_t*)&rehash[4]);
    uint32_t first = key[0];
    HTNode* node = (HTNode*)op_new(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (node) { node->k0 = key[0]; node->k1 = key[1]; node->k2 = key[2]; }
    node->next = 0;
    uint32_t slot = first % self->bucketCount;
    HTNode* cur = self->buckets[slot];
    if (cur) {
        for (;;) {
            if (*key == cur->k0) {
                node->next = cur->next;
                cur->next = node;
                goto done;
            }
            cur = cur->next;
            if (!cur) break;
        }
    }
    node->next = self->buckets[slot];
    self->buckets[slot] = node;
done:
    self->count++;
    *out = node;
    out[1] = (HTNode*)&self->buckets[slot];
    return (HTNode*)out;
}

// @ 0x00920560
HTStrIter* HTStr::Find(HTStrIter* out, void** pkey)
{
    const uint8_t* s = (const uint8_t*)*pkey;
    uint32_t h = 0x811c9dc5;
    uint8_t c = *s;
    while (c != 0) {
        s++;
        h = h * 0x1000193 ^ c;
        c = *s;
    }
    uint32_t slot = h % bucketCount;
    HTStrNode** slotPtr = &buckets[slot];
    HTStrNode* cur = buckets[slot];
    while (cur) {
        if (*pkey == cur->key) goto found;
        cur = cur->next;
    }
    slotPtr = &buckets[bucketCount];
    cur = *slotPtr;
found:
    out->node = cur;
    out->slot = slotPtr;
    return out;
}

// @ 0x009205e0
HashIter HashTable::insert(const HashValue& value, bool bFlag)
{
    MapOut mo;
    mRangeMap.Map((unsigned char*)&mo, mnBucketCount, mnSize, 1);
    if (mo.mValid)
        rehash(mo.mKey);
    const unsigned char* s = (const unsigned char*)value.mpName;
    unsigned h = 0x811c9dc5;
    unsigned c = *s;
    while (c != 0) {
        ++s;
        h = h * 0x1000193 ^ c;
        c = *s;
    }
    const unsigned idx = h % mnBucketCount;
    HashNode* n = (HashNode*)EASTL_allocator_allocate(0x14, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (n != 0) {
        n->mpName = value.mpName;
        n->mpStream = value.mpStream;
        n->mpOwner = value.mpOwner;
        n->mKey = value.mKey;
    }
    n->mpNext = 0;
    HashNode* p = mpBuckets[idx];
    for (; p != 0; p = p->mpNext)
        if (value.mpName == p->mpName)
            break;
    if (p == 0) {
        n->mpNext = mpBuckets[idx];
        mpBuckets[idx] = n;
    } else {
        n->mpNext = p->mpNext;
        p->mpNext = n;
    }
    ++mnSize;
    HashIter result;
    result.mpNode = n;
    result.mpSlot = &mpBuckets[idx];
    return result;
}

// @ 0x009206d0
EapdSymbolTable* EapdSymbolTable::ctor()
{
    *(void**)((char*)this + 0) = (void*)g_143d824;
    mLock.Init(0, 1);
    *(float*)((char*)this + 0x118) = 1.0f;
    *(float*)((char*)this + 0x11c) = 2.0f;
    _ReadWriteBarrier();
    *(unsigned*)((char*)this + 0x114) = 0;
    *(unsigned*)((char*)this + 0x120) = 0;
    *(unsigned*)((char*)this + 0x110) = 1;
    _ReadWriteBarrier();
    *(void**)((char*)this + 0x10c) = (void*)g_154df28;
    _ReadWriteBarrier();
    *(float*)((char*)this + 0x138) = 1.0f;
    *(float*)((char*)this + 0x13c) = 2.0f;
    _ReadWriteBarrier();
    *(unsigned*)((char*)this + 0x134) = 0;
    *(unsigned*)((char*)this + 0x140) = 0;
    *(void**)((char*)this + 0x12c) = (void*)g_154df28;
    *(unsigned*)((char*)this + 0x130) = 1;
    return this;
}

// @ 0x00920780
bool EapdSymbolTable::LoadSymbols(EapdStream* stream)
{
    bool ok = true;
    mLock.Lock(2, (void*)0x143d820);
    unsigned keys[0x80];
    unsigned count = stream->Read(keys, 0x80);
    for (unsigned i = 0; i < count; ++i) {
        unsigned key = keys[i];
        unsigned idx = key % symbols.mnBucketCount;
        SymbolNode* node = symbols.mpBuckets[idx];
        SymbolNode** slot = &symbols.mpBuckets[idx];
        if (node != 0) {
            while (node->mKey != key) {
                node = node->mpNext;
                if (node == 0)
                    break;
            }
        }
        SymbolIter it;
        if (node == 0) {
            it.mpNode = symbols.mpBuckets[symbols.mnBucketCount];
            it.mpSlot = &symbols.mpBuckets[symbols.mnBucketCount];
        } else {
            it.mpNode = node;
            it.mpSlot = slot;
        }
        SymbolNode* end = symbols.mpBuckets[symbols.mnBucketCount];
        while (it.mpNode != end) {
            if (it.mpNode->mKey != key) {
                ok = false;
                break;
            }
            if (it.mpNode->mpStream == stream) {
                symbols.erase(it);
                break;
            }
            if (it.mpNode->mpNext != 0) {
                it.mpNode = it.mpNode->mpNext;
            } else {
                do {
                    ++it.mpSlot;
                    it.mpNode = *it.mpSlot;
                } while (it.mpNode == 0);
            }
            if (it.mpNode == end)
                break;
        }
        const char* name = stream->GetName(key);
        if (name != 0) {
            HashIter git;
            groups.find(&git, &name);
            HashNode* gend = groups.mpBuckets[groups.mnBucketCount];
            while (git.mpNode != gend) {
                if (strcmp(git.mpNode->mpName, name) != 0) {
                    ok = false;
                    break;
                }
                if (git.mpNode->mpStream == stream) {
                    groups.erase(git);
                    break;
                }
                if (git.mpNode->mpNext != 0) {
                    git.mpNode = git.mpNode->mpNext;
                } else {
                    do {
                        ++git.mpSlot;
                        git.mpNode = *git.mpSlot;
                    } while (git.mpNode == 0);
                }
                if (git.mpNode == gend)
                    break;
            }
        }
    }
    mLock.Unlock();
    return ok;
}

// @ 0x009209c0
unsigned HashTable::lookup(unsigned key)
{
    EapdLock* lk = (EapdLock*)((char*)this + 8);
    lk->Lock(1, (void*)0x143d820);
    EapdEastlTable* t = (EapdEastlTable*)((char*)this + 0x108);
    EapdFind it;
    t->find(&it, &key);
    EapdNode* end = t->mpBuckets[t->mnBucketCount];
    EapdNode* p = it.node;
    unsigned* found = 0;
    if (p != end) {
        while (true) {
            if (p->mKey != key)
                break;
            if (found == 0 || found[1] < p->mExtra)
                found = &p->mValue;
            p = p->mpNext;
            if (p == 0) {
                EapdNode** slot = it.slot + 1;
                do {
                    p = *slot;
                    ++slot;
                } while (p == 0);
            }
            if (p == end)
                break;
        }
    }
    unsigned r = 0;
    if (found != 0)
        r = *found;
    lk->Unlock();
    return r;
}

// @ 0x00920a70
unsigned HashTable::find2(unsigned key, unsigned* out)
{
    EapdLock* lk = (EapdLock*)((char*)this + 8);
    lk->Lock(1, (void*)0x143d820);
    EapdGroupTable* t = (EapdGroupTable*)((char*)this + 0x128);
    EapdGroupFind it;
    t->Find(&it, &key);
    EapdGroupNode* end = t->mpBuckets[t->mnBucketCount];
    EapdGroupNode* p = it.node;
    unsigned* found = 0;
    if (p != end) {
        while (true) {
            if (p->mKey != key)
                break;
            if (found == 0 || found[1] < p->mExtra)
                found = &p->mValue;
            p = p->mpNext;
            if (p == 0) {
                EapdGroupNode** slot = it.slot + 1;
                do {
                    p = *slot;
                    ++slot;
                } while (p == 0);
            }
            if (p == end)
                break;
        }
    }
    unsigned r = 0;
    if (found != 0) {
        if (out != 0)
            *out = found[2];
        r = *found;
    }
    lk->Unlock();
    return r;
}

// @ 0x00920b30
bool EapdSymbolTable::LoadGroups(EapdStream* stream, void* owner)
{
    mLock.Lock(2, (void*)0x143d820);
    unsigned keys[0x80];
    unsigned count = stream->Read(keys, 0x80);
    for (unsigned i = 0; i < count; ++i) {
        unsigned key = keys[i];
        SymbolValue sv;
        sv.mKey = key;
        sv.mpStream = stream;
        sv.mpOwner = owner;
        bool bSymFlag = false;
        symbols.insert(sv, bSymFlag);
        const char* name = stream->GetName(key);
        if (name != 0) {
            HashValue gv;
            gv.mpName = name;
            gv.mpStream = stream;
            gv.mpOwner = owner;
            gv.mKey = key;
            bool bGroupFlag = false;
            groups.insert(gv, bGroupFlag);
        }
    }
    mLock.Unlock();
    return true;
}

// 0x00920c20 (byte-exact lifted version: match/slices/s00920c20/s00920c20.cpp)
bool HasAltSeparator(wchar_t* first, wchar_t* last)
{
    for (; first < last; ++first) {
        wchar_t c = *first;
        if (c == L':')
            return true;
        if (c == L'\\' || c == L'/')
            break;
    }
    return false;
}

// @ 0x00920c60
wchar_t* SkipComponent(wchar_t* first, wchar_t* last)
{
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if ((first + 2 <= last) && (first[0] == L'\\' || first[0] == L'/') &&
        (first[1] == L'\\' || first[1] == L'/'))
        first += 2;
    if (first < last) {
        while (true) {
            wchar_t c = *first;
            if (c == L'\\' || c == L'/')
                break;
            ++first;
            if (c == L':')
                break;
            if (last <= first)
                return first;
        }
        if (first < last && (*first == L'\\' || *first == L'/'))
            ++first;
    }
    return first;
}

// @ 0x00920d00
wchar_t* SkipComponentBack(wchar_t* first, wchar_t* last)
{
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if (first < last) {
        if (last[-1] == L'\\' || last[-1] == L'/')
            --last;
        if (first < last) {
            if (last[-1] == L':')
                --last;
            while (first < last && last[-1] != L'\\' && last[-1] != L'/' && last[-1] != L':')
                --last;
        }
    }
    if (last == first + 2 && (first[0] == L'\\' || first[0] == L'/') &&
        (first[1] == L'\\' || first[1] == L'/'))
        last = first;
    return last;
}

// @ 0x00920da0
wchar_t* ComponentAt(wchar_t* first, wchar_t* last, int index)
{
    if (index >= 0) {
        wchar_t* p = first;
        for (++index; p < last && index > 0; --index)
            p = SkipComponent(p, last);
        if (index == 0 && p > first && (p[-1] == L'\\' || p[-1] == L'/'))
            --p;
        return p;
    }
    ++index;
    while (last > first) {
        if (index >= 0) {
            if (last > first && (last[-1] == L'\\' || last[-1] == L'/'))
                --last;
            return last;
        }
        last = SkipComponentBack(first, last);
        ++index;
    }
    return last;
}

// @ 0x00920e30
wchar_t* FindExtension(wchar_t* first, wchar_t* last)
{
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if (first < last && (last[-1] == L'\\' || last[-1] == L'/'))
        return last;
    if ((first + 2 <= last) && (first[0] == L'\\' || first[0] == L'/') &&
        (first[1] == L'\\' || first[1] == L'/'))
        first = SkipComponent(first, last);
    wchar_t* p = last - 1;
    while (first <= p) {
        wchar_t c = *p;
        if (c == L'\\' || c == L'/' || c == L':')
            break;
        if (c == L'.')
            return p;
        if (--p < first)
            return last;
    }
    return last;
}

// @ 0x00920ee0
void NormalizeSeparators2(Range* r)
{
    FindExtension(r->begin, r->end);
}

// @ 0x00920f00
Range* NormalizeSeparators(Range* r)
{
    wchar_t* p = r->begin;
    if (p != r->end) {
        do {
            if (*p == L'/' || *p == L'\\')
                *p = L'\\';
            ++p;
        } while (p != r->end);
    }
    return r;
}

// @ 0x00920f30
Range* FUN_00920f30(Range* r, char flag)
{
    wchar_t* src = r->begin;
    wchar_t* last = r->end;
    wchar_t* dst = src;
    bool bAbsolute = false;
    if (src + 2 <= last && (src[0] == L'\\' || src[0] == L'/') &&
        (src[1] == L'\\' || src[1] == L'/'))
        bAbsolute = true;
    if (HasAltSeparator(src, last))
        bAbsolute = true;
    // leading run of separators is copied verbatim (UNC prefix)
    while (src < last) {
        wchar_t c = *src;
        if (c != L'\\' && c != L'/')
            break;
        if (flag)
            c = L'\\';
        *dst++ = c;
        ++src;
    }
    while (src < last) {
        if (src + 1 < last && src[0] == L'.' && (src[1] == L'\\' || src[1] == L'/')) {
            src += 2;
            while (src < last && (*src == L'\\' || *src == L'/'))
                ++src;
            continue;
        }
        if (src + 2 < last && src[0] == L'.' && src[1] == L'.' &&
            (src[2] == L'\\' || src[2] == L'/')) {
            wchar_t* begin = r->begin;
            if (dst > begin) {
                wchar_t* p = SkipComponentBack(begin, dst);
                if (p > begin || !bAbsolute) {
                    src += 3;
                    dst = p;
                    while (src < last && (*src == L'\\' || *src == L'/'))
                        ++src;
                    continue;
                }
            }
        }
        while (src < last) {
            wchar_t c = *src++;
            if (c == L'\\' || c == L'/') {
                if (flag)
                    c = L'\\';
                *dst++ = c;
                while (src < last && (*src == L'\\' || *src == L'/'))
                    ++src;
                break;
            }
            if (c == L':') {
                *dst++ = c;
                if (src >= last)
                    goto done;
                if (*dst == L'\\' || *dst == L'/')
                    continue;
                break;
            }
            *dst++ = c;
        }
    }
done:
    if (dst != last) {
        wchar_t* e = r->end;
        memmove(dst, last, (size_t)(e - last + 1) * sizeof(wchar_t));
        r->end = dst + (e - last);
    }
    return r;
}

// 0x00921150 (byte-exact lifted version: match/slices/s00921150/s00921150.cpp)
Range* FUN_00921150(Range* out, wchar_t* first, wchar_t* last)
{
    if (last == g_pNullStr) {
        wchar_t* e = first;
        while (*e != 0)
            ++e;
        last = e;
    }
    if (first == last)
        return out;
    bool alt = first < last && HasAltSeparator(first, last);
    if (!alt)
        alt = first < last && (*first == L'\\' || *first == L'/');
    if (alt) {
        if (out->begin != out->end) {
            *out->begin = 0;
            out->end = out->begin;
            out->append(first, last);
            return out;
        }
    } else if (out->begin == out->end ||
               (out->end[-1] != L'\\' && out->end[-1] != L'/')) {
        out->appendChar(L'\\');
    }
    out->append(first, last);
    return out;
}

// @ 0x00921210
void FUN_00921210(void* out, Range* r)
{
    FUN_00921150((Range*)out, r->begin, r->end);
    FUN_00920f30((Range*)out, 1);
}

// @ 0x00921250
void DebugPrint(const char* s)
{
    OutputDebugStringA(s);
    sys_gui();
}

// @ 0x009212c0
unsigned* UpperBound(unsigned* first, unsigned* last, const unsigned* key)
{
    int n = (int)(last - first);
    while (n > 0) {
        int half = n >> 1;
        unsigned* mid = first + half;
        if (!(*key < *mid)) {
            first = ++mid;
            n -= half + 1;
        } else
            n = half;
    }
    return first;
}

// @ 0x00921300
unsigned* LowerBound(unsigned* first, unsigned* last, const unsigned* key)
{
    int n = (int)(last - first);
    while (n > 0) {
        int half = n >> 1;
        unsigned* mid = first + half;
        if (*mid < *key) {
            first = ++mid;
            n -= half + 1;
        } else
            n = half;
    }
    return first;
}

// @ 0x00921340
int FUN_00921340(unsigned key)
{
    unsigned* p = UpperBound(g_boundLo, g_boundHi, &key);
    return (int)p[-1];
}
