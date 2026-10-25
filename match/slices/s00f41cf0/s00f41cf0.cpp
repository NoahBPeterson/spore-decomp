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

// Per-action scratch record (stride 0x1ac) addressed through ActionExtraTable.
struct ActionExtra {
    uint8_t  mExcluded;             // +0x000
    char     pad01[3];              // +0x001
    int32_t  mCost;                 // +0x004
    char     pad08[0x1ac - 0x08];   // +0x008
};
struct ActionExtraTable {
    ActionExtra* mEntries;          // +0x000
};

// Budget context handed to the state evaluator (only +0x004 is read).
struct ActionBudget {
    int32_t  mUnused0;              // +0x000
    int32_t  mBudget;               // +0x004
};

// Tutorial action vector (0x188 stride), reached from the manager.  Objects in
// the manager's tutorial array have stride 0x534.
struct Tutorial {
    char     pad00[0x84];           // +0x000
    Action*  mActionBegin;          // +0x084
    Action*  mActionEnd;            // +0x088
    char     pad8c[0x534 - 0x8c];   // +0x08c
};

// A record in the manager's record list (0x27e8 stride).  The lookup helper
// returns one of these and only the key and object fields are inspected.
struct ActionRecord {
    int32_t  mKey;                  // +0x000
    int32_t  mPad04;                // +0x004
    void*    mObject;               // +0x008
    char     pad0c[0x27e8 - 0x0c];  // +0x00c
};

struct ActionTable {
    char     pad00[0x2bf4];         // +0x000
    void*    mBegin;                // +0x2bf4
    void*    mEnd;                  // +0x2bf8
    char     pad2bfc[0x2c08 - 0x2bfc]; // +0x2bfc
    uint8_t  mFlag;                 // +0x2c08
};

struct ScenarioManager {
    char     pad00[0x178];          // +0x000
    int32_t  mSpanBegin178;         // +0x178
    int32_t  mSpanEnd17c;           // +0x17c
    char     pad180[0x238 - 0x180]; // +0x180
    int32_t  mCount238;             // +0x238
    Tutorial* mTutorialBegin;       // +0x23c
    Tutorial* mTutorialEnd;         // +0x240
    char     pad244[0x2bf4 - 0x244]; // +0x244
    void*    mRecordBegin;          // +0x2bf4
    void*    mRecordEnd;            // +0x2bf8
    char     pad2bfc[0x2c08 - 0x2bfc]; // +0x2bfc
    uint8_t  mRecordFlag;           // +0x2c08
};

// o+0x70 points at an array of 0x4e0-stride entries whose byte +2 is tested.
struct ActionInfoEntry {
    uint16_t pad00;                 // +0x000
    uint8_t  mFlag;                 // +0x002
    char     pad03[0x4e0 - 0x03];   // +0x003
};
struct ActionInfoHolder {
    char     pad00[0x70];           // +0x000
    ActionInfoEntry* mEntries;      // +0x070
};

// Masked helper objects.
struct EvalObj {
    char FUN_00f25ed0();            // 0x00f25ed0
};
struct PosseSim {
    int FUN_00d52df0();             // 0x00d52df0
};
struct Obj6c0200 {
    void* FUN_006c0200();           // 0x006c0200
};
struct ObjEE3020 {
    void FUN_00ee3020();            // 0x00ee3020
};
struct ScenarioGlobals {
    char pad00[0x14];               // +0x000
    Obj6c0200* mpField14;           // +0x014
};
extern void* g_16c7aa4;             // 0x016c7aa4

