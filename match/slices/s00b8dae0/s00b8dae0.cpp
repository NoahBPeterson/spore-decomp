// Setter (0x00b8dae0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x198.
#include "game/types.h"

struct Value12_b8dae0 { uint32_t a, b, c; };
struct Owner_b8dae0 {
    char mPad[0x198];
    Value12_b8dae0 mValue;                       // +0x198
    void SetValue(const Value12_b8dae0& value);
};

// @ 0x00b8dae0
void Owner_b8dae0::SetValue(const Value12_b8dae0& value)
{
    mValue = value;
}
