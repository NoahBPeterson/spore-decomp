// Slice s00c3a180 -- SPGameDataUFO.obj: cUFOKinestheticsTuning message handler +
// galaxy-warp time, the anonymous enableWeapon helper, the cSPGameDataUFO
// context-change / shutdown / tool / facing methods, and the universe-context
// dependent scale getter.
//
//   00c3a180  FUN_00c3a180                  cUFOKinestheticsTuning::HandleMessage
//   00c3a1b0  cUFOKinestheticsTuning::GetGalaxyWarpTime
//   00c3a220  `anonymous_namespace'::enableWeapon
//   00c3a2b0  cSPGameDataUFO::OnContextChange
//   00c3a5a0  FUN_00c3a5a0                  cSPGameDataUFO shutdown body
//   00c3a830  FUN_00c3a830                  cSPGameDataUFO::SetNPCTool
//   00c3a930  FUN_00c3a930                  cSPGameDataUFO::SetNPCToolIndexed
//   00c3a9f0  FUN_00c3a9f0                  window-initialize guard
//   00c3aa10  FUN_00c3aa10                  cGameData virtual-wrapper
//   00c3aa40  FUN_00c3aa40                  cSPGameDataUFO::SetFacing
//   00c3ad40  cSPGameDataUFO::GetContextScale
//
// Retail layout reference: s00c3ae70 (same object).  cGameData @0, cLocomotiveObject
// @0x34, cCombatant @0x508, cInteractionTarget @0x5d0.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

#pragma intrinsic(sqrt)

typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned short U16;
typedef          int   S32;

// ---------------------------------------------------------------- math types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

// ---------------------------------------------------------------- refcounted object
// Object whose vtable carries the owning-handle protocol: Release at +0x4
// (used when clearing a stored handle) and Release at +0x8 (used when dropping
// a temporary).  The disassembly loads the slot address and calls it.
struct IRefObject {
    virtual void q00();                    // +0x00
    virtual int  AddRef();                 // +0x04
    virtual int  Release();                // +0x08
};

// ---------------------------------------------------------------- constants
extern float gF_146bb70;                    // 0x0146bb70  1.5258789e-05

// ---------------------------------------------------------------- globals / free functions
int   __cdecl GetUniverseContext();         // 0x01021080
void* __cdecl IsArchivedState();            // 0x01021240 (returns cCivData* or 0)
void* __cdecl StarManager();                // 0x00b3d2a0 (StarManager())
void* __cdecl GetSpaceCombatTuning();       // 0x01029940
int   __cdecl GetPropertyAsFloatArray(void* pList, int id, int* pCount, float** pArray); // 0x006a08b0
void* __cdecl EraseToolEntry(void* p, void* q);   // 0x00b3d390
void* __cdecl FUN_00b3d300(void* p);        // 0x00b3d300 (noun-manager relookup)
void  __cdecl RemoveHandler(void*, void*, void*, void*, void*);   // 0x00571db0
void  __cdecl NounManager_RemoveNoun(void* mgr, void* noun);      // 0x00b225d0
void* __cdecl FUN_00b3d2a0(void* p);        // 0x00b3d2a0 (StarManager from id)
void* __cdecl FUN_00ba9370(void* p);        // 0x00ba9370 (GetEmpireByID)
void  __cdecl FUN_00c38510(void* thisp);    // 0x00c38510 DeactivateBehaviorTree
void  __cdecl FUN_00bfc720(void* thisp);    // 0x00bfc720
void  __cdecl FUN_00c42140(void* p);        // 0x00c42140
void  __cdecl FUN_00c38b10(void* thisp);    // 0x00c38b10
void  __cdecl FUN_00ac0450(void);           // 0x00ac0450
void  __cdecl FUN_00ac0520(void* thisp);    // 0x00ac0520 cLocomotiveObject::Shutdown
void  __cdecl FUN_00bc3110(void* p);        // 0x00bc3110 cSPTimer::Stop
void  __cdecl FUN_0059aed0(void* pOut, void* pKey, void* pIn);   // 0x0059aed0
float*__cdecl FUN_006985b0(Vector3* pOut, const Vector3* pIn);   // 0x006985b0 OrthogonalVector
void* __cdecl FUN_0069b440(void*, const void*, const void*);      // 0x0069b440 Matrix3FromFacingAndUp
void* __cdecl FUN_00472b80(void*, void*, int);                    // 0x00472b80 QuaternionFromMatrix33
void  __cdecl UseToolStop(void*);                  // 0x0104fa90
char  __cdecl UTFWin_Window_Initialize();          // 0x00b1fbf0 (bool)
int   __cdecl cSPSpaceCombatTuning_GetWeaponLevel(void* pTuning, const float* pPos); // 0x0102a360
int   __cdecl cEmpire_GetWeaponryLevel(void* pEmpire);   // 0x00c317a0
float*__cdecl cCivData_GetCities(void* pCiv);            // 0x005c65e0
void  __cdecl FUN_006a0ae0(void* pVector, int id, int* pCount, int* pBase); // 0x006a0ae0 (vector reserve)

