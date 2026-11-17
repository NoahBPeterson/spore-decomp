// Setter (0x00a16a90): store the dword argument in the member at +0x54.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a16a90 {
    char mPad[0x54];
    uint32_t mValue;                             // +0x54
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00a16a90
void Owner_a16a90::SetValue(uint32_t value)
{
    mValue = value;
}
