// Slice s00d48f20 -- Creature editor ability / panel helpers in SporeApp.exe
// (0x00d48f20..0x00d49b5?).
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP /arch:SSE /GS-.

#include "types.h"

// Declare N throwaway virtuals so a named slot lands at the right vtable index.
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV1 PV
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// GUI widget returned by the CreatureGUI lookup (0x00d48b50).  Only the slots
// touched by this slice are named; the rest are padding virtuals so each named
// slot lands at the right vtable index.
// ---------------------------------------------------------------------------
struct GUIWidget {
    PV2 PV1
    virtual GUIWidget* Slot0C(unsigned id);            // +0x0c
    PV4 PV2
    virtual void Slot28(int a, int b);                 // +0x28
    PV8 PV8 PV4
    virtual void Slot7C(int a, int b);                 // +0x7c
    PV8 PV4
    virtual int  SlotB0();                             // +0xb0
    virtual void* SlotB4(int a);                       // +0xb4
};

extern "C" GUIWidget* CreatureGUI(const char* name);        // 0x00d48b50

// SP::NounManager() (0x00b3d300) -> cGameNounManager, GetAvatar() (0x00b1fdb0).
struct Avatar;
struct cGameNounManager {
    Avatar* GetAvatar();
};
extern "C" cGameNounManager* SP_NounManager(void);          // 0x00b3d300

// The avatar object (Simulator::cCreatureBase).  Non-virtual bits used here:
//   +0xe70 / +0xe74  current-verb ids,  +0xb4 vtable slot -> verb-icon tray.
struct Avatar {
    PV8 PV8 PV8 PV4 PV4 PV8 PV4
    virtual int   SlotB0();                                 // +0xb0
    virtual void* SlotB4(int a);                            // +0xb4
    char pad0[0xe6c];
    int  mE70;                                              // +0xe70
    int  mE74;                                              // +0xe74
    void* ApplyCombatTarget();                              // 0x00c0ee90
};

// SP::GetCurrentGameMode() (0x00b5b800): returns the active game-mode singleton.
extern "C" void* SP_GetCurrentGameMode(void);               // 0x00b5b800

// Ability helpers.
extern "C" void* FUN_00d1e610(void);                        // 0x00d1e610
extern "C" void* FUN_00d1e830(int a);                       // 0x00d1e830
extern "C" int   FUN_00d2e490(void);                        // 0x00d2e490
extern "C" int   FUN_00d1f650(void* p, int a);              // 0x00d1f650
extern "C" int   FUN_00d1fb30(int a);                       // 0x00d1fb30
extern "C" float ScoreAbilityRange(int idx);                // 0x00d200a0
void sPlayerUseAbility(unsigned param);                      // 0x00d495b0 (defined below)

// Verb-icon tray helpers.
extern "C" void* GetImageFromLayout(void* img);             // 0x00458de0
extern "C" void  FUN_00806aa0(GUIWidget* w, void* img, int a);   // 0x00806aa0
extern "C" void  SetTooltipText(GUIWidget* w, const wchar_t* t,
                                int a, int b);              // 0x00806de0

// A text object embedded at +0x14 of the verb-icon tray.
struct cTextObj {
    char pad[0x14];
    const wchar_t* GetText();                               // 0x006b55c0
};

struct AbilityUI {
    char    pad0[0x14];
    cTextObj mText;                                         // +0x14
    void*   mImage;                                         // +0x28
};

struct AbilityEntry { char pad0[4]; float mValue; char pad1[8]; };
struct AbilityData {
    char           pad[0xc28];
    AbilityEntry*  mBegin;                                  // +0xc28
    AbilityEntry*  mEnd;                                    // +0xc2c
};

// A noun/record with a type word at +0x08 (SRM::type) plus the owning
// creature's ability-slot index at +0x0c.
struct CmpObj {
    char pad0[8];
    int  mType;                                             // +0x08
    int  mField0C;                                          // +0x0c
};

// Button -> ability map consulted by the verb tray controller.
// 0x0169e3ec points at 8-byte entries: a dword ability id plus a byte flag.
struct AbilitySlot {
    int  mAbility;                                          // +0x00
    char mFlag;                                             // +0x04
    char pad1[3];
};
extern AbilitySlot* g_169e3ec;                              // 0x0169e3ec

extern "C" char sGetButtonCategoryFromButtonID(int button, int* pCat, int* pIdx); // 0x00d48bc0
extern "C" void FUN_00d2e4a0(int a, int b);                 // 0x00d2e4a0 SetCreatureDisplayMode
extern "C" char FUN_00d1fa20(void* ability);                // 0x00d1fa20 IsAbilityAvailable
extern "C" void* FUN_00d1e660(void);                        // 0x00d1e660
extern "C" void FUN_00d48d30(void);                         // 0x00d48d30 (verb-tray refresh)