// thiscall member stubs -- each member is declared on its own line inside the struct so
// the '// 0x...' address annotation attaches to the (class, member) pair for the resolver.
struct Fn00bfc860 {
    void __thiscall f(void* pTool);            // 0x00bfc860  cGameData::WriteAsText
};
struct Fn0104bd50 {
    char __thiscall f();                       // 0x0104bd50  tool-active test
};
struct Fn005766e0 {
    void __thiscall f(void* pTarget);          // 0x005766e0
};
struct Fn00572620 {
    void __thiscall f(void* p);                // 0x00572620
};
struct Fn00c37740 {
    void* __thiscall f(void* p);               // 0x00c37740
};
struct Fn0104e340 {
    char __thiscall f(unsigned int toolId);    // 0x0104e340  CreateToolFromToolID (ret 4)
};

// external tuning pointer 0x0168df68 dereferenced directly at each use

// property-list ids referenced by these functions
static const int kPropGalaxyWarpTime = 0x5c8077c;
static const int kPropWeaponSet01    = 0x578ec62;
static const int kPropWeaponSet02    = 0x578ec6c;
static const int kPropWeaponSet03    = 0x6170f29;
static const int kPropWeaponSet04    = 0x6170f3a;
static const int kPropWeaponSet05    = 0x6170f38;
static const int kPropWeaponSet06    = 0x587348d;
static const int kPropWeaponSet07    = 0x580b099;
static const int kPropWeaponSet08    = 0x58734a1;
static const int kPropWeaponSet09    = 0x578ec76;
static const int kPropMineState01    = 0xb033b403;
static const int kPropMineState02    = 0x137e8e0;

// =============================================================================================
// cUFOKinestheticsTuning  (layout from the s00c3ae70 slice)
// =============================================================================================
struct IHandler {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048();
};

struct cUFOKinestheticsTuning : public IHandler {
    void* mpPropList;                        // +0x04
    U8 mf008[0x1e4 - 0x08];                  // +0x08 .. +0x1e3 (opaque tuning scalars)

    void  ReadProps();                       // 0x00c38d00
    float GetGalaxyWarpTime(int warpMode, float unused, float t);
    char  HandleMessage(int messageID, int arg);
};

