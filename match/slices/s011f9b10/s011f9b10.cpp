// slice s011f9b10 -- RenderWare 4 core: rw::graphics::BuildState resource init + D3D9
// shader-data cache, the global Shader registry, compiled-state arena callbacks, and the
// ActiveState D3D9 shader-constant upload helpers.
//
// This address range (0x011e2000-0x0120bc50) is RenderWare 4 core, built with VC .NET 2003
// (cl 13.10) and /GL + /LTCG.  A single-object compile cannot reproduce /LTCG cross-call
// register allocation, so byte-exactness is not generally achievable here (docs/matching.md,
// "Toolchain provenance").  These are complete behavioural reconstructions; leaf functions
// with no calls may still match under /vc71.
//
// Calling forms:
//   * BuildState methods are __thiscall (this in ecx).
//   * The loose ActiveState helpers are __cdecl free functions; the device is reached through
//     IDirect3DDevice9's vtable (+0x178 SetVertexShaderConstantF, +0x188
//     SetVertexShaderConstantB, +0x1b4 SetPixelShaderConstantF).
//   * 011e1fec / 011e1ff2 are the D3DXMatrixTranspose / D3DXMatrixMultiply import thunks
//     (__stdcall: the callee pops its arguments).
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include <string.h>
#include <malloc.h>
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

// ---- image globals ---------------------------------------------------------
extern void*   g_device;              // 0x016f89d0 IDirect3DDevice9*
extern void*   g_rwAllocFn;           // 0x016f4ae4
extern void*   g_rwFreeFn;            // 0x016f4aec
extern float   g_one;                 // 0x01485720 (1.0f)
extern float*  g_animTime;            // 0x016f65bc
extern u32     g_maxBoolConsts;       // 0x016f65b4
extern void*   g_skinData;            // 0x016f65b8

// ActiveState transform cache
struct Matrix44;
extern void*   g_transform;           // 0x016f85ac Matrix44Affine*
extern i32     g_transformType;       // 0x016f8b50 rw::math::vpu::MatrixType
extern void*   g_transposedTransform; // 0x016f8cf4 Matrix44*
extern Matrix44 g_matrixB10;          // 0x016f8b10 Matrix44
extern Matrix44 g_matrixBE0;          // 0x016f8be0 Matrix44
extern Matrix44 g_matrixC70;          // 0x016f8c70 Matrix44
extern void*   g_matrixPtrA5B8;       // 0x016fa5b8 Matrix44*

// Shader registry (128 hash buckets, chained through Shader::m_next at +0x40)
extern u32     g_shaderCount;         // 0x017186d0
extern void*   g_shaderLast;          // 0x017186d4
extern void*   g_shaderHash[128];     // 0x017186d8

// ---- imported D3DX math helpers (import thunks) ----------------------------
__declspec(dllimport) void __stdcall D3DXMatrixTranspose(void* out, const void* in);              // 0x011e1fec
__declspec(dllimport) void __stdcall D3DXMatrixMultiply(void* out, const void* a, const void* b); // 0x011e1ff2

// ---- callees ---------------------------------------------------------------
struct Shader
{
    void Release();                  // 0x011f4200 rw::graphics::Shader::Release
};
struct Arena
{
    void* IdToObject(u32 id);        // 0x011e2300 rw::core::arena::Arena::IdToObject
};
struct BlockNode
{
    void Free();                     // 0x011ed910
};i32  __cdecl FUN_011ed690(void*, void*);   // 0x011ed690
i32  __cdecl FUN_011f94f0(void*, void*);   // 0x011f94f0
i32  __cdecl ArenaTypeRegGetType(int);     // 0x011e22c0, int __cdecl FUN(int)

struct Matrix44
{
    float xAxis[4];   // +0x00
    float yAxis[4];   // +0x10
    float zAxis[4];   // +0x20
    float wAxis[4];   // +0x30
};

// ======================================================== BuildState (0x1250)
struct D3D9ShaderDataInfo
{
    u32   id;          // +0x00
    void* buffer;      // +0x04
    u16   size;        // +0x08
    u16   alignment;   // +0x0a
    u16   type;        // +0x0c
    i32   behaviour;   // +0x10
};

