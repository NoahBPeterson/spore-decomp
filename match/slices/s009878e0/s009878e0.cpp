// Manager call (0x009878e0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fbc8 and 0.
#include "game/types.h"

struct Manager_9878e0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9878e0* GetManager_9878e0();          // 0x00920090
extern const char sData_9878e0[];          // 0x0154fbc8

// @ 0x009878e0
void* CallManager_9878e0()
{
    return GetManager_9878e0()->Method(sData_9878e0, 0);
}
