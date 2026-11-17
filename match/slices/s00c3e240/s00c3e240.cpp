// Float setter (0x00c3e240): store the value in the float member at +0x678.
#include "game/types.h"

struct Owner_c3e240 {
    char mPad[0x678];
    float mValue;                             // +0x678
    void SetValue(float value);
};

// @ 0x00c3e240
void Owner_c3e240::SetValue(float value)
{
    mValue = value;
}
