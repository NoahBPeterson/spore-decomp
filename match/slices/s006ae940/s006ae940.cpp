// Slice s006ae940: SP::cAsyncResourceManager and related async resource helpers.
// Mostly /O2 with old-style EH; a few leaf helpers match directly.
#include "../../include/types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// globals (undefined externs -> relocations)
// ---------------------------------------------------------------------------
extern void* g_pRegistry;   // 0x1603118

// ---------------------------------------------------------------------------
// 006af5c0  void FUN_006af5c0(void* p)
// ---------------------------------------------------------------------------
void __stdcall FUN_006af5c0(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[9])(p);
}

// ---------------------------------------------------------------------------
// 006af940  bool FUN_006af940(int self)    (try-lock refcount addref)
// ---------------------------------------------------------------------------
bool __fastcall FUN_006af940(int self)
{
    volatile long* rc = (volatile long*)(self + 8);
    if (_InterlockedExchangeAdd(rc, 0) != 0) {
        _InterlockedExchangeAdd(rc, 1);
        return true;
    }
    return false;
}

// ===========================================================================
// remaining functions
// ===========================================================================
extern void* vtbl_14094d0;
extern void* vtbl_14094cc;
extern void* vtbl_13eb938;
extern void* vtbl_13ef094;
extern void* vtbl_14095f4;
extern void* vtbl_13effb8;
extern void* vtbl_13f1ab0;
extern void* vtbl_13fa72c;
extern void* vtbl_1408500;
extern void* vtbl_14084f0;
extern void* vtbl_1409630;
extern void* vtbl_140961c;
extern "C" void IO_WriteUint32(void* stream, void* src, int n, int flags); // 0x93aa70
extern "C" void FUN_0093ab10(void* stream, void* src, int n, int flags);   // 0x93ab10

struct XRBNode { XRBNode* left; XRBNode* right; };
struct XRBTree { void DoNukeSubtree(void* n); };
struct Mutex2 {                    // EA::Thread::Mutex
    void dtor();               // 0x922130
    void Lock(void* name);     // 0x9221b0
    void Unlock();             // 0x922270
};

// ---------------------------------------------------------------------------
// 006aebd0  SP::cAsyncResourceManager::~cAsyncResourceManager
// ---------------------------------------------------------------------------
// @ 0x006aebd0
void __fastcall FUN_006aebd0(void* self)
{
    *(void**)self = &vtbl_14094d0;
    *(void**)((char*)self + 4) = &vtbl_14094cc;
    void* anchor = *(void**)((char*)self + 0x4c);
    ((XRBTree*)((char*)self + 0x40))->DoNukeSubtree(anchor);
    ((Mutex2*)((char*)self + 0x10))->dtor();
    *(void**)((char*)self + 4) = &vtbl_13ef094;
    *(void**)self = &vtbl_13eb938;
}

// ---------------------------------------------------------------------------
// 006aedc0  SP::cAsyncResourceManager::cAsyncResourceManager
// ---------------------------------------------------------------------------
// @ 0x006aedc0
void __fastcall FUN_006aedc0(void* self)
{
    *(void**)self = &vtbl_13fa72c;
    *(void**)((char*)self + 4) = &vtbl_13ef094;
    *(void**)((char*)self + 8) = 0;
    *(void**)self = &vtbl_14094d0;
    *(void**)((char*)self + 4) = &vtbl_14094cc;
    ((Mutex2*)((char*)self + 0x10))->dtor();  // real: Mutex ctor
}

// ---------------------------------------------------------------------------
// 006af8a0  dtor
// ---------------------------------------------------------------------------
// @ 0x006af8a0
void __fastcall FUN_006af8a0(void* self)
{
    *(void**)self = &vtbl_14095f4;
    void* p = *(void**)((char*)self + 0x10);
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    void* q = *(void**)((char*)self + 0xc);
    if (q) {
        void* r = (char*)q + 4;
        ((void(__thiscall*)(void*))(*(void***)r)[1])(r);
    }
    *(void**)self = &vtbl_13effb8;
}

