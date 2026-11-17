// Float setter (0x00fd93f0): store the value in the float member at +0x20.
#include "game/types.h"

struct Owner_fd93f0 {
    char mPad[0x20];
    float mValue;                             // +0x20
    void SetValue(float value);
};

// @ 0x00fd93f0
void Owner_fd93f0::SetValue(float value)
{
    mValue = value;
}
