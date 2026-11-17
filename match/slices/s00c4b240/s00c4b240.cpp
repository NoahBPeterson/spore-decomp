// Setter (0x00c4b240): store the dword argument in the member at +0x1f4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c4b240 {
    char mPad[0x1f4];
    uint32_t mValue;                             // +0x1f4
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c4b240
void Owner_c4b240::SetValue(uint32_t value)
{
    mValue = value;
}
