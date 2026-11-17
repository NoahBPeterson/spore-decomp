// Setter (0x00c75740): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1280.
#include "game/types.h"

struct Value12_c75740 { uint32_t a, b, c; };
struct Owner_c75740 {
    char mPad[0x1280];
    Value12_c75740 mValue;                       // +0x1280
    void SetValue(const Value12_c75740& value);
};

// @ 0x00c75740
void Owner_c75740::SetValue(const Value12_c75740& value)
{
    mValue = value;
}
