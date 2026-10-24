// Slice s01066a40 -- SP::cSPUISpace (space-stage UI) helpers.
//
//   01066a40  cursor/layout update
//   01066d60  hide the global UI / event log
//   01066dd0  show the global UI / event log
//   01066e30  cSPUISpace::ShowForTutorial
//   01066f20  cSPUISpace::UpdateTerraformingBullseye
//   010673f0  cSPUISpace::UpdateCaptureBarsVisibility(int)
//   01067510  cSPUISpace::UpdateCaptureBarsVisibility(cGameNounManager*)
//   01067720  loyalty-meter update (foodweb)
//   010677b0  loyalty-meter update (trade route)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned char  byte;
typedef unsigned short wchar16;

// -------------------------------------------------------------------------------------------
// globals / constants
// -------------------------------------------------------------------------------------------
extern void*     gDAT_016e2234;   // 0x016e2234 (global "gate" object)
extern float     gF_016e2230;     // 0x016e2230 (bullseye refresh threshold)
extern float     gF_13ec4d0;      // 0x013ec4d0  100.0f
extern float     gF_13f9c6c;      // 0x013f9c6c -100.0f
extern float     gF_13ec4b0;      // 0x013ec4b0    0.6f
extern float     gF_13eb1bc;      // 0x013eb1bc   -1.0f
extern float     gF_1485720;      // 0x01485720    1.0f
extern float     gF_1471064;      // 0x01471064    0.5f
extern float     gF_149c1a0;      // 0x0149c1a0   25.0f
extern float     gF_1485378;      // 0x01485378    0.0f
extern float     gF_1486374;      // 0x01486374  bullseye threshold hi
extern float     gF_13ec434;      // 0x013ec434  bullseye threshold lo
extern char      gS_13f6b3c[];    // 0x013f6b3c  allocator name
extern wchar16   gW_CivConversionBar[];  // 0x014862ec  L"CivConversionBar"
extern char      gImg_15b9390[];  // 0x015b9390  far bullseye image key
extern char      gImg_15b939c[];  // 0x015b939c  mid bullseye image key
extern char      gImg_15b93a8[];  // 0x015b93a8  near bullseye image key

// -------------------------------------------------------------------------------------------
// external helpers (call relocations are masked by the matcher)
// -------------------------------------------------------------------------------------------
void*     FUN_00b3d230();                             // 0x00b3d230
void*     FUN_00b3d240();                             // 0x00b3d240
void*     FUN_00b3d430(int a);                        // 0x00b3d430  TerraformingManager
void*     FUN_00b3d4d0();                             // 0x00b3d4d0  TriggerMgr
char      FUN_00b5ca60();                             // 0x00b5ca60
void*     FUN_00b3d2a0();                             // 0x00b3d2a0  StarManager
void*     FUN_00b3d4a0();                             // 0x00b3d4a0  CommManager
void* __stdcall FUN_00b3d3e0(int a);                 // 0x00b3d3e0  EventLog (callee cleans arg)
void*     FUN_00b8de30(void* p, float v);             // 0x00b8de30  BioProtectorSort::operator()
void      FUN_00c8b820(void* a, void* b);             // 0x00c8b820
float     FUN_00c8c7f0(void* p, int* out);            // 0x00c8c7f0
float     FUN_00c8c5d0(void* p, int* out);            // 0x00c8c5d0
char      FUN_00ae9390_(void* p);                     // (see CommManager::IsActive)
void*     FUN_00e2f5c0(void* w, void* key);           // 0x00e2f5c0  SetImageFromKey
void*     FUN_01065ba0(int i);                        // (see cSPUISpace::FUN_01065ba0)
void      FUN_008414c0_(void);                        // (see helper below)
float     FUN_00805080();                             // 0x00805080  GetElapsedSeconds
void*     FUN_00f473a0(unsigned n, const char* file, unsigned a, unsigned b,
                        unsigned c, unsigned d);       // 0x00f473a0  operator new
