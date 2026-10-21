// Slice s00f114a0 (batch gold3, slice 130) -- scenario-mode HUD / creature-mode input strategy.
//
//   0x00F114A0  scenario minimap icon rebuild (missions + objectives)
//   0x00F118E0  scenario timer HUD update (mission timer text + progress bar)
//   0x00F11AC0  creature input strategy per-frame hook
//   0x00F11B10  creature input strategy message hook
//   0x00F11B40  property-manager write
//   0x00F11B60  cCreatureModeInputStrategy construction
//   0x00F11C30  cCreatureModeInputStrategy destruction
//   0x00F11CA0  cCreatureModeInputStrategy::Init
//   0x00F11F90  cCreatureModeInputStrategy::Shutdown
//   0x00F12090  QueryInterface-style cast
//   0x00F120C0  key/value forwarder
//   0x00F12140  cScenarioUnlockItemUI::Init
//   0x00F12270  cScenarioUnlockItemUI::Shutdown
//   0x00F122E0  cScenarioUnlockItemUI factory
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// cHudTargetController, cScenarioPlayProgressBar, cScenarioUnlockItemUI and every FUN_ name are
// Claude-coined placeholders derived from the addresses (no symbols exist for this object).
#include "types.h"

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vec2 { float x, y; };

// ===========================================================================
// Shared interfaces / value types
// ===========================================================================
struct CObj {
    PV
    virtual int AddRef();       // +0x04
    virtual int Release();      // +0x08
};

// UTFWin::IWindow minimal vtable (only the slots this slice calls).
struct IWin {
    PV8 PV4 PV2                                  // 0x00 .. 0x34
    virtual float* GetRect();                    // +0x38
    PV16                                         // 0x3c .. 0x78
    virtual void SetVisible(int group, bool on); // +0x7c
    virtual void SetText(const wchar_t* text);   // +0x80
    PV8 PV4 PV2 PV                               // 0x84 .. 0xbc
    virtual void* FUN_c0(Vec2 size, void* out);  // +0xc0
};

struct UIGlobal {
    IWin* FindWindowByID(u32 id);                // 0x00e012b0 (ret 4)
};

// eastl::string16 as laid out by VS2008 (begin/end/capacity pointers).
struct string16 {
    wchar_t* begin;
    wchar_t* end;
    wchar_t* capacity;
    ~string16()
    {
        if ((((u32)capacity - (u32)begin) & 0xfffffffeu) > 2 && begin)
            ::operator delete(begin);
    }
};

struct cIconInfo {                 // 0x24 bytes (cSPUIMinimapWin::AddIcon descriptor)
    u32    mType;                  // +0x00
    float  mX, mY, mZ;             // +0x04
    u32    mFlags;                 // +0x10
    CObj*  mpObject;               // +0x14
    float  mTimeout;               // +0x18
    u32    mAnimState;             // +0x1c
    u32    mImageID;               // +0x20
};

class cSPUIMinimapWin { public:
    void RemoveAllIcons();                                        // 0x00e0fb50
    void FUN_00e0ad00(int);                                       // 0x00e0ad00
    bool AddIcon(u32 id, const cIconInfo* info, int parent, bool flag); // 0x00e10580
    void FUN_00e0e1a0();                                          // 0x00e0e1a0
};

struct IconRef { u32 a, b; };

// eastl::rbtree/map header used for the icon-id -> {object, index} map at owner+0x2ec.
struct IconMap {
    u32    f0;         // +0x00
    void*  f4;         // +0x04
    void*  f8;         // +0x08
    void*  fC;         // +0x0c (tree root)
    u8     f10;        // +0x10
    u32    f14;        // +0x14
    void   FUN_009a9600(void* node);            // 0x009a9600 (nuke subtree)
    IconRef* FUN_00f0fe60(u32* key);            // 0x00f0fe60 (map::operator[])
};

struct MissionEntry {              // 0x238-byte element of the player's mission vector
    u32 flags;                     // +0x00 (bit30: end, bit31: continue)
    u32 key;                       // +0x04
    char pad[0x238 - 8];
};

