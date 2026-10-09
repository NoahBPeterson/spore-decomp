// RenderWare 4 rwaudio core: WAVE player / decode-buffer pipeline (prebuilt MSVC library
// code inside SporeApp.exe). Built with VC .NET 2003 (cl 13.10) + /LTCG; object-heavy, so
// behaviour-equivalent source where achievable, otherwise approximate.
// compile with /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;

// Original converts float->int with the round-to-nearest `cvtss2si` opcode (not the
// truncating `cvttss2si` a plain C `(int)` cast emits). The conversion goes through a
// memory operand because the source used an asm helper; reproduce that shape.
static inline int RoundToInt(float f)
{
    int r;
    __asm {
        cvtss2si eax, f
        mov r, eax
    }
    return r;
}

namespace rw { namespace audio { namespace core {

struct System;
extern System* g_pAudioSystem; // 0x016e61a8

struct System
{
    u8 pad0[0xa8];
    void* mpAssertHandler;      // +0xa8
    void* mGetCsisLibraryType;  // +0xac
    u8 pad1[0x34];
    u32  mCommandIndex;         // +0xe0 (approx)
    void* Alloc(int size, const char* name, int align, int a5); // 0x0112c820
    void  Free(void* p, int a3);                                // 0x0112c850
};

// Stream::ReleaseChunk is a __thiscall method (ecx = stream, one stack arg) at 0x011e7c70.
struct Stream { void ReleaseChunk(void* chunk); };                            // 0x011e7c70

// The sound player the WAVE pump submits packets to (called via its vtable; slots 0 and 1).
struct SndPlayer
{
    virtual void SubmitPacket(int param, unsigned len, unsigned blocks);      // vt[0]
    virtual void SubmitOffsets(unsigned* offsets, unsigned blocks);           // vt[1]
};

// SNDPKTPLAY_submit reads count at +4 and the per-channel offset table at +0xc.
struct SndPacket
{
    u32 header0;      // +0x0
    u32 count;        // +0x4 (blocks | 0x80000000)
    u32 header8;      // +0x8
    u32 data[8];      // +0xc
};

// Decoder / plug-in helpers (sibling TU).
void  FUN_01132fe0(void* p);                       // 0x01132fe0
void  FUN_0113fca0(void* p);                       // 0x0113fca0
void* FUN_0113f1c0(int size);                      // 0x0113f1c0
u32   FUN_0113f1d0(void* fn, int a2, int a3, int a4, u32 a5); // 0x0113f1d0
u32   FUN_0113f250(u32 a1, void* a2, void* a3, void* a4);      // 0x0113f250
int   FUN_0113fba0(u32 decoder, int value);        // 0x0113fba0
int   FUN_011402c0(int size);                      // 0x011402c0
u32   FUN_0113fb00();                              // 0x0113fb00
u32   FUN_0113fa50();                              // 0x0113fa50
u32   FUN_0113fdd0(u32 decoder, int index, int value); // 0x0113fdd0
u32   FUN_0113ff00(u32 decoder, int value);        // 0x0113ff00
int   FUN_0113f9b0(u32 decoder);                   // 0x0113f9b0
int   FUN_0113f750(u32 decoder);                   // 0x0113f750
int   FUN_01140110(int base, int tag, int limit);  // 0x01140110
int   FUN_0113fb50(int a1);                        // 0x0113fb50
void  FUN_0112eab0(int p);                         // 0x0112eab0
void  FUN_0112eb70(int id, int p);                 // 0x0112eb70
void  FUN_0112eeb0(int p, int* d);                 // 0x0112eeb0
void  FUN_0112fa50(int* p, int a, u32 b, int c, u8 d); // 0x0112fa50
int __fastcall Stream_GetChunk(void* stream);      // rw::core::filesys::Stream::GetChunk
void __fastcall FUN_011e7c70(void* p);             // 0x011e7c70
void  SNDPKTPLAY_submit(int a, void* b);           // external

// The external sample data table 0x014cafd2 (channel order remap).
extern const unsigned char g_channelOrder[]; // 0x014cafd2

// @ 0x0112ebf0 -- WAVE decode-buffer/timer setup (called from the player init).
void FUN_0112ebf0(int p)
{
    u32 uVar4 = (u32)FUN_0113f1c0(0xc);
    u8* puVar1 = (u8*)(p + 0x18);
    FUN_01132fe0(puVar1);
    FUN_0113fca0((char*)p + 0x28);

    int buf = (int)g_pAudioSystem->Alloc(0x4000, "Wave Player decode buffers", 0x10, 0);
    *(int*)(p + 200) = buf;
    *(int*)(p + 0xcc) = buf + 0x1000;
    *(int*)(p + 200) = buf;
    *(int*)(p + 0xe8) = 0;
    *(int*)(p + 0xd8) = 0;
    *(int*)(p + 0xec) = 0;
    *(int*)(p + 0xdc) = 0;
    *(int*)(p + 0xd0) = buf + 0x2000;
    *(int*)(p + 0xf0) = 0;
    *(int*)(p + 0xe0) = 0;
    *(int*)(p + 0xd4) = buf + 0x3000;
    *(int*)(p + 0xf4) = 0;
    *(int*)(p + 0xe4) = 0;

    uVar4 = FUN_0113f1d0((void*)&FUN_0112eb70, 0, p, p + 0xf8, uVar4);
    *(int*)(p + 0xa0) = (int)uVar4;
    *(u8*)(p + 0x8f) = 8;
    *(u16*)(p + 0x8c) = *(u16*)(p + 0xbc);
    *(u8*)(p + 0x2d) = 0x7f;
    *(short*)(p + 0xc2) = (short)(*(short*)(p + 0xc2) / *(short*)(p + 0xc0));
    *(u8*)(p + 0x8e) = *(u8*)(p + 0xc0);

    *(char*)puVar1 = (char)(int)(**(f32**)(p + 0x14) * 127.0f);
    *(short*)(p + 0x20) = (short)(int)(*(f32*)(*(int*)(p + 0x14) + 4) * 4096.0f);
    *(char*)(p + 0x1b) = (char)(int)(*(f32*)(*(int*)(p + 0x14) + 8) * 127.0f);
    *(short*)(p + 0x24) = (short)(int)(*(f32*)(*(int*)(p + 0x14) + 0x10));
    *(short*)(p + 0x26) = (short)(int)(*(f32*)(*(int*)(p + 0x14) + 0x14));
    *(char*)(p + 0x1c) = (char)(int)(**(f32**)(*(int*)(p + 0x14) + 0xc) * 127.0f);

    u8 bVar2 = *(u8*)(p + 0x8e);
    for (int i = 0; i < (int)bVar2; ++i)
        *(short*)(p + 0x30 + i * 2) = (u16)(g_channelOrder[i + (u32)bVar2 * 6] << 8);

    uVar4 = FUN_0113f250(*(u32*)(p + 0xa0), (void*)(p + 0x8c), (void*)(p + 0x28), puVar1);
    *(int*)(p + 0xa4) = (int)uVar4;

    if (*(int*)(p + 0xc) == 1)
        FUN_0113fba0(uVar4, 0);

    short sVar3 = *(short*)(p + 0xc2);
    if (sVar3 == 1) goto LAB_ee5f;
    if (sVar3 == 2)
    {
        int iVar5 = FUN_011402c0(0x18);
        if (iVar5 == 0) { uVar4 = 0; }
        else { uVar4 = FUN_0113fb00(); }
    }
    else if (sVar3 == 3)
    {
        int iVar5 = FUN_011402c0(0x18);
        if (iVar5 == 0) goto LAB_ee57;
        uVar4 = FUN_0113fa50();
    }
    else
    {
        goto LAB_ee5f;
    }
    *(int*)(p + 0xac) = (int)uVar4;
    {
        int vt = *(int*)(p + 0xac);
        (*(void(**)(void*))(*(int*)vt + 8))((void*)(p + 0xc0));
    }
    {
        u32 uVar7 = *(u32*)(p + 0xa8);
        int iVar5 = 0, iVar8 = 0;
        do
        {
            if ((u32)(*(int*)(p + 0x98) - iVar8) <= uVar7) return;
            FUN_0112eab0(p);
            uVar7 = *(u32*)(p + 0xa8);
            *(int*)(p + 0x9c) += uVar7;
            ++iVar5;
            iVar8 += uVar7;
        } while (iVar5 < 4);
    }
    return;
LAB_ee57:
    *(int*)(p + 0xac) = 0;
LAB_ee5f:
    *(int*)(p + 0xac) = (int)uVar4;
    {
        int vt = *(int*)(p + 0xac);
        (*(void(**)(void*))(*(int*)vt + 8))((void*)(p + 0xc0));
    }
    return;
}

// @ 0x0112eeb0 -- WAVE packet submit (gain table + sound player).
void FUN_0112eeb0(int id, int* d)
{
    int i = 0;
    int* q = d + 0x32;
    while (i < 4)
    {
        if (id == *q) break;
        ++i;
        ++q;
    }
    d[0x31] -= 1;
    if (*d < d[0x26] && (u32)d[0x24] != 0)
    {
        u32 uVar7 = (u32)d[0x2a];
        unsigned ch = *(u16*)((char*)d + 0xc2);
        if ((short)ch < 2) uVar7 = uVar7 >> 1;
        if (uVar7 > (u32)d[0x24]) uVar7 = (u32)d[0x24];
        int n = (short)d[0x30];
        unsigned blocks = uVar7 / (u32)(n * (int)(short)ch);

        SndPlayer* player = (SndPlayer*)d[0x2b];
        player->SubmitPacket(d[0x27], uVar7, blocks);

        int base = d[0x32 + i];
        unsigned vals[8];
        SndPacket pkt;
        int step = n ? (0x4000 / (n * 4)) : 0;
        for (int k = 0; k < n; ++k)
        {
            vals[k] = (unsigned)base;
            pkt.data[k] = (unsigned)base;
            base += step;
        }
        player->SubmitOffsets(vals, blocks);
        pkt.count = blocks | 0x80000000u;
        SNDPKTPLAY_submit(d[0x28], &pkt);
        d[1] += uVar7;
        d[2] += blocks;
        *d += uVar7;
        d[0x27] += uVar7;
        d[0x31] += 1;
        d[0x24] -= uVar7;
        return;
    }
    if (d[0x31] == 0 && d[0x24] == 0) d[3] = 3;
}

// @ 0x0112f080 -- set a plug-in parameter from a scaled float table entry.
int FUN_0112f080(int p, int index, int obj)
{
    FUN_0113fdd0(*(u32*)(obj + 0xa4), index,
                 RoundToInt(*(f32*)(*(int*)(p + 0xc) + index * 4) * 127.0f));
    return 0;
}

// @ 0x0112f0c0 -- start playback (state 1).
int FUN_0112f0c0(int p)
{
    FUN_0113fba0(*(u32*)(p + 0xa4), 0);
    *(int*)(p + 0xc) = 1;
    return 0;
}

// @ 0x0112f0f0 -- stop playback (state 0) with the current gain.
int FUN_0112f0f0(int p, int obj)
{
    FUN_0113fba0(*(u32*)(obj + 0xa4), RoundToInt(*(f32*)(p + 4) * 4096.0f));
    *(int*)(obj + 0xc) = 0;
    return 0;
}

// @ 0x0112f130 -- WAVE player shutdown/release.
int FUN_0112f130(int p)
{
    if (p != 0)
    {
        *(int*)(p + 0xb0) = 0;
        if (*(int*)(p + 0xc) != 2)
        {
            if (*(int*)(p + 0xac) != 0)
            {
                short s = *(short*)(p + 0xc2);
                if (s == 2 || s == 3)
                {
                    int vt = *(int*)(p + 0xac);
                    (*(void(**)(int))(*(int*)vt + 0xc))(1);
                }
                *(int*)(p + 0xac) = 0;
            }
            FUN_0113f9b0(*(u32*)(p + 0xa0));
            FUN_0113f750(*(u32*)(p + 0xa0));
            if (*(int*)(p + 0xb4) != 0 && *(int*)(p + 0xb0) != 0)
            {
                ((Stream*)*(void**)(p + 0x94))->ReleaseChunk(*(void**)(p + 0xb4));
                *(int*)(p + 0xb4) = 0;
            }
            int* q = (int*)(p + 0xe8);
            for (int i = 4; i != 0; --i, ++q)
            {
                if (*q == 1)
                {
                    FUN_0112eb70(q[-8], p);
                    *q = 0;
                }
            }
            if (*(int*)(p + 200) != 0)
            {
                g_pAudioSystem->Free(*(void**)(p + 200), 0);
                *(int*)(p + 200) = 0;
                *(int*)(p + 0xcc) = 0;
                *(int*)(p + 0xd0) = 0;
                *(int*)(p + 0xd4) = 0;
            }
            *(int*)(p + 0xc) = 2;
        }
        g_pAudioSystem->Free((void*)p, 0);
    }
    return 0;
}

// @ 0x0112f230 -- set a plug-in parameter from a scaled float.
int FUN_0112f230(float* p, int obj)
{
    FUN_0113ff00(*(u32*)(obj + 0xa4), RoundToInt(*p * 127.0f));
    return 0;
}

// @ 0x0112f2d0 -- playback progress (looped samples / total), or -1.
int FUN_0112f2d0(int p, float* out)
{
    if ((*(int*)(p + 0x10) != 1) || *(int*)(p + 0xc) == 0 || *(int*)(p + 0xc) == 1)
    {
        int iVar1 = *(int*)(p + 0xb8);
        if (iVar1 != 0)
        {
            f32 a = (f32)iVar1;
            if (iVar1 < 0) a += 4.2949673e+09f;
            f32 b = (f32)*(int*)(p + 0xbc);
            if (*(int*)(p + 0xbc) < 0) b += 4.2949673e+09f;
            *out = a / b;
            return 0;
        }
    }
    *out = -1.0f;
    return 0;
}

// @ 0x0112f340 -- request up to param_2 samples (buffer fill protocol).
int FUN_0112f340(int a1, u32 param_2, int a3, int p, u32* out)
{
    u32 uVar1 = *(u32*)(p + 0x90);
    u32 uVar2 = *(u32*)(p + 0xa8);
    if (uVar2 < uVar1)
    {
        if (uVar2 <= param_2)
        {
            *out = uVar2;
            *(int*)(p + 0x90) -= *(int*)(p + 0xa8);
            if (*(int*)(p + 0xb0) == 0) FUN_0112eab0(p);
            return 1;
        }
    }
    else if (uVar1 <= param_2)
    {
        *out = uVar1;
        *(int*)(p + 0x90) = 0;
        if (*(int*)(p + 0xb0) == 0) FUN_0112eab0(p);
        return 2;
    }
    (void)a1; (void)a3;
    return 0;
}

// @ 0x0112f3c0 -- initialise a WAVE player from an in-memory file image.
int* FUN_0112f3c0(int a1, int fileImage, int size, int a4, int a5, int* outOffset,
                  int a7, int* p)
{
    p[5] = a1;
    *(u16*)(p + 0x30) = 0;
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0x27] = fileImage;
    p[0x26] = size;
    p[3] = 0;
    p[0x2e] = 0;
    p[0x2f] = 0;
    *(u16*)((char*)p + 0xc2) = 0;
    p[0x31] = 0;
    p[0x2d] = 0;
    p[0x25] = a5;
    p[0x2a] = 0;

