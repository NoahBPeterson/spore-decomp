// Float setter (0x010171e0): store the value in the float member at +0x8c.
#include "game/types.h"

struct Owner_10171e0 {
    char mPad[0x8c];
    float mValue;                             // +0x8c
    void SetValue(float value);
};

// @ 0x010171e0
void Owner_10171e0::SetValue(float value)
{
    mValue = value;
}
