// Slice s006ec0c0 -- effects/camera helpers and EASTL vector instantiations.
#include <string.h>
#include <intrin.h>
#include <stdlib.h>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long u64;

extern void*  f_f47380(void*);
extern void*  f_f473a0(int, int, int, int, int, int);
extern void   f_ac2060(uint*, int, int, int, uint, uint, int);
extern int    f_ac3fa0(uint*, uint*, int);
extern int    f_7c3af0(int);
extern void   f_6ebd20(int, int);
extern void   f_6f66a0(int*);
extern int    f_6ebe50(uint*, int, uint, uint, int);
extern void   f_grow4(void*, int*);

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

// vector<Pair3> -- 3 dwords per element
struct VecC {
    int* b;
    int* e;
    int* cap;
    void DoInsert(int* pos, int* v);   // 0x6ec260
};

// the 0xc0-stride effect struct
struct Eff {
    char m[0xc0];
};

struct S8 {
    char m_unk[0x30d80];

    void m0c0(int a, int b, int c, int d, int e, void* f);  // 0x6ec0c0
    void mecc0();                                           // 0x6ec0c0 helper? (unused)
    void m260();                                            // placeholder
    void m4a0();                                            // 0x6ec4a0 (declared via VecC helper)
    void m660(void* src);                                   // 0x6ec660
    void m730();                                            // 0x6ec730
    void m840(int a, int b);                                // 0x6ec840
    void m8a0();                                            // 0x6ec8a0
    void maa0();                                            // 0x6ecaa0
    void mb40();                                            // 0x6ecb40
    void mdd0(int a, int b);                                // 0x6ecdd0
    void me30(int a, int b, int c);                         // 0x6ece30
    void me90(int n, int* a, int* b);                       // 0x6ece90
    void mf10();                                            // 0x6ecf10
    void mfc0(void* src);                                   // 0x6ecfc0
    void md070();                                           // 0x6ed070
    void md1a0(int idx, char v);                            // 0x6ed1a0
    void md210(int idx);                                    // 0x6ed210
};

// free helpers
int  __cdecl f6d0(int p1, int p2, int p3);     // 0x6ec6d0
void __stdcall fca50(char* p1, char* p2);      // 0x6eca50
void f5b0(uint* p1, int p2, int p3, int p4);   // 0x6ec5b0

// a vector<Pair3> helper: m4a0 uses 4-byte element vector, not modeled here.
// ---------------------------------------------------------------------------
// @ 0x006ec0c0
void S8::m0c0(int a, int b, int c, int d, int e, void* f)
{
    // 253-byte skill/effect resource installer; body omitted (partial).
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
}

// ---------------------------------------------------------------------------
// @ 0x006ec260  VecC::DoInsert
void VecC::DoInsert(int* pos, int* v)
{
    int* end = e;
    if (end != cap) {
        if (pos <= v && v < end)
            v += 3;
        if (end) {
            end[0] = end[-3];
            end[1] = end[-2];
            end[2] = end[-1];
        }
        int* d = e;
        int* s = e;
        while (s - 3 != pos) {
            d[-3] = s[-6];
            d[-2] = s[-5];
            d[-1] = s[-4];
            d -= 3;
            s -= 3;
        }
        pos[0] = v[0];
        pos[1] = v[1];
        pos[2] = v[2];
        e = e + 3;
        return;
    }
    int n = ((int)end - (int)b) / 0xc;
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    int* dst = (int*)malloc(n * 0xc);
    memcpy(dst, b, (int)pos - (int)b);
    int* mid = dst + ((int)pos - (int)b) / 4;
    if (mid) {
        mid[0] = v[0];
        mid[1] = v[1];
        mid[2] = v[2];
    }
    memcpy(mid + 3, pos, (int)end - (int)pos);
    if (b != 0)
        free(b);
    int* ne = (int*)((char*)mid + 0xc + ((int)end - (int)pos));
    b = dst;
    e = ne;
    cap = (int*)((char*)dst + n * 0xc);
}

// ---------------------------------------------------------------------------
// @ 0x006ec4a0 (vector<bool>) -- placeholder nonmatching body
void S8::m4a0() { }

