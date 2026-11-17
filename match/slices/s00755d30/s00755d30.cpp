// Forwarder (0x00755d30): call the object's member (0x755c80) with the first argument and return its result.
#include "game/types.h"

struct Object_755d30 {
    void* Call(void* arg);   // 0x00755c80
};

// @ 0x00755d30
void* Forward_755d30(void* arg, Object_755d30* object)
{
    return object->Call(arg);
}
