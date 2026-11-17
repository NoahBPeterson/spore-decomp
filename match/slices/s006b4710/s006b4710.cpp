// Forwarder (0x006b4710): call the object's member (0x6b4490) with the first argument and return its result.
#include "game/types.h"

struct Object_6b4710 {
    void* Call(void* arg);   // 0x006b4490
};

// @ 0x006b4710
void* Forward_6b4710(void* arg, Object_6b4710* object)
{
    return object->Call(arg);
}
