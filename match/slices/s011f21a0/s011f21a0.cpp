// Slice s011f21a0 -- rw::graphics D3D9 global-state sync and vertex-descriptor helpers
// (SporeApp.exe).  D3D9Sync pushes the pending soft/render/raster/texture-stage/sampler
// state to the device; the vertex-descriptor group covers the active-descriptor
// bind/clear path, the descriptor cache list add/find/remove and the per-element
// declaration type/hash/offset tables.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include <string.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef int                i32;

// ---------------------------------------------------------------------------
// rw::graphics device / dispatch entry points (all cdecl, args on the stack).
// ---------------------------------------------------------------------------
void __cdecl GlobalState_D3D9SoftStateDispatch(u32 delta);    // 0x011f1400
void __cdecl GlobalState_D3D9RenderStateDispatch(void);       // 0x011f1810
void __cdecl GlobalState_D3D9RasterDispatch(void);            // 0x011f18b0
void __cdecl GlobalState_D3D9PaletteDispatch(void);           // 0x011f1950
void __cdecl GlobalState_D3D9TextureStageStateDispatch(void); // 0x011f1a10
void __cdecl GlobalState_D3D9InitializeBitShiftTable(void);   // 0x011f13c0
void __cdecl GlobalState_D3D9Initialize(void);                // 0x011f2480

// ---------------------------------------------------------------------------
// D3D9 device bits used here.
// ---------------------------------------------------------------------------
extern void* g_d3d9Device;                 // 0x016f89d0 IDirect3DDevice9*

// Soft-state dirty bank (7 scalars) and render-state dirty bank (3 scalars).
extern u32 g_softDirty0;                   // 0x016f89d8
extern u32 g_softDirty1;                   // 0x016f89dc
extern u32 g_softDirty2;                   // 0x016f89e0
extern u32 g_softDirty3;                   // 0x016f89e4
extern u32 g_softDirty4;                   // 0x016f89e8
extern u32 g_softDirty5;                   // 0x016f89ec
extern u32 g_softDirty6;                   // 0x016f89f0
extern u32 g_renderDirty0;                 // 0x016f8af8
extern u32 g_renderDirty1;                 // 0x016f8b00
extern u32 g_renderDirty2;                 // 0x016f85b0

// Per-stage dirty banks (0x11 u32 entries each).
extern u32 g_textureStageDirty[0x11];      // 0x016f8b58
extern u32 g_samplerStateDirty[0x11];      // 0x016f8cb0

// Shadow copies / deltas produced by the dispatchers.
extern u32 g_shadowSoft0;                  // 0x016fa38c
extern u32 g_shadowSoft1;                  // 0x016fa390
extern u32 g_shadowSoft2;                  // 0x016fa394
extern u32 g_shadowSoft3;                  // 0x016fa398
extern u32 g_shadowSoft4;                  // 0x016fa39c
extern u32 g_shadowSoft5;                  // 0x016fa3a0
extern u32 g_shadowSoft6;                  // 0x016fa3a4
extern u32 g_shadowRender0;                // 0x016fa3a8
extern u32 g_shadowRender1;                // 0x016fa384
extern u32 g_shadowRender2;                // 0x016fa3ac
extern u32 g_softStateDelta;               // 0x016f9528
extern u32 g_renderStateDelta;             // 0x016f95a4
extern u32 g_softShadow0;                  // 0x016f9634
extern u32 g_softShadow1;                  // 0x016f9638
extern u32 g_softShadow2;                  // 0x016f963c
extern u32 g_softShadow3;                  // 0x016f9640
extern u32 g_softShadow4;                  // 0x016f9644
extern u32 g_softShadow5;                  // 0x016f9648
extern u32 g_softShadow6;                  // 0x016f964c
extern u32 g_texStageBitmap[0x11];         // 0x016f95a8
extern u32 g_samplerBitmap[0x11];          // 0x016f95f0
extern u32 g_activeRaster;                 // 0x016f96a4
extern u32 g_shadowRaster;                 // 0x016f9130

