// Slice s01373120: dynamic initializers of the UI line-color entries and of
// four Simulator property tables (SP::sHash / PropValF registrations).
//
//  - 01373120  line color "LineColorBottom" entry
//  - 013731b0  line color "LineColorDropShadow" entry
//  - 01373220  line color "LineColorBorder" entry
//  - 01373c20  property table (0x016b2c40)
//  - 01373ef0  property table (0x016b1430)
//  - 01374160  property table (0x016b2f10)
//  - 013742c0  property table (0x015a7948)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

uint32_t __cdecl FNVHash(const char* pName, uint32_t nSeed, int nFlags);   // 0x00932e80
int __cdecl atexit(void (__cdecl* pfn)(void));                             // 0x011e07ef

namespace SP
{
    uint32_t __cdecl sHash(const char* pName);                             // 0x00e4a9d0
    uint32_t __cdecl PropValF(float nValue);                               // 0x00e4a9c0
    uint32_t __cdecl PropValF(int nValue);                                 // 0x00e4a9c0
    uint32_t __cdecl PropValF(const void* pValue);                         // 0x00e4a9c0
}

// ---------------------------------------------------------------------------
// line color entries (singly linked list of named colors)
// ---------------------------------------------------------------------------
class cColorEntry
{
public:
    void*         mpClass;                // +0x00  (0x01481e20)
    uint32_t      mHash;                  // +0x04
    cColorEntry*  mpNext;                 // +0x08
    float         mR;                     // +0x0c
    float         mG;                     // +0x10
    float         mB;                     // +0x14
    float         mA;                     // +0x18
};

extern cColorEntry* gpColorList;          // 0x015a59f4
extern cColorEntry  gLineColorBottom;     // 0x016ace6c
extern cColorEntry  gLineColorDropShadow; // 0x016ace88
extern cColorEntry  gLineColorBorder;     // 0x016acea4

extern const float gColorRed_1482268;     // 0x01482268
extern const float gColorGreen_13fe160;   // 0x013fe160
extern const float gColorBlue_1481ca8;    // 0x01481ca8
extern const float gColorBorder_1482290;  // 0x01482290
extern const float gColorOne_1485720;     // 0x01485720

// ===========================================================================
// @ 0x01373120
// ===========================================================================
void __declspec(noinline) InitLineColorBottom()
{
    uint32_t nHash = FNVHash("LineColorBottom", 0x811c9dc5, 1);

    gLineColorBottom.mR = gColorRed_1482268;
    gLineColorBottom.mG = gColorGreen_13fe160;
    float fB = gColorBlue_1481ca8;
    gLineColorBottom.mHash = nHash;
    gLineColorBottom.mpNext = gpColorList;
    gLineColorBottom.mB = fB;
    float fA = gColorOne_1485720;
    gpColorList = &gLineColorBottom;
    gLineColorBottom.mpClass = (void*)0x01481e20;
    gLineColorBottom.mA = fA;

    atexit((void (__cdecl*)(void))0x013c7aa0);
}

// ===========================================================================
// @ 0x013731b0
// ===========================================================================
void __declspec(noinline) InitLineColorDropShadow()
{
    uint32_t nHash = FNVHash("LineColorDropShadow", 0x811c9dc5, 1);

    gLineColorDropShadow.mHash = nHash;
    gLineColorDropShadow.mpNext = gpColorList;
    gLineColorDropShadow.mR = 0.0f;
    gLineColorDropShadow.mG = 0.0f;
    gLineColorDropShadow.mB = 0.0f;
    float fA = gColorBlue_1481ca8;
    gpColorList = &gLineColorDropShadow;
    gLineColorDropShadow.mpClass = (void*)0x01481e20;
    gLineColorDropShadow.mA = fA;

    atexit((void (__cdecl*)(void))0x013c7ab0);
}

// ===========================================================================
// @ 0x01373220
// ===========================================================================
void __declspec(noinline) InitLineColorBorder()
{
    uint32_t nHash = FNVHash("LineColorBorder", 0x811c9dc5, 1);

    float fRGB = gColorBorder_1482290;
    gLineColorBorder.mHash = nHash;
    gLineColorBorder.mpNext = gpColorList;
    gLineColorBorder.mR = fRGB;
    gLineColorBorder.mG = fRGB;
    gLineColorBorder.mB = fRGB;
    float fA = gColorOne_1485720;
    gpColorList = &gLineColorBorder;
    gLineColorBorder.mpClass = (void*)0x01481e20;
    gLineColorBorder.mA = fA;

    atexit((void (__cdecl*)(void))0x013c7ac0);
}

