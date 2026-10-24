// Slice s00cbb020 (worker 9) -- the projectile/space-tool update block at
// 0x00CBB020:
//   SP::cFlakProjectile::Update, SP::cSpaceDefenseMissile::Update,
//   SP::cCulturalProjectile::Update, a list reader helper, a serialiser helper,
//   Simulator::cGameData's teardown (FUN_00cbb6f0), RemoveOwner and a large
//   space-tool UpdateRing.
//
// PDB names confirmed: 0x00cbb020 SP::cFlakProjectile::Update,
// 0x00cbb160 SP::cSpaceDefenseMissile::Update.  The rest carry Ghidra's
// FUN_ / caller-scored names; 0x00cbb790 is the well-known engine routine
// Simulator::cGameData::RemoveOwner (compare 0x00c3f310, 0x00c7c220).
//
// These routines are all "embedded sub-object" methods: ecx points at a block
// inside a larger object, so the enclosing body is recovered once at the top of
// each routine by the fixed base-pointer subtraction (the ABI forces this; every
// *field* below is a named member of a declared struct, never a raw offset).
// The two teardown routines (0x00cbb6f0, 0x00cbb790) are plain field/vtable work
// and are reconstructed for byte-exactness; the float-heavy Updates are
// structural reconstructions (x87/SSE scheduled, marked nonmatching).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;
typedef unsigned __int64 u64;

struct Vec3 { float x, y, z; };

// Dispatch through vftable slot <byteOffset> of an object whose class is not
// declared here (vtable-slot dispatch is the accepted convention).
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void  (__thiscall *Fn_v_ppp)(void*, void*, void*);
typedef void  (__thiscall *Fn_v_pppp)(void*, void*, void*, void*);
typedef void* (__thiscall *Fn_p_p)(void*);
typedef void* (__thiscall *Fn_p_pi)(void*, int);
typedef Vec3* (__thiscall *Fn_v3_ppi)(void*, void*, int);
typedef int   (__thiscall *Fn_i_p)(void*);
typedef bool  (__thiscall *Fn_b_p)(void*);
typedef bool  (__thiscall *Fn_b_pi)(void*, int);
typedef float (__thiscall *Fn_f_p)(void*);
// thiscall taking (spaceTool, position, stateIndex, object) on slot 0x30.
typedef void  (__thiscall *Fn_Slot30)(void*, void* pTool, void* pPos, int state, void* pObj);

// ---- engine data globals ----------------------------------------------------
extern "C" float DAT_013eb8b0 = -0.0f;                   // 0x013eb8b0  0x80000000 sign mask
extern "C" float DAT_013eb960 = 0.01f;                   // 0x013eb960  lubricant-universe fuse range
extern "C" float DAT_014853e0 = 4.0f;                    // 0x014853e0  default fuse range
extern "C" float DAT_01485720 = 1.0f;                    // 0x01485720  HK_REAL_ONE
extern "C" float DAT_01475160 = 1.52587890625e-05f;      // 0x01475160  2^-16
extern "C" float DAT_01470f1c = 2.0f;                    // 0x01470f1c  arrival radius
extern "C" float DAT_01486110 = 5.0f;                    // 0x01486110  guidance step
extern "C" u8    DAT_01186577 = 0;                       // 0x01186577  node key
extern "C" u8    DAT_014011d0 = 0;                       // 0x014011d0  empty wide string
extern "C" void* DAT_013f94d4 = 0;                       // 0x013f94d4  property/type key
extern "C" void* DAT_01654c05 = 0;                       // 0x01654c05  game-mode tag A
extern "C" void* DAT_01654c10 = 0;                       // 0x01654c10  game-mode tag B

// ---- forward declarations ---------------------------------------------------
struct Obj;
struct RefList;
struct RefMap;
struct cSPTimer;
struct WString16;
struct Struct_PlanetModel;
struct cPathFollowingLocomotion;
struct cSPSpaceTool;
struct cSpaceToolState;
struct cFlakProjectileBody;
struct cMissileBody;
struct cCulturalBody;
namespace Simulator { struct cGameData; struct cLocomotiveObject; }
namespace SP {
    struct cFlakProjectile;
    struct cSpaceDefenseMissile;
    struct cCulturalProjectile;
}