struct MissionDef {                // 0x62-byte element of the mission-definition vector
    u32  f0;                       // +0x00 (icon table index)
    u32  id;                       // +0x04
    u32  id2;                      // +0x08
    char pad0c[4];
    u8   active;                   // +0x10
    char pad11[0x62 - 0x11];
};

struct DefList {
    char pad[0x84];
    MissionDef* begin;             // +0x84
    MissionDef* end;               // +0x88
};

struct PlayerEntry {
    char pad0[0x150];
    float pos[3];                  // +0x150
    char pad1[0x2c10 - 0x15c];
    MissionEntry* mBegin;          // +0x2c10
    MissionEntry* mEnd;            // +0x2c14
    char pad2[0x2c24 - 0x2c18];
    u32  mSize;                    // +0x2c24
};

struct Mgr {
    char pad0[0x10];
    PlayerEntry* mpPlayer;         // +0x10
    void* FUN_00f3d780(int* key);  // 0x00f3d780
    void* FUN_00f3e900(void* obj); // 0x00f3e900
    DefList* FUN_00f3be60(u32 idx);// 0x00f3be60
};

struct PlayBar {                   // scenario progress/timer bar singleton (root+0x78)
    char pad0[0xb8];
    u32  mIndex;                   // +0xb8
    u32  mTimeMs;                  // +0xbc
    bool IsActive();               // 0x00f19b80
    void GetTimerText(string16* out); // 0x00f1dc50
    float GetProgressF();          // 0x00f19160
};

struct Root {
    char pad0[0x74];
    Mgr*     mpMgr;                // +0x74
    PlayBar* mpBar;                // +0x78
    char pad7c[0xd0 - 0x7c];
    int      mD0;                  // +0xd0
};

// --- camera/combat HUD controller (fields shared with slice s00f10670) ---------
struct TimerBar {
    char pad[0x7c];
    void SetValue(float v);        // 0x00d2beb0
};

struct LevelProgress {
    void FUN_00f17f70(u32 arg);    // 0x00f17f70
};

struct cScenarioTimerHud {
    char pad00[0x5c];
    UIGlobal*  mpUI;               // +0x5c
    char pad60[0xb0 - 0x60];
    TimerBar   mTimerBar;          // +0xb0
    LevelProgress* mpProgress;     // +0x12c

    void FUN_00f118e0(u32 arg);
};

// --- creature-mode input strategy ---------------------------------------------
struct InputManager {
    PV PV PV PV
    virtual void SetTriggerConfig(const char* name, int a, int b); // +0x10
    PV PV PV
    virtual void FUN_slot20(void* out, int a, int b);              // +0x20
    PV PV PV PV PV PV
    virtual void SetUIMachine(const char* name);                   // +0x3c
};

struct DevMgr {
    PV8 PV4 PV2
    virtual void AddSub(void* sub, int on);   // +0x38
    PV
    virtual void RemoveSub(void* sub);        // +0x40
};

struct Loc {
    PV PV PV PV PV
    virtual void* FUN_slot14();               // +0x14
};

struct CursorTable {
    u32 AddCursor(void* id, const wchar_t* name, int a, int b, int c); // 0x00802050
};

struct MsgServer {
    PV8 PV
    virtual void AddHandler(void* target, u32 msgId); // +0x24
};

struct EList {                       // empty eastl list header
    void* next;                      // +0x00
    void* prev;                      // +0x04
    u32   n;                         // +0x08
    u8    b;                         // +0x0c
    u8    pad[3];
    u32   f10;                       // +0x10
};

struct E4 { void FUN_00e4b990(void* arg); };   // 0x00e4b990
struct B1 { void FUN_00b1b830(void* arg); };   // 0x00b1b830

struct cCreatureModeInputStrategy {
    void* volatile mpVt;              // +0x00
    char  pad04[0x3c - 4];
    void* volatile mpVt3c;            // +0x3c
    char  pad40[4];
    void* volatile mpVt44;            // +0x44
    void* volatile mpVt48;            // +0x48
    void* volatile mpVt4c;            // +0x4c
    char  pad50[4];
    u8    mActive;                    // +0x54
    char  pad55[0x108 - 0x55];
    void* volatile m108;              // +0x108 (messaging server)
    u32   volatile m10c;              // +0x10c (handler object)
    void* volatile m110;              // +0x110 (message table)
    u32   volatile m114;              // +0x114 (message count)
    u32   volatile m118;              // +0x118

