// Float setter (0x00743ae0): store the value in the float member at +0x2b4.
#include "game/types.h"

struct Owner_743ae0 {
    char mPad[0x2b4];
    float mValue;                             // +0x2b4
    void SetValue(float value);
};

// @ 0x00743ae0
void Owner_743ae0::SetValue(float value)
{
    mValue = value;
}