void*     FUN_007f81d0(void* out, void* win, float a, float b, float c, int d); // 0x007f81d0
void*     FUN_005ca960(void* w);                      // 0x005ca960  interface_cast
uint32_t  FUN_00436ce0(float* a, float* b, float* out); // 0x00436ce0  Vector3_Normalize
float     FUN_006994a0(void* a, void* b);             // 0x006994a0  RaySphereIntersect
void      FUN_00808230(void* w, float* p);            // 0x00808230
void*     FUN_01021260();                             // 0x01021260  GetActivePlanet
void*     FUN_01021080();                             // 0x01021080  GetUniverseContext
char      FUN_0102adf0(void* planet);                 // 0x0102adf0  IsMissionActiveAtPlanet
void*     FUN_00b1fdb0(void* mgr);                    // 0x00b1fdb0  cGameNounManager::GetAvatar
void*     FUN_0067caa0();                             // 0x0067caa0  WindowManager
void*     FUN_0067cab0();                             // 0x0067cab0
char      FUN_00801bb0(void* p, uint32_t id);         // 0x00801bb0  CurMgr::FindLocal
void*     FUN_00435e90();                             // 0x00435e90  GetRecorderState
void*     FUN_00435ed0(uint32_t a, void* b);          // 0x00435ed0  KillSetiEffects
void*     FUN_01002bd0();                             // 0x01002bd0  SpaceGameGet
void*     FUN_008105b0(void* layout, uint32_t id, int b); // 0x008105b0 FindWindowByID
void      FUN_00810590(void* layout, int v);          // 0x00810590  SetVisibility
char      FUN_00810070(void* layout);                 // 0x00810070  IsVisible
void*     FUN_008414c0();                             // 0x008414c0
void*     FUN_00b188b0(void* p);                      // 0x00b188b0
void*     FUN_00b187f0(void* p);                      // 0x00b187f0
void*     FUN_00b18810(void* p);                      // 0x00b18810
void*     FUN_00b187d0(void* p);                      // 0x00b187d0
void*     FUN_00b18890(void* p);                      // 0x00b18890
void*     FUN_00b18870(void* p);                      // 0x00b18870
void      FUN_00b69930(void* p, float f, int a);      // 0x00b69930
void      FUN_00b69990(void* p);                      // 0x00b69990
void      FUN_00b5f950_Assign(void* a, void* b);      // 0x00b5f950 (assignment helper)

// -------------------------------------------------------------------------------------------
// dispatch helpers on an explicit vtable-pointer field
// -------------------------------------------------------------------------------------------
typedef void   (__thiscall *VF0)(void*);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP1)(void*, int);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF1P)(void*, void*);
typedef int    (__thiscall *VFI)(void*, int);
typedef char   (__thiscall *VFC0)(void*);
typedef char   (__thiscall *VFCVP)(void*, float*);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF2P)(void*, void*, int);
typedef void   (__thiscall *VFMP)(void*, float*);
typedef void   (__thiscall *VFMP2)(void*, float, float);

// -------------------------------------------------------------------------------------------
// object model
// -------------------------------------------------------------------------------------------
struct SPUIGlobalUI {                 // the global-UI object (pointer at cSPUISpace+0x224)
    char   IsTooltipVisible();        // 0x00e01380
    void   SetVisibility(int v);      // 0x00e01350
    void*  FindWindowByID(uint32_t id);  // 0x00e012b0
};

struct SPUIEventLog {
    void SetVisibility();             // 0x00dd8da0
};

struct SPUIMeter {
    void Shutdown(int v);             // 0x00e06940
    void PullToFront();               // 0x00e06d50
    void Init0(void* a);              // 0x00e066d0
    void Init1(void* a);              // 0x00e066e0
    void SetValue(int a, int b);      // 0x00e06710
    void SetPos(float a, float b);    // 0x00e06730
};

struct SPUIAnimator {
    void AddAnimation(void* target, void* win, int id);  // 0x007f8d10
};

