// Slice s00fb9420 -- SP::TextureManager / render-resource helpers
// Region flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (SSE for float, x87 st(0) for double returns)
#include <math.h>
typedef unsigned int uint;

// ---------------------------------------------------------------- masked externs
int*   __cdecl FUN_0067dd60(void);                  // 0x0067dd60 (singleton accessor, returns the object)
void   __cdecl GetImageResource(int res);           // 0x00576650 GetImageResource
double __cdecl FUN_00fb9870(void* p, float v);      // 0x00fb9870
void   __cdecl FUN_00f47380(void* p);               // 0x00f47380 ??3@YAXPAX@Z  (operator delete)
double __fastcall FUN_00fb88d0(int param_1);        // 0x00fb88d0 (__thiscall, returns a double in st(0))

// The three coordinate args are passed as one 12-byte by-value aggregate --
// the caller reserves them with a single `sub esp,0xc` and three dword stores,
// which is what MSVC emits for a by-value struct, not for three separate ints.
struct Arg12 { int a, b, c; };

// Virtual manager: the call at vtable+0x1c (slot 7) takes (Arg12, int) with `this` in ecx.
struct ITextureMgr {
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7(Arg12 s, int z);
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual void v13(void* o);
};

// Resource owner: GetImageResource is a __thiscall member (this in ecx).
struct IResOwner { bool GetImageResource(int res); };

// Terrain sphere / scale hooks (both reached with `this` in ecx).
struct CTerrainSphere { void Relevel(int a, int b); };
struct CScaleObj { void SetScale(float v); };
namespace SP { void* App(void); }

// Glyph/atlas lock interface reached through the first dword of the object at +0x328.
struct IFont {
    int  Lock(int a, int b, int* buf);      // __thiscall (this in ecx)
    void Unlock(int* buf);                  // __thiscall (this in ecx)
};

// @ 0x00fba2f0 -- SP::TextureManager
// Ask the manager to create the resource for (a,b,c), then register it: return true on success.
namespace SP {
bool TextureManager(int param_1, int param_2, int param_3, int param_4);
}
bool SP::TextureManager(int param_1, int param_2, int param_3, int param_4) {
    ITextureMgr* o = (ITextureMgr*)FUN_0067dd60();
    // The three dwords at &param_2 ARE the 12-byte aggregate for the virtual call.
    int r = o->v7(*(Arg12*)&param_2, 0);
    if (r != 0) {
        ((IResOwner*)param_1)->GetImageResource(r);
        return true;
    }
    return false;
}

// @ 0x00fb9aa0 -- FUN_00fb9aa0
// (1.0f - f2c) passed to the helper at +0x128, scaled by the float at (*(this+4))+0x38.
double __fastcall FUN_00fb9aa0(int param_1) {
    return FUN_00fb9870((void*)(param_1 + 0x128), 1.0f - *(float*)(param_1 + 0x2c)) *
           *(float*)(*(int*)(param_1 + 4) + 0x38);
}

// @ 0x00fb9870 -- FUN_00fb9870
// Piecewise-linear lookup over an array of (x, value) float pairs: clamp to the
// first/last entry, else find the bracketing pair and lerp.
double __cdecl FUN_00fb9870(int* param_1, float param_2) {
    int n = (param_1[1] - (int)*param_1) >> 3;
    float* p = (float*)*param_1;
    float local_8 = 0.0f;
    float local_c = 0.0f;
    float local_4 = 0.0f;
    if (n != 0) {
        if (param_2 <= p[0]) return p[1];
        if (p[n * 2 - 2] <= param_2) return p[n * 2 - 1];
        int i = 0;
        float* q = p;
        if (0 < n - 1) {
            while (param_2 < q[0] || q[2] <= param_2) {
                i++;
                q += 2;
                if (n - 1 <= i) goto done;
            }
            local_8 = p[i * 2 + 1];
            local_c = p[i * 2 + 3];
            local_4 = (param_2 - p[i * 2]) / (p[i * 2 + 2] - p[i * 2]);
        }
    }
done:
    return (local_c - local_8) * local_4 + local_8;
}

