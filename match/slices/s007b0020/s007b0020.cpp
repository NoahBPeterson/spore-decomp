// Forwarder (0x007b0020): call the object's member (0x7af720) with the first argument and return its result.
#include "game/types.h"

struct Object_7b0020 {
    void* Call(void* arg);   // 0x007af720
};

// @ 0x007b0020
void* Forward_7b0020(void* arg, Object_7b0020* object)
{
    return object->Call(arg);
}
