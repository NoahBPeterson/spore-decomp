// Slice s00c37a90 -- SP::cSPGameDataUFO / UFO motion helpers in SPGameDataUFO.obj.
// Retail layout differs from the 2008 PDB: cGameData @0, cLocomotiveObject @0x34,
// cCombatant @0x508, cInteractionTarget @0x5d0 (offsets read off the disassembly).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned __int64 U64;

struct Vector3 {
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    float x, y, z;
};
struct Quaternion {
    float x, y, z, w;
};

// ------------------------------------------------------------------ vtable shapes
// Base classes carry only placeholder virtuals; a derived interface adds the slots we call.

struct IGameData {
    virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
    virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
    virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
    virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
    virtual void g16(); virtual void g17(); virtual void g18();
    virtual U32  GetOwnerId();                       // slot 19, +0x4c
};

struct ILocomotive {
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
    virtual void l04(); virtual void l05(); virtual void l06(); virtual void l07();
    virtual void l08(); virtual void l09(); virtual void l10(); virtual void l11();
    virtual void l12(); virtual void l13();
    virtual void SetPosition(const Vector3&);        // slot 14, +0x38
    virtual void SetOrientation(const Quaternion&);  // slot 15, +0x3c
    virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
    virtual void l20(); virtual void l21(); virtual void l22(); virtual void l23();
    virtual void l24(); virtual void l25(); virtual void l26(); virtual void l27();
    virtual void l28(); virtual void l29(); virtual void l30(); virtual void l31();
    virtual void l32(); virtual void l33(); virtual void l34(); virtual void l35();
    virtual void l36();
    virtual void SetOffset47(const Vector3&);        // slot 37, +0x94
};

struct ICombatant {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21();
    virtual float GetWeaponPositionF();              // slot 22, +0x58
};

// space app mode: the transitions ExitToSpace drives
struct cAppModeSpace {
    void __thiscall TransitionFromPlanetToSolar(U32 id, U32 b);   // 0x00fdd390
    void __thiscall TransitionFromGalaxyToSolar();                // 0x00fdd5a0
    void __thiscall TransitionFromCivToSpace(U32 id, U32 b);      // 0x00fdba50
    void __thiscall FUN_00fde3e0(U32 a);                          // 0x00fde3e0
    void __thiscall FUN_00fe0e10();                               // 0x00fe0e10
};

// behavior-tree data object: only the vptr and the flag word are used here.
struct cBehaviorTreeData {
    U32    mInt000;                                  // +0x000
    U32    pad004[0x1cc / 4];                        // +0x004
    U32    mMotion1d0[0x78 / 4];                     // +0x1d0
    U32    pad248[0x3a0 / 4];                        // +0x248
    U32    mInt5e8;                                  // +0x5e8
    U32    pad5ec[0x10 / 4];                         // +0x5ec
    U32    mFlags5fc;                                // +0x5fc
};

// timer used by the UFO (cSPTimer layout not needed: only its methods are called)
struct cSPTimer {
    U32 md000[0x20 / 4];                             // +0x000 (0x20 bytes)
    void __thiscall Restart();                       // 0x0bc3130
    void __thiscall Stop();                          // 0x0bc3110
    bool __thiscall IsRunning();                     // 0x0feba90
};

struct cKey {
    U32 mId;        // +0x00
    U32 mType;      // +0x04
    U32 mInstance;  // +0x08
};

struct cListNode {
    cListNode* mpNext;   // +0x00
    cListNode* mpPrev;   // +0x04
};

struct cStarRecord;
struct cPlanet;
struct cEmpire;

// the planet tuning singleton at 0x0168df68: only the floats this slice reads.
struct cPlanetTuning {
    U32   pad000[0x10 / 4];
    float mf010;            // +0x010
    U32   pad014[0x14 / 4];
    float mf028;            // +0x028
    float mf02c;            // +0x02c
    U32   pad030[0x38 / 4];
    float mf068;            // +0x068
    float mf06c;            // +0x06c
    float mf070;            // +0x070
    float mf074;            // +0x074
    float mf078;            // +0x078
    U32   pad07c[0x10 / 4];
    float mf08c;            // +0x08c
    float mf090;            // +0x090
    U32   pad094[0x20 / 4];
    float mf0b4;            // +0x0b4
    float mf0b8;            // +0x0b8
    U32   pad0bc[8 / 4];
    float mf0c4;            // +0x0c4
    U32   pad0c8[0x20 / 4];
    float mf0e8;            // +0x0e8
};

