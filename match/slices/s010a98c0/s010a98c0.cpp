// Slice s010a98c0 -- Havok 1d constraint / simplex-solver helpers (gold3).
// Flags: /O2 /MD /Gy /TP /GS-
//
// x87 build: every float op in this slice is `fld`/`fmul`/`faddp`, so no
// /arch:SSE or /fp:fast here (unlike slice s01062ce0).
#include "types.h"

extern "C" void f010a8cf0(void*);                            // 0x010a8cf0
extern "C" void f010a8cb0(void*);                            // 0x010a8cb0
extern "C" void f010a90b0(void*, void*, void*, void*);       // 0x010a90b0
extern "C" void f010a9580(void*, void*, int, void*, void*);  // 0x010a9580
extern "C" void f010a8b90(void*);                            // 0x010a8b90

extern float g_14a23a4;                                      // 1.1920929e-07f

// A Havok body->matrix entry block (0x50..0x78 is a 3x3 rotation).
static inline float M(int p, int off) { return *(float*)(p + off); }

// ---------------------------------------------------------------- 0x010a98c0
// 1d constraint solver step: a switch on the state word p[0xc] driven by a
// jump table; cases 2/3/4 pull one constraint from the queue, run its
// projected-gradient step through 0x010a90b0/0x010a9580 and advance the state.
// @ 0x010a98c0
void f010a98c0(int* p)
{
    for (;;) {
        switch (p[0xc]) {
        case 1:
            f010a8cf0(p);
            return;
        case 2: {
            int scratch[4];
            f010a8cf0(p);
            f010a8cb0(scratch);
            if (*(uint8_t*)scratch) {
                f010a90b0(p, (void*)p[1], (void*)(p[0xe] + 0x10), (void*)(p[0xf] + 0x10));
                return;
            }
            int* dst = (int*)p[0xf];
            dst[4] = scratch[2];
            dst[5] = scratch[3];
            dst[6] = 0;
            dst[7] = 0;
            p[0] = p[3];
            p[1] = p[4];
            p[2] = p[5];
            p[0xc] = 1;
            continue;
        }
        case 3: {
            int scratch[8];
            int* pcur = p + 1;
            f010a8cf0(p);
            f010a8cb0(scratch);
            if (*(uint8_t*)scratch == 0) {
                f010a8cb0(scratch + 2);
                if (*(uint8_t*)((char*)scratch + 8) == 0) {
                    int* dst = (int*)p[0xf];
                    dst[4] = scratch[2];
                    dst[5] = scratch[3];
                    dst[6] = 0;
                    dst[7] = 0;
                    p[0] = p[6];
                    p[1] = p[7];
                    p[2] = p[8];
                    p[0xc] = 1;
                    continue;
                }
            }
            {
                int i = 0;
                do {
                    if (p[0xc] < 3) break;
                    f010a90b0(p, (void*)*pcur, (void*)(p[0xe] + 0x10), scratch);
                    f010a8cb0((char*)scratch + 12);
                    if (*(uint8_t*)((char*)scratch + 12) == 0) {
                        int* e = p + i * -3 + 3;
                        e[0] = p[3];
                        e[1] = p[4];
                        e[2] = p[5];
                        p[3] = p[6];
                        p[4] = p[7];
                        p[5] = p[8];
                        p[0xc] = 2;
                        break;
                    }
                    i++;
                    pcur += 3;
                } while (i < 2);
                if (i >= 2) {
                    if (p[0xc] > 2) {
                        f010a9580(p, (void*)p[7], 1, (void*)(p[0xe] + 0x10), (void*)(p[0xf] + 0x10));
                        return;
                    }
                }
            }
            continue;
        }
        case 4: {
            int loc[8];
            int i = 0;
            f010a8b90(p);
            do {
                f010a9580(p, (void*)p[10], 0, (void*)(p[0xe] + 0x10), loc);
                int* e = p + i * 3;
                f010a8cb0(loc);
                if (*(uint8_t*)loc == 0) {
                    e[0] = p[6];
                    e[1] = p[7];
                    e[2] = p[8];
                    p[6] = p[9];
                    p[7] = p[10];
                    p[8] = p[0xb];
                    p[0xc] = 3;
                    i = 10;
                }
                i++;
            } while (i < 3);
            if (i >= 10) continue;
            {
                float loc40[4];
                int* src = (int*)p[0xe];
                loc40[0] = *(float*)((char*)src + 0x10);
                loc40[1] = *(float*)((char*)src + 0x14);
                loc40[2] = *(float*)((char*)src + 0x18);
                loc40[3] = *(float*)((char*)src + 0x1c);
                int u = p[10];
                int saved = p[0xc];
                f010a9580(p, (void*)p[7], 0, loc40, loc40);
                if (saved == p[0xc]) f010a9580(p, (void*)u, 0, loc40, loc40);
                if (saved == p[0xc]) f010a9580(p, (void*)u, 0, loc40, loc40);
                if (saved == p[0xc]) f010a9580(p, (void*)u, 0, loc40, loc40);
                int* dst = (int*)p[0xf];
                dst[4] = *(int*)&loc40[0];
                dst[5] = *(int*)&loc40[1];
                dst[6] = *(int*)&loc40[2];
                dst[7] = *(int*)&loc40[3];
                int mx = 0;
                if (-1 < *(int*)(p[2] + 0xc)) mx = *(int*)(p[2] + 0xc);
                if (mx <= *(int*)(p[5] + 0xc)) mx = *(int*)(p[5] + 0xc);
                if (mx <= *(int*)(p[8] + 0xc)) mx = *(int*)(p[8] + 0xc);
                if (mx <= *(int*)(p[0xb] + 0xc)) mx = *(int*)(p[0xb] + 0xc);
                int k = 0;
                int* pi = p + 2;
                do {
                    if (mx == *(int*)(*pi + 0xc)) {
                        int* e = p + k * 3;
                        e[0] = p[9];
                        e[1] = p[10];
                        e[2] = p[0xb];
                        break;
                    }
                    k++;
                    pi += 3;
                } while (k < 4);
                p[0xc] = p[0xc] - 1;
                *(int*)(p[2] + 0xc) = 0;
                *(int*)(p[5] + 0xc) = 0;
                *(int*)(p[8] + 0xc) = 0;
            }
            return;
        }
        default:
            return;
        }
    }
}

