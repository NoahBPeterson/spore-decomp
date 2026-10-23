// Slice s00ce90c0 - SPAppMode/CityDisplayStrategy.obj region 0x00ce90c0..0x00cea080:
// SP::cCityDisplayStrategy posses / god-mode / vehicle-icon UI management.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include  (no /EHsc)
#include "types.h"

typedef unsigned int uint;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// ---- external callees (addresses in comments) --------------------------
void* __cdecl FUN_00f473a0(uint, const char*, int, int, const char*, int); // 0x00f473a0 operator new
void  __cdecl FUN_00f240d0(void*, void*);                          // 0x00f240d0 EventTree::Destroy
void  __cdecl FUN_00ce8d00(void*, void*, void*);                   // 0x00ce8d00
void* __cdecl FUN_008105b0(void*, u32, int);                       // 0x008105b0 cSPUILayout::FindWindowByID
void* __cdecl FUN_00b3d240(void*);                                 // 0x00b3d240 cSPUIGlobalUICiv::GetLayout
void  __cdecl FUN_00811ad0(void*, int);                            // 0x00811ad0 cSPUILayout::Shutdown
void* __cdecl FUN_00cf74c0();                                      // 0x00cf74c0 cCivModeStrategy::Get
void  __cdecl FUN_00cf74d0();                                      // 0x00cf74d0
void* __cdecl FUN_00b3d280();                                      // 0x00b3d280 GetCameraCtl
void* __cdecl FUN_00b3d350();                                      // 0x00b3d350 PlanetModel
void* __cdecl FUN_00b30d70();                                      // 0x00b30d70 GetGameTerrainCursor
void* __cdecl FUN_0067ddd0();                                      // 0x0067ddd0 EffectsManager
void* __cdecl FUN_00a206f0();                                      // 0x00a206f0 EA::Audio::GetSystemAT
void* __cdecl FUN_00921580(void*);                                 // 0x00921580 ?RBTreeIncrement
u8    __cdecl FUN_00e01380(void*);                                 // 0x00e01380
void* __cdecl FUN_00b10260(void*);                                 // 0x00b10260 cTerrainCameraController::GetTarget
void* __cdecl FUN_00ca10a0();                                      // 0x00ca10a0
void  __cdecl FUN_00b146a0(void*, int, int);                       // 0x00b146a0
void* __cdecl FUN_00b3d250();                                      // 0x00b3d250
void  __cdecl FUN_00e05930(void*, int);                            // 0x00e05930
void* __cdecl FUN_00cf8d70(void*, void*);                          // 0x00cf8d70 SetCameraTrackObject
uint  __cdecl FUN_00e23250();                                      // 0x00e23250 item count (static)
void  __cdecl FUN_00ca3350(void*, int);                            // 0x00ca3350
void  __cdecl FUN_00bfc5e0(void*, int);                            // 0x00bfc5e0
void  __cdecl FUN_00c9e870(void*, u32);                            // 0x00c9e870

// ---- window-area helper (address 0x00805ea0) --------------------------
struct Vec4 { float x, y, z, w; };
Vec4* __cdecl SPUIHelpers_GetMainWindowArea(Vec4* out); // 0x00805ea0

// ---- placeholder-struct members for thiscall-shaped direct callees ----
// Declaring these as (declaration-only) member functions makes the compiler
// emit `call rel32` with ecx set, instead of push/call/add-esp.
struct CIcon {
    void  Refresh();          // 0x00e21960
    void  RefreshAlt();       // 0x00e21980
    void  SetEnabled(u8);     // 0x00e215d0
    void* GetTaskSource();    // 0x00ca71d0
    void* FindItem(void*);    // 0x00e24c90
};

// cSPUILayout: UI layout handed out by the global civ UI (0x0093b6c0 is the
// accessor that returns it) and queried for windows by ID.
struct CSPUILayout {
    void* GetLayout();                 // 0x0093b6c0 (on cSPUIGlobalUICiv)
    void* FindWindowByID(u32 id, int); // 0x008105b0
    void  Shutdown(uint);              // 0x00811ad0
};

