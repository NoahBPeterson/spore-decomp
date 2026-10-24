// Slice s0088f1b0: EA::Text::TextRunIterator pre-decrement as linked into SporeApp.exe.
#include "types.h"

namespace EA { namespace Text {

struct TextRun {
    wchar_t* mpText;          // +0x00
    unsigned int mnTextSize;  // +0x04
};

class TextRunIterator {
public:
    TextRun* mpArray;             // +0x00
    TextRun* mpArrayEnd;          // +0x04
    TextRun* mpArrayCurrent;      // +0x08
    wchar_t* mpCharCurrent;       // +0x0c
    unsigned int mnStartPosition; // +0x10
    unsigned int mnEndPosition;   // +0x14
    unsigned int mnPosition;      // +0x18

    TextRunIterator& Decrement();
};

}}

// @ 0x0088f420
EA::Text::TextRunIterator& EA::Text::TextRunIterator::Decrement()
{
    if (mnPosition > mnStartPosition)
    {
        --mpCharCurrent;
        if (mpCharCurrent < mpArrayCurrent->mpText)
        {
            --mpArrayCurrent;
            while (mpArrayCurrent >= mpArray && mpArrayCurrent->mnTextSize == 0)
                --mpArrayCurrent;
            if (mpArrayCurrent >= mpArray)
            {
                mpCharCurrent = mpArrayCurrent->mpText + (mpArrayCurrent->mnTextSize - 1);
            }
            else
            {
                mpArrayCurrent = mpArray;
                mpCharCurrent = mpArray->mpText - 1;
                mnPosition = 0;
                return *this;
            }
        }
        --mnPosition;
    }
    return *this;
}
