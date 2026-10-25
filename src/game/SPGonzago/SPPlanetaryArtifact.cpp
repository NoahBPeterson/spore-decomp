// src/game/SPGonzago/SPPlanetaryArtifact.cpp -- migrated from slice(s) s00c73cb0, s00c68280 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanetaryArtifact.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cMovableDestructibleOrnament.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern int g_guard1693e00;       // 0x1693e00
extern int g_data1693dec[3];     // 0x1693dec
extern "C" void __cdecl FUN_013c4150();
#include <stdlib.h>
#include <math.h>
#include "SP/cSPPlanetaryArtifact.h"
#include "SP/cCivData.h"

// ---- items of slice s00c68280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_guard1693e00;       // 0x1693e00
extern int g_data1693dec[3];     // 0x1693dec
extern "C" void __cdecl FUN_013c4150();
// ---- items of slice s00c68280 end

// ---- items of slice s00c73cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* NounManager();                                                       // 0x00b3d300
void* FUN_01021260();                                                      // 0x01021260
void  GetPropertyAsKey(void* obj, int key, void* out);                     // 0x006a1250
void  RemoveArtifact(void* a, void* b, void* c);                           // 0x00c71160
struct cCombatant { void TakeHit(float d, int a, int b, int c, int e); };  // 0x00bfcdd0
struct NounMgr {                   // SP::NounManager() result
    void* GetCurrentTerrainSphere();   // 0x00f67d90  returns this->+0x74
    void* FUN_00b25f40(int id);        // 0x00b25f40
    void  RemoveNoun(void* noun);      // 0x00b225d0
};
struct MovableOrn { void cMovOrnCtor(); void cMovOrnDtor(); void FUN_00c69030(); };
struct cPlanetaryArtifact {
    void* mVtbl0;                  // +0x000
    void* mVtbl4;                  // +0x004
    char  mPad08[0x34 - 0x08];     // +0x008
    union { void* p34; int i34; }; // +0x034  secondary vptr / state int
    char  mPad38[0x108 - 0x38];    // +0x038
    void* mVtbl108;                // +0x108
    char  mPad10c[0x130 - 0x10c];  // +0x10c
    void* m130;                    // +0x130
    char  mPad134[0x144 - 0x134];  // +0x134
    void* m144;                    // +0x144 (8-byte sub-record)
    char  mPad148[0x150 - 0x148];  // +0x148
    int   m150;                    // +0x150
    char  mPad154[0x508 - 0x154];  // +0x154
    void* mVtbl508;                // +0x508
    char  mPad50c[0x5d0 - 0x50c];  // +0x50c
    void* mVtbl5d0;                // +0x5d0
    char  mPad5d4[0x638 - 0x5d4];  // +0x5d4
    void* m638;                    // +0x638
    void* m63c;                    // +0x63c
    void* m640;                    // +0x640
    void* m644;                    // +0x644
    void* m648;                    // +0x648
    void* m64c;                    // +0x64c
    void* m650;                    // +0x650
    void* m654;                    // +0x654
    int   m658;                    // +0x658
    char  m65c;                    // +0x65c
    char  m65d;                    // +0x65d
    char  m65e;                    // +0x65e
    char  mPad65f[1];              // +0x65f
    float m660;                    // +0x660

    void* FUN_00c74a50();          // ctor
    void  FUN_00c74ba0();
    void  FUN_00c74bd0();
    void  FUN_00c74c20(float dmg, int a, int b, int c, int d);
    bool  FUN_00c74ca0();
};
struct RefObj { virtual void v0(); virtual void v1(); };
// ---- items of slice s00c73cb0 end

// @ 0x00c69110
void* FUN_00c69110()
{
    if ((g_guard1693e00 & 1) == 0) {
        g_guard1693e00 |= 1;
        g_data1693dec[0] = 0;
        g_data1693dec[1] = 0;
        g_data1693dec[2] = 0;
        atexit(FUN_013c4150);
    }
    return g_data1693dec;
}

// @ 0x00c74ba0
void cPlanetaryArtifact::FUN_00c74ba0()
{
    if (m63c != 0) {
        void* p = m63c;
        m63c = 0;
        ((RefObj*)p)->v1();
    }
    ((MovableOrn*)this)->FUN_00c69030();
}

// @ 0x00c74bd0
void cPlanetaryArtifact::FUN_00c74bd0()
{
    mVtbl0 = (void*)0x1472bf0;
    mVtbl4 = (void*)0x1472bdc;
    p34 = (void*)0x1472ae0;
    mVtbl108 = (void*)0x1472ad8;
    mVtbl508 = (void*)0x1472a70;
    mVtbl5d0 = (void*)0x1472a08;
    if (m63c != 0)
        ((RefObj*)m63c)->v1();
    ((MovableOrn*)this)->cMovOrnDtor();
}

// @ 0x00c74c20
void cPlanetaryArtifact::FUN_00c74c20(float dmg, int a, int b, int c, int d)
{
    ((cCombatant*)this)->TakeHit(dmg, a, b, c, d);
    if (i34 == 2) {
        i34 = 0;
        if (m150 == 4) {
            void* p = FUN_01021260();
            if (p != 0)
                RemoveArtifact(*(void**)((char*)p + 0x13c), (void*)&m144, m130);
            ((NounMgr*)NounManager())->RemoveNoun((char*)this - 0x508);
        }
    }
}

// @ 0x00c74ca0
bool cPlanetaryArtifact::FUN_00c74ca0()
{
    unsigned local[3];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    GetPropertyAsKey(m63c, 0x34f1a4f, local);
    return local[0] == 0x7ecbe6f5u;
}
