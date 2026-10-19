// Slice s007403c0 (0x007403c0-0x007411b0): SP::cModelInstance bone/region accessors.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <new>

// Callees outside the slice are masked relocations; they are declared with the right calling
// convention and a `// 0x...` address comment (see docs/equivalence.md).
// Flags for the unmatched functions: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-  (no cookie: old-style EH prolog).

// ---------------------------------------------------------------------------
// @ 0x007411b0  eastl::vector<12-byte POD>::push_back
// ---------------------------------------------------------------------------
struct Vec12 { int a, b, c; };

struct Vec12Vector {
    Vec12* mpBegin;                  // +0x0
    Vec12* mpEnd;                    // +0x4
    Vec12* mpCapacity;               // +0x8
    void push_back(const Vec12& value);
    void DoInsertValue(Vec12* pos, const Vec12& value);   // 0x7409d0
};

void Vec12Vector::push_back(const Vec12& value)
{
    Vec12* p = mpEnd;
    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->a = value.a;
            p->b = value.b;
            p->c = value.c;
        }
        return;
    }
    DoInsertValue(p, value);
}

// ===========================================================================
// Bone / region accessors, EASTL vector helpers, cModelInstance ctor/dtor.
// ===========================================================================
#define kEastlFile \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
void* operator new(unsigned int, const char*, int, int, int, int);          // 0x00f473a0 (no matching delete)

struct Elem { uint32_t a, b; Elem(); ~Elem(); };               // 0x006c0fa0 / 0x00c2e4e0
struct ExpObj { uint32_t type; void* obj; uint32_t z0, z1, z2, z3; Elem arr[4];
    ExpObj() : type(0), obj(0), z0(0), z1(0), z2(0), z3(0) { arr[0].a = 0; arr[0].b = 1; }
};
struct Arena {
    int GetNumExportedObjects();                           // 0x011e23a0
    void GetExportedObjectByIndex(int idx, ExpObj* out);   // 0x011e28e0
};
struct ArenaOwner { char pad[0x18]; Arena* arena; };
struct RefIface { virtual void AddRef(); virtual void Release(); };
struct BoneTable : RefIface { char pad[0x48]; BoneTable(ExpObj* e, ArenaOwner* src); };   // 0x00762250, 0x4c bytes
struct PtrArr { void* begin; };
void operator delete[](void* p);                           // 0x00f47380
void operator delete(void* p, const char*, int, int, const char*, int);
void operator delete[](void* p);

struct cModelInstanceBones {
    char pad[0xcc];
    RefIface* mBones;            // +0xcc
    PtrArr* mHull;               // +0xd0
    void LoadExportedBoneTable(ArenaOwner* src);
};

// @ 0x007403c0
void cModelInstanceBones::LoadExportedBoneTable(ArenaOwner* src)
{
    Arena* arena = src->arena;
    int n = arena->GetNumExportedObjects();
    for (int i = 0; i < n; ++i) {
        ExpObj x;
        arena->GetExportedObjectByIndex(i, &x);
        if (x.type == 0x80003) {
            BoneTable* t = new("Graphics", 0, 0, (const char*)0, 0) BoneTable(&x, src);
            RefIface* old = mBones;
            if (t != old) {
                if (t) t->AddRef();
                mBones = t;
                if (old) old->Release();
            }
            PtrArr* h = mHull;
            if (h) {
                void* b = h->begin;
                if (b && ((int*)b)[-1] != 0) operator delete[](b);
                operator delete[](h);
            }
            mHull = 0;
        }
    }
}


// ---------------------------------------------------------------------------
// cModelResourceInfo bone accessors (0x740550, 0x740740)
// ---------------------------------------------------------------------------
struct BoneRange { uint8_t mat; int8_t count; int16_t start; uint32_t pad; };   // 8 bytes
struct Mat12 { float m[12]; };                                                  // 3x4 bone transform, 0x30 bytes
struct MatSrc { Mat12** pm; };                                                  // +8 of the material's aux
struct MatAux { uint32_t pad[2]; Mat12*** pm; };
struct IdSet { uint32_t pad[2]; uint32_t* data; uint32_t count; };              // +8 data, +0xc count
struct MatAux2 { uint32_t pad[3]; IdSet* ids; };                                // +0xc
struct Material {                                                               // 0xc4 bytes
    uint32_t pad0[2];
    union { MatAux* aux; MatAux2* aux2; };                                      // +8
    uint32_t pad[0xc4 / 4 - 3];
};
void MaterialPrepare(Material* m, int z);                          // 0x0073a900 (cdecl)
void CopyMats(Mat12* first, Mat12* last, Mat12* out);              // 0x0073fe20 (cdecl)
void CopyWords(void* dst, void* src, unsigned bytes);              // 0x011e0744 (cdecl)