// ------------------------------------------------------------------ the UFO
struct cSPGameDataUFO {
    bool Read(void* pStream);                        // 0x0c37a90
    bool WarpToDestination();                        // 0x0c37cc0
    void PopToDestination();                         // 0x0c37e60
    void ApplyVelocity(const Vector3& dir, float scale); // 0x0c37f70
    void SetOffset(const Vector3& offset);           // 0x0c381e0
    bool HasPendingCollisions();                     // 0x0c38260
    bool CanEnterPlanetContext();                    // 0x0c38270
    void ExitToSpace();                              // 0x0c382e0
    void DeactivateBehaviorTree();                   // 0x0c38510
    void SetupAI();                                  // 0x0c385d0
    bool TickUFOBehaviorTree(float dt, double time);// 0x0c38740
    float GetStandardSpeedForAltitude();             // 0x0c38840
    float GetMaxSpeedForAltitude();                  // 0x0c38900
    bool TestFlag(U32 flag);                         // 0x0c38990
    void SetFlag(U32 flag, bool value);              // 0x0c389c0

    U32    mpVftbl00;                                // +0x000
    U32    pad004[0x30 / 4];                         // +0x004
    U32    mpVftbl34;                                // +0x034 cLocomotiveObject vtable
    U32    pad038[0x1ec / 4];                        // +0x038
    U32    mInt224;                                  // +0x224
    U32    pad228[0x2e0 / 4];                        // +0x228
    U32    mpVftbl508;                               // +0x508 cCombatant vtable
    U32    pad50c[0x30 / 4];                         // +0x50c
    U32    mInt53c;                                  // +0x53c
    float  mf540;                                    // +0x540
    U32    pad544[0xa8 / 4];                         // +0x544
    float  mf5ec;                                    // +0x5ec
    U32    pad5f0[0x1c / 4];                         // +0x5f0
    float  mf60c;                                    // +0x60c
    float  mf610;                                    // +0x610
    float  mf614;                                    // +0x614
    float  mf618;                                    // +0x618
    float  mf61c;                                    // +0x61c
    float  mf620;                                    // +0x620
    U8     mb624;                                    // +0x624
    U8     pad625[3];                                // +0x625
    U32    pad628[0x20 / 4];                         // +0x628
    cSPTimer mMovementTimer;                         // +0x648
    U32    pad668[0x4c / 4];                         // +0x668
    float  mf6b4;                                    // +0x6b4
    float  mf6b8;                                    // +0x6b8
    U32    pad6bc[0xc / 4];                          // +0x6bc
    cBehaviorTreeData* mpBehaviorTreeData;           // +0x6c8
    U32    pad6cc[0x48 / 4];                         // +0x6cc
    U32    mUFOType;                                 // +0x714
    Vector3 mNextPosition;                           // +0x718
    Vector3 mNextVelocity;                           // +0x724
    Quaternion mNextOrientation;                     // +0x730
    Vector3 mOffsetFromPosition;                     // +0x740
    U8     mbWarping;                                // +0x74c
    U8     pad74d[3];                                // +0x74d
    Vector3 mDestination;                            // +0x750
    U32    pad75c[2];                                // +0x75c
    U32    mInt764;                                  // +0x764
    float  mf768;                                    // +0x768
    U32    pad76c;                                   // +0x76c
    cListNode mCollisions;                           // +0x770
    U32    pad778[8 / 4];                            // +0x778
    cKey   mDesiredModelKey;                         // +0x780
    U8     pad78c[0x24];                             // +0x78c
    U32    mInt7b0;                                  // +0x7b0
    U32    pad7b4[0x28 / 4];                         // +0x7b4
    U32    mFlags7dc;                                // +0x7dc
    U32    pad7e0[0x10 / 4];                         // +0x7e0
    U32    mp7f0;                                    // +0x7f0
    float  mf7f4;                                    // +0x7f4
    float  mf7f8;                                    // +0x7f8
    U32    pad7fc[2];                                // +0x7fc
    U32    mp804;                                    // +0x804
    U32    mp808;                                    // +0x808
    U32    mp80c;                                    // +0x80c
    U32    mp810;                                    // +0x810
    U32    mp814;                                    // +0x814
};

