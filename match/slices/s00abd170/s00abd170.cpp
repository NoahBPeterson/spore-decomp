// Slice s00abd170 -- EA::Swarm sequence-effect / cGme component methods.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- helpers
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define VC0V(p, off)    ((void(__thiscall*)(void*))VFN(p, off))((void*)(p))
#define VCV(p, off, a)  ((void(__thiscall*)(void*, int))VFN(p, off))((void*)(p), (int)(a))
#define VCB0(p, off)    ((char(__thiscall*)(void*))VFN(p, off))((void*)(p))
#define VCP(p, off, a)  ((void(__thiscall*)(void*, void*))VFN(p, off))((void*)(p), (void*)(a))
#define VC2P(p, off, a, b) ((void(__thiscall*)(void*, void*, int))VFN(p, off))((void*)(p), (void*)(a), (int)(b))
#define VCM2(p, off, a, b) ((void(__thiscall*)(void*, float, float))VFN(p, off))((void*)(p), (a), (b))

#define D(p, off) (*(int*)((char*)(p) + (off)))
#define F(p, off) (*(float*)((char*)(p) + (off)))
#define B(p, off) (*(unsigned char*)((char*)(p) + (off)))
#define W(p, off) (*(unsigned short*)((char*)(p) + (off)))
#define SV(p, off) (*(volatile int*)((char*)(p) + (off)))
#define SB(p, off) (*(volatile unsigned char*)((char*)(p) + (off)))
#define SF(p, off) (*(volatile float*)((char*)(p) + (off)))
#define SW(p, off) (*(volatile unsigned short*)((char*)(p) + (off)))

struct Vector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    void Resize(int n);                          // 0x00abd0f0
    void Dtor();                                 // 0x004b5440
    void Erase(void* first, void* last);         // 0x00533500
    void Push(void** p);                         // 0x00a7f430
};

struct IntList {
    int* mpBegin;                                // +0x00
    int* mpEnd;                                  // +0x04
};

struct Mat3 {
    float f0, f1, f2, f3, f4, f5, f6, f7, f8;
    Mat3() {}
    Mat3(const Mat3& o) { Assign(&o); }
    void Assign(const void* src);                // 0x0041cb40
};

struct CTrans {
    short a;                                     // +0x00
    short b;                                     // +0x02
    float x, y, z;                               // +0x04
    float w;                                     // +0x10
    Mat3  mat;                                   // +0x14
    void PreTransformBy(const CTrans& o);        // 0x00537f40
};

struct SPTransOps {
    void* Assign(const void* src);               // 0x00537dc0
};

struct TxtFactory {
    void* Make(int idx, int a, int b);           // 0x00a71410
};

struct AutoRef {
    void Set(void* p);                           // 0x00b5f950
};

// ---------------------------------------------------------------- globals
extern void* const vtbl_14598b0;                  // 0x014598b0
extern void* const vtbl_1459910;                  // 0x01459910
extern void* const vtbl_145990c;                  // 0x0145990c
extern void* const vtbl_14599ec;                  // 0x014599ec
extern void* const vtbl_14599e8;                  // 0x014599e8
extern void* const vtbl_13ef094;                  // 0x013ef094
extern void* const vtbl_13f21d4;                  // 0x013f21d4
extern const float kOne_1485720;                  // 0x01485720
extern const float kZero_1485378;                 // 0x01485378
extern const float k63_14321f8;                   // 0x014321f8
extern const float k9c54;                         // 0x01679c54
extern const float k9c58;                         // 0x01679c58
extern const float k9c5c;                         // 0x01679c5c
extern const float k9d00[9];                      // 0x01679d00
extern const float k9e84;                         // 0x01679e84
extern const float k9e88;                         // 0x01679e88
extern float* g_tabA_begin;                       // 0x01679e5c
extern float* g_tabA_end;                         // 0x01679e60
extern float* g_tabB_begin;                       // 0x01679e8c
extern const char kSwarm[];                       // 0x013f1fdc
struct RandObj { double RandomDoubleUniform(); }; // 0x009360d0
extern RandObj g_random_16778dc;                  // 0x016778dc

