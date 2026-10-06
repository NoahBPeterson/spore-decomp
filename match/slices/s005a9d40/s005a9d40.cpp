// slice s005a9d40 — manipulation cell pinning / manipulation object helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

#define PV(n) virtual void pv##n();

class cObj {
public:
    virtual void v0();
    virtual void v1();   // +0x04
    virtual void v2();   // +0x08
};

class cSetter {
public:
    char  pad0[0x1c];
    cObj* m1c;   // +0x1c
    int   m20;   // +0x20
    int   m24;   // +0x24
    int   m28;   // +0x28
    void Set(cObj** pp, int a, int b, int c);
};

// @ 0x005aa3d0
void cSetter::Set(cObj** pp, int a, int b, int c) {
    cObj* p = *pp;
    cObj* old = m1c;
    if (p != old) {
        if (p)
            p->v1();
        m1c = p;
        if (old)
            old->v2();
    }
    m20 = a;
    m24 = b;
    m28 = c;
}

// ---- large object with a Vector3 at +0x138 ---------------------------------
class cBigThing {
public:
    char pad0[0x138];
    uint32_t mX;   // +0x138
    uint32_t mY;   // +0x13c
    uint32_t mZ;   // +0x140
    void SetVec(uint32_t x, uint32_t y, uint32_t z);
};

// @ 0x005aa580
void cBigThing::SetVec(uint32_t x, uint32_t y, uint32_t z) {
    mX = x;
    mY = y;
    mZ = z;
}
void (cBigThing::*g_setVecPtr)(uint32_t, uint32_t, uint32_t) = &cBigThing::SetVec;

// ---- skin manager tail-call -------------------------------------------------
class cSkinManager {
public:
    void GetSkin(int index);
};
class cPinning {
public:
    char pad0[0xe0];
    cSkinManager* mSkinManager;   // +0xe0
    void Update(int deltaTime);
};

// @ 0x005aa5b0
void cPinning::Update(int) {
    mSkinManager->GetSkin(0);
}

// ---- shared stubs -----------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Mat3 {
    float m[9];
    Mat3(const Mat3& o);   // out-of-line copy ctor (Matrix3::Assign at 0x0041cb40)
    Mat3() {}
};

extern Vec3 g_planeNormal;   // 0x015111a0
extern Vec3 g_up;            // 0x015e8698
extern Vec3 g_up2;           // 0x015e88dc
extern Mat3 g_identity;      // 0x015e8950
extern Vec3 g_zero;          // 0x015e8814

// cdecl helpers
extern "C++" {
bool IntersectRaySphere(const Vec3* org, const Vec3* dir, const Vec3* center, float radius, float* t);  // 0x005a9c40
bool IntersectRayPlane(const Vec3* org, const Vec3* dir, const float* plane, float* t);                // 0x0044e640
void BuildOrientation(Mat3* out, const Vec3* dir, const Vec3* up);                                      // 0x004a89e0
void NormalizeVec3(Vec3* out, const Vec3* in);                                                          // 0x00436ce0
float VecLength(void* obj);                                                                              // 0x004a5bd0
}

class cCamObj { public: char pad[0xc]; Vec3 pos; };
class cBlockInfo { public: bool F4adc40(); };       // 0x004adc40 (thiscall)
class cBlock {
public:
    virtual void v0();
    virtual void AddRef();     // +4
    virtual void Release();    // +8
    char pad[0x28 - 4];
    cBlockInfo* mInfo;         // +0x28
    char pad2[0x48 - 0x2c];
    Vec3 pos;                  // +0x48
    char pad3[0x78 - 0x54];
    Vec3 up2;                  // +0x78
    char pad4[0x3f0 - 0x84];
    cCamObj* mCam;             // +0x3f0
    bool F43bc40(float f);     // 0x0043bc40
    bool HasAnyBlockFlag();    // Entity::HasAnyBlockFlag 0x00435d40
};
void RepinBlockToTorso(cBlock* b, Vec3 pos, Mat3 orient, int flag);   // 0x0049fbd0, cdecl

