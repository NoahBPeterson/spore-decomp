// Slice s010678e0 (batch gold6): SP::cSPUISpace space-UI helpers (tooltip and
// charge bar updates, minimap/slots/filter toggles), the eastl Blk28 (0x28-byte
// refcounted element) copy/destroy/range helpers, and eastl::deque<...>::clear.
//
// Flags: /O2 /MD /Gy /TP
//
// The stub classes below carry role-named fields at the retail offsets read off
// the disassembly (the migrated headers hold the 2008 dev-PDB layout, which is
// shifted relative to retail).

#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// fixed globals / tables (addresses are relocation bytes masked by the checker)
// ---------------------------------------------------------------------------
extern const signed char kNibbleSum[];     // 0x0145d1c4 nibble checksum table
extern float             gChargeCache;     // 0x015b9444 cached tool-charge value
extern const float       kFloatNegOne;     // 0x013eb1bc -1.0f
extern const float       kChargeMin;       // 0x013ef74c  0.15f
extern const float       kChargeMax;       // 0x01485720  1.0f
extern const float       kFloatHuge;       // 0x01477fbc  200.0f
extern void*             gTooltipGate;     // 0x0169d3c8
extern void*             gTokenTranslator; // 0x016e0d08
extern const u32         kIconTableA[];    // 0x0149c1a4
extern const u32         kIconTableB[];    // 0x0149c1b0

// ---------------------------------------------------------------------------
// external free functions
// ---------------------------------------------------------------------------
void* SP_NounManager();                    // 0x00b3d300
void* SP_SpaceGameGet();                   // 0x01002bd0
void* SP_GameTimeManager();                // 0x00b3d380
void* SP_GameInputManager();               // 0x00b3d250
void* SP_CommManager();                    // 0x00b3d4a0
void* SP_WindowManager();                  // 0x0067caa0
void* SP_GetActivePlanet();                // 0x01021260
void* SP_GetActivePlanetRecord();          // 0x010212a0
void* SP_GetSettingHost();                 // 0x00401090
void* SP_GetSystemAT();                    // 0x00a206f0
void* SP_GetPlayerEmpire();                // 0x01021300
void* SP_GetStateManager();                // 0x00b3d3f0
void  SP_DeleteArray(void* p);             // 0x00f47380 operator delete[]
float FUN_00c72030(void* civ);             // 0x00c72030
void  SetTooltipText(void* win, void* text, int a, int b);  // 0x00806de0
void  SetImageFromKey(void* win, void* key);                // 0x00e2f5c0
void  FUN_00572020(u32 handle, u32 on);    // 0x00572020
void __stdcall FUN_00812d80(u32 on);       // 0x00812d80
void  FUN_01066180(void* p, float f);      // 0x01066180
void* FUN_005994b0(void* win);             // 0x005994b0

// ---------------------------------------------------------------------------
// stub types
// ---------------------------------------------------------------------------
struct Key {
    u32 m0, m1, m2;
};

struct RefObj {                             // Blk28+0x00 payload
    virtual void AddRef();                  // slot 0
    virtual void Release();                 // slot 1
};
struct ObjRel {                             // Blk28+0x08 payload
    virtual void v0();                      // slot 0
    virtual void v1();                      // slot 1
    virtual void Release();                 // slot 2
};

struct Blk28 {
    RefObj* mpRef;      // +0x00
    u32     m04;        // +0x04
    ObjRel* m08;        // +0x08
    u32     m0c;        // +0x0c
    u32     m10;        // +0x10
    u32     m14;        // +0x14
    u32     m18;        // +0x18
    u8      m1c;        // +0x1c
    u8      mPad[3];
    u32     m20;        // +0x20
    u32     m24;        // +0x24

    Blk28* CopyCtor(const Blk28& src);      // 0x01068450
    Blk28& operator=(const Blk28& src);     // 0x010685a0
    Blk28* Destroy(u8 flags);               // 0x010687d0
};

