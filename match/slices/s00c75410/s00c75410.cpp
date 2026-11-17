// Setter (0x00c75410): store the dword argument in the member at +0x1248.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c75410 {
    char mPad[0x1248];
    uint32_t mValue;                             // +0x1248
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c75410
void Owner_c75410::SetValue(uint32_t value)
{
    mValue = value;
}
