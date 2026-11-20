#include "game/types.h"
#include "EA/Text/FontServer.h"
#include <new>

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_013ebb38[];

extern "C" void* __cdecl AllocateFaceSourceNode(unsigned int size,
    const char* name, int flags, int debugFlags, const char* file, int line);
// AllocateFaceSourceNode: 0x00f473a0.

// The embedded eastl::fixed_list<Font*, 4, 1> of a FaceSource.  It holds
// pointers and counters, so it is 0x58 bytes with word alignment and sits at
// 0x80 of the FaceSource -- FontServer.h's `unsigned char mFontList[0x58]` has
// alignment 1 and would put it at 0x7d.  Retail proves 0x80: the copy reads
// `mov cl,[edx+0x7c]` and then builds the list source as edx+0x80, the
// destination as eax+0x80, before the call at 0x0088e210.
struct FontListCopy {
    unsigned int mStorage[0x16];
    FontListCopy(const FontListCopy&) throw(); // 0x0088e210
};

// Same layout as EA::Text::FontServer::FaceSource with the list member typed,
// so that its implicit copy constructor copies the fixed list by calling the
// list's copy constructor (0x0088e210) -- which is what retail's inlined copy
// of `value_type(value)` does.
struct FaceSourceCopy {
    EA::IO::IStream* mpStream;              // 0x00
    EA::Text::FontType mFontType;           // 0x04
    EA::Text::FontDescription mFontDescription; // 0x08, 0x74 bytes
    unsigned char mnFontIndex;              // 0x7c
    FontListCopy mFontList;                 // 0x80
};

// eastl::ListNode<FaceSource>: two links, then the value.  sizeof is 0xe0, the
// node size of eastl::fixed_node_allocator<0xe0, 4, 4, 0, 1, eastl::allocator>.
struct FaceSourceNode {
    FaceSourceNode* mpNext;                 // 0x00
    FaceSourceNode* mpPrev;                 // 0x04
    FaceSourceCopy mValue;                  // 0x08
};

// The node pool embedded in the list (eastl::fixed_node_allocator).  Its
// free-list head is at +0x00 of the allocator (0x08 of the list) and the node
// size it hands to the tagged EASTL operator new at +0x10 (0x18 of the list):
// retail reads them as `mov ebp,[ecx+8]` and `mov ecx,[ecx+0x18]`.
struct FixedNodeAllocator {
    FaceSourceNode* mpFreeList;             // 0x00
    void* mpBegin;                          // 0x04
    void* mpEnd;                            // 0x08
    void* mpCapacity;                       // 0x0c
    unsigned int mnNodeSize;                // 0x10
    unsigned int mnUnknown;                 // 0x14

    void* allocate();
};

// Reuse a node popped from the pool, otherwise ask the tagged operator new for
// one.  Keeping this a separate inline member matters: with the whole body
// written flat in DoCreateNode cl 15 puts the node in ebx and the copied-from
// FaceSource in ebp (an extra push ebx/pop ebx), while retail keeps the node in
// ebp and the source in edx.  The inlined allocate()/DoAllocateNode() layers
// reproduce that allocation.
inline void* FixedNodeAllocator::allocate() {
    if (mpFreeList) {
        FaceSourceNode* node = mpFreeList;
        mpFreeList = node->mpNext;
        return node;
    }
    return AllocateFaceSourceNode(mnNodeSize, "EASTL", 0, 0,
        reinterpret_cast<const char*>(g_013ebb38), 0xd1);
}

// eastl::list<FaceSource, fixed_node_allocator<...>>: the sentinel node and the
// embedded allocator.  DoCreateNode is the node builder at 0x0088e5a0.
struct FaceSourceList {
    FaceSourceNode* mpNext;                 // 0x00
    FaceSourceNode* mpPrev;                 // 0x04
    FixedNodeAllocator mAllocator;          // 0x08

    FaceSourceNode* DoAllocateNode();
    FaceSourceNode* DoCreateNode(const EA::Text::FontServer::FaceSource& value);
};

inline FaceSourceNode* FaceSourceList::DoAllocateNode() {
    return static_cast<FaceSourceNode*>(mAllocator.allocate());
}

// @ 0x0088e5a0
//
// eastl::list<FaceSource, fixed_node_allocator<...>>::DoCreateNode(value):
// reuse the allocator's free node if there is one, otherwise allocate one
// through the tagged EASTL operator new, then copy-construct the value into
// node->mValue (mpStream and mFontType as dwords, the 0x74-byte description as
// `rep movsd` of 0x1d dwords, mnFontIndex as a byte, and the fixed list by
// calling its copy constructor at 0x0088e210).
FaceSourceNode* FaceSourceList::DoCreateNode(
    const EA::Text::FontServer::FaceSource& value) {
    FaceSourceNode* const node = DoAllocateNode();
    ::new (static_cast<void*>(&node->mValue))
        FaceSourceCopy(reinterpret_cast<const FaceSourceCopy&>(value));
    return node;
}
