// slice s011f6d10 -- RenderWare 4 D3D9 graphics (rwgdrvgraph/D3D9 vertex-shader subsystem).
// The rwg_D3D9 HLSL vertex-shader source generators, the vertex-shader cache
// (GetGeneratedVertexShader / BinaryFindVertexShader / vertex-shader state save+restore),
// plus the pixel-shader GetGenerated wrapper that sits in this address range.
//
// Module flags: /vc71 /O2 /MD /Gy /EHsc /TP  (RenderWare 4 core: VC .NET 2003 / cl 13.10).
// These are RenderWare 4 core functions: single-object codegen cannot reproduce the /LTCG
// cross-call register allocation, so byte-exactness is not the goal here (equivalence only).
#include "types.h"
#include <stdio.h>
#include <string.h>

typedef unsigned char  byte;
typedef unsigned short u16;

static int ByteCmp(const byte* a, const byte* b, unsigned n) {
    for (unsigned k = 0; k < n; ++k)
        if (a[k] != b[k]) return a[k] < b[k] ? -1 : 1;
    return 0;
}

static int StrCmp(const byte* a, const byte* b) {
    while (*a != 0 && *a == *b) { ++a; ++b; }
    return (int)*a - (int)*b;
}

// ---------------------------------------------------------------------------
// D3D9 COM device access (calls go through the active device's vtable)
// ---------------------------------------------------------------------------
extern void* g_d3d9Device;        // 0x016f89d0 IDirect3DDevice9*
static inline void* VSlot(void* obj, int byteOff) {
    return ((void**)(*(void***)obj))[byteOff / 4];
}
typedef void  (__stdcall* PFN_Release)(void*);
typedef long  (__stdcall* PFN_SetVertexShader)(void*, const void*);
typedef long  (__stdcall* PFN_SetPixelShader)(void*, const void*);
typedef long  (__stdcall* PFN_CreateVertexShader)(void*, const void*, void**);
typedef void* (__stdcall* PFN_GetBufferPointer)(void*);

// ---------------------------------------------------------------------------
// Pixel-shader cache (reused by the pixel GetGenerated wrapper in this slice)
// ---------------------------------------------------------------------------
extern byte     g_psTable[];      // 0x0170a898 D3D9PixelShaderDefs (stride 0x44)
extern unsigned g_psCount;        // 0x0170ed54
extern byte*    g_psCurrent;      // 0x0170ed58
extern unsigned g_16f8cf8;        // 0x016f8cf8 timestamp/counter
extern byte     g_170ec98[];      // 0x0170ec98 default pixel-shader key (0x11 + 0x20)
extern byte     g_170eca9[];      // 0x0170eca9 default pixel-shader name
extern void*    g_pixelShader;    // 0x016f89cc m_pixelShader

// ---------------------------------------------------------------------------
// Vertex-shader cache + active state
// ---------------------------------------------------------------------------
extern byte     g_vsTable[];      // 0x0170eef0 D3D9VertexShaderDefs (stride 0x30)
extern unsigned g_1711ef4;        // 0x01711ef4 vertex-shader count
extern byte*    g_1711ef8;        // 0x01711ef8 current vertex-shader descriptor
extern void*    g_1711ef0;        // 0x01711ef0 saved vertex shader
extern void*    g_vertexShader;   // 0x016f6564 m_vertexShader (active)
extern void*    g_16f6568;        // 0x016f6568 m_shader (active shader)
extern unsigned g_16f8cfc;        // 0x016f8cfc m_shaderFlags
extern unsigned g_16f9110;        // 0x016f9110 m_softStateUpdated

// vertex attribute tables (save/restore helpers FUN_011f7850/7870/78b0)
extern byte     g_170ee48[];      // 0x0170ee48 active attribute names
extern unsigned g_170ee68[];      // 0x0170ee68 active attribute values
extern unsigned g_170eee8;        // 0x0170eee8 active attribute count
extern byte     g_1711f00[];      // 0x01711f00 saved attribute names
extern unsigned g_1711f20[];      // 0x01711f20 saved attribute values
extern unsigned g_1711fa0;        // 0x01711fa0 saved attribute count
extern unsigned g_1711efc;        // 0x01711efc
extern byte     g_171be38[];      // 0x0171be38 attribute -> register offset table

