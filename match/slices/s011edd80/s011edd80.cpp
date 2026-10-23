// slice s011edd80 -- RenderWare D3D9 graphics state compilation / dispatch
// (rw::graphics::CompiledState + rw::graphics::EmbeddedState).
// Module flags: /O2 /MD /Gy /TP /arch:SSE (the big soft-state dispatch uses movaps on
// 16-byte aligned matrix rows, so it must be SSE).
#include <xmmintrin.h>
#include <intrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

// 16-byte aligned row vector / 4x4 matrix (copied with movaps).
union __declspec(align(16)) V4 { __m128 v; struct { float x, y, z, w; }; };
struct __declspec(align(16)) M44 { __m128 r[4]; };

// A 0x11-dword block (texture-stage / sampler state deltas).
struct U17 { u32 v[0x11]; };

// ---------------------------------------------------------------- globals
extern "C" u32   g_softStateUpdated;              // 0x16f9110
extern "C" u32   g_primitiveType;                 // 0x16f85a8
extern "C" u32   g_softStateDelta;                // 0x16f8af8
extern "C" void* g_d3dDevice;                     // 0x16f89d0
extern "C" u32   g_transformType;                 // 0x16f8b50
extern "C" void* g_transform;                     // 0x16f85ac
extern "C" u32   g_inverseTransform;              // 0x16f9120
extern "C" u32   g_transposedTransform;           // 0x16f8cf4
extern "C" u32   g_inverseNormalizedTransform;    // 0x16f9114
extern "C" void* g_vertexDescriptor;              // 0x16f65a0
extern "C" void* g_shader;                        // 0x16f6568
extern "C" u32   g_shaderDataDirty[0x800];        // 0x16f89f8
extern "C" void* g_shaderData[0x10000];           // 0x16f65a8
extern "C" float g_color[4];                      // 0x16f6590
extern "C" u32   g_colorIsWhite;                  // 0x16f89c4
extern "C" float g_ambient[3];                    // 0x16f5c40
extern "C" u32   g_ambientIsBlack;                // 0x16f89d4
extern "C" u32   g_light[8];                      // 0x16f656c
extern "C" u8    g_uvMapping[0x11];               // 0x16f85b4
extern "C" u32   g_fogType;                       // 0x16f90c0
extern "C" float g_fogColor[3];                   // 0x16f9168
extern "C" float g_fogStartDensity;               // 0x16f5c54
extern "C" float g_fogEnd;                        // 0x16f8d00
extern "C" u32   g_renderStateShadow[0x100];      // 0x16f85c8
extern "C" u32   g_renderStateDelta[0x100];       // 0x16f89d8
extern "C" u32   g_rasterDelta;                   // 0x16f8b00
extern "C" u32   g_paletteDelta;                  // 0x16f85b0
extern "C" void* g_paletteShadow;                 // 0x16f9130
extern "C" u32   g_textureStageStateDelta[8];     // 0x16f8b58
extern "C" u32   g_textureStageStateShadow[8*0x21];// 0x16f5ca0
extern "C" u32   g_samplerStateDelta[8];          // 0x16f8cb0
extern "C" u32   g_samplerStateShadow[8*0xe];     // 0x16f8d08
extern "C" u8    g_textureCaps;                   // 0x16fa3bd
extern "C" u8    g_stageType[1];                  // 0x16f8d24
extern "C" float g_one;                           // 0x1485720

// ---------------------------------------------------------------- engine calls
void __cdecl SetTexture(u32 stage, u32 tex);              // 0x11f1280
void __cdecl FindLights();                                // 0x11f1130
void __cdecl CheckUVMapping();                            // 0x11f1210
void __cdecl D3D9VertexShaderChange(void* shader);        // 0x11f7830
void __cdecl VertexDescriptorChange(void* vd);            // 0x006dd2a0