    int iVar4 = FUN_01140110(fileImage, 0x666d7420, size);
    u16 uVar1 = *(u16*)(iVar4 + 10);
    u32 uVar3 = *(u32*)(iVar4 + 0xc);
    u16 uVar2 = *(u16*)(iVar4 + 0x14);
    *(u8*)((char*)p + 0xc1) = (u8)(uVar1 >> 8);
    *(char*)(p + 0x30) = (char)uVar1;
    *(char*)(p + 0x2f) = (char)uVar3;
    *(u8*)((char*)p + 0xbd) = (u8)(uVar3 >> 8);
    *(u8*)((char*)p + 0xbe) = (u8)(uVar3 >> 0x10);
    *(u8*)((char*)p + 0xbf) = (u8)(uVar3 >> 0x18);
    *(u8*)((char*)p + 0xc2) = (u8)uVar2;
    *(u8*)((char*)p + 0xc3) = (u8)(uVar2 >> 8);
    *(short*)((char*)p + 0xc2) = (short)(*(short*)((char*)p + 0xc2) / *(short*)(p + 0x30));

    iVar4 = FUN_01140110(fileImage, 0x64617461, size);
    uVar3 = *(u32*)(iVar4 + 4);
    *(char*)(p + 0x24) = (char)uVar3;
    *(u8*)((char*)p + 0x91) = (u8)(uVar3 >> 8);
    *(u8*)((char*)p + 0x92) = (u8)(uVar3 >> 0x10);
    *(u8*)((char*)p + 0x93) = (u8)(uVar3 >> 0x18);
    p[0x2e] = (int)((u32)p[0x24] /
                    (u32)((int)*(short*)((char*)p + 0xc2) * (int)*(short*)(p + 0x30)));
    p[0x27] = iVar4 + 8;
    *outOffset = (iVar4 + 8) - fileImage;
    p[4] = 1;
    p[0x2c] = 1;
    p[0x2a] = (int)*(short*)((char*)p + 0xc2) << 0xb;
    return p;
}

// @ 0x0112f550 -- WAVE player Create.
int* FUN_0112f550(int a1, int fileImage, int size)
{
    int iVar8 = (int)FUN_0113f1c0(0xc);
    int* p = (int*)g_pAudioSystem->Alloc(iVar8 + 0xf8, "WAVE Player Instance", 0x10, 0);
    if (!p) return 0;
    p[5] = a1;
    *(u16*)(p + 0x30) = 0;
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0x26] = size;
    p[3] = 0; p[4] = 0;
    p[0x2e] = 0; p[0x2f] = 0;
    *(u16*)((char*)p + 0xc2) = 0;
    p[0x31] = 0; p[0x2d] = 0;
    p[0x24] = size;
    p[0x2c] = 1;
    p[0x25] = 0;
    iVar8 = FUN_0113f1d0((void*)&FUN_0112eeb0, 0, (int)p, (int)(p + 0x3e), (u32)iVar8);
    p[0x28] = iVar8;
    FUN_01132fe0(p + 6);
    FUN_0113fca0(p + 10);

