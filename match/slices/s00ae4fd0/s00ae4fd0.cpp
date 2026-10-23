// Slice s00ae4fd0: Simulator::SimSingleton (Spore simulator global singleton) member
// teardown / entry management, its constructor, noun+timer bookkeeping, a couple of
// string-keyed lookups and the city abduction-target scan.
// flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>

void __cdecl operator_delete__(void*);                    // 0x00f47380
void* __cdecl SporeMemcpy(void*, const void*, unsigned);  // 0x011e0744

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// --- globals / vtable address literals (relocations are masked) -------------
extern "C" void* g_pSimSingleton;      // 0x0167a60c
extern "C" float g_fCombatRange;       // 0x0167a610
extern "C" float g_f167a614;           // 0x0167a614
extern "C" float g_f167a618;           // 0x0167a618
extern char  g_x1654c04;               // 0x01654c04
extern char  g_b15d8b57;               // 0x015d8b57
extern char  g_b15d8b5a;               // 0x015d8b5a
extern wchar_t gEmptyString16;         // 0x01667bac
extern const wchar_t kStr_list[];      // 0x013f58ac  L"list"
extern const wchar_t kStr_type[];      // 0x013f36bc  L"type"
extern char vtbl_145ba98;              // 0x0145ba98
extern char vtbl_145ba74;              // 0x0145ba74
extern char vtbl_145b9ec;              // 0x0145b9ec
extern char vtbl_145b9c8;              // 0x0145b9c8
extern char vtbl_13ec458;              // 0x013ec458
extern char vtbl_13eb938;              // 0x013eb938
extern char vtbl_13f94d4;              // 0x013f94d4

// --- free (__cdecl) out-of-slice callees ------------------------------------
void* __cdecl FUN_00ae4590(void*, void*, void*);           // 0x00ae4590
void* __cdecl FUN_00b3d2c0(int, int);                      // 0x00b3d2c0
void* __cdecl SP_GetCurrentGameMode(void);                 // 0x00b5b800
void* __cdecl SP_GetActivePlanetRecord(void);              // 0x010212a0
void* __cdecl SP_NounManager(void);                        // 0x00b3d300
char  __cdecl FUN_00ac8050(void*, int, void*);             // 0x00ac8050
int   __cdecl FUN_00ae3390(void*);                         // 0x00ae3390
int   __cdecl FUN_00ae33b0(void*);                         // 0x00ae33b0
void* __cdecl FUN_00c420d0(void);                          // 0x00c420d0
float __cdecl FUN_00bfc400(void);                          // 0x00bfc400
void  __cdecl FUN_00695040(void*, const wchar_t*);         // 0x00695040
void  __cdecl FUN_00695080(void*, const wchar_t*);         // 0x00695080
void* __cdecl EA_ConvertToString16(void*, void*);          // 0x0093c6d0
void  __cdecl EA_ConvertToString16Impl(void*, const char*, unsigned); // 0x0093c5a0
void  __cdecl EA_RangeInitialize(void*, unsigned);         // 0x00579a90
void  __cdecl EA_ReadInt32(void*, void*, unsigned, unsigned); // 0x0093a780
void  __cdecl eastl_string16_copy(void*, const void*);     // 0x0056e2d0
void  __cdecl FUN_00b5b6f0(void*);                          // 0x00b5b6f0
void  __cdecl FUN_00b5b690(void*);                          // 0x00b5b690

// generic vtable-slot invoker: emits `mov eax,[ecx]; mov edx,[eax+off]; call edx`
static inline void* VSlot(void* o, unsigned off)
{
    return *(void**)((char*)(*(void**)o) + off);
}

typedef void* (__thiscall *PFn0p)(void*);
typedef void  (__thiscall *PFn0v)(void*);
typedef int   (__thiscall *PFn0i)(void*);
typedef char  (__thiscall *PFn0c)(void*);
typedef void* (__thiscall *PFn1p)(void*, void*);
typedef int   (__thiscall *PFn1i)(void*, void*);
typedef char  (__thiscall *PFn1c)(void*, void*);
typedef void  (__thiscall *PFn1v)(void*, void*);
typedef char  (__thiscall *PFn2c)(void*, void*, void*);

