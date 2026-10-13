// src/game/SPEngine/SPGraphicsModelInstance.cpp -- migrated from slice(s) s00741210, s007403c0, s0073f320, s0073e410, s0073cdf0, s0073afb0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsModelInstance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cMaterial.h"
#include "SP/cModelInstance.h"
#include <intrin.h>
#include "SP/cBoneRange.h"
#include "cSPTransform.h"
#include <xmmintrin.h>
#include "cSPBoundingBox.h"

// ---- items of slice s0073afb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cAnimGroupInfo_s0073_afb0 {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};
}
namespace SP {
struct cMaterial_s0073_afb0 {
    char  pad0[0xb8];
    void* f_b8;             // +0xb8
    void* f_bc;             // +0xbc
    void* f_c0;             // +0xc0
};
}
namespace SP {
class cModelInstance_s0073_afb0 {
public:
    char pad0[0xc];                 // +0x00
    int mFieldC;                    // +0x0c
    void* mField10;                 // +0x10
    cAnimGroupInfo_s0073_afb0* mGroupBegin;    // +0x14
    cAnimGroupInfo_s0073_afb0* mGroupEnd;      // +0x18
    char pad1c[0x28 - 0x1c];
    cMaterial_s0073_afb0* mMaterials;          // +0x28
    char pad2c[0x30 - 0x2c];
    int mField30;                   // +0x30 (address forwarded to a virtual call)
    char pad34[0x90 - 0x34];
    long long mCounter;             // +0x90
    char pad98[0xc8 - 0x98];
    unsigned short mFlags;          // +0xc8
    char padca[0xec - 0xca];
    void* mDynDraw;                 // +0xec
    char padec[0x8];
    char padf4[0x60];

public:
    // @ 0x0073B7E0
    int GetNumBones();  // 0x0073b7e0 (SP::cModelInstance::GetNumBones)
    // @ 0x0073B800
    void SetBoneTable(int a, void* b);  // 0x0073b800 (SP::cModelInstance::SetBoneTable)
    // @ 0x0073B840
    void SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4);  // 0x0073b840 (SP::cModelInstance::SetBoneCallback)
    // @ 0x0073B8E0
    void SetDynamicDraw(void* p, bool flag);  // 0x0073b8e0 (SP::cModelInstance::SetDynamicDraw)
};
}
namespace SP {
struct DynDrawObj {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};
}
// ---- items of slice s0073afb0 end

// ---- items of slice s0073cdf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ArenaResource {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual void* v3(uint32_t id);
};
struct ArenaElem {                 // element stride 0x7c
    char pad74[0x74];
    int  field74;                  // +0x74
    char pad78[4];
};
struct ArenaHolder {               // value returned by ArenaResource::v3 for the mesh set
    char    pad108[0x108];
    ArenaElem* begin;              // +0x108
    ArenaElem* end;                // +0x10c
};
struct cModelInstance_GetArenaResource {
    char pad[0xc4];
    ArenaResource* mResource;   // +0xc4
    int GetArenaResource();
};
// ---- items of slice s0073cdf0 end

