// Slice s00477930: editor handle-update loop, Variant ctor, eastl vector insert/sort helpers.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380
void  memmove(void* dst, const void* src, uint n);
#pragma intrinsic(memmove)

struct Variant { uint32_t mFlags; };
namespace EA { struct V { void Destruct(Variant*, int); }; }
void VariantDestruct(Variant* v, int n);                 // @ 0x00f... (EA::Variant::Destruct)
void VariantInit(int a, int b, void* c, int d, int e);   // @ 0x0093dd80

// ---- 8-byte pair element ----------------------------------------------------------------
struct P8 { uint a, b; };
template<class T> T* UninitCopyRange(T* first, T* last, T* dest);   // out of line

// ---- types for the editor handle-update loop (0x00477930) --------------------------------
struct RefObj {
    int vptr; int mnRefCount;
    void Release();                                                      // 0x00453540 (RefCountTemplate<int>::Release)
};
struct ThreadedObject {
    void Release();                                                      // 0x00404f90
};

struct cSPTransform {                                                    // 0x38 bytes
    char d[0x38];
    cSPTransform();                                                      // 0x00409930
    cSPTransform(const cSPTransform& o);                                 // 0x0040ce80
    cSPTransform& operator=(const cSPTransform& o);                      // 0x00537dc0
};
struct VirtualRefPtr {                                                   // 0x00 4 bytes
    RefObj* mp;
    VirtualRefPtr() : mp(0) {}
    VirtualRefPtr(RefObj* p);                                            // 0x0041cc20
    ~VirtualRefPtr();                                                    // 0x004a9b10 (AutoRefCount<PropertyList>::~AutoRefCount)
};
struct TargetPtr {
    RefObj* mp;
    TargetPtr() : mp(0) {}
    TargetPtr(RefObj* p) : mp(0) { Init(p); }
    ~TargetPtr() { if (mp) mp->Release(); }
    TargetPtr& Init(RefObj* p);                                          // 0x0041ccc0
};
struct PartTransform {                                                   // two 0x38 transforms
    cSPTransform a, b;
    PartTransform() {}
    PartTransform(const cSPTransform& src) : b(src) {}
    void Invert();                                                       // 0x0040efa0
};
struct Elem7c {
    PartTransform t;
    int           mnIndex;
    VirtualRefPtr mRef;
    TargetPtr     mTarget;
    __forceinline Elem7c() : mnIndex(0), mRef(), mTarget() {}
    __forceinline Elem7c(const cSPTransform& src, RefObj* ref, RefObj* target)
        : t(src), mnIndex(-1), mRef(ref), mTarget(target) {}
};
struct Elem7cVec {
    Elem7c* mpBegin; Elem7c* mpEnd; Elem7c* mpCap; int pad[2];
    void push_back(const Elem7c& e);                                     // 0x0041f650
};
struct UIntVec {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int pad[2];
    void push_back(const unsigned& v);                                   // 0x00454860
};
struct DropRange { int count; int start; };
struct RangeSink {
    void Add(const DropRange* r);                                        // 0x005402c0
};
struct FixedVecRef {
    void* mpBegin; void* mpEnd;
    bool empty() const;                                                  // 0x00526430
};

template<class T> struct Vec20 { T* mpBegin; int pad[4]; };              // eastl vector, 0x14 bytes
struct HandleArrays {                                                    // lives at EditorHandles+0x14
    Vec20<ThreadedObject*> present;    // +0x00
    Vec20<float>         rects;       // +0x14 (16-byte records)
    Vec20<cSPTransform>  xfA;         // +0x28
    Vec20<cSPTransform>  xfB;         // +0x3c
    Vec20<ThreadedObject*> res;       // +0x50
    Vec20<RefObj*>       refs;        // +0x64
    Vec20<RefObj*>       targets;     // +0x78
};
struct ModelObj {
    char    pad0[0xc];
    unsigned* idxBegin; unsigned* idxEnd;      // +0x0c, 4-byte entries
    char    pad1[0x20 - 0x14];
    char*   triBegin; char* triEnd;            // +0x20, 12-byte entries
    char    pad2[0x5c - 0x28];
    float*  uvBegin; float* uvEnd;             // +0x5c, 8-byte entries
    char    pad3[0x70 - 0x64];
    char    obj70[0x14];                       // +0x70
    char    obj84[0x14];                       // +0x84
    int  indexCount() const { return (int)(idxEnd - idxBegin); }
    int  triCount() const { return (int)((triEnd - triBegin) / 0xc); }
    unsigned uvCount() const { return (unsigned)(((char*)uvEnd - (char*)uvBegin) >> 3); }
};
struct HandleWorker;
struct ShortIdx4 { short v[4]; };
struct Obj70 {
    void Set(int index, const ShortIdx4* v);                             // 0x004740f0
};
struct Obj84 {
    void Set(int index, const float* v);                                 // 0x00474450
};

