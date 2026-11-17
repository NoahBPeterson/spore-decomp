// Setter (0x00c0c300): store the dword argument in the member at +0xeac.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c0c300 {
    char mPad[0xeac];
    uint32_t mValue;                             // +0xeac
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c0c300
void Owner_c0c300::SetValue(uint32_t value)
{
    mValue = value;
}
