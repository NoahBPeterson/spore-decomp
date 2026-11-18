// @ 0x00d4a4a0
//
// VerbTray keyboard handler: maps the pressed key to a verb slot for the active
// game mode and activates it.  Retail member offsets are taken from the
// disassembly; only the objects this function touches are modelled.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-

// Declare N throwaway virtuals so a named slot lands at the right vtable index.
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV1 PV
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern "C" void* SP_GetCurrentGameMode(void);      // 0x00b5b800
extern "C" void* SP_NounManager(void);             // 0x00b3d300
extern "C" void* cTribeModeStrategy_Instance(void); // 0x00cd40b0
extern "C" int   FUN_00d2e490(void);               // 0x00d2e490 returns 0x0169e394
extern "C" int   FUN_00d4a370(int slot, int key, int which); // 0x00d4a370 verb lookup
extern "C" void  sPlayerUseAbility(int verb);      // 0x00d495b0

// A verb icon returned by the avatar's tray lookup.
struct VerbIcon {
    char pad00[0x0c];
    int  mKind;                                    // +0x0c
};

// The avatar (Simulator::cCreatureBase); only the tray-lookup slot is named.
struct Avatar {
    PV8 PV8 PV8 PV4 PV4 PV8 PV4
    virtual int       SlotB0();                    // +0xb0
    virtual VerbIcon* SlotB4(int verb);            // +0xb4
};

struct cGameNounManager {
    Avatar* GetAvatar();                           // 0x00b1fdb0
};

// Mode strategy owning the verb table used by the space/tribe game modes.
struct cTribeModeStrategy {
    char pad000[0x390];
    int  mSlot390;                                 // +0x390
};

bool VerbTray_HandleKeyPress(int key)
{
    switch ((int)SP_GetCurrentGameMode()) {
    case 0x1654c10: {
        int verb = FUN_00d4a370(FUN_00d2e490(), key, 0);
        VerbIcon* icon = ((cGameNounManager*)SP_NounManager())->GetAvatar()->SlotB4(verb);
        if (icon != 0 && icon->mKind == 2)
            verb = FUN_00d4a370(FUN_00d2e490(), key, 1);
        if (verb == -1)
            return false;
        sPlayerUseAbility(verb);
        return true;
    }
    case 0x1654c02: {
        // The strategy instance's verb-table slot; read before the other arguments
        // so the instance call is evaluated first, as in the original.
        int slot = ((cTribeModeStrategy*)cTribeModeStrategy_Instance())->mSlot390;
        int verb = FUN_00d4a370(slot, key, 1);
        if (verb == -1)
            break;
        sPlayerUseAbility(verb);
        return true;
    }
    case 0x1654c01: {
        int verb = FUN_00d4a370(FUN_00d2e490(), key, 1);
        if (verb == -1)
            break;
        sPlayerUseAbility(verb);
        return true;
    }
    }
    return false;
}
