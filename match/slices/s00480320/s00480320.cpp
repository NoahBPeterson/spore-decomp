// Slice s00480320: cSPEditorHandleRotationRing geometry helpers, /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 { float x, y, z; };

// vector helpers (masked relocations)
Vector3* VecSubtract(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041db10
Vector3* VecNormalize(Vector3* out, const Vector3* in);                  // @ 0x00436ce0
Vector3* VecScale(Vector3* out, const float* s, const Vector3* v);       // @ 0x0041de40
Vector3* VecCross(Vector3* out, const Vector3* a, const Vector3* b);     // @ 0x0041dca0
void     GetLocalTransform(void* entity, void* matrix);                  // @ 0x00436380

// @ 0x00480cf0
void Ring_Reset(char* self)
{
    char matrix[0x38];
    GetLocalTransform(*(void**)(self + 0x10), matrix);

    Vector3 diff, dir;
    VecSubtract(&diff, (Vector3*)(self + 0x90), (Vector3*)(self + 0x9c));
    VecNormalize(&dir, &diff);
    *(Vector3*)(self + 0xc4) = dir;

    float scale = *(float*)0x13eb960;   // 5.0f
    Vector3 scaled, offset;
    VecScale(&scaled, &scale, (Vector3*)(self + 0xc4));
    VecSubtract(&offset, (Vector3*)(self + 0x9c), &scaled);
    *(Vector3*)(self + 0xb8) = offset;

    *(Vector3*)(self + 0xe8) = *(Vector3*)(self + 0x90);
    *(Vector3*)(self + 0x10c) = *(Vector3*)(self + 0x9c);

    void Ring_Rotate(char*, float);      // @ 0x004809c0
    Ring_Rotate(self, *(float*)0x13eb960);
    *(uint8_t*)(self + 0x118) = 1;
}

// @ 0x004809c0 -- PARTIAL: bounding-box / basis rebuild; only the entry BBox call
// and the normalisation tail are reproduced, the inner branchy math is omitted.
void Ring_Rotate(char* self, float angle)
{
    void GetBBox(void*, void*, int, int, int);   // @ 0x00480e90 region helper
    char bbox[0x28];
    GetBBox(*(void**)(self + 0x10), bbox, 1, 0, 0);
    (void)angle;
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

