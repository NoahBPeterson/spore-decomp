// Forwarder (0x00753fb0): call the object's member (0xb7d400) with the first argument and return its result.
#include "game/types.h"

struct Object_753fb0 {
    void* Call(void* arg);   // 0x00b7d400
};

// @ 0x00753fb0
void* Forward_753fb0(void* arg, Object_753fb0* object)
{
    return object->Call(arg);
}