struct DeqNode {
    void*    m00;       // +0x00
    void*    m04;       // +0x04
    DeqNode* m08;       // +0x08
};
struct Deque {
    void* m00; void* m04; void* m08; u32 m0c;
    int* clear(int* out, DeqNode* self, DeqNode* root); // 0x01068380
};

struct cGameNounManager { void* GetPlayerCivilization(); };
struct cGameData {
    float FUN_00fe67b0();
    void* FUN_00fe42a0();
};
struct cLivingUniverse { void* FUN_00c30cb0(); };
struct cSimManager { u8 FUN_01075500(); };
struct cSimThing  { void FUN_01065d20(); };
struct cSpaceGame {
    u8 pad00[0x14];
    cSimThing*   m14;     // +0x14
    cSimManager* m18;     // +0x18
    u8 pad1c[0x50 - 0x1c];
    u32 m50;              // +0x50
    cGameData* GetPlayerTribe();
};
struct cGameTimeManager {
    u8 pad48[0x48];
    u8 m48;               // +0x48
    void DecPauseGate(u32 id);
};
struct cGameInputManager {
    u8 pad110[0x110];
    u32 m110;             // +0x110
};
struct cCommManager {
    u8 IsActive();
    void CloseCommEvent();
    void FUN_00aed2c0(void* a, void* b);
};
struct cAudioSys {                 // EA::Audio system; only slot 0x28 is called
    virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0c();
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24();
    virtual bool a28(u32 h);       // +0x28
};
struct cToolGate  { void* FUN_00cfe780(void* p); };
struct cPlanet {
    void* FUN_00c71e30();
    u8 pad13c[0x13c];
    void* m13c;           // +0x13c
};
struct cPlanetInfo   { u8 pad84[0x84]; void* m84; };      // +0x84
struct cPlanetRecord { u8 pad2c[0x2c]; u32 mFlags; };     // +0x2c
struct cStarRecordRef { void* GetCommContext(); };
struct cPosse {
    void* FindItem(u32 id);
    u8 pad0[0xa4];
    u32 m0a4;             // +0xa4
    u32 m0a8;             // +0xa8
};
struct cGlobalUI { void* FindWindowByID(u32 id); };
struct cLayout   { void* FindWindowByID(u32 id, u32 rec); };
struct cLayoutHolder {
    void* FindWindowByID(u32 id, u32 rec);
    void  FUN_00e369f0();
    void  FUN_00e365a0(u32 a);
};
struct cProgressBar { void Update(float f, void* p); };
struct cSpeciesMgr  { void* GetProfile(const Key& k); };
struct cTokenTranslator {
    u8 pad14[0x14];
    u32 m14;              // +0x14
    u8 pad18[0x24 - 0x18];
    void* m24;            // +0x24
};
struct cWin61c  { void FUN_00e31030(u32 img, u32 a, u32 b, u32 c); };
struct cStateMgr { u8 ShouldShow(u32 id); };
struct cToolObj {
    virtual void s0();
    virtual void s1();        // +0x04
    virtual void s2();
    virtual void s3(u32);     // +0x0c
};
// Generic SPUI window: only the slots the slice actually calls are named.
struct cUIWin {
    virtual void  w00();          // 0x00
    virtual u32   w04();          // 0x04
    virtual void  w08();
    virtual void* w0c(u32);       // 0x0c
    virtual void* w10();          // 0x10
    virtual void  w14();
    virtual void  w18();
    virtual void  w1c();
    virtual u32   w20();          // 0x20
    virtual void  w24();
    virtual u32   w28();          // 0x28
    virtual void  w2c();
    virtual void  w30();
    virtual float* w34();         // 0x34
    virtual float* w38();         // 0x38
    virtual void  w3c();
    virtual void  w40();
    virtual void  w44();
    virtual void  w48();
    virtual void  w4c();
    virtual void  w50();
    virtual void  w54();
    virtual void  w58();
    virtual void  w5c();
    virtual void  w60();
    virtual void  w64();
    virtual void  w68(float, float);   // 0x68
    virtual void  w6c();
    virtual void  w70();
    virtual void  w74();
    virtual void  w78();
    virtual void  w7c(u32, u32);       // 0x7c
    virtual void  w80(u32);            // 0x80
};
struct cString {
    u32 m00, m04, m08, m0c;
    u8  m10, m11, mPad[2];
    cString(u32 a, u32 b, const wchar_t* c);   // 0x006b5770
    ~cString();                                // 0x006b5240
    void* GetText();                           // 0x006b55c0
};

