// Slice s00c278e0: creature-citizen action-circle map, tool selection and the
// small geometry/range helpers that live next to it (0xc278e0-0xc289a4).
//
// Reconstructed from the retail disassembly of SporeApp.exe (image base
// 0x400000).  The retail code uses scalar SSE arithmetic (movss/addss/mulss/
// subss/divss) for its float work, which cl15 never emits for plain float math
// (it always uses x87), so only the float-free functions can be byte-exact.
//
// Callees that are __thiscall are declared as members of a placeholder class
// (MSVC 2008 rejects __thiscall on free functions) and reached through the
// object pointer.
#include <math.h>
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;

#define nullptr 0

struct Vec3 { f32 x, y, z; };

// ---------------------------------------------------------------------------
// Raw dispatch helper for interface slots that are too high to spell out as
// virtual members of the reconstructed classes.
// ---------------------------------------------------------------------------
class cVTable { public: void* mpSlots[0x100]; };

class cDispatchObject {
public:
    void* Call(i32 nSlot) {
        return ((void* (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    i32 CallInt(i32 nSlot) {
        return ((i32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    f32 CallFloat(i32 nSlot) {
        return ((f32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    void CallVoid(i32 nSlot) {
        ((void (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    void CallVoidArg(i32 nSlot, i32 nArg) {
        ((void (__thiscall*)(cDispatchObject*, i32))mpTable->mpSlots[nSlot >> 2])(this, nArg);
    }
    void* CallArg(i32 nSlot, void* pArg) {
        return ((void* (__thiscall*)(cDispatchObject*, void*))mpTable->mpSlots[nSlot >> 2])(this, pArg);
    }
    cVTable* mpTable;                           // +0x000
};

// Reference counted interfaces: slot 0 is add, slot 4 is release.
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};

class cCommunity {
public:
    void* GetLeader();                          // 0x00c00650
};

// ---------------------------------------------------------------------------
// Containers.
// ---------------------------------------------------------------------------
class cStarRecordVector {
public:
    void Destroy();                             // 0x00ae6970
    cStarRecordVector& CopyFrom(cStarRecordVector* pOther);   // 0x00c277f0

    void* mpBegin;                              // +0x000
    void* mpEnd;                                // +0x004
    void* mpCapacity;                           // +0x008
};

// A vector of ref-counted pointers; only its three pointers matter here.
class cRefVector {
public:
    void Resize(i32 nCount, void* pSrc);        // 0x00b93c60
    void Erase(void* pBegin, void* pEnd);       // 0x00e25bd0

    void* mpBegin;                              // +0x000
    void* mpEnd;                                // +0x004
    void* mpCapacity;                           // +0x008
};

void __cdecl CopyRefRange(void** ppCursor, void** pBegin, void** pEnd, void* pDest,
                          void* pExtra);        // 0x00dc6730

// ---------------------------------------------------------------------------
// cActionCircle: the 0x68 byte record stored in the citizen's action map.
// ---------------------------------------------------------------------------
class cActionCircle {
public:
    cActionCircle* FUN_00afba10();              // 0x00afba10 (construct)
    void FUN_00afbad0();                        // 0x00afbad0 (destroy)
    cActionCircle* CopyFrom(cActionCircle* pSrc);   // 0x00c278e0

    f32 m00, m04, m08, m0c, m10, m14, m18, m1c, m20;   // +0x00
    i32 m24;                                    // +0x24
    u8  m28;                                    // +0x28
    u8  mPad29[3];                              // +0x29
    f32 m2c, m30, m34, m38;                     // +0x2c
    cRefVector mVec;                            // +0x3c
    void* m48;                                  // +0x48
    u8  mPad4c[4];                              // +0x4c
    cStarRecordVector mStars;                   // +0x50
    u8 mPad5c[0x0c];                            // +0x5c
};

// ---------------------------------------------------------------------------
// The citizen's action map (buckets + count) and its node iterator.
// ---------------------------------------------------------------------------
struct cMapIterator { void* mpNode; void* mpEnd; u32 mPad; };

// One map entry: a 4-byte key followed by the 0x64-byte action circle.
struct cMapRecord { u32 mKey; cActionCircle mCircle; };

class cActionCircleMap {
public:
    void Find(cMapIterator* pOut, u32* pKey);               // 0x00ac9d30
    void Insert(cMapIterator* pIt, cMapRecord* pRec, bool flag);  // 0x00c27a80
    cActionCircle* FindOrAdd(i32* pKey);                    // 0x00c27d20

    u8    mPad00[4];                            // +0x00
    void** mpBuckets;                           // +0x04
    u32   mnCount;                              // +0x08
    u8    mPad0c[4];                            // +0x0c
    u8    mPad10[0x10];                         // +0x10
};

// The object that owns the map at +0x394 (reached through citizen +0x10c).
class cActionMapOwner {
public:
    i32 FindOrAddKey(i32 nKey);                 // 0x00c27db0

    u8 mPad000[0x394];                          // +0x000
    cActionCircleMap mMap;                      // +0x394
};

// ---------------------------------------------------------------------------
// The creature / citizen.
// ---------------------------------------------------------------------------
// The embedded locomotion body at self+0xc0 (vtable +0x2c -> Vec3*, +0x74 -> float).
class cBodyObject {
public:
    void* FUN_00c41ec0();                       // 0x00c41ec0 -> this+0x1f4
};

class cCreatureBase {
public:
    void FUN_00c1fe80();                        // 0x00c1fe80
    void FUN_00c1c8e0();                        // 0x00c1c8e0
    i32  FUN_00c0c2f0();                        // 0x00c0c2f0
    bool Flag388();                             // 0x00c0c0e0
    void* FUN_00c0b750();                       // 0x00c0b750
    void* FUN_00c04590();                       // 0x00c04590
    void* GetTribe();                           // 0x00c22f50
    void* FUN_00c41ec0();                       // 0x00c41ec0
    void funcC4h();                             // 0x00c27b70
    void MoveToPointAndFacingAtSpeed(i32 nMode, float* pPos, float* pDir, f32 s0, f32 s1); // 0x00c1c5c0
    void MoveToPointAtSpeedPathPlan(void* pPlan, i32* pTarget, f32 s0, f32 s1, i32 nZero); // 0x00c1c310

    u8   mPad000[0x110];                        // +0x000
    u32  m110;                                  // +0x110
    u8   mPad114[0x23];                         // +0x114
    u8   m137;                                  // +0x137
    u8   mPad138[0x118];                        // +0x138
    Vec3 m250;                                  // +0x250
    u8   m25c;                                  // +0x25c
    u8   mPad25d[0xd3];                         // +0x25d
    u32  m330;                                  // +0x330
    u8   mPad334[0xcdc];                        // +0x334
    cRefCounted* mpOwnerCity;                   // +0x1010
    cRefCounted* mpOwnerTribe;                  // +0x1014
    cRefVector   mVec1018;                      // +0x1018
    i32  mnSpecializedTool;                     // +0x1024
    cRefCounted* mpHitSphere;                   // +0x1028
    i32  mnToolEffectIndex;                     // +0x102c
    cRefCounted* mpNoun;                        // +0x1030
};

// cSPCreatureCitizen, used by the tool-selection routine.
class cCreatureCitizen {
public:
    void SetSpecializedTool(i32 nTool);         // 0x00c279a0
    void* FUN_00c27dd0(void* pObj);             // 0x00c27dd0
    void MoveToPointAndFacingAtSpeed(i32 nMode, float* pPos, float* pDir, f32 s0, f32 s1); // 0x00c1c5c0

    u8   mPad000[0xe8c];                        // +0x000
    i32  mnE8c;                                 // +0x0e8c
    i32  mnE90;                                 // +0x0e90
    f32  mfE94;                                 // +0x0e94
    void* mpE98;                                // +0x0e98
    void* mpE9c;                                // +0x0e9c
    u8   mPadEA0[0x170];                        // +0x0ea0
    cRefCounted* mpOwnerCity;                   // +0x1010
    cRefCounted* mpOwnerTribe;                  // +0x1014
    u8   mPad1018[0x14];                        // +0x1018
    i32  mnToolEffectIndex;                     // +0x102c
};

// Simulator::cGameData, used by RemoveOwner.
class cEditorList {
public:
    void* First();                              // 0x00cee330
    u8 mPad[0x24];
};

class cGameData {
public:
    void RemoveOwner();                         // 0x00c27be0
    void FUN_00c1c8e0();                        // 0x00c1c8e0

    u8   mPad000[0x34];                         // +0x000
    cEditorList mEditor;                        // +0x034
    u8   mField58[0xfb8];                       // +0x058
    cRefCounted* mpOwnerCity;                   // +0x1010
    cRefCounted* mpOwnerTribe;                  // +0x1014
    cRefVector   mVec1018;                      // +0x1018
    u8   mPad1024[0x0c];                        // +0x1024
    cRefCounted* mpNoun;                        // +0x1030
};

// ---------------------------------------------------------------------------
// External services and callees.
// ---------------------------------------------------------------------------
class cPlanetModel {
public:
    void  FUN_00b7e430(void* pOut, i32 nFlag);            // 0x00b7e430
    void* FUN_00b816f0(void* pOut, void* pIn);            // 0x00b816f0
    void  FUN_00b7f250(void* pOut, void* pPos, void* pDir); // 0x00b7f250
};
cPlanetModel* __cdecl PlanetModel();            // 0x00b3d350

class cGameNounManager {
public:
    void RemoveNoun(void* pNoun);               // 0x00b225d0
};

class cGroundEditorRes {
public:
    void* getContainer();                       // 0x00ac79d0
    void  FUN_00ac79e0(void* pObj, void* pField);   // 0x00ac79e0
    void  FUN_00ac7de0(void* pObj, void* pContainer); // 0x00ac7de0
};

class cTribeStrategyObject {
public:
    void FUN_00cca880(void* pCitizen, i32 nTool);   // 0x00cca880
};

class cTribe {
public:
    void FUN_00c8f540(Vec3* pOut, f32 fA, i32 nB, void* pC, void* pD, void* pE);  // 0x00c8f540
};

// A creature list returned by cCreatureBase::FUN_00c04590.
class cCreatureList {
public:
    u8 mPad40[0x40];                            // +0x00
    cCreatureBase** mpBegin;                    // +0x40
    cCreatureBase** mpEnd;                      // +0x44
};

// The per-creature manager at +0xb4c whose +8 subobject gets FUN_00bc97f0.
class cOtherMgr {
public:
    void FUN_00bc97f0(u32 a, u32 b, f32 c, void* d);   // 0x00bc97f0
};

void* __cdecl FUN_00b3d310();                   // 0x00b3d310
void* __cdecl FUN_00b3d2b0();                   // 0x00b3d2b0
void* __cdecl FUN_00b3d260();                   // 0x00b3d260
void* __cdecl FUN_00b3d300();                   // 0x00b3d300
void* __cdecl GetCurrentGameMode();             // 0x00b5b800
void* __cdecl cTribeModeStrategy_Instance();    // 0x00cd40b0
void* __cdecl FUN_00b532b0(void* pKey);         // 0x00b532b0
void* __cdecl FUN_00ac80d0(void* pObj, void* pType);  // 0x00ac80d0
void* __cdecl FUN_00c423c0(void* pSelf);        // 0x00c423c0
void  __cdecl FUN_00c0d3a0(void* pSelf);        // 0x00c0d3a0
void* __cdecl FUN_00c986d0(void* pContainer, i32 nKey, i32* pOut, void* pSelf);  // 0x00c986d0

extern Vec3 g_168dd78;                          // 0x0168dd78
extern char DAT_018eb45e;                       // 0x018eb45e
extern char DAT_018eb4b7;                       // 0x018eb4b7
extern char DAT_01654c04;                       // 0x01654c04
extern char DAT_01654c05;                       // 0x01654c05
extern char DAT_01654c10;                       // 0x01654c10

// ===========================================================================
// 0x00c278e0  cActionCircle::CopyFrom
// ===========================================================================
// @ 0x00c278e0
cActionCircle* cActionCircle::CopyFrom(cActionCircle* pSrc)
{
    m00 = pSrc->m00;
    m04 = pSrc->m04;
    m08 = pSrc->m08;
    m0c = pSrc->m0c;
    m10 = pSrc->m10;
    m14 = pSrc->m14;
    m18 = pSrc->m18;
    m1c = pSrc->m1c;
    m20 = pSrc->m20;
    m24 = pSrc->m24;
    m28 = pSrc->m28;
    m2c = pSrc->m2c;
    m30 = pSrc->m30;
    m34 = pSrc->m34;
    m38 = pSrc->m38;

    i32 nCount = (i32)(((u8*)pSrc->mVec.mpEnd - (u8*)pSrc->mVec.mpBegin) >> 2);
    mVec.Resize(nCount, &pSrc->m48);

    void* pCursor = mVec.mpBegin;
    CopyRefRange(&pCursor, (void**)pSrc->mVec.mpBegin, (void**)pSrc->mVec.mpEnd,
                 mVec.mpBegin, pSrc);
    mVec.mpEnd = pCursor;

    mStars.CopyFrom(&pSrc->mStars);
    return this;
}

// ===========================================================================
// 0x00c279a0  cCreatureCitizen::SetSpecializedTool
// ===========================================================================
// @ 0x00c279a0
void cCreatureCitizen::SetSpecializedTool(i32 nTool)
{
    i32 nOld = mnToolEffectIndex;
    mnToolEffectIndex = nTool;

    if (nTool == 0) {
        cCommunity* pOwner = (cCommunity*)mpOwnerCity;
        if (pOwner == nullptr)
            pOwner = (cCommunity*)mpOwnerTribe;
        if (pOwner != nullptr) {
            if (pOwner->GetLeader() == this)
                mnToolEffectIndex = 0xb;
        }
    }

    if (nOld != mnToolEffectIndex) {
        mnE8c = -1;
        mnE90 = -1;
        mfE94 = 0.0f;

        u8* pBegin = (u8*)mpE98;
        u8* pEnd   = (u8*)mpE9c;
        memcpy(pBegin, pEnd, 0);
        mpE9c = (u8*)mpE9c + (((i32)(pEnd - pBegin) >> 2) * -4);
    }

    ((cDispatchObject*)this)->CallVoidArg(0xac, 1);

    void* pStrategy = cTribeModeStrategy_Instance();
    if (((cDispatchObject*)pStrategy)->CallInt(0x6c) != 0) {
        void* pStrategy2 = cTribeModeStrategy_Instance();
        void* pObj = ((cDispatchObject*)pStrategy2)->Call(0x6c);
        ((cTribeStrategyObject*)pObj)->FUN_00cca880(this, nOld);
    }
}

// ===========================================================================
// 0x00c27b70  cCreatureBase::funcC4h
// ===========================================================================
// @ 0x00c27b70
void cCreatureBase::funcC4h()
{
    FUN_00c1fe80();

    if (mpOwnerCity != nullptr) {
        cRefCounted* pCity = mpOwnerCity;
        mpOwnerCity = nullptr;
        pCity->Release();
    }
    if (mpOwnerTribe != nullptr) {
        cRefCounted* pTribe = mpOwnerTribe;
        mpOwnerTribe = nullptr;
        pTribe->Release();
    }

    mVec1018.Erase(mVec1018.mpBegin, mVec1018.mpEnd);
    mnToolEffectIndex = 0;
}

// ===========================================================================
// 0x00c27be0  cGameData::RemoveOwner
// ===========================================================================
// @ 0x00c27be0
void cGameData::RemoveOwner()
{
    if (mpNoun != nullptr)
        ((cGameNounManager*)FUN_00b3d300())->RemoveNoun(mpNoun);

    if (mpNoun != nullptr) {
        cRefCounted* pNoun = mpNoun;
        mpNoun = nullptr;
        pNoun->Release();
    }

    if (mpOwnerTribe != nullptr)
        FUN_00c0d3a0(this);

    void* pObj = mEditor.First();
    if (pObj != nullptr) {
        void* pContainer = ((cGroundEditorRes*)FUN_00b3d2b0())->getContainer();
        if (pContainer != nullptr) {
            void* pContainer2 = ((cGroundEditorRes*)FUN_00b3d2b0())->getContainer();
            ((cGroundEditorRes*)FUN_00b3d2b0())->FUN_00ac7de0(pObj, pContainer2);
        }
        else {
            ((cGroundEditorRes*)FUN_00b3d2b0())->FUN_00ac79e0(pObj, &mEditor);
        }
    }

    ((cDispatchObject*)FUN_00b3d260())->CallArg(0x3c, mField58);
    FUN_00c1c8e0();

    mVec1018.Erase(mVec1018.mpBegin, mVec1018.mpEnd);

    if (mpOwnerCity != nullptr) {
        cRefCounted* pCity = mpOwnerCity;
        mpOwnerCity = nullptr;
        pCity->Release();
    }
    if (mpOwnerTribe != nullptr) {
        cRefCounted* pTribe = mpOwnerTribe;
        mpOwnerTribe = nullptr;
        pTribe->Release();
    }
}

// ===========================================================================
// 0x00c27d20  cActionCircleMap::FindOrAdd
// ===========================================================================
// @ 0x00c27d20
cActionCircle* cActionCircleMap::FindOrAdd(i32* pKey)
{
    cMapIterator it;
    Find(&it, (u32*)pKey);

    if (it.mpNode == mpBuckets[mnCount]) {
        cActionCircle temp;
        cMapRecord rec;
        cActionCircle* p = temp.FUN_00afba10();
        rec.mKey = (u32)*pKey;
        rec.mCircle.CopyFrom(p);
        Insert(&it, &rec, false);
        rec.mCircle.FUN_00afbad0();
        temp.FUN_00afbad0();
    }

    return (cActionCircle*)((u8*)it.mpNode + 4);
}

// ===========================================================================
// 0x00c27db0  cActionMapOwner::FindOrAddKey
// ===========================================================================
// @ 0x00c27db0
i32 cActionMapOwner::FindOrAddKey(i32 nKey)
{
    i32 k = nKey;
    return (i32)mMap.FindOrAdd(&k);
}

// ===========================================================================
// 0x00c27dd0  cCreatureCitizen::FUN_00c27dd0
// ===========================================================================
// @ 0x00c27dd0
void* cCreatureCitizen::FUN_00c27dd0(void* pObj)
{
    i32 nIndex = -1;
    float* pSrc = (float*)FUN_00c986d0(*(void**)((u8*)pObj + 0x10c), 0xd, &nIndex, this);
    if (nIndex < 0)
        return (void*)nIndex;

    i32 nKey = 0xd;
    cActionCircle* pRec = ((cActionMapOwner*)(*(void**)((u8*)pObj + 0x10c)))->mMap.FindOrAdd(&nKey);

    float fScale = ((cDispatchObject*)((u8*)this + 0xc0))->CallFloat(0x74);
    f32 cx = *(f32*)((u8*)pRec + 0x14);
    f32 cy = *(f32*)((u8*)pRec + 0x18);
    f32 cz = *(f32*)((u8*)pRec + 0x1c);
    f32 dx = pSrc[0] - cx;
    f32 dy = pSrc[1] - cy;
    f32 dz = pSrc[2] - cz;
    f32 fInv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz) + 1e-08f);

    f32 fRadius = (*(f32*)((u8*)pRec + 0xc) + fScale) + 0.4f;
    f32 px = (fInv * dx) * fRadius + cx;
    f32 py = (fInv * dy) * fRadius + cy;
    f32 pz = (fInv * dz) * fRadius + cz;

    if (((pz - cz) * (pz - cz) + (px - cx) * (px - cx)) + (py - cy) * (py - cy) <
        (dz * dz + dy * dy) + dx * dx) {
        px = pSrc[0];
        py = pSrc[1];
        pz = pSrc[2];
    }

    f32 fx = -(fInv * dx);
    f32 fy = -(fInv * dy);
    f32 fz = -(fInv * dz);

    MoveToPointAndFacingAtSpeed(2, &px, &fx, 0.4f, 0.6f);
    return (void*)nIndex;
}

// ===========================================================================
// 0x00c27ff0  cActionCircle predicate (byte flag & 1)
// ===========================================================================
// @ 0x00c27ff0
u8 __cdecl FUN_00c27ff0(cActionCircle* pCircle)
{
    return *(u8*)((u8*)pCircle + 0x38) & 1;
}

// ===========================================================================
// 0x00c28000  copy range while a predicate is false
// ===========================================================================
// @ 0x00c28000
struct cRecord3c { u32 m[0xf]; };

u8* __cdecl FUN_00c28000(u8* pBegin, u8* pEnd, u8* pOut,
                         bool (__cdecl* pPred)(u8*))
{
    while (pBegin != pEnd) {
        if (!pPred(pBegin)) {
            *(cRecord3c*)pOut = *(cRecord3c*)pBegin;
            pOut += 0x3c;
        }
        pBegin += 0x3c;
    }
    return pOut;
}

// ===========================================================================
// 0x00c28050  planet-surface projection / clearance helper
// ===========================================================================
// @ 0x00c28050
void __cdecl FUN_00c28050(float* p1, float* p2, char bUseModel, char bUseDir,
                          float* p5, float* p6, float* p7)
{
    if (bUseModel != 0) {
        PlanetModel()->FUN_00b7e430(p5, 1);

        f32 dx = p5[0] - p1[0];
        f32 dy = p5[1] - p1[1];
        f32 dz = p5[2] - p1[2];
        f32 d = (p2[1] * dy + p2[0] * dx) + p2[2] * dz;

        f32 x = p5[0] - p2[0] * d;
        f32 y = p5[1] - p2[1] * d;
        f32 z = p5[2] - p2[2] * d;
        p6[0] = x;
        p6[1] = y;
        p6[2] = z;

        x -= p1[0];
        y -= p1[1];
        z -= p1[2];
        *p7 = sqrtf(x * x + (y * y + z * z));
        return;
    }

    if (bUseDir != 0) {
        f32 dx = p5[0] - p1[0];
        f32 dy = p5[1] - p1[1];
        f32 dz = p5[2] - p1[2];
        f32 d = (p2[0] * dx + p2[1] * dy) + p2[2] * dz;

        f32 x = p5[0] - p2[0] * d;
        f32 y = p5[1] - p2[1] * d;
        f32 z = p5[2] - p2[2] * d;
        p6[0] = x;
        p6[1] = y;
        p6[2] = z;

        x -= p1[0];
        y -= p1[1];
        z -= p1[2];
        *p7 = sqrtf(x * x + (y * y + z * z));
        return;
    }

    Vec3 local;
    PlanetModel()->FUN_00b816f0(&local, p5);
    p6[0] = local.x;
    p6[1] = local.y;
    p6[2] = local.z;
}

// ===========================================================================
// 0x00c28290  citizen surface orientation helper
// ===========================================================================
// @ 0x00c28290
void __cdecl FUN_00c28290(cCreatureBase* self, void* p2, void* p3)
{
    Vec3 pos;
    float* pPos = (float*)((cDispatchObject*)((u8*)self + 0xc0))->Call(0x2c);
    pos.x = pPos[0];
    pos.y = pPos[1];
    pos.z = pPos[2];

    char b137 = (char)self->m137;
    bool bFlag = (self->m110 & 0x1000) == 0x1000;
    void* pElem = FUN_00b532b0((u8*)self + 0xc0);
    bool bTest = (b137 != 0 && pElem != nullptr && *(i32*)((u8*)pElem + 0xcc) == 3);

    f32 fInv = 1.0f / sqrtf(pos.x * pos.x + (pos.y * pos.y + pos.z * pos.z) + 1e-08f);
    Vec3 dir;
    dir.x = fInv * pos.x;
    dir.y = fInv * pos.y;
    dir.z = fInv * pos.z;

    if (!bFlag) {
        if (b137 == 0)
            return;
        void* pMgr = FUN_00b3d310();
        if (*(i32*)((u8*)pMgr + 0x20) != 0)
            return;
    }

    FUN_00c28050(&pos.x, &dir.x, bFlag, bTest, (float*)p2, (float*)p2, (float*)p3);
    if (self->m25c != 0)
        FUN_00c28050(&pos.x, &dir.x, bFlag, bTest, (float*)&self->m250, (float*)&self->m250,
                     (float*)p3);
}

// ===========================================================================
// 0x00c283d0  citizen "call others" / selection helper
// ===========================================================================
// @ 0x00c283d0
u8 __cdecl FUN_00c283d0(Vec3* pOut, cCreatureBase* self)
{
    u8 bResult = 0;
    void* pMode = GetCurrentGameMode();
    u32 nFlags = self->m330;
    bool bMode10 = (pMode == (void*)&DAT_01654c10);

    if ((nFlags & 0xb) == 0)
        return bResult;

    bResult = 1;
    void* pBody = (u8*)self + 0xc0;
    void* pField = ((cBodyObject*)pBody)->FUN_00c41ec0();
    float fLimit = *(float*)((u8*)pField + 0x6c);

    if ((nFlags & 2) != 0 && 2.0f < fLimit && !bMode10) {
        self->m330 = nFlags & 0xfffffffd;
        return 0;
    }
    if (30.0f < fLimit && !bMode10)
        return 0;

    pOut->x = g_168dd78.x;
    pOut->y = g_168dd78.y;
    pOut->z = g_168dd78.z;

    void* pClass = ((cDispatchObject*)self)->Call(0x20);
    if (pClass == (void*)&DAT_018eb45e) {
        if (self->FUN_00c0c2f0() != 2)
            return bResult;

        cCreatureBase* pCitizen = (cCreatureBase*)FUN_00ac80d0(self, (void*)&DAT_018eb45e);
        cCreatureList* pList = (cCreatureList*)pCitizen->FUN_00c04590();

        Vec3 v;
        float fDist;
        if ((nFlags & 0x10) == 0) {
            fDist = ((cDispatchObject*)pBody)->CallFloat(0x74);
            fDist = fDist + fDist;
            float* pPos = (float*)((cDispatchObject*)pBody)->Call(0x2c);
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
        }
        else {
            float* pPos = (float*)FUN_00c423c0(self);
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
            fDist = ((cDispatchObject*)((u8*)pCitizen + 0xc0))->CallFloat(0x74) +
                    *(float*)((u8*)pField + 0x20);
        }

        i32 nCount = (i32)(pList->mpEnd - pList->mpBegin);
        for (i32 i = 0; i < nCount; ++i) {
            cCreatureBase* pOther = pList->mpBegin[i];
            if (pOther == pCitizen)
                continue;
            float* pPos = (float*)((cDispatchObject*)((u8*)pOther + 0xc0))->Call(0x2c);
            float ox = pPos[0];
            float oy = pPos[1];
            float oz = pPos[2];
            float fOther = ((cDispatchObject*)((u8*)pOther + 0xc0))->CallFloat(0x74);
            float fSum = fOther + fDist;
            if ((v.z - oz) * (v.z - oz) + (v.y - oy) * (v.y - oy) +
                (v.x - ox) * (v.x - ox) < fSum * fSum)
                ((cOtherMgr*)((u8*)pOther + 0xb4c + 8))->FUN_00bc97f0(
                    (u32)0x2000000, 0, 5.0f, pCitizen);
        }
    }
    else if (pClass == (void*)&DAT_018eb4b7) {
        cCreatureBase* pCitizen = self;
        cTribe* pTribe = (cTribe*)pCitizen->GetTribe();
        if ((nFlags & 0x10) == 0) {
            float fDist = 2.0f * ((cDispatchObject*)((u8*)pCitizen + 0xc0))->CallFloat(0x74);
            float* pPos = (float*)((cDispatchObject*)((u8*)pCitizen + 0xc0))->Call(0x2c);
            Vec3 v;
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
            pTribe->FUN_00c8f540(&v, fDist, 0, (void*)0x2000000, (void*)0x40a00000, pCitizen);
        }
        else {
            float fDist = ((cDispatchObject*)((u8*)pCitizen + 0xc0))->CallFloat(0x74) +
                          *(float*)((u8*)pField + 0x20);
            float* pPos = (float*)FUN_00c423c0(pCitizen);
            Vec3 v;
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
            pTribe->FUN_00c8f540(&v, fDist, 0, (void*)0x2000000, (void*)0x40a00000, pCitizen);
        }
    }
    return bResult;
}

// ===========================================================================
// 0x00c28700  approach-speed clamp helper
// ===========================================================================
// @ 0x00c28700
void __cdecl FUN_00c28700(cCreatureBase* self, u32 nArg2, i32* pVec, u32 nArg4,
                          f32 fA, f32 fB, f32* pOut)
{
    if (*pVec != pVec[1])
        return;

    f32 fDiff = fA - fB;
    void* pMgr = FUN_00b3d310();
    if (*(char*)((u8*)pMgr + 0x31) != 0) {
        f32 fT = fDiff / *(f32*)((u8*)self + 0x10);
        if (*pOut > fT)
            *pOut = fT;
        return;
    }

    f32 fVal = ((cDispatchObject*)((u8*)self + 0x14))->CallFloat(0xd4);
    f32 fBase = *(f32*)((u8*)self + 0x10);
    f32 fCur = *pOut;
    f32 fNew;
    if (fBase * fBase <= (fDiff / fVal) * 2.0f) {
        f32 fTemp = fDiff - fCur * fBase;
        f32 fClamped = (fTemp < 0.0f) ? 0.0f : fTemp;
        if ((fClamped * fVal) * 2.0f < fCur * fCur)
            fNew = sqrtf((fVal * fDiff + fVal * fDiff) + (fBase * fVal) * (fBase * fVal)) -
                   fBase * fVal;
        else
            fNew = fCur;
    }
    else {
        fNew = fDiff / fBase;
    }

    if (fNew < 1.0f)
        fNew = 1.0f;
    if (fCur <= fNew)
        fNew = fCur;
    *pOut = fNew;
}

// ===========================================================================
// 0x00c28870  move-to-target with speed/path plan
// ===========================================================================
// @ 0x00c28870
u8 __cdecl FUN_00c28870(Vec3* pOut, cCreatureBase* self, float* pPos, i32* pVec)
{
    if (*pVec != pVec[1])
        return 1;

    bool bFlag = false;
    if (self->Flag388()) {
        void* pMode = GetCurrentGameMode();
        if (pMode == (void*)&DAT_01654c04)
            bFlag = true;
        else {
            pMode = GetCurrentGameMode();
            if (pMode == (void*)&DAT_01654c05)
                bFlag = true;
        }
    }

    f32 fA = (f32)pVec[8];
    f32 fB = (f32)pVec[0x18];
    f32 fRadius = (fA + fB) + 100.0f;

    if (!bFlag && (self->m330 & 4) == 0) {
        f32 dx = (f32)pVec[5] - pPos[0];
        f32 dy = (f32)pVec[6] - pPos[1];
        f32 dz = (f32)pVec[7] - pPos[2];
        if (fRadius * fRadius < (dz * dz + dx * dx) + dy * dy) {
            i32 nField = pVec[0x17];
            pOut->x = 0.0f;
            pOut->y = 0.0f;
            pOut->z = 0.0f;

            void* pPlan = self->FUN_00c0b750();
            self->MoveToPointAtSpeedPathPlan(pPlan, pVec + 5, fA, fB, 0);
            void* pField = ((cBodyObject*)((u8*)self + 0xc0))->FUN_00c41ec0();
            *(i32*)((u8*)pField + 0x5c) = nField;
            *(i32*)((u8*)pField + 0x50) = pVec[0x14];
            *(i32*)((u8*)pField + 0x54) = pVec[0x15];
            *(i32*)((u8*)pField + 0x58) = pVec[0x16];
            return 0;
        }
    }
    return 1;
}
