// Float setter (0x005f22f0): store the value in the float member at +0x188.
#include "game/types.h"

struct Owner_5f22f0 {
    char mPad[0x188];
    float mValue;                             // +0x188
    void SetValue(float value);
};

// @ 0x005f22f0
void Owner_5f22f0::SetValue(float value)
{
    mValue = value;
}