// ---------------------------------------------------------------------------
// Vertex descriptor (rw::graphics::VertexDescriptor).
// ---------------------------------------------------------------------------
struct VDElement
{
    u16 mStream;      // +0x00 D3D stream index
    u16 mOffset;      // +0x02 byte offset within the stream (0xffff until resolved)
    u8  mType;        // +0x04 D3DDECLTYPE
    u8  mMethod;      // +0x05 D3DDECLMETHOD
    u8  mUsage;       // +0x06 D3DDECLUSAGE
    u8  mUsageIndex;  // +0x07 usage index
    u32 mBits;        // +0x08 per-element bit / stream offset
};
// 12 bytes.

struct VertexDescriptor
{
    VertexDescriptor* mpNext;     // +0x00 cache-list next
    VertexDescriptor* mpPrev;     // +0x04 cache-list tail link
    void*             mpD3DDecl;  // +0x08 IDirect3DVertexDeclaration9*
    u16               mu16Count;  // +0x0c element count
    u8                mPad0e;     // +0x0e
    u8                mbFlags;    // +0x0f
    u32               mHash;      // +0x10 hash / flags
    u8                mPad14[4];  // +0x14
    VDElement         mElements[1]; // +0x18

    static bool AreEqual(const VertexDescriptor& a, const VertexDescriptor& b); // 0x011f2e70
    static u32  ElementHashFunction(u8 type, u8 index);                        // 0x011f2fd0
    static int  Create(VertexDescriptor* pDesc);                              // 0x011f2c00
    static void Destroy(VertexDescriptor* pDesc);                            // 0x011f2d20
    void SetElement(u32 index, const void* pSrc);                             // 0x011f2f10
    u32  FindElement(u32 type);                                               // 0x011f2e40
};

typedef bool (__thiscall *PFN_VD_Create)(VertexDescriptor*);
typedef void (__thiscall *PFN_VD_Delete)(VertexDescriptor*);

VertexDescriptor* g_vertexDescriptorHead;   // 0x016fa558 cache list
void*             g_vertexDescriptorActive; // 0x016fa55c bound declaration
u32 g_vertexDescriptorShadow;               // 0x016f65a0 bound-descriptor shadow

// Declaration tables (rw::graphics rodata) -- 8-byte entries, payload at +0x04.
struct DeclTableEntry
{
    u32 mValue;    // +0x00 id / lookup key
    u32 mPayload;  // +0x04 mapped type or offset
};
extern const DeclTableEntry g_declUsageTable[0x12];   // 0x015d0720
extern const DeclTableEntry g_declTypeTable[8];       // 0x015d06e0
extern const DeclTableEntry g_elemHashTable[8];       // 0x015d06a0
extern const u32 g_declEnd[2];                        // 0x014f7478 D3DDECL_END()

// ---------------------------------------------------------------------------
// D3DCAPS9 bits read by rwg_D3D9FindBestDeclType.
// ---------------------------------------------------------------------------
struct D3DCaps9
{
    u8  mPad00[0xc4];          // +0x0000
    u32 mPixelShaderVersion;   // +0x00c4
    u8  mPadC8[0x24];          // +0x00c8
    u8  mPS20Caps;             // +0x00ec
};

const D3DCaps9* __cdecl DevCapsManager_GetD3DCAPS9(void);   // 0x011f8af0

// ===========================================================================
// rw::graphics::GlobalState::D3D9Start
// ===========================================================================
// @ 0x011f2bb0
int GlobalState_D3D9Start(void)
{
    GlobalState_D3D9InitializeBitShiftTable();
    GlobalState_D3D9Initialize();
    return 1;
}

