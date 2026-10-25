// src/game/SPGonzago/SPSimulatorColony.cpp -- migrated from slice(s) s00ff4d50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimulatorColony.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlayer.h"
#include "SP/cTribe.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPropertyList.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern char g_18c43e8[];    // [0x018c43e8] game-data selection key
extern char g_00cd7d10[];   // [0x00cd7d10] game-data selector
extern char g_00d3d420[];   // [0x00d3d420] game-data selector
extern char g_00acdff0[];   // [0x00acdff0] game-data selector
extern char g_00b1e500[];   // [0x00b1e500] game-data selector
extern void* g_vtbl_cColonySimulator;    // [0x01494ee4]
extern void* g_vtbl_cContentValidation;  // [0x013ec458]

// ---- items of slice s00ff4d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void* (__thiscall *FnVp0)(void*);
typedef int   (__thiscall *FnVp0i)(void*);
typedef char  (__thiscall *FnVp0c)(void*);
void  __cdecl operator_delete_array(void* p);                                            // 0x00f47380
extern char g_18c43e8[];    // [0x018c43e8] game-data selection key
extern char g_00cd7d10[];   // [0x00cd7d10] game-data selector
extern char g_00d3d420[];   // [0x00d3d420] game-data selector
extern char g_00acdff0[];   // [0x00acdff0] game-data selector
extern char g_00b1e500[];   // [0x00b1e500] game-data selector
extern void* g_vtbl_cColonySimulator;    // [0x01494ee4]
extern void* g_vtbl_cContentValidation;  // [0x013ec458]
struct CFileCountHolder {
    int __thiscall GetFileCount();   // 0x008e7f80
};
struct CNoun120 {
    void** mpVtbl;                          // +0x000
    char   pad04[0x120 - 0x04];
    CFileCountHolder mFileCount120;         // +0x120
    char   pad124[0x588 - 0x124];
    CFileCountHolder mFileCount588;         // +0x588
};
struct CTribe {
    void** mpVtbl;                          // +0x000
    char   pad04[0x354 - 0x04];
    CNoun120** mAgents;                     // +0x354
    CNoun120** mAgentsEnd;                  // +0x358

    int** __thiscall GetMembers();          // 0x00c8e810
};
struct cGonzagoTimer {
    void __thiscall ctor();                    // 0x00b63890
    void __thiscall dtor();                    // 0x00b638b0
    void __thiscall Start();                   // 0x00bc30f0
    void __thiscall Restart();                 // 0x00bc3130
    long long __thiscall GetElapsedTime();     // 0x00bc3190
    char pad[0x40];
};
struct cColonySimulator {
    void* mpVtbl;                            // +0x00
    int   m04;                               // +0x04
    cGonzagoTimer mTimer;                    // +0x08

    cColonySimulator* __thiscall ctor();                       // 0x00ff54e0
    void* __thiscall scalarDeletingDtor(char flags);           // 0x00ff5810
    void __thiscall DoGrowthSim(void* city);                   // 0x00ff5720
    void __thiscall OnTick(int a, int b, int c);               // 0x00ff5840
};
struct CCityGrow {
    void** mpVtbl;                       // +0x000
    char   pad04[0x120 - 0x04];
    void** mpCombatVtbl;                 // +0x120
    char   pad124[0x340 - 0x124];
    int    mCount340;                    // +0x340
    int    mCount344;                    // +0x344
    char   pad348[0x354 - 0x348];
    int    mCount354;                    // +0x354
    int    mCount358;                    // +0x358

    int  __thiscall FUN_00bd8110();      // 0x00bd8110
    int  __thiscall FUN_00bd9b60();      // 0x00bd9b60
    int  __thiscall GetCreatureCount();  // 0x00bd8120
    void __thiscall FUN_00c74860(int v);// 0x00c74860
    void __thiscall FUN_00bd9e50();      // 0x00bd9e50
    void __thiscall FUN_00be2070(int a, int b); // 0x00be2070
    void __thiscall FUN_00be5130(int v); // 0x00be5130
    void __thiscall FUN_00be7370(int v); // 0x00be7370
    void __thiscall FUN_00be3850();      // 0x00be3850
    void* __thiscall FUN_00bd7ef0(int v);// 0x00bd7ef0
    int  __thiscall FUN_00bdb590(void* a, int b); // 0x00bdb590
    int** __thiscall GetMembers();       // 0x00c8e810
};
int __cdecl FUN_00bdb470(int v);   // 0x00bdb470
void* __cdecl FUN_00b3d480(void* city, int flag);   // 0x00b3d480
struct CAc8cd0 { void* __thiscall FUN_00ac8cd0(); }; // 0x00ac8cd0
struct CNounManagerB {
    int* __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, void* e); // 0x00b21340
};
void* __cdecl FUN_00b3d300_1();    // 0x00b3d300  SP::NounManager (no argument form)
void* __cdecl FUN_01029940();      // 0x01029940  SP::GetSpaceCombatTuning
struct CCombatTuning {
    int __thiscall GetSecondsBetweenColonySimulatorTicks();   // 0x01029b50
};
struct CColonyEntry {
    void* __thiscall GetCity();          // 0x00bd9e30
};
// ---- items of slice s00ff4d50 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_00ff5330(int param_1, int* param_2, int* param_3, int* param_4, int* param_5, int* param_6);  // 0x00ff5330 (stays in the slice: not this object's)
void __cdecl FUN_00ff5410(CTribe* param_1, int* param_2, int* param_3, int* param_4, int* param_5, int* param_6);  // 0x00ff5410 (stays in the slice: not this object's)

