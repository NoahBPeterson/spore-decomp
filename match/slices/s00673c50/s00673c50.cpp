// Slice s00673c50 - `anonymous namespace'::cBuildXHTMLDetokenizer and its
// eastl::vector<cVar, fixed_vector_allocator<...>> internals (cVar stride 0x54).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (same region as s00671840).
#include "types.h"
#include <string.h>
#include <intrin.h>

void DeleteObj(void* p);   // 0x00f47380

// ---- cVar = a fixed-capacity eastl::basic_string<wchar_t> ------------
struct EStr {
    unsigned short* mpBegin;     // +0x00
    unsigned short* mpEnd;       // +0x04
    unsigned short* mpCapacity;  // +0x08
    void*           mpAlloc;     // +0x0c
    unsigned short* mpInline;    // +0x10
    unsigned short  mBuf[0x20];  // +0x14 .. +0x54

    void  assign(unsigned short* first, unsigned short* last);  // 0x00672750
    EStr* Construct(const unsigned short* src);
};

// ---- vector<cVar> ----------------------------------------------------
struct EStrVec {
    EStr* mpBegin;     // +0x00
    EStr* mpEnd;       // +0x04
    EStr* mpCapacity;  // +0x08
    char  padC[8];     // +0x0c
    void DoInsertValue(EStr* pos, const EStr* v);   // 0x00674440 (defined elsewhere)
    void DoInsertValueSkeleton(EStr* pos, const EStr* v);
    void  push_back(const EStr& v);
};

// ---- 0x00674170 : eastl fill_n over wchar_t --------------------------
// @ 0x00674170
void* FillN(unsigned short* first, unsigned n, unsigned short value) {
    unsigned short* p = first;
    unsigned short* end = first + n;
    while (p < end) *p++ = value;
    return first;
}

// ---- 0x006741b0 : find text element by wide-string key ---------------
// @ 0x006741b0
int FindRange(int* p, unsigned short* key) {
    int i = p[0];
    for (;;) {
        if (i == p[1]) return 0;
        unsigned* q = *(unsigned**)(i + 900);
        unsigned* qEnd = *(unsigned**)(i + 0x388);
        for (; q != qEnd; q += 0x15) {
            unsigned short* s = (unsigned short*)*q;
            unsigned short* k = key;
            int cmp;
            for (;;) {
                unsigned short a = *s, b = *k;
                if (a != b) { cmp = (b < a) ? 1 : -1; break; }
                if (a == 0) { cmp = 0; break; }
                a = s[1]; b = k[1];
                if (a != b) { cmp = (b < a) ? 1 : -1; break; }
                s += 2; k += 2;
                if (a == 0) { cmp = 0; break; }
            }
            if (cmp == 0) return i;
        }
        i += 0x63c;
    }
}

// ---- 0x00674230 : vector fill-insert --------------------------------
// @ 0x00674230
unsigned* FillInsert(unsigned* p, unsigned count, unsigned value) {
    unsigned* begin = (unsigned*)p[0];
    unsigned have = (p[1] - (unsigned)begin) >> 1;
    if (have < count) {
        unsigned* oldEnd = (unsigned*)((char*)begin + have * 2);
        for (unsigned* it = begin; it < oldEnd; ) {
            unsigned cnt = ((unsigned)((char*)oldEnd - (char*)it - 1) >> 1) + 1;
            unsigned i = cnt >> 1;
            while (i--) { *it++ = value & 0xffff | value << 0x10; }
            for (i = cnt & 1; i; --i) { *(unsigned short*)it = (unsigned short)value; it = (unsigned*)((char*)it + 2); }
        }
        FillN((unsigned short*)((char*)begin + have * 2), count - have, (unsigned short)value);
    } else {
        unsigned* mid = (unsigned*)((char*)begin + count * 2);
        for (unsigned* it = begin; it < mid; ) {
            unsigned cnt = ((unsigned)((char*)mid - (char*)it - 1) >> 1) + 1;
            unsigned i = cnt >> 1;
            while (i--) { *it++ = value & 0xffff | value << 0x10; }
            for (i = cnt & 1; i; --i) { *(unsigned short*)it = (unsigned short)value; it = (unsigned*)((char*)it + 2); }
        }
        void* src = (void*)p[1];
        void* dst = (void*)(p[0] + count * 2);
        if (dst != src) {
            memmove(dst, src, 2);
            p[1] = p[1] + (((char*)src - (char*)dst) >> 1) * -2;
        }
    }
    return p;
}