    void*  FUN_00f11b60();            // ctor-equivalent (returns this)
    void   FUN_00f11c30();            // dtor-equivalent
    void   FUN_00f11ca0();
    void   FUN_00f11f90();
    void   FUN_00f11ac0(int arg);
    bool   FUN_00f11b10(u32 msg, u32 arg);
    bool   HandleMessage(u32 msg, u32 arg);       // 0x00d35190
    void   FUN_00d32fb0(int arg);                 // 0x00d32fb0
    void   FUN_00d342d0();                        // 0x00d342d0
    void   SetInputPriorityStrategy(int s);       // 0x00d33ec0
};

// --- cSPPaletteItemUI / cScenarioUnlockItemUI --------------------------------
struct Key { u32 a, b, c; };

class cSPUILayout : public CObj { public:
    void* ctor();                                              // 0x00810000
    bool Init(const Key& key, bool b, u32 id);                 // 0x008120d0
    bool SetParentWin(IWin* parent, bool b, u32 id);           // 0x008121b0
    IWin* FindWindowByID(u32 id, bool recursive);              // 0x008105b0
    char pad[0x18 - 0x0c];
};

struct cSPPaletteItem : CObj {
    char pad[0x54 - 0x0c];
};

struct cSPPaletteItemUI {
    char pad[0x20];
    void Init(void* a, void* b, void* c, void* d);   // 0x005c6ca0
    void Shutdown();                                 // 0x005c6d20
    cSPPaletteItemUI();                              // 0x005c6bf0
};

template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};

struct cScenarioUnlockItemUI : cSPPaletteItemUI {
    AutoRefCount<cSPUILayout>     mpLayout;    // +0x20
    AutoRefCount<cSPPaletteItem>  mpItem;      // +0x24
    u32 m28, m2c, m30;                         // +0x28

    void Init(void* a, void* b, void* c, cSPPaletteItem* d);   // 0x00f12140
    void Shutdown();                                            // 0x00f12270
};

// ===========================================================================
// Globals (named after their address so the equivalence resolver can map them)
// ===========================================================================
extern Root* g_16c7aa4;                       // 0x016c7aa4 simulator/service root
extern float g_13eb1bc;                       // 0x013eb1bc -1.0f
extern float g_13f4fd0;                       // 0x013f4fd0 4294967296.0f
extern float g_13f9428;                       // 0x013f9428 0.001f
extern float g_1473c70;                       // 0x01473c70 10.0f
extern float g_148bdf0;                       // 0x0148bdf0 68.0f
extern float g_13eeda0;                       // 0x013eeda0 8.0f
extern u32   g_148bce8[];                     // 0x0148bce8 mission-icon resource table
extern u32   g_148be90[];                     // 0x0148be90 26 registered message ids
extern wchar_t g_1667bac[];                   // 0x01667bac empty eastl::string16
extern wchar_t g_1667bae[];                   // 0x01667bae (one past the empty string)
extern const char g_148bfc8[];                // 0x0148bfc8 "TriggerConfigScenarioMode"
extern const char g_1477758[];                // 0x01477758 "TriggerConfigWASD_fr-fr"
extern const char g_1477770[];                // 0x01477770 "TriggerConfigWASD"
extern const char g_148bfb0[];                // 0x0148bfb0 "UIMachineScenarioMode"
extern const wchar_t g_1403c98[];             // 0x01403c98 L"fr-fr"
extern const wchar_t g_147a7d4[];             // "cursor-target"
extern const wchar_t g_1476df0[];             // "cursor-mate"
extern const wchar_t g_1476ef8[];             // "cursor-heal"
extern const wchar_t g_1476eac[];             // "cursor-eat-fruit"
extern const wchar_t g_1476ed0[];             // "cursor-eat-carcass"
extern const wchar_t g_1476e24[];             // "cursor_atk"
extern const wchar_t g_147a7b8[];             // "cursor-evolve"
extern const wchar_t g_147a798[];             // "cursor-validate"
extern const wchar_t g_1476d30[];             // "cursor_social"
extern const wchar_t g_147a77c[];             // "cursor_friend"
extern const wchar_t g_147a75c[];             // "cursor_socialNo"
extern const wchar_t g_147a734[];             // "cursor-crg-addposse"
extern const wchar_t g_13fecec[];             // "cursor-crg-pickup"
extern const wchar_t g_147a70c[];             // "cursor-crg-putdown"
extern const wchar_t g_147a6f0[];             // "cur_ClaimNest"
extern const wchar_t g_147a6d0[];             // "cursor-crg-give"
extern const wchar_t g_13fecc8[];             // "cursor-crg-throw"
extern const wchar_t g_147a6a0[];             // "cursor-target-creature"
extern const wchar_t g_147a67c[];             // "cursor_skeleton2"
extern const wchar_t g_148bf94[];             // "cursor-talkto"
extern const wchar_t g_148bf70[];             // "cursor-talktoGoal"
extern const wchar_t g_148bf34[];             // "cursor-target-creature-friend"
extern const wchar_t g_148bef8[];             // "cursor-target-creature-enemy"
extern Key g_15ad898;                         // 0x015ad898 layout key
extern Key g_15ad8c0;                         // 0x015ad8c0 path key

