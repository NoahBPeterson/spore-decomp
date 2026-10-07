// slice s007a07b0: SP::cSplitDrawImpl (cSplitManager-driven split draw) and its vector helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
// Original names (PDB): 0x7a09f0 ~cSplitDrawImpl-like dtor, 0x7a0f90 SP::cIModelSplitter::Split,
// 0x7a11c0 SP::cSplitDrawImpl::Dispatch; element types are retail 20-byte vector-like records.
#include "types.h"

void* operator new(unsigned int, const char*, int, unsigned int, const char*, int);
void operator delete[](void*) throw();
extern "C" void* memmove_thunk_11e0744(void* dst, const void* src, unsigned n);  // memmove
static __forceinline unsigned ByteDiff(const void* last, const void* first) { return (unsigned)((const char*)last - (const char*)first); }
#define MOVE(d, s, n) memmove_thunk_11e0744((d), (s), (n))

// ---------------------------------------------------------------------------
// 20-byte "vector-like" element: begin/end/capacity + 2 extra dwords.
// ---------------------------------------------------------------------------
struct V20 {                       // value with copy-ctor 0x79a4a0, dtor 0x432e80
    int* b; int* e; int* c; int x; int y;
    V20() : b(0), e(0), c(0) {}
    V20(const V20&);               // 0x79a4a0
    ~V20();                        // 0x432e80
};

struct V20Pod {                    // same shape, trivially destructible (vector<cSplitInstanceList>)
    int* b; int* e; int* c; int x; int y;
    V20Pod() : b(0), e(0), c(0) {}
    ~V20Pod() { b = 0; }
};

// out-of-line eastl helpers (cdecl), signatures taken from the call sites
V20* UninitMove(V20** out, V20* first, V20* last, V20* dest, V20* pos);  // 0x79a710
V20* MoveBackward(V20* first, V20* last, V20* destEnd);                   // 0x79f770
V20* FillRange(V20* first, V20* last, const V20* val);                    // 0x79fcf0
V20* UninitFillN(V20* dest, unsigned n, const V20* val);       // 0x79a9d0

// A vector of V20 (begin/end/capacity at +0/+4/+8).
struct VecV20 {
    V20* mpBegin; V20* mpEnd; V20* mpCapacity;
    void Insert(V20* pos, unsigned n, const V20* val);
    void InsertC(V20* pos, unsigned n, const V20& val);   // same routine, by-reference spelling   // 0x7a07b0
    void Resize(unsigned n);                              // 0x7a1100
    V20* EraseTail(V20* first, V20* last);                // 0x7a05b0
};

// @ 0x7a07b0
void VecV20::Insert(V20* position, unsigned n, const V20* pValue)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const V20 temp(*pValue);
            const unsigned nExtra = (unsigned)(mpEnd - position);
            V20* pOldEnd = mpEnd;
            if (n < nExtra) {
                UninitMove((V20**)&pValue, pOldEnd - n, pOldEnd, pOldEnd, position);
                mpEnd += n;
                MoveBackward(position, pOldEnd - n, pOldEnd);
                FillRange(position, position + n, &temp);
            } else {
                UninitFillN(pOldEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                UninitMove(&position, position, pOldEnd, mpEnd, position);
                mpEnd += nExtra;
                FillRange(position, pOldEnd, &temp);
            }
        }
    } else {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewCap = nPrevSize ? nPrevSize * 2 : 1;
        if (nNewCap < nPrevSize + n) nNewCap = nPrevSize + n;
        V20* pNewData = 0;
        if (nNewCap)
            pNewData = (V20*)operator new(nNewCap * sizeof(V20), "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        unsigned nHead = (unsigned)((char*)position - (char*)mpBegin);
        V20* pNew = (V20*)MOVE(pNewData, mpBegin, nHead);
        V20* pFill = pNew + nHead / sizeof(V20);
        UninitFillN(pFill, n, pValue);
        unsigned nTail = (unsigned)((char*)mpEnd - (char*)position);
        V20* pTail = (V20*)MOVE(pFill + n, position, nTail);
        V20* pEnd = pTail + nTail / sizeof(V20);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete[](mpBegin);
        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewCap;
    }
}

