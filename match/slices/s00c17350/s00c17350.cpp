#include "types.h"

// ---------------------------------------------------------------------------
// Named views over the retail objects this slice touches.
// ---------------------------------------------------------------------------

struct cEffectSlot {
    virtual void v00();                // slot +0x00
    virtual void v04();                // slot +0x04
    virtual void v08();                // slot +0x08
    virtual void v0c();                // slot +0x0c
    virtual bool IsActive();           // slot +0x10
};

struct cEffectEntry {
    uint8_t      mPad000[0x8c];        // +0x000
    cEffectSlot* mEffect;              // +0x08c
};

struct cBodyAnim {
    // 0x009cab60  resolve the effect entry for a key
    cEffectEntry* FindEffect(uint32_t key);
};

struct cCreatureBody {
    uint8_t     mPad000[0x17c];        // +0x000
    cBodyAnim*  mAnim;                 // +0x17c
};

// SP::cSPCreatureBase
struct cSPCreatureBase {
    uint8_t        mPad0000[0xb20];    // +0x0000
    void*          mCreature;          // +0x0b20
    uint8_t        mPad0b24[0xb54 - 0xb24]; // +0x0b24
    cCreatureBody* mBody;              // +0x0b54

    uint32_t MakeBodyEffect(uint32_t part, uint32_t a, uint32_t b);  // 0x00c14f70
    void     BodyEffectNotify(uint32_t a, uint32_t b);               // 0x00c15150

    // 0x00c17580
    uint32_t GetBodyPartIndex(uint32_t kind, uint32_t index);
    // 0x00c17c80
    uint32_t CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b);
    // 0x00c17cc0
    uint32_t CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                     uint32_t b);
    // 0x00c17d60
    uint32_t CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                      uint32_t b);
};

// 0x00c17420  enumerate the body parts of `kind` into `out` (up to `max`)
uint32_t QueryCreatureBodyParts(cSPCreatureBase* self, uint32_t kind, uint32_t* out, uint32_t max);

// ---------------------------------------------------------------------------
// 0x00c17580  index into the enumerated body-part list
// ---------------------------------------------------------------------------
// @ 0x00c17580
uint32_t cSPCreatureBase::GetBodyPartIndex(uint32_t kind, uint32_t index)
{
    uint32_t result = 0xffffffff;
    uint32_t parts[255];
    uint32_t count = QueryCreatureBodyParts(this, kind, parts, 255);
    if (index < count) {
        result = parts[index];
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00c17c80  create a body effect for the first body part of `kind`
// ---------------------------------------------------------------------------
// @ 0x00c17c80
uint32_t cSPCreatureBase::CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b)
{
    uint32_t part;
    if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
        return MakeBodyEffect(part, a, b);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c17cc0  checked body-effect creation (guards on a live effect)
// ---------------------------------------------------------------------------
// @ 0x00c17cc0
uint32_t cSPCreatureBase::CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a,
                                                  uint32_t e, uint32_t b)
{
    if (flag != 0) {
        if (mBody != 0) {
            cEffectEntry* found = mBody->mAnim->FindEffect(e);
            if (found != 0) {
                cEffectSlot* eff = found->mEffect;
                if (eff != 0 && eff->IsActive()) {
                    return 0;
                }
            }
        }
        BodyEffectNotify(e, 1);
        uint32_t part;
        if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
            return MakeBodyEffect(part, a, e);
        }
        return 0;
    }
    BodyEffectNotify(e, b);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c17d60  checked body-effect creation (no part query)
// ---------------------------------------------------------------------------
// @ 0x00c17d60
uint32_t cSPCreatureBase::CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a,
                                                   uint32_t e, uint32_t b)
{
    if (flag != 0) {
        if (mBody != 0) {
            cEffectEntry* found = mBody->mAnim->FindEffect(e);
            if (found != 0) {
                cEffectSlot* eff = found->mEffect;
                if (eff != 0 && eff->IsActive()) {
                    return 0;
                }
            }
        }
        BodyEffectNotify(e, 1);
        return MakeBodyEffect(kind, a, e);
    }
    BodyEffectNotify(e, b);
    return 0;
}