struct BuildState
{
    u32   m_softStateDirty;             // 0x000
    u32   m_softStateDynamic;           // 0x004
    u32   m_softStateDynamicShared;     // 0x008
    u32   m_softStateExternal;          // 0x00c
    i32   m_transformType;              // 0x010
    void* m_transform;                  // 0x014
    u32   pad018[2];                    // 0x018
    float m_transformLocalCopy[16];     // 0x020
    void* m_shader;                     // 0x060
    float m_color[4];                   // 0x064
    float m_ambient[3];                 // 0x074
    void* m_light[8];                   // 0x080
    u32   m_renderStateDirty[7];        // 0x0a0
    u32   m_renderStateDynamic[7];      // 0x0bc
    u32   m_renderState[210];           // 0x0d8
    u8    m_uvMapping[17];              // 0x420
    u8    pad431[3];                    // 0x431
    u32   m_rasterDirty;                // 0x434
    u32   m_rasterDynamic;              // 0x438
    void* m_raster[17];                 // 0x43c
    u32   m_paletteDirty;               // 0x480
    u32   m_paletteDynamic;             // 0x484
    void* m_palette;                    // 0x488
    u32   m_textureStageStateDirty[17]; // 0x48c
    u32   m_textureStageStateDynamic[17];//0x4d0
    u32   m_textureStageState[17][33];  // 0x514
    u32   m_samplerStateDirty[17];      // 0xdd8
    u32   m_samplerStateDynamic[17];    // 0xe1c
    u32   m_samplerState[17][14];       // 0xe60
    i32   m_fogType;                    // 0x1218
    float m_fogStartDensity;            // 0x121c
    float m_fogEnd;                     // 0x1220
    float m_fogColor[3];                // 0x1224
    i32   m_primType;                   // 0x1230
    void* m_vdesc;                      // 0x1234
    u32   m_maxShaderData;              // 0x1238
    D3D9ShaderDataInfo m_shaderData[1]; // 0x123c

    void Release();
    void D3D9SetRenderState(u32 state, u32 value, i32 behaviour);
    u32  D3D9HasVertexDescriptor() const;
    void D3D9UpdateSoftStateBehaviour(u32 bits, i32 behaviour);
    void D3D9SetShaderData(u32 id, const void* data, u32 size, u32 alignment, i32 type, i32 behaviour);
    void D3D9SetVertexDescriptor(const void* vdesc, i32 behaviour);
};

// Resource descriptor used by rw::Resource allocation (four 8-byte base descriptors).
struct ResourceDesc8
{
    u32 m_size;        // +0x00
    u32 m_alignment;   // +0x04
    u32 m_rest[6];     // +0x08
};

struct ResourceMem
{
    void* mem;         // +0x00 (rw::Resource's first memory-resource pointer)
    u32   rest[3];
};

void* __cdecl BuildStateLookupShader(u32 key);
ResourceDesc8 __cdecl BuildStateGetResourceDescriptor(u32 shader, u32 maxShaderData);
BuildState* __cdecl BuildStateInitialize(ResourceMem* res, u32 shader, u32 maxShaderData);

// 011f9b10 -- drop every raster reference and free the cached shader-data buffers that this
// BuildState owns (external/reference buffers belong to the caller).
// @ 0x011f9b10
void BuildState::Release()
{
    u32 i;
    for (i = 0; i < 17; ++i)
    {
        m_rasterDirty |= 1u << i;
        m_raster[i] = 0;
    }
    for (i = 0; i < m_maxShaderData; ++i)
    {
        D3D9ShaderDataInfo* p = &m_shaderData[i];
        if (p->id != 0 && p->buffer != 0 && p->behaviour != 3 && p->behaviour != 4)
            ((void (__cdecl*)(void*))g_rwFreeFn)(p->buffer);
        p->id = 0;
        p->buffer = 0;
    }
}

// 011f9ba0 -- record a render state value and its behaviour mask.
// @ 0x011f9ba0
void BuildState::D3D9SetRenderState(u32 state, u32 value, i32 behaviour)
{
    u32 slot = (state - 7) >> 5;
    u32 bit = 1u << ((state - 7) & 0x1f);
    m_renderStateDirty[slot] |= bit;
    if (behaviour == 0)
        m_renderStateDynamic[slot] &= ~bit;
    else
        m_renderStateDynamic[slot] |= bit;
    m_renderState[state] = value;
}

