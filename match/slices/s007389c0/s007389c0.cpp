// Slice s007389c0 — model/mesh container helpers in the model region of SporeApp.exe.
//
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS- (no frame pointer; 0x738e50 has no cookie).

#include <math.h>

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
extern "C" void* UninitCopyOut(void* out, void* dest, void* srcFirst, void* srcLast, void* arg); // 0x0071F200

struct VecB {
    char* begin;        // +0
    char* end;          // +4
    char* capacity;     // +8
    VecB& assign(const VecB& x);
    void* DoAllocCopy(int n, void* srcBegin, void* srcEnd);   // 0x00738CB0
    void  DestroyRange(void* first, void* last);              // 0x00717930
};

// @ 0x00738D10 — VecB::assign(const VecB&)
// eastl::vector<0x8c-byte element>::operator= : grow to a fresh block when the
// capacity is short, else copy as many elements as fit and fill/trim the rest.
VecB& VecB::assign(const VecB& x)
{
    if (&x == this)
        return *this;

    char* const xb = x.begin;
    char* const xe = x.end;
    const unsigned n = (unsigned)((xe - xb) / 0x8c);
    const unsigned have = (unsigned)((capacity - begin) / 0x8c);
    if (have < n) {
        char* pNew = (char*)DoAllocCopy((int)n, xb, xe);
        DestroyRange(begin, end);
        if (begin != 0 && *(int*)(begin - 4) != 0)
            EA_dealloc(begin);
        begin = pNew;
        capacity = pNew + n * 0x8c;
    } else {
        const unsigned cur = (unsigned)((end - begin) / 0x8c);
        if (cur < n) {
            // Copy the overlap, then uninitialised-copy the remaining source tail.
            CopyRange(xb, xb + cur * 0x8c, begin);
            UninitCopyOut((void*)&x, ((end - begin) / 0x8c) * 0x8c + xb, xe, end, (void*)&x);
        } else {
            char* p = (char*)CopyRange(xb, xe, begin);
            DestroyRange(p, end);
        }
    }
    end = begin + n * 0x8c;
    return *this;
}

// ---------------------------------------------------------------------------
// SEH scope helpers for the group scatter below.
// ---------------------------------------------------------------------------
extern "C" void  BuildGroupIndices(void* self, void* vec, int a, int b, int c); // 0x0071ec20
extern "C" void  ResetGroupStream(void* self, int n, void* begin);               // 0x00738610
extern "C" void  InitStream15(void* stream);                                     // 0x007200f0
extern "C" void  EA_dealloc(void* p);                                            // 0x00F47380

// Per-(group, stream) header embedded at +0x10 of each 0x20-byte group entry.
struct GroupStream {
    int      count;      // +0x00  element count
    float*   data;       // +0x04  element storage
    short    span;       // +0x08  written as count*4
    unsigned short stride;// +0x0a  element stride in bytes
    void*    ref;        // +0x0c  refcounted binding (virtual dtor at slot 1)
};

// One 0x20-byte entry of the group array at self+8.
struct GroupEntry {
    int         pad00;      // +0x00
    int         pad04;      // +0x04
    int         total;      // +0x08  accumulated element total
    int         pad0c;      // +0x0c
    GroupStream stream;     // +0x10
};

struct GroupOuter {
    char        pad00[8];   // +0x00
    GroupEntry* entries;    // +0x08
};

// Small EASTL vector<int> used as the work list; mpBegin carries a 4-byte
// allocator header immediately before it.
struct IntVec {
    int* begin;             // +0x00
    int* end;               // +0x04
    int* capacity;          // +0x08
    void release();
};

// IntVec::release frees the work-list storage via the allocator header.
void IntVec::release()
{
    if (begin != 0 && begin[-1] != 0)
        EA_dealloc(begin);
}

// ---------------------------------------------------------------------------
// @ 0x007389C0 — accumulate one group's per-vertex data into a target stream.
//
// The whole body runs under an SEH scope; the local `idx` vector<int> is filled
// by FUN_0071ec20 and freed through the EASTL allocator guard on every exit.
// ---------------------------------------------------------------------------
void ScatterGroup(GroupOuter* self, int count)
{
    IntVec idx;
    idx.begin = 0;
    idx.end = 0;
    idx.capacity = 0;

    BuildGroupIndices(self, &idx, 10, 0, 0xe);

    if (count < 2) {
        ResetGroupStream(self, (int)(idx.end - idx.begin), idx.begin);
        idx.release();
        return;
    }

    const int nIdx = (int)(idx.end - idx.begin);
    for (int gi = 0; gi < nIdx; ++gi) {
        GroupEntry* entry = (GroupEntry*)((char*)self->entries + idx.begin[gi] * 0x20);
        const int total = entry->total;
        GroupStream* st = &entry->stream;

        if ((unsigned)(total - 1) >= 4 || count >= total)
            continue;

        // Release the previous binding, resize the stream, then scatter.
        void* ref = st->ref;
        if (ref != 0)
            (*(void (__thiscall**)(void*))*(void**)ref)(ref);

        st->span = (short)(count * 4);
        InitStream15(st);

        const int rows = st->count;
        for (int r = 0; r < rows; ++r) {
            if (count >= total)
                continue;

            const unsigned short stride = st->stride;
            float* src = (float*)((char*)st->data + r * stride);
            int k = count;
            for (; k < total; ++k) {
                float* dst = (float*)((char*)st->data + r * stride + k * 4);
                dst[-1] += src[k - count];
            }
        }

        entry->total = total + (count - total);

        if (ref != 0)
            (*(void (__thiscall**)(void*, int))(*(void***)ref)[1])(ref, 1);
    }

    idx.release();
}

