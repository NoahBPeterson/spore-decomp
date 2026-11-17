// Setter (0x00c9ee20): store the dword argument in the member at +0xd24.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c9ee20 {
    char mPad[0xd24];
    uint32_t mValue;                             // +0xd24
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c9ee20
void Owner_c9ee20::SetValue(uint32_t value)
{
    mValue = value;
}