// The map value object (a vehicle / interactable) stored in the posse maps.
// Its vtable-bearing sub-object sits at +0x34; a further sub-object at +0x508.
struct Sub34 {
    void* mpVtbl;            // +0x00
    char  pad04[0x2c - 4];
};

// An effect handle owned by the strategy; the effect system releases the
// object pointed to at +0x04.
struct EffectHandle {
    void* mpVtbl;            // +0x00
    void* mpField4;          // +0x04
};
struct MapValue {
    char  pad00[0x34];
    Sub34 mSub34;            // +0x34 : embedded, first word is a vtable
    char  pad6c[0x4a8];      // to +0x508
    void* mField508;         // +0x508
};

// ---- helper object surfaces -------------------------------------------
//
// cSPUIPosse: posses the strategy manages.  Retail reads an item vector
// begin/end at +0xa4/+0xa8 and a per-posse flag byte at +0x1e4.
struct cSPUIPosse {
    char   pad00[0xa4];
    void** mpItemBegin;   // +0xa4
    void** mpItemEnd;     // +0xa8
    char   pad_ac[0x1e4 - 0xac];
    u8     mbFlag;        // +0x1e4

    int ItemCount() { return (int)((char*)mpItemEnd - (char*)mpItemBegin) >> 3; }
    void Refresh() { ((CIcon*)this)->Refresh(); }        // 0x00e21960
    void RefreshAlt() { ((CIcon*)this)->RefreshAlt(); }  // 0x00e21980
    void* FindItem(void* key) { return ((CIcon*)this)->FindItem(key); } // 0x00e24c90
};

// cGameData: the vehicle-ish object stored as a map key / icon object;
// retail reads a task source at +0x10 (via FUN_00ca71d0), a continent at
// +0xb1c and a civ index at +0xb20.
struct cGameData {
    char pad00[0xb1c];
    int  mContinent;   // +0xb1c
    int  mCivIndex;    // +0xb20
    char pad24[0xb68 - 0xb24];
    void* mpField_b68; // +0xb68
    void* mpField_b6c; // +0xb6c
};

// the object FUN_00ca71d0 returns (a task/state source)
struct CTaskSource {
    char pad00[0x10];
    int  mTask;   // +0x10
};

// A reference-counted handle (vtable[0] = AddRef, vtable[1] = Release).
// SelectVehicle takes one of these on the stack and ref-counts it.
struct RefPtr {
    static void AddRef(void* p)  { if (p) ((void(__thiscall*)(void*))(*(void**)p))(p); }
    static void Release(void* p) { if (p) ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
};

// cTerrainCameraController (returned by GetCameraCtl())
struct cTerrainCamera {
    char pad00[0x14];
    u8   mbFlag14;  // +0x14
    u8   mbFlag15;  // +0x15
    u8   mbFlag16;  // +0x16
    u8   mbFlag17;  // +0x17
};

// cPlanetModel: continent lookup
struct cPlanetModel {
    char pad00[0x64];
    int  mContinentFlags;  // +0x64
    void* __thiscall GetContinent(void* key);   // 0x00b88590
};

// =======================================================================
// retail layout of SP::cCityDisplayStrategy
// =======================================================================
struct CDS {
    void*  mpVtbl;                    // +0x00
    char   pad04[0x38 - 4];
    void*  mpIHandlerVtbl;            // +0x38
    u8     mbGodModeActive;           // +0x3c
    int    mGodModeVehiclePurpose;    // +0x40
    int    mGodModeVehicleLocomotion; // +0x44
    uint   mGodModeCiv;               // +0x48
    void*  mAutoHandler0;             // +0x4c
    void*  mAutoHandler4;             // +0x50
    void*  mAutoHandler8;             // +0x54
    void*  mAutoHandlerC;             // +0x58
    void*  mAutoHandler10;            // +0x5c
    void*  mpMode;                    // +0x60
    void*  mpGlobalCivUI;             // +0x64
    int    mDebugAIPage;              // +0x68
    cSPUIPosse* mPosses[4];           // +0x6c
    char   mMaps[4 * 0x1c];           // +0x7c
    void*  mpPosseIconLayout;         // +0xec
    void*  mpMiniMapWin;              // +0xf0
    void*  mpTargetingReticle;        // +0xf4
    void*  mpErrorReticle;            // +0xf8
    void*  mpExtraReticle;            // +0xfc
    void*  mAudioSounds[3];           // +0x100
    void*  mpSelEff0;                 // +0x10c
    void*  mpSelEff1;                 // +0x110
    void*  mpSelEff2;                 // +0x114
    void*  mpSelEff3;                 // +0x118
    void*  mpSelEff4;                 // +0x11c

