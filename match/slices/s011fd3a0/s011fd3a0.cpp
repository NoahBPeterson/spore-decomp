// slice s011fd3a0 -- RenderWare 4 D3D9 soft-state cache (rwgdrvgraph / ActiveState render-state cache),
// memblock arena helpers and the old-animation interpolator controller.
//
// This address range (0x011e2000-0x0120bc50) is RenderWare 4 core, built with VC .NET 2003
// (cl 13.10) and /GL + /LTCG.  A single-object compile cannot reproduce the cross-call register
// allocation, so byte-exactness is not generally achievable here (see docs/matching.md, "Toolchain
// provenance"); these are complete behavioural reconstructions.  Leaf functions with no calls may
// still match under /vc71.
//
// Call forms:
//   * D3D9 device setters are __stdcall with `this` as the first stack argument, reached through
//     IDirect3DDevice9's vtable (+0x16c CreateVertexShader, +0x170 SetVertexShader,
//     +0x178 SetRenderState, +0x1a8 CreatePixelShader, +0x1ac SetPixelShader,
//     +0x1b4 SetTextureStageState, +0x1bc SetSamplerState, +0x1c4 SetTexture).
//   * 011fd530/011fd5d0/011fd610/011fd6b0 are members of one 20-byte memblock over VirtualAlloc.
//   * 011fdc70/011fdd70/011fe050/011fe100/011fe180 are one interpolator controller class.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include <string.h>
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

extern "C" {
__declspec(dllimport) void* __stdcall VirtualAlloc(void*, unsigned, unsigned, unsigned);
__declspec(dllimport) int   __stdcall VirtualFree(void*, unsigned, unsigned);
}

// ---- image globals (addresses from the cards) ------------------------------
extern void* g_device;                // 0x016f89d0 IDirect3DDevice9*
extern u8    g_shaderDirty;           // 0x016f89f8 shader dirty-state bits
extern void* g_vertexShaderCache;     // 0x016f65ac
extern void* g_pixelShaderCache;      // 0x016f65b0
extern void* g_vertexShaderActive;    // 0x016f6564
extern void* g_pixelShaderActive;     // 0x016f89cc
extern void* g_vertexDescriptorActive;// 0x016f65a0
extern void* g_shaderTable[];         // 0x016f65a8 shader/state object table, indexed by 16-bit id
extern const u32 g_maxSize;           // 0x015d0938 (0x0000ffff)

// render-state soft cache
extern u32 g_renderStateCount;        // 0x0171e11c
extern void* g_renderStateHandle;     // 0x0171e118
extern u32 g_renderStateExtra;        // 0x0171e120
extern u32 g_renderStateId;           // 0x0171e124

// ---- callees (no PDB symbol; named by address) -----------------------------
// 011fd0c0/011fcf20/011fd1f0 take `this` in ecx (__thiscall): declared __fastcall so the
// pointer arrives in ecx, matching the original's tail-jmp form.
void  __fastcall FUN_011fd0c0(void*); // 0x011fd0c0
void  __fastcall FUN_011fcf20(void*); // 0x011fcf20
void  __fastcall FUN_011fd1f0(void*); // 0x011fd1f0
int   FUN_011f57a0(u32, u32, void**, void**, u32*);   // 0x011f57a0
void  FUN_011f5940(void*);            // 0x011f5940
void  FUN_011f9920(void*, u32, u32, u32);             // 0x011f9920
void* FUN_011ffa40(void*);            // 0x011ffa40
void* FUN_01200800(void*);            // 0x01200800
void  __fastcall FUN_011fda40(void*, u32);       // 0x011fda40 (__thiscall: this + fmt)
// 0x011fda40 is really __thiscall(this, fmt) with fmt on the stack: model it as a member
// of a stub class so the ABI matches (cl rejects __thiscall on free functions).
struct CtlRaw { void SetDesc(u32 fmt); };
void  FUN_011f21a0(void);             // 0x011f21a0 GlobalState::D3D9Sync
void  FUN_011ff680(void);             // 0x011ff680 (stride handler)
void  FUN_011fed20(void);             // 0x011fed20 (stride handler)
void  __fastcall FUN_011fd6f0(void*); // 0x011fd6f0
void  __fastcall FUN_011fd730(void*); // 0x011fd730

// The loose __thiscall functions in this range all operate on the same controller layout; a stub
// class gives them the right `this` ABI (cl rejects __thiscall on free functions).
struct Ctl
{
    int   BuildRemap(int slot, u32* table);
    u8*   FrameAt(u32 index);
    int   Alloc(u32 baseOff, u32 slots, u32 tracks, u32 desc, u32 hasData);
    void  SetFrame(u32 handle, float frame);
    void  Advance(float dt);
    void  SetFormat(u32 fmt);
    int   Init(u32 size, u32 desc, u32 hasData);
    void  Evaluate(void);
    bool  Bind(void* handle);
    int   InitSimple(u32 size, u32 desc, u32 hasData);
    int   BuildKeys(u32 handle);
    int   Advance2(float dt);
    void* KeyOf(u32 index);
};

