// Setter (0x0067e0e0): store the byte argument in the member at +0x64.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_67e0e0 {
    char mPad[0x64];
    uint8_t mValue;                             // +0x64
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0067e0e0
void Owner_67e0e0::SetValue(uint8_t value)
{
    mValue = value;
}
