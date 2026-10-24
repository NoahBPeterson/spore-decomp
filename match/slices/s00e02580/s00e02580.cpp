// Slice s00e02580 -- cUI ban-mode content object + global-UI message pump.
//
//   00e02580  StartBanMode(int enable)
//   00e02900  ban-mode helper (message + spore guide)
//   00e02950  ban-mode exit / restore
//   00e02a20  ban-mode exit / restore (sporepedia variant)
//   00e02af0  create global-UI root window proc + global options
//   00e02c40  ShowContextSensitiveSporepedia wrapper
//   00e02c60  destroy range of 0x24-byte wstring-pair elements
//   00e02cc0  destroy range, returns advanced dst
//   00e02d30  forward copy of 0x24-byte wstring-pair elements
//   00e02da0  backward copy of 0x24-byte wstring-pair elements
//   00e02e10  shutdown layout, restore ban mode off
//   00e02e80  toggle ban mode from the content button
//   00e02f00  cSPUIGlobalUIRootWinProc::DoMessage
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned char  byte;
typedef unsigned short wchar16;
typedef unsigned int   uint32;

// -------------------------------------------------------------------------------------------
// external helpers (call relocations are masked by the matcher)
// -------------------------------------------------------------------------------------------
void*     MessageServer();                             // 0x0067dcc0
char      FUN_00dd1230();                              // 0x00dd1230
char      FUN_00e09540();                              // 0x00e09540
void*     FUN_00b3d410();                              // 0x00b3d410
char      FUN_00e00a40();                              // 0x00e00a40
char      FUN_00e00c40();                              // 0x00e00c40
char      FUN_00e00d20();                              // 0x00e00d20
void*     FUN_00b3d380();                              // 0x00b3d380  GameTimeManager
void*     FUN_00b5b800();                              // 0x00b5b800  GetCurrentGameMode
void*     FUN_01021080();                              // 0x01021080  GetUniverseContext
void*     FUN_0080fee0();                              // 0x0080fee0  MultiHeapObject::operator_new
void*     FUN_00f473a0(uint32 n, const char* file, uint32 a, uint32 b, uint32 c, uint32 d);
void      FUN_00f47380(void* p);                       // 0x00f47380  operator delete[]
void      FUN_00e02200();                              // 0x00e02200  ShowContextSensitiveSporeGuide
void      FUN_00e02040(void* a);                       // 0x00e02040  ShowContextSensitiveSporepedia
void*     FUN_0067cac0();                              // 0x0067cac0  (returns cUIHints*)
void*     FUN_0067cae0();                              // 0x0067cae0
void*     FUN_0067de40();                              // 0x0067de40
void*     FUN_00cf74c0();                              // 0x00cf74c0  cCivModeStrategy::Get
void*     FUN_00cd40b0();                              // 0x00cd40b0  cTribeModeStrategy::Instance
void*     FUN_010666a0();                              // 0x010666a0
void*     FUN_01002bd0();                              // 0x01002bd0  SpaceGameGet
void      FUN_00e3c6f0(int a, int b);                  // 0x00e3c6f0
void* __stdcall FUN_00b3d3f0(int a);                   // 0x00b3d3f0
void* __stdcall FUN_00b3d3e0(int a, int b, int c, int d, int e, int f); // 0x00b3d3e0 EventLog
void* __stdcall FUN_0067de90(int a);                   // 0x0067de90
void*     FUN_00572020(void* p, int v);                // 0x00572020
void*     FUN_00435ed0(uint32 id, void* p);            // 0x00435ed0  KillSetiEffects
void      FUN_00e009f0();                              // 0x00e009f0  on_ban_content_button
void      FUN_00809c50(void* p, int a, int b);         // 0x00809c50  SPUIHelpers::EndModal

