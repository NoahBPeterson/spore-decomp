// slice s00c451a0 -- SPGameNounManager.obj: membership test over a vector of ints.
// FUN_00c451a0 (0x00c451a0, 56 bytes): thiscall, `ret 4`.  The vector's begin/end pointers sit
//   at +0x1d0/+0x1d4; the count is (end - begin) and the scan walks a pointer IV with a
//   separate index counter, returning true on the first equal element.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"
#include <intrin.h>

// Owning class not identified yet; only the two vector pointers are touched here.
struct Obj00c451a0 {
    char pad[0x1d0];
    int* mBegin;   // +0x1d0
    int* mEnd;     // +0x1d4
    bool Contains(int value);
};

// @ 0x00c451a0
bool Obj00c451a0::Contains(int value)
{
    int n = (int)(mEnd - mBegin);
    _ReadWriteBarrier();
    for (int i = 0; i < n; i++) {
        if (mBegin[i] == value)
            return true;
    }
    return false;
}
