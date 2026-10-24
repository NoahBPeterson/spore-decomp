// Slice s0106a0a0 (batch gold6): SP::cSPUISpace space-UI refresh helpers --
// mission-rollover banners, active-planet info panel, comm-button state,
// minimap/slots/show-hide toggles, and the effects-batch emitter.
//
// Flags: /O2 /MD /Gy /TP
//
// The stub classes below carry role-named fields at the retail offsets read off
// the disassembly (the migrated headers hold the 2008 dev-PDB layout, which is
// shifted relative to retail).

#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---------------------------------------------------------------------------
// fixed globals (addresses are relocation bytes masked by the checker)
// ---------------------------------------------------------------------------
extern void*       gSpaceTokenTranslator;   // 0x016e0d08, +0xc = active planet record
extern const float kFHalf;                  // 0x01471064  0.5f
extern const float kF10000;                 // 0x013f0620  10000.0f
extern const float kFOne;                   // 0x01485720  1.0f
extern const float kFNeg10000;              // 0x013f4fd0 -10000.0f
extern u8          gEfxMatrixSrc[];         // 0x016e2800
extern float       gEfxVec[3];              // 0x016e2824

// ---------------------------------------------------------------------------
// external free functions
// ---------------------------------------------------------------------------
void* SP_GetNounManager();                  // 0x00b3d230
void* SP_GetMissionManager();               // 0x00feb9f0
void* SP_GetActivePlanet();                 // 0x01021260
void* SP_GetActivePlanetRecord();           // 0x010212a0
int   SP_IsPlanetArchived();                // 0x01021240
int   FUN_01021230();                       // 0x01021230
void* SP_GetPlayerHomePlanet();             // 0x01021370
u32   SP_GetUniverseContext();              // 0x01021080
void* SP_SpaceGameGet();                    // 0x01002bd0
void* SP_GetUFOSimulator();                 // 0x00ffbe50
void* SP_CommManager();                     // 0x00b3d4a0
void* SP_GetTriggerManager();               // 0x00b3d4d0
void* SP_EffectsManager();                  // 0x0067ddd0
void* SP_GetHUDSpaceFrame();                // 0x0067caf0
void* SP_GetSystemNounManager();            // 0x00b3d410
u32   FUN_00458a40(void* rgb);              // 0x00458a40  ColorRGBToU32
u32   FUN_00c8b540();                       // 0x00c8b540
u32   FUN_00c70e00();                       // 0x00c70e00
u8    FUN_00c70b50();                       // 0x00c70b50
void* FUN_00e2eba0(u32 id);                 // 0x00e2eba0
void  FUN_01066630(void* p);                // 0x01066630
void  SetImageFromKey(void* win, void* key);                     // 0x00e2f5c0
void  SetTooltipText(void* win, void* text, int a, int b);       // 0x00806de0
void  FUN_0041cb40(void* dst, void* src);   // 0x0041cb40  Matrix3::Assign

// ---------------------------------------------------------------------------
// stub types
// ---------------------------------------------------------------------------
class cUIWin {
public:
    virtual void  w00();
    virtual void  w04();
    virtual void  w08();
    virtual void* w0c(u32);
    virtual void* w10();
    virtual void  w14();
    virtual void  w18();
    virtual void  w1c();
    virtual u32   w20();
    virtual void  w24();
    virtual void  w28(u32, u32);              // 0x28
    virtual void  w2c();
    virtual void  w30();
    virtual void* w34();
    virtual void* w38();
    virtual void  w3c();
    virtual void  w40();
    virtual void  w44();
    virtual void  w48();
    virtual void  w4c();
    virtual void  w50();
    virtual void  w54();
    virtual u8    w58();
    virtual void  w5c();
    virtual void  w60(void*);
    virtual void  w64(float, float);
    virtual void  w68();
    virtual void  w6c();
    virtual void  w70(float, float);
    virtual void  w74(float, float);
    virtual void  w78();
    virtual void  w7c(u32, bool);              // 0x7c
    virtual void  w80(void*);
};

struct cUIWinNoArgs {                          // layout windows (slot 0x28 returns u8)
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual u8 w28();
};

