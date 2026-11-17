// Setter (0x00c227a0): store the dword argument in the member at +0xff8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c227a0 {
    char mPad[0xff8];
    uint32_t mValue;                             // +0xff8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c227a0
void Owner_c227a0::SetValue(uint32_t value)
{
    mValue = value;
}