// ---------------------------------------------------------------- 0x010a9d30
// @ 0x010a9d30
void f010a9d30(float* a, float* b)
{
    float l74 = a[0x10];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    int i = 0;
    int l38 = 0;
    int l50[6] = { 0, 0, 0, 0, 0, 0 };
    float* l14 = b;
    int l20 = 0;
    float l1c = 0.0f;
    if (0 < (int)a[0x13]) {
        int off = 0;
        do {
            char* e = (char*)(int)b[9] + off;
            e[0] = 0;
            e[1] = 0;
            *(int*)(e + 4) = 0;
            *(int*)(e + 8) = 0;
            *(int*)(e + 0xc) = 0;
            i++;
            off += 0x10;
        } while (i < (int)a[0x13]);
    }
    if (0.0f <= l74) {
        for (;;) {
            int n = l20;
            float l78 = l74;
            int l70 = -1;
            if (0 < (int)a[0x13]) {
                int idx = 0, c64 = 0, i8 = 0;
                do {
                    if ((((l20 < 1) || (l50[0] != idx)) &&
                         ((l20 < 2 || (l50[3] != idx)))) &&
                        (((l20 < 3 || (l38 != idx)) &&
                         (*(int*)((char*)(int)b[9] + 0xc + i8) == 0)))) {
                        float* e = (float*)((char*)(int)a[0x12] + c64);
                        float f1 = -((b[5] - e[5]) * e[1] +
                                     ((b[4] - *(float*)((char*)(int)a[0x12] + 0x10 + c64)) * e[0] +
                                      (b[6] - e[6]) * e[2]));
                        if (f1 < 0.0f == (f1 == 0.0f)) {
                            float f2 = -l1c;
                            f2 = ((f2 * e[5] + b[1]) * e[1] +
                                  ((f2 * e[4] + b[0]) * e[0] +
                                   (f2 * e[6] + b[2]) * e[2])) + e[3];
                            if (f2 < 1.1920929e-07f != (f2 == 1.1920929e-07f)) f2 = 0.0f;
                            f2 = f2 + *(float*)((char*)(int)l14[9] + 8 + i8);
                            if (f2 < f1 * l78) {
                                l78 = f2 / f1;
                                l70 = idx;
                            }
                        }
                    }
                    c64 += 0x40;
                    idx++;
                    i8 += 0x10;
                } while (idx < (int)a[0x13]);
            }
            if (0.0001f < l78) {
                l1c = l78 + l1c;
                l74 = l74 - l78;
                b[0] = l78 * b[4] + b[0];
                b[1] = l78 * b[5] + b[1];
                b[2] = l78 * b[6] + b[2];
                b[3] = l78 * b[7] + b[3];
                if (0 < l20) {
                    int* pi = l50 + 2;
                    int k = l20;
                    do {
                        char* e = (char*)*pi;
                        pi += 3;
                        k--;
                        *(float*)(e + 4) = l78 + *(float*)(e + 4);
                        e[0] = 1;
                    } while (k != 0);
                }
                b[8] = l1c;
                if (a[0x11] < l1c) return;
            }
            if (l70 < 0) break;
            int i7 = l20 * 3;
            int i8 = l20 * 3;
            l20 = l20 + 1;
            l50[i8 + 1] = l70 * 0x40 + (int)a[0x12];
            i8 = l70 * 0x10 + (int)b[9];
            float f1 = *(float*)(l70 * 0x10 + 8 + (int)b[9]) + 1.1920929e-07f;
            l50[i7 + 2] = i8;
            *(float*)(i8 + 8) = f1 + f1;
            l50[i7] = l70;
            f010a98c0(l50);
            if (l74 < 0.0f) return;
        }
        b[8] = a[0x10];
    }
}

