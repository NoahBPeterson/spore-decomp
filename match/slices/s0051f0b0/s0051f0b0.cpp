// Slice 7: nSPSkinner::cPaintSystem::ProcessHit and a two-float vector assignment helper.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

struct Vector2 {
    float x;
    float y;
    Vector2& operator=(const Vector2& other);
};

// @ 0x0051fb60
Vector2& Vector2::operator=(const Vector2& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

// @ 0x0051f0b0 nSPSkinner::cPaintSystem::ProcessHit -- PARTIAL skeleton (2724-byte /Od body)
void FUN_0051f0b0(void* self) { (void)self; }