// ---- engine entry points ----------------------------------------------------
Obj*  __cdecl SP_PlanetModel();                  // 0x00b3d350
void* __cdecl SP_GetCurrentGameMode();           // 0x00b5b800
int   __cdecl SP_GetUniverseContext();           // 0x01021080
float __cdecl SP_VectorLength(Vec3* p);          // 0x0040ae50
Obj*  __cdecl SP_InterfaceCast(void* p);         // 0x00cb45d0
Vec3* __cdecl SP_NormalizedSafe(Vec3* pOut, Vec3* pV);   // 0x00449c20
void  __cdecl EA_IO_ReadInt32(void* pStream, void* pOut, int n, int flag);  // 0x0093a780
const wchar_t* __cdecl EA_ConvertToString16(void* pOut, const wchar_t* p, int len);  // 0x0093c5a0
void* __cdecl eastl_RBTreeIncrement(void* node); // 0x00921580
char  __cdecl FUN_00ac8050(void* pMap, int a, void* pSrc);   // 0x00ac8050
void* __cdecl FUN_00ae3330(void* pField);        // 0x00ae3330
void* __cdecl FUN_00ad2670(void* pField);        // 0x00ad2670
int   __cdecl FUN_00cb6a50(Vec3* pStart, float r, Vec3* pDir, Vec3* pLast);   // 0x00cb6a50
int   __cdecl SP_CombatLineTest(Vec3* pLast, Vec3* pStart, float r, Vec3* pDir,
                                Vec3* pDelta, void* pTarget, int n);          // 0x00cb69e0

// ---- generic collaborator object -------------------------------------------
// Obj stands in for every engine object whose class is not declared here.  Each
// entry point is named after its retail address; all are __thiscall (this in
// ecx) unless the comment says otherwise.
struct Obj {
    int    m_8e7f80();                       // 0x008e7f80  damage-state query
    int    m_104bfa0();                      // 0x0104bfa0  timer limit
    float  m_104be70();                      // 0x0104be70  fuse radius
    bool   m_104cd20();                      // 0x0104cd20
    bool   m_104cd30();                      // 0x0104cd30
    bool   m_104cd60();                      // 0x0104cd60
    bool   m_104cda0();                      // 0x0104cda0
    Obj*   m_104f930();                      // 0x0104f930  cSPSpaceToolData::GetStrategy
    float  m_c41f20();                       // 0x00c41f20
    bool   m_c38990(int a);                  // 0x00c38990
    void   m_ae6970();                       // 0x00ae6970  eastl vector destructor
    void   m_b638b0();                       // 0x00b638b0  SP::cGonzagoTimer::~cGonzagoTimer
    void   m_c432e0();                       // 0x00c432e0
    void   m_b184c0();                       // 0x00b184c0  SP::cGameData::~cGameData
    void   m_c43f90();                       // 0x00c43f90  SP::cLocomotiveObject::Shutdown
    void   m_bc3170();                       // 0x00bc3170  cSPTimer reset
    void   m_aeab40(void* pKey);             // 0x00aeab40
    void   m_cb4ae0(Vec3* pEnd);             // 0x00cb4ae0  cPathFollowingLocomotion::UpdateEndPoint
    Vec3*  m_position();                     // vftable slot 0x2c
    void   m_setPosition(Vec3* p);           // vftable slot 0x38
};

// cSPTimer (only its queries matter to this slice).
struct cSPTimer {
    u8 mPad00[0x10];
    u64 GetElapsedTime();                    // 0x00bc3190  -> edx:eax
    void Start();                            // 0x00bc30f0
    void Reset();                            // 0x00bc3170
};

// cPlanetModel surface queried by the projectile proximity checks.
struct Struct_PlanetModel {
    float GetRadiusAt(void* pPos);           // 0x00b7ef70  (ecx=model, 1 stack arg)
    bool  IsPositionBelowSurface(void* pPos);// 0x00b81f90  (ecx=model, 1 stack arg)
};

// cPathFollowingLocomotion block referenced by the guidance routines.
struct cPathFollowingLocomotion {
    u8   mPad00[0x24];
    int  m24;                                // +0x024
    u8   mPad28[0x30 - 0x28];
    int  m30;                                // +0x030
    void m_cb4ae0(Vec3* pEnd);               // 0x00cb4ae0  UpdateEndPoint
};