// ===========================================================================
// rw::graphics::GlobalState::D3D9SetActiveVertexDescriptor
// ===========================================================================
// @ 0x011f2bc0
void __fastcall GlobalState_D3D9SetActiveVertexDescriptor(VertexDescriptor* pDesc)
{
    if (g_vertexDescriptorActive == pDesc->mpD3DDecl)
        return;
    void* pDecl = pDesc->mpD3DDecl;
    void* pDevice = g_d3d9Device;
    if ((*(i32(__stdcall**)(void*, void*))((char*)*(void**)pDevice + 0x15c))(pDevice, pDecl) >= 0)
        g_vertexDescriptorActive = pDecl;
}

// ===========================================================================
// rw::graphics::GlobalState::D3D9ClearActiveVertexDescriptor
// ===========================================================================
// @ 0x011f2bf0
void GlobalState_D3D9ClearActiveVertexDescriptor(void)
{
    g_vertexDescriptorActive = 0;
    g_vertexDescriptorShadow = 0;
}

// ===========================================================================
// rw::graphics::VertexDescriptor::FindElement
// ===========================================================================
// @ 0x011f2e40
u32 VertexDescriptor::FindElement(u32 type)
{
    u32 nCount = mu16Count;
    if (nCount != 0) {
        VDElement* pElem = &mElements[0];
        u32 i = 0;
        do {
            if (type == pElem->mBits)
                return i;
            ++i;
            ++pElem;
        } while (i < nCount);
    }
    return 0xffffffff;
}

// ===========================================================================
// rw::graphics::VertexDescriptor::AreEqual
// ===========================================================================
// @ 0x011f2e70
bool VertexDescriptor::AreEqual(const VertexDescriptor& a, const VertexDescriptor& b)
{
    u16 nCount = a.mu16Count;
    if (nCount != b.mu16Count)
        return false;
    if (a.mbFlags != b.mbFlags)
        return false;
    if (a.mHash != b.mHash)
        return false;
    if (nCount != 0) {
        const VDElement* pa = &a.mElements[0];
        const VDElement* pb = &b.mElements[0];
        u32 i = 0;
        do {
            if (pa[i].mStream != pb[i].mStream)
                return false;
            if (pa[i].mOffset != pb[i].mOffset)
                return false;
            if (pa[i].mType != pb[i].mType)
                return false;
            if (pa[i].mMethod != pb[i].mMethod)
                return false;
            if (pa[i].mUsage != pb[i].mUsage)
                return false;
            if (pa[i].mUsageIndex != pb[i].mUsageIndex)
                return false;
            if (pa[i].mBits != pb[i].mBits)
                return false;
            ++i;
        } while (i < nCount);
    }
    return true;
}

// ===========================================================================
// rw::graphics::VertexDescriptor::ElementHashFunction
// ===========================================================================
// @ 0x011f2fd0
u32 VertexDescriptor::ElementHashFunction(u8 type, u8 index)
{
    switch (type) {
    case 0:  return 1u << index;
    case 5:  return 0x10000u << index;
    case 1:  return 0x10000000u << index;
    case 2:  return 0x40000000u << index;
    case 3:  return 0x1000000u << index;
    case 6:  return 0x100u << index;
    case 7:  return 0x10u << index;
    case 10: return 0x1000u << index;
    default: return 0;
    }
}

// ===========================================================================
// rw::graphics::VertexDescriptor::SetElement
// ===========================================================================
// @ 0x011f2f10
void VertexDescriptor::SetElement(u32 index, const void* pSrc)
{
    VDElement* pElem = &mElements[index];
    const u32* p = (const u32*)pSrc;

    pElem->mStream = *(const u16*)((const u8*)p + 8);

    u32 i = 0;
    do {
        if (g_declUsageTable[i].mValue == p[1])
            break;
        ++i;
    } while (i < 0x12);
    pElem->mType = (i < 0x12) ? (u8)g_declUsageTable[i].mPayload : 0x11;
    pElem->mMethod = 0;

    i = 0;
    do {
        if (g_declTypeTable[i].mValue == p[0])
            break;
        ++i;
    } while (i < 8);
    pElem->mUsage = (i < 8) ? (u8)g_declTypeTable[i].mPayload : 0xff;
    pElem->mUsageIndex = *((const u8*)p + 0xa);

    i = 0;
    do {
        if (g_elemHashTable[i].mValue == p[0]) {
            if (p[0] == 1)
                pElem->mBits = *(const u16*)((const u8*)p + 0xa) + g_elemHashTable[i].mPayload;
            else
                pElem->mBits = g_elemHashTable[i].mPayload;
            break;
        }
        ++i;
    } while (i < 8);
    if (i == 8)
        pElem->mBits = 0xffffffff;

    pElem->mOffset = 0xffff;
    if (p[1] == 0x2a)
        pElem->mBits = 4;
}