// @ 0x00fb9f40 -- FUN_00fb9f40
// Releases the seven 0x14-byte-strided allocations (each preceded by a refcount dword).
void __fastcall FUN_00fb9f40(int param_1) {
    char* p;
    p = *(char**)(param_1 + 0x8c);
    if (p != 0 && *(int*)(p - 4) != 0) FUN_00f47380(p);
    p = *(char**)(param_1 + 0x78);
    if (p != 0 && *(int*)(p - 4) != 0) FUN_00f47380(p);
    p = *(char**)(param_1 + 0x64);
    if (p != 0 && *(int*)(p - 4) != 0) FUN_00f47380(p);
    char* off = (char*)(param_1 + 0x64);
    for (int i = 3; i >= 0; i--) {
        char* q = *(char**)(off - 0x14);
        off -= 0x14;
        if (q != 0 && *(int*)(q - 4) != 0) FUN_00f47380(q);
    }
}

// @ 0x00fb9e70 -- FUN_00fb9e70
// Samples one glyph-atlas texel: floor() the glyph metric, scale the arg to 0..255,
// read the alpha byte of the atlas entry, lerp then normalize to 0..1.
double __fastcall FUN_00fb9e70(int param_1, float param_2) {
    int* o = *(int**)(param_1 + 0x328);
    if ((*(unsigned char*)((char*)o + 4) & 1) == 0) {
        ITextureMgr* mgr = (ITextureMgr*)FUN_0067dd60();
        mgr->v13(o);
    }
    IFont* font = (IFont*)*(int*)o;
    float f = (float)FUN_00fb88d0(param_1);
    int i = (int)f;
    if (f < (float)i) i--;
    int j = (int)(param_2 * 255.0f);
    int buf[7];
    float result = 0.0f;
    if (font->Lock(1, 0, buf) != 0) {
        result = (float)*(unsigned char*)((char*)buf[0] + (((j << 8) + i) << 2) + 3) *
                 (f - (float)i) * 0.003921569f;
        font->Unlock(buf);
    }
    return result;
}

// @ 0x00fb9420 -- FUN_00fb9420
// Caches (time, value) and the normalized screen-space anchor, then re-scales the
// terrain sphere when the time delta is significant.
void __fastcall FUN_00fb9420(int param_1, int junk, float param_2, float param_3, float* param_4) {
    if (*(float*)(param_1 + 0x604) != param_2 || *(float*)(param_1 + 0x600) == *(float*)0x13eb1bc) {
        *(float*)(param_1 + 0x600) = param_3;
        *(float*)(param_1 + 0x604) = param_2;
        float fx = (param_4[0] + *(float*)0x15b15d4) * *(float*)0x1471064;
        float fy = (param_4[1] + *(float*)0x15b15d8) * *(float*)0x1471064;
        *(float*)(param_1 + 0x608) = fx;
        *(float*)(param_1 + 0x60c) = fy;
        if (*(float*)0x14911bc <= fabsf(*(float*)(param_1 + 0x18) - param_2)) {
            *(float*)(param_1 + 0x18) = param_2;
            ((CScaleObj*)*(int*)(param_1 + 4))->SetScale(param_2 * *(float*)0x1470f1c - *(float*)0x1485720);
            int* obj = *(int**)param_1;
            (*(void(__thiscall**)(int*, int))(*(int*)obj + 0x48))(obj, 10);
            ((CTerrainSphere*)obj)->Relevel(0, 1);
        }
    }
}

// @ 0x00fb9500 -- FUN_00fb9500// Picks the colour keyed by the current animation time out of a 4-byte-per-entry
// table, or falls back to the plain tint when the editor/preview override applies.
void __fastcall FUN_00fb9500(int param_1, int junk, char param_2) {
    if (*(char*)(param_1 + 0x264) == 0) {
        int* app = (int*)SP::App();
        int r = (*(int(__thiscall**)(int*))(*(int*)app + 0x38))(app);
        if (r != 0x1654c10 || param_2 != 0) {
            int n = *(int*)(*(int*)(param_1 + 500) + 0x1c) - 1;
            float f = (float)(unsigned)n * *(float*)(param_1 + 0x30);
            int i = (int)f;
            if (f < (float)i) i--;
            unsigned char* p = (unsigned char*)(*(int*)(*(int*)(param_1 + 500) + 0x28) + i * 4);
            *(float*)(param_1 + 0x434) = (float)p[0] * *(float*)0x13eecd4;
            *(float*)(param_1 + 0x430) = (float)p[1] * *(float*)0x13eecd4;
            *(float*)(param_1 + 0x42c) = (float)p[2] * *(float*)0x13eecd4;
            *(float*)(param_1 + 0x438) = (float)p[3] * *(float*)0x13eecd4;
            return;
        }
    }
    *(float*)(param_1 + 0x42c) = *(float*)(param_1 + 0x280);
    *(float*)(param_1 + 0x430) = *(float*)(param_1 + 0x284);
    *(float*)(param_1 + 0x438) = 1.0f;
    *(float*)(param_1 + 0x434) = *(float*)(param_1 + 0x288);
}

