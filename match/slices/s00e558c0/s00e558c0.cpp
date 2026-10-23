// Slice s00e558c0 (frozen batch spcg1): object SPGonzago/SPCellGame.obj.
// Cell-fluid force sampling, cell-level property getters and progress-bar helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- globals / helpers
extern uint8_t* g_CellGame;      // cCellGame* at 0x16b3c04
extern uint8_t* g_16b3c0c;       // 0x16b3c0c
extern int      g_16b3c10;       // 0x16b3c10

struct Vec3f { float x, y, z; };
struct Vec3i { int x, y, z; };

extern "C" double __cdecl FUN_00e55770(int);
extern "C" void*  __cdecl SP_FluidParticlesSampleVelocity(void*, int, void*);
extern "C" double __cdecl FUN_00e513d0(int, int, float, int, int);
extern "C" void*  __cdecl FUN_00b72210(int);
extern "C" bool   __cdecl FUN_00e83380(void*, unsigned int, float*);
extern "C" void*  __cdecl FUN_00e4ce40(int*);
extern "C" void   __cdecl FUN_00e82130();
extern "C" void   __cdecl FUN_00743b50();
extern "C" double __cdecl FUN_00e503a0(int);
extern "C" int    __cdecl SP_sGetSourceLevel();
extern "C" unsigned __cdecl FUN_00e4ee30(int);
extern "C" double __cdecl FUN_01041cd0(int, float, float);
extern "C" void   __cdecl FUN_00e53660(int, int);
extern "C" float  __cdecl FUN_00e837c0(unsigned int, float);
extern "C" float  __cdecl sqrtf(float);

extern "C" float g_1485720;      // DAT_01485720
extern "C" float g_14853e0;      // DAT_014853e0
extern "C" float g_1471064;      // DAT_01471064
extern "C" float g_1470f1c;      // DAT_01470f1c
extern "C" float g_1483bd0[];    // kLevelSize
extern "C" float g_15a853c;      // DAT_015a853c
extern "C" float g_14854c8;      // DAT_014854c8 (2.2f)
extern "C" float g_16b3c28, g_16b3c2c, g_16b3c30;

struct IWindow;
struct cSPUILayout {
    IWindow* FindWindowByID(unsigned int id, bool a) const;   // 0x8105b0
};
struct IWindow {
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
    virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
    virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
    virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
    virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
    virtual int v20(); virtual int v21(); virtual int v22(); virtual int v23();
    virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
    virtual int v28(); virtual int v29(); virtual int v30(); virtual int v31(int, int);
};
struct SomeObj { void* Lookup(); };     // 0xe51900

// ================================================================ 00e558c0
// @ 0x00e558c0
bool FUN_00e558c0(float* p1, float* p2, float* p3, float* p4, float p5,
                  float p6, float p7, int p8, float p9, float* out) {
    if (p5 == 0.0f) {
        out[0] = g_16b3c28; out[1] = g_16b3c2c; out[2] = g_16b3c30;
        return false;
    }
    float dx = p4[0] - p2[0], dy = p4[1] - p2[1], dz = p4[2] - p2[2];
    float d2 = dy * dy + dx * dx + dz * dz;
    float dist = sqrtf(d2);
    float vx, vy, vz;
    if (1.0f <= dist) { vx = p1[0]; vy = p1[1]; vz = p1[2]; }
    else {
        float inv = 1.0f / sqrtf(d2 + 1e-08f);
        vx = (p1[0] - inv * dx) * dist + inv * dx;
        vy = (p1[1] - inv * dy) * dist + inv * dy;
        vz = (p1[2] - inv * dz) * dist + inv * dz;
    }
    bool ok = true;
    if (1.5258789e-05f < p7) {
        float s = (float)FUN_00e55770(p8);
        vx *= s; vy *= s; vz *= s;
        if (s < 1.5258789e-05f) ok = false;
    }
    float* vp = (float*)SP_FluidParticlesSampleVelocity(&dx, *(int*)(g_CellGame + 0x4108), p2);
    float ex = p3[0] - vp[0], ey = p3[1] - vp[1], ez = p3[2] - vp[2];
    if (sqrtf(ey * ey + (ez * ez + ex * ex)) <= dist || (char)p8 == 0) {
        float t = FUN_00e513d0(0x3f000000, 0x40400000, dist, 0, 0x3f800000);
        dist = t;
        vp = (float*)SP_FluidParticlesSampleVelocity(&dx, *(int*)(g_CellGame + 0x4108), p2);
        ex = ((vx * p5) * dist) * p6 + vp[0];
        ez = vp[2] + ((vz * p5) * dist) * p6;
        ey = vp[1] + ((vy * p5) * dist) * p6;
    } else { ex = -ex; ey = -ey; ez = -ez; }
    float c1 = p3[1], c2 = p3[2], m = 1.0f;
    if (!ok && (char)p8 != 0) m = 10.0f;
    out[0] = ((ex - p3[0]) * p9) * m;
    out[1] = ((ey - c1) * p9) * m;
    out[2] = ((ez - c2) * p9) * m;
    return ok;
}

