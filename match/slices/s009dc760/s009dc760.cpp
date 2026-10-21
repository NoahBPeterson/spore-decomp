// Slice s009dc760 — frozen batch gold4 (slice 102)
// Animation curve / spline evaluation family (Hermite / Catmull-Rom tracks).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ------------------------------------------------------------------ constants
extern float g_f12;              // 0x01447c8c  12.0f
extern float g_f0p5;             // 0x01471064  0.5f
extern float g_f2;               // 0x01470f1c  2.0f
extern float g_f1;               // 0x01485720  1.0f
extern float g_f3;               // 0x013eb95c  3.0f
extern float g_f2p32;            // 0x013f4fd0  4294967296.0f  (negative int -> float fixup)
extern float g_fEps;             // 0x01447c88  1e-6f
extern float g_fAlmost1;         // 0x01447ccc  ~1.0f

// Vtable addresses for the result-record flavours.
extern void* g_vtbl_c0;          // 0x01447cc0  (3-component curve key, stride 0x44)
extern void* g_vtbl_c4;          // 0x01447cc4  (curve key, stride 0x58)
extern void* g_vtbl_c8;          // 0x01447cc8  (curve key, stride 0x1c)

// ------------------------------------------------------------------ helpers
// `fadd 4294967296.0f` for negative int->float: (int) -> float with the
// unsigned-side correction MSVC emits inline.
static __inline float s_itof(int v) {
    return (float)v;
}

// x87 fsqrt on a float value (32-bit result).
static __inline float SqrtF(float f) {
    double d = (double)f;
    float r;
    __asm {
        fld  d
        fsqrt
        fstp r
    }
    return r;
}

// ================================================================ 0x009dc760
struct Curve760 { void __thiscall CopyInto(char* dst); };

// @ 0x009dc760
void __thiscall Curve760::CopyInto(char* dst) {
    int* o = (int*)this;
    unsigned i = 0;
    *(int*)(dst + 0x10) = *o;
    if ((unsigned)*o <= i) return;
    unsigned off = 0;
    do {
        const char* src = (const char*)o[1] + off;
        *(float*)(dst + i * 8 + 0x18) = *(const float*)src;
        ++i;
        *(float*)(dst + i * 8 + 0x14) = *(const float*)(src + 4);
        off += 0xc;
    } while (i < (unsigned)*o);
}

// ================================================================
// Curve containers.  Each holds a begin/end pair of key records.
struct Curve3c44 {
    void __thiscall Find(float t, int* out);
    void __thiscall Eval(void* out, float t, int* range);
    void* __thiscall Sample(void* out, float t);
};
struct Curve1c58 {
    void __thiscall Find(float t, int* out);
    void __thiscall Eval(void* out, float t, int* range);
    void* __thiscall Sample(void* out, float t);
};
struct Curve1c1c {
    void __thiscall Find(float t, int* out);
    void __thiscall Eval(void* out, float t, int* range);
    void* __thiscall Sample(void* out, float t);
};

static __inline float KeyF(const char* p) {
    float f = (float)*(const int*)p;
    return f;
}

// Shared upper-bound search.  The key of entry k lives at +4 and is an
// integer time converted to float.  Writes {lo,hi} through the out pointer.
//
// @ 0x009dc860
void __thiscall Curve3c44::Find(float t, int* out) {
    int* o = (int*)this;
    const char* base = (const char*)o[0];
    int n = (int)((o[1] - (int)base) / 0x44);
    int i = 0;
    if (n > 3) {
        const char* p = base + 0x48;
        do {
            if (t < KeyF(p - 0x44)) break;
            if (t < KeyF(p)) { i += 1; break; }
            if (t < KeyF(p + 0x44)) { i += 2; break; }
            if (t < KeyF(p + 0x88)) { i += 3; break; }
            i += 4;
            p += 0x110;
        } while (i < n - 3);
    }
    if (i < n) {
        const char* p = base + 4 + i * 0x44;
        while (t >= KeyF(p)) {
            ++i;
            p += 0x44;
            if (i >= n) break;
        }
    }
    if (i == n) {
        out[0] = n - 1;
        out[1] = n - 1;
        return;
    }
    out[1] = i;
    out[0] = (i != 0) ? i - 1 : 0;
}

