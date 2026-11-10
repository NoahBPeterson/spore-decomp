// Slice s008980d0: walks a flag-array forward while the 0x10 bit is set, then
// counts the run of entries sharing the first one's word pointer.
// Status: not byte-exact (189 vs 200 bytes).  The original expands the "key at i"
// expression twice -- each expansion re-reads mpData, mpIdsEnd/mpIds and the +0x18
// word array -- and keeps the loop value in eax, the first key in ebx and the count
// pointer in esi.  cl 15 CSEs the second expansion into a jmp to the first and
// spills the third argument.  See nonmatching.txt.
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
};

struct Holder_008980d0 {
    Data_008980d0* mpData;                      // +0x000
    unsigned int   mIndex;                      // +0x004

    bool NextFlagsRun(unsigned int* pOut, unsigned int* pKeyIndex, unsigned int* pStart);
};

// @ 0x008980d0
bool Holder_008980d0::NextFlagsRun(unsigned int* pOut, unsigned int* pKeyIndex, unsigned int* pStart)
{
    unsigned int n = (unsigned int)(mpData->mpEntriesEnd - mpData->mpEntries);
    unsigned int i = mIndex;
    while (i < n) {
        if ((mpData->mpEntries[i].mFlags & 0x10) == 0)
            break;
        ++i;
    }
    *pOut = i;
    *pStart = i;
    if (i >= n) {
        mIndex = n;
        return false;
    }
    unsigned int idsN = (unsigned int)(mpData->mpIdsEnd - mpData->mpIds);
    int* key = mpData->mppWords[(i < idsN ? mpData->mpIds[i] : (int)(mpData->mpLast - mpData->mpFirst)) * 3];
    while (i < n) {
        unsigned int idsM = (unsigned int)(mpData->mpIdsEnd - mpData->mpIds);
        int* other = mpData->mppWords[(i < idsM ? mpData->mpIds[i] : (int)(mpData->mpLast - mpData->mpFirst)) * 3];
        if (other != key)
            break;
        if ((mpData->mpEntries[i].mFlags & 0x10) == 0)
            break;
        ++*pKeyIndex;
        ++i;
    }
    mIndex = i;
    return true;
}