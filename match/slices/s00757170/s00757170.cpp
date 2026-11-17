// Forwarder (0x00757170): call the object's member (0x756b50) with the first argument and return its result.
#include "game/types.h"

struct Object_757170 {
    void* Call(void* arg);   // 0x00756b50
};

// @ 0x00757170
void* Forward_757170(void* arg, Object_757170* object)
{
    return object->Call(arg);
}