// @ 0x009dcc90
void __thiscall Curve1c58::Find(float t, int* out) {
    int* o = (int*)this;
    const char* base = (const char*)o[0];
    int n = (int)((o[1] - (int)base) / 0x58);
    int i = 0;
    if (n > 3) {
        const char* p = base + 0x5c;
        do {
            if (t < KeyF(p - 0x58)) break;
            if (t < KeyF(p)) { i += 1; break; }
            if (t < KeyF(p + 0x58)) { i += 2; break; }
            if (t < KeyF(p + 0xb0)) { i += 3; break; }
            i += 4;
            p += 0x160;
        } while (i < n - 3);
    }
    if (i < n) {
        const char* p = base + 4 + i * 0x58;
        while (t >= KeyF(p)) {
            ++i;
            p += 0x58;
            if (i >= n) break;
        }
    }
    if (i == n) {
        out[0] = n - 1;
        out[1] = n - 1;
        return;
    }
    out[1] = i;
    out[0] = (i != 0) ? i - 1 : 0;
}

// @ 0x009dd100
void __thiscall Curve1c1c::Find(float t, int* out) {
    int* o = (int*)this;
    const char* base = (const char*)o[0];
    int n = (int)((o[1] - (int)base) / 0x1c);
    int i = 0;
    if (n > 3) {
        const char* p = base + 0x20;
        do {
            if (t < KeyF(p - 0x1c)) break;
            if (t < KeyF(p)) { i += 1; break; }
            if (t < KeyF(p + 0x1c)) { i += 2; break; }
            if (t < KeyF(p + 0x38)) { i += 3; break; }
            i += 4;
            p += 0x70;
        } while (i < n - 3);
    }
    if (i < n) {
        const char* p = base + 4 + i * 0x1c;
        while (t >= KeyF(p)) {
            ++i;
            p += 0x1c;
            if (i >= n) break;
        }
    }
    if (i == n) {
        out[0] = n - 1;
        out[1] = n - 1;
        return;
    }
    out[1] = i;
    out[0] = (i != 0) ? i - 1 : 0;
}
// @ 0x009dc7a0
float __stdcall FUN_009dc7a0(float* v) {
    float x = v[0];
    float y = v[1];
    float len = SqrtF(y * y + x * x);
    if (len > g_f12) {
        float l2 = SqrtF(y * y + x * x);
        if (l2 != 0.0f) {
            float s = g_f1 / l2;
            v[0] = x * s;
            v[1] = y * s;
        }
        v[0] = v[0] * g_f12;
        v[1] = v[1] * g_f12;
        len = g_f12;
    }
    return len;
}

// ================================================================
// Curve-key record layouts.
//   0x44 stride (3-component): time +4, vals +8/+0xc/+0x10,
//                              tangent mode byte at +0x1d, tangent +0x18
//   0x58 stride (1-component): time +4, vals +8..+0x14,
//                              mode byte at +0x15, tangent +0x14
//   0x1c stride (1-component): time +4, val +8, mode byte at +0x15,
//                              tangent +0xc
// Result records: vtable, time, then the interpolated components.

namespace {

// tangent weight for one component:
//   mode 0 -> auto (finite difference), 1 -> linear, 2 -> flat, 3 -> explicit
struct TanCtx {
    const char* other;   // neighbouring key for the auto mode
    float       dtNeg;   // gap to the previous key (as float)
    int         dtGap;   // gap key+1 - key (as int)
};

inline float AutoTangent(const char* prev, const char* next, float dt) {
    return 0.0f;   // placeholder; kept explicit at each call site
}

} // namespace