// 011f9c40 -- has a vertex descriptor been set?
// @ 0x011f9c40
u32 BuildState::D3D9HasVertexDescriptor() const
{
    return (m_softStateDirty >> 20) & 1;
}

// 011f9c50 -- move a soft-state bit into the mask selected by the behaviour.
// @ 0x011f9c50
void BuildState::D3D9UpdateSoftStateBehaviour(u32 bits, i32 behaviour)
{
    u32 notBits = ~bits;
    m_softStateDynamic &= notBits;
    m_softStateExternal &= notBits;
    m_softStateDynamicShared &= notBits;
    if (behaviour == 1)
        m_softStateDynamic |= bits;
    else if (behaviour == 2)
        m_softStateDynamicShared |= bits;
    else if (behaviour == 3 || behaviour == 4)
        m_softStateExternal |= bits;
}

// 011f9cb0 -- store (and for static/dynamic data, copy) one shader constant block.
// @ 0x011f9cb0
void BuildState::D3D9SetShaderData(u32 id, const void* data, u32 size, u32 alignment,
                                   i32 type, i32 behaviour)
{
    u32 freeIndex = 0xffffffff;
    u32 index = 0;
    if (m_maxShaderData != 0)
    {
        D3D9ShaderDataInfo* p = m_shaderData;
        do
        {
            if (p->id == 0)
            {
                if (index < freeIndex)
                    freeIndex = index;
            }
            else if (p->id == id)
            {
                break;
            }
            ++index;
            ++p;
        } while (index < m_maxShaderData);
    }

    if (index < m_maxShaderData)
    {
        D3D9ShaderDataInfo* p = &m_shaderData[index];
        freeIndex = index;
        if (p->behaviour == 3 || p->behaviour == 4)
        {
            p->buffer = 0;
        }
        else if (behaviour == 3 || behaviour == 4 || p->size < (u16)size)
        {
            ((void (__cdecl*)(void*))g_rwFreeFn)(p->buffer);
            p->buffer = 0;
        }
    }
    else
    {
        index = freeIndex;
    }

    u32 alignedSize = (size + 3) & ~3u;
    m_softStateDirty |= 8;

    D3D9ShaderDataInfo* p = &m_shaderData[index];
    if (behaviour == 3)
    {
        p->buffer = (void*)data;
    }
    else if (behaviour == 4)
    {
        p->buffer = 0;
    }
    else
    {
        if (p->buffer == 0)
            p->buffer = ((void* (__cdecl*)(u32, u32))g_rwAllocFn)(alignedSize, alignment);
        memcpy(p->buffer, data, size);
    }
    p->id = id;
    p->size = (u16)alignedSize;
    p->alignment = (u16)alignment;
    p->type = (u16)type;
    p->behaviour = behaviour;
}

// 011f9e20 -- record the vertex descriptor and its behaviour; tail-calls the mask update.
// @ 0x011f9e20
void BuildState::D3D9SetVertexDescriptor(const void* vdesc, i32 behaviour)
{
    m_softStateDirty |= 0x100000;
    m_vdesc = (void*)vdesc;
    D3D9UpdateSoftStateBehaviour(0x100000, behaviour);
}

// 011f9e50 -- required resource size/alignment for a BuildState with maxShaderData entries.
// @ 0x011f9e50
ResourceDesc8 __cdecl BuildStateGetResourceDescriptor(u32 shader, u32 maxShaderData)
{
    (void)shader;
    u32 size = 0x1250;
    if (maxShaderData != 0)
        size = (maxShaderData * 5 - 5) * 4 + 0x1250;

    ResourceDesc8 d;
    d.m_size = 0;
    d.m_rest[0] = 0;
    d.m_alignment = 1;
    d.m_rest[1] = 1;
    d.m_rest[2] = 0;
    d.m_rest[3] = 1;
    d.m_rest[4] = 0;
    d.m_rest[5] = 1;
    d.m_size = size;
    d.m_alignment = 0x10;
    return d;
}

