// s01057d50.cpp - reconstructed slice
// Compiler: MSVC 2008 SP1 (x86)
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
// ---------------------------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------------------------
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;
typedef float              f32;

// Object with a virtual method table (only the vtable pointer matters here).
struct cVObj {
    void** vftable;                     // 0x00
};

// Space-token translator global (0x16e0d08).
struct cSpaceTokenTranslator {
    u8    mPad00[0x14];
    i32   mField14;                     // 0x14
    u8    mPad18[0x24 - 0x18];
    void* mpField24;                    // 0x24 (species profile)
};
extern "C" char g_spaceTokenTranslator[];    // 0x16e0d08

// Creature-base object: embedded species-profile sub-record and vtable.
struct cSpeciesSubRec {
    u8    mPad000[0x504];
};
struct cSPCreatureBase {
    void** vftable;                     // 0x00
    u8     mPad04[0x0b20 - 0x04];
    void*  mpField0b20;                 // 0x0b20 (active-planet-ish object)

    void* GetSpeciesRecord();           // 0x00c0bbd0 -> returns species profile
};

// Species profile handed back by GetSpeciesRecord.
struct cSpeciesProfile {
    u8    mPad000[0x504];
    i32   mField504;                    // 0x504
    i32   mField508;                    // 0x508
    i32   mField50c;                    // 0x50c
};

// ---------------------------------------------------------------------------------------------
// Opaque extern callees referenced by absolute address.
// ---------------------------------------------------------------------------------------------
void __cdecl NotifyScannedCreatureSpecies(void* speciesRec, i32 flag);   // 0x01058460
void* __cdecl GetActivePlanet();                                         // 0x01021260

// Text-helper object with a cString at a given sub-offset.
struct cTextHolder {
    u8 mPad[4];
};
wchar_t* __cdecl TextHolder_GetText(void* holder);                       // 0x006b55c0

void* __cdecl GetIconTrayObj();                                          // 0x010666a0

// ShowScanEventLog(v3, v1, v2, fn, text) -- 5 dwords passed by value/push.
void __cdecl ShowScanEventLog(i32 v3, i32 v1, i32 v2, void* fn, void* text);   // 0x010531b0

struct cPlanetVt {
    void** vftable;
};

// Vtable slot call: slot index = byteoffset/4. Returns u32.
static inline u32 VT_0C_0(void* p, void* arg)
{
    void** vt = *(void***)p;
    void* fn = vt[3];
    return ((u32 (__thiscall*)(void*, void*))fn)(p, arg);
}

u8   __cdecl cPlanet_SetSpeciesAsScanned(void* planet, void* sub);         // 0x00c73ea0
void __cdecl cPlanet_ResetSpecies(void* planet, void* sub, i32 a, i32 b);  // 0x00c74690
void* __cdecl Text_GetText(void* strObj);                                  // 0x006b55c0

// ---------------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------------
// @ 0x01058660
// Forwards to NotifyScannedCreatureSpecies with the object's embedded species record.
void __cdecl ScanBuildingSpecies(void* obj, i32 flag)
{
    NotifyScannedCreatureSpecies((char*)*(void**)((char*)obj + 0x0b20) + 0x504, flag);
}

// @ 0x01058680
// Handles the "scan building" action for a creature base object.
extern "C" u32 __cdecl ScanBuilding(cSPCreatureBase* creature)
{
    u32 ok = 0;
    i32 v1;
    i32 v2;
    if (creature != 0) {
        if (VT_0C_0(creature, (void*)0xd0036e08) != 0) {
            void* planet = GetActivePlanet();
            cSpeciesProfile* species = (cSpeciesProfile*)creature->GetSpeciesRecord();
            cSpeciesSubRec* sub = (cSpeciesSubRec*)((char*)species + 0x504);

            v1 = species->mField508;
            v2 = species->mField50c;
            i32 v3 = species->mField504;

            char* tok = *(char**)g_spaceTokenTranslator;
            *(i32*)(tok + 0x14) = 0;
            *(void**)(tok + 0x24) = species;

            if (cPlanet_SetSpeciesAsScanned(planet, sub) == 0) {
                cPlanet_ResetSpecies(planet, sub, 1, 1);
                void* tray = GetIconTrayObj();
                void* text = Text_GetText((char*)tray + 0x44);
                ShowScanEventLog(v3, v1, v2, (void*)0x01052fd0, text);
                NotifyScannedCreatureSpecies((char*)creature->mpField0b20 + 0x504, 1);
                ok = 1;
            } else {
                void* tray = GetIconTrayObj();
                void* text = Text_GetText((char*)tray + 0x58);
                ShowScanEventLog(v3, v1, v2, 0, text);
            }
        }
    }
    return ok;
}