class AnimRaw {                       // animation handle produced by SPUICreateWindowAnimationTargetScale
public:
    void Destroy();                   // 0x0059a1e0
};

struct CivBar {                        // meter object created through the 0x50-byte alloc
    char  pad_00[0x50];
    void* Ctor(int a, uint32_t b, uint32_t c, const wchar16* name, uint32_t e);  // 0x00e06a10
};

class MeterRef {                       // EA::AutoRefCount<...> ; first dword is the meter pointer
public:
    SPUIMeter* mpMeter;                // +0x00
    MeterRef& operator=(void* p);      // 0x00b5f950
};

struct CommManager {
    char IsActive();                   // 0x00ae9390
};

struct GameObject {                    // a game object, passed by pointer as the `int param`
    int GetKind();                     // 0x00b8dab0
};

struct TerraformingManager {
    int GetState();                    // 0x00bbc670
};

struct StarManager {
    void* GetSystemMgr();              // 0x00ba6490
    void* GetEmpireByID(int id);       // 0x00ba9370
};

struct SpaceTradeRouteManager {
    char  SystemHasTradeRouteWithPlayer(void* player, void* avatar);  // 0x01037d30
    float GetTradeRouteScore(void* player, void* avatar);             // 0x01037dd0
};

struct WideObj {
    float GetScaleX();                 // 0x00c70a20
    float GetScaleY();                 // 0x00c709d0
};

struct CGameNounManager {
    char pad_00[0x70];
    void* mpPlayer;                    // +0x70
    int  GetType();                    // 0x00bb9ae0
    void* GetAvatar();                 // 0x00b1fdb0
};

namespace SP {

class cSPUISpace {
public:
    char          pad_00[0x08];
    uint32_t      mTimer8;             // +0x08
    void*         mpLayout;            // +0x0c  (cSPUILayout*)
    char          pad_10[0x224 - 0x10];
    SPUIGlobalUI* mpGlobal;            // +0x224
    char          pad_228[0x52c - 0x228];
    float         mF52c;               // +0x52c
    char          pad_530[0x558 - 0x530];
    void*         mpArr558[4];         // +0x558  (indexed by terraforming state)
    SPUIAnimator* mpAnimator;          // +0x568
    char          pad_56c[0x5ac - 0x56c];
    MeterRef      m5ac;                // +0x5ac  (foodweb meter)
    MeterRef      m5b0;                // +0x5b0  (unlocked-card meter)
    MeterRef      m5b4;                // +0x5b4  (loyalty meter)
    char          pad_5b8[0x5c4 - 0x5b8];
    void*         mp5c4;               // +0x5c4

    char     FUN_01066a40(int param);
    void     FUN_01066d60();
    void     FUN_01066dd0();
    void     ShowForTutorial(int param);
    void     UpdateTerraformingBullseye();
    uint32_t UpdateCaptureBarsVisibility(int param);
    int      UpdateCaptureBarsVisibility(CGameNounManager* mgr);
    void     FUN_01067720(void* p, float f1, float f2, char flag);
    void     FUN_010677b0(CGameNounManager* mgr, float f1, float f2, char flag);
    void*    FUN_01065ba0(int i);
};

} // namespace SP

using SP::cSPUISpace;

