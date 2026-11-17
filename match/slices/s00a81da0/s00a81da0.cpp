// Setter (0x00a81da0): store the dword argument in the member at +0x180.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a81da0 {
    char mPad[0x180];
    uint32_t mValue;                             // +0x180
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00a81da0
void Owner_a81da0::SetValue(uint32_t value)
{
    mValue = value;
}
