// Forwarder (0x00997720): call the object's member (0x9972a0) with the first argument and return its result.
#include "game/types.h"

struct Object_997720 {
    void* Call(void* arg);   // 0x009972a0
};

// @ 0x00997720
void* Forward_997720(void* arg, Object_997720* object)
{
    return object->Call(arg);
}
