// Forwarder (0x00769d70): call the object's member (0x769cb0) with the first argument and return its result.
#include "game/types.h"

struct Object_769d70 {
    void* Call(void* arg);   // 0x00769cb0
};

// @ 0x00769d70
void* Forward_769d70(void* arg, Object_769d70* object)
{
    return object->Call(arg);
}
