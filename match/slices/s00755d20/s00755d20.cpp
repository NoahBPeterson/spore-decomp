// Forwarder (0x00755d20): call the object's member (0x7555d0) with the first argument and return its result.
#include "game/types.h"

struct Object_755d20 {
    void* Call(void* arg);   // 0x007555d0
};

// @ 0x00755d20
void* Forward_755d20(void* arg, Object_755d20* object)
{
    return object->Call(arg);
}