// vertex-shader effect definitions + texcoord info
extern byte     g_vsEffectDefs[];         // 0x0171a538 D3D9VertexShaderEffectDefs (stride 0x10)
extern byte     g_vsEffectTexCoords[];    // 0x0171bd38 D3D9VertexShaderEffectTexCoords
extern byte     g_vsEffectTexCoordDims[]; // 0x0171bf38 ...TexCoordsDimensions
extern char     g_vsHlslBuffer[];         // 0x0171c0c0 D3D9HLSLTextBuffer
extern const char* g_vsMainFmt;           // 0x015d07dc -> "VS_OUT main( VS_IN In )\n{\n..."
extern const char* g_vsRetFmt;            // 0x015d07d8 -> "\nreturn Out;\n}\n"

// effect callbacks
typedef char* (__cdecl* VSFnGen)(char* dest, int effect, int ctx);
typedef char* (__cdecl* VSFnDump)(char* dest, int effect, int texCount);

// ---- callees -----------------------------------------------------------------
char* __cdecl D3D9TextCopy(char* dst, const char* src);                                  // 0x011fd6d0
int   __cdecl FUN_011f6660(const byte* pName, const byte* pKey, int table, unsigned n);  // 0x011f6660
char* __cdecl FUN_011f69a0(int desc);                                                    // 0x011f69a0
void  __fastcall FUN_011f6f20(int unused, byte* p);                                      // 0x011f6f20
void  __cdecl FUN_011fce20(void* a, void* b);                                            // 0x011fce20
int*  __cdecl FUN_011f8af0(void);                                                        // 0x011f8af0 DevCapsManager::GetD3DCAPS9
int   __cdecl FUN_011e1fd4(const char* src, int len, void* defs, void* inc,
                           const char* fn, const char* profile, int flags,
                           void** ppShader, void** ppErr, void* ppConst);                // 0x011e1fd4

// ===========================================================================
// @ 0x011f6d10  rw::graphics::(anonymous)::rwg_D3D9GetGeneratedPixelShader
// ===========================================================================
int FUN_011f6d10(void* param_1)
{
    int found = FUN_011f6660((const byte*)param_1, (const byte*)((byte*)param_1 + 0x11),
                             (int)g_psTable, g_psCount);
    if (found >= 0) {
        byte* entry = g_psTable + found * 0x44;
        g_psCurrent = entry;
        *(unsigned*)(entry + 0x38) = g_16f8cf8;
        return *(int*)(entry + 0x34);
    }
    int shader = (int)FUN_011f69a0((int)param_1);
    if (shader == 0)
        return 0;
    byte* cur;
    if (g_psCount < 0x100) {
        int i = -1 - found;
        if (i < (int)g_psCount)
            memmove(g_psTable + 0x44 + i * 0x44, g_psTable + i * 0x44, (g_psCount - i) * 0x44);
        cur = g_psTable + i * 0x44;
        g_psCount = g_psCount + 1;
        g_psCurrent = cur;
    } else {
        cur = g_psTable;
        g_psCurrent = g_psTable;
        if (g_psCount > 1) {
            byte* p = g_psTable + 0x44;
            for (unsigned i = g_psCount - 1; i; --i) {
                if (*(unsigned*)(p + 0x38) < *(unsigned*)(cur + 0x38)) {
                    cur = p;
                    g_psCurrent = p;
                }
                p += 0x44;
            }
        }
        if (*(void**)(cur + 0x34) != 0) {
            if (*(unsigned*)(cur + 0x3c) == 0) {
                void* obj = *(void**)(cur + 0x34);
                (*(PFN_Release)VSlot(obj, 8))(obj);
                cur = g_psCurrent;
            }
            *(void**)(cur + 0x34) = 0;
            cur = g_psCurrent;
        }
    }
    *(unsigned*)(cur + 0x00) = *(unsigned*)((byte*)param_1 + 0x00);
    *(unsigned*)(cur + 0x04) = *(unsigned*)((byte*)param_1 + 0x04);
    *(unsigned*)(cur + 0x08) = *(unsigned*)((byte*)param_1 + 0x08);
    *(unsigned*)(cur + 0x0c) = *(unsigned*)((byte*)param_1 + 0x0c);
    *(byte*)(cur + 0x10) = *(byte*)((byte*)param_1 + 0x10);
    memcpy(cur + 0x11, (byte*)param_1 + 0x11, 0x20);
    byte* e = g_psCurrent;
    *(int*)(e + 0x34) = shader;
    *(unsigned*)(e + 0x38) = g_16f8cf8;
    *(unsigned*)(e + 0x3c) = 0;
    *(unsigned*)(e + 0x40) = 0;
    return shader;
}