    // map anchor / node accessors for mVehiclePosseMaps[i]
    // anchor is at +0x80 + i*0x1c ; node key at node+0x14, value at node+0x10.
    char* MapAnchor(int i) { return (char*)this + 0x80 + i * 0x1c; }
    char* MapEnd(int i)    { return (char*)this + 0x80 + i * 0x1c; }

    void GodModeUpdateReticles();          // 0x00ce90c0
    void AccumulatePosseArea(Vec4* out);   // 0x00ce9380
    void SetVehicleTask(cGameData* data, cGameData* vehicle); // 0x00ce9460
    void ResetPosses();                    // 0x00ce9560
    void UpdateUI(int dummy);              // 0x00ce9590
    void SetReticlesVisible(u8 visible); // 0x00ce96b0
    void ShutdownAll();                    // 0x00ce97e0
    int  HandleMessage(int msgID, void* msg); // 0x00ce9920
    void SelectVehicle(void* vehicle, int flag, int param4); // 0x00ce9b70
    void RefreshVehicleIcons(cGameData* vehicle);   // 0x00ce9c30
    void UpdateVehicleContinent(cGameData* vehicle); // 0x00ce9d30
    void BuildEffectDesc(int type, int variant);     // 0x00ce9e20
};

// =======================================================================
// 0x00ce90c0 - 697 bytes
// =======================================================================
// @ 0x00ce90c0
void CDS::GodModeUpdateReticles()
{
    int counts[4];
    int smooth[4];
    float widths[4];
    float fAcc = 0.0f;
    float fMaxW = 0.0f;
    float fSumW = 0.0f;
    float fLimit;
    int iter = 0;
    int i;
    int ci, cj, sel;

    counts[0] = mPosses[0]->ItemCount();
    counts[1] = mPosses[1]->ItemCount();
    counts[2] = mPosses[2]->ItemCount();
    counts[3] = mPosses[3]->ItemCount();
    smooth[0] = counts[0];
    smooth[1] = counts[1];
    smooth[2] = counts[2];
    smooth[3] = counts[3];

    float area[4];
    SPUIHelpers_GetMainWindowArea((Vec4*)area);
    fLimit = (area[3] - area[2]) - 100.0f;

    do {
        fSumW = 0.0f;
        ci = smooth[0];
        cj = counts[0];
        sel = 0;
        if (!(ci > 0 || (ci == 0 && counts[0] <= 0x400))) {
            ci = 0;
            cj = 0x400;
        }
        if (ci < smooth[1] || (ci == smooth[1] && cj <= counts[1])) {
            sel = 1;
            ci = smooth[1];
            cj = counts[1];
        }
        if (ci < smooth[2] || (ci == smooth[2] && cj <= counts[2])) {
            sel = 2;
            ci = smooth[2];
            cj = counts[2];
        }
        if (ci < smooth[3] || (ci == smooth[3] && cj <= counts[3])) {
            sel = 3;
        }
        if (iter > 0) {
            smooth[sel] = (smooth[sel] + 1) >> 1;
        }
        for (i = 0; i < 4; i++) {
            cSPUIPosse* p = mPosses[i];
            Vec4* r = ((Vec4*(__thiscall*)(void*, Vec4*, int, int, float))
                       (*(void**)(*(char**)p + 0x98)))(p, (Vec4*)0, counts[i], smooth[i], -1.0f);
            widths[i] = r->w - r->z;
            if (fAcc < r->y - r->x) fAcc = r->y - r->x;
            fSumW += r->w - r->z;
        }
        iter++;
    } while (fLimit <= fSumW);

    fSumW = 100.0f;
    for (i = 0; i < 4; i++) {
        cSPUIPosse* p = mPosses[i];
        ((void(__thiscall*)(void*, int, float, int, int))
         (*(void**)(*(char**)p + 0x90)))(p, 0, fSumW, 0, 0);
        ((void(__thiscall*)(void*, float))
         (*(void**)(*(char**)p + 0x94)))(p, fMaxW);
        fSumW += widths[i];
    }

    if (mpGlobalCivUI != 0 && FUN_00e01380(mpGlobalCivUI) != 0) {
        for (i = 0; i < 4; i++) {
            cSPUIPosse* p = mPosses[i];
            if (p != 0) {
                ((void(__thiscall*)(void*, int))
                 (*(void**)(*(char**)p + 0xc0)))(p, p->ItemCount() != 0);
            }
        }
    }
}

// =======================================================================
// 0x00ce9380 - 215 bytes: union of the posses' screen rects
// =======================================================================
// @ 0x00ce9380
void CDS::AccumulatePosseArea(Vec4* out)
{
    int i;
    u8 bFirst = 0;
    for (i = 0; i < 4; i++) {
        cSPUIPosse* p = mPosses[i];
        if (p == 0 || p->mbFlag == 0) continue;
        if (bFirst) {
            Vec4 tmp;
            Vec4* r = ((Vec4*(__thiscall*)(void*, Vec4*))
                       (*(void**)(*(char**)p + 0x9c)))(p, &tmp);
            if (r->x <= out->x) out->x = r->x;
            if (r->y <= out->y) out->y = r->y;
            if (out->z <= r->z) out->z = r->z;
            if (out->w <= r->w) out->w = r->w;
        } else {
            Vec4 tmp;
            Vec4* r = ((Vec4*(__thiscall*)(void*, Vec4*))
                       (*(void**)(*(char**)p + 0x9c)))(p, &tmp);
            out->x = r->x;
            bFirst = 1;
            out->y = r->y;
            out->z = r->z;
            out->w = r->w;
        }
    }
}

// =======================================================================
// 0x00ce9460 - 232 bytes: SP::cCityDisplayStrategy::SetVehicleTask
// =======================================================================
// @ 0x00ce9460
void CDS::SetVehicleTask(cGameData* data, cGameData* vehicle)
{
    (void)vehicle;
    CTaskSource* src = (CTaskSource*)((CIcon*)data)->GetTaskSource();
    u32 taskID;
    switch (src->mTask) {
    case 1:
        if (data->mCivIndex == 0) taskID = 0x5d68776;
        else if (data->mCivIndex == 1) taskID = 0x5d687f1;
        else taskID = (data->mCivIndex == 2 ? 0 : 0x14) + 0x5d68802;
        break;
    case 2:  taskID = 0x5d68851; break;
    case 3:  taskID = 0x5d688bc; break;
    case 4:  taskID = 0x5d68bb2; break;
    case 5:  taskID = 0x5d68c25; break;
    case 6:  taskID = 0x6032276; break;
    case 7:  taskID = 0x5d68c7e; break;
    case 8:  taskID = 0x5d68eed; break;
    case 9:
    case 10:
    case 11: taskID = 0x5d68f22; break;
    default:
        ((void(__thiscall*)(cGameData*, int))(*(void**)(*(char**)data + 0xa4)))(data, 0);
        return;
    }
    ((void(__thiscall*)(cGameData*, u32, void*, int))
     (*(void**)(*(char**)data + 0x9c)))(data, taskID, mpPosseIconLayout, 0);
}

// =======================================================================
// 0x00ce9560 - 38 bytes: reset all posses
// =======================================================================
// @ 0x00ce9560
void CDS::ResetPosses()
{
    int i;
    for (i = 0; i < 4; i++) {
        cSPUIPosse* p = mPosses[i];
        if (p != 0) {
            p->Refresh();
        }
    }
}

// =======================================================================
// 0x00ce9590 - 258 bytes: SP::cCityDisplayStrategy::UpdateUI
// =======================================================================
// @ 0x00ce9590
void CDS::UpdateUI(int dummy)
{
    (void)dummy;
    void* civUI = mpGlobalCivUI;
    cTerrainCamera* cam = (cTerrainCamera*)FUN_00b3d280();
    if (civUI == 0 || cam == 0) return;
    void* layout = ((CSPUILayout*)civUI)->GetLayout();
    if (layout == 0) return;

    void* w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab570, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag14 = (u8)(v >> 1) & 1;
        }
    }
    w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab571, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag15 = (u8)(v >> 1) & 1;
        }
    }
    w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab56f, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag17 = (u8)(v >> 1) & 1;
        }
    }
    w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab56e, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag16 = (u8)(v >> 1) & 1;
        }
    }
}

