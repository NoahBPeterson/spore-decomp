// Forwarder (0x00767330): call the object's member (0x766e10) with the first argument and return its result.
#include "game/types.h"

struct Object_767330 {
    void* Call(void* arg);   // 0x00766e10
};

// @ 0x00767330
void* Forward_767330(void* arg, Object_767330* object)
{
    return object->Call(arg);
}
