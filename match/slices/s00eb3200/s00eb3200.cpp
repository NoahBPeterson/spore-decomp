// Float setter (0x00eb3200): store the value in the float member at +0x10c.
#include "game/types.h"

struct Owner_eb3200 {
    char mPad[0x10c];
    float mValue;                             // +0x10c
    void SetValue(float value);
};

// @ 0x00eb3200
void Owner_eb3200::SetValue(float value)
{
    mValue = value;
}