extern const float g_f01485720;                                    // 1.0f

template <class T> inline const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }
template <class T> inline const T& Max(const T& a, const T& b) { return (b < a) ? a : b; }

struct cModelResourceInfo {
    uint32_t pad0[3];
    int      mClamp;                  // +0x0c
    Mat12*   mClampTable;             // +0x10
    BoneRange* mRangesBegin;          // +0x14
    BoneRange* mRangesEnd;            // +0x18
    uint32_t pad1[3];
    Material* mMats;                  // +0x28
    uint32_t pad2[0x64 / 4 - 0x2c / 4];
    void* mAnimBegin;                 // +0x64
    void* mAnimEnd;                   // +0x68
    int GetBoneTransforms(Mat12* out);      // 0x740550
    int GetBoneIDs(uint32_t* dst);          // 0x740740
};

// @ 0x00740550
int cModelResourceInfo::GetBoneTransforms(Mat12* out)
{
    if (mAnimBegin == mAnimEnd || mRangesBegin == mRangesEnd)
        return 0;
    if (mClampTable != 0 && mClamp != 0) {
        int total = (mRangesBegin == mRangesEnd) ? 0 : mRangesEnd[-1].count + mRangesEnd[-1].start;
        int n = Min(mClamp, total);
        CopyMats(mClampTable, mClampTable + n, out);
    }
    Mat12 ident;
    ident.m[0] = g_f01485720; ident.m[1] = 0; ident.m[2] = 0; ident.m[3] = 0;
    ident.m[4] = 0; ident.m[5] = g_f01485720; ident.m[6] = 0; ident.m[7] = 0;
    ident.m[8] = 0; ident.m[9] = 0; ident.m[10] = g_f01485720; ident.m[11] = 0;
    int numRanges = (int)(mRangesEnd - mRangesBegin);
    for (int i = 0; i < numRanges; ++i) {
        BoneRange* r = mRangesBegin + i;
        int lo = 0;
        if (mClampTable != 0) {
            int t = mClamp - r->start;
            lo = Max(t, 0);
            if (lo >= r->count) continue;
        }
        Mat12* dst = out + r->start;
        if (r->mat == 0xff) {
            for (Mat12* p = dst + lo; p != dst + r->count; ++p)
                *p = ident;
        } else {
            Material* m = mMats + (int8_t)r->mat;
            MaterialPrepare(m, 0);
            Mat12* src = **m->aux->pm;
            Mat12* d = dst + lo;
            for (Mat12* p = src + lo; p != src + r->count; ++p, ++d)
                *d = *p;
        }
    }
    return mRangesEnd[-1].count + mRangesEnd[-1].start;
}

// @ 0x00740740
int cModelResourceInfo::GetBoneIDs(uint32_t* dst)
{
    if (mAnimBegin == mAnimEnd || mRangesBegin == mRangesEnd)
        return 0;
    BoneRange* r = mRangesBegin;
    uint32_t n = 0;
    if (r->mat != 0xff) {
        Material* m = mMats + (int8_t)r->mat;
        uint32_t cnt = (uint32_t)(int)r->count;
        IdSet* ids = m->aux2->ids;
        uint32_t* data = ids->data;
        n = Min(ids->count, cnt);
        CopyWords(dst, data, n * 4);
    }
    uint32_t* end = dst + r->count;
    for (uint32_t* p = dst + n; p != end; ++p)
        *p = 0;
    return r->count;
}

