// Float setter (0x00743980): store the value in the float member at +0x2b8.
#include "game/types.h"

struct Owner_743980 {
    char mPad[0x2b8];
    float mValue;                             // +0x2b8
    void SetValue(float value);
};

// @ 0x00743980
void Owner_743980::SetValue(float value)
{
    mValue = value;
}