// ---- items of slice s0073e410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_01200940();          // 0x1200940
extern "C" void  FUN_00730210(int, int);  // 0x730210
extern "C" void  FUN_0072fff0(int, int);  // 0x72fff0
extern "C" void  __cdecl PushShaderDataNull();                         // 0x777bf0
extern "C" void  __cdecl ShaderSet(int slot, const void* data, int n); // 0x777ae0
extern "C" void  __cdecl ShaderEnd();                                  // 0x777c10
extern "C" int   __cdecl VertexDescriptor_AreEqual(const void*, const void*);   // 0x11f2e70
extern struct { char pad[0x3c]; struct { char pad[0x58]; int f58; }* f3c; }* g_AppProps;   // 0x15fd918
extern char  g_sh_62b870[];     // 0x162b870
extern char* g_sh_62e880;       // 0x162e880
extern int   g_sh_62e874;       // 0x162e874
extern char  g_sh_62e870[];     // 0x162e870
extern char  g_sh_5377cc[];     // 0x15377cc
extern char  g_sh_5379d8;       // 0x15379d8
extern int   g_primType;        // 0x16f85a8
extern const void* g_vertDesc;  // 0x16f65a0
extern unsigned g_softState;    // 0x16f9110
extern "C" void  __cdecl FUN_007c5490b();                      // rw_AllocSerialized @0x7c5490
extern "C" int   __cdecl FUN_01201660b(void* buf, int a, int b);          // @0x1201660
extern "C" void  __cdecl FUN_006c1c80b(void* buf, int v);                 // @0x6c1c80
extern "C" void  __stdcall ehvec_dtor(void* p, unsigned size, int cnt, void (__thiscall* d)(void*));  // 0x11e0b22
extern "C" void  __cdecl Elem8Dtor();                                      // 0xc2e4e0
struct Vec3A { float x, y, z, w; };
struct AABB  { Vec3A mn, mx; };
struct BBoxTest {
    AABB box;
    bool Test(const AABB* other);   // 0x73f110
};
struct RC {
    virtual void v0(int mode);
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};
struct RCItem {
    char pad0[0xc];
    RC*  mpObject;                   // +0xc
    char pad10[0xb4];
};
struct V3 { float x, y, z; };
struct __declspec(align(16)) V3A {
    float x, y, z, pad;
    V3A(const V3* p) { _mm_store_ps(&x, _mm_set_ps(p->x, p->z, p->y, p->x)); }
    void set(const V3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix33 {
    float m[9];
    Matrix33(const Matrix33& o);       // @0x41cb40 (thiscall, ret 4)
};
struct cSPTransform_s0073_e410 {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    float tx, ty, tz;                  // +0x04 mTranslation
    float mScale;                      // +0x10
    Matrix33 mRotation;                // +0x14
    cSPTransform_s0073_e410(const cSPTransform_s0073_e410& o)
        : mFlags(o.mFlags), mModificationCount(o.mModificationCount),
          tx(o.tx), ty(o.ty), tz(o.tz), mScale(o.mScale), mRotation(o.mRotation) {}
    cSPTransform_s0073_e410& operator=(const cSPTransform_s0073_e410& o);   // @0x537dc0
    void Invert();                                    // @0x40efa0
    void BackTransformPoint(void* p);                 // @0x4ff6d0 (thiscall, ret 4)
};
struct RCObj { void** vt; int mnRefCount; };       // refcount at +4, slot 0 = deleting dtor
struct PTBase {
    int mField0;                                   // +0x00
    union { int mField4; struct { char a, b; } mFlagBytes; };   // +0x04 (two bytes; copied as a dword)
    int mField8;                                   // +0x08
    RCObj* mpObject;                               // +0x0c (refcounted, refcount at +4)
    PTBase(int a1, RCObj* obj)
    {
        mField8 = a1;
        mField0 = 0;
        mFlagBytes.a = 0;
        mFlagBytes.b = 0;
        mpObject = obj;
        if (mpObject)
            mpObject->mnRefCount++;
    }
    PTBase(const PTBase& o)
    {
        mField0 = o.mField0;
        mField4 = o.mField4;
        mField8 = o.mField8;
        mpObject = o.mpObject;
        if (mpObject)
            mpObject->mnRefCount++;
    }
};
struct PartTransform : PTBase {
    cSPTransform_s0073_e410 mXf;                  // +0x10
    cSPTransform_s0073_e410 mXf2;                 // +0x48
    cSPTransform_s0073_e410 mInverse;             // +0x80
    int mTail0, mTail1, mTail2;        // +0xb8..+0xc0

    PartTransform(int a1, RCObj* obj, const cSPTransform_s0073_e410* t1, const cSPTransform_s0073_e410* t2);
    PartTransform(const PartTransform& o);
};
struct DynDrawElem { void* p0; void* p4; void** p8; };      // 12 bytes
struct ElemVec {
    DynDrawElem* begin;
    DynDrawElem* end;
    int size() const { return (int)(end - begin); }
};
struct DynDraw {
    char pad0[0xc];
    int f0c;                           // +0x0c
    char* f10;                         // +0x10 (stride-0x30 records)
    char pad14[0x3c];
    ElemVec mElems;                    // +0x50
};
struct Pair8 { unsigned a, b; };
struct CompiledState { void Dispatch(); };                  // rw::graphics::CompiledState::Dispatch @0x11ee580
struct ShaderDataObj {
    void Push();                                            // 0x7789d0 rw::graphics::ShaderDataState_Push
};
struct VertDesc {
    char pad0[0xc];
    unsigned short count;              // +0x0c
    char pad0e[2];
    unsigned flags;                    // +0x10
    char pad14[4];
    // +0x18: elements of 0xc bytes (kind at +4, id at +8)
    void FUN_11f2bc0();                // @0x11f2bc0
};
struct MeshCtx {                       // the object passed as arg 4 of DispatchMesh
    char pad0[0x44];
    ShaderDataObj* f44;                // +0x44
    char b48;                          // +0x48
    char pad49[3];
    int f4c;                           // +0x4c
    int refcount50;                    // +0x50
};
struct MeshDrawObj {                   // arg 1 of DispatchMesh
    char pad0[8];
    struct { char pad[0x14]; int primType; }* f08;   // +0x08
    char pad0c[0x18];
    VertDesc** f24;                   // +0x24
    void FUN_11f9710();                // @0x11f9710
};
extern "C" void  __cdecl SetShaderDataC(CompiledState*);               // 0x777b50 SP::SetShaderData
struct HullObj { void** vt; };
struct IfaceObj { void** vt; };
struct cModelInstance {
    char pad0[0x1c];
    Pair8* v1c_begin;                  // +0x1c
    Pair8* v1c_end;                    // +0x20
    char pad24[0xc];
    void** v30_begin;                  // +0x30  (elements: object with CompiledState* at +4)
    void** v30_end;                    // +0x34
    char pad38[0xc];
    RCObj** v44_begin;                 // +0x44
    RCObj** v44_end;                   // +0x48
    char pad4c[0x78];
    IfaceObj* mpIface;                 // +0xc4
    char padc8[4];
    void* mpResource;                  // +0xcc
    void* mpD0;                        // +0xd0
    char padd4[0x18];
    HullObj* mpHull;                   // +0xec
    DynDraw* mpDynDraw;                // +0xf0

    bool GetMeshes(void* a);                                   // @0x73eb90
    bool RayCast(const V3* p0, const V3* p1, cSPTransform_s0073_e410* xf, float* outT,
                 V3* outPos, V3* outNormal, int* outA, int* outB);   // @0x73e410
    void DispatchMesh(MeshDrawObj* obj, unsigned idx, int unused, MeshCtx* ctx);  // @0x73ede0
    void SetDrawTransform(const void* src, void* out);         // @0x73eca0
};
struct ElemRelease { void FUN_01200940(); };                    // @0x1200940 (thiscall)
struct HitRec {                        // stride 0xd0
    char pad0[0x10];
    V3 pos;                            // +0x10
    char pad1c[4];
    V3 dir;                            // +0x20
    char pad2c[0x14];
    float t;                           // +0x40
    char pad44[0x8c];
};
struct IdRec { char pad[0x58]; int id; char pad5c[4]; };   // stride 0x60
struct RayCache {
    char pad0[0x10];
    HitRec* hits;                      // +0x10
    int count;                         // +0x14
    char pad18[0xcc];
    IdRec* ids;                        // +0xe4
    int fE8;                           // +0xe8
    char padec[0x14];
    int f100;                          // +0x100
    void FUN_73a6e0(void* buf, int a, int b, const V3A* p0, const V3A* p1);   // @0x73a6e0
};
struct XfBuf { void* p; };
struct AllocObj { void** vt; };
struct ResObj { AllocObj* GetAllocator(); };                              // @0x7f54d0
struct IdLookup { int FUN_729ad0(int id); };                              // @0x729ad0
extern RayCache* g_rayCache;                                              // 0x162eaf0
extern "C" RayCache* __cdecl FUN_012016d0b(void* buf, int a, int b);      // @0x12016d0
struct __declspec(align(16)) Mat4L { float r0[4], r1[4], r2[4], t[4]; };
static const float kFltMax = 3.4028234663852886e+38f;
// ---- items of slice s0073e410 end

// ---- items of slice s0073f320 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl EASTL_allocator_deallocate(void* p);   // 0xf47380
void __cdecl operator_delete__(void* p) throw();    // 0xf47380 (same function, nothrow view)
struct RC_s0073_f320 {
    virtual void v0(int mode);
    virtual void v1();
    int mnRefCount;                  // +0x4
};
inline void RcAddRef(RC_s0073_f320* p) { _InterlockedIncrement((volatile long*)&p->mnRefCount); }
inline void RcRelease(RC_s0073_f320* p) {
    long r = _InterlockedDecrement((volatile long*)&p->mnRefCount);
    if (r == 0) { _InterlockedExchange((volatile long*)&p->mnRefCount, 1); p->v0(1); }
}
struct RefPair {
    int value;                       // +0x0
    RC_s0073_f320* p;                           // +0x4
};
struct DynArray {
    void* first;                     // +0x0
};
struct ArrayHolder {
    char pad[0xd0];
    DynArray* mArray;                // +0xd0
    void SetArray(DynArray* p);
};
struct cSPTransformS {
    uint16_t mFlags;
    uint16_t mModificationCount;
    float    mTranslation[3];
    float    mScale;
    float    mRotation[9];           // +0x14
    cSPTransformS& operator=(const cSPTransformS& o);   // 0x537dc0
};
struct cSkinBinding {
    int f0, f4, f8;
    RC_s0073_f320* p0c;                         // +0xc
    cSPTransformS t10;               // +0x10
    cSPTransformS t48;               // +0x48
    cSPTransformS t80;               // +0x80
    int b8, bc, c0;
    cSkinBinding& operator=(const cSkinBinding& o);
};
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
// ---- items of slice s0073f320 end

// ---- items of slice s007403c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec12 { int a, b, c; };
struct Vec12Vector {
    Vec12* mpBegin;                  // +0x0
    Vec12* mpEnd;                    // +0x4
    Vec12* mpCapacity;               // +0x8
    void push_back(const Vec12& value);
    void DoInsertValue(Vec12* pos, const Vec12& value);   // 0x7409d0
};
// ---- items of slice s007403c0 end

// ---- items of slice s00741210 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResBase {
    virtual void v0();
    virtual void v1();
};
struct cMI_Construct {
    char    pad0[8];
    void*   mBegin8;                  // +0x8
    void*   mEndc;                    // +0xc
    char    pad10[0xc4 - 0x10];
    ResBase* mResource;               // +0xc4

