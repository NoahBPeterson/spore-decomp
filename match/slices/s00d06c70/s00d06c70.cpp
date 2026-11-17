// Setter (0x00d06c70): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x10c.
#include "game/types.h"

struct Value12_d06c70 { uint32_t a, b, c; };
struct Owner_d06c70 {
    char mPad[0x10c];
    Value12_d06c70 mValue;                       // +0x10c
    void SetValue(const Value12_d06c70& value);
};

// @ 0x00d06c70
void Owner_d06c70::SetValue(const Value12_d06c70& value)
{
    mValue = value;
}