// ---------------------------------------------------------------------------
// @ 0x006ec5b0
void f5b0(uint* p1, int p2, int p3, int p4)
{
    uint d = p2 - (int)p1;
    while ((int)(d & 0xfffffff8) > 0xe0 && p3 > 0) {
        uint a = *p1;
        int i = (p2 - (int)p1) >> 3;
        i = (i - (i >> 0x1f)) >> 1;
        uint x = p1[i * 2];
        uint y = x;
        uint* m = p1 + i * 2;
        uint* p = p1;
        if (x < a) { y = a; m = p1; p = p1 + i * 2; a = x; }
        if (a <= *(uint*)(p2 - 8) && *(uint*)(p2 - 8) < y)
            p = (uint*)(p2 - 8);
        int r = f_6ebe50(p1, p2, *p, p[1], p4);
        p3--;
        f5b0((uint*)r, p2, p3, p4);
        d = r - (int)p1;
        p2 = r;
    }
    if (p3 == 0)
        f_ac3fa0(p1, (uint*)p2, p4);
}

// ---------------------------------------------------------------------------
// @ 0x006ec660
void S8::m660(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    char* q = d + 0x14;
    *(void**)(d + 0x10) = q;
    *(void**)(d + 4) = q;
    *(void**)d = q;
    *(void**)(d + 8) = d + 0x94;
    *(ushort*)q = 0;
    f_6ebd20(*(int*)s, *((int*)s + 1));
}

// ---------------------------------------------------------------------------
// @ 0x006ec6d0
int __cdecl f6d0(int p1, int p2, int p3)
{
    if (p1 != p2) {
        do {
            int i = *(int*)(p1 + 4);
            if ((int)((*(int*)(p1 + 0xc) - i) & 0xfffffffe) > 2 && i != 0 &&
                i != *(int*)(p1 + 0x14))
                f_f47380((void*)i);
            p1 += 0xc0;
            p3 += 0xc0;
        } while (p1 != p2);
    }
    return p3;
}

// ---------------------------------------------------------------------------
// @ 0x006ec730
void S8::m730()
{
    char* p = (char*)this;
    *(uchar*)p = 0;
    char* q = p + 0x18;
    *(void**)(p + 0x14) = q;
    *(void**)(p + 8) = q;
    *(void**)(p + 4) = q;
    *(void**)(p + 0xc) = p + 0x98;
    *(ushort*)q = 0;
    *(int*)(p + 0x98) = 0;
    *(int*)(p + 0x9c) = 0;
    *(float*)(p + 0xa8) = 12.0f;
    *(int*)(p + 0xa0) = -1;
    *(int*)(p + 0xa4) = -1;
    float one = 1.0f;
    *(float*)(p + 0xac) = one;
    *(float*)(p + 0xb0) = one;
    *(float*)(p + 0xb4) = one;
    *(float*)(p + 0xb8) = one;
    *(float*)(p + 0xbc) = one;
}

// ---------------------------------------------------------------------------
// @ 0x006ec840
void S8::m840(int a, int b)
{
    char* self = (char*)this;
    // eastl::vector<AutoRefCount<...>>::erase + release tail; approximate
    int* end = *(int**)(self + 4);
    int* it = end;
    for (; it < end; it++) { }
    (void)a; (void)b;
}

// ---------------------------------------------------------------------------
// @ 0x006ec8a0
void S8::m8a0() { }

// ---------------------------------------------------------------------------
// @ 0x006ecaa0
void S8::maa0() { }

// ---------------------------------------------------------------------------
// @ 0x006ecb40
void S8::mb40() { }

