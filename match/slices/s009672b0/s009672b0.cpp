// Manager call (0x009672b0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f1f8 and 0.
#include "game/types.h"

struct Manager_9672b0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9672b0* GetManager_9672b0();          // 0x00920090
extern const char sData_9672b0[];          // 0x0154f1f8

// @ 0x009672b0
void* CallManager_9672b0()
{
    return GetManager_9672b0()->Method(sData_9672b0, 0);
}
