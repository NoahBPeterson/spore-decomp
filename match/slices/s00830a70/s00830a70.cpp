// Float setter (0x00830a70): store the value in the float member at +0x44.
#include "game/types.h"

struct Owner_830a70 {
    char mPad[0x44];
    float mValue;                             // +0x44
    void SetValue(float value);
};

// @ 0x00830a70
void Owner_830a70::SetValue(float value)
{
    mValue = value;
}
