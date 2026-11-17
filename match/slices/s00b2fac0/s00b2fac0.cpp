// Setter (0x00b2fac0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x120.
#include "game/types.h"

struct Value12_b2fac0 { uint32_t a, b, c; };
struct Owner_b2fac0 {
    char mPad[0x120];
    Value12_b2fac0 mValue;                       // +0x120
    void SetValue(const Value12_b2fac0& value);
};

// @ 0x00b2fac0
void Owner_b2fac0::SetValue(const Value12_b2fac0& value)
{
    mValue = value;
}