// ================================================================ 00e55c40
// @ 0x00e55c40
void FUN_00e55c40(float* p1, float* p2, float* p3, float* p4, float p5,
                  float p6, float p7, int p8, float p9, float* out) {
    if (p5 == 0.0f) {
        out[0] = g_16b3c28; out[1] = g_16b3c2c; out[2] = g_16b3c30;
        return;
    }
    float dy = p4[1] - p2[1], dz = p4[2] - p2[2], dx = p4[0] - p2[0];
    float d2 = (dz * dz + dy * dy) + dx * dx;
    float dist = sqrtf(d2);
    float vx, vy, vz;
    if (1.0f <= dist) { vx = p1[0]; vy = p1[1]; vz = p1[2]; }
    else {
        float inv = 1.0f / sqrtf(d2 + 1e-08f);
        vx = (p1[0] - inv * dx) * dist + inv * dx;
        vy = (p1[1] - dy * inv) * dist + dy * inv;
        vz = (p1[2] - dz * inv) * dist + dz * inv;
    }
    if (1.5258789e-05f < p7) {
        float s = (float)FUN_00e55770(p8);
        vx *= s; vy *= s; vz *= s;
    }
    float* vp = (float*)SP_FluidParticlesSampleVelocity(&dx, *(int*)(g_CellGame + 0x4108), p2);
    float ex = p3[0] - vp[0], ey = p3[1] - vp[1], ez = p3[2] - vp[2];
    if (sqrtf(ey * ey + (ez * ez + ex * ex)) <= dist) {
        float t = FUN_00e513d0(0x3f000000, 0x40400000, dist, 0x3f000000, 0x3f800000);
        dist = t;
        vp = (float*)SP_FluidParticlesSampleVelocity(&dx, *(int*)(g_CellGame + 0x4108), p2);
        ex = vp[0] + ((vx * dist) * p5) * p6;
        ey = vp[1] + ((vy * dist) * p5) * p6;
        ez = vp[2] + ((vz * dist) * p5) * p6;
    } else { ex = -ex; ey = -ey; ez = -ez; }
    float c1 = p3[1], c2 = p3[2];
    out[0] = (ex - p3[0]) * p9;
    out[1] = (ey - c1) * p9;
    out[2] = (ez - c2) * p9;
}

// ================================================================ 00e55f60
// @ 0x00e55f60
void FUN_00e55f60(float* p1, float* p2, float* p3, float p4, int p5, float* out) {
    if (p4 == 0.0f) {
        out[0] = g_16b3c28; out[1] = g_16b3c2c; out[2] = g_16b3c30;
        return;
    }
    float dy = p3[1] - p1[1], dz = p3[2] - p1[2], dx = p3[0] - p1[0];
    float d2 = (dy * dy + dz * dz) + dx * dx;
    float inv = 1.0f / sqrtf(d2 + 1e-08f);
    float dlen = sqrtf(d2);
    float m = (p4 <= dlen) ? p4 : dlen;
    float ux = m * (inv * dx), uy = m * (dy * inv), uz = m * (inv * dz);
    float* vp = (float*)SP_FluidParticlesSampleVelocity(0, *(int*)(g_CellGame + 0x4108), p1);
    out[0] = (vp[0] + ux) - p2[0];
    out[1] = (vp[1] + uy) - p2[1];
    out[2] = (vp[2] + uz) - p2[2];
}

