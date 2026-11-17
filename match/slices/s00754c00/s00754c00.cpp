// Forwarder (0x00754c00): call the object's member (0x7545b0) with the first argument and return its result.
#include "game/types.h"

struct Object_754c00 {
    void* Call(void* arg);   // 0x007545b0
};

// @ 0x00754c00
void* Forward_754c00(void* arg, Object_754c00* object)
{
    return object->Call(arg);
}