typedef void (__stdcall* PFN_2)(void*, u32);
typedef void (__stdcall* PFN_3)(void*, u32, u32);
typedef void (__stdcall* PFN_4)(void*, u32, u32, u32);

namespace rw { namespace graphics {

struct EmbeddedState;
struct CompiledState;

struct EmbeddedState {
    u32 instancedSize;    // +0x00
    u32 primitiveType;    // +0x04
    u32 softStateDirty;   // +0x08
    u32 softStateDelta;   // +0x0c
    u32 hardStateDirty;   // +0x10
    u32 hardStateDelta;   // +0x14
    u32 shader;           // +0x18

    void SetRaster(int, int);                            // 0x011ee6b0
    int  D3D9GetTextureStageState(int);                  // 0x011ee870
    void D3D9HasTextureStageState(int, int, int);        // 0x011eea30
};

struct CompiledState : EmbeddedState {
    float* D3D9SoftStateDispatch(float*);                    // 0x011edd80
    int*   D3D9RenderStateDispatch(int*);                    // 0x011ee2f0
    u32*   D3D9Palette_Raster_TSS_Samp_Dispatch(int*);       // 0x011ee380
    void   Dispatch();                                       // 0x011ee580
};

}} // namespace rw::graphics

using namespace rw::graphics;

