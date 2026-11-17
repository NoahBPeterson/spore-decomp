// Forwarder (0x00fa9830): call the object's member (0xfa9790) with the first argument and return its result.
#include "game/types.h"

struct Object_fa9830 {
    void* Call(void* arg);   // 0x00fa9790
};

// @ 0x00fa9830
void* Forward_fa9830(void* arg, Object_fa9830* object)
{
    return object->Call(arg);
}
