// Float setter (0x00ecd990): store the value in the float member at +0x64.
#include "game/types.h"

struct Owner_ecd990 {
    char mPad[0x64];
    float mValue;                             // +0x64
    void SetValue(float value);
};

// @ 0x00ecd990
void Owner_ecd990::SetValue(float value)
{
    mValue = value;
}
