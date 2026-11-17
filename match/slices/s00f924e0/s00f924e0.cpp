// Float setter (0x00f924e0): store the value in the float member at +0x38.
#include "game/types.h"

struct Owner_f924e0 {
    char mPad[0x38];
    float mValue;                             // +0x38
    void SetValue(float value);
};

// @ 0x00f924e0
void Owner_f924e0::SetValue(float value)
{
    mValue = value;
}
