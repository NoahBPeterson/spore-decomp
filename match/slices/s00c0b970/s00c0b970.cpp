// Float setter (0x00c0b970): store the value in the float member at +0xbb8.
#include "game/types.h"

struct Owner_c0b970 {
    char mPad[0xbb8];
    float mValue;                             // +0xbb8
    void SetValue(float value);
};

// @ 0x00c0b970
void Owner_c0b970::SetValue(float value)
{
    mValue = value;
}
