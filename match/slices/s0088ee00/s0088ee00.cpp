// @ 0x0088ee00
#include "game/types.h"
#include "EA/Text/FontServer.h"
#include "eastl/string.h"
#include <new>

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_013ebb38[];

extern "C" void* __cdecl AllocateFaceNode(unsigned int size, const char* name,
    int flags, int debugFlags, const char* file, int line); // 0x00f473a0

// Retail map values precede the hash-chain link in each node.
struct FaceMapValue {
    const eastl::string16 first;
    EA::Text::FontServer::Face second;
    FaceMapValue(const FaceMapValue&) throw(); // 0x0088ed20
};
struct FaceMapNode {
    FaceMapValue mValue;
    FaceMapNode* mpNext;
};

struct FaceMapTable {
    unsigned char mTableState[0x1c];
    FaceMapNode* mpHead;
    unsigned char mPoolState[0xc];
    unsigned int mnNodeSize;

    FaceMapNode* DoCreateNode(const FaceMapValue& value);
};

// @ 0x0088ee00
FaceMapNode* FaceMapTable::DoCreateNode(const FaceMapValue& value) {
    FaceMapNode* node = mpHead;
    if (node)
        mpHead = *reinterpret_cast<FaceMapNode**>(node);
    else {
        unsigned int size = mnNodeSize;
        node = static_cast<FaceMapNode*>(AllocateFaceNode(
            size, "EASTL", 0, 0, reinterpret_cast<const char*>(g_013ebb38), 0xd1));
    }
    new (node) FaceMapValue(value);
    node->mpNext = 0;
    return node;
}