// ---------------------------------------------------------------------------
// EASTL vector helpers shared by the 8- and 12-byte element vectors.
// ---------------------------------------------------------------------------
struct P8 { uint32_t a, b; };
void* H_uninit_copy12(void* first, void* last, void* dest);              // 0x00a11310 (cdecl)
void* H_uninit_copy8(void* first, void* last, void* dest);               // 0x0099efa0 (cdecl)
void* H_copy8(void* first, void* last, void* dest);                      // 0x004554f0 (cdecl)
void  H_move8(void* out, void* a, void* b, void* c, void* d);            // 0x0076ffd0 (cdecl, 5 args)
void  H_copy_backward8(void* first, void* last, void* destEnd);          // 0x0073fe50 (cdecl)
void  H_fill8(void* first, void* last, const P8* value);                 // 0x00a52da0 (cdecl)
void  H_fill_n8(void* dest, uint32_t n, const P8* value);                // 0x006ac440 (cdecl)
void  H_copy8b(void* first, void* last, void* dest);                     // 0x00ac4440 (cdecl)

// @ 0x007409d0  Vec12Vector::DoInsertValue
void Vec12Vector::DoInsertValue(Vec12* pos, const Vec12& value)
{
    Vec12* end = mpEnd;
    if (end != mpCapacity) {
        const Vec12* v = &value;
        if (!(v < pos) && v < end) v += 1;
        if (end) { end->a = end[-1].a; end->b = end[-1].b; end->c = end[-1].c; }
        Vec12* dst = mpEnd;
        Vec12* src = mpEnd - 1;
        while (src != pos) {
            --src; --dst;
            dst->a = src->a; dst->b = src->b; dst->c = src->c;
        }
        pos->a = v->a; pos->b = v->b; pos->c = v->c;
        mpEnd = mpEnd + 1;
        return;
    }
    int n = (int)(end - mpBegin);
    int newCap;
    Vec12* nd;
    if (n != 0) {
        newCap = n * 2;
        if (newCap == 0) { nd = 0; goto haveBuf; }
    } else {
        newCap = 1;
    }
    nd = (Vec12*)operator new(newCap * 12, "Graphics", 0, 0, kEastlFile, 0xd1);
haveBuf:
    Vec12* r = (Vec12*)H_uninit_copy12(mpBegin, pos, nd);
    if (r) { r->a = value.a; r->b = value.b; r->c = value.c; }
    Vec12* ne = (Vec12*)H_uninit_copy12(pos, mpEnd, r + 1);
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
    mpBegin = nd;
    mpEnd = ne;
    mpCapacity = nd + newCap;
}

struct Vec8Vector {
    P8* mpBegin; P8* mpEnd; P8* mpCapacity;
    void DoInsertValues(P8* pos, uint32_t n, const P8& value);               // 0x740b00
    void DoInsertRange(P8* pos, P8* first, P8* last, int tag);               // 0x740cc0
};

// @ 0x00740b00  Vec8Vector::DoInsertValues
void Vec8Vector::DoInsertValues(P8* pos, uint32_t n, const P8& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            P8 tmp = value;
            P8* oldEnd = mpEnd;
            uint32_t after = (uint32_t)(oldEnd - pos);
            if (n < after) {
                P8* mid = oldEnd - n;
                P8* t;
                H_move8(&t, mid, oldEnd, oldEnd, mid);
                mpEnd += n;
                H_copy_backward8(pos, mid, oldEnd);
                H_fill8(pos, pos + n, &tmp);
            } else {
                uint32_t extra = n - after;
                P8* t;
                H_fill_n8(oldEnd, extra, &tmp);
                mpEnd += extra;
                H_move8(&t, pos, oldEnd, mpEnd, (void*)after);
                mpEnd += after;
                H_fill8(pos, oldEnd, &tmp);
            }
        }
    } else {
        uint32_t prev = (uint32_t)(mpEnd - mpBegin);
        uint32_t grow = prev > 0 ? prev * 2 : 1;
        uint32_t newCap = prev + n;
        if (!(newCap > grow)) newCap = grow;
        P8* nd = 0;
        if (newCap) nd = (P8*)operator new(newCap * 8, "Graphics", 0, 0, kEastlFile, 0xd1);
        P8* np = (P8*)H_uninit_copy8(mpBegin, pos, nd);
        P8* q = np;
        for (uint32_t i = n; i > 0; --i) {
            if (q) { q->a = value.a; q->b = value.b; }
            ++q;
        }
        P8* ne = (P8*)H_uninit_copy8(pos, mpEnd, np + n);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
        mpBegin = nd;
        mpEnd = ne;
        mpCapacity = nd + newCap;
    }
}