// ---------------------------------------------------------------------------
// @ 0x006eca50
void __stdcall fca50(char* p1, char* p2)
{
    for (; p1 < p2; p1 += 0xc0) {
        int i = *(int*)(p1 + 4);
        if (((2 < (int)(*(int*)(p1 + 0xc) - i & 0xfffffffeU)) && (i != 0)) &&
            (i != *(int*)(p1 + 0x14)))
            f_f47380((void*)i);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ecdd0
void S8::mdd0(int a, int b)
{
    int loc[3];
    loc[0] = a; loc[1] = b; loc[2] = 0;
    char* self = (char*)this;
    int* p = *(int**)(self + 0xc);
    if (p < *(int**)(self + 0x10)) {
        *(int**)(self + 0xc) = p + 3;
        if (p != 0) {
            p[0] = loc[0];
            p[1] = loc[1];
            p[2] = loc[2];
            return;
        }
    }
    ((VecC*)(self + 8))->DoInsert(p, loc);
}

// ---------------------------------------------------------------------------
// @ 0x006ece30
void S8::me30(int a, int b, int c)
{
    int loc[3];
    loc[0] = a; loc[1] = b; loc[2] = c;
    char* self = (char*)this;
    int* p = *(int**)(self + 0xc);
    if (p < *(int**)(self + 0x10)) {
        *(int**)(self + 0xc) = p + 3;
        if (p != 0) {
            p[0] = loc[0];
            p[1] = loc[1];
            p[2] = loc[2];
            return;
        }
    }
    ((VecC*)(self + 8))->DoInsert(p, loc);
}

// ---------------------------------------------------------------------------
// @ 0x006ece90
void S8::me90(int n, int* a, int* b)
{
    char* self = (char*)this;
    while (n != 0) {
        int loc[3];
        loc[1] = *b;
        int* p = *(int**)(self + 0xc);
        loc[0] = *a;
        loc[2] = 0;
        n--;
        if (p < *(int**)(self + 0x10)) {
            *(int**)(self + 0xc) = p + 3;
            if (p != 0) {
                p[0] = loc[0]; p[1] = loc[1]; p[2] = 0;
            }
        } else {
            ((VecC*)(self + 8))->DoInsert(p, loc);
        }
        b++;
        a++;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ecf10
void S8::mf10()
{
    char* self = (char*)this;
    for (int i = 0; i < 0x28; i += 4) {
        int r = f_7c3af0(*(int*)(i + 0x1533cd0));
        VecC* v = (VecC*)(self + 0x30d54);
        int* p = v->e;
        if (p < v->cap) {
            v->e = p + 1;
            if (p)
                *p = r;
        } else {
            int loc = r;
            f_grow4(v, &loc);
        }
    }
    for (int i = 0; i < 0x28; i += 4) {
        int r = f_7c3af0(*(int*)(i + 0x1533ca8));
        VecC* v = (VecC*)(self + 0x30d68);
        int* p = v->e;
        if (p < v->cap) {
            v->e = p + 1;
            if (p)
                *p = r;
        } else {
            int loc = r;
            f_grow4(v, &loc);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ecfc0
void S8::mfc0(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uchar*)d = *(uchar*)s;
    if (d + 4 != s + 4) {
        if (*(ushort*)(d + 4) != *(ushort*)(d + 8)) {
            **(ushort**)(d + 4) = 0;
            *(uint*)(d + 8) = *(uint*)(d + 4);
        }
        f_6ebd20(*(int*)(s + 4), *(int*)(s + 8));
    }
    *(float*)(d + 0x98) = *(float*)(s + 0x98);
    *(float*)(d + 0x9c) = *(float*)(s + 0x9c);
    *(uint*)(d + 0xa0) = *(uint*)(s + 0xa0);
    *(uint*)(d + 0xa4) = *(uint*)(s + 0xa4);
    *(float*)(d + 0xa8) = *(float*)(s + 0xa8);
    *(float*)(d + 0xac) = *(float*)(s + 0xac);
    *(uint*)(d + 0xb0) = *(uint*)(s + 0xb0);
    *(uint*)(d + 0xb4) = *(uint*)(s + 0xb4);
    *(uint*)(d + 0xb8) = *(uint*)(s + 0xb8);
    *(uint*)(d + 0xbc) = *(uint*)(s + 0xbc);
}

// ---------------------------------------------------------------------------
// @ 0x006ed070
void S8::md070() { }

// ---------------------------------------------------------------------------
// @ 0x006ed1a0
void S8::md1a0(int idx, char v)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70)
        return;
    int off = idx * 0x70;
    char* p = (char*)(*(int*)(self + 0x48) + 0x48 + off);
    if (*p != v) {
        *p = v;
        if (v != 0 && *(char*)(*(int*)(self + 0x48) + 0x49 + off) == 0) {
            int t = idx & 0xffff;
            f_6f66a0(&t);
            *(char*)(*(int*)(self + 0x48) + 0x49 + off) = 1;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ed210
void S8::md210(int idx)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x178) - *(int*)(self + 0x174)) / 0x70)
        return;
    int off = idx * 0x70;
    char* e = (char*)(*(int*)(self + 0x174) + off);
    if (*(int*)e == 0)
        return;
    *(int*)e = 0;
    *(uchar*)(e + 0x48) = 0;
    int v = *(int*)(e + 0x64);
    if (v != 0) {
        void* h = *(void**)(self + 0x1e0);
        if (h)
            ((void(__thiscall*)(void*, int))VFN(h, 0x20))(h, v);
        *(int*)(e + 0x64) = 0;
    }
    VecC* vv = (VecC*)(self + 0x19c);
    int* p = vv->e;
    if (p < vv->cap) {
        vv->e = p + 1;
        if (p) {
            *p = idx;
            return;
        }
    }
    int loc = idx;
    f_grow4(vv, &loc);
}
