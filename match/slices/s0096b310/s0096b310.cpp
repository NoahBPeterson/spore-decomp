// Manager call (0x0096b310): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f384 and 0.
#include "game/types.h"

struct Manager_96b310 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_96b310* GetManager_96b310();          // 0x00920090
extern const char sData_96b310[];          // 0x0154f384

// @ 0x0096b310
void* CallManager_96b310()
{
    return GetManager_96b310()->Method(sData_96b310, 0);
}
