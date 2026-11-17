// Manager call (0x00970170): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f654 and 0.
#include "game/types.h"

struct Manager_970170 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_970170* GetManager_970170();          // 0x00920090
extern const char sData_970170[];          // 0x0154f654

// @ 0x00970170
void* CallManager_970170()
{
    return GetManager_970170()->Method(sData_970170, 0);
}
