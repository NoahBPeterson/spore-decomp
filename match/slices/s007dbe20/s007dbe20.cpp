// Setter (0x007dbe20): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x104.
#include "game/types.h"

struct Value12_7dbe20 { uint32_t a, b, c; };
struct Owner_7dbe20 {
    char mPad[0x104];
    Value12_7dbe20 mValue;                       // +0x104
    void SetValue(const Value12_7dbe20& value);
};

// @ 0x007dbe20
void Owner_7dbe20::SetValue(const Value12_7dbe20& value)
{
    mValue = value;
}
