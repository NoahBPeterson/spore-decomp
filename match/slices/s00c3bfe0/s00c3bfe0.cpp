// Slice s00c3bfe0 - SP::cSPGameDataUFO methods in SPGameDataUFO.obj:
//   SetDestination(const Vector3*)  0xc3bfe0
//   SetDestination(cPlanet*)        0xc3c190
//   SetDestinationFromCities        0xc3c360  (same tail, vector from cCivData::GetCities)
//   GetNextCollision                0xc3c4d0
//   StartPlayerDeathSequence        0xc3c520
//   list_push_back helper           0xc3c810  (eastl list insert helper)
//   cSPGameDataUFO ctor             0xc3c870
// Retail offsets: cGameData @0, cLocomotiveObject @0x34, cCombatant @0x508,
// cInteractionTarget @0x5d0 (ModAPI header, not the 2008 PDB).
#include "types.h"
#include <string.h>

typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned short U16;

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

// ---------------------------------------------------------------- EASTL list
struct ListNodeBase {
    ListNodeBase* mpNext;   // +0
    ListNodeBase* mpPrev;   // +4
};
struct CollisionInfo {
    int      mNounID;       // +0
    Vector3  mPosition;     // +4
};
struct CollisionNode : public ListNodeBase {
    CollisionInfo mValue;   // +8
};

// ---------------------------------------------------------------- refcounted object
// Object whose vtable carries AddRef at +0xbc and Release at +0xc0.
struct IRefObject {
    virtual void q00(); virtual void q01(); virtual void q02(); virtual void q03();
    virtual void q04(); virtual void q05(); virtual void q06(); virtual void q07();
    virtual void q08(); virtual void q09(); virtual void q10(); virtual void q11();
    virtual void q12(); virtual void q13(); virtual void q14(); virtual void q15();
    virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19();
    virtual void q20(); virtual void q21(); virtual void q22(); virtual void q23();
    virtual void q24(); virtual void q25(); virtual void q26(); virtual void q27();
    virtual void q28(); virtual void q29(); virtual void q30(); virtual void q31();
    virtual void q32(); virtual void q33(); virtual void q34(); virtual void q35();
    virtual void q36(); virtual void q37(); virtual void q38(); virtual void q39();
    virtual void q40(); virtual void q41(); virtual void q42(); virtual void q43();
    virtual void q44(); virtual void q45(); virtual void q46();
    virtual int AddRef();    // +0xbc
    virtual int Release();   // +0xc0
};