// ===========================================================================
// @ 0x011edd80  rw::graphics::CompiledState::D3D9SoftStateDispatch
// ===========================================================================
// @ 0x011edd80
float* CompiledState::D3D9SoftStateDispatch(float* param_2)
{
    u32 uVar8 = softStateDirty;
    u32 local = uVar8 & 0x1fffff;
    float* p = param_2;

    if ((uVar8 & 0x4000) != 0) {
        g_softStateUpdated |= 0x4000;
        local = uVar8 & 0x1fbfff;
        if (local == 0)
            return p;
    }
    if ((local & 1) != 0) {
        g_transformType = softStateDirty >> 0x1c;
        M44* m;
        if ((local & 2) == 0) {
            m = (M44*)p;
            p += 0x10;
        } else {
            m = (M44*)*(void**)p;
            p += 1;
        }
        g_transform = m;
        g_inverseTransform = 0;
        V4 t;
        t.v = m->r[0]; t.w = 0.0f; m->r[0] = t.v;
        t.v = m->r[1]; t.w = 0.0f; m->r[1] = t.v;
        t.v = m->r[2]; t.w = 0.0f; m->r[2] = t.v;
        t.v = m->r[3]; t.w = 1.0f; m->r[3] = t.v;
        g_softStateUpdated |= 1;
        local &= ~3u;
        g_transposedTransform = 0;
        g_inverseNormalizedTransform = 0;
        if (local == 0)
            return p;
    }
    if ((local & 0x100000) != 0) {
        u32 cnt = *(u16*)((char*)p + 0xc);
        p += (cnt + 2) * 3;
        if (g_vertexDescriptor != p - (cnt + 2) * 3)
            VertexDescriptorChange(p - (cnt + 2) * 3);
        if ((g_softStateUpdated & 0x100000) != 0)
            g_softStateUpdated |= 4;
        local &= ~0x100000u;
        if (local == 0)
            return p;
    }
    if ((local & 4) != 0) {
        if (g_shader != (void*)shader)
            D3D9VertexShaderChange((void*)shader);
        local &= ~4u;
        if (local == 0)
            return p;
    }
    if ((local & 8) != 0) {
        u8* base = (u8*)p;
        u16 id = *(u16*)base;
        p = (float*)(base + 8);
        while (id != 0) {
            g_shaderDataDirty[id >> 5] |= 1u << (id & 0x1f);
            if (*(u16*)(base + 4) != 0) {
                p = (float*)((u8*)p + *(u16*)(base + 2));
                g_shaderData[id] = (void*)p;
                p = (float*)((u8*)p + *(u16*)(base + 4));
            } else {
                g_shaderData[id] = *(void**)p;
                p += 1;
            }
            base = (u8*)p;
            id = *(u16*)base;
            p = (float*)(base + 8);
        }
        g_softStateUpdated |= 8;
        local &= ~8u;
        if (local == 0)
            return p;
    }
    if ((local & 0x10) != 0) {
        float f0 = p[0], f1 = p[1], f2 = p[2], f3 = p[3];
        p += 4;
        if (g_color[0] != f0 || g_color[1] != f1 || g_color[2] != f2 || g_color[3] != f3) {
            g_softStateUpdated |= 0x10;
            g_color[0] = f0; g_color[1] = f1; g_color[2] = f2; g_color[3] = f3;
            g_colorIsWhite = (f0 == 1.0f && f1 == 1.0f && f2 == 1.0f && f3 == 1.0f) ? 1 : 0;
        }
        local &= ~0x10u;
        if (local == 0)
            return p;
    }
    if ((local & 0x20) != 0) {
        float f0 = p[0], f1 = p[1], f2 = p[2];
        p += 3;
        if (g_ambient[0] != f0 || g_ambient[1] != f1 || g_ambient[2] != f2) {
            g_softStateUpdated |= 0x20;
            g_ambient[0] = f0; g_ambient[1] = f1; g_ambient[2] = f2;
            g_ambientIsBlack = (f0 == 0.0f && f1 == 0.0f && f2 == 0.0f) ? 1 : 0;
        }
        local &= ~0x20u;
        if (local == 0)
            return p;
    }
    uVar8 = local & 0x3fc0;
    if (uVar8 != 0) {
        g_softStateUpdated |= uVar8;
        u32* lp = g_light;
        do {
            if ((uVar8 & 0x40) != 0) {
                *lp = *(u32*)p;
                p += 1;
            }
            uVar8 >>= 1;
            lp++;
        } while (0x3f < uVar8);
        FindLights();
        local &= 0xffffc03f;
        if (local == 0)
            return p;
    }
    if ((local & 0x8000) != 0) {
        u32 i = 0;
        do {
            if (g_uvMapping[i] != ((u8*)p)[i]) {
                g_uvMapping[i] = ((u8*)p)[i];
                g_softStateUpdated |= 0x8000;
            }
            i++;
        } while (i < 0x11);
        p = (float*)((u8*)p + 0x11);
        if ((g_softStateUpdated & 0x8000) != 0)
            CheckUVMapping();
        local &= 0xffff7fff;
        if (local == 0)
            return p;
    }
    if ((local & 0xf0000) != 0) {
        if ((local & 0x10000) != 0) {
            g_fogType = *(u32*)p;
            p += 1;
            g_softStateUpdated |= 0x10000;
        }
        if ((local & 0xe0000) != 0) {
            if ((local & 0x20000) != 0) {
                g_fogColor[0] = p[0];
                g_fogColor[1] = p[1];
                g_fogColor[2] = p[2];
                p += 1;
                g_softStateUpdated |= 0x20000;
            }
            if ((local & 0x40000) != 0) {
                g_fogStartDensity = p[0];
                p += 1;
                g_softStateUpdated |= 0x40000;
            }
            if ((local & 0x80000) != 0) {
                g_fogEnd = p[0];
                p += 1;
                g_softStateUpdated |= 0x80000;
            }
        }
    }
    return p;
}

// ===========================================================================
// @ 0x011ee2f0  rw::graphics::CompiledState::D3D9RenderStateDispatch
// ===========================================================================
// @ 0x011ee2f0
int* CompiledState::D3D9RenderStateDispatch(int* param_1)
{
    u32* p = (u32*)param_1;
    u32 iVar4 = *p++;
    do {
        u32 iVar5 = *p++;
        do {
            u32 shadow = g_renderStateShadow[iVar5];
            g_renderStateDelta[iVar4] |= 1u << ((iVar5 - 7) & 0x1f);
            u32 iVar2 = *p++;
            if (iVar2 != shadow) {
                void* dev = g_d3dDevice;
                ((PFN_3*)*(void**)dev)[0x39](dev, iVar5, iVar2);
                g_renderStateShadow[iVar5] = iVar2;
            }
            iVar5 = *p++;
        } while (iVar5 != 0xffffffff);
        iVar4 = *p++;
    } while (iVar4 != 0xffffffff);
    return (int*)p;
}

