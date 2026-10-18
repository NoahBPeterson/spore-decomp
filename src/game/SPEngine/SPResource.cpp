// src/game/SPEngine/SPResource.cpp -- migrated from slice(s) s006ad5c0, s006ac630, s006ab3d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPResource.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/FixedAllocatorBase.h"

// unnamed retail callees and globals (address in the comment)
extern char sNullCache;            // 0x0152f7bc
extern char sManualExplicitCache;  // 0x0152f7c0
extern char sLRUCaches;            // 0x016032a8
#include <intrin.h>
#include "EA/Audio/IPrimitive.h"
#include "EA/Thread/Mutex.h"
#include <string.h>
#include "SP/cAsyncResourceRequest.h"
#include "SP/cJob.h"
#include "SP/cJobManager.h"

// ---- items of slice s006ab3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  EASTL_allocator_deallocate(void* p);                          // 0x00f47380
extern char sNullCache;            // 0x0152f7bc
extern char sManualExplicitCache;  // 0x0152f7c0
extern char sLRUCaches;            // 0x016032a8
struct CacheHolder { void** vtbl; };
inline int CacheHolder_Find(CacheHolder* o, int id)
{
    typedef int (__thiscall* Fn)(void*, int);
    return ((Fn)o->vtbl[0xc / 4])(o, id);
}
// ---- items of slice s006ab3d0 end