// 0-stack-argument __thiscall helpers (one pointer in ecx == __fastcall)
void* __fastcall FUN_00644b10(void* self);             // 0x00644b10  (returns self)
void  __fastcall FUN_00644b60(void* self);             // 0x00644b60  (dtor)
void* __fastcall FUN_00e00ec0(void* self);             // 0x00e00ec0  ctor
void* __fastcall FUN_00d486f0(void* self);             // 0x00d486f0  ctor
void  __fastcall FUN_0067c960(void* self);             // 0x0067c960  cUIHints::Update
void  __fastcall FUN_005fdf40(void* self);             // 0x005fdf40  AchievementNotifier::Update
char  __fastcall FUN_00e36fa0(void* self);             // 0x00e36fa0  (thiscall)
char  __fastcall FUN_00e393b0(void* self);             // 0x00e393b0  (thiscall)
char  __fastcall FUN_00cd44a0(void* self);             // 0x00cd44a0  (thiscall)
char  __fastcall FUN_01065e20(void* self);             // 0x01065e20  (thiscall)
void* __fastcall FUN_00bfc5f0(void* self);             // 0x00bfc5f0  (thiscall)
void  __fastcall FUN_00e190c0(void* self);             // 0x00e190c0  (thiscall)
void  __fastcall FUN_00dd8640(void* self);             // 0x00dd8640  PostFeedbackEvent

// __thiscall helpers that also take one stack argument
struct HintsSink { void Set(void* a); };               // 0x0067ca50
struct WinProc   { void* ctor(void* owner); };         // 0x00e010c0
struct Telemetry { void Flush(); };                    // 0x007ebce0

// -------------------------------------------------------------------------------------------
// external string / table data
// -------------------------------------------------------------------------------------------
extern char  g147f09c;        // 0x0147f09c
extern char  g147f0a0;        // 0x0147f0a0
extern char  g147f0a4;        // 0x0147f0a4
extern char  g147f0a8;        // 0x0147f0a8
extern char  g147f0ac;        // 0x0147f0ac
extern char  g15a4ae0;        // 0x015a4ae0
extern void* g169e3e8;        // 0x0169e3e8  gpCreatureTokenTranslator
extern void* g16c7aa4;        // 0x016c7aa4  (pointer to a global object)
extern char  gSimulatorName[];    // 0x013f09b4 "Simulator"
extern char  gRootWinProcName[];  // 0x0147f214 "Simulator/cSPUIGlobalUIRootWinProc"
extern char  gGlobalOptionsName[];// 0x0147f1fc "UI/cSPUIGlobalOptions"

// -------------------------------------------------------------------------------------------
// dispatch helpers on an explicit vtable-pointer field
// -------------------------------------------------------------------------------------------
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef void   (__thiscall *VF4)(void*, int, int, int, int);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP2)(void*, int, int);
typedef char   (__thiscall *VFC)(void*);
typedef int    (__thiscall *VFCI)(void*);

// -------------------------------------------------------------------------------------------
// object model
// -------------------------------------------------------------------------------------------
struct Layout {                                  // cSPUILayout
    void* FindWindowByID(uint32 id, int b);      // 0x008105b0
    void  Shutdown(int v);                       // 0x00811ad0
};

struct LayoutManager {                           // cSPUILayoutManager
    void  SetAllWorldsVisibility(char v);        // 0x008106a0
    void  Method10660(uint32 id, char v);        // 0x00810660
    void* GetWorldMainWindow(uint32 id);         // 0x00810620
};

struct GameTimeManager {
    void  IncPauseGate(int v);                   // 0x00b32220
    void  DecPauseGate(int v);                   // 0x00b32250
    char  pad_00[0x48];
    uint32 m48;                                  // +0x48
};

struct GlobalOptions {                           // UI::cSPUIGlobalOptions
    char  pad_00[0x14];
    void* m14;                                   // +0x14
    void  CreateDialog();                        // 0x00e02430
};

