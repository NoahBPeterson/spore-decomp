// Slice s00d30830 -- classifies the object under the cursor into a creature-mode
// command id (the value FUN_00d317e0 and the creature input strategy switch on).
//
// 32-bit x86, MSVC 2008 SP1.  Flags are chosen by the matching tool.

#include "types.h"

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

// --- external callees -------------------------------------------------------
extern "C" void* GetGameContext();                    // 0x00b3d4d0
extern "C" void* FUN_00b3d230();                      // 0x00b3d230
extern "C" void* GameInputManager();                  // 0x00b3d250
extern "C" void* CreatureSettings();                  // 0x00d51660
extern "C" void* App();                               // 0x0067dd10
extern "C" void* GetCameraThing(void* render);        // 0x00b60a50
extern "C" void* NounManager();                       // 0x00b3d300
extern "C" void* FUN_00c9f060(void* p);               // 0x00c9f060
extern "C" bool  FUN_00dd18b0(void* target);          // 0x00dd18b0
extern "C" bool  FUN_00e09ad0(void* target);          // 0x00e09ad0
extern "C" int   ClassifyTarget(void* obj, uint8_t* pHandled);   // 0x00d2ffd0

struct cGameContext {
    char pad0[0x2c];
    int  m2c;                                          // +0x2c
};

struct cSimSystem {
    char FUN_00b5ca60();                               // 0x00b5ca60
};

struct cGameInputManager {
    int GetInteractionMode() {                         // vtable +0x34
        return ((int(__thiscall*)(void*))VFUNC(this, 0x34))(this);
    }
};

struct cSettingsFlags {
    char     pad0[0x6c];
    uint32_t m6c;                                      // +0x6c
};

struct cGameNounManager {
    void* GetAvatar();                                 // 0x00b1fdb0
};

struct cCamera {
    char    pad0[0x314];
    uint8_t m314;                                      // +0x314
    uint8_t m315;                                      // +0x315
};

// The trigger manager's "creature mode" gate.  Kept as its own (inlined) predicate:
// inlining it is what makes cl lay the shared "return 1" block out inline after the
// two compares instead of sinking it past the function's last ret.
static bool IsCreatureMode(int mode)
{
    return mode == 1 || mode == 2;
}

// @ 0x00d30830
int FUN_00d30830(void* p)
{
    int mode = ((cGameContext*)GetGameContext())->m2c;
    if (IsCreatureMode(mode))
        return 1;

    if (((cSimSystem*)FUN_00b3d230())->FUN_00b5ca60() == 1)
        return 0;

    if (((cGameInputManager*)GameInputManager())->GetInteractionMode() == 2) {
        if (p != 0) {
            void* target = ((void*(__thiscall*)(void*, uint32_t))VFUNC(p, 0x0c))(p, 0x17f243b);
            if (target != 0 && FUN_00dd18b0(target))
                return 3;
        }
        return 2;
    }
    if (((cGameInputManager*)GameInputManager())->GetInteractionMode() == 3) {
        if (p != 0) {
            void* target = ((void*(__thiscall*)(void*, uint32_t))VFUNC(p, 0x0c))(p, 0x17f243b);
            if (target != 0 && FUN_00e09ad0(target))
                return 5;
        }
        return 4;
    }

    // Bit 4 of the settings word is the "creature mode disabled" flag.  Naming the
    // shifted byte keeps cl from folding the test into `test byte ptr [eax+0x6c],0x10`.
    unsigned char bits = (unsigned char)(((cSettingsFlags*)CreatureSettings())->m6c >> 4);
    if (bits & 1)
        return 0;

    // Retail calls the input-manager accessor here and discards the result.
    GameInputManager();

    void* app    = App();
    void* render = ((void*(__thiscall*)(void*))VFUNC(app, 0x50))(app);
    cCamera* cam = (cCamera*)GetCameraThing(
        ((void*(__thiscall*)(void*))VFUNC(render, 0x38))(render));
    if (cam != 0 && (cam->m315 != 0 || cam->m314 != 0))
        return 0;

    void* avatar = ((cGameNounManager*)NounManager())->GetAvatar();
    if (*(uint8_t*)((char*)avatar + 0xb5e) != 0)
        return 0;

    void* obj = FUN_00c9f060(p);
    if (obj == 0)
        return 0x1c;

    uint8_t handled = 0;
    int result = ClassifyTarget(obj, &handled);
    if (!handled)
        return 0x1c;
    return result;
}
