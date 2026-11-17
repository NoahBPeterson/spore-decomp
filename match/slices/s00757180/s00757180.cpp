// Forwarder (0x00757180): call the object's member (0x756c70) with the first argument and return its result.
#include "game/types.h"

struct Object_757180 {
    void* Call(void* arg);   // 0x00756c70
};

// @ 0x00757180
void* Forward_757180(void* arg, Object_757180* object)
{
    return object->Call(arg);
}
