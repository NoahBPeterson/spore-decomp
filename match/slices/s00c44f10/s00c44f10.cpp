// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct Object00c44f10 {
    char pad[0xf4];
    unsigned value;

    unsigned GetValue();
};

// @ 0x00c44f10
unsigned Object00c44f10::GetValue()
{
    return value;
}