struct ObjB {                                    // the object at [this+0x5c]+4
    char  pad_00[0x0c];
    char  m0c;                                   // +0x0c  byte flag
    char  pad_0d[0x14 - 0x0d];
    void* m14;                                   // +0x14
    char  pad_18[0x1c - 0x18];
    void* m1c;                                   // +0x1c
    char  pad_20[0x24 - 0x20];
    void* m24;                                   // +0x24
};

struct ObjA {                                    // the object at [this+0x5c]
    char  pad_00[4];
    ObjB* m04;                                   // +0x04
};

// element of the 0x24-byte wstring-pair arrays
struct WStr {
    uint32 begin;                                // +0x00
    uint32 end;                                  // +0x04
    uint32 cap;                                  // +0x08
    uint32 pad;                                  // +0x0c
    void   assign(const wchar16* first, const wchar16* last);   // 0x00423650
};

struct Elem24 {
    uint32 m00;                                  // +0x00
    WStr   s1;                                   // +0x04
    WStr   s2;                                   // +0x14
};

// the ban-mode content object (cUIBanningContent)
class UIThing {
public:
    char     pad_00[4];
    void*    m04;                                // +0x04  AutoRefCount<GlobalOptions>
    void*    m08;                                // +0x08  cSPUILayout*
    char     m0c;                                // +0x0c  byte flag
    char     pad_0d[3];
    void*    m10;                                // +0x10  cSPUILayout*
    uint32   m14;                                // +0x14
    void*    m18;                                // +0x18  window
    void*    m1c;                                // +0x1c
    void*    m20;                                // +0x20  window
    uint32   m24;                                // +0x24  state
    uint32   m28;                                // +0x28
    uint32   m2c;                                // +0x2c
    char     pad_30[0x3c - 0x30];
    uint32   m3c;                                // +0x3c
    uint32   m40;                                // +0x40
    uint32   m44;                                // +0x44
    char     pad_48[0x54 - 0x48];
    uint32   m54;                                // +0x54
    char     pad_58[4];
    ObjA*    m5c;                                // +0x5c

    void  FUN_00e02580(unsigned char enable);
    void  FUN_00e02900();
    void  FUN_00e02950();
    void  FUN_00e02a20();
    char  FUN_00e02af0();
    void  FUN_00e02e10();
    void  FUN_00e02e80();
    char  FUN_00e02f00(int a, void* msg);

    void  Enable(char v);                        // 0x00e018c0
    void* FindWindowByID(uint32 id);             // 0x00e01ce0
    void  FUN_00e00bb0();                        // 0x00e00bb0
    void  FUN_00e00bd0();                        // 0x00e00bd0
    void  FUN_00e00bf0();                        // 0x00e00bf0
    void  FUN_00e01d00();                        // 0x00e01d00  ShowTransition
    void  FUN_00e01270();                        // 0x00e01270
};

