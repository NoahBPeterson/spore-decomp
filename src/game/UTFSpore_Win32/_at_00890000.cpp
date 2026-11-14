// src/game/UTFSpore_Win32/_at_00890000.cpp
// Object file: UTFSpore_Win32/_at_00890000.obj.

#include "game/types.h"
#include "EA/Text/LayoutSettings.h"

namespace EA {
namespace Text {

// A font-selection target that can tell whether it owns a font and which font
// index a request resolves to.
struct IFontCompareTarget {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual bool HasFont(int32_t a, int32_t b);              // +0x28
    virtual void v11();
    virtual int32_t FindFont(int32_t a, int32_t b);          // +0x30
};

// EA::Text::Layout has no generated header; only its constructor is defined
// here, so a minimal stand-in with the real leading member is enough.
struct Layout {
    LayoutSettings mLayoutSettings;   // +0x000
    Layout();
};

typedef wchar_t Char;

enum CharCategory { };

struct CharCategoryInfo
{
    uint16_t mCode;         // first character code of the range
    uint8_t  mCharClass0;   // character class where the bitmask bit is 0
    uint8_t  mCharClass1;   // character class where the bitmask bit is 1
    uint8_t* mpBitMask;     // optional per-character bitmask
};

struct CharCategoryLess
{
    bool operator()(const CharCategoryInfo& a, const CharCategoryInfo& b) const
        { return a.mCode < b.mCode; }
};

extern CharCategoryInfo gCharCategoryTable[779];   // 0x0154a1a0 .. 0x0154b9f8

template <typename RandomAccessIterator, typename T, typename Compare>
RandomAccessIterator upper_bound(RandomAccessIterator first, RandomAccessIterator last,
                                 const T& value, Compare compare);   // 0x0089e5a0

}  // namespace Text
}  // namespace EA

// @ 0x00890f50
EA::Text::Layout::Layout()
{
}

// @ 0x00890f60
int __cdecl CompareFontCallback(EA::Text::IFontCompareTarget* pTarget, int32_t a2, int32_t a3, int32_t a4)
{
    if (pTarget->HasFont(a3, 0))
    {
        if (pTarget->FindFont(a2, a4) == a4)
            return 0;
    }
    return -1;
}

// @ 0x0089e5e0
namespace EA { namespace Text {
CharCategory GetCharCategory(Char nChar)
{
    const size_t           kCCTableSize = sizeof(gCharCategoryTable) / sizeof(gCharCategoryTable[0]);
    const CharCategoryInfo cciTemp      = { nChar, 0, 0, 0 };

    const CharCategoryInfo* const pCC = (upper_bound(gCharCategoryTable, gCharCategoryTable + kCCTableSize, cciTemp, CharCategoryLess()) - 1);

    if (pCC->mpBitMask == 0)
        return (CharCategory)pCC->mCharClass0;

    const int nBitIndex = nChar - pCC->mCode;
    return (CharCategory)((pCC->mpBitMask[nBitIndex >> 3] & (1 << (nBitIndex & 7))) ? pCC->mCharClass1 : pCC->mCharClass0);
}
}}  // namespace EA::Text
