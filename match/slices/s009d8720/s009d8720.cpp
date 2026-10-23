// Slice s009d8720 -- Gait copy ctor + eastl vector<Step> / merge / merge_sort internals.
// Module flags: /O2 /MD /Gy /TP  (no C++ EH: originals carry no unwind frames)
#include "types.h"
#include <stddef.h>
#include <new>

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------- masked externs
void* __cdecl EAAllocate(unsigned size, const char* tag, int a, int b, int c, int d); // 0x00f473a0
void* __cdecl mem_copy(void* dst, const void* src, unsigned n);                        // 0x011e0744 (memcpy)

struct Step;
struct Gait;

Step* __cdecl uninit_copy_step(Step* first, Step* last, Step* dst);        // 0x009d7f20
Step* __cdecl copy_backward_step(Step* first, Step* last, Step* dst);      // 0x009d7fa0
Step* __cdecl uninit_move_step(Step* first, Step* last, Step* dst);        // 0x009d7ee0
Step* __cdecl destroy_move_step(Step* first, Step* last, Step* dst);       // 0x009d6aa0
void  __cdecl destroy_step(Step* first, Step* last);                       // 0x009c15f0
Step* __cdecl copy_step(Step* first, Step* last, Step* dst);               // 0x009d6a70
void* __cdecl uninit_copy_slot(void** slot, Step* first, Step* last, Step* dst, const void* extra); // 0x009d7ea0
// ---------------------------------------------------------------- element types
struct Vec32 {
    u32*  begin;   // +0x00
    u32*  end;     // +0x04
    u32*  cap;     // +0x08
    void* alloc;   // +0x0c
    Vec32() : begin(0), end(0), cap(0), alloc(0) {}
    Vec32* init_count(u32 n, const void* a);                            // 0x00a69430
    __forceinline Vec32(const Vec32& o) {
        init_count((u32)(o.end - o.begin), &o.alloc);
        ptrdiff_t bytes = (const char*)o.end - (const char*)o.begin;
        u32*      dst   = begin;
        u32* p = (u32*)mem_copy(dst, o.begin, (unsigned)bytes);
        end = p + (bytes >> 2);
    }
};

struct StepSub {
    u32*  begin;   // +0x00
    u32*  end;     // +0x04
    u32*  cap;     // +0x08
    void* alloc;   // +0x0c
    StepSub() : begin(0), end(0), cap(0), alloc(0) {}
    StepSub& operator=(const StepSub& o);                               // 0x009d7bb0
};

struct Step {
    void*  obj;       // +0x00
    StepSub sub;      // +0x04
    u32    unused14;  // +0x14
    float  f18;       // +0x18
    float  f1c;       // +0x1c
    float  f20;       // +0x20
    u8     b24;       // +0x24
    u8     pad25[3];
    float  f28;       // +0x28
    float  f2c;       // +0x2c
    float  f30;       // +0x30
    float  f34;       // +0x34

    Step() : obj(0), unused14(0), f18(0.f), f1c(0.f), f20(0.f), b24(0),
             f28(0.f), f2c(0.f), f30(0.f), f34(0.f) {}
    Step(const Step& o);                                                // 0x009d7dd0

    Step& operator=(const Step& o) {
        obj = o.obj;
        sub = o.sub;
        f18 = o.f18;
        f1c = o.f1c;
        f20 = o.f20;
        b24 = o.b24;
        f28 = o.f28;
        f2c = o.f2c;
        f30 = o.f30;
        f34 = o.f34;
        return *this;
    }
};

struct GaitSub {
    Step* begin;   // +0x00
    Step* end;     // +0x04
    Step* cap;     // +0x08
    void* alloc;   // +0x0c
    GaitSub() : begin(0), end(0), cap(0), alloc(0) {}
    GaitSub(const GaitSub& o);                                          // 0x009d86c0
};

struct Gait {
    u32 a00, a04, a08, a0c;                                             // +0x00
    float f10, f14, f18, f1c, f20, f24, f28, f2c;                       // +0x10
    float f30, f34, f38, f3c, f40, f44;                                 // +0x30
    u32 a48;                                                            // +0x48
    GaitSub sub;                                                        // +0x4c
    u32 pad5c;                                                          // +0x5c
    float f60, f64, f68, f6c, f70, f74, f78, f7c;                       // +0x60
    float f80, f84, f88, f8c, f90, f94, f98, f9c;                       // +0x80
    float fa0, fa4, fa8, fac, fb0, fb4;                                 // +0xa0
    u32 ab8;                                                            // +0xb8
    Vec32 v;                                                            // +0xbc
    u32 padcc;                                                          // +0xcc
    float fd0, fd4, fd8, fdc, fe0, fe4, fe8, fec;                       // +0xd0
    float ff0, ff4, ff8, ffc, f100;                                     // +0xf0

    Gait(const Gait& o);                                                // 0x009d8720
};

