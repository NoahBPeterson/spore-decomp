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
extern void** g15ddc84;      // 0x15ddc84: singleton slot for cStaticBufferDraw
extern void   f777b50(void*);   // 0x777b50 SP::SetShaderData            (cdecl, 1 arg)
extern void   f11ee580(void*);  // 0x11ee580 rw::graphics::CompiledState::Dispatch (thiscall)
extern void   f11f1280(int, void*); // 0x11f1280 rw::graphics::ActiveState::SetTexture
extern void   f7a4710(void*);   // 0x7a4710 SP::cStaticBuffer::Flush      (thiscall)
extern void   f700120();        // 0x700120 cFrustumCull::FrustumTestSphere (thiscall, 3 args)
extern uint   g16f8b00;         // 0x16f8b00 raster-delta dirty mask
extern uint   g16f9110;         // 0x16f9110 soft-state dirty mask
extern int    g140afc4;         // 0x140afc4 identity/default quad state

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
    void m470(int a, uint flags, int c, void* viewer);
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
// Render pass B: walk bucket `a`'s list of 8-byte {tag, entity} records.  Each
// record's entity is filtered by the visibility mask / frustum, then state
// changes (shader, textures, shader-data stack) are flushed lazily and the
// entity is dispatched either through the state-batched path (bit 2 set) or
// directly.  `c` is the draw-batch object, `viewer` the cViewer doing the pass.
void S6::m470(int a, uint flags, int c, void* viewer)
{
    char* self = (char*)this;
    *(int*)(self + 0x168) = -1;

    uchar mask = 0;
    if (flags & 0x20000) mask = 8;
    if (flags & 0x40000) mask |= 0x40;

    if (!((char(__thiscall*)(void*))f7c4fd0)(viewer))
        return;

    f777bf0();
    f6ddde0(3, 2);

    int* rec = *(int**)(self + 0x104 + a * 0x14);
    int** endp = (int**)(self + 0x108 + a * 0x14);
    float mid[3];
    mid[0] = mid[1] = mid[2] = 0.0f;

    uchar changed = 0;    // local_5e: a shader-data push is live
    uchar lastBit2 = 0;   // local_5d: previous entity's batched-draw bit
    int shader68 = 0, shader5c = 0, shader60 = 0, tex28 = 0, tex2c = 0;

    while (rec != *endp) {
        int* e = (int*)rec[1];
        uchar ef = *(uchar*)((char*)e + 0x12);
        bool pass = (ef & mask) == mask;
        bool skip = false;

        if ((ef & 0x10) == 0) {
            if (!pass) {
                skip = true;
            } else {
                float b1[3], b2[3];
                b1[0] = *(float*)((char*)e + 0x3c);
                b1[1] = *(float*)((char*)e + 0x40);
                b1[2] = *(float*)((char*)e + 0x44);
                b2[0] = *(float*)((char*)e + 0x30);
                b2[1] = *(float*)((char*)e + 0x34);
                b2[2] = *(float*)((char*)e + 0x38);
                uint r = ((uint(__thiscall*)(void*, float*, float*, uint))f700120)
                    (self + 0x260, b2, b1, 0x200);
                if ((r & 0x40) != 0)
                    skip = true;
            }
        } else if (!pass) {
            skip = true;
        }

        if (!skip && e[0] != 0) {
            uchar bit2 = (uchar)((ef >> 2) & 1);
            if (changed
                || shader5c != e[0x17] || shader60 != e[0x18]
                || tex28 != e[10] || tex2c != e[0xb]
                || *(uint*)(self + 0x168) != (uint)*(uchar*)((char*)e + 0x10)
                || shader68 != e[0x1a] || lastBit2 != bit2) {
                f6ddef0(c);
                if (changed)
                    f777c10();
                f777c10();
                *(uint*)(self + 0x168) = (uint)*(uchar*)((char*)e + 0x10);
                shader68 = e[0x1a];
                shader5c = e[0x17];
                shader60 = e[0x18];
                tex28 = e[10];
                tex2c = e[0xb];
                f777bf0();
                f777b50(*(void**)(shader5c + 4));
                if ((ef & 3) != 0)
                    f777ae0(0x223, 0, 1);
                ((void(__thiscall*)(void*))f11ee580)(*(void**)(shader5c + 4));
                if (e[10] != 0) {
                    f11f1280(0, *(void**)e[10]);
                    g16f8b00 |= 1;
                }
                if (e[0xb] != 0) {
                    f11f1280(1, *(void**)e[0xb]);
                    g16f8b00 |= 2;
                }
                if (e[0x18] != 0)
                    ((void(__thiscall*)(void*))f7789d0)((void*)e[0x18]);
                int outA, outB;
                f6e6710((char)e[4], &outA, &outB);
                f6ddde0(outA, outB);
                lastBit2 = bit2;
            }
            f777bf0();
            if (e[0x1a] != 0)
                f777ae0(0x219, *(int*)e[0x1a], 0);
            if (e[0x19] != 0)
                f777ae0(0x206, e[0x19], 0);
            if ((ef & 3) != 3) {
                mid[0] = ((float)e[0x0f] + (float)e[0x0c]) * g1471064;
                mid[1] = ((float)e[0x10] + (float)e[0x0d]) * g1471064;
                mid[2] = ((float)e[0x11] + (float)e[0x0e]) * g1471064;
                f777ae0(0x226, (int)mid, 1);
            }
            if (bit2 == 0) {
                void* obj = (void*)e[0];
                ((void(__thiscall*)(void*, void*))VFN(obj, 0))(obj, self + 4);
            } else {
                if (e[0x1b] == 0) {
                    ((void(__thiscall*)(void*, int, int))f6e8e40)
                        (self + 0x16c, 0, *(int*)(self + 0x168));
                    void* obj = (void*)e[0];
                    ((void(__thiscall*)(void*, void*))VFN(obj, 0))(obj, self + 0x16c);
                    int* q = (int*)e[0x1b];
                    if (q != 0) {
                        e[0x1b] = 0;
                        ((void(__thiscall*)(void*))VFN(q, 8))(q);
                    }
                    void** slot = (void**)g15ddc84;
                    ((void(__thiscall*)(void*))f7a4710)(slot[0]);
                    e[0x1b] = (int)slot[0];
                    slot[0] = 0;
                }
                if (e[0x1b] != 0) {
                    int quad[4];
                    quad[0] = e[0x13]; quad[1] = e[0x14];
                    quad[2] = e[0x15]; quad[3] = e[0x16];
                    f6e6500(quad);
                    g16f9110 |= 0x10;
                    ((void(__thiscall*)(void*, int, int))f7a3e60)
                        ((void*)e[0x1b], c, 0);
                    uchar* pb = (uchar*)e[0x17];
                    if (pb != 0 && pb[0] > 1) {
                        int i = 1;
                        do {
                            ((void(__thiscall*)(void*))f11ee580)
                                (*(void**)(pb + i * 4 + 4));
                            ((void(__thiscall*)(void*, int, int))f7a3e60)
                                ((void*)e[0x1b], c, 0);
                            pb = (uchar*)e[0x17];
                            i++;
                        } while (i < (int)pb[0]);
                    }
                    f6e6500(&g140afc4);
                    g16f9110 |= 0x10;
                }
            }
            changed = (uchar)f777c90();
            if (!changed)
                f777c10();
            *(int*)(self + 0x370) += 1;
            endp = (int**)(self + 0x108 + a * 0x14);
        }
        rec += 2;
    }

    f6ddef0(c);
    if (changed)
        f777c10();
    f777c10();
    ((void(__thiscall*)(void*))f7c3c10)(viewer);
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
        volatile long* rc = (volatile long*)((char*)q + 8);
        if (_InterlockedDecrement(rc) < 1)
            _InterlockedIncrement(rc);
    }
    void* r = *(void**)(self + 0x28);
    if (r) {
        volatile long* rc = (volatile long*)((char*)r + 8);
        if (_InterlockedDecrement(rc) < 1)
            _InterlockedIncrement(rc);
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