// ---------------------------------------------------------------------------
// property table records (0x28 bytes each)
// ---------------------------------------------------------------------------
struct cPropRecord
{
    uint32_t     mPad00;                  // +0x00
    uint32_t     mDefault;                // +0x04  (PropValF result)
    int32_t      mType;                   // +0x08
    uint32_t     mPad0c;                  // +0x0c
    const char*  mpName;                  // +0x10
    uint32_t     mHash;                   // +0x14
    int32_t      mOffset;                 // +0x18
    uint32_t     mPad1c;                  // +0x1c
    uint32_t     mValue1;                 // +0x20
    uint32_t     mValue2;                 // +0x24
};

extern cPropRecord gPropTable_16b2c40[];  // 0x016b2c40
extern cPropRecord gPropTable_16b1430[];  // 0x016b1430
extern cPropRecord gPropTable_16b2f10[];  // 0x016b2f10
extern cPropRecord gPropTable_15a7948[];  // 0x015a7948

// ===========================================================================
// @ 0x01373c20
// ===========================================================================
void __declspec(noinline) InitPropTable_16b2c40()
{
    cPropRecord* p = gPropTable_16b2c40;

    p[0].mHash = SP::sHash(0);
    p[0].mOffset = 0;
    p[0].mPad1c = 0;
    p[0].mValue1 = SP::PropValF(1);
    p[0].mValue2 = SP::PropValF(0);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(1);
    p[1].mType = 8;
    p[1].mPad0c = 0;
    p[1].mpName = 0;
    p[1].mHash = SP::sHash(0);
    p[1].mOffset = 4;
    p[1].mPad1c = 0;
    p[1].mValue1 = SP::PropValF(3);
    p[1].mValue2 = SP::PropValF((const void*)0x016ad4b0);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(0);
    p[2].mType = 0;
    p[2].mPad0c = 0;
    p[2].mpName = "weight";
    p[2].mHash = SP::sHash("weight");
    p[2].mOffset = 0xc;
    p[2].mPad1c = 0;
    p[2].mValue1 = SP::PropValF(2);
    p[2].mValue2 = SP::PropValF(0);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(1.0f);
    p[3].mType = 2;
    p[3].mPad0c = 0;
    p[3].mpName = "count";
    p[3].mHash = SP::sHash("count");
    p[3].mOffset = 0x10;
    p[3].mPad1c = 0;
    p[3].mValue1 = SP::PropValF(1);
    p[3].mValue2 = SP::PropValF(0);

    p[4].mPad00 = 0;
    p[4].mDefault = SP::PropValF(1);
    p[4].mType = 2;
    p[4].mPad0c = 0;
    p[4].mpName = "countDelta";
    p[4].mHash = SP::sHash("countDelta");
    p[4].mOffset = 0x14;
    p[4].mPad1c = 0;
    p[4].mValue1 = SP::PropValF(1);
    p[4].mValue2 = SP::PropValF(0);

    p[5].mPad00 = 0;
    p[5].mDefault = SP::PropValF(0);
    p[5].mType = 2;
    p[5].mPad0c = 0;
    p[5].mpName = "levelOffset";
    p[5].mHash = SP::sHash("levelOffset");
    p[5].mOffset = 0x18;
    p[5].mPad1c = 0;
    p[5].mValue1 = SP::PropValF(1);
    p[5].mValue2 = SP::PropValF(0);

    p[6].mPad00 = 0;
    p[6].mDefault = SP::PropValF(0);
    p[6].mType = 2;
    p[6].mPad0c = 0;
    p[6].mpName = 0;
    p[6].mHash = SP::sHash(0);
    p[6].mOffset = -1;
    p[6].mPad1c = 0;
    p[6].mValue1 = SP::PropValF(0);
    p[6].mValue2 = SP::PropValF(0);

    p[7].mPad00 = 0;
    p[7].mDefault = SP::PropValF(0);
    p[7].mType = 0;
    p[7].mPad0c = 0;
}

