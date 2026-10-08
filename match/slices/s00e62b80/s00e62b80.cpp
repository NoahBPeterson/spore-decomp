// Slice s00e62b80: cell-game animation-group placement (poses the group's parts from a base transform).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

// ------------------------------------------------------------------ transform stubs
extern float gTransPos[3];   // 0x016b3c28 default translation
extern float gIdentRot[9];   // 0x016b3dac default rotation (identity)

struct cSPTransform {                                    // 0x38 bytes
    uint16_t mFlags;
    uint16_t mModCount;
    float    mPos[3];
    float    mScale;
    float    mRot[9];
    cSPTransform()
    {
        mFlags = 0;
        mModCount = 0;
        mPos[0] = gTransPos[0];
        mPos[1] = gTransPos[1];
        mPos[2] = gTransPos[2];
        mScale = 1.0f;
        for (int i = 0; i < 9; ++i) mRot[i] = gIdentRot[i];
    }
    cSPTransform(int) {}                                 // uninitialised (fields filled by the caller)
    cSPTransform& operator=(const cSPTransform& o);      // 0x00537dc0
    void PostTransformBy();                              // 0x00a7d770
};

struct Matrix3 {
    float m[9];
    Matrix3() {}
    void Assign(const Matrix3* src);                     // 0x0041cb40
    Matrix3(const Matrix3& o) { Assign(&o); }
};

struct cSwarmTransform {                                 // EA::Swarm::cTransform, 0x38 bytes
    uint16_t mFlags;
    uint16_t mModCount;
    float    mPos[3];
    float    mScale;
    Matrix3  mRot;
    void PostTransformBy(const cSPTransform* t);         // 0x00a8a140
};

struct cQuat { float q[4]; };
cQuat* __cdecl QuaternionFromMatrix33(cQuat* out, const float* m, float eps);   // 0x00472b80
Matrix3* __cdecl MakeAxisAngle(Matrix3* out, const float* axis, float angle);    // 0x00453b20
extern float gAxisZ[4];   // 0x015a7c40
extern float gPi;         // 0x015a7c24

// ------------------------------------------------------------------ game objects
struct cHandleRef {
    int mp;
    cHandleRef();                                        // 0x00743b50
    ~cHandleRef();                                       // 0x00e82130
};

struct cPartList {                                       // list returned by 0x00e823a0
    char pad0[0x14];
    char* mpEntries;                                     // +0x14, 0x28-byte entries
    int   mCount;                                        // +0x18
};
struct cPartEntry {
    int idx;                                             // +0x00 (-1 = none)
    int type;                                            // +0x04
};

// Object with position/quaternion at +4 (type 3 parts and the root object).
struct cPosObj {
    int   vt;
    float pos[3];                                        // +0x04
    float quat[4];                                       // +0x10
    char  pad20[0x3c - 0x20];
    float scale2;                                        // +0x3c
    char  pad40[0x80 - 0x40];
    float param80;                                       // +0x80
    char  pad84[0x180 - 0x84];
    int   h180;                                          // +0x180
    void  Place(int v);                                  // 0x00a04d00
    void  Refresh(int v);                                // 0x00a047d0
};

// Object with a transform at +8 (type 0 parts and the secondary object).
struct cXfObj {
    int   vt;
    char  pad4[4];
    cSPTransform xf;                                     // +0x08 (flags +8, modcount +0xa, pos +0xc, scale +0x18, rot +0x1c)
};

// Window-like part driven through its vtable (type 1).
struct cWinObj {
    virtual void v00();
    virtual void v04();
    virtual void SetHidden(int h);                       // 0x08
    virtual void SetShown(int s);                        // 0x0c
    virtual bool IsReady();                              // 0x10
    virtual void SetTransformRaw(const void* t);         // 0x14
    virtual void SetTransform(const cSwarmTransform* t); // 0x18
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void SetVisible(int v);                      // 0x30
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void SetParam(int id, const void* p, int n); // 0x44
};

struct cCellGame {
    char pad0[0x40fc];
    int  mCurrent;                                       // +0x40fc
    char pad4100[0x5190 - 0x4100];
    char* mpLevel;                                       // +0x5190
};
struct cCellGfx {
    char pad0[0x161c0];
    int  mAltTable;                                      // +0x161c0
    char pad161c4[4];
    int  mMainTable;                                     // +0x161c4 (+0x161c8) ...
};
extern cCellGame* gspCellGame;                           // 0x016b3c04
extern char*      gspCellGfx;                            // 0x016b3c08

cPartList* __cdecl GetPartList(int handle, cHandleRef* ref);            // 0x00e4cc40 -> 0x00e823a0
float __cdecl NormalizedLevel(void* obj, int level);                    // 0x00e51720
void  __cdecl ApplyTable(int table, void* obj, float v);                // 0x00e83640
void  __cdecl FetchPartTransform(cPosObj* root, int idx, cSPTransform* out);  // 0x00e84150
float __cdecl Interp3(float a, float b, float c);                       // 0x01041cd0

struct cAnimGroup {
    char  pad0[0x14];
    int   mHandle;                                       // +0x14
    char  pad18[0x24 - 0x18];
    cPosObj* mpRoot;                                     // +0x24
    cXfObj*  mpSecond;                                   // +0x28
    void* mpParts[11];                                   // +0x2c
    float mProgress;                                     // +0x58
    char  mDirty;                                        // +0x5c
    void Place(const cSPTransform* base, float p2, float z0, float z1, const cSPTransform* pre,
               int a6, int a7, int a8, int a9);         // 0x00e62b80
};

