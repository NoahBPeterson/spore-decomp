// Setter (0x00fcc200): store the dword argument in the member at +0x18.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_fcc200 {
    char mPad[0x18];
    uint32_t mValue;                             // +0x18
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00fcc200
void Owner_fcc200::SetValue(uint32_t value)
{
    mValue = value;
}
