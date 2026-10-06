// Slice s00f447f0 -- unnamed scenario/action system, slice 8 of bfs1.
// All five functions are large, highly specialized scenario resource/action routines; they are
// recorded as partial skeletons (control flow not reconstructed).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct ScenarioObj8 {
    char pad00[0x10];
    void* mpManager;   // +0x10

    // @ 0x00f447f0
    int  f447f0(char flag);
    // @ 0x00f44a40
    int  f44a40(int idx);
    // @ 0x00f44bf0
    int  f44bf0(void* msg);
    // @ 0x00f44dd0
    void f44dd0();
    // @ 0x00f44fe0
    char f44fe0();
};

// @ 0x00f447f0
// Scenario-mode init: creates the ScenarioResource (0x2cb0) and ScenarioEconomy (0x30), resets the
// global log-reporter/log list, optionally seeds the scenario state and registers 3 message handlers.
int ScenarioObj8::f447f0(char flag)
{
    (void)flag;
    return 1;
}

// @ 0x00f44a40
// Inserts an action element at index idx (bounds-checked to 1..7), then grows per-action vectors.
int ScenarioObj8::f44a40(int idx)
{
    (void)idx;
    return -1;
}

// @ 0x00f44bf0
// Applies a serialized scenario tag/asset message (two GetManager lookups + tag string).
int ScenarioObj8::f44bf0(void* msg)
{
    (void)msg;
    return 0;
}

// @ 0x00f44dd0
// Reinitializes the scenario manager state (large aligned frame, rebuilds action/economy state).
void ScenarioObj8::f44dd0()
{
}

// @ 0x00f44fe0
// 1532-byte scenario save/load/rebuild routine.
char ScenarioObj8::f44fe0()
{
    return 0;
}
