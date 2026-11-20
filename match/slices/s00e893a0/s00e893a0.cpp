// @ 0x00e893a0
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
// Effect view: finds the object that owns the player's ship, lazily creates a
// visual effect through the effects manager, and pushes the ship's placement
// (position / orientation / scale) to it.  Releases the effect when the object
// is not the player's one.
#include "game/types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VS(o, off)                 (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)             ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)     ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))

struct Vec3_00e893a0 {
    float x, y, z;
};

struct Mat33_00e893a0 {
    float m[9];
};

// Placement record handed to the effect: flags, a revision counter, the
// position, a uniform scale and a 3x3 orientation basis.
struct cEffectPlacement_00e893a0 {
    u16 mFlags;                        // +0x00
    u16 mRevision;                     // +0x02
    Vec3_00e893a0 mPosition;           // +0x04
    float mScale;                      // +0x10
    Mat33_00e893a0 mOrientation;       // +0x14
    cEffectPlacement_00e893a0();       // 0x00434040
};

struct cUFOSimulator_00e893a0 {
    void* GetPlayerShip();             // 0x00ffc320
};

void* GetUFOSimulator();                                        // 0x00ffbe50
void* EffectsManager();                                         // 0x0067ddd0
Mat33_00e893a0* QuatToMatrix(Mat33_00e893a0* out, const float* quat);  // 0x0059c190

struct cEffectView_00e893a0 {
    char  pad00[0x0c];
    void* mpObject;                    // +0x0c
    char  pad10[0x74];
    void* mpEffect;                    // +0x84  refcounted effect
    void Update();
};

void cEffectView_00e893a0::Update()
{
    void* obj = 0;
    if (this->mpObject != 0)
        obj = VC1(void*, this->mpObject, 0xb8, u32, 0x1007ae63u);

    if (obj != 0) {
        void* ship = ((cUFOSimulator_00e893a0*)GetUFOSimulator())->GetPlayerShip();
        void* owner = VC0(void*, obj, 0x84);
        if (ship == owner) {
        if (this->mpEffect == 0) {
            void* mgr = EffectsManager();
            if (this->mpEffect != 0) {
                void* old = this->mpEffect;
                this->mpEffect = 0;
                VC0(void, old, 4);
            }
            if (VC3(char, mgr, 0x2c, u32, 0x7d2bf7a3u, int, 0, void**, &this->mpEffect) != 0)
                VC1(void, this->mpEffect, 8, int, 0);
        }

        if (this->mpEffect != 0) {
            void* effectOwner = VC0(void*, obj, 0x84);
            cEffectPlacement_00e893a0 placement;
            void* spatial = (char*)effectOwner + 0x120;

            const Vec3_00e893a0* pos = VC0(const Vec3_00e893a0*, spatial, 0x2c);
            placement.mPosition = *pos;
            placement.mFlags |= 4;
            placement.mRevision = (u16)(placement.mRevision + 1);

            const float* quat = VC0(const float*, spatial, 0x30);
            Mat33_00e893a0 basis;
            placement.mOrientation = *QuatToMatrix(&basis, quat);

            placement.mRevision = (u16)(placement.mRevision + 1);
            placement.mFlags |= 2;
            placement.mScale = *(float*)(*(char**)((char*)effectOwner + 0x324) + 0x25c);
            placement.mRevision = (u16)(placement.mRevision + 1);

            VC1(void, this->mpEffect, 0x18, void*, &placement);
        }
        return;
        }
    }

    if (this->mpEffect != 0) {
        VC1(void, this->mpEffect, 0xc, int, 0);
        if (this->mpEffect != 0) {
            void* old = this->mpEffect;
            this->mpEffect = 0;
            VC0(void, old, 4);
        }
    }
}