// =============================================================================================
// cSPGameDataUFO  (flat retail layout; offsets match s00c3ae70)
// =============================================================================================
struct cSPGameDataUFO {
    void* mpVftbl0;                          // +0x000
    U8 pad004[48];                           // +0x004
    void* mpVftbl34;                         // +0x034
    U8 pad038[0x288 - 0x38];                 // +0x038
    IRefObject* mp288;                       // +0x288
    U8 pad28c[0x508 - 0x28c];                // +0x28c
    void* mpVftbl508;                        // +0x508
    U8 pad50c[0x5f4 - 0x50c];                // +0x50c .. +0x5f3
    float mDestZ;                            // +0x5f4 orthogonal component (z)
    float mDestX;                            // +0x5f8 orthogonal component (x)
    float mDestY;                            // +0x5fc orthogonal component (y)
    U8 pad600[0x648 - 0x600];                // +0x600 .. +0x647
    U8 mTimer648[0x20];                      // +0x648 cSPTimer
    U8 pad668[0x68c - 0x668];                // +0x668
    IRefObject* mp68c;                       // +0x68c
    U8 pad690[0x710 - 0x690];                // +0x690
    IRefObject* mp710;                       // +0x710
    int   mUFOType;                          // +0x714
    float mCurX;                             // +0x718
    float mCurY;                             // +0x71c
    float mCurZ;                             // +0x720
    U8 pad724[0x74c - 0x724];                // +0x724 .. +0x74b
    U8    mb74c;                             // +0x74c
    U8    pad74d[3];                         // +0x74d
    Vector3 mDestination;                    // +0x750
    IRefObject* mp75c;                       // +0x75c
    IRefObject* mp760;                       // +0x760
    U8 pad764[0x790 - 0x764];                // +0x764
    IRefObject* mp790;                       // +0x790
    IRefObject* mp794;                       // +0x794
    IRefObject* mp798;                       // +0x798
    IRefObject* mp79c;                       // +0x79c
    IRefObject* mp7a0;                       // +0x7a0
    IRefObject* mp7a4;                       // +0x7a4
    IRefObject* mp7a8;                       // +0x7a8
    IRefObject* mp7ac;                       // +0x7ac
    void* mp7b0;                             // +0x7b0 (cCivData*)
    U8 pad7b4[0x7bc - 0x7b4];                // +0x7b4
    int   mInt7bc;                           // +0x7bc
    U8 pad7c0[0x7d8 - 0x7c0];                // +0x7c0
    IRefObject* mp7d8;                       // +0x7d8
    U8 pad7dc[0x7f0 - 0x7dc];                // +0x7dc
    IRefObject* mp7f0;                       // +0x7f0
    U8 pad7f4[0x800 - 0x7f4];                // +0x7f4
    void* mp800;                             // +0x800
    void* mp804;                             // +0x804
    void* mp808;                             // +0x808
    void* mp80c;                             // +0x80c
    int   md810;                             // +0x810
    int   md814;                             // +0x814

    int   HandleMessage(int messageID, int arg);
    void  OnContextChange(int context);
    void  ShutdownInternal();
    void  SetNPCTool(void* pTool);
    void  SetNPCToolIndexed(void* pTool, int index);
    char  Initialize();
    char  vtableSlot40Wrapper(int arg);
    void  SetFacing(const Vector3* pFacing);
    float GetContextScale();
};
struct FnB183F0 { char __thiscall f(int arg); };   // 0x00b183f0 cGameData::vtableSlot40 (ret 4)
struct FnC385D0 { void __thiscall f(); };           // 0x00c385d0
struct Fn104e340 { char __thiscall f(unsigned int toolId); };  // 0x0104e340 CreateToolFromToolID
struct Fn104E340 { char __thiscall f(); };          // 0x0104e340 CreateToolFromToolID (ecx = slot ptr)

static const int kCivTuningId = 0x5c8077c;  // placeholder for the array-count id

// ---------------------------------------------------------------- vtable call shims
// (void* arithmetic is illegal in cl, so the slot address is built from a U8*.)
static inline void vcall_release8(IRefObject* p)          // vtable +0x8
{
    (*(void (__thiscall**)(void*))((U8*)*(void**)p + 0x8))(p);
}
static inline void vcall_addref4(IRefObject* p)           // vtable +0x4
{
    (*(void (__thiscall**)(void*))((U8*)*(void**)p + 0x4))(p);
}
static inline void vcall_c0(IRefObject* p)                // vtable +0xc0
{
    (*(void (__thiscall**)(void*))((U8*)*(void**)p + 0xc0))(p);
}
static inline int vcall_5c(IRefObject* p, int id)         // vtable +0x5c
{
    return (*(int (__thiscall**)(void*, int))((U8*)*(void**)p + 0x5c))(p, id);
}

// the +0x794/+0x79c style "copy through but release-if-exists" swap:
//   *pDst = *pSrc, AddRef-clear the destination's old value, Release the source's old value
static void HolderAssign(IRefObject** ppDst, IRefObject* pSrc)
{
    IRefObject* pOld = *ppDst;
    if (pSrc == pOld)
        return;
    if (pSrc != 0)
        vcall_addref4(pSrc);          // vtable +0x4
    *ppDst = pSrc;
    if (pOld != 0)
        vcall_release8(pOld);         // vtable +0x8
}

// =============================================================================================
// 00c3a180  cUFOKinestheticsTuning::HandleMessage
// =============================================================================================
// @ 0x00c3a180
char cUFOKinestheticsTuning::HandleMessage(int messageID, int arg)
{
    if (messageID == 0xf62def && *(int*)(arg + 0x18) == (int)0x99fb6f5b)
        this->ReadProps();
    return 0;
}

