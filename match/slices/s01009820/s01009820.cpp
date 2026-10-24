// Slice s01009820 - SporeApp 0x01009820..0x0100a640
// SP::cSPSimulatorSpaceGame helpers; the two reconstructions below are the
// AutoRefCount push/erase primitives used by the space-game object lists.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int u32;

// ---- ref-counted objects -----------------------------------------------------
// Objects stored in these lists start with a vtable whose slots 0 and 1 are
// AddRef and Release.
struct cRefCounted {
    void AddRef();
    void Release();
};

static inline void VT_00_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[0])(p); }
static inline void VT_04_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[1])(p); }
static inline void VT_08_1(void* p, int a) { ((void (__thiscall*)(void*, int))(*(void***)p)[2])(p, a); }

void __cdecl FUN_00aea5d0(void* end, cRefCounted** value);   // 0x00aea5d0 DoInsertPtr
void __cdecl FUN_01008820(void* dst, void* src, void* arg);  // 0x01008820

// The growable list of ref-counted pointers (SPVector<AutoRefCount>).
struct cAutoRefVector {
    u8             mPad0000[0x78];
    cRefCounted**  mpBegin;                        // 0x78
    cRefCounted**  mpEnd;                          // 0x7c
    cRefCounted**  mpCapacity;                     // 0x80

    void  Push(cRefCounted* p);                    // 0x01009a40
};

// A list of 0x14-byte object records with a count at +4.
struct cObjectList {
    u8*   mpBegin;                                 // 0x00
    u8*   mpEnd;                                   // 0x04

    void* EraseFront(u8* p);                       // 0x01009ab0
};

// @ 0x01009a40
// Appends one reference-counted object: the temporary reference taken for the
// duration of the call is dropped on the way out.
void cAutoRefVector::Push(cRefCounted* p)
{
    if (p != 0)
        VT_00_0(p);                                // AddRef
    if (mpEnd < mpCapacity) {
        cRefCounted** slot = mpEnd;
        mpEnd = slot + 1;
        if (slot != 0) {
            *slot = p;
            if (p != 0)
                VT_00_0(p);                        // AddRef
        }
    } else {
        FUN_00aea5d0(mpEnd, (cRefCounted**)&p);
    }
    if (p != 0)
        VT_04_0(p);                                // Release
}

// @ 0x01009ab0
// Removes the 0x14-byte record starting at `p` from the list, shifting the tail
// down, and clears the record's callback state; returns `p`.
void* cObjectList::EraseFront(u8* p)
{
    if (p + 0x14 < mpEnd)
        FUN_01008820(p + 0x14, mpEnd, p);
    mpEnd = mpEnd - 0x14;
    void* obj = *(void**)mpEnd;
    VT_08_1(obj, 0);
    return p;
}
