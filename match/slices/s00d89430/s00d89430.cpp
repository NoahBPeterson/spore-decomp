// slice s00d89430: FUN_00d896f0 (0x00d896f0, 248 bytes): creature update step. Clears stealth, fills a
// 0x74-byte request record with constants and calls the locomotion sub-object's virtual slot 0x37 (+0xdc)
// with it. The callee fills the record's first word (a vector-style buffer), which is freed here if
// non-null with a non-zero header word. Then the behaviour-tree object (+0xb4c) gets FUN_00bcb430 and the
// creature's Hover(false) runs.
// Free function (cdecl, one stack argument: the creature; the caller pops it).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef uint32_t uint32;

// 0x00f47380: operator delete (cdecl, one argument).
void operator_delete__(void* p);

// Float constants read from the image (addresses in the names).
extern float g_169f03c;
extern float g_169f040;
extern float g_169f044;
extern float g_1485720;
extern float g_1470f1c;
extern float g_13ec4b4;
extern float g_147c030;

// Behaviour-tree object at creature +0xb4c. Only FUN_00bcb430 is used here (0x00bcb430, thiscall).
struct cBehaviorTreeObj {
    void FUN_00bcb430();
};

// Creature (cSPCreatureBase). +0xc0 is the locomotion sub-object (its vptr is the first word there).
struct cSPCreatureBase {
    char pad00[0xb4c];
    cBehaviorTreeObj* mpBehavior;       // +0xb4c

    void SetStealthed(bool a, bool b);  // 0x00c1aed0 (thiscall, ret 8)
    void Hover(bool b);                 // 0x00c13a30 (thiscall, ret 4)
};

// 0x74-byte request record passed by pointer to the locomotion virtual call.
struct cLocoRequest {
    void*  mpBegin;                 // +0x00 (callee fills; buffer freed by the caller)
    void*  mpEnd;                   // +0x04
    void*  mpCapacity;              // +0x08
    uint32 pad0c[(0x14 - 0x0c) / 4];
    float  mfVec0;                  // +0x14
    float  mfVec1;                  // +0x18
    float  mfVec2;                  // +0x1c
    float  mfScalar;                // +0x20
    uint32 pad24;                   // +0x24
    uint32 pad28[(0x4c - 0x28) / 4];
    uint8_t mbFlag;                 // +0x4c
    uint8_t pad4d[3];
    float  mfZero50;                // +0x50
    float  mfZero54;                // +0x54
    float  mfZero58;                // +0x58
    uint32 mZero5c;                 // +0x5c
    float  mf60;                    // +0x60
    float  mf64;                    // +0x64
    float  mf68;                    // +0x68
    float  mfZero6c;                // +0x6c
    uint32 mZero70;                 // +0x70
};

// 0x00d896f0 (cdecl, plain `ret`).
void FUN_00d896f0(cSPCreatureBase* self)
{
    self->SetStealthed(false, false);

    // The original loads the first and fourth constants before the vtable slot is read.
    float cVec0 = g_169f03c;
    float cMf60 = g_1470f1c;

    // Locomotion vtable slot 0x37 (+0xdc), fetched before the record is filled.
    void** vt = *(void***)((char*)self + 0xc0);
    typedef void (__thiscall *FnLocoSlot)(void* self, cLocoRequest* request);
    FnLocoSlot fn = (FnLocoSlot)vt[0x37];

    cLocoRequest req;
    req.mfVec0 = cVec0;
    req.mfVec1 = g_169f040;
    req.mfVec2 = g_169f044;
    req.mf60 = cMf60;
    req.mfScalar = g_1485720;
    req.mf64 = g_13ec4b4;
    req.mpBegin = 0;
    req.mpEnd = 0;
    req.mpCapacity = 0;
    req.pad24 = 0;
    req.mbFlag = 0;
    req.mfZero50 = 0.0f;
    req.mfZero54 = 0.0f;
    req.mfZero58 = 0.0f;
    req.mZero5c = 0;
    req.mf68 = g_147c030;
    req.mfZero6c = 0.0f;
    req.mZero70 = 0;

    // Thiscall on the locomotion object (this = self + 0xc0) with the record pointer.
    fn((char*)self + 0xc0, &req);

    void* buf = req.mpBegin;
    if (buf != 0 && ((int*)buf)[-1] != 0)
        operator_delete__(buf);

    self->mpBehavior->FUN_00bcb430();
    self->Hover(false);
}
