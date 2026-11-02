// src/game/SPGonzago/InteractionTarget.cpp -- migrated from slice(s) s00ac0180 by tools/migrate/rewrite.py
// Object file: SPGonzago/InteractionTarget.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteractionTarget.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl operator_delete_array(void*);     // 0xf47380

// ---- items of slice s00ac0180 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
extern "C" void  __cdecl operator_delete_array(void*);     // 0xf47380
#define VTBL_01459be8  ((void*)0x1459be8)
struct RefObj {
    void* mpVftable;                                // +0x00
    u8    mPad04[0x04];                             // +0x04
    void* mpVftable2;                               // +0x08
};
struct InnerDeque {
    int* mpBlocks;                                  // +0x00
    u8   mPad04[0x08];                              // +0x04
    int* mpBegin;                                   // +0x0c
    int* mpEnd;                                     // +0x10
    int* mpCapacity;                                // +0x14
    int  mnCursor;                                  // +0x18
};
struct SlotEntry {
    void*      mpItem;                              // +0x00
    u8         mPad04[0x08];                        // +0x04
    InnerDeque mInner;                              // +0x0c
};
struct VecDtor {
    void dtor();                                    // 0xae6970
};
struct cInteractionTarget {
    void*  mpVftable;                               // +0x00
    void*  mpBegin;                                 // +0x04
    void*  mpEnd;                                   // +0x08
    void*  mpCapacity;                              // +0x0c

    cInteractionTarget* ctor();                     // 0xac03d0
    void   FUN_00ac0450();                          // 0xac0450
    void   FUN_00ac0520();                          // 0xac0520
    cInteractionTarget* FUN_00ac0540(char free);    // 0xac0540
};
// ---- items of slice s00ac0180 end

// @ 0x00ac0340
void __fastcall Object_virtual_dtor(RefObj* self, int* entry)
{
    int n = (int)(((char*)self->mpVftable2 - (char*)self->mpVftable) >> 2);
    if (n <= 0)
        return;
    RefObj** slots = (RefObj**)self->mpVftable;
    int i = 0;
    while ((int*)slots[i] != entry) {
        if (++i >= n)
            return;
    }
    RefObj** begin = (RefObj**)self->mpVftable;
    int  cnt   = (int)(((char*)self->mpVftable2 - (char*)self->mpVftable) >> 2);
    RefObj* lastv = begin[cnt - 1];
    RefObj* oldv  = begin[i];
    if (lastv != oldv) {
        if (lastv != 0)
            ((void(__fastcall*)(void*))(*(void***)lastv)[0])(lastv);
        begin[i] = lastv;
        if (oldv != 0)
            ((void(__fastcall*)(void*))(*(void***)oldv)[1])(oldv);
    }
    self->mpVftable2 = (void*)((char*)self->mpVftable2 - 4);
    RefObj* tail = *(RefObj**)self->mpVftable2;
    if (tail != 0)
        ((void(__fastcall*)(void*))(*(void***)tail)[1])(tail);
}

// @ 0x00ac03d0
cInteractionTarget* cInteractionTarget::ctor()
{
    mpVftable  = VTBL_01459be8;
    mpBegin    = 0;
    mpEnd      = 0;
    mpCapacity = 0;
    return this;
}

// @ 0x00ac03f0
void __cdecl FUN_00ac03f0(int* out, int* begin, u32 slot, int endA, int endB, int* target)
{
    extern void SlotIter_inc(u32*);                 // 0xabe9b0 iterator::operator++
    while (endB + endA != (int)slot + (int)begin) {
        if (*(int*)(*(int*)(*begin + (slot >> 7) * 4) + 4 + (slot & 0x7f) * 8) == *target)
            break;
        SlotIter_inc(&slot);
    }
    *out = (int)begin;
    out[1] = (int)slot;
}

// @ 0x00ac0450
void cInteractionTarget::FUN_00ac0450()
{
    SlotEntry* base = (SlotEntry*)this;
    SlotEntry** beginp = (SlotEntry**)((char*)this + 4);
    SlotEntry** endp   = (SlotEntry**)((char*)this + 8);
    if (*beginp == *endp)
        return;
    SlotEntry* cur = 0;
    do {
        SlotEntry* elem = *(SlotEntry**)*beginp;
        SlotEntry* prev = cur;
        if (elem != cur) {
            if (elem != 0)
                ((void(__fastcall*)(void*))(*(void***)elem)[0])(elem);
            prev = elem;
            if (cur != 0)
                ((void(__fastcall*)(void*))(*(void***)cur)[1])(cur);
        }
        cur = prev;
        InnerDeque* dq = &cur->mInner;
        int n    = (int)((dq->mpEnd - dq->mpBegin) >> 2);
        int cap  = (int)dq->mpCapacity;
        int limit = (n << 7) + cap - 0x7f;
        int slot = dq->mnCursor;
        int use  = ((u32)slot < 0x3fffffff) ? slot : limit;
        struct Pair { int x, y; } it;
        FUN_00ac03f0(&it.x, (int*)dq, (u32)use, (int)dq, limit, (int*)&cur);
        if (limit + (int)dq != it.y + it.x)
            ((void(__fastcall*)(void*, int, int))(*(void***)cur)[0x50 / 4])(
                (void*)&it, it.x, it.y);
        cur = prev;
    } while (*beginp != *endp);
    if (cur != 0)
        ((void(__fastcall*)(void*))(*(void***)cur)[1])(cur);
}

// @ 0x00ac0520
void cInteractionTarget::FUN_00ac0520()
{
    mpVftable = VTBL_01459be8;
    FUN_00ac0450();
    ((VecDtor*)((char*)this + 4))->dtor();
}

// @ 0x00ac0540
cInteractionTarget* cInteractionTarget::FUN_00ac0540(char free)
{
    mpVftable = VTBL_01459be8;
    FUN_00ac0450();
    ((VecDtor*)((char*)this + 4))->dtor();
    if (free & 1)
        operator_delete_array(this);
    return this;
}
