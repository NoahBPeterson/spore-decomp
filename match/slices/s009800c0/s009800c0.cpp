// Manager call (0x009800c0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f990 and 0.
#include "game/types.h"

struct Manager_9800c0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_9800c0* GetManager_9800c0();          // 0x00920090
extern const char sData_9800c0[];          // 0x0154f990

// @ 0x009800c0
void* CallManager_9800c0()
{
    return GetManager_9800c0()->Method(sData_9800c0, 0);
}
