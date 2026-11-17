// Manager call (0x00985c30): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154fb7c and 0.
#include "game/types.h"

struct Manager_985c30 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_985c30* GetManager_985c30();          // 0x00920090
extern const char sData_985c30[];          // 0x0154fb7c

// @ 0x00985c30
void* CallManager_985c30()
{
    return GetManager_985c30()->Method(sData_985c30, 0);
}
