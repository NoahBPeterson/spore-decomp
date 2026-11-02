// src/game/UTFSpore_Win32/_at_00990000.cpp -- migrated from slice(s) s00999110, s00997f50, s00996f10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00990000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "EA/Thread/Mutex.h"
#include "EA/UTFWinTools/RWTextureFactory.h"
#include "EA/UTFWinTools/SerCollection.h"
#include "EA/UTFWinTools/SerScope.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Allocator/StackAllocator.h"
#include <intrin.h>
#include <string.h>
#include <new>

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void* FUN_011e0744(void* dst, void* src, unsigned n);        // vector<bool>::DoInsertValue
extern "C" void* FUN_008de1a0(void);   // 0x8de1a0
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s00996f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void* FUN_011e0744(void* dst, void* src, unsigned n);        // vector<bool>::DoInsertValue
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
struct FrameSet {
    void* CreateFrame(void* src);                                         // 0x9973e0
    bool HandleLocationChange(int* p, void* a3, wchar_t* name, int flag); // 0x997730
    bool FindFrames(void* root, int id);                                  // 0x9979f0
    bool Bind(int** a1, int id, int* a3);                                 // 0x997bf0
};
struct VecPB {
    char pad[4];
    unsigned* mEnd;     // +4
    unsigned* mCap;     // +8
    __declspec(noinline) void push_back(unsigned* v);
    void DoInsertValue(unsigned* pos, unsigned* v);     // 0xa80dd0 (thiscall on the vector)
};
struct Obj33 {
    char pad[0x18];
    Obj33* ctor();                                 // 0x997b60
    void clear();                                  // 0x997ba0
    void* ScalarDtor(unsigned flags);              // 0x997cc0
    int  GetSupportedTypes(unsigned* out, unsigned n); // 0x997d40
    bool CanConvert(int a, int id);                // 0x997d80
    int  Release();                                // 0x997d90
    void* ctor2();                                 // 0x997f30
};
extern "C" void* FUN_008de1a0(void);   // 0x8de1a0
// ---- items of slice s00996f10 end

// ---- items of slice s00997f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d); // operator new
extern "C" void FUN_011e0744_(void* a, void* b, int c);
extern "C" const char g_mutexName_1446a78[];
extern "C" void __cdecl FUN_00921df0(unsigned* ms);    // EA::Thread::ThreadSleep
extern "C" void* __cdecl FUN_008de1a0_(void);          // singleton accessor
struct Misc34 {
    int  AsInterface(int iid);     // 0x998100
    void f98140();                 // 0x998140
    void f98f80(int* p);           // 0x998f80
    void f98fc0(void* o);          // 0x998fc0
};
struct Key3 { unsigned a, b, c; };
struct KV   { Key3 k; unsigned v; };
struct HNode { KV kv; HNode* next; };            // 0x14
struct HIter { HNode* node; HNode** bucket; };
struct false_type {};   // eastl::false_type (has_unique_keys_type of a multi-hashtable), passed by value as 1 byte
struct HRange { HNode* first; HNode** fb; HNode* last; HNode** lb; };
struct RehashRes { char need; unsigned n; };
struct HashPolicy {
    float maxLoad, growth; unsigned nextResize;
    void __thiscall GetRehash(RehashRes* out, unsigned bcount, unsigned ecount, int n);  // 0x921440
};
struct KeyHT {            // eastl::hashtable<Key, pair<Key,int>> (multi); member at SerAutoUpdate+0xc
    char alloc[4];
    HNode** buckets;      // +4
    unsigned bcount;      // +8
    unsigned count;       // +0xc
    HashPolicy policy;    // +0x10
    HRange* equal_range(HRange* out, const Key3* k);       // 0x998920
    HIter* insert(HIter* out, const KV* v, false_type);    // 0x9989d0 DoInsertValue(value, false_type)
    void __thiscall DoRehash(unsigned n);                  // 0x998870
    HIter* __thiscall find(HIter* out, const Key3* k);     // 0x833840
    void __thiscall erase(HIter* out, HIter pos);          // 0xb4f930
    void __thiscall DoFreeNodes(HNode** b, unsigned n);    // 0x7611f0
};
struct KeySet {           // eastl::hashtable<Key, ...> member at SerAutoUpdate+0x2c
    char alloc[4];
    HNode** buckets;
    unsigned bcount;
    unsigned count;
    HashPolicy policy;
    HIter* __thiscall insert(HIter* out, const Key3* k, char flag);   // 0x8dfcd0
    void __thiscall DoFreeNodes(HNode** b, unsigned n);               // 0x93dc70
};
struct Mutex {
    char s[0x20];
    void __thiscall Lock(const char* name);        // 0x9221b0
    void __thiscall Unlock();                      // 0x922270
    void __thiscall ctor(int a, int b);            // 0x9222a0
    void __thiscall dtor();                        // 0x922130
};
struct PtrVec {
    void** b; void** e; void** c;
    void __thiscall DoInsertValue(void** pos, void** v);   // 0xa80dd0
    void push_back(void* v)
    {
        void** p = e;
        if (p < c) {
            e = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(p, &v);
        }
    }
};
struct SerAutoUpdate {
    void*  vt0;            // +0
    void*  vt4;            // +4
    long   mRefCount;      // +8
    KeyHT  mFiles;         // +0xc
    char   pad0[0x2c - 0x0c - sizeof(KeyHT)];
    KeySet mChanged;       // +0x2c
    char   pad1[0x4c - 0x2c - sizeof(KeySet)];
    PtrVec mListeners;     // +0x4c
    char   pad2[0x60 - 0x4c - sizeof(PtrVec)];
    void*  mOwner;         // +0x60
    char   pad3[4];
    Mutex  mMutex;         // +0x68

