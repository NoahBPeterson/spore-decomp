// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct Object00c44c70 {
    char pad[0x84];
    int state;

    int GetState();
};

// @ 0x00c44c70
int Object00c44c70::GetState()
{
    return state;
}
