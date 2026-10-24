// Slice s009cfd40 (gold5 #15) -- SP:: creature-animation / dynamics helpers.
// Hand-written reconstruction from the disassembly + Ghidra decompilation.
// Callee addresses are relocations (masked); only the call shapes and the surrounding code matter.
//
// VA map:
//   009cfd40 ( 126B)  009cfdc0 ( 722B)  009d00a0 ( 466B)  009d0280 ( 478B)
//   009d0460 (1495B)  009d0a40 ( 195B)  009d0b10 (  98B)  009d0b80 ( 133B)
//   009d0c10 ( 106B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int uint;

// ---- module-level float constants (values verified against the image) ----
extern float g_1e6;    // 0x014479b4 = 1000000.0f
extern float g_m1e6;   // 0x013ef654 = -1000000.0f
extern float g_2pi;    // 0x0155145c = 6.28318548f   (2*pi)
extern float g_08;     // 0x015514a0 = 0.8f
extern float g_h05;    // 0x015514a4 = 0.5f
extern float g_09;     // 0x015514a8 = 0.9f
extern float g_c08;    // 0x015514ac = 0.8f
extern float g_m2;     // 0x015514b0 = -2.0f
extern float g_10;     // 0x015514b4 = 10.0f
extern float g_25;     // 0x015514b8 = 2.5f
extern float g_eps;    // 0x014479b0 = 1.0e-6f
extern float g_m1;     // 0x013eb1bc = -1.0f
extern float g_2;      // 0x01470f1c = 2.0f
extern float g_half;   // 0x01471064 = 0.5f
extern float g_1;      // 0x01485720 = 1.0f

// ---- external callees (relocations; shapes only) ----
extern "C" float FUN_009cdbe0(float, float, float, float, float);   // ?FUN_009cdbe0@@YAMMMMMM@Z
extern "C" __m128 FUN_009cdb20(float, float);   // returns in xmm0 (original: movss [esp],xmm0 right after the call)

struct Inner70 { char pad[0x70]; float c; };
struct TgtVec { char pad[0x10c]; float f10c, f110, f114; };   // *this->f0's +0x00 target

// ---------------------------------------------------------------------------
// "SA": the skinned-bone objects the animation containers walk.
// ---------------------------------------------------------------------------
struct SA {
    void*    q0_0;                // +0x00 pointer used by 009d0460/009d0b10
    void*    p04;                 // +0x04 pointer
    char     pad08[0x48 - 0x08];
    float    f48;                 // +0x48
    float    f4c;                 // +0x4c
    char     pad50[0x58 - 0x50];
    int      f58;                 // +0x58
    char     pad5c[0x6c - 0x5c];
    float    f6c;                 // +0x6c
    char     pad70[0x7c - 0x70];
    float    f7c;                 // +0x7c
    float    f80;                 // +0x80
    float    f84;                 // +0x84
    float    f88, f8c, f90, f94, f98;
    float    f9c;                 // +0x9c
    float    fa0;                 // +0xa0
    float    fa4;                 // +0xa4
    char     padA8[0xc8 - 0xa8];
    void*    fC8;                 // +0xc8
    char     padCC[0x114 - 0xcc];
    float    f114;                // +0x114
    char     pad118[0x350 - 0x118];
    float    f350;                // +0x350
    float    f354;                // +0x354
    float    f358;                // +0x358
    char     pad35c[0x434 - 0x35c];
    float    f434;                // +0x434

    void   Integrate(float dt, float* v, void* a3);                    // ?Bone_IntegrateVelocity@@..
    float* FA90(float* out, void* p, float a, float b, float c, float d);   // 0x009cfa90
    float* F370(float* out, void* p, float a, float b, float c);            // 0x009ce370
};

// "BN": the 2-element locator array held by a dynamics container (+0x04).
struct BN {
    float  f0, f4, f8;            // +0x00 vec3
    char   pad0c[0x58 - 0x0c];
    int    f58;                   // +0x58
    char   pad5c[0xc8 - 0x5c];
    void*  fC8;                   // +0xc8
};

// "BP": resolved slot object (has the 0x350 vector and 0x434 scalar).
struct BP {
    char  pad[0x350];
    float f350, f354, f358;       // +0x350
    char  pad35c[0x434 - 0x35c];
    float f434;                   // +0x434
};

// ===========================================================================
// @ 0x009cfd40  FUN_009cfd40
// __thiscall (ret 0xc): build (dir*scale) then integrate the bone by dt.
// ===========================================================================
struct Host40 {
    char  pad[4];
    SA*   f4;                     // +0x04
    void FUN_009cfd40(float* dir, void* a3, float dt);
};