// =============================================================================================
// 00c3a1b0  cUFOKinestheticsTuning::GetGalaxyWarpTime
//   warpMode 2 -> lerp(array[0], array[1], t);  warpMode 4 -> array[2];  else 1.0f.
//   Returned through the x87 stack, so declared float here.
// =============================================================================================
// @ 0x00c3a1b0
float cUFOKinestheticsTuning::GetGalaxyWarpTime(int warpMode, float unused, float t)
{
    (void)unused;
    float* pArray = 0;
    int    count  = 0;
    GetPropertyAsFloatArray(this->mpPropList, kPropGalaxyWarpTime, &count, &pArray);

    switch (warpMode)
    {
    case 2:
        if (count > 1)
            return (pArray[1] - pArray[0]) * t + pArray[0];
        break;
    case 4:
        if (count > 2)
            return pArray[2];
        break;
    default:
        break;
    }
    return 1.0f;
}

// =============================================================================================
// 00c3a220  `anonymous_namespace'::enableWeapon
//   Reserve the weapon-vector slot at the requested level, then create/replace
//   the tool bound to it.
// =============================================================================================
// @ 0x00c3a220
void enableWeapon(int toolID, int weaponLevel, IRefObject** ppSlot)
{
    int base  = 0;
    int count = 0;
    void* pTuning = GetSpaceCombatTuning();
    FUN_006a0ae0(*(void**)((U8*)pTuning + 8), toolID, &count, &base);

    if (count <= weaponLevel)
    {
        if (count > 0)
            weaponLevel = count - 1;
        if (count <= weaponLevel)
            return;
    }

    void* pEntry = (void*)(base + weaponLevel * 0xc);
    IRefObject* pOld = *ppSlot;
    if (pOld != 0)
    {
        *ppSlot = 0;
        vcall_release8(pOld);           // vtable +0x8
    }
    void* pEntryResult = EraseToolEntry(pEntry, ppSlot);
    // CreateToolFromToolID is `?CreateToolFromToolID@cSPToolManager@@QAE_NI@Z`; its `this`
    // (ecx) is the erase result and the tool id is the stack argument.  MSVC /O2 folds the
    // `mov ecx, eax` here, so the encoded call differs from the original even though the
    // observable behaviour is the same (see nonmatching.txt).
    ((Fn0104e340*)pEntryResult)->f((unsigned int)(U32)pEntry);
}

// =============================================================================================
// 00c3a2b0  cSPGameDataUFO::OnContextChange
//   Pick the weapon level from the empire/civ, then re-bind the +0x790..+0x7ac
//   tool slots for the requested context, keyed on mUFOType (3 or 8).
// =============================================================================================
// @ 0x00c3a2b0
void cSPGameDataUFO::OnContextChange(int context)
{
    void* pCiv = IsArchivedState();

    // (**(vftable+0x4c))() -- the loaded-object political id feeding the star manager.
    int objID = (*(int (__thiscall**)(cSPGameDataUFO*))((U8*)this->mpVftbl0 + 0x4c))(this);
    void* pEmpire = FUN_00ba9370(FUN_00b3d2a0((void*)objID));

    int weaponLevel;
    if (pEmpire != 0)
    {
        weaponLevel = cEmpire_GetWeaponryLevel(pEmpire);
    }
    else if (this->mp7b0 != 0)
    {
        float* pPos = cCivData_GetCities(this->mp7b0);
        void* pTuning = GetSpaceCombatTuning();
        weaponLevel = cSPSpaceCombatTuning_GetWeaponLevel(pTuning, pPos);
    }
    else if (pCiv != 0)
    {
        float* pPos = cCivData_GetCities(pCiv);
        void* pTuning = GetSpaceCombatTuning();
        weaponLevel = cSPSpaceCombatTuning_GetWeaponLevel(pTuning, pPos);
    }
    else
    {
        weaponLevel = 0;
    }

    if (this->mp790 != 0 && ((Fn0104bd50*)this->mp790)->f())
    {
        IRefObject* pTool = this->mp790;
        EraseToolEntry(pTool, 0);
        UseToolStop(pTool);
    }

    HolderAssign(&this->mp7a0, this->mp7a0);
    HolderAssign(&this->mp79c, this->mp7a0);
    HolderAssign(&this->mp798, this->mp79c);
    HolderAssign(&this->mp794, this->mp798);
    HolderAssign(&this->mp790, this->mp794);

    if (context == 0)
    {
        if (this->mUFOType == 3)
        {
            enableWeapon(kPropWeaponSet01, weaponLevel, &this->mp7a0);
            enableWeapon(kPropWeaponSet02, weaponLevel, &this->mp798);
        }
        else if (this->mUFOType == 8)
        {
            enableWeapon(kPropWeaponSet03, weaponLevel, &this->mp7a0);
            enableWeapon(kPropWeaponSet04, weaponLevel, &this->mp798);
            enableWeapon(kPropWeaponSet05, weaponLevel, &this->mp79c);
        }
    }
    else if (context == 1)
    {
        if (this->mUFOType == 3)
            enableWeapon(kPropWeaponSet06, weaponLevel, &this->mp7a0);
        else if (this->mUFOType == 8)
            enableWeapon(kPropWeaponSet07, weaponLevel, &this->mp7a0);
    }
    else if (context == 2)
    {
        if (this->mUFOType == 3)
            enableWeapon(kPropWeaponSet08, weaponLevel, &this->mp7a0);
        else if (this->mUFOType == 8)
            enableWeapon(kPropWeaponSet09, weaponLevel, &this->mp7a0);
    }
}

