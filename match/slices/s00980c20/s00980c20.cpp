// Setter (0x00980c20): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x4.
#include "game/types.h"

struct Value12_980c20 { uint32_t a, b, c; };
struct Owner_980c20 {
    char mPad[0x4];
    Value12_980c20 mValue;                       // +0x4
    void SetValue(const Value12_980c20& value);
};

// @ 0x00980c20
void Owner_980c20::SetValue(const Value12_980c20& value)
{
    mValue = value;
}
