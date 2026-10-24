// Slice s00896800 -- SporeApp retail bytes (EA::Text::TextStyleReader parser TU, part 2).
//
// This range continues the CSS-like style reader that the retail EAText revision kept in
// EATextStyleReader.cpp: ParseFontEffect, the property dispatcher ParseProperty, the per-statement
// ReadStyle, the top-level ReadStyles loop, the reader's name->id map constructor-initialiser and
// the reader constructor.  It reuses the Lexer templates from EAText/internal/EALexer.h and the
// TextStyleReader methods reconstructed in the sibling slice s00895630.
//
// Compile flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Iscratch_s00880170_inc /Iscratch_s00894440_inc

#include "types.h"

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_THREAD_SAFETY_ENABLED 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#include <EAText/internal/EALexer.h>

#include <string.h>
#include <stdlib.h>
#include <math.h>

// ---- retail helpers from the same translation unit (resolved elsewhere in the image) -----------
int      GetCharacterAsUTF16(uint16_t* pDest, int nDestCapacity, const char* pSrc, int nSrcLength);
uint32_t MakeColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
uint32_t __stdcall TextStyleReaderSkipCommand(int* pState);
void     AppendNarrow(void* pDest, const char* pSrc, unsigned nCount);

// name->id map / hashtable instantiations living in sibling slices
void**   NameStringMapFind(void* pMap, const void* pKey);
uint32_t* NameStringMapSubscript(void* pMap, const void* pKey);
void     FixedStringSet(void* pDest, const char* pBegin, const char* pEnd);
void     OperatorDelete(void* p);
const void* StyleManagerGetStyle(uint32_t pManager, uint32_t nId, void* pStyle);

// helpers only referenced from the name->id map constructor-initialiser
void* FixedPoolInit(void* pPool, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);
void* AllocBootstrap(uint32_t nBytes);
void  NameStringMapBuild(void* pState, ...);
uint32_t RehashPrime(uint32_t n);
void  NameStringMapDoRehash(void* pMap, uint32_t nNewBuckets);

// The retail reporter entry points are entered with the reader in ecx and one stack argument
// (ret 4), i.e. the same shape as a member call.  Declaring them as one keeps the call sequence
// identical while the definitions live outside this translation unit.
struct TextStyleReaderReporter
{
    void BeginToken(const void* pToken);
    void EndToken(const void* pToken);
};

// The image's shared empty UTF-16 string sentinel (eastl::gEmptyString16 at 0x01667bac, its
// terminator at 0x01667bad).  The reader's token strings are char-typed, so the sentinel is
// consumed as raw bytes.
namespace eastl { extern char16_t gEmptyString16[]; }

// A byte-accurate view of eastl::basic_string's three pointers, used by the constructor which
// seeds both token strings with the shared empty-string sentinel.
struct StringView
{
    const void* mpBegin;
    const void* mpEnd;
    void*       mpCapacity;
};

// A byte-accurate view of the reader's TokenReader base (CharStream mScanPos/mScanEnd, line
// bookkeeping and the matched-text string).  The lexer members are protected, so the ctor and
// the scan-position guards reach them through this named overlay.
struct ReaderBaseView
{
    const char* mScanPos;       // 0x00
    const char* mScanEnd;       // 0x04
    const char* mLineBegin;     // 0x08
    int32_t     mCurrentLine;   // 0x0c
    StringView  mMatchText;     // 0x10
};

