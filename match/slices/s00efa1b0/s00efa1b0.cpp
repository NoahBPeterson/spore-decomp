// Slice s00efa1b0 -- Simulator::cScenarioTutorials::Update (4904-byte switch dispatcher on
// mCategory at +0x30, cases 0..0xb).  Region flags: /O2 /MD /Gy /TP
//
// PARTIAL: the case bodies are large inlined sequences (FUN_00ef8820 guards, FUN_00ef8390
// three-float placement calls, FUN_00efa0b0/FUN_00efa110 category helpers).  Only the
// dispatch shape is reproduced here; the per-case bodies are approximated.
#include "types.h"

struct cScenarioTutorials {
    char* self() { return (char*)this; }
    void Update();   // 0x00efa1b0
    void HandleCategoryMessage(int, int);  // 0x00efa110
    void SetCategoryState(int, char);      // 0x00efa0b0
};

struct Guard   { bool f(int); };                      // 0x00ef8820
struct PlaceMgr{ void f(int, int, float, float, float); }; // 0x00ef8390
struct Cat     { void f(int); };                      // 0x00ef7a00
struct SimSvc  { void* f(int); };                     // 0x00ed4b50

extern void* g_Simulator;        // 0x016c7aa4
extern uint8_t g_16c7b50;        // 0x016c7b50
extern float g_v15acfd0[3];      // 0x015acfd0
extern float g_v15acff4[3];      // 0x015acff4
extern float g_v15ad000[3];      // 0x015ad000
extern float g_v15ad00c[3];      // 0x015ad00c
extern float g_v15ad018[3];      // 0x015ad018
extern float g_v15acfc0[3];      // 0x015acfc0 (case 0xb)

// @ 0x00efa1b0
void cScenarioTutorials::Update()
{
    char* self = (char*)this;
    switch (*(int*)(self + 0x30)) {
    case 0:
        if (!((Guard*)self)->f(1)) {
            if (g_16c7b50 != 0) {
                ((PlaceMgr*)self)->f(1, 0, g_v15acff4[0], g_v15acff4[1], g_v15acff4[2]);
            } else {
                *(uint8_t*)(self + 0x3e) = 1;
            }
        } else if (!((Guard*)self)->f(2)) {
            ((Cat*)((SimSvc*)(*(void**)((char*)g_Simulator + 0x14)))->f(0))->f(0);
            ((PlaceMgr*)self)->f(2, 0, g_v15ad000[0], g_v15ad000[1], g_v15ad000[2]);
        }
        break;
    case 1:
        if (!((Guard*)self)->f(3)) {
            ((PlaceMgr*)self)->f(3, 0, g_v15ad00c[0], g_v15ad00c[1], g_v15ad00c[2]);
        } else if (!((Guard*)self)->f(5)) {
            HandleCategoryMessage(4, (int)0xa9a5c32d);
        } else if (!((Guard*)self)->f(7)) {
            HandleCategoryMessage(6, (int)0xe760e7ce);
        } else if (!((Guard*)self)->f(8)) {
            ((PlaceMgr*)self)->f(8, 0, g_v15acfd0[0], g_v15acfd0[1], g_v15acfd0[2]);
        } else if (!((Guard*)self)->f(10)) {
            SetCategoryState(9, 0);
            *(uint8_t*)(self + 0x39) = 1;
        } else if (!((Guard*)self)->f(11)) {
            ((PlaceMgr*)self)->f(0xb, 0, g_v15ad018[0], g_v15ad018[1], g_v15ad018[2]);
        } else if (!((Guard*)self)->f(0));
        break;
    default:
        break;
    }
}
