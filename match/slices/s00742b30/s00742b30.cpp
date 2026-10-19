// Slice s00742b30 (0x00742b30-0x00743b00): SP::cModelWorld highlight/curve getters/setters.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <intrin.h>
#include <new>
#include <math.h>

// External callees (masked relocations).
extern "C" void FUN_00741aa0(void* a, void* b);      // 0x741aa0
extern "C" void FUN_00b41ea0();                       // 0xb41ea0
extern "C" void FUN_006ec390(void* a, void* b);       // 0x6ec390
extern "C" void FUN_007403c0(void* p);                // 0x7403c0

// ===========================================================================
// Small getters / comparators / curve accessors.
// ===========================================================================

// @ 0x00743910
uint8_t __cdecl FlagsNotBit0(int param_1)
{
    uint8_t v = *(uint8_t*)(param_1 + 4);
    return (uint8_t)(~v) & 1;
}

// @ 0x00743920  (strict comparator on +0x10 float)
int __cdecl CompareFloatAt10(int param_1, int param_2)
{
    return *(float*)(param_1 + 0x10) > *(float*)(param_2 + 0x10);
}

// @ 0x00743950  SP::cModelWorld::SetTimeScale
void __stdcall SetTimeScale(int param_1, float scale)
{
    if (param_1 != 0) {
        *(float*)(param_1 + 0x114) = scale;
        return;
    }
    *(float*)0x11c = scale;
}

// @ 0x007439b0
int __stdcall OffsetOrE4(int param_1)
{
    if (param_1 != 0)
        return param_1 + 0xdc;
    return 0xe4;
}

// ---------------------------------------------------------------------------
// Highlight-curve entry accessors (stride 0x20, base offset 0x1b4).
// ---------------------------------------------------------------------------
struct cModelWorld56 {
    // @ 0x00743940  vtable adjustor helper
    int Adjustor(int unused);

    // @ 0x007439d0
    void SetCurveSegment(int* a, int* b, int index);

    // @ 0x00743a20
    void GetCurveSegment(int* a, int* b, int index);

    // @ 0x00743a60
    void SetCurveRange(int index, int begin, int end);

    // @ 0x00743a80
    void GetCurveRange(int index, int* begin, int* end);

    // @ 0x00743b00  SP::cModelWorld::ResetHighlightCurve
    void ResetHighlightCurve();
};

// @ 0x00743940
int cModelWorld56::Adjustor(int unused)
{
    (void)unused;
    return (int)((char*)this - 0xc);
}

// @ 0x007439d0
void cModelWorld56::SetCurveSegment(int* a, int* b, int index)
{
    char* p = (char*)this + index * 0x20;
    *(int*)(p + 0x1bc) = a[0];
    *(int*)(p + 0x1c0) = a[1];
    *(int*)(p + 0x1c4) = b[0];
    *(int*)(p + 0x1c8) = b[1];
    if (*(int*)(p + 0x1b4) < 0)
        *(int*)(p + 0x1b4) = 0;
}

// @ 0x00743a20
void cModelWorld56::GetCurveSegment(int* a, int* b, int index)
{
    char* p = (char*)this + index * 0x20;
    a[0] = *(int*)(p + 0x1bc);
    a[1] = *(int*)(p + 0x1c0);
    b[0] = *(int*)(p + 0x1c4);
    b[1] = *(int*)(p + 0x1c8);
}

// @ 0x00743a60
void cModelWorld56::SetCurveRange(int index, int begin, int end)
{
    char* p = (char*)this + index * 0x20;
    *(int*)(p + 0x1b4) = begin;
    *(int*)(p + 0x1b8) = end;
}

// @ 0x00743a80
void cModelWorld56::GetCurveRange(int index, int* begin, int* end)
{
    if (begin)
        *begin = *(int*)((char*)this + index * 0x20 + 0x1b4);
    if (end)
        *end = *(int*)((char*)this + index * 0x20 + 0x1b8);
}

// @ 0x00743b00
void cModelWorld56::ResetHighlightCurve()
{
    float v = *(float*)((char*)this + 0x890);
    *(float*)((char*)this + 0x87c) = v;
    *(float*)((char*)this + 0x860) = 0.0f;
}


