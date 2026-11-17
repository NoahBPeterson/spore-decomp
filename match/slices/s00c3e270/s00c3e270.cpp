// Float setter (0x00c3e270): store the value in the float member at +0x674.
#include "game/types.h"

struct Owner_c3e270 {
    char mPad[0x674];
    float mValue;                             // +0x674
    void SetValue(float value);
};

// @ 0x00c3e270
void Owner_c3e270::SetValue(float value)
{
    mValue = value;
}
