// Slice s008945a0 -- EA::Text::TextStyle copy constructor.
// Flags: /O2 /MD /GS- /GR- /TP /arch=SSE.
//
// Retail TextStyle is 0x278 bytes: a non-trivial FontStyle base (default ctor 0x00894030) plus
// plain data. The retail copy ctor runs the base default ctor (0x00894030), then copies the whole
// 0x278 bytes over itself with a `memcpy` that folds to `push ebx; mov ebx,ecx; ... rep movsd 0x9e;
// mov eax,ebx` (so the object pointer comes back in eax).
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned);

struct FontStyle {
    FontStyle();                                // 0x00894030
    unsigned char mData[0x278];                 // plain data
};

struct TextStyle : FontStyle {
    TextStyle(const TextStyle& other);
};

// @ 0x008945a0
TextStyle::TextStyle(const TextStyle& other)
    : FontStyle()
{
    memcpy(this, &other, sizeof(TextStyle));
}