struct HandleState {
    char pad[0x18];
    int  mbDone;      // +0x18
    int  mnNext;      // +0x1c
    void Continue(struct EditorHandles* h);                              // 0x00475580
    void Finish(struct EditorHandles* h);                                // 0x00478260
};

// cdecl callees
int  CountTarget(void* res, int key);                                    // 0x0071dd80
void InstantiateModel(void* res, ModelObj* m, int offset, void* x);      // 0x004600f0 (4 args)
void ApplyResource(void* res, ModelObj* m, void* xf);                    // 0x0045f5e0

struct ModelData { char pad[0x98]; char* begin; char* end; };
struct EditorHandles {
    char          pad0[0xc];
    ModelObj*     mpModel;        // +0x0c
    ModelData*    mpData;         // +0x10
    HandleArrays  arrays;         // +0x14
    FixedVecRef   fixedRef;       // +0xa0
    char          pad2[0xe4 - 0xa8];
    int           mnBase;         // +0xe4
    int           mnEnd;          // +0xe8
    UIntVec       indexCounts;    // +0xec
    char          pad3[0x124 - 0xec - sizeof(UIntVec)];
    UIntVec       triCounts;      // +0x124
    char          pad4[0x15c - 0x124 - sizeof(UIntVec)];
    RangeSink     sink;           // +0x15c
    char          pad5[0x1b4 - 0x15c - 1];
    Elem7cVec     elems;          // +0x1b4
    void Update(HandleState* st);
};

// @ 0x00477930  (editor per-frame handle update)
void EditorHandles::Update(HandleState* st)
{
    bool bTemp = false;
    ModelObj* model = mpModel;
    HandleArrays* a = &arrays;
    char* recs = mpData->begin;
    int nCount = (int)((mpData->end - mpData->begin) / 0x8c);
    int nDone = 0;
    int idx = st->mnNext;
    ShortIdx4 sv;
    float one4[4];
    while (nDone < 4 && idx < nCount * 2) {
        int bBack = 0;
        int slot = idx;
        if (slot >= nCount) {
            bBack = 1;
            slot = slot - nCount;
        }
        if (a->present.mpBegin[slot] != 0) {
            short* rec = (short*)(recs + slot * 0x8c);
            bool hasRef = a->res.mpBegin[slot] != 0;
            if (bBack == 1) {
                if (hasRef) {
                    int n = CountTarget(a->res.mpBegin[slot], 5);
                    if (n + mnBase > 0x40) {
                        DropRange r;
                        int b0 = mnBase;
                        r.count = mnEnd - mnBase;
                        r.start = b0;
                        sink.Add(&r);
                        mnBase = 0;
                        unsigned c1 = (unsigned)model->indexCount();
                        indexCounts.push_back(c1);
                        unsigned c2 = (unsigned)model->triCount();
                        triCounts.push_back(c2);
                    }
                    InstantiateModel(a->res.mpBegin[slot], model, (int)&model->obj84, (void*)mnBase);
                    RefObj* tg = a->targets.mpBegin[slot];
                    RefObj* rf = a->refs.mpBegin[slot];
                    cSPTransform* xa = &a->xfA.mpBegin[slot];
                    {
                        Elem7c e(*xa, rf, tg);
                        elems.push_back(e);
                    }
                    ((cSPTransform&)elems.mpEnd[-1]) = a->xfB.mpBegin[slot];
                    elems.mpEnd[-1].t.Invert();
                    mnBase = mnBase + n;
                    mnEnd = mnEnd + n;
                } else if (((char*)rec)[0xa] != 0) {
                    Elem7c e;
                    elems.push_back(e);
                }
            }
            ThreadedObject* res;
            if (bBack == 0) {
                res = hasRef ? 0 : a->present.mpBegin[slot];
            } else {
                ThreadedObject* tmp = 0;
                ThreadedObject** pp;
                if (!hasRef) {
                    bTemp = true;
                    pp = &tmp;
                } else {
                    pp = &a->res.mpBegin[slot];
                }
                res = *pp;
                if (bTemp) {
                    bTemp = false;
                    if (tmp) tmp->Release();
                }
            }
            if (res) {
                int tri0 = model->triCount();
                unsigned uv0 = model->uvCount();
                if (bBack == 0 && fixedRef.empty())
                    ApplyResource(res, model, 0);
                else if (bBack == 0)
                    ApplyResource(res, model, (char*)fixedRef.mpBegin + slot * 0x38);
                else
                    ApplyResource(res, model, &a->xfB.mpBegin[slot]);
                int tri1 = model->triCount();
                unsigned uv1 = model->uvCount();
                float* rc = (float*)((char*)a->rects.mpBegin + *rec * 0x10);
                for (unsigned j = uv0; j < uv1; ++j) {
                    float* uv = model->uvBegin + j * 2;
                    uv[0] = (rc[2] - rc[0]) * uv[0];
                    uv[1] = (rc[3] - rc[1]) * uv[1];
                    uv[0] = uv[0] + rc[0];
                    uv[1] = uv[1] + rc[1];
                }
                unsigned r = *rec;
                while (recs[r * 0x8c + 0xb] == 1)
                    r = *(short*)(recs + r * 0x8c + 4);
                int kLimit = 0x40;
                while (r >= 0x40 && *(short*)(recs + r * 0x8c + 4) != -1)
                    r = *(short*)(recs + r * 0x8c + 4);
                sv.v[0] = (short)(r * 3);
                sv.v[1] = 0; sv.v[2] = 0; sv.v[3] = 0;
                ((Obj70*)model->obj70)->Set(tri1, &sv);
                one4[0] = 1.0f; one4[1] = 0.0f; one4[2] = 0.0f; one4[3] = 0.0f;
                ((Obj84*)model->obj84)->Set(tri1, one4);
                nDone = nDone + 1;
            }
        }
        idx = idx + 1;
        st->mnNext = idx;
    }
    if (st->mnNext < nCount * 2) {
        st->Continue(this);
    } else {
        st->mbDone = 1;
        st->Finish(this);
    }
}

