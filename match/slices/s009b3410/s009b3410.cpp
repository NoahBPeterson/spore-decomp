// Float setter (0x009b3410): store the value in the float member at +0x3ec.
#include "game/types.h"

struct Owner_9b3410 {
    char mPad[0x3ec];
    float mValue;                             // +0x3ec
    void SetValue(float value);
};

// @ 0x009b3410
void Owner_9b3410::SetValue(float value)
{
    mValue = value;
}
