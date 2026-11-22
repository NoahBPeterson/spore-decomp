// src/game/UTFSpore_Win32/ImmediateModeEx.cpp -- migrated from slice(s) s00962ff0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ImmediateModeEx.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/BuildState.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_011f5010(int*, int, int, int, int, int);  // 0x11f5010
extern void* g_pfnIndexBuffer;                                         // 0x16f4ae4

// ---- items of slice s00962ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_011f36d0(int*, int, int, int);            // 0x11f36d0
extern "C" void* __cdecl FUN_011f34a0(int* a, int b, int c);      // 0x011f34a0
extern "C" int   __cdecl FUN_011f4f20(int a, int* out);            // 0x011f4f20
extern "C" void  __cdecl FUN_011f4fd0(int* p);                     // 0x011f4fd0
extern "C" void* __cdecl FUN_011f9a90(int* a, int b);              // 0x011f9a90
extern "C" void  __cdecl FUN_011f9e50(void* out, unsigned p, int b); // 0x011f9e50
extern "C" void  __cdecl FUN_011f9ba0(int a, int b, int c);       // 0x011f9ba0
extern "C" void  __cdecl FUN_011f9c10(int a, int b);               // 0x011f9c10
extern "C" void  __cdecl FUN_011f9b10();                           // 0x011f9b10
extern void* g_pfnFree;              // 0x016f4aec
extern char  g_texParams;            // 0x015d07b0
struct ResDesc { int a, b, c, d, e; };
extern "C" void __cdecl  FUN_011f51d0_s0096_2ff0(ResDesc*, int, int, int, int);   // GetResourceDescriptor 0x11f51d0
struct VertexElement { unsigned short stream, offset; unsigned char type, method, usage, usageIndex; int rwDecl; };
struct VertexDescription {
    void*    pNextParent;      // +0x00
    void*    pNextSibling;     // +0x04
    void*    pDXDecl;          // +0x08
    unsigned short elementsCount; // +0x0c
    unsigned char  lockFlags;  // +0x0e
    unsigned char  stride;     // +0x0f
    int      elementsUsed;     // +0x10
    int      elementsHash;     // +0x14
    VertexElement elements[1]; // +0x18
    void Finalize();           // 0x011f3220
};
struct BuildState {
    unsigned m_softStateDirty;              // +0x000
    unsigned m_softStateDynamic;            // +0x004
    unsigned m_softStateDynamicShared;      // +0x008
    unsigned m_softStateExternal;           // +0x00c
    int      m_transformType;               // +0x010
    void*    m_transform;                   // +0x014
    unsigned pad018[2];                     // +0x018
    float    m_transformLocalCopy[16];      // +0x020
    void*    m_shader;                      // +0x060
    float    m_color[4];                    // +0x064
    float    m_ambient[3];                  // +0x074
    void*    m_light[8];                    // +0x080
    unsigned m_renderStateDirty[7];         // +0x0a0
    unsigned m_renderStateDynamic[7];       // +0x0bc
    unsigned m_renderState[210];            // +0x0d8
    unsigned char m_uvMapping[17];          // +0x420
    unsigned char pad431[3];                // +0x431
    unsigned m_rasterDirty;                 // +0x434
    unsigned m_rasterDynamic;               // +0x438
    void*    m_raster[17];                  // +0x43c
    unsigned m_paletteDirty;                // +0x480
    unsigned m_paletteDynamic;              // +0x484
    void*    m_palette;                     // +0x488
    unsigned m_textureStageStateDirty[17];  // +0x48c
    unsigned m_textureStageStateDynamic[17];// +0x4d0
    unsigned m_textureStageState[17][33];   // +0x514
    unsigned m_samplerStateDirty[17];       // +0xdd8
    unsigned m_samplerStateDynamic[17];     // +0xe1c
    unsigned m_samplerState[17][14];        // +0xe60
    int      m_fogType;                      // +0x1218
    float    m_fogStartDensity;             // +0x121c
    float    m_fogEnd;                      // +0x1220
    float    m_fogColor[3];                  // +0x1224
    int      m_primType;                     // +0x1230
    void*    m_vdesc;                        // +0x1234
    unsigned m_maxShaderData;                // +0x1238

