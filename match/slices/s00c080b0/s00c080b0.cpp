// Slice s00c080b0: creature attack/idle reset + game-data owner teardown.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---------------------------------------------------------------------------------------
// out-of-slice support declarations
// ---------------------------------------------------------------------------------------
extern float DAT_0168d844;                                  // 0x0168d844 default orientation x
extern float DAT_0168d848;                                  // 0x0168d848 default orientation y
extern float DAT_0168d84c;                                  // 0x0168d84c default orientation z

void* FUN_00b3d310();                                       // 0x00b3d310 global manager getter
void* SP_NounManager();                                     // 0x00b3d300
void* SP_PosseSimulator();                                  // 0x00d539d0
void* SP_BehaviorManager();                                 // 0x00b3d260
void  FUN_00c0d3a0(void* obj);                              // 0x00c0d3a0 (cdecl)
void  FUN_011e0744(void* first, void* last, int value);     // 0x011e0744 eastl::vector<bool>::DoInsertValue
void  remove_1st(void* vec, void* value);                   // 0x00acca00 spstl::remove_1st<...>

// eastl stores a 4-byte bookkeeping word immediately before a heap block
struct AllocHeader { int mOwner; };

// vtable-only sub-object embedded in cCreatureBase at +0x58 (the behaviour agent)
struct cBehaviorAgent { void* mpVtbl; };

// sub-object embedded in cCreatureBase at +0xc0 (locomotion / terrain agent)
struct cLocomotionAgent
{
    void* mpVtbl;                                   // +0x00
    void  FUN_00c41d60(const float* dir);           // 0x00c41d60
};

// object reached through cCreatureBase::mpAttackState (+0x1624)
struct cAttackState
{
    void* mpVtbl;                                   // +0x00
    void  FUN_00bc9de0(int anim);                   // 0x00bc9de0
};

// object returned by FUN_00b3d310()
struct cGlobalManager
{
    void* mpVtbl;                                   // +0x00
    void  FUN_00b45410(void* arg);                  // 0x00b45410
};

// noun manager (SP::cGameNounManager)
struct cGameNounManager
{
    void* mpVtbl;                                   // +0x00
    int   GetAvatar();                              // 0x00b1fdb0
    void  FUN_00b1fd50(int arg);                    // 0x00b1fd50
};

// posse simulator (SP::cPosseSimulator)
struct cPosseSimulator
{
    void* mpVtbl;                                   // +0x00
    void  RemovePosseMember(void* member, int a, int b);  // 0x00d53490
};

// behaviour manager (SP::cBehaviorManager): its vtable slot +0x3c takes the agent pointer
struct cBehaviorManager { void* mpVtbl; };

// flag word at cGameData+0xb58 (bit 8 is tested by RemoveOwner)
struct cGameDataFlags
{
    unsigned pad0  : 8;     // bits 0..7
    unsigned mbOwned : 1;   // bit 8
    unsigned pad9  : 23;    // bits 9..31
};

// The 0x74-byte block handed to the locomotion agent's vtable slot +0xdc.
struct AttackParams
{
    void* mpBegin;        // +0x00  eastl::vector<bool> heap block (released after the call)
    void* mpEnd;          // +0x04
    void* mpCapacity;     // +0x08
    char  pad0c[8];       // +0x0c
    float qx;             // +0x14
    float qy;             // +0x18
    float qz;             // +0x1c
    float qw;             // +0x20
    int   i24;            // +0x24
    char  pad28[0x24];    // +0x28
    char  b4c;            // +0x4c
    char  pad4d[3];       // +0x4d
    float f50;            // +0x50
    float f54;            // +0x54
    float f58;            // +0x58
    int   i5c;            // +0x5c
    float f60;            // +0x60
    float f64;            // +0x64
    float f68;            // +0x68
    float f6c;            // +0x6c
    int   i70;            // +0x70
};

// ---------------------------------------------------------------------------------------
// Simulator::cCreatureBase
// ---------------------------------------------------------------------------------------
struct cCreatureBase
{
    void*            mpVtbl;        // +0x00
    char             pad04[0x58 - 0x04];
    cBehaviorAgent   agent58;       // +0x58
    char             pad5c[0xc0 - 0x58 - 0x04];
    cLocomotionAgent agentC0;       // +0xc0
    char             padc4[0x328 - 0xc0 - 0x04];
    char             mbSelfPowered; // +0x328
    char             pad329[0x5e0 - 0x328 - 1];
    float            f5e0;          // +0x5e0
    char             pad5e4[0xb5e - 0x5e0 - 4];
    char             mbDead;        // +0xb5e
    char             padb5f[0xe3c - 0xb5e - 1];
    int              fE3C;          // +0xe3c
    char             pade40[0xe8c - 0xe3c - 4];
    int              fE8C;          // +0xe8c
    int              fE90;          // +0xe90
    float            fE94;          // +0xe94
    char*            mpE98;         // +0xe98
    char*            mpE9C;         // +0xe9c
    char             padea0[0x1624 - 0xe9c - 4];
    cAttackState*    mpAttackState; // +0x1624
    char             pad1628[0x1674 - 0x1624 - 4];
    void*            mp1674;        // +0x1674
    char             pad1678[0x1698 - 0x1674 - 4];
    void*            mp1698;        // +0x1698

