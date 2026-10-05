// Slice s00535d00: Swarm skin-paint ArgScript paint-variable registration + 16-byte
// element vector copy ctor. The two large registration helpers (00535e40, 005361a0,
// 005365b0, 00536910, 00536b00) are stubbed (partial.txt). Unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0

// ---------------------------------------------------------------- @ 0x00535d00
struct Elem16 {
    uint32_t d[4];
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    uint32_t mAlloc[2];
    Vec16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec16(const Vec16& x);
};
void* uninitialized_copy16(Elem16* first, Elem16* last, Elem16* dest);   // 0x005371a0

// @ 0x00535d00
Vec16::Vec16(const Vec16& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    Elem16* p = (n == 0) ? 0 : (Elem16*)EASTL_Allocate(mAlloc, n * 16, 4, 0);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    mpEnd = (Elem16*)uninitialized_copy16(x.mpBegin, x.mpEnd, mpBegin);
}

// ---------------------------------------------------------------- @ 0x005368f0
struct Host5368f0 {
    char pad[0x30];
    char* p;
    void Set(void* a);   // @ 0x005368f0
};
void Host5368f0::Set(void* a)
{
    (void)a;
    *(int*)(p + 0x50) = 0xff;
}

// ---------------------------------------------------------------- stubs (partial)
// @ 0x00535e40
void RegisterPaintEvalCommandsStub() {}
// @ 0x005361a0
void PaintVariableParseLineStub() {}
// @ 0x005365b0
void PaintVarModifierStub() {}
// @ 0x00536910
void PaintVarCommandStub() {}
// @ 0x00536b00
void PaintVarCommand2Stub() {}
