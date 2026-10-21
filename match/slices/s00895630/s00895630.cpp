// Slice s00895630 -- SporeApp retail bytes (EA::Text::TextStyleReader parser TU).
//
// The range is the CSS-like style reader that the retail EAText revision kept in
// EATextStyleReader.cpp (the vendored EAWebKit drop has an empty stub header).  It uses the
// Lexer templates from EAText/internal/EALexer.h, so the lexer instantiations at the front of
// the range are byte-identical to the real upstream header code.
//
// Compile flags: /O2 /MD /Gy /TP /arch:SSE /Iscratch_s00880170_inc /Iscratch_s00894440_inc

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

#include <stdlib.h>

// Retail helpers from the same translation unit (implemented / resolved elsewhere in the image).
int  GetCharacterAsUTF16(uint16_t* pDest, int nDestCapacity, const char* pSrc, int nSrcLength);
uint32_t __stdcall TextStyleReaderSkipCommand(int* pState);
uint32_t MakeColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

// The retail reporter is entered with the reader in ecx and one stack argument (ret 4), i.e. the
// same shape as a member call.  Declaring it as one keeps the call sequence identical while the
// definition lives outside this translation unit.
struct TextStyleReaderReporter
{
    void BeginToken(const void* pToken);
    void EndToken(const void* pToken);
};

namespace EA { namespace Text {

using namespace EA::Text::Lexer;

// ---- lexer instantiations used by the style reader ---------------------------------
// The reader lexes with Lexer::TokenReader<char, Lexer::CharStream<char>>.
typedef TokenReader<char, CharStream<char> > StyleReaderBase;

// Identifier start:  LowerCase | UpperCase | Underscore
typedef Alternative<Alternative<Range<97,122>, Range<65,90> >,
                    Character<95> > IdentStartExpr;
// Identifier continuation: LowerCase | UpperCase | Underscore | Digit | '-'
typedef Alternative<Alternative<Alternative<Alternative<Range<97,122>, Range<65,90> >,
                                              Character<95> >,
                                Range<48,57> >,
                    Character<45> > IdentExpr;
// sign, digit, hex prefix and hex digit predicates
typedef Character2<45,43> SignExpr;
typedef Range<48,57>     DigitExpr;
typedef Character2<120,88> HexPrefixExpr;
typedef Alternative<Alternative<Range<97,102>, Range<65,70> >, Range<48,57> > HexDigitExpr;

template bool StyleReaderBase::Match<IdentStartExpr>(const MatchExpression<IdentStartExpr>&);
// @ 0x00895630  TokenReader<char,CharStream<char> >::Match<identifier continuation>
template bool StyleReaderBase::Match<IdentExpr>(const MatchExpression<IdentExpr>&);
// @ 0x00895680  TokenReader<char,CharStream<char> >::Match<Character2<'-','+'> >
template bool StyleReaderBase::Match<SignExpr>(const MatchExpression<SignExpr>&);
// @ 0x008956c0  TokenReader<char,CharStream<char> >::Match<Range<'0','9'> >
template bool StyleReaderBase::Match<DigitExpr>(const MatchExpression<DigitExpr>&);
// @ 0x008956f0  TokenReader<char,CharStream<char> >::Match<Character2<'x','X'> >
template bool StyleReaderBase::Match<HexPrefixExpr>(const MatchExpression<HexPrefixExpr>&);
// @ 0x00895730  TokenReader<char,CharStream<char> >::Match<hex digit alternative>
template bool StyleReaderBase::Match<HexDigitExpr>(const MatchExpression<HexDigitExpr>&);
// @ 0x00895770  TokenReader<char,CharStream<char> >::MatchWhile<Range<'0','9'> >
template void StyleReaderBase::MatchWhile<DigitExpr>(const MatchExpression<DigitExpr>&);

// ---- style reader -----------------------------------------------------------------
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

// ---- style tables (retail .data) ---------------------------------------------------
static const IStaticDefinition<char, float> sUnits[] =
{
    { "cm", 28.346457f }, { "in", 72.0f }, { "mm", 2.8346457f },
    { "pc", 12.0f }, { "pt", 1.0f }, { "px", 1.0f }
};

static const IStaticDefinition<char, float> sFontSizes[] =
{
    { "large", 13.8f }, { "medium", 12.0f }, { "small", 10.434783f },
    { "x-large", 15.87f }, { "x-small", 9.0737409f }, { "xx-large", 18.250496f },
    { "xx-small", 7.8902435f }
};

static const IStaticDefinition<char, float> sFontWeights[] =
{
    { "bold", 700.0f }, { "bolder", 900.0f }, { "lighter", 100.0f }, { "normal", 400.0f }
};

static const IStaticDefinition<char, unsigned short> sVariants[] =
{
    { "normal", 0 }, { "small-caps", 1 }, { "fixed", 0 }, { "variable", 1 }
};

// Retail layout: TokenReader<char,CharStream<char>> occupies 0x00..0x1f in this
// configuration (its eastl string reserves one more dword than the retail build), four bytes of
// unsaved state follow, then the reader's own token fields.
class TextStyleReader : public StyleReaderBase { public:
    typedef StyleReaderBase::string_type     string_type;
    typedef StyleReaderBase::position_type   position_type;

