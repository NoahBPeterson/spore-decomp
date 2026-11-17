// Setter (0x00c22860): store the byte argument in the member at +0x1002.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c22860 {
    char mPad[0x1002];
    uint8_t mValue;                             // +0x1002
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c22860
void Owner_c22860::SetValue(uint8_t value)
{
    mValue = value;
}
