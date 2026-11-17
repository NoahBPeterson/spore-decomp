// Setter (0x007c7a00): store the byte argument in the member at +0x63.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7c7a00 {
    char mPad[0x63];
    uint8_t mValue;                             // +0x63
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007c7a00
void Owner_7c7a00::SetValue(uint8_t value)
{
    mValue = value;
}