// ---------------------------------------------------------------------------
// 006af960  resource handle ctor  (__thiscall, 2 stack args)
// ---------------------------------------------------------------------------
struct C_006af960 {
    void* mpVtbl0;     // +0x00
    void* mpVtbl1;     // +0x04
    long  mRefs;       // +0x08
    void* mpOwner;     // +0x0c
    void* mpPayload;   // +0x10
    void* mpExtra;     // +0x14
    C_006af960* ctor(void* a, void* b);
};

// @ 0x006af960
C_006af960* C_006af960::ctor(void* a, void* b)
{
    mpVtbl1 = (void*)&vtbl_13f1ab0;
    mpVtbl0 = (void*)&vtbl_1408500;
    mpVtbl1 = (void*)&vtbl_14084f0;
    _InterlockedExchange(&mRefs, 0);
    mpVtbl0 = (void*)&vtbl_1409630;
    mpVtbl1 = (void*)&vtbl_140961c;
    mpOwner = a;
    if (a) {
        void* r = (char*)a + 4;
        ((void(__thiscall*)(void*))(*(void***)r)[0])(r);
    }
    mpPayload = b;
    if (b)
        ((void(__thiscall*)(void*))(*(void***)b)[0])(b);
    mpExtra = 0;
    return this;
}

// ---------------------------------------------------------------------------
// 006af670  serialize a vector of 0x10-byte records  (__thiscall, 1 arg)
// ---------------------------------------------------------------------------
struct C_006af670 {
    void* mpVtbl0;     // +0x00
    void* mpVtbl1;     // +0x04
    int   mFlags;      // +0x08
    int   mKind;       // +0x0c
    char* mpBegin;     // +0x10
    char* mpEnd;       // +0x14
    void serialize(void* stream);
};

// @ 0x006af670
void C_006af670::serialize(void* stream)
{
    int header[2];
    header[0] = mFlags;
    header[1] = mKind;
    FUN_0093ab10(stream, header, 1, 0);
    int count = (int)(mpEnd - mpBegin) >> 4;
    IO_WriteUint32(stream, &count, 1, 0);
    for (char* p = mpBegin; p != mpEnd; p += 0x10) {
        int v8 = *(int*)(p + 8);
        IO_WriteUint32(stream, &v8, 1, 0);
        int v4 = *(int*)(p + 4);
        IO_WriteUint32(stream, &v4, 1, 0);
        int vc = *(int*)(p + 0xc);
        IO_WriteUint32(stream, &vc, 1, 0);
    }
}

// ---------------------------------------------------------------------------
// 006af5d0  bool V5d0::f(bool a, void* b, bool c)
// ---------------------------------------------------------------------------
struct V5d0 {
    char pad[0x14];
    void* m14;              // +0x14
    bool f(bool a, void* b, bool c);
};

// @ 0x006af5d0
bool V5d0::f(bool a, void* b, bool c)
{
    bool result = false;
    if (a) {
        void* x = m14;
        if (x && b != x)
            ((bool(__thiscall*)(void*, int, void*, bool))(*(void***)this)[17])(this, 0, x, c);
        if (b) {
            if (c) {
                m14 = b;
                return true;
            }
            return ((bool(__thiscall*)(void*, int, void*, int))(*(void***)b)[20])(b, 1, this, 0);
        }
    } else {
        if (b) {
            if (b != m14)
                return false;
            if (c) {
                m14 = 0;
                return true;
            }
            void* old = m14;
            return ((bool(__thiscall*)(void*, int, void*, int))(*(void***)old)[20])(old, 0, this, 0);
        }
    }
    return result;
}

// ===========================================================================
// async request tree / job helpers
// ===========================================================================
extern void* vtbl_1409478;   // 0x1409478
extern void* vtbl_1409474;   // 0x1409474
extern void* vtbl_13effa8;   // 0x13effa8
extern void* vtbl_1409488;   // 0x1409488

