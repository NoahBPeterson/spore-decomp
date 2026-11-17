// Manager call (0x0096f040): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f5c8 and 0.
#include "game/types.h"

struct Manager_96f040 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_96f040* GetManager_96f040();          // 0x00920090
extern const char sData_96f040[];          // 0x0154f5c8

// @ 0x0096f040
void* CallManager_96f040()
{
    return GetManager_96f040()->Method(sData_96f040, 0);
}
