
#include "types.h"

struct cGonzagoTimer {
    unsigned int data[8];

    ~cGonzagoTimer(); // 0x00b638b0
};

struct tGrobShockData {
    int mField00;
    int mField04;
    cGonzagoTimer mTimer;
};

typedef bool (__cdecl* ShockCompare)(
    const tGrobShockData&,
    const tGrobShockData&
);

// 0x01010f70: swaps two tGrobShockData records
void __cdecl FUN_01010f70(
    tGrobShockData* a,
    tGrobShockData* b
);


// @ 0x01012f80
tGrobShockData* __cdecl FUN_01012f80(
    tGrobShockData* first,
    tGrobShockData* last,
    tGrobShockData pivot,
    ShockCompare compare
)
{
scan_first:
    if (compare(*first, pivot)) {
        ++first;
        goto scan_first;
    }

    --last;

scan_last:
    if (compare(pivot, *last)) {
        --last;
        goto scan_last;
    }

    if (first < last) {
        FUN_01010f70(first, last);
        ++first;
        goto scan_first;
    }

    return first;
}
