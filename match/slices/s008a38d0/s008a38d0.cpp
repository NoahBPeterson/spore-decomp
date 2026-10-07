// EA::Text::Typesetter::GetThaiGlyphs (EAText, EATextShapeThai.cpp).
// Reference: the public EAText source shipped with EAWebKit (EATextShapeThai.cpp); the retail
// build adds a password-mode early-out (see GetGeneralGlyphs in EATextShapeGeneral.cpp).
#include "types.h"

namespace EA { namespace Text {

typedef wchar_t  Char;
typedef uint16_t GlyphId;
typedef unsigned eastl_size_t;

enum PasswordMode { kPMNone, kPMPassword };

struct AnalysisInfo { void* mpTextStyle; void* mpFont; uint32_t mBits; };  // 0xc

enum ThaiCharLayoutFlag
{
    kThaiCharLayoutFlagNone = 0x0000,
    kThaiCharLayoutFlagNC   = 0x0001, // No-tail consonant
    kThaiCharLayoutFlagUC   = 0x0002, // Up-tail consonant
    kThaiCharLayoutFlagBC   = 0x0004, // Bot-tail consonant
    kThaiCharLayoutFlagSC   = 0x0008, // Split-tail consonant
    kThaiCharLayoutFlagAV   = 0x0010, // Above vowel
    kThaiCharLayoutFlagBV   = 0x0020, // Below vowel
    kThaiCharLayoutFlagTN   = 0x0040, // Tone
    kThaiCharLayoutFlagAD   = 0x0080, // Above diacritic
    kThaiCharLayoutFlagBD   = 0x0100, // Below diacritic
    kThaiCharLayoutFlagAM   = 0x0200  // Sara Am
};

const uint16_t tfNC = kThaiCharLayoutFlagNC;
const uint16_t tfUC = kThaiCharLayoutFlagUC;
const uint16_t tfBC = kThaiCharLayoutFlagBC;
const uint16_t tfSC = kThaiCharLayoutFlagSC;
const uint16_t tfAV = kThaiCharLayoutFlagAV;
const uint16_t tfBV = kThaiCharLayoutFlagBV;
const uint16_t tfTN = kThaiCharLayoutFlagTN;
const uint16_t tfAD = kThaiCharLayoutFlagAD;
const uint16_t tfBD = kThaiCharLayoutFlagBD;
const uint16_t tfAM = kThaiCharLayoutFlagAM;

extern const uint16_t gThaiCharLayoutFlagsTable[256];   // 0x01430410
extern const Char     gThaiCharTable[256];              // 0x014307a0

struct ThaiCharAdjustment
{
public:
    uint8_t mStart_TONE_AD;
    uint8_t mStart_AV;
    uint8_t mStart_BV_BD;
    uint8_t mStart_TailCutCons;

    uint8_t mShiftDown_TONE_AD[8];
    uint8_t mShiftDownLeft_TONE_AD[8];
    uint8_t mShiftLeft_TONE_AD[8];
    uint8_t mShiftLeft_AV[7];
    uint8_t mShiftDown_BV_BD[3];
    uint8_t mTailCutCons[4];

    uint8_t mAmComp[2];

public:
    uint8_t shiftdown_tone_ad(eastl_size_t i)     const { return mShiftDown_TONE_AD    [i - mStart_TONE_AD];     }
    uint8_t shiftdownleft_tone_ad(eastl_size_t i) const { return mShiftDownLeft_TONE_AD[i - mStart_TONE_AD];     }
    uint8_t shiftleft_tone_ad(eastl_size_t i)     const { return mShiftLeft_TONE_AD    [i - mStart_TONE_AD];     }
    uint8_t shiftleft_av(eastl_size_t i)          const { return mShiftLeft_AV         [i - mStart_AV];          }
    uint8_t shiftdown_bv_bd(eastl_size_t i)       const { return mShiftDown_BV_BD      [i - mStart_BV_BD];       }
    uint8_t tailcutcons(eastl_size_t i)           const { return mTailCutCons          [i - mStart_TailCutCons]; }
};

extern const ThaiCharAdjustment gThaiCharAdjustment;    // 0x014309a0
extern const ThaiCharAdjustment gLaoCharAdjustment;     // 0x014309cc

inline bool IsCharThai(Char c)
{
    return ((unsigned)c - 0x0E00u) < (0x0E80u - 0x0E00u);
}

inline eastl_size_t GetThaiTableIndex(Char c)
{
    return (c - 0x0E00);
}

inline bool IsThaiCharLayoutFlag(Char c, unsigned flags)
{
    return ((gThaiCharLayoutFlagsTable[c - 0x0E00] & flags) != 0);
}

class Typesetter
{
public:
    eastl_size_t GetGlyphsForChar(const Char* pChar, eastl_size_t count, const AnalysisInfo* pAnalysisInfo,
                                  GlyphId* pGlyphIdArray, eastl_size_t& glyphIdCount,
                                  const Char* pFallbackOptions = 0, eastl_size_t fallbackOptionCount = 0);  // 0x00897790
    eastl_size_t GetThaiGlyphs(eastl_size_t i, const Char* pChar, eastl_size_t clusterSize, GlyphId* pGlyphIdArray);

