// Slice s00887530: EA::Text::BmpFont::ReadBmpFontInfo (0x00887530, 2639 bytes).
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc (same EAText module as s00885ad0).
//
// Parses the text header of a .bmpFont file line by line ("Key: value"): the font description
// and metrics, the glyph metrics map, the kerning map, the char->glyph map and the texture
// list. Written from the EAWebKit 1.21 EAText source (EATextBmpFont.cpp, vendored read-only in
// work/ext/EAWebKitSupportPackages) with the retail differences seen in the binary:
//   - "Family" goes through GetCharacterAsUTF16 and is terminated explicitly;
//   - Size/Weight/Stretch use an inline strtod, the metrics an out-of-line Atof (0x692700);
//   - the FixedPitch keyword is "Enabled" (fixed when absent, as upstream with "Yes"),
//     the line-through keys are "Strikethrough*";
//   - glyph metrics go to two maps (GlyphMetrics at +0x128, packed texture position at +0x14c);
//   - the texture info is created with the EA operator new (no allocator member assignment).
// The retail BmpFont layout differs from the vendored one, so members are addressed by their
// retail offsets with the vendored value/container types (as in s00885ad0's RT namespace).
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
#include <EAText/EATextFont.h>
#include <EASTL/map.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/fixed_string.h>
#include <EAIO/EAStreamAdapter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

namespace EA { namespace Text {
uint32_t GetCharacterAsUTF16(Char* pDest, uint32_t nDestCapacity, const char8_t* pSrc, uint32_t nSrcLength);  // 0x0093cf60
}}

