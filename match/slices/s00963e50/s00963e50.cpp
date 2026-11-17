// Manager call (0x00963e50): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f178 and 0.
#include "game/types.h"

struct Manager_963e50 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_963e50* GetManager_963e50();          // 0x00920090
extern const char sData_963e50[];          // 0x0154f178

// @ 0x00963e50
void* CallManager_963e50()
{
    return GetManager_963e50()->Method(sData_963e50, 0);
}
