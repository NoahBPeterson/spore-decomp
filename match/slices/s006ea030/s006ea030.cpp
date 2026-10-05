// Slice s006ea030 -- render-entity (0x70) copy/assign plus large render passes.
// Field offsets are raw; callees are relocation-masked.
#include <string.h>
#include <intrin.h>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

struct E6 {
    void  r537dc0(void*);     // cSPTransform::operator=
    void  r6e6ee0(void*, int, float, int);
    void  r7c4fd0_dummy();
};

extern void*  f67dd70();
extern void   f6e6ee0(void*, int, float, int);
extern void   f6e6e90(void*, void*);
extern void   f6e95a0(void*);
extern void   f6e8e40(int, int);
extern void   f6e6500(void*);
extern void   f6e6710(char, void*, void*);
extern int    f7c4fd0();
extern void   f777bf0();
extern void   f777c10();
extern char   f777c90();
extern void   f7c3c10();
extern void   f6ddde0(int, int);
extern void   f6ddef0(int);
extern void   f777ae0(int, int, int);
extern void   f7789d0();
extern void   f7a3e60(int, int);
extern void   f_f47380(void*);
extern float  g1533c74;
extern float  g1471064;
extern float  g1533c98;
extern float  g1533c9c;
extern float  g1533ca0;
extern float  g1533ca4;
extern void*  g15ddc84;

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

// the 0x70-byte render entity
struct R70 {
    char m[0x70];
    R70* mabc0(const R70& src);   // 0x6eabc0 copy ctor
    R70* mac80(const R70& src);   // 0x6eac80 assign
};

struct S6 {
    char m_unk[0x380];

    // 0x6ea030 render pass A
    void m030(int a, int b, int c);
    // 0x6ea470 render pass B
    void m470(int a, uint flags, int c);
    // 0x6ea920 EH dtor
    void m920();
    // 0x6ea9e0 setter
    void m9e0(int idx, float* box, float pad);
    // 0x6ead40 transform setter
    void mad40(int idx, void* xf);
};

// ---------------------------------------------------------------------------
// @ 0x006ea030
void S6::m030(int a, int b, int c)
{
    char* self = (char*)this;
    void* mm = f67dd70();
    int uVar3 = (int)((int(__thiscall*)(void*, int))VFN(mm, 0x28))(mm, 0);
    if (f7c4fd0() == 0)
        return;
    f777bf0();
    int n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x5c) + i * 2) * 0x70 + *(int*)(self + 0x48);
        if ((*(uchar*)(e + 0x12) & 4) == 0)
            f6e6ee0((void*)(e + 0x30), uVar3, g1533c98, c);
    }
    n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x5c) + i * 2) * 0x70 + *(int*)(self + 0x48);
        if ((*(uchar*)(e + 0x12) & 4) != 0)
            f6e6ee0((void*)(e + 0x30), uVar3, g1533c9c, c);
    }
    n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x188) + i * 2) * 0x70 + *(int*)(self + 0x174);
        if ((*(uchar*)(e + 0x12) & 4) == 0) {
            float box[6];
            box[0] = *(float*)(e + 0x2c); box[1] = *(float*)(e + 0x30); box[2] = *(float*)(e + 0x34);
            box[3] = *(float*)(e + 0x38); box[4] = *(float*)(e + 0x3c); box[5] = *(float*)(e + 0x40);
            float d = *(float*)(*(int*)(e + 0x28) + 0x68) * *(float*)(e + 0x44);
            if (box[0] != g1533c74 && box[0] != -g1533c74) {
                box[0] -= d; box[1] -= d; box[2] -= d;
                box[3] += d; box[4] += d; box[5] += d;
            }
            f6e6ee0(box, uVar3, g1533c98, c);
        }
    }
    n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x188) + i * 2) * 0x70 + *(int*)(self + 0x174);
        if ((*(uchar*)(e + 0x12) & 4) != 0) {
            float box[6];
            box[0] = *(float*)(e + 0x2c); box[1] = *(float*)(e + 0x30); box[2] = *(float*)(e + 0x34);
            box[3] = *(float*)(e + 0x38); box[4] = *(float*)(e + 0x3c); box[5] = *(float*)(e + 0x40);
            float d = *(float*)(*(int*)(e + 0x28) + 0x68) * *(float*)(e + 0x44);
            if (box[0] != g1533c74 && box[0] != -g1533c74) {
                box[0] -= d; box[1] -= d; box[2] -= d;
                box[3] += d; box[4] += d; box[5] += d;
            }
            f6e6ee0(box, uVar3, g1533ca0, c);
        }
    }
    n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
    for (int i = 0; i < n; i++) {
        int e = *(int*)(self + 0x1b8) + i * 0x68;
        if (*(uchar*)(e + 0x50) != 0 && *(int*)e != 0) {
            float box[6];
            int v = *(int*)e;
            box[0] = *(float*)(v + 0x50); box[1] = *(float*)(v + 0x54); box[2] = *(float*)(v + 0x58);
            box[3] = *(float*)(v + 0x5c); box[4] = *(float*)(v + 0x60); box[5] = *(float*)(v + 0x64);
            f6e95a0((void*)(e + 0x18));
            f6e6ee0(box, uVar3, g1533ca4, c);
        }
    }
    f777c10();
    f7c3c10();
}