// =======================================================================
// 0x00ce96b0 - 249 bytes: show/hide the reticles and stop audio loops
// =======================================================================
// @ 0x00ce96b0
void CDS::SetReticlesVisible(u8 visible)
{
    if (mpTargetingReticle != 0) {
        void* p = mpTargetingReticle;
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)p + 0xc)))(p, visible != 0);
        p = mpTargetingReticle;
        mpTargetingReticle = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p + 4)))(p);
        }
    }
    if (mpExtraReticle != 0) {
        void* p = mpExtraReticle;
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)p + 0xc)))(p, visible != 0);
        p = mpExtraReticle;
        mpExtraReticle = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p + 4)))(p);
        }
    }
    if (mpErrorReticle != 0) {
        void* p = mpErrorReticle;
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)p + 0xc)))(p, visible != 0);
        p = mpErrorReticle;
        mpErrorReticle = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p + 4)))(p);
        }
    }
    int i;
    for (i = 0; i < 3; i++) {
        void* snd = mAudioSounds[i];
        void* sys = FUN_00a206f0();
        if (sys != 0) {
            ((void(__thiscall*)(void*, u32))(*(void**)(*(char**)sys + 0x38)))(sys, 0x347536b);
            ((void(__thiscall*)(void*, u32, void*))(*(void**)(*(char**)sys + 0x40)))(sys, 0x3475385, snd);
            ((void(__thiscall*)(void*, u32, int))(*(void**)(*(char**)sys + 0x40)))(sys, 0x34753a0, 1);
            ((void(__thiscall*)(void*))(*(void**)(*(char**)sys + 0x58)))(sys);
        }
    }
}

