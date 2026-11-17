// Setter (0x00bb9ab0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x3c.
#include "game/types.h"

struct Value12_bb9ab0 { uint32_t a, b, c; };
struct Owner_bb9ab0 {
    char mPad[0x3c];
    Value12_bb9ab0 mValue;                       // +0x3c
    void SetValue(const Value12_bb9ab0& value);
};

// @ 0x00bb9ab0
void Owner_bb9ab0::SetValue(const Value12_bb9ab0& value)
{
    mValue = value;
}
