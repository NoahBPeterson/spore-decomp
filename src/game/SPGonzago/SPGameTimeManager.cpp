// src/game/SPGonzago/SPGameTimeManager.cpp -- migrated from slice(s) s00ddf990, s00642530 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameTimeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

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
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
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
    void PushMatrix(uint32_t nKey);
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
void cInterfaceState::PushMatrix(uint32_t nKey)
{
    float matrix[9];
    matrix[0] = gInterfaceFrom.mfX;
    matrix[1] = gInterfaceFrom.mfY;
    matrix[2] = gInterfaceFrom.mfZ;
    matrix[3] = gInterfaceValue;
    matrix[4] = gInterfaceBlend;
    matrix[5] = gInterfaceAngle;
    matrix[6] = gInterfaceSpeed;
    matrix[7] = 0.0f;
    matrix[8] = 1.0f;

    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04, (void*)matrix);

    gInterfaceStarted = 0;
    (void)nKey;
}
