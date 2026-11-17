// Float setter (0x00776450): store the value in the float member at +0x1b8.
#include "game/types.h"

struct Owner_776450 {
    char mPad[0x1b8];
    float mValue;                             // +0x1b8
    void SetValue(float value);
};

// @ 0x00776450
void Owner_776450::SetValue(float value)
{
    mValue = value;
}
