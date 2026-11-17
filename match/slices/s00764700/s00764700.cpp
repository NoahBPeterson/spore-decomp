// Forwarder (0x00764700): call the object's member (0x7646a0) with the first argument and return its result.
#include "game/types.h"

struct Object_764700 {
    void* Call(void* arg);   // 0x007646a0
};

// @ 0x00764700
void* Forward_764700(void* arg, Object_764700* object)
{
    return object->Call(arg);
}
