// Slice s00866220 -- the libjpeg colour-deconverter / range-limit init cluster
// plus lib_zlib::crc32_little.  All of the "this"-taking routines belong to one
// JPEG context object (fields at +0x58, +0x60, +0x6c, +0x70, +0x78, +0x84, +0x88,
// +0x544) which owns (at +0x5cc) an auxiliary state block, and an allocator
// interface at +0x04 (three __cdecl methods at [0]/[1]/[2], all reached with the
// owning object as their first argument).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (default /GS on).

#include "types.h"
#include <string.h>

struct Ctx;

// ---------------------------------------------------------------------------
// The allocator interface reached through this+0x04: three function pointers.
// ---------------------------------------------------------------------------
typedef void* (__cdecl *AFn)(void*, int, int);
typedef void* (__cdecl *AFn3)(void*, int, int, int);

// ---------------------------------------------------------------------------
// The auxiliary state block reached through this+0x5cc.
// ---------------------------------------------------------------------------
struct Ctx {
    void*     f00;   // +0x00  (fn ptr: the per-scan mode entry)
    void*     f04;   // +0x04  (fn ptr)
    void*     f08;   // +0x08  (fn ptr)
    void*     f0c;   // +0x0c  (fn ptr)
    int       f10;   // +0x10
    int       f14;   // +0x14
    uint32_t* f18;   // +0x18  (array of 0x20 row buffers)
    int       f1c;   // +0x1c
    int*      f20;   // +0x20  (sample buffer)
    int       f24;   // +0x24
    int*      f28;   // +0x28  (range-limit table)
};

// ---------------------------------------------------------------------------
// The owning object.
// ---------------------------------------------------------------------------
struct Obj {
    void**   m00;    // +0x00  (points at an error-reporting object: vtbl[0] and
                     //         two int fields at +0x14 / +0x18)
    void**   alloc;  // +0x04  (allocator interface)
    uint8_t  pad08[0x50];
    int      f58;    // +0x58
    uint8_t  pad5c[4];
    int      f60;    // +0x60
    uint8_t  pad64[8];
    int      f6c;    // +0x6c
    int      f70;    // +0x70
    uint8_t  pad74[4];
    int      f78;    // +0x78
    uint8_t  pad7c[8];
    int      f84;    // +0x84
    int*     f88;    // +0x88  (int[3])
    uint8_t  pad8c[0x544 - 0x8c];
    int      f544;   // +0x544
    uint8_t  pad548[0x5cc - 0x548];
    Ctx*     ctx;    // +0x5cc
};

// ---------------------------------------------------------------------------
// A small ring/refill buffer used by FUN_00866eb0.
// ---------------------------------------------------------------------------
struct Src {
    uint8_t pad00[0x08];
    void*   f08;     // +0x08
    uint8_t pad0c[0x04];
    void*   f10;     // +0x10  (cursor)
    int     f14;     // +0x14  (remaining)
};

struct Buf {
    uint8_t pad00[0x0c];
    void*   f0c;     // +0x0c  (cursor)
    int     f10;     // +0x10  (remaining)
    int     f14;     // +0x14
    uint8_t pad18[0x04];
    Src*    f1c;     // +0x1c
};

// ---------------------------------------------------------------------------
// External helpers (resolved back to the original code by their address).
// ---------------------------------------------------------------------------
extern "C" void FUN_00866040(void* self, int a, int b);
extern "C" void FUN_00865c50(int x);
extern "C" void FUN_008668f0(void* p, int size);   // lib_jpeg::jzero_far
extern "C" void FUN_008654f0();
extern "C" void FUN_00866160();

// The four static CRC tables referenced by lib_zlib::crc32_little.
extern "C" const uint32_t g_0141e9c0[256];
extern "C" const uint32_t g_0141edc0[256];
extern "C" const uint32_t g_0141f1c0[256];
extern "C" const uint32_t g_0141f5c0[256];

// Forward declarations of the routines defined in this file.
void FUN_00866220(Obj* self, int param_2, int* param_3, int param_4);
void FUN_008664e0(Obj* self);
void FUN_00866580(Obj* self);
void FUN_008665b0(Obj* self, int param_2);
void FUN_008666e0(Obj* self);
void FUN_00866700(Obj* self);