// map key: compared as k0, then k2, then k1 (unsigned)
struct AsyncKey { unsigned k0; unsigned k1; unsigned k2; };   // 12 bytes
struct AsyncValue { AsyncKey key; void* obj; };              // 16 bytes (map value)
struct AsyncNode {                    // 0x20 bytes
    AsyncNode* pLeft;      // +0x00
    AsyncNode* pRight;     // +0x04
    AsyncNode* pParent;    // +0x08
    unsigned   mColor;     // +0x0c
    unsigned   k0;         // +0x10
    unsigned   k1;         // +0x14
    unsigned   k2;         // +0x18
    void*      mpValue;    // +0x1c
};
struct AsyncTree {
    unsigned   mUnk00;      // +0x00
    AsyncNode* mpRoot;      // +0x04  (header; its address is the end sentinel)
    AsyncNode* mpCurrent;   // +0x08
    unsigned   mUnk0c[2];   // +0x0c
    unsigned   mCount;      // +0x14
    AsyncNode* mpFree;      // +0x18
    unsigned   mUnk1c;      // +0x1c
    void*      mpPoolBegin; // +0x20
    void*      mpPoolEnd;   // +0x24
};

static inline bool KeyLess3(unsigned a0, unsigned a1, unsigned a2,
                            unsigned b0, unsigned b1, unsigned b2)
{
    if (a0 != b0) return a0 < b0;
    if (a2 != b2) return a2 < b2;
    return a1 < b1;
}

// --- callees (hex embedded in the name so relocations resolve) -------------
extern "C" void* F_921580(void*);                                  // 0x921580 RBTreeIncrement
extern "C" void  F_921880(void*, void*);                           // 0x921880 RBTreeErase
extern "C" void  F_9216a0(void*, void*, void*, int);               // 0x9216a0 RBTreeInsert
extern "C" void  F_f47380(void*);                                  // 0xf47380 operator delete
extern "C" void* F_f473a0(int, const char*, int, int, int, int);   // 0xf473a0 eastl/EA alloc
extern "C" void* F_926020(int, const char*, int, int, int, int);   // 0x926020 zone new
extern "C" void* F_68f4d0(void);                                   // 0x68f4d0 job manager
extern "C" void* F_67de70(void*, void*);                           // 0x67de70 leaf accessor
extern "C" bool  F_6ae2f0(char*, void*);                           // 0x6ae2f0 request-complete hook
extern "C" bool  F_93a780(void*, void*, int, int);                 // 0x93a780 EA::IO::ReadInt32
extern "C" void  F_6aec50(void);                                   // 0x6aec50 continuation
extern "C" void  F_6af140(void);                                   // 0x6af140 job callback
extern void      __fastcall F_68f950(void* self, int);             // 0x68f950 AddRef
extern void      __fastcall F_690120(void* self, int);             // 0x690120 Release
extern int       __fastcall F_692400(void* self, int, int);        // 0x692400 Cancel(bool)
extern void      __fastcall F_68f9b0(void* self, int, void*);      // 0x68f9b0 AddDependency
extern int       __fastcall F_6909b0(void* self, int);             // 0x6909b0 GetStatus
extern void*     __fastcall F_6ae510(void* self, int, void*);      // 0x6ae510 Resource::Async ctor
extern void      __fastcall F_93bb40(void* self, int, int, float); // 0x93bb40 SetOption
extern void*     __fastcall F_93ba70(void* self, int);             // 0x93ba70 GetData
extern void*     __fastcall F_8dc5e0(void* self, int);             // 0x8dc5e0 PFRecordRead::GetBuffer
extern void      __fastcall F_6ae2a0(void* self, int, void*);      // 0x6ae2a0 AutoRefCount operator=
extern void*     __fastcall F_93bca0(void* self, int, void*, void*);// 0x93bca0 ctor
extern void*     __fastcall F_93c270(void* self, int, void*, void*, const char*); // 0x93c270 ctor
extern void*     __fastcall F_c7f560(void* self, int, void*, void*);// 0xc7f560 lower_bound
extern void*     __fastcall F_6ae660(void* self, int, void*);      // 0x6ae660 allocate node
extern void      __fastcall F_6ae700(void* self, int, void*, void*, void*, int); // 0x6ae700 hint insert
extern void      __fastcall F_6ae770(void* self, int, void*, void*, int);        // 0x6ae770 lower bound
extern void      __fastcall F_6ae880(void* self, int, void*, void*);              // 0x6ae880 complete
extern bool      __fastcall F_68f9f0(void* self, int, void*, void*);              // 0x68f9f0 Continuation

