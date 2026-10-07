// RenderWare graphics shader/camera management, 0x011f3f20-0x011f4e8c.
// Reconstructed from the retail disassembly + Ghidra decompile; class layouts and
// member names from the 2008 dev-build PDB (rw::graphics::Shader, rw::graphics::Camera).
#include "types.h"
#include <intrin.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t  i32;

// ---------------------------------------------------------------- forward decls
struct Shader;
struct Camera;

void __cdecl FUN_011f3ab0();
void __cdecl FUN_011f39b0();
void __cdecl UnregisterShader(u32 id);          // 0x11fa050
void __cdecl ShaderManagerRegister(u32 id, Shader* s); // 0x11f9fb0
void __cdecl FUN_011fd4d0();
void __cdecl FUN_011fd500();
void __cdecl FUN_011f7850();
void __cdecl FUN_011f6920();
void __cdecl FUN_011f7870();
u32  __cdecl FUN_011f78b0();
void __cdecl FUN_011f7c70();
void __cdecl FUN_011f6940();
u32  __cdecl FUN_011f6980();
void __cdecl FUN_011f6e80();
void __cdecl FUN_011fcee0(void* buf, u32 flags);
void __cdecl FUN_011fcde0(void* buf, u32 flags);
void __cdecl FUN_012057f0();
void FUN_011fb220(); void FUN_011fb1c0(); void FUN_011fb1f0(); void FUN_011fa370();
void FUN_011fa310(); void FUN_011fa630(); void FUN_011fa4f0(); void FUN_011fa5a0();
void FUN_011fa480(); void FUN_011fa6d0(); void FUN_011fa8c0(); void FUN_011fa8f0();
void FUN_011fa920(); void FUN_011fa9d0(); void FUN_011faa50(); void FUN_011faa80();
void FUN_011fbea0(); void FUN_011fab10(); void FUN_011fab60(); void FUN_011fab90();
void FUN_011fbf50(); void FUN_011fcbc0(); void FUN_011fac30(); void FUN_011fc040();
void FUN_011fc120(); void FUN_011fad70(); void FUN_011fc200(); void FUN_011face0();
void FUN_011fc3d0(); void FUN_011fae40(); void FUN_011fcc70(); void FUN_011faea0();
void FUN_011faf00(); void FUN_011faf30(); void FUN_011faf60(); void FUN_011fc470();
void FUN_011faf90(); void FUN_011fb030(); void FUN_011fb0f0(); void FUN_011fbce0();
void FUN_011fbda0(); void FUN_011fbbf0(); void FUN_011fa410();
void* __cdecl ArenaTypeRegGetType(int type);    // 0x11e22c0
struct Obj2270 { int Method(int h); };           // 0x11e2270 (__thiscall)

// matrix multiply/transpose helpers (D3DX); cdecl with pointer args
void __cdecl D3DXMatrixMultiply(void* out, const void* a, const void* b); // 0x11e1ff2
void __cdecl D3DXMatrixTranspose(void* out, const void* m);               // 0x11e1fec

// ---------------------------------------------------------------- rw::graphics::Shader (PDB, size 0x44)
struct Shader {
    i32        m_geomType;            // +0x00
    u32        m_flags;               // +0x04
    u32        m_elementTypes;        // +0x08
    u16        m_minVSVersionSupported; // +0x0c
    u16        m_maxVSVersionSupported; // +0x0e
    u16        m_minPSVersionSupported; // +0x10
    u16        m_maxPSVersionSupported; // +0x12
    void*      m_dispatchCB;          // +0x14
    u32        m_numDataTypes;        // +0x18
    u16*       m_dataTypeList;        // +0x1c
    u32        m_vertexShaderUpdateFlags; // +0x20
    u32        m_numVertexShaderBuilders; // +0x24
    void*      m_vertexShaderBuilders;    // +0x28
    u32        m_pixelShaderUpdateFlags;  // +0x2c
    u32        m_numPixelShaderBuilders;  // +0x30
    void*      m_pixelShaderBuilders;     // +0x34
    u32        m_id;                  // +0x38
    i32        m_refCount;            // +0x3c
    Shader*    m_next;                // +0x40

    void Release();
    int  CheckShaderVersionSupport();
};

// ---------------------------------------------------------------- rw::graphics::Camera (PDB, size 0xa0)
struct D3DVIEWPORT9 { u32 X, Y, Width, Height; float MinZ, MaxZ; };

