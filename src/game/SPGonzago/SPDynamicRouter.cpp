// src/game/SPGonzago/SPDynamicRouter.cpp -- migrated from slice(s) s004fe8c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPDynamicRouter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "cSPTransform.h"

// ---- items of slice s004fe8c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vec3 { float x, y, z; };
struct Vec3f : Vec3 {
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
    Vec3f& operator=(const Vec3f& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; };
struct cSPTransform_s004f_e8c0 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vec3 mTranslation;
    float mScale;
    Mat3 mRotation;
    void BackTransformPoint(Vec3* p);  // 0x004ff6d0 (cSPTransform::BackTransformPoint)
    cSPTransform_s004f_e8c0& operator=(const cSPTransform_s004f_e8c0& o);  // 0x00537dc0
};
void __cdecl FUN_004fc5a0(Vec3* p, Vec3* t);
void __cdecl FUN_004a9d20(Vec3* p, float* s);
Vec3* __cdecl FUN_0047ff90(Vec3* out, Mat3* m, Vec3* p);
// ---- items of slice s004fe8c0 end

// @ 0x004ff660
Vec3f* __cdecl FUN_004ff660(Vec3f* out, cSPTransform_s004f_e8c0* t, Vec3f* in)
{
    ScratchSlots<9>();
    Vec3f v = *in;
    t->BackTransformPoint(&v);
    *out = v;
    return out;
}

// @ 0x004ff6d0
void cSPTransform_s004f_e8c0::BackTransformPoint(Vec3* p)
{
    FUN_004fc5a0(p, &mTranslation);
    if (mScale != 1.0f)
        FUN_004a9d20(p, &mScale);
    if (mFlags & 2) {
        ScratchSlots<6>();
        Vec3 tmp;
        *p = *FUN_0047ff90(&tmp, &mRotation, p);
    }
}