// ---------------------------------------------------------------------------
// @ 0x006ea470
void S6::m470(int a, uint flags, int c)
{
    char* self = (char*)this;
    *(int*)(self + 0x168) = -1;
    uchar filt = 0;
    if (flags & 0x20000) filt = 8;
    if (flags & 0x40000) filt |= 0x40;
    if (f7c4fd0() == 0)
        return;
    f777bf0();
    f6ddde0(3, 2);
    int cur = *(int*)(self + 0x108 + a * 0x14);
    int* end = (int*)(self + 0x108 + a * 0x14);
    if (cur == *end) {
        f6ddef0(c);
        f777c10();
        f7c3c10();
        return;
    }
    // NOTE: full dispatch loop omitted (partial); see partial.txt
    f6ddef0(c);
    f777c10();
    f7c3c10();
}

// ---------------------------------------------------------------------------
// @ 0x006ea920
void S6::m920()
{
    char* self = (char*)this;
    void* p = *(void**)(self + 0x6c);
    if (p)
        ((void(__thiscall*)(void*))VFN(p, 8))(p);
    void* q = *(void**)(self + 0x2c);
    if (q) {
        int* rc = (int*)((char*)q + 8);
        if (--(*rc) < 1)
            (*rc)++;
    }
    void* r = *(void**)(self + 0x28);
    if (r) {
        int* rc = (int*)((char*)r + 8);
        if (--(*rc) < 1)
            (*rc)++;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ea9e0
void S6::m9e0(int idx, float* box, float pad)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70)
        return;
    int e = idx * 0x70 + *(int*)(self + 0x48);
    *(float*)(e + 0x3c) = box[3];
    *(float*)(e + 0x40) = box[4];
    *(float*)(e + 0x44) = box[5];
    *(float*)(e + 0x30) = box[0];
    *(float*)(e + 0x34) = box[1];
    *(float*)(e + 0x38) = box[2];
    float f = *(float*)(e + 0x30);
    pad = pad * 0.5f;
    if (f != g1533c74 && f != -g1533c74) {
        *(float*)(e + 0x30) = f - pad;
        *(float*)(e + 0x34) = *(float*)(e + 0x34) - pad;
        *(float*)(e + 0x38) = *(float*)(e + 0x38) - pad;
        *(float*)(e + 0x3c) = pad + *(float*)(e + 0x3c);
        *(float*)(e + 0x40) = pad + *(float*)(e + 0x40);
        *(float*)(e + 0x44) = pad + *(float*)(e + 0x44);
    }
    void* h = *(void**)(self + 0x1e0);
    if (h) {
        float c[3];
        if (*box == g1533c74) {
            c[0] = *(float*)0x1618de0;
            c[1] = *(float*)0x1618de4;
            c[2] = *(float*)0x1618de8;
        } else {
            c[0] = (*box + box[3]) * 0.5f;
            c[1] = (box[4] + box[1]) * 0.5f;
            c[2] = (box[5] + box[2]) * 0.5f;
        }
        if (*(int*)(e + 0x68) == 0)
            *(int*)(e + 0x68) =
                ((int(__thiscall*)(void*, float, float*))VFN(h, 0x18))(h, 1.0f, c);
        else
            ((void(__thiscall*)(void*, float, float*, int))VFN(h, 0x1c))(
                h, 1.0f, c, *(int*)(e + 0x68));
    }
    void* vl = *(void**)(e + 0x6c);
    if (vl) {
        *(void**)(e + 0x6c) = 0;
        ((void(__thiscall*)(void*))VFN(vl, 8))(vl);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006eabc0
R70* R70::mabc0(const R70& src)
{
    char* d = (char*)this;
    char* s = (char*)&src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    void* n = *(void**)(s + 0x28);
    void* o = *(void**)(d + 0x28);
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 4))++;
        *(void**)(d + 0x28) = n;
        if (o) {
            int v = (*(volatile int*)((char*)o + 4) += -1);
            if (v == 0) {
                *(int*)((char*)o + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(o, 0))(o, 1);
            }
        }
    }
    *(uint*)(d + 0x38) = *(uint*)(s + 0x38);
    *(uint*)(d + 0x3c) = *(uint*)(s + 0x3c);
    *(uint*)(d + 0x40) = *(uint*)(s + 0x40);
    *(uint*)(d + 0x2c) = *(uint*)(s + 0x2c);
    *(uint*)(d + 0x30) = *(uint*)(s + 0x30);
    *(uint*)(d + 0x34) = *(uint*)(s + 0x34);
    *(float*)(d + 0x44) = *(float*)(s + 0x44);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006eac80
