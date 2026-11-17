// Float setter (0x00c3e210): store the value in the float member at +0x66c.
#include "game/types.h"

struct Owner_c3e210 {
    char mPad[0x66c];
    float mValue;                             // +0x66c
    void SetValue(float value);
};

// @ 0x00c3e210
void Owner_c3e210::SetValue(float value)
{
    mValue = value;
}
