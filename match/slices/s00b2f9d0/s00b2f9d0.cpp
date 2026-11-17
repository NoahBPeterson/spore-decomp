// Float setter (0x00b2f9d0): store the value in the float member at +0x14c.
#include "game/types.h"

struct Owner_b2f9d0 {
    char mPad[0x14c];
    float mValue;                             // +0x14c
    void SetValue(float value);
};

// @ 0x00b2f9d0
void Owner_b2f9d0::SetValue(float value)
{
    mValue = value;
}
