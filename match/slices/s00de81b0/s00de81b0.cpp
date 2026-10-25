// Slice s00de81b0: cSPUIGlobalUI::HandleMessage, the mode-request setter and the
// per-frame galaxy-entry update of cGalaxyGameEntryImpl.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The three routines share one object layout.  Offsets are kept in the struct
// below and every touched field has a name.
#include "types.h"

// ---------------------------------------------------------------------------
// Callees (all original relocations).
// ---------------------------------------------------------------------------

// Global singleton accessors: plain `mov eax, [global]; ret`.
extern "C" void* __cdecl FUN_0067cac0();   // 0x67cac0  SP::UIHints
extern "C" void* __cdecl FUN_0067cad0();   // 0x67cad0  bounding-box manager
extern "C" void* __cdecl FUN_0067cb10();   // 0x67cb10  SP::MovieSystem
extern "C" void* __cdecl FUN_0067dcc0();   // 0x67dcc0  SP::MessageServer
extern "C" void* __cdecl FUN_0067dd10();   // 0x67dd10  SP::App
extern "C" void* __cdecl FUN_0067dd50();   // 0x67dd50
extern "C" void* __cdecl FUN_0067ddd0();   // 0x67ddd0  SP::EffectsManager
extern "C" void* __cdecl FUN_00b3d2a0();   // 0xb3d2a0  SP::StarManager
extern "C" void* __cdecl FUN_00b3d340();   // 0xb3d340  galaxy save/state object
extern "C" void* __cdecl FUN_00df5f40();   // 0xdf5f40  scene
extern "C" void* __cdecl FUN_00dd9190();   // 0xdd9190  CB object

// Free functions.
extern "C" int   __cdecl FUN_00401030();                          // 0x401030  ?GetSetting3@@YAHXZ
extern "C" void* __cdecl FUN_0042f530(void* a, void* b, void* c); // 0x42f530  copy/erase helper
extern "C" void  __cdecl FUN_00804ed0(void* a, void* b);          // 0x804ed0
extern "C" void  __cdecl FUN_00809db0(void* target, void* msg);   // 0x809db0  UI::CalloutMessageBox
extern "C" bool  __cdecl FUN_008d3200(int a, int b);              // 0x8d3200
extern "C" void* __cdecl FUN_00921580(void* node);                // 0x921580  RBTreeIncrement
extern "C" void  __cdecl FUN_00ddc8d0();                          // 0xddc8d0  final teardown

// __thiscall helpers.  `__fastcall` + throw-away edx models ecx=this, the
// remaining parameters on the stack (each callee pops its own arguments).
extern "C" void  __fastcall FUN_0067c3b0(void* self, int, int hint, char flag);      // 0x67c3b0  UIHints::Next
extern "C" void  __fastcall FUN_007c4010(void* self, int, uint32_t* out);            // 0x7c4010  cViewer::GetRect
extern "C" void  __fastcall FUN_0080dc50(void* self, int, void* arg);                // 0x80dc50
extern "C" void* __fastcall FUN_008105b0(void* self, int, uint32_t id, int flag);    // 0x8105b0  cSPUILayout::FindWindowByID
extern "C" void  __fastcall FUN_00811ad0(void* self, int, int flag);                 // 0x811ad0  cSPUILayout::Shutdown
extern "C" void  __fastcall FUN_00b96600(void* self, int, void* pos, const void* key); // 0xb96600  SPVector::DoInsertKey4
extern "C" void  __fastcall FUN_00bb7620(void* self, int);                          // 0xbb7620
extern "C" void  __fastcall FUN_00dda3b0(void* self, int, char v);                  // 0xdda3b0  CB::m3b0
extern "C" void  __fastcall FUN_00ddc6d0(void* self, int, int ms);                  // 0xddc6d0
extern "C" float __fastcall FUN_00dde5c0(void* self, int);                          // 0xdde5c0
extern "C" void  __fastcall FUN_00de44f0(void* self, int, float a, float b, int c); // 0xde44f0
extern "C" void  __fastcall FUN_00de4910(void* self, int);                          // 0xde4910
extern "C" void  __fastcall FUN_00de5470(void* self, int, bool flag);               // 0xde5470  ShowGalaxy
extern "C" void  __fastcall FUN_00de6650(void* self, int, float a, float b);        // 0xde6650
extern "C" void* __fastcall FUN_00de7630(void* self, int, int* key);                // 0xde7630  IntMap::Slot
extern "C" void  __fastcall FUN_00df6db0(void* self, int, int state);               // 0xdf6db0  cGameUIData::SetUIState
extern "C" void  __fastcall FUN_00df9510(void* self, int);                          // 0xdf9510
extern "C" void* __fastcall FUN_00e012b0(void* self, int, uint32_t id);             // 0xe012b0  cSPUIGlobalUI::FindWindowByID

