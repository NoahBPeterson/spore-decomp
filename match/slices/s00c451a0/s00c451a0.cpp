// Slice s00c451a0: linear search in a dword vector at +0x1d0/+0x1d4.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct Obj00c451a0 {
    char pad[0x1d0];
    unsigned* mpBegin;  // 0x1d0
    unsigned* mpEnd;    // 0x1d4

    bool Contains(unsigned v);  // 0x00c451a0
};

// @ 0x00c451a0
bool Obj00c451a0::Contains(unsigned v)
{
    int n = mpEnd - mpBegin;
    int i = 0;
    if (n > 0) {
        unsigned* p = mpBegin;
        do {
            if (*p == v)
                return true;
            ++i;
            ++p;
        } while (i < n);
    }
    return false;
}