// forward declarations of the functions defined below (bind by hex in the name)
AsyncNode** __fastcall FUN_006aec60(void* self, int, AsyncNode** out, AsyncNode* hint,
                                    AsyncKey* key, int flag);
void**      __fastcall FUN_006af080(void* self, int, AsyncKey* key);
char        __fastcall FUN_006af150(void* self, int, AsyncKey* key, void** out, void* ctorArg);

// ---------------------------------------------------------------------------
// 006ae940  drain async requests whose jobs have finished
// ---------------------------------------------------------------------------
// @ 0x006ae940
void __fastcall FUN_006ae940(void* self)
{
    Mutex2*    mutex = (Mutex2*)((char*)self + 0x10);
    AsyncTree* tree  = (AsyncTree*)((char*)self + 0x40);
    bool empty;
    do {
        void* job = 0;
        mutex->Lock((void*)0x1409448);
        empty = (tree->mCount == 0);
        if (!empty) {
            void* value = tree->mpCurrent->mpValue;
            void* j = *(void**)((char*)value + 0x0c);      // AsyncRequest::mpAsync
            if (j) {
                F_68f950(j, 0);
                job = j;
            }
            AsyncNode* node = tree->mpCurrent;
            tree->mCount = tree->mCount - 1;
            F_921580(node);
            F_921880(node, &tree->mpRoot);
            void* v = node->mpValue;
            if (v)
                ((void(__fastcall*)(void*, int))(*(void***)v)[1])(v, 0);
            if (node < (AsyncNode*)tree->mpPoolBegin || node >= (AsyncNode*)tree->mpPoolEnd)
                F_f47380(node);
            else {
                node->pLeft = tree->mpFree;
                tree->mpFree = node;
            }
        }
        mutex->Unlock();
        if (job) F_692400(job, 0, 1);          // Cancel(true)
        if (job) F_690120(job, 0);             // Release()
    } while (!empty);
}

// ---------------------------------------------------------------------------
// 006aea90  job completion callback (bool __thiscall(AsyncRequest*, void*))
// ---------------------------------------------------------------------------
// @ 0x006aea90
char __fastcall FUN_006aea90(void* self, int, void* param_2)
{
    char  ok    = 0;
    void* local = 0;                                  // AutoRef<> result object
    void* data  = *(void**)((char*)self + 0x10);      // AsyncRequest::mpData
    if (*(void**)((char*)data + 0x0c) != 0) {         // AsyncData::mpStream
        void* async = *(void**)((char*)self + 0x0c);  // AsyncRequest::mpAsync
        void* arg   = *(void**)((char*)self + 0x14);
        int   k1    = *(int*)((char*)self + 0x1c);
        ok = ((char(__fastcall*)(void*, int, void*, void*, void*, int))
                  (*(void***)async)[7])(async, 0, data, &local, arg, k1);
    }
    void* d2  = *(void**)((char*)self + 0x10);
    void* obj = *(void**)((char*)d2 + 8);             // AsyncData::mpObject
    ((void(__fastcall*)(void*, int))(*(void***)obj)[9])(obj, 0);
    if (obj) {
        d2 = *(void**)((char*)self + 0x10);
        *(void**)((char*)d2 + 8) = 0;
        ((void(__fastcall*)(void*, int))(*(void***)obj)[2])(obj, 0);
    }
    void* d3 = *(void**)((char*)self + 0x10);
    if (d3) {
        *(void**)((char*)self + 0x10) = 0;
        ((void(__fastcall*)(void*, int))(*(void***)d3)[2])(d3, 0);
    }
    if (ok) {
        if (*(char*)((char*)self + 0x24) == 0) {      // AsyncRequest::mFlag
            *(int*)((char*)local + 8)  = *(int*)((char*)self + 0x18);
            *(int*)((char*)local + 0xc) = *(int*)((char*)self + 0x1c);
            *(int*)((char*)local + 0x10) = *(int*)((char*)self + 0x20);
        } else {
            void* k = (char*)self + 0x18;
            void* r = F_67de70(k, local);
            F_6ae880(r, 0, k, local);
        }
        char res = F_6ae2f0((char*)param_2, local);
        if (local)
            ((void(__fastcall*)(void*, int))(*(void***)local)[1])(local, 0);
        return res;
    }
    if (*(char*)((char*)self + 0x24) != 0) {
        void* k = (char*)self + 0x18;
        void* r = F_67de70(k, 0);
        F_6ae880(r, 0, k, 0);
    }
    if (local)
        ((void(__fastcall*)(void*, int))(*(void***)local)[1])(local, 0);
    return 0;
}

