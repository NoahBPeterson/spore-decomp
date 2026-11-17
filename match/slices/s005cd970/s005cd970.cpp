// Float setter (0x005cd970): store the value in the float member at +0x11c.
#include "game/types.h"

struct Owner_5cd970 {
    char mPad[0x11c];
    float mValue;                             // +0x11c
    void SetValue(float value);
};

// @ 0x005cd970
void Owner_5cd970::SetValue(float value)
{
    mValue = value;
}