// ===========================================================================
// External helpers
// ===========================================================================
struct GameTime {
    char pad[0x48];
    u8 f48;
};

extern "C" GameTime* FUN_00b3d380();
extern "C" InputManager* FUN_00b3d250();
extern "C" DevMgr* FUN_00b3d230();
extern "C" Loc* FUN_0067de40();
extern "C" CursorTable* FUN_0067cab0();
extern "C" MsgServer* FUN_00883860();
extern "C" void* FUN_0067de30();
extern "C" void FUN_00efcae0();                       // ScenarioTutorials_CloseWindow
extern "C" void FUN_00f0f330(float);                  // scenario HUD helper
extern "C" void FUN_00b6dbd0(float);                  // timer tick helper
extern "C" void __fastcall FUN_00f10bd0(void*, u32, u32);  // cHudTargetController::Update
extern "C" void __fastcall FUN_00d37970(void*);       // base ctor
extern "C" void __fastcall FUN_00d37b60(void*);       // base dtor
extern "C" void FUN_00d49190();
extern "C" bool FUN_006ab760(void* obj, const wchar_t* tag);
extern "C" int  FUN_00eece20(int* key);               // resource key -> icon hash
extern "C" void FUN_00571db0(void*, void*, void*, u32, u32); // EA::Messaging::RemoveHandler
extern "C" void __cdecl SetWindowAreaToParent(IWin* win);    // 0x00806bf0
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int, int, int, int); // 0x00f473a0
void operator delete(void*);

// ===========================================================================
// 0x00F114A0 -- rebuild the scenario minimap icons
// ===========================================================================
struct MinimapOwner {
    char pad0[0x2e0];
    cSPUIMinimapWin* mpMinimap;   // +0x2e0
    char pad2e4[8];
    IconMap mIcons;               // +0x2ec

    void FUN_00f114a0();
};