// ---------------------------------------------------------------- 0x010aa040
struct hkJacobianElement;
struct hk1Lin2AngJacobian {
    char pad[0x30];
    hkJacobianElement* next(int i);      // 0x010aa040
};
// @ 0x010aa040
hkJacobianElement* hk1Lin2AngJacobian::next(int i)
{
    return (hkJacobianElement*)((char*)this + i * 0x30);
}

// ---------------------------------------------------------------- 0x010aa050
struct hkConstraintStack {
    int* cur;
    int* next;
};
// @ 0x010aa050
void f010aa050(float s, int body, int* stack, int index)
{
    float v = *(float*)(body + 4);
    *(float*)(index * -0x30 + *stack + 0xc) = s * v;
}

// ---------------------------------------------------------------- 0x010aa080
// @ 0x010aa080
void f010aa080(int ctx, int* stack, int a3, int a4)
{
    int b20 = *(int*)(ctx + 0x20);
    int b24 = *(int*)(ctx + 0x24);
    int b2c = *(int*)(ctx + 0x2c);
    int b28 = *(int*)(ctx + 0x28);
    int* out = (int*)stack[1];
    out[1] = *stack - b24;
    out[2] = b28 - b20;
    out[3] = b2c - b20;
    out[0] = 0x180101;
    out[5] = a3;
    out[4] = a4;
    stack[1] = (int)(out + 6);
}

// ---------------------------------------------------------------- 0x010aa0d0
// @ 0x010aa0d0
void f010aa0d0(float* a, float* b, int* stack)
{
    int* o = (int*)stack[1];
    int base = stack[0];
    int* ia = (int*)a;
    ((float*)o)[1] = a[2] * b[0];
    ((float*)o)[2] = a[3] * b[0];
    o[3] = ia[1];
    o[4] = ia[4];
    o[5] = ia[5];
    o[6] = 0x3f800000;
    o[0] = 0x1c0606;
    *(float*)(base + 0x1c) = b[1] * a[0];
    stack[0] = base + 0x20;
    stack[1] = (int)(o + 7);
}

// ---------------------------------------------------------------- 0x010aa130
// @ 0x010aa130
void f010aa130(float* a, float* b, int* stack, float* out)
{
    int base = stack[0];
    int* o = (int*)out;
    int* ia = (int*)a;
    out[0] = a[2] * b[0];
    out[1] = a[3] * b[0];
    o[2] = ia[1];
    o[3] = ia[4];
    o[4] = ia[5];
    o[5] = 0x3f800000;
    *(float*)(base + 0x1c) = b[1] * a[0];
    stack[0] = base + 0x20;
}

// ---------------------------------------------------------------- 0x010aa180
// @ 0x010aa180
void f010aa180(float* a, float* b, int* stack)
{
    int* o = (int*)stack[1];
    int base = stack[0];
    int* ia = (int*)a;
    ((float*)o)[1] = a[2] * b[0];
    ((float*)o)[2] = a[3] * b[0];
    o[3] = ia[1];
    o[6] = 0x3f800000;
    o[4] = ia[4];
    o[5] = ia[5];
    o[0] = 0x1c0507;
    *(float*)(base + 0xc) = b[1] * a[0];
    stack[0] = base + 0x30;
    stack[1] = (int)(o + 7);
}