// ===========================================================================
// rw::graphics::VertexDescriptor::Create (wrapper)
// ===========================================================================
// @ 0x011f2e10
bool VertexDescriptor_CreateWrapper(VertexDescriptor* pDesc)
{
    pDesc->mpPrev = 0;
    pDesc->mpNext = 0;
    return VertexDescriptor::Create(pDesc) != 0;
}

// ===========================================================================
// rw::graphics::VertexDescriptor::Create
// Finds or inserts this descriptor in the cache list, then creates the D3D
// vertex declaration (or AddRefs the cached one).
// ===========================================================================
// @ 0x011f2c00
int VertexDescriptor::Create(VertexDescriptor* pDesc)
{
    VertexDescriptor* pFound = g_vertexDescriptorHead;
    bool bDuplicate = false;
    if (pFound != 0) {
        do {
            if (pFound->mu16Count == pDesc->mu16Count && pFound->mHash == pDesc->mHash) {
                u32 n = (u32)pFound->mu16Count * 0xc;
                if (memcmp(&pFound->mElements[0], &pDesc->mElements[0], n) == 0) {
                    bDuplicate = true;
                    break;
                }
            }
            pFound = pFound->mpNext;
        } while (pFound != 0);
    }

    if (bDuplicate) {
        VertexDescriptor* pTail = pFound;
        VertexDescriptor* pWalk = pFound->mpPrev;
        while (pWalk != 0) {
            pTail = pWalk;
            pWalk = pWalk->mpPrev;
        }
        pTail->mpPrev = pDesc;
    }
    if (g_vertexDescriptorHead != 0)
        pDesc->mpNext = g_vertexDescriptorHead;
    g_vertexDescriptorHead = pDesc;

    if (bDuplicate) {
        pDesc->mpD3DDecl = pFound->mpD3DDecl;
        void* pDecl = pFound->mpD3DDecl;
        (*(void(__stdcall**)(void*))((char*)*(void**)pDecl + 4))(pDecl);
        return 1;
    }

    // Build the D3DVERTEXELEMENT9 array on the stack.
    u8 decl[0x88];
    u8* pd = decl;
    u16 nCount = pDesc->mu16Count;
    if (nCount != 0) {
        const u8* pe = (const u8*)&pDesc->mElements[0];
        u32 n = nCount;
        do {
            *(u16*)(pd + 0x00) = *(const u16*)(pe + 0x00);
            *(u16*)(pd + 0x02) = *(const u16*)(pe + 0x02);
            *(u8*)(pd + 0x04)  = *(const u8*)(pe + 0x04);
            *(u8*)(pd + 0x05)  = *(const u8*)(pe + 0x05);
            *(u8*)(pd + 0x06)  = *(const u8*)(pe + 0x06);
            *(u8*)(pd + 0x07)  = *(const u8*)(pe + 0x07);
            pd += 8;
            pe += 0xc;
        } while (--n != 0);
    }
    *(u32*)(pd + 0x00) = g_declEnd[0];
    *(u32*)(pd + 0x04) = g_declEnd[1];

    void* pDevice = g_d3d9Device;
    if ((*(i32(__stdcall**)(void*, void*, void*))((char*)*(void**)pDevice + 0x158))(
            pDevice, decl, &pDesc->mpD3DDecl) < 0)
        return 0;
    return 1;
}

