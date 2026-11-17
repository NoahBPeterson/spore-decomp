// Forwarder (0x008e2ae0): call the object's member (0x8e2a10) with the first argument and return its result.
#include "game/types.h"

struct Object_8e2ae0 {
    void* Call(void* arg);   // 0x008e2a10
};

// @ 0x008e2ae0
void* Forward_8e2ae0(void* arg, Object_8e2ae0* object)
{
    return object->Call(arg);
}
