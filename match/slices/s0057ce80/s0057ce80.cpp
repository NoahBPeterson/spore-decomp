// slice s0057ce80 — SP::cAppModeEditorBase::cAppModeEditorBase() (retail layout, size 0x5fc).
// A pure member-initializer constructor: 7 interface bases (their vptrs are stored first, then
// overwritten with the derived vtables), ~300 members zeroed or set to constants, a rbtree header
// reset for two eastl::maps, cLocalInputState (0x697960) and EA::Stopwatch (0x93a560) constructed,
// and the singleton pointer (0x15e4ef0) set to this.
// The 2008 PDB layout (0x458) is shifted from retail; names below come from the PDB where the
// offset mapping is clear, others are named by retail offset.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <stddef.h>

// ---- tiny initialized-member helpers (each is an inline default-constructed member) ----
struct Zd { uint32_t v; Zd() : v(0) {} };            // zeroed dword / pointer / AutoRefCount
struct Zb { uint8_t  v; Zb() : v(0) {} };            // false
struct Ob { uint8_t  v; Ob() : v(1) {} };            // true
struct Zf { float    v; Zf() : v(0.0f) {} };         // 0.0f

// ---- interface bases (retail has seven vptr sub-objects) ----
struct cIAppMode            { virtual void vIAppMode(); };
struct cILayer              { virtual void vILayer(); };
struct cIHintProcessor      { virtual void vIHint(); };
struct cISPEditorNameProvider { virtual void vIName(); };
struct IHandlerRC           { virtual void vIHandler(); };
struct RefCountVTemplateInt { virtual void vRef(); int mRefCount; RefCountVTemplateInt() : mRefCount(0) {} };
struct cIUnknownBase7       { virtual void vBase7(); };

// ---- eastl pieces ----
extern wchar_t gEmptyWString[1];                      // 0x1667bac
struct WString {                                      // eastl::basic_string<wchar_t> (16 bytes)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WString() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
};
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight; rbtree_node_base* mpNodeLeft; rbtree_node_base* mpNodeParent; char mColor;
};
struct RbMap {                                        // eastl::map<K,V> header (24 bytes)
    rbtree_node_base mAnchor; uint32_t mnSize; uint32_t mAllocator;
    RbMap() : mAnchor(), mnSize(0) { reset(); }
    void reset() {
        mAnchor.mpNodeRight = &mAnchor; mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0; mAnchor.mColor = 0; mnSize = 0;
    }
};
struct cLocalInputState {
    uint32_t d[0x12];
    cLocalInputState();   // 0x00697960: memset(this, 0, 0x48)
};
struct Stopwatch {
    uint32_t d[6];
    Stopwatch(int units, int startNow);   // 0x0093a560
};

