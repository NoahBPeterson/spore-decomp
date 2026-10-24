// Decompiled from SporeApp.exe (gold6 batch, worker 33).
// Slice s00b0d2a0: cKeySlotList slot management plus the "Simulator" agent /
// interaction bookkeeping class (paint system, agent vectors, slot lists).

#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned __int64 u64;

// ---------------------------------------------------------------------------
// External helpers (declared, resolved by the linker in the real binary).
// ---------------------------------------------------------------------------
extern "C" void* __cdecl op_new4(int size, const char* file, int flags, int align);
extern "C" void* __cdecl op_new6(int size, const char* file, int flags, int align,
                                 void* allocator, int line);
extern "C" void  __cdecl op_del_array(void* p);
extern "C" void* __cdecl memcpy_(void* dst, const void* src, unsigned size);
extern "C" int   __stdcall QueryPerformanceCounter_ll(long long* out);
extern "C" bool  __cdecl EA_WriteUint32(void* stream, u32* value, int count, int flags);

struct KeySlot {
    u32   mBits;   // +0x00: bits 31/30 = link flags, low 30 = index
    void* mpObj;   // +0x04
};

// ---------------------------------------------------------------------------
// cKeySlotList: a growable array of KeySlot at +0 with a free-run head at
// +0x14 and the most recently released index at +0x18.
// ---------------------------------------------------------------------------
struct SlotListStub {
    u32 NextRun(u32 idx);                   // 0x00b0ceb0
};

struct ReleaseStub {
    void Release(u32 idx);                  // 0x00b0d2a0
};

struct cKeySlotList {
    KeySlot* mpSlots;                       // +0x00
    u8       mPad04[0x08];                  // +0x04
    void**   mpBlocks;                      // +0x0c
    u32      mf10;                          // +0x10
    u32      mnFreeHead;                    // +0x14
    u32      mnLastReleased;                // +0x18
    u8       mPad1c[0x08];                  // +0x1c
    u32      mnActiveSlot;                  // +0x24

    void ReleaseSlot(u32 idx);                              // 0x00b0d2a0
    u32  GetActiveValue();                                  // 0x00b0d350
    void RemoveRangeTo(KeySlot** out, KeySlot* pos);        // 0x00b0d500
};

// ---------------------------------------------------------------------------
// cSkinner: the "Simulator" subsystem (vtable 0x145cc18).  Agent vector at
// +0x24, render-job list at +0x38, three slot lists at +0x44/+0x60/+0x7c and
// a stopwatch at +0x20.
// ---------------------------------------------------------------------------
struct cGonzago {                           // SP::cGonzagoSubsystem at +0x04
    void Construct();                       // 0x00b5b960
    void Destroy();                         // 0x00b5b9a0
};

struct SlotArray {                          // begin/end of a KeySlot list
    KeySlot* mpBegin;                       // +0x00
    KeySlot* mpEnd;                         // +0x04
    void DestroySlots(KeySlot* begin, KeySlot* end);   // 0x00b0cfd0
};

struct RenderJobList {                      // circular list sentinel
    RenderJobList* mpNext;                  // +0x00
    RenderJobList* mpPrev;                  // +0x04
    void Erase();                           // 0x0075f3f0
};

struct AgentListStub {
    void Destroy();                         // 0x00afb7a0
};

struct Stopwatch {
    Stopwatch* Init(int mode, int b);       // 0x0093a560
};

struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    void*     mpObj;
};

struct TransferVec {
    int* mpBegin;
    int* mpEnd;
};

struct cSkinner {
    void*       mpVftable;                  // +0x00
    u8          mPad04[0x1c];               // +0x04 (cGonzagoSubsystem)
    void*       mpStopwatch;                // +0x20
    void*       mpAgentBegin;               // +0x24
    void*       mpAgentEnd;                 // +0x28
    void*       mpAgentCap;                 // +0x2c
    u8          mPad30[0x08];               // +0x30
    RenderJobList mJobs;                    // +0x38
    u8          mPad40[0x04];               // +0x40
    SlotArray   mSlotsA;                    // +0x44
    u8          mPad4c[0x0c];               // +0x4c
    u32         mnSlotsAFree;               // +0x58
    u32         mnSlotsALast;               // +0x5c
    SlotArray   mSlotsB;                    // +0x60
    u8          mPad68[0x0c];               // +0x68
    u32         mnSlotsBFree;               // +0x74
    u32         mnSlotsBLast;               // +0x78
    SlotArray   mSlotsC;                    // +0x7c
    u8          mPad84[0x0c];               // +0x84
    u32         mnSlotsCFree;               // +0x90
    u32         mnSlotsCLast;               // +0x94
    u32         mf98;                       // +0x98
    u32         mf9c;                       // +0x9c
    u8          mbA0;                       // +0xa0