// ---------------------------------------------------------------- callees
void* __cdecl EAAllocate(uint32_t sz, const char* name, int, int, int, int); // 0x00f473a0
void  __cdecl EADealloc(void* p);                                            // 0x00f47380
void  __cdecl ReadInt32(void* s, void* out, int n, int a);                   // 0x0093a780
void  __cdecl ReadU8(void* s, void* out, int n);                             // 0x0093a6c0
void  __cdecl Ser7d27d0(void* s, void* out);                                 // 0x007d27d0
float __cdecl FUN_007cdb90(void* entry);                                     // 0x007cdb90
extern "C" double __cdecl sqrt(double);

// ---------------------------------------------------------------- object
struct Eff {
    char pad0[0xc];

    void FUN_00abd1f0(int a, int b, int c);
    void FUN_00abd230(int p);
    int  FUN_00abd270();
    void FUN_00abd290(char on);
    void FUN_00abd390(void* a, void* b);
    void* FUN_00abd3e0(int a, int b);
    void* FUN_00abd540(char del);
    void FUN_00abd590(void* p);
    void FUN_00abd640();
    void FUN_00abd6f0(float dt, int a, int b);
    void* FUN_00abd970(char del);
    void FUN_00abdb20(int unused);
    char FUN_00abdb70(int evt, void* data, int unused);
    void FUN_00abdbb0(float a, float b, int unused);
    void FUN_00abe090(CTrans* by, CTrans* src);
};

// ---------------------------------------------------------------- 0x00abd170
int* __cdecl FUN_00abd170(int* stream, Vector* vec);

// ---------------------------------------------------------------- 0x00abd170
// @ 0x00ABD170
int* __cdecl FUN_00abd170(int* stream, Vector* vec) {
    int n;
    ReadInt32(stream, &n, 1, 0);
    vec->Resize(n);
    int off = 0;
    for (unsigned i = 0; i < (unsigned)n; ++i, off += 12) {
        int* base = vec->mpBegin;
        VC2P(stream, 0x30, (char*)base + off, 8);
        ReadInt32(stream, (char*)base + off + 8, 1, 0);
    }
    return stream;
}

// ---------------------------------------------------------------- 0x00abd1f0
// @ 0x00ABD1F0
void Eff::FUN_00abd1f0(int a, int b, int c) {
    D(this, 0x18) = c;
    D(this, 0x14) = a;
    D(this, 0xa0) = (unsigned char)((unsigned)D(D(this, 0xc), 0x1c) >> 1) & 1;
    D(this, 0xa4) = (unsigned char)((unsigned)D(D(this, 0xc), 0x1c) >> 2) & 1;
}

// ---------------------------------------------------------------- 0x00abd230
// @ 0x00ABD230
void Eff::FUN_00abd230(int p) {
    IntList* v = (IntList*)((char*)D(this, 0xc) + 8);
    if (v->mpBegin != v->mpEnd) {
        B(this, 0x1c) = 1;
        if (p == 0 || B(this, 0x1d) != 0) {
            F(this, 0x20) = 0.0f;
            D(this, 0x24) = 0;
            F(this, 0x28) = 0.0f;
            B(this, 0x2c) = 0;
        }
        B(this, 0x1d) = 0;
    } else {
        B(this, 0x1c) = 0;
    }
}

// ---------------------------------------------------------------- 0x00abd270
// @ 0x00ABD270
int Eff::FUN_00abd270() {
    return B(this, 0x1c) != 0 || D(this, 0xac) != D(this, 0xb0);
}

// ---------------------------------------------------------------- 0x00abd290
// @ 0x00ABD290
void Eff::FUN_00abd290(char on) {
    B(this, 0x2d) = on;
    if (D(this, 0xa8) != 0)
        VCV(D(this, 0xa8), 0x30, on == 0);
    for (unsigned i = 0; i < (unsigned)((D(this, 0xb0) - D(this, 0xac)) >> 2); ++i) {
        void* o = ((void**)D(this, 0xac))[i];
        VCV(o, 0x30, on == 0);
    }
}

// ---------------------------------------------------------------- 0x00abd300
// @ 0x00ABD300
int __cdecl FUN_00abd300(void* self, IntList* list, int a, int b) {
    int n = (D(list, 0xc) - D(list, 8)) / 12;
    int total = 0;
    if (n > 0) {
        int off = 0;
        for (;;) {
            int* e = (int*)(D(list, 8) + off);
            if (e[2] >= 0) {
                int r = ((int(__thiscall*)(void*, int, int, int))VFN(self, 0x2c))
                            (self, e[2], a, b);
                total += r;
                if (a != 0) {
                    a += r * 16;
                    b -= r;
                }
            }
            off += 12;
            if (--n == 0)
                break;
        }
    }
    return total;
}

