// Setter (0x00ed4890): store the dword argument in the member at +0x20.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ed4890 {
    char mPad[0x20];
    uint32_t mValue;                             // +0x20
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00ed4890
void Owner_ed4890::SetValue(uint32_t value)
{
    mValue = value;
}
