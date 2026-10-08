// s00d39800: one function, 0x00d39dc0 (426 bytes), cdecl void(int source, const Vec3POD* pos).
// Keeps a single global effect (0x0169e2d0) alive while the flag 0x0169e2cc is set: it re-creates
// the effect through EffectsManager's vtable slot 11, then builds a cSPTransform on the stack
// (offset from pos, rotation from the planet surface orientation) and pushes it into the effect
// (slots 17, 6 and 2). Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

struct Vec3POD { float x, y, z; };
struct Quaternion { float x, y, z, w; };

struct Matrix3 {
    float m[9];
    Matrix3& Assign(const Matrix3& o);          // 0x0041cb40, thiscall ret 4
};

// Effect object stored in the global at 0x0169e2d0. Only the slots used here are named.
struct IEffect {
    virtual void s0();
    virtual void Release();                     // slot 1 (+4), no args
    virtual void s2(int);                       // slot 2 (+8), called with 0
    virtual void s3(int);                       // slot 3 (+0xC), called with 1
    virtual bool s4();                          // slot 4 (+0x10)
    virtual void s5();
    virtual void s6(const void* xform);         // slot 6 (+0x18)
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17(int, const void*, int);    // slot 17 (+0x44)
};

// SP::EffectsManager; slot 11 (+0x2C) creates the effect.
struct EffectsManager {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual bool s11(int, int, IEffect**);      // slot 11 (+0x2C), thiscall ret 0xC
};

struct Vector3 {                                // copy ctor copies field by field (movss)
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
extern const Vector3 kZeroOffset;               // 0x0169e308 (x, y, z)
extern const float kOne;                        // 0x01485720
extern const Matrix3 kIdentityRot;              // 0x0169e2e4

// Same layout as SP::cSPTransform (size 0x38): flags, modification count, translation, scale, rotation.
struct cSPTransform {
    uint16_t mFlags;                            // +0
    uint16_t mModificationCount;                // +2
    Vector3 mTranslation;                       // +4
    float mScale;                               // +0x10
    Matrix3 mRotation;                          // +0x14
    cSPTransform() : mFlags(0), mModificationCount(0), mTranslation(kZeroOffset), mScale(kOne)
    {
        mRotation.Assign(kIdentityRot);
    }
};

struct cPlanetModel {
    void BuildSurfaceOrientation(Quaternion* out, const Vec3POD* pos);   // thiscall ret 8
};

struct cSPEditorSpeciesManager {
    void* GetAvatarProfile();                   // 0x004df420, thiscall
};

namespace SP {
    EffectsManager* EffectsManager_Get();       // 0x0067ddd0, returns the global at 0x015fd8e8
    cPlanetModel* PlanetModel();                // 0x00b3d350, returns the global at 0x0167eaf8
}
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);   // 0x0059c190, cdecl
int GetSetting9();                              // 0x00401090, returns the global at 0x015d0c24

extern uint8_t gEffectActive;                   // 0x0169e2cc
extern IEffect* gEffect;                        // 0x0169e2d0

void UpdateEffectPlacement(int source, const Vec3POD* pos)
{
    if (gEffectActive && gEffect) {
        gEffect->s3(1);
        if (gEffect) {
            IEffect* old = gEffect;
            gEffect = 0;
            old->Release();
        }
    }
    if (gEffect && gEffect->s4()) {
        gEffectActive = 0;
        return;
    }

    EffectsManager* mgr = SP::EffectsManager_Get();
    if (gEffect) {
        IEffect* old = gEffect;
        gEffect = 0;
        old->Release();
    }
    if (!mgr->s11(source, 0, &gEffect)) {
        gEffectActive = 0;
        return;
    }

    cSPTransform xf;
    xf.mFlags |= 4;                             // SetOffset(*pos)
    xf.mModificationCount++;
    xf.mTranslation = *(const Vector3*)pos;

    Quaternion q;
    SP::PlanetModel()->BuildSurfaceOrientation(&q, pos);
    Matrix3 tmp;
    xf.mRotation = *Matrix3FromQuaternion(&tmp, &q);   // SetRotation(...)
    xf.mFlags |= 2;
    xf.mModificationCount++;

    cSPEditorSpeciesManager* species = (cSPEditorSpeciesManager*)GetSetting9();
    char* profile = (char*)species->GetAvatarProfile();
    const char* field = profile + 0x4ec;
    gEffect->s17(5, field, 3);
    gEffect->s6(&xf);
    gEffect->s2(0);
    gEffectActive = 0;
}
