#include "game/types.h"

struct Pair16_00e65480 {
    uint16_t lo;
    uint16_t hi;
};

struct SubE0_00e65480 {
    void Insert(const uint32_t& key); // 0x00e64fc0
};

struct Mgr_00e65480 {
    uint8_t pad00[0xe0];
    SubE0_00e65480 mE0;
};

extern Mgr_00e65480* gMgr_016b3c04;

// @ 0x00e65480
void __cdecl InsertPair_00e65480(uint32_t a, uint32_t b)
{
    Pair16_00e65480 p;
    if (a < b) {
        p.hi = (uint16_t)a;
        p.lo = (uint16_t)b;
    } else {
        p.hi = (uint16_t)b;
        p.lo = (uint16_t)a;
    }
    uint32_t packed = *(uint32_t*)&p;
    gMgr_016b3c04->mE0.Insert(packed);
}
