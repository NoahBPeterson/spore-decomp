// Manager call (0x00967870): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f228 and 0.
#include "game/types.h"

struct Manager_967870 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_967870* GetManager_967870();          // 0x00920090
extern const char sData_967870[];          // 0x0154f228

// @ 0x00967870
void* CallManager_967870()
{
    return GetManager_967870()->Method(sData_967870, 0);
}
