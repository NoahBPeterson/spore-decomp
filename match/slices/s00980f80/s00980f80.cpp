// Manager call (0x00980f80): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154faf0 and 0.
#include "game/types.h"

struct Manager_980f80 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_980f80* GetManager_980f80();          // 0x00920090
extern const char sData_980f80[];          // 0x0154faf0

// @ 0x00980f80
void* CallManager_980f80()
{
    return GetManager_980f80()->Method(sData_980f80, 0);
}
