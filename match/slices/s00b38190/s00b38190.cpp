// Slice 33: insertion sort of {RefObj*, float} pairs by a comparator functor (00b389f0).
#include "types.h"

// Refcounted object: +0 manager pointer (polymorphic; slot 0x170 frees the object),
// +4 flags (bit 31 is passed as the free flag), +0x40 reference count.
struct RcObj {
    void* mgr;
    uint32_t flags;
    char pad[0x38];
    int32_t refCount;
};

struct RcElem {
    RcObj* p;
    float f;
};

typedef void (__thiscall *RcFreeFn)(void* self, RcObj* o, int flag);

// Comparator functor (thiscall member, ret 8): 00b385d0.
struct SortCmp {
    int x;
    bool FUN_00b385d0(RcElem* a, RcElem* b) const; // 0x00b385d0 (thiscall, ret 8)
};

static inline void RcRelease(RcObj* o)
{
    if (o) {
        if (o->refCount < 2) {
            void* mgr = o->mgr;
            void** vt = *(void***)mgr;
            ((RcFreeFn)vt[0x170 / 4])(mgr, o, (o->flags >> 31) & 1);
        } else {
            o->refCount = o->refCount - 1;
        }
    }
}

// @ 0x00b389f0
void FUN_00b389f0(RcElem* first, RcElem* last, SortCmp cmp)
{
    for (RcElem* cur = first; cur != last; ++cur) {
        RcObj* keyP = cur->p;
        if (keyP) keyP->refCount++;
        RcElem key;
        key.p = keyP;
        key.f = cur->f;
        RcElem* h = cur;
        if (cmp.FUN_00b385d0(&key, cur - 1)) {
            bool c;
            do {
                RcElem* prev = h - 1;
                RcObj* a = prev->p;
                RcObj* b = h->p;
                if (a != b) {
                    if (a) a->refCount++;
                    h->p = a;
                    RcRelease(b);
                }
                h = prev;
                (h + 1)->f = h->f;
                c = cmp.FUN_00b385d0(&key, h - 1);
            } while (c);
        }
        RcObj* hp = h->p;
        if (keyP != hp) {
            if (keyP) keyP->refCount++;
            h->p = keyP;
            RcRelease(hp);
        }
        h->f = key.f;
        RcRelease(keyP);
    }
}