// ===========================================================================
// @ 0x011ee380  rw::graphics::CompiledState::D3D9Palette_Raster_TSS_Samp_Dispatch
// ===========================================================================
// @ 0x011ee380
u32* CompiledState::D3D9Palette_Raster_TSS_Samp_Dispatch(int* param_2)
{
    u32* p = (u32*)param_2;
    u32 iVar1 = *p++;
    if (iVar1 != 0xffffffff) {
        g_paletteDelta = 1;
        if ((void*)iVar1 != g_paletteShadow) {
            void* dev = g_d3dDevice;
            if (iVar1 == 0) {
                ((PFN_3*)*(void**)dev)[0x47](dev, 0, 0);
            } else {
                ((PFN_3*)*(void**)dev)[0x47](dev, 0, iVar1);
                ((PFN_2*)*(void**)dev)[0x49](dev, 0);
            }
            g_paletteShadow = (void*)iVar1;
        }
    }
    u32 uVar3 = hardStateDirty;
    if ((uVar3 & 0xdffff) != 0) {
        u32 stage = *p++;
        g_rasterDelta |= uVar3 & 0x1ffff;
        do {
            u32 tex = *p++;
            if (tex != 0xffffffff)
                SetTexture(stage, tex);
            u32 mask = *p++;
            if (mask != 0) {
                g_softStateUpdated |= 0x1000000;
                g_textureStageStateDelta[stage] |= mask;
                u32 idx = *p++;
                u32 base = stage * 0x21;
                do {
                    u32 val = *p++;
                    u32 k = base + idx;
                    if (val != g_textureStageStateShadow[k]) {
                        void* dev = g_d3dDevice;
                        ((PFN_4*)*(void**)dev)[0x43](dev, stage, idx, val);
                        g_textureStageStateShadow[k] = val;
                    }
                    idx = *p++;
                } while (idx != 0xffffffff);
            }
            u32 smask = *p++;
            if (smask != 0) {
                g_softStateUpdated |= 0x2000000;
                g_samplerStateDelta[stage] |= smask;
                u32 idx = *p++;
                bool bFlag = false;
                if (g_textureCaps != 0) {
                    bFlag = *(i32*)(g_stageType + stage * 0x38) == 2;
                    u32* q = p;
                    u32 sidx = idx;
                    u32 sval = *q++;
                    while (sidx != 7) {
                        sidx = *q++;
                        if (sidx == 0xffffffff)
                            break;
                        sval = *q++;
                    }
                    if (sidx == 7)
                        bFlag = (sval == 2);
                }
                u32 sbase = stage * 0xe;
                do {
                    u32 val = *p++;
                    if (bFlag && val == 2 && (idx == 6 || idx == 5))
                        val = 3;
                    u32 k = sbase + idx;
                    if (val != g_samplerStateShadow[k]) {
                        void* dev = g_d3dDevice;
                        ((PFN_4*)*(void**)dev)[0x45](dev, stage, idx, val);
                        g_samplerStateShadow[k] = val;
                    }
                    idx = *p++;
                } while (idx != 0xffffffff);
            }
            stage = *p++;
        } while (stage != 0xffffffff);
    }
    return p;
}

