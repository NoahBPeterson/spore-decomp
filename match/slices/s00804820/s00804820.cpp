// Setter (0x00804820): store the dword argument in the member at +0x30.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_804820 {
    char mPad[0x30];
    uint32_t mValue;                             // +0x30
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00804820
void Owner_804820::SetValue(uint32_t value)
{
    mValue = value;
}
