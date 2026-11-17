// Float setter (0x00989330): store the value in the float member at +0x414.
#include "game/types.h"

struct Owner_989330 {
    char mPad[0x414];
    float mValue;                             // +0x414
    void SetValue(float value);
};

// @ 0x00989330
void Owner_989330::SetValue(float value)
{
    mValue = value;
}
