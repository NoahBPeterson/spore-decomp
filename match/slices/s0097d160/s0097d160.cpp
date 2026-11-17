// Setter (0x0097d160): store the dword argument in the member at +0x14.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_97d160 {
    char mPad[0x14];
    uint32_t mValue;                             // +0x14
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0097d160
void Owner_97d160::SetValue(uint32_t value)
{
    mValue = value;
}
