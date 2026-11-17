// Setter (0x00bebdd0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x268.
#include "game/types.h"

struct Value12_bebdd0 { uint32_t a, b, c; };
struct Owner_bebdd0 {
    char mPad[0x268];
    Value12_bebdd0 mValue;                       // +0x268
    void SetValue(const Value12_bebdd0& value);
};

// @ 0x00bebdd0
void Owner_bebdd0::SetValue(const Value12_bebdd0& value)
{
    mValue = value;
}