namespace rw { namespace graphics {
// Minimal stubs so the callee ABIs are right (both are __thiscall members).
class EmbeddedState
{ public:
    void* SetVertexDescriptor(void);            // 0x011edcd0
};
class CompiledState
{ public:
    void Dispatch(void);                        // 0x011ee580
};
}}

namespace rw { namespace core { namespace arena {
class Arena
{ public:
    void* IdToObject(u32 id);         // 0x011e2300 rw::core::arena::Arena::IdToObject (__thiscall)
};
}}}

// ============================================================ state cache
// One 4-byte render-state record: {u16 id; u8 value; u8 sub}.
struct StateRec
{
    u16 id;
    u8  value;
    u8  sub;
};

// One 8-byte custom render command: {fn; u16 cmd; u8 a; u8 b}.
struct StateCmd
{
    void* fn;
    u16   cmd;
    u8    a;
    u8    b;
};

// The soft-state cache: 8-byte header, then four record lists (render states, pixel-shader states,
// sampler states, textures), then the custom command list.
class StateCache
{
public:
    u32  unk00;
    u32  unk04;
    StateRec  renderStates[1];        // +0x08
    // following lists are found by walking the records; modelled as bytes here
    u8   rest[1];
};

typedef void (__stdcall *PFN_DevStateIndexed)(void* dev, u32 value, void* obj, u32 sub);
typedef void (__fastcall *PFN_DevCreateVtxShader)(void* dev, void* out, void* desc);
typedef void (__fastcall *PFN_DevSetVtxShader)(void* dev, u32 shader);
typedef void (__fastcall *PFN_DevCreatePixShader)(void* dev, void* out, void* desc);
typedef void (__fastcall *PFN_DevSetPixShader)(void* dev, u32 shader);
typedef void (__cdecl *PFN_Cmd3)(u32, u32, u32);
typedef void (__cdecl *PFN_CmdArg)(void*);

void* DeviceVtblSlot(void* dev, u32 byteOff)
{
    return *(void**)((u8*)*(void**)dev + byteOff);
}

// 011fd3a0 -- apply the cached indexed states and custom render commands to the device
// @ 0x011fd3a0
void __fastcall StateCacheApplyPixel(StateCache* self)
{
    u8* p = (u8*)self + 8;

    // three consecutive indexed-state lists: texture-stage, sampler, texture (slots 0x1b4/0x1bc/0x1c4)
    for (u32 phase = 0; phase < 3; ++phase)
    {
        while (*(u16*)p != 0)
        {
            StateRec* r = (StateRec*)p;
            void* dev = g_device;
            PFN_DevStateIndexed fn = (PFN_DevStateIndexed)DeviceVtblSlot(dev, 0x1b4 + phase * 8);
            fn(dev, r->value, g_shaderTable[r->id], r->sub);
            p += 4;
        }
        p += 4;
    }

    // custom render commands
    StateCmd* cmd = (StateCmd*)p;
    while (cmd->cmd != 0)
    {
        if (cmd->cmd < 0x400 || cmd->cmd >= 0x800)
        {
            u8 a = cmd->a;
            u8 b = cmd->b;
            ((PFN_Cmd3)cmd->fn)(a, b, 0);
        }
        else
        {
            struct { u8 a; u8 b; u32 v; u8 c; } arg;
            arg.a = cmd->a;
            arg.b = cmd->b;
            arg.v = ((u32*)0x016fa5ec)[cmd->cmd * 8];
            arg.c = 0;
            ((PFN_CmdArg)cmd->fn)(&arg);
        }
        ++cmd;
    }
}

// 011fd4d0 -- flush vertex-shader state to the device if the dirty bit is set
// @ 0x011fd4d0
void __cdecl StateCacheFlushVertexShader(void)
{
    void* cache = g_vertexShaderCache;
    if (g_shaderDirty & 2)
    {
        FUN_011fd6f0(*(void**)cache);
        FUN_011fd0c0(cache);
    }
    else
    {
        FUN_011fcf20(cache);
    }
}

// 011fd500 -- flush pixel-shader state to the device if the dirty bit is set
// @ 0x011fd500
void __cdecl StateCacheFlushPixelShader(void)
{
    void* cache = g_pixelShaderCache;
    if (g_shaderDirty & 4)
    {
        FUN_011fd730(*(void**)cache);
        StateCacheApplyPixel((StateCache*)cache);
    }
    else
    {
        FUN_011fd1f0(cache);
    }
}

