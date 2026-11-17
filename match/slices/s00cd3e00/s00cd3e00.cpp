// Setter (0x00cd3e00): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1150.
#include "game/types.h"

struct Value12_cd3e00 { uint32_t a, b, c; };
struct Owner_cd3e00 {
    char mPad[0x1150];
    Value12_cd3e00 mValue;                       // +0x1150
    void SetValue(const Value12_cd3e00& value);
};

// @ 0x00cd3e00
void Owner_cd3e00::SetValue(const Value12_cd3e00& value)
{
    mValue = value;
}
