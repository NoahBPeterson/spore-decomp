// Slice s004c2100: EASTL heap primitives (make_heap/adjust_heap) for the 0x18-byte
// editor value type, cSPEditorSkinManager::AsInterface, and wide-string/refcount helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

// ===========================================================================
// 0x18-byte value type used by the heap helpers.
// ===========================================================================
struct Elem18 {
    uint32_t v[6];
    bool operator<(const Elem18& x) const { return v[0] < x.v[0]; }
};

namespace eastl {

struct Compare18 {
    bool operator()(const Elem18& a, const Elem18& b) const { return a.v[0] < b.v[0]; }
};

// @ 0x004c2520  eastl::adjust_heap<It,Distance,T,Compare>
inline void promote_heap(Elem18* first, int topPosition, int position, Elem18 value, Compare18 compare)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

void adjust_heap(Elem18* first, int topPosition, int heapSize, int position, Elem18 value, Compare18 compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    eastl::promote_heap(first, topPosition, position, value, compare);
}

// @ 0x004c2460  eastl::make_heap<It,Compare>
void make_heap(Elem18* first, Elem18* last, Compare18 compare)
{
    const int n = (int)(last - first);
    if (n >= 2) {
        int parent = ((n - 2) >> 1) + 1;
        do {
            --parent;
            const Elem18 temp(*(first + parent));
            eastl::adjust_heap(first, parent, n, parent, temp, compare);
        } while (parent != 0);
    }
}

} // namespace eastl

// ===========================================================================
// @ 0x004c3030  SP::cSPEditorSkinManager::AsInterface
// ===========================================================================
namespace SP {
class cSPEditorSkinManager {
public:
    void* AsInterface(uint32_t id);
};
void* cSPEditorSkinManager::AsInterface(uint32_t id)
{
    switch (id) {
    case 0xcfeb4c03:
        return this;
    case 0xee3f516e:
        return this;
    }
    return 0;
}
} // namespace SP

// ===========================================================================
// Wide fixed_string<wchar_t,256> helpers.
// ===========================================================================
namespace eastl {

struct WideFixedAlloc {
    uint32_t mOverflow;
    void* mpPoolBegin;
};

struct WideFixedStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    WideFixedAlloc mAllocator;

    void EnsureCapacity(uint32_t n);      // 0x004c26d0
    void SetCapacity(uint32_t n);         // 0x004c29c0
    void SwapHeap(WideFixedStr* other);   // 0x004c2ad0
};

// @ 0x004c26d0  grow helper used by append()
void WideFixedStr::EnsureCapacity(uint32_t n)
{
    uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
    uint32_t* p = (n < nSize) ? &nSize : &n;
    n = *p + 1;
    if ((uint32_t)(mpCapacity - mpBegin) < n)
        SetCapacity(n);
}

} // namespace eastl

// ===========================================================================
// Remaining editor-skin / wide-string helpers (PARTIAL skeletons).
// ===========================================================================

// @ 0x004c2100  vector<T> swap-with-fallback (3-pointer swap when allocators match)
void VectorSwap4(uint32_t* a, uint32_t* b)
{
    if (&a[3] == &b[3]) {
        uint32_t t0 = a[0]; a[0] = b[0]; b[0] = t0;
        uint32_t t1 = a[1]; a[1] = b[1]; b[1] = t1;
        uint32_t t2 = a[2]; a[2] = b[2]; b[2] = t2;
    } else {
        // PARTIAL: element-wise copy through a temporary buffer.
    }
}

// @ 0x004c2740  PARTIAL: vector<T>::operator= element-wise assignment
void VectorAssign4(uint32_t* self, uint32_t* other)
{
    (void)self; (void)other;
}

// @ 0x004c29c0  PARTIAL: basic_string<wchar_t,256>::set_capacity
void eastl_set_capacity(eastl::WideFixedStr* self, uint32_t n)
{
    (void)self; (void)n;
}

// @ 0x004c2ad0  PARTIAL: wide-buffer heap swap
void WideFixedStr_SwapHeap(eastl::WideFixedStr* self, eastl::WideFixedStr* other)
{
    (void)self; (void)other;
}

// @ 0x004c2bc0  PARTIAL: SP::cSPEditorSkinManager::cSPEditorSkinManager()
void cSPEditorSkinManager_ctor(void* self)
{
    (void)self;
}

// @ 0x004c2eb0  PARTIAL: SP::cSPEditorSkinManager::~cSPEditorSkinManager()
void cSPEditorSkinManager_dtor(void* self)
{
    (void)self;
}

// @ 0x004c3070  PARTIAL: editor skin raster setup (create_ui_raster)
void create_ui_raster(void* self, void* a, void* b, void* c)
{
    (void)self; (void)a; (void)b; (void)c;
}

#pragma pack(pop)
