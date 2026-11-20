// @ 0x0088c380
#include "game/types.h"
#include <new>

void* __cdecl operator_new(unsigned int size, const char* name, int flags,
                           int debugFlags, const char* file, int line);

// pair<const string16, string16>; its out-of-line copy constructor
// copies the two 16-byte EASTL strings (0x00614990). Declared nothrow:
// the retail build wraps no unwind frame around the construction below.
struct StrPair {
    unsigned int mFirstString[4];
    unsigned int mSecondString[4];
    StrPair(const StrPair& value) throw();
};

struct SubstitutionNode {
    StrPair mValue;
    SubstitutionNode* mpNext;
};

struct FamilySubstitutionTable {
    unsigned char mTableState[0x1c];
    SubstitutionNode* mpHead;
    unsigned char mPoolState[0xc];
    unsigned int mnNodeSize;

    SubstitutionNode* DoAllocateNode(const StrPair& value);
};

// @ 0x0088c380
SubstitutionNode* FamilySubstitutionTable::DoAllocateNode(const StrPair& value) {
    SubstitutionNode* node = mpHead;
    if (node)
        mpHead = *reinterpret_cast<SubstitutionNode**>(node);
    else {
        unsigned int size = mnNodeSize;
        node = static_cast<SubstitutionNode*>(
            operator_new(size, "EASTL", 0, 0, "allocator", 0xd1));
    }
    new (node) StrPair(value);
    node->mpNext = 0;
    return node;
}
