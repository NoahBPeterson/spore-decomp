// Slice s00be9850: Spore "Sim" manager members (4 functions, VAs 0x00be9850 .. 0x00be9cb0).
//
//   0x00be9850 Sim::sub_be9850    — "purchase from the noun": reject self/-1, look the noun up, resolve a
//                                  zero price via FUN_00be9250, check the civ's money, spend, then reset the
//                                  three eastl maps and re-seed map1 before notifying sub_be92e0.
//   0x00be9980 Sim::sub_be9980    — same purchase path, but keyed off this->f74c (>=100 s armed), with the
//                                  three-way "player civ / noun civ / neutral" feedback dispatch.
//   0x00be9b20 FUN_00be9b20       — free (cdecl) driver: clamp a price delta into [0,100] against a
//                                  Sim (or a fallback object), push it to that object, then either the
//                                  SpaceGame feedback path or the sub_be9980 purchase path.
//   0x00be9cb0 Sim::sub_be9cb0    — reset the three maps, re-seed map1[f64c], then sub_be92e0.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- eastl rbtree / map<unsigned,unsigned>
struct rbNodeBase {
    void* mpNodeRight;                  // +0x00
    void* mpNodeLeft;                   // +0x04
    void* mpNodeParent;                 // +0x08
    char  mColor;                       // +0x0c
    char  pad[3];
};
struct IntTreeMap {                     // sizeof 0x1c
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];                // +0x18
    int& operator[](const int& k);          // 0x00643a40
    void DoNukeSubtree(void* pNode);        // 0x009a9600
    void reset() {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
};

// ---------------------------------------------------------------- engine helpers
struct cCivilization {
    float GetMoney();                       // 0x00bef6d0
    void  SpendMoney(float amount);         // 0x00bef710
};

struct Avatar {
    void FUN00ffa900(void* a, int b);       // 0x00ffa900
};

struct cGameNounManager {
    void*   GetPlayerCivilization();        // 0x00b25fb0
    void*   FUN00b25f40(int key);           // 0x00b25f40
    Avatar* GetAvatar();                    // 0x00b1fdb0
};
cGameNounManager* GetNounManager();         // 0x00b3d300
cGameNounManager* SpaceGameGet();           // 0x01002bd0

void* GetCurrentGameMode();                 // 0x00b5b800
int   GetPlayerEmpireID();                  // 0x01021090
extern char DAT_01654c05;                   // 0x01654c05

struct cCivModeStrategy {
    void FUN00cf9040(void* a, unsigned b, unsigned c, void* d);   // 0x00cf9040
};
cCivModeStrategy* GetCivModeStrategy();     // 0x00cf74c0

struct RandomLCG {
    double RandomDoubleUniform();           // 0x009360d0
};
extern RandomLCG _sMathRandom;              // 0x01601760

// The "vehicle / object" operand of FUN_00be9b20.
struct Obj {
    char  pad0[0x38];
    int   f38;                              // +0x38
    float f3c;                              // +0x3c
    char  pad1[0x184 - 0x40];
    void* f184;                             // +0x184
    char  pad2[0x194 - 0x188];
    int   f194;                             // +0x194
    float FUN00b7e0a0();                    // 0x00b7e0a0
    int   FUN00a1ad10();                    // 0x00a1ad10
    void  FUN00ff03b0(int v);               // 0x00ff03b0
    void  FUN00ff03c0(float v);             // 0x00ff03c0
    int   FUN00b8dab0();                    // 0x00b8dab0
    void* FUN00b8de30();                    // 0x00b8de30
};
float FUN_00bd9a80(Obj* o);                 // 0x00bd9a80 (cdecl, returns float)
void  FUN_00c8d060(void* p);                // 0x00c8d060 (cdecl)

// ---------------------------------------------------------------- Sim
class Sim {
public:
    char       pad0[0x98];
    int        f98;                         // +0x98
    int        f9c;                         // +0x9c
    char       pad1[0x120 - 0xa0];
    void*      vptr120;                     // +0x120
    char       pad2[0x320 - 0x124];
    void*      p320;                        // +0x320
    char       pad3[0x590 - 0x324];
    void*      p590;                        // +0x590
    char       pad4[0x5a0 - 0x594];
    IntTreeMap map1;                        // +0x5a0
    IntTreeMap map2;                        // +0x5bc
    IntTreeMap map3;                        // +0x5d8
    char       pad5[0x64c - 0x5f4];
    int        f64c;                        // +0x64c
    char       pad6[0x748 - 0x650];
    float      f748;                        // +0x748
    int        f74c;                        // +0x74c

    void  sub_be9850(int a1, float a2);             // 0x00be9850
    void  sub_be9980(int a1);                       // 0x00be9980
    void  sub_be9cb0(int a1, int a2, int a3, int a4);// 0x00be9cb0
    float FUN00be9250(int a1);                      // 0x00be9250
    void  sub_be92e0(int, int, int, int, int);      // 0x00be92e0
    void  sub_bd9a00(void*);                        // 0x00bd9a00
    void  FUN00bd7d10(int iv, float v);             // 0x00bd7d10
};

