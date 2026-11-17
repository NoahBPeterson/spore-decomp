// Forwarder (0x007651c0): call the object's member (0x765150) with the first argument and return its result.
#include "game/types.h"

struct Object_7651c0 {
    void* Call(void* arg);   // 0x00765150
};

// @ 0x007651c0
void* Forward_7651c0(void* arg, Object_7651c0* object)
{
    return object->Call(arg);
}