void Host40::FUN_009cfd40(float* dir, void* a3, float dt)
{
    SA* b = f4;
    if (b->f48 < dt) {
        dt = dt - b->f48;
        b->f4c = dt;
        float c = ((Inner70*)b->p04)->c;
        float v[3];
        v[0] = dir[0] * c;
        v[1] = dir[1] * c;
        v[2] = dir[2] * c;
        b->Integrate(dt, v, a3);
    }
}

// ===========================================================================
// @ 0x009cfdc0  FUN_009cfdc0
// __thiscall (ret 0x18): bounding box of the bones' (f7c, f80) pairs.
// ===========================================================================
struct HostBC {
    char  pad[4];
    SA**  begin;                  // +0x04
    SA**  end;                    // +0x08
    void FUN_009cfdc0(float* w, float* h, float* minX, float* maxX, float* minY, float* maxY);
};

void HostBC::FUN_009cfdc0(float* w, float* h, float* minX, float* maxX, float* minY, float* maxY)
{
    *minX = g_1e6;
    *maxX = g_m1e6;
    *minY = g_1e6;
    *maxY = g_m1e6;
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    for (uint i = 0; i < n; i++) {
        SA* e = begin[i];
        float x = e->f7c;
        float y = e->f80;
        if (x > *maxX) *maxX = x;
        if (x < *minX) *minX = x;
        if (y > *maxY) *maxY = y;
        if (y < *minY) *minY = y;
    }
    *w = *maxX - *minX;
    *h = *maxY - *minY;
    if (*w < 0.01f || (n == 2 && *w < *h))
        *w = 0.0f;
    if (*h < 0.01f || (n == 2 && *h < *w))
        *h = 0.0f;
}

// ===========================================================================
// @ 0x009d00a0  FUN_009d00a0
// __thiscall (ret 8): average the per-bone delta positions and low-pass them.
// ===========================================================================
struct Param0 {
    char  pad00[0x10];
    float f10, f14, f18;          // +0x10
    char  pad1c[0x24 - 0x1c];
    float f24;                    // +0x24
    char  pad28[0x30 - 0x28];
    float f30, f34, f38;          // +0x30
    char  pad3c[0x4c - 0x3c];
    int   f4c;                    // +0x4c
    int   f50;                    // +0x50
};

struct HostD {
    char  pad04[0x04 - 0x00];
    SA**  begin;                  // +0x04
    SA**  end;                    // +0x08
    char  pad0c[0x18 - 0x0c];
    float f18, f1c, f20;          // +0x18
    char  pad24[0x34 - 0x24];
    float f34;                    // +0x34
    void FUN_009d00a0(float* out, Param0* p);
};

void HostD::FUN_009d00a0(float* out, Param0* p)
{
    float ax = 0.0f, ay = 0.0f, az = 0.0f;
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    for (uint i = 0; i < n; i++) {
        SA* e = begin[i];
        float buf[3];
        float* r = e->FA90(buf, this, p->f18, p->f14, p->f10, p->f24);
        ax = ax + r[0];
        ay = ay + r[1];
        az = az + r[2];
    }
    if (n < 2) {
        int m = (p->f50 - p->f4c) / 0x38;
        if (m >= 2) {
            ax = g_h05 * ax;
            ay = g_h05 * ay;
            az = g_h05 * az;
        }
    } else {
        float inv = (float)(1.0 / (double)(int)n);
        float f = 1.0f - f34 * g_09;
        ax = ax * inv;
        ay = ay * inv;
        az = az * inv;
        ax = ax * f;
        ay = ay * f;
        az = az * f;
    }
    float k = g_08;
    float ik = 1.0f - k;
    ax = ax * ik;
    ay = ay * ik;
    az = az * ik;
    f18 = f18 * k + ax;
    f1c = f1c * k + ay;
    f20 = f20 * k + az;
    out[0] = f18;
    out[1] = f1c;
    out[2] = f20;
}

// ===========================================================================
// @ 0x009d0280  FUN_009d0280
// __fastcall(this): distance between the two locator bones and the clamped
// triangle decomposition (f28 = dist, f2c = cos*len, f30 = sin*len).
// ===========================================================================
struct HostR {
    char  pad[4];
    BN**  f4;                     // +0x04 -> array of 2 BN*
    char  pad08[0x28 - 0x08];
    float f28;                    // +0x28
    float f2c;                    // +0x2c
    float f30;                    // +0x30
    void  FUN_009d0280();
};

