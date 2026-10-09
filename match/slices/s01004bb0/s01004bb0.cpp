// Slice s01004bb0 -- SP::cSPSimulatorSpaceGame space-game methods
// (0x01004bb0..0x010057f7).  Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned int   uintptr_t;
typedef int            intptr_t;

extern void* DAT_016dc0fc;    // cSPSimulatorSpaceGame singleton
extern u32   DAT_016dc1e0;    // k_wormhole key
extern float DAT_015b64c0;
extern float DAT_013ec4b8;
extern float DAT_01495390;

// ---------------------------------------------------------------------------
// free callees
// ---------------------------------------------------------------------------
void* __cdecl FUN_00ffbe50();                        // SP::GetUFOSimulator
void* __cdecl FUN_0067dd10();                        // SP::App
int   __cdecl FUN_01021080();                        // GetUniverseContext
void* __cdecl FUN_010212a0();                        // GetActivePlanetRecord
void* __cdecl FUN_01021260();                        // GetActivePlanet
int   __stdcall FUN_01021230(int);                   // 0x01021230
void* __cdecl FUN_01021240();                        // cSPMission::IsArchived
void* __cdecl FUN_01021300_(int);                    // GetPlayerEmpire
void* __cdecl FUN_01021300_2();                      // GetPlayerEmpire (no arg)
void* __cdecl FUN_00b3d2a0();                        // StarManager
void* __cdecl FUN_00b3d300();                        // NounManager
void* __cdecl FUN_00b3d380();                        // GameTimeManager
void* __cdecl FUN_00b3d450();                        // 0x00b3d450
void* __cdecl FUN_00b3d240();                        // 0x00b3d240
void* __cdecl FUN_00675250(u32, int);                // AchievementsController
void* __cdecl FUN_00ba70a0();                        // 0x00ba70a0
void* __cdecl FUN_00b3d2c0();                        // RelationshipManager
void  __cdecl FUN_00e39ab0(u32, int, void*, void*, void*);
void* __cdecl FUN_00fd9c60(int);                     // 0x00fd9c60
void  __cdecl FUN_00fde3e0(void*);                   // TransitionFromPlanetToSolar
void* __cdecl FUN_00401090(int*);                    // GetSetting9
void* __cdecl FUN_004df550(void*);                   // GetProfile
void* __cdecl FUN_01041d30(void*);                   // 0x01041d30
void* __cdecl FUN_00ac10a0(void*);                   // 0x00ac10a0
void* __cdecl FUN_008414c0(void);                    // 0x008414c0
void* __cdecl FUN_00c74730(void*, void*);            // 0x00c74730
void* __cdecl FUN_00c7ed00(void*, void*);            // 0x00c7ed00
void* __cdecl FUN_00ac0d80(void*, void*, void*, void*); // eastl::find
void* __cdecl FUN_00458a40(void*);                   // ColorRGBToU32
void* __cdecl FUN_0067de90(int, void*);              // 0x0067de90
void* __cdecl FUN_007ec160(int, void*);              // 0x007ec160
void* __cdecl FUN_00ba9370(void*);                   // cStarManager::GetEmpireByID
void* __cdecl FUN_00b67740(void*);                   // 0x00b67740
void* __cdecl FUN_010662d0(void*);                   // 0x010662d0
void* __cdecl FUN_00801920(void*);                   // 0x00801920
void* __cdecl FUN_00c375b0(void*);                   // interface_cast camera
void* __cdecl FUN_00b18720(void*);                   // interface_cast turret
float __cdecl FUN_01017030();                        // returns float
void* __cdecl FUN_00c8b770();                        // cStar::GetSolarSystem
int   __cdecl FUN_01042480(float*, float*);          // 0x01042480
void  __cdecl FUN_0106ab20(int);                     // 0x0106ab20
void  __cdecl FUN_0106200(void*, int);               // ToggleStarmapFilters
void  __cdecl FUN_00c706d0(void*, int);              // SetPlanetTechLevel
void  __cdecl FUN_00b22960();                        // cGameNounManager_ProcessPending
void* __cdecl FUN_00ffd710(void*);                   // 0x00ffd710
unsigned __int64 __cdecl FUN_00b316c0();             // returns u64
void  __cdecl FUN_00f47380(void*);                   // operator delete