// ============================================================ memblock arena
// 20-byte block descriptor over a VirtualAlloc'd region.
class MemBlock
{
public:
    u32  m_width;      // +0x00 element stride
    u32  m_capacity;   // +0x04 capacity
    u8*  m_base;       // +0x08 allocation
    u32  m_count;      // +0x0c live entries
    u8*  m_tail;       // +0x10 pointer past the used region

    bool Init(u32 width, u32 capacity);
    void Deinit(void);
    void* Alloc(void);
    void  Free(void* p);
};

// 011fd530 -- MemBlock::Init
// @ 0x011fd530
bool MemBlock::Init(u32 width, u32 capacity)
{
    m_width = width;
    m_capacity = capacity;
    m_count = capacity;

    u8* p = (u8*)VirtualAlloc(NULL, (width + 2) * g_maxSize, 0x102000, 4);
    m_base = p;
    if (p != NULL)
    {
        u32 commit = (width + 2) * capacity;
        if (VirtualAlloc(p, commit, 0x101000, 4) != NULL)
        {
            memset(p, 0, commit);

            m_tail = p + width * capacity;
            u32 i = 0;
            while (i < capacity)
            {
                ((u16*)m_tail)[i] = (u16)(capacity - i - 1);
                ++i;
            }
            return true;
        }
    }
    return false;
}

// 011fd5d0 -- MemBlock::Deinit
// @ 0x011fd5d0
void MemBlock::Deinit(void)
{
    if (m_base != NULL)
    {
        VirtualFree(m_base, (m_width + 2) * g_maxSize, 0xc000);
        m_base = NULL;
    }
    m_width = 0;
    m_capacity = 0;
    m_count = 0;
    m_tail = NULL;
}

// 011fd610 -- MemBlock::Alloc
// @ 0x011fd610
void* MemBlock::Alloc(void)
{
    if (m_count != 0)
    {
        u32 idx = m_count - 1;
        m_count = idx;
        return m_base + m_width * (u32)((u16*)m_tail)[idx];
    }

    u32 old = m_capacity;
    if (old >= g_maxSize)
        return NULL;

    u32 grow = (old >> 1) + 1;
    u32 ncap = grow + old;
    if (ncap > g_maxSize)
    {
        grow = g_maxSize - old;
        ncap = g_maxSize;
    }

    u32 commit = (m_width + 2) * ncap;
    VirtualAlloc(m_base, commit, 0x101000, 4);
    m_capacity = ncap;
    m_count = grow;

    m_tail = m_base + m_width * ncap;
    u32 i = 0;
    while (i < grow)
    {
        ((u16*)m_tail)[i] = (u16)(ncap - i - 1);
        ++i;
    }

    m_count = m_count - 1;
    return m_base + m_width * old;
}

// 011fd6b0 -- MemBlock::Free
// @ 0x011fd6b0
void MemBlock::Free(void* p)
{
    u32 idx = (u32)((u8*)p - m_base) / m_width;
    ((u16*)m_tail)[m_count] = (u16)idx;
    m_count = m_count + 1;
}

// ============================================================ text copy
// 011fd6d0 -- rw::graphics::D3D9TextCopy
// @ 0x011fd6d0
char* __cdecl rw__graphics__D3D9TextCopy(char* dst, const char* src)
{
    char c = *src;
    while (c != '\0')
    {
        ++src;
        *dst = c;
        ++dst;
        c = *src;
    }
    return dst;
}

// ============================================================ shader cache
// A shader descriptor cache: {vtable; u32 current; ... desc at +8}.
// 011fd6f0 -- bind the cached vertex shader (creating it on first use)
// @ 0x011fd6f0
void __fastcall FUN_011fd6f0(void* pself)
{
    u32* self = (u32*)pself;
    if (self[1] == 0)
    {
        void* dev = g_device;
        PFN_DevCreateVtxShader create = (PFN_DevCreateVtxShader)DeviceVtblSlot(dev, 0x16c);
        create(dev, (u8*)self + 8, (u8*)self + 4);
    }
    u32 shader = self[1];
    if ((u32)g_vertexShaderActive != shader)
    {
        void* dev = g_device;
        PFN_DevSetVtxShader set = (PFN_DevSetVtxShader)DeviceVtblSlot(dev, 0x170);
        set(dev, shader);
        g_vertexShaderActive = (void*)shader;
    }
}

