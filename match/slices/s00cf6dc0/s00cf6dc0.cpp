// Setter (0x00cf6dc0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1168.
#include "game/types.h"

struct Value12_cf6dc0 { uint32_t a, b, c; };
struct Owner_cf6dc0 {
    char mPad[0x1168];
    Value12_cf6dc0 mValue;                       // +0x1168
    void SetValue(const Value12_cf6dc0& value);
};

// @ 0x00cf6dc0
void Owner_cf6dc0::SetValue(const Value12_cf6dc0& value)
{
    mValue = value;
}
