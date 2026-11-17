// Forwarder (0x006b4b50): call the object's member (0x6b4a10) with the first argument and return its result.
#include "game/types.h"

struct Object_6b4b50 {
    void* Call(void* arg);   // 0x006b4a10
};

// @ 0x006b4b50
void* Forward_6b4b50(void* arg, Object_6b4b50* object)
{
    return object->Call(arg);
}
