// Setter (0x00c9d070): store the dword argument in the member at +0x1fc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c9d070 {
    char mPad[0x1fc];
    uint32_t mValue;                             // +0x1fc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c9d070
void Owner_c9d070::SetValue(uint32_t value)
{
    mValue = value;
}
