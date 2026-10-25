// src/game/SPGonzago/SPDisplayStrategy.cpp -- migrated from slice(s) s0091a680 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPDisplayStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete_array(void* pBlock);                   // 0x00f47380
#include <intrin.h>

// ---- items of slice s0091a680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete_array(void* pBlock);                   // 0x00f47380
struct cWString {
    uint16_t* mpBegin;                  // +0x00
    uint16_t* mpCapacityEnd;            // +0x04
    uint16_t* mpEnd;                    // +0x08
    uint16_t* mpSSOBuffer;              // +0x0c
    void Assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
};
struct cStrNode {
    cStrNode* mpNext;                   // +0x00
    cStrNode* mpPrev;                   // +0x04
    cWString mString;                   // +0x08
};
struct cStrList {
    cStrNode* mpListNext;               // +0x00 (sentinel head)
    cStrNode* mpListPrev;               // +0x04
    void DoClear();                     // 0x0091a750
};
// ---- items of slice s0091a680 end

// @ 0x0091a750
void cStrList::DoClear()
{
    cStrNode* pHead = (cStrNode*)this;
    cStrNode* pNode = mpListNext;
    if (pNode == pHead) return;
    do {
        cStrNode* pCur = pNode;
        int nBytes = (int)((char*)pCur->mString.mpEnd - (char*)pCur->mString.mpBegin);
        pNode = pCur->mpNext;
        nBytes &= ~1;
        if (nBytes > 2 && pCur->mString.mpBegin) operator_delete_array(pCur->mString.mpBegin);
        operator_delete_array(pCur);
    } while (pNode != pHead);
}
