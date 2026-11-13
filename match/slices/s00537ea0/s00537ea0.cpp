#include "game/types.h"

struct Mgr_00537ea0 {
    bool Check_00525a40(); // 0x00525a40
};

extern Mgr_00537ea0* __cdecl GetMgr_00401080();
inline Mgr_00537ea0* GetMgrInline() { return GetMgr_00401080(); }

struct Host_00537ea0 {
    uint8_t pad00[0x44];
    bool mFlag44; // +0x44

    // @ 0x00537ea0
    bool IsUsable();
};

// @ 0x00537ea0
bool Host_00537ea0::IsUsable()
{
    return !mFlag44 || GetMgrInline()->Check_00525a40();
}