// The space-tool data object stored at cGameData+0x518 (it owns the query
// methods 0x0104cd20/30/60, 0x0104bfa0, 0x0104cda0, 0x0104f930).
struct cSPSpaceTool {
    u8    mPad000[0x114];
    void* mpTarget;                          // +0x114
    int   m_104bfa0();                       // 0x0104bfa0
    bool  m_104cd20();                       // 0x0104cd20
    bool  m_104cd30();                       // 0x0104cd30
    bool  m_104cd60();                       // 0x0104cd60
    bool  m_104cda0();                       // 0x0104cda0
    Obj*  m_104f930();                       // 0x0104f930
};

// The state block reachable from a space-tool object's slot-0x5c query.
struct cSpaceToolState {
    u8  mPad000[0x76c];
    int mType;                               // +0x76c
};

// eastl-style intrusive list header (the +0x570 block of cGameData as well as
// the container passed to FUN_00cbb4c0).
struct RefList {
    void*  m00;                              // +0x00
    void*  mSentinelNext;                    // +0x04  points at itself when empty
    void*  mSentinelPrev;                    // +0x08  points at &mSentinelNext
    int    mCount;                           // +0x0c
    u8     mFlag;                            // +0x10
    u8     mPad11[3];
    int    m14;                              // +0x14
    void   m_cbae20(int field);              // 0x00cbae20 (ret 4)
    void   m_cbae70(void* pOut, void** pVal, int b);  // 0x00cbae70 (ret 0xc)
};

// The RB-tree map the serialiser walks (fields read by FUN_00cbb590).
struct RefMap {
    void* m00;                               // +0x00
    void* mSentinel;                         // +0x04  iteration stops here
    void* mRoot;                             // +0x08
    u8    mPad0c[0x14 - 0x0c];
    int   m14;                               // +0x14  non-zero => owned entries
};

// Minimal stand-in for the eastl::wstring temporary used by FUN_00cbb590.
struct WString16 {
    const wchar_t* mpBegin;
    void InitEmpty() { mpBegin = (const wchar_t*)&DAT_014011d0; }
    void InitFrom(const wchar_t* p) { mpBegin = p ? p : (const wchar_t*)&DAT_014011d0; }
    bool Empty() { return mpBegin == (const wchar_t*)&DAT_014011d0; }
    const wchar_t* Begin() { return mpBegin; }
    void Destroy() { }
};

// AutoRefCount<T> helper: the assignment operator at 0x00b5f950.
struct AutoRefCountH {
    void* mpObj;                             // +0x00
    AutoRefCountH* Assign(void* p);          // 0x00b5f950
};

namespace Simulator {

// The "locomotive" base embedded at cGameData+0x34.  Shutdown/position work acts
// on this block (its vftable is the leading dword).
struct cLocomotiveObject {
    void* mVftable;                          // +0x000
    u8    mPad04[0x1c8 - 0x04];
    Vec3  mVec1c8;                           // +0x1c8  == cGameData+0x1fc
    u8    mPad1d4[0x1f0 - 0x1d4];
    int   mField1f0;                         // +0x1f0  == cGameData+0x224
    u8    mPad1f4[0x4d0 - 0x1f4];
    void  m_c432e0();                        // 0x00c432e0
    void  m_c43f90();                        // 0x00c43f90  Shutdown
    void  m_c421b0(void* p);                 // 0x00c421b0
};

// Simulator::cGameData -- `this` is the object base (RemoveOwner's ecx).
// Recovered layout (fields named from the reads/writes of this slice):
//   +0x02c owner                 +0x034 embedded locomotive (0x4d0 bytes)
//   +0x1fc a vector              +0x504 a second vftable (sub-object)
//   +0x518 space tool            +0x51c locomotion   +0x520 last position
//   +0x540/0x544   +0x548 timer  +0x570 list         +0x58c home position
//   +0x598  +0x5cc/0x5d0/0x5d4/0x5d8/0x5dc
struct cGameData {
    u8    mPad00[0x2c];
    void* mpOwner;                           // +0x02c
    u8    mPad30[0x04];
    cLocomotiveObject mLoco;                 // +0x034  (0x4d0 bytes -> +0x504)
    void* mpVtable504;                       // +0x504  sub-object vftable
    u8    mPad508[0x10];
    cSPSpaceTool* mpSpaceTool;               // +0x518
    cPathFollowingLocomotion* mpLocomotion;  // +0x51c
    Vec3  mLastPosition;                     // +0x520
    u8    mPad52c[0x14];
    float mField540;                         // +0x540
    int   mField544;                         // +0x544
    cSPTimer mTimer;                         // +0x548
    u8    mPad558[0x18];
    RefList mList570;                        // +0x570
    u8    mPad588[0x04];
    Vec3  mHomePosition;                     // +0x58c
    int   mField598;                         // +0x598
    u8    mPad59c[0x30];
    void* mpField5cc;                        // +0x5cc
    int   mState5d0;                         // +0x5d0
    void* mpField5d4;                        // +0x5d4
    void* mpField5d8;                        // +0x5d8
    u8    mVector5dc[0x10];                  // +0x5dc  eastl vector

