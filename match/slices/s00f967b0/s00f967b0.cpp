// Float setter (0x00f967b0): store the value in the float member at +0x1e4.
#include "game/types.h"

struct Owner_f967b0 {
    char mPad[0x1e4];
    float mValue;                             // +0x1e4
    void SetValue(float value);
};

// @ 0x00f967b0
void Owner_f967b0::SetValue(float value)
{
    mValue = value;
}
