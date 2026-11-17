// Setter (0x00f678b0): store the byte argument in the member at +0x1ce.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_f678b0 {
    char mPad[0x1ce];
    uint8_t mValue;                             // +0x1ce
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00f678b0
void Owner_f678b0::SetValue(uint8_t value)
{
    mValue = value;
}
