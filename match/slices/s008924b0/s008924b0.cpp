// Slice s008924b0 -- small message/state setter: for key 0x12d store (value != 0) into the
// object's +0x48 byte.  Flags: /O2 /MD /Gy /TP /arch=SSE.
#include "types.h"

struct Widget {
    char pad00[0x48];
    bool mFlag;                 // +0x48
    void Set(int key, int value);
};

// @ 0x008924b0
void Widget::Set(int key, int value)
{
    if (key == 0x12d)
        mFlag = (value != 0);
}
