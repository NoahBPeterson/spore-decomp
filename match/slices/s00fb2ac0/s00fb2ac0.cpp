#include "types.h"

// ---------------------------------------------------------------------------
// helpers / declarations
// ---------------------------------------------------------------------------
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b,
                         const char* file, int line);
void  __cdecl operator delete(void* p);

struct E8  {
    float x, y;
    __forceinline E8& operator=(const E8& o) { x = o.x; y = o.y; return *this; }
};
struct E200 {
    float a0, a1, a2, a3, a4, a5, a6, a7, a8;
    int   i24;
    float b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
    int   i54;
    float c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
    int   i84;
    float d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
    int   ib4;
    float ab8, abc;
    int   ic0;
    char  cc4;
    __forceinline E200& operator=(const E200& o)
    {
        a0 = o.a0;
        a1 = o.a1;
        a2 = o.a2;
        a3 = o.a3;
        a4 = o.a4;
        a5 = o.a5;
        a6 = o.a6;
        a7 = o.a7;
        a8 = o.a8;
        i24 = o.i24;
        b0 = o.b0;
        b1 = o.b1;
        b2 = o.b2;
        b3 = o.b3;
        b4 = o.b4;
        b5 = o.b5;
        b6 = o.b6;
        b7 = o.b7;
        b8 = o.b8;
        b9 = o.b9;
        b10 = o.b10;
        i54 = o.i54;
        c0 = o.c0;
        c1 = o.c1;
        c2 = o.c2;
        c3 = o.c3;
        c4 = o.c4;
        c5 = o.c5;
        c6 = o.c6;
        c7 = o.c7;
        c8 = o.c8;
        c9 = o.c9;
        c10 = o.c10;
        i84 = o.i84;
        d0 = o.d0;
        d1 = o.d1;
        d2 = o.d2;
        d3 = o.d3;
        d4 = o.d4;
        d5 = o.d5;
        d6 = o.d6;
        d7 = o.d7;
        d8 = o.d8;
        d9 = o.d9;
        d10 = o.d10;
        ib4 = o.ib4;
        ab8 = o.ab8;
        abc = o.abc;
        ic0 = o.ic0;
        cc4 = o.cc4;
        return *this;
    }
};
struct E40 { unsigned d[10]; };
struct Ep200 { unsigned d[50]; };
struct E28 { float f[9]; char c; char pad[3]; };
struct E48 { unsigned d[12]; };
struct E16 { unsigned d[4]; };

// generic vector of trivially-copyable elements
struct Vec200 {
    Ep200* begin;
    Ep200* end;
    Ep200* cap;
    Ep200* erase(Ep200* first, Ep200* last);
};

// 40-byte element vector (GlyphDisplayEntry)
struct Vec40 {
    E40*  begin;
    E40*  end;
    E40*  cap;
    E40*  erase(E40* first, E40* last);
};

// 8-byte element vector with allocator
struct Vec8 {
    E8*   begin;
    E8*   end;
    E8*   cap;
    void* buf;
    int   line;
    void  insert(E8* position, const E8* value);
};

// 40-byte element vector used by the original insert helper family
struct Vec28 {
    E28*  begin;
    E28*  end;
    E28*  cap;
    void  insert(E28* position, unsigned n, const E28* value);
};

// 48-byte element vector
struct Vec48 {
    E48*  begin;
    E48*  end;
    E48*  cap;
    void  reserve(unsigned n);
    void  insert(E48* position, const E48* value);
};

struct Mgr {
    char  pad0[8];
    void* child[4];     // +0x08
    char  pad18[0x91 - 0x18];
    char  dirty;        // +0x91
    char  pad92[0x154 - 0x92];
    E16*  begin;        // +0x154
    E16*  end;          // +0x158
    char  pad15c[0x168 - 0x15c];
    unsigned maskA;     // +0x168
    unsigned maskB;     // +0x16c
    void  remove(int id);
};

struct Viewer;
struct Stats { char pad[0x2c]; };

