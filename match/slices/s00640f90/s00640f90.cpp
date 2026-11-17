// Forwarder (0x00640f90): call the object's member (0x640ee0) with the first argument and return its result.
#include "game/types.h"

struct Object_640f90 {
    void* Call(void* arg);   // 0x00640ee0
};

// @ 0x00640f90
void* Forward_640f90(void* arg, Object_640f90* object)
{
    return object->Call(arg);
}
