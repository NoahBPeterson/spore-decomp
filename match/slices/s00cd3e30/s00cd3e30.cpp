// Setter (0x00cd3e30): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x115c.
#include "game/types.h"

struct Value12_cd3e30 { uint32_t a, b, c; };
struct Owner_cd3e30 {
    char mPad[0x115c];
    Value12_cd3e30 mValue;                       // +0x115c
    void SetValue(const Value12_cd3e30& value);
};

// @ 0x00cd3e30
void Owner_cd3e30::SetValue(const Value12_cd3e30& value)
{
    mValue = value;
}
