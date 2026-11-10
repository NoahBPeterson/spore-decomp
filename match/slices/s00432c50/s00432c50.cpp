// Slice s00432c50: write nine floats into three consecutive Vector3 rows (offsets 0x00, 0x0c,
// 0x18).  The original ends straight at `mov esp, ebp`, so it is a void member, not the
// cSPMatrix3 constructor with the same argument list (a /Od constructor reloads `this` into eax
// before returning, e.g. 0x00432cf0).  No real class is known for the address, so the layout is
// spelled with the RenderWare vector template the matrix types use.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no locals need unwinding).
// The original materializes the address of the yAxis and zAxis rows into two pointer locals
// before writing their components; the xAxis row is written straight through `this`.
#include "game/types.h"
#include "rw/math/fpu/VectorTemplates.h"

typedef rw::math::fpu::Vector3Template<float, 0> Vec3;

struct Vec3Rows {
    Vec3 xAxis;                                     // +0x00
    Vec3 yAxis;                                     // +0x0C
    Vec3 zAxis;                                     // +0x18

    void Set(float a0, float a1, float a2,
             float a3, float a4, float a5,
             float a6, float a7, float a8);
};

// @ 0x00432c50
void Vec3Rows::Set(float a0, float a1, float a2,
                   float a3, float a4, float a5,
                   float a6, float a7, float a8)
{
    Vec3* rowA;
    Vec3* rowB;

    xAxis.x = a0;
    xAxis.y = a1;
    xAxis.z = a2;

    rowA = &yAxis;
    rowB = &zAxis;
    rowA->x = a3;
    rowA->y = a4;
    rowA->z = a5;

    rowB->x = a6;
    rowB->y = a7;
    rowB->z = a8;
}