// Slice s0071e390: SP mesh / primitive helpers (stream writer, fills, index collectors,
// vector<int> / vector<cFaceCluster> insert/resize, entry copy loops).
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t_;

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---------------------------------------------------------------------------
// Allocation / helpers living in other slices
// ---------------------------------------------------------------------------
void* operator_new(size_t_ n, const char* name, int, int, const char* file, int line);   // 0x00f473a0
void  operator_delete__(void* p);                                                         // 0x00f47380
#define NEW_ARRAY_BYTES(n) operator_new((n), "Graphics", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL\\allocator.h", 0xd1)

// ---------------------------------------------------------------------------
// vector<int>-like (sp_vector_allocator: begin, end, capacity, <pad>, fixed buffer)
// ---------------------------------------------------------------------------
int*  CopyInts(int* first, int* last, int* dest);                 // 0x007eb060 (uninitialized_copy)
int*  CopyBackwardInts(int* first, int* last, int* destEnd);      // 0x00c16090 (copy_backward)
void  FillInt(int* first, int* last, const int* value);           // 0x0071e5e0
void  FillNInt(int* first, unsigned n, const int* value);         // 0x0071e7a0

struct VecInt {
    int* mpBegin; int* mpEnd; int* mpCapacity; int mAllocPad; int* mpFixed;
    void DoInsertValues(int* position, unsigned n, const int* value);   // 0x0071e870
    void DoInsertValue(int* position, const int& value);               // 0x004558a0
    void reserve(unsigned n);                                          // 0x004e0880
    void resize(unsigned n);                                           // 0x0071ef50
    int* erase(int* first, int* last);                                 // 0x004ce270
    void push_back(const int& v)
    {
        if (mpEnd < mpCapacity) {
            int* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

// ---------------------------------------------------------------------------
// Mesh container layout (as seen by WriteMesh / FindPrimitives / collectors)
// ---------------------------------------------------------------------------
struct RefCounted {                 // EA::AutoRefCount target with inline interlocked refcount
    virtual void* Destroy(int flag);
    long mRefCount;
    void AddRef() { _InterlockedExchangeAdd(&mRefCount, 1); }
    int Release()
    {
        long n = _InterlockedExchangeAdd(&mRefCount, -1) - 1;
        if (n == 0) {
            _InterlockedExchange(&mRefCount, 1);
            Destroy(1);
        }
        return n;
    }
};

struct IRef {                       // virtual AddRef/Release (+0, +4)
    virtual int AddRef();
    virtual int Release();
};

struct Handle {                     // 16-byte handle member of a vertex record
    int mF0, mF4;                   // +0x00, +0x04
    short mS8, mSA;                 // +0x08, +0x0a
    IRef* mpRef;                    // +0x0c (refcounted)
    void Assign(const Handle* src);                                          // 0x00424f70
};
struct Vertex20 {                   // 0x20 bytes
    unsigned mA, mB, mC, mD;        // +0x00 .. +0x0c
    Handle mHandle;                 // +0x10
};

struct Prim14 {                     // 0x14 bytes
    int mType;                      // +0x00
    int mEntry;                     // +0x04
    int mStart;                     // +0x08
    int mEnd;                       // +0x0c
    int mAux;                       // +0x10
};

struct Entry8c {                    // 0x8c bytes
    unsigned mA, mB;                // +0x00, +0x04  (written by FUN_0071dbf0)
    short mS0, mS1;                 // +0x08, +0x0a
    IRef* mpRef;                    // +0x0c
    int mI10;                       // +0x10
    int* mpIdBegin;                 // +0x14 (fixed id vector of shorts pairs)
    int* mpIdEnd;                   // +0x18
    int* mpIdCap;                   // +0x1c
    char pad_20[0x44 - 0x20];
    char* mpV16Begin;               // +0x44 (16-byte records)
    char* mpV16End;                 // +0x48
    char pad_4c[0x8c - 0x4c];
};

struct Mesh {
    char pad_00[8];
    char* mpVertBegin;              // +0x08  (Vertex20)
    char* mpVertEnd;                // +0x0c
    char pad_10[0x1c - 0x10];
    char* mpEntryBegin;             // +0x1c  (Entry8c)
    char* mpEntryEnd;               // +0x20
    char pad_24[0x30 - 0x24];
    Prim14* mpPrimBegin;            // +0x30
    Prim14* mpPrimEnd;              // +0x34
};

// ===========================================================================
// @ 0x0071e5e0
// ===========================================================================
void FillInt(int* first, int* last, const int* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// ===========================================================================
// @ 0x0071e7a0
// ===========================================================================
void FillNInt(int* first, unsigned n, const int* value)
{
    if (n != 0) {
        do {
            if (first)
                *first = *value;
            ++first;
        } while (--n);
    }
}

// ===========================================================================
// @ 0x0071ef50  vector<int>::resize
// ===========================================================================
void VecInt::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        struct { short lo, hi; } v;   // element default value: two zeroed 16-bit halves
        v.lo = 0;
        v.hi = 0;
        DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), (const int*)&v);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// ===========================================================================
// @ 0x0071e870  vector<int>::DoInsertValues(position, n, value)
// ===========================================================================
void VecInt::DoInsertValues(int* position, unsigned n, const int* value)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const int temp = *value;
            const unsigned nExtra = (unsigned)(mpEnd - position);
            int* const oldEnd = mpEnd;
            if (n < nExtra) {
                CopyInts(oldEnd - n, oldEnd, oldEnd);
                mpEnd += n;
                CopyBackwardInts(position, oldEnd - n, oldEnd);
                FillInt(position, position + n, &temp);
            } else {
                FillNInt(oldEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                CopyInts(position, oldEnd, mpEnd);
                mpEnd += nExtra;
                FillInt(position, oldEnd, &temp);
            }
        }
    } else {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        const unsigned nGrowSize = nPrevSize ? 2 * nPrevSize : 1;
        const unsigned nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
        int* const pNewData = nNewSize ? (int*)NEW_ARRAY_BYTES(nNewSize * sizeof(int)) : 0;
        int* pNewEnd = pNewData;
        for (int* p = mpBegin; p != position; ++p) {
            if (pNewEnd)
                *pNewEnd = *p;
            ++pNewEnd;
        }
        for (unsigned i = n; i > 0; --i) {
            if (pNewEnd)
                *pNewEnd = *value;
            ++pNewEnd;
        }
        for (int* p = position; p != mpEnd; ++p) {
            if (pNewEnd)
                *pNewEnd = *p;
            ++pNewEnd;
        }
        if (mpBegin && mpBegin != mpFixed)
            operator_delete__(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ===========================================================================
// @ 0x0071e390  SP::WriteMesh
// ===========================================================================
struct IStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void Write(const void* data, unsigned size);        // +0x38
};
bool WriteUint16(IStream* s, const void* data, unsigned count, int endian);   // 0x0093a9d0
void WriteUint32(IStream* s, const void* data, unsigned count, int endian);   // 0x0093aa70
void WriteBytes(IStream* s, const void* data, unsigned count);                // 0x0093a9a0 (operator<<)
void WriteHandle(IStream* s, const void* handle);                             // 0x0071dbf0

bool WriteMesh(IStream* stream, Mesh* mesh)
{
    int local_4;
    int local_8;
    int local_c;
    unsigned char local_10[4];

    local_4 = 4;
    if (!WriteUint16(stream, &local_4, 1, 0))
        return false;

    local_4 = (int)(mesh->mpVertEnd - mesh->mpVertBegin) >> 5;
    WriteUint32(stream, &local_4, 1, 0);

    int nVerts = (int)(mesh->mpVertEnd - mesh->mpVertBegin) >> 5;
    if (nVerts > 0) {
        int off = 0;
        local_c = nVerts;
        do {
            char* v = mesh->mpVertBegin + off;
            local_10[0] = *(unsigned char*)v;
            char* v2 = mesh->mpVertBegin + off;
            WriteBytes(stream, local_10, 1);
            local_10[0] = *(unsigned char*)(v2 + 4);
            WriteBytes(stream, local_10, 1);
            local_10[0] = *(unsigned char*)(v2 + 8);
            WriteBytes(stream, local_10, 1);
            local_10[0] = *(unsigned char*)(v2 + 0xc);
            WriteBytes(stream, local_10, 1);
            WriteHandle(stream, v2 + 0x10);
            off += 0x20;
            --local_c;
        } while (local_c != 0);
    }

    local_4 = (int)(mesh->mpEntryEnd - mesh->mpEntryBegin) / 0x8c;
    WriteUint32(stream, &local_4, 1, 0);

    local_4 = (int)(mesh->mpEntryEnd - mesh->mpEntryBegin) / 0x8c;
    if (local_4 > 0) {
        local_c = 0;
        do {
            char* e = mesh->mpEntryBegin + local_c;
            WriteHandle(stream, e);
            local_8 = *(int*)(e + 0x10);
            WriteUint32(stream, &local_8, 1, 0);
            local_10[0] = (unsigned char)((*(int*)(e + 0x18) - *(int*)(e + 0x14)) >> 2);
            WriteBytes(stream, local_10, 1);
            WriteUint16(stream, (void*)*(int*)(e + 0x14), ((*(int*)(e + 0x18) - *(int*)(e + 0x14)) >> 2) * 2, 0);
            local_10[0] = (unsigned char)((*(int*)(e + 0x48) - *(int*)(e + 0x44)) >> 4);
            WriteBytes(stream, local_10, 1);
            int n16 = (*(int*)(e + 0x48) - *(int*)(e + 0x44)) >> 4;
            if (n16 > 0) {
                int o16 = 0;
                local_8 = n16;
                do {
                    WriteHandle(stream, (char*)*(int*)(e + 0x44) + o16);
                    o16 += 0x10;
                    --local_8;
                } while (local_8 != 0);
            }
            local_c += 0x8c;
            --local_4;
        } while (local_4 != 0);
    }

    local_4 = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
    WriteUint32(stream, &local_4, 1, 0);
    stream->Write(mesh->mpPrimBegin, (unsigned)(mesh->mpPrimEnd - mesh->mpPrimBegin) * sizeof(Prim14));
    return true;
}

// ===========================================================================
// @ 0x0071e600  budget walk over primitives; assigns a position record
// ===========================================================================
extern int g_PrimTab5c[10];         // 0x0140cf5c
extern signed char g_PrimTab84[12]; // 0x0140cf84
extern signed char g_PrimTab90[12]; // 0x0140cf90
extern signed char g_PrimTab9c[12]; // 0x0140cf9c

struct PrimCursor {
    RefCounted* mpMesh;             // +0x00
    int mIndex;                     // +0x04
    int mEntry;                     // +0x08
    int mTab5c;                     // +0x0c
    int mOffset;                    // +0x10
    int mSize;                      // +0x14
    int Seek(RefCounted* mesh, int budget);   // 0x0071e600
};

int PrimCursor::Seek(RefCounted* meshRef, int budget)
{
    Mesh* mesh = (Mesh*)meshRef;
    int nEntries = (int)(mesh->mpEntryEnd - mesh->mpEntryBegin) / 0x8c;
    for (int e = 0; e < nEntries; ++e) {
        int nPrims = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
        Prim14* prim = mesh->mpPrimBegin;
        for (int i = 0; i < nPrims; ++i, ++prim) {
            if (prim->mEntry != e)
                continue;
            int type = prim->mType;
            int size;
            if (type > 0 && type < 10) {
                if (type == 9)
                    size = 1;
                else
                    size = (g_PrimTab84[type] - prim->mStart + prim->mEnd) / g_PrimTab90[type];
            } else {
                size = 0;
            }
            if (budget < size) {
                RefCounted* old = mpMesh;
                if (meshRef != old) {
                    meshRef->AddRef();
                    mpMesh = meshRef;
                    if (old)
                        old->Release();
                }
                type = prim->mType;
                if (type > 0 && type < 10)
                    mTab5c = g_PrimTab5c[type];
                else
                    mTab5c = 0;
                mEntry = e;
                mIndex = i;
                type = prim->mType;
                if (type > 0 && type < 10 && type != 6)
                    mOffset = g_PrimTab90[type] * budget + prim->mStart;
                else
                    mOffset = -1;
                type = prim->mType;
                if (type > 0 && type < 10) {
                    if (type != 9)
                        mSize = g_PrimTab9c[type];
                    else
                        mSize = prim->mEnd - prim->mStart;
                } else {
                    mSize = 0;
                }
                return -1;
            }
            budget -= size;
        }
    }
    return budget;
}

// ===========================================================================
// @ 0x0071e7d0  assignment loop over 0x20-byte records with a refcounted pointer
// ===========================================================================
struct AutoRefIRef {                // EA::AutoRefCount<IRef>
    IRef* mp;
    AutoRefIRef& operator=(IRef* p)
    {
        if (p != mp) {
            IRef* const pTemp = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    AutoRefIRef& operator=(const AutoRefIRef& x) { return operator=(x.mp); }
};

struct Rec20 {
    int mF0;                        // +0x00
    int mF4, mF8, mFC, mF10, mF14;  // +0x04 .. +0x14
    short mS18, mS1A;               // +0x18, +0x1a
    AutoRefIRef mRef;               // +0x1c
};

// @ 0x0071e7d0
void CopyRec20(Rec20* first, Rec20* last, Rec20* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
}

// ===========================================================================
// @ 0x0071ec20  indices of 0x20-byte entries matching (a, b, c) filters
// ===========================================================================
struct Mesh20 {
    char pad_00[8];
    char* mpBegin;                  // +0x08
    char* mpEnd;                    // +0x0c
};

void CollectVertexIndices(const Mesh20* c, VecInt* out, int a, int b, int cc)
{
    int n = (int)((c->mpEnd - c->mpBegin) >> 5);
    for (int i = 0; i < n; ++i) {
        if ((a == 0 || a == *(int*)(c->mpBegin + i * 0x20))
            && (b == 0 || b == *(int*)(c->mpBegin + i * 0x20 + 8))
            && (cc == 0xe || cc == *(int*)(c->mpBegin + i * 0x20 + 0xc)))
            out->push_back(i);
    }
}

// ===========================================================================
// @ 0x0071ecc0  indices of 0x20-byte entries whose +0xc equals key
// ===========================================================================
void CollectVertexIndicesByKey(const Mesh20* c, VecInt* out, int key)
{
    int n = (int)((c->mpEnd - c->mpBegin) >> 5);
    for (int i = 0; i < n; ++i) {
        if (*(int*)(c->mpBegin + i * 0x20 + 0xc) == key)
            out->push_back(i);
    }
}

// ===========================================================================
// @ 0x0071ed30  merge a sorted int list into a vector of {short key, short -1} pairs
// ===========================================================================
struct KeyPair {
    short mKey;
    short mVal;
};
struct VecKeyPair {
    KeyPair* mpBegin; KeyPair* mpEnd; KeyPair* mpCapacity;
    void DoInsertValue(KeyPair* position, const KeyPair& v);    // 0x00476fe0
    void push_back(const KeyPair& v)
    {
        if (mpEnd < mpCapacity) {
            KeyPair* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

void MergeKeys(VecKeyPair* vec, int n, const int* keys)
{
    int nExisting = (int)(vec->mpEnd - vec->mpBegin);
    int j = 0;
    int i = 0;
    if (nExisting > 0) {
        do {
            if (j >= n)
                return;
            int cur = vec->mpBegin[i].mKey;
            KeyPair* pos = &vec->mpBegin[i];
            int want = keys[j];
            if (want <= cur) {
                if (cur != want) {
                    KeyPair v;
                    v.mKey = (short)want;
                    v.mVal = (short)-1;
                    if (pos == vec->mpEnd && vec->mpEnd != vec->mpCapacity) {
                        KeyPair* p = vec->mpEnd++;
                        if (p)
                            *p = v;
                    } else {
                        vec->DoInsertValue(pos, v);
                    }
                }
                ++j;
            }
            ++i;
        } while (i < nExisting);
    }
    for (; j < n; ++j) {
        KeyPair v;
        v.mKey = (short)keys[j];
        v.mVal = (short)-1;
        vec->push_back(v);
    }
}

// ===========================================================================
// @ 0x0071ee10  SP::FindPrimitives
// ===========================================================================
struct MeshPrims {
    char pad_00[0x30];
    Prim14* mpPrimBegin;            // +0x30
    Prim14* mpPrimEnd;              // +0x34
};

void FindPrimitives(MeshPrims* mesh, VecInt* out, int typeEntry, int start, int aux)
{
    out->reserve((unsigned)(mesh->mpPrimEnd - mesh->mpPrimBegin));
    if (start == 0 && aux < 0) {
        int n = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
        for (int i = 0; i < n; ++i) {
            if (mesh->mpPrimBegin[i].mEntry == typeEntry)
                out->push_back(i);
        }
    } else {
        int n = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
        for (int i = 0; i < n; ++i) {
            if ((typeEntry == -1 || mesh->mpPrimBegin[i].mEntry == typeEntry)
                && (start == 0 || mesh->mpPrimBegin[i].mType == start)
                && (aux == -1 || mesh->mpPrimBegin[i].mAux == aux))
                out->push_back(i);
        }
    }
}

// ===========================================================================
// 20-byte face clusters (vector<cFaceCluster>)
// ===========================================================================
struct cFaceCluster {               // 0x14 bytes
    int mKind;                      // 4 by default
    int m1, m2, m3, m4;
    cFaceCluster() : mKind(4), m1(0), m2(0), m3(0), m4(0) {}
};
cFaceCluster* UninitCopyFC(cFaceCluster** out, cFaceCluster* first, cFaceCluster* last,
                           cFaceCluster* dest, cFaceCluster* ref);                   // 0x008f05f0
cFaceCluster* UninitFillNFC(cFaceCluster* dest, unsigned n, const cFaceCluster* v,
                            cFaceCluster* ref);                                      // 0x008f0640
cFaceCluster* UninitCopy3FC(cFaceCluster* first, cFaceCluster* last, cFaceCluster* dest); // 0x00951bb0
cFaceCluster* CopyFC(cFaceCluster* first, cFaceCluster* last, cFaceCluster* dest);       // 0x00951bf0
cFaceCluster* CopyBackwardFC(cFaceCluster* first, cFaceCluster* last, cFaceCluster* destEnd); // 0x00c50ad0
void FillFC(cFaceCluster* first, cFaceCluster* last, const cFaceCluster* v);             // 0x00f96e70

struct VecFC {
    cFaceCluster* mpBegin; cFaceCluster* mpEnd; cFaceCluster* mpCapacity;
    void DoInsertValues(cFaceCluster* position, unsigned n, const cFaceCluster* value);   // 0x0071ea40
    void resize(unsigned n);                                                              // 0x0071efa0
};

// @ 0x0071ea40
void VecFC::DoInsertValues(cFaceCluster* position, unsigned n, const cFaceCluster* value)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const cFaceCluster temp = *value;
            cFaceCluster* oldEnd = mpEnd;
            const unsigned nExtra = (unsigned)(oldEnd - position);
            if (n < nExtra) {
                cFaceCluster* r;
                UninitCopyFC(&r, oldEnd - n, oldEnd, oldEnd, position);
                mpEnd += n;
                CopyBackwardFC(position, oldEnd - n, oldEnd);
                FillFC(position, position + n, &temp);
            } else {
                UninitFillNFC(oldEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                cFaceCluster* r;
                UninitCopyFC(&r, position, oldEnd, mpEnd, position);
                mpEnd += nExtra;
                FillFC(position, oldEnd, &temp);
            }
        }
    } else {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        const unsigned nGrowSize = nPrevSize ? 2 * nPrevSize : 1;
        const unsigned nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
        cFaceCluster* const pNewData = nNewSize ? (cFaceCluster*)NEW_ARRAY_BYTES(nNewSize * sizeof(cFaceCluster)) : 0;
        cFaceCluster* pNewEnd = UninitCopy3FC(mpBegin, position, pNewData);
        UninitFillNFC(pNewEnd, n, value, position);
        pNewEnd = UninitCopy3FC(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

void VecFC::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        cFaceCluster v;
        DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), &v);
    } else {
        cFaceCluster* first = mpBegin + n;
        cFaceCluster* last = mpEnd;
        CopyFC(last, mpEnd, first);
        mpEnd -= (last - first);
    }
}

// ===========================================================================
// @ 0x0071f040  update/append a {key, count} pair in an entry, then notify
// ===========================================================================
struct V16 {                        // vector of 16-byte records (begin, end, ...)
    char* mpBegin;
    char* mpEnd;
    void Notify(int arg);           // 0x006da2e0
    int size() const { return (int)(mpEnd - mpBegin) >> 4; }
};
struct EntryFor70 {                 // 0x8c bytes
    char pad_00[0x14];
    VecKeyPair mPairs;              // +0x14
    char pad_20[0x44 - 0x20];
    V16 mRecs;                      // +0x44
    char pad_4c[0x8c - 0x4c];
};
struct MeshEntries {
    char pad_00[0x1c];
    EntryFor70* mpEntries;          // +0x1c
};
int FindPairIndex(MeshEntries* m, int entry, int key);              // 0x0071e040

// @ 0x0071f040
void SetEntryKey(MeshEntries* m, int entry, int key, int arg)
{
    EntryFor70* e = &m->mpEntries[entry];
    int idx = FindPairIndex(m, entry, key);
    V16& recs = e->mRecs;
    if (idx >= 0) {
        e->mPairs.mpBegin[idx].mVal = (short)recs.size();
        recs.Notify(arg);
        return;
    }
    KeyPair v;
    v.mKey = (short)key;
    v.mVal = (short)recs.size();
    e->mPairs.push_back(v);
    recs.Notify(arg);
}

// ===========================================================================
// @ 0x0071f0f0  find-or-add a 0x20-byte vertex record; returns its index
// ===========================================================================
struct VertexKey {                  // temporary built by FUN_00469500 (5 args)
    unsigned mA, mB, mC, mD;
    Handle mHandle;
    VertexKey(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e);   // 0x00469500
    ~VertexKey() { if (mHandle.mpRef) mHandle.mpRef->Release(); }
};
struct VertexVec {
    char* mpBegin;
    char* mpEnd;
    void push_back(const VertexKey& v);                                      // 0x0041f7d0
};
struct VertexMesh {
    char pad_00[8];
    VertexVec mVerts;               // +0x08
};
int FindVertexIndex(VertexMesh* m, unsigned a, unsigned b, unsigned c, int d);   // 0x0071ddc0

inline void CopyVertex(Vertex20* dst, const VertexKey& src)
{
    dst->mA = src.mA;
    dst->mB = src.mB;
    dst->mC = src.mC;
    dst->mD = src.mD;
    dst->mHandle.Assign(&src.mHandle);
}

// @ 0x0071f0f0
int AddVertex(VertexMesh* mesh, unsigned a, unsigned b, unsigned c, unsigned d, unsigned e)
{
    int idx = FindVertexIndex(mesh, a, b, c, 0xe);
    if (idx < 0) {
        idx = (int)(mesh->mVerts.mpEnd - mesh->mVerts.mpBegin) >> 5;
        mesh->mVerts.push_back(VertexKey(a, b, c, d, e));
    } else {
        CopyVertex((Vertex20*)(mesh->mVerts.mpBegin + idx * 0x20), VertexKey(a, b, c, d, e));
    }
    return idx;
}

// ===========================================================================
// @ 0x0071f300  assignment loop over 0x8c-byte entries
// ===========================================================================
struct FixedIdVec {                 // 3 pointers followed by allocator data
    int* mpBegin; int* mpEnd; int* mpCap;
    void DoAssign(int* first, int* last, void* owner);                       // 0x0042cd50
    void erase(int* first, int* last)
    {
        int* d = first;
        for (int* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd -= (last - first);
    }
};
struct FixedEntryVec {
    char* mpBegin; char* mpEnd; char* mpCap;
    void Erase(char* first, char* last);                                     // 0x004772a0
    void DoAssign(char* first, char* last, void* owner);                     // 0x0042d020
};
struct EntryCopy {                  // 0x8c bytes
    int mF0, mF4;
    short mS8, mSA;
    AutoRefIRef mRef;               // +0x0c
    int mF10;
    FixedIdVec mIds;                // +0x14
    char pad_20[0x44 - 0x20];
    FixedEntryVec mEntries;         // +0x44
    char pad_50[0x8c - 0x50];
};

void CopyEntries(EntryCopy* first, EntryCopy* last, EntryCopy* src)
{
    for (; first != last; ++first, ++src) {
        first->mF0 = src->mF0;
        first->mF4 = src->mF4;
        first->mS8 = src->mS8;
        first->mSA = src->mSA;
        first->mRef = src->mRef;
        first->mF10 = src->mF10;
        if (&first->mIds != &src->mIds) {
            first->mIds.erase(first->mIds.mpBegin, first->mIds.mpEnd);
            first->mIds.DoAssign(src->mIds.mpBegin, src->mIds.mpEnd, first);
        }
        if (&first->mEntries != &src->mEntries) {
            first->mEntries.Erase(first->mEntries.mpBegin, first->mEntries.mpEnd);
            first->mEntries.DoAssign(src->mEntries.mpBegin, src->mEntries.mpEnd, first);
        }
    }
}
