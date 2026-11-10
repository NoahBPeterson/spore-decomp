// Slice s00898d70: append a run of 12-byte records.  The destination storage comes
// from an allocator reachable through this+0xc (vtable slot 2); the records are then
// copied by 0x00898b80, which receives the count back by reference and by value.
// Flags: /O2 /MD /Gy /TP
#include "types.h"

typedef unsigned int u32;

struct Rec12 {
    u32 a, b, c;
};

struct IdxHolder {
    virtual void slot0();
    virtual void slot1();
    virtual void* Alloc(u32 bytes, int flags, u32 ctx);   // slot 2, +0x08
};

struct AppendCtx {
    u32         mPad00[3];       // +0x00 .. +0x0b
    IdxHolder*  mpAlloc;         // +0x0c
    u32         mCtx;            // +0x10

    Rec12* Append(int count, Rec12* first, Rec12* last);   // 0x00898d70
};

// 0x00898b80: copies the records to dst and reports the advanced pointers/counts.
extern "C" void __cdecl FUN_00898b80(int*, Rec12* first, Rec12* last, Rec12* dst, int count);

// @ 0x00898d70
Rec12* AppendCtx::Append(int count, Rec12* first, Rec12* last)
{
    Rec12* dst;
    if (count != 0) {
        IdxHolder* h = mpAlloc;
        dst = (Rec12*)h->Alloc((u32)(count * 0xc), 0, mCtx);
    } else {
        dst = 0;
    }
    FUN_00898b80(&count, dst, first, last, count);
    return dst;
}