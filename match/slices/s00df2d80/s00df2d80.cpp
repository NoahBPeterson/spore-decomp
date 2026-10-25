// Slice s00df2d80 -- SP galaxy-game-entry UI state-machine helpers
// (SporeApp.exe 0x00df2d80..0x00df3bdc): the random-asset pickers that feed the
// "New Game" flow plus the editor->game transition helper.
//
// The two large siblings (SetLevel 0x00df2ea0, Init 0x00df32d0) are complete
// behavioural ports; the inlined eastl hashtable probe and the cString temporaries
// keep them from being byte-exact (recorded in nonmatching.txt).
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
    virtual void     Slot80(const wchar_t* s);     // +0x80  set label text
};

struct SPUILayout {
    char pad[0x18];
    IWindow* FindWindowByID(unsigned id, int flag); // 0x008105b0  __thiscall
};

struct GGE {                                        // kGUI_PanelIDs
    char pad00[0x103];
    char m103;                                      // +0x103
    char pad104[0xb0];                              // +0x104..+0x1b3
    int  mPanelIds[8];                              // +0x1b4  panel-id table indexed by mode/level
    void Fn53d0(int);                               // 0x00de53d0
};
extern GGE* kGUI_PanelIDs;                          // 0x016a1344
extern char DAT_016a0f78;                           // a config byte

void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0

// 12-byte resource key.
struct Key { int a; int b; int c; };

// An eastl hashtable (0x1c bytes).  The bucket array lives at +0x04 and the
// bucket count at +0x08; each node stores its key at +0x00 and its chain link
// at +0x08 (matching the inlined lookup in SetLevel/Init).
struct Hashtable {
    unsigned   m00;              // +0x00
    unsigned** mBuckets;         // +0x04
    unsigned   mBucketCount;     // +0x08
    unsigned   m0c;              // +0x0c
    unsigned   m10;              // +0x10
    unsigned   m14;              // +0x14
    unsigned   m18;              // +0x18
    unsigned*  LookupOrInsert(const void* key);  // 0x00de7630
};

// SP::cString (0x1c bytes).
class cString {
public:
    cString();                                             // 0x006b5060
    cString(unsigned table, unsigned instance, const wchar_t* def); // 0x006b5770
    cString& operator=(const cString& rhs);                // 0x006b5430
    ~cString();                                            // 0x006b5240
    const wchar_t* GetText();                              // 0x006b55c0
private:
    unsigned mData[7];
};

// One entry of the state machine's NewGame flow array (stride 0xc0, base +0x84).
struct tNewGameFlow {
    char      pad00[0x20];       // +0x00..+0x1f
    Hashtable mMap20;            // +0x20  key -> value map used by SetLevel
    char      pad3c[0x10];       // +0x3c..+0x4b
    Key       m4c;               // +0x4c
    char      pad58[0x08];       // +0x58..+0x5f
    unsigned* m60;               // +0x60  begin of {id, textId} pairs
    unsigned* m64;               // +0x64  end
    char      pad68[0x20];       // +0x68..+0x87
    unsigned  m88;               // +0x88  number of enabled flags
    char      pad8c[0x34];       // +0x8c..+0xbf  (stride is 0xc0)
};

extern const unsigned kUIFlagIds[5];        // 0x0147e530
extern const unsigned kUIPanelButtonIds[5]; // 0x0147e4d8

// Hashtable probe matching the inlined chain walk (key at node[0], next at node[2]).
static bool HashHasKey(Hashtable* t, unsigned key)
{
    if (t->mBucketCount == 0)
        return false;
    unsigned* node = (unsigned*)t->mBuckets[key % t->mBucketCount];
    while (node != 0) {
        if (node[0] == key)
            return true;
        node = (unsigned*)node[2];
    }
    return false;
}


// ---------------------------------------------------------------------------
// The UI state machine and its embedded impl sub-object
// ---------------------------------------------------------------------------
struct GameEntry {                                  // object at StateMachine+0x628
    char pad00[0x20];                               // +0x00..+0x1f
    unsigned short* m20;                            // +0x20  begin of a 16-bit vector
    unsigned short* m24;                            // +0x24  end
    char pad28[0x24];                               // +0x28..+0x4b
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
    char pad00[0x28];                               // +0x00..+0x27
    SPUILayout mLayout;                             // +0x28
    char pad40[0x41];                               // +0x40..+0x80
    unsigned char m81;                              // +0x81  "herbivore layout chosen" flag
    char pad82[0x02];                               // +0x82..+0x83
    tNewGameFlow mFlow[6];                          // +0x84  stride 0xc0
    char pad504[0x1c];                              // +0x504..+0x51f
    Hashtable mHash[7];                             // +0x520  stride 0x1c
    int m5e4;                                       // +0x5e4
    int m5e8;                                       // +0x5e8  last panel id applied
    char pad5ec[0x3c];                              // +0x5ec..+0x627
    GameEntry* mEntry;                              // +0x628

