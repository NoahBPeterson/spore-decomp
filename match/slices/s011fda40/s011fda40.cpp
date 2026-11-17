// Setter (0x011fda40): store the dword argument in the member at +0xc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_11fda40 {
    char mPad[0xc];
    uint32_t mValue;                             // +0xc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x011fda40
void Owner_11fda40::SetValue(uint32_t value)
{
    mValue = value;
}
