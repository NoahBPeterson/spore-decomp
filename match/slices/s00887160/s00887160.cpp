// Slice s00887160 -- dtor body for the object whose vtable pointer is 0x014279b0.
//
// Callees, read off the retail code:
//   0x00886fc0 clears +0x48, the hashtable range at +0x128 and the list range at +0x14c
//   0x00885f60 / 0x00885f20 recursive list dtors (thiscall on the range, one node arg;
//              node[+0] = child, node[+4] = next, node[+0x18]->vtbl[3] = operator delete,
//              element size 0x14 / 0x10)
//   0x008de7f0 deletes every node of a hashtable's bucket array (thiscall on the table,
//              buckets + count on the stack, ret 8)
//   0x00f47380 operator delete, 0x0088b560 the base dtor (tail call)
//
// Member offsets, read off the retail code:
//   +0x128 hashtable: buckets +0x12c, bucket count +0x130, count +0x134,
//                     node allocator +0x144
//   +0x14c hashtable: buckets +0x150, bucket count +0x154, count +0x158,
//                     node allocator +0x168
//   +0x170 range:     node +0x17c, buffer +0x190, buffer end +0x1a0
//   +0x1b8 range:     node +0x1c4 (elements of 0x14 bytes)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef char WordSizeCheck_s00887160[sizeof(void*) == 4 ? 1 : -1];

void __cdecl FUN_00886fc0(void* self);                                   // 0x00886fc0
void __cdecl EastlFree(void* p);                                         // 0x00f47380
void __cdecl BaseDtor(void* self);                                       // 0x0088b560

struct Allocator_s00887160 {     // eastl allocator; frees a bucket array through vtbl[3]
    unsigned    mA;              // +0x00
    unsigned    mB;              // +0x04
    const char* mpName;          // +0x08
    const char* mpFile;          // +0x0c
    int         mLine;           // +0x10
    void*       mpVtbl;          // +0x14
};

struct Range_s00887160 {         // intrusive list head
    char m[0x34];
    void Dtor20(void* node);     // 0x00885f60
    void Dtor10(void* node);     // 0x00885f20
};

struct Hash_s00887160 {          // hashtable head
    char m[0x1c];
    void ClearNodes(void** buckets, unsigned count);   // 0x008de7f0
};

// The object has no header in the repo; it is described by the word offsets the retail
// code touches: +0x12c/+0x130/+0x144, +0x150/+0x154/+0x168,
// +0x17c/+0x190/+0x1a0, +0x1c4.
struct Obj_s00887160 {
    char m[0x1c8];

    __forceinline unsigned& w(unsigned off) { return *(unsigned*)(m + off); }
    __forceinline unsigned& w2(unsigned off) { return *(unsigned*)(m + off); }
    __forceinline unsigned& w3(unsigned off) { return *(unsigned*)(m + off); }
    __forceinline void*&    p(unsigned off) { return *(void**)(m + off); }

    void Teardown();             // 0x00887160
};

// @ 0x00887160
void Obj_s00887160::Teardown()
{
    p(0) = (void*)0x14279b0;
    FUN_00886fc0(this);

    ((Range_s00887160*)(m + 0x1b8))->Dtor20(p(0x1c4));

    void* buf = p(0x190);
    if (buf != 0 && buf != p(0x1a0))
        EastlFree(buf);

    ((Range_s00887160*)(m + 0x170))->Dtor10(p(0x17c));

    // hashtable at +0x14c
    {
        unsigned n = w(0x154);
        ((Hash_s00887160*)(m + 0x14c))->ClearNodes((void**)p(0x150), n);
        w2(0x158) = 0;
        if (n > 1) {
            Allocator_s00887160* a = (Allocator_s00887160*)(m + 0x168);
            void** vt = *(void***)a;
            ((void (__thiscall*)(Allocator_s00887160*, void*, unsigned))vt[3])
                (a, p(0x150), n * 4 + 4);
        }
    }

    // hashtable at +0x128
    {
        unsigned n = w(0x130);
        ((Hash_s00887160*)(m + 0x128))->ClearNodes((void**)p(0x12c), n);
        w3(0x134) = 0;
        if (n > 1) {
            Allocator_s00887160* a = (Allocator_s00887160*)(m + 0x144);
            void** vt = *(void***)a;
            ((void (__thiscall*)(Allocator_s00887160*, void*, unsigned))vt[3])
                (a, p(0x12c), n * 4 + 4);
        }
    }

    BaseDtor(this);
}
