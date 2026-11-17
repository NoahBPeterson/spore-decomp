// Forwarder (0x006aec50): call the object's member (0x6aea90) with the first argument and return its result.
#include "game/types.h"

struct Object_6aec50 {
    void* Call(void* arg);   // 0x006aea90
};

// @ 0x006aec50
void* Forward_6aec50(void* arg, Object_6aec50* object)
{
    return object->Call(arg);
}
