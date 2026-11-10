// Slice s00c44ed0: set a bool flag at +0x18c; when clearing a previously-set flag,
// invoke vtable slot 0x1a0 with 1.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct Obj00c44ed0 {
    char pad[0x18c];
    unsigned char mFlag;  // 0x18c

    void SetFlag(unsigned char v);  // 0x00c44ed0
};

// @ 0x00c44ed0
void Obj00c44ed0::SetFlag(unsigned char v)
{
    if (mFlag) {
        if (!v) {
            typedef void (__thiscall *Vfn)(Obj00c44ed0*, int);
            Vfn f = (Vfn)(*(void***)this)[0x1a0 / 4];
            f(this, 1);
        }
        mFlag = v;
    } else {
        mFlag = v;
    }
}