// 011fd730 -- bind the cached pixel shader (creating it on first use)
// @ 0x011fd730
void __fastcall FUN_011fd730(void* pself)
{
    u32* self = (u32*)pself;
    if (self[1] == 0)
    {
        void* dev = g_device;
        PFN_DevCreatePixShader create = (PFN_DevCreatePixShader)DeviceVtblSlot(dev, 0x1a8);
        create(dev, (u8*)self + 8, (u8*)self + 4);
    }
    u32 shader = self[1];
    if ((u32)g_pixelShaderActive != shader)
    {
        void* dev = g_device;
        PFN_DevSetPixShader set = (PFN_DevSetPixShader)DeviceVtblSlot(dev, 0x1ac);
        set(dev, shader);
        g_pixelShaderActive = (void*)shader;
    }
}

// 011fd770 -- reset the soft render-state cache
// @ 0x011fd770
int __cdecl StateCacheReset(void)
{
    g_renderStateCount = 0;
    g_renderStateId = 0;
    g_renderStateExtra = 0;
    g_renderStateHandle = 0;
    return 1;
}

// 011fd790 -- per-vertex size from the bound descriptor's element count
// @ 0x011fd790
u32 __cdecl StateCacheVertexStride(void* desc)
{
    void* vd = ((rw::graphics::EmbeddedState*)desc)->SetVertexDescriptor();
    return g_renderStateExtra / *(u8*)((u8*)vd + 0xf);
}

// 011fd7b0 -- dispatch the compiled state and record the descriptor element count
// @ 0x011fd7b0
void __cdecl StateCacheDispatch(void* compiled)
{
    ((rw::graphics::CompiledState*)compiled)->Dispatch();
    FUN_011f21a0();
    g_renderStateCount = *(u8*)((u8*)g_vertexDescriptorActive + 0xf);
}

// 011fd7d0 -- clear the render-state count
// @ 0x011fd7d0
void __cdecl StateCacheClearCount(void)
{
    g_renderStateCount = 0;
}

// 011fd7e0 -- create the render-state object for a descriptor
// @ 0x011fd7e0
void* __cdecl StateCacheBegin(void* handle)
{
    void* out;
    g_renderStateId = (u32)handle;
    if (FUN_011f57a0(g_renderStateCount, (u32)handle, &handle, &out, &g_renderStateExtra) < 0)
        return NULL;
    g_renderStateHandle = handle;
    return out;
}

// 011fd820 -- destroy/free the render-state object
// @ 0x011fd820
void __cdecl StateCacheEnd(void)
{
    FUN_011f5940(g_renderStateHandle);
    FUN_011f9920(g_renderStateHandle, g_renderStateExtra, g_renderStateId, g_renderStateCount);
    g_renderStateHandle = NULL;
    g_renderStateId = 0;
}

// ============================================================ key tables
// A keyframe track descriptor: {u32 size; u32 data;} -- the per-key records live in data[].
class KeyTrack
{
public:
    u32 m_count;    // +0x00
    u32 m_keys;     // +0x04 address of the key array
};

// The controller object (0x48 + tables).
class Controller
{
public:
    u32* m_table;       // +0x00 remap table
    u32  m_valid;       // +0x04
    u32  m_unk08;       // +0x08
    u32  m_unk0c;       // +0x0c
    u32  m_stride;      // +0x10 per-key stride
    u32  m_tracks;      // +0x14 number of tracks
    u32  m_done;        // +0x18 evaluated flag
    void* m_ctrl;       // +0x1c controller handle
    float m_cur;        // +0x20 current frame
    float m_rate;       // +0x24 playback rate
    void* m_keys;       // +0x28 key output table
    u32  m_unk2c;       // +0x2c
    u32  m_unk30;       // +0x30
    u32  m_unk34;       // +0x34
    void* m_formatFn;   // +0x38 stride handler
    void* m_unk3c;      // +0x3c
    void* m_unk40;      // +0x40
    float m_len;        // +0x44 loop length
};

// 011fd860 -- Controller helper: key object for a track index (via the controller handle)
// @ 0x011fd860
void* Ctl::KeyOf(u32 index)
{
    u8* s = (u8*)this;
    return (u8*)(*(u32*)(s + 0x24) * index + *(u32*)(s + 0x2c));
}

// 011fd870 -- shift the controller's pointers forward after a track was reallocated
// @ 0x011fd870
void* __cdecl ControllerShiftForward(void* self, void* track)
{
    u8* s = (u8*)self;
    i32 delta = (i32)s - *(u32*)((u8*)track + 0x20);
    *(u32*)(s + 0x00) -= delta;
    *(u32*)(s + 0x2c) -= delta;
    *(u32*)(s + 0x10) -= delta;
    *(u32*)(s + 0x14) -= delta;
    *(u32*)(s + 0x28) = *(u32*)*(u32*)(s + 0x28);
    *(u32*)(s + 0x0c) = *(u32*)*(u32*)(s + 0x0c);
    return track;
}