    uint32_t      pad0[0x360 / 4];
    PasswordMode  mPasswordMode;              // +0x360  mLayoutSettings.mTextStyleDefault.mPasswordMode
    uint32_t      pad364[(0x3cc - 0x364) / 4];
    uint16_t      pad3cc;
    Char          mPasswordChar;              // +0x3ce
    uint32_t      pad3d0[(0x430 - 0x3d0) / 4];
    AnalysisInfo* mAnalysisInfoArray;         // +0x430  mLineLayout.mAnalysisInfoArray.mpBegin
};

///////////////////////////////////////////////////////////////////////////////
// GetThaiGlyphs
//
eastl_size_t Typesetter::GetThaiGlyphs(eastl_size_t i, const Char* pChar, eastl_size_t clusterSize, GlyphId* pGlyphIdArray)
{
    eastl_size_t glyphCount = 0;
    const AnalysisInfo* const pAnalysisInfo = &mAnalysisInfoArray[i];
    const ThaiCharAdjustment* const pTable = IsCharThai(*pChar) ? &gThaiCharAdjustment : &gLaoCharAdjustment;

    if(mPasswordMode == kPMPassword) // If the text is password text...
        GetGlyphsForChar(&mPasswordChar, 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
    else
    {
        switch (clusterSize)
        {
            case 1:
            {
                if(IsThaiCharLayoutFlag(pChar[0], tfAV | tfBV | tfTN | tfAD | tfBD | tfAM))
                {
                    const Char cDottedCircle = 0x25CC;
                    GetGlyphsForChar(&cDottedCircle, 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount, L"\x25CB _o", 4);
                }

                GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);

                break;
            }

            case 2:
            {
                if(IsThaiCharLayoutFlag(pChar[0], tfNC | tfBC | tfSC) &&
                   IsThaiCharLayoutFlag(pChar[1], tfAM))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->mAmComp[0]],          1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->mAmComp[1]],          1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfAM))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                   1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftleft_tone_ad(pTable->mAmComp[0])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->mAmComp[1]],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfNC | tfBC | tfSC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfAV))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfNC | tfBC | tfSC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdown_tone_ad(GetThaiTableIndex(pChar[1]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfAV))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                       1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftleft_av(GetThaiTableIndex(pChar[1]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                                1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdownleft_tone_ad(GetThaiTableIndex(pChar[1]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfNC | tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV | tfBD))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfBC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV | tfBD))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                          1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdown_bv_bd(GetThaiTableIndex(pChar[1]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfSC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV | tfBD))
                {
                    GetGlyphsForChar(&gThaiCharTable[pTable->tailcutcons(GetThaiTableIndex(pChar[0]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])],                      1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else
                {
                    const Char cDottedCircle = 0x25CC;
                    GetGlyphsForChar(&cDottedCircle,                               1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount, L"\x25CB _o", 4);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }

                break;
            }

            case 3:
            {
                if(IsThaiCharLayoutFlag(pChar[0], tfNC | tfBC | tfSC) &&
                   IsThaiCharLayoutFlag(pChar[1], tfTN) &&
                   IsThaiCharLayoutFlag(pChar[2], tfAM))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],  1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->mAmComp[0]],           1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])],  1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->mAmComp[1]],           1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfTN) &&
                        IsThaiCharLayoutFlag(pChar[2], tfAM))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftleft_tone_ad(pTable->mAmComp[0])],          1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftleft_tone_ad(GetThaiTableIndex(pChar[1]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->mAmComp[1]],                                     1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfAV) &&
                        IsThaiCharLayoutFlag(pChar[2], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftleft_av(GetThaiTableIndex(pChar[1]))],      1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftleft_tone_ad(GetThaiTableIndex(pChar[2]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfUC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV) &&
                        IsThaiCharLayoutFlag(pChar[2], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                                1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])],                                1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdownleft_tone_ad(GetThaiTableIndex(pChar[2]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfNC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV) &&
                        IsThaiCharLayoutFlag(pChar[2], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdown_tone_ad(GetThaiTableIndex(pChar[2]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfSC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV) &&
                        IsThaiCharLayoutFlag(pChar[2], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[pTable->tailcutcons(GetThaiTableIndex(pChar[0]))],       1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[1])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdown_tone_ad(GetThaiTableIndex(pChar[2]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else if(IsThaiCharLayoutFlag(pChar[0], tfBC) &&
                        IsThaiCharLayoutFlag(pChar[1], tfBV) &&
                        IsThaiCharLayoutFlag(pChar[2], tfAD | tfTN))
                {
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[0])],                            1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdown_bv_bd(GetThaiTableIndex(pChar[1]))],   1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                    GetGlyphsForChar(&gThaiCharTable[pTable->shiftdown_tone_ad(GetThaiTableIndex(pChar[2]))], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
                else
                {
                    for(eastl_size_t i = 0; i < 3; i++)
                        GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[i])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);
                }
            }
            break;

            case 4:
            default:
            {
                glyphCount = GetThaiGlyphs(i, pChar, 3, pGlyphIdArray);

                for(eastl_size_t i = 3; i < clusterSize; i++)
                    GetGlyphsForChar(&gThaiCharTable[GetThaiTableIndex(pChar[i])], 1, pAnalysisInfo, pGlyphIdArray + glyphCount, glyphCount);

                break;
            }
        }
    }

    return glyphCount;
}

}} // namespace EA::Text
