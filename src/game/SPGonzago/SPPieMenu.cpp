// src/game/SPGonzago/SPPieMenu.cpp -- migrated from slice(s) s00b7bd50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPieMenu.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern int g_PieMenuState;                      // 0x01688150
extern int g_PieMenuFontRes;                    // 0x04518450
extern "C" void* __cdecl SP_GameInputManager();
#include <emmintrin.h>

// ---- items of slice s00b7bd50 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
static inline void Vv0(void* p, int slot) {
    ((void(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline void Vv2(void* p, int slot, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[slot / 4])(p, a, b);
}
class cSPUIPieMenuItemWinProc { public:
    void** vftable;             // +0x00
    char   pad_04[0xc - 0x04];
    int    mButtonId;           // +0x0c
    int    mItemId;             // +0x10
    bool   bButtonClicked;      // +0x14
    void*  mpHighlightCallback; // +0x18

    void Hide();                // 0x00818330
    bool ContainsWindow(void* hwnd); // 0x00818370
};
extern cSPUIPieMenuItemWinProc* g_pPieWinProc;  // 0x0168817c
extern int g_PieMenuState;                      // 0x01688150
extern u8  g_bPieMenuVisible;                   // 0x01688154
extern int g_PieMenuFontRes;                    // 0x04518450
extern "C" void* __cdecl SP_GameInputManager();
// ---- items of slice s00b7bd50 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cSPUIPieMenuItemWinProc* g_pPieWinProc;  // 0x0168817c
extern u8  g_bPieMenuVisible;                   // 0x01688154

// @ 0x00b7c810
void __cdecl cSPPieMenu_HideUTFMenu(char bPlaySound)
{
    if (g_pPieWinProc) {
        g_pPieWinProc->Hide();
        Vv0(g_pPieWinProc, 0x24);
        cSPUIPieMenuItemWinProc* q = g_pPieWinProc;
        if (q) {
            g_pPieWinProc = 0;
            Vv0(q, 0x04);
        }
        if (bPlaySound) {
            void* gm = SP_GameInputManager();
            Vv2(gm, 0x64, (int)&g_PieMenuFontRes, 1);
        }
    }
    g_PieMenuState = 0;
    g_bPieMenuVisible = 0;
}
