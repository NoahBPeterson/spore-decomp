// Setter (0x006b42c0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0xc.
#include "game/types.h"

struct Value12_6b42c0 { uint32_t a, b, c; };
struct Owner_6b42c0 {
    char mPad[0xc];
    Value12_6b42c0 mValue;                       // +0xc
    void SetValue(const Value12_6b42c0& value);
};

// @ 0x006b42c0
void Owner_6b42c0::SetValue(const Value12_6b42c0& value)
{
    mValue = value;
}