struct Camera {
    float  m_transform[16];   // +0x00
    void*  m_raster[4];       // +0x40
    void*  m_zbuffer;         // +0x50
    float  m_viewOffset[2];   // +0x54
    float  m_viewWindow[2];   // +0x5c
    float  m_recipViewWindow[2]; // +0x64
    i32    m_projectionType;  // +0x6c
    float  m_nearPlane;       // +0x70
    float  m_farPlane;        // +0x74
    D3DVIEWPORT9 m_viewport;  // +0x78
    void*  m_window;          // +0x90
    u32    m_stencilClear;    // +0x94

    int Check();
};

// ---------------------------------------------------------------- D3DCAPS9 subset
struct D3DCAPS9 {
    u8  pad0[0xc4];
    u32 VertexShaderVersion;  // +0xc4
    u8  pad1[4];
    u32 PixelShaderVersion;   // +0xcc
};
D3DCAPS9* __cdecl DevCapsManager_GetD3DCAPS9();  // 0x11f8af0

// ---------------------------------------------------------------- globals
extern Shader g_defaultShader;             // 0x170a5f0
extern Shader* g_activeShader;             // 0x16f6568
extern u32   g_softState;                  // 0x16f9110
extern u8    g_vsTokenBuf[];               // 0x170ee48
extern i32   g_vsTokenIdx;                 // 0x1711efc
extern u32   g_vsStateMask;                // 0x170eee8
extern u8    g_psTokenBuf[];               // 0x170ec98
extern i32   g_psTokenIdx;                 // 0x170ed5c
extern u32   g_psStateMask;                // 0x170ed4c

// default shader ctor
Shader* __cdecl ShaderConstruct(Shader* s, u32 id, u32 geomType, u32 flags, u32 elementTypes,
                                u32 vsMin, u32 vsMax, u32 psMin, u32 psMax); // 0x11f4440
int  __cdecl ShaderDispatch();             // 0x11f42f0
int  __cdecl ShaderCleanup();              // 0x11f4420
Shader* __cdecl GetDefaultShader();        // 0x11f45d0
void __cdecl ReleaseDefaultShader();       // 0x11f45a0
void __cdecl InitShaderTable();            // 0x11f4630

// ===========================================================================
// @ 0x011f4200
void Shader::Release()
{
    if (--m_refCount == 0) {
        UnregisterShader(m_id);
        m_id = 0;
        m_next = 0;
    }
}

// ===========================================================================
// @ 0x011f4220
void __cdecl ReleaseShaderC(Shader* s)
{
    if (--s->m_refCount == 0) {
        UnregisterShader(s->m_id);
        s->m_id = 0;
        s->m_next = 0;
    }
}

// ===========================================================================
// Table of shader definitions at 0x16fa5e8 (2048 entries of 0x20 bytes).
struct ShaderDef {
    u16  m_id;        // +0x00
    u16  pad02;
    u32  f04;         // +0x04
    u8   f08;         // +0x08
    u8   f09;         // +0x09
    u8   pad0a[6];
    u32  p10;         // +0x10
    u32  p14;         // +0x14
    u32  p18;         // +0x18
    u32  p1c;         // +0x1c
};
extern ShaderDef g_shaderDefs[];   // 0x16fa5e8

// @ 0x011f4270
void __cdecl SetShaderDef(u16 id, u32 a, u32 b, u32 c, u32 d)
{
    g_shaderDefs[id].p10 = a;
    g_shaderDefs[id].p14 = b;
    g_shaderDefs[id].p18 = c;
    g_shaderDefs[id].m_id = id;
    g_shaderDefs[id].f04 = 0;
    g_shaderDefs[id].f08 = 0;
    g_shaderDefs[id].f09 = 0;
    g_shaderDefs[id].p1c = d;
}

// ===========================================================================
// @ 0x011f42c0
int __cdecl MapShaderHandle(int h, void* self)
{
    u16 index = (u16)h;
    if (index >= 0x400 && index < 0x800) {
        return ((Obj2270*)self)->Method(h - 0x400) + 0x400;
    }
    return h;
}

