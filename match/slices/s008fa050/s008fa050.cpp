// EA::XHTML::Style::CreateDefaultStylesheet (0x008fa050): builds the built-in user-agent stylesheet
// (display types, margins, fonts, list styles, link colours, table layout) for the XHTML renderer.
#include "types.h"
#include <stddef.h>

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

namespace EA {
namespace Allocator {

class StackAllocator {  // size 0x24 (PDB)
public:
    bool AllocateNewBlock(unsigned int nSize);  // 0x00928ba0

    void* Malloc(unsigned int nSize) {
        if ((mpCurrentBlockEnd - mpCurrentObjectBegin) - (int)nSize < 0) {
            if (!AllocateNewBlock(nSize))
                return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + nSize;
        mpCurrentObjectEnd = p + nSize;
        return p;
    }

    unsigned int mnDefaultBlockSize;  // +0x00
    void* mpCurrentBlock;             // +0x04
    char* mpCurrentBlockEnd;          // +0x08
    char* mpCurrentObjectBegin;       // +0x0c
    char* mpCurrentObjectEnd;         // +0x10
    void* mpCoreAllocationFunction;   // +0x14
    void* mpCoreFreeFunction;         // +0x18
    void* mpCoreFunctionContext;      // +0x1c
    void* mpTopBookmark;              // +0x20
};

}  // namespace Allocator
}  // namespace EA

inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator& allocator) throw() {
    return allocator.Malloc(nSize);
}
inline void operator delete(void*, EA::Allocator::StackAllocator&) throw() {}

namespace EA {
namespace XHTML {
namespace Style {

using EA::Allocator::StackAllocator;

enum Units {
    Unit_Number = 0, Unit_Pixels = 1, Unit_Points = 2, Unit_Picas = 3, Unit_Millimeters = 4,
    Unit_Centimeters = 5, Unit_Inches = 6, Unit_Ems = 7, Unit_Exs = 8, Unit_Percentage = 9,
    Unit_Auto = 10, Unit_Inherit = 11, Unit_BorderSize = 12, Unit_Unset = 13
};

enum EdgeIndex { Edge_Top = 0, Edge_Right = 1, Edge_Bottom = 2, Edge_Left = 3, Edge_All = 4 };

struct Length {  // size 0x8
    Length(float value, Units units) : mValue(value), mUnits(units) {}
    float mValue;  // +0x0
    Units mUnits;  // +0x4
};

// The property setters are pointers to StyleState members, formed while StyleState is still
// incomplete, so they use MSVC's 16-byte general (unknown-inheritance) representation.
class StyleState;

class Property {  // size 0x8
public:
    virtual void Apply(StyleState* pState) const;
    Property* mpNext;  // +0x4
};

class PropertyList {  // size 0x4
public:
    PropertyList() : mpFirst(0) {}
    void Add(Property* p) {
        p->mpNext = mpFirst;
        mpFirst = p;
    }
    Property* mpFirst;  // +0x0
};

class PropertyCollection {  // size 0x8
public:
    PropertyList mpProperties[2];  // +0x0
};

// font-family property: up to eight names (vtable 0x01439a6c). Its setter member is what fixes
// StyleState's member-pointer representation while the class is still incomplete.
class PropertyFuncNameList : public Property {  // size 0x40
public:
    void (StyleState::*mSetter)(const wchar_t** pNames, int nCount);  // +0x08
    const wchar_t* mNames[8];                                         // +0x18
    int mNameCount;                                                   // +0x38
};

template <class T>
Property* CreatePropertyFunc(StackAllocator* pAllocator, void (StyleState::*pSetter)(T), T arg);  // e.g. 0x008f33a0
template <class T, class U>
Property* CreatePropertyFunc(StackAllocator* pAllocator, void (StyleState::*pSetter)(T, U), T arg1,
                             U arg2);  // e.g. 0x008f3170
// PropertyFuncNameList (font-family) with a single name. 0x008f9fd0
Property* CreateNameListPropertyFunc(StackAllocator* pAllocator,
                                     void (StyleState::*pSetter)(const wchar_t** pNames, int nCount),
                                     const wchar_t* pName);

class StyleState {
public:
    void SetFontFamilies(const wchar_t** pNames, int nCount);       // 0x008f26b0
    void SetFontStyle(unsigned int style);                          // 0x008f2700
    void SetFontWeight(unsigned int weight);                        // 0x008f2760
    void SetColor(unsigned int color);                              // 0x008f27e0
    void SetBackgroundColor(unsigned int color);                    // 0x008f27f0
    void SetTextDecoration(uint16_t flags, uint16_t mask);          // 0x008f28c0
    void SetLineHeight(Length len);                                 // 0x008f2990
    void SetMargin(Length len, EdgeIndex edge);                     // 0x008f29b0
    void SetPadding(Length len, EdgeIndex edge);                    // 0x008f2a20
    void SetBorderWidth(Length len, EdgeIndex edge);                // 0x008f2a90
    void SetBorderStyle(unsigned int style, EdgeIndex edge);        // 0x008f2b40
    void SetBorderSpacing(Length len);                              // 0x008f2bc0
    void SetDisplay(unsigned int display);                          // 0x008f2c90
    void SetWhitespace(unsigned int mode);                          // 0x008f2ca0
    void SetListStyleType(unsigned int type);                       // 0x008f2cb0
    void SetFontSizeKeyword(unsigned int size);                     // 0x008fb8a0
    void SetCounterIncrement(const wchar_t* pName, int nIncrement); // 0x008fca70
};

class Selector {  // size 0x8
public:
    Selector() : mpNext(0) {}
    virtual bool Matches(void* pElement) const;

