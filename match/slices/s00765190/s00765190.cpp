// Forwarder (0x00765190): call the object's member (0x764820) with the first argument and return its result.
#include "game/types.h"

struct Object_765190 {
    void* Call(void* arg);   // 0x00764820
};

// @ 0x00765190
void* Forward_765190(void* arg, Object_765190* object)
{
    return object->Call(arg);
}
