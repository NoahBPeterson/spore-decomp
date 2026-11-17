// Forwarder (0x00765180): call the object's member (0x7649f0) with the first argument and return its result.
#include "game/types.h"

struct Object_765180 {
    void* Call(void* arg);   // 0x007649f0
};

// @ 0x00765180
void* Forward_765180(void* arg, Object_765180* object)
{
    return object->Call(arg);
}
