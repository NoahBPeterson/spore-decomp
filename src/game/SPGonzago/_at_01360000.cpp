// src/game/SPGonzago/_at_01360000.cpp -- migrated from slice(s) s01364b20, s0135d100 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01360000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned char g_01582786, g_0169defc;
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00572840();
extern "C" void fn_00693090();
extern "C" void fn_00694f00();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00675ca0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00ac88f0();
extern "C" void fn_006930b0();
extern "C" void fn_00694fc0();
extern "C" void fn_00acbb80();
extern "C" void fn_00692ff0();
extern "C" void fn_00694ee0();
extern "C" void fn_00aff840();
extern "C" void fn_00aff870();
extern "C" void fn_00692fd0();
extern "C" void fn_00694ec0();
extern "C" void fn_00595a70();
extern "C" void fn_00c143c0();
extern "C" void fn_00c143e0();

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_015829b8, g_015829f4, g_01582a30, g_01582a6c, g_01582aa8,
         g_01582ae4, g_01582b20;
extern unsigned char g_01582786, g_0169defc;
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00572840();
extern "C" void fn_00693090();
extern "C" void fn_00694f00();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00675ca0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00ac88f0();
extern "C" void fn_006930b0();
extern "C" void fn_00694fc0();
extern "C" void fn_00acbb80();
extern "C" void fn_00692ff0();
extern "C" void fn_00694ee0();
extern "C" void fn_00aff840();
extern "C" void fn_00aff870();
extern "C" void fn_00692fd0();
extern "C" void fn_00694ec0();
extern "C" void fn_00595a70();
extern "C" void fn_00c143c0();
extern "C" void fn_00c143e0();
// ---- items of slice s0135d100 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern T g_015829b8, g_015829f4, g_01582a30, g_01582a6c, g_01582aa8,
         g_01582ae4, g_01582b20;

// ---- items of slice s01364b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int      __cdecl atexit(void (__cdecl*)());
extern "C" void FUN_00572810();
extern "C" void FUN_00572840();
extern "C" void FUN_0057cde0();
extern "C" void FUN_00675ca0();
extern "C" void FUN_00692ca0();
extern "C" void FUN_00692fb0();
extern "C" void FUN_00692ff0();
extern "C" void FUN_00693090();
extern "C" void FUN_00694c10();
extern "C" void FUN_00694c80();
extern "C" void FUN_00694ee0();
extern "C" void FUN_00694f00();
extern "C" void FUN_00ac8050();
extern "C" void FUN_00ac87c0();
extern "C" void FUN_00ac87f0();
extern "C" void FUN_00acbbc0();
extern "C" void FUN_00b1fbf0();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00d011e0();
extern "C" void FUN_00de46a0();
extern "C" void FUN_00de4c80();
extern "C" void FUN_00de4d10();
extern "C" void FUN_00de4d50();
extern "C" void FUN_00de4d90();
extern "C" void FUN_00de6840();
extern "C" void FUN_00de70a0();
extern "C" void FUN_00de7200();
extern "C" void FUN_00de7330();
extern const float kStimulusMaxRange;                      // 0x0147c030 FLT_MAX
extern void        FUN_013c5790();                         // 0x013c5790 atexit destructor
extern float g_halfPi;                                     // 0x015a303c
extern float g_negativeHalfPi;                             // 0x015a3078
extern float g_positiveHalfPi;                             // 0x015a307c
#pragma warning(disable: 4100)
namespace Simulator {
struct Attribute {
    const char* mpName;                                    // +0x00  attribute name
    uint32_t    mHash;                                     // +0x04  FNV hash of the name
    uint32_t    mLocation;                                 // +0x08  member offset, or a static address
    uint32_t    mUnused0c;                                 // +0x0c  never written
    uint32_t    mUnused10;                                 // +0x10  never written
    uint32_t    mUnused14;                                 // +0x14  never written
    uint32_t    mZero18;                                   // +0x18
    uint32_t    mZero1c;                                   // +0x1c
    void*       mpFn20;                                    // +0x20
    void*       mpFn24;                                    // +0x24
    void*       mpFn28;                                    // +0x28
    void*       mpFn2c;                                    // +0x2c
    void*       mpFn30;                                    // +0x30
    void*       mpFn34;                                    // +0x34
    void*       mpFn38;                                    // +0x38
};  // namespace Simulator
}
using Simulator::Attribute;
extern Attribute g_spaceGameDataAttributes[6];             // 0x015a38b8
extern Attribute g_scenarioTerrainAttributes[4];           // 0x015a3a60
namespace SP {
bool AddLoudness(void* stimulus);        // 0x00d85370
}
namespace SP {
bool RemoveLoudness(void* stimulus);     // 0x00d853b0
}
namespace SP {
bool UpdateLoudness(void* stimulus);     // 0x00d85400
}
namespace SP {
bool AddHeldObject(void* stimulus);      // 0x00d85480
}
namespace SP {
bool AddAlphaFade(void* stimulus);       // 0x00d854f0
}
typedef bool (__cdecl* StimulusCallback)(void* stimulus);
class cStimulus {
public:
    void FUN_00bc9e30(float range, StimulusCallback add, StimulusCallback remove,
                      StimulusCallback update, const char* name);
};
extern cStimulus   g_loudnessStimulus;                     // 0x0169f0f0
extern cStimulus   g_heardRagingRoarStimulus;              // 0x0169f134
extern cStimulus   g_heardSirenSongStimulus;               // 0x0169f178
extern cStimulus   g_wasMotherStimulus;                    // 0x0169f1bc
// ---- items of slice s01364b20 end

// @ 0x01363fe0
void FUN_01363fe0()
{
    g_0169defc = g_01582786;
}