// object with two Vector3s at +0x54/+0x60 (0x0c37dc0's receiver)
struct cMotionFrame {
    U32    pad000[0x54 / 4];     // +0x000
    Vector3 mFrom;               // +0x054
    Vector3 mTo;                 // +0x060
};

// ------------------------------------------------------------------ externals
extern cPlanetTuning* g_pPlanetTuning;      // 0x0168df68
extern U32            g_pBannerListA;       // 0x0168df6c
extern U32            g_pBannerListB;       // 0x0168df70
extern Vector3        g_vZero;              // 0x0168df74, zero vector
extern float          g_f13f9428;           // 0x013f9428, 0.001
extern U32            g_aui146bb58[2];      // 0x0146bb58, UFO message ids
extern U8             g_b168e564;           // 0x0168e564, setup guard
extern U32            g_159fd50;            // 0x0159fd50, behavior-tree blackboard
extern U8             g_1573290;            // 0x01573290, serializer context

extern const char g_szSimulator[];          // 0x013f09b4 "Simulator"
extern const char g_szBehaviorTree[];       // 0x0146a6f4 "Simulator/cBehaviorTreeData"

void* __cdecl operator_new(U32 size, const char* pName, int a, int b, void* pAlloc, U32 line); // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                          // 0x00f47380

// EA::IO
struct cIOStream;
void __cdecl EA_ReadInt32(cIOStream* pStream, void* pDst, int nCount, int a);  // 0x0093a780
void __cdecl EA_ReadBool(cIOStream* pStream, bool* pDst);                      // 0x0093ac80

// stream interfaces: the argument object exposes a data stream via two virtual hops
struct IObjGetStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual cIOStream* GetStream();     // slot 6, +0x18
};
struct IStreamSource {
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3();
    virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7();
    virtual IObjGetStream* GetSource(); // slot 8, +0x20
};
struct IObjectStream : IStreamSource {};

// serializers / managers
struct cVarListSerializer {
    U32 md000[0xa14 / 4];
    cVarListSerializer(cSPGameDataUFO* pOwner, void* pContext, U32 hash);  // 0x00692f90
    bool Read(IObjectStream* pStream);                                     // 0x00693e10
};

struct cStarManager {
    U32 __thiscall GetBannerId();                                          // 0x00ba6d80
    cPlanet* __thiscall GetEmpireByID(U32 id);                             // 0x00ba9370
};
struct cNounManagerForUFO {
    void* __thiscall GetCurrentTerrainSphere();                            // 0x00f67d90
};

