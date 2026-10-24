// Slice s010554c0, part 2: two space-stage projectile tool strategies that share the
// "press point -> owner position" launch path.
//
//   0x010554c0 SP::cSPDragInputProjectileToolStrategy::OnMouseUp
//   0x01055790 SP::cSPDeepSpaceProjectileToolStrategy::StartTool
//
// Both are virtual overrides: the real `this` (the strategy) arrives in ecx and is
// never read, while the tool object is the first stack argument.  They are modelled
// as member functions so the tool is threaded through explicitly and the stack
// cleanup (ret 4 / ret 0xc) comes out right.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// engine types
// ---------------------------------------------------------------------------

struct Vector3 {
    float x;
    float y;
    float z;
};

// a row-major 3x3 basis; Assign copies one basis over another (0x0041cb40).
struct Matrix3Rows {
    float m[9];
    void Assign(const Matrix3Rows* pOther);   // 0x0041cb40
};

extern Vector3 gZeroVector;                   // 0x016e1b14
extern Vector3 gDefaultPosition;              // 0x016e20fc
extern Matrix3Rows gDefaultBasis;             // 0x016e20d8

// the transform message sent to an effect: two tagged sub-records (a header pair
// and a basis pair), the position, a scale and the row-major basis.
class XformMsg {
public:
    XformMsg()
    {
        mFlags = 0;
        mCount = 0;
        mPosition.x = gDefaultPosition.x;
        mPosition.y = gDefaultPosition.y;
        mPosition.z = gDefaultPosition.z;
        mScale = 1.0f;
        mBasis.Assign(&gDefaultBasis);
    }

    uint16_t mFlags;      // +0x00
    uint16_t mCount;      // +0x02
    Vector3 mPosition;    // +0x04
    float mScale;         // +0x10
    Matrix3Rows mBasis;   // +0x14
};

class cSPNoun;
class cSPAimObject;
class IEffect;
class cEffectsManager;

// one effect instance (slot numbers are byte offsets in the vtable)
class IEffect {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void Release();                                      // +0x04
    virtual void Detach(int32_t nValue);                         // +0x08
    virtual void* Slot0c(void* pOut);                            // +0x0c
    virtual void* Slot10(void* pOut);
    virtual void* Slot14();
    virtual void Send(XformMsg* pMsg);                           // +0x18
};

// the aimer/owner object stored at +0x114 of a space tool
class cSPAimObject {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual Vector3* GetPosition();                              // +0x2c
};

// every noun the star-stage creates (slot numbers are byte offsets)
class cSPNoun {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void Release();                                      // +0x04
    virtual bool Slot08();                                       // +0x08
    virtual void* Slot0c(uint32_t nNounId);                      // +0x0c
};

// the effects manager singleton
class cEffectsManager {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual bool CreateEffect(uint32_t nEffectId, int32_t nFlags,
                              IEffect** ppEffect);               // +0x2c
};

class cGameNounManager {
public:
    cSPNoun* CreateNoun(uint32_t nNounId);                       // 0x00b20c60
};

// the space tool object handed to the strategies
class cSpaceToolData {
public:
    int32_t GetEffectId() const;                                 // 0x0104bf40

    uint8_t mPad000[0x114];       // +0x000
    cSPAimObject* mpToolOwner;    // +0x114
    uint8_t mPad118[0x3c];        // +0x118
    Vector3 mPressedAt;           // +0x154
    Vector3 mReleasedAt;          // +0x160
    IEffect* mpEffect;            // +0x16c
    uint8_t mPad170[0xbc];        // +0x170
    int32_t mEffectId;            // +0x22c
};

// the two strategies whose overrides live here
class cSPDragInputProjectileToolStrategy {
public:
    bool OnMouseUp(cSpaceToolData* pTool);
};

class cSPDeepSpaceProjectileToolStrategy {
public:
    bool StartTool(cSpaceToolData* pTool, const Vector3* pDirection,
                   void* pParam);
};

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

