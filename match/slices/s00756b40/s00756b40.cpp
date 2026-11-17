// Forwarder (0x00756b40): call the object's member (0x756a20) with the first argument and return its result.
#include "game/types.h"

struct Object_756b40 {
    void* Call(void* arg);   // 0x00756a20
};

// @ 0x00756b40
void* Forward_756b40(void* arg, Object_756b40* object)
{
    return object->Call(arg);
}
