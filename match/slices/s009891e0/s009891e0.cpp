// Manager call (0x009891e0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fccc and 0.
#include "game/types.h"

struct Manager_9891e0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9891e0* GetManager_9891e0();          // 0x00920090
extern const char sData_9891e0[];          // 0x0154fccc

// @ 0x009891e0
void* CallManager_9891e0()
{
    return GetManager_9891e0()->Method(sData_9891e0, 0);
}
