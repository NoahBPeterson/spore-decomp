// Float setter (0x00989300): store the value in the float member at +0x3c4.
#include "game/types.h"

struct Owner_989300 {
    char mPad[0x3c4];
    float mValue;                             // +0x3c4
    void SetValue(float value);
};

// @ 0x00989300
void Owner_989300::SetValue(float value)
{
    mValue = value;
}