// external helpers used by the render walk
void __stdcall Fb1780(void* arg);
void __cdecl   F48a60();
void __stdcall F7c3d30(void* a, void* b, void* c, void* d);
void __stdcall Faed90();
void __stdcall Ffaf4e0(int type, void* out, unsigned v);
void __cdecl   F777ae0(int a, void* b, int c);
void __stdcall Faef10(unsigned a, void* b, int c, unsigned d);
void __stdcall Fc2830();

E8*   __cdecl UninitCopy8Destruct(E8* first, E8* last, E8* dst);
E28*  __cdecl CopyElems28(E28* first, E28* last, E28* dst);
E28*  __cdecl FillElems28(E28* dst, unsigned n, const E28* val);
void  __cdecl MoveElems28(E28* first, E28* last, E28* dst);
E48*  __cdecl CopyE48(E48* first, E48* last, E48* dst);
void  __cdecl FUN_00762a30(void* p);
void  __stdcall FUN_00fb29f0(const void* p);

struct Renderer { int walk(Viewer* v, int a, Stats* s); };

struct Clip { char pad[0x14]; int id; void* obj; };
struct RenderNode { char pad[0x154]; };

// ---------------------------------------------------------------------------
// 0x00fb2ac0  copy(first,last,result) with hidden result slot
// ---------------------------------------------------------------------------
// @ 0x00fb2ac0
void* __cdecl CopyR200(void** out, E200* first, E200* last, E200* result)
{
    *out = result;
    if (first != last) {
        do {
            if (result) *result = *first;
            ++first;
            ++result;
        } while (first != last);
        *out = result;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00fb2ca0  fill(dst,count,src)
// ---------------------------------------------------------------------------
// @ 0x00fb2ca0
void __cdecl Fill200(E200* dst, unsigned count, const E200* src)
{
    if (!count) return;
    do {
        if (dst) *dst = *src;
        ++dst;
        --count;
    } while (count);
}

// ---------------------------------------------------------------------------
// 0x00fb2e70  copy_backward over [first,last) into result
// ---------------------------------------------------------------------------
// @ 0x00fb2e70
E200* __cdecl CopyB200(E200* first, E200* last, E200* dummy, E200* result)
{
    (void)dummy;
    E200* out = result;
    while (first != last) {
        if (result) *result = *first;
        ++first;
        ++result;
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00fb3240  vector<E200>::erase
// ---------------------------------------------------------------------------
// @ 0x00fb3240
Ep200* Vec200::erase(Ep200* first, Ep200* last)
{
    Ep200* i = first;
    Ep200* j = last;
    while (j != end) {
        *i = *j;
        ++i;
        ++j;
    }
    int n = (int)(last - first);
    end = end + n;
    return first;
}

// ---------------------------------------------------------------------------
// 0x00fb32b0  vector<E40>::erase
// ---------------------------------------------------------------------------
// @ 0x00fb32b0
E40* Vec40::erase(E40* first, E40* last)
{
    E40* i = first;
    E40* j = last;
    while (j != end) {
        *i = *j;
        ++i;
        ++j;
    }
    int n = (int)(last - first);
    end = end + n;
    return first;
}

// ---------------------------------------------------------------------------
// 0x00fb3320  vector<E8>::insert(position, value)
// ---------------------------------------------------------------------------
// @ 0x00fb3320
void Vec8::insert(E8* position, const E8* value)
{
    if (end != cap) {
        if (value >= position && value < end)
            value += 1;
        if (end)
            *end = *(end - 1);
        E8* p = end;
        while (p != position) {
            p[-1] = p[-2];
            --p;
        }
        *position = *value;
        end = end + 1;
        return;
    }
    unsigned count = (unsigned)(end - begin);
    unsigned cap2 = count ? count * 2 : 1;
    E8* nb;
    if (cap2)
        nb = (E8*)EAAllocate(cap2 * 8, "Simulator", 0, 0,
                             (const char*)0x13ebb38, 0xd1);
    else
        nb = 0;
    E8* q = UninitCopy8Destruct(begin, position, nb);
    if (q)
        *q = *value;
    E8* ne = UninitCopy8Destruct(position, end, q + 1);
    if (begin && begin != (E8*)buf)
        operator delete(begin);
    begin = nb;
    end = ne;
    cap = nb + cap2;
}

// ---------------------------------------------------------------------------
// 0x00fb3430  vector<E28>::insert(position, n, value)
// ---------------------------------------------------------------------------
// @ 0x00fb3430
void Vec28::insert(E28* position, unsigned n, const E28* value)
{
    unsigned have = (unsigned)(((char*)cap - (char*)end) / sizeof(E28));
    if (n > have) {
        unsigned used = (unsigned)(((char*)end - (char*)begin) / sizeof(E28));
        unsigned want = used * 2;
        if (!used) want = 1;
        unsigned need = used + n;
        if (need > want) want = need;
        E28* nb = want ? (E28*)EAAllocate(want * sizeof(E28), "Simulator", 0, 0,
                                          (const char*)0x13ebb38, 0xd1) : 0;
        E28* mid = CopyElems28(begin, position, nb);
        E28* e1 = FillElems28(mid, n, value);
        E28* ne = CopyElems28(position, end, e1);
        if (begin && *(int*)((char*)begin - 4))
            operator delete(begin);
        begin = nb;
        end = ne;
        cap = nb + want;
    } else if (n) {
        E28 tmp = *value;
        unsigned have2 = (unsigned)(((char*)end - (char*)position) / sizeof(E28));
        if (n < have2) {
            MoveElems28(end - n, end, end);
            end = end + n;
            MoveElems28(position, end - 2 * n, position + n);
            FillElems28(position, n, &tmp);
        } else {
            FillElems28(end, n - have2, &tmp);
            end = end + (n - have2);
            MoveElems28(position, end - (n - have2), position + n);
            FillElems28(position, have2, &tmp);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00fb3660  Mgr::remove(id)
// ---------------------------------------------------------------------------
// @ 0x00fb3660
void Mgr::remove(int id)
{
    unsigned maskA2 = 0;
    unsigned maskB2 = 0;
    int n = (int)((end - begin));
    int idx = 0;
    if (n <= 0) return;
    E16* p = begin;
    while (p->d[0] != (unsigned)id) {
        maskA2 |= p->d[2];
        ++idx;
        maskB2 |= p->d[3];
        ++p;
        if (idx >= n) return;
    }
    for (int k = 0; k < 4; ++k) {
        if (child[k])
            ((Mgr*)child[k])->remove(id);
    }
    void* o = *(void**)((char*)begin + idx * 16 + 4);
    if (o) {
        FUN_00762a30(o);
        *(void**)((char*)begin + idx * 16 + 4) = 0;
    }
    ++idx;
    if (idx < n) {
        E16* q = begin + idx;
        int cnt = n - idx;
        do {
            maskA2 |= q->d[2];
            maskB2 |= q->d[3];
            ++q;
            --cnt;
        } while (cnt);
    }
    if (maskA != maskA2 || maskB != maskB2) {
        maskA = maskA2;
        maskB = maskB2;
        dirty = 1;
    }
    E16* src = begin + idx;
    E16* dst = src - 1;
    while (src < end) {
        *dst = *src;
        ++src;
        ++dst;
    }
    end = end - 1;
}

// ---------------------------------------------------------------------------
// 0x00fb37d0  vector<E48>::reserve(n)
// ---------------------------------------------------------------------------
// @ 0x00fb37d0
void Vec48::reserve(unsigned n)
{
    unsigned have = (unsigned)(((char*)cap - (char*)begin) / sizeof(E48));
    if (n <= have) return;
    E48* nb = n ? (E48*)EAAllocate(n * sizeof(E48), "Simulator", 0, 0,
                                   (const char*)0x13ebb38, 0xd1) : 0;
    E48* ne = CopyE48(begin, end, nb);
    if (begin && *(int*)((char*)begin - 4))
        operator delete(begin);
    end = nb + (unsigned)(((char*)end - (char*)begin) / sizeof(E48));
    begin = nb;
    cap = nb + n;
    (void)ne;
}

// ---------------------------------------------------------------------------
// 0x00fb3880  vector<E48>::insert(position, value)
// ---------------------------------------------------------------------------
// @ 0x00fb3880
void Vec48::insert(E48* position, const E48* value)
{
    if (end != cap) {
        if (value >= position && value < end)
            value += 1;
        if (end)
            FUN_00fb29f0(end - 1);
        E48* p = end;
        while (p != position) {
            p[-1] = p[-2];
            --p;
        }
        *position = *value;
        end = end + 1;
        return;
    }
    unsigned used = (unsigned)(((char*)end - (char*)begin) / sizeof(E48));
    unsigned want = used ? used * 2 : 1;
    E48* nb = want ? (E48*)EAAllocate(want * sizeof(E48), "Simulator", 0, 0,
                                      (const char*)0x13ebb38, 0xd1) : 0;
    E48* a = CopyE48(begin, position, nb);
    if (a)
        FUN_00fb29f0(value);
    E48* ne = CopyE48(position, end, a + 1);
    if (begin && *(int*)((char*)begin - 4))
        operator delete(begin);
    begin = nb;
    end = ne;
    cap = nb + want;
}

// ---------------------------------------------------------------------------
// 0x00fb3040  render walk
// ---------------------------------------------------------------------------
// @ 0x00fb3040
int Renderer::walk(Viewer* v, int arg3, Stats* stats)
{
    char buf[0x9c];
    (void)buf;
    Fb1780(v);
    F48a60();
    int count = (int)((*(int*)((char*)this + 0x158) - *(int*)((char*)this + 0x154)) >> 4);
    if (count <= 0) {
        stats->pad[0x20] += 0;
        return 0;
    }
    int off = 0;
    do {
        Clip* c = (Clip*)(*(int*)((char*)this + 0x154) + off);
        if (c->obj) {
            unsigned char loc[0x14];
            (void)loc;
            F7c3d30(v, loc, 0, 0);
            int type = 6;
            int flags = *(int*)((char*)c->obj + 0xb8) >> 1;
            if (flags & 1) {
                type = 9;
            } else {
                int m = *(int*)((char*)c->obj + 0x70);
                if (m == 1) type = 7;
                else if (m == 2) type = 8;
            }
            char loc2[0x80];
            (void)loc2;
            int k = 7;
            do { Faed90(); --k; } while (k >= 0);
            Ffaf4e0(type, loc2, **(unsigned**)((char*)c->obj + 0x128));
            void* o = c->obj;
            *(float*)((char*)o + 0xbc) = *(float*)((char*)o + 0x40);
            *(float*)((char*)o + 0xc0) = *(float*)((char*)o + 0x44);
            *(float*)((char*)o + 0xc4) = *(float*)((char*)o + 0x48);
            *(float*)((char*)o + 0xc8) = *(float*)((char*)o + 0x4c);
            if (*(int*)((char*)o + 0x70) == 9)
                *(float*)((char*)o + 0xc8) = 1.0f;
            F777ae0(0x304, (char*)o + 0xbc, 0);
            Faef10(*(unsigned*)(*(int*)((char*)this + 0x94)),
                   *(void**)((char*)c + 4), 0, *(unsigned*)((char*)c->obj + 8));
            stats->pad[0x24] += *(int*)((char*)c->obj + 8);
            stats->pad[0x28] += 1;
            F777ae0(0x304, 0, 0);
            int j = 7;
            do { Fc2830(); --j; } while (j >= 0);
        }
        off += 0x10;
        --count;
    } while (count);
    stats->pad[0x20] += *(int*)(*(int*)((char*)this + 0x94) + 0xc);
    return 0;
}
