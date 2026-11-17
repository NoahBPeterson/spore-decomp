// Manager call (0x0096b360): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f388 and 0.
#include "game/types.h"

struct Manager_96b360 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_96b360* GetManager_96b360();          // 0x00920090
extern const char sData_96b360[];          // 0x0154f388

// @ 0x0096b360
void* CallManager_96b360()
{
    return GetManager_96b360()->Method(sData_96b360, 0);
}