// ===========================================================================
// @ 0x011f42f0
int __cdecl ShaderDispatch()
{
    if ((g_activeShader->m_vertexShaderUpdateFlags & g_softState) != 0) {
        FUN_011f7870();
        i32 n = g_activeShader->m_numVertexShaderBuilders;
        u32* p = (u32*)g_activeShader->m_vertexShaderBuilders;
        do {
            u32 v = *p++;
            if (v < 0x100) {
                g_vsTokenBuf[g_vsTokenIdx++] = (u8)v;
            } else {
                ((void(__cdecl*)(void*))v)(g_vsTokenBuf);
            }
        } while (--n);
        g_vsTokenBuf[g_vsTokenIdx++] = 0;
        g_softState |= FUN_011f78b0();
        FUN_011f7c70();
    }
    if ((g_vsStateMask & g_softState) != 0) {
        FUN_011fcee0(g_vsTokenBuf, g_softState);
    }
    if ((g_activeShader->m_pixelShaderUpdateFlags & g_softState) != 0) {
        FUN_011f6940();
        i32 n = g_activeShader->m_numPixelShaderBuilders;
        u32* p = (u32*)g_activeShader->m_pixelShaderBuilders;
        do {
            u32 v = *p++;
            if (v < 0x100) {
                g_psTokenBuf[g_psTokenIdx++] = (u8)v;
            } else {
                ((void(__cdecl*)(void*))v)(g_psTokenBuf);
            }
        } while (--n);
        g_psTokenBuf[g_psTokenIdx++] = 0;
        g_softState |= FUN_011f6980();
        FUN_011f6e80();
    }
    if ((g_psStateMask & g_softState) != 0) {
        FUN_011fcde0(g_psTokenBuf, g_softState);
    }
    return 1;
}

// ===========================================================================
// @ 0x011f4420
int __cdecl ShaderCleanup()
{
    FUN_011fd4d0();
    FUN_011fd500();
    FUN_011f7850();
    FUN_011f6920();
    return 1;
}

// ===========================================================================
// @ 0x011f4440
Shader* __cdecl ShaderConstruct(Shader* s, u32 id, u32 geomType, u32 flags, u32 elementTypes,
                                u32 vsMin, u32 vsMax, u32 psMin, u32 psMax)
{
    s->m_elementTypes = elementTypes;
    s->m_flags = flags;
    s->m_geomType = geomType;
    s->m_dispatchCB = (void*)&ShaderDispatch;
    s->m_refCount = 1;
    s->m_minVSVersionSupported = _byteswap_ushort((u16)vsMin);
    s->m_maxVSVersionSupported = _byteswap_ushort((u16)vsMax);
    s->m_minPSVersionSupported = _byteswap_ushort((u16)psMin);
    s->m_maxPSVersionSupported = _byteswap_ushort((u16)psMax);
    s->m_id = id;
    s->m_numDataTypes = 0;
    s->m_dataTypeList = 0;
    s->m_vertexShaderUpdateFlags = 0;
    s->m_numVertexShaderBuilders = 0;
    s->m_vertexShaderBuilders = 0;
    s->m_pixelShaderUpdateFlags = 0;
    s->m_numPixelShaderBuilders = 0;
    s->m_pixelShaderBuilders = 0;
    s->m_next = 0;
    ShaderManagerRegister(id, s);
    return s;
}

// ===========================================================================
// @ 0x011f44f0
int Shader::CheckShaderVersionSupport()
{
    u32 vsMin;
    if (m_minVSVersionSupported <= 0)
        vsMin = 0;
    else
        vsMin = m_minVSVersionSupported | 0xfffe0000u;
    D3DCAPS9* caps = DevCapsManager_GetD3DCAPS9();
    u32 vsCaps = caps->VertexShaderVersion;
    if (vsMin > vsCaps)
        return 0;
    u32 vsMax;
    if (m_maxVSVersionSupported <= 0)
        vsMax = 0;
    else
        vsMax = m_maxVSVersionSupported | 0xfffe0000u;
    if (vsCaps < vsMax)
        m_maxVSVersionSupported = _byteswap_ushort((u16)vsCaps);
    u32 psMin;
    if (m_minPSVersionSupported <= 0)
        psMin = 0;
    else
        psMin = m_minPSVersionSupported | 0xffff0000u;
    u32 psCaps = caps->PixelShaderVersion;
    if (psMin > psCaps)
        return 0;
    u32 psMax;
    if (m_maxPSVersionSupported <= 0)
        psMax = 0;
    else
        psMax = m_maxPSVersionSupported | 0xffff0000u;
    if (psCaps < psMax)
        m_maxPSVersionSupported = _byteswap_ushort((u16)psCaps);
    return 1;
}