// =======================================================================
// 0x00ce97e0 - 318 bytes: shut down layout, effects and audio
// =======================================================================
// @ 0x00ce97e0
void CDS::ShutdownAll()
{
    int i;
    ((CSPUILayout*)mpPosseIconLayout)->Shutdown(1);
    void* layout = mpPosseIconLayout;
    if (layout != 0) {
        mpPosseIconLayout = 0;
        ((void(__thiscall*)(void*))(*(void**)(*(char**)layout + 8)))(layout);
    }
    EffectHandle* e;
    e = (EffectHandle*)mpSelEff0;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff1;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff2;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff3;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff4;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    SetReticlesVisible(1);
    for (i = 0; i < 3; i++) {
        void* snd = mAudioSounds[i];
        if (snd != 0) {
            void* sys = FUN_00a206f0();
            if (sys != 0) {
                ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sys + 0x2c)))(sys, snd);
            }
            mAudioSounds[i] = 0;
        }
    }
}

// =======================================================================
// 0x00ce9920 - 581 bytes: SP::cCityDisplayStrategy::HandleMessage
// =======================================================================
// @ 0x00ce9920
int CDS::HandleMessage(int msgID, void* msg)
{
    char* m = (char*)msg;
    void* key = *(void**)(m + 8);
    if (key == 0) return 1;

    if (msgID == 0x3deb129) {
        u8 bDone = 0;
        int idx = 0;
        char* anchor = (char*)this + 0x48;
        do {
            if (bDone) return 1;
            char* end = anchor;
            char* node = *(char**)(end + 4);
            while (node != end && !bDone) {
                if (*(void**)(node + 0x14) == key) {
                    MapValue* vel = *(MapValue**)(node + 0x10);
                    u32 flags = *(u32*)(m + 0x10);
                    void** vt = (void**)vel->mSub34.mpVtbl;
                    u8 b = ((u8(__thiscall*)(void*))vt[0x50 / 4])(&vel->mSub34);
                    u8 bNew = (u8)(flags & 1) != 0;
                    if (bNew) b = (b == 0);
                    bDone = bNew;
                    FUN_00ca3350(&vel->mSub34, bNew);
                    FUN_00bfc5e0(&vel->mField508, (u8)(flags & 2) != 0);
                    FUN_00c9e870(vel, flags);
                    void* cur = FUN_00b30d70();
                    ((void(__thiscall*)(void*))(*(void**)(*(char**)cur + 0x74)))(cur);
                    cur = FUN_00b30d70();
                    ((void(__thiscall*)(void*))(*(void**)(*(char**)cur + 0xc8)))(cur);
                    if (b != 0) {
                        FUN_00e05930(*(void**)((char*)this + 0x2c), -1);
                    }
                    FUN_00cf74d0();
                }
                node = (char*)FUN_00921580(node);
            }
            idx++;
            anchor += 0x1c;
        } while (idx < 4);
        return 1;
    }
    if (msgID == 0x3deb12a) {
        u8 bDone = 0;
        int idx = 0;
        char* anchor = (char*)this + 0x48;
        while (!bDone) {
            char* end = anchor;
            char* node = *(char**)(end + 4);
            for (; node != end; node = (char*)FUN_00921580(node)) {
                if (*(void**)(node + 0x14) == key) {
                    MapValue* vel = *(MapValue**)(node + 0x10);
                    bDone = 1;
                    void* cam = FUN_00b3d280();
                    FUN_00b10260(cam);
                    void** vt = (void**)vel->mSub34.mpVtbl;
                    void* p = ((void*(__thiscall*)(void*, int, int))vt[0x2c / 4])(&vel->mSub34, 1, 1);
                    void* cam2 = FUN_00b3d280();
                    FUN_00b146a0(cam2, (int)p, 1);
                    void* civ = FUN_00cf74c0();
                    FUN_00cf8d70(civ, (void*)0);
                }
            }
            idx++;
            anchor += 0x1c;
            if (idx >= 4) return 1;
        }
        return 1;
    }
    if (msgID == 0x61ed580 && key != 0) {
        cSPUIPosse** posses = (cSPUIPosse**)((char*)this + 0x34);
        int n = 4;
        do {
            cSPUIPosse* p = *posses;
            if (p != 0) {
                if (p == key && p->ItemCount() != (int)FUN_00e23250()) {
                    ((CIcon*)p)->RefreshAlt();
                } else {
                    ((CIcon*)p)->Refresh();
                }
            }
            posses++;
        } while (--n);
        return 1;
    }
    return 1;
}

