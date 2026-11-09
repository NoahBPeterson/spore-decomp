// src/game/SPEngine/SPGraphicsMeshData.cpp -- migrated from slice(s) s0071e390, s0071d550 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMeshData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include <intrin.h>

// ---- items of slice s0071e390 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_PrimTab5c[10];         // 0x0140cf5c
extern signed char g_PrimTab84[12]; // 0x0140cf84
extern signed char g_PrimTab90[12]; // 0x0140cf90
extern signed char g_PrimTab9c[12]; // 0x0140cf9c
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
typedef unsigned int size_t_;
void* operator_new(size_t_ n, const char* name, int, int, const char* file, int line);   // 0x00f473a0
void  operator_delete__(void* p);                                                         // 0x00f47380
#define NEW_ARRAY_BYTES(n) operator_new((n), "Graphics", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL\\allocator.h", 0xd1)
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
struct Prim14 {                     // 0x14 bytes
    int mType;                      // +0x00
    int mEntry;                     // +0x04
    int mStart;                     // +0x08
    int mEnd;                       // +0x0c
    int mAux;                       // +0x10
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
struct IStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void Write(const void* data, unsigned size);        // +0x38
};
bool WriteUint16(IStream* s, const void* data, unsigned count, int endian);   // 0x0093a9d0
void WriteUint32(IStream* s, const void* data, unsigned count, int endian);   // 0x0093aa70
void WriteBytes(IStream* s, const void* data, unsigned count);                // 0x0093a9a0 (operator<<)
void WriteHandle(IStream* s, const void* handle);                             // 0x0071dbf0
struct PrimCursor {
    RefCounted* mpMesh;             // +0x00
    int mIndex;                     // +0x04
    int mEntry;                     // +0x08
    int mTab5c;                     // +0x0c
    int mOffset;                    // +0x10
    int mSize;                      // +0x14
    int Seek(RefCounted* mesh, int budget);   // 0x0071e600
};
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
struct Mesh20 {
    char pad_00[8];
    char* mpBegin;                  // +0x08
    char* mpEnd;                    // +0x0c
};
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
struct MeshPrims {
    char pad_00[0x30];
    Prim14* mpPrimBegin;            // +0x30
    Prim14* mpPrimEnd;              // +0x34
};
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
cFaceCluster* CopyBackwardFC(cFaceCluster* first, cFaceCluster* last, cFaceCluster* destEnd); // 0x00c50ad0
void FillFC(cFaceCluster* first, cFaceCluster* last, const cFaceCluster* v);             // 0x00f96e70
struct VecFC {
    cFaceCluster* mpBegin; cFaceCluster* mpEnd; cFaceCluster* mpCapacity;
    void DoInsertValues(cFaceCluster* position, unsigned n, const cFaceCluster* value);   // 0x0071ea40
    void resize(unsigned n);                                                              // 0x0071efa0
};
// ---- items of slice s0071e390 end

// ---- items of slice s0071d550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
extern const int8_t g_secTabA[];   // 0x0140cf84
extern const int8_t g_secTabB[];   // 0x0140cf90
#pragma intrinsic(sin, cos, fabs)
struct Stream {                 // vertex/index stream
    int      count;             // +0x00
    char*    data;              // +0x04
    uint16_t format;            // +0x08
    uint16_t stride;            // +0x0A
    int      unk0c;             // +0x0C
};
struct ModelStreamEntry {       // 0x20 bytes
    int    semantic;            // +0x00
    int    usageIdx;            // +0x04
    int    number;              // +0x08
    int    type;                // +0x0C
    Stream stream;              // +0x10
};
struct StreamRef {              // 4 bytes
    short stream;               // +0x00 index into the model's stream array
    short remap;                // +0x02
};
struct Mesh_s0071_d550 {                   // 0x8C bytes
    Stream      mIndices;       // +0x00
    uint32_t    pad10;          // +0x10
    StreamRef*  mStreamMap;     // +0x14
    StreamRef*  mStreamMapEnd;  // +0x18
    uint32_t    pad1c[28];      // +0x1C .. +0x8C
};
struct Sec14 {                  // 0x14 bytes
    int type;                   // +0x00
    int idx;                    // +0x04
    int f8;                     // +0x08
    int fC;                     // +0x0C
    int f10;                    // +0x10
};
struct Model {
    uint32_t          pad00[2];       // +0x00
    ModelStreamEntry* mStreamsBegin;  // +0x08
    ModelStreamEntry* mStreamsEnd;    // +0x0C
    uint32_t          pad10[3];       // +0x10 .. +0x1C
    Mesh_s0071_d550*             mMeshesBegin;   // +0x1C
    Mesh_s0071_d550*             mMeshesEnd;     // +0x20
    uint32_t          pad24[3];       // +0x24 .. +0x30
    Sec14*            mSecBegin;      // +0x30
    Sec14*            mSecEnd;        // +0x34

