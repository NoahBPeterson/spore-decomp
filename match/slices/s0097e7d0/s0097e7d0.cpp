// Manager call (0x0097e7d0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f804 and 0.
#include "game/types.h"

struct Manager_97e7d0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_97e7d0* GetManager_97e7d0();          // 0x00920090
extern const char sData_97e7d0[];          // 0x0154f804

// @ 0x0097e7d0
void* CallManager_97e7d0()
{
    return GetManager_97e7d0()->Method(sData_97e7d0, 0);
}
