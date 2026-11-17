// Setter (0x00967e60): store the dword argument in the member at +0x2c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_967e60 {
    char mPad[0x2c];
    uint32_t mValue;                             // +0x2c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00967e60
void Owner_967e60::SetValue(uint32_t value)
{
    mValue = value;
}