// @ 0x00e62b80
void cAnimGroup::Place(const cSPTransform* base, float p2, float z0, float z1, const cSPTransform* pre,
                       int a6, int a7, int a8, int a9)
{
    cHandleRef ref;
    cPartList* list = GetPartList(mHandle, &ref);
    float scale = base->mScale;
    float zsum = z0 + z1;
    if (mpRoot) {
        cPosObj* o = mpRoot;
        o->pos[0] = base->mPos[0];
        o->pos[1] = base->mPos[1];
        o->pos[2] = base->mPos[2];
        mpRoot->pos[2] = zsum;
        cQuat qtmp;
        cQuat* q = QuaternionFromMatrix33(&qtmp, base->mRot, 0.0f);
        cQuat qq = *q;
        mpRoot->quat[0] = qq.q[0];
        mpRoot->quat[1] = qq.q[1];
        mpRoot->quat[2] = qq.q[2];
        mpRoot->quat[3] = qq.q[3];
        mpRoot->scale2 = base->mScale * 2.5f;
        mpRoot->Place(a9);
        mpRoot->param80 = p2;
        if (mDirty) mpRoot->Refresh(1);
        float lv = NormalizedLevel((void*)a9, *(int*)(gspCellGame->mpLevel + 0x1c));
        int table = (a9 == gspCellGame->mCurrent) ? *(int*)(gspCellGfx + 0x161cc) : *(int*)(gspCellGfx + 0x161c0);
        ApplyTable(table, (void*)mpRoot->h180, lv);
    }
    if (mpSecond) {
        cXfObj* b = mpSecond;
        b->xf = *base;
        const float zero = 0.0f;
        const float one = 1.0f;
        float* r = b->xf.mRot;
        float out[9];
        for (int k = 0; k < 9; k += 3) {
            float x = r[k], y = r[k + 1], z = r[k + 2];
            out[k]     = (z * zero - x * one) + y * zero;
            out[k + 1] = (x * zero - y * one) + z * zero;
            out[k + 2] = (x * zero + z) + y * zero;
        }
        b->xf.mFlags |= 2;
        b->xf.mModCount += 1;
        for (int i = 0; i < 9; ++i) r[i] = out[i];
        ApplyTable(*(int*)(gspCellGfx + 0x161cc), (void*)b, 1.0f);
    }

    int i = 0;
    if (list->mCount > 0) {
        int off = 0;
        void** slot = mpParts;
        do {
            cSPTransform t;
            cPartEntry* e = (cPartEntry*)(list->mpEntries + off);
            if (e->idx == -1 || !mpRoot)
                t = *base;
            else
                FetchPartTransform(mpRoot, e->idx, &t);
            float nz = t.mPos[2] + zsum;
            t.mFlags |= 4;
            t.mModCount += 1;
            t.mPos[2] = nz;
            int type = e->type;
            void* part = *slot;
            if (type == 0) {
                if (part) {
                    cXfObj* p = (cXfObj*)part;
                    p->xf.mModCount += 1;
                    p->xf.mScale = t.mScale * 2.1f;
                    for (int j = 0; j < 9; ++j) p->xf.mRot[j] = t.mRot[j];
                    p->xf.mFlags |= 2;
                    p->xf.mModCount += 1;
                    p->xf.mPos[0] = t.mPos[0];
                    p->xf.mPos[1] = t.mPos[1];
                    p->xf.mFlags |= 4;
                    p->xf.mModCount += 1;
                    p->xf.mPos[2] = nz;
                }
            } else if (type == 1) {
                cWinObj* w = (cWinObj*)part;
                cSwarmTransform t2;
                t2.mFlags = t.mFlags;
                t2.mModCount = t.mModCount;
                t2.mPos[0] = t.mPos[0];
                t2.mPos[1] = t.mPos[1];
                t2.mPos[2] = nz;
                t2.mScale = t.mScale;
                t2.mRot.Assign((const Matrix3*)t.mRot);
                cSPTransform t3(0);
                t3.mFlags = pre->mFlags;
                t3.mModCount = pre->mModCount;
                t3.mPos[0] = pre->mPos[0];
                t3.mPos[1] = pre->mPos[1];
                t3.mPos[2] = pre->mPos[2];
                t3.mScale = pre->mScale;
                ((Matrix3*)t3.mRot)->Assign((const Matrix3*)pre->mRot);
                t3.PostTransformBy();
                t2.PostTransformBy(&t3);
                if (0.0f < t2.mScale) {
                    w->SetTransform(&t2);
                    w->SetVisible(0);
                } else {
                    w->SetVisible(1);
                }
                w->SetTransformRaw(pre);
                w->SetParam(4, &p2, 1);
                if (scale < 0.0f) {
                    w->SetShown(1);
                } else if (!w->IsReady()) {
                    w->SetHidden(0);
                }
            } else if (type == 3) {
                if (part) {
                    Matrix3 mtmp;
                    static Matrix3 sRot(*MakeAxisAngle(&mtmp, gAxisZ, gPi));
                    cPosObj* p = (cPosObj*)part;
                    p->pos[0] = t.mPos[0];
                    p->pos[1] = t.mPos[1];
                    p->pos[2] = nz;
                    cQuat qtmp;
                    cQuat* q = QuaternionFromMatrix33(&qtmp, t.mRot, 0.0f);
                    cQuat qq = *q;
                    p->quat[0] = qq.q[0];
                    p->quat[1] = qq.q[1];
                    p->quat[2] = qq.q[2];
                    p->quat[3] = qq.q[3];
                    p->scale2 = t.mScale * 2.5f;
                    if (mDirty) p->Refresh(1);
                }
            }
            float v = Interp3(0.0f, 0.0f, scale);
            float c = 0.0f;
            if (0.0f <= v) c = v;
            if (1.0f <= c) c = 1.0f;
            mProgress = c;
            ++slot;
            ++i;
            off += 0x28;
            mDirty = 0;
        } while (i < list->mCount);
    }
}
