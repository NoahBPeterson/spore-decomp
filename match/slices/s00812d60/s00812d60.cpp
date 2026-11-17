// Setter (0x00812d60): store the byte argument in the member at +0x221.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_812d60 {
    char mPad[0x221];
    uint8_t mValue;                             // +0x221
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00812d60
void Owner_812d60::SetValue(uint8_t value)
{
    mValue = value;
}
