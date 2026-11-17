// Manager call (0x00951360): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154ec9c and 0.
#include "game/types.h"

struct Manager_951360 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_951360* GetManager_951360();          // 0x00920090
extern const char sData_951360[];          // 0x0154ec9c

// @ 0x00951360
void* CallManager_951360()
{
    return GetManager_951360()->Method(sData_951360, 0);
}
