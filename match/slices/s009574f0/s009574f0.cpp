// Manager call (0x009574f0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154ed74 and 0.
#include "game/types.h"

struct Manager_9574f0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9574f0* GetManager_9574f0();          // 0x00920090
extern const char sData_9574f0[];          // 0x0154ed74

// @ 0x009574f0
void* CallManager_9574f0()
{
    return GetManager_9574f0()->Method(sData_9574f0, 0);
}