// ---------------------------------------------------------------------------
// vtable-call helpers
// ---------------------------------------------------------------------------
typedef u32  (__thiscall *FnRetU32)(void*);
typedef u8   (__thiscall *FnRetU8)(void*);
typedef void (__thiscall *FnV0)(void*);
typedef void (__thiscall *FnV1)(void*, u32);
typedef void (__thiscall *FnV2)(void*, u32, u32);
typedef void (__thiscall *FnV2f)(void*, float, float);
typedef u32  (__thiscall *FnRetU32_1)(void*, u32);
typedef u8   (__thiscall *FnRetU8_1)(void*, u32);

static __forceinline u32 VCallU32(void* o, u32 off) {
    FnRetU32 f = (FnRetU32)((*(void***)o)[off / 4]);
    return f(o);
}
static __forceinline u8 VCallU8(void* o, u32 off) {
    FnRetU8 f = (FnRetU8)((*(void***)o)[off / 4]);
    return f(o);
}
static __forceinline u32 VCallU32a(void* o, u32 off, u32 a) {
    FnRetU32_1 f = (FnRetU32_1)((*(void***)o)[off / 4]);
    return f(o, a);
}
static __forceinline u8 VCallU8a(void* o, u32 off, u32 a) {
    FnRetU8_1 f = (FnRetU8_1)((*(void***)o)[off / 4]);
    return f(o, a);
}
static __forceinline void VCallV0(void* o, u32 off) {
    FnV0 f = (FnV0)((*(void***)o)[off / 4]);
    f(o);
}
static __forceinline void VCallV1(void* o, u32 off, u32 a) {
    FnV1 f = (FnV1)((*(void***)o)[off / 4]);
    f(o, a);
}
static __forceinline void VCallV2(void* o, u32 off, u32 a, u32 b) {
    FnV2 f = (FnV2)((*(void***)o)[off / 4]);
    f(o, a, b);
}
static __forceinline void VCallV2f(void* o, u32 off, float a, float b) {
    FnV2f f = (FnV2f)((*(void***)o)[off / 4]);
    f(o, a, b);
}

// ---------------------------------------------------------------------------
// cSPUISpace
// ---------------------------------------------------------------------------
class cSPUISpace {
public:
    u8 pad00[0x1fc];
    cString       mMinimapOffTip;   // +0x1fc
    cString       mMinimapOnTip;    // +0x210
    cGlobalUI*    mpGlobalUI;       // +0x224
    cProgressBar* mpProgressBar;    // +0x228
    u8 pad22c[0x258 - 0x22c];
    cLayout*      mpLayout;         // +0x258
    u8 pad25c[0x478 - 0x25c];
    cString       mTooltipText;     // +0x478
    u8 pad48c[0x530 - 0x48c];
    Blk28*        mpListBegin;      // +0x530
    Blk28*        mpListEnd;        // +0x534
    u8 pad538[0x5a8 - 0x538];
    cLayoutHolder* mpLayoutHolder;  // +0x5a8
    u8 pad5ac[0x5bc - 0x5ac];
    u32           mAudioHandle;     // +0x5bc
    cToolObj*     mpCurrentTool;    // +0x5c0
    cPosse*       mpPosse;          // +0x5c4
    u32           mProgressCount;   // +0x5c8
    u8 pad5cc[0x61c - 0x5cc];
    void*         mpWindow61c;      // +0x61c

