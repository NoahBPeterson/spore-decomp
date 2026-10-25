// Slice s00b68720: Spore UTFWin UI manager walk.  Names are Claude-coined from
// usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int uint;

// the window/object record walked by the manager
struct Obj {
    unsigned char pad0[4];
    int mField4;                        // 0x04
    unsigned char pad8[0x14];
    float m1c;                          // 0x1c
    float m20;                          // 0x20
    float m24;                          // 0x24
    float m28;                          // 0x28
    float m2c;                          // 0x2c
    float m30;                          // 0x30
    unsigned char m34;                  // 0x34 active-layout flag
    unsigned char pad35[3];
    float m38;                          // 0x38
    float m3c;                          // 0x3c
    float m40;                          // 0x40
    float m44;                          // 0x44
    float m48;                          // 0x48
    float m4c;                          // 0x4c
    int m50;                            // 0x50 (layout)
    int m54, m58, m5c;                  // 0x54..
    int m60, m64, m68, m6c, m70;
    int m74, m78, m7c, m80, m84, m88, m8c;
    int m90, m94, m98, m9c, ma0, ma4, ma8, mac, mb0, mb4;
    int mb8;                            // 0xb8
    int mFieldBC;                       // 0xbc
    unsigned char padc0[0x58];
    int m118;                           // 0x118
    float m11c;                         // 0x11c
    int m120;                           // 0x120
    int m124;                           // 0x124
    int m128;                           // 0x128
};

// the manager singleton at 0x01687348
struct Manager {
    unsigned char pad0[0x24];
    float mGlowDecay;                   // 0x24 damage-glow decay rate
    float mRefillRate;                  // 0x28 bar refill rate
    float mDrainRate;                   // 0x2c bar drain rate
    int GetPriority();                          // 0x00e31100 (thiscall)
    Obj* Find(const int& key);                  // 0x00b72230 (thiscall, ret 4)
    int Alloc();                                // 0x00b72160 (thiscall)
    Obj* Make(int handle);                      // 0x00b72210 (thiscall, ret 4)
};

// cSPUILayout: only the members 00b68aa0 needs; the two-argument call shape is
// what the resolver matches against the original's call sequence (via 0x008105b0).
struct cSPUILayout {
    void* FindWindowByID(unsigned id, int a);   // 0x008105b0 (thiscall)
};

extern Manager* gManager;               // 0x01687348

extern float kColourZero;               // 0x01485378  0.0f
extern float kColourScale;              // 0x013f2100  255.0f

// helpers used by the register-ABI window routine @ 00b68910
extern char gVtbl13f94d4;               // 0x013f94d4  RTTI-ish token passed to slot 3
extern int  __cdecl FUN_00bfc480();     // 0x00bfc480
extern void* __cdecl cConnectionDialog_ctor(void*);          // 0x00810000
extern int   __cdecl cSPUILayout_Init(void* self, const wchar_t* name, int a, int b, unsigned c); // 0x00812160
extern void* __cdecl cSPUILayout_FindWindowByID(void* self, unsigned id, int a);                  // 0x008105b0
extern void  __cdecl cSPUILayout_Shutdown(void* self, unsigned a);                                // 0x00811ad0
extern void  __cdecl cSPUILayout_dtor(void* self);                                               // 0x00811fe0
extern void  __cdecl AnchorWindowToWindow(void* a, void* b, int c, int d);                        // 0x00807340
extern const wchar_t kRolloverInvulnName[];   // 0x01464990 L"Rollover_ScenarioInvulnerableImage"
extern float kOne_;                      // 0x01485720  1.0f
extern float kProbeLimit;                // 0x013eb1bc
extern float __cdecl Clamp01(float v);   // 0x005a6e00

// axis-aligned rectangle handed back by window slot 0x38
struct Rect {
    float left;                         // 0x00
    float top;                          // 0x04
    float right;                        // 0x08
    float bottom;                       // 0x0c
};

