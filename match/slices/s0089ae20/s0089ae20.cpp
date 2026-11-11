// Slice s0089ae20 -- the out-of-line eastl::vector<Rec16>::assign(first, last) (thiscall,
// ret 0xc).  0x0089a510 is vector::DoAssign, 0x007f1890 eastl::uninitialized_copy(first,
// last, dest) (its out iterator pointer is the first argument, the last one is dead),
// 0x00705250 memmove, 0x00f47380 operator delete.
//
// NOT BYTE-EXACT YET.  The source is as close as the work on this address got (see
// nonmatching.txt for everything that was tried): the retail code keeps state in
// ebx/esi/edi only, derives `n` into edi from (last - first) >> 4 and reloads
// mpBegin/mpCapacity where they are needed, while cl 15 here insists on ebp (pushed
// past the test), passes the size in a register and re-reads the globals differently.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Rec16 {
    unsigned int m0;
    unsigned int m4;
    unsigned int m8;
    unsigned int mC;
};
typedef char Rec16SizeCheck[sizeof(Rec16) == 16 ? 1 : -1];

typedef unsigned int size_type;

void* __cdecl ClearRange16(void* first, void* last, void* destEnd);   // 0x00705250
void  __cdecl EastlFree(void* p);                                    // 0x00f47380

// eastl::uninitialized_copy(first, last, dest): the destination travels as a writable
// iterator (its address), which is how cl compiles the call.
void __cdecl UninitializedCopy(Rec16** dest, Rec16* first, Rec16* last, int unused);   // 0x007f1890

struct Allocator16 {        // EASTL allocator at this+0x0c (name 0x013f2150, file 0x013ebb38)
    unsigned int mA;        // +0x00
    unsigned int mB;        // +0x04
    const char*  mpName;    // +0x08
    const char*  mpFile;    // +0x0c
    int          mLine;     // +0x10
};

struct Vec16 {
    Rec16*     mpBegin;     // +0x00
    Rec16*     mpEnd;       // +0x04
    Rec16*     mpCapacity;  // +0x08
    Allocator16 mAllocator; // +0x0c

    void assign(Rec16* first, Rec16* last);
    Rec16* DoAssign(Rec16* first, Rec16* last);     // 0x0089a510
};

// @ 0x0089ae20
void Vec16::assign(Rec16* first, Rec16* last)
{
    Rec16* begin = *(Rec16**)this;
    const size_type n = (size_type)(last - first);
    if (n > (size_type)(mpCapacity - begin)) {
        Rec16* p = DoAssign(first, last);
        Rec16* b = mpBegin;
        if (b != 0 && b != mpCapacity)
            EastlFree(b);
        Rec16* end = (Rec16*)((char*)p + (n << 4));
        mpBegin = p;
        mpCapacity = end;
        mpEnd = end;
    } else {
        const size_type oldSize = (size_type)(mpEnd - begin);
        if (n > oldSize) {
            Rec16* p = (Rec16*)((char*)begin + (oldSize << 4));
            p = (Rec16*)ClearRange16(p, last, first);
            mpEnd = p;
        } else {
            Rec16* p = (Rec16*)((char*)begin + (n << 4));
            p = (Rec16*)ClearRange16(p, last, first);
            Rec16* cur = p;
            Rec16* end = mpEnd;
            UninitializedCopy(&cur, p, end, 0);
            mpEnd = cur;
        }
    }
}
