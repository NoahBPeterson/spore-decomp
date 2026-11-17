// Setter (0x00812d80): store the byte argument in the member at +0x222.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_812d80 {
    char mPad[0x222];
    uint8_t mValue;                             // +0x222
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00812d80
void Owner_812d80::SetValue(uint8_t value)
{
    mValue = value;
}
