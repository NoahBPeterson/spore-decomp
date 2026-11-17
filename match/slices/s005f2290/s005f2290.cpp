// Setter (0x005f2290): store the byte argument in the member at +0x16b.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f2290 {
    char mPad[0x16b];
    uint8_t mValue;                             // +0x16b
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f2290
void Owner_5f2290::SetValue(uint8_t value)
{
    mValue = value;
}