// ===========================================================================
// @ 0x011ee580  rw::graphics::CompiledState::Dispatch
// ===========================================================================
// @ 0x011ee580
void CompiledState::Dispatch()
{
    g_primitiveType = primitiveType;
    float* p = (float*)(((u32)(void*)this + 0x2b) & 0xfffffff0);
    if ((softStateDirty & 0xfffff) != 0)
        p = D3D9SoftStateDispatch(p);
    g_softStateDelta |= softStateDelta;
    u32 hd = hardStateDelta;
    if (hd != 0) {
        if ((hd & 0x20000) != 0) {
            g_renderStateDelta[0] = *(u32*)(p + 0);
            g_renderStateDelta[1] = *(u32*)(p + 1);
            g_renderStateDelta[2] = *(u32*)(p + 2);
            g_renderStateDelta[3] = *(u32*)(p + 3);
            g_renderStateDelta[4] = *(u32*)(p + 4);
            g_renderStateDelta[5] = *(u32*)(p + 5);
            g_renderStateDelta[6] = *(u32*)(p + 6);
            p += 7;
        }
        g_rasterDelta |= hd & 0x1ffff;
        g_paletteDelta |= (hd >> 0x14) & 1;
        if ((hd & 0x40000) != 0) {
            *(U17*)g_textureStageStateDelta = *(U17*)p;
            p += 0x11;
        }
        if ((hd & 0x80000) != 0) {
            *(U17*)g_samplerStateDelta = *(U17*)p;
            p += 0x11;
        }
    }
    u32 hdr = hardStateDirty;
    if (hdr != 0) {
        if ((hdr & 0x20000) != 0) {
            p = (float*)D3D9RenderStateDispatch((int*)p);
            hdr &= 0xfffdffff;
            g_softStateUpdated |= 0x800000;
        }
        if (hdr != 0)
            D3D9Palette_Raster_TSS_Samp_Dispatch((int*)p);
    }
}

// ===========================================================================
// @ 0x011ee6b0  rw::graphics::EmbeddedState::SetRaster
// ===========================================================================
// @ 0x011ee6b0
void EmbeddedState::SetRaster(int param_2, int param_3)
{
    u32 uVar2 = softStateDirty;
    int* p = (int*)(((u32)(void*)this + 0x2b) & 0xfffffff0);
    if (uVar2 != 0) {
        if ((uVar2 & 1) != 0) {
            if ((uVar2 & 2) != 0)
                p += 1;
            else
                p += 0x10;
        }
        if ((uVar2 & 0x100000) != 0)
            p += (*(u16*)(p + 3) + 2) * 3;
        if ((uVar2 & 8) != 0) {
            short sVar1 = (short)*p;
            int* r = p;
            for (;;) {
                p = r + 2;
                if (sVar1 == 0)
                    break;
                if (*(u16*)(r + 1) == 0)
                    p = p + 1;
                else
                    p = (int*)((int)p + *(u16*)((int)r + 2) + *(u16*)(r + 1));
                r = p;
                sVar1 = (short)*r;
            }
        }
        if ((uVar2 & 0x10) != 0)
            p += 4;
        if ((uVar2 & 0x20) != 0)
            p += 3;
        if ((uVar2 & 0x3fc0) != 0) {
            int i = 6;
            do {
                u32 b = 1u << i;
                if ((uVar2 & 0x3fc0) < b)
                    break;
                if ((uVar2 & b) != 0)
                    p += 1;
                i++;
            } while ((u32)(i - 6) < 8);
        }
        if ((uVar2 & 0x8000) != 0)
            p = (int*)((char*)p + 0x11);
        if ((uVar2 & 0xf0000) != 0) {
            if ((uVar2 & 0x10000) != 0)
                p += 1;
            if ((uVar2 & 0xe0000) != 0) {
                if ((uVar2 & 0x20000) != 0)
                    p += 3;
                if ((uVar2 & 0x40000) != 0)
                    p += 1;
                if ((uVar2 & 0x80000) != 0)
                    p += 1;
            }
        }
    }
    uVar2 = hardStateDelta;
    if (uVar2 != 0) {
        if ((uVar2 & 0x20000) != 0)
            p += 7;
        if ((uVar2 & 0x40000) != 0)
            p += 0x11;
        if ((uVar2 & 0x80000) != 0)
            p += 0x11;
    }
    if ((hardStateDirty & 0x20000) != 0) {
        int* r;
        p += 1;
        do {
            p += 1;
            do {
                r = p;
                p = r + 2;
            } while (r[1] != -1);
            p = r + 3;
        } while (r[2] != -1);
    }
    int iVar5 = p[1];
    p += 2;
    do {
        if (*p != -1 && iVar5 == param_2) {
            if (*p != param_3)
                *p = param_3;
            return;
        }
        int* r = p + 2;
        if (p[1] != 0) {
            r = p + 3;
            do {
                p = r + 1;
                r += 2;
            } while (*p != -1);
        }
        p = r + 1;
        if (*r != 0) {
            p = r + 2;
            do {
                r = p + 1;
                p += 2;
            } while (*r != -1);
        }
        iVar5 = *p;
        p += 1;
    } while (iVar5 != -1);
}

