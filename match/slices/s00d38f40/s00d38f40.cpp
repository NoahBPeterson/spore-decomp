// @ 0x00d38f40 — re-orders the entries of the global list that share a sort key.
// The list at 0x01583298 is (begin, end) of 8-byte entries whose key sits at +0x04 and is
// compared as a dword. The function walks the list once; for each maximal run [i..j] of
// equal keys it walks i from the run start while i < j and swaps entry i with the run's
// last entry j whenever a fresh random double is not below the previous draw, so the ties
// come out in a random order.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The list is touched through the global object itself, never through a cached `begin`
// local: retail keeps the base in edx for the scan, but reloads it from 0x01583298 three
// times inside the swap (the stores may alias the global), which only a direct access
// produces. The draw comparison is x87 `fld r; fxch st(1); fcompi st(1); fstp st(0); jb`
// (no NaN test), the shape /arch:SSE /fp:fast gives a double-versus-float `>=`.
#include "types.h"

struct RandomLinearCongruential {
    double RandomDoubleUniform();                        // 0x009360d0
};
extern RandomLinearCongruential g_random;                // 0x01601760

struct KeyedEntry {
    int mValue;                                          // +0x00
    int mKey;                                            // +0x04
};

struct KeyedEntryList {
    KeyedEntry* mBegin;                                  // +0x00
    KeyedEntry* mEnd;                                    // +0x04
};
extern KeyedEntryList g_keyedEntries;                    // 0x01583298

void ShuffleEqualKeyRuns()
{
    int i = 0;
    int j = 0;
    int count = (int)(g_keyedEntries.mEnd - g_keyedEntries.mBegin);

    while (j < count) {
        while (j < count && g_keyedEntries.mBegin[i].mKey == g_keyedEntries.mBegin[j].mKey)
            j++;
        j--;
        if (i < j) {
            while (i < j) {
                float r = (float)g_random.RandomDoubleUniform();
                if (g_random.RandomDoubleUniform() >= r) {
                    KeyedEntry t = g_keyedEntries.mBegin[i];
                    g_keyedEntries.mBegin[i] = g_keyedEntries.mBegin[j];
                    g_keyedEntries.mBegin[j] = t;
                }
                i++;
            }
        }
        i++;
        j++;
    }
}
