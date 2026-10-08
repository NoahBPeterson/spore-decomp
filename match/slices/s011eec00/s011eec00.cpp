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
    u32 type;        // +0x10
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
    u32 flags;                 // 0x000
    u32 pad04[3];
    u32 f10;                   // 0x010
    const M44* f14;            // 0x014 (matrix pointer or inline value)
    u32 pad18[0x48 / 4];
    u32 shader;                // 0x060
    u32 v64[4];                // 0x064
    u32 v74[3];                // 0x074
    u32 r80[8];                // 0x080
    u32 maskA[7];              // 0x0a0
    u32 pad_bc[(0x434 - 0xbc) / 4];
    u32 mask434;               // 0x434
    u32 pad438[(0x480 - 0x438) / 4];
    u32 f480;                  // 0x480
    u32 pad484;
    u32 f488;                  // 0x488
    u32 pad48c[(0xdd8 - 0x48c) / 4];
    u32 tabDD8[17];            // 0xdd8
    u32 pad_e1c[(0x1218 - 0xe1c) / 4];
    u32 f1218, f121c, f1220;   // 0x1218..0x1220
    u32 f1224[3];              // 0x1224
    u32 padPrim;               // 0x1230 (primitive type)
    BlockObj* block;           // 0x1234
    u32 recCount;              // 0x1238
    StateRec recs[1];          // 0x123c (20-byte records)

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
