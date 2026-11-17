// Float setter (0x00ecb790): store the value in the float member at +0x70.
#include "game/types.h"

struct Owner_ecb790 {
    char mPad[0x70];
    float mValue;                             // +0x70
    void SetValue(float value);
};

// @ 0x00ecb790
void Owner_ecb790::SetValue(float value)
{
    mValue = value;
}