// 011fd8b0 -- shift the controller's pointers after the arena block moved
// @ 0x011fd8b0
void __cdecl ControllerShiftBlock(void* self, void* oldbase)
{
    u8* s = (u8*)self;
    i32 delta = (i32)((u8*)s - (u8*)oldbase);
    *(u32*)(s + 0x00) += delta;
    *(u32*)(s + 0x2c) += delta;
    *(u32*)(s + 0x10) += delta;
    *(u32*)(s + 0x14) += delta;
    u32 a = *(u32*)(s + 0x28);
    u32 b = *(u32*)(s + 0x0c);
    *(u32*)(s + 0x28) = (u32)FUN_011ffa40((void*)a);
    *(u32*)(s + 0x0c) = (u32)FUN_01200800((void*)b);
}

// 011fd900 -- rebind the controller to a new keyframe table
// @ 0x011fd900
int __cdecl ControllerRebind(void* self, void* table)
{
    u32* s = (u32*)self;
    u32 c = *(u32*)((u8*)table + 0x7c);
    s[0] = (u32)s + (s[0] - c);
    s[0xb] = (u32)s + (s[0xb] - c);
    s[4] = (u32)s + (s[4] - c);
    s[5] = (u32)s + (s[5] - c);
    u32 a = s[10];
    u32 b = s[3];
    s[10] = (u32)FUN_011ffa40((void*)a);
    s[3] = (u32)FUN_01200800((void*)b);
    return 1;
}

// 011fd990 -- map every frame index of the source table to the target table's index (or -1)
// @ 0x011fd990
int Ctl::BuildRemap(int slot, u32* table)
{
    u32* s = (u32*)this;
    if (*(u32*)(s[0] + 8) == table[2])
    {
        s[1] = 0;
        return 1;
    }
    s[1] = 1;
    u32 count = *(u32*)(s[0] + 4);
    u32 n = table[1];
    i32 valid = 1;
    u32 i = 0;
    if (count == 0)
        return valid;
    do
    {
        u32 j = 0;
        if (n != 0)
        {
            u32* p = (u32*)*table;
            u32 key = *(u32*)(*(u32*)s[0] + i * 4);
            for (;;)
            {
                if (*p == key)
                {
                    *(u32*)(s[slot + 2] + i * 4) = j;
                    break;
                }
                ++j;
                ++p;
                if (j >= n)
                    break;
            }
        }
        if (j == n)
        {
            *(u32*)(s[slot + 2] + i * 4) = 0xffffffff;
            valid = 0;
        }
        ++i;
    } while (i < count);
    return valid;
}

// 011fda50 -- Controller::FrameAt: key object address for a frame index
// @ 0x011fda50
u8* Ctl::FrameAt(u32 index)
{
    u8* s = (u8*)this;
    return (u8*)(*(u32*)(s + 0x10) * index + *(u32*)(s + 8));
}

// 011fda60 -- layout a track block: base offset, slot count, track count, format, data flag.
// @ 0x011fda60
int Ctl::Alloc(u32 baseOff, u32 slots, u32 tracks, u32 desc, u32 hasData)
{
    u8* s = (u8*)this;
    u32 align = 4;
    if ((u8)desc != 0) align = 0x10;
    u32 stride = ((desc >> 16 & 0xff) + (desc & 0xff) * 4 + (desc >> 8 & 0xff)) * 4 + 4;
    stride = (stride + (align - 1)) & ~(align - 1);

    *(u32*)(s + 0x0c) = desc;
    *(u32*)(s + 0x10) = stride;
    *(u32*)(s + 0x14) = tracks;
    *(u32*)(s + 0x18) = 0;

    if (hasData == 0)
    {
        *(u32*)s = 0;
        return (int)baseOff;
    }

    u32 base = (baseOff + 3) & 0xfffffffc;
    u32 obj = base + (u32)s;
    *(u32*)s = obj;
    *(u32*)(obj + 4) = 0;
    *(u32*)obj = 0;

    u32 a = slots;
    u32 b = tracks;
    u32 c = slots * 4 - 4;
    if (a != 0)
    {
        u32 off = 0xc;
        u32 n = a;
        u32 sl = 8;
        do
        {
            *(u32*)(sl + *(u32*)s) = *(u32*)s + off + c;
            off += b * 4;
            --n;
            sl += 4;
        } while (n != 0);
    }
    return (int)(base + c + b * a * 4 + 0xc);
}

