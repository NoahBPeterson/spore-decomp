// Slice s00cf9ba0 -- SP::cCivModeStrategy civ-mode tutorial / event cluster
// (0x00cf9ba0..0x00cfaab0, 9 functions).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Relocations are masked by the matcher, so free helpers reached by absolute
// address are declared with exactly the argument count observed at each call
// site; symbol identity/mangling does not affect byte matching.  Calls shaped
// `push <args>; mov ecx, <obj>; call X` are modeled as __thiscall members of
// the object's class; calls shaped `mov ecx, <obj>; call X` (no stack args)
// are __thiscall 0-arg members.

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;

#define VTFN(p, slot)  ((*(void***)(p))[slot])

typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef int   (__thiscall* TFnII)(void*, int);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TFnPIV)(void*, int, void*);
typedef void* (__thiscall* TFnPUP)(void*, unsigned, int, void*);
typedef int   (__thiscall* TFnIP)(void*, void*);
typedef void  (__thiscall* TFnVFF)(void*, float, float);
typedef void* (__thiscall* TFnPU)(void*);

// ---------------------------------------------------------------------------
// Strategy object: SP::cCivModeStrategy.  Its own methods, called with `this`
// in ECX.
struct Civ;
struct Strat {
    char  __thiscall HasCivTutorialOccurred(int id);   // 0x00cf7830
    void  __thiscall MarkCivEventAsOccurred(int id);   // 0x00cf77f0
    int   __thiscall HasOccurred();                    // 0x00cf94b0
    void  __thiscall StartTechHint();                  // 0x00cf93b0
    int   __thiscall UpdateHintFlags();                // 0x00cfa120
    void  __thiscall CheckEvents();                    // 0x00cf9ba0
    void  __thiscall DoNext(int id, char rerun);       // 0x00cfa990
    void  __thiscall SignalCivEvent(int, float, float, int); // 0x00cfaab0 (ret 0x14)
    void  __thiscall PreGameModeTransition(int oldMode, int newMode); // 0x00cfa610 (ret 8)
    void* __thiscall GetLaunchMarker(int);             // 0x00cf7d40

    // Retail object layout (the dev PDB's cCivModeStrategy is the smaller
    // single-player variant, so names are by role).
    char  pad0[0x68];
    int   mCityInput;                                  // +0x68
    char  pad1[0x74];                                  // +0x6c
    int   miState_0xe0;                                // +0xe0
    void* mpEditor_0xe4;                               // +0xe4
    void* mpHintTarget_0xe8;                           // +0xe8
    void* mpSomething_0xec;                            // +0xec
    void* mpMode_0xf4;                                 // +0xf4 (result slot)
    char  pad2[0x0c];                                  // +0xf8
    void* mpUndo_0x104;                                // +0x104
    void* mpEditable_0x108;                            // +0x108
    void* mpPreloadA_0x10c;                            // +0x10c
    void* mpPreloadB_0x110;                            // +0x110
    char  pad3[0x0e];                                  // +0x114
    char  mbHintC_0x122;                               // +0x122
    char  mbHintB_0x123;                               // +0x123
    char  mbHintA_0x124;                               // +0x124
    char  mbHint0_0x125;                               // +0x125
    char  pad4[0x22];                                  // +0x126
    char  mbFirstCivEvent_0x148;                       // +0x148
};

// Civilization helper field accessors (all __thiscall on the civ pointer).
struct Civ {
    int   __thiscall HasSpecialtyCity();        // 0x00bf0260  find_specialty_city
    int   __thiscall TechLevelRank();           // 0x00bf0f40
    int   __thiscall RefAtB0();                 // 0x00befab0
    void* __thiscall KeyLookup(int);            // 0x00bef980
    char  __thiscall HasFlag(void*);            // 0x00bef970
    void  __thiscall DoThing();                 // 0x00bdc4a0

    char  padC[0x40];                           // +0x00
    int   miField_0x40;                         // +0x40 (id copied to empire)
    char  pad0[0x298 - 0x44];
    int   miNumCityLevels_0x298;                // +0x298 (tech-level gate)
    int   mPad_0x29c_cityLevel;                 // +0x29c (copied from city)
    char  pad1[0x1ac];                          // +0x2a0
    void* mpCity_0x44c;                         // +0x44c
    char  pad2[0x6c];                           // +0x450
    int   miHintThreshold_0x4bc;                // +0x4bc
};

// City object hanging off the civ (+0x44c).
struct City {
    int   __thiscall GetSpecialty();            // 0x00bd81d0
    void  __thiscall Rebuild();                 // 0x00bd91e0
    char  pad0[0x29c];
    int   miState_0x29c;                        // +0x29c
};

