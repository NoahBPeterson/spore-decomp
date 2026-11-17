// Forwarder (0x00757190): call the object's member (0x756d80) with the first argument and return its result.
#include "game/types.h"

struct Object_757190 {
    void* Call(void* arg);   // 0x00756d80
};

// @ 0x00757190
void* Forward_757190(void* arg, Object_757190* object)
{
    return object->Call(arg);
}
