// slice s011eec00 -- RenderWare D3D9 graphics state compilation (rw::graphics::CompiledState).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS- (VS2008: this piece uses movaps; VC7.1 gives rep movsd copies).
#include "types.h"
#include <xmmintrin.h>
#include <intrin.h>

typedef unsigned int u32;
typedef unsigned short u16;
struct U4 { u32 v[4]; };
struct U3 { u32 v[3]; };

// 16-byte aligned row vector / 4x4 matrix (copied with movaps).
union __declspec(align(16)) V4 { __m128 v; struct { float x, y, z, w; }; };
struct __declspec(align(16)) M44 { __m128 r[4]; };

// A variable-sized record kept in State::recs (20 bytes each).
struct StateRec {
    u32 id;          // +0x00 (0 = unused)
    void* data;      // +0x04
    u16 size;        // +0x08
    u16 align;       // +0x0a
    u32 pad;         // +0x0c (padding up to the type slot below)
    union { u32 type; u32 behaviour; };   // +0x10
};

// Object returned by State::GetBlock (word at +0xc is an element count).
struct BlockObj {
    u32 pad[3];
    u16 count;                 // +0x0c
    void Release(void* h);     // 0x011f3160 (thiscall, 1 arg)
};

// The "new state" being compiled (rw::graphics::State), addressed by dword index where the
// layout is table-like.
struct State {
    union { u32 flags; u32 softStateDirty; };   // 0x000
    u32 pad04[3];
    u32 f10;                   // 0x010
    const M44* f14;            // 0x014 (matrix pointer or inline value)
    u32 pad18[0x48 / 4];
    u32 shader;                // 0x060
    u32 v64[4];                // 0x064
    u32 v74[3];                // 0x074
    u32 r80[8];                // 0x080
    union { u32 maskA[7]; u32 renderStateDirty[7]; };   // 0x0a0
    u32 pad_bc[(0x434 - 0xbc) / 4];
    union { u32 mask434; u32 rasterDirty; };            // 0x434
    u32 pad438[(0x480 - 0x438) / 4];
    union { u32 f480; u32 paletteDirty; };              // 0x480
    u32 pad484;
    union { u32 f488; u32 palette; };                   // 0x488
    union {
        u32 pad48c[(0xdd8 - 0x48c) / 4];
        struct {
            u32 texStageDirty[17];                      // 0x48c
            u32 pad4d0[(0xdd8 - 0x4d0) / 4];
        };
    };
    union { u32 tabDD8[17]; u32 samplerStateDirty[17]; };   // 0xdd8
    u32 pad_e1c[(0x1218 - 0xe1c) / 4];
    u32 f1218, f121c, f1220;   // 0x1218..0x1220
    u32 f1224[3];              // 0x1224
    u32 padPrim;               // 0x1230 (primitive type)
    BlockObj* block;           // 0x1234
    union { u32 recCount; u32 maxShaderData; };          // 0x1238
    union { StateRec recs[1]; StateRec shaderData[1]; }; // 0x123c (20-byte records)

    u32 GetPrimitiveType() const;   // 0x011f9c20 thiscall
    u32 HasBlock() const;           // 0x011f9c40 thiscall
    BlockObj* GetBlock() const;     // 0x011f9c30 thiscall
};

inline u32 dw(const State* s, int i) { return ((const u32*)s)[i]; }

// CompiledState = EmbeddedState header (size 0x1c) followed by the 16-byte aligned stream.
struct CompiledState {
    u32 instancedSize;   // +0x00
    u32 primitiveType;   // +0x04
    u32 softStateDirty;  // +0x08
    u32 softStateDelta;  // +0x0c
    u32 hardStateDirty;  // +0x10
    u32 hardStateDelta;  // +0x14
    u32 shader;          // +0x18
};

extern unsigned char rwgD3D9BitShiftTable[256];   // 0x016fa3c0, filled by D3D9InitializeBitShiftTable
void __cdecl GlobalState_D3D9InitializeBitShiftTable();                      // 0x011f13c0
u32* __cdecl CompiledState_D3D9GetResourceDescriptor(void* out, const State* s, const State* base);  // 0x011eec00
void* __cdecl FUN_011f34a0(void* loc, u32 count, u32 zero);                  // 0x011f34a0
u32 __cdecl Device_D3D9GetMaxSamplerStage(u32 fmt);                          // 0x011f8400