    void FUN_00cbb6f0();                     // 0x00cbb6f0  teardown
    void RemoveOwner();                      // 0x00cbb790
    bool FUN_00cbb840();                     // 0x00cbb840  space-tool update
};

}  // namespace Simulator

// ============================================================================
// @ 0x00cbb020  SP::cFlakProjectile::Update
// `this` is the guidance block embedded at projectile+0x504; the projectile base
// (whose Explode runs) is at this-0x504 and the locomotive at this-0x4d0.
// ============================================================================
namespace SP {

// Projectile base as seen from the guidance block (only what Update touches).
struct cFlakProjectileBody {
    void Explode();                          // 0x00cb9bd0  SP::cFlakProjectile::Explode
    u8   mPad04[0x1fc - 0x04];
    Vec3 mVec1fc;                            // +0x1fc  (Update's [this-0x308])
};

// Guidance block (Update's `this`, embedded at body+0x504).
struct cFlakProjectile {
    u8    mPad00[0x18];
    float mFuseRange;                        // +0x018  (Update's [this+0x18])
    bool  Update();
};

}  // namespace SP

bool SP::cFlakProjectile::Update()
{
    cFlakProjectileBody* body = (cFlakProjectileBody*)((char*)this - 0x504);
    Obj* loco = (Obj*)((char*)this - 0x4d0);

    Vec3* p = loco->m_position();
    Vec3 pos;
    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;
    float dist = sqrtf(pos.z * pos.z + (pos.y * pos.y + pos.x * pos.x));

    if (dist <= this->mFuseRange) {
        Vec3* p2 = loco->m_position();
        Obj* planet = SP_PlanetModel();
        float radius = ((Struct_PlanetModel*)planet)->GetRadiusAt(p2);
        if (radius > dist)
            goto explode;
        return true;
    }

    {
        Vec3 v = body->mVec1fc;
        float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        float nx = -(v.x * inv);
        float ny = -(v.y * inv);
        float nz = -(v.z * inv);
        Vec3 d;
        d.x = nx * nx + pos.x;
        d.y = ny * ny + pos.y;
        d.z = nz * nz + pos.z;
        loco->m_setPosition(&d);
    }

explode:
    body->Explode();
    return false;
}

// ============================================================================
// @ 0x00cbb160  SP::cSpaceDefenseMissile::Update
// `this` is the missile's guidance block; the base is at this-0x504.
// ============================================================================
namespace SP {

struct cMissileBody {
    void Explode();                          // 0x00cba050  SP::cSpaceDefenseMissile::Explode
    u8   mPad04[0x1fc - 0x04];
    Vec3 mVec1fc;                            // +0x1fc
};

struct cSpaceDefenseMissile {
    u8    mPad00[0xdc];
    Obj*  mpFieldDC;                         // +0x0dc  fuse-radius query object
    void* mpVtableE0;                        // +0x0e0  embedded target object (leading vptr)
    cSPTimer mTimer;                         // +0x0e4
    bool  Update();
};

}  // namespace SP