// @ 0x00ff5510
int __cdecl SP_DetermineCityGrowth(CCityGrow* param_1, int* param_2)
{
    int local_28 = 0;
    int iStack_24, iStack_20, iStack_1c, iStack_18;
    int iStack_14, iStack_10, iStack_c, iStack_8, iStack_4;
    int i = 0;

    if (param_1 == 0)
        return local_28;

    char cVar2 = ((FnVp0c)((VObj*)&param_1->mpCombatVtbl)->vt[0x58 / 4])(&param_1->mpCombatVtbl);
    int uVar3 = param_1->FUN_00bd8110();

    iStack_18 = 0;
    iStack_10 = 0;
    iStack_8 = 0;
    iStack_20 = 0;
    iStack_24 = 0;
    FUN_00ff5410((CTribe*)param_1, &iStack_18, &iStack_10, &iStack_8, &iStack_20, &iStack_24);
    int sum = iStack_24 + iStack_20 + iStack_8 + iStack_10 + iStack_18;

    iStack_1c = 0;
    iStack_14 = 0;
    iStack_c = 0;
    iStack_4 = 0;
    FUN_00ff5330(uVar3, &iStack_24, &iStack_1c, &iStack_14, &iStack_c, &iStack_4);

    if (cVar2 == 0) {
        if (iStack_20 != iStack_1c) {
            local_28 = iStack_1c - iStack_20;
            *param_2 = 0xff10521;
        } else if (iStack_10 != iStack_14) {
            *param_2 = 0x1a55e4d;
            return iStack_14 - iStack_10;
        } else if (iStack_8 != iStack_c) {
            *param_2 = 0xecade42;
            return iStack_c - iStack_8;
        } else if (iStack_24 != iStack_4) {
            *param_2 = 0x436f315;
            return iStack_4 - iStack_24;
        }
    } else if (iStack_4 + iStack_c + iStack_14 + iStack_1c + iStack_24 < sum) {
        if (sum - iStack_20 < iStack_20) {
            *param_2 = 0x436f315;
            return -1;
        }
        int** members = param_1->GetMembers();
        int count = (int)(members[1] - members[0]) >> 2;
        if (count > 0) {
            do {
                CNoun120* m = (CNoun120*)((int*)members[0])[i];
                int t = ((FnVp0i)((VObj*)m)->vt[0x38 / 4])(m);
                if (t != 0x1007ae63) {
                    *param_2 = ((FnVp0i)((VObj*)m)->vt[0x38 / 4])(m);
                    return -1;
                }
                i++;
            } while (i < count);
            return 0;
        }
    }
    return local_28;
}

// @ 0x00ff5720
void __thiscall cColonySimulator::DoGrowthSim(void* city)
{
    if (city == 0)
        return;

    int code;
    int r = SP_DetermineCityGrowth((CCityGrow*)city, &code);
    CCityGrow* c = (CCityGrow*)city;

    if (r >= 1) {
        if (code == 0x436f315) {
            if (FUN_00bdb470(0x436f315) == 0)
                c->FUN_00be3850();
        } else if (FUN_00bdb470(code) == 0) {
            void* a = c->FUN_00bd7ef0(code);
            if (c->FUN_00bdb590(a, 0) != 0)
                c->FUN_00be7370(code);
        }
    } else if (r < 0) {
        if (code == 0x436f315)
            c->FUN_00be2070(0, 0);
        else
            c->FUN_00be5130(code);
        c->FUN_00bd9e50();
    }

    int v = ((c->mCount358 - c->mCount354) >> 2) + ((c->mCount344 - c->mCount340) >> 2);
    v -= c->FUN_00bd9b60();
    v = v * 5;
    if (v > 100)
        v = 100;
    if (v != c->GetCreatureCount()) {
        c->FUN_00c74860(v);
        void* o = FUN_00b3d480(city, 0);
        ((CAc8cd0*)o)->FUN_00ac8cd0();
    }
}

// @ 0x00ff5810
void* __thiscall cColonySimulator::scalarDeletingDtor(char flags)
{
    mpVtbl = &g_vtbl_cColonySimulator;
    mTimer.dtor();
    mpVtbl = &g_vtbl_cContentValidation;
    if ((flags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// @ 0x00ff5840
void __thiscall cColonySimulator::OnTick(int a, int b, int c)
{
    CNounManagerB* nm = (CNounManagerB*)FUN_00b3d300_1();
    int* vecBase = (int*)nm->GetGameDataVector(g_00cd7d10, g_00d3d420, g_00acdff0,
                                               g_00b1e500, g_18c43e8);
    int* vec = vecBase + 1;

    CCombatTuning* tuning = (CCombatTuning*)FUN_01029940();
    long long interval = tuning->GetSecondsBetweenColonySimulatorTicks() * 1000;

    long long elapsed = mTimer.GetElapsedTime();
    if ((unsigned long long)elapsed > (unsigned long long)interval) {
        mTimer.Restart();
        int n = (vec[1] - vec[0]) >> 2;
        for (int i = 0; i < n; ++i) {
            int* city = (int*)((int*)vec[0])[i];
            if (city[0x74c / 4] == -1)
                DoGrowthSim(city);
        }
    }

    int n2 = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n2; ++i) {
        CColonyEntry* e = (CColonyEntry*)((int*)vec[0])[i];
        void* p = e->GetCity();
        if (p != 0) {
            char ok = ((FnVp0c)((VObj*)((char*)p + 0x34))->vt[0x50 / 4])((char*)p + 0x34);
            if (ok != 0)
                ((FnVp0)((VObj*)p)->vt[0x68 / 4])(p);
        }
    }
}