// @ 0x01364240
void FUN_01364240()
{
    g_015829b8 = T("mCurrentBrainLevel", 0xb4177e0eu, 0x0, fn_00692ca0, (fp)0x572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, (fp)0x57cde0);
    g_015829f4 = T("mAvatarNormalizingScale", 0x61afd98u, 0x4, fn_00692ca0, (fp)0x572810, fn_00ac88f0, fn_006930b0, fn_00694fc0, fn_00b1fbf0, fn_00acbb80);
    g_01582a30 = T("mNumFlapsAllowed", 0x61afd99u, 0x8, fn_00692ca0, (fp)0x572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, (fp)0x57cde0);
    g_01582a6c = T("mAbilityMode", 0xb4177e0fu, 0x24, fn_00692ca0, (fp)0x572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_01582aa8 = T("mEvolutionPoints", 0x7220206fu, 0x28, fn_00692ca0, (fp)0x572810, fn_00ac88f0, fn_006930b0, fn_00694fc0, fn_00b1fbf0, fn_00acbb80);
    g_01582ae4 = T("DEPRECATED_mLearnedAbilities", 0xb4177e0du, 0x30, fn_00692ca0, fn_00aff840, fn_00aff870, fn_00692fd0, fn_00694ec0, fn_00b1fbf0, fn_00595a70);
    g_01582b20 = T("mLearnedAbilities", 0x76b6609u, 0x38, fn_00692ca0, fn_00c143c0, fn_00c143e0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00ac8050);
}

// @ 0x013674d0
void init_169f0f0()
{
    g_loudnessStimulus.FUN_00bc9e30(kStimulusMaxRange, SP::AddLoudness, SP::RemoveLoudness,
                                    SP::UpdateLoudness, "Loudness");
    g_heardRagingRoarStimulus.FUN_00bc9e30(kStimulusMaxRange, 0, SP::AddHeldObject,
                                           0, "HeardRagingRoar");
    g_heardSirenSongStimulus.FUN_00bc9e30(kStimulusMaxRange, 0, SP::AddHeldObject,
                                          SP::AddAlphaFade, "HeardSirenSong");
    g_wasMotherStimulus.FUN_00bc9e30(kStimulusMaxRange, 0, 0, 0, "WasMother");
    atexit(&FUN_013c5790);
}

// @ 0x0136cfb0
void init_15a3078()
{
    float value = g_halfPi;
    g_negativeHalfPi = -value;
    g_positiveHalfPi = value;
}

// @ 0x0136da30
void init_15a38b8()
{
    Attribute a;

    a.mpName   = "mLevelsToUnlockOnActivateOrShutdown";
    a.mHash    = 0x066b980b;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00de6840;
    a.mpFn28   = (void*)&FUN_00de4c80;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d011e0;
    a.mpFn38   = (void*)&FUN_00de70a0;
    a.mLocation = 0x254;
    g_spaceGameDataAttributes[0] = a;

    a.mpName   = "mLastSavedGame";
    a.mHash    = 0x066b980a;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ac87c0;
    a.mpFn28   = (void*)&FUN_00ac87f0;
    a.mpFn2c   = (void*)&FUN_00694c80;
    a.mpFn30   = (void*)&FUN_00694c10;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbbc0;
    a.mLocation = 0xd0;
    g_spaceGameDataAttributes[1] = a;

    a.mpName   = "mNumCaptainsBroughtToLevel10";
    a.mHash    = 0x07ca2686;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00692ff0;
    a.mpFn30   = (void*)&FUN_00694ee0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057cde0;
    a.mLocation = 0xe0;
    g_spaceGameDataAttributes[2] = a;

    a.mpName   = "mNumAdventuresQuickplayed";
    a.mHash    = 0x07ca2687;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x1f8;
    g_spaceGameDataAttributes[3] = a;

    a.mpName   = "mNumAdventuresCreated";
    a.mHash    = 0x07ca2688;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x1fc;
    g_spaceGameDataAttributes[4] = a;

    a.mpName   = "mGGEScenarioTerrainDB";
    a.mHash    = 0x07ca2689;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00de4d10;
    a.mpFn28   = (void*)&FUN_00de4d50;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00de46a0;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x3c;
    g_spaceGameDataAttributes[5] = a;
}

// @ 0x0136dcb0
void init_15a3a60()
{
    Attribute a;

    a.mpName   = "mScenarioToTerrain";
    a.mHash    = 0x07db67db;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00de7200;
    a.mpFn28   = (void*)&FUN_00de4d90;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d011e0;
    a.mpFn38   = (void*)&FUN_00de7330;
    a.mLocation = 0x38;
    g_scenarioTerrainAttributes[0] = a;

    a.mpName   = "mScenarioToScript";
    a.mHash    = 0x07db67dc;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00de7200;
    a.mpFn28   = (void*)&FUN_00de4d90;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d011e0;
    a.mpFn38   = (void*)&FUN_00de7330;
    a.mLocation = 0x54;
    g_scenarioTerrainAttributes[1] = a;

    a.mpName   = "mTerrainToScenario";
    a.mHash    = 0x07db67dd;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00de7200;
    a.mpFn28   = (void*)&FUN_00de4d90;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d011e0;
    a.mpFn38   = (void*)&FUN_00de7330;
    a.mLocation = 0x70;
    g_scenarioTerrainAttributes[2] = a;

    a.mpName   = "mCompletedImpostors";
    a.mHash    = 0x07db67de;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00de6840;
    a.mpFn28   = (void*)&FUN_00de4c80;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d011e0;
    a.mpFn38   = (void*)&FUN_00de70a0;
    a.mLocation = 0;
    g_scenarioTerrainAttributes[3] = a;
}
