// Setter (0x00c41d60): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1c8.
#include "game/types.h"

struct Value12_c41d60 { uint32_t a, b, c; };
struct Owner_c41d60 {
    char mPad[0x1c8];
    Value12_c41d60 mValue;                       // +0x1c8
    void SetValue(const Value12_c41d60& value);
};

// @ 0x00c41d60
void Owner_c41d60::SetValue(const Value12_c41d60& value)
{
    mValue = value;
}
