// Slice s00e62b80: cell-game animation-group placement (poses the group's parts from a base transform).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"
#include <xmmintrin.h>

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
    Matrix3& operator=(const Matrix3& o) { Assign(&o); return *this; }
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

struct cEffectMap {                                      // object returned by 0x00b721d0
    char  mUnk00[0x4c];
    float mCenter[3];                                    // +0x4c
};

struct cEffectMapMgr {
    cEffectMap* FindMap(int handle);                     // 0x00b721d0
};

struct cCellGame {
    char          mUnk00[0x1c];
    cEffectMapMgr mMaps;                                 // +0x1c
    char          mUnk20[0x40fc - 0x20];
    int           mCurrent;                              // +0x40fc
    char          mUnk4100[0x411c - 0x4100];
    int           mEffectMapHandle;                      // +0x411c
    char          mUnk4120[0x514c - 0x4120];
    float         mTime;                                 // +0x514c
    char          mUnk5150[0x5190 - 0x5150];
    char*         mpLevel;                               // +0x5190
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

// ===========================================================================
// 0x00e63400: destruction of a set of model references.  This is a member of
// the (large) cell-gfx object and owns
//   +0x00  eastl::vector<EA::AutoRefCount<SP::cMWModel>, sp_vector_allocator>
//   +0x14  eastl::vector<void*, sp_vector_allocator>
//   +0x28  a raw sp_vector_allocator block
//   +0x3c  one reference-counted object (shared vtable: +0 addRef, +4 release)
// Only the fields the destructor touches are modelled.
// ===========================================================================
struct cMWModel;                                        // SP::cMWModel

struct MWModelRef {                                     // EA::AutoRefCount<SP::cMWModel>
    cMWModel* mpModel;                                  // +0x00
};

struct MWModelRefVec {                                  // eastl::vector<...AutoRefCount...>
    MWModelRef* mpBegin;                                // +0x00
    MWModelRef* mpEnd;                                  // +0x04
    MWModelRef* mpCapEnd;                               // +0x08
    void DoDestroyValues(MWModelRef* first, MWModelRef* last);    // 0x005f3680
};

struct PtrVec {                                         // eastl::vector<void*, sp_vector_allocator>
    void** mpBegin;                                     // +0x00
    void** mpEnd;                                       // +0x04
    void** mpCapEnd;                                    // +0x08
    void DestroyRange(void** first, void** last);       // 0x0070f520
};

void __cdecl FreeRawBlock(void* p);                     // 0x00f47380 EASTL_allocator_deallocate

struct cMWModelRefSet {
    MWModelRefVec mModels;                              // +0x00
    char          pad0c[0x08];                          // +0x0c
    PtrVec        mPtrs;                                // +0x14
    char          pad20[0x08];                          // +0x20
    void*         mpBlock;                              // +0x28
    char          pad2c[0x10];                          // +0x2c
    void*         mpRefObj;                             // +0x3c
    void Destroy();                                     // 0x00e63400
};

static inline void** VTable(void* o) { return *(void***)o; }

// @ 0x00e63400
void cMWModelRefSet::Destroy()
{
    void* obj = mpRefObj;
    if (obj)
        ((void(__thiscall*)(void*))VTable(obj)[1])(obj);
    if (mpBlock) {
        if (((int*)mpBlock)[-1])
            FreeRawBlock(mpBlock);
    }
    mPtrs.DestroyRange(mPtrs.mpBegin, mPtrs.mpEnd);
    if (mPtrs.mpBegin) {
        if (((int*)mPtrs.mpBegin)[-1])
            FreeRawBlock(mPtrs.mpBegin);
    }
    mModels.DoDestroyValues(mModels.mpBegin, mModels.mpEnd);
    if (mModels.mpBegin) {
        if (((int*)mModels.mpBegin)[-1])
            FreeRawBlock(mModels.mpBegin);
    }
}

// ===========================================================================
// 0x00e63480: compose two part transforms and hand the result to a target.
// ===========================================================================
struct cXfCopy {                                       // cSPTransform layout, matrix member
    uint16_t mFlags;                                   // +0x00
    uint16_t mModCount;                                // +0x02
    float    mPos[3];                                  // +0x04
    float    mScale;                                   // +0x10
    Matrix3  mRot;                                     // +0x14
    cXfCopy(const cXfCopy& o)
    {
        mFlags = o.mFlags;
        mModCount = o.mModCount;
        mPos[0] = o.mPos[0];
        mPos[1] = o.mPos[1];
        mPos[2] = o.mPos[2];
        mScale = o.mScale;
        mRot = o.mRot;
    }
    void Invert();                                     // 0x00a7d770
};

struct cSwarmCopy {                                    // EA::Swarm::cTransform layout
    uint16_t mFlags;                                   // +0x00
    uint16_t mModCount;                                // +0x02
    float    mPos[3];                                  // +0x04
    float    mScale;                                   // +0x10
    Matrix3  mRot;                                     // +0x14
    cSwarmCopy(const cSwarmCopy& o)
    {
        mFlags = o.mFlags;
        mModCount = o.mModCount;
        mPos[0] = o.mPos[0];
        mPos[1] = o.mPos[1];
        mPos[2] = o.mPos[2];
        mScale = o.mScale;
        mRot = o.mRot;
    }
    void PostTransformBy(const void* m);               // 0x00a8a140
};

// @ 0x00e63480
namespace SP {
void sPartIntersectTarget(cWinObj* target, const cXfCopy* partA, const cSwarmCopy* partB)
{
    cXfCopy inv(*partA);
    inv.Invert();
    cSwarmCopy t(*partB);
    t.PostTransformBy(&inv);
    target->SetTransform((const cSwarmTransform*)&t);
    target->SetTransformRaw(partA);
}
}  // namespace SP

// ===========================================================================
// 0x00e639d0: spawn/update a part effect and push its fade parameters.
// ===========================================================================
extern float gZero_1485378;                                   // 0x01485378
extern float gScale_1473c70;                                  // 0x01473c70
extern float gCap_13f0e80;                                    // 0x013f0e80
extern "C" int __cdecl CreateEffectSafe(int id, void* effect, int unused, void** out); // 0x00628450

// The retail helper clamps with scalar SSE max/min (maxss/minss, NaN yields lo).
inline void ClampSS(float* dst, const float* lo, const float* hi)
{
    _mm_store_ss(dst, _mm_min_ss(_mm_max_ss(_mm_load_ss(dst), _mm_load_ss(lo)),
                                 _mm_load_ss(hi)));
}

// @ 0x00e639d0
void FUN_00e639d0(int id, void** effectPtr, const void* partA, const void* partB,
                  float param5, float param6, void* effect)
{
    if (param6 < gZero_1485378) {
        if (*effectPtr == 0)
            return;
    } else if (*effectPtr == 0) {
        CreateEffectSafe(id, effect, 0, effectPtr);
        ((cWinObj*)*effectPtr)->SetHidden(0);
    }

    float v = param6 * gScale_1473c70;
    float tmp[3];
    tmp[0] = v;
    tmp[2] = v;
    tmp[1] = 0.0f;
    float cap = gCap_13f0e80;
    ClampSS(&tmp[2], &tmp[1], &cap);
    tmp[0] = tmp[2];

    ((cWinObj*)*effectPtr)->SetTransformRaw(partA);
    ((cWinObj*)*effectPtr)->SetParam(3, &tmp[0], 1);
    ((cWinObj*)*effectPtr)->SetParam(4, &param5, 1);
    SP::sPartIntersectTarget((cWinObj*)*effectPtr, (const cXfCopy*)partA,
                             (const cSwarmCopy*)partB);
}

// ===========================================================================
// 0x00e63560: per-frame cell-game effect-map update.
// ===========================================================================
struct cHandleGuard {
    void* mp;
    cHandleGuard();                                    // 0x00743b50
    ~cHandleGuard();                                   // 0x00e82130
};

struct cEffectKey {                                    // piecewise timing, at entry+8
    float mStart;                                      // +0x00
    float mUnk04;                                      // +0x04
    float mUnk08;                                      // +0x08
    float mEnd;                                        // +0x0c
};

struct cEffectEntry {                                  // 0x1c bytes
    const char* mpName;                                // +0x00
    int         mType;                                 // +0x04
    cEffectKey  mKey;                                  // +0x08
    int         mArg18;                                // +0x18
};

struct cEffectList {
    int           mCount;                              // +0x00
    cEffectEntry* mpEntries;                           // +0x04
};

struct cEffectCatalog {
    char mUnk00[0x3c];
    int  mHandle;                                      // +0x3c
};

struct cCellState {
    char  mUnk00[0x48];
    float mPos[3];                                     // +0x48
};

struct cEffectSlotTable {
    char  mUnk00[0x4c];
    float mScale;                                      // +0x4c
    char  mUnk50[0x0c];
    void* mpSlots[0x5856];                             // +0x5c (stride 4)
    void* mpTemplate4;                                 // +0x161b4
    char  mUnk161b8[4];
    void* mpTemplate13;                                // +0x161bc
    char  mUnk161c0[8];
    void* mpTemplate02;                                // +0x161c8
};

extern cCellState* gspCellState;                       // 0x016b3c0c
extern float   gDefaultPos[3];                         // 0x016b3c54
extern Matrix3 gDefaultRot;                            // 0x016b3c60
extern float   gOne_1485720;                           // 0x01485720
extern float   gHalf_1471064;                          // 0x01471064
extern float   gBoxMin[3];                             // 0x016b3c88
extern float   gBoxMax[3];                             // 0x016b3c94

struct cEffectXf {                                     // cSPTransform / Swarm cTransform, 0x38
    uint16_t mFlags;                                   // +0x00
    uint16_t mModCount;                                // +0x02
    float    mPos[3];                                  // +0x04
    float    mScale;                                   // +0x10
    Matrix3  mRot;                                     // +0x14
    cEffectXf()
    {
        mFlags = 0;
        mModCount = 0;
        mPos[0] = gDefaultPos[0];
        mPos[1] = gDefaultPos[1];
        mPos[2] = gDefaultPos[2];
        mScale = gOne_1485720;
        mRot.Assign(&gDefaultRot);
    }
    void Transform(float* v);                          // 0x007cdee0
};

void* __cdecl FUN_00e4ce40(void* out);                              // 0x00e4ce40
void* __cdecl FUN_00e4cc40(int handle, void* out);                  // 0x00e4cc40
float __cdecl FUN_00e50220(float t, const cEffectKey* key);         // 0x00e50220
void  __cdecl FUN_00e5e2c0(cEffectEntry* e, float f, int arg);      // 0x00e5e2c0
void  __cdecl FUN_00e84e40(const char* fmt, ...);                   // 0x00e84e40
cEffectXf* __cdecl FUN_007d5590(cEffectXf* out, const cEffectXf* lhs,
                                const cEffectXf* rhs);              // 0x007d5590

static cEffectSlotTable* EffectSlots()
{
    return (cEffectSlotTable*)gspCellGfx;
}

// Release the effect held in slot i and clear the slot.
static void ClearEffectSlot(int i)
{
    cWinObj* p = (cWinObj*)EffectSlots()->mpSlots[i];
    if (p) {
        EffectSlots()->mpSlots[i] = 0;
        p->v04();
    }
}

// @ 0x00e63560
namespace SP {
void sUpdateEffectMap()
{
    cHandleGuard catalogGuard;
    cEffectCatalog* catalog = (cEffectCatalog*)FUN_00e4ce40(&catalogGuard);
    cHandleGuard listGuard;
    cEffectList* list = (cEffectList*)FUN_00e4cc40(catalog->mHandle, &listGuard);

    float time = gspCellGame->mTime;
    for (int i = 0; i < list->mCount; ++i) {
        cEffectEntry* entry = &list->mpEntries[i];
        cWinObj* effect = (cWinObj*)EffectSlots()->mpSlots[i];
        float f = FUN_00e50220(time, &entry->mKey);
        if (entry->mType == 5) {
            FUN_00e5e2c0(entry, f, entry->mArg18);
            continue;
        }
        if (effect && !effect->IsReady()) {
            ClearEffectSlot(i);
            effect = 0;
        }
        if (f == 0.0f) {
            if (effect) {
                effect->SetShown(1);
                ClearEffectSlot(i);
            }
            continue;
        }
        if (!effect) {
            int id;
            switch (entry->mType) {
            case 0:
            case 2:  id = (int)EffectSlots()->mpTemplate02; break;
            case 1:
            case 3:  id = (int)EffectSlots()->mpTemplate13; break;
            case 4:  id = (int)EffectSlots()->mpTemplate4; break;
            default: id = 0; break;
            }
            ClearEffectSlot(i);
            CreateEffectSafe(id, (void*)entry->mpName, 0, &EffectSlots()->mpSlots[i]);
            effect = (cWinObj*)EffectSlots()->mpSlots[i];
            if (!effect) {
                FUN_00e84e40("couldn't start effect %s", entry->mpName);
                continue;
            }
            effect->SetHidden(1);
        }
        effect->SetParam(4, &f, 1);

        cEffectXf partXf;
        if (entry->mType == 2 || entry->mType == 3) {
            float s = gOne_1485720 / EffectSlots()->mScale;
            partXf.mPos[0] = gspCellState->mPos[0] * s;
            partXf.mPos[1] = gspCellState->mPos[1] * s;
            partXf.mPos[2] = gspCellState->mPos[2] * s;
            partXf.mFlags |= 4;
            ++partXf.mModCount;
        }
        effect->SetTransform((const cSwarmTransform*)&partXf);

        cEffectXf drawXf;
        if ((unsigned)entry->mType <= 4) {
            drawXf.mScale = EffectSlots()->mScale;
            ++drawXf.mModCount;
        }
        effect->SetTransformRaw(&drawXf);

        cEffectMap* map = gspCellGame->mMaps.FindMap(gspCellGame->mEffectMapHandle);
        if (map) {
            cEffectXf placed;
            FUN_007d5590(&placed, &drawXf, &partXf);
            float v[3];
            v[0] = map->mCenter[0] - (gBoxMax[0] + gBoxMin[0]) * gHalf_1471064;
            v[1] = map->mCenter[1] - (gBoxMax[1] + gBoxMin[1]) * gHalf_1471064;
            v[2] = map->mCenter[2] - (gBoxMax[2] + gBoxMin[2]) * gHalf_1471064;
            placed.Transform(v);
            effect->SetParam(9, v, 3);
            effect->SetParam(10, &gOne_1485720, 1);
        }
    }
}
}  // namespace SP
