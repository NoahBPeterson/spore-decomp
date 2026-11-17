// Setter (0x00c5b390): store the dword argument in the member at +0x1f8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c5b390 {
    char mPad[0x1f8];
    uint32_t mValue;                             // +0x1f8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c5b390
void Owner_c5b390::SetValue(uint32_t value)
{
    mValue = value;
}
