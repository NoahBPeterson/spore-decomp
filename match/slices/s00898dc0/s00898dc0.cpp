// Slice s00898dc0 -- allocate a copy of a count-element array through an
// allocator member and hand the range to a five-argument copy helper.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---- callees ---------------------------------------------------------------
extern int* __cdecl FUN_0076ffd0(int* out, int first, int last, int dst, int value);     // 0x0076ffd0

// this+0xc is the allocator object (vtable at +0, slot 2 = Allocate(bytes, zero, tag));
// this+0x10 is the tag passed through.
struct Allocator_00898dc0;
typedef void* (__thiscall *AllocateFn_00898dc0)(Allocator_00898dc0* self, int bytes, int zero, void* tag);

struct Allocator_00898dc0 {
    void** vtable;                                    // +0x00
    inline void* Allocate(int bytes, int zero, void* tag)
    {
        return ((AllocateFn_00898dc0)vtable[2])(this, bytes, zero, tag);
    }
};

struct Self_00898dc0 {
    char pad[0x0c];
    Allocator_00898dc0* mAlloc;                       // +0x0c
    void* mTag;                                       // +0x10
    int* Assign(int count, int first, int last);
};

// @ 0x00898dc0
int* Self_00898dc0::Assign(int count, int first, int last)
{
    int* p;
    if (count != 0) {
        Allocator_00898dc0* a = mAlloc;
        void* tag = mTag;
        p = (int*)a->Allocate(count * 2 * 2 * 2, 0, tag);
    } else
        p = 0;
    FUN_0076ffd0(&count, first, last, (int)p, count);
    return p;
}
