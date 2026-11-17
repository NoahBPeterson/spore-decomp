// Float setter (0x00a67920): store the value in the float member at +0x314.
#include "game/types.h"

struct Owner_a67920 {
    char mPad[0x314];
    float mValue;                             // +0x314
    void SetValue(float value);
};

// @ 0x00a67920
void Owner_a67920::SetValue(float value)
{
    mValue = value;
}
