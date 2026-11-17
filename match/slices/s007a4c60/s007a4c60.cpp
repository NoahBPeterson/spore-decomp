// Setter (0x007a4c60): store the byte argument in the member at +0x168.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7a4c60 {
    char mPad[0x168];
    uint8_t mValue;                             // +0x168
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007a4c60
void Owner_7a4c60::SetValue(uint8_t value)
{
    mValue = value;
}