namespace EA { namespace Text {

using namespace EA::Text::Lexer;

// ---- lexer instantiations used by the style reader ---------------------------------------------
typedef TokenReader<char, CharStream<char> > StyleReaderBase;

// ---- style reader ------------------------------------------------------------------------------
enum TextStyleToken
{
    TokenNone        = 0,
    TokenError       = 1,
    TokenIdent       = 3,
    TokenInteger     = 4,
    TokenHexInteger  = 5,
    TokenFloat       = 6,
    TokenString      = 7,
    TokenPound       = 8,   // '#'
    TokenAt          = 9,   // '@'
    TokenColon       = 10,  // ':'
    TokenSemicolon   = 11,  // ';'
    TokenOpenParen   = 12,  // '('
    TokenCloseParen  = 13,  // ')'
    TokenOpenBrace   = 14,  // '{'
    TokenCloseBrace  = 15,  // '}'
    TokenComma       = 16,  // ','
    TokenPlus        = 17,  // '+'
    TokenPercent     = 18   // '%'
};

// Property selector ids (index into ParseProperty's dispatch table at 0x00896cf4).
enum TextStylePropertyID
{
    PropertyColor            = 0,
    PropertyBackgroundColor  = 1,
    PropertyEmphasisStyle    = 2,
    PropertyFont             = 3,
    PropertyFontEffect       = 4,
    PropertyEmphasisPosition = 5,
    PropertyFontVariant      = 6,
    PropertyFontFamily       = 7,
    PropertyFontPitch        = 8,
    PropertyFontSize         = 9,
    PropertyFontSmooth       = 10,
    PropertyLineHeight       = 11,
    PropertyFontStyle        = 12,
    PropertyFontWeight       = 13,
    PropertyFontSizeAdjust   = 14,
    PropertyTextIndent       = 15,
    PropertyWordSpacing      = 16,
    PropertyTextDecoration   = 17,
    PropertyTextAlignment    = 18,
    PropertyTextTransform    = 19,
    PropertyTextWrap         = 20,
    PropertyLetterSpacing    = 21,
    PropertyVerticalAlign    = 22,
    PropertyTextOverflow     = 23,
    PropertyWhiteSpace       = 24,
    PropertyUnknown          = 25
};

// Property-name table (retail .data at 0x01549518).
static const IStaticDefinition<char, int> sPropertyTable[] =
{
    { "background-color", 1 }, { "color", 0 }, { "emphasis-position", 5 },
    { "emphasis-style", 2 },   { "font", 3 },  { "font-effect", 4 },
    { "font-family", 7 },      { "font-pitch", 8 }, { "font-size", 9 },
    { "font-size-adjust", 14 },{ "font-smooth", 10 }, { "font-style", 12 },
    { "font-variant", 6 },     { "font-weight", 13 }, { "letter-spacing", 21 },
    { "line-height", 11 },     { "text-alignment", 18 }, { "text-decoration", 17 },
    { "text-indent", 15 },     { "text-overflow", 23 }, { "text-transform", 19 },
    { "text-wrap", 20 },       { "vertical-align", 22 }, { "white-space", 24 },
    { "word-spacing", 16 },    { "invalid", 25 }
};

// Per-property value tables (each keyed by the enum it assigns).
static const IStaticDefinition<char, int> sJustify[] =
{
    { "bottom", 5 }, { "center", 1 }, { "left", 2 },
    { "none", 0 }, { "right", 3 }, { "top", 4 }
};

static const IStaticDefinition<char, float> sFontWeight[] =
{
    { "bold", 700.0f }, { "bolder", 900.0f }, { "lighter", 100.0f }, { "normal", 400.0f }
};

static const IStaticDefinition<char, int> sPitch[] =
{ { "fixed", 0 }, { "variable", 1 } };

static const IStaticDefinition<char, int> sHAlign[] =
{ { "center", 1 }, { "justify", 3 }, { "left", 0 }, { "right", 2 } };

static const IStaticDefinition<char, int> sTextWrap[] =
{
    { "char", 2 }, { "char-hyphen", 6 }, { "hyphen", 4 }, { "none", 0 },
    { "word", 1 }, { "word-char", 3 },   { "word-hyphen", 5 }
};

static const IStaticDefinition<char, int> sTextOverflow[] =
{ { "clip", 0 }, { "ellipsis", 1 }, { "fade", 2 } };

static const IStaticDefinition<char, unsigned short> sDecoration[] =
{
    { "line-through", 4 }, { "none", 0 }, { "overline", 2 }, { "underline", 1 }
};

static const IStaticDefinition<char, int> sDigitSub[] =
{
    { "context", 1 }, { "depressed", 3 }, { "invalid", 4 }, { "national", 2 }, { "none", 0 }
};

static const IStaticDefinition<char, int> sEmphasisStyle[] =
{ { "accent", 1 }, { "circle", 3 }, { "disc", 4 }, { "dot", 2 }, { "none", 0 } };

static const IStaticDefinition<char, int> sEmphasisPosition[] =
{ { "before", 1 }, { "none", 0 } };

static const IStaticDefinition<char, int> sPassword[] =
{ { "disc", 1 }, { "none", 0 } };

// ---- forward decls of local types ---------------------------------------------------------------
struct TextStyle;

// ---- TextStyle layout used by the parser -------------------------------------------------------
enum
{
    kMaxFontFamilies = 0x10,
    kMaxFamilyChars  = 0x20
};

// Retail TextStyle is a fixed-layout struct; only the members the parser names are declared.
struct TextStyle
{
    uint8_t  mFontName[0x200];      // 0x000
    float    mfFontSize;            // 0x200
    int32_t  mFontStyle;            // 0x204
    float    mfFontWeight;          // 0x208
    int32_t  mFontVariant;          // 0x20c
    int32_t  mPitch;                // 0x210
    int32_t  mSmooth;               // 0x214
    int32_t  mFontEffectType;       // 0x218
    float    mfFontEffectSize;      // 0x21c
    float    mfFontEffectOffset;    // 0x220
    uint32_t mColor;                // 0x224
    uint32_t mBackgroundColor;      // 0x228
    uint32_t mShadowColor;          // 0x22c
    uint32_t mUnderlineColor;       // 0x230
    uint32_t mOverlineColor;        // 0x234
    int32_t  mDecoration;           // 0x238
    int32_t  mTextWrap;             // 0x244
    int32_t  mJustify;              // 0x248
    int32_t  mHAlignment;           // 0x24c
    int32_t  mTextOverflow;         // 0x250
    int32_t  mVerticalAlign;        // 0x254
    int32_t  mEmphasisStyle;        // 0x258
    int32_t  mEmphasisPosition;     // 0x25c
    int32_t  mDigitSubstitution;    // 0x260
    int32_t  mPasswordMode;         // 0x264
    float    mfLineHeight;          // 0x268
    float    mfTextIndent;          // 0x26c
    float    mfLetterSpacing;       // 0x270
    float    mfWordSpacing;         // 0x274
};

// ---- reader ------------------------------------------------------------------------------------
// Retail layout: TokenReader<char,CharStream<char>> occupies 0x00..0x1f in this configuration
// (its eastl string reserves one more dword than the retail build), then the reader's own token
// fields.  This parser slice additionally stores the owning manager at 0x20 and the name->id map
// at 0x44 (the sibling slice s00895630 did not need those members).
class TextStyleReader : public StyleReaderBase
{
public:
    typedef StyleReaderBase::string_type     string_type;
    typedef StyleReaderBase::position_type   position_type;

