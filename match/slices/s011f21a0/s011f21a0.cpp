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

// The d3d9 state banks, split in two halves:
//   ActiveState::m_*       -- the deltas the caller has requested,
//   GlobalState::m_*Dirty  -- the shadow of what was last flushed.
// For every pair `toUpdate = ~delta & dirty` is "still stale", then both words
// are retired.  The rwg_D3D9*ToUpdate words are the per-bank results consumed by
// the dispatchers below.
extern u32 g_activeRenderDelta[7];         // 0x016f89d8 ActiveState::m_renderStateDelta
extern u32 g_activeSoftDelta;              // 0x016f8af8 ActiveState::m_softStateDelta
extern u32 g_activeRasterDelta;            // 0x016f8b00 ActiveState::m_rasterDelta
extern u32 g_activePaletteDelta;           // 0x016f85b0 ActiveState::m_paletteDelta
extern u32 g_activeTextureStageDelta[0x11];// 0x016f8b58 ActiveState::m_textureStageStateDelta
extern u32 g_activeSamplerDelta[0x11];     // 0x016f8cb0 ActiveState::m_samplerStateDelta

extern u32 g_softStateDirty;               // 0x016f9528 GlobalState::m_softStateDirty
extern u32 g_renderStateDirty[7];          // 0x016fa38c GlobalState::m_renderStateDirty
extern u32 g_rasterStageDirty;             // 0x016fa3a8 GlobalState::m_rasterStageDirty
extern u32 g_paletteDirty;                 // 0x016fa384 GlobalState::m_paletteDirty
extern u32 g_textureStageStateDirty[0x11]; // 0x016f9f80 GlobalState::m_textureStageStateDirty
extern u32 g_samplerStateDirty[0x11];      // 0x016f9530 GlobalState::m_samplerStateDirty

extern u32 g_renderStateToUpdate[7];       // 0x016f9634 rwg_D3D9RenderStateToUpdate
extern u32 g_rasterToUpdate;               // 0x016f95a4 rwg_D3D9RasterToUpdate
extern u32 g_textureStageStateToUpdate[0x11]; // 0x016f95a8 rwg_D3D9TextureStageStateToUpdate
extern u32 g_samplerStateToUpdate[0x11];   // 0x016f95f0 rwg_D3D9SamplerStateToUpdate

