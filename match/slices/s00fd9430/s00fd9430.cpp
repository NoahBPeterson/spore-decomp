// Float setter (0x00fd9430): store the value in the float member at +0x28.
#include "game/types.h"

struct Owner_fd9430 {
    char mPad[0x28];
    float mValue;                             // +0x28
    void SetValue(float value);
};

// @ 0x00fd9430
void Owner_fd9430::SetValue(float value)
{
    mValue = value;
}
