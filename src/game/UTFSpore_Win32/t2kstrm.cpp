// src/game/UTFSpore_Win32/t2kstrm.cpp -- migrated from slice(s) s008cb7f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2kstrm.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int setjmp3(void* buf, int unused);                                                   // 0x011e0cac
extern "C" void* memcpy(void* dst, const void* src, unsigned int count);                         // 0x011e0744

// ---- items of slice s008cb7f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef int8_t int8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;
struct tsiMemObject {
    uint8 pad00[0x54];
    void* base54;           // +0x54
    void* stream58;         // +0x58 (stream that owns +0x90)
    uint8 pad5c[0x8c - 0x5c];
    int32 flag8c;           // +0x8c
    int32 flag90;           // +0x90
};
typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);
struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x204];           // +0x00c (byte cache lives at +0x00d)
    uint32 pendingCount;           // +0x210 (bytes left after the primed block)
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 streamEnd;              // +0x220
    uint32 baseOffset;             // +0x224
    uint8 kind;                    // +0x228
    uint8 pad229[3];               // +0x229
    tsiMemObject* mem;             // +0x22c
    uint32 field230;               // +0x230
    uint32 field234;               // +0x234
    uint8 field238;                // +0x238
    uint8 pad239[3];               // +0x239
};
extern "C" void tsi_Error(tsiMemObject* mem, int32 errCode);                                    // 0x008d10c0
extern "C" void tsi_DeAllocMem(tsiMemObject* mem, void* p);                                     // 0x008d1440
extern "C" __declspec(noinline) int32 PrimeT2KInputStream(InputStream* in);                     // 0x008cc0b0
extern "C" uint32 Tell_InputStream(InputStream* in);                                            // 0x008cc5b0
extern "C" void Seek_InputStream(InputStream* in, uint32 pos);                                  // 0x008cc580
extern "C" InputStream* New_InputStream2(tsiMemObject* mem, InputStream* in, uint32 offset, uint32 length,
int32 unused, int* errCode);                           // 0x008cc330
extern "C" void Delete_InputStream(InputStream* t, int* errCode);                               // 0x008cc5d0
#define T2K_ERR_TRANS_FAIL 10024
struct T2KMemHeader {                   // 0x14 bytes
    tsiMemObject* mem;                  // +0x00
    int16 flags04;                      // +0x04
    int16 flags06;                      // +0x06
    int16 value08;                      // +0x08
    int16 value0a;                      // +0x0a
    int16 value0c;                      // +0x0c
    int16 value0e;                      // +0x0e
    int16 value10;                      // +0x10
    int16 pad12;                        // +0x12
};
extern "C" void* tsi_AllocMem(tsiMemObject* mem, int32 size);                                    // 0x008d1260
extern "C" void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 align);                     // 0x008d14d0
extern "C" void tsi_EmergencyShutDown(tsiMemObject* mem);                                        // 0x008d1210
extern "C" int setjmp3(void* buf, int unused);                                                   // 0x011e0cac
extern "C" void* memcpy(void* dst, const void* src, unsigned int count);                         // 0x011e0744
extern "C" void PreLoadT2KInputStream(InputStream* in, int32 length);                            // 0x008cc040
extern "C" uint32 ReadInt32(InputStream* in);                                                    // 0x008cc0f0
extern "C" uint16 ReadInt16(InputStream* in);                                                    // 0x008cc190
extern "C" void PeekInt16(InputStream* in, void* dest, int32 count);                             // 0x008cc220
extern "C" int32 GetStreamLength(InputStream* in);                                               // 0x008cc2a0
extern "C" int32 GetEntireStreamIntoMemory(InputStream* in);                                     // 0x008cc2c0
extern "C" InputStream* New_InputStream4(tsiMemObject* mem, void* base, uint32 end, int* errCode);  // 0x008cc410
extern "C" InputStream* New_NonRamInputStream(tsiMemObject* mem, PF_READ_TO_RAM readToRam, void* id,
uint32 end, int* errCode);                         // 0x008cc4b0
extern "C" void Rewind_InputStream(InputStream* in);                                             // 0x008cc550
extern "C" T2KMemHeader* New_T2KMemHeader(tsiMemObject* mem, InputStream* in, int32 count);      // 0x008cbf10
extern "C" uint32 ReadUnsignedNumber(InputStream* in);                                           // 0x008cc670
void PreLoadT2KInputStream(InputStream* in, int32 length);  // 0x008cc040 (defined below; used by a stub's inline body)
static __inline void PrimeStreamInline(InputStream* in)
{
    int32 remaining = (int32)(in->streamEnd - in->pos);
    int32 n = remaining;
    if (n > 8)
        n = 8;
    if ((int32)in->pendingCount > n)
        n = (int32)in->pendingCount;
    if (n > remaining)
        n = remaining;
    PreLoadT2KInputStream(in, n);
}
// ---- items of slice s008cb7f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void tsi_Error(tsiMemObject* mem, int32 errCode);                                    // 0x008d10c0
extern "C" void tsi_DeAllocMem(tsiMemObject* mem, void* p);                                     // 0x008d1440
extern "C" __declspec(noinline) int32 PrimeT2KInputStream(InputStream* in);                     // 0x008cc0b0
extern "C" uint32 Tell_InputStream(InputStream* in);                                            // 0x008cc5b0
extern "C" void Seek_InputStream(InputStream* in, uint32 pos);                                  // 0x008cc580
extern "C" InputStream* New_InputStream2(tsiMemObject* mem, InputStream* in, uint32 offset, uint32 length,
int32 unused, int* errCode);                           // 0x008cc330
extern "C" void Delete_InputStream(InputStream* t, int* errCode);                               // 0x008cc5d0
extern "C" void* tsi_AllocMem(tsiMemObject* mem, int32 size);                                    // 0x008d1260
extern "C" void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 align);                     // 0x008d14d0
extern "C" void tsi_EmergencyShutDown(tsiMemObject* mem);                                        // 0x008d1210
extern "C" void PreLoadT2KInputStream(InputStream* in, int32 length);                            // 0x008cc040
extern "C" uint32 ReadInt32(InputStream* in);                                                    // 0x008cc0f0
extern "C" uint16 ReadInt16(InputStream* in);                                                    // 0x008cc190
extern "C" void PeekInt16(InputStream* in, void* dest, int32 count);                             // 0x008cc220
extern "C" int32 GetStreamLength(InputStream* in);                                               // 0x008cc2a0
extern "C" int32 GetEntireStreamIntoMemory(InputStream* in);                                     // 0x008cc2c0
extern "C" InputStream* New_InputStream4(tsiMemObject* mem, void* base, uint32 end, int* errCode);  // 0x008cc410
extern "C" InputStream* New_NonRamInputStream(tsiMemObject* mem, PF_READ_TO_RAM readToRam, void* id,
uint32 end, int* errCode);                         // 0x008cc4b0
extern "C" void Rewind_InputStream(InputStream* in);                                             // 0x008cc550
extern "C" T2KMemHeader* New_T2KMemHeader(tsiMemObject* mem, InputStream* in, int32 count);      // 0x008cbf10
extern "C" uint32 ReadUnsignedNumber(InputStream* in);                                           // 0x008cc670

