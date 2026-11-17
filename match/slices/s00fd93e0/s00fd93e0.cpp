// Float setter (0x00fd93e0): store the value in the float member at +0x18.
#include "game/types.h"

struct Owner_fd93e0 {
    char mPad[0x18];
    float mValue;                             // +0x18
    void SetValue(float value);
};

// @ 0x00fd93e0
void Owner_fd93e0::SetValue(float value)
{
    mValue = value;
}
