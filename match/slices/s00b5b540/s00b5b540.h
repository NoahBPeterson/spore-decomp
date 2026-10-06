// Slice s00b5b540 (batch bfs1) — shared types.
// Module "Spore"; SP::cGonzagoSubsystem (two polymorphic bases: IUnknown-ish
// primary vtable at +0 and RefCount vtable at +4; state ints at +0xc..+0x18).

#pragma once
#include "types.h"

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

// Small interface stubs used by the wrapper thunks.
struct GameModeObj
{
    int GetLocation();          // 0x00a42730
    int FUN_00ff35d0();         // 0x00ff35d0
};

struct MsgObj
{
    void FUN_00dd18d0(int);
};

// Free functions in this slice.
extern "C" void FUN_00b5b690(int);
extern "C" void FUN_00b5b6f0(int);
extern "C" int  FUN_00b5b800();
extern "C" int  FUN_00b5b820();
extern "C" void FUN_00b5b730();
extern "C" bool FUN_00b5cb20(int);
extern "C" bool FUN_00b5cb60(int, int*);
extern "C" bool FUN_00b5cb80(int, int*);
extern "C" bool FUN_00b5cba0(int, int*);
extern "C" bool FUN_00b5cbc0(int, int*);
extern "C" bool FUN_00b5cbe0(int, int*);
extern "C" bool FUN_00b5cc00(int, int*);
extern "C" bool FUN_00b5ca70();
extern "C" void FUN_00b5c990();
extern "C" void FUN_00b5cc80();
extern "C" int  FUN_00b5c9d0(void*);
extern "C" bool FUN_00b5cde0(int);
extern "C" void FUN_00b5ca50();
extern "C" void FUN_00b5cd90(void*, int);
extern "C" void FUN_00b5be10(void*, void*);
extern "C" bool FUN_00b5be60(void*, void*);
extern "C" bool FUN_00b5bf30(void*, void*);
extern "C" bool FUN_00b5bf80(void*, void*);
extern "C" void FUN_00b5b540_fwd();
extern "C" void FUN_00b5ba30(int);
extern "C" void FUN_00b5ce70(void*, int);