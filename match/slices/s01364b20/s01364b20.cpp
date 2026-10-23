// Slice s01364b20 -- the Simulator property system's static initializers:
//
//   0x01364b20  $E494      -- three-row attribute table of the creature editor (builds each 0x3c-byte
//                             record on the stack, then block-copies it into the table).
//   0x01364f50  $E218      -- eight-row attribute table (one handled UI "command"-like object).
//   0x01365320  $E260      -- eight-row attribute table (the creature "call mate" behaviour object).
//   0x013674d0  unnamed    -- registers the four cStimulus descriptions used by the Social behaviour.
//   0x0136bfb0  $E513      -- pushes the "ImpostorOffset" node onto the sGGEProperties list.
//   0x0136cfb0  unnamed    -- copies a float to its mirror and to its negation.
//   0x0136da30  unnamed    -- six-row attribute table of the SpaceGame data block.
//   0x0136dcb0  unnamed    -- four-row attribute table of the scenario/terrain link block.
//   0x01370490  unnamed    -- constructs the SPUI layout singleton and registers its destructor.
//   0x01370950  unnamed    -- "ProgressBarSuccessSound" node of the progress-bar property list.
//   0x013709b0  unnamed    -- "ProgressBarFailSound" node of the same list.
//   0x013716e0  unnamed    -- "ImpostorOffset" node of the dialog-layout property list.
//   0x013717e0  unnamed    -- "BackgroundEffectID" node of the dialog-layout property list.
//   0x01373000  unnamed    -- "LineColorTop" node of the line-colour property list.
//   0x01373090  unnamed    -- "LineColorMiddle" node of the line-colour property list.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (Simulator static-init module).
#include "types.h"

#pragma warning(disable: 4100)

extern "C" int      __cdecl atexit(void (__cdecl*)());
extern "C" uint32_t __cdecl FNVHash(const char* name, uint32_t seed, int lowercased);  // 0x00932e80

// ---- unnamed attribute-table callees, named by address --------------------------
extern "C" void FUN_00572810();
extern "C" void FUN_00572840();
extern "C" void FUN_0057cde0();
extern "C" void FUN_0057ce00();
extern "C" void FUN_00675ca0();
extern "C" void FUN_00692ca0();
extern "C" void FUN_00692fb0();
extern "C" void FUN_00692ff0();
extern "C" void FUN_00693090();
extern "C" void FUN_006930b0();
extern "C" void FUN_00693150();
extern "C" void FUN_00694c10();
extern "C" void FUN_00694c80();
extern "C" void FUN_00694ee0();
extern "C" void FUN_00694f00();
extern "C" void FUN_00694fa0();
extern "C" void FUN_00694fc0();
extern "C" void FUN_00695080();
extern "C" void FUN_00ac8050();
extern "C" void FUN_00ac8750();
extern "C" void FUN_00ac8780();
extern "C" void FUN_00ac87c0();
extern "C" void FUN_00ac87f0();
extern "C" void FUN_00ac88f0();
extern "C" void FUN_00acbb80();
extern "C" void FUN_00acbbc0();
extern "C" void FUN_00ae3310();
extern "C" void FUN_00ae3430();
extern "C" void FUN_00ae3450();
extern "C" void FUN_00ae3470();
extern "C" void FUN_00ae3490();
extern "C" void FUN_00ae5720();
extern "C" void FUN_00b1fbf0();
extern "C" void FUN_00b20510();
extern "C" void FUN_00b6f550();
extern "C" void FUN_00ba7450();
extern "C" void FUN_00ba94e0();
extern "C" void FUN_00baa2b0();
extern "C" void FUN_00bca960();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00c78ff0();
extern "C" void FUN_00cd5980();
extern "C" void FUN_00cd92f0();
extern "C" void FUN_00cdb4c0();
extern "C" void FUN_00d011e0();
extern "C" void FUN_00d38b50();
extern "C" void FUN_00d38b70();
extern "C" void FUN_00d38b90();
extern "C" void FUN_00d4b390();
extern "C" void FUN_00d4cce0();
extern "C" void FUN_00d4d7f0();
extern "C" void FUN_00d4ebe0();
extern "C" void FUN_00de46a0();
extern "C" void FUN_00de4c80();
extern "C" void FUN_00de4d10();
extern "C" void FUN_00de4d50();
extern "C" void FUN_00de4d90();
extern "C" void FUN_00de6840();
extern "C" void FUN_00de70a0();
extern "C" void FUN_00de7200();
extern "C" void FUN_00de7330();
extern "C" void FUN_011874d0();