// =============================================================================================
// 00c3a5a0  cSPGameDataUFO::ShutdownInternal  (Destruct-shaped teardown)
// =============================================================================================
// @ 0x00c3a5a0
void cSPGameDataUFO::ShutdownInternal()
{
    if (this->mp800 != 0)
    {
        IRefObject* p = (IRefObject*)this->mp800;
        this->mp800 = 0;
        vcall_addref4(p);                       // vtable +0x4
    }

    FUN_00c38510(this);                         // DeactivateBehaviorTree
    FUN_00bfc720(this);

    IRefObject* p34 = (IRefObject*)this->mpVftbl34;
    if (p34 != 0)
    {
        this->mpVftbl34 = 0;
        vcall_addref4(p34);                     // vtable +0x4
    }

    FUN_00ac0450();
    FUN_00ac0520(this);                         // cLocomotiveObject::Shutdown

    if (this->mp790 != 0 && ((Fn0104bd50*)this->mp790)->f())
    {
        IRefObject* pTool = this->mp790;
        EraseToolEntry(pTool, 0);
        UseToolStop(pTool);
    }

    if (this->mp794 != 0)
    {
        IRefObject* p = this->mp794;
        this->mp794 = 0;
        vcall_release8(p);                      // vtable +0x8
    }

    HolderAssign(&this->mp7a0, this->mp79c);
    HolderAssign(&this->mp79c, this->mp798);
    HolderAssign(&this->mp798, this->mp794);

    if (this->mp710 != 0)
    {
        IRefObject* p = this->mp710;
        this->mp710 = 0;
        vcall_release8(p);                      // vtable +0x8
    }

    if (this->mp7d8 != 0)
    {
        void* pNoun = FUN_00b3d300(this->mp7d8);
        NounManager_RemoveNoun(pNoun, this->mp7d8);
        if (this->mp7d8 != 0)
        {
            IRefObject* p = this->mp7d8;
            this->mp7d8 = 0;
            vcall_addref4(p);                   // vtable +0x4
        }
    }

    FUN_00c42140((void*)0x00b4c850);
    FUN_00c38b10(this);

    if (this->mp75c != 0)
    {
        IRefObject* p = this->mp75c;
        this->mp75c = 0;
        vcall_c0(p);                            // vtable +0xc0
    }
    if (this->mp760 != 0)
    {
        IRefObject* p = this->mp760;
        this->mp760 = 0;
        vcall_c0(p);                            // vtable +0xc0
    }

    if (this->mp7f0 != 0) { IRefObject* p = this->mp7f0; this->mp7f0 = 0; vcall_addref4(p); }
    if (this->mp68c != 0) { IRefObject* p = this->mp68c; this->mp68c = 0; vcall_addref4(p); }
    if (this->mp7a8 != 0) { IRefObject* p = this->mp7a8; this->mp7a8 = 0; vcall_addref4(p); }
    if (this->mp7ac != 0) { IRefObject* p = this->mp7ac; this->mp7ac = 0; vcall_addref4(p); }
    if (this->mp7a4 != 0) { IRefObject* p = this->mp7a4; this->mp7a4 = 0; vcall_addref4(p); }

    if (this->mp804 != 0)
    {
        void* h = this->mp804;
        this->mp804 = 0;
        RemoveHandler(h, this->mp808, this->mp80c, (void*)(U32)this->md810, (void*)(U32)this->md814);
    }
}

