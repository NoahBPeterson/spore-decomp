// Slice s00fbb1a0 -- SP planet-surface paint ramp / height histogram builder.
// The per-instance colouriser object holds a bank of colour stops, two eastl
// vectors (a time axis and a vertex/colour axis), a 10x4 float ramp texture and
// a 6x4x4 float height grid.  This slice builds the percentile ramp from a
// height histogram (using a 0x40000-byte scratch histogram), samples that ramp
// to export the surface ramp texture, and fills the grid from the terrain map.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    i8;
typedef short          i16;
typedef int            i32;

#pragma warning(disable: 4035)

// ---- EA math helpers (hand-written SSE in the original) ---------------------
// Round-to-nearest-then-decrement-to-floor of a float, as the original emits
// with cvtss2si / cvtsi2ss / cmovb (matching.md alt of the platform FloorToInt).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// ---- colour value class -----------------------------------------------------
struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {}
    ColorRGB(const ColorRGB& o) : r(o.r), g(o.g), b(o.b) {}
};

// =============================================================== callees
// Allocation (EA's operator new / delete).
void* __cdecl SpNew(u32 size, int align, int a3, const char* name,
                    int a5, int a6, int a7, int a8);              // 0xf473d0
void  __cdecl SpDelete(void* p);                                 // 0xf47380

// Singleton accessor returning a manager whose vtable slot 0x34 is called with
// the device object as this.
void* __cdecl GetGonzago();                                      // 0x67dd60
void* __cdecl SP_App();                                          // 0x67dd10

// Texture device: Lock(volume, slice, &out) and Unlock(&handle).
// The original passes the device's vtable word as `this` (mov ecx,[dev] before
// the call), so the lock/unlock entry points take the vtable object.
struct TexVtbl {
    int  Lock(int a, int b, void** out);                         // 0x11ef750
    void Unlock(void* h);                                        // 0x11ef880
};

// In-slice helpers.
float* ScaleHSL(float* out, ColorRGB c, float sS, float sL);     // 0xfb8fc0
void   BuildPaintTexture(void* p1, void* p2, void* p3, void* p4,
                         void* p5, void* p6, void* p7);          // 0xfb8790

// =============================================================== painter object
// Layout read off the disassembly (byte offsets); names for fields shared with
// the neighbouring slice s00fb84e0 (stop0/stop1, f2c0, f2d8, mp328) kept.
struct PlanetColor {
    u8    pad00[8];
    float f08;            // +0x08
    float f0c;            // +0x0c
    float f10;            // +0x10 histogram low percentile
    float f14;            // +0x14 histogram high percentile
    u8    pad18[0x264 - 0x18];
    u8    b264;           // +0x264 "ramp valid" flag
    u8    pad265[0x268 - 0x265];
    ColorRGB stop0;       // +0x268
    ColorRGB stop1;       // +0x274
    u8    pad280[0x298 - 0x280];
    float* mpTimes;       // +0x298 eastl::vector<float> begin
    u8    pad29c[0x2ac - 0x29c];
    void*  mpVerts;       // +0x2ac eastl::vector<ColorRGB> begin
    void*  mpVertsEnd;    // +0x2b0 eastl::vector<ColorRGB> end
    void*  mpVertsCap;    // +0x2b4 eastl::vector<ColorRGB> capacity
    u8    pad2b8[0x2c0 - 0x2b8];
    float f2c0;           // +0x2c0 stop saturation scale
    u8    pad2c4[0x2d8 - 0x2c4];
    float f2d8;           // +0x2d8 stop luminance scale
    u8    pad2dc[0x328 - 0x2dc];
    void*  mp328;         // +0x328 texture device owning the ramp texture
    u8    pad32c[0x330 - 0x32c];
    void*  mp330;         // +0x330
    void*  mp334;         // +0x334
    void*  mp338;         // +0x338
    void*  mp33c;         // +0x33c
    void*  mp340;         // +0x340
    u8    pad344[0x50c - 0x344];
    float  mRamp[10][4];  // +0x50c 10x4 rgba ramp texture
    float  mPct[101];     // +0x628 percentile height ramp (mPct[80] = +0x768 threshold)
    u8     b7bc;          // +0x7bc grid built flag
    u8    pad7bd[0x940 - 0x7bd];
    float  mPrev[96];     // +0x940 previous height grid (compare source)
    float  mGrid[96];     // +0xac0 6x4x4 height grid

