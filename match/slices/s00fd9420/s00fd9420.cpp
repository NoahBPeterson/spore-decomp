// Float setter (0x00fd9420): store the value in the float member at +0x24.
#include "game/types.h"

struct Owner_fd9420 {
    char mPad[0x24];
    float mValue;                             // +0x24
    void SetValue(float value);
};

// @ 0x00fd9420
void Owner_fd9420::SetValue(float value)
{
    mValue = value;
}
