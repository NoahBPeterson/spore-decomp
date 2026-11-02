// src/game/SPBake/SPEditorHandleDeform.cpp -- migrated from slice(s) s00481f00, s00480320, s0047f520 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorHandleDeform.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "SP/cMWModel.h"
#include "SP/cModelDeformationHandle.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorHandleDeform.h"
#include "SP/cSPEditorTrianglePinningInfo.h"
#include "cSPTransform.h"

// unnamed retail callees and globals (address in the comment)
extern void* EditorTuning();                       // 0x00401070 tuning struct, Vec3 members at +0x6c.. +0x90
extern void  __fastcall Transform_Ctor(void* t);              // 0x409930 (ecx = &mTransform)
extern void  __fastcall TrianglePinningInfo_Ctor(void* p);    // FUN_004e8f70 (ecx = this)
extern void  __fastcall TrianglePinningInfo_Dtor(void* p);    // FUN_004ae250 (ecx = this)
extern const float kDeformVec0;  // 0x15d4fd8
extern const float kDeformVec1;  // 0x15d4fdc
extern const float kDeformVec2;  // 0x15d4fe0
extern const float kPreviewDelta;                          // 0x1471064 (0.5f)
extern char gEmptyString[];                                // 0x1667bac

// ---- items of slice s0047f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  operator_delete_array(void* p);        // 0x00f47380, cdecl 1 arg
extern void __fastcall cSPEditorHandle_Shutdown(void* self);   // 0x47e2c0 SP::cSPEditorHandle::Shutdown
extern void __fastcall cSPEditorHandle_BaseDtor(void* self);   // 0x47d870 ~cSPEditorHandle
extern void __fastcall cSPEditorHandle_BaseCtor(void* self);   // 0x47d6a0 ctor
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int16_t  i16;
struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; Mat3* Assign(const void* src); };   // Assign 0x41cb40
struct cMWModel {
    char pad0[8];
    u16 mFlags;      // +8
    i16 mCount;      // +10
    Vec3 mPos;       // +0xc
    char pad18[4];   // +0x18
    Mat3 mBasis;     // +0x1c
    char pad40[4];   // +0x40
    u32 mGroups[2];  // +0x44
};
struct cSPModelManager {
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
    virtual u32 GetGroupID(u32 name, int flag);   // slot 0x28
};
struct cSPTransformOps {
    u32 raw[0x38 / 4];
    cSPTransformOps* Assign(const void* src);   // 0x537dc0
    void Apply(Vec3* v);                        // 0x44d4f0
};
struct cSPEditorBlock;
struct cModelDeformationHandle;
struct IRefCounted { virtual void q0(); virtual void Release(); };
struct cSPEditorTrianglePinningInfo {
    u32 mField0;             // +0
    void* mpRef4;            // +4 (IRefCounted)
    void Update();           // 0x4ae250
};
struct cSPEditorHandle {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void PlaceHandle();                    // slot 5 (+0x14)
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void GetHandlePosition(Vec3* out);     // slot 9 (+0x24)
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
    void* mRefCountVft;                    // +4
    char pad8[8];
    cSPEditorBlock* mBlock;                // +0x10
    cMWModel* mModel;                      // +0x14
    cMWModel* mOverdrawModel;              // +0x18
    char pad1c[0x34];

