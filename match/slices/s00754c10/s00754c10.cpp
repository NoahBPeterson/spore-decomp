// Forwarder (0x00754c10): call the object's member (0x754770) with the first argument and return its result.
#include "game/types.h"

struct Object_754c10 {
    void* Call(void* arg);   // 0x00754770
};

// @ 0x00754c10
void* Forward_754c10(void* arg, Object_754c10* object)
{
    return object->Call(arg);
}
