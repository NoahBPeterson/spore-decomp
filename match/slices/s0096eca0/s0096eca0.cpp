// Manager call (0x0096eca0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f568 and 0.
#include "game/types.h"

struct Manager_96eca0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_96eca0* GetManager_96eca0();          // 0x00920090
extern const char sData_96eca0[];          // 0x0154f568

// @ 0x0096eca0
void* CallManager_96eca0()
{
    return GetManager_96eca0()->Method(sData_96eca0, 0);
}