// ================================================================ 00e560d0
// @ 0x00e560d0
void FUN_00e560d0(int self, float* v) {
    float sc, a, b, c;
    if (*(int*)(self + 0x248) == 0 || *(int*)(self + 0x250) < 2) {
        sc = *(float*)(self + 0xbc); a = v[1]; b = v[2]; c = sc * v[0];
    } else {
        int i = 0;
        if (0 < *(int*)(self + 0x250)) {
            int base = *(int*)(g_CellGame + 0x4108);
            int* idx = (int*)(self + 0x254);
            do {
                sc = *(float*)(self + 0xbc); a = v[1]; b = v[2];
                float* p = (float*)(base + 0x4654 + *idx * 0xc);
                p[0] = *(float*)(base + 0x4654 + *idx * 0xc) + sc * v[0];
                p[1] = p[1] + a * sc;
                p[2] = p[2] + b * sc;
                ++i; ++idx;
            } while (i < *(int*)(self + 0x250));
        }
        sc = *(float*)(self + 0xbc); a = v[1]; b = v[2]; c = sc * v[0];
    }
    *(float*)(self + 0x98) = b * sc + *(float*)(self + 0x98);
    *(float*)(self + 0x94) = a * sc + *(float*)(self + 0x94);
    *(float*)(self + 0x90) = *(float*)(self + 0x90) + c;
}

// ================================================================ 00e56200
// @ 0x00e56200
double FUN_00e56200(int self) {
    int k = *(int*)(self + 0x1b0);
    if (0x11 < k && (k < 0x15 || k == 0x30)) {
        if (*(int*)(self + 0x248) != 0 && *(int*)(self + 0xfc) != 0) {
            int cell = (int)FUN_00b72210(*(int*)(self + 0x248));
            if (*(int*)(cell + 0x24) != 0) {
                float out;
                if (FUN_00e83380(*(void**)(cell + 0x24), 0x98c942b4, &out) == false) {
                    FUN_00743b50();
                    int o = (int)FUN_00e4ce40(&self);
                    float f = *(float*)(o + 0x108);
                    FUN_00e82130();
                    return (double)f;
                }
                *(float*)(self + 0x1c0) = out * 100.0f;
                return (double)(out * 100.0f);
            }
        }
        FUN_00743b50();
        int o = (int)FUN_00e4ce40(&self);
        float f = *(float*)(o + 0x108);
        FUN_00e82130();
        return (double)f;
    }
    return (double)*(float*)(self + 0x1c0);
}

// ================================================================ 00e56300
// @ 0x00e56300
double FUN_00e56300(int self) {
    int k = *(int*)(self + 0x1b0);
    if (k < 0x12 || (0x14 < k && k != 0x30))
        return (double)*(float*)(self + 0x1c0);
    if (*(int*)(self + 0x248) != 0 && *(int*)(self + 0xfc) != 0) {
        int cell = (int)FUN_00b72210(*(int*)(self + 0x248));
        int q = *(int*)(cell + 0x24);
        if (q != 0 && *(int*)(q + 0x54) != 0) {
            float out;
            if (FUN_00e83380((void*)q, 0x98c942b4, &out) == false)
                return (double)FUN_00e503a0(2);
            *(float*)(self + 0x1c0) = out * 20.0f;
            return (double)(out * 20.0f);
        }
    }
    FUN_00743b50();
    int o = (int)FUN_00e4ce40(&self);
    float f = *(float*)(o + 0x104);
    FUN_00e82130();
    return (double)f;
}

// ================================================================ 00e563e0
// @ 0x00e563e0
float FUN_00e563e0(void* obj) {
    float f = g_1485720;
    int idx = *(int*)((char*)obj + 0x358);
    if (idx != -1) {
        int lvl = SP_sGetSourceLevel();
        f = g_1483bd0[idx] / g_1483bd0[lvl];
    }
    return FUN_00e837c0(0x7ac2e49f, f);
}

