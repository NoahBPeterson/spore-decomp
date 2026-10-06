// slice s00ee16f0 -- UI::cScenarioTutorialsChecklistUI::Refresh (single 4,452-byte function).
//
// PARTIAL: the full body is ~4.4 KB of widget-refresh code with hundreds of inlined
// vtable queries (FUN_00...); only the prologue, the early-out guard and the epilogue
// are reproduced faithfully below.  The dense middle section is not transcribed.
#include "types.h"

struct Manager {};
struct GlobalObj {
    char pad0[0x74];
    Manager* f74;
};
extern GlobalObj* g_16c7aa4;

struct CChecklist {
    char  pad0[0x10];
    void* f10;               // +0x10 layout
    char  pad1[0x18 - 0x14];
    void* f18;               // +0x18
    char  pad2[0x20 - 0x1c];
    int   f20;               // +0x20
    char  pad3[0x48 - 0x24];
    char  f48;               // +0x48
};

int   __cdecl   ScenarioTutorials_GetActive();
void* __fastcall FUN_00f3be30(void*, int);          // manager count
void* __fastcall FUN_00f3e8a0(void*, int, int key); // manager find
void  __cdecl   FUN_00ed8a30(int a, int b);
void  __cdecl   FUN_00ed9990(void* p, int a);
bool  __cdecl   cSPUILayout_IsVisible(void* layout);

// @ 0x00ee16f0
void __fastcall f_ee16f0(CChecklist* c)
{
    int mode = ScenarioTutorials_GetActive();
    int count = 1;
    Manager* mgr = g_16c7aa4->f74;
    if (mgr != 0)
        count = (int)FUN_00f3be30(mgr, 0);
    void* e = (mgr != 0) ? FUN_00f3e8a0(mgr, 0, c->f20) : 0;
    if (!cSPUILayout_IsVisible(c->f10))
        goto end;
    if (e == 0)
        goto end;
    // ---- omitted: ~4.4 KB of widget refresh (checklist rows, hint buttons, images,
    //      locale-formatted counts, per-category window updates). ----
    (void)count;

end:
    FUN_00ed8a30(c->f20, mode);
    FUN_00ed9990(&c->f48, 1);
}