R70* R70::mac80(const R70& src)
{
    char* d = (char*)this;
    char* s = (char*)&src;
    void* n = *(void**)s;
    void* o = *(void**)d;
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 4))++;
        *(void**)d = n;
        if (o) {
            int v = (*(volatile int*)((char*)o + 4) += -1);
            if (v == 0) {
                *(int*)((char*)o + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(o, 0))(o, 1);
            }
        }
    }
    *(uint*)(d + 4) = *(uint*)(s + 4);
    *(uint*)(d + 8) = *(uint*)(s + 8);
    *(uint*)(d + 0xc) = *(uint*)(s + 0xc);
    *(float*)(d + 0x10) = *(float*)(s + 0x10);
    *(float*)(d + 0x14) = *(float*)(s + 0x14);
    ((E6*)(d + 0x18))->r537dc0(s + 0x18);
    *(uchar*)(d + 0x50) = *(uchar*)(s + 0x50);
    *(uchar*)(d + 0x51) = *(uchar*)(s + 0x51);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(uint*)(d + 0x58) = *(uint*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    _ReadWriteBarrier();
    void* n2 = *(void**)(s + 0x60);
    void* o2 = *(void**)(d + 0x60);
    if (n2 != o2) {
        if (n2)
            ((void(__thiscall*)(void*))VFN(n2, 0))(n2);
        *(void**)(d + 0x60) = n2;
        if (o2)
            ((void(__thiscall*)(void*))VFN(o2, 4))(o2);
    }
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006ead40
void S6::mad40(int idx, void* xf)
{
    char* self = (char*)this;
    int e = idx * 0x68 + *(int*)(self + 0x1b8);
    void* o = *(void**)(e + 0x60);
    if (o) {
        ((void(__thiscall*)(void*, int, void*))VFN(o, 0x14))(o, idx, xf);
        return;
    }
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68)
        return;
    ((E6*)(e + 0x18))->r537dc0(xf);
    float a = *(float*)(e + 0x14);
    float b = *(float*)(e + 0x28);
    *(ushort*)(e + 0x18) |= 1;
    *(ushort*)(e + 0x1a) = *(ushort*)(e + 0x1a) + 1;
    *(float*)(e + 0x28) = a * b;
    void* h = *(void**)(self + 0x1e0);
    if (h) {
        float c[3];
        c[0] = *(float*)((char*)xf + 4);
        c[1] = *(float*)((char*)xf + 8);
        c[2] = *(float*)((char*)xf + 0xc);
        if (*(int*)(e + 0x5c) == 0)
            *(int*)(e + 0x5c) =
                ((int(__thiscall*)(void*, float, float*))VFN(h, 0x18))(h, 1.0f, c);
        else
            ((void(__thiscall*)(void*, float, float*, int))VFN(h, 0x1c))(
                h, 1.0f, c, *(int*)(e + 0x5c));
    }
}
