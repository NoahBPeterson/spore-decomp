// Manager call (0x00980f30): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154faec and 0.
#include "game/types.h"

struct Manager_980f30 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_980f30* GetManager_980f30();          // 0x00920090
extern const char sData_980f30[];          // 0x0154faec

// @ 0x00980f30
void* CallManager_980f30()
{
    return GetManager_980f30()->Method(sData_980f30, 0);
}