void HostR::FUN_009d0280()
{
    BN** v = f4;
    BN*  a = v[0];
    BN*  b = v[1];
    int  offA = *(int*)((char*)a->fC8 + 0x2e4) + a->f58 * 0x2bc;
    int  offB = *(int*)((char*)b->fC8 + 0x2e4) + b->f58 * 0x2bc;
    BP*  X = (BP*)*(int*)(*(int*)(offA + 8));
    BP*  Y = (BP*)*(int*)(*(int*)(offB + 8));
    float xlen = sqrtf(X->f350 * X->f350 + X->f354 * X->f354 + X->f358 * X->f358);
    float ylen = sqrtf(Y->f350 * Y->f350 + Y->f354 * Y->f354 + Y->f358 * Y->f358);
    float dx = Y->f350 - X->f350;
    float dy = Y->f354 - X->f354;
    float dz = Y->f358 - X->f358;
    float d = sqrtf((dx * dx + dz * dz) + dy * dy);
    f28 = d;
    if (d > g_eps) {
        float f = (xlen * xlen - ylen * ylen + d * d) / ((d * xlen) * g_2);
        if (f > g_m1) {
            if (f > 1.0f)
                f = 1.0f;
        } else {
            f = g_m1;
        }
        float t = 1.0f - f * f;
        float z = 0.0f;
        float* pv = &z;
        if (0.0f <= t)
            pv = &t;
        f2c = (f / d) * xlen;
        f30 = sqrtf(*pv) * xlen;
    } else {
        f28 = 0.0f;
        f2c = g_half;
        f30 = 0.0f;
    }
}

// ===========================================================================
// @ 0x009d0460  FUN_009d0460
// __thiscall (ret 8): approach/depart offset solver.
// ===========================================================================
struct HostE {
    SA*   f0;                     // +0x00
    BN**  f4;                     // +0x04 -> array of 2 BN*
    char  pad08[0x18 - 0x08];
    float f18, f1c, f20;          // +0x18
    char  pad24[0x28 - 0x24];
    float f28, f2c, f30;          // +0x28
    void FUN_009d0460(float* out, float dt);
};

void HostE::FUN_009d0460(float* out, float dt)
{
    BN** v = f4;
    BN*  a = v[0];
    BN*  b = v[1];
    SA*  a0 = f0;
    int  offA = *(int*)((char*)a->fC8 + 0x2e4) + a->f58 * 700;
    int  offB = *(int*)((char*)b->fC8 + 0x2e4) + b->f58 * 700;
    BP*  X = (BP*)*(int*)(*(int*)(offA + 8));
    BP*  Y = (BP*)*(int*)(*(int*)(offB + 8));
    float la = ((BP*)*(int*)offA)->f434
             - sqrtf(X->f350 * X->f350 + X->f354 * X->f354 + X->f358 * X->f358);
    float lb = ((BP*)*(int*)offB)->f434
             - sqrtf(Y->f350 * Y->f350 + Y->f354 * Y->f354 + Y->f358 * Y->f358);
    float ax = a->f0, ay = a->f4, az = a->f8;
    float dirx = b->f0 - ax;
    float diry = b->f4 - ay;
    float dirz = b->f8 - az;
    float d = sqrtf((diry * diry + dirz * dirz) + dirx * dirx);
    if (d != 0.0f) {
        float s = 1.0f / d;
        dirx *= s;
        diry *= s;
        dirz *= s;
    }
    float want = f28;
    if (d <= want)
        d = want - d;
    else
        d = d - want;
    float sinA, cosA;
    if (d <= g_eps) {
        d = 0.0f;
        sinA = g_1;
        cosA = 0.0f;
    } else {
        float c = ((la * la - lb * lb) + d * d) / ((d * la) * g_2);
        if (c > g_m1) {
            if (c > g_1)
                c = g_1;
        } else {
            c = g_m1;
        }
        float t = g_1 - c * c;
        float z = 0.0f;
        float* pv = &z;
        if (0.0f <= t)
            pv = &t;
        cosA = c;
        sinA = sqrtf(*pv);
    }
    float off = sinA * la - f30;
    float s2 = f2c * f28 + cosA * la;
    float px = ax + dirx * s2;
    float py = ay + diry * s2;
    float pz = az + dirz * s2;
    float tgtx, tgty, tgtz, sc;
    if (a0->f88 <= g_eps) {
        TgtVec* q = (TgtVec*)a0->q0_0;
        sc = ((Inner70*)a0->p04)->c;
        tgtx = q->f10c * sc;
        tgty = q->f110 * sc;
        tgtz = q->f114;
    } else {
        sc = g_1 / a0->f88;
        tgtx = a0->f7c * sc;
        tgty = a0->f80 * sc;
        tgtz = a0->f84;
    }
    tgtz = tgtz * sc;
    float bx = tgtx - px, by = tgty - py, bz = tgtz - pz;
    float dot = bx * dirx + bz * dirz + by * diry;
    float nx = bx - dirx * dot;
    float nz = bz - dirz * dot;
    float ny = by - diry * dot;
    float r2 = (nz * nz + ny * ny) + nx * nx;
    float qx, qy, qz;
    if (off * off <= r2) {
        r2 = sqrtf(r2);
        if (r2 != 0.0f) {
            float s = 1.0f / r2;
            nx *= s; nz *= s; ny *= s;
        }
        qx = nx * off + px;
        qy = ny * off + py;
        qz = nz * off + pz;
    } else {
        r2 = off * off - nx * nx - ny * ny;
        float z = 0.0f;
        float* pv = &r2;
        if (r2 <= 0.0f)
            pv = &z;
        qx = nx + px;
        qy = ny + py;
        qz = sqrtf(*pv) + pz;
    }
    float amp = FUN_009cdbe0(dt, 0.0f, g_25, 0.0f, g_1);
    float u = (dt - g_25) / (g_10 - g_25);
    if (u < 0.0f) u = 0.0f;
    else if (u > g_1) u = g_1;
    float t2 = _mm_cvtss_f32(FUN_009cdb20(u, g_m2));
    float w = FUN_009cdbe0(t2, 0.0f, g_1, g_1, g_half) * amp;
    float k = g_c08;
    float c2 = g_1 - k;
    f18 = f18 * k + ((qx - tgtx) * w) * c2;
    f1c = f1c * k + ((qy - tgty) * w) * c2;
    f20 = f20 * k + ((qz - tgtz) * w) * c2;
    out[0] = f18;
    out[1] = f1c;
    out[2] = f20;
}

