// Slice s008387c0 (w2g7 #41), 32-bit MSVC 2008 SP1.
// EA::ArgScript argument spec + eastl string/vector copy helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void  __cdecl DoInsertValue(char*, const char*, uint32_t);   // 0x11e0744
void  __cdecl RangeInitRaw(void*, uint32_t);                 // 0x475ab0
char* __cdecl SearchStr(void*, void*, void*, void*);         // 0x609d50
template <typename T> static const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }

// ---------------------------------------------------------------------------
// eastl::basic_string<char>
// ---------------------------------------------------------------------------
struct RawStr {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;

    void RangeInitialize(uint32_t n);                 // 0x475ab0
    void Assign(const char* first, const char* last); // 0x454cb0
    RawStr(const RawStr& s, uint32_t pos, uint32_t n); // 0x8389f0
    int  Find(const char* p, uint32_t pos);           // 0x838a60
};

// @ 0x008389f0
RawStr::RawStr(const RawStr& s, uint32_t pos, uint32_t n) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    uint32_t rem = (uint32_t)(s.mpEnd - s.mpBegin) - pos;
    const uint32_t& cnt = min_alt(rem, n);
    char* src = s.mpBegin + pos;
    char* end = src + cnt;
    uint32_t len = (uint32_t)(end - src);
    RangeInitialize(len + 1);
    char* dst = mpBegin;
    DoInsertValue(dst, src, len);
    mpEnd = dst + len;
    *mpEnd = 0;
}

// @ 0x00838a60
int RawStr::Find(const char* p, uint32_t pos) {
    const char* e = p;
    while (*e) ++e;
    char* begin = mpBegin;
    char* end = mpEnd;
    if (pos < (uint32_t)(end - begin)) {
        char* r = SearchStr(begin + pos, end, (void*)p, (void*)e);
        if (r != end) return (int)(r - begin);
    }
    return -1;
}

// ---------------------------------------------------------------------------
// structured element types
// ---------------------------------------------------------------------------
struct Ent {                 // 0x20 bytes
    int    field0;           // +0
    RawStr name;             // +4
    int    field14;          // +0x14
    bool   field18;          // +0x18
    char   pad[3];
    int    field1c;          // +0x1c
};

struct Ent2 {                // 0x18 bytes
    RawStr name;             // +0
    int    field10;          // +0x10
    int    field14;          // +0x14
};

struct Vec2 {
    float x, y;
    Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; }
};

// @ 0x00838ab0
Ent* CopyEnt(Ent* dst, const Ent* src) {
    dst->field0 = src->field0;
    dst->name.mpBegin = 0;
    dst->name.mpEnd = 0;
    dst->name.mpCapacity = 0;
    uint32_t size = (uint32_t)(src->name.mpEnd - src->name.mpBegin);
    dst->name.RangeInitialize(size + 1);
    char* dstp = dst->name.mpBegin;
    DoInsertValue(dstp, src->name.mpBegin, size);
    dst->name.mpEnd = dstp + (src->name.mpEnd - src->name.mpBegin);
    *dst->name.mpEnd = 0;
    dst->field14 = src->field14;
    dst->field18 = src->field18;
    dst->field1c = src->field1c;
    return dst;
}

// @ 0x00838b90
Vec2* CopyVec2(Vec2* first, Vec2* last, Vec2* dst) {
    if (first != last) {
        int off = (int)((char*)first - (char*)dst);
        do {
            if (dst) *dst = *(Vec2*)(off + (char*)dst);
            ++dst;
        } while ((Vec2*)(off + (char*)dst) != last);
    }
    return dst;
}

// @ 0x00838e80
Ent* DestroyEnts(Ent* first, Ent* last, Ent* dst) {
    if (first != last) {
        do {
            char* b = first->name.mpBegin;
            if ((first->name.mpCapacity - b) > 1 && b) operator_delete__(b);
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838f20
Ent* CopyEntsFwd(Ent* first, Ent* last, Ent* dst) {
    if (first != last) {
        do {
            dst->field0 = first->field0;
            if (&first->name != &dst->name) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field14 = first->field14;
            dst->field18 = first->field18;
            dst->field1c = first->field1c;
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838f80
Ent* CopyEntsBwd(Ent* first, Ent* last, Ent* dst) {
    if (first != last) {
        do {
            first -= 1;
            dst -= 1;
            dst->field0 = first->field0;
            if (&first->name != &dst->name) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field14 = first->field14;
            dst->field18 = first->field18;
            dst->field1c = first->field1c;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838ff0
Ent2* CopyEnts2Fwd(Ent2* first, Ent2* last, Ent2* dst) {
    if (first != last) {
        do {
            if (first != dst) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field10 = first->field10;
            dst->field14 = first->field14;
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00839040
Ent2* CopyEnts2Bwd(Ent2* first, Ent2* last, Ent2* dst) {
    if (first != last) {
        do {
            first -= 1;
            dst -= 1;
            if (first != dst) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field10 = first->field10;
            dst->field14 = first->field14;
        } while (first != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00838de0  (assign sub-range)
// ---------------------------------------------------------------------------
void FUN_00838de0(RawStr* p, uint32_t pos, uint32_t n) {
    char* begin = p->mpBegin;
    uint32_t rem = (uint32_t)(p->mpEnd - begin) - pos;
    const uint32_t& cnt = min_alt(rem, n);
    p->Assign(begin + pos, begin + pos + cnt);
}

// ---------------------------------------------------------------------------
// complex / partial bodies
// ---------------------------------------------------------------------------
int  FUN_008387c0(void* self, char* name) { (void)self; (void)name; return 0; }
void FUN_00838cd0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
void FUN_00839090(void* a, void* b, char* c) { (void)a; (void)b; (void)c; }
void FUN_008392b0(int a, int b, int c, char* d, int e) { (void)a; (void)b; (void)c; (void)d; (void)e; }
void FUN_008393a0(int a, int b, int* c, int d) { (void)a; (void)b; (void)c; (void)d; }
void FUN_00839540(void* self, char* a, void* b, char* c) { (void)self; (void)a; (void)b; (void)c; }
void FUN_008397a0(void* self, uint32_t t) { (void)self; (void)t; }
