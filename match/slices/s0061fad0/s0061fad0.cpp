// Forwarder (0x0061fad0): call the object's member (0x61f670) with the first argument and return its result.
#include "game/types.h"

struct Object_61fad0 {
    void* Call(void* arg);   // 0x0061f670
};

// @ 0x0061fad0
void* Forward_61fad0(void* arg, Object_61fad0* object)
{
    return object->Call(arg);
}
