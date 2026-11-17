// Float setter (0x007dbd70): store the value in the float member at +0x94.
#include "game/types.h"

struct Owner_7dbd70 {
    char mPad[0x94];
    float mValue;                             // +0x94
    void SetValue(float value);
};

// @ 0x007dbd70
void Owner_7dbd70::SetValue(float value)
{
    mValue = value;
}