// 12-byte animation key: time + two ramp values.
struct Key3 { float t, a, b; };

// @ 0x00fb9610 -- FUN_00fb9610
// Samples the key table at (param_1 + 0x158 + param_4 * 0x14) for time param_3,
// writing the interpolated pair through param_2 and returning it.
float* __fastcall FUN_00fb9610(int param_1, int junk, float* param_2, float param_3, int param_4) {
    int* vec = (int*)(param_1 + 0x158 + param_4 * 0x14);
    unsigned n = (vec[1] - vec[0]) / 12;
    *param_2 = 1.0f;
    param_2[1] = 1.0f;
    if (n != 0) {
        Key3* base = (Key3*)vec[0];
        Key3* p = base;
        float f = 0.0f;
        unsigned i = 0;
        float t, a, b;
        for (;;) {
            t = p->t;
            a = p->a;
            b = p->b;
            if (param_3 <= t) break;
            if (i == n - 1) {
                *param_2 = a;
                param_2[1] = b;
            }
            i++;
            p++;
            if (n <= i) return param_2;
        }
        float la = a;
        float lb = b;
        if (i != 0) {
            f = (param_3 - base[i - 1].t) / (t - base[i - 1].t);
            la = base[i - 1].a;
            lb = base[i - 1].b;
        }
        *param_2 = (a - la) * f + la;
        param_2[1] = (b - lb) * f + lb;
    }
    return param_2;
}

// @ 0x00fb9740 -- FUN_00fb9740
// Wraps a time value into a normalized [0,1) fraction and samples the same
// (x, value) ramp table as FUN_00fb9870, clamping outside the key range.
double __fastcall FUN_00fb9740(int param_1, int junk, float param_2) {
    float f = (param_2 * *(float*)0x13f1f0c) * *(float*)0x13f1f0c * *(float*)0x140ebc0;
    float* p = *(float**)(param_1 + 0x1a8);
    f = (f - (float)(int)f) * *(float*)0x13f1164;
    int n = (*(int*)(param_1 + 0x1ac) - (int)p) >> 3;
    float a = 1.0f;
    float b = 1.0f;
    float t = 0.0f;
    if (n != 0) {
        if (f < p[0] || p[n * 2 - 2] <= f) {
            a = p[n * 2 - 1];
            b = p[1];
            t = (f - p[n * 2 - 2]) / (p[0] - p[n * 2 - 2]);
        } else {
            int i = 0;
            float* q = p;
            if (0 < n - 1) {
                do {
                    if (q[0] <= f && f < q[2]) {
                        a = p[i * 2 + 1];
                        b = p[i * 2 + 3];
                        t = (f - p[i * 2]) / (p[i * 2 + 2] - p[i * 2]);
                        break;
                    }
                    i++;
                    q += 2;
                } while (i < n - 1);
            }
        }
    }
    return (b - a) * t + a;
}

// @ 0x00fb9950 -- FUN_00fb9950
// Samples a 12-byte-stride (time, valueA, valueB) key table for time param_3 and
// writes the interpolated pair through param_1; clamps to the end keys.
void __cdecl FUN_00fb9950(float* param_1, int* param_2, float param_3) {
    float f = 0.0f;
    float* p = (float*)*param_2;
    int n = (param_2[1] - (int)p) / 12;
    float local_8 = 0.0f;
    float local_4 = 0.0f;
    float local_10 = 0.0f;
    float local_c = 0.0f;
    if (n != 0) {
        if (param_3 <= p[0]) {
            *param_1 = p[1];
            param_1[1] = p[2];
            return;
        }
        if (p[n * 3 - 3] <= param_3) {
            *param_1 = p[n * 3 - 2];
            param_1[1] = p[n * 3 - 1];
            return;
        }
        int i = 0;
        float* q = p;
        if (0 < n - 1) {
            do {
                if (q[0] <= param_3 && param_3 < q[3]) {
                    float* r = p + i * 3;
                    local_8 = r[1];
                    local_4 = r[2];
                    local_10 = r[4];
                    local_c = r[5];
                    f = (param_3 - r[0]) / (p[i * 3 + 3] - r[0]);
                    break;
                }
                i++;
                q += 3;
            } while (i < n - 1);
        }
    }
    *param_1 = (local_10 - local_8) * f + local_8;
    param_1[1] = (local_c - local_4) * f + local_4;
}

