// @ 0x0067af70
#include "game/types.h"
#include "cIHintProcessor.h"

struct HintConditionVector {
    unsigned int* mpBegin;
    unsigned int* mpEnd;
    unsigned int* mpCapacity;
};

class cUIHints {
public:
    uint32_t mPrefix[3];
    cIHintProcessor** mpProcessorsBegin;
    cIHintProcessor** mpProcessorsEnd;

    bool TestNoConditions(const HintConditionVector& conditions);
};

bool cUIHints::TestNoConditions(const HintConditionVector& conditions)
{
    unsigned int count = conditions.mpEnd - conditions.mpBegin;
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int processorCount = mpProcessorsEnd - mpProcessorsBegin;
        unsigned int condition = conditions.mpBegin[i];
        if (processorCount > 0) {
            if (mpProcessorsEnd[-1]->TestCondition(condition))
                return false;
        }
    }
    return true;
}