    uint32_t        mPad0;          // 0x20
    int32_t         mToken;         // 0x24
    int32_t         mTokenLine;     // 0x28
    position_type   mTokenLineStart;// 0x2c
    position_type   mTokenPos;      // 0x30
    string_type     mTokenValue;    // 0x34

    bool MatchString(char quote);
    bool Advance();
    bool MatchToken(TextStyleToken token);
    bool MatchSymbol(const char* symbol);
    bool MatchFloat(float* pValue);
    bool MatchInteger(uint32_t* pValue);
    bool MatchColor(uint32_t* pValue);

    template<typename T, int N>
    bool MatchSymbol(const IStaticDefinition<char, T>* pTable, T* pValue);

    bool ParseFontFamilies(intptr_t pDest);
    bool ParseFontSize(intptr_t pStyle);
    bool MatchLength(float* pValue, float defaultLength);
    bool SkipCommand();
};

// @ 0x008957b0  EA::Text::TextStyleReader::MatchString
bool TextStyleReader::MatchString(char quote)
{
    mMatchText.clear();

    for (;;)
    {
        if (!mStream.More())
            return false;

        if (mStream.Current() == quote)
        {
            mStream.Advance();
            return true;
        }

        if (!mStream.More())
            return false;

        Append(mStream.Current());
        mStream.Advance();
    }
}

// @ 0x00895d00  EA::Text::TextStyleReader::MatchToken
bool TextStyleReader::MatchToken(TextStyleToken token)
{
    if (mToken == (int32_t)token)
    {
        swap(mTokenValue, mMatchText);
        Advance();
        return true;
    }
    return false;
}

// @ 0x00895d40  EA::Text::TextStyleReader::MatchSymbol(const char*)
bool TextStyleReader::MatchSymbol(const char* symbol)
{
    if (mToken == TokenIdent)
    {
        if (strcmp(symbol, mMatchText.c_str()) == 0)
        {
            Advance();
            return true;
        }
    }
    return false;
}

// @ 0x00895d90  EA::Text::TextStyleReader::MatchFloat
bool TextStyleReader::MatchFloat(float* pValue)
{
    if (mToken == TokenFloat || mToken == TokenInteger)
    {
        *pValue = (float)strtod(mMatchText.c_str(), 0);
        Advance();
        return true;
    }
    return false;
}

// @ 0x00895dd0  EA::Text::TextStyleReader::MatchInteger
bool TextStyleReader::MatchInteger(uint32_t* pValue)
{
    if (mToken == TokenInteger)
    {
        *pValue = strtoul(mMatchText.c_str(), 0, 10);
        Advance();
        return true;
    }
    if (mToken == TokenHexInteger)
    {
        *pValue = strtoul(mMatchText.c_str(), 0, 16);
        Advance();
        return true;
    }
    return false;
}

// @ 0x00896120  EA::Text::TextStyleReader::ParseFontFamilies
bool TextStyleReader::ParseFontFamilies(intptr_t pDest)
{
    unsigned i = 0;
    intptr_t pCur = pDest;

    for (;;)
    {
        if (mToken == TokenIdent)
            swap(mTokenValue, mMatchText);
        else if (mToken == TokenString)
            swap(mTokenValue, mMatchText);
        else
            goto Done;

        Advance();

        if (i < 8)
        {
            GetCharacterAsUTF16((uint16_t*)pCur, 0x20, mTokenValue.c_str(), -1);
            ++i;
            pCur += 0x40;
        }

        if (mToken != TokenComma)
            break;

        swap(mTokenValue, mMatchText);
        Advance();
    }

Done:
    if (i < 8)
    {
        uint16_t* p = (uint16_t*)(pDest + i * 0x40);
        unsigned n = 8 - i;
        i += n;
        do
        {
            *p = 0;
            p += 0x20;
        } while (--n);
    }

    return i > 0;
}

// @ 0x00896210  eastl::hash_map<fixed_string<char,12,1>, uint32_t, ...>::operator[]
// Retail body: hashtable::find(key); if the returned node is the end bucket, build a temporary
// fixed_string and call NameStringMapDoInsertValue(..., 0); then return &node->mValue (node+0x20).
// It is the map's operator[] instantiation, and neither the fixed_hashtable_allocator<17,40,15,4,0,1>
// nor the NameStringHash functor is imported by this translation unit, so the body is not
// reconstructed (recorded in nonmatching.txt).

// @ 0x008962d0  MatchSymbol<IStaticDefinition<char, Effect>, 6> (unit table)
// @ 0x00896330  MatchSymbol<IStaticDefinition<char, TextStylePropertyID>, 7> (font sizes)
// @ 0x008963f0  MatchSymbol<IStaticDefinition<char, float>, 4> (font weights)
// @ 0x00896450  MatchSymbol<IStaticDefinition<char, unsigned short>, 4> (variants)
template<typename T, int N>
bool TextStyleReader::MatchSymbol(const IStaticDefinition<char, T>* pTable, T* pValue)
{
    if (mToken == TokenIdent)
    {
        eastl::pair<const IStaticDefinition<char, T>*, const IStaticDefinition<char, T>*>
            found = eastl::equal_range(pTable, pTable + N, mMatchText.c_str());
        if (found.first + 1 == found.second)
        {
            *pValue = found.first->mValue;
            Advance();
            return true;
        }
    }
    return false;
}

template bool TextStyleReader::MatchSymbol<float, 6>(const IStaticDefinition<char, float>*, float*);
template bool TextStyleReader::MatchSymbol<float, 7>(const IStaticDefinition<char, float>*, float*);
template bool TextStyleReader::MatchSymbol<float, 4>(const IStaticDefinition<char, float>*, float*);
template bool TextStyleReader::MatchSymbol<unsigned short, 4>(const IStaticDefinition<char, unsigned short>*, unsigned short*);

// @ 0x00895cc0  EA::Text::TextStyleReader::SkipCommand
struct TextStyleReaderCommandState
{
    int mState[4];
    TextStyleReaderCommandState() {}
};

bool TextStyleReader::SkipCommand()
{
    static TextStyleReaderCommandState sCommandState;

    if (mToken != TokenSemicolon)
    {
        TextStyleReaderSkipCommand(sCommandState.mState);

        if (mStream.More() && mStream.Current() == ';')
            mStream.Advance();
    }

    return Advance();
}

// @ 0x00895e30  EA::Text::TextStyleReader::MatchColor
bool TextStyleReader::MatchColor(uint32_t* pValue)
{
    string_type& text = mMatchText;

    if (mToken == TokenPound)
    {
        static MatchRange<'0','9'>      Digit;
        static MatchEither<MatchRange<'a','f'>, MatchRange<'A','F'> > HexAlpha;

        text.clear();

        int i = 0;
        do
        {
            if (!Match(Digit | HexAlpha))
                break;
            ++i;
        } while (i < 8);

        uint32_t value = (uint32_t)strtoul(text.c_str(), 0, 16);

        size_t n = text.length();
        if (n != 8)
        {
            if (n == 6)
            {
                *pValue = value | 0xff000000;
                Advance();
                return true;
            }

            if (n == 4)
            {
                uint32_t t = (((value & 0xf000) << 4 | (value & 0xf00)) << 4 | (value & 0xf0)) << 4 | (value & 0xf);
                value = (t << 4) | t;
            }
            else
            {
                if (n != 3)
                {
                    reinterpret_cast<TextStyleReaderReporter*>(this)->BeginToken((const void*)0x02600004);
                    Advance();
                    return false;
                }

                uint32_t t = ((value & 0xf00) << 4 | (value & 0xf0)) << 4 | (value & 0xf);
                value = ((t | 0xfff00000) << 4) | t;
            }
        }

        *pValue = value;
        Advance();
        return true;
    }
    else
    {
        if (!MatchSymbol("rgb"))
            return false;

        if (!MatchToken(TokenOpenParen))
        {
            reinterpret_cast<TextStyleReaderReporter*>(this)->BeginToken((const void*)0x02600004);
            return false;
        }

        int i = 0;
        float rgb[3];

        do
        {
            if (mToken == TokenFloat || mToken == TokenInteger)
            {
                float value = (float)strtod(text.c_str(), 0);
                Advance();

                if (mToken == TokenPercent)
                {
                    swap(mTokenValue, text);
                    Advance();
                    value *= 2.55f;
                }

                rgb[i] = value;
                ++i;

                if (mToken != TokenComma)
                    break;

                swap(mTokenValue, text);
                Advance();
            }
        } while (i < 3);

        if (i != 3 || !MatchToken(TokenCloseParen))
        {
            reinterpret_cast<TextStyleReaderReporter*>(this)->BeginToken((const void*)0x02600004);
            return false;
        }

        float r = rgb[0];
        if (r < 0.0f)
            r = 0.0f;
        else if (r > 255.0f)
            r = 255.0f;
        unsigned char rb = (unsigned char)r;

        float g = rgb[1];
        if (g < 0.0f)
            g = 0.0f;
        else if (g > 255.0f)
            g = 255.0f;
        unsigned char gb = (unsigned char)g;

        float b = rgb[2];
        if (b < 0.0f)
            b = 0.0f;
        else if (b > 255.0f)
            b = 255.0f;
        unsigned char bb = (unsigned char)b;

        *pValue = MakeColor(0xff, rb, gb, bb);
        return true;
    }
}

// @ 0x008966f0  EA::Text::TextStyleReader::MatchLength
bool TextStyleReader::MatchLength(float* pValue, float defaultLength)
{
    if (mToken == TokenFloat || mToken == TokenInteger)
    {
        *pValue = (float)strtod(mMatchText.c_str(), 0);
        Advance();

        float unit;
        if (MatchSymbol<float, 6>(sUnits, &unit))
            *pValue *= unit;
    }
    else if (MatchSymbol("normal"))
    {
        *pValue = defaultLength;
    }
    else
        return false;

    return true;
}

// @ 0x00896770  EA::Text::TextStyleReader::ParseFontSize
bool TextStyleReader::ParseFontSize(intptr_t pStyle)
{
    float* pValue = (float*)(pStyle + 0x200);

    if (!MatchLength(pValue, 12.0f))
    {
        if (!MatchSymbol<float, 7>(sFontSizes, pValue))
        {
            if (MatchSymbol("larger"))
                *pValue *= 1.15f;
            else if (MatchSymbol("smaller"))
                *pValue *= 0.86956525f;
            else
                return false;
        }
    }

    return true;
}

// The namespace-scope matcher objects from EALexer.h are copy-free empty predicates; the retail
// reader declared its own function-local instances, which is why the image has guard bytes.
static MatchRange<'a','z'>      sLowerCase;
static MatchRange<'A','Z'>      sUpperCase;
static MatchRange<'0','9'>      sDigit;
static MatchChar<'_'>           sUnderscore;
static MatchAnyOf<'-','+'>      sSign;
static MatchAnyOf<'x','X'>      sHexPrefix;

// @ 0x00895810  EA::Text::TextStyleReader::Advance
bool TextStyleReader::Advance()
{
    static MatchRange<'a','z'>      LowerCase;
    static MatchRange<'A','Z'>      UpperCase;
    static MatchChar<'_'>           Underscore;
    static MatchAnyOf<'-','+'>      Sign;
    static MatchAnyOf<'x','X'>      HexPrefix;
    static MatchRange<'0','9'>      Digit;

    mMatchText.clear();

    mTokenPos       = Position();
    mTokenLine      = Line();
    mTokenLineStart = LineStart();

    while (!AtEoF())
    {
        if (SkipWS())
            continue;

        if (Skip("//"))
        {
            SkipToEoL();
            continue;
        }

        if (Skip("/*"))
        {
            SkipUntil("*/");
            continue;
        }

        if (Match(LowerCase | UpperCase | Underscore))
        {
            while (Match(LowerCase | UpperCase | Underscore | Digit | MatchChar<'-'>()))
            {
            }
            mToken = TokenIdent;
            return true;
        }

        if (Match(Sign))
            mToken = TokenError;

        if (Match(Digit))
        {
            mToken = TokenInteger;

            if (*mMatchText.c_str() == '0' && Match(HexPrefix))
            {
                mMatchText.clear();
                while (Match(MatchRange<'a','f'>() | MatchRange<'A','F'>() | Digit))
                {
                }
                if (mMatchText.length() != 0)
                {
                    mToken = TokenHexInteger;
                    return true;
                }
                mToken = TokenError;
                return true;
            }

            MatchWhile(Digit);

            if (Match('.'))
            {
                MatchWhile(Digit);
                mToken = TokenFloat;
            }
            return true;
        }

        if (Skip('"'))
        {
            if (MatchString('"'))
            {
                mToken = TokenString;
                return true;
            }
            reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600003);
            mToken = TokenError;
        }

        if (Skip('\''))
        {
            if (MatchString('\''))
            {
                mToken = TokenString;
                return true;
            }
            reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600003);
            mToken = TokenError;
        }