    SerAutoUpdate* ctor(void* owner);                       // 0x998df0
    void dtor();                                            // 0x998eb0
    void RemoveEntry(Key3* k, int value);                   // 0x998ac0
    void AddEntry(Key3* k, int value);                      // 0x998b60
    void ProcessChanges();                                  // 0x998bd0
};
// ---- items of slice s00997f50 end

// ---- items of slice s00999110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern void* FUN_00925cb0();     // ICoreAllocator::GetDefaultAllocator
#pragma intrinsic(_InterlockedExchange)
typedef unsigned int uint;
struct IUnknown32 {
  virtual void AddRef();
  virtual void Release();
  virtual void v08();
  virtual void* Cast(uint type);
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
};
struct KeyFilter { virtual ~KeyFilter() {} };
struct HashSetU32 {                 // eastl::hash_set<uint> (nodes of 8 bytes)
  char alloc[4];
  void** mpBucketArray;             // +0x04 (in filter)
  uint  mnBucketCount;
  uint  mnElementCount;
  float mfMaxLoad, mfGrowth;
  uint  mnNextResize;
  void __thiscall DoFreeNodes(void** array, uint count) throw();         // 0x6b6570
  void* __thiscall DoInsertValue(void* out, const uint* v, char flag);   // 0x6758a0
  __forceinline ~HashSetU32() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) operator_delete(mpBucketArray);
  }
};
struct StringTableFilter : KeyFilter {
  HashSetU32 mTypes;   // +0x04
  __forceinline ~StringTableFilter() {}
  StringTableFilter() {
    mTypes.mnBucketCount = 1;
    mTypes.mpBucketArray = (void**)0x154df28;
    mTypes.mnElementCount = 0;
    mTypes.mfMaxLoad = 1.0f;
    mTypes.mfGrowth = 2.0f;
    mTypes.mnNextResize = 0;
  }
};
struct IAlloc { virtual void v0(); virtual void v4(); virtual void v8(); virtual void Free(void* p, uint n); };
struct ListNode { ListNode* next; ListNode* prev; };
struct ListNodeObj : ListNode { IUnknown32* obj; };
struct StringManMgr {
  int mRefCount;      // +4
  void* mpManager;    // +8
  void Open();
};
// ---- items of slice s00999110 end

// @ 0x00997b10
void VecPB::push_back(unsigned* v)
{
    unsigned* p = mEnd;
    if (p < mCap) {
        mEnd = p + 1;
        if (p != 0)
            *p = *v;
        return;
    }
    DoInsertValue(p, v);
}