struct cObj238 { u32 FUN_00ff3f00(); };
struct cNounManager { u8 FUN_00b5ca60(); };
struct cGameNounManager { void* GetAvatar(); };
struct cGameInputManager { u8 FUN_00e393b0(); };
struct cTriggerManager { u8 FUN_00ac80f0(); };
struct cAvatar { u8 FUN_00ff6360(); };
struct cSpaceInventory { u8 m74c; };
struct cUFOSimulator { void* GetPlayerInventory(); };
struct cCommMgr { u8 SpaceToolSelect(void* rec, void* ctx); };
struct cCommScreen { u8 IsActive(); };
struct cHud { u8 IsShown(); };

struct cMission {
    u8    IsActive();                          // 0xc44c80
    void* GetModel();                          // 0xc45ce0
};
struct cMissionManager { void** GetMissionList(); };  // 0xfedd50
struct cBannerSort { void* SortBanners(); };           // 0xb8de30

struct cGlobalUI { void* FindWindowByID(u32 id); };
struct cLayout   { void* FindWindowByID(u32 id, u32 rec); };

struct cCivData { void** GetCities(void* a, void* b); };
struct cPlanet {
    void* GetName();
    void* FUN_00c71e30();
};
struct cEmpire {
    u8    pad84[0x84];
    void* m84;                                 // +0x84
    u8    FUN_00c30910();                      // 0xc30910
    void* GetColor(void* out);                 // 0xc32cd0
};
struct cStarRecordRef { void* GetCommContext(); };

struct cString {
    u32 m00, m04, m08, m0c;
    u8  m10, m11, mPad[2];
    cString(u32 a, u32 b, const wchar_t* c);   // 0x006b5770
    ~cString();                                // 0x006b5240
    void* GetText();                           // 0x006b55c0
};

struct cEfxNode {
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18(void*); virtual void e1c();
    virtual void e20(); virtual void e24(); virtual void e28(); virtual void e2c();
};
struct cEffectsMgr {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28();
    virtual u8   m2c(u32 id, u32 a, void* out);
};

// ---------------------------------------------------------------------------
// cSPUISpace
// ---------------------------------------------------------------------------
class cSPUISpace {
public:
    u8            pad00[0x224];
    cGlobalUI*    mpGlobalUI;      // +0x224
    u8            pad228[0x238 - 0x228];
    cObj238*      m238;            // +0x238
    u8            pad23c[0x258 - 0x23c];
    cLayout*      mpGlobalLayout;  // +0x258
    u8            pad25c[0x478 - 0x25c];
    cString       mTooltipText;    // +0x478
    u8            pad48c[0x598 - 0x48c];
    void*         mGlowInfoList;   // +0x598
    u8            pad59c[0x5cc - 0x59c];
    u32           mDial;           // +0x5cc
    u8            m5d0;            // +0x5d0
    u8            m5d1;            // +0x5d1
    u8            m5d2;            // +0x5d2

    u32   UpdateMissionRollover(u32 a0, u32 a1, u32 a2, u32 a3);
    void  FUN_0106a280();
    void  UpdateActivePlanetInfo();
    void  UpdateCommButtons(void* outState, void* outColor);
    void  FUN_0106a970();
    void  FUN_0106aa10(u32 on);
    void  FUN_0106aab0(u32 on);
    void  FUN_0106ab20(int state);
    void  FUN_0106ac90(void* civ);

    // members defined in other slices
    u8    ToggleSlotsUI();         // 0x01067fb0
    u8    ToggleMinimapUI();       // 0x01068080
    u8    UpdateStarMapFilters();  // 0x01068140
    void  FUN_01066230(u32 on);    // 0x01066230
    u8    FUN_01065b30();          // 0x01065b30
    void  FUN_01068800(u32 a, void* b, u32 c);  // 0x01068800
    void* GetDominantSpeciesThumbnailKey(u32* out, u32 planet); // 0x01065f00
};

// ---------------------------------------------------------------------------
// vtable-call helpers (used only by the non-byte-exact bodies)
// ---------------------------------------------------------------------------
typedef void* (__thiscall *FnRetP0)(void*);
typedef void* (__thiscall *FnRetP2)(void*, u32, u32);
typedef u32   (__thiscall *FnRetU0)(void*);
typedef void  (__thiscall *FnV1p_)(void*, void*);
typedef void  (__thiscall *FnV2f_)(void*, float, float);
typedef void  (__thiscall *FnV2u_)(void*, u32, u32);

