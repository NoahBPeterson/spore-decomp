// Setter (0x00cb3d00): store the byte argument in the member at +0x16e.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_cb3d00 {
    char mPad[0x16e];
    uint8_t mValue;                             // +0x16e
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00cb3d00
void Owner_cb3d00::SetValue(uint8_t value)
{
    mValue = value;
}
