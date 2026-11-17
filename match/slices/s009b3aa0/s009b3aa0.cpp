// Setter (0x009b3aa0): store the byte argument in the member at +0x260.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_9b3aa0 {
    char mPad[0x260];
    uint8_t mValue;                             // +0x260
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x009b3aa0
void Owner_9b3aa0::SetValue(uint8_t value)
{
    mValue = value;
}
