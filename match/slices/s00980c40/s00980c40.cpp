// Float setter (0x00980c40): store the value in the float member at +0x10.
#include "game/types.h"

struct Owner_980c40 {
    char mPad[0x10];
    float mValue;                             // +0x10
    void SetValue(float value);
};

// @ 0x00980c40
void Owner_980c40::SetValue(float value)
{
    mValue = value;
}
