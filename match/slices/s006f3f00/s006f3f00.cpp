// Float setter (0x006f3f00): store the value in the float member at +0x170.
#include "game/types.h"

struct Owner_6f3f00 {
    char mPad[0x170];
    float mValue;                             // +0x170
    void SetValue(float value);
};

// @ 0x006f3f00
void Owner_6f3f00::SetValue(float value)
{
    mValue = value;
}
