// Float setter (0x00c0baf0): store the value in the float member at +0xb84.
#include "game/types.h"

struct Owner_c0baf0 {
    char mPad[0xb84];
    float mValue;                             // +0xb84
    void SetValue(float value);
};

// @ 0x00c0baf0
void Owner_c0baf0::SetValue(float value)
{
    mValue = value;
}
