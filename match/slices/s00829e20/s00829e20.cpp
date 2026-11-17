// Float setter (0x00829e20): store the value in the float member at +0x78.
#include "game/types.h"

struct Owner_829e20 {
    char mPad[0x78];
    float mValue;                             // +0x78
    void SetValue(float value);
};

// @ 0x00829e20
void Owner_829e20::SetValue(float value)
{
    mValue = value;
}