// the min(max(v, 0), 1) form MSVC inlined into 0x00b69010 at three sites
static __inline float Clamp01Inline(float v)
{
    __m128 x = _mm_set_ss(v);
    x = _mm_max_ss(_mm_setzero_ps(), x);
    x = _mm_min_ss(x, _mm_set_ss(1.0f));
    return _mm_cvtss_f32(x);
}

// helpers used by the layout builder @ 00b68aa0
extern int  __cdecl FUN_00b687d0(int* value);          // 0x00b687d0 (FindOrCreate)
extern float __cdecl FUN_00b685e0(int* value);         // 0x00b685e0
extern void* __cdecl operator_new(unsigned n, const char* file, int a, int b, int c, int d);  // FUN_00f473a0
extern void* __cdecl SPUIHelpers_CenterWindowInRect(void* obj);   // FUN_00b5b800
extern void* __cdecl GetCurrentGameMode();              // FUN_00cd40b0
extern int   __cdecl TribeModeStrategyInstance();       // 0x00cd40b0 SP::cTribeModeStrategy::Instance
// Layout-name wide strings (VA in the original).  Their exact text is in rdata-literal.txt
// because the resolver's string search is unreliable for UTF-16 literals.
extern const wchar_t kLayout_TribeTool[];               // L"Rollover_TribeTool"          0x01464b2c
extern const wchar_t kLayout_TribeCitizen[];            // L"Rollover_TribeCitizen"       0x01464b54
extern const wchar_t kLayout_TribeHut[];                // L"Rollover_TribeHut"           0x01464b08
extern const wchar_t kLayout_TribeMinimap[];            // L"Rollover_Tribe_Minimap"      0x01464ad8
extern const wchar_t kLayout_ScenarioVehicle[];         // L"Rollover_ScenarioVehicle"    0x01464bcc
extern const wchar_t kLayout_CivVehicle[];              // L"Rollover_CivVehicle"         0x01464ba4
extern const wchar_t kLayout_CityMinimap[];             // L"RolloverCity_Minimap"        0x01464a48
extern const wchar_t kLayout_SpaceCity[];               // L"RolloverSpaceCity"           0x01464a24
extern const wchar_t kLayout_SharedHealthBar[];         // L"SharedHealthBar"             0x01464a04
extern const wchar_t kLayout_Building[];                // L"Rollover_Building"           0x01464b80
extern const wchar_t kLayout_UFO[];                     // L"RolloverUFO"                 0x01464ac0
extern const wchar_t kLayout_Creature[];                // L"Rollover_Creature"           0x01464a9c
extern const wchar_t kLayout_CRGMinimap[];              // L"Rollover_CRGMinimap"         0x01464a74
extern const wchar_t kLayout_FixedObject[];             // L"Rollover_FixedObject"        0x014649d8

// =============================================================================
// @ 0x00b68720  Walk the manager's window list, returning the first window whose
// mField4 is set and which matches the requested category bits (flags).
int __cdecl FindWindow(unsigned char flags)
{
    int key = gManager->GetPriority();
    Obj* o;
    while ((o = gManager->Find(key)) != 0) {
        if (o->mField4 != 0) {
            if ((flags & 8) != 0) {
                if (o->mFieldBC != 0)
                    return o->mField4;
            } else if ((flags & 2) != 0) {
                if (o->m50 != 0 && o->m44 == 0.0f)
                    return o->mField4;
            } else if ((flags & 4) != 0) {
                if (o->m50 != 0 && o->m44 != 0.0f)
                    return o->mField4;
            } else if ((flags & 0x10) != 0) {
                if (o->m120 != 0)
                    return o->mField4;
            }
        }
    }
    return 0;
}