// ---------------------------------------------------------------------------
// Globals touched directly.
// ---------------------------------------------------------------------------
extern void*    kGUI_PanelIDs;    // 0x16a1344
extern uint8_t  g_CBEnabled;      // 0x16a1348
extern uint8_t  g_CBIndex;        // 0x16a0fa8
extern float    g_fAbsThreshold;  // 0x16a0f68
extern uint8_t  g_bSomeFlag;      // 0x16a0e78

static const float kfMsScale = 1000.0f;   // 0x13ec5b4
static const float kfHalf    = 0.5f;      // 0x1471064

// ---------------------------------------------------------------------------
// Virtual dispatch helpers.
// ---------------------------------------------------------------------------
typedef void (__thiscall* VFn0)(void*);
typedef void (__thiscall* VFn1)(void*, int);
typedef char (__thiscall* VFnC)(void*);
typedef void* (__thiscall* VFnP)(void*);

static inline void** VT(void* o) { return *(void***)o; }

static inline void  VCall0(void* o, int slot) { ((VFn0)VT(o)[slot])(o); }
static inline void  VCall1(void* o, int slot, int a) { ((VFn1)VT(o)[slot])(o, a); }
static inline char  VCallC(void* o, int slot) { return ((VFnC)VT(o)[slot])(o); }
static inline void* VCallP(void* o, int slot) { return ((VFnP)VT(o)[slot])(o); }

// Release a refcounted slot: clear it first, then drop the reference.
static inline void ReleaseSlot(void** slot)
{
    void* p = *slot;
    if (p) {
        *slot = 0;
        VCall0(p, 1);                 // vt +0x04
    }
}

// Slots released through the "is-still-in-use?" test: ask vt +0x10, and if it
// says busy drop the extra reference (vt +0x0c(1)); then release the slot.
static inline void ReleaseSlotChecked(void** slot)
{
    void* p = *slot;
    if (p && VCallC(p, 4))            // vt +0x10
        VCall1(p, 3, 1);              // vt +0x0c(1)
    p = *slot;
    if (p) {
        *slot = 0;
        VCall0(p, 1);                 // vt +0x04
    }
}

// ---------------------------------------------------------------------------
// Object layout shared by the three routines.
// ---------------------------------------------------------------------------
struct GalaxyEntry
{
    void**    vtable;             // 0x000
    uint8_t   pad004[4];          // 0x004
    void*     mpMessageTarget;    // 0x008  opaque handle broadcast to
    void*     mpCalloutTarget;    // 0x00c  opaque handle used by CalloutMessageBox
    uint8_t   pad010[0x28];       // 0x010..0x037
    void*     mpModeTarget;       // 0x038  refcounted current mode/effects world
    uint8_t   pad03c[0x8c];       // 0x03c..0x0c7
    uint8_t   mbC8;               // 0x0c8
    uint8_t   mbC9;               // 0x0c9
    uint8_t   pad0ca[2];          // 0x0ca..0x0cb
    void*     mpBoundingBox;      // 0x0cc
    uint8_t   pad0d0[0x2c];       // 0x0d0..0x0fb
    void*     mpUIData;           // 0x0fc  (UI data object; +0xb8 holds the state owner)
    uint8_t   mb100;              // 0x100
    uint8_t   pad101[2];          // 0x101..0x102
    uint8_t   mb103;              // 0x103  "refresh icons" request
    uint8_t   pad104[4];          // 0x104..0x107
    int32_t   mn108;              // 0x108  current mode
    int32_t   mn10c;              // 0x10c  requested mode
    uint32_t* mpVecBegin;         // 0x110  mode history vector
    uint32_t* mpVecEnd;           // 0x114
    uint32_t* mpVecCap;           // 0x118
    uint8_t   pad11c[8];          // 0x11c..0x123
    void*     mpMapRoot;          // 0x124  int -> object map (root)
    void*     mpMapSentinel;      // 0x128  map sentinel / head link
    void*     mpMapFirst;         // 0x12c  first map node
    void*     mpMapLast;          // 0x130
    uint8_t   pad134[0x0c];       // 0x134..0x13f
    uint8_t   mb140;              // 0x140
    uint8_t   pad141[3];          // 0x141..0x143
    uint8_t   mLayout[0x18];      // 0x144  embedded cSPUILayout
    void*     mpEffectsWorld;     // 0x15c
    void*     mp160;              // 0x160
    void*     mp164;              // 0x164
    void*     mp168;              // 0x168
    void*     mp16c;              // 0x16c
    void*     mp170;              // 0x170
    uint8_t   pad174[0x10];       // 0x174..0x183
    void*     mp184;              // 0x184  window host
    uint8_t   pad188[0x10];       // 0x188..0x197
    void*     mp198;              // 0x198
    void*     mp19c;              // 0x19c
    void*     mp1a0;              // 0x1a0
    void*     mp1a4;              // 0x1a4
    void*     mp1a8;              // 0x1a8
    uint8_t   pad1ac[4];          // 0x1ac..0x1af
    void*     mp1b0;              // 0x1b0
    uint8_t   pad1b4[0x24];       // 0x1b4..0x1d7
    void**    mpEffectVecBegin;   // 0x1d8  AutoRefCount<cIVisualEffect> vector
    void**    mpEffectVecEnd;     // 0x1dc
    uint8_t   pad1e0[0x0c];       // 0x1e0..0x1eb
    int32_t   mn1ec;              // 0x1ec  number of selectable modes
    uint8_t   pad1f0[6];          // 0x1f0..0x1f5
    uint8_t   mb1f6;              // 0x1f6  "drop star manager overlay" request
};

