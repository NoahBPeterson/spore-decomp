// Forwarder (0x00753fa0): call the object's member (0x754c20) with the first argument and return its result.
#include "game/types.h"

struct Object_753fa0 {
    void* Call(void* arg);   // 0x00754c20
};

// @ 0x00753fa0
void* Forward_753fa0(void* arg, Object_753fa0* object)
{
    return object->Call(arg);
}