// ---------------------------------------------------------------------------
// 006aec60  fixed_map emplace/insert-hint  (AsyncNode** __thiscall(tree, out, hint, key, flag))
// ---------------------------------------------------------------------------
// @ 0x006aec60
AsyncNode** __fastcall FUN_006aec60(void* self, int, AsyncNode** out, AsyncNode* hint,
                                    AsyncKey* key, int flag)
{
    AsyncTree* tree = (AsyncTree*)self;
    AsyncNode* root = tree->mpRoot;
    if (hint == root || hint == (AsyncNode*)&tree->mpRoot) {
        if (tree->mCount != 0 &&
            KeyLess3(root->k0, root->k1, root->k2, key->k0, key->k1, key->k2)) {
            F_6ae700(tree, 0, out, root, key, 0);
            return out;
        }
        AsyncNode* it;
        F_6ae770(tree, 0, &it, key, (int)((unsigned)key & 0xFFFFFF00u));
        *out = it;
        return out;
    }
    AsyncNode* next = (AsyncNode*)F_921580(hint);
    if (KeyLess3(hint->k0, hint->k1, hint->k2, key->k0, key->k1, key->k2) &&
        KeyLess3(key->k0, key->k1, key->k2, next->k0, next->k1, next->k2)) {
        if (hint->pLeft != 0) {
            AsyncNode* n = (AsyncNode*)F_6ae660(tree, 0, key);
            F_9216a0(n, next, &tree->mpRoot, 0);
            tree->mCount = tree->mCount + 1;
            *out = n;
            return out;
        }
        F_6ae700(tree, 0, out, hint, key, 0);
        return out;
    }
    AsyncNode* it;
    F_6ae770(tree, 0, &it, key, (int)((unsigned)key & 0xFFFFFF00u));
    *out = it;
    return out;
}