    void BuildHeightHistogram();            // 0x00fbb1a0
    bool ExportRampTexture();               // 0x00fbb8b0
    bool ExportRampTextureEx();             // 0x00fbbc00
    void InitHistogramBuf(void* buf);       // 0xfbafa0
};

// Sample the piecewise-linear ramp built from `n` colour stops (`*ppVerts`,
// 12-byte elements) at coordinate `t`, using the time axis `*ppTimes`.
// @ 0x00fbb7a0
float* SampleRampValue(float* out, float t, int n, void** ppVerts, float** ppTimes)
{
    if (n < 1) {
        out[0] = *(float*)0x16d6710;
        out[1] = *(float*)0x16d6714;
        out[2] = *(float*)0x16d6718;
        return out;
    }
    int i = 0;
    float* times;
    if (n > 0) {
        times = (float*)*ppTimes;
        do {
            if (t < times[i]) {
                if (i != 0) {
                    float* v = (float*)*ppVerts;
                    float r0 = v[i * 3 - 3];
                    float g0 = v[i * 3 - 2];
                    float b0 = v[i * 3 - 1];
                    float b1 = v[i * 3 + 2];
                    float* vi = v + i * 3;
                    float f = (t - times[i - 1]) / (times[i] - times[i - 1]);
                    out[0] = r0 + (vi[0] - r0) * f;
                    out[1] = g0 + (vi[1] - g0) * f;
                    out[2] = b0 + f * (b1 - b0);
                    return out;
                }
                times = (float*)*ppVerts;
                break;
            }
            i++;
        } while (i < n);
        if (i >= n) times = (float*)*ppVerts + n * 3 - 3;
    } else {
        out[0] = *(float*)0x16d6710;
        out[1] = *(float*)0x16d6714;
        out[2] = *(float*)0x16d6718;
        return out;
    }
    out[0] = times[0];
    out[1] = times[1];
    out[2] = times[2];
    return out;
}