// Noun-manager helpers.
struct Noun {
    Civ*  __thiscall GetPlayerCivilization();        // 0x00b25fb0
    void  __thiscall RemoveNounsOfType(int);         // 0x00b22650
    void* __thiscall GetCurrentTerrainSphere();      // 0x00f67d90
    void  __thiscall PreShutdown();                  // 0x00b25ee0
    void  __thiscall PostShutdown();                 // 0x00b25fe0
    void  __thiscall ProcessPending();               // 0x00b22960
};

// Game time manager.
struct GTM {
    void  __thiscall IncPauseGate(int);              // 0x00b32220
    void  __thiscall DecPauseGate(int);              // 0x00b32250
};

// Config manager.  GetFlag lives at vtable slot 0x30/4 == 12.
struct Cfg {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual int  GetFlag(unsigned int);          // slot 0x30
};

// The object produced by FUN_00d004b0 (a gameplay-manager-ish noun) and used
// as `mov ecx, ebx` for the hint helpers.
struct HintObj {
    void  __thiscall Hint(int);                      // 0x00b706a0
    void  __thiscall HintClear(int);                 // 0x00b707a0
};

// Terrain-sphere object (noun manager's sphere) used for the tech-hint query.
struct Sphere {
    char  __thiscall Query(int);                     // 0x00c772c0
};

// Object producing player civ with an int arg (0x00b25c30) then 0x00bdc4a0.
struct NounByIndex {
    void* __thiscall GetCivilization(int);           // 0x00b25c30
};
struct Civ2 {
    void  __thiscall DoThing();                      // 0x00bdc4a0 (this in ecx)
    int   __thiscall SpecialCity();                  // 0x00bf0260
};

// Effects manager (vtable slot 0x2c = Query3).
struct Effects {
    void __thiscall Query3(unsigned, void*, void*);  // slot 0x2c
};

// Trigger manager: built from a never-NULL singleton accessor.
struct TriggerMgr {
    int  __thiscall PostAction(int id, void* target, int a);           // 0x00ae09b0
    void __thiscall PostTrigger(const char* name, int a, int b,
                                int c, int d, int e);                  // 0x00ae0930
};

// Action target guard object built around the gameplay-marker object.
struct ActionTarget {
    ActionTarget(void*);                       // 0x00ad7a30
    ~ActionTarget();                           // 0x00ad7ad0
    int pad0;
    int pad1;
};

// "Today"/stats singleton used for the city-count check in CheckEvents.
struct DayStats {
    char pad0[0xac];
    int  miCountAC;                            // +0xac
    int  miCountB0;                            // +0xb0
    void __thiscall SysGui();                  // 0x00c2e4e0
};

// MessageBasicRC<5>-shaped local notification sent on the transition out of
// city mode.  Only the slots the original touches are named.
struct Msg5 {
    void*   mpVtbl;                            // +0x00
    int     miRef;                             // +0x04
    int     mPad[10];                          // +0x08
    unsigned int mData2;                       // +0x30
    int     mPad2;
    unsigned int mData3;                       // +0x38
    void __thiscall Destruct();                // 0x00421cf0
};

// Messaging server, vtable slot 0x14 = PostMessage.
struct MsgServer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04();
    virtual void Post(unsigned, void*, int);
};

// Camera controller: secondary methods used on launch-screen init.
struct CamCtl {
    void __thiscall LookAt(void* a, void* b, int c);   // 0x00b12dd0
    void __thiscall F1(float, float, float);           // 0x00b10340
    void __thiscall F2(float, float, float);           // 0x00b10540
};

// Planet / universe object with a secondary base at +0x04.
struct SecBase {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05();
    virtual void SetKey(int, void*);                   // slot 0x18
};
struct PlanetObj {
    char    pad0[4];
    SecBase base1;                                     // +0x04
};

// Universe object (0x01021260) queried for the active planet.
struct Universe {
    void* __thiscall GetPlanet(int, int);              // 0x00c713e0
    void  __thiscall Erase9(int);                      // 0x00c71560
    void  __thiscall EraseKeyBC();                     // 0x00c73310
    void  __thiscall EraseKeyD0();                     // 0x00c73330
};

// Property manager (vtable slot 0x2c = property test).
struct PropMgr {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10();
    virtual char Test(void*);                          // slot 0x2c
};

// Star manager used to clear the old star's planet.
struct StarMgr {
    void* __thiscall Find(void* planet, int zero);      // 0x00bb5990
};

// Behavior manager (vtable slot 0x30).
struct BehaviorMgr {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
    virtual void Clear();                              // slot 0x30
};

// Terrain cursor (vtable slot 0x58).
struct TerrainCursor {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21();
    virtual void Set(int);                             // slot 0x58
};

// Species profile.
struct SpeciesProfile {
    void __thiscall GetUiName(void*);                  // 0x004da330
};

// The "editor" object at +0xe4 of the strategy: vtable 0/4/8 methods.
struct ModeSub {
    virtual void m00(); virtual void m01(); virtual void m02();
    void __thiscall Fn0ed0();                          // 0x00cf0ed0
};

