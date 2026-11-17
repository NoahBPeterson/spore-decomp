// Setter (0x00c3f530): store the byte argument in the member at +0x230.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c3f530 {
    char mPad[0x230];
    uint8_t mValue;                             // +0x230
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c3f530
void Owner_c3f530::SetValue(uint8_t value)
{
    mValue = value;
}
