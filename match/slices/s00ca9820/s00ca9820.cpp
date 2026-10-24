// Slice s00ca9820 -- ref-counted slot vector range erase.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

// Ref-counted object used by the 16-byte slot vector.
class cRefObj16 {
public:
    virtual void v000();                                 // +0x00
    virtual void v004();                                 // +0x04
    virtual void Release();                              // +0x08
};

// One 16-byte slot: payload pointer plus padding.
struct tSlot16 {
    cRefObj16* mpObj;                                    // +0x00
    uint8_t    pad004[0x0c];                             // +0x04 .. +0x0f
};

// Ref-counted object used by the 24-byte slot vector.
class cRefObj24 {
public:
    virtual void v000();                                 // +0x00
    virtual void Release();                              // +0x04
};

// One 24-byte slot: payload pointer plus padding.
struct tSlot24 {
    cRefObj24* mpObj;                                    // +0x00
    uint8_t    pad004[0x14];                             // +0x04 .. +0x17
};

extern tSlot16* __cdecl FUN_00ca0e80(tSlot16* pLast, tSlot16* pEnd, tSlot16* pFirst); // 0x00ca0e80
extern tSlot24* __cdecl FUN_00ca0da0(tSlot24* pLast, tSlot24* pEnd, tSlot24* pFirst); // 0x00ca0da0

// Vector of 16-byte slots.
class cSlotVector16 {
public:
    tSlot16* Erase(tSlot16* pFirst, tSlot16* pLast);

    tSlot16* mpBegin;                                    // +0x00
    tSlot16* mpEnd;                                      // +0x04
    tSlot16* mpCapacity;                                 // +0x08
};

// Vector of 24-byte slots.
class cSlotVector24 {
public:
    tSlot24* Erase(tSlot24* pFirst, tSlot24* pLast);

    tSlot24* mpBegin;                                    // +0x00
    tSlot24* mpEnd;                                      // +0x04
    tSlot24* mpCapacity;                                 // +0x08
};

namespace SP {

class cVehicle {
public:
    void DestroyVehicle();
};

} // namespace SP

using namespace SP;

// @ 0xca9820 FUN_00ca9820
void __cdecl FUN_00ca9820()
{
}

// @ 0xca9b00 cSlotVector24::Erase
tSlot24* __thiscall cSlotVector24::Erase(tSlot24* pFirst, tSlot24* pLast)
{
    tSlot24* pNewEnd = FUN_00ca0da0(pLast, mpEnd, pFirst);
    tSlot24* pEnd = mpEnd;
    for (tSlot24* p = pNewEnd; p < pEnd; ++p) {
        if (p->mpObj)
            p->mpObj->Release();
    }
    mpEnd -= (int32_t)(pLast - pFirst);
    return pFirst;
}

// @ 0xca9b70 FUN_00ca9b70
void __cdecl FUN_00ca9b70()
{
}

// @ 0xca9cc0 cSlotVector16::Erase
tSlot16* __thiscall cSlotVector16::Erase(tSlot16* pFirst, tSlot16* pLast)
{
    tSlot16* pNewEnd = FUN_00ca0e80(pLast, mpEnd, pFirst);
    tSlot16* pEnd = mpEnd;
    for (tSlot16* p = pNewEnd; p < pEnd; ++p) {
        if (p->mpObj)
            p->mpObj->Release();
    }
    mpEnd -= (int32_t)(pLast - pFirst);
    return pFirst;
}

// @ 0xca9d20 FUN_00ca9d20
void __cdecl FUN_00ca9d20()
{
}

// @ 0xca9e90 FUN_00ca9e90
void __cdecl FUN_00ca9e90()
{
}

// @ 0xcaa0c0 FUN_00caa0c0
void __cdecl FUN_00caa0c0()
{
}

// @ 0xcaa1c0 FUN_00caa1c0
void __cdecl FUN_00caa1c0()
{
}

// @ 0xcaa360 SP::cVehicle::DestroyVehicle
void __thiscall cVehicle::DestroyVehicle()
{
}
