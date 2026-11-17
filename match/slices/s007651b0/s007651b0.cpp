// Forwarder (0x007651b0): call the object's member (0x7650f0) with the first argument and return its result.
#include "game/types.h"

struct Object_7651b0 {
    void* Call(void* arg);   // 0x007650f0
};

// @ 0x007651b0
void* Forward_7651b0(void* arg, Object_7651b0* object)
{
    return object->Call(arg);
}