// @ 0x00997b60
Obj33* Obj33::ctor()
{
    *(void**)((char*)this + 4) = (void*)0x13ef094;
    *(unsigned*)((char*)this + 8) = 0;
    *(void**)((char*)this + 0) = (void*)0x1446838;
    *(void**)((char*)this + 4) = (void*)0x1446834;
    *(unsigned*)((char*)this + 0xc) = 0;
    *(unsigned*)((char*)this + 0x10) = 0;
    *(unsigned*)((char*)this + 0x14) = 0;
    return this;
}

// @ 0x00997ba0
void Obj33::clear()
{
    unsigned* p = *(unsigned**)((char*)this + 0xc);
    unsigned* end = *(unsigned**)((char*)this + 0x10);
    for (; p != end; p++) {
        void* o = (void*)*p;
        if (o)
            (*(void(__thiscall**)(void*))((char*)*(void**)o + 4))(o);
    }
    unsigned* a = *(unsigned**)((char*)this + 0xc);
    unsigned* b = *(unsigned**)((char*)this + 0x10);
    FUN_011e0744(a, b, 0);
    int n = (int)((char*)b - (char*)a) >> 2;
    n = -n;
    n = n + n;
    n = n + n;
    *(int*)((char*)this + 0x10) = (int)b + n;
}