    uint32_t        mpManager;          // 0x20
    int32_t         mToken;             // 0x24
    int32_t         mTokenLine;         // 0x28
    position_type   mTokenLineStart;    // 0x2c
    position_type   mTokenPos;          // 0x30
    string_type     mTokenValue;        // 0x34

    uint8_t         mStyleNames[0x338]; // 0x44  NameStringMap (hash_map + pool + rehash policy)

    void*           mpCallback;         // 0x380
    void*           mpCallbackContext;  // 0x384
    void*           mpErrorCallback;    // 0x388
    void*           mpErrorContext;     // 0x38c
    int32_t         mResult;            // 0x390
    int32_t         mWarningCount;      // 0x394

    bool Advance();
    bool MatchToken(TextStyleToken token);
    bool MatchFloat(float* pValue);
    bool MatchInteger(uint32_t* pValue);
    bool MatchColor(uint32_t* pValue);

    template<typename T, int N>
    bool MatchSymbol(const IStaticDefinition<char, T>* pTable, T* pValue);

    bool ParseFontFamilies(intptr_t pDest);
    bool ParseFontSize(intptr_t pStyle);
    bool MatchLength(float* pValue, float defaultLength);
    bool SkipCommand();

    bool ParseFontEffect(TextStyle* pStyle);
    bool ParseProperty(TextStyle* pStyle);
    uint32_t LookupStyleId();
    bool ReadStyle(char* pName, unsigned nNameCapacity, uint32_t* pId, TextStyle* pStyle);
    bool ReadStyles();

