// Slice s0064acd0 -- cSPUIAssetBrowser launch / ban / message handling.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

struct cSPUIAssetBrowser {
    uint8_t pad0[0x19c];
    uint32_t mField19C;   // +0x19c
    void ShowSporeGuide();
};
struct MsgParam; struct Msg;

extern "C" void __cdecl LaunchSporeGuide(uint32_t id);   // 0x0064aba0

// @ 0x0064b6a0
void cSPUIAssetBrowser::ShowSporeGuide() {
    LaunchSporeGuide(mField19C);
}

// ---------------------------------------------------------------------------
// Large methods; reconstructed only in outline (partial.txt).
// ---------------------------------------------------------------------------
// @ 0x0064acd0
void __fastcall sub_64acd0(void*) {}
// @ 0x0064b4b0
void __fastcall sub_64b4b0(void*) {}
// @ 0x0064b6b0
void __fastcall sub_64b6b0(void*) {}
