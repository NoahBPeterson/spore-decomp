// EA::XHTML::Style::CSSParser::ParseBoxHeight (0x008f7f20): parses the value of a box height
// property (`auto` or a length) and appends a property setter to the list.
#include "types.h"
#include <stddef.h>

namespace EA {
namespace Allocator {
class StackAllocator;
}  // namespace Allocator
}  // namespace EA

inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator& allocator) throw();

namespace EA {
namespace XHTML {
namespace Style {

using EA::Allocator::StackAllocator;

enum Units {
    Unit_Number = 0, Unit_Pixels = 1, Unit_Points = 2, Unit_Picas = 3, Unit_Millimeters = 4,
    Unit_Centimeters = 5, Unit_Inches = 6, Unit_Ems = 7, Unit_Exs = 8, Unit_Percentage = 9,
    Unit_Auto = 10, Unit_Inherit = 11, Unit_BorderSize = 12, Unit_Unset = 13
};

struct Length {  // size 0x8
    Length(float value, Units units) : mValue(value), mUnits(units) {}
    float mValue;  // +0x0
    Units mUnits;  // +0x4
};

class StyleState;

// The setter is a pointer to a StyleState member formed while StyleState is still incomplete, so it
// uses MSVC's 16-byte general (unknown-inheritance) form. A member of this type fixes that layout.
class SetterHolder {
public:
    void (StyleState::*mSetter)(Length);
};

class Property {  // size 0x8
public:
    virtual void Apply(StyleState* pState) const;
    Property* mpNext;  // +0x4
};

class PropertyList {  // size 0x4
public:
    void Add(Property* p) {
        p->mpNext = mpFirst;
        mpFirst = p;
    }
    Property* mpFirst;  // +0x0
};

// Built from the setter pointer, the allocator and the value. Defined in another slice (0x008f3090).
template <class T>
Property* CreatePropertyFunc(StackAllocator* pAllocator, void (StyleState::*pSetter)(T), T arg);

class StyleState {
public:
    void SetHeight(Length len);  // 0x008f2c10: writes mHeight (+0x374 value, +0x378 units)
};

struct MatchText {  // eastl::basic_string<wchar_t> (only the begin pointer is used here)
    const wchar_t* mpBegin;  // +0x0
    char mRest[0xc];         // +0x4
};

class CSSParser {
public:
    bool ParseBoxHeight(PropertyList* pList);  // 0x008f7f20

private:
    void Advance();                     // 0x008f3d90
    bool MatchLength(Length* pLength);  // 0x008f5560

    wchar_t* mpSourceURI;      // +0x00
    char mReaderStream[0x10];  // +0x04 CSSTokenReader: stream, mLineBegin, mCurrentLine
    MatchText mMatchText;      // +0x14 CSSTokenReader::mMatchText
    char mReaderResult[4];     // +0x24 CSSTokenReader::mResult
    int mToken;                // +0x28 CSSToken
    char mTokenRest[0x20];     // +0x2c
    StackAllocator* mAllocator;  // +0x4c
};

bool CSSParser::ParseBoxHeight(PropertyList* pList) {
    Length value(0.0f, Unit_Auto);
    bool bAuto = false;
    if (mToken == 3 /* TokenIdent */) {
        const wchar_t* pAuto = L"auto";
        const wchar_t* pText = mMatchText.mpBegin;
        bool bMismatch = false;
        wchar_t c;
        do {
            c = *pAuto;
            if (c != *pText) {
                bMismatch = true;
                break;
            }
            if (c == 0)
                break;
            c = pAuto[1];
            if (c != pText[1]) {
                bMismatch = true;
                break;
            }
            pAuto += 2;
            pText += 2;
        } while (c != 0);
        bAuto = !bMismatch;
    }
    if (bAuto) {
        Advance();
    } else if (!MatchLength(&value)) {
        return false;
    }
    pList->Add(CreatePropertyFunc(mAllocator, &StyleState::SetHeight, value));
    return true;
}

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
