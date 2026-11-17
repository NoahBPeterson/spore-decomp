// Manager call (0x009513b0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154eca0 and 0.
#include "game/types.h"

struct Manager_9513b0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9513b0* GetManager_9513b0();          // 0x00920090
extern const char sData_9513b0[];          // 0x0154eca0

// @ 0x009513b0
void* CallManager_9513b0()
{
    return GetManager_9513b0()->Method(sData_9513b0, 0);
}