cStarManager* __cdecl StarManager(U32 at);                                 // 0x00b3d2a0
U32 __cdecl MessageServerRaw();                                            // 0x0067dcc0
cNounManagerForUFO* __cdecl NounManager();                                 // 0x00b3d300
U32 __cdecl GameTimeManager();                                             // 0x00b3d380
U32 __cdecl FUN_00b3d230();                                                // 0x00b3d230
U64 __fastcall FUN_00b316c0(void* pTime);                                  // 0x00b316c0
U32 __cdecl ResourceMan_GetManager();                                      // 0x0067dcd0
U32 __cdecl FUN_00bc8fa0(void* p);                                         // 0x00bc8fa0
void* __fastcall FUN_0105d1d0(void* pThis);                                // 0x0105d1d0
void* __fastcall FUN_00c75770(void* pSphere);                              // 0x00c75770
void* __fastcall FUN_00c30bd0(void* pEmpire);                              // 0x00c30bd0
U32 __cdecl FUN_00ba5df0(cKey* pKey, Vector3* pOut);                       // 0x00ba5df0
U32 __cdecl GetUniverseContext();                                          // 0x01021080
U32 __cdecl FUN_01021240();                                                // 0x01021240
U32 __cdecl FUN_01021260();                                                // 0x01021260
U32 __cdecl FUN_010212a0();                                                // 0x010212a0
void* __cdecl FUN_01021300();                                              // 0x01021300
U32 __fastcall FUN_00c70880(void* p);                                      // 0x00c70880
bool __fastcall FUN_00b8d970(void* p);                                     // 0x00b8d970
U32 __fastcall FUN_00c71e30(void* p);                                      // 0x00c71e30
bool __cdecl IsMissionActiveAtPlanet(void* p);                             // 0x0102adf0
void* __fastcall FUN_00c308d0(void* pThis);                                // 0x00c308d0
U32 __fastcall FUN_00c30c60(void* pThis);                                  // 0x00c30c60
void* __fastcall GetCities(void* pThis);                                   // 0x005c65e0
U32 __cdecl FUN_00fd9c60();                                                // 0x00fd9c60
U32 __fastcall FUN_00fdd200(void* pMode);                                  // 0x00fdd200
U32 __cdecl FUN_010666a0();                                                // 0x010666a0
void __fastcall FUN_01066dd0(void* pThis);                                 // 0x01066dd0
U32 __cdecl FUN_01046fc0();                                                // 0x01046fc0
void* __cdecl PlanetModel();                                               // 0x00b3d350
float __fastcall FUN_00b7e4d0(void* pThis);                                // 0x00b7e4d0
U32 __cdecl FUN_00b3d360(void* p);                                         // 0x00b3d360
void __fastcall FUN_00b7d580(void* pThis);                                 // 0x00b7d580
U32 __fastcall FUN_00bc9980(void* pObj, float dt);                         // 0x00bc9980
bool __cdecl FUN_00bc8ff0(float dt, double time, U32 vtbl, void* p,
                          void* pMotion, U32 a, U32 b, U32 c);             // 0x00bc8ff0
void __fastcall FUN_00f924e0(void* pThis, float f);                        // 0x00f924e0
void __fastcall FUN_00c421b0(void* pLoco, void* pArg);                     // 0x00c421b0
void __fastcall FUN_00bcb660(cBehaviorTreeData* p, void* pArg);            // 0x00bcb660
void __fastcall FUN_00bcb3d0(cBehaviorTreeData* p);                        // 0x00bcb3d0
void __fastcall FUN_00bc9ac0(cBehaviorTreeData* p, IObjectStream* pStream); // 0x00bc9ac0
U32 __fastcall FUN_00bfc540(void* pCombatant, IObjectStream* pStream);     // 0x00bfc540
U32 __fastcall FUN_00c43c10(void* pLoco, IObjectStream* pStream);          // 0x00c43c10
void __fastcall FUN_00c37180(cSPGameDataUFO* p, cKey* pKey, bool b);       // 0x00c37180
U32 __fastcall FUN_00b18600(cSPGameDataUFO* p, IObjectStream* pStream);    // 0x00b18600
cBehaviorTreeData* __fastcall FUN_00bcb2a0(cBehaviorTreeData* pThis);      // 0x00bcb2a0
U32 __cdecl FUN_00bc86e0(double t, U32 vtbl, cSPGameDataUFO* p,
                         void* pMotion, U32 a, U32 b);                     // 0x00bc86e0

// declared here so the UFO methods can call them
void cSPGameDataUFO_SetDesiredModel(cSPGameDataUFO* p, const cKey* pKey, bool b)
{
    FUN_00c37180(p, (cKey*)pKey, b);
}

// squared length, evaluated in double (x87) with the z term first, as the original does
static __forceinline double _LenSqD(float x, float y, float z)
{
    double dz = z;
    double dy = y;
    double dx = x;
    return dz * dz + dy * dy + dx * dx;
}

