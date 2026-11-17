// Setter (0x00c227d0): store the dword argument in the member at +0xff4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c227d0 {
    char mPad[0xff4];
    uint32_t mValue;                             // +0xff4
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c227d0
void Owner_c227d0::SetValue(uint32_t value)
{
    mValue = value;
}
