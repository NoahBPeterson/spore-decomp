// Setter (0x0095fa30): store the dword argument in the member at +0x80.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_95fa30 {
    char mPad[0x80];
    uint32_t mValue;                             // +0x80
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0095fa30
void Owner_95fa30::SetValue(uint32_t value)
{
    mValue = value;
}
