// Slice s008934e0 - EA::Text::PolygonFont::Open (retail EAText).
//
// Built on the vendored EAWebKit EAText headers (same setup as slice s00885ad0). The function body
// is the upstream EATextPolygonFont.cpp implementation, adjusted to the retail (Spore) EAText
// version, which differs from the EAWebKit drop in these ways (all visible in the binary):
//   - Stricmp is an inline wrapper over the CRT _stricmp (dllimport), not an out-of-line function;
//   - Atof is an inline `strtod(p, &end)` (an end-pointer local), so cl inlines its first uses
//     and calls an out-of-line copy (0x00692700) once its inline budget is spent;
//   - "Family" also writes the terminator mFamily[kFamilyNameCapacity - 1] = 0;
//   - ReadFromBigEndianFloat byte-swaps a dword and converts it as an unsigned integer value
//     (fild + 2^32 fixup), and ReadFromBigEndianUint16 swaps a loaded word;
//   - GetGlyphIds takes five arguments (no bWriteInvalidGlyphs);
//   - the UTF-8 -> UTF-16 Strlcpy (0x0093CF60) takes (dest, capacity, source, length);
//   - mReplacementGlyphId is at +0x14 (the extra Font fields are split around it).
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc

#include "types.h"

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#include <EABase/EABase.h>
#include <EAText/EAText.h>
#include <EAText/EATextStyle.h>
#include <EASTL/utility.h>
#include <EASTL/hash_map.h>
#include <EASTL/core_allocator_adapter.h>
#include <coreallocator/icoreallocator_interface.h>
#include <EAIO/EAStream.h>
// Retail Font base is 0x28 bytes larger than the EAWebKit one (see s00885ad0). One of the extra
// dwords sits before mReplacementGlyphId (retail +0x14, read by Open), the rest after mRefCount.
#define mpStream mpStream; unsigned mRetailFontExtra0
#define mRefCount mRefCount; unsigned mRetailFontExtra[9]
#include <EAText/EATextFont.h>
#undef mRefCount
#undef mpStream
#include <EAText/EATextPolygonFont.h>
#include <EASTL/fixed_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace EA
{
namespace Text
{

// Retail EAText StdC helpers (only the ones Open uses).
namespace RetailStdC
{
    inline int Stricmp(const char8_t* pString1, const char8_t* pString2)
    {
        return _stricmp(pString1, pString2);
    }

    inline double Atof(const char8_t* pString)
    {
        char8_t* pEnd;
        return strtod(pString, &pEnd);
    }

    EA_FORCE_INLINE uint32_t AtoU32(const char8_t* pString)
    {
        return (uint32_t)strtoul(pString, NULL, 10);
    }

    inline const char8_t* Strchr(const char8_t* pString, int c)
    {
        return strchr(pString, c);
    }

    char8_t* Stristr(const char8_t* pString, const char8_t* pSubString);                    // 0x0092CC00
    // Retail parameter order: destination, capacity, source, source length.
    int Strlcpy(char16_t* pDestination, size_t nDestCapacity, const char8_t* pSource,
                size_t nSourceLength = (size_t)~0);                                         // 0x0093CF60
}

namespace PolygonFontInternal
{
    EA_FORCE_INLINE uint16_t ReadFromBigEndianUint16(const void* pData)
    {
        return _byteswap_ushort(*(const uint16_t*)pData);
    }

    EA_FORCE_INLINE uint32_t ReadFromBigEndianUint32(const void* pData)
    {
        return _byteswap_ulong(*(const uint32_t*)pData);
    }

    // Retail: reads a big-endian dword, converts it as an unsigned value, and advances the cursor.
    EA_FORCE_INLINE float ReadFromBigEndianFloat(const float*& pData)
    {
        return (float)_byteswap_ulong(*(const uint32_t*)pData++);
    }
}

// FontFileLineReader (EATextPolygonFont.cpp)
struct FontFileLineReader
{
    static const uint32_t kBufferSize = 4095;
    eastl::fixed_string<char8_t,  kBufferSize + 1, true> mBuffer8;

    EA::IO::size_type ReadLine(EA::IO::IStream* pIS);   // 0x00892870
};

// Retail Font vtable slot +0x38: GetGlyphIds with five parameters.
struct RetailFontGlyphIds
{
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03(); virtual void f04();
    virtual void f05(); virtual void f06(); virtual void f07(); virtual void f08(); virtual void f09();
    virtual void f10(); virtual void f11(); virtual void f12(); virtual void f13();
    virtual uint32_t GetGlyphIds(const Char* pCharArray, uint32_t nCharArrayCount, GlyphId* pGlyphIdArray,
                                 bool bUseReplacementGlyph, const uint32_t nGlyphIdStride);   // +0x38
};


// @ 0x008934E0
bool PolygonFont::Open(IO::IStream* pStream)
{
    using namespace EA::Text::PolygonFontInternal;
    using namespace EA::Text::RetailStdC;

    bool                bResult = false;
    IO::size_type       size;
    eastl_size_t        pos;
    const IO::size_type posSaved = (IO::size_type)pStream->GetPosition();
    FontFileLineReader  reader;

    // Long lines wrap to the next line, so we shouldn't run out of space during the read.
    while((size = reader.ReadLine(pStream)) < EA::IO::kSizeTypeDone)
    {
        pos = reader.mBuffer8.find(':');

        if(pos < reader.mBuffer8.length())
        {
            // Move past any whitespace after the ':' char.
            reader.mBuffer8[pos] = 0;
            pos = reader.mBuffer8.find_first_not_of(" \t", pos + 1);
            const char8_t* pData8 = reader.mBuffer8.c_str() + (pos < reader.mBuffer8.length() ? pos : reader.mBuffer8.length());

            if(Stricmp(reader.mBuffer8.c_str(), "Family") == 0)
            {
                Strlcpy(mFontDescription.mFamily, kFamilyNameCapacity, pData8);
                mFontDescription.mFamily[kFamilyNameCapacity - 1] = 0;
            }
            else if(Stricmp(reader.mBuffer8.c_str(), "Size") == 0)
                mFontDescription.mfSize = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Style") == 0)
            {
                if(Stristr(pData8, "italic"))
                    mFontDescription.mStyle = kStyleItalic;
                else if(Stristr(pData8, "oblique"))
                    mFontDescription.mStyle = kStyleOblique;
                else
                    mFontDescription.mStyle = kStyleNormal;
            }
            else if(Stricmp(reader.mBuffer8.c_str(), "Weight") == 0)
                mFontDescription.mfWeight = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Stretch") == 0)
                mFontDescription.mfStretch = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Smooth") == 0)
            {
                if(Stristr(pData8, "Yes"))
                    mFontDescription.mSmooth = kSmoothEnabled;
                else
                    mFontDescription.mSmooth = kSmoothNone;
            }
            else if(Stricmp(reader.mBuffer8.c_str(), "Variant") == 0)
            {
                if(Stristr(pData8, "SmallCaps"))
                    mFontDescription.mVariant = kVariantSmallCaps;
                else
                    mFontDescription.mVariant = kVariantNormal;
            }
            else if(Stricmp(reader.mBuffer8.c_str(), "FixedPitch") == 0)
            {
                if(Stristr(pData8, "Enabled") == 0)
                {
                    mFontMetrics.mPitch     = kPitchFixed;
                    mFontDescription.mPitch = kPitchFixed;
                }
                else
                {
                    mFontMetrics.mPitch     = kPitchVariable;
                    mFontDescription.mPitch = kPitchVariable;
                }
            }
            else if(Stricmp(reader.mBuffer8.c_str(), "HAdvanceXMax") == 0)
                mFontMetrics.mfHAdvanceXMax = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "VAdvanceYMax") == 0)
                mFontMetrics.mfVAdvanceYMax = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Ascent") == 0)
                mFontMetrics.mfAscent = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Descent") == 0)
                mFontMetrics.mfDescent = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Leading") == 0)
                mFontMetrics.mfLeading = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "Baseline") == 0)
                mFontMetrics.mfBaseline = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "LineHeight") == 0)
                mFontMetrics.mfLineHeight = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "XHeight") == 0)
                mFontMetrics.mfXHeight = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "CapsHeight") == 0)
                mFontMetrics.mfCapsHeight = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "UnderlinePosition") == 0)
                mFontMetrics.mfUnderlinePosition = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "UnderlineThickness") == 0)
                mFontMetrics.mfUnderlineThickness = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "StrikethroughPosition") == 0)
                mFontMetrics.mfLinethroughPosition = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "StrikethroughThickness") == 0)
                mFontMetrics.mfLinethroughThickness = (float)Atof(pData8);
            else if(Stricmp(reader.mBuffer8.c_str(), "GlyphMetricsMap") == 0)
            {
                bool    bShouldReadAnotherLine;

                while(*pData8 != ' ') // Skip past the entry count digits.
                    pData8++;

                do{ // Read each line
                    bShouldReadAnotherLine = false;

                    do{ // Read the entries within each line.
                        unsigned        glyphId;
                        GlyphMetrics    gm;
                        const int       nFieldCount = sscanf(pData8, "%u %f %f %f %f %f",
                                                                &glyphId, &gm.mfSizeX, &gm.mfSizeY,
                                                                &gm.mfHBearingX, &gm.mfHBearingY, &gm.mfHAdvanceX);
                        (void)nFieldCount;
                        mGlyphMetricsMap.insert(GlyphMetricsMap::value_type((GlyphId)glyphId, gm));

                        pData8 = Strchr(pData8, ',');
                    } while(pData8++ && (pData8 < (reader.mBuffer8.data() + reader.mBuffer8.length())));

                    // To read multi-line glyph metric map.
                    if(reader.mBuffer8[(eastl_size_t)size - 1] == ',')
                    {
                        bShouldReadAnotherLine = true;

                        size = reader.ReadLine(pStream);
                        pData8 = reader.mBuffer8.c_str();
                    }
                } while(bShouldReadAnotherLine);
            }
            else if(Stricmp(reader.mBuffer8.c_str(), "CharMapSet") == 0)
            {
                bool bShouldReadAnotherLine;

                while(*pData8 != ' ') // Skip past the entry count digits.
                    pData8++;

                do{ // Read each line
                    bShouldReadAnotherLine = false;

                    do{ // Read the entries within each line.
                        unsigned character;
                        unsigned glyphId;

                        const int nFieldCount = sscanf(pData8, "%u %u", &character, &glyphId);
                        (void)nFieldCount;
                        mCharGlyphMap.insert(CharGlyphMap::value_type((Char)character, (GlyphId)glyphId));

                        pData8 = Strchr(pData8, ',');
                    } while(pData8++ && (pData8 < (reader.mBuffer8.data() + reader.mBuffer8.length())));

                    // To read multi-line glyph metric map.
                    if(reader.mBuffer8[(eastl_size_t)size - 1] == ',')
                    {
                        bShouldReadAnotherLine = true;

                        size = reader.ReadLine(pStream);
                        pData8 = reader.mBuffer8.c_str();
                    }
                } while(bShouldReadAnotherLine);
            }
            else if(Stristr(reader.mBuffer8.c_str(), "Glyph") == reader.mBuffer8.c_str())
            {
                if(!mbUserGlyphInfo)
                {
                    Allocator::ICoreAllocator* const pAllocator = mPolygonGlyphMap.get_allocator().get_allocator();

                    const uint32_t glyphId = AtoU32(reader.mBuffer8.c_str() + 5); // "Glyph37: # # # #, array array"

                    unsigned vertexArraySize;
                    unsigned indexArraySize;
                    unsigned backFaceVertexStart;
                    unsigned backFaceIndexStart;

                    const int nFieldCount = sscanf(pData8, "%u %u %u %u", &vertexArraySize, &indexArraySize, &backFaceVertexStart, &backFaceIndexStart);
                    (void)nFieldCount;

                    // Set up the PolygonGlyph
                    PolygonGlyphPtr& glyphPtr = mPolygonGlyphMap[(uint16_t)glyphId];
                    glyphPtr.mpPolygonGlyph = (PolygonGlyph*)pAllocator->Alloc(sizeof(PolygonGlyph), "PolygonGlyph", 0);

                    if(glyphPtr.mpPolygonGlyph)
                    {
                        // Use placement new to construct the PolygonGlyph.
                        glyphPtr.mpPolygonGlyph = new(glyphPtr.mpPolygonGlyph) PolygonGlyph;

                        if(vertexArraySize) // Some glyphs have no geometry (e.g. the space char)
                        {
                            PolygonGlyph& glyph = *glyphPtr.mpPolygonGlyph;

                            glyph.mVertexArray.resize(vertexArraySize);
                            glyph.mIndexArray.resize(indexArraySize);

                            // Skip past the above-read values.
                            pData8 = strchr(pData8, ',') + 1;

                            // Copy the vertex data.
                            const float* pVertexData = (const float*)pData8;

                            for(uint32_t v = 0; v < vertexArraySize; v++)
                            {
                                glyph.mVertexArray[v].mX  = ReadFromBigEndianFloat(pVertexData);
                                glyph.mVertexArray[v].mY  = ReadFromBigEndianFloat(pVertexData);
                                glyph.mVertexArray[v].mZ  = ReadFromBigEndianFloat(pVertexData);
                                glyph.mVertexArray[v].mNX = ReadFromBigEndianFloat(pVertexData);
                                glyph.mVertexArray[v].mNY = ReadFromBigEndianFloat(pVertexData);
                                glyph.mVertexArray[v].mNZ = ReadFromBigEndianFloat(pVertexData);
                            }

                            // Copy the index data.
                            const uint16_t* const pIndexData = (const uint16_t*)(const char*)pVertexData;

                            for(eastl_size_t i = 0; i < indexArraySize; i++)
                                glyph.mIndexArray[i] = ReadFromBigEndianUint16(pIndexData + i);
                        }
                    }
                }
            }
        }
    }

    bResult = (!mCharGlyphMap.empty() && !mGlyphMetricsMap.empty());

    if(bResult)
    {
        // Set up mSupportedScriptSet.
        SetupSupportedScriptSet();

        // Set up mReplacementGlyphId.
        mReplacementGlyphId = mGlyphMetricsMap.begin()->first;
        Char c = '_';
        ((RetailFontGlyphIds*)this)->GetGlyphIds(&c, 1, &mReplacementGlyphId, false, sizeof(GlyphId));

        // Add a kGlyphIdZeroWidth glyph.
        GlyphMetrics gmZeroWidth;
        memset(&gmZeroWidth, 0, sizeof(gmZeroWidth));
        mGlyphMetricsMap.insert(GlyphMetricsMap::value_type(kGlyphIdZeroWidth, gmZeroWidth));
    }

    // Restore the original stream position.
    pStream->SetPosition((EA::IO::off_type)posSaved);

    return bResult;
}

} // namespace Text
} // namespace EA
