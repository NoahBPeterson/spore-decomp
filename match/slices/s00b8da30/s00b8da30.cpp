// Setter (0x00b8da30): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x188.
#include "game/types.h"

struct Value12_b8da30 { uint32_t a, b, c; };
struct Owner_b8da30 {
    char mPad[0x188];
    Value12_b8da30 mValue;                       // +0x188
    void SetValue(const Value12_b8da30& value);
};

// @ 0x00b8da30
void Owner_b8da30::SetValue(const Value12_b8da30& value)
{
    mValue = value;
}