// ===========================================================================
// rw::graphics::VertexDescriptor::Destroy
// Unlinks the descriptor from the cache list and releases its declaration.
// ===========================================================================
// @ 0x011f2d20
void VertexDescriptor::Destroy(VertexDescriptor* pDesc)
{
    VertexDescriptor* pPrev = 0;
    VertexDescriptor* p = g_vertexDescriptorHead;
    while (p != 0) {
        if (p->mu16Count == pDesc->mu16Count && p->mHash == pDesc->mHash) {
            u32 n = (u32)p->mu16Count * 0xc;
            if (memcmp(&p->mElements[0], &pDesc->mElements[0], n) == 0)
                break;
        }
        pPrev = p;
        p = p->mpNext;
    }

    if (p == pDesc) {
        VertexDescriptor* pNext = p->mpPrev;
        if (p == g_vertexDescriptorHead) {
            if (pNext == 0) {
                g_vertexDescriptorHead = p->mpNext;
            } else {
                g_vertexDescriptorHead = pNext;
                p->mpPrev->mpNext = p->mpNext;
            }
        } else if (pNext == 0) {
            pPrev->mpNext = p->mpNext;
        } else {
            pPrev->mpNext = p->mpPrev;
            p->mpPrev->mpNext = p->mpNext;
        }
    } else {
        pPrev = 0;
        while (p != 0) {
            if (p == pDesc) {
                if (pPrev != 0)
                    pPrev->mpPrev = p->mpPrev;
                break;
            }
            pPrev = p;
            p = p->mpPrev;
        }
    }

    void* pDecl = pDesc->mpD3DDecl;
    if (pDecl != 0) {
        (*(void(__stdcall**)(void*))((char*)*(void**)pDecl + 8))(pDecl);
        if (g_vertexDescriptorActive == pDesc->mpD3DDecl)
            g_vertexDescriptorActive = 0;
        pDesc->mpD3DDecl = 0;
    }
    pDesc->mpNext = 0;
    pDesc->mpPrev = 0;
}

// ===========================================================================
// rw::graphics::rwg_D3D9FindBestDeclType (argument in EAX)
// ===========================================================================
// @ 0x011f3070
int rwg_D3D9FindBestDeclType(u32 type)
{
    switch (type) {
    case 0:  case 0x11:
        return 2;
    case 1:
        return 3;
    case 2:  case 0x12: case 0x13: case 0x14:
        break;
    case 3:  case 4:  case 5:
        return 4;
    case 6:  case 7:  case 8:  case 9:  case 10:
    case 0xb: case 0xc: case 0xd:
        return 1;
    case 0xe: case 0x16:
        return 7;
    case 0xf: case 0x17:
    {
        const D3DCaps9* pCaps = DevCapsManager_GetD3DCAPS9();
        if ((pCaps->mPS20Caps & 0x20) == 0)
            return 3;
        if (pCaps->mPixelShaderVersion > 0xfffe0200)
            return 0xc;
        return 3;
    }
    case 0x10: case 0x15:
        return 0;
    default:
        return 0xffffffff;
    }
    const D3DCaps9* pCaps = DevCapsManager_GetD3DCAPS9();
    if ((pCaps->mPS20Caps & 0x80) == 0)
        return 2;
    if (pCaps->mPixelShaderVersion < 0xfffe0200)
        return 2;
    return 0xe;
}