// -------------------------------------------------------------------------------------------
// 00e02580 : StartBanMode(int enable)
// -------------------------------------------------------------------------------------------
// @ 0x00e02580
void UIThing::FUN_00e02580(unsigned char enable)
{
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    } else {
        if (FUN_00e09540() != 0) {
            void* ms = MessageServer();
            ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
        }
    }
    if (m18 != 0)
        ((VF2)(*(void***)m18)[0x7c / 4])(m18, 1, enable);
    if (FUN_00b5b800() != (void*)0x01654c00) {
        GameTimeManager* gm = (GameTimeManager*)FUN_00b3d380();
        if (enable == 0)
            gm->DecPauseGate(0x4bf38a4);
        else
            gm->IncPauseGate(0x4bf38a4);
    }
    LayoutManager* lm = (LayoutManager*)FUN_0080fee0();
    if (enable != 0)
        lm->SetAllWorldsVisibility(0);
    lm->Method10660(0x5b598f7, enable);
    lm->Method10660(0x5b598f6, enable);
    lm->Method10660(0x5b598f9, enable);
    lm->Method10660(0x5f1bfc10, enable);
    if (enable == 0)
        lm->SetAllWorldsVisibility(1);
    Enable(enable);
    if (m20 != 0)
        ((VF2)(*(void***)m20)[0x28 / 4])(m20, 4, enable);
    if (enable == 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a504a, 0, 0);
        ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2f5, 0, 0);
        return;
    }
    m0c = 1;
    char cFlag = FUN_00e00a40();
    void* w1 = ((Layout*)m10)->FindWindowByID(0x10f366e, 1);
    void* w2 = ((Layout*)m10)->FindWindowByID(0x44ea79e, 1);
    void* w3 = ((Layout*)m10)->FindWindowByID(0x62025f9, 1);
    void* w4 = ((Layout*)m10)->FindWindowByID(0x447060a, 1);
    if (FUN_00b5b800() == (void*)0x01654c05)
        FUN_01002bd0();
    char cVar3 = FUN_00e00c40();
    char bVar1;
    if (FUN_00b5b800() == (void*)0x01654c04 &&
        *(char*)((char*)FUN_00cf74c0() + 0x148) == 1)
        bVar1 = 1;
    else if (FUN_00b5b800() == (void*)0x01654c02 && FUN_00cd44a0(FUN_00cd40b0()) == 1)
        bVar1 = 1;
    else if (FUN_00b5b800() == (void*)0x01654c05 &&
             FUN_01065e20(FUN_010666a0()) == 1)
        bVar1 = 1;
    else if (FUN_00b5b800() == (void*)0x01654c05 &&
             *(char*)((char*)FUN_00bfc5f0(FUN_01002bd0()) + 0xa0) != 0)
        bVar1 = 1;
    else
        bVar1 = 0;
    char cVar2;
    if (cFlag != 0 && cVar3 == 0)
        cVar2 = 1;
    else
        cVar2 = 0;
    if (w4 != 0)
        ((VF2)(*(void***)w4)[0x7c / 4])(w4, 2, !bVar1);
    if (w2 != 0) {
        uint32 v;
        if (cVar3 != 0 || FUN_00b5b800() == (void*)0x01654c00)
            v = 0;
        else
            v = 1;
        ((VF2)(*(void***)w2)[0x7c / 4])(w2, 2, v);
    }
    if (w3 != 0) {
        uint32 v;
        if (bVar1 != 0)
            v = 0;
        else if (FUN_00e00d20() != 0)
            v = 1;
        else
            v = 0;
        ((VF2)(*(void***)w3)[0x7c / 4])(w3, 2, v);
    }
    if (w1 == 0)
        goto LAB_msg_show;
    ((VF2)(*(void***)w1)[0x7c / 4])(w1, 2, cVar2);
    if (cVar2 == 0) {
        if (FUN_00b5b800() == (void*)0x01654c10) {
            void* g = g16c7aa4;
            if (*(int*)((char*)g + 0xcc) != 2 || *(int*)((char*)g + 0xd0) != 2)
                goto LAB_msg_show;
            ((VF1)(*(void***)w1)[0x104 / 4])(w1, (int)m3c);
        } else if (FUN_00b5b800() != (void*)0x01654c05) {
            ((VF1)(*(void***)w1)[0x104 / 4])(w1, (int)m54);
        } else {
            ((VF1)(*(void***)w1)[0x104 / 4])(w1, (int)m3c);
        }
    } else {
        ((VF1)(*(void***)w1)[0x108 / 4])(w1, (int)m3c);
        ((VF1)(*(void***)w1)[0x108 / 4])(w1, (int)m54);
    }
LAB_msg_show:
    {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a5044, 0, 0);
        ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2ed, 0, 0);
    }
}

// -------------------------------------------------------------------------------------------
// 00e02900 : ban-mode helper (message + spore guide)
// -------------------------------------------------------------------------------------------
// @ 0x00e02900
void UIThing::FUN_00e02900()
{
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
        return FUN_00e02200();
    }
    if (FUN_00e09540() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
    }
    return FUN_00e02200();
}

