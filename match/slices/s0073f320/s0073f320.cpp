// Slice s0073f320 (0x0073f320-0x00740370): SP::cModelInstance bindings / dispatch.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
// Functions at 0x73f440..0x7402e0 are built with an extra /GS- (manifest flags override).
#include "types.h"
#include <intrin.h>

void __cdecl EASTL_allocator_deallocate(void* p);   // 0xf47380
void __cdecl operator_delete__(void* p) throw();    // 0xf47380 (same function, nothrow view)

struct RC {
    virtual void v0(int mode);
    virtual void v1();
    int mnRefCount;                  // +0x4
};
inline void RcAddRef(RC* p) { _InterlockedIncrement((volatile long*)&p->mnRefCount); }
inline void RcRelease(RC* p) {
    long r = _InterlockedDecrement((volatile long*)&p->mnRefCount);
    if (r == 0) { _InterlockedExchange((volatile long*)&p->mnRefCount, 1); p->v0(1); }
}

// ---------------------------------------------------------------------------
// @ 0x0073fe50  eastl::copy_backward<8-byte POD*>
// ---------------------------------------------------------------------------
struct T8 { int a, b; };

void __cdecl copy_backward8(T8* first, T8* last, T8* result)
{
    while (last != first) {
        *--result = *--last;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073f440  copy_backward for an 8-byte element with a refcounted pointer
// ---------------------------------------------------------------------------
struct RefPair {
    int value;                       // +0x0
    RC* p;                           // +0x4
};

RefPair* __cdecl copy_backward_ref(RefPair* first, RefPair* last, RefPair* result)
{
    while (last != first) {
        --last; --result;
        result->value = last->value;
        RC* p = last->p;
        RC* old = result->p;
        if (p != old) {
            if (p) RcAddRef(p);
            result->p = p;
            if (old) RcRelease(old);
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00740370  set a refcounted array pointer member at +0xd0
// ---------------------------------------------------------------------------
struct DynArray {
    void* first;                     // +0x0
};

struct ArrayHolder {
    char pad[0xd0];
    DynArray* mArray;                // +0xd0
    void SetArray(DynArray* p);
};

void ArrayHolder::SetArray(DynArray* p)
{
    DynArray* old = mArray;
    if (old) {
        void* first = old->first;
        if (first && *(int*)((char*)first - 4) != 0)
            EASTL_allocator_deallocate(first);
        EASTL_allocator_deallocate(old);
    }
    mArray = p;
}

// ---------------------------------------------------------------------------
// @ 0x0073f320  SP::cModelInstance::cSkinBinding::operator=
// ---------------------------------------------------------------------------
struct cSPTransformS {
    uint16_t mFlags;
    uint16_t mModificationCount;
    float    mTranslation[3];
    float    mScale;
    float    mRotation[9];           // +0x14
    cSPTransformS& operator=(const cSPTransformS& o);
};

struct cSkinBinding {
    int f0, f4, f8;
    RC* p0c;                         // +0xc
    cSPTransformS t10;               // +0x10
    cSPTransformS t48;               // +0x48
    cSPTransformS t80;               // +0x80
    int b8, bc, c0;
    cSkinBinding& operator=(const cSkinBinding& o);
};

cSkinBinding& cSkinBinding::operator=(const cSkinBinding& o)
{
    f0 = o.f0;
    f4 = o.f4;
    f8 = o.f8;
    if (o.p0c != p0c) {
        RC* p = o.p0c;
        RC* old = p0c;
        if (p)
            ++p->mnRefCount;
        p0c = p;
        if (old) {
            int n = (old->mnRefCount += -1);
            if (n == 0) {
                old->mnRefCount = 1;
                _ReadWriteBarrier();
                old->v0(1);
            }
        }
    }
    t10 = o.t10;
    t48 = o.t48;
    t80 = o.t80;
    b8 = o.b8;
    bc = o.bc;
    c0 = o.c0;
    return *this;
}


// ===========================================================================
// Functions below are compiled with /GS- appended to the module flags.
// ===========================================================================
struct cSPTransform {                              // 0x38 bytes
    uint16_t mFlags;                               // bit 1/2: has rotation/translation
    uint16_t mModificationCount;
    float mTranslation[3];
    float mScale;                                  // +0x10
    float mRotation[9];                            // +0x14 (3 rows of 3)
    cSPTransform& operator=(const cSPTransform& o);   // 0x537dc0 (out of line)
    void BackTransformPoint(float* p) const;       // 0x4ff6d0
};


// @ 0x0073f4b0  SP::cModelInstance::SetAnimationGroupTransform
struct Mesh8 { signed char mat; char pad[7]; };
struct Material { char pad0[0x48]; cSPTransform src; cSPTransform dst; char pad_[0xc4 - 0xb8]; };
cSPTransform& translateTransform(cSPTransform& out, const cSPTransform& in, const cSPTransform& delta); // 0x6271a0
struct ModelInstanceAnim {
    char pad0[0x14];
    Mesh8* mMeshesBegin;   // +0x14
    Mesh8* mMeshesEnd;     // +0x18
    char pad1c[0x28 - 0x1c];
    Material* mMaterials;  // +0x28
    void SetAnimationGroupTransform(int idx, const cSPTransform& t);
};
// @ 0x0073f4b0
void ModelInstanceAnim::SetAnimationGroupTransform(int idx, const cSPTransform& t)
{
    if (idx >= 0 && idx < (int)(mMeshesEnd - mMeshesBegin)) {
        signed char m = mMeshesBegin[idx].mat;
        if (m >= 0) {
            Material& mat = mMaterials[m];
            cSPTransform& src = mat.src;
            if (src.mScale == 1.0f && (src.mFlags & 6) == 0) {
                mat.dst = t;
            } else {
                cSPTransform tmp;
                mat.dst = translateTransform(tmp, src, t);
            }
        }
    }
}


// @ 0x0073fd20  SP::cModelInstance::Dispatch
struct __declspec(align(16)) DispatchCtx { int d[0x11]; int arg3; int p48, p4c; int result; };
struct Listener { virtual void v0(); virtual void v1(); virtual void v2(); virtual void OnDispatch(void* inst, DispatchCtx* c, int a2); };
struct Processor { void Process(DispatchCtx* c); };   // 0x73bb40
struct Mesh;
struct ModelInstanceDispatch {
    char pad0[8];
    Mesh** mMeshesBegin;  // +8
    Mesh** mMeshesEnd;    // +0xc
    char pad10[0x70 - 0x10];
    char sub70[0x58];
    uint32_t mFlags;      // +0xc8
    char pad_cc[0xec - 0xcc];
    Listener* mListener;  // +0xec
    Processor* mProc;     // +0xf0
    void Setup(void* sub, DispatchCtx* c);              // 0x73eca0
    void DispatchMesh(Mesh* m, int i, int a2, DispatchCtx* c);   // 0x73ede0
    int  Dispatch(int a2, int a3);
};
// @ 0x0073fd20
int ModelInstanceDispatch::Dispatch(int a2, int a3)
{
    DispatchCtx c;
    int i = 0;
    c.result = 0;
    c.arg3 = a3;
    Setup(sub70, &c);
    mProc->Process(&c);
    if (!(mFlags & 4)) {
        int n = (int)(mMeshesEnd - mMeshesBegin);
        if (n > 0) {
            do {
                DispatchMesh(mMeshesBegin[i], i, a2, &c);
                ++i;
            } while (i < n);
        }
    }
    Listener* l = mListener;
    if (l)
        l->OnDispatch(this, &c, a2);
    return c.result;
}


// @ 0x0073fe80 / 0x0073ffb0  bone-binding validators (3 bindings checked against the mesh set)
inline void RcReleaseChecked(RC* p) {
    long r = _InterlockedDecrement((volatile long*)&p->mnRefCount);
    if (r == 0) { _InterlockedExchange((volatile long*)&p->mnRefCount, 1); if (p) p->v0(1); }
}
struct MeshPtr { RC* p; };
struct MeshVec {
    MeshPtr* b; MeshPtr* e; MeshPtr* c; int alloc[2];
    MeshVec() { b = 0; e = 0; c = 0; }
    void DestroyRange(MeshPtr* first, MeshPtr* last);   // 0x4243e0
    ~MeshVec() {
        DestroyRange(b, e);
        if (b && ((int*)b)[-1] != 0) operator_delete__(b);
    }
};
struct ModelInstanceMeshes { void GetMeshes(MeshVec& out); };   // 0x73eb90
struct BindQuery {
    RC* p; int a, b, count, c, d;
    BindQuery() : p(0), a(-1), b(-1), count(0), c(-1), d(0) {}
    ~BindQuery() { if (p) RcReleaseChecked(p); }
    bool Check(void* item, int n, int i, int x, int y);      // 0x73c290
};
bool __cdecl BuildQuery(BindQuery* q, MeshVec* meshes, int arg);        // 0x732220
bool __cdecl CheckEntry(BindQuery* q, int i, void* a, void* b);         // 0x73c4b0

struct BindingsA {
    char pad[0xc];
    ModelInstanceMeshes* mInst;   // +0xc
    int mArg;                // +0x10
    char items[0x24];        // +0x14, 3 x 0xc
    bool Validate();         // 0x73fe80
};
// @ 0x0073fe80
bool __fastcall ValidateA(char* self)
{
    bool ok = false;
    MeshVec meshes;
    (*(ModelInstanceMeshes**)(self + 0xc))->GetMeshes(meshes);
    BindQuery q;
    if (BuildQuery(&q, &meshes, *(int*)(self + 0x10)) && q.count == 3) {
        ok = true;
        self += 0x14;
        for (int i = 0; i < 3; ++i) {
            if (ok && q.Check(self, 3, i, 1, -1)) ok = true;
            else ok = false;
            self += 0xc;
        }
    }
    return ok;
}
struct BindingsB {
    char pad[0xc];
    ModelInstanceMeshes* mInst;   // +0xc
    int mArg;                // +0x10
    char items[0x84];        // +0x14, 3 x 0x2c
    bool Validate();         // 0x73ffb0
};
// @ 0x0073ffb0
bool __fastcall ValidateB(char* self)
{
    bool ok = false;
    MeshVec meshes;
    (*(ModelInstanceMeshes**)(self + 0xc))->GetMeshes(meshes);
    BindQuery q;
    if (BuildQuery(&q, &meshes, *(int*)(self + 0x10)) && q.count == 3) {
        ok = true;
        self += 0x30;
        for (int i = 0; i < 3; ++i) {
            if (ok && q.Check(self - 0x1c, 3, i, 1, -1) && CheckEntry(&q, i, self - 0x10, self)) ok = true;
            else ok = false;
            self += 0x2c;
        }
    }
    return ok;
}


// @ 0x007400f0 / 0x00740160  binding-set ctor / dtor
inline void BindFreeBuf(int* b) { if (b && b[-1] != 0) operator_delete__(b); }
struct BindPodVec {
    int* b; int* e; int* c; int alloc[2];
    BindPodVec() { b = 0; e = 0; c = 0; }
    ~BindPodVec() { BindFreeBuf(b); }
};
struct BindRcObj { virtual void v0(); virtual void Release(); };
struct BindSmartPtr { BindRcObj* p; BindSmartPtr() { p = 0; } ~BindSmartPtr() { if (p) p->Release(); } };
struct BindElem { void ResetInterpolators(); void NoOp(); };   // 0x75b410 / 0x11fb220
struct BindPool { void Free(BindElem* e); };                       // 0x9276c0
extern BindPool* gBindPool;                                        // 0x16c8b44
struct BindRefVec {
    int* b; int* e; int* c; int alloc[2];
    BindRefVec() { b = 0; e = 0; c = 0; }
    void DestroyRange(int* first, int* last);              // 0x73f2e0
    ~BindRefVec() { DestroyRange(b, e); BindFreeBuf(b); }
};
struct BindingBase { virtual void v0(); int f4; BindingBase() { f4 = 0; } virtual ~BindingBase() {} };
struct BindingSet : BindingBase {
    uint32_t mFlags; int f0c, f10;     // +8
    BindPodVec pv14;
    BindRefVec rv28;
    BindPodVec pv3c;
    BindPodVec pv50;
    BindPodVec elems;                      // +0x64
    BindPodVec pv78;
    int pad8c;
    int f90, f94;
    BindSmartPtr p98;
    BindingSet();
    ~BindingSet();
    virtual void v0();
};
// @ 0x007400f0
BindingSet::BindingSet() : mFlags(0), f0c(0), f10(0), f90(0), f94(0) {}
// @ 0x00740160
BindingSet::~BindingSet()
{
    int i = 0;
    int n = (int)(elems.e - elems.b);
    if (mFlags & 0x20) {
        if (n > 0) {
            do {
                ((BindElem*)elems.b[i])->ResetInterpolators();
                gBindPool->Free((BindElem*)elems.b[i]);
                elems.b[i] = 0;
                ++i;
            } while (i < n);
        }
    } else {
        if (n > 0) {
            do {
                ((BindElem*)elems.b[i])->NoOp();
                gBindPool->Free((BindElem*)elems.b[i]);
                elems.b[i] = 0;
                ++i;
            } while (i < n);
        }
    }
}


// @ 0x007402e0  destructor of the skin/animation binding container (EH)
struct IdPtrVec { int d[5]; ~IdPtrVec(); };       // 0x421190
struct RefVector { int d[5]; ~RefVector(); };     // 0x41eb80
struct ContPodVec {
    int* b; int* e; int* c; int alloc[2];
    ~ContPodVec() throw() { if (b && b[-1] != 0) operator_delete__(b); }
};
struct BindingContainer {
    ContPodVec a, b, c;
    RefVector refs;    // +0x3c
    IdPtrVec ids;      // +0x50
    ~BindingContainer();
};
// @ 0x007402e0
BindingContainer::~BindingContainer() {}



// @ 0x0073f540 / 0x0073f910  PickLine / IntersectsSphere
struct V4 { float x, y, z, w; };
struct M4 { V4 r0, r1, r2, t; };                   // 3 basis rows + translation row

struct cSPBoundingBox { float mMin[3]; float mMax[3];
    void Transform(const void* m);                 // 0x409dd0
};
struct PartTransform64 {                           // 0x40-byte matrix helper
    char d[0x40];
    PartTransform64(const cSPTransform& t);        // 0x40ce80 (thiscall, ret 4)
    void Invert();                                 // 0x40efa0
};

struct QueryItem {                                 // 0x60 bytes
    char pad0[0x44];
    uint32_t mFlags;                               // +0x44, bit 0 = visited
    char pad48[0x60 - 0x48];
    int Test(int a, int b, const void* arg);       // 0x12022b0 (ret 0xc)
};
struct BoxPair {                                   // (min, max) as 4-lane vectors
    V4 mMin, mMax;
    int Overlaps(const void* arg);                 // 0x73f110 (ret 4)
};
struct __declspec(align(16)) QueryState {          // 0xf4 bytes, global singleton
    void**     mppScratch;                         // +0x00
    int        f04, f08, f0c;
    V4         mMin;                               // +0x10
    V4         mMax;                               // +0x20
    char       pad30[0x10];
    int        f40;                                // +0x40
    char       pad44[0xc0 - 0x44];
    int        fc0;
    char       pad_c4[8];
    int        fcc;
    char       pad_d0[4];
    QueryItem* mItems;                             // +0xd4
    uint32_t   mItemCount;                         // +0xd8
    char       pad_dc[4];
    int        fe0;
    char       pad_e4[4];
    int        fe8;
    int        fec;
    char       ff0;
};
struct QueryAlloc;
struct QueryAllocVT { char pad[0x18]; int (__thiscall *Query)(QueryAlloc* self, QueryState* q, const void* basis); };
struct QueryAlloc { char pad[0x20]; QueryAllocVT* vt; };
struct ExternalTable { QueryAlloc* GetAllocator(); };      // 0x7f54d0

// Lazy-singleton construction helpers (opaque callees).
void* __cdecl QueryStage1(void* buf, int a, int b);                       // 0x1204110
void  __cdecl QueryStage2(void* dst, void* src);                          // 0x6c1c80
QueryState* __cdecl QueryStage3(void* tmp, int a, int b);                 // 0x1204180
void  __stdcall EhVecDtor(void* p, unsigned size, int count, void* dtor);  // 0x11e0b22 (__ehvec_dtor)
extern char Elem8Dtor;                                                    // 0xc2e4e0
extern QueryState* gPickQuery;                                            // 0x162eaf4
extern QueryState* gSphereQuery;                                          // 0x162eaf8

extern const float kRay0, kRay1, kRay2;            // 0x153782c / 0x1537830 / 0x1537834
extern const float kOne;                           // 0x1485720

static int RunQuery(ExternalTable* table, QueryState* q, const void* basis)
{
    QueryAlloc* a = table->GetAllocator();
    return a->vt->Query(a, q, basis);
}

static QueryState* GetQuery(QueryState*& slot)
{
    if (slot == 0) {
        char scratch[32];
        char tmp[0x10];
        void* t = QueryStage1(scratch, 8, 8);
        QueryStage2(tmp, t);
        EhVecDtor(scratch, 8, 4, &Elem8Dtor);
        slot = QueryStage3(tmp, 8, 8);
    }
    return slot;
}

static void InitQuery(QueryState* q, void** scratchSlot, const V4& mn, const V4& mx)
{
    q->mppScratch = scratchSlot;
    q->f04 = 0;
    q->f08 = 1;
    q->f0c = 0;
    q->fc0 = 0;
    q->fcc = 0;
    q->f40 = 0;
    q->fe0 = 0;
    q->fe8 = 0;
    q->mItemCount = 0;
    q->mMin = mn;
    q->mMax = mx;
    q->fec = 0;
    q->ff0 = 0;
}

struct cModelInstanceQ {
    char pad0[0xcc];
    ExternalTable* mExternalBoneTable;             // +0xcc
    bool PickLine(const float* origin, float len, const cSPTransform* xf, bool firstHitOnly);
    bool IntersectsSphere(const cSPBoundingBox* box, const cSPTransform* xf, bool firstHitOnly);
};

// @ 0x0073f540
bool cModelInstanceQ::PickLine(const float* origin, float len, const cSPTransform* xf, bool firstHitOnly)
{
    if (!mExternalBoneTable)
        return false;
    float p[3] = { origin[0], origin[1], origin[2] };
    M4 basis;
    if (xf->mScale == 1.0f) {
        const float s = xf->mScale;
        basis.r0.x = xf->mRotation[0] * s; basis.r0.y = xf->mRotation[1] * s; basis.r0.z = xf->mRotation[2] * s;
        basis.r1.x = xf->mRotation[3] * s; basis.r1.y = xf->mRotation[4] * s; basis.r1.z = xf->mRotation[5] * s;
        basis.r2.x = s * xf->mRotation[6]; basis.r2.y = xf->mRotation[7] * s; basis.r2.z = xf->mRotation[8] * s;
        basis.t.x = xf->mTranslation[0]; basis.t.y = xf->mTranslation[1]; basis.t.z = xf->mTranslation[2];
    } else {
        xf->BackTransformPoint(p);
        len = len / xf->mScale;
        basis.r0.x = 1.0f; basis.r0.y = 0.0f; basis.r0.z = 0.0f; basis.r0.w = 0.0f;
        basis.r1.x = 0.0f; basis.r1.y = 1.0f; basis.r1.z = 0.0f; basis.r1.w = 0.0f;
        basis.r2.x = 0.0f; basis.r2.y = 0.0f; basis.r2.z = 1.0f; basis.r2.w = 0.0f;
        basis.t.x = 0.0f; basis.t.y = 0.0f; basis.t.z = 0.0f; basis.t.w = 0.0f;
    }
    V4 mx, mn;
    mx.x = kRay0 * len + p[0];
    mx.y = p[1] + kRay1 * len;
    mx.z = p[2] + kRay2 * len;
    mx.w = mx.x;
    mn.x = p[0] - kRay0 * len;
    mn.y = p[1] - kRay1 * len;
    mn.z = p[2] - kRay2 * len;
    mn.w = mn.x;
    char stackBuf[100];
    void* stackBufPtr = stackBuf;
    QueryState* q = GetQuery(gPickQuery);
    InitQuery(q, &stackBufPtr, mn, mx);
    BoxPair box; box.mMin = mn; box.mMax = mx;
    ExternalTable* table = mExternalBoneTable;
    for (int r = RunQuery(table, q, &basis); r == 0; r = RunQuery(mExternalBoneTable, gPickQuery, &basis)) {
        if (firstHitOnly)
            return true;
        uint32_t i = 0;
        if (gPickQuery->mItemCount != 0) {
            int off = 0;
            do {
                QueryItem* it = (QueryItem*)((char*)gPickQuery->mItems + off);
                it->mFlags &= ~1u;
                if (it->Test(0, 0, &mx) && box.Overlaps(&mx))
                    return true;
                ++i;
                off += 0x60;
            } while (i < gPickQuery->mItemCount);
        }
    }
    return false;
}

// @ 0x0073f910
bool cModelInstanceQ::IntersectsSphere(const cSPBoundingBox* box, const cSPTransform* xf, bool firstHitOnly)
{
    if (!mExternalBoneTable)
        return false;
    M4 basis;
    char invMatrix[0x40];
    V4 mn, mx;
    if (xf->mScale == 1.0f) {
        mx.x = box->mMax[0]; mx.y = box->mMax[1]; mx.z = box->mMax[2]; mx.w = box->mMax[0];
        mn.x = box->mMin[0]; mn.y = box->mMin[1]; mn.z = box->mMin[2]; mn.w = box->mMin[0];
        const float s = xf->mScale;
        basis.t.x = xf->mTranslation[0]; basis.t.y = xf->mTranslation[1]; basis.t.z = xf->mTranslation[2];
        basis.r0.x = s * xf->mRotation[0]; basis.r0.y = xf->mRotation[1] * s; basis.r0.z = xf->mRotation[2] * s;
        basis.r1.x = xf->mRotation[3] * s; basis.r1.y = xf->mRotation[4] * s; basis.r1.z = xf->mRotation[5] * s;
        basis.r2.x = s * xf->mRotation[6]; basis.r2.y = xf->mRotation[7] * s; basis.r2.z = xf->mRotation[8] * s;
    } else {
        PartTransform64 inv(*xf);
        inv.Invert();
        cSPBoundingBox bb = *box;
        bb.Transform(&inv);
        for (int k = 0; k < 0x40; ++k) invMatrix[k] = inv.d[k];
        mn.x = bb.mMin[0]; mn.y = bb.mMin[1]; mn.z = bb.mMin[2]; mn.w = bb.mMin[0];
        mx.x = bb.mMax[0]; mx.y = bb.mMax[1]; mx.z = bb.mMax[2]; mx.w = bb.mMax[0];
        basis.r0.x = 1.0f; basis.r0.y = 0.0f; basis.r0.z = 0.0f; basis.r0.w = 0.0f;
        basis.r1.x = 0.0f; basis.r1.y = 1.0f; basis.r1.z = 0.0f; basis.r1.w = 0.0f;
        basis.r2.x = 0.0f; basis.r2.y = 0.0f; basis.r2.z = 1.0f; basis.r2.w = 0.0f;
        basis.t.x = 0.0f; basis.t.y = 0.0f; basis.t.z = 0.0f; basis.t.w = 0.0f;
    }
    char stackBuf[100];
    void* stackBufPtr = stackBuf;
    QueryState* q = GetQuery(gSphereQuery);
    InitQuery(q, &stackBufPtr, mn, mx);
    BoxPair bp; bp.mMin = mn; bp.mMax = mx;
    ExternalTable* table = mExternalBoneTable;
    for (int r = RunQuery(table, q, &basis); r == 0; r = RunQuery(mExternalBoneTable, gSphereQuery, &basis)) {
        if (firstHitOnly)
            return true;
        uint32_t i = 0;
        if (gSphereQuery->mItemCount != 0) {
            int off = 0;
            do {
                QueryItem* it = (QueryItem*)((char*)gSphereQuery->mItems + off);
                it->mFlags &= ~1u;
                if (it->Test(0, 0, invMatrix) && bp.Overlaps(invMatrix))
                    return true;
                ++i;
                off += 0x60;
            } while (i < gSphereQuery->mItemCount);
        }
    }
    return false;
}
