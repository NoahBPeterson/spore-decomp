// Manager call (0x0097e480): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f7d0 and 0.
#include "game/types.h"

struct Manager_97e480 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_97e480* GetManager_97e480();          // 0x00920090
extern const char sData_97e480[];          // 0x0154f7d0

// @ 0x0097e480
void* CallManager_97e480()
{
    return GetManager_97e480()->Method(sData_97e480, 0);
}
