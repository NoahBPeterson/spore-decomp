// Setter (0x00d1dce0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0xec.
#include "game/types.h"

struct Value12_d1dce0 { uint32_t a, b, c; };
struct Owner_d1dce0 {
    char mPad[0xec];
    Value12_d1dce0 mValue;                       // +0xec
    void SetValue(const Value12_d1dce0& value);
};

// @ 0x00d1dce0
void Owner_d1dce0::SetValue(const Value12_d1dce0& value)
{
    mValue = value;
}
