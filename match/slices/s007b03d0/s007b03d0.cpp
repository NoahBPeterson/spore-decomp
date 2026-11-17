// Forwarder (0x007b03d0): call the object's member (0x7b01d0) with the first argument and return its result.
#include "game/types.h"

struct Object_7b03d0 {
    void* Call(void* arg);   // 0x007b01d0
};

// @ 0x007b03d0
void* Forward_7b03d0(void* arg, Object_7b03d0* object)
{
    return object->Call(arg);
}