namespace Simulator {

// One row of a serialized-attribute table.  The initializers build a 15-dword record on the stack and
// block-copy it into the global table; the three words at +0x0c.. are never written, so they keep
// whatever the stack held (the source left them uninitialized too).
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
};

}  // namespace Simulator

using Simulator::Attribute;

// ---- the attribute tables (start of each table) ---------------------------------
extern Attribute g_creatureEditorAttributes[3];            // 0x015833f0
extern Attribute g_commandUIAttributes[8];                 // 0x015836c8
extern Attribute g_mateBehaviourAttributes[8];             // 0x01583b00
extern Attribute g_spaceGameDataAttributes[6];             // 0x015a38b8
extern Attribute g_scenarioTerrainAttributes[4];           // 0x015a3a60

// ===========================================================================
// @ 0x01364b20  $E494
// ===========================================================================
void init_15833f0()
{
    Attribute a;

    a.mpName   = "mbDisplayingEvolutionButton";
    a.mHash    = 0x054aba85;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;   // default-value getter
    a.mpFn24   = (void*)&FUN_00ac8750;
    a.mpFn28   = (void*)&FUN_00ac8780;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694fa0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057ce00;
    a.mLocation = 0xdc;
    g_creatureEditorAttributes[0] = a;

    a.mpName   = "sCreatureGameData";
    a.mHash    = 0x061afc2e;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_011874d0;
    a.mpFn24   = (void*)&FUN_00d38b70;
    a.mpFn28   = (void*)&FUN_00d38b90;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d38b50;
    a.mpFn38   = 0;
    a.mLocation = 0x0169e370;
    g_creatureEditorAttributes[1] = a;

    a.mpName   = "mAllPartsUnlockedColumn";
    a.mHash    = 0x066ce337;
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
    g_creatureEditorAttributes[2] = a;
}

// ===========================================================================
// @ 0x01364f50  $E218
// ===========================================================================
void init_15836c8()
{
    Attribute a;

    a.mpName   = "mbActive";
    a.mHash    = 0x0559039b;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ac8750;
    a.mpFn28   = (void*)&FUN_00ac8780;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694fa0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057ce00;
    a.mLocation = 0xc;
    g_commandUIAttributes[0] = a;

    a.mpName   = "mType";
    a.mHash    = 0x055903a0;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x14;
    g_commandUIAttributes[1] = a;

    a.mpName   = "mFrequency";
    a.mHash    = 0x0695c2d7;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x18;
    g_commandUIAttributes[2] = a;

    a.mpName   = "mCheckTime";
    a.mHash    = 0x069d8c20;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00ac88f0;
    a.mpFn2c   = (void*)&FUN_006930b0;
    a.mpFn30   = (void*)&FUN_00694fc0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbb80;
    a.mLocation = 0x28;
    g_commandUIAttributes[3] = a;

    a.mpName   = "mDuration";
    a.mHash    = 0x055946f7;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00ac88f0;
    a.mpFn2c   = (void*)&FUN_006930b0;
    a.mpFn30   = (void*)&FUN_00694fc0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbb80;
    a.mLocation = 0x2c;
    g_commandUIAttributes[4] = a;

    a.mpName   = "mPropListKey";
    a.mHash    = 0x055903a4;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ae3430;
    a.mpFn28   = (void*)&FUN_00ae3450;
    a.mpFn2c   = (void*)&FUN_00693150;
    a.mpFn30   = (void*)&FUN_00695080;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00ae5720;
    a.mLocation = 0x34;
    g_commandUIAttributes[5] = a;

    a.mpName   = "mData";
    a.mHash    = 0x055903a7;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00cdb4c0;
    a.mpFn28   = (void*)&FUN_00cd5980;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00cd92f0;
    a.mLocation = 0x44;
    g_commandUIAttributes[6] = a;

    a.mpName   = "mGameDataMap";
    a.mHash    = 0x055903ab;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00d4ebe0;
    a.mpFn28   = (void*)&FUN_00d4cce0;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d4b390;
    a.mpFn38   = (void*)&FUN_00c78ff0;
    a.mLocation = 0x5c;
    g_commandUIAttributes[7] = a;
}

