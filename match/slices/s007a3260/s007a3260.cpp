// slice s007a3260: static buffer draw (SP::cStaticBuffer / cStaticBufferDraw) and a mesh pair-list builder.
// Flags: cl 15.00 /O2 /MD /Gy /EHsc /TP
#include <intrin.h>
#include <new>
#include "types.h"
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---------------------------------------------------------------------------------------------
// Intrusive refcounted object: vtable slot 0 = deleting destructor, refcount at +4.
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
};
static inline void AddRef(RefObj* p) { _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, 1); }
static inline void ReleaseRefObj(RefObj* p) {
    if (p) {
        int n = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (n - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}

// Smart pointer around RefObj (sp<T>).
struct RefPtr {
    RefObj* mp;
    RefPtr() : mp(0) {}
    RefPtr(RefObj* p) : mp(p) { if (mp) AddRef(mp); }
    RefPtr(const RefPtr& o) : mp(o.mp) { if (mp) AddRef(mp); }
    ~RefPtr() { ReleaseRefObj(mp); }
};

// (smart pointer, tag) entry; 8 bytes.
struct Entry {
    RefPtr ref;
    int mTag;
    Entry(const RefPtr& r, int t) : ref(r), mTag(t) {}
};

// Plain (key, tag) pair as produced by the source list.
struct KeyTag {
    int mKey;
    int mTag;
};

extern "C" void __cdecl operator_delete__(void* p);   // 0x00f47380 (array delete)
extern "C" void EXT_f47380();

struct EntryVec;
// 0x0079f4e0: slow path of push_back (insert at pos).
// 0x0079af80: reserve(n).
struct EntryVec {
    Entry* mpBegin;
    Entry* mpEnd;
    Entry* mpCapacity;
    int mAllocator[2];
    void reserve(int n);                                 // 0x0079af80
    void DoInsertValue(Entry* pos, const Entry& v);      // 0x0079f4e0
    void push_back(const Entry& v) {
        if (mpEnd < mpCapacity) {
            Entry* p = mpEnd++;
            if (p)
                new (p) Entry(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

struct KeyTagVec {
    KeyTag* mpBegin;
    KeyTag* mpEnd;
    KeyTag* mpCapacity;
    int mAllocator[2];
};

// vector<KeyTagVec>; 0x007a0b90 fills it, 0x0079b0d0 destroys [begin,end).
struct KeyTagVecVec {
    KeyTagVec* mpBegin;
    KeyTagVec* mpEnd;
    KeyTagVec* mpCapacity;
    void Fill(void* src);                                // 0x007a0b90
    void DestroyRange(KeyTagVec* b, KeyTagVec* e);       // 0x0079b0d0
    ~KeyTagVecVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

// Output: vector<EntryVec>; 0x007a1100 resizes it.
struct EntryVecVec {
    EntryVec* mpBegin;
    void resize(int n);                                  // 0x007a1100
};

// Per-key gather result (0x70 bytes); two smart pointers at +0/+4, rest is sub-state.
struct GatherResult {
    RefPtr a;            // +0
    RefPtr b;            // +4
    int w[4];            // +8
    int _pad18[2];
    int x[3];            // +0x20
    int _pad2c[2];
    int c34;             // +0x34
    int y[4];            // +0x38
    int z[3];            // +0x48
    int _pad54[2];
    int c5c;             // +0x5c
    int t[4];            // +0x60
    __forceinline GatherResult() {
        a.mp = 0; b.mp = 0;
        w[0] = w[1] = w[2] = w[3] = 0;
        x[0] = x[1] = x[2] = 0;
        c34 = 4;
        y[0] = y[1] = y[2] = y[3] = 0;
        z[0] = z[1] = z[2] = 0;
        c5c = 4;
        t[0] = t[1] = t[2] = t[3] = 0;
    }
    ~GatherResult();                                     // 0x0079aeb0
};

struct MeshBuilder {
    void GatherA(int key, GatherResult* r1, GatherResult* r2);   // 0x007a1f40
    void GatherB(int key, GatherResult* r1, GatherResult* r2);   // 0x007a2180

    template <void (MeshBuilder::*Gather)(int, GatherResult*, GatherResult*)>
    __forceinline void Build(EntryVecVec* out) {
        KeyTagVecVec src;
        src.mpBegin = src.mpEnd = src.mpCapacity = 0;
        src.Fill(out);
        GatherResult r1;
        GatherResult r2;
        int n = (int)(src.mpEnd - src.mpBegin);
        out->resize(n * 2);
        KeyTagVec* sv = src.mpBegin;
        int off = 0;
        for (int i = 0; i < n; ++i, ++sv, off += 2) {
            EntryVec* v0 = out->mpBegin + off;
            EntryVec* v1 = v0 + 1;
            int count = (int)(sv->mpEnd - sv->mpBegin);
            v0->reserve(count);
            v1->reserve(count);
            for (int j = 0; j < (int)(sv->mpEnd - sv->mpBegin); ++j) {
                KeyTag* e = &sv->mpBegin[j];
                (this->*Gather)(e->mKey, &r1, &r2);
                if (r1.a.mp) { Entry t(r1.a, e->mTag); v0->push_back(t); }
                if (r1.b.mp) { Entry t(r1.b, e->mTag); v0->push_back(t); }
                if (r2.a.mp) { Entry t(r2.a, e->mTag); v1->push_back(t); }
                if (r2.b.mp) { Entry t(r2.b, e->mTag); v1->push_back(t); }
            }
        }
    }

    void BuildPairListsA(EntryVecVec* out);
    void BuildPairListsB(EntryVecVec* out);
};

// @ 0x007a3260
void MeshBuilder::BuildPairListsA(EntryVecVec* out) { Build<&MeshBuilder::GatherA>(out); }

// @ 0x007a37a0
void MeshBuilder::BuildPairListsB(EntryVecVec* out) { Build<&MeshBuilder::GatherB>(out); }

// ---------------------------------------------------------------------------------------------
// cStaticBufferDraw singleton
struct cStaticBufferDraw;
extern cStaticBufferDraw* gStaticBufferDraw;                  // 0x015ddc84
void __fastcall FUN_006de2a0(void* self);          // base-class setup (SingletonBase)
extern "C" int __cdecl FUN_007c3af0(const char* fmt);         // vertex-format lookup by name

// EA::SingletonBase<cStaticBufferDraw>: registers the instance; has an out-of-line dtor (so the ctor gets an EH frame).
struct SingletonBaseStub {
    SingletonBaseStub(cStaticBufferDraw* p) { gStaticBufferDraw = p; }
    ~SingletonBaseStub();
};

struct cStaticBufferDraw : SingletonBaseStub {
    int mStaticBuffer;       // +0x00
    int mField04;
    int mField08;
    int mField0c;
    int mField10;
    int mField14;
    int mField18;
    int mField1c;
    char mField20;
    char _pad21[3];
    int mField24;
    int mField28;
    int mField2c;
    int mField30;
    char _pad34[12];
    char mField40;
    char _pad41[3];
    int mVertexDesc;         // +0x44

    cStaticBufferDraw();
    void SetVertexFormat(int fmt);
    static void sInstanceReset();
};

cStaticBufferDraw* gStaticBufferDraw;

// @ 0x007a3de0
void cStaticBufferDraw::sInstanceReset() { gStaticBufferDraw = 0; }

// @ 0x007a3df0
cStaticBufferDraw::cStaticBufferDraw() : SingletonBaseStub(this) {
    mStaticBuffer = 0;
    mField04 = 0;
    mField08 = 0;
    mField0c = 0;
    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1c = 0;
    mField20 = 0;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mField30 = 0;
    mField40 = 0;
    FUN_006de2a0(this);
}

// @ 0x007a3ce0
extern char gVertexFormatsDirty;       // 0x0153b690 (starts nonzero)
extern int gVertexFormats[12];         // 0x01634770
void cStaticBufferDraw::SetVertexFormat(int fmt) {
    if (gVertexFormatsDirty) {
        gVertexFormatsDirty = 0;
        gVertexFormats[0] = FUN_007c3af0("V3FC4B");
        gVertexFormats[1] = FUN_007c3af0("V3FT2F");
        gVertexFormats[2] = FUN_007c3af0("V3FC4BT2F");
        gVertexFormats[3] = FUN_007c3af0("V3FC4BT3F");
        gVertexFormats[4] = FUN_007c3af0("V3FN3FC4BT2F");
        gVertexFormats[5] = FUN_007c3af0("V3FC4BP1F");
        gVertexFormats[6] = FUN_007c3af0("V4FN4FC4BT2F");
        gVertexFormats[7] = FUN_007c3af0("V4FN4FC4BC4B");
        gVertexFormats[8] = FUN_007c3af0("V4FN4FG3FC4BC4B");
        gVertexFormats[9] = FUN_007c3af0("V4FN3FC4BT4FT4FT4FT4FT4F");
        gVertexFormats[10] = FUN_007c3af0("V3FC4BT2FT2FT2F");
        gVertexFormats[11] = FUN_007c3af0("V4FN4FC4BC4BT4B");
    }
    mVertexDesc = gVertexFormats[fmt];
}

// ---------------------------------------------------------------------------------------------
// SP::cStaticBuffer::Dispatch
struct ShaderData;
extern "C" void __cdecl pushShaderDataNull();                 // 0x00777bf0
extern "C" void __cdecl SetShaderData(ShaderData* sd);        // 0x00777b50
extern "C" void __cdecl pushShaderDataPop();                  // 0x00777c10
struct CompiledState { void Dispatch(); };                    // 0x011ee580 (rw::graphics::CompiledState)
extern "C" void __cdecl D3D9Sync();                           // 0x011f21a0
extern "C" int __cdecl VertexDescriptorAreEqual(int a, int b);// 0x011f2e70
extern "C" void __fastcall FUN_011f2bc0(int desc);            // applies the vertex descriptor

struct D3DDevice { void** vt; };
typedef long (__stdcall* DrawPrimFn)(D3DDevice*, int type, int start, int count);
typedef long (__stdcall* DrawIdxFn)(D3DDevice*, int type, int baseVertex, int minIndex, int numVerts, int startIndex, int primCount);
typedef long (__stdcall* SetStreamFn)(D3DDevice*, int stream, int vb, int offset, int stride);
typedef long (__stdcall* SetIndicesFn)(D3DDevice*, int ib);

struct Stream { int vb; int offset; int stride; };
struct DrawStats { char _pad[0x20]; int mVerts; int mTris; int mBatches; };
struct RendererFns { char _pad[0x14]; int (__cdecl* IsReady)(int); };

struct StaticBatch {          // 24-byte draw record
    int mBuffer;              // +0x00 index into mpBuffers
    int mStart;               // +0x04
    int mCount;               // +0x08
    int mIndexSet;            // +0x0c (<0 = none)
    int mIndexOffset;         // +0x10
    int mIndexCount;          // +0x14
};
struct BufferInfo { char* mpDesc; int mVB; int mOffset; };   // mpDesc+0x0f = stride
struct IndexInfo { int mIB; int mBase; };

struct cStaticBuffer {
    char _pad0[8];
    BufferInfo** mpBuffers;       // +0x08
    char _pad0c[0x10];
    IndexInfo** mpIndexSets;      // +0x1c
    char _pad20[0x10];
    StaticBatch* mpBatchBegin;    // +0x30
    StaticBatch* mpBatchEnd;      // +0x34
    char _pad38[0x10];
    int mPrimType;                // +0x48
    void Dispatch(DrawStats* stats, ShaderData* sd);
};

extern int gCurVertexDesc;          // 0x016f65a0
extern unsigned gDirtyFlags;        // 0x016f9110
extern Stream gStreams[3];          // 0x016f9144 (streams 1..3)
extern Stream gStream0;             // 0x016f9138
extern int gCurIndexBuffer;         // 0x016f8afc
extern RendererFns* gRendererFns;   // 0x016f6568
extern int gRendererArg;            // 0x016079a0
extern IndexInfo* gDefaultIndexSet; // 0x016079a4
extern D3DDevice* gDevice;          // 0x016f89d0

// @ 0x007a3e60
void cStaticBuffer::Dispatch(DrawStats* stats, ShaderData* sd) {
    if (sd) {
        pushShaderDataNull();
        SetShaderData(sd);
        ((CompiledState*)sd)->Dispatch();
        D3D9Sync();
    }
    int desc = *(int*)((char*)this + 0x44);
    if (!gCurVertexDesc || !VertexDescriptorAreEqual(gCurVertexDesc, desc))
        gDirtyFlags |= 0x100000;
    gCurVertexDesc = desc;
    FUN_011f2bc0(desc);
    int (__cdecl* isReady)(int) = gRendererFns->IsReady;
    if (!isReady(gRendererArg))
        return;

    D3DDevice* dev = gDevice;
    gDirtyFlags = 0;
    for (int stream = 1; stream < 4; ++stream) {
        Stream* s = &gStreams[stream - 1];
        if (s->vb) {
            ((SetStreamFn)dev->vt[0x190 / 4])(dev, stream, 0, 0, 0);
            s->vb = 0;
            s->offset = 0;
            s->stride = 0;
        }
    }

    if ((int)(mpBatchEnd - mpBatchBegin) > 0) {
        int count = (int)(mpBatchEnd - mpBatchBegin);
        int off = 0;
        for (; count; --count, off += sizeof(StaticBatch)) {
            StaticBatch* b = (StaticBatch*)((char*)mpBatchBegin + off);
            BufferInfo* buf = mpBuffers[b->mBuffer];
            int baseVertex = buf->mOffset;
            IndexInfo* idx = 0;
            if (b->mIndexSet >= 0)
                idx = mpIndexSets[b->mIndexSet];
            int vb = buf->mVB;
            int stride = (unsigned char)buf->mpDesc[0xf];
            if (gStream0.vb != vb || gStream0.offset != 0 || gStream0.stride != stride) {
                ((SetStreamFn)dev->vt[0x190 / 4])(dev, 0, vb, 0, stride);
                gStream0.vb = vb;
                gStream0.offset = 0;
                gStream0.stride = stride;
            }
            int ib = 0;
            int startIndex = 0;
            if (mPrimType == 3) {
                IndexInfo* d = gDefaultIndexSet;
                ib = d->mIB;
                startIndex = d->mBase;
            } else if (idx) {
                ib = idx->mIB;
                startIndex = idx->mBase + b->mIndexOffset;
            }
            if (gCurIndexBuffer != ib) {
                ((SetIndicesFn)dev->vt[0x1a0 / 4])(dev, ib);
                gCurIndexBuffer = ib;
            }
            int start = b->mStart + baseVertex;
            switch (mPrimType) {
            case 0:
                ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 1, start, b->mCount);
                break;
            case 1:
                ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 2, start, b->mCount / 2);
                break;
            case 2:
                if (ib)
                    ((DrawIdxFn)dev->vt[0x148 / 4])(dev, 4, start, 0, b->mCount, startIndex, b->mIndexCount / 3);
                else
                    ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 4, start, b->mCount / 3);
                break;
            case 3:
                ((DrawIdxFn)dev->vt[0x148 / 4])(dev, 4, start, 0, b->mCount, startIndex, b->mCount / 2);
                stats->mTris += (b->mCount * 3) / 2;
                break;
            case 4:
                if (ib)
                    ((DrawIdxFn)dev->vt[0x148 / 4])(dev, 5, start, 0, b->mCount, startIndex, b->mIndexCount - 2);
                else
                    ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 5, start, b->mCount - 2);
                break;
            }
            stats->mVerts += b->mCount;
            stats->mTris += b->mIndexCount;
            stats->mBatches += 1;
        }
    }
    if (sd)
        pushShaderDataPop();
}

// @ 0x007a41a0
// Frees the heap block of an array-new'd buffer (count cookie at [-4]).
void __fastcall FreeArrayBlock(void** pp) {
    void* p = *pp;
    if (p && ((int*)p)[-1] != 0)
        operator_delete__(p);
}