    // Out of line at 0x008f9fa0 (cl turned the recursion into a loop); inlined one level here.
    void Append(Selector* pSelector) {
        if (mpNext)
            mpNext->Append(pSelector);
        else
            mpNext = pSelector;
    }

    Selector* mpNext;  // +0x4
};

// Element-name selector (vtable 0x014399dc), built by Stylesheet::AddRule.
class TypeSelector : public Selector {  // size 0x10
public:
    TypeSelector(const wchar_t* pName) : mpName(pName) {}
    virtual bool Matches(void* pElement) const;
    const wchar_t* mpName;  // +0x8
    uint32_t mUnknownC;     // +0xc (not set by the ctor)
};

// Descendant-of selector (vtable 0x01439a0c).
class ParentSelector : public Selector {  // size 0x10
public:
    ParentSelector(Selector* pParent) : mpParentSelectors(pParent) {}
    virtual bool Matches(void* pElement) const;
    Selector* mpParentSelectors;  // +0x8
    uint32_t mUnknownC;           // +0xc
};

// Pseudo-class selector such as :link/:visited/:hover/:active (vtable 0x01439a00).
class PseudoClassSelector : public Selector {  // size 0x10
public:
    PseudoClassSelector(int pseudoClass) : mPseudoClass(pseudoClass) {}
    virtual bool Matches(void* pElement) const;
    int mPseudoClass;    // +0x8
    uint32_t mUnknownC;  // +0xc
};

class Rule {  // size 0x10
public:
    void AddProperty(Property* p) { mpProperties->mpProperties[0].Add(p); }
    void AppendSelector(Selector* p) { mpSelectors->Append(p); }

    Rule* mpNext;                       // +0x0
    Selector* mpSelectors;              // +0x4
    PropertyCollection* mpProperties;   // +0x8
    unsigned int mSpecificity;          // +0xc
};

class Stylesheet {  // size 0x70 in retail (0x6c in the 2008 PDB)
public:
    Stylesheet(const wchar_t* pBaseURI);  // 0x008f9db0
    virtual int AddRef();
    virtual int Release();

    // Adds a rule for one element name; a NULL collection gets a fresh one. 0x008f9cd0
    Rule* AddRule(const wchar_t* pElementName, PropertyCollection* pProperties);

