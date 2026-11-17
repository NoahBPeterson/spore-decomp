// Setter (0x00bef8f0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0xc4.
#include "game/types.h"

struct Value12_bef8f0 { uint32_t a, b, c; };
struct Owner_bef8f0 {
    char mPad[0xc4];
    Value12_bef8f0 mValue;                       // +0xc4
    void SetValue(const Value12_bef8f0& value);
};

// @ 0x00bef8f0
void Owner_bef8f0::SetValue(const Value12_bef8f0& value)
{
    mValue = value;
}
