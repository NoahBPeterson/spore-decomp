// src/game/SPBake/SPEditorHandleDeform.cpp -- migrated from slice(s) s00481f00, s00480320, s0047f520 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorHandleDeform.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* EditorTuning();                       // tuning struct, Vec3 members at +0x6c.. +0x90
extern void  Transform_Ctor(void* t);              // 0x409930
extern void  TrianglePinningInfo_Ctor(void* p);    // FUN_004e8f70
extern void  TrianglePinningInfo_Dtor(void* p);    // FUN_004ae250
extern const float kDeformVec0, kDeformVec1, kDeformVec2;  // 0x15d4fd8..0x15d4fe0
extern const float kPreviewDelta;                          // 0x1471064 (0.5f)
extern char gEmptyString[];                                // 0x1667bac

// ---- items of slice s0047f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint32_t u32;
struct Vec3 { float x, y, z; };
struct cMWModel { char pad[0x44]; u32 mGroups[2]; };
struct cSPEditorHandle;
extern void* EditorTuning();                       // tuning struct, Vec3 members at +0x6c.. +0x90
extern void  cSPEditorHandle_Shutdown(cSPEditorHandle*);   // SP::cSPEditorHandle::Shutdown
extern void  cSPEditorHandle_BaseCtor(cSPEditorHandle*);   // FUN_0047d6a0
extern void  Transform_Ctor(void* t);              // 0x409930
extern void  TrianglePinningInfo_Ctor(void* p);    // FUN_004e8f70
extern void  TrianglePinningInfo_Dtor(void* p);    // FUN_004ae250
extern const float kDeformVec0, kDeformVec1, kDeformVec2;  // 0x15d4fd8..0x15d4fe0
extern const float kPreviewDelta;                          // 0x1471064 (0.5f)
extern char gEmptyString[];                                // 0x1667bac
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
struct cSPEditorBlock;
struct cSPEditorHandle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void GetPosition(Vec3* out);   // slot 0x24
    void* mRefCountVft;                    // +4
    char pad8[8];
    cSPEditorBlock* mBlock;                // +0x10
    cMWModel* mModel;                      // +0x14
    cMWModel* mOverdrawModel;              // +0x18
    char pad1c[0x34];
};
struct DeformIface { void* QueryInterface(u32 id); };
// ---- items of slice s0047f520 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void  cSPEditorHandle_Shutdown(cSPEditorHandle*);   // SP::cSPEditorHandle::Shutdown
extern void  cSPEditorHandle_BaseCtor(cSPEditorHandle*);   // FUN_0047d6a0

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
void     TransformPoint(void* xform, Vector3* p);                  // @ 0x0044d4f0 (ecx=xform)
Vector3* Interp(Vector3* out, const Vector3* a, const Vector3* b, float t); // @ 0x00413cc0
struct RotHandle {
    char pad0[0x10];
    void* mBlock;                  // +0x10
    char pad14[0x7c];
    Vector3 mP0;                   // +0x90
    Vector3 mP1;                   // +0x9c
    char padA8[0xd8];
    float  mRadius;                // +0x180
    char pad184[0x4c];
    uint8_t mDone;                 // +0x1d5

    Vector3* GetHandlePos(Vector3* out, float t);
    Vector3* GetDir(Vector3* out, bool useParent);
    Vector3* GetP0(Vector3* out, bool transform);
    Vector3* GetP1(Vector3* out, bool transform);
    void*    GetOrientation(void* out);
    void     Update();             // 0x4823b0, partial
};
struct EntityXform {
    char pad[8];
    void TransformPoint(Vector3* p);   // uses 0x44d4f0 on this+8
};
// ---- items of slice s00481f00 end

// @ 0x0047fa30
void* __fastcall cSPEditorHandleDeform_Ctor(cSPEditorHandle* self)
{
    cSPEditorHandle_BaseCtor(self);
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    Transform_Ctor((char*)self + 0x50);
    AT(u32, self, 0xac) = 0x95f07f3d;      // mPinningType
    AT(u32, self, 0xb0) = 0;               // mAxisToIgnore
    AT(void*, self, 0xb4) = 0;             // mSymmetricHandle
    AT(char, self, 0x118) = 0;             // mSetPickData
    // empty eastl string at +0x11c
    AT(char*, self, 0x11c) = 0;
    AT(char*, self, 0x120) = 0;
    AT(char*, self, 0x124) = 0;
    AT(char*, self, 0x11c) = gEmptyString;
    AT(char*, self, 0x120) = AT(char*, self, 0x11c);
    AT(char*, self, 0x124) = AT(char*, self, 0x11c) + 1;
    for (int off = 0x12c; off <= 0x144; off += 0xc) {
        AT(float, self, off)     = kDeformVec0;
        AT(float, self, off + 4) = kDeformVec1;
        AT(float, self, off + 8) = kDeformVec2;
    }
    AT(float, self, 0x184) = kPreviewDelta;
    TrianglePinningInfo_Ctor((char*)self + 0x188);
    AT(char, self, 0x1d5) = 0;
    return self;
}

// @ 0x0047fcb0
void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle* self)
{
    cSPEditorHandle_Shutdown(self);
    AT(u32, self, 0xb4) = 0;
    TrianglePinningInfo_Dtor((char*)self + 0x188);
}

// @ 0x0047fce0
void* DeformIface::QueryInterface(u32 id)
{
    void* self = this;
    switch (id) {
    case 0xee3f516e: return self;
    case 0x050a1fe5: return self;
    case 0x050a993c: return self;
    }
    return 0;
}

// @ 0x00480280
Vec3* __fastcall Deform_GetTuningVec(char* self, int /*edx*/, Vec3* out)
{
    char* t = (char*)EditorTuning();
    u32 k = AT(u32, self, 0x8c);
    if (k == 0x503283aa)      *out = AT(Vec3, t, 0x78);
    else if (k == 0xe20e2032) *out = AT(Vec3, t, 0x84);
    else                      *out = AT(Vec3, t, 0x6c);
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

// @ 0x004823b0
void RotHandle::Update()
{
    if (this->mDone)
        return;
    char xform[0x38];
    void GetLocalTransform(void*, void*);              // @ 0x0040ce80
    GetLocalTransform(*(char**)((char*)this->mBlock + 0x10) + 8, xform);
    void PartTransformInvert(void*);                   // @ 0x0040efa0
    PartTransformInvert(xform);
}