// ================================================================ 0x009dcd60
// @ 0x009dcd60
void __thiscall Curve1c58::Eval(void* out, float t, int* range) {
    char* rec = (char*)out;
    int*  o   = (int*)this;
    int   count = (int)((o[1] - o[0]) / 0x58);
    int   i;

    *(int*)(rec + 4)   = (int)t;
    *(float*)(rec + 8)  = g_fEps;
    *(float*)(rec + 0xc) = g_fEps;
    *(float*)(rec + 0x10) = g_fEps;
    *(void**)(rec + 0)  = &g_vtbl_c4;
    *(float*)(rec + 0x14) = g_fAlmost1;
    *(float*)(rec + 0x18) = 0.0f;
    *(float*)(rec + 0x1c) = 0.0f;
    *(float*)(rec + 0x28) = 0.0f;
    rec[0x20] = 0; rec[0x21] = 0; *(u16*)(rec + 0x22) = 0;
    *(float*)(rec + 0x2c) = 0.0f;
    rec[0x30] = 0; rec[0x31] = 0; *(u16*)(rec + 0x32) = 0;
    *(float*)(rec + 0x38) = 0.0f;
    *(float*)(rec + 0x3c) = 0.0f;
    rec[0x40] = 0; rec[0x41] = 0; *(u16*)(rec + 0x42) = 0;
    *(float*)(rec + 0x48) = 0.0f;
    *(float*)(rec + 0x4c) = 0.0f;
    rec[0x50] = 0; rec[0x51] = 0; *(u16*)(rec + 0x52) = 0;

    const char* base = (const char*)o[0];
    i = range[0];
    int j = range[1];
    const char* kLo = base + i * 0x58;
    const char* kHi = base + j * 0x58;
    if (i == j) {
        *(float*)(rec + 8)  = *(const float*)(kLo + 8);
        *(float*)(rec + 0xc) = *(const float*)(kLo + 0xc);
        *(float*)(rec + 0x10) = *(const float*)(kLo + 0x10);
        *(float*)(rec + 0x14) = *(const float*)(kLo + 0x14);
        return;
    }

    int im = (i > 0) ? i - 1 : 0;
    if (j < count - 1) ++j;
    const char* kPrev = base + im * 0x58;
    const char* kNext = base + j * 0x58;

    int tLo = *(const int*)(kLo + 4);
    int tHi = *(const int*)(kHi + 4);
    float u  = (t - (float)tLo) / (float)(tHi - tLo);
    float u2 = u * u;
    float u3 = u2 * u;

    float wh0 = (1.0f - u2 * g_f3) + u3 * g_f2;   // 1 - 3u^2 + 2u^3
    float wh1 = (u - u2 * g_f2) + u3;             // u - 2u^2 + u^3
    float wh2 = (u3 - u2);                        // u^3 - u^2
    float wh3 = (u2 * g_f3 - u3 * g_f2);          // 3u^2 - 2u^3

    for (int c = 0; c < 4; ++c) {
        const float* v = (const float*)(kLo + 8 + c * 4);
        const float* vn = (const float*)(kHi + 8 + c * 4);
        const float* vp = (const float*)(kPrev + 8 + c * 4);
        const float* vx = (const float*)(kNext + 8 + c * 4);

        int tPrev = *(const int*)(kPrev + 4);
        int gapA  = (tLo < tPrev) ? 100 : tLo;
        float dtA = (float)(gapA - tPrev);
        if (gapA - tPrev < 0) dtA += g_f2p32;
        int dA = (tLo <= tHi) ? tHi - tLo : tHi;
        float mA;
        u8 modeA = (u8)(*(const u8*)(kLo + 0x1d) & 3);
        if (modeA == 0) {
            mA = (*v - *vx) / ((float)dA + dtA) * (float)dA;
        } else if (modeA == 1) {
            mA = *v - *vp;
        } else if (modeA == 3) {
            mA = *(const float*)(kLo + 0x18);
        } else {
            mA = 0.0f;
        }

        int tHi2 = tHi;
        int gapB = (tHi2 < tLo) ? 100 : tHi2;
        float dtB = (float)(gapB - tLo);
        if (gapB - tLo < 0) dtB += g_f2p32;
        int dB = (tHi2 <= *(const int*)(kNext + 4)) ? *(const int*)(kNext + 4) - tHi2 : *(const int*)(kNext + 4);
        float mB;
        u8 modeB = (u8)(*(const u8*)(kHi + 0x14) & 3);
        if (modeB == 0) {
            mB = ((*vn - *vp) / ((float)dB + dtB)) * dtB;
        } else if (modeB == 1) {
            mB = *v - *vp;
        } else if (modeB == 3) {
            mB = dtB * *(const float*)(kHi + 0xc);
        } else {
            mB = 0.0f;
        }

        *(float*)(rec + 8 + c * 4) = *v * wh0 + mB * wh2 + mA * wh1 + *vn * wh3;
    }
}