    void AddGeometryFromArena(ResBase* p);          // 0x741210
    bool ConstructFromArenaResource(ResBase* p);    // 0x741a40
    void Sub3c0(ResBase* p);                        // 0x7403c0
};
struct RefCounted {
    virtual void v0();
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};
struct RefPair8 {
    int         value;               // +0x0
    RefCounted* p;                   // +0x4
};
struct Vec8 {
    RefPair8* mpBegin;               // +0x0
    RefPair8* mpEnd;                 // +0x4
    RefPair8* mpCapacity;            // +0x8
    RefPair8* insert(RefPair8* pos, const RefPair8* v);
    void DoInsertValue(RefPair8* pos, const RefPair8* v);   // 0x7418f0
};
// ---- items of slice s00741210 end

// @ 0x0073b7e0
namespace SP {
int cModelInstance_s0073_afb0::GetNumBones()
{
    if (mGroupBegin == mGroupEnd)
        return 0;
    return (int)mGroupEnd[-1].mBoneCount + (int)mGroupEnd[-1].mBoneOffset;
}
}  // namespace SP








// @ 0x0073b800
namespace SP {
void cModelInstance_s0073_afb0::SetBoneTable(int a, void* b)
{
    cAnimGroupInfo_s0073_afb0* p = mGroupBegin;
    if (p != mGroupEnd && (int)p->mBoneCount < a)
        mFieldC = (int)p->mBoneCount;
    else
        mFieldC = a;
    mField10 = b;
    mCounter += 1;
}
}  // namespace SP








// @ 0x0073b840
namespace SP {
void cModelInstance_s0073_afb0::SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4)
{
    if (boneIndex == -1) {
        if (mGroupBegin == mGroupEnd)
            return;
        cAnimGroupInfo_s0073_afb0* p = mGroupBegin;
        do {
            char idx = p->mBindingIdx;
            if (idx >= 0) {
                cMaterial_s0073_afb0* m = &mMaterials[idx];
                m->f_b8 = a3;
                m->f_c0 = a4;
                m->f_bc = a2;
            }
            p = (cAnimGroupInfo_s0073_afb0*)((char*)p + 8);
        } while (p != mGroupEnd);
        return;
    }
    if (boneIndex < 0)
        return;
    if (boneIndex >= (int)(mGroupEnd - mGroupBegin))
        return;
    char idx = mGroupBegin[boneIndex].mBindingIdx;
    if (idx < 0)
        return;
    cMaterial_s0073_afb0* m = &mMaterials[idx];
    m->f_b8 = a3;
    m->f_c0 = a4;
    m->f_bc = a2;
}
}  // namespace SP