cGameNounManager* __cdecl NounManager();                         // 0x00b3d300
cEffectsManager* __cdecl EffectsManagerPtr();                    // 0x0067ddd0
void __cdecl LaunchProjectile(cSpaceToolData* pTool, void* pProjectile,
                              const Vector3* pOrigin,
                              const Vector3* pDirection);        // 0x010543e0
Matrix3Rows* __cdecl Matrix3FromFacingAndUp(Matrix3Rows* pOut,
                                            const Vector3* pFacing,
                                            const Vector3* pUp);  // 0x0069b440

// ---------------------------------------------------------------------------
// the overrides
// ---------------------------------------------------------------------------

// @ 0x010554c0
bool cSPDragInputProjectileToolStrategy::OnMouseUp(cSpaceToolData* pTool)
{
    bool bResult = false;

    if (pTool->mpEffect != 0) {
        pTool->mpEffect->Slot0c(0);
        if (pTool->mpEffect != 0) {
            IEffect* pOld = pTool->mpEffect;
            pTool->mpEffect = 0;
            pOld->Release();
        }
    }

    if (pTool->mPressedAt.x != gZeroVector.x
        || pTool->mPressedAt.y != gZeroVector.y
        || pTool->mPressedAt.z != gZeroVector.z) {
        cSPNoun* pNoun = NounManager()->CreateNoun(0x24270c5);
        void* pProjectile = (pNoun != 0) ? pNoun->Slot0c(0x24270c4) : 0;

        Vector3* pOwnerPosition = pTool->mpToolOwner->GetPosition();
        Vector3 origin;
        origin.x = pOwnerPosition->x;
        origin.y = pOwnerPosition->y;
        origin.z = pOwnerPosition->z;
        LaunchProjectile(pTool, pProjectile, &origin, &pTool->mPressedAt);

        IEffect* pEffect = 0;
        cEffectsManager* pManager = EffectsManagerPtr();
        if (pEffect != 0) {
            pEffect = 0;
            pEffect->Release();
        }
        if (pManager->CreateEffect(pTool->GetEffectId(), 0, &pEffect)) {
            Vector3 facing;
            facing.x = pTool->mPressedAt.x - origin.x;
            facing.y = pTool->mPressedAt.y - origin.y;
            facing.z = pTool->mPressedAt.z - origin.z;
            float fInv = 1.0f / sqrtf(facing.x * facing.x
                                      + facing.y * facing.y
                                      + facing.z * facing.z);
            facing.x *= fInv;
            facing.y *= fInv;
            facing.z *= fInv;

            XformMsg msg;
            msg.mFlags |= 4;
            msg.mCount += 1;
            msg.mPosition = origin;
            msg.mBasis = *Matrix3FromFacingAndUp(&msg.mBasis, &facing, &origin);
            msg.mFlags |= 2;
            msg.mCount += 1;

            pEffect->Send(&msg);
            pEffect->Detach(0);
        }
        bResult = true;
        if (pEffect != 0)
            pEffect->Release();
    }

    pTool->mPressedAt = gZeroVector;
    pTool->mReleasedAt = gZeroVector;
    return bResult;
}

// @ 0x01055790
bool cSPDeepSpaceProjectileToolStrategy::StartTool(cSpaceToolData* pTool,
                                                   const Vector3* pDirection,
                                                   void* pParam)
{
    bool bResult = false;
    if (pDirection->x != gZeroVector.x || pDirection->y != gZeroVector.y
        || pDirection->z != gZeroVector.z) {
        cSPNoun* pNoun = NounManager()->CreateNoun(0x24270c7);
        void* pProjectile = (pNoun != 0) ? pNoun->Slot0c(0x24270c6) : 0;

        float fInv = 1.0f / sqrtf(pDirection->x * pDirection->x
                                  + pDirection->y * pDirection->y
                                  + pDirection->z * pDirection->z);
        Vector3 velocity;
        velocity.x = pDirection->x * fInv * 2000.0f;
        velocity.y = pDirection->y * fInv * 2000.0f;
        velocity.z = pDirection->z * fInv * 2000.0f;

        LaunchProjectile(pTool, pProjectile, &velocity, pDirection);
        return true;
    }
    return bResult;
}