// ---- items of slice s006ac630 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
 extern const unsigned int kTimeoutNone; 
}  // 0x1436788
}
void operator delete(void* p) throw();   // 0x00f47380
struct IObj {
    virtual void AddRef();                  // +0
    virtual void Release();                 // +4
    virtual void Slot2();                   // +8  (resource: deleting dtor)
    virtual void* Cast(uint32_t iid);       // +0xc
};
struct cResourceBase {                      // what Cast(0x355d6f5) returns
    virtual void Slot0();
    virtual void Slot1();
    virtual void Destroy(int flags);        // +8
    int mnRefCount;                         // +4 (vptr at +0)
    uint32_t key[3];                        // +8 instance, +0xc type, +0x10 group
    int mnRegistered;                       // +0x14 (cleared on unregister)
};
typedef void (__cdecl *ResCallback)(bool, cResourceBase*);
struct CbNode { CbNode* unused; ResCallback* begin; ResCallback* end; };
struct CbIter { CbNode* node; CbNode** bucket; };
struct CbTable {                            // hashtable<uint, fixed_vector<cb,8>> at 0x152f79c
    void* pad0; CbNode** buckets; uint32_t bucketCount;
    void find(CbIter* out, const uint32_t* key);   // 0x006ac490
};
extern CbTable gCbTable;   // 0x152f79c
struct RegNode { uint32_t key[3]; IObj* value; RegNode* next; };
struct RegIter { RegNode* node; RegNode** bucket; };
struct RegPair { uint32_t key[3]; IObj* value; };
struct RegTable {                           // eastl hashtable at Registry+0xc
    void* pad0;
    RegNode** buckets;                      // +4
    uint32_t bucketCount;                   // +8
    int count;                              // +0xc
    char pad1[0x1c];
    void* freelist;                         // +0x2c
    void find(RegIter* out, const uint32_t* key);                     // 0x00833840
    void insert(RegIter* out, RegPair* pr, bool b);                   // 0x006ac4f0
    RegIter* erase(RegIter* out, RegIter it);                         // 0x006aca20
};
struct RWSpinLock {                         // at Registry+0x48
    long state;                             // +0 (bit0 = writer, +2 per reader)
    long pad4;
    long generation;                        // +8 (Registry+0x50)
    void AcquireShared();                    // 0x006abf20
    void AcquireExclusive();                 // 0x006abfa0
};
struct Registry {
    char pad0[0xc];
    RegTable table;                         // +0xc
    char pad1[0x48 - 0xc - sizeof(RegTable)];
    RWSpinLock lock;                        // +0x48
    char padRegistry[0x34];
    bool Register(void* key, void* obj);     // 0x006acc60
    bool Unregister(void* key, void* obj);   // 0x006ace70
    bool Lookup(const uint32_t* key, IObj** out);     // 0x006ac840
    int Enumerate(void* list, struct IFilter* f);    // 0x006ac8d0
    bool ClearAll();                         // 0x006ac7d0
};
extern Registry* sRegistry;   // 0x01603118
bool Registry_RegisterFree(void* key, void* obj);     // 0x006acc60 (cdecl tail-call form)
bool Registry_UnregisterFree(void* key, void* obj);   // 0x006ace70
struct Mutex {
    Mutex(void* attr, bool b);   // 0x009222a0
    ~Mutex();                    // 0x00922130
    int Lock(const int& timeout);
    int Unlock();
};
extern const int kTimeoutNone;   // 0x014093b4
struct LockGuard {
    Mutex* m;
    LockGuard(Mutex* mm) : m(mm) { m->Lock(kTimeoutNone); }
    ~LockGuard() { m->Unlock(); }
};
struct ReadGuard {
    long* p;
    ReadGuard(Registry* r) : p(&r->lock.state) { r->lock.AcquireShared(); }
    ~ReadGuard() { _InterlockedExchangeAdd(p, -2); }
};
struct WriteGuard {
    Registry* r;
    WriteGuard(Registry* rr) : r(rr) { r->lock.AcquireExclusive(); }
    ~WriteGuard() { _InterlockedExchangeAdd(&r->lock.state, -1); _InterlockedExchangeAdd(&r->lock.generation, 1); }
};
void OnRegister(bool added, IObj* obj);
struct RegEntry { cResourceBase* obj; int count; };
struct RegVec {
    RegEntry* mpBegin;      // +4
    RegEntry* mpEnd;        // +8
    RegEntry* mpCapEnd;     // +0xc
    int pad10;
    void* mpBuf;            // +0x14
    int pad18;
    RegEntry mBuf[32];      // +0x1c
    int pad11c;             // +0x11c
    RegVec()
    {
        RegEntry* p = mBuf;
        mpBuf = p;
        mpEnd = p;
        mpBegin = p;
        mpCapEnd = p + 32;
    }
    ~RegVec()
    {
        if (mpBegin && mpBegin != mpBuf)
            operator delete(mpBegin);
    }
};
struct RegList {
    virtual void Add(cResourceBase* obj);   // vtable 0x014093c4 slot 0 = 0x006ad410
    virtual ~RegList();                     // slot 1 = 0x006ac750 (scalar deleting dtor)
    RegVec v;               // +4
    Mutex mMutex;           // +0x120
    RegList();
    bool ReleaseAll();      // 0x006ad270
    void Reset();           // 0x006ad350
};
struct IFilter { virtual void S0(); virtual bool Accept(RegNode* n); };
struct ListNode { ListNode* next; ListNode* prev; IObj* value; };
ListNode* AllocListNode(void* list, IObj** tmp);      // 0x006ac3c0 (thiscall on list)
struct Elem8 { uint32_t a, b; };
struct Vec8 {
    Elem8* mpBegin; Elem8* mpEnd; Elem8* mpCapEnd; int pad; Elem8* mpFixed;
    void InsertN(Elem8* pos, uint32_t n, const Elem8* val);
};
Elem8* UninitCopy(Elem8* first, Elem8* last, Elem8* dst);                // 0x0099efa0
void* AllocBytes(uint32_t bytes, const char* name, int, int, const char* file, int line);   // 0x00f473a0
struct CopyTag {};   // by-value tag argument: an unused, uninitialised dword
void CopyFwd(Elem8** out, Elem8* first, Elem8* last, Elem8* dst, CopyTag);   // 0x0076ffd0 (eastl::copy)
void CopyBack(Elem8* first, Elem8* last, Elem8* dstEnd);                 // 0x0073fe50
void FillRange(Elem8* first, Elem8* last, const Elem8* v);               // 0x00a52da0
void UninitFill(Elem8* dst, uint32_t n, const Elem8* v);                 // 0x006ac440
    void operator delete(void*); // 0x00f47380
// ---- items of slice s006ac630 end