// Sound-effect / message dispatch helpers used by the verb-tray click handler.
struct HashThing;
extern "C" HashThing* FUN_0067cac0(unsigned hash);          // 0x0067cac0
struct HashThing {
    void FUN_0067c830();                                    // 0x0067c830
};
extern "C" unsigned GetRecorderState(void);                 // 0x00435e90
extern "C" void KillSetiEffects(int a, int b);              // 0x00435ed0
extern "C" void FUN_00d48b00(int ability);                  // 0x00d48b00

// Combat-target holder reached through the DST global at 0x016c7aa4.
struct CombatHolder {
    char pad0[0x78];
    void* mField78;
};
extern CombatHolder* g_16c7aa4;                             // 0x016c7aa4

struct AttackTargeter {
    bool FUN_00f1b360(void* target);                        // 0x00f1b360
};

// ===========================================================================
// @ 0x00d48f20  FUN_00d48f20
// ===========================================================================
bool FUN_00d48f20(CmpObj* param_1)
{
    switch (param_1->mType) {
    case 0xd: case 0x10: case 0x11: case 0x12:
    case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23: case 0x24:
    case 0x25: case 0x27: case 0x31: case 0x32: case 0x33:
        break;
    case 0x3d: case 0x3e: case 0x40: case 0x41: case 0x42: case 0x48: case 0x49:
    case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f: case 0x50:
    case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57:
        return SP_GetCurrentGameMode() == (void*)0x1654c10;
    case 5: case 6: case 7:
    case 0x2b: case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
    case 0x3a: case 0x3b:
        return SP_GetCurrentGameMode() == (void*)0x1654c02;
    default:
        return false;
    }
    return SP_GetCurrentGameMode() == (void*)0x1654c01 ||
           SP_GetCurrentGameMode() == (void*)0x1654c10;
}

// ===========================================================================
// @ 0x00d48ff0  FUN_00d48ff0
// ===========================================================================
int FUN_00d48ff0(CmpObj* param_1)
{
    switch ((int)SP_GetCurrentGameMode()) {
    case 0x1654c02:
        switch (param_1->mType) {
        case 5: case 0x34: case 0x35: case 0x36: case 0x3b:
            return 0;
        case 6: case 0x37: case 0x38: case 0x39: case 0x3a:
            return 1;
        case 7: case 0x2b:
            return 2;
        default:
            return -1;
        }
        break;
    case 0x1654c01:
    case 0x1654c10:
        break;
    default:
        return -1;
    }
    switch (param_1->mType) {
    case 0xd: case 0x20: case 0x23: case 0x42: case 0x48: case 0x4f: case 0x52: case 0x56:
        return 3;
    case 0x10: case 0x1e: case 0x25: case 0x31: case 0x32: case 0x33: case 0x3e: case 0x4a:
    case 0x4d: case 0x54:
        return 0;
    case 0x11: case 0x1f: case 0x22: case 0x3d: case 0x49: case 0x4c: case 0x53: case 0x55:
        return 1;
    case 0x12: case 0x21: case 0x24: case 0x40: case 0x41: case 0x4b: case 0x4e: case 0x51:
        return 2;
    case 0x27: case 0x50:
        return 4;
    default:
        return -1;
    }
}

