// Slice s0066f9f0: SP::cSPUIFeedListItem-adjacent card/view helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

void* __cdecl FUN_0067cb30();                       // 0x0067cb30
void  __cdecl FUN_005507a0(void* a);                // 0x005507a0
void  __cdecl FUN_00550800(void* a);                // 0x00550800
void  __cdecl FUN_00550820(void* a);                // 0x00550820
void  __cdecl FUN_004786e0(void* a, void* b);       // 0x004786e0
void  __cdecl FUN_00610460(void* a);                // 0x00610460
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380

extern int gVt700_0, gVt700_1, gVt700_2, gVt700_3, gVt700_4, gVt700_5;
extern int gStr700A, gStr700B;

// -----------------------------------------------------------------------------
// @ 0x006700d0  constructor
// -----------------------------------------------------------------------------
void __fastcall FUN_006700d0(void* self) {
    uint32_t* p = (uint32_t*)self;
    p[1] = (uint32_t)&gVt700_1;
    p[3] = (uint32_t)&gVt700_3;
    uint32_t z = 0;
    p[4] = z;
    p[0] = (uint32_t)&gVt700_0;
    p[1] = (uint32_t)&gVt700_4;
    p[2] = (uint32_t)&gVt700_2;
    p[3] = (uint32_t)&gVt700_5;
    p[5] = z;
    uint32_t m1 = 0xffffffff;
    p[6] = m1; p[7] = m1; p[8] = m1; p[9] = m1;
    p[0xc] = (uint32_t)&gStr700B;
    uint32_t s = (uint32_t)&gStr700A;
    p[10] = s; p[0xb] = s;
    p[0x10] = m1; p[0x11] = m1; p[0x12] = m1; p[0x13] = m1;
    *(uint8_t*)(p + 0xe) = 1;
    p[0x16] = z;
    p[0x14] = s; p[0x15] = s;
    p[0x16] = p[0x14] + 2;
    *(uint8_t*)(p + 0x18) = 1;
    p[0x1a] = z; p[0x1b] = z;
    *(uint8_t*)(p + 0x1c) = 0;
    p[0x1d] = z; p[0x1e] = z; p[0x1f] = z;
    p[0x20] = z; p[0x21] = z; p[0x22] = z; p[0x23] = z;
    p[0x24] = z; p[0x25] = z; p[0x26] = z; p[0x27] = z;
    p[0x28] = z; p[0x29] = z; p[0x2a] = z; p[0x2b] = z;
    p[0x2c] = z; p[0x2d] = z; p[0x2e] = z; p[0x2f] = z;
    p[0x30] = z; p[0x31] = z; p[0x32] = z;
}

// -----------------------------------------------------------------------------
// @ 0x0066f9f0 / 0x0066fee0 / 0x00670200 / 0x00670370 / 0x006704f0 / 0x00670610
// @ 0x006707a0  (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void __fastcall FUN_0066f9f0(void* self) { (void)self; }
void __fastcall FUN_0066fee0(void* self) { (void)self; }
void __fastcall FUN_00670200(void* self) { (void)self; }
void __fastcall FUN_00670370(void* self) { (void)self; }
void __fastcall FUN_006704f0(void* self) { (void)self; }
void __fastcall FUN_00670610(void* self) { (void)self; }
void __fastcall FUN_006707a0(void* self) { (void)self; }