// @ 0x008cbf10
T2KMemHeader* New_T2KMemHeader(tsiMemObject* mem, InputStream* in, int32 count)
{
    T2KMemHeader* h = (T2KMemHeader*)tsi_AllocMem(mem, 0x14);
    h->flags04 = 0;
    h->flags06 = 0;
    h->value08 = 1;
    h->value0a = 2;
    h->mem = mem;
    h->value0c = 10;
    h->value0e = 0;
    h->value10 = 0;
    if (in != 0) {
        h->flags04 = (int16)ReadInt16(in);
        h->flags06 = (int16)ReadInt16(in);
        if (h->flags04 == 1 && count > 4) {
            int32 n = (int32)(((uint32)(count - 5) >> 2) + 1);
            do {
                int16 tag = (int16)ReadInt16(in);
                int16 value = (int16)ReadInt16(in);
                switch (tag) {
                case 0:
                    h->value08 = value;
                    break;
                case 1:
                    h->value0a = value;
                    break;
                case 2:
                    h->value0c = value;
                    break;
                case 3:
                    h->value0e = value;
                    break;
                case 4:
                    h->value10 = value;
                    break;
                }
                n--;
            } while (n != 0);
        }
    }
    h->value0a = (int16)(h->value0a * 8);
    h->value0c = (int16)(h->value0c * 8);
    return h;
}

