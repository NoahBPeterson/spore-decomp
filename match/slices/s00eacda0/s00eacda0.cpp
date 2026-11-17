// Setter (0x00eacda0): store the dword argument in the member at +0x108.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_eacda0 {
    char mPad[0x108];
    uint32_t mValue;                             // +0x108
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00eacda0
void Owner_eacda0::SetValue(uint32_t value)
{
    mValue = value;
}