bool SP::cSpaceDefenseMissile::Update()
{
    cMissileBody* body = (cMissileBody*)((char*)this - 0x504);
    Obj* loco = (Obj*)((char*)this - 0x4d0);

    if (SP_PlanetModel() == 0)
        return false;

    {
        u64 elapsed = this->mTimer.GetElapsedTime();
        int limit = this->mpFieldDC->m_104bfa0();
        if ((u32)(elapsed >> 32) > 0u || (u32)elapsed > (u32)limit)
            goto explode;
        if (((Obj*)&this->mpVtableE0)->m_8e7f80() == 2)
            goto explode;

        void* pTarget = ((Fn_p_p)VTSLOT(&this->mpVtableE0, 8))(&this->mpVtableE0);
        Vec3* pa = ((Obj*)pTarget)->m_position();
        Vec3* pb = loco->m_position();
        float dx = pb->x - pa->x;
        float dy = pb->y - pa->y;
        float dz = pb->z - pa->z;
        float dist = sqrtf(dz * dz + (dy * dy + dx * dx));
        float radius = this->mpFieldDC->m_104be70();
        if (radius > dist)
            goto explode;

        Obj* planet = SP_PlanetModel();
        if (((Struct_PlanetModel*)planet)->IsPositionBelowSurface(pb))
            goto explode;

        Vec3* pc = loco->m_position();
        (void)SP_VectorLength(pc);
        float extra = this->mpFieldDC->m_c41f20();
        if (dist > extra)
            goto explode;

        Obj* pIf = SP_InterfaceCast(&this->mpVtableE0);
        if (pIf != 0) {
            if (pIf->m_c38990(1))
                goto explode;
        }
        return true;
    }

explode:
    body->Explode();
    return false;
}

// ============================================================================
// @ 0x00cbb2a0  SP::cCulturalProjectile::Update
// `this` is the guidance block; the base is at this-0x504.
// ============================================================================
namespace SP {

struct cCulturalBody {
    void Explode();                          // 0x00cba690  SP::cCulturalProjectile::Explode
    u8   mPad04[0x1fc - 0x04];
    Vec3 mVec1fc;                            // +0x1fc
};

struct cCulturalProjectile {
    u8    mPad00[0x14];
    cPathFollowingLocomotion* mpLocomotion;  // +0x014
    void* mpField18;                         // +0x018  owner of the damage-state block at +0x508
    Obj*  mpField1c;                         // +0x01c
    int   mField24;                          // +0x024
    Vec3  mEndPoint;                         // +0x028
    u8    mPad34;
    u8    mFlag35;                           // +0x035
    u8    mPad36[0x3c - 0x36];
    cSPTimer mTimer;                         // +0x03c
    bool  Update();
};

}  // namespace SP

bool SP::cCulturalProjectile::Update()
{
    cCulturalBody* body = (cCulturalBody*)((char*)this - 0x504);
    Obj* loco = (Obj*)((char*)this - 0x4d0);

    if (this->mpField18 != 0) {
        Obj* pSub = (Obj*)((char*)this->mpField18 + 0x508);
        if (pSub->m_8e7f80() == 2)
            return false;
        if (((Fn_p_p)VTSLOT(pSub, 0x54))(pSub) != (void*)this->mpField1c)
            return false;
    }
    if (this->mFlag35 != 0 && this->mpLocomotion != 0) {
        if (this->mpLocomotion->m30 == this->mpLocomotion->m24)
            return false;
    }

    {
        u64 e = this->mTimer.GetElapsedTime();
        if ((u32)(e >> 32) != 0u || (u32)e != 0u) {
            u64 e2 = this->mTimer.GetElapsedTime();
            if ((u32)(e2 >> 32) != 0u || (u32)e2 > 2000u)
                return false;
            return true;
        }
    }

    {
        bool bA = false;
        if (this->mpField1c != 0)
            bA = ((Fn_b_pi)VTSLOT(this->mpField1c, 0x5c))(this->mpField1c, (int)0x137e8e0);
        bool bB = false;
        if (this->mpField1c != 0)
            bB = ((Fn_b_pi)VTSLOT(this->mpField1c, 0x5c))(this->mpField1c, (int)0xd0036e08);

        if (bA || bB) {
            void* pN1 = ((Fn_p_p)VTSLOT(this->mpField1c, 8))(this->mpField1c);
            Vec3* src = ((Obj*)pN1)->m_position();
            if ((this->mEndPoint.x != src->x || this->mEndPoint.y != src->y || this->mEndPoint.z != src->z)
                && this->mpLocomotion != 0) {
                if (this->mField24 == -1) {
                    void* pN2 = ((Fn_p_p)VTSLOT(this->mpField1c, 8))(this->mpField1c);
                    Vec3* s2 = ((Obj*)pN2)->m_position();
                    this->mEndPoint.x = s2->x;
                    this->mEndPoint.y = s2->y;
                    this->mEndPoint.z = s2->z;
                    if (bA) {
                        Vec3 n;
                        SP_NormalizedSafe(&n, &this->mEndPoint);
                        this->mEndPoint.x += n.x * DAT_01486110;
                        this->mEndPoint.y += n.y * DAT_01486110;
                        this->mEndPoint.z += n.z * DAT_01486110;
                    }
                } else {
                    Vec3* v = ((Fn_v3_ppi)VTSLOT(this->mpField1c, 0x28))(this->mpField1c, &this->mEndPoint, this->mField24);
                    this->mEndPoint.x = v->x;
                    this->mEndPoint.y = v->y;
                    this->mEndPoint.z = v->z;
                }
                this->mpLocomotion->m_cb4ae0(&this->mEndPoint);
            }
        }

        Vec3* pos = loco->m_position();
        float dx = this->mEndPoint.x - pos->x;
        float dy = this->mEndPoint.y - pos->y;
        float dz = this->mEndPoint.z - pos->z;
        if (sqrtf(dx * dx + dy * dy + dz * dz) < DAT_01470f1c) {
            this->mTimer.Start();
            body->Explode();
        }
    }
    return true;
}

