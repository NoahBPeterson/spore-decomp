// Declarations for slice s0098d630 (EA::UTFWinControls::WinTextEdit rebuild/scroll helpers).
// Callees are external (relocated) in the original; the PDB supplies the names where known.
#pragma once
#include "types.h"

namespace EA {
namespace UTFWin {

class IRenderMode;
class IWindow;

// 2D-batch handle returned by RenderCtx::Begin2D.
struct Batch2D;

class RenderCtx {
public:
    Batch2D* Begin2D(IRenderMode* mode);                            // 0x0095BC10
};

// A 2x4 float rectangle used by the text-edit geometry (0x10 bytes).
struct RectF {
    float left;                                                     // 0x00
    float top;                                                      // 0x04
    float right;                                                    // 0x08
    float bottom;                                                   // 0x0c
};

// A float rectangle + style blob passed to the layout callbacks (0x10 bytes here).
struct LayoutRect {
    float x0;                                                       // 0x00
    float y0;                                                       // 0x04
    float x1;                                                       // 0x08
    float y1;                                                       // 0x0c
};

} // namespace UTFWin
} // namespace EA

namespace EA {
namespace UTFWinControls {

// WinTextEdit.  Members are named by role; offsets are the retail offsets read by this slice.
class WinTextEdit {
public:
    // Window base (at this+0x04 is the IWindow*); vtable slots are called by offset.
    uint32_t  pad_000;                                              // 0x000
    EA::UTFWin::IWindow* mpWindow;                                  // 0x004
    uint32_t  pad_008[0x1e0/4 - 0x008/4 - 1];                       // 0x008..0x1e0
    void*     mpImeComposition;                                     // 0x1e0
    uint32_t  flags_214;                                            // 0x214
    uint32_t  flags_218;                                            // 0x218
    uint32_t  pad_21c[0x230/4 - 0x21c/4];                           // 0x21c..0x230
    EA::UTFWin::RectF visibleRect;                                  // 0x230 text viewport
    uint32_t  pad_240[2];                                           // 0x240..0x248
    void*     mpLayout[4];                                          // 0x244..0x254 (two labelled variants)
    uint32_t  pad_254[0x580/4 - 0x254/4];                           // 0x254..0x580
    void*     mpScrollbarH;                                         // 0x580
    uint32_t  pad_584;                                              // 0x584
    int       mScrollModeA;                                         // 0x588
    uint32_t  pad_58c;                                              // 0x58c
    uint32_t  pad_590;                                              // 0x590
    void*     mpScrollbarV;                                         // 0x594
    uint32_t  pad_598;                                              // 0x598
    int       mScrollModeB;                                         // 0x59c
    uint32_t  pad_5a0[0x5b0/4 - 0x5a0/4];                           // 0x5b0
    float     mMinWidth;                                            // 0x5b0
    float     mMinHeight;                                           // 0x5b4

    void OnRebuild(EA::UTFWin::IRenderMode* mode);                  // 0x0098D630
    void RecalculateLineBreaks();                                   // 0x0098D110
    void CalculateVisibleArea();                                    // 0x00989870
    void FUN_0098dff0();                                            // 0x0098DFF0
};

void FUN_0098dff0(WinTextEdit* self);                               // 0x0098DFF0 (ecx=this)

} // namespace UTFWinControls
} // namespace EA
