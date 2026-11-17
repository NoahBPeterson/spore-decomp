// Setter (0x006e6be0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1e8.
#include "game/types.h"

struct Value12_6e6be0 { uint32_t a, b, c; };
struct Owner_6e6be0 {
    char mPad[0x1e8];
    Value12_6e6be0 mValue;                       // +0x1e8
    void SetValue(const Value12_6e6be0& value);
};

// @ 0x006e6be0
void Owner_6e6be0::SetValue(const Value12_6e6be0& value)
{
    mValue = value;
}