// ---------------------------------------------------------------------------
// @ 0x00866220
// Per-row colour de-conversion: for each of param_4 "rows" re-sample param_3's
// component planes into the 3-short-per-pixel sample buffer, clamping each
// component through the range-limit table at ctx+0x28 (indexed by the packed
// 3-component sample) and folding the result into the running per-row sums that
// are flushed into the sample buffer at the end of each row.
// ---------------------------------------------------------------------------
void FUN_00866220(Obj* self, int param_2, int* param_3, int param_4)
{
    int iVar1, iVar2, iVar4, iVar5, iVar7, iVar8, iVar9, iVar10;
    int iVar12, iVar13, iVar14, iVar17, iVar19, iVar21;
    uint32_t uVar15, uVar18, uVar20;
    int* piVar6;
    uint8_t* pbVar11;
    int16_t* psVar16;
    uint8_t* puStack_5c;
    int iStack_54, iStack_50, iStack_4c, iStack_44, iStack_40, iStack_3c, iStack_38, iStack_24;
    int stride;
    int* piStack_48;
    Ctx* c;

    iVar2 = self->f70;
    c = self->ctx;
    iVar4 = (int)c->f18;
    iVar5 = self->f544;
    piVar6 = self->f88;
    iVar7 = piVar6[0];
    iVar8 = piVar6[1];
    iVar9 = piVar6[2];
    iVar10 = (int)c->f28;
    if (0 < param_4) {
        piStack_48 = param_3;
        iStack_24 = param_4;
        do {
            iVar12 = 0;
            pbVar11 = *(uint8_t**)((int)piStack_48 + (param_2 - (int)param_3));
            puStack_5c = (uint8_t*)*piStack_48;
            if (c->f24 == 0) {
                psVar16 = (int16_t*)c->f20;
                iStack_38 = 1;
                stride = 3;
                c->f24 = 1;
            } else {
                pbVar11 = pbVar11 + iVar2 * 3 - 3;
                puStack_5c = puStack_5c + iVar2 - 1;
                psVar16 = (int16_t*)((char*)c->f20 + (iVar2 * 3 + 3) * 2);
                iStack_38 = -1;
                stride = -3;
                c->f24 = 0;
            }
            iVar17 = 0;
            iVar14 = 0;
            iStack_3c = 0;
            iStack_40 = 0;
            iStack_44 = 0;
            iStack_4c = 0;
            iStack_50 = 0;
            iStack_54 = 0;
            for (iVar1 = iVar2; iVar1 != 0; iVar1 = iVar1 - 1) {
                uVar18 = *(uint8_t*)(*(int*)(iVar10 + ((psVar16[stride] + 8 + iVar17) >> 4) * 4) + (uint32_t)*pbVar11 + iVar5);
                uVar20 = *(uint8_t*)(*(int*)(iVar10 + ((psVar16[stride + 1] + 8 + iVar12) >> 4) * 4) + (uint32_t)pbVar11[1] + iVar5);
                uVar15 = *(uint8_t*)(*(int*)(iVar10 + ((psVar16[stride + 2] + 8 + iVar14) >> 4) * 4) + (uint32_t)pbVar11[2] + iVar5);
                iVar13 = (int)uVar15 >> 3;
                iVar14 = ((int)uVar20 >> 2) * 0x20 + iVar13;
                iVar17 = (int)uVar18 >> 3;
                iVar12 = *(int*)(iVar4 + iVar17 * 4);
                if (*(int16_t*)(iVar12 + iVar14 * 2) == 0) {
                    FUN_00866040(self, iVar17, iVar13);
                }
                iVar12 = (int)(*(uint16_t*)(iVar12 + iVar14 * 2) - 1);
                *puStack_5c = (char)iVar12;
                iVar19 = (int)uVar18 - *(uint8_t*)(iVar12 + iVar7);
                iVar21 = (int)uVar20 - *(uint8_t*)(iVar12 + iVar8);
                iVar13 = (int)uVar15 - *(uint8_t*)(iVar12 + iVar9);
                psVar16[0] = (int16_t)(iStack_54 + iVar19 * 3);
                iStack_54 = iStack_44 + iVar19 * 5;
                iVar17 = iVar19 * 7;
                psVar16[1] = (int16_t)(iStack_50 + iVar21 * 3);
                iStack_50 = iStack_40 + iVar21 * 5;
                iVar12 = iVar21 * 7;
                psVar16[2] = (int16_t)(iStack_4c + iVar13 * 3);
                iStack_4c = iStack_3c + iVar13 * 5;
                puStack_5c = puStack_5c + iStack_38;
                iVar14 = iVar13 * 7;
                pbVar11 = pbVar11 + stride;
                psVar16 = psVar16 + stride;
                iStack_3c = iVar13;
                iStack_40 = iVar21;
                iStack_44 = iVar19;
            }
            piStack_48 = piStack_48 + 1;
            *psVar16 = (int16_t)iStack_54;
            psVar16[1] = (int16_t)iStack_50;
            iStack_24 = iStack_24 - 1;
            psVar16[2] = (int16_t)iStack_4c;
        } while (iStack_24 != 0);
    }
    return;
}