// @ 0x00f114a0
void MinimapOwner::FUN_00f114a0()
{
    if (!mpMinimap)
        return;

    mpMinimap->RemoveAllIcons();
    mpMinimap->FUN_00e0ad00(4);

    mIcons.FUN_009a9600(mIcons.fC);
    mIcons.fC = 0;
    mIcons.f10 = 0;
    mIcons.f14 = 0;
    mIcons.f4 = &mIcons.f4;
    mIcons.f8 = &mIcons.f4;

    Root* g = g_16c7aa4;
    PlayBar* bar = g->mpBar;
    Mgr* mgr = g->mpMgr;
    PlayerEntry* pl = mgr->mpPlayer;

    cIconInfo info;
    info.mType = 0;
    info.mX = 0.0f;
    info.mY = 0.0f;
    info.mZ = g_13eb1bc;
    info.mFlags = 0x28;
    info.mpObject = 0;
    info.mTimeout = 0.0f;
    info.mAnimState = 0;
    info.mImageID = 0;
    info.mX = pl->pos[0];
    info.mY = pl->pos[1];
    info.mZ = pl->pos[2];
    info.mImageID = 0x7f20c30;
    mpMinimap->AddIcon(0x79965de, &info, 0, 0);

    u32 iconId = 0x17e00000;
    MissionEntry* it = (pl->mSize < 0x3fffffff) ? pl->mBegin + pl->mSize : pl->mEnd;
    MissionEntry* end = pl->mEnd;
    if (it != end) {
        do {
            MissionEntry* cur = it;
            void* obj = mgr->FUN_00f3d780((int*)((char*)cur + 4));
            if (obj) {
                void* def = mgr->FUN_00f3e900(obj);
                if (def && *(u8*)(bar->mIndex * 0x4e0 + *(int*)((char*)def + 0x70))) {
                    void* q = (*(void* (__thiscall**)(void*, u32))((char*)*(void**)obj + 0xc))(obj, 0x1186577);
                    if (q) {
                        DefList* dl = mgr->FUN_00f3be60(bar->mIndex);
                        MissionDef* md = dl->begin;
                        MissionDef* mde = dl->end;
                        int count = 0;
                        while (md != mde) {
                            if (md->id == 0xfffffffe)
                                break;
                            if (!md->active)
                                break;
                            if (*(u32*)((char*)obj + 0x1c) == md->id ||
                                *(u32*)((char*)obj + 0x1c) == md->id2) {
                                cIconInfo i2;
                                i2.mType = 0;
                                i2.mX = 0.0f;
                                i2.mY = 0.0f;
                                i2.mZ = g_13eb1bc;
                                i2.mFlags = 0x80;
                                i2.mpObject = 0;
                                i2.mTimeout = 0.0f;
                                i2.mAnimState = 0;
                                i2.mImageID = g_148bce8[md->f0];
                                float* pp =
                                    (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)q + 0x2c))(q);
                                i2.mX = pp[0];
                                i2.mY = pp[1];
                                i2.mZ = pp[2];
                                mpMinimap->AddIcon(iconId, &i2, 0, 0);
                                IconRef* e = mIcons.FUN_00f0fe60(&iconId);
                                iconId += 100;
                                e->a = *(u32*)((char*)obj + 0x24);
                                e->b = count;
                                if (i2.mpObject)
                                    i2.mpObject->Release();
                            }
                            count++;
                            md = (MissionDef*)((char*)md + 0x62);
                        }

                        cIconInfo i3;
                        i3.mType = 0;
                        i3.mX = 0.0f;
                        i3.mY = 0.0f;
                        i3.mZ = g_13eb1bc;
                        i3.mFlags = 0x80000;
                        i3.mpObject = 0;
                        i3.mTimeout = 0.0f;
                        i3.mAnimState = 0;
                        i3.mImageID = 0;

                        int h = FUN_00eece20((int*)def);
                        bool build = false;
                        if (h == (int)0xe34e8a60) {
                            void* q2 = (*(void* (__thiscall**)(void*, u32))((char*)*(void**)obj + 0xc))(
                                obj, 0xd0036e08);
                            if (q2 && !((*(u32*)((char*)q2 + 0xb58) >> 9) & 1)) {
                                i3.mFlags = 0x40;
                                build = true;
                            }
                        } else if (h == 0x5b3d1d0d) {
                            i3.mFlags = 0x100;
                            build = true;
                        } else {
                            build = i3.mFlags != 0x80000;
                        }
                        if (build) {
                            float* pp =
                                (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)q + 0x2c))(q);
                            i3.mX = pp[0];
                            i3.mY = pp[1];
                            i3.mZ = pp[2];
                            mpMinimap->AddIcon(iconId, &i3, 0, 0);
                            IconRef* e = mIcons.FUN_00f0fe60(&iconId);
                            iconId += 100;
                            e->a = *(u32*)((char*)obj + 0x24);
                            e->b = 0xffffffff;
                        }
                        if (i3.mpObject)
                            i3.mpObject->Release();
                    }
                }
            }

            for (;;) {
                if ((it->flags >> 30) & 1)
                    break;
                it = (MissionEntry*)((char*)it + 0x238);
                if (!((it->flags >> 31) & 1))
                    break;
            }
        } while (it != end);
    }

    mpMinimap->FUN_00e0ad00(4);
    mpMinimap->FUN_00e0e1a0();
}