// @ 0x008cc040
void PreLoadT2KInputStream(InputStream* in, int32 length)
{
    PF_READ_TO_RAM func = in->ReadToRamFunc;
    if (func != 0) {
        uint32 pos = in->pos;
        int32 got = 0x200;
        if (length < got)
            got = length;
        in->pendingCount = (uint32)(length - got);
        in->privateBase = in->tmp_ch + 1;
        int r = func(in->nonRamID, in->privateBase, (int32)pos, got);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        in->cacheCount = (uint32)got;
        in->posZero = in->pos;
    }
}

// @ 0x008cc0b0
int32 PrimeT2KInputStream(InputStream* in)
{
    int32 remaining = (int32)(in->streamEnd - in->pos);
    int32 n = remaining;
    if (n > 8)
        n = 8;
    if ((int32)in->pendingCount > n)
        n = (int32)in->pendingCount;
    if (n > remaining)
        n = remaining;
    PreLoadT2KInputStream(in, n);
    return 0;
}

// @ 0x008cc0f0
uint32 ReadInt32(InputStream* in)
{
    uint32 pos = in->pos;
    uint8* p = in->privateBase;
    if (p != 0) {
        uint32 off = pos;
        if (in->ReadToRamFunc != 0) {
            if (pos - in->posZero + 4 > in->cacheCount)
                PrimeT2KInputStream(in);
            off = pos - in->posZero;
        }
        p += off;
    } else {
        uint32 buf;
        p = (uint8*)&buf;
        int r = in->ReadToRamFunc(in->nonRamID, p, (int32)pos, 4);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    }
    in->pos = pos + 4;
    uint32 v = p[0];
    v = (v << 8) | p[1];
    v = (v << 8) | p[2];
    v = (v << 8) | p[3];
    return v;
}

// @ 0x008cc190
uint16 ReadInt16(InputStream* in)
{
    uint32 pos = in->pos;
    uint8* p = in->privateBase;
    if (p != 0) {
        uint32 off = pos;
        if (in->ReadToRamFunc != 0) {
            if (pos - in->posZero + 2 > in->cacheCount)
                PrimeT2KInputStream(in);
            off = pos - in->posZero;
        }
        p += off;
    } else {
        uint16 buf;
        p = (uint8*)&buf;
        int r = in->ReadToRamFunc(in->nonRamID, p, (int32)pos, 2);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    }
    in->pos = pos + 2;
    uint16 v = p[0];
    v <<= 8;
    v |= p[1];
    return v;
}

// @ 0x008cc220
void PeekInt16(InputStream* in, void* dest, int32 count)
{
    if (count <= 0)
        return;
    uint32 pos = in->pos;
    if (in->ReadToRamFunc != 0) {
        int r = in->ReadToRamFunc(in->nonRamID, (uint8*)dest, (int32)pos, count);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    } else {
        memcpy(dest, in->privateBase + pos, (uint32)count);
    }
    pos += (uint32)count;
    if (pos > in->streamEnd)
        tsi_Error(in->mem, 0x2729);
    in->pos = pos;
}

// @ 0x008cc2a0
int32 GetStreamLength(InputStream* in)
{
    return (int32)(in->streamEnd - in->baseOffset);
}

// @ 0x008cc2c0
int32 GetEntireStreamIntoMemory(InputStream* in)
{
    if (in->privateBase == 0 && in->ReadToRamFunc != 0) {
        in->kind = 1;
        uint8* base = (uint8*)tsi_AllocMem(in->mem, (int32)in->streamEnd);
        in->privateBase = base;
        int r = in->ReadToRamFunc(in->nonRamID, base, 0, (int32)in->streamEnd);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    }
    return (int32)(in->baseOffset + (uint32)in->privateBase);
}

// @ 0x008cc330
#pragma optimize("y", off)
InputStream* New_InputStream2(tsiMemObject* mem, InputStream* src, uint32 offset, uint32 length, int32 unused, int* errCode)
{
    if (errCode != 0) {
        int r = setjmp3((uint8*)mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return 0;
        }
    }
    InputStream* in = unused != 0 ? (InputStream*)tsi_FastAllocN(mem, 0x23c, 2)
                                  : (InputStream*)tsi_AllocMem(mem, 0x23c);
    in->mem = mem;
    in->privateBase = src->privateBase;
    in->ReadToRamFunc = src->ReadToRamFunc;
    in->nonRamID = src->nonRamID;
    in->cacheCount = 0;
    in->posZero = 0;
    uint32 base = src->baseOffset + offset;
    in->baseOffset = base;
    in->pos = base;
    in->streamEnd = base + length;
    in->field230 = 0;
    in->field234 = 0;
    in->kind = 2;
    in->field238 = 0;
    PreLoadT2KInputStream(in, (int32)length);
    return in;
}

