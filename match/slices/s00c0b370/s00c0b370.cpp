// Setter (0x00c0b370): store the dword argument in the member at +0xe3c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c0b370 {
    char mPad[0xe3c];
    uint32_t mValue;                             // +0xe3c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c0b370
void Owner_c0b370::SetValue(uint32_t value)
{
    mValue = value;
}