// ---------------------------------------------------------------------------
// 006aee60  build the memory stream for a finished async request
// ---------------------------------------------------------------------------
// @ 0x006aee60
char __fastcall FUN_006aee60(void* self, int, void* job)
{
    void* local = 0;                                  // AutoRef<> the shared buffer object
    void* data  = *(void**)((char*)self + 0x10);
    void* obj   = *(void**)((char*)data + 8);         // AsyncData::mpObject
    obj = ((void*(__fastcall*)(void*, int))(*(void***)obj)[6])(obj, 0);   // object payload
    void* arg = ((void*(__fastcall*)(void*, int))(*(void***)obj)[7])(obj, 0);
    unsigned type = ((unsigned(__fastcall*)(void*, int))(*(void***)obj)[3])(obj, 0);
    if (type == 0x347223d2u)
        F_6ae2a0(&local, 0, *(void**)((char*)obj + 4));
    if (local == 0) {
        type = ((unsigned(__fastcall*)(void*, int))(*(void***)obj)[3])(obj, 0);
        if (type == 0x12e4a891u) {
            void* b = F_8dc5e0((char*)obj - 0x20, 0);
            F_6ae2a0(&local, 0, b);
        }
        if (local == 0) {
            if (((unsigned(__fastcall*)(void*, int))(*(void***)obj)[5])(obj, 0) == 0) {
                void* mem = F_926020(0x18, "App/AsyncRequest/SharedPointer", 0, 0, 0, 0);
                void* made = mem ? F_93bca0(mem, 0, arg, (void*)"App/AsyncRequest/SharedPointer") : 0;
                F_6ae2a0(&local, 0, made);
                if (arg != 0) {
                    void* p = *(void**)((char*)local + 0x10);
                    if (((void*(__fastcall*)(void*, int, void*, void*))
                             (*(void***)obj)[12])(obj, 0, p, arg) != arg)
                        F_6ae2a0(&local, 0, 0);
                }
            }
        }
    }
    if (local != 0) {
        void* mem2 = F_f473a0(0x24, "App/AsyncRequest/MemoryStream", 0, 0, 0, 0);
        void* s = mem2 ? F_93c270(mem2, 0, local, arg, "App/SimpleAsync/StreamToMemory") : 0;
        void* d = *(void**)((char*)self + 0x10);
        void* old = *(void**)((char*)d + 0x0c);       // AsyncData::mpStream
        if (s != old) {
            if (s)
                ((void(__fastcall*)(void*, int))(*(void***)s)[1])(s, 0);
            *(void**)((char*)d + 0x0c) = s;
            if (old)
                ((void(__fastcall*)(void*, int))(*(void***)old)[2])(old, 0);
        }
        void* stream = *(void**)((char*)self + 0x10);
        stream = *(void**)((char*)stream + 0x0c);
        F_93bb40(stream, 0, 1, 0.0f);
        stream = *(void**)((char*)self + 0x10);
        stream = *(void**)((char*)stream + 0x0c);
        F_93bb40(stream, 0, 4, 1.0f);
    }
    *(int*)((char*)job + 0x18) = 1;                   // cJob::mThreadAffinity
    char r = F_68f9f0(job, 0, (void*)&F_6aec50, self) ? 1 : 0;
    if (local) {
        volatile long* rc = (volatile long*)((char*)local + 8);
        long n = _InterlockedExchangeAdd(rc, -1);
        if (n == 1) {
            _InterlockedExchange(rc, 1);
            void* recv = (char*)local + 4;
            if (*(void**)recv)
                (*(void(__fastcall**)(void*, int))(*(void***)recv))(recv, 1);
        }
    }
    return r;
}

// ---------------------------------------------------------------------------
// 006af080  fixed_map find-or-emplace, returns pointer to the mapped value
// ---------------------------------------------------------------------------
// @ 0x006af080
void** __fastcall FUN_006af080(void* self, int, AsyncKey* key)
{
    AsyncNode* it;
    F_c7f560(self, 0, &it, key);
    AsyncNode* node = it;
    if (it == (AsyncNode*)((char*)self + 4) ||
        KeyLess3(key->k0, key->k1, key->k2, it->k0, it->k1, it->k2)) {
        AsyncValue kv;
        kv.key = *key;
        kv.obj = 0;
        FUN_006aec60(self, 0, &node, it, (AsyncKey*)&kv, (int)((unsigned)it & 0xFFFFFF00u));
    }
    return (void**)((char*)node + 0x1c);
}

// ---------------------------------------------------------------------------
// 006af150  cAsyncResourceManager::AllocateRequest
// ---------------------------------------------------------------------------
// @ 0x006af150
char __fastcall FUN_006af150(void* self, int, AsyncKey* key, void** out, void* ctorArg)
{
    Mutex2* mutex = (Mutex2*)((char*)self + 0x10);
    mutex->Lock((void*)0x1409448);
    void* obj = 0;
    void* mem = F_f473a0(0x10, "Resource/Async", 0, 0, 0, 0);
    if (mem) obj = F_6ae510(mem, 0, ctorArg);
    if (obj)
        ((void(__fastcall*)(void*, int))(*(void***)obj)[0])(obj, 0);      // AddRef
    void* temp = obj;
    void** slot = (void**)FUN_006af080((char*)self + 0x40, 0, key);
    void* old = *slot;
    if (obj != old) {
        if (obj)
            ((void(__fastcall*)(void*, int))(*(void***)obj)[0])(obj, 0);
        *slot = obj;
        if (old)
            ((void(__fastcall*)(void*, int))(*(void***)old)[1])(old, 0);
    }
    if (out) {
        temp = 0;
        *out = obj;
    }
    if (temp)
        ((void(__fastcall*)(void*, int))(*(void***)temp)[1])(temp, 0);
    mutex->Unlock();
    return 1;
}

