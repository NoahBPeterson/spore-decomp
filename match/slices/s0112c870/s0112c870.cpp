// Setter (0x0112c870): store the dword argument in the member at +0xa8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_112c870 {
    char mPad[0xa8];
    uint32_t mValue;                             // +0xa8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0112c870
void Owner_112c870::SetValue(uint32_t value)
{
    mValue = value;
}