// @ 0x008cc410
InputStream* New_InputStream4(tsiMemObject* mem, void* base, uint32 end, int* errCode)
{
    if (errCode != 0) {
        int r = setjmp3((uint8*)mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return 0;
        }
    }
    InputStream* in = (InputStream*)tsi_AllocMem(mem, 0x23c);
    in->mem = mem;
    in->ReadToRamFunc = 0;
    in->nonRamID = 0;
    in->cacheCount = 0;
    in->posZero = 0;
    in->pos = 0;
    in->baseOffset = 0;
    in->field230 = 0;
    in->field234 = 0;
    in->field238 = 0;
    in->privateBase = (uint8*)base;
    in->streamEnd = end;
    in->kind = 4;
    return in;
}

// @ 0x008cc4b0
InputStream* New_NonRamInputStream(tsiMemObject* mem, PF_READ_TO_RAM readToRam, void* id, uint32 end, int* errCode)
{
    if (errCode != 0) {
        int r = setjmp3((uint8*)mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return 0;
        }
    }
    InputStream* in = (InputStream*)tsi_AllocMem(mem, 0x23c);
    in->mem = mem;
    in->ReadToRamFunc = readToRam;
    in->privateBase = 0;
    in->cacheCount = 0;
    in->posZero = 0;
    in->pos = 0;
    in->baseOffset = 0;
    in->field230 = 0;
    in->field234 = 0;
    in->field238 = 0;
    in->nonRamID = id;
    in->streamEnd = end;
    in->kind = 4;
    return in;
}
#pragma optimize("y", on)

// @ 0x008cc550
void Rewind_InputStream(InputStream* in)
{
    in->pos = in->baseOffset;
    if (in->baseOffset < in->posZero) {
        in->cacheCount = 0;
        in->posZero = 0;
    }
}

// @ 0x008cc580
void Seek_InputStream(InputStream* in, uint32 offset)
{
    uint32 p = offset;
    p += in->baseOffset;
    in->pos = p;
    if (p < in->posZero) {
        in->cacheCount = 0;
        in->posZero = 0;
    }
}

// @ 0x008cc5b0
uint32 Tell_InputStream(InputStream* in)
{
    return in->pos - in->baseOffset;
}
#pragma optimize("y", off)

// @ 0x008cc5d0
void Delete_InputStream(InputStream* in, int* errCode)
{
    if (in == 0)
        return;
    if (errCode != 0) {
        int r = setjmp3((uint8*)in->mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(in->mem);
            return;
        }
    }
    if (in->kind == 1) {
        tsi_DeAllocMem(in->mem, in->privateBase);
        tsi_DeAllocMem(in->mem, in);
        return;
    }
    tsiMemObject* mem = in->mem;
    if (in == (InputStream*)mem->stream58) {
        mem->flag90 = 1;
        return;
    }
    tsi_DeAllocMem(mem, in);
}
#pragma optimize("y", on)

// @ 0x008cc670
uint32 ReadUnsignedNumber(InputStream* in)
{
    uint32 acc = 0;
    int32 shift = 0;
    for (;;) {
        uint8 b;
        if (in->privateBase == 0) {
            uint32 pos = in->pos;
            in->pos = pos + 1;
            int r = in->ReadToRamFunc(in->nonRamID, in->tmp_ch, (int32)pos, 1);
            if (r < 0) {
                tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
                b = 0;
            } else {
                b = in->tmp_ch[0];
            }
        } else if (in->ReadToRamFunc == 0) {
            b = in->privateBase[in->pos++];
        } else {
            if (in->pos - in->posZero + 1 > in->cacheCount)
                PrimeStreamInline(in);
            b = in->privateBase[in->pos - in->posZero];
            in->pos++;
        }
        acc |= (uint32)(b & 0x7f) << shift;
        shift += 7;
        if ((int8)b >= 0)
            return acc;
    }
}