// @ 0x00740cc0  Vec8Vector::DoInsertRange
void Vec8Vector::DoInsertRange(P8* pos, P8* first, P8* last, int tag)
{
    (void)tag;
    if (first == last) return;
    uint32_t n = (uint32_t)(last - first);
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        P8* oldEnd = mpEnd;
        uint32_t after = (uint32_t)(oldEnd - pos);
        if (n < after) {
            P8* mid = oldEnd - n;
            P8* t;
            H_move8(&t, mid, oldEnd, oldEnd, first);
            mpEnd += n;
            H_copy_backward8(pos, mid, oldEnd);
            H_copy8b(first, last, pos);
        } else {
            P8* mid = first + after;
            P8* t;
            H_move8(&t, mid, last, oldEnd, first);
            mpEnd += n - after;
            H_move8(&t, pos, oldEnd, mpEnd, first);
            mpEnd += after;
            H_copy_backward8(first, mid, pos + after);
        }
    } else {
        uint32_t prev = (uint32_t)(mpEnd - mpBegin);
        uint32_t newCap = prev * 2;
        if (prev == 0) newCap = 1;
        if (!(newCap > prev + n)) newCap = prev + n;
        P8* nd = 0;
        if (newCap) nd = (P8*)operator new(newCap * 8, "Graphics", 0, 0, kEastlFile, 0xd1);
        P8* np = (P8*)H_copy8(mpBegin, pos, nd);
        P8* t;
        H_move8(&t, first, last, np, first);
        P8* ne = (P8*)H_copy8(pos, mpEnd, np);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
        mpBegin = nd;
        mpEnd = ne;
        mpCapacity = nd + newCap;
    }
}

// ---------------------------------------------------------------------------
// 0x7407d0  cModelInstance: create a binding object and validate it
// ---------------------------------------------------------------------------
struct Binding : RefIface {
    uint32_t pad[3];
    uint32_t mKey;           // +0x10
    RefIface* mTarget;       // +0x14
    uint32_t pad2[2];
};
struct Owner { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
               virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
               virtual bool Validate(uint32_t key, RefIface** target); };   // vtable slot 8 (+0x20)
struct VecHdr { Material* mpBegin; Material* mpEnd; };
struct ResRef {
    uint32_t pad[10];
    void* v28Begin; void* v28End;            // +0x28 / +0x2c
    uint32_t pad2[8];
    void* v50Begin; void* v50End;            // +0x50 / +0x54
};
struct T20 : Binding { T20(void* mi, uint32_t a2, void* v1, void* v2); };   // 0x0073aa70, 0x20 bytes
struct T9c : RefIface { uint32_t pad[0x98 / 4]; T9c(void* mi, uint32_t a2, void* v1); };               // 0x0073cb40
struct T38 : RefIface { uint32_t pad[0x34 / 4]; T38(void* mi, uint32_t a2); };                         // 0x0073cac0
bool __fastcall ValidateB(T9c* p);       // 0x0073ffb0
bool __fastcall ValidateA(T38* p);       // 0x0073fe80
template <class T> struct Hold {
    T* p;
    explicit Hold(T* q) : p(q) { if (p) p->AddRef(); }
    ~Hold() { if (p) p->Release(); }
};

struct cModelInstanceB {
    uint32_t pad[0xec / 4];
    Owner* mOwner;           // +0xec
    ResRef* mRes;            // +0xf0
    bool CreateBinding(uint32_t a2, RefIface** out);       // 0x7407d0
};