// Community editor (at +0x80 of the editor object).
struct CommunityEditor {
    char __thiscall IsActive();                        // 0x00d09660
    int  __thiscall GetResult();                       // 0x00d09670
    void __thiscall Deactivate(int, int);              // 0x00d100b0
};

// Small ref-counted cache object (+0x108 of the strategy).
struct C20 {
    void __thiscall Clear();                           // 0x007b1950
};

// Launch-screen editor object reached through 0x01021230.
struct EditObj {
    int   __thiscall Active();                         // 0x00c8b370 (0 args)
    void* __thiscall Lookup(unsigned int, void**);     // 0x00c8b370 (key, out)
};

// Planet model.
struct PM {
    void __thiscall SetPlanet(void*);                  // 0x00b8d8a0
};

// Hint target object at +0xe8 of the strategy.
struct HintTarget {
    void __thiscall Reset(int);                        // 0x00ce8ee0
    void __thiscall Prep();                            // 0x00ce97e0
};

// Texture preload object (+0x10c/+0x110 of the strategy).
struct Preload {
    void __thiscall Free();                            // 0x007cfc60
};

// eastl::rbtree node search helper.
struct RTree {
    void* __thiscall Find(unsigned int* key, void** out); // 0x00e5c780
};

// Vehicle tree returned by 0x00c9efc0.
struct VehicleTree {
    void __thiscall Fn7540();                          // 0x00dc7540
};

// Sub-object at (this - 4) torn down on mode exit.
struct Sub4 {
    void __thiscall Fn86d0();                          // 0x00cf86d0
};

// Input state at +0x68 of the strategy.
struct InputState {
    void __thiscall OnMouseWheel(int, float, float, int); // 0x00697b40
};

// eastl wide string (begin/end/capacity).
struct WStr {
    unsigned short* mpBegin;
    unsigned short* mpEnd;
    unsigned short* mpCapacity;
    void __thiscall Assign(void*);                     // 0x00b6f380
    void __thiscall Append(const unsigned short*);     // 0x005c3d90
};

// ---------------------------------------------------------------------------
// Free accessors / helpers reachable by absolute address.
extern "C" {
    void* __cdecl SP_GetCurrentGameMode();          // 0x00b5b800
    void* __cdecl SP_ConfigManager();               // 0x0067dd30
    void* __cdecl SP_GameTimeManager();             // 0x00b3d380
    void* __cdecl SP_NounManager();                 // 0x00b3d300
    void* __cdecl SP_EffectsManager();              // 0x0067ddd0
    void* __cdecl SP_PropertyManager();             // 0x0067de30
    void* __cdecl SP_BehaviorManager();             // 0x00b3d260
    void* __cdecl SP_PlanetModel();                 // 0x00b3d350
    void* __cdecl SP_TerraformingManager();         // 0x00b3d430
    void* __cdecl SP_GetGameTerrainCursor();        // 0x00b30d70
    void* __cdecl SP_GetCameraCtl();                // 0x00b3d280
    void* __cdecl SP_StarManager();                 // 0x00b3d2a0
    void* __cdecl SP_GameInputManager();            // 0x00b3d250
    void* __cdecl SP_00b3d3b0();                    // 0x00b3d3b0
    void* __cdecl SP_00b3d2b0();                    // 0x00b3d2b0
    void* __cdecl SP_0067ddc0();                    // 0x0067ddc0
    void* __cdecl SP_00c9efc0();                    // 0x00c9efc0
    void* __cdecl SP_01021260();                    // 0x01021260
    void* __cdecl SP_01021300();                    // 0x01021300
    void* __cdecl SP_EA_Messaging();                // 0x00883860
    void* __cdecl SP_0067cac0();                    // 0x0067cac0 (0 args)

    int   __cdecl FUN_00d004b0();                   // 0x00d004b0
    int   __cdecl FUN_00cf6e30();                   // 0x00cf6e30 (no arg)
    void* __cdecl FUN_00cf6e30_1(int);              // 0x00cf6e30 (1 arg)
    void* __cdecl FUN_00cf7d40_1(int);              // 0x00cf7d40 (1 arg)
    void* __cdecl FUN_00b18e00(void*);              // 0x00b18e00
    void* __stdcall FUN_00b3d4f0_1(int);            // 0x00b3d4f0 (1 arg, callee-cleans)
    int   __cdecl SP_01021230();                    // 0x01021230
    void* __cdecl SP_00c713e0(int, int);            // 0x00c713e0
    int   __cdecl FUN_00c8b370_0();                 // 0x00c8b370 (no arg)
    void* __cdecl FUN_00c8b370_2(int, void**);      // 0x00c8b370 (obj + out)
    void  __cdecl FUN_00ba1c60(void*);              // 0x00ba1c60
    void  __cdecl FUN_00b6c280();                   // 0x00b6c280
    void  __cdecl FUN_01002ee0();                   // 0x01002ee0
    void* __cdecl FUN_00c30c80();                   // 0x00c30c80
    int   __cdecl SP_GetPropertyAsUint32(void*, unsigned, void**); // 0x004af210
    void  __cdecl FUN_00d1c610(int, int);           // 0x00d1c610 (obj, int)
    void  __cdecl FUN_00b12dd0(int, int, int);      // 0x00b12dd0
    void  __cdecl FUN_00b10340(void*, float, float); // 0x00b10340 (this, f, f)
    void  __cdecl FUN_00b10540(void*, float, float); // 0x00b10540
    void  __cdecl FUN_00b8d8a0(void*, int, int);    // 0x00b8d8a0
    void* __cdecl FUN_00bb5990(void*, void*, int);  // 0x00bb5990
    void  __cdecl FUN_00c71560(void*, int);         // 0x00c71560
    void  __cdecl FUN_00c73310(void*);              // 0x00c73310
    void  __cdecl FUN_00c73330(void*);              // 0x00c73330
    void  __cdecl FUN_00cfeac0();                   // 0x00cfeac0
    void  __cdecl FUN_00c9a080();                   // 0x00c9a080
    void  __cdecl FUN_01021230v();                  // placeholder
    void  __cdecl FUN_00bd91e0(void*);              // 0x00bd91e0
    int   __cdecl FUN_00bd81d0(void*);              // 0x00bd81d0
    void  __cdecl operator_delete__(void*);         // 0x00f47380
    void  __cdecl FUN_00d09660c(void*);             // 0x00d09660 (char)
    int   __cdecl FUN_00d09670(void*);              // 0x00d09670
    int   __cdecl FUN_00697b40(void*, int, float, float, int); // 0x00697b40 (unused)
    void* __cdecl SP_0067caf0(float,float,float,void*,int,float,float,float,int,int); // 0x0067caf0
}

