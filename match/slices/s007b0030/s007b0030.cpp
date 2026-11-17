// Forwarder (0x007b0030): call the object's member (0x7afe10) with the first argument and return its result.
#include "game/types.h"

struct Object_7b0030 {
    void* Call(void* arg);   // 0x007afe10
};

// @ 0x007b0030
void* Forward_7b0030(void* arg, Object_7b0030* object)
{
    return object->Call(arg);
}