    void D3D9SetVertexDescriptor(void* vdesc, int flags);        // 0x011f9e20
    void D3D9SetShaderData(int a, void* b, int c, int d, int e, int f); // 0x011f9cb0
};
extern "C" BuildState* __cdecl FUN_011f9eb0(int* a, unsigned p, int b); // 0x011f9eb0
extern "C" void* __cdecl FUN_011ef6f0(int* a, BuildState* bs);     // 0x011ef6f0
extern "C" void  __cdecl D3D9GetResourceDescriptor(void*, BuildState*, BuildState*); // 0x011f9f00
extern "C" void __cdecl  FUN_011f51d0(int*, int, int, int, int, int);  // GetResourceDescriptor 0x11f51d0
// ---- items of slice s00962ff0 end

// @ 0x00962ff0
int __cdecl FUN_00962ff0(int allocator, int vertexDescription, int vertexCount, int flags)
{
    // The resource descriptor reserves eight words; its first two give the
    // allocation size and alignment. The allocator argument is unused here.
    int descriptor[8];
    ((void (__cdecl*)(int*, int, int, int))FUN_011f51d0_s0096_2ff0)(
        descriptor, vertexDescription, vertexCount, flags);
    int memory = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(
        descriptor[0], descriptor[1]);
    if (memory != 0) {
        int allocation[4];
        allocation[0] = memory;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        return (int)FUN_011f36d0(allocation, vertexDescription, vertexCount, flags);
    }
    return 0;
}

// @ 0x00963060
int __cdecl FUN_00963060(int p1, int p2, int p3, int p4, int p5, int p6)
{
    int desc[8];
    FUN_011f51d0(desc, p2, p3, p4, p5, p6);
    int r = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(desc[0], desc[1]);
    if (r != 0) {
        int local[4];
        local[0] = r;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        return (int)FUN_011f5010(local, p2, p3, p4, p5, p6);
    }
    return 0;
}