// ===========================================================================
// SP::cModelInstance model-resource construction (functions 0x742b30-0x7434b0).
// Fields are addressed by retail byte offset.
// ===========================================================================
#define AT(T, off) (*(T*)((char*)this + (off)))

struct RC {                       // virtual add-ref / release object
    virtual void AddRef();
    virtual void Release();
};

template <class T> static inline void SetRC(T*& dst, T* v)
{
    T* old = dst;
    if (v != old) {
        if (v) v->AddRef();
        dst = v;
        if (old) old->Release();
    }
}

struct VecInt {                   // eastl vector<int> range insert
    int* mpBegin; int* mpEnd; int* mpCap;
    void insert_range(int* pos, const int* first, const int* last, void* src);   // 0x00715ec0
};
struct VecInt2 {                  // second vector flavour at +0x1c
    int* mpBegin; int* mpEnd; int* mpCap;
    void insert_range(int* pos, const int* first, const int* last, void* src);   // 0x00740cc0
};
struct RefVec { void Assign(const void* src); };                                  // 0x0041ebe0

struct Obj138 : RC {
    virtual RC* Get();            // slot 2
};
struct ObjEC : RC {
    virtual void s2();
    virtual void s3();
    virtual void Apply(void* p);  // slot 4
};

struct E8 { uint8_t a, b; uint16_t c; uint8_t d, e; uint16_t f; };
struct VecE8 {
    E8* mpBegin; E8* mpEnd; E8* mpCap;
    void Grow(E8* pos, const E8& v);                    // 0x006ec390
    void push(const E8& v) {
        if (mpEnd < mpCap) {
            E8* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            Grow(mpEnd, v);
        }
    }
};
struct ArenaOwner;

struct RefCounted {
    virtual void* Del(unsigned flags);       // slot 0: scalar deleting destructor
    volatile long mnRefCount;     // +4
    void Release() {
        long r = _InterlockedDecrement(&mnRefCount);
        if (r == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            Del(1);
        }
    }
};
struct AR {                      // intrusive smart pointer to RefCounted
    RefCounted* p;
    AR() : p(0) {}
    AR(const AR& o) : p(o.p) { if (p) _InterlockedIncrement(&p->mnRefCount); }
    ~AR() { if (p) p->Release(); }
};
struct RefPair8 {
    int value;
    AR second;
    RefPair8(int v, const AR& s) : value(v), second(s) {}
};
extern RefPair8* __cdecl LowerBoundB41ea0(RefPair8* first, RefPair8* last, const RefPair8* v, uint8_t flag);  // 0x00b41ea0
extern RefPair8* __cdecl LowerBound42dd00(RefPair8* first, RefPair8* last, const int* key, uint8_t flag);     // 0x0042dd00

struct Map8 {
    RefPair8* mpBegin; RefPair8* mpEnd; RefPair8* mpCap; uint32_t pad[2];
    uint8_t flag;                                       // +0x14
    RefPair8* insert(RefPair8* pos, const RefPair8* v); // 0x00741aa0
    RefPair8* MapInsert(RefPair8* pos, RefPair8* value);// 0x00742ca0
    AR* GetOrAdd(const int* key);              // 0x00742f60
};

struct Src : RC {                 // source model resource (retail offsets)
    uint32_t pad04[5];
    int* v18; int* v1c;           // +0x18
    char pad20[0xb8 - 0x20];
    int* vb8; int* vbc;
    char padc0[0xe0 - 0xc0];
    int* ve0; int* ve4;
    char pade8[0xf4 - 0xe8];
    char rv_f4[0x11c - 0xf4];
    int i11c, i120, i124, i128, i12c, i130;
    float f134;
    Obj138* o138;
    void* p13c;
};

struct cMI {
    void AddAnimationsFromArena(RC* arena, int a, uint16_t* b, uint16_t* c);   // 0x00741b10
    void Fn7403c0(void* p);                                                     // 0x007403c0
    void Sub2b30(Src* src);
    void SetAnimationResource(RC* p);
    void ConstructFromGameModelResource(char* src);
};