// ===========================================================================
// @ 0x00d49110  FUN_00d49110
// ===========================================================================
bool FUN_00d49110(int a)
{
    CmpObj* p = (CmpObj*)FUN_00d1e830(a);
    if (p != 0) {
        switch (p->mType) {
        case 0x11: case 0x12: case 0x51: case 0x53:
            return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00d49190  FUN_00d49190
// ===========================================================================
void FUN_00d49190(void)
{
    GUIWidget* w = CreatureGUI((const char*)0x7e495e0);
    if (w != 0) {
        w->Slot7C(1, 0);
    }
}

// ===========================================================================
// @ 0x00d491b0  FUN_00d491b0
// ===========================================================================
void FUN_00d491b0(char param)
{
    cGameNounManager* mgr = SP_NounManager();
    Avatar* av = mgr->GetAvatar();
    int mode = FUN_00d2e490();
    int id;
    switch (mode) {
    case 1:
        id = av->mE70;
        break;
    case 0:
        id = av->mE74;
        break;
    default:
        return;
    }
    if (id == -1) {
        return;
    }
    GUIWidget* w = CreatureGUI((const char*)0x7e45040);
    if (w == 0) {
        return;
    }
    if (param != 0) {
        GUIWidget* w2 = CreatureGUI((const char*)0x7e495e0);
        if (w2 != 0) {
            w2->Slot7C(1, 1);
        }
    }
    cGameNounManager* mgr2 = SP_NounManager();
    Avatar* av2 = mgr2->GetAvatar();
    AbilityUI* x = (AbilityUI*)av2->SlotB4(id);
    void* img = GetImageFromLayout(x->mImage);
    FUN_00806aa0(w, img, 0);
    SetTooltipText(w, x->mText.GetText(), -1, 1);
}

// ===========================================================================
// @ 0x00d49270  FUN_00d49270
// ===========================================================================
int FUN_00d49270(int param_1)
{
    GUIWidget* p = (GUIWidget*)FUN_00d1e610();
    if (p != 0) {
        if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
            AttackTargeter* f = (AttackTargeter*)g_16c7aa4->mField78;
            cGameNounManager* mgr = SP_NounManager();
            Avatar* av = mgr->GetAvatar();
            void* t = av->ApplyCombatTarget();
            if (f->FUN_00f1b360(t)) {
                return 1;
            }
        }
        int n = p->SlotB0();
        if (param_1 < n) {
            return FUN_00d1f650(p, param_1);
        }
        if (SP_GetCurrentGameMode() == (void*)0x1654c02 && param_1 - n < 6) {
            return FUN_00d1fb30(param_1 - n);
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00d49300  sActivatePanel
// ===========================================================================
void sActivatePanel(int param_1)
{
    GUIWidget* w = CreatureGUI((const char*)0x4c61b50);
    int mode;
    if (param_1 == 1) {
        GUIWidget* a = (w == 0) ? (GUIWidget*)0 : w->Slot0C(0x8ed27e7a);
        a->Slot28(4, 0);
        GUIWidget* b = CreatureGUI((const char*)0x4c61dd9);
        if (b == 0) {
            ((GUIWidget*)0)->Slot28(4, 1);
        }
        else {
            b->Slot0C(0x8ed27e7a)->Slot28(4, 1);
        }
        mode = 0;
    }
    else {
        GUIWidget* a = (w == 0) ? (GUIWidget*)0 : w->Slot0C(0x8ed27e7a);
        a->Slot28(4, 1);
        GUIWidget* b = CreatureGUI((const char*)0x4c61dd9);
        if (b == 0) {
            ((GUIWidget*)0)->Slot28(4, 0);
        }
        else {
            b->Slot0C(0x8ed27e7a)->Slot28(4, 0);
        }
        mode = 1;
    }
    GUIWidget* g = CreatureGUI(mode == 0 ? (const char*)0x53efdc8 : (const char*)0x53efdc0);
    if (g != 0) {
        g->Slot7C(1, 0);
    }
    const char* name;
    if (param_1 == 0) {
        name = (const char*)0x53efdc8;
    }
    else if (param_1 == 1) {
        name = (const char*)0x53efdc0;
    }
    else {
        name = 0;
    }
    GUIWidget* h = CreatureGUI(name);
    if (h != 0) {
        h->Slot7C(1, 4);
    }
}

// ===========================================================================
// @ 0x00d49450  FUN_00d49450
// ===========================================================================
void FUN_00d49450(void)
{
    AbilitySlot* t = g_169e3ec;
    for (int i = 0; i < 0x19; i++) {
        t[i].mAbility = -1;
        t[i].mFlag = 0;
    }
    GUIWidget* p = (GUIWidget*)FUN_00d1e610();
    if (p == 0) {
        return;
    }
    int n = p->SlotB0();
    for (int i = 0; i < n; i++) {
        CmpObj* x = (CmpObj*)p->SlotB4(i);
        if (FUN_00d48f20(x) && FUN_00d1fa20(x)) {
            int k = FUN_00d48ff0(x);
            if (k >= 0) {
                g_169e3ec[k + x->mField0C * 5].mAbility = i;
            }
        }
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
        for (int j = 0; j < 6; j++) {
            CmpObj* a = (CmpObj*)*(int*)((char*)FUN_00d1e660() + 0x34 + j * 4);
            if (FUN_00d48f20(a) && FUN_00d1fa20(a)) {
                int k = FUN_00d48ff0(a);
                if (k >= 0) {
                    g_169e3ec[k + a->mField0C * 5].mAbility = n + j;
                }
            }
        }
    }
    FUN_00d48d30();
}

// ===========================================================================
// @ 0x00d49560  FUN_00d49560
// ===========================================================================
float FUN_00d49560(int idx)
{
    AbilityData* p = (AbilityData*)FUN_00d1e610();
    if (p != 0) {
        if (idx >= 0) {
            int n = (int)(p->mEnd - p->mBegin);
            if (idx < n) {
                return p->mBegin[idx].mValue;
            }
        }
        if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
            return ScoreAbilityRange(idx);
        }
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x00d495b0  sPlayerUseAbility
// ===========================================================================
void sPlayerUseAbility(unsigned param)
{
    int r = FUN_00d49270((int)param);
    cGameNounManager* mgr = SP_NounManager();
    Avatar* av = mgr->GetAvatar();
    if (av != 0) {
        Avatar* av2 = SP_NounManager()->GetAvatar();
        int m = FUN_00d2e490();
        int verb1;
        if (m == 0) {
            verb1 = av2->mE74;
        }
        else if (m == 1) {
            verb1 = av2->mE70;
        }
        else {
            verb1 = -1;
        }
        if (param != (unsigned)-1) {
            int n = av->SlotB0();
            if ((int)param < n) {
                CmpObj* x = (CmpObj*)av->SlotB4((int)param);
                if (x->mField0C == 0) {
                    av->mE74 = (int)param;
                }
                else if (x->mField0C == 1) {
                    av->mE70 = (int)param;
                }
            }
        }
        Avatar* av3 = SP_NounManager()->GetAvatar();
        int m2 = FUN_00d2e490();
        int verb2;
        if (m2 == 0) {
            verb2 = av3->mE74;
        }
        else if (m2 == 1) {
            verb2 = av3->mE70;
        }
        else {
            verb2 = -1;
        }
        if (verb1 != verb2) {
            GUIWidget* w = CreatureGUI((const char*)0x7e495e0);
            if (w != 0) {
                w->Slot7C(1, 0);
            }
        }
    }
    switch (r) {
    case 0:
        if (!FUN_00d49110((int)param)) {
            unsigned st = GetRecorderState();
            KillSetiEffects(0xa03e74b2, st);
        }
        FUN_00d48b00((int)param);
        return;
    case 2:
        FUN_0067cac0(0xc30cd054)->FUN_0067c830();
        return;
    case 3:
    case 4:
        if (SP_GetCurrentGameMode() != (void*)0x1654c10) {
            FUN_0067cac0(0xcf540d88)->FUN_0067c830();
            return;
        }
        break;
    case 6:
        FUN_0067cac0(0x893133b0)->FUN_0067c830();
        return;
    case 8:
        FUN_0067cac0(0x5b8e12c)->FUN_0067c830();
        return;
    case 10:
        if (SP_GetCurrentGameMode() == (void*)0x1654c01) {
            FUN_0067cac0(0x55e2f180)->FUN_0067c830();
            return;
        }
        FUN_0067cac0(0x423b4b69)->FUN_0067c830();
        return;
    case 0xb:
        FUN_0067cac0(0xf9ff317c)->FUN_0067c830();
        return;
    case 0xc:
        FUN_0067cac0(0x3b052a35)->FUN_0067c830();
        return;
    case 0xd:
        FUN_0067cac0(0xa551b66a)->FUN_0067c830();
        return;
    case 0xe:
        FUN_0067cac0(0xe3177a43)->FUN_0067c830();
        return;
    case 0xf:
        FUN_0067cac0(0xa0dfbc77)->FUN_0067c830();
        break;
    }
}

// ===========================================================================
// @ 0x00d49820  FUN_00d49820
// ===========================================================================
bool FUN_00d49820(int param_1)
{
    int iVar3, iVar4;
    int local_8, local_4;
    switch ((int)SP_GetCurrentGameMode()) {
    case 0x1654c02:
        if (param_1 == 0x4c61b50) {
            return 0;
        }
        if (param_1 == 0x4c61dd9) {
            return 0;
        }
        break;
    case 0x1654c01:
    case 0x1654c10:
        iVar3 = FUN_00d2e490();
        if (param_1 == 0x4c61b50) {
            FUN_00d2e4a0(0, 1);
            iVar4 = FUN_00d2e490();
            if (iVar3 != iVar4) {
                GUIWidget* p = CreatureGUI((const char*)0x7e495e0);
                if (p != 0) {
                    p->Slot7C(1, 0);
                }
            }
            return 1;
        }
        if (param_1 == 0x4c61dd9) {
            FUN_00d2e4a0(1, 1);
            iVar4 = FUN_00d2e490();
            if (iVar3 == iVar4) {
                return 1;
            }
            FUN_00d49190();
            return 1;
        }
        break;
    }
    if (sGetButtonCategoryFromButtonID(param_1, &local_4, &local_8)) {
        int v = g_169e3ec[local_4 + local_8 * 5].mAbility;
        if (v != -1) {
            sPlayerUseAbility(v);
            return 1;
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00d49920  FUN_00d49920
// ===========================================================================
bool FUN_00d49920(unsigned param)
{
    cGameNounManager* mgr = SP_NounManager();
    if (mgr->GetAvatar() != 0) {
        sPlayerUseAbility(param);
        return true;
    }
    return false;
}