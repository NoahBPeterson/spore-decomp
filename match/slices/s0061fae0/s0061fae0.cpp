// Forwarder (0x0061fae0): call the object's member (0x61f530) with the first argument and return its result.
#include "game/types.h"

struct Object_61fae0 {
    void* Call(void* arg);   // 0x0061f530
};

// @ 0x0061fae0
void* Forward_61fae0(void* arg, Object_61fae0* object)
{
    return object->Call(arg);
}