// -------------------------------------------------------------------------------------------
// 00e02950 : ban-mode exit / restore
// -------------------------------------------------------------------------------------------
// @ 0x00e02950
void UIThing::FUN_00e02950()
{
    char cVar2 = FUN_00dd1230();
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    } else {
        if (FUN_00e09540() != 0) {
            void* ms = MessageServer();
            ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
        }
    }
    if (cVar2 != 0)
        return;
    {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    }
    if (m5c == 0)
        return;
    ObjB* obj = m5c->m04;
    if (obj == 0)
        return;
    if (obj->m1c != 0)
        ((VF2)(*(void***)obj->m1c)[0x7c / 4])(obj->m1c, 1, 0);
    if (FUN_00b5b800() != (void*)0x01654c00)
        FUN_00809c50((void*)obj->m14, 0, 0);
    if (obj->m24 != 0) {
        ((VF1)(*(void***)obj->m24)[0xc / 4])(obj->m24, 0);
        void* p = obj->m24;
        if (p != 0) {
            obj->m24 = 0;
            return ((VF0)(*(void***)p)[4 / 4])(p);
        }
    }
}

// -------------------------------------------------------------------------------------------
// 00e02a20 : ban-mode exit / restore (sporepedia variant)
// -------------------------------------------------------------------------------------------
// @ 0x00e02a20
void UIThing::FUN_00e02a20()
{
    char cVar2 = FUN_00e09540();
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    } else {
        if (FUN_00e09540() != 0) {
            void* ms = MessageServer();
            ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
        }
    }
    if (cVar2 != 0)
        return;
    {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
    }
    if (m5c == 0)
        return;
    ObjB* obj = m5c->m04;
    if (obj == 0)
        return;
    if (obj->m1c != 0)
        ((VF2)(*(void***)obj->m1c)[0x7c / 4])(obj->m1c, 1, 0);
    if (FUN_00b5b800() != (void*)0x01654c00)
        FUN_00809c50((void*)obj->m14, 0, 0);
    if (obj->m24 != 0) {
        ((VF1)(*(void***)obj->m24)[0xc / 4])(obj->m24, 0);
        void* p = obj->m24;
        if (p != 0) {
            obj->m24 = 0;
            return ((VF0)(*(void***)p)[4 / 4])(p);
        }
    }
}

// -------------------------------------------------------------------------------------------
// 00e02af0 : create global-UI root window proc + global options
// -------------------------------------------------------------------------------------------
// @ 0x00e02af0
char UIThing::FUN_00e02af0()
{
    GlobalOptions* piVar4 = 0;
    ObjB* piVar2 = 0;
    if (m08 != 0) {
        piVar2 = (ObjB*)((Layout*)m08)->FindWindowByID(0xffffffff, 1);
        if (piVar2 != 0) {
            void* pv = FUN_00f473a0(0x60, gRootWinProcName, 0, 0, 0, 0);
            void* obj = 0;
            if (pv != 0)
                obj = ((WinProc*)pv)->ctor(this);
            ((VF1)(*(void***)piVar2)[0x104 / 4])(piVar2, (int)obj);
            if (m08 != 0) {
                if (((Layout*)m08)->FindWindowByID(0x10ed874, 1) != 0)
                    goto LAB_end;
            }
            void* g = FUN_00f473a0(0x58, gGlobalOptionsName, 0, 0, 0, 0);
            if (g != 0)
                piVar4 = (GlobalOptions*)FUN_00e00ec0(g);
            GlobalOptions* piVar1 = (GlobalOptions*)m04;
            if (piVar4 != piVar1) {
                if (piVar4 != 0)
                    ((VF0)(*(void***)piVar4)[0])(piVar4);
                m04 = piVar4;
                if (piVar1 != 0)
                    ((VF0)(*(void***)piVar1)[1])(piVar1);
            }
            ((GlobalOptions*)m04)->CreateDialog();
            void* q = ((GlobalOptions*)m04)->m14;
            if (q != 0)
                ((VF1)(*(void***)q)[0x104 / 4])(q, (int)obj);
        }
    }
LAB_end:
    ((HintsSink*)FUN_0067cac0())->Set(&g15a4ae0);
    {
        void* r = FUN_00f473a0(0x30, gSimulatorName, 0, 0, 0, 0);
        void* gp;
        if (r == 0)
            gp = 0;
        else
            gp = FUN_00d486f0(r);
        g169e3e8 = gp;
        void* q2 = FUN_0067de40();
        void* q3 = ((VFP)(*(void***)q2)[0x20 / 4])(q2);
        ((VF1)(*(void***)q3)[0x1c / 4])(q3, (int)gp);
    }
    return piVar2 != 0;
}

