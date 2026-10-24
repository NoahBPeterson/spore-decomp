// gold7 batch, worker 5: two Simulator functions sharing the space-mission element model.
//   0x00c5cff0  read of the 0x20-byte mission-element list (attribute mBackgroundShipsList, +0x238)
//   0x00c5d140  SP::UFO_STRAFE_ATTACK_TARGET_Deactivate
// The mission-element vector and the copy/insert helpers match s00c5b9c0 / s00c5a580.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast

#include "types.h"

float sinf(float fValue);
float cosf(float fValue);
float sqrtf(float fValue);

namespace eastl { struct string8; }
typedef eastl::string8 string8;

struct Vec3 {
    float x, y, z;
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

// 0x20-byte mission element (vtable 0x0146f688).
struct MissionElem {
    void** vtbl;    // 0x00
    int    id;      // 0x04
    Vec3   pos;     // 0x08
    float  f14;     // 0x14
    float  f18;     // 0x18
    int    i1c;     // 0x1c
};

struct ElemVec {
    MissionElem* begin;   // 0x00
    MissionElem* end;     // 0x04
    MissionElem* cap;     // 0x08
    void Insert(MissionElem* pos, MissionElem* val);   // 0x00c5bf80
};

MissionElem* __cdecl CopyMissionElementsForward(MissionElem* first, MissionElem* last,
                                                MissionElem* dst);      // 0x00c5b450

// serializer plumbing
class ISerializerReadStream;
namespace EA { namespace IO {
    void ReadInt32(void* pStream, void* pDest, int nCount, int bFlag);   // 0x0093a780
} }

extern void* g_MissionElemVtable[4];   // 0x0146f688  {0xc5ae30, 0xc5aea0, 0xc5bcf0, 0xc5df50}
extern float g_elemPosX;               // 0x01691fc8
extern float g_elemPosY;               // 0x01691fcc
extern float g_elemPosZ;               // 0x01691fd0
extern float g_elemNegOne;             // 0x013eb1bc

void FUN_00c5bef0(ElemVec* vec, int n);                                 // 0x00c5bef0

// @ 0x00c5cff0
bool Read_00c5cff0(int unused0, ElemVec* vec, int unused2, void* pStream, int unused4, int nLast)
{
    CopyMissionElementsForward(vec->end, vec->end, vec->begin);
    vec->end += (vec->begin - vec->end);

    int count = 0;
    {
        void** sv = (void**)((void*(*)(void*))((void**)pStream)[0x20 / 4])(pStream);
        void*  rd = (void*)((void*(*)(void*))sv[0x18 / 4])(sv);
        EA::IO::ReadInt32(rd, &count, 1, 0);
    }
    FUN_00c5bef0(vec, nLast);
    (void)unused0; (void)unused2; (void)unused4;

    for (int i = 0; i < count; ++i) {
        MissionElem elem;
        elem.vtbl = g_MissionElemVtable;
        elem.id   = -1;
        elem.pos.x = g_elemPosX;
        elem.pos.y = g_elemPosY;
        elem.pos.z = g_elemPosZ;
        elem.f14 = g_elemNegOne;
        elem.f18 = g_elemNegOne;
        elem.i1c = -1;
        ((void(*)(MissionElem*, void*))g_MissionElemVtable[1])(&elem, pStream);

        MissionElem* p = vec->end;
        if (p < vec->cap) {
            vec->end = p + 1;
            if (p != 0)
                *p = elem;
        }
        else {
            vec->Insert(p, &elem);
        }
    }
    return ((bool(*)(void*))((void**)pStream)[0x1c / 4])(pStream);
}

// ---------------------------------------------------------------------------
// 0x00c5d140  SP::UFO_STRAFE_ATTACK_TARGET_Deactivate
//
// Clears the previous strafe target on every strafe element, re-aims each UFO at
// its primary target, and (optionally) posts the attack behaviour events and the
// per-UFO scale.  All callees are declared with the convention/arg-count their own
// body uses (see the per-line address comments).  Stub classes carry only the
// fields this routine reads or writes, named by role + offset.
// ---------------------------------------------------------------------------
namespace SP {

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// Intrusive-refcounted element of the local spawned-UFO vector.
struct AutoRefCount {
    void* mpObject;                            // 0x00
    void AddRef()  { if (mpObject) (*(void(**)(void*))(*(void***)mpObject))  (mpObject); }
    void Release() { if (mpObject) (*(void(**)(void*))(*(void***)mpObject + 1))(mpObject); }
};

// {begin,end,cap} vector of intrusive pointers (matches s00c5d640.cpp).
struct ObjPtrVec {
    AutoRefCount* begin;                       // 0x00
    AutoRefCount* end;                         // 0x04
    AutoRefCount* cap;                         // 0x08
    void DoInsertPtr(AutoRefCount* pos, const AutoRefCount& v);   // 0x00aea5d0
};

// The mission's 0x20-byte element (same record read/written by the helpers).
struct MissionElem {
    void** vtbl;                               // 0x00
    int    mId;                                // 0x04
    Vec3   mPos;                               // 0x08
    float  mF14;                               // 0x14
    float  mF18;                               // 0x18
    int    mTargetIndex;                       // 0x1c
};
struct ElemVec {                               // {begin,end}; read-only list here
    MissionElem* begin;                        // 0x00
    MissionElem* end;                          // 0x04
};

// cSPGameDataUFO: only the members this routine touches.
class cUFO {
public:
    uint8_t  mPad000[0x508];
    /* 0x508 */ float    mScaleTarget;          // 0x508  (FUN_00f924e0 target)
    uint8_t  mPad50c[0x188];
    /* 0x694 */ Vec3     mPosition;             // 0x694
    uint8_t  mPad6a0[0x10];
    /* 0x6b0 */ int      mSpawnIndex;           // 0x6b0
    uint8_t  mPad6b4[0x14];
    /* 0x6c8 */ uint8_t* mEventOwnerBase;       // 0x6c8  (owner of the +8 event list)
    uint8_t  mPad6cc[0x4c];
    /* 0x718 */ Vec3     mLocalExtentsMin;      // 0x718
    /* 0x724 */ Vec3     mLocalExtentsMax;      // 0x724
    /* 0x730 */ Quat     mSurfaceOrientation;   // 0x730