// @ 0x00c37a90
bool cSPGameDataUFO::Read(void* pRawStream)
{
    IObjectStream* pStream = (IObjectStream*)pRawStream;
    int nVersion;
    EA_ReadInt32(pStream->GetSource()->GetStream(), &nVersion, 1, 0);

    bool bOk = false;
    if (FUN_00b18600(this, pStream) &&
        FUN_00bfc540(&mpVftbl508, pStream) &&
        FUN_00c43c10(&mpVftbl34, pStream))
        bOk = true;

    void* pNew = operator_new(0x10, g_szSimulator, 0, 0, 0, 0);
    if (pNew != 0)
        pNew = FUN_0105d1d0(pNew);
    FUN_00c421b0(&mpVftbl34, pNew);

    mInt224 = 5;

    cVarListSerializer serializer(this, &g_1573290, 0x1a80d26);
    if (bOk && serializer.Read(pStream))
        bOk = true;
    else
        bOk = false;

    if (g_pBannerListB != 0)
        mInt7b0 = StarManager(g_pBannerListB)->GetBannerId();
    else
        mInt7b0 = 0;
    if (g_pBannerListA != 0)
        mInt764 = StarManager(g_pBannerListA)->GetBannerId();
    else
        mInt764 = 0;
    cSPGameDataUFO_SetDesiredModel(this, &mDesiredModelKey, true);

    if (mbWarping)
        mMovementTimer.Restart();

    bool bRebuild = false;
    EA_ReadBool(pStream->GetSource()->GetStream(), &bRebuild);
    if (bRebuild) {
        if (mpBehaviorTreeData != 0) {
            ((void(__thiscall*)(cBehaviorTreeData*))0x00bcae90)(mpBehaviorTreeData);
            operator_delete(mpBehaviorTreeData);
        }
        cBehaviorTreeData* pTree = (cBehaviorTreeData*)operator_new(0x670, g_szBehaviorTree, 0, 0, 0, 0);
        if (pTree != 0)
            pTree = FUN_00bcb2a0(pTree);
        mpBehaviorTreeData = pTree;
        FUN_00bc9ac0(pTree, pStream);
    }

    if (mUFOType == 0) {
        cListNode* pOwner = &mCollisions;
        U32 pServer = MessageServerRaw();
        mp804 = pServer;
        mp808 = (U32)pOwner;
        mp80c = (U32)g_aui146bb58;
        mp810 = 2;
        mp814 = 0;
        if (pServer != 0 && pOwner != 0) {
            for (U32 i = 0; i < 8; i += 4) {
                void* pSelf = pOwner;
                ((void(__thiscall*)(void*, void*, U32))((void**)(*(void***)pServer)[9]))(
                    pSelf, pOwner, g_aui146bb58[i / 4]);
            }
        }
    }
    return bOk;
}

// @ 0x00c37cc0
bool cSPGameDataUFO::WarpToDestination()
{
    if (mUFOType == 1)
        return true;

    void* pResMgr = (void*)ResourceMan_GetManager();
    typedef bool (__thiscall* tIsModelMissing)(void*, cKey*, U32, U32, U32, U32, U32);
    if (((tIsModelMissing)((void**)(*(void***)pResMgr)[3]))(pResMgr, &mDesiredModelKey, 0, 0, 0, 0, 0))
        return true;

    Vector3 vDest(0, 0, 0);
    U32 nOwner = ((IGameData*)this)->GetOwnerId();
    if (nOwner == 0xffffffff) {
        void* pSphere = NounManager()->GetCurrentTerrainSphere();
        ((void(__thiscall*)(void*))((void**)(*(void***)pSphere)[16]))(pSphere);
        vDest = *(Vector3*)FUN_00c75770(NounManager()->GetCurrentTerrainSphere());
    } else {
        cPlanet* pEmpire = StarManager(nOwner)->GetEmpireByID(nOwner);
        if (pEmpire != 0)
            vDest = *(Vector3*)FUN_00c30bd0((void*)pEmpire);
    }

    FUN_00ba5df0(&mDesiredModelKey, &vDest);
    ((ILocomotive*)&mpVftbl34)->SetOffset47(vDest);
    cSPGameDataUFO_SetDesiredModel(this, &mDesiredModelKey, true);
    return true;
}

