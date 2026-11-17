// Setter (0x009896c0): store the dword argument in the member at +0x650.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_9896c0 {
    char mPad[0x650];
    uint32_t mValue;                             // +0x650
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x009896c0
void Owner_9896c0::SetValue(uint32_t value)
{
    mValue = value;
}
