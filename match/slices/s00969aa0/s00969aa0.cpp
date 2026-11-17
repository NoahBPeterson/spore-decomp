// Manager call (0x00969aa0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f358 and 0.
#include "game/types.h"

struct Manager_969aa0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_969aa0* GetManager_969aa0();          // 0x00920090
extern const char sData_969aa0[];          // 0x0154f358

// @ 0x00969aa0
void* CallManager_969aa0()
{
    return GetManager_969aa0()->Method(sData_969aa0, 0);
}
