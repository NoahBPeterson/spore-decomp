// Forwarder (0x007564a0): call the object's member (0x755fe0) with the first argument and return its result.
#include "game/types.h"

struct Object_7564a0 {
    void* Call(void* arg);   // 0x00755fe0
};

// @ 0x007564a0
void* Forward_7564a0(void* arg, Object_7564a0* object)
{
    return object->Call(arg);
}
