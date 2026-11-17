// Setter (0x008f2940): store the dword argument in the member at +0x2dc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2940 {
    char mPad[0x2dc];
    uint32_t mValue;                             // +0x2dc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2940
void Owner_8f2940::SetValue(uint32_t value)
{
    mValue = value;
}