// @ 0x0073b8e0
namespace SP {
void cModelInstance_s0073_afb0::SetDynamicDraw(void* pv, bool flag)
{
    DynDrawObj* p = (DynDrawObj*)pv;
    mFlags = mFlags & 0xfffb;
    if (p != 0) {
        if (flag)
            mFlags |= 4;
        DynDrawObj* dd = (DynDrawObj*)((void*(__thiscall*)(DynDrawObj*))p->vftable[2])(p);
        DynDrawObj* old = (DynDrawObj*)mDynDraw;
        if (dd != old) {
            if (dd != 0)
                ((void(__thiscall*)(DynDrawObj*))dd->vftable[0])(dd);
            mDynDraw = dd;
            if (old != 0)
                ((void(__thiscall*)(DynDrawObj*))old->vftable[1])(old);
        }
        ((void(__thiscall*)(DynDrawObj*, void*))((DynDrawObj*)mDynDraw)->vftable[4])((DynDrawObj*)mDynDraw, &mField30);
        return;
    }
    DynDrawObj* old = (DynDrawObj*)mDynDraw;
    if (old != 0) {
        mDynDraw = 0;
        ((void(__thiscall*)(DynDrawObj*))old->vftable[1])(old);
    }
}
}  // namespace SP







// @ 0x0073d160
int cModelInstance_GetArenaResource::GetArenaResource()
{
    int result = 0;
    ArenaResource* p = mResource;
    if (p) {
        result = (int)p->v3(0x2f4e681b);
        if (result)
            return result;
    }
    p = mResource;
    if (p) {
        ArenaHolder* h = (ArenaHolder*)p->v3(0xe6bce5);
        if (h) {
            if (h->end - h->begin == 1)
                return h->begin->field74;
        }
    }
    return result;
}