struct V3 { float x, y, z; };

// UIHints object returned by FUN_0067cac0 (vtable-driven hint display).
struct UIHints {
    void __thiscall Show(int);                    // 0x0067c830
    void __thiscall Show2(int, int);              // 0x0067c8c0
    void __thiscall Apply();                      // 0x0067aaf0
};

// Generic subobject reached through a returned pointer; `Rel()` is 0x00e2f270.
struct SubObj {
    int  __thiscall Rel();                        // 0x00e2f270
};

// Checker object at +0x80 of the editor object.
struct Checker {
    char  __thiscall Check();                     // 0x00d09660
};

// Game input manager; slot 0x60 handles a signal(int,float,float,int).
struct GameInput {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void Signal(int, float, float, int);  // slot 0x60
};

static int CivFlag(void* civ, int key) {
    Civ* c = (Civ*)civ;
    return c->HasFlag(c->KeyLookup(key));
}

extern "C" {
    unsigned char DAT_0169d2bc;                       // 0x0169d2bc
    unsigned char DAT_0169d2cc;                       // 0x0169d2cc
    unsigned char DAT_015819b4;                       // 0x015819b4
    unsigned char DAT_01654c04;                       // 0x01654c04 game-mode tag
    unsigned char DAT_01654c05;                       // 0x01654c05
    unsigned char DAT_01654c06;                       // 0x01654c06
    unsigned char DAT_01654c08;                       // 0x01654c08
    unsigned char DAT_01667bac;                       // 0x01667bac
    unsigned char DAT_01667bae;                       // 0x01667bae
    unsigned char DAT_018c6de8;                       // 0x018c6de8
    unsigned char DAT_018c6d19;                       // 0x018c6d19
    unsigned char DAT_018c43e8;                       // 0x018c43e8
    unsigned char DAT_01581b54;                       // 0x01581b54
    unsigned char DAT_01581b58;                       // 0x01581b58
    unsigned char DAT_01581b5c;                       // 0x01581b5c
    unsigned char DAT_01581b78;                       // 0x01581b78
    unsigned char DAT_01581b7c;                       // 0x01581b7c
    unsigned char DAT_01581b80;                       // 0x01581b80
    unsigned char PTR_01581bd0;                       // 0x01581bd0
    unsigned char PTR_01581bd4;                       // 0x01581bd4

    TriggerMgr* __cdecl GetTriggerMgr();               // 0x00b3d4d0
    Noun* __cdecl SP_NounManager1(int);                // 0x00b3d300 (with arg)
    DayStats* __cdecl FUN_00b26930();                  // 0x00b26930
    void  __cdecl FUN_00401090();                      // 0x00401090
}

