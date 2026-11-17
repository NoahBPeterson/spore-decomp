// Manager call (0x00988670): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fca0 and 0.
#include "game/types.h"

struct Manager_988670 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_988670* GetManager_988670();          // 0x00920090
extern const char sData_988670[];          // 0x0154fca0

// @ 0x00988670
void* CallManager_988670()
{
    return GetManager_988670()->Method(sData_988670, 0);
}
