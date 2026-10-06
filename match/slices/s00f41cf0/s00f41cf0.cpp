// Slice s00f41cf0 -- Unnamed scenario/action evaluator region (bfs1 slice 5).
// Module flags: /O2 /MD /Gy /EHsc /TP  (all functions are /O2; no SEH here).
#include "types.h"
#include <new>
#include <intrin.h>

// ---------------------------------------------------------------- extern helpers (masked)
// 0x00f41bb0  (this-object, pointer arg)
void __cdecl FUN_00f41bb0(void* self, void* v);
// 0x00f41820
// 0x00f3e8a0
// 0x00f41300 / 0x00f3c420 / 0x00f416b0 / 0x00f3b370 / 0x00f404d0 / 0x00f25ed0
void* __cdecl SP_NounManager();
struct cGameNounManager { void* GetAvatar(); };

// ---------------------------------------------------------------- action element (stride 0x188)
struct Action {
    int32_t  mType;                 // +0x000
    int32_t  mParam1;               // +0x004
    int32_t  mParam2;               // +0x008
    int32_t  mParam3;               // +0x00c
    char     pad10[0x14 - 0x10];    // +0x010
    uint32_t mFlags;                // +0x014
    char     pad18[0x184 - 0x18];   // +0x018
    int32_t  mState;                // +0x184
};

// ---------------------------------------------------------------- 0x00f42780
// T* f(T* dst, unsigned n, const T& v): constructs n copies via the copy ctor.
struct Elem4e0 {
    char pad[0x4e0];
    void Construct(const Elem4e0&) throw();
};
Elem4e0* __cdecl f_42780(Elem4e0* dst, unsigned n, const Elem4e0& v)
{
    while (n > 0) {
        --n;
        dst->Construct(v);
        dst = (Elem4e0*)((char*)dst + 0x4e0);
    }
    return dst;
}

// ---------------------------------------------------------------- scenario object (the 'this' class)
struct ScenarioObj {
    char     pad00[0x10];           // +0x000
    void*    mpManager;             // +0x010
    char     pad14[0x8c - 0x14];    // +0x014
    void*    mpField8c;             // +0x08c
    char     pad90[0xb4 - 0x90];    // +0x090
    void**   mpBuckets;             // +0x0b4
    int      mnBucketCount;         // +0x0b8
    char     padbc[0xd0 - 0xbc];    // +0x0bc
    void*    mpFieldD0;             // +0x0d0
    void*    mpFieldD4;             // +0x0d4
    int      mFieldD8;              // +0x0d8
    int      mFieldDC;              // +0x0dc
    int      mFieldE0;              // +0x0e0
    int      mFieldE4;              // +0x0e4

    void Eval427c0();               // 0x00f427c0
    void Call41820(int param);      // 0x00f41820
    void Sub41300();                // 0x00f41300
    void Sub3c420();                // 0x00f3c420
    void* CallE8a0(int param);      // 0x00f3e8a0

    void f_41cf0();                 // 0x00f41cf0
    void f_42580(void* v);          // 0x00f42580
    void f_425d0(int param);        // 0x00f425d0
    void f_42a00(int param);        // 0x00f42a00
    char f_41dc0(Action* a, int idx, void* p);   // 0x00f41dc0
    char f_420d0(int idx, Action* a, int n, int* out, void* p); // 0x00f420d0
};

// @ 0x00f42580
struct V3 { int a, b, c; };
void ScenarioObj::f_42580(void* v)
{
    *(V3*)((char*)mpManager + 0x130) = *(V3*)v;
    if (mpField8c != 0) {
        cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
        nm->GetAvatar();
        FUN_00f41bb0(this, v);
    }
}

// @ 0x00f42a00
void ScenarioObj::f_42a00(int param)
{
    Eval427c0();
    Call41820(param);
    Eval427c0();
}

// ---------------------------------------------------------------- vector<T,Alloc> with 0x44 stride
struct Vec44 {
    char*    mpBegin;               // +0x00
    char*    mpEnd;                 // +0x04
    char*    mpCapacity;            // +0x08
    char     mAllocator[4];         // +0x0c
    void assign(unsigned n, const void* value);  // 0x00f42670
};

// out-of-line EASTL helpers (masked).
void  __cdecl vec_fill(char* first, char* last, const void* value);       // 0xf09800
void  __cdecl vec_uninit_fill(char* first, unsigned n, const void* value); // 0xf09d70
void  __cdecl vec_fill_n(char* first, unsigned n, const void* value);      // 0xf3dec0
void  __cdecl vec_erase_range(char* first, char* last);                    // 0xf0b0e0
void  __cdecl vec_ctor_assign(Vec44* self, unsigned n, const void* value, void* alloc); // 0xf3f9a0
void  __cdecl vec_swap(Vec44* self, Vec44* other);                        // 0xf41b30
void  __cdecl vec_dtor(Vec44* self);                                      // 0xdfb380