// =============================================================================
// @ 0x00b687d0  Find a manager record whose +4 value is `value`; if none exists,
// allocate a fresh record, attach `value` (refcounted), reset its state fields,
// and return the record handle.
int __cdecl FindOrCreate(int* value)
{
    int key = gManager->GetPriority();
    int* o;
    while ((o = (int*)gManager->Find(key)) != 0) {
        if ((int*)o[1] == value)
            return *o;
    }

    int handle = gManager->Alloc();             // 0x00b72160
    if (handle == 0)
        return 0;
    Obj* rec = (Obj*)gManager->Make(handle);    // 0x00b72210
    int* old = (int*)rec->mField4;
    if (value != old) {
        if (value != 0)
            (*(void(__thiscall**)(int*))value[0])(value);            // slot 0
        rec->mField4 = (int)value;
        if (old != 0)
            (*(void(__thiscall**)(int*))(old[0] + 4))(old);          // slot 1
    }
    rec->m1c = 0.0f;
    rec->m30 = 0.0f;
    rec->m28 = 0.0f;
    rec->m24 = 0.0f;
    rec->m2c = 0.0f;
    rec->m38 = 0.0f;
    rec->m3c = 0.0f;
    rec->m40 = 0.0f;
    rec->m44 = 0.0f;
    rec->m48 = 0x7f7fffff;
    rec->m4c = 0x7f7fffff;
    int* p = (int*)rec->m50;
    if (p != 0) {
        rec->m50 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 8))(p);                  // slot 2
    }
    rec->m118 = 0x075f3ea8;
    p = (int*)rec->mb8;
    if (p != 0) {
        rec->mb8 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 8))(p);                  // slot 2
    }
    rec->m11c = 0.0f;
    p = (int*)rec->m120;
    if (p != 0) {
        rec->m120 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 4))(p);                  // slot 1
    }
    rec->m124 = 0;
    rec->m128 = 0;
    return handle;
}

// =============================================================================
// @ 0x00b693b0  Register-ABI helper (incoming ecx = rect provider, esi = target
// window, stack float alpha at entry+4): builds a rect from the provider's
// slot-0x34 rectangle scaled by alpha on the x axis and hands it to the
// target's slot 0x60, then sets the colour/visibility from alpha.  The two
// register arguments are modelled as explicit leading parameters.
void FUN_00b693b0(void* pProvider, void* pTarget, float alpha)
{
    const Rect* r = (const Rect*)(*(void*(__thiscall**)(void*))(*(int*)pProvider + 0x34))(pProvider);
    Rect rc;
    rc.left = 0.0f;
    rc.top = 0.0f;
    rc.right = (r->right - r->left) * alpha;
    rc.bottom = r->bottom - r->top;
    (*(void(__thiscall**)(void*, Rect*))(*(int*)pTarget + 0x60))(pTarget, &rc);

    if (alpha == 0.0f) {
        (*(void(__thiscall**)(void*, int, int))(*(int*)pTarget + 0x7c))(pTarget, 1, 0);
        return;
    }
    int level = _mm_cvtss_si32(_mm_set_ss(alpha * kColourScale));
    (*(void(__thiscall**)(void*, unsigned int))(*(int*)pTarget + 0x5c))(
        pTarget, ((unsigned int)level << 0x18) | 0xffffffu);
    (*(void(__thiscall**)(void*, int, int))(*(int*)pTarget + 0x7c))(pTarget, 1, 1);
}

// =============================================================================
// @ 0x00b69460  Register-ABI helper (incoming esi = a window, edi = a mode):
// fetches the window's slot-0x0c sub-object and toggles that sub-object's
// slot-0x7c visibility; a real mode is then forwarded to the window's
// slot-0x14.  The two register arguments are explicit parameters here.
void FUN_00b69460(void* pWindow, int mode)
{
    void* pCtx = 0;
    if (pWindow != 0)
        pCtx = (*(void*(__thiscall**)(void*, void*))(*(int*)pWindow + 0x0c))(pWindow, (void*)0xeeee8218);
    if (mode == -1) {
        (*(void(__thiscall**)(void*, int, int))(*(int*)pCtx + 0x7c))(pCtx, 1, 0);
        return;
    }
    (*(void(__thiscall**)(void*, int, int))(*(int*)pCtx + 0x7c))(pCtx, 1, 1);
    (*(void(__thiscall**)(void*, int))(*(int*)pWindow + 0x14))(pWindow, mode);
}