// rw::ResourceDescriptor: a size/alignment pair followed by four sub-resource
// descriptors (each a size/alignment pair).  0x20 bytes total.
struct ResourceDescriptor {
    u32 size;            // +0x00
    u32 alignment;       // +0x04
    u32 mem[6];          // +0x08 .. +0x1c
};

// ---------------------------------------------------------------------------
// @ 0x011eec00  rw::graphics::CompiledState::D3D9GetResourceDescriptor
// ---------------------------------------------------------------------------
// @ 0x011eec00
u32* __cdecl CompiledState_D3D9GetResourceDescriptor(void* out, const State* s, const State* base)
{
    ResourceDescriptor* d = (ResourceDescriptor*)out;
    u32 size = 0x20;

    if (s->softStateDirty != 0) {
        if (s->softStateDirty & 1) {
            // A transform replaces the base descriptor size: a pointer when the
            // previous state already carried one, otherwise the full matrix.
            if (s->softStateDirty & 2)
                size = 0x24;
            else
                size = 0x60;
        }
        if (s->HasBlock()) {
            BlockObj* o = s->GetBlock();
            size += (o->count + 2) * 12;
        }
        if (s->softStateDirty & 8) {
            u32 any = 0;
            for (u32 i = 0; i < s->maxShaderData; ++i) {
                const StateRec* r = &s->shaderData[i];
                if (r->id == 0)
                    continue;
                size += 8;
                if (r->behaviour == 3 || r->behaviour == 4) {
                    size += 4;
                } else {
                    u32 alignment = r->align;
                    if (alignment > 4)
                        size = (size + alignment - 1) & ~(alignment - 1);
                    size += r->size;
                }
                any = 1;
            }
            if (any)
                size += 8;
        }
        if (s->softStateDirty & 0x10)
            size += 0x10;
        if (s->softStateDirty & 0x20)
            size += 0xc;
        if (s->softStateDirty & 0x3fc0) {
            for (u32 bit = 6; bit < 14; ++bit)
                if (s->softStateDirty & (1u << bit))
                    size += 4;
        }
        if (s->softStateDirty & 0x8000)
            size += 0x11;
        if (s->softStateDirty & 0xf0000) {
            if (s->softStateDirty & 0x10000)
                size += 4;
            if (s->softStateDirty & 0xe0000) {
                if (s->softStateDirty & 0x20000)
                    size += 0xc;
                if (s->softStateDirty & 0x40000)
                    size += 4;
                if (s->softStateDirty & 0x80000)
                    size += 4;
            }
        }
    }

    // State that differs from the base state must be re-emitted.
    if (s != base) {
        u32 extra = 0;
        for (u32 i = 0; i < 7; ++i) {
            if (base->renderStateDirty[i] != 0) {
                extra = 0x20000;
                break;
            }
        }
        extra |= base->rasterDirty;
        if (base->paletteDirty != 0)
            extra |= 0x100000;
        for (u32 i = 0; i < 17; ++i) {
            if (i < Device_D3D9GetMaxSamplerStage(0xffff0000) && base->texStageDirty[i] != 0) {
                extra |= 0x40000;
                break;
            }
        }
        for (u32 i = 0; i < 17; ++i) {
            if (base->samplerStateDirty[i] != 0) {
                extra |= 0x80000;
                break;
            }
        }
        if (extra & 0x20000)
            size += 0x1c;
        if (extra & 0x40000)
            size += 0x44;
        if (extra & 0x80000)
            size += 0x44;
    }

    // Render-state bitmasks: one header word per non-empty mask, one word per set bit.
    u32 anyState = 0;
    for (u32 i = 0; i < 7; ++i) {
        u32 v = s->renderStateDirty[i];
        if (v == 0)
            continue;
        anyState = 1;
        size += 4;
        for (; v != 0; v >>= 1)
            if (v & 1)
                size += 8;
        size += 4;
    }
    if (anyState)
        size += 4;
    size += 4;

    // Per-texture-stage state: raster, texture-stage and sampler blocks.
    for (u32 i = 0; i < 17; ++i) {
        if (!(s->rasterDirty & (1u << i)) &&
            !(i < Device_D3D9GetMaxSamplerStage(0xffff0000) && s->texStageDirty[i] != 0) &&
            s->samplerStateDirty[i] == 0)
            continue;
        size += 0xc;
        if (i < Device_D3D9GetMaxSamplerStage(0xffff0000) && s->texStageDirty[i] != 0) {
            for (u32 v = s->texStageDirty[i]; v != 0; v >>= 1)
                if (v & 1)
                    size += 8;
            size += 4;
        }
        u32 sampler = s->samplerStateDirty[i];
        size += 4;
        if (sampler != 0) {
            for (; sampler != 0; sampler >>= 1)
                if (sampler & 1)
                    size += 8;
            size += 4;
        }
    }
    size += 4;

    d->size = 0;
    d->mem[0] = 0;
    d->alignment = 1;
    d->mem[1] = 1;
    d->mem[2] = 0;
    d->mem[3] = 1;
    d->mem[4] = 0;
    d->mem[5] = 1;
    d->size = size;
    d->alignment = 0x10;
    return (u32*)d;
}

