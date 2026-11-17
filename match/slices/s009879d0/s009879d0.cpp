// Setter (0x009879d0): store the dword argument in the member at +0x24.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_9879d0 {
    char mPad[0x24];
    uint32_t mValue;                             // +0x24
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x009879d0
void Owner_9879d0::SetValue(uint32_t value)
{
    mValue = value;
}