// 011fdb30 -- relocate the controller tables after the block moved by `delta`
// @ 0x011fdb30
void __cdecl ControllerFixup(void* self, void* arena, u32 delta, u32 n)
{
    u8* s = (u8*)self;
    if (delta != 0)
    {
        *(u32*)(s + 8) += delta;
        if (*(u32*)s == 0)
            return;
        *(u32*)s += delta;
        if (n != 0)
        {
            u32 off = 8;
            do
            {
                u32* p = (u32*)(*(u32*)s + off);
                *p = *p + delta;
                off += 4;
            } while (--n != 0);
        }
    }
    u32* obj = (u32*)*(u32*)s;
    if (obj != NULL)
    {
        *obj = (u32)((rw::core::arena::Arena*)arena)->IdToObject(*obj);
    }
}

// 011fdba0 -- store the frame value and (re)build the key chain
// @ 0x011fdba0
void Ctl::SetFrame(u32 handle, float frame)
{
    u8* s = (u8*)this;
    if (*(u32*)(s + 0x18) != 0)
    {
        u32 n = *(u32*)(s + 0x14) * *(u32*)(s + 0x10);
        memcpy(*(void**)(s + 0x3c), *(void**)(s + 8), n);
        *(float*)(s + 0x44) = frame;
        ((Ctl*)s)->BuildKeys(handle);
        return;
    }
    *(float*)(s + 0x44) = -1.0f;
    ((Ctl*)s)->BuildKeys(handle);
}

// 011fdc00 -- clamp the loop length and advance
// @ 0x011fdc00
void Ctl::Advance(float dt)
{
    u8* s = (u8*)this;
    if (*(float*)(s + 0x44) > 0.0f)
    {
        float t = *(float*)(s + 0x20) + dt;
        if (t > *(float*)(s + 0x44))
            *(u32*)(s + 0x44) = 0;
    }
    ((Ctl*)s)->Advance2(dt);
}

// 011fdc30 -- choose the per-key stride handler from the format dword
// @ 0x011fdc30
void Ctl::SetFormat(u32 fmt)
{
    u8* s = (u8*)this;
    ((CtlRaw*)s)->SetDesc(fmt);
    if ((u8)fmt == 1 && (u8)(fmt >> 8) == 3 && *(u8*)((u8*)&fmt + 2) == 0)
        *(void**)(s + 0x38) = (void*)FUN_011ff680;
    else
        *(void**)(s + 0x38) = (void*)FUN_011fed20;
}

// 011fdc70 -- construct the controller wrapper over `size` tracks
// @ 0x011fdc70
int Ctl::Init(u32 size, u32 desc, u32 hasData)
{
    u8* s = (u8*)this;
    u32 align = 4;
    if ((u8)desc != 0) align = 0x10;
    u32 stride = ((desc >> 16 & 0xff) + (desc & 0xff) * 4 + (desc >> 8 & 0xff)) * 4 + 4;
    stride = (stride + (align - 1)) & ~(align - 1);

    int obj = Alloc(0x48, 1, size, desc, hasData);
    u32 table = (u32)obj + size * 8;
    if (align > 1)
    {
        u32 m = align - 1;
        table = (table + m) & ~m;
    }

    u32 p = (size + 1) * stride + table + (u32)s;

    *(u32*)(s + 0x20) = 0;
    *(u32*)(s + 8) = p;
    *(float*)(s + 0x24) = 1.0f;
    *(u32*)(s + 0x28) = (u32)obj + (u32)s;
    *(u32*)(s + 0x1c) = 0;
    *(u32*)(s + 0x2c) = 0;
    *(u32*)(s + 0x38) = 0;
    *(u32*)(s + 4) = 0x015d093c;
    *(float*)(s + 0x44) = -1.0f;
    *(u32*)(s + 0x3c) = table + (u32)s;
    *(u32*)(s + 0x40) = p - stride;
    return (int)s;
}

// 011fdd40 -- create a controller from an allocation handle
// @ 0x011fdd40
void* __cdecl ControllerCreate(void** handle, u32 size, u32 desc, u32 hasData)
{
    void* h = *handle;
    if (h == NULL)
        return NULL;
    return (void*)((Ctl*)h)->Init(size, desc, hasData);
}

