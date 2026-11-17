// Float setter (0x00ff0370): store the value in the float member at +0x1c.
#include "game/types.h"

struct Owner_ff0370 {
    char mPad[0x1c];
    float mValue;                             // +0x1c
    void SetValue(float value);
};

// @ 0x00ff0370
void Owner_ff0370::SetValue(float value)
{
    mValue = value;
}