struct GaitCmp1 { bool operator()(Gait a, Gait b) const; };             // 0x009d7840
struct GaitCmp2 { bool operator()(Gait a, Gait b) const; };             // 0x009d7920

// ---------------------------------------------------------------- Gait copy ctor
// @ 0x009d8720 Gait::Gait
Gait::Gait(const Gait& o)
  : a00(o.a00), a04(o.a04), a08(o.a08), a0c(o.a0c),
    f10(o.f10), f14(o.f14), f18(o.f18), f1c(o.f1c), f20(o.f20), f24(o.f24),
    f28(o.f28), f2c(o.f2c), f30(o.f30), f34(o.f34), f38(o.f38), f3c(o.f3c),
    f40(o.f40), f44(o.f44),
    a48(o.a48), sub(o.sub),
    f60(o.f60), f64(o.f64), f68(o.f68), f6c(o.f6c), f70(o.f70), f74(o.f74),
    f78(o.f78), f7c(o.f7c), f80(o.f80), f84(o.f84), f88(o.f88), f8c(o.f8c),
    f90(o.f90), f94(o.f94), f98(o.f98), f9c(o.f9c), fa0(o.fa0), fa4(o.fa4),
    fa8(o.fa8), fac(o.fac), fb0(o.fb0), fb4(o.fb4),
    ab8(o.ab8), v(o.v),
    fd0(o.fd0), fd4(o.fd4), fd8(o.fd8), fdc(o.fdc), fe0(o.fe0), fe4(o.fe4),
    fe8(o.fe8), fec(o.fec), ff0(o.ff0), ff4(o.ff4), ff8(o.ff8), ffc(o.ffc),
    f100(o.f100)
{
}

// ---------------------------------------------------------------- merges
// @ 0x009d8980 merge_by_subcount
void merge_by_subcount(Step* f1, Step* l1, Step* f2, Step* l2, Step* out, GaitCmp1 cmp)
{
    while (f1 != l1 && f2 != l2) {
        u32 c1 = (u32)(f1->sub.end - f1->sub.begin);
        u32 c2 = (u32)(f2->sub.end - f2->sub.begin);
        if (c2 <= c1) {
            *out = *f1;
            ++f1;
        } else {
            *out = *f2;
            ++f2;
        }
        ++out;
    }
    Step* e = uninit_copy_step(f1, l1, out);
    uninit_copy_step(f2, l2, e);
}

// @ 0x009d8ab0 merge_by_key
void merge_by_key(Step* f1, Step* l1, Step* f2, Step* l2, Step* out, GaitCmp2 cmp)
{
    while (f1 != l1 && f2 != l2) {
        float k2 = *(float*)((char*)f2->obj + 0x110);
        float k1 = *(float*)((char*)f1->obj + 0x110);
        if (k2 <= k1) {
            *out = *f1;
            ++f1;
        } else {
            *out = *f2;
            ++f2;
        }
        ++out;
    }
    Step* e = uninit_copy_step(f1, l1, out);
    uninit_copy_step(f2, l2, e);
}

// ---------------------------------------------------------------- median of three
// @ 0x009d8be0 select_median_subcount
Gait* select_median_subcount(Gait* a, Gait* b, Gait* c, GaitCmp1 cmp)
{
    if (cmp(*a, *b)) {
        if (cmp(*b, *c))
            return b;
        if (cmp(*a, *c))
            return c;
        return a;
    } else {
        if (cmp(*a, *c))
            return a;
        if (cmp(*b, *c))
            return c;
        return b;
    }
}

// @ 0x009d8ce0 select_median_key
Gait* select_median_key(Gait* a, Gait* b, Gait* c, GaitCmp2 cmp)
{
    if (cmp(*a, *b)) {
        if (cmp(*b, *c))
            return b;
        if (cmp(*a, *c))
            return c;
        return a;
    } else {
        if (cmp(*a, *c))
            return a;
        if (cmp(*b, *c))
            return c;
        return b;
    }
}

// ---------------------------------------------------------------- vector<Step>
struct VectorStep {
    Step* begin;   // +0x00
    Step* end;     // +0x04
    Step* cap;     // +0x08
    void* alloc;   // +0x0c

    Step* alloc_n_copy(u32 n, const Step* first, const Step* last);      // 0x009d8660
    Step* erase(Step* first, Step* last);
    void  destroy(Step* first, Step* last);                             // 0x009c15f0
    void  insert(Step* pos, const Step& value);
    VectorStep& operator=(const VectorStep& o);
};

// @ 0x009d8e20 VectorStep::erase
Step* VectorStep::erase(Step* first, Step* last)
{
    Step* newend = uninit_copy_step(last, end, first);
    destroy(newend, end);
    end -= last - first;
    return first;
}