    void AddRef()  { (*(void(**)(void*))(*(void***)this))    (this); }   // vtable +0x00
    void Release() { (*(void(**)(void*))(*(void***)this + 1))(this); }   // vtable +0x04
    void ClearAttackBehaviorTarget(void* pTarget);   // 0x00c3b630
    void FUN_00c376d0(void* pArg);                   // 0x00c376d0
    void FUN_00c3dae0(const Vec3* pPos);             // 0x00c3dae0
    void FUN_00c3aa40(const Vec3* pVel, const Quat* pOrient);   // 0x00c3aa40
    void FUN_00c37130(int a);                        // 0x00c37130
};

cUFO* __cdecl CreateUFO(int defId, Vec3* pPos, void* pDef);        // 0x0102acb0
struct ModelHolder {
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);     // 0x00b7f190 ret 8
};
ModelHolder* __cdecl PlanetModel();                                // 0x00b3d350
Quat* __cdecl RotateByQuat(Quat* out, const Quat* q, const Quat* v);   // 0x0059aed0
void  __cdecl FUN_00bc97f0(int a, int b, float f, int c);          // 0x00bc97f0
void  __cdecl FUN_00f924e0(float* pTarget, float fValue);          // 0x00f924e0
void  __cdecl operator_delete(void* p);                            // 0x00f47380

extern const float gAngleScale;        // 0x01692594
extern const float gAxisX;             // 0x01692598
extern const float gAxisY;             // 0x0169259c
extern const float gAxisZ;             // 0x016925a0
extern const Quat  gAttackRotation;    // 0x016925a4
extern const float gFifteen;           // 0x014007f4 (15.0f)
extern const float gNegOne;            // 0x013eb1bc (-1.0f)
extern const float gTwoTenths;         // 0x013ec480 (0.2f)
extern const float gHalf;              // 0x01471064 (0.5f)
extern const float gFloatMax;          // 0x0146f65c (FLT_MAX)
extern const Vec3  gDefaultPos;        // 0x01691fc8 (usually all-zero)

static inline Quat* BuildOrientation(Quat* out, const Vec3* pos)
{
    return PlanetModel()->BuildSurfaceOrientation(out, pos);
}

// @ 0x00c5d140
void __cdecl FUN_00c5d140(void* pGame, ElemVec* pList, int nAttackSet, void* pDef,
                           Vec3 pos, int bPostEvents, int bFlag)
{
    ObjPtrVec spawnVec = { 0, 0, 0 };
    int   nSpawnCount = 0;         // esp+0x1c
    int   nPrevTarget = -1;        // esp+0x20
    char  bPostedDrift = 0;        // esp+0x13

    (void)pGame; (void)nAttackSet;

    const int nCount = (int)((char*)pList->end - (char*)pList->begin) >> 5;

    for (int i = 0; i < nCount; ++i) {
        MissionElem* e = (MissionElem*)((char*)pList->begin + (i << 5));
        cUFO* ufo = CreateUFO(e->mId, &pos, pDef);
        ufo->FUN_00c376d0(pDef);

        if (e->mId == 2) {                     // strafe-attack element
            int tgt = e->mTargetIndex;
            if (tgt == -1)
                goto orientation;
            if (nPrevTarget != tgt)
                nSpawnCount = 0;
            if (tgt >= (int)(spawnVec.end - spawnVec.begin))
                goto orientation;
            nPrevTarget = tgt;
            ufo->ClearAttackBehaviorTarget(spawnVec.begin[tgt].mpObject);
            ufo->mSpawnIndex = nSpawnCount;

            float ang = ((float)nSpawnCount * gAngleScale) * gTwoTenths * gHalf;
            float s = sinf(ang);
            float c = cosf(ang);
            Vec3 axis;
            axis.x = s * gAxisX;
            axis.y = s * gAxisY;
            axis.z = s * gAxisZ;
            Quat vq;
            vq.x = axis.x; vq.y = axis.y; vq.z = axis.z; vq.w = c;
            Quat rotated;
            RotateByQuat(&rotated, &gAttackRotation, &vq);
            ufo->mPosition.x = rotated.x * gFifteen;
            ufo->mPosition.y = rotated.y * gFifteen;
            ufo->mPosition.z = rotated.z * gFifteen;
            ++nSpawnCount;

            cUFO* pTarget = (cUFO*)spawnVec.begin[e->mTargetIndex].mpObject;
            ufo->FUN_00c3dae0(&pTarget->mLocalExtentsMin);
            ufo->mSurfaceOrientation =
                *BuildOrientation(&ufo->mSurfaceOrientation, &pTarget->mLocalExtentsMin);
        }
        else if (e->mId == 4) {                // spawn-a-UFO element
            AutoRefCount ref;
            ref.mpObject = ufo;
            if (ufo)
                ufo->AddRef();
            if (spawnVec.end < spawnVec.cap) {
                AutoRefCount* slot = spawnVec.end;
                spawnVec.end = slot + 1;
                if (slot) {
                    *slot = ref;
                    if (ufo)
                        ufo->AddRef();
                }
            }
            else {
                spawnVec.DoInsertPtr(spawnVec.end, ref);
            }
            if (ref.mpObject)
                ref.Release();
        }

    orientation:
        if (pos.x == gDefaultPos.x && pos.y == gDefaultPos.y && pos.z == gDefaultPos.z) {
            if (e->mPos.x == gDefaultPos.x && e->mPos.y == gDefaultPos.y &&
                e->mPos.z == gDefaultPos.z) {
                if (!bFlag) {
                    float ex = ufo->mLocalExtentsMin.x;
                    float ey = ufo->mLocalExtentsMin.y;
                    float ez = ufo->mLocalExtentsMin.z;
                    float inv = 1.0f / sqrtf((ex * ex + ez * ez) + ey * ey + 1e-8f);
                    Vec3 v;
                    v.x = (ey * inv) * 1000.0f;
                    v.y = (ez * inv) * 1000.0f;
                    v.z = (ex * inv) * 1000.0f;
                    ufo->FUN_00c3aa40(&v, &ufo->mSurfaceOrientation);
                }
            }
            else {
                ufo->FUN_00c3dae0(&e->mPos);
                ufo->mSurfaceOrientation = *BuildOrientation(&ufo->mSurfaceOrientation, &e->mPos);
            }
        }
        else {
            ufo->FUN_00c3dae0(&pos);
            ufo->mSurfaceOrientation = *BuildOrientation(&ufo->mSurfaceOrientation, &pos);
        }

        if (bPostEvents) {
            FUN_00bc97f0(8, 0, gFloatMax, 0);
            FUN_00bc97f0(0x10, 0, gFloatMax, 0);
            ufo->FUN_00c37130(0);
            if (!bPostedDrift) {
                FUN_00bc97f0(0x20, 0, gFloatMax, 0);
                bPostedDrift = 1;
            }
        }

        if (e->mF14 != gNegOne)
            FUN_00f924e0(&ufo->mScaleTarget, e->mF14);
    }

    // release the local object vector
    for (AutoRefCount* it = spawnVec.begin; it < spawnVec.end; ++it) {
        if (it->mpObject)
            it->Release();
    }
    if (spawnVec.begin && spawnVec.begin[-1].mpObject == 0)
        operator_delete(spawnVec.begin);
}

}  // namespace SP
