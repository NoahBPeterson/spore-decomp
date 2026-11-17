// Setter (0x00f02660): store the byte argument in the member at +0x4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_f02660 {
    char mPad[0x4];
    uint8_t mValue;                             // +0x4
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00f02660
void Owner_f02660::SetValue(uint8_t value)
{
    mValue = value;
}