// ===========================================================================
// @ 0x009d0a40  FUN_009d0a40
// __thiscall (ret 8): sum of F370 over all bones.
// ===========================================================================
struct HostF {
    char  pad[4];
    SA**  begin;                  // +0x04
    SA**  end;                    // +0x08
    float* FUN_009d0a40(float* out, Param0* p);
};

float* HostF::FUN_009d0a40(float* out, Param0* p)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    float a = p->f30, b = p->f34, c = p->f38;
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    for (uint i = 0; i < n; i++) {
        SA* e = begin[i];
        float buf[3];
        float* r = e->F370(buf, this, a, b, c);
        out[0] = out[0] + r[0];
        out[1] = out[1] + r[1];
        out[2] = out[2] + r[2];
    }
    return out;
}

// ===========================================================================
// @ 0x009d0b10  FUN_009d0b10
// __fastcall(this): per-bone atan2 angles (f9c / fa0 / fa4).
// ===========================================================================
struct HostG {
    SA**   f0;                    // +0x00 -> one SA*
    SA**   begin;                 // +0x04
    SA**   end;                   // +0x08
    void FUN_009d0b10();
};

void HostG::FUN_009d0b10()
{
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    if (n != 0) {
        SA** p = begin;
        SA*  q = *f0;
        do {
            SA* e = *p++;
            --n;
            e->f9c = atan2f(e->f80, e->f7c);
            e->fa0 = atan2f(q->f114, e->f80);
            e->fa4 = atan2f(e->f84, e->f7c);
        } while (n != 0);
    }
}

// ===========================================================================
// @ 0x009d0b80  FUN_009d0b80
// __fastcall(this): mean resultant length of the per-bone phase angles.
// ===========================================================================
struct HostH {
    char  pad[4];
    SA**  begin;                  // +0x04
    SA**  end;                    // +0x08
    char  pad0c[0x34 - 0x0c];
    float f34;                    // +0x34
    void FUN_009d0b80();
};

void HostH::FUN_009d0b80()
{
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    if (1 < n) {
        float ss = 0.0f;
        float sc = 0.0f;
        SA** p = begin;
        for (uint i = n; i != 0; --i) {
            SA* e = *p++;
            float a = e->f6c * g_2pi;
            ss = ss + sinf(a);
            sc = sc + cosf(a);
        }
        f34 = sqrtf(ss * ss + sc * sc) / (float)n;
    }
}

// ===========================================================================
// @ 0x009d0c10  FUN_009d0c10
// bool __fastcall(this): both locator bones resolve to the same entry.
// ===========================================================================
struct HostI {
    char  pad[4];
    SA**  begin;                  // +0x04
    SA**  end;                    // +0x08
    bool FUN_009d0c10();
};

bool HostI::FUN_009d0c10()
{
    if (((int)((char*)end - (char*)begin) >> 2) != 2)
        return false;
    SA** p = begin;
    for (int i = 0; i < 2; i++) {
        SA*  e = p[i];
        int** pp = (int**)e->fC8;
        int* q = *pp;
        int arr = *(int*)((char*)q + 0x384);
        int base = e->f58 * 0x468;
        int sub = *(int*)(base + arr + 0x1fc);
        base += arr;
        int v = *(int*)(base + 0x430);
        if (v != *(int*)(sub * 0x468 + arr + 0x1fc))
            return false;
    }
    return true;
}
