// Scalar deleting destructor (0x00e20690): run the destructor (0xe20630), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e20690(void* p);   // 0x00f47380

struct Object_e20690 {
    ~Object_e20690();        // 0x00e20630
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e20690
void* Object_e20690::DeletingDtor(unsigned int flags)
{
    this->~Object_e20690();
    if (flags & 1)
        Free_e20690(this);
    return this;
}
