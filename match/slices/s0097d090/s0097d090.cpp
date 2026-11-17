// Manager call (0x0097d090): get the manager (0x920090) and call its vtable slot 1 with the data at
// 0x154f680 and 0.
#include "game/types.h"

struct Manager_97d090 {
    virtual void v0();
    virtual void* Method(const void* data, int flags);
};
Manager_97d090* GetManager_97d090();          // 0x00920090
extern const char sData_97d090[];          // 0x0154f680

// @ 0x0097d090
void* CallManager_97d090()
{
    return GetManager_97d090()->Method(sData_97d090, 0);
}