// ===========================================================================
// @ 0x011ee870  rw::graphics::EmbeddedState::D3D9GetTextureStageState
// ===========================================================================
// @ 0x011ee870
int EmbeddedState::D3D9GetTextureStageState(int param_2)
{
    u32 uVar2 = softStateDirty;
    int* p = (int*)(((u32)(void*)this + 0x2b) & 0xfffffff0);
    if (uVar2 != 0) {
        if ((uVar2 & 1) != 0) {
            if ((uVar2 & 2) != 0)
                p += 1;
            else
                p += 0x10;
        }
        if ((uVar2 & 0x100000) != 0)
            p += (*(u16*)(p + 3) + 2) * 3;
        if ((uVar2 & 8) != 0) {
            short sVar1 = (short)*p;
            int* r = p;
            for (;;) {
                p = r + 2;
                if (sVar1 == 0)
                    break;
                if (*(u16*)(r + 1) == 0)
                    p = p + 1;
                else
                    p = (int*)((int)p + *(u16*)((int)r + 2) + *(u16*)(r + 1));
                r = p;
                sVar1 = (short)*r;
            }
        }
        if ((uVar2 & 0x10) != 0)
            p += 4;
        if ((uVar2 & 0x20) != 0)
            p += 3;
        if ((uVar2 & 0x3fc0) != 0) {
            int i = 6;
            do {
                u32 b = 1u << i;
                if ((uVar2 & 0x3fc0) < b)
                    break;
                if ((uVar2 & b) != 0)
                    p += 1;
                i++;
            } while ((u32)(i - 6) < 8);
        }
        if ((uVar2 & 0x8000) != 0)
            p = (int*)((char*)p + 0x11);
        if ((uVar2 & 0xf0000) != 0) {
            if ((uVar2 & 0x10000) != 0)
                p += 1;
            if ((uVar2 & 0xe0000) != 0) {
                if ((uVar2 & 0x20000) != 0)
                    p += 3;
                if ((uVar2 & 0x40000) != 0)
                    p += 1;
                if ((uVar2 & 0x80000) != 0)
                    p += 1;
            }
        }
    }
    uVar2 = hardStateDelta;
    if (uVar2 != 0) {
        if ((uVar2 & 0x20000) != 0)
            p += 7;
        if ((uVar2 & 0x40000) != 0)
            p += 0x11;
        if ((uVar2 & 0x80000) != 0)
            p += 0x11;
    }
    if ((hardStateDirty & 0x20000) != 0) {
        int* r;
        p += 1;
        do {
            p += 1;
            do {
                r = p;
                p = r + 2;
            } while (r[1] != -1);
            p = r + 3;
        } while (r[2] != -1);
    }
    int iVar5 = p[1];
    p += 2;
    do {
        if (*p != -1 && iVar5 == param_2)
            return *p;
        int* r = p + 2;
        if (p[1] != 0) {
            r = p + 3;
            do {
                p = r + 1;
                r += 2;
            } while (*p != -1);
        }
        p = r + 1;
        if (*r != 0) {
            p = r + 2;
            do {
                r = p + 1;
                p += 2;
            } while (*r != -1);
        }
        iVar5 = *p;
        p += 1;
    } while (iVar5 != -1);
    return 0;
}

