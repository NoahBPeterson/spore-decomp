// Manager call (0x00991f20): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x15500a0 and 0.
#include "game/types.h"

struct Manager_991f20 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_991f20* GetManager_991f20();          // 0x00920090
extern const char sData_991f20[];          // 0x015500a0

// @ 0x00991f20
void* CallManager_991f20()
{
    return GetManager_991f20()->Method(sData_991f20, 0);
}