// =======================================================================
// 0x00ce9b70 - 181 bytes: select the posse item for a vehicle and task it
// =======================================================================
// @ 0x00ce9b70
void CDS::SelectVehicle(void* vehicle, int flag, int param4)
{
    int i;
    for (i = 0; i < 4; i++) {
        char* anchor = (char*)this + 0x80 + i * 0x1c;
        RefPtr::AddRef(vehicle);
        char* parent = *(char**)(anchor + 8);
        char* best = anchor;
        while (parent != 0) {
            if (*(void**)(parent + 0x10) < vehicle) {
                parent = *(char**)(parent + 4);
            } else {
                best = parent;
                parent = *(char**)(parent);
            }
        }
        char* found = (best != anchor && *(void**)(best + 0x10) <= vehicle) ? best : anchor;
        RefPtr::Release(vehicle);
        if (found != anchor) {
            void* key = *(void**)(found + 0x14);
            void* item = ((CIcon*)mPosses[i])->FindItem(key);
            if (item != 0) {
                if (flag != 0) {
                    ((CIcon*)item)->SetEnabled((u8)param4);
                }
                SetVehicleTask((cGameData*)item, (cGameData*)vehicle);
                FUN_00ce8d00(item, vehicle, 0);
            }
            return;
        }
    }
}