// --- structures -------------------------------------------------------------
struct Slot64 {                    // one 0x64-byte element of the +0x14 vector
    char mRaw[0x64];
    void Grow(void* value);        // 0x00ae4430
    void Ctor(void* src);          // 0x00ae3a10
};

struct PtrVec {                    // vector header at +0x14
    char* b;                       // +0x00
    char* e;                       // +0x04
    char* cap;                     // +0x08
    void DestroyRange(char* first, char* last);   // 0x00ae4930
    void AE5B70(unsigned n);                      // 0x00ae5b70
    void AE5D60(unsigned pos, void* elem);        // 0x00ae5d60
};

struct SimNode {                   // intrusive list node (0x28 bytes)
    SimNode* mpNext;               // +0x00
    SimNode* mpPrev;               // +0x04
    char     mData[0x10];          // +0x08   (callback argument is &mData)
    void*    mpObj;                // +0x18
    int      mx1c;                 // +0x1c
    int      mx20;                 // +0x20
    void   (*mpfn)(void*);         // +0x24
};

struct SimList {                   // intrusive list head at +0x28 (8 bytes)
    SimNode* mpNext;               // +0x00
    SimNode* mpPrev;               // +0x04
    void AE4990();                 // 0x00ae4990
};

struct Entry {                     // overlay of SimNode::mData (node + 8)
    char     mx00[0x10];           // +0x00
    void*    mpObj;                // +0x10
    int      mx14;                 // +0x14
    int      mx18;                 // +0x18
    void   (*mpfn)(void*);         // +0x1c
};

struct EString16 {                 // eastl::basic_string<wchar_t> (3 words)
    wchar_t* mpBegin;              // +0x00
    wchar_t* mpEnd;                // +0x04
    wchar_t* mpCap;                // +0x08
};

struct EStr16B {                   // 4-word eastl string temporary
    void*    mx00;
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCap;
};

struct OpaqueObj {                 // p1 receiver of SetIsEnabled
    void F_00bd8bd0();             // 0x00bd8bd0
    void F_00beb5c0();             // 0x00beb5c0
    void F_00c01e20(int);          // 0x00c01e20
    void F_00bdc8a0(void*, void*); // 0x00bdc8a0
    void F_00be3ad0();             // 0x00be3ad0
    void F_00be2110();             // 0x00be2110
    void F_00be3de0();             // 0x00be3de0
};

struct TC {                        // out-of-slice thiscall callees (ecx receiver)
    void* GetCivilization();       // 0x00bd9bf0  SP::cCity::GetCivilization
    void  F_00be5700(void*);       // 0x00be5700
    int   F_00bfc600();            // 0x00bfc600
    int   F_008e7f80();            // 0x008e7f80
    char  F_00c0c0e0();            // 0x00c0c0e0
    char  F_00bfcc40(int);         // 0x00bfcc40
    void  F_00ae2e20();            // 0x00ae2e20
    int   F_00b8dab0();            // 0x00b8dab0
    void  F_00b225d0(void*);       // 0x00b225d0  cGameNounManager::RemoveNoun
    void  F_00b63890();            // 0x00b63890  cGonzagoTimer ctor
    void  F_00b638b0();            // 0x00b638b0  cGonzagoTimer dtor
    void  F_00bc30f0();            // 0x00bc30f0  SP::cSPTimer::Start
};

struct Cvls {                      // cVarListSerializer factory
    void Construct(void* data, void* tag, unsigned id);   // 0x00692f90
};

struct CvlsStream {                // cVarListSerializer_s0069_3280
    char Serialize(void* obj);                            // 0x00693e10
};

struct SimSingleton {              // 0xc4 bytes
    void*    mpVtblA;              // +0x00
    void*    mx04;                 // +0x04
    void*    mpVtblB;              // +0x08
    int      mx0c;                 // +0x0c
    uint8_t  mc10;                 // +0x10
    uint8_t  mx11[3];              // +0x11
    PtrVec   mVec;                 // +0x14
    void*    mx20;                 // +0x20
    int      mx24;                 // +0x24
    SimList  mList;                // +0x28
    int      mx30;                 // +0x30
    int      mx34;                 // +0x34
    char     mTimer38[0x20];       // +0x38
    char     mTimer58[0x20];       // +0x58
    char     mTimer78[0x20];       // +0x78
    EString16 mStr;                // +0x98
    int      mxA4;                 // +0xa4
    uint8_t  mcA8;                 // +0xa8
    uint8_t  mcA9;                 // +0xa9
    uint16_t mxAa;                 // +0xaa
    int      miAC;                 // +0xac
    int      miB0;                 // +0xb0
    uint8_t  mcB4;                 // +0xb4
    uint8_t  mxB5[3];              // +0xb5
    int      miB8;                 // +0xb8
    int      miBC;                 // +0xbc
    int      miC0;                 // +0xc0

