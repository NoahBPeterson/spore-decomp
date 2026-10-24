// 0x00e19dd0..0x00e1b350 -- SP mission/civ ordering helpers (SPGonzago).
//
// The block is dominated by one comparison routine (0x00e19dd0) and eight
// eastl insertion-sort instantiations over 4-byte EA::AutoRefCount elements
// that all call it, plus a small bounds-checked array accessor and a couple of
// class constructors.  Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

// ---------------------------------------------------------------------------
// 0x00e1a1a0: bounds-checked 4-byte array indexer (returns 0 out of range).
// ---------------------------------------------------------------------------
struct CIndexedArray
{
    /* 000h */ uint8_t   mPad_000[0x44];
    /* 044h */ uint32_t* mBegin_44;   // array begin
    /* 048h */ uint32_t* mEnd_48;     // array end
    /* 04ch */ uint8_t   mPad_04c[0x90 - 0x4c];
    /* 090h */ int32_t   mIndex_90;   // current index
};

// @ 0x00e1a1a0
uint32_t __fastcall FUN_00e1a1a0(CIndexedArray* pThis)
{
    int32_t iIndex = pThis->mIndex_90;
    if ((iIndex >= 0) && (iIndex < (int32_t)(pThis->mEnd_48 - pThis->mBegin_44)))
        return pThis->mBegin_44[iIndex];
    return 0;
}