// ---- items of slice s006ad5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pRegistry;   // 0x1603118
extern char  g_caches[];    // 0x16032a8, array of cLRUCache, stride 0x150
extern char  g_cachesEnd[]; // 0x1604118
extern "C" void ea_dealloc(void*);          // 0x00f47380
extern char g_callbackMap[];                // 0x152f79c  hash_map<unsigned, vector>
extern void* vtbl_154df28;
extern void* vtbl_14093bc;
extern void* vtbl_14093cc;
extern void* vtbl_13effb8;
extern "C" void* ea_eastl_alloc(unsigned size, void* zone, int, int, const char* file, int line); // 0xf473a0
extern "C" void ea_zone_delete(void*);      // 0x926060
struct cLRUCache {
    void Clear();          // FUN_006ad350
    void Reset();          // FUN_006ad270
    void Do(int);          // FUN_006ada20
    void Destroy(void** base, unsigned count);  // 006ad910
};
#define VFN(off) (*(void***)p)[(off) / 4]
namespace SP {
void FlushCache(int x);
}
namespace SP {
struct RCVector { void* x0; void** fill; void** cap; };
}
namespace SP {
struct CallbackMap { RCVector* operator[](const unsigned* key); };
}
namespace SP {
struct RCVectorOps { void Grow(void** p, void** v); };
}
namespace SP {
void AddRegistrationCallback(unsigned key, void* cb);
}
struct Sub140 { void Init(void* a); };      // FUN_006ac140
struct KRSub  { void Destroy(); };          // FUN_006ad0f0
struct Sub970 { void Do(void* x, void* y, void* a); }; // FUN_006ad970
// ---- items of slice s006ad5c0 end

// @ 0x006abee0
bool __fastcall FUN_006abee0(char* self)
{
    if (self[8] == 0)
        self[8] = 1;
    return true;
}



// @ 0x006abf20
void FUN_006abf20(void* self)
{
    // TODO(partial): spin-wait / atomic retire queue.
    (void)self;
}



// @ 0x006abfa0
void FUN_006abfa0(void* self)
{
    // TODO(partial): atomic refcount retire helper.
    (void)self;
}



// @ 0x006ac040
bool SetCachingType(int type, void* obj)
{
    if (*(void**)((char*)obj + 0x14) != 0)
        return false;
    if (type == 2) { *(void**)((char*)obj + 0x14) = &sNullCache; return true; }
    if (type == 1) { *(void**)((char*)obj + 0x14) = &sManualExplicitCache; return true; }
    if ((unsigned)(type - 3) <= 0xa) {
        *(void**)((char*)obj + 0x14) = (char*)&sLRUCaches + (type - 3) * 0x150;
        return true;
    }
    if (type != 0)
        return false;
    return true;
}



// @ 0x006ac0a0
uint32_t FUN_006ac0a0(uint32_t type, CacheHolder* obj)
{
    if (!obj)
        return 0;
    int v = CacheHolder_Find(obj, 0x355d6f5);
    if (!v)
        return 0;
    return SetCachingType(type, (void*)v);
}



// @ 0x006ac0d0
int FUN_006ac0d0(CacheHolder* obj)
{
    if (!obj)
        return 0;
    int v = CacheHolder_Find(obj, 0x355d6f5);
    if (!v)
        return 0;
    void** c = *(void***)(v + 0x14);
    if (!c)
        return 0;
    if (c == (void**)&sManualExplicitCache) return 1;
    if (c == (void**)&sNullCache) return 2;
    if ((uint32_t)c > 0x16032a7u && (uint32_t)c < 0x1604118u)
        return (int)((char*)c - 0x16032a8) / 0x150 + 3;
    return 0;
}



// @ 0x006ac140
void FUN_006ac140(void* self)
{
    // TODO(partial): FixedAllocatorBase::Init + vtable setup.
    (void)self;
}



// @ 0x006ac260
void* FUN_006ac260(void* self, void* value)
{
    // TODO(partial): fixed-allocator node allocation + value copy.
    (void)self; (void)value;
    return 0;
}



// @ 0x006ac2f0
void FUN_006ac2f0(void* self, void* a2, void* a3)
{
    // TODO(partial): fixed-allocator node init loop.
    (void)self; (void)a2; (void)a3;
}



// @ 0x006ac3c0
void FUN_006ac3c0(void* self)
{
    // TODO(partial): fixed-allocator core teardown.
    (void)self;
}



// @ 0x006ac440
void FUN_006ac440(uint32_t* dst, uint32_t count, const uint32_t* src)
{
    while (count != 0) {
        if (dst) {
            dst[0] = src[0];
            dst[1] = src[1];
        }
        dst += 2;
        --count;
    }
}