// Currently bound palette and the shadow of what the device last received.
extern void* g_activePalette;              // 0x016f96a4 ActiveState::m_palette
extern void* g_paletteShadow;              // 0x016f9130 ActiveState::m_paletteShadow

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
    u8  mPadC8[0x1c];          // +0x00c8
    u8  mPadE4;                // +0x00e4
    u8  mPadE5;                // +0x00e5
    u8  mPadE6;                // +0x00e6
    u8  mPadE7;                // +0x00e7
    u8  mPadE8;                // +0x00e8
    u8  mPadE9;                // +0x00e9
    u8  mPadEA;                // +0x00ea
    u8  mPadEB;                // +0x00eb
    u8  mPS20Caps;             // +0x00ec
    u8  mPadED;                // +0x00ed
    u8  mPadEE;                // +0x00ee
    u8  mPadEF;                // +0x00ef
    u8  mPadF0[0x14];          // +0x00f0
    u8  mPad104;               // +0x0104
    u8  mPad105;               // +0x0105
    u8  mPad106;               // +0x0106
    u8  mPad107;               // +0x0107
    u8  mPad108;               // +0x0108
    u8  mPad109;               // +0x0109
    u8  mPad10A;               // +0x010a
    u8  mPad10B;               // +0x010b
    u8  mPixelShaderCaps;      // +0x010c (bit 7 = pixel shader 3.0 supported)
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
//
// The whole "prelude" is evaluated in one go: every dirty word is OR-ed into a
// single `changed` accumulator (the two 0x11-entry per-stage banks included, as
// a 0x44-byte tail loop) and the function returns immediately when the shadow
// deltas come out empty.  Only then does the flush fan out over the banks.
// ===========================================================================
// @ 0x011f21a0
void GlobalState_D3D9Sync(void)
{
    // Every bank participates in one "is anything requested at all" test.
    u32 d0 = g_activeRenderDelta[0];
    u32 d1 = g_activeRenderDelta[1];
    u32 d2 = g_activeRenderDelta[2];
    u32 d3 = g_activeRenderDelta[3];
    u32 d4 = g_activeRenderDelta[4];
    u32 d5 = g_activeRenderDelta[5];
    u32 d6 = g_activeRenderDelta[6];
    u32 soft = g_activeSoftDelta;
    u32 raster = g_activeRasterDelta;
    u32 palette = g_activePaletteDelta;

    u32 changed = d0 | d1 | d2 | d3 | d4 | d5 | d6;
    changed |= soft;
    changed |= raster | palette;
    // The two 0x11-entry per-stage banks are part of the same chain (0x44-byte
    // tail loop in the original).
    for (u32 i = 0; i < 0x11; ++i)
        changed |= g_activeSamplerDelta[i] | g_activeTextureStageDelta[i];
    if (changed == 0)
        return;

    // ---- soft state -------------------------------------------------------
    // One scalar delta feeds the soft dispatcher.
    u32 softDelta = ~soft & g_softStateDirty;
    g_softStateDirty = soft;
    g_activeSoftDelta = 0;
    if (softDelta != 0)
        GlobalState_D3D9SoftStateDispatch(softDelta);

    // The dispatcher may have touched the render-state delta bank, so the seven
    // shadow/delta pairs are re-read after the call.
    d0 = g_activeRenderDelta[0];
    d1 = g_activeRenderDelta[1];
    d2 = g_activeRenderDelta[2];
    d3 = g_activeRenderDelta[3];
    d4 = g_activeRenderDelta[4];
    d5 = g_activeRenderDelta[5];
    d6 = g_activeRenderDelta[6];

    g_renderStateToUpdate[0] = ~d0 & g_renderStateDirty[0];
    g_renderStateDirty[0] = d0;
    g_renderStateToUpdate[1] = ~d1 & g_renderStateDirty[1];
    g_renderStateDirty[1] = d1;
    g_renderStateToUpdate[2] = ~d2 & g_renderStateDirty[2];
    g_renderStateDirty[2] = d2;
    g_renderStateToUpdate[3] = ~d3 & g_renderStateDirty[3];
    g_renderStateDirty[3] = d3;
    g_renderStateToUpdate[4] = ~d4 & g_renderStateDirty[4];
    g_renderStateDirty[4] = d4;

    g_activeRenderDelta[0] = 0;
    g_activeRenderDelta[1] = 0;
    g_activeRenderDelta[2] = 0;
    g_activeRenderDelta[3] = 0;
    g_activeRenderDelta[4] = 0;

    g_renderStateToUpdate[5] = ~d5 & g_renderStateDirty[5];
    g_renderStateDirty[5] = d5;
    g_renderStateToUpdate[6] = ~d6 & g_renderStateDirty[6];
    g_renderStateDirty[6] = d6;

    g_activeRenderDelta[5] = 0;
    g_activeRenderDelta[6] = 0;

    u32 renderChanged = g_renderStateToUpdate[0] | g_renderStateToUpdate[1] |
                        g_renderStateToUpdate[2] | g_renderStateToUpdate[3] |
                        g_renderStateToUpdate[4] | g_renderStateToUpdate[5] |
                        g_renderStateToUpdate[6];
    if (renderChanged != 0)
        GlobalState_D3D9RenderStateDispatch();

    // ---- raster state -----------------------------------------------------
    // The raster delta is re-read after the dispatch above.
    raster = g_activeRasterDelta;
    g_rasterToUpdate = ~raster & g_rasterStageDirty;
    g_rasterStageDirty = raster;
    g_activeRasterDelta = 0;

    // The palette flush fires when a palette stops being requested.
    palette = g_activePaletteDelta;
    u32 paletteChanged = (g_paletteDirty != 0 && palette == 0) ? 1 : 0;
    g_paletteDirty = palette;
    g_activePaletteDelta = 0;

    if (g_rasterToUpdate != 0)
        GlobalState_D3D9RasterDispatch();

    if (paletteChanged != 0) {
        void* boundPalette = g_activePalette;
        if (boundPalette != g_paletteShadow) {
            void* pDevice = g_d3d9Device;
            if (boundPalette != 0) {
                (*(i32(__stdcall**)(void*, u32, void*))((char*)*(void**)pDevice + 0x11c))(pDevice, 0, boundPalette);
                (*(i32(__stdcall**)(void*, u32))((char*)*(void**)pDevice + 0x124))(pDevice, 0);
            } else {
                (*(i32(__stdcall**)(void*, u32, u32))((char*)*(void**)pDevice + 0x11c))(pDevice, 0, 0);
            }
            g_paletteShadow = boundPalette;
        }
    }

    // ---- per-stage banks --------------------------------------------------
    u32 texOr = 0, sampOr = 0;
    for (u32 i = 0; i < 0x11; ++i) {
        u32 t = g_activeTextureStageDelta[i];
        u32 td = ~t & g_textureStageStateDirty[i];
        g_textureStageStateDirty[i] = t;
        g_textureStageStateToUpdate[i] = td;
        g_activeTextureStageDelta[i] = 0;
        texOr |= td;

        u32 s = g_activeSamplerDelta[i];
        u32 sd = ~s & g_samplerStateDirty[i];
        g_samplerStateDirty[i] = s;
        g_samplerStateToUpdate[i] = sd;
        g_activeSamplerDelta[i] = 0;
        sampOr |= sd;
    }
    if (texOr != 0)
        GlobalState_D3D9PaletteDispatch();
    if (sampOr != 0)
        GlobalState_D3D9TextureStageStateDispatch();
}