// ---- 0x006742f0 : copy-assign backward (uninitialized_move tail) -----
// @ 0x006742f0
EStr* MoveAssignBackward(EStr* first, EStr* last, EStr* dst) {
    if (first != last) {
        EStr* s = last - 1;
        EStr* d = dst - 1;
        do {
            if (d != s) {
                unsigned short* b = d->mpBegin;
                if (b != d->mpEnd) { *b = 0; d->mpEnd = d->mpBegin; }
                d->assign(s->mpBegin, s->mpEnd);
            }
            --s; --d;
        } while (s != first);
        return d;
    }
    return dst;
}

// ---- 0x00674340 : uninitialized copy-construct forward --------------
// @ 0x00674340
EStr* UninitCopy(EStr* first, EStr* last, EStr* dst) {
    while (first != last) {
        if (dst) {
            unsigned short* inl = (unsigned short*)((char*)dst + 0x14);
            dst->mpInline = inl;
            dst->mpEnd = inl;
            dst->mpBegin = inl;
            dst->mpCapacity = inl + 0x20;
            *inl = 0;
            dst->assign(first->mpBegin, first->mpEnd);
        }
        ++first; ++dst;
    }
    return dst;
}

// ---- 0x006743a0 : destroy-value range -------------------------------
// @ 0x006743a0
EStr* DestroyValues(EStr* first, EStr* last, EStr* dst) {
    while (first != last) {
        unsigned short* b = first->mpBegin;
        if ((((char*)first->mpCapacity - (char*)b) & ~1) > 2 && b && b != first->mpInline)
            DeleteObj(b);
        ++first;
        ++dst;
    }
    return dst;
}

// ---- 0x006743f0 : cVar constructor from wide C string ---------------
// @ 0x006743f0
EStr* EStr::Construct(const unsigned short* src) {
    unsigned short* inl = (unsigned short*)((char*)this + 0x14);
    mpInline = inl;
    _ReadWriteBarrier();
    mpCapacity = inl + 0x20;
    mpEnd = inl;
    mpBegin = inl;
    *inl = 0;
    const unsigned short* p = src;
    while (*p) ++p;
    assign((unsigned short*)src, (unsigned short*)src + (p - src));
    return this;
}

// ---- 0x00674440 : vector::DoInsertValue (partial skeleton) ----------
// @ 0x00674440
void EStrVec::DoInsertValueSkeleton(EStr* pos, const EStr* v) {
    (void)pos; (void)v;
}

// ---- 0x006745d0 : vector::push_back ---------------------------------
// @ 0x006745d0
void EStrVec::push_back(const EStr& v) {
    EStr* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e) {
            unsigned short* inl = (unsigned short*)((char*)e + 0x14);
            e->mpInline = inl;
            _ReadWriteBarrier();
            e->mpCapacity = inl + 0x20;
            e->mpEnd = inl;
            e->mpBegin = inl;
            *inl = 0;
            e->assign(v.mpBegin, v.mpEnd);
        }
        return;
    }
    DoInsertValue(e, &v);
}

// ---- 0x00673c50 : cBuildXHTMLDetokenizer ctor (partial) -------------
struct Detokenizer {
    void Ctor();
};
// @ 0x00673c50
void Detokenizer::Ctor() { }