// thiscall callees
struct Ext {
    void* FUN_00a1ad60();                    // GetPlayerInventory
    void* FUN_00c30cb0();                    // 0x00c30cb0
    void* FUN_00b25fb0();                    // GetPlayerCivilization
    void* FUN_00bf01e0();                    // 0x00bf01e0 -> int
    void* FUN_00bef6c0();                    // 0x00bef6c0
    void* FUN_00bd9e30();                    // SP::ProfLeaveZone -> void*
    void* FUN_00b22960();                    // 0x00b22960
    void* FUN_00b8d950(int);                 // 0x00b8d950
    void* FUN_00b8de30();                    // 0x00b8de30
    int   FUN_00bbaa60(int);                 // 0x00bbaa60
    void  FUN_00bb9c40(int);                 // 0x00bb9c40
    void* FUN_00c71530();                    // 0x00c71530
    void* FUN_00e0fb50();                    // RemoveAllIcons
    void* FUN_00e0ad00(int);                 // 0x00e0ad00
    void* FUN_00e0e1a0();                    // 0x00e0e1a0
    void  FUN_0106ab20(int);                 // 0x0106ab20
    void* FUN_01067e60();                    // 0x01067e60
    void* FUN_00ff3f00();                    // 0x00ff3f00
    void* FUN_00c32cd0(void*);               // GetColor
    void* FUN_00c30c60();                    // 0x00c30c60
    void* FUN_00c31730();                    // GetHomePlanet
    void* FUN_00bb59b0(int);                 // GetOrActivatePlanet
    void* FUN_00b67740(void*);               // 0x00b67740
    void* FUN_00befee0(void*, int);          // 0x00befee0
    void* FUN_00ffd710(void*);               // 0x00ffd710
    void  FUN_00c71530b();                   // placeholder
    void* FUN_00b316c0();                    // 0x00b316c0 -> u64
    void* FUN_00c8b770();                    // GetSolarSystem
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }

// ---------------------------------------------------------------------------
struct SimGame {
    u8 raw[0x400];
    void* f4bb0(int key);
    int   f4c00();
    char  f4c30();
    void  f4c80(float* dir);
    char  f52d0(int id);
    void  f5320();
    void  f5130();
    void* f5180(int param);
    bool  f53c0(int msg, int* p);
};
void  __stdcall f50d0(int param);
void  f4fc0(int* key);
void  f4e50();
bool  f53a0();

// ===========================================================================
// 0x01004bb0
// ===========================================================================
// @ 0x01004bb0
void* SimGame::f4bb0(int key) {
    int** it = *(int***)(raw + 0x78);
    if (it != *(int***)(raw + 0x7c)) {
        do {
            int* p = *it;
            if (((int(__thiscall*)(void*))VTP(p)[0x4c / 4])(p) == key && p[0x1c5] == 3)
                return p;
            ++it;
        } while (it != *(int***)(raw + 0x7c));
    }
    return 0;
}

// ===========================================================================
// 0x01004c00
// ===========================================================================
// @ 0x01004c00
int SimGame::f4c00() {
    int n = 0;
    int** it = *(int***)(raw + 0x78);
    int** end = *(int***)(raw + 0x7c);
    for (; it != end; ++it) {
        if ((*it)[0x1c5] == 8) ++n;
    }
    return n;
}

// ===========================================================================
// 0x01004c30
// ===========================================================================
// @ 0x01004c30
char SimGame::f4c30() {
    void* sim = FUN_00ffbe50();
    void* inv = E(sim)->FUN_00a1ad60();
    int target = *(int*)((char*)inv + 0x544);
    int** it = *(int***)(raw + 0x78);
    if (it != *(int***)(raw + 0x7c)) {
        do {
            int* p = *it;
            if (p[0x1c5] == 8) {
                if (((int(__thiscall*)(void*))VTP(p)[0x4c / 4])(p) == target) return 1;
            }
            ++it;
        } while (it != *(int***)(raw + 0x7c));
    }
    return 0;
}

// ===========================================================================
// 0x01004c80
// ===========================================================================
// @ 0x01004c80
void SimGame::f4c80(float* dir) {
    char* s = (char*)raw;
    void* app = FUN_0067dd10();
    void* a1 = ((void*(__thiscall*)(void*))VTP(app)[0x50 / 4])(app);
    void* a2 = ((void*(__thiscall*)(void*))VTP(a1)[0x38 / 4])(a1);
    if (!a2) return;
    void* esi = ((void*(__thiscall*)(void*, u32))VTP(a2)[0x0c / 4])(a2, 0x303154cc);
    if (!esi) return;
    void* sim = FUN_00ffbe50();
    void* inv = E(sim)->FUN_00a1ad60();
    float x = dir[0] - *(float*)((char*)inv + 0x718);
    float y = dir[1] - *(float*)((char*)inv + 0x71c);
    float z = dir[2] - *(float*)((char*)inv + 0x720);
    float len2 = x * x + y * y + z * z;
    if (len2 <= 0.0f) return;
    float inv2 = 1.0f / len2;
    x *= inv2; y *= inv2; z *= inv2;
    *(float*)((char*)esi + 0xc8) = *(float*)((char*)esi + 0x6c);
    *(float*)((char*)esi + 0xc0) = *(float*)((char*)esi + 0x70);
    int ctx = FUN_01021080();
    float timer;
    if (ctx == 1) timer = *(float*)(s + 0x38);
    else if (ctx == 2) timer = *(float*)(s + 0x34);
    else return;
    float f = timer * DAT_015b64c0;
    x = -x; y = -y; z = -z;
    float out[3];
    FUN_01042480(out, &x);
    *(float*)((char*)esi + 0xcc) = out[2];
    *(float*)((char*)esi + 0xc4) = out[1];
    *(float*)((char*)esi + 0xc4) = out[1] - f;
    *(float*)((char*)esi + 0xd0) = 0.0f;
    *(u8*)((char*)esi + 0xd4) = 1;
}

