// src/game/SPGonzago/SPGonzagoSubsystem.cpp -- migrated from slice(s) s00b5b540 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoSubsystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/eGameMode.h"
#include "SP/cGonzagoSubsystem.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  FUN_00b5b820();
extern "C" void* FUN_00b3d320();
extern char g_vt0dummy, g_vt1dummy;

// ---- items of slice s00b5b540 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cGonzagoSubsystem
{
    void** vt0;         // +0x00  primary vtable
    void** vt4;         // +0x04  refcount vtable
    int    m08;         // +0x08
    int    mPreMode;    // +0x0c  mPreModeTransitionState
    int    mPostMode;   // +0x10  mPostModeTransitionState
    int    mCurrent;    // +0x14  mCurrentTransition
    int    mPhase;      // +0x18  mCurrentTransitionPhase
    char   pad_1c[0x400];

    cGonzagoSubsystem();                        // @ 0x00b5b960
    ~cGonzagoSubsystem();                       // @ 0x00b5b9a0
    void* ScalarDeletingDtor(char);             // @ 0x00b5b9b0
    bool  CheckGonzagoSubsystemInitState(int);  // @ 0x00b5b840
    void  PostGameModeTransition(int, int);     // @ 0x00b5b900
    void  PreGameModeTransition(int, int);      // @ 0x00b5b930
    void  SetTransitionState1(int);             // @ 0x00b5b880
    void  SetTransitionState2(int);             // @ 0x00b5b8a0
    void  EndTransitionPre();                   // @ 0x00b5b8c0
    void  EndTransitionPost();                  // @ 0x00b5b8e0
};
struct GameModeObj
{
    int GetLocation();          // 0x00a42730
    int FUN_00ff35d0();         // 0x00ff35d0
};
extern "C" int  FUN_00b5b820();
extern "C" void* FUN_00b3d320();
extern char g_vt0dummy, g_vt1dummy;
// ---- items of slice s00b5b540 end

// @ 0x00b5b800
namespace SP {
eGameMode GetCurrentGameMode()
{
    GameModeObj* p = (GameModeObj*)FUN_00b3d320();
    if (p) return (SP::eGameMode)(p->GetLocation());
    return (SP::eGameMode)(-1);
}
}  // namespace SP

// @ 0x00b5b820
int FUN_00b5b820()
{
    GameModeObj* p = (GameModeObj*)FUN_00b3d320();
    if (p) return p->FUN_00ff35d0();
    return -1;
}

// @ 0x00b5b840
bool cGonzagoSubsystem::CheckGonzagoSubsystemInitState(int param)
{
    if (param != ((int(__thiscall*)(void*))vt0[0x1c / 4])(this)) return false;
    if (param != ((int(__thiscall*)(void*))vt0[0x20 / 4])(this)) return false;
    if (mCurrent != -1) return false;
    return true;
}

// @ 0x00b5b880
void cGonzagoSubsystem::SetTransitionState1(int p)
{
    mPhase = 1;
    if (mCurrent == -1) mCurrent = p;
}

// @ 0x00b5b8a0
void cGonzagoSubsystem::SetTransitionState2(int p)
{
    mPhase = 2;
    if (mCurrent == -1) mCurrent = p;
}

// @ 0x00b5b8c0
void cGonzagoSubsystem::EndTransitionPre()
{
    mPreMode = mCurrent;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b8e0
void cGonzagoSubsystem::EndTransitionPost()
{
    mPostMode = mCurrent;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b900
void cGonzagoSubsystem::PostGameModeTransition(int, int mode)
{
    if (((int(__thiscall*)(void*))vt0[0x20 / 4])(this) != mode)
    {
        ((void(__thiscall*)(void*, int))vt0[0x44 / 4])(this, mode);
        ((void(__thiscall*)(void*))vt0[0x4c / 4])(this);
    }
}

// @ 0x00b5b930
void cGonzagoSubsystem::PreGameModeTransition(int, int mode)
{
    if (((int(__thiscall*)(void*))vt0[0x1c / 4])(this) != mode)
    {
        ((void(__thiscall*)(void*, int))vt0[0x40 / 4])(this, mode);
        ((void(__thiscall*)(void*))vt0[0x48 / 4])(this);
    }
}

// @ 0x00b5b960
cGonzagoSubsystem::cGonzagoSubsystem()
{
    vt4 = (void**)&g_vt1dummy;
    m08 = 0;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    mPreMode = -1;
    mPostMode = -1;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b9a0
cGonzagoSubsystem::~cGonzagoSubsystem()
{
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
}
