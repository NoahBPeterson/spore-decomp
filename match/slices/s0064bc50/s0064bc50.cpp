// Slice s0064bc50 -- cSPUIAssetBrowser launch / update / message handling.
// Module flags: /O2 /MD /Gy /TP /GS-.
#include "types.h"

// Argument block built by Launch for AdvancedLaunch (0x48 bytes).
struct LaunchParams {
    uint32_t f00;
    uint32_t f04, f08, f0c;
    uint8_t  f10, f11, f12, f13, f14;
    uint8_t  pad15[3];
    uint32_t f18, f1c, f20;
    uint8_t  f24;
    uint8_t  pad25[3];
    uint32_t f28;
    uint8_t  f2c;
    uint8_t  pad2d[3];
    uint32_t f30;
    uint32_t f34;
    uint32_t f38;
    uint32_t f3c, f40, f44;
};

extern "C" void __cdecl AdvancedLaunch(LaunchParams* p);   // 0x0064a990

// @ 0x0064bc50
void __cdecl Launch(uint32_t a, uint32_t b, uint32_t c) {
    LaunchParams p;
    p.f04 = 0;
    p.f08 = 0;
    p.f0c = 0;
    p.f10 = 0;
    p.f11 = 0;
    p.f12 = 0;
    p.f14 = 0;
    p.f18 = 0;
    p.f1c = 0;
    p.f20 = 0;
    p.f28 = 0;
    p.f2c = 0;
    p.f3c = 0;
    p.f40 = 0;
    p.f44 = 0;
    p.f00 = a;
    const uint32_t one = 1;
    p.f13 = (uint8_t)one;
    p.f24 = (uint8_t)one;
    p.f34 = one;
    p.f38 = b;
    p.f30 = c;
    AdvancedLaunch(&p);
}

// ---------------------------------------------------------------------------
// Large methods; reconstructed only in outline (partial.txt).
// ---------------------------------------------------------------------------
// @ 0x0064bcd0
void __fastcall sub_64bcd0(void*) {}
// @ 0x0064c0d0
void __fastcall sub_64c0d0(void*) {}
// @ 0x0064c280
void __fastcall sub_64c280(void*) {}
// @ 0x0064c400
void __fastcall sub_64c400(void*) {}
// @ 0x0064c6b0
void __fastcall sub_64c6b0(void*) {}