// 011f9eb0 -- initialize a BuildState inside freshly allocated resource memory.
// @ 0x011f9eb0
BuildState* __cdecl BuildStateInitialize(ResourceMem* res, u32 shader, u32 maxShaderData)
{
    BuildState* bs = (BuildState*)res->mem;
    ResourceDesc8 d = BuildStateGetResourceDescriptor(shader, maxShaderData);
    memset(bs, 0, d.m_size);

    bs->m_uvMapping[0] = 0;
    bs->m_uvMapping[1] = 0;
    bs->m_uvMapping[2] = 0;
    bs->m_uvMapping[3] = 0;
    bs->m_uvMapping[4] = 0;
    bs->m_uvMapping[5] = 0;
    bs->m_uvMapping[6] = 0;
    bs->m_uvMapping[7] = 0;
    bs->m_uvMapping[8] = 0;
    bs->m_uvMapping[9] = 0;
    bs->m_uvMapping[10] = 0;
    bs->m_uvMapping[11] = 0;
    bs->m_uvMapping[12] = 0;
    bs->m_uvMapping[13] = 0;
    bs->m_uvMapping[14] = 0;
    bs->m_uvMapping[15] = 0;
    bs->m_uvMapping[16] = 0;
    bs->m_primType = -1;
    bs->m_vdesc = 0;

    if (shader != 0)
        bs->m_shader = BuildStateLookupShader(shader);
    else
        bs->m_shader = 0;

    bs->m_maxShaderData = maxShaderData;
    if (shader != 0)
        bs->m_softStateDirty |= 4;

    bs->m_color[0] = 1.0f;
    bs->m_color[1] = 1.0f;
    bs->m_color[2] = 1.0f;
    bs->m_color[3] = 1.0f;
    bs->m_fogEnd = 1.0f;
    bs->m_fogColor[0] = 1.0f;
    bs->m_fogColor[1] = 1.0f;
    bs->m_fogColor[2] = 1.0f;
    return bs;
}

// 011f9f90 -- reset the global shader hash table.
// @ 0x011f9f90
void __cdecl ResetShaderRegistry()
{
    for (u32 i = 0; i < 128; ++i)
        g_shaderHash[i] = 0;
    g_shaderCount = 0;
    g_shaderLast = 0;
}

// 011f9fb0 -- insert a shader into the hash table (key = its 32-bit id at +0x38).
// @ 0x011f9fb0
void __cdecl InsertShader(u32 key, Shader* node)
{
    g_shaderLast = node;
    u32 bucket = *(u32*)((u8*)node + 0x38) & 0x7f;
    void** head = &g_shaderHash[bucket];
    for (void* p = *head; p != 0; p = *(void**)((u8*)p + 0x40))
    {
        if (*(u32*)((u8*)p + 0x38) == key)
            return;
    }
    *(void**)((u8*)node + 0x40) = *head;
    *head = node;
    ++g_shaderCount;
}

// 011fa000 -- look up a shader by id, caching the last hit.
// @ 0x011fa000
void* __cdecl BuildStateLookupShader(u32 key)
{
    void* p = g_shaderLast;
    if (p == 0 || *(u32*)((u8*)p + 0x38) != key)
    {
        if (g_shaderCount == 0)
            return 0;
        p = g_shaderHash[key & 0x7f];
        if (p == 0)
        {
            g_shaderLast = 0;
            return 0;
        }
        while (*(u32*)((u8*)p + 0x38) != key)
        {
            p = *(void**)((u8*)p + 0x40);
            if (p == 0)
                return 0;
        }
    }
    g_shaderLast = p;
    return p;
}

// 011fa050 -- unlink a shader from the hash table.
// @ 0x011fa050
void __cdecl RemoveShader(u32 key)
{
    if (g_shaderCount == 0)
        return;
    void** head = &g_shaderHash[key & 0x7f];
    void* cur = *head;
    void* prev = 0;
    if (cur == 0)
        return;
    while (*(u32*)((u8*)cur + 0x38) != key)
    {
        prev = cur;
        cur = *(void**)((u8*)cur + 0x40);
        if (cur == 0)
            return;
    }
    void* next = *(void**)((u8*)cur + 0x40);
    if (prev == 0)
        *head = next;
    else
        *(void**)((u8*)prev + 0x40) = next;
    *(void**)((u8*)cur + 0x40) = 0;
    --g_shaderCount;
    g_shaderLast = 0;
}