// ================================================================ 0x009dc930
// 3-component spline, 0x44 stride.
// @ 0x009dc930
void __thiscall Curve3c44::Eval(void* out, float t, int* range) {
    char* rec = (char*)out;
    int*  o   = (int*)this;
    int   count = (int)((o[1] - o[0]) / 0x44);

    *(int*)(rec + 4)   = (int)t;
    *(float*)(rec + 8)  = 0.0f;
    *(float*)(rec + 0xc) = 0.0f;
    *(float*)(rec + 0x10) = 0.0f;
    rec[0x1c] = 0; rec[0x1d] = 0; *(u16*)(rec + 0x1e) = 0;
    *(float*)(rec + 0x14) = 0.0f;
    *(float*)(rec + 0x18) = 0.0f;
    *(float*)(rec + 0x24) = 0.0f;
    *(float*)(rec + 0x28) = 0.0f;
    rec[0x2c] = 0; rec[0x2d] = 0; *(u16*)(rec + 0x2e) = 0;
    *(float*)(rec + 0x34) = 0.0f;
    *(float*)(rec + 0x38) = 0.0f;
    rec[0x3c] = 0; rec[0x3d] = 0; *(u16*)(rec + 0x3e) = 0;
    *(void**)(rec + 0) = &g_vtbl_c0;

    const char* base = (const char*)o[0];
    int i = range[0];
    int j = range[1];
    const char* kLo = base + i * 0x44;
    const char* kHi = base + j * 0x44;
    if (i == j) {
        *(float*)(rec + 8)  = *(const float*)(kLo + 8);
        *(float*)(rec + 0xc) = *(const float*)(kLo + 0xc);
        *(float*)(rec + 0x10) = *(const float*)(kLo + 0x10);
        return;
    }

    int im = (i > 0) ? i - 1 : 0;
    if (j < count - 1) ++j;
    const char* kPrev = base + im * 0x44;
    const char* kNext = base + j * 0x44;

    int tLo = *(const int*)(kLo + 4);
    int tHi = *(const int*)(kHi + 4);
    float u  = (t - (float)tLo) / (float)(tHi - tLo);
    float u2 = u * u;
    float u3 = u2 * u;

    float wh0 = (1.0f - u2 * g_f3) + u3 * g_f2;
    float wh1 = (u - u2 * g_f2) + u3;
    float wh2 = (u3 - u2);
    float wh3 = (u2 * g_f3 - u3 * g_f2);

    for (int c = 0; c < 3; ++c) {
        const float* v  = (const float*)(kLo + 8 + c * 4);
        const float* vn = (const float*)(kHi + 8 + c * 4);

        int tPrev = *(const int*)(kPrev + 4);
        int gapA = (tLo < tPrev) ? 100 : tLo;
        float dtA = (float)(gapA - tPrev);
        if (gapA - tPrev < 0) dtA += g_f2p32;
        int dA = (tLo <= tHi) ? tHi - tLo : tHi;
        float mA;
        u8 modeA = (u8)(*(const u8*)(kLo + 0x1d) & 3);
        if (modeA == 0) {
            mA = (*v - *(const float*)(kNext + 8 + c * 4)) / ((float)dA + dtA) * (float)dA;
        } else if (modeA == 1) {
            mA = *v - *(const float*)(kPrev + 8 + c * 4);
        } else if (modeA == 3) {
            mA = *(const float*)(kLo + 0x18);
        } else {
            mA = 0.0f;
        }

        int gapB = (tHi < tLo) ? 100 : tHi;
        float dtB = (float)(gapB - tLo);
        if (gapB - tLo < 0) dtB += g_f2p32;
        int dT = *(const int*)(kNext + 4);
        int dB = (tHi <= dT) ? dT - tHi : dT;
        float mB;
        u8 modeB = (u8)(*(const u8*)(kHi + 0x14) & 3);
        if (modeB == 0) {
            mB = ((*(const float*)(kNext + 8 + c * 4) - *(const float*)(kPrev + 8 + c * 4))
                  / ((float)dB + dtB)) * dtB;
        } else if (modeB == 1) {
            mB = *v - *(const float*)(kPrev + 8 + c * 4);
        } else if (modeB == 3) {
            mB = dtB * *(const float*)(kHi + 0xc);
        } else {
            mB = 0.0f;
        }

        *(float*)(rec + 8 + c * 4) = *(const float*)(kPrev + 8 + c * 4) * wh0
                                   + mB * wh2 + mA * wh1 + *v * wh3;
    }
}