// ---------------------------------------------------------------------------
// 006af260  submit a large async request (7 stack args, __stdcall)
// ---------------------------------------------------------------------------
struct JobBuffer {              // 0x10
    void* mpVtbl0;   // +0x00
    long  mRefs;     // +0x04
    void* mpMgr;     // +0x08
    void* mpStream;  // +0x0c
};
struct JobData {                // 0x28
    void*       mpVtbl0;    // +0x00
    void*       mpVtbl1;    // +0x04
    long        mRefs;      // +0x08
    void*       mpJob;      // +0x0c
    JobBuffer*  mpBuffer;   // +0x10
    void*       m14;        // +0x14
    unsigned    k0;         // +0x18
    unsigned    k1;         // +0x1c
    unsigned    k2;         // +0x20
    char        mFlag;      // +0x24
};
struct cJob {
    void* mpCallback;       // +0x00
    void* mpCallbackData;   // +0x04
    void* mpExtraObject;    // +0x08
    void* mpDebugName;      // +0x0c
    int   mPriority;        // +0x10
    int   mStatus;          // +0x14
    int   mThreadAffinity;  // +0x18
    int   mSlot;            // +0x1c
    void* mpReturnValue;    // +0x20
    void* mpCleanup;        // +0x24
};

// @ 0x006af260
char __stdcall FUN_006af260(void* p1, void** out, void* p3, void* p4, void* p5,
                            void* p6, char flag)
{
    if (flag) {
        char r = ((char(__fastcall*)(void*, int, void*, void*, void*, void*, void*, void*))
                      (*(void***)p1)[8])(p1, 0, out, p3, p4, p5,
                                         *(void**)((char*)p6 + 4), p6);
        if (r) return r;
    }
    void* mgr = F_68f4d0();                                        // job manager
    ((void(__fastcall*)(void*, int))(*(void***)mgr)[8])(mgr, 0);
    cJob* localJob = 0;
    void* mgr2 = F_68f4d0();
    if (localJob) {
        cJob* t = localJob;
        localJob = 0;
        F_690120(t, 0);
    }
    ((void(__fastcall*)(void*, int, void**))(*(void***)mgr2)[4])(mgr2, 0, (void**)&localJob);
    JobData* jd = (JobData*)F_f473a0(0x28, "App/AsyncRequest/JobData", 0, 0, 0, 0);
    if (jd) {
        jd->mpVtbl0 = &vtbl_13f1ab0;
        jd->mpVtbl1 = &vtbl_13ef094;
        _InterlockedExchange(&jd->mRefs, 0);
        jd->mpVtbl0 = &vtbl_1409478;
        jd->mpVtbl1 = &vtbl_1409474;
        jd->mpJob = 0;
        jd->mpBuffer = 0;
        jd->k0 = 0; jd->k1 = 0; jd->k2 = 0;
    }
    if (jd)
        ((void(__fastcall*)(void*, int))(*(void***)jd)[0])(jd, 0);
    void* oldJob = jd->mpJob;
    if (p1 != oldJob) {
        if (p1)
            ((void(__fastcall*)(void*, int))(*(void***)p1)[1])(p1, 0);
        jd->mpJob = p1;
        if (oldJob)
            ((void(__fastcall*)(void*, int))(*(void***)oldJob)[2])(oldJob, 0);
    }
    JobBuffer* buf = (JobBuffer*)F_926020(0x10, "App/AsyncRequest/Buffer", 0, 0, 0, 0);
    if (buf) {
        buf->mpVtbl0 = &vtbl_13effa8;
        _InterlockedExchange(&buf->mRefs, 0);
        buf->mpVtbl0 = &vtbl_1409488;
        buf->mpMgr = 0;
        buf->mpStream = 0;
    }
    JobBuffer* oldBuf = jd->mpBuffer;
    if (buf != oldBuf) {
        if (buf)
            ((void(__fastcall*)(void*, int))(*(void***)buf)[1])(buf, 0);
        jd->mpBuffer = buf;
        if (oldBuf)
            ((void(__fastcall*)(void*, int))(*(void***)oldBuf)[2])(oldBuf, 0);
    }
    JobBuffer* cur = jd->mpBuffer;
    void* oldMgr = cur->mpMgr;
    if (p4 != oldMgr) {
        if (p4)
            ((void(__fastcall*)(void*, int))(*(void***)p4)[1])(p4, 0);
        cur->mpMgr = p4;
        if (oldMgr)
            ((void(__fastcall*)(void*, int))(*(void***)oldMgr)[2])(oldMgr, 0);
    }
    void* oldStream = jd->mpBuffer->mpStream;
    if (oldStream) {
        jd->mpBuffer->mpStream = 0;
        ((void(__fastcall*)(void*, int))(*(void***)oldStream)[2])(oldStream, 0);
    }
    jd->m14 = p5;
    jd->k0 = *(unsigned*)((char*)p6 + 0);
    jd->k1 = *(unsigned*)((char*)p6 + 4);
    jd->k2 = *(unsigned*)((char*)p6 + 8);
    jd->mFlag = flag;
    F_68f9b0(localJob, 0, jd);                                     // AddDependency
    localJob->mThreadAffinity = 4;
    localJob->mpCallback = (void*)&F_6af140;
    localJob->mpCallbackData = jd;
    if (localJob) F_68f950(localJob, 0);                           // AddRef
    void* result = 0;
    if (!flag) {
        void* mem = F_f473a0(0x10, "Resource/Async", 0, 0, 0, 0);
        void* r = mem ? F_6ae510(mem, 0, &localJob) : 0;
        if (r) {
            ((void(__fastcall*)(void*, int))(*(void***)r)[0])(r, 0);
            result = r;
        }
    } else {
        void* m = F_67de70(p6, &localJob);
        FUN_006af150(m, 0, (AsyncKey*)p6, &result, &localJob);
    }
    ((void(__fastcall*)(void*, int))(*(void***)p4)[8])(p4, 0);
    F_6909b0(localJob, 0);                                         // GetStatus
    *out = result;
    if (localJob) F_690120(localJob, 0);
    ((void(__fastcall*)(void*, int))(*(void***)jd)[1])(jd, 0);
    if (localJob) F_690120(localJob, 0);
    ((void(__fastcall*)(void*, int))(*(void***)mgr)[9])(mgr, 0);
    return 1;
}

