// Forwarder (0x00754fe0): call the object's member (0x754ca0) with the first argument and return its result.
#include "game/types.h"

struct Object_754fe0 {
    void* Call(void* arg);   // 0x00754ca0
};

// @ 0x00754fe0
void* Forward_754fe0(void* arg, Object_754fe0* object)
{
    return object->Call(arg);
}