    int sumSection();                 // 0x0071dcc0
};
struct Obj13 {
    char pad_00[0x1c];
    char* mBase;        // +0x1c
    bool func_dc90(int idx);
    int  findShort(int idx, int key);
};
struct VecDescr {
    char pad_00[8];
    char* mpBegin;          // +0x08
    char* mpEnd;            // +0x0c
    char* mpCapacity;       // +0x10
};
struct Vector3 { float x, y, z; };
struct Rend {
    virtual void v0() = 0;                          // +0x00
    virtual void v1() = 0;                          // +0x04
    virtual void v2() = 0;                          // +0x08
    virtual void v3() = 0;                          // +0x0C
    virtual void v4() = 0;                          // +0x10
    virtual void v5() = 0;                          // +0x14
    virtual void v6(Vector3* p) = 0;                // +0x18
    virtual void v7(Vector3* p) = 0;                // +0x1C
    virtual void v8(Vector3* p, int n) = 0;         // +0x20
    virtual void v9() = 0;                          // +0x24
    virtual void v10() = 0;                         // +0x28
    virtual void v11() = 0;                         // +0x2C
    virtual void v12() = 0;                         // +0x30
    virtual void v13() = 0;                         // +0x34
    virtual void v14(const void* p, int n) = 0;     // +0x38
    virtual void v15() = 0;                         // +0x3C
    virtual void v16() = 0;                         // +0x40
    virtual void v17() = 0;                         // +0x44
    virtual void v18() = 0;                         // +0x48
    virtual void v19(int n) = 0;                    // +0x4C
    virtual void v20(int n) = 0;                    // +0x50
    virtual void v21(int n) = 0;                    // +0x54
    virtual void v22(int n) = 0;                    // +0x58
    virtual void v23() = 0;                         // +0x5C
    virtual void v24() = 0;                         // +0x60
    virtual void v25(int a, int b) = 0;             // +0x64
    virtual void v26() = 0;                         // +0x68
    virtual void v27() = 0;                         // +0x6C
    virtual void v28() = 0;                         // +0x70
    virtual void v29() = 0;                         // +0x74
    virtual void v30() = 0;                         // +0x78
    virtual void v31() = 0;                         // +0x7C
    virtual void v32(int n) = 0;                    // +0x80
    virtual void v33() = 0;                         // +0x84
    virtual void v34() = 0;                         // +0x88
    virtual void v35(int a, int b, float f) = 0;    // +0x8C
};
bool __cdecl WriteUint32(Rend* s, const uint32_t* p, uint32_t n, int flags);   // 0x0093aa70
bool __cdecl WriteUint16(Rend* s, const uint16_t* p, uint32_t n, int flags);   // 0x0093a9d0
struct IntVec {                    // eastl-style vector of ints (8 bytes)
    int* mpBegin;                  // +0x00
    int* mpEnd;                    // +0x04
};
bool __cdecl ReadInt32(void* s, void* p, int n, int flags);     // 0x0093a780
bool __cdecl ReadUint16(void* s, uint16_t* p, int n, int flags); // 0x0093a700
bool __cdecl ReadBytes(void* s, void* p, uint32_t n);           // 0x0093a6c0
bool __cdecl HasRoom(void* s, int elemSize, int count);         // 0x0093a890
void __cdecl Obj15_Init(void* p);                               // 0x00720070
// ---- items of slice s0071d550 end

// @ 0x0071dbf0
bool __cdecl WriteStream(Rend* w, const Stream* s)
{
    uint32_t count = s->count;
    WriteUint32(w, &count, 1, 0);
    uint16_t format = s->format;
    WriteUint16(w, &format, 1, 0);
    if (s->data) {
        if (s->format == s->stride) {
            w->v14(s->data, s->format * s->count);
            return true;
        }
        for (int i = 0; i < s->count; ++i)
            w->v14(s->data + s->stride * i, s->format);
    }
    return true;
}

// @ 0x0071dc90
bool Obj13::func_dc90(int idx)
{
    int* p = (int*)(mBase + idx * 0x8c + 0x44);
    return p[0] != p[1];
}

// @ 0x0071dcc0
int Model::sumSection()
{
    int total = 0;
    int numMeshes = (int)(mMeshesEnd - mMeshesBegin);
    if (numMeshes > 0) {
        int meshIdx = 0;
        do {
            int numSec = (int)(mSecEnd - mSecBegin);
            if (numSec > 0) {
                Sec14* p = mSecBegin;
                int j = numSec;
                do {
                    if (p->idx == meshIdx) {
                        int t = p->type;
                        if (t < 1 || t > 9)
                            t = 0;
                        else if (t == 9)
                            t = 1;
                        else
                            t = ((int)g_secTabA[t] - p->f8 + p->fC) / (int)g_secTabB[t];
                        total += t;
                    }
                    ++p;
                } while (--j);
            }
            ++meshIdx;
        } while (meshIdx < numMeshes);
    }
    return total;
}

