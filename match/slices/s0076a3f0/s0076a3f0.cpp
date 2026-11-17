// Forwarder (0x0076a3f0): call the object's member (0x76a300) with the first argument and return its result.
#include "game/types.h"

struct Object_76a3f0 {
    void* Call(void* arg);   // 0x0076a300
};

// @ 0x0076a3f0
void* Forward_76a3f0(void* arg, Object_76a3f0* object)
{
    return object->Call(arg);
}