// -------------------------------------------------------------------------------------------
// 01066a40 : cursor/layout update
// -------------------------------------------------------------------------------------------
// @ 0x01066a40
char cSPUISpace::FUN_01066a40(int param)
{
    mTimer8 += (uint32_t)param;
    void* m = FUN_00b3d230();
    char  c = FUN_00b5ca60();
    int   iVar4;
    void* piVar3;
    int   iVar5;
    (void)m;
    if (c != 0) {
        if (mpLayout == 0) goto LAB_d3c;
        if (FUN_00810070(mpLayout) == 0) goto LAB_d3c;
        void* wm = FUN_0067caa0();
        int   wi = ((VFI)(*(void***)wm)[0x48 / 4])(wm, 1);
        void* w  = FUN_008105b0(mpLayout, 0x37ab944, 1);
        if (w != (void*)(size_t)wi)
            goto LAB_d32;
        iVar4 = (int)(size_t)FUN_0067cab0();
        if (iVar4 != 0)
            FUN_00801bb0((void*)(size_t)iVar4, 0x64e9c00);
    } else {
        int tm = (int)(size_t)FUN_00b3d4d0();
        if (*(int*)((char*)(size_t)tm + 0x2c) == 1 || *(int*)((char*)(size_t)tm + 0x2c) == 2)
            goto LAB_d22;
        if (FUN_01021080() != 0)
            goto LAB_d22;
    }
    {
        void* pi = FUN_00b3d240();
        piVar3 = (void*)((VFP)(*(void***)pi)[0x30 / 4])(pi);
        if (piVar3 == 0) {
            param  = 0;
            iVar4  = 0;
        } else {
            iVar4 = (int)(size_t)((VFP1)(*(void***)piVar3)[0x0c / 4])(piVar3, 0x17f243b);
            if (iVar4 != 0 && FUN_00b188b0((void*)(size_t)iVar4) != 0)
                return 0;
            iVar4 = (int)(size_t)((VFP1)(*(void***)piVar3)[0x0c / 4])(piVar3, 0xb033b403);
            if (iVar4 != 0 && *(int*)((char*)(size_t)iVar4 + 0x714) == 0)
                return 0;
            iVar4 = (int)(size_t)((VFP1)(*(void***)piVar3)[0x0c / 4])(piVar3, 0x1007ae63);
            if (iVar4 != 0 && mpLayout != 0) {
                char cv = ((VFC0)(*(void***)(size_t)(iVar4 + 0x34))[0x58 / 4])((void*)(size_t)(iVar4 + 0x34));
                byte vis;
                if (cv == 0) {
LAB_c12:
                    vis = 0;
                } else {
                    void* plt = FUN_01021260();
                    if (FUN_0102adf0(plt) != 0) goto LAB_c12;
                    vis = 1;
                    if (FUN_00810070(mpLayout) == 0) {
                        void* rs = FUN_00435e90();
                        FUN_00435ed0(0xa47319c2, rs);
                    }
                    void* sg = FUN_01002bd0();
                    FUN_00b5f950_Assign((void*)((char*)sg + 0x28), (void*)(size_t)iVar4);
                    mTimer8 = 0;
                }
                FUN_00810590(mpLayout, vis);
            }
        }
        piVar3 = FUN_008105b0(mpLayout, 0x68afc98, 1);
        {
            void* sg    = FUN_01002bd0();
            void* inner = *(void**)((char*)sg + 0x28);
            if (inner == 0)
                iVar5 = 0;
            else
                iVar5 = (int)(size_t)((VFP1)(*(void***)inner)[0x0c / 4])(inner, 0x1007ae63);
        }
        if (piVar3 != 0 && iVar5 != 0) {
            float out[2];
            char  cv = ((VFCVP)(*(void***)(size_t)(iVar5 + 0x34))[0x7c / 4])((void*)(size_t)(iVar5 + 0x34), out);
            if (cv == 0)
                FUN_00810590(mpLayout, 0);
            else
                ((VFMP2)(*(void***)piVar3)[0x64 / 4])(piVar3, out[0], out[1]);
        }
        if (iVar4 == 0 && mpLayout != 0 && FUN_00810070(mpLayout) != 0 && mTimer8 > 0xbb8)
            FUN_00810590(mpLayout, 0);
        {
            char bl;
            if (FUN_01021080() == 0) {
                void* sg = FUN_01002bd0();
                void* av = FUN_00b1fdb0(sg);
                bl = (*(char*)((char*)av + 0x14) != 0) ? 1 : 0;
            } else {
                bl = 0;
            }
            if (FUN_00b187f0((void*)(size_t)iVar4) == 0 &&
                FUN_00b18810((void*)(size_t)param) == 0 &&
                FUN_00b187d0((void*)(size_t)param) == 0 &&
                FUN_00b18890((void*)(size_t)param) == 0) {
                if (FUN_00b18870((void*)(size_t)param) == 0)
                    return 1;
                goto LAB_do6999;
            }
            if (bl != 0) {
                FUN_00b69930((void*)(size_t)param, gF_13eb1bc, 0);
                return 1;
            }
LAB_do6999:
            FUN_00b69990((void*)(size_t)param);
            return 1;
        }
    }
LAB_d22:
    if (mpLayout == 0) goto LAB_d3c;
    if (FUN_00810070(mpLayout) == 0) goto LAB_d3c;
LAB_d32:
    FUN_00810590(mpLayout, 0);
LAB_d3c:
    {
        int x = (int)(size_t)FUN_0067cab0();
        if (x != 0)
            FUN_00801bb0((void*)(size_t)x, 0x1002);
    }
    return 0;
}

