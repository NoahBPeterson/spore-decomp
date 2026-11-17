// Setter (0x00bfe220): store the dword argument in the member at +0x288.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bfe220 {
    char mPad[0x288];
    uint32_t mValue;                             // +0x288
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00bfe220
void Owner_bfe220::SetValue(uint32_t value)
{
    mValue = value;
}
