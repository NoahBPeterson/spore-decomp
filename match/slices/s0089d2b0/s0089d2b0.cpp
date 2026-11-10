// @ 0x0089d2b0
// eastl::fixed_vector<RunInfo,4,true>::operator= (EAText Typesetter run list): clear the
// destination, then insert the source's runs.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"

struct RunInfo { uint32_t mScript; int mnBidiLevel; uint32_t mnCharBegin; uint32_t mnCharEnd; };

// eastl::fixed_vector<RunInfo,4,true>, retail layout
struct RunVec {
    RunInfo* mpBegin;       // +0x00
    RunInfo* mpEnd;         // +0x04
    RunInfo* mpCapacity;    // +0x08
    uint32_t pad0;          // +0x0c
    RunInfo* mpPoolBegin;   // +0x10
    uint32_t pad1;          // +0x14
    RunInfo mBuffer[4];     // +0x18

    RunVec& operator=(const RunVec& o);                       // 0x0089d2b0
    void DestructRange(RunInfo* first, RunInfo* last);        // 0x00705250
    void DoInsert(RunInfo* pos, RunInfo* first, RunInfo* last);   // 0x0089ae20
};

// @ 0x0089d2b0
RunVec& RunVec::operator=(const RunVec& o)
{
    if (&o != this) {
        DestructRange(mpBegin, mpEnd);
        mpEnd -= mpEnd - mpBegin;
        DoInsert(mpBegin, o.mpBegin, o.mpEnd);
    }
    return *this;
}
