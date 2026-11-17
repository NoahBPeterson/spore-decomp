// Setter (0x00edcc70): store the dword argument in the member at +0x104.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_edcc70 {
    char mPad[0x104];
    uint32_t mValue;                             // +0x104
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00edcc70
void Owner_edcc70::SetValue(uint32_t value)
{
    mValue = value;
}