// ---------------------------------------------------------------- 0x00abd390
// @ 0x00ABD390
void Eff::FUN_00abd390(void* a, void* b) {
    SPTransOps* p0 = (SPTransOps*)((char*)this + 0x30);
    p0->Assign(a);
    SPTransOps* p1 = (SPTransOps*)((char*)this + 0x68);
    p1->Assign(b);
    void* o = (void*)D(this, 0xa8);
    if (o != 0) {
        VCP(o, 0x18, p0);
        VCP(o, 0x14, p1);
    }
}

// ---------------------------------------------------------------- 0x00abd3e0
// @ 0x00ABD3E0
void* Eff::FUN_00abd3e0(int a, int b) {
    int z = 0;
    SV(this, 4) = (int)&vtbl_13ef094;
    D(this, 8) = z;
    SV(this, 0xc) = a;
    SV(this, 0x10) = b;
    SF(this, 0x20) = 0.0f;
    SF(this, 0x28) = 0.0f;
    SV(this, 0) = (int)&vtbl_1459910;
    SV(this, 4) = (int)&vtbl_145990c;
    SV(this, 0x14) = z;
    SB(this, 0x1c) = z;
    SV(this, 0x24) = z;
    SB(this, 0x2c) = z;
    SB(this, 0x1d) = 1;
    SB(this, 0x2d) = 1;
    SW(this, 0x30) = 0;
    SW(this, 0x32) = 0;
    SF(this, 0x34) = k9c54;
    SF(this, 0x38) = k9c58;
    SF(this, 0x3c) = k9c5c;
    F(this, 0x40) = kOne_1485720;
    ((Mat3*)((char*)this + 0x44))->Assign(k9d00);
    SW(this, 0x68) = 0;
    SW(this, 0x6a) = 0;
    SF(this, 0x6c) = k9c54;
    SF(this, 0x70) = k9c58;
    SF(this, 0x74) = k9c5c;
    F(this, 0x78) = kOne_1485720;
    ((Mat3*)((char*)this + 0x7c))->Assign(k9d00);
    SV(this, 0xa8) = z;
    SV(this, 0xac) = z;
    SV(this, 0xb0) = z;
    SV(this, 0xb4) = z;
    return this;
}

// ---------------------------------------------------------------- 0x00abd540
// @ 0x00ABD540
void* Eff::FUN_00abd540(char del) {
    D(this, 0) = (int)&vtbl_1459910;
    D(this, 4) = (int)&vtbl_145990c;
    ((Vector*)((char*)this + 0xac))->Dtor();
    if (D(this, 0xa8) != 0)
        VC0V(D(this, 0xa8), 4);
    D(this, 0) = (int)&vtbl_13f21d4;
    D(this, 4) = (int)&vtbl_13ef094;
    if ((del & 1) != 0)
        EADealloc(this);
    return this;
}

// ---------------------------------------------------------------- 0x00abd590
// @ 0x00ABD590
void Eff::FUN_00abd590(void* p) {
    if (D(this, 0xa8) != 0) {
        VCV(D(this, 0xa8), 0xc, p);
        void* q = (void*)D(this, 0xa8);
        if (q != 0) {
            D(this, 0xa8) = 0;
            VC0V(q, 4);
        }
    }
    if (p != 0) {
        Vector* v = (Vector*)((char*)this + 0xac);
        if (v->mpBegin != v->mpEnd) {
            for (unsigned i = 0; i < (unsigned)(v->mpEnd - v->mpBegin); ++i) {
                if (VCB0((void*)v->mpBegin[i], 0x10))
                    VCV((void*)v->mpBegin[i], 0xc, p);
            }
            v->Erase(v->mpBegin, v->mpEnd);
        }
    }
    B(this, 0x1c) = 0;
}

// ---------------------------------------------------------------- 0x00abd640
// @ 0x00ABD640
void Eff::FUN_00abd640() {
    Vector* v = (Vector*)((char*)this + 0xac);
    int j = 0;
    for (unsigned i = 0; i < (unsigned)((D(this, 0xb0) - D(this, 0xac)) >> 2); ++i) {
        void* cur = (void*)v->mpBegin[i];
        if (VCB0(cur, 0x10)) {
            if (j < (int)i) {
                void* keep = (void*)v->mpBegin[i];
                void* old = (void*)v->mpBegin[j];
                if (keep != old) {
                    if (keep != 0)
                        VC0V(keep, 0);
                    v->mpBegin[j] = (int)keep;
                    if (old != 0)
                        VC0V(old, 4);
                }
            }
            ++j;
        }
    }
    v->Erase(v->mpBegin + j, v->mpEnd);
}