    iVar8 = FUN_01140110(fileImage, 0x666d7420, size);
    u16 uVar3 = *(u16*)(iVar8 + 10);
    u32 uVar6 = *(u32*)(iVar8 + 0xc);
    u16 uVar4 = *(u16*)(iVar8 + 0x14);
    *(u8*)((char*)p + 0xc0) = (u8)uVar3;
    *(u8*)((char*)p + 0xc1) = (u8)(uVar3 >> 8);
    *(u8*)((char*)p + 0xbe) = (u8)(uVar6 >> 0x10);
    *(u8*)((char*)p + 0xbf) = (u8)(uVar6 >> 0x18);
    *(char*)(p + 0x2f) = (char)uVar6;
    *(u8*)((char*)p + 0xbd) = (u8)(uVar6 >> 8);
    *(u8*)((char*)p + 0xc2) = (u8)uVar4;
    *(u8*)((char*)p + 0xc3) = (u8)(uVar4 >> 8);
    *(u8*)((char*)p + 0x8f) = 8;
    *(short*)((char*)p + 0x8c) = (short)p[0x2f];
    *(u8*)((char*)p + 0x2d) = 0x7f;
    *(short*)((char*)p + 0xc2) = (short)(*(short*)((char*)p + 0xc2) / (short)*(u16*)(p + 0x30));
    *(u8*)((char*)p + 0x8e) = (u8)(u16)*(p + 0x30);
    *(char*)(p + 6) = (char)(int)(*(f32*)p[5] * 127.0f);
    *(short*)(p + 8) = (short)(int)(*(f32*)(p[5] + 4) * 4096.0f);
    *(char*)((char*)p + 0x1b) = (char)(int)(*(f32*)(p[5] + 8) * 127.0f);
    *(short*)(p + 9) = (short)(int)(*(f32*)(p[5] + 0x10));
    *(short*)((char*)p + 0x26) = (short)(int)(*(f32*)(p[5] + 0x14));
    *(char*)(p + 7) = (char)(int)(**(f32**)(p[5] + 0xc) * 127.0f);

