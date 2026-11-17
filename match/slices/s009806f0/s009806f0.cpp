// Manager call (0x009806f0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fa18 and 0.
#include "game/types.h"

struct Manager_9806f0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9806f0* GetManager_9806f0();          // 0x00920090
extern const char sData_9806f0[];          // 0x0154fa18

// @ 0x009806f0
void* CallManager_9806f0()
{
    return GetManager_9806f0()->Method(sData_9806f0, 0);
}
