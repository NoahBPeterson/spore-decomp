// Setter (0x00c3e1b0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x65c.
#include "game/types.h"

struct Value12_c3e1b0 { uint32_t a, b, c; };
struct Owner_c3e1b0 {
    char mPad[0x65c];
    Value12_c3e1b0 mValue;                       // +0x65c
    void SetValue(const Value12_c3e1b0& value);
};

// @ 0x00c3e1b0
void Owner_c3e1b0::SetValue(const Value12_c3e1b0& value)
{
    mValue = value;
}