// ================================================================ 0x009dd1d0
// 1-component spline, 0x1c stride.
// @ 0x009dd1d0
void __thiscall Curve1c1c::Eval(void* out, float t, int* range) {
    char* rec = (char*)out;
    int*  o   = (int*)this;
    int   count = (int)((o[1] - o[0]) / 0x1c);

    *(int*)(rec + 4)   = (int)t;
    *(void**)(rec + 0)  = &g_vtbl_c8;
    *(float*)(rec + 8)  = g_f0p5;
    rec[0x14] = 0; rec[0x15] = 0;
    *(float*)(rec + 0xc) = 0.0f;
    *(float*)(rec + 0x10) = 0.0f;
    *(u16*)(rec + 0x16) = 0;

    const char* base = (const char*)o[0];
    int i = range[0];
    int j = range[1];
    const char* kLo = base + i * 0x1c;
    const char* kHi = base + j * 0x1c;
    if (i == j) {
        *(float*)(rec + 8) = *(const float*)(kLo + 8);
        return;
    }

    int im = (i > 0) ? i - 1 : 0;
    if (j < count - 1) ++j;
    const char* kPrev = base + im * 0x1c;
    const char* kNext = base + j * 0x1c;

    int tLo = *(const int*)(kLo + 4);
    int tHi = *(const int*)(kHi + 4);
    float u  = (t - (float)tLo) / (float)(tHi - tLo);
    float u2 = u * u;
    float u3 = u2 * u;

    float wh0 = (1.0f - u2 * g_f3) + u3 * g_f2;
    float wh1 = (u - u2 * g_f2) + u3;
    float wh2 = (u3 - u2);
    float wh3 = (u2 * g_f3 - u3 * g_f2);

    const float* v  = (const float*)(kLo + 8);

    int tPrev = *(const int*)(kPrev + 4);
    int gapA = (tLo < tPrev) ? 100 : tLo;
    float dtA = (float)(gapA - tPrev);
    if (gapA - tPrev < 0) dtA += g_f2p32;
    int dA = (tLo <= tHi) ? tHi - tLo : tHi;
    float mA;
    u8 modeA = (u8)(*(const u8*)(kLo + 0x15) & 3);
    if (modeA == 0) {
        mA = (*v - *(const float*)(kNext + 8)) / ((float)dA + dtA) * (float)dA;
    } else if (modeA == 1) {
        mA = *v - *(const float*)(kPrev + 8);
    } else if (modeA == 3) {
        mA = *(const float*)(kLo + 0x10);
    } else {
        mA = 0.0f;
    }

    int gapB = (tHi < tLo) ? 100 : tHi;
    float dtB = (float)(gapB - tLo);
    if (gapB - tLo < 0) dtB += g_f2p32;
    int dT = *(const int*)(kNext + 4);
    int dB = (tHi <= dT) ? dT - tHi : dT;
    float mB;
    u8 modeB = (u8)(*(const u8*)(kHi + 0x14) & 3);
    if (modeB == 0) {
        mB = ((*(const float*)(kNext + 8) - *(const float*)(kPrev + 8))
              / ((float)dB + dtB)) * dtB;
    } else if (modeB == 1) {
        mB = *v - *(const float*)(kPrev + 8);
    } else if (modeB == 3) {
        mB = dtB * *(const float*)(kHi + 0xc);
    } else {
        mB = 0.0f;
    }

    *(float*)(rec + 8) = *(const float*)(kPrev + 8) * wh0
                       + mB * wh2 + mA * wh1 + *v * wh3;
}

// ================================================================ 0x009dcc50
// @ 0x009dcc50
void* __thiscall Curve3c44::Sample(void* out, float t) {
    int key[2];
    ((Curve3c44*)this)->Find(t, key);
    ((Curve3c44*)this)->Eval(out, t, key);
    return out;
}

// ================================================================ 0x009dd0c0
// @ 0x009dd0c0
void* __thiscall Curve1c58::Sample(void* out, float t) {
    int key[2];
    ((Curve1c58*)this)->Find(t, key);
    ((Curve1c58*)this)->Eval(out, t, key);
    return out;
}

// ================================================================ 0x009dd440
// @ 0x009dd440
void* __thiscall Curve1c1c::Sample(void* out, float t) {
    int key[2];
    ((Curve1c1c*)this)->Find(t, key);
    ((Curve1c1c*)this)->Eval(out, t, key);
    return out;
}

// ================================================================ 0x009dd480
// 0xa4-stride key lookup with a float time; returns the frac in st0.
struct CurveStr0a4 { float __thiscall Lookup(float t, char** out); };