    TextStyleReader* Construct(uint32_t pManager, const char* pBegin, const char* pEnd);
};

// The eastl fixed_string<char,12,1> key handed to the hashtable.
struct NameKey
{
    const char* mpBegin;
    const char* mpEnd;
    void*       mpCapacity;
};

// @ 0x00896800  EA::Text::TextStyleReader::ParseFontEffect
bool TextStyleReader::ParseFontEffect(TextStyle* pStyle)
{
    if (mToken == TokenIdent)
    {
        if (strcmp("none", mMatchText.c_str()) == 0)
        {
            Advance();
            return true;
        }
    }

    if (MatchSymbol<int, 5>(sDigitSub, &pStyle->mFontEffectType))
    {
        if (mToken == TokenFloat || mToken == TokenInteger)
        {
            pStyle->mfFontEffectSize = (float)strtod(mMatchText.c_str(), 0);
            Advance();

            if (MatchFloat(&pStyle->mfFontEffectOffset))
            {
                if (MatchColor(&pStyle->mShadowColor))
                {
                    if (MatchColor(&pStyle->mUnderlineColor))
                    {
                        int32_t effect = pStyle->mFontEffectType;
                        if (effect == 3 || effect == 4)
                        {
                            if (!MatchColor(&pStyle->mOverlineColor))
                                return false;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// @ 0x00896900  EA::Text::TextStyleReader::ParseProperty
bool TextStyleReader::ParseProperty(TextStyle* pStyle)
{
    int property;

    if (!MatchSymbol<int, 3>(sPropertyTable, &property))
    {
        reinterpret_cast<TextStyleReaderReporter*>(this)->BeginToken((const void*)0x02600008);
        return false;
    }

    if (mToken != TokenColon)
        return true;

    swap(mTokenValue, mMatchText);
    Advance();

    switch (property)
    {
        case PropertyColor:
            return MatchColor(&pStyle->mBackgroundColor);

        case PropertyBackgroundColor:
            return MatchColor(&pStyle->mColor);

        case PropertyEmphasisStyle:
            return MatchSymbol<int, 5>(sDigitSub, &pStyle->mDigitSubstitution);

        case PropertyFont:
            for (;;)
            {
                if (MatchSymbol<int, 6>(sJustify, &pStyle->mFontStyle))
                    continue;
                if (MatchSymbol<int, 2>(sPassword, &pStyle->mFontVariant))
                    continue;
                if (MatchSymbol<float, 4>(sFontWeight, &pStyle->mfFontWeight))
                    continue;

                if (!ParseFontSize((intptr_t)pStyle))
                    return false;

                return ParseFontFamilies((intptr_t)pStyle);
            }

        case PropertyFontEffect:
            return ParseFontEffect(pStyle);

        case PropertyEmphasisPosition:
            return MatchSymbol<int, 2>(sEmphasisPosition, &pStyle->mEmphasisPosition);

        case PropertyFontVariant:
            return MatchSymbol<int, 5>(sEmphasisStyle, &pStyle->mEmphasisStyle);

        case PropertyFontFamily:
            return ParseFontFamilies((intptr_t)pStyle);

        case PropertyFontPitch:
            return MatchSymbol<int, 2>(sPitch, &pStyle->mPitch);

        case PropertyFontSize:
            return ParseFontSize((intptr_t)pStyle);

        case PropertyFontSmooth:
            return MatchSymbol<int, 6>(sJustify, &pStyle->mSmooth);

        case PropertyLineHeight:
            return MatchLength(&pStyle->mfLineHeight, 1.0f);

        case PropertyFontStyle:
            return MatchSymbol<int, 6>(sJustify, &pStyle->mFontStyle);

        case PropertyFontWeight:
            return MatchSymbol<int, 2>(sPassword, &pStyle->mFontVariant);

        case PropertyFontSizeAdjust:
            if (MatchFloat(&pStyle->mfFontWeight))
                return true;
            return MatchSymbol<float, 4>(sFontWeight, &pStyle->mfFontWeight);

        case PropertyTextIndent:
            return MatchLength(&pStyle->mfTextIndent, 0.0f);

        case PropertyWordSpacing:
            return MatchLength(&pStyle->mfWordSpacing, 0.0f);

        case PropertyTextDecoration:
        {
            unsigned short value = 0;

            if (MatchSymbol<unsigned short, 4>(sDecoration, &value))
            {
                for (;;)
                {
                    if (value != 0)
                        pStyle->mDecoration |= value & 0xffff;
                    else
                        pStyle->mDecoration = 0;

                    if (!MatchSymbol<unsigned short, 4>(sDecoration, &value))
                        break;
                }
            }
            return true;
        }

        case PropertyTextAlignment:
            return MatchSymbol<int, 4>(sHAlign, &pStyle->mHAlignment);

        case PropertyTextTransform:
            return MatchSymbol<int, 6>(sJustify, &pStyle->mVerticalAlign);

        case PropertyTextWrap:
            return MatchSymbol<int, 6>(sJustify, &pStyle->mJustify);

        case PropertyLetterSpacing:
            return MatchSymbol<int, 2>(sPitch, &pStyle->mPasswordMode);

        case PropertyVerticalAlign:
            return MatchSymbol<int, 7>(sTextWrap, &pStyle->mTextWrap);

        case PropertyTextOverflow:
            return MatchSymbol<int, 3>(sTextOverflow, &pStyle->mTextOverflow);

        case PropertyWhiteSpace:
            return MatchLength(&pStyle->mfLetterSpacing, 0.0f);
    }

    reinterpret_cast<TextStyleReaderReporter*>(this)->BeginToken((const void*)0x02600008);
    return false;
}

// ReadStyle (0x00896d60) inlined block -- build the fixed_string key from mTokenValue and look its
// id up in the reader's name map.
uint32_t TextStyleReader::LookupStyleId()
{
    NameKey key;
    key.mpBegin    = mTokenValue.c_str();
    key.mpEnd      = mTokenValue.c_str() + mTokenValue.length();
    key.mpCapacity = (void*)key.mpBegin;

    void** pSlot = NameStringMapFind(mStyleNames, &key);
    return *(uint32_t*)((uint8_t*)*pSlot + 0x20);
}

// @ 0x00896d60  EA::Text::TextStyleReader::ReadStyle
bool TextStyleReader::ReadStyle(char* pName, unsigned nNameCapacity, uint32_t* pId, TextStyle* pStyle)
{
    uint16_t familyNames[kMaxFontFamilies][kMaxFamilyChars];

    while (mToken == TokenAt)
    {
        swap(mTokenValue, mMatchText);
        Advance();

        int i = 0;
        uint8_t* pCur   = (uint8_t*)familyNames;
        uint8_t* pLimit = (uint8_t*)&familyNames[kMaxFontFamilies][0];

        while (mToken != TokenSemicolon)
        {
            if (mToken == TokenIdent || mToken == TokenString)
            {
                swap(mTokenValue, mMatchText);
                Advance();

                uint8_t* pNext = pCur + (mTokenValue.length() + 1) * 2;
                if (pNext < pLimit && i < kMaxFontFamilies)
                {
                    GetCharacterAsUTF16((uint16_t*)pCur, (int)((pLimit - pCur) >> 1),
                                        mTokenValue.c_str(), -1);
                    pCur = pNext;
                    ++i;
                }
                continue;
            }

            if (mpErrorCallback != 0)
                ((void(__cdecl*)(int, int, void*))mpErrorCallback)(0x02600007, mTokenLine, mpErrorContext);
            mResult = 0x02600002;
            return false;
        }

        swap(mTokenValue, mMatchText);
        Advance();

        if (mpCallback != 0)
            ((void(__cdecl*)(int, void*, void*))mpCallback)(i, familyNames, mpCallbackContext);
    }

    pName[0] = 0;

    if (mToken == TokenIdent)
    {
        swap(mTokenValue, mMatchText);
        Advance();

        AppendNarrow(pName, mTokenValue.c_str(), nNameCapacity);

        if (mToken == TokenOpenParen)
        {
            swap(mTokenValue, mMatchText);
            Advance();

            if (!MatchInteger(pId))
            {
                reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600005);
                return false;
            }
            if (!MatchToken(TokenCloseParen))
            {
                reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600005);
                return false;
            }
        }
    }
    else if (mToken == TokenString)
    {
        swap(mTokenValue, mMatchText);
        Advance();

        AppendNarrow(pName, mTokenValue.c_str(), nNameCapacity);
    }

    if (mToken == TokenColon)
    {
        swap(mTokenValue, mMatchText);
        Advance();

        uint32_t id = 0;
        bool     haveId = false;

        if (mToken == TokenIdent)
        {
            swap(mTokenValue, mMatchText);
            Advance();
            id = LookupStyleId();
            haveId = true;
        }
        else if (MatchToken(TokenString))
        {
            id = LookupStyleId();
            haveId = true;
        }
        else if (MatchInteger(&id))
        {
            haveId = true;
        }

        if (haveId)
        {
            if (StyleManagerGetStyle(mpManager, id, pStyle) == 0)
            {
                reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600006);
                return false;
            }
        }
        else
        {
            *pStyle = TextStyle();
        }
    }
    else
    {
        *pStyle = TextStyle();
    }

    if (mToken == TokenOpenBrace)
    {
        swap(mTokenValue, mMatchText);
        Advance();

        if (reinterpret_cast<ReaderBaseView*>(this)->mScanPos < reinterpret_cast<ReaderBaseView*>(this)->mScanEnd)
        {
            do
            {
                if (mToken == TokenCloseBrace)
                {
                    swap(mTokenValue, mMatchText);
                    Advance();

                    if (pName[0] != 0)
                    {
                        NameKey key;
                        key.mpBegin    = pName;
                        key.mpEnd      = pName + strlen(pName);
                        key.mpCapacity = (void*)pName;

                        uint32_t* pSlot = NameStringMapSubscript(mStyleNames, &key);
                        *pSlot = *pId;

                        FixedStringSet(pName, pName, pName + strlen(pName));
                    }
                    return true;
                }

                if (!ParseProperty(pStyle))
                {
                    ++mWarningCount;
                    if (mpErrorCallback != 0)
                        ((void(__cdecl*)(int, int, void*))mpErrorCallback)(0x02600009, mTokenLine, mpErrorContext);
                    mResult = 0x02600009;

                    SkipCommand();

                    ++mWarningCount;
                    if (mpErrorCallback != 0)
                        ((void(__cdecl*)(int, int, void*))mpErrorCallback)(0x02600009, mTokenLine, mpErrorContext);
                    mResult = 0x02600009;
                }
                else if (mToken == TokenSemicolon)
                {
                    swap(mTokenValue, mMatchText);
                    Advance();
                }
                else if (mToken != TokenCloseBrace)
                {
                    reinterpret_cast<TextStyleReaderReporter*>(this)->BeginToken((const void*)0x02600009);
                    SkipCommand();
                }
            } while (reinterpret_cast<ReaderBaseView*>(this)->mScanPos < reinterpret_cast<ReaderBaseView*>(this)->mScanEnd);
        }

        return false;
    }

    return true;
}

// @ 0x00897350  EA::Text::TextStyleReader::ReadStyles
bool TextStyleReader::ReadStyles()
{
    TextStyle style;
    uint32_t  id = 0xfffffffe;

    while (reinterpret_cast<ReaderBaseView*>(this)->mScanPos < reinterpret_cast<ReaderBaseView*>(this)->mScanEnd)
    {
        char name[kMaxFamilyChars];

        if (!ReadStyle(name, kMaxFamilyChars, &id, &style))
            return false;
    }

    return true;
}

// @ 0x00897460  EA::Text::TextStyleReader::NameStringMap constructor-initialiser
// Entered with the map (this) in ecx and two allocator parameters on the stack (ret 8).
void* TextStyleReaderNameMapInit(void* pMap, void* pPoolBase, void* pParamB)
{
    uint8_t* pThis = (uint8_t*)pMap;

    FixedPoolInit(pThis + 0x78, 0x258, 0x28, 4, 0, 0);

    AllocBootstrap(0x10);

    NameStringMapBuild(pPoolBase, pParamB, pThis + 0x78 + 0x258, pThis + 0x34, pThis + 0x78);

    *(uint32_t*)(pThis + 0x10) = 0x461c4000;
    *(uint32_t*)(pThis + 0x14) = 0x40000000;
    *(uint32_t*)(pThis + 0x18) = 0;

    uint32_t n = RehashPrime(*(uint32_t*)(pThis + 0xc));
    if (*(uint32_t*)(pThis + 8) < n)
        NameStringMapDoRehash(pThis, n);

    return pThis;
}

// @ 0x00897530  EA::Text::TextStyleReader::TextStyleReader(StyleManager*, const char*, const char*)
TextStyleReader* TextStyleReader::Construct(uint32_t pManager, const char* pBegin, const char* pEnd)
{
    ReaderBaseView* base = reinterpret_cast<ReaderBaseView*>(this);
    base->mScanEnd     = pEnd;
    base->mScanPos     = pBegin;
    base->mLineBegin   = pBegin;
    base->mCurrentLine = 1;

    const char* pEmpty = (const char*)eastl::gEmptyString16;

    reinterpret_cast<StringView*>(&mMatchText)->mpBegin    = pEmpty;
    reinterpret_cast<StringView*>(&mMatchText)->mpEnd      = pEmpty;
    reinterpret_cast<StringView*>(&mMatchText)->mpCapacity = (void*)(pEmpty + 1);

    mpManager       = pManager;
    mToken          = TokenNone;
    mTokenLine      = 0;
    mTokenLineStart = 0;
    mTokenPos       = 0;

    reinterpret_cast<StringView*>(&mTokenValue)->mpBegin    = pEmpty;
    reinterpret_cast<StringView*>(&mTokenValue)->mpEnd      = pEmpty;
    reinterpret_cast<StringView*>(&mTokenValue)->mpCapacity = (void*)(pEmpty + 1);

    TextStyleReaderNameMapInit(mStyleNames, (void*)pBegin, (void*)pEnd);

    mpCallback        = 0;
    mpCallbackContext = 0;
    mpErrorCallback   = 0;
    mpErrorContext    = 0;
    mResult           = 0;
    mWarningCount     = 0;

    Advance();
    return this;
}

}} // namespace EA::Text

// A float range (low/high) with the retail validator; entered with the object in ecx and no stack
// arguments (plain __thiscall member).
struct FloatRange
{
    uint8_t mPad[0xa0];
    float   mfLow;      // 0xa0
    float   mfHigh;     // 0xa4

    // 0x008975c0: (float)floor(low) - (float)ceil(high)
    float Validate();
};

// @ 0x008975c0
float FloatRange::Validate()
{
    float lo = (float)floor((double)mfLow);
    return lo - (float)ceil((double)mfHigh);
}

// The three tiny members below are pairs/triples of fields; they are entered with the object in
// ecx and take their operands on the stack (ret 4 / ret 0xc).
struct ValueFlagPair
{
    void* mpValue;      // 0x00
    void* mpFlag;       // 0x04

    ValueFlagPair* Store(void* pValue);

    void Assign(void* pValue);
};

struct TripleFloat
{
    uint8_t mPad[0x3c0];
    float   mfA;        // 0x3c0
    float   mfB;        // 0x3c4
    float   mfC;        // 0x3c8

    void Set(float a, float b, float c);
};

// @ 0x00897600  store a value and clear the paired flag (returns *this)
ValueFlagPair* ValueFlagPair::Store(void* pValue)
{
    mpValue = pValue;
    mpFlag  = 0;
    return this;
}

// @ 0x00897620  clear the paired flag, then store a non-null value
void ValueFlagPair::Assign(void* pValue)
{
    mpFlag = 0;
    if (pValue != 0)
        mpValue = pValue;
}

// @ 0x00897640  store three floats
void TripleFloat::Set(float a, float b, float c)
{
    mfA = a;
    mfB = b;
    mfC = c;
}
