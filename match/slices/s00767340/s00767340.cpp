// Forwarder (0x00767340): call the object's member (0x766b30) with the first argument and return its result.
#include "game/types.h"

struct Object_767340 {
    void* Call(void* arg);   // 0x00766b30
};

// @ 0x00767340
void* Forward_767340(void* arg, Object_767340* object)
{
    return object->Call(arg);
}