// -------------------------------------------------------------------------------------------
// 01066d60 : hide the global UI / event log
// -------------------------------------------------------------------------------------------
// @ 0x01066d60
void cSPUISpace::FUN_01066d60()
{
    if (mpGlobal->IsTooltipVisible()) {
        if (gDAT_016e2234 != 0)
            ((VF0)(*(void***)gDAT_016e2234)[0x18 / 4])(gDAT_016e2234);
        void* m = FUN_00b3d230();
        ((VF1P)(*(void***)m)[0x40 / 4])(m, gDAT_016e2234);
        mpGlobal->SetVisibility(0);
        SPUIEventLog* ev = (SPUIEventLog*)FUN_00b3d3e0(0);
        ev->SetVisibility();
        void* p = mp5c4;
        if (p != 0)
            ((VF1)(*(void***)p)[0xc0 / 4])(p, 0);
    }
}

// -------------------------------------------------------------------------------------------
// 01066dd0 : show the global UI / event log
// -------------------------------------------------------------------------------------------
// @ 0x01066dd0
void cSPUISpace::FUN_01066dd0()
{
    if (!mpGlobal->IsTooltipVisible()) {
        void* m = FUN_00b3d230();
        ((VF2P)(*(void***)m)[0x38 / 4])(m, gDAT_016e2234, 1);
        mpGlobal->SetVisibility(1);
        SPUIEventLog* ev = (SPUIEventLog*)FUN_00b3d3e0(1);
        ev->SetVisibility();
        void* p = mp5c4;
        if (p != 0)
            ((VF1)(*(void***)p)[0xc0 / 4])(p, 1);
    }
}

// -------------------------------------------------------------------------------------------
// 01066e30 : cSPUISpace::ShowForTutorial
// -------------------------------------------------------------------------------------------
// @ 0x01066e30
void cSPUISpace::ShowForTutorial(int param)
{
    float off = 0.0f;
    int   id  = param;
    int   vis = param;
    switch (param) {
    case 0: id = 0x30aa150; off = gF_13f9c6c; vis = 1; break;
    case 1: id = 0x30aa150; off = gF_13ec4d0; vis = 0; break;
    }
    void* w = mpGlobal->FindWindowByID(id);
    if (w != 0)
        ((VF0)(*(void***)w)[0])(w);
    float* r = (float*)((VFP)(*(void***)w)[0x34 / 4])(w);
    float pos[4];
    pos[0] = r[0];
    pos[1] = r[1] + off;
    pos[2] = r[2];
    pos[3] = r[3] + off;
    ((VFMP)(*(void***)w)[0x60 / 4])(w, pos);
    mpGlobal->SetVisibility(vis);
    ((VF0)(*(void***)w)[1])(w);
}

