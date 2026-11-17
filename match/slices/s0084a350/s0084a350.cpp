// Setter (0x0084a350): store the dword argument in the member at +0xd0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_84a350 {
    char mPad[0xd0];
    uint32_t mValue;                             // +0xd0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0084a350
void Owner_84a350::SetValue(uint32_t value)
{
    mValue = value;
}
