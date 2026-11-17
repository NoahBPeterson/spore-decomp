// Setter (0x007a4c80): store the byte argument in the member at +0x16a.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7a4c80 {
    char mPad[0x16a];
    uint8_t mValue;                             // +0x16a
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007a4c80
void Owner_7a4c80::SetValue(uint8_t value)
{
    mValue = value;
}
