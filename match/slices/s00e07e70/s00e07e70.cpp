// GonzagoHintConditions  @ 0x00e07e70
//
// PARTIAL reconstruction. ~5747-byte __cdecl dispatcher: a long if/else chain on
// a 32-bit hint-condition id (FNV-1 hashes).  The first ~12 conditions and the
// overall shape are reproduced; the remaining ~115 conditions (creature/city/
// tribe/mission predicates) are omitted.
//
//   bool GonzagoHintConditions(int tag)

#pragma once
typedef unsigned char byte;

// --- game-mode globals returned by SP::GetCurrentGameMode() (masked) ---
extern "C" unsigned char DAT_01654c00;
extern "C" unsigned char DAT_01654c01;
extern "C" unsigned char DAT_01654c02;
extern "C" unsigned char DAT_01654c04;
extern "C" unsigned char DAT_01654c05;
extern "C" unsigned char LAB_00dbdb9f_2;

// --- SP helpers (masked relocations) ---
extern "C" void* SP_GetCurrentGameMode(void);
extern "C" int   SP_SporeGuide(void);
extern "C" int   SP_GameTimeManager(void);
extern "C" int   SP_SporeGuide_guide(int id);
extern "C" void  SP_NounManager(int id);
extern "C" int   SP_NounManager_avatar(void);
extern "C" int   SP_cGameNounManager_GetAvatar(void);
extern "C" byte  FUN_00de4380(void);
extern "C" void  FUN_00c77bf0(int id);
extern "C" byte  FUN_00c772c0(int id);
extern "C" void  FUN_00bfc490(void);
extern "C" void  FUN_00c0b9c0(void);
extern "C" byte  FUN_00c0b770(void);

// @ 0x00e07e70
bool GonzagoHintConditions(int tag)
{
    if (tag == (int)0xbb2129cd)
        return FUN_00de4380() != 0;

    if (tag == 0x29930bb7)
        return SP_GetCurrentGameMode() == (void*)&LAB_00dbdb9f_2;

    if (tag == 0x3d97a8ef)
        return SP_GetCurrentGameMode() == (void*)&DAT_01654c00;
    if (tag == 0x2b978c55)
        return SP_GetCurrentGameMode() == (void*)&DAT_01654c01;
    if (tag == 0x256ca1de)
        return SP_GetCurrentGameMode() == (void*)&DAT_01654c02;
    if (tag == 0x27978581)
        return SP_GetCurrentGameMode() == (void*)&DAT_01654c04;
    if (tag == 0x297079fb)
        return SP_GetCurrentGameMode() == (void*)&DAT_01654c05;

    // terrain-editor "current sphere" pair
    if (tag == 0x3158bf4f || tag == (int)0xadfcd351)
    {
        int guide = SP_SporeGuide();
        if (*(char*)(guide + 0x1c) != 0)
        {
            SP_NounManager(0x52da204);
            FUN_00c77bf0(0x52da204);
        }
        SP_NounManager(0x52da204);
        return FUN_00c772c0(0x52da204) != 0;
    }

    if (tag == (int)0xbc8ead02)   // -0x437186fe
        return false;

    // --- partially reconstructed ---
    // The remaining ~115 ids fan out over the current game mode (spacestage,
    // civstage, tribestage, cellstage, creaturestage, ...) and test avatar,
    // city, tribe, mission and mining state.  Each arm follows one of two
    // shapes:
    //     if (tag == HASH) { helper1(); return cond; }
    //     if (tag == HASH) { if (cond) return false; return flag; }
    // e.g. under DAT_01654c01 (creature stage):
    //   0x3481f823 -> false
    //   0xab5783e0 -> avatar bounding test < DAT_01582e1c, then flag +0xb5e
    //   0x3e79c333 -> avatar test, then flag +0xb5e
    //   0x9c9ee7b8 -> FUN_00d2e360, compare < *DAT_0169e35c, FUN_00c0b770
    // Reproducing all arms byte-for-byte requires enumerating every hash and its
    // exact inlined predicate; withheld, so this function is incomplete.
    return false;
}
