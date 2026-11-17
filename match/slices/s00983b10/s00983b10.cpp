// Manager call (0x00983b10): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fb38 and 0.
#include "game/types.h"

struct Manager_983b10 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_983b10* GetManager_983b10();          // 0x00920090
extern const char sData_983b10[];          // 0x0154fb38

// @ 0x00983b10
void* CallManager_983b10()
{
    return GetManager_983b10()->Method(sData_983b10, 0);
}