    void PickRandomVehicle();                       // 0x00df2d80
    void OnAssetBrowserSelection(Key* p);           // 0x00df21d0  (ret 4)
    void SelectNextState();                         // 0x00df2550
    void PickRandomCreature();                      // 0x00df2bb0
    void PickRandomAssets(char flag);               // 0x00df3ab0  (ret 4)
    void PickRandomByMode(unsigned id, int tag, Key* key); // 0x00df2a60  (ret 0xc)
    void SetLevel(int level);                       // 0x00df2ea0  (ret 4)
    void Init(int flowId);                          // 0x00df32d0  (ret 4)
    void SelectTheme(int theme);                    // 0x00defdd0
    void ShowSkin(unsigned skinId);                 // 0x00dec6d0
    void SetStateSummaryText(int a, unsigned b, const wchar_t* text); // 0x00defd10
    void ResetAssetButtons(int a, int b, int c);    // 0x00ded140
    int  FnEE890(Key* key);                         // 0x00dee890
    void FnEF20(int a, Hashtable* table, unsigned panelId); // 0x00deef20
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

// @ 0x00df2ea0
void StateMachine::SetLevel(int level)
{
    GameEntry* p = this->mEntry;
    if (p != 0) {
        p->mA8 = level;
        p->mA4 = level;
        if (p->m20 != p->m24) {
            *p->m20 = 0;
            p->m24 = p->m20;
        }
        p->m70.a = 0;
        p->m70.b = 0;
        p->m70.c = 0;
        p->m4c = p->m70;
        p->m64 = p->m4c;
        this->SelectTheme(0);
    }

    unsigned ids[5];
    ids[0] = 0x5a72f76;
    ids[1] = 0x6149c87;
    ids[2] = 0x5a72f77;
    ids[3] = 0x5a72f78;
    ids[4] = 0x5a72f79;
    for (int i = 0; i < 5; i++)
        this->mLayout.FindWindowByID(ids[i], 1)->Slot7C(1, 0);

    IWindow* w = this->mLayout.FindWindowByID(0x62f1f94, 1);
    if (w != 0)
        w->Slot7C(1, 0);

    cString summary;

    tNewGameFlow* flow = &this->mFlow[level];
    if (!HashHasKey(&flow->mMap20, 8) && !HashHasKey(&flow->mMap20, 3))
        this->PickRandomCreature();

    switch (level) {
    case 0: summary = cString(0x2b7a0311, 0x5b08702, 0); this->ShowSkin(0x5b218d1); break;
    case 1: summary = cString(0x2b7a0311, 0x5b08703, 0); this->ShowSkin(0x5b218c9); break;
    case 2: summary = cString(0x2b7a0311, 0x5b08704, 0); this->ShowSkin(0x5adf8e2); break;
    case 4: summary = cString(0x2b7a0311, 0x5b08705, 0); this->ShowSkin(0x5b8a143); break;
    case 5: summary = cString(0x2b7a0311, 0x5b08706, 0); this->ShowSkin(0x5b218d9); break;
    }

    this->SetStateSummaryText(1, 0x5b08739, summary.GetText());
    this->SelectNextState();

    this->mLayout.FindWindowByID(0x5af2b91, 1);

    for (unsigned i = 0; i < 5; i++) {
        IWindow* flagW = this->mLayout.FindWindowByID(kUIFlagIds[i], 1);
        if (flagW != 0)
            flagW->Slot7C(1, i < flow->m88);
        IWindow* btnW = this->mLayout.FindWindowByID(kUIPanelButtonIds[i], 1);
        if (btnW != 0)
            btnW->Slot7C(1, i < flow->m88);
    }

    unsigned* begin = flow->m60;
    unsigned count = (unsigned)(flow->m64 - flow->m60) >> 2;
    for (unsigned i = 0; i < count; i += 2) {
        unsigned* e = begin + i;
        IWindow* lw = this->mLayout.FindWindowByID(e[0], 1);
        cString text(0x2b7a0311, e[1], 0);
        if (lw != 0)
            lw->Slot80(text.GetText());
    }

    this->ResetAssetButtons(1, 1, 1);
}

// @ 0x00df32d0
void StateMachine::Init(int flowId)
{
    int mode = this->mEntry->mA4;
    if (mode == 0) {
        int want = (flowId == 0x6775e23 || flowId == 0x6775e20) ? 1 : 0;
        do {
            this->PickRandomCreature();
        } while (this->FnEE890(&this->mEntry->m4c) != want);
        this->SelectNextState();
        return;
    }

    bool herbivore = (this->m81 != 0) && (mode == 1);

    int sel = 0;
    Hashtable* table = 0;
    switch (flowId) {
    case 0x6775e1f:
    case 0x6775e22:
        sel = 1;
        table = herbivore ? &this->mHash[4] : &this->mHash[1];
        break;
    case 0x6775e20:
    case 0x6775e23:
        sel = 0;
        table = herbivore ? &this->mHash[5] : &this->mHash[2];
        break;
    case 0x6775e21:
        sel = 2;
        table = herbivore ? &this->mHash[6] : &this->mHash[3];
        break;
    }

    int row = (mode == 1) ? 1 : (mode == 2) ? 2 : 0;
    unsigned panelId = kGUI_PanelIDs->mPanelIds[sel + 3 * row];
    this->m5e8 = 0x54045ce;
    this->FnEF20(this->mEntry->mA8, table, panelId);
}