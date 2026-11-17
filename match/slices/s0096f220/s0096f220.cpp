// Manager call (0x0096f220): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f5f8 and 0.
#include "game/types.h"

struct Manager_96f220 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_96f220* GetManager_96f220();          // 0x00920090
extern const char sData_96f220[];          // 0x0154f5f8

// @ 0x0096f220
void* CallManager_96f220()
{
    return GetManager_96f220()->Method(sData_96f220, 0);
}