// =============================================================================================
// 00c3a830  cSPGameDataUFO::SetNPCTool  (invoked on the +0x508 subobject, so `this`
//   points at ufo+0x508; the base object is recovered by subtracting the subobject offset)
// =============================================================================================
// @ 0x00c3a830
void cSPGameDataUFO::SetNPCTool(void* pTool)
{
    // `this` is the cCombatant subobject at base+0x508 in the retail object model.
    cSPGameDataUFO* pBase = (cSPGameDataUFO*)((U8*)this - 0x508);

    IRefObject* pOld = pBase->mp790;
    if (pOld != 0)
        vcall_addref4(pOld);                    // vtable +0x4 -> Release

    if (pTool == 0 || pBase->mUFOType == 7)
        goto done;

    {
        IRefObject* p = (IRefObject*)pTool;
        int a = vcall_5c(p, 0x2dd8c33);         // QI -> some sub-tool
        int b = vcall_5c(p, kPropMineState01);  // 0xb033b403
        int c = vcall_5c(p, kPropMineState02);  // 0x137e8e0

        if (a != 0)
        {
            ((Fn005766e0*)&pBase->mp790)->f(&pBase->mp7a4);
            goto done;
        }

        if (pTool == 0)
        {
            if (c == 0 || *(int*)(c + 0xb1c) != 2)
            {
                ((Fn005766e0*)&pBase->mp790)->f(&pBase->mp794);
                goto done;
            }
        }

        void* r = ((Fn00c37740*)pBase)->f(pTool);
        ((Fn00572620*)&pBase->mp790)->f(r);
    }

done:
    if (pOld != 0 && ((Fn0104bd50*)pOld)->f() && pOld != pBase->mp790)
    {
        EraseToolEntry(pOld, 0);
        UseToolStop(pOld);
    }

    ((Fn00bfc860*)this)->f(pTool);              // WriteAsText  (this = base+0x508)

    if (pOld != 0)
        vcall_release8(pOld);                   // vtable +0x8 -> Release
}

// =============================================================================================
// 00c3a930  cSPGameDataUFO::SetNPCToolIndexed
// =============================================================================================
// @ 0x00c3a930
void cSPGameDataUFO::SetNPCToolIndexed(void* pTool, int index)
{
    IRefObject** ppSlot = &this->mp790;
    IRefObject* pOld = *ppSlot;

    if (pOld != 0)
        vcall_addref4(pOld);                    // vtable +0x4

    if (pTool != 0 && this->mUFOType != 7)
    {
        vcall_5c((IRefObject*)pTool, kPropMineState01);
        vcall_5c((IRefObject*)pTool, kPropMineState02);

        if (index == 1)
            ((Fn005766e0*)&this->mp790)->f(&this->mp798);
        else if (index == 2)
            ((Fn005766e0*)&this->mp790)->f(&this->mp79c);
        else if (index == 3)
            ((Fn005766e0*)&this->mp790)->f(&this->mp7a0);
    }

    if (pOld != 0 && ((Fn0104bd50*)pOld)->f() && pOld != *ppSlot)
    {
        EraseToolEntry(pOld, 0);
        UseToolStop(pOld);
    }

    ((Fn00bfc860*)((U8*)this + 0x508))->f(pTool);   // WriteAsText

    if (pOld != 0)
        vcall_release8(pOld);                   // vtable +0x8
}

// =============================================================================================
// 00c3a9f0  window-initialize guard
// =============================================================================================
// @ 0x00c3a9f0
char cSPGameDataUFO::Initialize()
{
    if (this->mInt7bc == 0)
        return UTFWin_Window_Initialize();
    return 0;
}

// =============================================================================================
// 00c3aa10  cGameData virtual-wrapper
// =============================================================================================
// @ 0x00c3aa10
char cSPGameDataUFO::vtableSlot40Wrapper(int arg)
{
    char ok = ((FnB183F0*)this)->f(arg);
    if (ok != 0)
        ((FnC385D0*)this)->f();
    return ok;
}

