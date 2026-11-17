// Setter (0x00bfc460): store the dword argument in the member at +0x34.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bfc460 {
    char mPad[0x34];
    uint32_t mValue;                             // +0x34
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00bfc460
void Owner_bfc460::SetValue(uint32_t value)
{
    mValue = value;
}