// ===========================================================================
// @ 0x011f6e80  rw::graphics::(anonymous)::D3D9PixelShaderDescriptor::DefaultLoadAndSelect
// ===========================================================================
void FUN_011f6e80(void)
{
    int sel;
    if (StrCmp(g_psCurrent + 0x11, g_170eca9) == 0 &&
        ByteCmp(g_psCurrent, g_170ec98, 0x11) == 0) {
        *(unsigned*)(g_psCurrent + 0x38) = g_16f8cf8;
        sel = *(int*)(g_psCurrent + 0x34);
    } else {
        sel = FUN_011f6d10(&g_170ec98);
    }
    if (g_pixelShader != (void*)sel) {
        void* dev = g_d3d9Device;
        (*(PFN_SetPixelShader)VSlot(dev, 0x1ac))(dev, (void*)sel);
        g_pixelShader = (void*)sel;
    }
}

// ===========================================================================
// @ 0x011f6f20  (fastcall: edx = attribute table); fills p+0x20 with offsets
// ===========================================================================
void __fastcall FUN_011f6f20(int unused, byte* param_2)
{
    (void)unused;
    byte b = *param_2;
    int prev = 4;
    int* out = (int*)(param_2 + 0x20);
    const byte* q = param_2 + 1;
    do {
        byte t = g_171be38[b];
        int val = 0;
        if (t != 0) {
            val = prev;
            prev += t;
        }
        *out = val;
        b = *q++;
        ++out;
    } while (b > 0);
}

// ===========================================================================
// @ 0x011f6f60  rw::graphics::(anonymous)::rwg_D3D9GenerateInputStruct
// ===========================================================================
char* FUN_011f6f60(char* dst, unsigned mask)
{
    char* p = D3D9TextCopy(dst, "\nstruct VS_IN\n{\n");
    if ((mask & 3) != 0)
        p = D3D9TextCopy(p, "float4 position :POSITION0;\n");
    if ((mask & 4) != 0)
        p = D3D9TextCopy(p, "float4 normal :NORMAL0;\n");
    if ((mask & 0x18) != 0)
        p = D3D9TextCopy(p, "float4 color :COLOR0;\n");
    unsigned i = 0;
    do {
        if ((mask & (1u << (i + 6))) == 0)
            break;
        p += sprintf(p, "float4 texcoord%d :TEXCOORD%d;\n", i, i);
        ++i;
    } while (i < 8);
    if ((mask & 0x4000) != 0)
        p = D3D9TextCopy(p, "int4 indices :BLENDINDICES0;\n");
    if ((mask & 0x8000u) != 0)
        p = D3D9TextCopy(p, "float4 weights :BLENDWEIGHT0;\n");
    if ((mask & 0x20000) != 0)
        p = D3D9TextCopy(p, "float4 position2 :POSITION1;\n");
    if ((mask & 0x40000) != 0)
        p = D3D9TextCopy(p, "float4 normal2 :NORMAL1;\n");
    if ((mask & 0x400000) != 0)
        p = D3D9TextCopy(p, "int4 indices2 :BLENDINDICES1;\n");
    if ((mask & 0x800000) != 0)
        p = D3D9TextCopy(p, "float4 weights2 :BLENDWEIGHT1;\n");
    if ((mask & 0x80000) != 0)
        p = D3D9TextCopy(p, "float4 tangent :TANGENT0;\n");
    if ((mask & 0x100000) != 0)
        p = D3D9TextCopy(p, "float4 binormal :BINORMAL0;\n");
    if ((mask & 0x20) != 0)
        p = D3D9TextCopy(p, "float3 specular :COLOR1;\n");
    if ((mask & 0x200000) != 0)
        p = D3D9TextCopy(p, "float fog :COLOR1;\n");
    if ((mask & 0x10000) != 0)
        p = D3D9TextCopy(p, "float pointSize :PSIZE;\n");
    return D3D9TextCopy(p, "};\n\n");
}