// ---------------------------------------------------------------------------
// @ 0x00de81b0  cSPUIGlobalUI::HandleMessage
//
// Tear the current session down: clear the hint queue, release every handler
// map entry, shut the layout, drop all refcounted subsystems, flush the effects
// world, then broadcast the mode-change messages.
// ---------------------------------------------------------------------------
void __fastcall FUN_00de81b0(GalaxyEntry* self, int /*edx*/)
{
    uint8_t* base = (uint8_t*)self;

    self->mbC8 = 0;

    {
        void* hints = FUN_0067cac0();
        FUN_0067c3b0(hints, 0, 0x2e25815e, 0);   // UIHints::Next(0x2e25815e, 0)
    }

    // Release every handler stored in the map at +0x124.
    for (void* node = self->mpMapFirst; node != &self->mpMapSentinel; node = FUN_00921580(node)) {
        void* handler = *(void**)((char*)node + 0x14);
        VCall0(handler, 0xf);                    // vt +0x3c
    }

    {
        void* win = FUN_008105b0(base + 0x144, 0, 0x615a5ff, 1);
        if (win)
            VCall1(win, 0x1f, 1);                // vt +0x7c(1, 0)
        FUN_00811ad0(base + 0x144, 0, 1);
    }

    if (self->mn108 == 3) {
        self->mn108 = 5;
        self->mn10c = 5;
    }

    self->mb100 = 0;

    // Release the window host (+0x184) and the optional host at +0x1b0.
    {
        void* p = self->mp184;
        VCall0(p, 3);                            // vt +0x0c
        p = self->mp184;
        if (p)
            VCall1(p, 0, 1);                     // vt +0x00(1)
        self->mb103 = 1;
        self->mp184 = 0;
    }
    {
        void* p = self->mp1b0;
        if (p) {
            VCall1(p, 3, 0);                     // vt +0x0c(0)
            p = self->mp1b0;
            if (p) {
                self->mp1b0 = 0;
                VCall0(p, 1);                    // vt +0x04
            }
        }
    }

    // Scene / effects / movie subsystems.
    {
        void* scene = FUN_00df5f40();
        VCall1(scene, 0x17, 0);                  // vt +0x5c(0)
    }
    {
        void* obj = FUN_0067dd50();
        VCall1(obj, 0x14, 0xd);                  // vt +0x50(0xd)
    }
    {
        void* fx = FUN_0067ddd0();
        void* world = self->mpEffectsWorld;
        void* arg = VCallP(fx, 7);               // vt +0x1c
        VCall1(world, 7, (int)arg);              // vt +0x1c(world's world)
    }

    ReleaseSlot((void**)&self->mp160);
    ReleaseSlot((void**)&self->mp1a0);
    ReleaseSlot((void**)&self->mp164);
    ReleaseSlot((void**)&self->mp168);
    ReleaseSlot((void**)&self->mp16c);
    ReleaseSlot((void**)&self->mp170);

    ReleaseSlotChecked((void**)&self->mp1a4);
    ReleaseSlotChecked((void**)&self->mp1a8);
    ReleaseSlotChecked((void**)&self->mp19c);

    if (self->mn108 != 4) {
        void* ui = self->mpUIData;
        if (ui && *(void**)((char*)ui + 0xb8))
            FUN_00df6db0(*(void**)((char*)ui + 0xb8), 0, 1);   // SetUIState(1)

        // Two-phase release of the effects vector, then empty it.
        void** first = self->mpEffectVecBegin;
        void** last = self->mpEffectVecEnd;
        for (void** it = first; it != last; ++it) {
            if (*it)
                VCall1(*it, 3, 1);               // vt +0x0c(1)
        }
        void** newEnd = (void**)FUN_0042f530(last, last, first);
        for (void** it = newEnd; it < self->mpEffectVecEnd; ++it) {
            if (*it)
                VCall0(*it, 1);                  // vt +0x04
        }
        self->mpEffectVecEnd = newEnd;
    }

    {
        uint8_t* panels = (uint8_t*)kGUI_PanelIDs;
        if (panels[0x104] != 0 || *(int32_t*)(panels + 0x108) != 4) {
            void* scene = FUN_00df5f40();
            VCall1(scene, 0x18, 0);              // vt +0x60(0, 0)
            scene = FUN_00df5f40();
            VCall1(scene, 0x17, 0);              // vt +0x5c(0)
            scene = FUN_00df5f40();
            FUN_00df9510(scene, 0);
        }
    }

    self->mb140 = 0;

    // Broadcast the mode-change messages.
    {
        static const uint32_t kModeMsgs[] = {
            0x4360e14, 0x56bbd7f, 0x44db12e, 0x5bd6378, 0x5dd52c7, 0x6203fdc,
            0x4519b5f, 0x625d27d, 0x67c75bd6, 0x634297ad, 0x275a9c8c, 0xeda117de,
            0x8085c4c,
        };
        for (int i = 0; i < 13; ++i) {
            void* server = FUN_0067dcc0();
            ((void (__thiscall*)(void*, void*, uint32_t, int))VT(server)[0xb])(
                server, base + 8, kModeMsgs[i], 0xffffd8f1);
        }
    }

    {
        void* fx = FUN_0067ddd0();
        VCall1(fx, 0x26, 0);                     // vt +0x98(10, 0)
    }
    {
        void* world = self->mpEffectsWorld;
        VCall0(world, 0xd);                      // vt +0x34
    }
    {
        void* fx = FUN_0067ddd0();
        VCall1(fx, 0x14, 0x2dda976);             // vt +0x50(0x2dda976)
    }

    ReleaseSlot((void**)&self->mpEffectsWorld);

    self->mbC9 = 0;

    {
        void* movie = FUN_0067cb10();
        if (movie)
            VCall1(movie, 0x10, 1);              // vt +0x40(1)
    }

    FUN_0080dc50(FUN_0067cad0(), 0, self->mpBoundingBox);

    FUN_00ddc8d0();
}