// ===========================================================================
// @ 0x01365320  $E260
// ===========================================================================
void init_1583b00()
{
    Attribute a;

    a.mpName   = "mGameTimer";
    a.mHash    = 0x057a5299;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ae3470;
    a.mpFn28   = (void*)&FUN_00ae3490;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00ae3310;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x18;
    g_mateBehaviourAttributes[0] = a;

    a.mpName   = "mpMate";
    a.mHash    = 0x32709745;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00b20510;
    a.mpFn28   = (void*)&FUN_00bca960;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00b6f550;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x38;
    g_mateBehaviourAttributes[1] = a;

    a.mpName   = "mpBabyTeacher";
    a.mHash    = 0x94d9ce6c;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00b20510;
    a.mpFn28   = (void*)&FUN_00bca960;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00b6f550;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x14;
    g_mateBehaviourAttributes[2] = a;

    a.mpName   = "mCheckForMateTimer";
    a.mHash    = 0x04a0ad62;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00ac88f0;
    a.mpFn2c   = (void*)&FUN_006930b0;
    a.mpFn30   = (void*)&FUN_00694fc0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbb80;
    a.mLocation = 0x3c;
    g_mateBehaviourAttributes[3] = a;

    a.mpName   = "mCurrentMateCallIndex";
    a.mHash    = 0x04a0ad63;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x40;
    g_mateBehaviourAttributes[4] = a;

    a.mpName   = "mNestUpgradeLevel";
    a.mHash    = 0x93f4227d;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00692ff0;
    a.mpFn30   = (void*)&FUN_00694ee0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057cde0;
    a.mLocation = 0x44;
    g_mateBehaviourAttributes[5] = a;

    a.mpName   = "mDramaEvents";
    a.mHash    = 0x055912ad;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00d4d7f0;
    a.mpFn28   = (void*)&FUN_00ba94e0;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00ba7450;
    a.mpFn38   = (void*)&FUN_00baa2b0;
    a.mLocation = 0x50;
    g_mateBehaviourAttributes[6] = a;

    a.mpName   = "mActiveDramaEventMask";
    a.mHash    = 0x746556ec;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x6c;
    g_mateBehaviourAttributes[7] = a;
}

// ===========================================================================
// @ 0x0136da30
// ===========================================================================
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

// ===========================================================================
// @ 0x0136dcb0
// ===========================================================================
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

// ---- stimulus descriptions (Social behaviour) -----------------------------------
namespace SP {

bool AddLoudness(void* stimulus);        // 0x00d85370
bool RemoveLoudness(void* stimulus);     // 0x00d853b0
bool UpdateLoudness(void* stimulus);     // 0x00d85400
bool AddHeldObject(void* stimulus);      // 0x00d85480
bool AddAlphaFade(void* stimulus);       // 0x00d854f0

}  // namespace SP

typedef bool (__cdecl* StimulusCallback)(void* stimulus);

// A SocialBehaviour stimulus description; the method at 0x00bc9e30 fills the instance.
class cStimulus {
public:
    void FUN_00bc9e30(float range, StimulusCallback add, StimulusCallback remove,
                      StimulusCallback update, const char* name);
};

extern const float kStimulusMaxRange;                      // 0x0147c030 FLT_MAX
extern cStimulus   g_loudnessStimulus;                     // 0x0169f0f0
extern cStimulus   g_heardRagingRoarStimulus;              // 0x0169f134
extern cStimulus   g_heardSirenSongStimulus;               // 0x0169f178
extern cStimulus   g_wasMotherStimulus;                    // 0x0169f1bc
extern void        FUN_013c5790();                         // 0x013c5790 atexit destructor

// ===========================================================================
// @ 0x013674d0
// ===========================================================================
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

// ---- FNV-hashed property nodes ---------------------------------------------------
// The registered-property nodes: +0x00 is the property-list key, +0x04 the FNV hash of the property
// name, +0x08 the previously registered node (the list head is updated afterwards), then the value.
// Several value shapes share the same three-word header, so the header stays a common base.
struct PropertyNode {
    const char*  mpKey;                                    // +0x00
    uint32_t     mHash;                                    // +0x04
    PropertyNode* mpNext;                                  // +0x08
};

