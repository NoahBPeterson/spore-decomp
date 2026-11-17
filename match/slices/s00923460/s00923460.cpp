// Setter (0x00923460): store the byte argument in the member at +0xc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_923460 {
    char mPad[0xc];
    uint8_t mValue;                             // +0xc
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00923460
void Owner_923460::SetValue(uint8_t value)
{
    mValue = value;
}