    u8 bVar2 = *(u8*)((char*)p + 0x8e);
    for (int i = 0; i < (int)bVar2; ++i)
        *(u16*)((char*)p + 0x30 + i * 2) = (u16)(g_channelOrder[i + (u32)bVar2 * 6] << 8);

    iVar8 = FUN_0113f250((u32)p[0x28], p + 0x23, p + 10, p + 6);
    p[0x29] = iVar8;

    iVar8 = FUN_01140110(fileImage, 0x64617461, size);
    uVar6 = *(u32*)(iVar8 + 4);
    *(char*)(p + 0x2e) = (char)uVar6;
    *(u8*)((char*)p + 0xba) = (u8)(uVar6 >> 0x10);
    *(char*)((char*)p + 0xb9) = (char)(uVar6 >> 8);
    *(u8*)((char*)p + 0xbb) = (u8)(uVar6 >> 0x18);
    p[0x27] = iVar8 + 8;
    p[0x2e] = (int)((u32)p[0x2e] /
                    (u32)((int)*(short*)((char*)p + 0xc2) * (int)(short)*(u16*)((char*)p + 0xc0)));
    iVar8 = (int)g_pAudioSystem->Alloc(0x4000, "Wave Player decode buffers", 0x10, 0);
    p[0x32] = iVar8;
    for (int i = 0; i < 0x4000; i += 0x1000)
    {
        int* q = (int*)((char*)p + 0xe8 + i);
        q[-8] = p[0x32] + i;
        *q = 0;
        q[-4] = 0;
    }
    short sVar5 = *(short*)((char*)p + 0xc2);
    p[0x2a] = (int)sVar5 << 0xb;
    if (sVar5 == 1)
    {
        iVar8 = FUN_011402c0(0x18);
        if (iVar8 == 0) { iVar8 = 0; }
        else { iVar8 = FUN_0113fb00(); }
    }
    else if (sVar5 == 2)
    {
        iVar8 = FUN_011402c0(0x18);
        if (iVar8 == 0) goto LAB_e8e8;
        iVar8 = FUN_0113fb00();
    }
    else if (sVar5 == 3)
    {
        iVar8 = FUN_011402c0(0x18);
        if (iVar8 == 0) goto LAB_e8f0;
        iVar8 = FUN_0113fa50();
    }
    p[0x2b] = iVar8;
    {
        int vt = p[0x2b];
        (*(void(**)(int))(*(int*)vt + 8))((int)p + 0xc0);
    }
    return p;
LAB_e8e8:
    p[0x2b] = 0;
    return p;
LAB_e8f0:
    p[0x2b] = 0;
    return p;
}

// @ 0x0112fa50 -- WAVE packet submit (variant using +0xba/+0x2e).
void FUN_0112fa50(int* p, int a, u32 b, int c, u8 d)
{
    (void)a; (void)d;
    int n = (short)p[0x2e];
    u32 blocks = b / (u32)((int)*(short*)((char*)p + 0xba) * n);
    typedef void (*SubmitFn)(int, unsigned, unsigned);
    ((SubmitFn)(*(int*)p[0x2b]))(a, b, blocks);
    unsigned vals[8];
    int base = *(int*)((int)p * 5 + 200);
    for (int i = 0; i < n; ++i)
        vals[i] = (unsigned)(base + (0x4000 / (n * 4)) * i);
    ((void(*)(unsigned*, unsigned))(*(int*)p[0x2b] + 4))(vals, blocks);
    SNDPKTPLAY_submit(p[0x29], vals);
    p[2] += blocks;
    p[0x2f] += 1;
    *p += b;
}

// @ 0x0112fb50 -- WAVE chunk pump.
void FUN_0112fb50(int p)
{
    if (*(int*)(p + 0x98) == 0)
    {
        int i = 0;
        int* q = (int*)(p + 0xd8);
        do
        {
            if (q[4] == 0)
            {
                int chunk = Stream_GetChunk(*(void**)(p + 0x94));
                if (chunk == 0) return;
                FUN_0112fa50((int*)p, *(int*)(chunk + 8), *(u32*)(chunk + 4), i, 1);
                *q = chunk;
            }
            ++i; ++q;
        } while (i < 4);
    }
    else
    {
        if (*(int*)(p + 0xc4) == 0)
        {
            *(int*)(p + 0xc4) = Stream_GetChunk(*(void**)(p + 0x94));
            ((Stream*)*(void**)(p + 0x94))->ReleaseChunk(*(void**)(p + 0xc4));
        }
        int chunk = Stream_GetChunk(*(void**)(p + 0x94));
        if (chunk != 0)
        {
            FUN_0112fa50((int*)p, *(int*)(chunk + 8), *(u32*)(chunk + 4), 0, 0);
            *(int*)(p + 0xd8) = chunk;
            *(int*)(p + 0xc4) = 0;
            *(int*)(p + 0x98) = 0;
        }
    }
}


}}} // namespace rw::audio::core
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct rw {
    void SNDPKTPLAY_submit(int, void*); // 0x0113f5c0
};
}