    void* Construct();                                              // 0x00b0d8d0
    void  Destroy();                                                // 0x00b0d610
    void  Serialize(void* stream, TransferVec* vec);                // 0x00b0d540
    void* FindMatchingSlot(void* profile, u32 arg3, u32 arg4,
                           u32 arg5);                               // 0x00b0d380
    void* CreateAgentLink(void* a1, void* a2, u32 a3, u32 a4);      // 0x00b0d9f0
    void* CreateAgentLinkFlag(void* a1, void* a2, u32 a3, u32 a4);  // 0x00b0db30
    void  ResetSlots();                                             // 0x00b0dc60
    bool  RemoveAgent(void* agent);                                 // 0x00b0e1d0
    bool  AddAgent(void* agent);                                    // 0x00b0e400
};

// ---------------------------------------------------------------------------
// EASTL-ish vector helper types used by the free functions below.
// ---------------------------------------------------------------------------
struct SlotVec {                            // +0 begin, +4 end, +8 capacity
    KeySlot* mpBegin;
    KeySlot* mpEnd;
    KeySlot* mpCap;
    u8       mPad0c[0x08];                  // +0x0c
    u32      mnFreeHead;                    // +0x14
    u32      mnLastReleased;                // +0x18

    void Insert(KeySlot* at, KeySlot* val);         // 0x00b0e070
    void PushDefault();                             // 0x00b0e2d0
    u32  Acquire(void** value);                     // 0x00b0e490
};

struct ObjVec {                             // +0 begin, +4 end, +8 capacity
    void** mpBegin;
    void** mpEnd;
    void** mpCap;

    void InsertN(void* at, u32 count, void** val);          // 0x00b0d710
    void AssignVec(ObjVec* other);                          // 0x00b0ddd0
    void EraseRange(void** first, void** last);             // 0x00b0dec0
};

struct AgentVec {                           // begin/end at +0x24 handled by caller
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
};

struct VecGrowStub {
    void Assign(void** a, void** b);                    // 0x00afb1a0
    void* Realloc(u32 n, void** a, void** b);           // 0x00b0d2f0
    void GrowOne(void** at, void** val);                // 0x00b0df20
};

struct KeySlotStub {
    KeySlot* Assign(KeySlot* other);        // 0x00b0d050
};

struct FilterRange {
    int v0, v1, v2, v3, v4, v5;
    void Init(void* src, void* tag);        // 0x00abf010
    void Advance();                         // 0x00abeb20
};

