// Setter (0x00a37f50): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x20.
#include "game/types.h"

struct Value12_a37f50 { uint32_t a, b, c; };
struct Owner_a37f50 {
    char mPad[0x20];
    Value12_a37f50 mValue;                       // +0x20
    void SetValue(const Value12_a37f50& value);
};

// @ 0x00a37f50
void Owner_a37f50::SetValue(const Value12_a37f50& value)
{
    mValue = value;
}