// 011fa0b0 -- release every shader in the registry.
// @ 0x011fa0b0
void __cdecl ReleaseShaderRegistry()
{
    if (g_shaderCount == 0)
        return;
    g_shaderCount = 0;
    for (u32 i = 0; i < 128; ++i)
    {
        void* p = g_shaderHash[i];
        while (p != 0)
        {
            void* next = *(void**)((u8*)p + 0x40);
            ((Shader*)p)->Release();
            p = next;
        }
        g_shaderHash[i] = 0;
    }
    g_shaderLast = 0;
}

// 011fa100 -- free a compiled-state memory block list and reset its header.
// @ 0x011fa100
void __fastcall MemBlockFree(void* self)
{
    u32* hdr = (u32*)self;
    if (hdr[1] != 0)
    {
        u8* p = (u8*)(((u32)self + 0xc7) & ~0xfu);
        for (u32 i = 0; i < hdr[1]; ++i)
        {
            u8* blk = (u8*)(((u32)p + 0xf) & ~0xfu);
            p = blk + *(u32*)blk;
            if (*(u32*)(blk + 8) & 0x200000)
                p += *(u32*)p;
            ((BlockNode*)blk)->Free();
        }
        hdr[1] = 0;
    }
    hdr[0] = 0;
}

// 011fa170 -- validate every block of a compiled-state memory block list.
// @ 0x011fa170
i32 __cdecl MemBlockValidate(u8* base, void* arg)
{
    if (base != *(u8**)((u8*)arg + 0x7c))
        *(u32*)(base + 0xb4) += (u32)(base - *(u32*)((u8*)arg + 0x7c));

    u8* end = *(u8**)(base + 0xb4);
    u8* p = (u8*)(((u32)base + 0xc7) & ~0xfu);
    do
    {
        u8* blk = (u8*)(((u32)p + 0xf) & ~0xfu);
        if (FUN_011ed690(blk, arg) == 0)
            return 0;
        p = blk + *(u32*)blk;
        if (*(u32*)(blk + 8) & 0x200000)
        {
            if (FUN_011f94f0(p, arg) == 0)
                return 0;
            p += *(u32*)p;
        }
    } while (p < end);
    return 1;
}

// 011fa230 -- arena read callback: resolve every stored object id against the arena.
// @ 0x011fa230
struct ArenaReadDesc
{
    u32 id;         // +0x00
    u32 count;      // +0x04
    u32 ids[1];     // +0x08
};

i32 __cdecl MeshCompiledStateLinkArenaRead(ArenaReadDesc* d, u8* owner)
{
    Arena* arena = *(Arena**)(owner + 0x78);
    u32 id = d->id;
    d->id = (u32)arena->IdToObject(id);
    for (u32 i = 0; i < d->count; ++i)
    {
        u32 sub = d->ids[i];
        d->ids[i] = (u32)arena->IdToObject(sub);
    }
    return 1;
}

// 011fa280 -- register the read callbacks of the compiled-state arena type.
// @ 0x011fa280
void __cdecl RegisterMeshCompiledStateLinkArenaRead()
{
    u8* info = (u8*)ArenaTypeRegGetType(0x2001a);
    *(void**)(info + 0x0c) = (void*)&MeshCompiledStateLinkArenaRead;
    *(u32*)(info + 0x10) = 0;
}

// 011fa2d0 -- zero a freshly created arena object and stamp its id.
// @ 0x011fa2d0
void* __cdecl MeshCompiledStateLinkCreate(void** out, u32 id)
{
    u32* obj = (u32*)*out;
    memset(obj, 0, 0x40);
    *obj = id;
    return obj;
}

// ---- ActiveState constant upload helpers -----------------------------------
typedef void (__stdcall *PFN_ConstF)(void*, u32, const void*, u32);
typedef void (__stdcall *PFN_ConstB)(void*, u32, const void*, u32);