extern "C" void* __cdecl FUN_00b0d0d0(void* dst, void* src, void* param);
extern "C" void  __cdecl FUN_00dc6730(void* a, void* b, void* c, void* d, void* e = 0);
extern "C" void  __cdecl FUN_00b0d210(KeySlot* at, KeySlot* from, KeySlot* to);
extern "C" void  __cdecl FUN_00b0d120(void* a, void* b, void** c);
extern "C" void  __cdecl FUN_00b0d170(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00b0ce40(void* a, u32 n, void** val, void* at);
extern "C" void  __fastcall AutoRefAssign(void** dst, void* val);

#define VTBL_SKINNER        ((void*)0x145cc18)
#define VTBL_GONZAGO_BASE   ((void*)0x145cbc8)
#define VTBL_GONZAGO_SUB    ((void*)0x145cbc0)
#define VTBL_PAINTSYSTEM    ((void*)0x13eb394)
#define VTBL_LISTENERBASE   ((void*)0x13eb384)
#define ALLOCATOR           ((void*)0x13ebb38)
#define STR_SIMULATOR       ((const char*)0x13f09b4)
#define STR_STOPWATCH       ((const char*)0x145cc8c)

// ===========================================================================
// 0x00b0d2a0 -- release a slot back onto the free run.
// ===========================================================================
// @ 0x00b0d2a0
void cKeySlotList::ReleaseSlot(u32 idx)
{
    KeySlot* slot = mpSlots + idx;
    void* obj = slot->mpObj;
    if (obj != 0)
        ((void(__fastcall*)(void*))(*(void***)obj)[1])(obj);
    u32 last = mnLastReleased;
    slot->mBits = (last & 0x3fffffffu) | (slot->mBits & 0xc0000000u) | 0x80000000u;
    mnLastReleased = idx;
    if (mnFreeHead == idx)
        mnFreeHead = ((SlotListStub*)this)->NextRun(idx);
}

// ===========================================================================
// 0x00b0d350 -- value stored in the active slot, or 0.
// ===========================================================================
// @ 0x00b0d350
u32 cKeySlotList::GetActiveValue()
{
    if (mnActiveSlot != 0x3fffffffu) {
        void* block = *(void**)((char*)mpBlocks + (mnActiveSlot >> 7) * 4);
        return *(u32*)((char*)block + 4 + (mnActiveSlot & 0x7f) * 8);
    }
    return 0;
}

// ===========================================================================
// 0x00b0d500 -- release the slot at pos, then copy the resulting iterator.
// ===========================================================================
// @ 0x00b0d500
void cKeySlotList::RemoveRangeTo(KeySlot** out, KeySlot* pos)
{
    ((ReleaseStub*)this)->Release((u32)(((char*)pos - (char*)mpSlots) >> 3));

    for (;;) {
        KeySlot* cur = pos;
        pos = pos + 1;
        if (((cur->mBits >> 30) & 1) != 0)
            break;
        if (((pos->mBits >> 31) & 1) != 0)
            break;
    }
    *out = pos;
}

// ===========================================================================
// 0x00b0d380 -- search both slot ranges for a matching interaction target.
// ===========================================================================
// @ 0x00b0d380
void* cSkinner::FindMatchingSlot(void* profile, u32 arg3, u32 arg4, u32 arg5)
{
    KeySlot* p;
    if (mnSlotsAFree < 0x3fffffffu)
        p = mSlotsA.mpBegin + mnSlotsAFree;
    else
        p = mSlotsA.mpEnd;

    KeySlot* endp = mSlotsA.mpEnd;
    for (;;) {
        if (p == endp) {
            ListNode* node = (ListNode*)((char*)this + 0x38);
            ListNode* it = (ListNode*)*(void**)((char*)this + 0x38);
            for (;;) {
                if (it == node)
                    return 0;
                void* item = it->mpObj;
                int a = ((int(__fastcall*)(void*))(*(void***)profile)[0x1c / 4])(profile);
                int b = ((int(__fastcall*)(void*))(*(void***)item)[0x1c / 4])(item);
                if (a == b && *(u32*)((char*)profile + 0x68) == arg5 &&
                    ((char(__fastcall*)(void*, u32, int))(*(void***)item)[0x30 / 4])(item, arg3, 0) != 0 &&
                    *(u32*)((char*)item + 0x70) != 0) {
                    if (arg4 == 0)
                        return item;
                    u32 cur = *(u32*)((char*)item + 0x24);
                    u32 val;
                    if (cur == 0x3fffffffu) {
                        val = 0;
                    } else {
                        void* block = *(void**)((char*)(*(void**)((char*)item + 0x0c)) + (cur >> 7) * 4);
                        val = *(u32*)((char*)block + 4 + (cur & 0x7f) * 8);
                    }
                    if (val == arg4)
                        return item;
                }
                it = it->mpNext;
            }
        }

        void* item = p->mpObj;
        int a = ((int(__fastcall*)(void*))(*(void***)profile)[0x1c / 4])(profile);
        int b = ((int(__fastcall*)(void*))(*(void***)item)[0x1c / 4])(item);
        if (a == b && *(u32*)((char*)profile + 0x68) == arg5 &&
            ((char(__fastcall*)(void*, u32, int))(*(void***)item)[0x30 / 4])(item, arg3, 0) != 0 &&
            *(u32*)((char*)item + 0x70) != 0) {
            if (arg4 == 0)
                return item;
            u32 cur = *(u32*)((char*)item + 0x24);
            u32 val;
            if (cur == 0x3fffffffu) {
                val = 0;
            } else {
                void* block = *(void**)((char*)(*(void**)((char*)item + 0x0c)) + (cur >> 7) * 4);
                val = *(u32*)((char*)block + 4 + (cur & 0x7f) * 8);
            }
            if (val == arg4)
                return item;
        }

        do {
            u32 bits = p->mBits;
            p = p + 1;
            if (((bits >> 30) & 1) != 0)
                break;
        } while ((int)p->mBits < 0);
    }
}

// ===========================================================================
// 0x00b0d540 -- serialize the agent id vector through the stream vtable.
// ===========================================================================
// @ 0x00b0d540
void cSkinner::Serialize(void* stream, TransferVec* vec)
{
    int* begin = vec->mpBegin;
    int* end   = vec->mpEnd;
    int  count = (int)(end - begin);

    void* io = ((void*(__fastcall*)(void*))(*(void***)this)[0x20 / 4])(this);
    void* strm = ((void*(__fastcall*)(void*))(*(void***)io)[0x18 / 4])(io);
    EA_WriteUint32(strm, (u32*)&count, 1, 0);

    for (int* it = begin; it != end; ++it) {
        u32 id = 0;
        if (*it != 0)
            id = ((u32(__fastcall*)(int, u32))(*(void***)*it)[2])(*it, 0x179c807);
        ((void(__fastcall*)(void*, u32))(*(void***)this)[0x2c / 4])(this, id);
    }

    ((void(__fastcall*)(void*))(*(void***)this)[0x1c / 4])(this);
}

// ===========================================================================
// 0x00b0d610 -- destructor: release the three slot lists and the job list.
// ===========================================================================
// @ 0x00b0d610
void cSkinner::Destroy()
{
    void* stopwatch = *(void**)((char*)this + 0x20);

    mpVftable = VTBL_SKINNER;
    *(void**)((char*)this + 4) = VTBL_GONZAGO_BASE;
    *(void**)((char*)this + 8) = VTBL_GONZAGO_SUB;

    if (stopwatch != 0)
        op_del_array(stopwatch);

    SlotArray* a = (SlotArray*)((char*)this + 0x7c);
    a->DestroySlots(a->mpBegin, a->mpEnd);
    if (a->mpBegin != 0)
        op_del_array(a->mpBegin);

    SlotArray* b = (SlotArray*)((char*)this + 0x60);
    b->DestroySlots(b->mpBegin, b->mpEnd);
    if (b->mpBegin != 0)
        op_del_array(b->mpBegin);

    SlotArray* c = (SlotArray*)((char*)this + 0x44);
    c->DestroySlots(c->mpBegin, c->mpEnd);
    if (c->mpBegin != 0)
        op_del_array(c->mpBegin);

    ((RenderJobList*)((char*)this + 0x38))->Erase();
    ((AgentListStub*)((char*)this + 0x24))->Destroy();
    ((cGonzago*)((char*)this + 4))->Destroy();

    mpVftable = VTBL_PAINTSYSTEM;
}

// ===========================================================================
// 0x00b0d710 -- insert count copies of *val at `at`.
// ===========================================================================
// @ 0x00b0d710
void ObjVec::InsertN(void* at, u32 count, void** val)
{
    ObjVec* self = this;

    if ((u32)(self->mpCap - self->mpBegin) < count) {
        int cur = (int)(self->mpEnd - self->mpBegin);
        u32 cap = (u32)cur * 2;
        if (cur == 0)
            cap = 1;
        u32 need = (u32)cur + count;
        if (need < cap)
            need = cap;

        void* buf;
        if (need == 0)
            buf = 0;
        else
            buf = op_new6((int)(need * 4), STR_SIMULATOR, 0, 0, ALLOCATOR, 0xd1);

        unsigned headBytes = (unsigned)((char*)at - (char*)self->mpBegin);
        void* p = memcpy_(buf, self->mpBegin, headBytes);
        void* insAt = (char*)p + headBytes;
        FUN_00b0ce40(insAt, count, val, at);

        unsigned tailBytes = (unsigned)((char*)self->mpEnd - (char*)at);
        void* tail = memcpy_((char*)insAt + count * 4, at, tailBytes);

        if (self->mpBegin != 0)
            op_del_array(self->mpBegin);
        self->mpBegin = (void**)buf;
        self->mpEnd   = (void**)((char*)tail + tailBytes);
        self->mpCap   = (void**)((char*)buf + need * 4);
        return;
    }

    if (count == 0)
        return;

    void* old = *val;
    if (old != 0)
        ((void(__fastcall*)(void*))(*(void***)old)[0x60 / 4])(old);

    u32 have = (u32)((char*)self->mpEnd - (char*)at) >> 2;
    if (count < have) {
        void* src = (char*)self->mpEnd - count * 4;
        FUN_00dc6730(&count, src, self->mpEnd, self->mpEnd);
        void* insAt = at;
        self->mpEnd = (void**)((char*)self->mpEnd + count * 4);
        FUN_00b0d170(at, src, self->mpEnd);
        FUN_00b0d120(insAt, (char*)insAt + count * 4, val);
    } else {
        FUN_00b0ce40(self->mpEnd, count - have, val, at);
        void* insAt = at;
        self->mpEnd = (void**)((char*)self->mpEnd + (count - have) * 4);
        FUN_00dc6730(&at, at, self->mpEnd, self->mpEnd);
        self->mpEnd = (void**)((char*)self->mpEnd + have * 4);
        FUN_00b0d120(insAt, self->mpEnd, val);
    }

    if (*val != 0)
        ((void(__fastcall*)(void*))(*(void***)*val)[0x5c / 4])(*val);
}

// ===========================================================================
// 0x00b0d8d0 -- constructor.
// ===========================================================================
// @ 0x00b0d8d0
void* cSkinner::Construct()
{
    u32 z = 0;

    mpVftable = VTBL_LISTENERBASE;
    ((cGonzago*)((char*)this + 4))->Construct();

    mpVftable = VTBL_SKINNER;
    *(void**)((char*)this + 4) = VTBL_GONZAGO_BASE;
    *(void**)((char*)this + 8) = VTBL_GONZAGO_SUB;

    *(u32*)((char*)this + 0x24) = z;
    *(u32*)((char*)this + 0x28) = z;
    *(u32*)((char*)this + 0x2c) = z;

    RenderJobList* jobs = (RenderJobList*)((char*)this + 0x38);
    jobs->mpNext = jobs;
    jobs->mpPrev = jobs;

    *(u32*)((char*)this + 0x44) = z;
    *(u32*)((char*)this + 0x48) = z;
    *(u32*)((char*)this + 0x4c) = z;

    u32 sentinel = 0x3fffffffu;
    *(u32*)((char*)this + 0x58) = sentinel;
    *(u32*)((char*)this + 0x5c) = sentinel;

    *(u32*)((char*)this + 0x60) = z;
    *(u32*)((char*)this + 0x64) = z;
    *(u32*)((char*)this + 0x68) = z;

    *(u32*)((char*)this + 0x74) = sentinel;
    *(u32*)((char*)this + 0x78) = sentinel;

    *(u32*)((char*)this + 0x7c) = z;
    *(u32*)((char*)this + 0x80) = z;
    *(u32*)((char*)this + 0x84) = z;

    *(u32*)((char*)this + 0x90) = sentinel;
    *(u32*)((char*)this + 0x94) = sentinel;

    *(u32*)((char*)this + 0x98) = z;
    *(u32*)((char*)this + 0x9c) = z;
    mbA0 = (u8)z;

    void* sw = op_new4(0x18, STR_STOPWATCH, (int)z, (int)z);
    if (sw != 0)
        sw = ((Stopwatch*)sw)->Init(3, 0);
    *(void**)((char*)this + 0x20) = sw;

    if ((*(u32*)sw | *(u32*)((char*)sw + 4)) == 0) {
        if (*(u32*)((char*)sw + 0x10) == 1) {
            u64 t = __rdtsc();
            *(u32*)sw = (u32)t;
            *(u32*)((char*)sw + 4) = (u32)(t >> 32);
        } else {
            long long q;
            QueryPerformanceCounter_ll(&q);
            *(u32*)sw = (u32)q;
            *(u32*)((char*)sw + 4) = (u32)(q >> 32);
        }
    }
    return this;
}

// ===========================================================================
// 0x00b0d9f0 -- register an interaction agent and splice a link node in.
// ===========================================================================
// @ 0x00b0d9f0
void* cSkinner::CreateAgentLink(void* a1, void* a2, u32 a3, u32 a4)
{
    if (a1 == 0)
        return 0;

    if (a2 != 0) {
        void* r = ((void*(__fastcall*)(void*))(*(void***)a2)[0x20 / 4])(a2);
        if (r != 0) {
            r = ((void*(__fastcall*)(void*))(*(void***)a2)[0x20 / 4])(a2);
            if (*(int*)((char*)r + 0x68) == 2)
                return 0;
        }
    }

    if (((char(__fastcall*)(void*, void*))(*(void***)a1)[0x34 / 4])(a1, a2) == 0)
        return 0;

    void* local = 0;
    if (a2 != 0) {
        u32 r = ((u32(__fastcall*)(void*, void*, void*, u32, u32))
                 (*(void***)this)[0x1c / 4])(this, a1, a2, a3, a4);
        AutoRefAssign(&local, (void*)r);
    }

    void* target = ((void*(__fastcall*)(void*))(*(void***)a1)[0x10 / 4])(a1);
    AutoRefAssign(&local, target);

    *(u32*)((char*)local + 0x68) = a4;
    if (a3 != 0)
        ((void(__fastcall*)(void*, u32))(*(void***)local)[0x4c / 4])(local, a3);
    if (a2 != 0)
        ((void(__fastcall*)(void*, void*))(*(void***)local)[0x40 / 4])(local, a2);

    ListNode* head = (ListNode*)((char*)this + 0x38);
    ListNode* node = (ListNode*)op_new6(0xc, STR_SIMULATOR, 0, 0, ALLOCATOR, 0xd1);
    if (node != 0) {
        node->mpObj = local;
        if (local != 0)
            ((void(__fastcall*)(void*))(*(void***)local)[0])(local);
        node->mpNext = head;
        node->mpPrev = head->mpPrev;
        head->mpPrev->mpNext = node;
        head->mpPrev = node;
    }
    if (local != 0)
        ((void(__fastcall*)(void*))(*(void***)local)[1])(local);
    return local;
}

// ===========================================================================
// 0x00b0db30 -- register an interaction agent, also stamping the link kind.
// ===========================================================================
// @ 0x00b0db30
void* cSkinner::CreateAgentLinkFlag(void* a1, void* a2, u32 a3, u32 a4)
{
    if (a1 == 0)
        return 0;

    if (((char(__fastcall*)(void*, void*))(*(void***)a1)[0x34 / 4])(a1, a2) == 0)
        return 0;

    void* local = 0;
    if (a2 != 0) {
        u32 r = ((u32(__fastcall*)(void*, void*, void*, u32, u32))
                 (*(void***)this)[0x1c / 4])(this, a1, a2, a3, a4);
        AutoRefAssign(&local, (void*)r);
    }

    void* target = ((void*(__fastcall*)(void*))(*(void***)a1)[0x10 / 4])(a1);
    AutoRefAssign(&local, target);

    *(u32*)((char*)local + 0x68) = a4;
    *(u32*)((char*)local + 0x6c) = 1;
    if (a3 != 0)
        ((void(__fastcall*)(void*, u32))(*(void***)local)[0x4c / 4])(local, a3);
    if (a2 != 0)
        ((void(__fastcall*)(void*, void*))(*(void***)local)[0x40 / 4])(local, a2);

    ListNode* head = (ListNode*)((char*)this + 0x38);
    ListNode* node = (ListNode*)op_new6(0xc, STR_SIMULATOR, 0, 0, ALLOCATOR, 0xd1);
    if (node != 0) {
        node->mpObj = local;
        if (local != 0)
            ((void(__fastcall*)(void*))(*(void***)local)[0])(local);
        node->mpNext = head;
        node->mpPrev = head->mpPrev;
        head->mpPrev->mpNext = node;
        head->mpPrev = node;
    }
    if (local != 0)
        ((void(__fastcall*)(void*))(*(void***)local)[1])(local);
    return local;
}

// ===========================================================================
// 0x00b0dc60 -- run every agent's queued interaction steps and drain slots.
// ===========================================================================
// @ 0x00b0dc60
void cSkinner::ResetSlots()
{
    u32 last = *(u32*)((char*)this + 0x74);
    KeySlot* p;
    if (last < 0x3fffffffu)
        p = *(KeySlot**)((char*)this + 0x60) + last;
    else
        p = *(KeySlot**)((char*)this + 0x64);

    KeySlot* endp = *(KeySlot**)((char*)this + 0x64);
    while (p != endp) {
        void* agent = p->mpObj;
        if (agent != 0)
            ((void(__fastcall*)(void*))(*(void***)agent)[0])(agent);
        ((void(__fastcall*)(void*))(*(void***)agent)[0x24 / 4])(agent);

        u8 tag = 0;
        FilterRange range;
        range.Init((char*)agent + 0x2c, &tag);

        while (range.v0 + range.v1 != range.v2 + range.v3) {
            ((void(__fastcall*)(void*, int, int, int, int, int, int))
             (*(void***)agent)[0x44 / 4])(agent, range.v0, range.v1, range.v2,
                                         range.v3, range.v4, range.v5);
            range.Advance();
        }

        while (*(u32*)((char*)agent + 0x24) != 0x3fffffffu) {
            u32 cur = *(u32*)((char*)agent + 0x24);
            void* block = *(void**)((char*)(*(void**)((char*)agent + 0x0c)) + (cur >> 7) * 4);
            if (*(u32*)((char*)block + 4 + (cur & 0x7f) * 8) == 0)
                break;
            if (cur > 0x3ffffffe) {
                cur = (u32)(((*(u32*)((char*)agent + 0x10) - *(u32*)((char*)agent + 0x0c)) >> 2) * 0x80)
                      + 0xffffff81u + *(u32*)((char*)agent + 0x20);
            }
            ((void(__fastcall*)(void*, FilterRange*, u32))
             (*(void***)agent)[0x50 / 4])(agent, &range, cur);
        }

        ((void(__fastcall*)(void*))(*(void***)agent)[4 / 4])(agent);

        do {
            u32 bits = p->mBits;
            p = p + 1;
            if (((bits >> 30) & 1) != 0)
                break;
        } while ((int)p->mBits < 0);
    }
}

// ===========================================================================
// 0x00b0ddd0 -- eastl::vector<AutoRefCount<cInteractionAgent>>::operator=
// ===========================================================================
// @ 0x00b0ddd0
void ObjVec::AssignVec(ObjVec* other)
{
    ObjVec* self = this;

    if (other == self)
        return;

    void** srcBegin = other->mpBegin;
    void** srcEnd   = other->mpEnd;
    u32 n = (u32)(srcEnd - srcBegin);

    if ((u32)(self->mpCap - self->mpBegin) < n) {
        void* buf = ((VecGrowStub*)self)->Realloc(n, srcBegin, srcEnd);
        ((VecGrowStub*)self)->Assign(self->mpBegin, self->mpEnd);
        if (self->mpBegin != 0 && *(u32*)((char*)self->mpBegin - 4) != 0)
            op_del_array(self->mpBegin);
        self->mpCap   = (void**)((char*)buf + n * 4);
        self->mpEnd   = (void**)((char*)buf + n * 4);
        self->mpBegin = (void**)buf;
        return;
    }

    u32 have = (u32)(self->mpEnd - self->mpBegin);
    if (have < n) {
        FUN_00b0d0d0(srcBegin, (char*)srcBegin + have * 4, self->mpEnd);
        FUN_00dc6730(&other, (char*)srcBegin + (u32)(self->mpEnd - self->mpBegin) * 4,
                     other->mpEnd, self->mpEnd, other);
        self->mpEnd = (void**)((char*)self->mpBegin + n * 4);
        return;
    }

    void* res = FUN_00b0d0d0(srcBegin, srcEnd, self->mpBegin);
    ((VecGrowStub*)self)->Assign((void**)res, self->mpEnd);
    self->mpEnd = (void**)((char*)self->mpBegin + n * 4);
}

// ===========================================================================
// 0x00b0dec0 -- destroy the range and shrink the vector.
// ===========================================================================
// @ 0x00b0dec0
void ObjVec::EraseRange(void** first, void** last)
{
    ObjVec* self = this;

    void** it = (void**)FUN_00b0d0d0(last, self->mpEnd, first);
    void** end = self->mpEnd;
    for (; it < end; ++it) {
        void* obj = *it;
        if (obj != 0)
            ((void(__fastcall*)(void*))(*(void***)obj)[0x5c / 4])(obj);
    }
    self->mpEnd = (void**)((char*)self->mpEnd + ((char*)last - (char*)first) * -1);
}

// ===========================================================================
// 0x00b0e070 -- insert one KeySlot before `at`.
// ===========================================================================
// @ 0x00b0e070
void SlotVec::Insert(KeySlot* at, KeySlot* val)
{
    SlotVec* self = this;

    KeySlot* end = self->mpEnd;
    if (end != self->mpCap) {
        if (at <= val && val < end)
            val = val + 1;

        if (end != 0 && ((end->mBits = end[-1].mBits), (int)end[-1].mBits >= 0) &&
            &end->mpObj != 0) {
            end->mpObj = end[-1].mpObj;
            if (end[-1].mpObj != 0)
                ((void(__fastcall*)(void*))(*(void***)end[-1].mpObj)[0])(end[-1].mpObj);
        }
        FUN_00b0d210(at, self->mpEnd - 1, self->mpEnd);
        ((KeySlotStub*)at)->Assign(val);
        self->mpEnd = self->mpEnd + 1;
        return;
    }

    int count = (int)(end - self->mpBegin);
    int newCap;
    if (count == 0)
        newCap = 1;
    else
        newCap = count * 2;

    void* buf;
    if (newCap == 0) {
        buf = 0;
    } else {
        buf = op_new6(newCap * 8, STR_SIMULATOR, 0, 0, ALLOCATOR, 0xd1);
    }

    unsigned headBytes = (unsigned)((char*)at - (char*)self->mpBegin);
    void* p = memcpy_(buf, self->mpBegin, headBytes);
    KeySlot* ins = (KeySlot*)((char*)p + headBytes);
    if (ins != 0) {
        ins->mBits = val->mBits;
        if (((int)val->mBits >= 0) && &ins->mpObj != 0) {
            ins->mpObj = val->mpObj;
            if (val->mpObj != 0)
                ((void(__fastcall*)(void*))(*(void***)val->mpObj)[0])(val->mpObj);
        }
    }
    unsigned tailBytes = (unsigned)((char*)self->mpEnd - (char*)at);
    void* tail = memcpy_((char*)ins + 8, at, tailBytes);

    if (self->mpBegin != 0)
        op_del_array(self->mpBegin);
    self->mpEnd   = (KeySlot*)((char*)tail + tailBytes);
    self->mpBegin = (KeySlot*)buf;
    self->mpCap   = (KeySlot*)((char*)buf + newCap * 8);
}

// ===========================================================================
// 0x00b0e1d0 -- remove agent from the +0x24 vector.
// ===========================================================================
// @ 0x00b0e1d0
bool cSkinner::RemoveAgent(void* agent)
{
    void** begin = (void**)mpAgentBegin;
    void** end   = (void**)((char*)this + 0x28);
    void** it    = begin;
    if (it != end) {
        for (;;) {
            if (*it == agent)
                break;
            ++it;
            if (it == end)
                break;
        }
        if (it != end) {
            if (agent != 0)
                ((void(__fastcall*)(void*))(*(void***)agent)[0x34 / 4])(agent);
            ((void(__fastcall*)(void*))(*(void***)agent)[0x60 / 4])(agent);

            void** curEnd = (void**)((char*)this + 0x28);
            if (it + 1 < curEnd)
                FUN_00b0d0d0(it + 1, curEnd, it);
            *(void**)((char*)this + 0x28) = (char*)curEnd - 4;

            void** last = *(void***)((char*)this + 0x28);
            if (*last != 0)
                ((void(__fastcall*)(void*))(*(void***)*last)[0x5c / 4])(*last);
            ((void(__fastcall*)(void*))(*(void***)agent)[0x5c / 4])(agent);
            return true;
        }
    }
    return false;
}

// ===========================================================================
// 0x00b0e2d0 -- push a default (empty) KeySlot onto the vector.
// ===========================================================================
// @ 0x00b0e2d0
void SlotVec::PushDefault()
{
    SlotVec* self = this;

    KeySlot* p = self->mpEnd;
    if (p < self->mpCap) {
        self->mpEnd = p + 1;
        if (p != 0) {
            p->mBits = 0x80000000u;
        }
    } else {
        KeySlot tmp;
        tmp.mBits = 0x80000000u;
        self->Insert(p, &tmp);
        u32 sign = tmp.mBits >> 31;
        if (sign == 0 && tmp.mpObj != 0)
            ((void(__fastcall*)(void*))(*(void***)tmp.mpObj)[1])(tmp.mpObj);
    }
}

// ===========================================================================
// 0x00b0e400 -- add agent to the +0x24 vector if not already present.
// ===========================================================================
// @ 0x00b0e400
bool cSkinner::AddAgent(void* agent)
{
    AgentVec* vec = (AgentVec*)((char*)this + 0x24);
    void** it = vec->mpBegin;
    void** end = vec->mpEnd;
    for (; it != end; ++it) {
        if (*it == agent)
            return false;
    }

    if (agent != 0)
        ((void(__fastcall*)(void*))(*(void***)agent)[0x60 / 4])(agent);

    void** p = vec->mpEnd;
    if (p < vec->mpCap) {
        vec->mpEnd = p + 1;
        if (p != 0) {
            *p = agent;
            if (agent == 0)
                return true;
            ((void(__fastcall*)(void*))(*(void***)agent)[0x60 / 4])(agent);
        }
    } else {
        ((VecGrowStub*)vec)->GrowOne(p, &agent);
    }

    if (agent != 0)
        ((void(__fastcall*)(void*))(*(void***)agent)[0x5c / 4])(agent);
    return true;
}

// ===========================================================================
// 0x00b0e490 -- allocate (or reuse) a KeySlot and store *value in it.
// ===========================================================================
// @ 0x00b0e490
u32 SlotVec::Acquire(void** value)
{
    SlotVec* self = this;

    u32 idx = self->mnLastReleased;
    if (idx == 0x3fffffffu) {
        void* obj = *value;
        if (obj != 0)
            ((void(__fastcall*)(void*))(*(void***)obj)[0])(obj);

        idx = (u32)(self->mpEnd - self->mpBegin);
        self->PushDefault();
        if (idx != 0) {
            KeySlot* last = self->mpBegin + idx - 1;
            last->mBits &= 0xbfffffffu;
        }
        KeySlot* slot = self->mpBegin + idx;
        slot->mBits |= 0x40000000u;
        slot->mBits &= 0x7fffffffu;
        slot->mpObj = obj;
        if (obj != 0)
            ((void(__fastcall*)(void*))(*(void***)obj)[0])(obj);
        if (obj != 0)
            ((void(__fastcall*)(void*))(*(void***)obj)[1])(obj);
    } else {
        KeySlot* slot = self->mpBegin + idx;
        self->mnLastReleased = slot->mBits & 0x3fffffffu;
        slot->mBits &= 0x7fffffffu;
        void* obj = *value;
        slot->mpObj = obj;
        if (obj != 0)
            ((void(__fastcall*)(void*))(*(void***)obj)[0])(obj);
    }
    if (idx < self->mnFreeHead)
        self->mnFreeHead = idx;
    return idx;
}
