// Setter (0x005f2160): store the byte argument in the member at +0x166.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f2160 {
    char mPad[0x166];
    uint8_t mValue;                             // +0x166
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f2160
void Owner_5f2160::SetValue(uint8_t value)
{
    mValue = value;
}
