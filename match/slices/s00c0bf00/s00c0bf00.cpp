// Setter (0x00c0bf00): store the byte argument in the member at +0xb67.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c0bf00 {
    char mPad[0xb67];
    uint8_t mValue;                             // +0xb67
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c0bf00
void Owner_c0bf00::SetValue(uint8_t value)
{
    mValue = value;
}
