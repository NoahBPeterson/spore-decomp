// Setter (0x008d5f10): store the dword argument in the member at +0xac.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8d5f10 {
    char mPad[0xac];
    uint32_t mValue;                             // +0xac
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008d5f10
void Owner_8d5f10::SetValue(uint32_t value)
{
    mValue = value;
}