// @ 0x009630e0
int __fastcall FUN_009630e0(void* selfPtr, int, unsigned p2, int p3)
{
    char* self = (char*)selfPtr;
    int localVd[4];
    int localIb[3];
    int localDesc[2];
    int cb[5];
    int stateAlloc[4];

    VertexDescription* vd = (VertexDescription*)((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(0x48, 4);
    if (vd == 0) {
        vd = 0;
    } else {
        stateAlloc[0] = (int)vd;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        vd = (VertexDescription*)FUN_011f34a0(stateAlloc, 4, 0);
    }
    *(VertexDescription**)(self + 8) = vd;
    vd->lockFlags |= 2;
    vd->elements[0].stream = 0;            // +0x18
    vd->elements[0].offset = 0;            // +0x1a
    vd->elements[0].type = 1;              // +0x1c
    vd->elements[0].method = 0;            // +0x1d
    vd->elements[0].usage = 4;             // +0x1e
    vd->elements[0].usageIndex = 3;        // +0x1f
    vd->elements[0].rwDecl = 0;
    vd->elements[1].stream = 0;            // +0x20
    vd->elements[1].offset = 0;            // +0x22
    vd->elements[1].type = 4;              // +0x24
    vd->elements[1].method = 5;            // +0x25
    vd->elements[1].usage = 1;             // +0x26
    vd->elements[1].usageIndex = 6;        // +0x27
    vd->elements[1].rwDecl = 0;
    vd->Finalize();

    *(void**)(self + 0x18) = (void*)FUN_00962ff0((int)&g_texParams, *(int*)(self + 8), 0x1000, 1);
    *(unsigned*)(self + 0x10) = 0;
    *(void**)(self + 0x1c) = (void*)FUN_00963060((int)&g_texParams, (int)&g_texParams, 0x800, 0x1800, 8, 4);

    if (FUN_011f4f20(2, localIb) != 0) {
        short* p = (short*)(localIb[0] + 4);
        short s = 2;
        do {
            p[-2] = s - 2;
            p[1] = s - 2;
            p[0] = s;
            p[2] = s;
            p[-1] = s - 1;
            p[3] = s + 1;
            unsigned short next = s + 2;
            p += 6;
            s += 4;
            (void)next;
            if (next >= 0x1000)
                break;
        } while (1);
        FUN_011f4fd0(localIb);
    }

    void* sampler = ((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(0x28, 4);
    if (sampler == 0) {
        stateAlloc[0] = 0;
        sampler = 0;
    } else {
        stateAlloc[0] = (int)sampler;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        sampler = FUN_011f9a90(stateAlloc, 1);
    }
    *(void**)(self + 0x20) = sampler;

    FUN_011f9e50(localDesc, p2, 1);
    void* bsMem = ((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(localDesc[0], localDesc[1]);
    BuildState* bs;
    if (bsMem == 0) {
        bs = 0;
    } else {
        stateAlloc[0] = (int)bsMem;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        bs = FUN_011f9eb0(stateAlloc, p2, 1);
    }

    for (int i = 0; i < 2; ++i) {
        bs->m_samplerStateDirty[i] |= 0x10;
        bs->m_samplerStateDynamic[i] &= ~0x10u;
        bs->m_samplerState[i][5] = 2;
        bs->m_samplerStateDirty[i] |= 0x20;
        bs->m_samplerStateDynamic[i] &= ~0x20u;
        bs->m_samplerState[i][6] = 2;
        bs->m_samplerStateDirty[i] |= 0x40;
        bs->m_samplerStateDynamic[i] &= ~0x40u;
        bs->m_samplerState[i][7] = 0;
        bs->m_samplerStateDirty[i] |= 1;
        bs->m_samplerStateDynamic[i] &= ~1u;
        bs->m_samplerState[i][1] = 3;
        bs->m_samplerStateDirty[i] |= 2;
        bs->m_samplerStateDynamic[i] &= ~2u;
        bs->m_samplerState[i][2] = 3;
    }

    FUN_011f9ba0(0x13, 5, 0);
    FUN_011f9ba0(0x14, 6, 0);
    FUN_011f9ba0(0x1b, 1, 0);
    FUN_011f9ba0(0x16, 1, 0);
    FUN_011f9ba0(0x19, 8, 0);
    FUN_011f9ba0(7, 0, 0);
    FUN_011f9ba0(0x1c, 0, 0);

    bs->m_rasterDirty |= 3;
    bs->m_rasterDynamic |= 3;
    bs->m_softStateDirty |= 0x8000;
    bs->m_softStateDynamic &= 0xffff7fffu;
    bs->m_raster[0] = 0;
    bs->m_raster[1] = 0;
    bs->m_uvMapping[0] = 0;
    bs->m_uvMapping[1] = 0;

    bs->D3D9SetVertexDescriptor(*(void**)(self + 8), 0);
    if (p3 != 0) {
        cb[0] = p2 & 0xffffff00u;
        cb[1] = 0; cb[2] = 0; cb[3] = 0; cb[4] = 0;
        bs->D3D9SetShaderData(p3, cb, 1, 1, 4, 3);
    }
    FUN_011f9c10(4, 1);
    D3D9GetResourceDescriptor(localDesc, bs, bs);

    void* compiled = ((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(localDesc[0], localDesc[1]);
    if (compiled == 0) {
        stateAlloc[0] = 0;
        compiled = 0;
    } else {
        stateAlloc[0] = (int)compiled;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        compiled = FUN_011ef6f0(stateAlloc, bs);
    }
    *(void**)(self + 4) = compiled;
    FUN_011f9b10();
    ((void (__cdecl*)(BuildState*))g_pfnFree)(bs);
    return 1;
}