// @ 0x006ac470
void __fastcall FUN_006ac470(int self)
{
    int p = *(int*)(self + 4);
    if (p != 0 && p != *(int*)(self + 0x14))
        EASTL_allocator_deallocate((void*)p);
}



// @ 0x006ac5d0
void FUN_006ac5d0(void* self, void* buckets, uint32_t count)
{
    // TODO(partial): free a bucket array of allocated nodes.
    (void)self; (void)buckets; (void)count;
}


// @ 0x006ac630
void OnRegister(bool added, IObj* obj)
{
    if (obj) {
        cResourceBase* p = (cResourceBase*)obj->Cast(0x355d6f5);
        if (p) {
            long* rc = (long*)&p->mnRefCount;
            if (added) {
                _InterlockedExchangeAdd(rc, 1);
            } else {
                if (_InterlockedDecrement(rc) == 0) {
                    _InterlockedExchange(rc, 2);
                    p->Destroy(1);
                }
            }
            CbIter it;
            gCbTable.find(&it, &p->key[1]);
            if (it.node != gCbTable.buckets[gCbTable.bucketCount]) {
                CbNode* n = it.node;
                int cnt = (int)(n->end - n->begin);
                for (int i = 0; i < cnt; i++)
                    n->begin[i](added, p);
            }
        }
    }
}


// @ 0x006ac6f0
RegList::~RegList()
{
}


// @ 0x006ac770
RegList::RegList()
: mMutex(0, true)
{
}


// @ 0x006ac7d0
bool Registry::ClearAll()
{
    char& flag = *((char*)this + 8);
    if (flag) {
        RegNode** pb = table.buckets;
        RegNode* n = *pb;
        if (!n) {
            do { ++pb; n = *pb; } while (!n);
        }
        RegNode* end = table.buckets[table.bucketCount];
        while (n != end) {
            OnRegister(false, n->value);
            n = n->next;
            if (!n) {
                do { ++pb; n = *pb; } while (!n);
            }
        }
        flag = 0;
    }
    return true;
}


// @ 0x006ac840
bool Registry::Lookup(const uint32_t* key, IObj** out)
{
    ReadGuard g(this);
    RegIter it;
    table.find(&it, key);
    if (it.node == table.buckets[table.bucketCount])
        return false;
    if (out) {
        IObj* v = it.node->value;
        *out = v;
        v->AddRef();
    }
    return true;
}


// @ 0x006ac8d0
int Registry::Enumerate(void* list, IFilter* f)
{
    ReadGuard g(this);
    int matched = 0;
    RegNode** pb = table.buckets;
    RegNode* n = *pb;
    if (!n) {
        do { ++pb; n = *pb; } while (!n);
    }
    RegNode* end = table.buckets[table.bucketCount];
    while (n != end) {
        if (!f || f->Accept(n)) {
            matched++;
            if (list) {
                IObj* tmp = 0;
                ListNode* head = (ListNode*)list;
                ListNode* nn = AllocListNode(list, &tmp);
                nn->next = head;
                nn->prev = head->prev;
                head->prev->next = nn;
                head->prev = nn;
                tmp = nn->value;
                IObj* v = n->value;
                if (v != tmp) {
                    if (v) v->AddRef();
                    nn->value = v;
                    if (tmp) tmp->Release();
                }
            }
        }
        n = n->next;
        if (!n) {
            do { ++pb; n = *pb; } while (!n);
        }
    }
    return matched;
}


// @ 0x006aca20
RegIter* RegTable::erase(RegIter* out, RegIter it)
{
    RegNode* node = it.node;
    RegNode** bucket = it.bucket;
    // advance to the next element
    out->bucket = bucket;
    out->node = node->next;
    while (!out->node) {
        out->bucket++;
        out->node = *out->bucket;
    }
    RegNode* cur = *bucket;
    if (cur == node) {
        *bucket = cur->next;
    } else {
        RegNode* nx = cur->next;
        while (nx != node) {
            cur = nx;
            nx = nx->next;
        }
        cur->next = nx->next;
    }
    if (node->value)
        node->value->Release();
    *(void**)node = freelist;
    freelist = node;
    count--;
    return out;
}


