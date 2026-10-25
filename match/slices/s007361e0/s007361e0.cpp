// Slice s007361e0 — refcounted EltArray/descriptor construction and reconstruction loops.
// 0x00736660 is a small in-place emplace; the three larger EH/refcount routines rebuild
// the element-index arrays of a mesh model.  Optimized module:
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

typedef unsigned int size_t_;

// ---------------------------------------------------------------------------
// Allocation (EASTL sp_vector_allocator / raw operator new-delete)
// ---------------------------------------------------------------------------
void* EAAlloc(size_t_ n, const char* name, int flags, unsigned debugFlags,
              const char* file, int line);              // 0x00f473a0
void  EAFree(void* p);                                  // 0x00f47380
inline void* operator new(size_t_, void* p) { return p; }

// ---------------------------------------------------------------------------
// Ref-counted buffer (EA::RefCountTemplate<EA::Thread::AtomicInt<int>>)
// ---------------------------------------------------------------------------
struct IRefObj {
    virtual int AddRef();       // vtable slot 0
    virtual int Release();      // vtable slot 1
};

// SP::cEltArrayRef / SP::cIndexArrayRef (0x10)
struct cEltArrayRef {
    int            mNumElts;    // +0x00
    unsigned char* mData;       // +0x04
    unsigned short mEltSize;    // +0x08
    unsigned short mEltStride;  // +0x0a
    IRefObj*       mDataRC;     // +0x0c
    void Assign(const cEltArrayRef* src);       // 0x00424f70 Handle::Assign
};

// The refcount copy is inlined at nearly every site in the retail code (only the
// empty-element-list branch calls 0x00424f70 out of line).
__forceinline void AssignElt(cEltArrayRef* dst, const cEltArrayRef* src)
{
    dst->mNumElts = src->mNumElts;
    dst->mData = src->mData;
    dst->mEltSize = src->mEltSize;
    dst->mEltStride = src->mEltStride;
    if (src->mDataRC != dst->mDataRC) {
        IRefObj* old = dst->mDataRC;
        if (src->mDataRC)
            src->mDataRC->AddRef();
        dst->mDataRC = src->mDataRC;
        if (old)
            old->Release();
    }
}

// ---------------------------------------------------------------------------
// Model (the stream list at +0x08 and the 0x14-byte section list at +0x30)
// ---------------------------------------------------------------------------
struct ModelStream {            // 0x10
    int            mNumElts;    // +0x00
    unsigned char* mData;       // +0x04
    unsigned short mEltSize;    // +0x08
    unsigned short mEltStride;  // +0x0a
    IRefObj*       mDataRC;     // +0x0c
};
struct ModelStreamEntry {       // 0x20
    int         mSemantic;      // +0x00
    int         mUsageIdx;      // +0x04
    int         mNumber;        // +0x08
    int         mType;          // +0x0c
    ModelStream mStream;        // +0x10
};
struct Sec14 {                  // 0x14
    int mType;                  // +0x00
    int mIdx;                   // +0x04
    int mF8;                    // +0x08
    int mFC;                    // +0x0c
    int mF10;                   // +0x10
};
struct Model {
    char              pad_00[0x08];
    ModelStreamEntry* mStreamsBegin;    // +0x08
    ModelStreamEntry* mStreamsEnd;      // +0x0c
    char              pad_10[0x20];
    Sec14*            mSecBegin;        // +0x30
    Sec14*            mSecEnd;          // +0x34
};

// ---------------------------------------------------------------------------
// Helpers used by the reconstruction routines.
// ---------------------------------------------------------------------------
struct Key3 { int a, b, v; };

Key3* LowerBound(Key3* begin, Key3* end, const Key3* key, char flag); // 0x007330d0

struct KeyVec {                 // sorted vector of 0xc-byte keys (0x18)
    Key3* mpBegin;              // +0x00
    Key3* mpEnd;                // +0x04
    Key3* mpCap;                // +0x08
    int   mPad0;                // +0x0c
    int   mPad1;                // +0x10
    char  mFlag;                // +0x14
    Key3* findLower(const Key3* key);   // 0x00735ec0
};

void Obj15_Init(cEltArrayRef* p);                               // 0x00720070
void Obj15_ctor(int count, unsigned short eltSize, cEltArrayRef* out); // 0x00720190

