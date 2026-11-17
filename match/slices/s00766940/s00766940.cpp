// Forwarder (0x00766940): call the object's member (0x7664e0) with the first argument and return its result.
#include "game/types.h"

struct Object_766940 {
    void* Call(void* arg);   // 0x007664e0
};

// @ 0x00766940
void* Forward_766940(void* arg, Object_766940* object)
{
    return object->Call(arg);
}