// @ 0x007407d0
bool cModelInstanceB::CreateBinding(uint32_t a2, RefIface** out)
{
    ResRef* B = mRes;
    void* c = B->v28Begin;
    if (mOwner) {
        void* v1;
        if (c == B->v28End) v1 = 0; else v1 = c;
        void* v2;
        if (B->v50Begin == B->v50End) v2 = 0; else v2 = B->v50Begin;
        Binding* b = new("Graphics", 0, 0, 0, 0) T20(this, a2, v1, v2);
        Hold<Binding> h(b);
        Owner* o = mOwner;
        RefIface* old = b->mTarget;
        if (old) { b->mTarget = 0; old->Release(); }
        if (o->Validate(b->mKey, &b->mTarget)) {
            b->AddRef();
            *out = b;
            return true;
        }
        return false;
    }
    if (c != B->v28End) {
        T9c* t = new("Graphics", 0, 0, 0, 0) T9c(this, a2, c);
        Hold<T9c> h(t);
        if (ValidateB(t)) {
            t->AddRef();
            *out = t;
            return true;
        }
    }
    T38* t = new("Graphics", 0, 0, 0, 0) T38(this, a2);
    Hold<T38> h(t);
    if (ValidateA(t)) {
        t->AddRef();
        *out = t;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// cModelInstance constructor (0x740e90) / destructor body (0x741040) / region map lookup (0x741150)
// ---------------------------------------------------------------------------
struct Matrix3 { float m[9]; Matrix3(const Matrix3& src); };   // 0x0041cb40
extern const Matrix3 g_Matrix0162e9cc;
extern const float g_f0162e88c;     // 0x0162e88c
extern const float g_f0162e890;     // 0x0162e890
extern const float g_f0162e894;     // 0x0162e894
extern const float g_fNeg1;         // 0x013eb1bc  -1.0f
extern const float g_fMax;          // 0x0140d56c  FLT_MAX
extern const float g_fMin;          // 0x013f51ac  -FLT_MAX

struct Vec3 { float x, y, z; Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };

struct Xf {
    uint16_t a, b; float f0, f1, f2, w; Matrix3 m;
    Xf() : m(g_Matrix0162e9cc) { f0 = g_f0162e88c; f1 = g_f0162e890; f2 = g_f0162e894; a = 0; b = 0; w = g_f01485720; }
};

struct Cell { uint32_t nameA, nameB; uint32_t mpBegin, mpEnd, mpCap; Cell() : mpBegin(0), mpEnd(0), mpCap(0) {} };
struct BindingContainer {
    uint32_t w8, wc, w10;
    Cell cells[4];                       // 0x14, 0x28, 0x3c, 0x50
    uint32_t w64, w68;
    uint8_t  flag6c; uint8_t pad6d[3];
    BindingContainer() : w8(0), wc(0), w10(0) {}
    ~BindingContainer();                 // 0x007402e0
};

extern char vtbl_GmeRefCount[];        // 0x013ef094  ??_7GmeRefCount@@6B@
extern char vtbl_cModelInstance[];     // 0x0140d638
struct RCBase {                        // GmeRefCount: vptr kept as a plain field (no vtable is built here)
    void* vt;
    int mRefCount;
    RCBase() : mRefCount(0) { vt = vtbl_GmeRefCount; }
    ~RCBase() { vt = vtbl_GmeRefCount; }
};
template <class T> struct ARC {
    T* p;
    ARC() : p(0) {}
    ~ARC() { if (p) p->Release(); }
};
struct RCObj { virtual ~RCObj() {} int rc; };
struct IPtr {
    RCObj* p;
    IPtr() : p(0) {}
    ~IPtr() { RCObj* q = p; if (q) { int t = q->rc; q->rc = t - 1; if (t - 1 == 0) { q->rc = 1; delete q; } } }
};
struct HullData { void* begin; };

struct BBox { Vec3 mn, mx; BBox() : mn(g_fNeg1, g_fNeg1, g_fNeg1), mx(g_f01485720, g_f01485720, g_f01485720) {} };

struct cModelInstance : RCBase {
    BindingContainer bc;                 // +0x08
    Xf       mTransform;                 // +0x70
    BBox     mBox;                       // +0xa8
    float    mRadius;                    // +0xc0
    ARC<RefIface> mResource;             // +0xc4
    uint16_t mFlags;                     // +0xc8
    ARC<RefIface> mBones;                // +0xcc
    HullData* mHull;                     // +0xd0
    Vec3     mHullMin, mHullMax;         // +0xd4 / +0xe0
    ARC<RefIface> mDynamicDraw;          // +0xec
    IPtr     mRes;                       // +0xf0
    uint32_t padf4;
    int      mF8, mFC;                   // +0xf8 / +0xfc

    cModelInstance();                    // 0x740e90
    ~cModelInstance();                   // 0x741040
    void* GetRegionMaterialInfo(int region);    // 0x741150
};

struct Matrix3Place { float m[9]; void Assign(const Matrix3& src); };   // 0x0041cb40

// The retail layout (refcounted base, 0x100 bytes); the base class' destructor is what makes
// the compiler emit an EH frame for this constructor.
struct MInit : RCBase {
    uint32_t w[0x3e];
    MInit();                            // 0x740e90
};

// @ 0x00740e90  (cModelInstance constructor)
MInit::MInit()
{
    vt = vtbl_cModelInstance;
    w[0] = 0; w[1] = 0; w[2] = 0;
    w[5] = 0; w[6] = 0; w[7] = 0;
    w[0xa] = 0; w[0xb] = 0; w[0xc] = 0;
    w[0xf] = 0; w[0x10] = 0; w[0x11] = 0;
    w[0x14] = 0; w[0x15] = 0; w[0x16] = 0;
    *(uint16_t*)((char*)this + 0x72) = 0;
    *(uint16_t*)((char*)this + 0x70) = 0;
    float* f = (float*)this;
    f[0x1d] = g_f0162e88c;
    f[0x1e] = g_f0162e890;
    f[0x1f] = g_f0162e894;
    f[0x20] = g_f01485720;
    ((Matrix3Place*)((char*)this + 0x84))->Assign(g_Matrix0162e9cc);
    f[0x2a] = g_fNeg1;
    f[0x2b] = g_fNeg1;
    f[0x2c] = g_fNeg1;
    f[0x2d] = g_f01485720;
    f[0x2e] = g_f01485720;
    f[0x2f] = g_f01485720;
    f[0x30] = g_f01485720;
    ((uint32_t*)this)[0x31] = 0;
    *(uint16_t*)((char*)this + 0xc8) = 0;
    ((uint32_t*)this)[0x33] = 0; ((uint32_t*)this)[0x34] = 0;
    Vec3 mn(g_fMax, g_fMax, g_fMax);
    *(Vec3*)((char*)this + 0xd4) = mn;
    Vec3 mx(g_fMin, g_fMin, g_fMin);
    *(Vec3*)((char*)this + 0xe0) = mx;
    ((uint32_t*)this)[0x3b] = 0; ((uint32_t*)this)[0x3c] = 0;
    ((uint32_t*)this)[0x3e] = (uint32_t)-1; ((uint32_t*)this)[0x3f] = (uint32_t)-1;
}

// @ 0x00741040
cModelInstance::~cModelInstance()
{
    vt = vtbl_cModelInstance;
    HullData* h = mHull;
    if (h) {
        void* b = h->begin;
        if (b && ((int*)b)[-1] != 0) operator delete[](b);
        operator delete[](h);
    }
    mHull = 0;
    if (mBones.p) {
        RefIface* bones = mBones.p;
        mBones.p = 0;
        bones->Release();
    }
}

struct KeyPair { int key; void* value; };
KeyPair* RegionLowerBound(KeyPair* first, KeyPair* last, const int* key, unsigned flag);   // 0x0042dd00 (cdecl)

struct cModelInstanceR {
    uint32_t pad0[0x30 / 4];
    void* v30Begin; void* v30End;        // +0x30 / +0x34
    uint32_t pad1[(0x44 - 0x38) / 4];
    void* v44Begin; void* v44End;        // +0x44 / +0x48
    uint32_t pad2[(0x58 - 0x4c) / 4];
    KeyPair* mapBegin; KeyPair* mapEnd;  // +0x58 / +0x5c
    uint32_t pad3[(0x6c - 0x60) / 4];
    uint8_t  flag;                       // +0x6c
    void* GetRegionMaterialInfo(int region);
};

// @ 0x00741150
void* cModelInstanceR::GetRegionMaterialInfo(int region)
{
    if (v44Begin == v44End || v30Begin == v30End)
        return 0;
    KeyPair* end = mapEnd;
    KeyPair* it = RegionLowerBound(mapBegin, end, &region, flag);
    if (it == end || region < it->key || it == it + 1)
        it = end;
    if (it != end)
        return it->value;
    return 0;
}