// ================================================================ 00e56450
// @ 0x00e56450
double FUN_00e56450(int self) {
    int idx = *(int*)(self + 0x358);
    if (idx != -1) {
        int lvl = SP_sGetSourceLevel();
        float r = g_1483bd0[idx] / g_1483bd0[lvl];
        if (r <= 0.5f) return 4.0;
        if (r <= 1.0f) return 4.0 - ((double)r - 0.5) * 4.0;
        if (r <= 2.0f) return 2.0;
        if (r <= 4.0f) return 2.0 - ((double)r - 2.0) * 0.5;
    }
    return 1.0;
}

// ================================================================ 00e56510
// @ 0x00e56510
float FUN_00e56510(SomeObj* obj) {
    int k = *(int*)((char*)obj + 0x18c);
    if (k == 0x30 || k == 0x12 || k == 0x14 || k == 0x13)
        return 1.0f;
    void* h = obj->Lookup();
    if (h) {
        float out;
        if (FUN_00e83380(h, 0x98c942b5, &out))
            return out;
    }
    return 1.0f;
}

// ================================================================ 00e56560
// @ 0x00e56560
void FUN_00e56560(float* out, int* self) {
    if (self[0x92] != 0 && self[0x3f] != 0) {
        int cell = (int)FUN_00b72210(self[0x92]);
        if (*(int*)(cell + 0x24) != 0) {
            float q = 0.0f;
            FUN_00e83380(*(void**)(cell + 0x24), 0x98c942b6, &q);
            float s = sqrtf(*(float*)((char*)self + 0xbc));
            float a = (g_15a853c * (q * *(float*)((char*)self + 0x1a0))) * s;
            float b = (g_15a853c * (*(float*)((char*)self + 0x1a4) * q)) * s;
            float c = (g_15a853c * (*(float*)((char*)self + 0x1a8) * q)) * s;
            if (*self == *(int*)(g_CellGame + 0x411c)) {
                unsigned u = FUN_00e4ee30(*(int*)(*(int*)(g_CellGame + 0x5190) + 0x1c));
                if (u & 1) { a *= g_14854c8; b *= g_14854c8; c *= g_14854c8; }
            }
            out[0] = a; out[1] = b; out[2] = c;
            return;
        }
    }
    out[0] = g_16b3c28; out[1] = g_16b3c2c; out[2] = g_16b3c30;
}

// ================================================================ 00e56690
// @ 0x00e56690
void FUN_00e56690() {
    *(uint8_t*)(g_16b3c0c + 0x938) = 0;
    FUN_00e53660(2, 0);
    uint8_t* p = *(uint8_t**)(g_CellGame + 0x5190) + 0x80;
    *(int*)(p + 0) = 1;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0;
    *(float*)(p + 0xc) = 0.0f;
}

// ================================================================ 00e566e0
// @ 0x00e566e0
void FUN_00e566e0() {
    *(uint8_t*)(g_16b3c0c + 0x938) = 0;
    FUN_00e53660(2, 0);
}

// ================================================================ 00e56700
// @ 0x00e56700
double FUN_00e56700(int data, int count, float t) {
    if (0 < count - 1) {
        int i = 0;
        do {
            float hi = *(float*)(data + 8 + i * 8);
            if (t < hi) {
                float lo = *(float*)(data + 4 + i * 8);
                float v2 = *(float*)(data + 0xc + i * 8);
                float u = FUN_01041cd0(*(int*)(data + i * 8), hi, t);
                float cl = 0.0f;
                if (0.0f <= u) cl = u;
                if (1.0f <= cl) cl = 1.0f;
                return ((double)v2 - (double)lo) * (double)cl + (double)lo;
            }
            ++i;
        } while (i < count - 1);
    }
    return (double)*(float*)(data + -4 + count * 8);
}

// ================================================================ 00e567c0
// @ 0x00e567c0
void FUN_00e567c0() {
    cSPUILayout* layout = *(cSPUILayout**)(g_16b3c0c + 0x90);
    IWindow* w = layout->FindWindowByID(0x5af4ae5, 1);
    if (w) w->v31(1, 0);
    uint8_t* p = *(uint8_t**)(g_CellGame + 0x5190) + 0x80;
    g_16b3c10 = 0;
    *(int*)(p + 0) = 1;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0;
    *(float*)(p + 0xc) = 0.0f;
}