// =============================================================================
// @ 0x00b68910  Register-ABI window routine (incoming ecx = an object whose
// slot-3 method yields a window, edi = the manager record).  Creates a
// Rollover_ScenarioInvulnerableImage layout, finds its window, sizes and
// anchors it to the record's panel, then shuts the layout down.  The two
// register arguments are explicit parameters here.
void FUN_00b68910(void* pOwner, Obj* self)
{
    void* pWin = 0;
    if (pOwner != 0)
        pWin = (*(void*(__thiscall**)(void*, void*))(*(int*)pOwner + 0x0c))(pOwner, (void*)&gVtbl13f94d4);
    self->m34 = 0;
    if (pWin == 0)
        return;
    if (!FUN_00bfc480())
        return;

    self->m34 = 1;
    if (self->m64 != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m64 + 0x7c))((void*)self->m64, 1, 0);
    if (self->m68 != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m68 + 0x7c))((void*)self->m68, 1, 0);
    if (self->m6c != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m6c + 0x7c))((void*)self->m6c, 1, 0);
    if (self->m74 != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m74 + 0x7c))((void*)self->m74, 1, 0);

    // cSPUILayout instance (0x18 bytes); ctor/Init/Shutdown/dtor are the same
    // thiscall helpers the original invokes, modelled with an explicit self.
    char layout[0x18];
    cConnectionDialog_ctor(layout);
    if (!cSPUILayout_Init(layout, kRolloverInvulnName, 0x40464100, 0, 0x5b598fa)) {
        cSPUILayout_dtor(layout);
        return;
    }

    void* pItem = cSPUILayout_FindWindowByID(layout, 0x26e0df3, 1);
    if (pItem != 0)
        (*(void(__thiscall**)(void*))(*(int*)pItem + 0x00))(pItem);
    void* pR = (*(void*(__thiscall**)(void*))(*(int*)pItem + 0x10))(pItem);
    if (pR != 0) {
        void* pR2 = (*(void*(__thiscall**)(void*))(*(int*)pItem + 0x10))(pItem);
        (*(void(__thiscall**)(void*, void*))(*(int*)pR2 + 0xdc))(pR2, pItem);
    }
    cSPUILayout_Shutdown(layout, 1);

    void* pPanel = (void*)self->m70;
    (*(void(__thiscall**)(void*, void*))(*(int*)pPanel + 0xd8))(pPanel, pItem);
    (*(void(__thiscall**)(void*, float, float))(*(int*)pItem + 0x70))(pItem, 0.0f, 0.0f);

    const Rect* a = (const Rect*)(*(void*(__thiscall**)(void*))(*(int*)pPanel + 0x38))(pPanel);
    float height = a->bottom - a->top;
    const Rect* b = (const Rect*)(*(void*(__thiscall**)(void*))(*(int*)pPanel + 0x38))(pPanel);
    float width = b->right - b->left;
    (*(void(__thiscall**)(void*, float, float))(*(int*)pItem + 0x74))(pItem, width, height);
    AnchorWindowToWindow(pPanel, pItem, 0x300, 0);
    (*(void(__thiscall**)(void*))(*(int*)pItem + 0x04))(pItem);

    cSPUILayout_dtor(layout);
}