// @ 0x0071dd80
int Vec20_find(const VecDescr* v, uint32_t key)
{
    int n = (int)((v->mpEnd - v->mpBegin) >> 5);
    const char* begin = v->mpBegin;
    for (int i = 0; i < n; ++i)
        if (*(const uint32_t*)(begin + i * 0x20 + 0xc) == key)
            return *(const int*)(begin + i * 0x20 + 0x10);
    return 0;
}

// @ 0x0071ddc0
int __cdecl FindStreamEntry(const Model* m, int semantic, int usageIdx, int number, int type)
{
    int n = (int)(m->mStreamsEnd - m->mStreamsBegin);
    if (n > 0) {
        const ModelStreamEntry* e = m->mStreamsBegin;
        int i = 0;
        do {
            if ((semantic == 0 || e->semantic == semantic) &&
                (usageIdx == -1 || e->usageIdx == usageIdx) &&
                (number == 0 || e->number == number)) {
                if (type == 0xe)
                    return i;
                if (e->type == type)
                    return i;
            }
            ++i;
            ++e;
        } while (i < n);
    }
    return -1;
}

// @ 0x0071de40
Stream* __cdecl FindStream(const Model* m, int semantic, int usageIdx, int number, int type)
{
    int n = (int)(m->mStreamsEnd - m->mStreamsBegin);
    if (n > 0) {
        const ModelStreamEntry* e = m->mStreamsBegin;
        int i = 0;
        do {
            if ((semantic == 0 || e->semantic == semantic) &&
                (usageIdx < 0 || e->usageIdx == usageIdx) &&
                (number == 0 || e->number == number) &&
                (type == 0xe || e->type == type))
                return (Stream*)&e->stream;
            ++i;
            ++e;
        } while (i < n);
    }
    return (Stream*)0x162aa80;
}

// @ 0x0071ded0
bool __cdecl SelectStreams(const Model* m, int count, int* out, const int* semantics, const int* usageIndex, const int* numbers, const int* types)
{
    int nStreams = (int)(m->mStreamsEnd - m->mStreamsBegin);
    int found = 0;
    if (count > 0) {
        int k = 0;
        do {
            bool matched = false;
            if (nStreams < 1) {
                out[k] = -1;
                ++k;
            } else {
                int i = 0;
                do {
                    const ModelStreamEntry* e = &m->mStreamsBegin[i];
                    if ((semantics == 0 || semantics[k] == 0 || e->semantic == semantics[k]) &&
                        (usageIndex == 0 || usageIndex[k] == -1 || e->usageIdx == usageIndex[k]) &&
                        (numbers == 0 || numbers[k] == 0 || e->number == numbers[k]) &&
                        (types == 0 || types[k] == 0xe || m->mStreamsBegin[k].type == types[k])) {
                        out[k] = i;
                        ++found;
                        ++k;
                        matched = true;
                        if (k == count)
                            break;
                    }
                    ++i;
                } while (i < nStreams);
                if (!matched) {
                    out[k] = -1;
                    ++k;
                }
            }
        } while (k < count);
    }
    return found == count;
}

// @ 0x0071e040
int Obj13_findShort(Obj13* self, int idx, int key)
{
    int* p = (int*)(self->mBase + idx * 0x8c + 0x14);
    const short* q = (const short*)p[0];
    int n = (int)((p[1] - (int)q) >> 2);
    const short* ps = q;
    for (int i = 0; i < n; ++i, ps += 2)
        if (*ps == key)
            return i;
    return -1;
}

// @ 0x0071e090
int __cdecl FindMeshStreamIndex(const Model* m, int meshIndex, int semantic, int usageIdx, int number)
{
    const Mesh_s0071_d550* mesh = m->mMeshesBegin + meshIndex;
    const StreamRef* ref = mesh->mStreamMap;
    int n = (int)(mesh->mStreamMapEnd - ref);
    if (n > 0) {
        const ModelStreamEntry* streams = m->mStreamsBegin;
        int i = 0;
        do {
            const ModelStreamEntry* e = &streams[ref->stream];
            if ((semantic == 0 || e->semantic == semantic) &&
                (number == 0 || e->number == number)) {
                if (usageIdx == -1)
                    return i;
                if (e->usageIdx == usageIdx)
                    return i;
            }
            ++i;
            ++ref;
        } while (i < n);
    }
    return -1;
}

