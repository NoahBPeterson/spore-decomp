// Slice s00c44bd0: register four property/event ids via vtable slot 0x150.
// Same id set as GameObj::RegisterIds_c44b80; different class/slot.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct Obj00c44bd0 {
    virtual void v0();
    // ... slots up to 0x150/4 = 84
    virtual void RegisterId(unsigned int id);  // slot at +0x150 — stand-in; body unused

    void RegisterIds();  // 0x00c44bd0
};

// Force slot 0x150 by calling through raw vtable.
static inline void call_v150(Obj00c44bd0* self, unsigned int id)
{
    typedef void (__thiscall *Vfn)(Obj00c44bd0*, unsigned int);
    Vfn f = (Vfn)(*(void***)self)[0x150 / 4];
    f(self, id);
}

// @ 0x00c44bd0
void Obj00c44bd0::RegisterIds()
{
    call_v150(this, 0x35ec3de);
    call_v150(this, 0x248975f);
    call_v150(this, 0x2489760);
    call_v150(this, 0x4249453);
}
