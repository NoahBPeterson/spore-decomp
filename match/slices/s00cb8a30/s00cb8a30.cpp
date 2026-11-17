// Float setter (0x00cb8a30): store the value in the float member at +0x54.
#include "game/types.h"

struct Owner_cb8a30 {
    char mPad[0x54];
    float mValue;                             // +0x54
    void SetValue(float value);
};

// @ 0x00cb8a30
void Owner_cb8a30::SetValue(float value)
{
    mValue = value;
}