// ===========================================================================
// 0x00F118E0 -- scenario timer HUD update
// ===========================================================================
// @ 0x00f118e0
void cScenarioTimerHud::FUN_00f118e0(u32 arg)
{
    GameTime* gt = FUN_00b3d380();
    u32 mask = ~(u32)((gt->f48 & 1) != 0);
    FUN_00f10bd0(this, 0, arg & mask);

    float t = (float)arg * g_13f9428;
    FUN_00f0f330(t);
    FUN_00b6dbd0(t);

    IWin* w = mpUI->FindWindowByID(0x7e1aea8);
    bool active = g_16c7aa4->mpBar->IsActive();
    if (w)
        w->SetVisible(1, active);

    if (active) {
        string16 s;
        s.begin = g_1667bac;
        s.end = g_1667bac;
        s.capacity = g_1667bae;
        g_16c7aa4->mpBar->GetTimerText(&s);
        if (w)
            w->SetText(s.begin);

        float p = g_16c7aa4->mpBar->GetProgressF();
        bool b = g_1473c70 > p;
        if (w)
            w->SetVisible(2, b);

        float* r = w->GetRect();
        Vec2 v;
        v.x = 0.0f;
        v.y = r[3] - r[1];
        void* out;
        void* res = w->FUN_c0(v, &out);
        mTimerBar.SetValue(*(float*)((char*)res + 4));
    } else {
        mTimerBar.SetValue((g_16c7aa4->mD0 == 0) ? g_148bdf0 : g_13eeda0);
    }

    if (mpProgress)
        mpProgress->FUN_00f17f70(arg);
}

// ===========================================================================
// 0x00F11AC0 -- creature input strategy per-frame hook
// ===========================================================================
// @ 0x00f11ac0
void cCreatureModeInputStrategy::FUN_00f11ac0(int arg)
{
    if (FUN_00b3d250() && mActive)
        FUN_00d342d0();
    FUN_00d32fb0(arg);
}

// ===========================================================================
// 0x00F11B10 -- creature input strategy message hook
// ===========================================================================
// @ 0x00f11b10
bool cCreatureModeInputStrategy::FUN_00f11b10(u32 msg, u32 arg)
{
    bool r = HandleMessage(msg, arg);
    if (msg == 0x13cdf6fa)
        FUN_00d49190();
    return r;
}

// ===========================================================================
// 0x00F11B40 -- property-manager write
// ===========================================================================
// @ 0x00f11b40
void __stdcall FUN_00f11b40(u32 value)
{
    void* pm = FUN_0067de30();
    typedef void (__thiscall *SetFn)(void*, u32, u32, u32);
    SetFn fn = *(SetFn*)((char*)*(void**)pm + 0x2c);
    fn(pm, 0x2980610e, 0x408a0100, value);
}

// ===========================================================================
// 0x00F11B60 -- cCreatureModeInputStrategy construction
// ===========================================================================
// @ 0x00f11b60
void* cCreatureModeInputStrategy::FUN_00f11b60()
{
    FUN_00d37970(this);
    u32 z = (u32)((char*)this - (char*)this);
    mpVt = (void*)0x148be68;
    mpVt3c = (void*)0x148be50;
    mpVt44 = (void*)0x148be34;
    mpVt48 = (void*)0x148be24;
    mpVt4c = (void*)0x148be14;
    m108 = (void*)z;
    m10c = z;
    m110 = (void*)z;
    m114 = z;
    m118 = z;
    return this;
}

// ===========================================================================
// 0x00F11C30 -- cCreatureModeInputStrategy destruction
// ===========================================================================
// @ 0x00f11c30
void cCreatureModeInputStrategy::FUN_00f11c30()
{
    mpVt = (void*)0x148be68;
    mpVt3c = (void*)0x148be50;
    mpVt44 = (void*)0x148be34;
    mpVt48 = (void*)0x148be24;
    mpVt4c = (void*)0x148be14;

    void* server = m108;
    if (server) {
        FUN_00571db0(server, (void*)m10c, m110, m114, m118);
        m108 = 0;
    }
    FUN_00d37b60(this);
}

