// Forwarder (0x007646f0): call the object's member (0x764670) with the first argument and return its result.
#include "game/types.h"

struct Object_7646f0 {
    void* Call(void* arg);   // 0x00764670
};

// @ 0x007646f0
void* Forward_7646f0(void* arg, Object_7646f0* object)
{
    return object->Call(arg);
}
