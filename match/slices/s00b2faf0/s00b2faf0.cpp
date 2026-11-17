// Setter (0x00b2faf0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x12c.
#include "game/types.h"

struct Value12_b2faf0 { uint32_t a, b, c; };
struct Owner_b2faf0 {
    char mPad[0x12c];
    Value12_b2faf0 mValue;                       // +0x12c
    void SetValue(const Value12_b2faf0& value);
};

// @ 0x00b2faf0
void Owner_b2faf0::SetValue(const Value12_b2faf0& value)
{
    mValue = value;
}
