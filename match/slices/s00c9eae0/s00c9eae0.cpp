// Setter (0x00c9eae0): store the dword argument in the member at +0xd08.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c9eae0 {
    char mPad[0xd08];
    uint32_t mValue;                             // +0xd08
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c9eae0
void Owner_c9eae0::SetValue(uint32_t value)
{
    mValue = value;
}