    void  FUN_010678e0();
    void  FUN_010679f0();
    void  UpdateToolChargeBar(float f);
    u8    FUN_01067b60();
    void  SetToolTip(void* a1, void* a2, void* a3, void* a4, void* a5);
    void  FUN_01067e70(void* p1, Key* key);
    Blk28* FUN_01067ef0(u32 id);
    void  FUN_01067f60(u32 on);
    u8    ToggleSlotsUI();
    u8    ToggleMinimapUI();
    u8    UpdateStarMapFilters();
    void  FUN_010681e0(int a, int b);
    void  FUN_01068230();
    void  FUN_010682a0(u32 id);
    void  FUN_01068300();
    void  FUN_01068330();
    bool  FUN_01068350();
    void  FUN_01066230(u32 on);
};

// ---------------------------------------------------------------------------
// SP::cSPUISpace
// ---------------------------------------------------------------------------
// @ 0x010678e0 FUN_010678e0
void cSPUISpace::FUN_010678e0() {
    float v = kFloatNegOne;
    cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
    void* civ = nm->GetPlayerCivilization();
    if (civ != 0) {
        v = FUN_00c72030(civ);
    }
    if (v != gChargeCache) {
        gChargeCache = v;
        void* win = mpGlobalUI->FindWindowByID(0xabcd1001);
        if (win != 0) {
            if (gChargeCache < 0.0f) {
                cString str(0xc0152a6d, 0x4cac3d8, 0);
                SetTooltipText(win, str.GetText(), -1, 1);
            } else {
                void* saved = ((cToolGate*)gTooltipGate)->FUN_00cfe780(civ);
                cString str(0xc0152a6d, 0x65f79f1, 0);
                SetTooltipText(win, str.GetText(), -1, 1);
                ((cToolGate*)gTooltipGate)->FUN_00cfe780(saved);
            }
        }
    }
}

// @ 0x010679f0 FUN_010679f0
void cSPUISpace::FUN_010679f0() {
    cSpaceGame* game = (cSpaceGame*)SP_SpaceGameGet();
    cGameData* tribe = game->GetPlayerTribe();
    if (tribe == 0) return;
    float t = tribe->FUN_00fe67b0();
    cProgressBar* bar = mpProgressBar;
    cLivingUniverse* lu = (cLivingUniverse*)SP_GetPlayerEmpire();
    void* e = lu->FUN_00c30cb0();
    bar->Update(t, e);
    u32 n = (u32)tribe->FUN_00fe42a0();
    u32 i = mProgressCount;
    if (i < n) {
        do {
            cUIWin* win = (cUIWin*)mpGlobalUI->FindWindowByID(i + 0x6161080);
            if (win != 0) {
                void* x = win->w0c(0x106f146);
                if (x != 0) {
                    VCallV1((char*)x + 0x20c, 0x14, 1);
                }
            }
            i = i + 1;
        } while (i < n);
        mProgressCount = n;
    }
}

// @ 0x01067aa0 UpdateToolChargeBar
void cSPUISpace::UpdateToolChargeBar(float f) {
    if (f <= 0.15f) f = 0.15f;
    if (1.0f <= f) f = 1.0f;
    void* w1 = mpGlobalUI->FindWindowByID(0x341ba47);
    void* w2 = mpGlobalUI->FindWindowByID(0x341ba3b);
    if (w1 != 0 && w2 != 0) {
        float* r = (float*)VCallU32(w1, 0x34);
        VCallV2f(w2, 0x68, (r[2] - r[0]) * f, r[3] - r[1]);
    }
}