struct GGEProperty : PropertyNode {                        // 0x18 bytes
    float        mValue0c;                                 // +0x0c
    float        mValue10;                                 // +0x10
    float        mValue14;                                 // +0x14
};

struct UIProperty : PropertyNode {                         // 0x18 bytes
    uint32_t     mValue0c;                                 // +0x0c
    uint32_t     mValue10;                                 // +0x10
    uint32_t     mValue14;                                 // +0x14
};

struct LineColorProperty : PropertyNode {                  // 0x1c bytes
    float        mRed;                                     // +0x0c
    float        mGreen;                                   // +0x10
    float        mBlue;                                    // +0x14
    float        mAlpha;                                   // +0x18
};

extern PropertyNode* sGGEProperties;                       // 0x015a2ff8
extern GGEProperty  kImpostorOffset;                       // 0x016a0dc4
extern GGEProperty  kImpostorOffsetDialog;                 // 0x016ac5e0
extern PropertyNode* sProgressBarProperties;              // 0x015a55e8
extern PropertyNode* sDialogLayoutProperties;             // 0x015a57d0
extern UIProperty   kProgressBarSuccessSound;              // 0x016ac318
extern UIProperty   kProgressBarFailSound;                 // 0x016ac330
extern UIProperty   kBackgroundEffectID;                   // 0x016ac618
extern LineColorProperty* sLineColorProperties;            // 0x015a59f4
extern LineColorProperty  kLineColorTop;                   // 0x016ace34
extern LineColorProperty  kLineColorMiddle;                // 0x016ace50

// Property-list key strings these nodes point at.
extern const char g_propKey147d3b8;                        // 0x0147d3b8
extern const char g_propKey14811f0;                        // 0x014811f0
extern const char g_propKey1481e20;                        // 0x01481e20

// Colours and factors the line-colour nodes start from.
extern const float kLineColorTopA;                         // 0x0144359c 0.03
extern const float kLineColorTopB;                         // 0x0148223c 0.44
extern const float kLineColorTopC;                         // 0x01482238 0.22
extern const float kLineColorMiddleA;                      // 0x01482254 0.29
extern const float kLineColorMiddleB;                      // 0x01482250 0.74
extern const float kLineColorMiddleC;                      // 0x013f6a20 0.85
extern const float kColorOne;                              // 0x01485720 1.0F

extern void FUN_013c6000();                                // 0x013c6000 atexit destructor
extern void FUN_013c75c0();                                // 0x013c75c0 atexit destructor
extern void FUN_013c75d0();                                // 0x013c75d0 atexit destructor
extern void FUN_013c78d0();                                // 0x013c78d0 atexit destructor
extern void FUN_013c7900();                                // 0x013c7900 atexit destructor
extern void FUN_013c7a80();                                // 0x013c7a80 atexit destructor
extern void FUN_013c7a90();                                // 0x013c7a90 atexit destructor

// ===========================================================================
// @ 0x0136bfb0  $E513
// ===========================================================================
void init_16a0dc4()
{
    kImpostorOffset.mHash = FNVHash("ImpostorOffset", 0x811c9dc5, 1);
    kImpostorOffset.mpNext = sGGEProperties;
    sGGEProperties = &kImpostorOffset;
    kImpostorOffset.mpKey = &g_propKey147d3b8;
    kImpostorOffset.mValue0c = 0.0F;
    kImpostorOffset.mValue10 = 0.0F;
    kImpostorOffset.mValue14 = 0.0F;
    atexit(&FUN_013c6000);
}

// ===========================================================================
// @ 0x0136cfb0
// ===========================================================================
extern float g_halfPi;                                     // 0x015a303c
extern float g_negativeHalfPi;                             // 0x015a3078
extern float g_positiveHalfPi;                             // 0x015a307c

void init_15a3078()
{
    float value = g_halfPi;
    g_negativeHalfPi = -value;
    g_positiveHalfPi = value;
}

// ===========================================================================
// @ 0x01370490
// ===========================================================================
// Constructs the SPUI layout singleton at 0x15a51bc; the flags byte at 0x15a51d4 starts out clear.
class cSPUILayout {
public:
    cSPUILayout* FUN_00810000();                           // 0x00810000 (constructor)
};

extern cSPUILayout g_spuiLayout;                           // 0x015a51bc
extern bool        g_spuiLayoutInitialized;                // 0x015a51d4
extern void        FUN_013c72d0();                         // 0x013c72d0 atexit destructor