static __forceinline void* VCallP0(void* o, u32 off) {
    FnRetP0 f = (FnRetP0)((*(void***)o)[off / 4]); return f(o);
}
static __forceinline void* VCallP2(void* o, u32 off, u32 a, u32 b) {
    FnRetP2 f = (FnRetP2)((*(void***)o)[off / 4]); return f(o, a, b);
}
static __forceinline void VCallV1p(void* o, u32 off, void* a) {
    FnV1p_ f = (FnV1p_)((*(void***)o)[off / 4]); f(o, a);
}
static __forceinline void VCallV2f(void* o, u32 off, float a, float b) {
    FnV2f_ f = (FnV2f_)((*(void***)o)[off / 4]); f(o, a, b);
}
static __forceinline void VCallV2u(void* o, u32 off, u32 a, u32 b) {
    FnV2u_ f = (FnV2u_)((*(void***)o)[off / 4]); f(o, a, b);
}

// ---------------------------------------------------------------------------
// SP::cSPUISpace
// ---------------------------------------------------------------------------
// @ 0x0106a0a0 UpdateMissionRollover
u32 cSPUISpace::UpdateMissionRollover(u32 a0, u32 a1, u32 a2, u32 a3) {
    void* nm = SP_GetNounManager();
    u8 bl = ((cNounManager*)nm)->FUN_00b5ca60();
    void* gl = mGlowInfoList;
    VCallV2u(gl, 0xf0, 0x1c22446, 1);
    int count = 0;
    u8 any = 0;
    if (bl == 0) {
        void* mm = SP_GetMissionManager();
        void** list = ((cMissionManager*)mm)->GetMissionList();
        void** it = (void**)list[0];
        void** end = (void**)list[1];
        if (it != end) {
            do {
                cMission* m = (cMission*)*it;
                if (m->IsActive() != 0 && *(u32*)((char*)m + 0x17c) == 0) {
                    void* model = m->GetModel();
                    if (model != 0) {
                        int ok = 0;
                        if (a1 != 0 && a1 == (u32)model) ok = 1;
                        else if (a2 != 0 &&
                                 a2 == (u32)((cBannerSort*)((char*)model + 0x13c))->SortBanners()) ok = 1;
                        if (ok && count < 3) {
                            any = 1;
                            FUN_01068800((u32)gl, (void*)m, 1);
                            count++;
                        }
                    }
                }
                it++;
            } while (it != end);
            if (any != 0) {
                VCallV2f(gl, 0x64, *(float*)&a3, 0.0f);
                float* p = (float*)VCallP0(gl, 0x34);
                float v[4];
                v[0] = p[0];
                v[1] = p[1];
                v[2] = p[2];
                v[3] = *(float*)&a1;
                int n = count * 0x22;
                if (n < 0) v[3] = (float)n + kFNeg10000;
                VCallV1p(gl, 0x60, v);
            }
        }
    }
    if (count < 3) {
        u32 id = (u32)(count + 0x1c2245) << 4;
        int n = 3 - count;
        do {
            void* w = VCallP2(gl, 0xf0, id, 1);
            VCallV2u(w, 0x7c, 1, 0);
            id += 0x10;
            n--;
        } while (n != 0);
    }
    VCallV2u(gl, 0x7c, 1, (u32)any);
    if (any == 0) return 0;
    return (u32)mGlowInfoList;
}