// @ 0x01067b60 FUN_01067b60
u8 cSPUISpace::FUN_01067b60() {
    cSpaceGame* game = (cSpaceGame*)SP_SpaceGameGet();
    u32 flags = game->m50;
    u32 sum = 0;
    if (flags != 0) {
        do {
            sum += (int)kNibbleSum[flags & 15];
            flags >>= 4;
        } while (flags != 0);
        if (sum > 0) return 1;
    }
    cGameTimeManager* gtm = (cGameTimeManager*)SP_GameTimeManager();
    if (gtm->m48 & 1) return 1;
    void* win = mpGlobalUI->FindWindowByID(0x5d6aa28);
    if (win == 0) return 1;
    if ((((cUIWin*)win)->w28() & 2) == 0) return 1;
    SP_GetActivePlanet();
    cSpaceGame* g2 = (cSpaceGame*)SP_SpaceGameGet();
    if (g2->m18->FUN_01075500()) return 1;
    if (((cStateMgr*)SP_GetStateManager())->ShouldShow(0)) return 1;
    if (((cCommManager*)SP_CommManager())->IsActive()) {
        ((cCommManager*)SP_CommManager())->CloseCommEvent();
        return 1;
    }
    void* planet = SP_GetActivePlanet();
    cPlanetInfo* info = 0;
    if (planet != 0) info = (cPlanetInfo*)((cPlanet*)planet)->FUN_00c71e30();
    cStarRecordRef* ref = (cStarRecordRef*)((cPlanet*)planet)->m13c;
    planet = info->m84;
    void* ctx = ref->GetCommContext();
    ((cCommManager*)SP_CommManager())->FUN_00aed2c0(planet, ctx);
    return 1;
}

// @ 0x01067c50 SetToolTip
void cSPUISpace::SetToolTip(void* a1, void* a2, void* a3, void* a4, void* a5) {
    cLayoutHolder* h = mpLayoutHolder;
    void* w1 = h->FindWindowByID(0x44ead4f, 1);
    void* w2 = h->FindWindowByID(0x7064a982, 1);
    void* w3 = h->FindWindowByID(0x9064a9b3, 1);
    void* w4 = h->FindWindowByID(0x6550c98, 1);
    if (w1 == 0 || w2 == 0 || w3 == 0 || w4 == 0) return;
    if (a5 != 0) {
        VCallV2(w1, 0x7c, 1, 1);
        SetImageFromKey(w1, a5);
    } else {
        VCallV2(w1, 0x7c, 1, 0);
    }
    float gap = 0.0f;
    if (a2 != 0) {
        VCallV2(w2, 0x7c, 1, 1);
        VCallV1(w2, 0x80, (u32)a2);
        void* x = FUN_005994b0(w2);
        if (x != 0) {
            FUN_01066180(x, 0.0f);
            float* r = (float*)VCallU32(w2, 0x38);
            float d = r[2] - r[0];
            if (d > 0.0f) gap = d;
        }
    } else {
        VCallV2(w2, 0x7c, 1, 0);
    }
    if (a3 != 0) {
        VCallV2(w3, 0x7c, 1, 1);
        VCallV1(w3, 0x80, (u32)a3);
        void* x = FUN_005994b0(w3);
        if (x != 0) FUN_01066180(x, gap);
    } else {
        VCallV2(w3, 0x7c, 1, 0);
    }
    if (a4 != 0) {
        VCallV2(w4, 0x7c, 1, 1);
        VCallV1(w4, 0x80, (u32)a4);
        void* x = FUN_005994b0(w4);
        if (x != 0) FUN_01066180(x, gap);
    } else {
        VCallV2(w4, 0x7c, 1, 0);
    }
    h->FUN_00e369f0();
    h->FUN_00e365a0((u32)a1);
}

// @ 0x01067e70 FUN_01067e70
void cSPUISpace::FUN_01067e70(void* p1, Key* key) {
    void* prof = ((cSpeciesMgr*)SP_GetSettingHost())->GetProfile(*key);
    if (prof == 0) return;
    Key local = *key;
    local.m1 = 0x2f7d0004;
    cTokenTranslator* tt = (cTokenTranslator*)gTokenTranslator;
    tt->m14 = 0;
    tt->m24 = prof;
    void* img = *(void**)((char*)prof + 0x51c);
    SetToolTip(p1, img, mTooltipText.GetText(), 0, &local);
}

