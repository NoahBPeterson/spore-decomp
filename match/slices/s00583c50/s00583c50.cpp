// slice s00583c50 — vector resize helper + stubs.
#include "types.h"

struct cIntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    void Resize(uint32_t n);
    int* Insert(int* at, uint32_t count, const int* value);   // @ 0x0057f220
    int* Erase(int* first, int* last);                       // @ 0x005c2170
};

// @ 0x00584160
void cIntVec::Resize(uint32_t n)
{
    int* begin = mpBegin;
    int* end = mpEnd;
    uint32_t cur = (uint32_t)(end - begin);
    if (n > cur) {
        int zero = 0;
        Insert(end, n - cur, &zero);
        return;
    }
    Erase(begin + n, end);
}

// ---------------------------------------------------------------------------------------------
void FUN_00583c50() {}   // 0x00583c50  1046 B
void FUN_00584070() {}   // 0x00584070  234 B
void FUN_005841b0() {}   // 0x005841b0  122 B
void FUN_00584230() {}   // 0x00584230  193 B
