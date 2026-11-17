// Float setter (0x00828010): store the value in the float member at +0x4c.
#include "game/types.h"

struct Owner_828010 {
    char mPad[0x4c];
    float mValue;                             // +0x4c
    void SetValue(float value);
};

// @ 0x00828010
void Owner_828010::SetValue(float value)
{
    mValue = value;
}
