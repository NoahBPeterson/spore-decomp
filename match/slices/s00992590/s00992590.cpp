// Manager call (0x00992590): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x15500d0 and 0.
#include "game/types.h"

struct Manager_992590 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_992590* GetManager_992590();          // 0x00920090
extern const char sData_992590[];          // 0x015500d0

// @ 0x00992590
void* CallManager_992590()
{
    return GetManager_992590()->Method(sData_992590, 0);
}