// @ 0x0071e110
bool __cdecl FindMeshStreams(const Model* m, int meshIndex, int count, const int* semantics, const int* usageIndex, const int* formats, int* outIdx)
{
    const Mesh_s0071_d550* mesh = m->mMeshesBegin + meshIndex;
    const StreamRef* ref = mesh->mStreamMap;
    int nRefs = (int)(mesh->mStreamMapEnd - ref);
    const ModelStreamEntry* streams = m->mStreamsBegin;
    int found = 0;
    if (count > 0) {
        int k = 0;
        do {
            bool matched = false;
            if (nRefs < 1) {
                outIdx[k] = -1;
                ++k;
            } else {
                int i = 0;
                do {
                    const ModelStreamEntry* e = &streams[ref[i].stream];
                    if ((semantics == 0 || semantics[k] == 0 || e->semantic == semantics[k]) &&
                        (formats == 0 || formats[k] == 0 || e->number == formats[k]) &&
                        (usageIndex == 0 || usageIndex[k] == -1 || e->usageIdx == usageIndex[k])) {
                        outIdx[k] = i;
                        ++found;
                        ++k;
                        matched = true;
                        if (k == count)
                            break;
                    }
                    ++i;
                } while (i < nRefs);
                if (!matched) {
                    outIdx[k] = -1;
                    ++k;
                }
            }
        } while (k < count);
    }
    return found == count;
}

// @ 0x0071e230
bool __cdecl MatchingIndices(const IntVec* v, int limit, const int* keys, int* out)
{
    int i = 0;
    int n = (int)(v->mpEnd - v->mpBegin);
    int count = 0;
    for (; i < n; ++i) {
        if (count >= limit)
            break;
        if ((short)v->mpBegin[i] == keys[count]) {
            if (out)
                out[count] = i;
            ++count;
        }
    }
    return count == limit;
}

// @ 0x0071e290
char __cdecl Obj13_e290(void* stream, void* self)
{
    int* p = (int*)self;
    if (ReadInt32(stream, p, 1, 0)) {
        uint16_t* format = (uint16_t*)(p + 2);
        if (ReadUint16(stream, format, 1, 0)) {
            *(uint16_t*)((char*)p + 10) = *format;
            p[3] = 0;
            _ReadWriteBarrier();
            int count = p[0];
            p[1] = 0;
            if (count > 0) {
                if (HasRoom(stream, *format, count)) {
                    Obj15_Init(p);
                    uint32_t c = (uint32_t)p[0];
                    uint32_t n = (uint32_t)*format;
                    self = (void*)p[1];
                    if (ReadBytes(stream, self, n * c))
                        return 1;
                }
            } else {
                return 1;
            }
        }
    }
    return 0;
}

// @ 0x0071e320
char __cdecl Obj13_e320(void* stream, void* self)
{
    int* p = (int*)self;
    if (!ReadBytes(stream, p, 0x10))
        return 0;
    p[3] = 0;
    _ReadWriteBarrier();
    int count = p[0];
    p[1] = 0;
    if (count > 0) {
        uint16_t* format = (uint16_t*)(p + 2);
        if (!HasRoom(stream, *format, count))
            return 0;
        Obj15_Init(p);
        uint32_t c = (uint32_t)p[0];
        uint32_t n = (uint32_t)*format;
        self = (void*)p[1];
        if (!ReadBytes(stream, self, n * c))
            return 0;
    }
    return 1;
}

// @ 0x0071e390
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

// @ 0x0071e5e0
void FillInt(int* first, int* last, const int* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// @ 0x0071e600
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

// @ 0x0071e7a0
void FillNInt(int* first, unsigned n, const int* value)
{
    int* p = first;
    if (n == 0) return;
    do {
        if (p)
            *p = *value;
        ++p;
    } while (--n);
}

// @ 0x0071e7d0
void CopyRec20(Rec20* first, Rec20* last, Rec20* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
}

// @ 0x0071e870
void VecInt::DoInsertValues(int* position, unsigned n, const int* value)
{
    // A function-scope `volatile` local gives this function the extra 4-byte frame
    // slot the original has: cl 15.00 emits `push ecx`/`pop ecx`, so the entry
    // `this` in ecx survives (the original never leaves ecx clobbered; the caller
    // at 0072f326 is `or ecx,-1`, i.e. it does not read it, but the harness compares
    // every register the original leaves untouched).
    volatile unsigned nNewSize;
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
        nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
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

// @ 0x0071ec20
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

// @ 0x0071ecc0
void CollectVertexIndicesByKey(const Mesh20* c, VecInt* out, int key)
{
    int n = (int)((c->mpEnd - c->mpBegin) >> 5);
    for (int i = 0; i < n; ++i) {
        if (*(int*)(c->mpBegin + i * 0x20 + 0xc) == key)
            out->push_back(i);
    }
}

// @ 0x0071ed30
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
        KeyPair v2;
        v2.mKey = (short)keys[j];
        v2.mVal = (short)-1;
        vec->push_back(v2);
    }
}

// @ 0x0071ee10
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