// ===========================================================================
// 0x00F11CA0 -- cCreatureModeInputStrategy::Init
// ===========================================================================
// @ 0x00f11ca0
void cCreatureModeInputStrategy::FUN_00f11ca0()
{
    InputManager* im = FUN_00b3d250();
    mActive = 1;
    void* sub = (void*)&mpVt3c;

    DevMgr* dm = FUN_00b3d230();
    dm->AddSub(sub, 1);

    im->SetTriggerConfig(g_148bfc8, 0, 1);

    const char* cfg = FUN_006ab760(FUN_0067de40()->FUN_slot14(), g_1403c98)
                          ? g_1477758 : g_1477770;
    im->SetTriggerConfig(cfg, 0, 0);
    im->SetUIMachine(g_148bfb0);

    CursorTable* ct = FUN_0067cab0();
    ct->AddCursor((void*)0x514ab7b0u, g_147a7d4, 1, 0, 0);
    ct->AddCursor((void*)0x314ab7b1u, g_1476df0, 1, 0, 0);
    ct->AddCursor((void*)0xf14ab7b3u, g_1476ef8, 1, 0, 0);
    ct->AddCursor((void*)0xb14ab7b6u, g_1476eac, 1, 0, 0);
    ct->AddCursor((void*)0x514ab7b7u, g_1476ed0, 1, 0, 0);
    ct->AddCursor((void*)0xb14ab7b9u, g_1476e24, 1, 0, 0);
    ct->AddCursor((void*)0x114ab7bau, g_147a7b8, 1, 0, 0);
    ct->AddCursor((void*)0x514abe0bu, g_147a798, 1, 0, 0);
    ct->AddCursor((void*)0x71664d85u, g_1476d30, 1, 0, 0);
    ct->AddCursor((void*)0x755c4eb5u, g_147a77c, 1, 0, 0);
    ct->AddCursor((void*)0xf4f6c345u, g_147a75c, 1, 0, 0);
    ct->AddCursor((void*)0x3b360d8u, g_147a734, 1, 0, 0);
    ct->AddCursor((void*)0x3b360dcu, g_13fecec, 1, 0, 0);
    ct->AddCursor((void*)0x3b360dfu, g_147a70c, 1, 0, 0);
    ct->AddCursor((void*)0x7542cdb5u, g_147a6f0, 1, 0, 0);
    ct->AddCursor((void*)0x3b360e2u, g_147a6d0, 1, 0, 0);
    ct->AddCursor((void*)0x3b360e4u, g_13fecc8, 1, 0, 0);
    ct->AddCursor((void*)0xf36a0c84u, g_147a6a0, 1, 0, 0);
    ct->AddCursor((void*)0x342d221fu, g_147a67c, 1, 0, 0);
    ct->AddCursor((void*)0x7a2a419u, g_148bf94, 1, 0, 0);
    ct->AddCursor((void*)0x8054deau, g_148bf70, 1, 0, 0);
    ct->AddCursor((void*)0x7e849beu, g_148bf34, 1, 0, 0);
    ct->AddCursor((void*)0x7e849c5u, g_148bef8, 1, 0, 0);

    MsgServer* srv = FUN_00883860();
    m108 = srv;
    m10c = (u32)((char*)this + 0x48);
    m110 = (void*)g_148be90;
    m114 = 0x1a;
    m118 = 0;
    if (srv && (char*)this + 0x48) {
        u32 off = 0;
        do {
            srv->AddHandler((char*)this + 0x48, *(u32*)((char*)g_148be90 + off));
            off += 4;
        } while (off < 0x68);
    }

    SetInputPriorityStrategy(0);
    (*(void (__thiscall**)(void*))((char*)*(void**)this + 8))(this);
}

// ===========================================================================
// 0x00F11F90 -- cCreatureModeInputStrategy::Shutdown
// ===========================================================================
// @ 0x00f11f90
void cCreatureModeInputStrategy::FUN_00f11f90()
{
    FUN_00efcae0();

    void* server = m108;
    if (server) {
        FUN_00571db0(server, (void*)m10c, m110, m114, m118);
        m108 = 0;
    }

    InputManager* im = FUN_00b3d250();
    EList a;
    EList b;
    void* out = 0;
    a.next = &a; a.prev = &a; a.n = 0; a.b = 0; a.f10 = 0;
    b.next = &b; b.prev = &b; b.n = 0; b.b = 0; b.f10 = 0;
    im->FUN_slot20(&out, 0, 0);
    ((E4*)&b)->FUN_00e4b990((void*)b.n);
    ((B1*)&a)->FUN_00b1b830((void*)a.n);

    void* sub = this ? (void*)((char*)this + 0x3c) : 0;
    FUN_00b3d230()->RemoveSub(sub);
    mActive = 0;
}

