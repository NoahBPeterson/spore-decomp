// Setter (0x00c41d90): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1d4.
#include "game/types.h"

struct Value12_c41d90 { uint32_t a, b, c; };
struct Owner_c41d90 {
    char mPad[0x1d4];
    Value12_c41d90 mValue;                       // +0x1d4
    void SetValue(const Value12_c41d90& value);
};

// @ 0x00c41d90
void Owner_c41d90::SetValue(const Value12_c41d90& value)
{
    mValue = value;
}