// =======================================================================
// 0x00ce9c30 - 253 bytes: refresh the icons of a vehicle's posse
// =======================================================================
// @ 0x00ce9c30
void CDS::RefreshVehicleIcons(cGameData* vehicle)
{
    int idx = vehicle->mCivIndex;
    if (mPosses[idx] == 0) return;
    char* anchor = (char*)this + idx * 0x1c + 0x80;
    char* node = *(char**)(anchor + 4);
    cPlanetModel* pm;
    for (; node != anchor; node = (char*)FUN_00921580(node)) {
        cGameData* other = *(cGameData**)(node + 0x10);
        void* item = ((CIcon*)mPosses[idx])->FindItem(*(void**)(node + 0x14));
        if (other == 0 || item == 0) continue;
        if (other->mContinent != vehicle->mContinent) continue;
        pm = (cPlanetModel*)FUN_00b3d350();
        if (pm == 0) continue;
        if (other->mContinent == 0) {
            void* ka = ((void*(__thiscall*)(void*))(*(void**)(*(char**)vehicle + 0x2c)))((char*)vehicle + 0x34);
            void* cb = pm->GetContinent(ka);
            void* kb = ((void*(__thiscall*)(void*))(*(void**)(*(char**)other + 0x2c)))((char*)other + 0x34);
            void* cc = pm->GetContinent(kb);
            if (cc != cb) continue;
        }
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)item + 0xb8)))(item, 2);
    }
}

// =======================================================================
// 0x00ce9d30 - 231 bytes: update the icons by continent
// =======================================================================
// @ 0x00ce9d30
void CDS::UpdateVehicleContinent(cGameData* vehicle)
{
    cPlanetModel* pm = (cPlanetModel*)FUN_00b3d350();
    if (pm == 0) return;
    void* cont = pm->GetContinent(vehicle);
    u8 flag = *(u8*)((char*)cont + pm->mContinentFlags);

    int idx;
    for (idx = 0; idx < 4; idx++) {
        cSPUIPosse* posse = mPosses[idx];
        if (posse == 0) continue;
        char* anchor = (char*)this + 0x80 + idx * 0x1c;
        char* node = *(char**)(anchor + 4);
        for (; node != anchor; node = (char*)FUN_00921580(node)) {
            cGameData* other = *(cGameData**)(node + 0x10);
            void* item = ((CIcon*)posse)->FindItem(*(void**)(node + 0x14));
            if (other == 0 || item == 0) continue;
            u32 u = other->mContinent;
            if (u != 2) {
                if (u != (flag == 0)) continue;
                if (u != 2) {
                    void* kb = ((void*(__thiscall*)(void*))(*(void**)(*(char**)other + 0x2c)))((char*)other + 0x34);
                    void* cc = pm->GetContinent(kb);
                    if (cc != cont) continue;
                }
            }
            ((void(__thiscall*)(void*, int))(*(void**)(*(char**)item + 0xb8)))(item, 2);
        }
    }
}