// @ 0x006acaa0
void Vec8::InsertN(Elem8* pos, uint32_t n, const Elem8* val)
{
    if (n <= (uint32_t)(mpCapEnd - mpEnd)) {
        if (n > 0) {
            const Elem8 tmp = *val;
            Elem8* const end = mpEnd;
            const uint32_t after = (uint32_t)(end - pos);
            if (n < after) {
                Elem8* o;
                CopyTag t;
                CopyFwd(&o, end - n, end, end, t);
                mpEnd += n;
                CopyBack(pos, end - n, end);
                FillRange(pos, pos + n, &tmp);
            } else {
                UninitFill(end, n - after, &tmp);
                mpEnd += n - after;
                Elem8* o;
                CopyTag t;
                CopyFwd(&o, pos, end, mpEnd, t);
                mpEnd += after;
                FillRange(pos, end, &tmp);
            }
        }
    } else {
        const uint32_t oldSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t grow = oldSize > 0 ? oldSize * 2 : 1;
        const uint32_t need = oldSize + n;
        const uint32_t newCap = grow > need ? grow : need;
        Elem8* const mem = newCap ? (Elem8*)AllocBytes(newCap * 8, "App", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        Elem8* const mid = UninitCopy(mpBegin, pos, mem);
        Elem8* d = mid;
        for (uint32_t i = n; i > 0; --i, ++d) {
            if (d) *d = *val;
        }
        Elem8* const end2 = UninitCopy(pos, mpEnd, mid + n);
        if (mpBegin && mpBegin != mpFixed)
            operator delete(mpBegin);
        mpBegin = mem;
        mpEnd = end2;
        mpCapEnd = mem + newCap;
    }
}


// @ 0x006acc60
bool Registry::Register(void* vkey, void* vobj)
{
    const uint32_t* key = (const uint32_t*)vkey;
    IObj* obj = (IObj*)vobj;
    bool r = false;
    IObj* old = 0;
    if (obj) {
        bool same;
        {
            ReadGuard g(this);
            RegIter it;
            table.find(&it, key);
            if (it.node != table.buckets[table.bucketCount] && it.node->value == obj) {
                r = true;
                same = true;
            } else {
                same = false;
            }
        }
        if (!same) {
            bool added;
            {
                WriteGuard w(this);
                RegIter it;
                table.find(&it, key);
                if (it.node == table.buckets[table.bucketCount]) {
                    obj->AddRef();
                    RegPair pr;
                    pr.key[0] = key[0]; pr.key[1] = key[1]; pr.key[2] = key[2];
                    pr.value = obj;
                    obj->AddRef();
                    obj->Release();
                    table.insert(&it, &pr, false);
                    added = true;
                    if (pr.value) pr.value->Release();
                } else {
                    IObj** slot = &it.node->value;
                    added = (*slot != obj);
                    if (added) {
                        old = *slot;
                        *slot = 0;
                        if (obj) obj->AddRef();
                        *slot = obj;
                    }
                    if (old) {
                        cResourceBase* p = (cResourceBase*)old->Cast(0x355d6f5);
                        if (p) p->mnRegistered = 0;
                    }
                }
                r = true;
            }
            if (old)
                OnRegister(false, old);
            if (added)
                OnRegister(true, obj);
        }
    }
    if (old)
        old->Release();
    return r;
}


// @ 0x006ace70
bool Registry::Unregister(void* vkey, void* vobj)
{
    const uint32_t* key = (const uint32_t*)vkey;
    IObj* obj = (IObj*)vobj;
    IObj* old = 0;
    bool r = false;
    bool absent = false;
    {
        ReadGuard g(this);
        RegIter it;
        table.find(&it, key);
        if (it.node == table.buckets[table.bucketCount] || (obj && it.node->value != obj))
            absent = true;
    }
    if (!absent) {
        {
            WriteGuard w(this);
            RegIter it;
            table.find(&it, key);
            if (it.node == table.buckets[table.bucketCount]) {
                r = false;
            } else if (!obj || it.node->value == obj) {
                old = it.node->value;
                it.node->value = 0;
                RegIter out;
                table.erase(&out, it);
                r = true;
                if (old) {
                    cResourceBase* p = (cResourceBase*)old->Cast(0x355d6f5);
                    if (p) p->mnRegistered = 0;
                }
            }
        }
        if (old)
            OnRegister(false, old);
    }
    if (old)
        old->Release();
    return r;
}


// @ 0x006acfe0
bool FUN_006acfe0(uint32_t* a, char* b)
{
    *(uint32_t*)(b + 8)  = a[0];
    *(uint32_t*)(b + 0xc) = a[1];
    *(uint32_t*)(b + 0x10) = a[2];
    if (sRegistry)
        return sRegistry->Register(a, b);
    return false;
}


// @ 0x006ad010
bool FUN_006ad010(char* a)
{
    if (sRegistry)
        return sRegistry->Register(a + 8, a);
    return false;
}


// @ 0x006ad030
bool FUN_006ad030(char* a)
{
    if (sRegistry)
        return sRegistry->Unregister(a, 0);
    return false;
}


// @ 0x006ad050
bool FUN_006ad050(char* a)
{
    if (sRegistry)
        return sRegistry->Unregister(a + 8, a);
    return false;
}


// @ 0x006ad070
void RemoveRegistrationCallback(uint32_t key, ResCallback callback)
{
    CbIter it;
    gCbTable.find(&it, &key);
    if (it.node != gCbTable.buckets[gCbTable.bucketCount]) {
        ResCallback* end = it.node->end;
        ResCallback* begin = it.node->begin;
        int n = (int)(end - begin);
        int i = 0;
        ResCallback* p = begin;
        if (n > 0) {
            while (*p != callback) {
                i++;
                p++;
                if (i >= n)
                    return;
            }
            ResCallback* tail = begin + i + 1;
            if (tail < end)
                memmove(begin + i, tail, (char*)end - (char*)tail);
            it.node->end -= 1;
        }
    }
}


// @ 0x006ad250
void __stdcall FUN_006ad250(char* a)
{
    Registry* r = sRegistry;
    if (r)
        r->Unregister(a + 8, a);
}


// @ 0x006ad410
void RegList::Add(cResourceBase* obj)
{
    LockGuard g(&mMutex);
    if (v.mpBegin == v.mpEnd) {
        if (sRegistry)
            sRegistry->Unregister(&obj->key[0], obj);
    } else {
        int n = (int)(v.mpEnd - v.mpBegin);
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (v.mpBegin[i].obj == obj) {
                v.mpBegin[i].count++;
                found = true;
                break;
            }
        }
        int n2 = (int)(v.mpEnd - v.mpBegin);
        int freeSlot = -1;
        int best = 0;
        int bestIdx = 0;
        for (int i = 0; i < n2; i++) {
            if (v.mpBegin[i].obj) {
                int c = _InterlockedExchangeAdd((long*)&v.mpBegin[i].obj->mnRefCount, 0);
                if ((c >> 1) - 1 > 0) {
                    v.mpBegin[i].obj = 0;
                    v.mpBegin[i].count = 1000;
                    freeSlot = i;
                } else {
                    v.mpBegin[i].count++;
                }
            }
            int cnt = v.mpBegin[i].count;
            if (best < cnt) {
                best = cnt;
                bestIdx = i;
            }
        }
        if (!found) {
            int idx = freeSlot;
            if (idx < 0)
                idx = bestIdx;
            RegEntry* e = &v.mpBegin[idx];
            cResourceBase* prev = e->obj;
            if (prev && sRegistry)
                sRegistry->Unregister(&prev->key[0], prev);
            e->obj = obj;
            e->count = 0;
        }
    }
}