// ---------------------------------------------------------------- 0x010aa1e0
// Angular bilateral constraint: build both 4-vectors, scale the last component
// by the lever arm and the mass-weighted inverse of the combined inertia.
// @ 0x010aa1e0
void f010aa1e0(float* a, int b, int* stack)
{
    int bodyA = *(int*)(b + 0x28);
    float lever = *(float*)(b + 0x18);
    int bodyB = *(int*)(b + 0x2c);
    float* e = (float*)*stack;
    if (*(char*)(bodyA + 0xc) == 0) {
        float x = a[4], y = a[5], z = a[6];
        e[0] = x * M(bodyA, 0x50) + (y * M(bodyA, 0x60) + z * M(bodyA, 0x70));
        e[1] = x * M(bodyA, 0x54) + (y * M(bodyA, 0x64) + z * M(bodyA, 0x74));
        e[2] = x * M(bodyA, 0x58) + (y * M(bodyA, 0x68) + z * M(bodyA, 0x78));
        e[3] = 0.0f;
    } else {
        e[0] = a[4];
        e[1] = a[5];
        e[2] = a[6];
        e[3] = a[7];
    }
    float nx = -a[4];
    if (*(char*)(bodyB + 0xc) == 0) {
        float ny = -a[5];
        float nz = -a[6];
        e[4] = nx * M(bodyB, 0x50) + (nz * M(bodyB, 0x70) + ny * M(bodyB, 0x60));
        e[5] = nz * M(bodyB, 0x74) + (nx * M(bodyB, 0x54) + ny * M(bodyB, 0x64));
        e[6] = nz * M(bodyB, 0x78) + (nx * M(bodyB, 0x58) + ny * M(bodyB, 0x68));
        e[7] = 0.0f;
    } else {
        e[4] = nx;
        e[5] = -a[5];
        e[6] = -a[6];
        e[7] = -a[7];
    }
    // Original x87 rounding structure (0x010aa322..0x010aa373):
    //   q2/q4/q5/q6 are stored to 32-bit float slots and reloaded; q0/q1 are
    //   never stored and stay in extended-precision x87 registers (so a huge e[1]
    //   does not overflow to inf before the multiply -- `inf * 0` would be NaN).
    //   Each product is extended (float operand, extended result) and the three
    // Original x87 rounding structure (0x010aa2ea..0x010aa36f). Trace of the x87
    // stack, top first:
    //   q0 = e0^2 , q1 = e1^2   -> stay in x87 registers (never fstp'd)
    //   q2/q4/q5/q6             -> fstp'd to 32-bit float slots and reloaded
    //   0x010aa327 fstp [esp+0x20]  -> `q0*A30` is rounded to FLOAT on its own
    //   0x010aa32b fmul [edx+0x34]  -> `q1*A34` stays extended
    //   0x010aa332 fmul [edx+0x38]  -> `q2*A38` stays extended
    //   `mem20 = q4*B30 + q0*A30` (fstp -> float), `mem24 = q5*B34 + q1*A34`
    //   (fstp -> float), `mem18 = q6*B38` (fstp -> float). Combine order is
    //   `((q2*A38 + mem18) + mem24) + mem20 + eps`, extended, one rounding at the
    //   e[3] store.
    // Separately rounding q0*A30 to float is what makes a huge e[0] turn the pair
    // into NaN (inf*finite + -inf) instead of a finite value.
    float q2 = e[2] * e[2], q4 = e[4] * e[4], q5 = e[5] * e[5], q6 = e[6] * e[6];
    long double q0 = (long double)e[0] * e[0];
    long double q1 = (long double)e[1] * e[1];
    float m18 = (float)((long double)q6 * M(bodyB, 0x38));
    float m24 = (float)((long double)q5 * M(bodyB, 0x34) + q1 * M(bodyA, 0x34));
    float t20 = (float)(q0 * M(bodyA, 0x30));
    float m20 = (float)((long double)q4 * M(bodyB, 0x30) + t20);
    long double den = ((((long double)q2 * M(bodyA, 0x38) + m18) + m24) + m20) +
                      g_14a23a4;
    e[3] = (float)((long double)lever / den);
    int* cmd = (int*)stack[1];
    cmd[0] = 0x4060e;
    stack[0] = (int)(e + 8);
    stack[1] = (int)(cmd + 1);
    e[7] = -(a[0] * a[8] + (a[1] * a[9] + a[2] * a[10])) * *(float*)(b + 0x14);
}