// @ 0x01067ef0 FUN_01067ef0
Blk28* cSPUISpace::FUN_01067ef0(u32 id) {
    int count = (int)(mpListEnd - mpListBegin);
    for (int i = 0; i < count; ++i) {
        Blk28* e = &mpListBegin[i];
        if (e->mpRef != 0) {
            if (VCallU32(e->mpRef, 0x1c) == id) return e;
        }
    }
    return 0;
}

// @ 0x01067f60 FUN_01067f60
void cSPUISpace::FUN_01067f60(u32 on) {
    cGameInputManager* gim = (cGameInputManager*)SP_GameInputManager();
    if ((u8)on) gim->m110 = gim->m110 + 1;
    else        gim->m110 = gim->m110 - 1;
    void* wm = SP_WindowManager();
    u32 v = ((cUIWin*)wm)->w04();
    if (v != 0 && v != 4) {
        FUN_00812d80(on);
    }
    FUN_01066230(on);
}

// @ 0x01067fb0 ToggleSlotsUI
u8 cSPUISpace::ToggleSlotsUI() {
    void* w0 = mpGlobalUI->FindWindowByID(0x4359752);
    void* btn = 0;
    if (w0 != 0) btn = (void*)VCallU32a(w0, 0xc, 0x8ed27e7a);
    void* winA = mpGlobalUI->FindWindowByID(0x58d9b3e0);
    void* winB = mpGlobalUI->FindWindowByID(0x52c2948);
    u8 on = 0;
    if ((VCallU8(btn, 0x20) & 4) != 0) {
        void* p = (void*)VCallU32(btn, 0x10);
        if ((VCallU8(p, 0x28) & 2) != 0) on = 1;
    }
    VCallV2(winA, 0x7c, 1, (u32)on);
    void* rec = SP_GetActivePlanetRecord();
    u8 has = 0;
    if (rec != 0 && (((cPlanetRecord*)rec)->mFlags & 0x800) != 0) has = 1;
    VCallV2(winB, 0x7c, 1, (u32)has);
    return on;
}

// @ 0x01068080 ToggleMinimapUI
u8 cSPUISpace::ToggleMinimapUI() {
    void* w0 = mpGlobalUI->FindWindowByID(0x562a141);
    void* btn = 0;
    if (w0 != 0) btn = (void*)VCallU32a(w0, 0xc, 0x8ed27e7a);
    void* pw = mpGlobalUI->FindWindowByID(0x34c963f);
    u8 on = 0;
    if ((VCallU8(btn, 0x20) & 4) != 0) {
        void* p = (void*)VCallU32(btn, 0x10);
        if ((VCallU8(p, 0x28) & 1) != 0) on = 1;
    }
    VCallV2(pw, 0x7c, 2, (u32)on);
    cString* tip = (on != 0) ? &mMinimapOnTip : &mMinimapOffTip;
    void* host = (void*)VCallU32(btn, 0x10);
    SetTooltipText(host, tip->GetText(), -1, 1);
    return on;
}

// @ 0x01068140 UpdateStarMapFilters
u8 cSPUISpace::UpdateStarMapFilters() {
    void* w0 = mpGlobalUI->FindWindowByID(0x453ef531);
    void* btn = 0;
    if (w0 != 0) btn = (void*)VCallU32a(w0, 0xc, 0x8ed27e7a);
    void* pw = mpGlobalUI->FindWindowByID(0x5d42af0);
    u32 flags = VCallU32(btn, 0x20);
    u8 on = (u8)((flags >> 2) & 1);
    VCallV2(pw, 0x7c, 2, (u32)on);
    cString* tip = (on != 0) ? &mMinimapOnTip : &mMinimapOffTip;
    void* host = (void*)VCallU32(btn, 0x10);
    SetTooltipText(host, tip->GetText(), -1, 1);
    return on;
}