// =======================================================================
// 0x00ce9e20 - 519 bytes: build the selection-effect description
// =======================================================================
// The effect object this method targets (self), and the descriptor the
// effect system's factory fills in.
struct EffectTarget {
    void* mpVtbl;     // +0x00
    void* mField4;    // +0x04
    u8    mField8;    // +0x08
    char  pad09[0xc - 9];
    u32   mColor;     // +0x0c
    int   mType;      // +0x10
    int   mVariant;   // +0x14
};
struct EffectDesc {
    u32   mId;        // +0x00
    u32   mField4;    // +0x04
    u8    mbField8;   // +0x08
    char  pad09[0xc - 9];
    u8    mbFlagC;    // +0x0c
    u8    mbFlagD;    // +0x0d
    u8    mbFlagE;    // +0x0e
    u8    mbFlagF;    // +0x0f
    float mFloat10;   // +0x10
    u32   mField14;   // +0x14
    u32   mField18;   // +0x18
    u32   mField1c;   // +0x1c
};
// @ 0x00ce9e20
void CDS::BuildEffectDesc(int type, int variant)
{
    EffectTarget* self = (EffectTarget*)this;
    void* mgr = FUN_0067ddd0();
    void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
    void* fx = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);

    EffectDesc desc;
    desc.mbField8 = 0;
    desc.mField18 = 0xffffffff;
    desc.mField1c = 0xffffffff;
    self->mVariant = variant;
    desc.mbFlagF = 0;
    desc.mFloat10 = 0.0f;
    if (type == 2) {
        desc.mId = 0x784c7cc8;
    } else {
        desc.mId = 0xd21f4398;
        if (variant != 0) desc.mId = 0x748de859;
    }
    desc.mbFlagD = (type == 1);
    desc.mField4 = 0;
    desc.mbFlagC = 0;
    desc.mbFlagE = 3;
    ((void(__thiscall*)(void*, EffectTarget*, EffectDesc*, void*))
     (*(void**)(*(char**)fx + 0x18)))(fx, self, &desc, &self->mField4);
    ((void(__thiscall*)(void*, void*, u8))
     (*(void**)(*(char**)fx + 0x10)))(fx, &self->mField8, desc.mbField8);
    desc.mField14 = 0;
    desc.mField18 = 0;
    desc.mField1c = 0;
    void* c = FUN_00ca10a0();
    float fArg = (type == 1) ? 0.5f : 1.0f;
    ((void(__thiscall*)(void*, void*, void*, float))
     (*(void**)(*(char**)fx + 0x20)))(fx, &self->mField4, c, fArg);
    ((void(__thiscall*)(void*, void*, int))
     (*(void**)(*(char**)fx + 0x24)))(fx, &self->mField4, 1);

    float f = (type == 1) ? 0.5f : 1.0f;
    float fv = (f >= 0.0f) ? f : 0.0f;
    float fscaled = fv * 255.0f;
    if (fscaled > 255.0f) fscaled = 255.0f;
    u32 alpha = (u32)(int)fscaled;
    self->mColor = ((alpha & 0xff) << 24) | (0xff << 16) | (0xf2 << 8) | 0x99;
    self->mType = type;
}

// =======================================================================
// 0x00cea030 - 83 bytes: allocate a 0x18 object and copy two refcounts
// =======================================================================
// @ 0x00cea030
void* __fastcall FUN_00cea030(void* unused1, void* unused2, void** src)
{
    (void)unused1; (void)unused2;
    char* obj = (char*)FUN_00f473a0(0x18, "Simulator", 0, 0, "c:\\BuildAgent", 0xd1);
    char* base = obj + 0x10;
    if (base != 0) {
        void* p0 = src[0];
        ((void**)base)[0] = p0;
        if (p0 != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p0)))(p0);
        }
        void* p1 = src[1];
        ((void**)base)[1] = p1;
        if (p1 != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p1)))(p1);
        }
    }
    return obj;
}