// Build the percentile height ramp (this->mPct) from the terrain height
// histogram in a 0x40000-byte scratch buffer.
// @ 0x00fbb1a0
void PlanetColor::BuildHeightHistogram()
{
    u32* buf = (u32*)SpNew(0x40000, 0x10, 0, "Terrain/Histogram", 0, 0, 0, 0);
    InitHistogramBuf(buf);

    this->f10 = 0.0f;
    this->f14 = 1.0f;

    float* pfVar8 = &this->mPct[1];     // +0x62c
    float* pfVar7 = &this->mPct[0];     // +0x628
    int local14 = 0;
    int* pi = (int*)((char*)buf + 8);
    int i = 2;
    u32 uVar12 = 0;
    do {
        // four taps pi[-2], pi[-1], pi[0], pi[1] (the original unrolls this)
        int idx;
        float fv, h, fi, lo;
        idx = i - 2;
        local14 += pi[-2];
        fv = (float)(u32)local14;
        if (local14 < 0) fv = fv + 4294967296.0f;
        fv = fv * 6.357829e-07f;
        if (pi[-2] == 0 && fv == 0.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            this->f10 = h * 1.5259022e-05f;
        } else if (pi[-2] == 0 && fv == 1.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            lo = this->f14;
            if (h * 1.5259022e-05f < lo) lo = h * 1.5259022e-05f;
            this->f14 = lo;
        }
        if (100 < uVar12) break;
        fi = (float)(int)uVar12;
        if ((int)uVar12 < 0) fi = fi + 4294967296.0f;
        if (fi < fv * 100.0f) {
            uVar12 = uVar12 + 1;
            *pfVar8 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            pfVar8 = pfVar8 + 1;
        } else {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            *pfVar7 = h * 1.5259022e-05f;
        }

        idx = i - 1;
        local14 += pi[-1];
        fv = (float)(u32)local14;
        if (local14 < 0) fv = fv + 4294967296.0f;
        fv = fv * 6.357829e-07f;
        if (pi[-1] == 0 && fv == 0.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            this->f10 = h * 1.5259022e-05f;
        } else if (pi[-1] == 0 && fv == 1.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            lo = this->f14;
            if (h * 1.5259022e-05f < lo) lo = h * 1.5259022e-05f;
            this->f14 = lo;
        }
        if (100 < uVar12) break;
        fi = (float)(int)uVar12;
        if ((int)uVar12 < 0) fi = fi + 4294967296.0f;
        if (fi < fv * 100.0f) {
            uVar12 = uVar12 + 1;
            *pfVar8 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            pfVar8 = pfVar8 + 1;
        } else {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            *pfVar7 = h * 1.5259022e-05f;
        }

        idx = i;
        local14 += pi[0];
        fv = (float)(u32)local14;
        if (local14 < 0) fv = fv + 4294967296.0f;
        fv = fv * 6.357829e-07f;
        if (pi[0] == 0 && fv == 0.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            this->f10 = h * 1.5259022e-05f;
        } else if (pi[0] == 0 && fv == 1.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            lo = this->f14;
            if (h * 1.5259022e-05f < lo) lo = h * 1.5259022e-05f;
            this->f14 = lo;
        }
        if (100 < uVar12) break;
        fi = (float)(int)uVar12;
        if ((int)uVar12 < 0) fi = fi + 4294967296.0f;
        if (fi < fv * 100.0f) {
            uVar12 = uVar12 + 1;
            *pfVar8 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            pfVar8 = pfVar8 + 1;
        } else {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            *pfVar7 = h * 1.5259022e-05f;
        }

        idx = i + 1;
        local14 += pi[1];
        fv = (float)(u32)local14;
        if (local14 < 0) fv = fv + 4294967296.0f;
        fv = fv * 6.357829e-07f;
        if (pi[1] == 0 && fv == 0.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            this->f10 = h * 1.5259022e-05f;
        } else if (pi[1] == 0 && fv == 1.0f) {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            lo = this->f14;
            if (h * 1.5259022e-05f < lo) lo = h * 1.5259022e-05f;
            this->f14 = lo;
        }
        if (100 < uVar12) break;
        fi = (float)(int)uVar12;
        if ((int)uVar12 < 0) fi = fi + 4294967296.0f;
        if (fi < fv * 100.0f) {
            uVar12 = uVar12 + 1;
            *pfVar8 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            pfVar8 = pfVar8 + 1;
        } else {
            h = (float)(u32)idx;
            if (idx < 0) h = h + 4294967296.0f;
            *pfVar7 = h * 1.5259022e-05f;
        }

        i += 4;
        pi += 4;
    } while (i - 2 < 0x10000);
    // ---- build the 6x4x4 height grid from the terrain map ----
    {
    float thr = this->mPct[80];
    int thrI = (int)(thr * 65535.0f);
    void* r = ((void*(__thiscall*)(void*))*(void**)(*(char**)this + 0xc))(this);
    u16* local_10 = *(u16**)((char*)(*(void**)((char*)r + 8)) + 0x10);
    unsigned short thrU = (unsigned short)thrI;

    float* pfDest = &this->mGrid[0];
    int local_8 = 6;
    do {
        int iStack_c = 4;
        do {
            int local_14b = 4;
            u16* puVar13 = local_10;
            do {
                local_10 = puVar13;
                *pfDest = 0.0f;
                if ((float)((int)(thr * 65535.0f) & 0xffff) < pfDest[-0x60]) {
                    int iVar5 = 0x80;
                    u16* puRow = local_10;
                    float acc = 0.0f;
                    do {
                        int cnt = 0x10;
                        u16* puCol = puRow;
                        do {
                            acc = (float)(thrU < puCol[0]) + acc;
                            *pfDest = acc;
                            acc = (float)(thrU < puCol[1]) + acc;
                            *pfDest = acc;
                            acc = (float)(thrU < puCol[2]) + acc;
                            *pfDest = acc;
                            acc = (float)(thrU < puCol[3]) + acc;
                            *pfDest = acc;
                            acc = (float)(thrU < puCol[4]) + acc;
                            *pfDest = acc;
                            acc = (float)(thrU < puCol[5]) + acc;
                            *pfDest = acc;
                            acc = (float)(thrU < puCol[6]) + acc;
                            *pfDest = acc;
                            u16* puTail = puCol + 7;
                            puCol = puCol + 8;
                            acc = (float)(thrU < *puTail) + acc;
                            *pfDest = acc;
                            cnt = cnt - 1;
                        } while (cnt != 0);
                        puRow = puRow + 0x200;
                        iVar5 = iVar5 - 1;
                    } while (iVar5 != 0);
                    *pfDest = acc * 6.1035156e-05f;
                }
                pfDest = pfDest + 1;
                local_14b = local_14b - 1;
                puVar13 = local_10 + 0x80;
            } while (local_14b != 0);
            local_10 = local_10 + 0xfe80;
            iStack_c = iStack_c - 1;
        } while (iStack_c != 0);
        local_8 = local_8 - 1;
    } while (local_8 != 0);
    this->b7bc = 1;
    SpDelete(buf);
    }
}