// ===========================================================================
// @ 0x011f7100  rw::graphics::(anonymous)::rwg_D3D9GenerateCurrentStruct
// ===========================================================================
char* FUN_011f7100(char* dst, unsigned mask, unsigned texCount, const byte* texDims)
{
    char* p = D3D9TextCopy(dst, "struct VS_CURRENT\n{\n");
    p = D3D9TextCopy(p, "float4 position;\n");
    if ((mask & 4) != 0)
        p = D3D9TextCopy(p, "float4 normal;\n");
    if ((mask & 0x18) != 0)
        p = D3D9TextCopy(p, "float4 color;\n");
    for (unsigned i = 0; i < texCount; ++i)
        p += sprintf(p, "float%d texcoord%d;\n", (unsigned)texDims[i], i);
    if ((mask & 0x4000) != 0)
        p = D3D9TextCopy(p, "int4 indices;\n");
    if ((mask & 0x8000u) != 0)
        p = D3D9TextCopy(p, "float4 weights;\n");
    if ((mask & 0x20000) != 0)
        p = D3D9TextCopy(p, "float4 position2;\n");
    if ((mask & 0x40000) != 0)
        p = D3D9TextCopy(p, "float4 normal2;\n");
    if ((mask & 0x400000) != 0)
        p = D3D9TextCopy(p, "int4 indices2;\n");
    if ((mask & 0x800000) != 0)
        p = D3D9TextCopy(p, "float4 weights2;\n");
    if ((mask & 0x80000) != 0)
        p = D3D9TextCopy(p, "float4 tangent;\n");
    if ((mask & 0x100000) != 0)
        p = D3D9TextCopy(p, "float4 binormal;\n");
    if ((mask & 0x20) != 0)
        p = D3D9TextCopy(p, "float3 specular;\n");
    if ((mask & 0x200000) != 0)
        p = D3D9TextCopy(p, "float fog;\n");
    if ((mask & 0x10000) != 0)
        p = D3D9TextCopy(p, "float pointSize;\n");
    return D3D9TextCopy(p, "};\n\n");
}

// ===========================================================================
// @ 0x011f72a0  rw::graphics::(anonymous)::rwg_D3D9GenerateOutputStruct
// ===========================================================================
char* FUN_011f72a0(char* dst, unsigned mask, unsigned texCount, const byte* texDims)
{
    char* p = D3D9TextCopy(dst, "struct VS_OUT\n{\n");
    p = D3D9TextCopy(p, "float4 position :POSITION;\n");
    if ((mask & 0x18) != 0)
        p = D3D9TextCopy(p, "float4 diffuse :COLOR0;\n");
    for (unsigned i = 0; i < texCount; ++i)
        p += sprintf(p, "float%d texcoord%d :TEXCOORD%d;\n", (unsigned)texDims[i], i, i);
    if ((mask & 0x20) != 0) {
        if ((mask & 0x200000) != 0) {
            if ((*(unsigned*)((byte*)FUN_011f8af0() + 0xcc)) <= 0xffff0000u) {
                p = D3D9TextCopy(p, "float3 specular :COLOR1;\n");
                p = D3D9TextCopy(p, "float fog :FOG;\n");
            } else {
                p = D3D9TextCopy(p, "float4 specularAndFog :COLOR1;\n");
            }
        } else {
            p = D3D9TextCopy(p, "float3 specular :COLOR1;\n");
        }
    } else if ((mask & 0x200000) != 0) {
        if ((*(unsigned*)((byte*)FUN_011f8af0() + 0xcc)) <= 0xffff0000u)
            p = D3D9TextCopy(p, "float fog :FOG;\n");
        else
            p = D3D9TextCopy(p, "float4 fog :COLOR1;\n");
    }
done:
    if ((mask & 0x10000) != 0)
        p = D3D9TextCopy(p, "float pointSize :PSIZE;\n");
    return D3D9TextCopy(p, "};\n\n");
}