// @ 0x00997bf0
bool FrameSet::Bind(int** a1, int id, int* a3)
{
    char* self = (char*)this;
    if (id == 0x3ff) {
        short* hdr = (short*)a1[0];
        if (*hdr == 0x13 && *(int*)(hdr + 2) == (int)0xf074e1c8) {
            void* o = FUN_008de1a0();
            int r = VF(o, 0x48, int(__thiscall*)(void*, int, int))(o, a3[1], 0x19aef76);
            if (r != 0) {
                struct Req { int a, b, c; };
                Req req = *(Req*)a3;
                req.b = 0x19aef76;
                int out = 0;
                char ok = VF(o, 0xc, char(__thiscall*)(void*, int*, int*, int, int, int, Req*))(o, a3, &out, 0, 0, r, &req);
                if (ok) {
                    *a1[1] = out;
                    unsigned v = (unsigned)out;
                    ((VecPB*)(self + 0xc))->push_back(&v);
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00997cc0
void* Obj33::ScalarDtor(unsigned flags)
{
    *(void**)((char*)this + 0) = (void*)0x1446838;
    *(void**)((char*)this + 4) = (void*)0x1446834;
    clear();
    int p = *(int*)((char*)this + 0xc);
    if (p != 0 && *(int*)(p - 4) != 0)
        FUN_00f47380((void*)p);
    *(void**)((char*)this + 4) = (void*)0x13ef094;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    if (flags & 1)
        FUN_00f47380(this);
    return this;
}

// @ 0x00998920
HRange* KeyHT::equal_range(HRange* out, const Key3* k)
{
    unsigned a = k->a;
    unsigned c = k->c;
    HNode** bk = buckets + (a ^ c) % bcount;
    HNode* p = *bk;
    for (;;) {
        if (p == 0) {
            HNode** e = buckets + bcount;
            HNode* en = *e;
            out->first = en; out->fb = e; out->last = en; out->lb = e;
            return out;
        }
        if (a == p->kv.k.a && k->b == p->kv.k.b && c == p->kv.k.c)
            break;
        p = p->next;
    }
    HNode* q = p->next;
    if (q != 0) {
        while (a == q->kv.k.a && k->b == q->kv.k.b) {
            if (c != q->kv.k.c)
                break;
            q = q->next;
            if (q == 0)
                break;
        }
    }
    HNode** qb = bk;
    if (q == 0) {
        qb = bk + 1;
        while (*qb == 0)
            qb++;
        q = *qb;
    }
    out->fb = bk;
    out->first = p;
    out->last = q;
    out->lb = qb;
    return out;
}

// @ 0x009989d0
HIter* KeyHT::insert(HIter* out, const KV* v, false_type)
{
    RehashRes rr;
    policy.GetRehash(&rr, bcount, count, 1);
    if (rr.need)
        DoRehash(rr.n);
    unsigned idx = (v->k.a ^ v->k.c) % bcount;
    HNode* n = (HNode*)FUN_00f473a0(0x14, "EASTL", 0, 0, (int)
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (n)
        n->kv = *v;
    n->next = 0;
    HNode* head = buckets[idx];
    for (HNode* p = head; ; p = p->next) {
        if (p == 0) {
            n->next = head;
            buckets[idx] = n;
            break;
        }
        if (v->k.a == p->kv.k.a && v->k.b == p->kv.k.b && v->k.c == p->kv.k.c) {
            n->next = p->next;
            p->next = n;
            break;
        }
    }
    count++;
    out->node = n;
    out->bucket = buckets + idx;
    return out;
}

// @ 0x00998ac0
void SerAutoUpdate::RemoveEntry(Key3* k, int value)
{
    mMutex.Lock(g_mutexName_1446a78);
    HRange r;
    mFiles.equal_range(&r, k);
    HNode* n = r.first;
    HNode** bk = r.fb;
    HNode* end = r.last;
    if (n != end) {
        while (n->kv.v != (unsigned)value) {
            n = n->next;
            while (n == 0) {
                n = *++bk;
            }
            if (n == end) {
                mMutex.Unlock();
                return;
            }
        }
        HIter pos;
        pos.node = n; pos.bucket = bk;
        HIter res;
        mFiles.erase(&res, pos);
    }
    mMutex.Unlock();
}

// @ 0x00998b60
void SerAutoUpdate::AddEntry(Key3* k, int value)
{
    mMutex.Lock(g_mutexName_1446a78);
    KV kv;
    kv.k = *k;
    kv.v = (unsigned)value;
    HIter out;
    mFiles.insert(&out, &kv, false_type());
    mMutex.Unlock();
}

// @ 0x00998bd0
void SerAutoUpdate::ProcessChanges()
{
    void** first = mListeners.b;
    void** last = mListeners.e;
    FUN_011e0744_(first, last, (int)((char*)mListeners.e - (char*)last));
    mListeners.e = mListeners.e - (last - first);

    if (mChanged.count != 0) {
        mMutex.Lock(g_mutexName_1446a78);
        HNode** bk = mChanged.buckets;
        HNode* end = bk[mChanged.bcount];
        HNode* n = *bk;
        HNode** nb = bk;
        if (n == 0) {
            nb = bk + 1;
            while (*nb == 0)
                nb++;
            n = *nb;
        }
        while (n != end) {
            HRange r;
            mFiles.equal_range(&r, (const Key3*)n);
            HNode* m = r.first;
            HNode** mb = r.fb;
            if (m != r.last) {
                do {
                    mListeners.push_back((void*)m->kv.v);
                    m = m->next;
                    if (m == 0) {
                        do { m = *++mb; } while (m == 0);
                    }
                } while (m != r.last);
            }
            n = (HNode*)n->kv.v;     // set-node next link at +0xc
            while (n == 0) {
                nb++;
                n = *nb;
            }
        }
        mChanged.DoFreeNodes(mChanged.buckets, mChanged.bcount);
        mChanged.count = 0;
        mMutex.Unlock();
    }
    void** p = mListeners.b;
    if (p != mListeners.e) {
        void** q = mListeners.e;
        for (; p != q; p++) {
            void* o = *p;
            VF(o, 0, void(__thiscall*)(void*))(o);
        }
    }
}

// @ 0x00998d30
void __cdecl ReloadChangedLayouts(void* iface)
{
    unsigned ms = 100;
    FUN_00921df0(&ms);
    SerAutoUpdate* s = 0;
    if (iface)
        s = (SerAutoUpdate*)VF(iface, 0xc, void*(__thiscall*)(void*, unsigned))(iface, 0x2fbf2058);
    s->ProcessChanges();
}

// @ 0x00998d70
void __cdecl OnResourceChanged(int a, Key3* key, SerAutoUpdate* self)
{
    (void)a;
    self->mMutex.Lock(g_mutexName_1446a78);
    HNode* endNode = self->mFiles.buckets[self->mFiles.bcount];
    HIter tmp;
    HIter* f = self->mFiles.find(&tmp, key);
    if (f->node != endNode) {
        if (self->mChanged.count == 0) {
            void* o = self->mOwner;
            VF(o, 0x1c, void(__thiscall*)(void*, void*, void*))(o, (void*)ReloadChangedLayouts, self);
        }
        char flag = 0;
        self->mChanged.insert(&tmp, key, flag);
    }
    self->mMutex.Unlock();
}

// @ 0x00998df0
SerAutoUpdate* SerAutoUpdate::ctor(void* owner)
{
    *(void**)((char*)this + 0) = (void*)0x13fa72c;
    *(void**)((char*)this + 4) = (void*)0x13ef094;
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    *(void**)((char*)this + 0) = (void*)0x1446a90;
    *(void**)((char*)this + 4) = (void*)0x1446a8c;
    mFiles.policy.maxLoad = 1.0f;
    mFiles.policy.growth = 2.0f;
    mFiles.bcount = 1;
    mFiles.count = 0;
    mFiles.policy.nextResize = 0;
    mFiles.buckets = (HNode**)0x154df28;
    mChanged.policy.maxLoad = 1.0f;
    mChanged.policy.growth = 2.0f;
    mChanged.bcount = 1;
    mChanged.buckets = (HNode**)0x154df28;
    mChanged.count = 0;
    mChanged.policy.nextResize = 0;
    mListeners.b = 0;
    mListeners.e = 0;
    mListeners.c = 0;
    mOwner = owner;
    mMutex.ctor(0, 1);
    void* mgr = FUN_008de1a0_();
    if (mgr)
        VF(mgr, 0x40, void(__thiscall*)(void*, int, void*, void*, int, int))(mgr, 1, (void*)OnResourceChanged, this, 0, 0);
    return this;
}

// @ 0x00998eb0
void SerAutoUpdate::dtor()
{
    mMutex.dtor();
    void** p = mListeners.b;
    if (p && ((int*)p)[-1])
        FUN_00f47380(p);
    mChanged.DoFreeNodes(mChanged.buckets, mChanged.bcount);
    mChanged.count = 0;
    if (mChanged.bcount > 1)
        FUN_00f47380(mChanged.buckets);
    mFiles.DoFreeNodes(mFiles.buckets, mFiles.bcount);
    mFiles.count = 0;
    if (mFiles.bcount > 1)
        FUN_00f47380(mFiles.buckets);
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    *(void**)((char*)this + 4) = (void*)0x13ef094;
}

// @ 0x00998f80
void Misc34::f98f80(int* p)
{
    char* self = (char*)this;
    *(int*)(self + 0xc) = p[0];
    *(int*)(self + 0x10) = p[1];
    *(int*)(self + 0x14) = p[2];
    (*(void(__thiscall**)(char*))((char*)*(void**)self + 0x14))(self);
}

// @ 0x00999930
void StringManMgr::Open()
{
  ListNode list1;
  list1.next = &list1; list1.prev = &list1;
  StringTableFilter filter;
  VF(mpManager, 0x4c, void(__thiscall*)(void*, ListNode*, int))(mpManager, &list1, -1);
  for (ListNode* n = list1.next; n != &list1; n = n->next) {
    IUnknown32* o = ((ListNodeObj*)n)->obj;
    if (VF(o, 0x18, int(__thiscall*)(void*))(o) == (int)0x8f6ad1c8) {
      uint types[16];
      uint cnt = VF(o, 0x2c, uint(__thiscall*)(void*, uint*, uint))(o, types, 0x10);
      for (uint i = 0; i < cnt; i++) {
        uint v = types[i];
        char flag = 0;
        char out[8];
        filter.mTypes.DoInsertValue(out, &v, flag);
      }
    }
  }
  struct { ListNode head; IAlloc* alloc; uint count; } list2;
  list2.head.next = &list2.head; list2.head.prev = &list2.head;
  list2.alloc = (IAlloc*)FUN_00925cb0();
  list2.count = 0;
  VF(mpManager, 0x5c, void(__thiscall*)(void*, ListNode*, int))(mpManager, &list2.head, 0);
  for (ListNode* w = list2.head.next; w != &list2.head; w = w->next) { }
  for (ListNode* n = list2.head.next; n != &list2.head; ) {
    ListNode* nx = n->next;
    list2.alloc->Free(n, 0xc);
    n = nx;
  }
  for (ListNode* n = list1.next; n != &list1; ) {
    ListNode* nx = n->next;
    operator_delete(n);
    n = nx;
  }
}