// ---------------------------------------------------------------- 0x010aa3c0
// Angular friction rows: one 8-float row + one 3-word command per constraint.
// @ 0x010aa3c0
// The original is call-free: its last register write before both exits is
// `mov eax,[ebp+0x10]` (= param_3, the stack cursor), so equivalence compares
// eax. Model that by returning param_3 (no float conversions are involved, so
// this adds no helper calls).
int f010aa3c0(int* p, float* b, int* stack_)
{
    float* e = (float*)*stack_;
    int* cmd = (int*)stack_[1];
    float* v = (float*)*p;
    int n = p[3];
    if (n - 1 >= 0) {
        float* src = (float*)(p[1] + 4);
        do {
            // b[] holds two body pointers in float slots; the original loads them
            // as raw dwords (`mov edx,[ecx+0x2c]`), so reinterpret, don't convert.
            int bodyB = *(int*)(b + 0xb);
            int bodyA = *(int*)(b + 10);
            float bx = v[0], by = v[1], bz = v[2];
            if (*(char*)(bodyA + 0xc) == 0) {
                e[0] = bx * M(bodyA, 0x50) + (by * M(bodyA, 0x60) + bz * M(bodyA, 0x70));
                e[1] = bx * M(bodyA, 0x54) + (by * M(bodyA, 0x64) + bz * M(bodyA, 0x74));
                e[2] = bx * M(bodyA, 0x58) + (by * M(bodyA, 0x68) + bz * M(bodyA, 0x78));
                e[3] = 0.0f;
            } else {
                e[0] = v[0];
                e[1] = v[1];
                e[2] = v[2];
                e[3] = v[3];
            }
            float nx = -v[0];
            if (*(char*)(bodyB + 0xc) == 0) {
                float ny = -v[1];
                float nz = -v[2];
                e[4] = nx * M(bodyB, 0x50) + (ny * M(bodyB, 0x60) + nz * M(bodyB, 0x70));
                e[5] = ny * M(bodyB, 0x64) + (nz * M(bodyB, 0x74) + nx * M(bodyB, 0x54));
                e[6] = ny * M(bodyB, 0x68) + (nz * M(bodyB, 0x78) + nx * M(bodyB, 0x58));
                e[7] = 0.0f;
            } else {
                e[4] = nx;
                e[5] = -v[1];
                e[6] = -v[2];
                e[7] = -v[3];
            }
            // Original x87 rounding structure (0x010aa4f0..0x010aa59a), same shape as
            // 010aa1e0 above (trace there is annotated in full): q2/q4/q5/q6 pass
            // through 32-bit float slots, q0/q1 stay in x87 registers,
            // `mem30 = q0*A30` is rounded to float on its own (0x010aa53d) before
            // `mem20 = q4*B30 + mem30`, `mem24 = q5*B34 + q1*A34` (q1 extended) and
            // `mem18 = q6*B38` are each fstp'd to float, and the combine is
            // `((q6*B38 + q2*A38) + mem24) + mem20 + eps` in extended precision
            // (0x010aa582..0x010aa594) with one rounding at the e[3] store.
            float q2 = e[2] * e[2], q4 = e[4] * e[4], q5 = e[5] * e[5], q6 = e[6] * e[6];
            long double q0 = (long double)e[0] * e[0];
            long double q1 = (long double)e[1] * e[1];
            float m18 = (float)((long double)q6 * M(bodyB, 0x38));
            float m24 = (float)((long double)q5 * M(bodyB, 0x34) + q1 * M(bodyA, 0x34));
            float m30 = (float)(q0 * M(bodyA, 0x30));
            float m20 = (float)((long double)q4 * M(bodyB, 0x30) + m30);
            long double den = ((((long double)m18 + (long double)q2 * M(bodyA, 0x38)) +
                                m24) +
                               m20) +
                              g_14a23a4;
            e[3] = (float)(1.0L / den);
            cmd[0] = 0xc060b;
            cmd[2] = 0x3f800000;
            // `fld [ecx+8]` (ecx = param_1) / `fmul [b]` / `fstp [edi-8]`: the middle
            // command word is p[2] read as a float and scaled by the time step b[0];
            // it is stored as a *float* (a raw fstp), so no int conversion.
            *(float*)(cmd + 1) = *(float*)(p + 2) * b[0];
            e[7] = *src * b[1];
            src += 2;
            v += 4;
            e += 8;
            cmd += 3;
        } while (--n != 0);
    }
    stack_[1] = (int)cmd;
    int* end = stack_;
    end[0] = (int)e;
    return (int)end;
}
