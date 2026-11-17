// Setter (0x00feba60): store the byte argument in the member at +0x17.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_feba60 {
    char mPad[0x17];
    uint8_t mValue;                             // +0x17
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00feba60
void Owner_feba60::SetValue(uint8_t value)
{
    mValue = value;
}