// -------------------------------------------------------------------------------------------
// 00e02c40 : ShowContextSensitiveSporepedia wrapper
// -------------------------------------------------------------------------------------------
// @ 0x00e02c40
void FUN_00e02c40()
{
    char buf[0x48];
    void* r = FUN_00644b10(buf);
    FUN_00e02040(r);
    FUN_00644b60(buf);
}

// -------------------------------------------------------------------------------------------
// 00e02c60 : destroy range of 0x24-byte wstring-pair elements
// -------------------------------------------------------------------------------------------
// @ 0x00e02c60
void __stdcall FUN_00e02c60(Elem24* begin, Elem24* end)
{
    for (; begin < end; begin += 1) {
        if (((int)((begin->s2.cap - begin->s2.begin) & 0xfffffffeu) > 2) &&
            begin->s2.begin != 0)
            FUN_00f47380((void*)begin->s2.begin);
        if (((int)((begin->s1.cap - begin->s1.begin) & 0xfffffffeu) > 2) &&
            begin->s1.begin != 0)
            FUN_00f47380((void*)begin->s1.begin);
    }
}

// -------------------------------------------------------------------------------------------
// 00e02cc0 : destroy range, returns advanced dst
// -------------------------------------------------------------------------------------------
// @ 0x00e02cc0
Elem24* FUN_00e02cc0(Elem24* begin, Elem24* end, Elem24* dst)
{
    if (begin != end) {
        do {
            if (((int)((begin->s2.cap - begin->s2.begin) & 0xfffffffeu) > 2) &&
                begin->s2.begin != 0)
                FUN_00f47380((void*)begin->s2.begin);
            if (((int)((begin->s1.cap - begin->s1.begin) & 0xfffffffeu) > 2) &&
                begin->s1.begin != 0)
                FUN_00f47380((void*)begin->s1.begin);
            begin += 1;
            dst += 1;
        } while (begin != end);
    }
    return dst;
}

// -------------------------------------------------------------------------------------------
// 00e02d30 : forward copy of 0x24-byte wstring-pair elements
// -------------------------------------------------------------------------------------------
// @ 0x00e02d30
Elem24* FUN_00e02d30(Elem24* src, Elem24* srcEnd, Elem24* dst)
{
    if (src != srcEnd) {
        do {
            dst->m00 = src->m00;
            WStr* ss1 = &src->s1;
            WStr* ss2 = &src->s2;
            WStr* ds1 = &dst->s1;
            WStr* ds2 = &dst->s2;
            if (ss1 != ds1)
                ds1->assign((const wchar16*)ss1->begin, (const wchar16*)ss1->end);
            if (ss2 != ds2)
                ds2->assign((const wchar16*)ss2->begin, (const wchar16*)ss2->end);
            src += 1;
            dst += 1;
        } while (src != srcEnd);
    }
    return dst;
}

// -------------------------------------------------------------------------------------------
// 00e02da0 : backward copy of 0x24-byte wstring-pair elements
// -------------------------------------------------------------------------------------------
// @ 0x00e02da0
Elem24* FUN_00e02da0(Elem24* first, Elem24* last, Elem24* dstEnd)
{
    if (last != first) {
        do {
            last -= 1;
            dstEnd -= 1;
            dstEnd->m00 = last->m00;
            if (&last->s1 != &dstEnd->s1)
                dstEnd->s1.assign((const wchar16*)last->s1.begin, (const wchar16*)last->s1.end);
            if (&last->s2 != &dstEnd->s2)
                dstEnd->s2.assign((const wchar16*)last->s2.begin, (const wchar16*)last->s2.end);
        } while (last != first);
    }
    return dstEnd;
}

