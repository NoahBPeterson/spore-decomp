// Slice s00649f60 -- cSPUIAssetBrowser show/hide/launch helpers.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

struct State {
    uint8_t pad[0x1c];
    uint8_t mField1C;   // +0x1c
};

extern "C" State* __cdecl SporeGuide();     // 0x00401040
extern "C" State* __cdecl AssetBrowser();   // 0x00401030
extern "C" void  __cdecl UpdateMouseFocus(int); // 0x00804f50

struct Iface;

struct cSPUIAssetBrowser {
    uint8_t pad0[0x1c];
    uint8_t mIsVisible;       // +0x1c
    uint8_t pad1D[0x08];      // +0x1d..0x24
    uint8_t mField25;         // +0x25
    uint8_t pad26[0x03];      // +0x26..0x28
    uint8_t mField29;         // +0x29
    uint8_t pad2A[0x92];      // +0x2a..0xbb
    void*   mpFieldBC;        // +0xbc
    uint8_t padC0[0x108];     // +0xc0..0x1c7
    uint8_t mField1C8;        // +0x1c8
    uint8_t padC9[0x6b];      // +0x1c9..0x233
    uint8_t mField234;        // +0x234

    void SetVisibility(int a, int b, int c);   // 0x0064a400 (declared)
    void Update();                              // 0x0064ab20
};

// @ 0x0064ab20
void cSPUIAssetBrowser::Update() {
    if (!mIsVisible)
        return;
    if (!mField25)
        return;
    if (!mField29 && SporeGuide()->mField1C)
        return;
    void* const p = mpFieldBC;
    if (p && (mField234 || mField1C8) && p)
        return;

    bool v = false;
    if (mField29) {
        if (AssetBrowser()->mField1C)
            v = true;
    }
    SetVisibility(0, 1, v);
    UpdateMouseFocus(1);
}

// ---------------------------------------------------------------------------
// Large methods; reconstructed only in outline (partial.txt).
// ---------------------------------------------------------------------------
// @ 0x00649f60
void __fastcall sub_649f60(void*) {}
// @ 0x0064a220
void __fastcall sub_64a220(void*) {}
// @ 0x0064a400
void __fastcall sub_64a400(void*) {}
// @ 0x0064a990
void __fastcall sub_64a990(void*) {}
// @ 0x0064aba0
void __fastcall sub_64aba0(void*) {}
