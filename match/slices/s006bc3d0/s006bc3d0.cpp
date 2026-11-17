// Setter (0x006bc3d0): store the byte argument in the member at +0x4e8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_6bc3d0 {
    char mPad[0x4e8];
    uint8_t mValue;                             // +0x4e8
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x006bc3d0
void Owner_6bc3d0::SetValue(uint8_t value)
{
    mValue = value;
}