// 011fdd70 -- walk all tracks and emit keys for the current frame
// @ 0x011fdd70
void __fastcall ControllerEvaluate(void* self)
{
    u8* s = (u8*)self;
    if (*(u32*)(s + 0x18) != 0)
    {
        *(u32*)(s + 0x18) = 1;
        return;
    }

    u32 tracks = *(u32*)(s + 0x14);
    u32 out = *(u32*)(s + 8);
    u32 ctrl = *(u32*)(s + 0x1c);
    u32 flags = ((*(u8*)(ctrl + 0x1c) & 1) << 3) | 4;
    u32 i = 0;

    if (*(float*)(s + 0x20) < *(float*)(s + 0x44))
    {
        float t = (*(float*)(s + 0x44) - *(float*)(s + 0x20)) / *(float*)(s + 0x44);
        u32 l0 = *(u32*)(s + 0x3c);
        if (tracks != 0)
        {
            do
            {
                u32 key = 0;
                u32 tbl = *(u32*)s;
                if (tbl != 0 && *(u32*)(tbl + 4) != 0)
                    key = *(u32*)(*(u32*)(tbl + 8) + i * 4);
                void* k = ((Ctl*)ctrl)->KeyOf(key);
                typedef void (__cdecl *Emit)(u32, void*, u32, float, u32, void*);
                ((Emit)*(void**)(s + 0x2c))(*(u32*)(s + 0x40), (void*)(*(u32*)(s + 0x28) + key * 8),
                                            *(u32*)((u8*)k + 4) - flags, *(float*)(s + 0x20),
                                            *(u32*)(ctrl + 0xc), k);
                typedef void (__cdecl *Emit2)(u32, u32, u32, u32, float);
                ((Emit2)*(void**)(s + 0x38))(out, *(u32*)(s + 0x40), l0, *(u32*)(s + 0xc), t);
                l0 += *(u32*)(s + 0x10);
                out += *(u32*)(s + 0x10);
                ++i;
            } while (i < tracks);
            *(u32*)(s + 0x18) = 1;
            return;
        }
    }
    else if (tracks != 0)
    {
        do
        {
            u32 key = 0;
            u32 tbl = *(u32*)s;
            if (tbl != 0 && *(u32*)(tbl + 4) != 0)
                key = *(u32*)(*(u32*)(tbl + 8) + i * 4);
            void* k = ((Ctl*)ctrl)->KeyOf(key);
            typedef void (__cdecl *Emit)(u32, void*, u32, float, u32, void*);
            ((Emit)*(void**)(s + 0x2c))(out, (void*)(*(u32*)(s + 0x28) + key * 8),
                                        *(u32*)((u8*)k + 4) - flags, *(float*)(s + 0x20),
                                        *(u32*)(ctrl + 0xc), k);
            out += *(u32*)(s + 0x10);
            ++i;
        } while (i < tracks);
    }
    *(u32*)(s + 0x18) = 1;
}

// 011fdf00 -- compute the byte size of a controller block of `size` tracks
// @ 0x011fdf00
u32* __cdecl ControllerLayout(u32* o, u32 size, u32 desc, u32 hasData)
{
    u32 align = 4;
    if ((u8)desc != 0) align = 0x10;
    u32 stride = ((desc >> 16 & 0xff) + (desc & 0xff) * 4 + (desc >> 8 & 0xff)) * 4 + 4;
    stride = (stride + (align - 1)) & ~(align - 1);

    u32 extra = 0;
    if (hasData != 0)
        extra = size * 4 + 0xc;

    u32 total = extra + size * 8 + 0x48;
    if (align > 1)
    {
        u32 m = align - 1;
        total = (total + m) & ~m;
    }
    total += stride * size + (size + 1) * stride;

    o[0] = 0;
    o[1] = 1;
    o[2] = 0;
    o[3] = 1;
    o[4] = 0;
    o[5] = 1;
    o[6] = 0;
    o[7] = 1;
    o[1] = align;
    o[0] = total;
    return o;
}

// 011fdfc0 -- return the block size for this controller
// @ 0x011fdfc0
u32 __fastcall ControllerSize(void* self)
{
    u32* s = (u32*)self;
    u32 buf[8];
    return *ControllerLayout(buf, s[5], s[3], *s != 0 ? 1 : 0);
}

// 011fdff0 -- attach a keyframe table handle to the controller
// @ 0x011fdff0
bool Ctl::Bind(void* handle)
{
    u8* s = (u8*)this;
    void* r = FUN_011ffa40(handle);
    if (r == NULL)
        return false;
    *(u32*)(s + 0x34) = (u32)handle;
    *(u32*)(s + 0x2c) = *(u32*)((u8*)r + 4);
    *(u32*)(s + 0x30) = *(u32*)((u8*)r + 8);
    return true;
}

// 011fe030 -- the controller handle
// @ 0x011fe030
void* __fastcall ControllerGetTable(void* self)
{
    u32 zero = 0;
    void* p = *(void**)((u8*)self + 0x1c);
    if (p == NULL)
        p = (void*)zero;
    return p;
}

// 011fe040 -- refresh the remap for the current controller handle
// @ 0x011fe040
void __fastcall ControllerRebuild(void* self)
{
    u8* s = (u8*)self;
    Ctl* c = *(Ctl**)s;
    c->BuildRemap(0, (u32*)*(u32*)(s + 0x1c));
}