// ===========================================================================
// @ 0x011f45a0
void __cdecl ReleaseDefaultShader()
{
    if (--g_defaultShader.m_refCount == 0) {
        UnregisterShader(g_defaultShader.m_id);
        g_defaultShader.m_id = 0;
        g_defaultShader.m_next = 0;
    }
}

// ===========================================================================
// @ 0x011f45d0
Shader* __cdecl GetDefaultShader()
{
    u32 id = g_defaultShader.m_id;
    if (id == 0) {
        ShaderConstruct(&g_defaultShader, 0x80000000u, 0xffffffffu, 0, 0xffffff,
                        0xfffe0101, 0xfffe0300, 0xffff0000, 0xffff0300);
        g_defaultShader.m_dispatchCB = (void*)&ShaderCleanup;
        return &g_defaultShader;
    }
    g_defaultShader.m_refCount++;
    return &g_defaultShader;
}

// ===========================================================================
// @ 0x011f4e70
void __cdecl RegisterArenaReadCallbacks()
{
    void* t = ArenaTypeRegGetType(0x20006);
    *(void**)((char*)t + 0xc) = (void*)&FUN_012057f0;
    *(u32*)((char*)t + 0x10) = 0;
}

// ===========================================================================
// @ 0x011f4630
void __cdecl InitShaderTable()
{
    for (u32* p = (u32*)g_shaderDefs; p != (u32*)((char*)g_shaderDefs + 0x10000); ++p) {
        *p = 0;
    }

    g_shaderDefs[3].p10 = (u32)&FUN_011fb220;
    g_shaderDefs[3].p14 = (u32)&FUN_011fb220;
    g_shaderDefs[3].p18 = (u32)&FUN_011fb220;
    g_shaderDefs[3].p1c = 0;
    g_shaderDefs[3].m_id = 3;
    g_shaderDefs[3].f04 = 0;
    g_shaderDefs[3].f08 = 0;
    g_shaderDefs[3].f09 = 0;

    g_shaderDefs[4].p10 = (u32)&FUN_011fb1c0;
    g_shaderDefs[4].p14 = (u32)&FUN_011fb1f0;
    g_shaderDefs[4].p18 = (u32)&FUN_011fb1f0;
    g_shaderDefs[4].p1c = (u32)&FUN_011fa370;
    g_shaderDefs[4].m_id = 4;
    g_shaderDefs[4].f04 = 0;
    g_shaderDefs[4].f08 = 0;
    g_shaderDefs[4].f09 = 0;

    g_shaderDefs[5].p10 = (u32)&FUN_011fb220;
    g_shaderDefs[5].p14 = (u32)&FUN_011fb220;
    g_shaderDefs[5].p18 = (u32)&FUN_011fb220;
    g_shaderDefs[5].m_id = 5;
    g_shaderDefs[5].f04 = 0;
    g_shaderDefs[5].f08 = 0;
    g_shaderDefs[5].f09 = 0;
    g_shaderDefs[5].p1c = (u32)&FUN_011fa310;

    static const u32 kP1c[40] = {
        (u32)&FUN_011fa310, (u32)&FUN_011fa630, (u32)&FUN_011fa4f0, (u32)&FUN_011fa5a0,
        (u32)&FUN_011fa480, (u32)&FUN_011fa6d0, (u32)&FUN_011fa8c0, (u32)&FUN_011fa8f0,
        (u32)&FUN_011fa920, (u32)&FUN_011fa9d0, (u32)&FUN_011faa50, (u32)&FUN_011faa80,
        (u32)&FUN_011fbea0, (u32)&FUN_011fab10, (u32)&FUN_011fab60, (u32)&FUN_011fbea0,
        (u32)&FUN_011fab90, (u32)&FUN_011fbf50, (u32)&FUN_011fcbc0, (u32)&FUN_011fac30,
        (u32)&FUN_011fc040, (u32)&FUN_011fc120, (u32)&FUN_011fad70, (u32)&FUN_011fc200,
        (u32)&FUN_011face0, (u32)&FUN_011fc3d0, (u32)&FUN_011fae40, (u32)&FUN_011fcc70,
        (u32)&FUN_011faea0, (u32)&FUN_011faf00, (u32)&FUN_011faf30, (u32)&FUN_011faf60,
        (u32)&FUN_011fc470, (u32)&FUN_011faf90, (u32)&FUN_011fb030, (u32)&FUN_011fb0f0,
        (u32)&FUN_011fbce0, (u32)&FUN_011fbda0, (u32)&FUN_011fbbf0, (u32)&FUN_011fa410,
    };
    for (int i = 6; i <= 44; ++i) {
        ShaderDef* e = &g_shaderDefs[i];
        e->p10 = 0;
        e->p14 = 0;
        e->p18 = 0;
        e->m_id = (u16)i;
        e->f04 = 0;
        e->f08 = 0;
        e->f09 = 0;
        e->p1c = kP1c[i - 5];
    }

    GetDefaultShader();
}

