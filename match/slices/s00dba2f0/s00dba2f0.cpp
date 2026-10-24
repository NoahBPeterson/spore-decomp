// Slice s00dba2f0 -- cHealOther tagged assignment (partial).
// Module flags: /O2 /MD /Gy /TP /arch=SSE /fp:fast
#include "types.h"

struct cHealOtherData {
    void* mpVtable;                                          // +0x00
    uint32_t mPad04;                                         // +0x04

    void Copy(const cHealOtherData* src);                    // 0x00db97f0
    cHealOtherData& operator=(const cHealOtherData& rhs);    // 0x00dba120
};

struct cHealOther {
    int32_t        mTag;                                     // +0x00
    cHealOtherData mData;                                    // +0x04

    cHealOther* Assign(const cHealOther* other);
};

static inline bool TagIsNegative(int32_t tag)
{
    return ((uint32_t)tag >> 31) & 1;
}

// @ 0x00dba580
cHealOther* cHealOther::Assign(const cHealOther* other)
{
    bool argNeg = TagIsNegative(other->mTag);
    if (argNeg) {
        if (!TagIsNegative(mTag)) {
            ((void (__thiscall*)(cHealOtherData*, int))((void**)mData.mpVtable)[0])(&mData, 0);
            mTag = other->mTag;
            return this;
        }
    }
    if (!argNeg) {
        if (TagIsNegative(mTag))
            mData.Copy(&other->mData);
        else
            mData = other->mData;
    }
    mTag = other->mTag;
    return this;
}