// @ 0x009d8e80 VectorStep::insert
void VectorStep::insert(Step* pos, const Step& value)
{
    if (end != cap) {
        const Step* v = &value;
        if (v >= pos && v < end)
            ++v;
        if (end)
            new (end) Step(*(end - 1));
        copy_backward_step(pos, end - 1, end);
        *pos = *v;
        ++end;
        return;
    }

    u32 n = (u32)(end - begin);
    u32 ncap = (n == 0) ? 1 : n * 2;
    Step* buf = ncap ? (Step*)EAAllocate(ncap * 0x38, "Anim/gait/untagged", 0, 0, 0x13ebb38, 0xd1) : 0;

    Step* mid = uninit_move_step(begin, pos, buf);
    destroy_move_step(begin, pos, buf);
    if (mid)
        new (mid) Step(value);
    Step* newend = uninit_move_step(pos, end, mid + 1);
    destroy_move_step(pos, end, mid + 1);

    if (begin != 0 && ((int*)begin)[-1] != 0)
        ::operator delete(begin);

    end   = newend;
    begin = buf;
    cap   = buf + ncap;
}

// @ 0x009d8fd0 VectorStep::operator=
VectorStep& VectorStep::operator=(const VectorStep& o)
{
    if (this != &o) {
        u32 n = (u32)(o.end - o.begin);
        if (n > (u32)(cap - begin)) {
            Step* p = alloc_n_copy(n, o.begin, o.end);
            destroy(begin, end);
            if (begin != 0 && ((int*)begin)[-1] != 0)
                ::operator delete(begin);
            begin = p;
            cap   = p + n;
        } else if (n > (u32)(end - begin)) {
            Step* dst = end;
            uninit_copy_step(o.begin, o.begin + (end - begin), begin);
            void* slot;
            uninit_copy_slot(&slot, o.begin + (end - begin), o.end, dst, &o);
        } else {
            Step* newend = uninit_copy_step(o.begin, o.end, begin);
            destroy_step(newend, end);
        }
        end = begin + n;
    }
    return *this;
}

// ---------------------------------------------------------------- merge sort
// @ 0x009d9120 merge_sort_subcount
void merge_sort_subcount(Step* first, Step* last, Step* buffer, GaitCmp1 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        ptrdiff_t h = n / 2;
        Step* mid = first + h;

        if (h > 1) {
            ptrdiff_t q = h / 2;
            merge_sort_subcount(first, first + q, buffer, cmp);
            merge_sort_subcount(first + q, mid, buffer + q, cmp);
            merge_by_subcount(first, first + q, first + q, mid, buffer, cmp);
        } else {
            *buffer = *first;
        }

        if (n - h > 1) {
            ptrdiff_t q = (h + n) / 2;
            merge_sort_subcount(mid, first + q, buffer + h, cmp);
            merge_sort_subcount(first + q, last, buffer + q, cmp);
            merge_by_subcount(mid, first + q, first + q, last, buffer + h, cmp);
        } else {
            *(buffer + h) = *mid;
        }

        merge_by_subcount(buffer, buffer + h, buffer + h, buffer + n, first, cmp);
    }
}

// @ 0x009d92a0 merge_sort_key
void merge_sort_key(Step* first, Step* last, Step* buffer, GaitCmp2 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        ptrdiff_t h = n / 2;
        Step* mid = first + h;

        if (h > 1) {
            ptrdiff_t q = h / 2;
            merge_sort_key(first, first + q, buffer, cmp);
            merge_sort_key(first + q, mid, buffer + q, cmp);
            merge_by_key(first, first + q, first + q, mid, buffer, cmp);
        } else {
            *buffer = *first;
        }

        if (n - h > 1) {
            ptrdiff_t q = (h + n) / 2;
            merge_sort_key(mid, first + q, buffer + h, cmp);
            merge_sort_key(first + q, last, buffer + q, cmp);
            merge_by_key(mid, first + q, first + q, last, buffer + h, cmp);
        } else {
            *(buffer + h) = *mid;
        }

        merge_by_key(buffer, buffer + h, buffer + h, buffer + n, first, cmp);
    }
}

// ---------------------------------------------------------------- stable sort
// @ 0x009d9420 stable_sort_subcount
void stable_sort_subcount(Step* first, Step* last, GaitCmp1 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        Step* buf = (Step*)EAAllocate((u32)(n * 0x38), "Anim/gait/untagged", 0, 0, 0x13ebb38, 0xd1);
        Step  empty;
        Step* e = buf + n;
        for (Step* p = buf; p != e; ++p)
            new (p) Step(empty);
        merge_sort_subcount(first, last, buf, cmp);
        copy_step(buf, e, last);
        ::operator delete(buf);
    }
}

// @ 0x009d9520 stable_sort_key
void stable_sort_key(Step* first, Step* last, GaitCmp2 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        Step* buf = (Step*)EAAllocate((u32)(n * 0x38), "Anim/gait/untagged", 0, 0, 0x13ebb38, 0xd1);
        Step  empty;
        Step* e = buf + n;
        for (Step* p = buf; p != e; ++p)
            new (p) Step(empty);
        merge_sort_key(first, last, buf, cmp);
        copy_step(buf, e, last);
        ::operator delete(buf);
    }
}