// @ 0x00742b30
void cMI::Sub2b30(Src* src)
{
    SetRC(AT(RC*, 0xc4), (RC*)src);
    AT(int, 0xb4) = src->i128;
    AT(int, 0xb8) = src->i12c;
    AT(int, 0xbc) = src->i130;
    AT(int, 0xa8) = src->i11c;
    AT(int, 0xac) = src->i120;
    AT(int, 0xb0) = src->i124;
    AT(float, 0xc0) = src->f134;
    Obj138* o = src->o138;
    if (o) {
        SetRC(AT(ObjEC*, 0xec), (ObjEC*)o->Get());
        AT(ObjEC*, 0xec)->Apply((char*)this + 0x30);
    }
    ((RefVec*)((char*)this + 0x44))->Assign(&src->rv_f4);
    if (src->v18 != src->v1c) {
        ((VecInt*)((char*)this + 8))->insert_range(AT(int*, 8), src->v18, src->v1c, src);
        ((VecInt*)((char*)this + 0x30))->insert_range(AT(int*, 0x30), src->vb8, src->vbc, src);
    }
    if (src->ve0 != src->ve4)
        ((VecInt2*)((char*)this + 0x1c))->insert_range(AT(int*, 0x1c), src->ve0, src->ve4, src);
    if (src->p13c)
        Fn7403c0(src->p13c);
}

// @ 0x00742ca0
__declspec(noinline) RefPair8* Map8::MapInsert(RefPair8* pos, RefPair8* value)
{
    RefPair8* end = mpEnd;
    RefPair8* r;
    if (pos != end && value->value < pos->value)
        r = LowerBoundB41ea0(mpBegin, pos, value, flag);
    else
        r = LowerBoundB41ea0(pos, end, value, flag);
    if (r == end || value->value < r->value)
        r = insert(r, value);
    return r;
}

// @ 0x00742cf0
void cMI::SetAnimationResource(RC* p)
{
    SetRC(AT(RC*, 0x98), p);
    if (!(AT(uint32_t, 8) & 1)) {
        AddAnimationsFromArena(p, 0, 0, 0);
        return;
    }
    E8 e = { 0xff, 0, 0, 0, 0, 0 };
    ((VecE8*)((char*)this + 0x14))->push(e);
}

// @ 0x00742db0
void cMI::ConstructFromGameModelResource(char* src)
{
    SetRC(AT(RC*, 0x98), (RC*)src);
    int* mb = *(int**)(src + 0x108);
    int* me = *(int**)(src + 0x10c);
    E8 e;
    uint32_t flags;
    if (mb != me && !((flags = AT(uint32_t, 8)) & 1)) {
        int sum = 0;
        if ((uint32_t)(((char*)*(int**)(src + 0x10c) - (char*)*(int**)(src + 0x108)) / 0x7c) > 1)
            AT(uint32_t, 8) = flags | 2;
        int n = (int)(((char*)*(int**)(src + 0x10c) - (char*)*(int**)(src + 0x108)) / 0x7c);
        for (int off = 0; n > 0; n--, off += 0x7c) {
            char* m = (char*)*(int**)(src + 0x108) + off;
            RC* arena = *(RC**)(m + 0x74);
            if (!arena) {
                e.a = 0xff;
                e.b = *(uint8_t*)(m + 0x70);
                e.c = (uint16_t)sum;
                e.d = 0; e.e = 0; e.f = 0;
                ((VecE8*)((char*)this + 0x14))->push(e);
            } else {
                AddAnimationsFromArena(arena, *(int*)(m + 0x78), (uint16_t*)m, (uint16_t*)(m + 0x38));
            }
            sum += *(char*)(AT(char*, 0x18) - 7);
        }
        return;
    }
    e.a = 0xff; e.b = 0; e.c = 0; e.d = 0; e.e = 0; e.f = 0;
    ((VecE8*)((char*)this + 0x14))->push(e);
}

// @ 0x00742f60
AR* Map8::GetOrAdd(const int* key)
{
    RefPair8* r = LowerBound42dd00(mpBegin, mpEnd, key, flag);
    if (r == mpEnd || *key < r->value) {
        AR def;
        RefPair8 tmp(*key, def);
        r = MapInsert(r, &tmp);
    }
    return &r->second;
}

// ---- fixed vector<int, 64> (see s00421fb0) ----------------------------------
void __cdecl EASTL_allocator_deallocate(void* p);               // 0x00f47380