// ===========================================================================
// @ 0x011f73c0  rw::graphics::(anonymous)::rwg_D3D9GenerateDumpCurrent
// ===========================================================================
char* FUN_011f73c0(char* dst, unsigned mask)
{
    char* p;
    if ((mask & 3) != 0)
        p = D3D9TextCopy(dst, "Current.position = In.position;\n");
    else
        p = dst;
    if ((mask & 4) != 0)
        p = D3D9TextCopy(p, "Current.normal = In.normal;\n");
    if ((mask & 0x18) != 0)
        p = D3D9TextCopy(p, "Current.color = In.color;\n");
    unsigned i = 0;
    do {
        if ((mask & (1u << (i + 6))) == 0)
            break;
        p += sprintf(p, "Current.texcoord%d = In.texcoord%d;\n", i, i);
        ++i;
    } while (i < 8);
    if ((mask & 0x4000) != 0)
        p = D3D9TextCopy(p, "Current.indices = In.indices;\n");
    if ((mask & 0x8000u) != 0)
        p = D3D9TextCopy(p, "Current.weights = In.weights;\n");
    if ((mask & 0x20000) != 0)
        p = D3D9TextCopy(p, "Current.position2 = In.position2;\n");
    if ((mask & 0x40000) != 0)
        p = D3D9TextCopy(p, "Current.normal2 = In.normal2;\n");
    if ((mask & 0x400000) != 0)
        p = D3D9TextCopy(p, "Current.indices2 = In.indices2;\n");
    if ((mask & 0x800000) != 0)
        p = D3D9TextCopy(p, "Current.weights2 = In.weights2;\n");
    if ((mask & 0x80000) != 0)
        p = D3D9TextCopy(p, "Current.tangent = In.tangent;\n");
    if ((mask & 0x100000) != 0)
        p = D3D9TextCopy(p, "Current.binormal = In.binormal;\n");
    if ((mask & 0x20) != 0)
        p = D3D9TextCopy(p, "Current.specular = In.specular;\n");
    if ((mask & 0x200000) != 0)
        p = D3D9TextCopy(p, "Current.fog = In.fog;\n");
    if ((mask & 0x10000) != 0)
        p = D3D9TextCopy(p, "Current.pointSize = In.pointSize;\n");
    return p;
}

// ===========================================================================
// @ 0x011f7550  rw::graphics::(anonymous)::rwg_D3D9GenerateDumpOutput
// ===========================================================================
char* FUN_011f7550(char* dst, unsigned mask, unsigned texCount)
{
    char* p = D3D9TextCopy(dst, "\n");
    p = D3D9TextCopy(p, "Out.position = Current.position;\n");
    if ((mask & 0x18) != 0)
        p = D3D9TextCopy(p, "Out.diffuse = Current.color;\n");
    for (unsigned i = 0; i < texCount; ++i)
        p += sprintf(p, "Out.texcoord%d = Current.texcoord%d;\n", i, i);
    if ((mask & 0x20) != 0) {
        if ((mask & 0x200000) != 0) {
            if ((*(unsigned*)((byte*)FUN_011f8af0() + 0xcc)) <= 0xffff0000u) {
                p = D3D9TextCopy(p, "Out.specular = Current.specular;\n");
                p = D3D9TextCopy(p, "Out.fog = Current.fog;\n");
            } else {
                p = D3D9TextCopy(p, "Out.specularAndFog.xyz = Current.specular;\n");
                p = D3D9TextCopy(p, "Out.specularAndFog.w = Current.fog;\n");
            }
        } else {
            p = D3D9TextCopy(p, "Out.specular = Current.specular;\n");
        }
    } else if ((mask & 0x200000) != 0) {
        p = D3D9TextCopy(p, "Out.fog = Current.fog;\n");
    }
done:
    if ((mask & 0x10000) != 0)
        p = D3D9TextCopy(p, "Out.pointSize = Current.pointSize;\n");
    return p;
}

// ===========================================================================
// @ 0x011f7650  rw::graphics::(anonymous)::rwg_D3D9BinaryFindVertexShader
// LTCG internal convention: ecx = table base, eax = entry count, stack = key.
// ===========================================================================
int __fastcall FUN_011f7650(int table, unsigned count, const byte* key)
{
    int lo = 0;
    unsigned n = count;
    if (n == 0)
        return -1 - lo;
    int hi = (int)n - 1;
    do {
        if (n < 2) {
            const byte* e = (const byte*)(table + lo * 0x30);
            if (StrCmp(key, e) == 0)
                return lo;
            if (StrCmp(key, e) >= 0)
                return -2 - lo;
            return -1 - lo;
        }
        int mid = (int)(n >> 1) + (int)(n & 1) + lo - 1;
        const byte* e = (const byte*)(table + mid * 0x30);
        if (StrCmp(key, e) == 0)
            return mid;
        if (StrCmp(key, e) < 0)
            hi = mid - 1;
        else
            lo = mid + 1;
        n = (unsigned)(hi - lo + 1);
    } while (n != 0);
    return -1 - lo;
}

