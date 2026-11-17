// Forwarder (0x007ae910): call the object's member (0x7afae0) with the first argument and return its result.
#include "game/types.h"

struct Object_7ae910 {
    void* Call(void* arg);   // 0x007afae0
};

// @ 0x007ae910
void* Forward_7ae910(void* arg, Object_7ae910* object)
{
    return object->Call(arg);
}