// @ 0x006ad590
bool FUN_006ad590(char* a, bool flag)
{
    if (flag)
        return Registry_RegisterFree(a + 8, a);
    return Registry_UnregisterFree(a + 8, a);
}

// @ 0x006ad5c0
void FUN_006ad5c0()
{}

// @ 0x006ad7c0
void SP::FlushCache(int x)
{
    if (x == 0 || x == 1) {
        void* p = g_pRegistry;
        ((void(__thiscall*)(void*, int))VFN(0x28))(p, 0);
    } else if ((unsigned)(x - 3) <= 0xa) {
        ((cLRUCache*)(g_caches + (x - 3) * 0x150))->Clear();
    }
}

// @ 0x006ad800
void FUN_006ad800(int n)
{
    int c = n;
    if (c > 0) {
        do {
            void* p = g_pRegistry;
            ((void(__thiscall*)(void*, int))VFN(0x28))(p, 0);
            cLRUCache* q = (cLRUCache*)g_caches;
            do {
                q->Clear();
                q = (cLRUCache*)((char*)q + 0x150);
            } while ((int)q < (int)g_cachesEnd);
        } while (--c);
    }
}

// @ 0x006ad850
void FUN_006ad850(void* p)
{
    ((void(__thiscall*)(void*, int, void*, int))VFN(0x64))(p, 0, g_pRegistry, 0);
    g_pRegistry = 0;
    cLRUCache* q = (cLRUCache*)g_caches;
    do {
        q->Reset();
        q = (cLRUCache*)((char*)q + 0x150);
    } while ((int)q < (int)g_cachesEnd);
}

