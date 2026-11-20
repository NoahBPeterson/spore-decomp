// Slice s008980d0: walks a flag-array forward while the 0x10 bit is set, then
// counts the run of entries sharing the first one's word pointer.
// Two out-pointers (ret 8): both get the run start, the second counts the run.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Entry_008980d0 {
    unsigned char mFlags;                       // +0x00 (bit 0x10 = visited)
    char          pad_01[7];                    // +0x01 .. +0x07
};

struct Data_008980d0 {
    char  pad_000[0x004];                       // +0x000
    short* mpFirst;                             // +0x004
    short* mpLast;                              // +0x008
    char  pad_00c[0x018 - 0x00c];               // +0x00c .. +0x017
    int** mppWords;                             // +0x018 (array of 3 ints)
    char  pad_01c[0x040 - 0x01c];               // +0x01c .. +0x03f
    Entry_008980d0* mpEntries;                  // +0x040
    Entry_008980d0* mpEntriesEnd;               // +0x044
    char  pad_048[0x07c - 0x048];               // +0x048 .. +0x07b
    int*  mpIds;                                // +0x07c
    int*  mpIdsEnd;                             // +0x080

    int* KeyAt(unsigned int i)
    {
        int idx;
        int* const* ids = &mpIds;   // {begin, end}: the size reads end first, the element re-reads begin
        if (i < (unsigned int)(ids[1] - ids[0]))
            idx = mpIds[i];
        else
            idx = (int)(mpLast - mpFirst);
        return mppWords[idx * 3];
    }
};

struct Holder_008980d0 {
    Data_008980d0* mpData;                      // +0x000
    unsigned int   mIndex;                      // +0x004

    bool NextFlagsRun(unsigned int* pStart, unsigned int* pEnd);
};

// @ 0x008980d0
bool Holder_008980d0::NextFlagsRun(unsigned int* pStart, unsigned int* pEnd)
{
    Data_008980d0* d = mpData;
    unsigned int i = mIndex;
    unsigned int n = (unsigned int)(d->mpEntriesEnd - d->mpEntries);
    while (i < n) {
        if ((mpData->mpEntries[i].mFlags & 0x10) == 0)
            break;
        ++i;
    }
    *pStart = i;
    *pEnd = i;
    if (i < n) {
        unsigned int s = *pStart;
        int* key = mpData->KeyAt(s);
        do {
            int* other = mpData->KeyAt(i);
            if (other != key)
                break;
            if ((mpData->mpEntries[i].mFlags & 0x10) != 0)
                break;
            ++*pEnd;
            ++i;
        } while (i < n);
        mIndex = i;
        return true;
    }
    mIndex = n;
    return false;
}
