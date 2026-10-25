// Slice s00480320: SP::cSPEditorHandleDeform pick-ray helpers (SetPickOffset, SetPickData),
// plus the RingHandle::Update matched in an earlier wave.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast  (editor /Od region, no /EHsc).
#include "types.h"
// |v| via the x87 fabs the original folds in; the pragma must precede <math.h> so the
// intrinsic wins and no CRT symbol is referenced.
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
#include <math.h>

// ---- rw::math / cSP math types -------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
    float SquaredLength() const { return x * x + y * y + z * z; }
};

// The original funnels a handful of Vector3 copies through one shared out-of-line copy
// constructor (0x004098a0); this derived type stands in for it so those sites stay calls.
struct Vector3Copyable : Vector3 {
    Vector3Copyable(const Vector3& o);                          // 0x004098a0
    Vector3& Vec();                                             // opaque view, keeps the reload
    const Vector3& Vec() const;                                 // opaque view, keeps the reload
};
Vector3Copyable::Vector3Copyable(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
Vector3& Vector3Copyable::Vec() { return *this; }
const Vector3& Vector3Copyable::Vec() const { return *this; }

Vector3 operator-(const Vector3& a, const Vector3& b);          // 0x0041db10
Vector3 operator+(const Vector3& a, const Vector3& b);          // 0x0041dc10
Vector3 operator*(const Vector3& a, const float& s);            // 0x0041dca0
Vector3 operator*(const float& s, const Vector3& a);            // 0x0041de40
float   Dot3(const Vector3& a, const Vector3& b);               // 0x00455cc0
Vector3 Normalize(const Vector3& v);                            // 0x00436ce0
inline float AbsF(float v) { return fabsf(v); }

struct cSPMatrix3 {
    Vector3 xAxis, yAxis, zAxis;                                // 3 rows, 0x24 bytes
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& o);                            // 0x0041cb40
};
extern const cSPMatrix3 kIdentityMatrix;                        // 0x015d4ea8
extern const Vector3 kZeroVector;                               // 0x015d4fd8

struct cSPTransform {
    unsigned short mFlags;                                      // +0
    unsigned short mModificationCount;                          // +2
    Vector3 mTranslation;                                       // +4
    float mScale;                                               // +0x10
    cSPMatrix3 mRotation;                                       // +0x14
    cSPTransform();                                             // 0x00409930
};

struct cSPBoundingBox {
    Vector3 mMin;                                               // +0
    Vector3 mMax;                                               // +0xc
    Vector3& GetCenter(Vector3& out) const;                     // 0x00409b90
    void TransformBy(const cSPTransform& t);                    // 0x00409dd0
};

namespace SP {

class cSPEditorBlock { public:
    cSPBoundingBox GetBBox(int type, bool a, bool b);           // 0x0044ae00
    cSPTransform GetLocalTransform();                           // 0x00436380
};

struct cModelDeformationHandle {
    unsigned int mHandleType;                                   // +0
    cSPTransform mTransform;                                    // +4
    unsigned int mAnimationID;                                  // +0x3c
    Vector3 mStartPt;                                           // +0x40
    Vector3 mEndPt;                                             // +0x4c
    float mRestVal;                                             // +0x58
};

class cSPEditorHandle {
public:
    virtual void v00();
    char pad04[0x0c - 0x04];
    void* mPropList;                                            // +0x0c
    cSPEditorBlock* mBlock;                                     // +0x10
    char pad14[0x50 - 0x14];
};

class cSPEditorHandleDeform : public cSPEditorHandle { public:
    cModelDeformationHandle mData;                              // +0x50
    unsigned int mPinningType;                                  // +0xac
    unsigned int mAxisToIgnore;                                 // +0xb0
    void* mSymmetricHandle;                                     // +0xb4
    Vector3 mPickOrigin;                                        // +0xb8
    Vector3 mPickDirection;                                     // +0xc4
    Vector3 mHandleStart;                                       // +0xd0
    Vector3 mHandleEnd;                                         // +0xdc
    Vector3 mHandleStartLocal;                                  // +0xe8
    Vector3 mHandleEndLocal;                                    // +0xf4
    Vector3 mBlockPositionForPicking;                           // +0x100
    Vector3 mBlockPickReference;                                // +0x10c
    bool mSetPickData;                                          // +0x118