// ---------------------------------------------------------------------------
// @ 0x00de86d0  FUN_00de86d0(value, flag)
//
// Record a requested mode.  When `flag` is set the current mode is normalised
// and pushed onto the mode history before the request is stored.
// ---------------------------------------------------------------------------
void __fastcall FUN_00de86d0(GalaxyEntry* self, int /*edx*/, int value, char flag)
{
    if (!flag) {
        self->mn10c = value;
        return;
    }

    int32_t& state = self->mn108;
    if (state == 1 || state == 0 || state == 8 || state == 9)
        state = 2;

    if (self->mpVecEnd < self->mpVecCap) {
        uint32_t* pos = self->mpVecEnd;
        self->mpVecEnd = pos + 1;
        if (pos)
            *pos = (uint32_t)state;
    } else {
        FUN_00b96600(&self->mpVecBegin, 0, self->mpVecEnd, &state);
    }

    self->mn10c = value;
}

// ---------------------------------------------------------------------------
// @ 0x00de8760  FUN_00de8760(dt, total)
//
// Per-frame galaxy-entry update: drive the CB overlay, tick the current mode
// target, refresh the icon layout when requested, run the mode machine, then
// swap in the effects world selected by the mode map.
// ---------------------------------------------------------------------------
void __fastcall FUN_00de8760(GalaxyEntry* self, int /*edx*/, float dt, float total)
{
    if (g_CBEnabled != 0) {
        FUN_00dda3b0(FUN_00dd9190(), 0, 0);
        FUN_00dda3b0(FUN_00dd9190(), 0, 1);
        g_CBEnabled = 0;
    }
    FUN_00dda3b0(FUN_00dd9190(), 0, (char)g_CBIndex);

    if (self->mb1f6) {
        FUN_00bb7620(FUN_00b3d2a0(), 0);
        self->mb1f6 = 0;
    }

    if (self->mpModeTarget)
        ((void (__thiscall*)(void*, float))VT(self->mpModeTarget)[5])(self->mpModeTarget, dt);

    {
        int ms = (int)(total * kfMsScale);
        FUN_00ddc6d0(FUN_00dd9190(), 0, ms);
    }

    if (self->mb103) {
        self->mb103 = 0;

        uint32_t rect[4] = { 0, 0, 0, 0 };
        void* app = FUN_0067dd10();
        void* viewer = VCallP(app, 0x16);                    // vt +0x58
        FUN_007c4010(viewer, 0, rect);

        float cx = (float)((int)(rect[2] - rect[0]) / 2);
        float cy = (float)((int)(rect[3] - rect[1]) / 2);

        void* win = FUN_00e012b0(&self->mp184, 0, 0x3685038);
        if (win) {
            float* r = (float*)VCallP(win, 0xe);             // vt +0x38
            ((void (__thiscall*)(void*, float, float))VT(win)[0x19])(
                win,
                cx - (r[2] - r[0]) * kfHalf,
                cy - (r[3] - r[1]) * kfHalf);
        }
    }

    {
        int setting = FUN_00401030();
        void* world = self->mpEffectsWorld;
        int on = *(char*)(setting + 0x1c) != 0;
        VCall1(world, 3, on);                                // vt +0x0c(enabled)
    }

    FUN_00de6650(self, 0, dt, total);

    {
        float v = FUN_00dde5c0(self->mp198, 0);
        float av = v < 0 ? -v : v;
        void* p;
        if (FUN_008d3200(0x11, 0x3ff) && FUN_008d3200(0x10, 0x3ff)) {
            p = self->mp170;
            if (p && g_fAbsThreshold < av && !VCallC(p, 4))  // vt +0x10
                VCall1(p, 2, 0);                            // vt +0x08(0)
        } else {
            p = self->mp16c;
            if (p && g_fAbsThreshold < av && !VCallC(p, 4))
                VCall1(p, 2, 0);
        }
    }

    // Mode machine.
    if (self->mn108 != self->mn10c) {
        if (self->mn108 == 0) {
            if (self->mn1ec == 6) {
                void* galaxy = FUN_00b3d340();
                if (*(uint8_t*)((char*)galaxy + 0x47) != 0 || g_bSomeFlag != 0) {
                    int msg[3] = { 0x7fa5e584, 0xb1b104, 0xf5f6fde8 };
                    FUN_00809db0(&self->mpCalloutTarget, msg);
                    self->mn10c = 0;
                    self->mn108 = 0;
                    ((uint8_t*)FUN_00b3d340())[0x47] = 0;
                    goto mode_target;
                }
                self->mn108 = self->mn10c;
                FUN_00de5470(self, 0, true);
            }
        } else if (self->mn108 == 1) {
            self->mn108 = self->mn10c;
            FUN_00de5470(self, 0, true);
        } else {
            self->mn108 = self->mn10c;
        }
    }

mode_target:
    {
        int* sel = (int*)FUN_00de7630(&self->mpMapRoot, 0, &self->mn108);
        int selected = *sel;
        if ((uint32_t)(self->mn1ec - 1) <= 4) {
            int key = 1;
            sel = (int*)FUN_00de7630(&self->mpMapRoot, 0, &key);
            selected = *sel;
        }

        int* old = (int*)self->mpModeTarget;
        if (selected != (int)old) {
            if (old)
                VCallC(old, 4);                             // vt +0x10
            self->mpModeTarget = (void*)selected;
            if (selected)
                VCall0((void*)selected, 3);                 // vt +0x0c
            FUN_00804ed0(&dt, &total);
            FUN_00de44f0(self, 0, dt, total, 0);
            FUN_00de4910(self, 0);
        }
    }
}