    SimSingleton();                                   // 0x00ae5c30
    void  Destroy();                                  // 0x00ae5740
    void  SetIsEnabled(OpaqueObj* p1, void* p2, void* p3);  // 0x00ae5840
    void  RemoveDeadEntries();                        // 0x00ae58c0
    void  ShutdownEntries();                          // 0x00ae5930
    void  RemoveEnabledEntries();                     // 0x00ae59a0
    void  RemoveInactiveEntries(void* arg);           // 0x00ae4fd0
    void  ResetAll();                                 // 0x00ae5f20
    void  B5B6C0();                                   // 0x00b5b6c0
    void  AE3660(void*, void*, void*);                // 0x00ae3660
};

// ===========================================================================
// 0x00ae5740
// @ 0x00ae5740
void SimSingleton::Destroy()
{
    mpVtblA = &vtbl_145ba98;
    mpVtblB = &vtbl_145ba74;
    _ReadWriteBarrier();
    {
        char* b = (char*)mStr.mpBegin;
        if ((int)((char*)mStr.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    ((TC*)mTimer78)->F_00b638b0();
    ((TC*)mTimer58)->F_00b638b0();
    ((TC*)mTimer38)->F_00b638b0();
    mList.AE4990();
    mVec.DestroyRange(mVec.b, mVec.e);
    if (mVec.b != 0 && *(int*)(mVec.b - 4) != 0)
        operator_delete__(mVec.b);
    mpVtblA = &vtbl_145b9ec;
    mpVtblB = &vtbl_145b9c8;
    FUN_00b5b690(this);
    if (g_pSimSingleton == this)
        g_pSimSingleton = 0;
    *(void* volatile*)&mpVtblA = &vtbl_13ec458;
    *(void* volatile*)&mpVtblB = &vtbl_13eb938;
}

// ===========================================================================
// 0x00ae5840
// @ 0x00ae5840
void SimSingleton::SetIsEnabled(OpaqueObj* p1, void* p2, void* p3)
{
    AE3660(p1, p2, p3);
    p1->F_00bd8bd0();
    p1->F_00beb5c0();
    if (SP_GetCurrentGameMode() == (void*)&g_x1654c04 ||
        ((TC*)SP_GetActivePlanetRecord())->F_00b8dab0() != 5)
        RemoveInactiveEntries(p1);
    p1->F_00c01e20(0);
    p1->F_00bdc8a0(p2, p3);
    p1->F_00be3ad0();
    p1->F_00be2110();
    p1->F_00be3de0();
}

// ===========================================================================
// 0x00ae58c0
// @ 0x00ae58c0
void SimSingleton::RemoveDeadEntries()
{
    SimNode* head = (SimNode*)&mList;
    SimNode* n = head->mpNext;
    if (n == head)
        return;
    do {
        void** o = (void**)n->mpObj;
        Entry* e = (Entry*)n->mData;
        if (o == 0 || ((PFn0c)(*(void**)((char*)*(void**)o + 0x10)))(o) == 0) {
            if (e->mpfn != 0)
                e->mpfn(e);
            SimNode* next = n->mpNext;
            SimNode* dead = next->mpPrev;
            dead->mpPrev->mpNext = dead->mpNext;
            dead->mpNext->mpPrev = dead->mpPrev;
            void** dobj = (void**)dead->mpObj;
            if (dobj != 0)
                ((PFn0v)(*(void**)((char*)*(void**)dobj + 0x04)))(dobj);
            operator_delete__(dead);
            n = next;
        } else {
            n = n->mpNext;
        }
    } while (n != head);
}

// ===========================================================================
// 0x00ae5930
// @ 0x00ae5930
void SimSingleton::ShutdownEntries()
{
    SimNode* head = (SimNode*)&mList;
    SimNode* n;
    for (n = head->mpNext; n != head; n = n->mpNext) {
        Entry* e = (Entry*)n->mData;
        void** o = (void**)e->mpObj;
        if (o != 0)
            ((PFn1v)VSlot(o, 0x0c))(o, (void*)1);
        if (e->mpfn != 0)
            e->mpfn(e);
    }
    SimNode* p = head->mpNext;
    while (p != head) {
        SimNode* cur = p;
        p = p->mpNext;
        void** o = (void**)cur->mpObj;
        if (o != 0)
            ((PFn0v)VSlot(o, 0x04))(o);
        operator_delete__(cur);
    }
    head->mpNext = head;
    head->mpPrev = head;
}

// ===========================================================================
// 0x00ae59a0
// @ 0x00ae59a0
void SimSingleton::RemoveEnabledEntries()
{
    SimNode* head = (SimNode*)&mList;
    SimNode* n = head->mpNext;
    if (n == head)
        return;
    do {
        void** o = (void**)n->mpObj;
        Entry* e = (Entry*)n->mData;
        if (o != 0 && ((PFn0c)(*(void**)((char*)*(void**)o + 0x10)))(o) != 0) {
            void** o2 = (void**)e->mpObj;
            ((PFn1v)(*(void**)((char*)*(void**)o2 + 0x0c)))(o2, (void*)0);
            if (e->mpfn != 0)
                e->mpfn(e);
            n = n->mpNext;
            SimNode* dead = n->mpPrev;
            dead->mpPrev->mpNext = dead->mpNext;
            dead->mpNext->mpPrev = dead->mpPrev;
            void** dobj = (void**)dead->mpObj;
            if (dobj != 0)
                ((PFn0v)(*(void**)((char*)*(void**)dobj + 0x04)))(dobj);
            operator_delete__(dead);
        } else {
            n = n->mpNext;
        }
    } while (n != head);
}

// ===========================================================================
// 0x00ae4fd0
// @ 0x00ae4fd0
void SimSingleton::RemoveInactiveEntries(void* arg)
{
    void* civ = ((TC*)this)->GetCivilization();
    int id = ((PFn0i)VSlot(civ, 0x4c))(civ);
    void* current = 0;
    void* arr[32];
    struct { void** b; void** e; } range;
    range.b = arr;
    range.e = arr;
    ((TC*)this)->F_00be5700(&range);
    for (void** it = range.b; it != range.e; ++it) {
        void* cand;
        if (*it == 0)
            cand = 0;
        else
            cand = ((PFn1p)VSlot(*it, 0x0c))(*it, (void*)0x0436f315);
        if (cand != current) {
            if (cand != 0)
                ((PFn0v)VSlot(cand, 0x00))(cand);
            if (current != 0)
                ((PFn0v)VSlot(current, 0x04))(current);
            current = cand;
        }
        void* chosen = 0;
        if (*(int*)((char*)current + 0x684) < 1) {
            void* objs;
            if (((TC*)current)->F_00bfc600() != 0)
                goto emit;
            if (FUN_00ae33b0(0) == 0)
                goto emit;
            objs = FUN_00c420d0();
            {
                char best = 0;
                for (void** p = *(void***)objs; p != *(void***)((char*)objs + 4); ++p) {
                    void* c;
                    void* w1;
                    float* pf;
                    float* qf;
                    char b;
                    if (*p == 0)
                        continue;
                    c = ((PFn1p)VSlot(*p, 0xb8))(*p, &vtbl_13f94d4);
                    if (c == 0)
                        continue;
                    if (FUN_00ae3390(c) == 2)
                        continue;
                    w1 = ((PFn0p)VSlot(c, 0x0c))(c);
                    if (((PFn0c)VSlot(w1, 0x2c))(w1) != 0)
                        continue;
                    if (((PFn0i)VSlot(c, 0x10))(c) == id)
                        continue;
                    w1 = ((PFn0p)VSlot(c, 0x08))(c);
                    pf = (float*)((PFn0p)VSlot(current, 0x2c))(current);
                    qf = (float*)((PFn0p)VSlot(w1, 0x2c))(w1);
                    {
                        float dx = qf[0] - pf[0];
                        float dy = qf[1] - pf[1];
                        float dz = qf[2] - pf[2];
                        if (dx * dx + dy * dy + dz * dz > FUN_00bfc400())
                            continue;
                    }
                    b = 0;
                    {
                        void* r = ((PFn1p)VSlot(c, 0x5c))(c, (void*)0x0137e8e0);
                        if (r != 0) {
                            if (((TC*)r)->F_00b8dab0() == 2)
                                continue;
                            FUN_00b3d2c0(id, (int)r);
                            if (FUN_00ae3390((void*)id) != 0 ||
                                ((TC*)c)->F_00bfcc40(id) != 0) {
                                int t = *(int*)((char*)r + 0xb20);
                                b = t == 0 ? 4 : (char)((t == 1) * 2 + 1);
                            }
                        } else {
                            void* r2 = ((PFn1p)VSlot(c, 0x5c))(c, (void*)0xb033b403);
                            if (r2 == 0) {
                                if (FUN_00ae3390(c) == 0) {
                                    if (FUN_00ae33b0(c) != 0 &&
                                        ((TC*)c)->F_00c0c0e0() != 0)
                                        b = 2;
                                } else {
                                    if (((TC*)c)->F_00bfcc40(id) != 0)
                                        b = 1;
                                }
                            } else {
                                int t;
                                if (((PFn0i)VSlot(r2, 0x4c))(r2) != -1) {
                                    FUN_00b3d2c0(id, (int)r2);
                                    if (FUN_00ae3390((void*)id) == 0)
                                        goto emit;
                                }
                                t = 0;
                                b = 5;
                            }
                        }
                    }
                    if (best < b) {
                        chosen = c;
                        best = b;
                    }
                }
            }
        }
emit:
        if (current != 0)
            ((PFn1v)VSlot((char*)current + 0x588, 0x50))((char*)current + 0x588, chosen);
    }
    for (void** it = range.b; it != range.e; ++it) {
        if (*it != 0)
            ((PFn0v)VSlot(*it, 0x04))(*it);
    }
    if (range.b != 0 && range.b != arr)
        operator_delete__(range.b);
}

// ===========================================================================
// 0x00ae5c30
// @ 0x00ae5c30
SimSingleton::SimSingleton()
{
    B5B6C0();
    mpVtblA = &vtbl_145b9ec;
    mpVtblB = &vtbl_145b9c8;
    g_pSimSingleton = this;
    FUN_00b5b6f0(this);
    mpVtblA = &vtbl_145ba98;
    mpVtblB = &vtbl_145ba74;
    mc10 = 0;
    mVec.b = 0;
    mVec.e = 0;
    mVec.cap = 0;
    SimNode* head = (SimNode*)&mList;
    head->mpNext = head;
    head->mpPrev = head;
    ((TC*)mTimer38)->F_00b63890();
    ((TC*)mTimer58)->F_00b63890();
    ((TC*)mTimer78)->F_00b63890();
    mStr.mpCap = &gEmptyString16 + 1;
    mStr.mpBegin = &gEmptyString16;
    mStr.mpEnd = &gEmptyString16;
    mcA8 = 0;
    mcA9 = 0;
    miAC = 0;
    miB0 = 0;
    mcB4 = 0;
    miB8 = 0;
    miBC = 0;
    miC0 = 0;
    ((TC*)mTimer38)->F_00bc30f0();
}

// ===========================================================================
// 0x00ae5f20
// @ 0x00ae5f20
void SimSingleton::ResetAll()
{
    void* mgr = SP_NounManager();
    PtrVec* v = &mVec;
    char* s = v->b;
    char* t = v->e;
    for (char* p = s; p != t; p += 0x64) {
        void* noun = *(void**)(p + 0x38);
        if (noun != 0) {
            ((TC*)mgr)->F_00b225d0(noun);
            void* r = *(void**)(p + 0x38);
            if (r != 0) {
                *(void**)(p + 0x38) = 0;
                ((PFn0v)VSlot(r, 0x04))(r);
            }
        }
        if (*(int*)(p + 0x60) != 0) {
            volatile long* rc = (volatile long*)(*(char**)(p + 0x60) + 8);
            long old;
            *(int*)(p + 0x60) = 0;
            _InterlockedExchangeAdd(rc, -1);
            old = _InterlockedExchangeAdd(rc, 0);
            if (old < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
    for (char* p = s; p != s; p += 0x64)
        ((Slot64*)p)->Grow(t);
    v->DestroyRange(s, t);
    v->e += (int)(t - s) / 0x64 * 0x64;
    {
        SimNode* head = (SimNode*)&mList;
        SimNode* n = head->mpNext;
        while (n != head) {
            SimNode* cur = n;
            void** o = (void**)cur->mpObj;
            n = n->mpNext;
            if (o != 0)
                ((PFn0v)VSlot(o, 0x04))(o);
            operator_delete__(cur);
        }
        head->mpPrev = head;
        head->mpNext = head;
    }
}

// ===========================================================================
// 0x00ae6060
// @ 0x00ae6060
void __cdecl FUN_00ae6060(void* param_1, PtrVec* v)
{
    char* b = v->b;
    char* e = v->e;
    char* p = (char*)FUN_00ae4590(e, e, b);
    v->DestroyRange(p, v->e);
    v->e += (int)(e - b) / 0x64 * 0x64;

    unsigned count = 0;
    void* s = ((PFn0p)VSlot(param_1, 0x20))(param_1);
    void* r = ((PFn0p)VSlot(s, 0x18))(s);
    EA_ReadInt32(r, &count, 1, 0);
    v->AE5B70(count);
    for (unsigned i = 0; i < count; ++i) {
        char buf[0x98];
        *(int*)(buf + 0x00) = -1;
        *(float*)(buf + 0x04) = g_fCombatRange;
        *(float*)(buf + 0x08) = g_f167a614;
        *(float*)(buf + 0x0c) = g_f167a618;
        *(int*)(buf + 0x20) = -1;
        *(uint8_t*)(buf + 0x24) = 0;
        *(uint8_t*)(buf + 0x25) = 1;
        *(uint8_t*)(buf + 0x26) = 0;
        *(int*)(buf + 0x28) = -1;
        *(int*)(buf + 0x2c) = -1;
        *(uint8_t*)(buf + 0x30) = 0;
        *(uint8_t*)(buf + 0x31) = 0;
        *(int*)(buf + 0x34) = 0;
        *(int*)(buf + 0x38) = 0;
        *(int*)(buf + 0x3c) = 0;
        *(uint8_t*)(buf + 0x40) = 0;
        *(int*)(buf + 0x44) = 0;
        *(int*)(buf + 0x48) = 0;
        *(int*)(buf + 0x4c) = 0;
        *(int*)(buf + 0x50) = 0;
        *(int*)(buf + 0x54) = 0;
        *(int*)(buf + 0x58) = 0;
        *(int*)(buf + 0x5c) = 0;
        *(int*)(buf + 0x60) = 0;
        ((Cvls*)(buf + 0x64))->Construct(buf, (void*)0x015665f0, 0x1a80d26u);
        ((CvlsStream*)(buf + 0x58))->Serialize(param_1);
        if (v->e < v->cap) {
            char* pos = v->e;
            v->e = pos + 0x64;
            if (pos != 0)
                ((Slot64*)pos)->Ctor(buf);
        } else {
            v->AE5D60((unsigned)v->e, buf);
        }
        {
            void* rc0 = *(void**)(buf + 0x54);
            if (rc0 != 0) {
                volatile long* rc = (volatile long*)((char*)rc0 + 8);
                long old;
                _InterlockedExchangeAdd(rc, -1);
                old = _InterlockedExchangeAdd(rc, 0);
                if (old < 1)
                    _InterlockedExchangeAdd(rc, 1);
                else
                    _InterlockedExchangeAdd(rc, 0);
            }
        }
        {
            void** q = *(void***)(buf + 0x2c);
            if (q != 0)
                ((PFn0v)VSlot(q, 0x04))(q);
        }
    }
    ((PFn0v)VSlot(param_1, 0x1c))(param_1);
}

// ===========================================================================
// 0x00ae5a20
// @ 0x00ae5a20
char __cdecl FUN_00ae5a20(void* functor, const char* name, PtrVec* v)
{
    char flag = 1;
    if (v->b == v->e)
        return 1;
    {
        EStr16B local;
        EString16 key;
        EStr16B tmp;
        local.mx00 = 0;
        local.mpBegin = &gEmptyString16;
        local.mpEnd = &gEmptyString16;
        local.mpCap = &gEmptyString16 + 1;
        if (name != 0) {
            EA_ConvertToString16Impl(&tmp, name, 0xffffffffu);
        } else {
            tmp.mx00 = 0;
            tmp.mpBegin = &gEmptyString16;
            tmp.mpEnd = &gEmptyString16;
            tmp.mpCap = &gEmptyString16 + 1;
            EA_RangeInitialize(&tmp.mpBegin, 0);
        }
        eastl_string16_copy(&key, &tmp.mpBegin);
        {
            char* tb = (char*)tmp.mpBegin;
            if ((int)((char*)tmp.mpCap - tb & 0xfffffffe) > 2 && tb != 0)
                operator_delete__(tb);
        }
        {
            wchar_t* ks = key.mpBegin;
            if (ks == key.mpEnd)
                ks = (wchar_t*)kStr_list;
            ((PFn1v)VSlot(functor, 0x00))(functor, ks);
        }
        for (char* q = v->b; q != v->e; q += 0x64) {
            if (flag != 0) {
                char ok = FUN_00ac8050(functor, 0, q);
                flag = 1;
                if (ok == 0)
                    flag = 0;
            } else {
                flag = 0;
            }
        }
        {
            wchar_t* ks = key.mpBegin;
            if (ks == key.mpEnd)
                ks = (wchar_t*)kStr_list;
            ((PFn1v)VSlot(functor, 0x04))(functor, ks);
        }
        {
            char* kb = (char*)key.mpBegin;
            if ((int)((char*)key.mpCap - kb & 0xfffffffe) > 2 && kb != 0)
                operator_delete__(kb);
        }
        {
            char* lb = (char*)local.mpBegin;
            if ((int)((char*)local.mpCap - lb & 0xfffffffe) > 2 && lb != 0)
                operator_delete__(lb);
        }
    }
    return flag;
}

// ===========================================================================
// 0x00ae5360
// @ 0x00ae5360
char __cdecl FUN_00ae5360(void* functor, const char* name, const wchar_t* key, void* arg3)
{
    EStr16B outer;
    EStr16B conv;
    EString16 str;
    EString16 key2;
    char ok;
    outer.mx00 = 0;
    outer.mpBegin = &gEmptyString16;
    outer.mpEnd = &gEmptyString16;
    outer.mpCap = &gEmptyString16 + 1;
    FUN_00695040(&outer.mpBegin, key);
    if (outer.mpBegin == outer.mpEnd)
        return 1;
    conv.mx00 = 0;
    if (name == 0) {
        conv.mpBegin = &gEmptyString16;
        conv.mpEnd = &gEmptyString16;
        conv.mpCap = &gEmptyString16 + 1;
        EA_RangeInitialize(&conv.mpBegin, 0);
    } else {
        EA_ConvertToString16Impl(&conv, name, 0xffffffffu);
    }
    eastl_string16_copy(&str, &conv.mpBegin);
    {
        char* b = (char*)conv.mpBegin;
        if ((int)((char*)conv.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    EA_ConvertToString16(&key2, &outer.mpBegin);
    if (str.mpBegin == str.mpEnd) {
        ok = ((PFn1c)VSlot(functor, 0x00))(functor, arg3);
        if (ok != 0) {
            ok = ((PFn1c)VSlot(functor, 0x0c))(functor, key2.mpBegin);
            if (ok != 0)
                ok = 1;
        }
    } else {
        ok = ((PFn1c)VSlot(functor, 0x00))(functor, str.mpBegin);
        if (g_b15d8b57 == 0) {
            if (ok != 0) {
                ok = ((PFn1c)VSlot(functor, 0x0c))(functor, key2.mpBegin);
                if (ok != 0)
                    ok = 1;
            }
        } else if (ok != 0) {
            ok = ((PFn2c)VSlot(functor, 0x08))(functor, (void*)kStr_type, arg3);
            if (ok != 0) {
                ok = ((PFn1c)VSlot(functor, 0x0c))(functor, key2.mpBegin);
                if (ok != 0)
                    ok = 1;
            }
        }
    }
    if (str.mpBegin == str.mpEnd) {
        if (ok != 0) {
            char t = ((PFn1c)VSlot(functor, 0x04))(functor, arg3);
            ok = t == 0 ? 0 : 1;
        } else {
            ok = 0;
        }
    } else {
        if (ok != 0) {
            char t = ((PFn1c)VSlot(functor, 0x04))(functor, str.mpBegin);
            ok = t == 0 ? 0 : 1;
        } else {
            ok = 0;
        }
    }
    {
        char* b = (char*)str.mpBegin;
        if ((int)((char*)str.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    {
        char* b = (char*)key2.mpBegin;
        if ((int)((char*)key2.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    {
        char* b = (char*)outer.mpBegin;
        if ((int)((char*)outer.mpCap - b) > 1 && b != 0)
            operator_delete__(b);
    }
    return ok;
}

// ===========================================================================
// 0x00ae5530
// @ 0x00ae5530
char __cdecl FUN_00ae5530(void* functor, const char* name, const wchar_t* key, void* arg3)
{
    EStr16B outer;
    EStr16B conv;
    EString16 str;
    EString16 key2;
    char ok;
    outer.mx00 = 0;
    outer.mpBegin = &gEmptyString16;
    outer.mpEnd = &gEmptyString16;
    outer.mpCap = &gEmptyString16 + 1;
    FUN_00695080(&outer.mpBegin, key);
    if (outer.mpBegin == outer.mpEnd)
        return 1;
    conv.mx00 = 0;
    if (name == 0) {
        conv.mpBegin = &gEmptyString16;
        conv.mpEnd = &gEmptyString16;
        conv.mpCap = &gEmptyString16 + 1;
        EA_RangeInitialize(&conv.mpBegin, 0);
    } else {
        EA_ConvertToString16Impl(&conv, name, 0xffffffffu);
    }
    eastl_string16_copy(&str, &conv.mpBegin);
    {
        char* b = (char*)conv.mpBegin;
        if ((int)((char*)conv.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    EA_ConvertToString16(&key2, &outer.mpBegin);
    if (str.mpBegin == str.mpEnd) {
        ok = ((PFn1c)VSlot(functor, 0x00))(functor, arg3);
        if (ok != 0) {
            ok = ((PFn1c)VSlot(functor, 0x0c))(functor, key2.mpBegin);
            if (ok != 0)
                ok = 1;
        }
    } else {
        ok = ((PFn1c)VSlot(functor, 0x00))(functor, str.mpBegin);
        if (g_b15d8b5a == 0) {
            if (ok != 0) {
                ok = ((PFn1c)VSlot(functor, 0x0c))(functor, key2.mpBegin);
                if (ok != 0)
                    ok = 1;
            }
        } else if (ok != 0) {
            ok = ((PFn2c)VSlot(functor, 0x08))(functor, (void*)kStr_type, arg3);
            if (ok != 0) {
                ok = ((PFn1c)VSlot(functor, 0x0c))(functor, key2.mpBegin);
                if (ok != 0)
                    ok = 1;
            }
        }
    }
    if (str.mpBegin == str.mpEnd) {
        if (ok != 0) {
            char t = ((PFn1c)VSlot(functor, 0x04))(functor, arg3);
            ok = t == 0 ? 0 : 1;
        } else {
            ok = 0;
        }
    } else {
        if (ok != 0) {
            char t = ((PFn1c)VSlot(functor, 0x04))(functor, str.mpBegin);
            ok = t == 0 ? 0 : 1;
        } else {
            ok = 0;
        }
    }
    {
        char* b = (char*)str.mpBegin;
        if ((int)((char*)str.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    {
        char* b = (char*)key2.mpBegin;
        if ((int)((char*)key2.mpCap - b & 0xfffffffe) > 2 && b != 0)
            operator_delete__(b);
    }
    {
        char* b = (char*)outer.mpBegin;
        if ((int)((char*)outer.mpCap - b) > 1 && b != 0)
            operator_delete__(b);
    }
    return ok;
}
