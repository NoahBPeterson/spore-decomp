// Setter (0x00bb9b90): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x74.
#include "game/types.h"

struct Value12_bb9b90 { uint32_t a, b, c; };
struct Owner_bb9b90 {
    char mPad[0x74];
    Value12_bb9b90 mValue;                       // +0x74
    void SetValue(const Value12_bb9b90& value);
};

// @ 0x00bb9b90
void Owner_bb9b90::SetValue(const Value12_bb9b90& value)
{
    mValue = value;
}