// ---------------------------------------------------------------------------
// @ 0x011eef30  rw::graphics::CompiledState::D3D9Initialize
// ---------------------------------------------------------------------------
// @ 0x011eef30
CompiledState* __cdecl CompiledState_D3D9Initialize(CompiledState** pcs, const State* s, const State* base)
{
    GlobalState_D3D9InitializeBitShiftTable();
    CompiledState* cs = *pcs;
    union { V4 t; struct { u32* cur; u32 z[3]; } loc; u32 w[8]; } tmp;   // 32-byte descriptor scratch (written by GetResourceDescriptor)
    cs->instancedSize = *CompiledState_D3D9GetResourceDescriptor(&tmp, s, base);
    cs->primitiveType = s->GetPrimitiveType();
    cs->softStateDirty = s->flags;
    cs->softStateDelta = base->flags & 0xffffd;
    cs->hardStateDirty = 0;
    cs->hardStateDelta = 0;
    u32 sh = s->shader;
    cs->shader = sh;
    if (sh == 0)
        cs->shader = base->shader;

    u32* p = (u32*)(((u32)cs + 0x2b) & 0xfffffff0);

    if (s->flags != 0) {
        if (s->flags & 1) {
            u32 sd = cs->softStateDirty;
            cs->softStateDirty = sd | (s->f10 << 0x1c);
            if ((~(s->flags >> 1) & 1) == 0) {
                *p++ = (u32)s->f14;
            } else {
                M44* dst = (M44*)p;
                const M44* src = s->f14;
                dst->r[0] = src->r[0];
                dst->r[1] = src->r[1];
                dst->r[2] = src->r[2];
                dst->r[3] = src->r[3];
                tmp.t.v = dst->r[0]; tmp.t.w = 0.0f; dst->r[0] = tmp.t.v;
                tmp.t.v = dst->r[1]; tmp.t.w = 0.0f; dst->r[1] = tmp.t.v;
                tmp.t.v = dst->r[2]; tmp.t.w = 0.0f; dst->r[2] = tmp.t.v;
                tmp.t.v = dst->r[3]; tmp.t.w = 1.0f; dst->r[3] = tmp.t.v;
                p += 16;
            }
        }
        if (s->HasBlock()) {
            BlockObj* o = s->GetBlock();
            tmp.loc.z[0] = 0; tmp.loc.z[1] = 0; tmp.loc.z[2] = 0;
            tmp.loc.cur = p;
            void* h = FUN_011f34a0(&tmp.loc, o->count, 0);
            o->Release(h);
            p += (o->count + 2) * 3;
        }
        if (s->flags & 8) {
            u32 n = s->recCount;
            u32 any = 0;
            if (n != 0) {
                const StateRec* r = s->recs;
                do {
                    if (r->id != 0) {
                        u16* hdr = (u16*)p;
                        hdr[0] = (u16)r->id;
                        p += 2;
                        if (r->type == 3 || r->type == 4) {
                            hdr[1] = 0;
                            hdr[2] = 0;
                            *p++ = (u32)r->data;
                        } else {
                            u32 al = r->align;
                            unsigned char* dst = (unsigned char*)(((u32)p + al - 1) & ~(al - 1));
                            hdr[1] = (u16)(unsigned char)((unsigned char)(u32)dst - (unsigned char)(u32)p);
                            hdr[2] = r->size;
                            u32 sz = r->size;
                            __movsd((unsigned long*)dst, (const unsigned long*)r->data, sz >> 2);
                            __movsb(dst + (sz & ~3u), (const unsigned char*)r->data + (sz & ~3u), sz & 3);
                            dst += sz;
                            p = (u32*)(dst);
                        }
                        any = 1;
                    }
                    r++;
                } while (--n != 0);
            }
            if (any != 0) {
                u16* e = (u16*)p;
                e[0] = 0; e[1] = 0; e[2] = 0; e[3] = 0;
                p += 2;
            } else {
                cs->softStateDirty &= 0xfffffff7;
                if (s == base)
                    cs->softStateDelta &= 0xfffffff7;
            }
        }
        if (s->flags & 0x10) {
            *(U4*)p = *(const U4*)s->v64;
            p += 4;
        }
        if (s->flags & 0x20) {
            *(U3*)p = *(const U3*)s->v74;
            p += 3;
        }
        u32 m = s->flags & 0x3fc0;
        if (m != 0) {
            const u32* q = s->r80;
            int i = 6;
            u32 k;
            do {
                u32 b = 1u << i;
                if (b > m) break;
                if (s->flags & b)
                    *p++ = *q;
                q++;
                k = i - 5;
                i++;
            } while (k < 8);
        }
        if ((char)(s->flags >> 8) < 0) {
            u32 i = 0;
            do {
                ((unsigned char*)p)[i] = ((const unsigned char*)s)[i + 0x420];
                i++;
            } while (i < 0x11);
            p = (u32*)((unsigned char*)p + 0x11);
        }
        if (s->flags & 0xf0000) {
            if (s->flags & 0x10000)
                *p++ = dw(s, 0x486);
            if (s->flags & 0xe0000) {
                if (s->flags & 0x20000) {
                    *(U3*)p = *(const U3*)s->f1224;
                    p += 3;
                }
                if (s->flags & 0x40000)
                    *p++ = dw(s, 0x487);
                if (s->flags & 0x80000)
                    *p++ = dw(s, 0x488);
            }
        }
    }

    if (s != base) {
        u32 i = 0;
        const u32* q = &base->maskA[0];
        do {
            if (*q != 0) { cs->hardStateDelta |= 0x20000; break; }
            i++; q++;
        } while (i < 7);
        u32 a = dw(base, 0x10d);
        u32 d = cs->hardStateDelta;
        cs->hardStateDelta = d | a;
        if (dw(base, 0x120) != 0)
            cs->hardStateDelta = d | a | 0x100000;
        q = (const u32*)base + 0x123;
        u32 j = 0;
        do {
            u32 mx = Device_D3D9GetMaxSamplerStage(0xffff0000);
            if (j < mx && *q != 0) { cs->hardStateDelta |= 0x40000; break; }
            j++; q++;
        } while (j < 0x11);
        i = 0;
        q = (const u32*)base + 0x376;
        do {
            if (*q != 0) { cs->hardStateDelta |= 0x80000; break; }
            i++; q++;
        } while (i < 0x11);
    }

    if (cs->hardStateDelta & 0xe0000) {
        if (cs->hardStateDelta & 0x20000) {
            p[0] = dw(base, 0x28); p[1] = dw(base, 0x29); p[2] = dw(base, 0x2a); p[3] = dw(base, 0x2b);
            p[4] = dw(base, 0x2c); p[5] = dw(base, 0x2d); p[6] = dw(base, 0x2e);
            p += 7;
        }
        if (cs->hardStateDelta & 0x40000) {
            u32 i = 0;
            const u32* q = (const u32*)base + 0x123;
            do {
                u32 v;
                if (i < Device_D3D9GetMaxSamplerStage(0xffff0000)) v = *q; else v = 0;
                *p++ = v;
                i++; q++;
            } while (i < 0x11);
        }
        if (cs->hardStateDelta & 0x80000) {
            const u32* q = (const u32*)base + 0x376;
            int c = 0x11;
            do { *p++ = *q++; c--; } while (c != 0);
        }
    }

    {
        const u32* q = &s->maskA[0];
        u32 idx = 0;
        u32 bitBase = 7;
        do {
            u32 mk = *q;
            if (mk != 0) {
                cs->hardStateDirty |= 0x20000;
                *p++ = idx;
                u32 bit = bitBase;
                do {
                    while (!(mk & 1)) {
                        u32 tz = rwgD3D9BitShiftTable[mk & 0xff];
                        mk >>= tz;
                        bit += tz;
                    }
                    *p++ = bit;
                    *p++ = dw(s, bit + 0x36);
                    mk >>= 1;
                    bit++;
                } while (mk != 0);
                *p++ = 0xffffffff;
            }
            idx++; q++; bitBase += 0x20;
        } while (bitBase < 0xe7);
    }
    if (cs->hardStateDirty & 0x20000)
        *p++ = 0xffffffff;
    if (s->f480 != 0) {
        cs->hardStateDirty |= 0x100000;
        *p = s->f488;
    } else {
        *p = 0xffffffff;
    }
    p++;

    {
        const u32* q = &s->tabDD8[0];
        u32 i = 0;
        u32 offB = 0x398;
        u32 offA = 0x145;
        do {
            u32 v1;
            if (i < Device_D3D9GetMaxSamplerStage(0xffff0000)) v1 = q[-0x253]; else v1 = 0;
            u32 v2 = *q;
            u32 bit = 1u << i;
            if ((s->mask434 & bit) || v1 != 0 || v2 != 0) {
                *p = i;
                if (!(bit & s->mask434)) {
                    p[1] = 0xffffffff;
                } else {
                    cs->hardStateDirty |= bit;
                    p[1] = q[-0x267];
                }
                p[2] = v1;
                p += 3;
                if (v1 != 0) {
                    ((unsigned char*)&cs->hardStateDirty)[2] |= 4;
                    u32 b2 = 1;
                    do {
                        while (!(v1 & 1)) {
                            u32 tz = rwgD3D9BitShiftTable[v1 & 0xff];
                            v1 >>= tz;
                            b2 += tz;
                        }
                        *p = b2;
                        p[1] = dw(s, offA + b2);
                        v1 >>= 1;
                        b2++;
                        p += 2;
                    } while (v1 != 0);
                    *p++ = 0xffffffff;
                }
                *p++ = v2;
                if (v2 != 0) {
                    cs->hardStateDirty |= 0x80000;
                    u32 b3 = 1;
                    do {
                        while (!(v2 & 1)) {
                            u32 tz = rwgD3D9BitShiftTable[v2 & 0xff];
                            v2 >>= tz;
                            b3 += tz;
                        }
                        *p = b3;
                        p[1] = dw(s, offB + b3);
                        v2 >>= 1;
                        b3++;
                        p += 2;
                    } while (v2 != 0);
                    *p++ = 0xffffffff;
                }
            }
            i++; q++;
            offA += 0x21;
            offB += 0xe;
        } while (offA < 0x376);
    }
    *p = 0xffffffff;
    return cs;
}