// -------------------------------------------------------------------------------------------
// 00e02e10 : shutdown layout, restore ban mode off
// -------------------------------------------------------------------------------------------
// @ 0x00e02e10
void UIThing::FUN_00e02e10()
{
    char c = 0;
    void* w = ((LayoutManager*)FUN_0080fee0())->GetWorldMainWindow(0x5f1bfc10);
    if (w != 0) {
        void* x = ((VFP2)(*(void***)w)[0xf0 / 4])(w, 0x615b50d, 1);
        if (x != 0) {
            c = ((VFC)(*(void***)x)[0x28 / 4])(x);
            if ((c & 1) != 0)
                FUN_00e02580(0);
        }
    }
    if (m10 != 0) {
        ((Layout*)m10)->Shutdown(1);
        if (m10 != 0) {
            void* p = m10;
            m10 = 0;
            ((VF0)(*(void***)p)[8 / 4])(p);
        }
    }
}

// -------------------------------------------------------------------------------------------
// 00e02e80 : toggle ban mode from the content button
// -------------------------------------------------------------------------------------------
// @ 0x00e02e80
void UIThing::FUN_00e02e80()
{
    if (m18 == 0)
        return;
    FUN_00572020(&g147f0a0, 1);
    FUN_00435ed0(0x5da7b944, &g147f0a0);
    unsigned char bl = 0;
    void* w = ((LayoutManager*)FUN_0080fee0())->GetWorldMainWindow(0x5f1bfc10);
    if (w != 0) {
        void* x = ((VFP2)(*(void***)w)[0xf0 / 4])(w, 0x615b50d, 1);
        if (x != 0) {
            bl = (unsigned char)((VFCI)(*(void***)x)[0x28 / 4])(x);
            bl &= 1;
        }
    }
    FUN_00e02580(bl == 0);
}

