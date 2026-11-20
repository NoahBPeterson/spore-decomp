#include "game/types.h"

struct HintConditionVector {
    unsigned int* mpBegin;
    unsigned int* mpEnd;
    unsigned int* mpCapacity;
    unsigned int mAllocator[2];

    unsigned int size() const { return mpEnd - mpBegin; }
};

struct cHint {
    void* mpVtable;
    int mRefCount;
    unsigned int mTriggerID;
    HintConditionVector mPresentList;
    HintConditionVector mAbsentList;
    HintConditionVector mCancelList;
};

class cUIHints {
public:
    bool TestAllConditions(const HintConditionVector& conditions);
    bool TestNoConditions(const HintConditionVector& conditions);
    bool CheckConditions(cHint* pHint);
};

// @ 0x0067afd0
bool cUIHints::CheckConditions(cHint* pHint)
{
    if (TestAllConditions(pHint->mPresentList) &&
        (pHint->mAbsentList.size() == 0 || TestNoConditions(pHint->mAbsentList)) &&
        (pHint->mCancelList.size() == 0 || !TestAllConditions(pHint->mCancelList)))
        return true;
    return false;
}