// @ 0x010681e0 FUN_010681e0
void cSPUISpace::FUN_010681e0(int a, int b) {
    if (a > 0 && b < a) {
        ((cWin61c*)mpWindow61c)->FUN_00e31030(kIconTableA[a], 0x622c8b6, 1, 0);
        return;
    }
    ((cWin61c*)mpWindow61c)->FUN_00e31030(kIconTableB[b], 0x622c8b6, 1, 0);
}

// @ 0x01068230 FUN_01068230
void cSPUISpace::FUN_01068230() {
    u32 h = mAudioHandle;
    cAudioSys* at = (cAudioSys*)SP_GetSystemAT();
    if (at != 0) {
        if (at->a28(h)) {
            FUN_00572020(mAudioHandle, 1);
        }
    }
    if (mpCurrentTool != 0) {
        mpCurrentTool->s3(0);
        if (mpCurrentTool != 0) {
            cToolObj* p = mpCurrentTool;
            mpCurrentTool = 0;
            return p->s1();
        }
    }
}

// @ 0x010682a0 FUN_010682a0
void cSPUISpace::FUN_010682a0(u32 id) {
    if (mpPosse == 0) return;
    void* item = mpPosse->FindItem(id);
    if (item == 0) return;
    VCallV2(mpPosse, 0xa8, (u32)item, 1);
    cPosse* p = mpPosse;
    if (((p->m0a8 - p->m0a4) & 0xfffffff8) == 0) {
        return ((FnV1)((*(void***)p)[0xc0 / 4]))(p, 0);
    }
}

// @ 0x01068300 FUN_01068300
void cSPUISpace::FUN_01068300() {
    cPosse* p = mpPosse;
    if (p != 0 && ((p->m0a8 - p->m0a4) & 0xfffffff8) != 0) {
        VCallV1(p, 0xc0, 1);
    }
}

// @ 0x01068330 FUN_01068330
void cSPUISpace::FUN_01068330() {
    if (mpPosse != 0) VCallV1(mpPosse, 0xc0, 0);
}

// @ 0x01068350 FUN_01068350
bool cSPUISpace::FUN_01068350() {
    if (mpLayout) {
        void* w = mpLayout->FindWindowByID(0x755f180, 1);
        if (w != 0) return (((cUIWin*)w)->w28() & 1) != 0;
    }
    return false;
}

// ---------------------------------------------------------------------------
// eastl::deque  /  Blk28 helpers
// ---------------------------------------------------------------------------
// @ 0x01068380 eastl_deque_clear
int* Deque::clear(int* out, DeqNode* self, DeqNode* root) {
    DeqNode* n = self->m08;
    out[1] = (int)root;
    out[0] = (int)n;
    while (n == 0) {
        out[1] += 4;
        n = *(DeqNode**)out[1];
        out[0] = (int)n;
    }
    DeqNode* r = (DeqNode*)root->m00;
    if (r == self) {
        root->m00 = r->m08;
        SP_DeleteArray(self);
        m0c = m0c - 1;
        return out;
    }
    DeqNode* e = r->m08;
    while (e != self) {
        r = e;
        e = r->m08;
    }
    r->m08 = e->m08;
    SP_DeleteArray(self);
    m0c = m0c - 1;
    return out;
}

// @ 0x01068450 Blk28_copy
Blk28* Blk28::CopyCtor(const Blk28& src) {
    RefObj* r = src.mpRef;
    mpRef = r;
    if (r != 0) r->AddRef();
    m04 = src.m04;
    m08 = src.m08;
    m0c = src.m0c;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    m1c = src.m1c;
    m20 = src.m20;
    m24 = src.m24;
    return this;
}

// @ 0x010684b0 FUN_010684b0
Blk28** FUN_010684b0(Blk28** out, Blk28* begin, Blk28* end, Blk28* dst) {
    *out = dst;
    while (begin != end) {
        Blk28* d = *out;
        if (d != 0) {
            RefObj* r = begin->mpRef;
            d->mpRef = r;
            if (r != 0) r->AddRef();
            d->m04 = begin->m04;
            d->m08 = begin->m08;
            d->m0c = begin->m0c;
            d->m10 = begin->m10;
            d->m14 = begin->m14;
            d->m18 = begin->m18;
            d->m1c = begin->m1c;
            d->m20 = begin->m20;
            d->m24 = begin->m24;
        }
        *out = *out + 1;
        begin = begin + 1;
    }
    return out;
}