    int Init(cSPEditorBlock* block, bool b, u32 a, u32 c);   // 0x47db30 (returns self)
};
struct cSPEditorBlock {
    char pad0[0x10];
    void* mp10;                            // +0x10
    char pad14[4];
    void* mp18;                            // +0x18
    void GetTransform(cSPTransformOps* out);   // 0x4362a0
};
struct cModelDeformationHandle {
    u32 mField0;                 // +0
    cSPTransformOps mTransform;  // +4
    u32 mField3c;                // +0x3c
    Vec3 mVec40;                 // +0x40
    Vec3 mVec4c;                 // +0x4c
    float mFloat58;              // +0x58
    cModelDeformationHandle* Copy(const cModelDeformationHandle* src);  // 0x47fda0
};
struct cSPEditorHandleDeform : cSPEditorHandle {
    cModelDeformationHandle mData;             // +0x50 (0x5c bytes)
    u32  mPinningType;                         // +0xac
    u32  mAxisToIgnore;                        // +0xb0
    cSPEditorHandleDeform* mSymmetricHandle;   // +0xb4
    char padb8[0x118 - 0xb8];
    u8   mSetPickData;                         // +0x118
    char pad119[3];
    char* mpSoundBegin;                        // +0x11c
    char* mpSoundEnd;                          // +0x120
    char* mpSoundCap;                          // +0x124
    char pad128[4];                            // +0x128
    Vec3 mVec12c;                              // +0x12c
    Vec3 mVec138;                              // +0x138
    Vec3 mVec144;                              // +0x144
    char pad150[0x184 - 0x150];
    float mPreviewDelta;                       // +0x184
    cSPEditorTrianglePinningInfo mTriangleInfo; // +0x188
    char pad190[0x1d4 - 0x190];
    u8 mIsHiddenHandle;                        // +0x1d4
    u8 mDoNotPlaceHandle;                      // +0x1d5

    void SetFade(float f);                                        // 0x4809a0
    void SetData(const cModelDeformationHandle* data, bool flag); // 0x47fd30
    void UpdateDirection(bool flag);                              // 0x47fe20
    void Init(cSPModelManager* mgr, cSPEditorBlock* block,
              const cModelDeformationHandle* data, bool flag);    // 0x480030
};
extern void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle* self);   // 0x47fcb0
struct DeformIface { void* QueryInterface(u32 id); };
extern float Vec3_Dot(Vec3* a, void* b);                                  // FUN_00455cc0
// ---- items of slice s0047f520 end