// ===========================================================================
// @ 0x01373ef0
// ===========================================================================
void __declspec(noinline) InitPropTable_16b1430()
{
    cPropRecord* p = gPropTable_16b1430;

    p[0].mHash = SP::sHash(0);
    p[0].mOffset = 0;
    p[0].mPad1c = 0;
    p[0].mValue1 = SP::PropValF(1);
    p[0].mValue2 = SP::PropValF(0);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(2);
    p[1].mType = 8;
    p[1].mPad0c = 0;
    p[1].mpName = 0;
    p[1].mHash = SP::sHash(0);
    p[1].mOffset = 8;
    p[1].mPad1c = 0;
    p[1].mValue1 = SP::PropValF(3);
    p[1].mValue2 = SP::PropValF((const void*)0x016b1020);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(0);
    p[2].mType = 0;
    p[2].mPad0c = 0;
    p[2].mpName = "weight";
    p[2].mHash = SP::sHash("weight");
    p[2].mOffset = 0xc;
    p[2].mPad1c = 0;
    p[2].mValue1 = SP::PropValF(2);
    p[2].mValue2 = SP::PropValF(0);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(1.0f);
    p[3].mType = 2;
    p[3].mPad0c = 0;
    p[3].mpName = "count";
    p[3].mHash = SP::sHash("count");
    p[3].mOffset = 0x10;
    p[3].mPad1c = 0;
    p[3].mValue1 = SP::PropValF(1);
    p[3].mValue2 = SP::PropValF(0);

    p[4].mPad00 = 0;
    p[4].mDefault = SP::PropValF(1);
    p[4].mType = 2;
    p[4].mPad0c = 0;
    p[4].mpName = "countDelta";
    p[4].mHash = SP::sHash("countDelta");
    p[4].mOffset = 0x14;
    p[4].mPad1c = 0;
    p[4].mValue1 = SP::PropValF(1);
    p[4].mValue2 = SP::PropValF(0);

    p[5].mPad00 = 0;
    p[5].mDefault = SP::PropValF(0);
    p[5].mType = 2;
    p[5].mPad0c = 0;
    p[5].mpName = 0;
    p[5].mHash = SP::sHash(0);
    p[5].mOffset = -1;
    p[5].mPad1c = 0;
    p[5].mValue1 = SP::PropValF(0);
    p[5].mValue2 = SP::PropValF(0);

    p[6].mPad00 = 0;
    p[6].mDefault = SP::PropValF(0);
    p[6].mType = 0;
    p[6].mPad0c = 0;
}

// ===========================================================================
// @ 0x01374160
// ===========================================================================
void __declspec(noinline) InitPropTable_16b2f10()
{
    cPropRecord* p = gPropTable_16b2f10;

    p[0].mHash = SP::sHash(0);
    p[0].mOffset = 0;
    p[0].mPad1c = 0;
    p[0].mValue1 = SP::PropValF(1);
    p[0].mValue2 = SP::PropValF(0);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(0);
    p[1].mType = 8;
    p[1].mPad0c = 0;
    p[1].mpName = "weight";
    p[1].mHash = SP::sHash("weight");
    p[1].mOffset = 0xc;
    p[1].mPad1c = 0;
    p[1].mValue1 = SP::PropValF(2);
    p[1].mValue2 = SP::PropValF(0);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(1.0f);
    p[2].mType = 2;
    p[2].mPad0c = 0;
    p[2].mpName = 0;
    p[2].mHash = SP::sHash(0);
    p[2].mOffset = -1;
    p[2].mPad1c = 0;
    p[2].mValue1 = SP::PropValF(0);
    p[2].mValue2 = SP::PropValF(0);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(0);
    p[3].mType = 0;
    p[3].mPad0c = 0;
}