// ===========================================================================
// 0x01004e50 SP::BlowUpPlanet
// ===========================================================================
// @ 0x01004e50
void f4e50() {
    if (FUN_01021080() != 0) return;
    void* rec = FUN_010212a0();
    void* planet = FUN_01021260();
    int sortv = (int)(intptr_t)E(rec)->FUN_00b8de30();
    E(rec)->FUN_00b8d950(1);
    FUN_00c706d0(rec, 0);
    void* ach = FUN_00675250(0x5c54d48f, 1);
    ((void(__thiscall*)(void*, u32, int))VTP(ach)[0])(ach, 0x5c54d48f, 1);
    void* sm = FUN_00b3d2a0();
    int m = (int)(intptr_t)FUN_00ba70a0();
    if (sortv == m) {
        if (E((void*)sortv)->FUN_00bbaa60(0) == (int)(intptr_t)rec) {
            void* ach2 = FUN_00675250(0xc280a311, 1);
            ((void(__thiscall*)(void*, u32, int))VTP(ach2)[0])(ach2, 0xc280a311, 1);
        }
    }
    void* star = (void*)FUN_01021230(0);
    void* ss = (void*)E(star)->FUN_00c8b770();
    (void)ss;
    E(rec)->FUN_00bb9c40(1);
    u32 locals[16] = {0};
    FUN_00e39ab0(0x57779cbb, 0, 0, 0, 0);
    void* t = FUN_00fd9c60(0);
    FUN_00fde3e0(t);
    (void)sm; (void)planet; (void)locals;
}

// ===========================================================================
// 0x01004fc0
// ===========================================================================
// @ 0x01004fc0
void f4fc0(int* key) {
    void* rec = FUN_010212a0();
    if (!rec) return;
    int begin = *(int*)((char*)rec + 0xd0);
    int end = *(int*)((char*)rec + 0xd4);
    if (FUN_00ac0d80((void*)begin, (void*)end, key, 0) == (void*)end) return;
    void* prof = FUN_004df550(FUN_00401090(key));
    if (!prof) return;
    if (*(int*)((char*)prof + 0x57c) != (int)0x9ea3031a) return;
    void* h = FUN_01041d30(prof);
    int lc = 0, l8 = 0, l4 = 0;
    void* unused = FUN_00b3d450();
    (void)unused;
    for (;;) {
        if (lc != 0 && (lc != key[0] || l8 != key[1] || l4 != key[2])) break;
        void* n = FUN_00ac10a0(h);
        if (!n) return;
        lc = *(int*)((char*)n + 0x504);
        l8 = *(int*)((char*)n + 0x508);
        l4 = *(int*)((char*)n + 0x50c);
    }
    void* planet = FUN_01021260();
    if (!planet) return;
    FUN_00c74730(planet, key);
    void* x = FUN_008414c0();
    if (!x) return;
    FUN_00c7ed00(x, key);
    (void)begin; (void)end;
}

// ===========================================================================
// 0x010050d0
// ===========================================================================
// @ 0x010050d0
void __stdcall f50d0(int param) {
    void* nouns = FUN_00b3d300();
    void* civ = E(nouns)->FUN_00b25fb0();
    if (!civ) return;
    if ((int)(intptr_t)E(civ)->FUN_00bf01e0() <= 0) return;
    int* v = (int*)(intptr_t)E(civ)->FUN_00bef6c0();
    int* it = (int*)v[0];
    int* end = (int*)v[1];
    for (; it != end; ++it) {
        void* z = E((void*)*it)->FUN_00bd9e30();
        if (z) {
            void* obj = (void*)((char*)z + 0x34);
            ((void(__thiscall*)(void*, int))VTP(obj)[0x54 / 4])(obj, param);
        }
    }
}