// ---------------------------------------------------------------------------
// 006af720  read + append a chunk to a "1URL" MemoryStream file
// ---------------------------------------------------------------------------
// @ 0x006af720
void __fastcall FUN_006af720(void* self, int, void* stream)
{
    int hdr = 0;
    int size = 0;
    ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, 0, 0);
    unsigned total = ((unsigned(__fastcall*)(void*, int))(*(void***)stream)[7])(stream, 0);
    if (total >= 8 && (total & 3) == 0 &&
        F_93a780(stream, &hdr, 1, 0) && hdr == 0x4c525531 &&
        F_93a780(stream, &size, 1, 0) &&
        size >= 8 && (unsigned)(size + 4) <= total && (size & 3) == 0) {
        // header looks valid: keep `size`
    } else {
        ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, 0, 0);
        int magic = 0x4c525531;
        IO_WriteUint32(stream, &magic, 1, 0);
        int zero = 0;
        IO_WriteUint32(stream, &zero, 1, 0);
        size = 0;
    }

    void* mstream = *(void**)((char*)self + 0x54);   // MemoryStream being appended
    int msize = ((int(__fastcall*)(void*, int))(*(void***)mstream)[7])(mstream, 0);
    int pos = 8;
    if (size != 0 && (unsigned)(msize + 0xc) > (unsigned)size) {
        ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, size, 0);
        int extra = 0;
        if (F_93a780(stream, &extra, 1, 0) && (extra & 3) == 0 &&
            (unsigned)(extra + size) <= total)
            pos = extra + size + 4;
    }
    ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, pos, 0);
    IO_WriteUint32(stream, &msize, 1, 0);
    void* m2 = *(void**)((char*)self + 0x54);
    void* data = F_93ba70(m2, msize);
    ((void(__fastcall*)(void*, int, void*, int))(*(void***)stream)[14])(stream, 0, data, msize);
    ((void(__fastcall*)(void*, int))(*(void***)stream)[13])(stream, 0);
    ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, 4, 0);
    IO_WriteUint32(stream, &pos, 1, 0);
}