// -------------------------------------------------------------------------------------------
// 01066f20 : cSPUISpace::UpdateTerraformingBullseye
// -------------------------------------------------------------------------------------------
// @ 0x01066f20
void cSPUISpace::UpdateTerraformingBullseye()
{
    float t = FUN_00805080();
    if (!(gF_016e2230 <= t))
        return;

    TerraformingManager* tfm = (TerraformingManager*)FUN_00b3d430(0);
    int   state = tfm->GetState();
    void* wA    = mpGlobal->FindWindowByID(0xa80a7e44);
    if (wA == 0) return;
    if (state == -1) {
        ((VF2)(*(void***)wA)[0x7c / 4])(wA, 1, 0);
        return;
    }
    void* planet = FUN_01021260();
    if (planet == 0) return;
    void* wB = mpGlobal->FindWindowByID(0xa80a7e45);
    void* wC = mpGlobal->FindWindowByID(0x4d90456);
    if (wB == 0 || wC == 0) return;

    float* rA = (float*)((VFP)(*(void***)wA)[0x34 / 4])(wA);
    float  a0 = rA[0], a1 = rA[1], a2 = rA[2], a3 = rA[3];
    float* rB = (float*)((VFP)(*(void***)wB)[0x34 / 4])(wB);
    float  b0 = rB[0], b1 = rB[1], b2 = rB[2], b3 = rB[3];
    float* rC = (float*)((VFP)(*(void***)wC)[0x38 / 4])(wC);
    float  c0 = rC[0], c1 = rC[1], c2 = rC[2], c3 = rC[3];

    float tgt = (state < 1) ? gF_13ec4b0 : gF_1485720;
    if (tgt != mF52c) {
        float secs = FUN_00805080();
        AnimRaw anim;
        FUN_007f81d0(&anim, wA, a1, secs, gF_1485720, 0);
        mpAnimator->AddAnimation(&anim, wA, 0x5243cd6);
        mF52c = tgt;
        anim.Destroy();
    }

    float f10 = ((WideObj*)wB)->GetScaleX();
    float f12 = ((WideObj*)wB)->GetScaleY();

    ((VFMP2)(*(void***)wB)[0x64 / 4])(wB,
        (a2 - a0) * f10 - (b2 - b0) * gF_1471064,
        (a3 - a1) * (gF_1485720 - f12) - (b3 - b1) * gF_1471064);
    ((VFMP2)(*(void***)wC)[0x64 / 4])(wC,
        (c2 - c0) * f10 - (a2 - a0) * gF_1471064,
        (c3 - c1) * (gF_1485720 - f12) - (a3 - a1) * gF_1471064);

    void* btn1 = FUN_005ca960(mpGlobal->FindWindowByID(0x5233980));
    void* btn2 = FUN_005ca960(mpGlobal->FindWindowByID(0x52339a8));
    void* btn3 = FUN_005ca960(mpGlobal->FindWindowByID(0x52339c0));
    ((VF2)(*(void***)btn1)[0x28 / 4])(btn1, 4, (state > 0) ? 1 : 0);
    ((VF2)(*(void***)btn2)[0x28 / 4])(btn2, 4, (state > 1) ? 1 : 0);
    ((VF2)(*(void***)btn3)[0x28 / 4])(btn3, 4, (state > 2) ? 1 : 0);
    {
        void* d = (void*)((VFP)(*(void***)btn1)[0x10 / 4])(btn1);
        ((VF1)(*(void***)d)[0x5c / 4])(d, (int)(size_t)FUN_01065ba0(1));
    }
    {
        void* d = (void*)((VFP)(*(void***)btn2)[0x10 / 4])(btn2);
        ((VF1)(*(void***)d)[0x5c / 4])(d, (int)(size_t)FUN_01065ba0(2));
    }
    {
        void* d = (void*)((VFP)(*(void***)btn3)[0x10 / 4])(btn3);
        ((VF1)(*(void***)d)[0x5c / 4])(d, (int)(size_t)FUN_01065ba0(3));
    }

    void* ob = FUN_008414c0();
    float dx = *(float*)((char*)ob + 0x1fd4);
    float dy = *(float*)((char*)ob + 0x1fd8);
    float len = (float)sqrt((double)(dx * dx + dy * dy));
    if (len <= gF_1485378) {
        ((VF2)(*(void***)wA)[0x7c / 4])(wA, 1, 0);
    } else {
        ((VF2)(*(void***)wA)[0x7c / 4])(wA, 1, 1);
        float v0[3];
        float v1[3];
        float v2[3];
        v0[0] = 0.0f; v0[1] = 1.0f; v0[2] = 0.0f;
        v1[0] = -dy / len; v1[1] = 0.0f; v1[2] = dx / len;
        v2[0] = 0.0f; v2[1] = 0.0f; v2[2] = 0.0f;
        FUN_00436ce0(v0, v1, v2);
        float hit = FUN_006994a0(v1, v2);
        float dist[1];
        dist[0] = hit;
        FUN_00808230(wA, dist);
        if (dist[0] > gF_1486374)
            FUN_00e2f5c0(wA, gImg_15b93a8);
        else if (dist[0] > gF_13ec434)
            FUN_00e2f5c0(wA, gImg_15b939c);
        else
            FUN_00e2f5c0(wA, gImg_15b9390);
    }
    ((VF1)(*(void***)wA)[0x5c / 4])(wA, (int)(size_t)mpArr558[state]);
}

