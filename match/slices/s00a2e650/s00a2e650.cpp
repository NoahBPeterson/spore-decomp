// Slice s00a2e650 - EA::Audio / UI text-style manager helpers.
#include "types.h"

// ---- eastl::map<unsigned long,unsigned long>::operator[]  (0xa2e060) --------
struct MapUU {
    int& operator[](const uint32_t& key);
};

class cTypeMapHolder {
public:
    char  pad[0x118a5c];
    MapUU mMap;                              // +0x118a5c
    void SetTypePriority(uint32_t type, uint32_t priority);   // @ 0xa2f180
    void InitDefaultPriorities();                             // @ 0xa2f1a0
};

// @ 0xa2f180
void cTypeMapHolder::SetTypePriority(uint32_t type, uint32_t priority)
{
    mMap[type] = (int)priority;
}

// @ 0xa2f1a0
void cTypeMapHolder::InitDefaultPriorities()
{
    mMap[0x3055f61] = 0;
    mMap[0x2b9f662] = 1;
    mMap[0x1a527db] = 2;
}

// ---- placeholders for the remaining functions in this slice -----------------
// @ 0xa2e650
extern "C" int Placeholder_e650() { return 0; }
// @ 0xa2edd0
extern "C" int Placeholder_edd0() { return 0; }
// @ 0xa2ee40
extern "C" int Placeholder_ee40() { return 0; }
// @ 0xa2eed0
extern "C" int Placeholder_eed0() { return 0; }
// @ 0xa2ef60
extern "C" int Placeholder_ef60() { return 0; }
// @ 0xa2f210
extern "C" int Placeholder_f210() { return 0; }
// @ 0xa2f310
extern "C" int Placeholder_f310() { return 0; }
// @ 0xa2f410
extern "C" int Placeholder_f410() { return 0; }
// @ 0xa2f5d0
extern "C" int Placeholder_f5d0() { return 0; }