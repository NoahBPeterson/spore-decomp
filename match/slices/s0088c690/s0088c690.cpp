// Slice s0088c690 -- eastl red-black tree RBTree::DoCreateNode(const RBValue*):
// pop a node from the free list (or allocate mNodeSize bytes), then copy-construct the value in place.
// Local stand-in layout (retail offsets).
// Flags: /O2 /MT /GS- /GR- /TP /arch:SSE
#include "types.h"

inline void* __cdecl operator new(unsigned int, void* p) { return p; }

struct ICoreAllocator {
    virtual void* Slot0();      // +0x00
    virtual void* Slot4();      // +0x04
    virtual void* AddRef();     // +0x08
};

// The value the tree copies in: a ref-counted pointer, whose copy ctor AddRefs the pointee.
struct AutoRefCount {
    ICoreAllocator* mpPtr;      // +0x00

    AutoRefCount(const AutoRefCount&);
};

struct RBValue {
    AutoRefCount mRef;          // +0x00

    RBValue(const RBValue& x);
};

struct RBNode {
    RBNode*       mpRight;      // +0x00  free-list next / right child
    RBNode*       mpLeft;       // +0x04
    RBNode*       mpParent;     // +0x08
    unsigned char mColor;       // +0x0c
    unsigned char mPad[3];
    RBValue       mValue;       // +0x10
};

void* EAOperatorNew(unsigned int size, const char* name, int flags, int alignment, const char* file, int line); // 0x00f473a0

struct RBTree {
    unsigned char mPad0[0x18];  // +0x00
    RBNode*       mpFreeList;   // +0x18
    unsigned char mPad1[0x0c];  // +0x1c
    unsigned int  mNodeSize;    // +0x28

    __declspec(noinline) RBNode* DoCreateNode(const RBValue*);
};

// @ 0x0088c690
RBNode* RBTree::DoCreateNode(const RBValue* pValue)
{
    RBNode* node = mpFreeList;
    if (node != 0) {
        mpFreeList = node->mpRight;
    } else {
        node = (RBNode*)EAOperatorNew(mNodeSize, "EASTL", 0, 0, "allocator", 0xd1);
    }
    new (&node->mValue) RBValue(*pValue);
    return node;
}

AutoRefCount::AutoRefCount(const AutoRefCount& x) : mpPtr(x.mpPtr)
{
    ICoreAllocator* p = mpPtr;
    if (p)
        p->AddRef();
}

RBValue::RBValue(const RBValue& x) : mRef(x.mRef)
{
}