// @ 0x00c37dc0
float __fastcall ScaleForPlanetDistance(const cMotionFrame* pFrame)
{
    float d[3];
    d[0] = pFrame->mTo.x - pFrame->mFrom.x;
    d[1] = pFrame->mTo.y - pFrame->mFrom.y;
    d[2] = pFrame->mTo.z - pFrame->mFrom.z;
    float* pMax = (d[1] > d[0]) ? &d[1] : &d[0];
    if (d[2] > *pMax)
        pMax = &d[2];
    float m = *pMax;
    if (m > 1.52587890625e-05f) {
        cPlanetTuning* pTuning = g_pPlanetTuning;
        if (m > pTuning->mf02c)
            return pTuning->mf02c / m;
        if (m < pTuning->mf028)
            return pTuning->mf028 / m;
    }
    return 1.0f;
}

// @ 0x00c37e60
void cSPGameDataUFO::PopToDestination()
{
    mNextVelocity = g_vZero;
    mNextPosition = mDestination;
    mf768 = (float)sqrt(_LenSqD(mNextPosition.x, mNextPosition.y, mNextPosition.z));

    ((ILocomotive*)&mpVftbl34)->SetPosition(mNextPosition + mOffsetFromPosition);
    ((ILocomotive*)&mpVftbl34)->SetOrientation(mNextOrientation);

    mbWarping = 1;
    if (!mMovementTimer.IsRunning())
        mMovementTimer.Restart();
}

// @ 0x00c37f70
void cSPGameDataUFO::ApplyVelocity(const Vector3& dir, float scale)
{
    if (mbWarping)
        mb624 = 0;

    float fLenX = mNextPosition.x;
    float fLenY = mNextPosition.y;
    float fLenZ = mNextPosition.z;
    float fInv = (float)(1.0 / sqrt(_LenSqD(fLenX, fLenY, fLenZ)));
    Vector3 n;
    n.x = fLenX * fInv;
    n.y = fLenY * fInv;
    n.z = fLenZ * fInv;

    Vector3 v = dir * scale;

    float fDot = v.z * n.z + v.y * n.y + v.x * n.x;
    Vector3 tangential = v - n * fDot;
    Vector3 radial = v - tangential;

    float fMag = (float)sqrt(_LenSqD(radial.x, radial.y, radial.z));
    if (fDot <= 0.0f)
        fMag = -fMag;

    mbWarping = 0;
    mMovementTimer.Stop();

    mDestination.x += tangential.x;
    mDestination.y += tangential.y;
    mDestination.z += tangential.z;
    mf768 += fMag;
    mf618 += tangential.x * 0.001f;
    mf61c += tangential.y * 0.001f;
    mf620 += tangential.z * 0.001f;
    mf60c += tangential.x * scale;
    mf610 += tangential.y * scale;
    mf614 += tangential.z * scale;
}

// @ 0x00c381e0
void cSPGameDataUFO::SetOffset(const Vector3& offset)
{
    mOffsetFromPosition = offset;
    ((ILocomotive*)&mpVftbl34)->SetPosition(mNextPosition + mOffsetFromPosition);
}

// @ 0x00c38260
bool cSPGameDataUFO::HasPendingCollisions()
{
    return mCollisions.mpNext != &mCollisions;
}

struct cActivePlanet {
    U32 pad000[0x13c / 4];     // +0x000
    U32 mp13c;                 // +0x13c
};

// @ 0x00c38270
bool cSPGameDataUFO::CanEnterPlanetContext()
{
    cActivePlanet* pPlanet = (cActivePlanet*)FUN_01021260();
    if (pPlanet == 0)
        return false;
    if (FUN_00c70880(pPlanet) == 1)
        return false;
    if (pPlanet->mp13c != 0) {
        if (FUN_00b8d970((void*)pPlanet->mp13c))
            return false;
    }
    if (!mbWarping)
        return false;
    if (!(0.0f < mf540)) {
        if ((void*)FUN_00c71e30(pPlanet) != FUN_01021300())
            return false;
        if (IsMissionActiveAtPlanet(pPlanet))
            return false;
    }
    return true;
}

struct PtrVector {
    U32* mpBegin;      // +0x00
    U32* mpEnd;        // +0x04
};

static __forceinline float DistSq(const Vector3* pa, const Vector3* pb)
{
    float dx = pb->x - pa->x;
    float dy = pb->y - pa->y;
    float dz = pb->z - pa->z;
    return dz * dz + dy * dy + dx * dx;
}

