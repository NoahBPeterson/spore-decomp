// Setter (0x00ecdbd0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x18.
#include "game/types.h"

struct Value12_ecdbd0 { uint32_t a, b, c; };
struct Owner_ecdbd0 {
    char mPad[0x18];
    Value12_ecdbd0 mValue;                       // +0x18
    void SetValue(const Value12_ecdbd0& value);
};

// @ 0x00ecdbd0
void Owner_ecdbd0::SetValue(const Value12_ecdbd0& value)
{
    mValue = value;
}