// @ 0x0073e410
bool cModelInstance::RayCast(const V3* p0, const V3* p1, cSPTransform_s0073_e410* xf, float* outT, V3* outPos, V3* outNormal, int* outA, int* outB)
{
    if (!mpResource)
        return false;
    V3A a0(p0);
    V3A a1(p1);
    float scale = xf->mScale;
    Mat4L mat;
    bool needXform;
    if (scale == 1.0f) {
        mat.t[0] = xf->tx; mat.t[1] = xf->ty; mat.t[2] = xf->tz;
        mat.r0[0] = xf->mRotation.m[0] * scale; mat.r0[1] = xf->mRotation.m[1] * scale; mat.r0[2] = xf->mRotation.m[2] * scale;
        mat.r1[0] = xf->mRotation.m[3] * scale; mat.r1[1] = xf->mRotation.m[4] * scale; mat.r1[2] = xf->mRotation.m[5] * scale;
        mat.r2[0] = xf->mRotation.m[6] * scale; mat.r2[1] = xf->mRotation.m[7] * scale; mat.r2[2] = xf->mRotation.m[8] * scale;
        needXform = false;
    } else {
        needXform = true;
        xf->BackTransformPoint(&a0);
        xf->BackTransformPoint(&a1);
        mat.t[0] = 0; mat.t[1] = 0; mat.t[2] = 0; mat.t[3] = 0;
        mat.r2[0] = 0; mat.r2[1] = 0; mat.r2[2] = 1.0f; mat.r2[3] = 0;
        mat.r0[0] = 1.0f; mat.r0[1] = 0; mat.r0[2] = 0; mat.r0[3] = 0;
        mat.r1[0] = 0; mat.r1[1] = 1.0f; mat.r1[2] = 0; mat.r1[3] = 0;
    }
    needXform = scale != 1.0f;
    if (g_rayCache == 0) {
        char arr[32];
        char tmp[16];
        int r = FUN_01201660b(arr, 4, 4);
        FUN_006c1c80b(tmp, r);
        ehvec_dtor(arr, 8, 4, (void (__thiscall*)(void*))Elem8Dtor);
        g_rayCache = FUN_012016d0b(tmp, 4, 4);
    }
    RayCache* cache = g_rayCache;
    char buf[100];
    XfBuf xb;
    xb.p = buf;
    cache->FUN_73a6e0(&xb, 0, 1, &a0, &a1);
    cache->f100 = 2;
    float best = kFltMax;
    int bestId = -1;
    bool again;
    do {
        cache->count = 0;
        cache->fE8 = 0;
        AllocObj* al = ((ResObj*)mpResource)->GetAllocator();
        void** iface = *(void***)((char*)al + 0x20);
        int r = ((int (__thiscall*)(void*, RayCache*, Mat4L*))iface[0x14 / 4])(al, cache, &mat);
        cache = g_rayCache;
        again = (r == 0);
        for (int i = 0; i < cache->count; ++i) {
            HitRec* h = &cache->hits[i];
            if (best > h->t) {
                a1.set(h->pos);
                best = h->t;
                a0.set(h->dir);
                bestId = cache->ids[i].id;
            }
        }
    } while (cache->count != 0 && again);
    if (!(best < kFltMax))
        return false;
    if (outT)
        *outT = best;
    if (outPos) {
        outPos->x = a1.x; outPos->y = a1.y; outPos->z = a1.z;
        if (needXform) {
            if (xf->mFlags & 2) {
                float y = outPos->y, z = outPos->z, x = outPos->x;
                const float* r = xf->mRotation.m;
                outPos->x = (r[3] * y + r[6] * z) + x * r[0];
                outPos->y = (r[1] * x + r[4] * y) + r[7] * z;
                outPos->z = (r[2] * x + r[5] * y) + r[8] * z;
            }
            float s = xf->mScale;
            float z = outPos->z, x = outPos->x, y = outPos->y;
            outPos->y = s * y;
            outPos->z = z * s;
            outPos->x = x * s;
            outPos->x = x * s + xf->tx;
            outPos->y = xf->ty + s * y;
            outPos->z = xf->tz + z * s;
        }
    }
    if (outNormal) {
        outNormal->x = a0.x; outNormal->y = a0.y; outNormal->z = a0.z;
        if (needXform && (xf->mFlags & 2)) {
            float y = outNormal->y, z = outNormal->z, x = outNormal->x;
            const float* r = xf->mRotation.m;
            outNormal->x = (r[3] * y + r[6] * z) + r[0] * x;
            outNormal->y = (r[1] * x + r[4] * y) + r[7] * z;
            outNormal->z = (r[2] * x + r[5] * y) + r[8] * z;
        }
    }
    if (outA || outB) {
        int v;
        if (mpD0) {
            v = ((IdLookup*)mpD0)->FUN_729ad0(bestId);
        } else {
            v = -1;
            bestId = -1;
        }
        if (outA) *outA = v;
        if (outB) *outB = bestId;
    }
    return true;
}






