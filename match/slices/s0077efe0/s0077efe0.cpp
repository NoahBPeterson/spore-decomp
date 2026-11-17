// Setter (0x0077efe0): copy a 12-byte value (three words, e.g. a vector or a resource key) into the member at +0x194.
#include "game/types.h"

struct Value12_77efe0 { uint32_t a, b, c; };
struct Owner_77efe0 {
    char mPad[0x194];
    Value12_77efe0 mValue;                       // +0x194
    void SetValue(const Value12_77efe0& value);
};

// @ 0x0077efe0
void Owner_77efe0::SetValue(const Value12_77efe0& value)
{
    mValue = value;
}