struct FixedVec64 {
    int* mpBegin; int* mpEnd; int* mpCap;
    uint32_t mFlags; void* mpPool; uint32_t mReserved;
    int mBuffer[64];
    FixedVec64(uint32_t n, int value);                           // 0x00422740
    ~FixedVec64() throw() {
        if (mpBegin && mpBegin != mpPool)
            EASTL_allocator_deallocate(mpBegin);
    }
    void DoPushBackAux(int* pos, const int& v);                  // 0x004281d0
    void push_back(const int& v) {
        if (mpEnd < mpCap)
            ::new (mpEnd++) int(v);
        else
            DoPushBackAux(mpEnd, v);
    }
};

struct BoneInfo { uint32_t* flags; uint32_t pad[4]; int count; };      // flags +0, count +0x14
struct MatEntry { uint32_t pad[3]; BoneInfo* info; };                    // info +0xc

struct cMI2 {
    int GetBoneParents(int* out);                                        // 0x00743030
    void Sub3150(int tag, RefCounted* mat);                              // 0x00743150
};

// @ 0x00743030  SP::cModelInstance::GetBoneParents
int cMI2::GetBoneParents(int* out)
{
    MatEntry** mats = AT(MatEntry**, 0x28);
    if (mats != AT(MatEntry**, 0x2c)) {
        MatEntry* m = mats[2];
        if (m && m->info) {
            BoneInfo* info = m->info;
            FixedVec64 stack(1, -1);
            int cur = -1;
            for (int i = 0; i < info->count; i++) {
                out[i] = cur;
                switch (info->flags[i] & 3) {
                case 0:
                    cur = i;
                    break;
                case 1:
                    cur = stack.mpEnd[-1];
                    stack.mpEnd -= 1;
                    break;
                case 2:
                    stack.push_back(cur);
                    cur = i;
                    break;
                }
            }
            return info->count;
        }
    }
    return 0;
}

// ---- refcounted-pointer slot assignment -------------------------------------
struct ES {                                   // rw::graphics::EmbeddedState view
    uint32_t pad[2]; uint32_t flags;
    int* D3D9GetShaderData(int id);           // 0x011edcf0
};
struct Item2 { uint32_t pad; ES* es; };       // +4
struct SlotVec { Item2** mpBegin; Item2** mpEnd; Item2** mpCap; };
struct RefVecMat { void resize(int n); };     // 0x0041ee90

static __forceinline void AssignAR(AR& dst, RefCounted* v)
{
    RefCounted* old = dst.p;
    if (v != old) {
        if (v) _InterlockedIncrement(&v->mnRefCount);
        dst.p = v;
        if (old) old->Release();
    }
}

// @ 0x00743150
void cMI2::Sub3150(int tag, RefCounted* mat)
{
    if (AT(int, 0x30) == AT(int, 0x34))
        return;
    if (AT(int, 0x44) == AT(int, 0x48))
        ((RefVecMat*)((char*)this + 0x44))->resize((AT(int, 0x34) - AT(int, 0x30)) >> 2);
    int n = (AT(int, 0x34) - AT(int, 0x30)) >> 2;
    for (int i = 0; i < n; i++) {
        ES* es = (*(Item2**)(AT(int, 0x30) + i * 4))->es;
        if (es && (es->flags & 8)) {
            int* d = es->D3D9GetShaderData(0x20f);
            if (d && *d == tag)
                AssignAR(*(AR*)(AT(int, 0x44) + i * 4), mat);
        }
    }
    AssignAR(*((Map8*)((char*)this + 0x58))->GetOrAdd(&tag), mat);
}

// ---- 0x00743270: build per-mesh instance objects ------------------------------
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