// @ 0x0073eb90
bool cModelInstance::GetMeshes(void* a)
{
    if (mpHull) {
        int n = mpDynDraw->mElems.size();
        for (int i = 0; i < n; ++i) {
            DynDrawElem* e = &mpDynDraw->mElems.begin[i];
            if (e->p8) {
                if (e->p0) {
                    void** vt2 = *(void***)((char*)e->p0 + 4);
                    ((void (__thiscall*)(void*))vt2[3])(e->p0);
                    *e->p8 = e->p0;
                    ((ElemRelease*)e->p8)->FUN_01200940();
                } else {
                    FUN_007c5490b();
                }
            }
        }
        if (((bool (__thiscall*)(void*, void*))mpHull->vt[0x18 / 4])(mpHull, a))
            return true;
    }
    IfaceObj* i1 = mpIface;
    if (i1) {
        int r = ((int (__thiscall*)(void*, unsigned))i1->vt[0xc / 4])(i1, 0xe6bce5);
        if (r) {
            FUN_00730210(r, (int)a);
            return true;
        }
    }
    IfaceObj* i2 = mpIface;
    if (i2) {
        int r = ((int (__thiscall*)(void*, unsigned))i2->vt[0xc / 4])(i2, 0x2f4e681b);
        if (r) {
            FUN_0072fff0(r, (int)a);
            return true;
        }
    }
    return false;
}






