// Slice s0106c930 -- SP::cSPUISpace cursor helpers (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct cIntrusiveNode {
    cIntrusiveNode* mpNext;                                  // +0x00
    cIntrusiveNode* mpPrev;                                  // +0x04

    void Init(cIntrusiveNode* self, void* value, void** src, uint32_t dummy); // 0x0106b950
    void* Construct(void** src);
};

} // namespace SP

// @ 0x0106cbd0
void* SP::cIntrusiveNode::Construct(void** src)
{
    bool dummy = false;
    mpNext = this;
    mpPrev = this;
    Init(this, *src, src, *(uint32_t*)&dummy);
    return this;
}
