// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct Object00c45100 {
    void Invoke(void* value, void* typeInfo, void* vtable);
};

// @ 0x00c45100
bool __cdecl FUN_00c45100(Object00c45100* object, void* value)
{
    if (value != 0) {
        object->Invoke(value, (void*)0x01574c48, (void*)0x0146d138);
    }
    return true;
}
