// Manager call (0x00963ef0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f180 and 0.
#include "game/types.h"

struct Manager_963ef0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_963ef0* GetManager_963ef0();          // 0x00920090
extern const char sData_963ef0[];          // 0x0154f180

// @ 0x00963ef0
void* CallManager_963ef0()
{
    return GetManager_963ef0()->Method(sData_963ef0, 0);
}
