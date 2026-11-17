// Float setter (0x00ff03c0): store the value in the float member at +0x3c.
#include "game/types.h"

struct Owner_ff03c0 {
    char mPad[0x3c];
    float mValue;                             // +0x3c
    void SetValue(float value);
};

// @ 0x00ff03c0
void Owner_ff03c0::SetValue(float value)
{
    mValue = value;
}