void init_15a51bc()
{
    g_spuiLayout.FUN_00810000();
    g_spuiLayoutInitialized = false;
    atexit(&FUN_013c72d0);
}

// ===========================================================================
// @ 0x01370950
// ===========================================================================
void init_16ac318()
{
    kProgressBarSuccessSound.mHash = FNVHash("ProgressBarSuccessSound", 0x811c9dc5, 1);
    kProgressBarSuccessSound.mpNext = sProgressBarProperties;
    sProgressBarProperties = &kProgressBarSuccessSound;
    kProgressBarSuccessSound.mpKey = &g_propKey14811f0;
    kProgressBarSuccessSound.mValue0c = 0;
    kProgressBarSuccessSound.mValue10 = 0;
    kProgressBarSuccessSound.mValue14 = 0;
    atexit(&FUN_013c75c0);
}

// ===========================================================================
// @ 0x013709b0
// ===========================================================================
void init_16ac330()
{
    kProgressBarFailSound.mHash = FNVHash("ProgressBarFailSound", 0x811c9dc5, 1);
    kProgressBarFailSound.mpNext = sProgressBarProperties;
    sProgressBarProperties = &kProgressBarFailSound;
    kProgressBarFailSound.mpKey = &g_propKey14811f0;
    kProgressBarFailSound.mValue0c = 0;
    kProgressBarFailSound.mValue10 = 0;
    kProgressBarFailSound.mValue14 = 0;
    atexit(&FUN_013c75d0);
}

// ===========================================================================
// @ 0x013716e0
// ===========================================================================
void init_16ac5e0()
{
    kImpostorOffsetDialog.mHash = FNVHash("ImpostorOffset", 0x811c9dc5, 1);
    kImpostorOffsetDialog.mpNext = sDialogLayoutProperties;
    sDialogLayoutProperties = &kImpostorOffsetDialog;
    kImpostorOffsetDialog.mpKey = &g_propKey147d3b8;
    kImpostorOffsetDialog.mValue0c = 0.0F;
    kImpostorOffsetDialog.mValue10 = 0.0F;
    kImpostorOffsetDialog.mValue14 = 0.0F;
    atexit(&FUN_013c78d0);
}

// ===========================================================================
// @ 0x013717e0
// ===========================================================================
void init_16ac618()
{
    kBackgroundEffectID.mHash = FNVHash("BackgroundEffectID", 0x811c9dc5, 1);
    kBackgroundEffectID.mpNext = sDialogLayoutProperties;
    sDialogLayoutProperties = &kBackgroundEffectID;
    kBackgroundEffectID.mpKey = &g_propKey14811f0;
    kBackgroundEffectID.mValue0c = 0;
    kBackgroundEffectID.mValue10 = 0;
    kBackgroundEffectID.mValue14 = 0;
    atexit(&FUN_013c7900);
}

// ===========================================================================
// @ 0x01373000
// ===========================================================================
void init_16ace34()
{
    kLineColorTop.mHash = FNVHash("LineColorTop", 0x811c9dc5, 1);
    kLineColorTop.mRed = kLineColorTopA;
    kLineColorTop.mGreen = kLineColorTopB;
    kLineColorTop.mBlue = kLineColorTopC;
    kLineColorTop.mpNext = sLineColorProperties;
    sLineColorProperties = &kLineColorTop;
    kLineColorTop.mpKey = &g_propKey1481e20;
    kLineColorTop.mAlpha = kColorOne;
    atexit(&FUN_013c7a80);
}

// ===========================================================================
// @ 0x01373090
// ===========================================================================
void init_16ace50()
{
    kLineColorMiddle.mHash = FNVHash("LineColorMiddle", 0x811c9dc5, 1);
    kLineColorMiddle.mRed = kLineColorMiddleA;
    kLineColorMiddle.mGreen = kLineColorMiddleB;
    kLineColorMiddle.mBlue = kLineColorMiddleC;
    kLineColorMiddle.mpNext = sLineColorProperties;
    sLineColorProperties = &kLineColorMiddle;
    kLineColorMiddle.mpKey = &g_propKey1481e20;
    kLineColorMiddle.mAlpha = kColorOne;
    atexit(&FUN_013c7a90);
}
