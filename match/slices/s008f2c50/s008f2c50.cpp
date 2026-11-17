// Setter (0x008f2c50): store the dword argument in the member at +0x384.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2c50 {
    char mPad[0x384];
    uint32_t mValue;                             // +0x384
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2c50
void Owner_8f2c50::SetValue(uint32_t value)
{
    mValue = value;
}
