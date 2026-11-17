// Setter (0x00ff03b0): store the dword argument in the member at +0x38.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ff03b0 {
    char mPad[0x38];
    uint32_t mValue;                             // +0x38
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00ff03b0
void Owner_ff03b0::SetValue(uint32_t value)
{
    mValue = value;
}
