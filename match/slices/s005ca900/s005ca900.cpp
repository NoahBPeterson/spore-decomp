// Setter (0x005ca900): store the byte argument in the member at +0x69.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5ca900 {
    char mPad[0x69];
    uint8_t mValue;                             // +0x69
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005ca900
void Owner_5ca900::SetValue(uint8_t value)
{
    mValue = value;
}
