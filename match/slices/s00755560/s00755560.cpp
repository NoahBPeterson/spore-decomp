// Forwarder (0x00755560): call the object's member (0x755520) with the first argument and return its result.
#include "game/types.h"

struct Object_755560 {
    void* Call(void* arg);   // 0x00755520
};

// @ 0x00755560
void* Forward_755560(void* arg, Object_755560* object)
{
    return object->Call(arg);
}
