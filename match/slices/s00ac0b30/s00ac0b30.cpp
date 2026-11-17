// Setter (0x00ac0b30): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x5c.
#include "game/types.h"

struct Value12_ac0b30 { uint32_t a, b, c; };
struct Owner_ac0b30 {
    char mPad[0x5c];
    Value12_ac0b30 mValue;                       // +0x5c
    void SetValue(const Value12_ac0b30& value);
};

// @ 0x00ac0b30
void Owner_ac0b30::SetValue(const Value12_ac0b30& value)
{
    mValue = value;
}