// ===========================================================================
// 0x01005130
// ===========================================================================
// @ 0x01005130
void SimGame::f5130() {
    char* s = (char*)this;
    void* m = E(*(void**)(s + 0x14))->FUN_01067e60();
    if (m) {
        E(m)->FUN_00e0fb50();
        E(m)->FUN_00e0ad00(4);
        E(m)->FUN_00e0e1a0();
    }
    E(*(void**)(s + 0x14))->FUN_0106ab20(1);
    FUN_0106200(*(void**)(s + 0x14), 0);
    void* nouns = FUN_00b3d300();
    E(nouns)->FUN_00b22960();
}

// ===========================================================================
// 0x01005180
// ===========================================================================
// @ 0x01005180
void* SimGame::f5180(int param) {
    char* s = (char*)this;
    FUN_0067de90(4, (void*)param);
    void* esi = (void*)FUN_007ec160(4, (void*)param);
    if (!esi) return 0;
    ((void(__thiscall*)(void*, int))VTP(esi)[0])(esi, 7);
    void* tm = FUN_00b3d380();
    unsigned __int64 t = FUN_00b316c0();
    (void)t;
    return esi;
}

// ===========================================================================
// 0x010052d0
// ===========================================================================
// @ 0x010052d0
char SimGame::f52d0(int id) {
    int n = (*(int*)(raw + 0xe0) - *(int*)(raw + 0xdc)) / 0x14;
    if (n > 0) {
        int* p = (int*)(*(int*)(raw + 0xdc) + 0xc);
        for (int i = 0; i < n; ++i) {
            if (*p == id) return 1;
            p += 5;
        }
    }
    return 0;
}

// ===========================================================================
// 0x01005320
// ===========================================================================
// @ 0x01005320
void SimGame::f5320() {
    char* s = (char*)raw;
    char* it = *(char**)(s + 0);
    char* end = *(char**)(s + 4);
    for (; it < end; it += 0x14) {
        ((void(__thiscall*)(void*, int))VTP(it)[8 / 4])(it, 0);
    }
    void* base = *(void**)(s + 0);
    if (base && *(int*)((char*)base - 4) != 0) {
        FUN_00f47380(base);
    }
}

// ===========================================================================
// 0x010053a0
// ===========================================================================
// @ 0x010053a0
bool f53a0() {
    void* s = DAT_016dc0fc;
    void* o = *(void**)((char*)s + 0x40);
    return ((char(__thiscall*)(void*, u32))VTP(o)[0x74 / 4])(o, (u32)(uintptr_t)&DAT_016dc1e0) != 0;
}

// ===========================================================================
// 0x010053c0
// ===========================================================================
// @ 0x010053c0
bool SimGame::f53c0(int msg, int* p) {
    void* piVar2 = ((void*(__thiscall*)(void*))VTP(p)[0x10 / 4])(p);
    void* piVar3 = ((void*(__thiscall*)(void*, int))VTP(piVar2)[0x1c / 4])(piVar2, 0);
    void* ppuVar4;
    if ((*(u8*)((char*)piVar3 + 0x10) & 0x30) != 0) {
        piVar3 = *(void**)piVar3;
        ppuVar4 = piVar3 ? ((void*(__thiscall*)(void*, u32))VTP(piVar3)[0x0c / 4])(piVar3, 0x17f243b) : 0;
    } else {
        ppuVar4 = (*(u16*)((char*)piVar3 + 0x12) == 0) ? 0
                  : ((void*(__thiscall*)(void*, u32))VTP(piVar3)[0x0c / 4])(piVar3, 0x17f243b);
    }
    void* tm = FUN_00b3d380();
    if (*(u8*)((char*)tm + 0x48) & 1) return true;
    ((void(__thiscall*)(void*, int))VTP(piVar2)[0x1c / 4])(piVar2, 1);
    E(*(void**)(raw + 0x40))->FUN_00ff3f00();

    if (msg == 0x5417b45) {
        if (!ppuVar4) return true;
        ((void(__thiscall*)(void*, u32))VTP(ppuVar4)[0x0c / 4])(ppuVar4, 0x13f94d4);
        return true;
    } else if (msg == 0x4dd13d1) {
        void* t = FUN_00b18720(ppuVar4);
        if (!t) return true;
        FUN_00ffbe50();
        return true;
    } else if (msg == 0x22d38ee) {
        void* planet = (void*)FUN_00ffbe50();
        if (planet) { }
        return true;
    } else if (msg == 0x2e81d88) {
        return true;
    } else if (msg == 0x3056566) {
        return true;
    } else if (msg == 0x589c84b) {
        return true;
    } else if (msg == 0x54a7806) {
        return true;
    } else if (msg == 0x57df7e0) {
        return true;
    }
    return true;
}