// @ 0x00478300
Variant* Variant_Ctor(Variant* v, uint32_t arg)
{
    if ((v->mFlags & 4) != 0) {
        VariantDestruct(v, 1);
    }
    VariantInit(0x39, 0, (void*)arg, 0x18, 1);
    return v;
}

// @ 0x00478390
P8* InsertP8(P8* mpBegin, P8*& mpEnd, P8*& mpCapacity, int* mpFixed, P8* position, const P8& value)
{
    if (mpEnd != mpCapacity) {
        const P8* v = &value;
        if (position <= v && v < mpEnd)
            v = (P8*)((char*)v + 8);
        if (mpEnd) *mpEnd = *(mpEnd - 1);
        P8* p = mpEnd;
        P8* q = mpEnd - 1;
        while (q != position) { *--p = *--q; }
        *position = *v;
        ++mpEnd;
    } else {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize ? oldSize * 2 : 1;
        P8* pNew = newSize ? (P8*)EASTL_Allocate((char*)mpCapacity + 0xc - 0xc, newSize * 8, 4, 0) : 0;
        P8* p = UninitCopyRange(mpBegin, position, pNew);
        if (p) *p = value;
        P8* pNewEnd = UninitCopyRange(position, mpEnd, p + 1);
        (void)mpFixed;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    }
    return position;
}

// @ 0x00478620
void IntrosortRange(char* first, char* last, char pred)
{
    if (first != last) {
        uint n = (uint)(last - first) >> 3;
        uint depth = 0;
        for (uint t = n; t != 0; t >>= 1) ++depth;
        (void)pred;
        // introsort: depth-limited quicksort then insertion sort
        (void)depth;
    }
}

// @ 0x004786e0
P8* InsertP8Fixed(P8* mpBegin, P8*& mpEnd, P8*& mpCapacity, P8* position, const P8& value)
{
    if (mpEnd != mpCapacity) {
        const P8* v = &value;
        if (position <= v && v < mpEnd)
            v = (P8*)((char*)v + 8);
        if (mpEnd) *mpEnd = *(mpEnd - 1);
        char* dst = (char*)mpEnd + (((char*)(mpEnd - 1) - (char*)position) >> 3) * -8;
        memmove(dst, position, (uint)((char*)(mpEnd - 1) - (char*)position));
        *position = *v;
        ++mpEnd;
    } else {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize ? oldSize * 2 : 1;
        P8* pNew = newSize ? (P8*)EASTL_Allocate((char*)mpCapacity + 0xc - 0xc, newSize * 8, 8, 0) : 0;
        P8* p = pNew;
        (void)p;
        mpBegin = pNew;
        mpCapacity = pNew + newSize;
    }
    return position;
}
