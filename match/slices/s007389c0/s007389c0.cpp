// Slice s007389c0 — model/mesh container helpers in the model region of SporeApp.exe.
//
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS- (no frame pointer; 0x738e50 has no cookie).

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

extern "C" void EA_dealloc(void* p);        // 0x00F47380

// ---------------------------------------------------------------------------
// A 20-byte vector-like member (begin/end/capacity + 8-byte allocator).  The
// copy-assign helper for the 0x00738E50 class operates on members at stride
// 0x14, so each member is represented as an opaque 20-byte subobject with an
// out-of-line __thiscall operator=.
// ---------------------------------------------------------------------------
struct SubVec {
    void* begin;
    void* end;
    void* cap;
    int alloc[2];
    SubVec& operator=(const SubVec& x);
};

struct FourVecs {
    char pad0[8];       // +0x00: refcount/vtable + padding
    SubVec m8;          // +0x08
    SubVec m1c;         // +0x1c
    SubVec m30;         // +0x30
    SubVec m44;         // +0x44
    FourVecs& operator=(const FourVecs& x);
};

// @ 0x00738E50 — FourVecs::operator=(const FourVecs&)
FourVecs& FourVecs::operator=(const FourVecs& x)
{
    this->m8  = x.m8;
    this->m1c = x.m1c;
    this->m30 = x.m30;
    this->m44 = x.m44;
    return *this;
}

// ---------------------------------------------------------------------------
// eastl::vector<Element, alloc>::operator= for a 0x8c-byte element.
// ---------------------------------------------------------------------------
extern "C" void* CopyRange(void* first, void* last, void* dest);   // 0x0071F410
extern "C" void  UninitCopyOut(void* out, void* dest, void* srcFirst, void* srcLast); // 0x0071F200

struct VecB {
    char* begin;        // +0
    char* end;          // +4
    char* capacity;     // +8
    VecB& operator=(const VecB& x);
    void* DoAllocCopy(int n, void* srcBegin, void* srcEnd);   // 0x00738CB0
    void  DestroyRange(void* first, void* last);              // 0x00717930
};

// @ 0x00738D10 — VecB::operator=(const VecB&)
VecB& VecB::operator=(const VecB& x)
{
    if (&x != this) {
        char* const xb = x.begin;
        char* const xe = x.end;
        const uint32_t n = (uint32_t)((xe - xb) / 0x8c);
        if (n > (uint32_t)((capacity - begin) / 0x8c)) {
            char* pNew = (char*)DoAllocCopy((int)n, xb, xe);
            DestroyRange(begin, end);
            if (begin && *(int*)(begin - 4))
                EA_dealloc(begin);
            begin = pNew;
            capacity = pNew + n * 0x8c;
        } else if ((uint32_t)((end - begin) / 0x8c) < n) {
            CopyRange(xb, xb + ((end - begin) / 0x8c) * 0x8c, begin);
            UninitCopyOut(0, 0, 0, 0);
        } else {
            void* p = CopyRange(xb, xe, begin);
            DestroyRange(p, end);
        }
        end = begin + n * 0x8c;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x007389C0 — scatter/accumulate a group's per-vertex data (large loop).
// ---------------------------------------------------------------------------
struct GroupOuter;
void ScatterGroup(GroupOuter* self, int count)
{
    (void)self; (void)count;
    // Large float-accumulation loop; skeleton kept for completeness.
}

// ---------------------------------------------------------------------------
// @ 0x00738E90 — normalise vertex batches / merge two groups (large loop).
// ---------------------------------------------------------------------------
void NormalizeGroup(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
    // Large x87 + SSE normalisation loop; skeleton kept for completeness.
}
