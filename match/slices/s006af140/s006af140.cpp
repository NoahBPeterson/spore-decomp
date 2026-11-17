// Forwarder (0x006af140): call the object's member (0x6aee60) with the first argument and return its result.
#include "game/types.h"

struct Object_6af140 {
    void* Call(void* arg);   // 0x006aee60
};

// @ 0x006af140
void* Forward_6af140(void* arg, Object_6af140* object)
{
    return object->Call(arg);
}
