// Slice s00e52c70: cell-game state check -- true only while the two cell-game
// timers are non-positive, the +0x5190 sub-object is flagged and the config
// manager reports the key below as enabled.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern char* gspCellGame;                       // 0x016b3c04
extern char* g_16b3c0c;                         // 0x016b3c0c

struct IConfigManager_00e52c70;

struct ConfigVtbl_00e52c70 {
    char pad_00[0x30];                          // +0x00 .. +0x2f
    unsigned int (__thiscall* fn_30)(IConfigManager_00e52c70*, unsigned int);  // +0x30
};

struct IConfigManager_00e52c70 {
    ConfigVtbl_00e52c70* vtbl;                  // +0x00
};

extern "C" IConfigManager_00e52c70* ConfigManager();   // 0x0067dd30

// @ 0x00e52c70
bool __cdecl FUN_00e52c70(void)
{
    char* game = gspCellGame;
    if (!(*(float*)(game + 0x51cc) > 0.0f)
        && (*(char**)(game + 0x5190))[0x69] != 0
        && *(float*)(game + 0x51d0) > 0.0f
        && g_16b3c0c[0x938] == 0)
    {
        IConfigManager_00e52c70* cfg = ConfigManager();
        if (cfg->vtbl->fn_30(cfg, 0x4ea96cb) > 0)
            return true;
    }
    return false;
}