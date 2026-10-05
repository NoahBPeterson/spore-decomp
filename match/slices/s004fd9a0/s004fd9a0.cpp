// Slice s004fd9a0: allocator/vector/string helpers (unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).
#include "types.h"

struct Vector2 { float x, y; };

void FUN_00425990(void* p);                       // 0x00425990
void FUN_004feb50();                              // 0x004feb50
void FUN_00442365(void* s, const wchar_t* first, const wchar_t* last); // 0x00423650 (assign)
void thunk_009265b0(void* p);                     // 0x00926640
char AddCore(void* a, int b, int c);              // 0x00926650

// @ 0x004fddb0
int MaxIndex(const float* p)
{
    if (p[0] <= p[1]) {
        if (p[1] <= p[2])
            return 2;
        return 1;
    } else {
        if (p[0] <= p[2])
            return 2;
        return 0;
    }
}

// @ 0x004fde40
void* PopChunk(void* alloc)
{
    for (;;) {
        if (*(void**)((char*)alloc + 0x10)) {
            void* c = *(void**)((char*)alloc + 0x10);
            *(void**)((char*)alloc + 0x10) = *(void**)c;
            return c;
        }
        if (!AddCore(alloc, 0, 0))
            return 0;
    }
}

// @ 0x004fe7f0
Vector2* AddVec2(Vector2* out, const Vector2* a, const Vector2* b)
{
    Vector2 r;
    r.x = a->x + b->x;
    r.y = a->y + b->y;
    Vector2 s = r;
    *out = s;
    return out;
}

// @ 0x004fdd60
void FUN_004fdd60(void* self)
{
    thunk_009265b0((char*)self + 0x24);
    for (uint32_t i = *(uint32_t*)((char*)self + 0x10); i < *(uint32_t*)((char*)self + 0x14); i += 4) {
    }
    FUN_00425990((char*)self + 0x10);
}

// @ 0x004fe860
void FUN_004fe860(void* self, const wchar_t* s)
{
    FUN_004feb50();
    *(char*)((char*)self + 0x3c) = 0;
    const wchar_t* end = s;
    while (*end)
        ++end;
    FUN_00442365(self, s, end);
}

// ---------------------------------------------------------------------------
// Large /Od bodies below are skeletons (listed in partial.txt).
// ---------------------------------------------------------------------------
// @ 0x004fd9a0
void FUN_004fd9a0() {}
// @ 0x004fdcb0
void FUN_004fdcb0() {}
// @ 0x004fde90
void FUN_004fde90() {}
// @ 0x004fe070
void FUN_004fe070() {}
// @ 0x004fe2a0
void FUN_004fe2a0() {}
// @ 0x004fe510
void FUN_004fe510() {}