// ===========================================================================
// rw::graphics::GlobalState::D3D9Sync
// Flushes every dirty state bank to the D3D9 device.
// ===========================================================================
// @ 0x011f21a0
void GlobalState_D3D9Sync(void)
{
    u32 changed = g_softDirty0 | g_softDirty1 | g_softDirty2 | g_softDirty3 |
                  g_softDirty4 | g_softDirty5 | g_softDirty6 |
                  g_renderDirty0 | g_renderDirty1 | g_renderDirty2;
    for (u32 i = 0; i < 0x11; ++i)
        changed |= g_samplerStateDirty[i] | g_textureStageDirty[i];
    if (changed == 0)
        return;

    // ---- soft state -------------------------------------------------------
    {
        u32 v = g_renderDirty0;
        u32 delta = ~v & g_softStateDelta;
        g_softStateDelta = v;
        g_renderDirty0 = 0;
        if (delta != 0)
            GlobalState_D3D9SoftStateDispatch(delta);
    }
    {
        u32 v0 = g_softDirty0, v1 = g_softDirty1, v2 = g_softDirty2, v3 = g_softDirty3;
        u32 v4 = g_softDirty4, v5 = g_softDirty5, v6 = g_softDirty6;

        g_softShadow0 = ~v0 & g_shadowSoft0;
        g_shadowSoft0 = v0;
        g_softShadow1 = ~v1 & g_shadowSoft1;
        g_shadowSoft1 = v1;
        g_softShadow2 = ~v2 & g_shadowSoft2;
        g_shadowSoft2 = v2;
        g_softShadow3 = ~v3 & g_shadowSoft3;
        g_shadowSoft3 = v3;
        g_softShadow4 = ~v4 & g_shadowSoft4;
        g_shadowSoft4 = v4;

        g_softDirty0 = 0;
        g_softDirty1 = 0;
        g_softDirty2 = 0;
        g_softDirty3 = 0;
        g_softDirty4 = 0;

        g_softShadow5 = ~v5 & g_shadowSoft5;
        g_shadowSoft5 = v5;
        g_softShadow6 = ~v6 & g_shadowSoft6;
        g_shadowSoft6 = v6;

        g_softDirty5 = 0;
        g_softDirty6 = 0;

        u32 softAll = g_softShadow0 | g_softShadow1 | g_softShadow2 | g_softShadow3 |
                      g_softShadow4 | g_softShadow5 | g_softShadow6;
        if (softAll != 0)
            GlobalState_D3D9RenderStateDispatch();
    }

    // ---- render state -----------------------------------------------------
    u32 changedRaster;
    u32 renderAll;
    {
        u32 v = g_renderDirty1;
        u32 delta = ~v & g_shadowRender0;
        g_shadowRender0 = v;
        renderAll = delta;

        u32 wasActive = g_shadowRender1;
        if (wasActive == 0 || g_renderDirty2 == 0)
            changedRaster = 0;
        else
            changedRaster = 1;

        g_shadowRender1 = g_renderDirty2;
        g_renderDirty2 = 0;
    }
    u32 texOr = 0, sampOr = 0;
    for (u32 i = 0; i < 0x11; ++i) {
        u32 t = g_textureStageDirty[i];
        u32 td = ~t & g_texStageBitmap[i];
        g_texStageBitmap[i] = t;
        g_textureStageDirty[i] = 0;
        texOr |= td;

        u32 s = g_samplerStateDirty[i];
        u32 sd = ~s & g_samplerBitmap[i];
        g_samplerBitmap[i] = s;
        g_samplerStateDirty[i] = 0;
        sampOr |= sd;
    }
    if (renderAll != 0)
        GlobalState_D3D9RasterDispatch();
    if (changedRaster != 0) {
        u32 raster = g_activeRaster;
        if (raster != g_shadowRaster) {
            void* pDevice = g_d3d9Device;
            if (raster != 0) {
                (*(i32(__stdcall**)(void*, u32, u32))((char*)*(void**)pDevice + 0x11c))(pDevice, 0, raster);
                (*(i32(__stdcall**)(void*, u32))((char*)*(void**)pDevice + 0x124))(pDevice, 0);
            } else {
                (*(i32(__stdcall**)(void*, u32, u32))((char*)*(void**)pDevice + 0x11c))(pDevice, 0, 0);
            }
            g_shadowRaster = raster;
        }
    }
    if (texOr != 0)
        GlobalState_D3D9PaletteDispatch();
    if (sampOr != 0)
        GlobalState_D3D9TextureStageStateDispatch();
}