// Normalise one stream's 3-float vectors in place (used twice below).
static void NormalizeStream(char* entriesBase, int sel)
{
    if (sel < 0)
        return;
    // entriesBase points at a selected entry's +0x10 stream header.
    int*   hdr    = (int*)(entriesBase + sel * 0x20);
    unsigned n    = (unsigned)hdr[0];
    unsigned short stride = *(unsigned short*)((char*)hdr + 0xa);
    char*  data   = (char*)hdr[1];
    for (unsigned i = 0; i < n; ++i) {
        float* p = (float*)(data + i * stride);
        float  x = p[0], y = p[1], z = p[2];
        float  s = 1.0f / sqrtf(x * x + y * y + z * z + 1e-08f);
        p[0] = x * s;
        p[1] = y * s;
        p[2] = z * s;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00738E90 — normalise vertex batches and merge two model groups.
// ---------------------------------------------------------------------------
extern "C" void  SelectStreams(void* model, int count, int* out0, const int* a,
                               int b, const int* c, int d);      // 0x0071ded0
extern "C" void  ClearStream(void* stream);                      // 0x007200f0
extern "C" void  MergeGroup(void* model, void* group, int s0, int s1,
                            int s2, int type, void* a, void* b); // 0x00732410
extern "C" void  VecAssign735dd0(void* dst, void* src);          // 0x00735dd0
extern "C" void  VecAssign738d10(void* dst, void* src);          // 0x00738d10
extern "C" void  VecAssign715120(void* dst, void* src);          // 0x00715120
extern "C" void  VecAssign735260(void* dst, void* src);          // 0x00735260

// A 0x8c-byte element of the +0x1c vector in the group: a short-index list.
struct IndexList {
    char    pad00[0x14];    // +0x00
    int*    begin;          // +0x14  list of 4-byte index slots (low 16 bits used)
    int*    end;            // +0x18
};

// The group object passed as param_4.  +0x08/+0x0c are a 0x14-byte-stride
// vector's begin/end (also the primary "entries" pointer used below); +0x1c/+0x20
// are a second vector of 0x8c-byte index lists.
struct GroupIn {
    char       pad00[8];    // +0x00
    void*      begin08;     // +0x08  also the entries array base
    void*      end0c;       // +0x0c
    char       pad10[0x0c]; // +0x10
    IndexList* lists;       // +0x1c  vector of 0x8c-byte IndexList
    IndexList* listsEnd;    // +0x20
};

void NormalizeGroup(void* param_1, void* param_2, void* param_3, GroupIn* param_4)
{
    // selectStreams fills a 7-int descriptor block:
    //   sel[0..2] = stream ids, sel[3..5] = their companion ids, sel[6] = shared.
    int sel[7];
    SelectStreams(param_3, 7, &sel[0], (const int*)0x140d4fc, 0, (const int*)0x140d518, 0);

    GroupIn* g = param_4;

    // The copy/merge block runs only when the group's two header pointers match.
    if (g->begin08 == g->end0c) {
        // Re-seat the four 0x14-byte vectors of param_4 from param_3.
        VecAssign735dd0((char*)g + 8, (char*)param_3 + 8);
        VecAssign738d10((char*)g + 0x1c, (char*)param_3 + 0x1c);
        VecAssign715120((char*)g + 0x30, (char*)param_3 + 0x30);
        VecAssign735260((char*)g + 0x44, (char*)param_3 + 0x44);

        // Drop index entries whose entry type is one of the geometry primitives.
        void*  entriesV = g->begin08;
        int*   entries  = (int*)entriesV;
        const int count = (int)(((char*)g->listsEnd - (char*)g->lists) / 0x8c);
        for (int li = 0; li < count; ++li) {
            IndexList* list = (IndexList*)((char*)g->lists + li * 0x8c);
            int* p = list->begin;
            while (p != list->end) {
                const int type = entries[*(short*)p * 8];   // entry + 0x00, stride 0x20
                if (type == 0xb || type == 0xc || type == 0xd ||
                    type == 0xe || type == 0x10 || type == 0x11) {
                    for (int* q = p + 1; q != list->end; ++q)
                        q[-1] = q[0];
                    list->end = (int*)((char*)list->end - 4);
                } else {
                    ++p;
                }
            }
        }

        if (sel[3] >= 0 && sel[0] >= 0)
            ClearStream((char*)entriesV + sel[0] * 0x20 + 0x10);
        if (sel[4] >= 0 && sel[1] >= 0)
            ClearStream((char*)entriesV + sel[1] * 0x20 + 0x10);
        if (sel[5] >= 0 && sel[2] >= 0)
            ClearStream((char*)entriesV + sel[2] * 0x20 + 0x10);
    }

    MergeGroup(param_3, g, sel[0], sel[6], sel[3], 0xc, param_2, param_1);
    MergeGroup(param_3, g, sel[1], sel[6], sel[4], 0xd, param_2, param_1);
    MergeGroup(param_3, g, sel[2], sel[6], sel[5], 0xe, param_2, param_1);

    NormalizeStream((char*)g->begin08 + 0x10, sel[1]);
    NormalizeStream((char*)g->begin08 + 0x10, sel[2]);
}
