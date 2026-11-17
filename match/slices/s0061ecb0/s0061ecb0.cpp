// Forwarder (0x0061ecb0): call the object's member (0x61e740) with the first argument and return its result.
#include "game/types.h"

struct Object_61ecb0 {
    void* Call(void* arg);   // 0x0061e740
};

// @ 0x0061ecb0
void* Forward_61ecb0(void* arg, Object_61ecb0* object)
{
    return object->Call(arg);
}