// ===========================================================================
// @ 0x00cf9ba0
// SP::cCivModeStrategy::CheckEvents -- civ-mode tutorial event state machine.
void Strat::CheckEvents()
{
    if ((void*)SP_GetCurrentGameMode() != (void*)0x01654c04)
        return;
    HintObj* obj = (HintObj*)FUN_00d004b0();
    if (obj == 0)
        return;
    if (((Cfg*)SP_ConfigManager())->GetFlag(0x4ea96cb) == 0)
        return;
    if (this->HasOccurred())
        return;

    if (!this->HasCivTutorialOccurred(0x64e666f)) {
        if (!this->HasCivTutorialOccurred(0x64e6666)) {
            this->mbFirstCivEvent_0x148 = 1;
            this->MarkCivEventAsOccurred(0x64e6666);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(FUN_00cf6e30());
        return;
    }
    if (!this->HasCivTutorialOccurred(0x64e6673)) {
        if (!this->HasCivTutorialOccurred(0x64e6671)) {
            this->MarkCivEventAsOccurred(0x64e6671);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(0x5f011813);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x64e6676)) {
        if (!this->HasCivTutorialOccurred(0x64e6674)) {
            this->MarkCivEventAsOccurred(0x64e6674);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(0xdb5f195a);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x64e6679)) {
        if (!this->HasCivTutorialOccurred(0x64e6678)) {
            this->MarkCivEventAsOccurred(0x64e6678);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(0x90382acc);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x65cbcb4)) {
        this->MarkCivEventAsOccurred(0x65cbcb4);
        this->mbFirstCivEvent_0x148 = 0;
        void* marker = this->GetLaunchMarker(0);
        if (marker == 0)
            return;
        {
            ActionTarget target(FUN_00b18e00(marker));
            GetTriggerMgr()->PostAction(0x9e430ff6, &target, 0);
            GetTriggerMgr()->PostTrigger("CVG_SendVehicleToCommodity", 1, 0, 0, 0, 0);
        }
        return;
    }
    if (!this->HasCivTutorialOccurred(0x308f4ce8)) {
        obj->Hint(0x308f4ce8);
        if (!this->HasCivTutorialOccurred(0x6302c60)) {
            this->MarkCivEventAsOccurred(0x6302c60);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x4bf38a7);
            V3 v = { *(float*)&DAT_01581b78, *(float*)&DAT_01581b7c, *(float*)&DAT_01581b80 };
            ((UIHints*)SP_0067caf0(v.x, v.y, v.z, &PTR_01581bd4, 0,
                                   -1.0f, -1.0f, 0.0f, 0, 0))->Apply();
        }
        return;
    }
    if (!this->HasCivTutorialOccurred(0x34646619)) {
        obj->Hint(0x34646619);
        if (!this->HasCivTutorialOccurred(0x654da12)) {
            this->MarkCivEventAsOccurred(0x654da12);
            ((Noun*)SP_NounManager1(1))->GetPlayerCivilization()->DoThing();
        }
        if (!this->HasCivTutorialOccurred(0x65509c9)) {
            this->MarkCivEventAsOccurred(0x65509c9);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x4bf38a7);
            V3 v = { *(float*)&DAT_01581b54, *(float*)&DAT_01581b58, *(float*)&DAT_01581b5c };
            ((UIHints*)SP_0067caf0(v.x, v.y, v.z, &PTR_01581bd0, 0,
                                   -1.0f, -1.0f, 0.0f, 0, 0))->Apply();
        }
        return;
    }
    if (!this->HasCivTutorialOccurred(0xbb7368ed)) {
        obj->Hint(0xbb7368ed);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x6d3814ed)) {
        Civ* civ = ((Noun*)SP_NounManager1(1))->GetPlayerCivilization();
        if (civ->HasSpecialtyCity() > 0) {
            obj->Hint(0x6d3814ed);
            return;
        }
    }
    if (!this->HasCivTutorialOccurred(0xced8b9d4)) {
        Civ* civ = ((Noun*)SP_NounManager1(2))->GetPlayerCivilization();
        if (civ->HasSpecialtyCity() > 0) {
            obj->Hint(0xced8b9d4);
            return;
        }
    }
    int diff = FUN_00b26930()->miCountAC - FUN_00b26930()->miCountB0;
    int rank = ((Noun*)SP_NounManager())->GetPlayerCivilization()->TechLevelRank();
    switch (rank) {
    case 0:
        if (!this->HasCivTutorialOccurred(0xe9b77b0b)) {
            if (diff < 2)
                return;
            obj->Hint(0xe9b77b0b);
            return;
        }
        break;
    case 1:
        if (!this->HasCivTutorialOccurred(0x92a23f21)) {
            if (diff < 2)
                return;
            obj->Hint(0x92a23f21);
            return;
        }
        break;
    case 2:
        if (!this->HasCivTutorialOccurred(0x9a2cac7f)) {
            if (diff < 2)
                return;
            obj->Hint(0x9a2cac7f);
            return;
        }
        break;
    default:
        return;
    }
    if (!this->HasCivTutorialOccurred(0x3120767d))
        obj->Hint(0x3120767d);
}

