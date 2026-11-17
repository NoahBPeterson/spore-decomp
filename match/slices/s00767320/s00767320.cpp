// Forwarder (0x00767320): call the object's member (0x767270) with the first argument and return its result.
#include "game/types.h"

struct Object_767320 {
    void* Call(void* arg);   // 0x00767270
};

// @ 0x00767320
void* Forward_767320(void* arg, Object_767320* object)
{
    return object->Call(arg);
}
