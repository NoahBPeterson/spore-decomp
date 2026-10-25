// slice s00774f80: SP::cRuntimeModelBuilder comparison / copy helpers with EH
// frames and inlined EASTL vectors (fixed 0x14-byte element ranges, 0x8c-byte
// mesh records, 0x20-byte cell elements).
#include "types.h"
#include <intrin.h>

extern "C" void  EASTL_allocator_deallocate(void* p);   // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, int c, int d);  // 0x00f473a0

// The 0x20-byte vector element: a 4-dword header (0x13,0,0xe,5) followed by the
// copied mesh record fields and a refcounted pointer at +0x1c.
struct Elem20 {
    int m0;              // +0x00 (copied from src+0x00)
    int m4;              // +0x04 (copied from src+0x04)
    unsigned short m8;   // +0x08
    unsigned short ma;   // +0x0a
    void* mpRef;         // +0x0c (copied start; full 0x20 layout below)
};
// 0x0041f7d0 — vector<0x20-byte element>::push_back, __thiscall(this, const Elem&).
struct Vec20 {
    void push_back(const Elem20& value);
};

// ---- fixed-vector range constructor (0x00774f10): builds a vector from a
//      [first,last) range of 0x14-byte elements.  Reconstructed elsewhere; the
//      ABI here is __thiscall(dst, first, last) with ret 8.
struct FixVec14 {
    int* mpBegin;     // +0x00
    int* mpEnd;       // +0x04
    int* mpCapacity;  // +0x08
    int* mpAlloc;     // +0x0c
    int* mpFixed;     // +0x10
    int mAux14;       // +0x14
    int mInline[0x140 / 4];   // +0x18 .. +0x158 inline storage (16 x 0x14 elements)
    void init_range(void* first, void* last);   // @ 0x00774f10
    ~FixVec14() {
        if (mpBegin != 0 && mpBegin != mpFixed)
            EASTL_allocator_deallocate(mpBegin);
    }
};

// ---- eastl::sort over 0x14-byte elements with a function-pointer comparator
//      (0x007749e0): __cdecl(first, last, compare) where compare is the
//      3-int lexicographic LessPage at 0x0076f540.
extern "C" void eastl_sort_14(void* first, void* last, void* compare);  // 0x007749e0
extern "C" void* LessPage;   // 0x0076f540

// ---- SP::cRuntimeModelBuilder: mesh helpers.
struct CellVec;
struct RuntimeModelBuilder {
    int m0;                  // +0x00
    int m4;                  // +0x04
    int mCount;              // +0x08  (number of meshes)
    int m_0c;                // +0x0c
    int m_10;                // +0x10
    int m_pRecA;             // +0x14  (0x8c-byte record array)
    int m_pRecB;             // +0x18
    int m_pMeshBegin;        // +0x1c  (0x8c-byte mesh records)
    int m_pMeshEnd;          // +0x20
    int m_24;                // +0x24
    int m_28;                // +0x28
    int m_2c;                // +0x2c
    int m_pFixBegin;         // +0x30  (0x14-byte fixed elements)
    int m_pFixEnd;           // +0x34
    void BuildCellArray(void** out);   // @ 0x00775230
};

