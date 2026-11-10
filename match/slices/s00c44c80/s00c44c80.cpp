// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct Object00c44c80 {
    char pad[0x84];
    int state;

    bool IsStateThree();
};

// @ 0x00c44c80
bool Object00c44c80::IsStateThree()
{
    return state == 3;
}