// @ 0x0106a280 FUN_0106a280
void cSPUISpace::FUN_0106a280() {
    void* home = SP_GetPlayerHomePlanet();
    cCivData* civ = (cCivData*)((cBannerSort*)home)->SortBanners();
    cCivData* rec = (cCivData*)SP_IsPlanetArchived();
    if (civ == 0 || rec == 0) return;

    cUIWin* w0 = (cUIWin*)mpGlobalUI->FindWindowByID(0x616ebc0);
    cUIWin* w1 = (cUIWin*)mpGlobalUI->FindWindowByID(0x616ebb8);
    cUIWin* w2 = (cUIWin*)mpGlobalUI->FindWindowByID(0x6174050);
    if (w0 == 0 || w1 == 0 || w2 == 0) return;

    FUN_01066630(civ->GetCities(0, 0));
    FUN_01066630(rec->GetCities(0, 0));

    {
        cString s(0xf5e156f8, 0x66dde72, (const wchar_t*)0x149c250);
        SetTooltipText(w2, s.GetText(), -1, 1);
    }
    float* pf0 = (float*)w0->w38();
    float len = pf0[2] - pf0[0];
    float* pf1 = (float*)w1->w38();
    float f = ((pf1[2] + pf1[0]) * kFHalf) / len;
    float ratio;
    if (*(float*)&civ <= *(float*)&rec) {
        ratio = (kFOne - *(float*)&civ / *(float*)&rec) * (kFOne - f) + f;
    } else {
        ratio = (kFOne - (*(float*)&civ - *(float*)&rec) / (kF10000 - *(float*)&rec)) * f;
    }
    float v = ratio;
    if (ratio > 1.0f) v = 1.0f;
    else if (ratio < 0.0f) v = 0.0f;
    v = v * len;
    float* pw = (float*)w2->w38();
    w2->w70(v - (pw[2] - pw[0]) * kFHalf, pw[1]);

    cUIWin* w3 = (cUIWin*)mpGlobalUI->FindWindowByID(0x616ebc8);
    if (w3 != 0) {
        float* pf = (float*)w3->w38();
        w3->w74(0.0f, pf[3] - pf[1]);
    }
}

// @ 0x0106a4e0 UpdateActivePlanetInfo
void cSPUISpace::UpdateActivePlanetInfo() {
    u8 flag = 0;
    if (mpGlobalLayout != 0) {
        cUIWinNoArgs* w = (cUIWinNoArgs*)mpGlobalLayout->FindWindowByID(0x755f180, 1);
        if (w != 0) flag = (u8)(w->w28() & 1);
    }
    FUN_01066230(flag);
    void* planet = SP_GetActivePlanet();
    void* rec = SP_GetActivePlanetRecord();
    *(void**)((char*)gSpaceTokenTranslator + 0xc) = rec;

    int level;
    cUIWin* pw = (cUIWin*)mpGlobalUI->FindWindowByID(0x562a2da);
    if (pw != 0) {
        if (planet != 0) {
            pw->w80(((cPlanet*)planet)->GetName());
        } else if (FUN_01021230() != 0) {
            pw->w80((void*)FUN_00c8b540());
        } else {
            pw->w80((void*)0x13ec468);
        }
        level = (int)FUN_00c70e00();
    } else if (planet != 0) {
        level = (int)FUN_00c70e00();
    } else {
        level = 0;
    }

    {
        cUIWin* w = (cUIWin*)mpGlobalUI->FindWindowByID(0x36fe7c1);
        if (w != 0) {
            bool has = 0 < level;
            w->w7c(1, has);
            if (has) {
                u32* pi = (u32*)planet;
                if (pi[0x4f] == (u32)SP_GetPlayerHomePlanet()) {
                    SetImageFromKey(w, (void*)0x15b9124);
                } else if (((cEmpire*)planet)->FUN_00c30910() == 0) {
                    SetImageFromKey(w, (void*)FUN_00e2eba0(pi[0x4f]));
                    cString s(0x2db6dad3, 0x473d0cf, 0);
                    SetTooltipText(w, s.GetText(), -1, 1);
                } else {
                    SetImageFromKey(w, (void*)0x15b9118);
                }
            }
        }
    }

    cUIWin* wa = (cUIWin*)mpGlobalUI->FindWindowByID(0x36c0957);
    cUIWin* wb = (cUIWin*)mpGlobalUI->FindWindowByID(0x44d94d1);
    if (level < 2 || wa == 0 || wb == 0) {
        wb->w7c(1, 0);
        wa->w7c(1, 0);
    } else {
        cString s(0x2db6dad3, 0x3e81c64, 0);
        wb->w80(s.GetText());
        wb->w7c(1, 1);
        SetTooltipText(wb, s.GetText(), -1, 1);
        u32 key;
        SetImageFromKey(wa, GetDominantSpeciesThumbnailKey(&key, ((u32*)planet)[0x4f]));
        wa->w7c(1, 1);
    }

    cUIWin* wc = (cUIWin*)mpGlobalUI->FindWindowByID(0x6748980);
    if (wc != 0) {
        u8 v = 0;
        if (planet != 0) v = FUN_00c70b50();
        wc->w7c(1, v);
    }
}

