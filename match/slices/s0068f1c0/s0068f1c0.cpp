// Forwarder (0x0068f1c0): call the object's member (0x68f180) with the first argument and return its result.
#include "game/types.h"

struct Object_68f1c0 {
    void* Call(void* arg);   // 0x0068f180
};

// @ 0x0068f1c0
void* Forward_68f1c0(void* arg, Object_68f1c0* object)
{
    return object->Call(arg);
}
