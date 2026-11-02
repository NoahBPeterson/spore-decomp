// src/game/UTFSpore_Win32/EATextShapeHangul.cpp -- migrated from slice(s) s008a2a00 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextShapeHangul.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/Typesetter.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/Font.h"
#include "EA/Text/GlyphInfo.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/GlyphMetrics.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/TextStyle.h"

// ---- items of slice s008a2a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
typedef unsigned short GlyphId;
}
}
namespace EA {
namespace Text {
typedef wchar_t Char;
}
}
namespace EA {
namespace Text {
enum {
    kCharNBSP    = 0x00A0,
    kCharSpace   = 0x0020,
    kCharLF      = 0x000A,
    kCharCR      = 0x000D,
    kCharNEL     = 0x0085,
    kCharZWSP    = 0x200B,
    kCharLSEP    = 0x2028,
    kCharPSEP    = 0x2029,
    kCharZWNBSP  = 0xFEFF,
    kCharOBJ     = 0xFFFC,
    kPMPassword_s008a_2a00  = 1,
    kCCFlagControlChar = 2,
};
}
}
namespace EA {
namespace Text {
enum HangulClusterType {
    kHangulClusterTypeNone,
    kHangulClusterTypeJamo,
    kHangulClusterTypeTone,
    kHangulClusterTypeUnicode,
};
}
}
namespace EA {
namespace Text {
const unsigned kJamoLFiller = 0x115F;
}
}
namespace EA {
namespace Text {
const unsigned kJamoVFiller = 0x1160;
}
}
namespace EA {
namespace Text {
const unsigned kHangulTone1  = 0x302E;
}
}
namespace EA {
namespace Text {
#define IsTone(c)               (((unsigned)(c) - 0x302Eu) < (0x3030u - 0x302Eu))
}
}
namespace EA {
namespace Text {
#define IsLSyllable(j)          (((unsigned)(j) - 0x1100u) < (0x1113u - 0x1100u))
}
}
namespace EA {
namespace Text {
#define IsVSyllable(j)          (((unsigned)(j) - 0x1161u) < (0x1176u - 0x1161u))
}
}
namespace EA {
namespace Text {
#define IsTSyllable(j)          (((unsigned)(j) - 0x11A8u) < (0x11C3u - 0x11A8u))
}
}
namespace EA {
namespace Text {
#define GetSyllableLVT(l, v, t) (0xAC00 + (((l) - 0x1100) * 21 + ((v) - 0x1161)) * 28 + ((t) - 0x11A7))
}
}
namespace EA {
namespace Text {
#define GetSyllableLV(l, v)     (0xAC00 + (((l) - 0x1100) * 21 + ((v) - 0x1161)) * 28)
}
}
// ---- items of slice s008a2a00 end

// @ 0x008a3480
unsigned int EA::Text::Typesetter::AppendHangulCharCluster(unsigned int iCharBegin, unsigned int charCount, wchar_t const * pCharCluster, unsigned int clusterSize, int clusterType)
{
    const EA::Text::AnalysisInfo* const pAnalysisInfo = &mLineLayout.mAnalysisInfoArray[iCharBegin];
    GlyphId pGlyphIdArray[32];
    unsigned glyphCount = 0;
    unsigned charsEaten = 0;

    if (mLayoutSettings.mTextStyleDefault.mPasswordMode == kPMPassword_s008a_2a00) {
        GetGlyphsForChar(&mPasswordChar, 1, pAnalysisInfo, pGlyphIdArray, glyphCount, 0, 0);
        charsEaten = clusterSize;
    } else {
        switch (clusterType) {
            case kHangulClusterTypeJamo: {
                const Char cTone = pCharCluster[clusterSize - 1];
                const bool bAppendTone = IsTone(cTone);
                unsigned syllableLength;
                Char c;

                if (bAppendTone)
                    --clusterSize;

                if ((clusterSize >= 3) && IsLSyllable(pCharCluster[0]) &&
                    IsVSyllable(pCharCluster[1]) && IsTSyllable(pCharCluster[2]))
                    syllableLength = 3;
                else if ((clusterSize >= 2) && IsLSyllable(pCharCluster[0]) &&
                         IsVSyllable(pCharCluster[1]))
                    syllableLength = 2;
                else
                    syllableLength = 0;

                if (syllableLength) {
                    if (syllableLength == 3)
                        c = GetSyllableLVT(pCharCluster[0], pCharCluster[1], pCharCluster[2]);
                    else
                        c = GetSyllableLV(pCharCluster[0], pCharCluster[1]);

                    GetGlyphsForChar(&c, 1, pAnalysisInfo, pGlyphIdArray + glyphCount,
                                     glyphCount, 0, 0);
                    charsEaten += syllableLength;
                }

                for (unsigned i = charsEaten; i < clusterSize; i += charsEaten) {
                    if ((pCharCluster[i] != kJamoLFiller) && (pCharCluster[i] != kJamoVFiller)) {
                        charsEaten += GetGlyphsForChar(pCharCluster + i, clusterSize - i, pAnalysisInfo,
                                                       pGlyphIdArray + glyphCount, glyphCount, 0, 0);
                    } else {
                        ++charsEaten;
                    }
                }

                if (glyphCount == 0) {
                    const Char cHangulFiller = 0x3164;
                    charsEaten += GetGlyphsForChar(&cHangulFiller, 1, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount,
                                                   L"\x25CB _o", 4);
                }

                if (bAppendTone) {
                    charsEaten += GetGlyphsForChar(&cTone, 1, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount,
                                                   (cTone == kHangulTone1) ? L"\x00b7" : L":", 1);
                }
                break;
            }

            case kHangulClusterTypeTone: {
                const Char cDottedCircle = 0x25CC;

                for (unsigned i = charsEaten; i < clusterSize; i += charsEaten) {
                    charsEaten += GetGlyphsForChar(pCharCluster + i, clusterSize - i, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount,
                                                   (pCharCluster[i] == kHangulTone1) ? L"\x00b7" : L":", 1);
                    GetGlyphsForChar(&cDottedCircle, 1, pAnalysisInfo,
                                     pGlyphIdArray + glyphCount, glyphCount, L"\x25CB _o", 4);
                }
                break;
            }

            case kHangulClusterTypeUnicode: {
                for (unsigned i = charsEaten; i < clusterSize; i += charsEaten) {
                    charsEaten += GetGlyphsForChar(pCharCluster + i, clusterSize - i, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount, 0, 0);
                }
                break;
            }
        }
    }

    AppendGeneralGlyphCluster(iCharBegin, charCount, pCharCluster, charsEaten, pGlyphIdArray, glyphCount, pAnalysisInfo->mnBidiLevel);
    PlaceGeneralGlyphCluster(iCharBegin, charsEaten);
    return glyphCount;
}