// =============================================================================================
// 00c3aa40  cSPGameDataUFO::SetFacing (SetHeading-shaped)
//   Normalise the facing vector, store it into the destination + current-position
//   cache, build the orthonormal basis + quaternion into +0x730.
//
// NOTE (set 2026-10-24):  this reconstruction uses the Ghidra *variable* names from the
// bounded-stack decompilation, but the author's description text below it (written earlier)
// cites addresses differently.  Cross-checked against the raw listing at 00c3aa40..00c3ad40:
//   +0x718/+0x71c/+0x720 = the incoming facing (raw *pFacing)
//   +0x750/+0x754/+0x758 = the *normalised* dir
//   +0x5f4(z)/+0x5f8(x)/+0x5fc(y) = the orthogonal components
// The Ghidra variable `dir` is therefore the raw pFacing, and `unit` is the normalised one;
// the pre-refactor source had these swapped.  Renamed here for readability only.
// =============================================================================================
// @ 0x00c3aa40
void cSPGameDataUFO::SetFacing(const Vector3* pFacing)
{
    Vector3 basis;
    FUN_0059aed0(&basis, (void*)0x015731b0, &mDestination);

    float invLen = 1.0f / sqrtf(pFacing->x * pFacing->x +
                                pFacing->y * pFacing->y +
                                pFacing->z * pFacing->z);

    Vector3 unit;
    unit.x = pFacing->x * invLen;
    unit.y = pFacing->y * invLen;
    unit.z = pFacing->z * invLen;

    this->mb74c = 0;
    FUN_00bc3110(this->mTimer648);              // cSPTimer::Stop

    this->mDestination = unit;

    // (*(vftbl34+0x38))(pFacing)
    (*(void (__thiscall**)(void*, const Vector3*))
        ((U8*)*(void**)this->mpVftbl34 + 0x38))(this->mpVftbl34, pFacing);

    this->mCurX = pFacing->x;
    this->mCurY = pFacing->y;
    this->mCurZ = pFacing->z;

    float dot = unit.x * basis.x + unit.y * basis.y + unit.z * basis.z;
    float oy  = basis.y - unit.y * dot;         // -> +0x5fc
    float oz  = basis.z - unit.z * dot;         // -> +0x5f4
    float ox  = basis.x - unit.x * dot;         // -> +0x5f8

    this->mDestZ = oz;
    this->mDestX = ox;
    this->mDestY = oy;

    if (ox * ox + oy * oy + oz * oz < gF_146bb70)
    {
        Vector3 ortho;
        FUN_006985b0(&ortho, &basis);
        float l2 = 1.0f / sqrtf(ortho.x * ortho.x + ortho.y * ortho.y + ortho.z * ortho.z);
        ox = ortho.x * l2;
        oy = ortho.y * l2;
        oz = ortho.z * l2;
        this->mDestZ = oz;
        this->mDestX = ox;
        this->mDestY = oy;
    }

    float mtx[9];
    FUN_0069b440(mtx, &basis, &unit);
    float quat[4];
    FUN_00472b80(quat, mtx, 0);
    (*(float*)((U8*)this + 0x730)) = quat[0];
    (*(float*)((U8*)this + 0x734)) = quat[1];
    (*(float*)((U8*)this + 0x738)) = quat[2];
    (*(float*)((U8*)this + 0x73c)) = quat[3];
}

// =============================================================================================
// 00c3ad40  cSPGameDataUFO::GetContextScale
//   Jump-table dispatch on mUFOType; several cases consult the universe context.
// =============================================================================================
// @ 0x00c3ad40
float cSPGameDataUFO::GetContextScale()
{
    float* pTuning = *(float**)0x0168df68;
    switch (this->mUFOType)
    {
    case 1:
        return pTuning[0x38 / 4];
    case 2:
        if (GetUniverseContext() == 2)
            return pTuning[0x48 / 4];
        return pTuning[0x34 / 4];
    case 3:
        return pTuning[0x3c / 4];
    case 4:
        if (GetUniverseContext() == 2)
            return pTuning[0x44 / 4];
        return pTuning[0x30 / 4];
    case 5:
        break;
    case 6:
        if (GetUniverseContext() == 2)
            return pTuning[0x50 / 4];
        return pTuning[0x40 / 4];
    case 7:
        break;
    case 8:
        break;
    case 9:
        if (GetUniverseContext() == 2)
            return pTuning[0x4c / 4];
        break;
    default:
        break;
    }
    return pTuning[0x64 / 4];
}