// =============================================================================
// @ 0x00b69010  Register-ABI health-bar/decay updater (incoming esi = the
// record, stack floats target at entry+4 and dt at entry+8).  Eases the
// record's bar towards its target, clamps its sub-values through the
// min(max(v,0),1) sequence the original inlines, and returns whether the flash
// value (record+0x38) is still positive.  The register argument is an explicit
// trailing parameter here.
bool FUN_00b69010(float target, float dt, Obj* self)
{
    // damage-glow decay (inline clamp at 0x00b6904a)
    self->m44 = Clamp01Inline(self->m44 - gManager->mGlowDecay * dt);

    self->m20 = target;
    if (target > self->m1c) {
        self->m28 = target;
        self->m30 = target;
    }
    if (self->m1c == kProbeLimit)
        self->m1c = target;

    if (self->m40 > 0.0f) {
        self->m40 -= dt;
        return self->m38 > 0.0f;
    }

    // flash still growing
    if (self->m38 < 1.0f) {
        if (self->m1c != target) {
            self->m38 = Clamp01Inline(self->m38 + gManager->mRefillRate * dt);
            if (self->m44 > self->m38)
                self->m38 = self->m44;
        }
        return self->m38 > 0.0f;
    }

    // bar below target: ramp the chase value down, then the bar up
    if (target > self->m1c) {
        if (self->m24 > 0.0f)
            self->m24 = Clamp01Inline(self->m24 - gManager->mRefillRate * dt);
        if (self->m2c < 1.0f) {
            self->m2c = Clamp01Inline(self->m2c + gManager->mRefillRate * dt);
        } else {
            self->m1c += gManager->mDrainRate * dt;
            if (self->m1c >= self->m20)
                self->m1c = self->m20;
        }
        return self->m38 > 0.0f;
    }

    // bar above target: drain the cooldown, then chase or snap
    if (target < self->m1c) {
        bool cooldownWasZero = true;
        if (self->m2c > 0.0f) {
            self->m2c = Clamp01Inline(self->m2c - gManager->mRefillRate * dt);
            cooldownWasZero = false;
        }
        if (self->m24 < 1.0f && self->m28 > self->m1c) {
            self->m24 = Clamp01Inline(self->m24 + gManager->mRefillRate * dt);
            return self->m38 > 0.0f;
        }
        self->m24 = 1.0f;
        if (cooldownWasZero) {
            self->m1c -= gManager->mDrainRate * dt;
            if (self->m1c < self->m20)
                self->m1c = self->m20;
        }
        return self->m38 > 0.0f;
    }

    // bar at target
    if (self->m24 > 0.0f && self->m28 > self->m1c) {
        self->m24 = Clamp01Inline(self->m24 - dt);
        return self->m38 > 0.0f;
    }
    self->m28 = target;
    self->m30 = target;
    if (self->m3c > 0.0f) {
        if (self->m38 < 1.0f)
            self->m38 = Clamp01Inline(self->m38 + gManager->mRefillRate * dt);
        else
            self->m3c -= dt;
    } else {
        self->m38 -= gManager->mRefillRate * dt;
        if (self->m44 > self->m38)
            self->m38 = self->m44;
    }
    return self->m38 > 0.0f;
}