namespace RT2 {
using namespace EA::Text;

char* Stristr(const char* s1, const char* s2);                // 0x0092cc00
double Atof(const char* p);                                   // 0x00692700

inline double AtofInline(const char* p, char** pEnd) { return strtod(p, pEnd); }


typedef eastl::hash_map<GlyphId, GlyphMetrics, eastl::hash<uint32_t>, eastl::equal_to<GlyphId>,
                        EA::Allocator::EASTLICoreAllocator> GMap;
struct RBmpGM { int mnTextureIndex : 8; int mnPositionX : 12; int mnPositionY : 12; };   // retail: bitfield word only
typedef eastl::hash_map<GlyphId, RBmpGM, eastl::hash<uint32_t>, eastl::equal_to<GlyphId>,
                        EA::Allocator::EASTLICoreAllocator> BMap;
typedef eastl::pair<GlyphId, GlyphId> GPair;
typedef eastl::map<GPair, Kerning, eastl::less<GPair>, EA::Allocator::EASTLICoreAllocator> KMap;
typedef eastl::map<Char, GlyphId, eastl::less<Char>, EA::Allocator::EASTLICoreAllocator> CMap;

// Retail BmpTextureInfo (0x2d0 bytes as allocated here).
struct RPathString16 {
    RPathString16& operator+=(Char c);                        // 0x00887510
};
struct RBmpTexInfo {
    virtual ~RBmpTexInfo();
    virtual int AddRef();                                     // +0x04
    virtual int Release();
    uint32_t pad04[(0x40 - 0x04) / 4];
    float    mfSizeInverse;                                   // +0x40
    uint32_t pad44;
    uint32_t mnSize;                                          // +0x48
    uint8_t  pad4c[0x1a0 - 0x4c];
    RPathString16 mTextureFilePath;                           // +0x1a0
    uint8_t  pad1a1[0x2b8 - 0x1a1];
    uint32_t mnTextureFileSize;                               // +0x2b8
    uint8_t  pad2bc[0x2d0 - 0x2bc];
    RBmpTexInfo();                                            // 0x00886ad0
};

typedef eastl::fixed_vector<RBmpTexInfo*, 4, true> TextureInfoArray;

struct RBmpFont {
    bool ReadBmpFontInfo(EA::IO::IStream* pStream);
};

#define RF(T, off) (*(T*)((char*)this + (off)))
#define mFontDescription RF(FontDescription, 0x48)   // retail offset
#define mFontMetrics     RF(FontMetrics, 0xbc)       // retail offset

// @ 0x00887530
bool RBmpFont::ReadBmpFontInfo(EA::IO::IStream* pStream)
{
    EA::IO::size_type size;
    eastl_size_t      pos;
    const uint32_t    kBufferSize = 512;


    eastl::fixed_string<char8_t, kBufferSize + 1, true> sBuffer8(kBufferSize, 0);

    const EA::IO::size_type streamPositionSaved = (EA::IO::size_type)pStream->GetPosition();

    while((size = EA::IO::ReadLine(pStream, &sBuffer8[0], kBufferSize)) < EA::IO::kSizeTypeDone)
    {
        sBuffer8.resize((eastl_size_t)size);
        pos = sBuffer8.find(':');

        if(pos < sBuffer8.length())
        {
            sBuffer8[pos] = 0;
            pos = sBuffer8.find_first_not_of(" \t", pos + 1);
            const char8_t* pData8 = sBuffer8.c_str() + (pos < sBuffer8.length() ? pos : sBuffer8.length());

            if(_stricmp(sBuffer8.c_str(), "Family") == 0)
            {
                // Strlcpy (retail): bounded 8->16 copy, then terminate.
                GetCharacterAsUTF16(mFontDescription.mFamily, kFamilyNameCapacity, pData8, 0xffffffff);
                mFontDescription.mFamily[kFamilyNameCapacity - 1] = 0;
            }
            else if(_stricmp(sBuffer8.c_str(), "Size") == 0)
            {
                char* pEnd;
                mFontDescription.mfSize = (float)AtofInline(pData8, &pEnd);
            }
            else if(_stricmp(sBuffer8.c_str(), "Style") == 0)
            {
                if(Stristr(pData8, "italic"))
                    mFontDescription.mStyle = kStyleItalic;
                else if(Stristr(pData8, "oblique"))
                    mFontDescription.mStyle = kStyleOblique;
                else
                    mFontDescription.mStyle = kStyleNormal;
            }
            else if(_stricmp(sBuffer8.c_str(), "Weight") == 0)
            {
                char* pEnd;
                mFontDescription.mfWeight = (float)AtofInline(pData8, &pEnd);
            }
            else if(_stricmp(sBuffer8.c_str(), "Stretch") == 0)
            {
                char* pEnd;
                mFontDescription.mfStretch = (float)AtofInline(pData8, &pEnd);
            }
            else if(_stricmp(sBuffer8.c_str(), "Smooth") == 0)
            {
                if(Stristr(pData8, "Yes"))
                    mFontDescription.mSmooth = kSmoothEnabled;
                else
                    mFontDescription.mSmooth = kSmoothNone;
            }
            else if(_stricmp(sBuffer8.c_str(), "Variant") == 0)
            {
                if(Stristr(pData8, "SmallCaps"))
                    mFontDescription.mVariant = kVariantSmallCaps;
                else
                    mFontDescription.mVariant = kVariantNormal;
            }
            else if(_stricmp(sBuffer8.c_str(), "FixedPitch") == 0)
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
            else if(_stricmp(sBuffer8.c_str(), "HAdvanceXMax") == 0)
                mFontMetrics.mfHAdvanceXMax = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "VAdvanceYMax") == 0)
                mFontMetrics.mfVAdvanceYMax = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "Ascent") == 0)
                mFontMetrics.mfAscent = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "Descent") == 0)
                mFontMetrics.mfDescent = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "Leading") == 0)
                mFontMetrics.mfLeading = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "Baseline") == 0)
                mFontMetrics.mfBaseline = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "LineHeight") == 0)
                mFontMetrics.mfLineHeight = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "XHeight") == 0)
                mFontMetrics.mfXHeight = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "CapsHeight") == 0)
                mFontMetrics.mfCapsHeight = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "UnderlinePosition") == 0)
                mFontMetrics.mfUnderlinePosition = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "UnderlineThickness") == 0)
                mFontMetrics.mfUnderlineThickness = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "StrikethroughPosition") == 0)
                mFontMetrics.mfLinethroughPosition = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "StrikethroughThickness") == 0)
                mFontMetrics.mfLinethroughThickness = (float)Atof(pData8);
            else if(_stricmp(sBuffer8.c_str(), "GlyphMetricsMap") == 0)
            {
                bool bShouldReadAnotherLine;

                while(*pData8 != ' ')
                    pData8++;

                do{ // Read each line
                    bShouldReadAnotherLine = false;

                    do{ // Read the entries within each line.
                        unsigned     glyphId;
                        GlyphMetrics gm;
                        int          textureIndex, positionX, positionY;
                        sscanf(pData8, "%u %d %d %d %f %f %f %f %f",
                               &glyphId, &textureIndex, &positionX,
                               &positionY, &gm.mfSizeX, &gm.mfSizeY,
                               &gm.mfHBearingX, &gm.mfHBearingY, &gm.mfHAdvanceX);
                        RBmpGM bgm;
                        bgm.mnTextureIndex = textureIndex;
                        bgm.mnPositionX    = positionX;
                        bgm.mnPositionY    = positionY;
                        RF(GMap, 0x128).insert(GMap::value_type((GlyphId)glyphId, gm));
                        RF(BMap, 0x14c).insert(BMap::value_type((GlyphId)glyphId, bgm));

                        pData8 = strchr(pData8, ',');
                    } while(pData8++ && (pData8 < (sBuffer8.data() + sBuffer8.length())));

                    if(sBuffer8[(eastl_size_t)size - 1] == ',')
                    {
                        bShouldReadAnotherLine = true;

                        sBuffer8.resize(kBufferSize);
                        size = EA::IO::ReadLine(pStream, &sBuffer8[0], kBufferSize);
                        sBuffer8.resize((eastl_size_t)size);
                        pData8 = sBuffer8.c_str();
                    }
                } while(bShouldReadAnotherLine);
            }
            else if(_stricmp(sBuffer8.c_str(), "KerningMap") == 0)
            {
                bool bShouldReadAnotherLine;

                while(*pData8 != ' ')
                    pData8++;

                do{ // Read each line
                    bShouldReadAnotherLine = false;

                    do{ // Read the entries within each line.
                        unsigned glyphId1, glyphId2;
                        Kerning  kerning;

                        sscanf(pData8, "%u %u %f", &glyphId1, &glyphId2, &kerning.mfKernX);
                        RF(KMap, 0x170).insert(KMap::value_type(GPair((GlyphId)glyphId1, (GlyphId)glyphId2), kerning));

                        pData8 = strchr(pData8, ',');
                    } while(pData8++ && (pData8 < (sBuffer8.data() + sBuffer8.length())));

                    if(sBuffer8[(eastl_size_t)size - 1] == ',')
                    {
                        bShouldReadAnotherLine = true;

                        sBuffer8.resize(kBufferSize);
                        size = EA::IO::ReadLine(pStream, &sBuffer8[0], kBufferSize);
                        sBuffer8.resize((eastl_size_t)size);
                        pData8 = sBuffer8.c_str();
                    }
                } while(bShouldReadAnotherLine);
            }
            else if(_stricmp(sBuffer8.c_str(), "CharMapSet") == 0)
            {
                bool bShouldReadAnotherLine;

                while(*pData8 != ' ')
                    pData8++;

                do{ // Read each line
                    bShouldReadAnotherLine = false;

                    do{ // Read the entries within each line.
                        unsigned character;
                        unsigned glyphId;

                        sscanf(pData8, "%u %u", &character, &glyphId);
                        RF(CMap, 0x1b8).insert(CMap::value_type((Char)character, (GlyphId)glyphId));

                        pData8 = strchr(pData8, ',');
                    } while(pData8++ && (pData8 < (sBuffer8.data() + sBuffer8.length())));

                    if(sBuffer8[(eastl_size_t)size - 1] == ',')
                    {
                        bShouldReadAnotherLine = true;

                        sBuffer8.resize(kBufferSize);
                        size = EA::IO::ReadLine(pStream, &sBuffer8[0], kBufferSize);
                        sBuffer8.resize((eastl_size_t)size);
                        pData8 = sBuffer8.c_str();
                    }
                } while(bShouldReadAnotherLine);
            }
            else if(Stristr(sBuffer8.c_str(), "Texture") == sBuffer8.c_str())
            {
                // "Texture0: 19387 256 256 EATextDemo 0.png"; pData8 points past the ':'.
                RBmpTexInfo* const pBmpTextureInfo = new("EAText/BmpTextureInfo", 0, 0, 0, 0) RBmpTexInfo;
                pBmpTextureInfo->AddRef(); // AddRef for the mTextureInfoArray container.

                sscanf(pData8, "%u %u %u", (unsigned*)&pBmpTextureInfo->mnTextureFileSize,
                                            (unsigned*)&pBmpTextureInfo->mnSize,
                                            (unsigned*)&pBmpTextureInfo->mnSize);

                pBmpTextureInfo->mfSizeInverse = 1.f / pBmpTextureInfo->mnSize;

                const char8_t* pTextureFileName = strchr(pData8, ' ');
                pTextureFileName = strchr(++pTextureFileName, ' ');
                pTextureFileName = strchr(++pTextureFileName, ' ');

                while(*++pTextureFileName)
                    pBmpTextureInfo->mTextureFilePath += (uint8_t)*pTextureFileName;

                RF(TextureInfoArray, 0x190).push_back(pBmpTextureInfo);
            }
        }

        sBuffer8.resize(kBufferSize);
    }

    pStream->SetPosition((EA::IO::off_type)streamPositionSaved);

    return true;
}

}  // namespace RT2
