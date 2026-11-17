// Forwarder (0x006b4720): call the object's member (0x6b4610) with the first argument and return its result.
#include "game/types.h"

struct Object_6b4720 {
    void* Call(void* arg);   // 0x006b4610
};

// @ 0x006b4720
void* Forward_6b4720(void* arg, Object_6b4720* object)
{
    return object->Call(arg);
}