// ---- items of slice s00480320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s0048_0320 {
    float x, y, z;
    Vec3_s0048_0320() {}
    Vec3_s0048_0320(const Vec3_s0048_0320& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3_s0048_0320& operator=(const Vec3_s0048_0320& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vec3POD { float x, y, z; };
struct Mat33 { float m[9]; };
Vec3_s0048_0320 operator-(const Vec3_s0048_0320& a, const Vec3_s0048_0320& b);               // @ 0x0041db10
Vec3_s0048_0320 operator*(const Vec3_s0048_0320& a, const float& s);              // @ 0x0041dca0
struct XformBlock {
    unsigned short flags;       // +0
    unsigned short count;       // +2
    Vec3POD pos;                // +4
    char padc[4];
    Mat33 basis;                // +0x14
    void SetPos(const Vec3POD& v) { pos = v; flags |= 4; count++; }
    void SetBasis(const Mat33& m) { basis = m; flags |= 2; count++; }
};
struct HandleObj {
    char pad0[8];
    XformBlock xf;              // +8
    int mRefCount;              // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
};
struct ObjRef {
    HandleObj* mp;
    ObjRef(const ObjRef& o) : mp(o.mp) { if (mp) mp->AddRef(); }
    HandleObj* operator->() const { return mp; }
    operator HandleObj*() const { return mp; }
};
struct MsgMgr {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void Submit(ObjRef obj, int id, float a, float b, int c);   // vtable +0x18, ret 0x14
};
MsgMgr* GetMsgMgr();                                         // @ 0x00401060
struct RingHandle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual float Param38(int a);                           // +0x38
    virtual float Param3c(int a);                           // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual void PointAt(Vec3_s0048_0320* out, float t);               // +0x4c
    char pad04[0x10];
    ObjRef m14;                                             // +0x14
    ObjRef m18;                                             // +0x18
    char pad1c[0xc];
    float mScale;                                           // +0x28

    void GetOrientation(Mat33* out);                        // @ 0x004822d0
    void Update();                                          // @ 0x00480320
};
// ---- items of slice s00480320 end

// ---- items of slice s00481f00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
Vector3* VSub(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041db10
Vector3* VNorm(Vector3* out, const Vector3* a);                    // @ 0x00436ce0
Vector3* VMul(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041daf0
void     TransformPoint(void* xform, Vector3* p);                  // @ 0x0044d4f0 (ecx=xform)
Vector3* Interp(Vector3* out, const Vector3* a, const Vector3* b, float t); // @ 0x00413cc0
struct Mat3_s0048_1f00 { float m[9]; };
struct cSPTransform_s0048_1f00 {
    uint16_t mFlags;               // +0x00
    uint16_t mModificationCount;   // +0x02
    Vector3  mTranslation;         // +0x04
    float    mScale;               // +0x10
    Mat3_s0048_1f00     mRotation;            // +0x14
    cSPTransform_s0048_1f00(const cSPTransform_s0048_1f00& src);     // 0x0040ce80 (copy ctor)
    void Invert();                             // 0x0040efa0
    void TransformPoint(Vector3& p);           // 0x0044d4f0
    // cSPTransform::SetTranslation / SetRotation (inline in the original)
    void SetTranslation(const Vector3& v)
    { mTranslation = v; mFlags |= 0x4; mModificationCount++; }   // kHasTranslation
    void SetRotation(const Mat3_s0048_1f00& r)
    { mRotation = r; mFlags |= 0x2; mModificationCount++; }      // kHasRotation
};
struct cMWModel_s0048_1f00 {
    char pad0[0x08];
    cSPTransform_s0048_1f00 mTransform;      // +0x08
};
struct cSPEditorBlock_s0048_1f00 {
    char pad0[0x10];
    cMWModel_s0048_1f00* mModel;              // +0x10
};
#define RH_VIRT(n) virtual void vpad##n();
struct RotHandle {
    RH_VIRT(0) RH_VIRT(1) RH_VIRT(2) RH_VIRT(3) RH_VIRT(4) RH_VIRT(5) RH_VIRT(6)
    RH_VIRT(7) RH_VIRT(8) RH_VIRT(9) RH_VIRT(10) RH_VIRT(11) RH_VIRT(12)
    RH_VIRT(13) RH_VIRT(14) RH_VIRT(15) RH_VIRT(16) RH_VIRT(17) RH_VIRT(18)
    virtual Vector3* GetHandlePos(Vector3* out, float t);   // slot 19 (vptr+0x4c)

    uint32_t pad04[3];             // +0x04 (RefCountVTemplate vptr/refcount)
    cSPEditorBlock_s0048_1f00* mBlock;        // +0x10
    cMWModel_s0048_1f00* mModel;              // +0x14 (AutoRefCount<cMWModel>)
    cMWModel_s0048_1f00* mOverdrawModel;      // +0x18 (AutoRefCount<cMWModel>)
    char pad1c[0x74];              // +0x1c .. +0x8f
    Vector3 mP0;                   // +0x90
    Vector3 mP1;                   // +0x9c
    char padA8[0xc0];              // +0xa8 .. +0x167
    Vector3 mTriangleRelativeDirection;  // +0x168
    Vector3 mBasePositionOffset;         // +0x174
    float  mRadius;                // +0x180
    char pad184[0x51];             // +0x184 .. +0x1d4
    uint8_t mDoNotPlaceHandle;     // +0x1d5

    Vector3* GetDir(Vector3* out, bool useParent);
    Vector3* GetP0(Vector3* out, bool transform);
    Vector3* GetP1(Vector3* out, bool transform);
    void*    GetOrientation(void* out);
    void     Update();
};
struct EntityXform {
    char pad[8];
    void TransformPoint(Vector3* p);   // uses 0x44d4f0 on this+8
};
struct MatOut {
    void Assign(const Mat3_s0048_1f00* src);   // @ 0x0041cb40
};
// ---- items of slice s00481f00 end

// @ 0x0047fa30
void* __fastcall cSPEditorHandleDeform_Ctor(cSPEditorHandle* self)
{
    cSPEditorHandle_BaseCtor(self);
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    Transform_Ctor((char*)self + 0x54);
    cSPEditorHandleDeform* d = (cSPEditorHandleDeform*)self;
    d->mPinningType = 0x95f07f3d;
    d->mAxisToIgnore = 0;
    d->mSymmetricHandle = 0;
    d->mSetPickData = 0;
    d->mpSoundBegin = 0;
    d->mpSoundEnd = 0;
    d->mpSoundCap = 0;
    d->mpSoundBegin = gEmptyString;
    d->mpSoundEnd = d->mpSoundBegin;
    d->mpSoundCap = d->mpSoundBegin + 1;
    for (int off = 0; off < 3; off++) {
        Vec3* v = (Vec3*)((char*)d + 0x12c + off * 0xc);
        v->x = kDeformVec0;
        v->y = kDeformVec1;
        v->z = kDeformVec2;
    }
    d->mPreviewDelta = kPreviewDelta;
    TrianglePinningInfo_Ctor((char*)self + 0x188);
    d->mDoNotPlaceHandle = 0;
    return self;
}

// @ 0x0047fc10
void __fastcall cSPEditorHandleDeform_Dtor(cSPEditorHandle* self)
{
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    cSPEditorHandleDeform* d = (cSPEditorHandleDeform*)self;
    cSPEditorHandleDeform_Shutdown(self);
    void* held = d->mTriangleInfo.mpRef4;
    if (held)
        ((IRefCounted*)held)->Release();
    if (d->mpSoundCap - d->mpSoundBegin > 1) {
        if (d->mpSoundBegin)
            operator_delete_array(d->mpSoundBegin);
    }
    cSPEditorHandle_BaseDtor(self);
}

// @ 0x0047fcb0
void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle* self)
{
    cSPEditorHandle_Shutdown(self);
    ((cSPEditorHandleDeform*)self)->mSymmetricHandle = 0;
    ((cSPEditorHandleDeform*)self)->mTriangleInfo.Update();
}

// @ 0x0047fce0
void* DeformIface::QueryInterface(u32 id)
{
    switch (id) {
    case 0xee3f516e: return this;
    case 0x050a1fe5: return this;
    case 0x050a993c: return this;
    }
    return 0;
}

// @ 0x0047fda0
cModelDeformationHandle* cModelDeformationHandle::Copy(const cModelDeformationHandle* src)
{
    mField0 = src->mField0;
    mTransform.Assign(&src->mTransform);
    mField3c = src->mField3c;
    mVec40 = src->mVec40;
    mVec4c = src->mVec4c;
    mFloat58 = src->mFloat58;
    return this;
}

// @ 0x0047ff90
Vec3* Mat3_TransformDir_(Vec3* out, char* mat, void* v)
{
    float a = Vec3_Dot((Vec3*)v, mat);
    float b = Vec3_Dot((Vec3*)v, mat + 0xc);
    float c = Vec3_Dot((Vec3*)v, mat + 0x18);
    out->x = a; out->y = b; out->z = c;
    return out;
}

// @ 0x00480280
Vec3* __fastcall Deform_GetTuningVec(char* self, int /*edx*/, Vec3* out)
{
    char* t = (char*)EditorTuning();
    u32 k = *(u32*)(self + 0x8c);
    if (k == 0x503283aa)      *out = *(Vec3*)(t + 0x78);
    else if (k == 0xe20e2032) *out = *(Vec3*)(t + 0x84);
    else                      *out = *(Vec3*)(t + 0x6c);
    return out;
}

// @ 0x00480320
void RingHandle::Update()
{
    // slot order only (n31 = mgr, begin = along, p4 = basis, where = endpoint, p18 = side, mid = p0, p30 = p1)
    MsgMgr* n31 = GetMsgMgr();
    Vec3_s0048_0320 mid, p30, begin, where, p18;
    Mat33 p4;
    PointAt(&mid, 0.0f);
    PointAt(&p30, 1.0f);
    begin = p30 - mid;
    GetOrientation(&p4);
    PointAt(&p18, -1.0f);
    where = mid - begin * 0.1f;
    if (m14) {
        m14->xf.SetPos(*(Vec3POD*)&where);
        m14->xf.SetBasis(p4);
        n31->Submit(m14, 5, p18.x, mScale, 3);
        n31->Submit(m14, 6, p18.y, mScale, 3);
        n31->Submit(m14, 7, p18.z, mScale, 3);
        n31->Submit(m14, 4, Param38(3), mScale, 1);
    }
    if (m18) {
        m18->xf.SetPos(*(Vec3POD*)&where);
        m18->xf.SetBasis(p4);
        n31->Submit(m18, 5, p18.x, mScale, 3);
        n31->Submit(m18, 6, p18.y, mScale, 3);
        n31->Submit(m18, 7, p18.z, mScale, 3);
        n31->Submit(m18, 4, Param3c(3), mScale, 1);
    }
}

// @ 0x00481fa0
Vector3* RotHandle::GetHandlePos(Vector3* out, float t)
{
    if (t == -1.0f)
        t = this->mRadius;
    Vector3 local;
    Interp(&local, &this->mP0, &this->mP1, t);
    ((EntityXform*)(*(char**)((char*)this->mBlock + 0x10) + 8))->TransformPoint(&local);
    out->x = local.x;
    out->y = local.y;
    out->z = local.z;
    return out;
}

// @ 0x00482040
Vector3* RotHandle::GetDir(Vector3* out, bool useParent)
{
    Vector3 d;
    VSub(&d, &this->mP1, &this->mP0);
    Vector3 n;
    VNorm(&n, &d);
    if (useParent) {
        Vector3 t;
        VMul(&t, &n, (const Vector3*)(*(char**)((char*)this->mBlock + 0x10) + 0x1c));
        n = t;
    }
    out->x = n.x;
    out->y = n.y;
    out->z = n.z;
    return out;
}

// @ 0x00482130
Vector3* RotHandle::GetP0(Vector3* out, bool transform)
{
    Vector3 v = this->mP1;
    if (transform) {
        ((EntityXform*)(*(char**)((char*)this->mBlock + 0x10) + 8))->TransformPoint(&v);
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
    } else {
        out->x = this->mP1.x;
        out->y = this->mP1.y;
        out->z = this->mP1.z;
    }
    return out;
}

// @ 0x00482200
Vector3* RotHandle::GetP1(Vector3* out, bool transform)
{
    Vector3 v = this->mP0;
    if (transform) {
        ((EntityXform*)(*(char**)((char*)this->mBlock + 0x10) + 8))->TransformPoint(&v);
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
    } else {
        out->x = this->mP0.x;
        out->y = this->mP0.y;
        out->z = this->mP0.z;
    }
    return out;
}

// @ 0x004822d0
void* RotHandle::GetOrientation(void* out)
{
    Vector3 d, t;
    Mat3_s0048_1f00 basis;
    VSub(&d, &this->mP1, &this->mP0);
    VMul(&t, &d, (const Vector3*)(*(char**)((char*)this->mBlock + 0x10) + 0x1c));
    void BuildMatrix(Mat3_s0048_1f00*, const Vector3*, void*);   // @ 0x004a89e0
    BuildMatrix(&basis, &t, (void*)0x15d4e28);
    ((MatOut*)out)->Assign(&basis);
    return out;
}

// @ 0x004823b0
void RotHandle::Update()
{
    if (!mDoNotPlaceHandle) {
        Vector3 pos;
        mTriangleRelativeDirection = *GetHandlePos(&pos, mRadius);

        cSPTransform_s0048_1f00 xform(mBlock->mModel->mTransform);
        xform.Invert();

        mBasePositionOffset = mTriangleRelativeDirection;
        xform.TransformPoint(mBasePositionOffset);

        Mat3_s0048_1f00 basis;
        GetOrientation(&basis);

        if (mModel) {
            mModel->mTransform.SetTranslation(mTriangleRelativeDirection);
            mModel->mTransform.SetRotation(basis);
        }
        if (mOverdrawModel) {
            mOverdrawModel->mTransform.SetTranslation(mTriangleRelativeDirection);
            mOverdrawModel->mTransform.SetRotation(basis);
        }
    }
}