static void SetVSFloatConst(void* dev, u32 reg, const void* data, u32 count)
{
    ((PFN_ConstF)((void**)(*(void***)dev))[0x178 / 4])(dev, reg, data, count);
}
static void SetPSFloatConst(void* dev, u32 reg, const void* data, u32 count)
{
    ((PFN_ConstF)((void**)(*(void***)dev))[0x1b4 / 4])(dev, reg, data, count);
}
static void SetVSBoolConst(void* dev, u32 reg, const void* data, u32 count)
{
    ((PFN_ConstB)((void**)(*(void***)dev))[0x188 / 4])(dev, reg, data, count);
}

// 011fa310 -- upload one float4 constant (animation blend weight).
// @ 0x011fa310
void __cdecl ActiveStateSetBlendConstant(u32 reg)
{
    float v[4];
    v[0] = *g_animTime;
    v[1] = g_one - *g_animTime;
    v[2] = 0.0f;
    v[3] = g_one;
    SetVSFloatConst(g_device, reg, v, 1);
}

// 011fa370 -- upload the skinning matrix palette (3 constants per bone).
// @ 0x011fa370
void __cdecl ActiveStateSetSkinConstants(u32 reg)
{
    u32* s = (u32*)g_skinData;
    if (s[2] == 0)
    {
        SetVSFloatConst(g_device,
                        reg + s[0] * 3,
                        (const void*)(s[4] + s[0] * 0x30),
                        s[1] * 3);
        return;
    }
    for (i32 i = 0; i < (i32)s[2]; i += 3)
    {
        u8* idx = (u8*)(s[3] + i);
        SetVSFloatConst(g_device,
                        reg + idx[1] * 3,
                        (const void*)(s[4] + idx[2] * 0x30),
                        idx[0] * 3);
    }
}

// 011fa410 -- upload a run of boolean constants (true up to the device maximum).
// @ 0x011fa410
void __cdecl ActiveStateSetBoolConstants(u32 reg, u32 count)
{
    u32* flags = (u32*)_alloca(count * 4);
    u32 n = g_maxBoolConsts;
    if (n > count)
        n = count;
    u32 i;
    for (i = 0; i < n; ++i)
        flags[i] = 1;
    for (; i < count; ++i)
        flags[i] = 0;
    SetVSBoolConst(g_device, reg, flags, count);
}

// 011fa480 -- upload the transform concatenated with one of the cached matrices.
// @ 0x011fa480
void __cdecl ActiveStateSetTransformConstantA(u32 reg, u32 count, i32 vertexShader)
{
    Matrix44 m;
    if (g_transformType == 4)
        memcpy(&m, &g_matrixBE0, sizeof(m));
    else
        D3DXMatrixMultiply(&m, g_transform, &g_matrixBE0);
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &m, count);
    else
        SetPSFloatConst(g_device, reg, &m, count);
}

// 011fa4f0 -- upload the transposed transform (optionally concatenated).
// @ 0x011fa4f0
void __cdecl ActiveStateSetTransposedTransform(u32 reg, u32 count, i32 vertexShader)
{
    Matrix44 m;
    if (g_transformType == 4)
    {
        D3DXMatrixTranspose(&m, &g_matrixB10);
    }
    else
    {
        Matrix44 t8b10;
        D3DXMatrixTranspose(&t8b10, &g_matrixB10);
        if (g_transposedTransform == 0)
        {
            Matrix44 tt;
            D3DXMatrixTranspose(&tt, g_transform);
            D3DXMatrixMultiply(&m, &t8b10, &tt);
        }
        else
        {
            D3DXMatrixMultiply(&m, &t8b10, g_transposedTransform);
        }
    }
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &m, count);
    else
        SetPSFloatConst(g_device, reg, &m, count);
}

// 011fa5a0 -- upload the cached transposed transform, or transpose the live one.
// @ 0x011fa5a0
void __cdecl ActiveStateSetTransposedTransformB(u32 reg, u32 count, i32 vertexShader)
{
    if (g_transposedTransform != 0)
    {
        if (vertexShader != 0)
            SetVSFloatConst(g_device, reg, g_transposedTransform, count);
        else
            SetPSFloatConst(g_device, reg, g_transposedTransform, count);
        return;
    }
    Matrix44 m;
    D3DXMatrixTranspose(&m, g_transform);
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &m, count);
    else
        SetPSFloatConst(g_device, reg, &m, count);
}