// @ 0x00774f80
bool CompareModelBuilders(RuntimeModelBuilder* a, RuntimeModelBuilder* b) {
    // (m_pMeshEnd - m_pMeshBegin) / 0x8c, signed.
    int meshA = (int)(((char*)a->m_pMeshEnd - (char*)a->m_pMeshBegin)) / 0x8c;
    int meshB = (int)(((char*)b->m_pMeshEnd - (char*)b->m_pMeshBegin)) / 0x8c;
    if (meshA != meshB)
        return false;

    int fixA = (int)(((char*)a->m_pFixEnd - (char*)a->m_pFixBegin)) / 0x14;
    int fixB = (int)(((char*)b->m_pFixEnd - (char*)b->m_pFixBegin)) / 0x14;
    if (fixA != fixB)
        return false;

    FixVec14 vecA, vecB;
    vecA.init_range((void*)a->m_pFixBegin, (void*)a->m_pFixEnd);
    vecB.init_range((void*)b->m_pFixBegin, (void*)b->m_pFixEnd);

    eastl_sort_14(vecA.mpBegin, vecA.mpEnd, &LessPage);
    eastl_sort_14(vecB.mpBegin, vecB.mpEnd, &LessPage);

    const int n = (int)(((char*)vecA.mpEnd - (char*)vecA.mpBegin)) / 0x14;
    const int* pa = vecA.mpBegin;
    const int* pb = vecB.mpBegin;
    int i = 0;
    if (n > 0) {
        do {
            if (pa[0] != pb[0])
                return false;
            if (pa[1] != pb[1])
                return false;
            if (pa[2] != pb[2])
                return false;
            if (pa[3] != pb[3])
                return false;
            ++i;
            pa += 5;
            pb += 5;
        } while (i < n);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00775230  build a packed 0xa0-byte-per-mesh cell array from the builder's
// 0x30-stride source records plus 0xb0-stride source element blocks, then hand
// it to the 0x10-byte refcounted cell-array constructor and store via out.
// ---------------------------------------------------------------------------
// 0x007003a0 — cell-array constructor, __thiscall(this=newObj, buffer, count).
struct CellVec;
struct CellArray {
    void ctor(CellVec* buffer, int count);
};

// The 0xb0-byte source element block (only the offsets the body reads).
struct MeshSrc {
    unsigned char m00;        // +0x00
    char pad03[3];
    int m04;                  // +0x04
    int m08;                  // +0x08
    int m0c;                  // +0x0c
    float m10[4];             // +0x10..0x1c
    float m20[4];             // +0x20..0x2c
    float m30[4];             // +0x30..0x3c
    float m40[4];             // +0x40..0x4c
    float m50[4];             // +0x50..0x5c
    float m60[4];             // +0x60..0x6c
    float m70[4];             // +0x70..0x7c
    float m80[4];             // +0x80..0x8c
    int m90;                  // +0x90
    int m94;                  // +0x94
    int m98;                  // +0x98
    int m9c;                  // +0x9c
    int ma0;                  // +0xa0
    int ma4;                  // +0xa4
};

// The 0x30-byte source record: the first three dwords feed dest[0..2].
struct MeshRec {
    int m00;                  // +0x00
    int m04;                  // +0x04
    int m08;                  // +0x08
    int m0c;                  // +0x0c
    int m10;                  // +0x10
    int m14;                  // +0x14
    int m18;                  // +0x18
    int m1c;                  // +0x1c
    int m20;                  // +0x20
    int m24;                  // +0x24
    int m28;                  // +0x28
    int m2c;                  // +0x2c
};

// The 0xa0-byte packed destination cell.
struct CellRec {
    int m[0x28];              // 0xa0 bytes
};

struct Vec4i { int x, y, z, w; };

// The stack-local fixed vector that accumulates the packed cells: a 0x20-byte
// header whose begin pointer points at the 0x100-entry inline array at +0x20.
struct CellVec {
    CellRec* mpBegin;         // +0x00 (points at the inline array)
    CellRec* mpEnd;           // +0x04
    CellRec* mpCapacity;      // +0x08
    CellRec* mpAlloc;         // +0x0c
    CellRec* mpFixed;         // +0x10
    int m_14;                 // +0x14
    int m_18;                 // +0x18
    int m_1c;                 // +0x1c
    CellRec mInline[0x100];   // +0x20
    void reserve(int count);  // @ 0x00774d30
};

void RuntimeModelBuilder::BuildCellArray(void** out) {
    CellVec vec;              // fixed 0x100-entry packed buffer (0xa000 bytes)

    vec.reserve(mCount);

    int idx = 0;
    if (mCount > 0) {
        int dstOff = 0;
        int recOff = 0;
        int elOff = 0;
        do {
            const MeshRec* rec = (const MeshRec*)(m_pRecA + recOff);
            const MeshSrc* el = (const MeshSrc*)(m_pRecB + elOff);
            CellRec* d = (CellRec*)((char*)vec.mpBegin + dstOff);
            int* o = d->m;

            o[0] = rec->m10;
            o[1] = rec->m14;
            o[2] = rec->m18;
            // rec[0..3] copied as one 16-byte block (original: movaps).
            *(Vec4i*)&o[4] = *(const Vec4i*)&rec->m00;
            o[8] = rec->m1c;
            o[9] = rec->m20;
            o[10] = rec->m24;
            o[0xb] = el->m90;
            o[0xc] = el->m94;
            o[0xd] = el->m98;
            *(unsigned char*)&o[0xe] = el->m00;
            o[0xf] = el->m04;
            o[0x10] = el->m08;
            o[0x11] = el->m0c;

            // 4x4 matrix product: out rows = A(m10,m20,m30,m40) * B(cols m50,m60,m70,m80).
            float* f = (float*)&o[0x14];
            f[0] = el->m10[0] * el->m50[0] + el->m20[0] * el->m50[1] + el->m30[0] * el->m50[2];
            f[1] = el->m10[1] * el->m50[0] + el->m20[1] * el->m50[1] + el->m30[1] * el->m50[2];
            f[2] = el->m10[2] * el->m50[0] + el->m20[2] * el->m50[1] + el->m30[2] * el->m50[2];
            f[3] = el->m10[3] * el->m50[0] + el->m20[3] * el->m50[1] + el->m30[3] * el->m50[2];
            f[4] = el->m10[0] * el->m60[0] + el->m20[0] * el->m60[1] + el->m30[0] * el->m60[2];
            f[5] = el->m10[1] * el->m60[0] + el->m20[1] * el->m60[1] + el->m30[1] * el->m60[2];
            f[6] = el->m10[2] * el->m60[0] + el->m20[2] * el->m60[1] + el->m30[2] * el->m60[2];
            f[7] = el->m10[3] * el->m60[0] + el->m20[3] * el->m60[1] + el->m30[3] * el->m60[2];
            f[8] = el->m10[0] * el->m70[0] + el->m20[0] * el->m70[1] + el->m30[0] * el->m70[2];
            f[9] = el->m10[1] * el->m70[0] + el->m20[1] * el->m70[1] + el->m30[1] * el->m70[2];
            f[10] = el->m10[2] * el->m70[0] + el->m20[2] * el->m70[1] + el->m30[2] * el->m70[2];
            f[11] = el->m10[3] * el->m70[0] + el->m20[3] * el->m70[1] + el->m30[3] * el->m70[2];
            f[12] = el->m10[0] * el->m80[0] + el->m20[0] * el->m80[1] + el->m30[0] * el->m80[2] + el->m40[0];
            f[13] = el->m10[1] * el->m80[0] + el->m20[1] * el->m80[1] + el->m30[1] * el->m80[2] + el->m40[1];
            f[14] = el->m10[2] * el->m80[0] + el->m20[2] * el->m80[1] + el->m30[2] * el->m80[2] + el->m40[2];
            f[15] = el->m10[3] * el->m80[0] + el->m20[3] * el->m80[1] + el->m30[3] * el->m80[2] + el->m40[3];
            o[0x24] = el->m9c;
            o[0x25] = el->ma0;
            o[0x26] = el->ma4;

            ++idx;
            dstOff += 0xa0;
            recOff += 0x30;
            elOff += 0xb0;
        } while (idx < mCount);
    }

    char* p = (char*)EASTL_allocator_allocate(0x10, "Graphics", 0, 0, 0, 0);
    char* result = 0;
    if (p == 0) {
        result = 0;
    } else {
        result = p;
        ((CellArray*)result)->ctor(&vec, mCount);
    }
    *(int*)(result + 4) += 1;   // refcount
    *out = result;
}

// ---------------------------------------------------------------------------
// build the element index table from the two findStream lookups and copy
// per-index 3-float values into the stream buffers.
// ---------------------------------------------------------------------------
extern "C" void* Model_findStream(void* m, int semantic, int usageIdx, int number, int type);  // 0x0071de40
extern "C" int   Model_findStreamEntry(void* m, int semantic, int usageIdx, int number, int type);  // 0x0071ddc0
extern "C" void  BuildIndexTable(void* m, void* out);        // 0x0076fdc0
extern "C" void  Obj15_200f0(void* buf);                     // 0x007200f0
extern "C" void  FUN_00774d90(int v);                        // 0x00774d90
extern int g_0140e5b4[];   // 0x0140e5b4 (channel mask table)
extern int g_0140e5c8[];   // 0x0140e5c8 (semantic list)
extern int g_0140e5d4[];   // 0x0140e5d4 (end of the semantic list)

// A per-semantic stream buffer: count, then stride/index ahead of a data base.
struct StreamBuf {
    int mCount;              // +0x00
    int mBase;               // +0x04 (data base pointer)
    unsigned short m08;      // +0x08
    unsigned short mStrideA; // +0x0a
};

// A 0x8c-byte mesh record: the stream pointer and its channel/stride fields.
struct MeshRecord8c {
    int m00;                 // +0x00
    int mStream;             // +0x04 (StreamBuf*)
    unsigned short m08;      // +0x08 (channel index)
    unsigned short mStride;  // +0x0a (variable stride)
};

// An 8-byte index-table entry: a record index and a column.
struct IndexEntry {
    int mIndex;              // +0x00 (-1 = empty)
    int mColumn;             // +0x04
};

// An index table. BuildIndexTable (0x0076fdc0) fills it: a heap or inline array
// of 8-byte entries, with the count alongside.
struct IndexTable {
    char mInline[0x10];       // +0x00 (inline header / self pointer)
    IndexEntry* mpEntries;    // +0x10
    int mCount;               // +0x14
    char mBuf[0x2000];        // +0x18 inline storage
    void* data() { return mBuf; }
    IndexEntry* entries() { return mpEntries; }
};

// @ 0x007754d0
bool BuildElementIndex(void* arg1, void* arg2) {
    void* target = arg1;   // the mesh whose stream/index we build
    void* source = arg2;   // the mesh we read values from
    void* stream = Model_findStream(target, 1, -1, 3, 0xe);
    if (((int*)stream)[1] == 0)
        return false;

    int handle = ((int*)stream)[0];
    FUN_00774d90(handle);

    IndexTable table;
    BuildIndexTable(target, &table);

    int* sem = g_0140e5c8;
    do {
        int i0 = Model_findStreamEntry(source, *sem, -1, 3, 0xe);
        int i1 = Model_findStreamEntry(target, *sem, -1, 3, 0xe);
        if (i0 >= 0 && i1 >= 0) {
            StreamBuf* dst = (StreamBuf*)(*(int*)((char*)target + 8) + i1 * 0x20 + 0x10);
            StreamBuf* src = (StreamBuf*)(*(int*)((char*)source + 8) + i0 * 0x20 + 0x10);
            Obj15_200f0(dst);

            int n = dst->mCount;
            if (table.mCount < n)
                n = table.mCount;

            IndexEntry* e = table.entries();
            for (int j = 0; j < n; ++j) {
                if (e[j].mIndex == -1)
                    continue;
                int col = e[j].mColumn;
                MeshRecord8c* rec = (MeshRecord8c*)(*(int*)((char*)source + 0x1c) + e[j].mIndex * 0x8c);
                if (rec->mStream != 0) {
                    unsigned int raw = *(unsigned int*)(rec->mStream + rec->mStride * col);
                    col = (int)(raw & (unsigned int)g_0140e5b4[rec->m08]);
                }
                float* srcv = (float*)(src->mBase + src->mStrideA * col);
                float* dstv = (float*)(dst->mBase + dst->mStrideA * j);
                dstv[0] = srcv[0];
                dstv[1] = srcv[1];
                dstv[2] = srcv[2];
            }
        }
        ++sem;
    } while (sem < g_0140e5d4);

    if (table.mpEntries != 0 && (void*)table.mpEntries != table.data())
        EASTL_allocator_deallocate(table.mpEntries);
    return true;
}

// ---------------------------------------------------------------------------
// push_back a 0x20-byte element (copied from src with an AddRef on its
// referenced object) onto the vector field at self+8.
// ---------------------------------------------------------------------------
struct RefObject {
    virtual void AddRef();    // vtbl +0
    virtual void Release();   // vtbl +4
};

// The 0x20-byte element as an unwindable object: its destructor releases the
// owned reference, which is what puts an EH frame around the push_back call.
struct Elem20Full {
    int h0, h1, h2, h3;   // +0x00 +0x04 +0x08 +0x0c
    int m0;               // +0x10
    int m4;               // +0x14
    unsigned short m8;    // +0x18
    unsigned short ma;    // +0x1a
    void* mpRef;          // +0x1c
    ~Elem20Full() {
        if (mpRef != 0)
            ((RefObject*)mpRef)->Release();
    }
};

// @ 0x007756b0
void PushElem20(void* self, Elem20* src) {
    Elem20Full tmp;
    tmp.h0 = 0x13;
    tmp.h1 = 0;
    tmp.h2 = 0xe;
    tmp.h3 = 5;
    tmp.m0 = src->m0;
    tmp.m4 = src->m4;
    tmp.m8 = src->m8;
    tmp.ma = src->ma;
    tmp.mpRef = src->mpRef;

    if (tmp.mpRef != 0)
        ((RefObject*)tmp.mpRef)->AddRef();

    ((Vec20*)((char*)self + 8))->push_back(*(const Elem20*)&tmp);
}
