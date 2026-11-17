// Float setter (0x009805a0): store the value in the float member at +0x4.
#include "game/types.h"

struct Owner_9805a0 {
    char mPad[0x4];
    float mValue;                             // +0x4
    void SetValue(float value);
};

// @ 0x009805a0
void Owner_9805a0::SetValue(float value)
{
    mValue = value;
}
