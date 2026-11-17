// Manager call (0x0097e780): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f800 and 0.
#include "game/types.h"

struct Manager_97e780 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_97e780* GetManager_97e780();          // 0x00920090
extern const char sData_97e780[];          // 0x0154f800

// @ 0x0097e780
void* CallManager_97e780()
{
    return GetManager_97e780()->Method(sData_97e780, 0);
}