// @ 0x009dd480
float __thiscall CurveStr0a4::Lookup(float t, char** out) {
    int* o = (int*)this;
    unsigned idx = 0;
    if (o[0] != 0) {
        const float* p = (const float*)o[1];
        unsigned prev = 0;
        do {
            prev = idx;
            if (t < *p) break;
            ++idx;
            p += 0x29;                       // 0xa4 bytes
        } while (idx != (unsigned)o[0]);
        if (idx != 0) {
            unsigned off = prev * 0xa4;
            if (idx == (unsigned)o[0]) {
                char* b = (char*)o[1];
                *out = b + off + 4;
                out[1] = b + off + 4;
                return 0.0f;
            }
            const char* b = (const char*)o[1];
            float hi = *(const float*)(b + idx * 0xa4);
            float lo = *(const float*)(b + off);
            *out = (char*)o[1] + off + 4;
            out[1] = (char*)o[1] + idx * 0xa4 + 4;
            return (t - lo) / (hi - lo);
        }
    }
    *out = (char*)o[1] + 4;
    out[1] = (char*)o[1] + 4;
    return 0.0f;
}

// ================================================================ 0x009dd530
// Copy 0x44-byte records into a destination range.
// @ 0x009dd530
void __cdecl FUN_009dd530(void** dstEnd, char* first, char* last, char* dst) {
    *dstEnd = dst;
    if (first != last) {
        char* d = dst;
        do {
            if (dst != 0) {
                int* s = (first != 0) ? (int*)(first + 4) : 0;
                *(int*)(d - 0xc) = s ? *s : 0;
                *(void**)dst    = &g_vtbl_c0;
                *(float*)(d - 8)  = *(const float*)(first + 8);
                *(float*)(d - 4)  = *(const float*)(first + 0xc);
                *(float*)(d)      = *(const float*)(first + 0x10);
                int* sp = (int*)(first + 0x14);
                int* dp = (int*)(d + 4);
                for (int k = 0xc; k != 0; --k) *dp++ = *sp++;
            }
            first += 0x44;
            dst   += 0x44;
            d     += 0x44;
        } while (first != last);
        *dstEnd = dst;
    }
}

// ================================================================ 0x009dd5b0
// Copy 0x58-byte records into a destination range.
// @ 0x009dd5b0
void __cdecl FUN_009dd5b0(void** dstEnd, char* first, char* last, char* dst) {
    *dstEnd = dst;
    if (first != last) {
        char* d = dst;
        do {
            if (dst != 0) {
                int* s = (first != 0) ? (int*)(first + 4) : 0;
                *(int*)(d - 0xc) = s ? *s : 0;
                *(void**)dst    = &g_vtbl_c4;
                *(float*)(d - 8)  = *(const float*)(first + 8);
                *(float*)(d - 4)  = *(const float*)(first + 0xc);
                *(float*)(d)      = *(const float*)(first + 0x10);
                *(float*)(d + 4)  = *(const float*)(first + 0x14);
                int* sp = (int*)(first + 0x18);
                int* dp = (int*)(d + 8);
                for (int k = 0x10; k != 0; --k) *dp++ = *sp++;
            }
            first += 0x58;
            dst   += 0x58;
            d     += 0x58;
        } while (first != last);
        *dstEnd = dst;
    }
}

// ================================================================ 0x009dd630
// Copy 0x1c-byte records into a destination range.
// @ 0x009dd630
void __cdecl FUN_009dd630(void** dstEnd, char* first, char* last, char* dst) {
    void** endp = dstEnd;
    *endp = dst;
    if (first == last) return;
    do {
        if (dst != 0) {
            int* s = (first != 0) ? (int*)(first + 4) : 0;
            *(int*)(dst + 4) = s ? *s : 0;
            *(void**)dst     = &g_vtbl_c8;
            *(int*)(dst + 8)  = *(const int*)(first + 8);
            *(int*)(dst + 0xc) = *(const int*)(first + 0xc);
            *(int*)(dst + 0x10) = *(const int*)(first + 0x10);
            *(int*)(dst + 0x14) = *(const int*)(first + 0x14);
            *(int*)(dst + 0x18) = *(const int*)(first + 0x18);
        }
        first += 0x1c;
        dst   += 0x1c;
    } while (first != last);
    *endp = dst;
}
