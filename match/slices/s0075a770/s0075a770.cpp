// Setter (0x0075a770): store the byte argument in the member at +0x50.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_75a770 {
    char mPad[0x50];
    uint8_t mValue;                             // +0x50
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0075a770
void Owner_75a770::SetValue(uint8_t value)
{
    mValue = value;
}