// ---------------------------------------------------------------- 0x00abd6f0
// @ 0x00ABD6F0
void Eff::FUN_00abd6f0(float dt, int a, int b) {
    if (B(this, 0x1c) == 0) {
        FUN_00abd640();
        return;
    }
    F(this, 0x20) += dt;
    if (B(this, 0x2c) != 0) {
        char ready;
        if (D(this, 0xa8) != 0 && VCB0(D(this, 0xa8), 0x10))
            ready = 0;
        else
            ready = 1;
        F(this, 0x28) = F(this, 0x20);
        if (!ready)
            return;
    } else {
        if (F(this, 0x20) < F(this, 0x28))
            return;
    }
    if (F(this, 0x28) > kZero_1485378) {
        ++D(this, 0x24);
        int cfg = D(this, 0xc);
        int cnt = (D(cfg, 0xc) - D(cfg, 8)) / 12;
        if (D(this, 0x24) >= cnt) {
            if ((B(cfg, 0x1c) & 1) == 0) {
                VCV(this, 0xc, D(this, 0xa4));
                return;
            }
            D(this, 0x24) = 0;
        }
        if (D(this, 0xa8) != 0 && VCB0(D(this, 0xa8), 0x10)) {
            int e = D(this, 0xc);
            if (((unsigned)D(e, 0x1c) >> 3 & 1) == 0) {
                VCV(D(this, 0xa8), 0xc, D(this, 0xa4));
                if (D(this, 0xa4) != 0)
                    goto poped;
            }
            ((Vector*)((char*)this + 0xac))->Push((void**)((char*)this + 0xa8));
            FUN_00abd640();
        poped:
            if (D(this, 0xa8) != 0) {
                void* q = (void*)D(this, 0xa8);
                D(this, 0xa8) = 0;
                VC0V(q, 4);
            }
        }
    }
    {
        int idx = D(this, 0x24);
        int cfg = D(this, 0xc);
        char* ent = (char*)(D(cfg, 8) + idx * 12);
        if (F(ent, 0) < kZero_1485378) {
            B(this, 0x2c) = 1;
        } else {
            F(this, 0x28) += FUN_007cdb90(ent);
            B(this, 0x2c) = 0;
        }
        int idx2 = D(this, 0x24);
        int cfg2 = D(this, 0xc);
        char* ent2 = (char*)(D(cfg2, 8) + idx2 * 12);
        if (D(ent2, 8) < 0)
            return;
        void* txt = ((TxtFactory*)((char*)this + 0x14))->Make(D(ent2, 8), D(this, 0x10), D(this, 0x18));
        ((AutoRef*)((char*)this + 0xa8))->Set(txt);
        void* w = (void*)D(this, 0xa8);
        if (w != 0) {
            VCP(w, 0x18, (char*)this + 0x30);
            VCP((void*)D(this, 0xa8), 0x14, (char*)this + 0x68);
            VCV((void*)D(this, 0xa8), 8, D(this, 0xa0));
            VCV((void*)D(this, 0xa8), 0x30, B(this, 0x2d) == 0);
        }
    }
}

// ---------------------------------------------------------------- 0x00abd8d0
// @ 0x00ABD8D0
void* __cdecl FUN_00abd8d0(int* stream) {
    int* p = (int*)EAAllocate(0x20, kSwarm, 0, 0, 0, 0);
    int* q;
    if (p != 0) {
        p[1] = 0;
        p[0] = (int)&vtbl_14598b0;
        p[2] = 0;
        p[3] = 0;
        p[4] = 0;
        p[7] = 0;
        q = p;
    } else {
        q = 0;
    }
    FUN_00abd170(stream, (Vector*)(q + 2));
    int v;
    ReadInt32(stream, &v, 1, 0);
    q[7] = v & 0xf;
    return q;
}

// ---------------------------------------------------------------- 0x00abd970
// @ 0x00ABD970
void* Eff::FUN_00abd970(char del) {
    int x = D(this, 0x2c);
    if (x != 0 && D((char*)x - 4, 0) != 0)
        EADealloc((void*)x);
    x = D(this, 0x18);
    if (x != 0 && D((char*)x - 4, 0) != 0)
        EADealloc((void*)x);
    D(this, 0) = (int)&vtbl_13ef094;
    if ((del & 1) != 0)
        EADealloc(this);
    return this;
}

