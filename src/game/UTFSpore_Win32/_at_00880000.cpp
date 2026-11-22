// UTFSpore_Win32/_at_00880000.obj: the EAText word-break helpers (slice s00887530).
// The slice's other two functions (0x00887530 RBmpFont::ReadBmpFontInfo, 0x00887f80 RBmpFont::Open)
// belong to UTFSpore_Win32/EATextBmpFont.obj and stay in the slice.
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
// The vendored EATextBreak.h declares ParagraphBreakIterator without the retail
// GetNextParagraphBreak member. Rename that declaration aside so the retail-layout
// class below can provide the method (and its exact retail symbol).
#define ParagraphBreakIterator EATextVendorParagraphBreakIterator
#include <EAText/EATextBreak.h>
#undef ParagraphBreakIterator
#include <EAText/EATextStyle.h>
#include <coreallocator/icoreallocator_interface.h>

namespace RT2
{
    using namespace EA::Text;

    void __fastcall IncrementTextRunIterator(EA::Text::TextRunIterator* pIterator);              // 0x00888160
    EA::Text::Char __fastcall DerefTextRunIterator(const EA::Text::TextRunIterator* pIterator);  // 0x008880c0

    // The retail word-break dictionary keeps its additions in an EASTL hash map; the second
    // container is the vector of entries that is keyed by the string hash. Only the allocator
    // fields are touched by InitWordBreakDictionary.
    struct RWordBreakDictionary
    {
        void*                         mpBucketArray;   // +0x00
        uint32_t                      mnBucketCount;   // +0x04
        uint32_t                      mnElementCount;  // +0x08
        float                         mfLoadFactor;    // +0x0c
        float                         mfGrowthFactor;  // +0x10
        uint32_t                      mnReserved14;    // +0x14
        EA::Allocator::ICoreAllocator* mpAllocator;    // +0x18
        uint32_t                      mnReserved1c;    // +0x1c
    };
    RWordBreakDictionary gWordBreakDictionary;             // 0x016519ac

    struct RWordBreakEntryArray
    {
        uint32_t                      mnBegin;          // +0x00
        uint32_t                      mnEnd;            // +0x04
        uint32_t                      mnCapacity;       // +0x08
        EA::Allocator::ICoreAllocator* mpAllocator;      // +0x0c
        uint32_t                      mnReserved10;     // +0x10
    };
    RWordBreakEntryArray gWordBreakDictionaryEntries;       // 0x01651994

// @ 0x008881e0
    uint32_t HashWordBreakString(const Char* pString, uint32_t nLength, uint32_t nHash)
    {
        const Char* const pEnd = pString + nLength;

        while((pString < pEnd) && *pString)
        {
            nHash = nHash * 33 + *pString;
            ++pString;
        }

        return nHash;
    }
}  // namespace RT2

namespace EA
{
    namespace Text
    {
        class ParagraphBreakIterator : public CharacterBreakIterator
        {
        public:
            ParagraphBreakIterator() { }

            ParagraphBreakIterator(const TextRun* pTextRunArray, uint32_t nTextRunArraySize,
                                   const LayoutContext* pLayoutContext = NULL)
                : CharacterBreakIterator(pTextRunArray, nTextRunArraySize, pLayoutContext) { }

            ParagraphBreakIterator(const TextRunIterator& tri, const LayoutContext* pLayoutContext = NULL)
                : CharacterBreakIterator(tri, pLayoutContext) { }

            uint32_t GetNextParagraphBreak();
        };

// @ 0x008883a0
        uint32_t ParagraphBreakIterator::GetNextParagraphBreak()
        {
            if(!mIterator.AtEnd())
            {
                Char cCurrent = *mIterator;

                RT2::IncrementTextRunIterator(&mIterator);
                Char cNext = *mIterator;

                while(!mIterator.AtEnd())
                {
                    if(cCurrent == kCharCR)
                    {
                        if(cNext != kCharLF)
                            break;
                    }
                    else if(cCurrent == kCharPSEP)
                        break;

                    cCurrent = cNext;
                    RT2::IncrementTextRunIterator(&mIterator);
                    cNext = RT2::DerefTextRunIterator(&mIterator);
                }
            }

            return mIterator.GetPosition();
        }

// @ 0x00888480
        void InitWordBreakDictionary()
        {
            if(RT2::gWordBreakDictionary.mnElementCount == 0)
                RT2::gWordBreakDictionary.mpAllocator = GetAllocator();

            if(RT2::gWordBreakDictionaryEntries.mnBegin == RT2::gWordBreakDictionaryEntries.mnEnd)
                RT2::gWordBreakDictionaryEntries.mpAllocator = GetAllocator();
        }
    }  // namespace Text
}  // namespace EA