// @ 0x0073ede0
void cModelInstance::DispatchMesh(MeshDrawObj* obj, unsigned idx, int, MeshCtx* ctx)
{
    ctx->refcount50++;
    PushShaderDataNull();
    CompiledState* cs = 0;
    if (idx < (unsigned)(v30_end - v30_begin) && v30_begin[idx])
        cs = *(CompiledState**)((char*)v30_begin[idx] + 4);
    ShaderDataObj* sd = 0;
    if (idx < (unsigned)(v44_end - v44_begin))
        sd = (ShaderDataObj*)v44_begin[idx];
    if (cs) {
        SetShaderDataC(cs);
        cs->Dispatch();
    }
    VertDesc* vd = *obj->f24;
    if (((vd->flags >> 14) & 1) && !ctx->b48 && g_AppProps->f3c->f58 == 0) {
        if (ctx->f4c) {
            if (mpDynDraw->f0c == ctx->f4c)
                g_sh_62e880 = mpDynDraw->f10;
            else
                g_sh_62e880 = g_sh_62b870;
            if (v1c_begin == v1c_end) {
                g_sh_62e874 = ctx->f4c;
            } else {
                g_sh_62e880 = g_sh_62e880 + v1c_begin[idx].a * 0x30;
                g_sh_62e874 = v1c_begin[idx].b;
            }
            ShaderSet(4, g_sh_62e870, 1);
            ShaderSet(3, g_sh_5377cc, 0);
        }
    } else {
        ShaderSet(3, 0, 0);
        ShaderSet(4, 0, 0);
    }
    if (vd->flags & 4) {
        unsigned n = vd->count;
        unsigned i = 0;
        if (n) {
            char* e = (char*)vd + 0x18;
            do {
                if (*(int*)(e + 8) == 2) {
                    if (e[4] == 5 && g_sh_5379d8)
                        ShaderSet(0x22c, &g_sh_5379d8, 0);
                    break;
                }
                ++i;
                e += 0xc;
            } while (i < n);
        }
    }
    g_primType = obj->f08->primType;
    if (g_vertDesc == 0 || !VertexDescriptor_AreEqual(g_vertDesc, vd))
        g_softState |= 0x100000;
    g_vertDesc = vd;
    vd->FUN_11f2bc0();
    if (sd) sd->Push();
    if (ctx->f44) ctx->f44->Push();
    obj->FUN_11f9710();
    ShaderEnd();
}