// cEltArrayRefT<4-byte element> accessor over the ref-counted IntVecObj.
struct ContV {
    virtual void Init(int);
    char          pad[8];
    int           mC;           // +0x0c
    int           m10;          // +0x10
    cEltArrayRef* Make4(cEltArrayRef* out);     // 0x00732ff0
};

// Ref-counted int-vector object (0x24).
struct IntVecObj {
    char pad_00[0x0c];
    int* mBegin;        // +0x0c
    int* mEnd;          // +0x10
    int* mCap;          // +0x14
    char pad_18[8];
    int  mField20;      // +0x20
    IntVecObj(int n);   // 0x00723680
};

// eastl::fixed_vector<int,64> (0x18 header + inline buffer).
template <int N>
struct FixedIntVec {
    int* mpBegin;       // +0x00
    int* mpEnd;         // +0x04
    int* mpCap;         // +0x08
    int  mOverflow;     // +0x0c
    int* mpPoolBegin;   // +0x10
    int  mUnused;       // +0x14
    int  mBuffer[N];    // +0x18
    FixedIntVec()
    {
        mpBegin = mpEnd = mBuffer;
        mpPoolBegin = mBuffer;
        mpCap = mBuffer + N;
        mOverflow = 0;
        mUnused = 0;
    }
    void DoInsertValue(int* pos, const int& value);     // 0x004281d0
    void push_back(int value)
    {
        if (mpEnd != mpCap)
            *mpEnd++ = value;
        else
            DoInsertValue(mpEnd, value);
    }
};
typedef FixedIntVec<64> IntFixedVec;

// ---------------------------------------------------------------------------
// SP::cMDSection (retail 0x8c) and the owning mesh-data container.
// ---------------------------------------------------------------------------
struct cMDFormatEntry { short mElts; short mIndices; };

struct FormatVec {              // fixed_vector<cMDFormatEntry,6>, only the head is used here
    cMDFormatEntry* mpBegin;    // +0x00
    cMDFormatEntry* mpEnd;      // +0x04
    cMDFormatEntry* mpCap;      // +0x08
};
struct RefVec {                 // eastl::vector<cEltArrayRef> head
    cEltArrayRef* mpBegin;      // +0x00
    cEltArrayRef* mpEnd;        // +0x04
    cEltArrayRef* mpCap;        // +0x08
    void resize(int n);         // 0x004751a0
};
struct Section {                // 0x8c
    cEltArrayRef mVertIndices;  // +0x00
    int          mNumVertices;  // +0x10
    FormatVec    mFormat;       // +0x14
    char         pad_20[0x24];  // +0x20 .. +0x44
    RefVec       mEltIndices;   // +0x44
    char         pad_50[0x3c];  // +0x50 .. +0x8c
};
struct MeshData {
    char     pad_00[0x1c];
    Section* mpSectionsBegin;   // +0x1c
    Section* mpSectionsEnd;     // +0x20
};

// Mask table indexed by element width (0x0140d4e0).
extern const uint32_t g_d4e0[];     // 0x0140d4e0

void FUN_00423080(int);
void FUN_00424cf0(int, int);
typedef void (__thiscall *FnVoidIP)(void*, int);
typedef void (__thiscall *FnVoidIIP)(void*, int, int);
void FUN_004751a0(int);
void FUN_00424f70(int*);
int* FUN_00732ff0(void*);
void* FUN_00723680(int);

struct Vec41
{
    int* mBegin;
    int* mEnd;
    int* mCap;
    int  emit(int pos, int src);   // 0x736660
};

// @ 0x00736660
int Vec41::emit(int param_2, int param_3)
{
    int iVar1 = (int)mEnd;
    int iVar2 = (int)mBegin;
    if (param_2 == iVar1 && iVar1 != (int)mCap)
    {
        mEnd = (int*)(iVar1 + 0x20);
        if (iVar1 != 0)
            ((FnVoidIP)FUN_00423080)((void*)iVar1, param_3);
    }
    else
    {
        ((FnVoidIIP)FUN_00424cf0)(this, param_2, param_3);
    }
    return ((param_2 - iVar2) >> 5) * 0x20 + (int)mBegin;
}

