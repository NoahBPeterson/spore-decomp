// Setter (0x00e31b20): store the dword argument in the member at +0x44.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_e31b20 {
    char mPad[0x44];
    uint32_t mValue;                             // +0x44
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00e31b20
void Owner_e31b20::SetValue(uint32_t value)
{
    mValue = value;
}
