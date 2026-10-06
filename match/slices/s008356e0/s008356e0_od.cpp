// Slice s008356e0 (w2g7 #38) - /Od helper (separate TU).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void __cdecl FUN_00835f80(void* obj, void* owner);   // 0x835f80

struct ThisObj {
    virtual void t0();
    virtual void t1();
    virtual void t2();
    virtual void t3();
    virtual void t4();
    virtual void* t5();   // +0x14
};
struct TooltipHelper {
    void Attach(void* param);
};

// @ 0x00835fa0
void TooltipHelper::Attach(void* param) {
    FUN_00835f80(param, (char*)this - 4);
    *(void**)((char*)param + 0xc) = ((ThisObj*)this)->t5();
}