// ---------------------------------------------------------------------------
// Stream lookup (0x0071ddc0): same filter used by the mesh loader.
// ---------------------------------------------------------------------------
int FindStreamEntry(const Model* m, int semantic, int usageIdx, int number, int type); // 0x0071ddc0

// @ 0x007361e0
int FUN_007361e0(int param_1)
{
    Model* model = (Model*)param_1;
    int result = 0;

    int i15 = FindStreamEntry(model, 0x15, 0, 6, 0xe);
    int i14 = FindStreamEntry(model, 0x14, 0, 6, 0xe);
    if (i15 < 0)
        return -1;

    // The position stream (semantic 0x15) owns the ordering used by the section list.
    cEltArrayRef pos;
    {
        ModelStream* s = &model->mStreamsBegin[i15].mStream;
        pos.mNumElts = s->mNumElts;
        pos.mData = s->mData;
        pos.mEltSize = s->mEltSize;
        pos.mEltStride = s->mEltStride;
        pos.mDataRC = s->mDataRC;
        if (pos.mDataRC)
            pos.mDataRC->AddRef();
    }

    // Optional second stream (semantic 0x14) provides the tie-break key.
    cEltArrayRef key;
    key.mNumElts = 0;
    key.mData = 0;
    key.mEltSize = 4;
    key.mEltStride = 4;
    key.mDataRC = 0;
    if (i14 >= 0) {
        ModelStream* s = &model->mStreamsBegin[i14].mStream;
        key.mNumElts = s->mNumElts;
        key.mData = s->mData;
        key.mEltSize = s->mEltSize;
        key.mEltStride = s->mEltStride;
        key.mDataRC = s->mDataRC;
        if (key.mDataRC)
            key.mDataRC->AddRef();
    }

    KeyVec keys;
    keys.mpBegin = 0;
    keys.mpEnd = 0;
    keys.mpCap = 0;
    keys.mPad0 = 0;
    keys.mPad1 = 0;
    keys.mFlag = 0;
    IntFixedVec seq;

    // Assign each section a compact ordinal: sections sharing a (pos,key) pair share one.
    int nSec = (int)(model->mSecEnd - model->mSecBegin) / 0x14;
    if (nSec > 0) {
        Sec14* sec = model->mSecBegin;
        for (int i = 0; i < nSec; ++i, ++sec) {
            int idx = sec->mF10;
            int a = *(int*)(pos.mData + pos.mEltStride * idx);
            int b = (i14 < 0) ? -1 : *(int*)(key.mData + key.mEltStride * idx);
            Key3 k;
            k.a = a;
            k.b = b;
            k.v = 0;
            Key3* pos3 = LowerBound(keys.mpBegin, keys.mpEnd, &k, keys.mFlag);
            if (pos3 == keys.mpEnd || pos3->a > a || (pos3->a == a && b < pos3->b)) {
                seq.push_back(idx);
                sec->mF10 = result;
                Key3* slot = keys.findLower(&k);
                slot->v = result;
                ++result;
            } else {
                sec->mF10 = pos3->v;
            }
        }
    }

    // Rebuild every position stream from the ordinal order.
    int nStreams = (int)(model->mStreamsEnd - model->mStreamsBegin);
    if (nStreams > 0) {
        ModelStreamEntry* e = model->mStreamsBegin;
        for (int i = 0; i < nStreams; ++i, ++e) {
            if (e->mType != 8)
                continue;
            cEltArrayRef src;
            src.mNumElts = e->mStream.mNumElts;
            src.mData = e->mStream.mData;
            src.mEltSize = e->mStream.mEltSize;
            src.mEltStride = e->mStream.mEltStride;
            src.mDataRC = e->mStream.mDataRC;
            if (src.mDataRC)
                src.mDataRC->AddRef();

            cEltArrayRef dst;
            dst.mNumElts = 0;
            dst.mData = 0;
            dst.mEltSize = 0;
            dst.mEltStride = 0;
            dst.mDataRC = 0;
            Obj15_ctor(result, src.mEltSize, &dst);

            int count = (int)(seq.mpEnd - seq.mpBegin);
            for (int j = 0; j < count; ++j) {
                int si = seq.mpBegin[j];
                memcpy(dst.mData + dst.mEltStride * j,
                       src.mData + src.mEltStride * si, src.mEltSize);
            }

            AssignElt((cEltArrayRef*)&e->mStream, &dst);
            if (dst.mDataRC)
                dst.mDataRC->Release();
            if (src.mDataRC)
                src.mDataRC->Release();
        }
    }

    if (seq.mpBegin && seq.mpBegin != seq.mBuffer)
        EAFree(seq.mpBegin);
    if (keys.mpBegin)
        EAFree(keys.mpBegin);
    if (key.mDataRC)
        key.mDataRC->Release();
    if (pos.mDataRC)
        pos.mDataRC->Release();
    return result;
}

