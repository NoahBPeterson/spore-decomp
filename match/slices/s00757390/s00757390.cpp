// Forwarder (0x00757390): call the object's member (0x7571a0) with the first argument and return its result.
#include "game/types.h"

struct Object_757390 {
    void* Call(void* arg);   // 0x007571a0
};

// @ 0x00757390
void* Forward_757390(void* arg, Object_757390* object)
{
    return object->Call(arg);
}