    void SetPickOffset(float offset);                           // 0x004809c0
    void SetPickData();                                         // 0x00480cf0
};

}  // namespace SP

// @ 0x00480cf0
// Derives the pick ray from the deformation handle's start/end points: direction runs from
// end to start, the origin sits five units behind the end point, and the local start point
// and block reference are cached before refreshing the offset.
void SP::cSPEditorHandleDeform::SetPickData()
{
    cSPTransform local = mBlock->GetLocalTransform();           // 0x00436380

    Vector3 diff = mData.mStartPt - mData.mEndPt;                // 0x0041db10
    Vector3 dir = Normalize(diff);                              // 0x00436ce0
    mPickDirection = dir;

    Vector3 scaled = 5.0f * mPickDirection;                     // 0x0041de40
    mPickOrigin = mData.mEndPt - scaled;                        // 0x0041db10

    mHandleStartLocal = mData.mStartPt;
    mBlockPickReference = mData.mEndPt;

    SetPickOffset(0.01f);                                       // 0x004809c0
    mSetPickData = true;
}

// @ 0x004809c0
// Tilts the pick direction towards the current block bounds by "offset": the bounds are
// normalised to world space, the ray from the pick origin to the bounds centre is nudged
// along whichever axis is misaligned, then folded into the existing direction.
void SP::cSPEditorHandleDeform::SetPickOffset(float offset)
{
    cSPBoundingBox bounds = mBlock->GetBBox(1, false, false);   // 0x0044ae00

    cSPTransform transform;                                     // 0x00409930
    transform.mRotation = kIdentityMatrix;                      // 0x015d4ea8
    transform.mScale = 1.0f;
    transform.mTranslation = kZeroVector;                       // 0x015d4fd8
    transform.mFlags = 0;
    transform.mModificationCount = 0;
    bounds.TransformBy(transform);                              // 0x00409dd0

    Vector3 center;
    bounds.GetCenter(center);                                   // 0x00409b90

    Vector3 target = center - mPickOrigin;                      // 0x0041db10
    Vector3 dir = Normalize(target);                            // 0x00436ce0

    Vector3 scaled;
    // The first alignment test is an inline dot the original folds into the compare; the
    // second goes through the shared Dot3 helper.
    if (AbsF(mPickDirection.x * dir.x + mPickDirection.y * dir.y + mPickDirection.z * dir.z) > 0.999f) {
        Vector3Copyable adjusted(dir);                          // 0x004098a0
        adjusted[0] += offset * 5.0f;
        adjusted.Vec() = Normalize(adjusted.Vec());
        if (AbsF(Dot3(mPickDirection, adjusted)) > 0.999f) {    // 0x00455cc0
            adjusted.Vec() = dir;
            adjusted[1] += offset * 5.0f;
            adjusted.Vec() = Normalize(adjusted.Vec());
        }
        Vector3Copyable s1(adjusted * offset);                  // 0x0041dca0, 0x004098a0
        scaled = s1;
    } else {
        Vector3Copyable s2(dir * offset);                       // 0x0041dca0, 0x004098a0
        scaled = s2;
    }

    Vector3Copyable sum(mPickDirection + scaled);               // 0x0041dc10, 0x004098a0
    mPickDirection = Normalize(sum);
}

// @ 0x00480320
// Rotation ring Update: places the two attached handle objects (m14 and m18) at the ring
// end point, orients them with the ring basis and queues their property updates.
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vec3POD { float x, y, z; };
struct Mat33 { float m[9]; };
Vec3 operator-(const Vec3& a, const Vec3& b);               // @ 0x0041db10
Vec3 operator*(const Vec3& a, const float& s);              // @ 0x0041dca0

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
    virtual void PointAt(Vec3* out, float t);               // +0x4c
    char pad04[0x10];
    ObjRef m14;                                             // +0x14
    ObjRef m18;                                             // +0x18
    char pad1c[0xc];
    float mScale;                                           // +0x28

    void GetOrientation(Mat33* out);                        // @ 0x004822d0
    void Update();                                          // @ 0x00480320
};

void RingHandle::Update()
{
    // slot order only (n31 = mgr, begin = along, p4 = basis, where = endpoint, p18 = side, mid = p0, p30 = p1)
    MsgMgr* n31 = GetMsgMgr();
    Vec3 mid, p30, begin, where, p18;
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

