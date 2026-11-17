// Setter (0x005cd940): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0xfc.
#include "game/types.h"

struct Value12_5cd940 { uint32_t a, b, c; };
struct Owner_5cd940 {
    char mPad[0xfc];
    Value12_5cd940 mValue;                       // +0xfc
    void SetValue(const Value12_5cd940& value);
};

// @ 0x005cd940
void Owner_5cd940::SetValue(const Value12_5cd940& value)
{
    mValue = value;
}
