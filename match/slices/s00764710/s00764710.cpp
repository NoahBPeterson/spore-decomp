// Forwarder (0x00764710): call the object's member (0x7646c0) with the first argument and return its result.
#include "game/types.h"

struct Object_764710 {
    void* Call(void* arg);   // 0x007646c0
};

// @ 0x00764710
void* Forward_764710(void* arg, Object_764710* object)
{
    return object->Call(arg);
}
