// Slice s00bc1690: introsort recursion (0x00bc1940) over 12-byte pair<unsigned, cWorld> items,
// ordered by key. Median-of-three pivot, Hoare-style partition, depth limit that falls back to
// heap sort (0x00bc1830). The 28-byte rbtree argument is passed by value and destroyed at the end.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

struct Item12 {                       // eastl::pair<const unsigned, cSPUILayoutManager::cWorld>
    uint32_t key;
    uint32_t v1;
    uint32_t v2;
};

// 28-byte rbtree passed by value. Copy constructor 0x00AF0D40 (thiscall, ret 4);
// destructor (DoNukeSubtree) 0x009A9600.
class TreeArg {
public:
    TreeArg(const TreeArg& other);
    ~TreeArg();
    uint32_t raw[7];
};

Item12* Median3(Item12* a, Item12* b, Item12* c);                          // 0x00BBFBF0
Item12* Partition(Item12* first, Item12* last, Item12 pivot);               // 0x00BBFCE0
void HeapFallback(Item12* first, Item12* middle, Item12* last);             // 0x00BC1830

// @ 0x00bc1940
void __cdecl QuickSortImpl(Item12* first, Item12* last, int depth, TreeArg tree)
{
    while ((last - first) > 28 && depth > 0) {
        Item12* mid = first + (last - first) / 2;
        Item12 pivot = *Median3(first, mid, last - 1);
        Item12* cut = Partition(first, last, pivot);
        --depth;
        QuickSortImpl(cut, last, depth, tree);
        last = cut;
    }
    if (depth == 0)
        HeapFallback(first, last, last);
}