    void  func8Ch();                // 0x00c080b0
    void  FUN_00c0cff0(int arg);    // 0x00c0cff0
    void  FUN_00c0d240();           // 0x00c0d240
    void  FUN_00c17350(int id, int arg);  // 0x00c17350
};

// =======================================================================================
// 00c080b0 -- Simulator::cCreatureBase::func8Ch (attack/idle state reset)
// =======================================================================================
// @ 0x00c080b0
void cCreatureBase::func8Ch()
{
    // stop the running behaviour (agent embedded at +0x58, vtable slot +0x34)
    ((void (__thiscall*)(void*))VTC(&agent58, 0x34))(&agent58);

    // SetCreatureTarget(null, null, false) on the creature itself (vtable slot +0x84)
    ((void (__thiscall*)(void*, int, int, int))VTC(this, 0x84))(this, 0, 0, 0);

    mbSelfPowered = 0;
    f5e0 = 0.0f;

    // build the locomotion parameter block
    AttackParams p;
    p.qx = DAT_0168d844;
    p.qy = DAT_0168d848;
    p.qz = DAT_0168d84c;
    p.qw = 1.0f;
    p.f60 = 2.0f;
    p.f64 = 0.9f;
    p.mpBegin = 0;
    p.mpEnd = 0;
    p.mpCapacity = 0;
    p.i24 = 0;
    p.b4c = 0;
    p.f50 = 0.0f;
    p.f54 = 0.0f;
    p.f58 = 0.0f;
    p.i5c = 0;
    p.f68 = 3.402823466e+38F;
    p.f6c = 0.0f;
    p.i70 = 0;

    // locomotion agent (embedded at +0xc0), vtable slot +0xdc
    ((void (__thiscall*)(void*, AttackParams*))VTC(&agentC0, 0xdc))(&agentC0, &p);

    // release the eastl vector<bool> buffer the call may have allocated
    if (p.mpBegin != 0) {
        AllocHeader* hdr = (AllocHeader*)p.mpBegin - 1;
        if (hdr->mOwner != 0) {
            char* block = (char*)p.mpBegin;
            delete[] block;
        }
    }

    FUN_00c0cff0(0);
    agentC0.FUN_00c41d60(&DAT_0168d844);

    fE8C = -1;
    fE90 = -1;
    fE94 = 0.0f;

    char* const begin = mpE98;
    FUN_011e0744(begin, mpE9C, 0);
    mpE9C += -((int)(mpE9C - begin) >> 2) * 4;

    fE3C = -1;
    FUN_00c0d240();
    mbDead = 1;
    mpAttackState->FUN_00bc9de0(-1);
    FUN_00c17350(0x2c4bf1c, 0);

    if (FUN_00b3d310() != 0)
        ((cGlobalManager*)FUN_00b3d310())->FUN_00b45410(&agentC0);
}

// ---------------------------------------------------------------------------------------
// Simulator::cGameData
// ---------------------------------------------------------------------------------------
struct cGameData
{
    void*          mpVtbl;          // +0x00
    char           pad04[0x58 - 0x04];
    cBehaviorAgent agent58;         // +0x58
    char           pad5c[0xb58 - 0x58 - 0x04];
    cGameDataFlags   flagsB58;      // +0xb58
    char           padb5c[0x1624 - 0xb58 - 4];
    cAttackState*  mpAttackState;   // +0x1624
    char           pad1628[0x1674 - 0x1624 - 4];
    void*          mp1674;          // +0x1674
    char           pad1678[0x1698 - 0x1674 - 4];
    void*          mp1698;          // +0x1698

    void RemoveOwner();             // 0x00c08270
    void FUN_00c1c8e0();            // 0x00c1c8e0
};

// =======================================================================================
// 00c08270 -- Simulator::cGameData::RemoveOwner
// =======================================================================================
// @ 0x00c08270
void cGameData::RemoveOwner()
{
    FUN_00c0d3a0(this);
    mpAttackState->FUN_00bc9de0(-1);

    if (this == (cGameData*)((cGameNounManager*)SP_NounManager())->GetAvatar())
        ((cGameNounManager*)SP_NounManager())->FUN_00b1fd50(0);

    if (flagsB58.mbOwned)
        ((cPosseSimulator*)SP_PosseSimulator())->RemovePosseMember(this, 0, 1);

    void* agent = &agent58;
    cBehaviorManager* bm = (cBehaviorManager*)SP_BehaviorManager();
    ((void (__thiscall*)(void*, void*))VTC(bm, 0x3c))(bm, agent);

    ((void (__thiscall*)(void*, int, int, int))VTC(this, 0x84))(this, 0, 0, 0);

    if (mp1674 != 0) {
        cGameData* tmp = this;
        remove_1st((char*)mp1674 + 0x40, &tmp);
    }
    if (mp1674 != 0) {
        void* obj = mp1674;
        mp1674 = 0;
        ((void (__thiscall*)(void*))VTC(obj, 0x04))(obj);
    }

    void* obj = mp1698;
    mp1698 = 0;
    if (obj != 0)
        ((void (__thiscall*)(void*))VTC(obj, 0x64))(obj);

    FUN_00c1c8e0();
}