// 011fe050 -- construct a controller without a key table
// @ 0x011fe050
int Ctl::InitSimple(u32 size, u32 desc, u32 hasData)
{
    u8* s = (u8*)this;
    u32 align = 4;
    if ((u8)desc != 0) align = 0x10;

    int obj = Alloc(0x38, 1, size, desc, hasData);
    u32 table = (u32)obj + size * 8;
    if (align > 1)
    {
        u32 m = align - 1;
        table = (table + m) & ~m;
    }

    *(u32*)(s + 0x20) = 0;
    *(u32*)(s + 0x28) = (u32)obj + (u32)s;
    *(u32*)(s + 4) = 0x015d0968;
    *(u32*)(s + 8) = table + (u32)s;
    *(u32*)(s + 0x1c) = 0;
    *(float*)(s + 0x24) = 1.0f;
    *(u32*)(s + 0x2c) = 0;
    *(u32*)(s + 0x30) = 0;
    return (int)s;
}

// 011fe0d0 -- create a simple controller from an allocation handle
// @ 0x011fe0d0
void* __cdecl ControllerCreateSimple(void** handle, u32 size, u32 desc, u32 hasData)
{
    void* h = *handle;
    if (h == NULL)
        return NULL;
    return (void*)((Ctl*)h)->InitSimple(size, desc, hasData);
}

// 011fe100 -- evaluate the current frame into the key table
// @ 0x011fe100
int Ctl::BuildKeys(u32 handle)
{
    u8* s = (u8*)this;
    *(u32*)(s + 0x1c) = handle;
    *(float*)(s + 0x20) = 0.0f;
    if (*(u32*)s != 0 && *(u32*)*(u32*)s != 0)
    {
        typedef void (__fastcall *Fn)(void*, void*);
        ((Fn)*(void**)(*(u32*)(s + 4) + 0x28))((void*)s, 0);
    }
    u32* out = (u32*)*(u32*)(s + 0x28);
    *(u32*)(s + 0x18) = 0;
    u32 count = *(u32*)(s + 0x14);
    u32 i = 0;
    if (count != 0)
    {
        do
        {
            u32* k = (u32*)((Ctl*)handle)->KeyOf(i);
            typedef int (__cdecl *Emit)(u32, u32, u32);
            int r = ((Emit)*(void**)(s + 0x30))(k[2], *(u32*)(handle + 0x1c), *(u32*)(handle + 0xc));
            u32 v = k[0];
            *out = v;
            out[1] = v + (u32)r;
            out += 2;
            ++i;
        } while (i < count);
    }
    return 1;
}

// 011fe180 -- integrate dt, wrap the frame and update the key pointers
// @ 0x011fe180
int Ctl::Advance2(float dt)
{
    u8* s = (u8*)this;
    float step = *(float*)(s + 0x24) * dt;
    if (step > 0.0f)
    {
        u32 ctrl = *(u32*)(s + 0x1c);
        float len = *(float*)(ctrl + 0x20);
        float f = *(float*)(s + 0x20) + step;
        u32 n = *(u32*)(s + 0x14);
        *(float*)(s + 0x20) = f;
        *(u32*)(s + 0x18) = 0;
        if (f > len)
        {
            float r = f - len;
            while (r > len)
                r = r - len;
            *(float*)(s + 0x20) = r;
            ((Ctl*)s)->BuildKeys(ctrl);
            *(float*)(s + 0x20) = r;
        }
        u32* out = (u32*)*(u32*)(s + 0x28);
        if ((*(u8*)(ctrl + 0x1c) & 1) == 0)
        {
            while (n != 0)
            {
                --n;
                u32* k = (u32*)((Ctl*)ctrl)->KeyOf(n);
                u32 stride = k[1];
                u32* e = (u32*)(out[1] + stride - 4);
                while (*(float*)(s + 0x20) > *(float*)e)
                    e = (u32*)((u8*)e + stride);
                out[1] = (u32)e - stride + 4;
                *out = (u32)e - stride;
                out += 2;
            }
        }
        else if (n != 0)
        {
            do
            {
                --n;
                u32* k = (u32*)((Ctl*)ctrl)->KeyOf(n);
                u32 stride = k[1];
                u32* e = (u32*)(out[1] + stride - 0xc);
                while (*(float*)(s + 0x20) > *(float*)e)
                    e = (u32*)((u8*)e + e[1]);
                out[1] = (u32)e - stride + 0xc;
                *out = (u32)e[2] - stride + 0xc + (u32)e;
                out += 2;
            } while (n != 0);
        }
    }
    return 1;
}