#define VGETID(p)     ((int(__thiscall*)(void*))((void**)*(void***)(p))[0x4c / 4])((void*)(p))
#define VCALL(p,slot) ((void**)*(void***)(p))[(slot) / 4]
#define V120M3(p,slot,a,b,c) ((void*(__thiscall*)(void*,int,int,int))VCALL((char*)(p) + 0x120, slot))((void*)((char*)(p) + 0x120), (a), (b), (c))
#define V120M1(p,slot,a)     ((void*(__thiscall*)(void*,int))VCALL((char*)(p) + 0x120, slot))((void*)((char*)(p) + 0x120), (a))

// ==================================================================== 0x00be9850
// @ 0x00be9850
void Sim::sub_be9850(int a1, float a2)
{
    int id = VGETID(this->p590);
    if (a1 == id)
        return;
    cCivilization* noun = (cCivilization*)GetNounManager()->FUN00b25f40(a1);
    if (a2 == 0.0f)
        a2 = this->FUN00be9250(a1);
    if (0.0f > a2)
        return;
    if (noun->GetMoney() < a2)
        return;
    noun->SpendMoney(a2);
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    int v = this->f64c;
    this->map1[a1] = v;
    this->sub_be92e0(a1, 2, 0, 0, 0);
}

// ==================================================================== 0x00be9980
// @ 0x00be9980
void Sim::sub_be9980(int a1)
{
    int id = VGETID(this->p590);
    int key = this->f74c;
    if (key == -1)
        return;
    if (key == id)
        return;
    if (!(this->f748 >= 100.0f))
        return;
    void* noun = GetNounManager()->FUN00b25f40(key);
    void* civ  = GetNounManager()->GetPlayerCivilization();
    if (civ == this->p590) {
        GetCivModeStrategy()->FUN00cf9040(this, 0xedd4a52f, 0x2bb7aff, V120M3(this, 0x2c, 0, 1, 0));
    } else if (noun == civ) {
        GetCivModeStrategy()->FUN00cf9040(this, 0x43d2843c, 0x2bb7aff, V120M3(this, 0x2c, 0, 1, 0));
    } else if (*((char*)noun + 0x8a) == 0) {
        this->sub_bd9a00(noun);
    }
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    int v = this->f64c;
    this->map1[key] = v;
    this->f98 = 0;
    this->f9c = 0;
    this->sub_be92e0(key, 0, 0, a1, 0);
    if (this->p320 != 0)
        V120M1(this->p320, 0x2c, 0);
}

// ==================================================================== 0x00be9b20
// @ 0x00be9b20
void FUN_00be9b20(Obj* a1, Sim* sim, Obj* alt, int a4, float a5, int a6, int a7)
{
    float fv;
    int   iv;
    if (sim != 0) {
        fv = sim->f748;
        iv = sim->f74c;
    } else {
        fv = alt->FUN00b7e0a0();
        iv = alt->FUN00a1ad10();
    }
    if (a6 == -1)
        return;
    if (a6 == a4)
        return;
    float delta = a5 * 0.1f;
    int iv2 = iv;
    if (iv2 == -1)
        iv2 = a6;
    iv = iv2;
    float nv;
    if (iv == a6)
        nv = fv + delta;
    else
        nv = fv - delta;
    if (nv < 0.0f) {
        nv = -nv;
        iv = a6;
    }
    if (nv > 100.0f)
        nv = 100.0f;
    if (sim != 0) {
        sim->FUN00bd7d10(iv, nv);
    } else if (alt != 0) {
        alt->FUN00ff03b0(iv);
        alt->FUN00ff03c0(nv);
    }
    if (GetCurrentGameMode() != (void*)&DAT_01654c05
        || (a1->FUN00b8dab0() == 4 && a6 != GetPlayerEmpireID())) {
        sim->sub_be9980(a7);
        return;
    }
    if (nv < 100.0f)
        return;
    if (GetCurrentGameMode() == (void*)&DAT_01654c05 && sim != 0 && iv == GetPlayerEmpireID()) {
        float r = FUN_00bd9a80(a1);
        if (r > 0.0f && (float)_sMathRandom.RandomDoubleUniform() < r)
            SpaceGameGet()->GetAvatar()->FUN00ffa900(sim, iv);
    }
    FUN_00c8d060(a1->FUN00b8de30());
}

// ==================================================================== 0x00be9cb0
// @ 0x00be9cb0
void Sim::sub_be9cb0(int a1, int a2, int a3, int a4)
{
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    int v = this->f64c;
    this->map1[a1] = v;
    this->sub_be92e0(a1, a2, a3, 0, a4);
}