// ===========================================================================
// @ 0x011f3f20
extern float g_view[16];              // 0x16f8b10
extern float g_proj[16];              // 0x16f90d0
extern float g_world[16];             // 0x16f8be0
extern float g_worldT[16];            // 0x16f8c70
extern D3DVIEWPORT9 g_savedViewport;  // 0x16f9198
extern Camera* g_currentCamera;       // 0x16fa5b8
extern void* g_d3dDevice;             // 0x16f89d0
extern float g_epsilon;               // 0x14f7514

typedef void (__stdcall* PFN_SetTransform)(void* self, u32 state, const void* m);
typedef int  (__stdcall* PFN_SetViewport)(void* self, const void* vp);

int Camera::Check()
{
    FUN_011f3ab0();
    g_view[0] = -g_view[0];
    g_view[4] = -g_view[4];
    g_view[3] = 0.0f;
    g_view[7] = 0.0f;
    g_view[8] = -g_view[8];
    g_view[11] = 0.0f;
    g_view[12] = -g_view[12];
    g_view[15] = 1.0f;

    void* dev = g_d3dDevice;
    void** vt = *(void***)dev;
    ((PFN_SetTransform)vt[0xb0 / 4])(dev, 2, g_view);

    g_proj[0] = m_recipViewWindow[0];
    g_proj[5] = m_recipViewWindow[1];
    g_proj[8] = m_viewOffset[0] * m_recipViewWindow[0];
    g_proj[9] = m_viewOffset[1] * m_recipViewWindow[1];
    g_proj[12] = -g_proj[8];
    g_proj[13] = -g_proj[9];

    float zscale;
    if (m_projectionType == 2) {
        zscale = 1.0f / (m_farPlane - m_nearPlane);
        g_proj[11] = 0.0f;
        g_proj[15] = 1.0f;
    } else {
        if (m_projectionType == 3)
            zscale = 1.0f;
        else
            zscale = m_farPlane / (m_farPlane - m_nearPlane);
        g_proj[11] = 1.0f;
        g_proj[15] = 0.0f;
    }
    g_proj[10] = zscale;
    g_proj[14] = -m_nearPlane * zscale;
    ((PFN_SetTransform)vt[0xb0 / 4])(dev, 3, g_proj);

    D3DXMatrixMultiply(g_world, g_view, g_proj);
    D3DXMatrixTranspose(g_worldT, g_world);
    g_softState |= 0x4000;
    FUN_011f39b0();

    if (g_savedViewport.X == m_viewport.X &&
        g_savedViewport.Y == m_viewport.Y &&
        g_savedViewport.Width == m_viewport.Width &&
        g_savedViewport.Height == m_viewport.Height) {
        float dz = g_savedViewport.MinZ - m_viewport.MinZ;
        *(int*)&dz &= 0x7fffffff;
        if (dz <= g_epsilon) {
            float dw = g_savedViewport.MaxZ - m_viewport.MaxZ;
            *(int*)&dw &= 0x7fffffff;
            if (dw <= g_epsilon) {
                g_currentCamera = this;
                return 1;
            }
        }
    }

    g_savedViewport.X = m_viewport.X;
    g_savedViewport.Y = m_viewport.Y;
    g_savedViewport.Width = m_viewport.Width;
    g_savedViewport.Height = m_viewport.Height;
    g_savedViewport.MinZ = m_viewport.MinZ;
    g_savedViewport.MaxZ = m_viewport.MaxZ;

    if (((PFN_SetViewport)vt[0xbc / 4])(dev, &m_viewport) >= 0) {
        g_currentCamera = this;
        return 1;
    }
    return 0;
}
