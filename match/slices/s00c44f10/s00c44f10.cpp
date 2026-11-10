// Slice s00c44f10: dword getter at +0xf4 (owner not yet identified; stand-in).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct Obj00c44f10 {
    char pad[0xf4];
    uint32_t value;  // 0xf4

    uint32_t Get() const;  // 0x00c44f10
};

// @ 0x00c44f10
uint32_t Obj00c44f10::Get() const
{
    return value;
}
