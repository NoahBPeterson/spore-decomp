// Forwarder (0x007aa8d0): call the object's member (0x7aa3a0) with the first argument and return its result.
#include "game/types.h"

struct Object_7aa8d0 {
    void* Call(void* arg);   // 0x007aa3a0
};

// @ 0x007aa8d0
void* Forward_7aa8d0(void* arg, Object_7aa8d0* object)
{
    return object->Call(arg);
}
