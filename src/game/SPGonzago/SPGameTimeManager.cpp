// src/game/SPGonzago/SPGameTimeManager.cpp -- migrated from slice(s) s00ddf990, s00642530 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameTimeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"

// ---- items of slice s00642530 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; uint32_t color; };
struct Tag {};
struct Iter { RBNode* n; Iter() {} Iter(const Iter& o) : n(o.n) {} };
struct UUNode : RBNode { uint32_t key; uint32_t val; };
struct MapUU { uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter DoInsertValueHint(Iter hint, const uint32_t* kv, Tag);
    uint32_t* operator_idx(const uint32_t* k);
};
// ---- items of slice s00642530 end

// ---- items of slice s00ddf990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gInterfaceValue;
extern float gInterfaceBlend;
extern float gInterfaceAngle;
extern float gInterfaceSpeed;
#define nullptr 0
struct cMethodTable {
    void* mSlots[0x40];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (__thiscall*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, void* pArg1, int nArg2) {
        return ((void* (*)(void*, void*, int))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
};
class cInterfaceState {
public:
    cInterfaceState(cDispatchObject* pTarget);
    ~cInterfaceState();
    bool ResetDefaults();
    void PushMatrix(const cSPVector3* pVec);
    void UpdateTransition(unsigned int nElapsed, uint32_t nFlags);
    void UpdateFade(float fDelta);
    void UpdateSequence(int nDelta);
    void UpdateAlpha(int nDelta);
    void BeginSequence(uint8_t bFirst, uint8_t bSecond);
    void ResetSequence();
    void NotifySequence();
    bool IsIdle();

    uint32_t mpVftable;                         // 0x00
    int mnTimer;                                // 0x04
    uint8_t mPad08[0x18];                       // 0x08
    float mfValue20;                            // 0x20
    float mfValue24;                            // 0x24
    float mfValue28;                            // 0x28
    float mfValue2c;                            // 0x2c
    float mfValue30;                            // 0x30
    float mfTolerance;                          // 0x34
    float mfStart38;                            // 0x38
    float mfStart3c;                            // 0x3c
    uint8_t mbFlag40;                           // 0x40
    uint8_t mPad41[0x03];                       // 0x41
    float mfTo44;                               // 0x44
    float mfTo48;                               // 0x48
    float mfTo4c;                               // 0x4c
    float mfFrom50;                             // 0x50
    float mfFrom54;                             // 0x54
};
struct cInterfaceDefaults {
    float mfUnknown00;                          // 0x00
    float mfUnknown04;                          // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};
extern cDispatchObject* gInterfaceNotifier;
extern cInterfaceDefaults gInterfaceFrom;
extern uint8_t gInterfaceStarted;

// The camera controller object (0x015a30b8) and the identity transform it is reset from.
// Its Init is defined here (as it was in the retail translation unit): the caller's code keeps the
// object address in ecx across the call, which cl only does when it can see the callee's body.
struct cCameraCtl {
    int32_t mPad00;                                              // 0x00
    int32_t m04;                                                 // 0x04
    int32_t m08;                                                 // 0x08
    float   m0c;                                                 // 0x0c
    rw::math::fpu::Vector3Template<float, 0> m10;                // 0x10
    float   m1c;                                                 // 0x1c
    float   m20;                                                 // 0x20
    float   m24;                                                 // 0x24
    float   m28;                                                 // 0x28
    float   m2c;                                                 // 0x2c
    float   m30;                                                 // 0x30
    rw::math::fpu::Vector3Template<float, 0> m34;                // 0x34
    rw::math::fpu::Vector3Template<float, 0> m40;                // 0x40
    rw::math::fpu::Vector3Template<float, 0> m4c;                // 0x4c
    void init(void* pArg, const rw::math::fpu::Vector3Template<float, 0>* pVec);
};
extern cCameraCtl gCameraCtl;                                        // 0x015a30b8
extern rw::math::fpu::Vector3Template<float, 0> gZeroTranslation;    // 0x016a10cc
extern rw::math::fpu::Matrix33Template<float, 0> gIdentityRotation;  // 0x016a10e0
extern float gCamStep30;                                             // 0x015a308c
extern float gCamStep1c;                                             // 0x015a3090
extern float gCamValue24;                                            // 0x015a3094
extern rw::math::fpu::Vector3Template<float, 0> gCamTranslation;     // 0x015a3048

// @ 0x00dde2b0
void cCameraCtl::init(void* pArg, const rw::math::fpu::Vector3Template<float, 0>* pVec)
{
    m30 = gCamStep30;
    m1c = gCamStep1c;
    m10 = *pVec;
    m24 = gCamValue24;
    m2c = 100.0f;
    m40 = *pVec;
    m34 = gCamTranslation;
    m4c = m34;
    m04 = 0;
    m08 = 500;
    *(int32_t*)&m0c = 0;
    (void)pArg;
}

// The 0x38-byte transform handed to the notifier: RenderWare's cTransform layout.  Its rotation
// assignment is out of line (Matrix3::Assign, 0x0041cb40), so the type declares it without a body.
struct cXformMatrix : public rw::math::fpu::Matrix33Template<float, 0> {
    cXformMatrix& operator=(const rw::math::fpu::Matrix33Template<float, 0>&);
};
struct cXform {
    uint16_t mFlags;                                             // 0x00
    uint16_t mModificationCount;                                 // 0x02
    rw::math::fpu::Vector3Template<float, 0> mTranslation;       // 0x04
    float mScale;                                                // 0x10
    cXformMatrix mRotation;                                      // 0x14
};
typedef char sizeof_check_cXform[(sizeof(cXform) == 0x38) ? 1 : -1];
// ---- items of slice s00ddf990 end

// @ 0x00643a40
uint32_t* MapUU::operator_idx(const uint32_t* k)
{
    RBNode* pNode = anchor.parent;
    RBNode* pEnd = &anchor;
    while (pNode) {
        if (!(((UUNode*)pNode)->key < *k)) { pEnd = pNode; pNode = pNode->left; }
        else pNode = pNode->right;
    }
    if (pEnd == &anchor || *k < ((UUNode*)pEnd)->key) {
        uint32_t kv[2];
        kv[0] = *k; kv[1] = 0;
        Iter hi; hi.n = pEnd;
        Iter it = DoInsertValueHint(hi, kv, Tag());
        pEnd = it.n;
    }
    return &((UUNode*)pEnd)->val;
}

// @ 0x00ddfb50
void cInterfaceState::PushMatrix(const cSPVector3* pVec)
{
    cXform xform;
    xform.mFlags = 0;
    xform.mModificationCount = 0;
    xform.mTranslation.x = gZeroTranslation.x;
    xform.mTranslation.y = gZeroTranslation.y;
    xform.mTranslation.z = gZeroTranslation.z;
    xform.mScale = 1.0f;
    xform.mRotation = gIdentityRotation;

    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04, (void*)&xform);

    gCameraCtl.init(&xform.mTranslation, pVec);
    gInterfaceNotifier = (cDispatchObject*)&gCameraCtl;
}