// ---------------------------------------------------------------------------
// rw::graphics::Raster (retail layout cross-checked against 011ef710/011ef750/011ef880)
// ---------------------------------------------------------------------------
struct Raster;

typedef unsigned char u8;

// Lock() output record; field order/offsets from the dev PDB Raster::Locked.
struct Locked {
    void* pixelData;      // +0x00
    Raster* raster;       // +0x04
    u32 level;            // +0x08
    u32 stride;           // +0x0c
    u32 sliceStride;      // +0x10
    u32 lockFlags;        // +0x14
    u32 volumeDepth;      // +0x18
};

struct Raster {
    u32 m_format;             // +0x00
    int m_type;               // +0x04 (low nibble = raster type, 0x1000 cube, 0x2000 volume)
    void* m_d3dTexture;       // +0x08 (IDirect3DBaseTexture9)
    u16 m_width;              // +0x0c
    u16 m_height;             // +0x0e
    u8 m_depth;               // +0x10
    u8 m_numMipLevels;        // +0x11
    u8 m_face;                // +0x12
    u8 m_pad;                 // +0x13
    Raster* m_nextParent;     // +0x14
    void* m_swapChain;        // +0x18
    void* m_window;           // +0x1c

    void D3D9AddToUnmanagedList();
    void D3D9RemoveFromUnmanagedList() const;
    static unsigned char FormatGetDepth(int format);
    static void D3D9ReleaseResources();
    Raster* Lock(unsigned int lockFlags, unsigned char level, Locked& locked);
    Raster* Unlock(Locked& locked);
};