// @ 0x00fb9ad0 -- FUN_00fb9ad0
// Blends four 4-float colours (0x50c/0x51c/0x52c/0x53c, stride 0x10) with the
// phase weights derived from the float at +0x30.
void __fastcall FUN_00fb9ad0(int param_1, int junk, float* param_2) {
    float f = *(float*)(param_1 + 0x30);
    float w16, w15;
    float w13 = 0.0f;
    if (0.125f < f) {
        w16 = 0.0f;
        if (0.375f < f) {
            if (f <= 0.625f || 0.875f < f) {
                w15 = 0.0f;
                goto L2c;
            }
            w15 = 1.0f;
            goto L2c;
        }
        w15 = 1.0f;
    } else {
        w16 = 1.0f;
        if (f <= 0.625f || 0.875f < f) {
            w15 = 0.0f;
            goto L2c;
        }
        w15 = 1.0f;
    }
L2c:
    float w14;
    if (f <= 0.375f || 0.625f < f) {
        w14 = 0.0f;
    } else {
        w14 = 1.0f;
    }
    if (0.875f < f) {
        w13 = 1.0f;
    }
    param_2[0] = ((*(float*)(param_1 + 0x52c) * w16 + *(float*)(param_1 + 0x50c) * w15) +
                  *(float*)(param_1 + 0x51c) * w14) + *(float*)(param_1 + 0x53c) * w13;
    param_2[1] = ((*(float*)(param_1 + 0x530) * w16 + *(float*)(param_1 + 0x510) * w15) +
                  *(float*)(param_1 + 0x520) * w14) + *(float*)(param_1 + 0x540) * w13;
    param_2[2] = ((*(float*)(param_1 + 0x534) * w16 + *(float*)(param_1 + 0x514) * w15) +
                  *(float*)(param_1 + 0x524) * w14) + *(float*)(param_1 + 0x544) * w13;
    param_2[3] = ((*(float*)(param_1 + 0x538) * w16 + *(float*)(param_1 + 0x518) * w15) +
                  *(float*)(param_1 + 0x528) * w14) + *(float*)(param_1 + 0x548) * w13;
}

// @ 0x00fb9ca0 -- FUN_00fb9ca0
// Same four-colour phase blend as FUN_00fb9ad0, for the second colour row at 0x54c.
void __fastcall FUN_00fb9ca0(int param_1, int junk, float* param_2) {
    float f = *(float*)(param_1 + 0x30);
    float w16, w15;
    float w13 = 0.0f;
    if (0.125f < f) {
        w16 = 0.0f;
        if (0.375f < f) {
            if (f <= 0.625f || 0.875f < f) {
                w15 = 0.0f;
                goto L2c;
            }
            w15 = 1.0f;
            goto L2c;
        }
        w15 = 1.0f;
    } else {
        w16 = 1.0f;
        if (f <= 0.625f || 0.875f < f) {
            w15 = 0.0f;
            goto L2c;
        }
        w15 = 1.0f;
    }
L2c:
    float w14;
    if (f <= 0.375f || 0.625f < f) {
        w14 = 0.0f;
    } else {
        w14 = 1.0f;
    }
    if (0.875f < f) {
        w13 = 1.0f;
    }
    param_2[0] = ((*(float*)(param_1 + 0x56c) * w16 + *(float*)(param_1 + 0x54c) * w15) +
                  *(float*)(param_1 + 0x55c) * w14) + *(float*)(param_1 + 0x57c) * w13;
    param_2[1] = ((*(float*)(param_1 + 0x570) * w16 + *(float*)(param_1 + 0x550) * w15) +
                  *(float*)(param_1 + 0x560) * w14) + *(float*)(param_1 + 0x580) * w13;
    param_2[2] = ((*(float*)(param_1 + 0x574) * w16 + *(float*)(param_1 + 0x554) * w15) +
                  *(float*)(param_1 + 0x564) * w14) + *(float*)(param_1 + 0x584) * w13;
    param_2[3] = ((*(float*)(param_1 + 0x578) * w16 + *(float*)(param_1 + 0x558) * w15) +
                  *(float*)(param_1 + 0x568) * w14) + *(float*)(param_1 + 0x588) * w13;
}