    int mnRefCount;                // +0x04
    StackAllocator mAllocator;     // +0x08
    Rule* mpFirst;                 // +0x2c
    Rule* mpLast;                  // +0x30
    uint32_t mImportURLs[13];      // +0x34 fixed_vector<const wchar_t*,8>
    wchar_t* mpBaseURI;            // +0x68
    uint32_t mUnknown6C;           // +0x6c
};

Stylesheet* CreateDefaultStylesheet() {
    Stylesheet* pSS = new ("XHTML/Style/CreateDefaultStylesheet", 0, 0, 0, 0) Stylesheet(0);
    StackAllocator* pAlloc = &pSS->mAllocator;
    pSS->AddRef();
    Rule* pRule;
    PropertyCollection* pPC;

    pRule = pSS->AddRule(L"body", NULL);
    pRule->AddProperty(CreateNameListPropertyFunc(pAlloc, &StyleState::SetFontFamilies, L"web-default"));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_All));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetLineHeight, Length(1.1f, Unit_Number)));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetBackgroundColor, 0xffffffffu));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetColor, 0xff000000u));

    pPC = new (*pAlloc) PropertyCollection;
    pPC->mpProperties[0].Add(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 2u));
    pSS->AddRule(L"h1", pPC);
    pSS->AddRule(L"h2", pPC);
    pSS->AddRule(L"h3", pPC);
    pSS->AddRule(L"h4", pPC);
    pSS->AddRule(L"h5", pPC);
    pSS->AddRule(L"h6", pPC);
    pSS->AddRule(L"p", pPC);
    pSS->AddRule(L"ol", pPC);
    pSS->AddRule(L"dir", pPC);
    pSS->AddRule(L"menu", pPC);
    pSS->AddRule(L"div", pPC);
    pSS->AddRule(L"dt", pPC);
    pSS->AddRule(L"dd", pPC);
    pSS->AddRule(L"address", pPC);
    pSS->AddRule(L"blockquote", pPC);
    pSS->AddRule(L"pre", pPC);
    pSS->AddRule(L"form", pPC);
    pSS->AddRule(L"dl", pPC);

    pPC = new (*pAlloc) PropertyCollection;
    pPC->mpProperties[0].Add(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 3u));
    pSS->AddRule(L"b", pPC);
    pSS->AddRule(L"strong", pPC);
    pSS->AddRule(L"i", pPC);
    pSS->AddRule(L"em", pPC);
    pSS->AddRule(L"cite", pPC);
    pSS->AddRule(L"var", pPC);
    pSS->AddRule(L"tt", pPC);
    pSS->AddRule(L"code", pPC);
    pSS->AddRule(L"kbd", pPC);
    pSS->AddRule(L"samp", pPC);
    pSS->AddRule(L"img", pPC);
    pSS->AddRule(L"span", pPC);
    pSS->AddRule(L"a", pPC);
    pSS->AddRule(L"input", pPC);
    pSS->AddRule(L"button", pPC);
    pSS->AddRule(L"select", pPC);
    pSS->AddRule(L"nowrap", pPC);

    pRule = pSS->AddRule(L"h1", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Bottom));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontSizeKeyword, 6u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));

    pRule = pSS->AddRule(L"h2", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Bottom));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontSizeKeyword, 5u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));

    pRule = pSS->AddRule(L"h3", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Bottom));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontSizeKeyword, 4u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontStyle, 2u));

    pRule = pSS->AddRule(L"h4", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Bottom));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));

    pRule = pSS->AddRule(L"h5", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontStyle, 2u));

    pRule = pSS->AddRule(L"h6", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));

    pRule = pSS->AddRule(L"p", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Bottom));

    pPC = new (*pAlloc) PropertyCollection;
    pPC->mpProperties[0].Add(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));
    pSS->AddRule(L"b", pPC);
    pSS->AddRule(L"strong", pPC);

    pPC = new (*pAlloc) PropertyCollection;
    pPC->mpProperties[0].Add(CreatePropertyFunc(pAlloc, &StyleState::SetFontStyle, 2u));
    pSS->AddRule(L"i", pPC);
    pSS->AddRule(L"cite", pPC);
    pSS->AddRule(L"em", pPC);
    pSS->AddRule(L"var", pPC);
    pSS->AddRule(L"address", pPC);
    pSS->AddRule(L"blockquote", pPC);

    pPC = new (*pAlloc) PropertyCollection;
    pPC->mpProperties[0].Add(CreateNameListPropertyFunc(pAlloc, &StyleState::SetFontFamilies, L"monospace"));
    pSS->AddRule(L"pre", pPC);
    pSS->AddRule(L"tt", pPC);
    pSS->AddRule(L"code", pPC);
    pSS->AddRule(L"kbd", pPC);
    pSS->AddRule(L"samp", pPC);

    pRule = pSS->AddRule(L"u", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetTextDecoration, (uint16_t)1, (uint16_t)0));

    pRule = pSS->AddRule(L"strike", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetTextDecoration, (uint16_t)2, (uint16_t)0));

    pRule = pSS->AddRule(L"nowrap", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetWhitespace, 3u));

    pRule = pSS->AddRule(L"pre", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetWhitespace, 1u));

    pRule = pSS->AddRule(L"blockquote", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(3.0f, Unit_Ems), Edge_Left));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(3.0f, Unit_Ems), Edge_Right));

    pRule = pSS->AddRule(L"ul", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetListStyleType, 1u));

    pRule = pSS->AddRule(L"ul", NULL);
    pRule->AppendSelector(new (*pAlloc) ParentSelector(new (*pAlloc) TypeSelector(L"ul")));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetListStyleType, 3u));

    pRule = pSS->AddRule(L"ol", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetListStyleType, 4u));

    pRule = pSS->AddRule(L"dir", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetListStyleType, 1u));

    pRule = pSS->AddRule(L"li", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 5u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(5.0f, Unit_Ems), Edge_Left));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(0.6f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(0.6f, Unit_Ems), Edge_Bottom));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetCounterIncrement, L"list", 1));

    pRule = pSS->AddRule(L"a", NULL);
    pRule->AppendSelector(new (*pAlloc) PseudoClassSelector(3));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetColor, 0xff0000ffu));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetTextDecoration, (uint16_t)1, (uint16_t)0));

    pRule = pSS->AddRule(L"a", NULL);
    pRule->AppendSelector(new (*pAlloc) PseudoClassSelector(4));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetColor, 0xffff0000u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetTextDecoration, (uint16_t)1, (uint16_t)0));

    pRule = pSS->AddRule(L"a", NULL);
    pRule->AppendSelector(new (*pAlloc) PseudoClassSelector(6));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetColor, 0xff00ff00u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetTextDecoration, (uint16_t)1, (uint16_t)0));

    pRule = pSS->AddRule(L"a", NULL);
    pRule->AppendSelector(new (*pAlloc) PseudoClassSelector(5));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetColor, 0xffffff00u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetTextDecoration, (uint16_t)1, (uint16_t)0));

    pRule = pSS->AddRule(L"table", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 6u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetBorderSpacing, Length(1.0f, Unit_Pixels)));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetBorderWidth, Length(0.0f, Unit_Pixels), Edge_All));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetBorderStyle, 8u, Edge_All));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Top));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetMargin, Length(1.0f, Unit_Ems), Edge_Bottom));

    pRule = pSS->AddRule(L"tr", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 8u));

    pRule = pSS->AddRule(L"thead", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 10u));

    pRule = pSS->AddRule(L"tbody", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 9u));

    pRule = pSS->AddRule(L"tfoot", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 11u));

    pRule = pSS->AddRule(L"col", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 12u));

    pRule = pSS->AddRule(L"colgroup", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 13u));

    pRule = pSS->AddRule(L"td", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 14u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetPadding, Length(1.0f, Unit_Pixels), Edge_All));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetBorderStyle, 7u, Edge_All));

    pRule = pSS->AddRule(L"th", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 14u));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetPadding, Length(1.0f, Unit_Pixels), Edge_All));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetBorderStyle, 7u, Edge_All));
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetFontWeight, 700u));

    pRule = pSS->AddRule(L"caption", NULL);
    pRule->AddProperty(CreatePropertyFunc(pAlloc, &StyleState::SetDisplay, 15u));

    return pSS;
}

typedef char PmfSizeCheck[sizeof(void (StyleState::*)(unsigned int)) == 16 ? 1 : -1];

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