// ===========================================================================
// @ 0x011f77d0  (vertex-shader save)
// ===========================================================================
void FUN_011f77d0(void)
{
    g_1711ef0 = g_vertexShader;
    if (g_vertexShader != 0) {
        void* dev = g_d3d9Device;
        (*(PFN_SetVertexShader)VSlot(dev, 0x170))(dev, 0);
        g_vertexShader = 0;
    }
}

// ===========================================================================
// @ 0x011f7800  (vertex-shader restore)
// ===========================================================================
void FUN_011f7800(void)
{
    void* p = g_1711ef0;
    if (p != 0 && g_vertexShader != p) {
        (*(PFN_SetVertexShader)VSlot(g_d3d9Device, 0x170))(g_d3d9Device, p);
        g_vertexShader = p;
    }
}

// ===========================================================================
// @ 0x011f7830  rw::graphics::D3D9VertexShaderChange
// ===========================================================================
void FUN_011f7830(int param_1)
{
    g_16f6568 = (void*)param_1;
    g_16f8cfc = *(unsigned*)(param_1 + 4);
    g_16f9110 |= 4;
}

// ===========================================================================
// @ 0x011f7850
// ===========================================================================
void FUN_011f7850(void)
{
    g_1711f00[0] = 0;
    g_1711fa0 = 0;
    g_170ee48[0] = 0;
    g_170eee8 = 0;
}

// ===========================================================================
// @ 0x011f7870
// ===========================================================================
void FUN_011f7870(void)
{
    g_1711efc = 0;
    byte b = 0;
    unsigned char c;
    do {
        c = (unsigned char)g_170ee48[b];
        unsigned v = g_170ee68[b];
        g_1711f00[b] = (byte)c;
        g_1711f20[b] = v;
        ++b;
    } while (c > 0);
    g_1711fa0 = g_170eee8;
}

// ===========================================================================
// @ 0x011f78b0
// ===========================================================================
void FUN_011f78b0(void)
{
    FUN_011f6f20(0, g_170ee48);
    FUN_011fce20(g_170ee48, g_1711f00);
}