// A ref-counted handle (AutoRefCount<T>): assignment AddRefs the new object and Releases the old.
struct RefHolder {
    IRefObject* mpObject;                                       // +0
    __forceinline RefHolder& operator=(const RefHolder& o)
    {
        if (mpObject != o.mpObject) {
            if (o.mpObject) o.mpObject->AddRef();
            IRefObject* pOld = mpObject;
            mpObject = o.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    __forceinline RefHolder& operator=(IRefObject* p)
    {
        if (mpObject != p) {
            if (p) p->AddRef();
            IRefObject* pOld = mpObject;
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------- externals
extern const char    g_sz_Simulator[];        // 0x13f09b4  "Simulator"
extern char          g_allocator_13ebb38[];   // 0x13ebb38  EASTL allocator
extern const wchar_t g_wsz_UninitUfoName[];   // 0x146be08  L"UNINITIALIZED UFO NAME"

// float / table constants (masked as relocs by chk.py)
extern float gF_1470f1c;   // 2.0
extern float gF_1485720;   // HK_REAL_ONE (1.0)
extern float gF_13ec4b4;   // FLT_MAX
extern float gF_146bb6c;   // 0.9
extern float gF_168df74;
extern float gF_168df78;
extern float gF_168df7c;
extern float gF_15731bc;
extern float gF_15731c0;
extern float gF_15731c4;
extern float gF_15731c8;
extern float gF_15731cc;
extern float gF_15731d0;
extern float gF_15731d4;
extern float gF_13ec5b4;
extern float gF_168e534;
extern float gF_168e558;
extern float gF_168e55c;
extern float gF_168e560;

void* __cdecl operator_new(U32 size, const char* pName, int a, int b, void* pAlloc, U32 line);  // 0xf473a0
void  __cdecl operator_delete(void* p);                                                          // 0xf47380

void* __cdecl NounManager();            // 0x00b3d300
void* __cdecl GetUFOSimulator();        // 0x00ffbe50
void* __cdecl GetTriggerMgr();          // 0x00b3d4d0
int   __cdecl GetUniverseContext();     // 0x01021080
void* __cdecl EffectsManager();         // 0x0067ddd0
void* __cdecl SpaceGameGet();           // 0x01002bd0
void* __cdecl FUN_010666a0();           // 0x010666a0
void* __cdecl FUN_004a9b40(void*, void*);  // 0x004a9b40 QuaternionToMatrix(out, q)
void* __cdecl FUN_00b3d390(void*, void*);  // 0x00b3d390 eastl vector erase
Vector3* __cdecl GetCities();           // 0x005c65e0 cCivData::GetCities
void* __cdecl FUN_00f67d90(void*);      // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
void* __cdecl FUN_00a1ad60(void*);      // 0x00a1ad60 GetPlayerInventory
void* __cdecl FUN_0108db30(void*);      // 0x0108db30
void* __cdecl FUN_00ff3f00(void*);      // 0x00ff3f00 GetActiveTool
void* __cdecl FUN_00c43860(void*);      // 0x00c43860
void* __cdecl FUN_00bfd4e0(void*);      // 0x00bfd4e0 cCombatant::cCombatant
void* __cdecl FUN_00ac03d0(void*);      // 0x00ac03d0 cInteractionTarget::cInteractionTarget
void* __cdecl FUN_00b18660(void*);      // 0x00b18660 cGameData::cGameData

// thiscall callee stubs
struct FnB18660  { void  __thiscall f(); };                  // 0x00b18660 cGameData::cGameData
struct FnC43860  { void  __thiscall f(); };                  // 0x00c43860
struct FnBFD4E0  { void  __thiscall f(); };                  // 0x00bfd4e0 cCombatant::cCombatant
struct FnAC03D0  { void  __thiscall f(); };                  // 0x00ac03d0 cInteractionTarget::cInteractionTarget
struct FnBC3110  { void  __thiscall f(); };                  // 0x00bc3110 cSPTimer::Stop
struct FnB63890  { void  __thiscall f(); };                  // 0x00b63890 cGonzagoTimer::cGonzagoTimer
struct FnAD79D0  { void  __thiscall f(void*, void*); };      // 0x00ad79d0 CamInfo::init
struct FnAD7AD0  { void  __thiscall f(); };                  // 0x00ad7ad0 cActionTarget::~cActionTarget
struct FnAE09B0  { void  __thiscall f(int, void*, int); };   // 0x00ae09b0 cTriggerMgr::PostAction
struct FnAE0930  { void  __thiscall f(const char*, int, int, int, int); }; // 0x00ae0930 cTriggerMgr::PostTrigger
struct Fn1066D60 { void  __thiscall f(); };                  // 0x01066d60
struct Fn104FA90 { void  __thiscall f(); };                  // 0x0104fa90 cSPToolManager::UseToolStop
struct Fn41CB40  { void  __thiscall f(void*); };             // 0x0041cb40 Matrix33::Assign
struct Fn423650  { void  __thiscall f(void*, void*); };      // 0x00423650 eastl wstring assign(first,last)
struct Fn105D1D0 { void* __thiscall f(); };                  // 0x0105d1d0
struct FnC421B0  { void  __thiscall f(void*); };             // 0x00c421b0
struct Fn104BD50 { int   __thiscall f(); };                  // 0x0104bd50

struct cPlanet;   // opaque

// pointer-to-global-of-object-with-+0x30 (0x16e0d08)
struct GlobalInvOwner { U32 md00[0xc]; void* mp30; };
extern GlobalInvOwner* g_pInvOwner16e0d08;

// ---------------------------------------------------------------- the UFO
struct cSPGameDataUFO {
    void SetDestination(const Vector3* pDest);
    void SetDestination(cPlanet* pPlanet);
    void SetDestinationFromCities(int param);
    int  GetNextCollision(Vector3* pOut);
    void StartPlayerDeathSequence();
    cSPGameDataUFO();

    void* mpVftbl00;            // +0x000
    void* mpVftbl04;            // +0x004
    U32   md008[0x2c / 4];      // +0x008
    void* mpVftbl34;            // +0x034  cLocomotiveObject vftable
    float mf038;                // +0x038
    float mf03c;                // +0x03c
    float mf040;                // +0x040
    U32   md044[0xc4 / 4];      // +0x044
    void* mpVftbl108;           // +0x108
    U32   md10c[0x118 / 4];     // +0x10c
    int   mInt224;              // +0x224
    U32   md228[0x2e0 / 4];     // +0x228
    U32   mCombatant[0xc8 / 4]; // +0x508
    U32   mInteraction[0x18 / 4];// +0x5d0
    void* mpVftbl5e8;           // +0x5e8
    float mf5ec;                // +0x5ec
    float mf5f0;                // +0x5f0
    float mf5f4;                // +0x5f4
    float mf5f8;                // +0x5f8
    float mf5fc;                // +0x5fc
    float mf600;                // +0x600
    float mf604;                // +0x604
    U8    mb608;                // +0x608
    U8    md609[3];             // +0x609 (pad)
    float mf60c;                // +0x60c
    float mf610;                // +0x610
    float mf614;                // +0x614
    float mf618;                // +0x618
    float mf61c;                // +0x61c
    float mf620;                // +0x620
    U8    mb624;                // +0x624
    U8    md625[3];             // +0x625 (pad)
    U32   mTimer628[0x20 / 4];  // +0x628
    U32   mTimer648[0x20 / 4];  // +0x648
    U32   mTimer668[0x20 / 4];  // +0x668
    U8    mb688;                // +0x688
    U8    mb689;                // +0x689
    U16   mw68a;                // +0x68a (pad)
    U32   md68c;                // +0x68c
    U8    mb690;                // +0x690
    U8    mb691;                // +0x691
    U16   mw692;                // +0x692 (pad)
    float mf694;                // +0x694
    float mf698;                // +0x698
    float mf69c;                // +0x69c
    float mf6a0;                // +0x6a0
    float mf6a4;                // +0x6a4
    float mf6a8;                // +0x6a8
    float mf6ac;                // +0x6ac
    int   mInt6b0;              // +0x6b0
    float mf6b4;                // +0x6b4
    float mf6b8;                // +0x6b8
    float mf6bc;                // +0x6bc
    float mf6c0;                // +0x6c0
    float mf6c4;                // +0x6c4
    void* mp6c8;                // +0x6c8
    U32   md6cc;                // +0x6cc (pad)
    U32   mTimer6d0[0x20 / 4];  // +0x6d0
    U32   mTimer6f0[0x20 / 4];  // +0x6f0
    int   md710;                // +0x710
    int   mUFOType;             // +0x714
    float mf718;                // +0x718
    float mf71c;                // +0x71c
    float mf720;                // +0x720
    float mf724;                // +0x724
    float mf728;                // +0x728
    float mf72c;                // +0x72c
    float mf730;                // +0x730
    float mf734;                // +0x734
    float mf738;                // +0x738
    float mf73c;                // +0x73c
    float mf740;                // +0x740
    float mf744;                // +0x744
    float mf748;                // +0x748
    U8    mb74c;                // +0x74c
    U8    md74d[3];             // +0x74d (pad)
    Vector3 mDestination;       // +0x750
    RefHolder mRef75C;          // +0x75c
    RefHolder mRef760;          // +0x760
    int   mInt764;              // +0x764
    float mf768;                // +0x768
    int   md76c;                // +0x76c
    ListNodeBase mCollisions;   // +0x770
    U32   md778;                // +0x778 (pad)
    U8    mb77c;                // +0x77c
    U8    mb77d;                // +0x77d
    U8    mb77e;                // +0x77e
    U8    mb77f;                // +0x77f (pad)
    void* mp780;                // +0x780
    void* mp784;                // +0x784
    void* mp788;                // +0x788
    U8    mb78c;                // +0x78c
    U8    mb78d;                // +0x78d
    U16   mw78e;                // +0x78e (pad)
    void* mp790;                // +0x790
    void* mp794;                // +0x794
    void* mp798;                // +0x798
    void* mp79c;                // +0x79c
    void* mp7a0;                // +0x7a0
    void* mp7a4;                // +0x7a4
    void* mp7a8;                // +0x7a8
    void* mp7ac;                // +0x7ac
    void* mp7b0;                // +0x7b0
    U32   mTimer7b8[0x20 / 4];  // +0x7b8
    void* mp7d8;                // +0x7d8
    void* mp7dc;                // +0x7dc
    wchar_t* mNameBegin;        // +0x7e0  eastl wstring
    wchar_t* mNameEnd;          // +0x7e4
    wchar_t* mNameCapacity;     // +0x7e8
    U32   md7ec;                // +0x7ec (pad)
    RefHolder mRef7f0;          // +0x7f0
    float mf7f4;                // +0x7f4
    float mf7f8;                // +0x7f8
    int   mInt7fc;              // +0x7fc
    void* mp800;                // +0x800
    void* mp804;                // +0x804
    void* mp808;                // +0x808
    void* mp80c;                // +0x80c
    int   md810;                // +0x810
    int   md814;                // +0x814
};

// destination parameter block shared by the SetDestination* family
struct DestParam {
    void* mpArray;      // +0x00
    U32   d004;         // +0x04
    U32   d008;         // +0x08
    U32   d00c;         // +0x0c  (uninitialised in the original)
    U32   d010;         // +0x10  (uninitialised in the original)
    float x;            // +0x14
    float y;            // +0x18
    float z;            // +0x1c
    float f020;         // +0x20
    U32   d024;         // +0x24
    U32   d028[9];      // +0x28  (uninitialised in the original)
    U8    b04c;         // +0x4c
    U32   d050;         // +0x50
    U32   d054;         // +0x54
    U32   d058;         // +0x58
    U32   d05c;         // +0x5c
    float f060;         // +0x60
    float f064;         // +0x64
    float f068;         // +0x68
    float f06c;         // +0x6c
    U32   d070;         // +0x70
};

typedef void (__thiscall* VfDest)(void*, DestParam*);

// emits the shared "set destination" tail: build parameter block, call
// locomotive vtable slot 0xdc, then free the block's backing array.
__forceinline void EmitDestParam(cSPGameDataUFO* self)
{
    DestParam dp;
    dp.mpArray = 0;
    dp.d004 = 0;
    dp.d008 = 0;
    dp.x = self->mDestination.x;
    dp.y = self->mDestination.y;
    dp.z = self->mDestination.z;
    dp.f020 = gF_1485720;
    dp.d024 = 0;
    dp.b04c = 0;
    dp.d050 = 0;
    dp.d054 = 0;
    dp.d058 = 0;
    dp.d05c = 1;
    dp.f060 = gF_1470f1c;
    dp.f064 = gF_13ec4b4;
    dp.f068 = gF_146bb6c;
    dp.f06c = 0.0f;
    dp.d070 = 0;
    void* pLoco = (char*)self + 0x34;
    ((VfDest)(*(void**)((char*)self->mpVftbl34 + 0xdc)))(pLoco, &dp);
    if (dp.mpArray != 0 && ((int*)dp.mpArray)[-1] != 0)
        operator_delete(dp.mpArray);
}

// ---------------------------------------------------------------- list push_back helper
// @ 0x00c3c810
void __stdcall FUN_00c3c810(ListNodeBase* pHead, const CollisionInfo* pValue)
{
    CollisionNode* pNode = (CollisionNode*)operator_new(0x18, g_sz_Simulator, 0, 0,
                                                        g_allocator_13ebb38, 0xd1);
    CollisionInfo* pDst = &pNode->mValue;
    if (pDst != 0) {
        pDst->mNounID      = pValue->mNounID;
        pDst->mPosition.x  = pValue->mPosition.x;
        pDst->mPosition.y  = pValue->mPosition.y;
        pDst->mPosition.z  = pValue->mPosition.z;
    }
    pNode->mpNext = pHead;
    pNode->mpPrev = pHead->mpPrev;
    pHead->mpPrev->mpNext = pNode;
    pHead->mpPrev = pNode;
}

// @ 0x00c3bfe0
void cSPGameDataUFO::SetDestination(const Vector3* pDest)
{
    // mRef760 = (mByte74c ? mRef75c : null)
    IRefObject* pNew = mb74c ? mRef75C.mpObject : 0;
    if (pNew != mRef760.mpObject) {
        if (pNew) pNew->AddRef();
        IRefObject* pOld = mRef760.mpObject;
        mRef760.mpObject = pNew;
        if (pOld) pOld->Release();
    }
    mRef75C = (IRefObject*)0;
    mInt764 = 0;
    mDestination = *pDest;
    mb74c = 0;
    if (mUFOType == 0)
        ((FnBC3110*)((char*)this + 0x648))->f();
    EmitDestParam(this);
}

// @ 0x00c3c190
void cSPGameDataUFO::SetDestination(cPlanet* pPlanet)
{
    IRefObject* pNew = mb74c ? mRef75C.mpObject : 0;
    if (pNew != mRef760.mpObject) {
        if (pNew) pNew->AddRef();
        IRefObject* pOld = mRef760.mpObject;
        mRef760.mpObject = pNew;
        if (pOld) pOld->Release();
    }
    mRef75C = (IRefObject*)pPlanet;
    mInt764 = 0;
    typedef Vector3* (__thiscall* VGet)(void*);
    void* pObj = (void*)pPlanet;
    Vector3* pd = ((VGet)(*(void**)(*(char**)pObj + 0x2c)))(pObj);
    mDestination = *pd;
    mb74c = 0;
    ((FnBC3110*)((char*)this + 0x648))->f();
    EmitDestParam(this);
}

// @ 0x00c3c360
void cSPGameDataUFO::SetDestinationFromCities(int param)
{
    mRef75C = (IRefObject*)0;
    mRef760 = mRef75C;
    mInt764 = param;
    Vector3* pd = GetCities();
    mDestination = *pd;
    mb74c = 0;
    ((FnBC3110*)((char*)this + 0x648))->f();
    EmitDestParam(this);
}

// @ 0x00c3c4d0
int cSPGameDataUFO::GetNextCollision(Vector3* pOut)
{
    ListNodeBase* pHead = &mCollisions;
    if (pHead->mpNext != pHead) {
        CollisionInfo* pInfo = &((CollisionNode*)pHead->mpNext)->mValue;
        int nounID = pInfo->mNounID;
        *pOut = pInfo->mPosition;
        CollisionNode* pNode = (CollisionNode*)pHead->mpNext;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        operator_delete(pNode);
        return nounID;
    }
    return 0;
}

// @ 0x00c3c520
void cSPGameDataUFO::StartPlayerDeathSequence()
{
    // set up the local camera/action-target block
    U32 camBlock[0x18];

    void* nm = NounManager();
    FUN_00f67d90(nm);
    void* inv = FUN_00a1ad60(GetUFOSimulator());
    g_pInvOwner16e0d08->mp30 = inv;

    void* invA = FUN_00a1ad60(GetUFOSimulator());
    void* invB = FUN_00a1ad60(GetUFOSimulator());
    void* subA = (char*)invA + 0x34;
    void* subB = (char*)invB + 0x34;
    typedef void* (__thiscall* VGet)(void*);
    void* argA = ((VGet)(*(void**)(*(char**)subA + 0x30)))(subA);
    void* argB = ((VGet)(*(void**)(*(char**)subB + 0x2c)))(subB);
    ((FnAD79D0*)camBlock)->f(argA, argB);

    void* invF = FUN_00a1ad60(GetUFOSimulator());
    void* subF = (char*)invF + 0x34;
    float fA = ((float (__thiscall*)(void*))(*(void**)(*(char**)subF + 0x74)))(subF);
    void* invG = FUN_00a1ad60(GetUFOSimulator());
    void* subG = (char*)invG + 0x34;
    float fB = ((float (__thiscall*)(void*))(*(void**)(*(char**)subG + 0x70)))(subG);
    (void)fA; (void)fB;

    U32 postArg[3];
    ((FnAE09B0*)GetTriggerMgr())->f(0x14a4c5f5, postArg, 0);

    void* cnt = FUN_0108db30(GetUFOSimulator());
    const char* trig;
    if (*(int*)cnt == (int)cnt) {
        int ctx = GetUniverseContext();
        trig = (ctx == 2) ? "SPG_PlayerDestroyed_PrePosse_Galaxy"
                          : "SPG_PlayerDestroyed_PrePosse_NotGalaxy";
    } else {
        trig = "SPG_PlayerDestroyed_PostPosse";
    }
    ((FnAE0930*)GetTriggerMgr())->f(trig, 1, 0, 0, 0);

    void* effects = EffectsManager();
    if (mRef7f0.mpObject != 0) {
        IRefObject* pOld = mRef7f0.mpObject;
        mRef7f0.mpObject = 0;
        ((void (__thiscall*)(void*))(*(void**)(*(char**)pOld + 4)))(pOld);
    }
    ((void (__thiscall*)(void*, int, int, RefHolder*))(*(void**)(*(char**)effects + 0x2c)))
        (effects, 0x4d42643, 0, &mRef7f0);

    void* p66a0 = FUN_010666a0();
    ((Fn1066D60*)p66a0)->f();

    if (mb77c) {
        mb77c = 0;
        mb77d = 1;
    }

    void* tool = FUN_00ff3f00(FUN_00a1ad60(SpaceGameGet()));
    if (tool != 0) {
        ((void (__thiscall*)(void*))(*(void**)(*(char**)tool + 4)))(tool);
        if (((Fn104BD50*)tool)->f()) {
            void* e = FUN_00b3d390(tool, 0);
            ((Fn104FA90*)e)->f();
        }
    }

    if (mRef7f0.mpObject != 0) {
        IRefObject* p = mRef7f0.mpObject;
        U32 pair[2];
        pair[0] = (U32)mp780;
        pair[1] = (U32)mp788;
        ((void (__thiscall*)(void*, int, void*, int))(*(void**)(*(char**)p + 0x48)))
            (p, 6, pair, 2);

        void* loco = (char*)this + 0x34;
        float trans;
        trans = ((float (__thiscall*)(void*))(*(void**)(*(char**)((char*)this + 0x34) + 0x34)))(loco);
        ((void (__thiscall*)(void*, int, void*, int))(*(void**)(*(char**)p + 0x44)))
            (p, 1, &trans, 1);

        U32 mat[9];
        ((Fn41CB40*)mat)->f(&gF_168e534);
        void* q = ((void* (__thiscall*)(void*))(*(void**)(*(char**)((char*)this + 0x34) + 0x30)))(loco);
        U32 qt[9];
        void* pm = FUN_004a9b40(qt, q);
        memcpy(mat, pm, 36);

        void* v = ((void* (__thiscall*)(void*))(*(void**)(*(char**)((char*)this + 0x34) + 0x2c)))(loco);
        struct ActionArg {
            U16 flags; U16 count; U32 v0; U32 v1; U32 v2; float f;
        };
        ActionArg aa;
        aa.flags = 4;
        aa.count = 2;
        aa.v0 = ((U32*)v)[0];
        aa.v1 = ((U32*)v)[1];
        aa.v2 = ((U32*)v)[2];
        aa.f = trans;
        ((void (__thiscall*)(void*, ActionArg*))(*(void**)(*(char**)p + 0x18)))(p, &aa);
        ((void (__thiscall*)(void*, int))(*(void**)(*(char**)p + 8)))(p, 0);
    }

    if (tool != 0)
        ((void (__thiscall*)(void*))(*(void**)(*(char**)tool + 8)))(tool);

    ((FnAD7AD0*)camBlock)->f();
}

// @ 0x00c3c870
cSPGameDataUFO::cSPGameDataUFO()
{
    ((FnB18660*)this)->f();                   // cGameData::cGameData
    void* p34 = (char*)this + 0x34;
    ((FnC43860*)p34)->f();
    void* p508 = (char*)this + 0x508;
    ((FnBFD4E0*)p508)->f();                   // cCombatant::cCombatant
    void* p5d0 = (char*)this + 0x5d0;
    ((FnAC03D0*)p5d0)->f();                   // cInteractionTarget::cInteractionTarget

    mpVftbl5e8 = (void*)0x13eb394;
    *(void**)p5d0 = (void*)0x146bb88;
    mpVftbl00 = (void*)0x146bd28;
    mpVftbl04 = (void*)0x146bd14;
    *(void**)p34 = (void*)0x146bc18;
    mpVftbl108 = (void*)0x146bc10;
    *(void**)p508 = (void*)0x146bba8;
    mpVftbl5e8 = (void*)0x146bb80;

    mf5ec = 0.0f;
    mf5f0 = 0.0f;
    mf5f4 = gF_168df74;
    mf5f8 = gF_168df78;
    mf5fc = gF_168df7c;
    mf600 = 0.0f;
    mf604 = 0.0f;
    mb608 = 0;

    mf60c = gF_168df74;
    mf610 = gF_168df78;
    mf614 = gF_168df7c;
    mf618 = gF_168df74;
    mf61c = gF_168df78;
    mf620 = gF_168df7c;
    mb624 = 0;

    ((FnB63890*)((char*)this + 0x628))->f();
    ((FnB63890*)((char*)this + 0x648))->f();
    ((FnB63890*)((char*)this + 0x668))->f();

    mb688 = 0;
    mb689 = 0;
    md68c = 0;
    mb690 = 0;
    mb691 = 0;
    mf694 = 0.0f;
    mf698 = 0.0f;
    mf69c = 0.0f;
    mf6a0 = 0.0f;
    mf6a4 = 0.0f;
    mf6a8 = 0.0f;
    mf6ac = 0.0f;
    mf6b4 = gF_1485720;
    mf6b8 = gF_1485720;
    mInt6b0 = -1;

    mf6bc = gF_15731bc;
    mf6c0 = gF_15731c0;
    mf6c4 = gF_15731c4;
    mp6c8 = 0;

    ((FnB63890*)((char*)this + 0x6d0))->f();
    ((FnB63890*)((char*)this + 0x6f0))->f();

    md710 = 0;
    mUFOType = -1;

    mf718 = gF_15731bc;
    mf71c = gF_15731c0;
    mf720 = gF_15731c4;
    mf724 = gF_168df74;
    mf728 = gF_168df78;
    mf72c = gF_168df7c;
    mf730 = gF_15731c8;
    mf734 = gF_15731cc;
    mf738 = gF_15731d0;
    mf73c = gF_15731d4;
    mf740 = gF_168df74;
    mf744 = gF_168df78;
    mf748 = gF_168df7c;

    mb74c = 1;
    mDestination.x = gF_15731bc;
    mDestination.y = gF_15731c0;
    mDestination.z = gF_15731c4;

    (void)gF_13ec5b4;
    mRef75C.mpObject = 0;
    mRef760.mpObject = 0;
    mInt764 = 0;
    mf768 = gF_13ec5b4;
    md76c = 0;

    mCollisions.mpNext = &mCollisions;
    mCollisions.mpPrev = &mCollisions;

    mb77c = 1;
    mb77d = 0;
    mb77e = 0;
    mp780 = 0;
    mp784 = 0;
    mp788 = 0;
    mb78c = 1;
    mb78d = 0;
    mp790 = 0;
    mp794 = 0;
    mp798 = 0;
    mp79c = 0;
    mp7a0 = 0;
    mp7a4 = 0;
    mp7a8 = 0;
    mp7ac = 0;
    mp7b0 = 0;

    ((FnB63890*)((char*)this + 0x7b8))->f();

    mp7d8 = 0;
    mp7dc = 0;
    mNameBegin = (wchar_t*)0x1667bac;
    mNameEnd = (wchar_t*)0x1667bac;
    mNameCapacity = (wchar_t*)0x1667bae;

    mRef7f0.mpObject = 0;
    mf7f4 = 0.0f;
    mf7f8 = 0.0f;
    mInt7fc = -1;
    mp800 = 0;
    mp804 = 0;
    mp808 = 0;
    mp80c = 0;
    md810 = 0;
    md814 = 0;

    mf038 = gF_15731bc;
    mf03c = gF_15731c0;
    mf040 = gF_15731c4;

    void* p = operator_new(0x10, g_sz_Simulator, 0, 0, 0, 0);
    if (p != 0)
        p = ((Fn105D1D0*)p)->f();
    else
        p = 0;
    ((FnC421B0*)p34)->f(p);

    mInt224 = 5;

    const wchar_t* pEnd = g_wsz_UninitUfoName;
    while (*pEnd != 0)
        ++pEnd;
    ((Fn423650*)((char*)this + 0x7e0))->f((void*)g_wsz_UninitUfoName, (void*)pEnd);
}