// ============================================================================
// @ 0x00cbb4c0  FUN_00cbb4c0  (__cdecl) -- read a RefList from a stream
// ============================================================================
void __cdecl FUN_00cbb4c0(Obj* pStream, RefList* pList)
{
    pList->m_cbae20(pList->mCount);
    pList->mSentinelNext = &pList->mSentinelNext;
    pList->mSentinelPrev = &pList->mSentinelNext;
    pList->mCount = 0;
    pList->mFlag = 0;
    pList->m14 = 0;

    {
        int count = 0;
        void* pReader = ((Fn_p_p)VTSLOT(pStream, 0x20))(pStream);
        void* pIn = ((Fn_p_p)VTSLOT(pReader, 0x18))(pReader);
        EA_IO_ReadInt32(pIn, &count, 1, 0);

        for (u32 i = 0; i < (u32)count; ++i) {
            void* tmp = 0;
            ((Fn_v_pppp)VTSLOT(pStream, 0x28))(pStream, (void*)&DAT_01186577, &tmp, 0);
            ((Fn_v_p)VTSLOT(pStream, 0x1c))(pStream);
            void* out;
            pList->m_cbae70(&out, &tmp, 0);
            if (tmp != 0)
                ((Fn_v_p)VTSLOT(tmp, 0xc0))(tmp);
        }
        ((Fn_v_p)VTSLOT(pStream, 0x1c))(pStream);
    }
}

// ============================================================================
// @ 0x00cbb590  FUN_00cbb590  (__cdecl) -- write a labelled RefMap to a stream
// ============================================================================
bool __cdecl FUN_00cbb590(Obj* pStream, const wchar_t* pName, RefMap* pMap)
{
    bool ok = true;
    if (pMap->m14 == 0)
        return ok;

    {
        WString16 label;
        wchar_t conv[8];
        if (pName == 0)
            label.InitEmpty();
        else
            label.InitFrom(EA_ConvertToString16(conv, pName, -1));

        const wchar_t* pText = label.Empty() ? (const wchar_t*)&DAT_014011d0 : label.Begin();
        ((Fn_v_pp)VTSLOT(pStream, 0))(pStream, (void*)pText);

        void* pEnd = &pMap->mSentinel;
        for (void* node = pMap->mRoot; node != pEnd; node = eastl_RBTreeIncrement(node)) {
            if (ok)
                ok = FUN_00ac8050(pStream, 0, (char*)node + 0x10) != 0;
        }

        ((Fn_v_pp)VTSLOT(pStream, 4))(pStream, (void*)pText);
        label.Destroy();
    }
    return ok;
}

// ============================================================================
// @ 0x00cbb6f0  Simulator::cGameData::FUN_00cbb6f0  -- teardown
// ============================================================================
void Simulator::cGameData::FUN_00cbb6f0()
{
    ((Obj*)&mVector5dc)->m_ae6970();

    if (mpField5d8 != 0)
        ((Fn_v_p)VTSLOT(mpField5d8, 0xc0))(mpField5d8);
    if (mpField5d4 != 0)
        ((Fn_v_p)VTSLOT(mpField5d4, 4))(mpField5d4);
    if (mpField5cc != 0)
        ((Fn_v_p)VTSLOT(mpField5cc, 4))(mpField5cc);

    RefList* pList570 = &mList570;
    pList570->m_cbae20(pList570->mCount);

    ((Obj*)&mTimer)->m_b638b0();

    if (mpLocomotion != 0) {
        void* p = mpLocomotion;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }
    if (mpSpaceTool != 0) {
        void* p = mpSpaceTool;
        ((Fn_v_p)VTSLOT(p, 8))(p);
    }

    cLocomotiveObject* pLoco = &mLoco;
    mpVtable504 = (void*)0x145dca8;
    pLoco->m_c432e0();
    ((Obj*)this)->m_b184c0();
}