        char c = Read();
        if (Isprint((char8_t)c))
        {
            switch (c)
            {
                case '#': mToken = TokenPound;      mTokenValue.push_back(c); return true;
                case '%': mToken = TokenPercent;    mTokenValue.push_back(c); return true;
                case '(': mToken = TokenOpenParen;  mTokenValue.push_back(c); return true;
                case ')': mToken = TokenCloseParen; mTokenValue.push_back(c); return true;
                case '+': mToken = TokenPlus;       mTokenValue.push_back(c); return true;
                case ',': mToken = TokenComma;      mTokenValue.push_back(c); return true;
                case ':': mToken = TokenColon;      mTokenValue.push_back(c); return true;
                case ';': mToken = TokenSemicolon;  mTokenValue.push_back(c); return true;
                case '@': mToken = TokenAt;         mTokenValue.push_back(c); return true;
                case '{': mToken = TokenOpenBrace;  mTokenValue.push_back(c); return true;
                case '}': mToken = TokenCloseBrace; mTokenValue.push_back(c); return true;
                default:
                    reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600001);
                    mTokenValue.push_back(c);
                    return true;
            }
        }

        reinterpret_cast<TextStyleReaderReporter*>(this)->EndToken((const void*)0x02600001);
        mToken = TokenError;
        return false;
    }

    mToken = TokenNone;
    return false;
}

}} // namespace EA::Text