// @ 0x006ad890
void __fastcall FUN_006ad890(void* self, void* a)
{
    *(int*)((char*)self + 8) = 0;
    *(int*)((char*)self + 0xc) = 0;
    *(float*)((char*)self + 0x10) = 1.0f;
    *(float*)((char*)self + 0x14) = 2.0f;
    *(int*)((char*)self + 0x18) = 0;
    ((Sub140*)((char*)self + 0x1c))->Init(a);
    *(int*)((char*)self + 0xc) = 0;
    *(int*)((char*)self + 0x18) = 0;
    *(int*)((char*)self + 8) = 1;
    *(void**)((char*)self + 4) = &vtbl_154df28;
}

// @ 0x006ad910
void cLRUCache::Destroy(void** base, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        char* n = (char*)base[i];
        while (n) {
            char* cur = n;
            n = *(char**)(n + 0x3c);
            void* p = *(void**)(cur + 4);
            if (p && p != *(void**)(cur + 0x14))
                ea_dealloc(p);
            ea_dealloc(cur);
        }
        base[i] = 0;
    }
}

// @ 0x006ada20
void FUN_006ada20()
{}

// @ 0x006adb40
void FUN_006adb40()
{}

// @ 0x006adbf0
void __fastcall FUN_006adbf0(void* self, unsigned char flag)
{
    *(void**)self = &vtbl_14093cc;
    g_pRegistry = 0;
    ((KRSub*)((char*)self + 0xc))->Destroy();
    *(void**)self = &vtbl_13effb8;
    if (flag & 1)
        ea_zone_delete(self);
}

// @ 0x006adc60
void FUN_006adc60(int x, int a)
{
    if ((unsigned)(x - 3) <= 0xa)
        ((cLRUCache*)(g_caches + (x - 3) * 0x150))->Do(a);
}

// @ 0x006adc90
void __fastcall FUN_006adc90(void* self, void* arg)
{
    (void)self; (void)arg;
    // partial: zone_new(0x58) -> FUN_006adb40, publish to g_pRegistry, notify,
    // then FUN_006ada20(0x10/0x40/0x20) on three cache globals.
}

// @ 0x006add30
void __fastcall FUN_006add30(void* self, void* a)
{
    *(void**)((char*)self + 0x10) = (char*)self + 0x18;
    *(void**)((char*)self + 4) = (char*)self + 0x18;
    *(void**)self = (char*)self + 0x18;
    *(void**)((char*)self + 8) = (char*)self + 0x38;
    void* x = *(void**)a;
    void* y = *(void**)((char*)a + 4);
    ((Sub970*)self)->Do(x, y, a);
}

// @ 0x006adda0
void* __fastcall FUN_006adda0(void* a)
{
    void* n = ea_eastl_alloc(
        0x40, &vtbl_14093bc, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (n) {
        *(void**)n = *(void**)a;
        ((void(__fastcall*)(void*, void*))FUN_006add30)((char*)n + 4, (char*)a + 4);
    }
    *(int*)((char*)n + 0x3c) = 0;
    return n;
}

// @ 0x006adee0
void FUN_006adee0()
{}

// @ 0x006adfe0
void SP::AddRegistrationCallback(unsigned key, void* cb)
{
    RCVector* v = ((CallbackMap*)g_callbackMap)->operator[](&key);
    void** p = v->fill;
    if (p < v->cap) {
        v->fill = p + 1;
        if (p)
            *p = cb;
    } else {
        ((RCVectorOps*)v)->Grow(p, &cb);
    }
}
