// Float setter (0x009709d0): store the value in the float member at +0x60.
#include "game/types.h"

struct Owner_9709d0 {
    char mPad[0x60];
    float mValue;                             // +0x60
    void SetValue(float value);
};

// @ 0x009709d0
void Owner_9709d0::SetValue(float value)
{
    mValue = value;
}