// Small ordered key/cost map used by the two-pass evaluator (the retail map is a
// vector_map of 8-byte {key,value} entries).
struct CostEntry {
    int32_t mKey;                   // +0x000
    int32_t mValue;                 // +0x004
};
#define COST_MAP_CAPACITY 128
static int CostFind(const CostEntry* entries, int count, int key)
{
    int lo = 0, hi = count;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (entries[mid].mKey < key)
            lo = mid + 1;
        else
            hi = mid;
    }
    if (lo < count && entries[lo].mKey == key)
        return entries[lo].mValue;
    return 0;
}
static void CostAdd(CostEntry* entries, int* count, int key, int add)
{
    int lo = 0, hi = *count;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (entries[mid].mKey < key)
            lo = mid + 1;
        else
            hi = mid;
    }
    if (lo < *count && entries[lo].mKey == key) {
        entries[lo].mValue += add;
        return;
    }
    if (*count >= COST_MAP_CAPACITY)
        return;
    for (int i = *count; i > lo; --i)
        entries[i] = entries[i - 1];
    entries[lo].mKey = key;
    entries[lo].mValue = add;
    ++*count;
}

char   __cdecl FUN_00f3b370(int type);                          // 0x00f3b370
int*   __cdecl FUN_00ed29b0(void* begin, void* end, int* key, unsigned char flag); // 0x00ed29b0
void*  __cdecl FUN_00d539d0();                                  // 0x00d539d0

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

    bool Eval427c0();               // 0x00f427c0
    void Call41820(int param);      // 0x00f41820
    void Sub41300();                // 0x00f41300
    void Sub3c420();                // 0x00f3c420
    void* CallE8a0(int param);      // 0x00f3e8a0
    int  FUN_00f416b0(int idx, Action* a, int param, void* extra,
                      int zero1, int zero2, char* out, int flag); // 0x00f416b0
    char FUN_00f404d0(int param, int idx);                        // 0x00f404d0
    Tutorial* FUN_00f3be60(int idx);                              // 0x00f3be60

    void f_41cf0();                 // 0x00f41cf0
    void f_42580(void* v);          // 0x00f42580
    void f_425d0(int param);        // 0x00f425d0
    void f_42a00(int param);        // 0x00f42a00
    bool f_41dc0(Action* a, int idx, void* p);   // 0x00f41dc0
    bool f_420d0(int idx, Action* a, int n, int* out, void* p); // 0x00f420d0
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
    void assign(unsigned n, const void* value);                    // 0x00f42670
    void ctor_assign(unsigned n, const void* value, void* alloc);  // 0x00f3f9a0
    void swap(Vec44* other);                                       // 0x00f41b30
    void dtor();                                                   // 0x00dfb380
    void erase_range(char* first, char* last);                     // 0x00f0b0e0
};

// out-of-line EASTL helpers (masked).
void  __cdecl vec_fill(char* first, char* last, const void* value);       // 0xf09800
void  __cdecl vec_uninit_fill(char* first, unsigned n, const void* value); // 0xf09d70
void  __cdecl vec_fill_n(char* first, unsigned n, const void* value);      // 0xf3dec0