// ---------------------------------------------------------------- 0x00abd9c0
// @ 0x00ABD9C0
void __cdecl FUN_00abd9c0(int* stream, int unused, char* out) {
    int v;
    unsigned char b;
    ReadInt32(stream, &v, 1, 0);
    D(out, 0xc) = v & 1;
    ReadInt32(stream, out + 0x10, 1, 0);
    ReadInt32(stream, out + 0x14, 1, 0);
    Ser7d27d0(stream, out + 0x18);
    Ser7d27d0(stream, out + 0x2c);
    ReadInt32(stream, out + 0x40, 1, 0);
    ReadU8(stream, &b, 1);
    D(out, 0x44) = b;
    ReadInt32(stream, out + 0x48, 1, 0);
}

// ---------------------------------------------------------------- 0x00abda70
// @ 0x00ABDA70
float* __cdecl FUN_00abda70(float* out, int unused, float* lo, float* hi) {
    double l = *lo;
    double h = *hi;
    double r = g_random_16778dc.RandomDoubleUniform();
    double v = l + (h - l) * r;
    if (v >= h)
        v = h;
    else if (v < l)
        v = l;
    out[0] = (float)v;

    double h2;
    double l2;
    l2 = lo[1];
    h2 = hi[1];
    r = g_random_16778dc.RandomDoubleUniform();
    v = l2 + (h2 - l2) * r;
    if (v >= h2)
        v = h2;
    else if (v < l2)
        v = l2;
    out[1] = (float)v;
    return out;
}

// ---------------------------------------------------------------- 0x00abdb20
// @ 0x00ABDB20
void Eff::FUN_00abdb20(int unused) {
    if (B(this, 0x18) == 0 && D(this, 0x10) != 0) {
        int e = D(this, 0xc);
        if (D(e, 0x18) != D(e, 0x1c) && D(e, 0x2c) != D(e, 0x30) &&
            F(e, 0x10) > 0.0f) {
            F(this, 0x28) = kOne_1485720 / F(e, 0x10);
            F(this, 0x2c) = 0.0f;
            F(this, 0x30) = 0.0f;
            B(this, 0x18) = 1;
        }
    }
}

