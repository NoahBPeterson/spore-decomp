// Forwarder (0x006b0890): call the object's member (0x6b05d0) with the first argument and return its result.
#include "game/types.h"

struct Object_6b0890 {
    void* Call(void* arg);   // 0x006b05d0
};

// @ 0x006b0890
void* Forward_6b0890(void* arg, Object_6b0890* object)
{
    return object->Call(arg);
}