// ============================================================================
// @ 0x00cbb790  Simulator::cGameData::RemoveOwner
// ============================================================================
void Simulator::cGameData::RemoveOwner()
{
    if (mpSpaceTool != 0) {
        void* p = mpSpaceTool;
        mpSpaceTool = 0;
        ((Fn_v_p)VTSLOT(p, 8))(p);
    }
    if (mpLocomotion != 0) {
        void* p = mpLocomotion;
        mpLocomotion = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }

    RefList* pList = &mList570;
    pList->m_cbae20(pList->mCount);
    pList->mSentinelPrev = &pList->mSentinelNext;
    pList->mCount = 0;
    pList->mFlag = 0;
    pList->m14 = 0;
    pList->mSentinelNext = &pList->mSentinelNext;

    if (mpField5cc != 0) {
        void* p = mpField5cc;
        mpField5cc = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }
    if (mpField5d4 != 0) {
        void* p = mpField5d4;
        mpField5d4 = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }
    if (mpOwner != 0) {
        void* p = mpOwner;
        mpOwner = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }

    mLoco.m_c43f90();
}

// ============================================================================
// @ 0x00cbb840  Simulator::cGameData::FUN_00cbb840  -- space-tool update ring
// ============================================================================
bool Simulator::cGameData::FUN_00cbb840()
{
    bool bForce = false;
    Vec3 start = *((Obj*)&mLoco)->m_position();
    float range = 0.0f;
    bool bHit = false;
    bool bMode13 = false;

    if (mpLocomotion != 0 && mpLocomotion->m30 == mpLocomotion->m24)
        goto L_force;

    if (!mpSpaceTool->m_104cd30())
        goto L_after;

    {
        void* pTarget = 0;
        if (mpField5d8 != 0) {
            pTarget = ((Fn_p_pi)VTSLOT(mpField5d8, 0xb8))(mpField5d8, (int)&DAT_013f94d4);
            if (pTarget != 0) {
                void* pObj = ((Fn_p_p)VTSLOT(pTarget, 0xc))(pTarget);
                if (((Fn_b_p)VTSLOT(pObj, 0x2c))(pObj))
                    return false;
                if (((Obj*)pTarget)->m_8e7f80() == 2)
                    return false;
            }
        }

        if (SP_GetCurrentGameMode() == (void*)&DAT_01654c05 && SP_GetUniverseContext() == 2) {
            range = DAT_013eb960;
            if (pTarget != 0) {
                void* pX = ((Fn_p_pi)VTSLOT(pTarget, 0x5c))(pTarget, (int)0xb033b403);
                if (pX != 0 && ((cSpaceToolState*)pX)->mType == 3)
                    return false;
            }
        } else {
            range = DAT_014853e0;
        }

        if (mpLocomotion == 0) {
            Vec3* p2 = ((Obj*)&mLoco)->m_position();
            float dx = p2->x - mHomePosition.x;
            float dy = p2->y - mHomePosition.y;
            float dz = p2->z - mHomePosition.z;
            if (sqrtf(dx * dx + dy * dy + dz * dz) > range)
                goto L_force;
        }
    }
    goto L_after;

L_force:
    bForce = true;

L_after:
    AutoRefCountH refTemp;
    refTemp.mpObj = 0;
    mState5d0 = 3;
    {
        int limit = mpSpaceTool->m_104bfa0();
        u64 elapsed = mTimer.GetElapsedTime();
        if (elapsed >= (u64)(u32)limit)
            bHit = true;
    }
    if (mpSpaceTool->m_104cd60())
        goto L_slow;

    {
        Vec3* p3 = ((Obj*)&mLoco)->m_position();
        Vec3 delta;
        delta.x = p3->x - mLastPosition.x;
        delta.y = p3->y - mLastPosition.y;
        delta.z = p3->z - mLastPosition.z;
        float dist = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        if (!(dist > 0.0f))
            goto L_slow;

        float inv = DAT_01485720 / dist;
        Vec3 dir;
        dir.x = delta.x * inv;
        dir.y = delta.y * inv;
        dir.z = delta.z * inv;

        void* pTarget2 = 0;
        if (mpSpaceTool->mpTarget != 0)
            pTarget2 = ((Fn_p_pi)VTSLOT(mpSpaceTool->mpTarget, 0xb8))(mpSpaceTool->mpTarget, (int)&DAT_013f94d4);

        bMode13 = (SP_GetCurrentGameMode() == (void*)&DAT_01654c10);
        bool bFlag = mpSpaceTool->m_104cd20();
        if (bMode13 || bFlag) {
            int r = FUN_00cb6a50(&start, dist, &dir, &mLastPosition);
            mState5d0 = r;
            if (r != 3)
                bHit = true;
            if (bFlag)
                goto L_slow;
        }

        if (bHit)
            goto L_reconfig;

        int r2 = SP_CombatLineTest(&mLastPosition, &start, dist, &dir, &delta, pTarget2, 4);
        mState5d0 = r2;
        if (mpField5d8 != 0 && mpSpaceTool->m_104cd30()) {
            if (mState5d0 != 0)
                goto L_proceed;
            goto L_reconfig;
        }
        if (mState5d0 == 3)
            goto L_proceed;
        goto L_reconfig;
    }

L_slow:
    if (bHit)
        goto L_reconfig;

L_proceed:
    if (mpLocomotion == 0) {
        Vec3* p4 = ((Obj*)&mLoco)->m_position();
        float dx = p4->x - mHomePosition.x;
        float dy = p4->y - mHomePosition.y;
        float dz = p4->z - mHomePosition.z;
        if (sqrtf(dx * dx + dy * dy + dz * dz) < DAT_01475160)
            goto L_reconfig;
    }
    goto L_far;

L_reconfig:
    if (mpSpaceTool->m_104cd60() && mpSpaceTool->m_104cd30() && mpField5d8 != 0) {
        mState5d0 = 0;
        void* q = FUN_00ad2670(&mpField5d8);
        refTemp.Assign(q);
    }
    {
        void* ebxVal = refTemp.mpObj;
        mLoco.m_c421b0(0);
        mField544 = 1;
        mLoco.mField1f0 = 5;
        mField540 = 0.0f;
        mTimer.Reset();
        mLoco.mVec1c8.x = 0.0f;
        mLoco.mVec1c8.y = 0.0f;
        mLoco.mVec1c8.z = 0.0f;

        mList570.m_cbae20(mList570.mCount);
        mList570.mSentinelNext = &mList570.mSentinelNext;
        mList570.mSentinelPrev = &mList570.mSentinelNext;
        mList570.mCount = 0;
        mList570.mFlag = 0;
        mList570.m14 = 0;

        {
            void* pOld = mpField5d4;
            if (ebxVal != pOld) {
                if (ebxVal != 0)
                    ((Fn_v_p)VTSLOT(ebxVal, 0))(ebxVal);
                mpField5d4 = ebxVal;
                if (pOld != 0)
                    ((Fn_v_p)VTSLOT(pOld, 4))(pOld);
            }
        }

        ((Obj*)&mLoco)->m_setPosition(&start);

        if (mpSpaceTool != 0 && !mpSpaceTool->m_104cda0()) {
            Obj* pStrat = mpSpaceTool->m_104f930();
            if (pStrat != 0)
                ((Fn_Slot30)VTSLOT(pStrat, 0x30))(pStrat, mpSpaceTool, &mLastPosition,
                                                  mState5d0, mpField5d4);
        }

        if (refTemp.mpObj != 0) {
            void* p = refTemp.mpObj;
            ((Fn_v_p)VTSLOT(p, 4))(p);
        }
    }
    goto L_tail;

L_far:
    if (mpField5d8 != 0 && mpSpaceTool->m_104cd30() && mpLocomotion != 0) {
        void* pRes = FUN_00ae3330(&mpField5d8);
        Vec3* pHome = ((Fn_v3_ppi)VTSLOT(pRes, 0x28))(pRes, &mHomePosition, mField598);
        mHomePosition.x = pHome->x;
        mHomePosition.y = pHome->y;
        mHomePosition.z = pHome->z;
        mpLocomotion->m_cb4ae0(&mHomePosition);
    }

L_tail:
    {
        Vec3* p5 = ((Obj*)&mLoco)->m_position();
        mLastPosition.x = p5->x;
        mLastPosition.y = p5->y;
        mLastPosition.z = p5->z;
    }
    return true;
}