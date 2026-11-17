// Forwarder (0x0061eca0): call the object's member (0x61eac0) with the first argument and return its result.
#include "game/types.h"

struct Object_61eca0 {
    void* Call(void* arg);   // 0x0061eac0
};

// @ 0x0061eca0
void* Forward_61eca0(void* arg, Object_61eca0* object)
{
    return object->Call(arg);
}
