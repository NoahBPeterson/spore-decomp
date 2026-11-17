// Float setter (0x00b2f9a0): store the value in the float member at +0x148.
#include "game/types.h"

struct Owner_b2f9a0 {
    char mPad[0x148];
    float mValue;                             // +0x148
    void SetValue(float value);
};

// @ 0x00b2f9a0
void Owner_b2f9a0::SetValue(float value)
{
    mValue = value;
}