// Fill the 10x4 ramp from the two stop colours and the sampled ramp, then lock
// the ramp texture, sample it into the ramp rows and flush the grid.
// @ 0x00fbb8b0
bool PlanetColor::ExportRampTexture()
{
    this->mRamp[0][3] = 1.0f;
    this->mRamp[0][0] = this->stop0.r;
    this->mRamp[4][3] = 1.0f;
    this->mRamp[0][1] = this->stop0.g;
    this->mRamp[0][2] = this->stop0.b;
    this->mRamp[4][0] = this->stop1.r;
    this->mRamp[1][0] = this->mRamp[0][0];
    this->mRamp[4][1] = this->stop1.g;
    this->mRamp[1][1] = this->mRamp[0][1];
    this->mRamp[4][2] = this->stop1.b;
    this->mRamp[1][2] = this->mRamp[0][2];
    this->mRamp[2][0] = this->mRamp[0][0];
    this->mRamp[1][3] = this->mRamp[0][3];
    this->mRamp[2][1] = this->mRamp[0][1];
    this->mRamp[2][2] = this->mRamp[0][2];
    this->mRamp[3][0] = this->mRamp[0][0];
    this->mRamp[2][3] = this->mRamp[0][3];
    this->mRamp[3][1] = this->mRamp[0][1];
    this->mRamp[3][2] = this->mRamp[0][2];
    this->mRamp[5][0] = this->mRamp[4][0];
    this->mRamp[3][3] = this->mRamp[0][3];
    this->mRamp[5][1] = this->mRamp[4][1];
    this->mRamp[5][2] = this->mRamp[4][2];
    this->mRamp[6][0] = this->mRamp[4][0];
    this->mRamp[5][3] = this->mRamp[4][3];
    this->mRamp[6][1] = this->mRamp[4][1];
    this->mRamp[6][2] = this->mRamp[4][2];
    this->mRamp[7][0] = this->mRamp[4][0];
    this->mRamp[6][3] = this->mRamp[4][3];
    this->mRamp[7][1] = this->mRamp[4][1];
    this->mRamp[7][2] = this->mRamp[4][2];
    this->mRamp[7][3] = this->mRamp[4][3];

    float local[3];
    ScaleHSL(local, ColorRGB(this->stop1.r, this->stop1.g, this->stop1.b),
             this->f2c0, this->f2d8);
    void* dev = this->mp328;
    this->mRamp[9][0] = local[0];
    this->mRamp[9][1] = local[1];
    this->mRamp[9][2] = local[2];
    this->mRamp[9][3] = 1.0f;

    if ((*(u8*)((u8*)dev + 4) & 1) == 0) {
        void* g = GetGonzago();
        ((void(__thiscall*)(void*, void*))*(void**)(*(char**)g + 0x34))(g, dev);
    }

    void* handle = 0;
    if (((TexVtbl*)*(void**)dev)->Lock(2, 0, &handle) == 0)
        return false;

    u32* tex = (u32*)((char*)handle + 0x3fc02);
    const float f255 = 255.0f;
    int y = 0;
    do {
        float tmp[3];
        SampleRampValue(tmp, (float)(u32)y * 0.003921568859368563f,
                        (int)((char*)this->mpVertsEnd - (char*)this->mpVerts) / 12,
                        &this->mpVerts, &this->mpTimes);
        float sb = tmp[2] * f255;
        float sg = tmp[1] * f255;
        float sr = tmp[0] * f255;
        int x = 0x100;
        do {
            *((u8*)tex - 2) = (u8)(int)sb;
            *((u8*)tex - 1) = (u8)(int)sg;
            *((u8*)tex)     = (u8)(int)sr;
            *((u8*)tex + 1) = 0xff;
            tex = (u32*)((char*)tex + 4);
            x--;
        } while (x);
        y++;
        tex = (u32*)((char*)tex - 0x400 - 0x100 * 4);
    } while (y < 0x100);

    ((TexVtbl*)*(void**)dev)->Unlock(&handle);
    return true;
}