// ---------------------------------------------------------------------------
// @ 0x008664e0
// Build the range-limit table: allocate 0x7fc bytes, bias the base by +0x3fc,
// then fill three runs of 32-bit entries (0..0x0f mirrored, 0x10..0x2f with the
// alternating increment, 0x30..0xff at the running value) whose negative
// counterparts are written at the mirrored negative index.
// ---------------------------------------------------------------------------
void FUN_008664e0(Obj* self)
{
    Ctx* c;
    int* piVar2;
    int* piVar5;
    int iVar1;
    int iVar4;
    uint32_t uVar3;

    c = self->ctx;
    piVar2 = (int*)((char*)((AFn)self->alloc[0])(self, 1, 0x7fc) + 0x3fc);
    c->f28 = piVar2;
    iVar4 = 0;
    uVar3 = 0;
    iVar1 = 0;
    piVar5 = piVar2;
    do {
        piVar2[uVar3] = iVar4;
        *piVar5 = iVar1;
        uVar3 = uVar3 + 1;
        piVar5 = piVar5 + -1;
        iVar4 = iVar4 + 1;
        iVar1 = iVar1 + -1;
    } while ((int)uVar3 < 0x10);
    if ((int)uVar3 < 0x30) {
        piVar5 = piVar2 + -uVar3;
        do {
            piVar2[uVar3] = iVar4;
            *piVar5 = -iVar4;
            uVar3 = uVar3 + 1;
            piVar5 = piVar5 + -1;
            iVar4 = iVar4 + (~uVar3 & 1);
        } while ((int)uVar3 < 0x30);
    }
    if ((int)uVar3 <= 0xff) {
        piVar5 = piVar2 + -uVar3;
        do {
            piVar2[uVar3] = iVar4;
            *piVar5 = -iVar4;
            uVar3 = uVar3 + 1;
            piVar5 = piVar5 + -1;
        } while ((int)uVar3 <= 0xff);
    }
    return;
}

// ---------------------------------------------------------------------------
// @ 0x00866580
// Publish the current multi-scan width (ctx+0x10) into this+0x88, hand this'
// scan-counter (ctx+0x14) back to FUN_00865c50 and mark ctx+0x1c.
// ---------------------------------------------------------------------------
void FUN_00866580(Obj* self)
{
    Ctx* c = self->ctx;

    self->f88 = (int*)c->f10;
    FUN_00865c50(c->f14);
    c->f1c = 1;
    return;
}

// ---------------------------------------------------------------------------
// @ 0x008665b0
// Select the per-frame conversion routine (multi-scan FUN_00866220 / single-scan
// FUN_00866160) plus its output routine, bound the component count, size the
// sample buffer from the row width and, when a new scan begins, zero the whole
// row-buffer ring.
// ---------------------------------------------------------------------------
void FUN_008665b0(Obj* self, int param_2)
{
    Ctx* c;
    int iVar4;

    c = self->ctx;
    if (self->f58 != 0) {
        self->f58 = 2;
    }
    if (param_2 == 0) {
        if (self->f58 == 2) {
            c->f04 = (void*)&FUN_00866220;
        } else {
            c->f04 = (void*)&FUN_00866160;
        }
        c->f08 = (void*)0xc2e4e0;
        iVar4 = self->f84;
        if (iVar4 < 1) {
            *(int*)((char*)self->m00 + 0x14) = 0x37;
            *(int*)((char*)self->m00 + 0x18) = 1;
            ((void(__cdecl*)(void*))self->m00[0])(self);
        }
        if (0x100 < iVar4) {
            *(int*)((char*)self->m00 + 0x14) = 0x38;
            *(int*)((char*)self->m00 + 0x18) = 0x100;
            ((void(__cdecl*)(void*))self->m00[0])(self);
        }
        if (self->f58 == 2) {
            iVar4 = (self->f70 + 2) * 6;
            if (c->f20 == 0) {
                c->f20 = (int*)((AFn)self->alloc[1])(self, 1, iVar4);
            }
            FUN_008668f0(c->f20, iVar4);
            if (c->f28 == 0) {
                FUN_008664e0(self);
            }
            c->f24 = 0;
        }
    } else {
        c->f04 = (void*)&FUN_008654f0;
        c->f08 = (void*)&FUN_00866580;
        c->f1c = 1;
    }
    if (c->f1c != 0) {
        iVar4 = 0;
        do {
            FUN_008668f0((void*)c->f18[iVar4], 0x1000);
            iVar4 = iVar4 + 1;
        } while (iVar4 < 0x20);
        c->f1c = 0;
    }
    return;
}

// ---------------------------------------------------------------------------
// @ 0x008666e0
// ---------------------------------------------------------------------------
void FUN_008666e0(Obj* self)
{
    self->ctx->f1c = 1;
    return;
}

