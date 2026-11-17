// Forwarder (0x007651a0): call the object's member (0x7650d0) with the first argument and return its result.
#include "game/types.h"

struct Object_7651a0 {
    void* Call(void* arg);   // 0x007650d0
};

// @ 0x007651a0
void* Forward_7651a0(void* arg, Object_7651a0* object)
{
    return object->Call(arg);
}