// ===========================================================================
// @ 0x00cfa0c0
// SP::cCivModeStrategy::StartTechLevelUpgradeHintIfAppropriate
char __fastcall FUN_00cfa0c0(void* self)
{
    char result = 0;
    Sphere* terrain = (Sphere*)((Noun*)SP_NounManager())->GetCurrentTerrainSphere();
    Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
    bool canUpgrade = false;
    if (civ != 0)
        canUpgrade = civ->miNumCityLevels_0x298 >= 3;
    if (canUpgrade) {
        if (terrain->Query(0x50a2e65) == 0) {
            ((Strat*)self)->StartTechHint();
            result = 1;
        }
    }
    return result;
}


// ===========================================================================
// @ 0x00cfa120
// SP::cCivModeStrategy::UpdateHintFlags
int __fastcall FUN_00cfa120(void* self)
{
    Noun* nm = (Noun*)SP_NounManager();
    Civ* civ = nm->GetPlayerCivilization();
    int thr = *(int*)((char*)civ + 0x4bc);
    if (civ->RefAtB0() <= thr)
        return 0;

    int* local = 0;
    int* eff = (int*)SP_EffectsManager();
    if (local) {
        int* t = local;
        local = 0;
        ((TFnV)VTFN(t, 1))(t);
    }
    (*(TFnPUP)VTFN(eff, 0x2c / 4))(eff, 0x9abfe031, 0, (void*)&local);    if (local) {
        int* lp = local;
        ((TFnVI)VTFN(lp, 2))(lp, 0);
    }
    char result = 1;
    if (*(int*)((char*)*(void**)((char*)self + 0xec) + 0x64) != 0) {
        if (CivFlag(civ, 0x36213c6a) || CivFlag(civ, 0x81299805) || CivFlag(civ, 0xfc716a94)) {
            *(char*)((char*)self + 0x125) = 1;
        } else if (CivFlag(civ, 0x008226d0) || CivFlag(civ, 0xfd05ab6d) || CivFlag(civ, 0x08a91f1e)) {
            *(char*)((char*)self + 0x124) = 1;
        } else if (CivFlag(civ, 0x2cdbd6a1) || CivFlag(civ, 0x4a78672c) || CivFlag(civ, 0x3221e759)) {
            *(char*)((char*)self + 0x123) = 1;
        } else if (CivFlag(civ, 0x0756d422) || CivFlag(civ, 0x045cdf1a) || CivFlag(civ, 0xc0617b2f)) {
            *(char*)((char*)self + 0x122) = 1;
        }
    }
    if (local) {
        int* lp = local;
        ((TFnV)VTFN(lp, 1))(lp);
    }
    return result;
}

// ===========================================================================
// @ 0x00cfa360
void __cdecl FUN_00cfa360()
{
    GTM* gtm = (GTM*)SP_GameTimeManager();
    gtm->DecPauseGate(0x4bf38a7);
    Cfg* cfg = (Cfg*)SP_ConfigManager();
    if (cfg->GetFlag(0x4ea96cb) != 0) {
        ((Strat*)*(void**)0x0169d2c8)->CheckEvents();
        return;
    }
    void* sm = FUN_00b3d4f0_1(0);
    ((SubObj*)sm)->Rel();
}

// ===========================================================================
// @ 0x00cfa3b0
void __cdecl FUN_00cfa3b0()
{
    GTM* gtm = (GTM*)SP_GameTimeManager();
    gtm->DecPauseGate(0x4bf38a7);
    Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
    City* city = (City*)civ->mpCity_0x44c;
    int spec = city->GetSpecialty();
    int state = city->miState_0x29c;
    bool keep = (state != 0 || spec == 0) && (state != 1 || spec == 1) &&
                (state != 2 || spec == 2);
    if (keep) {
        ((Strat*)*(void**)0x0169d2c8)->UpdateHintFlags();
        return;
    }
    city->Rebuild();
}

