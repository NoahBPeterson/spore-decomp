// Float setter (0x009fef50): store the value in the float member at +0x90.
#include "game/types.h"

struct Owner_9fef50 {
    char mPad[0x90];
    float mValue;                             // +0x90
    void SetValue(float value);
};

// @ 0x009fef50
void Owner_9fef50::SetValue(float value)
{
    mValue = value;
}
