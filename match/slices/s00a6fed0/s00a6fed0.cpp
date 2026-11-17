// Setter (0x00a6fed0): store the dword argument in the member at +0x28.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a6fed0 {
    char mPad[0x28];
    uint32_t mValue;                             // +0x28
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00a6fed0
void Owner_a6fed0::SetValue(uint32_t value)
{
    mValue = value;
}
