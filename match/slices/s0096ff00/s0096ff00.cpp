// Manager call (0x0096ff00): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f628 and 0.
#include "game/types.h"

struct Manager_96ff00 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_96ff00* GetManager_96ff00();          // 0x00920090
extern const char sData_96ff00[];          // 0x0154f628

// @ 0x0096ff00
void* CallManager_96ff00()
{
    return GetManager_96ff00()->Method(sData_96ff00, 0);
}
