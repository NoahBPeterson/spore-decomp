// Setter (0x008e22c0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x10.
#include "game/types.h"

struct Value12_8e22c0 { uint32_t a, b, c; };
struct Owner_8e22c0 {
    char mPad[0x10];
    Value12_8e22c0 mValue;                       // +0x10
    void SetValue(const Value12_8e22c0& value);
};

// @ 0x008e22c0
void Owner_8e22c0::SetValue(const Value12_8e22c0& value)
{
    mValue = value;
}
