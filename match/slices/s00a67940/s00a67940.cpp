// Float setter (0x00a67940): store the value in the float member at +0x310.
#include "game/types.h"

struct Owner_a67940 {
    char mPad[0x310];
    float mValue;                             // +0x310
    void SetValue(float value);
};

// @ 0x00a67940
void Owner_a67940::SetValue(float value)
{
    mValue = value;
}