// @ 0x00c382e0
void cSPGameDataUFO::ExitToSpace()
{
    U32 planet = FUN_01021240();
    PtrVector* pStars = (PtrVector*)FUN_00c308d0(FUN_01021300());

    U32 bestEmpire = FUN_00c30c60(FUN_01021300());
    float fBest = DistSq((const Vector3*)GetCities((void*)planet),
                         (const Vector3*)GetCities((void*)bestEmpire));
    for (U32* pIter = pStars->mpBegin; pIter != pStars->mpEnd; ++pIter) {
        U32 star = *pIter;
        float d = DistSq((const Vector3*)GetCities((void*)planet),
                         (const Vector3*)GetCities((void*)star));
        if (fBest > d) {
            fBest = d;
            bestEmpire = star;
        }
    }

    U32 ctx = GetUniverseContext();
    switch (ctx) {
    case 0:
        if (FUN_01021240() == bestEmpire && FUN_00fdd200((void*)FUN_00fd9c60()) == FUN_010212a0())
            goto done;
        FUN_00b7d580((void*)FUN_00b3d360((void*)FUN_01021260()));
        ((cAppModeSpace*)FUN_00fd9c60())->FUN_00fde3e0(0);
        break;
    case 1:
        break;
    case 2:
        ((cAppModeSpace*)FUN_00fd9c60())->TransitionFromGalaxyToSolar();
        break;
    default:
        goto done;
    }
    ((cAppModeSpace*)FUN_00fd9c60())->TransitionFromPlanetToSolar(bestEmpire, 0);
    ((cAppModeSpace*)FUN_00fd9c60())->FUN_00fe0e10();
done:
    FUN_01066dd0((void*)FUN_010666a0());
    U32 ms = MessageServerRaw();
    ((void(__thiscall*)(U32, U32, U32, U32))((void**)(*(void***)ms)[5]))(ms, 0x6174b67, 0, 0);
    ((cAppModeSpace*)FUN_00fd9c60())->TransitionFromCivToSpace(0x64e8373, 0);
    if (mp7f0 != 0) {
        U32 pOld = mp7f0;
        mp7f0 = 0;
        ((void(__thiscall*)(U32))((void**)(*(void***)pOld)[1]))(pOld);
    }
    ((void(__fastcall*)(void*))0x01045c10)((void*)FUN_01046fc0());
    mInt53c = 0;
    float f = ((ICombatant*)&mpVftbl508)->GetWeaponPositionF();
    FUN_00f924e0(&mpVftbl508, f);
    mf7f4 = mf7f8;
}

// @ 0x00c38510
void cSPGameDataUFO::DeactivateBehaviorTree()
{
    if (mpBehaviorTreeData == 0 || mpBehaviorTreeData->mInt000 == 0)
        return;
    if (FUN_00b3d230() == 0)
        return;
    if (GameTimeManager() == 0)
        return;
    double t = (double)(U64)FUN_00b316c0((void*)GameTimeManager()) * g_f13f9428;
    FUN_00bc86e0(t, mpBehaviorTreeData->mInt000, this, &mpBehaviorTreeData->mMotion1d0,
                 mpBehaviorTreeData->mInt5e8, mpBehaviorTreeData->mFlags5fc);
    FUN_00bcb3d0(mpBehaviorTreeData);
}