// @ 0x00f42670
void Vec44::assign(unsigned n, const void* value)
{
    if (n > (unsigned)((mpCapacity - mpBegin) / 0x44)) {
        Vec44 temp;
        vec_ctor_assign(&temp, n, value, (void*)mAllocator);
        vec_swap(this, &temp);
        vec_dtor(&temp);
    } else if (n > (unsigned)((mpEnd - mpBegin) / 0x44)) {
        unsigned cur = (unsigned)((mpEnd - mpBegin) / 0x44);
        vec_fill(mpBegin, mpEnd, value);
        vec_uninit_fill(mpEnd, n - cur, value);
        mpEnd = mpBegin + (n * 0x44);
    } else {
        vec_fill_n(mpBegin, n, value);
        vec_erase_range(mpBegin + (n * 0x44), mpEnd);
    }
}

// Hashtable node: +0 key, +4 value, +8 next.
struct HNode { int key; int val; HNode* next; };

// @ 0x00f425d0  (scan hash buckets for entries whose table look-up equals param)
void ScenarioObj::f_425d0(int param)
{
    void* obj = CallE8a0(param);
    if (obj == 0)
        return;
    HNode** buckets = (HNode**)mpBuckets;
    HNode* node = buckets[0];
    HNode** b = buckets;
    if (node == 0) {
        do { ++b; } while (*b == 0);
        node = *b;
    }
    HNode* end = buckets[mnBucketCount];
    int* table = *(int**)((char*)mpManager + 0x2c10);
    while (node != end) {
        if (*(int*)((char*)table + node->key * 0x238 + 4) == param)
            FUN_00f41bb0(this, obj);
        node = node->next;
        if (node == 0) {
            do { ++b; node = *b; } while (node == 0);
        }
    }
}

// The three large action-evaluator state machines below are recorded as partial
// (skeletons): their full control flow was not reconstructed.

// --- helpers for the teardown
struct RefObj { virtual void vt0(); virtual void vt1(); };
struct RefCnt {
    virtual void destroy(int flag);     // +0x00
    int mnRef;                          // +0x04
};
void __cdecl SubEf29c0();               // 0x00ef29c0
void __cdecl RemoveHandler(void* h, int a, int b, int c, int d);  // 0x00571db0

struct GlobalList {
    void*  begin;            // +0x00
    void*  end;              // +0x04
    char   pad08[0x14 - 0x08];
    int    f14;              // +0x14
    int    f18;              // +0x18
    char   pad1c[0x20 - 0x1c];
    char   f20;              // +0x20
    char   pad21[0x24 - 0x21];
    void*  f24;              // +0x24
    void erase(void* first, void* last);   // 0x00e25bd0
};
extern GlobalList g_globalList;         // 0x016065d8

// @ 0x00f41cf0
void ScenarioObj::f_41cf0()
{
    Sub41300();
    Sub3c420();

    if (mpManager != 0) {
        void* p = mpManager;
        mpManager = 0;
        ((RefObj*)p)->vt1();
    }
    if (mpFieldD0 != 0) {
        RefCnt* rc = (RefCnt*)mpFieldD0;
        mpFieldD0 = 0;
        int n = rc->mnRef - 1;
        rc->mnRef = rc->mnRef - 1;
        if (n == 0) {
            rc->mnRef = 1;
            _ReadWriteBarrier();
            rc->destroy(1);
        }
    }
    g_globalList.f14 = 0;
    g_globalList.erase(g_globalList.begin, g_globalList.end);
    g_globalList.f18++;
    g_globalList.f20 = 1;
    if (g_globalList.f24 != 0) {
        void* p = g_globalList.f24;
        g_globalList.f24 = 0;
        ((RefObj*)p)->vt1();
    }
    SubEf29c0();
    if (mpFieldD4 != 0) {
        void* h = mpFieldD4;
        mpFieldD4 = 0;
        RemoveHandler(h, mFieldD8, mFieldDC, mFieldE0, mFieldE4);
    }
}

// @ 0x00f41dc0
char ScenarioObj::f_41dc0(Action* a, int idx, void* p)
{
    (void)a; (void)idx; (void)p;
    return 0;
}

// @ 0x00f420d0
char ScenarioObj::f_420d0(int idx, Action* a, int n, int* out, void* p)
{
    (void)idx; (void)a; (void)n; (void)out; (void)p;
    return 0;
}
