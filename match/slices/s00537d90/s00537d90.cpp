// @ 0x00537d90
// Swarm skin-paint host (cSPSkinPaintParticleEffect): initialise the transform subobject from
// a default transform and reset the flag. Unoptimised TU:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// (the transform ctor 0x00434040, the Assign at 0x00537dc0 and the effect class itself live in
// slice s00536d40 and are declared here.)
#include "types.h"

// cSPTransform (0x38): flags, mod count, translation, scale, 3x3 rotation.
struct cSPTransform {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float mTranslation[3];  // +0x04
    float mScale;           // +0x10
    float mRotation[9];     // +0x14
    cSPTransform();                             // 0x00434040
    cSPTransform(const cSPTransform& x);        // 0x00538000
    void Compound(const cSPTransform& x);       // 0x00537f40

    cSPTransform& Assign(const void* x);        // 0x00537dc0
};

struct cSPSkinPaintParticleEffect {
    void* mpVtA;               // +0x00
    void* mpVtB;               // +0x04
    void* mpVtC;               // +0x08
    cSPTransform mTransform;   // +0x0c
    bool mFlag;                // +0x44

    void InitParticles(void* a, void* b, void* c);
};

// @ 0x00537d90
void cSPSkinPaintParticleEffect::InitParticles(void* a, void* b, void* c)
{
    (void)a;
    (void)b;
    (void)c;
    cSPTransform t;
    mTransform.Assign(&t);
    mFlag = false;
}