// ===========================================================================
// @ 0x013742c0
// ===========================================================================
void __declspec(noinline) InitPropTable_15a7948()
{
    cPropRecord* p = gPropTable_15a7948;

    p[0].mHash = SP::sHash("table");
    p[0].mOffset = 0;
    p[0].mPad1c = 4;
    p[0].mValue1 = SP::PropValF((const void*)0x016b0f8c);
    p[0].mValue2 = SP::PropValF(4);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(0);
    p[1].mType = 4;
    p[1].mPad0c = 0;
    p[1].mpName = "cell";
    p[1].mHash = SP::sHash("cell");
    p[1].mOffset = 0;
    p[1].mPad1c = 4;
    p[1].mValue1 = SP::PropValF((const void*)0x016b0a54);
    p[1].mValue2 = SP::PropValF(4);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(0);
    p[2].mType = 4;
    p[2].mPad0c = 0;
    p[2].mpName = "nothing";
    p[2].mHash = SP::sHash("nothing");
    p[2].mOffset = 0;
    p[2].mPad1c = 4;
    p[2].mValue1 = SP::PropValF((const void*)0x016b0ea8);
    p[2].mValue2 = SP::PropValF(4);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(0);
    p[3].mType = 4;
    p[3].mPad0c = 0;
    p[3].mpName = "expelForce";
    p[3].mHash = SP::sHash("expelForce");
    p[3].mOffset = 0x14;
    p[3].mPad1c = 0;
    p[3].mValue1 = SP::PropValF(2);
    p[3].mValue2 = SP::PropValF(0);

    p[4].mPad00 = 0;
    p[4].mDefault = SP::PropValF(0.0f);
    p[4].mType = 6;
    p[4].mPad0c = 0;
    p[4].mpName = "effect";
    p[4].mHash = SP::sHash("effect");
    p[4].mOffset = 0x18;
    p[4].mPad1c = 0x18;
    p[4].mValue1 = SP::PropValF(7);
    p[4].mValue2 = SP::PropValF(0);

    p[5].mPad00 = 0;
    p[5].mDefault = SP::PropValF(0);
    p[5].mType = 6;
    p[5].mPad0c = 0;
    p[5].mpName = "mustHavePart";
    p[5].mHash = SP::sHash("mustHavePart");
    p[5].mOffset = 0x1c;
    p[5].mPad1c = 0;
    p[5].mValue1 = SP::PropValF(6);
    p[5].mValue2 = SP::PropValF(0);

    p[6].mPad00 = 0;
    p[6].mDefault = SP::PropValF(0);
    p[6].mType = 6;
    p[6].mPad0c = 0;
    p[6].mpName = "minRadius";
    p[6].mHash = SP::sHash("minRadius");
    p[6].mOffset = 8;
    p[6].mPad1c = 0;
    p[6].mValue1 = SP::PropValF(2);
    p[6].mValue2 = SP::PropValF(0);

    p[7].mPad00 = 0;
    p[7].mDefault = SP::PropValF(0.0f);
    p[7].mType = 6;
    p[7].mPad0c = 0;
    p[7].mpName = "maxRadius";
    p[7].mHash = SP::sHash("maxRadius");
    p[7].mOffset = 0xc;
    p[7].mPad1c = 0;
    p[7].mValue1 = SP::PropValF(2);
    p[7].mValue2 = SP::PropValF(0);

    p[8].mPad00 = 0;
    p[8].mDefault = SP::PropValF(0.0f);
    p[8].mType = 6;
    p[8].mPad0c = 0;
    p[8].mpName = "initialAlpha";
    p[8].mHash = SP::sHash("initialAlpha");
    p[8].mOffset = 0x10;
    p[8].mPad1c = 0;
    p[8].mValue1 = SP::PropValF(2);
    p[8].mValue2 = SP::PropValF(0);

    p[9].mPad00 = 0;
    p[9].mDefault = SP::PropValF(1.0f);
    p[9].mType = 6;
    p[9].mPad0c = 0;
    p[9].mpName = "delay";
    p[9].mHash = SP::sHash("delay");
    p[9].mOffset = 0x20;
    p[9].mPad1c = 0;
    p[9].mValue1 = SP::PropValF(2);
    p[9].mValue2 = SP::PropValF(0);

    p[10].mPad00 = 0;
    p[10].mDefault = SP::PropValF(0.0f);
    p[10].mType = 6;
    p[10].mPad0c = 0;
    p[10].mpName = 0;
    p[10].mHash = SP::sHash(0);
    p[10].mOffset = -1;
    p[10].mPad1c = 0;
    p[10].mValue1 = SP::PropValF(0);
    p[10].mValue2 = SP::PropValF(0);

    p[11].mPad00 = 0;
    p[11].mDefault = SP::PropValF(0);
    p[11].mType = 0;
    p[11].mPad0c = 0;
}