// @ 0x0073f000
PartTransform::PartTransform(int a1, RCObj* obj, const cSPTransform_s0073_e410* t1, const cSPTransform_s0073_e410* t2)
: PTBase(a1, obj), mXf(*t1), mXf2(*t2), mInverse(*t2)
{
    mTail0 = 0;
    mTail1 = 0;
    mTail2 = 0;
    mInverse = mXf;
    mInverse.Invert();
}






// @ 0x0073f110
bool BBoxTest::Test(const AABB* other)
{
    if (box.mn.x <= other->mx.x)
        if (other->mn.x <= box.mx.x)
            if (box.mn.y <= other->mx.y)
                if (other->mn.y <= box.mx.y)
                    if (box.mn.z <= other->mx.z)
                        if (other->mn.z <= box.mx.z)
                            return true;
    return false;
}






// @ 0x0073f1c0
PartTransform::PartTransform(const PartTransform& o)
: PTBase(o), mXf(o.mXf), mXf2(o.mXf2), mInverse(o.mInverse)
{
    mTail0 = o.mTail0;
    mTail1 = o.mTail1;
    mTail2 = o.mTail2;
}






// @ 0x0073f2e0
void __stdcall ReleaseRange(RCItem* first, RCItem* last)
{
    for (; first < last; ++first) {
        RC* p = first->mpObject;
        if (p) {
            int n = (p->mnRefCount += -1);
            if (n == 0) {
                p->mnRefCount = 1;
                _ReadWriteBarrier();
                p->v0(1);
            }
        }
    }
}





// @ 0x0073f320
cSkinBinding& cSkinBinding::operator=(const cSkinBinding& o)
{
    f0 = o.f0;
    f4 = o.f4;
    f8 = o.f8;
    if (o.p0c != p0c) {
        RC_s0073_f320* p = o.p0c;
        RC_s0073_f320* old = p0c;
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




// @ 0x0073f440
RefPair* __cdecl copy_backward_ref(RefPair* first, RefPair* last, RefPair* result)
{
    while (last != first) {
        --last; --result;
        result->value = last->value;
        RC_s0073_f320* p = last->p;
        RC_s0073_f320* old = result->p;
        if (p != old) {
            if (p) RcAddRef(p);
            result->p = p;
            if (old) RcRelease(old);
        }
    }
    return result;
}




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




// @ 0x007402e0
BindingContainer::~BindingContainer()
{}




// @ 0x00740370
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



// @ 0x007411b0
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


// @ 0x00741a40
bool cMI_Construct::ConstructFromArenaResource(ResBase* p)
{
    ResBase* old = mResource;
    if (p != old) {
        if (p)
            p->v0();
        mResource = p;
        if (old)
            old->v1();
    }
    AddGeometryFromArena(p);
    if (mBegin8 == mEndc)
        return false;
    Sub3c0(p);
    return true;
}

// @ 0x00741aa0
RefPair8* Vec8::insert(RefPair8* pos, const RefPair8* v)
{
    RefPair8* p = mpEnd;
    int idx = (int)(pos - mpBegin);
    if (pos == p && p != mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->value = v->value;
            RefCounted* r = v->p;
            p->p = r;
            if (r) {
                _InterlockedIncrement((volatile long*)&r->mnRefCount);
            }
        }
    } else {
        DoInsertValue(pos, v);
    }
    return mpBegin + idx;
}
