// Float setter (0x00ecb780): store the value in the float member at +0x6c.
#include "game/types.h"

struct Owner_ecb780 {
    char mPad[0x6c];
    float mValue;                             // +0x6c
    void SetValue(float value);
};

// @ 0x00ecb780
void Owner_ecb780::SetValue(float value)
{
    mValue = value;
}
