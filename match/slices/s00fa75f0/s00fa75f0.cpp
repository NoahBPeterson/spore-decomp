// Slice s00fa75f0: Terrain/Sphere cube-map height builder (6 faces x 256x256 float images).
// Names are guesses: no PDB names for these functions.
#include "types.h"
#include <xmmintrin.h>
#include <string.h>
#include <new>
#include <math.h>

typedef unsigned int size_t_;

// Operator new overloads taking (name, flags...) used by Spore's allocator.
void* __cdecl operator new(unsigned int size, const char* name, int a, int b, int c, int d);
void __cdecl operator delete(void* p, const char* name, int a, int b, int c, int d);
void* __cdecl AllocEA(unsigned int size, int flags, int a, const char* name, int b, int c, const char* file, int line); // 0xf473d0
void __cdecl FreeArray(void* p);                                                                                         // 0xf47380

struct FVec {            // eastl::vector<float> body (begin/end/capacity)
    float* b;
    float* e;
    float* c;
    void Swap(FVec* other);   // 0xf8f8a0
};

struct ImgBase {
    virtual void Dtor(int del);   // slot 0: scalar deleting destructor
    uint32_t pad[3];
    FVec v;                       // +0x10
    uint32_t pad2[2];
    ImgBase();                    // 0xf8ee70
    void Init(int n);             // 0xf92250
    void Assign(ImgBase* src);    // 0xf88360
    void Finish();                // 0xf918d0
    void Fini();                  // 0xf8f970 (stack-image destructor)
    void CubeEdge(int face, int x, int y, float* data, const float* w, float scale);   // 0xf87d20
};

struct Img : ImgBase {
    Img() {}
    virtual void Dtor(int del);
};

struct Ctx {                      // object at Cls+0x2c
    uint32_t pad0[2];
    Img* A;                       // +0x08  packed u16 source
    Img* B;                       // +0x0c  packed byte source
    Img* out;                     // +0x10  packed output
    uint32_t pad1[7];
    Img* C;                       // +0x24
    Img* D;                       // +0x28
    Img* E;                       // +0x2c
    Img* F;                       // +0x30
};

struct O2 { uint32_t pad[10]; uint8_t* tbl; };          // +0x28
struct O1 { uint32_t pad[0xcb]; O2* o2; };              // +0x32c
struct O210 { void Use(Img* h); };                      // 0xfc42a0

struct Cls {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual bool Query(int what);                       // slot 0x4c
    uint32_t pad0[10];
    Ctx* ctx;                                           // +0x2c
    uint32_t pad1[0x77];
    O1* o1;                                             // +0x20c
    O210* o210;                                         // +0x210
    uint32_t pad2[0x4e];
    float f34c, f350, f354, f358, f35c;

    void BuildTerrain(const float* rects);              // @ 0xfa75f0
};

static inline int FloorI(float x) {
    int i = _mm_cvt_ss2si(_mm_set_ss(x));
    if (x < (float)i) --i;
    return i;
}

