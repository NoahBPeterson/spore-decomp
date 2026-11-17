// Setter (0x00ae9140): store the dword argument in the member at +0x74.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ae9140 {
    char mPad[0x74];
    uint32_t mValue;                             // +0x74
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00ae9140
void Owner_ae9140::SetValue(uint32_t value)
{
    mValue = value;
}
