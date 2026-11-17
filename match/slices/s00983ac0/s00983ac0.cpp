// Manager call (0x00983ac0): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fb34 and 0.
#include "game/types.h"

struct Manager_983ac0 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_983ac0* GetManager_983ac0();          // 0x00920090
extern const char sData_983ac0[];          // 0x0154fb34

// @ 0x00983ac0
void* CallManager_983ac0()
{
    return GetManager_983ac0()->Method(sData_983ac0, 0);
}