class cViewerStub {
public:
    void GetWorldRayFromScreenCoords(float x, float y, Vec3* org, Vec3* dir);   // thiscall, ret 0x10
};
class cAppStub {
public:
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21();
    virtual cViewerStub* GetViewer();   // +0x58
};
cAppStub* GetApp();   // SP::App 0x0067dd10

class cRefIface {
public:
    virtual void AddRef();     // +0
    virtual void Release();    // +4
};
template <class T> class AutoRef {
public:
    T* p;
    AutoRef() : p(0) {}
    AutoRef(const AutoRef& o) : p(o.p) { if (p) p->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
    AutoRef& operator=(const AutoRef& o) {
        T* n = o.p;
        T* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
        return *this;
    }
};

class cManipBase {
public:
    cManipBase();               // 0x005b0f80
    virtual void m0();
    bool mFlag4;
    char pad8[0x14 - 8];
};
class cRC {
public:
    cRC() : mnRefCount(0) {}
    virtual void r0();
    virtual void r1();
    int mnRefCount;
};

// ---- 0x005a9d40: drag the block under the mouse ------------------------------
class cManipDrag {
public:
    char pad0[4];
    bool mMoved;      // +4
    char pad5[0x1c - 5];
    cBlock* mBlock;   // +0x1c
    bool OnMouse(float x, float y, int unused);
};

// @ 0x005a9d40
bool cManipDrag::OnMouse(float x, float y, int) {
    if (!mBlock)
        return false;
    Vec3 org, dir, v;
    Mat3 mat;
    cViewerStub* viewer = GetApp()->GetViewer();
    viewer->GetWorldRayFromScreenCoords(x, y, &org, &dir);
    cBlock* b;
    float t;
    if (mBlock->mInfo->F4adc40() && mBlock->F43bc40(1.0f) && mBlock->HasAnyBlockFlag()) {
        b = mBlock;
        float plane[4];
        plane[0] = g_planeNormal.x;
        plane[1] = g_planeNormal.y;
        plane[2] = g_planeNormal.z;
        plane[3] = -((b->pos.y * g_planeNormal.y + b->pos.z * g_planeNormal.z) + b->pos.x * g_planeNormal.x);
        if (!IntersectRayPlane(&org, &dir, plane, &t))
            goto done;
        v.x = (dir.x * t + org.x) - b->pos.x;
        v.y = (dir.y * t + org.y) - b->pos.y;
        v.z = (dir.z * t + org.z) - b->pos.z;
        BuildOrientation(&mat, &v, &g_up);
    } else {
        b = mBlock;
        cCamObj* cam = b->mCam;
        float dx = b->pos.x - cam->pos.x;
        float dy = b->pos.y - cam->pos.y;
        float dz = b->pos.z - cam->pos.z;
        float r = sqrtf((dx * dx + dy * dy) + dz * dz);
        if (IntersectRaySphere(&org, &dir, &b->pos, r, &t)) {
            v.x = (org.x + dir.x * t) - b->pos.x;
            v.y = (org.y + dir.y * t) - b->pos.y;
            v.z = (org.z + dir.z * t) - b->pos.z;
            float inv = 1.0f / sqrtf((v.x * v.x + v.y * v.y) + v.z * v.z);
            v.x = inv * v.x;
            v.y = inv * v.y;
            v.z = inv * v.z;
            float d = (v.y * g_up.y + v.z * g_up.z) + v.x * g_up.x;
            if (0.97 < d)
                v = g_up;
            Vec3 up2 = b->up2;
            BuildOrientation(&mat, &v, &up2);
        } else {
            float a = (dir.x * dir.x + dir.z * dir.z) + dir.y * dir.y;
            float pd = (b->pos.z * dir.z + b->pos.y * dir.y) + b->pos.x * dir.x;
            pd = -pd;
            if (a == 0.0f)
                goto done;
            float tt = ((org.x * dir.x + org.z * dir.z) + org.y * dir.y + pd) / a;
            tt = -tt;
            if (tt < 0.0f)
                goto done;
            Vec3 q;
            q.x = tt * dir.x + org.x;
            q.y = org.y + dir.y * tt;
            q.z = org.z + dir.z * tt;
            Vec3 w;
            w.x = b->pos.x - q.x;
            w.y = b->pos.y - q.y;
            w.z = b->pos.z - q.z;
            float winv = 1.0f / sqrtf((w.x * w.x + w.y * w.y) + w.z * w.z);
            Vec3 wn;
            wn.x = winv * w.x;
            wn.y = winv * w.y;
            wn.z = winv * w.z;
            cam = b->mCam;
            dx = b->pos.x - cam->pos.x;
            dy = b->pos.y - cam->pos.y;
            dz = b->pos.z - cam->pos.z;
            r = sqrtf((dx * dx + dy * dy) + dz * dz);
            if (!IntersectRaySphere(&q, &wn, &b->pos, r, &t))
                goto done;
            Vec3 h;
            h.x = (wn.x * t + q.x) - b->pos.x;
            h.y = (wn.y * t + q.y) - b->pos.y;
            h.z = (wn.z * t + q.z) - b->pos.z;
            NormalizeVec3(&v, &h);
            float d = v.x * g_up.x + (v.z * g_up.z + v.y * g_up.y);
            if (0.97 < d)
                v = g_up;
            Vec3 up2 = b->up2;
            BuildOrientation(&mat, &v, &up2);
        }
    }
    RepinBlockToTorso(mBlock, mBlock->pos, mat, 0);
done:
    if (!mMoved)
        mMoved = true;
    return true;
}

// ---- 0x005aa420: manipulation object ctor (tactile component list at +0x2c) ---
class cManipTactile : public cManipBase, public cRC {
public:
    void* m1c;
    float f20, f24, f28;
    void* mVecBegin;   // +0x2c
    void* mVecEnd;     // +0x30
    void* mVecCap;     // +0x34
    int mAlloc;        // +0x38
    cManipTactile();
    struct VecOut { void** begin; void** end; void** cap; };
    VecOut* CopyList(VecOut* out);
};

// @ 0x005aa420
cManipTactile::cManipTactile()
    : m1c(0), f20(0.0f), f24(0.0f), f28(0.0f), mVecBegin(0), mVecEnd(0), mVecCap(0) {
    mFlag4 = false;
}

// ---- 0x005aa490: vector copy ----------------------------------------------
struct EaVecCtorTarget {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void Ctor(int n, void* alloc);              // eastl::vector(n, alloc): thiscall, ret 8
};
void CopyAutoRefRange(void** result, void** first, void** last, void** dest, void* hint);   // 0x004b2220, cdecl

// @ 0x005aa490
cManipTactile::VecOut* cManipTactile::CopyList(VecOut* out) {
    VecOut* ret = out;
    ((EaVecCtorTarget*)ret)->Ctor(((char*)mVecEnd - (char*)mVecBegin) >> 2, &mAlloc);
    CopyAutoRefRange((void**)&out, (void**)mVecBegin, (void**)mVecEnd, ret->begin, out);
    ret->end = (void**)out;
    return ret;
}

// ---- 0x005aa530: transform init -----------------------------------------------
class cXform {
public:
    uint16_t mA, mB;
    Vec3 mPos;
    float mScale;
    Mat3 mRot;
    void Init();
};

// @ 0x005aa530
void cXform::Init() {
    mRot = g_identity;
    mScale = 1.0f;
    mPos = g_zero;
    mA = 0;
    mB = 0;
}

// ---- 0x005aa5d0: clamp a position to the highest/lowest pinned block ---------
class cBlockSet {
public:
    int Count();                 // 0x004accf0
    class cBlockEntry* At(int);  // 0x004accb0
};
class cBlockEntry {
public:
    char pad0[0x48];
    Vec3 pos;                    // +0x48
    char pad1[0xdc8 - 0x54];
    uint32_t mFlags;             // +0xdc8
};
extern const float g_lowInit;    // 0x013f70b0 (FLT_MAX)
extern const float g_highInit;   // 0x013f70ac (FLT_MIN)

// @ 0x005aa5d0
void __stdcall ClampToPinned(Vec3* out, float a, float y, float z, cBlockSet* set) {
    Vec3 lo, hi;
    lo.x = 0.0f; lo.y = g_lowInit; lo.z = 0.0f;
    hi.x = 0.0f; hi.y = g_highInit; hi.z = 0.0f;
    int i = 0;
    int n = set->Count();
    for (; i < n; i++) {
        uint32_t fl = set->At(i)->mFlags;
        fl >>= 7;
        if (fl & 1) {
            cBlockEntry* e = set->At(i);
            Vec3 p;
            p.x = e->pos.x;
            p.z = e->pos.z;
            const Vec3* pp = &e->pos;
            p.y = pp->y;
            if (lo.y > p.y)
                lo = p;
            else if (p.y > hi.y)
                hi = p;
        }
    }
    if (lo.y > y) {
        out->x = lo.x; out->y = lo.y; out->z = lo.z;
    } else if (y > hi.y) {
        out->x = hi.x; out->y = hi.y; out->z = hi.z;
    } else {
        out->x = 0.0f; out->y = y; out->z = z;
    }
}

// ---- 0x005aa740: remove_copy over AutoRef<cBlock> -----------------------------
// @ 0x005aa740
AutoRef<cBlock>* RemoveCopyBlocks(AutoRef<cBlock>* first, AutoRef<cBlock>* last, AutoRef<cBlock>* dest, const AutoRef<cBlock>* value) {
    for (; first != last; ++first) {
        if (first->p != value->p) {
            *dest = *first;
            ++dest;
        }
    }
    return dest;
}

// ---- cell pinning manipulation --------------------------------------------------
class cSkinMgrIface {
public:
    virtual void AddRef();
    virtual void Release();
};
class cMeshData {
public:
    char pad0[8];
    Vec3* mPositions;      // +8
    char pad1[0x1c - 0xc];
    Vec3* mNormals;        // +0x1c
    void F490(Vec3 v, Vec3* out);   // 0x0050c490, thiscall ret 0x10
    void F5a0(Vec3 v, Vec3* out);   // 0x0050c5a0, thiscall ret 0x10
};
class cSkin { public: char pad[0x34]; cMeshData* mMesh; };
class cSkinMgr { public: cSkin* GetSkin(int idx); };   // SP::cSPEditorSkinManager::GetSkin 0x004c49e0
class cEdgeObj {
public:
    char pad0[8];
    Vec3* mVerts;          // +8
    Vec3* mVertsEnd;       // +0xc
    bool F50bd90(const Vec3* a, const Vec3* b, int one, float* p5, float* p4, float* p3, float* p2, float* p1);   // 0x0050bd90 thiscall ret 0x20
};
class cPosObj { public: char pad[0x48]; float x, y; };      // helper objects with pos
class cPosHolder { public: cPosObj* F4ac610(); cPosObj* F4ac710(); };   // 0x004ac610, 0x004ac710

class cCellPinning : public cManipBase, public cRC {
public:
    void* m1c; void* m20; void* m24;      // 0x1c..0x24
    char pad28[0x30 - 0x28];
    AutoRef<cBlock> mBlockRef;            // +0x30
    char pad34[0x38 - 0x34];
    float mOffX, mOffY, mOffZ;            // +0x38..0x40
    bool mFlag44;                         // +0x44
    char pad45[0xe0 - 0x45];
    AutoRef<cSkinMgrIface> mSkinRef;      // +0xe0
    cEdgeObj* mEdges;                     // +0xe4
    void* mE8; void* mEc; void* mF0;      // 0xe8..0xf0
    char padf4[0xfc - 0xf4];
    void* mFc; void* m100; void* m104;
    char pad108[0x110 - 0x108];
    void* m110; void* m114; void* m118;
    char pad11c[0x124 - 0x11c];
    bool m124;
    char pad125[0x128 - 0x125];
    Vec3 mV1;                             // +0x128
    Vec3 mV2;                             // +0x134
    float m140, m144;
    bool m148;
    cCellPinning();
    void CalculateInflatedMesh();
    bool GetPlacement(Vec3 a, Vec3 b, Vec3* o7, Mat3* o8, Vec3* o9);
    void Setup(const AutoRef<cBlock>& blk, float x, float y, float unused, AutoRef<cSkinMgrIface> skin, bool b1, bool b2);
};

// @ 0x005aa7a0
void cCellPinning::CalculateInflatedMesh() {
    cSkinMgr* skinMgr = (cSkinMgr*)mSkinRef.p;
    cMeshData* mesh = skinMgr->GetSkin(0)->mMesh;
    cEdgeObj* eo = mEdges;
    if (eo && mesh) {
        int n = (int)(eo->mVertsEnd - eo->mVerts);
        if (n > 0) {
            int off = 0;
            do {
                Vec3 nrm = *(Vec3*)((char*)mesh->mNormals + off);
                Vec3 pos = *(Vec3*)((char*)mesh->mPositions + off);
                Vec3 negN;
                negN.x = -nrm.x;
                negN.y = -nrm.y;
                negN.z = -nrm.z;
                Mat3 m;
                BuildOrientation(&m, &negN, &g_up2);
                float az = nrm.z < 0 ? -nrm.z : nrm.z;
                float f = 1.0f;
                if (az < 0.5f)
                    f = (1.0f - az) * 0.5f + 1.0f;
                if (sqrtf((mOffX * mOffX + mOffY * mOffY) + mOffZ * mOffZ) < 0.1f)
                    f = f * 1.5f;
                float a = mOffX * f;
                float b = mOffY * f;
                float c = mOffZ * f;
                Vec3* dst = (Vec3*)((char*)mEdges->mVerts + off);
                dst->x = ((m.m[6] * c + m.m[3] * b) + m.m[0] * a) + pos.x;
                dst->y = ((m.m[1] * a + m.m[4] * b) + m.m[7] * c) + pos.y;
                dst->z = ((m.m[8] * c + m.m[5] * b) + m.m[2] * a) + pos.z;
                off += 12;
                n--;
            } while (n != 0);
        }
    }
}

// @ 0x005aa9c0
bool cCellPinning::GetPlacement(Vec3 a, Vec3 b, Vec3* o7, Mat3* o8, Vec3* o9) {
    float buf[20];
    bool ok = mEdges->F50bd90(&a, &b, 1, &buf[1], &buf[0], &buf[2], &buf[5], &buf[15]);
    cSkin* skin = ((cSkinMgr*)mSkinRef.p)->GetSkin(0);
    cMeshData* mesh = skin->mMesh;
    if (!ok || !mesh)
        return false;
    *o9 = *(Vec3*)&buf[5];
    Vec3 A = *(Vec3*)&buf[1];
    Vec3 out1, out2;
    mesh->F490(A, &out1);
    mesh->F5a0(A, &out2);
    Mat3 m;
    BuildOrientation(&m, &out2, &g_up2);
    *o7 = out1;
    *o8 = m;
    return true;
}

// @ 0x005aab00
void cCellPinning::Setup(const AutoRef<cBlock>& blk, float x, float y, float, AutoRef<cSkinMgrIface> skin, bool b1, bool b2) {
    mBlockRef = blk;
    mOffX = x;
    mOffY = y;
    mOffZ = 0.0f;
    mSkinRef = skin;
    m148 = b1;
    mFlag44 = b2;
    cPosHolder* h = (cPosHolder*)mBlockRef.p->mInfo;
    cPosObj* p1 = h->F4ac610();
    cPosObj* p2 = h->F4ac710();
    mV1.x = p1->x;
    mV1.y = p1->y;
    mV1.x = 0.0f;
    mV1.z = 0.0f;
    mV1.y = mV1.y - VecLength(p1);
    mV2.x = p2->x;
    mV2.y = p2->y;
    mV2.x = 0.0f;
    mV2.z = 0.0f;
    mV2.y = VecLength(p2) + mV2.y;
}

// @ 0x005aac30
cCellPinning::cCellPinning() {
    m1c = 0;
    m20 = 0;
    m24 = 0;
    mBlockRef.p = 0;
    *(void**)&pad34 = 0;
    mOffX = 0.0f;
    mOffY = 0.0f;
    mOffZ = 0.0f;
    mFlag44 = true;
    mSkinRef.p = 0;
    mE8 = 0; mEc = 0; mF0 = 0;
    mFc = 0; m100 = 0; m104 = 0;
    m110 = 0; m114 = 0; m118 = 0;
    m124 = false;
    m148 = false;
    mFlag4 = false;
    m140 = 0.0f;
    m144 = 0.0f;
}