// =============================================================================
// @ 0x00b68aa0  SP::sFindOrCreateUI.  Looks the record up (creating it if
// needed), and if its layout slot (+0x50) is still empty, builds the appropriate
// rollover layout for the requested category and caches every window handle the
// other helpers use.  Faithful C; the switch/string ordering keeps this from
// being byte-exact.
int __cdecl sFindOrCreateUI(int* param_1, int param_2, float param_3)
{
    int handle = FUN_00b687d0(param_1);
    Obj* rec = gManager->Make(handle);
    if (rec->m50 != 0)
        return (int)rec;

    if (param_3 == -1.0f)
        param_3 = FUN_00b685e0(param_1);

    rec->m1c = param_3;
    rec->m30 = param_3;
    rec->m28 = param_3;

    int* nw = (int*)operator_new(0x18, "Simulator/HealthBar", 0, 0, 0, 0);
    int* win = 0;
    if (nw != 0)
        win = (int*)SPUIHelpers_CenterWindowInRect(nw);

    int* old = (int*)rec->m50;
    if (win != old) {
        if (win != 0)
            (*(void(__thiscall**)(int*))(win[0] + 4))(win);      // slot 1
        rec->m50 = (int)win;
        if (old != 0)
            (*(void(__thiscall**)(int*))(old[0] + 8))(old);      // slot 2
    }

    void* mode = GetCurrentGameMode();
    unsigned flags;
    const wchar_t* name;
    switch (param_2) {
    case 2:  flags = 0xe9f70df9; name = kLayout_TribeTool;        break;
    case 3:  flags = 0xe9f70df9; name = kLayout_TribeCitizen;     break;
    case 4:  flags = 0xe9f70df9; name = kLayout_TribeHut;         break;
    case 5:  flags = 0x5b598f6;  name = kLayout_TribeMinimap;     break;
    case 6:
        flags = 0xe9f70df9;
        name = (mode == (void*)0x01654c10) ? kLayout_ScenarioVehicle : kLayout_CivVehicle;
        break;
    case 7:
        if (mode != (void*)0x01654c05)
            goto default_case;
        flags = 0x5b598f6;  name = kLayout_CityMinimap;           break;
    case 8:
        flags = 0xe9f70df9;
        name = (mode == (void*)0x01654c05) ? kLayout_SpaceCity : kLayout_SharedHealthBar;
        break;
    case 9:  flags = 0xe9f70df9; name = kLayout_Building;         break;
    case 11: flags = 0xe9f70df9; name = kLayout_UFO;              break;
    case 12:
        if (mode != (void*)0x01654c01 && mode != (void*)0x01654c10)
            goto default_case;
        flags = 0xe9f70df9;  name = kLayout_Creature;             break;
    case 14: flags = 0x5b598f6;  name = kLayout_CRGMinimap;       break;
    case 16: flags = 0xe9f70df9; name = kLayout_FixedObject;      break;
    default:
    default_case:
        flags = 0xe9f70df9;  name = kLayout_SharedHealthBar;      break;
    }

    cSPUILayout_Init((void*)rec->m50, name, 0x40464100, 1, flags);

    cSPUILayout* lay = (cSPUILayout*)rec->m50;
    if (lay != 0)
        (*(void(__thiscall**)(cSPUILayout*, int))(*(int*)lay + 0x7c))(lay, 1);  // SetVisibility

    rec->m54 = (int)lay->FindWindowByID(0x93310e4a, 1);
    rec->m58 = (int)lay->FindWindowByID(0x933103eb, 1);
    rec->m5c = (int)lay->FindWindowByID(0x31e94d0, 1);
    rec->m60 = (int)lay->FindWindowByID(0x933103ea, 1);
    rec->m64 = (int)lay->FindWindowByID(0x26e0df0, 1);
    rec->m68 = (int)lay->FindWindowByID(0x26e0df1, 1);
    rec->m6c = (int)lay->FindWindowByID(0x26e0df2, 1);
    rec->m70 = (int)lay->FindWindowByID(0x26e0df3, 1);
    rec->m74 = (int)lay->FindWindowByID(0x46adf86, 1);
    rec->m78 = (int)lay->FindWindowByID(0x3caf1f4, 1);
    rec->m7c = (int)lay->FindWindowByID(0x2b0e0f6, 1);
    rec->m80 = (int)lay->FindWindowByID(0x3f8a0d2, 1);
    rec->m84 = (int)lay->FindWindowByID(0x4c1f3a0, 1);
    rec->m88 = (int)lay->FindWindowByID(0x5d2a1b9, 1);
    rec->m8c = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* w90 = (int*)lay->FindWindowByID(0x4d039a8, 1);
    if (w90 != 0) {
        int* p = w90;
        int* r = 0;
        if (w90 != 0)
            r = (int*)(*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);
        rec->m90 = (int)r;
    }
    rec->m94 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->m98 = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* w74 = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->m74 = (int)w74;
    if (w74 != 0) {
        unsigned vis = *((unsigned char*)gManager + 0x30);
        (*(void(__thiscall**)(int*, unsigned, int))(*(int*)w74 + 0x7c))(w74, vis, 1);
    }
    FUN_00b68910(param_1, rec);
    rec->m9c = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma0 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma4 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma8 = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* wac = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mac = (int)wac;
    if (wac != 0 && GetCurrentGameMode() == (void*)0x01654c02) {
        int gm = (*(int(__thiscall**)(int*))(*param_1 + 0x38))(param_1);
        if (gm == 0xee02c7) {
            int inst = TribeModeStrategyInstance();
            void* arg = (inst == 0) ? 0 : (void*)(inst + 4);
            (*(void(__thiscall**)(int*, void*))(wac[0] + 0x104))(wac, arg);
        }
    }

    int* p = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mb0 = (p == 0) ? 0 : (*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);
    p = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mb4 = (p == 0) ? 0 : (*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);

    return (int)rec;
}