// @ 0x00c385d0
void cSPGameDataUFO::SetupAI()
{
    if (g_b168e564 == 0) {
        g_b168e564 = 1;
        FUN_00bc8fa0(&g_159fd50);
    }
    DeactivateBehaviorTree();
    if (mpBehaviorTreeData == 0) {
        cBehaviorTreeData* pTree = (cBehaviorTreeData*)operator_new(0x670, g_szBehaviorTree, 0, 0, 0, 0);
        if (pTree != 0)
            pTree = FUN_00bcb2a0(pTree);
        mpBehaviorTreeData = pTree;
    }
    FUN_00bcb660(mpBehaviorTreeData, &g_159fd50);

    switch (mUFOType) {
    case 1:  mpBehaviorTreeData->mFlags5fc |= 4;       return;
    case 2:  mpBehaviorTreeData->mFlags5fc |= 8;       return;
    case 3:  mpBehaviorTreeData->mFlags5fc |= 0x10;    return;
    case 4:  mpBehaviorTreeData->mFlags5fc |= 0x20;    return;
    case 5:  mpBehaviorTreeData->mFlags5fc |= 0x80;    return;
    case 6:  mpBehaviorTreeData->mFlags5fc |= 0x100;   return;
    case 7:  mpBehaviorTreeData->mFlags5fc |= 2;       return;
    case 8:  mpBehaviorTreeData->mFlags5fc |= 0x200;   return;
    case 9:  mpBehaviorTreeData->mFlags5fc |= 0x400;   return;
    case 10: mpBehaviorTreeData->mFlags5fc |= 0x800;   return;
    case 11: mpBehaviorTreeData->mFlags5fc |= 0x10000; return;
    }
}

// @ 0x00c38740
bool cSPGameDataUFO::TickUFOBehaviorTree(float dt, double time)
{
    if (mpBehaviorTreeData == 0 || mpBehaviorTreeData->mInt000 == 0)
        return false;
    U32 nFlags = mpBehaviorTreeData->mFlags5fc;
    U32 nResult = FUN_00bc9980((char*)mpBehaviorTreeData + 8, dt);
    return FUN_00bc8ff0(dt, time, mpBehaviorTreeData->mInt000, this,
                        &mpBehaviorTreeData->mMotion1d0, mpBehaviorTreeData->mInt5e8,
                        nFlags, nResult);
}

// @ 0x00c387b0
float PlanetDistanceScale(Vector3 v)
{
    float fDist = (float)sqrt(_LenSqD(v.x, v.y, v.z));
    float fT = (fDist - FUN_00b7e4d0(PlanetModel())) / g_pPlanetTuning->mf010;
    float fMin = 0.0f;
    float fMax = 1.0f;
    __asm {
        movss  xmm0, fT
        maxss  xmm0, fMin
        minss  xmm0, fMax
        movss  fT, xmm0
    }
    return (float)((g_pPlanetTuning->mf090 - 1.0) * fT + 1.0);
}

// @ 0x00c38840
float cSPGameDataUFO::GetStandardSpeedForAltitude()
{
    float fBase;
    switch (mUFOType) {
    case 0:  fBase = g_pPlanetTuning->mf068; break;
    case 1:  fBase = g_pPlanetTuning->mf078; break;
    case 2:  fBase = g_pPlanetTuning->mf070; break;
    case 3:  fBase = g_pPlanetTuning->mf08c; break;
    case 4:  fBase = g_pPlanetTuning->mf074; break;
    default: fBase = g_pPlanetTuning->mf06c; break;
    }
    return PlanetDistanceScale(mNextPosition) * fBase * mf6b4;
}

// @ 0x00c38900
float cSPGameDataUFO::GetMaxSpeedForAltitude()
{
    cPlanetTuning* pTuning = g_pPlanetTuning;
    float fBase;
    if (mUFOType == 0)
        fBase = pTuning->mf0b4;
    else
        fBase = pTuning->mf0b8;
    if (GetUniverseContext() == 0)
        fBase = (float)((fabs(mf5ec) / pTuning->mf0e8) * (pTuning->mf0c4 - 1.0) + 1.0) * fBase;
    return PlanetDistanceScale(mNextPosition) * fBase * mf6b8;
}

// @ 0x00c38990
bool cSPGameDataUFO::TestFlag(U32 flag)
{
    // the original tests the upper bound twice; keep both guards
    if (flag <= 10) {
        if (flag < 10)
            return (mFlags7dc & (1u << (flag & 0x1f))) ? true : false;
    }
    return false;
}

// @ 0x00c389c0
void cSPGameDataUFO::SetFlag(U32 flag, bool value)
{
    if (flag < 10) {
        U32 nBit = flag & 0x1f;
        if (value)
            mFlags7dc |= 1u << nBit;
        else
            mFlags7dc &= ~(1u << nBit);
    }
}