// @ 0x7a1100

void VecV20::Resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin))
        InsertC(mpEnd, n - (unsigned)(mpEnd - mpBegin), V20());
    else
        EraseTail(mpBegin + n, mpEnd);
}

// ---------------------------------------------------------------------------
// vector<cSplitInstanceList>-like resize (0x7a0ae0)
// ---------------------------------------------------------------------------
struct VecPod20 {
    V20Pod* mpBegin; V20Pod* mpEnd; V20Pod* mpCapacity;
    void Resize(unsigned n);
    void UninitInsertN(V20Pod* pos, unsigned n, const V20Pod& val);   // 0x7a0110
    V20Pod* DestroyRangeP(V20Pod* first, V20Pod* last);              // 0x7a00c0
};

// @ 0x7a0ae0
void VecPod20::Resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin))
        UninitInsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), V20Pod());
    else
        DestroyRangeP(mpBegin + n, mpEnd);
}

// ---------------------------------------------------------------------------
// reference-counted base with virtual dtor (EA::RefCountTemplate<int>)
// ---------------------------------------------------------------------------
extern "C" long _InterlockedExchange(long volatile*, long);
extern "C" long _InterlockedIncrement(long volatile*);
extern "C" long _InterlockedDecrement(long volatile*);
#pragma intrinsic(_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement)

struct RefBase {
    virtual ~RefBase() {}
    volatile long mnRefCount;
    RefBase() { _InterlockedExchange(&mnRefCount, 0); }
    __forceinline void AddRef() { _InterlockedIncrement(&mnRefCount); }
    __forceinline int Release() {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) { _InterlockedExchange(&mnRefCount, 1); delete this; }
        return (int)n;
    }
};

struct Transform0x30 { void Reset(int arg); };       // 0x79a3f0 (thiscall)

struct V16 { int a, b, c, d; };
V16* CopyV16(V16* first, V16* last, V16* dest);        // 0x705250 (cdecl)

// cSplitManager-like 0x58-byte object
struct SplitMgr : RefBase {
    int a8[3]; int pad14, pad18; int a1c[3]; int pad28, pad2c; Transform0x30 t30; int a30tail[2];
    int pad3c, pad40; int a44[3]; int pad50, pad54;
    SplitMgr() {
        int* w = (int*)this;
        w[2] = 0; w[3] = 0; w[4] = 0;
        w[7] = 0; w[8] = 0; w[9] = 0;
        w[0xc] = 0; w[0xd] = 0; w[0xe] = 0;
        w[0x11] = 0; w[0x12] = 0; w[0x13] = 0;
    }
};