struct TObj {                              // GmeRefCount: virtual ref-counted base
    virtual void* Del(unsigned flags);
    volatile long mnRefCount;
    TObj() { _InterlockedExchange(&mnRefCount, 0); }
};
struct Ref {
    TObj* p;
    Ref(TObj* o) : p(o) { if (p) _InterlockedIncrement(&p->mnRefCount); }
    Ref(const Ref& o) : p(o.p) { if (p) _InterlockedIncrement(&p->mnRefCount); }
    ~Ref() {
        if (p) {
            long r = _InterlockedDecrement(&p->mnRefCount);
            if (r == 0) {
                _InterlockedExchange(&p->mnRefCount, 1);
                p->Del(1);
            }
        }
    }
};
struct RefVecL {
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; uint32_t alloc;
    RefVecL() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~RefVecL();                                              // 0x0041eb80
    void DoInsertValue(Ref* pos, const Ref& v);              // 0x00424430
    void push_back(const Ref& v) {
        if (mpEnd < mpCap)
            ::new (mpEnd++) Ref(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct MeshVec {                                             // local vector of mesh refs
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; uint32_t alloc;
    MeshVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void DestroyRange(Ref* first, Ref* last);                // 0x004243e0
    ~MeshVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};
struct VecA {
    int* a; int* b; int* c;
    VecA() : a(0), b(0), c(0) {}
    VecA& operator=(const VecA& x);                         // 0x00735dd0
};
struct VecB {
    int* a; int* b; int* c;
    VecB() : a(0), b(0), c(0) {}
    VecB& operator=(const VecB& x);                         // 0x00738d10
};
struct VecC {
    int* a; int* b; int* c;
    VecC() : a(0), b(0), c(0) {}
    VecC& operator=(const VecC& x);                         // 0x00715120
};
struct VecD {
    int* a; int* b; int* c;
    VecD() : a(0), b(0), c(0) {}
    VecD& operator=(const VecD& x);                         // 0x00735260
};
struct Obj58 : TObj {
    VecA v8; uint32_t pad14[2];
    VecB v1c; uint32_t pad28[2];
    VecC v30; uint32_t pad3c[2];
    VecD v44; uint32_t pad50[2];
    virtual void* Del(unsigned flags);
};
struct MeshSrc {                                             // a mesh record (retail offsets)
    uint32_t pad0[2];
    VecA v8; uint32_t pad14[2];
    VecB v1c; uint32_t pad28[2];
    VecC v30; uint32_t pad3c[2];
    VecD v44;
};
struct Matrix3 { float m[9]; Matrix3(const Matrix3& src); };   // 0x0041cb40
extern const Matrix3 g_Matrix0162e9cc;
extern const float g_f0162e88c;                            // 0x0162e88c
extern const float g_f0162e890;                            // 0x0162e890
extern const float g_f0162e894;                            // 0x0162e894
extern const float g_f01485720;                            // 0x01485720
struct Xf {
    uint16_t a, b; float f0, f1, f2, w; Matrix3 m;
    Xf() : a(0), b(0), f0(g_f0162e88c), f1(g_f0162e890), f2(g_f0162e894), w(g_f01485720), m(g_Matrix0162e9cc) {}
};
struct Elem {
    uint32_t a, b;
    Elem();                                                 // 0x006c0fa0
    ~Elem();                                                // 0x00c2e4e0
};
struct BoneProv {
    int GetBoneTransforms(void* buf);                       // 0x00740550
};
bool __cdecl SkinMesh(void* bones, MeshSrc* mesh, Obj58* obj);   // 0x0073a110
void __cdecl Fn734d00(Xf* a2, Obj58* obj);                       // 0x00734d00

struct cMI3 {
    bool GetMeshes(MeshVec* out);                            // 0x0073eb90
    bool Sub3270(Xf* a2, RefVecL* out);
    bool Sub34b0(float* out);
};

// @ 0x00743270
bool cMI3::Sub3270(Xf* a2, RefVecL* out)
{
    MeshVec meshes;
    GetMeshes(&meshes);
    if (meshes.mpBegin == meshes.mpEnd)
        return false;
    uint32_t buf[0x2ffc / 4];
    int bones = AT(BoneProv*, 0xf0)->GetBoneTransforms(buf);
    int n = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < n; i++) {
        Ref obj(new ("Graphics", 0, 0, 0, 0) Obj58);
        if (!bones || !SkinMesh(buf, (MeshSrc*)meshes.mpBegin[i].p, (Obj58*)obj.p)) {
            Obj58* o = (Obj58*)obj.p;
            MeshSrc* mesh = (MeshSrc*)meshes.mpBegin[i].p;
            o->v8 = mesh->v8;
            o->v1c = mesh->v1c;
            o->v30 = mesh->v30;
            o->v44 = mesh->v44;
        }
        Fn734d00(a2, (Obj58*)obj.p);
        out->push_back(obj);
    }
    return true;
}

// ---- 0x007434b0: model bounds + KD tree --------------------------------------
extern const float kFltMax;                                  // 0x0140d56c
extern const float kNegFltMax;                               // 0x013f51ac
struct V3 {
    float x, y, z;
    V3(float a) : x(a), y(a), z(a) {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Obj90 { uint32_t pad[0x24]; int w90; int w94; };      // +0x90 / +0x94
struct KDZ { uint32_t z[6]; KDZ() { z[0] = 0; z[1] = 0; z[2] = 0; z[3] = 0; z[4] = 0; z[5] = 0; } };
struct KD : KDZ { Elem arr[4]; };
struct DynArr { uint32_t a, b, c; uint32_t pad[2]; DynArr() : a(0), b(0), c(0) {} };
struct KDObj : RC {
    uint32_t pad[18];
    KDObj(KD* kd, int z);                                   // 0x00762250
};
int __cdecl MakeKDTree(RefVecL* meshes, float* extent, DynArr* arr, int leaf, KD* kd);   // 0x0072c270
void __cdecl AccumBounds(TObj* mesh, V3* bounds);            // 0x00732a30
struct ArrHolder {
    void SetArray(DynArr* a);                               // 0x00740370
};
static inline const float& MaxRef(const float& a, const float& b) { return (a < b) ? b : a; }

// @ 0x007434b0
bool cMI3::Sub34b0(float* out)
{
    Obj90* o = AT(Obj90*, 0xf0);
    if (o->w90 == AT(int, 0xf8) && o->w94 == AT(int, 0xfc)) {
        if (out) {
            ((uint32_t*)out)[3] = AT(uint32_t, 0xe0); ((uint32_t*)out)[4] = AT(uint32_t, 0xe4); ((uint32_t*)out)[5] = AT(uint32_t, 0xe8);
            ((uint32_t*)out)[0] = AT(uint32_t, 0xd4); ((uint32_t*)out)[1] = AT(uint32_t, 0xd8); ((uint32_t*)out)[2] = AT(uint32_t, 0xdc);
        }
        return true;
    }
    AT(int, 0xf8) = o->w90;
    AT(int, 0xfc) = o->w94;
    RefVecL meshes;
    Xf xf;
    Sub3270(&xf, &meshes);
    AT(V3, 0xd4) = V3(kFltMax);
    AT(V3, 0xe0) = V3(kNegFltMax);
    int n = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < n; i++)
        AccumBounds(meshes.mpBegin[i].p, &AT(V3, 0xd4));
    if (out) {
        ((uint32_t*)out)[3] = AT(uint32_t, 0xe0); ((uint32_t*)out)[4] = AT(uint32_t, 0xe4); ((uint32_t*)out)[5] = AT(uint32_t, 0xe8);
        ((uint32_t*)out)[0] = AT(uint32_t, 0xd4); ((uint32_t*)out)[1] = AT(uint32_t, 0xd8); ((uint32_t*)out)[2] = AT(uint32_t, 0xdc);
    }
    if (meshes.mpBegin == meshes.mpEnd)
        return false;
    DynArr* arr = new ("Graphics", 0, 0, 0, 0) DynArr;
    KD kd;
    kd.arr[0].a = 0;
    kd.arr[0].b = 1;
    int ok = MakeKDTree(&meshes, &AT(float, 0xa8), arr, 0x10, &kd);
    V3 neg(-AT(float, 0xa8), -AT(float, 0xac), -AT(float, 0xb0));
    const float& zz = MaxRef(neg.z, AT(float, 0xbc));
    const float& yy = MaxRef(neg.y, AT(float, 0xb8));
    const float& xx = MaxRef(neg.x, AT(float, 0xb4));
    AT(float, 0xc0) = sqrtf(xx * xx + yy * yy + zz * zz);
    if (ok) {
        SetRC(AT(RC*, 0xcc), (RC*)0);
        KDObj* ko = new ("Graphics", 0, 0, 0, 0) KDObj(&kd, 0);
        SetRC(AT(RC*, 0xcc), (RC*)ko);
        ((ArrHolder*)this)->SetArray(arr);
        return true;
    }
    if (arr) {
        if (arr->a && ((int*)arr->a)[-1])
            EASTL_allocator_deallocate((void*)arr->a);
        EASTL_allocator_deallocate(arr);
    }
    return false;
}
