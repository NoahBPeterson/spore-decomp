// Setter (0x00c75a20): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x1290.
#include "game/types.h"

struct Value12_c75a20 { uint32_t a, b, c; };
struct Owner_c75a20 {
    char mPad[0x1290];
    Value12_c75a20 mValue;                       // +0x1290
    void SetValue(const Value12_c75a20& value);
};

// @ 0x00c75a20
void Owner_c75a20::SetValue(const Value12_c75a20& value)
{
    mValue = value;
}
