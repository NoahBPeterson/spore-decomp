// Manager call (0x00985c80): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fb80 and 0.
#include "game/types.h"

struct Manager_985c80 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_985c80* GetManager_985c80();          // 0x00920090
extern const char sData_985c80[];          // 0x0154fb80

// @ 0x00985c80
void* CallManager_985c80()
{
    return GetManager_985c80()->Method(sData_985c80, 0);
}