Raster* g_D3D9UnmanagedList;   // 0x016f5c0c

// ---------------------------------------------------------------------------
// @ 0x011ef6f0  CompiledState::D3D9Initialize pair adapter
// ---------------------------------------------------------------------------
// @ 0x011ef6f0
void CompiledState_D3D9InitializePair(void* pcs, void* state)
{
    CompiledState_D3D9Initialize((CompiledState**)pcs, (const State*)state, (const State*)state);
}

// ---------------------------------------------------------------------------
// @ 0x011ef710  rw::graphics::Raster::D3D9AddToUnmanagedList
// ---------------------------------------------------------------------------
// @ 0x011ef710
void Raster::D3D9AddToUnmanagedList()
{
    Raster* p = g_D3D9UnmanagedList;
    while (p != 0) {
        if (p == this)
            return;
        p = p->m_nextParent;
    }
    if (g_D3D9UnmanagedList != 0) {
        m_nextParent = g_D3D9UnmanagedList;
        g_D3D9UnmanagedList = this;
    } else {
        g_D3D9UnmanagedList = this;
        m_nextParent = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x011ef910  rw::graphics::Raster::FormatGetDepth
// ---------------------------------------------------------------------------
// @ 0x011ef910
unsigned char Raster::FormatGetDepth(int format)
{
    if (format <= 0x32) {
        if (format == 0x32) return 8;
        switch (format) {
        case 0x14: return 0x18;
        case 0x15: case 0x16:
        case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
            return 0x20;
        case 0x17: case 0x18: case 0x19: case 0x1a:
        case 0x1d: case 0x1e: case 0x28:
            return 0x10;
        case 0x1b: case 0x1c: case 0x29:
            return 8;
        case 0x24: return 0x40;
        }
    }
    else if (format <= 0x6f) {
        if (format == 0x6f) return 0x10;
        switch (format) {
        case 0x33: case 0x3c: case 0x3d: case 0x46: case 0x49:
        case 0x50: case 0x51: case 0x65:
            return 0x10;
        case 0x34: return 8;
        case 0x3e: case 0x3f: case 0x40: case 0x43: case 0x47:
        case 0x4b: case 0x4d: case 0x4f: case 0x52: case 0x53: case 0x66:
            return 0x20;
        case 0x6e: return 0x40;
        }
    }
    else if (format <= 0x3154454d) {
        if (format == 0x3154454d) return 0x20;   // MULTI2_ARGB8
        switch (format) {
        case 0x74: return 0x80;
        case 0x71: case 0x73: return 0x40;
        case 0x70: case 0x72: return 0x20;
        case 0x75: return 0x10;
        }
    }
    else {
        switch (format) {
        case 0x34545844: return 8;      // DXT4
        case 0x32595559: return 0x10;   // YUY2
        case 0x33545844: return 8;      // DXT3
        case 0x31545844: return 4;      // DXT1
        case 0x32545844: return 8;      // DXT2
        case 0x35545844: return 8;      // DXT5
        case 0x47424752: return 0x10;   // R8G8_B8G8
        case 0x42475247: return 0x10;   // G8R8_G8B8
        case 0x59565955: return 0x10;   // UYVY
        }
    }
    return 0;
}
// @ 0x011efb20
void Raster::D3D9RemoveFromUnmanagedList() const
{
    Raster* p = g_D3D9UnmanagedList;
    Raster* prev = 0;
    while (p != 0) {
        if (p == this) {
            if (p == g_D3D9UnmanagedList) {
                g_D3D9UnmanagedList = p->m_nextParent;
                return;
            }
            if (prev != 0)
                prev->m_nextParent = p->m_nextParent;
            return;
        }
        prev = p;
        p = p->m_nextParent;
    }
}

// ---------------------------------------------------------------------------
// D3D9 texture interfaces (COM __stdcall: the object is the first stack arg).
// ---------------------------------------------------------------------------
union D3D9LockInfo {
    struct { u32 pitch; void* bits; } rect;                       // D3DLOCKED_RECT
    struct { u32 rowPitch; u32 slicePitch; void* bits; } box;     // D3DLOCKED_BOX
};

typedef int (__stdcall *D3D9LockFn)(void* self, unsigned int level, D3D9LockInfo* info, const void* rect, unsigned int flags);
typedef int (__stdcall *D3D9LockFaceFn)(void* self, unsigned int face, unsigned int level, D3D9LockInfo* info, const void* rect, unsigned int flags);
typedef int (__stdcall *D3D9UnlockLevelFn)(void* self, unsigned int level);
typedef int (__stdcall *D3D9UnlockFaceFn)(void* self, unsigned int face, unsigned int level);
typedef int (__stdcall *D3D9ReleaseFn)(void* self);
typedef int (__stdcall *D3D9SetTextureFn)(void* self, unsigned int stage, void* texture);

// Vtable views: the leading slots are unnamed padding up to the method of interest.
struct D3D9TextureLockVtbl { void* slots[0x4c / 4]; D3D9LockFn Lock; };
struct D3D9TextureLockFaceVtbl { void* slots[0x4c / 4]; D3D9LockFaceFn Lock; };
struct D3D9TextureUnlockVtbl { void* slots[0x50 / 4]; D3D9UnlockLevelFn Unlock; };
struct D3D9TextureUnlockFaceVtbl { void* slots[0x50 / 4]; D3D9UnlockFaceFn Unlock; };
struct D3D9ResourceVtbl { void* slots[8 / 4]; D3D9ReleaseFn Release; };
struct D3D9DeviceVtbl { void* slots[0x104 / 4]; D3D9SetTextureFn SetTexture; };

// COM-style interface views used where retail calls through [vtbl+0x50] directly.
struct D3D9TextureBase20 {
    virtual void __stdcall s00() = 0; virtual void __stdcall s01() = 0;
    virtual void __stdcall s02() = 0; virtual void __stdcall s03() = 0;
    virtual void __stdcall s04() = 0; virtual void __stdcall s05() = 0;
    virtual void __stdcall s06() = 0; virtual void __stdcall s07() = 0;
    virtual void __stdcall s08() = 0; virtual void __stdcall s09() = 0;
    virtual void __stdcall s10() = 0; virtual void __stdcall s11() = 0;
    virtual void __stdcall s12() = 0; virtual void __stdcall s13() = 0;
    virtual void __stdcall s14() = 0; virtual void __stdcall s15() = 0;
    virtual void __stdcall s16() = 0; virtual void __stdcall s17() = 0;
    virtual void __stdcall s18() = 0; virtual void __stdcall s19() = 0;
};
struct D3D9TextureUnlockIface : D3D9TextureBase20 {
    virtual int __stdcall Unlock(unsigned int level) = 0;
};
struct D3D9TextureUnlockFaceIface : D3D9TextureBase20 {
    virtual int __stdcall Unlock(unsigned int face, unsigned int level) = 0;
};

void* g_d3d9Device;             // 0x016f89d0 (IDirect3DDevice9*)
void* g_rasterShadow[17];       // 0x016f5c58 (raster bound to each sampler stage)

// ---------------------------------------------------------------------------
// @ 0x011ef750  rw::graphics::Raster::Lock
// ---------------------------------------------------------------------------
// @ 0x011ef750
Raster* Raster::Lock(unsigned int lockFlags, unsigned char level, Locked& locked)
{
    switch (m_type & 0xf) {
    case 1: case 2: case 3: case 4: case 5:
    case 6: case 7: case 9: case 10:
        return 0;
    case 8:
        break;
    default:
        return 0;
    }

    unsigned int d3dFlags = 0;
    if ((lockFlags & 2) == 0)
        d3dFlags = 0x10;
    if (lockFlags & 8)
        d3dFlags |= 0x2000;

    D3D9LockInfo info;
    int hr;

    if (m_type & 0x1000) {                       // cube map: level is a face
        hr = ((D3D9LockFaceFn*)(*(void***)m_d3dTexture))[0x4c / 4](m_d3dTexture, m_face, level, &info, 0, d3dFlags);
        if (hr < 0)
            return 0;
        locked.pixelData = info.rect.bits;
        locked.stride = info.rect.pitch;
        locked.sliceStride = 0;
        locked.level = level;
        locked.lockFlags = lockFlags;
        locked.raster = this;
        return this;
    }
    if (m_type & 0x2000) {                       // volume: D3DLOCKED_BOX
        hr = ((D3D9LockFn*)(*(void***)m_d3dTexture))[0x4c / 4](m_d3dTexture, level, &info, 0, d3dFlags);
        if (hr < 0)
            return 0;
        locked.pixelData = info.box.bits;
        locked.stride = info.box.rowPitch;
        locked.sliceStride = info.box.slicePitch;
        unsigned int depth = (unsigned short)(m_type >> 16) >> (level & 0x1f);
        locked.volumeDepth = depth;
        if (depth == 0) {
            locked.level = level;
            locked.lockFlags = lockFlags;
            locked.raster = this;
            locked.volumeDepth = 1;
            return this;
        }
        locked.level = level;
        locked.lockFlags = lockFlags;
        locked.raster = this;
        return this;
    }
    hr = ((D3D9LockFn*)(*(void***)m_d3dTexture))[0x4c / 4](m_d3dTexture, level, &info, 0, d3dFlags);
    if (hr < 0)
        return 0;
    locked.pixelData = info.rect.bits;
    locked.stride = info.rect.pitch;
    locked.sliceStride = 0;
    locked.level = level;
    locked.lockFlags = lockFlags;
    locked.raster = this;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x011ef880  rw::graphics::Raster::Unlock
// ---------------------------------------------------------------------------
// @ 0x011ef880
Raster* Raster::Unlock(Locked& locked)
{
    switch (m_type & 0xf) {
    case 1: case 2: case 3: case 4: case 5:
    case 6: case 7: case 9: case 10:
        return 0;
    case 8:
        break;
    default:
        return 0;
    }

    int hr;
    if (m_type & 0x1000) {
        hr = ((D3D9TextureUnlockFaceIface*)m_d3dTexture)->Unlock(m_face, locked.level);
    } else {
        hr = ((D3D9TextureUnlockIface*)m_d3dTexture)->Unlock(locked.level);
    }
    if (hr < 0)
        return 0;

    locked.raster = 0;
    locked.lockFlags = 0;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x011efa70  rw::graphics::Raster::D3D9ReleaseResources
// ---------------------------------------------------------------------------
// @ 0x011efa70
void Raster::D3D9ReleaseResources()
{
    Raster* r = g_D3D9UnmanagedList;
    while (r != 0) {
        for (unsigned int i = 0; i < 17; ++i) {
            if (g_rasterShadow[i] == r) {
                void* device = g_d3d9Device;
                D3D9SetTextureFn setTexture = ((D3D9SetTextureFn*)(*(void***)device))[0x104 / 4];
                setTexture(device, i, 0);
            }
        }
        int type = r->m_type;
        if (type & 0x1000) {
            D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_d3dTexture))[8 / 4];
            release(r->m_d3dTexture);
        } else if (type & 0x2000) {
            D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_d3dTexture))[8 / 4];
            release(r->m_d3dTexture);
        } else {
            switch (type & 0xf) {
            case 1:
                if (r->m_swapChain != 0) {
                    D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_swapChain))[8 / 4];
                    release(r->m_swapChain);
                    r->m_swapChain = 0;
                }
                {
                    D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_d3dTexture))[8 / 4];
                    release(r->m_d3dTexture);
                }
                break;
            case 2:
                {
                    D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_d3dTexture))[8 / 4];
                    release(r->m_d3dTexture);
                }
                break;
            case 9:
                {
                    D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_d3dTexture))[8 / 4];
                    release(r->m_d3dTexture);
                }
                break;
            default:
                {
                    D3D9ReleaseFn release = ((D3D9ReleaseFn*)(*(void***)r->m_d3dTexture))[8 / 4];
                    release(r->m_d3dTexture);
                }
                break;
            }
        }
        r->m_d3dTexture = 0;
        r = r->m_nextParent;
    }
}
