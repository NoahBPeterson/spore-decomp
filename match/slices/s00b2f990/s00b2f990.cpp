// Setter (0x00b2f990): store the byte argument in the member at +0x15a.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2f990 {
    char mPad[0x15a];
    uint8_t mValue;                             // +0x15a
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b2f990
void Owner_b2f990::SetValue(uint8_t value)
{
    mValue = value;
}
