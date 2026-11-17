// Setter (0x00c74860): store the dword argument in the member at +0x64c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c74860 {
    char mPad[0x64c];
    uint32_t mValue;                             // +0x64c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c74860
void Owner_c74860::SetValue(uint32_t value)
{
    mValue = value;
}