// @ 0xfa75f0
void Cls::BuildTerrain(const float* rects)
{
    Ctx* x = ctx;
    Img* outImg = x->out;
    if (!outImg) return;
    Img* A = x->A; Img* B = x->B; Img* C = x->C; Img* D = x->D; Img* E = x->E; Img* F = x->F;
    const __m128 zero = _mm_setzero_ps();
    const uint32_t k16 = 0xffff, kone = 0x3f800000;
    const __m128 m16 = _mm_set1_ps(*(const float*)&k16);
    const __m128 one = _mm_set1_ps(1.0f);
    const __m128 four = _mm_set1_ps(4.0f);
    const __m128 half = _mm_set1_ps(0.5f);
    const __m128 two = _mm_set1_ps(2.0f);

    if (!o210 || !Query(4)) {
        // plain path: 2x2 box of the u16 map into C, rescaled and clamped at 0
        const float* r = rects;
        for (int fo = 0; fo < 0x600; fo += 0x100, r += 4) {
            int a = FloorI(r[0] * 256.0f);
            int b = FloorI(r[2] * 256.0f);
            int c = FloorI(r[1] * 256.0f);
            int d = FloorI(r[3] * 256.0f);
            int k0 = a >> 2, k1 = b >> 2;
            char* src = (char*)A->v.b + (fo + c) * 0x800;
            char* dst = (char*)C->v.b + (fo + c) * 0x400;
            if (c < d) {
                for (int n = d - c; n; --n) {
                    if (k0 < k1) {
                        const char* q = src + 0x402 + k0 * 16;
                        float* o = (float*)(dst + k0 * 16);
                        for (int m = k1 - k0; m; --m) {
                            __m128 p0 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 0x402)), m16), one);
                            __m128 p1 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q - 0x400)), m16), one);
                            __m128 p3 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)q), m16), one);
                            __m128 p2 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 2)), m16), one);
                            __m128 s = _mm_add_ps(_mm_add_ps(p0, p1), _mm_add_ps(p2, p3));
                            s = _mm_mul_ps(_mm_sub_ps(s, four), _mm_set1_ps(64.0009765625f));
                            _mm_store_ps(o, _mm_max_ps(_mm_sub_ps(s, one), zero));
                            q += 16; o += 4;
                        }
                    }
                    dst += 0x400; src += 0x800;
                }
            }
        }
    } else {
        // detailed path: build 6x256x256 from A, downsample to 64x64 (H64), add lat map, normalise
        for (int fb = 0, ob = 0; fb < 0x300000; fb += 0x80000, ob += 0x40000) {
            const char* src = (const char*)A->v.b + fb + 0x402;
            float* o = (float*)((char*)C->v.b + ob);
            for (int row = 0x100; row; --row) {
                const char* q = src;
                for (int n = 0x40; n; --n) {
                    __m128 p0 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 0x402)), m16), one);
                    __m128 p1 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q - 0x400)), m16), one);
                    __m128 p3 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)q), m16), one);
                    __m128 p2 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 2)), m16), one);
                    __m128 s = _mm_add_ps(_mm_add_ps(p0, p1), _mm_add_ps(p2, p3));
                    _mm_store_ps(o, _mm_mul_ps(_mm_sub_ps(s, four), _mm_set1_ps(32.00048828125f)));
                    q += 16; o += 4;
                }
                src += 0x800;
            }
        }

        Img* H = new ("Terrain/Sphere/Height64", 0, 0, 0, 0) Img();
        H->Init(0x40);
        {
            const float* cp = (const float*)((char*)C->v.b + 0x800);
            float* o = H->v.b;
            for (int row = 0x180; row; --row) {
                const float* p = cp;
                for (int n = 0x10; n; --n) {
                    for (int i = 0; i < 4; ++i) {
                        const float* e = p + 4 * i;
                        o[i] = ((((e[-0x200 + 3] + e[-0x100 + 3]) + (e[0x100 + 3] + e[3])) +
                                 ((e[-0x200 + 2] + e[-0x100 + 2]) + (e[0x100 + 2] + e[2]))) +
                                (((e[-0x200 + 1] + e[-0x100 + 1]) + (e[0x100 + 1] + e[1])) +
                                 ((e[-0x200] + e[-0x100]) + (e[0x100] + e[0])))) * 0.0625f;
                    }
                    o += 4; p += 0x10;
                }
                cp += 0x400;
            }
        }

        Img* L = new ("Terrain/Sphere/LatMap", 0, 0, 0, 0) Img();
        L->Init(0x40);
        {
            static const uint8_t axes[3][4] = { {0, 1, 2, 0}, {1, 2, 0, 0}, {2, 0, 1, 0} };
            float* lf = L->v.b;
            float v[4];
            for (int face = 0; face < 6; ++face) {
                const uint8_t* t = axes[face >> 1];
                int odd = face & 1;
                float* col = lf;
                for (unsigned u = 0; u < 0x40; ++u) {
                    float fx = (((float)(int)u + 0.5f) * 0.015625f) * 2.0f - 1.0f;
                    float* o = col;
                    for (unsigned w = 0; w < 0x40; ++w) {
                        float fy = (((float)(int)w + 0.5f) * 0.015625f) * 2.0f - 1.0f;
                        float inv = 1.0f / sqrtf((fy * fy + fx * fx) + 1.0f);
                        float sinv = odd ? -inv : inv;
                        v[t[0]] = sinv * fx;
                        v[t[1]] = inv * fy;
                        v[t[2]] = sinv;
                        float z = v[2] * v[2];
                        if (z < 0.0f) z = 0.0f;
                        else if (z > 1.0f) z = 1.0f;
                        *o = z;
                        o += 0x40;
                    }
                    col += 1;
                }
                lf += 0x1000;
            }
        }

        {
            __m128* h = (__m128*)H->v.b;
            __m128* l = (__m128*)L->v.b;
            __m128 mx = _mm_set1_ps(-3.402823466e+38f);
            __m128 mn = _mm_set1_ps(3.402823466e+38f);
            for (int i = 0; i < 0x180 * 0x10; ++i) {
                __m128 s = _mm_add_ps(l[i], h[i]);
                h[i] = s;
                mx = _mm_max_ps(s, mx);
                mn = _mm_min_ps(s, mn);
            }
            mx = _mm_max_ps(_mm_shuffle_ps(mx, mx, 0xb1), mx);
            mx = _mm_max_ps(_mm_shuffle_ps(mx, mx, 0x1b), mx);
            mn = _mm_min_ps(_mm_shuffle_ps(mn, mn, 0xb1), mn);
            mn = _mm_min_ps(_mm_shuffle_ps(mn, mn, 0x1b), mn);
            __m128 rc = _mm_rcp_ps(_mm_sub_ps(mx, mn));
            for (int i = 0; i < 0x180 * 0x10; ++i)
                h[i] = _mm_mul_ps(_mm_sub_ps(h[i], mn), rc);
        }
        L->Dtor(1);
        {
            __m128* c = (__m128*)C->v.b;
            for (int i = 0; i < 6 * 0x100 * 0x40; ++i)
                c[i] = _mm_max_ps(_mm_mul_ps(_mm_sub_ps(c[i], half), two), zero);
        }
        o210->Use(H);
        H->Dtor(1);
    }

    // B (bytes) -> D: mean of squared normalised samples, scaled by f350
    {
        const float* r = rects;
        for (int fo = 0; fo < 0x600; fo += 0x100, r += 4) {
            int a = FloorI(r[0] * 256.0f);
            int b = FloorI(r[2] * 256.0f);
            int c = FloorI(r[1] * 256.0f);
            int d = FloorI(r[3] * 256.0f);
            char* src = (char*)B->v.b + ((fo + c) << 12);
            char* dst = (char*)D->v.b + ((fo + c) << 10);
            int k0 = a >> 2, k1 = b >> 2;
            const __m128 sc = _mm_set1_ps(f350);
            if (c < d) {
                for (int n = d - c; n; --n) {
                    if (k0 < k1) {
                        const char* q = src + (k0 << 5) + 0x12;
                        float* o = (float*)(dst + (k0 << 4));
                        for (int m = k1 - k0; m; --m) {
                            const uint32_t k8 = 0xff;
                            const __m128 mm = _mm_set1_ps(*(const float*)&k8);
                            const __m128 cc = _mm_set1_ps(65793.0078125f);
                            __m128 s0 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q - 0x10)), mm), one), one);
                            s0 = _mm_sub_ps(_mm_mul_ps(s0, cc), one); s0 = _mm_mul_ps(s0, s0);
                            __m128 t0 = _mm_add_ps(_mm_shuffle_ps(s0, s0, 0xb1), s0);
                            __m128 s1 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)q), mm), one), one);
                            s1 = _mm_sub_ps(_mm_mul_ps(s1, cc), one); s1 = _mm_mul_ps(s1, s1);
                            __m128 t1 = _mm_add_ps(_mm_shuffle_ps(s1, s1, 0xb1), s1);
                            __m128 s2 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q + 0x7f0)), mm), one), one);
                            s2 = _mm_sub_ps(_mm_mul_ps(s2, cc), one); s2 = _mm_mul_ps(s2, s2);
                            __m128 t2 = _mm_add_ps(_mm_shuffle_ps(s2, s2, 0xb1), s2);
                            __m128 s3 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q + 0x800)), mm), one), one);
                            s3 = _mm_sub_ps(_mm_mul_ps(s3, cc), one); s3 = _mm_mul_ps(s3, s3);
                            __m128 t3 = _mm_add_ps(_mm_shuffle_ps(s3, s3, 0xb1), s3);
                            __m128 hi = _mm_shuffle_ps(t2, t3, 0xdd);
                            __m128 lo = _mm_shuffle_ps(t0, t1, 0xdd);
                            __m128 res = _mm_mul_ps(_mm_add_ps(hi, lo), _mm_set1_ps(0.25f));
                            _mm_store_ps(o, _mm_mul_ps(res, sc));
                            q += 0x20; o += 4;
                        }
                    }
                    dst += 0x400; src += 0x1000;
                }
            }
        }
    }

    // E = D * f354 + C * f34c
    {
        const float* r = rects;
        for (int fo = 0; fo < 0x600; fo += 0x100, r += 4) {
            int a = FloorI(r[0] * 256.0f);
            int b = FloorI(r[2] * 256.0f);
            int c = FloorI(r[1] * 256.0f);
            int d = FloorI(r[3] * 256.0f);
            int off = (fo + c) << 10;
            char* eP = (char*)E->v.b + off;
            char* dP = (char*)D->v.b + off;
            char* cP = (char*)C->v.b + off;
            int k0 = a >> 2, k1 = b >> 2;
            const __m128 w0 = _mm_set1_ps(f34c);
            const __m128 w1 = _mm_set1_ps(f354);
            if (c < d) {
                for (int n = d - c; n; --n) {
                    for (int k = k0; k < k1; ++k) {
                        __m128 dv = _mm_load_ps((const float*)(dP + k * 16));
                        __m128 cv = _mm_load_ps((const float*)(cP + k * 16));
                        _mm_store_ps((float*)(eP + k * 16), _mm_add_ps(_mm_mul_ps(dv, w1), _mm_mul_ps(w0, cv)));
                    }
                    eP += 0x400; dP += 0x400; cP += 0x400;
                }
            }
        }
    }

    F->Assign(E);

    // add 256x256 byte detail table to every face of F
    {
        const uint8_t* tbl = o1->o2->tbl;
        float scale = f35c;
        float* p = F->v.b;
        for (int face = 6; face; --face) {
            for (unsigned y = 0; (int)y < 0x100; ++y) {
                for (unsigned xx = 0; (int)xx < 0x100; ++xx) {
                    *p = ((float)tbl[(xx & 0xff) + (y & 0xff) * 0x100] * 0.007843137718737125f - 1.0f) * scale + *p;
                    ++p;
                }
            }
        }
    }

    // 3x3 blur of F into scratch image S, then fix the cube-face edges
    Img S;
    S.Init(0x100);
    {
        const __m128 wr0 = _mm_set1_ps(0.125f), wmid = _mm_set1_ps(0.25f), wr2 = _mm_set1_ps(0.125f);
        const __m128 sr0 = _mm_set1_ps(0.0625f), smid = _mm_set1_ps(0.125f), sr2 = _mm_set1_ps(0.0625f);
        static const float edgeW[4] = { 0.0625f, 0.125f, 0.0625f, 0.125f };
        for (int face = 0, fo = 0; fo < 0x180000; fo += 0x40000, ++face) {
            char* src = (char*)F->v.b + fo;
            char* dst = (char*)S.v.b + fo + 0x400;
            for (int row = 0xfe; row; --row) {
                __m128 prev = zero;
                __m128 r0 = _mm_load_ps((const float*)src);
                __m128 rm = _mm_load_ps((const float*)(src + 0x400));
                __m128 r2 = _mm_load_ps((const float*)(src + 0x800));
                __m128 cur = _mm_add_ps(_mm_add_ps(_mm_mul_ps(rm, smid), _mm_mul_ps(r0, sr0)), _mm_mul_ps(r2, sr2));
                const char* nx = src + 0x410;
                for (int n = 0x40; n; --n) {
                    __m128 c2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(rm, wmid), _mm_mul_ps(r0, wr0)), _mm_mul_ps(r2, wr2));
                    __m128 nm = _mm_load_ps((const float*)nx);
                    __m128 n0 = _mm_load_ps((const float*)(nx - 0x400));
                    __m128 n2 = _mm_load_ps((const float*)(nx + 0x400));
                    __m128 next = _mm_add_ps(_mm_add_ps(_mm_mul_ps(nm, smid), _mm_mul_ps(n0, sr0)), _mm_mul_ps(n2, sr2));
                    __m128 t = _mm_shuffle_ps(cur, next, 0x0d);
                    __m128 right = _mm_shuffle_ps(cur, t, 0xd9);
                    __m128 left = _mm_shuffle_ps(prev, cur, 0x8f);
                    left = _mm_shuffle_ps(left, cur, 0x98);
                    _mm_store_ps((float*)dst, _mm_add_ps(_mm_add_ps(right, left), c2));
                    r0 = n0; rm = nm; r2 = n2;
                    nx += 16; dst += 16;
                    prev = cur; cur = next;
                }
                src += 0x400;
            }
            for (int i = 0; i < 0x100; ++i) {
                F->CubeEdge(face, i, 0, S.v.b, edgeW, 1.0f);
                F->CubeEdge(face, i, 0xff, S.v.b, edgeW, 1.0f);
                F->CubeEdge(face, 0, i, S.v.b, edgeW, 1.0f);
                F->CubeEdge(face, 0xff, i, S.v.b, edgeW, 1.0f);
            }
        }
    }

    // F.data <- blurred data (via a temporary copy of F's old buffer)
    {
        int n = (int)(F->v.e - F->v.b);
        FVec t;
        void* mem = n ? AllocEA(n * 4, 0x80, 0, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5) : 0;
        t.b = (float*)mem;
        t.c = (float*)((char*)mem + n * 4);
        int bytes = (int)((char*)F->v.e - (char*)F->v.b);
        void* endp = memcpy(mem, F->v.b, bytes);
        t.e = (float*)((char*)endp + (bytes >> 2) * 4);
        F->v.Swap(&S.v);
        S.v.Swap(&t);
        if (mem) FreeArray(mem);
    }

    // pack F (6 x 256 x 256 floats) into the 8-bit output image
    {
        const __m128 k0 = _mm_set1_ps(3.039836883544922e-05f);
        const __m128 k1 = _mm_set1_ps(0.007781982421875f);
        const uint32_t u_ff = 0xff, u_ff00 = 0xff00, u_hi = 0xffff0000;
        const __m128 mask_lo = _mm_set1_ps(*(const float*)&u_ff);
        const __m128 mask_mid = _mm_set1_ps(*(const float*)&u_ff00);
        const __m128 mask_hi = _mm_set1_ps(*(const float*)&u_hi);
        float* o = outImg->v.b;
        const char* f = (const char*)F->v.b;
        for (int face = 6; face; --face) {
            for (int row = 0x100; row; --row) {
                const float* p = (const float*)f;
                for (int n = 0x10; n; --n) {
                    __m128 c0 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p), zero), one);
                    __m128 c1 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p + 4), zero), one);
                    __m128 c2 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p + 8), zero), one);
                    __m128 c3 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p + 12), zero), one);
                    __m128 pa = _mm_shuffle_ps(c0, c1, 0x44), pc = _mm_shuffle_ps(c0, c1, 0xee);
                    __m128 pb = _mm_shuffle_ps(c2, c3, 0x44), pd = _mm_shuffle_ps(c2, c3, 0xee);
                    __m128 l0 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pa, pb, 0x88), k0), one), mask_lo);
                    __m128 l1 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pa, pb, 0xdd), k1), one), mask_mid);
                    __m128 l3 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pc, pd, 0xdd), k1), one), mask_mid);
                    __m128 l2 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pc, pd, 0x88), k0), one), mask_lo);
                    _mm_store_ps(o, _mm_or_ps(l3, l2));
                    __m128 m = _mm_loadu_ps((const float*)((char*)o - 2));
                    _mm_store_ps(o, _mm_or_ps(_mm_and_ps(m, mask_hi), _mm_or_ps(l1, l0)));
                    p += 16; o += 4;
                }
                f += 0x400;
            }
        }
    }
    outImg->Finish();
    S.Fini();
}