namespace SP {

class cAppModeEditorBase;
extern cAppModeEditorBase* sInstance;                 // 0x15e4ef0

class cAppModeEditorBase : public cIAppMode, public cILayer, public cIHintProcessor,
                           public cISPEditorNameProvider, public IHandlerRC,
                           public RefCountVTemplateInt, public cIUnknownBase7 {
public:
    cAppModeEditorBase();

    Zd mApp;                    // 0x20
    Zd mCurrentConfigProperties;// 0x24
    Zf mX;                      // 0x28
    Zf mY;                      // 0x2c
    Zd mModifiers;              // 0x30
    Zd mCurrentMouseDown;       // 0x34
    Zb mMouseMoved;             // 0x38
    uint8_t pad39[3];
    Zd mModeModifiers;          // 0x3c
    uint32_t mControlModifierMode;      // 0x40
    uint32_t mEyeDropperModiferMode;    // 0x44
    Zd mModelValidity[4];       // 0x48
    Zd mModelSaveValidity[4];   // 0x58
    Zf mIdleTime;               // 0x68
    Zf mIdleTarget;             // 0x6c
    Zf mSwapToModelTime;        // 0x70
    Ob f74;                     // 0x74
    uint8_t pad75[3];
    Zd f78, f7c, f80, f84, f88, f8c, f90, f94, f98, f9c, fa0, fa4, fa8, fac;   // 0x78..0xac
    WString mOriginalTag;       // 0xb0
    uint32_t uc0, uc4, uc8;     // 0xc0
    Zd fcc, fd0, fd4, fd8, fdc; // 0xcc..0xdc
    Zb fe0;                     // 0xe0
    uint8_t pade1[3];
    Zd fe4;                     // 0xe4
    Zb fe8; Zb fe9;             // 0xe8
    uint8_t padea[2];
    Zd fec, ff0, ff4;           // 0xec
    cLocalInputState mEditorLocalInputState;   // 0xf8
    Ob f140; Zb f141; Zb f142; uint8_t pad143;  // 0x140
    Ob f144; uint8_t pad145[3];                 // 0x144
    Zd f148, f14c, f150, f154, f158, f15c, f160, f164, f168;   // 0x148..0x168
    uint32_t u16c, u170;        // 0x16c
    Zd f174, f178, f17c;        // 0x174
    uint32_t u180, u184;        // 0x180
    Zd f188;                    // 0x188
    uint32_t f18c;              // 0x18c
    Ob f190; Ob f191; uint8_t pad192[2];        // 0x190
    Zd f194;                    // 0x194
    uint32_t f198;              // 0x198
    Zd f19c;                    // 0x19c
    uint32_t f1a0, f1a4, f1a8;  // 0x1a0
    Zd f1ac;                    // 0x1ac
    uint32_t u1b0;              // 0x1b0
    RbMap mResourceToConfigMap; // 0x1b4
    Zd f1cc, f1d0, f1d4, f1d8;  // 0x1cc
    WString f1dc;               // 0x1dc
    Zd f1ec, f1f0, f1f4, f1f8, f1fc, f200, f204, f208;   // 0x1ec..0x208
    uint16_t u20c; Zb f20e; uint8_t pad20f;     // 0x20c
    Zd f210, f214, f218, f21c, f220, f224, f228, f22c, f230, f234;   // 0x210
    Zd f238, f23c, f240, f244, f248, f24c, f250, f254, f258, f25c;
    Zd f260, f264, f268, f26c, f270, f274, f278, f27c, f280, f284;   // ..0x284
    float f288;                 // 0x288
    Zd f28c, f290, f294, f298, f29c, f2a0, f2a4, f2a8, f2ac;   // 0x28c..0x2ac
    Zb f2b0; uint8_t u2b1; Ob f2b2; Zb f2b3; Zb f2b4; uint8_t pad2b5[3];   // 0x2b0
    float f2b8, f2bc, f2c0, f2c4;   // 0x2b8
    float f2c8, f2cc, f2d0;     // 0x2c8
    Zf f2d4;                    // 0x2d4
    Zd f2d8;                    // 0x2d8
    int f2dc, f2e0, f2e4;       // 0x2dc
    uint32_t u2e8;              // 0x2e8
    Zf f2ec;                    // 0x2ec
    uint8_t u2f0; Zb f2f1; Zb f2f2; Zb f2f3; Zb f2f4; Zb f2f5; Zb f2f6; uint8_t u2f7, u2f8;   // 0x2f0
    Ob f2f9; Zb f2fa; uint8_t u2fb;             // 0x2f9
    Zd f2fc, f300, f304, f308, f30c;            // 0x2fc
    Ob f310; uint8_t pad311[3];                 // 0x310
    float f314;                 // 0x314
    Zd f318, f31c, f320, f324, f328;            // 0x318
    uint32_t u32c, u330;        // 0x32c
    Zd f334, f338, f33c;        // 0x334
    uint32_t u340, u344;        // 0x340
    int f348, f34c;             // 0x348
    Zd f350, f354, f358, f35c, f360, f364, f368, f36c, f370, f374;   // 0x350
    uint32_t u378, u37c;        // 0x378
    Zd f380;                    // 0x380
    Zb f384; Zb f385; uint8_t u386, u387;       // 0x384
    uint32_t u388;              // 0x388
    Zd f38c, f390;              // 0x38c
    Zb f394; Zb f395; uint8_t u396; Zb f397;    // 0x394
    Ob f398; Ob f399; Ob f39a; uint8_t u39b;    // 0x398
    Zd f39c, f3a0, f3a4;        // 0x39c
    uint32_t u3a8, u3ac, u3b0, u3b4;            // 0x3a8
    Zd f3b8, f3bc, f3c0, f3c4; // 0x3b8
    Zb f3c8; Ob f3c9; uint8_t u3ca[2];          // 0x3c8
    uint32_t u3cc, u3d0, u3d4, u3d8, u3dc;      // 0x3cc
    Zb f3e0; Zb f3e1; uint8_t u3e2[2];          // 0x3e0
    Zd f3e4;                    // 0x3e4
    uint32_t f3e8;              // 0x3e8
    Zd f3ec, f3f0, f3f4, f3f8;  // 0x3ec
    uint32_t f3fc;              // 0x3fc
    Zd f400;                    // 0x400
    uint32_t f404;              // 0x404
    Zd f408, f40c, f410;        // 0x408
    uint32_t u414, u418;        // 0x414
    Zd f41c, f420, f424;        // 0x41c
    uint32_t u428, u42c;        // 0x428
    Zb f430; uint8_t pad431[3]; // 0x430
    Zd f434, f438, f43c, f440, f444, f448, f44c;   // 0x434
    uint32_t f450;              // 0x450
    uint32_t u454;              // 0x454
    RbMap f458;                 // 0x458
    Zb f470; uint8_t u471; Zb f472; uint8_t pad473;   // 0x470
    Zf f474;                    // 0x474
    float f478, f47c;           // 0x478
    Zf f480, f484;              // 0x480
    float f488;                 // 0x488
    uint32_t u48c, u490;        // 0x48c
    Zd f494, f498, f49c, f4a0, f4a4;   // 0x494
    uint32_t u4a8;              // 0x4a8
    uint32_t f4ac;              // 0x4ac
    Ob f4b0; Ob f4b1; Zb f4b2; uint8_t u4b3, u4b4; Zb f4b5; uint8_t u4b6; Zb f4b7; Zb f4b8; Zb f4b9; uint8_t u4ba[2];   // 0x4b0
    Zd f4bc, f4c0, f4c4;        // 0x4bc
    Zb f4c8; Zb f4c9; uint8_t u4ca[2];          // 0x4c8
    Zd f4cc;                    // 0x4cc
    float f4d0;                 // 0x4d0
    uint32_t u4d4;              // 0x4d4
    Zd f4d8, f4dc, f4e0;        // 0x4d8
    uint32_t u4e4[(0x508 - 0x4e4) / 4];         // 0x4e4
    Zd f508, f50c, f510;        // 0x508
    uint32_t u514, u518;        // 0x514
    Zd f51c, f520, f524;        // 0x51c
    uint32_t u528, u52c;        // 0x528
    Zd f530, f534, f538;        // 0x530
    uint32_t u53c, u540;        // 0x53c
    Zd f544, f548, f54c;        // 0x544
    uint32_t u550, u554;        // 0x550
    Zd f558, f55c, f560;        // 0x558
    uint32_t u564, u568;        // 0x564
    Zd f56c, f570, f574;        // 0x56c
    uint32_t u578[(0x588 - 0x578) / 4];         // 0x578
    Zd f588, f58c, f590;        // 0x588
    uint32_t u594, u598;        // 0x594
    Zd f59c;                    // 0x59c
    float f5a0;                 // 0x5a0
    uint32_t u5a4;              // 0x5a4
    Stopwatch mStopwatch;       // 0x5a8
    Zd f5c0, f5c4, f5c8, f5cc, f5d0, f5d4, f5d8, f5dc, f5e0, f5e4, f5e8, f5ec, f5f0, f5f4, f5f8;  // 0x5c0
};

// layout checks (retail offsets)
#define OFFCHK(m, o) typedef char chk_##m[(offsetof(cAppModeEditorBase, m) == (o)) ? 1 : -1]
OFFCHK(mApp, 0x20); OFFCHK(mIdleTime, 0x68); OFFCHK(f78, 0x78); OFFCHK(mOriginalTag, 0xb0);
OFFCHK(fcc, 0xcc); OFFCHK(mEditorLocalInputState, 0xf8); OFFCHK(f140, 0x140); OFFCHK(f1ac, 0x1ac);
OFFCHK(mResourceToConfigMap, 0x1b4); OFFCHK(f1dc, 0x1dc); OFFCHK(f20e, 0x20e); OFFCHK(f210, 0x210);
OFFCHK(f288, 0x288); OFFCHK(f2b0, 0x2b0); OFFCHK(f2b8, 0x2b8); OFFCHK(f2f9, 0x2f9); OFFCHK(f314, 0x314);
OFFCHK(f348, 0x348); OFFCHK(f398, 0x398); OFFCHK(f3c8, 0x3c8); OFFCHK(f3e8, 0x3e8); OFFCHK(f404, 0x404);
OFFCHK(f430, 0x430); OFFCHK(f458, 0x458); OFFCHK(f470, 0x470); OFFCHK(f488, 0x488); OFFCHK(f4ac, 0x4ac);
OFFCHK(f4b0, 0x4b0); OFFCHK(f4bc, 0x4bc); OFFCHK(f4d0, 0x4d0); OFFCHK(f508, 0x508); OFFCHK(f588, 0x588);
OFFCHK(f5a0, 0x5a0); OFFCHK(mStopwatch, 0x5a8); OFFCHK(f5c0, 0x5c0);
typedef char chk_size[(sizeof(cAppModeEditorBase) == 0x5fc) ? 1 : -1];

// @ 0x0057ce80
cAppModeEditorBase::cAppModeEditorBase()
    : f18c(0x465c50ba), f198(2), f1a0(2), f1a4(2), f1a8(2),
      f288(1.2f), f2b8(2.0f), f2bc(2.0f), f2c0(-2.0f), f2c4(2.0f),
      f2c8(3.402823466e+38f), f2cc(3.402823466e+38f), f2d0(3.402823466e+38f),
      f2dc(-1), f2e0(-1), f2e4(-1), f314(0.5f), f348(-1), f34c(-1),
      f3e8(5), f3fc(0x24), f404(1), f450(1),
      f478(0.3f), f47c(10.0f), f488(30.0f), f4ac(1), f4d0(57.29578f), f5a0(1.0f),
      mStopwatch(4, 0)
{
    sInstance = this;
}

}  // namespace SP