// ---------------------------------------------------------------------------
// @ 0x00866700
// Create the auxiliary state block (0x2c bytes), install the entry routines,
// allocate the 0x20-entry row-buffer ring and the sample buffer, size the
// component buffer, and when a multi-scan pass is active allocate the sample
// buffer and build the range-limit table.
// ---------------------------------------------------------------------------
void FUN_00866700(Obj* self)
{
    Ctx* c;
    int iVar3;

    c = (Ctx*)((AFn)self->alloc[0])(self, 1, 0x2c);
    self->ctx = c;
    c->f00 = (void*)&FUN_008665b0;
    c->f0c = (void*)&FUN_008666e0;
    c->f20 = 0;
    c->f28 = 0;
    if (self->f78 != 3) {
        *(int*)((char*)self->m00 + 0x14) = 0x2e;
        ((void(__cdecl*)(void*))self->m00[0])(self);
    }
    c->f18 = (uint32_t*)((AFn)self->alloc[0])(self, 1, 0x80);
    iVar3 = 0;
    do {
        *(void**)((char*)c->f18 + iVar3) = (void*)((AFn)self->alloc[1])(self, 1, 0x1000);
        iVar3 = iVar3 + 4;
    } while (iVar3 < 0x80);
    c->f1c = 1;
    if (self->f6c == 0) {
        c->f10 = 0;
    } else {
        iVar3 = self->f60;
        if (iVar3 < 8) {
            *(int*)((char*)self->m00 + 0x14) = 0x37;
            *(int*)((char*)self->m00 + 0x18) = 8;
            ((void(__cdecl*)(void*))self->m00[0])(self);
        }
        if (0x100 < iVar3) {
            *(int*)((char*)self->m00 + 0x14) = 0x38;
            *(int*)((char*)self->m00 + 0x18) = 0x100;
            ((void(__cdecl*)(void*))self->m00[0])(self);
        }
        c->f10 = (int)((AFn3)self->alloc[2])(self, 1, iVar3, 3);
        c->f14 = iVar3;
    }
    if (self->f58 != 0) {
        self->f58 = 2;
    }
    if (self->f58 == 2) {
        c->f20 = (int*)((AFn)self->alloc[1])(self, 1, (self->f70 + 2) * 6);
        FUN_008664e0(self);
        return;
    }
    return;
}

// ---------------------------------------------------------------------------
// @ 0x00866b80
// lib_zlib::crc32_little -- CRC-32 (reflected, poly 0xEDB88320) over `len`
// bytes, four-table implementation.  The original passes the running CRC in eax
// and (buf, len) in ecx/edx.
// ---------------------------------------------------------------------------
uint32_t crc32_little(uint32_t crc, const uint8_t* buf, uint32_t len)
{
    uint32_t c = ~crc;

    while (len != 0 && (((uintptr_t)buf & 3) != 0)) {
        c = (c >> 8) ^ g_0141e9c0[(*buf ^ c) & 0xff];
        buf++;
        len--;
    }
    while (len >= 0x20) {
        uint32_t n = len >> 5;
        do {
            c = c ^ *(const uint32_t*)buf;
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            len -= 0x20;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff]);
            n--;
        } while (n != 0);
    }
    while (len >= 4) {
        uint32_t n = len >> 2;
        do {
            c = c ^ *(const uint32_t*)buf;
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff]);
            len -= 4;
            n--;
        } while (n != 0);
    }
    while (len != 0) {
        c = (c >> 8) ^ g_0141e9c0[(*buf ^ c) & 0xff];
        buf++;
        len--;
    }
    return ~c;
}

// ---------------------------------------------------------------------------
// @ 0x00866eb0
// Refill the destination cursor from the source cursor: memcpy the smaller of
// the two remaining counts, advance both cursors and both remaining counters,
// and when the source is exhausted rewind its cursor to its base.
// ---------------------------------------------------------------------------
void FUN_00866eb0(Buf* buf)
{
    Src* src;
    uint32_t size;

    src = buf->f1c;
    size = (uint32_t)src->f14;
    if ((uint32_t)buf->f10 < size) {
        size = (uint32_t)buf->f10;
    }
    if (size != 0) {
        memcpy(buf->f0c, src->f10, size);
        buf->f0c = (char*)buf->f0c + size;
        src = buf->f1c;
        src->f10 = (char*)src->f10 + size;
        buf->f14 = buf->f14 + (int)size;
        buf->f10 = buf->f10 - (int)size;
        src = buf->f1c;
        src->f14 = src->f14 - (int)size;
        src = buf->f1c;
        if (src->f14 == 0) {
            src->f10 = src->f08;
        }
    }
    return;
}
