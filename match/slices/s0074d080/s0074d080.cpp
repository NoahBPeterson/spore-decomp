// Forwarder (0x0074d080): call the object's member (0x74cad0) with the first argument and return its result.
#include "game/types.h"

struct Object_74d080 {
    void* Call(void* arg);   // 0x0074cad0
};

// @ 0x0074d080
void* Forward_74d080(void* arg, Object_74d080* object)
{
    return object->Call(arg);
}