// ===========================================================================
// @ 0x011f78d0  rw::graphics::(anonymous)::rwg_D3D9GenerateVertexShader
// ===========================================================================
char* FUN_011f78d0(int param_1)
{
    char* dest = g_vsHlslBuffer;
    unsigned outMask = 0;
    unsigned inMask = 0;
    unsigned texCount = 0;
    byte texBuf[0x20];

    for (unsigned idx = 0; idx < 0x20; ++idx) {
        unsigned e = *(byte*)(param_1 + idx);
        if (e == 0)
            break;
        unsigned off = e * 0x10;
        outMask |= *(unsigned*)(g_vsEffectDefs + off + 4);
        inMask  |= *(unsigned*)(g_vsEffectDefs + off + 0);
        if (*(VSFnGen*)(g_vsEffectDefs + off + 8) != 0)
            dest = (*(VSFnGen*)(g_vsEffectDefs + off + 8))(dest, (int)e, *(int*)(param_1 + 0x20 + idx * 4));
        unsigned n = g_vsEffectTexCoords[e];
        if (n != 0) {
            byte dim = g_vsEffectTexCoordDims[e];
            byte* bp = texBuf + texCount;
            unsigned q = n >> 2;
            for (; q; --q) { *(unsigned*)bp = dim * 0x01010101u; bp += 4; }
            for (q = n & 3; q; --q) { *bp++ = dim; }
            texCount += n;
        }
    }

    dest = (char*)FUN_011f6f60(dest, inMask);
    dest = (char*)FUN_011f7100(dest, outMask | inMask, texCount, texBuf);
    dest = (char*)FUN_011f72a0(dest, outMask, texCount, texBuf);
    dest = D3D9TextCopy(dest, g_vsMainFmt);
    dest = (char*)FUN_011f73c0(dest, inMask);

    texCount = 0;
    for (unsigned idx = 0; idx < 0x20; ++idx) {
        unsigned e = *(byte*)(param_1 + idx);
        if (e == 0)
            break;
        if (*(VSFnDump*)(g_vsEffectDefs + e * 0x10 + 0xc) != 0)
            dest = (*(VSFnDump*)(g_vsEffectDefs + e * 0x10 + 0xc))(dest, (int)e, (int)texCount);
        texCount += g_vsEffectTexCoords[e];
    }
    dest = (char*)FUN_011f7550(dest, outMask, texCount);
    dest = D3D9TextCopy(dest, g_vsRetFmt);
    *dest = 0;

    unsigned v = *(unsigned short*)((byte*)g_16f6568 + 0xe);
    unsigned u = (v == 0) ? 0 : (v | 0xfffe0000u);
    const char* profile = 0;
    if (u == 0xfffe0101) profile = "vs_1_1";
    else if (u == 0xfffe0200) profile = "vs_2_0";
    else if (u == 0xfffe0261) profile = "vs_2_a";
    else if (u == 0xfffe0300) profile = "vs_3_0";

    void* shaderBuf = 0;
    void* errBuf = 0;
    int hr = FUN_011e1fd4(g_vsHlslBuffer, (int)(dest - g_vsHlslBuffer), 0, 0,
                          "main", profile, 2, &shaderBuf, &errBuf, 0);
    if (hr < 0)
        return 0;
    if (errBuf != 0)
        (*(PFN_Release)VSlot(errBuf, 8))(errBuf);
    void* dev = g_d3d9Device;
    void* bytecode = ((PFN_GetBufferPointer)VSlot(shaderBuf, 0xc))(shaderBuf);
    void* handle = 0;
    (*(PFN_CreateVertexShader)VSlot(dev, 0x16c))(dev, bytecode, &handle);
    (*(PFN_Release)VSlot(shaderBuf, 8))(shaderBuf);
    return (char*)handle;
}

// ===========================================================================
// @ 0x011f7b20  rw::graphics::(anonymous)::rwg_D3D9GetGeneratedVertexShader
// ===========================================================================
int FUN_011f7b20(void* param_1)
{
    int found = FUN_011f7650((int)g_vsTable, g_1711ef4, (const byte*)param_1);
    if (found >= 0) {
        byte* entry = g_vsTable + found * 0x30;
        g_1711ef8 = entry;
        *(unsigned*)(entry + 0x24) = g_16f8cf8;
        return *(int*)(entry + 0x20);
    }
    int shader = (int)FUN_011f78d0((int)param_1);
    if (shader == 0)
        return 0;
    byte* cur;
    if (g_1711ef4 < 0x100) {
        int i = -1 - found;
        if (i < (int)g_1711ef4)
            memmove(g_vsTable + 0x30 + i * 0x30, g_vsTable + i * 0x30, (g_1711ef4 - i) * 0x30);
        cur = g_vsTable + i * 0x30;
        g_1711ef4 = g_1711ef4 + 1;
        g_1711ef8 = cur;
    } else {
        cur = g_vsTable;
        g_1711ef8 = g_vsTable;
        if (g_1711ef4 > 1) {
            byte* p = g_vsTable + 0x30;
            for (unsigned i = g_1711ef4 - 1; i; --i) {
                if (*(unsigned*)(p + 0x24) < *(unsigned*)(cur + 0x24)) {
                    cur = p;
                    g_1711ef8 = p;
                }
                p += 0x30;
            }
        }
        if (*(void**)(cur + 0x20) != 0) {
            if (*(unsigned*)(cur + 0x28) == 0) {
                void* obj = *(void**)(cur + 0x20);
                (*(PFN_Release)VSlot(obj, 8))(obj);
                cur = g_1711ef8;
            }
            *(void**)(cur + 0x20) = 0;
            cur = g_1711ef8;
        }
    }
    memcpy(cur, param_1, 0x20);
    byte* e = g_1711ef8;
    *(int*)(e + 0x20) = shader;
    *(unsigned*)(e + 0x24) = g_16f8cf8;
    *(unsigned*)(e + 0x28) = 0;
    *(unsigned*)(e + 0x2c) = 0;
    return shader;
}