// -------------------------------------------------------------------------------------------
// 010673f0 : cSPUISpace::UpdateCaptureBarsVisibility(int)
// -------------------------------------------------------------------------------------------
// @ 0x010673f0
uint32_t cSPUISpace::UpdateCaptureBarsVisibility(int param)
{
    char active = ((CommManager*)FUN_00b3d4a0())->IsActive();
    if (active != 0 || param == 0)
        goto LAB_65;
    if (((GameObject*)(size_t)param)->GetKind() != 5)
        goto LAB_65;
    {
        int   local = -1;
        float v     = FUN_00c8c7f0((void*)(size_t)param, &local);
        if (local != -1) {
            if (((StarManager*)FUN_00b3d2a0())->GetEmpireByID(local) == 0)
                FUN_00c8b820(FUN_00b8de30((void*)(size_t)param, v), 0);
            goto LAB_65;
        }
        if (v > gF_1485378) {
            if (m5b4.mpMeter == 0) {
                CivBar* obj  = (CivBar*)FUN_00f473a0(0x50, gS_13f6b3c, 0, 0, 0, 0);
                void*   made = obj ? obj->Ctor(0, 0x3ffb28c, 0x4d428c1, gW_CivConversionBar, 0x6722122) : 0;
                m5b4 = made;
                m5b4.mpMeter->Init1((void*)(size_t)param);
            }
            return 1;
        }
    }
LAB_65:
    if (m5b4.mpMeter != 0) {
        m5b4.mpMeter->Shutdown(1);
        if (m5b4.mpMeter != 0) {
            SPUIMeter* old = m5b4.mpMeter;
            m5b4.mpMeter = 0;
            ((VF0)(*(void***)old)[1])(old);
        }
    }
    return 0;
}

