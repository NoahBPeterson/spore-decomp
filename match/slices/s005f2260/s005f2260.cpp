// Setter (0x005f2260): store the byte argument in the member at +0xe8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f2260 {
    char mPad[0xe8];
    uint8_t mValue;                             // +0xe8
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f2260
void Owner_5f2260::SetValue(uint8_t value)
{
    mValue = value;
}
