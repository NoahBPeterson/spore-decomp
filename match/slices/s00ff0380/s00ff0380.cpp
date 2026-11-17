// Setter (0x00ff0380): store the dword argument in the member at +0xb8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ff0380 {
    char mPad[0xb8];
    uint32_t mValue;                             // +0xb8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00ff0380
void Owner_ff0380::SetValue(uint32_t value)
{
    mValue = value;
}