// ===========================================================================
// @ 0x011eea30  rw::graphics::EmbeddedState::D3D9HasTextureStageState
// ===========================================================================
// @ 0x011eea30
void EmbeddedState::D3D9HasTextureStageState(int param_2, int param_3, int param_4)
{
    u32 uVar2 = softStateDirty;
    int* p = (int*)(((u32)(void*)this + 0x2b) & 0xfffffff0);
    if (uVar2 != 0) {
        if ((uVar2 & 1) != 0) {
            if ((uVar2 & 2) != 0)
                p += 1;
            else
                p += 0x10;
        }
        if ((uVar2 & 0x100000) != 0)
            p += (*(u16*)(p + 3) + 2) * 3;
        if ((uVar2 & 8) != 0) {
            short sVar1 = (short)*p;
            int* r = p;
            for (;;) {
                p = r + 2;
                if (sVar1 == 0)
                    break;
                if (*(u16*)(r + 1) == 0)
                    p = p + 1;
                else
                    p = (int*)((int)p + *(u16*)((int)r + 2) + *(u16*)(r + 1));
                r = p;
                sVar1 = (short)*r;
            }
        }
        if ((uVar2 & 0x10) != 0)
            p += 4;
        if ((uVar2 & 0x20) != 0)
            p += 3;
        if ((uVar2 & 0x3fc0) != 0) {
            int i = 6;
            do {
                u32 b = 1u << i;
                if ((uVar2 & 0x3fc0) < b)
                    break;
                if ((uVar2 & b) != 0)
                    p += 1;
                i++;
            } while ((u32)(i - 6) < 8);
        }
        if ((uVar2 & 0x8000) != 0)
            p = (int*)((char*)p + 0x11);
        if ((uVar2 & 0xf0000) != 0) {
            if ((uVar2 & 0x10000) != 0)
                p += 1;
            if ((uVar2 & 0xe0000) != 0) {
                if ((uVar2 & 0x20000) != 0)
                    p += 3;
                if ((uVar2 & 0x40000) != 0)
                    p += 1;
                if ((uVar2 & 0x80000) != 0)
                    p += 1;
            }
        }
    }
    uVar2 = hardStateDelta;
    if (uVar2 != 0) {
        if ((uVar2 & 0x20000) != 0)
            p += 7;
        if ((uVar2 & 0x40000) != 0)
            p += 0x11;
        if ((uVar2 & 0x80000) != 0)
            p += 0x11;
    }
    if ((hardStateDirty & 0x20000) != 0) {
        int* r;
        p += 1;
        do {
            p += 1;
            do {
                r = p;
                p = r + 2;
            } while (r[1] != -1);
            p = r + 3;
        } while (r[2] != -1);
    }
    int iVar7 = p[1];
    p += 2;
    do {
        int* r = p + 2;
        if (p[1] != 0) {
            r = p + 3;
            do {
                p = r + 1;
                r += 2;
            } while (*p != -1);
        }
        p = r + 1;
        if (*r != 0) {
            int iVar5 = *p;
            p = r + 2;
            do {
                if (param_2 == iVar7 && param_3 == iVar5) {
                    if (*p != param_4)
                        *p = param_4;
                    return;
                }
                iVar5 = p[1];
                p += 2;
            } while (iVar5 != -1);
        }
        iVar7 = *p;
        p += 1;
        if (iVar7 == -1)
            return;
    } while (true);
}
