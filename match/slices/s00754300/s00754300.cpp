// Forwarder (0x00754300): call the object's member (0x754110) with the first argument and return its result.
#include "game/types.h"

struct Object_754300 {
    void* Call(void* arg);   // 0x00754110
};

// @ 0x00754300
void* Forward_754300(void* arg, Object_754300* object)
{
    return object->Call(arg);
}