// @ 0x01068530 FUN_01068530
void FUN_01068530(Blk28* dst, u32 count, const Blk28* src) {
    if (count == 0) return;
    do {
        if (dst != 0) {
            RefObj* r = src->mpRef;
            dst->mpRef = r;
            if (r != 0) r->AddRef();
            dst->m04 = src->m04;
            dst->m08 = src->m08;
            dst->m0c = src->m0c;
            dst->m10 = src->m10;
            dst->m14 = src->m14;
            dst->m18 = src->m18;
            dst->m1c = src->m1c;
            dst->m20 = src->m20;
            dst->m24 = src->m24;
        }
        count = count - 1;
        dst = dst + 1;
    } while (count != 0);
}

// @ 0x010685a0 Blk28_assign
Blk28& Blk28::operator=(const Blk28& src) {
    RefObj* n = src.mpRef;
    RefObj* o = mpRef;
    if (n != o) {
        if (n != 0) n->AddRef();
        mpRef = n;
        if (o != 0) o->Release();
    }
    m04 = src.m04;
    m08 = src.m08;
    m0c = src.m0c;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    m1c = src.m1c;
    m20 = src.m20;
    m24 = src.m24;
    return *this;
}

// @ 0x01068610 FUN_01068610
Blk28* FUN_01068610(Blk28* begin, Blk28* end, Blk28* dst) {
    if (begin == end) return dst;
    do {
        if (dst != 0) {
            RefObj* r = begin->mpRef;
            dst->mpRef = r;
            if (r != 0) r->AddRef();
            dst->m04 = begin->m04;
            dst->m08 = begin->m08;
            dst->m0c = begin->m0c;
            dst->m10 = begin->m10;
            dst->m14 = begin->m14;
            dst->m18 = begin->m18;
            dst->m1c = begin->m1c;
            dst->m20 = begin->m20;
            dst->m24 = begin->m24;
        }
        begin = begin + 1;
        dst = dst + 1;
    } while (begin != end);
    return dst;
}

// @ 0x01068710 FUN_01068710
Blk28* FUN_01068710(Blk28* begin, Blk28* end, Blk28* dst) {
    if (begin == end) return dst;
    do {
        RefObj* n = (end - 1)->mpRef;
        RefObj* o = (dst - 1)->mpRef;
        end = end - 1;
        dst = dst - 1;
        if (n != o) {
            if (n != 0) n->AddRef();
            dst->mpRef = n;
            if (o != 0) o->Release();
        }
        dst->m04 = end->m04;
        dst->m08 = end->m08;
        dst->m0c = end->m0c;
        dst->m10 = end->m10;
        dst->m14 = end->m14;
        dst->m18 = end->m18;
        dst->m1c = end->m1c;
        dst->m20 = end->m20;
        dst->m24 = end->m24;
    } while (end != begin);
    return dst;
}

// @ 0x010687a0 FUN_010687a0
void FUN_010687a0() {
    cGameTimeManager* tm = (cGameTimeManager*)SP_GameTimeManager();
    tm->DecPauseGate(0x4bf38a7);
    cSpaceGame* g = (cSpaceGame*)SP_SpaceGameGet();
    if (g != 0) {
        cSimThing* p = g->m14;
        return p->FUN_01065d20();
    } else {
        cSimThing* p = 0;
        return p->FUN_01065d20();
    }
}

// @ 0x010687d0 Blk28_destroy
Blk28* Blk28::Destroy(u8 flags) {
    ObjRel* o = m08;
    if (o != 0) o->Release();
    if (flags & 1) SP_DeleteArray(this);
    return this;
}