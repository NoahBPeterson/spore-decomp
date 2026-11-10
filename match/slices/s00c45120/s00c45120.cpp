// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct Object00c45120 {
    void Invoke(void* value, void* typeInfo, void* vtable);
};

// @ 0x00c45120
bool __cdecl FUN_00c45120(Object00c45120* object, void* value)
{
    if (value != 0) {
        object->Invoke(value, (void*)0x01574d38, (void*)0x0146d14c);
    }
    return true;
}
