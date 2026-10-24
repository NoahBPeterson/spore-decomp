// Slice s00df2d80 -- SP galaxy-game-entry UI state-machine helpers
// (SporeApp.exe 0x00df2d80..0x00df3bdc): the random-asset pickers that feed the
// "New Game" flow plus the editor->game transition helper.
//
// Two very large siblings in this slice (SetLevel 0x00df2ea0, Init 0x00df32d0)
// are categorised partial / no source.
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).

#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------
struct IWindow {                                   // a cSPUIWindow / cSPUILayout window
    PV2 PV
    PV4 PV2 PV                                     // +0x0c..+0x24  (unused slots)
    virtual char     Slot28();                     // +0x28  -> predicate (low byte)
    virtual unsigned Slot2C();                     // +0x2c  -> state value
    PV8 PV8 PV2 PV                                 // +0x30..+0x78  (unused slots)
    virtual void     Slot7C(int a, int b);         // +0x7c  SetVisible/flag
};

struct SPUILayout {
    char pad[0x18];
    IWindow* FindWindowByID(unsigned id, int flag); // 0x008105b0  __thiscall
};

struct GGE {                                        // kGUI_PanelIDs
    char pad00[0x103];
    char m103;                                      // +0x103
    void Fn53d0(int);                               // 0x00de53d0
};
extern GGE* kGUI_PanelIDs;                          // 0x016a1344
extern char DAT_016a0f78;                           // a config byte

void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0

// 12-byte resource key.
struct Key { int a; int b; int c; };

// ---------------------------------------------------------------------------
// The UI state machine and its embedded impl sub-object
// ---------------------------------------------------------------------------
struct GameEntry {                                  // object at StateMachine+0x628
    char pad00[0x4c];
    Key  m4c;                                       // +0x4c
    char pad58[0x0c];                               // +0x58..+0x63
    Key  m64;                                       // +0x64
    Key  m70;                                       // +0x70
    char pad7c[0x14];                               // +0x7c..+0x8f
    int  m90;                                       // +0x90
    char pad94[0x10];                               // +0x94..+0xa3
    int  mA4;                                       // +0xa4
    int  mA8;                                       // +0xa8
};

struct StateMachine {
    char pad00[0x28];
    SPUILayout mLayout;                             // +0x28
    char pad40[0x5e8];                              // +0x40..+0x627
    GameEntry* mEntry;                              // +0x628

    void PickRandomVehicle();                       // 0x00df2d80
    void OnAssetBrowserSelection(Key* p);           // 0x00df21d0  (ret 4)
    void SelectNextState();                         // 0x00df2550
    void PickRandomCreature();                      // 0x00df2bb0
    void PickRandomAssets(char flag);               // 0x00df3ab0  (ret 4)
    void PickRandomByMode(unsigned id, int tag, Key* key); // 0x00df2a60  (ret 0xc)
};

// cGalaxyGameEntryImpl lives at StateMachine+8 and owns the layout at +0x20.
struct Impl {
    char pad00[0x20];
    SPUILayout mLayout;                             // +0x20
    char pad38[0x34];                               // +0x38..+0x6b
    int  m6c;                                       // +0x6c
    char pad70[0x570];                              // +0x70..+0x5df
    int  m5e0;                                      // +0x5e0

    void TestEditorToGame(int* p);                  // 0x00df2e20  (ret 4)
};

// The 0x630-byte "Simulator" object allocated by FUN_00df3a70.
struct Sim {
    char pad[0x630];
    Sim* Ctor();                                    // 0x00df0c00  (returns this)
    void Fn3410();                                  // 0x00df3410
};

struct Holder { char pad[8]; Sim* m8; };            // object taking the new Simulator

// ---------------------------------------------------------------------------
// Bodies
// ---------------------------------------------------------------------------

// @ 0x00df2d80
void StateMachine::PickRandomVehicle()
{
    GameEntry* p = this->mEntry;
    switch (p->mA4) {
    case 4:
        switch (p->m90) {
        case 0:
            this->PickRandomByMode(0x54045e3, 0x7d433fad, &p->m64);
            return;
        case 1:
            this->PickRandomByMode(0x54045e3, 0x9ad7d4aa, &p->m64);
            return;
        case 2:
            this->PickRandomByMode(0x54045e3, 0xf670aa43, &p->m64);
            return;
        }
        break;
    case 5:
        this->PickRandomByMode(0x54045e3, 0x98e03c0d, &p->m64);
        return;
    }
    this->PickRandomByMode(0x54045e3, (int)this, &p->m64);
}

// @ 0x00df2e20
void Impl::TestEditorToGame(int* p)
{
    IWindow* w = this->mLayout.FindWindowByID(0x5384881, 1);
    w->Slot7C(1, 1);
    kGUI_PanelIDs->Fn53d0(1);
    kGUI_PanelIDs->m103 = 1;
    if (*p != 0) {
        char b = (this->m6c == 2);
        if (this->m5e0 == 0x54045ce && (b || DAT_016a0f78 != 0))
            b = 1;
        StateMachine* sm = (StateMachine*)((char*)this - 8);
        sm->OnAssetBrowserSelection((Key*)p);
        if (b)
            sm->SelectNextState();
    }
}

// @ 0x00df3a70
void __fastcall FUN_00df3a70(Holder* h)
{
    Sim* o = (Sim*)operator_new(0x630, "Simulator", 0, 0, 0, 0);
    if (o)
        o = o->Ctor();
    else
        o = 0;
    h->m8 = o;
    o->Fn3410();
}

// @ 0x00df3ab0
void StateMachine::PickRandomAssets(char flag)
{
    if (this->mEntry == 0)
        return;

    IWindow* w = this->mLayout.FindWindowByID(0x59461b1, 1);
    if (w == 0 || (((char)(w->Slot2C() >> 2)) & 1) == 0) {
        IWindow* w2 = this->mLayout.FindWindowByID(0x54045ce, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m4c.a == 0))
            this->PickRandomCreature();
    }

    w = this->mLayout.FindWindowByID(0x59461b0, 1);
    if (w == 0 || (((char)(w->Slot2C() >> 2)) & 1) == 0) {
        IWindow* w2 = this->mLayout.FindWindowByID(0x54045e3, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m64.a == 0))
            this->PickRandomVehicle();
    }

    w = this->mLayout.FindWindowByID(0x59461b2, 1);
    if (w == 0 || (((char)(w->Slot2C() >> 2)) & 1) == 0) {
        IWindow* w2 = this->mLayout.FindWindowByID(0x5404617, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m70.a == 0))
            this->PickRandomByMode(0x5404617, 0x99e92f05, &this->mEntry->m70);
    }
}

// @ 0x00df2ea0  (partial / no source: SP::cGalaxyGameEntryUIStateMachine::SetLevel, 1068 bytes)
// @ 0x00df32d0  (partial / no source: SP::cGalaxyGameEntryUIStateMachine::Init, 1940 bytes)