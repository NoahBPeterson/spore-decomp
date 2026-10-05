// Slice s0064fa20 -- cSPUIAssetGrid scrolling / layout / entry lookup.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

// Grid entry; lookup key (asset id) lives at +0x10, stride 0x20.
struct GridEntry {
    uint8_t  pad00[0x10];
    uint32_t mID;        // +0x10
    uint8_t  pad14[0x0c];
};

struct Grid {
    uint8_t    pad00[0xe8];
    GridEntry* mpBegin;  // +0xe8
    GridEntry* mpEnd;    // +0xec
    GridEntry* Find(uint32_t id);
};

// @ 0x006505d0
GridEntry* Grid::Find(uint32_t id) {
    int index = -1;
    if (id == 0) {
        index = 0;
    } else {
        const int n = (int)(mpEnd - mpBegin);
        for (int i = 0; i < n; ++i) {
            if (mpBegin[i].mID == id) {
                index = i;
                break;
            }
        }
    }
    if (index == -1)
        return 0;
    return &mpBegin[index];
}

// ---------------------------------------------------------------------------
// Large methods; reconstructed only in outline (partial.txt).
// ---------------------------------------------------------------------------
// @ 0x0064fa20
void __fastcall sub_64fa20(void*) {}
// @ 0x0064fc40
void __fastcall sub_64fc40(void*) {}
// @ 0x0064fd00
void __fastcall sub_64fd00(void*) {}
// @ 0x0064fde0
void __fastcall sub_64fde0(void*) {}
// @ 0x0064ff90
void __fastcall sub_64ff90(void*) {}
// @ 0x00650020
void __fastcall sub_650020(void*) {}
// @ 0x00650190
void __fastcall sub_650190(void*) {}
// @ 0x00650470
void __fastcall sub_650470(void*) {}
