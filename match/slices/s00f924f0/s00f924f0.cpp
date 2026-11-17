// Float setter (0x00f924f0): store the value in the float member at +0x40.
#include "game/types.h"

struct Owner_f924f0 {
    char mPad[0x40];
    float mValue;                             // +0x40
    void SetValue(float value);
};

// @ 0x00f924f0
void Owner_f924f0::SetValue(float value)
{
    mValue = value;
}
