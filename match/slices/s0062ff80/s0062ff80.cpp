// Setter (0x0062ff80): store the dword argument in the member at +0xe74.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_62ff80 {
    char mPad[0xe74];
    uint32_t mValue;                             // +0xe74
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0062ff80
void Owner_62ff80::SetValue(uint32_t value)
{
    mValue = value;
}