// Second ramp export: reads the terrain-map colour ramp directly and pushes it
// through BuildPaintTexture. Returns true when b264 is set (delegates to
// ExportRampTexture) or when the lock succeeds.
// @ 0x00fbbc00
bool PlanetColor::ExportRampTextureEx()
{
    if (this->b264 != 0)
        return this->ExportRampTexture();

    void* dev = this->mp328;
    if ((*(u8*)((u8*)dev + 4) & 1) == 0) {
        void* g = GetGonzago();
        ((void(__thiscall*)(void*, void*))*(void**)(*(char**)g + 0x34))(g, dev);
    }

    void* p338 = this->mp338;
    void* p340 = this->mp340;
    void* p330 = this->mp330;
    void* p334 = this->mp334;
    void* p33c = this->mp33c;

    void* handle = 0;
    if (((TexVtbl*)*(void**)dev)->Lock(3, 0, &handle) == 0)
        return false;

    u32 v33c = *(u32*)((char*)p33c + 0x28);
    u32 v330 = *(u32*)((char*)p330 + 0x28);
    float fa = this->f08 * 63.0f + 0.5f;
    u32 v334 = *(u32*)((char*)p334 + 0x28);
    u32 v338 = *(u32*)((char*)p338 + 0x28);
    void* p340v = (void*)*(u32*)((char*)p340 + 0x28);

    int idxA = FloorToInt(fa);
    void* app = SP_App();
    void* kind = ((void*(__thiscall*)(void*))*(void**)(*(char**)app + 0x38))(app);
    int idxB = idxA;
    if (kind == (void*)0x1654c10) {
        float fb = this->f0c * 63.0f + 0.5f;
        idxB = FloorToInt(fb);
    }

    const u8* tex = (const u8*)p340v;
    const float inv255 = 0.003921568859368563f;

    for (int s = 0; s < 10; s++) {
        int idx = (s == 0 || s == 4 || s == 9) ? idxB : idxA;
        const u8* p = tex + s * 0x100 + idx * 4;
        this->mRamp[s][0] = (float)p[2] * inv255;
        this->mRamp[s][1] = (float)p[1] * inv255;
        this->mRamp[s][2] = (float)p[0] * inv255;
        this->mRamp[s][3] = (float)p[3] * inv255;
    }

    BuildPaintTexture(handle, (void*)v33c, (void*)v330, (void*)v334,
                      (void*)v338, (void*)(size_t)idxA, (void*)(size_t)idxB);
    ((TexVtbl*)*(void**)dev)->Unlock(&handle);
    return true;
}
