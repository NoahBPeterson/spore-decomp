// Setter (0x00eab830): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x108.
#include "game/types.h"

struct Value12_eab830 { uint32_t a, b, c; };
struct Owner_eab830 {
    char mPad[0x108];
    Value12_eab830 mValue;                       // +0x108
    void SetValue(const Value12_eab830& value);
};

// @ 0x00eab830
void Owner_eab830::SetValue(const Value12_eab830& value)
{
    mValue = value;
}
