// Setter (0x007e5ec0): store the dword argument in the member at +0x168.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7e5ec0 {
    char mPad[0x168];
    uint32_t mValue;                             // +0x168
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x007e5ec0
void Owner_7e5ec0::SetValue(uint32_t value)
{
    mValue = value;
}