// @ 0x007366e0
void FUN_007366e0(int param_1)
{
    MeshData* md = (MeshData*)param_1;
    Section* sec = md->mpSectionsBegin;
    int n = (int)((md->mpSectionsEnd - sec) / 0x8c);
    for (int i = 0; i < n; ++i, ++sec) {
        // Only sections whose element-index list is still empty get one built.
        if (sec->mEltIndices.mpBegin != sec->mEltIndices.mpEnd)
            continue;

        sec->mEltIndices.resize(1);
        AssignElt(sec->mEltIndices.mpBegin, &sec->mVertIndices);

        int nf = (int)(sec->mFormat.mpEnd - sec->mFormat.mpBegin) >> 2;
        for (int j = 0; j < nf; ++j)
            *(short*)((char*)sec->mFormat.mpBegin + j * 4 + 2) = 0;

        int nv = sec->mVertIndices.mNumElts;
        sec->mNumVertices = nv;

        IntVecObj* v = (IntVecObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
        if (v)
            v = new (v) IntVecObj(nv);
        for (int j = 0; j < nv; ++j)
            v->mBegin[j] = j;

        cEltArrayRef tmp;
        ((ContV*)v)->Make4(&tmp);
        AssignElt(&sec->mVertIndices, &tmp);
        if (tmp.mDataRC)
            tmp.mDataRC->Release();
    }
}

// @ 0x007368a0
void FUN_007368a0(int* param_1)
{
    Section* sec = (Section*)param_1;
    int nv = sec->mVertIndices.mNumElts;
    if (nv == sec->mNumVertices)
        return;

    if (sec->mEltIndices.mpBegin == sec->mEltIndices.mpEnd) {
        sec->mEltIndices.resize(1);
        sec->mEltIndices.mpBegin->Assign(&sec->mVertIndices);
        int nf = (int)(sec->mFormat.mpEnd - sec->mFormat.mpBegin) >> 2;
        for (int j = 0; j < nf; ++j)
            *(short*)((char*)sec->mFormat.mpBegin + j * 4 + 2) = 0;
    } else {
        int count = (int)((sec->mEltIndices.mpEnd - sec->mEltIndices.mpBegin) >> 4);
        for (int i = 0; i < count; ++i) {
            cEltArrayRef tmp;
            tmp.mNumElts = nv;
            tmp.mData = 0;
            tmp.mEltSize = 4;
            tmp.mEltStride = 4;
            tmp.mDataRC = 0;
            Obj15_Init(&tmp);

            cEltArrayRef* e = sec->mEltIndices.mpBegin + i;
            for (int j = 0; j < nv; ++j) {
                int masked = (int)(g_d4e0[sec->mVertIndices.mEltSize] &
                     *(unsigned int*)(sec->mVertIndices.mData +
                                      j * sec->mVertIndices.mEltStride));
                int val = *(int*)(e->mData + masked * e->mEltStride);
                *(int*)(tmp.mData + j * tmp.mEltStride) =
                    (int)(g_d4e0[e->mEltSize] & (unsigned int)val);
            }

            AssignElt(e, &tmp);
            if (tmp.mDataRC)
                tmp.mDataRC->Release();
        }
    }

    // The vertex-index array becomes the identity permutation.
    cEltArrayRef ident;
    ident.mNumElts = nv;
    ident.mData = 0;
    ident.mEltSize = 4;
    ident.mEltStride = 4;
    ident.mDataRC = 0;
    Obj15_Init(&ident);
    for (int j = 0; j < nv; ++j)
        *(int*)(ident.mData + j * ident.mEltStride) = j;

    AssignElt(&sec->mVertIndices, &ident);
    sec->mNumVertices = nv;
    if (ident.mDataRC)
        ident.mDataRC->Release();
}
