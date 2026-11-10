// Slice s0088c760: intrusive-list splice used by the manager containers.  For every
// node in [first, last) a fresh 0xc-byte node is popped from the pool (the object is an
// EASTL list header: sentinel at +0x0/+0x4, free-list head at +0x8, allocator at +0x18),
// its payload (+0x8) is copied from the source node, and it is linked in front of the
// sentinel.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// Tagged allocator: (allocatorProxy, name, 0, 0, sourceFile, line); returns 0xc bytes.
extern "C" void* __cdecl EAAllocate(void* alloc, const char* name, int b, int c, const char* file, int line); // 0x00f473a0
extern char kAllocFile_13ebb38[];   // 0x013ebb38 ".../EASTL/allocator.h"
extern char kAllocName_13f2150[];   // 0x013f2150 allocation name

struct ValC760 { int x; };              // 4-byte payload

struct NodeC760 {
    NodeC760* next;     // +0x0
    NodeC760* owner;    // +0x4
    ValC760   value;    // +0x8  payload copied from the source node
    int       padc;     // +0xc
};

// The sentinel the new nodes are linked in front of has its own (2-pointer) type.
struct ListNode {
    ListNode* next;     // +0x0
    ListNode* owner;    // +0x4
};

struct ListC760 {
    ListNode  head;      // +0x0 sentinel
    NodeC760* pool;      // +0x8 free-list head
    char      pad0c[0xc];
    void*     alloc;     // +0x18 allocator proxy passed to EAAllocate

    void splice(NodeC760* first, NodeC760* last, NodeC760* end, int);  // @ 0x0088c760
};

// @ 0x0088c760
void ListC760::splice(NodeC760* first, NodeC760* last, NodeC760*, int)
{
    for (; first != last; first = first->next) {
        ValC760* slot = &first->value;
        NodeC760* n;
        if (pool) {
            n = pool;
            pool = pool->next;
        } else {
            n = (NodeC760*)EAAllocate(alloc, kAllocName_13f2150, 0, 0, kAllocFile_13ebb38, 0xd1);
        }
        ValC760* payload = &n->value;
        if (payload)
            *payload = *slot;
        n->next = (NodeC760*)&head;
        n->owner = (NodeC760*)head.owner;
        head.owner->next = (ListNode*)n;
        head.owner = (ListNode*)n;
    }
}
