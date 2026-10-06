// @ 0x01330060  $E410   (compiler-generated dynamic initializer of a property table)
//
// PARTIAL.  The retail function is a single straight-line sequence of ~140
// records: for each property it builds a 15-dword descriptor on the stack and
// copies it to the next 0x3c-aligned global (0x0156faa8, 0x0156fae4, ...).
//
// The full data set (names, hashes, accessor function pointers) was not
// transcribed; this reproduces the record layout and the fill operation.

#include "types.h"

// Descriptor layout observed in the retail code (15 dwords / 0x3c bytes):
//   +0x00 const char* name
//   +0x04 uint32_t    nameHash
//   +0x08 uint32_t    memberOffset
//   +0x0c uint32_t    reserved0
//   +0x10 uint32_t    reserved1
//   +0x14 uint32_t    reserved2
//   +0x18 uint32_t    flags
//   +0x1c uint32_t    extra
//   +0x20 void*       getFn
//   +0x24 void*       setFn
//   +0x28 void*       writer1
//   +0x2c void*       writer2
//   +0x30 void*       writer3
//   +0x34 void*       writer4
//   +0x38 void*       writer5
struct PropDesc {
    const char* name;
    uint32_t    hash;
    uint32_t    offset;
    uint32_t    reserved0, reserved1, reserved2;
    uint32_t    flags;
    uint32_t    extra;
    void*       w0; void* w1; void* w2; void* w3; void* w4; void* w5;
};

static void Fill(PropDesc* dst, const char* name, uint32_t hash, uint32_t off,
                 uint32_t flags, uint32_t extra,
                 void* w0, void* w1, void* w2, void* w3, void* w4, void* w5)
{
    PropDesc rec;
    rec.name = name;
    rec.hash = hash;
    rec.offset = off;
    rec.reserved0 = 0; rec.reserved1 = 0; rec.reserved2 = 0;
    rec.flags = flags;
    rec.extra = extra;
    rec.w0 = w0; rec.w1 = w1; rec.w2 = w2;
    rec.w3 = w3; rec.w4 = w4; rec.w5 = w5;
    *dst = rec;
}

void __cdecl _E410(void)
{
    // Placeholder: the retail body is the unrolled per-property sequence, e.g.
    //   Fill((PropDesc*)0x0156faa8, "mCultureSet", 0x3acc625, 0x6c, 0, 0,
    //        FUN_00692ca0, FUN_00bf1c70, FUN_00bf1cb0, ...);
    //   Fill((PropDesc*)0x0156fae4, "mInitialized", 0x23922cc, 0x88, ...);
    // ... 140 records ...
    (void)&Fill;
}