// ===========================================================================
// @ 0x00cfa990
// SP::cCivModeStrategy::DoNextCivTutorial
void Strat::DoNext(int id, char rerun)
{
    if ((void*)SP_GetCurrentGameMode() != (void*)0x01654c04)
        return;
    Strat* s = this;
    if (s->HasCivTutorialOccurred(id))
        return;
    HintObj* obj = (HintObj*)FUN_00d004b0();
    if (obj == 0)
        return;

    switch (id) {
    case 0x64e666f: {
        ((UIHints*)SP_0067cac0())->Show2(FUN_00cf6e30(), 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e6673: {
        ((UIHints*)SP_0067cac0())->Show2(0x5f011813, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e6676: {
        ((UIHints*)SP_0067cac0())->Show2(0xdb5f195a, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e6679: {
        ((UIHints*)SP_0067cac0())->Show2(0x90382acc, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e667d: {
        ((UIHints*)SP_0067cac0())->Show2(0x178f5417, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        ((SubObj*)FUN_00b3d4f0_1(0))->Rel();
        break;
    }
    default:
        obj->Hint(id);
        obj->HintClear(id);
        break;
    }
    s->MarkCivEventAsOccurred(id);
    if (rerun)
        this->CheckEvents();
}

// ===========================================================================
// @ 0x00cfaab0
// SP::cCivModeStrategy::SignalCivEvent
void Strat::SignalCivEvent(int a, float b, float c, int d)
{
    ((InputState*)((char*)this + 0x68))->OnMouseWheel(a, b, c, d);
    void* e = *(void**)((char*)this + 0xe8);
    if (e != 0) {
        if (((CommunityEditor*)*(void**)((char*)e + 0x80))->IsActive() == 0) {
            Strat* s = this;
            if (s->HasCivTutorialOccurred(0x64e6674)) {
                if ((void*)SP_GetCurrentGameMode() == (void*)0x01654c04) {
                    if (!s->HasCivTutorialOccurred(0x64e6676)) {
                        if (FUN_00d004b0() != 0) {
                            ((UIHints*)SP_0067cac0())->Show2(0xdb5f195a, 1);
                            GTM* gtm = (GTM*)SP_GameTimeManager();
                            gtm->DecPauseGate(0x64beb65);
                            s->MarkCivEventAsOccurred(0x64e6676);
                            s->CheckEvents();
                        }
                    }
                }
            }
        }
    }
    void* gim = SP_GameInputManager();
    ((GameInput*)gim)->Signal(a, b, c, d);
}

// ===========================================================================
// @ 0x00cfa610
// SP::cCivModeStrategy::PreGameModeTransition
void Strat::PreGameModeTransition(int oldMode, int newMode)
{
    if (((TFnPU)VTFN(this, 0x1c / 4))(this) == (void*)newMode)
        return;
    ((TFnVI)VTFN(this, 0x40 / 4))(this, newMode);

    if ((void*)oldMode != (void*)0x01654c04) {
        if ((void*)newMode == (void*)0x01654c04 && (void*)oldMode != (void*)0x00dbdba1)
            FUN_01002ee0();
        ((TFnV)VTFN(this, 0x48 / 4))(this);
        return;
    }

    void* eff = SP_EffectsManager();
    ((TFnVII)VTFN(eff, 0x98 / 4))(eff, 0xb, 0);
    FUN_00b6c280();
    this->miState_0xe0 = -1;

    if ((void*)newMode == (void*)0x01654c08) {
        void* p = SP_00b3d2b0();
        ((TFnV)VTFN(p, 0x5c / 4))(p);
        ((DayStats*)FUN_00b26930())->SysGui();    } else if ((void*)newMode == (void*)0x01654c06 || (void*)newMode == (void*)0x00dbdba1) {
        goto afterTeardown;
    }

    if (this->mpEditable_0x108) {
        ((C20*)this->mpEditable_0x108)->Clear();
        if (this->mpEditable_0x108) {
            void* p = this->mpEditable_0x108;
            this->mpEditable_0x108 = 0;
            ((TFnV)VTFN(p, 1))(p);
        }
    }
    ((Preload*)this->mpPreloadA_0x10c)->Free();
    ((Preload*)this->mpPreloadB_0x110)->Free();
    FUN_00cfeac0();
    ((BehaviorMgr*)SP_BehaviorManager())->Clear();
    ((VehicleTree*)SP_00c9efc0())->Fn7540();
    ((Sub4*)((char*)this - 4))->Fn86d0();

afterTeardown:
    if ((void*)newMode == (void*)0x01654c05) {
        void* cur = SP_GetGameTerrainCursor();
        ((TFnVI)VTFN(cur, 0x58 / 4))(cur, 0);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6de8);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6d19);
        void* empire = SP_01021300();
        Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
        *(int*)((char*)empire + 0x10) = civ->miField_0x40;
        WStr name;
        name.mpBegin = name.mpEnd = (unsigned short*)&DAT_01667bac;
        name.mpCapacity = (unsigned short*)&DAT_01667bae;
        ((SpeciesProfile*)FUN_00c30c80())->GetUiName(&name);
        ((WStr*)((char*)empire + 0xc))->Assign(&name);
        unsigned int key = 2;
        void* out = 0;
        void* node = ((RTree*)((char*)empire + 0x14))->Find(&key, &out);
        ((WStr*)((char*)empire + 0x3c))->Append(*(const unsigned short**)((char*)*(void**)node + 0x14));
        if ((((char*)name.mpCapacity - (char*)name.mpBegin) & ~1) > 2 && name.mpBegin)
            operator_delete__(name.mpBegin);
    } else if ((void*)newMode == (void*)0x01654c08 || newMode == -1 ||
               (void*)newMode == (void*)0x02ccd1d2) {
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6de8);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6d19);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c43e8);
        void* nm = SP_NounManager();
        ((Noun*)nm)->PreShutdown();
        FUN_00c9a080();
        ((Noun*)SP_NounManager())->PostShutdown();
    }

    void* editor = this->mpEditor_0xe4;
    if (editor) {
        if ((void*)newMode == (void*)0x00dbdba1) {
            CommunityEditor* ce = *(CommunityEditor**)((char*)editor + 0x80);
            if (ce != 0 && ce->IsActive() != 0) {
                this->mpMode_0xf4 = (void*)ce->GetResult();
                ce->Deactivate(1, 1);
            }
            ((ModeSub*)editor)->Fn0ed0();
        } else {
            ((TFnV)VTFN(editor, 8 / 4))(editor);
        }
    }

    ((HintTarget*)this->mpHintTarget_0xe8)->Reset(0);
    if ((void*)newMode != (void*)0x00dbdba1) {
        void* hint = this->mpHintTarget_0xe8;
        if (hint) {
            ((HintTarget*)hint)->Prep();
            if (this->mpHintTarget_0xe8) {
                void* h = this->mpHintTarget_0xe8;
                ((TFnVI)VTFN(h, 0))(h, 1);
            }
            this->mpHintTarget_0xe8 = 0;
        }
        if (this->mpUndo_0x104) {
            void* u = this->mpUndo_0x104;
            ((TFnV)VTFN(u, 0x24 / 4))(u);
            if (this->mpUndo_0x104) {
                u = this->mpUndo_0x104;
                this->mpUndo_0x104 = 0;
                ((TFnV)VTFN(u, 2))(u);
            }
        }
    }

    void* mgr = SP_0067ddc0();
    if (mgr) {
        ((TFnVI)VTFN(mgr, 0x28 / 4))(mgr, 0);
        ((TFnV)VTFN(mgr, 0x24 / 4))(mgr);
    }
    ((BehaviorMgr*)SP_BehaviorManager())->Clear();
    ((TFnV)VTFN(this, 0x48 / 4))(this);
}

// ===========================================================================
// @ 0x00cfa410
// SP::cCivModeStrategy::InitCityCivModeFromLaunchScreen
void __cdecl FUN_00cfa410()
{
    void* cam = SP_GetCameraCtl();
    if (cam != 0) {
        ((CamCtl*)cam)->LookAt(&DAT_0169d2cc, &DAT_015819b4, 1);
        ((CamCtl*)cam)->F1(0.0f, 0.0f, 0.0f);
        ((CamCtl*)cam)->F2(0.0f, 0.0f, 0.0f);
    }
    DAT_0169d2bc = 1;
    FUN_00401090();
    EditObj* obj = (EditObj*)SP_01021230();
    void* holder = 0;
    if (obj == 0)
        return;
    if (obj->Active() == 0)
        goto cleanup;
    {
        PropMgr* props = (PropMgr*)SP_PropertyManager();
        if (holder != 0) {
            void* old = holder;
            holder = 0;
            ((TFnV)VTFN(old, 1))(old);
        }
        void* key = obj->Lookup(0xe38475d9, &holder);
        if (props->Test(key) == 0)
            goto cleanup;
        Universe* uni = (Universe*)SP_01021260();
        void* planet = uni->GetPlanet(1, 1);
        ((PM*)SP_PlanetModel())->SetPlanet(planet);
        void* marker = 0;
        if (SP_GetPropertyAsUint32(holder, 0xe01c9c03, &marker) && marker != 0) {
            FUN_00d1c610((int)marker, 0);
        } else {
            uni->Erase9(-9);
            uni->EraseKeyBC();
            uni->EraseKeyD0();
            ((StarMgr*)SP_StarManager())->Find(uni, 0);
        }
        void* pm = SP_PlanetModel();
        ((SecBase*)((char*)pm + 4))->SetKey(0x2ccd1d2, &DAT_01654c04);
        void* tfm = SP_TerraformingManager();
        ((TFnPIV)VTFN(tfm, 6))(tfm, 0x2ccd1d2, &DAT_01654c04);
        void* x = SP_00b3d3b0();
        ((TFnPIV)VTFN((char*)x + 4, 6))((char*)x + 4, 0x2ccd1d2, &DAT_01654c04);
        FUN_00ba1c60(&DAT_01654c04);
        ((Noun*)SP_NounManager())->ProcessPending();
        DAT_0169d2bc = 0;
        {
            Msg5 msg;
            msg.mData2 = 0x1c3d2e0;
            msg.mpVtbl = (void*)0x13eb90c;
            msg.miRef = 0;
            msg.mpVtbl = (void*)0x13eb844;
            msg.mData3 = 0;
            ((MsgServer*)SP_EA_Messaging())->Post(msg.mData2, (void*)&msg, 0);
            msg.Destruct();
        }
    }
cleanup:
    if (holder != 0) {
        void* old = holder;
        holder = 0;
        ((TFnV)VTFN(old, 1))(old);
    }
}