// 011fa630 -- upload the transform concatenated with the second cached matrix.
// @ 0x011fa630
void __cdecl ActiveStateSetTransformConstantB(u32 reg, u32 count, i32 vertexShader)
{
    Matrix44 m;
    if (g_transformType == 4)
    {
        memcpy(&m, &g_matrixC70, sizeof(m));
    }
    else if (g_transposedTransform == 0)
    {
        Matrix44 t;
        D3DXMatrixTranspose(&t, g_transform);
        D3DXMatrixMultiply(&m, &g_matrixC70, &t);
    }
    else
    {
        D3DXMatrixMultiply(&m, &g_matrixC70, g_transposedTransform);
    }
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &m, count);
    else
        SetPSFloatConst(g_device, reg, &m, count);
}

// 011fa6d0 -- upload the product of the live transform and the first cached matrix.
// @ 0x011fa6d0
void __cdecl ActiveStateSetTransformConstantC(u32 reg, u32 count, i32 vertexShader)
{
    Matrix44 m;
    const void* data;
    if (g_transformType == 4)
    {
        data = &g_matrixB10;
    }
    else
    {
        D3DXMatrixMultiply(&m, g_transform, &g_matrixB10);
        data = &m;
    }
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, data, count);
    else
        SetPSFloatConst(g_device, reg, data, count);
}

// 011fa8c0 -- upload the live affine transform.
// @ 0x011fa8c0
void __cdecl ActiveStateSetLiveTransform(u32 reg, u32 count, i32 vertexShader)
{
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, g_transform, count);
    else
        SetPSFloatConst(g_device, reg, g_transform, count);
}

// 011fa8f0 -- upload the second cached matrix.
// @ 0x011fa8f0
void __cdecl ActiveStateSetCachedMatrixC70(u32 reg, u32 count, i32 vertexShader)
{
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &g_matrixC70, count);
    else
        SetPSFloatConst(g_device, reg, &g_matrixC70, count);
}

// 011fa920 -- upload the transposed view matrix with a canonical fourth row.
// @ 0x011fa920
void __cdecl ActiveStateSetTransposedMatrixA(u32 reg, u32 count, i32 vertexShader)
{
    Matrix44 m;
    D3DXMatrixTranspose(&m, g_matrixPtrA5B8);
    m.wAxis[0] = 0.0f;
    m.wAxis[1] = 0.0f;
    m.wAxis[2] = 0.0f;
    m.wAxis[3] = 1.0f;
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &m, count);
    else
        SetPSFloatConst(g_device, reg, &m, count);
}

// 011fa9d0 -- upload the transposed first cached matrix with a canonical fourth row.
// @ 0x011fa9d0
void __cdecl ActiveStateSetTransposedMatrixB(u32 reg, u32 count, i32 vertexShader)
{
    Matrix44 m;
    D3DXMatrixTranspose(&m, &g_matrixB10);
    m.wAxis[0] = 0.0f;
    m.wAxis[1] = 0.0f;
    m.wAxis[2] = 0.0f;
    m.wAxis[3] = 1.0f;
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &m, count);
    else
        SetPSFloatConst(g_device, reg, &m, count);
}

// 011faa50 -- upload the third cached matrix.
// @ 0x011faa50
void __cdecl ActiveStateSetCachedMatrixBE0(u32 reg, u32 count, i32 vertexShader)
{
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, &g_matrixBE0, count);
    else
        SetPSFloatConst(g_device, reg, &g_matrixBE0, count);
}

// 011faa80 -- upload the matrix behind g_matrixPtrA5B8 unmodified.
// @ 0x011faa80
void __cdecl ActiveStateSetMatrixA5B8(u32 reg, u32 count, i32 vertexShader)
{
    if (vertexShader != 0)
        SetVSFloatConst(g_device, reg, g_matrixPtrA5B8, count);
    else
        SetPSFloatConst(g_device, reg, g_matrixPtrA5B8, count);
}
