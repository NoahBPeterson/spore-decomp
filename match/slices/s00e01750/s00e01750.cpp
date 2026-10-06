// Slice s00e01750 (batch bfs3, slice 14). Region 0xe01750-0xe02572.
// Global options UI: window-proc dispatch, activation, tooltips, and the
// context-sensitive Sporepedia / SporeGuide launchers.
// Optimised: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380

extern "C" void* __cdecl SP_GetCurrentGameMode();                // 0xb5b800
extern "C" void* __cdecl SP_MessageServer();                     // 0x67dcc0
extern "C" void* __cdecl SP_WindowManager();                     // 0x67caa0
extern "C" void* __cdecl SP_GameTimeManager();                   // 0xb3d380
extern "C" void* __cdecl SP_EffectsManager();                    // 0x67ddd0
extern "C" void  __cdecl SPUI_BeginModal();
extern "C" void  __cdecl SPUI_EndModal();
extern "C" void  __cdecl FUN_00e00db0(void*, float);
extern "C" void  __cdecl FUN_00e01990();
extern "C" void  __cdecl FUN_00e01cc0();
extern "C" void* __cdecl FUN_009512c0();
extern "C" void* __cdecl FUN_009512d0();
extern "C" void  __cdecl FUN_0080fee0();
extern "C" void  __cdecl FUN_00810000();
extern "C" void  __cdecl FUN_008120d0();
extern "C" void  __cdecl FUN_00810090();
extern "C" void  __cdecl FUN_00835990();
extern "C" void  __cdecl FUN_00835cc0();
extern "C" void  __cdecl FUN_00835ed0();
extern "C" void  __cdecl FUN_006b55c0();
extern "C" void  __cdecl FUN_005ca960();
extern "C" void  __cdecl FUN_005c2570();
extern "C" void  __cdecl FUN_00b5f950();
extern "C" void  __cdecl FUN_00b32220();
extern "C" void  __cdecl FUN_00b32250();
extern "C" void  __cdecl FUN_00b32280();

struct AutoWin { void* mp; };
struct SPUILayout2 {
    void* FindWindowByID(void* id, int a);
    void  SetVisibility(void* v);
    void  Init(void* a, int b, int c);
    void  SetReloadCallback(void* cb, void* arg);
};

// ===========================================================================
//  0x00e01750  message dispatch (switch on sub-command)
// ===========================================================================
// @ 0x00e01750
char Dispatch(void* self, void* win, void* msg) {
    // Large switch; see nonmatching.txt.
    (void)self; (void)win; (void)msg;
    return 0;
}

// ===========================================================================
//  0x00e018c0  activate/deactivate (modal begin/end)
// ===========================================================================
// @ 0x00e018c0
void Activate(void* self, char on) {
    (void)self; (void)on;
}

// ===========================================================================
//  0x00e01990  large global-options update
// ===========================================================================
// @ 0x00e01990
void GlobalOptionsUpdate() {}

// ===========================================================================
//  0x00e01ce0  nested FindWindowByID
// ===========================================================================
struct Ctl { char pad[8]; void* f08; };
struct GlobalOpts2 {
    char pad[0x5c];
    Ctl* p5c;
    void* FindWin(void* id);
};
// @ 0x00e01ce0
void* GlobalOpts2::FindWin(void* id) {
    if (p5c->f08 != 0) {
        return p5c->f08->FindWindowByID(id, 1);
    }
    return 0;
}

// ===========================================================================
//  0x00e01d00  show transition (timing + visibility)
// ===========================================================================
// @ 0x00e01d00
void ShowTransition(void* self) {
    (void)self;
}

// ===========================================================================
//  0x00e01db0  large global-options update
// ===========================================================================
// @ 0x00e01db0
void GlobalOptionsUpdate2() {}

// ===========================================================================
//  0x00e02040  SP::ShowContextSensitiveSporepedia
// ===========================================================================
// @ 0x00e02040
void ShowContextSensitiveSporepedia(void* arg) { (void)arg; }

// ===========================================================================
//  0x00e02200  SP::ShowContextSensitiveSporeGuide
// ===========================================================================
// @ 0x00e02200
void ShowContextSensitiveSporeGuide(void* arg) { (void)arg; }

// ===========================================================================
//  0x00e02430  create options dialog + tooltips
// ===========================================================================
// @ 0x00e02430
void CreateOptionsDialog(void* self) { (void)self; }
