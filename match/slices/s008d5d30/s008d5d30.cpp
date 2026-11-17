// Setter (0x008d5d30): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x234.
#include "game/types.h"

struct Value12_8d5d30 { uint32_t a, b, c; };
struct Owner_8d5d30 {
    char mPad[0x234];
    Value12_8d5d30 mValue;                       // +0x234
    void SetValue(const Value12_8d5d30& value);
};

// @ 0x008d5d30
void Owner_8d5d30::SetValue(const Value12_8d5d30& value)
{
    mValue = value;
}