// @ 0x0106a7b0 UpdateCommButtons
void cSPUISpace::UpdateCommButtons(void* outState, void* outColor) {
    u8 show = 0;
    u8 cam = 0;
    *(u32*)outColor = 0xffffffff;
    void* planet = SP_GetActivePlanet();
    if (planet == 0) goto tail;
    {
        void* p13c = *(void**)((char*)planet + 0x13c);
        cEmpire* emp = (cEmpire*)((cPlanet*)planet)->FUN_00c71e30();
        if (emp != 0 && p13c != 0) {
            cGameNounManager* gnm = (cGameNounManager*)SP_SpaceGameGet();
            void* avatar = gnm->GetAvatar();
            u8 bVar2;
            if (((cGameInputManager*)SP_GetSystemNounManager())->FUN_00e393b0() != 0) bVar2 = 1;
            else if (FUN_01065b30() != 0) bVar2 = 1;
            else if (((cTriggerManager*)SP_GetTriggerManager())->FUN_00ac80f0() != 0) bVar2 = 1;
            else if (avatar != 0 && ((cAvatar*)avatar)->FUN_00ff6360() != 0) bVar2 = 1;
            else bVar2 = 0;

            u8 bVar3;
            if (SP_GetUniverseContext() == 2) {
                bVar3 = 1;
            } else if (SP_GetUniverseContext() == 1 &&
                       ((cSpaceInventory*)((cUFOSimulator*)SP_GetUFOSimulator())->GetPlayerInventory())->m74c == 0) {
                bVar3 = 1;
            } else {
                bVar3 = 0;
            }

            if (bVar2 || bVar3) {
                show = 0;
                cam = 0;
            } else {
                show = 1;
                cam = 0;
                if (emp->FUN_00c30910() != 0) {
                    if (((cCommMgr*)SP_CommManager())->SpaceToolSelect(emp->m84,
                            ((cStarRecordRef*)p13c)->GetCommContext()) != 0) {
                        if (((cHud*)SP_GetHUDSpaceFrame())->IsShown() != 0) cam = 1;
                    }
                } else {
                    if (((cHud*)SP_GetHUDSpaceFrame())->IsShown() != 0) cam = 1;
                }
            }

            u32 color;
            *(u32*)outColor = FUN_00458a40(emp->GetColor(&color));
        }
    }
tail:
    {
        u8 active;
        if (((cCommScreen*)SP_CommManager())->IsActive() == 0) {
            bool flag = false;
            if (mpGlobalLayout != 0) {
                cUIWinNoArgs* w = (cUIWinNoArgs*)mpGlobalLayout->FindWindowByID(0x755f180, 1);
                if (w != 0 && (w->w28() & 1) != 0) flag = true;
            }
            active = (u8)flag;
        } else {
            active = 1;
        }
        if (cam != 0 && active == 0) { *(u32*)outState = 1; return; }
        if (show != 0 && active == 0) { *(u32*)outState = 0; return; }
    }
    *(u32*)outState = 2;
}

// @ 0x0106a970 FUN_0106a970
void cSPUISpace::FUN_0106a970() {
    cSPUISpace* self = this;
    UpdateCommButtons(&mDial, &self);
    cUIWin* w0 = (cUIWin*)mpGlobalUI->FindWindowByID(0x5d6aa28);
    cUIWin* w1 = (cUIWin*)mpGlobalUI->FindWindowByID(0x17f29bf);
    cUIWin* w2 = (cUIWin*)mpGlobalUI->FindWindowByID(0x61b0530);
    if (w0 != 0 && w1 != 0 && w2 != 0) {
        w0->w7c(2, mDial != 2);
        w1->w7c(2, mDial != 2);
        w2->w7c(2, mDial == 1);
    }
}

