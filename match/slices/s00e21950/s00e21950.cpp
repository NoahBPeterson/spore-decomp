// Setter (0x00e21950): store the byte argument in the member at +0x1e5.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_e21950 {
    char mPad[0x1e5];
    uint8_t mValue;                             // +0x1e5
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00e21950
void Owner_e21950::SetValue(uint8_t value)
{
    mValue = value;
}