// @ 0x00f42670
void Vec44::assign(unsigned n, const void* value)
{
    if (n > (unsigned)((mpCapacity - mpBegin) / 0x44)) {
        Vec44 temp;
        temp.ctor_assign(n, value, (void*)mAllocator);
        this->swap(&temp);
        temp.dtor();
    } else if (n > (unsigned)((mpEnd - mpBegin) / 0x44)) {
        unsigned cur = (unsigned)((mpEnd - mpBegin) / 0x44);
        vec_fill(mpBegin, mpEnd, value);
        vec_uninit_fill(mpEnd, n - cur, value);
        mpEnd = mpBegin + (n * 0x44);
    } else {
        vec_fill_n(mpBegin, n, value);
        this->erase_range(mpBegin + (n * 0x44), mpEnd);
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
bool ScenarioObj::f_41dc0(Action* a, int idx, void* pv)
{
    ActionBudget* p = (ActionBudget*)pv;
    char out = 0;                       // FUN_00f416b0 output (reuses the arg slot in retail)
    bool result = true;                 // local_6
    bool bVar1 = false;                 // mParam1 == mParam2 for the first-probe group
    bool bOther = false;                // local_13
    int limit = a->mParam3 - (p != 0 ? p->mBudget : 0);
    int n1;

    a->mState = -1;

    if ((unsigned)(a->mType - 1) > 0xa)
        return result;

    switch (a->mType) {
    case 6:
    case 9:
    case 10:
        n1 = FUN_00f416b0(idx, a, a->mParam2, p, 0, 0, &out, 1);
        if (n1 < limit) {
            if (n1 == 0 && out != 0 && a->mState == -1 && p != 0 &&
                FUN_00f3b370(a->mType)) {
                int param = a->mParam2;
                if (FUN_00f404d0(param, idx) == 0) {
                    EvalObj* o = (EvalObj*)CallE8a0(param);
                    if (o != 0 && o->FUN_00f25ed0())
                        goto after_first;
                }
            }
            result = false;
            a->mState = 0x11;
        } else {
            if (p == 0) {
                if (a->mParam3 != 0)
                    goto after_first;
            } else {
                n1 = a->mParam3;
            }
            if (n1 == 0) {
                result = false;
                a->mState = 0x14;
            }
        }
    after_first:
        if (a->mParam1 == a->mParam2)
            bVar1 = true;
        break;
    default:
        break;
    }

    int n2 = FUN_00f416b0(idx, a, a->mParam1, p, 0, 0, &out, 1);
    if (n2 < limit) {
        if (result) {
            if (n2 == 0 && out != 0 && a->mState == -1 && p != 0 &&
                FUN_00f3b370(a->mType)) {
                int param = a->mParam1;
                if (FUN_00f404d0(param, idx) == 0) {
                    EvalObj* o = (EvalObj*)CallE8a0(param);
                    if (o != 0 && o->FUN_00f25ed0())
                        goto done;
                }
            }
            result = false;
            if (a->mState == -1)
                a->mState = 0x11;
        }
    } else if (p == 0) {
        if (a->mParam3 == 0) {
            if (n2 == 0) {
                if (result) {
                    result = false;
                    if (a->mState == -1) {
                        EvalObj* o = (EvalObj*)CallE8a0(a->mParam1);
                        if (o != 0 && o->FUN_00f25ed0())
                            a->mState = 0x15;
                        else
                            a->mState = 0x14;
                    }
                }
            } else {
                EvalObj* o = (EvalObj*)CallE8a0(a->mParam1);
                if (o != 0 && o->FUN_00f25ed0() && result) {
                    result = false;
                    if (a->mState == -1)
                        a->mState = 0x15;
                }
            }
        }
    } else if (a->mParam3 == 0) {
        if (result) {
            result = false;
            if (a->mState == -1) {
                EvalObj* o = (EvalObj*)CallE8a0(a->mParam1);
                if (o != 0 && o->FUN_00f25ed0())
                    a->mState = 0x15;
                else
                    a->mState = 0x14;
            }
        }
    }

done:
    if (bVar1 && n2 < 2 && result) {
        result = false;
        a->mState = 0x13;
    }
    if (a->mType == 5) {
        ScenarioManager* mgr = (ScenarioManager*)mpManager;
        int value;
        int other;
        if (p == 0) {
            value = mgr->mCount238;
            other = (mgr->mSpanEnd17c - mgr->mSpanBegin178) / 0x38;
        } else {
            value = mgr->mCount238;
            PosseSim* sim = (PosseSim*)FUN_00d539d0();
            other = sim->FUN_00d52df0();
        }
        if (value - other < limit && result) {
            result = false;
            a->mState = 0x16;
        }
    }
    return result;
}

// @ 0x00f420d0
bool ScenarioObj::f_420d0(int idx, Action* fixed, int n, int* out, void* pv)
{
    ActionExtraTable* extraTable = (ActionExtraTable*)pv;
    bool local_39 = false;
    bool local_3a = false;
    char local_3b = 0;
    Tutorial* tutorial = FUN_00f3be60(idx);
    int count = (int)(tutorial->mActionEnd - tutorial->mActionBegin);
    if (count <= n)
        count = n + 1;
    if (out != 0)
        *out = -1;

    CostEntry costs[COST_MAP_CAPACITY];
    int costCount = 0;

    for (int pass = 0; pass < 2; ++pass) {
        for (int i = 0; i < count; ++i) {
            Action* a;
            if (fixed == 0 || n != i)
                a = &tutorial->mActionBegin[i];
            else
                a = fixed;

            bool active;
            if (a->mType == 3)
                active = true;
            else if (a->mType == 7 || a->mType == 6 ||
                     a->mType == 10 || a->mType == 9)
                active = false;
            else
                continue;

            if (pass != (active ? 0 : 1))
                continue;

            ActionExtra* extra = 0;
            if (extraTable != 0) {
                extra = &extraTable->mEntries[i];
                if (extra->mExcluded != 0)
                    continue;
            }

            if (a->mParam1 != -1) {
                int cost1 = FUN_00f416b0(idx, a, a->mParam1, extra, 0, 0, &local_3b, 0);

                ScenarioManager* mgr = (ScenarioManager*)mpManager;
                ActionRecord* recEnd = (ActionRecord*)mgr->mRecordEnd;
                ActionRecord* rec = (ActionRecord*)FUN_00ed29b0(
                    mgr->mRecordBegin, mgr->mRecordEnd, &a->mParam1, mgr->mRecordFlag);
                if (rec == recEnd || a->mParam1 < rec->mKey)
                    rec = recEnd;
                void* found = (rec == recEnd) ? 0 : (void*)&rec->mObject;

                if (pass == 0 && local_3b != 0 && extraTable != 0 &&
                    a->mType != 4 && a->mType != 5 && a->mType != 0xb) {
                    ActionInfoHolder* holder = (ActionInfoHolder*)CallE8a0(a->mParam1);
                    bool noFlag = (holder == 0) ||
                                  (holder->mEntries[idx].mFlag == 0);
                    if (noFlag &&
                        (found == 0 || ((EvalObj*)found)->FUN_00f25ed0()))
                        cost1 = 0x7fffffff;
                }

                int value1 = CostFind(costs, costCount, a->mParam1);

                int limit1 = a->mParam3;
                if (limit1 == 0)
                    limit1 = cost1;
                if (extraTable != 0)
                    limit1 -= extra->mCost;

                if (cost1 - value1 < limit1 && value1 > 0) {
                    local_39 = true;
                    if (fixed == 0 || a == fixed) {
                        a->mFlags |= 1;
                        if (a->mState == -1)
                            a->mState = 0x18;
                        if (a == fixed)
                            local_3a = true;
                        if (out != 0 && *out == -1)
                            *out = i;
                    }
                }
                if (pass == 0)
                    CostAdd(costs, &costCount, a->mParam1, limit1);
            }

            if ((a->mType == 9 || a->mType == 6 || a->mType == 10) &&
                a->mParam2 != -1) {
                int cost2 = FUN_00f416b0(idx, a, a->mParam2, extra, 0, 0, &local_3b, 0);
                EvalObj* obj = (EvalObj*)CallE8a0(a->mParam2);

                if (cost2 == 0 && local_3b != 0 && extraTable != 0 &&
                    a->mType != 4 && a->mType != 5 && a->mType != 0xb &&
                    FUN_00f404d0(a->mParam2, idx) == 0 &&
                    (obj == 0 || obj->FUN_00f25ed0()))
                    cost2 = 0x7fffffff;

                int value2 = CostFind(costs, costCount, a->mParam2);

                int limit2 = a->mParam3;
                if (limit2 == 0)
                    limit2 = cost2;
                if (extraTable != 0)
                    limit2 -= extra->mCost;

                if (cost2 - value2 < limit2 && value2 > 0) {
                    local_39 = true;
                    if (fixed == 0 || a == fixed) {
                        a->mFlags |= 1;
                        if (a->mState == -1)
                            a->mState = 0x18;
                        if (a == fixed)
                            local_3a = true;
                        if (out != 0 && *out == -1)
                            *out = i;
                    }
                }
                if (pass == 0)
                    CostAdd(costs, &costCount, a->mParam2, limit2);
            }
        }
    }

    return fixed != 0 ? local_3a : local_39;
}