// @ 0x0106aa10 FUN_0106aa10
void cSPUISpace::FUN_0106aa10(u32 on) {
    if (m5d0 == 0) {
        if (m238->FUN_00ff3f00() == 0) {
            cUIWin* w = (cUIWin*)mpGlobalUI->FindWindowByID(0x4359752);
            cUIWin* p = (w != 0) ? (cUIWin*)w->w0c(0x8ed27e7a) : 0;
            u32 v = p->w20();
            if (((v >> 2) & 1) != (u8)on) {
                p->w28(4, on);
                ToggleSlotsUI();
            }
            m5d1 = (u8)on;
        } else {
            m5d1 = (u8)on;
        }
    } else {
        m5d1 = (u8)on;
    }
}

// @ 0x0106aab0 FUN_0106aab0
void cSPUISpace::FUN_0106aab0(u32 on) {
    if (m5d0 == 0 && m5d1 == 0) {
        cUIWin* w = (cUIWin*)mpGlobalUI->FindWindowByID(0x4359752);
        cUIWin* p;
        if (w != 0) p = (cUIWin*)w->w0c(0x8ed27e7a);
        else p = 0;
        u32 v = p->w20();
        if (((v >> 2) & 1) != (u8)on) {
            p->w28(4, on);
            ToggleSlotsUI();
        }
    }
}

// @ 0x0106ab20 FUN_0106ab20
void cSPUISpace::FUN_0106ab20(int state) {
    bool b = state != 0;
    cUIWin* w1 = (cUIWin*)mpGlobalUI->FindWindowByID(0x4359752);
    cUIWin* w2 = (cUIWin*)mpGlobalUI->FindWindowByID(0x562a141);
    cUIWin* w3 = (cUIWin*)mpGlobalUI->FindWindowByID(0x453ef531);
    cUIWin* p = 0;
    if (w3 != 0) p = (cUIWin*)w3->w0c(0x8ed27e7a);
    if (w1 == 0) return;
    if (w2 == 0) return;
    w1->w7c(2, b);
    ToggleSlotsUI();
    w2->w7c(1, b);
    ToggleMinimapUI();
    u32 fill;
    if (b) {
        if (m5d2 == 0) fill = 1;
        else fill = 0;
    } else {
        u32 v = p->w20();
        m5d2 = ~(u8)(v >> 2) & 1;
        fill = 0;
    }
    p->w28(4, fill);
    UpdateStarMapFilters();
    if (state == 2 || state == 3) {
        cUIWin* w = (cUIWin*)mpGlobalUI->FindWindowByID(0x4359752);
        if (w != 0) {
            w = (cUIWin*)w->w0c(0x8ed27e7a);
            if (w != 0) {
                u32 v = w->w20();
                if ((u8)((v >> 2) & 1) != (u8)(state == 3)) {
                    w->w28(4, state);
                    ToggleSlotsUI();
                }
            }
        }
    }
}

// @ 0x0106ac90 FUN_0106ac90
void cSPUISpace::FUN_0106ac90(void* civ) {
    if (SP_GetUniverseContext() == 0) return;
    cEfxNode* node = 0;
    cEffectsMgr* mgr = (cEffectsMgr*)SP_EffectsManager();
    if (node != 0) { node->e04(); node = 0; }
    u8 ok = mgr->m2c(0x3e2cc60, 0, &node);
    if (ok != 0) {
        node->e08();
        struct { u16 f0; u16 f2; u16 f4; float x, y, z; } args;
        args.f0 = 0; args.f2 = 0; args.f4 = 0;
        args.x = gEfxVec[0]; args.y = gEfxVec[1]; args.z = gEfxVec[2];
        u8 mat[0x30];
        FUN_0041cb40(mat, gEfxMatrixSrc);
        if (SP_GetUniverseContext() == 2) {
            void** p = ((cCivData*)civ)->GetCities(0, 0);
            *(u32*)&args.x = (u32)p[0];
            *(u32*)&args.y = (u32)p[1];
            *(u32*)&args.z = (u32)p[2];
            args.f0 = (u16)(args.f0 | 4);
            args.f2 = (u16)(args.f2 + 1);
        }
        node->e18(&args);
    }
    if (node != 0) node->e04();
}