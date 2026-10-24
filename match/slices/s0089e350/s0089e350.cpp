#include "types.h"

// EA::Text::GetCharCategory -- EATextUnicode.cpp (EA EAText / EAIO)
namespace EA { namespace Text {

typedef wchar_t Char;

enum CharCategory { };

struct CharCategoryInfo
{
    uint16_t mCode;         // starting code of the range
    uint8_t  mCharClass0;   // character class for 0 bits
    uint8_t  mCharClass1;   // character class for 1 bits
    uint8_t* mpBitMask;     // bitmask (can be NULL)
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

// @ 0x0089e5e0
CharCategory GetCharCategory(Char nChar)
{
    const size_t           kCCTableSize = sizeof(gCharCategoryTable) / sizeof(gCharCategoryTable[0]);
    const CharCategoryInfo cciTemp      = { nChar, 0, 0, 0 };

    const CharCategoryInfo* const pCC = (EA::Text::upper_bound(gCharCategoryTable, gCharCategoryTable + kCCTableSize, cciTemp, CharCategoryLess()) - 1);

    if(pCC->mpBitMask == 0)
        return (CharCategory)pCC->mCharClass0;

    const int nBitIndex = nChar - pCC->mCode;
    return (CharCategory)((pCC->mpBitMask[nBitIndex >> 3] & (1 << (nBitIndex & 7))) ? pCC->mCharClass1 : pCC->mCharClass0);
}

}}