// -------------------------------------------------------------------------------------------
// 01067510 : cSPUISpace::UpdateCaptureBarsVisibility(cGameNounManager*)
// -------------------------------------------------------------------------------------------
// @ 0x01067510
int cSPUISpace::UpdateCaptureBarsVisibility(CGameNounManager* mgr)
{
    int  count  = 0;
    char haveAc = 0;
    char haveUn = 0;
    char active = ((CommManager*)FUN_00b3d4a0())->IsActive();
    void* sysMgr = ((StarManager*)FUN_00b3d2a0())->GetSystemMgr();
    if (active != 0 || mgr == 0)
        goto LAB_d6_check;
    if (mgr->GetType() != 5)
        goto LAB_d6_check;
    {
        void* player = mgr->mpPlayer;
        void* avatar = mgr->GetAvatar();
        if (((SpaceTradeRouteManager*)sysMgr)->SystemHasTradeRouteWithPlayer(player, avatar) != 0) {
            if (m5ac.mpMeter == 0) {
                CivBar* obj  = (CivBar*)FUN_00f473a0(0x50, gS_13f6b3c, 0, 0, 0, 0);
                void*   made = obj ? obj->Ctor(2, 0x3ffb28c, 0x4d428c1, gW_CivConversionBar, 0x6722122) : 0;
                m5ac = made;
                m5ac.mpMeter->Init0(mgr);
            }
            haveAc = 1;
            count  = 1;
        }
    }
    {
        int   local = -1;
        float v     = FUN_00c8c5d0(mgr, &local);
        if (local != -1) {
            if (((StarManager*)FUN_00b3d2a0())->GetEmpireByID(local) == 0)
                FUN_00c8b820(mgr, (void*)(size_t)local);
            goto LAB_after_un;
        }
        if (v > gF_1485378) {
            if (m5b0.mpMeter == 0) {
                CivBar* obj  = (CivBar*)FUN_00f473a0(0x50, gS_13f6b3c, 0, 0, 0, 0);
                void*   made = obj ? obj->Ctor(0, 0x3ffb28c, 0x4d428c1, gW_CivConversionBar, 0x6722122) : 0;
                m5b0 = made;
                m5b0.mpMeter->Init0(mgr);
            }
            count++;
            haveUn = 1;
        }
    }
LAB_after_un:
    if (haveAc != 0)
        goto LAB_d6_check;
LAB_d6_check:
    if (m5ac.mpMeter != 0) {
        m5ac.mpMeter->Shutdown(1);
        if (m5ac.mpMeter != 0) {
            SPUIMeter* old = m5ac.mpMeter;
            m5ac.mpMeter = 0;
            ((VF0)(*(void***)old)[1])(old);
        }
    }
    if (haveUn == 0 && m5b0.mpMeter != 0) {
        m5b0.mpMeter->Shutdown(1);
        if (m5b0.mpMeter != 0) {
            SPUIMeter* old = m5b0.mpMeter;
            m5b0.mpMeter = 0;
            ((VF0)(*(void***)old)[1])(old);
        }
    }
    return count;
}

// -------------------------------------------------------------------------------------------
// 01067720 : loyalty-meter update (foodweb)
// -------------------------------------------------------------------------------------------
// @ 0x01067720
void cSPUISpace::FUN_01067720(void* p, float f1, float f2, char flag)
{
    if (p == 0 || m5b4.mpMeter == 0)
        return;
    int   local = -1;
    float v     = FUN_00c8c7f0(p, &local);
    m5b4.mpMeter->SetValue((int)v, local);
    if (flag != 0)
        m5b4.mpMeter->PullToFront();
    m5b4.mpMeter->SetPos(f1, f2);
}

// -------------------------------------------------------------------------------------------
// 010677b0 : loyalty-meter update (trade route)
// -------------------------------------------------------------------------------------------
// @ 0x010677b0
void cSPUISpace::FUN_010677b0(CGameNounManager* mgr, float f1, float f2, char flag)
{
    if (mgr == 0)
        return;
    int n = 0;
    if (m5ac.mpMeter != 0) {
        void* sysMgr = ((StarManager*)FUN_00b3d2a0())->GetSystemMgr();
        void* player = mgr->mpPlayer;
        void* avatar = mgr->GetAvatar();
        int   v      = (int)((SpaceTradeRouteManager*)sysMgr)->GetTradeRouteScore(player, avatar);
        m5ac.mpMeter->SetValue(v, -1);
        m5ac.mpMeter->SetPos(f1, f2);
        if (flag != 0)
            m5ac.mpMeter->PullToFront();
        n = 1;
    }
    if (m5b0.mpMeter != 0) {
        int   local = -1;
        float v     = FUN_00c8c5d0(mgr, &local);
        m5b0.mpMeter->SetValue((int)v, local);
        if (flag != 0)
            m5b0.mpMeter->PullToFront();
        float off = (float)n * gF_149c1a0 + f2;
        m5b0.mpMeter->SetPos(f1, off);
    }
}