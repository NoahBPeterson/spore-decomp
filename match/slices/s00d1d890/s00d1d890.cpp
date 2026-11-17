// Setter (0x00d1d890): store the dword argument in the member at +0x10c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_d1d890 {
    char mPad[0x10c];
    uint32_t mValue;                             // +0x10c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00d1d890
void Owner_d1d890::SetValue(uint32_t value)
{
    mValue = value;
}
