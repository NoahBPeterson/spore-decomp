// Setter (0x005f2150): store the byte argument in the member at +0xea.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f2150 {
    char mPad[0xea];
    uint8_t mValue;                             // +0xea
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f2150
void Owner_5f2150::SetValue(uint8_t value)
{
    mValue = value;
}
