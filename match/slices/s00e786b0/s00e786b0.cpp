// Slice s00e786b0 -- SP Cell/plant UI + digestion message helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- globals
extern char* g_cellGame;      // 0x016b3c04  _gspCellGame
extern char* g_16b3c0c;       // 0x016b3c0c
extern float g_1457e0c;       // 0x1457e0c
extern float g_1485378;       // 0x1485378
extern int   g_1483bd0[8];    // 0x1483bd0

// ---------------------------------------------------------------- callees (0x00e78e70)
void __cdecl FUN_00e538b0(int);
void __cdecl SP_sOnButtonSaveClick(void);
void __cdecl FUN_00e53ad0(void);
void __cdecl FUN_00e53920(void);
void __cdecl SP_sOnQuitDesktopButtonClick(void);
void __cdecl FUN_00e501f0(void);
void __cdecl FUN_00e53a20(void);
bool __cdecl FUN_00e00ac0(void);
void __cdecl FUN_00e53660(int, int);
void __cdecl SP_ShowContextSensitiveSporeGuide(void);
void __cdecl FUN_00e539c0(void);
void __cdecl FUN_00e78e40(void);
void __cdecl FUN_00e760f0(void);
void __cdecl FUN_00e53860(int);
void __cdecl FUN_00e5daa0(void);

// ---------------------------------------------------------------- 0x00e786b0 (partial)
void __cdecl SP_sCreatePlant_Type3(int, int, int, int) {}

// ---------------------------------------------------------------- 0x00e78830 (partial)
void __cdecl SP_sGenPlants(void) {}

// ---------------------------------------------------------------- 0x00e78b20 (partial)
void __fastcall FUN_00e78b20(int, int, int, int) {}

// ---------------------------------------------------------------- 0x00e78b80 (partial)
void __fastcall FUN_00e78b80(int, int, int) {}

// ---------------------------------------------------------------- 0x00e78c00 (partial)
int __fastcall FUN_00e78c00(int* p, int q) { (void)p; (void)q; return 0; }

// ---------------------------------------------------------------- 0x00e78d10 (partial)
void __cdecl FUN_00e78d10(void) {}

// ---------------------------------------------------------------- 0x00e78de0
int  __cdecl FUN_00b3d4d0(int);
void __cdecl FUN_00e77930(int);

struct CellStub { int b721d0(int); };
struct ObjStub  { void ad7e40(); };

void __cdecl FUN_00e78de0(void)
{
    void* o = (void*)FUN_00b3d4d0(0);
    ((ObjStub*)o)->ad7e40();
    *(char*)(g_16b3c0c + 0x936) = 0;
    *(char*)(g_16b3c0c + 0xe4) = 0;
    int v = ((CellStub*)(g_cellGame + 0x1c))->b721d0(*(int*)(g_cellGame + 0x411c));
    *(char*)(g_cellGame + 0x51dc) = 0;
    if (v)
        FUN_00e77930(v);
}

// ---------------------------------------------------------------- 0x00e78e40
void __cdecl FUN_00e53580(void);
void __cdecl FUN_00e78e40(void)
{
    FUN_00e53580();
    int v = ((CellStub*)(g_cellGame + 0x1c))->b721d0(*(int*)(g_cellGame + 0x411c));
    if (v)
        FUN_00e77930(v);
}

// ---------------------------------------------------------------- 0x00e78e70
bool __stdcall FUN_00e78e70(int unused, int* msg)
{
    if (msg[2] == (int)0x287259f6) {
        switch (msg[3]) {
        case 0x447060c: FUN_00e538b0(1); return true;
        case 0x10f366e: SP_sOnButtonSaveClick(); return true;
        case 0x10ed852: FUN_00e53ad0(); return true;
        case (int)0xd305ca84: FUN_00e53920(); return true;
        case 0x10f366d: SP_sOnQuitDesktopButtonClick(); return true;
        case 0x2268ba4: FUN_00e501f0(); return true;
        case 0x43b72d0: FUN_00e53a20(); return true;
        case 0x447060a:
            if (!FUN_00e00ac0())
                FUN_00e53660(2, 1);
            SP_ShowContextSensitiveSporeGuide();
            return true;
        case 0x595e0a8: FUN_00e53ad0(); return true;
        case 0x44827b8: FUN_00e539c0(); return true;
        case 0x44827b9: FUN_00e78e40(); return true;
        case 0x44837c0: FUN_00e760f0(); return true;
        case 0x6244208: FUN_00e53860(1); return true;
        case 0x6455c5e: FUN_00e5daa0(); return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------- 0x00e78fc0 (partial)
void __cdecl SP_sUpdateAICaterpillar(void) {}

// ---------------------------------------------------------------- 0x00e791a0 (partial)
void __cdecl FUN_00e791a0(int) {}

// ---------------------------------------------------------------- 0x00e791f0 (partial)
void __cdecl SP_sDigestionOutput(int, int, int) {}

// ---------------------------------------------------------------- 0x00e792b0 (partial)
void __cdecl SP_sDigestion_End(int, int) {}

// ---------------------------------------------------------------- 0x00e79320 (partial)
void __cdecl SP_sOnEatEater(int, int, int) {}

// ---------------------------------------------------------------- 0x00e79460 (partial)
void __fastcall FUN_00e79460(int, int, int, int) {}
