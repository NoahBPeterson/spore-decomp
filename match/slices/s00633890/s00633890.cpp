// Forwarder (0x00633890): call the object's member (0x633560) with the first argument and return its result.
#include "game/types.h"

struct Object_633890 {
    void* Call(void* arg);   // 0x00633560
};

// @ 0x00633890
void* Forward_633890(void* arg, Object_633890* object)
{
    return object->Call(arg);
}
