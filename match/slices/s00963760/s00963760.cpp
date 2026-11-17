// Float setter (0x00963760): store the value in the float member at +0x34.
#include "game/types.h"

struct Owner_963760 {
    char mPad[0x34];
    float mValue;                             // +0x34
    void SetValue(float value);
};

// @ 0x00963760
void Owner_963760::SetValue(float value)
{
    mValue = value;
}