template <class T> struct AutoRef {
    T* mp;
    __forceinline AutoRef& operator=(T* p) {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};

struct U16Vec { unsigned short* b; unsigned short* e; unsigned short* c; int x, y; };

// state with a manager, a 16-byte-element vector and a 20-byte-element vector (this = 0x7a0cd0 receiver)
struct SplitState {
    AutoRef<SplitMgr> mMgr;       // +0
    V16* mpBegin; V16* mpEnd;     // +4/+8 (vector of 16-byte elements)
    int pad[3];
    VecPod20 mLists;              // +0x18
    // 0x7a0cd0
    void Reset(int a, int b);
};

// @ 0x7a0cd0
void SplitState::Reset(int a, int b)
{
    mMgr = new ("Graphics", 0, 0, 0, 0) SplitMgr();
    ((SplitMgr*)mMgr.mp)->t30.Reset(a);
    V16* first = mpBegin;
    V16* last = mpEnd;
    CopyV16(last, last, first);
    mpEnd += -(last - first);
    mLists.Resize(b);
    U16Vec* it = (U16Vec*)mLists.mpBegin;
    if (it != (U16Vec*)mLists.mpEnd) {
        do {
            unsigned short* eb = it->b;
            unsigned short* ee = it->e;
            MOVE(eb, ee, ByteDiff(it->e, ee));
            it->e += -(ee - eb);
            it = (U16Vec*)((char*)it + 0x14);
        } while (it != (U16Vec*)mLists.mpEnd);
    }
}

struct SplitState2 {
    AutoRef<SplitMgr> mMgr;       // +0
    int pad4;
    SplitState mSub;              // +8 (size 0x24)
    char pad48[0x48 - 0x8 - sizeof(SplitState)];
    VecPod20 mLists48;            // +0x48
    void Reset(int a, int b);     // 0x7a0de0
};

// @ 0x7a0de0
void SplitState2::Reset(int a, int b)
{
    mMgr = new ("Graphics", 0, 0, 0, 0) SplitMgr();
    mSub.Reset(a, b);
    mLists48.Resize(b);
    U16Vec* it = (U16Vec*)mLists48.mpBegin;
    if (it != (U16Vec*)mLists48.mpEnd) {
        do {
            unsigned short* eb = it->b;
            unsigned short* ee = it->e;
            MOVE(eb, ee, ByteDiff(it->e, ee));
            it->e += -(ee - eb);
            it = (U16Vec*)((char*)it + 0x14);
        } while (it != (U16Vec*)mLists48.mpEnd);
    }
    ((SplitMgr*)mMgr.mp)->t30.Reset(a);
}

// ---------------------------------------------------------------------------
// 0x7a09f0: destructor of the split-draw object (two bases, two refcounted members, one vector)
// ---------------------------------------------------------------------------
struct IntVecVec { int* mpBegin; int* mpEnd; int* mpCap; };
void ClearVecVec(IntVecVec* v);                            // 0x7a0410

struct BaseA { virtual void vA(); };
struct BaseB { virtual void vB(); ~BaseB() {} };
struct PlainRc {
    virtual ~PlainRc() {}
    int mnRefCount;
    __forceinline int Release() {
        int n = mnRefCount + -1;
        mnRefCount = n;
        if (n == 0) { mnRefCount = 1; delete this; }
        return n;
    }
};
template <class T> struct RcPtr {
    T* mp;
    ~RcPtr() { if (mp) mp->Release(); }
};

struct CIntVec {
    int* mpBegin; int* mpEnd; int* mpCap;
    void DestroyRange(int* first, int* last) throw();   // 0x1023030 (thiscall)
    ~CIntVec() {
        // element destruction through 0x1023030, then buffer release
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
};

struct SplitDrawBase : BaseA, BaseB {
    int pad8;
    RcPtr<PlainRc> mA;            // +0xc
    CIntVec mVec;                 // +0x10
    int pad1c, pad20;
    RcPtr<PlainRc> mC;            // +0x24
    ~SplitDrawBase();             // 0x7a09f0
};

// @ 0x7a09f0
SplitDrawBase::~SplitDrawBase()
{
    ClearVecVec((IntVecVec*)&mVec);
}

// ---------------------------------------------------------------------------
// vector<int*>-ish swap (0x7a0b90) and helpers
// ---------------------------------------------------------------------------
struct V20Tmp { int w[5]; ~V20Tmp(); };     // 0x432e80 dtor

struct V12 {
    V20* b; V20* e; V20* c; int x; int y;
    V12() : b(0), e(0), c(0) {}
    V12(const V12&);                       // 0x79b020
    V12& Assign(const V12&);               // 0x7a0460 (operator=, thiscall)
    ~V12();                                // 0x432de0
    void Swap(V12& other);                 // 0x7a0b90
    void Free(V20* first, V20* last);      // 0x79b0d0 (thiscall)
    void Add(const V20Tmp& v);             // 0x7a0c50 (thiscall)
};

static __forceinline void SwapPtr(V20*& a, V20*& b) { V20* t = a; a = b; b = t; }

// @ 0x7a0b90
void V12::Swap(V12& other)
{
    V20* x = b;
    if ((x == 0 || ((int*)x)[-1] != 0)) {
        V20* y = other.b;
        if (y == 0 || ((int*)y)[-1] != 0) {
            b = y; other.b = x;
            SwapPtr(e, other.e);
            SwapPtr(c, other.c);
            return;
        }
    }
    V12 tmp(*this);
    Assign(other);
    other.Assign(tmp);
}

// ---------------------------------------------------------------------------
// cIModelSplitter::Split and helpers
// ---------------------------------------------------------------------------
struct MeshList {                           // 12-byte RefVector
    int* b; int* e; int* c;
    MeshList() : b(0), e(0), c(0) {}
    ~MeshList();                            // 0x41eb80 (RefVector::~RefVector)
};

struct SplitterVec { V20* b; V20* e; V20* c; V20Pod* x; };

struct IModelSplitter {
    virtual void v0();
    virtual void Notify(V12* out);          // vtbl+4
    void Process(int a, V12* vec);          // 0x7a0ee0
    void Split(int meshes, V12* out);       // 0x7a0f90
};

V20* FindErase(V20* a, V20* b, V20* c);     // 0x79f730 (cdecl, 3 args)
V20Tmp MakeTmp(int a);                      // 0x79fd20 (cdecl, hidden return slot)

// @ 0x7a0ee0
void IModelSplitter::Process(int a, V12* vec)
{
    V20* b0 = vec->b;
    V20* e0 = vec->e;
    V20* r = FindErase(e0, e0, b0);
    vec->Free(r, vec->e);
    vec->e += -(e0 - b0);
    vec->Add(MakeTmp(a));
    Notify(vec);
}

void CompileSplitModels(V12* models, V12* out);        // 0x7a0360 (cdecl)

// @ 0x7a0f90
void IModelSplitter::Split(int meshes, V12* out)
{
    V12 tmp;
    Process(meshes, &tmp);
    CompileSplitModels(&tmp, out);
}

// ---------------------------------------------------------------------------
// 0x7a1000: re-apply tmp contents into target if present in the ordered map
// ---------------------------------------------------------------------------
struct MapNode { MapNode* a; MapNode* b; int pad[2]; int key; };

struct V12Src {                          // vector built from the host's manager; inline dtor
    V20* b; V20* e; V20* c; int x; int y;
    V12Src(int arg) : b(0), e(0), c(0) { Init(arg); }
    void Init(int arg);                  // 0x79a4f0 (thiscall)
    ~V12Src() {
        ((V12*)this)->Free(b, e);
        if (b && ((int*)b)[-1]) operator delete[](b);
    }
    void Swap(V12& other) { ((V12*)this)->Swap(other); }
};

struct ApplyHost {
    int pad[4];
    int pad10, pad14;       // +0x10: map header node
    MapNode* mRoot;         // +0x18
    int pad1c;
    int mArg;               // +0x20
    void Apply(V12* target);
};

// @ 0x7a1000
void ApplyHost::Apply(V12* target)
{
    V12Src tmp(mArg);
    tmp.Swap(*target);
    unsigned count = (unsigned)(tmp.e - tmp.b);
    V20* p = tmp.b;
    MapNode* head = (MapNode*)((char*)this + 0x10);
    for (unsigned i = 0; i < count; ++i, ++p) {
        MapNode* r = head;
        MapNode* n = mRoot;
        while (n) {
            if (n->key < (int)i) n = n->a;
            else { r = n; n = n->b; }
        }
        if (r != head && (int)i < r->key) r = head;
        if (r != head)
            target->Add(*(const V20Tmp*)p);
    }
}

// ---------------------------------------------------------------------------
// 0x7a11c0: cSplitDrawImpl::Dispatch
// ---------------------------------------------------------------------------
struct CompiledElem { int mesh; int material; };
struct ElemList { CompiledElem* b; CompiledElem* e; CompiledElem* c; int p3, p4; };   // 20 bytes

struct SplitInstEntry { int key; char pad[0x3c]; char xform[0x38]; };                 // 0x78 bytes
struct SplitInstList { int nextFree; SplitInstEntry* b; SplitInstEntry* e; int pad[4]; };  // 0x1c bytes
struct SplitMgrData { char pad[0x40]; SplitInstList* mb; SplitInstList* me; };

struct ModelInstance {
    void GetMeshes(MeshList* out);                                   // 0x73eb90
    void SetTransform(const void* xf, int a);                        // 0x73eca0
    void DrawMesh(int mesh, int material, int b, int a);             // 0x73ede0
};

extern unsigned g_renderStateDirty;     // 0x16fa38c
extern int g_drawFlag;                  // 0x16f9238

struct SplitDrawImpl {
    int pad0[3];
    IModelSplitter* mSplitter;          // +0xc
    ElemList* mpBegin;                  // +0x10
    ElemList* mpEnd;                    // +0x14
    int pad18[3];
    SplitMgrData* mMgr;                 // +0x24
    void Dispatch(ModelInstance* model, int a, int b);
};

// @ 0x7a11c0
void SplitDrawImpl::Dispatch(ModelInstance* model, int a, int b)
{
    ElemList** pVec = &mpBegin;
    if (pVec[0] == pVec[1]) {
        MeshList meshes;
        model->GetMeshes(&meshes);
        mSplitter->Split((int)&meshes, (V12*)pVec);
    }
    g_renderStateDirty |= 0x8000;
    g_drawFlag = 1;
    if (mMgr == 0) {
        int n = (int)(pVec[1] - pVec[0]);
        if (n != 0) {
            int off = 0;
            do {
                ElemList* el = (ElemList*)((char*)*pVec + off);
                unsigned cnt = (unsigned)(el->e - el->b);
                for (unsigned j = 0; j < cnt; ++j)
                    model->DrawMesh(el->b[j].mesh, el->b[j].material, b, a);
                off += 0x14;
                --n;
            } while (n != 0);
        }
    } else {
        int n = (int)(mMgr->me - mMgr->mb);
        if (n != 0) {
            int off1 = 0;
            int off2 = 0;
            do {
                SplitInstList* inst = (SplitInstList*)((char*)mMgr->mb + off1);
                ElemList* el = (ElemList*)((char*)*pVec + off2);
                SplitInstEntry* last = inst->e;
                SplitInstEntry* it = inst->b;
                for (; it != last && it->key != -2; ++it) {}
                if (it != last) {
                    do {
                        model->SetTransform(it->xform, a);
                        unsigned cnt = (unsigned)(el->e - el->b);
                        for (unsigned j = 0; j < cnt; ++j)
                            model->DrawMesh(el->b[j].mesh, el->b[j].material, b, a);
                        do {
                            ++it;
                        } while (it != last && it->key != -2);
                    } while (it != last);
                }
                off2 += 0x14;
                off1 += 0x1c;
                --n;
            } while (n != 0);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x7a1400: copy per-model stream/geometry data into the compiled split manager
// ---------------------------------------------------------------------------
extern unsigned g_sizeMask[];           // 0x140f544 (per-component masks)
extern int g_streamTable[];             // 0x153b208

struct StreamDesc {                     // 0x8c bytes
    int w0; char* data; unsigned short maskIdx; unsigned short stride; char pad[0x8c - 12];
};

struct FixedIdVec6 { void Assign(const void* src); };   // 0x719170 FixedIdVector6::operator=
struct StreamIdVec { void Resize(int n); };             // 0x71f7e0
struct ElemVec    { void Resize(int n); void Grow(); };   // 0x475320 / 0x79fe20

struct IObjRelease { virtual void v0(); virtual void Release(); };

struct RangeInfo {
    int count; unsigned short* ptr; unsigned short w1, w2; IObjRelease* r;
    RangeInfo(int c, unsigned short* p) : count(c), ptr(p), w1(2), w2(2), r(0) {}
    ~RangeInfo() { if (r) r->Release(); }
};
void BuildStream(RangeInfo* r, void* dst);              // 0x7201d0 (cdecl)
void BuildObj(int count, unsigned short w, void* dst);  // 0x720190 (cdecl)
void HandleAssign(void* dst, const void* src);          // 0x424f70 (thiscall Handle_Assign)
void BlendCopy(int a, int b, float f, int v1, int v2, void* out);  // 0x799e70 (cdecl)

struct PairElem { int a, b, c; float f; };              // 16 bytes
struct CompiledStreamElem {                             // 0x20 bytes
    int k0, k1, k2, k3;
    char* data; int base; unsigned short w; unsigned short stride; int pad;
};
struct ModelDst {                                       // the object pointed to by *this
    char pad[8]; char* elems;                           // +8 ElemVec begin..: used via methods
    int e0c;                                            // +0xc: end of ElemVec
    char pad2[0x1c - 0x10];
    char* streams;                                      // +0x1c: StreamIdVec begin
};
struct ModelSrc {
    char pad[8]; CompiledStreamElem* sb; CompiledStreamElem* se;   // +8/+0xc
    char pad2[0x1c - 0x10];
    StreamDesc* streamBegin; StreamDesc* streamEnd;                // +0x1c/+0x20
};
struct GeomBuilder {
    ModelDst* mDst;                  // +0
    PairElem* mpB; PairElem* mpE;    // +4/+8
    int pad[3];
    ElemList* mListsB; ElemList* mListsE;  // +0x18/+0x1c (20-byte lists)
    ModelDst* Build(ModelSrc* src);  // 0x7a1400
};

// @ 0x7a1400
ModelDst* GeomBuilder::Build(ModelSrc* src)
{
    if (mpB == mpE) return 0;
    ((StreamIdVec*)((char*)mDst + 0x1c))->Resize((int)(src->streamEnd - src->streamBegin));
    int nLists = (int)(mListsE - mListsB);
    for (int i = 0; i < nLists; ++i) {
        char* t1 = *(char**)((char*)mDst + 0x1c) + i * 0x8c;
        *(int*)(t1 + 0x10) = (int)(mpE - mpB);
        ((FixedIdVec6*)(t1 + 0x14))->Assign((char*)src->streamBegin + i * 0x8c + 0x14);
        ElemList* el = mListsB + i;
        RangeInfo ri((int)(((char*)el->e - (char*)el->b) >> 1), (unsigned short*)el->b);
        BuildStream(&ri, t1);
    }
    ((ElemVec*)((char*)mDst + 8))->Resize((int)(src->se - src->sb));
    unsigned nSrc = (unsigned)(src->se - src->sb);
    for (unsigned k = 0; k < nSrc; ++k) {
        CompiledStreamElem* e = src->sb + k;
        if (g_streamTable[e->k0] == 0) continue;
        ((ElemVec*)((char*)mDst + 8))->Grow();
        CompiledStreamElem* d = (CompiledStreamElem*)(*(char**)((char*)mDst + 0xc)) - 1;
        d->k3 = e->k3; d->k1 = e->k1; d->k0 = e->k0; d->k2 = e->k2;
        int kind = e->k3;
        if (kind < 0) continue;
        if (kind <= 2) {
            char* obj = (char*)d + 0x10;
            unsigned cnt = (unsigned)(mpE - mpB);
            BuildObj((int)cnt, e->w, obj);
            cnt = (unsigned)(mpE - mpB);
            for (unsigned j = 0; j < cnt; ++j) {
                PairElem* p = mpB + j;
                StreamDesc* sd = src->streamBegin + p->a;
                char* out = *(char**)(obj + 4) + (*(unsigned short*)(obj + 0xa)) * j;
                if (p->f != 0.0f) {
                    unsigned v2 = *(unsigned*)(sd->data + sd->stride * p->c) & g_sizeMask[sd->maskIdx];
                    unsigned v1 = *(unsigned*)(sd->data + sd->stride * p->b) & g_sizeMask[sd->maskIdx];
                    BlendCopy(d->k0, d->k2, p->f, (int)(v1 * e->stride + e->base),
                              (int)(v2 * e->stride + e->base), out);
                } else {
                    unsigned v1 = *(unsigned*)(sd->data + sd->stride * p->b) & g_sizeMask[sd->maskIdx];
                    MOVE(out, (void*)(v1 * e->stride + e->base), e->w);
                }
            }
        } else if (kind == 8) {
            HandleAssign((char*)d + 0x10, (char*)e + 0x10);
        }
    }
    return mDst;
}
