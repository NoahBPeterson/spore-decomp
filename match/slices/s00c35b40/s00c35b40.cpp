// Float setter (0x00c35b40): store the value in the float member at +0x134.
#include "game/types.h"

struct Owner_c35b40 {
    char mPad[0x134];
    float mValue;                             // +0x134
    void SetValue(float value);
};

// @ 0x00c35b40
void Owner_c35b40::SetValue(float value)
{
    mValue = value;
}
