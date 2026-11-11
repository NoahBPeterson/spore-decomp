// Slice s0089cf10 -- EA::Text::Typesetter::ProcessLine(): when the line is not already
// full, reset the pen and the bidi run array, then re-analyse, shape and update the state.
// Local stand-in layout (retail offsets).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

struct RunInfo89cf10 {
    unsigned int mWords[4];             // 16 bytes
};

void copy_705250(const void* first, const void* last, void* dst);   // 0x00705250

struct RunInfoVec89cf10 {
    RunInfo89cf10* mpBegin;             // +0x00
    RunInfo89cf10* mpEnd;               // +0x04
    RunInfo89cf10* mpCapacity;          // +0x08
    void*          mpAllocator;         // +0x0c
    unsigned int   mFlags;              // +0x10

    // The inlined fixed_vector shrink path for resize(0): move the (empty) tail down
    // and pull mpEnd back by the erased element count.
    void resize(int n)
    {
        RunInfo89cf10* first = mpBegin + n;
        RunInfo89cf10* last = mpEnd;
        copy_705250(last, mpEnd, first);
        mpEnd -= (last - first);
    }
};

struct Typesetter89cf10 {
    unsigned char    pad000[0x414];
    int              mLineState;        // +0x414
    unsigned char    pad418[0x4cc - 0x418];
    RunInfoVec89cf10 mBidiRunInfoArray; // +0x4cc
    unsigned char    pad4e0[0x528 - 0x4e0];
    float            mfPenX;            // +0x528
    float            mfPenXMax;         // +0x52c

    int  ProcessLine();
    void UpdateAnalysis();              // 0x0089c750
    void ShapeText();                   // 0x0089b520
    void UpdateLineState();             // 0x00898820
};

// @ 0x0089cf10
int Typesetter89cf10::ProcessLine()
{
    if (mLineState != 1) {
        mfPenX = 0.0f;
        mfPenXMax = 0.0f;
        mBidiRunInfoArray.resize(0);
        UpdateAnalysis();
        ShapeText();
        UpdateLineState();
    }
    return mLineState;
}
