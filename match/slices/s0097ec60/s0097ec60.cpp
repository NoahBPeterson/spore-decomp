// Manager call (0x0097ec60): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f82c and 0.
#include "game/types.h"

struct Manager_97ec60 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_97ec60* GetManager_97ec60();          // 0x00920090
extern const char sData_97ec60[];          // 0x0154f82c

// @ 0x0097ec60
void* CallManager_97ec60()
{
    return GetManager_97ec60()->Method(sData_97ec60, 0);
}