// ---------------------------------------------------------------- 0x00abdb70
// @ 0x00ABDB70
char Eff::FUN_00abdb70(int evt, void* data, int unused) {
    switch (evt) {
    case 0x101:
        F(this, 0x38) = F(data, 8);
        F(this, 0x3c) = F(data, 0x14);
        return 1;
    case 4:
        F(this, 0x34) = F(data, 0);
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00abdbb0
// @ 0x00ABDBB0
void Eff::FUN_00abdbb0(float a, float b, int unused) {
    float one = kOne_1485720;
    F(this, 0x2c) = F(this, 0x28) * a + F(this, 0x2c);
    if (F(this, 0x2c) > one)
        F(this, 0x2c) = one;

    int cfg = D(this, 0xc);
    unsigned n = (unsigned)((D(cfg, 0x1c) - D(cfg, 0x18)) >> 2) - 1;
    float t = F(this, 0x2c);
    float v;
    if (n == 0) {
        v = *(float*)D(cfg, 0x18);
    } else {
        float f = (float)((double)n * t);
        int i = (int)f;
        float fr = f - (float)i;
        float* base = (float*)D(cfg, 0x18);
        if (fr <= 0.0f)
            v = base[i];
        else
            v = (base[i + 1] - base[i]) * fr + base[i];
    }

    float lo = F(this, 0x38);
    float amp = F(this, 0x3c);
    cfg = D(this, 0xc);
    float att = F(cfg, 0x48);
    amp = (amp - lo) * b + lo;
    amp *= F(this, 0x34);
    amp *= v;
    if (att > 0.0f) {
        float d;
        if ((B(cfg, 0xc) & 1) == 0) {
            float* m = (float*)D(this, 0x14);
            float px = F(this, 0x1c);
            float py = F(this, 0x20);
            float pz = F(this, 0x24);
            float X = m[7] * px + m[11] * py + m[15] * pz + m[19];
            float Y = m[8] * px + m[12] * py + m[16] * pz + m[20];
            float W = m[10] * px + m[14] * py + m[18] * pz + m[22];
            float nx = X / W;
            float ny = Y / W;
            d = nx * nx + ny * ny;
        } else {
            float* m = (float*)D(this, 0x14);
            float dx = m[0x80 / 4] - F(this, 0x1c);
            float dy = m[0x84 / 4] - F(this, 0x20);
            float dz = m[0x88 / 4] - F(this, 0x24);
            d = (float)sqrt((double)(dz * dz + dy * dy + dx * dx));
        }
        amp = (one / (att * d + one)) * amp;
    }

    cfg = D(this, 0xc);
    unsigned n2 = (unsigned)((D(cfg, 0x30) - D(cfg, 0x2c)) >> 2) - 1;
    float scale = amp / F(cfg, 0x40);
    float amp2 = F(cfg, 0x40) * amp;
    float t2 = F(this, 0x2c);
    float v2;
    if (n2 == 0) {
        v2 = *(float*)D(cfg, 0x2c);
    } else {
        float f = (float)((double)n2 * t2);
        int i = (int)f;
        float fr = f - (float)i;
        float* base = (float*)D(cfg, 0x2c);
        if (fr <= 0.0f)
            v2 = base[i];
        else
            v2 = (base[i + 1] - base[i]) * fr + base[i];
    }
    F(this, 0x30) = v2 * a + F(this, 0x30);

    unsigned tc = (unsigned)(((char*)g_tabA_end - (char*)g_tabA_begin) >> 3);
    float phase = F(this, 0x30) / (double)tc;
    int idx = (int)phase;
    if (phase < (float)idx)
        --idx;
    float frac = (float)((double)phase - (double)idx);

    float s1, s2;
    if (D(cfg, 0x44) == 0) {
        float* tab = g_tabA_begin;
        float x = frac * k63_14321f8;
        int i = (int)x;
        float fr = x - (float)i;
        if (fr <= 0.0f) {
            s1 = tab[i * 2];
            s2 = tab[i * 2 + 1];
        } else {
            s1 = (tab[i * 2 + 2] - tab[i * 2]) * fr + tab[i * 2];
            s2 = (tab[i * 2 + 3] - tab[i * 2 + 1]) * fr + tab[i * 2 + 1];
        }
    } else if (D(cfg, 0x44) == 1) {
        float* tab = g_tabB_begin;
        float x = frac * k63_14321f8;
        int i = (int)x;
        float fr = x - (float)i;
        if (fr <= 0.0f) {
            s1 = tab[i * 2];
            s2 = tab[i * 2 + 1];
        } else {
            s1 = (tab[i * 2 + 2] - tab[i * 2]) * fr + tab[i * 2];
            s2 = (tab[i * 2 + 3] - tab[i * 2 + 1]) * fr + tab[i * 2 + 1];
        }
    } else {
        s1 = 0.0f;
        s2 = 0.0f;
    }
    float o1 = s1 * scale;
    float o2 = s2 * amp2;
    VCM2(D(this, 0x10), 0x5c, o1, o2);
    if (F(this, 0x2c) == one)
        VCV(this, 0xc, 0);
}

// ---------------------------------------------------------------- 0x00abe010
// @ 0x00ABE010
void* __cdecl FUN_00abe010(int arg) {
    int* p = (int*)EAAllocate(0x40, kSwarm, 0, 0, 0, 0);
    if (p != 0) {
        SV(p, 8) = 0;
        SV(p, 4) = (int)&vtbl_13ef094;
        SF(p, 0x28) = 0.0f;
        SF(p, 0x2c) = 0.0f;
        SF(p, 0x30) = 0.0f;
        float one = kOne_1485720;
        SV(p, 0x10) = 0;
        SV(p, 0x14) = 0;
        SB(p, 0x18) = 0;
        SV(p, 0) = (int)&vtbl_14599ec;
        SV(p, 4) = (int)&vtbl_14599e8;
        SV(p, 0xc) = arg;
        SF(p, 0x34) = one;
        SF(p, 0x38) = k9e84;
        SF(p, 0x3c) = k9e88;
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00abe090
// @ 0x00ABE090
void Eff::FUN_00abe090(CTrans* by, CTrans* src) {
    CTrans t = *src;
    t.PreTransformBy(*by);
    D(this, 0x1c) = *(int*)&t.x;
    D(this, 0x20) = *(int*)&t.y;
    D(this, 0x24) = *(int*)&t.z;
}
