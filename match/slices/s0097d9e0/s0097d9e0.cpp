// Manager call (0x0097d9e0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f758 and 0.
#include "game/types.h"

struct Manager_97d9e0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_97d9e0* GetManager_97d9e0();          // 0x00920090
extern const char sData_97d9e0[];          // 0x0154f758

// @ 0x0097d9e0
void* CallManager_97d9e0()
{
    return GetManager_97d9e0()->Method(sData_97d9e0, 0);
}
