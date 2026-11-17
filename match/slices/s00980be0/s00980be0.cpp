// Manager call (0x00980be0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fa48 and 0.
#include "game/types.h"

struct Manager_980be0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_980be0* GetManager_980be0();          // 0x00920090
extern const char sData_980be0[];          // 0x0154fa48

// @ 0x00980be0
void* CallManager_980be0()
{
    return GetManager_980be0()->Method(sData_980be0, 0);
}
