// Setter (0x0077f010): store the dword argument in the member at +0x21c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_77f010 {
    char mPad[0x21c];
    uint32_t mValue;                             // +0x21c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0077f010
void Owner_77f010::SetValue(uint32_t value)
{
    mValue = value;
}