// -------------------------------------------------------------------------------------------
// 00e02f00 : cSPUIGlobalUIRootWinProc::DoMessage
// -------------------------------------------------------------------------------------------
// @ 0x00e02f00
char UIThing::FUN_00e02f00(int a, void* msg)
{
    (void)a;
    if (*(int*)((char*)msg + 8) != 0xc) {
        if (*(int*)((char*)msg + 8) != 0x287259f6)
            return 0;
        uint32 id = *(uint32*)((char*)msg + 0xc);
        switch (id) {
        case 0x10ed852: {
            void* p = FindWindowByID(0x10ed874);
            if (p == 0)
                return 0;
            FUN_00572020(&g147f0a0, 1);
            FUN_00435ed0(0x5da7b944, &g147f0a0);
            char b = ((VFC)(*(void***)p)[0x28 / 4])(p);
            b = (b ^ 0xff) & 1;
            ((VF2)(*(void***)p)[0x7c / 4])(p, 1, b);
            void* ms = MessageServer();
            if (b != 0)
                ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a5044, 0, 0);
            else
                ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a504a, 0, 0);
            return 0;
        }
        case 0x10f366d:
            ((Telemetry*)FUN_0067de90(-1))->Flush();
            FUN_00e009f0();
            FUN_00572020(&g147f0a8, 1);
            FUN_00435ed0(0x6d719e97, &g147f0a8);
            switch ((uint32)FUN_00b5b800()) {
            case 0x01654c01:
            case 0x01654c02:
            case 0x01654c04:
            case 0x01654c05:
                if (m5c->m04->m0c == 0)
                    goto LAB_default;
                if (FUN_00e00a40() != 0 && FUN_00e00c40() == 0) {
                    m24 = 3; FUN_00e00bd0();
                    return 0;
                }
                m24 = 1; FUN_00e00bb0();
                return 0;
            case 0x01654c10:
                m24 = 1; FUN_00e00bb0();
                return 0;
            default:
            LAB_default:
                m24 = 9; FUN_00e01d00();
                return 0;
            }
        case 0x10f366e:
            ((Telemetry*)FUN_0067de90(-1))->Flush();
            FUN_00e009f0();
            FUN_00572020(&g147f0a4, 1);
            FUN_00435ed0(0x31c0d295, &g147f0a4);
            if (FUN_00b5b800() == (void*)0x01654c05 && FUN_01021080() == 0) {
                FUN_00dd8640(FUN_00b3d3e0(0x6251278c, 0x131a9f54, 0, 0, 1, 0));
                return 0;
            }
            m5c->m04->m0c = 0;
            {
                void* ms = MessageServer();
                ((VF4)(*(void***)ms)[0x18 / 4])(ms, 0x1cd20f0, 0, 0, 0);
            }
            return 0;
        case 0x2268ba4:
            FUN_00e009f0();
            FUN_00572020(&g147f0a4, 1);
            FUN_00435ed0(0x31c0d295, &g147f0a4);
            if (FUN_00b5b800() != (void*)0x01654c10) {
                if (m5c->m04->m0c == 0) {
                    m24 = 10; FUN_00e01d00();
                    return 0;
                }
                if (FUN_00e00a40() != 0 && FUN_00e00c40() == 0) {
                    m24 = 4; FUN_00e00bd0();
                    return 0;
                }
            }
            m24 = 2; FUN_00e00bb0();
            return 0;
        case 0x43b72d0:
            FUN_00e00bf0();
            return 0;
        case 0x447060a:
            FUN_00572020(&g147f0ac, 1);
            FUN_00435ed0(0x0d6c6c5c, &g147f0ac);
            FUN_00e02900();
            return 0;
        case 0x44827b8:
            if (FUN_00b5b800() == (void*)0x01654c04 &&
                *(char*)((char*)FUN_00cf74c0() + 0x148) != 0)
                return 0;
            if (FUN_00b5b800() == (void*)0x01654c02 &&
                FUN_00cd44a0(FUN_00cd40b0()) != 0)
                return 0;
            if (FUN_00b5b800() == (void*)0x01654c05 &&
                FUN_01065e20(FUN_010666a0()) != 0)
                return 0;
            ((GameTimeManager*)FUN_00b3d380())->IncPauseGate(0x4bf38a4);
            FUN_00e3c6f0(0, 0);
            return 0;
        case 0x44ea79e:
            FUN_00e02950();
            return 1;
        case 0x62025f9:
            FUN_00e02a20();
            return 1;
        case 0x6244208:
            FUN_00e190c0(FUN_00b3d3f0(0));
            return 0;
        case 0x6244660:
            FUN_00e02c40();
            return 0;
        case 0xd305ca84:
            FUN_00572020(&g147f09c, 1);
            FUN_00435ed0(0x6938ce2c, &g147f09c);
            FUN_00e01270();
            return 0;
        default:
            return 0;
        }
    }
    {
        char cVar2 = FUN_00e36fa0(FUN_00b3d410());
        char bVar4;
        if (((((GameTimeManager*)FUN_00b3d380())->m48 >> 1) & 1) != 0 &&
            FUN_00e393b0(FUN_00b3d410()) == 0)
            bVar4 = 1;
        else
            bVar4 = 0;
        if (cVar2 == 0 && bVar4 == 0) {
            FUN_0067c960(FUN_0067cac0());
            FUN_005fdf40(FUN_0067cae0());
        }
    }
    if ((m28 | m2c) != 0 || (m40 | m44) != 0) {
        void* ms = MessageServer();
        ((VF4)(*(void***)ms)[0x18 / 4])(ms, 0x685d440, 0, 0, 0);
    }
    return 0;
}