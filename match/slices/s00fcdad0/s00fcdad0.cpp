// Float setter (0x00fcdad0): store the value in the float member at +0x2c.
#include "game/types.h"

struct Owner_fcdad0 {
    char mPad[0x2c];
    float mValue;                             // +0x2c
    void SetValue(float value);
};

// @ 0x00fcdad0
void Owner_fcdad0::SetValue(float value)
{
    mValue = value;
}
