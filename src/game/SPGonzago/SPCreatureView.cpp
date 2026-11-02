// src/game/SPGonzago/SPCreatureView.cpp -- migrated from slice(s) s00e8c120, s00e8b7a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_vtbl_014863cc[];   // 0x014863cc  SP::cCreatureView vftable
extern void* g_vtbl_01455648[];   // 0x01455648  view base vftable
#include <math.h>
#include "SP/cAnimatingCreature.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"

// ---- items of slice s00e8b7a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
extern void* g_vtbl_014863cc[];   // 0x014863cc  SP::cCreatureView vftable
extern void* g_vtbl_01455648[];   // 0x01455648  view base vftable
extern u32   g_15a881c;           // 0x015a881c
u32  GetCurrentGameMode();                                             // 0x00b5b800
void* operator new(u32 size, const char* pName, int flags, unsigned dbgFlags,
                   const char* pFile, int line);                       // 0x00f473a0
void  operator delete(void* p);                                        // 0x00f47380
__forceinline void* vcall1(void* p, u32 off, void* a)
{ return ((void*(__thiscall*)(void*, void*))(*(void***)p)[off >> 2])(p, a); }
__forceinline u8 vbool0(void* p, u32 off)
{ return ((u8(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline u32 vint0(void* p, u32 off)
{ return ((u32(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline void vvoid0(void* p, u32 off)
{ ((void(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline void vvoid1(void* p, u32 off, u32 a)
{ ((void(__thiscall*)(void*, u32))(*(void***)p)[off >> 2])(p, a); }
class cCombatSub {
public:
    void** mpVtbl;              // +0x00
    u32  FUN_008e7f80();        // 0x008e7f80
    bool FUN_00bfc600();        // 0x00bfc600
};
class cCreature {
public:
    void** mpVtbl;              // +0x00
    char pad04[0x34 - 0x04];
    void** mpVtbl34;            // +0x34  polymorphic sub-object (slot 0x74 = a float)
    char pad38[0x6e - 0x38];
    u8   m6e;                   // +0x6e
    char pad6f[0x84 - 0x6f];
    u32  m84;                   // +0x84
    char pad88[0xc0 - 0x88];
    void** mpVtblC0;            // +0xc0  animation sub-object (slot 0x8c)
    char padC4[0x330 - 0xc4];
    u32  m330;                  // +0x330
    char pad334[0x588 - 0x334];
    cCombatSub mCombat;         // +0x588
    char pad58c[0x684 - 0x58c];
    i32  m684;                  // +0x684
    char pad688[0xb58 - 0x688];
    u32  mFlagsB58;             // +0xb58
    char padB5c[0xb5e - 0xb5c];
    u8   mB5e;                  // +0xb5e
    char padB5f[0xb61 - 0xb5f];
    u8   mB61;                  // +0xb61
    u8   mB62;                  // +0xb62
    char padB63[0xf90 - 0xb63];
    u8   mF90;                  // +0xf90

    // direct (non-virtual) members -------------------------------------------
    bool FUN_00c8b220(u32 a, u32 b, u32 c, u32 d);   // 0x00c8b220
    void FUN_00c88a00(u32 a, float f);               // 0x00c88a00
    void FUN_00c8a020(u32 a, float f);               // 0x00c8a020
    void FUN_00c88a30(u32 a, void* b);               // 0x00c88a30
    void* FUN_00c14e70(u32 id);                      // 0x00c14e70
    void FUN_00c17350(u32 id, u32 b);                // 0x00c17350
    void FUN_00c1d400(u32 a, u32 b);                 // 0x00c1d400
    void FUN_00c1d460(u32 a, u32 b);                 // 0x00c1d460
    bool FUN_00c0b780();                             // 0x00c0b780
    bool FUN_00c0b7a0();                             // 0x00c0b7a0
    bool FUN_00c0c0e0();                             // 0x00c0c0e0
    void FUN_00c201a0(bool v, u32 a, u32 b);         // 0x00c201a0
};
class cEffect {
public:
    char pad00[0x88];
    u32  m88;                   // +0x88
    void Release();             // 0x00a05270
};
class cAnimSub {
public:
    void* FUN_00c41ec0();       // 0x00c41ec0
};
class cSubState {
public:
    char pad00[0x6c];
    float m6c;                  // +0x6c
};
namespace SP {
class cCreatureView {
public:
    void** mpVtbl;              // +0x00
    u32    m04;                 // +0x04
    u32    m08;                 // +0x08
    cCreature* mpCreature;      // +0x0c
    cEffect*   mpOverhead;      // +0x10
    u8     mb14;                // +0x14
    char   pad15[0x18 - 0x15];
    void*  mp18;                // +0x18

    cCreatureView();                                    // 0x00e8bc80
    void FUN_00e8bca0(cCreature* p);                    // 0x00e8bca0
    void FUN_00e8bd70(bool b);                          // 0x00e8bd70
    bool FUN_00e8bda0();                                // 0x00e8bda0
    void FUN_00e8bdc0();                                // 0x00e8bdc0
    void UpdateInteractionEffects();                    // 0x00e8be60
    void UpdateMotiveEffects();                         // 0x00e8bf20
    void FUN_00e8c030();                                // 0x00e8c030
    cCreatureView* FUN_00e8c0c0(u8 f);                  // 0x00e8c0c0
    void CreatureCitizenUpdate(cCreature* p);           // 0x00e8c070
};
}
namespace SP {
SP::cCreatureView* __stdcall FUN_00e8bd10(void* pSrc);  // 0x00e8bd10
}
// ---- items of slice s00e8b7a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   g_15a881c;           // 0x015a881c

// ---- items of slice s00e8c120 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gFadeFarSq;          // 0x015a87fc
extern float gFadeNearSq;         // 0x015a8800
extern float gLodNearSq;          // 0x015a8804
extern float gLodMidSq;           // 0x015a8808
extern int   gTerrainPropVersion; // 0x016c4bcc
extern float kEffectNearDist;      // 0x01581338
extern float kFadeStep;            // 0x013f26dc
extern float kFadeMul;             // 0x013f9428
extern float kFadeBias;            // 0x013f4fd0
extern float kFadeLow;             // 0x013ec480
typedef unsigned short     u16;
void* operator new(u32 size, u32 tag, int a, int b, int c, int d);
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Mat3 { float m[9]; };
struct XformMsg {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    Vec3  pos;        // +0x04
    float scale;      // +0x10
    Mat3  rot;        // +0x14
    XformMsg();       // 0x00434040
};
struct Transform {
    u16   flags;
    u16   count;
    Vec3  pos;
    float scale;
    Mat3  rot;
    Transform();                                  // 0x00409930
    void SetB(const Vec3& up, const Vec3& dir);   // 0x006ba840 (MatOwner::SetB)
    void SetPosition(const Vec3& v) { flags |= 4; ++count; pos = v; }
    void SetScale(float s) { scale = s; ++count; }
};
struct cPlanetModel_s00e8_c120 {
    void FUN_00b7e3b0(Vec3* out, const Vec3* in);          // 0x00b7e3b0
    const Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in);   // 0x00b815a0
};
cPlanetModel_s00e8_c120* PlanetModel();                      // 0x00b3d350
int  GetCurrentGameMode_s00e8_c120();                        // 0x00b5b800
bool Vector3Equal(const Vec3* a, const Vec3* b);  // 0x004232c0 (cdecl)
float* Matrix3FromQuaternion(float* out, const void* q);   // 0x0059c190 (cdecl)
bool GetFloatProperty(const void* obj, u32 id, float* out); // 0x0040cf10 (cdecl)
extern Vec3  gReferencePos;       // 0x0167ea30
extern Vec3  gZeroVec;            // 0x016c4bd8
float FUN_005a6e00(float x);       // 0x005a6e00
void* FUN_00e8bca0(void* self, void* tracked);   // 0x00e8bca0
void  FUN_00e8be60(void* self);    // 0x00e8be60
void  FUN_00e92a10(void* c);       // 0x00e92a10
struct cPropertyList_s00e8_c120 {
    int GetModificationCount();       // 0x006237a0
};
struct cTerrainRecord {
    char pad[0x30];
    cPropertyList_s00e8_c120* mpProps;   // +0x30
    int  mVersion;            // +0x34
};
struct cTerrainMgr {
    cTerrainRecord* Fn2();            // 0x00b1de80
};
cTerrainMgr* GetTerrainMgr();                               // 0x00b3d320
struct cGameState { char pad[0xcc]; int mMode; };
extern cGameState* gGameState;                              // 0x016c7aa4
struct cIVisualEffect {
    void AddRef();                    // 0x00a02c30
    void Release();                   // 0x00a05270
    char pad[0x80];
    float mAlpha;                     // +0x80
    char pad2[0x128 - 0x84];
    struct cEffectParam* mp128;       // +0x128
    int   m12c;                       // +0x12c
    int   m130;                       // +0x130
    char pad3[0x180 - 0x134];
    struct cEffectState* mpState;     // +0x180
    void SetShown(int b);             // 0x00a047d0
    int  GetLevel();                  // 0x00a02bd0
    bool  IsInView();                 // 0x00c35d10
    void  FUN_00c35b60();             // 0x00c35b60
    void  FUN_00c88530(float d);      // 0x00c88530
};
struct cEffectState { int pad; u32 mFlags; };   // +4: bit0 "interactable", bit14, bit18
struct cEffectParam {
    int  FUN_00c22850();                          // 0x00c22850
    void FUN_00c22870();                          // 0x00c22870
    void FUN_00c23300(const void* c, int f);      // 0x00c23300
};
struct cTransform34 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
    virtual void SetDist(float d);                // slot 16 (+0x40)  0x00c88530
    char pad[0x34];
};
struct cEffectsMgr {
    char pad[0x20];
    bool mEnabled;
    void Place(Transform* t, float f);   // 0x00ac7680
};
cEffectsMgr* GetEffectsMgr();            // 0x00b3d370
struct cMsgTarget {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void Send(XformMsg* m);      // slot 6 (+0x18)
    virtual void s7();
    virtual void Prepare(XformMsg* m);   // slot 8 (+0x20)
};
struct cAnimComp {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void s10();
    virtual const Vec3* GetPosition();            // slot 11 (+0x2c)
    virtual const void* GetOrientation();         // slot 12 (+0x30)
    virtual float GetScale();                     // slot 13 (+0x34)
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual bool IsReady();                       // slot 18 (+0x48)
    virtual void SetFlag(bool b);                 // slot 19 (+0x4c)
virtual void s20();
virtual void s21();
    virtual bool IsActive();                      // slot 22 (+0x58)
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual float GetHeight();                    // slot 28 (+0x70)
    virtual float GetRadius();                    // slot 29 (+0x74)
    char pad0[0x50 - 4];
    u32  mStateFlags;                             // +0x50 (creature +0x110); bit 11 = "needs name effect"
    char pad1[0x68 - 0x54];
    float mViewDistance;                          // +0x68 (creature +0x128)
    char pad2[0x74 - 0x6c];
    bool mDirty;                                  // +0x74 (creature +0x134)
    bool mHasView;                                // +0x75 (creature +0x135)
    bool pad3;
    bool mOnPlanet;                               // +0x77 (creature +0x137)
    bool IsDirty() const { return mDirty; }
    bool ConsumeDirty() { if (mDirty) { mDirty = false; return true; } return false; }
    void ClearNeedsNameEffect() { mStateFlags &= ~0x800u; }
    bool NeedsNameEffect() const { return (mStateFlags & 0x800) != 0; }
    void FUN_00c89d60(Transform* t);              // 0x00c89d60
    void FUN_00c8aa60();                          // 0x00c8aa60
};
struct cCreatureState { char pad[0x648]; int mCount648; char pad2[0x694 - 0x64c]; u32 mCount694; char pad3[0x69c - 0x698]; u32 mCount69c; };
class cAnimatingBase {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual u32  GetType();                       // slot 8 (+0x20)
    char pad0[0xc0 - 4];
};
class cAnimatingCreature_s00e8_c120 : public cAnimatingBase, public cAnimComp {   // cAnimComp subobject at +0xc0
public:
    char pad1[0x330 - 0x138];
    int  m330;                                    // +0x330
    char pad2[0xb20 - 0x334];
    cCreatureState* mpState;                      // +0xb20
    char pad3[0xb54 - 0xb24];
    cIVisualEffect* mpOverheadEffect;             // +0xb54
    u32  mFlagsB58;                               // +0xb58 (bit 9 = fixed LOD)
    char pad4[0xb5d - 0xb5c];
    bool mbB5D;                                   // +0xb5d
    bool mbB5E;                                   // +0xb5e
    char pad5[0xbb0 - 0xb5f];
    bool mbBB0;                                   // +0xbb0
    char pad6[0xe58 - 0xbb1];
    float mfE58;                                  // +0xe58
    char pad7[0xe68 - 0xe5c];
    bool mbE68;                                   // +0xe68
    char pad8[0xf90 - 0xe69];
    bool mbF90;                                   // +0xf90

    void SetLOD(int lod);                         // 0x00c0c300
    const Vec3* GetBasePosition();                // 0x00c0e580
    bool FUN_00c0c130();                          // 0x00c0c130
    bool FUN_00c0c0e0();                          // 0x00c0c0e0
    void SetEffectParam(bool v, u32 hash, u32 id);   // 0x00c201a0
    cMsgTarget* FindEffect(u32 id);               // 0x00c14e70
    void KillEffect(u32 id, int flag);            // 0x00c17350
    void CreateEffect(u32 hash, u32 id);          // 0x00c1d400
    bool IsInView();                              // 0x00c35d10
    void FUN_00c35b60();                          // 0x00c35b60
    float FUN_00c41ec0();                         // 0x00c41ec0
    cTransform34* mp34;                           // +0x34
};
namespace SP {
class cCreatureView_s00e8_c120 {
public:
    virtual void v0();
    virtual void HandleSimulationUpdate(int a, int b);   // slot 1 (+4) 0x00e8c120
virtual void v2();
virtual void v3();
    virtual void SetOverheadShown(bool b);        // slot 4 (+0x10)
    virtual void v5();
    virtual void SetOverheadActive(bool b);       // slot 6 (+0x18)
    virtual bool IsOverheadActive();              // slot 7 (+0x1c)

    char pad0[8];
    cAnimatingCreature_s00e8_c120* mpCreature;               // +0x0c
    cIVisualEffect* mpOverheadEffect;             // +0x10
    bool mbShowOverhead;                          // +0x14
    char pad1[3];
    int  mState;                                  // +0x1c  0/1/2 effect lifecycle state
    float mAccum;                                 // +0x20  accumulated fade accumulator

    void UpdateMotiveEffects();                   // 0x00e8bf20
    void CreatureCitizenUpdate(cAnimatingCreature_s00e8_c120* c);   // 0x00e8c070
    void HandleUpdate(int a, int b);              // 0x00e8ca10
    void HandleMessage(int a, int b);             // 0x00e8cf50
};
}
namespace SP {
struct cTrackedEffect {
    void* mpVtbl;        // +0x00
    u32   m04;           // +0x04
    u32   m08;           // +0x08
    u32   m0c;           // +0x0c
    u32   m10;           // +0x10
    u8    mb14;          // +0x14
    char  pad[3];
    u32   m18;           // +0x18
    u32   m1c;           // +0x1c
    float m20;           // +0x20
};
}
namespace SP {
class cEffectView {
public:
    virtual void v0();
    virtual void HandleUpdate(int a, int b);      // slot 1 (+4)
virtual void v2();
virtual void v3();
    virtual void SetShown(bool b);                // slot 4 (+0x10)
    virtual void v5();
    virtual void SetActive(bool b);               // slot 6 (+0x18)
    virtual bool IsActive();                      // slot 7 (+0x1c)

    char pad0[8];
    cAnimatingCreature_s00e8_c120* mpCreature;               // +0x0c
    cIVisualEffect* mpEffect;                     // +0x10
    bool mbActive;                                // +0x14
    char pad1[3];
    Vec3  mVec;                                   // +0x18
    u32   m24;                                    // +0x24
    u32   m28;                                    // +0x28
    u32   m2c;                                    // +0x2c
    u32   m30;                                    // +0x30
    u32   m34;                                    // +0x34
    u32   m38;                                    // +0x38
    u32   m3c;                                    // +0x3c

    void SetTrackedEffect(cAnimatingCreature_s00e8_c120* c); // 0x00e8c9a0
    cEffectView* Initialize();                    // 0x00e8cc90
    Vec3* ComputeFade(Vec3* out, int& ok, void* c);   // 0x00e8cd30
    cEffectView* CreateFor(cAnimatingCreature_s00e8_c120* c);                  // 0x00e8cec0
    void HandleMessage(int a, int b);             // 0x00e8cf50
};
}
static __forceinline bool Bit(u32 v, int n) { u8 b = (u8)(v >> n); return (b & 1) != 0; }
static __forceinline void AssignEffect(cIVisualEffect*& dst, cIVisualEffect* src)
{
    cIVisualEffect* old = dst;
    if (src != old) {
        if (src) src->AddRef();
        dst = src;
        if (old) old->Release();
    }
}
#define SEND_SCALE(T, C, GETTER) do { \
        XformMsg m; \
        (T)->Prepare(&m); \
        m.scale = (C)->GETTER(); \
        m.count += 1; \
        (T)->Send(&m); } while (0)
// ---- items of slice s00e8c120 end

// @ 0x00e8bca0
void SP::cCreatureView::FUN_00e8bca0(cCreature* p)
{
    cCreature* pOld = mpCreature;
    if (p != pOld) {
        if (p != 0)
            vvoid0(p, 0x00);            // AddRef
        mpCreature = p;
        if (pOld != 0)
            vvoid0(pOld, 0x04);         // Release
    }
    // reset the creature's animation sub-object at +0xc0 (slot 0x8c, argument 0)
    vvoid1((char*)mpCreature + 0xc0, 0x8c, 0);
    u32 flags = p->mFlagsB58;
    bool bStunned = ((flags >> 9) & 1) != 0;
    if (bStunned || p->FUN_00c0c0e0())
        mb14 = 0;
}

// @ 0x00e8bd10
SP::cCreatureView* __stdcall SP::FUN_00e8bd10(void* pSrc)
{
    void* pArg = pSrc != 0 ? vcall1(pSrc, 0x0c, (void*)0xce9f6639) : 0;
    SP::cCreatureView* pView =
        new ("Simulator/cCreatureView", 0, 0, 0, 0) SP::cCreatureView;
    pView->FUN_00e8bca0((cCreature*)pArg);
    return pView;
}

// @ 0x00e8bd70
void SP::cCreatureView::FUN_00e8bd70(bool b)
{
    cEffect* p = mpOverhead;
    if (p != 0) {
        if (b)
            p->m88 |= 1u;
        else
            p->m88 &= ~1u;
    }
    if (mpCreature != 0)
        mpCreature->mF90 = b;
}

// @ 0x00e8bda0
bool SP::cCreatureView::FUN_00e8bda0()
{
    if (mpOverhead != 0)
        return (mpOverhead->m88 & 1) != 0;
    return false;
}

// @ 0x00e8bdc0
void SP::cCreatureView::FUN_00e8bdc0()
{
    if (mp18 != 0) {
        vvoid1(mp18, 0x0c, 1);
        if (mp18 != 0) {
            void* p18 = mp18;
            mp18 = 0;
            vvoid0(p18, 0x04);
        }
    }
    if (mpCreature->FUN_00c14e70(0x73e4cdf) != 0)
        mpCreature->FUN_00c17350(0x73e4cdf, 0);
    if (mpCreature->FUN_00c14e70(0x7e2fedf) != 0)
        mpCreature->FUN_00c17350(0x7e2fedf, 0);
    if (mpCreature != 0) {
        cCreature* p = mpCreature;
        mpCreature = 0;
        vvoid0(p, 0x04);
    }
    if (mpOverhead != 0) {
        cEffect* p = mpOverhead;
        mpOverhead = 0;
        p->Release();
    }
}

// @ 0x00e8be60
void SP::cCreatureView::UpdateInteractionEffects()
{
    if (!vbool0(mpCreature, 0xa0))
        return;
    mpCreature->FUN_00c17350(0x62edba5, 0);
    switch (vint0(mpCreature, 0x98)) {
    case 1:
        mpCreature->FUN_00c1d400(0xd8b86866, 0x62edba5);
        return;
    case 2:
        mpCreature->FUN_00c1d400(0xa01d381f, 0x62edba5);
        return;
    case 3:
        mpCreature->FUN_00c1d400(0xa31d75a8, 0x62edba5);
        return;
    case 4:
        mpCreature->FUN_00c1d400(0x121dd1fe, 0x62edba5);
        return;
    case 5:
        mpCreature->FUN_00c1d400(0x7a16b9e7, 0x62edba5);
        break;
    }
}

// @ 0x00e8bf20
void SP::cCreatureView::UpdateMotiveEffects()
{
    int iVar2 = (int)vint0(mpCreature, 0xa4);

    if (((mpCreature->m330 & 1) != 0) &&
        ((cSubState*)((cAnimSub*)((char*)mpCreature + 0xc0))->FUN_00c41ec0())->m6c > 5.0f) {
        if (mpCreature->FUN_00c14e70(0x6885174) != 0)
            return;
        mpCreature->FUN_00c1d460(0x57619fab, 0x6885174);
        mpCreature->FUN_00c17350(0x62edba6, 0);
        return;
    }
    if (vbool0(mpCreature, 0xa8) != 0) {
        mpCreature->mB61 = 0;
        mpCreature->FUN_00c17350(0x6885174, 0);
        mpCreature->FUN_00c17350(0x62edba6, 0);
        // the original keeps the two `cmp edi,2 / jl` and `cmp edi,3 / jg` separate
        // (cl folds `if (i<2) return; if (i>3) return;` into one range test)
        switch (iVar2) {
        case 2:
        case 3:
            break;
        default:
            return;
        }
        if (mpCreature->FUN_00c0b780() && mpCreature->FUN_00c0b7a0()) {
            mpCreature->FUN_00c1d460(0xbde1a55d, 0x62edba6);
            return;
        }
        if (mpCreature->FUN_00c0b7a0())
            mpCreature->FUN_00c1d460(0xde4f1682, 0x62edba6);
        else
            mpCreature->FUN_00c1d460(0x275458db, 0x62edba6);
        return;
    }
    mpCreature->FUN_00c17350(0x6885174, 0);
}

// @ 0x00e8c030
void SP::cCreatureView::FUN_00e8c030()
{
    mpVtbl = g_vtbl_014863cc;
    FUN_00e8bdc0();
    if (mp18 != 0)
        vvoid0(mp18, 0x04);
    if (mpOverhead != 0)
        mpOverhead->Release();
    if (mpCreature != 0)
        vvoid0(mpCreature, 0x04);
    mpVtbl = g_vtbl_01455648;
}

// @ 0x00e8c070
void SP::cCreatureView::CreatureCitizenUpdate(cCreature* p)
{
    UpdateInteractionEffects();
    if (GetCurrentGameMode() == 0x1654c05) {
        bool v = (p->mB62 != 0) && (p->mB5e == 0);
        mpCreature->FUN_00c201a0(v, g_15a881c, 0x372a3c5);
    }
}

// @ 0x00e8c0c0
SP::cCreatureView* SP::cCreatureView::FUN_00e8c0c0(u8 f)
{
    mpVtbl = g_vtbl_014863cc;
    FUN_00e8bdc0();
    if (mp18 != 0)
        vvoid0(mp18, 0x04);
    if (mpOverhead != 0)
        mpOverhead->Release();
    if (mpCreature != 0)
        vvoid0(mpCreature, 0x04);
    u8 bDelete = f & 1;
    mpVtbl = g_vtbl_01455648;
    if (bDelete)
        operator delete(this);
    return this;
}

// @ 0x00e8c120
void SP::cCreatureView_s00e8_c120::HandleSimulationUpdate(int a, int b)
{
    if (!mpCreature->mHasView)
        return;

    AssignEffect(mpOverheadEffect, mpCreature->mpOverheadEffect);
    if (!mpOverheadEffect)
        return;

    // Refresh the squared LOD radii when the terrain property list changed.
    cTerrainRecord* terrain = GetTerrainMgr()->Fn2();
    if (terrain) {
        int mods = terrain->mpProps ? terrain->mpProps->GetModificationCount() : 0;
        int version = terrain->mVersion + mods;
        if (version != gTerrainPropVersion) {
            gTerrainPropVersion = version;
            GetFloatProperty(terrain, 0x52583bc, &gLodNearSq);
            gLodNearSq = gLodNearSq * gLodNearSq;
            GetFloatProperty(terrain, 0x52583d4, &gLodMidSq);
            gLodMidSq = gLodMidSq * gLodMidSq;
        }
    }

    // Squared distance to the reference point and the overhead-effect fade factor.
    const Vec3* pos = mpCreature->GetPosition();
    float dy = gReferencePos.y - pos->y;
    float dz = gReferencePos.z - pos->z;
    float dx = gReferencePos.x - pos->x;
    float distSq = dx * dx + dz * dz + dy * dy;
    mpCreature->mViewDistance = (float)sqrt(distSq);
    float alpha = 1.0f;
    if (distSq > gFadeFarSq)
        alpha = 0.0f;
    else if (distSq > gFadeNearSq)
        alpha = 1.0f - (distSq - gFadeNearSq) / (gFadeFarSq - gFadeNearSq);

    if (GetCurrentGameMode_s00e8_c120() != 0x1654c10 || gGameState->mMode != 1) {
        if (!IsOverheadActive())
            SetOverheadActive(true);
        SetOverheadShown(alpha > 0.0f);
    }

    int mode = GetCurrentGameMode_s00e8_c120();
    if (mode >= 0x1654c01 && (mode <= 0x1654c02 || mode == 0x1654c10))
        mbShowOverhead = false;

    if (mbShowOverhead && mpOverheadEffect->mAlpha > alpha)
        mpOverheadEffect->mAlpha = alpha;

    if (mpCreature->mbB5D) {
        mpOverheadEffect->SetShown(1);
        mpCreature->mbB5D = false;
        mpCreature->m330 = 0;
    }

    cEffectState* st = mpOverheadEffect->mpState;
    if (st) {
        bool lit = mpOverheadEffect->GetLevel() != 0;
        mpCreature->SetFlag(lit);
        if (mpCreature->mbF90)
            st->mFlags |= 1;
        else
            st->mFlags &= ~1u;
    }

    if (!Bit(mpCreature->mFlagsB58, 9)) {
        int lod = 2;
        if (distSq > gLodNearSq)
            lod = 0;
        else if (distSq > gLodMidSq)
            lod = 1;
        mpCreature->SetLOD(lod);
    }

    // Ground-contact effect for selected / interactable creatures.
    cEffectsMgr* fx = GetEffectsMgr();
    if (fx->mEnabled) {
        cEffectState* es = mpOverheadEffect->mpState;
        if (es && Bit(es->mFlags, 14) && !Bit(es->mFlags, 18)
            && mpCreature->IsReady() && mpCreature->mbF90) {
            Transform tr;
            Vec3 p = *mpCreature->GetBasePosition();
            if (Vector3Equal(&p, &gZeroVec))
                p = *mpCreature->GetPosition();
            Vec3 dir;
            PlanetModel()->FUN_00b7e3b0(&dir, &p);
            tr.SetB(Vec3(0.0f, 0.0f, 1.0f), dir);
            const Vec3* w = &p;
            Vec3 surf;
            if (!mpCreature->mOnPlanet)
                w = PlanetModel()->DirectionToSurfacePosition(&surf, &p);
            tr.SetPosition(Vec3(*w));
            tr.SetScale(mpCreature->GetHeight() * 2.0f);
            fx->Place(&tr, 1.0f);
        }
    }

    if (mpCreature->IsActive())
        UpdateMotiveEffects();

    cCreatureState* cs = mpCreature->mpState;
    if (cs->mCount648 > 0) {
        bool v = mpCreature->mfE58 > 0.0f;
        mpCreature->SetEffectParam(v, 0x5e361462, 0x73e4cdf);
        cMsgTarget* t = mpCreature->FindEffect(0x73e4cdf);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    } else {
        if (mpCreature->FindEffect(0x73e4cdf))
            mpCreature->KillEffect(0x73e4cdf, 0);
    }

    if (mpCreature->mpState->mCount69c > 0) {
        bool v = mpCreature->FUN_00c0c130();
        mpCreature->SetEffectParam(v, 0xdca300c0, 0x77492d8);
        cMsgTarget* t = mpCreature->FindEffect(0x77492d8);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    }

    if (mpCreature->mpState->mCount694 > 0) {
        mpCreature->SetEffectParam(mpCreature->mbBB0, 0xdaee4c72, 0x7e2fedf);
        cMsgTarget* t = mpCreature->FindEffect(0x7e2fedf);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    } else {
        if (mpCreature->FindEffect(0x7e2fedf))
            mpCreature->KillEffect(0x7e2fedf, 0);
    }

    {
        bool v = mpCreature->mbE68 && !mpCreature->mbB5E;
        mpCreature->SetEffectParam(v, 0xc29a026f, 0x7a16140);
        cMsgTarget* t = mpCreature->FindEffect(0x7a16140);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    }

    cAnimatingCreature_s00e8_c120* c = mpCreature;
    if (c && c->GetType() == 0x18eb4b7) {
        CreatureCitizenUpdate(c);
    } else if (mpCreature->mStateFlags & 0x800) {
        if (!mpCreature->FindEffect(0x6452ca4)) {
            mpCreature->CreateEffect(0x56192017, 0x6452ca4);
            cMsgTarget* t = mpCreature->FindEffect(0x6452ca4);
            if (t) SEND_SCALE(t, mpCreature, GetRadius);
        }
        mpCreature->ClearNeedsNameEffect();
    } else {
        if (mpCreature->FindEffect(0x6452ca4))
            mpCreature->KillEffect(0x6452ca4, 0);
    }

    // Write the component's position / orientation back when it was marked dirty.
    if (mpCreature->ConsumeDirty()) {
        Transform tr;
        const Vec3* p = mpCreature->GetPosition();
        tr.pos = *p;
        tr.flags |= 4;
        tr.count += 1;
        tr.scale = mpCreature->GetScale();
        tr.count += 1;
        Mat3 m;
        Matrix3FromQuaternion(m.m, mpCreature->GetOrientation());
        tr.rot = m;
        tr.flags |= 2;
        tr.count += 1;
        mpCreature->FUN_00c89d60(&tr);
    }
    mpCreature->FUN_00c8aa60();
}

// @ 0x00e8c9a0
void SP::cEffectView::SetTrackedEffect(cAnimatingCreature_s00e8_c120* c)
{
    // The tracked object is produced by a factory carrying the type key 0xce9f6639; the result
    // (null or not) is handed to the per-view hook together with the freshly built view state.
    cTrackedEffect* tracked = 0;
    if (c)
        tracked = (cTrackedEffect*)((void* (__thiscall*)(void*, u32))((*((void***)c))[3]))(c, 0xce9f6639);

    cTrackedEffect* v = (cTrackedEffect*)operator new(0x24, 0x1460e9c, 0, 0, 0, 0);
    if (v) {
        v->m08 = 0;
        v->m04 = 0;
        v->m0c = 0;
        v->m10 = 0;
        v->mb14 = 1;
        v->m18 = 0;
        v->mpVtbl = (void*)0x14605e4;
    } else {
        v = 0;
    }
    v->m1c = 0;
    v->m20 = 0.0f;
    ((void (__thiscall*)(void*, cTrackedEffect*))FUN_00e8bca0)(v, tracked);
}

// @ 0x00e8ca10
void SP::cCreatureView_s00e8_c120::HandleUpdate(int a, int b)
{
    cAnimatingCreature_s00e8_c120* c = mpCreature;
    if (!c || c->GetType() != 0x18eb45e)
        c = 0;

    bool early = GetCurrentGameMode_s00e8_c120() == 0x1654c01;
    bool r;
    if (early)
        r = !c->IsActive() && !c->mbB5E && !c->FUN_00c0c0e0();
    else
        r = !c->FUN_00c0c0e0();
    mbShowOverhead = r;

    HandleSimulationUpdate(a, b);

    if (GetCurrentGameMode_s00e8_c120() == 0x1654c10) {
        if (c->IsActive())
            FUN_00e92a10(c);
        if (c->m330 & 1) {
            if (c->FUN_00c41ec0() > kEffectNearDist) {
                if (!c->FindEffect(0x6885174))
                    c->CreateEffect(0x57619fab, 0x6885174);
            }
        } else {
            c->KillEffect(0x6885174, 0);
        }
    } else {
        if (c->IsActive())
            goto done;
        if (mState == 0) {
            if (!c->mHasView)
                goto done;
            mState = 1;
            mAccum = 0.0f;
            c->mFlagsB58 |= 0x800;
            if (c->mpOverheadEffect)
                c->mpOverheadEffect->mAlpha = 0.0f;
            goto done;
        }
        if (mState == 1) {
            if (!c->mHasView) {
                mState = 0;
                goto done;
            }
            c->mFlagsB58 |= 0x800;
            if (!c->mpOverheadEffect)
                goto done;
            float step = (float)b * kFadeMul + kFadeBias;
            float low = c->FUN_00c0c130() ? kFadeLow : 1.0f;
            mAccum += step;
            float scaled = mAccum * kFadeStep;
            float prev = FUN_005a6e00(scaled);
            c->mpOverheadEffect->mAlpha = prev * low;
            if (mAccum <= prev)
                goto done;
            if (!c->FUN_00c0c130())
                c->mFlagsB58 &= ~0x800u;
            mState = 2;
            goto done;
        }
        // mState == 2
        if (!c->mHasView)
            goto done;
        mState = 0;
        goto done;
    }

done:
    if (!early)
        FUN_00e8be60(this);
}
