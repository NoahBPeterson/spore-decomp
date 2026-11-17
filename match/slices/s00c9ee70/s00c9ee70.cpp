// Float setter (0x00c9ee70): store the value in the float member at +0xd2c.
#include "game/types.h"

struct Owner_c9ee70 {
    char mPad[0xd2c];
    float mValue;                             // +0xd2c
    void SetValue(float value);
};

// @ 0x00c9ee70
void Owner_c9ee70::SetValue(float value)
{
    mValue = value;
}
