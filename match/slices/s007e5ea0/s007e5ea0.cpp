// Float setter (0x007e5ea0): store the value in the float member at +0x164.
#include "game/types.h"

struct Owner_7e5ea0 {
    char mPad[0x164];
    float mValue;                             // +0x164
    void SetValue(float value);
};

// @ 0x007e5ea0
void Owner_7e5ea0::SetValue(float value)
{
    mValue = value;
}