// ===========================================================================
// 0x00F12090 -- QueryInterface-style cast
// ===========================================================================
struct QI {
    u32 FUN_00f12090(u32 id);
};

// @ 0x00f12090
u32 QI::FUN_00f12090(u32 id)
{
    if (id != 0x2f009dd0)
        return 0;
    return ((char*)this - 0xc) ? (u32)this : 0;
}

// ===========================================================================
// 0x00F120C0 -- key/value forwarder
// ===========================================================================
struct KeySink {
    void FUN_00e0a4c0(u32 value, const void* key);   // 0x00e0a4c0
};

struct KeyForwarder {
    char pad[8];
    KeySink sink;                     // +0x08
    void FUN_00f120c0(u32 value);
};

// @ 0x00f120c0
void KeyForwarder::FUN_00f120c0(u32 value)
{
    sink.FUN_00e0a4c0(value, &g_15ad8c0);
}

// ===========================================================================
// 0x00F12140 -- cScenarioUnlockItemUI::Init
// ===========================================================================
// @ 0x00f12140
void cScenarioUnlockItemUI::Init(void* a, void* b, void* c, cSPPaletteItem* d)
{
    cSPPaletteItemUI::Init(a, b, c, d);

    mpItem = d;

    cSPUILayout* alloc = (cSPUILayout*)EAAllocate(0x18, "Simulator", 0, 0, 0, 0);
    cSPUILayout* layout = alloc ? (cSPUILayout*)alloc->ctor() : 0;
    mpLayout = layout;

    if (mpLayout.mp->Init(g_15ad898, 1, 0x5b598fa)) {
        mpLayout.mp->SetParentWin((IWin*)b, 1, 0x5b598fa);
        IWin* win = mpLayout.mp->FindWindowByID(0x7c4af80, 1);
        SetWindowAreaToParent(win);

        u32 ids[3];
        ids[0] = 0xa2e50993;
        ids[1] = 0x4d7d9be4;
        ids[2] = 0x0e03db96;
        for (int i = 0; i < 3; i++) {
            u32 id = ids[i];
            IWin* w = mpLayout.mp->FindWindowByID(id, 1);
            if (w)
                w->SetVisible(1, 0);
        }
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)this + 0xc))(this, a);
    }
}

// ===========================================================================
// 0x00F12270 -- cScenarioUnlockItemUI::Shutdown
// ===========================================================================
// @ 0x00f12270
void cScenarioUnlockItemUI::Shutdown()
{
    cSPPaletteItemUI::Shutdown();

    cSPUILayout* layout = mpLayout.mp;
    if (layout) {
        mpLayout.mp = 0;
        layout->Release();
    }
    cSPPaletteItem* item = mpItem.mp;
    if (item) {
        mpItem.mp = 0;
        item->Release();
    }
}

// ===========================================================================
// 0x00F122E0 -- cScenarioUnlockItemUI factory
// ===========================================================================
// @ 0x00f122e0
IWin* __stdcall FUN_00f122e0(u32, u32)
{
    cScenarioUnlockItemUI* p =
        (cScenarioUnlockItemUI*)EAAllocate(0x34, "cScenarioUnlockItemUI", 0, 0, 0, 0);
    if (!p)
        return 0;
    p->cSPPaletteItemUI::cSPPaletteItemUI();
    *(void**)p = (void*)0x148c034;
    *(void**)((char*)p + 0x10) = (void*)0x148c008;
    *(void**)((char*)p + 0xc) = (void*)0x148c018;
    p->mpLayout.mp = 0;
    p->mpItem.mp = 0;
    p->m28 = 0;
    p->m2c = 0;
    p->m30 = 0;
    return (IWin*)((char*)p + 0xc);
}

void* __cdecl operator new(unsigned int size, const char* name, int a, int b,
                           const char* file, int line);   // 0x00f473a0
