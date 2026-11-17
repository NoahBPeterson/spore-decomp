// Manager call (0x00967820): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f224 and 0.
#include "game/types.h"

struct Manager_967820 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_967820* GetManager_967820();          // 0x00920090
extern const char sData_967820[];          // 0x0154f224

// @ 0x00967820
void* CallManager_967820()
{
    return GetManager_967820()->Method(sData_967820, 0);
}
